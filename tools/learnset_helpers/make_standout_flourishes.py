#!/usr/bin/env python3
"""Generate a repository-aware first-pass learnset-flourish design document."""

from __future__ import annotations

import re
from collections import Counter, defaultdict
from pathlib import Path

from type_move_report import (
    DEFAULT_DATA_DIR,
    DEFAULT_SPECIES_DIR,
    collect_move_pools,
    display_constant,
    iter_initializer_blocks,
    load_game_data,
    load_species_info,
    normalize_constant,
    qualified_name,
    type_label,
)


ROOT = Path(__file__).resolve().parents[2]
LEVEL_UP = ROOT / "src/data/pokemon/level_up_learnsets/gen_9.h"
SPECIES_DIR = ROOT / "src/data/pokemon/species_info"
MOVES_INFO = ROOT / "src/data/moves_info.h"
TUTORS = ROOT / "src/data/pokemon/center_tutor_moves.h"
TIER_DOC = ROOT / "docs/gameplay/tier-points.md"
OUTPUT = ROOT / "tools/learnset_helpers/standout-learnset-flourishes.md"


SETUP_MOVES = {
    "MOVE_AGILITY", "MOVE_AMNESIA", "MOVE_AUTOTOMIZE", "MOVE_BELLY_DRUM",
    "MOVE_BULK_UP", "MOVE_CALM_MIND", "MOVE_CLANGOROUS_SOUL", "MOVE_COIL",
    "MOVE_COSMIC_POWER", "MOVE_COTTON_GUARD", "MOVE_DRAGON_DANCE",
    "MOVE_GROWTH", "MOVE_HONE_CLAWS", "MOVE_IRON_DEFENSE", "MOVE_NASTY_PLOT",
    "MOVE_NO_RETREAT", "MOVE_QUIVER_DANCE", "MOVE_ROCK_POLISH",
    "MOVE_SHELL_SMASH", "MOVE_SHIFT_GEAR", "MOVE_SWORDS_DANCE",
    "MOVE_TAIL_GLOW", "MOVE_TIDY_UP", "MOVE_VICTORY_DANCE", "MOVE_WORK_UP",
}

# Setup is intentionally opt-in. These are design calls, not consequences of rarity scoring.
SETUP_EXCEPTIONS = {
    "DUSTOX": ("MOVE_QUIVER_DANCE", "low offenses keep the boost from becoming an early sweep button"),
    "SEVIPER": ("MOVE_COIL", "the coiling snake animation and middling Speed make this unusually exact"),
    "TROPIUS": ("MOVE_DRAGON_DANCE", "its low Attack and Speed leave room for a flavorful dragon-like dance"),
    "WEAVILE": ("MOVE_NASTY_PLOT", "its low Sp. Atk makes the special setup a creative sidegrade"),
}

# Ecosystem allocations deliberately compare alternatives instead of scoring each move in
# isolation. The tuple is (move, rationale, target level). Entries may exceed historical
# distribution where anatomy, habitat, or a desired alternate offensive route supports it.
CURATED_ADDITIONS = {
    # Grassy Terrain: prioritize roles not already represented by Vileplume/Roserade's
    # Grass/Poison special-status niche or Rillaboom's premium physical terrain offense.
    "PARASECT": [("MOVE_GRASSY_TERRAIN", "Low-tier Bug/Grass field control is distinct from the existing setters", 28)],
    "MEGANIUM": [("MOVE_GRASSY_TERRAIN", "Bulky mono-Grass team support is its clearest ecosystem niche", 30)],
    "SUNFLORA": [("MOVE_GRASSY_TERRAIN", "A slow low-tier sun specialist benefits from a second field identity", 24)],
    "TORTERRA": [("MOVE_GRASSY_TERRAIN", "A bulky physical Grass/Ground setter has little role overlap with the special Grass/Poison setters", 36)],
    "GOGOAT": [("MOVE_GRASSY_TERRAIN", "A terrestrial physical grazer can use terrain as sustain and team support", 30)],

    # Ground coverage families.
    "CRADILY": [("MOVE_EARTH_POWER", "Its rooted fossil body and usable 81 Sp. Atk support special geological coverage", 38)],
    "SUNFLORA": [("MOVE_GRASSY_TERRAIN", "A slow low-tier sun specialist benefits from a second field identity", 24),
                  ("MOVE_EARTH_POWER", "105 Sp. Atk makes Ground coverage meaningful while its low Speed and tier keep it fair", 38)],
    "ARBOLIVA": [("MOVE_EARTH_POWER", "Its roots and 125 Sp. Atk make this the strongest non-Ground botanical candidate", 42)],
    "WORMADAM_SANDY": [("MOVE_EARTH_POWER", "The sandy cloak supplies direct flavor and its special offense is not negligible", 34)],
    "WHISCASH": [("MOVE_EARTH_POWER", "Its mud-dwelling identity and mixed offenses support a special Ground route", 34)],
    "SEISMITOAD": [("MOVE_EARTH_POWER", "Its vibrations and 85 Sp. Atk make special Ground STAB a real alternative", 38)],
    "AGGRON": [("MOVE_EARTHQUAKE", "Its weight and territorial stomping justify premium physical Ground coverage", 52),
               ("MOVE_HARD_PRESS", "Its armored mass gives the variable-power Steel attack a visible source", 44)],
    "AVALUGG_HISUI": [("MOVE_HIGH_HORSEPOWER", "127 Attack and a charging iceberg body suit physical Ground coverage", 44),
                       ("MOVE_HARD_PRESS", "Its immense armored body is a much better fit than special Earth Power", 40)],
    "DONPHAN": [("MOVE_HIGH_HORSEPOWER", "A charging elephant distinguishes this from its existing seismic Earthquake identity", 38)],
    "ZEBSTRIKA": [("MOVE_HIGH_HORSEPOWER", "Equine anatomy and 100 Attack make this coverage both legible and useful", 36)],
    "BOUFFALANT": [("MOVE_HIGH_HORSEPOWER", "A charging buffalo is one of the move's clearest non-horse fits", 34)],
    "STONJOURNER": [("MOVE_HARD_PRESS", "Its monolithic weight creates a rare natural home for Hard Press", 40)],
    "COPPERAJAH": [("MOVE_HARD_PRESS", "A heavy Steel elephant supplies both the mass and physical offense the move needs", 42)],
    "REVAVROOM": [("MOVE_HARD_PRESS", "Its industrial chassis makes a literal mechanical press easy to justify", 40)],
    "MARACTUS": [("MOVE_SCORCHING_SANDS", "Its Pokédex habitat explicitly names arid regions; 106 Sp. Atk makes the novel coverage matter", 34),
                 ("MOVE_HYPER_VOICE", "Its Pokédex entry explicitly emphasizes maraca-like sound, and 106 Sp. Atk makes that identity useful", 38)],
    "CACTURNE": [("MOVE_SCORCHING_SANDS", "Its Pokédex text says its body became sand after millennia in harsh deserts", 36),
                 ("MOVE_KNOCK_OFF", "Its nocturnal ambusher role and usable hands justify earlier disruptive Dark STAB", 34)],
    "PALOSSAND": [("MOVE_SCORCHING_SANDS", "A sentient sand castle can weaponize sun-heated sand naturally", 38)],
    "AZUMARILL": [("MOVE_MUDDY_WATER", "Early special STAB gives non-Huge-Power abilities and its 60 Sp. Atk a meaningful route", 38)],

    # Knock Off is easy to justify, so scarcity should come from role selection rather than
    # flavor denial. These users emphasize hands, theft, scavenging, or disruptive play.
    "PERSIAN": [("MOVE_KNOCK_OFF", "Fast low-tier disruption gives it a reason to exist beside stronger Normal attackers", 32)],
    "PERSIAN_ALOLA": [("MOVE_KNOCK_OFF", "Its smug, underhanded Dark identity is almost a literal reading of the move", 30)],
    "AMBIPOM": [("MOVE_KNOCK_OFF", "Dexterous tail-hands make item removal visibly plausible", 34)],
    "LIEPARD": [("MOVE_KNOCK_OFF", "A fast trickster gains role expression without receiving setup", 30)],
    "THIEVUL": [("MOVE_KNOCK_OFF", "The thief motif is direct and the species is weak enough to merit early League-tutor access", 28)],
    "WATCHOG": [("MOVE_KNOCK_OFF", "A low-tier sentry with grasping limbs can support through disruption", 28)],
    "SHIFTRY": [("MOVE_KNOCK_OFF", "Its hands and malicious forest-trickster role distinguish this from pure damage coverage", 36)],
}

