# Elastic Emerald Custom Functionality Dossier

This README summarizes the core project-specific functionality authored by commit user `zenmodeman`. It is intended as a regression-audit companion for the `merge-upgrade-helper` skill during upstream `pokeemerald-expansion` merges, and as a trace of custom systems that are easy to forget once they are woven into normal gameplay.

The inventory was built from local `git log --author=zenmodeman`, current symbol scans, and current implementation anchors. It intentionally focuses on feature additions, AI logic, mechanic changes, and merge-sensitive integration points, not routine moveset, encounter, map, or trainer balance changes unless those changes introduced a new mechanic or gate. Treat it as a functional map, not a complete design spec.

## Documentation Status

- Latest commit whose applicable project changes have been reviewed for this dossier: `13802b45662f6833e9f376cbd83837e70199e3a3` (`13802b4566`, merge of `e80ae569039786564381723fca22aac07afc3503`).
- Applicable work after that boundary: uncommitted first-port Expansion 1.15 merge repairs currently in the working tree, including trainer-backsprite palette lifecycle fixes, low-maximum-HP health-bar color handling, Forewarn tie-selection restoration, Hidden-STAB helper restoration, stale test-API migrations, and the mode/progression merge-guard tests described below.
- Maintenance rule: before advancing the commit above, review every applicable change through the proposed boundary. Keep not-yet-committed work labeled as uncommitted, and replace that label with its real commit once committed.

## Tag-Partitioned Custom Implementation Trace

This section groups the major custom implementations by Elastic Emerald release tag. Entries are grouped by where the implementation first appears in history; later fixes may be listed in a newer tag range or in the merge-regression ledger below.

### Up To `v0.1.0`

Major systems and mechanics:

- Initial content and scripting foundation: Poryscript setup, Petalburg Forest route boss, Sidney singles/doubles teams, early route content, Oldale Ruins, Petalburg Grove, Sandfront, Rustboro Grass, Trainer School flow, no-whiteout battles, AI-vs-AI player-side backsprite support, and early demo/progression guards.
- Mode framework: monotype selection, Resource Mode, Restricted Mode, EV mode, progression-based EV acquisition, truck-start variables/flags, mode-aware Oldale mart logic, Resource Mode berry/TM/consumable behavior, and mode-specific starter/gift setup.
- Monotype encounters and gifts: type-filtered wild encounters, tree encounters, monotype exceptions, monotype evolution handling, gender forcing for split-evolution lines, monotype catch-rate support, monotype starter expansion, and monotype-aware `givemon` improvements.
- Tutor and acquisition systems: Menu Move Relearner, Center Tutor data structure and resource logic, Tech Tutor/Tech House, already-learned Center Tutor count exclusion, Hyper Training/Bottle Cap NPCs, and custom gift IV shuffling.
- Tera framework: random/curated Tera assignment, Tera Orb teaching/charging, player-side Terastallization logic, and AI safeguards around pre-emptive player Tera calculation.
- AI foundation: item-clause support, double-target KO de-incentivizing, faster-attacker logic, Knock Off/Parting Shot/status scoring tweaks, Hidden STAB and non-protecting move helpers, move-effect viability before best damage, smart trainer flags, move history for Soak/Aqua Ring targeting, and early switch/immunity prediction work.
- Battle mechanics and ability work: item restore/prevent keeping trainer items, Life Orb recording, Summary Screen IV/EV display, Mud Sport and Water Sport protection changes, Hail/Snow defense behavior, trainer money formula by total levels, Pinch Berry healing, accuracy boosts for Foresight/Odor Sleuth/Laser Focus, Life Dew singles healing, Big Pecks defensive buff, Honey Gather/Honey rework, Heavy/Light Metal bounds, Electro Ball/Punishment changes, and initial Drain Douse.
- QOL and overworld: MenuFly, custom Cut HM users, HM deletion, Pokedex Plus, Party Nickname option, Box Link work/reversion, Fake RTC and time advancing, reduced egg steps, larger bags, minimum berry yield, fishing/content scripts, and map menu flag cleanup.
- Content-scoped systems that can still affect mechanics: early Route 101/102/104/115/116, Petalburg, Rustboro, Oldale, Sandfront, Trainer School, Aurelio, Cindy, Darren, Birch aide, and Roxanne checks.

