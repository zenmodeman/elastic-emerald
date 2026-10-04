# Elastic Emerald custom feature reference

This reference describes current custom functionality and new bugfixes at a high level, with source anchors where they help locate the implementation. The [feature history](../feature-history.md) records implementation commits, release chronology, breaking behavior and its repairs, and historical validation. My [upgrade notes](upstream-upgrades.md) describe maintenance procedures.

Update the affected feature here when behavior is added or fixed. Keep commit specifications and audit results in the feature history, and use the topic guides for detailed maintenance procedures. Routine balance edits belong here only when they introduce a mechanic or gate.

## Proactive Color Change

Color Change changes the target's type before target immunity checks, including for status moves. `CanActivateProactiveColorChange` in `src/battle_util.c` supplies the shared eligibility rule; `TryActivateProactiveColorChange` in `src/battle_move_resolution.c` applies it, and AI type prediction uses the same rule. Struggle, already-matching types, and None/Mystery/Stellar types do not trigger it.

## Overwhelm Beam

A Special Normal attack with 120 power, 80% accuracy, and 10 PP. On a successful hit, its secondary effect replaces the target's ability with Insomnia, subject to ability-replacement rules.

## Round turn tracking

Round doubles its power after another Round is used during the same turn, on either side. The tracking resets each turn so an earlier use cannot boost Round on the following turn, including when an earlier battler cannot move.

## Run Mode And Progression Framework

Elastic Emerald adds early-game mode selection in the truck and threads those choices through encounters, gifts, marts, tutors, Tera, item availability, and party legality.

Primary anchors:

- `data/maps/InsideOfTruck/scripts.pory`: asks about Restricted Mode, Resource Mode, curated Tera, monotype, and tier points.
- `include/constants/flags.h`: `FLAG_RESTRICTED_MODE`, `FLAG_RESOURCE_MODE`, `FLAG_TERA_CHARGED`, `FLAG_CURATED_TERA`, `FLAG_TIERED`.
- `include/constants/vars.h`: mode-selection vars may be touched by map scripts.
- `src/elastic_emerald_pokemon.c`: `GetMonoType`, tier-point calculations, tutor-resource eligibility, party totals, and automatic party-to-PC deposits after the 1.15 core rewrite.
- `src/pokemon.c`: curated/random Tera assignment and the upstream Pokémon core.
- `src/battle_terastal.c`: monotype and Restricted Mode Tera legality.
- `data/maps/*/scripts.pory`: mode-specific gifts, shops, dialogue, and progression gates.

Behavior and integration notes:

- Truck choices set the expected flags before downstream scripts query them.
- Monotype and Tiered mode are intentionally mutually exclusive in the startup flow.
- The `.pory` source determines the generated `.inc` script behavior; an old generated conflict can disagree with that source.
- Mode-specific script behavior is often in map files that do not conflict directly with battle code, so I include scripts in reviews of changes to flags, vars, specials, party helpers, and item-give commands.

## Monotype System

Monotype runs filter and rebalance wild encounters, gifts, split evolutions, some battles, and Tera eligibility around a chosen type.

Primary anchors:

- `src/elastic_emerald_pokemon.c`: `GetMonoType`.
- `src/wild_encounter.c`: `IsMonMonotypeException`, `TryGetMonotypeWildMonIndex`, land/shaking/fishing filters, gender fixes for split-evolution lines.
- `src/script_pokemon_util.c`: `PopulateMonotypeResistBerriesInPC`, which seeds PC resist berries during truck setup for monotypes weak to covered attacking types.
- `src/evolution_scene.c`: Shedinja and other evolution exceptions.
- `src/battle_terastal.c`: Tera is allowed only if it preserves the monotype or is Stellar.
- `data/maps/InsideOfTruck/scripts.pory`: monotype choice and explanation.
- `src/data/wild_encounters.json`: type-compatible encounter planning.
- Map scripts and trainer data: monotype-specific gifts, dialogue, and balance adjustments.

Behavior and integration notes:

- Wild encounter filtering falls back to a valid compatible slot rather than allowing incompatible species in monotype mode.
- The exception cases include Snorunt/Ghost, Ralts/Fighting, Burmy exclusive-evolution types, Shedinja/Ghost, and split-evolution gender forcing.
- `CreateWildMon` forces female Snorunt for Ghost teams, male Ralts/Kirlia for Fighting teams, male Burmy for Flying teams, and female Burmy for Grass, Ground, or Steel teams so a compatible split evolution remains available.
- Truck setup adds 12 copies of each applicable resist berry to PC storage for attack types that are super-effective against the selected monotype.
- Tera legality considers both the chosen monotype and Restricted Mode bans.
- I follow `GetMonoType()` callers during upgrades; data references without runtime callers can indicate a lost hook.

