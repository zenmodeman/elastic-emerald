#!/usr/bin/env python3
"""Rank defensive typings against fully evolved species based on data in expansion source.

Each attacker is classified only by its BEST  STAB matchup.
"""
from __future__ import annotations

import argparse
import csv
import io
import re
import subprocess
import sys
from collections import Counter
from dataclasses import dataclass
from itertools import combinations
from math import prod
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]


@dataclass(frozen=True)
class Species:
    name: str
    dex: str
    types: tuple[str, ...]
    evolves: bool
    mega: bool


def preprocess(source: str) -> str:
    prefix = '\n'.join([
        '#define TRUE 1', '#define FALSE 0',
        '#include "config/general.h"', '#include "config/pokemon.h"',
        '#include "config/battle.h"',
    ])
    return subprocess.run(
        ['cpp', '-E', '-P', '-I', str(ROOT / 'include'), '-x', 'c', '-'],
        input=prefix + '\n' + source, text=True, capture_output=True, check=True,
    ).stdout


def load_species() -> dict[str, Species]:
    paths = sorted((ROOT / 'src/data/pokemon/species_info').glob('gen_*_families.h'))
    if not paths:
        raise ValueError('No species headers found')
    source = preprocess('\n'.join(f'#include "{path}"' for path in paths))
    # Match only top-level species entries. Fields can contain nested braces.
    entries = list(re.finditer(r'\[(SPECIES_\w+)\]\s*=\s*\{', source))
    result = {}
    for index, entry in enumerate(entries):
        body = source[entry.end():entries[index + 1].start() if index + 1 < len(entries) else len(source)]
        typing = re.search(r'\.types\s*=\s*(?:MON_TYPES\(|\{)([^)}]+)[)}]', body)
        dex = re.search(r'\.natDexNum\s*=\s*(NATIONAL_DEX_\w+)', body)
        if not typing or not dex:
            raise ValueError(f'Missing types or dex number: {entry[1]}')
        types = tuple(sorted(set(re.findall(r'TYPE_\w+', typing[1]))))
        if not types or len(types) > 2:
            raise ValueError(f'Invalid types for {entry[1]}: {typing[1]}')
        result[entry[1]] = Species(entry[1], dex[1], types,
                                  bool(re.search(r'\.evolutions\s*=', body)),
                                  bool(re.search(r'\.isMegaEvolution\s*=\s*1\b', body)))
    if not result:
        raise ValueError('No species parsed')
    return result


def select_attackers(species: dict[str, Species]) -> list[Species]:
    # Form tables explicitly put the base form first, including species whose
    # constant carries a form suffix (e.g. Rotom, Basculin, and Floette).
    source = preprocess('#include "' + str(ROOT / 'src/data/pokemon/form_species_tables.h') + '"')
    bases = {}
    for body in re.findall(r'static const u16 \w+\[\]\s*=\s*\{([^}]+)\}', source):
        forms = re.findall(r'SPECIES_\w+', body)
        if forms and forms[0] in species:
            for form in forms:
                bases[form] = species[forms[0]]
    selected = []
    seen = set()
    for mon in species.values():
        base = bases.get(mon.name, mon)
        if mon.evolves or (mon.name != base.name and mon.types == base.types):
            continue
        key = (mon.dex, mon.types)
        if key not in seen:
            seen.add(key)
            selected.append(mon)
    if not selected:
        raise ValueError('No eligible fully evolved species')
    return selected