### `v0.1.0` To `v.0.1.1`

Major systems and mechanics:

- Custom Cut HM use: field-effect generation, designated/custom mon Cut behavior, Cutter and Fly Rider dialogue support, and HM deletion support.
- Restricted Mode evolution-move guards and Move Tutor adjustments.
- AI and move-helper refinements: `IncreaseStatUpScore` stat-constant parameterization, monotype catch-rate/AI refinements, and miscellaneous move/learnset/script adjustments that support early-game systems.
- Rustboro/Sandfront content hooks: Roxanne first-battle check, Rustboro Center/Mart changes, and Route 115/116/Sandfront map/trainer integration.

### `v.0.1.1` To `v.0.1.2`

Major systems and mechanics:

- QOL/menu additions: Pokedex Plus, Party Nickname option, and Box Link.
- Tech Tutor and ability-tutor expansion: Niche Ability Tutor in Tech House, Tech House dialogue work, and Tech Tutor slot-fix follow-up.
- Restricted Mode ability-item guards: early Ability Patch guard work.
- New or modified ability mechanics: Covered/Fur Layer as Shield Dust clone, Solar Core, Frisk item-move modification, Limber speed-drop immunity, Truant Slack Off healing, Suction Cups starting-item and fishing refinements, and Water Veil/Aqua Ring interaction.
- Move and battle-mechanic updates: Mud Sport/Water Sport type checks, Assurance hurt tracking and accuracy component, Enticing/item-interacting move flags, monotype fishing guards, sweeping minimum monotype catch rate, and wild table expansion.
- Demo/progression/content support: demo guard, Devon Hyper Training dialogue, Wally duplicate fix, Rustboro mart fix, map/item/trainer adjustments, starter learnsets, tutor/encounter/evolution checks, and documentation checkpoint.

### `v.0.1.2` To `v.0.1.2.1`

Major systems and mechanics:

- AI upgrades: damage-optimized doubles targeting, GapThreshold fix, Illuminate rework and illuminating move category, and `IncreaseStatUpScore` change-id/stat handling.
- Ability and mechanic updates: Damp healing on switch-in against Rain/Water Sport, after-resolution Damp healing trigger, Truant `lastMoveFailed` logic, Razor Wind skipping recharge under Tailwind, and affection mechanic removal.
- Merge and script repairs: Tech Tutor var-order fix, truck dialogue fix, hidden-STAB read restoration, and post-merge adjustment commits.
- Content hooks: Dewford Garden starting content, overworld Sweet Scent doubles chance, Aurelio tweaks, Index Land slot completion, and trainer/move tweaks.

### `v.0.1.2.1` To `v.0.2.0`

Major systems and mechanics:

