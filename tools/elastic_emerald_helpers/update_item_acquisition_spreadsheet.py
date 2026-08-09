"""Update tagged item cells in ItemAcquisitionUnreleased from project sources."""

from __future__ import annotations

import argparse
import json
import os
import re
import sys
from dataclasses import dataclass
from pathlib import Path

if not __package__:
    sys.path.insert(0, str(Path(__file__).resolve().parents[2]))

from tools.elastic_emerald_helpers.source_data import REPO_ROOT

TAG_COLUMN = 6  # F
ITEM_COLUMN = 3  # C
TAG_HEADER = "Automation Tag"
ITEM_DISPLAY_OVERRIDES = {
    "ITEM_HM_CUT": ("HM01 Cut", "HM01 Cut"),
    "ITEM_TM_HELPING_HAND": ("TM09 Helping Hand", "TM09 Helping Hand"),
    "ITEM_TM_ROCK_TOMB": ("TM39 Rock Tomb", "TM39 Rock Tomb"),
}


@dataclass(frozen=True)
class BootstrapTag:
    location: str
    details: str
    tag: str
    current_item: str = ""


@dataclass(frozen=True)
class MapItem:
    item: str
    amount: int
    source_type: str


def _normalize(value: str) -> str:
    return " ".join(value.split()).strip().lower()