## Tier Points System

Tier Points is a party-budget mode that assigns point values to Pokemon, constrains catches, gifts, evolutions, PC movement, ability changes, and tutor access, and displays points in UI.

Primary anchors:

- `include/pokemon.h`: `GetMonTierPoints`, `CountPartyTierPoints`, `GetPartyTierPointExcessWithMon`, `CalcTierPointsAfterEvolution`, `CalcTierPointsAfterAbilityChange`, `CanMonUseCenterTutorWithCurrentResources`.
- `src/elastic_emerald_pokemon.c`: species/ability-aware tier point calculations, party total, Center Tutor exceptions, and auto-box support.
- `src/pokemon.c`: Pokémon creation/data paths and curated Tera dependencies.
- `src/battle_script_commands.c`: catch flow guard/auto-box behavior.
- `src/script_pokemon_util.c`: gift Pokemon tier checks and automatic boxing.
- `src/evolution_scene.c`: evolution and Shedinja tier checks.
- `src/pokemon_storage_system.c`: party/PC shift and withdraw guards using `gExcessTierPoints`.
- `src/party_menu.c`: ability patch/capsule and evolution item guards.
- `src/pokemon_summary_screen.c`: tier point display.
- `src/strings.c`, `include/strings.h`, `src/battle_message.c`: player-facing error and auto-box messages.

Behavior and integration notes:

- An over-cap catch, gift, or evolution is boxed or blocked according to the pathway, rather than lost.
- A newly hatched Pokémon is counted only after its Egg flag is cleared. If that makes the current Tiered party exceed the cap, the hatch flow warns the player and deposits the hatchling after the nickname decision. `GetCurrentPartyTierPointExcess` is the shared, directly tested decision helper; it returns zero while the slot is still an Egg and outside Tiered Mode.
- Before a nickname screen or party insertion, Tiered captures project the caught Pokemon against the existing party without mutation. An over-cap capture sets `gExcessTierPoints`, bypasses the normal full-party swap prompt, and returns through the boxing-capable callback.
- PC-to-party and empty-slot moves recompute total party points and report any excess.
- Ability-change projections calculate Tier Points using the proposed ability.
- Ability Capsule and Ability Patch reject an over-cap proposed ability before confirmation or item consumption; the shared guard is inactive outside Tiered Mode.
- Free Center Tutor eligibility includes species/evolution-chain checks as well as the one-point threshold.
- Summary Screen points expose the party-budget information to the player; I retain that information when adjusting the layout.

## Restricted And Resource Modes

Restricted Mode and Resource Mode impose balance and scarcity constraints across items, moves, gifts, tutors, evo items, release rules, and Tera.

Primary anchors:

- `include/constants/flags.h`: `FLAG_RESTRICTED_MODE`, `FLAG_RESOURCE_MODE`.
- `src/battle_setup.c`, `include/battle_setup.h`, `src/battle_tower.c`: `BattleSetup_EnforceRestrictedModeItemClause` removes duplicate held items from the player's party before trainer battles, sending them to bag, then PC, then discard if no storage remains.
- `src/pokemon.c`: Restricted evolution conditions and move/tutor compatibility.
- `src/elastic_emerald_pokemon.c`: `CanMonUseCenterTutorWithCurrentResources`, free-tutor evolution-chain checks, and Resource Mode tutor/relearner eligibility.
- `src/party_menu.c`: item use and ability-change restrictions.
- `src/pokemon_storage_system.c`: restricted release move ownership checks.
- `src/data/items.h`, `src/data/pokemon/item_effects.h`, `include/constants/item_effects.h`: EV acquisition items and prices.
- `src/battle_util.c`, `src/battle_script_commands.c`, `src/battle_stat_change.c`: Resource Mode held-item consumption/restoration, the wild-consumable transfer guard shared by stealing abilities and moves, and Restricted Mode player stat-boost limits.
- `data/maps/*/scripts.pory`: marts, gifts, tutors, and progression requirements that change under modes.
- `src/battle_terastal.c`: Restricted Mode Tera bans based on tier threshold.

Behavior and integration notes:

- Restricted Mode enforcement spans scripts, party menus, evolution, release, and Tera checks.
- Automatic trainer-battle item-clause enforcement supersedes the old explicit Roxanne/Brawly script gates.
- Restricted Mode checks are coupled to item-use, tutor, and evolution helper paths.
- Item-clause enforcement runs before standard trainer battles, Battle Pyramid/Trainer Hill battles, and Battle Tower trainer battles, through their respective setup callbacks.
- Restricted release logic prevents releasing the sole owner of certain required moves.
- Restricted Mode caps player Defiant and Competitive at two positive stages, including a partial final one-stage raise when necessary; opponents retain the normal two-stage trigger.
- Player Moxie, Chilling Neigh, Grim Neigh, Beast Boost, and Soul Heart may raise their relevant stat from neutral or below, but may not stack another boost once it is already positive. Opponent abilities are unaffected.
- A player's Mirror Herb in Restricted Mode may copy only boosts directly applied to its target by Swagger, Flatter, Spicy Extract, or Decorate. It ignores an opponent's self-setup, while unrestricted and opponent-side Mirror Herbs retain normal behavior.
- I include Resource Mode shop/gift/tutor scripts when reviewing changed command names or item constants.
- Resource Mode spends normally activated consumable held items while treating Knock Off/Fling/theft as temporary removal. The distinction lives in end-of-battle held-item restoration.
- The Resource Mode wild-battle rule prevents consumable held-item transfers from the wild side to the player. Item-only moves such as Trick/Switcheroo and Bestow fail when that transfer would occur; damaging moves such as Thief/Covet still deal damage without stealing. Pickup, Magician, and Pickpocket use the same restriction. Bug Bite/Pluck are intentionally exempt because they consume the berry immediately, and non-consumables such as Poison Barb remain transferable.

## Trainer Battle Preparation And Battle-End Status

Recent Elastic behavior modifies both entry to trainer battles and persistence after any battle.

Primary anchors:

- `src/battle_setup.c`: `TryHealPlayerPartyBeforeTrainerBattle` and `RerollSleepTurnsAfterBattle`.
- `data/scripts/trainer_battle.inc`: invokes the healing special for normal trainer battles and rematches and selects class-specific medicine dialogue.
- `include/constants/trainers.h`: `TRAINER_PRE_BATTLE_HEAL_*` result values.
- `docs/gameplay/trainers.md` and `tools/elastic_emerald_helpers/sync_trainer_docs.py`: source-derived trainer documentation and healing annotations.

Behavioral intent:

- Accomplished, professional, affluent, boss, and facility-leader classes may fully heal the player's party before an ordinary trainer battle; selected status-themed classes instead clear status with class-specific medicine flavor. Route bosses such as Aurelio force a full heal.
- Complete healing wins when a double battle's trainers offer different healing levels. Battle Pyramid and Trainer Hill retain their own healing rules and are excluded.
- With modern sleep turns, sleeping party members have their remaining sleep duration rerolled to two through four turns after wild, scripted wild, first, trainer, and rematch battles. Trainer-battle running remains disabled.

Behavior and integration notes:

- The healing flow depends on script calls before supported trainer/rematch starts as well as the C special and result constants.
- New trainer classes default to no healing until explicitly categorized. Confirm trainer IDs/classes and generated trainer documentation together.
- Battle-end sleep rerolls depend on every supported callback; a missing exit-path call creates inconsistent persistent status behavior.

## Curated And Random Tera

Elastic Emerald supports curated species-specific Tera choices, random Tera fallback, monotype-compatible Tera handling, and Restricted Mode Tera bans.

Primary anchors:

- `src/pokemon.c`: `GetCustomTeraType`, `GetTeraTypeFromPersonality`, Pokémon-creation assignment, and `MON_DATA_TERA_TYPE` handling.
- `include/pokemon.h`: `teraType` substruct field, `forceTeraType`, Tera prototypes.
- `include/config/battle.h`: `B_FLAG_TERA_ORB_CHARGED` and `B_FLAG_TERA_ORB_NO_COST` are intentionally both `FLAG_TERA_CHARGED`.
- `src/battle_terastal.c`: `IsRestrictedModeTeraBanned`, `CanTerastallize`, `GetBattlerTeraType`.
- `src/script_pokemon_util.c`: script `givemon` Tera parameter handling.
- `src/data/trainers.party`: trainer Tera types and intended Terastallization.
- `data/maps/RustboroCity_PokemonSchool/scripts.pory`: early Tera teaching sequence.

Behavior and integration notes:

- `TYPE_NONE` and invalid scripted Tera values use the fallback path.
- Forced species Tera types override personality-derived types.
- Random assignment uses the personality to span every ordinary type, mapping the otherwise-invalid Mystery slot to Stellar. When Monotype Mode's selected type matches that random result (or the result is Stellar), the compatible random result deliberately takes precedence over a curated species entry.
- Current curated examples include Fire Jolteon, Grass Vikavolt, and Normal Alolan Raichu; these are compact sentinels for detecting an older curated table after a merge.
- Monotype runs may bypass curated assignment only when the random type is compatible or Stellar.
- Restricted Mode bans are tied to Tier Points.
- AI-side Tera decisions model player eligibility rather than assuming the player can always Tera.
- Restricted Mode normally bans Terastallization at four or more Tier Points. Lower-power ability combinations remain exempt for Thick Fat Azumarill, non-Huge-Power Diggersby, non-Pure-Power Medicham, non-Sand-Stream Gigalith, non-Speed-Boost Blaziken, and non-Weak-Armor Polteageist. Older exceptions for species later moved into badge-dependent three-point bands were intentionally removed and are historical alongside the corresponding older Tier table.
- Tera Orb charge is intentionally no-cost in Elastic Emerald. The shared `FLAG_TERA_CHARGED` alias for `B_FLAG_TERA_ORB_CHARGED` and `B_FLAG_TERA_ORB_NO_COST` implements that design.

## Center Tutor And Tech Tutor Systems

The project extends tutor flows beyond upstream defaults, including a Tech House tutor, Center Tutor resource logic, point exceptions, and compatibility adjustments.

Primary anchors:

- `data/scripts/pkmn_center_tutor.pory`
- `data/maps/OldaleTown_TechHouse/scripts.pory`
- `src/move_center_tutor.c`
- `src/pokemon.c`: tutor-list and compatibility construction.
- `src/elastic_emerald_pokemon.c`: tutor/relearner resource checks and free-tier exceptions.
- `src/party_menu.c`: "not ready" messaging when tutor/evolution conditions fail.
- `src/data/pokemon/center_tutor_moves.h`
- `src/data/pokemon/teachable_learnsets.h`
- `include/center_move_tutor.h`

Behavior and integration notes:

- Already-learned moves are excluded from available Center Tutor move counts.
- Tech Tutor slot ordering and temporary variables have broken before, making script variable order a recurring review point for me.
- One-tier-point tutor exceptions depend on the Tier Points calculations.
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
- `Big Root`: locally buffed drain recovery to 40%; the runtime multiplier in `GetDrainedBigRootHp` is the important behavior, not just the item data parameter.
- `Metal Rush`: custom move with weight/metal interactions and speed-boost planning.
- `Echoed Voice`: more accurate consecutive-use behavior tracked through battle structs and AI damage prediction.
- `Refresh`: heals all status conditions and is not blocked by those statuses.
- `Aqua Ring` and Water Veil interaction: Water Veil doubles the final Aqua Ring recovery after Big Root adjustment; the same synergy is relevant to AI valuation.
- `Stockpile` / `Swallow`: Gluttony synergy, efficient healing, stat-wearoff handling.
- Binding/wrapping moves: AI best-damage logic includes residual damage with Magic Guard and tempo exceptions.
- `Snore` and `Bounce`: species-specific modifications.
- `Lucky Chant`: turn adjustment when moving last and priority removal.
- `Razor Wind`: skips recharge under Tailwind.
- `Life Dew`: heals one third when the attacker has no present ally, and one quarter for each recipient when a doubles partner is present.
- `Mud Sport` / `Water Sport`: +1 priority and status protection additions, including paralysis/burn prevention.
- Foresight and Odor Sleuth identify the target while raising the user's Accuracy; repeat use remains valid so Accuracy can rise again. Laser Focus likewise raises Accuracy and refreshes successfully when repeated.
- Electro Ball, Punishment, Heavy Metal, Light Metal, Pinch Berry healing, Present, Assurance, and burn reduction exceptions have local balance tweaks.

Behavior and integration notes:

- I trace custom effects through their move constants, effect enums, script labels, command implementations, messages, move data, AI scoring, and tests.
- Drain Douse is especially sensitive to move-end refactors because runtime healing, AI estimates, and test expectations share its contract. `BS_SetDrainDouse` only sets the volatile, so `MOVEEND_ABSORB` also consumes `gBattleMons[gBattlerAttacker].volatiles.drainDouse` and calls `BattleScript_DrainDouseHeal` or `BattleScript__DrainDouseOoze`.
- Magic Guard, low action count, and tempo loss can invalidate a binding move's apparent residual-damage advantage.
- I include custom `try*`, `do*`, and move-end commands in reviews of upstream parameter-convention changes.

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

