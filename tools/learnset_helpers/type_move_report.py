#!/usr/bin/env python3
"""Generate a Markdown move report for fully evolved Pokemon of one type.

Standout moves fall below the configured prevalence threshold in the relevant
comparison group. Move pools are unions across all bundled porymoves game data.

Examples:
python3 tools/learnset_helpers/type_move_report.py Fire
python3 tools/learnset_helpers/type_move_report.py TYPE_WATER -o docs/water_move_report.md
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from collections import Counter
from dataclasses import dataclass
from pathlib import Path


SCRIPT_DIR = Path(__file__).resolve().parent
REPO_ROOT = SCRIPT_DIR.parents[1]
DEFAULT_DATA_DIR = SCRIPT_DIR / "porymoves_files"
DEFAULT_SPECIES_DIR = REPO_ROOT / "src" / "data" / "pokemon" / "species_info"
MOVE_CLASSES = ("level_up", "egg", "total")
STANDOUT_THRESHOLDS = {"level_up": 1 / 6, "egg": 1 / 6, "total": 1 / 4}
METHOD_KEYS = {
    "level_up": ("LevelMoves",),
    "egg": ("EggMoves",),
    "total": ("LevelMoves", "PreEvoMoves", "TMMoves", "EggMoves", "TutorMoves"),
}


@dataclass(frozen=True)
class SpeciesInfo:
    name: str
    display_name: str
    types: tuple[str, ...]
    fully_evolved: bool
    evolutions: tuple[str, ...]


def normalize_constant(value: str, prefix: str = "") -> str:
    value = value.strip().upper()
    if prefix and value.startswith(prefix):
        value = value[len(prefix) :]
    return re.sub(r"[^A-Z0-9]+", "_", value).strip("_")


def display_constant(value: str, prefix: str = "") -> str:
    if prefix and value.startswith(prefix):
        value = value[len(prefix) :]
    return value.replace("_", " ").title()


def iter_initializer_blocks(content: str):
    """Yield (species constant, initializer body) from a species-info header."""
    header = re.compile(r"\[SPECIES_([A-Z0-9_]+)\]\s*=\s*\{")
    for match in header.finditer(content):
        depth = 1
        position = match.end()
        while position < len(content) and depth:
            if content[position] == "{":
                depth += 1
            elif content[position] == "}":
                depth -= 1
            position += 1
        if depth:
            raise ValueError(f"unterminated species initializer for {match.group(1)}")
        yield match.group(1), content[match.end() : position - 1]


def extract_evolutions(body: str) -> tuple[str, ...]:
    """Extract target species only from the EVOLUTION(...) field."""
    match = re.search(r"\.evolutions\s*=\s*EVOLUTION\(", body)
    if not match:
        return ()
    depth = 1
    position = match.end()
    while position < len(body) and depth:
        if body[position] == "(":
            depth += 1
        elif body[position] == ")":
            depth -= 1
        position += 1
    if depth:
        raise ValueError("unterminated EVOLUTION expression")
    return tuple(
        dict.fromkeys(re.findall(r"\bSPECIES_([A-Z0-9_]+)\b", body[match.end() : position - 1]))
    )


def load_species_info(species_dir: Path) -> dict[str, SpeciesInfo]:
    paths = sorted(species_dir.glob("gen_*_families.h"))
    if not paths:
        raise FileNotFoundError(f"no species-info headers found in {species_dir}")
    result: dict[str, SpeciesInfo] = {}
    type_pattern = re.compile(r"\.types\s*=\s*MON_TYPES\(([^)]*)\)")
    name_pattern = re.compile(r'\.speciesName\s*=\s*_\("([^"]+)"\)')
    for path in paths:
        content = path.read_text(encoding="utf-8")
        type_aliases = {
            name: type_name
            for name, type_name in re.findall(
                r"^\s*#define\s+([A-Z0-9_]+)\s+[^\n]*?\b(TYPE_[A-Z0-9_]+)\b",
                content,
                re.MULTILINE,
            )
        }
        for species, body in iter_initializer_blocks(content):
            type_match = type_pattern.search(body)
            if not type_match:
                continue
            raw_types = (item.strip() for item in type_match.group(1).split(","))
            types = tuple(
                normalize_constant(type_aliases.get(item, item), "TYPE_")
                for item in raw_types
                if item
            )
            types = tuple(dict.fromkeys(types))
            name_match = name_pattern.search(body)
            evolutions = extract_evolutions(body)
            result[species] = SpeciesInfo(
                name=species,
                display_name=name_match.group(1) if name_match else display_constant(species),
                types=types,
                fully_evolved=".evolutions" not in body,
                evolutions=evolutions,
            )
    return result


def evolution_line(species: str, species_info: dict[str, SpeciesInfo]) -> set[str]:
    """Return the connected evolution family containing species."""
    neighbors: dict[str, set[str]] = {name: set() for name in species_info}
    for name, info in species_info.items():
        for evolved in info.evolutions:
            if evolved in neighbors:
                neighbors[name].add(evolved)
                neighbors[evolved].add(name)
    family = {species}
    pending = [species]
    while pending:
        current = pending.pop()
        for relative in neighbors.get(current, set()) - family:
            family.add(relative)
            pending.append(relative)
    return family


def load_game_data(data_dir: Path) -> dict[str, dict]:
    paths = sorted(data_dir.glob("*.json"))
    if not paths:
        raise FileNotFoundError(f"no learnset JSON files found in {data_dir}")
    games = {}
    for path in paths:
        with path.open(encoding="utf-8") as source:
            data = json.load(source)
        if not isinstance(data, dict):
            raise ValueError(f"expected a species object in {path}")
        games[path.stem] = data
    return games


def collect_move_pools(games: dict[str, dict]) -> dict[str, dict[str, set[str]]]:
    """Union each species' moves across games, deduplicated by move constant."""
    species_names = {normalize_constant(species) for game in games.values() for species in game}
    pools = {species: {kind: set() for kind in MOVE_CLASSES} for species in species_names}
    for game in games.values():
        for source_species, learnset in game.items():
            species = normalize_constant(source_species)
            for move_class, keys in METHOD_KEYS.items():
                for key in keys:
                    for entry in learnset.get(key, []):
                        move = entry["Move"] if isinstance(entry, dict) else entry
                        if move != "MOVE_UNAVAILABLE":
                            pools[species][move_class].add(move)
    return pools


