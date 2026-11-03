---
name: maintain-elastic-emerald-documentation
description: Maintain Elastic Emerald feature references, feature history, AI documentation status, and repository skill organization. Use for cross-topic documentation maintenance or reorganizing agent guidance; use the topic skills for system-specific workflows.
---

# Maintain Elastic Emerald Documentation

Read `AGENTS.md` and use its topic routing. Agent instructions, technical maintenance notes, and task workflows belong in `skills/`; human-facing gameplay rules, the AI behavior summary, and feature history remain in `docs/`.

## Documentation ownership

- Maintain [the feature reference](references/feature-reference.md) as concise descriptions of current functional features and player-visible rules. Update existing descriptions only when functional behavior changes. Do not add standalone bugfixes, repair narratives, commit histories, or test inventories.
- Maintain [feature history](../../docs/feature-history.md) as brief outcomes of additions, changes, and repairs. Use real commit IDs or explicitly pending/uncommitted labels until the commit is known.
- Preserve [gameplay documentation](../../docs/gameplay/README.md) as player-facing rules and [the AI summary](../../docs/custom_ai_logic_summary.md) as current AI behavior with accurate documentation status.
- For bugfixes, update history and the relevant topic skill or supporting reference. Restoring expected behavior does not warrant a new feature entry. Keep actionable merge-breakage lessons in the [upgrade reference](../merge-upgrade-helper/references/upstream-upgrades.md). Do not create verbose feature archives.

## Topic guidance

Use the six system skills routed by `AGENTS.md`. Fold new task procedures and technical contracts into the relevant skill or its supporting references. Link shared material rather than maintaining duplicate copies. Read only the references needed for the task.

Preserve current guidance on matchup commitment, adaptive Hidden Power, Unown IV guarantees, and Expansion 1.17.1 integration when reorganizing files. Historical skill text is not authority for superseded behavior.

The [source-backed documentation helpers](../../tools/elastic_emerald_helpers/README.md) and [learnset tools](../../tools/learnset_helpers/README.md) retain their usage documentation alongside the tools.

## Verification

Check changed links, source references, skill metadata, and diffs. Use static verification; ROM and test builds require an explicit request. The project test prefix is `Elastic-tests: `. State what remains unverified.
