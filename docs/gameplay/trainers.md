
# Elastic Emerald — Trainer Documentation

-  Any specified EVs apply only to EV mode. 
- There are some additional information such as some select AI notes for particular fights. 
	- Note that unlike in vanilla Emerald, the best damaging move gets a +1 score, so moves with a +1 score usually will tie with the best damaging move.

The following tags are used to automate trainer data from source code, while the rest of the text is inputted manually:
```text
<!-- trainer-party:start id=SOURCE_ID -->
...generated trainer items, healing policy, and party data...
<!-- trainer-party:end -->
```

When Brendan and May records intentionally share a party, both are tracked and
the sync fails if they diverge:
```text
<!-- trainer-party:start ids=SOURCE_ID_1,SOURCE_ID_2 -->
...generated shared trainer items, healing policy, and party data...
<!-- trainer-party:end -->
```

---

## Route 103

### Route 103 Rival (Torchic Team) — *Mandatory*
<!-- trainer-party:start ids=TRAINER_BRENDAN_ROUTE_103_TREECKO,TRAINER_MAY_ROUTE_103_TREECKO -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Torchic**
- **Gender:** Trainer default
- **Ability:** Blaze
- **Nature:** Serious
- **Level:** 5
- **IVs:** 3 HP / 3 Atk / 3 Def / 3 SpA / 3 SpD / 3 Spe
- **Moves:**
  - Scratch
  - Growl
<!-- trainer-party:end -->

> This team is used if the player chooses **Treecko** as starter, or the player chooses Mono **Normal, Grass, Dark, Bug, Ice, or Steel**.

---

### Route 103 Rival (Mudkip Team)
<!-- trainer-party:start ids=TRAINER_BRENDAN_ROUTE_103_TORCHIC,TRAINER_MAY_ROUTE_103_TORCHIC -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Mudkip**
- **Gender:** Trainer default
- **Ability:** Torrent
- **Nature:** Serious
- **Level:** 5
- **IVs:** 0 HP / 0 Atk / 0 Def / 0 SpA / 0 SpD / 0 Spe
- **Moves:**
  - Tackle
  - Growl
<!-- trainer-party:end -->

> This team is used if the player chooses **Torchic** as starter, or the player chooses Mono **Flying, Poison, Rock, Ghost, Fire, or Fairy**.

---

### Rival (Treecko Team)
<!-- trainer-party:start ids=TRAINER_BRENDAN_ROUTE_103_MUDKIP,TRAINER_MAY_ROUTE_103_MUDKIP -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Treecko**
- **Gender:** Trainer default
- **Ability:** Overgrow
- **Nature:** Serious
- **Level:** 5
- **IVs:** 3 HP / 3 Atk / 3 Def / 3 SpA / 3 SpD / 3 Spe
- **Moves:**
  - Quick Attack
  - Leer
<!-- trainer-party:end -->

> This team is used if the player chooses **Mudkip** as starter, or the player chooses Mono **Water, Ground, Electric, Psychic, Dragon, or Fighting**.

---

## Route 102

### Youngster Calvin — *Mandatory*
<!-- trainer-party:start id=TRAINER_CALVIN_1 -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Shinx**
- **Gender:** Male
- **Ability:** Rivalry
- **Level:** 4
- **Nature:** Careful
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Thunder Shock
  - Fake Tears
  - Mud-Slap
  - Quick Attack

**Litleo**
- **Gender:** Female
- **Ability:** Rivalry
- **Level:** 5
- **Nature:** Adamant
- **IVs:** 10 HP / 20 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Ember
  - Tackle
  - Leer
  - Entrainment
<!-- trainer-party:end -->

**AI Notes:**  
- Entrainment is incentivized if the target has a non-Rivalry ability and is of the opposite gender of the Entrainment mon.  
- Odds of using Entrainment over the ordinary best attacking move is about **75%** when the target can't faint the AI mon.

---

### Bug Catcher Rick — *Mandatory*
<!-- trainer-party:start id=TRAINER_RICK -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Surskit** @ Aguav Berry
- **Gender:** Male
- **Ability:** Swift Swim
- **Level:** 5
- **Nature:** Bashful
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Soak
  - Bubble
  - Quick Attack
  - Mist

**Venonat** @ Wide Lens
- **Gender:** Male
- **Ability:** Tinted Lens
- **Level:** 6
- **Nature:** Quiet
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Stun Spore
  - Pounce
  - Poison Powder
  - Supersonic
<!-- trainer-party:end -->

**AI notes:**  
- Soak incentives will not occur if the AI mon can 2KO or the target can KO.  
- Soak will get **+1 score** if AI mon doesn't have a SE move against the target.  
- Mist has a **50% chance** of +1 if the AI mon can't 2KO and the target can't KO.

---

### Youngster Allen — *Optional*
<!-- trainer-party:start id=TRAINER_ALLEN -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Zigzagoon** @ Ganlon Berry
- **Gender:** Male
- **Ability:** Gluttony
- **Level:** 5
- **Nature:** Impish
- **IVs:** 8 HP / 8 Atk / 8 Def / 8 SpA / 8 SpD / 8 Spe
- **Moves:**
  - Sand Attack
  - Tackle
  - Tail Whip
  - Growl

**Taillow** @ Lansat Berry
- **Gender:** Male
- **Ability:** Guts
- **Level:** 6
- **Nature:** Careful
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Peck
  - Quick Attack
  - Focus Energy
  - Growl
<!-- trainer-party:end -->

---

### Lass Tiana — *Mandatory*
<!-- trainer-party:start id=TRAINER_TIANA -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Flabebe** @ Oran Berry
- **Gender:** Female
- **Ability:** Flower Veil
- **Level:** 7
- **EVs:** 8 SpD / 16 Spe
- **Nature:** Bold
- **IVs:** 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- **Moves:**
  - Camouflage
  - Magical Leaf
  - Fairy Wind
  - Chilling Water

**Tangela** @ Rocky Helmet
- **Gender:** Female
- **Ability:** Regenerator
- **Level:** 8
- **EVs:** 20 HP / 20 Def / 20 Spe
- **Nature:** Adamant
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 20 SpD / 15 Spe
- **Moves:**
  - Rage
  - Rest
  - Synthesis
  - Amnesia
<!-- trainer-party:end -->

**AI notes:**  
- **Camouflage** context:
  - Tiana is guaranteed to be fought on a grass patch so Camouflage considers whether it's worthwhile to turn **Grass**.  
  - Camouflage will **not** be incentivized if the AI mon can 2KO the target, the Camouflaged type is weak to the target's STABs, or the current AI type resists all of the target's STABs.  
  - If not disincentivized: there's a **50% chance** to get +1 score; Camouflage gets +1 when AI mon will turn into Grass and has Flower Veil; it will get another +1 if Camouflage gives it STAB on a supereffective move.
- **Tangela / Amnesia**:
  - Because Tangela has 3 status moves and Rocky Helmet, **Amnesia** gets **+2 score** when Tangela's Sp.Def stage is less than 2.  
  - If the target has revealed a **-2 Sp.Def** move, there's a **50% chance** to ignore all Amnesia incentives and also get **-1 score**.

---

## Route 104 (Before Petalburg Woods)

### Beauty Ayumu — *Branched Mandatory / Optional*
<!-- trainer-party:start id=TRAINER_AYUMU -->
**Battle type:** Singles.

**Pre-battle healing:** Status conditions only (Casteliacone).

**Skitty** @ Oran Berry
- **Gender:** Female
- **Ability:** Cute Charm
- **Level:** 8
- **Nature:** Calm
- **IVs:** 10 HP / 4 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Charm
  - Fake Tears
  - Water Pulse
  - Attract

**Stufful** @ Rawst Berry
- **Gender:** Male
- **Ability:** Cute Charm
- **Level:** 8
- **EVs:** 12 Def / 12 SpD / 12 Spe
- **Nature:** Impish
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Attract
  - Baby-Doll Eyes
  - Confide
  - Tackle
<!-- trainer-party:end -->

**Mechanics Note:** Charm, Fake Tears, Baby-Doll Eyes, and Confide debuff by an additional stat stage if the mon has Cute Charm and the target is applicable to be infatuated.

---

### Youngster Billy — *Optional, Reward*
<!-- trainer-party:start id=TRAINER_BILLY -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Meowth-Galar** @ Throat Spray
- **Gender:** Male
- **Ability:** Pickup
- **Level:** 7
- **EVs:** 20 HP / 36 Def
- **IVs:** 10 HP / 31 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Nature:** Serious
- **Moves:**
  - Metal Sound
  - Round
  - Metal Claw
  - Growl

