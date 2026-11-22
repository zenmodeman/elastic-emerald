#!/usr/bin/env python3
"""Reproduce the level-50 Glaive Rush, Protect, Glaive Rush calculations.

This is a design study that assumes Baxcalibur can be given Protect.
"""

import re
from dataclasses import dataclass
from functools import cache

from analyze_baxcalibur_matchups import (
    DATA, HALF, ITEMS, LINES, ONE, ONE_AND_HALF, POKEMON, Case, damage, effectiveness,
    entry, half_down, move, outgoing, source, species, spreads, stat, verify_inputs,
)


@dataclass(frozen=True)
class ProtectCase:
    opponent: Case
    healing: str = ""


CASES = (
    ProtectCase(Case("MEW", "SYNCHRONIZE", "Twisted Spoon",
                     ("AIR_CUTTER", "PSYCHIC_NOISE", "SURF", "LEAF_STORM"), "PSYCHIC", 4915)),
    ProtectCase(Case("NECROZMA", "PRISM_ARMOR", "Sitrus Berry",
                     ("SHOCK_WAVE", "EXPANDING_FORCE", "HYPER_VOICE", "SWIFT")), "sitrus"),
    ProtectCase(Case("UXIE", "LEVITATE", "Leftovers",
                     ("SHOCK_WAVE", "DAZZLING_GLEAM", "GIGA_DRAIN", "SWIFT")), "leftovers"),
)


@cache
def species_profile(name):
    return entry(next(source(path) for path in (POKEMON / "species_info").glob("*.h")
                      if f"[SPECIES_{name}]" in source(path)), "SPECIES_" + name)


@cache
def special_base_stat(name, field):
    return int(re.search(rf"\.base{field}\s*=\s*(\d+)", species_profile(name))[1])


@cache
def special_damage(case, name, defense, resist=False, vulnerable=False):
    attack = entry(source(DATA / "moves_info.h"), "MOVE_" + name)
    power = re.search(r"\.power\s*=\s*(?:[^,\n]+\?\s*)?(\d+)", attack)[1]
    if name == "GRASS_KNOT":
        for defender in ("BAXCALIBUR", "BAXCALIBUR_MEGA"):
            weight = int(re.search(r"\.weight\s*=\s*(\d+)", species_profile(defender))[1])
            if weight < 2000:
                raise ValueError("Recheck Grass Knot power for this Baxcalibur weight")
        power = 120
    move_type = re.search(r"\.type\s*=\s*TYPE_(\w+)", attack)[1]
    sp_attack = special_base_stat(case.species, "SpAttack")
    factor = effectiveness(move_type, species("BAXCALIBUR").types)
    resist = resist and (factor >= 2 * ONE or move_type == "NORMAL")
    return damage(int(power), stat(sp_attack, 180), defense, move_type in species(case.species).types,
                  factor, 100, True, case.power_boost if move_type == case.item_type else ONE,
                  HALF if resist else ONE, vulnerable)


def dragon_hits(case, attack, item):
    first = outgoing(case, "GLAIVE_RUSH", attack, item)
    second = outgoing(case, "GLAIVE_RUSH", attack, "none" if item == "dragon gem" else item)
    return first, second


