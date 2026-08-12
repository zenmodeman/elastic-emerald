# Standout level-up learnset flourishes

> Design workbook, not an implementation list. Each entry is a compact shortlist for review against encounter timing, evolution level, and the final trainer curve.

This pass covers **583** fully evolved species or mechanically distinct forms represented in both the repository and the bundled historical learnset corpus. Cosmetic forms and Mega Evolutions are omitted. Historical precedent is unioned across **23** game datasets. Repository Pokédex prose is the default flavor source; external species references should be used for borderline calls before implementation.

## Reading the entries

- **Add** is a proposed level-up flourish, not blanket permission for the whole family. A source in parentheses records historical precedent.
- **Earlier power** proposes a useful damaging move near the stated level. Levels follow the requested badge curve, with modest acceleration for final-tier 1–2 Pokémon. They must still be reconciled with actual availability and evolution timing.
- **Tutor context** calls out current Center/Tech Tutor timing. Costless Tech Tutor moves receive little novelty credit; late tutors receive more.
- Final tier is conservatively treated as the stronger value for ability-dependent weather/terrain cases. Tier 5–6 entries often receive an `already distinctive` recommendation instead of more privilege.
- Setup is opt-in. Dragon Dance, Quiver Dance, Swords Dance, Nasty Plot, Shift Gear, Shell Smash, and similar moves are filtered unless explicitly discussed. Baton Pass is never proposed here.
- Coverage is checked against the attacking stat that actually uses it. A rare move is not valuable when the relevant offense is unusable; deliberate mixed branches are called out explicitly.
- Guard Split is excluded from level-up recommendations because it is now a costless Tech Tutor option; historical egg access no longer makes it a meaningful flourish.

## Global setup calls

- **Dustox — Quiver Dance:** reasonable before post-game because 50 Sp. Atk and 65 Speed limit the payoff; do not pair it with Baton Pass.
- **Seviper — Coil:** one of the cleanest flavor/mechanics fits; Coil patches physical accuracy and bulk but not its poor Speed.
- **Tropius — Dragon Dance:** acceptable substantially earlier than the general tutor because 68 Attack and 51 Speed require real help.
- **Weavile — Nasty Plot:** an allowed creative special branch because 45 Sp. Atk keeps it a sidegrade. Hone Claws remains too efficient for its normal physical plan.

## Distribution ecosystem decisions

These allocations compare candidates with current natural learners, not just with historical compatibility. They are intended to keep easily justified moves from becoming generic.

| Move family | Existing natural ecosystem | Priority additions | Deliberately deferred |
|---|---|---|---|
| Grassy Terrain | 15 setters already cover Grass/Poison special status (Vileplume/Roserade), fast offense (Meowscarada), premium physical terrain (Rillaboom), support (Comfey), and legendary field control | Parasect, Meganium, Sunflora, Torterra, Gogoat | Venusaur is lower priority because it overlaps Vileplume/Roserade in typing, bulk, status, and special Grass play; Serperior and Sceptile need less help |
| Special Ground | Earth Power already has 22 natural users | Cradily, Sunflora, Arboliva, Sandy Wormadam, Whiscash, Seismitoad | Hisuian Avalugg and other unusably low-Sp. Atk physical bodies; broad TM compatibility alone is insufficient |
| Physical Ground | Earthquake has 31 natural users; High Horsepower only 7 | Earthquake Aggron; High Horsepower Hisuian Avalugg, Donphan, Zebstrika, Bouffalant | Avoid duplicating Earthquake where High Horsepower better communicates charging anatomy |
| Heated sand | Scorching Sands has no natural users in the current file | Maractus, Cacturne, Palossand | Physical desert species with poor Sp. Atk should retain Earthquake/High Horsepower rather than receiving decorative special coverage |
| Item disruption | Knock Off already has 36 natural users and is a League tutor | Persian, Alolan Persian, Ambipom, Liepard, Thievul, Watchog, Shiftry | Strong high-tier attackers and species lacking a thief, scavenger, grasping-limb, or disruptive role |
| Crushing Steel | Hard Press has no natural users | Aggron, Hisuian Avalugg, Stonjourner, Copperajah, Revavroom | Light or special Steel types; mere TM compatibility is not enough |

## Modern teachable-heavy move audit

These counts use the full bundled historical corpus. `Teachable` means TM or tutor in at least one dataset; it does not mean the species currently has that access in Elastic Emerald. A tiny natural column beside a large teachable column is distribution debt, not an instruction to naturalize the move broadly.

| Move | Historical level-up learners | Historical teachable learners | Proposed natural identity owners |
|---|---:|---:|---|
| Terrain Pulse | 3 | 23 | Kecleon |
| Burning Jealousy | 0 | 56 | Banette, Spiritomb |
| Flip Turn | 4 | 75 | Luvdisc, Lumineon, Wugtrio |
| Grassy Glide | 0 | 106 | Parasect, Leafeon |
| Rising Voltage | 1 | 48 | Dedenne, Ampharos |
| Coaching | 0 | 70 | Ledian, Passimian |
| Scorching Sands | 0 | 86 | Maractus, Cacturne, Palossand |
| Dual Wingbeat | 9 | 126 | Toucannon |
| Meteor Beam | 0 | 93 | Lunatone, Aurorus |
| Skitter Smack | 5 | 132 | Ariados, Wormadam (Trash) |
| Triple Axel | 0 | 48 | Delibird, Hitmontop |
| Expanding Force | 4 | 99 | Beheeyem, Musharna |
| Poltergeist | 0 | 61 | Banette, Dusknoir |
| Scale Shot | 1 | 91 | Seviper, Druddigon |
| Lash Out | 0 | 146 | Mightyena, Mabosstiff |
| Steel Roller | 1 | 51 | Klinklang, Revavroom |
| Misty Explosion | 0 | 25 | Weezing (Galar), Aromatisse |
| Pounce | 0 | 84 | Ariados, Kricketune |
| Chilling Water | 0 | 224 | Dewgong, Glalie, Cryogonal |
| Ice Spinner | 2 | 69 | Beartic, Avalugg |
| Alluring Voice | 0 | 64 | Jynx, Chimecho |
| Hard Press | 0 | 47 | Aggron, Avalugg (Hisui), Stonjourner, Copperajah, Revavroom |
| Temper Flare | 0 | 74 | Flareon, Torkoal |

Compatibility gaps are assessed separately. Presence is inferred directly from whether the species has an entry in `swsh.json` and `sv.json`. Absence from Sword/Shield or Scarlet/Violet is evidence that a species may simply have missed a distribution pass; it is not by itself proof that every new move fits.

## Species suggestions

### Abomasnow

**Type:** Grass/Ice · **Final tier weight:** 2
**Role profile:** Atk 92 / Sp. Atk 92 / Spe 60 · Snow Warning, Soundproof
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Magical Leaf:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 5%; Tech Tutor (7 badges).*
- **Add — Leech Seed:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Earlier power — Magical Leaf around Lv. 22:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Absol

**Type:** Dark · **Final tier weight:** 2
**Role profile:** Atk 130 / Sp. Atk 75 / Spe 75 · Pressure, Super Luck, Justified
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Megahorn:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/TM; type-cohort prevalence 4%; Center Tutor (before Gym 8).*
- **Add — Bite:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg; type-cohort prevalence 44%; no Center/Tech Tutor overlap.*
- **Earlier power — Megahorn around Lv. 52:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Accelgor

**Type:** Bug · **Final tier weight:** 3
**Role profile:** Atk 70 / Sp. Atk 100 / Spe 145 · Hydration, Sticky Hold, Unburden
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Sludge Bomb:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 23%; no Center/Tech Tutor overlap.*
- **Add — Leech Life:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 51%; Center Tutor (before Gym 7).*
- **Earlier power — Sludge Bomb around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Aerodactyl

**Type:** Rock/Flying · **Final tier weight:** 4
**Role profile:** Atk 105 / Sp. Atk 60 / Spe 130 · Rock Head, Pressure, Unnerve
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Steel Wing:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power — Steel Wing around Lv. 34:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Aggron

**Type:** Steel/Rock · **Final tier weight:** 3
**Role profile:** Atk 110 / Sp. Atk 60 / Spe 50 · Sturdy, Rock Head, Heavy Metal
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Earthquake:** Its weight and territorial stomping justify premium physical Ground coverage. *Precedent: TM; type-cohort prevalence 52%; no Center/Tech Tutor overlap.*
- **Add — Hard Press:** Its armored mass gives the variable-power Steel attack a visible source. *Precedent: deliberate design exception; type-cohort prevalence 19%; no Center/Tech Tutor overlap.*
- **Earlier power — Hard Press around Lv. 44:** up to 100 BP (HP-dependent); STAB. Treat this as the curve target, not a fixed slot.

### Alakazam

**Type:** Psychic · **Final tier weight:** 4
**Role profile:** Atk 50 / Sp. Atk 135 / Spe 120 · Synchronize, Inner Focus, Magic Guard
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Barrier:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 12%; Center Tutor (before Gym 6).*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Alomomola

**Type:** Water · **Final tier weight:** 5
**Role profile:** Atk 75 / Sp. Atk 40 / Spe 65 · Healer, Hydration, Regenerator
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Altaria

**Type:** Dragon/Flying · **Final tier weight:** 2
**Role profile:** Atk 70 / Sp. Atk 70 / Spe 80 · Natural Cure, Cloud Nine
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Dragon Rush:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg/TM; type-cohort prevalence 14%; no Center/Tech Tutor overlap.*
- **Add — Feather Dance:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg/TM; type-cohort prevalence 2%; Tech Tutor (5 badges).*
- **Earlier power — Dragon Rush around Lv. 54:** 100 BP; STAB. Treat this as the curve target, not a fixed slot.

### Ambipom

**Type:** Normal · **Final tier weight:** 4
**Role profile:** Atk 100 / Sp. Atk 60 / Spe 115 · Technician, Pickup, Skill Link
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Knock Off:** Dexterous tail-hands make item removal visibly plausible. *Precedent: TM/tutor; type-cohort prevalence 41%; Center Tutor (League).*
- **Earlier power — Knock Off around Lv. 34:** 65 BP; coverage. Treat this as the curve target, not a fixed slot.

### Amoonguss

**Type:** Grass/Poison · **Final tier weight:** 5
**Role profile:** Atk 85 / Sp. Atk 85 / Spe 30 · Effect Spore, Regenerator
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Ampharos

**Type:** Electric · **Final tier weight:** 3
**Role profile:** Atk 75 / Sp. Atk 115 / Spe 55 · Static, Plus
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Rising Voltage:** Its low Speed and strong special electricity make terrain-dependent power a fair branch. *Precedent: deliberate design exception; type-cohort prevalence 58%; Center Tutor (before Gym 7).*
- **Add — Thunderbolt:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 100%; no Center/Tech Tutor overlap.*
- **Earlier power — Thunderbolt around Lv. 58:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Annihilape

**Type:** Fighting/Ghost · **Final tier weight:** 6
**Role profile:** Atk 115 / Sp. Atk 50 / Spe 90 · Vital Spirit, Inner Focus, Defiant
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Appletun

**Type:** Grass/Dragon · **Final tier weight:** 3
**Role profile:** Atk 85 / Sp. Atk 100 / Spe 30 · Ripen, Gluttony, Thick Fat
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Sucker Punch:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 13%; Legacy Tutor.*
- **Add — Draco Meteor:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM/tutor; type-cohort prevalence 6%; Center Tutor (League).*
- **Earlier power — Draco Meteor around Lv. 58:** 130 BP; STAB. Treat this as the curve target, not a fixed slot.

### Araquanid

**Type:** Water/Bug · **Final tier weight:** 4
**Role profile:** Atk 70 / Sp. Atk 50 / Spe 42 · Water Bubble, Water Absorb
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Sticky Web:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 1%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Arbok

**Type:** Poison · **Final tier weight:** 2
**Role profile:** Atk 95 / Sp. Atk 65 / Spe 80 · Intimidate, Shed Skin, Unnerve
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Slam:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/egg; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Add — Sucker Punch:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/egg; type-cohort prevalence 17%; Legacy Tutor.*
- **Earlier power — Slam around Lv. 44:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Arboliva

**Type:** Grass/Normal · **Final tier weight:** 4
**Role profile:** Atk 69 / Sp. Atk 125 / Spe 39 · Seed Sower, Harvest
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Earth Power:** Its roots and 125 Sp. Atk make this the strongest non-Ground botanical candidate. *Precedent: TM; type-cohort prevalence 16%; Center Tutor (before Gym 8).*
- **Earlier power — Earth Power around Lv. 42:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Arcanine

**Type:** Fire · **Final tier weight:** 4
**Role profile:** Atk 110 / Sp. Atk 100 / Spe 95 · Intimidate, Flash Fire, Justified
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Burn Up:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 15%; no Center/Tech Tutor overlap.*
- **Earlier power — Burn Up around Lv. 58:** 130 BP; STAB. Treat this as the curve target, not a fixed slot.

### Arcanine (Hisui)

**Type:** Fire/Rock · **Final tier weight:** 4
**Role profile:** Atk 115 / Sp. Atk 95 / Spe 90 · Intimidate, Flash Fire, Rock Head
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Morning Sun:** Its jaw-based anatomy gives the coverage a concrete physical source. *Precedent: egg; type-cohort prevalence 4%; Legacy Tutor.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Archaludon

**Type:** Steel/Dragon · **Final tier weight:** 6
**Role profile:** Atk 105 / Sp. Atk 125 / Spe 85 · Stamina, Sturdy, Stalwart
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Archeops

**Type:** Rock/Flying · **Final tier weight:** 4
**Role profile:** Atk 140 / Sp. Atk 112 / Spe 110 · Defeatist
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Head Smash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Head Smash around Lv. 58:** 150 BP; STAB. Treat this as the curve target, not a fixed slot.

### Arctovish

**Type:** Water/Ice · **Final tier weight:** 3
**Role profile:** Atk 90 / Sp. Atk 80 / Spe 55 · Water Absorb, Ice Body, Slush Rush
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Psychic Fangs:** Its pronounced jaws or fangs give the unusual Psychic coverage a physical basis. *Precedent: TM; type-cohort prevalence 8%; Center Tutor (before Gym 7).*
- **Add — Brine:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 16%; Center Tutor (before Gym 5).*
- **Earlier power — Psychic Fangs around Lv. 48:** 85 BP; coverage. Treat this as the curve target, not a fixed slot.

### Arctozolt

**Type:** Electric/Ice · **Final tier weight:** 3
**Role profile:** Atk 100 / Sp. Atk 90 / Spe 55 · Volt Absorb, Static, Slush Rush
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Wild Charge:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 3%; Center Tutor (before Gym 8).*
- **Add — Thunder Fang:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 5%; Center Tutor (before Gym 4).*
- **Earlier power — Wild Charge around Lv. 58:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Ariados

**Type:** Bug/Poison · **Final tier weight:** 1
**Role profile:** Atk 90 / Sp. Atk 60 / Spe 40 · Swarm, Insomnia, Sniper
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Skitter Smack:** A low-tier physical spider can own the disruptive Bug attack. *Precedent: TM; type-cohort prevalence 21%; Center Tutor (before Gym 6).*
- **Add — Pounce:** Pouncing is a direct spider hunting behavior and offers a modest early bridge. *Precedent: TM; type-cohort prevalence 17%; Center Tutor (before Gym 2).*
- **Add — Megahorn:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 8%; Center Tutor (before Gym 8).*
- **Earlier power — Megahorn around Lv. 51:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Armaldo

**Type:** Rock/Bug · **Final tier weight:** 3
**Role profile:** Atk 125 / Sp. Atk 70 / Spe 45 · Battle Armor, Swift Swim
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Cross Poison:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/TM; type-cohort prevalence 6%; Center Tutor (before Gym 5).*
- **Add — Rapid Spin:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg; type-cohort prevalence 6%; Center Tutor (before Gym 5).*
- **Earlier power — Cross Poison around Lv. 34:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Armarouge

**Type:** Fire/Psychic · **Final tier weight:** 4
**Role profile:** Atk 60 / Sp. Atk 125 / Spe 75 · Flash Fire, Weak Armor
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Psybeam:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/TM; type-cohort prevalence 4%; Center Tutor (before Gym 4).*
- **Earlier power — Psybeam around Lv. 33:** 65 BP; STAB. Treat this as the curve target, not a fixed slot.

### Aromatisse

**Type:** Fairy · **Final tier weight:** 3
**Role profile:** Atk 72 / Sp. Atk 99 / Spe 29 · Healer, Aroma Veil
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Misty Explosion:** Perfume mist and low Speed make this a thematic emergency button. *Precedent: tutor; type-cohort prevalence 35%; Center Tutor (before Gym 6).*
- **Add — Wish:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 24%; Legacy Tutor.*
- **Earlier power — Misty Explosion around Lv. 40:** 100 BP; STAB. Treat this as the curve target, not a fixed slot.

### Articuno

**Type:** Ice/Flying · **Final tier weight:** 3
**Role profile:** Atk 85 / Sp. Atk 95 / Spe 85 · Pressure, Snow Cloak
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Sky Attack:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/TM/tutor; type-cohort prevalence 5%; Center Tutor (before Gym 7).*
- **Add — Frost Breath:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: TM; type-cohort prevalence 3%; Center Tutor (before Gym 8).*
- **Earlier power — Sky Attack around Lv. 58:** 140 BP; STAB. Treat this as the curve target, not a fixed slot.

### Articuno (Galar)

**Type:** Psychic/Flying · **Final tier weight:** 3
**Role profile:** Atk 85 / Sp. Atk 125 / Spe 95 · Competitive
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Hyper Voice:** Its voice, cry, song, or sound-based identity makes this natural level-up expression. *Precedent: TM; type-cohort prevalence 24%; no Center/Tech Tutor overlap.*
- **Add — Mind Reader:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power — Hyper Voice around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Audino

**Type:** Normal · **Final tier weight:** 2
**Role profile:** Atk 60 / Sp. Atk 60 / Spe 50 · Healer, Regenerator, Klutz
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Draining Kiss:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 8%; Center Tutor (before Gym 4).*
- **Add — Heal Bell:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 8%; Center Tutor (before Gym 5).*
- **Earlier power — Draining Kiss around Lv. 13:** 50 BP; coverage. Treat this as the curve target, not a fixed slot.

### Aurorus

**Type:** Rock/Ice · **Final tier weight:** 3
**Role profile:** Atk 77 / Sp. Atk 99 / Spe 58 · Refrigerate, Snow Warning
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Meteor Beam:** Its aurora and fossil spectacle support a rare special Rock setup attack. *Precedent: TM/tutor; type-cohort prevalence 14%; Center Tutor (before Gym 7).*
- **Add — Rock Throw:** Its established sound motif makes this a strong identity move. *Precedent: level-up/egg/TM; type-cohort prevalence 3%; no Center/Tech Tutor overlap.*
- **Earlier power — Meteor Beam around Lv. 48:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Avalugg

**Type:** Ice · **Final tier weight:** 4
**Role profile:** Atk 117 / Sp. Atk 44 / Spe 28 · Own Tempo, Ice Body, Sturdy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Ice Spinner:** Its physical bulk and iceberg motion support a slow terrain-clearing attack. *Precedent: TM; type-cohort prevalence 49%; Center Tutor (before Gym 7).*
- **Earlier power — Ice Spinner around Lv. 42:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Avalugg (Hisui)

**Type:** Ice/Rock · **Final tier weight:** 4
**Role profile:** Atk 127 / Sp. Atk 34 / Spe 38 · Strong Jaw, Ice Body, Sturdy
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — High Horsepower:** 127 Attack and a charging iceberg body suit physical Ground coverage. *Precedent: TM/tutor; type-cohort prevalence 19%; Center Tutor (before Gym 8).*
- **Add — Hard Press:** Its immense armored body is a much better fit than special Earth Power. *Precedent: TM; type-cohort prevalence 16%; no Center/Tech Tutor overlap.*
- **Earlier power — Hard Press around Lv. 40:** up to 100 BP (HP-dependent); coverage. Treat this as the curve target, not a fixed slot.

### Azelf

**Type:** Psychic · **Final tier weight:** 5
**Role profile:** Atk 125 / Sp. Atk 125 / Spe 115 · Levitate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Azumarill

**Type:** Water/Fairy · **Final tier weight:** 4
**Role profile:** Atk 50 / Sp. Atk 60 / Spe 50 · Thick Fat, Huge Power, Sap Sipper
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Muddy Water:** Early special STAB gives non-Huge-Power abilities and its 60 Sp. Atk a meaningful route. *Precedent: egg/TM; type-cohort prevalence 6%; Center Tutor (before Gym 8).*
- **Earlier power — Muddy Water around Lv. 38:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Banette

**Type:** Ghost · **Final tier weight:** 1
**Role profile:** Atk 115 / Sp. Atk 83 / Spe 65 · Insomnia, Frisk, Cursed Body
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Burning Jealousy:** Its grudge-born Pokédex lore gives the emotion-based attack an unusually direct home. *Precedent: TM; type-cohort prevalence 22%; Tech Tutor (8 badges).*
- **Add — Poltergeist:** A possessed doll is the clearest possible natural owner of Poltergeist. *Precedent: TM; type-cohort prevalence 81%; Center Tutor (before Gym 8).*
- **Add — Gunk Shot:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 14%; Center Tutor (before Gym 8).*
- **Earlier power — Gunk Shot around Lv. 49:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Barbaracle

**Type:** Rock/Water · **Final tier weight:** 3
**Role profile:** Atk 105 / Sp. Atk 54 / Spe 68 · Tough Claws, Sniper, Pickpocket
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Night Slash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 9%; no Center/Tech Tutor overlap.*
- **Add — Rock Throw:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Earlier power — Night Slash around Lv. 34:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Barraskewda

**Type:** Water · **Final tier weight:** 4
**Role profile:** Atk 123 / Sp. Atk 60 / Spe 136 · Swift Swim, Propeller Tail
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Thrash:** Its jaw-based anatomy gives the coverage a concrete physical source. *Precedent: egg; type-cohort prevalence 12%; no Center/Tech Tutor overlap.*
- **Earlier power — Thrash around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Bastiodon

**Type:** Rock/Steel · **Final tier weight:** 3
**Role profile:** Atk 52 / Sp. Atk 47 / Spe 30 · Sturdy, Soundproof
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Stealth Rock:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 60%; Center Tutor (before Gym 4).*
- **Add — Rock Slide:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/TM/tutor; type-cohort prevalence 60%; no Center/Tech Tutor overlap.*
- **Earlier power — Rock Slide around Lv. 42:** 75 BP; STAB. Treat this as the curve target, not a fixed slot.

### Baxcalibur

**Type:** Dragon/Ice · **Final tier weight:** 5
**Role profile:** Atk 145 / Sp. Atk 75 / Spe 87 · Thermal Exchange, Ice Body
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Dragon Rush:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg/TM; type-cohort prevalence 3%; no Center/Tech Tutor overlap.*
- **Earlier power — Dragon Rush around Lv. 61:** 100 BP; STAB. Treat this as the curve target, not a fixed slot.

### Beartic

**Type:** Ice · **Final tier weight:** 2
**Role profile:** Atk 130 / Sp. Atk 70 / Spe 50 · Snow Cloak, Slush Rush, Swift Swim
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Ice Spinner:** Its strong physical Ice offense and mobile bear body make terrain-clearing contact plausible. *Precedent: deliberate design exception; type-cohort prevalence 49%; Center Tutor (before Gym 7).*
- **Add — Play Rough:** Its jaw-based anatomy gives the coverage a concrete physical source. *Precedent: egg/TM; type-cohort prevalence 16%; Center Tutor (before Gym 8).*
- **Earlier power — Play Rough around Lv. 52:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Beautifly

**Type:** Bug/Flying · **Final tier weight:** 1
**Role profile:** Atk 70 / Sp. Atk 100 / Spe 65 · Swarm, Wind Rider, Rivalry
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Venoshock:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/TM; type-cohort prevalence 8%; Center Tutor (before Gym 4).*
- **Add — Air Slash:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up; type-cohort prevalence 34%; Center Tutor (before Gym 6).*
- **Add — Silver Wind:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/TM; type-cohort prevalence 22%; no Center/Tech Tutor overlap.*
- **Earlier power — Air Slash around Lv. 35:** 75 BP; STAB. Treat this as the curve target, not a fixed slot.

### Beedrill

**Type:** Bug/Poison · **Final tier weight:** 1
**Role profile:** Atk 90 / Sp. Atk 45 / Spe 75 · Swarm, Sniper, Poison Touch
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Lunge:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 15%; Center Tutor (before Gym 7).*
- **Add — X Scissor:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 21%; Center Tutor (before Gym 7).*
- **Add — Outrage:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 11%; Center Tutor (before Gym 7).*
- **Compatibility gap — Pounce:** Verify or add TM/tutor compatibility rather than level-up access; a fast stinging insect is an obvious recipient of the broadly distributed Bug TM.
- **Earlier power — Outrage around Lv. 49:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Beheeyem

**Type:** Psychic · **Final tier weight:** 2
**Role profile:** Atk 75 / Sp. Atk 125 / Spe 40 · Telepathy, Synchronize, Analytic
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Expanding Force:** A slow Psychic specialist can exploit terrain without becoming a generic fast sweeper. *Precedent: tutor; type-cohort prevalence 86%; no Center/Tech Tutor overlap.*
- **Add — Synchronoise:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 14%; Tech Tutor (5 badges).*
- **Earlier power — Synchronoise around Lv. 54:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Bellibolt

**Type:** Electric · **Final tier weight:** 4
**Role profile:** Atk 64 / Sp. Atk 103 / Spe 45 · Electromorphosis, Static, Damp
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Parabolic Charge:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 8%; no Center/Tech Tutor overlap.*
- **Earlier power — Parabolic Charge around Lv. 33:** 65 BP; STAB. Treat this as the curve target, not a fixed slot.

### Bellossom

**Type:** Grass · **Final tier weight:** 3
**Role profile:** Atk 80 / Sp. Atk 90 / Spe 50 · Chlorophyll, Healer
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Strength Sap:** Its draining or parasitic flavor supports a distinctive utility niche. *Precedent: egg; type-cohort prevalence 11%; no Center/Tech Tutor overlap.*
- **Add — Leaf Storm:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 85%; Center Tutor (League).*
- **Earlier power — Leaf Storm around Lv. 58:** 130 BP; STAB. Treat this as the curve target, not a fixed slot.

### Bewear

**Type:** Normal/Fighting · **Final tier weight:** 3
**Role profile:** Atk 125 / Sp. Atk 55 / Spe 60 · Fluffy, Klutz, Unnerve
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Stomp:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Add — Force Palm:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Stomp around Lv. 33:** 65 BP; STAB. Treat this as the curve target, not a fixed slot.

### Bibarel

**Type:** Normal/Water · **Final tier weight:** 1
**Role profile:** Atk 85 / Sp. Atk 55 / Spe 71 · Simple, Unaware, Moody
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Aqua Tail:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/tutor; type-cohort prevalence 12%; Center Tutor (before Gym 8).*
- **Add — Double Edge:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 65%; no Center/Tech Tutor overlap.*
- **Add — Hyper Fang:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 1%; no Center/Tech Tutor overlap.*
- **Earlier power — Double Edge around Lv. 51:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Blacephalon

**Type:** Fire/Ghost · **Final tier weight:** 3
**Role profile:** Atk 127 / Sp. Atk 151 / Spe 107 · Beast Boost
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Flame Burst:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Add — Overheat:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 16%; Center Tutor (League).*
- **Earlier power — Overheat around Lv. 58:** 130 BP; STAB. Treat this as the curve target, not a fixed slot.

### Blastoise

**Type:** Water · **Final tier weight:** 3
**Role profile:** Atk 83 / Sp. Atk 85 / Spe 78 · Torrent, Rain Dish
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Brine:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg/TM; type-cohort prevalence 60%; Center Tutor (before Gym 5).*
- **Add — Water Spout:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Earlier power — Water Spout around Lv. 58:** 150 BP; STAB. Treat this as the curve target, not a fixed slot.

### Blaziken

**Type:** Fire/Fighting · **Final tier weight:** 5
**Role profile:** Atk 120 / Sp. Atk 110 / Spe 80 · Blaze, Speed Boost
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Blissey

**Type:** Normal · **Final tier weight:** 6
**Role profile:** Atk 10 / Sp. Atk 75 / Spe 55 · Natural Cure, Serene Grace, Healer
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Heal Bell:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 8%; Center Tutor (before Gym 5).*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Boltund

**Type:** Electric · **Final tier weight:** 3
**Role profile:** Atk 90 / Sp. Atk 90 / Spe 121 · Strong Jaw, Competitive
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Flame Charge:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 6%; Center Tutor (before Gym 3).*
- **Add — Double Edge:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 44%; no Center/Tech Tutor overlap.*
- **Earlier power — Double Edge around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Bombirdier

**Type:** Flying/Dark · **Final tier weight:** 3
**Role profile:** Atk 103 / Sp. Atk 60 / Spe 82 · Big Pecks, Keen Eye, Rocky Payload
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Sucker Punch:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg; type-cohort prevalence 11%; Legacy Tutor.*
- **Add — Sky Attack:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg; type-cohort prevalence 10%; Center Tutor (before Gym 7).*
- **Earlier power — Sky Attack around Lv. 58:** 140 BP; STAB. Treat this as the curve target, not a fixed slot.

### Bouffalant

**Type:** Normal · **Final tier weight:** 2
**Role profile:** Atk 110 / Sp. Atk 40 / Spe 55 · Reckless, Sap Sipper, Soundproof
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — High Horsepower:** A charging buffalo is one of the move's clearest non-horse fits. *Precedent: TM; type-cohort prevalence 22%; Center Tutor (before Gym 8).*
- **Add — Rock Climb:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 19%; Center Tutor (before Gym 7).*
- **Earlier power — High Horsepower around Lv. 34:** 95 BP; coverage. Treat this as the curve target, not a fixed slot.

### Brambleghast

**Type:** Grass/Ghost · **Final tier weight:** 3
**Role profile:** Atk 115 / Sp. Atk 80 / Spe 90 · Wind Rider, Infiltrator
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Strength Sap:** Its draining or parasitic flavor supports a distinctive utility niche. *Precedent: egg; type-cohort prevalence 11%; no Center/Tech Tutor overlap.*
- **Add — Trailblaze:** Its terrestrial movement and plant association support an active Grass attack rather than generic TM access. *Precedent: TM; type-cohort prevalence 16%; Center Tutor (before Gym 3).*
- **Earlier power — Trailblaze around Lv. 19:** 50 BP; STAB. Treat this as the curve target, not a fixed slot.

### Braviary

**Type:** Normal/Flying · **Final tier weight:** 3
**Role profile:** Atk 123 / Sp. Atk 57 / Spe 80 · Keen Eye, Sheer Force, Defiant
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Sky Drop:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/TM; type-cohort prevalence 2%; Center Tutor (before Gym 3).*
- **Add — Brave Bird:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/TM; type-cohort prevalence 14%; Center Tutor (League).*
- **Earlier power — Brave Bird around Lv. 58:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Braviary (Hisui)

