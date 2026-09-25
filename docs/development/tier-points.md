# Tier Points documentation notes

I maintain `docs/gameplay/tier-points.md` through individual editorial changes. Its regional lists, fully evolved/not fully evolved groupings, and varied wording reflect how I organize the design. I do not treat it as a schema for generated replacement prose.

## Implementation and intent

A document edit can describe an intended change before the code implements it. I distinguish that situation from an inaccurate description of existing behavior by comparing the document, working diff, and source. Empty ability headings remain placeholders; they do not establish a point schedule. A Tera exception also does not necessarily change ordinary Tier Points.

Synchronizing prose to source and changing gameplay to match an intended rule are different decisions. My discrepancy notes keep unresolved design choices separate from factual mismatches.

## Source map

| Source | Role |
| --- | --- |
| `src/elastic_emerald_pokemon.c` | `GetMonTierPoints`, `GetSpeciesAbilityTierPoints`, form normalization, badge/ability branches, eggs/default cost, MaxTierPoints traversal, teaching predicates, party totals and projections |
| `include/pokemon.h` | Party cap and separate teaching thresholds |
| `src/data/pokemon/species_info/`, evolution and form-change tables | Ability slots, evolution endpoints, and distinct forms; exact table locations can change upstream |
| `src/party_menu.c`, `src/move_center_tutor.c`, `src/move_relearner.c`, `src/chooseboxmon.c`, `src/pokemon.c` | Teaching callers, resource costs/refunds, boxed compatibility, and ability changes |
| `src/battle_terastal.c` | Runtime Tera eligibility |
| `src/pokemon_storage_system.c`, `src/evolution_scene.c`, `src/egg_hatch.c`, `src/battle_script_commands.c` | PC, evolution, hatch, and capture enforcement |

Runtime item/ability handling supplies mode-specific details. The [battle AI notes](battle-ai.md) cover cases that also affect simulation or decisions.

## Comparing a rule with source

For each entry, I identify the species/form, ability, mode, and badge transitions in the executable branches. The implementation tests individual badge flags; interpreting them as a badge count assumes normal ordered progression. Values immediately before and at a threshold are useful distinctions.

Ordinary Tier Points and MaxTierPoints answer different questions. MaxTierPoints considers the current-mon floor, terminal evolutions, terminal Megas, nonempty ability slots, and current progression, with the Nincada-to-Shedinja branch excluded. Evolution requirements do not gate that search. Teaching implications also depend on the callers.

A conditional entry may appear in both an ability section and an unqualified “Always” list. I compare those occurrences together. Names such as Mega Charizard Y, regional forms, punctuation variants, and collective names such as Sinistcha sometimes need manual interpretation. A base-species case covers other forms only where the code normalizes or aliases them.

A broad comparison runs in both directions: documented values against source and explicit source cases against document coverage. I distinguish wrong conditions, missing entries, internal contradictions, and placeholders. This still does not establish coverage of every available species; default cost alone says nothing about encounter availability. Availability depends on the encounter and progression references.

## Discrepancy notes

`docs/tier-points-discrepancy-analysis.md` holds outstanding findings separately from player-facing prose. A useful finding records the document claim, implemented behavior, source symbol, and the remaining correction or design question, including any uncommitted baseline.

When I resolve a finding, I remove it after comparing the relevant source and document occurrences. The report is an outstanding-work list rather than a resolution history. A partial fix leaves the remaining contradiction or uncertainty visible.

For documentation changes, I review the prose, source references, and diff without a game build. The scope of that review remains separate from runtime verification.