- Dewford/Gym 2 expansion: Dewford Garden, Granite Cave trainers/encounters/items, Brawly Gym script, Steven's Room/Tera Orb, Dewford Delibird gift, Rustboro trade monotype guard, Good Rod/fishing changes, Cindy level-increasing rematches, and demo `v0.2.0` guards.
- AI and switching: Hidden STAB switch logic, smarter speed-control logic, doubles preference logic for self-benefitting move effects, switch prediction for immunity abuse, defensive Tera calculation, smart Tera/switching adjustments, Coaching AI, simulated stat-change apply/reverse helpers, Reflect/Light Screen/Recovery/Rest/Defense Curl AI tuning, Paralysis/Leech Seed scoring, sport/Damp healing AI, OHKO switch timing, and Collector Darren AI.
- New or modified abilities: Merry, Dedicated, Inner Focus prevents Focus Punch loss, Astral Charge, Anticipation damage reduction, Covered rename, Forewarn modification, extra burn-damage-reduction exceptions, and additional derived ability work.
- Move and battle mechanics: Metal Rush, Present formula, more accurate Echoed Voice with battle-struct support, Refresh full-status/unblockable behavior, Drain Douse infinite-loop fix and later move-end absorb rework, Stockpile/Swallow/Gluttony synergy, Restricted evolution-item guards, custom move tests, Snore/Bounce groundwork via species changes, and Lucky Chant follow-up after the tag.
- Tier Points and restricted Tera: Tier Point display, catch/gift/evolution/PC/withdraw/empty-slot guards, 4-6 point values, Shedinja monotype/tier logic, truck-start integration, Restricted Mode Tera guard, and White Herb florist progression change.
- Curated Tera: main curated Tera pass, monotype-aware curated/random Tera behavior, curated species adjustments, and Rustboro/Steven/Tera teaching content.
- QOL and progression: auto-boxing egg hatches, improved egg hatch memo, item recording for defensive items, NPC level badge checks via `FlagGet`, fishing leniency restored, and miscellaneous freeze/flow fixes.

### After `v.0.2.0` / No Elastic Tag Yet

Major systems and mechanics:

- Upstream expansion merge survival: merges through `expansion/1.12.0`, `1.12.1`, `1.12.2`, `1.12.3`, `1.13.0`, `1.14.0`, and `1.14.4`, followed by several custom repair commits.
- Tier Points refinement: ability-aware point computation, ability-swap prevention, curated Tera/tier point tweaks, one-tier-point Center Tutor exception, restored Summary Screen tier point display, restored catch logic after `expansion/1.14.0`, and current party/PC/evolution/gift/tutor guard anchors.
- Item and mode refinements: Restricted Mode automatically enforces item clause before trainer battles by bagging duplicate held items in party order, monotype truck setup seeds the PC with resist berries for types super-effective against the chosen monotype, and Big Root drain recovery is buffed to 40%.
- AI refinements and tests: revealed-KO/lead/quad-effective fast-switch conditions, Dig switch removal, Sweet Scent double-battle static state, smarter double Rock Tomb logic, simulated stat-change guards/reverse fix, Wrap/binding best-damage work, Magic Guard and damage-gap exceptions, player held-item knowledge, resist-berry two-turn damage comparison, AI test additions, trainer flag restoration after merge breaks, and a simplified immunity-switch prediction rework for repeated player switch cycles.
- Move and ability regression repairs: improved Swallow logic after upstream refactors, Honey Gather regression repairs, binding and Drain Douse test repairs, Aqua Ring bonus-effect cleanup, extra Suction Cups restoration, species-specific Snore/Bounce modifications, Lucky Chant turn/priority adjustment, and post-merge minor patches.
- Data/mechanic standardization: standardized EV acquisition items and prices, Center Tutor/Brawly Combusken tweaks, Triumph counts, and several freeze-scenario fixes.
- Overworld fail-safes: Fly menu use from Route 109 can return Mr. Briney to Dewford when Slateport is not yet visited, preventing the early MenuFly softlock state where Briney remains stranded on Route 109.
- Documentation: feature summary/dossier commits now fold into this README.

## Merge Regression And Rework Ledger

Confirmed later-merge breakages already repaired in history:

- Hidden STAB move reading was broken by a merge and restored in `829ec9c367`.
- Tech Tutor var/slot ordering broke and was repaired in `bb06e1f632` and `e670a4e65b`.
- Scyther Cut event script was lost and restored in `f6508306a4`.
- Improved Swallow logic was broken by upstream battle refactors and repaired in `8bd215017a`.
- Honey Gather regressed and was repaired in `23421cb46e`.
- After `expansion/1.14.0`, monotype filtering, non-monotype modulus behavior, Tier Points catch logic, extra Suction Cups behavior, AI flags, candy cap logic, and Aqua Ring bonus-effect cleanup needed restoration in `5b2db2f453`, `448477bf2e`, `4038c36be7`, `5d34747fa5`, and `86a1b336ef`.
- After `expansion/1.14.4`, additional minor custom-functionality patches landed in `9865fe909f` and `0cf4955fd9`.
- During the first `expansion/1.15.0` merge portion, the new generational-config API required bare tags in `GetConfig`, level-cap calls gained an explicit hard/candy-cap argument, and variable config tags required `GetConfigInternal`. The merge also displaced Metal Rush's weight-dependent additional effect, full player held-item AI knowledge, repeated-switch immunity prediction, and weather-setter preservation; these were restored as uncommitted merge work on the 1.15 runtime and AI APIs. Incoming-mon prediction must run its final damaging-move comparison against the temporary predicted battler, then restore the active battler and cached AI damage data. Expansion 1.15's `HandleKOThroughBerryReduction` now provides the consumed-resist-berry follow-up damage model, so the older local temporary-hold-effect simulator should not be duplicated.
- Binding, Wrap, and Drain Douse tests required post-merge fixes around `bd83b55fb4`, `c701193e0d`, and `be3390bd51`.
- A post-1.15 test-ROM build found that Forewarn's tests and deterministic tie handling had survived on opposite sides of the merge: the tests referenced `RNG_FOREWARN`, while the runtime had reverted to pairwise untagged randomness and lacked the empty-candidate guard. The uncommitted repair restores the tagged uniform tie selection and its RNG constant. The same build found stale tests for removed generational keys (`B_INFILTRATOR_SUBSTITUTE`, `B_TAUNT_ME_FIRST`, `B_BATON_PASS_TRAPPING`, `B_PSYCH_UP_CRIT_RATIO`, and four Transform failure keys) plus renamed move target/effect APIs; those tests now assert the current fixed behavior or current helper names.
- The same audit found that `GetMovesArrayWithHiddenSTAB` remained covered by a custom test but had lost both its declaration and implementation. The uncommitted repair restores the helper on the current `gBattleHistory` and move APIs, excludes status, recharge, and delayed two-turn attacks from hidden-STAB inference, and leaves ordinary move-specific logic on revealed `GetMovesArray` data.
- The broad `Zenmodeman:` test-build audit repaired the remaining custom regressions across hard level caps, Anticipation, Astral Charge, defensive contact abilities, Honey Gather, Heavy/Light Metal (with Light Metal capped at 40 kg), Drain Douse, Metal Rush, Mud/Water Sport, repeated-switch prediction, and weather-setter preservation. All 40 custom/merge-guard tests pass. Several failures were stale fixtures rather than runtime defects: explicit `SEND_OUT` actions after the upgraded `SWITCH` helper, ability overrides that did not represent party-data weather synergy, and a Sheer Force Copperajah suppressing Metal Rush's additional effect.

Current audit status from static symbol scans:

- Monotype, Tier Points, curated Tera, Restricted/Resource gates, Drain Douse, custom abilities, and smart AI systems all still have live data and runtime anchors in current `include`, `src`, `data`, and `test` scans.
- Drain Douse still injects through `MOVEEND_ABSORB` and still has script/message/test anchors. Several advanced Drain Douse tests remain commented out in `test/battle/move_effect/drain_douse.c`; treat that as a test coverage gap, not proof the runtime is broken.
- Tier Points catch/gift/evolution/PC/tutor/ability-change paths are present, including `gExcessTierPoints`, Summary Screen display, and one-point Center Tutor exceptions.
- AI prediction and smart switching still retain `AI_FLAG_PREDICT_SWITCH`, `AI_FLAG_PREDICT_INCOMING_MON`, `AI_FLAG_SMART_TERA`, `GetMostSuitableMonToSwitchInto`, and `ShouldSwitch` hooks, plus tests for prediction and smart Tera. Held-item awareness now also feeds damage simulation for player-side items, including resist berries.