**Tyrogue** @ Flame Orb
- **Gender:** Male
- **Ability:** Guts
- **Level:** 8
- **EVs:** 24 HP / 24 Def / 24 SpD
- **IVs:** 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- **Nature:** Naughty
- **Moves:**
  - Fake Out
  - Bullet Punch
  - Mach Punch
  - Rapid Spin
<!-- trainer-party:end -->

**AI Notes:**  
- Sound moves have a **+1 score** while AI mon has Throat Spray.  
- Metal Sound's incentives for Sp.Def dropping do not apply if all the mon's moves of that split are ineffective (e.g., against a Ghost type since Round is the only Special move).

**Reward Notes:**  
- If Billy is defeated **before** beating Woods Aqua Grunt, he gives a **Naughty Mint**.  
- If beaten **after**, he gives a **Serious Mint**.

---

### Fisherman Darian — *Optional*
<!-- trainer-party:start id=TRAINER_DARIAN -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Magikarp**
- **Gender:** Male
- **Level:** 9
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
<!-- trainer-party:end -->

---

### Schoolkid Jimmy — *Branched Mandatory / Optional*
**Item note:** Jimmy is guarding the hidden **Ability Patch**.
<!-- trainer-party:start id=TRAINER_JIMMY -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Ekans** @ Chesto Berry
- **Gender:** Male
- **Ability:** Shed Skin
- **Level:** 8
- **Nature:** Quirky
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **EVs:** 8 Def
- **Moves:**
  - Rest
  - Trailblaze
  - Mud Bomb
  - Poison Sting

**Sandshrew** @ Normal Gem
- **Gender:** Male
- **Ability:** Sand Veil
- **Level:** 9
- **Nature:** Jolly
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **EVs:** 8 HP
- **Moves:**
  - Fury Swipes
  - Bulldoze
  - Sandstorm
  - Metal Claw
<!-- trainer-party:end -->

---

### Lady Cindy 1 — *Optional, Rematchable*
- Lady Cindy is intended to be an easy source of money. Happy Hour and Pay Day have been made to apply to the winner, so her uses of these moves increase the player's money if they win the battle.
- Cindy's teams increase by 3 levels after beating Roxanne and by another 4 levels after beating Brawly.
- Cindy's money yield is `200 * total sum of Pokemon levels; multiply by 2 once Happy Hour is used.` Not factoring any Pay Day boosts, this puts her first team at 9,600 with Happy Hour.  to start and 18,000 post-Brawly.
<!-- trainer-party:start id=TRAINER_CINDY_1 -->
**Items:** Full Restore

**Battle type:** Singles.

**Pre-battle healing:** Complete heal.

**Meowth** @ Oran Berry
- **Gender:** Female
- **Ability:** Pickup
- **Level:** 8
- **EVs:** 32 Def
- **Nature:** Timid
- **IVs:** 10 HP / 5 Atk / 10 Def / 5 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Happy Hour
  - Pay Day

**Combee** @ Honey
- **Gender:** Male
- **Ability:** Honey Gather
- **Level:** 8
- **Nature:** Jolly
- **IVs:** 10 HP / 2 Atk / 10 Def / 2 SpA / 10 SpD / 10 Spe
- **EVs:** 16 Spe
- **Moves:**
  - Gust
  - Bug Bite

**Gimmighoul** @ Amulet Coin
- **Gender:** Genderless
- **Level:** 8
- **Ability:** Rattled
- **Nature:** Bold
- **IVs:** 10 HP / 2 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Pay Day
  - Thief
<!-- trainer-party:end -->

**Mechanics Notes:**  
- Happy Hour and Pay Day are reciprocal and apply to the **winner** rather than only if the user won the battle.

**AI Notes:**  
- Happy Hour has a **+2 score** before Happy Hour has been used.

---

## Petalburg Woods

### Bug Catcher Lyle — *Optional*
- Although Lyle is optional, it's required to fight Route Boss Aurelio
- If Collector Darren has been defeated, Lyle's Pokemon increase by 2 levels (for Route Boss level scaling).
<!-- trainer-party:start id=TRAINER_LYLE -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Cascoon** @ Poison Barb
- **Gender:** Male
- **Ability:** Shed Skin
- **Level:** 7
- **EVs:** 20 HP / 20 SpD
- **Nature:** Adamant
- **IVs:** 8 HP / 31 Atk / 8 Def / 8 SpA / 8 SpD / 8 Spe
- **Moves:**
  - Tackle
  - String Shot
  - Harden
  - Poison Sting

**Joltik** @ Miracle Seed
- **Gender:** Male
- **Ability:** Compound Eyes
- **Level:** 8
- **EVs:** 20 HP / 20 Def / 20 SpD
- **IVs:** 8 HP / 31 Atk / 8 Def / 8 SpA / 8 SpD / 8 Spe
- **Moves:**
  - Electroweb
  - Pounce
  - Absorb

**Cutiefly** @ Fairy Gem
- **Gender:** Male
- **Ability:** Honey Gather
- **Level:** 9
- **EVs:** 40 HP
- **Nature:** Calm
- **IVs:** 10 HP / 31 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Powder
  - Fairy Wind
  - Absorb
  - Covet
<!-- trainer-party:end -->

---

### Petalburg Woods Aqua Grunt — *Mandatory*
<!-- trainer-party:start id=TRAINER_GRUNT_PETALBURG_WOODS -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Chewtle** @ Apicot Berry
- **Gender:** Male
- **Ability:** Shell Armor
- **Level:** 10
- **EVs:** 4 SpD
- **Nature:** Sassy
- **IVs:** 12 HP / 31 Atk / 12 Def / 12 SpA / 12 SpD / 0 Spe
- **Moves:**
  - Tackle
  - Chilling Water
  - Bite
  - Scary Face

**Tadbulb** @ Luminous Moss
- **Gender:** Male
- **Ability:** Static
- **Level:** 11
- **EVs:** 24 Def
- **Nature:** Calm
- **IVs:** 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- **Moves:**
  - Soak
  - Water Pulse
  - Thunder Shock
  - Mud-Slap
<!-- trainer-party:end -->

**AI Notes:**  
- Soak incentives will not occur if the AI mon can 2KO or the target can KO.  
- Because Tadbulb has **Soak + Thunder Shock**, it will get **+2 score** on Soak, but in cases where Tadbulb can 3KO, or Tadbulb has used Soak 2 or 3 turns ago, the **+2 score** only has a **50% chance** of occurring.

---

### Youngster James — *Optional*
- While Youngster James is optional, it's required to fight Route Boss Aurelio
- If Collector Darren has been defeated, James' Pokemon increase by 2 levels (for Route Boss level-scaling)
<!-- trainer-party:start id=TRAINER_JAMES_1 -->
**Battle type:** Singles.

**Additional AI flags:** Force Setup First Turn.

**Pre-battle healing:** None.

**Zigzagoon** @ Ring Target
- **Gender:** Male
- **Ability:** Quick Feet
- **Level:** 9
- **EVs:** 12 HP / 16 Spe
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Trick
  - Headbutt
  - Mud Shot
  - Shock Wave

**Impidimp** @ Mirror Herb
- **Gender:** Male
- **Ability:** Prankster
- **Level:** 10
- **EVs:** 32 Spe
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 12 Spe
- **Moves:**
  - Flatter
  - Punishment
  - Confusion
  - Round
<!-- trainer-party:end -->

**AI Notes:**  
- Force Setup First Turn flag: Zigzagoon gets **+1** to using **Trick** on the first turn while holding Ring Target. Trick + Ring Target also has an additional **+1** when the target has a held item.  
- **Flatter** has **+1** while the AI mon is holding Mirror Herb. Flatter gets an additional **+1** while AI mon has Punishment. Regular confusion logic to increase by +1 also occurs **20%** of the time.

---

### Cooltrainer Aurelio — *Optional Route Boss with rewards*
- **Battle Notes:** Requires beating **Youngster James** and **Bug Catcher Lyle** to fight.
- If Collector Darren has been defeated, Aurelio's Pokemon increase by 2 levels (for level scaling).
- In Restricted Mode, Aurelio can no longer be fought after beating Roxanne, to bound its Route Boss reward.
- **Reward Notes:**  
	- 1 Jaboca Berry and 1 Rowap Berry in non-Resource Mode;  
	- 3 Jaboca Berries and 3 Rowap Berries in Resource Mode.

<!-- trainer-party:start id=TRAINER_AURELIO -->
**Battle type:** Singles.

**Pre-battle healing:** Complete heal (route boss override).

