#!/usr/bin/env python3
"""Write a Markdown analysis of documented trainer-party blocks.

Run from anywhere with:
    python3 tools/elastic_emerald_helpers/analyze_trainer_types.py
"""

from __future__ import annotations

import argparse
import re
import unicodedata
from collections import Counter, defaultdict
from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_DOCUMENT = REPO_ROOT / "docs/gameplay/trainers.md"
DEFAULT_OUTPUT = Path(__file__).resolve().parent / "trainer_set_analysis.md"
DEFAULT_SPECIES_DIR = REPO_ROOT / "src/data/pokemon/species_info"
DEFAULT_SPECIES_CONSTANTS = REPO_ROOT / "include/constants/species.h"
MOVES_INFO = REPO_ROOT / "src/data/moves_info.h"
TRAINER_SOURCE = REPO_ROOT / "src/data/trainers.party"
DEFAULT_ABILITY = "Default"
TYPES = (
    "Normal",
    "Fire",
    "Water",
    "Electric",
    "Grass",
    "Ice",
    "Fighting",
    "Poison",
    "Ground",
    "Flying",
    "Psychic",
    "Bug",
    "Rock",
    "Ghost",
    "Dragon",
    "Dark",
    "Steel",
    "Fairy",
)
PARTY_BLOCK_RE = re.compile(
    r"<!-- trainer-party:start ids?=([^ ]+) -->(.*?)<!-- trainer-party:end -->",
    re.DOTALL,
)
POKEMON_HEADING_RE = re.compile(
    r"^\*\*(.+?)\*\*(?: @ .+)?\n- \*\*Gender:\*\*",
    re.MULTILINE,
)


def normalize_name(value: str) -> str:
    """Convert a display name or constant into a comparable identifier."""
    value = unicodedata.normalize("NFKD", value)
    value = "".join(character for character in value if not unicodedata.combining(character))
    value = value.replace("’", "").replace("'", "")
    return re.sub(r"[^A-Z0-9]+", "_", value.upper()).strip("_")


def canonical_trainer_id(raw_ids: str) -> str:
    """Collapse party-format suffixes while retaining the trainer identity."""
    ignored_tokens = {"DOUBLES", "SINGLES", "MON"}
    trainer_ids = []
    for raw_id in raw_ids.split(","):
        tokens = raw_id.removeprefix("TRAINER_").split("_")
        # Rival party identifiers also encode location and the player's
        # starter/team branch. Those branches are still the same trainer when
        # the responsible species and move are identical.
        if tokens[0] in {"BRENDAN", "MAY"}:
            trainer_ids.append(tokens[0])
            continue
        identity = [
            token
            for token in tokens
            if not token.isdigit()
            and not re.fullmatch(r"\d+MON", token)
            and token not in ignored_tokens
        ]
        trainer_ids.append("_".join(identity))
    return ",".join(sorted(trainer_ids))


def heading_species_name(heading: str) -> str:
    display_name = heading.split(" @ ", 1)[0]
    nickname_match = re.search(r"\(([^()]+)\)$", display_name)
    return nickname_match.group(1) if nickname_match else display_name