**Type:** Psychic/Flying · **Final tier weight:** 3
**Role profile:** Atk 83 / Sp. Atk 112 / Spe 65 · Keen Eye, Sheer Force, Tinted Lens
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Roost:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg; type-cohort prevalence 12%; no Center/Tech Tutor overlap.*
- **Add — Brave Bird:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/TM; type-cohort prevalence 6%; Center Tutor (League).*
- **Earlier power — Brave Bird around Lv. 58:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Breloom

**Type:** Grass/Fighting · **Final tier weight:** 3
**Role profile:** Atk 130 / Sp. Atk 60 / Spe 70 · Effect Spore, Poison Heal, Technician
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Drain Punch:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 22%; Center Tutor (before Gym 6).*
- **Add — Wake Up Slap:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 3%; no Center/Tech Tutor overlap.*
- **Earlier power — Drain Punch around Lv. 42:** 75 BP; STAB. Treat this as the curve target, not a fixed slot.

### Bronzong

**Type:** Steel/Psychic · **Final tier weight:** 4
**Role profile:** Atk 89 / Sp. Atk 79 / Spe 33 · Levitate, Heatproof, Heavy Metal
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Flash Cannon:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM/tutor; type-cohort prevalence 24%; Center Tutor (before Gym 7).*
- **Earlier power — Flash Cannon around Lv. 50:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Brute Bonnet

**Type:** Grass/Dark · **Final tier weight:** 3
**Role profile:** Atk 127 / Sp. Atk 79 / Spe 55 · Protosynthesis
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 17%; Center Tutor (before Gym 7).*
- **Add — Trailblaze:** Its terrestrial movement and plant association support an active Grass attack rather than generic TM access. *Precedent: TM; type-cohort prevalence 40%; Center Tutor (before Gym 3).*
- **Earlier power — Body Press around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Bruxish

**Type:** Water/Psychic · **Final tier weight:** 3
**Role profile:** Atk 105 / Sp. Atk 70 / Spe 92 · Dazzling, Strong Jaw, Wonder Skin
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Poison Fang:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg; type-cohort prevalence 1%; no Center/Tech Tutor overlap.*
- **Add — Ice Fang:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg/TM; type-cohort prevalence 6%; Center Tutor (before Gym 4).*
- **Earlier power — Ice Fang around Lv. 31:** 65 BP; coverage. Treat this as the curve target, not a fixed slot.

### Butterfree

**Type:** Bug/Flying · **Final tier weight:** 2
**Role profile:** Atk 45 / Sp. Atk 90 / Spe 70 · Compound Eyes, Honey Gather, Tinted Lens
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Razor Wind:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 11%; no Center/Tech Tutor overlap.*
- **Add — Energy Ball:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 17%; Center Tutor (before Gym 8).*
- **Earlier power — Energy Ball around Lv. 52:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Buzzwole

**Type:** Bug/Fighting · **Final tier weight:** 5
**Role profile:** Atk 139 / Sp. Atk 53 / Spe 79 · Beast Boost
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Leech Life:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 4%; Center Tutor (before Gym 7).*
- **Earlier power — Leech Life around Lv. 53:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Cacturne

**Type:** Grass/Dark · **Final tier weight:** 2
**Role profile:** Atk 115 / Sp. Atk 115 / Spe 55 · Sand Veil, Water Absorb, Sand Rush
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Scorching Sands:** Its Pokédex text says its body became sand after millennia in harsh deserts. *Precedent: deliberate design exception; type-cohort prevalence 2%; Center Tutor (before Gym 6).*
- **Add — Knock Off:** Its nocturnal ambusher role and usable hands justify earlier disruptive Dark STAB. *Precedent: TM; type-cohort prevalence 46%; Center Tutor (League).*
- **Earlier power — Scorching Sands around Lv. 36:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Calyrex

**Type:** Psychic/Grass · **Final tier weight:** 3
**Role profile:** Atk 80 / Sp. Atk 80 / Spe 80 · Unnerve
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Pollen Puff:** Its flower, pollen, or caregiving identity supports both the attack and ally-heal flavor. *Precedent: TM; type-cohort prevalence 6%; Center Tutor (before Gym 8).*
- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 14%; Center Tutor (before Gym 7).*
- **Earlier power — Pollen Puff around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Calyrex (Ice)

**Type:** Psychic/Ice · **Final tier weight:** 3
**Role profile:** Atk 165 / Sp. Atk 85 / Spe 50 · As One Ice Rider
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 14%; Center Tutor (before Gym 7).*
- **Add — Solar Blade:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 3%; Center Tutor (before Gym 8).*
- **Earlier power — Solar Blade around Lv. 56:** 125 BP; coverage. Treat this as the curve target, not a fixed slot.

### Calyrex (Shadow)

**Type:** Psychic/Ghost · **Final tier weight:** 3
**Role profile:** Atk 85 / Sp. Atk 165 / Spe 150 · As One Shadow Rider
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Pollen Puff:** Its flower, pollen, or caregiving identity supports both the attack and ally-heal flavor. *Precedent: TM; type-cohort prevalence 3%; Center Tutor (before Gym 8).*
- **Add — Tri Attack:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 5%; Center Tutor (before Gym 6).*
- **Earlier power — Pollen Puff around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Camerupt

**Type:** Fire/Ground · **Final tier weight:** 2
**Role profile:** Atk 100 / Sp. Atk 105 / Spe 40 · Magma Armor, Solid Rock, Anger Point
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Mud Bomb:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Heat Wave:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 10%; Center Tutor (before Gym 8).*
- **Earlier power — Heat Wave around Lv. 54:** 95 BP; STAB. Treat this as the curve target, not a fixed slot.

### Carbink

**Type:** Rock/Fairy · **Final tier weight:** 3
**Role profile:** Atk 50 / Sp. Atk 50 / Spe 50 · Clear Body, Sturdy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Dazzling Gleam:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 11%; Center Tutor (before Gym 7).*
- **Add — Rock Throw:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 9%; no Center/Tech Tutor overlap.*
- **Earlier power — Dazzling Gleam around Lv. 50:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Carnivine

**Type:** Grass · **Final tier weight:** 1
**Role profile:** Atk 100 / Sp. Atk 90 / Spe 46 · Levitate
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Acid Spray:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 14%; Center Tutor (before Gym 3).*
- **Add — Rage Powder:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 12%; no Center/Tech Tutor overlap.*
- **Add — Stun Spore:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 32%; no Center/Tech Tutor overlap.*
- **Earlier power — Acid Spray around Lv. 10:** 40 BP; coverage. Treat this as the curve target, not a fixed slot.

### Carracosta

**Type:** Water/Rock · **Final tier weight:** 3
**Role profile:** Atk 108 / Sp. Atk 83 / Spe 32 · Solid Rock, Sturdy, Swift Swim
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Rock Throw:** Its jaw-based anatomy gives the coverage a concrete physical source. *Precedent: egg; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Add — Liquidation:** Its jaw-based anatomy gives the coverage a concrete physical source. *Precedent: egg/TM/tutor; type-cohort prevalence 17%; Center Tutor (before Gym 7).*
- **Earlier power — Liquidation around Lv. 50:** 85 BP; STAB. Treat this as the curve target, not a fixed slot.

### Celebi

**Type:** Psychic/Grass · **Final tier weight:** 4
**Role profile:** Atk 100 / Sp. Atk 100 / Spe 100 · Natural Cure
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Pollen Puff:** Its flower, pollen, or caregiving identity supports both the attack and ally-heal flavor. *Precedent: TM; type-cohort prevalence 6%; Center Tutor (before Gym 8).*
- **Earlier power — Pollen Puff around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Celesteela

**Type:** Steel/Flying · **Final tier weight:** 5
**Role profile:** Atk 101 / Sp. Atk 107 / Spe 61 · Beast Boost
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Centiskorch

**Type:** Fire/Bug · **Final tier weight:** 3
**Role profile:** Atk 115 / Sp. Atk 90 / Spe 65 · Flash Fire, White Smoke, Flame Body
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Struggle Bug:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 6%; Center Tutor (before Gym 2).*
- **Add — Mystical Fire:** Its supernatural or elegant fire identity makes the move feel native rather than generic coverage. *Precedent: TM; type-cohort prevalence 4%; Center Tutor (before Gym 6).*
- **Earlier power — Mystical Fire around Lv. 42:** 75 BP; STAB. Treat this as the curve target, not a fixed slot.

### Ceruledge

**Type:** Fire/Ghost · **Final tier weight:** 4
**Role profile:** Atk 125 / Sp. Atk 60 / Spe 85 · Flash Fire, Weak Armor
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Phantom Force:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 2%; Center Tutor (before Gym 8).*
- **Earlier power — Phantom Force around Lv. 58:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Cetitan

**Type:** Ice · **Final tier weight:** 3
**Role profile:** Atk 113 / Sp. Atk 45 / Spe 73 · Thick Fat, Slush Rush, Sheer Force
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Icicle Crash:** Its jaw-based anatomy gives the coverage a concrete physical source. *Precedent: egg; type-cohort prevalence 46%; no Center/Tech Tutor overlap.*
- **Add — Superpower:** Its jaw-based anatomy gives the coverage a concrete physical source. *Precedent: egg; type-cohort prevalence 22%; Center Tutor (League).*
- **Earlier power — Superpower around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Chandelure

**Type:** Ghost/Fire · **Final tier weight:** 4
**Role profile:** Atk 55 / Sp. Atk 145 / Spe 80 · Flash Fire, Flame Body, Infiltrator
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Clear Smog:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 11%; no Center/Tech Tutor overlap.*
- **Earlier power — Clear Smog around Lv. 17:** 50 BP; coverage. Treat this as the curve target, not a fixed slot.

### Charizard

**Type:** Fire/Flying · **Final tier weight:** 4
**Role profile:** Atk 84 / Sp. Atk 0 / Spe 100 · Blaze, Solar Power
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Focus Punch:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 9%; Tech Tutor (5 badges).*
- **Earlier power — Focus Punch around Lv. 56:** 150 BP; coverage. Treat this as the curve target, not a fixed slot.

### Chatot

**Type:** Normal/Flying · **Final tier weight:** 1
**Role profile:** Atk 65 / Sp. Atk 92 / Spe 91 · Keen Eye, Tangled Feet, Big Pecks
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Boomburst:** Its exceptional sound-producing anatomy justifies rare access to this premium attack. *Precedent: egg; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Add — Air Cutter:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/tutor; type-cohort prevalence 17%; Center Tutor (before Gym 3).*
- **Add — Synchronoise:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 6%; Tech Tutor (5 badges).*
- **Compatibility gap — Alluring Voice:** Verify or add TM/tutor compatibility rather than level-up access; a vocal mimic should receive the sound-based TM regardless of Fairy typing.
- **Earlier power — Boomburst around Lv. 51:** 140 BP; STAB. Treat this as the curve target, not a fixed slot.

### Chesnaught

**Type:** Grass/Fighting · **Final tier weight:** 4
**Role profile:** Atk 107 / Sp. Atk 74 / Spe 64 · Overgrow, Bulletproof
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Needle Arm:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/pre-evolution; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Needle Arm around Lv. 26:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Chi-Yu

**Type:** Dark/Fire · **Final tier weight:** 3
**Role profile:** Atk 80 / Sp. Atk 135 / Spe 100 · Beads Of Ruin
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Heat Wave:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: TM; type-cohort prevalence 23%; Center Tutor (before Gym 8).*
- **Add — Snarl:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: TM; type-cohort prevalence 23%; no Center/Tech Tutor overlap.*
- **Earlier power — Heat Wave around Lv. 58:** 95 BP; STAB. Treat this as the curve target, not a fixed slot.

### Chien-Pao

**Type:** Dark/Ice · **Final tier weight:** 3
**Role profile:** Atk 120 / Sp. Atk 90 / Spe 135 · Sword Of Ruin
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Psychic Fangs:** Its pronounced jaws or fangs give the unusual Psychic coverage a physical basis. *Precedent: TM; type-cohort prevalence 8%; Center Tutor (before Gym 7).*
- **Add — Snowscape:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 8%; no Center/Tech Tutor overlap.*
- **Earlier power — Psychic Fangs around Lv. 48:** 85 BP; coverage. Treat this as the curve target, not a fixed slot.

### Chimecho

**Type:** Psychic · **Final tier weight:** 2
**Role profile:** Atk 50 / Sp. Atk 95 / Spe 65 · Levitate
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Alluring Voice:** Its resonant cry and 95 Sp. Atk distinguish this from generic Fairy coverage. *Precedent: deliberate design exception; type-cohort prevalence 11%; no Center/Tech Tutor overlap.*
- **Add — Boomburst:** Its exceptional sound-producing anatomy justifies rare access to this premium attack. *Precedent: level-up/TM; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Boomburst around Lv. 52:** 140 BP; coverage. Treat this as the curve target, not a fixed slot.

### Cinccino

**Type:** Normal · **Final tier weight:** 4
**Role profile:** Atk 95 / Sp. Atk 65 / Spe 115 · Cute Charm, Technician, Skill Link
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Aqua Tail:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 12%; Center Tutor (before Gym 8).*
- **Earlier power — Aqua Tail around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Cinderace

**Type:** Fire · **Final tier weight:** 5
**Role profile:** Atk 116 / Sp. Atk 65 / Spe 119 · Blaze, Libero
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Clawitzer

**Type:** Water · **Final tier weight:** 2
**Role profile:** Atk 73 / Sp. Atk 120 / Spe 59 · Mega Launcher
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Bubble Beam:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 49%; no Center/Tech Tutor overlap.*
- **Add — Hydro Pump:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 93%; no Center/Tech Tutor overlap.*
- **Earlier power — Hydro Pump around Lv. 54:** 110 BP; STAB. Treat this as the curve target, not a fixed slot.

### Claydol

**Type:** Ground/Psychic · **Final tier weight:** 2
**Role profile:** Atk 70 / Sp. Atk 70 / Spe 75 · Levitate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Psychic Terrain:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 14%; Center Tutor (before Gym 7).*
- **Earlier power — Body Press around Lv. 44:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Clodsire

**Type:** Poison/Ground · **Final tier weight:** 4
**Role profile:** Atk 75 / Sp. Atk 45 / Spe 20 · Poison Point, Water Absorb, Unaware
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Recover:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Cloyster

**Type:** Water/Ice · **Final tier weight:** 4
**Role profile:** Atk 95 / Sp. Atk 85 / Spe 70 · Shell Armor, Skill Link, Overcoat
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Life Dew:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg; type-cohort prevalence 7%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Coalossal

**Type:** Rock/Fire · **Final tier weight:** 4
**Role profile:** Atk 80 / Sp. Atk 80 / Spe 30 · Steam Engine, Flame Body, Flash Fire
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Burn Up:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Burn Up around Lv. 58:** 130 BP; STAB. Treat this as the curve target, not a fixed slot.

### Cobalion

**Type:** Steel/Fighting · **Final tier weight:** 4
**Role profile:** Atk 90 / Sp. Atk 90 / Spe 108 · Justified
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Bounce:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/TM/tutor; type-cohort prevalence 6%; Center Tutor (before Gym 7).*
- **Earlier power — Bounce around Lv. 48:** 85 BP; coverage. Treat this as the curve target, not a fixed slot.

### Cofagrigus

**Type:** Ghost · **Final tier weight:** 3
**Role profile:** Atk 50 / Sp. Atk 95 / Spe 30 · Mummy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Fake Tears:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 19%; Tech Tutor (5 badges).*
- **Add — Ominous Wind:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 54%; Center Tutor (before Gym 3).*
- **Earlier power — Ominous Wind around Lv. 26:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Comfey

**Type:** Fairy · **Final tier weight:** 3
**Role profile:** Atk 52 / Sp. Atk 82 / Spe 100 · Flower Veil, Triage, Natural Cure
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Leaf Tornado:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 3%; no Center/Tech Tutor overlap.*
- **Add — Pollen Puff:** Its flower, pollen, or caregiving identity supports both the attack and ally-heal flavor. *Precedent: TM; type-cohort prevalence 9%; Center Tutor (before Gym 8).*
- **Earlier power — Pollen Puff around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Conkeldurr

**Type:** Fighting · **Final tier weight:** 4
**Role profile:** Atk 140 / Sp. Atk 55 / Spe 45 · Guts, Sheer Force, Iron Fist
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Force Palm:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 18%; no Center/Tech Tutor overlap.*
- **Earlier power — Force Palm around Lv. 26:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Copperajah

**Type:** Steel · **Final tier weight:** 3
**Role profile:** Atk 130 / Sp. Atk 80 / Spe 30 · Sheer Force, Heavy Metal
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Hard Press:** A heavy Steel elephant supplies both the mass and physical offense the move needs. *Precedent: TM; type-cohort prevalence 29%; no Center/Tech Tutor overlap.*
- **Add — Slam:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 8%; no Center/Tech Tutor overlap.*
- **Earlier power — Hard Press around Lv. 42:** up to 100 BP (HP-dependent); STAB. Treat this as the curve target, not a fixed slot.

### Corsola

**Type:** Water/Rock · **Final tier weight:** 1
**Role profile:** Atk 55 / Sp. Atk 65 / Spe 35 · Dedicated, Natural Cure, Regenerator
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Brine:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 15%; Center Tutor (before Gym 5).*
- **Add — Head Smash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Add — Liquidation:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 17%; Center Tutor (before Gym 7).*
- **Earlier power — Head Smash around Lv. 51:** 150 BP; STAB. Treat this as the curve target, not a fixed slot.

### Corviknight

**Type:** Flying/Steel · **Final tier weight:** 5
**Role profile:** Atk 87 / Sp. Atk 53 / Spe 67 · Pressure, Unnerve, Mirror Armor
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Sky Attack:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg/TM; type-cohort prevalence 4%; Center Tutor (before Gym 7).*
- **Earlier power — Sky Attack around Lv. 61:** 140 BP; STAB. Treat this as the curve target, not a fixed slot.

### Crabominable

**Type:** Fighting/Ice · **Final tier weight:** 2
**Role profile:** Atk 132 / Sp. Atk 62 / Spe 43 · Hyper Cutter, Iron Fist, Anger Point
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Superpower:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 22%; Center Tutor (League).*
- **Add — Dizzy Punch:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 3%; no Center/Tech Tutor overlap.*
- **Earlier power — Superpower around Lv. 54:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Cradily

**Type:** Rock/Grass · **Final tier weight:** 2
**Role profile:** Atk 81 / Sp. Atk 81 / Spe 43 · Suction Cups, Storm Drain
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Earth Power:** Its rooted fossil body and usable 81 Sp. Atk support special geological coverage. *Precedent: TM/tutor; type-cohort prevalence 22%; Center Tutor (before Gym 8).*
- **Add — Recover:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 11%; no Center/Tech Tutor overlap.*
- **Earlier power — Earth Power around Lv. 38:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Cramorant

**Type:** Flying/Water · **Final tier weight:** 2
**Role profile:** Atk 85 / Sp. Atk 85 / Spe 85 · Gulp Missile
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Aqua Cutter:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Aerial Ace:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 26%; Tech Tutor (7 badges).*
- **Earlier power — Aqua Cutter around Lv. 32:** 70 BP; STAB. Treat this as the curve target, not a fixed slot.

### Crawdaunt

**Type:** Water/Dark · **Final tier weight:** 3
**Role profile:** Atk 120 / Sp. Atk 90 / Spe 55 · Hyper Cutter, Shell Armor, Adaptability
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Dark Pulse:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM/tutor; type-cohort prevalence 15%; Center Tutor (before Gym 7).*
- **Add — Brine:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: deliberate design exception; type-cohort prevalence 4%; Center Tutor (before Gym 5).*
- **Mixed-offense branch:** Its 80 BP Dark Pulse STAB lets 95 Sp. Atk matter for a stretch without improving Crawdaunt's dominant physical Adaptability ceiling. Brine is the gentler 65 BP alternative.
- **Earlier power — Dark Pulse around Lv. 35:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Cresselia

**Type:** Psychic · **Final tier weight:** 4
**Role profile:** Atk 70 / Sp. Atk 75 / Spe 85 · Levitate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Recover:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 26%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Crobat

**Type:** Poison/Flying · **Final tier weight:** 5
**Role profile:** Atk 90 / Sp. Atk 70 / Spe 130 · Inner Focus, Infiltrator
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Brave Bird:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg/TM; type-cohort prevalence 4%; Center Tutor (League).*
- **Earlier power — Brave Bird around Lv. 61:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Crustle

**Type:** Bug/Rock · **Final tier weight:** 3
**Role profile:** Atk 105 / Sp. Atk 65 / Spe 45 · Sturdy, Shell Armor, Weak Armor
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Night Slash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 9%; no Center/Tech Tutor overlap.*
- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 9%; Center Tutor (before Gym 7).*
- **Earlier power — Body Press around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Cryogonal

**Type:** Ice · **Final tier weight:** 2
**Role profile:** Atk 50 / Sp. Atk 95 / Spe 105 · Levitate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Chilling Water:** 95 Sp. Atk makes the attack usable and its ice-crystal body supplies the chill. *Precedent: TM; type-cohort prevalence 54%; Center Tutor (before Gym 3).*
- **Add — Frost Breath:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 59%; Center Tutor (before Gym 8).*
- **Earlier power — Frost Breath around Lv. 22:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Cursola

**Type:** Ghost · **Final tier weight:** 3
**Role profile:** Atk 95 / Sp. Atk 145 / Spe 30 · Weak Armor, Perish Body
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Water Pulse:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg; type-cohort prevalence 14%; Center Tutor (before Gym 4).*
- **Add — Brine:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: TM; type-cohort prevalence 14%; Center Tutor (before Gym 5).*
- **Earlier power — Brine around Lv. 31:** 65 BP; coverage. Treat this as the curve target, not a fixed slot.

### Cyclizar

**Type:** Dragon/Normal · **Final tier weight:** 4
**Role profile:** Atk 95 / Sp. Atk 85 / Spe 121 · Shed Skin, Regenerator
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Power Whip:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 5%; Center Tutor (before Gym 8).*
- **Earlier power — Power Whip around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Dachsbun

**Type:** Fairy · **Final tier weight:** 4
**Role profile:** Atk 80 / Sp. Atk 50 / Spe 95 · Well Baked Body, Aroma Veil
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Wish:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 24%; Legacy Tutor.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Darkrai

**Type:** Dark · **Final tier weight:** 6
**Role profile:** Atk 90 / Sp. Atk 135 / Spe 125 · Bad Dreams
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Decidueye

**Type:** Grass/Ghost · **Final tier weight:** 3
**Role profile:** Atk 107 / Sp. Atk 100 / Spe 70 · Overgrow, Long Reach
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Ominous Wind:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg; type-cohort prevalence 9%; Center Tutor (before Gym 3).*
- **Add — Roost:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/TM; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Earlier power — Ominous Wind around Lv. 26:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Decidueye (Hisui)

**Type:** Grass/Fighting · **Final tier weight:** 3
**Role profile:** Atk 112 / Sp. Atk 95 / Spe 60 · Overgrow, Scrappy
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Roost:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Add — Aura Sphere:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 6%; Center Tutor (before Gym 7).*
- **Earlier power — Aura Sphere around Lv. 50:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Dedenne

**Type:** Electric/Fairy · **Final tier weight:** 2
**Role profile:** Atk 58 / Sp. Atk 81 / Spe 101 · Cheek Pouch, Pickup, Plus
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Rising Voltage:** A weak Electric/Fairy with terrain utility can own the terrain payoff without dominating it. *Precedent: tutor; type-cohort prevalence 3%; Center Tutor (before Gym 7).*
- **Add — Eerie Impulse:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 9%; Tech Tutor (5 badges).*
- **Earlier power — Rising Voltage around Lv. 36:** 70 BP; STAB. Treat this as the curve target, not a fixed slot.

### Delcatty

**Type:** Normal · **Final tier weight:** 1
**Role profile:** Atk 70 / Sp. Atk 55 / Spe 95 · Cute Charm, Normalize, Wonder Skin
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Sucker Punch:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 16%; Legacy Tutor.*
- **Add — Last Resort:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 45%; Center Tutor (before Gym 7).*
- **Add — Zen Headbutt:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 47%; Center Tutor (before Gym 7).*
- **Compatibility gap — Alluring Voice:** Verify or add TM/tutor compatibility rather than level-up access; its charm and voice-oriented support pool fit the broadly distributed sound TM.
- **Earlier power — Last Resort around Lv. 51:** 140 BP; STAB. Treat this as the curve target, not a fixed slot.

### Delibird

**Type:** Ice/Flying · **Final tier weight:** 1
**Role profile:** Atk 70 / Sp. Atk 75 / Spe 80 · Merry, Hustle, Vital Spirit
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Triple Axel:** Its low Attack and slapstick movement keep premium multi-hit Ice coverage in check. *Precedent: TM/tutor; type-cohort prevalence 5%; Center Tutor (League).*
- **Add — Freeze Dry:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg/TM; type-cohort prevalence 3%; no Center/Tech Tutor overlap.*
- **Add — Ice Punch:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 5%; Center Tutor (before Gym 7).*
- **Earlier power — Ice Punch around Lv. 35:** 75 BP; STAB. Treat this as the curve target, not a fixed slot.

### Delphox

**Type:** Fire/Psychic · **Final tier weight:** 4
**Role profile:** Atk 69 / Sp. Atk 114 / Spe 104 · Blaze, Magician
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Psychic Terrain:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Deoxys (Attack)

**Type:** Psychic · **Final tier weight:** 3
**Role profile:** Atk 180 / Sp. Atk 180 / Spe 150 · Pressure
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Toxic Spikes:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 9%; Center Tutor (before Gym 5).*
- **Add — Psycho Shift:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 16%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Deoxys (Defense)

**Type:** Psychic · **Final tier weight:** 3
**Role profile:** Atk 70 / Sp. Atk 70 / Spe 90 · Pressure
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Switcheroo:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Add — Psycho Shift:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 16%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Deoxys (Normal)

**Type:** Psychic · **Final tier weight:** 3
**Role profile:** Atk 150 / Sp. Atk 150 / Spe 150 · Pressure
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Switcheroo:** Its established sound motif makes this a strong identity move. *Precedent: level-up; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Add — Toxic Spikes:** Its established sound motif makes this a strong identity move. *Precedent: level-up; type-cohort prevalence 9%; Center Tutor (before Gym 5).*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Deoxys (Speed)

**Type:** Psychic · **Final tier weight:** 3
**Role profile:** Atk 95 / Sp. Atk 95 / Spe 180 · Pressure
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Toxic Spikes:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 9%; Center Tutor (before Gym 5).*
- **Add — Psycho Shift:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 16%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Dewgong

**Type:** Water/Ice · **Final tier weight:** 2
**Role profile:** Atk 70 / Sp. Atk 70 / Spe 70 · Thick Fat, Hydration, Ice Body
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Chilling Water:** An aquatic Ice type is a better natural owner than generic Water-compatible species. *Precedent: TM; type-cohort prevalence 54%; Center Tutor (before Gym 3).*
- **Add — Signal Beam:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/tutor; type-cohort prevalence 32%; Center Tutor (before Gym 6).*
- **Earlier power — Signal Beam around Lv. 36:** 75 BP; coverage. Treat this as the curve target, not a fixed slot.

### Dhelmise

**Type:** Ghost/Grass · **Final tier weight:** 2
**Role profile:** Atk 131 / Sp. Atk 86 / Spe 40 · Steelworker
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 14%; Center Tutor (before Gym 7).*
- **Add — Liquidation:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 2%; Center Tutor (before Gym 7).*
- **Earlier power — Liquidation around Lv. 44:** 85 BP; coverage. Treat this as the curve target, not a fixed slot.

### Dialga

**Type:** Steel/Dragon · **Final tier weight:** 3
**Role profile:** Atk 120 / Sp. Atk 150 / Spe 90 · Pressure, Telepathy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Dragon Pulse:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM/tutor; type-cohort prevalence 15%; Center Tutor (before Gym 7).*
- **Add — Hyper Voice:** Its voice, cry, song, or sound-based identity makes this natural level-up expression. *Precedent: TM/tutor; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Earlier power — Hyper Voice around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Diancie

**Type:** Rock/Fairy · **Final tier weight:** 4
**Role profile:** Atk 100 / Sp. Atk 100 / Spe 50 · Clear Body
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Draining Kiss:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 2%; Center Tutor (before Gym 4).*
- **Earlier power — Draining Kiss around Lv. 19:** 50 BP; STAB. Treat this as the curve target, not a fixed slot.

### Diggersby

**Type:** Normal/Ground · **Final tier weight:** 4
**Role profile:** Atk 56 / Sp. Atk 50 / Spe 78 · Pickup, Cheek Pouch, Huge Power
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Spikes:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg/TM; type-cohort prevalence 3%; Center Tutor (before Gym 4).*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Ditto

**Type:** Normal · **Final tier weight:** 2
**Role profile:** Atk 48 / Sp. Atk 48 / Spe 48 · Limber, Imposter
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Dodrio

**Type:** Normal/Flying · **Final tier weight:** 3
**Role profile:** Atk 110 / Sp. Atk 60 / Spe 110 · Run Away, Early Bird, Tangled Feet
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Brave Bird:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 14%; Center Tutor (League).*
- **Add — Sky Attack:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 17%; Center Tutor (before Gym 7).*
- **Earlier power — Sky Attack around Lv. 58:** 140 BP; STAB. Treat this as the curve target, not a fixed slot.

### Dondozo

**Type:** Water · **Final tier weight:** 5
**Role profile:** Atk 100 / Sp. Atk 65 / Spe 35 · Unaware, Oblivious, Water Veil
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Donphan

**Type:** Ground · **Final tier weight:** 3
**Role profile:** Atk 120 / Sp. Atk 60 / Spe 50 · Sturdy, Sand Veil
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — High Horsepower:** A charging elephant distinguishes this from its existing seismic Earthquake identity. *Precedent: egg/TM; type-cohort prevalence 71%; Center Tutor (before Gym 8).*
- **Add — Play Rough:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg/TM; type-cohort prevalence 7%; Center Tutor (before Gym 8).*
- **Earlier power — High Horsepower around Lv. 38:** 95 BP; STAB. Treat this as the curve target, not a fixed slot.

### Dracovish

**Type:** Water/Dragon · **Final tier weight:** 5
**Role profile:** Atk 90 / Sp. Atk 70 / Spe 75 · Water Absorb, Strong Jaw, Sand Rush
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Dracozolt

**Type:** Electric/Dragon · **Final tier weight:** 4
**Role profile:** Atk 100 / Sp. Atk 80 / Spe 75 · Volt Absorb, Hustle, Sand Rush
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Wild Charge:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 17%; Center Tutor (before Gym 8).*
- **Earlier power — Wild Charge around Lv. 58:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Dragalge

