---
name: modify-elastic-emerald-npcs
description: Add, change, diagnose, review, suggest, or document Elastic Emerald overworld NPCs, ordinary trainers, optional encounters, and route bosses. Use for NPC dialogue-informed team design, map object placement, NPC or trainer scripts, Poryscript conversion, trainer-party or trainer-slot changes, route-boss prerequisites and rewards, Restricted/Resource/progression gates, runtime trainer-level scaling, pre-battle healing, item-gift storage behavior, and related trainer documentation.
---

Read `AGENTS.md` for repository conventions. Maintain this skill’s technical guidance when changes affect it.


# Modify Elastic Emerald NPCs

## Core workflow

1. Read the repository `AGENTS.md`, inspect `git status`, and preserve unrelated changes.
2. Trace the complete feature: map object, script entry point, trainer ID and party, prerequisite flags, reward state, mode gates, rematches, runtime helpers, and documentation.
3. Prefer existing infrastructure and unused slots over expanding fixed tables or save structures.
4. Edit source files, regenerate derived files, and use static checks only unless the user explicitly requests a build.

## Map objects and local IDs

- Add or move overworld objects in the map's `map.json`; do not hand-edit generated `events.inc`.
- Choose coordinates by inspecting nearby objects, elevations, collision/layout data, and map connections. Confirm that the new object does not block progression or overlap another event.
- Regenerate the map output with `tools/mapjson/mapjson map emerald <map.json> data/layouts/layouts.json <map-directory>` when needed. Generated map includes may be ignored by Git but still need regeneration for local verification.
- Use a map-specific local-id name when persistent object manipulation requires one. Avoid generic global local-id symbols that can collide. Omit a named local ID when the script does not need to address the object.
- Use `TRAINER_TYPE_NONE` for a route boss that must run prerequisite, mode, consent, or reward logic before starting its battle.

## Poryscript source ownership

- If new NPC logic is added to a map that has `scripts.pory`, edit the `.pory` source and regenerate `scripts.inc`.
- If the map has only `scripts.inc`, create `scripts.pory` rather than growing new hand-written assembly logic. Keep unaffected legacy assembly in a `raw` block or a clearly named raw include, and implement the new NPC logic in native Poryscript.
- Ensure only one definition exists for every migrated script and text label. Remove obsolete legacy logic instead of hiding it behind assembler `.if 0`: the character preprocessor reads string contents before the assembler evaluates conditionals, so malformed escapes or unsupported characters inside a disabled block can still fail the build.
- In function-style Poryscript, write argument-bearing commands as calls, such as `setflag(FLAG_NAME)`, `giveItem(ITEM_NAME)`, and `trainerbattle_no_intro(TRAINER_ID, DefeatText)`.
- Compile both the checked-in output and a `/tmp` output with:

  `tools/poryscript/poryscript -i <scripts.pory> -o <output> -fc tools/poryscript/font_config.json -cc tools/poryscript/command_config.json`

  Compare the generated files to confirm source/output consistency.

## Trainers and route bosses

- Before adding a trainer ID, inspect `include/constants/opponents.h`, rematch tables, Match Call data, and `src/data/trainers.party`. Reuse an explicitly unneeded trainer slot when the fixed trainer count should not grow.
- When repurposing a rematch slot, update the old trainer's rematch table so it no longer resolves to the reused ID. Give the reused constant a descriptive name when practical, while preserving its numeric value.
- Define parties in `src/data/trainers.party` and regenerate `src/data/trainers.h` using the current Makefile's targeted trainerproc generation rule. Treat `trainers.h` as generated.
- For route bosses, add the trainer to `IsRouteBossTrainer` when the intended treatment includes the full pre-battle heal.
- Gate the battle using the actual defeat flags for every required trainer, including trainers in connected interiors. Shared double-trainer IDs should be checked once.
- Check the boss's defeated flag before time-limited or Restricted-mode gates so an already-defeated boss remains conversational.
- Use `FLAG_RESTRICTED_MODE` together with the requested progression flag to close a bounded reward encounter. Do not apply that cutoff outside Restricted Mode unless explicitly requested.
- Ask for battle consent after prerequisites pass. Keep decline, not-ready, restricted, defeated, and reward outcomes explicit and terminating.

## Trainer-party suggestions

- Read the trainer's intro, defeat, and post-battle dialogue before suggesting Pokémon. Treat characterization, occupation, location, visual jokes, and stated interests as meaningful selection factors rather than relying only on trainer class.
- Refresh `tools/elastic_emerald_helpers/trainer_set_analysis.md` with `python3 tools/elastic_emerald_helpers/analyze_trainer_types.py` when its source documentation may have changed.
- Prefer diversity in this order: an unused species; a used species with an unused ability for that species; a repeated species-and-ability combination only when theme, progression, battle design, or team cohesion justifies it.
- Use the analysis's species-and-ability counts when comparing otherwise suitable candidates. Do not reject a strong dialogue-driven choice merely because it repeats; explain why the repeat earns its place.
- Favor lesser-covered types when they fit the NPC and encounter. Audit the combined type profile of trainers in the same location so nominal species diversity does not produce repetitive battles or excessive local representation of one type.
- Allow a reasonable density of types inherent to the setting or trainer classes, such as Water on a beach. Reduce avoidable saturation through secondary typings and non-obligatory party slots rather than stripping away the location's identity.
- Inspect status-move usage and unused status moves for additional variety. Prefer candidates that can legally and appropriately use uncovered or less-covered status moves at the intended level, without forcing a poor thematic choice or an oppressive early-game set.
- Account for the trainer's battle format, expected level, nearby parties, rematches, player progression, and team size. Present the thematic and mechanical reason for each suggested Pokémon and call out deliberate repeats.