Likely rework candidates:

- Tier Points now compute with ability awareness, but the point table itself is still hand-coded in `src/elastic_emerald_pokemon.c`; if expansion gains richer species/form metadata or if more form/ability exceptions accumulate, consider moving tier data into a structured species-side table.
- Curated Tera is still centralized in code; as curated lists grow, a data-driven species table would make merge conflict resolution easier than editing a large switch/list in `src/pokemon.c`.
- Monotype exceptions and gender-forced split-evolution handling are runtime helpers in `src/wild_encounter.c`; these are stable, but they should be revisited if expansion adds native encounter filters or richer evolution-family predicates.
- Drain Douse's current `MOVEEND_ABSORB` integration is the right post-refactor shape, but double/spread/mixed-target semantics are under-tested because several tests are commented out.
- Smart AI systems are extensive and merge-sensitive. When expansion changes AI damage, switching, or Tera APIs, prefer adapting these helpers onto the new upstream utilities over preserving stale duplicated calculations.

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
- `src/elastic_emerald_pokemon.c`: `GetMonoType`, tier-point calculations, tutor-resource eligibility, party totals, and automatic party-to-PC deposits after the 1.15 core rewrite.
- `src/pokemon.c`: curated/random Tera assignment and the upstream Pokémon core.
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

- `src/elastic_emerald_pokemon.c`: `GetMonoType`.
- `src/wild_encounter.c`: `IsMonMonotypeException`, `TryGetMonotypeWildMonIndex`, land/shaking/fishing filters, gender fixes for split-evolution lines.
- `src/script_pokemon_util.c`: `PopulateMonotypeResistBerriesInPC`, which seeds PC resist berries during truck setup for monotypes weak to covered attacking types.
- `src/evolution_scene.c`: Shedinja and other evolution exceptions.
- `src/battle_terastal.c`: Tera is allowed only if it preserves the monotype or is Stellar.
- `data/maps/InsideOfTruck/scripts.pory`: monotype choice and explanation.
- `src/data/wild_encounters.json`: type-compatible encounter planning.
- Map scripts and trainer data: monotype-specific gifts, dialogue, and balance adjustments.

Audit checks:

- Wild encounter filtering must fall back to a valid compatible slot rather than allowing incompatible species in monotype mode.
- Exceptions such as Snorunt/Ghost, Ralts/Fighting, Burmy exclusive-evolution types, Shedinja/Ghost, and split-evolution gender forcing must survive refactors.
- Truck setup should still add 12 copies of each applicable resist berry to PC storage for attack types that are super-effective against the selected monotype.
- Tera legality must continue to consider both the chosen monotype and Restricted Mode bans.
- Search for `GetMonoType()` after merges. If only data references remain, runtime hooks likely dropped.

## Tier Points System

Tier Points is a party-budget mode that assigns point values to Pokemon, constrains catches, gifts, evolutions, PC movement, ability changes, and tutor access, and displays points in UI.

Primary anchors:

- `include/pokemon.h`: `GetMonTierPoints`, `CountPartyTierPoints`, `CalcTierPointsAfterEvolution`, `CalcTierPointsAfterAbilityChange`, `CanMonUseCenterTutorWithCurrentResources`.
- `src/elastic_emerald_pokemon.c`: species/ability-aware tier point calculations, party total, Center Tutor exceptions, and auto-box support.
- `src/pokemon.c`: Pokémon creation/data paths and curated Tera dependencies.
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
- `src/battle_setup.c`, `include/battle_setup.h`, `src/battle_tower.c`: `BattleSetup_EnforceRestrictedModeItemClause` removes duplicate held items from the player's party before trainer battles, sending them to bag, then PC, then discard if no storage remains.
- `src/pokemon.c`: Restricted evolution conditions and move/tutor compatibility.
- `src/elastic_emerald_pokemon.c`: `CanMonUseCenterTutorWithCurrentResources`, free-tutor evolution-chain checks, and Resource Mode tutor/relearner eligibility.
- `src/party_menu.c`: item use and ability-change restrictions.
- `src/pokemon_storage_system.c`: restricted release move ownership checks.
- `src/data/items.h`, `src/data/pokemon/item_effects.h`, `include/constants/item_effects.h`: EV acquisition items and prices.
- `data/maps/*/scripts.pory`: marts, gifts, tutors, and progression requirements that change under modes.
- `src/battle_terastal.c`: Restricted Mode Tera bans based on tier threshold.