**Type:** Poison/Dragon · **Final tier weight:** 3
**Role profile:** Atk 75 / Sp. Atk 97 / Spe 44 · Poison Point, Poison Touch, Adaptability
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Dragon Tail:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 17%; Tech Tutor (7 badges).*
- **Add — Sludge Wave:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 13%; Center Tutor (before Gym 8).*
- **Earlier power — Sludge Wave around Lv. 58:** 95 BP; STAB. Treat this as the curve target, not a fixed slot.

### Dragapult

**Type:** Dragon/Ghost · **Final tier weight:** 6
**Role profile:** Atk 120 / Sp. Atk 100 / Spe 142 · Clear Body, Infiltrator, Cursed Body
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Sucker Punch:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 13%; Legacy Tutor.*
- **Earlier power — Sucker Punch around Lv. 37:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Dragonite

**Type:** Dragon/Flying · **Final tier weight:** 5
**Role profile:** Atk 134 / Sp. Atk 100 / Spe 80 · Inner Focus, Multiscale
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Drampa

**Type:** Normal/Dragon · **Final tier weight:** 3
**Role profile:** Atk 60 / Sp. Atk 135 / Spe 36 · Berserk, Sap Sipper, Cloud Nine
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Razor Wind:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 14%; no Center/Tech Tutor overlap.*
- **Add — Hurricane:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 14%; no Center/Tech Tutor overlap.*
- **Earlier power — Hurricane around Lv. 56:** 110 BP; coverage. Treat this as the curve target, not a fixed slot.

### Drapion

**Type:** Poison/Dark · **Final tier weight:** 4
**Role profile:** Atk 90 / Sp. Atk 60 / Spe 95 · Battle Armor, Sniper, Keen Eye
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Poison Tail:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 6%; Center Tutor (before Gym 2).*
- **Earlier power — Poison Tail around Lv. 19:** 50 BP; STAB. Treat this as the curve target, not a fixed slot.

### Drednaw

**Type:** Water/Rock · **Final tier weight:** 4
**Role profile:** Atk 115 / Sp. Atk 48 / Spe 74 · Strong Jaw, Shell Armor, Swift Swim
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Skull Bash:** Its jaw-based anatomy gives the coverage a concrete physical source. *Precedent: egg; type-cohort prevalence 17%; Center Tutor (before Gym 6).*
- **Earlier power — Skull Bash around Lv. 56:** 130 BP; coverage. Treat this as the curve target, not a fixed slot.

### Drifblim

**Type:** Ghost/Flying · **Final tier weight:** 3
**Role profile:** Atk 80 / Sp. Atk 90 / Spe 80 · Flare Boost, Unburden, Thermal Exchange
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Weather Ball:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/TM; type-cohort prevalence 5%; Center Tutor (before Gym 7).*
- **Add — Clear Smog:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Weather Ball around Lv. 17:** 50 BP; coverage. Treat this as the curve target, not a fixed slot.

### Druddigon

**Type:** Dragon · **Final tier weight:** 2
**Role profile:** Atk 120 / Sp. Atk 60 / Spe 48 · Rough Skin, Sheer Force, Mold Breaker
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Scale Shot:** Its rough scales and low Speed make this a literal and balanced fit. *Precedent: tutor; type-cohort prevalence 66%; Center Tutor (before Gym 7).*
- **Add — Night Slash:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg; type-cohort prevalence 9%; no Center/Tech Tutor overlap.*
- **Earlier power — Night Slash around Lv. 30:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Dubwool

**Type:** Normal · **Final tier weight:** 3
**Role profile:** Atk 80 / Sp. Atk 60 / Spe 88 · Fluffy, Steadfast, Bulletproof
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Stomp:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 17%; no Center/Tech Tutor overlap.*
- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 19%; Center Tutor (before Gym 7).*
- **Earlier power — Body Press around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Dugtrio

**Type:** Ground · **Final tier weight:** 3
**Role profile:** Atk 100 / Sp. Atk 50 / Spe 120 · Sand Veil, Arena Trap, Sand Force
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Rock Slide:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 93%; no Center/Tech Tutor overlap.*
- **Add — Screech:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 31%; Tech Tutor (5 badges).*
- **Earlier power — Rock Slide around Lv. 40:** 75 BP; coverage. Treat this as the curve target, not a fixed slot.

### Dugtrio (Alola)

**Type:** Ground/Steel · **Final tier weight:** 3
**Role profile:** Atk 100 / Sp. Atk 50 / Spe 110 · Sand Veil, Tangling Hair, Sand Force
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Thrash:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Add — Headbutt:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg/TM; type-cohort prevalence 48%; Center Tutor (before Gym 3).*
- **Earlier power — Thrash around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Durant

**Type:** Bug/Steel · **Final tier weight:** 4
**Role profile:** Atk 109 / Sp. Atk 48 / Spe 109 · Swarm, Hustle, Truant
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — First Impression:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power — First Impression around Lv. 58:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Dusknoir

**Type:** Ghost · **Final tier weight:** 3
**Role profile:** Atk 100 / Sp. Atk 65 / Spe 45 · Pressure, Frisk
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Poltergeist:** 100 Attack makes physical Ghost STAB valuable while low Speed restrains it. *Precedent: TM/tutor; type-cohort prevalence 81%; Center Tutor (before Gym 8).*
- **Add — Leech Life:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM/tutor; type-cohort prevalence 8%; Center Tutor (before Gym 7).*
- **Earlier power — Poltergeist around Lv. 46:** 110 BP; STAB. Treat this as the curve target, not a fixed slot.

### Dustox

**Type:** Bug/Poison · **Final tier weight:** 2
**Role profile:** Atk 50 / Sp. Atk 50 / Spe 65 · Shield Dust, Corrosion, Compound Eyes
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Silver Wind:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/TM; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Add — Sludge Bomb:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: TM/tutor; type-cohort prevalence 23%; no Center/Tech Tutor overlap.*
- **Earlier setup — Quiver Dance around Lv. 30:** Move it forward from Lv. 40; low offenses keep the boost from becoming an early sweep button. Do not pair this access with Baton Pass.
- **Earlier power — Sludge Bomb around Lv. 54:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Eelektross

**Type:** Electric · **Final tier weight:** 2
**Role profile:** Atk 115 / Sp. Atk 105 / Spe 50 · Levitate
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Liquidation:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 6%; Center Tutor (before Gym 7).*
- **Add — Spark:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/pre-evolution/TM; type-cohort prevalence 62%; no Center/Tech Tutor overlap.*
- **Earlier power — Liquidation around Lv. 44:** 85 BP; coverage. Treat this as the curve target, not a fixed slot.

### Eldegoss

**Type:** Grass · **Final tier weight:** 4
**Role profile:** Atk 50 / Sp. Atk 80 / Spe 60 · Cotton Down, Regenerator, Effect Spore
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Pollen Puff:** Its flower, pollen, or caregiving identity supports both the attack and ally-heal flavor. *Precedent: TM; type-cohort prevalence 26%; Center Tutor (before Gym 8).*
- **Earlier power — Pollen Puff around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Electivire

**Type:** Electric · **Final tier weight:** 3
**Role profile:** Atk 123 / Sp. Atk 95 / Spe 95 · Motor Drive, Vital Spirit
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Fire Punch:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 22%; Center Tutor (before Gym 7).*
- **Add — Hammer Arm:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Hammer Arm around Lv. 56:** 100 BP; coverage. Treat this as the curve target, not a fixed slot.

### Electrode

**Type:** Electric · **Final tier weight:** 2
**Role profile:** Atk 50 / Sp. Atk 80 / Spe 150 · Soundproof, Static, Aftermath
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Thunderbolt:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM/tutor; type-cohort prevalence 100%; no Center/Tech Tutor overlap.*
- **Add — Recycle:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 10%; Center Tutor (before Gym 5).*
- **Earlier power — Thunderbolt around Lv. 54:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Electrode (Hisui)

**Type:** Electric/Grass · **Final tier weight:** 2
**Role profile:** Atk 50 / Sp. Atk 80 / Spe 150 · Soundproof, Static, Aftermath
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Thunderbolt:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM/tutor; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Add — Thunder:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Earlier power — Thunder around Lv. 54:** 110 BP; STAB. Treat this as the curve target, not a fixed slot.

### Emboar

**Type:** Fire/Fighting · **Final tier weight:** 3
**Role profile:** Atk 123 / Sp. Atk 100 / Spe 65 · Blaze, Reckless
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Superpower:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 19%; Center Tutor (League).*
- **Add — Flame Wheel:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power — Superpower around Lv. 58:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Emolga

**Type:** Electric/Flying · **Final tier weight:** 2
**Role profile:** Atk 75 / Sp. Atk 75 / Spe 103 · Static, Motor Drive
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Air Slash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 6%; Center Tutor (before Gym 6).*
- **Add — Shock Wave:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/tutor; type-cohort prevalence 20%; Tech Tutor (7 badges).*
- **Earlier power — Air Slash around Lv. 38:** 75 BP; STAB. Treat this as the curve target, not a fixed slot.

### Empoleon

**Type:** Water/Steel · **Final tier weight:** 4
**Role profile:** Atk 86 / Sp. Atk 111 / Spe 60 · Torrent, Competitive
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Roost:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 8%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Entei

**Type:** Fire · **Final tier weight:** 4
**Role profile:** Atk 115 / Sp. Atk 90 / Spe 100 · Pressure, Inner Focus
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Flamethrower:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM/tutor; type-cohort prevalence 98%; no Center/Tech Tutor overlap.*
- **Earlier power — Flamethrower around Lv. 58:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Escavalier

**Type:** Bug/Steel · **Final tier weight:** 4
**Role profile:** Atk 135 / Sp. Atk 60 / Spe 20 · Swarm, Shell Armor, Overcoat
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Slash:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/egg; type-cohort prevalence 25%; no Center/Tech Tutor overlap.*
- **Earlier power — Slash around Lv. 34:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Espathra

**Type:** Psychic · **Final tier weight:** 3
**Role profile:** Atk 60 / Sp. Atk 101 / Spe 105 · Opportunist, Frisk, Speed Boost
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Hyper Voice:** Its voice, cry, song, or sound-based identity makes this natural level-up expression. *Precedent: TM; type-cohort prevalence 24%; no Center/Tech Tutor overlap.*
- **Add — Roost:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 12%; no Center/Tech Tutor overlap.*
- **Earlier power — Hyper Voice around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Espeon

**Type:** Psychic · **Final tier weight:** 4
**Role profile:** Atk 65 / Sp. Atk 130 / Spe 110 · Synchronize, Synchronize, Magic Bounce
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Synchronoise:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 14%; Tech Tutor (5 badges).*
- **Earlier power — Synchronoise around Lv. 58:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Eternatus

**Type:** Poison/Dragon · **Final tier weight:** 3
**Role profile:** Atk 85 / Sp. Atk 145 / Spe 130 · Pressure
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Eternabeam:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Mystical Fire:** Its supernatural or elegant fire identity makes the move feel native rather than generic coverage. *Precedent: TM; type-cohort prevalence 2%; Center Tutor (before Gym 6).*
- **Earlier power — Eternabeam around Lv. 58:** 160 BP; STAB. Treat this as the curve target, not a fixed slot.

### Excadrill

**Type:** Ground/Steel · **Final tier weight:** 5
**Role profile:** Atk 135 / Sp. Atk 50 / Spe 88 · Sand Rush, Sand Force, Mold Breaker
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Slash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 21%; no Center/Tech Tutor overlap.*
- **Earlier power — Slash around Lv. 37:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Exeggutor

**Type:** Grass/Psychic · **Final tier weight:** 3
**Role profile:** Atk 95 / Sp. Atk 125 / Spe 55 · Chlorophyll, Harvest
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Moonlight:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 8%; Legacy Tutor.*
- **Add — Stun Spore:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/pre-evolution; type-cohort prevalence 1%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Exeggutor (Alola)

**Type:** Grass/Dragon · **Final tier weight:** 3
**Role profile:** Atk 105 / Sp. Atk 125 / Spe 45 · Frisk, Harvest
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Moonlight:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; Legacy Tutor.*
- **Add — Stun Spore:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/pre-evolution; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Exploud

**Type:** Normal · **Final tier weight:** 2
**Role profile:** Atk 91 / Sp. Atk 91 / Spe 68 · Soundproof, Dominate, Scrappy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Smelling Salts:** Its established sound motif makes this a strong identity move. *Precedent: egg; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Add — Circle Throw:** Its established sound motif makes this a strong identity move. *Precedent: egg; type-cohort prevalence 6%; Tech Tutor (7 badges).*
- **Earlier power — Smelling Salts around Lv. 32:** 70 BP; STAB. Treat this as the curve target, not a fixed slot.

### Falinks

**Type:** Fighting · **Final tier weight:** 4
**Role profile:** Atk 100 / Sp. Atk 70 / Spe 75 · Battle Armor, Defiant
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Brick Break:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 95%; no Center/Tech Tutor overlap.*
- **Earlier power — Brick Break around Lv. 42:** 75 BP; STAB. Treat this as the curve target, not a fixed slot.

### Farfetch'd

**Type:** Normal/Flying · **Final tier weight:** 3
**Role profile:** Atk 90 / Sp. Atk 58 / Spe 60 · Keen Eye, Inner Focus, Defiant
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Sky Attack:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/tutor; type-cohort prevalence 17%; Center Tutor (before Gym 7).*
- **Add — First Impression:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Sky Attack around Lv. 58:** 140 BP; STAB. Treat this as the curve target, not a fixed slot.

### Farigiraf

**Type:** Normal/Psychic · **Final tier weight:** 4
**Role profile:** Atk 90 / Sp. Atk 110 / Spe 60 · Cud Chew, Armor Tail, Sap Sipper
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Future Sight:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 9%; Center Tutor (before Gym 7).*
- **Earlier power — Future Sight around Lv. 58:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Fearow

**Type:** Normal/Flying · **Final tier weight:** 2
**Role profile:** Atk 90 / Sp. Atk 61 / Spe 100 · Keen Eye, Sniper
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Sky Attack:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 17%; Center Tutor (before Gym 7).*
- **Add — Tri Attack:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 6%; Center Tutor (before Gym 6).*
- **Earlier power — Sky Attack around Lv. 54:** 140 BP; STAB. Treat this as the curve target, not a fixed slot.

### Feraligatr

**Type:** Water · **Final tier weight:** 3
**Role profile:** Atk 105 / Sp. Atk 79 / Spe 78 · Torrent, Sheer Force
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Dragon Claw:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Add — Chip Away:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power — Dragon Claw around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Ferrothorn

**Type:** Grass/Steel · **Final tier weight:** 5
**Role profile:** Atk 94 / Sp. Atk 54 / Spe 20 · Iron Barbs, Anticipation
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Rock Climb:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg; type-cohort prevalence 11%; Center Tutor (before Gym 7).*
- **Earlier power — Rock Climb around Lv. 59:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Fezandipiti

**Type:** Poison/Fairy · **Final tier weight:** 4
**Role profile:** Atk 91 / Sp. Atk 70 / Spe 99 · Toxic Chain, Technician
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Acid Spray:** Its established sound motif makes this a strong identity move. *Precedent: TM; type-cohort prevalence 6%; Center Tutor (before Gym 3).*
- **Earlier power — Acid Spray around Lv. 15:** 40 BP; STAB. Treat this as the curve target, not a fixed slot.

### Flamigo

**Type:** Flying/Fighting · **Final tier weight:** 4
**Role profile:** Atk 115 / Sp. Atk 75 / Spe 90 · Scrappy, Tangled Feet, Costar
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Sky Attack:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 5%; Center Tutor (before Gym 7).*
- **Earlier power — Sky Attack around Lv. 58:** 140 BP; STAB. Treat this as the curve target, not a fixed slot.

### Flapple

**Type:** Grass/Dragon · **Final tier weight:** 2
**Role profile:** Atk 110 / Sp. Atk 95 / Spe 70 · Ripen, Gluttony, Hustle
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Sucker Punch:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 13%; Legacy Tutor.*
- **Add — Trailblaze:** Its terrestrial movement and plant association support an active Grass attack rather than generic TM access. *Precedent: TM; type-cohort prevalence 13%; Center Tutor (before Gym 3).*
- **Earlier power — Sucker Punch around Lv. 30:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Flareon

**Type:** Fire · **Final tier weight:** 2
**Role profile:** Atk 130 / Sp. Atk 95 / Spe 65 · Flash Fire, Flash Fire, Guts
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Temper Flare:** 130 Attack and an emotional Fire identity give it valuable physical STAB with a condition. *Precedent: TM; type-cohort prevalence 57%; no Center/Tech Tutor overlap.*
- **Add — Yawn:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 17%; no Center/Tech Tutor overlap.*
- **Earlier power — Temper Flare around Lv. 38:** 75 BP; STAB. Treat this as the curve target, not a fixed slot.

### Floatzel

**Type:** Water · **Final tier weight:** 4
**Role profile:** Atk 105 / Sp. Atk 85 / Spe 115 · Swift Swim, Water Veil
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Slash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 16%; no Center/Tech Tutor overlap.*
- **Earlier power — Slash around Lv. 34:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Flutter Mane

**Type:** Ghost/Fairy · **Final tier weight:** 3
**Role profile:** Atk 55 / Sp. Atk 135 / Spe 135 · Protosynthesis
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Disarming Voice:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 5%; Tech Tutor (7 badges).*
- **Add — Hyper Voice:** Its voice, cry, song, or sound-based identity makes this natural level-up expression. *Precedent: TM; type-cohort prevalence 11%; no Center/Tech Tutor overlap.*
- **Earlier power — Hyper Voice around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Flygon

**Type:** Ground/Dragon · **Final tier weight:** 3
**Role profile:** Atk 100 / Sp. Atk 80 / Spe 100 · Levitate, Levitate, Levitate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — First Impression:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Bug Bite:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/TM/tutor; type-cohort prevalence 4%; Center Tutor (before Gym 3).*
- **Earlier power — First Impression around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Forretress

**Type:** Bug/Steel · **Final tier weight:** 4
**Role profile:** Atk 90 / Sp. Atk 60 / Spe 40 · Sturdy, Overcoat
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Reflect:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/egg/TM; type-cohort prevalence 26%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Froslass

**Type:** Ice/Ghost · **Final tier weight:** 3
**Role profile:** Atk 80 / Sp. Atk 80 / Spe 110 · Snow Cloak, Cursed Body
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Icicle Crash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 3%; no Center/Tech Tutor overlap.*
- **Add — Weather Ball:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 5%; Center Tutor (before Gym 7).*
- **Earlier power — Icicle Crash around Lv. 50:** 85 BP; STAB. Treat this as the curve target, not a fixed slot.

### Frosmoth

**Type:** Ice/Bug · **Final tier weight:** 3
**Role profile:** Atk 65 / Sp. Atk 125 / Spe 65 · Shield Dust, Ice Scales
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Weather Ball:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: TM; type-cohort prevalence 6%; Center Tutor (before Gym 7).*
- **Add — Hurricane:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: TM; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Earlier power — Hurricane around Lv. 56:** 110 BP; coverage. Treat this as the curve target, not a fixed slot.

### Furret

**Type:** Normal · **Final tier weight:** 1
**Role profile:** Atk 76 / Sp. Atk 45 / Spe 90 · Run Away, Keen Eye, Covered
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Last Resort:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 45%; Center Tutor (before Gym 7).*
- **Add — Slash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 20%; no Center/Tech Tutor overlap.*
- **Add — Iron Tail:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 47%; Center Tutor (before Gym 7).*
- **Earlier power — Last Resort around Lv. 51:** 140 BP; STAB. Treat this as the curve target, not a fixed slot.

### Gallade

**Type:** Psychic/Fighting · **Final tier weight:** 4
**Role profile:** Atk 125 / Sp. Atk 65 / Spe 80 · Steadfast, Sharpness, Justified
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Misty Terrain:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 5%; Tech Tutor (3 badges).*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Galvantula

**Type:** Bug/Electric · **Final tier weight:** 3
**Role profile:** Atk 77 / Sp. Atk 97 / Spe 108 · Compound Eyes, Unnerve, Swarm
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Struggle Bug:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 4%; Center Tutor (before Gym 2).*
- **Add — Lunge:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 6%; Center Tutor (before Gym 7).*
- **Earlier power — Lunge around Lv. 50:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Garbodor

**Type:** Poison · **Final tier weight:** 2
**Role profile:** Atk 95 / Sp. Atk 60 / Spe 75 · Stench, Weak Armor, Aftermath
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Self Destruct:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 23%; Center Tutor (before Gym 6).*
- **Add — Sludge Wave:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 83%; Center Tutor (before Gym 8).*
- **Earlier power — Self Destruct around Lv. 52:** 200 BP; coverage. Treat this as the curve target, not a fixed slot.

### Garchomp

**Type:** Dragon/Ground · **Final tier weight:** 5
**Role profile:** Atk 130 / Sp. Atk 80 / Spe 102 · Sand Veil, Rough Skin
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Outrage:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 26%; Center Tutor (before Gym 7).*
- **Earlier power — Outrage around Lv. 61:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Gardevoir

**Type:** Psychic/Fairy · **Final tier weight:** 4
**Role profile:** Atk 65 / Sp. Atk 125 / Spe 80 · Synchronize, Trace, Telepathy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Synchronoise:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 9%; Tech Tutor (5 badges).*
- **Earlier power — Synchronoise around Lv. 58:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Garganacl

**Type:** Rock · **Final tier weight:** 5
**Role profile:** Atk 100 / Sp. Atk 45 / Spe 35 · Purifying Salt, Sturdy, Clear Body
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Gengar

**Type:** Ghost/Poison · **Final tier weight:** 4
**Role profile:** Atk 65 / Sp. Atk 130 / Spe 110 · unknown
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Clear Smog:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 11%; no Center/Tech Tutor overlap.*
- **Earlier power — Clear Smog around Lv. 19:** 50 BP; STAB. Treat this as the curve target, not a fixed slot.

### Gholdengo

**Type:** Steel/Ghost · **Final tier weight:** 5
**Role profile:** Atk 60 / Sp. Atk 133 / Spe 84 · Good As Gold
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Gigalith

**Type:** Rock · **Final tier weight:** 4
**Role profile:** Atk 135 / Sp. Atk 60 / Spe 25 · Sturdy, Sand Stream, Solar Core
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Rock Tomb:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 100%; no Center/Tech Tutor overlap.*
- **Earlier power — Rock Tomb around Lv. 26:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Glaceon

**Type:** Ice · **Final tier weight:** 2
**Role profile:** Atk 60 / Sp. Atk 130 / Spe 65 · Snow Cloak, Snow Cloak, Ice Body
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Synchronoise:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 3%; Tech Tutor (5 badges).*
- **Add — Ice Beam:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM/tutor; type-cohort prevalence 95%; no Center/Tech Tutor overlap.*
- **Earlier power — Synchronoise around Lv. 52:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Glalie

**Type:** Ice · **Final tier weight:** 1
**Role profile:** Atk 80 / Sp. Atk 80 / Spe 80 · Inner Focus, Ice Body, Moody
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Chilling Water:** Melting or spraying icy water gives a low-tier Ice type early physical mitigation. *Precedent: TM; type-cohort prevalence 54%; Center Tutor (before Gym 3).*
- **Add — Icicle Crash:** Its established sound motif makes this a strong identity move. *Precedent: level-up/egg/TM; type-cohort prevalence 46%; no Center/Tech Tutor overlap.*
- **Add — Fake Tears:** Its established sound motif makes this a strong identity move. *Precedent: level-up/egg/TM; type-cohort prevalence 19%; Tech Tutor (5 badges).*
- **Earlier power — Icicle Crash around Lv. 43:** 85 BP; STAB. Treat this as the curve target, not a fixed slot.

### Glastrier

**Type:** Ice · **Final tier weight:** 4
**Role profile:** Atk 145 / Sp. Atk 65 / Spe 30 · Chilling Neigh
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 43%; Center Tutor (before Gym 7).*
- **Earlier power — Body Press around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Glimmora

**Type:** Rock/Poison · **Final tier weight:** 6
**Role profile:** Atk 55 / Sp. Atk 130 / Spe 86 · Toxic Debris, Corrosion
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Gliscor

**Type:** Ground/Flying · **Final tier weight:** 4
**Role profile:** Atk 95 / Sp. Atk 45 / Spe 95 · Hyper Cutter, Sand Veil, Poison Heal
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Wing Attack:** Its established sound motif makes this a strong identity move. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Wing Attack around Lv. 26:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Gogoat

**Type:** Grass · **Final tier weight:** 3
**Role profile:** Atk 100 / Sp. Atk 97 / Spe 68 · Sap Sipper, Grass Pelt
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Grassy Terrain:** A terrestrial physical grazer can use terrain as sustain and team support. *Precedent: egg/TM; type-cohort prevalence 83%; no Center/Tech Tutor overlap.*
- **Add — Megahorn:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 6%; Center Tutor (before Gym 8).*
- **Earlier power — Megahorn around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Golduck

**Type:** Water · **Final tier weight:** 2
**Role profile:** Atk 82 / Sp. Atk 95 / Spe 85 · Mystic, Cloud Nine, Swift Swim
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Clear Smog:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Add — Psybeam:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 12%; Center Tutor (before Gym 4).*
- **Earlier power — Psybeam around Lv. 27:** 65 BP; coverage. Treat this as the curve target, not a fixed slot.

### Golem

**Type:** Rock/Ground · **Final tier weight:** 3
**Role profile:** Atk 120 / Sp. Atk 55 / Spe 45 · Rock Head, Sturdy, Sand Force
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Rock Slide:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 93%; no Center/Tech Tutor overlap.*
- **Add — Mega Punch:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 19%; Center Tutor (before Gym 5).*
- **Earlier power — Mega Punch around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Golem (Alola)

**Type:** Rock/Electric · **Final tier weight:** 3
**Role profile:** Atk 120 / Sp. Atk 55 / Spe 45 · Magnet Pull, Sturdy, Galvanize
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Rock Climb:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg; type-cohort prevalence 10%; Center Tutor (before Gym 7).*
- **Add — Steamroller:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Rock Climb around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Golisopod

**Type:** Bug/Water · **Final tier weight:** 5
**Role profile:** Atk 125 / Sp. Atk 60 / Spe 40 · Emergency Exit
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Metal Claw:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 6%; Center Tutor (before Gym 2).*
- **Earlier power — Metal Claw around Lv. 20:** 50 BP; coverage. Treat this as the curve target, not a fixed slot.

### Golurk

**Type:** Ground/Ghost · **Final tier weight:** 3
**Role profile:** Atk 124 / Sp. Atk 55 / Spe 55 · Iron Fist, Klutz, No Guard
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Bulldoze:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 35%; Center Tutor (before Gym 4).*
- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 14%; Center Tutor (before Gym 7).*
- **Earlier power — Body Press around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Goodra

**Type:** Dragon · **Final tier weight:** 4
**Role profile:** Atk 100 / Sp. Atk 110 / Spe 80 · Sap Sipper, Hydration, Gooey
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Life Dew:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Goodra (Hisui)

**Type:** Dragon/Steel · **Final tier weight:** 4
**Role profile:** Atk 100 / Sp. Atk 110 / Spe 60 · Sap Sipper, Shell Armor, Gooey
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Life Dew:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Gorebyss

**Type:** Water · **Final tier weight:** 3
**Role profile:** Atk 84 / Sp. Atk 114 / Spe 52 · Swift Swim, Hydration
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Brine:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 60%; Center Tutor (before Gym 5).*
- **Add — Muddy Water:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 50%; Center Tutor (before Gym 8).*
- **Earlier power — Muddy Water around Lv. 58:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Gothitelle

**Type:** Psychic · **Final tier weight:** 3
**Role profile:** Atk 55 / Sp. Atk 95 / Spe 65 · Astral Charge, Competitive, Shadow Tag
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Uproar:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 31%; Tech Tutor (6 badges).*
- **Add — Dark Pulse:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 22%; Center Tutor (before Gym 7).*
- **Earlier power — Uproar around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Gouging Fire

**Type:** Fire/Dragon · **Final tier weight:** 3
**Role profile:** Atk 115 / Sp. Atk 65 / Spe 91 · Protosynthesis
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Psychic Fangs:** Its pronounced jaws or fangs give the unusual Psychic coverage a physical basis. *Precedent: TM; type-cohort prevalence 11%; Center Tutor (before Gym 7).*
- **Add — Dragon Tail:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 11%; Tech Tutor (7 badges).*
- **Earlier power — Psychic Fangs around Lv. 48:** 85 BP; coverage. Treat this as the curve target, not a fixed slot.

### Grafaiai

**Type:** Poison/Normal · **Final tier weight:** 2
**Role profile:** Atk 95 / Sp. Atk 80 / Spe 110 · Unburden, Poison Touch, Prankster
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Cross Poison:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 3%; Center Tutor (before Gym 5).*
- **Add — Parting Shot:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Earlier power — Cross Poison around Lv. 32:** 70 BP; STAB. Treat this as the curve target, not a fixed slot.

### Granbull

**Type:** Fairy · **Final tier weight:** 2
**Role profile:** Atk 120 / Sp. Atk 60 / Spe 45 · Intimidate, Quick Feet, Rattled
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Smelling Salts:** Its jaw-based anatomy gives the coverage a concrete physical source. *Precedent: egg; type-cohort prevalence 3%; no Center/Tech Tutor overlap.*
- **Add — Retaliate:** Its jaw-based anatomy gives the coverage a concrete physical source. *Precedent: egg/TM; type-cohort prevalence 15%; Tech Tutor (8 badges).*
- **Earlier power — Smelling Salts around Lv. 30:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Grapploct

**Type:** Fighting · **Final tier weight:** 3
**Role profile:** Atk 118 / Sp. Atk 70 / Spe 42 · Limber, Technician
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Circle Throw:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 16%; Tech Tutor (7 badges).*
- **Add — Sucker Punch:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 15%; Legacy Tutor.*
- **Earlier power — Sucker Punch around Lv. 34:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Great Tusk

**Type:** Ground/Fighting · **Final tier weight:** 3
**Role profile:** Atk 131 / Sp. Atk 53 / Spe 87 · Protosynthesis
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 36%; Center Tutor (before Gym 7).*
- **Add — Play Rough:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 5%; Center Tutor (before Gym 8).*
- **Earlier power — Play Rough around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Greedent

**Type:** Normal · **Final tier weight:** 3
**Role profile:** Atk 95 / Sp. Atk 55 / Spe 20 · Cheek Pouch, Gluttony
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Last Resort:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 45%; Center Tutor (before Gym 7).*
- **Add — Psychic Fangs:** Its pronounced jaws or fangs give the unusual Psychic coverage a physical basis. *Precedent: TM; type-cohort prevalence 8%; Center Tutor (before Gym 7).*
- **Earlier power — Last Resort around Lv. 58:** 140 BP; STAB. Treat this as the curve target, not a fixed slot.

### Greninja

