# Learnset helpers

## Single-Pokémon move analysis

`mon_move_analysis.py` reads every `porymoves_files/*.json` game dataset and
combines the level-up learnsets for one Pokémon. If a move appears in multiple
datasets, the script reports the arithmetic mean plus the minimum and maximum
observed levels. Level 0 evolution-move records count toward those ranges. It also reports
standout level-up, egg, and total-learnset moves relative to fully evolved
Pokémon of each of the Pokémon's types and its exact dual type, when applicable.
Immediately after the combined level-up table, it reports deduplicated move
deltas against all pre-evolutions and evolutions for those same three move
classes. A move shared by multiple relatives is listed once with every relative
that contributes the difference.

The report also lists every evolution move for every Pokémon in the connected
evolutionary line. A move counts as an evolution move when any bundled game
records it at level 0; the report shows all such games and deduplicates repeated
records.

Run it from anywhere; its default data path is relative to the script:

```sh
python3 tools/learnset_helpers/mon_move_analysis.py Bulbasaur
python3 tools/learnset_helpers/mon_move_analysis.py "Mr. Mime" -o reports/mr_mime.md
python3 tools/learnset_helpers/mon_move_analysis.py Rotom_Wash
```

Markdown output is sorted by average level and then move name. If `--output` is
omitted, the report is written to `move_analysis_output_instance.md`. Report
contents are not printed to standard output; the command prints only a concise
success message identifying the destination file. Failures produce a concise
error instead.
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

## Off-type teachable move counts

`off_type_teachable_move_counts.py` ranks every move, including Normal and
status moves, by the number of fully evolved Pokémon that do not share its type
and learn it by TM or tutor, but never by level-up or as an egg move in any
bundled PoryMoves dataset. Learnsets are unioned across all of the JSON
datasets. The only move-level output filter omits moves with no qualifying
teachable learners. The report also shows the number of fully evolved off-type
Pokémon learning each displayed move by level-up and the difference between
its teachable and level-up counts. Moves are sorted by that difference in
descending order. The primary section excludes moves named in
`tmExclusionHelper`, while a secondary section contains only those excluded
moves so that moves already ruled out as TMs do not distort the priority list.

```sh
python3 tools/learnset_helpers/off_type_teachable_move_counts.py
python3 tools/learnset_helpers/off_type_teachable_move_counts.py -o reports/custom_name.md
```

The Markdown table is written to
`tools/learnset_helpers/off_type_moves.md` by default. Use `--output` to select
a different destination.
