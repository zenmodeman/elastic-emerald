# Elastic Emerald feature history

I keep this index of the major custom systems and their implementation commits, through `9cf5263470` (October 4, 2026), with pending additions explicitly labeled. It draws on the existing project feature/AI references and local Git history. It covers major gameplay, content, and tooling changes; routine individual learnset, encounter, trainer, and balance edits are not exhaustively listed. The inherited Expansion changelog remains separate.

Commits identify introductions, extensions, or repairs as labeled; old patches are historical evidence, not necessarily the current implementation. I use `git show <commit>` to inspect a patch and `git log -- <path>` to follow later changes. The [custom feature reference](development/feature-reference.md) describes current behavior and source anchors at a high level, the [AI summary](custom_ai_logic_summary.md) covers individual scoring rules, and the [development guides](development/README.md) record my maintenance approach.

## Newest changes

Committed entries use their actual commit IDs. **Newest — uncommitted** identifies working-tree changes awaiting a commit; replace that label with the commit ID once committed.

| Change | Commit or status | Specification |
| --- | --- | --- |
| Proactive Color Change | `cb993f21b5` (2026-09-25) | Changes the target's type before immunity checks, including status moves; runtime eligibility and AI prediction share the rule. |
| Overwhelm Beam | `3c2264d738` (2026-09-27) | Adds a 120-power, 80%-accuracy Special Normal attack with an Insomnia ability-replacement secondary effect. Supersedes the earlier uncommitted label. |
| Round turn-tracking repair | `868293c1c6` (2026-10-04) | Replaces reliance on the previous move/action with `roundUsedThisTurn`, records Round after move resolution, and clears the flag at battle initialization and turn end. Prevents a previous turn's Round from doubling later damage; adds single- and double-battle regression scenarios. |
| Custom test naming | `510e560dfe` (2026-10-04) | Renames the project test convention to `Elastic-tests: `. |
| Color Change animation coverage | `9cf5263470` (2026-10-04) | Adds animation expectations to Color Change tests. |
| Party-menu relearner repair | **Newest — uncommitted** | Upstream `7c1033a479` removed party-menu access. Adds a single `RELEARN MOVES` entry opening level-up moves directly for the selected Pokemon, with current Resource Mode checks, facility exclusions, and the existing party-return callback. The entry requires an available level-up move. Expands the action buffer for four field moves and widens the action window for the label. Adds the declaring `battle_factory.h` and `battle_tent.h` headers to fix compilation. Replaces the earlier uncommitted category-submenu restoration to match the intended party-menu service. |
| Party-menu relearner regression coverage | **Newest — uncommitted** | Adds nine `Elastic-tests: Party relearner` cases and `TESTING`-only hooks in `test/party_menu.c` / `src/party_menu.c`. Covers eligible entry, eggs/empty slots, exhausted learnsets, non-field menus, facility exclusions, paid/free Resource Mode access, direct level-up entry and selected-mon state, and nine actions with four field moves. The revised direct-entry implementation passes all 12 cases with `make -j4 check TESTS=test/party_menu.c` (nine relearner and three existing navigation cases). `make -j4 modern` completes and generates `pokeemerald.gba`. Window rendering and the return transition remain outside these tests. |
| Documentation organization | **Newest — uncommitted** | Moves release chronology, repair specifications, and historical validation into this history; keeps current feature and bugfix descriptions in the feature reference and records the maintenance convention in the development README. |

These entries record patch contents, not a new test run. The newest commit boundary does not extend the September full-history gameplay audit.

## Modes, progression, and party limits

| Feature | Implementation commits |
| --- | --- |
| Mode selection and startup configuration | `42c5eeeb3d`; Resource/EV startup integration `afe367d583`; level-cap integration `deb19c05ef` |
| Resource Mode: finite TMs, consumable costs, and berry rules | `a9a46378a0`, `16ee6c0fd7`; held-item persistence and wild-consumable transfer repair `0799104ebb` |
| EV Mode and progression-based EV caps | `ffc1ad361b`, `ac1003e4b3`; cap/enforcement restoration `67fd498d45` |
| Restricted Mode battle-item limits and evolution restrictions | Bag-item restriction `51997a50c6`; evolution-move guards `6b6d39460d`; item-evolution guards `bfd34cd4c7`; evolution repair `0c5750859b` |
| Restricted Mode automatic held-item clause | Early implementation `561746c192`; automatic enforcement `ceca765303` |
| Restricted Mode ability and setup limits | Ability Patch guard `5cfb964e71`; Moxie/Defiant/Mirror Herb guards `5bf4ab34f8`; Gorilla Tactics suppresses player Choice Band/Scarf effects `f70470b888` |
| Tiered party budget and display | Display/Tera guards `25cb571c14`; 4–6 point entries `539550a306`; startup integration `eaa0e78e0e` |
| Tier Point enforcement across PC moves, capture, gifts, evolution, and hatching | `d60c8d11e3`, `6eb74a17e9`, `2c1866bd1a`, `f77b3b0562`, `d82ecd712c`, `31521844e7` |
| Ability-aware Tier Points and ability-swap restrictions | `90b834a506`, `f8d55383b9` |
| MaxTierPoints across evolution chains, teaching eligibility, and Mega endpoints | `eb69f0ece0`, `985efb9d37`; source/document consistency `11c627aca2` |
| Progression-scaled split EXP | `b52d7017aa` |
| Strict level caps and scripted level increases | Strict caps `9f05dad927`; additional level-up handling `74890d32a6`; auto-evolution and EXP Candy cap repair `96612a0097` |

## Monotype, encounters, and Terastalization

| Feature | Implementation commits |
| --- | --- |
| Monotype wild encounters and tree encounters | `d3ac7d1908`, `b7dda88681`, `108f3c6b94` |
| Monotype exceptions, evolutions, and split-evolution gender control | `e94b415385`, `fe98227f6f`; Shedinja/type lookup `1d8a0a1b29` |
| Monotype starter/gift options and three-perfect-IV gifts | `62e2a2f856`, `90196177b1`, `c903cefea8`; gift IV fix `1b308fbbbd` |
| Monotype catch-rate floor and fishing guards | `36a4a57e53`, `89eeeb0191`, `17ae9e7921` |
| Monotype startup resist berries | `a3c602a181` |
| Random and curated Tera assignment | `427014b1c5`; main curated pass `e39d21c6d4`; separate distribution data `0d9ccc314a`; fallback refinement `eb69f0ece0` |
| Player Tera, Tera Orb acquisition, and Restricted Tera eligibility | `7fdbe2f144`, `6681292cda`, `74b1d125c6`, `650ed69d0b`, `25cb571c14` |
| Sweet Scent double-encounter chance | `8e5f359474`; state-handling fix `6832160cef` |

## Move services, items, and quality of life

