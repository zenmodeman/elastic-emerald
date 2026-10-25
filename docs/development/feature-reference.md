# Elastic Emerald custom feature reference

This reference describes current functional features and player-visible rules. Keep descriptions concise. Repair records belong in the [feature history](../feature-history.md); implementation and maintenance details belong in the [developer topic guides](README.md). Restoring expected behavior does not create a new feature entry.

## Run modes and progression

Players choose Restricted, Resource, EV, Monotype, Tiered, and curated Tera options early in the game. These choices affect encounters, gifts, shops, move services, evolutions, and party eligibility. Monotype and Tiered modes are mutually exclusive.

Level caps follow progression, including rival and Champion milestones. EV Mode uses progression-based per-stat and total EV limits and allows EV redistribution through the Summary Screen.

## Monotype

Wild encounters, gifts, evolutions, and Tera eligibility support the chosen type. Exceptions allow Pokemon that can evolve into a compatible type, with suitable genders for split evolutions. Ghost teams can obtain Shedinja directly from Nincada; Flying and Poison teams receive the appropriate Wurmple evolution.

Starting PC storage includes 12 of each resist berry covering a weakness of the selected type. Terastallization must preserve the chosen type or use Stellar.

See [encounter notes](encounters.md) and the [gameplay reference](../gameplay/README.md).

## Tier Points

Tiered Mode assigns species- and ability-dependent costs and limits the party's total. Captures, gifts, hatches, evolutions, PC transfers, and ability changes respect that budget; excess Pokemon are boxed or the change is blocked as appropriate. The Summary Screen displays Tier Points.

See [Tier Points](../gameplay/tier-points.md) for costs and eligibility rules.

## Restricted and Resource modes

Restricted Mode limits battle items, evolution and ability changes, stat-boosting abilities, and Terastallization. Trainer battles enforce a held-item clause. Release restrictions protect access to required moves.

Player Defiant and Competitive boosts are capped at two positive stages. Moxie-family abilities cannot add another boost once the relevant stat is positive. Mirror Herb copies only boosts directly given to its target by Swagger, Flatter, Spicy Extract, or Decorate. Opponent abilities retain their ordinary behavior.

Resource Mode makes TMs, consumable held items, and move-service points finite. Normal held-item activations spend the item; Knock Off, Fling, and theft cause temporary removal. Consumable held items cannot be transferred from wild Pokemon to the player, while immediate berry consumption and non-consumable transfers remain available.

## Trainer healing and battle-end status

Route bosses and selected accomplished trainer classes heal the player's party before battle. Other selected classes cure status with medicine appropriate to their theme. Full healing takes precedence when paired trainers offer different services; facilities retain their own rules.

After ordinary battles, sleeping Pokemon receive a fresh two-to-four-turn sleep duration. Running from trainer battles remains disabled.

See [trainer rules](../gameplay/trainers.md).

## Terastallization

Tera types can use curated species choices or random assignment. Compatible random types and Stellar can take precedence in Monotype runs. Tera Orb charging is free.

Restricted Mode normally bans Terastallization at four or more Tier Points, with exceptions for selected lower-power ability combinations. Trainer AI accounts for player eligibility when making Tera decisions.

See [curated Tera types](../gameplay/curated-tera-type-distribution.md).

## Move services

Pokemon Centers provide move tutoring, and the party menu provides direct level-up move relearning. Oldale's Tech House offers additional tutors, including alternate niche abilities.

Resource Mode starts with three tutor and relearner points, or five for Monotype teams. Badges award further points, with extra support for depleted balances. When points run out, free tutoring requires the current Pokemon and its reachable evolutions to stay at one Tier Point or less; relearning uses a two-point threshold. Beedrill is exempt from both limits.

## Custom moves and effects

- Overwhelm Beam is a 120-power, 80%-accuracy Special Normal attack with 10 PP and an Insomnia ability-replacement secondary effect.
- Drain Douse and Metal Rush add custom battle effects.
- Big Root increases drain recovery by 40%; Water Veil doubles Aqua Ring's final recovery.
- Refresh cures all major status conditions, including those that ordinarily prevent movement.
- Stockpile and Swallow have improved healing and Gluttony synergy.
- Life Dew heals one third without an ally and one quarter per recipient with a doubles partner.
- Mud Sport and Water Sport have increased priority and additional status protection.
- Foresight, Odor Sleuth, and Laser Focus raise Accuracy and permit repeated use.
- Razor Wind fires immediately under Tailwind; Lucky Chant has adjusted duration and priority.
- Snore and Bounce have species-specific bonuses. Other moves receive balance changes to power, accuracy, healing, or secondary effects.

## Custom abilities

