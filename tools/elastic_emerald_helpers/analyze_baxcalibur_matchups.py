#!/usr/bin/env python3
"""Screen level-50 physical singles sets for the Baxcalibur two-attack challenge.

The cases describe controlled pivot and follow-up branches, independent of AI
scoring. Extend CASES only after reviewing move effects, ability and item timing.
The base comparison uses generous per-item bounds on the specified branch.
This is a source calculator for these branches, without a battle-engine build.
"""

import argparse
import itertools
import json
import re
from dataclasses import dataclass
from functools import cache
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
DATA = ROOT / "src/data"
POKEMON = DATA / "pokemon"
EVS = [0, *range(4, 253, 8)]
STAT_FIELDS = ("HP", "Attack", "Defense", "Speed")
LINES = (
    ("GLAIVE_RUSH", "ICE_SHARD"),
    ("ICICLE_CRASH", "ICE_SHARD"),
    ("BULLDOZE", "GLAIVE_RUSH"),
    ("BULLDOZE", "ICICLE_CRASH"),
)
ONE = 4096
HALF = 2048
ONE_AND_HALF = 6144


@dataclass(frozen=True)
class Case:
    species: str
    ability: str
    item: str
    moves: tuple[str, ...]  # Pivot, strongest follow-up, two alternate attacks.
    item_type: str = ""
    power_boost: int = ONE
    super_effective_boost: int = ONE


CASES = (
    Case("EXCADRILL", "MOLD_BREAKER", "Ground Gem",
         ("X_SCISSOR", "EARTHQUAKE", "BRICK_BREAK", "SHADOW_CLAW"), "GROUND", 5530),
    Case("GROUDON", "DROUGHT", "Soft Sand",
         ("SHADOW_CLAW", "EARTHQUAKE", "BRICK_BREAK", "DRAGON_CLAW"), "GROUND", 4915),
    Case("ANNIHILAPE", "INNER_FOCUS", "Expert Belt",
         ("SEED_BOMB", "BRICK_BREAK", "RAGE_FIST", "EARTHQUAKE"),
         super_effective_boost=4915),
    Case("GREAT_TUSK", "PROTOSYNTHESIS", "Ground Gem",
         ("KNOCK_OFF", "EARTHQUAKE", "ICE_SPINNER", "THROAT_CHOP"), "GROUND", 5530),
    Case("OKIDOGI", "GUARD_DOG", "Poison Barb",
         ("KNOCK_OFF", "BRICK_BREAK", "POISON_JAB", "PSYCHIC_FANGS"), "POISON", 4915),
)


@dataclass(frozen=True)
class Species:
    hp: int
    attack: int
    defense: int
    speed: int
    types: tuple[str, ...]


@dataclass(frozen=True)
class Move:
    power: int
    type: str
    accuracy: int
    contact: bool
    priority: int


@cache
def source(path):
    return path.read_text()


def entry(source_text, key):
    match = re.search(rf"\[{key}\]\s*=\s*\{{(.*?)\n    \}},", source_text, re.S)
    if match is None:
        raise ValueError(f"Missing definition for {key}")
    return match[1]


@cache
def species(name):
    for header in sorted((POKEMON / "species_info").glob("*.h")):
        content = source(header)
        if f"[SPECIES_{name}]" in content:
            body = entry(content, "SPECIES_" + name)
            values = [int(re.search(rf"\.base{key}\s*=\s*(\d+)", body)[1]) for key in STAT_FIELDS]
            types = re.search(r"\.types\s*=\s*MON_TYPES\((.*?)\)", body)[1]
            return Species(*values, tuple(dict.fromkeys(re.findall(r"TYPE_(\w+)", types))))
    raise ValueError(f"Missing species {name}")