# These tags cover rows with stable, structured source anchors. Scripted rewards
# whose prose describes progression or mode branches remain intentionally untagged.
BOOTSTRAP_TAGS = (
    BootstrapTag("Player's Room / Pokemon Center", "Default PC Items", "item-array|src/player_pc.c|sNewGamePCItems"),
    BootstrapTag("Birch's Lab", "Held Item on Starter", "held-item|data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory|givemon"),
    BootstrapTag("Oldale Town", "New Berry Patches", "berry-trees|BERRY_TREE_OLDALE_IAPAPA,BERRY_TREE_OLDALE_AGUAV"),
    BootstrapTag("Oldale Mart", "Mart Items", "marts|data/maps/OldaleTown_Mart/scripts.pory|Oldale_BasicMartItems,Oldale_StockedMartItemsResourceEVless,Oldale_StockedMartItemsResourceEVs,Oldale_StockedMartItemsResourcefulEVless,Oldale_StockedMartItemsResourcefulEVs"),
    BootstrapTag("Oldale Ruins 1F", "Ground Item", "map-items|OldaleRuins_1F|FLAG_ITEM_OLDALE_RUINS_1F_ABILITY_CAPSULE"),
    BootstrapTag("Route 102", "Berry Patches", "berry-trees|BERRY_TREE_ROUTE_102_ORAN,BERRY_TREE_ROUTE_102_PECHA"),
    BootstrapTag("Route 102", "Ground Item", "map-items|Route102|FLAG_ITEM_ROUTE_102_BRAVE_MINT"),
    BootstrapTag("Petalburg Mart", "Mart Items", "marts|data/maps/PetalburgCity_Mart/scripts.pory|Petalburg_MartItemsResourceEVless,Petalburg_MartItemsResourceEVs,Petalburg_MartItemsResourcefulEVless,Petalburg_MartItemsResourcefulEVs"),
    BootstrapTag("Route 104, below Petalburg Woods", "Hidden Items near Youngster Billy. Gift from trainer Youngster Billy.", "gift-and-map|data/maps/Route104/scripts.pory|Route104_EventScript_BillyGift|Route104|FLAG_HIDDEN_ITEM_ROUTE_104_QUICK_BALL,FLAG_HIDDEN_ITEM_ROUTE_104_HEART_SCALE"),
    BootstrapTag("Route 104, below Petalburg Woods", "Hidden Item, guarded by Schoolkid Jimmy", "map-items|Route104|FLAG_HIDDEN_ITEM_ROUTE_104_ABILITY_PATCH"),
    BootstrapTag("Route 104, below Petalburg Woods", "Ground Item", "map-items|Route104|FLAG_ITEM_ROUTE_104_ABILITY_CAPSULE"),
    BootstrapTag("Petalburg Woods", "Hidden Item", "map-items|PetalburgWoods|FLAG_HIDDEN_ITEM_PETALBURG_WOODS_CALM_MINT"),
    BootstrapTag("Petalburg Woods", "Ground Item", "map-items|PetalburgWoods|FLAG_ITEM_PETALBURG_WOODS_HONEY"),
    BootstrapTag("Petalburg Woods", "Ground and Hidden Item near Youngster James", "map-items|PetalburgWoods|FLAG_HIDDEN_ITEM_PETALBURG_WOODS_NET_BALL,FLAG_ITEM_PETALBURG_WOODS_GRIP_CLAW"),
    BootstrapTag("Petalburg Woods, Cut Section", "Hidden Item", "map-items|PetalburgWoods|FLAG_HIDDEN_ITEM_PETALBURG_WOODS_BIG_MUSHROOM"),
    BootstrapTag("Petalburg Woods, Cut Section", "Ground Item", "map-items|PetalburgWoods|FLAG_ITEM_PETALBURG_WOODS_BIG_ROOT"),
    BootstrapTag("Petalburg Woods, Cut Section", "Ground Item and Hidden Item", "map-items|PetalburgWoods|FLAG_ITEM_PETALBURG_WOODS_GRASSY_SEED,FLAG_HIDDEN_ITEM_PETALBURG_WOODS_BALM_MUSHROOM"),
    BootstrapTag("Route 104, above Petalburg Woods", "Berry Patches, near Petalburg Woods", "berry-trees|BERRY_TREE_ROUTE_104_MICLE,BERRY_TREE_ROUTE_104_ORAN_1,BERRY_TREE_ROUTE_104_LANSAT"),
    BootstrapTag("Route 104, above Petalburg Woods", "Ground Item and Hidden Items", "map-items|Route104|FLAG_ITEM_ROUTE_104_SHED_SHELL,FLAG_HIDDEN_ITEM_ROUTE_104_GREAT_BALL,FLAG_HIDDEN_ITEM_ROUTE_104_ETHER"),
    BootstrapTag("Route 104, above Petalburg Woods, Cut Section", "Ground Item", "map-items|Route104|FLAG_ITEM_ROUTE_104_WIDE_LENS"),
    BootstrapTag("Route 104, above Petalburg Woods", "Berry Patches, below Rustboro", "berry-trees|BERRY_TREE_ROUTE_104_CHARTI,BERRY_TREE_ROUTE_104_LEPPA"),
    BootstrapTag("Rustboro City", "Ground Item", "map-items|RustboroCity|FLAG_ITEM_RUSTBORO_CITY_RED_CARD"),
    BootstrapTag("Rustboro Mart", "Mart Items", "marts|data/maps/RustboroCity_Mart/scripts.pory|Rustburo_MartItemsResourceEVless,Rustburo_MartItemsResourceEVs,Rustburo_MartItemsResourcefulEVless,Rustburo_MartItemsResourcefulEVs"),
    BootstrapTag("Route 115 (Rustboro side)", "Ground Item", "map-items|Route115|FLAG_ITEM_ROUTE_115_LUMINOUS_MOSS"),
    BootstrapTag("Rustboro Sandfront", "Ground Item", "map-items|SandFront|FLAG_ITEM_SANDFRONT_ICY_ROCK"),
    BootstrapTag("Route 116", "Ground Item", "map-items|Route116|FLAG_ITEM_ROUTE_116_REPEL"),
    BootstrapTag("Route 116, Cut Section", "Berry Patches and Ground Items", "berry-and-map|BERRY_TREE_ROUTE_116_CHOPLE,BERRY_TREE_ROUTE_116_KEE,BERRY_TREE_ROUTE_116_ORAN,BERRY_TREE_ROUTE_116_CHESTO_1|Route116|FLAG_ITEM_ROUTE_116_NAIVE_MINT,FLAG_ITEM_ROUTE_116_ETHER"),
    BootstrapTag("Rusturf Tunnel", "Ground Item", "map-items|RusturfTunnel|FLAG_ITEM_RUSTURF_TUNNEL_REPEAT_BALL"),
    BootstrapTag("Petalburg Grove (below Petalburg City; requires Cut)", "Ground Item", "map-items|PetalburgGrove|FLAG_ITEM_PETALBURG_GROVE_BALM_MUSHROOM"),
    BootstrapTag("Dewford Garden", "Berry patches", "berry-trees|BERRY_TREE_DEWFORD_GARDEN_ENIGMA,BERRY_TREE_DEWFORD_GARDEN_WIKI"),
    BootstrapTag("Route 106", "Hidden Item", "map-items|Route106|FLAG_HIDDEN_ITEM_ROUTE_106_DIVE_BALL", "Dive Ball"),
    BootstrapTag("Route 106", "Hidden Item", "map-items|Route106|FLAG_HIDDEN_ITEM_ROUTE_106_BOTTLE_CAP", "Bottle Cap"),
    BootstrapTag("Route 106", "Hidden Item", "map-items|Route106|FLAG_HIDDEN_ITEM_ROUTE_106_STARDUST", "Stardust"),
    BootstrapTag("Granite Cave 1F", "Ground Item", "map-items|GraniteCave_1F|FLAG_ITEM_GRANITE_CAVE_1F_ESCAPE_ROPE"),
    BootstrapTag("Granite Cave B1F", "Ground Item", "map-items|GraniteCave_B1F|FLAG_ITEM_GRANITE_CAVE_B1F_FLOAT_STONE"),
    BootstrapTag("Granite Cave B2F", "Hidden Item", "map-items|GraniteCave_B2F|FLAG_HIDDEN_ITEM_GRANITE_CAVE_B2F_EVERSTONE_1,FLAG_HIDDEN_ITEM_GRANITE_CAVE_B2F_EVERSTONE_2"),
    BootstrapTag("Birch's Lab", "Gift from Rival (after first Rival fight)", "script-items|data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory|LittlerootTown_ProfessorBirchsLab_EventScript_MayGivePokeBalls,LittlerootTown_ProfessorBirchsLab_EventScript_BrendanGivePokeBalls"),
    BootstrapTag("Oldale Town", "Fisherman Gift (expanded portion of Oldale to the right)", "script-items|data/maps/OldaleTown/scripts.pory|OldaleTown_EventScript_Fisherman"),
    BootstrapTag("Petalburg Woods", "Route Boss Cool Trainer Aurelio Reward", "script-items|data/maps/PetalburgWoods/scripts.pory|ResourceModeAurelioBerries,ResourcefulModeAurelioBerries"),
    BootstrapTag("Petalburg Woods, Cut Section", "Gift from Girl", "script-items|data/maps/PetalburgWoods/scripts.pory|PetalburgWoods_EventScript_Girl"),
    BootstrapTag("Route 104, above Petalburg Woods", "Boy NPC above Petalburg Woods", "script-items|data/maps/Route104/scripts.pory|Route104_EventScript_Boy2"),
    BootstrapTag("Route 104, Pretty Petal Flower Shop", "Daily Random Berry Girl", "random-berries|data/maps/Route104_PrettyPetalFlowerShop/scripts.inc|Route104_PrettyPetalFlowerShop_EventScript_RandomBerryGirl"),
    BootstrapTag("Route 104, Pretty Petal Flower Shop", "Gift from Girl", "script-items|data/maps/Route104_PrettyPetalFlowerShop/scripts.inc|Route104_PrettyPetalFlowerShop_EventScript_GiveWailmerPail"),
    BootstrapTag("Route 104, Outside Pretty Petal Flower Shop (After beating Roxanne)", "Gift from Girl who appears outside the Pretty Petal Flower Shop after getting the first badge", "script-items|data/maps/Route104/scripts.pory|Route104_EventScript_WhiteHerbFlorist"),
    BootstrapTag("Route 104, above Petalburg Woods", "Elder Lady Gift", "script-items|data/maps/Route104/scripts.pory|Route104_EventScript_ExpertF"),
    BootstrapTag("Rustboro City, Cutter's House", "Cutter NPC Gift", "script-items|data/maps/RustboroCity_CuttersHouse/scripts.pory|RustboroCity_CuttersHouse_EventScript_Cutter"),
    BootstrapTag("Rustboro Trainers School", "Teacher Gift", "script-items|data/maps/RustboroCity_PokemonSchool/scripts.pory|RustboroCity_PokemonSchool_EventScript_Teacher"),
    BootstrapTag("Rustboro Gym", "Gym TM", "script-items|data/maps/RustboroCity_Gym/scripts.pory|RustboroCity_Gym_EventScript_GiveRockTomb"),
    BootstrapTag("Rustboro City", "Devon Employee, after beating Rusturf Grunt", "script-items|data/maps/RustboroCity/scripts.pory|RustboroCity_EventScript_ReturnGoods"),
    BootstrapTag("Route 116", "Camper battle reward and Ground Item", "gift-and-map|data/maps/Route116/scripts.pory|Route116_EventScript_Elias|Route116|FLAG_ITEM_ROUTE_116_ABILITY_CAPSULE"),
    BootstrapTag("Granite Cave 1F", "Gift from Black Belts The rightmost Black Belt can only be fought after beating Brawly and the other two Black Belts.", "script-items|data/maps/GraniteCave_1F/scripts.pory|GraniteCave_1F_ProtectivePad_Kenji,GraniteCave_1F_MuscleBand_Daichi,GraniteCave_1F_BlackBelt_Leader_Ryuji"),
    BootstrapTag("Granite Cave: Steven's Room", "Ground Item and gift from Steven", "gift-and-map|data/maps/GraniteCave_StevensRoom/scripts.pory|Steven_Gives_Tera_Orb|GraniteCave_StevensRoom|FLAG_ITEM_GRANITE_ROCK_GEMS"),
)


