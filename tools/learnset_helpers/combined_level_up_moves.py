#!/usr/bin/env python3
"""Combine a Pokemon's level-up learnsets from every bundled game.

Examples:
    python tools/learnset_helpers/combined_level_up_moves.py Bulbasaur
    python tools/learnset_helpers/combined_level_up_moves.py "Mr. Mime" --format csv
    python tools/learnset_helpers/combined_level_up_moves.py Rotom_Wash --format json

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


def format_level(level: float) -> str:
    return str(int(level)) if level.is_integer() else f"{level:.2f}".rstrip("0")


def write_text(species: str, moves: list[dict[str, object]], output: TextIO) -> None:
    print(f"Combined level-up moves for {display_name(species)}", file=output)
    print(f"{'Average level':>13}  {'Move':<28} Games", file=output)
    print(f"{'-' * 13}  {'-' * 28} {'-' * 5}", file=output)
    for item in moves:
        level = format_level(item["average_level"])
        print(
            f"{level:>13}  {display_name(item['move'], 'MOVE_'):<28} {item['appearances']}",
            file=output,
        )


def write_csv(species: str, moves: list[dict[str, object]], output: TextIO) -> None:
    writer = csv.writer(output)
    writer.writerow(["pokemon", "move", "average_level", "appearances", "game_levels"])
    for item in moves:
        game_levels = ";".join(
            f"{entry['game']}:{entry['level']}" for entry in item["games"]
        )
        writer.writerow(
            [species, item["move"], format_level(item["average_level"]), item["appearances"], game_levels]
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
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    try:
        games, _ = load_learnsets(args.data_dir)
        species = resolve_species(args.pokemon, games)
        moves = combine_moves(species, games)
    except (FileNotFoundError, json.JSONDecodeError, LookupError, ValueError) as error:
        print(f"error: {error}", file=sys.stderr)
        return 1

    if args.format == "json":
        json.dump({"pokemon": species, "moves": moves}, sys.stdout, indent=2)
        print()
    elif args.format == "csv":
        write_csv(species, moves, sys.stdout)
    else:
        write_text(species, moves, sys.stdout)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
