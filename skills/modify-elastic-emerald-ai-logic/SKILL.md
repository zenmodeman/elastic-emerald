---
name: modify-elastic-emerald-ai-logic
description: Implement, diagnose, review, or document battle-AI behavior in Elastic Emerald. Use for changes involving move scoring, target choice, switching, inferred or revealed information, damage and speed simulation, temporary battle-state mutation, AI knowledge, trainer items, doubles coordination, Terastalization decisions, or AI tests; also use when a gameplay mechanic needs a matching AI model or an AI regression must be checked after nearby code changes.
---

Read `AGENTS.md` for repository conventions. Maintain this skill’s technical guidance when changes affect it.


# Modify Elastic Emerald AI Logic

## Core workflow

1. Read the repository `AGENTS.md` and obey its build and test restrictions.
2. Read `skills/modify-elastic-emerald-ai-logic/references/behavior-summary.md`, including its documentation status, before changing behavior.
3. Inspect `git status`, the relevant diff, and recent history. Preserve unrelated user changes.
4. Trace the complete decision path before editing: information acquisition, cached data, simulation, score or switch gate, candidate selection, and final action.
5. State the intended information policy in code: distinguish actual, revealed, inferred, predicted, and omniscient data.
6. Implement the smallest coherent behavior change and restore every temporarily mutated state carrier.
7. Run targeted static checks only unless the user explicitly requests a build. Update AI documentation in the same work.

Before restoring older AI logic during an upgrade, check whether a newer commit deliberately removed or superseded it. Preserve the current design decision rather than reviving an abandoned heuristic merely because its old symbols still appear in history or tests. In particular, generalized clean-state/fast-KO switching is historical in this project; both generalized clean-state switching and weather-setter preservation have been superseded by matchup commitment. Read the current battle-AI notes and behavior summary before restoring any heuristic.

## Simulation and decision guardrails

- Compare the same move, battler, or switch candidate across alternate states. Do not let independent maxima from different candidates satisfy separate halves of one condition.
- When a decision requires both actual and hypothetical validity, require both explicitly. A clean-state result is a guard on real behavior, not a replacement for the current-state check.
- Recalculate an exact move when inferred and revealed move arrays may not share cache indexes. Do not assume a cached damage slot describes a separately constructed move array.
- Use effective speed helpers when stat stages, abilities, items, status, weather, or field effects matter. Decide deliberately whether priority and Trick Room belong in the comparison.
- Preserve imperfect information. Do not read hidden moves, abilities, or party data unless the applicable AI flags or inference policy authorize it.
- Prefer evidence-backed exceptions. For example, depleted PP can show that a battler attempted a self-debuffing move; merely knowing that the move exists is weaker evidence.
- Use stable identity for lead and party reasoning. Party slot plus switch-in history is more reliable than first-turn flags when the requirement concerns the literal lead.
- Keep active gimmicks such as Tera and current item changes when design intent says they remain real. Remove only the state classes the hypothetical calculation is meant to neutralize.

## Temporary state checklist

Before a simulation, identify every global or cached structure the called helpers can read or mutate. Relevant carriers commonly include:

- `gBattleMons`, including stat stages, types, ability, item, PP, and volatiles;
- `gDisableStructs` and other per-battler transient structures;
- field, side, weather, and gimmick state;
- `gAiLogicData` abilities, items, hold effects, speed caches, and calculation flags;
- dynamic move type/category globals and prediction state.

Snapshot before mutation and restore on every exit. Prefer a single exit after restoration when a helper has several temporary changes. Preserve the caller's prior calculation flags instead of assuming they were false.

When adding a clean-state calculation, define its contract beside the helper. Typical protected player tech includes temporary type changes, added types, immunity bypass, grounding, ability replacement or suppression, and externally caused negative defensive or Speed stages. Self-caused drops may remain when battle evidence supports them. Keep actual-state checks alongside the clean calculation so the AI never reacts to a hypothetical KO or speed order that does not exist.

## Runtime and AI parity

When adding AI support for a gameplay mechanic, trace the runtime implementation first. Match its type resolution, ability suppression, item negation, grounding, status immunity, move properties, and generation/config gates. If AI and runtime helpers intentionally differ because of knowledge limits, document the difference.

