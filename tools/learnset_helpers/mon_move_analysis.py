#!/usr/bin/env python3
"""Analyze a Pokemon's historical moves and type-relative standout moves.

Examples:
    python tools/learnset_helpers/mon_move_analysis.py Bulbasaur
    python tools/learnset_helpers/mon_move_analysis.py "Mr. Mime" -o mr_mime.md
    python tools/learnset_helpers/mon_move_analysis.py Rotom_Wash

When a move occurs in more than one game, its reported level is the arithmetic
mean of the levels in those games.  The source data lives in porymoves_files
beside this script.
"""

from __future__ import annotations

import argparse
import difflib
import json
import re
import sys
from collections import defaultdict
from io import StringIO
from pathlib import Path

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
DEFAULT_OUTPUT = Path("move_analysis_output_instance.md")


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
        levels = [level for _, level in entries]
        average = sum(levels) / len(levels)
        combined.append(
            {
                "move": move,
                "average_level": average,
                "minimum_level": min(levels),
                "maximum_level": max(levels),
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


def evolution_relatives(
    species: str, species_info: dict[str, SpeciesInfo]
) -> tuple[set[str], set[str]]:
    """Return all ancestors and descendants without including sibling branches."""
    children = {name: set(info.evolutions) & species_info.keys() for name, info in species_info.items()}
    parents: dict[str, set[str]] = {name: set() for name in species_info}
    for parent, evolved_forms in children.items():
        for evolved in evolved_forms:
            parents[evolved].add(parent)

    def transitive(start: str, graph: dict[str, set[str]]) -> set[str]:
        found: set[str] = set()
        pending = list(graph.get(start, set()))
        while pending:
            relative = pending.pop()
            if relative not in found:
                found.add(relative)
                pending.extend(graph.get(relative, set()) - found)
        return found

    return transitive(species, parents), transitive(species, children)


def delta_entries(moves_to_relatives: dict[str, set[str]]) -> list[dict[str, object]]:
    return [
        {"move": move, "relatives": sorted(relatives)}
        for move, relatives in sorted(
            moves_to_relatives.items(), key=lambda item: display_constant(item[0], "MOVE_")
        )
    ]


def build_evolution_deltas(
    species: SpeciesInfo,
    species_info: dict[str, SpeciesInfo],
    pools: dict[str, dict[str, set[str]]],
) -> dict[str, object]:
    """Aggregate move differences against every ancestor and descendant once per move."""
    ancestors, descendants = evolution_relatives(species.name, species_info)
    ancestors &= pools.keys()
    descendants &= pools.keys()
    classes: dict[str, dict[str, list[dict[str, object]]]] = {}
    for move_class in MOVE_CLASSES:
        target_moves = pools[species.name][move_class]
        evolution_only: dict[str, set[str]] = defaultdict(set)
        missing_from_evolutions: dict[str, set[str]] = defaultdict(set)
        pre_evolution_only: dict[str, set[str]] = defaultdict(set)
        new_since_pre_evolutions: dict[str, set[str]] = defaultdict(set)
        for relative in descendants:
            relative_moves = pools[relative][move_class]
            for move in relative_moves - target_moves:
                evolution_only[move].add(relative)
            for move in target_moves - relative_moves:
                missing_from_evolutions[move].add(relative)
        for relative in ancestors:
            relative_moves = pools[relative][move_class]
            for move in relative_moves - target_moves:
                pre_evolution_only[move].add(relative)
            for move in target_moves - relative_moves:
                new_since_pre_evolutions[move].add(relative)
        classes[move_class] = {
            "evolution_only": delta_entries(evolution_only),
            "missing_from_evolutions": delta_entries(missing_from_evolutions),
            "pre_evolution_only": delta_entries(pre_evolution_only),
            "new_since_pre_evolutions": delta_entries(new_since_pre_evolutions),
        }
    return {
        "pre_evolutions": sorted(ancestors),
        "evolutions": sorted(descendants),
        "move_classes": classes,
    }


def build_evolution_moves(
    species: SpeciesInfo,
    species_info: dict[str, SpeciesInfo],
    games: dict[str, dict],
) -> list[dict[str, object]]:
    """Collect every level-0 move seen anywhere in the connected evolution family."""
    family = evolution_line(species.name, species_info)
    moves_by_species: dict[str, dict[str, set[str]]] = {
        relative: defaultdict(set) for relative in family
    }
    for game_name, game_data in games.items():
        for source_species, learnset in game_data.items():
            relative = normalize_name(source_species)
            if relative not in moves_by_species:
                continue
            for entry in learnset.get("LevelMoves", []):
                if int(entry["Level"]) == 0 and entry["Move"] != "MOVE_UNAVAILABLE":
                    moves_by_species[relative][entry["Move"]].add(game_name)

    return [
        {
            "species": relative,
            "moves": [
                {"move": move, "games": sorted(game_names)}
                for move, game_names in sorted(
                    moves_by_species[relative].items(),
                    key=lambda item: display_constant(item[0], "MOVE_"),
                )
            ],
        }
        for relative in sorted(
            family, key=lambda name: (qualified_name(species_info[name]), name)
        )
    ]


def format_level(level: float) -> str:
    return str(int(level)) if level.is_integer() else f"{level:.2f}".rstrip("0")


def analysis_move_list(entries: list[dict[str, object]]) -> str:
    if not entries:
        return "None."
    return ", ".join(
        f"`{display_constant(entry['move'], 'MOVE_')}` "
        f"({entry['learners']}/{entry['cohort_size']}, {entry['prevalence']:.1%})"
        for entry in entries
    ) + "."


def relative_names(names: list[str], species_info: dict[str, SpeciesInfo]) -> str:
    if not names:
        return "None"
    return ", ".join(qualified_name(species_info[name]) for name in names)


def delta_move_list(entries: list[dict[str, object]], species_info: dict[str, SpeciesInfo]) -> str:
    if not entries:
        return "None."
    return ", ".join(
        f"`{display_constant(entry['move'], 'MOVE_')}` "
        f"({relative_names(entry['relatives'], species_info)})"
        for entry in entries
    ) + "."


def render_markdown(
    species: SpeciesInfo,
    moves: list[dict[str, object]],
    evolution_moves: list[dict[str, object]],
    evolution_deltas: dict[str, object],
    comparisons: list[dict[str, object]],
    species_info: dict[str, SpeciesInfo],
    *,
    include_standouts: bool = True,
) -> str:
    output = StringIO()
    print(f"# Move analysis: {qualified_name(species)}", file=output)
    print(file=output)
    print(f"**Type:** {type_label(species.types)}  ", file=output)
    print(f"**Fully evolved:** {'Yes' if species.fully_evolved else 'No'}", file=output)
    print(file=output)
    print("## Combined historical level-up moves", file=output)
    print(file=output)
    print("| Average level | Minimum level | Maximum level | Move | Game appearances |", file=output)
    print("|---:|---:|---:|---|---:|", file=output)
    for item in moves:
        level = format_level(item["average_level"])
        print(
            f"| {level} | {item['minimum_level']} | {item['maximum_level']} | "
            f"{display_name(item['move'], 'MOVE_')} | {item['appearances']} |",
            file=output,
        )
    print(file=output)
    print("## Evolution moves across the evolutionary line", file=output)
    print(file=output)
    print(
        "Any move recorded at level 0 in at least one bundled game is included. "
        "Repeated records are deduplicated by Pokémon, move, and game.",
        file=output,
    )
    for relative_data in evolution_moves:
        relative = species_info[relative_data["species"]]
        print(file=output)
        print(f"### {qualified_name(relative)}", file=output)
        print(file=output)
        if not relative_data["moves"]:
            print("None recorded.", file=output)
            continue
        for entry in relative_data["moves"]:
            print(
                f"- `{display_constant(entry['move'], 'MOVE_')}` — "
                f"{', '.join(entry['games'])}",
                file=output,
            )
    print(file=output)
    print("## Evolution-relative move deltas", file=output)
    print(file=output)
    print(
        "Moves are deduplicated across relatives. Parentheses identify every ancestor or "
        "descendant responsible for that delta.",
        file=output,
    )
    print(file=output)
    print(
        f"**Pre-evolutions compared:** {relative_names(evolution_deltas['pre_evolutions'], species_info)}  ",
        file=output,
    )
    print(
        f"**Evolutions compared:** {relative_names(evolution_deltas['evolutions'], species_info)}",
        file=output,
    )
    class_labels = {
        "level_up": "Level-up moves",
        "egg": "Egg moves",
        "total": "Total learnset",
    }
    for move_class in MOVE_CLASSES:
        deltas = evolution_deltas["move_classes"][move_class]
        print(file=output)
        print(f"### {class_labels[move_class]}", file=output)
        print(file=output)
        print(
            "- **Present in evolutions but not this Pokémon:** "
            + delta_move_list(deltas["evolution_only"], species_info),
            file=output,
        )
        print(
            "- **Present in this Pokémon but missing from evolutions:** "
            + delta_move_list(deltas["missing_from_evolutions"], species_info),
            file=output,
        )
        print(
            "- **Present in pre-evolutions but not this Pokémon:** "
            + delta_move_list(deltas["pre_evolution_only"], species_info),
            file=output,
        )
        print(
            "- **New on this Pokémon relative to pre-evolutions:** "
            + delta_move_list(deltas["new_since_pre_evolutions"], species_info),
            file=output,
        )
    if include_standouts:
        print(file=output)
        print("## Standout move comparisons", file=output)
        if not species.fully_evolved:
            excluded = comparisons[0]["excluded_evolution_line"]
            print(file=output)
            print(
                "**Excluded evolution line:** "
                + ", ".join(display_name(name) for name in excluded)
                + ".",
                file=output,
            )
        for comparison in comparisons:
            print(file=output)
            print(
                f"### {comparison['group']} cohort ({comparison['cohort_size']} Pokémon)",
                file=output,
            )
            if not comparison["cohort_size"]:
                print(file=output)
                print("No eligible fully evolved comparison Pokémon.", file=output)
                continue
            print(file=output)
            for move_class, label in (
                ("level_up", "Level-up (< 1/6)"),
                ("egg", "Egg (< 1/6)"),
                ("total", "Total learnset (< 1/4)"),
            ):
                print(
                    f"- **{label}:** {analysis_move_list(comparison['moves'][move_class])}",
                    file=output,
                )
    return output.getvalue()


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("pokemon", help="Pokemon name, such as Bulbasaur or Mr. Mime")
    parser.add_argument(
        "-o", "--output", type=Path,
        help="Markdown result filename (default: move_analysis_output_instance.md)",
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
        evolution_moves = build_evolution_moves(species, species_info, games)
        evolution_deltas = build_evolution_deltas(species, species_info, pools)
        comparisons = build_comparisons(species, species_info, pools)
    except (FileNotFoundError, json.JSONDecodeError, LookupError, ValueError) as error:
        print(f"error: {error}", file=sys.stderr)
        return 1

    markdown = render_markdown(
        species,
        moves,
        evolution_moves,
        evolution_deltas,
        comparisons,
        species_info,
    )
    output_path = args.output or DEFAULT_OUTPUT
    if output_path.suffix.lower() != ".md":
        print("error: output path must end in .md", file=sys.stderr)
        return 2
    try:
        output_path.parent.mkdir(parents=True, exist_ok=True)
        output_path.write_text(markdown, encoding="utf-8")
    except OSError as error:
        print(f"error: could not write {output_path}: {error}", file=sys.stderr)
        return 1

    print(f"Success: move analysis written to {output_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
