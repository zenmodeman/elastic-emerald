# Upstream upgrade notes

I use the [custom feature reference](feature-reference.md) to locate local behavior and the [feature history](../feature-history.md) to distinguish introductions, redesigns, and repairs.

## How I approach a merge

The working diff, merge parents, and unmerged paths establish what is changing. Structural problems—duplicate enums, fields, cases, or interleaved braces—often need attention before a semantic comparison is possible.

My aim is to retain the current Elastic Emerald behavior on the newer upstream APIs and data layouts. Later local commits matter: restoring an older implementation can accidentally undo an intentional redesign. Adjacent code also matters, because stale callers and generated inputs can sit outside the conflict hunk.

I trace a feature through its constants/data, runtime dispatch, scripts, UI, save state, and AI simulation. A declaration or surviving test does not establish that its runtime caller survived. Record non-obvious resolutions here or in the relevant developer topic guide when they help prevent recurring breakage. Keep repair details out of the feature reference.

Routine review uses [static checks](check-recipes.md). Full builds and test runs are separate decisions. When I do build, compilation, linking, and ROM generation are distinct milestones; an incremental follow-up can expose unstable generated dependencies.

## Recurring failure patterns

- Undefined custom symbols can mean that a rewritten core retained callers but lost implementations or shared state. Empty stubs would hide that loss.
- A newly unused helper can indicate a severed runtime hook rather than obsolete behavior.
- A coherent project-owned compatibility module can reduce conflict surface in a frequently rewritten upstream file.
- Numeric collisions can survive a clean textual merge, particularly in battle-type bits, trainer modes, flags, and palette ranges.
- Generated outputs follow their source and current generator; an output deleted or ignored by upstream may no longer belong in the repository.
- Boolean rewrites can change helper arguments, invert a condition, or save and restore different battler indexes.
- Conditional species-stat macros can disappear from one branch or move below their users.
- A missing dispatch case can disable a configuration-gated mechanic even when its data still compiles.

## Battle AI parity

The [battle AI notes](battle-ai.md) cover simulation and scoring. I compare the model with runtime ability suppression, immunity, dynamic targets, item negation, and check-only versus script-running calls, while retaining intentional knowledge limits.

Some apparent anomalies are deliberate. Tera Orb charged/no-cost flags share an alias because charging has no cost. The old clean-state and weather-preservation switching paths are also historical; matchup commitment superseded them.

## Priority merge-breakage checks

These are recurring failure points, not a historical feature inventory. Check the affected paths even when the merge has no textual conflicts.

| Area | Preserve during upgrades |
| --- | --- |
| Monotype | Saved type decoding across the removed type slot, compatible split evolutions, and starting resist berries for exactly the selected type's weaknesses. |
| Tier Points | Exclude eggs and empty slots; retain ability- and badge-dependent costs, safe defaults for missing candidates, and evolution/ability projections that do not mutate the party. |
| Restricted item clause | Keep enforcement before trainer battles and return later duplicate held items to storage. |
| EV and Resource modes | Retain local EV caps and mode gates. Keep consumable-item persistence ahead of upstream trainer-battle item-return rules. |
| Custom battle effects | Follow runtime dispatch and move-end hooks as well as data; check the matching AI model. Surviving descriptions alone do not establish working behavior. |
| Party menus and services | Preserve relearner access, tutor costs, selected-Pokemon state, and return callbacks. |
| Numeric namespaces | Check battle flags, trainer modes, save flags, and palettes for collisions introduced by FRLG integration. |
| Battle display | Keep trainer backsprite palette indexing and low-HP bar conversion. Separate intro party trays for each trainer; the shared layout retained in merge `5725273a2a` hid paired trainers' Pokeballs. |

Keep only actionable lessons here. Feature history records brief outcomes and commit IDs; old test counts, exhaustive feature accounts, and release-by-release audit narratives do not need a separate archive.

## Source paths to review during upgrades

I trace an affected system through data, prototypes, save flags/vars, scripts, UI, AI calculations, and tests. The complete runtime path matters because a surviving declaration can conceal a lost implementation hook. My usual resolution retains Elastic Emerald behavior on current upstream APIs, with static review first and builds handled separately.

High-risk files that repeatedly contain local behavior:

- `src/pokemon.c`
- `include/pokemon.h`
- `src/battle_terastal.c`
- `src/battle_ai_main.c`
- `src/battle_ai_util.c`
- `include/battle_ai_util.h`
- `src/battle_ai_switch.c` and `src/battle_ai_items.c`
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

## Expansion 1.17.1 integration

Trainer generation now lives in `battle_setup.c` and `trainer_util.c`. Keep level modifiers and evolution-on-scaling in the setup path, and retain PP bonuses and EV Mode gating in the shared generator. Dynamic trainer script snippets must call the pre-battle healing script. Paired approaches and explicitly paired battles must record the two-opponent reward state before battle starts. The AI demonstration uses the current trainer command layout and its AI-versus-AI battle flag to continue after a loss, independently of early-rival handling.

Additional effects now dispatch through `battle_set_effect.c` and `constants/battle_set_effect.h`. Metal Rush and Overwhelm Beam need handlers there; declarations alone leave a null dispatch entry. Resolve Metal Rush's light-user recipient before target secondary-effect blockers. Befuddle uses the random-effect list and `RNG_RANDOM_FROM_LIST`. Native draining is now an additional effect, so Drain Douse's move-end recovery must not add the native drain a second time. Present's local probability distribution belongs in the new power/category setup helper.

Target failure checks now run in phases. Proactive Color Change belongs after Protect and bounce checks but before target immunities and effectiveness, including delayed attacks. AI checks temporarily change and restore target types around the current blocking/effectiveness helpers. Preserve the predicted-switch score rather than comparing it again against the restored active opponent. Debug damage displays use `AiCalcValues` through the current calculation API and preserve the dynamic damage category.

The local relearner deliberately retains its own state machine, Resource Mode charging, party-menu entry, and Summary Screen category cycling. Avoid interleaving it with upstream's task-based replacement. Scripted gifts use `PokemonTemplate`; apply the three-perfect-IV floor only when all IVs are unspecified. Explicit IVs and species guarantees retain their separate rules.

`include/constants/wild_encounter.h` is generated from `wild_encounters.json` and `wild_encounters.constants.json.txt` and is no longer tracked. Use generated slot-count names, including custom shake encounters. The JSON retains forty land slots. The retired trainer-mode constants header is removed. Petalburg's custom tiles must not be truncated to upstream's vanilla tile count. The recorded-battle action buffer is reduced to 386 bytes per battler so the current header and parties fit before the save-sector counter; old recordings are not a compatibility target for this upgrade.

The recent migration scripts were reviewed against their target constructs. Regional dex and coin-box changes are already present, and no legacy coin-box arguments or load-sprite commands remain to migrate. Do not rerun the 1.17 coin-box script indiscriminately: it subtracts one from show-box coordinates each time. The older graphics migration warns against running over a tree containing build artifacts; preserve current INCGFX declarations and custom assets directly here.

Validation for this resolution uses conflict scans, diff checks, generated encounter constants, Python syntax checks, and C front-end syntax checks. Graphics include expressions are replaced with placeholders only in temporary syntax-check input to avoid generating assets. These checks do not verify graphics sizes, linking, ROM layout, or battle outcomes. ROM builds and Expansion/Elastic test execution remain separate, explicitly requested steps.

### Build follow-up

The full assembler pass also needs the custom battle scripts migrated: accuracy checks now belong to `attackcanceler`, `end2` is replaced by `end`, and `healthbarupdate` takes only the battler. `datahpupdate` takes the current Assurance flag. Keep one definition of `Std_MsgboxAutoclose`; combining the old trainer scripts with dynamic snippets can duplicate it and leave an orphaned command tail.

The Tier Point projection over terminal-species forms intentionally considers only Mega forms, so its `FormChanges` enum switch needs an explicit default for other methods under `-Werror=switch`. The retired `ABILITYEFFECT_COLOR_CHANGE` enum entry has no remaining callers: proactive Color Change runs in target failure checks, while Berserk and Anger Shell use `ABILITYEFFECT_HP_THRESHOLD`.

After these follow-up fixes, `make -j4` completed compilation, assembly, linking, and ROM generation. A subsequent incremental `make -j4` also completed successfully. The resulting ROM uses 27,040,820 bytes of the 32 MiB ROM region. Runtime Expansion and Elastic tests were not run in this build-repair pass.
