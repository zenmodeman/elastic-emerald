# AI-vs-AI 1v1 simulator

The host battle-test runner supports autonomous singles simulations through
`AI_VS_AI_SINGLE_BATTLE_TEST`. Both active Pokemon are controlled by the same
in-game AI path, and the normal battle engine runs the matchup until it reports
a win, loss, or draw. This keeps damage, accuracy, secondary effects, items,
abilities, status, weather, Terastalization, and other mechanics aligned with
the ROM instead of duplicating them in a separate simulator.

## Defining a matchup

Add a scenario under `test/battle/ai`:

```c
AI_VS_AI_SINGLE_BATTLE_TEST("ZenmodemanSim: simulator example")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_SMART_TRAINER);
        PLAYER(SPECIES_BRELOOM) {
            Level(50);
            Nature(NATURE_ADAMANT);
            IVs(31, 31, 31, 31, 31, 31);
            EVs(0, 252, 0, 0, 4, 252);
            Ability(ABILITY_TECHNICIAN);
            Item(ITEM_MUSCLE_BAND);
            Moves(MOVE_MACH_PUNCH, MOVE_BULLET_SEED, MOVE_ROCK_TOMB, MOVE_SPORE);
        }
        OPPONENT(SPECIES_LUCARIO) {
            Level(50);
            Nature(NATURE_ADAMANT);
            Ability(ABILITY_INNER_FOCUS);
            Item(ITEM_BLACK_BELT);
            Moves(MOVE_CLOSE_COMBAT, MOVE_BULLET_PUNCH, MOVE_CRUNCH, MOVE_SWORDS_DANCE);
        }
    } THEN {
        EXPECT(gBattleOutcome == B_OUTCOME_WON
            || gBattleOutcome == B_OUTCOME_LOST
            || gBattleOutcome == B_OUTCOME_DREW);
    }
}
```

`PLAYER` and `OPPONENT` accept the same designated fields as other battle
tests, including level, nature, ability, item, four moves, friendship, HP,
stats, status, and Tera type. `IVs` and `EVs` provide compact six-stat
declarations in HP, Attack, Defense, Special Attack, Special Defense, Speed
order. `EVs` rejects values above the configured per-stat cap and totals above
510, then recalculates stats using the declared nature and IVs. If stats are
omitted, normal Pokemon creation calculates them; autonomous simulations do not apply the scripted test
runner's turn-order-based Speed inference. `gBattleOutcome` is from the player's perspective, and
`gBattleResults.battleTurnCounter` is available in `THEN` for collecting or
asserting turn counts.

The starter scenarios live in `test/battle/ai/ai_vs_ai_simulation.c`. Run them
with `make check TESTS='ZenmodemanSim: AI-vs-AI simulator'`.

## Batch matchup matrix

`tools/ai_matchup_simulator/run.py` accepts a JSON list of sets, generates every
unordered pair, and runs each pair repeatedly. Repetitions alternate which set
occupies the engine's player side and use independently derived deterministic
RNG states. Results are normalized back to set identity.

All autonomous simulation tests use the `ZenmodemanSim:` name prefix. This
keeps long-running simulation cases separate from ordinary `Zenmodeman:`
regression tests and gives `make check` a dedicated simulation filter.

Start with the included four-set example:

```sh
python3 tools/ai_matchup_simulator/run.py \
    tools/ai_matchup_simulator/example_sets.json \
    --repeats 4
```

The default output directory is `build/ai-matchups` and contains:

- `trials.csv`: every battle's sides, winner, outcome code, and turn count;
- `matchups.csv`: head-to-head wins, draws, win rates, and average turns;
- `rankings.csv`: overall wins, losses, draws, win rate, score rate, and rank;
- `report.md`: readable ranking and matchup tables;
- `runner.log`: the underlying battle-test runner output.

Reported turn counts are one-based: a battle decided during the opening turn
is recorded as one turn even though the engine's internal counter starts at
zero.

Ranking score rate treats a win as one point and a draw as half a point. Use
`--seed` to select a reproducible seed family and `--output` to change the
report directory. `--generate-only` writes the generated C scenarios without
building or running them, which is useful for inspection. While running, the
program first reports that it is building the test runner, then displays
completed and total battles, percentage, elapsed time, estimated time
remaining, and battles per second. In redirected/non-interactive output it
prints progress at roughly five-percent intervals. Pass `--verbose` to stream
all underlying compiler and test-runner output in addition to the progress.

The JSON accepts short names such as `"BRELOOM"` or full C constants such as
`"SPECIES_BRELOOM"`. Each entry requires `name`, `species`, and one to four
`moves`. Optional fields are `level`, `nature`, `ability`, `item`, `tera_type`,
`friendship`, explicit battle stats, HP, maximum HP, and an `evs` object. IVs
are always assumed to be 31 in all six stats. EV keys are `hp`, `attack`,
`defense`, `sp_attack`, `sp_defense`, and `speed`; omitted EVs default to zero.
For example:

```json
"evs": {"attack": 252, "sp_defense": 4, "speed": 252}
```

See `tools/ai_matchup_simulator/example_sets.json` for a complete starting
point.

## Information policy

`AI_FLAG_SMART_TRAINER` is intentionally used without `AI_FLAG_OMNISCIENT`.
Each side therefore follows the project's Smart AI knowledge policy: revealed
information, configured inference, and prediction are used rather than direct
access to the opponent's complete hidden moveset. Both sides do know held
items, matching current Smart AI behavior. Because a 1v1 has no reserve, switch
selection does not affect these initial scenarios.
