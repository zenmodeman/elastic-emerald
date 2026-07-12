# AGENTS.md instructions

When working with the elastic-emerald project, avoid doing build checks unless explicitly asked and stick to static checks for code verification. The developer will handle doing the build check, since the overhead is large and a build can take a long time.

Any new tests created for this project should use the `Zenmodeman: ` prefix in the test name, to distinguish these tests from Expansion native tests.

## Map and script editing notes

When editing map scripts, prefer changing the source `.pory` file and regenerating the corresponding `.inc` with `tools/poryscript/poryscript`. A quick static check can compile the single script to `/tmp` with the same `-fc tools/poryscript/font_config.json` and `-cc tools/poryscript/command_config.json` arguments used by the Makefile.

In Poryscript function-style blocks, commands with arguments such as `setflag`, `removeobject`, and `playmoncry` should use function-call syntax, e.g. `setflag(FLAG_NAME)`, `removeobject(LOCALID_NAME)`, and `playmoncry(SPECIES_NAME, CRY_MODE_NORMAL)`. Otherwise the compiler may accept the file but emit malformed split command lines.

Local-id symbols from `map.json` are generated into a global header, so avoid generic names such as `LOCALID_PROFESSOR_BIRCH` that may collide with another map. For one-off script-local IDs, a raw `.set LOCALID_MAP_NAME_OBJECT, <id>` can be safer than adding a `local_id` to `map.json`.

For static overworld Pokemon map objects, this project supports `OBJ_EVENT_GFX_SPECIES(NAME)`. When adding ambient Pokemon to a custom encounter area, check the first eight normal land encounter slots first; later encounter slots may be monotype-specific.
