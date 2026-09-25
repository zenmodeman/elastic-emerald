# Battle AI development notes

My [AI behavior summary](../custom_ai_logic_summary.md) contains info about AI logic.

## Information and comparisons

I distinguish actual, revealed, inferred, predicted, and omniscient information. A simulation can be numerically accurate yet make the AI unfair if it obtains a hidden move or ability outside the intended knowledge policy.

Comparisons across alternate states concern the same move or switch candidate. Combining the best result from one candidate with a condition satisfied only by another can produce a decision that neither candidate supports. Similarly, inferred and revealed move arrays can have different indexes, so an exact-move recalculation is sometimes necessary instead of reusing a damage-cache slot.

Effective Speed includes stages, abilities, items, status, weather, and field effects. Whether priority and Trick Room belong in a comparison depends on whether I am modeling raw Speed or actual turn order. For lead identity, party slot and switch-in history carry more information than a first-turn flag.

I favor evidence-based exceptions. Depleted PP, for example, supports an inference that a self-debuffing move was attempted; merely knowing the move does not. Hypothetical calculations retain real state such as active Tera and item changes unless that particular calculation is intended to remove it.

## Temporary battle state

The simulation helpers share mutable state with the battle engine. The relevant state commonly includes:

- `gBattleMons`: stages, types, ability, item, PP, and volatiles;
- `gDisableStructs` and other per-battler transient structures;
- field, side, weather, and gimmick state;
- `gAiLogicData`: modeled abilities/items, hold effects, Speed caches, and calculation flags;
- dynamic move type/category globals and prediction state.

I think of a simulation as a snapshot, a temporary calculation, and a restoration. Restoration includes the caller's previous flags, even when they were already enabled. A single restoration path makes this easier to reason about than several early returns.

Historical clean-state experiments distinguished temporary type changes, immunity bypass, grounding, ability replacement/suppression, and externally caused defensive or Speed drops from the underlying matchup. Self-caused drops could remain when battle evidence supported them. Those experiments also required actual-state validity: a hypothetical KO alone was insufficient.

Generalized clean-state switching and the later weather-setter preservation heuristic are now historical. The current fast-KO path uses [matchup commitment](../custom_ai_logic_summary.md#matchup-commitment-for-fast-ko-switching), introduced in `53239d220d` and refined in `9c4b986496` and `c753e34660`. I use that history to distinguish intentional redesigns from merge losses.

## Runtime and simulation parity

Runtime behavior is the reference for type resolution, ability suppression, item negation, grounding, status immunity, move properties, and generation/configuration gates. Differences in the AI model are sometimes intentional because the AI has less information; I document those differences explicitly.

Immunity helpers are particularly sensitive to upstream changes. Soundproof, Bulletproof, Good as Gold, side-wide priority blockers, and dynamic targets can involve different paths. A check-only query also has a different role from a helper that starts a battle script. The [upgrade notes](upstream-upgrades.md) and [feature reference](feature-reference.md) record related integration problems.


