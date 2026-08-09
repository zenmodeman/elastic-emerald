"""Summarize species available by the current early-game progression point."""

from __future__ import annotations

import argparse
import json
import re
import sys
from collections import defaultdict
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable

if __package__:
    from .source_data import REPO_ROOT
else:
    # Support direct execution in addition to the preferred package invocation.
    sys.path.insert(0, str(Path(__file__).resolve().parents[2]))
    from tools.elastic_emerald_helpers.source_data import REPO_ROOT


@dataclass(frozen=True)
class Location:
    """One independently counted location, optionally backed by multiple maps."""

    name: str
    maps: tuple[str, ...]
    excluded_methods: frozenset[str] = frozenset()


# MANUAL configuration: need to define what it currently available
#The tuple form such as in Granite Cave clusters different maps of the same map section
AVAILABLE_LOCATIONS = (
    *(Location(re.sub(r"(?<=[A-Za-z])(?=\d)", " ", name.removeprefix("MAP_").replace("_", " ")).title(), (name,)) for name in (
        "MAP_LITTLEROOT_TOWN", "MAP_ROUTE101", "MAP_OLDALE_TOWN", "MAP_OLDALE_RUINS_1F",
        "MAP_ROUTE102", "MAP_ROUTE103", "MAP_ROUTE104", "MAP_PETALBURG_CITY",
        "MAP_PETALBURG_GROVE", "MAP_PETALBURG_WOODS", "MAP_RUSTBORO_CITY",
        "MAP_SAND_FRONT", "MAP_ROUTE116", "MAP_RUSTURF_TUNNEL", "MAP_DEWFORD_TOWN",
        "MAP_ROUTE106", "MAP_ROUTE107", "MAP_DEWFORD_GARDEN", "MAP_ROUTE109",
    )),
    Location("Route 115 fishing area", ("MAP_ROUTE115",), frozenset({"land_mons"})),
    Location("Granite Cave", (
        "MAP_GRANITE_CAVE_1F", "MAP_GRANITE_CAVE_B1F", "MAP_GRANITE_CAVE_B2F",
        "MAP_GRANITE_CAVE_STEVENS_ROOM",
    )),
)

# Methods currently usable at this progression point. Surf, Rock Smash, and the
# Super Rod can be added here when obtained; their source-defined slots need no code changes.
AVAILABLE_METHODS = ("land_mons", "shake_mons", "old_rod", "good_rod")
FISHING_METHODS = frozenset({"old_rod", "good_rod", "super_rod"})
METHOD_LABELS = {
    "land_mons": "walking",
    "shake_mons": "shaking",
    "old_rod": "Old Rod",
    "good_rod": "Good Rod",
}
MINIMUM_ENCOUNTER_UNITS = 1.0
ENCOUNTER_UNIT_CHANCE = 0.25
NONE_SPECIES = "SPECIES_NONE"


@dataclass(frozen=True)
class EncounterSource:
    encounters_by_map: dict[str, dict[str, object]]
    rates_by_field: dict[str, tuple[int, ...]]
    fishing_groups: dict[str, tuple[int, ...]]
    regular_land_slots: int


@dataclass
class LocationAvailability:
    standard: defaultdict[str, float]
    candidates: set[str]


def load_encounter_source() -> EncounterSource:
    data = json.loads((REPO_ROOT / "src/data/wild_encounters.json").read_text(encoding="utf-8"))
    group = next(group for group in data["wild_encounter_groups"] if group.get("for_maps"))
    fields = {field["type"]: field for field in group["fields"]}
    land_source = (REPO_ROOT / "src/wild_encounter.c").read_text(encoding="utf-8")
    land_slots = re.search(r"^#define MAX_REGULAR_LAND_SLOTS\s+(\d+)\s*$", land_source, re.MULTILINE)
    if land_slots is None:
        raise ValueError("MAX_REGULAR_LAND_SLOTS not found in src/wild_encounter.c")
    encounters_by_map: dict[str, dict[str, object]] = {}
    for entry in group["encounters"]:
        # Runtime lookup uses the first matching map header as well.
        encounters_by_map.setdefault(entry["map"], entry)
    return EncounterSource(
        encounters_by_map=encounters_by_map,
        rates_by_field={name: tuple(field["encounter_rates"]) for name, field in fields.items()},
        fishing_groups={name: tuple(slots) for name, slots in fields["fishing_mons"]["groups"].items()},
        regular_land_slots=int(land_slots.group(1)),
    )


def _species(entries: Iterable[dict[str, object]]) -> set[str]:
    return {str(entry["species"]) for entry in entries if entry["species"] != NONE_SPECIES}


