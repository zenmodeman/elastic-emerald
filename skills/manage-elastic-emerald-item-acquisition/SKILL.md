---
name: manage-elastic-emerald-item-acquisition
description: Maintain Elastic Emerald's source-linked ItemAcquisitionUnreleased automation while preserving user-authored contextual documentation. Use when adding or changing item acquisition rows, generic Column F tags, source mappings, NPC gifts, trainer rewards, marts, berry patches, ground or hidden items, item substitution templates, or refreshing source-side presentation strings after spreadsheet UI edits.
---

# Manage Elastic Emerald Item Acquisition

Treat the worksheet as user-authored documentation and the helper as a selective item-substitution system. Do not attempt to regenerate the entire row from game source.

## Ownership model

- The user owns the broader context, explanations, mode wording, ordering, and presentation in Column C.
- Game source owns dynamic item identities and quantities wherever a reliable source anchor exists.
- Column F owns stable, generic row identities such as `HiddenItem1`, `GroundItem1`, or `NPCGift1`.
- Code owns the mapping from each normalized location plus generic tag to volatile source symbols, paths, labels, and flags.
- The released `ItemAcquisition` worksheet is a historical reference. Never write to it.

Read `tools/elastic_emerald_helpers/update_item_acquisition_spreadsheet.py`, its README section, the relevant source files, and the live `ItemAcquisitionUnreleased` Columns A:F before changing mappings or templates. Compare the released `ItemAcquisition` row when checking whether context was accidentally lost.

## Preserve stable spreadsheet tags

Never put source identifiers such as flags, script labels, paths, or variable names in Column F. Keep those in `BOOTSTRAP_TAGS`/`AUTOMATION_MAPPINGS` so source renames require code changes only.

Tag all reliably source-backed acquisitions, including NPC gifts and trainer rewards. Use a generic category plus a location-local ordinal. Preserve an existing tag even if the underlying item or source symbol changes. Use `current_item` only to disambiguate bootstrap rows that otherwise have identical location/details; it is not the persistent identity.

## Add a new documented acquisition

1. Let the user establish the initial row and contextual wording in `ItemAcquisitionUnreleased`.
2. Read Columns A:F and identify the row by location, details, existing item text, and nearby rows.
3. Find the narrowest reliable source anchor: map item flag, script label, item array, mart array, berry-tree constant, or a reviewed composite.
4. Add a `BootstrapTag` mapping and ensure `_generic_tag` selects an appropriate generic tag family.
5. Add or extend source extraction only when the existing source kinds cannot represent the acquisition.
6. Preserve the user's row format in `_render_tag` or a dedicated presentation helper. Substitute only source-backed item-bearing fragments.
7. Include relevant mode/progression distinctions and NPC-gift context from the authored row; do not collapse them into a bare item list.
8. Dry-run tag initialization and population before any write.

If a row has no trustworthy source anchor, leave it untagged instead of inventing a fragile mapping.

## Refresh presentation strings from spreadsheet edits

Use this workflow when the user has improved contextual text in the spreadsheet UI or asks to add acquisitions:

1. Read the current `ItemAcquisitionUnreleased` A:F values and run the updater with `--dry-run` to obtain code-rendered values.
2. Match rows by normalized Column A plus the stable Column F tag, not by row number or current item text.
3. Review each difference. Treat a deliberate prose, layout, ordering, or mode-note edit in Column C as the new contextual template.
4. Identify the dynamic item fragments in that template and keep them sourced through `_render_source` and its extraction helpers. Never freeze current item names or quantities into the template when they can change in source.
5. Update the row-specific branch in `_render_tag`, or factor repeated layouts into a named presentation helper. Preserve whitespace and line structure when meaningful.
6. Run another dry-run. The proposed value should match the user-authored format while reflecting current source items.
7. Compare relevant rows with the released `ItemAcquisition` tab to catch lost historical context such as NPC identity, progression timing, image position, or mode behavior.

Do not refresh a presentation template merely because the item value differs: if prose is unchanged and source changed the item, source must win. Do not automatically ingest every live Column C value into code; review is required to separate context from substitutions.

## Verify and write safely

Run from the repository root:

```bash
python -m tools.elastic_emerald_helpers.update_item_acquisition_spreadsheet --initialize-tags --dry-run
python -m tools.elastic_emerald_helpers.update_item_acquisition_spreadsheet --dry-run
python -m py_compile tools/elastic_emerald_helpers/update_item_acquisition_spreadsheet.py
```

Inspect all affected rendered rows, especially marts, branched quantities, composite item/gift rows, and repeated location/tag categories. Do not run a project build unless explicitly requested.

Only initialize tags without `--dry-run` when Column F writes are authorized. Only run normal population without `--dry-run` when Column C writes are authorized. State which columns and worksheet will change before writing, and confirm that no other columns or released tabs were modified.
