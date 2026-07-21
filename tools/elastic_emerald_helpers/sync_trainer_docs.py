"""Update opt-in generated trainer-party blocks in docs/gameplay/trainers.md."""

from __future__ import annotations

import argparse
import re
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_DOCUMENT = REPO_ROOT / "docs/gameplay/trainers.md"
TRAINER_SOURCE = REPO_ROOT / "src/data/trainers.party"
TRAINER_DATA = REPO_ROOT / "src/data/trainers.h"
BATTLE_SETUP_SOURCE = REPO_ROOT / "src/battle_setup.c"
SPECIES_INFO_DIR = REPO_ROOT / "src/data/pokemon/species_info"
SPECIES_CONSTANTS = REPO_ROOT / "include/constants/species.h"
START_RE = re.compile(r"<!-- trainer-party:start ids?=(TRAINER_[A-Z0-9_]+(?:,TRAINER_[A-Z0-9_]+)*) -->")
END_MARKER = "<!-- trainer-party:end -->"
STAT_NAMES = ("HP", "Atk", "Def", "SpA", "SpD", "Spe")


def _trainer_blocks(source: str) -> dict[str, str]:
    matches = list(re.finditer(r"^=== (TRAINER_[A-Z0-9_]+) ===\s*$", source, re.MULTILINE))
    return {
        match.group(1): source[match.end() : matches[index + 1].start() if index + 1 < len(matches) else len(source)]
        for index, match in enumerate(matches)
    }


def _function_body(source: str, function_name: str) -> str:
    match = re.search(rf"\b{re.escape(function_name)}\s*\([^)]*\)\s*\{{", source)
    if match is None:
        raise ValueError(f"function not found: {function_name}")
    depth = 1
    position = match.end()
    while position < len(source) and depth:
        if source[position] == "{":
            depth += 1
        elif source[position] == "}":
            depth -= 1
        position += 1
    if depth:
        raise ValueError(f"unterminated function: {function_name}")
    return source[match.end() : position - 1]


def _trainer_classes(source: str) -> dict[str, str]:
    entry_re = re.compile(r"\[DIFFICULTY_NORMAL\]\[(TRAINER_[A-Z0-9_]+)\]\s*=")
    entries = list(entry_re.finditer(source))
    classes = {}
    for index, match in enumerate(entries):
        block_end = entries[index + 1].start() if index + 1 < len(entries) else len(source)
        class_match = re.search(r"\.trainerClass\s*=\s*(TRAINER_CLASS_[A-Z0-9_]+)", source[match.end() : block_end])
        if class_match is not None:
            classes[match.group(1)] = class_match.group(1)
    return classes


def _healing_policy(source: str) -> tuple[set[str], dict[str, str], set[str]]:
    class_body = _function_body(source, "TrainerClassHealsBeforeBattle")
    full_return = class_body.find("return TRUE;")
    if full_return < 0:
        raise ValueError("TrainerClassHealsBeforeBattle has no full-heal return")
    full_section = class_body[:full_return]
    full_heal_classes = set(re.findall(r"case (TRAINER_CLASS_[A-Z0-9_]+):", full_section))

    status_body = _function_body(source, "GetTrainerClassPreBattleStatusHeal")
    status_heals = {
        trainer_class: result.removeprefix("TRAINER_PRE_BATTLE_HEAL_").replace("_", " ").title()
        for trainer_class, result in re.findall(
            r"case (TRAINER_CLASS_[A-Z0-9_]+):\s*return (TRAINER_PRE_BATTLE_HEAL_[A-Z0-9_]+);",
            status_body,
        )
    }

    route_boss_body = _function_body(source, "IsRouteBossTrainer")
    route_bosses = set(re.findall(r"case (TRAINER_[A-Z0-9_]+):", route_boss_body))
    return full_heal_classes, status_heals, route_bosses


def _render_healing(
    trainer_id: str,
    trainer_classes: dict[str, str],
    full_heal_classes: set[str],
    status_heals: dict[str, str],
    route_bosses: set[str],
) -> str:
    if trainer_id in route_bosses:
        return "**Pre-battle healing:** Complete heal (route boss override)."
    if trainer_id not in trainer_classes:
        raise ValueError(f"tagged trainer has no normal-difficulty trainer class: {trainer_id}")
    trainer_class = trainer_classes[trainer_id]
    if trainer_class in full_heal_classes:
        return "**Pre-battle healing:** Complete heal."
    if trainer_class in status_heals:
        return f"**Pre-battle healing:** Status conditions only ({status_heals[trainer_class]})."
    return "**Pre-battle healing:** None."