def documented_data(
    document: Path,
) -> tuple[
    dict[str, str],
    dict[str, Counter[str]],
    Counter[str],
    dict[str, list[tuple[str, ...]]],
]:
    """Return species abilities and deduplicated trainer/species move usage."""
    source = document.read_text(encoding="utf-8")
    source = re.sub(r"```.*?```", "", source, flags=re.DOTALL)
    pokemon: dict[str, str] = {}
    pokemon_abilities: dict[str, Counter[str]] = defaultdict(Counter)
    moves: Counter[str] = Counter()
    move_trainer_uses: dict[str, list[tuple[str, ...]]] = defaultdict(list)
    seen_pokemon_abilities: set[tuple[str, str, str]] = set()
    seen_move_uses: set[tuple[str, str, str]] = set()
    for raw_ids, party_block in PARTY_BLOCK_RE.findall(source):
        trainer_id = canonical_trainer_id(raw_ids)
        headings = list(POKEMON_HEADING_RE.finditer(party_block))
        for index, heading_match in enumerate(headings):
            species_name = heading_species_name(heading_match.group(1))
            normalized_species = normalize_name(species_name)
            pokemon.setdefault(normalized_species, species_name)
            segment_end = (
                headings[index + 1].start()
                if index + 1 < len(headings)
                else len(party_block)
            )
            pokemon_block = party_block[heading_match.end() : segment_end]
            ability_match = re.search(
                r"^- \*\*Ability:\*\* (.+?)\s*$",
                pokemon_block,
                re.MULTILINE,
            )
            ability = ability_match.group(1).strip() if ability_match else DEFAULT_ABILITY
            species_ability = (trainer_id, normalized_species, normalize_name(ability))
            if species_ability not in seen_pokemon_abilities:
                seen_pokemon_abilities.add(species_ability)
                pokemon_abilities[normalized_species][ability] += 1
            for move in re.findall(r"^  - (.+?)\s*$", pokemon_block, re.MULTILINE):
                move = move.strip()
                use = (trainer_id, normalize_name(species_name), normalize_name(move))
                if use not in seen_move_uses:
                    seen_move_uses.add(use)
                    moves[move] += 1
                    move_trainer_uses[move].append(tuple(raw_ids.split(",")))
    if not pokemon:
        raise ValueError(f"no generated trainer-party Pokemon found in {document}")
    if not moves:
        raise ValueError(f"no moves found in generated trainer-party blocks in {document}")
    return pokemon, pokemon_abilities, moves, move_trainer_uses


def trainer_definitions(trainer_source: Path) -> dict[str, tuple[str, str, int]]:
    """Return trainer names, classes, and source-definition positions."""
    source = trainer_source.read_text(encoding="utf-8")
    headers = list(
        re.finditer(r"^=== (TRAINER_[A-Z0-9_]+) ===\s*$", source, re.MULTILINE)
    )
    definitions = {}
    for index, header in enumerate(headers):
        end = headers[index + 1].start() if index + 1 < len(headers) else len(source)
        block = source[header.end() : end]
        name_match = re.search(r"^Name:\s*(.*?)\s*$", block, re.MULTILINE)
        class_match = re.search(r"^Class:\s*(.*?)\s*$", block, re.MULTILINE)
        if name_match and name_match.group(1):
            definitions.setdefault(
                header.group(1),
                (
                    name_match.group(1),
                    class_match.group(1) if class_match else "Pkmn Trainer",
                    index,
                ),
            )
    return definitions


def grunt_location(trainer_id: str) -> str:
    """Return the meaningful identifier suffix for a Grunt definition."""
    prefix = "TRAINER_GRUNT_"
    if not trainer_id.startswith(prefix):
        return ""
    tokens = [
        token
        for token in trainer_id.removeprefix(prefix).split("_")
        if not token.isdigit()
        and not re.fullmatch(r"\d+MON", token)
        and token not in {"DOUBLES", "SINGLES", "MON"}
    ]
    return " ".join(token.title() for token in tokens)


def move_trainer_names(
    move_trainer_uses: dict[str, list[tuple[str, ...]]],
    definitions: dict[str, tuple[str, str, int]],
) -> dict[str, list[str]]:
    """Resolve trainer uses, retaining explicit shared-set groupings."""
    result = {}
    for move, trainer_uses in move_trainer_uses.items():
        trainer_ids = {
            trainer_id for trainer_use in trainer_uses for trainer_id in trainer_use
        }
        missing = sorted(
            trainer_id for trainer_id in trainer_ids if trainer_id not in definitions
        )
        if missing:
            raise ValueError(
                f"trainer definitions not found for {move}: " + ", ".join(missing)
            )

        grouped_uses: Counter[tuple[str, ...]] = Counter()
        group_order: dict[tuple[str, ...], int] = {}
        for trainer_use in trainer_uses:
            ordered = sorted(
                (
                    (trainer_id, *definitions[trainer_id])
                    for trainer_id in trainer_use
                ),
                key=lambda entry: entry[3],
            )
            labels = []
            seen_normalized_names = set()
            for trainer_id, name, trainer_class, _ in ordered:
                location = grunt_location(trainer_id) if normalize_name(name) == "GRUNT" else ""
                label = f"{trainer_class} {name}"
                if location:
                    label += f" ({location})"
                normalized_label = normalize_name(label)
                if normalized_label not in seen_normalized_names:
                    seen_normalized_names.add(normalized_label)
                    labels.append(label)
            group = tuple(labels)
            grouped_uses[group] += 1
            group_order.setdefault(group, ordered[0][3])

        result[move] = []
        for group, frequency in sorted(
            grouped_uses.items(),
            key=lambda item: group_order[item[0]],
        ):
            if len(group) > 1:
                label = " / ".join(
                    (
                        f"{trainer} ({frequency})"
                        if frequency > 1
                        else trainer
                    )
                    for trainer in group
                )
                label += " (shared set)" if frequency == 1 else " (shared sets)"
            else:
                label = group[0]
            if len(group) == 1 and frequency > 1:
                label += f" ({frequency})"
            result[move].append(label)
    return result