| Feature | Implementation commits |
| --- | --- |
| Menu Move Relearner and Resource Mode costs | `86df472e63`; low-point exception `0c63a31be8` |
| Pokémon Center Tutor | `c8e97f7aea`, `af68b16bc0`, `27b7e29de2`; known-move exclusion `2abeb845d3`; low-point exception `07e26dbde6` |
| Tech House/Tech Tutor and niche-ability tutor | `06038813a6`, `2e29a8037f`, `f23f6aae7e`; two-option/species-specific ability tutor `fcc52a8afa` |
| Dynamic tutor/relearner point awards and later-badge tutor data | `6657c02dbb`, `9e4907f57c`; Beedrill/species exception adjustment `6a75115a04` |
| Mode-dependent TM quantities and HM-to-TM migration | `aa9e68e067`, `4bc8395b06`, `e61b1710a5` |
| Plain, regular, and Gold Bottle Cap services | `0d34f8c366`, `75715dfc19` |
| MenuFly, custom Cut users, and deletable HMs | `3687e49fe5`, `788df3d315`, `cfa37ccd61`, `56d74513dd`; Fly approach triggers `f22ed33b03`; Route 109/Briney failsafe `df7364a608` |
| Pokédex Plus, party nicknames, and Box Link | `aed58485c6`, `9fc23521eb`, `c1e8fd5840`; naming adapted to Expansion `2f4cae0bac` |
| Fake RTC and in-game time advancement | `f92d4c13dd` |
| Reduced egg steps, hatch auto-boxing, and hatch memo | `8109fb58de`, `f77b3b0562` |
| Larger bags and minimum berry yields | `b78bcfe55f` (save-breaking change), `b1569e4087`; later individual berry overrides remain in source |
| Summary IV/EV display and EV redistribution | `0ce0e855df`, `532d14cf37`, `2f4cae0bac` |
| Triumph participation counts and Pokémon Details page | `d81fe4a78a`; restoration/display `6caaf26c77`; Details layout `985efb9d37` |
| Trainer-class pre-battle healing and post-battle sleep rerolls | `8ee8b797ed`, `25abb4daf7` |
| Trainer prize money based on total opposing levels | `c9a5ff44fc`; later restoration included in `085910e20f` |
| Suction Cups fishing rewards and lenient fishing timing | `3e08a521e2`, `17ae9e7921`, `e7bdc4146e`; reward restoration `5d34747fa5` |

## Custom moves and abilities

| Feature | Implementation commits |
| --- | --- |
| Mud Sport/Water Sport protection and AI support | `9b7f7206c0`, `9fe2bc8d56`, `8dc19a1451`, `8911bb3be4` |
| Proactive Color Change, including AI type prediction | `cb993f21b5` |
| Overwhelm Beam: damaging Normal beam with an Insomnia secondary effect | `3c2264d738` |
| Round power boost confined to the current turn | Repair `868293c1c6` |
| Drain Douse | `432b00e197`; loop fix `fe64fecd8f`; move-end absorption rework `f3744907b1`; test/API repair `be3390bd51` |
| Chilling Water bonus for Ice-type users | `67fd498d45` |
| Hail with Snow's Defense boost; affection mechanics removed | `572b2f744f`, `aff25e61b6` |
| Big Root's 40% recovery bonus restored | `b21e72f566` |
| Metal Rush and weight-dependent rider | `c7ee8ad345`, `c5b8784b92`; restoration `fc02d3e737` |
| Improved Stockpile/Swallow and Gluttony synergy | `c3e648e71c`; repairs `8bd215017a`, `9febfb4eb7` |
| Custom Present distribution and Echoed Voice | `dcfdbdf3a6`, `83efbbf34e`, `d2cc2a8bf2` |
| Refresh cures all major statuses; Razor Wind responds to Tailwind | `6fc7851af8`, `ef524ca30f`; runtime restoration `d92f4c0db6` |
| Life Dew singles healing and accuracy-raising Foresight/Odor Sleuth/Laser Focus | `124a4aba4d`, `743e380045`; restoration `085910e20f` |
| Electro Ball/Punishment, Assurance, and species-specific Snore/Bounce changes | `605b212073`, `cbcc6fa700`, `dde6ecbad8` |
| Befuddle, Perplex Dance, and Cut's Grass-target critical bonus | `02b670576c`, `04e8acf271`, `ec25d70aa6` |
| Big Pecks defensive protection and Heavy/Light Metal bounds | `193f287ec2`, `5a7ff5cecb`, `52dcad264b` |
| Honey Gather/Honey rework | `87063ef5b8`; regression repair `23421cb46e` |
| Cute Charm, Frisk, and Illuminate move-category interactions | `8873931270`, `ece86112ff`, `35af2b0ad0`, `d1d3622877`, `51107271f3` |
| Fur Layer/Covered and Solar Core | `751228c71d`, `366e2b0244`, `1460453826` |
| Limber, Truant, Water Veil/Aqua Ring, and Inner Focus/Focus Punch buffs | `7519f785d7`, `aa0fa146fe`, `eecd6f492f`, `892128d5e6`, `5b8a8c64a7` |
| Damp moisture healing | `3a3b1f5373`, `b2b4ebef95`; associated AI `8911bb3be4` |
| Merry and Dedicated | `78fdff7719`, `02d1efbfb3` |
| Astral Charge, Anticipation, and Forewarn | `9fcc4a7c21`, `9129bf865f`, `a9811e3e50`, `1f6633f157` |
| Mystic/Dominate and additional burn-penalty exceptions | Derived abilities `007c0519bb`; Hyper Cutter/Flare Boost exceptions `06ed994876`; restoration `9febfb4eb7` |
| Lucky Chant/Safeguard late-action duration | `04a9726ba9`, `e901c9c6b8`, `5875900b61` |

## Battle AI

The [AI summary](custom_ai_logic_summary.md) expands these entries into per-move rules, knowledge limits, and simulation contracts. “AI” here means the game's battle decision code.

| Feature | Implementation commits |
| --- | --- |
| Hidden STAB inference and non-protecting move knowledge | `59b76d3fcd`, `4bb634c651`; merge repair `829ec9c367`; switching integration `7ee8501957` |
| Smart-trainer policy and repeated-switch immunity prediction | `72a47e0272`, `2a278a5a56`; flags restored `86a1b336ef`; simplification `9335949404` |
| Revealed item history and deliberate full player-item knowledge | `ac7f19cbd6`, `3c07dac5ed`, `6cf60d5e69` |
| Move-effect viability before damage ranking, including residual/binding value | `7a57d6931d`, `d15ae7979e`, `cf246c99c5`, `41dd243ec6` |
| Doubles target coordination and damage optimization | `8d8f319d02`, `a27a48156d`, `7dfb075b05`; restoration `934f83278c` |
| Status, recovery, screens, and setup scoring | `93531a3cea`, `6e5f7576f7`, `50a6b64898`, `9b1bdd30a6`, `08b7585ba5`, `f3fb33af5a` |
| Speed-control thresholds and doubles coordination | `c098ddca1c`, `321ef0e57c` |
| Coaching and reversible stat-change simulation | `4a52d27b94`, `0d40937518`, `a0437698e7`, `0abf70faf9` |
| Defensive Tera simulation and player-Tera information limits | `bd8658f64c`, `10f438d2f0`, `7829b03a9c` |
| Current fast-KO switching with matchup commitment | `53239d220d`; no-effect/pivot handling `9c4b986496`; established commitment reset on player switch `c753e34660` |
| Battle information and damage-debug views | `dea75e5c6d`, `dc794373b3`, `3ee4fe2a78`, `995fbe355c`; runtime debug gate restored `124606eb8c` |

