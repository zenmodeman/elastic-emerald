"""Update the PokemonMovesets worksheet from the repository's current learnsets."""

from __future__ import annotations

import argparse
import os
import re
import sys
import time
from pathlib import Path

if __package__:
    from .source_data import load_species_data, load_teachable_mappings
    from .spreadsheet_config import egg_move_column, split_info, teachable_categories
else:
    # Support `python update_moves_spreadsheet.py` from this directory in addition
    # to the preferred package invocation from the repository root.
    sys.path.insert(0, str(Path(__file__).resolve().parents[2]))
    from tools.elastic_emerald_helpers.source_data import load_species_data, load_teachable_mappings
    from tools.elastic_emerald_helpers.spreadsheet_config import egg_move_column, split_info, teachable_categories


def _normalize_species_name(name: str) -> str:
    return re.sub(r"[^a-z0-9]", "", name.lower())


def _normalize_species_number(number: str) -> str:
    return number.strip().replace(",", "")


def _resolve_sheet_rows(sheet_values: list[list[str]], species: list[dict[str, object]]) -> dict[str, int]:
    """Resolve stable Column A identifiers to current worksheet row numbers."""
    rows_by_number: dict[str, list[tuple[int, str]]] = {}
    for row_number, row in enumerate(sheet_values, 1):
        if not row:
            continue
        number = _normalize_species_number(row[0])
        if number:
            rows_by_number.setdefault(number, []).append((row_number, row[1] if len(row) > 1 else ""))

    resolved: dict[str, int] = {}
    for mon in species:
        species_number = str(mon["species_number"])
        candidates = rows_by_number.get(_normalize_species_number(species_number), [])
        if len(candidates) == 1:
            resolved[mon["species_id"]] = candidates[0][0]
            continue
        name = _normalize_species_name(str(mon["species_id"]))
        name_matches = [row for row, sheet_name in candidates if _normalize_species_name(sheet_name) == name]
        if len(name_matches) == 1:
            resolved[mon["species_id"]] = name_matches[0]
            continue
        details = ", ".join(f"row {row} ({sheet_name})" for row, sheet_name in candidates) or "none"
        raise ValueError(
            f"Could not uniquely resolve {mon['species_id']} (species number {species_number}); candidates: {details}"
        )
    return resolved


def _cell_text(mon: dict[str, object], split: dict[str, object], mappings: list[dict[str, object]]) -> str:
    grouped: dict[int, list[str]] = {}
    for level_info in mon["levelup_reference"]:
        level = level_info["level"]
        if split["min_level"] <= level <= split["max_level"]:
            grouped.setdefault(level, []).append(level_info["move"])
    sections = [
        f"{'Evo Move' if level == 0 else f'Level {level}'}: {', '.join(moves)}"
        for level, moves in grouped.items()
    ]
    teachable = set(mon["teachable_reference"])
    for category in teachable_categories.display_order:
        mapping = next(
            (
                item
                for item in mappings
                if item["type"] == category and item["num_badges"] == split["num_badges"]
            ),
            None,
        )
        if mapping:
            available = sorted(teachable.intersection(mapping["data"]))
            if available:
                sections.append(f"{category}: {', '.join(available)}")
    return "\n".join(sections)


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--credentials", type=Path, default=os.environ.get("ELASTIC_EMERALD_GOOGLE_CREDENTIALS", Path(__file__).with_name("SecretKey.json")))
    parser.add_argument("--workbook", default="Pokemon Elastic Emerald Spreadsheet")
    #Temporarily using another sheet with the full scope to avoid the current limitations
    parser.add_argument("--worksheet", default="PokemonMovesetsUnreleased")
    # parser.add_argument("--worksheet", default="PokemonMovesets")

    parser.add_argument("--start", type=int, default=0)
    parser.add_argument("--end", type=int)
    parser.add_argument("--delay", type=float, default=1.1)
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args()

    species = load_species_data()[args.start : args.end]
    mappings = load_teachable_mappings()
    sheet = None
    sheet_rows: dict[str, int] = {}
    if not args.dry_run:
        import gspread
        if not args.credentials.is_file():
            parser.error(f"credentials file not found: {args.credentials}")
        sheet = gspread.service_account(filename=str(args.credentials)).open(args.workbook).worksheet(args.worksheet)
        sheet_rows = _resolve_sheet_rows(sheet.get("A:B"), species)

    for mon in species:
        row = sheet_rows.get(mon["species_id"])
        updates = {
            split["column"]: _cell_text(mon, split, mappings)
            for split in split_info
        }
        if mon["egg_move_reference"]:
            updates[egg_move_column] = ", ".join(sorted(mon["egg_move_reference"]))
        for column, value in updates.items():
            if args.dry_run:
                print(f"{mon['species_id']} {column}[species #{mon['species_number']}]:\n{value}\n")
            else:
                cell = f"{column}{row}"
                sheet.update_acell(cell, value)
                time.sleep(args.delay)


if __name__ == "__main__":
    main()