**Type:** Water/Dark · **Final tier weight:** 5
**Role profile:** Atk 95 / Sp. Atk 103 / Spe 122 · Torrent, Protean
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Grimmsnarl

**Type:** Dark/Fairy · **Final tier weight:** 4
**Role profile:** Atk 120 / Sp. Atk 95 / Spe 60 · Prankster, Pickpocket, Frisk
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 12%; Center Tutor (before Gym 7).*
- **Earlier power — Body Press around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Groudon

**Type:** Ground · **Final tier weight:** 3
**Role profile:** Atk 150 / Sp. Atk 100 / Spe 90 · Drought
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Stone Edge:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 88%; Center Tutor (before Gym 7).*
- **Add — Dynamic Punch:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM/tutor; type-cohort prevalence 21%; Tech Tutor (5 badges).*
- **Earlier power — Stone Edge around Lv. 56:** 100 BP; coverage. Treat this as the curve target, not a fixed slot.

### Grumpig

**Type:** Psychic · **Final tier weight:** 3
**Role profile:** Atk 45 / Sp. Atk 90 / Spe 80 · Thick Fat, Own Tempo, Gluttony
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Future Sight:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 86%; Center Tutor (before Gym 7).*
- **Add — Extrasensory:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 19%; no Center/Tech Tutor overlap.*
- **Earlier power — Future Sight around Lv. 58:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Gumshoos

**Type:** Normal · **Final tier weight:** 2
**Role profile:** Atk 110 / Sp. Atk 55 / Spe 45 · Stakeout, Strong Jaw, Adaptability
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Last Resort:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 45%; Center Tutor (before Gym 7).*
- **Add — Ice Fang:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 6%; Center Tutor (before Gym 4).*
- **Earlier power — Last Resort around Lv. 54:** 140 BP; STAB. Treat this as the curve target, not a fixed slot.

### Guzzlord

**Type:** Dark/Dragon · **Final tier weight:** 3
**Role profile:** Atk 101 / Sp. Atk 97 / Spe 43 · Beast Boost
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Steamroller:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Brutal Swing:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 27%; Center Tutor (before Gym 3).*
- **Earlier power — Steamroller around Lv. 31:** 65 BP; coverage. Treat this as the curve target, not a fixed slot.

### Gyarados

**Type:** Water/Flying · **Final tier weight:** 4
**Role profile:** Atk 125 / Sp. Atk 60 / Spe 81 · Intimidate, Moxie
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Dragon Rush:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power — Dragon Rush around Lv. 56:** 100 BP; coverage. Treat this as the curve target, not a fixed slot.

### Hariyama

**Type:** Fighting · **Final tier weight:** 3
**Role profile:** Atk 120 / Sp. Atk 40 / Spe 50 · Thick Fat, Guts, Sheer Force
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Wake Up Slap:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 11%; no Center/Tech Tutor overlap.*
- **Add — Chip Away:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 7%; no Center/Tech Tutor overlap.*
- **Earlier power — Wake Up Slap around Lv. 36:** 70 BP; STAB. Treat this as the curve target, not a fixed slot.

### Hatterene

**Type:** Psychic/Fairy · **Final tier weight:** 4
**Role profile:** Atk 90 / Sp. Atk 136 / Spe 29 · Healer, Anticipation, Magic Bounce
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Mystical Fire:** Its supernatural or elegant fire identity makes the move feel native rather than generic coverage. *Precedent: egg/TM; type-cohort prevalence 19%; Center Tutor (before Gym 6).*
- **Earlier power — Mystical Fire around Lv. 40:** 75 BP; coverage. Treat this as the curve target, not a fixed slot.

### Hawlucha

**Type:** Fighting/Flying · **Final tier weight:** 5
**Role profile:** Atk 92 / Sp. Atk 74 / Spe 118 · Limber, Unburden, Mold Breaker
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Haxorus

**Type:** Dragon · **Final tier weight:** 4
**Role profile:** Atk 147 / Sp. Atk 60 / Spe 97 · Rivalry, Mold Breaker, Unnerve
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — First Impression:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power — First Impression around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Heatmor

**Type:** Fire · **Final tier weight:** 2
**Role profile:** Atk 97 / Sp. Atk 105 / Spe 65 · Gluttony, Flash Fire, White Smoke
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Night Slash:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Add — Heat Wave:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg/TM/tutor; type-cohort prevalence 94%; Center Tutor (before Gym 8).*
- **Earlier power — Heat Wave around Lv. 54:** 95 BP; STAB. Treat this as the curve target, not a fixed slot.

### Heatran

**Type:** Fire/Steel · **Final tier weight:** 5
**Role profile:** Atk 90 / Sp. Atk 130 / Spe 77 · Flash Fire, Flame Body
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Heliolisk

**Type:** Electric/Normal · **Final tier weight:** 3
**Role profile:** Atk 55 / Sp. Atk 109 / Spe 109 · Dry Skin, Sand Veil, Solar Power
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Electric Terrain:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/TM; type-cohort prevalence 3%; no Center/Tech Tutor overlap.*
- **Add — Morning Sun:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/TM; type-cohort prevalence 2%; Legacy Tutor.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Heracross

**Type:** Bug/Fighting · **Final tier weight:** 4
**Role profile:** Atk 125 / Sp. Atk 40 / Spe 85 · Swarm, Guts, Moxie
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Night Slash:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/egg/TM; type-cohort prevalence 15%; no Center/Tech Tutor overlap.*
- **Earlier power — Night Slash around Lv. 34:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Hippowdon

**Type:** Ground · **Final tier weight:** 4
**Role profile:** Atk 112 / Sp. Atk 68 / Spe 47 · Sand Stream, Sand Force
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Revenge:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 14%; Center Tutor (before Gym 6).*
- **Earlier power — Revenge around Lv. 24:** 60 BP; coverage. Treat this as the curve target, not a fixed slot.

### Hitmonchan

**Type:** Fighting · **Final tier weight:** 3
**Role profile:** Atk 105 / Sp. Atk 35 / Spe 76 · Keen Eye, Iron Fist, Inner Focus
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — High Jump Kick:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 13%; no Center/Tech Tutor overlap.*
- **Add — Dizzy Punch:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power — High Jump Kick around Lv. 58:** 130 BP; STAB. Treat this as the curve target, not a fixed slot.

### Hitmonlee

**Type:** Fighting · **Final tier weight:** 3
**Role profile:** Atk 120 / Sp. Atk 35 / Spe 87 · Limber, Reckless, Unburden
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Mind Reader:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 13%; no Center/Tech Tutor overlap.*
- **Add — Hi Jump Kick:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 18%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Hitmontop

**Type:** Fighting · **Final tier weight:** 3
**Role profile:** Atk 95 / Sp. Atk 35 / Spe 70 · Intimidate, Technician, Steadfast
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — High Jump Kick:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 13%; no Center/Tech Tutor overlap.*
- **Add — Ally Switch:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 11%; Center Tutor (before Gym 6).*
- **Earlier power — High Jump Kick around Lv. 58:** 130 BP; STAB. Treat this as the curve target, not a fixed slot.

### Ho-Oh

**Type:** Fire/Flying · **Final tier weight:** 3
**Role profile:** Atk 130 / Sp. Atk 110 / Spe 90 · Pressure, Regenerator
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Brave Bird:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 9%; Center Tutor (League).*
- **Add — Burn Up:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 3%; no Center/Tech Tutor overlap.*
- **Earlier power — Burn Up around Lv. 58:** 130 BP; STAB. Treat this as the curve target, not a fixed slot.

### Honchkrow

**Type:** Dark/Flying · **Final tier weight:** 2
**Role profile:** Atk 125 / Sp. Atk 105 / Spe 71 · Insomnia, Super Luck, Moxie
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Brave Bird:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 8%; Center Tutor (League).*
- **Add — Assurance:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/pre-evolution; type-cohort prevalence 29%; Tech Tutor (8 badges).*
- **Earlier power — Brave Bird around Lv. 54:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Hoopa (Confined)

**Type:** Psychic/Ghost · **Final tier weight:** 4
**Role profile:** Atk 110 / Sp. Atk 150 / Spe 70 · Magician
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Psychic Terrain:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Hoopa (Unbound)

**Type:** Psychic/Dark · **Final tier weight:** 4
**Role profile:** Atk 160 / Sp. Atk 170 / Spe 80 · Magician
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Psychic Terrain:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Houndoom

**Type:** Dark/Fire · **Final tier weight:** 3
**Role profile:** Atk 90 / Sp. Atk 110 / Spe 95 · Early Bird, Flash Fire, Unnerve
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Overheat:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 6%; Center Tutor (League).*
- **Add — Punishment:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Earlier power — Overheat around Lv. 58:** 130 BP; STAB. Treat this as the curve target, not a fixed slot.

### Houndstone

**Type:** Ghost · **Final tier weight:** 3
**Role profile:** Atk 101 / Sp. Atk 50 / Spe 68 · Sand Rush, Fluffy
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Psychic Fangs:** Its pronounced jaws or fangs give the unusual Psychic coverage a physical basis. *Precedent: TM; type-cohort prevalence 5%; Center Tutor (before Gym 7).*
- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 14%; Center Tutor (before Gym 7).*
- **Earlier power — Psychic Fangs around Lv. 48:** 85 BP; coverage. Treat this as the curve target, not a fixed slot.

### Huntail

**Type:** Water · **Final tier weight:** 2
**Role profile:** Atk 104 / Sp. Atk 94 / Spe 52 · Swift Swim, Water Veil
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Muddy Water:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 50%; Center Tutor (before Gym 8).*
- **Add — Body Slam:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 67%; Center Tutor (before Gym 6).*
- **Earlier power — Muddy Water around Lv. 54:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Hydrapple

**Type:** Grass/Dragon · **Final tier weight:** 5
**Role profile:** Atk 80 / Sp. Atk 120 / Spe 44 · Supersweet Syrup, Regenerator, Sticky Hold
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Hydreigon

**Type:** Dark/Dragon · **Final tier weight:** 4
**Role profile:** Atk 105 / Sp. Atk 125 / Spe 98 · Levitate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Belch:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power — Belch around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Hypno

**Type:** Psychic · **Final tier weight:** 2
**Role profile:** Atk 73 / Sp. Atk 73 / Spe 67 · Insomnia, Forewarn, Inner Focus
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Barrier:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 12%; Center Tutor (before Gym 6).*
- **Add — Psychic Terrain:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 71%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Illumise

**Type:** Bug · **Final tier weight:** 2
**Role profile:** Atk 47 / Sp. Atk 73 / Spe 85 · Oblivious, Tinted Lens, Prankster
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Silver Wind:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/TM; type-cohort prevalence 51%; no Center/Tech Tutor overlap.*
- **Add — Fake Tears:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/TM; type-cohort prevalence 4%; Tech Tutor (5 badges).*
- **Earlier power — Silver Wind around Lv. 22:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Incineroar

**Type:** Fire/Dark · **Final tier weight:** 4
**Role profile:** Atk 115 / Sp. Atk 80 / Spe 60 · Blaze, Intimidate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Crunch:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 32%; Center Tutor (before Gym 7).*
- **Earlier power — Crunch around Lv. 50:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Indeedee (F)

**Type:** Psychic/Normal · **Final tier weight:** 3
**Role profile:** Atk 55 / Sp. Atk 95 / Spe 85 · Own Tempo, Synchronize, Psychic Surge
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Mystical Fire:** Its supernatural or elegant fire identity makes the move feel native rather than generic coverage. *Precedent: TM; type-cohort prevalence 3%; Center Tutor (before Gym 6).*
- **Add — Hyper Voice:** Its voice, cry, song, or sound-based identity makes this natural level-up expression. *Precedent: TM; type-cohort prevalence 24%; no Center/Tech Tutor overlap.*
- **Earlier power — Hyper Voice around Lv. 58:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Indeedee (M)

**Type:** Psychic/Normal · **Final tier weight:** 3
**Role profile:** Atk 65 / Sp. Atk 105 / Spe 95 · Inner Focus, Synchronize, Psychic Surge
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Extrasensory:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 11%; no Center/Tech Tutor overlap.*
- **Add — Mystical Fire:** Its supernatural or elegant fire identity makes the move feel native rather than generic coverage. *Precedent: TM; type-cohort prevalence 3%; Center Tutor (before Gym 6).*
- **Earlier power — Extrasensory around Lv. 50:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Infernape

**Type:** Fire/Fighting · **Final tier weight:** 5
**Role profile:** Atk 104 / Sp. Atk 104 / Spe 108 · Blaze, Iron Fist
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Inteleon

**Type:** Water · **Final tier weight:** 4
**Role profile:** Atk 85 / Sp. Atk 125 / Spe 120 · Torrent, Sniper
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Weather Ball:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 37%; Center Tutor (before Gym 7).*
- **Earlier power — Weather Ball around Lv. 17:** 50 BP; coverage. Treat this as the curve target, not a fixed slot.

### Iron Boulder

**Type:** Rock/Psychic · **Final tier weight:** 3
**Role profile:** Atk 120 / Sp. Atk 68 / Spe 124 · Quark Drive
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Solar Blade:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: TM; type-cohort prevalence 4%; Center Tutor (before Gym 8).*
- **Add — Close Combat:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: TM; type-cohort prevalence 11%; Center Tutor (League).*
- **Earlier power — Solar Blade around Lv. 56:** 125 BP; coverage. Treat this as the curve target, not a fixed slot.

### Iron Bundle

**Type:** Ice/Water · **Final tier weight:** 3
**Role profile:** Atk 80 / Sp. Atk 124 / Spe 136 · Quark Drive
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Icy Wind:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 87%; no Center/Tech Tutor overlap.*
- **Add — Water Pulse:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 54%; Center Tutor (before Gym 4).*
- **Earlier power — Water Pulse around Lv. 26:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Iron Crown

**Type:** Steel/Psychic · **Final tier weight:** 3
**Role profile:** Atk 72 / Sp. Atk 122 / Spe 98 · Quark Drive
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Steel Beam:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 8%; Center Tutor (League).*
- **Add — Psychic Noise:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 8%; no Center/Tech Tutor overlap.*
- **Earlier power — Steel Beam around Lv. 58:** 140 BP; STAB. Treat this as the curve target, not a fixed slot.

### Iron Hands

**Type:** Fighting/Electric · **Final tier weight:** 3
**Role profile:** Atk 140 / Sp. Atk 50 / Spe 50 · Quark Drive
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 18%; Center Tutor (before Gym 7).*
- **Add — Supercell Slam:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Earlier power — Supercell Slam around Lv. 58:** 100 BP; STAB. Treat this as the curve target, not a fixed slot.

### Iron Jugulis

**Type:** Dark/Flying · **Final tier weight:** 3
**Role profile:** Atk 80 / Sp. Atk 122 / Spe 108 · Quark Drive
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Flash Cannon:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 6%; Center Tutor (before Gym 7).*
- **Add — Hurricane:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 15%; no Center/Tech Tutor overlap.*
- **Earlier power — Hurricane around Lv. 58:** 110 BP; STAB. Treat this as the curve target, not a fixed slot.

### Iron Leaves

**Type:** Grass/Psychic · **Final tier weight:** 3
**Role profile:** Atk 130 / Sp. Atk 70 / Spe 104 · Quark Drive
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Trailblaze:** Its terrestrial movement and plant association support an active Grass attack rather than generic TM access. *Precedent: TM; type-cohort prevalence 21%; Center Tutor (before Gym 3).*
- **Add — Wild Charge:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 5%; Center Tutor (before Gym 8).*
- **Earlier power — Wild Charge around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Iron Moth

**Type:** Fire/Poison · **Final tier weight:** 3
**Role profile:** Atk 70 / Sp. Atk 140 / Spe 110 · Quark Drive
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Dazzling Gleam:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 6%; Center Tutor (before Gym 7).*
- **Add — Heat Wave:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 15%; Center Tutor (before Gym 8).*
- **Earlier power — Heat Wave around Lv. 58:** 95 BP; STAB. Treat this as the curve target, not a fixed slot.

### Iron Thorns

**Type:** Rock/Electric · **Final tier weight:** 3
**Role profile:** Atk 134 / Sp. Atk 70 / Spe 72 · Quark Drive
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 18%; Center Tutor (before Gym 7).*
- **Add — Smack Down:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 4%; Center Tutor (before Gym 2).*
- **Earlier power — Body Press around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Iron Treads

**Type:** Ground/Steel · **Final tier weight:** 3
**Role profile:** Atk 112 / Sp. Atk 72 / Spe 106 · Quark Drive
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 46%; Center Tutor (before Gym 7).*
- **Add — Smart Strike:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 14%; Center Tutor (before Gym 5).*
- **Earlier power — Body Press around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Iron Valiant

**Type:** Fairy/Fighting · **Final tier weight:** 3
**Role profile:** Atk 130 / Sp. Atk 120 / Spe 116 · Quark Drive
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Hyper Voice:** Its voice, cry, song, or sound-based identity makes this natural level-up expression. *Precedent: TM; type-cohort prevalence 7%; no Center/Tech Tutor overlap.*
- **Add — Psychic Terrain:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Earlier power — Hyper Voice around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Jellicent

**Type:** Water/Ghost · **Final tier weight:** 3
**Role profile:** Atk 60 / Sp. Atk 85 / Spe 60 · Water Absorb, Cursed Body, Damp
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Bubble Beam:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 3%; no Center/Tech Tutor overlap.*
- **Add — Strength Sap:** Its draining or parasitic flavor supports a distinctive utility niche. *Precedent: egg; type-cohort prevalence 1%; no Center/Tech Tutor overlap.*
- **Earlier power — Bubble Beam around Lv. 33:** 65 BP; STAB. Treat this as the curve target, not a fixed slot.

### Jirachi

**Type:** Steel/Psychic · **Final tier weight:** 4
**Role profile:** Atk 100 / Sp. Atk 100 / Spe 100 · Serene Grace
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Steel Beam:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: TM/tutor; type-cohort prevalence 8%; Center Tutor (League).*
- **Earlier power — Steel Beam around Lv. 58:** 140 BP; STAB. Treat this as the curve target, not a fixed slot.

### Jolteon

**Type:** Electric · **Final tier weight:** 3
**Role profile:** Atk 65 / Sp. Atk 110 / Spe 130 · Volt Absorb, Volt Absorb, Quick Feet
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Synchronoise:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; Tech Tutor (5 badges).*
- **Add — Yawn:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power — Synchronoise around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Jumpluff

**Type:** Grass/Flying · **Final tier weight:** 4
**Role profile:** Atk 55 / Sp. Atk 55 / Spe 110 · Chlorophyll, Leaf Guard, Infiltrator
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Rage Powder:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg; type-cohort prevalence 3%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Jynx

**Type:** Ice/Psychic · **Final tier weight:** 3
**Role profile:** Atk 50 / Sp. Atk 115 / Spe 95 · Oblivious, Forewarn, Dry Skin
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Alluring Voice:** Its singing, humanoid presentation and 115 Sp. Atk make this an identity attack. *Precedent: deliberate design exception; type-cohort prevalence 8%; no Center/Tech Tutor overlap.*
- **Add — Frost Breath:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 6%; Center Tutor (before Gym 8).*
- **Earlier power — Alluring Voice around Lv. 34:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Kabutops

**Type:** Rock/Water · **Final tier weight:** 3
**Role profile:** Atk 115 / Sp. Atk 65 / Spe 80 · Swift Swim, Battle Armor, Weak Armor
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Rock Throw:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Add — Rapid Spin:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 7%; Center Tutor (before Gym 5).*
- **Earlier power — Rock Throw around Lv. 19:** 50 BP; STAB. Treat this as the curve target, not a fixed slot.

### Kangaskhan

**Type:** Normal · **Final tier weight:** 3
**Role profile:** Atk 95 / Sp. Atk 40 / Spe 90 · Early Bird, Scrappy, Inner Focus
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Crush Claw:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Add — Chip Away:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Earlier power — Crush Claw around Lv. 42:** 75 BP; STAB. Treat this as the curve target, not a fixed slot.

### Kartana

**Type:** Grass/Steel · **Final tier weight:** 3
**Role profile:** Atk 181 / Sp. Atk 59 / Spe 109 · Beast Boost
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — X Scissor:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 15%; Center Tutor (before Gym 7).*
- **Add — Psycho Cut:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 8%; Center Tutor (before Gym 5).*
- **Earlier power — X Scissor around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Kecleon

**Type:** Normal · **Final tier weight:** 3
**Role profile:** Atk 90 / Sp. Atk 60 / Spe 40 · Color Change, Protean
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Terrain Pulse:** Color Change and Protean make terrain-responsive offense part of its core identity. *Precedent: deliberate design exception; type-cohort prevalence 14%; Center Tutor (before Gym 7).*
- **Add — Recover:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 3%; no Center/Tech Tutor overlap.*
- **Earlier power — Terrain Pulse around Lv. 34:** 50 BP; STAB. Treat this as the curve target, not a fixed slot.

### Kilowattrel

**Type:** Electric/Flying · **Final tier weight:** 3
**Role profile:** Atk 70 / Sp. Atk 105 / Spe 125 · Wind Power, Volt Absorb, Competitive
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Weather Ball:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/TM; type-cohort prevalence 18%; Center Tutor (before Gym 7).*
- **Add — Feather Dance:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/TM; type-cohort prevalence 2%; Tech Tutor (5 badges).*
- **Earlier power — Weather Ball around Lv. 17:** 50 BP; coverage. Treat this as the curve target, not a fixed slot.

### Kingambit

**Type:** Dark/Steel · **Final tier weight:** 5
**Role profile:** Atk 135 / Sp. Atk 60 / Spe 50 · Defiant, Supreme Overlord, Pressure
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Sucker Punch:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 10%; Legacy Tutor.*
- **Earlier power — Sucker Punch around Lv. 39:** 70 BP; STAB. Treat this as the curve target, not a fixed slot.

### Kingdra

**Type:** Water/Dragon · **Final tier weight:** 4
**Role profile:** Atk 95 / Sp. Atk 95 / Spe 85 · Swift Swim, Sniper, Damp
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Clear Smog:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Clear Smog around Lv. 17:** 50 BP; coverage. Treat this as the curve target, not a fixed slot.

### Kingler

**Type:** Water · **Final tier weight:** 3
**Role profile:** Atk 130 / Sp. Atk 50 / Spe 75 · Hyper Cutter, Shell Armor, Sheer Force
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Chip Away:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Add — Slash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 16%; no Center/Tech Tutor overlap.*
- **Earlier power — Slash around Lv. 34:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Klawf

**Type:** Rock · **Final tier weight:** 3
**Role profile:** Atk 100 / Sp. Atk 35 / Spe 75 · Anger Shell, Shell Armor, Regenerator
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Crabhammer:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Trailblaze:** Its terrestrial movement and plant association support an active Grass attack rather than generic TM access. *Precedent: TM; type-cohort prevalence 17%; Center Tutor (before Gym 3).*
- **Earlier power — Crabhammer around Lv. 56:** 100 BP; coverage. Treat this as the curve target, not a fixed slot.

### Kleavor

**Type:** Bug/Rock · **Final tier weight:** 4
**Role profile:** Atk 135 / Sp. Atk 45 / Spe 85 · Swarm, Sheer Force, Sharpness
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Lunge:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/TM; type-cohort prevalence 2%; Center Tutor (before Gym 7).*
- **Earlier power — Lunge around Lv. 50:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Klefki

**Type:** Steel/Fairy · **Final tier weight:** 4
**Role profile:** Atk 80 / Sp. Atk 80 / Spe 75 · Prankster, Magician
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Mirror Shot:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Earlier power — Mirror Shot around Lv. 33:** 65 BP; STAB. Treat this as the curve target, not a fixed slot.

### Klinklang

**Type:** Steel · **Final tier weight:** 3
**Role profile:** Atk 100 / Sp. Atk 70 / Spe 90 · Plus, Minus, Clear Body
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Steel Roller:** Interlocking gears provide the rolling machinery while low Speed limits terrain removal offense. *Precedent: tutor; type-cohort prevalence 35%; Tech Tutor (6 badges).*
- **Add — Mirror Shot:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 15%; no Center/Tech Tutor overlap.*
- **Earlier power — Steel Roller around Lv. 42:** 130 BP; STAB. Treat this as the curve target, not a fixed slot.

### Komala

**Type:** Normal · **Final tier weight:** 3
**Role profile:** Atk 115 / Sp. Atk 75 / Spe 65 · Comatose
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Superpower:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 17%; Center Tutor (League).*
- **Add — Play Rough:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 27%; Center Tutor (before Gym 8).*
- **Earlier power — Superpower around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Kommo-o

**Type:** Dragon/Fighting · **Final tier weight:** 4
**Role profile:** Atk 110 / Sp. Atk 100 / Spe 85 · Bulletproof, Soundproof, Overcoat
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Dragon Breath:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Dragon Breath around Lv. 26:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Koraidon

**Type:** Fighting/Dragon · **Final tier weight:** 3
**Role profile:** Atk 135 / Sp. Atk 85 / Spe 135 · Orichalcum Pulse
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 36%; Center Tutor (before Gym 7).*
- **Add — Dragon Tail:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 5%; Tech Tutor (7 badges).*
- **Earlier power — Body Press around Lv. 50:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Kricketune

**Type:** Bug · **Final tier weight:** 1
**Role profile:** Atk 85 / Sp. Atk 55 / Spe 65 · Swarm, Technician
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Pounce:** A low-tier terrestrial insect can use the Speed-drop bridge without threatening sweeps. *Precedent: TM; type-cohort prevalence 47%; Center Tutor (before Gym 2).*
- **Add — Leech Life:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM/tutor; type-cohort prevalence 51%; Center Tutor (before Gym 7).*
- **Add — Heal Bell:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: tutor; type-cohort prevalence 4%; Center Tutor (before Gym 5).*
- **Earlier power — Leech Life around Lv. 43:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Krookodile

**Type:** Ground/Dark · **Final tier weight:** 4
**Role profile:** Atk 117 / Sp. Atk 65 / Spe 92 · Intimidate, Moxie, Anger Point
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Double Edge:** Its jaw-based anatomy gives the coverage a concrete physical source. *Precedent: level-up/egg/TM; type-cohort prevalence 54%; no Center/Tech Tutor overlap.*
- **Earlier power — Double Edge around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Kyogre

**Type:** Water · **Final tier weight:** 3
**Role profile:** Atk 100 / Sp. Atk 150 / Spe 90 · Drizzle
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Surf:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 94%; no Center/Tech Tutor overlap.*
- **Add — Brine:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 60%; Center Tutor (before Gym 5).*
- **Earlier power — Surf around Lv. 58:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Kyurem

**Type:** Dragon/Ice · **Final tier weight:** 3
**Role profile:** Atk 130 / Sp. Atk 130 / Spe 95 · Pressure
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Icy Wind:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM/tutor; type-cohort prevalence 26%; no Center/Tech Tutor overlap.*
- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 43%; Center Tutor (before Gym 7).*
- **Earlier power — Body Press around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Kyurem (Black)

**Type:** Dragon/Ice · **Final tier weight:** 3
**Role profile:** Atk 170 / Sp. Atk 120 / Spe 95 · Teravolt
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 43%; Center Tutor (before Gym 7).*
- **Add — Dragon Tail:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 14%; Tech Tutor (7 badges).*
- **Earlier power — Body Press around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Kyurem (White)

**Type:** Dragon/Ice · **Final tier weight:** 3
**Role profile:** Atk 120 / Sp. Atk 170 / Spe 95 · Turboblaze
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Icy Wind:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM/tutor; type-cohort prevalence 26%; no Center/Tech Tutor overlap.*
- **Add — Draco Meteor:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM/tutor; type-cohort prevalence 11%; Center Tutor (League).*
- **Earlier power — Draco Meteor around Lv. 58:** 130 BP; STAB. Treat this as the curve target, not a fixed slot.

### Lanturn

**Type:** Water/Electric · **Final tier weight:** 3
**Role profile:** Atk 58 / Sp. Atk 76 / Spe 67 · Volt Absorb, Illuminate, Water Absorb
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Brine:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 4%; Center Tutor (before Gym 5).*
- **Add — Water Pulse:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 6%; Center Tutor (before Gym 4).*
- **Earlier power — Brine around Lv. 33:** 65 BP; STAB. Treat this as the curve target, not a fixed slot.

### Lapras

**Type:** Water/Ice · **Final tier weight:** 4
**Role profile:** Atk 85 / Sp. Atk 85 / Spe 60 · Water Absorb, Shell Armor, Hydration
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Dragon Pulse:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 13%; Center Tutor (before Gym 7).*
- **Earlier power — Dragon Pulse around Lv. 48:** 85 BP; coverage. Treat this as the curve target, not a fixed slot.

### Latias

**Type:** Dragon/Psychic · **Final tier weight:** 5
**Role profile:** Atk 80 / Sp. Atk 110 / Spe 110 · Levitate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Mystical Fire:** Its supernatural or elegant fire identity makes the move feel native rather than generic coverage. *Precedent: level-up/TM; type-cohort prevalence 9%; Center Tutor (before Gym 6).*
- **Earlier power — Mystical Fire around Lv. 43:** 75 BP; coverage. Treat this as the curve target, not a fixed slot.

### Latios

**Type:** Dragon/Psychic · **Final tier weight:** 5
**Role profile:** Atk 90 / Sp. Atk 130 / Spe 110 · Levitate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Mystical Fire:** Its supernatural or elegant fire identity makes the move feel native rather than generic coverage. *Precedent: level-up/TM; type-cohort prevalence 9%; Center Tutor (before Gym 6).*
- **Earlier power — Mystical Fire around Lv. 43:** 75 BP; coverage. Treat this as the curve target, not a fixed slot.

### Leafeon

**Type:** Grass · **Final tier weight:** 2
**Role profile:** Atk 110 / Sp. Atk 60 / Spe 95 · Leaf Guard, Leaf Guard, Chlorophyll
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Grassy Glide:** A low-final-tier physical Grass attacker is a fair natural owner outside Rillaboom. *Precedent: TM/tutor; type-cohort prevalence 71%; Center Tutor (before Gym 6).*
- **Add — Wish:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 2%; Legacy Tutor.*
- **Earlier power — Grassy Glide around Lv. 38:** 55 BP; STAB. Treat this as the curve target, not a fixed slot.

### Leavanny

**Type:** Bug/Grass · **Final tier weight:** 2
**Role profile:** Atk 103 / Sp. Atk 70 / Spe 92 · Swarm, Chlorophyll, Overcoat
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Silver Wind:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 9%; no Center/Tech Tutor overlap.*
- **Add — Lunge:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 8%; Center Tutor (before Gym 7).*
- **Earlier power — Lunge around Lv. 46:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Ledian

