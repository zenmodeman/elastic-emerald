---
name: manage-elastic-emerald-encounters
description: Audit Elastic Emerald encounter availability and maintain the source-backed EncountersUnreleased spreadsheet population. Use for progression encounter audits, adding newly reachable routes or methods, validating wild encounter source interpretation, changing encounter row mappings, or updating the unreleased encounter worksheet while preserving the released Encounters record.
---

Read `AGENTS.md` for repository conventions. Maintain this skill’s technical guidance when changes affect it.


# Manage Elastic Emerald Encounters

Maintain one source interpretation across the encounter audit and spreadsheet helper. Treat player progression as curated policy and encounter contents as source-derived data.

## Inspect the sources

Read these files before changing behavior:

- `tools/elastic_emerald_helpers/audit_encounters.py`
- `tools/elastic_emerald_helpers/update_encounters_spreadsheet.py`
- `src/data/wild_encounters.json`
- `src/wild_encounter.c` when land-slot boundaries or runtime lookup behavior matter
- `tools/elastic_emerald_helpers/README.md`

Inspect relevant map or species files only when the requested change requires them. If the work changes map/NPC content rather than documentation helpers alone, also load `skills/modify-elastic-emerald-npcs/SKILL.md`.

## Preserve the encounter model

- Keep reachable locations explicit in `AVAILABLE_LOCATIONS`; source data cannot determine progression.
- Keep currently usable methods explicit in `AVAILABLE_METHODS`. Do not include Surf, Rock Smash, or Super Rod until the user says they are obtainable at the audited point.
- Add a route to both the audit policy and spreadsheet row mappings when it belongs in both outputs.
- Use the first matching encounter header for a map, matching runtime lookup behavior.
- Read encounter rates and fishing slot groups from `wild_encounters.json` rather than duplicating them.
- Read `MAX_REGULAR_LAND_SLOTS` from `src/wild_encounter.c`; normal land encounters use only those slots.
- Treat later land slots as Monotype candidates. Preserve evolution-based type eligibility used by the spreadsheet renderer.
- Combine alternate floors of one logical location without double-counting availability.

## Maintain spreadsheet mappings

Use the normalized `(Encounter Location, Encounter Type)` pair from Columns A and B as the row identity. Add aliases to `LOCATION_MAPS` only when the displayed wording genuinely has multiple accepted forms, and add each intentionally automated pair to `AUTOMATED_ROWS`.

Automate only Column C in `EncountersUnreleased`. Preserve Columns A, B, and D and never update the released `Encounters` worksheet. Preserve the existing Non-Monotype and Monotype layout and colored `Mono-*` labels.

Map encounter types as follows:

- Grass, Cave, Sand, or a deliberate blank type: land encounters with Monotype output.
- Tree: shaking encounters without Monotype output.
- Fishing: Old Rod and Good Rod only at the current progression point.
- Old Rod: Old Rod only.

Do not create Surfing or Super Rod rows merely because their data exists in source.

## Add a reachable location

1. Confirm the exact map constant and whether multiple maps form one logical area.
2. Add the curated audit `Location`, including method exclusions where necessary.
3. Add the spreadsheet location text mapping and only the row types that already exist or were requested.
4. Check for duplicate map headers and confirm first-match behavior remains correct.
5. Run the static verification below.

## Verify statically

Run from the repository root:

```bash
python -m tools.elastic_emerald_helpers.audit_encounters --by-location
python tools/elastic_emerald_helpers/audit_encounters.py --by-location
python -m tools.elastic_emerald_helpers.update_encounters_spreadsheet --dry-run
python -m py_compile tools/elastic_emerald_helpers/audit_encounters.py tools/elastic_emerald_helpers/update_encounters_spreadsheet.py
```

Compare the direct and module audit outputs when import behavior changes. Inspect the proposed encounter text for the affected rows. Do not run a project build unless the user explicitly requests it.

Only run the spreadsheet updater without `--dry-run` when spreadsheet writes are within the request. Report the worksheet and number of cells updated.

## Current implementation and maintenance notes

Keep progression policy separate from source-derived encounter contents. The encounter audit and spreadsheet helper share an interpretation of the source, but the source alone cannot establish which locations or methods a player can reach at a particular point.

## Source map

| File | Role |
| --- | --- |
| `tools/elastic_emerald_helpers/audit_encounters.py` | Availability policy and audit output |
| `tools/elastic_emerald_helpers/update_encounters_spreadsheet.py` | Row mappings and rendered encounter text |
| `src/data/wild_encounters.json` | Species, rates, fishing groups, and map headers |
| `src/wild_encounter.c` | Runtime lookup and `MAX_REGULAR_LAND_SLOTS` |
| `tools/elastic_emerald_helpers/README.md` | Helper usage |

Map/NPC changes have additional context in the [NPC notes](../modify-elastic-emerald-npcs/SKILL.md).

## Availability model

