# Elastic Emerald feature history

I keep this index of the major custom systems and their implementation commits, through `9c12ae6d16` (September 24, 2026). It draws on the existing project feature/AI references and local Git history. It covers major gameplay, content, and tooling changes; routine individual learnset, encounter, trainer, and balance edits are not exhaustively listed. The inherited Expansion changelog remains separate.

Commits identify introductions, extensions, or repairs as labeled; old patches are historical evidence, not necessarily the current implementation. I use `git show <commit>` to inspect a patch and `git log -- <path>` to follow later changes. The [custom feature reference](development/feature-reference.md) contains detailed behavior and source anchors, the [AI summary](custom_ai_logic_summary.md) covers individual scoring rules, and the [development guides](development/README.md) record my maintenance approach.

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