ECOSYSTEM_MOVES = {
    "MOVE_GRASSY_TERRAIN", "MOVE_EARTH_POWER", "MOVE_EARTHQUAKE",
    "MOVE_HIGH_HORSEPOWER", "MOVE_SCORCHING_SANDS", "MOVE_KNOCK_OFF", "MOVE_HARD_PRESS",
}

MODERN_MOVES = (
    "MOVE_TERRAIN_PULSE", "MOVE_BURNING_JEALOUSY", "MOVE_FLIP_TURN",
    "MOVE_GRASSY_GLIDE", "MOVE_RISING_VOLTAGE", "MOVE_COACHING",
    "MOVE_SCORCHING_SANDS", "MOVE_DUAL_WINGBEAT", "MOVE_METEOR_BEAM",
    "MOVE_SKITTER_SMACK", "MOVE_TRIPLE_AXEL", "MOVE_EXPANDING_FORCE",
    "MOVE_POLTERGEIST", "MOVE_SCALE_SHOT", "MOVE_LASH_OUT", "MOVE_STEEL_ROLLER",
    "MOVE_MISTY_EXPLOSION", "MOVE_POUNCE", "MOVE_CHILLING_WATER",
    "MOVE_ICE_SPINNER", "MOVE_ALLURING_VOICE", "MOVE_HARD_PRESS",
    "MOVE_TEMPER_FLARE",
)

