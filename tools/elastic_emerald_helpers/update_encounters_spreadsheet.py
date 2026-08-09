"""Update source-backed cells in the EncountersUnreleased worksheet."""

from __future__ import annotations

import argparse
import os
import re
import sys
from collections import Counter
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable

if __package__:
    from .audit_encounters import EncounterSource, load_encounter_source
    from .source_data import REPO_ROOT
else:
    sys.path.insert(0, str(Path(__file__).resolve().parents[2]))
    from tools.elastic_emerald_helpers.audit_encounters import EncounterSource, load_encounter_source
    from tools.elastic_emerald_helpers.source_data import REPO_ROOT


@dataclass(frozen=True)
class RowSource:
    map_name: str
    field_name: str
    fishing_groups: tuple[str, ...] = ()
    include_monotype: bool = False


TYPE_ORDER = (
    "TYPE_BUG", "TYPE_POISON", "TYPE_FLYING",
    "TYPE_GRASS", "TYPE_FIRE", "TYPE_WATER",
    "TYPE_DARK", "TYPE_FIGHTING", "TYPE_FAIRY",
    "TYPE_GROUND", "TYPE_ROCK", "TYPE_STEEL",
    "TYPE_NORMAL", "TYPE_PSYCHIC", "TYPE_GHOST",
    "TYPE_DRAGON", "TYPE_ELECTRIC", "TYPE_ICE",
)
TYPE_COLORS = {
    "TYPE_BUG": "#aabb22", "TYPE_POISON": "#aa5599", "TYPE_FLYING": "#8899ff",
    "TYPE_GRASS": "#77cc55", "TYPE_FIRE": "#ff4422", "TYPE_WATER": "#3399ff",
    "TYPE_DARK": "#775544", "TYPE_FIGHTING": "#bb5544", "TYPE_FAIRY": "#ee99ee",
    "TYPE_GROUND": "#ddbb55", "TYPE_ROCK": "#bbaa66", "TYPE_STEEL": "#aaaabb",
    "TYPE_NORMAL": "#aaaa99", "TYPE_PSYCHIC": "#ff5599", "TYPE_GHOST": "#6666bb",
    "TYPE_DRAGON": "#7766ee", "TYPE_ELECTRIC": "#ffcc33", "TYPE_ICE": "#66ccff",
}

# Column A is deliberately mapped to source identifiers here. This is the only
# spreadsheet-specific encounter mapping; column B selects the encounter field.
LOCATION_MAPS = {
    "littleroot town": "MAP_LITTLEROOT_TOWN",
    "route 101": "MAP_ROUTE101",
    "oldale town": "MAP_OLDALE_TOWN",
    "oldale ruins 1f": "MAP_OLDALE_RUINS_1F",
    "route 103": "MAP_ROUTE103",
    "route 102": "MAP_ROUTE102",
    "petalburg city": "MAP_PETALBURG_CITY",
    "route 104": "MAP_ROUTE104",
    "petalburg woods": "MAP_PETALBURG_WOODS",
    "rustboro city": "MAP_RUSTBORO_CITY",
    "rustboro sandfront": "MAP_SAND_FRONT",
    "sandfront": "MAP_SAND_FRONT",
    "route 115": "MAP_ROUTE115",
    "route 116": "MAP_ROUTE116",
    "rusturf tunnel": "MAP_RUSTURF_TUNNEL",
    "petalburg grove (below petalburg city; requires cut)": "MAP_PETALBURG_GROVE",
    "petalburg grove": "MAP_PETALBURG_GROVE",
    "dewford town": "MAP_DEWFORD_TOWN",
    "route 107": "MAP_ROUTE107",
    "route 106": "MAP_ROUTE106",
    "dewford garden": "MAP_DEWFORD_GARDEN",
    "granite cave 1f": "MAP_GRANITE_CAVE_1F",
    "granite cave b1f": "MAP_GRANITE_CAVE_B1F",
    "granite cave b2f": "MAP_GRANITE_CAVE_B2F",
    "granite cave steven's room": "MAP_GRANITE_CAVE_STEVENS_ROOM",
    "route 109": "MAP_ROUTE109",
}
ENCOUNTER_TYPES = {
    "": ("land_mons", True),
    "grass": ("land_mons", True),
    "cave": ("land_mons", True),
    "sand": ("land_mons", True),
    "tree": ("shake_mons", False),
    "fishing": ("fishing_mons", False),
    "old rod": ("fishing_mons", False),
}
AUTOMATED_ROWS = {
    (location, encounter_type)
    for location, encounter_types in {
        "littleroot town": ("tree",),
        "route 101": ("grass", "tree"),
        "oldale town": ("tree", "fishing"),
        "oldale ruins 1f": ("cave", "fishing"),
        "route 103": ("grass", "tree", "fishing"),
        "route 102": ("grass", "tree", "fishing"),
        "petalburg city": ("tree", "fishing"),
        "route 104": ("grass", "tree", "fishing"),
        "petalburg woods": ("grass", "tree"),
        "rustboro city": ("tree",),
        "rustboro sandfront": ("sand",),
        "sandfront": ("fishing",),
        "route 115": ("tree", "fishing"),
        "route 116": ("grass", "tree"),
        "rusturf tunnel": ("cave",),
        "petalburg grove (below petalburg city; requires cut)": ("grass",),
        "petalburg grove": ("tree",),
        "dewford town": ("fishing",),
        "route 107": ("fishing",),
        "route 106": ("fishing",),
        "dewford garden": ("grass", "tree"),
        "granite cave 1f": ("cave",),
        "granite cave b1f": ("cave",),
        "granite cave b2f": ("",),
        "granite cave steven's room": ("",),
        "route 109": ("fishing",),
    }.items()
    for encounter_type in encounter_types
}
REGIONAL_SUFFIXES = {"ALOLA": "Alola", "GALAR": "Galar", "HISUI": "Hisui", "PALDEA": "Paldea"}


