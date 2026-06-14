# Elastic Emerald Custom Functionality Dossier

This README summarizes the core project-specific functionality authored by commit user `zenmodeman`. It is intended as a regression-audit companion for the `merge-upgrade-helper` skill during upstream `pokeemerald-expansion` merges.

The inventory was built from local `git log --author=zenmodeman`, current symbol scans, and current implementation anchors. Treat it as a functional map, not a complete design spec.

## How To Use This During A Merge

Before deciding a conflict in any touched area, check whether the file participates in one of the systems below. For each system that appears in a conflict or adjacent code:

1. Preserve the full runtime path, not just constants or data declarations.
2. Verify data, public prototypes, save flags/vars, scripts, UI, AI mirrors, and tests still agree.
3. Prefer current upstream APIs where signatures changed, but keep Elastic Emerald behavior unless upstream now implements the same behavior.
4. Use static checks and targeted scans first. Do not run a full build unless the user explicitly asks.

High-risk files that repeatedly contain local behavior:

- `src/pokemon.c`
- `include/pokemon.h`
- `src/battle_terastal.c`
- `src/battle_ai_main.c`
- `src/battle_ai_util.c`
- `include/battle_ai_util.h`
- `src/battle_ai_switch_items.c`
- `src/battle_util.c`
- `src/battle_script_commands.c`
- `data/battle_scripts_1.s`
- `src/wild_encounter.c`
- `src/pokemon_storage_system.c`
- `src/evolution_scene.c`
- `src/script_pokemon_util.c`
- `src/party_menu.c`
- `src/pokemon_summary_screen.c`
- `src/data/moves_info.h`
- `src/data/pokemon/center_tutor_moves.h`
- `src/data/pokemon/teachable_learnsets.h`
- `src/data/pokemon/level_up_learnsets/gen_9.h`
- `src/data/trainers.party`
- `src/data/trainers.h`
- `src/data/wild_encounters.json`
- `data/maps/*/scripts.pory`

## Run Mode And Progression Framework

Elastic Emerald adds early-game mode selection in the truck and threads those choices through encounters, gifts, marts, tutors, Tera, item availability, and party legality.

Primary anchors:

- `data/maps/InsideOfTruck/scripts.pory`: asks about Restricted Mode, Resource Mode, curated Tera, monotype, and tier points.
- `include/constants/flags.h`: `FLAG_RESTRICTED_MODE`, `FLAG_RESOURCE_MODE`, `FLAG_TERA_CHARGED`, `FLAG_CURATED_TERA`, `FLAG_TIERED`.
- `include/constants/vars.h`: mode-selection vars may be touched by map scripts.
- `src/pokemon.c`: `GetMonoType`, curated/random Tera assignment, resource checks, tier point helpers.
- `src/battle_terastal.c`: monotype and Restricted Mode Tera legality.
- `data/maps/*/scripts.pory`: mode-specific gifts, shops, dialogue, and progression gates.

Audit checks:

- Truck choices must still set the expected flags before downstream scripts query them.
- Monotype and Tiered mode are intentionally mutually exclusive in the startup flow.
- Generated `.inc` script files should match `.pory` source policy for the current repo state; do not preserve stale generated script conflicts if the generator source is authoritative.
- Mode-specific script behavior is often in map files that do not conflict directly with battle code, so scan scripts when a merge changes flags, vars, specials, party helpers, or item-give commands.

## Monotype System

Monotype runs filter and rebalance wild encounters, gifts, split evolutions, some battles, and Tera eligibility around a chosen type.

Primary anchors:

- `src/pokemon.c`: `GetMonoType`.
- `src/wild_encounter.c`: `IsMonMonotypeException`, `TryGetMonotypeWildMonIndex`, land/shaking/fishing filters, gender fixes for split-evolution lines.
- `src/evolution_scene.c`: Shedinja and other evolution exceptions.
- `src/battle_terastal.c`: Tera is allowed only if it preserves the monotype or is Stellar.
- `data/maps/InsideOfTruck/scripts.pory`: monotype choice and explanation.
- `src/data/wild_encounters.json`: type-compatible encounter planning.
- Map scripts and trainer data: monotype-specific gifts, dialogue, and balance adjustments.