def _render_items(block: str) -> str | None:
    metadata = block[: block.find("AI:")]
    match = re.search(r"^Items:\s*(.+?)\s*$", metadata, re.MULTILINE)
    if match is None:
        return None
    return f"**Items:** {match.group(1)}"


def _metadata_value(block: str, field: str) -> str | None:
    match = re.search(rf"^{re.escape(field)}:\s*(.+?)\s*$", block, re.MULTILINE)
    return match.group(1).strip() if match is not None else None


def _render_battle_type(block: str) -> str:
    battle_type = _metadata_value(block, "Battle Type") or "Singles"
    return f"**Battle type:** {battle_type}."


def _render_additional_ai_flags(block: str) -> str | None:
    ai = _metadata_value(block, "AI")
    if ai is None:
        return None
    flags = [flag.strip() for flag in ai.split("/") if flag.strip() and flag.strip() != "Smart Trainer"]
    if not flags:
        return None
    return " / ".join(flags)


def _species_constant(name: str) -> str:
    if name.startswith("SPECIES_"):
        return name
    normalized = name.replace("é", "e").replace("É", "E")
    normalized = normalized.replace("'", "").replace("’", "").replace("%", "")
    normalized = re.sub(r"[^A-Za-z0-9]+", "_", normalized)
    return f"SPECIES_{normalized.strip('_').upper()}"


def _pokemon_species(heading: str) -> str:
    pokemon = heading.split(" @ ", 1)[0]
    pokemon = re.sub(r"\s+\((?:M|F|Male|Female)\)$", "", pokemon)
    nickname_match = re.search(r"\(([^()]+)\)$", pokemon)
    return nickname_match.group(1) if nickname_match is not None else pokemon


def _species_gender_ratios() -> dict[str, str]:
    ratios = {}
    entry_re = re.compile(r"\[(SPECIES_[A-Z0-9_]+)\]\s*=\s*\{")
    for path in SPECIES_INFO_DIR.glob("*.h"):
        source = path.read_text(encoding="utf-8")
        macro_ratios = {}
        macro_bodies = {}
        macro_entries = list(re.finditer(r"^#define\s+([A-Z0-9_]+)(?:\([^\n]*\))?", source, re.MULTILINE))
        for macro_index, macro_entry in enumerate(macro_entries):
            macro_end = macro_entries[macro_index + 1].start() if macro_index + 1 < len(macro_entries) else len(source)
            body = source[macro_entry.end() : macro_end]
            macro_bodies[macro_entry.group(1)] = body
            macro_ratio = re.search(
                r"\.genderRatio\s*=\s*(MON_MALE|MON_FEMALE|MON_GENDERLESS|PERCENT_FEMALE\([0-9.]+\))",
                body,
            )
            if macro_ratio is not None:
                macro_ratios[macro_entry.group(1)] = macro_ratio.group(1)
        while True:
            additions = {
                name: ratio
                for name, body in macro_bodies.items()
                if name not in macro_ratios
                for dependency, ratio in macro_ratios.items()
                if re.search(rf"\b{dependency}\s*\(", body)
            }
            if not additions:
                break
            macro_ratios.update(additions)
        entries = list(entry_re.finditer(source))
        for index, entry in enumerate(entries):
            end = entries[index + 1].start() if index + 1 < len(entries) else len(source)
            ratio = re.search(
                r"\.genderRatio\s*=\s*(MON_MALE|MON_FEMALE|MON_GENDERLESS|PERCENT_FEMALE\([0-9.]+\))",
                source[entry.end() : end],
            )
            if ratio is not None:
                ratios[entry.group(1)] = ratio.group(1)
            else:
                macro = next((value for name, value in macro_ratios.items() if re.search(rf"\b{name}\s*\(", source[entry.end() : end])), None)
                if macro is not None:
                    ratios[entry.group(1)] = macro
    aliases = re.findall(
        r"^#define\s+(SPECIES_[A-Z0-9_]+)\s+(SPECIES_[A-Z0-9_]+)\s*$",
        SPECIES_CONSTANTS.read_text(encoding="utf-8"),
        re.MULTILINE,
    )
    unresolved = dict(aliases)
    while unresolved:
        progress = False
        for alias, target in list(unresolved.items()):
            if target in ratios:
                ratios[alias] = ratios[target]
                del unresolved[alias]
                progress = True
        if not progress:
            break
    return ratios