**Clefairy** @ Sticky Barb
- **Gender:** Female
- **Ability:** Magic Guard
- **Level:** 10
- **EVs:** 32 HP / 8 Def / 32 SpA
- **Nature:** Bold
- **IVs:** 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- **Moves:**
  - Trick
  - Echoed Voice
  - Charm
  - Disarming Voice

**Shroodle** @ Jaboca Berry
- **Gender:** Male
- **Ability:** Pickpocket
- **Level:** 11
- **EVs:** 32 HP / 32 Spe
- **Nature:** Serious
- **IVs:** 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- **Moves:**
  - Poison Fang
  - Mud Shot
  - Leer
  - Super Fang

**Applin** @ Rowap Berry
- **Gender:** Male
- **Ability:** Ripen
- **Level:** 12
- **EVs:** 20 HP / 28 Def / 20 SpD
- **Nature:** Impish
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Recycle
  - Defense Curl
  - Rollout
  - Grassy Glide
<!-- trainer-party:end -->

**AI Notes:**  
- **Trick + Sticky Barb** has a **+2 score**. However, if the target mon is faster, has no held item, and is expected to use a contact move, Trick only has a **22% chance** to get +1 score, and the other 78% of the time, it gets a -2 score.
- If Trick was used the previous turn, there is a **50% chance** to skip all Trick incentives.
- Trick is highly disincentivized if the player mon is holding a Mail.
- If Echoed Voice is not the highest damaging move, the Pokemon is not Tormented, and the Pokemon cannot 2KO the target, Echoed Voice gets a +1 score.



---

## Route 104 (After Petalburg Woods)

### Rich Boy Winston — *Optional*
<!-- trainer-party:start id=TRAINER_WINSTON_1 -->
**Items:** Full Restore

**Battle type:** Singles.

**Pre-battle healing:** Complete heal.

**Bonsly** @ Rindo Berry
- **Gender:** Male
- **Ability:** Sturdy
- **Level:** 10
- **EVs:** 8 HP / 16 SpA / 16 Spe
- **Nature:** Quiet
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Natural Gift
  - Power Gem
  - Low Kick
  - Tearful Look
<!-- trainer-party:end -->

**AI Notes:**  
- Tearful Look has various checks to determine whether AI should lower either Atk or Sp.Def. If these checks are met while AI has a heal item, Tearful Look gets **+1 score**, and a blanket **50% chance** of getting another **+1 score**.

---

### Lass Haley — *Optional*
<!-- trainer-party:start id=TRAINER_HALEY_1 -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Marill** @ Cell Battery
- **Gender:** Female
- **Ability:** Huge Power
- **Level:** 9
- **EVs:** 12 Def / 12 SpD
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Aqua Jet
  - Covet
  - Aqua Ring
  - Fling

**Vulpix-Alola** @ Persim Berry
- **Gender:** Female
- **Ability:** Snow Cloak
- **Level:** 9
- **EVs:** 8 HP / 12 SpA
- **Nature:** Docile
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Disable
  - Confuse Ray
  - Powder Snow
  - Tail Slap
<!-- trainer-party:end -->

---

### Twins Mina and Gina — *Mandatory*
<!-- trainer-party:start id=TRAINER_GINA_AND_MIA_1 -->
**Battle type:** Doubles.

**Pre-battle healing:** None.

**Milcery** @ Maranga Berry
- **Gender:** Female
- **Ability:** Aroma Veil
- **Level:** 10
- **IVs:** 31 HP / 0 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
- **Moves:**
  - Sweet Kiss
  - Sweet Scent
  - Draining Kiss
  - Aromatic Mist

**Stunky** @ Chesto Berry
- **Gender:** Male
- **Ability:** Stench
- **Level:** 10
- **IVs:** 31 HP / 31 Atk / 31 Def / 31 SpA / 31 SpD / 31 Spe
- **Moves:**
  - Corrosive Gas
  - Poison Gas
  - Fury Cutter
  - Smog
<!-- trainer-party:end -->

**Mechanics Note:**  
- Stench turns normal poison inflicted by ability holder into **Toxic Poison**.  
- **Aromatic Mist** gives **+2 Sp.Def** to ally.

**AI Notes:**  
- Sweet Scent is incentivized when ally has moves calculated below **100% accuracy** (e.g., Poison Gas, Smog, Fury Cutter).

---

### Collector Darren — *Mandatory*
<!-- trainer-party:start id=TRAINER_DARREN -->
**Battle type:** Singles.

**Pre-battle healing:** Status conditions only (Pewter Crunchies).

**Dottler** @ Eviolite
- **Gender:** Male
- **Ability:** Compound Eyes
- **Level:** 12
- **EVs:** 12 HP / 36 Def / 24 SpD
- **Nature:** Bold
- **IVs:** 31 HP / 14 Atk / 31 Def / 12 SpA / 31 SpD / 16 Spe
- **Moves:**
  - Struggle Bug
  - Confusion
  - Supersonic
  - Reflect

**Seel** @ Leftovers
- **Gender:** Male
- **Ability:** Thick Fat
- **Level:** 13
- **EVs:** 36 HP / 24 SpD
- **Nature:** Calm
- **IVs:** 31 HP / 2 Atk / 31 Def / 11 SpA / 31 SpD / 14 Spe
- **Moves:**
  - Stockpile
  - Swallow
  - Skull Bash
  - Double Team
<!-- trainer-party:end -->

**Mechanics Notes:**  
- Swallow heals by **1/3 × number of stockpiles**, and it doesn't use up more stockpiles than necessary to heal to full (e.g. if only healing 60% HP and having 3 stockpiles up, only 2 are used).

**AI Notes:**  
- Double Team incentives are ignored if the target has Sweet Scent to stunlock evasion. Double Team is disincentivized if the player mon has an ability (e.g., Keen Eye) or status (e.g., Foresight) that ignores evasion boosts. Double Team gets additional incentives while AI mon has both Stockpile and Swallow and Evasion is less than +2.  
- Stockpile has a **50% chance** to get an additional **+1** while the AI mon has either Swallow or Spit Up.

---

### Fisherman Ivan — *Optional*
<!-- trainer-party:start id=TRAINER_IVAN -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Magikarp**
- **Gender:** Male
- **Level:** 10
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe

**Goldeen**
- **Gender:** Male
- **Level:** 11
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe

**Wishiwashi**
- **Gender:** Male
- **Level:** 10
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
<!-- trainer-party:end -->

### Youngster Joey — *Optional*
<!-- trainer-party:start id=TRAINER_JOEY -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Machop** @ Shell Bell
- **Gender:** Male
- **Ability:** Steadfast
- **Level:** 11
- **EVs:** 36 Def / 8 SpD
- **Nature:** Careful
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Focus Energy
  - Low Kick
  - Bullet Punch
  - Leer

**Panpour** @ Iapapa Berry
- **Gender:** Male
- **Ability:** Gluttony
- **Level:** 11
- **EVs:** 36 HP / 16 Def / 16 SpD
- **Nature:** Serious
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Water Sport
  - Cut
  - Water Gun
  - Grass Knot
<!-- trainer-party:end -->

**Mechanics Note:** Cut is still **Normal-type** but is SE against **Grass**.

---

### Bug Catcher Jose — *Optional*
<!-- trainer-party:start id=TRAINER_JOSE -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Beautifly** @ Apicot Berry
- **Gender:** Male
- **Ability:** Swarm
- **Level:** 10
- **Nature:** Calm
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Gust
  - Stun Spore
  - Absorb
  - Harden

**Dustox** @ Mago Berry
- **Gender:** Male
- **Ability:** Shield Dust
- **Level:** 10
- **Nature:** Docile
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Poison Powder
  - Poison Sting
  - Confusion
  - Harden
<!-- trainer-party:end -->

---

### School Kid Karen — *Optional*
<!-- trainer-party:start id=TRAINER_KAREN_1 -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Shroomish** @ Big Root
- **Gender:** Female
- **Ability:** Effect Spore
- **Level:** 10
- **Nature:** Quirky
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Leech Seed
  - Absorb
  - Headbutt
  - Stun Spore

**Cyndaquil** @ Leftovers
- **Gender:** Male
- **Ability:** Flash Fire
- **Level:** 10
- **EVs:** 16 Def
- **Nature:** Lonely
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Ember
  - Smokescreen
  - Double Kick
  - Howl
<!-- trainer-party:end -->

---

### Youngster Johnson — *Optional*
<!-- trainer-party:start id=TRAINER_JOHNSON -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Seedot** @ Jaboca Berry
- **Gender:** Male
- **Ability:** Pickpocket
- **Level:** 10
- **Nature:** Hardy
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Bide
  - Astonish
  - Harden
  - Absorb

