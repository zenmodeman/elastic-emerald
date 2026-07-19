---
name: modify-elastic-emerald-ai-logic
description: Implement, diagnose, review, or document battle-AI behavior in Elastic Emerald. Use for changes involving move scoring, target choice, switching, inferred or revealed information, damage and speed simulation, temporary battle-state mutation, AI knowledge, trainer items, doubles coordination, Terastalization decisions, or AI tests; also use when a gameplay mechanic needs a matching AI model or an AI regression must be checked after nearby code changes.
---

# Modify Elastic Emerald AI Logic

## Core workflow

1. Read the repository `AGENTS.md` and obey its build and test restrictions.
2. Read `docs/custom_ai_logic_summary.md`, including its documentation status, before changing behavior.
3. Inspect `git status`, the relevant diff, and recent history. Preserve unrelated user changes.
4. Trace the complete decision path before editing: information acquisition, cached data, simulation, score or switch gate, candidate selection, and final action.
5. State the intended information policy in code: distinguish actual, revealed, inferred, predicted, and omniscient data.
6. Implement the smallest coherent behavior change and restore every temporarily mutated state carrier.
7. Run targeted static checks only unless the user explicitly requests a build. Update AI documentation in the same work.

Before restoring older AI logic during an upgrade, check whether a newer commit deliberately removed or superseded it. Preserve the current design decision rather than reviving an abandoned heuristic merely because its old symbols still appear in history or tests. In particular, generalized clean-state/fast-KO switching is historical in this project; current weather-setter preservation is the active replacement.

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

For upgrade or merge work that touches AI, load `skills/merge-upgrade-helper/SKILL.md` first and read `docs/merge-upgrade-helper/README.md`. Then apply this skill to verify that the resolved code still represents the intended AI behavior.

## Verification and documentation

- Use `rg` to confirm callers, state fields, move-effect coverage, and stale logic.
- Run `git diff --check` and inspect the complete diff. Do not run a full build unless explicitly requested.
- Name new tests with the `Zenmodeman: ` prefix. Prefer tests that distinguish actual versus hypothetical state and verify restoration after simulation.
- Update `docs/custom_ai_logic_summary.md` with the behavior and key commits.
- If AI changes are uncommitted, list them as uncommitted in the summary. On later documentation edits, reconcile that marker with `git log` and the relevant committed diff before advancing the last-documented commit.
