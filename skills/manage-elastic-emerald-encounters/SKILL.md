---
name: manage-elastic-emerald-encounters
description: Audit Elastic Emerald encounter availability and maintain the source-backed EncountersUnreleased spreadsheet population. Use for progression encounter audits, adding newly reachable routes or methods, validating wild encounter source interpretation, changing encounter row mappings, or updating the unreleased encounter worksheet while preserving the released Encounters record.
---

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