Audit checks:

- Wild encounter filtering must fall back to a valid compatible slot rather than allowing incompatible species in monotype mode.
- Exceptions such as Snorunt/Ghost, Ralts/Fighting, Burmy exclusive-evolution types, Shedinja/Ghost, and split-evolution gender forcing must survive refactors.
- Tera legality must continue to consider both the chosen monotype and Restricted Mode bans.
- Search for `GetMonoType()` after merges. If only data references remain, runtime hooks likely dropped.

## Tier Points System

Tier Points is a party-budget mode that assigns point values to Pokemon, constrains catches, gifts, evolutions, PC movement, ability changes, and tutor access, and displays points in UI.

Primary anchors:

- `include/pokemon.h`: `GetMonTierPoints`, `CountPartyTierPoints`, `CalcTierPointsAfterEvolution`, `CalcTierPointsAfterAbilityChange`, `CanMonUseCenterTutorWithCurrentResources`.
- `src/pokemon.c`: species/ability-aware tier point calculations, party total, Center Tutor exceptions, curated Tera dependencies.
- `src/battle_script_commands.c`: catch flow guard/auto-box behavior.
- `src/script_pokemon_util.c`: gift Pokemon tier checks and automatic boxing.
- `src/evolution_scene.c`: evolution and Shedinja tier checks.
- `src/pokemon_storage_system.c`: party/PC shift and withdraw guards using `gExcessTierPoints`.
- `src/party_menu.c`: ability patch/capsule and evolution item guards.
- `src/pokemon_summary_screen.c`: tier point display.
- `src/strings.c`, `include/strings.h`, `src/battle_message.c`: player-facing error and auto-box messages.

Audit checks:

- A catch, gift, or evolution that exceeds the cap should not vanish; it should be boxed or blocked according to the pathway.
- Moving Pokemon from PC to party and moving into empty slots must recompute total party points and report excess points.
- Ability changes must recalculate tier value using the proposed ability, not the current ability.
- One-tier-point Center Tutor exceptions should remain free where intended, including species/evolution-chain checks.
- Summary screen points are diagnostic for players and should survive UI layout refactors.

## Restricted And Resource Modes

Restricted Mode and Resource Mode impose balance and scarcity constraints across items, moves, gifts, tutors, evo items, release rules, and Tera.

Primary anchors:

- `include/constants/flags.h`: `FLAG_RESTRICTED_MODE`, `FLAG_RESOURCE_MODE`.
- `src/pokemon.c`: Restricted evolution item checks, restricted move/tutor logic, `CanMonUseCenterTutorWithCurrentResources`.
- `src/party_menu.c`: item use and ability-change restrictions.
- `src/pokemon_storage_system.c`: restricted release move ownership checks.
- `src/data/items.h`, `src/data/pokemon/item_effects.h`, `include/constants/item_effects.h`: EV acquisition items and prices.
- `data/maps/*/scripts.pory`: marts, gifts, tutors, and progression requirements that change under modes.
- `src/battle_terastal.c`: Restricted Mode Tera bans based on tier threshold.

Audit checks:

- Do not reduce Restricted Mode to only script gates; party menu, evolution, release, and Tera checks are also enforcement points.
- If a merge changes item-use, tutor, or evolution APIs, re-thread Restricted Mode checks through the new helper path.
- Restricted release logic should prevent releasing the sole owner of certain required moves.
- Resource Mode shop/gift/tutor scripts should be audited when command names or item constants change.

## Curated And Random Tera

Elastic Emerald supports curated species-specific Tera choices, random Tera fallback, monotype-compatible Tera handling, and Restricted Mode Tera bans.

