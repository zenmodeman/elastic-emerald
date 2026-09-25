# Item acquisition documentation notes

I write the acquisition context in the spreadsheet and use source extraction for item names and quantities. The helper is a selective substitution system, so a source change does not replace a whole row's explanation with a bare item list.

## Authored context and source values

Column C contains my explanations, mode distinctions, ordering, and presentation. Reliable source anchors supply the dynamic item identities and quantities. Column F holds a stable generic tag such as `HiddenItem1`, `GroundItem1`, or `NPCGift1`; the code maps location/tag pairs to source paths, labels, flags, or arrays.

The working tab is `ItemAcquisitionUnreleased`. I retain the released `ItemAcquisition` tab as a historical reference, including when comparing whether context has been lost.

The implementation is `tools/elastic_emerald_helpers/update_item_acquisition_spreadsheet.py`, with usage notes in the adjacent README. Live Columns A:F provide the authored baseline for mapping or presentation changes.

## Stable identities

Source identifiers belong in `BOOTSTRAP_TAGS`/`AUTOMATION_MAPPINGS`, rather than in Column F. This lets a source rename remain a code change without changing the row's identity. Tags use a generic category and location-local ordinal and survive changes to the underlying item.

`current_item` disambiguates otherwise identical bootstrap rows; it is not a persistent identity. Acquisitions without a trustworthy source anchor remain untagged.

## Adding an acquisition

I begin with the row and its contextual wording, then identify the narrowest reliable anchor: a map item flag, script label, item/mart array, berry-tree constant, or a reviewed combination. A `BootstrapTag` and `_generic_tag` associate that anchor with the row. New extraction logic is only needed when the existing source kinds cannot represent it.

`_render_tag` or a dedicated presentation helper retains the row's prose and layout while substituting source-backed fragments. Mode/progression distinctions and NPC-gift context stay part of that presentation. Separate dry runs show the effects of tag initialization and normal population.

## Editing spreadsheet wording

After I change prose or layout in the spreadsheet, a dry run shows where the code's presentation template still differs. I match rows by normalized location plus Column F tag, since row numbers and item names can change.

Deliberate wording changes become the new template in `_render_tag`; dynamic fragments continue through `_render_source` and its extraction helpers. Repeated layouts can share a presentation helper. A second dry run shows whether the updated template matches the intended whitespace, ordering, and context while still following the source items.

An item-only difference has a different meaning: when source changes an item but the prose is unchanged, the source value wins. I review differences individually rather than treating every live Column C value as a new template. The released tab helps catch lost details such as NPC identity, progression timing, or image position.

## Checks and writes

My review commands are:

```sh
python -m tools.elastic_emerald_helpers.update_item_acquisition_spreadsheet --initialize-tags --dry-run
python -m tools.elastic_emerald_helpers.update_item_acquisition_spreadsheet --dry-run
python -m py_compile tools/elastic_emerald_helpers/update_item_acquisition_spreadsheet.py
```

Tag initialization writes Column F; normal population writes Column C. I review those changes separately, particularly marts, branched quantities, combined gifts, and repeated location/tag categories. Other columns and released tabs are outside the updater's intended changes.
