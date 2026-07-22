# Learnset helpers

## Single-Pokémon move analysis

`mon_move_analysis.py` reads every `porymoves_files/*.json` game dataset and
combines the level-up learnsets for one Pokémon. If a move appears in multiple
datasets, the script reports the arithmetic mean of its levels. It also reports
standout level-up, egg, and total-learnset moves relative to fully evolved
Pokémon of each of the Pokémon's types and its exact dual type, when applicable.

Run it from anywhere; its default data path is relative to the script:

```sh
python3 tools/learnset_helpers/mon_move_analysis.py Bulbasaur
python3 tools/learnset_helpers/mon_move_analysis.py "Mr. Mime" --format csv
python3 tools/learnset_helpers/mon_move_analysis.py Rotom_Wash --format json
```

Text output is sorted by average level and then move name. CSV and JSON output
also include the source game/level pairs, making individual values easy to audit.
For a Pokémon that can still evolve, its entire connected evolution line is
excluded from the fully evolved comparison cohorts.

## Type move reports

`type_move_report.py` generates a Markdown report for every fully evolved Pokémon
of a requested type. It lists standout level-up and egg moves learned by fewer
than one-sixth of the comparison group, plus total-learnset moves learned by
fewer than one-quarter. Each result includes its learner count and prevalence.
Dual-typed Pokémon also receive the same three comparisons against their exact
dual-type peers when at least one such peer exists.

```sh
python3 tools/learnset_helpers/type_move_report.py Fire
python3 tools/learnset_helpers/type_move_report.py TYPE_WATER -o docs/water_move_report.md
```

The report unions and deduplicates moves across all bundled game datasets. The
total learnset includes level-up, pre-evolution, egg, TM/HM, and tutor moves.
Each Pokémon section includes that complete unique historical move list before
its standout comparisons.