def _generic_tag(mapping: BootstrapTag, counters: dict[tuple[str, str], int]) -> str:
    source_kind, *parts = mapping.tag.split("|")
    if source_kind == "item-array":
        return "DefaultPCItems"
    if source_kind == "held-item":
        return "StarterHeldItem"
    if source_kind == "marts":
        return "MartInventory"
    if source_kind == "berry-trees":
        base = "BerryPatches"
    elif source_kind == "random-berries":
        base = "NPCGift"
    elif source_kind == "script-items":
        details = _normalize(mapping.details)
        base = "TrainerReward" if "reward" in details or "gym tm" in details or "black belt" in details else "NPCGift"
    elif source_kind == "gift-and-map":
        base = "HiddenItems" if "youngster billy" in _normalize(mapping.details) else ("TrainerReward" if "reward" in _normalize(mapping.details) else "ItemAndGift")
    elif source_kind == "berry-and-map":
        base = "GroundItems"
    elif source_kind == "map-items":
        flags = parts[1].split(",")
        hidden = sum("HIDDEN_ITEM" in flag for flag in flags)
        ground = len(flags) - hidden
        if hidden and ground:
            base = "ItemGroup"
        elif hidden:
            base = "HiddenItem" if len(flags) == 1 else "HiddenItems"
        else:
            base = "GroundItem" if len(flags) == 1 else "GroundItems"
    else:
        raise ValueError(f"unsupported bootstrap source tag: {mapping.tag}")
    key = (_normalize(mapping.location), base)
    counters[key] = counters.get(key, 0) + 1
    return f"{base}{counters[key]}"


