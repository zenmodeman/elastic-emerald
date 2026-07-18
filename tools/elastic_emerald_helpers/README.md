# Elastic Emerald data helpers

These scripts keep spreadsheet/reference workflows beside the source data they read. Run them from the repository root as modules so imports remain stable:

```sh
python -m tools.elastic_emerald_helpers.audit_encounters
python -m tools.elastic_emerald_helpers.update_moves_spreadsheet --dry-run --start 0 --end 2
```

The spreadsheet updater can also be launched directly from this directory:

```sh
python update_moves_spreadsheet.py --dry-run --start 0 --end 2
```

The spreadsheet updater reads current learnsets and tutor lists from `src/data/pokemon`. Stable species numbers, the complete TM list, and all progression split definitions remain in `spreadsheet_config.py`. At runtime, the updater finds each current row from Columns A and B, so inserting or moving spreadsheet rows does not require configuration changes. Columns D–M cover every split from Gym 1 through post-game; each column receives only the level-up, tutor, and TM/HM moves introduced during that split. The dedicated egg-move column receives the complete egg-move list.

## Google credentials

Install `gspread` in your local Python environment to perform updates. Put the service-account JSON at `tools/elastic_emerald_helpers/SecretKey.json`, or set `ELASTIC_EMERALD_GOOGLE_CREDENTIALS`/pass `--credentials` with another path. Credential JSON files in this directory are ignored; never commit a real key.

Share the target spreadsheet with the service account's `client_email` before running without `--dry-run`. Use `--start` and `--end` for small batches and review a dry run first.