If an upstream refactor combines or splits runtime immunity helpers, keep any compatibility query used by AI prediction behaviorally aligned with the new runtime path. Verify Soundproof/Bulletproof/Good as Gold-style blockers, side-wide priority blockers, dynamic move targets, and the distinction between check-only and script-running calls.

For upgrade or merge work that touches AI, load `skills/merge-upgrade-helper/SKILL.md` first and read `skills/merge-upgrade-helper/references/upstream-upgrades.md`. Then apply this skill to verify that the resolved code still represents the intended AI behavior.

## Verification and documentation

- Use `rg` to confirm callers, state fields, move-effect coverage, and stale logic.
- Run `git diff --check` and inspect the complete diff. Do not run a full build unless explicitly requested.
- Name new tests with the `Elastic-tests: ` prefix. Prefer tests that distinguish actual versus hypothetical state and verify restoration after simulation.
- Update `skills/modify-elastic-emerald-ai-logic/references/behavior-summary.md` with the behavior and key commits.
- If AI changes are uncommitted, list them as uncommitted in the summary. On later documentation edits, reconcile that marker with `git log` and the relevant committed diff before advancing the last-documented commit.

## Current implementation and maintenance notes

Read the [AI behavior summary](references/behavior-summary.md) for current decision rules and reviewed implementation history.

## Information and comparisons

Distinguish actual, revealed, inferred, predicted, and omniscient information. A simulation can be numerically accurate yet make the AI unfair if it obtains a hidden move or ability outside the intended knowledge policy.

Comparisons across alternate states concern the same move or switch candidate. Combining the best result from one candidate with a condition satisfied only by another can produce a decision that neither candidate supports. Similarly, inferred and revealed move arrays can have different indexes, so an exact-move recalculation is sometimes necessary instead of reusing a damage-cache slot.

Effective Speed includes stages, abilities, items, status, weather, and field effects. Whether priority and Trick Room belong in a comparison depends on whether the comparison models raw Speed or actual turn order. For lead identity, party slot and switch-in history carry more information than a first-turn flag.

For doubles Speed-drop redundancy, retain the target alongside the simulated partner move. Use the AI processing order to distinguish simulated actions from already chosen actions; numeric battler order is insufficient when processing is reversed. Runtime Low Kick records Float Stone when calculating its weight-based power; calculation-only AI queries must not record it.

Prefer evidence-based exceptions. Depleted PP, for example, supports an inference that a self-debuffing move was attempted; merely knowing the move does not. Hypothetical calculations retain real state such as active Tera and item changes unless that particular calculation is intended to remove it.

## Temporary battle state

The simulation helpers share mutable state with the battle engine. The relevant state commonly includes:

- `gBattleMons`: stages, types, ability, item, PP, and volatiles;
- `gDisableStructs` and other per-battler transient structures;
- field, side, weather, and gimmick state;
- `gAiLogicData`: modeled abilities/items, hold effects, Speed caches, and calculation flags;
- dynamic move type/category globals and prediction state.

Structure simulations as a snapshot, a temporary calculation, and a restoration. Restoration includes the caller's previous flags, even when they were already enabled. A single restoration path makes this easier to reason about than several early returns.

Historical clean-state experiments distinguished temporary type changes, immunity bypass, grounding, ability replacement/suppression, and externally caused defensive or Speed drops from the underlying matchup. Self-caused drops could remain when battle evidence supported them. Those experiments also required actual-state validity: a hypothetical KO alone was insufficient.