def _automation_mappings() -> tuple[dict[tuple[str, str], str], dict[str, str]]:
    counters: dict[tuple[str, str], int] = {}
    by_location_and_tag = {}
    legacy_to_generic = {}
    for mapping in BOOTSTRAP_TAGS:
        generic = _generic_tag(mapping, counters)
        key = (_normalize(mapping.location), generic)
        if key in by_location_and_tag:
            raise ValueError(f"duplicate generic automation mapping: {key}")
        by_location_and_tag[key] = mapping.tag
        legacy_to_generic[mapping.tag] = generic
    return by_location_and_tag, legacy_to_generic


AUTOMATION_MAPPINGS, LEGACY_TAGS = _automation_mappings()


def _item_names() -> dict[str, tuple[str, str]]:
    content = (REPO_ROOT / "src/data/items.h").read_text(encoding="utf-8")
    starts = list(re.finditer(r"^\s*\[(ITEM_[A-Z0-9_]+)\]\s*=", content, re.MULTILINE))
    result = {}
    for index, match in enumerate(starts):
        end = starts[index + 1].start() if index + 1 < len(starts) else len(content)
        block = content[match.end():end]
        singular = re.search(r'\.name\s*=\s*ITEM_NAME\("([^"]+)"\)', block)
        plural = re.search(r'\.pluralName\s*=\s*ITEM_PLURAL_NAME\("([^"]+)"\)', block)
        if singular:
            result[match.group(1)] = (singular.group(1), plural.group(1) if plural else "")
    return result


def _display_item_name(item: str, pluralize: bool, names: dict[str, tuple[str, str]]) -> str:
    singular, plural = ITEM_DISPLAY_OVERRIDES.get(item, names.get(item, (item.removeprefix("ITEM_").replace("_", " ").title(), "")))
    if not pluralize:
        return singular
    if not plural:
        if singular in {"Honey", "Luminous Moss"}:
            plural = singular
        elif singular.endswith("Berry"):
            plural = f"{singular[:-1]}ies"
        else:
            plural = f"{singular}s"
    return plural


def _display_item(item: str, amount: int, names: dict[str, tuple[str, str]]) -> str:
    name = _display_item_name(item, amount != 1, names)
    return name if amount == 1 else f"{amount} {name}"


def _map_item_entries(map_name: str, flags: list[str]) -> list[MapItem]:
    data = json.loads((REPO_ROOT / f"data/maps/{map_name}/map.json").read_text(encoding="utf-8"))
    found: dict[str, tuple[str, int, str]] = {}
    for event in data.get("object_events", []):
        if event.get("script") == "Common_EventScript_FindItem":
            amount = int(event.get("movement_range_x", 0)) or 1
            found[event["flag"]] = (event["trainer_sight_or_berry_tree_id"], amount, "Ground Item")
    for event in data.get("bg_events", []):
        if event.get("type") == "hidden_item":
            found[event["flag"]] = (event["item"], 1, "Hidden Item")
    missing = [flag for flag in flags if flag not in found]
    if missing:
        raise ValueError(f"{map_name} item flags not found: {', '.join(missing)}")
    return [MapItem(*found[flag]) for flag in flags]


def _map_items(map_name: str, flags: list[str], names: dict[str, tuple[str, str]]) -> str:
    grouped: dict[tuple[str, str], int] = {}
    for entry in _map_item_entries(map_name, flags):
        key = (entry.item, entry.source_type)
        grouped[key] = grouped.get(key, 0) + entry.amount
    rendered = []
    for (item, source_type), amount in grouped.items():
        rendered.append(f"{_display_item(item, amount, names)} ({source_type})" if len(flags) > 1 else _display_item(item, amount, names))
    return "\n".join(rendered)


def _extract_braced_block(content: str, marker: str) -> str:
    match = re.search(rf"\b{re.escape(marker)}\s*\{{", content)
    if match is None:
        raise ValueError(f"source block not found: {marker}")
    start = match.end()
    depth = 1
    for index in range(start, len(content)):
        if content[index] == "{":
            depth += 1
        elif content[index] == "}":
            depth -= 1
            if depth == 0:
                return content[start:index]
    raise ValueError(f"unterminated source block: {marker}")