## Level scaling

- Do not duplicate trainer parties solely for progression-based level changes.
- Centralize runtime scaling in `GetTrainerLevelModifier(trainerNum)` and apply its result when each trainer Pokémon is created. Cap the resulting level at `MAX_LEVEL`.
- Include all applicable base and rematch IDs. Confirm whether the route boss itself belongs to the scaling group.
- Make cumulative progression explicit. Independent achieved flags should contribute independently when later milestones add to earlier bonuses.
- Update `docs/gameplay/trainers.md` with the exact trigger and cumulative modifier.

## Rewards and flags

- Do not allocate a permanent flag solely to remember a route-boss reward when the trainer-defeated flag already makes the battle and reward one-shot.
- Give a one-shot reward immediately after the successful trainer battle. Use an extra reward flag only when the design explicitly requires later retry, independent collection, or a reward state that cannot be derived from existing progression.
- Scripted `additem`/`giveItem` uses the project-wide Bag-then-PC fallback through `AddBagItemOrPC`. Important items and Battle Pyramid inventory must not be diverted into normal PC item storage.
- Preserve `VAR_RESULT`: success means either Bag or PC accepted the full quantity; failure means neither applicable destination could accept it.
- Keep standard obtain-item messaging accurate when fallback sends the item to the PC. If both destinations are full and no retry state exists, explain the failure in the NPC script.
- Reclaim an abandoned custom flag by restoring its `FLAG_UNUSED_*` definition and confirm no live references remain with `rg`.

## Documentation and verification

- Add or update the trainer section in `docs/gameplay/trainers.md`, including prerequisites, mode cutoff, reward, level scaling, reused-slot caveats, and route-boss healing.
- Wrap documented parties in `trainer-party` markers and run `python3 tools/elastic_emerald_helpers/sync_trainer_docs.py`, followed by `--check`.
- Use targeted source generation where needed; do not invoke broad build targets or ROM/test builds unless requested.
- Use `rg` to audit trainer IDs, flags, script labels, rematch references, and stale reward logic.
- Run `git diff --check` and inspect the complete relevant diff. Distinguish pre-existing whitespace warnings from new ones.
- If the work changes battle-AI behavior rather than only trainer content, also load `skills/modify-elastic-emerald-ai-logic/SKILL.md` and follow its documentation requirements.

## Current implementation and maintenance notes


## Trainer identity and route bosses

A route boss with prerequisites, consent, or rewards uses `TRAINER_TYPE_NONE` so its script controls entry into battle. `IsRouteBossTrainer` supplies the full pre-battle heal. Prerequisites include the actual defeat flags for the relevant trainers.

In Restricted Mode,  Route Bosses often cannot be battled after a certain progression point.

## Party design

`trainerproc` leaves an unspecified Pokemon gender at zero. The shared trainer generator retains the previous defaults: personality low byte `0x88` for a male trainer in singles, `0x78` for a female trainer in singles, and `0x80` for other battle types. Explicit Pokemon genders override these values; partners retain random unspecified genders. Keep this contract when updating the generator API.

When trying to figure out the right Pokemon to use for a trainer, their existing intro, defeat, and post-battle dialogue is helpful. The NPC's location and trainer class also is a big factor.


 The diversity report is refreshed with:
```sh
python3 tools/elastic_emerald_helpers/analyze_trainer_types.py
```

This script is helpful to figure out what types should get more representation that fit the given trainers.  For otherwise suitable candidates, my preference is an unused species, then an unused ability on a used species, then a repeated species/ability pairing when it makes sense for theme or battle design. 


## Scaling and rewards

Runtime level scaling lives in `GetTrainerLevelModifier(trainerNum)` and is applied when trainer Pokémon are created, capped at `MAX_LEVEL`. This avoids duplicate parties solely for level changes. Base/rematch IDs and route-boss membership determine the affected group; independent progression flags can  cumulative bonuses. I record those triggers ancontributed totals in `docs/gameplay/trainers.md`.


## Documentation and review

My trainer notes cover prerequisites, mode cutoffs, rewards, scaling, reused slots, and healing. Parties inside `trainer-party` markers are synchronized by:

```sh
python3 tools/elastic_emerald_helpers/sync_trainer_docs.py
python3 tools/elastic_emerald_helpers/sync_trainer_docs.py --check
```

