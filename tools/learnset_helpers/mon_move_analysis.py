#!/usr/bin/env python3
"""Analyze a Pokemon's historical moves and type-relative standout moves.

Examples:
    python tools/learnset_helpers/mon_move_analysis.py Bulbasaur
    python tools/learnset_helpers/mon_move_analysis.py "Mr. Mime" --format csv
    python tools/learnset_helpers/mon_move_analysis.py Rotom_Wash --format json

When a move occurs in more than one game, its reported level is the arithmetic
mean of the levels in those games.  The source data lives in porymoves_files
beside this script.
"""

from __future__ import annotations

import argparse
import csv
import difflib
import json
import re
import sys
from collections import defaultdict
from pathlib import Path
from typing import TextIO

try:
    from .type_move_report import (
        DEFAULT_SPECIES_DIR,
        MOVE_CLASSES,
        STANDOUT_THRESHOLDS,
        SpeciesInfo,
        collect_move_pools,
        display_constant,
        evolution_line,
        load_species_info,
        move_frequencies,
        qualified_name,
        standout_moves,
        type_label,
    )
except ImportError:  # Direct script execution.
    from type_move_report import (
        DEFAULT_SPECIES_DIR,
        MOVE_CLASSES,
        STANDOUT_THRESHOLDS,
        SpeciesInfo,
        collect_move_pools,
        display_constant,
        evolution_line,
        load_species_info,
        move_frequencies,
        qualified_name,
        standout_moves,
        type_label,
    )


DEFAULT_DATA_DIR = Path(__file__).resolve().parent / "porymoves_files"


def normalize_name(name: str) -> str:
    """Convert a display name or constant-like name to a comparable key."""
    name = name.strip().upper()
    name = name.replace("♀", "_F").replace("♂", "_M")
    return re.sub(r"[^A-Z0-9]+", "_", name).strip("_")


def display_name(constant: str, prefix: str = "") -> str:
    """Make repository constants reasonably pleasant to read."""
    if prefix and constant.startswith(prefix):
        constant = constant[len(prefix) :]
    return constant.replace("_", " ").title()


def load_learnsets(data_dir: Path) -> tuple[dict[str, dict], list[Path]]:
    files = sorted(data_dir.glob("*.json"))
    if not files:
        raise FileNotFoundError(f"no learnset JSON files found in {data_dir}")

    games: dict[str, dict] = {}
    for path in files:
        with path.open(encoding="utf-8") as source:
            data = json.load(source)
        if not isinstance(data, dict):
            raise ValueError(f"expected a species object in {path}")
        games[path.stem] = data
    return games, files


def resolve_species(query: str, games: dict[str, dict]) -> str:
    species = {name for game in games.values() for name in game}
    normalized = normalize_name(query)
    matches = sorted(name for name in species if normalize_name(name) == normalized)
    if matches:
        return matches[0]

    normalized_species = {normalize_name(name): name for name in species}
    suggestions = difflib.get_close_matches(normalized, normalized_species, n=5, cutoff=0.55)
    hint = ""
    if suggestions:
        hint = "; close matches: " + ", ".join(normalized_species[item] for item in suggestions)
    raise LookupError(f"Pokemon {query!r} was not found{hint}")


def combine_moves(species: str, games: dict[str, dict]) -> list[dict[str, object]]:
    occurrences: dict[str, list[tuple[str, int]]] = defaultdict(list)
    for game_name, game_data in games.items():
        species_data = game_data.get(species)
        if not species_data:
            continue
        for entry in species_data.get("LevelMoves", []):
            occurrences[entry["Move"]].append((game_name, int(entry["Level"])))

    combined = []
    for move, entries in occurrences.items():
        average = sum(level for _, level in entries) / len(entries)
        combined.append(
            {
                "move": move,
                "average_level": average,
                "appearances": len(entries),
                "games": [{"game": game, "level": level} for game, level in entries],
            }
        )
    return sorted(combined, key=lambda item: (item["average_level"], item["move"]))


def build_comparisons(
    species: SpeciesInfo,
    species_info: dict[str, SpeciesInfo],
    pools: dict[str, dict[str, set[str]]],
) -> list[dict[str, object]]:
    """Compare a mon with fully evolved type peers, excluding its line if unevolved."""
    excluded = evolution_line(species.name, species_info) if not species.fully_evolved else set()
    comparisons: list[tuple[str, tuple[str, ...]]] = [
        (display_constant(mon_type), (mon_type,)) for mon_type in species.types
    ]
    if len(species.types) == 2:
        comparisons.append((type_label(species.types), species.types))

    results = []
    for label, types in comparisons:
        exact_dual = len(types) == 2
        cohort = sorted(
            (
                candidate
                for candidate in species_info.values()
                if candidate.fully_evolved
                and candidate.name in pools
                and candidate.name not in excluded
                and (
                    frozenset(candidate.types) == frozenset(types)
                    if exact_dual
                    else types[0] in candidate.types
                )
            ),
            key=lambda candidate: (candidate.display_name, candidate.name),
        )
        if not cohort:
            results.append(
                {
                    "group": label,
                    "cohort_size": 0,
                    "peers": [],
                    "excluded_evolution_line": sorted(excluded),
                    "moves": {},
                }
            )
            continue
        frequencies = move_frequencies(cohort, pools)
        moves = {}
        for move_class in MOVE_CLASSES:
            standout = standout_moves(species, pools, frequencies, move_class, len(cohort))
            moves[move_class] = [
                {
                    "move": move,
                    "learners": frequencies[move_class][move],
                    "cohort_size": len(cohort),
                    "prevalence": frequencies[move_class][move] / len(cohort),
                    "threshold": STANDOUT_THRESHOLDS[move_class],
                }
                for move in standout
            ]
        results.append(
            {
                "group": label,
                "cohort_size": len(cohort),
                "peers": [candidate.name for candidate in cohort],
                "excluded_evolution_line": sorted(excluded),
                "moves": moves,
            }
        )
    return results


