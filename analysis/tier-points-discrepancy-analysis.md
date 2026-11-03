# Tier points discrepancy analysis

Reviewed 2026-09-06 against working-tree `docs/gameplay/tier-points.md` and source based on HEAD `985efb9d37`, including existing uncommitted edits in both files. This is an analysis, not a change to gameplay or the author's current wording.

## Unspecified or needing separate evidence

- Regenerator, Huge Power/Pure Power, Shell Armor/Battle Armor, Speed Boost, Contrary, and Moxie headings are empty. They do not specify discrepancies to implement. The current calculator has ability-dependent branches for Politoed, Pelipper, Vulpix, Ninetales, Glimmora, Glimmet, and Darmanitan-Galar; it does not implement broad ability-category discounts.
- The claim that all other Pokémon should be eligible before the post-game, the BST-based legendary exclusion, ability-patch progression restrictions, and Mega Charizard Y availability were not established by this cost review. They require a separate availability/progression audit; tier cases alone cannot establish them.
- The opening paragraph says “cannot exclude” the cap; “cannot exceed” conveys the implemented rule. Other spelling issues are editorial, not gameplay discrepancies.

## Reviewed matches and limits

The ordinary progression branches were compared with the document's Ends at 3/2/1 groupings. The cap constant is 20. Eggs contribute zero before hatching, a detail the introduction does not currently explain.

The MaxTierPoints algorithm and threshold description agree with `GetMonMaxTierPoints`, its helper traversal, and the constants in [pokemon.h](../include/pokemon.h#L24): current-mon floor, terminal evolutions and their Megas, all nonempty terminal/Mega ability slots, current badge state, and the Nincada/Shedinja exclusion. The teaching predicates and reviewed callers support the documented Resource Mode threshold of 2 and Restricted Mode threshold of 5, including earliest current-species level and boxed-level conversion. TM reimbursement preserves quantity and uses the quoted message in [party_menu.c](../src/party_menu.c#L5635). The Tera threshold of 4 and ability exceptions are present in [battle_terastal.c](../src/battle_terastal.c#L58); a complete form-eligibility audit was not performed.

This was a static review of the calculator, document lists, and relevant teaching/Tera paths. No build or runtime tests were run. It is not an exhaustive census of every form falling through to the default 3-point value, every acquisition method, or every cap-enforcement edge case. No source or player-facing document changes were made by this audit.