**Type:** Bug/Flying · **Final tier weight:** 1
**Role profile:** Atk 35 / Sp. Atk 55 / Spe 85 · Swarm, Rattled, Astral Charge
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Coaching:** Its team-oriented hero motif and very low tier favor doubles support over personal setup. *Precedent: deliberate design exception; type-cohort prevalence 3%; Center Tutor (before Gym 5).*
- **Add — Silver Wind:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg/TM; type-cohort prevalence 22%; no Center/Tech Tutor overlap.*
- **Add — Bug Bite:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/tutor; type-cohort prevalence 12%; Center Tutor (before Gym 3).*
- **Earlier power — Silver Wind around Lv. 19:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Lickilicky

**Type:** Normal · **Final tier weight:** 3
**Role profile:** Atk 85 / Sp. Atk 80 / Spe 50 · Own Tempo, Oblivious, Cloud Nine
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Zen Headbutt:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 47%; Center Tutor (before Gym 7).*
- **Add — Smelling Salts:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Earlier power — Zen Headbutt around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Liepard

**Type:** Dark · **Final tier weight:** 2
**Role profile:** Atk 88 / Sp. Atk 88 / Spe 106 · Limber, Unburden, Prankster
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Knock Off:** A fast trickster gains role expression without receiving setup. *Precedent: TM/tutor; type-cohort prevalence 69%; Center Tutor (League).*
- **Add — Slash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 25%; no Center/Tech Tutor overlap.*
- **Earlier power — Slash around Lv. 30:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Lilligant

**Type:** Grass · **Final tier weight:** 3
**Role profile:** Atk 60 / Sp. Atk 110 / Spe 90 · Chlorophyll, Own Tempo, Leaf Guard
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Pollen Puff:** Its flower, pollen, or caregiving identity supports both the attack and ally-heal flavor. *Precedent: TM; type-cohort prevalence 26%; Center Tutor (before Gym 8).*
- **Add — Healing Wish:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 8%; no Center/Tech Tutor overlap.*
- **Earlier power — Pollen Puff around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Lilligant (Hisui)

**Type:** Grass/Fighting · **Final tier weight:** 3
**Role profile:** Atk 105 / Sp. Atk 50 / Spe 105 · Chlorophyll, Hustle, Leaf Guard
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Close Combat:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 14%; Center Tutor (League).*
- **Add — Recover:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power — Close Combat around Lv. 58:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Linoone

**Type:** Normal · **Final tier weight:** 1
**Role profile:** Atk 75 / Sp. Atk 50 / Spe 100 · Pickup, Gluttony, Quick Feet
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Extreme Speed:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Rock Climb:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 19%; Center Tutor (before Gym 7).*
- **Add — Play Rough:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 27%; Center Tutor (before Gym 8).*
- **Earlier power — Rock Climb around Lv. 51:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Lokix

**Type:** Bug/Dark · **Final tier weight:** 4
**Role profile:** Atk 102 / Sp. Atk 52 / Spe 92 · Swarm, Tinted Lens
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Leech Life:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 8%; Center Tutor (before Gym 7).*
- **Earlier power — Leech Life around Lv. 50:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Lopunny

**Type:** Normal · **Final tier weight:** 2
**Role profile:** Atk 76 / Sp. Atk 54 / Spe 105 · Cute Charm, Klutz, Limber
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Sky Uppercut:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Circle Throw:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 6%; Tech Tutor (7 badges).*
- **Earlier power — Sky Uppercut around Lv. 44:** 85 BP; coverage. Treat this as the curve target, not a fixed slot.

### Lucario

**Type:** Fighting/Steel · **Final tier weight:** 4
**Role profile:** Atk 110 / Sp. Atk 115 / Spe 90 · Steadfast, Inner Focus, Justified
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Bite:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 7%; no Center/Tech Tutor overlap.*
- **Earlier power — Bite around Lv. 24:** 60 BP; coverage. Treat this as the curve target, not a fixed slot.

### Ludicolo

**Type:** Water/Grass · **Final tier weight:** 3
**Role profile:** Atk 70 / Sp. Atk 90 / Spe 70 · Swift Swim, Rain Dish, Own Tempo
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Giga Drain:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/pre-evolution/TM/tutor; type-cohort prevalence 6%; Center Tutor (before Gym 6).*
- **Add — Razor Leaf:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 1%; no Center/Tech Tutor overlap.*
- **Earlier power — Giga Drain around Lv. 42:** 75 BP; STAB. Treat this as the curve target, not a fixed slot.

### Lugia

**Type:** Psychic/Flying · **Final tier weight:** 3
**Role profile:** Atk 90 / Sp. Atk 90 / Spe 110 · Pressure, Multiscale
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Punishment:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up; type-cohort prevalence 1%; no Center/Tech Tutor overlap.*
- **Add — Brine:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: TM; type-cohort prevalence 8%; Center Tutor (before Gym 5).*
- **Earlier power — Brine around Lv. 31:** 65 BP; coverage. Treat this as the curve target, not a fixed slot.

### Lumineon

**Type:** Water · **Final tier weight:** 1
**Role profile:** Atk 69 / Sp. Atk 69 / Spe 91 · Swift Swim, Storm Drain, Water Veil
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Flip Turn:** Its graceful swimming identity supports a utility pivot niche. *Precedent: TM; type-cohort prevalence 44%; Center Tutor (League).*
- **Add — Brine:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/TM; type-cohort prevalence 60%; Center Tutor (before Gym 5).*
- **Add — Aqua Tail:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/tutor; type-cohort prevalence 44%; Center Tutor (before Gym 8).*
- **Earlier power — Aqua Tail around Lv. 51:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Lunala

**Type:** Psychic/Ghost · **Final tier weight:** 3
**Role profile:** Atk 113 / Sp. Atk 137 / Spe 97 · Shadow Shield
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Hyper Beam:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/TM; type-cohort prevalence 95%; Tech Tutor (6 badges).*
- **Add — Future Sight:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: TM; type-cohort prevalence 14%; Center Tutor (before Gym 7).*
- **Earlier power — Hyper Beam around Lv. 56:** 150 BP; coverage. Treat this as the curve target, not a fixed slot.

### Lunatone

**Type:** Rock/Psychic · **Final tier weight:** 2
**Role profile:** Atk 55 / Sp. Atk 95 / Spe 70 · Levitate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Meteor Beam:** The lunar meteor body and 95 Sp. Atk make the charged Rock attack functional. *Precedent: tutor; type-cohort prevalence 22%; Center Tutor (before Gym 7).*
- **Add — Power Gem:** Its mineral, jewel, light, or crystalline anatomy gives the attack a visible source. *Precedent: level-up/TM; type-cohort prevalence 16%; Center Tutor (before Gym 7).*
- **Earlier power — Meteor Beam around Lv. 44:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Lurantis

**Type:** Grass · **Final tier weight:** 2
**Role profile:** Atk 105 / Sp. Atk 80 / Spe 45 · Leaf Guard, Contrary
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Superpower:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 20%; Center Tutor (League).*
- **Add — Weather Ball:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 29%; Center Tutor (before Gym 7).*
- **Earlier power — Superpower around Lv. 52:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Luvdisc

**Type:** Water · **Final tier weight:** 1
**Role profile:** Atk 30 / Sp. Atk 40 / Spe 107 · Swift Swim, Dedicated, Hydration
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Flip Turn:** A low-tier fish gains useful momentum without gaining raw sweeping power. *Precedent: TM; type-cohort prevalence 44%; Center Tutor (League).*
- **Add — Brine:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 60%; Center Tutor (before Gym 5).*
- **Add — Heal Pulse:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 7%; costless Tech Tutor (always).*
- **Earlier power — Brine around Lv. 26:** 65 BP; STAB. Treat this as the curve target, not a fixed slot.

### Luxray

**Type:** Electric · **Final tier weight:** 3
**Role profile:** Atk 120 / Sp. Atk 95 / Spe 70 · Rivalry, Intimidate, Guts
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Thunder Fang:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 30%; Center Tutor (before Gym 4).*
- **Add — Night Slash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Night Slash around Lv. 34:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Lycanroc (Dusk)

**Type:** Rock · **Final tier weight:** 3
**Role profile:** Atk 117 / Sp. Atk 55 / Spe 110 · Tough Claws
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Thrash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 17%; no Center/Tech Tutor overlap.*
- **Add — Last Resort:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 9%; Center Tutor (before Gym 7).*
- **Earlier power — Last Resort around Lv. 56:** 140 BP; coverage. Treat this as the curve target, not a fixed slot.

### Lycanroc (Midday)

**Type:** Rock · **Final tier weight:** 3
**Role profile:** Atk 115 / Sp. Atk 55 / Spe 112 · Keen Eye, Sand Rush, Steadfast
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Last Resort:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg/tutor; type-cohort prevalence 9%; Center Tutor (before Gym 7).*
- **Add — Thrash:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg; type-cohort prevalence 17%; no Center/Tech Tutor overlap.*
- **Earlier power — Last Resort around Lv. 56:** 140 BP; coverage. Treat this as the curve target, not a fixed slot.

### Lycanroc (Midnight)

**Type:** Rock · **Final tier weight:** 3
**Role profile:** Atk 115 / Sp. Atk 55 / Spe 82 · Keen Eye, Vital Spirit, No Guard
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Sucker Punch:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg; type-cohort prevalence 13%; Legacy Tutor.*
- **Add — Last Resort:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg/tutor; type-cohort prevalence 9%; Center Tutor (before Gym 7).*
- **Earlier power — Last Resort around Lv. 56:** 140 BP; coverage. Treat this as the curve target, not a fixed slot.

### Mabosstiff

**Type:** Dark · **Final tier weight:** 3
**Role profile:** Atk 120 / Sp. Atk 60 / Spe 85 · Intimidate, Guard Dog, Stakeout
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Lash Out:** Its protective, retaliatory temperament makes Lash Out an identity attack. *Precedent: TM; type-cohort prevalence 92%; Tech Tutor (8 badges).*
- **Add — Lunge:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 8%; Center Tutor (before Gym 7).*
- **Earlier power — Lunge around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Machamp

**Type:** Fighting · **Final tier weight:** 3
**Role profile:** Atk 130 / Sp. Atk 65 / Spe 55 · Guts, No Guard, Steadfast
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Submission:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 13%; Legacy Tutor.*
- **Add — Close Combat:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 100%; Center Tutor (League).*
- **Earlier power — Close Combat around Lv. 58:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Magcargo

**Type:** Fire/Rock · **Final tier weight:** 1
**Role profile:** Atk 50 / Sp. Atk 90 / Spe 30 · Magma Armor, Flame Body, Weak Armor
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Inferno:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Heat Wave:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg/TM/tutor; type-cohort prevalence 13%; Center Tutor (before Gym 8).*
- **Add — Flame Burst:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Inferno around Lv. 51:** 100 BP; STAB. Treat this as the curve target, not a fixed slot.

### Magearna

**Type:** Steel/Fairy · **Final tier weight:** 6
**Role profile:** Atk 95 / Sp. Atk 130 / Spe 65 · Soul Heart
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Disarming Voice:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 6%; Tech Tutor (7 badges).*
- **Earlier power — Disarming Voice around Lv. 29:** 55 BP; STAB. Treat this as the curve target, not a fixed slot.

### Magmortar

**Type:** Fire · **Final tier weight:** 3
**Role profile:** Atk 95 / Sp. Atk 125 / Spe 83 · Flame Body, Vital Spirit
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Belch:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 11%; no Center/Tech Tutor overlap.*
- **Add — Flame Burst:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 32%; no Center/Tech Tutor overlap.*
- **Earlier power — Belch around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Magnezone

**Type:** Electric/Steel · **Final tier weight:** 4
**Role profile:** Atk 70 / Sp. Atk 130 / Spe 60 · Magnet Pull, Sturdy, Analytic
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Mirror Shot:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Mirror Shot around Lv. 33:** 65 BP; STAB. Treat this as the curve target, not a fixed slot.

### Malamar

**Type:** Dark/Psychic · **Final tier weight:** 2
**Role profile:** Atk 92 / Sp. Atk 68 / Spe 73 · Contrary, Suction Cups, Infiltrator
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Close Combat:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 11%; Center Tutor (League).*
- **Add — Psyshock:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 10%; Center Tutor (before Gym 7).*
- **Earlier power — Close Combat around Lv. 52:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Mamoswine

**Type:** Ice/Ground · **Final tier weight:** 4
**Role profile:** Atk 130 / Sp. Atk 70 / Spe 80 · Oblivious, Snow Cloak, Thick Fat
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Icicle Crash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Icicle Crash around Lv. 50:** 85 BP; STAB. Treat this as the curve target, not a fixed slot.

### Manaphy

**Type:** Water · **Final tier weight:** 5
**Role profile:** Atk 100 / Sp. Atk 100 / Spe 100 · Hydration
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Mandibuzz

**Type:** Dark/Flying · **Final tier weight:** 4
**Role profile:** Atk 65 / Sp. Atk 55 / Spe 80 · Big Pecks, Overcoat, Weak Armor
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Foul Play:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 14%; Center Tutor (before Gym 8).*
- **Earlier power — Foul Play around Lv. 58:** 95 BP; STAB. Treat this as the curve target, not a fixed slot.

### Manectric

**Type:** Electric · **Final tier weight:** 3
**Role profile:** Atk 75 / Sp. Atk 105 / Spe 105 · Static, Lightning Rod, Minus
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Spark:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 62%; no Center/Tech Tutor overlap.*
- **Add — Flame Burst:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Flame Burst around Lv. 34:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Mantine

**Type:** Water/Flying · **Final tier weight:** 3
**Role profile:** Atk 40 / Sp. Atk 80 / Spe 70 · Swift Swim, Water Absorb, Water Veil
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Signal Beam:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/tutor; type-cohort prevalence 26%; Center Tutor (before Gym 6).*
- **Add — Brine:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 8%; Center Tutor (before Gym 5).*
- **Earlier power — Signal Beam around Lv. 40:** 75 BP; coverage. Treat this as the curve target, not a fixed slot.

### Maractus

**Type:** Grass · **Final tier weight:** 2
**Role profile:** Atk 86 / Sp. Atk 106 / Spe 60 · Water Absorb, Chlorophyll, Storm Drain
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Scorching Sands:** Its Pokédex habitat explicitly names arid regions; 106 Sp. Atk makes the novel coverage matter. *Precedent: deliberate design exception; type-cohort prevalence 2%; Center Tutor (before Gym 6).*
- **Add — Hyper Voice:** Its Pokédex entry explicitly emphasizes maraca-like sound, and 106 Sp. Atk makes that identity useful. *Precedent: TM/tutor; type-cohort prevalence 14%; no Center/Tech Tutor overlap.*
- **Earlier power — Hyper Voice around Lv. 38:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Marowak

**Type:** Ground · **Final tier weight:** 4
**Role profile:** Atk 80 / Sp. Atk 50 / Spe 45 · Rock Head, Lightning Rod, Battle Armor
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Perish Song:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Marowak (Alola)

**Type:** Fire/Ghost · **Final tier weight:** 4
**Role profile:** Atk 80 / Sp. Atk 50 / Spe 45 · Cursed Body, Lightning Rod, Rock Head
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Chip Away:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Chip Away around Lv. 34:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Marshadow

**Type:** Fighting/Ghost · **Final tier weight:** 6
**Role profile:** Atk 125 / Sp. Atk 90 / Spe 125 · Technician
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Phantom Force:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 4%; Center Tutor (before Gym 8).*
- **Earlier power — Phantom Force around Lv. 61:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Masquerain

**Type:** Bug/Flying · **Final tier weight:** 2
**Role profile:** Atk 60 / Sp. Atk 100 / Spe 80 · Intimidate, Unnerve
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Hydro Pump:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/TM; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Add — Mud Shot:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/TM; type-cohort prevalence 3%; Center Tutor (before Gym 4).*
- **Earlier power — Hydro Pump around Lv. 52:** 110 BP; coverage. Treat this as the curve target, not a fixed slot.

### Mawile

**Type:** Steel/Fairy · **Final tier weight:** 2
**Role profile:** Atk 95 / Sp. Atk 55 / Spe 50 · Hyper Cutter, Intimidate, Sheer Force
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Misty Terrain:** Its jaw-based anatomy gives the coverage a concrete physical source. *Precedent: egg/TM; type-cohort prevalence 6%; Tech Tutor (3 badges).*
- **Add — Punishment:** Its jaw-based anatomy gives the coverage a concrete physical source. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Punishment around Lv. 20:** 60 BP; coverage. Treat this as the curve target, not a fixed slot.

### Medicham

**Type:** Fighting/Psychic · **Final tier weight:** 4
**Role profile:** Atk 60 / Sp. Atk 60 / Spe 80 · Pure Power, Telepathy
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Dynamic Punch:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 16%; Tech Tutor (5 badges).*
- **Earlier power — Dynamic Punch around Lv. 58:** 100 BP; STAB. Treat this as the curve target, not a fixed slot.

### Meganium

**Type:** Grass · **Final tier weight:** 3
**Role profile:** Atk 82 / Sp. Atk 83 / Spe 80 · Overgrow, Leaf Guard
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Grassy Terrain:** Bulky mono-Grass team support is its clearest ecosystem niche. *Precedent: egg/TM; type-cohort prevalence 83%; no Center/Tech Tutor overlap.*
- **Add — Leaf Storm:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 85%; Center Tutor (League).*
- **Earlier power — Leaf Storm around Lv. 58:** 130 BP; STAB. Treat this as the curve target, not a fixed slot.

### Melmetal

**Type:** Steel · **Final tier weight:** 6
**Role profile:** Atk 143 / Sp. Atk 80 / Spe 34 · Iron Fist
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Meltan

**Type:** Steel · **Final tier weight:** 3
**Role profile:** Atk 65 / Sp. Atk 55 / Spe 34 · Magnet Pull
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Brutal Swing:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/TM; type-cohort prevalence 29%; Center Tutor (before Gym 3).*
- **Add — Magnet Bomb:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: TM; type-cohort prevalence 25%; Tech Tutor (7 badges).*
- **Earlier power — Magnet Bomb around Lv. 26:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Meowscarada

**Type:** Grass/Dark · **Final tier weight:** 5
**Role profile:** Atk 110 / Sp. Atk 81 / Spe 123 · Overgrow, Protean
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Petal Blizzard:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Earlier power — Petal Blizzard around Lv. 61:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Meowstic (F)

**Type:** Psychic · **Final tier weight:** 3
**Role profile:** Atk 48 / Sp. Atk 83 / Spe 104 · Keen Eye, Infiltrator, Competitive
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Signal Beam:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/tutor; type-cohort prevalence 61%; Center Tutor (before Gym 6).*
- **Add — Assist:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; costless Tech Tutor (always).*
- **Earlier power — Signal Beam around Lv. 40:** 75 BP; coverage. Treat this as the curve target, not a fixed slot.

### Meowstic (M)

**Type:** Psychic · **Final tier weight:** 3
**Role profile:** Atk 48 / Sp. Atk 83 / Spe 104 · Keen Eye, Infiltrator, Prankster
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Assist:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; costless Tech Tutor (always).*
- **Add — Barrier:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 12%; Center Tutor (before Gym 6).*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Mesprit

**Type:** Psychic · **Final tier weight:** 3
**Role profile:** Atk 105 / Sp. Atk 105 / Spe 80 · Levitate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Recover:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 26%; no Center/Tech Tutor overlap.*
- **Add — Lucky Chant:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 14%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Metagross

**Type:** Steel/Psychic · **Final tier weight:** 4
**Role profile:** Atk 135 / Sp. Atk 95 / Spe 70 · Clear Body, Light Metal
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Iron Head:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM/tutor; type-cohort prevalence 15%; Center Tutor (before Gym 7).*
- **Earlier power — Iron Head around Lv. 50:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Mew

**Type:** Psychic · **Final tier weight:** 4
**Role profile:** Atk 100 / Sp. Atk 100 / Spe 100 · Synchronize
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Sludge Wave:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 6%; Center Tutor (before Gym 8).*
- **Earlier power — Sludge Wave around Lv. 56:** 95 BP; coverage. Treat this as the curve target, not a fixed slot.

### Mewtwo

**Type:** Psychic · **Final tier weight:** 3
**Role profile:** Atk 110 / Sp. Atk 154 / Spe 130 · Pressure, Unnerve
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Psybeam:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 76%; Center Tutor (before Gym 4).*
- **Add — Power Gem:** Its mineral, jewel, light, or crystalline anatomy gives the attack a visible source. *Precedent: TM; type-cohort prevalence 16%; Center Tutor (before Gym 7).*
- **Earlier power — Power Gem around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Mienshao

**Type:** Fighting · **Final tier weight:** 4
**Role profile:** Atk 125 / Sp. Atk 95 / Spe 105 · Inner Focus, Regenerator, Reckless
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Vital Throw:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 13%; Tech Tutor (7 badges).*
- **Earlier power — Vital Throw around Lv. 36:** 70 BP; STAB. Treat this as the curve target, not a fixed slot.

### Mightyena

**Type:** Dark · **Final tier weight:** 1
**Role profile:** Atk 90 / Sp. Atk 60 / Spe 80 · Intimidate, Quick Feet, Moxie
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Lash Out:** An intimidated pack hunter is a natural low-tier owner of retaliation-based Dark STAB. *Precedent: TM; type-cohort prevalence 92%; Tech Tutor (8 badges).*
- **Add — Poison Fang:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 8%; no Center/Tech Tutor overlap.*
- **Add — Covet:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 17%; Center Tutor (before Gym 3).*
- **Earlier power — Lash Out around Lv. 32:** 75 BP; STAB. Treat this as the curve target, not a fixed slot.

### Milotic

**Type:** Water · **Final tier weight:** 5
**Role profile:** Atk 60 / Sp. Atk 100 / Spe 81 · Marvel Scale, Competitive, Cute Charm
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Brine:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 60%; Center Tutor (before Gym 5).*
- **Earlier power — Brine around Lv. 36:** 65 BP; STAB. Treat this as the curve target, not a fixed slot.

### Miltank

**Type:** Normal · **Final tier weight:** 3
**Role profile:** Atk 80 / Sp. Atk 40 / Spe 100 · Thick Fat, Scrappy, Sap Sipper
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Dizzy Punch:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 9%; no Center/Tech Tutor overlap.*
- **Add — Punishment:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Earlier power — Dizzy Punch around Lv. 36:** 70 BP; STAB. Treat this as the curve target, not a fixed slot.

### Minun

**Type:** Electric · **Final tier weight:** 1
**Role profile:** Atk 40 / Sp. Atk 75 / Spe 95 · Minus, Dedicated, Volt Absorb
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Fake Tears:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 14%; Tech Tutor (5 badges).*
- **Add — Charm:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 24%; Tech Tutor (5 badges).*
- **Add — Sing:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Miraidon

**Type:** Electric/Dragon · **Final tier weight:** 3
**Role profile:** Atk 85 / Sp. Atk 135 / Spe 135 · Hadron Engine
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Power Gem:** Its mineral, jewel, light, or crystalline anatomy gives the attack a visible source. *Precedent: TM; type-cohort prevalence 8%; Center Tutor (before Gym 7).*
- **Add — Volt Switch:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 6%; Center Tutor (League).*
- **Earlier power — Power Gem around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Mismagius

**Type:** Ghost · **Final tier weight:** 4
**Role profile:** Atk 60 / Sp. Atk 105 / Spe 105 · Levitate
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Ominous Wind:** Its established sound motif makes this a strong identity move. *Precedent: egg/tutor; type-cohort prevalence 54%; Center Tutor (before Gym 3).*
- **Earlier power — Ominous Wind around Lv. 26:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Moltres

**Type:** Fire/Flying · **Final tier weight:** 4
**Role profile:** Atk 100 / Sp. Atk 125 / Spe 90 · Pressure, Flame Body
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Burn Up:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up; type-cohort prevalence 3%; no Center/Tech Tutor overlap.*
- **Earlier power — Burn Up around Lv. 58:** 130 BP; STAB. Treat this as the curve target, not a fixed slot.

### Moltres (Galar)

**Type:** Dark/Flying · **Final tier weight:** 4
**Role profile:** Atk 85 / Sp. Atk 100 / Spe 90 · Berserk
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Brave Bird:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 8%; Center Tutor (League).*
- **Earlier power — Brave Bird around Lv. 58:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Mr. Mime

**Type:** Psychic/Fairy · **Final tier weight:** 3
**Role profile:** Atk 45 / Sp. Atk 100 / Spe 90 · Soundproof, Filter, Technician
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Freeze Dry:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Future Sight:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 26%; Center Tutor (before Gym 7).*
- **Earlier power — Future Sight around Lv. 58:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Mr. Rime

**Type:** Ice/Psychic · **Final tier weight:** 3
**Role profile:** Atk 85 / Sp. Atk 110 / Spe 70 · Tangled Feet, Screen Cleaner, Ice Body
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Confuse Ray:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 16%; Center Tutor (before Gym 2).*
- **Add — Dream Eater:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 22%; Tech Tutor (5 badges).*
- **Earlier power — Dream Eater around Lv. 58:** 100 BP; STAB. Treat this as the curve target, not a fixed slot.

### Mudsdale

**Type:** Ground · **Final tier weight:** 4
**Role profile:** Atk 125 / Sp. Atk 55 / Spe 35 · Own Tempo, Stamina, Inner Focus
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Close Combat:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 14%; Center Tutor (League).*
- **Earlier power — Close Combat around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Muk

**Type:** Poison · **Final tier weight:** 3
**Role profile:** Atk 105 / Sp. Atk 65 / Spe 50 · Stench, Sticky Hold, Poison Touch
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Shadow Punch:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Add — Explosion:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 21%; Center Tutor (before Gym 8).*
- **Earlier power — Explosion around Lv. 56:** 250 BP; coverage. Treat this as the curve target, not a fixed slot.

### Muk (Alola)

**Type:** Poison/Dark · **Final tier weight:** 3
**Role profile:** Atk 105 / Sp. Atk 65 / Spe 50 · Poison Touch, Gluttony, Power Of Alchemy
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Assurance:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 29%; Tech Tutor (8 badges).*
- **Add — Recycle:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 4%; Center Tutor (before Gym 5).*
- **Earlier power — Assurance around Lv. 26:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Munkidori

**Type:** Poison/Psychic · **Final tier weight:** 4
**Role profile:** Atk 75 / Sp. Atk 130 / Spe 106 · Toxic Chain, Frisk
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Sludge Bomb:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 11%; no Center/Tech Tutor overlap.*
- **Earlier power — Sludge Bomb around Lv. 58:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Musharna

**Type:** Psychic · **Final tier weight:** 3
**Role profile:** Atk 55 / Sp. Atk 107 / Spe 29 · Forewarn, Synchronize, Telepathy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Expanding Force:** Its dream and field-control role supports slow Psychic Terrain offense. *Precedent: tutor; type-cohort prevalence 86%; no Center/Tech Tutor overlap.*
- **Add — Swift:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 79%; Tech Tutor (7 badges).*
- **Earlier power — Expanding Force around Lv. 38:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Naganadel

**Type:** Poison/Dragon · **Final tier weight:** 3
**Role profile:** Atk 73 / Sp. Atk 127 / Spe 121 · Beast Boost
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Sludge Wave:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 13%; Center Tutor (before Gym 8).*
- **Add — Sludge Bomb:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 17%; no Center/Tech Tutor overlap.*
- **Earlier power — Sludge Wave around Lv. 58:** 95 BP; STAB. Treat this as the curve target, not a fixed slot.

### Necrozma

**Type:** Psychic · **Final tier weight:** 4
**Role profile:** Atk 107 / Sp. Atk 127 / Spe 79 · Prism Armor
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Mirror Shot:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 1%; no Center/Tech Tutor overlap.*
- **Earlier power — Mirror Shot around Lv. 31:** 65 BP; coverage. Treat this as the curve target, not a fixed slot.

### Nidoking

**Type:** Poison/Ground · **Final tier weight:** 3
**Role profile:** Atk 102 / Sp. Atk 85 / Spe 85 · Poison Point, Rivalry, Sheer Force
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Thrash:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Chip Away:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power — Thrash around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Nidoqueen

**Type:** Poison/Ground · **Final tier weight:** 3
**Role profile:** Atk 92 / Sp. Atk 75 / Spe 76 · Poison Point, Rivalry, Sheer Force
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Chip Away:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Add — Poison Fang:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/pre-evolution; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Chip Away around Lv. 34:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Nihilego

**Type:** Rock/Poison · **Final tier weight:** 5
**Role profile:** Atk 53 / Sp. Atk 127 / Spe 103 · Beast Boost
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Ninetales

**Type:** Fire · **Final tier weight:** 6
**Role profile:** Atk 76 / Sp. Atk 81 / Spe 100 · Flash Fire, Drought
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Mystical Fire:** Its supernatural or elegant fire identity makes the move feel native rather than generic coverage. *Precedent: TM/tutor; type-cohort prevalence 34%; Center Tutor (before Gym 6).*
- **Earlier power — Mystical Fire around Lv. 45:** 75 BP; STAB. Treat this as the curve target, not a fixed slot.

### Ninetales (Alola)

**Type:** Ice/Fairy · **Final tier weight:** 3
**Role profile:** Atk 67 / Sp. Atk 81 / Spe 109 · Snow Cloak, Snow Warning
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Moonblast:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 3%; no Center/Tech Tutor overlap.*
- **Add — Hypnosis:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Earlier power — Moonblast around Lv. 58:** 95 BP; STAB. Treat this as the curve target, not a fixed slot.

### Ninjask

**Type:** Bug/Flying · **Final tier weight:** 3
**Role profile:** Atk 90 / Sp. Atk 50 / Spe 160 · Speed Boost, Infiltrator
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Night Slash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 12%; no Center/Tech Tutor overlap.*
- **Add — Dig:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/pre-evolution/TM; type-cohort prevalence 9%; Center Tutor (before Gym 7).*
- **Earlier power — Dig around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Noctowl

**Type:** Normal/Flying · **Final tier weight:** 2
**Role profile:** Atk 50 / Sp. Atk 86 / Spe 70 · Insomnia, Mystic, Tinted Lens
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Hurricane:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/TM; type-cohort prevalence 14%; no Center/Tech Tutor overlap.*
- **Add — Synchronoise:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up; type-cohort prevalence 6%; Tech Tutor (5 badges).*
- **Earlier power — Synchronoise around Lv. 52:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Noivern

**Type:** Flying/Dragon · **Final tier weight:** 4
**Role profile:** Atk 70 / Sp. Atk 97 / Spe 123 · Frisk, Infiltrator, Telepathy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Razor Wind:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/TM; type-cohort prevalence 17%; no Center/Tech Tutor overlap.*
- **Earlier power — Razor Wind around Lv. 50:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Obstagoon

**Type:** Dark/Normal · **Final tier weight:** 5
**Role profile:** Atk 90 / Sp. Atk 60 / Spe 95 · Reckless, Guts, Defiant
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Octillery

**Type:** Water · **Final tier weight:** 2
**Role profile:** Atk 105 / Sp. Atk 105 / Spe 45 · Suction Cups, Sniper, Moody
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Acid Spray:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 10%; Center Tutor (before Gym 3).*
- **Add — Water Spout:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Earlier power — Water Spout around Lv. 54:** 150 BP; STAB. Treat this as the curve target, not a fixed slot.