def _item_array(path: str, label: str, names: dict[str, tuple[str, str]]) -> str:
    content = (REPO_ROOT / path).read_text(encoding="utf-8")
    match = re.search(rf"\b{re.escape(label)}\s*\[\]\[2\]\s*=\s*\{{(.*?)\n\}};", content, re.DOTALL)
    if match is None:
        raise ValueError(f"item array not found: {label} in {path}")
    entries = [(item, int(amount)) for item, amount in re.findall(r"\{\s*(ITEM_[A-Z0-9_]+)\s*,\s*(\d+)\s*\}", match.group(1)) if item != "ITEM_NONE"]
    return ", ".join(_display_item(item, amount, names) for item, amount in entries)


def _held_item(path: str, command: str, names: dict[str, tuple[str, str]]) -> str:
    content = (REPO_ROOT / path).read_text(encoding="utf-8")
    items = tuple(dict.fromkeys(re.findall(rf"\b{command}\s*\([^,]+,\s*[^,]+,\s*(ITEM_[A-Z0-9_]+)", content)))
    if len(items) != 1:
        raise ValueError(f"expected one unique held item in {path}, found: {items}")
    return _display_item(items[0], 1, names)


def _source_section(content: str, label: str) -> str:
    pory = re.search(rf"(?:^|\n)\s*(?:script\s+)?{re.escape(label)}\s*\{{", content)
    if pory:
        return _extract_braced_block(content, label)
    raw = re.search(rf"^{re.escape(label)}::\s*$", content, re.MULTILINE)
    if raw:
        following = re.search(r"^[A-Za-z_][A-Za-z0-9_]*::\s*$", content[raw.end():], re.MULTILINE)
        end = raw.end() + following.start() if following else len(content)
        return content[raw.end():end]
    raise ValueError(f"script label not found: {label}")


def _script_item_occurrences(path: str, labels: list[str]) -> dict[str, tuple[int, ...]]:
    content = (REPO_ROOT / path).read_text(encoding="utf-8")
    amounts: dict[str, list[int]] = {}
    order = []
    for label in labels:
        section = _source_section(content, label)
        for item, amount in re.findall(r"\bgiveitem\s*\(?\s*(ITEM_[A-Z0-9_]+)(?:\s*,\s*(\d+))?", section, re.IGNORECASE):
            if item not in amounts:
                order.append(item)
                amounts[item] = []
            amounts[item].append(int(amount or 1))
    if not order:
        raise ValueError(f"no gift items found in {path}: {', '.join(labels)}")
    return {item: tuple(amounts[item]) for item in order}


def _script_item_amounts(path: str, labels: list[str]) -> dict[str, tuple[int, ...]]:
    occurrences = _script_item_occurrences(path, labels)
    return {item: tuple(sorted(set(amounts))) for item, amounts in occurrences.items()}


def _script_items(path: str, labels: list[str], names: dict[str, tuple[str, str]]) -> str:
    rendered = []
    for item, item_amounts in _script_item_amounts(path, labels).items():
        if len(item_amounts) == 1:
            rendered.append(_display_item(item, item_amounts[0], names))
        else:
            name = _display_item_name(item, True, names)
            rendered.append(f"{'/'.join(map(str, item_amounts))} {name}")
    return ", ".join(rendered)


def _expect_one_item(items: dict[str, tuple[int, ...]], context: str) -> tuple[str, tuple[int, ...]]:
    if len(items) != 1:
        raise ValueError(f"expected one source-backed item for {context}, found: {tuple(items)}")
    return next(iter(items.items()))


def _random_berries(path: str, label: str, names: dict[str, tuple[str, str]]) -> str:
    content = (REPO_ROOT / path).read_text(encoding="utf-8")
    section = _source_section(content, label)
    match = re.search(r"giverandomberry\s+(BERRY_ID_[A-Z0-9_]+)\s*,\s*(BERRY_ID_[A-Z0-9_]+)", section)
    if match is None:
        raise ValueError(f"random berry range not found in {path}: {label}")
    constants = (REPO_ROOT / "include/constants/berries.h").read_text(encoding="utf-8")
    berry_ids = [f"BERRY_ID_{name}" for name in re.findall(r"^\s*F\(([A-Z0-9_]+)\)", constants, re.MULTILINE)]
    first, last = berry_ids.index(match.group(1)), berry_ids.index(match.group(2))
    items = [berry.replace("BERRY_ID_", "ITEM_") + "_BERRY" for berry in berry_ids[first:last + 1]]
    return "Random: " + ", ".join(_display_item(item, 1, names) for item in items)


def _marts(path: str, labels: list[str], names: dict[str, tuple[str, str]]) -> str:
    content = (REPO_ROOT / path).read_text(encoding="utf-8")
    sections = []
    for label in labels:
        items = re.findall(r"\bITEM_[A-Z0-9_]+\b", _extract_braced_block(content, label))
        sections.append(f"{label}:\n" + ", ".join(_display_item(item, 1, names) for item in items))
    return "\n\n".join(sections)


