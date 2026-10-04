# Elastic Emerald development notes

I keep these notes as a reference for maintaining Elastic Emerald.

- [Feature reference](feature-reference.md): high-level current functionality and new bugfixes, with useful source anchors. Update the affected feature when behavior changes; keep commit specifications, release chronology, and historical test/build reports in the history.
- [Feature history](../feature-history.md): implementation commits and their specifications, including commits that repair breaking behavior. Record the cause and resulting repair when known. Use **Newest — uncommitted** for pending working-tree changes, then replace it with the actual commit ID after committing. Committed recent changes always retain their commit IDs.
- [Gameplay reference](../gameplay/README.md): player-facing rules.

When adding functionality or fixing a bug, update the feature reference's current behavior and the feature history's commit or pending entry as appropriate. Do not treat historical verification results as validation of the current working tree. Detailed source/API maintenance procedures belong in the topic guides below.

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
