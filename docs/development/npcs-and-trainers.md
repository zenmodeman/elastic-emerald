# NPC and trainer development notes

An encounter spans more than its dialogue: the map object, script entry point, trainer ID and party, prerequisites, mode gates, reward state, rematches, and runtime helpers all contribute to its behavior. I prefer reusing suitable infrastructure and unused slots when that avoids expanding fixed tables or save structures.

## Maps and scripts

Map objects belong to `map.json`; `events.inc` is generated. Placement depends on neighboring objects, elevation, collision data, and map connections. Named local IDs enter a global header, so I use map-specific names when a script needs to address an object. Objects without that requirement can omit a named ID.

The map generator invocation is:

```sh
tools/mapjson/mapjson map emerald <map.json> data/layouts/layouts.json <map-directory>
```

For native scripting I use `scripts.pory`, with `scripts.inc` as its output. A map with only legacy assembly can retain unaffected content in a `raw` block or raw include while new logic lives in Poryscript. Each script and text label still has one definition. An assembler `.if 0` does not hide malformed strings from the earlier character-preprocessing step, which is why obsolete text can still break generation.

Argument-bearing commands in function-style blocks use calls: `setflag(FLAG_NAME)`, `giveItem(ITEM_NAME)`, and `trainerbattle_no_intro(TRAINER_ID, DefeatText)`. My source/output comparison uses the same configuration as the Makefile, with a temporary output when reviewing:

```sh
tools/poryscript/poryscript -i <scripts.pory> -o <output> -fc tools/poryscript/font_config.json -cc tools/poryscript/command_config.json
```

## Trainer identity and route bosses

Trainer identity connects `include/constants/opponents.h`, rematch tables, Match Call data, and `src/data/trainers.party`. Reusing a rematch slot also changes the old trainer's rematch mapping; otherwise the old encounter can resolve to the new party. I retain the numeric value when renaming a reused constant. `src/data/trainers.h` is generated from the party source through `make generated`.

A route boss with prerequisites, consent, or rewards uses `TRAINER_TYPE_NONE` so its script controls entry into battle. `IsRouteBossTrainer` supplies the full pre-battle heal. Prerequisites include the actual defeat flags for the relevant trainers, including connected interiors; shared double-trainer IDs represent a single check.

My route-boss scripts distinguish not-ready, decline, restricted, defeated, and reward outcomes. The defeated branch precedes time-limited gates so the boss remains conversational afterward. A Restricted-only cutoff combines `FLAG_RESTRICTED_MODE` with its progression flag, leaving other modes unaffected. Battle consent follows the prerequisite checks.

## Party design

I use intro, defeat, and post-battle dialogue as design material. Characterization, occupation, location, visual jokes, and stated interests can justify a choice that trainer class alone would miss.

For otherwise suitable candidates, my preference is an unused species, then an unused ability on a used species, then a repeated species/ability pairing when theme or battle design earns it. I also look at the combined type profile of a location: different species can still produce repetitive battles. Water types on a beach fit the setting, while secondary typings and optional party slots offer variety.

Status-move coverage is another source of variety, within legality, expected level, and early-game difficulty. Format, rematches, progression, team size, and nearby parties all affect the final choice. The diversity report is refreshed with:

```sh
python3 tools/elastic_emerald_helpers/analyze_trainer_types.py
```

## Scaling and rewards

Runtime level scaling lives in `GetTrainerLevelModifier(trainerNum)` and is applied when trainer Pokémon are created, capped at `MAX_LEVEL`. This avoids duplicate parties solely for level changes. Base/rematch IDs and route-boss membership determine the affected group; independent progression flags can contribute cumulative bonuses. I record those triggers and totals in `docs/gameplay/trainers.md`.

For a one-shot boss reward, the defeated flag usually represents all the persistent state needed. I use separate reward state only for designs with retries, independent collection, or another distinction the defeat flag cannot express. A one-shot reward follows the successful battle.

Scripted `additem`/`giveItem` uses `AddBagItemOrPC`: the Bag is tried first, then normal PC storage where applicable. Important items and Battle Pyramid inventory remain outside that fallback. `VAR_RESULT` reports whether a destination accepted the full quantity. The item message reflects a PC delivery; when both destinations are full and no retry exists, the NPC dialogue explains the failure. Abandoned custom flags return to their `FLAG_UNUSED_*` definitions once no live references remain.

## Documentation and review

My trainer notes cover prerequisites, mode cutoffs, rewards, scaling, reused slots, and healing. Parties inside `trainer-party` markers are synchronized by:

```sh
python3 tools/elastic_emerald_helpers/sync_trainer_docs.py
python3 tools/elastic_emerald_helpers/sync_trainer_docs.py --check
```

Source generation is separate from a ROM or test build. Static review covers IDs, flags, labels, rematch references, generated-output consistency, and whitespace. Changes that also affect battle decisions connect to the [battle AI notes](battle-ai.md).
