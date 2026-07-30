#!/usr/bin/env python3
"""Rank moves by fully evolved, off-type teachable learners.

Learnsets are unioned across every bundled PoryMoves JSON file.  A Pokemon is
counted for a move when:

* it is fully evolved and does not share the move's type;
* the move occurs in its TM or tutor learnset in at least one game; and
* the move occurs in neither its level-up nor egg learnset in any game.

By default the Markdown report is written beside this script as
tools/learnset_helpers/off_type_moves.md.
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path

from type_move_report import (
    DEFAULT_DATA_DIR,
    DEFAULT_SPECIES_DIR,
    display_constant,
    iter_initializer_blocks,
    load_game_data,
    load_species_info,
    normalize_constant,
)


SCRIPT_DIR = Path(__file__).resolve().parent
REPO_ROOT = SCRIPT_DIR.parents[1]
DEFAULT_MOVES_FILE = REPO_ROOT / "src" / "data" / "moves_info.h"
DEFAULT_OUTPUT = SCRIPT_DIR / "off_type_moves.md"

tmExclusionHelper = [
    "Facade", #Tutor
    "Substitute", #Setup tutor
    "Giga Impact", #Tech tutor
    "Hyper Beam", #Tech tutor
    "Round", #Tutor (and later Tech tutor)
    "Protect", #Setup tutor
    "Endure", #Definitive tutor
    "Toxic", #Exclusive
    "Frustration", #Exclusive
    "Hidden Power", #Exclusive
    "Sunny Day", #Setup tutor
    "Attract", #Tech tutor
    "Swagger", #Exclusive
    "Rain Dance", #Setup tutor
    "Double Team", #Setup tutor
    "Fling", #Exclusive
    "Swift", #Tutor (and later tech tutor)
    "Take Down", #tutor
    "Mud-Slap", #Tech tutor
    "Strength", #Tutor
    "Mimic", #Setup tutor
    "Captivate", #Tech Tutor
    "Psych Up", #Setup tutor
    "Confide", #Tech Tutor
    "Trailblaze", #Tech Tutor
    "Aerial Ace", #Tutor (and later Tech Tutor)
    "Laser Focus", #Tech Tutor
    "Shock Wave", #Tutor (and later Tech Tutor)
    "Headbutt", #Tutor (Easy to distribute by level-up to whoever needs it)
    "Body Press", #Tutor (Easy to distribute by level-up to whoever needs it)
    "Taunt", #Setup Tutor
    "Mega Kick", #Tutor (Easy to distribute by level-up to whoever needs it)
    "Uproar", #Tech Tutor
    "Mega Punch", #Tutor (Easy to distribute by level-up to whoever needs it)
    "Incinerate", #Tutor (and later Tech Tutor)
    "Thief", #Tutor (and later Tech Tutor)
    "Sleep Talk", #Tech Tutor
    "Snore", #Tech Tutor
    "Natural Gift", #Tutor
    "Dig", #Tutor (Easy to distribute by level-up to whoever needs it)
    "Focus Blast", #Tutor and Accuracy Tutor
    "Iron Tail", #Tutor and Accuracy Tutor
    "Stone Edge", #Tutor and Accuracy Tutor
    "Blizzard", #Tutor and Accuracy Tutor
    "Thunder", #Tutor and Accuracy Tutor
    "Fire Blast", #Tutor and Accuracy Tutor
    "Hydro Pump", #Tutor and Accuracy Tutor
    "Gunk Shot", #Tutor and Accuracy Tutor
    "Power Whip", #Tutor and Accuracy Tutor
    "Zap Cannon", #Tutor and Accuracy Tutor
    "Inferno", #Tutor and Accuracy Tutor
    "Cross Chop", #Tutor and Accuracy Tutor
    "Dynamic Punch", #Tutor and Accuracy Tutor
]

@dataclass(frozen=True)
class MoveInfo:
    name: str
    display_name: str
    type: str


def first_constant(body: str, field: str, prefix: str) -> str | None:
    """Return the first matching constant in a designated initializer field."""
    match = re.search(rf"\.{field}\s*=\s*([^,\n]+)", body)
    if not match:
        return None
    constant = re.search(rf"\b{prefix}([A-Z0-9_]+)\b", match.group(1))
    return constant.group(1) if constant else None


def load_moves(path: Path) -> dict[str, MoveInfo]:
    content = path.read_text(encoding="utf-8")
    moves: dict[str, MoveInfo] = {}
    # Reuse the balanced-brace parser used for species initializers by adapting
    # only move array designators to the token it recognizes.
    for move, body in iter_initializer_blocks(content.replace("[MOVE_", "[SPECIES_")):
        move_type = first_constant(body, "type", "TYPE_")
        if not move_type:
            continue
        name_match = re.search(
            r'\.name\s*=\s*(?:COMPOUND_STRING|_)\("([^"]+)"\)', body
        )
        moves[f"MOVE_{move}"] = MoveInfo(
            name=f"MOVE_{move}",
            display_name=(
                name_match.group(1)
                if name_match
                else display_constant(move)
            ),
            type=move_type,
        )
    return moves


def collect_method_pools(games: dict[str, dict]) -> dict[str, dict[str, set[str]]]:
    pools: dict[str, dict[str, set[str]]] = defaultdict(
        lambda: {"teachable": set(), "level_up": set(), "egg": set()}
    )
    method_map = {
        "teachable": ("TMMoves", "TutorMoves"),
        "level_up": ("LevelMoves",),
        "egg": ("EggMoves",),
    }
    for game in games.values():
        for raw_species, learnset in game.items():
            species = normalize_constant(raw_species)
            for method, keys in method_map.items():
                for key in keys:
                    for entry in learnset.get(key, []):
                        move = entry["Move"] if isinstance(entry, dict) else entry
                        if move != "MOVE_UNAVAILABLE":
                            pools[species][method].add(move)
    return pools


def count_learners(
    moves: dict[str, MoveInfo],
    species_info,
    pools: dict[str, dict[str, set[str]]],
) -> tuple[dict[str, list[str]], dict[str, list[str]]]:
    teachable_learners: dict[str, list[str]] = {move: [] for move in moves}
    level_up_learners: dict[str, list[str]] = {move: [] for move in moves}
    for species_name, methods in pools.items():
        species = species_info.get(species_name)
        if not species or not species.fully_evolved:
            continue
        exclusively_teachable = (
            methods["teachable"] - methods["level_up"] - methods["egg"]
        )
        for move in (exclusively_teachable | methods["level_up"]) & moves.keys():
            if moves[move].type not in species.types:
                if move in exclusively_teachable:
                    teachable_learners[move].append(species.display_name)
                if move in methods["level_up"]:
                    level_up_learners[move].append(species.display_name)
    return teachable_learners, level_up_learners


def build_report(
    moves: dict[str, MoveInfo],
    teachable_learners: dict[str, list[str]],
    level_up_learners: dict[str, list[str]],
    game_count: int,
) -> str:
    ordered = sorted(
        (move for move in moves.values() if teachable_learners[move.name]),
        key=lambda move: (
            -(
                len(teachable_learners[move.name])
                - len(level_up_learners[move.name])
            ),
            move.display_name,
            move.name,
        ),
    )
    excluded_names = set(tmExclusionHelper)
    tm_candidates = [move for move in ordered if move.display_name not in excluded_names]
    excluded_moves = [move for move in ordered if move.display_name in excluded_names]

    def table(move_group: list[MoveInfo]) -> list[str]:
        lines = [
            "| Move | Type | Teachable | Level-up | Difference |",
            "|---|---|---:|---:|---:|",
        ]
        lines.extend(
            f"| {move.display_name} | {display_constant(move.type)} | "
            f"{len(teachable_learners[move.name])} | "
            f"{len(level_up_learners[move.name])} | "
            f"{len(teachable_learners[move.name]) - len(level_up_learners[move.name])} |"
            for move in move_group
        )
        return lines

    lines = [
        "# Off-type teachable move counts",
        "",
        f"Learnsets are deduplicated unions across {game_count} PoryMoves datasets.",
        "",
        "## TM priority candidates",
        "",
        "Moves listed in `tmExclusionHelper` are omitted from this section.",
        "",
    ]
    lines.extend(table(tm_candidates))
    lines.extend(
        [
            "",
            "## Excluded from TM consideration",
            "",
            "This section contains only moves listed in `tmExclusionHelper`.",
            "",
        ]
    )
    lines.extend(table(excluded_moves))
    return "\n".join(lines) + "\n"


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        default=DEFAULT_OUTPUT,
        help="output path (default: tools/learnset_helpers/off_type_moves.md)",
    )
    parser.add_argument("--data-dir", type=Path, default=DEFAULT_DATA_DIR)
    parser.add_argument("--species-dir", type=Path, default=DEFAULT_SPECIES_DIR)
    parser.add_argument("--moves-file", type=Path, default=DEFAULT_MOVES_FILE)
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    try:
        games = load_game_data(args.data_dir)
        species_info = load_species_info(args.species_dir)
        moves = load_moves(args.moves_file)
        pools = collect_method_pools(games)
        teachable_learners, level_up_learners = count_learners(
            moves, species_info, pools
        )
        report = build_report(
            moves, teachable_learners, level_up_learners, len(games)
        )
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(report, encoding="utf-8")
        displayed_count = sum(
            bool(move_learners) for move_learners in teachable_learners.values()
        )
        print(f"Wrote {args.output} ({displayed_count} moves).")
    except (FileNotFoundError, json.JSONDecodeError, OSError, ValueError) as error:
        print(f"error: {error}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