def remaining_foe_hp(healing, hp, chip, first, final_move_heal):
    remaining = hp - chip - first
    if remaining <= 0:
        return 0
    if healing == "leftovers":
        remaining = min(hp, remaining + 2 * (hp // 16))
    if healing == "sitrus" and remaining <= hp // 2:
        remaining += hp // 4
    return min(hp, remaining + final_move_heal)


def protect_spread(config, evs, mega, item, protect=True):
    case = config.opponent
    pivot, optimal, *_ = case.moves
    hp_ev, attack_ev, spdef_ev, _ = evs
    form_name = "BAXCALIBUR_MEGA" if mega else "BAXCALIBUR"
    base, form = species("BAXCALIBUR"), species(form_name)
    hp = stat(base.hp, hp_ev, hp=True)
    foe_hp = stat(species(case.species).hp, 76, hp=True)
    before = stat(special_base_stat("BAXCALIBUR", "SpDefense"), spdef_ev)
    after = stat(special_base_stat(form_name, "SpDefense"), spdef_ev)
    if item == "assault vest":
        before, after = half_down(before, ONE_AND_HALF), half_down(after, ONE_AND_HALF)
    x = special_damage(case, pivot, before, resist=item == "resist pivot")
    first, second = dragon_hits(case, stat(form.attack, attack_ev), item)
    chip = foe_hp // 8 if item == "rowap" else 0
    recoil = hp // 10 if item == "life orb" else 0
    worst_hp, worst_ko = hp, foe_hp
    sequences = ((a, b) for a in case.moves for b in case.moves)
    if not mega:
        # The strongest repeated pair is a sufficient failure witness for base.
        # Uxie's drain on the last action also challenges the minimum-roll KO.
        sequences = [(optimal, optimal)]
        if "GIGA_DRAIN" in case.moves:
            sequences.append((optimal, "GIGA_DRAIN"))
    for a, b in sequences:
        y = special_damage(case, a, after, resist=item == "resist direct")
        z = special_damage(case, b, after, vulnerable=not protect)
        blocks_heal = a == b == "PSYCHIC_NOISE"
        # On the repeated Psychic Noise branch, it applies before move-end items.
        # Leftovers runs before Heal Block expires on the Protect turn.
        available = hp - x + (hp // 16 if item == "leftovers" else 0)
        if available <= 0:
            return None
        available -= y
        if item == "enigma" and not blocks_heal and optimal == "DAZZLING_GLEAM":
            available += hp // 4
        if available <= 0:
            return None
        if item in ("sitrus", "figy") and not blocks_heal:
            # Give base Bax the heal before the last hit regardless of threshold.
            available += hp // (4 if item == "sitrus" else 3)
        if item == "leftovers" and not blocks_heal:
            available += (2 if protect else 1) * (hp // 16)
        if item == "shell bell" and not blocks_heal:
            available += first // 8
        if available <= recoil:
            return None
        available -= recoil
        after_first = remaining_foe_hp(config.healing, foe_hp, chip, first, 0)
        if after_first > 0:
            available -= z + recoil
            if available <= 0:
                return None
            heal = z // 2 if b == "GIGA_DRAIN" else 0
            target = remaining_foe_hp(config.healing, foe_hp, chip, first, heal)
            ko_margin = second - target
        else:
            ko_margin = first + chip - foe_hp
        worst_hp, worst_ko = min(worst_hp, available), min(worst_ko, ko_margin)
    return worst_hp, worst_ko, first, second


def best_spread(config, mega, item="none", protect=True):
    results = []
    for evs in spreads(0):
        result = protect_spread(config, evs, mega, item, protect)
        if result and result[1] >= 0:
            results.append((min(result[0], result[1] + 1), *result, evs))
    return max(results, default=None)


def vest_shortcuts(config):
    case = config.opponent
    foe_hp = stat(species(case.species).hp, 76, hp=True)
    bax = species("BAXCALIBUR")
    # Upper bound with max Attack, no need to survive, and free turn order.
    return max(sum(outgoing(case, name, stat(bax.attack, 252), "none") for name in line)
               for line in LINES), foe_hp


def validate(config):
    case = config.opponent
    # Reuse the level-50 learnset check with only the opponent's category check omitted.
    verify_inputs(case, special=True)
    assert move("GLAIVE_RUSH").accuracy == 100
    assert all(special_damage(case, case.moves[1], defense) >=
               max(special_damage(case, name, defense) for name in case.moves)
               for defense in range(106, 154))


def main():
    bax_teachable = source(POKEMON / "teachable_learnsets.h")
    if not re.search(r"sBaxcaliburTeachableLearnset\[\]\s*=\s*\{[^}]*\bMOVE_PROTECT\b",
                     bax_teachable):
        print("Protect is absent from the generated Baxcalibur teachable list. Assuming access for this study.")
    base_items = [item for item in ITEMS if item not in ("jaboca", "resist")]
    base_items += ["resist pivot", "resist direct", "rowap"]
    for config in CASES:
        case = config.opponent
        validate(config)
        result = best_spread(config, True)
        print(case.species, case.item, case.moves)
        print("Mega (margin, HP left, KO margin, hits, EVs):", result)
        if result:
            evs = result[-1]
            x = special_damage(case, case.moves[0], stat(special_base_stat("BAXCALIBUR", "SpDefense"), evs[2]))
            y = special_damage(case, case.moves[1], stat(special_base_stat("BAXCALIBUR_MEGA", "SpDefense"), evs[2]))
            print("Incoming crits:", (x, y, y))
        base = {item: result for item in base_items
                if (result := best_spread(config, False, item))}
        print("Base items passing the modeled branches:", base)
        print("Assault Vest back-to-back:", best_spread(config, False, "assault vest", False))
        print("Assault Vest if it could Protect:", best_spread(config, False, "assault vest"))
        print("Assault Vest other lines (damage upper bound, foe HP):", vest_shortcuts(config))


if __name__ == "__main__":
    main()
