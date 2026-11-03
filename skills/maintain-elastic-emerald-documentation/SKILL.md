---
name: maintain-elastic-emerald-documentation
description: Maintain Elastic Emerald feature references, feature history, AI documentation status, and repository skill organization. Use for cross-topic documentation maintenance or reorganizing agent guidance; use the topic skills for system-specific workflows.
---

# Maintain Elastic Emerald Documentation

Read `AGENTS.md` and use its topic routing. The developer owns `docs/`. Preserve authored gameplay and design prose against direct LLM edits unless explicitly instructed. Designated source-driven documentation tools may refresh their generated sections as part of relevant authorized source changes; preserve manual prose and the tool’s defined scope. Narrow, factual updates to existing technical documentation directly affected by requested code changes are appropriate; updating `docs/tutorials/ai_flags.md` with changed flag behavior is one example. New agent summaries and history belong in `skills/`; task-specific working analyses belong in `analysis/`.

## Documentation ownership

- Maintain [the feature reference](references/feature-reference.md) as concise descriptions of current functional features and player-visible rules. Update existing descriptions only when functional behavior changes. Do not add standalone bugfixes, repair narratives, commit histories, or test inventories.
- Maintain [feature history](references/feature-history.md) as brief outcomes of additions, changes, and repairs. Use real commit IDs or explicitly pending/uncommitted labels until the commit is known.
- Treat [gameplay documentation](../../docs/gameplay/README.md) as developer-owned design context. Report discrepancies without editing it unless instructed. Maintain [the AI summary](../modify-elastic-emerald-ai-logic/references/behavior-summary.md) as agent reference material with accurate documentation status.
- Keep working audit reports such as the [Tier Points discrepancy analysis](../../analysis/tier-points-discrepancy-analysis.md) in `analysis/` and link them from the matching skill. Keep reusable procedures and established technical contracts in skill references. Preserve authored gameplay documents and inherited upstream manuals in `docs/`. When relocating references, preserve pending changes, rebase relative links, update skill routing and consumers, and remove moved entries from the mdBook index.
- For bugfixes, update history and the relevant topic skill or supporting reference. Restoring expected behavior does not warrant a new feature entry. Keep actionable merge-breakage lessons in the [upgrade reference](../merge-upgrade-helper/references/upstream-upgrades.md). Do not create verbose feature archives.

## Topic guidance

Use the topic skills routed by `AGENTS.md`. Fold new task procedures and technical contracts into the relevant skill or its supporting references. Write skill instructions as direct guidance and references as neutral factual descriptions. Avoid first-person narration or wording that implies the agent authored the developer’s design. Preserve attribution when it identifies actual design ownership. Link shared material rather than maintaining duplicate copies. Read only the references needed for the task.

Preserve current guidance on matchup commitment, adaptive Hidden Power, Unown IV guarantees, and Expansion 1.17.1 integration when reorganizing files. Historical skill text is not authority for superseded behavior.

The [source-backed documentation helpers](../../tools/elastic_emerald_helpers/README.md) and [learnset tools](../../tools/learnset_helpers/README.md) retain their usage documentation alongside the tools.

## Verification

Check changed links, source references, skill metadata, and diffs. Use static verification; ROM and test builds require an explicit request. The project test prefix is `Elastic-tests: `. State what remains unverified.
