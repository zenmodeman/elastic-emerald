---
name: merge-upgrade-helper
description: Resolve codebase merge conflicts, post-merge build errors, and functionality regressions during upstream version upgrades. Use when Codex is asked to fix conflicted files, clean stale adjacent code after a merge, adapt local custom logic to newer upstream APIs, audit whether designed behavior broke after an upgrade, handle generated/deleted files in a merge, investigate merge-related compiler/assembler errors, or reduce repeated rediscovery during large upgrade merges.
---

# Merge Upgrade Helper

Read `AGENTS.md` first. Preserve current Elastic Emerald behavior while adapting to current upstream APIs and generated-file conventions.

## References

- Read `skills/merge-upgrade-helper/references/upstream-upgrades.md` for recurring breakage, source paths, and Expansion 1.17.1 integration lessons.
- Read `skills/merge-upgrade-helper/references/resolution-policy.md` for conflict decisions.
- Use `skills/merge-upgrade-helper/references/stale-api-map.md` when migrating callers; compare every mapping with current declarations.
- Use `skills/merge-upgrade-helper/references/check-recipes.md` for targeted static checks.
- Use `skills/maintain-elastic-emerald-documentation/references/feature-reference.md` for current behavior and `docs/feature-history.md` for introductions, redesigns, and repairs.

## Workflow

1. Inspect the working diff, merge parents, unmerged paths, and relevant later local commits. Resolve duplicate fields/enums/cases and broken scopes before semantic review.
2. Retain local game design while adopting upstream APIs. Trace adjacent callers and generated inputs, including files outside conflict hunks. A lost custom implementation needs recovery, not an empty linker stub.
3. Audit affected features through data, runtime dispatch, scripts, UI, save state, and AI. Surviving declarations or tests do not establish a working runtime path. Treat newly unused helpers as possible lost hooks. Check numeric namespaces for collisions.
4. For AI changes, also load `skills/modify-elastic-emerald-ai-logic/SKILL.md`. Preserve current matchup commitment rather than restoring historical switching heuristics.
5. Use conflict scans, stale-symbol/caller searches, and diff checks. Run builds or test builds only when explicitly requested. If requested, distinguish compilation, assembly, linking, ROM generation, and runtime testing in the results.
6. Record actionable repair/API lessons in the relevant topic skill or upgrade references. Keep feature history concise and commit references accurate; label uncommitted work explicitly. Update feature descriptions only when functional rules change.

Report changed files, verification and its limits, outstanding issues, and whether anything was staged.