### Oinkologne (F)

**Type:** Normal · **Final tier weight:** 3
**Role profile:** Atk 90 / Sp. Atk 59 / Spe 65 · Aroma Veil, Gluttony, Thick Fat
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 19%; Center Tutor (before Gym 7).*
- **Add — Trailblaze:** Its terrestrial movement and plant association support an active Grass attack rather than generic TM access. *Precedent: TM; type-cohort prevalence 34%; Center Tutor (before Gym 3).*
- **Earlier power — Body Press around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Oinkologne (M)

**Type:** Normal · **Final tier weight:** 3
**Role profile:** Atk 100 / Sp. Atk 59 / Spe 65 · Lingering Aroma, Gluttony, Thick Fat
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Okidogi

**Type:** Poison/Fighting · **Final tier weight:** 4
**Role profile:** Atk 128 / Sp. Atk 58 / Spe 80 · Toxic Chain, Guard Dog
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Psychic Fangs:** Its pronounced jaws or fangs give the unusual Psychic coverage a physical basis. *Precedent: TM; type-cohort prevalence 2%; Center Tutor (before Gym 7).*
- **Earlier power — Psychic Fangs around Lv. 48:** 85 BP; coverage. Treat this as the curve target, not a fixed slot.

### Omastar

**Type:** Rock/Water · **Final tier weight:** 3
**Role profile:** Atk 60 / Sp. Atk 115 / Spe 55 · Swift Swim, Shell Armor, Weak Armor
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Muddy Water:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg/TM; type-cohort prevalence 13%; Center Tutor (before Gym 8).*
- **Add — Supersonic:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power — Muddy Water around Lv. 58:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Oranguru

**Type:** Normal/Psychic · **Final tier weight:** 2
**Role profile:** Atk 60 / Sp. Atk 90 / Spe 60 · Inner Focus, Telepathy, Symbiosis
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Psychic Terrain:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Add — Dream Eater:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 19%; Tech Tutor (5 badges).*
- **Earlier power — Dream Eater around Lv. 54:** 100 BP; STAB. Treat this as the curve target, not a fixed slot.

### Orbeetle

**Type:** Bug/Psychic · **Final tier weight:** 3
**Role profile:** Atk 45 / Sp. Atk 80 / Spe 90 · Swarm, Frisk, Telepathy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Recover:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 9%; no Center/Tech Tutor overlap.*
- **Add — Psyshock:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 4%; Center Tutor (before Gym 7).*
- **Earlier power — Psyshock around Lv. 50:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Orthworm

**Type:** Steel · **Final tier weight:** 4
**Role profile:** Atk 85 / Sp. Atk 60 / Spe 65 · Earth Eater, Sand Veil
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 46%; Center Tutor (before Gym 7).*
- **Earlier power — Body Press around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Overqwil

**Type:** Dark/Poison · **Final tier weight:** 3
**Role profile:** Atk 115 / Sp. Atk 65 / Spe 85 · Poison Point, Swift Swim, Intimidate
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Self Destruct:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 6%; Center Tutor (before Gym 6).*
- **Add — Aqua Tail:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/tutor; type-cohort prevalence 12%; Center Tutor (before Gym 8).*
- **Earlier power — Self Destruct around Lv. 56:** 200 BP; coverage. Treat this as the curve target, not a fixed slot.

### Pachirisu

**Type:** Electric · **Final tier weight:** 1
**Role profile:** Atk 45 / Sp. Atk 45 / Spe 95 · Run Away, Pickup, Volt Absorb
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Baby Doll Eyes:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/tutor; type-cohort prevalence 10%; no Center/Tech Tutor overlap.*
- **Add — Follow Me:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Add — Flatter:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Palkia

**Type:** Water/Dragon · **Final tier weight:** 3
**Role profile:** Atk 120 / Sp. Atk 150 / Spe 100 · Pressure, Telepathy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Dragon Pulse:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM/tutor; type-cohort prevalence 13%; Center Tutor (before Gym 7).*
- **Add — Dragon Claw:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Earlier power — Dragon Pulse around Lv. 50:** 85 BP; STAB. Treat this as the curve target, not a fixed slot.

### Palossand

**Type:** Ghost/Ground · **Final tier weight:** 3
**Role profile:** Atk 75 / Sp. Atk 100 / Spe 35 · Water Compaction, Sand Veil
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Scorching Sands:** A sentient sand castle can weaponize sun-heated sand naturally. *Precedent: TM/tutor; type-cohort prevalence 8%; Center Tutor (before Gym 6).*
- **Add — Ancient Power:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 8%; Legacy Tutor.*
- **Earlier power — Scorching Sands around Lv. 38:** 70 BP; STAB. Treat this as the curve target, not a fixed slot.

### Pangoro

**Type:** Fighting/Dark · **Final tier weight:** 3
**Role profile:** Atk 124 / Sp. Atk 69 / Spe 58 · Iron Fist, Mold Breaker, Scrappy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Storm Throw:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Foul Play:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 11%; Center Tutor (before Gym 8).*
- **Earlier power — Foul Play around Lv. 58:** 95 BP; STAB. Treat this as the curve target, not a fixed slot.

### Parasect

**Type:** Bug/Grass · **Final tier weight:** 1
**Role profile:** Atk 95 / Sp. Atk 60 / Spe 30 · Effect Spore, Dry Skin, Damp
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Grassy Terrain:** Low-tier Bug/Grass field control is distinct from the existing setters. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Add — Grassy Glide:** Priority compensates for extreme slowness without making its Attack exceptional. *Precedent: deliberate design exception; type-cohort prevalence 2%; Center Tutor (before Gym 6).*
- **Add — Fell Stinger:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 5%; Center Tutor (before Gym 5).*
- **Earlier power — Grassy Glide around Lv. 32:** 55 BP; STAB. Treat this as the curve target, not a fixed slot.

### Passimian

**Type:** Fighting · **Final tier weight:** 3
**Role profile:** Atk 120 / Sp. Atk 40 / Spe 80 · Receiver, Defiant
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Coaching:** Its explicit teamwork and ball-passing behavior make this the move's strongest thematic owner. *Precedent: TM/tutor; type-cohort prevalence 80%; Center Tutor (before Gym 5).*
- **Add — Vital Throw:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 13%; Tech Tutor (7 badges).*
- **Earlier power — Vital Throw around Lv. 36:** 70 BP; STAB. Treat this as the curve target, not a fixed slot.

### Pawmot

**Type:** Electric/Fighting · **Final tier weight:** 4
**Role profile:** Atk 115 / Sp. Atk 70 / Spe 105 · Volt Absorb, Natural Cure, Iron Fist
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 18%; Center Tutor (before Gym 7).*
- **Earlier power — Body Press around Lv. 50:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Pecharunt

**Type:** Poison/Ghost · **Final tier weight:** 5
**Role profile:** Atk 88 / Sp. Atk 88 / Spe 88 · Poison Puppeteer
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Pelipper

**Type:** Water/Flying · **Final tier weight:** 6
**Role profile:** Atk 50 / Sp. Atk 95 / Spe 65 · Keen Eye, Hydration, Drizzle
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Brine:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 8%; Center Tutor (before Gym 5).*
- **Earlier power — Brine around Lv. 36:** 65 BP; STAB. Treat this as the curve target, not a fixed slot.

### Perrserker

**Type:** Steel · **Final tier weight:** 4
**Role profile:** Atk 110 / Sp. Atk 50 / Spe 50 · Battle Armor, Tough Claws, Steely Spirit
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Night Slash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 19%; no Center/Tech Tutor overlap.*
- **Earlier power — Night Slash around Lv. 34:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Persian

**Type:** Normal · **Final tier weight:** 2
**Role profile:** Atk 70 / Sp. Atk 65 / Spe 115 · Limber, Technician, Unnerve
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Knock Off:** Fast low-tier disruption gives it a reason to exist beside stronger Normal attackers. *Precedent: TM/tutor; type-cohort prevalence 41%; Center Tutor (League).*
- **Add — Hypnosis:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 11%; no Center/Tech Tutor overlap.*
- **Earlier power — Knock Off around Lv. 32:** 65 BP; coverage. Treat this as the curve target, not a fixed slot.

### Persian (Alola)

**Type:** Dark · **Final tier weight:** 2
**Role profile:** Atk 60 / Sp. Atk 75 / Spe 115 · Fur Coat, Technician, Rattled
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Knock Off:** Its smug, underhanded Dark identity is almost a literal reading of the move. *Precedent: TM/tutor; type-cohort prevalence 69%; Center Tutor (League).*
- **Add — Hypnosis:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 8%; no Center/Tech Tutor overlap.*
- **Earlier power — Knock Off around Lv. 30:** 65 BP; STAB. Treat this as the curve target, not a fixed slot.

### Pheromosa

**Type:** Bug/Fighting · **Final tier weight:** 3
**Role profile:** Atk 137 / Sp. Atk 137 / Spe 151 · Beast Boost
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Silver Wind:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Add — Jump Kick:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Jump Kick around Lv. 58:** 100 BP; STAB. Treat this as the curve target, not a fixed slot.

### Phione

**Type:** Water · **Final tier weight:** 1
**Role profile:** Atk 80 / Sp. Atk 80 / Spe 80 · Hydration
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Moonblast:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Add — Hydro Pump:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 93%; no Center/Tech Tutor overlap.*
- **Add — Heal Bell:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: tutor; type-cohort prevalence 6%; Center Tutor (before Gym 5).*
- **Earlier power — Hydro Pump around Lv. 51:** 110 BP; STAB. Treat this as the curve target, not a fixed slot.

### Pidgeot

**Type:** Normal/Flying · **Final tier weight:** 2
**Role profile:** Atk 80 / Sp. Atk 80 / Spe 0 · Keen Eye, Big Pecks, Covered
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Brave Bird:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 14%; Center Tutor (League).*
- **Add — Air Cutter:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 17%; Center Tutor (before Gym 3).*
- **Earlier power — Brave Bird around Lv. 54:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Pincurchin

**Type:** Electric · **Final tier weight:** 3
**Role profile:** Atk 101 / Sp. Atk 91 / Spe 15 · Lightning Rod, Electric Surge
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Sucker Punch:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg; type-cohort prevalence 22%; Legacy Tutor.*
- **Add — Memento:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Sucker Punch around Lv. 34:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Pinsir

**Type:** Bug · **Final tier weight:** 3
**Role profile:** Atk 125 / Sp. Atk 55 / Spe 85 · Hyper Cutter, Mold Breaker, Moxie
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Close Combat:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 19%; Center Tutor (League).*
- **Add — Thrash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 9%; no Center/Tech Tutor overlap.*
- **Earlier power — Thrash around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Plusle

**Type:** Electric · **Final tier weight:** 1
**Role profile:** Atk 50 / Sp. Atk 85 / Spe 95 · Plus, Dedicated, Lightning Rod
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Fake Tears:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 14%; Tech Tutor (5 badges).*
- **Add — Charm:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 24%; Tech Tutor (5 badges).*
- **Add — Sing:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Politoed

**Type:** Water · **Final tier weight:** 6
**Role profile:** Atk 75 / Sp. Atk 90 / Spe 70 · Water Absorb, Damp, Drizzle
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Poliwrath

**Type:** Water/Fighting · **Final tier weight:** 3
**Role profile:** Atk 95 / Sp. Atk 70 / Spe 70 · Water Absorb, Damp, Swift Swim
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Submission:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 7%; Legacy Tutor.*
- **Add — Mind Reader:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power — Submission around Lv. 50:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Porygon-Z

**Type:** Normal · **Final tier weight:** 4
**Role profile:** Atk 80 / Sp. Atk 135 / Spe 90 · Adaptability, Download, Analytic
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Signal Beam:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/tutor; type-cohort prevalence 8%; Center Tutor (before Gym 6).*
- **Earlier power — Signal Beam around Lv. 40:** 75 BP; coverage. Treat this as the curve target, not a fixed slot.

### Primarina

**Type:** Water/Fairy · **Final tier weight:** 5
**Role profile:** Atk 74 / Sp. Atk 126 / Spe 60 · Torrent, Liquid Voice
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Life Dew:** Its established sound motif makes this a strong identity move. *Precedent: egg; type-cohort prevalence 7%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Probopass

**Type:** Rock/Steel · **Final tier weight:** 3
**Role profile:** Atk 55 / Sp. Atk 75 / Spe 40 · Sturdy, Magnet Pull, Sand Force
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Head Smash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Add — Flash Cannon:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM/tutor; type-cohort prevalence 30%; Center Tutor (before Gym 7).*
- **Earlier power — Head Smash around Lv. 58:** 150 BP; STAB. Treat this as the curve target, not a fixed slot.

### Purugly

**Type:** Normal · **Final tier weight:** 2
**Role profile:** Atk 82 / Sp. Atk 64 / Spe 112 · Thick Fat, Own Tempo, Defiant
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Wake Up Slap:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Add — Last Resort:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 45%; Center Tutor (before Gym 7).*
- **Earlier power — Last Resort around Lv. 54:** 140 BP; STAB. Treat this as the curve target, not a fixed slot.

### Pyroar

**Type:** Fire/Normal · **Final tier weight:** 3
**Role profile:** Atk 68 / Sp. Atk 109 / Spe 106 · Rivalry, Unnerve, Moxie
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Snarl:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 14%; no Center/Tech Tutor overlap.*
- **Add — Entrainment:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; costless Tech Tutor (always).*
- **Earlier power — Snarl around Lv. 24:** 55 BP; coverage. Treat this as the curve target, not a fixed slot.

### Pyukumuku

**Type:** Water · **Final tier weight:** 3
**Role profile:** Atk 60 / Sp. Atk 30 / Spe 5 · Innards Out, Unaware
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Bestow:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Venom Drench:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 6%; costless Tech Tutor (always).*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Quagsire

**Type:** Water/Ground · **Final tier weight:** 3
**Role profile:** Atk 85 / Sp. Atk 65 / Spe 35 · Damp, Water Absorb, Unaware
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Recover:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Add — Body Slam:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 67%; Center Tutor (before Gym 6).*
- **Earlier power — Body Slam around Lv. 48:** 85 BP; coverage. Treat this as the curve target, not a fixed slot.

### Quaquaval

**Type:** Water/Fighting · **Final tier weight:** 4
**Role profile:** Atk 120 / Sp. Atk 85 / Spe 85 · Torrent, Moxie
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Last Resort:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 6%; Center Tutor (before Gym 7).*
- **Earlier power — Last Resort around Lv. 56:** 140 BP; coverage. Treat this as the curve target, not a fixed slot.

### Qwilfish

**Type:** Water/Poison · **Final tier weight:** 1
**Role profile:** Atk 95 / Sp. Atk 65 / Spe 85 · Poison Point, Swift Swim, Intimidate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Barb Barrage:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 1%; no Center/Tech Tutor overlap.*
- **Add — Brine:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 12%; Center Tutor (before Gym 5).*
- **Add — Bubble Beam:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 12%; no Center/Tech Tutor overlap.*
- **Earlier power — Bubble Beam around Lv. 26:** 65 BP; STAB. Treat this as the curve target, not a fixed slot.

### Rabsca

**Type:** Bug/Psychic · **Final tier weight:** 2
**Role profile:** Atk 50 / Sp. Atk 115 / Spe 45 · Synchronize, Telepathy
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Weather Ball:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 6%; Center Tutor (before Gym 7).*
- **Add — Confusion:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 17%; no Center/Tech Tutor overlap.*
- **Earlier power — Weather Ball around Lv. 13:** 50 BP; coverage. Treat this as the curve target, not a fixed slot.

### Raging Bolt

**Type:** Electric/Dragon · **Final tier weight:** 3
**Role profile:** Atk 73 / Sp. Atk 137 / Spe 75 · Protosynthesis
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Volt Switch:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 6%; Center Tutor (League).*
- **Add — Weather Ball:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 18%; Center Tutor (before Gym 7).*
- **Earlier power — Volt Switch around Lv. 36:** 70 BP; STAB. Treat this as the curve target, not a fixed slot.

### Raichu

**Type:** Electric · **Final tier weight:** 3
**Role profile:** Atk 90 / Sp. Atk 90 / Spe 110 · Static, Lightning Rod
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Volt Tackle:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/pre-evolution/TM/tutor; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Add — Electric Terrain:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/pre-evolution/TM; type-cohort prevalence 92%; no Center/Tech Tutor overlap.*
- **Earlier power — Volt Tackle around Lv. 58:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Raichu (Alola)

**Type:** Electric/Psychic · **Final tier weight:** 3
**Role profile:** Atk 85 / Sp. Atk 95 / Spe 110 · Surge Surfer
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Electric Terrain:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Add — Encore:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 20%; Center Tutor (before Gym 5).*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Raikou

**Type:** Electric · **Final tier weight:** 4
**Role profile:** Atk 85 / Sp. Atk 115 / Spe 115 · Pressure, Inner Focus
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Weather Ball:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 18%; Center Tutor (before Gym 7).*
- **Earlier power — Weather Ball around Lv. 17:** 50 BP; coverage. Treat this as the curve target, not a fixed slot.

### Rampardos

**Type:** Rock · **Final tier weight:** 2
**Role profile:** Atk 165 / Sp. Atk 65 / Spe 58 · Mold Breaker, Sheer Force
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Iron Head:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 62%; Center Tutor (before Gym 7).*
- **Add — Crunch:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 34%; Center Tutor (before Gym 7).*
- **Earlier power — Iron Head around Lv. 44:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Rapidash

**Type:** Fire · **Final tier weight:** 3
**Role profile:** Atk 100 / Sp. Atk 80 / Spe 105 · Run Away, Flash Fire, Flame Body
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Double Edge:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 64%; no Center/Tech Tutor overlap.*
- **Add — Morning Sun:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 13%; Legacy Tutor.*
- **Earlier power — Double Edge around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Rapidash (Galar)

**Type:** Psychic/Fairy · **Final tier weight:** 3
**Role profile:** Atk 100 / Sp. Atk 80 / Spe 105 · Run Away, Pastel Veil, Anticipation
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Morning Sun:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg; type-cohort prevalence 6%; Legacy Tutor.*
- **Add — Double Edge:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/egg; type-cohort prevalence 38%; no Center/Tech Tutor overlap.*
- **Earlier power — Double Edge around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Raticate

**Type:** Normal · **Final tier weight:** 3
**Role profile:** Atk 81 / Sp. Atk 50 / Spe 97 · Run Away, Guts, Hustle
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Flame Wheel:** Its jaw-based anatomy gives the coverage a concrete physical source. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Last Resort:** Its jaw-based anatomy gives the coverage a concrete physical source. *Precedent: egg/tutor; type-cohort prevalence 45%; Center Tutor (before Gym 7).*
- **Earlier power — Last Resort around Lv. 58:** 140 BP; STAB. Treat this as the curve target, not a fixed slot.

### Raticate (Alola)

**Type:** Dark/Normal · **Final tier weight:** 3
**Role profile:** Atk 71 / Sp. Atk 40 / Spe 77 · Gluttony, Hustle, Thick Fat
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Revenge:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 20%; Center Tutor (before Gym 6).*
- **Add — Uproar:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 33%; Tech Tutor (6 badges).*
- **Earlier power — Uproar around Lv. 58:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Rayquaza

**Type:** Dragon/Flying · **Final tier weight:** 3
**Role profile:** Atk 150 / Sp. Atk 150 / Spe 95 · Air Lock
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Dragon Rush:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 14%; no Center/Tech Tutor overlap.*
- **Add — Dragon Claw:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 14%; no Center/Tech Tutor overlap.*
- **Earlier power — Dragon Rush around Lv. 58:** 100 BP; STAB. Treat this as the curve target, not a fixed slot.

### Regice

**Type:** Ice · **Final tier weight:** 3
**Role profile:** Atk 50 / Sp. Atk 100 / Spe 50 · Clear Body, Ice Body
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Frost Breath:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 59%; Center Tutor (before Gym 8).*
- **Add — Thunderbolt:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 19%; no Center/Tech Tutor overlap.*
- **Earlier power — Thunderbolt around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Regidrago

**Type:** Dragon · **Final tier weight:** 4
**Role profile:** Atk 100 / Sp. Atk 100 / Spe 80 · Dragons Maw
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Vice Grip:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Regieleki

**Type:** Electric · **Final tier weight:** 4
**Role profile:** Atk 100 / Sp. Atk 100 / Spe 200 · Transistor
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Electric Terrain:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 92%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Regigigas

**Type:** Normal · **Final tier weight:** 3
**Role profile:** Atk 160 / Sp. Atk 80 / Spe 100 · Slow Start
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Dizzy Punch:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up; type-cohort prevalence 9%; no Center/Tech Tutor overlap.*
- **Add — Superpower:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/TM/tutor; type-cohort prevalence 17%; Center Tutor (League).*
- **Earlier power — Superpower around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Regirock

**Type:** Rock · **Final tier weight:** 3
**Role profile:** Atk 100 / Sp. Atk 50 / Spe 50 · Clear Body, Sturdy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 47%; Center Tutor (before Gym 7).*
- **Add — Drain Punch:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: TM/tutor; type-cohort prevalence 4%; Center Tutor (before Gym 6).*
- **Earlier power — Body Press around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Registeel

**Type:** Steel · **Final tier weight:** 4
**Role profile:** Atk 75 / Sp. Atk 75 / Spe 50 · Clear Body, Light Metal
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 46%; Center Tutor (before Gym 7).*
- **Earlier power — Body Press around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Relicanth

**Type:** Water/Rock · **Final tier weight:** 3
**Role profile:** Atk 90 / Sp. Atk 45 / Spe 55 · Swift Swim, Rock Head, Sturdy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Skull Bash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 17%; Center Tutor (before Gym 6).*
- **Add — Rock Slide:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 39%; no Center/Tech Tutor overlap.*
- **Earlier power — Skull Bash around Lv. 56:** 130 BP; coverage. Treat this as the curve target, not a fixed slot.

### Reshiram

**Type:** Dragon/Fire · **Final tier weight:** 3
**Role profile:** Atk 120 / Sp. Atk 150 / Spe 90 · Turboblaze
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Mystical Fire:** Its supernatural or elegant fire identity makes the move feel native rather than generic coverage. *Precedent: TM; type-cohort prevalence 9%; Center Tutor (before Gym 6).*
- **Add — Draco Meteor:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM/tutor; type-cohort prevalence 6%; Center Tutor (League).*
- **Earlier power — Draco Meteor around Lv. 58:** 130 BP; STAB. Treat this as the curve target, not a fixed slot.

### Reuniclus

**Type:** Psychic · **Final tier weight:** 4
**Role profile:** Atk 65 / Sp. Atk 125 / Spe 30 · Overcoat, Magic Guard, Regenerator
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Acid Armor:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 1%; Center Tutor (before Gym 6).*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Revavroom

**Type:** Steel/Poison · **Final tier weight:** 3
**Role profile:** Atk 119 / Sp. Atk 54 / Spe 90 · Overcoat, Filter
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Hard Press:** Its industrial chassis makes a literal mechanical press easy to justify. *Precedent: TM; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Add — Steel Roller:** A literal engine supplies the strongest mechanical justification for the move. *Precedent: deliberate design exception; type-cohort prevalence 4%; Tech Tutor (6 badges).*
- **Earlier power — Steel Roller around Lv. 44:** 130 BP; STAB. Treat this as the curve target, not a fixed slot.

### Rhyperior

**Type:** Ground/Rock · **Final tier weight:** 4
**Role profile:** Atk 140 / Sp. Atk 55 / Spe 40 · Lightning Rod, Solid Rock, Reckless
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Rock Slide:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 93%; no Center/Tech Tutor overlap.*
- **Earlier power — Rock Slide around Lv. 42:** 75 BP; STAB. Treat this as the curve target, not a fixed slot.

### Ribombee

**Type:** Bug/Fairy · **Final tier weight:** 3
**Role profile:** Atk 55 / Sp. Atk 95 / Spe 124 · Honey Gather, Shield Dust, Sweet Veil
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Moonblast:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Silver Wind:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 15%; no Center/Tech Tutor overlap.*
- **Earlier power — Moonblast around Lv. 58:** 95 BP; STAB. Treat this as the curve target, not a fixed slot.

### Rillaboom

**Type:** Grass · **Final tier weight:** 5
**Role profile:** Atk 125 / Sp. Atk 60 / Spe 85 · Overgrow, Grassy Surge
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Hammer Arm:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Earlier power — Hammer Arm around Lv. 59:** 100 BP; coverage. Treat this as the curve target, not a fixed slot.

### Roaring Moon

**Type:** Dragon/Dark · **Final tier weight:** 3
**Role profile:** Atk 139 / Sp. Atk 55 / Spe 119 · Protosynthesis
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 17%; Center Tutor (before Gym 7).*
- **Add — Dragon Tail:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 13%; Tech Tutor (7 badges).*
- **Earlier power — Body Press around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Roserade

**Type:** Grass/Poison · **Final tier weight:** 4
**Role profile:** Atk 70 / Sp. Atk 125 / Spe 90 · Natural Cure, Poison Point, Technician
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Leaf Storm:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 10%; Center Tutor (League).*
- **Earlier power — Leaf Storm around Lv. 58:** 130 BP; STAB. Treat this as the curve target, not a fixed slot.

### Rotom (Fan)

**Type:** Electric/Flying · **Final tier weight:** 3
**Role profile:** Atk 65 / Sp. Atk 105 / Spe 86 · Levitate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Thunderbolt:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/TM/tutor; type-cohort prevalence 15%; no Center/Tech Tutor overlap.*
- **Add — Thunder:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/TM; type-cohort prevalence 15%; no Center/Tech Tutor overlap.*
- **Earlier power — Thunder around Lv. 58:** 110 BP; STAB. Treat this as the curve target, not a fixed slot.

### Rotom (Frost)

**Type:** Electric/Ice · **Final tier weight:** 3
**Role profile:** Atk 65 / Sp. Atk 105 / Spe 86 · Levitate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Thunderbolt:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/TM/tutor; type-cohort prevalence 19%; no Center/Tech Tutor overlap.*
- **Add — Thunder:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/TM; type-cohort prevalence 19%; no Center/Tech Tutor overlap.*
- **Earlier power — Thunder around Lv. 58:** 110 BP; STAB. Treat this as the curve target, not a fixed slot.

### Rotom (Heat)

**Type:** Electric/Fire · **Final tier weight:** 3
**Role profile:** Atk 65 / Sp. Atk 105 / Spe 86 · Levitate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Thunderbolt:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM/tutor; type-cohort prevalence 11%; no Center/Tech Tutor overlap.*
- **Add — Thunder:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 9%; no Center/Tech Tutor overlap.*
- **Earlier power — Thunder around Lv. 58:** 110 BP; STAB. Treat this as the curve target, not a fixed slot.

### Rotom (Mow)

**Type:** Electric/Grass · **Final tier weight:** 3
**Role profile:** Atk 65 / Sp. Atk 105 / Spe 86 · Levitate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Thunderbolt:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM/tutor; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Add — Thunder:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Earlier power — Thunder around Lv. 58:** 110 BP; STAB. Treat this as the curve target, not a fixed slot.

### Rotom (Wash)

**Type:** Electric/Water · **Final tier weight:** 3
**Role profile:** Atk 65 / Sp. Atk 105 / Spe 86 · Levitate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Charge Beam:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM/tutor; type-cohort prevalence 6%; Center Tutor (before Gym 4).*
- **Add — Thunderbolt:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM/tutor; type-cohort prevalence 10%; no Center/Tech Tutor overlap.*
- **Earlier power — Thunderbolt around Lv. 58:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Runerigus

**Type:** Ground/Ghost · **Final tier weight:** 3
**Role profile:** Atk 95 / Sp. Atk 50 / Spe 30 · Wandering Spirit
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Phantom Force:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 5%; Center Tutor (before Gym 8).*
- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 14%; Center Tutor (before Gym 7).*
- **Earlier power — Phantom Force around Lv. 58:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Sableye

**Type:** Dark/Ghost · **Final tier weight:** 2
**Role profile:** Atk 85 / Sp. Atk 65 / Spe 50 · Keen Eye, Stall, Prankster
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Recover:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Add — Moonlight:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; Legacy Tutor.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Salamence

**Type:** Dragon/Flying · **Final tier weight:** 5
**Role profile:** Atk 135 / Sp. Atk 110 / Spe 100 · Intimidate, Moxie
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Fire Fang:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg/TM; type-cohort prevalence 8%; Center Tutor (before Gym 4).*
- **Earlier power — Fire Fang around Lv. 34:** 65 BP; coverage. Treat this as the curve target, not a fixed slot.

### Salazzle

**Type:** Poison/Fire · **Final tier weight:** 4
**Role profile:** Atk 64 / Sp. Atk 111 / Spe 117 · Corrosion, Oblivious
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Flame Burst:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power — Flame Burst around Lv. 36:** 70 BP; STAB. Treat this as the curve target, not a fixed slot.

### Samurott

**Type:** Water · **Final tier weight:** 4
**Role profile:** Atk 100 / Sp. Atk 108 / Spe 70 · Torrent, Shell Armor
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Brine:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg; type-cohort prevalence 60%; Center Tutor (before Gym 5).*
- **Earlier power — Brine around Lv. 33:** 65 BP; STAB. Treat this as the curve target, not a fixed slot.

### Samurott (Hisui)

**Type:** Water/Dark · **Final tier weight:** 4
**Role profile:** Atk 108 / Sp. Atk 100 / Spe 85 · Torrent, Sharpness
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Night Slash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 13%; no Center/Tech Tutor overlap.*
- **Earlier power — Night Slash around Lv. 36:** 70 BP; STAB. Treat this as the curve target, not a fixed slot.

### Sandaconda

**Type:** Ground · **Final tier weight:** 3
**Role profile:** Atk 107 / Sp. Atk 65 / Spe 71 · Sand Spit, Shed Skin, Sand Veil
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Last Resort:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 7%; Center Tutor (before Gym 7).*
- **Add — Dragon Rush:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 10%; no Center/Tech Tutor overlap.*
- **Earlier power — Last Resort around Lv. 56:** 140 BP; coverage. Treat this as the curve target, not a fixed slot.

### Sandslash

**Type:** Ground · **Final tier weight:** 3
**Role profile:** Atk 100 / Sp. Atk 45 / Spe 65 · Sand Veil, Hyper Cutter, Sand Rush
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Night Slash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 14%; no Center/Tech Tutor overlap.*
- **Add — Chip Away:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 12%; no Center/Tech Tutor overlap.*
- **Earlier power — Night Slash around Lv. 34:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Sandslash (Alola)

**Type:** Ice/Steel · **Final tier weight:** 3
**Role profile:** Atk 100 / Sp. Atk 25 / Spe 65 · Snow Cloak, Hyper Cutter, Slush Rush
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Crush Claw:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Add — Chip Away:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Crush Claw around Lv. 40:** 75 BP; coverage. Treat this as the curve target, not a fixed slot.