Primary anchors:

- `src/pokemon.c`: `getCuratedOrRandomTeraType`, `GetTeraTypeFromPersonality`, `MON_DATA_TERA_TYPE` handling.
- `include/pokemon.h`: `teraType` substruct field, `forceTeraType`, Tera prototypes.
- `src/battle_terastal.c`: `IsRestrictedModeTeraBanned`, `CanTerastallize`, `GetBattlerTeraType`.
- `src/script_pokemon_util.c`: script `givemon` Tera parameter handling.
- `src/data/trainers.party`: trainer Tera types and intended Terastallization.
- `data/maps/RustboroCity_PokemonSchool/scripts.pory`: early Tera teaching sequence.

Audit checks:

- `TYPE_NONE` and invalid scripted Tera values should fall back safely.
- Forced species Tera types must override personality-derived types.
- Monotype runs may bypass curated assignment only when the random type is compatible or Stellar.
- Restricted Mode bans should remain tied to tier points unless deliberately redesigned.
- AI-side Tera decisions should mirror player legality and not assume the player side can always Tera.

## Center Tutor And Tech Tutor Systems

The project extends tutor flows beyond upstream defaults, including a Tech House tutor, Center Tutor resource logic, point exceptions, and compatibility adjustments.

Primary anchors:

- `data/scripts/pkmn_center_tutor.pory`
- `data/maps/OldaleTown_TechHouse/scripts.pory`
- `src/move_center_tutor.c`
- `src/pokemon.c`: tutor compatibility/resource checks.
- `src/party_menu.c`: "not ready" messaging when tutor/evolution conditions fail.
- `src/data/pokemon/center_tutor_moves.h`
- `src/data/pokemon/teachable_learnsets.h`
- `include/center_move_tutor.h`

Audit checks:

- Already-learned moves should not count against available Center Tutor move counts.
- Tech Tutor slot ordering and temp vars have broken before; inspect script var ordering after conflicts.
- One-tier-point tutor exceptions should remain aligned with Tier Points calculations.
- Compatibility changes often live in both generated learnset helper JSON and C headers.

## Custom Battle Moves And Effects

Elastic Emerald adds or rewrites several move effects and move-data behaviors. These often require synchronized battle scripts, C commands, move flags/effects, messages, AI viability, and tests.

Primary anchors:

- `data/battle_scripts_1.s`
- `asm/macros/battle_script.inc`
- `include/constants/battle_move_effects.h`
- `include/constants/battle_script_commands.h`
- `include/constants/battle_string_ids.h`
- `include/battle_scripts.h`
- `include/battle_util.h`
- `src/battle_script_commands.c`
- `src/battle_util.c`
- `src/battle_message.c`
- `src/data/battle_move_effects.h`
- `src/data/moves_info.h`
- `src/battle_ai_main.c`
- `src/battle_ai_util.c`
- `test/battle/move_effect/*`

Known custom or materially modified behaviors:

- `Drain Douse`: status-like absorb injection through move-end absorb handling, Liquid Ooze inversion, infinite-loop guard.
- `Metal Rush`: custom move with weight/metal interactions and speed-boost planning.
- `Echoed Voice`: more accurate consecutive-use behavior tracked through battle structs and AI damage prediction.
- `Refresh`: heals all status conditions and is not blocked by those statuses.
- `Aqua Ring` and Water Veil interaction: modified bonus effect cleanup and AI valuation.
- `Stockpile` / `Swallow`: Gluttony synergy, efficient healing, stat-wearoff handling.
- Binding/wrapping moves: AI best-damage logic includes residual damage with Magic Guard and tempo exceptions.
- `Snore` and `Bounce`: species-specific modifications.
- `Lucky Chant`: turn adjustment when moving last and priority removal.
- `Razor Wind`: skips recharge under Tailwind.
- `Life Dew`: single-target/singles healing adjustment.
- `Mud Sport` / `Water Sport`: status protection additions, including paralysis/burn prevention.
- Foresight, Odor Sleuth, and Laser Focus: accuracy-related boost.
- Electro Ball, Punishment, Heavy Metal, Light Metal, Pinch Berry healing, Present, Assurance, and burn reduction exceptions have local balance tweaks.

