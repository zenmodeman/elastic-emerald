# AGENTS.md instructions

When working with the elastic-emerald project, avoid doing build checks unless explicitly asked and stick to static checks for code verification. The developer will handle doing the build check, since the overhead is large and a build can take a long time.

Any new tests created for this project should use the `Zenmodeman: ` prefix in the test name, to distinguish these tests from Expansion native tests.

## Skill selection and autodetection

Load and follow a skill whenever the request names it or the work matches the cases below. Announce the selected skill before acting.

### Elastic Emerald AI logic skill

Use the project skill at `skills/modify-elastic-emerald-ai-logic/SKILL.md` when implementing, diagnosing, reviewing, or documenting battle-AI behavior. Autodetect it for work involving:

- move scoring, viability, damage comparison, target selection, switching, switch-in ranking, trainer items, or doubles coordination;
- revealed, inferred, predicted, or omniscient opponent information;
- AI damage, Speed, type, ability, item, status, field, or gimmick simulations;
- temporary mutation and restoration of battle state during AI calculations;
- AI support for a new or changed move, ability, item, battle mechanic, or Terastalization behavior;
- battle-AI regressions or tests under `test/battle/ai`.

### Elastic Emerald NPC and route boss skill

Use the project skill at `skills/modify-elastic-emerald-npcs/SKILL.md` when implementing, diagnosing, reviewing, or documenting NPC, trainer, or route-boss content. Autodetect it for work involving:

- overworld NPC placement, map objects, local IDs, map-script entry points, or NPC dialogue and interaction logic;
- creating or converting a map `scripts.pory`, raw-script migration, or regeneration of a map's `scripts.inc`;
- trainer IDs, trainer-slot reuse, rematch-table changes, trainer parties, Match Call integration, or trainer documentation;
- route-boss prerequisites, pre-battle healing, consent flow, rewards, Bag-to-PC fallback, or reward-state flags;
- Restricted Mode, Resource Mode, badge, rival, trainer-defeat, or other progression gates on NPC encounters;
- programmatic trainer-level scaling or changes to `GetTrainerLevelModifier`;
- verification or regression work for any of the above.

If NPC or route-boss work also changes battle-AI decisions or simulation behavior, use both this skill and the Elastic Emerald AI logic skill.

### Elastic Emerald encounter management skill

Use the project skill at `skills/manage-elastic-emerald-encounters/SKILL.md` when auditing encounter availability or maintaining the source-backed encounter spreadsheet automation. Autodetect it for work involving:

- `audit_encounters.py`, reachable-location or available-method policy, encounter weighting, or Monotype-only availability;
- `update_encounters_spreadsheet.py`, encounter row mappings, encounter rendering, or the `EncountersUnreleased` worksheet;
- adding a newly reachable route or fishing method to encounter documentation.

### Elastic Emerald item acquisition management skill

Use the project skill at `skills/manage-elastic-emerald-item-acquisition/SKILL.md` when maintaining source-linked item acquisition documentation. Autodetect it for work involving:

- `update_item_acquisition_spreadsheet.py` or the `ItemAcquisitionUnreleased` worksheet;
- generic automation tags, source mappings, NPC gifts, trainer rewards, marts, berries, ground items, or hidden items;
- refreshing source-side presentation templates after user edits to spreadsheet wording or layout.

### Merge upgrade helper

Use the project skill at `skills/merge-upgrade-helper/SKILL.md` automatically when resolving or auditing an upstream merge or version upgrade. Trigger cases include:

- unresolved conflict markers or files reported as unmerged;
- post-merge compiler, assembler, linker, or generated-file failures;
- stale APIs, renamed constants or struct fields, duplicate enum members, duplicate cases, or interleaved brace/switch structure after an upgrade;
- adapting local custom behavior to a newer upstream API or data layout;
- checking whether custom gameplay, AI, scripts, UI, save data, or generated content survived a merge even when conflicts are already resolved;
- repeated merge rediscovery that should be captured in the upgrade dossier.

For Elastic Emerald merge audits, read `docs/merge-upgrade-helper/README.md` as directed by the skill. If merge work touches battle AI, use both skills: apply the merge helper for conflict resolution and upstream adaptation, then the Elastic Emerald AI logic skill for behavioral intent, simulation safety, AI/runtime parity, tests, and summary updates.

## AI documentation maintenance

When changing battle-AI behavior, update `docs/custom_ai_logic_summary.md` in the same work so its behavioral description and key-commit references remain current.

Maintain the document's `Documentation status` section as follows:

- Record the newest commit whose applicable AI changes have actually been reviewed and documented.
- If the AI changes being documented are not committed yet, identify them explicitly as uncommitted; do not attribute them to an older commit or invent a future hash.
- Whenever later work modifies `custom_ai_logic_summary.md`, check `git status`, the relevant diff, and recent history to determine whether previously documented uncommitted AI changes now have a commit. If so, replace the uncommitted marker with the real commit and advance the last-documented commit as appropriate.
- Do not advance the recorded commit past AI changes that have not yet been reviewed for inclusion in the summary.

## Map and script editing notes

When editing map scripts, prefer changing the source `.pory` file and regenerating the corresponding `.inc` with `tools/poryscript/poryscript`. A quick static check can compile the single script to `/tmp` with the same `-fc tools/poryscript/font_config.json` and `-cc tools/poryscript/command_config.json` arguments used by the Makefile.

In Poryscript function-style blocks, commands with arguments such as `setflag`, `removeobject`, and `playmoncry` should use function-call syntax, e.g. `setflag(FLAG_NAME)`, `removeobject(LOCALID_NAME)`, and `playmoncry(SPECIES_NAME, CRY_MODE_NORMAL)`. Otherwise the compiler may accept the file but emit malformed split command lines.

Local-id symbols from `map.json` are generated into a global header, so avoid generic names such as `LOCALID_PROFESSOR_BIRCH` that may collide with another map. For one-off script-local IDs, a raw `.set LOCALID_MAP_NAME_OBJECT, <id>` can be safer than adding a `local_id` to `map.json`.

For static overworld Pokemon map objects, this project supports `OBJ_EVENT_GFX_SPECIES(NAME)`. When adding ambient Pokemon to a custom encounter area, check the first eight normal land encounter slots first; later encounter slots may be monotype-specific.