@cache
def move(name):
    body = entry(source(DATA / "moves_info.h"), "MOVE_" + name)
    fields = dict(re.findall(r"\.(power|type|accuracy|priority)\s*=\s*([^,]+),", body))
    if "DAMAGE_CATEGORY_PHYSICAL" not in body:
        raise ValueError(f"{name} must be physical in this model")
    power = fields["power"]
    if "?" in power:
        # The move table uses generation thresholds for these physical attacks.
        power = power.split("?")[1].split(":")[0]
    return Move(int(power), fields["type"].removeprefix("TYPE_"), int(fields["accuracy"]),
                ".makesContact = TRUE" in body, int(fields.get("priority", 0)))


@cache
def type_chart():
    table = source(DATA / "types_info.h").split("gTypeEffectivenessTable")[1].split("#undef")[0]
    rows = dict(re.findall(r"\[TYPE_(\w+)\]\s*=\s*\{([^}]+)\}", table))
    values = {"______": ONE, "X(0.5)": HALF, "X(2.0)": 8192, "X(0.0)": 0,
              "BUG_RS": ONE, "PSN_RS": HALF, "STL_RS": ONE, "PSY_RS": 8192, "FIR_RS": HALF}
    return {(attack, defense): values[value.strip()]
            for attack, row in rows.items() for defense, value in zip(rows, row.split(","))}


def half_down(value, modifier):
    return (value * modifier + HALF - 1) // ONE


@cache
def effectiveness(move_type, types):
    result = ONE
    for target_type in types:
        result = half_down(result, type_chart()[move_type, target_type])
    return result


@cache
def damage(power, attack, defense, stab, type_factor, roll, critical=False,
           power_boost=ONE, final_boost=ONE):
    if type_factor == 0:
        return 0
    value = 22 * half_down(power, power_boost) * attack // defense // 50 + 2
    if critical:
        value = half_down(value, ONE_AND_HALF)
    value = value * roll // 100
    if stab:
        value = half_down(value, ONE_AND_HALF)
    return max(1, half_down(half_down(value, type_factor), final_boost))