**Lotad** @ White Herb
- **Gender:** Male
- **Ability:** Swift Swim
- **Level:** 10
- **Nature:** Docile
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Mist
  - Growl
  - Water Gun
  - Astonish
<!-- trainer-party:end -->

---

### Hiker Clark — *Optional*
<!-- trainer-party:start id=TRAINER_CLARK -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Nacli** @ Oran Berry
- **Gender:** Male
- **Ability:** Purifying Salt
- **Level:** 11
- **EVs:** 20 HP / 4 Def / 36 SpD
- **Nature:** Impish
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Mud Shot
  - Rock Throw
  - Iron Defense
  - Tackle
<!-- trainer-party:end -->

---

### Hiker Devan — *Mandatory to reach Rusturf Tunnel*
<!-- trainer-party:start id=TRAINER_DEVAN -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Diglett** @ Silk Scarf
- **Gender:** Male
- **Ability:** Sand Veil
- **Level:** 11
- **EVs:** 16 Def
- **Nature:** Impish
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Scratch
  - Bulldoze
  - Screech
  - Aerial Ace
<!-- trainer-party:end -->

---

### Camper Elias — *Optional with Reward*
<!-- trainer-party:start id=TRAINER_ELIAS -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Scraggy** @ Eject Button
- **Gender:** Male
- **Ability:** Intimidate
- **Level:** 12
- **EVs:** 12 HP / 28 Spe
- **IVs:** 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- **Nature:** Jolly
- **Moves:**
  - Fake Out
  - Beat Up
  - Low Kick
  - Leer

**Sableye** @ Eject Button
- **Gender:** Male
- **Ability:** Prankster
- **Level:** 12
- **EVs:** 20 HP / 32 SpD
- **Nature:** Careful
- **IVs:** 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- **Moves:**
  - Reflect
  - Light Screen
  - Shadow Sneak
  - Feint
<!-- trainer-party:end -->

**Reward Notes:**  
- Gives **1 Eject Button** in non-Resource mode.  
- Gives **3 Eject Buttons** in Resource non-Monotype.  
- Gives **6 Eject Buttons** in Resource Monotype.

---

## Rustboro Gym

### Youngster Josh — *Mandatory*
<!-- trainer-party:start id=TRAINER_JOSH -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Roggenrola** @ Oran Berry
- **Gender:** Male
- **Ability:** Sturdy
- **Level:** 10
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Rock Throw
  - Tackle
  - Harden

**Geodude** @ Clear Amulet
- **Gender:** Male
- **Ability:** Sturdy
- **Level:** 12
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Rock Polish
  - Rollout
  - Defense Curl
  - Tackle
<!-- trainer-party:end -->

---

### Youngster Tommy and Hiker Marc — *Mandatory Double Battle*

#### Youngster Tommy
<!-- trainer-party:start id=TRAINER_TOMMY -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Binacle** @ Rindo Berry
- **Gender:** Male
- **Ability:** Pickpocket
- **Level:** 11
- **EVs:** 8 Def / 24 SpD
- **Nature:** Sassy
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Payback
  - Smack Down
  - Helping Hand
  - Water Gun

**Rockruff**
- **Gender:** Male
- **Ability:** Vital Spirit
- **Level:** 12
- **Nature:** Impish
- **IVs:** 10 HP / 31 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Helping Hand
  - Taunt
  - Tackle
  - Rock Throw
<!-- trainer-party:end -->

#### Hiker Marc
<!-- trainer-party:start id=TRAINER_MARC -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Rolycoly** @ Absorb Bulb
- **Gender:** Male
- **Ability:** Steam Engine
- **Level:** 11
- **EVs:** 12 HP / 48 Spe
- **Nature:** Hardy
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 10 SpD / 10 Spe
- **Moves:**
  - Incinerate
  - Ancient Power
  - Smokescreen
  - Rapid Spin

**Rhyhorn**
- **Gender:** Male
- **Ability:** Rock Head
- **Level:** 12
- **Nature:** Careful
- **IVs:** 10 HP / 10 Atk / 10 Def / 10 SpA / 15 SpD / 10 Spe
- **Moves:**
  - Take Down
  - Tail Whip
  - Fire Fang
<!-- trainer-party:end -->

**AI Notes:** Incinerate is incentivized while at least one of the player's mons is holding a berry.

---

### Gym Leader Roxanne — *Mandatory (4 possible fights)*
- Player can choose between **Singles** or **Doubles** Roxanne. Singles Roxanne has the additional **Force Setup First Turn** flag that results in **Sandstorm** almost always being used Turn 1.  
- **4-mon Roxanne** occurs in non-Monotype, or a favorable Monotype: **Mono Fighting, Water, Grass, Steel, Ground**. **3-mon Roxanne** occurs in all other Monotypes.
- Roxanne has 4 possible team formats: 3-mon singles, 4-mon singles, 3-mon doubles, 4-mon doubles. Below lists each.

---

#### Gym Leader Roxanne (3-mon Singles)
<!-- trainer-party:start id=TRAINER_ROXANNE_1_3MON -->
**Battle type:** Singles.

**Additional AI flags:** Force Setup First Turn.

**Pre-battle healing:** Complete heal.

**Yamask-Galar** @ Smooth Rock
- **Gender:** Female
- **Ability:** Wandering Spirit
- **Level:** 14
- **Tera Type:** Rock
- **EVs:** 16 HP / 8 Def / 32 SpD / 12 Spe
- **Nature:** Careful
- **IVs:** 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- **Moves:**
  - Sandstorm
  - Astonish
  - Rock Tomb
  - Curse

**Lileep** @ Kee Berry
- **Gender:** Female
- **Ability:** Storm Drain
- **Level:** 13
- **EVs:** 12 HP / 16 Def / 28 SpD / 16 Spe
- **Nature:** Serious
- **IVs:** 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- **Moves:**
  - Mega Drain
  - Infestation
  - Rock Tomb
  - Recover

**Nosepass** @ Enigma Berry
- **Gender:** Female
- **Ability:** Sand Force
- **Level:** 15
- **EVs:** 12 HP / 24 Def / 12 SpD / 12 Spe
- **Nature:** Hardy
- **IVs:** 24 HP / 24 Atk / 24 Def / 24 SpA / 24 SpD / 24 Spe
- **Moves:**
  - Rock Smash
  - Torment
  - Rock Tomb
  - Bulldoze
<!-- trainer-party:end -->

---

#### Gym Leader Roxanne (4-mon Singles)
<!-- trainer-party:start id=TRAINER_ROXANNE_1 -->
**Battle type:** Singles.

**Additional AI flags:** Force Setup First Turn.

**Pre-battle healing:** Complete heal.

**Yamask-Galar** @ Smooth Rock
- **Gender:** Female
- **Ability:** Wandering Spirit
- **Level:** 14
- **Tera Type:** Rock
- **EVs:** 16 HP / 8 Def / 32 SpD / 12 Spe
- **Nature:** Careful
- **IVs:** 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- **Moves:**
  - Sandstorm
  - Astonish
  - Rock Tomb
  - Curse

**Dwebble** @ Berry Juice
- **Gender:** Female
- **Ability:** Sturdy
- **Level:** 13
- **EVs:** 16 HP / 12 Def / 12 SpD / 36 Spe
- **Nature:** Impish
- **IVs:** 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- **Moves:**
  - Rock Tomb
  - Withdraw
  - Rock Smash
  - Aerial Ace

**Lileep** @ Kee Berry
- **Gender:** Female
- **Ability:** Storm Drain
- **Level:** 13
- **EVs:** 12 HP / 16 Def / 28 SpD / 16 Spe
- **Nature:** Serious
- **IVs:** 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- **Moves:**
  - Mega Drain
  - Infestation
  - Rock Tomb
  - Recover

**Nosepass** @ Enigma Berry
- **Gender:** Female
- **Ability:** Sand Force
- **Level:** 15
- **EVs:** 12 HP / 24 Def / 12 SpD / 12 Spe
- **Nature:** Hardy
- **IVs:** 24 HP / 24 Atk / 24 Def / 24 SpA / 24 SpD / 24 Spe
- **Moves:**
  - Shock Wave
  - Pain Split
  - Rock Tomb
  - Bulldoze
<!-- trainer-party:end -->

---

#### Gym Leader Roxanne (3-mon doubles)
<!-- trainer-party:start id=TRAINER_ROXANNE_1_3MON_DOUBLES -->
**Battle type:** Doubles.