def _mart_item_lists(path: str, labels: list[str]) -> dict[str, list[str]]:
    content = (REPO_ROOT / path).read_text(encoding="utf-8")
    return {label: re.findall(r"\bITEM_[A-Z0-9_]+\b", _extract_braced_block(content, label)) for label in labels}


def _friendly_marts(path: str, labels: list[str], names: dict[str, tuple[str, str]]) -> str:
    inventories = _mart_item_lists(path, labels)
    variant_labels = labels[1:] if labels[0].endswith("BasicMartItems") else labels
    common = set(inventories[variant_labels[0]])
    for label in variant_labels[1:]:
        common.intersection_update(inventories[label])
    common_ordered = [item for item in inventories[variant_labels[0]] if item in common]
    ev_labels = [label for label in variant_labels if label.endswith("EVs")]
    resourceful_labels = [label for label in variant_labels if "Resourceful" in label]
    ev_common = set(inventories[ev_labels[0]]).intersection(*(inventories[label] for label in ev_labels[1:]))
    resourceful_common = set(inventories[resourceful_labels[0]]).intersection(*(inventories[label] for label in resourceful_labels[1:]))
    ev_only = [item for item in inventories[ev_labels[0]] if item in ev_common and item not in common]
    resourceful_only = [item for item in inventories[resourceful_labels[0]] if item in resourceful_common and item not in common]
    display = lambda items: ", ".join(_display_item(item, 1, names) for item in items)
    sections = []
    if variant_labels != labels:
        base = inventories[labels[0]]
        sections.append(f"Before Rival Portion: {display(base)}")
        always_added = [item for item in common_ordered if item not in base]
        sections.append("Added items after Rival Portion\n" + f"Always: {display(always_added)}")
    else:
        sections.append(f"Always: {display(common_ordered)}")
    if ev_only:
        sections.append(f"In EV Mode: {display(ev_only)}")
    if resourceful_only:
        sections.append(f"If not playing Resource Mode: {display(resourceful_only)}")
    return "\n\n".join(sections)


def _berry_tree_assignments() -> dict[str, str]:
    result = {}
    paths = [REPO_ROOT / "data/scripts/new_game.inc", *sorted((REPO_ROOT / "data/maps").glob("*/scripts.pory"))]
    pattern = re.compile(r"setberrytree\s*\(?\s*(BERRY_TREE_[A-Z0-9_]+)\s*,\s*ITEM_TO_BERRY\s*\(\s*(ITEM_[A-Z0-9_]+)")
    for path in paths:
        for tree, item in pattern.findall(path.read_text(encoding="utf-8")):
            result.setdefault(tree, item)
    return result


def _berry_yields() -> dict[str, tuple[int, int]]:
    content = (REPO_ROOT / "src/berry.c").read_text(encoding="utf-8")
    result = {}
    starts = list(re.finditer(r"^\s*\[BERRY_ID_([A-Z0-9_]+)\]\s*=", content, re.MULTILINE))
    for index, match in enumerate(starts):
        end = starts[index + 1].start() if index + 1 < len(starts) else len(content)
        block = content[match.end():end]
        minimum = re.search(r"\.minYield\s*=\s*YIELD_RATE\((\d+)", block)
        maximum = re.search(r"\.maxYield\s*=\s*YIELD_RATE\((\d+)", block)
        if minimum and maximum:
            result[f"ITEM_{match.group(1)}_BERRY"] = (int(minimum.group(1)), int(maximum.group(1)))
    return result


def _berry_trees(trees: list[str], names: dict[str, tuple[str, str]]) -> str:
    assignments = _berry_tree_assignments()
    yields = _berry_yields()
    missing = [tree for tree in trees if tree not in assignments]
    if missing:
        raise ValueError(f"berry tree assignments not found: {', '.join(missing)}")
    rendered = []
    seen = set()
    for tree in trees:
        item = assignments[tree]
        if item in seen:
            continue
        seen.add(item)
        minimum, maximum = yields[item]
        singular, plural = names[item]
        rendered.append(f"{minimum}-{maximum} {plural if maximum != 1 else singular}")
    return ", ".join(rendered)


def _render_source(source_tag: str, names: dict[str, tuple[str, str]]) -> str:
    parts = source_tag.split("|")
    if parts[0] == "map-items" and len(parts) == 3:
        return _map_items(parts[1], parts[2].split(","), names)
    if parts[0] == "item-array" and len(parts) == 3:
        return _item_array(parts[1], parts[2], names)
    if parts[0] == "held-item" and len(parts) == 3:
        return _held_item(parts[1], parts[2], names)
    if parts[0] == "marts" and len(parts) == 3:
        return _friendly_marts(parts[1], parts[2].split(","), names)
    if parts[0] == "berry-trees" and len(parts) == 2:
        return _berry_trees(parts[1].split(","), names)
    if parts[0] == "script-items" and len(parts) == 3:
        return _script_items(parts[1], parts[2].split(","), names)
    if parts[0] == "random-berries" and len(parts) == 3:
        return _random_berries(parts[1], parts[2], names)
    if parts[0] == "gift-and-map" and len(parts) == 5:
        gift = _script_items(parts[1], parts[2].split(","), names)
        ground = _map_items(parts[3], parts[4].split(","), names)
        return f"Gift: {gift}\nGround Item: {ground}"
    if parts[0] == "berry-and-map" and len(parts) == 4:
        berries = _berry_trees(parts[1].split(","), names)
        ground = _map_items(parts[2], parts[3].split(","), names)
        return f"Berry Patches: {berries}\n\n{ground}"
    raise ValueError(f"unsupported mapped source tag: {source_tag}")


