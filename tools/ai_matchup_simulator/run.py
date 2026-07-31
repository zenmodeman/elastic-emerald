#!/usr/bin/env python3
"""Generate and run an all-pairs Smart-AI singles matchup matrix."""

from __future__ import annotations

import argparse
import csv
import hashlib
import json
import re
import subprocess
import sys
import time
from collections import defaultdict
from pathlib import Path


ROOT = Path(__file__).resolve().parents[2]
GENERATED_TEST = ROOT / "test/battle/ai/generated_ai_matchups.c"
DEFAULT_OUTPUT = ROOT / "build/ai-matchups"
IDENTIFIER = re.compile(r"^[A-Z][A-Z0-9_]*$")

CONSTANT_FIELDS = {
    "species": "SPECIES_",
    "nature": "NATURE_",
    "ability": "ABILITY_",
    "item": "ITEM_",
    "tera_type": "TYPE_",
}
NUMERIC_FIELDS = {
    "level": "Level",
    "friendship": "Friendship",
    "hp": "HP",
    "max_hp": "MaxHP",
    "attack": "Attack",
    "defense": "Defense",
    "sp_attack": "SpAttack",
    "sp_defense": "SpDefense",
    "speed": "Speed",
}
EV_FIELDS = ("hp", "attack", "defense", "sp_attack", "sp_defense", "speed")
RESULT_PATTERN = re.compile(r"AI_SIM_RESULT,(\d+),(\d+),(\d+),(\d+),(\d+)")


def constant(value: object, prefix: str, field: str) -> str:
    if not isinstance(value, str):
        raise ValueError(f"{field} must be a string")
    value = value.upper().replace("-", "_").replace(" ", "_")
    if not value.startswith(prefix):
        value = prefix + value
    if not IDENTIFIER.fullmatch(value):
        raise ValueError(f"invalid {field} constant: {value!r}")
    return value


def load_sets(path: Path) -> list[dict]:
    with path.open(encoding="utf-8") as stream:
        document = json.load(stream)
    sets = document.get("sets") if isinstance(document, dict) else document
    if not isinstance(sets, list) or len(sets) < 2:
        raise ValueError("input must contain a 'sets' array with at least two sets")

    normalized = []
    names = set()
    for index, raw in enumerate(sets):
        if not isinstance(raw, dict):
            raise ValueError(f"set {index} must be an object")
        allowed_fields = {"name", "moves", "evs"} | set(CONSTANT_FIELDS) | set(NUMERIC_FIELDS)
        unknown_fields = set(raw) - allowed_fields
        if unknown_fields:
            raise ValueError(f"set {index} has unknown fields: {', '.join(sorted(unknown_fields))}")
        name = raw.get("name")
        if not isinstance(name, str) or not name.strip():
            raise ValueError(f"set {index} needs a non-empty name")
        if name in names:
            raise ValueError(f"duplicate set name: {name!r}")
        names.add(name)

        current = {"name": name, "species": constant(raw.get("species"), "SPECIES_", "species")}
        for field, prefix in CONSTANT_FIELDS.items():
            if field != "species" and field in raw:
                current[field] = constant(raw[field], prefix, field)
        moves = raw.get("moves")
        if not isinstance(moves, list) or not 1 <= len(moves) <= 4:
            raise ValueError(f"{name}: moves must contain one to four entries")
        current["moves"] = [constant(move, "MOVE_", "move") for move in moves]
        raw_evs = raw.get("evs", {})
        if not isinstance(raw_evs, dict):
            raise ValueError(f"{name}: evs must be an object")
        unknown_evs = set(raw_evs) - set(EV_FIELDS)
        if unknown_evs:
            raise ValueError(f"{name}: unknown EV fields: {', '.join(sorted(unknown_evs))}")
        current["evs"] = {}
        for field in EV_FIELDS:
            value = raw_evs.get(field, 0)
            if not isinstance(value, int) or not 0 <= value <= 252:
                raise ValueError(f"{name}: {field} EV must be an integer from 0 to 252")
            current["evs"][field] = value
        if sum(current["evs"].values()) > 510:
            raise ValueError(f"{name}: EV total cannot exceed 510")
        for field in NUMERIC_FIELDS:
            if field in raw:
                if not isinstance(raw[field], int) or raw[field] < 0:
                    raise ValueError(f"{name}: {field} must be a non-negative integer")
                current[field] = raw[field]
        normalized.append(current)
    return normalized