**Pre-battle healing:** Complete heal.

**Yamask-Galar** @ Berry Juice
- **Gender:** Female
- **Ability:** Wandering Spirit
- **Level:** 14
- **Tera Type:** Rock
- **EVs:** 16 HP / 8 Def / 32 SpD / 12 Spe
- **Nature:** Careful
- **IVs:** 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- **Moves:**
  - Sandstorm
  - Astonish
  - Rock Tomb
  - Curse

**Lileep** @ Kee Berry
- **Gender:** Female
- **Ability:** Storm Drain
- **Level:** 13
- **EVs:** 12 HP / 16 Def / 28 SpD / 16 Spe
- **Nature:** Serious
- **IVs:** 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- **Moves:**
  - Mega Drain
  - Infestation
  - Rock Tomb
  - Recover

**Nosepass** @ Enigma Berry
- **Gender:** Female
- **Ability:** Sand Force
- **Level:** 15
- **EVs:** 12 HP / 24 Def / 12 SpD / 12 Spe
- **Nature:** Hardy
- **IVs:** 24 HP / 24 Atk / 24 Def / 24 SpA / 24 SpD / 24 Spe
- **Moves:**
  - Shock Wave
  - Pain Split
  - Rock Tomb
  - Bulldoze
<!-- trainer-party:end -->

---

#### Gym Leader Roxanne (4-mon doubles)
<!-- trainer-party:start id=TRAINER_ROXANNE_1_DOUBLES -->
**Battle type:** Doubles.

**Pre-battle healing:** Complete heal.

**Dwebble** @ Berry Juice
- **Gender:** Female
- **Ability:** Sturdy
- **Level:** 13
- **EVs:** 32 HP / 28 SpD
- **Nature:** Impish
- **IVs:** 16 HP / 12 Atk / 25 Def / 10 SpA / 21 SpD / 5 Spe
- **Moves:**
  - Rock Tomb
  - Withdraw
  - Rock Smash
  - Aerial Ace

**Lileep** @ Kee Berry
- **Gender:** Female
- **Ability:** Storm Drain
- **Level:** 13
- **EVs:** 12 HP / 16 Def / 36 Spe
- **Nature:** Jolly
- **IVs:** 24 HP / 12 Atk / 19 Def / 17 SpA / 21 SpD / 30 Spe
- **Moves:**
  - Mega Drain
  - Infestation
  - Rock Tomb
  - Recover

**Yamask-Galar** @ Smooth Rock
- **Gender:** Female
- **Ability:** Wandering Spirit
- **Level:** 14
- **Tera Type:** Rock
- **EVs:** 16 HP / 8 Def / 32 SpD / 12 Spe
- **Nature:** Careful
- **IVs:** 12 HP / 12 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- **Moves:**
  - Sandstorm
  - Astonish
  - Rock Tomb
  - Curse

**Nosepass** @ Enigma Berry
- **Gender:** Female
- **Ability:** Sand Force
- **Level:** 15
- **EVs:** 12 HP / 24 Def / 12 SpD / 12 Spe
- **Nature:** Hardy
- **IVs:** 24 HP / 24 Atk / 24 Def / 24 SpA / 24 SpD / 24 Spe
- **Moves:**
  - Shock Wave
  - Pain Split
  - Rock Tomb
  - Bulldoze
<!-- trainer-party:end -->

### Lady Sarah and Rich Boy Dawson — *Optional Double Battle*
> This Double Battle guards a **Naive Mint**.

#### Rich Boy Dawson
<!-- trainer-party:start id=TRAINER_DAWSON -->
**Battle type:** Singles.

**Pre-battle healing:** Complete heal.

**Popplio** @ Throat Spray
- **Gender:** Male
- **Ability:** Liquid Voice
- **Level:** 14
- **EVs:** 28 HP / 24 Def / 12 SpA / 8 SpD
- **Nature:** Calm
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Disarming Voice
  - Draining Kiss
  - Icy Wind
  - Life Dew

**Skwovet** @ Sitrus Berry
- **Gender:** Male
- **Ability:** Cheek Pouch
- **Level:** 14
- **EVs:** 40 HP / 16 Def / 32 SpD
- **Nature:** Impish
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Assurance
  - Bullet Seed
  - Dig
  - Tail Whip
<!-- trainer-party:end -->

#### Lady Sarah
<!-- trainer-party:start id=TRAINER_SARAH -->
**Items:** Full Restore

**Battle type:** Singles.

**Pre-battle healing:** Complete heal.

**Floette** @ Misty Seed
- **Gender:** Female
- **Ability:** Symbiosis
- **Level:** 14
- **EVs:** 24 HP / 24 Def / 16 SpD
- **Nature:** Sassy
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 0 Spe
- **Moves:**
  - Misty Terrain
  - Disarming Voice
  - Grass Knot
  - Helping Hand

**Pachirisu** @ Sitrus Berry
- **Gender:** Female
- **Ability:** Pickup
- **Level:** 14
- **EVs:** 4 HP / 40 Def / 20 SpD / 12 Spe
- **Nature:** Careful
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Follow Me
  - Helping Hand
  - Nuzzle
  - Super Fang
<!-- trainer-party:end -->

**AI Notes:**  
- Floette will be incentivized to use **Misty Terrain** on T1, and Popplio **Disarming Voice** gains **+1 score** thanks to Throat Spray.

---

### School Kid Jerry — *Optional*
<!-- trainer-party:start id=TRAINER_JERRY_1 -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Ralts**
- **Gender:** Male
- **Level:** 13
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
<!-- trainer-party:end -->

---

### Lass Janice — *Optional*
<!-- trainer-party:start id=TRAINER_JANICE -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Marill**
- **Gender:** Female
- **Level:** 13
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
<!-- trainer-party:end -->

### Rusturf Tunnel Aqua Grunt — *Mandatory*
<!-- trainer-party:start id=TRAINER_GRUNT_RUSTURF_TUNNEL -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Clobbopus** @ Mystic Water
- **Gender:** Male
- **Ability:** Technician
- **Level:** 15
- **EVs:** 28 HP / 32 Def / 28 SpD
- **Nature:** Impish
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Aqua Jet
  - Rock Smash
  - Leer
  - Feint

**Totodile** @ Sea Incense
- **Gender:** Male
- **Ability:** Torrent
- **Level:** 16
- **EVs:** 20 HP / 16 Def / 36 SpD
- **Nature:** Bashful
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Thrash
  - Water Pulse
  - Water Sport
  - Bite
<!-- trainer-party:end -->

**Terrain Note:** Rusturf Tunnel has **Misty Terrain**, which prevents Totodile's **Thrash** from confusing.

---

## Rustburo City (After Badge 1)

### Rustburo Rival — *Optional, Reward*
> Winning this fight gives **Bottle Cap**.

> There are three rival teams depending on starter/monotype.

---

#### Rustburo Rival (Combusken Team)
> This team is used if the player chooses **Treecko** as starter, or the player chooses Mono **Normal, Grass, Dark, Bug, Ice, or Steel**.

<!-- trainer-party:start ids=TRAINER_BRENDAN_RUSTBORO_TREECKO,TRAINER_MAY_RUSTBORO_TREECKO -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Wingull** @ Berry Juice
- **Gender:** Trainer default
- **Ability:** Rain Dish
- **Level:** 15
- **EVs:** 20 HP / 44 Def / 16 SpD
- **Nature:** Calm
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Supersonic
  - Water Pulse
  - Rain Dance
  - Aqua Ring

**Poochyena** @ Tanga Berry
- **Gender:** Trainer default
- **Ability:** Rattled
- **Level:** 15
- **EVs:** 32 HP / 32 Def / 32 Spe
- **Nature:** Jolly
- **IVs:** 15 HP / 31 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Yawn
  - Bite
  - Trailblaze
  - Take Down

**Combusken** @ Scope Lens
- **Gender:** Trainer default
- **Ability:** Blaze
- **Level:** 17
- **EVs:** 16 HP / 16 Atk / 16 Def / 16 SpD / 32 Spe
- **Nature:** Quirky
- **IVs:** 20 HP / 20 Atk / 20 Def / 20 SpA / 20 SpD / 20 Spe
- **Moves:**
  - Focus Energy
  - Double Kick
  - Incinerate
  - Quick Attack
<!-- trainer-party:end -->

---

#### Rustboro Rival (Grovyle Team)
> This team is used if the player chooses **Mudkip** as starter, or the player chooses Mono **Water, Ground, Electric, Psychic, Dragon, or Fighting**.