Behavior and integration notes:

- Ability data depends on switch-in triggers, damage modifiers, status blockers, message scripts, and AI helpers for its actual behavior.
- AI helpers model the same ability conditions as runtime helpers.
- Renames such as Covered can regress if upstream ability arrays are regenerated or sorted.
- The `Elastic-tests:` test prefix identifies custom regression cases for my separately planned test runs.

Flannery's two gym floors deliberately use diagonal fog. Unlike ordinary horizontal overworld fog, diagonal fog does not initialize Misty Terrain when battle begins; this preserves the gym's visual effect without changing its battle rules.

## Battle AI And Switching

Elastic Emerald heavily customizes trainer AI, especially damage comparison, switch prediction, smarter switch-ins, Tera decisions, doubles targeting, and trainer flag composition.

Primary anchors:

- `include/constants/battle_ai.h`: local flag combinations such as `AI_FLAG_SMART_TRAINER`, prediction, assumptions, smart Tera, and smart mon choices.
- `include/config/ai.h`
- `include/battle_ai_util.h`
- `src/battle_ai_main.c`
- `src/battle_ai_util.c`
- `src/battle_ai_switch.c` and `src/battle_ai_items.c`
- `src/data/trainers.party`
- `test/battle/ai/*`

Known AI systems:

- Best-damaging-move logic includes Hidden STAB, binding residual, damage gaps, wrapping exceptions, and OHKO exclusions.
- Player held items are known to the AI at all times; player-side `AI_DecideHoldEffectForTurn` uses the battler's current held item effect, and player party data records held items outside omniscient-only knowledge.
- Resist berries are modeled as consumed over repeated damaging turns: the first hit uses current simulated berry-reduced damage, later hits recalculate without the berry, and non-OHKO same-KO-timing move comparisons can prefer the higher two-turn damage line.
- Smart switching integrates hazards, weather, status, recurring healing/damage, priority, 1v1 viability, ace rules, Baton Pass, Truant, Wonder Guard, trapper, choice lock, and ability-benefit switches.
- Switch prediction mirrors player-side `ShouldSwitch` and can score against predicted incoming Pokemon.
- Immunity-switch prediction is intentionally singles-only and now keys off repeated player switches during the current AI battler's field stint, not the old per-mon repeated-immunity-switch gate. `gAiBattleData->playerSwitchesDuringAiStint` resets when the AI mon switches out, increments for voluntary player hard switches and normal player pivot moves, and excludes forced switch-outs such as phazing or Red Card switch cases.
- `AI_FLAG_PREDICT_INCOMING_MON` immunity prediction only considers a revealed, non-active player party mon after at least five player switches during the current AI stint. Revealed party switch-in history is also accepted as a fallback for switch paths that do not update the dedicated stint counter. The move being predicted around is the highest-scored damaging move chosen by the normal scoring pass in `ChooseMoveOrAction_Singles`, after damaging-move comparison; status moves and unavailable moves do not trigger this path.
- The RNG gate for this prediction is `PREDICT_SWITCH_CHANCE` through `RNG_AI_PREDICT_SWITCH`. The helper-side defensive-switch chance is deliberately 100% so there is not a second independent 50% roll hiding in the immunity candidate path.
- Candidate priority for immunity prediction is: highest existing `switchInCount` among revealed player mons, then higher immunity value, then random tie selection. Ability absorption immunities such as Volt Absorb or Lightning Rod outrank ability blockers, which outrank type immunities such as Ground into Electric.
- Smart Tera chooses Tera for KO, survival, and priority contexts.
- Move prediction and move history logic help with Soak, Aqua Ring, and target expectations.
- Simulated stat changes support Coaching and similar doubles decisions, with apply/reverse guards.
- Doubles targeting prefers damage-optimized targets and self-benefitting effects where appropriate.
- Special cases include Rock Tomb doubles logic, Sweet Scent double-battle logic, Focus Punch on predicted switches, Recovery/Rest/Reflect/Light Screen scoring, Paralysis/Leech Seed scoring, Sport/Damp Healing awareness, and immunity abuse.
- Partner-aware Speed control updates and restores both the simulated target stage and cached Speed while asking whether the partner's guaranteed drop already flips turn order; otherwise stale cached Speed can cause a redundant second Rock Tomb to receive extra score.

Behavior and integration notes:

- My source searches include `AI_FLAG_SMART_TRAINER`, `AI_FLAG_PREDICT_SWITCH`, `AI_FLAG_SMART_TERA`, `GetMostSuitableMonToSwitchInto`, `ShouldSwitch`, `AI_CalcDamage`, and `ApplySimulatedStatChanges`.
- Boolean rewrites in AI helper arguments can silently change battler or side indexes.
- Predicted-switch logic may use `PARTY_SIZE` as a generic switch sentinel. Array access depends on validating `gAiLogicData->mostSuitableMonId[...]` first. An accidental `if (...);` can bypass an intended predicted-switch check.
- Immunity prediction resets `playerSwitchesDuringAiStint` on AI switch-in and increments it for qualifying player switches/pivots, excluding forced switches. Its overlay follows normal move scoring and uses the highest-scored damaging move.
- Regression tests for this behavior live in `test/battle/ai/ai_flag_predict_switch.c` with `Elastic-tests:` names. They exercise the pre-threshold active-target behavior, the five-switch threshold, the `PREDICT_SWITCH_CHANCE` RNG gate, and equally frequent immunity candidates under the merged move-comparison order.
- Runtime changes affect the corresponding AI model wherever the AI scores or predicts that mechanic.
- Resist-berry AI depends on `gAiLogicData->holdEffects` being restored after temporary no-item damage simulation; Unnerve/As One also blocks the berry modifier through `IsUnnerveBlocked`.
- `src/battle_ai_switch.c` and `src/battle_ai_items.c`, `src/battle_ai_util.c`, and `src/battle_util.c` often need coordinated updates.

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
- Route 109's Cassia encounter requires every beach and Seashore House trainer, heals the party through the route-boss classifier, closes after badge 3 only in Restricted Mode, and awards one Power Herb normally, 12 in Resource Mode, or 18 when Resource and Monotype modes are combined. Rival 110 completion raises the complete Route 109 beach trainer group by three levels. Edmond separately awards Water Gems only when his battle actually had two opponents, with quantities of one, three, or six under the same mode progression.
- Pre-battle healing is trainer-driven: route bosses and accomplished/professional classes restore the full party, selected status-oriented classes cure status with class-flavored medicine, ordinary and villainous classes do not heal, and a full healer takes precedence in a two-opponent battle. Facility challenges retain their own healing rules. After every ordinary battle exit, sleeping party members receive a fresh two-to-four-turn sleep counter while other major statuses remain unchanged.
- Triumphs credit player Pokemon that participate when a comparably leveled opposing trainer Pokemon faints. Singles explicitly give presence credit to the eligible player battler without inferring the battle format from populated battler slots; in doubles with multiple eligible battlers, only the direct attacker receives credit. Opponents more than five levels below the player are excluded, counts cap at 30, and already-defeated trainers plus link, recorded, Frontier, Trainer Hill, and e-Reader battles cannot be farmed. The per-battle participation mask resets at battle initialization and after every award attempt.
- First-time Triumph eligibility is snapshotted during battle initialization, before post-battle trainer flags can change. Final battle teardown awards and consumes that snapshot only after battle scripts, controllers, Summary Screen visits, held-item restoration, and form reversion have finished reconciling party data. Current Expansion resolves ordinary damaging-move KOs through `MoveEndFaintBlock`, which marks Triumph participation before `SetValuesOnFaint`; the legacy `tryfaintmon` hook remains necessary for alternate scripted faint paths and accepts both the script's `BS_TARGET` operand and resolved `gBattlerTarget` for doubles attribution.
- Current Expansion represents the former `BATTLE_TYPE_WALLY_TUTORIAL` exclusion with `BATTLE_TYPE_FIRST_BATTLE`; restored Triumph guards use that constant.
- Demo guards, progression requirements, White Herb florist progression, Rustboro trade monotype guard, Bottle Cap/Hyper Training NPCs, Oldale/Rustboro/Petalburg mart changes.
- Dewford Garden's school kid is positioned at `(6, 12)`, has an interaction script, and releases the player after its dialogue. Roost remains the TM40 move and Nature Power the TM10 move; their Fortree/Slateport acquisition scripts and machine lookup are coupled to those TM assignments.
- Petalburg Grove's first-badge scene includes Birch and ambient Bulbasaur, Chikorita, and Vulpix objects. Birch hides after his conversation and is also hidden when Brawly awards the second badge, so delayed visitors cannot encounter stale first-badge dialogue.
- The Trainer School demonstration saves the real player party before its AI-vs-AI rival battle, restores it afterward, and uses trainer-battle mode 14 to return to the script on either outcome instead of whiteout. Mode 14 is distinct from the later early-rival mode 15. The school breeder is a one-shot, monotype-aware egg service: no-monotype runs randomly offer Igglybuff, Toxel, or Smoochum; compatible Normal/Fairy, Electric/Poison, Ice/Psychic, and Flying runs receive Igglybuff, Toxel, Smoochum, and Gligar respectively. The receipt flag is set only after the egg reaches the party or PC.