def emit_set(side: str, item: dict) -> list[str]:
    lines = [f"        {side}({item['species']}) {{"]
    if "level" in item:
        lines.append(f"            Level({item['level']});")
    if "nature" in item:
        lines.append(f"            Nature({item['nature']});")
    lines.append("            IVs(31, 31, 31, 31, 31, 31);")
    evs = item["evs"]
    lines.append(f"            EVs({', '.join(str(evs[field]) for field in EV_FIELDS)});")
    for field, function in NUMERIC_FIELDS.items():
        if field not in ("level",) and field in item:
            lines.append(f"            {function}({item[field]});")
    for field, function in (("ability", "Ability"), ("item", "Item"), ("tera_type", "TeraType")):
        if field in item:
            lines.append(f"            {function}({item[field]});")
    lines.append(f"            Moves({', '.join(item['moves'])});")
    lines.append("        }")
    return lines


def seed_state(base_seed: int, matchup: int, repeat: int) -> tuple[int, int, int, int]:
    digest = hashlib.sha256(f"{base_seed}:{matchup}:{repeat}".encode()).digest()
    values = [int.from_bytes(digest[offset:offset + 4], "little") for offset in range(0, 12, 4)]
    return values[0], values[1], values[2], 1


def generate_test(sets: list[dict], repeats: int, base_seed: int) -> tuple[str, list[dict]]:
    lines = [
        '#include "global.h"',
        '#include "test/battle.h"',
        "",
        "// Generated by tools/ai_matchup_simulator/run.py. Do not edit.",
        "",
    ]
    manifest = []
    matchup = 0
    for left in range(len(sets)):
        for right in range(left + 1, len(sets)):
            for repeat in range(repeats):
                # Alternate engine sides, then normalize the outcome in Python.
                player, opponent = (left, right) if repeat % 2 == 0 else (right, left)
                seed = seed_state(base_seed, matchup, repeat)
                test_name = f"ZenmodemanSim: AI matchup simulation {matchup:04d}-{repeat:03d}"
                lines.extend([
                    f'AI_VS_AI_SINGLE_BATTLE_TEST("{test_name}")',
                    "{",
                    "    GIVEN {",
                    f"        rng_value_t seed = {{{seed[0]}u, {seed[1]}u, {seed[2]}u, {seed[3]}u}};",
                    "        RNGSeed(seed);",
                    "        AI_FLAGS(AI_FLAG_SMART_TRAINER);",
                ])
                lines.extend(emit_set("PLAYER", sets[player]))
                lines.extend(emit_set("OPPONENT", sets[opponent]))
                lines.extend([
                    "    } THEN {",
                    f'        Test_MgbaPrintf("AI_SIM_RESULT,{matchup},{repeat},{player},%d,%d\\n", gBattleOutcome, gBattleResults.battleTurnCounter + 1);',
                    "        EXPECT(gBattleOutcome == B_OUTCOME_WON",
                    "            || gBattleOutcome == B_OUTCOME_LOST",
                    "            || gBattleOutcome == B_OUTCOME_DREW);",
                    "    }",
                    "}",
                    "",
                ])
                manifest.append({
                    "matchup": matchup,
                    "repeat": repeat,
                    "set_a": left,
                    "set_b": right,
                    "player": player,
                    "opponent": opponent,
                })
            matchup += 1
    return "\n".join(lines), manifest


def write_csv(path: Path, rows: list[dict], fields: list[str]) -> None:
    with path.open("w", newline="", encoding="utf-8") as stream:
        writer = csv.DictWriter(stream, fieldnames=fields)
        writer.writeheader()
        writer.writerows(rows)


def format_duration(seconds: float) -> str:
    seconds = max(0, round(seconds))
    hours, remainder = divmod(seconds, 3600)
    minutes, seconds = divmod(remainder, 60)
    if hours:
        return f"{hours:d}:{minutes:02d}:{seconds:02d}"
    return f"{minutes:d}:{seconds:02d}"