MODERN_LEVELUP_ALLOCATIONS = {
    "KECLEON": [("MOVE_TERRAIN_PULSE", "Color Change and Protean make terrain-responsive offense part of its core identity", 34)],
    "BANETTE": [("MOVE_BURNING_JEALOUSY", "Its grudge-born Pokédex lore gives the emotion-based attack an unusually direct home", 34),
                ("MOVE_POLTERGEIST", "A possessed doll is the clearest possible natural owner of Poltergeist", 44)],
    "SPIRITOMB": [("MOVE_BURNING_JEALOUSY", "Its collection of malicious spirits supports jealous, retaliatory fire", 38)],
    "LUVDISC": [("MOVE_FLIP_TURN", "A low-tier fish gains useful momentum without gaining raw sweeping power", 26)],
    "LUMINEON": [("MOVE_FLIP_TURN", "Its graceful swimming identity supports a utility pivot niche", 30)],
    "WUGTRIO": [("MOVE_FLIP_TURN", "Its low tier and aquatic ambush style leave room for early pivot access", 28)],
    "PARASECT": [("MOVE_GRASSY_GLIDE", "Priority compensates for extreme slowness without making its Attack exceptional", 32)],
    "LEAFEON": [("MOVE_GRASSY_GLIDE", "A low-final-tier physical Grass attacker is a fair natural owner outside Rillaboom", 38)],
    "DEDENNE": [("MOVE_RISING_VOLTAGE", "A weak Electric/Fairy with terrain utility can own the terrain payoff without dominating it", 36)],
    "AMPHAROS": [("MOVE_RISING_VOLTAGE", "Its low Speed and strong special electricity make terrain-dependent power a fair branch", 42)],
    "LEDIAN": [("MOVE_COACHING", "Its team-oriented hero motif and very low tier favor doubles support over personal setup", 28)],
    "PASSIMIAN": [("MOVE_COACHING", "Its explicit teamwork and ball-passing behavior make this the move's strongest thematic owner", 34)],
    "TOUCANNON": [("MOVE_DUAL_WINGBEAT", "A physical bird with middling Speed gains natural Flying STAB without Brave Bird's ceiling", 36)],
    "LUNATONE": [("MOVE_METEOR_BEAM", "The lunar meteor body and 95 Sp. Atk make the charged Rock attack functional", 44)],
    "AURORUS": [("MOVE_METEOR_BEAM", "Its aurora and fossil spectacle support a rare special Rock setup attack", 48)],
    "ARIADOS": [("MOVE_SKITTER_SMACK", "A low-tier physical spider can own the disruptive Bug attack", 30),
                ("MOVE_POUNCE", "Pouncing is a direct spider hunting behavior and offers a modest early bridge", 22)],
    "WORMADAM_TRASH": [("MOVE_SKITTER_SMACK", "Its low tier and physical cloak attacks make the debuffing Bug move safe", 30)],
    "DELIBIRD": [("MOVE_TRIPLE_AXEL", "Its low Attack and slapstick movement keep premium multi-hit Ice coverage in check", 38)],
    "HITMONTOP": [("MOVE_TRIPLE_AXEL", "Spinning kick anatomy makes the three-part attack visually exact", 42)],
    "BEHEEYEM": [("MOVE_EXPANDING_FORCE", "A slow Psychic specialist can exploit terrain without becoming a generic fast sweeper", 40)],
    "MUSHARNA": [("MOVE_EXPANDING_FORCE", "Its dream and field-control role supports slow Psychic Terrain offense", 38)],
    "DUSKNOIR": [("MOVE_POLTERGEIST", "100 Attack makes physical Ghost STAB valuable while low Speed restrains it", 46)],
    "SEVIPER": [("MOVE_SCALE_SHOT", "A scaled snake with middling Speed gains a risky physical speed-control option", 40)],
    "DRUDDIGON": [("MOVE_SCALE_SHOT", "Its rough scales and low Speed make this a literal and balanced fit", 42)],
    "MIGHTYENA": [("MOVE_LASH_OUT", "An intimidated pack hunter is a natural low-tier owner of retaliation-based Dark STAB", 32)],
    "MABOSSTIFF": [("MOVE_LASH_OUT", "Its protective, retaliatory temperament makes Lash Out an identity attack", 36)],
    "KLINKLANG": [("MOVE_STEEL_ROLLER", "Interlocking gears provide the rolling machinery while low Speed limits terrain removal offense", 42)],
    "REVAVROOM": [("MOVE_STEEL_ROLLER", "A literal engine supplies the strongest mechanical justification for the move", 44)],
    "WEEZING_GALAR": [("MOVE_MISTY_EXPLOSION", "Its Fairy typing, gas body, and Misty Surge option unite every part of the move", 42)],
    "AROMATISSE": [("MOVE_MISTY_EXPLOSION", "Perfume mist and low Speed make this a thematic emergency button", 40)],
    "KRICKETUNE": [("MOVE_POUNCE", "A low-tier terrestrial insect can use the Speed-drop bridge without threatening sweeps", 20)],
    "DEWGONG": [("MOVE_CHILLING_WATER", "An aquatic Ice type is a better natural owner than generic Water-compatible species", 24)],
    "GLALIE": [("MOVE_CHILLING_WATER", "Melting or spraying icy water gives a low-tier Ice type early physical mitigation", 28)],
    "CRYOGONAL": [("MOVE_CHILLING_WATER", "95 Sp. Atk makes the attack usable and its ice-crystal body supplies the chill", 30)],
    "BEARTIC": [("MOVE_ICE_SPINNER", "Its strong physical Ice offense and mobile bear body make terrain-clearing contact plausible", 40)],
    "AVALUGG": [("MOVE_ICE_SPINNER", "Its physical bulk and iceberg motion support a slow terrain-clearing attack", 42)],
    "JYNX": [("MOVE_ALLURING_VOICE", "Its singing, humanoid presentation and 115 Sp. Atk make this an identity attack", 34)],
    "CHIMECHO": [("MOVE_ALLURING_VOICE", "Its resonant cry and 95 Sp. Atk distinguish this from generic Fairy coverage", 34)],
    "FLAREON": [("MOVE_TEMPER_FLARE", "130 Attack and an emotional Fire identity give it valuable physical STAB with a condition", 38)],
    "TORKOAL": [("MOVE_TEMPER_FLARE", "A slow physical-capable fire tortoise can use the failure payoff without easy snowballing", 36)],
}

# Compatibility-only gaps are deliberately narrower than level-up allocations. They flag
# plausible modern TM/tutor access that may have been missed because the species was absent.
COMPATIBILITY_GAPS = {
    "UNFEZANT": [("MOVE_ACROBATICS", "Gen 9 greatly broadened Acrobatics among ordinary birds; Unfezant missed that pass")],
    "BEEDRILL": [("MOVE_POUNCE", "a fast stinging insect is an obvious recipient of the broadly distributed Bug TM")],
    "DELCATTY": [("MOVE_ALLURING_VOICE", "its charm and voice-oriented support pool fit the broadly distributed sound TM")],
    "CHATOT": [("MOVE_ALLURING_VOICE", "a vocal mimic should receive the sound-based TM regardless of Fairy typing")],
    "WATCHOG": [("MOVE_LASH_OUT", "a low-tier physical sentry can reasonably share the broad retaliation tutor")],
    "SIMISAGE": [("MOVE_GRASSY_GLIDE", "its physical Grass role fits the modern Grass tutor even without natural access")],
    "SIMISEAR": [("MOVE_TEMPER_FLARE", "its emotional Fire motif and physical option fit the modern Fire TM")],
    "SIMIPOUR": [("MOVE_FLIP_TURN", "an agile Water primate can reasonably share the expanded pivot TM")],
}