Audit checks:

- Do not reduce Restricted Mode to only script gates; party menu, evolution, release, and Tera checks are also enforcement points.
- Do not restore old explicit Roxanne/Brawly item-clause script gates unless the automatic trainer-battle item-clause enforcement is intentionally removed.
- If a merge changes item-use, tutor, or evolution APIs, re-thread Restricted Mode checks through the new helper path.
- If a merge changes trainer-battle setup callbacks, ensure Restricted Mode item-clause enforcement still runs before standard trainer battles, Battle Pyramid/Trainer Hill battles, and Battle Tower trainer battles.
- Restricted release logic should prevent releasing the sole owner of certain required moves.
- Resource Mode shop/gift/tutor scripts should be audited when command names or item constants change.

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

Audit checks:

- Preserve the script call before every supported trainer/rematch start, not only the C special or result constants.
- New trainer classes default to no healing until explicitly categorized. Confirm trainer IDs/classes and generated trainer documentation together.
- Keep battle-end sleep reroll calls on every supported callback; a refactor that updates only one exit path creates inconsistent persistent status behavior.

## Curated And Random Tera

Elastic Emerald supports curated species-specific Tera choices, random Tera fallback, monotype-compatible Tera handling, and Restricted Mode Tera bans.

Primary anchors:

- `src/pokemon.c`: `getCuratedOrRandomTeraType`, `GetTeraTypeFromPersonality`, `MON_DATA_TERA_TYPE` handling.
- `include/pokemon.h`: `teraType` substruct field, `forceTeraType`, Tera prototypes.
- `include/config/battle.h`: `B_FLAG_TERA_ORB_CHARGED` and `B_FLAG_TERA_ORB_NO_COST` are intentionally both `FLAG_TERA_CHARGED`.
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
- Tera Orb charge is intentionally no-cost in Elastic Emerald. Do not report `B_FLAG_TERA_ORB_CHARGED` and `B_FLAG_TERA_ORB_NO_COST` sharing `FLAG_TERA_CHARGED` as a breakage unless the design changes.

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
- `Big Root`: locally buffed drain recovery to 40%; the runtime multiplier in `GetDrainedBigRootHp` is the important behavior, not just the item data parameter.
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
- Drain Douse is especially sensitive to move-end refactors; verify both runtime healing and AI/test expectations. `BS_SetDrainDouse` only sets the volatile, so `MOVEEND_ABSORB` must also consume `gBattleMons[gBattlerAttacker].volatiles.drainDouse` and call `BattleScript_DrainDouseHeal` or `BattleScript__DrainDouseOoze`.
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
- Player held items are known to the AI at all times; player-side `AI_DecideHoldEffectForTurn` uses the battler's current held item effect, and player party data records held items outside omniscient-only knowledge.
- Resist berries are modeled as consumed over repeated damaging turns: the first hit uses current simulated berry-reduced damage, later hits recalculate without the berry, and non-OHKO same-KO-timing move comparisons can prefer the higher two-turn damage line.
- Smart switching integrates hazards, weather, status, recurring healing/damage, priority, 1v1 viability, ace rules, Baton Pass, Truant, Wonder Guard, trapper, choice lock, and ability-benefit switches.
- Switch prediction mirrors player-side `ShouldSwitch` and can score against predicted incoming Pokemon.
- Immunity-switch prediction is intentionally singles-only and now keys off repeated player switches during the current AI battler's field stint, not the old per-mon repeated-immunity-switch gate. `gAiBattleData->playerSwitchesDuringAiStint` resets when the AI mon switches out, increments for voluntary player hard switches and normal player pivot moves, and excludes forced switch-outs such as phazing or Red Card switch cases.
- `AI_FLAG_PREDICT_INCOMING_MON` immunity prediction only considers a revealed, non-active player party mon after at least six player switches during the current AI stint. The move being predicted around is the highest-scored damaging move chosen by the normal scoring pass in `ChooseMoveOrAction_Singles`, after damaging-move comparison; status moves and unavailable moves do not trigger this path.
- The RNG gate for this prediction should remain `PREDICT_SWITCH_CHANCE` through `RNG_AI_PREDICT_SWITCH`. The helper-side defensive-switch chance is deliberately 100% so there is not a second independent 50% roll hiding in the immunity candidate path.
- Candidate priority for immunity prediction is: highest existing `switchInCount` among revealed player mons, then higher immunity value, then random tie selection. Ability absorption immunities such as Volt Absorb or Lightning Rod outrank ability blockers, which outrank type immunities such as Ground into Electric.
- Smart Tera chooses Tera for KO, survival, and priority contexts.
- Move prediction and move history logic help with Soak, Aqua Ring, and target expectations.
- Simulated stat changes support Coaching and similar doubles decisions, with apply/reverse guards.
- Doubles targeting prefers damage-optimized targets and self-benefitting effects where appropriate.
- Special cases include Rock Tomb doubles logic, Sweet Scent double-battle logic, Focus Punch on predicted switches, Recovery/Rest/Reflect/Light Screen scoring, Paralysis/Leech Seed scoring, Sport/Damp Healing awareness, and immunity abuse.

