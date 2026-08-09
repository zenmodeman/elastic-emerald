#!/usr/bin/env python3

"""
Usage: python3 make_learnables.py INPUTS_DIR OUTPUT_FILE

Build a primary store of learnable moves for each species based on input documents. This script
is meant to be run to generate a pre-processed store of data that should not change very much;
thus, it can safely be pre-computed in order to speed up incremental builds for end-users.
"""

from functools import reduce

import json
import pathlib
import sys


TEACHABLE_MOVE_SOURCES = {
    "MOVE_MIMIC": {"sv.json", "za.json", "elastic.json"},
    "MOVE_CONFIDE": {"sv.json", "elastic.json"},
    "MOVE_CAPTIVATE": {"sv.json", "elastic.json"},
    "MOVE_TOXIC": {"swsh.json", "sv.json", "la.json", "bdsp.json", "elastic.json"},
    "MOVE_SCALD": {"sv.json", "za.json", "elastic.json"},
    "MOVE_BIDE": {"sv.json", "elastic.json"},
    "MOVE_NATURAL_GIFT": {"sv.json", "elastic.json"},
}

SPECIES_ALIASES = {
    "FARFETCHÂ€™D": "FARFETCHD",
    "MR. MIME": "MR_MIME",
    "MIME JR.": "MIME_JR",
    "PORYGON-Z": "PORYGON_Z",
    "FLABÃ©BÃ©": "FLABEBE",
    "SIRFETCHÂ€™D": "SIRFETCHD",
    "MR. RIME": "MR_RIME",
}


def from_single(fname: pathlib.Path) -> dict[str, set[str]]:
    with open(fname, "r") as fp:
        data = json.load(fp)

    out = {}

    for species, by_method in data.items():
        moves = set()

        # Level-up
        for lvl in by_method["LevelMoves"]:
            moves.add(lvl["Move"])

        # Egg
        moves.update(by_method["EggMoves"])

        # Tutor
        moves.update(
            move
            for move in by_method["TutorMoves"]
            if move not in TEACHABLE_MOVE_SOURCES or fname.name in TEACHABLE_MOVE_SOURCES[move]
        )

        # TM
        for move in by_method["TMMoves"]:
            if move in TEACHABLE_MOVE_SOURCES and fname.name not in TEACHABLE_MOVE_SOURCES[move]:
                continue
            moves.add(move)

        out[SPECIES_ALIASES.get(species, species)] = moves

    return out

def from_batch(dir: pathlib.Path) -> dict[str, set[str]]:
    return reduce(
        lambda acc, single: {
            species: acc.get(species, set()) | single.get(species, set())
            for species in acc.keys() | single.keys()
        },
        map(from_single, dir.glob("*.json")),
        {},
    )


def main():
    if len(sys.argv) < 3:
        print("Missing required arguments", file=sys.stderr)
        print(__doc__, file=sys.stderr)
        quit(1)

    INPUTS_DIR = pathlib.Path(sys.argv[1])
    OUTPUT_FILE = pathlib.Path(sys.argv[2])

    assert INPUTS_DIR.exists(), f"{INPUTS_DIR=} does not exist"
    assert INPUTS_DIR.is_dir(), f"{INPUTS_DIR=} is not a directory"
    assert OUTPUT_FILE.parent.exists(), f"parent of {OUTPUT_FILE=} does not exist"

    batch = {
        species: list(sorted(learnables))
        for species, learnables in from_batch(INPUTS_DIR).items()
    }
    with open(OUTPUT_FILE, "w") as fp:
        json.dump(batch, fp, indent=2)


if __name__ == "__main__":
    main()