- Unown forms guarantee three perfect IVs on random generation: A–F each fix one stat in display order and randomize two others; G–Z cover all twenty fixed triples; question mark picks any triple; exclamation mark picks one offensive, one defensive, and one HP/Speed stat. Other IVs can naturally roll 31.
- Hidden Power has 60 base power and only Unown (all forms) can use it. Unown receives a damage multiplier of `(Sp. Atk + Attack / 4) / Sp. Atk`, using its stats before battle stages and item/ability multipliers. After switching and target redirection, it chooses the strongest ordinary type using type matchups, explicitly revealed abilities, weather, terrain, STAB, known opposing items, and the user’s held type boosters or Gems. Ties use a consistent type order. Its type is announced before Proactive Color Change.
- Proactive Color Change changes the target's type before immunity checks, including for status moves. Struggle, matching types, and None/Mystery/Stellar types do not trigger it.
- Astral Charge boosts Special Attack when hit by Fairy or Psychic attacks; Mystic boosts Psychic damage by 50%; Dominate uses Download's defensive comparison.
- Dedicated extends field and protection effects. Merry provides Delibird with gifting and battle bonuses. Covered provides Shield Dust-style protection; Solar Core benefits from sun.
- Anticipation reduces damage from super-effective threats on initial switch-in.
- Illuminate, Cute Charm, and Frisk support illuminating, enticing, and item-interacting move categories. Frisk makes item-oriented moves bypass accuracy checks.
- Damp heals in Rain or Water Sport. Limber prevents Speed reductions, and Inner Focus preserves Focus Punch.
- Big Pecks protects screens and positive Defense stages from critical-hit and Chip Away bypasses.
- Truant improves Slack Off healing and interacts with failed-action effects. Honey Gather and Suction Cups provide additional item and overworld benefits.

## Battle AI

Trainer AI compares damage, residual effects, resist berries, priority, hazards, weather, and recovery when choosing moves and switches. It knows player held items, coordinates doubles targeting and Speed control, and uses Tera for knockouts or survival.

Singles immunity-switch prediction becomes available after at least five voluntary player switches during the current opponent's stint. It considers revealed reserve Pokemon and favors frequently used immunity candidates. Forced switches do not contribute.

See the [AI behavior summary](../custom_ai_logic_summary.md) for individual decision rules.

## Maps, trainers, and story

Custom areas and events include Petalburg Grove, Oldale Ruins, Sandfront, Rustboro Grass, Dewford Garden, the Trainer School, Tech House, and expanded early routes and Granite Cave. Trainer parties, rivals, bosses, shops, gifts, and progression gates reflect the selected modes.

Route 109's Cassia requires defeating the beach and Seashore House trainers, heals the party, and offers mode-dependent Power Herb rewards. Her encounter closes after badge three only in Restricted Mode. Rival 110 completion raises beach trainer levels by three. Edmond awards mode-dependent Water Gems after a paired battle.

Triumphs reward participation in first-time trainer victories against comparably leveled Pokemon, up to 30 per Pokemon. Rematches and special battle formats cannot be used to farm them.

The Trainer School includes an AI-versus-AI demonstration and a one-time, Monotype-aware egg gift. Petalburg Grove's Birch scene is limited to the first-badge period. Flannery's diagonal fog is visual and does not introduce Misty Terrain.

See [NPC and trainer notes](npcs-and-trainers.md) and [trainer rules](../gameplay/trainers.md).

## Overworld and quality of life

MenuFly, designated HM users, HM deletion, party nicknaming, Box Link, and Pokedex Plus extend navigation and menus. Oldale's Corviknight caller grants MenuFly. Early Fly travel from Route 109 preserves access to Briney's boat.

The in-game clock supports time advancement, including eight-hour Pokemon Center rests. Egg hatching is faster and supports automatic boxing. Ordinary scripted gifts with unspecified IVs receive at least three perfect IVs.

Split EXP becomes more generous with badges. With two participants, each receives 50%, 62.5%, 75%, 87.5%, and 100% at zero, two, four, six, and eight badges. A sole participant receives full EXP.

Fishing uses shorter rounds and more lenient input timing. Suction Cups can award Bottle Caps after failed bites, with badge and Resource Mode restrictions. Berry yields have increased minimums and selected individual adjustments.

The Summary Screen includes IV/EV information and a Details page for Tier Points, Triumphs, and Tera Type.

## Species, learnsets, and item balance

Species stats, abilities, evolution levels, learnsets, tutor compatibility, machines, items, prices, encounters, and trainer parties receive custom balance changes. Examples include revised early-game bulk profiles, Wind Rider Beautifly, Corrosion Dustox, and Beautifly's Mud-Slap compatibility.

Detailed values and acquisition rules belong in the [gameplay reference](../gameplay/README.md), [item notes](item-acquisition.md), and [learnset tools](../../tools/learnset_helpers/README.md).