def _resolved_gender(block: str, heading: str, ratios: dict[str, str]) -> str:
    species = _species_constant(_pokemon_species(heading))
    if species not in ratios:
        raise ValueError(f"gender ratio not found for documented species: {species}")
    ratio = ratios[species]
    if ratio == "MON_MALE":
        return "Male"
    if ratio == "MON_FEMALE":
        return "Female"
    if ratio == "MON_GENDERLESS":
        return "Genderless"

    explicit = re.search(r"\s+\((M|F|Male|Female)\)(?:\s+@|$)", heading)
    if explicit is not None:
        return "Male" if explicit.group(1) in {"M", "Male"} else "Female"

    battle_type = _metadata_value(block, "Battle Type") or "Singles"
    if battle_type != "Singles":
        personality_byte = 0x80
    else:
        personality_byte = 0x78 if _metadata_value(block, "Gender") == "Female" else 0x88
    percent = float(ratio.removeprefix("PERCENT_FEMALE(").removesuffix(")"))
    threshold = min(254, int(percent * 255 / 100))
    return "Female" if threshold > personality_byte else "Male"


def _party_paragraphs(block: str) -> list[list[str]]:
    lines = block.strip().splitlines()
    ai_index = next((index for index, line in enumerate(lines) if line.startswith("AI:")), None)
    if ai_index is None:
        raise ValueError("trainer block has no AI metadata terminator")
    party_text = "\n".join(lines[ai_index + 1 :]).strip()
    # Source-only comments can describe party ordering or implementation details;
    # they are not Pokemon records and should not leak into generated Markdown.
    party_text = re.sub(r"/\*.*?\*/", "", party_text, flags=re.DOTALL)
    return [[line.rstrip() for line in paragraph.splitlines()] for paragraph in re.split(r"\n\s*\n", party_text) if paragraph.strip()]


def _render_ivs(value: str) -> str:
    ivs = dict.fromkeys(STAT_NAMES, 31)
    seen = set()
    if not value.strip():
        return " / ".join(f"31 {stat}" for stat in STAT_NAMES)
    for entry in value.split("/"):
        match = re.fullmatch(r"\s*(\d+)\s+(HP|Atk|Def|SpA|SpD|Spe)\s*", entry)
        if match is None:
            raise ValueError(f"invalid IVs value: {value}")
        stat = match.group(2)
        if stat in seen:
            raise ValueError(f"duplicate IV stat: {stat}")
        seen.add(stat)
        iv = int(match.group(1))
        if iv not in range(32):
            raise ValueError(f"IV for {stat} is outside 0 to 31: {iv}")
        ivs[stat] = iv
    return " / ".join(f"{ivs[stat]} {stat}" for stat in STAT_NAMES)


def _render_party(
    block: str,
    ratios: dict[str, str],
    use_shared_default: bool = False,
) -> str:
    rendered = []
    for lines in _party_paragraphs(block):
        heading = lines[0].strip()
        attributes = []
        moves = []
        pp_ups = [0, 0, 0, 0]
        for line in lines[1:]:
            value = line.strip()
            if not value:
                continue
            if value.startswith("- "):
                moves.append(value[2:].strip())
            elif value.startswith("PP Ups:"):
                pp_ups = [int(item.strip()) for item in value.removeprefix("PP Ups:").split("/")]
                if len(pp_ups) != 4 or any(item not in range(4) for item in pp_ups):
                    raise ValueError(f"invalid PP Ups value: {value}")
            elif value.endswith(" Nature"):
                attributes.append(("Nature", value.removesuffix(" Nature")))
            elif ":" in value:
                label, content = value.split(":", 1)
                if label == "IVs":
                    content = _render_ivs(content)
                attributes.append((label, content.strip()))
            else:
                raise ValueError(f"unsupported trainer-party line: {value}")

        if not any(label == "IVs" for label, _ in attributes):
            attributes.append(("IVs", _render_ivs("")))

        if " @ " in heading:
            pokemon, item = heading.split(" @ ", 1)
        else:
            pokemon = heading
            item = None
        gender_match = re.search(r"\s+\((M|F|Male|Female)\)$", pokemon)
        gender = "Trainer default" if use_shared_default and gender_match is None else _resolved_gender(block, heading, ratios)
        attributes.insert(0, ("Gender", gender))
        if gender_match is not None:
            pokemon = pokemon[: gender_match.start()]
        rendered_heading = f"**{pokemon}**" + (f" @ {item}" if item is not None else "")
        output = [rendered_heading]
        output.extend(f"- **{label}:** {value}" for label, value in attributes)
        if moves:
            output.append("- **Moves:**")
            for index, move in enumerate(moves):
                annotation = " (**PP Maxed**)" if pp_ups[index] == 3 else (f" (**{pp_ups[index]} PP Ups**)" if pp_ups[index] else "")
                output.append(f"  - {move}{annotation}")
        rendered.append("\n".join(output))
    return "\n\n".join(rendered)