def initializer_blocks(source: str, constant_prefix: str):
    """Yield constants and brace-balanced initializer bodies."""
    header = re.compile(rf"\[({re.escape(constant_prefix)}[A-Z0-9_]+)\]\s*=\s*\{{")
    for match in header.finditer(source):
        depth = 1
        position = match.end()
        while position < len(source) and depth:
            if source[position] == "{":
                depth += 1
            elif source[position] == "}":
                depth -= 1
            position += 1
        if depth:
            raise ValueError(f"unterminated species initializer: {match.group(1)}")
        yield match.group(1), source[match.end() : position - 1]


def macros(source: str) -> dict[str, tuple[tuple[str, ...], str]]:
    """Read macro parameters and bodies, retaining the active-first variant."""
    logical_source = re.sub(r"\\\r?\n", "", source)
    result = {}
    pattern = re.compile(
        r"^\s*#define\s+([A-Z0-9_]+)(?:\(([^)]*)\))?\s+(.+)$",
        re.MULTILINE,
    )
    for name, raw_parameters, body in pattern.findall(logical_source):
        parameters = tuple(
            parameter.strip() for parameter in raw_parameters.split(",")
        ) if raw_parameters else ()
        # Type-selection macros in these headers put the modern configuration
        # first and the legacy fallback in an #else branch.
        result.setdefault(name, (parameters, body))
    return result


def parse_types(expression: str) -> tuple[str, ...]:
    constants = re.findall(r"\bTYPE_([A-Z0-9_]+)\b", expression)
    return tuple(dict.fromkeys(constant.title() for constant in constants))


def types_from_body(
    body: str,
    macro_definitions: dict[str, tuple[tuple[str, ...], str]],
    seen: frozenset[str] = frozenset(),
) -> tuple[str, ...]:
    direct_match = re.search(r"\.types\s*=\s*MON_TYPES\(([^)]*)\)", body)
    if direct_match:
        return parse_types(direct_match.group(1))

    field_macro = re.search(r"\.types\s*=\s*([A-Z0-9_]+)", body)
    if field_macro and field_macro.group(1) in macro_definitions:
        return parse_types(macro_definitions[field_macro.group(1)][1])

    for macro_name, (parameters, macro_body) in macro_definitions.items():
        if macro_name in seen:
            continue
        call = re.search(rf"\b{re.escape(macro_name)}(?:\(([^)]*)\))?", body)
        if call is None:
            continue
        arguments = tuple(
            argument.strip() for argument in (call.group(1) or "").split(",")
        )
        expanded = macro_body
        for parameter, argument in zip(parameters, arguments):
            expanded = re.sub(rf"\b{re.escape(parameter)}\b", argument, expanded)
        types = types_from_body(expanded, macro_definitions, seen | {macro_name})
        if types:
            return types
    return ()


def species_types(species_dir: Path) -> dict[str, tuple[str, ...]]:
    """Read types from direct fields and shared species-info macros."""
    result = {}
    for path in sorted(species_dir.glob("gen_*_families.h")):
        source = path.read_text(encoding="utf-8")
        macro_definitions = macros(source)
        for species, body in initializer_blocks(source, "SPECIES_"):
            types = types_from_body(body, macro_definitions)
            if types:
                result[species.removeprefix("SPECIES_")] = types
    if not result:
        raise ValueError(f"no species types found in {species_dir}")
    return result