def progress_text(completed: int, total: int, started: float, now: float) -> str:
    elapsed = max(0.0, now - started)
    fraction = completed / total if total else 1.0
    width = 24
    filled = min(width, int(fraction * width))
    bar = "#" * filled + "-" * (width - filled)
    rate = completed / elapsed if elapsed > 0 else 0.0
    eta = (total - completed) / rate if rate > 0 else 0.0
    eta_text = format_duration(eta) if completed else "--:--"
    return (f"[{bar}] {completed}/{total} ({fraction:6.2%})  "
            f"elapsed {format_duration(elapsed)}  ETA {eta_text}  {rate:.2f} battles/s")


def run_simulations(command: list[str], total: int, verbose: bool = False) -> tuple[int, str]:
    print(f"Building the simulation test runner for {total} battles...", file=sys.stderr, flush=True)
    started = time.monotonic()
    process = subprocess.Popen(
        command,
        cwd=ROOT,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        bufsize=1,
    )
    assert process.stdout is not None
    output = []
    completed_trials = set()
    interactive = sys.stderr.isatty()
    noninteractive_step = max(1, total // 20)

    for line in process.stdout:
        output.append(line)
        if verbose:
            sys.stdout.write(line)
            sys.stdout.flush()
        changed = False
        for match in RESULT_PATTERN.finditer(line):
            key = (int(match.group(1)), int(match.group(2)))
            if key not in completed_trials:
                completed_trials.add(key)
                changed = True
        completed = len(completed_trials)
        if changed and (interactive or completed == total or completed % noninteractive_step == 0):
            status = progress_text(completed, total, started, time.monotonic())
            if interactive:
                sys.stderr.write("\r\033[K" + status)
                sys.stderr.flush()
            else:
                print(status, file=sys.stderr, flush=True)

    return_code = process.wait()
    if interactive:
        sys.stderr.write("\n")
    if return_code == 0 and len(completed_trials) == total:
        print(f"Simulation battles complete in {format_duration(time.monotonic() - started)}; processing reports...", file=sys.stderr, flush=True)
    return return_code, "".join(output)


def aggregate(sets: list[dict], manifest: list[dict], output: str) -> tuple[list[dict], list[dict], list[dict]]:
    found = {(int(a), int(b)): (int(c), int(d), int(e)) for a, b, c, d, e in RESULT_PATTERN.findall(output)}
    if len(found) != len(manifest):
        missing = [(entry["matchup"], entry["repeat"]) for entry in manifest if (entry["matchup"], entry["repeat"]) not in found]
        raise RuntimeError(f"received {len(found)}/{len(manifest)} simulation results; missing {missing[:8]}")

    trials = []
    totals = defaultdict(lambda: {"wins": 0, "losses": 0, "draws": 0, "turns": 0})
    pair_totals = defaultdict(lambda: {"wins_a": 0, "wins_b": 0, "draws": 0, "turns": 0, "battles": 0})
    for entry in manifest:
        player, outcome, turns = found[(entry["matchup"], entry["repeat"])]
        if player != entry["player"]:
            raise RuntimeError(f"player identity mismatch for matchup {entry['matchup']} repeat {entry['repeat']}")
        a, b = entry["set_a"], entry["set_b"]
        if outcome == 1:
            winner = player
        elif outcome == 2:
            winner = entry["opponent"]
        elif outcome == 3:
            winner = None
        else:
            raise RuntimeError(f"unexpected battle outcome {outcome}")

        pair = pair_totals[(a, b)]
        pair["battles"] += 1
        pair["turns"] += turns
        totals[a]["turns"] += turns
        totals[b]["turns"] += turns
        if winner is None:
            result = "draw"
            pair["draws"] += 1
            totals[a]["draws"] += 1
            totals[b]["draws"] += 1
        else:
            result = sets[winner]["name"]
            loser = b if winner == a else a
            pair["wins_a" if winner == a else "wins_b"] += 1
            totals[winner]["wins"] += 1
            totals[loser]["losses"] += 1
        trials.append({
            "matchup": entry["matchup"], "repeat": entry["repeat"],
            "set_a": sets[a]["name"], "set_b": sets[b]["name"],
            "player_side": sets[player]["name"], "winner": result,
            "outcome": outcome, "turns": turns,
        })

    matchups = []
    for (a, b), value in pair_totals.items():
        battles = value["battles"]
        matchups.append({
            "set_a": sets[a]["name"], "set_b": sets[b]["name"],
            "wins_a": value["wins_a"], "wins_b": value["wins_b"], "draws": value["draws"],
            "win_rate_a": f"{value['wins_a'] / battles:.3f}",
            "win_rate_b": f"{value['wins_b'] / battles:.3f}",
            "average_turns": f"{value['turns'] / battles:.2f}",
        })

    rankings = []
    for index, item in enumerate(sets):
        value = totals[index]
        battles = value["wins"] + value["losses"] + value["draws"]
        points = value["wins"] + value["draws"] * 0.5
        rankings.append({
            "set": item["name"], "wins": value["wins"], "losses": value["losses"], "draws": value["draws"],
            "win_rate": f"{value['wins'] / battles:.3f}",
            "score_rate": f"{points / battles:.3f}",
            "average_turns": f"{value['turns'] / battles:.2f}",
        })
    rankings.sort(key=lambda row: (-float(row["score_rate"]), -int(row["wins"]), row["set"]))
    for rank, row in enumerate(rankings, 1):
        row["rank"] = rank
    return trials, matchups, rankings


def write_report(path: Path, rankings: list[dict], matchups: list[dict], repeats: int) -> None:
    lines = [
        "# Smart-AI 1v1 matchup report", "",
        f"Each unordered matchup was simulated {repeats} times. A win is worth 1 point and a draw 0.5.", "",
        "## Rankings", "",
        "| Rank | Set | W | L | D | Win rate | Score rate | Avg. turns |",
        "| ---: | --- | ---: | ---: | ---: | ---: | ---: | ---: |",
    ]
    for row in rankings:
        lines.append(f"| {row['rank']} | {row['set']} | {row['wins']} | {row['losses']} | {row['draws']} | {row['win_rate']} | {row['score_rate']} | {row['average_turns']} |")
    lines.extend(["", "## Matchups", "", "| Set A | Set B | A wins | B wins | Draws | Avg. turns |", "| --- | --- | ---: | ---: | ---: | ---: |"])
    for row in matchups:
        lines.append(f"| {row['set_a']} | {row['set_b']} | {row['wins_a']} | {row['wins_b']} | {row['draws']} | {row['average_turns']} |")
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("sets", type=Path, help="JSON file containing designated Pokemon sets")
    parser.add_argument("--repeats", type=int, default=4, help="trials per unordered matchup (default: 4)")
    parser.add_argument("--seed", type=int, default=1, help="base seed used to derive deterministic trial seeds")
    parser.add_argument("--output", type=Path, default=DEFAULT_OUTPUT, help="report directory")
    parser.add_argument("--generate-only", action="store_true", help="write the generated C scenarios without building or running them")
    parser.add_argument("--verbose", action="store_true", help="also stream all compiler and test-runner output")
    args = parser.parse_args()
    if args.repeats < 1:
        parser.error("--repeats must be positive")

    try:
        sets = load_sets(args.sets)
        source, manifest = generate_test(sets, args.repeats, args.seed)
        GENERATED_TEST.write_text(source, encoding="utf-8")
        if args.generate_only:
            print(f"Generated {len(manifest)} trials in {GENERATED_TEST.relative_to(ROOT)}")
            return 0

        command = ["make", "check", "TESTS=ZenmodemanSim: AI matchup simulation"]
        try:
            return_code, runner_output = run_simulations(command, len(manifest), args.verbose)
        finally:
            GENERATED_TEST.unlink(missing_ok=True)
        if return_code:
            if not args.verbose:
                sys.stdout.write(runner_output)
            return return_code

        trials, matchups, rankings = aggregate(sets, manifest, runner_output)
        args.output.mkdir(parents=True, exist_ok=True)
        write_csv(args.output / "trials.csv", trials, ["matchup", "repeat", "set_a", "set_b", "player_side", "winner", "outcome", "turns"])
        write_csv(args.output / "matchups.csv", matchups, ["set_a", "set_b", "wins_a", "wins_b", "draws", "win_rate_a", "win_rate_b", "average_turns"])
        write_csv(args.output / "rankings.csv", rankings, ["rank", "set", "wins", "losses", "draws", "win_rate", "score_rate", "average_turns"])
        write_report(args.output / "report.md", rankings, matchups, args.repeats)
        (args.output / "runner.log").write_text(runner_output, encoding="utf-8")
        print(f"Completed {len(trials)} trials. Report: {args.output / 'report.md'}")
        return 0
    except (OSError, ValueError, RuntimeError, json.JSONDecodeError) as error:
        print(f"error: {error}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