Audit checks:

- For every custom move effect, verify: move constant, effect enum, battle script label, command implementation, message string, move data, AI scoring, and test references.
- Drain Douse is especially sensitive to move-end refactors; verify both runtime healing and AI/test expectations.
- Binding logic should not blindly add residual damage when Magic Guard, low action count, or tempo loss makes it wrong.
- If upstream changes battle script command parameter conventions, audit every custom `try*`, `do*`, and move-end command added locally.

## Custom Abilities And Ability Buffs

Several abilities are new, renamed, or materially rebalanced. These are high-risk in upstream merges because ability behavior may be split between utility checks, battle scripts, switch-in triggers, AI mirrors, and data descriptions.

Primary anchors:

- `include/constants/abilities.h`
- `src/data/abilities.h`
- `src/data/pokemon/species_info/*`
- `src/battle_util.c`
- `src/battle_script_commands.c`
- `data/battle_scripts_1.s`
- `src/battle_ai_util.c`
- `test/battle/ability/*`

Known custom or materially modified abilities:

- `Honey Gather`: reworked Honey behavior, battle-script hooks, item interaction, and regression tests.
- `Anticipation`: damage reduction buff on initial switch-in against super-effective or quad-effective threats.
- `Astral Charge`: Sp. Atk boost when hit by Fairy or Psychic attacks.
- `Dedicated`: custom ability.
- `Merry`: Delibird-focused custom ability with activation script.
- `Covered`: Shield Dust clone.
- `Solar Core`: custom ability.
- `Illuminate`: illuminating move category revisions.
- `Cute Charm`: rework plus trainer integration.
- `Damp`: healing on switch-in against Rain or Water Sport, after-resolution trigger, AI awareness.
- `Limber`: buffed to be immune to speed reductions.
- `Suction Cups`: starting item/fishing logic and extra switch-prevention behavior.
- `Frisk`: skips accuracy checks for item-oriented moves.
- `Big Pecks`: prevents crits / Chip Away from bypassing Reflect/Aurora Veil and positive Defense stages.
- `Truant`: Slack Off extra healing and switch/AI logic.
- `Inner Focus`: prevents Focus Punch from losing focus.
- `Water Veil` / Aqua Ring synergy and burn-damage-reduction exception abilities.

Audit checks:

- Ability data alone is not enough. Check switch-in triggers, damage modifiers, status blockers, message scripts, and AI helpers.
- AI helpers should model the same ability conditions as runtime helpers.
- Renames such as Covered can regress if upstream ability arrays are regenerated or sorted.
- Custom tests with `Zenmodeman:` in names are good targeted regression candidates, but still avoid full builds unless requested.

## Battle AI And Switching

Elastic Emerald heavily customizes trainer AI, especially damage comparison, switch prediction, smarter switch-ins, Tera decisions, doubles targeting, and trainer flag composition.

Primary anchors:

- `include/constants/battle_ai.h`: local flag combinations such as `AI_FLAG_SMART_TRAINER`, prediction, assumptions, smart Tera, and smart mon choices.
- `include/config/ai.h`
- `include/battle_ai_util.h`
- `src/battle_ai_main.c`
- `src/battle_ai_util.c`
- `src/battle_ai_switch_items.c`
- `src/data/trainers.party`
- `test/battle/ai/*`

Known AI systems:

- Best-damaging-move logic includes Hidden STAB, binding residual, damage gaps, wrapping exceptions, and OHKO exclusions.
- Smart switching integrates hazards, weather, status, recurring healing/damage, priority, 1v1 viability, ace rules, Baton Pass, Truant, Wonder Guard, trapper, choice lock, and ability-benefit switches.
- Switch prediction mirrors player-side `ShouldSwitch` and can score against predicted incoming Pokemon.
- Smart Tera chooses Tera for KO, survival, and priority contexts.
- Move prediction and move history logic help with Soak, Aqua Ring, and target expectations.
- Simulated stat changes support Coaching and similar doubles decisions, with apply/reverse guards.
- Doubles targeting prefers damage-optimized targets and self-benefitting effects where appropriate.
- Special cases include Rock Tomb doubles logic, Sweet Scent double-battle logic, Focus Punch on predicted switches, Recovery/Rest/Reflect/Light Screen scoring, Paralysis/Leech Seed scoring, Sport/Damp Healing awareness, and immunity abuse.

Audit checks:

- Search for `AI_FLAG_SMART_TRAINER`, `AI_FLAG_PREDICT_SWITCH`, `AI_FLAG_SMART_TERA`, `GetMostSuitableMonToSwitchInto`, `ShouldSwitch`, `AI_CalcDamage`, and `ApplySimulatedStatChanges`.
- Be suspicious of boolean rewrites in AI helper arguments, especially battler indexes and side indexes.
- Any runtime battle mechanic change should have an AI mirror if the AI scores or predicts it.
- `src/battle_ai_switch_items.c`, `src/battle_ai_util.c`, and `src/battle_util.c` often need coordinated updates.
- Existing dirty worktree edits in these files may be user changes; inspect before editing.

## Encounter, Map, And Story Content

The fork contains substantial playable-content changes: new/altered maps, early-game routes, trainer sets, gifts, marts, monotype encounter plans, Rustboro/Dewford/Granite Cave content, and demo/progression guards.

Primary anchors:

- `data/maps/*/map.json`
- `data/layouts/*/map.bin`
- `data/maps/*/scripts.pory`
- `data/maps/*/scripts.inc`
- `data/event_scripts.s`
- `data/maps/map_groups.json`
- `include/constants/map_groups.h`
- `include/constants/layouts.h`
- `include/constants/flags.h`
- `include/constants/opponents.h`
- `src/data/trainers.party`
- `src/data/trainers.h`
- `src/data/wild_encounters.json`
- `src/battle_setup.c`

Known content areas:

- Petalburg Grove, Oldale Ruins, Sandfront, Rustboro Grass, Dewford Garden, Brawly Gym script/content, Granite Cave trainers/encounters, Steven's Room/Tera Orb, Trainer School event, Tech House, early Route 101/102/104/115/116 changes.
- Rival, Cindy rematches, Collector Darren, Aurelio, Brawly, Roxanne, Dewford/Granite Cave trainers, and multiple early-game trainer AI/set revisions.
- Demo guards, progression requirements, White Herb florist progression, Rustboro trade monotype guard, Bottle Cap/Hyper Training NPCs, Oldale/Rustboro/Petalburg mart changes.

Audit checks:

- Map scripts and trainer party data are often regenerated or adjacent to upstream updates; avoid losing local script branches when resolving broad generated-file conflicts.
- If trainer constants or party formats change upstream, inspect both `trainers.party` and generated `trainers.h`.
- Content systems are coupled to mode flags; a script conflict can break Tiered, Restricted, Resource, Monotype, or Tera progression without touching C.

## Overworld And Quality Of Life

Elastic Emerald includes several non-battle utility systems and QOL changes.

Primary anchors:

- `src/field_effect.c`, `data/scripts/field_move_scripts.pory`: MenuFly and designated/custom HM user behavior.
- `src/player_pc.c`, `src/party_menu.c`, `src/item_menu.c`: PC, party, and item menu extensions.
- `src/fake_rtc.c`, `src/clock.c`, `src/overworld.c`, `include/clock.h`: fake RTC and time advancing.
- `src/egg_hatch.c`, `src/daycare.c`: reduced egg steps, candy cap/daycare logic, egg auto-boxing and memo improvements.
- `src/caps.c`, `include/caps.h`, `include/config/caps.h`: level caps, split exp progression, candy cap logic.
- `src/fishing.c`, `include/config/fishing.h`: more lenient fishing and Suction Cups/Sticky Hold logic.
- `src/berry.c`, `data/scripts/berry_tree.pory`: minimum berry yield, resource-mode berry logic.
- `src/pokemon_summary_screen.c`: IV/EV display and tier points.

