---
name: merge-upgrade-helper
description: Resolve codebase merge conflicts, post-merge build errors, and functionality regressions during upstream version upgrades. Use when Codex is asked to fix conflicted files, clean stale adjacent code after a merge, adapt local custom logic to newer upstream APIs, audit whether designed behavior broke after an upgrade, handle generated/deleted files in a merge, investigate merge-related compiler/assembler errors, or reduce repeated rediscovery during large upgrade merges.
---

# Merge Upgrade Helper

## Core Workflow

1. Start with repository guidance. Read `AGENTS.md` and obey project-specific validation limits, especially build restrictions.
2. Inventory conflicts with `git diff --name-only --diff-filter=U` and marker scans.
3. Resolve structurally first: remove duplicate enum entries, duplicate struct fields, broken brace scopes, duplicated `case` labels, and generated-file conflicts.
4. Preserve local behavior while adopting current upstream APIs and data shapes.
5. Sweep stale adjacent code after each file, not only conflict hunks.
6. Audit custom functionality that survived the merge syntactically but may have lost runtime hooks or AI mirrors.
7. Maintain the project merge dossier while findings are fresh. Add any newly discovered custom behavior, post-upgrade repair, API adaptation, or reusable conflict insight that is not already covered. Do not defer all documentation until the end of a large merge.
8. Update the dossier's documentation-status record after checking the relevant diff and history. Advance the latest documented commit only through commits whose applicable changes have actually been reviewed; identify current applicable work as uncommitted until it receives a real commit.
9. Run static checks before staging. Avoid full builds unless explicitly requested by the user.
10. Stage only after markers and static checks are clean, if staging is requested or appropriate for the merge workflow.

When the user explicitly requests builds, continue through compilation, assembly, linking, and ROM generation; a clean C compile is not a clean build. After the first successful full build, run an incremental confirmation build to catch unstable generated dependencies.

Prefer `rg` for discovery. Use `git diff --check`, targeted stale-token scans, and file-level compiler front-end checks when useful.

## References

Load only what is needed:

- `references/check-recipes.md`: command patterns for conflict inventory, static checks, stale scans, and targeted C compiler checks.
- `references/stale-api-map.md`: common upgrade mappings for pokeemerald-expansion-style battle/AI merges.
- `references/resolution-policy.md`: file-specific resolution rules and merge decision heuristics.

Also load `docs/merge-upgrade-helper/README.md` before functionality regression audits or when conflicts touch local gameplay systems. It summarizes `zenmodeman`-authored mode, tier-point, monotype, Tera, AI, battle-mechanic, content, and QOL behavior that must survive upstream merges. Treat this dossier as a maintained output of the workflow: update it whenever the work uncovers previously undocumented implementation changes or conflict-resolution knowledge.

## Dossier Maintenance

For projects with a merge dossier such as `docs/merge-upgrade-helper/README.md`:

- Read its documentation-status section before beginning the audit. Use the recorded commit as the lower history boundary, while still inspecting older code when a conflict or regression points there.
- Compare the recorded commit with `HEAD`, the relevant commit range, and the working-tree diff. Do not assume that a recent README commit means all code through that commit was reviewed.
- Document new project behavior and new conflict insights in the appropriate durable section. Capture why a resolution is required, the current API/data contract, and the stale pattern future passes should search for.
- Avoid duplicate ledger entries. Extend or correct an existing entry when it already describes the same system or regression.
- Keep two states distinct: the latest real commit fully reviewed and documented, and applicable uncommitted changes reviewed during the current pass.
- When previously documented uncommitted work is later committed, replace the uncommitted marker with the real commit and advance the latest documented commit only if no intervening applicable changes remain unreviewed.
- Before finishing, re-read the status section, inspect `git status`, the dossier diff, and recent history, then leave the status accurate even when no code changes were necessary.

## Conflict Heuristics

- Treat duplicate enum members and duplicate struct fields as merge residue unless both sides intentionally introduced separate names.
- Treat parser cascades like “expected identifier before do/while” as likely broken brace/switch structure from interleaved conflict sides.
- Prefer current upstream helpers over local reimplementations when the helper now exists.
- Keep custom scoring/gameplay logic only if it still compiles against current APIs and does not duplicate newer upstream behavior.
- For generated files, prefer the current generator source and stage deletion of generated outputs when the repo now ignores/regenerates them.
- Treat linker clusters of undefined custom symbols as evidence that a rewritten core file retained callers/prototypes but lost implementation bodies. Recover the real implementations and their shared state; do not satisfy the linker with behaviorless stubs.
- Treat newly unused custom helpers as possible severed runtime hooks. Trace why the helper became unused before deleting or suppressing it.
- When upstream heavily rewrites a large core file, a focused project-owned compatibility module can reduce future conflict surface, provided it contains coherent existing behavior and uses current public APIs.

## Functionality Regression Audits

Use this pass after the build is clean or when the user asks whether designed behavior broke during the upgrade.

- Start by reading `docs/merge-upgrade-helper/README.md` and use its system checklists as the audit spine.
- Treat documented project-specific intent in the dossier as authoritative for false-positive filtering. For example, Elastic Emerald intentionally aliases Tera Orb charged/no-cost flags so Tera has no charge cost.
- Start from local custom symbols and systems, not only changed files: custom abilities, moves, species stat conditionals, resource/restricted modes, tier/scoring logic, bespoke AI prediction, menu flows, scripts, and config-gated behavior.
- Trace each custom behavior through data declaration, public constants/prototypes, runtime implementation, battle scripts, UI/menu access, save/var/flag usage, and AI prediction. A behavior is suspicious when only data or AI references remain but the runtime hook is missing.
- For enum-driven custom conditions, compile with exhaustive-switch warnings and verify every local enum member still has a runtime case. Missing cases can silently disable data-defined gameplay even when the data compiles.
- Compare AI helper logic against the runtime helper it is modeling. If a custom ability/item/move blocks or enables an effect in AI, verify the corresponding battle-util or script path enforces the same behavior.
- Search for semantically wrong boolean rewrites after conflict resolution, especially helper calls whose arguments became boolean expressions, temporary state saved/restored from different battler indexes, duplicated negations, and stale side indexes in switch prediction.
- For conditional species stats, keep shared macros near the family that uses them and scan for all-caps stat identifiers referenced before definition or replaced by raw values on only one side of the condition.
- Prefer targeted static checks and `rg` confirmation over broad builds: scan for conflict markers, stale API tokens, unresolved custom symbols, suspicious helper-call argument shapes, and paired runtime/AI occurrences.

## Reporting

In the final response, state:

- which files were changed,
- which stale constructions were updated,
- what static checks were run,
- how the merge dossier and its latest-documented-commit status were updated (or why no update was needed),
- whether files were staged,
- whether a build was intentionally skipped.
