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
START_RE = re.compile(r"<!-- trainer-party:start ids?=(TRAINER_[A-Z0-9_]+(?:,TRAINER_[A-Z0-9_]+)*) -->")
END_MARKER = "<!-- trainer-party:end -->"


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


def _render_party(block: str) -> str:
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
                attributes.append((label, content.strip()))
            else:
                raise ValueError(f"unsupported trainer-party line: {value}")

        if " @ " in heading:
            pokemon, item = heading.split(" @ ", 1)
            rendered_heading = f"**{pokemon}** @ {item}"
        else:
            rendered_heading = f"**{heading}**"
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
            rendered_parties.append(_render_party(sources[trainer_id]))
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
    )
    if args.check:
        if updated != original:
            raise SystemExit(f"{args.document} has stale generated trainer blocks")
    else:
        args.document.write_text(updated, encoding="utf-8")


if __name__ == "__main__":
    main()