Audit checks:

- Search for `AI_FLAG_SMART_TRAINER`, `AI_FLAG_PREDICT_SWITCH`, `AI_FLAG_SMART_TERA`, `GetMostSuitableMonToSwitchInto`, `ShouldSwitch`, `AI_CalcDamage`, and `ApplySimulatedStatChanges`.
- Be suspicious of boolean rewrites in AI helper arguments, especially battler indexes and side indexes.
- Predicted-switch logic may use `PARTY_SIZE` as a generic switch sentinel. Guard `gAiLogicData->mostSuitableMonId[...]` before indexing a party array, and scan for accidental `if (...);` constructs around predicted-switch checks.
- For immunity-switch prediction, verify `playerSwitchesDuringAiStint` is reset on AI switch-in and only incremented for valid player switch/pivot cases. Keep forced switches excluded, and keep the prediction overlay after normal move scoring so it uses the current highest-pointed damaging move rather than preselecting an immunity before scores exist.
- Regression tests for this behavior live in `test/battle/ai/ai_flag_predict_switch.c` with `Zenmodeman:` names. They should exercise the pre-threshold active-target behavior, the six-switch threshold, the `PREDICT_SWITCH_CHANCE` RNG gate, and the `switchInCount` before immunity-value tie-breaker ordering.
- Any runtime battle mechanic change should have an AI mirror if the AI scores or predicts it.
- Resist-berry AI depends on `gAiLogicData->holdEffects` being restored after temporary no-item damage simulation; also verify Unnerve/As One still prevents the berry damage modifier through `IsUnnerveBlocked`.
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
- Route 109 MenuFly softlock prevention: if Fly is used from Route 109 before Slateport is visited and Briney/boat are still present there, `SetFlyDestination` returns Briney and the boat to Dewford.
- Fake RTC and in-game time advancement.
- Reduced egg steps, auto-boxing egg hatches, improved hatch memo.
- Split EXP progression scaling and level/candy caps.
- Fishing behavior changes and lead Suction Cups item logic.
- Berry availability and minimum yield changes.

