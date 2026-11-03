# Elastic Emerald agent instructions

“Make suggestions” means report suggestions without editing code. Preserve unrelated working changes.

Use static verification. Do not run ROM builds, test builds, or broad build checks unless explicitly asked. Targeted source generation is allowed when needed for an edit. State verification limits accurately.

When adding or modifying tests because of code changes, use the `Elastic-tests: ` prefix.

## Repository skills

Read and follow the matching repository skill before acting, and announce its use. Paths are relative to the repository root. Load multiple skills when the work crosses their boundaries.

| Work | Skill |
| --- | --- |
| Battle-AI scoring, targeting, switching, knowledge, simulation, trainer items, doubles, or matching AI support for mechanics | [modify-elastic-emerald-ai-logic](skills/modify-elastic-emerald-ai-logic/SKILL.md) |
| NPCs, dialogue-informed party suggestions, map objects/scripts, trainers, route bosses, rewards, progression gates, or scaling | [modify-elastic-emerald-npcs](skills/modify-elastic-emerald-npcs/SKILL.md) |
| Encounter availability audits, progression policy, encounter row mappings, or encounter spreadsheet automation | [manage-elastic-emerald-encounters](skills/manage-elastic-emerald-encounters/SKILL.md) |
| Source-linked item acquisition rows, generic tags, mappings, or authored spreadsheet presentation | [manage-elastic-emerald-item-acquisition](skills/manage-elastic-emerald-item-acquisition/SKILL.md) |
| Tier Points/MaxTierPoints documentation audits, discrepancies, or selective synchronization | [manage-elastic-emerald-tier-points](skills/manage-elastic-emerald-tier-points/SKILL.md) |
| Upstream conflicts, version upgrades, stale APIs, post-merge failures, or merge regression audits | [merge-upgrade-helper](skills/merge-upgrade-helper/SKILL.md) |
| Feature/history maintenance or agent documentation structure | [maintain-elastic-emerald-documentation](skills/maintain-elastic-emerald-documentation/SKILL.md) |

These repo-local paths are the maintained project skills. Select them through this file even when the client does not automatically discover the `skills/` directory. For upgrade work involving AI, apply both the merge and AI skills.

## Documentation ownership and maintenance

The developer owns the documents in `docs/`, especially authored gameplay rules and design prose. Do not directly rewrite, reorganize, or expand authored prose through LLM edits without explicit instruction. Focused corrections to existing technical documentation that directly accompany a requested code change are appropriate, such as updating `docs/tutorials/ai_flags.md` when an AI flag's behavior changes. Keep such edits narrow and factual, preserving the author's style and unrelated content. This exception does not authorize new LLM-written summaries, histories, or working analyses in `docs/`. Designated source-driven tooling such as `sync_trainer_docs.py` may update its generated sections as part of relevant authorized source changes without a separate documentation request. Preserve the tooling’s defined scope and manual prose; this allowance does not authorize direct LLM rewrites or changes to templates merely to bypass the prose policy.

Agent routing and task procedures belong in `AGENTS.md` and `skills/*/SKILL.md`. Reusable agent knowledge, feature references, behavior summaries, and maintenance history belong in the relevant skill's `references/` directory. Task-specific working analyses and outstanding audit reports belong in `analysis/`, with their review baseline and limitations recorded; link them from the relevant skill when useful, and recheck their findings before treating them as current. Link shared material instead of duplicating it. Keep authored design documents in `docs/`; do not infer permission to relocate them merely because an agent has edited them before.

After changes, update the appropriate repository skill or its supporting references with changed technical contracts or useful maintenance lessons. For bugfixes, also update `skills/maintain-elastic-emerald-documentation/references/change-history.md`; keep outcomes brief. Change `skills/maintain-elastic-emerald-documentation/references/feature-reference.md` only when a described functional rule changes, rather than adding repair narratives or test inventories. Record actual commit IDs when known and identify pending work as uncommitted.

When battle-AI behavior changes, update `skills/modify-elastic-emerald-ai-logic/references/behavior-summary.md` in the same work. Before changing its documentation status, inspect the relevant diff and history. Replace previously documented uncommitted markers with actual commits when available, and advance the last-documented commit only through applicable AI changes actually reviewed.

## Source ownership

Edit map objects in `map.json`, map scripts in `scripts.pory`, parties in `src/data/trainers.party`, and teachable compatibility in `src/data/pokemon/all_learnables.json`. Regenerate affected derived files with the current targeted generator.

In function-style Poryscript, argument-bearing commands use call syntax, for example `setflag(FLAG_NAME)`. Map local-ID names enter a global header; use map-specific names. Static overworld Pokémon support `OBJ_EVENT_GFX_SPECIES(NAME)`. Check normal land encounter slots before selecting ambient species; later slots may be Monotype-specific.
