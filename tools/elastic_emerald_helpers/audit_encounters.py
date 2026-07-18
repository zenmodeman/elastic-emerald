"""Report low-frequency and monotype-only encounters for an early-game map set."""

from __future__ import annotations

import json
from collections import defaultdict

from .source_data import REPO_ROOT

APPLICABLE_MAPS = [
    "MAP_LITTLEROOT_TOWN", "MAP_ROUTE101", "MAP_OLDALE_TOWN", "MAP_OLDALE_RUINS_1F",
    "MAP_ROUTE102", "MAP_ROUTE103", "MAP_ROUTE104", "MAP_PETALBURG_CITY",
    "MAP_PETALBURG_GROVE", "MAP_PETALBURG_FOREST", "MAP_RUSTBORO_CITY", "MAP_ROUTE_115",
    "MAP_SAND_FRONT", "MAP_ROUTE116", "MAP_RUSTURF_TUNNEL", "MAP_DEWFORD_TOWN",
    "MAP_ROUTE106", "MAP_ROUTE107", "MAP_DEWFORD_GARDEN",
]
CLUSTERED_MAPS = [["MAP_GRANITE_CAVE_1F", "MAP_GRANITE_CAVE_B1F", "MAP_GRANITE_CAVE_B2F", "MAP_GRANITE_CAVE_STEVENS_ROOM"]]
NO_LAND_MAPS = {"MAP_ROUTE_115"}
SEEN_SPECIES: set[str] = set()


def _combine_max(dicts: list[dict[str, float]]) -> defaultdict[str, float]:
    result: defaultdict[str, float] = defaultdict(float)
    for values in dicts:
        for species, value in values.items():
            result[species] = max(result[species], value)
    return result


def _weighted(entries: list[dict[str, object]], weights: list[float]) -> defaultdict[str, float]:
    result: defaultdict[str, float] = defaultdict(float)
    for entry, weight in zip(entries, weights):
        species = entry["species"]
        if species != "SPECIES_NONE":
            result[species] += weight
    return result


def _map_values(encounters: list[dict[str, object]], map_name: str) -> defaultdict[str, float]:
    match = next((entry for entry in encounters if entry["map"] == map_name), {})
    methods = []
    if map_name not in NO_LAND_MAPS and "land_mons" in match:
        mons = match["land_mons"]["mons"]
        SEEN_SPECIES.update(mon["species"] for mon in mons if mon["species"] != "SPECIES_NONE")
        methods.append(_weighted(mons[:8], [0.125] * 8))
    if "fishing_mons" in match:
        mons = match["fishing_mons"]["mons"]
        SEEN_SPECIES.update(mon["species"] for mon in mons if mon["species"] != "SPECIES_NONE")
        methods.extend((_weighted(mons[:2], [0.6, 0.4]), _weighted(mons[2:5], [0.5, 0.25, 0.25])))
    if "shake_mons" in match:
        mons = match["shake_mons"]["mons"]
        SEEN_SPECIES.update(mon["species"] for mon in mons if mon["species"] != "SPECIES_NONE")
        methods.append(_weighted(mons[:5], [0.2] * 5))
    return _combine_max(methods)


def main() -> None:
    data = json.loads((REPO_ROOT / "src/data/wild_encounters.json").read_text(encoding="utf-8"))
    encounters = data["wild_encounter_groups"][0]["encounters"]
    totals: defaultdict[str, float] = defaultdict(float)
    for map_name in APPLICABLE_MAPS:
        for species, value in _map_values(encounters, map_name).items():
            totals[species] += value
    for cluster in CLUSTERED_MAPS:
        for species, value in _combine_max([_map_values(encounters, name) for name in cluster]).items():
            totals[species] += value
    units = {species: round(value / 0.25, 2) for species, value in totals.items()}
    print("Below minimum encounter threshold:")
    print(dict(sorted((item for item in units.items() if item[1] < 1), key=lambda item: item[0])))
    print("\nMonotype-only encounters:")
    print(sorted(SEEN_SPECIES.difference(totals)))
    print("\nAll encounter units:")
    print(sorted(units.items(), key=lambda item: item[1], reverse=True))


if __name__ == "__main__":
    main()