def sync_document(
    document: str,
    sources: dict[str, str],
    trainer_classes: dict[str, str],
    full_heal_classes: set[str],
    status_heals: dict[str, str],
    route_bosses: set[str],
    species_gender_ratios: dict[str, str],
) -> str:
    output = []
    position = 0
    seen = set()
    while match := START_RE.search(document, position):
        end = document.find(END_MARKER, match.end())
        if end < 0:
            raise ValueError(f"missing end marker for {match.group(1)}")
        trainer_ids = match.group(1).split(",")
        rendered_items = []
        rendered_battle_types = []
        rendered_ai_flags = []
        rendered_healing = []
        rendered_parties = []
        for trainer_id in trainer_ids:
            if trainer_id in seen:
                raise ValueError(f"duplicate documentation tag: {trainer_id}")
            if trainer_id not in sources:
                raise ValueError(f"tagged trainer is absent from source: {trainer_id}")
            seen.add(trainer_id)
            rendered_items.append(_render_items(sources[trainer_id]))
            rendered_battle_types.append(_render_battle_type(sources[trainer_id]))
            rendered_ai_flags.append(_render_additional_ai_flags(sources[trainer_id]))
            rendered_healing.append(
                _render_healing(trainer_id, trainer_classes, full_heal_classes, status_heals, route_bosses)
            )
            rendered_parties.append(_render_party(sources[trainer_id], species_gender_ratios, len(trainer_ids) > 1))
        for label, values in (
            ("items", rendered_items),
            ("battle type", rendered_battle_types),
            ("healing policy", rendered_healing),
            ("party", rendered_parties),
        ):
            if any(value != values[0] for value in values[1:]):
                raise ValueError(f"tagged trainers no longer share {label}: {', '.join(trainer_ids)}")

        generated_sections = []
        if rendered_items[0] is not None:
            generated_sections.append(rendered_items[0])
        generated_sections.append(rendered_battle_types[0])
        if all(flags == rendered_ai_flags[0] for flags in rendered_ai_flags[1:]):
            if rendered_ai_flags[0] is not None:
                generated_sections.append(f"**Additional AI flags:** {rendered_ai_flags[0]}.")
        else:
            for trainer_id, flags in zip(trainer_ids, rendered_ai_flags):
                if flags is not None:
                    trainer_name = (_metadata_value(sources[trainer_id], "Name") or trainer_id).title()
                    generated_sections.append(f"**Additional AI flags ({trainer_name}):** {flags}.")
        generated_sections.append(rendered_healing[0])
        generated_sections.append(rendered_parties[0])
        output.append(document[position : match.end()])
        output.append("\n")
        output.append("\n\n".join(generated_sections))
        output.append("\n")
        output.append(END_MARKER)
        position = end + len(END_MARKER)
    output.append(document[position:])
    return "".join(output)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--document", type=Path, default=DEFAULT_DOCUMENT)
    parser.add_argument("--check", action="store_true", help="fail if the generated regions are stale")
    args = parser.parse_args()
    original = args.document.read_text(encoding="utf-8")
    full_heal_classes, status_heals, route_bosses = _healing_policy(BATTLE_SETUP_SOURCE.read_text(encoding="utf-8"))
    updated = sync_document(
        original,
        _trainer_blocks(TRAINER_SOURCE.read_text(encoding="utf-8")),
        _trainer_classes(TRAINER_DATA.read_text(encoding="utf-8")),
        full_heal_classes,
        status_heals,
        route_bosses,
        _species_gender_ratios(),
    )
    if args.check:
        if updated != original:
            raise SystemExit(f"{args.document} has stale generated trainer blocks")
    else:
        args.document.write_text(updated, encoding="utf-8")


if __name__ == "__main__":
    main()
