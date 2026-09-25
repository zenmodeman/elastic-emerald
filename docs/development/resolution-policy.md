# Notes on merge decisions

## Local behavior and upstream structure

I retain local game design, scoring, custom data, and mode policy while adopting newer upstream API signatures, generated-file conventions, struct layouts, enum names, and helpers. Where upstream now implements the same behavior, a separate local implementation can become redundant.

Generated output is a consequence of its input and generator. When upstream deletes or ignores an old output, the meaningful resolution is usually in the input rather than a hand-merged copy of that output.

## Recurring conflict locations

| Location | Problems seen during upgrades |
| --- | --- |
| `include/battle.h` | Duplicate fields in large structs |
| `include/constants/battle_string_ids.h` | Duplicate string IDs introduced at different positions |
| `src/battle_ai_main.c` | Duplicate cases, stale signatures/status globals, interleaved switch blocks |
| `src/battle_ai_util.c` | Stale damage/type APIs, duplicate helpers, declaration mismatches |
| `src/battle_ai_switch.c`, `src/battle_ai_items.c` | Logic formerly combined in `battle_ai_switch_items.c`; interleaved functions, stale battler/status access, duplicate locals |
| `data/battle_scripts_1.s` | Unresolved macro arguments/constants causing `invalid operands (*ABS* and *UND*) for '|'` |

## Reviewing a resolution

I use conflict-marker scans, relevant stale-symbol searches, and `git diff --check` before staging. The staged diff and remaining unmerged-path list provide a separate check that the intended resolution is what Git will record. Compiler checks, when needed, use the current project toolchain and are separate from routine static review.