Generalized clean-state switching and the later weather-setter preservation heuristic are now historical. The current fast-KO path uses [matchup commitment](references/behavior-summary.md#matchup-commitment-for-fast-ko-switching), introduced in `53239d220d` and refined in `9c4b986496` and `c753e34660`. Use that history to distinguish intentional redesigns from merge losses.

## Runtime and simulation parity

Runtime behavior is the reference for type resolution, ability suppression, item negation, grounding, status immunity, move properties, and generation/configuration gates. Differences in the AI model are sometimes intentional because the AI has less information; document those differences explicitly.

Immunity helpers are particularly sensitive to upstream changes. Soundproof, Bulletproof, Good as Gold, side-wide priority blockers, and dynamic targets can involve different paths. A check-only query also has a different role from a helper that starts a battle script. The [upgrade notes](../merge-upgrade-helper/references/upstream-upgrades.md) and [feature reference](../maintain-elastic-emerald-documentation/references/feature-reference.md) record related integration problems.

### Proactive Color Change

When attacking against a Color Change mon where the Color Change ability isn't negated, the AI will factor the type the Color Change mon would become when determining its moves.

## Adaptive Hidden Power

Hidden Power has fixed 60 base power and fails for any battle species whose base form is not Unown. `GetHiddenPowerType` scores all 18 ordinary types against the resolved target using the shared type-effectiveness and damage-modifier helpers. None, Mystery, and Stellar are excluded. Equal scores keep the first type in the type enum; no random roll or IV calculation is involved. The score includes STAB, weather, terrain, attacker type boosters and prospective Gems, and applicable revealed defensive abilities/items. It does not anticipate Proactive Color Change. Anticipation evaluates the same adaptive type when checking incoming Unown moves and ignores Hidden Power on species that cannot use it.

Unown’s Hidden Power receives a final damage multiplier of `(Sp. Atk + Attack / 4) / Sp. Atk`, using stored battle stats before stages and item/ability multipliers. Equal Attack and Special Attack give 1.25× damage (approximately 75 effective power); higher Attack relative to Special Attack increases the bonus. `ApplyModifiersAfterDmgRoll` applies the same calculation to actual damage and AI estimates, after the existing modifiers. Integer arithmetic preserves fractional `Attack / 4` until the final result and rounds half down. A minimum Special Attack of 1 protects the denominator. This type-independent bonus does not alter the adaptive type ranking.

`CANCELER_HIDDEN_POWER_TYPE` follows target selection and PP deduction, before primal-weather failure checks, Protean, and target failure/Color Change. It stores the final move type, reapplies Electrify if necessary, refreshes Gem eligibility, and runs the type-announcement script. Damage uses that stored type even after Color Change. Move menus retain the nominal Normal type because no execution target has been resolved.

`AiPartyMon.revealedAbility` and `revealedHoldEffect` are written only by the battle reveal-recording functions. They remain separate from AI knowledge, which can be populated by omniscience, and retain revealed information when a party member switches out and back. Scoring compares those records with the current effective ability/item so suppression and replaced effects are respected. The ability-reveal restriction applies to the user as well as other battlers; the user’s own held item is always available. AI damage/type calculations use their explicit target, reject non-Unown users, and avoid fixed-type absorber switches for Hidden Power because it reselects after switching.

The focused regressions live in `test/battle/move_effect/hidden_power.c` with the `Elastic-tests: ` prefix. Build and runtime test execution are separate from static review.

### Read-only damage display

`PutReadOnlyAiDamageText` keeps all three ability columns (54 pixels each, 52 usable) on one page. Multiword headings always prefer two rows, splitting at the last word boundary whose prefix fits; for example, `Good as` / `Gold`. Single-word names use one row when they fit. There is no legend; ability headings occupy y=0/12 below the icons. Move rows start at y=28 and advance by 24 pixels; move names wrap within 76 pixels. Both AI Dmg and Player Dmg display minimum normal damage–maximum possible critical damage (`min-maxCrit`), collapsing `0-0` to `0` through `FormatDisplayedDamageRange`. Critical blockers make the upper value the normal maximum instead. AI Dmg prefers `FONT_NARROW` where the string fits and uses `FONT_SMALL_NARROWER` for longer values. Player Dmg uses actual current abilities for both simulations and restores cached AI ability knowledge after each query. Keep the compact icons and all four rows inside the 240×128 window (screen y=32). `FONT_SMALL_NARROW` reports an 8-pixel maximum height but renders 12-pixel glyphs; `FONT_SMALL_NARROWER` renders 15-pixel glyphs. Use the rendered heights for layout. `AI_CalcDamageForDisplay` explicitly requests normal or possible-critical damage through the shared calculator; blocked critical hits retain normal damage. Ordinary `AI_CalcDamage` callers retain the existing guaranteed/risky critical policy. The display wrapper must restore battle and AI state after each query.

Focused read-only menu regressions live in `test/battle/battle_info.c`. The `TESTING`-only `Test_BattleInfoCalcAiDamage` entry point calls the production menu wrapper so tests cover temporary ability replacement and state restoration as well as roll calculations. These source tests do not verify rendered wrapping, colors, or icon cleanup.

The read-only damage window uses BG1 base tile `0x180`: its graphics occupy `0xB000..0xEBFF`, between BG1’s tilemap (`0xA000..0xA7FF`) and BG0’s options tilemap (`0xF800..0xFFFF`). A 30×16 window at the old base `0x200` reaches `0xFBFF` and corrupts the options tilemap, leaving a blank screen on return. Check complete VRAM byte ranges whenever enlarging windows; tile storage can overlap another BG’s tilemap even when the windows use different backgrounds. The focused VRAM regression reads the production window and BG templates.

Player Dmg and read-only AI Dmg keep BG1 and their newly created sprites hidden during initialization. After drawing and queuing window graphics/tilemap copies, wait for `IsDma3ManagerBusyWithBgCopy()` to clear before hiding BG0 and revealing BG1/sprites. Showing BG1 in setup state 0 exposes the previous table for a frame before state 1 replaces it. Input starts only after the reveal state.

### Trainer Tera eligibility

`GenerateMonFromTrainerMon` must store `TYPE_MYSTERY` when the trainer party entry omits `teraType`, regardless of `smartTera`. `ShouldTrainerBattlerUseGimmick` uses that sentinel to block Tera; generated/curated defaults are not permission. `GetMonData(MON_DATA_TERA_TYPE)` must preserve that sentinel ahead of species-forced types as well. Preserve explicit party types. The regression in `test/battle/trainer_control.c` covers Smart Tera without an explicit type.

### Suppressed general switch prediction

`SetupAIPredictionData` clears the modeled player's switch bit and does not call `ShouldSwitch`, `GetMostSuitableMonToSwitchInto`, or `ModifySwitchAfterMoveScoring`. The latter can independently create a switch prediction from bad move scores, so suppressing only `ShouldSwitch` is insufficient. Keep normal AI switching in `ComputeAiBattlerDecisions` intact. Retain the prediction flags and probability for `TryChooseImmunityPredictionSwitchin`, which establishes its own candidate and switch bit after observed-switch restrictions pass. Legacy general-prediction battle scenarios need expectations reflecting suppression if maintained; static review does not establish their runtime results.

### STAB and item knowledge flags

`GetDamageMoves` is the damage-only inference entry point for `AI_FLAG_ASSUME_STAB`. It copies `GetMovesArray` into a caller-owned array, then fills eligible hidden species-STAB attacks at their actual slots. Never record inferred attacks through `RecordKnownMove`: active and party history must remain independent of damage assumptions. Use this array for damage-cache population, survival/KO queries, and incoming switch damage; retain `GetMovesArray` for effect checks, move prediction, and knowledge completeness. Do not expose damage-only candidates through `GetBestDmgMovesFromBattler`, whose callers inspect effects.

Filter hidden attacks using `gBattleMoveEffects[effect].twoTurnEffect` and `MoveHasAdditionalEffectSelf(move, MOVE_EFFECT_RECHARGE)`. `CanAssumeTwoTurnMove` permits known effective Power Herb, applicable weather with modeled ability/item, or Tailwind for Razor Wind. Sky Drop cannot use Herb, and semi-invulnerable effects do not use weather. Revealed moves and move/full omniscience override these inference restrictions. Keep slot indexes aligned with damage caches and do not mutate shared move arrays during simulations.

`AI_FLAG_ELASTIC_KNOWLEDGE` combines STAB inference, weighted ability prediction, and item omniscience. Keep held-item knowledge flag-driven in `Ai_InitPartyStruct` and `AI_DecideHoldEffectForTurn`; retain item revelation hooks for trainers without omniscience and for mechanics that explicitly require revealed effects.
