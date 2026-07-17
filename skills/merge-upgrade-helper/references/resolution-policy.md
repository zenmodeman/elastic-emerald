# Resolution Policy

## Preserve Local Intent, Adopt Upstream Shape

Prefer local custom behavior when it is game-design logic, scoring logic, custom data, or project-specific policy. Prefer upstream when the difference is an API shape, generated-file convention, struct layout, enum name, macro, or helper function that changed in the newer version.

## Generated Files

If a conflicted file is now generated, deleted, or ignored by upstream, do not hand-merge the generated output unless the repo still consumes it directly. Prefer the generator source and stage the deletion.

## Common Hotspots

- `include/battle.h`: duplicate fields in large structs are common after conflict resolution.
- `include/constants/battle_string_ids.h`: duplicate string IDs are common when one side added messages near the top and the other appended locally.
- `src/battle_ai_main.c`: look for duplicate `case` labels, stale helper signatures, old status globals, and interleaved switch blocks.
- `src/battle_ai_util.c`: look for stale damage/type APIs, duplicate helper definitions, mismatched prototypes, and missing forward declarations.
- `src/battle_ai_switch_items.c`: look for interleaved functions, stale `GetThinkingBattler`, old status globals, and duplicated local arrays/pointers.
- `data/battle_scripts_1.s`: assembler `invalid operands (*ABS* and *UND*) for '|'` can mean a macro argument or constant name stayed unresolved after a merge, not necessarily a clean-build issue.

## Staging

Before staging:

1. Run marker scan.
2. Run `git diff --check`.
3. Run stale-token scans relevant to touched files.
4. If allowed, run targeted compiler front-end checks for changed C files.

After staging:

1. Run `git diff --cached --check`.
2. Run `git diff --name-only --diff-filter=U`.
