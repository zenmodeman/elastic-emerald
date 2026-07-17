# Check Recipes

## Conflict Inventory

Use:

```bash
git diff --name-only --diff-filter=U
rg -n "<<<<<<<|=======|>>>>>>>" <files>
```

After staging, verify:

```bash
git diff --name-only --diff-filter=U
git status --short
```

## Static Hygiene

Use:

```bash
git diff --check -- <files>
git diff --cached --check -- <files>
```

Scan for repeated stale symbols from recent merges:

```bash
rg -n "status2|gStatuses3|gStatuses4|STATUS2_|STATUS3_|STATUS4_|tentativeScores|wild_encounters\.json\.txt" src include data asm test
rg -n "MOVE_EFFECT_STEAL_ITEM|MOVE_EFFECT_SPIKES|HITMARKER_PASSIVE_DAMAGE|B_ILLUMINATE_EFFECT" src include data asm test
```

## Targeted C Front-End Check

When full builds are expensive or forbidden, check one touched C file with the same broad front-end shape as the Makefile and write output to `/tmp`:

```bash
arm-none-eabi-cpp -iquote include -Wno-trigraphs -DMODERN=1 -DTESTING=0 -std=gnu17 src/file.c \
  | tools/preproc/preproc -i src/file.c charmap.txt \
  | /usr/lib/gcc/arm-none-eabi/10.3.1/cc1 -quiet -mthumb -mthumb-interwork -O2 -mabi=apcs-gnu -mtune=arm7tdmi -march=armv4t -Wno-pointer-to-int-cast -std=gnu17 -Werror -Wall -Wno-strict-aliasing -Wno-attribute-alias -Woverride-init -Wnonnull -Wenum-conversion -Wno-error=unused-variable -Wno-error=unused-const-variable -Wno-error=unused-parameter -Wno-error=unused-function -Wno-error=unused-but-set-parameter -Wno-error=unused-but-set-variable -Wno-error=unused-value -Wno-error=unused-local-typedefs -o /tmp/file.s -
```

Use this only for touched C files and only when it respects repository instructions.
