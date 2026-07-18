"""Update opt-in generated trainer-party blocks in docs/gameplay/trainers.md."""

from __future__ import annotations

import argparse
import re
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parents[2]
DEFAULT_DOCUMENT = REPO_ROOT / "docs/gameplay/trainers.md"
TRAINER_SOURCE = REPO_ROOT / "src/data/trainers.party"
START_RE = re.compile(r"<!-- trainer-party:start ids?=(TRAINER_[A-Z0-9_]+(?:,TRAINER_[A-Z0-9_]+)*) -->")
END_MARKER = "<!-- trainer-party:end -->"


def _trainer_blocks(source: str) -> dict[str, str]:
    matches = list(re.finditer(r"^=== (TRAINER_[A-Z0-9_]+) ===\s*$", source, re.MULTILINE))
    return {
        match.group(1): source[match.end() : matches[index + 1].start() if index + 1 < len(matches) else len(source)]
        for index, match in enumerate(matches)
    }


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


def sync_document(document: str, sources: dict[str, str]) -> str:
    output = []
    position = 0
    seen = set()
    while match := START_RE.search(document, position):
        end = document.find(END_MARKER, match.end())
        if end < 0:
            raise ValueError(f"missing end marker for {match.group(1)}")
        trainer_ids = match.group(1).split(",")
        rendered_parties = []
        for trainer_id in trainer_ids:
            if trainer_id in seen:
                raise ValueError(f"duplicate documentation tag: {trainer_id}")
            if trainer_id not in sources:
                raise ValueError(f"tagged trainer is absent from source: {trainer_id}")
            seen.add(trainer_id)
            rendered_parties.append(_render_party(sources[trainer_id]))
        if any(party != rendered_parties[0] for party in rendered_parties[1:]):
            raise ValueError(f"tagged trainers no longer share a party: {', '.join(trainer_ids)}")
        output.append(document[position : match.end()])
        output.append("\n")
        output.append(rendered_parties[0])
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
    updated = sync_document(original, _trainer_blocks(TRAINER_SOURCE.read_text(encoding="utf-8")))
    if args.check:
        if updated != original:
            raise SystemExit(f"{args.document} has stale generated trainer blocks")
    else:
        args.document.write_text(updated, encoding="utf-8")


if __name__ == "__main__":
    main()