<!-- trainer-party:start ids=TRAINER_BRENDAN_RUSTBORO_MUDKIP,TRAINER_MAY_RUSTBORO_MUDKIP -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Wingull** @ Berry Juice
- **Gender:** Trainer default
- **Ability:** Rain Dish
- **Level:** 15
- **EVs:** 20 HP / 44 Def / 16 SpD
- **Nature:** Calm
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Supersonic
  - Water Pulse
  - Rain Dance
  - Aqua Ring

**Poochyena** @ Tanga Berry
- **Gender:** Trainer default
- **Ability:** Rattled
- **Level:** 15
- **EVs:** 32 HP / 32 Def / 32 Spe
- **Nature:** Jolly
- **IVs:** 15 HP / 31 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Yawn
  - Bite
  - Trailblaze
  - Take Down

**Grovyle** @ Bright Powder
- **Gender:** Trainer default
- **Ability:** Overgrow
- **Level:** 17
- **EVs:** 20 HP / 36 Def / 28 SpD / 12 Spe
- **Nature:** Serious
- **IVs:** 20 HP / 20 Atk / 20 Def / 20 SpA / 20 SpD / 20 Spe
- **Moves:**
  - Aerial Ace
  - Mega Drain
  - Fury Cutter
  - Substitute
<!-- trainer-party:end -->

---

#### Rustboro Rival (Marshtomp Team)
> This team is used if the player chooses **Torchic** as starter, or the player chooses Mono **Flying, Poison, Rock, Ghost, Fire, or Fairy**.

<!-- trainer-party:start ids=TRAINER_BRENDAN_RUSTBORO_TORCHIC,TRAINER_MAY_RUSTBORO_TORCHIC -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Slugma** @ Grip Claw
- **Gender:** Trainer default
- **Ability:** Flame Body
- **Level:** 15
- **EVs:** 20 HP / 20 Def / 12 SpA / 20 SpD
- **Nature:** Bold
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Will-O-Wisp
  - Recover
  - Smog
  - Fire Spin

**Poochyena** @ Tanga Berry
- **Gender:** Trainer default
- **Ability:** Rattled
- **Level:** 15
- **EVs:** 32 HP / 32 Def / 32 Spe
- **Nature:** Jolly
- **IVs:** 15 HP / 31 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Yawn
  - Bite
  - Trailblaze
  - Take Down

**Marshtomp** @ Iapapa Berry
- **Gender:** Trainer default
- **Ability:** Torrent
- **Level:** 17
- **EVs:** 36 HP / 12 Def / 16 SpA / 36 SpD
- **IVs:** 20 HP / 20 Atk / 20 Def / 20 SpA / 20 SpD / 20 Spe
- **Nature:** Serious
- **Moves:**
  - Rock Smash
  - Supersonic
  - Mud Bomb
  - Water Pulse
<!-- trainer-party:end -->

### Aroma Lady Plenny
> South of Dewford Town; Blocks access to Dewford Garden.

<!-- trainer-party:start id=TRAINER_PLENNY -->
**Battle type:** Singles.

**Pre-battle healing:** Status conditions only (Lum Berry).

**Noibat** @ Leftovers
- **Gender:** Female
- **Ability:** Frisk
- **Level:** 17
- **EVs:** 12 HP / 16 Atk / 28 Def / 12 SpD
- **Nature:** Quirky
- **IVs:** 12 HP / 31 Atk / 12 Def / 12 SpA / 12 SpD / 12 Spe
- **Moves:**
  - Fly
  - Agility
  - Bite
  - Absorb

**Grotle** @ Soft Sand
- **Gender:** Male
- **Ability:** Overgrow
- **Level:** 18
- **EVs:** 28 Atk / 36 SpA / 20 SpD
- **Nature:** Quiet
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Mud Shot
  - Razor Leaf
  - Leech Seed
  - Curse
<!-- trainer-party:end -->

### Fisherman Ned — *Optional Spinner*
> Fisherman directly above Dewford

<!-- trainer-party:start id=TRAINER_NED -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Tentacool** @ Honey
- **Gender:** Male
- **Ability:** Clear Body
- **Level:** 14
- **EVs:** 20 HP / 32 Def / 12 Spe
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Supersonic
  - Aurora Beam
  - Acupressure
  - Bubble Beam

**Inkay** @ Grip Claw
- **Gender:** Male
- **Ability:** Contrary
- **Level:** 14
- **EVs:** 32 HP / 4 Def / 32 SpD
- **IVs:** 15 HP / 31 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Flatter
  - Topsy-Turvy
  - Wrap
  - Liquidation
<!-- trainer-party:end -->

### Fisherman Elliot — *Mandatory to reach Granite Cave*
> Fisherman next to Granite Cave

**Remoraid** @ Sea Incense  
- **Ability:** Hustle  
- **Level:** 14  
- **EVs:** 4 HP / 20 Atk / 4 Def / 20 SpA / 4 SpD / 20 Spe  
- **Nature:** Quirky  
- **IVs:** 15 HP / 15 Def / 15 SpA / 15 SpD / 15 Spe  
- **Moves:**
  - Screech
  - Secret Power
  - Psybeam
  - Brine

<!-- trainer-party:start id=TRAINER_ELLIOT_1 -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Poliwag** @ Damp Rock
- **Gender:** Male
- **Ability:** Damp
- **Level:** 14
- **EVs:** 28 Atk / 20 SpA / 20 SpD / 20 Spe
- **Nature:** Hardy
- **IVs:** 15 HP / 31 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Water Sport
  - Flip Turn
  - Hypnosis
  - Round

**Remoraid** @ Sea Incense
- **Gender:** Male
- **Ability:** Hustle
- **Level:** 14
- **EVs:** 4 HP / 20 Atk / 4 Def / 20 SpA / 4 SpD / 20 Spe
- **Nature:** Quirky
- **IVs:** 15 HP / 31 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Screech
  - Secret Power
  - Psybeam
  - Brine

**Magikarp** @ Adrenaline Orb
- **Gender:** Male
- **Ability:** Rattled
- **Level:** 15
- **EVs:** 20 HP / 48 Atk / 8 Def / 20 Spe
- **Nature:** Adamant
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Bounce
  - Flail
  - Tackle
  - Splash
<!-- trainer-party:end -->

**Mechanics Notes:**

- Damp heals **33%** after Water Sport or Rain has been activated, or the mon switches in while they are active.  
- Damp Rock extends **Water Sport** to **8 turns**.

**AI Notes:**  
- Pivot attacking moves like **Flip Turn** get a **+1 score** if the Pokémon has Damp, Water Sport is active, and the mon either is slower or has **≤ 75% HP**.  
- Water Sport gets a **+1 score** if the user has a switching move (like Flip Turn); and it "lives 1 hit" from the player mon if it's faster or "2 hits" if it's slower. These KO calcs add **33% HP** to the mon to take into account the Water Sport and Damp healing.

---

## Granite Cave — area outside Steven's Room

### Black Belt Daichi — Mandatory to reach Steven's Room
- The left-most Black Belt outside Steven's Room
-  Can be fought before Brawly, and is mandatory for story progression after Brawly. Gives a **Muscle Band**. His Pokémon have excess Attack EVs for flavor.

<!-- trainer-party:start id=TRAINER_DAICHI -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Crabrawler** @ Muscle Band
- **Gender:** Male
- **Ability:** Hyper Cutter
- **Level:** 15
- **EVs:** 20 HP / 31 Atk / 20 Def / 20 SpD
- **Nature:** Impish
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Vise Grip
  - Rock Smash
  - Leer
  - Payback

**Mudbray** @ Muscle Band
- **Gender:** Male
- **Ability:** Inner Focus
- **Level:** 15
- **EVs:** 20 HP / 47 Atk / 20 Def / 8 SpD
- **Nature:** Careful
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Rock Smash
  - Stomp
  - Smack Down
  - Iron Defense
<!-- trainer-party:end -->

---

### Black Belt Kenji — Mandatory to reach Steven's Room
- The center Black Belt outside Steven's room.
- Can be fought before Brawly, and is mandatory for story progression after Brawly. Gives **Protective Pads**. His Pokémon have excess Attack EVs for flavor.

<!-- trainer-party:start id=TRAINER_KENJI -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Pancham** @ Protective Pads
- **Gender:** Male
- **Ability:** Iron Fist
- **Level:** 15
- **EVs:** 43 Atk / 32 Def / 24 Spe
- **Nature:** Careful
- **IVs:** 15 HP / 31 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Arm Thrust
  - Comet Punch
  - Power Trip
  - Work Up