@dataclass(frozen=True)
class SpeciesInfo:
    name: str
    types: frozenset[str]
    evolutions: tuple[str, ...]


MACRO_DEFINED_SPECIES = {
    "SPECIES_FLABEBE": SpeciesInfo("Flabébé", frozenset({"TYPE_FAIRY"}), ()),
    "SPECIES_SCATTERBUG": SpeciesInfo("Scatterbug", frozenset({"TYPE_BUG"}), ("SPECIES_SPEWPA",)),
    "SPECIES_UNOWN": SpeciesInfo("Unown", frozenset({"TYPE_PSYCHIC"}), ()),
}


def _normalize(value: str) -> str:
    return " ".join(value.split()).strip().lower()


def _resolve_row_source(location: str, encounter_type: str) -> RowSource | None:
    key = (_normalize(location), _normalize(encounter_type))
    if key not in AUTOMATED_ROWS:
        return None
    field_name, include_monotype = ENCOUNTER_TYPES[key[1]]
    groups = ("old_rod", "good_rod") if key[1] == "fishing" else (("old_rod",) if key[1] == "old rod" else ())
    return RowSource(LOCATION_MAPS[key[0]], field_name, groups, include_monotype)


def _species_segments() -> Iterable[tuple[str, str]]:
    pattern = re.compile(r"^\s*\[(SPECIES_[A-Z0-9_]+)\]\s*=", re.MULTILINE)
    for path in sorted((REPO_ROOT / "src/data/pokemon/species_info").glob("*_families.h")):
        content = path.read_text(encoding="utf-8")
        matches = list(pattern.finditer(content))
        for index, match in enumerate(matches):
            end = matches[index + 1].start() if index + 1 < len(matches) else len(content)
            yield match.group(1), content[match.end():end]


def _display_species(species: str, source_name: str | None = None) -> str:
    if species == "SPECIES_NIDORAN_F":
        return "Nidoran-F"
    if species == "SPECIES_NIDORAN_M":
        return "Nidoran-M"
    parts = species.removeprefix("SPECIES_").split("_")
    suffix = REGIONAL_SUFFIXES.get(parts[-1])
    if source_name:
        name = source_name
    else:
        name = "-".join(part.title() for part in parts)
    if suffix and not name.endswith(suffix):
        name = f"{name}-{suffix}"
    return name


