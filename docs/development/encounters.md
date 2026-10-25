# Encounter documentation notes

I keep progression policy separate from source-derived encounter contents. The encounter audit and spreadsheet helper share an interpretation of the source, but the source alone cannot establish which locations or methods a player can reach at a particular point.

## Source map

| File | Role |
| --- | --- |
| `tools/elastic_emerald_helpers/audit_encounters.py` | Availability policy and audit output |
| `tools/elastic_emerald_helpers/update_encounters_spreadsheet.py` | Row mappings and rendered encounter text |
| `src/data/wild_encounters.json` | Species, rates, fishing groups, and map headers |
| `src/wild_encounter.c` | Runtime lookup and `MAX_REGULAR_LAND_SLOTS` |
| `tools/elastic_emerald_helpers/README.md` | Helper usage |

Map/NPC changes have additional context in my [NPC notes](npcs-and-trainers.md).

## Availability model

`AVAILABLE_LOCATIONS` and `AVAILABLE_METHODS` represent the progression point I am documenting. Surf, Rock Smash, and Super Rod data can exist before those methods are available. A newly reachable route can therefore require changes to both the audit policy and the spreadsheet mappings.

The runtime uses the first matching encounter header for a map. Rates and fishing slot groups come from the JSON, while the normal land-slot boundary comes from `MAX_REGULAR_LAND_SLOTS`. Later land slots are Monotype candidates, with evolution-based type eligibility in the renderer. Alternate floors can form one logical location without counting that availability more than once.

## Spreadsheet rows

The normalized `(Encounter Location, Encounter Type)` pair in Columns A and B identifies a row. `LOCATION_MAPS` handles accepted location names and aliases; `AUTOMATED_ROWS` identifies the pairs included in automation.

I automate Column C in `EncountersUnreleased`. Columns A, B, and D retain their authored content, and the released `Encounters` tab remains a historical record. The rendered text keeps the Non-Monotype/Monotype layout and colored `Mono-*` labels.

| Encounter type | Interpretation at the documented progression point |
| --- | --- |
| Grass, Cave, Sand, or deliberate blank | Land encounters, including Monotype output |
| Tree | Shaking encounters, without Monotype output |
| Fishing | Old Rod and Good Rod |
| Old Rod | Old Rod only |

I add locations using their exact map constants, grouping maps where they form one area and recording method exclusions where needed. Existing source data does not by itself establish a new Surfing or Super Rod row.

## Checks I use

These commands run from the repository root. The two audit forms help compare direct-script and module import behavior; the dry run exposes the proposed row text.

```sh
python -m tools.elastic_emerald_helpers.audit_encounters --by-location
python tools/elastic_emerald_helpers/audit_encounters.py --by-location
python -m tools.elastic_emerald_helpers.update_encounters_spreadsheet --dry-run
python -m py_compile tools/elastic_emerald_helpers/audit_encounters.py tools/elastic_emerald_helpers/update_encounters_spreadsheet.py
```

My review focuses on map grouping, duplicate headers, first-match behavior, and the affected rows. Live spreadsheet updates are a separate step after reviewing the dry run.

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