### Sandy Shocks

**Type:** Electric/Ground · **Final tier weight:** 3
**Role profile:** Atk 81 / Sp. Atk 121 / Spe 101 · Protosynthesis
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Power Gem:** Its mineral, jewel, light, or crystalline anatomy gives the attack a visible source. *Precedent: TM; type-cohort prevalence 8%; Center Tutor (before Gym 7).*
- **Add — Volt Switch:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 5%; Center Tutor (League).*
- **Earlier power — Power Gem around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Sawk

**Type:** Fighting · **Final tier weight:** 4
**Role profile:** Atk 125 / Sp. Atk 30 / Spe 85 · Sturdy, Inner Focus, Mold Breaker
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Karate Chop:** Its established sound motif makes this a strong identity move. *Precedent: level-up; type-cohort prevalence 7%; no Center/Tech Tutor overlap.*
- **Earlier power — Karate Chop around Lv. 17:** 50 BP; coverage. Treat this as the curve target, not a fixed slot.

### Sceptile

**Type:** Grass · **Final tier weight:** 3
**Role profile:** Atk 85 / Sp. Atk 105 / Spe 120 · Overgrow, Unburden
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Dragon Breath:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Add — Slash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 8%; no Center/Tech Tutor overlap.*
- **Earlier power — Slash around Lv. 34:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Scizor

**Type:** Bug/Steel · **Final tier weight:** 5
**Role profile:** Atk 130 / Sp. Atk 55 / Spe 65 · Swarm, Technician, Light Metal
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Steel Wing:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg/TM; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Earlier power — Steel Wing around Lv. 39:** 70 BP; STAB. Treat this as the curve target, not a fixed slot.

### Scolipede

**Type:** Bug/Poison · **Final tier weight:** 3
**Role profile:** Atk 100 / Sp. Atk 55 / Spe 112 · Poison Point, Swarm, Speed Boost
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Rock Climb:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 9%; Center Tutor (before Gym 7).*
- **Add — Steamroller:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Rock Climb around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Scovillain

**Type:** Grass/Fire · **Final tier weight:** 2
**Role profile:** Atk 108 / Sp. Atk 108 / Spe 75 · Chlorophyll, Insomnia, Moody
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Rage Powder:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Add — Leech Seed:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Scrafty

**Type:** Dark/Fighting · **Final tier weight:** 2
**Role profile:** Atk 90 / Sp. Atk 45 / Spe 58 · Shed Skin, Moxie, Intimidate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Faint Attack:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Add — Chip Away:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Earlier power — Chip Away around Lv. 30:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Scream Tail

**Type:** Fairy/Psychic · **Final tier weight:** 3
**Role profile:** Atk 65 / Sp. Atk 65 / Spe 111 · Protosynthesis
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Misty Terrain:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 11%; Tech Tutor (3 badges).*
- **Add — Psychic Terrain:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 21%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Seaking

**Type:** Water · **Final tier weight:** 1
**Role profile:** Atk 92 / Sp. Atk 65 / Spe 68 · Swift Swim, Water Veil, Lightning Rod
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Skull Bash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 23%; Center Tutor (before Gym 6).*
- **Add — Aqua Tail:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 44%; Center Tutor (before Gym 8).*
- **Add — Body Slam:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 67%; Center Tutor (before Gym 6).*
- **Earlier power — Skull Bash around Lv. 49:** 130 BP; coverage. Treat this as the curve target, not a fixed slot.

### Seismitoad

**Type:** Water/Ground · **Final tier weight:** 3
**Role profile:** Atk 95 / Sp. Atk 85 / Spe 74 · Swift Swim, Poison Touch, Water Absorb
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Earth Power:** Its vibrations and 85 Sp. Atk make special Ground STAB a real alternative. *Precedent: egg/TM/tutor; type-cohort prevalence 21%; Center Tutor (before Gym 8).*
- **Add — Mud Bomb:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 9%; no Center/Tech Tutor overlap.*
- **Earlier power — Earth Power around Lv. 38:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Serperior

**Type:** Grass · **Final tier weight:** 3
**Role profile:** Atk 75 / Sp. Atk 75 / Spe 113 · Overgrow, Covered
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Iron Tail:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 18%; Center Tutor (before Gym 7).*
- **Add — Leaf Tornado:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 9%; no Center/Tech Tutor overlap.*
- **Earlier power — Iron Tail around Lv. 56:** 100 BP; coverage. Treat this as the curve target, not a fixed slot.

### Seviper

**Type:** Poison · **Final tier weight:** 1
**Role profile:** Atk 100 / Sp. Atk 100 / Spe 65 · Shed Skin, Infiltrator
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Scale Shot:** A scaled snake with middling Speed gains a risky physical speed-control option. *Precedent: TM; type-cohort prevalence 15%; Center Tutor (before Gym 7).*
- **Add — Night Slash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 12%; no Center/Tech Tutor overlap.*
- **Add — Punishment:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier setup — Coil around Lv. 30:** Move it forward from Lv. 44; the coiling snake animation and middling Speed make this unusually exact. Do not pair this access with Baton Pass.
- **Earlier power — Night Slash around Lv. 27:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Sharpedo

**Type:** Water/Dark · **Final tier weight:** 3
**Role profile:** Atk 120 / Sp. Atk 95 / Spe 95 · Rough Skin, Speed Boost
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Brine:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 4%; Center Tutor (before Gym 5).*
- **Add — Psychic Fangs:** Its pronounced jaws or fangs give the unusual Psychic coverage a physical basis. *Precedent: egg/TM; type-cohort prevalence 9%; Center Tutor (before Gym 7).*
- **Earlier power — Psychic Fangs around Lv. 48:** 85 BP; coverage. Treat this as the curve target, not a fixed slot.

### Shaymin (Land)

**Type:** Grass · **Final tier weight:** 4
**Role profile:** Atk 100 / Sp. Atk 100 / Spe 100 · Natural Cure
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Recover:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 11%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Shaymin (Sky)

**Type:** Grass/Flying · **Final tier weight:** 4
**Role profile:** Atk 103 / Sp. Atk 120 / Spe 127 · Serene Grace
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Recover:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 8%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Shedinja

**Type:** Bug/Ghost · **Final tier weight:** 6
**Role profile:** Atk 90 / Sp. Atk 30 / Spe 40 · Wonder Guard
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Bug Bite:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/tutor; type-cohort prevalence 3%; Center Tutor (before Gym 3).*
- **Earlier power — Bug Bite around Lv. 29:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Shiftry

**Type:** Grass/Dark · **Final tier weight:** 3
**Role profile:** Atk 100 / Sp. Atk 90 / Spe 80 · Chlorophyll, Wind Rider, Pickpocket
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Knock Off:** Its hands and malicious forest-trickster role distinguish this from pure damage coverage. *Precedent: TM/tutor; type-cohort prevalence 46%; Center Tutor (League).*
- **Add — Foul Play:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 14%; Center Tutor (before Gym 8).*
- **Earlier power — Foul Play around Lv. 58:** 95 BP; STAB. Treat this as the curve target, not a fixed slot.

### Shiinotic

**Type:** Grass/Fairy · **Final tier weight:** 3
**Role profile:** Atk 45 / Sp. Atk 90 / Spe 30 · Illuminate, Effect Spore, Rain Dish
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Pollen Puff:** Its flower, pollen, or caregiving identity supports both the attack and ally-heal flavor. *Precedent: TM; type-cohort prevalence 9%; Center Tutor (before Gym 8).*
- **Add — Sludge Bomb:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 15%; no Center/Tech Tutor overlap.*
- **Earlier power — Sludge Bomb around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Shuckle

**Type:** Bug/Rock · **Final tier weight:** 3
**Role profile:** Atk 10 / Sp. Atk 10 / Spe 5 · Sturdy, Gluttony, Contrary
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Acupressure:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg; type-cohort prevalence 2%; Center Tutor (before Gym 6).*
- **Add — Sweet Scent:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg; type-cohort prevalence 2%; costless Tech Tutor (always).*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Sigilyph

**Type:** Psychic/Flying · **Final tier weight:** 3
**Role profile:** Atk 58 / Sp. Atk 103 / Spe 97 · Wonder Skin, Magic Guard, Tinted Lens
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Synchronoise:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up; type-cohort prevalence 8%; Tech Tutor (5 badges).*
- **Add — Future Sight:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/TM; type-cohort prevalence 15%; Center Tutor (before Gym 7).*
- **Earlier power — Synchronoise around Lv. 58:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Simipour

**Type:** Water · **Final tier weight:** 2
**Role profile:** Atk 98 / Sp. Atk 98 / Spe 101 · Gluttony, Torrent
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Hydro Pump:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 93%; no Center/Tech Tutor overlap.*
- **Add — Aqua Tail:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 44%; Center Tutor (before Gym 8).*
- **Compatibility gap — Flip Turn:** Verify or add TM/tutor compatibility rather than level-up access; an agile Water primate can reasonably share the expanded pivot TM.
- **Earlier power — Hydro Pump around Lv. 54:** 110 BP; STAB. Treat this as the curve target, not a fixed slot.

### Simisage

**Type:** Grass · **Final tier weight:** 2
**Role profile:** Atk 98 / Sp. Atk 98 / Spe 101 · Gluttony, Overgrow
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Leaf Storm:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg/TM; type-cohort prevalence 85%; Center Tutor (League).*
- **Add — Magical Leaf:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg/TM; type-cohort prevalence 82%; Tech Tutor (7 badges).*
- **Compatibility gap — Grassy Glide:** Verify or add TM/tutor compatibility rather than level-up access; its physical Grass role fits the modern Grass tutor even without natural access.
- **Earlier power — Leaf Storm around Lv. 54:** 130 BP; STAB. Treat this as the curve target, not a fixed slot.

### Simisear

**Type:** Fire · **Final tier weight:** 2
**Role profile:** Atk 98 / Sp. Atk 98 / Spe 101 · Gluttony, Blaze
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Disarming Voice:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 6%; Tech Tutor (7 badges).*
- **Add — Flare Blitz:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 94%; Center Tutor (League).*
- **Compatibility gap — Temper Flare:** Verify or add TM/tutor compatibility rather than level-up access; its emotional Fire motif and physical option fit the modern Fire TM.
- **Earlier power — Flare Blitz around Lv. 54:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Sirfetch'd

**Type:** Fighting · **Final tier weight:** 3
**Role profile:** Atk 135 / Sp. Atk 68 / Spe 65 · Steadfast, Scrappy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Sky Attack:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 5%; Center Tutor (before Gym 7).*
- **Add — Night Slash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 15%; no Center/Tech Tutor overlap.*
- **Earlier power — Sky Attack around Lv. 56:** 140 BP; coverage. Treat this as the curve target, not a fixed slot.

### Skarmory

**Type:** Steel/Flying · **Final tier weight:** 5
**Role profile:** Atk 80 / Sp. Atk 40 / Spe 70 · Keen Eye, Sturdy, Weak Armor
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Night Slash:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg/TM; type-cohort prevalence 12%; no Center/Tech Tutor overlap.*
- **Earlier power — Night Slash around Lv. 37:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Skeledirge

**Type:** Fire/Ghost · **Final tier weight:** 5
**Role profile:** Atk 75 / Sp. Atk 110 / Spe 66 · Blaze, Unaware
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Skuntank

**Type:** Poison/Dark · **Final tier weight:** 2
**Role profile:** Atk 93 / Sp. Atk 71 / Spe 84 · Stench, Lingering Aroma, Aftermath
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Slash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 8%; no Center/Tech Tutor overlap.*
- **Add — Double Edge:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 52%; no Center/Tech Tutor overlap.*
- **Earlier power — Double Edge around Lv. 52:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Slaking

**Type:** Normal · **Final tier weight:** 4
**Role profile:** Atk 160 / Sp. Atk 95 / Spe 100 · Truant
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Slash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/pre-evolution; type-cohort prevalence 20%; no Center/Tech Tutor overlap.*
- **Earlier power — Slash around Lv. 36:** 70 BP; STAB. Treat this as the curve target, not a fixed slot.

### Slither Wing

**Type:** Bug/Fighting · **Final tier weight:** 3
**Role profile:** Atk 135 / Sp. Atk 85 / Spe 81 · Protosynthesis
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 9%; Center Tutor (before Gym 7).*
- **Add — Flare Blitz:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: TM; type-cohort prevalence 6%; Center Tutor (League).*
- **Earlier power — Flare Blitz around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Slowbro

**Type:** Water/Psychic · **Final tier weight:** 5
**Role profile:** Atk 75 / Sp. Atk 100 / Spe 30 · Oblivious, Own Tempo, Regenerator
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Stomp:** Its jaw-based anatomy gives the coverage a concrete physical source. *Precedent: level-up/egg; type-cohort prevalence 7%; no Center/Tech Tutor overlap.*
- **Earlier power — Stomp around Lv. 34:** 65 BP; coverage. Treat this as the curve target, not a fixed slot.

### Slowbro (Galar)

**Type:** Poison/Psychic · **Final tier weight:** 5
**Role profile:** Atk 100 / Sp. Atk 100 / Spe 30 · Quick Draw, Own Tempo, Regenerator
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Slowking

**Type:** Water/Psychic · **Final tier weight:** 5
**Role profile:** Atk 75 / Sp. Atk 100 / Spe 30 · Oblivious, Own Tempo, Regenerator
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Sludge Wave:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/TM; type-cohort prevalence 6%; Center Tutor (before Gym 8).*
- **Earlier power — Sludge Wave around Lv. 59:** 95 BP; coverage. Treat this as the curve target, not a fixed slot.

### Slowking (Galar)

**Type:** Poison/Psychic · **Final tier weight:** 5
**Role profile:** Atk 65 / Sp. Atk 110 / Spe 30 · Curious Medicine, Own Tempo, Regenerator
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Belch:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Earlier power — Belch around Lv. 61:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Slurpuff

**Type:** Fairy · **Final tier weight:** 3
**Role profile:** Atk 80 / Sp. Atk 85 / Spe 72 · Sweet Veil, Unburden
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Yawn:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 12%; no Center/Tech Tutor overlap.*
- **Add — Copycat:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 15%; Center Tutor (before Gym 2).*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Smeargle

**Type:** Normal · **Final tier weight:** 3
**Role profile:** Atk 20 / Sp. Atk 20 / Spe 75 · Own Tempo, Technician, Moody
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Sneasler

**Type:** Fighting/Poison · **Final tier weight:** 5
**Role profile:** Atk 130 / Sp. Atk 40 / Spe 120 · Pressure, Unburden, Poison Touch
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Snorlax

**Type:** Normal · **Final tier weight:** 5
**Role profile:** Atk 110 / Sp. Atk 65 / Spe 30 · Immunity, Thick Fat, Gluttony
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Double Edge:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 77%; no Center/Tech Tutor overlap.*
- **Earlier power — Double Edge around Lv. 61:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Solgaleo

**Type:** Psychic/Steel · **Final tier weight:** 3
**Role profile:** Atk 137 / Sp. Atk 113 / Spe 97 · Full Metal Body
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Wake Up Slap:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Psychic Fangs:** Its pronounced jaws or fangs give the unusual Psychic coverage a physical basis. *Precedent: TM; type-cohort prevalence 8%; Center Tutor (before Gym 7).*
- **Earlier power — Psychic Fangs around Lv. 50:** 85 BP; STAB. Treat this as the curve target, not a fixed slot.

### Solrock

**Type:** Rock/Psychic · **Final tier weight:** 2
**Role profile:** Atk 95 / Sp. Atk 55 / Spe 70 · Levitate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Smack Down:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: TM; type-cohort prevalence 8%; Center Tutor (before Gym 2).*
- **Add — Psychic Terrain:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: TM; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power — Smack Down around Lv. 15:** 50 BP; STAB. Treat this as the curve target, not a fixed slot.

### Spectrier

**Type:** Ghost · **Final tier weight:** 3
**Role profile:** Atk 65 / Sp. Atk 145 / Spe 130 · Grim Neigh
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Uproar:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 27%; Tech Tutor (6 badges).*
- **Add — Hyper Beam:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 95%; Tech Tutor (6 badges).*
- **Earlier power — Hyper Beam around Lv. 56:** 150 BP; coverage. Treat this as the curve target, not a fixed slot.

### Spidops

**Type:** Bug · **Final tier weight:** 1
**Role profile:** Atk 84 / Sp. Atk 52 / Spe 35 · Insomnia, Stakeout
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — First Impression:** Its established sound motif makes this a strong identity move. *Precedent: egg; type-cohort prevalence 15%; no Center/Tech Tutor overlap.*
- **Add — Sucker Punch:** Its established sound motif makes this a strong identity move. *Precedent: egg; type-cohort prevalence 19%; Legacy Tutor.*
- **Add — Lunge:** Its established sound motif makes this a strong identity move. *Precedent: egg/TM; type-cohort prevalence 57%; Center Tutor (before Gym 7).*
- **Earlier power — First Impression around Lv. 51:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Spinda

**Type:** Normal · **Final tier weight:** 1
**Role profile:** Atk 66 / Sp. Atk 66 / Spe 68 · Own Tempo, Tangled Feet, Contrary
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Smelling Salts:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Add — Rapid Spin:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 5%; Center Tutor (before Gym 5).*
- **Add — Psycho Cut:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; Center Tutor (before Gym 5).*
- **Earlier power — Smelling Salts around Lv. 29:** 70 BP; STAB. Treat this as the curve target, not a fixed slot.

### Spiritomb

**Type:** Ghost/Dark · **Final tier weight:** 3
**Role profile:** Atk 92 / Sp. Atk 92 / Spe 35 · Pressure, Infiltrator
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Burning Jealousy:** Its collection of malicious spirits supports jealous, retaliatory fire. *Precedent: TM/tutor; type-cohort prevalence 19%; Tech Tutor (8 badges).*
- **Add — Foul Play:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg/TM/tutor; type-cohort prevalence 35%; Center Tutor (before Gym 8).*
- **Earlier power — Foul Play around Lv. 58:** 95 BP; STAB. Treat this as the curve target, not a fixed slot.

### Stakataka

**Type:** Rock/Steel · **Final tier weight:** 4
**Role profile:** Atk 131 / Sp. Atk 53 / Spe 13 · Beast Boost
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 46%; Center Tutor (before Gym 7).*
- **Earlier power — Body Press around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Staraptor

**Type:** Normal/Flying · **Final tier weight:** 4
**Role profile:** Atk 120 / Sp. Atk 50 / Spe 100 · Intimidate, Reckless
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Double Edge:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 72%; no Center/Tech Tutor overlap.*
- **Earlier power — Double Edge around Lv. 58:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Starmie

**Type:** Water/Psychic · **Final tier weight:** 4
**Role profile:** Atk 75 / Sp. Atk 100 / Spe 115 · Illuminate, Natural Cure, Analytic
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Bubble Beam:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/pre-evolution/TM; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Earlier power — Bubble Beam around Lv. 33:** 65 BP; STAB. Treat this as the curve target, not a fixed slot.

### Steelix

**Type:** Steel/Ground · **Final tier weight:** 5
**Role profile:** Atk 85 / Sp. Atk 55 / Spe 30 · Rock Head, Sturdy, Sheer Force
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Head Smash:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/egg/TM; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Earlier power — Head Smash around Lv. 59:** 150 BP; coverage. Treat this as the curve target, not a fixed slot.

### Stonjourner

**Type:** Rock · **Final tier weight:** 3
**Role profile:** Atk 125 / Sp. Atk 20 / Spe 70 · Power Spot, Dedicated
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Hard Press:** Its monolithic weight creates a rare natural home for Hard Press. *Precedent: TM; type-cohort prevalence 19%; no Center/Tech Tutor overlap.*
- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 47%; Center Tutor (before Gym 7).*
- **Earlier power — Hard Press around Lv. 40:** up to 100 BP (HP-dependent); coverage. Treat this as the curve target, not a fixed slot.

### Stoutland

**Type:** Normal · **Final tier weight:** 3
**Role profile:** Atk 110 / Sp. Atk 45 / Spe 80 · Intimidate, Sand Rush, Scrappy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Psychic Fangs:** Its pronounced jaws or fangs give the unusual Psychic coverage a physical basis. *Precedent: egg/TM; type-cohort prevalence 8%; Center Tutor (before Gym 7).*
- **Add — Covet:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 39%; Center Tutor (before Gym 3).*
- **Earlier power — Psychic Fangs around Lv. 48:** 85 BP; coverage. Treat this as the curve target, not a fixed slot.

### Stunfisk

**Type:** Ground/Electric · **Final tier weight:** 3
**Role profile:** Atk 66 / Sp. Atk 81 / Spe 32 · Static, Limber, Sand Veil
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Sludge Wave:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 6%; Center Tutor (before Gym 8).*
- **Add — Shock Wave:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 14%; Tech Tutor (7 badges).*
- **Earlier power — Sludge Wave around Lv. 56:** 95 BP; coverage. Treat this as the curve target, not a fixed slot.

### Stunfisk (Galar)

**Type:** Ground/Steel · **Final tier weight:** 3
**Role profile:** Atk 81 / Sp. Atk 66 / Spe 32 · Mimicry
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Yawn:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Add — Reflect Type:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Sudowoodo

**Type:** Rock · **Final tier weight:** 3
**Role profile:** Atk 100 / Sp. Atk 30 / Spe 30 · Sturdy, Rock Head, Rattled
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Self Destruct:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 26%; Center Tutor (before Gym 6).*
- **Add — Slam:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 9%; no Center/Tech Tutor overlap.*
- **Earlier power — Self Destruct around Lv. 56:** 200 BP; coverage. Treat this as the curve target, not a fixed slot.

### Suicune

**Type:** Water · **Final tier weight:** 4
**Role profile:** Atk 75 / Sp. Atk 90 / Spe 85 · Pressure, Inner Focus
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Bubble Beam:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 49%; no Center/Tech Tutor overlap.*
- **Earlier power — Bubble Beam around Lv. 33:** 65 BP; STAB. Treat this as the curve target, not a fixed slot.

### Sunflora

**Type:** Grass · **Final tier weight:** 1
**Role profile:** Atk 75 / Sp. Atk 105 / Spe 30 · Chlorophyll, Solar Power, Early Bird
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Grassy Terrain:** A slow low-tier sun specialist benefits from a second field identity. *Precedent: egg/TM; type-cohort prevalence 83%; no Center/Tech Tutor overlap.*
- **Add — Earth Power:** 105 Sp. Atk makes Ground coverage meaningful while its low Speed and tier keep it fair. *Precedent: TM/tutor; type-cohort prevalence 22%; Center Tutor (before Gym 8).*
- **Add — Morning Sun:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; Legacy Tutor.*
- **Earlier power — Earth Power around Lv. 38:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Swalot

**Type:** Poison · **Final tier weight:** 2
**Role profile:** Atk 73 / Sp. Atk 73 / Spe 53 · Liquid Ooze, Sticky Hold, Gluttony
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Clear Smog:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 21%; no Center/Tech Tutor overlap.*
- **Add — Sludge Wave:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 83%; Center Tutor (before Gym 8).*
- **Earlier power — Sludge Wave around Lv. 54:** 95 BP; STAB. Treat this as the curve target, not a fixed slot.

### Swampert

**Type:** Water/Ground · **Final tier weight:** 4
**Role profile:** Atk 110 / Sp. Atk 85 / Spe 60 · Torrent, Damp
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Mud Bomb:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 9%; no Center/Tech Tutor overlap.*
- **Earlier power — Mud Bomb around Lv. 33:** 65 BP; STAB. Treat this as the curve target, not a fixed slot.

### Swanna

**Type:** Water/Flying · **Final tier weight:** 2
**Role profile:** Atk 87 / Sp. Atk 87 / Spe 98 · Keen Eye, Big Pecks, Hydration
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Brine:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg; type-cohort prevalence 8%; Center Tutor (before Gym 5).*
- **Add — Steel Wing:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/TM; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Earlier power — Steel Wing around Lv. 30:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Swellow

**Type:** Normal/Flying · **Final tier weight:** 4
**Role profile:** Atk 85 / Sp. Atk 75 / Spe 125 · Guts, Scrappy
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Boomburst:** Its exceptional sound-producing anatomy justifies rare access to this premium attack. *Precedent: egg; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Earlier power — Boomburst around Lv. 58:** 140 BP; STAB. Treat this as the curve target, not a fixed slot.

### Swoobat

**Type:** Psychic/Flying · **Final tier weight:** 1
**Role profile:** Atk 57 / Sp. Atk 87 / Spe 114 · Unaware, Klutz, Simple
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Synchronoise:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 8%; Tech Tutor (5 badges).*
- **Add — Psychic Fangs:** Its pronounced jaws or fangs give the unusual Psychic coverage a physical basis. *Precedent: TM; type-cohort prevalence 8%; Center Tutor (before Gym 7).*
- **Add — Fake Tears:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 5%; Tech Tutor (5 badges).*
- **Earlier power — Synchronoise around Lv. 51:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Sylveon

**Type:** Fairy · **Final tier weight:** 4
**Role profile:** Atk 65 / Sp. Atk 110 / Spe 60 · Cute Charm, Cute Charm, Pixilate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Hyper Voice:** Its voice, cry, song, or sound-based identity makes this natural level-up expression. *Precedent: level-up/TM/tutor; type-cohort prevalence 29%; no Center/Tech Tutor overlap.*
- **Earlier power — Hyper Voice around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Talonflame

**Type:** Fire/Flying · **Final tier weight:** 4
**Role profile:** Atk 81 / Sp. Atk 74 / Spe 126 · Flame Body, Gale Wings
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Wing Attack:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Earlier power — Wing Attack around Lv. 26:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Tangrowth

**Type:** Grass · **Final tier weight:** 5
**Role profile:** Atk 100 / Sp. Atk 110 / Spe 50 · Chlorophyll, Leaf Guard, Regenerator
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Tapu Bulu

**Type:** Grass/Fairy · **Final tier weight:** 3
**Role profile:** Atk 130 / Sp. Atk 85 / Spe 75 · Grassy Surge, Telepathy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Superpower:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/TM/tutor; type-cohort prevalence 12%; Center Tutor (League).*
- **Add — Darkest Lariat:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: TM; type-cohort prevalence 5%; Center Tutor (before Gym 7).*
- **Earlier power — Superpower around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Tapu Fini

**Type:** Water/Fairy · **Final tier weight:** 3
**Role profile:** Atk 75 / Sp. Atk 95 / Spe 85 · Misty Surge, Telepathy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Draining Kiss:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 7%; Center Tutor (before Gym 4).*
- **Add — Play Rough:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 7%; Center Tutor (before Gym 8).*
- **Earlier power — Play Rough around Lv. 58:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Tapu Koko

**Type:** Electric/Fairy · **Final tier weight:** 3
**Role profile:** Atk 115 / Sp. Atk 95 / Spe 130 · Electric Surge, Telepathy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Mirror Move:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Sky Attack:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: tutor; type-cohort prevalence 4%; Center Tutor (before Gym 7).*
- **Earlier power — Sky Attack around Lv. 56:** 140 BP; coverage. Treat this as the curve target, not a fixed slot.

### Tapu Lele

**Type:** Psychic/Fairy · **Final tier weight:** 3
**Role profile:** Atk 85 / Sp. Atk 130 / Spe 95 · Psychic Surge, Telepathy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Future Sight:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: TM; type-cohort prevalence 26%; Center Tutor (before Gym 7).*
- **Add — Dazzling Gleam:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: TM; type-cohort prevalence 42%; Center Tutor (before Gym 7).*
- **Earlier power — Future Sight around Lv. 58:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Tauros

**Type:** Normal · **Final tier weight:** 4
**Role profile:** Atk 100 / Sp. Atk 40 / Spe 110 · Intimidate, Anger Point, Sheer Force
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Stomp:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 17%; no Center/Tech Tutor overlap.*
- **Earlier power — Stomp around Lv. 33:** 65 BP; STAB. Treat this as the curve target, not a fixed slot.

### Tauros (Paldea Aqua)

**Type:** Fighting/Water · **Final tier weight:** 4
**Role profile:** Atk 110 / Sp. Atk 30 / Spe 100 · Intimidate, Anger Point, Cud Chew
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 18%; Center Tutor (before Gym 7).*
- **Earlier power — Body Press around Lv. 50:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Tauros (Paldea Blaze)

**Type:** Fighting/Fire · **Final tier weight:** 4
**Role profile:** Atk 110 / Sp. Atk 30 / Spe 100 · Intimidate, Anger Point, Cud Chew
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 19%; Center Tutor (before Gym 7).*
- **Earlier power — Body Press around Lv. 50:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Tauros (Paldea Combat)

**Type:** Fighting · **Final tier weight:** 4
**Role profile:** Atk 110 / Sp. Atk 30 / Spe 100 · Intimidate, Anger Point, Cud Chew
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 36%; Center Tutor (before Gym 7).*
- **Earlier power — Body Press around Lv. 50:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Tentacruel

**Type:** Water/Poison · **Final tier weight:** 3
**Role profile:** Atk 70 / Sp. Atk 80 / Spe 100 · Clear Body, Liquid Ooze, Rain Dish
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Brine:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/TM; type-cohort prevalence 12%; Center Tutor (before Gym 5).*
- **Add — Acid Spray:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/TM; type-cohort prevalence 10%; Center Tutor (before Gym 3).*
- **Earlier power — Brine around Lv. 33:** 65 BP; STAB. Treat this as the curve target, not a fixed slot.

### Terrakion

**Type:** Rock/Fighting · **Final tier weight:** 5
**Role profile:** Atk 129 / Sp. Atk 72 / Spe 108 · Justified
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Rock Throw:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Earlier power — Rock Throw around Lv. 22:** 50 BP; STAB. Treat this as the curve target, not a fixed slot.

### Thievul

**Type:** Dark · **Final tier weight:** 2
**Role profile:** Atk 58 / Sp. Atk 87 / Spe 90 · Run Away, Unburden, Stakeout
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Knock Off:** The thief motif is direct and the species is weak enough to merit early League-tutor access. *Precedent: level-up/egg/TM; type-cohort prevalence 69%; Center Tutor (League).*
- **Add — Howl:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg; type-cohort prevalence 6%; Center Tutor (before Gym 5).*
- **Earlier power — Knock Off around Lv. 28:** 65 BP; STAB. Treat this as the curve target, not a fixed slot.

### Throh

**Type:** Fighting · **Final tier weight:** 3
**Role profile:** Atk 100 / Sp. Atk 30 / Spe 45 · Guts, Inner Focus, Mold Breaker
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Dynamic Punch:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 33%; Tech Tutor (5 badges).*
- **Add — Brick Break:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 95%; no Center/Tech Tutor overlap.*
- **Earlier power — Dynamic Punch around Lv. 58:** 100 BP; STAB. Treat this as the curve target, not a fixed slot.

### Ting-Lu

**Type:** Dark/Ground · **Final tier weight:** 5
**Role profile:** Atk 110 / Sp. Atk 55 / Spe 45 · Vessel Of Ruin
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Tinkaton

