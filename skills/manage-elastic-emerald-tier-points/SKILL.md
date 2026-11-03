---
name: manage-elastic-emerald-tier-points
description: Review and selectively sync Elastic Emerald's tier-points.md against implemented species costs, progression, abilities, modes, and MaxTierPoints rules while preserving its custom prose. Use for tier-point documentation audits and requested updates, not general battle-AI or encounter work.
---

Read `AGENTS.md` for repository conventions. Maintain this skill’s technical guidance when changes affect it.


# Tier points documentation

Maintain `docs/gameplay/tier-points.md` through case-by-case editorial review. Its inconsistent phrasing, regional lists, and fully evolved/not fully evolved groupings are intentional authoring context, not a schema to normalize. Do not introduce a generated replacement, spreadsheet pipeline, or permanent prose parser for this workflow.

## Scope and editing decisions

- Read the current document, `git status`, and relevant source/document diffs first. Uncommitted document statements may express intended changes that source does not yet implement. Preserve existing edits and distinguish current implementation from design intent.
- For an analysis request, report discrepancies with source evidence and suggested resolutions; leave the gameplay document and code intact. For a requested sync to source, make narrow documentation edits in the existing style. Do not change gameplay to make the document true unless implementation was requested.
- If the requested direction is clear, proceed. If a discrepancy leaves an actual design decision unresolved, isolate it and continue independent work; ask only for the decision needed to resolve that case.
- Empty ability headings are placeholders, not specifications. Do not invent affected species or point schedules from an ability's reputation. Do not assume a Tera exception also changes ordinary points.

## Source map

- `src/elastic_emerald_pokemon.c`: `GetMonTierPoints`, `GetSpeciesAbilityTierPoints`, species/form normalization, ability branches, badge flags, default cost, eggs; MaxTierPoints terminal-evolution/Mega traversal and teaching predicates; party totals and excess checks.
- `include/pokemon.h`: cap and separate teaching thresholds.
- `src/data/pokemon/species_info/`, `src/data/pokemon/evolution.h`, and `src/data/pokemon/form_change_tables.h`: follow actual species accessors and tables as needed to establish ability slots, evolution endpoints, and distinct forms. Locate moved tables with `rg` rather than trusting a stale path.
- `src/party_menu.c`, `src/move_center_tutor.c`, `src/move_relearner.c`, `src/chooseboxmon.c`, and `src/pokemon.c`: teaching callers, resource depletion/reimbursement, boxed compatibility, and ability-change restrictions.
- `src/battle_terastal.c`: runtime Tera eligibility. Trace runtime item/ability handling when a mode-specific explanation needs verification; load the AI skill only if reviewing or changing AI behavior too.
- `src/pokemon_storage_system.c`, `src/evolution_scene.c`, `src/egg_hatch.c`, and capture code in `src/battle_script_commands.c`: cap enforcement details when relevant.

## Comparison method

Read executable branches rather than inferring behavior from comments or section labels. For each requested entry, identify the exact species/form, applicable ability, mode, and badge transitions. Check before and at each threshold; the code tests individual badge flags, which correspond to counts only under normal ordered progression.

Distinguish ordinary cost from MaxTierPoints: current-mon floor, terminal evolutions, terminal Megas, nonempty ability slots, current progression, and the excluded Nincada-to-Shedinja branch all matter. Evolution requirements do not gate that search. Check the callers before generalizing teaching benefits or restrictions.

Search all document occurrences before updating a conditional entry. An ability subsection and an unqualified “Always” list can contradict each other. Resolve names manually where needed (Mega Charizard Y, punctuation, regional forms, or collective names such as Sinistcha); do not treat spelling differences as missing species. A base-species case does not automatically cover other forms unless the code normalizes or aliases them.

For broad audits, compare both directions: documented costs against source and explicit source cases against document coverage. Separate wrong values/conditions, missing entries, internal contradictions, and unspecified placeholders. State coverage limits: an explicit-case comparison is not proof that every available species or form is documented. Default cost is not evidence of encounter availability. Availability and post-game claims require encounter/progression evidence and the applicable project skills if investigated.

## Findings and verification

Give each finding the document location, observed claim, implemented behavior, source path and symbol (line links when useful), and a proposed correction or unresolved intent. Record whether the baseline includes uncommitted changes. Keep broad audit reports separate from player-facing prose; historical findings are leads to recheck, not future source of truth.

When implementing or documenting a fix for a recorded discrepancy, update `docs/tier-points-discrepancy-analysis.md` in the same work. Recheck the affected finding against current source and all relevant document occurrences, delete resolved findings from the report. Keep the report focused on outstanding issues; do not add resolved sections, resolution histories, or completion notes. Keep any remaining documentation contradiction or unverified behavior open rather than marking the whole case resolved. Refresh related report statements and affected source links so the report no longer describes implemented behavior as missing. This maintenance also applies when the request is to implement the documented behavior in source rather than sync the document to source.

Use static verification only unless a build is explicitly requested. Re-read changed paragraphs and other occurrences, check source links and `git diff --check`, and summarize what was reviewed versus left unverified. Do not add gameplay tests for documentation-only edits.

## Current implementation and maintenance notes

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

Runtime item/ability handling supplies mode-specific details. The [battle AI notes](../modify-elastic-emerald-ai-logic/SKILL.md) cover cases that also affect simulation or decisions.

## Comparing a rule with source

For each entry, I identify the species/form, ability, mode, and badge transitions in the executable branches. The implementation tests individual badge flags; interpreting them as a badge count assumes normal ordered progression. Values immediately before and at a threshold are useful distinctions.

Ordinary Tier Points and MaxTierPoints answer different questions. MaxTierPoints considers the current-mon floor, terminal evolutions, terminal Megas, nonempty ability slots, and current progression, with the Nincada-to-Shedinja branch excluded. Evolution requirements do not gate that search. Teaching implications also depend on the callers.

A conditional entry may appear in both an ability section and an unqualified “Always” list. I compare those occurrences together. Names such as Mega Charizard Y, regional forms, punctuation variants, and collective names such as Sinistcha sometimes need manual interpretation. A base-species case covers other forms only where the code normalizes or aliases them.

A broad comparison runs in both directions: documented values against source and explicit source cases against document coverage. I distinguish wrong conditions, missing entries, internal contradictions, and placeholders. This still does not establish coverage of every available species; default cost alone says nothing about encounter availability. Availability depends on the encounter and progression references.

## Discrepancy notes

`docs/tier-points-discrepancy-analysis.md` holds outstanding findings separately from player-facing prose. A useful finding records the document claim, implemented behavior, source symbol, and the remaining correction or design question, including any uncommitted baseline.

When I resolve a finding, I remove it after comparing the relevant source and document occurrences. The report is an outstanding-work list rather than a resolution history. A partial fix leaves the remaining contradiction or uncertainty visible.

For documentation changes, I review the prose, source references, and diff without a game build. The scope of that review remains separate from runtime verification.