## Maps, trainers, and progression content

| Feature | Implementation commits |
| --- | --- |
| Poryscript foundation and Petalburg Forest route boss Aurelio | `e334707a51`, `3b82402048`; trainer restoration `dcd0380d63` |
| Oldale Ruins, Petalburg Grove, Sandfront, and Rustboro Grass | `04b55fbe93`, `296aa67297`, `d54392a974`, `f8983d2fa6`, `5dcdf0d0e6` |
| Trainer School demonstration, party preservation, egg service, and no-whiteout battles | `941fbf0a7a`, `6a16652bcf`, `4f34de84da`, `753535f4d7`; player-side AI battle backsprites `2c07078933` |
| Dewford Garden, Granite Cave trainers/items, Brawly, and Steven/Tera Orb | `6ebe9e4727`, `7ba108e51d`, `b0d0411d10`, `02a4e753c6`, `74b1d125c6` |
| Dewford Delibird, Good Rod, and Rustboro trade Monotype gate | `1b308fbbbd`, `22104fc029`, `0d3bdfec64` |
| Cindy progression rematches | `ed8ec1d021`; badge-query fix `75cd496b13` |
| Petalburg Grove Birch scene and second-badge cleanup | `b565b3eb80`, `2521e0ed74` |
| Route 109 boss Cassia, beach trainers, and Edmond's doubles reward | `619a0447de`, `01a1b06c9a`, `ec25d70aa6`, `591b03388a` |
| Mirage Island portal, dedicated map section, and legendary rolls | `7fc131b6ed`; BST threshold adjustment `686c22eab6` |
| Flannery's non-terrain fog | `48bf87b52a` |

## Developer tools and restoration milestones

| Change | Commits |
| --- | --- |
| Trainer documentation synchronized from marked party sections | `f1c9171da6` |
| Trainer-set diversity analysis | `9deecbc424` |
| Source-backed encounter and item-acquisition documentation automation | `5251c8f9ee`; item-rendering refinement `483b1ef9ac` |
| Learnset and move-analysis tools | `7f09ab2b83`, `8a558241f7`, `017a1b8384`; off-type analysis `6657c02dbb` |
| Defensive typing/STAB wall rankings | `80004d3f08` |
| Unconventional first-stage level-1 move analysis | `9c12ae6d16` |
| Post-upgrade player palette and HP-bar color fixes | `38bad90219` |
| Historical feature restorations and regression coverage | `d92f4c0db6`, `0c5750859b`, `3cbf01e171`, `9febfb4eb7`, `085910e20f`; final fixture/commitment corrections `9c4b986496`, `c753e34660` |

## Reworked approaches

- Clean-state/literal-lead fast-KO switching (`6f1d67a6f4`, `8d856e4bcf`, `4547aff533`) was removed in `5440fb44b4` in favor of weather-setter preservation. Matchup commitment (`53239d220d`) later replaced that separate preservation path. 
- Fishing briefly prevented fish from escaping (`bd0ec22dae`). The later design (`e7bdc4146e`) restored failure while making timing more lenient.
- The standalone host-driven AI-versus-AI simulator began in `9ebc494153` and was removed in `9c4b986496`. The in-game AI-versus-AI battle mode remains separate and supported.
- PC access through the Pokénav (`4a17ce7633`) was replaced by Box Link (`c1e8fd5840`).

## Archived audit and upgrade records

The following records were moved from the feature reference. Test counts and build-success statements describe the historical runs reported by those notes, not current-working-tree validation. Their September audit boundary remains unchanged; then-pending repairs are historical unless listed under Newest changes above.

## Historical audit notes (September 2026)

