# Static check notes

These are commands I use to answer specific questions during review. A clean result is limited to what the command checks; it does not replace a runtime test.

## Conflicts and working state

Git's unmerged-path list and a marker search expose unresolved text conflicts. `<files>` stands for the paths under review.

```sh
git diff --name-only --diff-filter=U
rg -n "<<<<<<<|=======|>>>>>>>" <files>
git status --short
```

The broad marker search can also match ordinary separator text, so I review the matches rather than treating every one as a conflict.

## Whitespace and stale symbols

The working and staged diffs have separate whitespace checks:

```sh
git diff --check -- <files>
git diff --cached --check -- <files>
```

These searches collect symbols that have appeared in older upgrade problems. A match is a lead for investigation, not an automatic replacement:

```sh
rg -n "status2|gStatuses3|gStatuses4|STATUS2_|STATUS3_|STATUS4_|tentativeScores|wild_encounters\.json\.txt" src include data asm test
rg -n "MOVE_EFFECT_STEAL_ITEM|MOVE_EFFECT_SPIKES|HITMARKER_PASSIVE_DAMAGE|B_ILLUMINATE_EFFECT" src include data asm test
```

## Compiler checks

A targeted C front-end check still depends on the compiler, generated headers, and preprocessing pipeline. I derive such commands from the current Makefile and installed toolchain; compiler paths copied from older notes can be stale. Routine documentation review needs no compilation.
