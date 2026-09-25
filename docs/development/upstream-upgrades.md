# Upstream upgrade notes

I use the [custom feature reference](feature-reference.md) to locate local behavior and the [feature history](../feature-history.md) to distinguish introductions, redesigns, and repairs. The historical test results describe earlier runs; they are not a current validation result.

## How I approach a merge

The working diff, merge parents, and unmerged paths establish what is changing. Structural problems—duplicate enums, fields, cases, or interleaved braces—often need attention before a semantic comparison is possible.

My aim is to retain the current Elastic Emerald behavior on the newer upstream APIs and data layouts. Later local commits matter: restoring an older implementation can accidentally undo an intentional redesign. Adjacent code also matters, because stale callers and generated inputs can sit outside the conflict hunk.

I trace a feature through its constants/data, runtime dispatch, scripts, UI, save state, and AI simulation. A declaration or surviving test does not establish that its runtime caller survived. Non-obvious resolutions go into the feature reference with their reasoning and API contract.

Routine review uses [static checks](check-recipes.md). Full builds and test runs are separate decisions. When I do build, compilation, linking, and ROM generation are distinct milestones; an incremental follow-up can expose unstable generated dependencies.

## Recurring failure patterns

- Undefined custom symbols can mean that a rewritten core retained callers but lost implementations or shared state. Empty stubs would hide that loss.
- A newly unused helper can indicate a severed runtime hook rather than obsolete behavior.
- A coherent project-owned compatibility module can reduce conflict surface in a frequently rewritten upstream file.
- Numeric collisions can survive a clean textual merge, particularly in battle-type bits, trainer modes, flags, and palette ranges.
- Generated outputs follow their source and current generator; an output deleted or ignored by upstream may no longer belong in the repository.
- Boolean rewrites can change helper arguments, invert a condition, or save and restore different battler indexes.
- Conditional species-stat macros can disappear from one branch or move below their users.
- A missing dispatch case can disable a configuration-gated mechanic even when its data still compiles.

## Battle AI parity

The [battle AI notes](battle-ai.md) cover simulation and scoring. I compare the model with runtime ability suppression, immunity, dynamic targets, item negation, and check-only versus script-running calls, while retaining intentional knowledge limits.

Some apparent anomalies are deliberate. Tera Orb charged/no-cost flags share an alias because charging has no cost. The old clean-state and weather-preservation switching paths are also historical; matchup commitment superseded them.

## Documentation coverage

I distinguish original feature commits, redesigns, and regression repairs. The documented boundary advances with reviewed changes, not merely because a newer documentation commit exists. Pending work and unresolved questions remain explicit, as do the checks actually performed.