def move_frequencies(
    cohort: list[SpeciesInfo], pools: dict[str, dict[str, set[str]]]
) -> dict[str, Counter]:
    return {
        kind: Counter(move for species in cohort for move in pools[species.name][kind])
        for kind in MOVE_CLASSES
    }


def standout_moves(
    species: SpeciesInfo,
    pools: dict[str, dict[str, set[str]]],
    frequencies: dict[str, Counter],
    move_class: str,
    cohort_size: int,
) -> list[str]:
    return sorted(
        (
            move
            for move in pools[species.name][move_class]
            if frequencies[move_class][move] / cohort_size < STANDOUT_THRESHOLDS[move_class]
        ),
        key=lambda move: display_constant(move, "MOVE_"),
    )


def move_list(moves: list[str], frequencies: Counter, cohort_size: int) -> str:
    if not moves:
        return "None."
    return ", ".join(
        f"`{display_constant(move, 'MOVE_')}` ({frequencies[move]}/{cohort_size}, "
        f"{frequencies[move] / cohort_size:.1%})"
        for move in moves
    ) + "."


def complete_move_list(moves: set[str]) -> str:
    """Format a species' complete deduplicated historical move pool."""
    ordered = sorted(moves, key=lambda move: display_constant(move, "MOVE_"))
    return ", ".join(f"`{display_constant(move, 'MOVE_')}`" for move in ordered) + "."


def qualified_name(species: SpeciesInfo) -> str:
    """Distinguish forms whose in-game display names are identical."""
    display_key = normalize_constant(species.display_name)
    if species.name.startswith(display_key + "_"):
        form = display_constant(species.name[len(display_key) + 1 :])
        return f"{species.display_name} ({form})"
    return species.display_name


def type_label(types: tuple[str, ...]) -> str:
    return "/".join(display_constant(mon_type) for mon_type in types)