def species_default_abilities(species_dir: Path) -> dict[str, str]:
    """Read the first ability used when a trainer set omits an override."""
    result = {}
    for path in sorted(species_dir.glob("gen_*_families.h")):
        source = path.read_text(encoding="utf-8")
        macro_definitions = macros(source)
        for species, body in initializer_blocks(source, "SPECIES_"):
            ability_match = re.search(
                r"\.abilities\s*=\s*\{\s*ABILITY_([A-Z0-9_]+)",
                body,
            )
            if ability_match is None:
                macro_match = re.search(r"\.abilities\s*=\s*([A-Z0-9_]+)", body)
                if macro_match and macro_match.group(1) in macro_definitions:
                    ability_match = re.search(
                        r"\{\s*ABILITY_([A-Z0-9_]+)",
                        macro_definitions[macro_match.group(1)][1],
                    )
            if ability_match:
                result[species.removeprefix("SPECIES_")] = (
                    ability_match.group(1).replace("_", " ").title()
                )
    return result


def species_aliases(constants_path: Path) -> dict[str, str]:
    source = constants_path.read_text(encoding="utf-8")
    return {
        alias.removeprefix("SPECIES_"): target.removeprefix("SPECIES_")
        for alias, target in re.findall(
            r"\b(SPECIES_[A-Z0-9_]+)\s*=\s*(SPECIES_[A-Z0-9_]+)\b",
            source,
        )
    }


def resolve_default_abilities(
    pokemon_abilities: dict[str, Counter[str]],
    aliases: dict[str, str],
    default_abilities: dict[str, str],
) -> None:
    """Replace omitted trainer abilities with each species' first ability."""
    for species, abilities in pokemon_abilities.items():
        frequency = abilities.pop(DEFAULT_ABILITY, 0)
        if not frequency:
            continue
        constant = aliases.get(species, species)
        if constant not in default_abilities:
            raise ValueError(f"default ability not found for documented Pokemon: {species}")
        abilities[default_abilities[constant]] += frequency


def resolve_species(
    documented: dict[str, str],
    types_by_species: dict[str, tuple[str, ...]],
    aliases: dict[str, str],
) -> dict[str, tuple[str, ...]]:
    resolved = {}
    missing = []
    for normalized_name, display_name in documented.items():
        constant = aliases.get(normalized_name, normalized_name)
        if constant not in types_by_species:
            missing.append(display_name)
            continue
        resolved[display_name] = types_by_species[constant]
    if missing:
        raise ValueError("types not found for documented Pokemon: " + ", ".join(sorted(missing)))
    return resolved


def status_move_analysis(
    documented_moves: Counter[str],
    moves_info_path: Path,
) -> tuple[Counter[str], list[str]]:
    """Return used status frequencies and unused status move display names."""
    source = moves_info_path.read_text(encoding="utf-8")
    move_blocks = list(initializer_blocks(source, "MOVE_"))
    known_constants = {
        constant.removeprefix("MOVE_") for constant, _ in move_blocks
    }
    status_moves = {
        constant.removeprefix("MOVE_"): (
            name_match.group(1)
            if (name_match := re.search(
                r'\.name\s*=\s*COMPOUND_STRING\("([^"]+)"\)',
                body,
            ))
            else constant.removeprefix("MOVE_").replace("_", " ").title()
        )
        for constant, body in move_blocks
        if re.search(r"\.category\s*=\s*DAMAGE_CATEGORY_STATUS\b", body)
    }
    missing = sorted(
        move for move in documented_moves if normalize_name(move) not in known_constants
    )
    if missing:
        raise ValueError("move data not found for documented moves: " + ", ".join(missing))
    used = Counter(
        {
            move: frequency
            for move, frequency in documented_moves.items()
            if normalize_name(move) in status_moves
        }
    )
    used_constants = {normalize_name(move) for move in used}
    unused = sorted(
        (
            display_name
            for constant, display_name in status_moves.items()
            if constant not in used_constants
        ),
        key=lambda name: (normalize_name(name), name),
    )
    return used, unused