def _load_species_info(required_species: set[str]) -> dict[str, SpeciesInfo]:
    result: dict[str, SpeciesInfo] = dict(MACRO_DEFINED_SPECIES)
    type_macros: dict[str, tuple[str, ...]] = {}
    for path in sorted((REPO_ROOT / "src/data/pokemon/species_info").glob("*_families.h")):
        content = path.read_text(encoding="utf-8")
        for name, values in re.findall(r"#define\s+([A-Z0-9_]+_TYPES)\s+\{([^}]+)\}", content):
            type_macros.setdefault(name, tuple(dict.fromkeys(re.findall(r"\bTYPE_[A-Z_]+\b", values))))
    for species, segment in _species_segments():
        type_match = re.search(r"\.types\s*=\s*MON_TYPES\((.*?)\)", segment, re.DOTALL)
        macro_match = re.search(r"\.types\s*=\s*([A-Z0-9_]+_TYPES)\b", segment)
        if type_match:
            types = tuple(dict.fromkeys(re.findall(r"\bTYPE_[A-Z_]+\b", type_match.group(1))))
        elif macro_match and macro_match.group(1) in type_macros:
            types = type_macros[macro_match.group(1)]
        else:
            continue
        name_match = re.search(r'\.speciesName\s*=\s*_\("([^"]+)"\)', segment)
        evo_match = re.search(r"\.evolutions\s*=\s*EVOLUTION\((.*?)(?:\n\s*\.[A-Za-z]|\n\s*\})", segment, re.DOTALL)
        evolutions = tuple(dict.fromkeys(re.findall(r"\bSPECIES_[A-Z0-9_]+\b", evo_match.group(1)))) if evo_match else ()
        result[species] = SpeciesInfo(
            _display_species(species, name_match.group(1) if name_match else None),
            frozenset(types),
            evolutions,
        )
    constants = (REPO_ROOT / "include/constants/species.h").read_text(encoding="utf-8")
    aliases = dict(re.findall(r"^\s*(SPECIES_[A-Z0-9_]+)\s*=\s*(SPECIES_[A-Z0-9_]+)\s*,", constants, re.MULTILINE))
    for species in required_species.difference(result):
        target = aliases.get(species)
        if target in result:
            target_info = result[target]
            result[species] = SpeciesInfo(
                _display_species(species, target_info.name),
                target_info.types,
                target_info.evolutions,
            )
    missing = sorted(required_species.difference(result))
    if missing:
        raise ValueError(f"species info not found for: {', '.join(missing)}")
    return result


def _format_percent(value: float) -> str:
    rounded = round(value, 1)
    return f"{int(rounded)}%" if rounded.is_integer() else f"{rounded:g}%"


def _weighted_species(entries: list[dict[str, object]], slots: Iterable[int], rates: tuple[int, ...]) -> str:
    slots = tuple(slots)
    total = sum(rates[index] for index in slots)
    weights: Counter[str] = Counter()
    order: list[str] = []
    for index in slots:
        species = str(entries[index]["species"])
        if species == "SPECIES_NONE":
            continue
        if species not in weights:
            order.append(species)
        weights[species] += rates[index]
    return ", ".join(f"{{{species}}} ({_format_percent(100 * weights[species] / total)})" for species in order)


def _eligible_types(species: str, species_info: dict[str, SpeciesInfo], memo: dict[str, frozenset[str]]) -> frozenset[str]:
    if species in memo:
        return memo[species]
    info = species_info[species]
    result = set(info.types)
    memo[species] = frozenset(result)  # Break accidental evolution cycles.
    for evolution in info.evolutions:
        if evolution in species_info:
            result.update(_eligible_types(evolution, species_info, memo))
    memo[species] = frozenset(result)
    return memo[species]


def _monotype_species(entries: list[dict[str, object]], type_name: str, species_info: dict[str, SpeciesInfo]) -> str:
    memo: dict[str, frozenset[str]] = {}
    eligible = [str(entry["species"]) for entry in entries if entry["species"] != "SPECIES_NONE" and type_name in _eligible_types(str(entry["species"]), species_info, memo)]
    if not eligible:
        return "[None]"
    counts = Counter(eligible)
    order = tuple(dict.fromkeys(eligible))
    if len(set(counts.values())) == 1:
        return ", ".join(f"{{{species}}}" for species in order)
    total = len(eligible)
    return ", ".join(f"{{{species}}} ({_format_percent(100 * counts[species] / total)})" for species in order)


def _render_row(row_source: RowSource, encounters: EncounterSource, species_info: dict[str, SpeciesInfo]) -> tuple[str, list[tuple[int, str]]]:
    encounter = encounters.encounters_by_map.get(row_source.map_name)
    if encounter is None or row_source.field_name not in encounter:
        raise ValueError(f"{row_source.map_name} has no {row_source.field_name} encounter data")
    entries = encounter[row_source.field_name]["mons"]
    rates = encounters.rates_by_field[row_source.field_name]
    sections: list[str] = []
    colored_labels: list[tuple[int, str]] = []
    if row_source.field_name == "fishing_mons":
        for group in row_source.fishing_groups:
            label = group.replace("_", " ").title()
            sections.append(f"{label}: {_weighted_species(entries, encounters.fishing_groups[group], rates)}")
    else:
        slots = range(encounters.regular_land_slots) if row_source.field_name == "land_mons" else range(len(entries))
        prefix = "Non-Monotype: " if row_source.include_monotype else ""
        sections.append(prefix + _weighted_species(entries, slots, rates))
        if row_source.include_monotype:
            sections.append("")
            for line_start in range(0, len(TYPE_ORDER), 3):
                labels = []
                for type_name in TYPE_ORDER[line_start:line_start + 3]:
                    label = f"Mono-{type_name.removeprefix('TYPE_').title()}:"
                    labels.append(f"{label} {_monotype_species(entries, type_name, species_info)}")
                sections.append(" | ".join(labels))
    text = "\n".join(sections)
    for type_name in TYPE_ORDER:
        label = f"Mono-{type_name.removeprefix('TYPE_').title()}:"
        start = text.find(label)
        if start >= 0:
            colored_labels.append((start, TYPE_COLORS[type_name]))
    return text, colored_labels