**Type:** Fairy/Steel · **Final tier weight:** 4
**Role profile:** Atk 75 / Sp. Atk 70 / Spe 94 · Mold Breaker, Own Tempo, Pickpocket
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Ice Hammer:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Ice Hammer around Lv. 56:** 100 BP; coverage. Treat this as the curve target, not a fixed slot.

### Toedscruel

**Type:** Ground/Grass · **Final tier weight:** 3
**Role profile:** Atk 70 / Sp. Atk 80 / Spe 100 · Mycelium Might
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Rage Powder:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Rapid Spin:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 8%; Center Tutor (before Gym 5).*
- **Earlier power — Rapid Spin around Lv. 17:** 50 BP; coverage. Treat this as the curve target, not a fixed slot.

### Togedemaru

**Type:** Electric/Steel · **Final tier weight:** 4
**Role profile:** Atk 98 / Sp. Atk 40 / Spe 96 · Iron Barbs, Lightning Rod, Sturdy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Wish:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; Legacy Tutor.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Togekiss

**Type:** Fairy/Flying · **Final tier weight:** 5
**Role profile:** Atk 50 / Sp. Atk 120 / Spe 80 · Hustle, Serene Grace, Super Luck
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Extrasensory:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 8%; no Center/Tech Tutor overlap.*
- **Earlier power — Extrasensory around Lv. 51:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Torkoal

**Type:** Fire · **Final tier weight:** 3
**Role profile:** Atk 85 / Sp. Atk 85 / Spe 20 · White Smoke, Shell Armor, Drought
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Temper Flare:** A slow physical-capable fire tortoise can use the failure payoff without easy snowballing. *Precedent: TM; type-cohort prevalence 57%; no Center/Tech Tutor overlap.*
- **Add — Superpower:** Its established sound motif makes this a strong identity move. *Precedent: egg/TM/tutor; type-cohort prevalence 19%; Center Tutor (League).*
- **Earlier power — Superpower around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Torterra

**Type:** Grass/Ground · **Final tier weight:** 4
**Role profile:** Atk 109 / Sp. Atk 75 / Spe 56 · Overgrow, Shell Armor
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Grassy Terrain:** A bulky physical Grass/Ground setter has little role overlap with the special Grass/Poison setters. *Precedent: egg/TM; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Toucannon

**Type:** Normal/Flying · **Final tier weight:** 2
**Role profile:** Atk 120 / Sp. Atk 75 / Spe 60 · Keen Eye, Skill Link, Sheer Force
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Dual Wingbeat:** A physical bird with middling Speed gains natural Flying STAB without Brave Bird's ceiling. *Precedent: TM; type-cohort prevalence 9%; Center Tutor (before Gym 7).*
- **Add — Gunk Shot:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 8%; Center Tutor (before Gym 8).*
- **Earlier power — Gunk Shot around Lv. 52:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Toxapex

**Type:** Poison/Water · **Final tier weight:** 5
**Role profile:** Atk 63 / Sp. Atk 53 / Spe 35 · Merciless, Limber, Regenerator
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Toxicroak

**Type:** Poison/Fighting · **Final tier weight:** 3
**Role profile:** Atk 106 / Sp. Atk 86 / Spe 85 · Anticipation, Dry Skin, Poison Touch
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Wake Up Slap:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Cross Chop:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Cross Chop around Lv. 58:** 100 BP; STAB. Treat this as the curve target, not a fixed slot.

### Toxtricity (Amped)

**Type:** Electric/Poison · **Final tier weight:** 3
**Role profile:** Atk 98 / Sp. Atk 114 / Spe 75 · Punk Rock, Plus, Technician
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Venoshock:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/TM; type-cohort prevalence 6%; Center Tutor (before Gym 4).*
- **Add — Sludge Wave:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: TM; type-cohort prevalence 6%; Center Tutor (before Gym 8).*
- **Earlier power — Sludge Wave around Lv. 58:** 95 BP; STAB. Treat this as the curve target, not a fixed slot.

### Toxtricity (Low Key)

**Type:** Electric/Poison · **Final tier weight:** 3
**Role profile:** Atk 98 / Sp. Atk 114 / Spe 75 · Punk Rock, Minus, Technician
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Sludge Wave:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 6%; Center Tutor (before Gym 8).*
- **Add — Sludge Bomb:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Earlier power — Sludge Wave around Lv. 58:** 95 BP; STAB. Treat this as the curve target, not a fixed slot.

### Trevenant

**Type:** Ghost/Grass · **Final tier weight:** 3
**Role profile:** Atk 110 / Sp. Atk 65 / Spe 56 · Natural Cure, Frisk, Harvest
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Sucker Punch:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 23%; Legacy Tutor.*
- **Add — Trailblaze:** Its terrestrial movement and plant association support an active Grass attack rather than generic TM access. *Precedent: TM; type-cohort prevalence 16%; Center Tutor (before Gym 3).*
- **Earlier power — Sucker Punch around Lv. 34:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Tropius

**Type:** Grass/Flying · **Final tier weight:** 2
**Role profile:** Atk 68 / Sp. Atk 72 / Spe 51 · Chlorophyll, Solar Power, Harvest
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Dragon Dance:** Its low attack and speed leave room for a flavorful dragon-like dance. *Precedent: deliberate design exception; type-cohort prevalence 0%; Center Tutor (before Gym 8).*
- **Add — Dragon Hammer:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Leaf Blade:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 3%; Center Tutor (before Gym 8).*
- **Earlier power — Leaf Blade around Lv. 54:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Tsareena

**Type:** Grass · **Final tier weight:** 3
**Role profile:** Atk 120 / Sp. Atk 50 / Spe 72 · Leaf Guard, Queenly Majesty, Sweet Veil
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Play Rough:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 11%; Center Tutor (before Gym 8).*
- **Add — Punishment:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Play Rough around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Turtonator

**Type:** Fire/Dragon · **Final tier weight:** 3
**Role profile:** Atk 78 / Sp. Atk 91 / Spe 36 · Shell Armor
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Head Smash:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Add — Revenge:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: egg/TM; type-cohort prevalence 6%; Center Tutor (before Gym 6).*
- **Earlier power — Head Smash around Lv. 56:** 150 BP; coverage. Treat this as the curve target, not a fixed slot.

### Typhlosion

**Type:** Fire · **Final tier weight:** 4
**Role profile:** Atk 84 / Sp. Atk 109 / Spe 100 · Blaze, Flash Fire
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Submission:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 6%; Legacy Tutor.*
- **Earlier power — Submission around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Typhlosion (Hisui)

**Type:** Fire/Ghost · **Final tier weight:** 4
**Role profile:** Atk 84 / Sp. Atk 119 / Spe 95 · Blaze, Frisk
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Extrasensory:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 13%; no Center/Tech Tutor overlap.*
- **Earlier power — Extrasensory around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Tyranitar

**Type:** Rock/Dark · **Final tier weight:** 5
**Role profile:** Atk 134 / Sp. Atk 95 / Spe 61 · Sand Stream, Unnerve
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Assurance:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 19%; Tech Tutor (8 badges).*
- **Earlier power — Assurance around Lv. 29:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Tyrantrum

**Type:** Rock/Dragon · **Final tier weight:** 3
**Role profile:** Atk 121 / Sp. Atk 69 / Spe 71 · Strong Jaw, Rock Head
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Rock Throw:** Its jaw-based anatomy gives the coverage a concrete physical source. *Precedent: level-up/egg/TM; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Add — Poison Fang:** Its jaw-based anatomy gives the coverage a concrete physical source. *Precedent: egg/TM; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Rock Throw around Lv. 19:** 50 BP; STAB. Treat this as the curve target, not a fixed slot.

### Umbreon

**Type:** Dark · **Final tier weight:** 4
**Role profile:** Atk 65 / Sp. Atk 60 / Spe 65 · Synchronize, Synchronize, Inner Focus
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Synchronoise:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; Tech Tutor (5 badges).*
- **Earlier power — Synchronoise around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Unfezant

**Type:** Normal/Flying · **Final tier weight:** 3
**Role profile:** Atk 115 / Sp. Atk 65 / Spe 93 · Big Pecks, Super Luck, Rivalry
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Morning Sun:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg; type-cohort prevalence 3%; Legacy Tutor.*
- **Add — Steel Wing:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/TM; type-cohort prevalence 19%; no Center/Tech Tutor overlap.*
- **Compatibility gap — Acrobatics:** Verify or add TM/tutor compatibility rather than level-up access; Gen 9 greatly broadened Acrobatics among ordinary birds; Unfezant missed that pass.
- **Earlier power — Steel Wing around Lv. 34:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Ursaluna

**Type:** Ground/Normal · **Final tier weight:** 5
**Role profile:** Atk 140 / Sp. Atk 45 / Spe 50 · Guts, Bulletproof, Unnerve
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Double Edge:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 76%; no Center/Tech Tutor overlap.*
- **Earlier power — Double Edge around Lv. 61:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Ursaluna (Bloodmoon)

**Type:** Ground/Normal · **Final tier weight:** 5
**Role profile:** Atk 70 / Sp. Atk 135 / Spe 52 · Minds Eye
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Urshifu (Rapid Strike)

**Type:** Fighting/Water · **Final tier weight:** 3
**Role profile:** Atk 130 / Sp. Atk 63 / Spe 97 · Unseen Fist
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 18%; Center Tutor (before Gym 7).*
- **Add — Revenge:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: TM; type-cohort prevalence 6%; Center Tutor (before Gym 6).*
- **Earlier power — Body Press around Lv. 50:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Urshifu (Single Strike)

**Type:** Fighting/Dark · **Final tier weight:** 3
**Role profile:** Atk 130 / Sp. Atk 63 / Spe 97 · Unseen Fist
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 17%; Center Tutor (before Gym 7).*
- **Add — Foul Play:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 11%; Center Tutor (before Gym 8).*
- **Earlier power — Foul Play around Lv. 58:** 95 BP; STAB. Treat this as the curve target, not a fixed slot.

### Uxie

**Type:** Psychic · **Final tier weight:** 3
**Role profile:** Atk 75 / Sp. Atk 75 / Spe 95 · Levitate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Heal Bell:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: tutor; type-cohort prevalence 15%; Center Tutor (before Gym 5).*
- **Add — U Turn:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 18%; Center Tutor (League).*
- **Earlier power — U Turn around Lv. 34:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Vanilluxe

**Type:** Ice · **Final tier weight:** 2
**Role profile:** Atk 95 / Sp. Atk 110 / Spe 79 · Ice Body, Snow Warning, Weak Armor
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Explosion:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 14%; Center Tutor (before Gym 8).*
- **Add — Mirror Shot:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 3%; no Center/Tech Tutor overlap.*
- **Earlier power — Explosion around Lv. 52:** 250 BP; coverage. Treat this as the curve target, not a fixed slot.

### Vaporeon

**Type:** Water · **Final tier weight:** 4
**Role profile:** Atk 65 / Sp. Atk 110 / Spe 65 · Water Absorb, Water Absorb, Hydration
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Synchronoise:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; Tech Tutor (5 badges).*
- **Earlier power — Synchronoise around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Veluza

**Type:** Water/Psychic · **Final tier weight:** 3
**Role profile:** Atk 102 / Sp. Atk 78 / Spe 70 · Mold Breaker, Sharpness
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Recover:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 10%; no Center/Tech Tutor overlap.*
- **Add — Thrash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 9%; no Center/Tech Tutor overlap.*
- **Earlier power — Thrash around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Venomoth

**Type:** Bug/Poison · **Final tier weight:** 2
**Role profile:** Atk 65 / Sp. Atk 90 / Spe 90 · Shield Dust, Tinted Lens, Wonder Skin
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Signal Beam:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/tutor; type-cohort prevalence 12%; Center Tutor (before Gym 6).*
- **Add — Morning Sun:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; Legacy Tutor.*
- **Earlier power — Signal Beam around Lv. 38:** 75 BP; STAB. Treat this as the curve target, not a fixed slot.

### Venusaur

**Type:** Grass/Poison · **Final tier weight:** 4
**Role profile:** Atk 82 / Sp. Atk 100 / Spe 80 · Overgrow, Chlorophyll
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Leaf Storm:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 10%; Center Tutor (League).*
- **Earlier power — Leaf Storm around Lv. 58:** 130 BP; STAB. Treat this as the curve target, not a fixed slot.

### Vespiquen

**Type:** Bug/Flying · **Final tier weight:** 2
**Role profile:** Atk 80 / Sp. Atk 80 / Spe 40 · Pressure, Unnerve
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Recover:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 8%; no Center/Tech Tutor overlap.*
- **Add — Pollen Puff:** Its flower, pollen, or caregiving identity supports both the attack and ally-heal flavor. *Precedent: TM; type-cohort prevalence 5%; Center Tutor (before Gym 8).*
- **Earlier power — Pollen Puff around Lv. 54:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Victini

**Type:** Psychic/Fire · **Final tier weight:** 4
**Role profile:** Atk 100 / Sp. Atk 100 / Spe 100 · Victory Star
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Flame Burst:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 1%; no Center/Tech Tutor overlap.*
- **Earlier power — Flame Burst around Lv. 36:** 70 BP; STAB. Treat this as the curve target, not a fixed slot.

### Victreebel

**Type:** Grass/Poison · **Final tier weight:** 2
**Role profile:** Atk 105 / Sp. Atk 100 / Spe 70 · Chlorophyll, Gluttony
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Clear Smog:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Add — Leech Life:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 6%; Center Tutor (before Gym 7).*
- **Earlier power — Leech Life around Lv. 44:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Vikavolt

**Type:** Bug/Electric · **Final tier weight:** 3
**Role profile:** Atk 70 / Sp. Atk 145 / Spe 43 · Levitate
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Air Slash:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 6%; Center Tutor (before Gym 6).*
- **Add — Electroweb:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 28%; Center Tutor (before Gym 3).*
- **Earlier power — Air Slash around Lv. 40:** 75 BP; coverage. Treat this as the curve target, not a fixed slot.

### Vileplume

**Type:** Grass/Poison · **Final tier weight:** 3
**Role profile:** Atk 80 / Sp. Atk 110 / Spe 50 · Chlorophyll, Effect Spore
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Strength Sap:** Its draining or parasitic flavor supports a distinctive utility niche. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Add — Sludge Wave:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 8%; Center Tutor (before Gym 8).*
- **Earlier power — Sludge Wave around Lv. 58:** 95 BP; STAB. Treat this as the curve target, not a fixed slot.

### Virizion

**Type:** Grass/Fighting · **Final tier weight:** 3
**Role profile:** Atk 90 / Sp. Atk 90 / Spe 108 · Justified
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Aura Sphere:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 6%; Center Tutor (before Gym 7).*
- **Add — Horn Leech:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Aura Sphere around Lv. 50:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Volbeat

**Type:** Bug · **Final tier weight:** 2
**Role profile:** Atk 73 / Sp. Atk 47 / Spe 85 · Illuminate, Swarm, Prankster
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Dizzy Punch:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Add — Encore:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg/TM; type-cohort prevalence 13%; Center Tutor (before Gym 5).*
- **Earlier power — Dizzy Punch around Lv. 30:** 70 BP; coverage. Treat this as the curve target, not a fixed slot.

### Volcanion

**Type:** Fire/Water · **Final tier weight:** 4
**Role profile:** Atk 110 / Sp. Atk 130 / Spe 70 · Water Absorb
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Sludge Wave:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 6%; Center Tutor (before Gym 8).*
- **Earlier power — Sludge Wave around Lv. 56:** 95 BP; coverage. Treat this as the curve target, not a fixed slot.

### Volcarona

**Type:** Bug/Fire · **Final tier weight:** 5
**Role profile:** Atk 60 / Sp. Atk 135 / Spe 100 · Flame Body, Swarm
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Silver Wind:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power — Silver Wind around Lv. 29:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Wailord

**Type:** Water · **Final tier weight:** 2
**Role profile:** Atk 90 / Sp. Atk 90 / Spe 60 · Water Veil, Oblivious, Pressure
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Clear Smog:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Add — Thrash:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 12%; no Center/Tech Tutor overlap.*
- **Earlier power — Thrash around Lv. 52:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Walking Wake

**Type:** Water/Dragon · **Final tier weight:** 3
**Role profile:** Atk 83 / Sp. Atk 125 / Spe 109 · Protosynthesis
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Draco Meteor:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 5%; Center Tutor (League).*
- **Add — Weather Ball:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 32%; Center Tutor (before Gym 7).*
- **Earlier power — Draco Meteor around Lv. 58:** 130 BP; STAB. Treat this as the curve target, not a fixed slot.

### Walrein

**Type:** Ice/Water · **Final tier weight:** 3
**Role profile:** Atk 80 / Sp. Atk 95 / Spe 65 · Thick Fat, Ice Body, Oblivious
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Water Pulse:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 54%; Center Tutor (before Gym 4).*
- **Add — Signal Beam:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/tutor; type-cohort prevalence 32%; Center Tutor (before Gym 6).*
- **Earlier power — Signal Beam around Lv. 40:** 75 BP; coverage. Treat this as the curve target, not a fixed slot.

### Watchog

**Type:** Normal · **Final tier weight:** 1
**Role profile:** Atk 85 / Sp. Atk 60 / Spe 77 · Illuminate, Keen Eye, Analytic
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Knock Off:** A low-tier sentry with grasping limbs can support through disruption. *Precedent: tutor; type-cohort prevalence 41%; Center Tutor (League).*
- **Add — Iron Tail:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 47%; Center Tutor (before Gym 7).*
- **Add — Double Edge:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 77%; no Center/Tech Tutor overlap.*
- **Compatibility gap — Lash Out:** Verify or add TM/tutor compatibility rather than level-up access; a low-tier physical sentry can reasonably share the broad retaliation tutor.
- **Earlier power — Double Edge around Lv. 51:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Weavile

**Type:** Dark/Ice · **Final tier weight:** 4
**Role profile:** Atk 120 / Sp. Atk 45 / Spe 125 · Pressure, Pickpocket
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Punishment:** Its armored or mineral body plan makes the move read as anatomy, not arbitrary coverage. *Precedent: level-up/egg; type-cohort prevalence 3%; no Center/Tech Tutor overlap.*
- **Earlier setup — Nasty Plot around Lv. 38:** Move it forward from Lv. 48; its low Sp. Atk makes the special setup a creative sidegrade. Do not pair this access with Baton Pass.
- **Earlier power — Punishment around Lv. 26:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Weezing

**Type:** Poison · **Final tier weight:** 3
**Role profile:** Atk 90 / Sp. Atk 85 / Spe 60 · Levitate, Neutralizing Gas, Stench
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Psybeam:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 17%; Center Tutor (before Gym 4).*
- **Add — Screech:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg/TM; type-cohort prevalence 44%; Tech Tutor (5 badges).*
- **Earlier power — Psybeam around Lv. 31:** 65 BP; coverage. Treat this as the curve target, not a fixed slot.

### Weezing (Galar)

**Type:** Poison/Fairy · **Final tier weight:** 3
**Role profile:** Atk 90 / Sp. Atk 85 / Spe 60 · Levitate, Neutralizing Gas, Misty Surge
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Misty Explosion:** Its Fairy typing, gas body, and Misty Surge option unite every part of the move. *Precedent: TM/tutor; type-cohort prevalence 2%; Center Tutor (before Gym 6).*
- **Add — Sludge Wave:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 3%; Center Tutor (before Gym 8).*
- **Earlier power — Misty Explosion around Lv. 42:** 100 BP; STAB. Treat this as the curve target, not a fixed slot.

### Whimsicott

**Type:** Grass/Fairy · **Final tier weight:** 4
**Role profile:** Atk 67 / Sp. Atk 77 / Spe 116 · Prankster, Infiltrator, Chlorophyll
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Misty Terrain:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 2%; Tech Tutor (3 badges).*
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Whiscash

**Type:** Water/Ground · **Final tier weight:** 2
**Role profile:** Atk 78 / Sp. Atk 76 / Spe 60 · Oblivious, Anticipation, Hydration
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Earth Power:** Its mud-dwelling identity and mixed offenses support a special Ground route. *Precedent: level-up/egg/TM/tutor; type-cohort prevalence 21%; Center Tutor (before Gym 8).*
- **Add — Hydro Pump:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM; type-cohort prevalence 14%; no Center/Tech Tutor overlap.*
- **Earlier power — Hydro Pump around Lv. 54:** 110 BP; STAB. Treat this as the curve target, not a fixed slot.

### Wo-Chien

**Type:** Dark/Grass · **Final tier weight:** 4
**Role profile:** Atk 85 / Sp. Atk 95 / Spe 70 · Tablets Of Ruin
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Pollen Puff:** Its flower, pollen, or caregiving identity supports both the attack and ally-heal flavor. *Precedent: TM; type-cohort prevalence 6%; Center Tutor (before Gym 8).*
- **Earlier power — Pollen Puff around Lv. 56:** 90 BP; coverage. Treat this as the curve target, not a fixed slot.

### Wobbuffet

**Type:** Psychic · **Final tier weight:** 3
**Role profile:** Atk 33 / Sp. Atk 33 / Spe 33 · Shadow Tag, Telepathy
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Wormadam (Plant)

**Type:** Bug/Grass · **Final tier weight:** 3
**Role profile:** Atk 59 / Sp. Atk 79 / Spe 36 · Anticipation, Overcoat
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Struggle Bug:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/TM; type-cohort prevalence 5%; Center Tutor (before Gym 2).*
- **Add — Silver Wind:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 9%; no Center/Tech Tutor overlap.*
- **Earlier power — Silver Wind around Lv. 26:** 60 BP; STAB. Treat this as the curve target, not a fixed slot.

### Wormadam (Sandy)

**Type:** Bug/Ground · **Final tier weight:** 3
**Role profile:** Atk 79 / Sp. Atk 59 / Spe 36 · Anticipation, Overcoat
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Earth Power:** The sandy cloak supplies direct flavor and its special offense is not negligible. *Precedent: level-up/tutor; type-cohort prevalence 11%; Center Tutor (before Gym 8).*
- **Add — Silver Wind:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 5%; no Center/Tech Tutor overlap.*
- **Earlier power — Earth Power around Lv. 34:** 90 BP; STAB. Treat this as the curve target, not a fixed slot.

### Wormadam (Trash)

**Type:** Bug/Steel · **Final tier weight:** 3
**Role profile:** Atk 69 / Sp. Atk 69 / Spe 36 · Anticipation, Overcoat
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet absent

- **Add — Skitter Smack:** Its low tier and physical cloak attacks make the debuffing Bug move safe. *Precedent: deliberate design exception; type-cohort prevalence 10%; Center Tutor (before Gym 6).*
- **Add — Silver Wind:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 4%; no Center/Tech Tutor overlap.*
- **Earlier power — Skitter Smack around Lv. 30:** 70 BP; STAB. Treat this as the curve target, not a fixed slot.

### Wugtrio

**Type:** Water · **Final tier weight:** 2
**Role profile:** Atk 100 / Sp. Atk 50 / Spe 120 · Gooey, Rattled, Sand Veil
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Flip Turn:** Its low tier and aquatic ambush style leave room for early pivot access. *Precedent: deliberate design exception; type-cohort prevalence 44%; Center Tutor (League).*
- **Add — Foul Play:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 5%; Center Tutor (before Gym 8).*
- **Earlier power — Foul Play around Lv. 52:** 95 BP; coverage. Treat this as the curve target, not a fixed slot.

### Wyrdeer

**Type:** Normal/Psychic · **Final tier weight:** 2
**Role profile:** Atk 105 / Sp. Atk 105 / Spe 65 · Intimidate, Frisk, Sap Sipper
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Extrasensory:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 11%; no Center/Tech Tutor overlap.*
- **Add — Confusion:** Restoring historical natural access preserves established species flavor. *Precedent: level-up; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Earlier power — Extrasensory around Lv. 46:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Xatu

**Type:** Psychic/Flying · **Final tier weight:** 2
**Role profile:** Atk 75 / Sp. Atk 95 / Spe 95 · Synchronize, Early Bird, Magic Bounce
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Synchronoise:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 8%; Tech Tutor (5 badges).*
- **Add — Drill Peck:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 2%; no Center/Tech Tutor overlap.*
- **Earlier power — Synchronoise around Lv. 54:** 120 BP; STAB. Treat this as the curve target, not a fixed slot.

### Xurkitree

**Type:** Electric · **Final tier weight:** 4
**Role profile:** Atk 89 / Sp. Atk 173 / Spe 83 · Beast Boost
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Signal Beam:** Restoring historical natural access preserves established species flavor. *Precedent: level-up/tutor; type-cohort prevalence 56%; Center Tutor (before Gym 6).*
- **Earlier power — Signal Beam around Lv. 40:** 75 BP; coverage. Treat this as the curve target, not a fixed slot.

### Yanmega

**Type:** Bug/Flying · **Final tier weight:** 3
**Role profile:** Atk 76 / Sp. Atk 116 / Spe 95 · Speed Boost, Tinted Lens, Frisk
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Silver Wind:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/egg/TM; type-cohort prevalence 22%; no Center/Tech Tutor overlap.*
- **Add — Signal Beam:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: egg/tutor; type-cohort prevalence 26%; Center Tutor (before Gym 6).*
- **Earlier power — Signal Beam around Lv. 42:** 75 BP; STAB. Treat this as the curve target, not a fixed slot.

### Yveltal

**Type:** Dark/Flying · **Final tier weight:** 3
**Role profile:** Atk 131 / Sp. Atk 131 / Spe 99 · Dark Aura
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add — Razor Wind:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: level-up/TM; type-cohort prevalence 13%; no Center/Tech Tutor overlap.*
- **Add — Sky Drop:** Its aerial anatomy makes this a visible extension of how it already fights. *Precedent: TM; type-cohort prevalence 2%; Center Tutor (before Gym 3).*
- **Earlier power — Razor Wind around Lv. 50:** 80 BP; STAB. Treat this as the curve target, not a fixed slot.

### Zangoose

**Type:** Normal · **Final tier weight:** 4
**Role profile:** Atk 115 / Sp. Atk 60 / Spe 90 · Immunity, Toxic Boost
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Iron Tail:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg/TM/tutor; type-cohort prevalence 47%; Center Tutor (before Gym 7).*
- **Earlier power — Iron Tail around Lv. 56:** 100 BP; coverage. Treat this as the curve target, not a fixed slot.

### Zapdos

**Type:** Electric/Flying · **Final tier weight:** 5
**Role profile:** Atk 90 / Sp. Atk 125 / Spe 100 · Pressure, Static
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Zapdos (Galar)

**Type:** Fighting/Flying · **Final tier weight:** 5
**Role profile:** Atk 125 / Sp. Atk 85 / Spe 100 · Defiant
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Zarude

**Type:** Dark/Grass · **Final tier weight:** 4
**Role profile:** Atk 120 / Sp. Atk 70 / Spe 105 · Leaf Guard
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Solar Blade:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 6%; Center Tutor (before Gym 8).*
- **Earlier power — Solar Blade around Lv. 58:** 125 BP; STAB. Treat this as the curve target, not a fixed slot.

### Zebstrika

**Type:** Electric · **Final tier weight:** 3
**Role profile:** Atk 100 / Sp. Atk 80 / Spe 116 · Lightning Rod, Motor Drive, Sap Sipper
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — High Horsepower:** Equine anatomy and 100 Attack make this coverage both legible and useful. *Precedent: TM; type-cohort prevalence 8%; Center Tutor (before Gym 8).*
- **Add — Double Edge:** Its established sound motif makes this a strong identity move. *Precedent: egg/TM; type-cohort prevalence 44%; no Center/Tech Tutor overlap.*
- **Earlier power — Double Edge around Lv. 56:** 120 BP; coverage. Treat this as the curve target, not a fixed slot.

### Zekrom

**Type:** Dragon/Electric · **Final tier weight:** 3
**Role profile:** Atk 150 / Sp. Atk 120 / Spe 90 · Teravolt
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Body Press:** Its armor, shell, mass, or defensive body plan makes Defense-based offense expressive. *Precedent: TM; type-cohort prevalence 18%; Center Tutor (before Gym 7).*
- **Add — Electric Terrain:** Historical compatibility supplies precedent; level-up access would turn that quiet trait into a visible niche. *Precedent: TM; type-cohort prevalence 6%; no Center/Tech Tutor overlap.*
- **Earlier power — Body Press around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Zeraora

**Type:** Electric · **Final tier weight:** 5
**Role profile:** Atk 112 / Sp. Atk 102 / Spe 143 · Volt Absorb
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet absent

- **Add:** No priority addition. Already powerful/distinctive enough; prefer rearranging its current natural moves before expanding coverage.
- **Earlier power:** No special acceleration proposed; preserve the ordinary STAB curve or use a current move as the bridge.

### Zoroark

**Type:** Dark · **Final tier weight:** 4
**Role profile:** Atk 105 / Sp. Atk 120 / Spe 105 · Illusion
**Modern-game datasets:** Sword/Shield present · Scarlet/Violet present

- **Add — Extrasensory:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: egg; type-cohort prevalence 8%; no Center/Tech Tutor overlap.*
- **Earlier power — Extrasensory around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

### Zoroark (Hisui)

**Type:** Normal/Ghost · **Final tier weight:** 4
**Role profile:** Atk 100 / Sp. Atk 125 / Spe 110 · Illusion
**Modern-game datasets:** Sword/Shield absent · Scarlet/Violet present

- **Add — Extrasensory:** Promoting a historical egg move makes lineage flavor visible during an ordinary playthrough. *Precedent: level-up/egg; type-cohort prevalence 11%; no Center/Tech Tutor overlap.*
- **Earlier power — Extrasensory around Lv. 48:** 80 BP; coverage. Treat this as the curve target, not a fixed slot.

## Follow-up review checklist

1. Confirm each proposed level against the earliest obtainable/evolution level and important boss ownership.
2. Recheck final tier values for ability-dependent species and any tier document/source drift.
3. Reject coverage whose only support is a one-off legacy TM if anatomy or Pokédex text does not independently support it.
4. Audit every accepted setup move together with Speed, relevant offense, priority, Baton Pass access, and alternative boosting moves.
5. Re-run this workbook after `gen_9.h` leaves WIP status; many `no priority` calls may simply reflect already-expanded local learnsets.

## Research sources

- Repository species descriptions and stats: `src/data/pokemon/species_info/`.
- Current level-up sets: `src/data/pokemon/level_up_learnsets/gen_9.h`.
- Historical learnsets: `tools/learnset_helpers/porymoves_files/`.
- Current tutor timing: `src/data/pokemon/center_tutor_moves.h`.
- Tier policy: `docs/gameplay/tier-points.md` and `GetMonTierPoints`.
- External flavor cross-check: [PokéAPI species flavor-text documentation](https://pokeapi.github.io/pokeapi.co/v2/) and [Bulbapedia species biology/learnset pages](https://bulbapedia.bulbagarden.net/wiki/Pok%C3%A9mon). These are secondary checks; no external text is copied into this document.