EXCLUDED = {
    "MOVE_ATTRACT", "MOVE_BIDE", "MOVE_CAPTIVATE", "MOVE_CONFIDE", "MOVE_CUT",
    "MOVE_DOUBLE_TEAM", "MOVE_FLASH", "MOVE_FORESIGHT", "MOVE_FRUSTRATION",
    "MOVE_GROWL", "MOVE_HIDDEN_POWER", "MOVE_LEER", "MOVE_MIMIC", "MOVE_MUD_SLAP",
    "MOVE_NATURAL_GIFT", "MOVE_ODOR_SLEUTH", "MOVE_PLAY_NICE", "MOVE_RAGE",
    "MOVE_RETURN", "MOVE_ROCK_SMASH", "MOVE_ROUND", "MOVE_SECRET_POWER",
    "MOVE_SLEEP_TALK", "MOVE_SNORE", "MOVE_STRENGTH", "MOVE_SWAGGER",
    "MOVE_TAIL_WHIP", "MOVE_TERA_BLAST", "MOVE_TOXIC", "MOVE_WATER_SPORT",
    "MOVE_MUD_SPORT", "MOVE_BATON_PASS", "MOVE_WRING_OUT", "MOVE_SPIT_UP",
    "MOVE_STORED_POWER", "MOVE_POWER_TRIP",
    "MOVE_GUARD_SPLIT",
}

GENERIC_LOW_VALUE = {
    "MOVE_ENDURE", "MOVE_FACADE", "MOVE_FLING", "MOVE_HELPING_HAND", "MOVE_PROTECT",
    "MOVE_RAIN_DANCE", "MOVE_REST", "MOVE_SAFEGUARD", "MOVE_SUBSTITUTE",
    "MOVE_SUNNY_DAY", "MOVE_TAKE_DOWN",
}

PRIORITY_MOVES = {
    "MOVE_GRASSY_TERRAIN", "MOVE_MISTY_TERRAIN", "MOVE_ELECTRIC_TERRAIN",
    "MOVE_PSYCHIC_TERRAIN", "MOVE_TRAILBLAZE", "MOVE_EARTH_POWER",
    "MOVE_MYSTICAL_FIRE", "MOVE_STRENGTH_SAP", "MOVE_POLLEN_PUFF",
    "MOVE_FIRST_IMPRESSION", "MOVE_RAGE_POWDER", "MOVE_LIFE_DEW", "MOVE_HEAL_BELL",
    "MOVE_MORNING_SUN", "MOVE_MOONLIGHT", "MOVE_SHORE_UP", "MOVE_RECOVER",
    "MOVE_SCORCHING_SANDS", "MOVE_BURNING_JEALOUSY", "MOVE_TERRAIN_PULSE",
    "MOVE_WEATHER_BALL", "MOVE_ACID_SPRAY", "MOVE_CLEAR_SMOG", "MOVE_POWER_GEM",
    "MOVE_BODY_PRESS", "MOVE_PSYCHIC_FANGS", "MOVE_HYPER_VOICE", "MOVE_BOOMBURST",
    "MOVE_SLUDGE_WAVE", "MOVE_SLUDGE_BOMB", "MOVE_BRINE", "MOVE_CHILLING_WATER",
}


def arrays(text: str) -> dict[str, str]:
    header = re.compile(r"static const struct LevelUpMove s([A-Za-z0-9_]+)LevelUpLearnset\[\]\s*=\s*\{")
    found = {}
    for match in header.finditer(text):
        depth, pos = 1, match.end()
        while pos < len(text) and depth:
            depth += (text[pos] == "{") - (text[pos] == "}")
            pos += 1
        found[match.group(1)] = text[match.end():pos - 1]
    return found


def species_bodies() -> dict[str, str]:
    out = {}
    for path in sorted(SPECIES_DIR.glob("gen_*_families.h")):
        out.update(dict(iter_initializer_blocks(path.read_text(encoding="utf-8"))))
    return out


def current_learnsets() -> tuple[dict[str, dict[str, int]], dict[str, str]]:
    learnset_arrays = arrays(LEVEL_UP.read_text(encoding="utf-8"))
    result, descriptions = {}, {}
    for species, body in species_bodies().items():
        pointer = re.search(r"\.levelUpLearnset\s*=\s*s([A-Za-z0-9_]+)LevelUpLearnset", body)
        if pointer and pointer.group(1) in learnset_arrays:
            entries = re.findall(r"LEVEL_UP_MOVE\(\s*(\d+)\s*,\s*(MOVE_[A-Z0-9_]+)\s*\)", learnset_arrays[pointer.group(1)])
            result[species] = {move: int(level) for level, move in entries}
        desc = re.search(r"\.description\s*=\s*COMPOUND_STRING\((.*?)\)\s*,", body, re.S)
        descriptions[species] = " ".join(re.findall(r'"([^"]*)"', desc.group(1))) if desc else ""
    return result, descriptions


def battle_profiles() -> dict[str, dict[str, object]]:
    profiles = {}
    for species, body in species_bodies().items():
        stats = {}
        for field in ("Attack", "SpAttack", "Speed", "Defense"):
            match = re.search(rf"\.base{field}\s*=\s*([^,\n]+)", body)
            if match:
                expression = match.group(1)
                numbers = [int(value) for value in re.findall(r"\d+", expression)]
                stats[field] = numbers[-2] if "?" in expression and len(numbers) >= 2 else (numbers[0] if numbers else 0)
        ability_match = re.search(r"\.abilities\s*=\s*\{([^}]+)\}", body)
        abilities = re.findall(r"ABILITY_([A-Z0-9_]+)", ability_match.group(1)) if ability_match else []
        profiles[species] = {"stats": stats, "abilities": abilities}
    return profiles


def historical_methods(games: dict[str, dict]) -> dict[str, dict[str, set[str]]]:
    out = defaultdict(lambda: defaultdict(set))
    for game in games.values():
        for raw_species, data in game.items():
            species = normalize_constant(raw_species)
            for key, label in (("LevelMoves", "level-up"), ("EggMoves", "egg"),
                               ("TMMoves", "TM"), ("TutorMoves", "tutor"),
                               ("PreEvoMoves", "pre-evolution")):
                for entry in data.get(key, []):
                    move = entry["Move"] if isinstance(entry, dict) else entry
                    if move != "MOVE_UNAVAILABLE":
                        out[species][move].add(label)
    return out