- Latest commit whose applicable project changes have been reviewed for this dossier: `9c4b986496` (`Remove the AI v.s. AI simulator and make modifications for test passes`).
- Follow-up: `c753e34660` committed the forward-audit refinement and focused fixture corrections described below.
- **History audit through `9c4b986496` (2026-09-07):** every zenmodeman-authored commit from the first project change `f5a841eef6` (`Test ReadME commit`, 2023-12-31) through `9c4b986496` has been reviewed. The backward pass compared each surviving feature with current runtime/data/script anchors and existing `Elastic-tests:` coverage; merge/build-only commits and historical balance values superseded by later zenmodeman commits were not frozen into tests. The subsequent forward pass reviewed every commit added after the audit originally began, so no committed history remains unchecked at this boundary.
- **Forward-pass inventory:** the reviewed commits cover encounter and item-acquisition documentation automation, item and fishing-encounter changes, learnsets, Route 109 trainer and Cut-critical behavior, trainer level scaling and Rare Candy caps, Edmond's reward, Beedrill/tutor eligibility, Triumph and Stats Details, MaxTierPoints and teaching/Tera eligibility, fast-KO matchup commitment, Restricted Mode's Gorilla Tactics/Choice-item suppression, Tier Point documentation, and the latest restoration set. Existing focused regressions cover the surviving behavior; stale expectations exposed by the aggregate run were corrected.
- **Forward-audit result:** commit `9c4b986496` contains the trainer-scaling EXP fix, protected/no-effect commitment guard, pending-commitment pivot reset, stale Tera/tutor/Tier Point expectation updates, and removal of the standalone host-driven AI-versus-AI simulator, generated matchup output, runner support, and dedicated tests. The refinement committed in `c753e34660` clears an already-established opponent commitment when the player changes the matchup; focused Protect and pivot fixtures were adjusted to isolate the intended switching preconditions. The in-game AI-versus-AI battle mode and its unrelated presentation/script behavior remain supported. The audit reported that the complete aggregate passed all 451 `Elastic-tests:` tests.
- The post-1.16.2 test-build repair updates the Toxic and Sheer Cold test-only move-property overrides to pass the renamed `B_*` configuration identifiers through `GetConfig`.
- The post-1.16.2 warning cleanup removes explicit `waitstate` commands after specials whose `data/specials.inc` definitions now provide `waitstate=1`, and includes `item_menu.h` where Pokémon form-change code reads `gSpecialVar_ItemId`.
- The party-API warning cleanup replaces deprecated player- and enemy-party compatibility macros in C sources with indexed `gParties`/`gPartiesCount` access for `B_TRAINER_PLAYER` and `B_TRAINER_OPPONENT_A`.
- The tutor-data parser repair corrects the Tech Tutor six-badge array's integer type, restores terminators on the final three Resource Mode TM-trade arrays, and terminates the added seven-badge Tech Tutor array so the including `pokemon.c` translation unit parses correctly.
- Commit `67fd498d45` restores the custom badge-based per-stat cap, its derived total cap, the EV Mode gates on battle EV gain, EV items, and trainer EV spreads, and the matching Summary Screen redistribution limit after these hooks were displaced by an upstream Pokémon-core merge.
- Commit `0799104ebb` restores Resource Mode's post-battle held-item persistence gate after the upstream Gen 9 restoration rewrite: ordinary consumable activations cost the item only in Resource Mode, while Knock Off, Fling, and theft do not permanently cost the player their original item. The Resource Mode consumption gate takes precedence over the generic trainer-battle item-return fallback. Battle initialization clears the complete per-party `partyState` and `itemLost` arrays before recording original items so stale `isKnockedOff` or `stolen` bits cannot leak across battles. The repair also prevents consumable held items from moving from wild Pokémon to the player through Thief/Covet, Trick/Switcheroo, Magician, Pickpocket, Pickup, Bestow, and shared steal paths; non-consumable transfers and immediate consumption such as Bug Bite/Pluck remain legal.
- Commit `5875900b61` restores Lucky Chant's three-turn Dedicated extension and its additional turn when every living opponent has already acted. Safeguard now follows the same late-action rule so both five-turn protections provide five full subsequent turns when established after the opposing side has finished acting.
- The same repair adapts the Infiltrator/Mist tests from the removed `EFFECT_DEFENSE_DOWN_2` constant to `ASSUME_STAT_CHANGE`, preserving the sharp Defense-drop contract under the unified stat-change move effect.
- AI regression tests now use the unified stat-minus additional effect and the upstream `AI_FLAG_ASSUME_STAB` knowledge path instead of the removed `MOVE_EFFECT_SPD_MINUS_1` and `GetMovesArrayWithHiddenSTAB` APIs.
- The Coaching AI regression likewise uses `ASSUME_STAT_CHANGE` instead of the removed dedicated `EFFECT_COACHING` constant.
- Commit `d92f4c0db6` adds 20 scenarios for Tier Point normalization across Scatterbug, Spewpa, Squawkabilly, Pumpkaboo, Gourgeist, Flabébé, Floette, and Florges forms; Politoed, Pelipper, and Vulpix ability-dependent costs; non-linear badge EV-cap state; Normal, Electric, Ghost, and Dragon monotype resist-berry derivation; independent and egg-separated Restricted Mode item-clause groups; and null/egg free-tutor eligibility. The targeted `Elastic-tests: Merge guard:` suite passes all 55 cases.
- The same commit's second 20-scenario audit found and repaired post-1.16.2 runtime-hook losses for Solar Core's sun-based special multiplier, Limber's Speed-drop immunity, Inner Focus preserving Focus Punch, Truant's three-quarter Slack Off healing, Razor Wind firing immediately under Tailwind, Refresh curing every major status despite sleep/freeze/paralysis, and Big Pecks preserving physical defensive stages and screens against critical hits and Chip Away. Negative controls cover physical Solar Core attacks, weather suppression, self-inflicted Limber drops, ordinary Focus Punch/Slack Off, and special critical hits through Aurora Veil. All 183 `Elastic-tests:` cases pass after the repairs.
- Commit `0c5750859b` restores Restricted Mode's item-evolution minimums: level 25 for Nidorina and Nidorino, and level 32 for Slowpoke, Galarian Slowbro, Kadabra, Graveler, Machoke, and Haunter. The guard applies when an item is consumed while item eligibility checks still expose the evolution, allowing the Party Menu to show `NOT READY`. It also restores Golbat's level-30 Restricted Mode condition alongside friendship. Twenty `Elastic-tests: Evolution restrictions:` scenarios cover enabled and disabled Restricted Mode, threshold boundaries, unrelated item evolutions, preserved item-check visibility, Woobat and Golbat friendship gates, Fire/Flying/Water/incompatible Monotype gates, and combined Restricted-plus-Monotype state; all 20 pass.
- The historical audit added regression contracts for Route 109 trainer scaling and its Briney Fly failsafe, Cassia's route-boss healing classification, the Rival 110 and Champion cap milestones, Edmond's two-opponent reward discriminator, Perplex Dance's AI decision rules, unconditional and effect-revealed player-item knowledge, smart-trainer flag composition, partner-aware doubles Speed control, Sport/Damp protection and pivot scoring, raw-stat screen inference, Defense Curl/Rollout survival scoring, Mystic, Dominate, Astral Charge, Merry, and Dedicated behavior and species assignments, dynamic tutor/relearner point awards and free-service thresholds, the niche-ability tutor, Oldale, Petalburg Grove, Dewford Garden, Granite Cave, Rustboro trade, Good Rod, Dewford Delibird, Dewford Center's tutor and Float Stone hint NPCs, Route 104 rival rewards, and custom Scyther Cut compiled content, trainer-class healing, post-battle sleep rerolls, Triumph attribution and awards, Restricted Mode's Defiant, Moxie-family, Mirror Herb, item-evolution, friendship-evolution, and walking-evolution limits, Summary Screen EV redistribution, Suction Cups fishing rewards, shortened fishing rounds, extended reel windows and near-completion input grace, one-shot Sweet Scent double encounters, monotype split-evolution genders, Tier Point capture, hatch, PC, and ability-change projections, Water Veil's Aqua Ring recovery, the custom Swallow/Stockpile/Gluttony rules, custom Present distribution, custom move accuracies, powers, and Sport priority, Roost/Nature Power/Trick/Power Split TM assignments, Tech Tutor tiers including Twister's later one-badge placement, ground-TM quantities, Comet Shard pricing, three-perfect-IV scripted gifts, Hyper Cutter/Flare Boost burn exceptions, cost-free Tera Orb charging, curated/random/Monotype Tera assignment, stored Tera creation data, Restricted Tera ability exceptions, Snorlax's Snore bonus, the Spoink line's Bounce bonus, surviving early species-stat and evolution-level rebalances, the Demo 2 species redesigns, Badge 2 Beautifly/Dustox abilities, Beautifly's Mud-Slap compatibility, Wurmple and Nincada mode-specific evolution branches, representative original 4–6 point species, Flash's badge exception, Flannery's non-terrain diagonal fog, Route 106's Dive Ball, Dewford/Granite encounter rosters, Forewarn's warned-move reduction, the complete illuminating/enticing/item-interacting move categories, Illuminate's spotlight and split accuracy contract, Cute Charm's enticing debuff amplification, Frisk's item-interacting sure-hit rule, and Truant's Stomping Tantrum synergy. The targeted subsets pass all 183 exercised cases. The audit repaired the missing terminator in the niche-ability tutor's species-exception table and restored merge-lost Triumph accounting, Restricted Mode stat-boost guards, Water Veil/Aqua Ring synergy, monotype wild-gender forcing, Tiered capture and hatch auto-box integration, Tiered Ability Capsule/Patch guards, doubles redundant-Speed-drop suppression, improved Swallow/Gluttony, custom Present roll thresholds, Rock Throw's perfect accuracy, Hyper Cutter/Flare Boost burn exceptions, Mystic's shared Psychic modifier, Dominate's Download-like switch-in dispatch, Merry's gifting flags and activated power/accuracy/Speed modifiers, Dedicated's weather/terrain/screen/room/protection/Tailwind/Sport extensions, raw-stat screen inference, Defense Curl's Rollout survival gate, effect-revealed Float Stone/Eviolite/Assault Vest recording, custom fishing timing and input grace, the Sport/Damp AI rules, the complete curated Tera assignment hook/table, the species-specific Snore/Bounce modifiers, Beautifly's generated Mud-Slap compatibility, Forewarn's switch-cleared warned-move state plus shared damage modifier, strict Monotype branch selection without changing permissive Monotype eligibility guards, non-Resource ground-TM quantities, three-perfect-IV scripted gifts on the current parameterized creation API, diagonal-fog terrain exclusion, Comet Shard pricing, Mud/Water Sport priority, Present/Air Cutter/Snarl plus Fire Spin/Arm Thrust/Trop Kick move data, the three custom move-category tables and their ability hooks, Illuminate's intended evasion-piercing without accuracy-drop immunity, and Truant's failed-action handoff to Stomping Tantrum.
- Count correction through the late-December 2024 slice: the targeted historical subsets now exercise 198 cases (409 cases in the full `Elastic-tests:` aggregate), superseding the 183 figure embedded in the inventory paragraph above.
- The December 7 backward slice adds four contracts for Youngster James's Petalburg Woods object/rematch identity and Powder scoring with incomplete versus complete non-Fire move knowledge. It restores `HasAllKnownMoves` on the current AI knowledge API so an unrevealed move slot is not treated as evidence that Powder is useless. The intervening `1b5639df4e` merge-repair changes were either build/API adaptations or behavior already represented by later tests and implementations.
- The completed 2023–2024 backward slice adds map contracts for Bug Catcher Lyle, Petalburg Woods and Route 104 custom items, every Tech House tutor/guide plus both exits, and Aurelio's founding Petalburg Woods route-boss object. It also restores three merge-lost mechanics on current APIs: trainer prize money uses the sum of all opposing party levels (with the original single-opponent doubles multiplier), Life Dew heals one third when no ally is present and one quarter with a doubles partner, and Foresight, Odor Sleuth, and repeatable Laser Focus each raise the user's Accuracy. Targeted regression tests cover all of these contracts.
- I advance the documented boundary with reviewed changes and reconcile pending-work notes with their actual commits.