def render_report(
    resolved: dict[str, tuple[str, ...]],
    pokemon_abilities: dict[str, Counter[str]],
    status_moves: Counter[str],
    status_move_trainers: dict[str, list[str]],
    unused_status_moves: list[str],
    document: Path,
) -> str:
    pokemon_by_type: dict[str, set[str]] = defaultdict(set)
    for pokemon, pokemon_types in resolved.items():
        for pokemon_type in pokemon_types:
            pokemon_by_type[pokemon_type].add(pokemon)

    ordered_types = sorted(
        TYPES,
        key=lambda pokemon_type: (-len(pokemon_by_type[pokemon_type]), pokemon_type),
    )
    try:
        source_label = document.resolve().relative_to(REPO_ROOT)
    except ValueError:
        source_label = document.resolve()
    lines = [
        "# Trainer Set Analysis",
        "",
        f"Generated from `{source_label}`. Re-run the analyzer to refresh this file.",
        "",
        "## Unique Pokémon by Type",
        "",
        "Ability counts deduplicate numbered, battle-format, and shared rival-team "
        "branches for the same trainer, Pokémon species, and ability combination.",
        "",
    ]
    for pokemon_type in ordered_types:
        pokemon = sorted(
            pokemon_by_type[pokemon_type],
            key=lambda name: (normalize_name(name), name),
        )
        pokemon_labels = []
        for name in pokemon:
            abilities = pokemon_abilities[normalize_name(name)]
            ability_labels = [
                f"{ability} ({frequency})" if frequency > 1 else ability
                for ability, frequency in sorted(
                    abilities.items(),
                    key=lambda item: (normalize_name(item[0]), item[0]),
                )
            ]
            pokemon_labels.append(f"{name} ({', '.join(ability_labels)})")
        lines.extend(
            [
                f"### {pokemon_type} ({len(pokemon)})",
                "",
                ", ".join(pokemon_labels) if pokemon_labels else "None.",
                "",
            ]
        )

    lines.extend(
        [
            "## Status Move Usage",
            "",
            "Frequencies count each unique trainer and Pokémon-species combination using "
            "the move. Party-size, battle-format, and numbered trainer variants are "
            "deduplicated.",
            "",
            "| Move | Frequency | Trainers |",
            "| --- | ---: | --- |",
        ]
    )
    lines.extend(
        f"| {move} | {frequency} | {', '.join(status_move_trainers[move])} |"
        for move, frequency in sorted(
            status_moves.items(),
            key=lambda item: (-item[1], normalize_name(item[0]), item[0]),
        )
    )
    lines.extend(
        [
            "",
            "## Unused Status Moves",
            "",
            f"{len(unused_status_moves)} status moves have not appeared on a documented "
            "trainer set.",
            "",
            ", ".join(unused_status_moves) if unused_status_moves else "None.",
        ]
    )
    return "\n".join(lines) + "\n"


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Write a Markdown analysis of documented trainer sets."
    )
    parser.add_argument(
        "document",
        nargs="?",
        type=Path,
        default=DEFAULT_DOCUMENT,
        help=f"trainer Markdown file (default: {DEFAULT_DOCUMENT.relative_to(REPO_ROOT)})",
    )
    parser.add_argument(
        "-o",
        "--output",
        type=Path,
        default=DEFAULT_OUTPUT,
        help=f"output Markdown file (default: {DEFAULT_OUTPUT.relative_to(REPO_ROOT)})",
    )
    args = parser.parse_args()

    (
        documented,
        pokemon_abilities,
        documented_moves,
        move_trainer_uses,
    ) = documented_data(args.document)
    types_by_species = species_types(DEFAULT_SPECIES_DIR)
    aliases = species_aliases(DEFAULT_SPECIES_CONSTANTS)
    resolve_default_abilities(
        pokemon_abilities,
        aliases,
        species_default_abilities(DEFAULT_SPECIES_DIR),
    )
    resolved = resolve_species(documented, types_by_species, aliases)
    status_moves, unused_status_moves = status_move_analysis(documented_moves, MOVES_INFO)
    all_move_trainers = move_trainer_names(
        move_trainer_uses,
        trainer_definitions(TRAINER_SOURCE),
    )
    status_move_trainers = {
        move: all_move_trainers[move]
        for move in status_moves
    }
    report = render_report(
        resolved,
        pokemon_abilities,
        status_moves,
        status_move_trainers,
        unused_status_moves,
        args.document,
    )
    args.output.parent.mkdir(parents=True, exist_ok=True)
    args.output.write_text(report, encoding="utf-8")
    print(f"Wrote {args.output}")


if __name__ == "__main__":
    main()