def game_presence(games: dict[str, dict]) -> dict[str, set[str]]:
    return {
        game: {
            normalize_constant(species)
            for species, data in learnsets.items()
            if data.get("LevelMoves")
        }
        for game, learnsets in games.items()
    }


def modern_distribution_counts(games: dict[str, dict]) -> dict[str, tuple[int, int]]:
    counts = {}
    for move in MODERN_MOVES:
        level_learners, teachable_learners = set(), set()
        for game in games.values():
            for raw_species, learnset in game.items():
                species = normalize_constant(raw_species)
                if any(
                    isinstance(entry, dict) and entry.get("Move") == move
                    for entry in learnset.get("LevelMoves", [])
                ):
                    level_learners.add(species)
                if move in learnset.get("TMMoves", []) or move in learnset.get("TutorMoves", []):
                    teachable_learners.add(species)
        counts[move] = (len(level_learners), len(teachable_learners))
    return counts


def move_data() -> dict[str, tuple[int, str, str]]:
    text = MOVES_INFO.read_text(encoding="utf-8")
    result = {}
    for match in re.finditer(r"\[(MOVE_[A-Z0-9_]+)\]\s*=\s*\{", text):
        depth, pos = 1, match.end()
        while pos < len(text) and depth:
            depth += (text[pos] == "{") - (text[pos] == "}")
            pos += 1
        body = text[match.end():pos - 1]
        power_match = re.search(r"\.power\s*=\s*([^,\n]+)", body)
        type_match = re.search(r"\.type\s*=\s*TYPE_([A-Z]+)", body)
        category_match = re.search(r"\.category\s*=\s*DAMAGE_CATEGORY_([A-Z]+)", body)
        result[match.group(1)] = (
            (lambda expression: (int(re.findall(r"\d+", expression)[-2]) if "?" in expression and len(re.findall(r"\d+", expression)) >= 2 else int(re.findall(r"\d+", expression)[0])) if re.findall(r"\d+", expression) else 0)(power_match.group(1)) if power_match else 0,
            type_match.group(1) if type_match else "UNKNOWN",
            category_match.group(1) if category_match else "STATUS",
        )
    return result


def tutor_badges() -> tuple[dict[str, str], dict[str, int]]:
    text = TUTORS.read_text(encoding="utf-8")
    labels, badges = {}, {}
    for name, body in re.findall(r"const u16 (g[A-Za-z0-9]+)\[\]\s*=\s*\{(.*?)\};", text, re.S):
        if name.startswith("gTechTutor"):
            number = re.search(r"(\d+)Badge", name)
            badge = int(number.group(1)) if number else 0
            label = f"Tech Tutor ({badge} badges)" if badge else "costless Tech Tutor (always)"
        elif name.startswith("gPreGym"):
            badge = int(re.search(r"gPreGym(\d+)", name).group(1)) - 1
            label = f"Center Tutor (before Gym {badge + 1})"
        elif name == "gEliteFourTutor":
            badge, label = 8, "Center Tutor (League)"
        elif name == "gLegacyTutor":
            badge, label = 9, "Legacy Tutor"
        else:
            continue
        for move in re.findall(r"MOVE_[A-Z0-9_]+", body):
            if move not in badges or badge > badges[move]:
                badges[move], labels[move] = badge, label
    return labels, badges


def final_tiers(species) -> dict[str, int]:
    text = TIER_DOC.read_text(encoding="utf-8")
    tiers = {mon.name: 3 for mon in species}
    sections = []
    for match in re.finditer(r"^## (Always|Ends at) ([1-6]) Points?", text, re.M):
        end = text.find("\n## ", match.end())
        sections.append((int(match.group(2)), text[match.end():end if end >= 0 else None]))
    for mon in species:
        names = {qualified_name(mon), mon.display_name, display_constant(mon.name)}
        for tier, section in sections:
            if any(re.search(rf"(?<![A-Za-z]){re.escape(name)}(?![A-Za-z-])", section, re.I) for name in names):
                tiers[mon.name] = max(tiers.get(mon.name, 0), tier) if "Always" in section[:0] else tier
    # Ability-dependent cases: use the stronger final value to avoid over-privileging them.
    tiers.update({"NINETALES": 6, "POLITOED": 6, "PELIPPER": 6, "GLIMMORA": 6})
    return tiers


def frequency_by_type(species, pools) -> dict[str, Counter]:
    result = defaultdict(Counter)
    for mon in species:
        for mon_type in mon.types:
            result[mon_type].update(pools[mon.name]["total"])
    return result


def source_label(methods: set[str]) -> str:
    order = [name for name in ("level-up", "egg", "pre-evolution", "TM", "tutor") if name in methods]
    return "/".join(order) if order else "deliberate design exception"