def build_report(
    requested_type: str,
    cohort: list[SpeciesInfo],
    pools: dict[str, dict[str, set[str]]],
    game_names: list[str],
) -> str:
    frequencies = move_frequencies(cohort, pools)
    dual_cohorts: dict[frozenset[str], list[SpeciesInfo]] = {}
    for species in cohort:
        if len(species.types) == 2:
            dual_cohorts.setdefault(frozenset(species.types), []).append(species)
    dual_frequencies = {
        types: move_frequencies(members, pools)
        for types, members in dual_cohorts.items()
        if len(members) > 1
    }
    type_name = display_constant(requested_type)
    lines = [
        f"# Fully evolved {type_name}-type move report",
        "",
        f"This report covers **{len(cohort)}** fully evolved Pokémon with the {type_name} "
        f"type. Learnsets are deduplicated unions across **{len(game_names)}** bundled game "
        f"datasets: {', '.join(game_names)}.",
        "",
        "A **standout** level-up or egg move is available to strictly fewer than one-sixth "
        "of the Pokémon in its comparison group. For the broader total learnset, the "
        "threshold is strictly fewer than one-quarter. Each result shows learner count, "
        "cohort size, and percentage. Total learnsets include level-up, pre-evolution, egg, "
        "TM/HM, and tutor moves. Fully evolved means the repository species entry has no "
        "further evolution.",
        "",
        "## Overview",
        "",
        "| Pokémon | Type | Level-up moves | Egg moves | Total moves |",
        "|---|---|---:|---:|---:|",
    ]
    for species in cohort:
        species_pools = pools[species.name]
        lines.append(
            f"| {qualified_name(species)} | {type_label(species.types)} | "
            f"{len(species_pools['level_up'])} | {len(species_pools['egg'])} | "
            f"{len(species_pools['total'])} |"
        )

    for species in cohort:
        lines.extend(
            [
                "",
                f"## {qualified_name(species)}",
                "",
                f"**Type:** {type_label(species.types)}  ",
                f"**Unique historical moveset size:** {len(pools[species.name]['total'])}",
                "",
                "### Complete unique historical moveset",
                "",
                complete_move_list(pools[species.name]["total"]),
                "",
                f"### Standout level-up moves among {type_name} types",
                "",
                move_list(
                    standout_moves(species, pools, frequencies, "level_up", len(cohort)),
                    frequencies["level_up"],
                    len(cohort),
                ),
                "",
                f"### Standout egg moves among {type_name} types",
                "",
                move_list(
                    standout_moves(species, pools, frequencies, "egg", len(cohort)),
                    frequencies["egg"],
                    len(cohort),
                ),
                "",
                f"### Standout total-learnset moves among {type_name} types",
                "",
                move_list(
                    standout_moves(species, pools, frequencies, "total", len(cohort)),
                    frequencies["total"],
                    len(cohort),
                ),
            ]
        )
        if len(species.types) == 2:
            type_key = frozenset(species.types)
            peers = dual_cohorts[type_key]
            lines.extend(["", f"### Comparison within fully evolved {type_label(species.types)} types", ""])
            if len(peers) == 1:
                lines.append("No other fully evolved Pokémon with this exact dual type exists in the dataset.")
            else:
                peer_names = ", ".join(qualified_name(peer) for peer in peers if peer != species)
                pair_frequencies = dual_frequencies[type_key]
                lines.extend(
                    [
                        f"Compared with: {peer_names}.",
                        "",
                        "- **Standout level-up moves:** "
                        + move_list(
                            standout_moves(
                                species, pools, pair_frequencies, "level_up", len(peers)
                            ),
                            pair_frequencies["level_up"],
                            len(peers),
                        ),
                        "- **Standout egg moves:** "
                        + move_list(
                            standout_moves(species, pools, pair_frequencies, "egg", len(peers)),
                            pair_frequencies["egg"],
                            len(peers),
                        ),
                        "- **Standout total-learnset moves:** "
                        + move_list(
                            standout_moves(species, pools, pair_frequencies, "total", len(peers)),
                            pair_frequencies["total"],
                            len(peers),
                        ),
                    ]
                )
    return "\n".join(lines) + "\n"


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("type", help="Pokemon type, such as Fire or TYPE_FIRE")
    parser.add_argument(
        "-o", "--output", type=Path,
        help="output .md path (default: TYPE_fully_evolved_move_report.md)",
    )
    parser.add_argument("--data-dir", type=Path, default=DEFAULT_DATA_DIR, help=argparse.SUPPRESS)
    parser.add_argument("--species-dir", type=Path, default=DEFAULT_SPECIES_DIR, help=argparse.SUPPRESS)
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    requested_type = normalize_constant(args.type, "TYPE_")
    output = args.output or Path(f"{requested_type.lower()}_fully_evolved_move_report.md")
    if output.suffix.lower() != ".md":
        print("error: output path must end in .md", file=sys.stderr)
        return 2
    try:
        species_info = load_species_info(args.species_dir)
        games = load_game_data(args.data_dir)
        pools = collect_move_pools(games)
        known_types = {mon_type for species in species_info.values() for mon_type in species.types}
        if requested_type not in known_types:
            choices = ", ".join(sorted(display_constant(mon_type) for mon_type in known_types))
            raise ValueError(f"unknown Pokemon type {args.type!r}; choose from: {choices}")
        cohort = sorted(
            (species for species in species_info.values()
             if species.fully_evolved and requested_type in species.types and species.name in pools),
            key=lambda species: (species.display_name, species.name),
        )
        if not cohort:
            raise ValueError(f"no fully evolved {display_constant(requested_type)} types found")
        report = build_report(requested_type, cohort, pools, sorted(games))
        output.parent.mkdir(parents=True, exist_ok=True)
        output.write_text(report, encoding="utf-8")
    except (FileNotFoundError, json.JSONDecodeError, OSError, ValueError) as error:
        print(f"error: {error}", file=sys.stderr)
        return 1
    print(f"Wrote {output} ({len(cohort)} Pokemon).")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