def _replace_species_tokens(text: str, species_info: dict[str, SpeciesInfo]) -> str:
    return re.sub(r"\{(SPECIES_[A-Z0-9_]+)\}", lambda match: species_info[match.group(1)].name, text)


def _rgb(hex_color: str) -> dict[str, float]:
    value = hex_color.removeprefix("#")
    return {name: int(value[index:index + 2], 16) / 255 for name, index in (("red", 0), ("green", 2), ("blue", 4))}


def _text_format_runs(text: str, labels: list[tuple[int, str]]) -> list[dict[str, object]]:
    runs: list[dict[str, object]] = []
    for start, color in labels:
        label_end = text.index(":", start) + 1
        runs.extend((
            {"startIndex": start, "format": {"foregroundColorStyle": {"rgbColor": _rgb(color)}}},
            {"startIndex": label_end, "format": {}},
        ))
    return sorted(runs, key=lambda run: run["startIndex"])


def _colored_labels(text: str) -> list[tuple[int, str]]:
    result = []
    for type_name in TYPE_ORDER:
        label = f"Mono-{type_name.removeprefix('TYPE_').title()}:"
        start = text.find(label)
        if start >= 0:
            result.append((start, TYPE_COLORS[type_name]))
    return result


def _sheet_rows(values: list[list[str]]) -> list[tuple[int, str, str, RowSource]]:
    rows = []
    seen: set[tuple[str, str]] = set()
    for row_number, row in enumerate(values, 1):
        location = row[0] if row else ""
        encounter_type = row[1] if len(row) > 1 else ""
        source = _resolve_row_source(location, encounter_type)
        if source is None:
            continue
        key = (_normalize(location), _normalize(encounter_type))
        if key in seen:
            raise ValueError(f"duplicate encounter row key at row {row_number}: {location!r}, {encounter_type!r}")
        seen.add(key)
        rows.append((row_number, location, encounter_type, source))
    return rows


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--credentials", type=Path, default=os.environ.get("ELASTIC_EMERALD_GOOGLE_CREDENTIALS", Path(__file__).with_name("SecretKey.json")))
    parser.add_argument("--workbook", default="Pokemon Elastic Emerald Spreadsheet")
    parser.add_argument("--worksheet", default="EncountersUnreleased")
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args()

    encounters = load_encounter_source()
    required_species = {
        str(mon["species"])
        for encounter in encounters.encounters_by_map.values()
        for field in encounter.values()
        if isinstance(field, dict) and "mons" in field
        for mon in field["mons"]
        if mon["species"] != "SPECIES_NONE"
    }
    species_info = _load_species_info(required_species)

    if args.dry_run:
        for location, encounter_type in sorted(AUTOMATED_ROWS):
            source = _resolve_row_source(location, encounter_type)
            assert source is not None
            text, _ = _render_row(source, encounters, species_info)
            print(f"{location} | {encounter_type}\n{_replace_species_tokens(text, species_info)}\n")
        return

    if not args.credentials.is_file():
        parser.error(f"credentials file not found: {args.credentials}")
    import gspread

    workbook = gspread.service_account(filename=str(args.credentials)).open(args.workbook)
    sheet = workbook.worksheet(args.worksheet)
    rows = _sheet_rows(sheet.get("A:B"))
    requests = []
    for row_number, _, _, source in rows:
        tokenized_text, _ = _render_row(source, encounters, species_info)
        text = _replace_species_tokens(tokenized_text, species_info)
        requests.append({
            "updateCells": {
                "range": {
                    "sheetId": sheet.id,
                    "startRowIndex": row_number - 1,
                    "endRowIndex": row_number,
                    "startColumnIndex": 2,
                    "endColumnIndex": 3,
                },
                "rows": [{"values": [{
                    "userEnteredValue": {"stringValue": text},
                    "textFormatRuns": _text_format_runs(text, _colored_labels(text)),
                }]}],
                "fields": "userEnteredValue,textFormatRuns",
            }
        })
    if not requests:
        raise ValueError("no mapped encounter rows found")
    workbook.batch_update({"requests": requests})
    print(f"Updated {len(requests)} encounter cells in {args.worksheet}; columns A, B, and D were untouched.")


if __name__ == "__main__":
    main()
