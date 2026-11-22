#!/usr/bin/env python3
"""Compare Mega and Assault Vest Baxcalibur in the original two-attack lines."""

from functools import cache

from analyze_baxcalibur_matchups import (
    LINES, ONE_AND_HALF, Case, effectiveness, half_down, minimum_speed, move,
    outgoing, species, spreads, stat, verify_inputs,
)
from analyze_baxcalibur_protect import remaining_foe_hp, special_base_stat, special_damage

CASES = (
    (Case("CALYREX_SHADOW", "AS_ONE_SHADOW_RIDER", "Psychic Gem",
          ("GIGA_DRAIN", "PSYCHIC", "ASTRAL_BARRAGE", "SHADOW_BALL"), "PSYCHIC", 5530), ""),
    (Case("VICTINI", "VICTORY_STAR", "Leftovers",
          ("SHOCK_WAVE", "DAZZLING_GLEAM", "FLAMETHROWER", "PSYCHIC")), "leftovers"),
    (Case("ZERAORA", "VOLT_ABSORB", "Sitrus Berry",
          ("SHOCK_WAVE", "AURA_SPHERE", "SWIFT", "SNARL")), "sitrus"),
    (Case("LUGIA", "PRESSURE", "Leftovers",
          ("AIR_CUTTER", "DRAGON_PULSE", "SURF", "PSYCHIC_NOISE")), "leftovers"),
)


@cache
def ko_margin(case, healing, line, attack, item):
    foe_hp = stat(species(case.species).hp, 76, hp=True)
    first, second = damage_pair(case, line, attack, item)
    margins = []
    for first_hit in first:
        if first_hit >= foe_hp:
            margins.append(first_hit - foe_hp)
            continue
        if healing == "leftovers":
            # There is one end-of-turn tick between the two hits.
            needed = min(foe_hp, foe_hp - first_hit + foe_hp // 16)
        else:
            needed = remaining_foe_hp(healing, foe_hp, 0, first_hit, 0)
        margins.append(second - needed)
    return min(margins)


@cache
def damage_pair(case, line, attack, item):
    first = tuple(outgoing(case, line[0], attack, item, roll) for roll in range(85, 101))
    second_item = "none" if item == move(line[0]).type.lower() + " gem" else item
    return first, outgoing(case, line[1], attack, second_item)


def screen(case, healing, mega=False, item="none"):
    base_name = "BAXCALIBUR"
    form_name = "BAXCALIBUR_MEGA" if mega else base_name
    bax, form = species(base_name), species(form_name)
    pivot, strongest, *_ = case.moves
    best_win = best_margin = None
    for line in LINES:
        speed = minimum_speed(case, line)
        if speed is None or any(move(name).accuracy != 100 for name in line):
            continue
        if line[0] == "BULLDOZE" and not effectiveness("GROUND", species(case.species).types):
            continue
        for evs in spreads(speed):
            hp_ev, attack_ev, spdef_ev, _ = evs
            hp = stat(bax.hp, hp_ev, hp=True)
            before = stat(special_base_stat(base_name, "SpDefense"), spdef_ev)
            after = stat(special_base_stat(form_name, "SpDefense"), spdef_ev)
            if item == "assault vest":
                before = half_down(before, ONE_AND_HALF)
                after = half_down(after, ONE_AND_HALF)
            first = special_damage(case, pivot, before)
            second = special_damage(case, strongest, after)
            if second < max(special_damage(case, name, after) for name in case.moves):
                raise ValueError(f"Recheck the strongest follow-up for {case.species}")
            left = hp - first
            if left <= 0:
                continue
            if item == "leftovers":
                left = min(hp, left + hp // 16)
            left -= second
            if item == "life orb":
                left -= 2 * (hp // 10)
            if left <= 0:
                continue
            attack = stat(form.attack, attack_ev)
            margin = ko_margin(case, healing, line, attack, item)
            first_rolls, second_hit = damage_pair(case, line, attack, item)
            hits = (first_rolls[0], second_hit)
            result = (margin, left, evs, line, (first, second), hits)
            if best_margin is None or result > best_margin:
                best_margin = result
            if margin >= 0:
                score = min(margin + 1, left)
                if best_win is None or (score, result) > best_win:
                    best_win = score, result
    return best_win, best_margin


def main():
    for case, healing in CASES:
        verify_inputs(case, special=True)
        print(case.species, case.item, case.moves)
        print("Fields: KO margin, HP left, HP/Atk/SpD/Spe EVs, line, crits taken, min hits")
        print("Mega best win:", screen(case, healing, mega=True)[0])
        for item in ("assault vest", "none", "leftovers", "life orb", "dragon boost",
                     "ice boost", "ground boost", "dragon gem", "ice gem", "ground gem"):
            print(f"Base {item} best surviving margin:", screen(case, healing, item=item)[1])


if __name__ == "__main__":
    main()