Audit checks:

- These systems often depend on callbacks and menu state; merge conflicts can compile while losing return paths.
- Route 109's Briney failsafe is intentionally in the successful Fly destination path, not the Fly cancel path.
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

## Expansion 1.15 First-Port Build Findings

The first 1.15 merge build exposed several custom systems whose callers or data survived while their implementation hooks were lost. The port restores:

- MAP/FLY start-menu labels and the Fly error script export.
- Suction Cups fishing item rewards on a failed bite.
- Trainer PP Ups, NPC center tutors, resource-mode relearner/tutor costs, and the item-clause party special.
- Restricted-level and monotype evolution conditions, including a missing break that previously fell through to the region condition.
- Tier-point calculation/party enforcement, egg/evolution auto-box support, and monotype lookup in `src/elastic_emerald_pokemon.c`, separated from the heavily rewritten upstream Pokémon core.
- Drain Douse and Damp healing battle-script commands/flow, plus illuminating and Merry move-end effects.
- The custom AI/runtime ability-block query used by repeated-switch immunity prediction, adapted to the 1.15 move-resolution APIs.
- Correct player backsprite palettes during battle intros. `gTrainerBacksprites` uses full `enum TrainerPicID` designated indices, so callers must not subtract `TRAINER_PIC_FRONT_COUNT`. Load the backsprite palette once through `LoadSpritePalette`, select it with `IndexOfSpritePaletteTag` in every trainer draw/slide path, and do not allocate a duplicate palette during the ball throw; fixed OBJ palette slots can be overwritten or reused during the intro.
- Correct HP-bar colors for low-HP, low-level battlers. When maximum HP is below the 48-pixel health-bar width, the animated current value is Q24.8 fixed-point and must be converted before passing it to `GetHPBarLevel`; comparing the raw value makes damaged low-level opponents appear permanently green.

The full modern build and a second incremental build both link successfully and produce `pokeemerald.gba`. Merge-marker and unmerged-path scans are clean. The merged upstream tree still contains pre-existing whitespace findings and CRLF normalization notices in generated map/script files.

## Tests And Static Verification Targets

Useful targeted test files when the user asks for tests:

- `test/elastic_emerald_modes.c` (ten `Zenmodeman: Merge guard:` contracts for monotype encoding/startup inventory, Tier Points, and Restricted Mode item clause)
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
rg -n 'Drain Douse|EFFECT_DRAIN_DOUSE|trydamphealing|Honey Gather|Astral Charge|Merry|Covered|Stockpile|Swallow|Echoed Voice|AI_FLAG_SMART_TRAINER|AI_FLAG_PREDICT_SWITCH|AI_FLAG_SMART_TERA|ApplySimulatedStatChanges|BattleSetup_EnforceRestrictedModeItemClause|PopulateMonotypeResistBerriesInPC|TryGetResistBerryConsumedDamages|TryReturnMrBrineyToDewfordAfterRoute109Fly' include src data test
```

Avoid full build checks unless explicitly requested.

The first automated merge-guard batch should retain these ten contracts, ranked by merge sensitivity and cross-system reach:

1. Monotype save-value decoding across the removed type slot.
2. Monotype startup seeding of exactly the super-effective resist berries.
3. Egg exclusion from Tier Points.
4. Ability-aware Tier Points for weather setters.
5. Badge-progression-aware Tier Points.
6. Safe default Tier Points for a missing candidate.
7. Party Tier Point totals excluding eggs and empty slots.
8. Evolution Tier Point projection without mutating the party.
9. Ability-change Tier Point projection without mutating the party.
10. Restricted Mode item-clause enforcement, including returning the later duplicate to the bag.

Run this batch with `make check TESTS='Zenmodeman: Merge guard:*'`. After a successful test-ROM build, repeat the command incrementally to catch unstable generated dependencies.
