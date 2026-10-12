# Elastic Emerald development notes

I keep these notes as a reference for maintaining Elastic Emerald.

- [Feature reference](feature-reference.md): concise descriptions of current functional features and player-visible rules. Do not add standalone bugfixes, repair explanations, commit history, or implementation details. Update an existing description only when its functional behavior changes.
- [Feature history](../feature-history.md): brief descriptions of additions, changes, and repairs, with commit IDs or the pending **Newest** label. Describe the outcome; retain technical details in topic guides only when they help future maintenance.
- [Gameplay reference](../gameplay/README.md): player-facing rules.

For a bugfix, update the history and the relevant developer topic guide. Update the feature reference only if the fix changes a described functional rule; restoring expected behavior does not warrant a new feature entry. Keep both overview documents descriptive and concise. Do not create archives for verbose feature accounts or test inventories. Preserve actionable merge-breakage guidance in the existing upgrade notes.

## Topics

- [Battle AI](battle-ai.md) and the [AI behavior summary](../custom_ai_logic_summary.md)
- [NPCs, trainers, map scripts, and route bosses](npcs-and-trainers.md)
- [Encounter documentation](encounters.md)
- [Item acquisition documentation](item-acquisition.md)
- [Tier Points documentation](tier-points.md)
- [Upstream upgrades](upstream-upgrades.md), [merge decisions](resolution-policy.md), [API migration notes](stale-api-map.md), and [static checks](check-recipes.md)
- [Source-backed documentation and analysis tools](../../tools/elastic_emerald_helpers/README.md)
- [Learnset analysis tools](../../tools/learnset_helpers/README.md)

## My development conventions

I normally use static checks during review and handle full ROM and test builds separately because of their cost. Diff checks, caller searches, documentation links, and targeted script generation answer narrower questions; they do not establish runtime correctness.

My project-specific tests use the `Elastic-tests: ` prefix to distinguish them from Expansion tests. The tests and deterministic helper scripts remain part of my development tools.

The editable inputs are map objects in `map.json`, native scripts in `scripts.pory`, trainer parties in `src/data/trainers.party`, and teachable compatibility in `src/data/pokemon/all_learnables.json`. Their generated outputs follow those inputs. Argument-bearing commands in function-style Poryscript use call syntax, such as `setflag(FLAG_NAME)`.

I use map-specific local IDs because named map IDs enter a global header. Static overworld Pokémon support `OBJ_EVENT_GFX_SPECIES(NAME)`. The first eight normal land encounter slots are the starting point for ambient species choices; later slots may be Monotype-specific.

I record meaningful feature additions, redesigns, and removals alongside their actual commits. Pending work stays labeled as uncommitted until I can identify its commit. This distinction is especially useful during upgrades, when an old patch may describe behavior I have since replaced.