def stat(base, ev, hp=False):
    return base + (31 + ev // 4) // 2 + (60 if hp else 5)


def incoming(case, name, defense, removable_item=False, resist=False):
    attack = move(name)
    foe = species(case.species)
    bax_types = species("BAXCALIBUR").types
    type_factor = effectiveness(attack.type, bax_types)
    # The specified pivot does not consume the foe's type gem.
    power_boost = case.power_boost if attack.type == case.item_type else ONE
    if name == "KNOCK_OFF" and removable_item:
        power_boost = half_down(power_boost, ONE_AND_HALF)
    final = case.super_effective_boost if type_factor >= 8192 else ONE
    if resist:
        final = half_down(final, HALF)
    return damage(attack.power, stat(foe.attack, 180), defense, attack.type in foe.types,
                  type_factor, 100, True, power_boost, final)


ITEMS = (
    "none", "life orb", "muscle band", "expert belt",
    "ice boost", "dragon boost", "ground boost", "ice gem", "dragon gem", "ground gem",
    "sitrus", "figy", "leftovers", "shell bell", "enigma", "resist", "jaboca",
    "rocky helmet", "liechi",
)
# On the Knock Off branch, grant these items their entry-hit benefits even
# if the engine removes them before activation. Also grant free turn order to
# base Bax in both branches, covering Custap and Salac without timing rules.
KNOCK_OFF_ITEMS = ("none", "sitrus", "figy", "enigma", "jaboca", "rocky helmet", "liechi")


def outgoing(case, name, attack_stat, item):
    attack = move(name)
    foe = species(case.species)
    stab = attack.type in species("BAXCALIBUR").types
    factor = effectiveness(attack.type, foe.types)
    power_boost = {"muscle band": 4505, attack.type.lower() + " boost": 4915,
                   attack.type.lower() + " gem": 5530}.get(item, ONE)
    if item == "liechi":
        # Optimistically grant +1 on both turns, regardless of the threshold.
        attack_stat = attack_stat * 3 // 2
    final = 5324 if item == "life orb" else ONE
    if item == "expert belt" and factor >= 8192:
        final = 4915
    return damage(attack.power, attack_stat, stat(foe.defense, 0), stab, factor, 85,
                  power_boost=power_boost, final_boost=final)


def minimum_speed(case, line):
    opponent = stat(species(case.species).speed, 252) * 11 // 10
    if line[0] != "BULLDOZE":
        return 0
    return next((ev for ev in EVS if stat(species("BAXCALIBUR").speed, ev) > opponent * 2 // 3), None)


def spreads(speed_ev):
    for attack_ev, defense_ev in itertools.product(EVS, repeat=2):
        # Extra HP only improves survival under the conservative item bounds.
        room = 510 - speed_ev - attack_ev - defense_ev
        hp_ev = min(252, max(0, (room + 4) // 8 * 8 - 4))
        if room >= 0:
            yield hp_ev, attack_ev, defense_ev, speed_ev


@dataclass(frozen=True)
class Result:
    hp: int
    foe_hp: int
    pivot: int
    direct: int
    left: int
    damage: tuple[int, int]
    evs: tuple[int, ...]
    line: tuple[str, str]
    followups: tuple[tuple[str, int, int], ...]

    @property
    def margin(self):
        return min(self.left, sum(self.damage) - self.foe_hp + 1)


def mega_result(case, attack_base, defense_base):
    bax = species("BAXCALIBUR")
    foe_hp = stat(species(case.species).hp, 76, hp=True)
    pivot, strongest, *_ = case.moves
    best = None
    for line in LINES:
        speed_ev = minimum_speed(case, line)
        if speed_ev is None or any(move(name).accuracy != 100 for name in line):
            continue
        for evs in spreads(speed_ev):
            hp_ev, attack_ev, defense_ev, _ = evs
            hp = stat(bax.hp, hp_ev, hp=True)
            pivot_damage = incoming(case, pivot, stat(bax.defense, defense_ev))
            followups = []
            for name in case.moves:
                crit = incoming(case, name, stat(defense_base, defense_ev))
                residual = 2 * (hp // 8) if name == "POISON_JAB" else 0
                followups.append((name, crit, residual))
            direct = dict((name, crit) for name, crit, _ in followups)[strongest]
            left = hp - pivot_damage - max(crit + residual for _, crit, residual in followups)
            hits = tuple(outgoing(case, name, stat(attack_base, attack_ev), "none") for name in line)
            result = Result(hp, foe_hp, pivot_damage, direct, left, hits, evs, line, tuple(followups))
            if result.margin > 0 and (best is None or result.margin > best.margin):
                best = result
    return best


def base_bounds(case):
    """Best minimum-roll KO margin after surviving the specified crit pair."""
    bax = species("BAXCALIBUR")
    pivot, direct, *_ = case.moves
    foe_hp = stat(species(case.species).hp, 76, hp=True)
    knocks_off = pivot == "KNOCK_OFF"
    bounds = {}
    for item in KNOCK_OFF_ITEMS if knocks_off else ITEMS:
        best = None
        for line in LINES:
            if any(move(name).accuracy != 100 for name in line):
                continue
            if line[0] == "BULLDOZE" and not effectiveness("GROUND", species(case.species).types):
                continue
            for hp_ev, attack_ev, defense_ev, _ in spreads(0):
                hp = stat(bax.hp, hp_ev, hp=True)
                defense = stat(bax.defense, defense_ev)
                eligible = [name for name in (pivot, direct)
                            if effectiveness(move(name).type, bax.types) >= 8192
                            or move(name).type == "NORMAL"]
                resist = eligible[0] if item == "resist" and eligible else None
                first = incoming(case, pivot, defense, knocks_off and item != "none", resist == pivot)
                second = incoming(case, direct, defense, resist == direct and pivot != direct)
                if hp <= first:
                    continue
                available = hp - first
                if item in ("sitrus", "figy"):
                    # Smaller HP spreads can cross an activation threshold that
                    # the largest spread misses. Grant the best such spread,
                    # even if its HP falls between attainable stat points.
                    threshold = 2 if item == "sitrus" else 4
                    divisor = 4 if item == "sitrus" else 3
                    activation_hp = min(hp, first * threshold // (threshold - 1))
                    if activation_hp >= stat(bax.hp, 0, hp=True):
                        available = max(available, activation_hp - first + activation_hp // divisor)
                if item == "leftovers":
                    available += hp // 16
                if item == "enigma" and effectiveness(move(pivot).type, bax.types) >= 8192:
                    available += hp // 4
                if available <= second:
                    continue
                # Ignore Life Orb's recoil here. A base failure still holds even
                # under this more generous survival bound.
                attack = stat(bax.attack, attack_ev)
                dealt = sum(outgoing(case, name, attack, item) for name in line)
                if item == "jaboca":
                    dealt += foe_hp // 8
                if item == "rocky helmet":
                    dealt += (foe_hp // 6) * sum(move(name).contact for name in (pivot, direct))
                margin = dealt - foe_hp
                if best is None or margin > best:
                    best = margin
        bounds[item] = best
    return bounds


def verify_inputs(case):
    learnable = json.loads(source(POKEMON / "all_learnables.json"))
    level_files = "\n".join(source(path) for path in sorted((POKEMON / "level_up_learnsets").glob("*.h")))
    for species_name, names in ((case.species, case.moves), ("BAXCALIBUR", set(itertools.chain(*LINES)))):
        header = next(path for path in (POKEMON / "species_info").glob("*.h")
                      if f"[SPECIES_{species_name}]" in source(path))
        body = entry(source(header), "SPECIES_" + species_name)
        if species_name == case.species and "ABILITY_" + case.ability not in body:
            raise ValueError(f"{case.species} cannot have {case.ability}")
        level_array = re.search(r"\.levelUpLearnset\s*=\s*(\w+)", body)[1]
        level_body = re.search(rf"\b{level_array}\[\]\s*=\s*\{{([^}}]*)\}}", level_files)[1]
        learned = {name for level, name in re.findall(r"LEVEL_UP_MOVE\((\d+), (MOVE_\w+)\)", level_body)
                   if int(level) <= 50}
        missing = {"MOVE_" + name for name in names} - learned - set(learnable.get(species_name, ()))
        if missing:
            raise ValueError(f"{species_name} missing moves from level-50/teachable data: {sorted(missing)}")
    if stat(species(case.species).speed, 252) * 11 // 10 <= stat(species("BAXCALIBUR").speed, 252):
        raise ValueError("Opponent must outrun max-Speed neutral Baxcalibur")
    if any(move(name).priority != 0 for name in case.moves):
        raise ValueError("Opponent priority requires a separate turn-order check")
    for name in case.moves:
        body = entry(source(DATA / "moves_info.h"), "MOVE_" + name)
        if re.search(r"MOVE_EFFECT_\w*(?:FLINCH|PARALYS|CONFUS|SLEEP|FREEZE|FROSTBITE)", body):
            raise ValueError(f"{name} can deny an action and needs its own branches")
        if re.search(r"\.speed\s*=", body):
            raise ValueError(f"{name} needs a separate turn-order check")
    if case.item.endswith("Gem") and move(case.moves[0]).type == case.item_type:
        raise ValueError("The pivot would consume the gem before the follow-up")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("species", nargs="*", help="Species constants to evaluate. Defaults to all cases.")
    args = parser.parse_args()
    wanted = {name.upper() for name in args.species}
    if wanted - {case.species for case in CASES}:
        parser.error("Unknown case: " + ", ".join(sorted(wanted - {case.species for case in CASES})))
    bax, mega = species("BAXCALIBUR"), species("BAXCALIBUR_MEGA")
    for case in CASES:
        if wanted and case.species not in wanted:
            continue
        verify_inputs(case)
        result = mega_result(case, mega.attack, mega.defense)
        print(case.species, case.item, case.moves)
        if result:
            print(result)
            print("Mega Attack only:", mega_result(case, mega.attack, bax.defense) is not None)
            print("Mega Defense only:", mega_result(case, bax.attack, mega.defense) is not None)
        print("Base KO margins after surviving the crit pair:", base_bounds(case))


if __name__ == "__main__":
    main()