def rationale(mon, move: str, methods: set[str], dex: str) -> str:
    pretty = display_constant(move, "MOVE_")
    lower = dex.lower()
    special = {
        "MOVE_EARTH_POWER": "Its grounded or geological flavor makes this a defensible boundary-pushing coverage choice.",
        "MOVE_MYSTICAL_FIRE": "Its supernatural or elegant fire identity makes the move feel native rather than generic coverage.",
        "MOVE_GRASSY_TERRAIN": "It is strongly associated with vegetation or cultivating a local ecosystem.",
        "MOVE_TRAILBLAZE": "Its terrestrial movement and plant association support an active Grass attack rather than generic TM access.",
        "MOVE_STRENGTH_SAP": "Its draining or parasitic flavor supports a distinctive utility niche.",
        "MOVE_POLLEN_PUFF": "Its flower, pollen, or caregiving identity supports both the attack and ally-heal flavor.",
        "MOVE_POWER_GEM": "Its mineral, jewel, light, or crystalline anatomy gives the attack a visible source.",
        "MOVE_HYPER_VOICE": "Its voice, cry, song, or sound-based identity makes this natural level-up expression.",
        "MOVE_BOOMBURST": "Its exceptional sound-producing anatomy justifies rare access to this premium attack.",
        "MOVE_BODY_PRESS": "Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive.",
        "MOVE_PSYCHIC_FANGS": "Its pronounced jaws or fangs give the unusual Psychic coverage a physical basis.",
    }
    if move in special:
        return special[move]
    if any(word in lower for word in ("wing", "bird", " fly", "sky")):
        return "Its aerial anatomy makes this a visible extension of how it already fights."
    if any(word in lower for word in ("jaw", "fang", "bite", "tooth")):
        return "Its jaw-based anatomy gives the coverage a concrete physical source."
    if any(word in lower for word in ("shell", "armor", "rock", "stone", "metal", "steel")):
        return "Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage."
    if any(word in lower for word in ("song", "voice", "sound", "cry")):
        return "Its established sound motif makes this a strong identity move."
    if "egg" in methods:
        return "Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough."
    if "level-up" in methods:
        return "Restoring historical natural access preserves established species flavor."
    return "Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche."


def curve_level(power: int, tier: int, stab: bool) -> int:
    thresholds = [(40, 15), (50, 19), (60, 26), (65, 33), (70, 36), (75, 42), (85, 50), (10_000, 58)]
    level = next(level for cap, level in thresholds if power <= cap)
    if tier <= 1:
        level -= 7
    elif tier == 2:
        level -= 4
    elif tier >= 5:
        level += 3
    if not stab:
        level -= 2
    return max(10, level)