Known QOL/content systems:

- MenuFly, custom Cut HM users, HM deletion, Party Nickname option, Box Link, Pokedex Plus, no-whiteout battles, AI-vs-AI/player-side backsprite support.
- Fake RTC and in-game time advancement.
- Reduced egg steps, auto-boxing egg hatches, improved hatch memo.
- Split EXP progression scaling and level/candy caps.
- Fishing behavior changes and lead Suction Cups item logic.
- Berry availability and minimum yield changes.

Audit checks:

- These systems often depend on callbacks and menu state; merge conflicts can compile while losing return paths.
- If upstream changes menu tasks, field effects, daycare, or RTC helpers, verify custom callbacks still restore the correct screen/state.

## Data Balance And Learnsets

Many commits tune species data, learnsets, tutor compatibility, TMs/HMs, trainers, wild encounters, items, prices, and curated Tera assignments.

Primary anchors:

- `src/data/pokemon/species_info/*`
- `src/data/pokemon/level_up_learnsets/gen_9.h`
- `src/data/pokemon/center_tutor_moves.h`
- `src/data/pokemon/teachable_learnsets.h`
- `tools/learnset_helpers/porymoves_files/sv.json`
- `src/data/moves_info.h`
- `include/constants/tms_hms.h`
- `src/data/items.h`
- `src/data/pokemon/item_effects.h`
- `include/constants/item_effects.h`
- `src/data/wild_encounters.json`
- `src/data/trainers.party`
- `src/data/trainers.h`

Audit checks:

- Conditional species-stat macros should remain near the family that uses them and should not be replaced by raw values on only one side of a condition.
- EV acquisition item effects and prices were standardized; check item constants, item data, and item effect arrays together.
- Learnset helper JSON and generated learnset headers can diverge after merge conflict resolution.
- Curated Tera comments in `src/pokemon.c` often explain why high-tier species intentionally lack curated Tera.

## Tests And Static Verification Targets

Useful targeted test files when the user asks for tests:

- `test/battle/ability/anticipation.c`
- `test/battle/ability/astral_charge.c`
- `test/battle/ability/honey_gather.c`
- `test/battle/ai/ai.c`
- `test/battle/ai/ai_doubles.c`
- `test/battle/ai/ai_flag_predict_switch.c`
- `test/battle/move_effect/drain_douse.c`
- `test/battle/move_effect/echoed_voice.c`
- `test/battle/move_effect/mud_sport.c`
- `test/battle/move_effect/stockpile.c`
- `test/battle/move_effect/water_sport.c`

Default static checks for this repo:

```sh
git diff --check
rg -n '(<{7}|={7}|>{7})' .
rg -n 'GetMonTierPoints|CountPartyTierPoints|CalcTierPointsAfter|GetMonoType|FLAG_TIERED|FLAG_RESTRICTED_MODE|FLAG_RESOURCE_MODE|FLAG_CURATED_TERA|CanTerastallize|IsRestrictedModeTeraBanned|CanMonUseCenterTutorWithCurrentResources' include src data
rg -n 'Drain Douse|EFFECT_DRAIN_DOUSE|trydamphealing|Honey Gather|Astral Charge|Merry|Covered|Stockpile|Swallow|Echoed Voice|AI_FLAG_SMART_TRAINER|AI_FLAG_PREDICT_SWITCH|AI_FLAG_SMART_TERA|ApplySimulatedStatChanges' include src data test
```

Avoid full build checks unless explicitly requested.
