#!/usr/bin/env python3
"""Recheck the selected two-hit cases under the opponent BST and move filters."""

import re

from analyze_baxcalibur_matchups import (
    DATA, POKEMON, Case, base_bounds, entry, mega_result, source, species, verify_inputs,
)
from analyze_baxcalibur_protect import species_profile
from tools.elastic_emerald_helpers.CalcAnalysis.analyze_baxcalibur_special_matchups import screen

PHYSICAL_CASES = (
    Case("PINSIR", "HYPER_CUTTER", "None", ("THROAT_CHOP", "STONE_EDGE", "X_SCISSOR", "EARTHQUAKE")),
    Case("GALLADE_MEGA", "INNER_FOCUS", "Galladite", ("LEAF_BLADE", "STONE_EDGE", "EARTHQUAKE", "X_SCISSOR")),
    Case("MARSHADOW", "TECHNICIAN", "Leftovers", ("THROAT_CHOP", "STONE_EDGE", "SPECTRAL_THIEF", "POLTERGEIST")),
    Case("ANNIHILAPE", "INNER_FOCUS", "Expert Belt", ("SEED_BOMB", "DRAIN_PUNCH", "STONE_EDGE", "EARTHQUAKE"),
         super_effective_boost=4915),
    Case("EXCADRILL", "MOLD_BREAKER", "Ground Gem", ("X_SCISSOR", "EARTHQUAKE", "THROAT_CHOP", "POISON_JAB"),
         "GROUND", 5530),
    Case("GREAT_TUSK", "PROTOSYNTHESIS", "Ground Gem", ("ICE_SPINNER", "HIGH_HORSEPOWER", "THROAT_CHOP", "GIGA_IMPACT"),
         "GROUND", 5530),
)
SPECIAL_CASES = (
    (Case("BLASTOISE", "RAIN_DISH", "Fighting Gem", ("SURF", "AURA_SPHERE", "DRAGON_PULSE"),
          "FIGHTING", 5530), "", "dragon gem"),
    (Case("ZERAORA", "VOLT_ABSORB", "Sitrus Berry", ("GRASS_KNOT", "AURA_SPHERE")), "sitrus", "dragon boost"),
    (Case("VICTINI", "VICTORY_STAR", "Leftovers", ("GRASS_KNOT", "DAZZLING_GLEAM", "FLAMETHROWER")),
     "leftovers", "dragon boost"),
)


def bst(name):
    profile = species_profile(name)
    fields = ("HP", "Attack", "Defense", "SpAttack", "SpDefense", "Speed")
    for field in fields:
        value = re.search(rf"\.base{field}\s*=\s*([^,]+),", profile)[1].strip()
        if value.endswith("_SP_DEF"):
            # The stat tables can name a generation-dependent expression.
            resource = next(source(path) for path in (POKEMON / "species_info").glob("*.h")
                            if f"#define {value} " in source(path))
            value = re.search(rf"#define {value}[ \t]+([^\n]+)", resource)[1]
        if "?" in value:
            value = value.split("?")[1].split(":")[0].strip()
        yield int(value)


def check_moves(case, special=False):
    base_name = case.species.removesuffix("_MEGA")
    if sum(bst(base_name)) > 600:
        raise ValueError(f"{case.species} exceeds the base-form BST cap")
    # Mega Gallade uses Gallade's learnset and has already evolved on the opponent's side.
    profile = species_profile(base_name)
    if f"ABILITY_{case.ability}" not in species_profile(case.species):
        raise ValueError(f"{case.species} lacks {case.ability}")
    teachable = re.search(r"\.teachableLearnset\s*=\s*(\w+)", profile)[1]
    level_up = re.search(r"\.levelUpLearnset\s*=\s*(\w+)", profile)[1]
    array = r"\b{}\[\]\s*=\s*\{{([^}}]*)"
    taught = re.search(array.format(teachable), source(POKEMON / "teachable_learnsets.h"))[1]
    levels = "\n".join(source(path) for path in (POKEMON / "level_up_learnsets").glob("*.h"))
    learned = re.search(array.format(level_up), levels)[1]
    available = set(re.findall(r"\bMOVE_(\w+)", taught))
    available.update(name for level, name in re.findall(r"LEVEL_UP_MOVE\(\s*(\d+),\s*MOVE_(\w+)\)", learned)
                     if int(level) <= 50)
    if missing := set(case.moves) - available:
        raise ValueError(f"{base_name} lacks {sorted(missing)} in the active learnset")
    for name in case.moves:
        body = entry(source(DATA / "moves_info.h"), "MOVE_" + name)
        if re.search(r"\.(?:attack|defense|spDefense|spDef)\s*=|MOVE_EFFECT_FLINCH", body):
            raise ValueError(f"Recheck stat effects for {name}")
        power = int(re.search(r"\.power\s*=\s*(?:[^,\n]+\?\s*)?(\d+)", body)[1])
        if power < 80 and name not in ("DRAIN_PUNCH", "GRASS_KNOT"):
            raise ValueError(f"Recheck power for {name}")
    if base_name == case.species:
        verify_inputs(case, special=special)


def main():
    mega = species("BAXCALIBUR_MEGA")
    for case in PHYSICAL_CASES:
        check_moves(case)
        result = mega_result(case, mega.attack, mega.defense)
        print(case.species, sum(bst(case.species)), case.moves, result)
        if case.item == "Leftovers":
            print("KO target with Leftovers:", result.foe_hp + result.foe_hp // 16)
            assert sum(result.damage) >= result.foe_hp + result.foe_hp // 16
        bounds = base_bounds(case)
        margins = [margin for margin in bounds.values() if margin is not None]
        print("Base best KO margin after surviving:", max(margins, default=None))
    for case, healing, alternative in SPECIAL_CASES:
        check_moves(case, special=True)
        print(case.species, sum(bst(case.species)), case.moves, screen(case, healing, mega=True)[0])
        for item in ("assault vest", alternative):
            print(item, screen(case, healing, item=item)[1])


if __name__ == "__main__":
    main()