**Pikipek** @ Protective Pads
- **Gender:** Male
- **Ability:** Skill Link
- **Level:** 15
- **EVs:** 8 HP / 35 Atk / 20 Def / 20 SpD / 8 Spe
- **Nature:** Jolly
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Fury Attack
  - Rock Smash
  - Pluck
  - Supersonic
<!-- trainer-party:end -->

---

### Black Belt Ryuji — Mandatory to reach Steven's Room
- The right-most black belt outside Steven's room, and the Black Belt directly blocking the entrance.
- Is mandatory for story progression, but can't be fought until beating Brawly, Daichi, and Kenji. Gives a **Black Belt**. Has excess Atk EVs for flavor.

<!-- trainer-party:start id=TRAINER_RYUJI -->
**Battle type:** Doubles.

**Pre-battle healing:** None.

**Sawk** @ Black Belt
- **Gender:** Male
- **Ability:** Sturdy
- **Level:** 17
- **EVs:** 12 HP / 34 Atk / 12 Def / 12 SpD / 28 Spe
- **Nature:** Jolly
- **IVs:** 18 HP / 18 Atk / 18 Def / 18 SpA / 18 SpD / 18 Spe
- **Moves:**
  - Rock Smash
  - Low Sweep
  - Quick Guard
  - Coaching

**Throh** @ Black Belt
- **Gender:** Male
- **Ability:** Guts
- **Level:** 17
- **EVs:** 4 HP / 40 Atk / 28 Def / 28 SpD
- **Nature:** Impish
- **IVs:** 18 HP / 18 Atk / 18 Def / 18 SpA / 18 SpD / 18 Spe
- **Moves:**
  - Bulk Up
  - Seismic Toss
  - Vital Throw
  - Rock Smash
<!-- trainer-party:end -->

### Battle Girl Laura — Mandatory

<!-- trainer-party:start id=TRAINER_LAURA -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Farfetch’d-Galar** @ Stick
- **Gender:** Female
- **Ability:** Scrappy
- **Level:** 15
- **EVs:** 32 HP / 36 Atk / 32 Def
- **Nature:** Impish
- **IVs:** 15 HP / 31 Atk / 16 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Counter
  - Feint
  - Peck
  - Leer
<!-- trainer-party:end -->

### Black Belt Takao — Optional
- Takao is found on the left side of Dewford Gym
<!-- trainer-party:start id=TRAINER_TAKAO -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Machop** @ Iapapa Berry
- **Gender:** Male
- **Ability:** Guts
- **Level:** 15
- **EVs:** 48 HP / 48 Def / 8 SpD
- **Nature:** Impish
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Bide
  - Karate Chop
  - Heavy Slam
  - Encore
<!-- trainer-party:end -->

### Battle Girl Lilith and Sailor Brenden — Optional Double Battle
- These two trainers are on  the right side of the Gym. 

#### Battle Girl Lilith
<!-- trainer-party:start id=TRAINER_LILITH -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Riolu** @ Micle Berry
- **Gender:** Male
- **Ability:** Prankster
- **Level:** 15
- **EVs:** 20 HP / 20 Atk / 36 SpA / 20 Spe
- **Nature:** Serious
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Me First
  - Mind Reader
  - Focus Blast
  - Iron Tail
<!-- trainer-party:end -->

#### Sailor Brenden
<!-- trainer-party:start id=TRAINER_BRENDEN -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Croagunk** @ Oran Berry
- **Gender:** Male
- **Ability:** Anticipation
- **Level:** 15
- **EVs:** 40 Atk / 20 Def / 20 SpD
- **Nature:** Hardy
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Mud-Slap
  - Poison Sting
  - Astonish
  - Taunt
<!-- trainer-party:end -->

### Battle Girl Jocelyn and Black Belt Cristian — Mandatory Double Battle
#### Battle Girl Jocelyn
<!-- trainer-party:start id=TRAINER_JOCELYN -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Crabrawler** @ Shell Bell
- **Gender:** Female
- **Ability:** Hyper Cutter
- **Level:** 16
- **EVs:** 16 HP / 34 Atk / 32 Def
- **Nature:** Impish
- **IVs:** 15 HP / 18 Atk / 16 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Upper Hand
  - Liquidation
  - Reversal
  - Dizzy Punch

**Timburr** @ Silk Scarf
- **Gender:** Male
- **Ability:** Guts
- **Level:** 16
- **EVs:** 16 HP / 38 Atk / 24 Def
- **Nature:** Adamant
- **IVs:** 15 HP / 18 Atk / 16 Def / 15 SpA / 15 SpD / 15 Spe
- **Moves:**
  - Force Palm
  - Smelling Salts
  - Payback
  - Helping Hand
<!-- trainer-party:end -->

#### Black Belt Cristian
<!-- trainer-party:start id=TRAINER_CRISTIAN -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Sneasel-Hisui** @ Payapa Berry
- **Gender:** Male
- **Ability:** Pickpocket
- **Level:** 16
- **EVs:** 28 HP / 34 Atk / 36 Spe
- **Nature:** Careful
- **IVs:** 15 HP / 16 Atk / 15 Def / 15 SpA / 15 SpD / 18 Spe
- **Moves:**
  - Fake Out
  - Coaching
  - Trailblaze
  - Rock Smash

**Mankey** @ Loaded Dice
- **Gender:** Male
- **Ability:** Vital Spirit
- **Level:** 16
- **EVs:** 20 HP / 36 Atk / 44 Spe
- **Nature:** Jolly
- **IVs:** 15 HP / 16 Atk / 15 Def / 15 SpA / 15 SpD / 18 Spe
- **Moves:**
  - Foresight
  - Power-Up Punch
  - Fury Swipes
  - Swagger
<!-- trainer-party:end -->

**AI Notes:**  
- The AI computes loaded Dice Fury Swipes as 4.5x the base power of Fury Swipes.
- **Coaching**
	- -10 score if either of the player's mons is faster than both the Coaching mon and its partner, and that player mon can KO the partner mon. 
	- In the case that the coaching mon is faster than all AI mons that can KO the partner,  the AI simulates the partner gaining the coaching stat changes. If the partner can still be fast killed by a player mon after gaining those stat changes, a -10 score is applied.
	- Since all partners have physical moves, disincentives for player slow kills are ignored.
	- While the partner is at half health or above:
		- General +1 score (equalizing Coaching with best damaging move when no disincentives are applied).
		- Since all partners have physical moves, there's a 50% chance to get a score increase. This increase is +2 if the partner has a neutral Attack stat stage or worse and +1 otherwise. 
### Gym Leader Brawly — *Mandatory (4 possible fights)*
- Player can choose between **Singles** or **Doubles** Brawly. Singles Brawly has the additional **Force Setup First Turn** flag that results in **Light Screen** almost always being used Turn 1.  
- **4-mon Brawly** occurs in non-Monotype, **Mono Water**, or a favorable Monotype: **Mono Flying, Psychic, Fairy, Poison, Ghost, Bug.** (Water is included solely because of the abundance of Water types, despite having a neutral matchup.)
- Brawly has 4 possible team formats: 3-mon singles, 4-mon singles, 3-mon doubles, 4-mon doubles. Below lists each.
#### Gym Leader Brawly (4-mon Singles)
<!-- trainer-party:start id=TRAINER_BRAWLY_1 -->
**Battle type:** Singles.

**Additional AI flags:** Force Setup First Turn.

**Pre-battle healing:** Complete heal.

**Meditite** @ Coba Berry
- **Gender:** Male
- **Ability:** Pure Power
- **Level:** 17
- **EVs:** 48 Atk / 32 Def / 16 Spe
- **Nature:** Naive
- **IVs:** 18 HP / 18 Atk / 18 Def / 18 SpA / 18 SpD / 18 Spe
- **Moves:**
  - Low Kick
  - Psychic
  - Light Screen
  - Aerial Ace

**Combusken** @ Shuca Berry
- **Gender:** Male
- **Ability:** Speed Boost
- **Level:** 17
- **EVs:** 8 HP / 48 Atk / 32 Def
- **Nature:** Naughty
- **IVs:** 18 HP / 18 Atk / 18 Def / 18 SpA / 18 SpD / 18 Spe
- **Moves:**
  - Work Up
  - Incinerate
  - Low Kick
  - Natural Gift

**Pawniard** @ Protective Pads
- **Gender:** Male
- **Ability:** Inner Focus
- **Level:** 18
- **Tera Type:** Fighting
- **EVs:** 28 HP / 48 Atk / 28 Def
- **IVs:** 20 HP / 20 Atk / 20 Def / 20 SpA / 20 SpD / 20 Spe
- **Nature:** Impish
- **Moves:**
  - Low Kick
  - Metal Claw
  - Taunt
  - Assurance