`AVAILABLE_LOCATIONS` and `AVAILABLE_METHODS` represent the progression point under review. Surf, Rock Smash, and Super Rod data can exist before those methods are available. A newly reachable route can therefore require changes to both the audit policy and the spreadsheet mappings.

The runtime uses the first matching encounter header for a map. Rates and fishing slot groups come from the JSON, while the normal land-slot boundary comes from `MAX_REGULAR_LAND_SLOTS`. Later land slots are Monotype candidates, with evolution-based type eligibility in the renderer. Alternate floors can form one logical location without counting that availability more than once.

## Spreadsheet rows

The normalized `(Encounter Location, Encounter Type)` pair in Columns A and B identifies a row. `LOCATION_MAPS` handles accepted location names and aliases; `AUTOMATED_ROWS` identifies the pairs included in automation.

Automate only Column C in `EncountersUnreleased`. Columns A, B, and D retain their authored content, and the released `Encounters` tab remains a historical record. The rendered text keeps the Non-Monotype/Monotype layout and colored `Mono-*` labels.

| Encounter type | Interpretation at the documented progression point |
| --- | --- |
| Grass, Cave, Sand, or deliberate blank | Land encounters, including Monotype output |
| Tree | Shaking encounters, without Monotype output |
| Fishing | Old Rod and Good Rod |
| Old Rod | Old Rod only |

Add locations using their exact map constants, grouping maps where they form one area and recording method exclusions where needed. Existing source data does not by itself establish a new Surfing or Super Rod row.

## Verification commands

These commands run from the repository root. The two audit forms help compare direct-script and module import behavior; the dry run exposes the proposed row text.

```sh
python -m tools.elastic_emerald_helpers.audit_encounters --by-location
python tools/elastic_emerald_helpers/audit_encounters.py --by-location
python -m tools.elastic_emerald_helpers.update_encounters_spreadsheet --dry-run
python -m py_compile tools/elastic_emerald_helpers/audit_encounters.py tools/elastic_emerald_helpers/update_encounters_spreadsheet.py
```

Focus review on map grouping, duplicate headers, first-match behavior, and the affected rows. Live spreadsheet updates are a separate step after reviewing the dry run.

## Unown form IV guarantees

Randomly generated Unown receive three distinct guaranteed 31 IVs based on their displayed letter. Base-species Unown derive the letter from personality; explicit form species use that form. A–F guarantee HP, Attack, Defense, Sp. Atk, Sp. Def, and Speed respectively, then choose two distinct other stats at random. Question mark chooses any three distinct stats. Exclamation mark chooses one stat from each pair: Attack/Sp. Atk, Defense/Sp. Def, and HP/Speed.

G–Z enumerate triples lexicographically in display order (HP, Attack, Defense, Sp. Atk, Sp. Def, Speed):

| Form | Guaranteed IVs |
| --- | --- |
| G | HP, Attack, Defense |
| H | HP, Attack, Sp. Atk |
| I | HP, Attack, Sp. Def |
| J | HP, Attack, Speed |
| K | HP, Defense, Sp. Atk |
| L | HP, Defense, Sp. Def |
| M | HP, Defense, Speed |
| N | HP, Sp. Atk, Sp. Def |
| O | HP, Sp. Atk, Speed |
| P | HP, Sp. Def, Speed |
| Q | Attack, Defense, Sp. Atk |
| R | Attack, Defense, Sp. Def |
| S | Attack, Defense, Speed |
| T | Attack, Sp. Atk, Sp. Def |
| U | Attack, Sp. Atk, Speed |
| V | Attack, Sp. Def, Speed |
| W | Defense, Sp. Atk, Sp. Def |
| X | Defense, Sp. Atk, Speed |
| Y | Defense, Sp. Def, Speed |
| Z | Sp. Atk, Sp. Def, Speed |

`GetUnownPerfectIVMask` maps display order to the engine’s storage order, where Speed precedes the special stats. Both `SetBoxMonIVs` and template `ResolveIVs` apply the form mask instead of generic species/gift perfect-IV selection, so gift generation does not add a second random triple. Unselected IVs retain their ordinary rolls and may also naturally reach 31. Explicit fixed IVs and authored template values are preserved. Existing Pokémon are not modified retroactively.

The `Elastic-tests: Unown` tests in `test/pokemon.c` cover all twenty fixed combinations, all random-choice possibilities with deterministic seeds, all 28 forms through legacy/wild-template/gift-template creation, and explicit IV overrides.

Run `make check -j4 TESTS="Elastic-tests: Unown"` for the form guarantees and `make check -j4 TESTS="test/pokemon.c"` for the surrounding creation regressions. The Pokémon tests use Elastic’s random/curated Tera defaults rather than upstream primary/secondary-type assumptions. Hidden Power regressions can be selected with `make check -j4 TESTS="*Hidden Power"`; generation overrides in battle tests require `CONFIG_B_*` identifiers in `WITH_CONFIG`.