def load_chart() -> tuple[list[str], dict[str, dict[str, float]]]:
    source = preprocess('#include "' + str(ROOT / 'src/data/types_info.h') + '"')
    enum = re.search(r'enum\s+__attribute__\(\(packed\)\)\s+Type\s*\{(.*?)\}', source, re.S)
    if not enum:
        raise ValueError('Type enum not found')
    indices = {name: int(number) for name, number in re.findall(r'(TYPE_\w+)\s*=\s*(\d+)', enum[1])}
    table = re.search(r'gTypeEffectivenessTable[^=]*=\s*\{(.*?)\n\};', source, re.S)
    if not table:
        raise ValueError('Type chart not found')
    # The chart uses numeric UQ_4_12 literals and generation-dependent ternaries.
    body = re.sub(r'UQ_4_12\(([0-9.]+)\)', r'\1', table[1])
    body = re.sub(r'\((\d+)\s*>=\s*(\d+)\s*\?\s*([0-9.]+)\s*:\s*([0-9.]+)\)',
                  lambda m: m[3] if int(m[1]) >= int(m[2]) else m[4], body)
    chart = {}
    for name, row in re.findall(r'\[(TYPE_\w+)\]\s*=\s*\{([^}]+)\}', body):
        values = [float(value.strip()) for value in row.split(',') if value.strip()]
        if len(values) != len(indices):
            raise ValueError(f'Unexpected chart width for {name}')
        chart[name] = {defender: values[index] for defender, index in indices.items()}
    if chart.keys() != indices.keys():
        raise ValueError('Incomplete type chart')
    return [name for name in indices if name not in {'TYPE_NONE', 'TYPE_MYSTERY', 'TYPE_STELLAR'}], chart


def display(types: tuple[str, ...]) -> str:
    return '/'.join(t.removeprefix('TYPE_').title() for t in types)


def rank_walls(attackers: list[Species], types: list[str], chart: dict) -> list[dict]:
    rows = []
    for defense in [(t,) for t in types] + list(combinations(types, 2)):
        counts = Counter(max(prod(chart[attack][d] for d in defense)
                             for attack in mon.types) for mon in attackers)
        row = {'typing': display(defense), 'population': len(attackers)}
        for label, multiplier in [('resisted', 0.5), ('quad_resisted', 0.25), ('immune', 0.0)]:
            row[label] = counts[multiplier]
        row['walled'] = sum(row[label] for label in ('resisted', 'quad_resisted', 'immune'))
        for label in ('resisted', 'quad_resisted', 'immune', 'walled'):
            row[label + '_percent'] = 100 * row[label] / len(attackers)
        rows.append(row)
    return sorted(rows, key=lambda row: (-row['walled'], row['typing']))


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('-o', '--output', type=Path, help='Write report here (default: stdout)')
    parser.add_argument('--format', choices=('markdown', 'csv'), default='markdown')
    parser.add_argument('--species-output', type=Path, help='Also export the counted population as CSV for auditing')
    args = parser.parse_args()
    try:
        attackers = select_attackers(load_species())
        types, chart = load_chart()
        rows = rank_walls(attackers, types, chart)
    except (ValueError, OSError, subprocess.CalledProcessError) as error:
        parser.exit(1, f'Error: {error}\n{getattr(error, "stderr", "")}')
    output = io.StringIO()
    if args.format == 'csv':
        writer = csv.DictWriter(output, fieldnames=list(rows[0]))
        writer.writeheader()
        writer.writerows({k: f'{v:.4f}' if isinstance(v, float) else v for k, v in row.items()} for row in rows)
    else:
        output.write(f'# Defensive typing STAB walls\n\nPopulation: {len(attackers)} fully evolved species/forms; {len(rows)} defensive typings.\n\n')
        output.write('Categories use the strongest available STAB: resisted = ½×, quad-resisted = ¼×, immune = 0×. Counts are disjoint; all percentages use the full population. Type chart only; abilities and battle conditions are ignored.\n\n')
        output.write('Forms (including Megas) count only when their typing differs from the base form, and at most once per National Dex number and distinct typing. Species with evolution entries are excluded.\n\n')
        output.write('Only the 18 conventional types are included.\n\n')
        output.write('| Rank | Typing | Resisted | Quad-resisted | Immune | Total walled |\n| ---: | --- | ---: | ---: | ---: | ---: |\n')
        for index, row in enumerate(rows, 1):
            cells = [f'{row[key]} ({row[key + "_percent"]:.2f}%)' for key in ('resisted', 'quad_resisted', 'immune', 'walled')]
            output.write(f'| {index} | {row["typing"]} | ' + ' | '.join(cells) + ' |\n')
    if args.output:
        args.output.write_text(output.getvalue(), encoding='utf-8')
    else:
        sys.stdout.write(output.getvalue())
    if args.species_output:
        with args.species_output.open('w', newline='', encoding='utf-8') as stream:
            writer = csv.writer(stream)
            writer.writerow(['species', 'national_dex', 'typing', 'mega'])
            writer.writerows((mon.name, mon.dex, display(mon.types), mon.mega) for mon in attackers)
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