def _render_tag(location: str, tag: str, names: dict[str, tuple[str, str]]) -> str:
    key = (_normalize(location), tag)
    source_tag = AUTOMATION_MAPPINGS.get(key)
    if source_tag is None:
        raise ValueError(f"unknown automation mapping for {location!r}: {tag}")
    rendered = _render_source(source_tag, names)

    if key == ("route 104, below petalburg woods", "HiddenItems1"):
        parts = source_tag.split("|")
        gifts = list(_script_item_amounts(parts[1], [parts[2]]).items())
        hidden = _map_item_entries(parts[3], parts[4].split(","))
        if len(gifts) != 2 or any(len(amounts) != 1 for _, amounts in gifts) or len(hidden) != 2:
            raise ValueError("Youngster Billy's presentation expects two gifts and two hidden items")
        return (
            f"{_display_item(hidden[0].item, hidden[0].amount, names)} (bottom hidden item in image)\n"
            f"{_display_item(hidden[1].item, hidden[1].amount, names)} (top hidden item in image)\n\n"
            "Beating Youngster Billy:\n"
            f"- before Petalburg Woods Aqua Grunt: {_display_item(gifts[1][0], gifts[1][1][0], names)}\n"
            f"- after Petalburg Woods Aqua Grunt: {_display_item(gifts[0][0], gifts[0][1][0], names)}"
        )
    if key == ("petalburg woods", "TrainerReward1"):
        parts = source_tag.split("|")
        labels = parts[2].split(",")
        resource_rewards = _script_item_occurrences(parts[1], [labels[0]])
        other_rewards = _script_item_occurrences(parts[1], [labels[1]])
        if resource_rewards.keys() != other_rewards.keys():
            raise ValueError("Aurelio's Resource and non-Resource rewards must contain the same items")
        resource_amounts = {amounts for amounts in resource_rewards.values()}
        other_amounts = {amounts for amounts in other_rewards.values()}
        if len(resource_amounts) != 1 or len(other_amounts) != 1:
            raise ValueError("Aurelio's rewards must use one shared quantity per mode")
        resource_amount = next(iter(resource_amounts))
        other_amount = next(iter(other_amounts))
        if len(resource_amount) != 1 or len(other_amount) != 1:
            raise ValueError("Aurelio's presentation expects one quantity per mode")
        return rendered + f"\n\n{resource_amount[0]} of each are given in Resource Mode; {other_amount[0]} otherwise"
    if key == ("route 104, pretty petal flower shop", "NPCGift1"):
        return rendered.replace("Random: ", "Random between ") + "\n\nIn Resource Mode, this triggers only once and does not regenerate daily"
    if key == ("route 104, outside pretty petal flower shop (after beating roxanne)", "NPCGift1"):
        parts = source_tag.split("|")
        item, amounts = _expect_one_item(_script_item_occurrences(parts[1], parts[2].split(",")), "White Herb florist")
        if len(amounts) != 3:
            raise ValueError("White Herb florist presentation expects Resource, Monotype Resource, and normal quantities")
        return (
            f"{_display_item_name(item, False, names)}\n\n"
            f"{amounts[0]} in non-Monotype Resource Mode; "
            f"{amounts[1]} in Monotype Resource Mode; {amounts[2]} otherwise"
        )
    if key == ("route 116", "TrainerReward1"):
        parts = source_tag.split("|")
        item, amounts = _expect_one_item(_script_item_occurrences(parts[1], [parts[2]]), "Camper Elias")
        ground = _map_item_entries(parts[3], parts[4].split(","))
        if len(amounts) != 3 or len(ground) != 1:
            raise ValueError("Camper Elias's presentation expects three reward quantities and one ground item")
        return (
            f"{_display_item_name(item, True, names)} for beating Camper Elias: "
            f"{amounts[0]} in non-Monotype Resource Mode; "
            f"{amounts[1]} in Monotype Resource Mode; {amounts[2]} otherwise\n\n"
            f"{_display_item(ground[0].item, ground[0].amount, names)} ({ground[0].source_type})"
        )
    if key == ("granite cave 1f", "TrainerReward1"):
        parts = source_tag.split("|")
        labels = parts[2].split(",")
        rewards = [_expect_one_item(_script_item_amounts(parts[1], [label]), label) for label in labels]
        if any(len(amounts) != 1 for _, amounts in rewards):
            raise ValueError("Black Belt presentation expects one quantity per reward")
        return (
            f"{_display_item(rewards[1][0], rewards[1][1][0], names)} for beating the leftmost Black Belt\n"
            f"{_display_item(rewards[0][0], rewards[0][1][0], names)} for beating the centermost Black Belt\n"
            f"{_display_item(rewards[2][0], rewards[2][1][0], names)} for beating the rightmost Black Belt"
        )
    if key == ("granite cave: steven's room", "ItemAndGift1"):
        parts = source_tag.split("|")
        gift_item, gift_amounts = _expect_one_item(_script_item_amounts(parts[1], [parts[2]]), "Steven's gift")
        ground = _map_item_entries(parts[3], parts[4].split(","))
        if len(gift_amounts) != 1 or len(ground) != 1:
            raise ValueError("Steven's Room presentation expects one gift and one ground item")
        return (
            f"Ground Item: {_display_item(ground[0].item, ground[0].amount, names)}\n"
            f"Gift from Steven: {_display_item(gift_item, gift_amounts[0], names)}"
        )
    if key == ("route 104, above petalburg woods", "ItemGroup1"):
        parts = source_tag.split("|")
        items = _map_item_entries(parts[1], parts[2].split(","))
        if len(items) != 3:
            raise ValueError("Route 104 item-group presentation expects three mapped items")
        return (
            f"{_display_item(items[0].item, items[0].amount, names)} ({items[0].source_type})\n\n"
            f"{_display_item(items[1].item, items[1].amount, names)} (bottom {items[1].source_type} in image)\n"
            f"{_display_item(items[2].item, items[2].amount, names)} (top {items[2].source_type} in image)"
        )
    return rendered