**Makuhita** @ Eviolite
- **Gender:** Male
- **Ability:** Sheer Force
- **Level:** 19
- **EVs:** 4 HP / 48 Atk / 48 Def
- **IVs:** 26 HP / 24 Atk / 26 Def / 24 SpA / 26 SpD / 24 Spe
- **Nature:** Adamant
- **Moves:**
  - Bulk Up
  - Low Kick
  - Rock Tomb
  - Body Slam
<!-- trainer-party:end -->

#### Gym Leader Brawly (3-mon Singles)
<!-- trainer-party:start id=TRAINER_BRAWLY_1_3MON -->
**Battle type:** Singles.

**Additional AI flags:** Force Setup First Turn.

**Pre-battle healing:** Complete heal.

**Meditite** @ Coba Berry
- **Gender:** Male
- **Ability:** Pure Power
- **Level:** 17
- **EVs:** 48 Atk / 32 Def / 16 Spe
- **Nature:** Naive
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 18 Spe
- **Moves:**
  - Low Kick
  - Psychic
  - Light Screen
  - Rock Tomb

**Pawniard** @ Protective Pads
- **Gender:** Male
- **Ability:** Inner Focus
- **Level:** 18
- **Tera Type:** Fighting
- **EVs:** 28 HP / 48 Atk / 28 Def
- **IVs:** 15 HP / 15 Atk / 20 Def / 11 SpA / 15 SpD / 15 Spe
- **Nature:** Impish
- **Moves:**
  - Low Kick
  - Metal Claw
  - Taunt
  - Assurance

**Makuhita** @ Eviolite
- **Gender:** Male
- **Ability:** Sheer Force
- **Level:** 19
- **EVs:** 36 HP / 48 Atk / 16 Def
- **IVs:** 15 HP / 15 Atk / 16 Def / 10 SpA / 20 SpD / 15 Spe
- **Nature:** Adamant
- **Moves:**
  - Bulk Up
  - Low Kick
  - Bulldoze
  - Body Slam
<!-- trainer-party:end -->

#### Gym Leader Brawly (4-mon Doubles)

<!-- trainer-party:start id=TRAINER_BRAWLY_1_DOUBLES -->
**Battle type:** Doubles.

**Pre-battle healing:** Complete heal.

**Meditite** @ Coba Berry
- **Gender:** Male
- **Ability:** Pure Power
- **Level:** 17
- **EVs:** 48 Atk / 32 Def / 16 Spe
- **Nature:** Naive
- **IVs:** 18 HP / 18 Atk / 18 Def / 18 SpA / 18 SpD / 18 Spe
- **Moves:**
  - Low Kick
  - Psychic
  - Light Screen
  - Signal Beam

**Combusken** @ Expert Belt
- **Gender:** Male
- **Ability:** Speed Boost
- **Level:** 17
- **EVs:** 8 HP / 48 Atk / 32 Def
- **Nature:** Naughty
- **IVs:** 18 HP / 18 Atk / 18 Def / 18 SpA / 18 SpD / 18 Spe
- **Moves:**
  - Aerial Ace
  - Low Kick
  - Incinerate
  - Helping Hand

**Pawniard** @ Protective Pads
- **Gender:** Male
- **Ability:** Inner Focus
- **Level:** 18
- **Tera Type:** Fighting
- **EVs:** 28 HP / 48 Atk / 28 Def
- **IVs:** 20 HP / 20 Atk / 20 Def / 20 SpA / 20 SpD / 20 Spe
- **Nature:** Impish
- **Moves:**
  - Low Kick
  - Metal Claw
  - Taunt
  - Assurance

**Makuhita** @ Eviolite
- **Gender:** Male
- **Ability:** Sheer Force
- **Level:** 19
- **EVs:** 4 HP / 48 Atk / 48 Def
- **IVs:** 26 HP / 24 Atk / 26 Def / 24 SpA / 26 SpD / 24 Spe
- **Nature:** Adamant
- **Moves:**
  - Bulk Up
  - Low Kick
  - Rock Tomb
  - Body Slam
<!-- trainer-party:end -->

#### Gym Leader Brawly (3-mon Doubles)
<!-- trainer-party:start id=TRAINER_BRAWLY_1_3MON_DOUBLES -->
**Battle type:** Doubles.

**Pre-battle healing:** Complete heal.

**Meditite** @ Coba Berry
- **Gender:** Male
- **Ability:** Pure Power
- **Level:** 17
- **EVs:** 48 Atk / 32 Def / 16 Spe
- **Nature:** Naive
- **IVs:** 15 HP / 15 Atk / 15 Def / 15 SpA / 15 SpD / 18 Spe
- **Moves:**
  - Low Kick
  - Psychic
  - Light Screen
  - Aerial Ace

**Pawniard** @ Protective Pads
- **Gender:** Male
- **Ability:** Inner Focus
- **Level:** 18
- **Tera Type:** Fighting
- **EVs:** 28 HP / 48 Atk / 28 Def
- **IVs:** 15 HP / 15 Atk / 20 Def / 11 SpA / 15 SpD / 15 Spe
- **Nature:** Impish
- **Moves:**
  - Low Kick
  - Metal Claw
  - Taunt
  - Assurance

**Makuhita** @ Eviolite
- **Gender:** Male
- **Ability:** Sheer Force
- **Level:** 19
- **EVs:** 4 HP / 48 Atk / 48 Def
- **IVs:** 15 HP / 15 Atk / 16 Def / 10 SpA / 20 SpD / 15 Spe
- **Nature:** Adamant
- **Moves:**
  - Bulk Up
  - Low Kick
  - Rock Tomb
  - Body Slam
<!-- trainer-party:end -->

## Route 109

Initial Route 109 beach and Seashore House trainer parties gain 3 levels when challenged after defeating the Route 110 rival. Route 109 trainers with map-object coordinates below the beach (`y > 24`) are excluded, as are Ricky and Lola's rematch teams.

### Aroma Lady Cassia — *Optional Route Boss with reward*

- Requires defeating every other trainer on the Route 109 beach (`y <= 24`) and in the Seashore House. Trainers in Route 109's water portions are excluded.
- In Restricted Mode, Cassia can no longer be challenged after earning the third Badge.

- **Reward:** 1 Power Herb normally, 12 in non-monotype Resource Mode, or 18 in monotype Resource Mode. Scripted item gifts fall back to PC storage when the Bag is full.



### Tuber Ricky
<!-- trainer-party:start id=TRAINER_RICKY_1 -->
**Battle type:** Singles.

**Pre-battle healing:** None.

**Spheal** @ Wiki Berry
- **Gender:** Male
- **Ability:** Ice Body
- **Level:** 18
- **EVs:** 80 HP / 80 Def / 12 SpD
- **Nature:** Bold
- **IVs:** 13 HP / 12 Atk / 19 Def / 13 SpA / 14 SpD / 10 Spe
- **Moves:**
  - Hail
  - Aurora Beam
  - Water Pulse
  - Headbutt
<!-- trainer-party:end -->

<!-- trainer-party:start id=TRAINER_CASSIA -->
**Battle type:** Singles.

**Pre-battle healing:** Complete heal (route boss override).

**Ivysaur** @ Eviolite
- **Gender:** Female
- **Ability:** Overgrow
- **Level:** 19
- **EVs:** 36 HP / 20 Def / 20 SpD
- **Nature:** Calm
- **IVs:** 18 HP / 18 Atk / 18 Def / 18 SpA / 18 SpD / 18 Spe
- **Moves:**
  - Razor Leaf
  - Leech Seed
  - Poison Powder
  - Take Down

**Carkol** @ Sitrus Berry
- **Gender:** Female
- **Ability:** Flame Body
- **Level:** 20
- **EVs:** 28 HP / 28 Def / 20 SpD
- **Nature:** Impish
- **IVs:** 18 HP / 18 Atk / 18 Def / 18 SpA / 18 SpD / 18 Spe
- **Moves:**
  - Flame Charge
  - Smack Down
  - Rapid Spin
  - Rock Polish

**Tropius** @ Power Herb
- **Gender:** Female
- **Ability:** Chlorophyll
- **Level:** 21
- **EVs:** 28 HP / 36 SpA / 12 Spe
- **Nature:** Modest
- **IVs:** 20 HP / 20 Atk / 20 Def / 20 SpA / 20 SpD / 20 Spe
- **Moves:**
  - Solar Beam
  - Air Cutter
  - Stomp
  - Growth
<!-- trainer-party:end -->