def main() -> None:
    info = load_species_info(DEFAULT_SPECIES_DIR)
    games = load_game_data(DEFAULT_DATA_DIR)
    pools = collect_move_pools(games)
    mons = sorted((m for m in info.values() if m.fully_evolved and m.name in pools), key=lambda m: (m.name.split("_")[0], m.name))
    current, dex = current_learnsets()
    profiles = battle_profiles()
    methods = historical_methods(games)
    presence = game_presence(games)
    modern_counts = modern_distribution_counts(games)
    data = move_data()
    tutor_labels, tutor_unlocks = tutor_badges()
    tiers = final_tiers(mons)
    frequencies = frequency_by_type(mons, pools)
    type_counts = Counter(mon_type for mon in mons for mon_type in mon.types)

    lines = [
        "# Standout level-up learnset flourishes",
        "",
        "> Design workbook, not an implementation list. Each entry is a compact shortlist for review against encounter timing, evolution level, and the final trainer curve.",
        "",
        f"This pass covers **{len(mons)}** fully evolved species or mechanically distinct forms represented in both the repository and the bundled historical learnset corpus. Cosmetic forms and Mega Evolutions are omitted. Historical precedent is unioned across **{len(games)}** game datasets. Repository Pokédex prose is the default flavor source; external species references should be used for borderline calls before implementation.",
        "",
        "## Reading the entries",
        "",
        "- **Add** is a proposed level-up flourish, not blanket permission for the whole family. A source in parentheses records historical precedent.",
        "- **Earlier power** proposes a useful damaging move near the stated level. Levels follow the requested badge curve, with modest acceleration for final-tier 1–2 Pokémon. They must still be reconciled with actual availability and evolution timing.",
        "- **Tutor context** calls out current Center/Tech Tutor timing. Costless Tech Tutor moves receive little novelty credit; late tutors receive more.",
        "- Final tier is conservatively treated as the stronger value for ability-dependent weather/terrain cases. Tier 5–6 entries often receive an `already distinctive` recommendation instead of more privilege.",
        "- Setup is opt-in. Dragon Dance, Quiver Dance, Swords Dance, Nasty Plot, Shift Gear, Shell Smash, and similar moves are filtered unless explicitly discussed. Baton Pass is never proposed here.",
        "- Coverage is checked against the attacking stat that actually uses it. A rare move is not valuable when the relevant offense is unusable; deliberate mixed branches are called out explicitly.",
        "- Guard Split is excluded from level-up recommendations because it is now a costless Tech Tutor option; historical egg access no longer makes it a meaningful flourish.",
        "",
        "## Global setup calls",
        "",
        "- **Dustox — Quiver Dance:** reasonable before post-game because 50 Sp. Atk and 65 Speed limit the payoff; do not pair it with Baton Pass.",
        "- **Seviper — Coil:** one of the cleanest flavor/mechanics fits; Coil patches physical accuracy and bulk but not its poor Speed.",
        "- **Tropius — Dragon Dance:** acceptable substantially earlier than the general tutor because 68 Attack and 51 Speed require real help.",
        "- **Weavile — Nasty Plot:** an allowed creative special branch because 45 Sp. Atk keeps it a sidegrade. Hone Claws remains too efficient for its normal physical plan.",
        "",
        "## Distribution ecosystem decisions",
        "",
        "These allocations compare candidates with current natural learners, not just with historical compatibility. They are intended to keep easily justified moves from becoming generic.",
        "",
        "| Move family | Existing natural ecosystem | Priority additions | Deliberately deferred |",
        "|---|---|---|---|",
        "| Grassy Terrain | 15 setters already cover Grass/Poison special status (Vileplume/Roserade), fast offense (Meowscarada), premium physical terrain (Rillaboom), support (Comfey), and legendary field control | Parasect, Meganium, Sunflora, Torterra, Gogoat | Venusaur is lower priority because it overlaps Vileplume/Roserade in typing, bulk, status, and special Grass play; Serperior and Sceptile need less help |",
        "| Special Ground | Earth Power already has 22 natural users | Cradily, Sunflora, Arboliva, Sandy Wormadam, Whiscash, Seismitoad | Hisuian Avalugg and other unusably low-Sp. Atk physical bodies; broad TM compatibility alone is insufficient |",
        "| Physical Ground | Earthquake has 31 natural users; High Horsepower only 7 | Earthquake Aggron; High Horsepower Hisuian Avalugg, Donphan, Zebstrika, Bouffalant | Avoid duplicating Earthquake where High Horsepower better communicates charging anatomy |",
        "| Heated sand | Scorching Sands has no natural users in the current file | Maractus, Cacturne, Palossand | Physical desert species with poor Sp. Atk should retain Earthquake/High Horsepower rather than receiving decorative special coverage |",
        "| Item disruption | Knock Off already has 36 natural users and is a League tutor | Persian, Alolan Persian, Ambipom, Liepard, Thievul, Watchog, Shiftry | Strong high-tier attackers and species lacking a thief, scavenger, grasping-limb, or disruptive role |",
        "| Crushing Steel | Hard Press has no natural users | Aggron, Hisuian Avalugg, Stonjourner, Copperajah, Revavroom | Light or special Steel types; mere TM compatibility is not enough |",
        "",
        "## Modern teachable-heavy move audit",
        "",
        "These counts use the full bundled historical corpus. `Teachable` means TM or tutor in at least one dataset; it does not mean the species currently has that access in Elastic Emerald. A tiny natural column beside a large teachable column is distribution debt, not an instruction to naturalize the move broadly.",
        "",
        "| Move | Historical level-up learners | Historical teachable learners | Proposed natural identity owners |",
        "|---|---:|---:|---|",
    ]
    allocation_owners = defaultdict(list)
    for allocation_map in (CURATED_ADDITIONS, MODERN_LEVELUP_ALLOCATIONS):
        for species, allocations in allocation_map.items():
            for move, _, _ in allocations:
                if move in MODERN_MOVES:
                    allocation_owners[move].append(qualified_name(info[species]) if species in info else display_constant(species))
    for move in MODERN_MOVES:
        level_count, teachable_count = modern_counts[move]
        owners = ", ".join(allocation_owners.get(move, [])) or "No new natural owner proposed"
        lines.append(
            f"| {display_constant(move, 'MOVE_')} | {level_count} | {teachable_count} | {owners} |"
        )
    lines += [
        "",
        "Compatibility gaps are assessed separately. Presence is inferred directly from whether the species has an entry in `swsh.json` and `sv.json`. Absence from Sword/Shield or Scarlet/Violet is evidence that a species may simply have missed a distribution pass; it is not by itself proof that every new move fits.",
        "",
        "## Species suggestions",
        "",
    ]

    for mon in mons:
        tier = tiers.get(mon.name, 3)
        existing = set(current.get(mon.name, {}))
        profile = profiles.get(mon.name, {"stats": {}, "abilities": []})
        stats = profile["stats"]
        candidates = []
        for move, provenance in methods.get(mon.name, {}).items():
            if move in existing or move in EXCLUDED or move in GENERIC_LOW_VALUE or move in SETUP_MOVES:
                continue
            if move in ECOSYSTEM_MOVES or move in MODERN_MOVES:
                continue
            power, move_type, category = data.get(move, (0, "UNKNOWN", "STATUS"))
            # Old pre-evolution filler is not a flourish on a final stage. Utility moves
            # and priority attacks are considered separately through PRIORITY_MOVES.
            if category != "STATUS" and power < 50 and move not in PRIORITY_MOVES:
                continue
            if power and category in ("PHYSICAL", "SPECIAL"):
                relevant = stats.get("Attack" if category == "PHYSICAL" else "SpAttack", 0)
                other = stats.get("SpAttack" if category == "PHYSICAL" else "Attack", 0)
                deliberate_mixed = mon.name in {"AZUMARILL", "CRAWDAUNT"}
                if move_type not in mon.types and (relevant < 60 or relevant + 25 < other):
                    continue
                if move_type in mon.types and relevant + 35 < other and not deliberate_mixed:
                    continue
            prevalence = min((frequencies[t][move] / type_counts[t] for t in mon.types), default=1)
            score = (5 if "egg" in provenance else 0) + (4 if "level-up" in provenance else 0)
            score += (2.5 if prevalence < .08 else 1 if prevalence < .20 else 0)
            score += 3 if move in PRIORITY_MOVES else 0
            score += min(tutor_unlocks.get(move, 4), 8) * .18
            if power and move_type in mon.types:
                score += 2
            elif power >= 70:
                score += 1
            if category == "STATUS" and move not in PRIORITY_MOVES:
                score -= 1.5
            if power and category in ("PHYSICAL", "SPECIAL"):
                relevant = stats.get("Attack" if category == "PHYSICAL" else "SpAttack", 0)
                other = stats.get("SpAttack" if category == "PHYSICAL" else "Attack", 0)
                score += max(-2, min(2, (relevant - other) / 25))
            candidates.append((score, move, provenance, power, move_type, category, prevalence))
        candidates.sort(reverse=True)

        desired = 3 if tier <= 1 else 2 if tier <= 3 else 1
        if tier >= 5:
            desired = 1 if candidates and candidates[0][0] >= 11 else 0
        allocations = CURATED_ADDITIONS.get(mon.name, []) + MODERN_LEVELUP_ALLOCATIONS.get(mon.name, [])
        curated_details = {
            move: (why, level)
            for move, why, level in allocations
            if move not in existing
        }
        curated = [
            (100, move, methods.get(mon.name, {}).get(move, {"ecosystem allocation"}),
             *data.get(move, (0, "UNKNOWN", "STATUS")),
             min((frequencies[t][move] / type_counts[t] for t in mon.types), default=0))
            for move in curated_details
        ]
        chosen = curated + [item for item in candidates if item[1] not in curated_details][
            :max(0, desired - len(curated))
        ]
        if mon.name == "CRAWDAUNT":
            chosen = [
                (98, move, methods[mon.name].get(move, {"deliberate mixed-offense exception"}),
                 *data.get(move, (0, "UNKNOWN", "STATUS")),
                 min((frequencies[t][move] / type_counts[t] for t in mon.types), default=0))
                for move in ("MOVE_DARK_PULSE", "MOVE_BRINE")
                if move not in existing
            ]
        if mon.name == "NINETALES" and "MOVE_MYSTICAL_FIRE" not in existing:
            chosen = [(99, "MOVE_MYSTICAL_FIRE", methods[mon.name].get("MOVE_MYSTICAL_FIRE", {"deliberate identity exception"}),
                       *data.get("MOVE_MYSTICAL_FIRE", (75, "FIRE", "SPECIAL")),
                       min((frequencies[t]["MOVE_MYSTICAL_FIRE"] / type_counts[t] for t in mon.types), default=0))]
        setup = SETUP_EXCEPTIONS.get(mon.name)
        if setup and setup[0] not in existing:
            chosen.insert(0, (99, setup[0], {"deliberate setup exception"}, *data.get(setup[0], (0, "UNKNOWN", "STATUS")), 0))

        lines.append(f"### {qualified_name(mon)}")
        lines.append("")
        lines.append(f"**Type:** {type_label(mon.types)} · **Final tier weight:** {tier}")
        attack = stats.get("Attack", "?")
        sp_attack = stats.get("SpAttack", "?")
        speed = stats.get("Speed", "?")
        abilities = ", ".join(display_constant(ability) for ability in profile["abilities"] if ability != "NONE") or "unknown"
        lines.append(f"**Role profile:** Atk {attack} / Sp. Atk {sp_attack} / Spe {speed} · {abilities}")
        swsh = "present" if mon.name in presence.get("swsh", set()) else "absent"
        sv = "present" if mon.name in presence.get("sv", set()) else "absent"
        lines.append(f"**Modern-game datasets:** Sword/Shield {swsh} · Scarlet/Violet {sv}")
        lines.append("")
        if not chosen:
            lines.append("- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.")
        for _, move, provenance, power, move_type, category, prevalence in chosen:
            pretty = display_constant(move, "MOVE_")
            source = source_label(provenance)
            context = f"; {tutor_labels[move]}" if move in tutor_labels else "; no Center/Tech Tutor overlap"
            why = (curated_details[move][0] + ".") if move in curated_details else (setup[1].capitalize() + "." if setup and move == setup[0] else rationale(mon, move, provenance, dex.get(mon.name, "")))
            lines.append(f"- **Add — {pretty}:** {why} *Precedent: {source}; type-cohort prevalence {prevalence:.0%}{context}.*")

        for move, why in COMPATIBILITY_GAPS.get(mon.name, []):
            lines.append(
                f"- **Compatibility gap — {display_constant(move, 'MOVE_')}:** Verify or add TM/tutor compatibility rather than level-up access; {why}."
            )

        if setup and setup[0] in existing:
            old_level = current[mon.name][setup[0]]
            target = 38 if mon.name == "WEAVILE" else 34 if mon.name == "TROPIUS" else 30
            lines.append(
                f"- **Earlier setup — {display_constant(setup[0], 'MOVE_')} around Lv. {target}:** "
                f"Move it forward from Lv. {old_level}; {setup[1]}. Do not pair this access with Baton Pass."
            )

        if mon.name == "NINETALES" and "MOVE_MYSTICAL_FIRE" in existing:
            old_level = current[mon.name]["MOVE_MYSTICAL_FIRE"]
            lines.append(f"- **Identity anchor — Mystical Fire:** Keep it natural and consider Lv. 34–38 instead of Lv. {old_level}; this is the exemplary mystical-fire flourish even though Ninetales needs no broad coverage buff.")
        if mon.name == "CRAWDAUNT":
            lines.append("- **Mixed-offense branch:** Its 80 BP Dark Pulse STAB lets 95 Sp. Atk matter for a stretch without improving Crawdaunt's dominant physical Adaptability ceiling. Brine is the gentler 65 BP alternative.")

        damaging = [item for item in chosen if item[3] >= 40 and item[5] != "STATUS"]
        if damaging:
            _, move, _, power, move_type, _, _ = max(damaging, key=lambda item: (item[3], item[1]))
            stab = move_type in mon.types
            level = curated_details[move][1] if move in curated_details else (35 if mon.name == "CRAWDAUNT" and move == "MOVE_DARK_PULSE" else curve_level(power, tier, stab))
            power_text = f"up to {power} BP (HP-dependent)" if move == "MOVE_HARD_PRESS" else f"{power} BP"
            lines.append(f"- **Earlier power — {display_constant(move, 'MOVE_')} around Lv. {level}:** {power_text}; {'STAB' if stab else 'coverage'}. Treat this as the curve target, not a fixed slot.")
        else:
            lines.append("- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.")
        lines.append("")

    lines += [
        "## Follow-up review checklist", "",
        "1. Confirm each proposed level against the earliest obtainable/evolution level and important boss ownership.",
        "2. Recheck final tier values for ability-dependent species and any tier document/source drift.",
        "3. Reject coverage whose only support is a one-off legacy TM if anatomy or Pokédex text does not independently support it.",
        "4. Audit every accepted setup move together with Speed, relevant offense, priority, Baton Pass access, and alternative boosting moves.",
        "5. Re-run this workbook after `gen_9.h` leaves WIP status; many `no priority` calls may simply reflect already-expanded local learnsets.",
        "",
        "## Research sources", "",
        "- Repository species descriptions and stats: `src/data/pokemon/species_info/`.",
        "- Current level-up sets: `src/data/pokemon/level_up_learnsets/gen_9.h`.",
        "- Historical learnsets: `tools/learnset_helpers/porymoves_files/`.",
        "- Current tutor timing: `src/data/pokemon/center_tutor_moves.h`.",
        "- Tier policy: `docs/gameplay/tier-points.md` and `GetMonTierPoints`.",
        "- External flavor cross-check: [PokéAPI species flavor-text documentation](https://pokeapi.github.io/pokeapi.co/v2/) and [Bulbapedia species biology/learnset pages](https://bulbapedia.bulbagarden.net/wiki/Pok%C3%A9mon). These are secondary checks; no external text is copied into this document.",
    ]
    OUTPUT.write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(f"Wrote {OUTPUT} with {len(mons)} species entries")


if __name__ == "__main__":
    main()