def _bootstrap_tag(row: list[str]) -> str | None:
    location = _normalize(row[0] if row else "")
    details = _normalize(row[1] if len(row) > 1 else "")
    current_item = _normalize(row[2] if len(row) > 2 else "")
    matches = [mapping for mapping in BOOTSTRAP_TAGS if _normalize(mapping.location) == location and _normalize(mapping.details) == details and (not mapping.current_item or _normalize(mapping.current_item) == current_item)]
    if len(matches) > 1:
        raise ValueError(f"ambiguous bootstrap mapping: {row[:3]}")
    if not matches:
        return None
    return LEGACY_TAGS[matches[0].tag]


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--credentials", type=Path, default=os.environ.get("ELASTIC_EMERALD_GOOGLE_CREDENTIALS", Path(__file__).with_name("SecretKey.json")))
    parser.add_argument("--workbook", default="Pokemon Elastic Emerald Spreadsheet")
    parser.add_argument("--worksheet", default="ItemAcquisitionUnreleased")
    parser.add_argument("--initialize-tags", action="store_true", help="populate Column F tags for recognized current rows")
    parser.add_argument("--dry-run", action="store_true", help="read the sheet and print proposed changes without writing")
    args = parser.parse_args()
    if not args.credentials.is_file():
        parser.error(f"credentials file not found: {args.credentials}")

    import gspread

    workbook = gspread.service_account(filename=str(args.credentials)).open(args.workbook)
    sheet = workbook.worksheet(args.worksheet)
    values = sheet.get("A:F")
    names = _item_names()
    requests = []
    if args.initialize_tags:
        header_added = False
        for row_number, row in enumerate(values, 1):
            existing_tag = row[5].strip() if len(row) > 5 else ""
            tag = _bootstrap_tag(row)
            if tag and existing_tag != tag:
                requests.append({"range": f"F{row_number}", "values": [[tag]]})
                if args.dry_run:
                    print(f"row {row_number}: {tag}")
        if len(values) > 0 and (len(values[0]) < TAG_COLUMN or not values[0][TAG_COLUMN - 1]):
            requests.insert(0, {"range": "F1", "values": [[TAG_HEADER]]})
            header_added = True
        if args.dry_run:
            print(f"Tag updates: {len(requests)}; no spreadsheet changes made.")
            return
        if not requests:
            print("No tag updates needed.")
            return
        sheet.batch_update(requests, value_input_option="RAW")
        print(f"Initialized {len(requests) - int(header_added)} automation tags in {args.worksheet}; Column C was untouched.")
        return

    mapped = 0
    for row_number, row in enumerate(values, 1):
        tag = row[5].strip() if len(row) > 5 else ""
        if not tag or tag == TAG_HEADER:
            continue
        rendered = _render_tag(row[0] if row else "", tag, names)
        mapped += 1
        if args.dry_run:
            print(f"row {row_number} [{tag}]\n{rendered}\n")
        else:
            requests.append({"range": f"C{row_number}", "values": [[rendered]]})

    if args.dry_run:
        print(f"Mapped rows: {mapped}; no spreadsheet changes made.")
        return
    if not requests:
        raise ValueError("no tag or item updates generated")
    sheet.batch_update(requests, value_input_option="RAW")
    print(f"Applied {len(requests)} updates in {args.worksheet}; mapped item rows: {mapped}.")


if __name__ == "__main__":
    main()