## Tag-Partitioned Custom Implementation Trace

This section groups the major custom implementations by Elastic Emerald release tag. Entries are grouped by where the implementation first appears in history; later fixes may be listed in a newer tag range or in the merge-regression ledger below.

### Up To `v0.1.0`

Major systems and mechanics:

- Initial content and scripting foundation: Poryscript setup, Petalburg Forest route boss, Sidney singles/doubles teams, early route content, Oldale Ruins, Petalburg Grove, Sandfront, Rustboro Grass, Trainer School flow, no-whiteout battles, AI-vs-AI player-side backsprite support, and early demo/progression guards.
- Mode framework: monotype selection, Resource Mode, Restricted Mode, EV mode, progression-based EV acquisition, truck-start variables/flags, mode-aware Oldale mart logic, Resource Mode berry/TM/consumable behavior, and mode-specific starter/gift setup.
- Monotype encounters and gifts: type-filtered wild encounters, tree encounters, monotype exceptions, monotype evolution handling, gender forcing for split-evolution lines, monotype catch-rate support, monotype starter expansion, and monotype-aware `givemon` improvements.
- Tutor and acquisition systems: Menu Move Relearner, Center Tutor data structure and resource logic, Tech Tutor/Tech House, already-learned Center Tutor count exclusion, Hyper Training/Bottle Cap NPCs, and custom gift IV shuffling.
- Tera framework: random/curated Tera assignment, Tera Orb teaching/charging, player-side Terastallization logic, and AI safeguards around pre-emptive player Tera calculation.
- AI foundation: item-clause support, double-target KO de-incentivizing, faster-attacker logic, Knock Off/Parting Shot/status scoring tweaks, Hidden STAB and non-protecting move helpers, move-effect viability before best damage, smart trainer flags, move history for Soak/Aqua Ring targeting, and early switch/immunity prediction work.
- Battle mechanics and ability work: item restore/prevent keeping trainer items, Life Orb recording, Summary Screen IV/EV display, Mud Sport and Water Sport protection changes, Hail/Snow defense behavior, trainer money formula by total levels, Pinch Berry healing, accuracy boosts for Foresight/Odor Sleuth/Laser Focus, Life Dew singles healing, Big Pecks defensive buff, Honey Gather/Honey rework, Heavy/Light Metal bounds, Electro Ball/Punishment changes, and initial Drain Douse.
- QOL and overworld: MenuFly, custom Cut HM users, HM deletion, Pokedex Plus, Party Nickname option, Box Link work/reversion, Fake RTC and time advancing, reduced egg steps, larger bags, minimum berry yield, fishing/content scripts, and map menu flag cleanup.
- Content-scoped systems that can still affect mechanics: early Route 101/102/104/115/116, Petalburg, Rustboro, Oldale, Sandfront, Trainer School, Aurelio, Cindy, Darren, Birch aide, and Roxanne checks.

### `v0.1.0` To `v.0.1.1`

Major systems and mechanics:

- Custom Cut HM use: field-effect generation, designated/custom mon Cut behavior, Cutter and Fly Rider dialogue support, and HM deletion support.
- Restricted Mode evolution-move guards and Move Tutor adjustments.
- AI and move-helper refinements: `IncreaseStatUpScore` stat-constant parameterization, monotype catch-rate/AI refinements, and miscellaneous move/learnset/script adjustments that support early-game systems.
- Rustboro/Sandfront content hooks: Roxanne first-battle check, Rustboro Center/Mart changes, and Route 115/116/Sandfront map/trainer integration.

### `v.0.1.1` To `v.0.1.2`

Major systems and mechanics:

- QOL/menu additions: Pokedex Plus, Party Nickname option, and Box Link.
- Tech Tutor and ability-tutor expansion: Niche Ability Tutor in Tech House, Tech House dialogue work, and Tech Tutor slot-fix follow-up.
- Restricted Mode ability-item guards: early Ability Patch guard work.
- New or modified ability mechanics: Covered/Fur Layer as Shield Dust clone, Solar Core, Frisk item-move modification, Limber speed-drop immunity, Truant Slack Off healing, Suction Cups starting-item and fishing refinements, and Water Veil/Aqua Ring interaction.
- Move and battle-mechanic updates: Mud Sport/Water Sport type checks, Assurance hurt tracking and accuracy component, Enticing/item-interacting move flags, monotype fishing guards, sweeping minimum monotype catch rate, and wild table expansion.
- Demo/progression/content support: demo guard, Devon Hyper Training dialogue, Wally duplicate fix, Rustboro mart fix, map/item/trainer adjustments, starter learnsets, tutor/encounter/evolution checks, and documentation checkpoint.

### `v.0.1.2` To `v.0.1.2.1`

Major systems and mechanics:

- AI upgrades: damage-optimized doubles targeting, GapThreshold fix, Illuminate rework and illuminating move category, and `IncreaseStatUpScore` change-id/stat handling.
- Ability and mechanic updates: Damp healing on switch-in against Rain/Water Sport, after-resolution Damp healing trigger, Truant `lastMoveFailed` logic, Razor Wind skipping recharge under Tailwind, and affection mechanic removal.
- Merge and script repairs: Tech Tutor var-order fix, truck dialogue fix, hidden-STAB read restoration, and post-merge adjustment commits.
- Content hooks: Dewford Garden starting content, overworld Sweet Scent doubles chance, Aurelio tweaks, Index Land slot completion, and trainer/move tweaks.

