"""Read move data directly from the current Elastic Emerald source tree."""

from __future__ import annotations

import re
from pathlib import Path

from .spreadsheet_config import species_map_arr, teachable_categories, tm_map

REPO_ROOT = Path(__file__).resolve().parents[2]
POKEMON_DATA = REPO_ROOT / "src" / "data" / "pokemon"


def _read(relative_path: str) -> str:
    return (POKEMON_DATA / relative_path).read_text(encoding="utf-8")


def extract_move_array(content: str, array_name: str | None, *, required: bool = True) -> list[str]:
    if array_name is None:
        return []
    pattern = rf"(?:static\s+)?const\s+u16\s+{re.escape(array_name)}\[\]\s*=\s*\{{(.*?)\}};"
    match = re.search(pattern, content, re.DOTALL)
    if match is None:
        if not required:
            return []
        raise ValueError(f"move array not found: {array_name}")
    constants = re.findall(r"\bMOVE_[A-Z0-9_]+\b", match.group(1))
    return [_display_move(move) for move in constants if move != "MOVE_UNAVAILABLE"]


def extract_level_up_moves(content: str, array_name: str | None) -> list[dict[str, object]]:
    if array_name is None:
        return []
    pattern = rf"static\s+const\s+struct\s+LevelUpMove\s+{re.escape(array_name)}\[\]\s*=\s*\{{(.*?)\}};"
    match = re.search(pattern, content, re.DOTALL)
    if match is None:
        raise ValueError(f"level-up array not found: {array_name}")
    moves = re.findall(r"LEVEL_UP_MOVE\(\s*(\d+)\s*,\s*(MOVE_[A-Z0-9_]+)\s*\)", match.group(1))
    return [{"level": int(level), "move": _display_move(move)} for level, move in moves]


def _display_move(move: str) -> str:
    return move.removeprefix("MOVE_").replace("_", " ").title()


def load_species_data() -> list[dict[str, object]]:
    level_up = _read("level_up_learnsets/gen_9.h")
    egg_moves = _read("egg_moves.h")
    teachable = _read("teachable_learnsets.h")
    return [
        {
            "species_id": species["species_id"],
            "species_number": species["species_number"],
            "egg_move_reference": extract_move_array(egg_moves, species["egg_move_reference"], required=False),
            "teachable_reference": extract_move_array(teachable, species["teachable_reference"]),
            "levelup_reference": extract_level_up_moves(level_up, species["levelup_reference"]),
        }
        for species in species_map_arr
    ]


def load_teachable_mappings() -> list[dict[str, object]]:
    tutor_content = _read("center_tutor_moves.h")
    definitions = [
        (teachable_categories.tutor_str, 0, "gPreGym1Tutor"),
        (teachable_categories.setup_tutor_str, 0, "gPreGym1TutorSetup"),
        (teachable_categories.tech_tutor_str, 0, "gTechTutorAlways"),
        (teachable_categories.tutor_str, 1, "gPreGym2Tutor"),
        (teachable_categories.setup_tutor_str, 1, "gPreGym2TutorSetup"),
        (teachable_categories.tech_tutor_str, 1, "gTechTutor1Badge"),
        (teachable_categories.tutor_str, 2, "gPreGym3Tutor"),
        (teachable_categories.setup_tutor_str, 2, "gPreGym3TutorSetup"),
        (teachable_categories.tech_tutor_str, 2, "gTechTutor2Badge"),
        (teachable_categories.tutor_str, 3, "gPreGym4Tutor"),
        (teachable_categories.setup_tutor_str, 3, "gPreGym4TutorSetup"),
        (teachable_categories.tech_tutor_str, 3, "gTechTutor3Badge"),
        (teachable_categories.tutor_str, 4, "gPreGym5Tutor"),
        (teachable_categories.setup_tutor_str, 4, "gPreGym5TutorSetup"),
        (teachable_categories.tutor_str, 5, "gPreGym6Tutor"),
        (teachable_categories.setup_tutor_str, 5, "gPreGym6TutorSetup"),
        (teachable_categories.tutor_str, 6, "gPreGym7Tutor"),
        (teachable_categories.setup_tutor_str, 6, "gPreGym7TutorSetup"),
        (teachable_categories.tutor_str, 7, "gPreGym8Tutor"),
        (teachable_categories.setup_tutor_str, 7, "gPreGym8TutorSetup"),
        (teachable_categories.tutor_str, 8, "gEliteFourTutor"),
        (teachable_categories.tutor_str, 9, "gLegacyTutor"),
    ]
    mappings = [
        {
            "type": category,
            "num_badges": badges,
            "data": extract_move_array(tutor_content, symbol),
        }
        for category, badges, symbol in definitions
    ]
    mappings.extend(
        {
            "type": teachable_categories.tms_str,
            "num_badges": entry["num_badges"],
            "data": entry["tms"],
        }
        for entry in tm_map
    )
    return mappings
