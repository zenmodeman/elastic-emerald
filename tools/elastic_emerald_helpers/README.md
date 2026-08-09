# Elastic Emerald data helpers

These scripts keep spreadsheet/reference workflows beside the source data they read. Run them from the repository root as modules so imports remain stable:

```sh
python -m tools.elastic_emerald_helpers.audit_encounters
python -m tools.elastic_emerald_helpers.audit_encounters --by-location
python -m tools.elastic_emerald_helpers.update_encounters_spreadsheet --dry-run
python -m tools.elastic_emerald_helpers.update_item_acquisition_spreadsheet --dry-run
python -m tools.elastic_emerald_helpers.update_moves_spreadsheet --dry-run --start 0 --end 2
```

## Encounter availability audit

`audit_encounters.py` summarizes the standard and Monotype-only species obtainable
through the current early-game checkpoint. The audited locations and currently
available traversal methods are declared at the top of the script; encounter slot
groups and probabilities are read from `src/data/wild_encounters.json`, and the
normal-mode land-slot boundary is read from `src/wild_encounter.c`. Surfing, Rock
Smash, and Super Rod encounters are currently excluded. Use `--by-location` to see
which standard-mode species each independently counted area contributes.

`update_encounters_spreadsheet.py` writes only Column C of source-backed rows in
`EncountersUnreleased`. It resolves rows through the configured Column A location
and Column B encounter-type keys, derives normal and Monotype encounters from the
same source data and runtime type-selection rules, and applies the existing colored
Monotype labels. Gift rows, unavailable encounter methods, and the versioned
`Encounters` worksheet are not modified. Run with `--dry-run` to inspect generated
cell contents without credentials or network access.

`update_item_acquisition_spreadsheet.py` uses Column F of
`ItemAcquisitionUnreleased` as a stable automation-tag column. Generic sheet tags
such as `HiddenItem1`, `GroundItem1`, and `MartInventory` are resolved through a
code-side mapping to map item flags, berry-tree IDs, mart definitions, item arrays,
or held-item commands. Source-symbol renames therefore require changes only in the
script. Row-specific code templates preserve explanatory prose, mode conditions,
positional notes, and combined rewards while substituting the source-backed item
names and quantities; only tagged rows have their Column C value regenerated. Use
`--initialize-tags` once after establishing new rows, and review `--dry-run` before
running an update. Complex scripted rewards remain untagged until they receive a
stable source mapping, so their manually maintained prose is preserved.

The spreadsheet updater can also be launched directly from this directory:

```sh
python update_moves_spreadsheet.py --dry-run --start 0 --end 2
```

## Trainer documentation

`sync_trainer_docs.py` updates only explicitly tagged generated regions in `docs/gameplay/trainers.md`; it never imports untagged or work-in-progress trainer parties. Each generated region includes trainer battle items when present, battle type, AI flags beyond the default `Smart Trainer`, the class- or route-boss-based pre-battle healing policy, and the party. Party entries document the resolved Pokémon gender from explicit settings, fixed species genders, or the trainer-/battle-type-based personality default. Intentionally shared teams retain the neutral `Trainer default` label when gender is omitted. Manual notes outside those regions are preserved. Use `--check` for a non-writing stale-content check.

The spreadsheet updater reads current learnsets and tutor lists from `src/data/pokemon`. Stable species numbers, the complete TM list, and all progression split definitions remain in `spreadsheet_config.py`. At runtime, the updater finds each current row from Columns A and B, so inserting or moving spreadsheet rows does not require configuration changes. Columns D–M cover every split from Gym 1 through post-game; each column receives only the level-up, tutor, and TM/HM moves introduced during that split. The dedicated egg-move column receives the complete egg-move list.

## Google credentials

Install `gspread` in your local Python environment to perform updates. Put the service-account JSON at `tools/elastic_emerald_helpers/SecretKey.json`, or set `ELASTIC_EMERALD_GOOGLE_CREDENTIALS`/pass `--credentials` with another path. Credential JSON files in this directory are ignored; never commit a real key.

Share the target spreadsheet with the service account's `client_email` before running without `--dry-run`. Use `--start` and `--end` for small batches and review a dry run first.