### `v.0.1.2.1` To `v.0.2.0`

Major systems and mechanics:

- Dewford/Gym 2 expansion: Dewford Garden, Granite Cave trainers/encounters/items, Brawly Gym script, Steven's Room/Tera Orb, Dewford Delibird gift, Rustboro trade monotype guard, Good Rod/fishing changes, Cindy level-increasing rematches, and demo `v0.2.0` guards.
- AI and switching: Hidden STAB switch logic, smarter speed-control logic, doubles preference logic for self-benefitting move effects, switch prediction for immunity abuse, defensive Tera calculation, smart Tera/switching adjustments, Coaching AI, simulated stat-change apply/reverse helpers, Reflect/Light Screen/Recovery/Rest/Defense Curl AI tuning, Paralysis/Leech Seed scoring, sport/Damp healing AI, OHKO switch timing, and Collector Darren AI.
- New or modified abilities: Merry activates from Present, Heal Pulse, or Bestow and boosts power, accuracy, and Speed by 50%; Dedicated extends weather, terrain, screens, rooms, side protections, Tailwind, and Sport fields by three turns; Inner Focus prevents Focus Punch loss; plus Astral Charge, Anticipation damage reduction, Covered rename, Forewarn modification, extra burn-damage-reduction exceptions, and additional derived ability work.
- Move and battle mechanics: Metal Rush, Present formula, more accurate Echoed Voice with battle-struct support, Refresh full-status/unblockable behavior, Drain Douse infinite-loop fix and later move-end absorb rework, Stockpile/Swallow/Gluttony synergy, Restricted evolution-item guards, custom move tests, Snore/Bounce groundwork via species changes, and Lucky Chant follow-up after the tag.
- Improved Swallow heals one third of maximum HP per Stockpile, consumes only the minimum Stockpiles needed for the missing HP, removes only the matching Defense and Special Defense stages, and preserves its counters when used at full HP. Gluttony doubles healing per Stockpile and doubles Spit Up's base power. AI recovery estimates mirror the one-third/two-thirds/full progression and Gluttony multiplier.
- Present uses a custom outcome distribution: rolls 0–49 select 40 power, 50–203 select 80 power, 204–228 select 120 power, and 229–255 heal. Expansion's move-resolution refactor reverted those thresholds to vanilla values until the historical audit restored them at the new resolver and added boundary contracts.
- Burn does not halve physical damage for attackers with Guts, Hyper Cutter, or Flare Boost. The latter two project exceptions were lost when damage calculation moved to `DamageContext`; direct ability and ordinary-ability controls now protect the shared live/AI modifier.
- Tier Points and restricted Tera: Tier Point display, catch/gift/evolution/PC/withdraw/empty-slot guards, 4-6 point values, Shedinja monotype/tier logic, truck-start integration, Restricted Mode Tera guard, and White Herb florist progression change.
- Curated Tera: main curated Tera pass, monotype-aware curated/random Tera behavior, curated species adjustments, and Rustboro/Steven/Tera teaching content.
- QOL and progression: auto-boxing egg hatches, improved egg hatch memo, item recording for defensive items, NPC level badge checks via `FlagGet`, fishing leniency restored, and miscellaneous freeze/flow fixes.

### After `v.0.2.0` / No Elastic Tag Yet

Major systems and mechanics:

- Upstream expansion merge survival: merges through `expansion/1.12.0`, `1.12.1`, `1.12.2`, `1.12.3`, `1.13.0`, `1.14.0`, and `1.14.4`, followed by several custom repair commits.
- Tier Points refinement: ability-aware point computation, ability-swap prevention, curated Tera/tier point tweaks, one-tier-point Center Tutor exception, restored Summary Screen tier point display, restored catch logic after `expansion/1.14.0`, and current party/PC/evolution/gift/tutor guard anchors.
- Item and mode refinements: Restricted Mode automatically enforces item clause before trainer battles by bagging duplicate held items in party order, monotype truck setup seeds the PC with resist berries for types super-effective against the chosen monotype, and Big Root drain recovery is buffed to 40%.
- AI refinements and tests: revealed-KO/lead/quad-effective fast-switch conditions, Dig switch removal, Sweet Scent double-battle static state, smarter double Rock Tomb logic, simulated stat-change guards/reverse fix, Wrap/binding best-damage work, Magic Guard and damage-gap exceptions, player held-item knowledge, resist-berry two-turn damage comparison, AI test additions, trainer flag restoration after merge breaks, and a simplified immunity-switch prediction rework for repeated player switch cycles.
- Move and ability regression repairs: improved Swallow logic after upstream refactors, Honey Gather regression repairs, binding and Drain Douse test repairs, Aqua Ring bonus-effect cleanup, extra Suction Cups restoration, species-specific Snore/Bounce modifications, Lucky Chant turn/priority adjustment, and post-merge minor patches.
- Data/mechanic standardization: standardized EV acquisition items and prices, Center Tutor/Brawly Combusken tweaks, Triumph counts, and several freeze-scenario fixes.
- Overworld fail-safes: Fly menu use from Route 109 can return Mr. Briney to Dewford when Slateport is not yet visited, preventing the early MenuFly softlock state where Briney remains stranded on Route 109.
- Documentation: feature summary/dossier material was consolidated into the development references.

## Merge Regression And Rework Ledger

- The FRLG integration merge collides with Elastic Emerald identifiers in shared numeric namespaces. The resolution retains `BATTLE_TYPE_AI_VS_AI` on bit 28, uses bits 29/30 for FRLG ghost/Pokédude battles, and separates continue-after-loss mode 14 from early-rival mode 15. Emerald's custom flags `0x20`-`0x2B` remain in the non-FRLG branch, and the Ruin Maniac palette follows the imported FRLG palette range. I track these namespaces because duplicate numeric values can survive a textual merge.
- The FRLG integration updates `tools/mapjson` so every layout record requires a nonempty `layout_version`. Older Elastic Emerald layouts use `"layout_version": "emerald"`; otherwise map-source generation stops before compilation with `Value for 'layout_version' cannot be empty.`

Confirmed later-merge breakages already repaired in history:

- Hidden STAB move reading was broken by a merge and restored in `829ec9c367`.
- Tech Tutor var/slot ordering broke and was repaired in `bb06e1f632` and `e670a4e65b`.
- Scyther Cut event script was lost and restored in `f6508306a4`.
- Improved Swallow logic was broken by upstream battle refactors and repaired in `8bd215017a`.
- The post-1.16.2 move-resolution rewrite displaced that repair again; the historical audit re-ported partial Stockpile consumption and stat-stage removal, full-HP preservation, Gluttony healing and Spit Up power, and aligned AI healing estimates onto the current battle pipeline.
- Honey Gather regressed and was repaired in `23421cb46e`.
- After `expansion/1.14.0`, monotype filtering, non-monotype modulus behavior, Tier Points catch logic, extra Suction Cups behavior, AI flags, candy cap logic, and Aqua Ring bonus-effect cleanup needed restoration in `5b2db2f453`, `448477bf2e`, `4038c36be7`, `5d34747fa5`, and `86a1b336ef`.
- After `expansion/1.14.4`, additional minor custom-functionality patches landed in `9865fe909f` and `0cf4955fd9`.
- During the first `expansion/1.15.0` merge portion, the new generational-config API required bare tags in `GetConfig`, level-cap calls gained an explicit hard/candy-cap argument, and variable config tags required `GetConfigInternal`. The merge also displaced Metal Rush's weight-dependent additional effect, full player held-item AI knowledge, repeated-switch immunity prediction, and weather-setter preservation; these were restored during the merge on the 1.15 runtime and AI APIs. Incoming-mon prediction compares damaging moves against the temporary predicted battler before restoring the active battler and cached AI damage data. Expansion 1.15's `HandleKOThroughBerryReduction` now provides the consumed-resist-berry follow-up damage model, replacing the role of the older local temporary-hold-effect simulator.
- During the `expansion/1.16.2` merge, broad upstream rewrites conflicted with Elastic Emerald's battle, AI, mode, content, and generated-data files. The resolution used the rewritten upstream battle and AI cores as the framework base, re-ported Drain Douse, Illuminate, Merry, Honey Gather, trainer PP Ups, mode/evolution hooks, and project tuning onto their new APIs, and accepted the upstream deletion of generated `src/data/trainer_parties.h`. The upstream AI now carries dynamic scoring/switch callbacks that were previously local. The custom smart-trainer information policy remains composed from prediction and assumption flags rather than upstream omniscience and PP-stall prevention. I include this flag composition in semantic review even when `include/constants/battle_ai.h` merges without textual conflict.
- Merge `13802b4566` accepted Expansion's Pokémon-core EV-cap path without re-porting Elastic Emerald's `GetEVStatCap()` contract. Commit `67fd498d45` restores EV Mode's per-stat progression of 36 before badge 1, then 48/84/120/156/192/228 through badges 1-6, and 252 from badge 7 onward. Its total cap remains `2 * per-stat cap + 6`. Outside EV Mode, battle EV gain and positive EV-item effects are disabled, and trainer-authored EV spreads are not applied. Summary Screen EV redistribution conserves the Pokémon's original EV total and keeps every stat within the custom per-stat cap rather than Expansion's `GetCurrentEVCap()`, which represents a total EV cap. The shared validator and four `Elastic-tests:` cases pin those rules at zero- and one-badge boundaries.
- Poryscript specials declared with `waitstate=1` in `data/specials.inc` emit their own wait state. An adjacent explicit `waitstate` is redundant and produces an assembler warning; remove the explicit command from the `.pory` source and regenerate its `.inc`. The post-1.16.2 cleanup applies this to party selection, trade scenes, berry selection/watering, and Pokenav tutorial specials. The same cleanup replaces `src/pokemon.c`'s ad hoc `gSpecialVar_ItemId` declaration with the public declaration from `item_menu.h`.
- Expansion's compatibility declarations mark `gPlayerParty`, `gPlayerPartyCount`, `gEnemyParty`, and `gEnemyPartyCount` deprecated. The replacement accessors are `gParties[B_TRAINER_PLAYER]`/`gPartiesCount[B_TRAINER_PLAYER]` for the player and `gParties[B_TRAINER_OPPONENT_A]`/`gPartiesCount[B_TRAINER_OPPONENT_A]` for legacy enemy-party call sites; stale macros surface as pointer deprecation warnings at each use.
- The same merge restored the upstream compile-time `DEBUG_BATTLE_MENU` guard in `HandleInputChooseAction`, disabling Select because Elastic Emerald intentionally keeps that flag false. Commit `124606eb8c` restored entry through `IsDebugModeEnabled()`, but that runtime entry gate also blocked the non-debug battle info menu. Select now opens the shared menu regardless of Debug Mode; `CB2_BattleDebugMenu` sets `readOnly = !IsDebugModeEnabled()` to select battle info with editing disabled or the full debug menu. The runtime mode check should be kept inside the menu rather than gating the Select action, so both saved Debug Mode settings retain access.
- Binding, Wrap, and Drain Douse tests required post-merge fixes around `bd83b55fb4`, `c701193e0d`, and `be3390bd51`.
- A post-1.15 test-ROM build found that Forewarn's tests and deterministic tie handling had survived on opposite sides of the merge: the tests referenced `RNG_FOREWARN`, while the runtime had reverted to pairwise untagged randomness and lacked the empty-candidate guard. The repair, recorded as pending during that audit, restores the tagged uniform tie selection and its RNG constant. The same build found stale tests for removed generational keys (`B_INFILTRATOR_SUBSTITUTE`, `B_TAUNT_ME_FIRST`, `B_BATON_PASS_TRAPPING`, `B_PSYCH_UP_CRIT_RATIO`, and four Transform failure keys) plus renamed move target/effect APIs; those tests now assert the current fixed behavior or current helper names.
- An earlier post-1.15 audit temporarily restored `GetMovesArrayWithHiddenSTAB`; the 1.16.2 adaptation supersedes that helper with upstream `AI_FLAG_ASSUME_STAB` move-history inference and updates the custom regression accordingly.
- The broad `Elastic-tests:` test-build audit repaired the remaining custom regressions across hard level caps, Anticipation, Astral Charge, defensive contact abilities, Honey Gather, Heavy/Light Metal (with Light Metal capped at 40 kg), Drain Douse, Metal Rush, Mud/Water Sport, repeated-switch prediction, and weather-setter preservation. Follow-up batches pin Restricted Mode item-clause enablement, ordering, egg/empty-slot handling, uniqueness and idempotence; Tier Point totals, projections, egg exclusions, and alternate-form normalization; invalid/disabled monotype values; Damp moisture healing and suppression; Honey Gather suppression and Magic Room; Metal Rush's weight modifiers, stat-loss defenses, Protect, Mirror Armor, and Contrary interactions; Drain Douse type rates, Substitute/immunity/multi-hit handling, Big Root scaling, Heal Block, Magic Guard, lethal hits, duplicate application, switch cleanup, native-drain stacking, spread targets, Protect, Liquid Ooze, and full-HP behavior; plus weather preservation's Speed and Focus Sash gates. All 139 current custom/merge-guard cases pass after the post-1.16.2 repair. Several failures were stale fixtures rather than runtime defects, while genuine merge regressions included lost end-turn ability dispatch, battle-state targeting memory, switch-candidate fallback, sport status prevention, weight bounds, custom move/ability hooks, and Resource Mode held-item restoration being overridden by the generic trainer-battle fallback.
- The third Drain Douse boundary batch exposed that `GetDrainedBigRootHp` had reverted from Elastic Emerald's documented 40% recovery bonus to Expansion's 30% value. Commit `b21e72f566` restores the `1.4` multiplier in the shared runtime helper and updates the native Big Root tests for absorbing moves, Liquid Ooze, Leech Seed, Ingrain, and Aqua Ring to the project contract.
- The fifth batch found that Damp's custom Water Sport recovery did not honor Heal Block and that Metal Rush's guaranteed weight rider was marked `certain`, unintentionally bypassing Clear Body-style stat-loss prevention. The repair, recorded as pending during that audit, gates Damp healing on the current Heal Block volatile and keeps Metal Rush guaranteed while allowing the normal stat-change pipeline to enforce immunity, Mirror Armor, and Contrary. Drain Douse intentionally follows the native absorb convention of not draining Substitute damage.

