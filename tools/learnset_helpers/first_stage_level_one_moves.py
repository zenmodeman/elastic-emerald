#!/usr/bin/env python3
"""Find suspiciously advanced level-1 moves on first-stage Pokemon.

A move's usual positive learn level across all bundled PoryMoves data is used
as an explainable proxy for its calibre. Level-0 evolution moves are ignored.
"""

from __future__ import annotations

import argparse
import json
import statistics
import sys
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path

from type_move_report import DEFAULT_SPECIES_DIR, display_constant, load_species_info, normalize_constant

SCRIPT_DIR = Path(__file__).resolve().parent
DEFAULT_DATA_DIR = SCRIPT_DIR / "porymoves_files"


@dataclass(frozen=True)
class Occurrence:
    game: str
    species: str
    level: int


@dataclass(frozen=True)
class Finding:
    display_name: str
    move: str
    level_one_games: tuple[str, ...]
    same_species_later: tuple[Occurrence, ...]
    comparison_levels: tuple[int, ...]
    comparison_species: int

    @property
    def typical_level(self) -> float:
        levels = self.comparison_levels or tuple(item.level for item in self.same_species_later)
        return statistics.median(levels)

    @property
    def maximum_level(self) -> int:
        levels = self.comparison_levels + tuple(item.level for item in self.same_species_later)
        return max(levels)


def load_occurrences(data_dir: Path) -> tuple[dict[str, dict[str, list[Occurrence]]], list[Path]]:
    paths = sorted(data_dir.glob("*.json"))
    if not paths:
        raise FileNotFoundError(f"no PoryMoves JSON files found in {data_dir}")
    occurrences: dict[str, dict[str, list[Occurrence]]] = defaultdict(lambda: defaultdict(list))
    for path in paths:
        with path.open(encoding="utf-8") as source:
            data = json.load(source)
        if not isinstance(data, dict):
            raise ValueError(f"expected a species object in {path}")
        for raw_species, learnset in data.items():
            species = normalize_constant(raw_species)
            for entry in learnset.get("LevelMoves", []):
                move = entry.get("Move")
                if not move or move == "MOVE_UNAVAILABLE":
                    continue
                try:
                    level = int(entry["Level"])
                except (KeyError, TypeError, ValueError) as error:
                    raise ValueError(f"invalid level move for {raw_species} in {path}") from error
                if level > 0:
                    occurrences[move][species].append(Occurrence(path.stem, species, level))
    return occurrences, paths


def first_stage_species(species_info) -> set[str]:
    """Return species that evolve and are not an evolution target themselves."""
    targets = {
        target
        for info in species_info.values()
        for target in info.evolutions
        if target in species_info
    }
    return {
        species
        for species, info in species_info.items()
        if info.evolutions and species not in targets
    }


def find_suspicious_moves(occurrences, species_info, min_typical_level, min_late_level, min_comparisons):
    findings = []
    for species in sorted(first_stage_species(species_info)):
        for move, by_species in occurrences.items():
            own = by_species.get(species, [])
            level_one_games = tuple(sorted({item.game for item in own if item.level == 1}))
            if not level_one_games:
                continue
            same_species_later = tuple(sorted(
                (item for item in own if item.level >= min_late_level),
                key=lambda item: (item.level, item.game),
            ))
            comparisons = [
                item
                for other_species, entries in by_species.items()
                if other_species != species
                for item in entries
                if item.level > 1
            ]
            comparison_levels = tuple(item.level for item in comparisons)
            typical_is_late = (
                len(comparison_levels) >= min_comparisons
                and statistics.median(comparison_levels) >= min_typical_level
                and max(comparison_levels) >= min_late_level
            )
            if not same_species_later and not typical_is_late:
                continue
            findings.append(Finding(
                display_name=species_info[species].display_name,
                move=move,
                level_one_games=level_one_games,
                same_species_later=same_species_later,
                comparison_levels=comparison_levels,
                comparison_species=len({item.species for item in comparisons}),
            ))
    return sorted(findings, key=lambda item: (
        -item.typical_level, -item.maximum_level, item.display_name, item.move
    ))


def format_number(value: float) -> str:
    return str(int(value)) if float(value).is_integer() else f"{value:.1f}"


def render_report(findings, file_count, args):
    lines = [
        "# Suspicious first-stage level-1 moves",
        "",
        f"Scanned {file_count} PoryMoves JSON files. Candidates are Pokémon that can evolve and have no pre-evolution. A level-1 move is flagged when at least {args.min_comparisons} records for other Pokémon have a median learn level of {args.min_typical_level}+ and one reaches level {args.min_late_level}+, or when the same Pokémon learns it at level {args.min_late_level}+ in another game. Level-0 evolution moves are ignored.",
        "",
        "| Pokémon | Move | Level-1 games | Typical comparison level | Evidence |",
        "|---|---|---|---:|---|",
    ]
    for finding in findings:
        later = ""
        if finding.same_species_later:
            occurrences = ", ".join(
                f"{item.game} Lv.{item.level}" for item in finding.same_species_later
            )
            later = f"; same Pokémon later: {occurrences}"
        evidence = (
            f"{len(finding.comparison_levels)} records across "
            f"{finding.comparison_species} other species; max Lv.{finding.maximum_level}{later}"
        )
        lines.append("| " + " | ".join((
            finding.display_name,
            display_constant(finding.move, "MOVE_"),
            ", ".join(finding.level_one_games),
            format_number(finding.typical_level),
            evidence,
        )) + " |")
    if not findings:
        lines.append("| _No matches_ | | | | |")
    lines.extend(("", f"Total candidates: {len(findings)}", ""))
    return "\n".join(lines)


def parse_args():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--data-dir", type=Path, default=DEFAULT_DATA_DIR)
    parser.add_argument("--species-dir", type=Path, default=DEFAULT_SPECIES_DIR)
    parser.add_argument("-o", "--output", type=Path, help="write Markdown here instead of stdout")
    parser.add_argument("--min-typical-level", type=int, default=25)
    parser.add_argument("--min-late-level", type=int, default=30)
    parser.add_argument("--min-comparisons", type=int, default=2)
    args = parser.parse_args()
    if min(args.min_typical_level, args.min_late_level, args.min_comparisons) < 1:
        parser.error("thresholds must be positive integers")
    return args


def main() -> int:
    args = parse_args()
    try:
        species_info = load_species_info(args.species_dir)
        occurrences, paths = load_occurrences(args.data_dir)
        findings = find_suspicious_moves(
            occurrences, species_info, args.min_typical_level,
            args.min_late_level, args.min_comparisons,
        )
        report = render_report(findings, len(paths), args)
        if args.output:
            args.output.parent.mkdir(parents=True, exist_ok=True)
            args.output.write_text(report, encoding="utf-8")
            print(f"Wrote {len(findings)} candidates to {args.output}")
        else:
            print(report, end="")
    except (FileNotFoundError, OSError, ValueError) as error:
        print(f"error: {error}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