Behavior and integration notes:

- Map scripts and trainer party data are often regenerated or adjacent to upstream updates; I compare local script branches with the generator inputs during broad conflicts.
- Trainer-constant and party-format changes span `trainers.party` and generated `trainers.h`.
- Content systems are coupled to mode flags; a script conflict can break Tiered, Restricted, Resource, Monotype, or Tera progression without touching C.

## Overworld And Quality Of Life

Elastic Emerald includes several non-battle utility systems and QOL changes.

Primary anchors:

- `src/field_effect.c`, `data/scripts/field_move_scripts.pory`: MenuFly and designated/custom HM user behavior.
- `src/player_pc.c`, `src/party_menu.c`, `src/item_menu.c`: PC, party, and item menu extensions.
- `src/fake_rtc.c`, `src/clock.c`, `src/overworld.c`, `include/clock.h`: fake RTC and time advancing.
- `src/egg_hatch.c`, `src/daycare.c`: reduced egg steps, candy cap/daycare logic, egg auto-boxing and memo improvements.
- `src/caps.c`, `include/caps.h`, `include/config/caps.h`: level caps, split exp progression, candy cap logic.

Split Exp is progression-scaled rather than fixed Gen 3 splitting. With multiple participants and zero badges, each participant receives the ordinary `1 / participants` share. Every badge converts one eighth of the remaining shared portion into personal Exp for every participant; with two participants the reward therefore progresses through 50%, 62.5%, 75%, 87.5%, and 100% at zero, two, four, six, and eight badges. One participant always receives full Exp. The same factor applies to the participant half when an Exp Share holder exists, while the Exp Share pool retains its own division.
- `src/fishing.c`, `include/config/fishing.h`: more lenient fishing and Suction Cups/Sticky Hold logic.
- `src/berry.c`, `data/scripts/berry_tree.pory`: minimum berry yield, resource-mode berry logic.

The Pokémon Center service-station rest advances the fake RTC by exactly eight hours with normal carry across day boundaries. The fake RTC configuration remains enabled; replacing this with wall-clock-only behavior breaks the rest service and the project's time-progression model.

Under the active Gen 3 berry-yield preset, Lum; Spelon, Pamtre, Watmel, Durin, and Belue; the five stat-pinch berries; Starf, Custap, Jaboca, Rowap, Maranga, and the e-Reader Enigma all retain a two-to-three yield floor/range. Later explicit balance overrides raise Lansat to 4–6, Enigma to 6–10, Micle to 4–6, and Kee to 3–4. These values were lost when Expansion rewrote the berry table even though the original minimum-yield change and later targeted overrides were still the latest zenmodeman intent.
- `src/pokemon_summary_screen.c`: IV/EV display and the rightmost Pokémon Details page. The Details page follows the Battle Moves list/description structure: Tier Points, stored Triumph count, and Tera Type are selectable rows with contextual descriptions. Tier Points have their own row rather than being appended to the trainer memo. Move-selection mode remains capped at the Battle and Contest Moves pages.

Known QOL/content systems:

- Party-menu move relearner: a single `RELEARN MOVES` option opens the level-up relearner directly for the selected non-egg Pokemon, without a category submenu. Only Pokemon with available level-up moves qualify; Resource Mode eligibility and facility restrictions apply. Closing the relearner returns to the party menu. Regression cases in `test/party_menu.c` cover visibility, restrictions, direct-entry state, and the full action list. See the [newest changes](../feature-history.md#newest-changes) for the pending repair and validation details.
- MenuFly, custom Cut HM users, HM deletion, Party Nickname option, Box Link, Pokedex Plus, no-whiteout battles, AI-vs-AI/player-side backsprite support.
- Oldale's Corviknight ride caller grants MenuFly through either direct interaction or nine surrounding coordinate triggers while `VAR_OLDALE_TOWN_STATE` is 1; receiving Fly advances the state to 2 so the approach triggers stop firing. The caller's map local ID is deliberately stable because every approach movement script targets it.
- Route 109 MenuFly softlock prevention: if Fly is used from Route 109 before Slateport is visited and Briney/boat are still present there, `SetFlyDestination` returns Briney and the boat to Dewford.
- Fake RTC and in-game time advancement.
- Reduced egg steps, auto-boxing egg hatches, improved hatch memo.
- Ordinary scripted gifts receive at least three randomly selected perfect IVs when every IV is unspecified. Explicit IV parameters bypass that project-wide floor and remain unchanged; species-specific `perfectIVCount` still applies through the current parameterized creation path.
- Split EXP progression scaling and level/candy caps.
- Resource Mode move services begin with three tutor and relearner points, or five for Monotype teams. Badge awards add one point normally or two for Monotype, with one additional affordability point when prior use meets the badge-dependent depletion threshold; tutor and relearner balances are evaluated independently.
- When Resource Mode points are exhausted, the center tutor is free only for Pokemon whose current ability and every reachable evolution stay at one tier point or less; the move relearner uses the analogous two-point threshold. Beedrill is an explicit exception to both free-service rules.
- Oldale's niche-ability tutor can expose up to two distinct viable alternate abilities, applies the player's selected slot, and treats Moxie as tutor-worthy specifically for Litleo and Pyroar. Its species-exception table is `SPECIES_NONE`-terminated.
- Failed fishing bites can award the lead Suction Cups user a Plain Bottle Cap, Bottle Cap, then Gold Bottle Cap. The third guaranteed reward waits for badge two; later rewards are chance-based and disabled in Resource Mode. Eggs, Sticky Hold, and other abilities do not qualify.
- Fishing uses shorter rounds, extended reel windows, and a bounded 40% near-completion input grace check. Missed input can still let a fish escape.
- Mystic is a 1.5× Psychic analogue of Steelworker assigned to Golduck, Noctowl, and Stantler; Dominate shares Download's switch-in Defense/Special Defense comparison and is assigned to Loudred and Exploud. Expansion's `DamageContext` and switch-in dispatch rewrites retained the data but dropped both runtime cases until the historical audit restored them with direct positive and negative contracts.
- Berry availability and minimum yield changes.

Behavior and integration notes:

- These systems often depend on callbacks and menu state; merge conflicts can compile while losing return paths.
- Route 109's Briney failsafe is intentionally in the successful Fly destination path, not the Fly cancel path.
- Menu, field-effect, daycare, and RTC helpers depend on custom callbacks returning to the correct screen/state.

## Data Balance And Learnsets

Many commits tune species data, learnsets, tutor compatibility, TMs/HMs, trainers, wild encounters, items, prices, and curated Tera assignments.

The surviving Demo 2 species redesigns include 70 Special Defense for both Grimer forms; the custom Gulpin, Swalot, Wailmer, and Wailord bulk profiles; Swablu's 55/45/65/50/45/80 spread, Natural Cure/Cloud Nine/Friend Guard slots, and level-32 evolution; Foongus's 74/65/55/15/65/60 spread; and Larvesta's 75/85/65/60/50/75 spread. These values are gameplay rules rather than incidental upstream data and have direct regression contracts.

Badge 2 tuning gives Beautifly Wind Rider and Dustox Corrosion in their second ability slots. Wurmple's level-7 Monotype branches select Silcoon for Flying and Cascoon for Poison, while ordinary runs retain personality-based branching. Ghost Monotype Nincada evolves directly into Shedinja at level 20; ordinary Nincada still evolves into Ninjask. These branch-selecting rules require a strict type match. They differ from the permissive Monotype eligibility condition used by Fletchling and Magikarp, where a disabled Monotype setting deliberately means “unrestricted.” A generic-condition merge had conflated the two semantics and caused ordinary Wurmple and Nincada to take Monotype-only branches; direct positive, negative, and normal-mode control tests now guard that boundary.

Beautifly also has custom Mud-Slap tutor compatibility. After Expansion moved teachable learnsets to generated data, that customization lives in `src/data/pokemon/all_learnables.json`; editing only generated `teachable_learnsets.h` will be lost. The historical audit restored the missing source entry and verifies the public compatibility query. The first expanded Tier Point table classifies representative Charizard, Snorlax, and Shedinja at four, five, and six points respectively. PC placement and shifting calculate the retained party total while excluding the destination slot before admitting the moving Pokémon; a direct budget contract covers occupied and empty destinations.

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

Behavior and integration notes:

- I keep conditional species-stat macros near their families; replacing only one branch with raw values loses the relationship between the alternatives.
- EV acquisition item effects and prices were standardized; item constants, item data, and effect arrays jointly describe those changes.
- Learnset helper JSON and generated learnset headers can diverge after merge conflict resolution.
- Curated Tera comments in `src/pokemon.c` often explain why high-tier species intentionally lack curated Tera.