Current audit status from static symbol scans:

- Monotype, Tier Points, curated Tera, Restricted/Resource gates, Drain Douse, custom abilities, and smart AI systems all still have live data and runtime anchors in current `include`, `src`, `data`, and `test` scans.
- Drain Douse still injects through `MOVEEND_ABSORB` and still has script/message/test anchors. Its formerly commented advanced tests are now active and adapted to the current test API; the runtime processes spread damage once per opposing target, excludes the attacker's ally, and retains a move's native drain alongside Drain Douse.
- Tier Points catch/gift/evolution/PC/tutor/ability-change paths are present, including `gExcessTierPoints`, Summary Screen display, and one-point Center Tutor exceptions.
- AI prediction and smart switching still retain `AI_FLAG_PREDICT_SWITCH`, `AI_FLAG_PREDICT_INCOMING_MON`, `AI_FLAG_SMART_TERA`, `GetMostSuitableMonToSwitchInto`, and `ShouldSwitch` hooks, plus tests for prediction and smart Tera. Held-item awareness now also feeds damage simulation for player-side items, including resist berries.

Likely rework candidates:

- Tier Points now compute with ability awareness, but the point table itself is still hand-coded in `src/elastic_emerald_pokemon.c`; a structured species-side table is a possible future direction if richer metadata or additional form/ability exceptions make it worthwhile.
- Curated Tera is still centralized in code; as curated lists grow, a data-driven species table would make merge conflict resolution easier than editing a large switch/list in `src/pokemon.c`.
- Monotype exceptions and gender-forced split-evolution handling are runtime helpers in `src/wild_encounter.c`; native encounter filters or richer evolution-family predicates could eventually replace some of this custom handling.
- Drain Douse's current `MOVEEND_ABSORB` integration is the right post-refactor shape, with active regression coverage for double/spread, mixed Liquid Ooze, native-drain, Protect, current-attacker, and full-HP semantics.
- Smart AI systems are extensive and merge-sensitive. I adapt these helpers to newer damage, switching, and Tera utilities as upstream APIs evolve.

## Expansion 1.15/1.16 Port Build Findings

The 1.15 and 1.16 merge builds exposed several custom systems whose callers or data survived while their implementation hooks were lost. The ports restore:

- MAP/FLY start-menu labels and the Fly error script export.
- Suction Cups fishing item rewards on a failed bite.
- Trainer PP Ups, NPC center tutors, resource-mode relearner/tutor costs, and the item-clause party special.
- Restricted-level and monotype evolution conditions, including a missing break that previously fell through to the region condition.
- Tier-point calculation/party enforcement, egg/evolution auto-box support, and monotype lookup in `src/elastic_emerald_pokemon.c`, separated from the heavily rewritten upstream Pokémon core.
- Drain Douse and Damp healing battle-script commands/flow, plus Honey Gather, illuminating, and Merry move-end effects. The delayed stolen-item handoff still blocks Pickup, Harvest, Recycle, and Symbiosis until the item is assigned at move end.
- The custom AI/runtime ability-block query used by repeated-switch immunity prediction, adapted to the 1.15 move-resolution APIs.
- Correct player backsprite palettes during battle intros. `gTrainerBacksprites` uses full `enum TrainerPicID` designated indices, so callers index it without subtracting `TRAINER_PIC_FRONT_COUNT`. The backsprite palette loads once through `LoadSpritePalette`, and trainer draw/slide paths select it with `IndexOfSpritePaletteTag`. A duplicate allocation during ball throw is unsafe because fixed OBJ palette slots can be overwritten or reused during the intro.
- Correct HP-bar colors for low-HP, low-level battlers. When maximum HP is below the 48-pixel health-bar width, the animated current value is Q24.8 fixed-point and needs conversion before it reaches `GetHPBarLevel`; comparing the raw value makes damaged low-level opponents appear permanently green.

The full modern build and a second incremental build both link successfully and produce `pokeemerald.gba`. Merge-marker and unmerged-path scans are clean. The merged upstream tree still contains pre-existing whitespace findings and CRLF normalization notices in generated map/script files.

## Historical tests and static verification targets

Useful targeted test files for a developer-planned test run:

- `test/elastic_emerald_modes.c` (ten `Elastic-tests: Merge guard:` contracts for monotype encoding/startup inventory, Tier Points, and Restricted Mode item clause)
- `test/battle/ability/anticipation.c`
- `test/battle/ability/astral_charge.c`
- `test/battle/ability/honey_gather.c`
- `test/battle/ai/ai.c`
- `test/battle/ai/ai_doubles.c`
- `test/battle/ai/ai_flag_predict_switch.c`
- `test/battle/move_effect/drain_douse.c`
- `test/battle/move_effect/echoed_voice.c`
- `test/battle/move_effect/mud_sport.c`
- `test/battle/move_effect/stockpile.c`
- `test/battle/move_effect/water_sport.c`

The second automated merge-guard batch adds eleven boundary and negative-path contracts across these files: Honey remains held at 76% HP; Light Metal still halves sub-cap weights; neutral attacks receive no Anticipation reduction; non-damaging Psychic moves do not trigger Astral Charge; Mud/Water Sport do not block off-type secondary statuses; Sheer Force suppresses Metal Rush's rider; Drain Douse does nothing after a zero-damage action and uses its Poison-target two-thirds rate; and weather setters stay in when faster or protected from the inferred KO by Focus Sash.

Default static checks for this repo:

```sh
git diff --check
rg -n '(<{7}|={7}|>{7})' .
rg -n 'GetMonTierPoints|CountPartyTierPoints|CalcTierPointsAfter|GetMonoType|FLAG_TIERED|FLAG_RESTRICTED_MODE|FLAG_RESOURCE_MODE|FLAG_CURATED_TERA|CanTerastallize|IsRestrictedModeTeraBanned|CanMonUseCenterTutorWithCurrentResources' include src data
rg -n 'Drain Douse|EFFECT_DRAIN_DOUSE|trydamphealing|Honey Gather|Astral Charge|Merry|Covered|Stockpile|Swallow|Echoed Voice|AI_FLAG_SMART_TRAINER|AI_FLAG_PREDICT_SWITCH|AI_FLAG_SMART_TERA|ApplySimulatedStatChanges|BattleSetup_EnforceRestrictedModeItemClause|PopulateMonotypeResistBerriesInPC|TryGetResistBerryConsumedDamages|TryReturnMrBrineyToDewfordAfterRoute109Fly' include src data test
```

Priority cases often to look at for merge breakage:

1. Monotype save-value decoding across the removed type slot.
2. Monotype startup seeding of exactly the super-effective resist berries.
3. Egg exclusion from Tier Points.
4. Ability-aware Tier Points for weather setters.
5. Badge-progression-aware Tier Points.
6. Safe default Tier Points for a missing candidate.
7. Party Tier Point totals excluding eggs and empty slots.
8. Evolution Tier Point projection without mutating the party.
9. Ability-change Tier Point projection without mutating the party.
10. Restricted Mode item-clause enforcement, including returning the later duplicate to the bag.