def format_level(level: float) -> str:
    return str(int(level)) if level.is_integer() else f"{level:.2f}".rstrip("0")


def analysis_move_list(entries: list[dict[str, object]]) -> str:
    if not entries:
        return "None."
    return ", ".join(
        f"{display_constant(entry['move'], 'MOVE_')} "
        f"({entry['learners']}/{entry['cohort_size']}, {entry['prevalence']:.1%})"
        for entry in entries
    ) + "."


def write_text(
    species: SpeciesInfo,
    moves: list[dict[str, object]],
    comparisons: list[dict[str, object]],
    output: TextIO,
) -> None:
    print(f"Move analysis for {qualified_name(species)} ({type_label(species.types)})", file=output)
    print(file=output)
    print("Combined historical level-up moves", file=output)
    print(f"{'Average level':>13}  {'Move':<28} Games", file=output)
    print(f"{'-' * 13}  {'-' * 28} {'-' * 5}", file=output)
    for item in moves:
        level = format_level(item["average_level"])
        print(
            f"{level:>13}  {display_name(item['move'], 'MOVE_'):<28} {item['appearances']}",
            file=output,
        )
    print(file=output)
    print("Standout move comparisons", file=output)
    if not species.fully_evolved:
        excluded = comparisons[0]["excluded_evolution_line"]
        print(
            "Excluded evolution line: "
            + ", ".join(display_name(name) for name in excluded)
            + ".",
            file=output,
        )
    for comparison in comparisons:
        print(file=output)
        print(f"{comparison['group']} cohort ({comparison['cohort_size']} Pokemon)", file=output)
        if not comparison["cohort_size"]:
            print("  No eligible fully evolved comparison Pokemon.", file=output)
            continue
        for move_class, label in (
            ("level_up", "Level-up (< 1/6)"),
            ("egg", "Egg (< 1/6)"),
            ("total", "Total learnset (< 1/4)"),
        ):
            print(f"  {label}: {analysis_move_list(comparison['moves'][move_class])}", file=output)


def write_csv(
    species: str,
    moves: list[dict[str, object]],
    comparisons: list[dict[str, object]],
    output: TextIO,
) -> None:
    writer = csv.writer(output)
    writer.writerow(["pokemon", "move", "average_level", "appearances", "game_levels"])
    for item in moves:
        game_levels = ";".join(
            f"{entry['game']}:{entry['level']}" for entry in item["games"]
        )
        writer.writerow(
            [species, item["move"], format_level(item["average_level"]), item["appearances"], game_levels]
        )
    writer.writerow([])
    writer.writerow(["comparison", "move_class", "move", "learners", "cohort_size", "prevalence"])
    for comparison in comparisons:
        for move_class, entries in comparison.get("moves", {}).items():
            for entry in entries:
                writer.writerow(
                    [comparison["group"], move_class, entry["move"], entry["learners"],
                     entry["cohort_size"], f"{entry['prevalence']:.6f}"]
                )


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("pokemon", help="Pokemon name, such as Bulbasaur or Mr. Mime")
    parser.add_argument(
        "--format", choices=("text", "json", "csv"), default="text", help="output format"
    )
    parser.add_argument(
        "--data-dir", type=Path, default=DEFAULT_DATA_DIR, help=argparse.SUPPRESS
    )
    parser.add_argument(
        "--species-dir", type=Path, default=DEFAULT_SPECIES_DIR, help=argparse.SUPPRESS
    )
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    try:
        games, _ = load_learnsets(args.data_dir)
        source_species_name = resolve_species(args.pokemon, games)
        species_name = normalize_name(source_species_name)
        species_info = load_species_info(args.species_dir)
        if species_name not in species_info:
            raise LookupError(f"species metadata for {species_name} was not found")
        species = species_info[species_name]
        pools = collect_move_pools(games)
        moves = combine_moves(source_species_name, games)
        comparisons = build_comparisons(species, species_info, pools)
    except (FileNotFoundError, json.JSONDecodeError, LookupError, ValueError) as error:
        print(f"error: {error}", file=sys.stderr)
        return 1

    if args.format == "json":
        json.dump(
            {
                "pokemon": species.name,
                "display_name": qualified_name(species),
                "types": species.types,
                "fully_evolved": species.fully_evolved,
                "level_up_moves": moves,
                "standout_comparisons": comparisons,
            },
            sys.stdout,
            indent=2,
        )
        print()
    elif args.format == "csv":
        write_csv(species.name, moves, comparisons, sys.stdout)
    else:
        write_text(species, moves, comparisons, sys.stdout)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