def _weighted(entries: list[dict[str, object]], slots: Iterable[int], rates: tuple[int, ...]) -> defaultdict[str, float]:
    selected_slots = tuple(slots)
    total_rate = sum(rates[index] for index in selected_slots)
    result: defaultdict[str, float] = defaultdict(float)
    for index in selected_slots:
        species = str(entries[index]["species"])
        if species != NONE_SPECIES:
            result[species] += rates[index] / total_rate
    return result


def _combine_max(groups: Iterable[dict[str, float]]) -> defaultdict[str, float]:
    result: defaultdict[str, float] = defaultdict(float)
    for values in groups:
        for species, value in values.items():
            result[species] = max(result[species], value)
    return result


def _method_availability(source: EncounterSource, encounter: dict[str, object], method: str) -> LocationAvailability:
    if method in FISHING_METHODS:
        field_name = "fishing_mons"
        slots = source.fishing_groups[method]
        # Monotype fishing considers every slot through the best available rod.
        candidate_slots = range(max(slots) + 1)
    else:
        field_name = method
        entries = encounter.get(field_name, {}).get("mons", [])
        slots = range(source.regular_land_slots) if method == "land_mons" else range(len(entries))
        candidate_slots = range(len(entries))

    field = encounter.get(field_name)
    if not field:
        return LocationAvailability(defaultdict(float), set())
    entries = field["mons"]
    return LocationAvailability(
        standard=_weighted(entries, slots, source.rates_by_field[field_name]),
        candidates=_species(entries[index] for index in candidate_slots),
    )


def _location_availability(source: EncounterSource, location: Location) -> LocationAvailability:
    by_map = []
    candidates: set[str] = set()
    methods = tuple(method for method in AVAILABLE_METHODS if method not in location.excluded_methods)
    for map_name in location.maps:
        encounter = source.encounters_by_map.get(map_name, {})
        map_methods = [_method_availability(source, encounter, method) for method in methods]
        by_map.append(_combine_max(method.standard for method in map_methods))
        candidates.update(*(method.candidates for method in map_methods))
    return LocationAvailability(_combine_max(by_map), candidates)


def _validate_locations(source: EncounterSource) -> None:
    missing = sorted(
        map_name
        for location in AVAILABLE_LOCATIONS
        for map_name in location.maps
        if map_name not in source.encounters_by_map
    )
    if missing:
        raise ValueError(f"configured maps missing from wild encounter data: {', '.join(missing)}")


def _encounter_units(chance: float) -> float:
    return round(chance / ENCOUNTER_UNIT_CHANCE, 2)


def _display_species(species: str) -> str:
    return species.removeprefix("SPECIES_").replace("_", " ").title()


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--by-location", action="store_true", help="also list standard encounters for each location")
    args = parser.parse_args()

    source = load_encounter_source()
    _validate_locations(source)
    totals: defaultdict[str, float] = defaultdict(float)
    all_candidates: set[str] = set()
    availability_by_location = []
    for location in AVAILABLE_LOCATIONS:
        availability = _location_availability(source, location)
        availability_by_location.append((location, availability))
        all_candidates.update(availability.candidates)
        for species, chance in availability.standard.items():
            totals[species] += chance

    units = {species: _encounter_units(chance) for species, chance in totals.items()}
    below_minimum = dict(sorted(
        ((species, value) for species, value in units.items() if value < MINIMUM_ENCOUNTER_UNITS),
        key=lambda item: item[0],
    ))
    monotype_only = sorted(all_candidates.difference(totals))

    print("Access assumptions:")
    methods = ", ".join(METHOD_LABELS[method] for method in AVAILABLE_METHODS)
    print(f"  {len(AVAILABLE_LOCATIONS)} locations; methods: {methods}")
    print("  Excluded for now: surfing, rock smash, super rod")
    print(f"\nStandard-mode species available: {len(totals)}")
    print(f"Monotype-only species available: {len(monotype_only)}")
    print("\nBelow minimum encounter threshold:")
    print({_display_species(species): value for species, value in below_minimum.items()})
    print("\nMonotype-only encounters:")
    print([_display_species(species) for species in monotype_only])
    print("\nAll standard encounter units:")
    print([(_display_species(species), value) for species, value in sorted(units.items(), key=lambda item: (-item[1], item[0]))])

    if args.by_location:
        print("\nStandard encounters by location:")
        for location, availability in availability_by_location:
            names = sorted(_display_species(species) for species in availability.standard)
            print(f"  {location.name}: {', '.join(names) if names else '(none)'}")


if __name__ == "__main__":
    main()
