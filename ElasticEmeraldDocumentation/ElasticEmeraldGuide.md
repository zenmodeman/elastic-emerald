# Elastic Emerald Guide

# About This Document

Elastic Emerald is a romhack that gives the player monotype options, and it’s a game driven towards utilizing the game mechanics of Pokemon. Pokemon have been given buffs, but most buffs tend to be quite tame.  
This guide serves to provide information about the current version of the Pokemon romhack Elastic Emerald. The current pre-release version is 0.1.2.

# About Version 0.1.2

This version’s contents end right before Mr.Briney takes the player to Dewford. The available Pokemon are the ones listed in cells of the [Encounter Sheet](https://docs.google.com/spreadsheets/d/1w00UPV-e9T6S0IAVSUsqH232ncC6fKQn9mSTrP3aMPY/edit?gid=1656689645) up to Encounter Location “Petalburg Grove”. Learnsets of available Pokemon have only been placed up to level 19\. Beyond that, the learnsets are a mess and should not be taken into consideration. 

# Reference Links

Release Page: [https://github.com/zenmodeman/elastic-emerald/releases](https://github.com/zenmodeman/elastic-emerald/releases)  
Main Spreadsheet: [https://docs.google.com/spreadsheets/d/1w00UPV-e9T6S0IAVSUsqH232ncC6fKQn9mSTrP3aMPY/edit?usp=sharing](https://docs.google.com/spreadsheets/d/1w00UPV-e9T6S0IAVSUsqH232ncC6fKQn9mSTrP3aMPY/edit?usp=sharing)  
Documentation Folder: [https://drive.google.com/drive/folders/1r9yykx9H6t7KH1WKjZMBmJKSwGVNgmfJ?usp=sharing](https://drive.google.com/drive/folders/1r9yykx9H6t7KH1WKjZMBmJKSwGVNgmfJ?usp=sharing)

# Debug Mode

In this pre-release, Debug Mode is enabled, and will likely remain enabled until the full release. “Start \+ R” accesses the overworld debug menu. During a battle, “Select” will open the battle debug menu. In the Pokemon summary menu while not in a battle, “Select” will open the sprite debug menu, but this one is less useful for a player. 

The debug menu can help get out of weird states by enabling warping and such, and it can also help playtest difficult to reach states. Just keep in mind that many Pokemon and locations that could be accessible through debug mode are not ready for play yet.

## Some Gameplay Details to Know

* While the player is inside the truck, they are prompted with [several mode options](#mode-options).  
* The player’s PC has several items to bootstrap the experience.   
* Time passes based on game time rather than vanilla emerald’s real time.  
* The player gets their starter in Birch’s lab to more easily accommodate monotype patterns. So the Zigzagoon event no longer occurs. The player still has to visit the rival’s house before getting a starter.  
* Birch gives the player the Box Link right after giving the player their starter. The Box Link gives remote access to the PC akin to modern gens, but it also means the PC does not heal Pokemon placed in it until the user heals at a Pokemon center.  
* Move relearning can be accessed from the party menu.  
* Pokemon can be encountered in trees by interacting with them. Functionally this is like Headbutt trees without the need for headbutt.  
* The Pokedex contains expanded Pokemon information, such as level-up moves.  
* Talking to the man in the center square of Oldale Town gives access to using Fly from the menu.   
* Pokemon Centers have a counter lady who as of now performs two functions:  
  * Teaches tutor moves. These moves may be limited depending on [mode options](#mode-options).  
  *  Advances time by 8 hours (player takes a nap). This mainly serves for time of day evolutions, but using this feature 3 times also moves the day forward for daily events.  
* An intentional choice has been made to not include a Pokevial item. But money yields make purchasing healing items not too costly, and the box link does still give some convenience.  
* New Locations so far: Oldale Ruins (to Oldale Town’s right), Petalburg Grove (below Petalburg City), and Rustboro Sandfront (to the left of Route 115).  
* The right end of Oldale Town contains the Tech House, which includes niche but free (even in Resource Mode) tutor moves and abilities.   
  * Current List of abilities tutorable by the Psychic in Tech House: Keen Eye, Damp, Long Reach, Illuminate, Stalwart, Propeller Tail, Klutz, Light Metal, Rivalry, and Stakeout. This Psychic serves as a means to avoid using Ability Capsules or Ability Patches for niche abilities.  
* The gen 9 catch rate boost to low-level Pokemon (below level 13\) is in effect, and this catch rate multiplier makes the hidden Quick Ball in Route 104 a guaranteed catch on most pokemon. This can serve as a fail-safe for one cumbersome early encounter.   
* Devon Corp First Floor now has an elderly man who changes IVs based on Bottle Caps. The custom Plain Bottle Caps is a more abundant variant that sets a single stat’s IVs to 15\. The player begins with a dozen Plain Bottle Caps in their PC.  
* Gym Leaders now have the option to be battled in either Single or Double battles.

# Mode Options {#mode-options}

## Monotype Mode

The player has the choice to choose one of the 18 monotypes to specialize in. This choice lasts until the post-game, and affects numerous aspects of the game.

### Monotype Starters

| Mono Bug: Sewaddle | Mono Poison: Ekans | Mono Flying: Fletchling |
| :---- | :---- | :---- |
| Mono Grass: Treecko | Mono Fire: Torchic | Mono Water: Mudkip |
| Mono Dark: Houndour | Mono Fighting: Timburr | Mono Fairy: Fidough |
| Mono Ground: Sandshrew | Mono Rock: Nacli | Mono Steel: Sandshrew-alola |
| Mono Normal: Lillipup | Mono Psychic: Drowzee | Mono Ghost: Gastly |
| Mono Dragon: Gible | Mono Electric: Pawmi | Mono Ice: Sandshrew-Alola |

Some of the constraints for choosing a starter were that it does not evolve by Roxanne’s level cap (15), but it does evolve within Wattson’s level cap (26). 

### Rival Teams

The rival still only has 3 teams, but the teams are cycled between different monotypes. 

The Torchic team is used in Mono Normal, Grass, Dark, Bug, Ice, and Steel. 

The Mudkip team is used in Mono Flying, Poison, Rock, Ghost, Fire, and Fairy. (Fairy is chosen because one of the Swampert sets will have Iron Tail. Ghost is chosen because Combusken’s secondary STAB doesn’t match up well against the type, whereas Treecko’s STAB doesn’t match up well against Ghost’s starter.)

The Treecko team is used in  Mono Water, Ground, Electric, Psychic, Dragon, and Fighting. (Psychic, Dragon, and Fighting chosen because Sceptile’s sets will occasionally include Dark, Dragon, and Flying coverage).   
 

### Monotype Encounters

The encounter table is different between Monotype runs and non-monotype runs. Each monotype effectively has a different table. In most encounter forms, it will not be possible for the player to encounter a Pokemon that is not of the designated type, unless it evolves to a Pokemon of that type. 

There is an exception for specifically fishing, because there were complications in generating no fishing encounter due to the nibble mechanics. When there is no valid Pokemon of the monotype while fishing, Magikarp will be encountered instead. In Monotypes that are not Water or Flying, Magikarp won't evolve, so it serves as pure filler.

Gender-evolution Pokemon can have a guaranteed wild encounter gender in some monotypes. For example, wild Snorunt in Mono Ghost will always be female to be Frosslass evolution viable. And likewise, Wurmple will always evolve into Cascoon in Mono Poison. 

Evolutions are also prohibited when they do not align with the monotype. For example, Fletchling in Mono Normal cannot evolve.

### Monotype Tera Types

The player is unable to tera out of the Monotype, but Stellar is still permissible since it does not change types.

### Misc Monotype Comments

* Some Boss trainers have 2 teams, one meant for non-Monotype and favorable monotype matchups, and one meant for less favorable monotype matchups. For example, Mono Water fights a 4-Pokemon Roxanne team, whereas Mono Ice fights a 3-Pokemon Roxanne team.   
* In Resource Mode, certain aspects can be more accommodating in Monotype Mode than in non-Monotype mode. Monotype can get more of a given reward item, or more tutor move points after beating a gym. If the player is not playing Resource mode, then this aspect is unchanged between Monotype and non-Monotype.  
* Monotype currently has a minimum catch rate of 75, though eventually there may be a full custom list of individual catch rate changes in monotype. The main purpose of this is to make the early pseudo-legendaries more manageable. Non-monotype does not access the pseudo-legendaries quite as early, so it can handle the capture difficulties there.  
    
    
    
  


## Restricted Mode

This mode adds several restrictions:

* Certain moves (mostly setup moves) are excluded from Move Tutor selections.  
* Items can’t be used from the bag during trainer battles.  
* Certain Pokemon have additional evolution clauses. For example, many friendship evolutions gain a minimum level to evolve.  
* Certain Pokemon are incompatible from using Ability Patches (e.g. Salamence line and Moxie). Some Pokemon are not compatible with Ability Patches until certain progression points. The [PokemonList Sheet](https://docs.google.com/spreadsheets/d/1w00UPV-e9T6S0IAVSUsqH232ncC6fKQn9mSTrP3aMPY/edit?gid=137589446) mentions these occurrences on the applicable Pokemon.   
* Some Pokemon have altered Evolution moves. For example, Skelidirge loses Torch Song for Inferno. (Torch Song may still be level-up near the endgame, but it won’t be evolution-level available in Restricted Mode.)  
* Item Clause is enforced in Gym Battles.   
* Using the Box Link is prohibited in the Pokemon League.  
* Certain Pokemon are prohibited from Terastallizing. 

## Resource Mode

Choosing this mode constrains resources in several ways:

* Consumable items do not regenerate.  
* Several daily events only occur once.   
* Berries cannot be planted.   
* There is a limit to the total number of tutor moves (aside from the Tech Tutor).  
* There is a limit to the total number of relearner moves.  
* TMs deplete after use.  
* The player can only get 1 of the 3 Choice Items.   
* Nature Mints, Bottle Caps, Ability Capsules, and Ability Patches are in limited supply.  
* Mirror Herbs deplete after they yield an egg move

## Curated Tera Types

(Keep in mind that this mode does not have an impact in the current release, since the Tera Orb is only player accessible post-Brawly.)

Choosing this option results in Tera Types being fixed and handpicked for a given Pokemon. This enables the mechanic to add an extra layer of differentiation between Pokemon based on the Tera Type that is definitively assigned to them. 

If this mode is not chosen, Tera Types will be randomly generated based on Personality Type. 

## Level Caps

Choosing Level Cap mode enforces level caps. The intended level cap is the cap at which exp candies and rare candies stop working, but the player can still level-up an additional time before exp becomes 0\. This is mainly to still preserve exp management for nuzlockes, but a casual player can also simply just play at the level where exp becomes 0\. 

In addition to main boss level caps, there are level caps from intermediate trainers. 

Current Level Caps:

* Until beating Lass Tiana (Route 102): 8  
* Until beating Petalburg Aqua Grunt: 11  
* Until beating Collector Darren (Route 104, below Rustboro): 13  
* Until beating Roxanne: 15  
* Until beating Brawly: 19

# 

# 

# 

# 

# 

## 

## EV Mode

If EV mode is enabled, the player can gain EVs and trainers will have them. EV mode operates on EV caps between progression. The total EV cap is `2 * individual-stat EV cap + 4`. 

* 0 badges: individual-stat EV cap of 36; total EV cap of 76  
* 1 badge: individual-stat EV cap of 48; total EV cap of 100  
* 2 badges: individual-stat EV cap of 84; total EV cap of 172  
* 3 badges: individual-stat EV cap of 120; total EV cap of 244  
* 4 badges: individual-stat EV cap of 156; total EV cap of 316  
* 5 badges: individual-stat EV cap of 192; total EV cap of 388  
* 6 badges: individual-stat EV cap of 228; total EV cap of 460  
* 7 badges: individual-stat EV cap of 252; total EV cap of 508

# 

# 

# 

# 

# 

# 

# EXP and Money

## Money

The player starts with $15k instead of the usual $3k. 

Trainer money yields are overall higher because money yields are now computed based on sum of the trainers levels, rather than the original approach of using the level of the trainer’s last slot. 

Route 104 also has Lady Cindy who’s a rematchable trainer, and she uses Happy Hour turn 1, which has been modified to apply to the winner rather than only the using player. Her team does progress at certain points in the game, which helps maintain a sufficient money yield for all portions of the game.

Many items that don’t fulfill much of a function beyond selling have had their sell prices increase.

## EXP

Marts sell Exp.Candy which helps with grinding. The ease of acquiring money helps make grinding quite minimal. 

When it comes to exp gain when multiple Pokemon took part in a battle, I’ve implemented a linearly interpolated approach, where when the player has 0 badges, exp is evenly split, and when the player has 8 badges, all participants get the full exp. When the player has 4 badges and 2 Pokemon took part in a battle, the scaling means each one gets 0.75x of the experience they would have gotten if they battled solo. The reason for this approach is that the modern gen implementation of every participant getting full experience immediately makes the early exp gains a little too high, but by the late-game, such exp gains are welcome.

## EVs

Feathers cost $300 and now increment by 4 EVs instead of 1\. Mochis cost $2500 and now increment by 40 EVs. Vitamins cost $6000 and now increment by 100 EVs. 

Given the Money yields that can be quickly acquired, this helps EVs be trained very quickly. 

 

# AI

A lot of the custom AI logic is heavily specific, and as such, notes about AI as it pertains to particular trainers have been noted in the Trainer Document. 

One of the key adjustments is that the best damaging move gets \+1 score, rather than all the other moves getting \-1 score, and if two moves take the same number of hits to KO, priority is given to the one with the better effect or accuracy. Additionally, a best damaging move that is heavily disincentivized due to other logic will be ignored and the next best damaging move will take the \+1 score spot. 

The current tera logic is centered around the STABs of the player’s Pokemon. 

* If both the player Pokemon’s STABs are SE against the non-tera type, the AI will tera.  
* If none of the player Pokemon’s STABs are SE against the AI’s current typing, and at least one of the player’s types is SE against the Tera Type, AI will not Tera.   
* If both of the player Pokemon’s STABs are resisted or worse by the AI’s current typing, and the Tera type is not resisted by at least one of the AI’s types, the AI will not tera.   
* In scenarios apart from the ones listed above, AI will tera. 

## 

## 

## 

## 

## 

## 

## Key Doubles AI Elements

When an AI mon is targeting a player mon, it will do a check on whether it should prioritize targeting the other player mon. If it should, then the \+1 score for best damaging move on the current player target does not apply. This is the case if either the ally mon is flagged to KO this player mon, or the AI mon takes 2 or more additional hits to KO this player mon compared to the other player mon.

Speed Preference Function: for a given AI mon, the result of this function will be the slower player mon if the AI mon outspeeds one player mon and underspeeds the other. Otherwise, the result will be the faster player mon, or the player mon facing the AI mon if the player mons speed tie. 

There’s a hierarchy of targeting when AI mons see KOs, to help with damage efficiency.  
Let A1 and A2 be the two AI mons, and P1 and P2 be the two player mons:

* Suppose both A1 and A2 see KO on P1 but do not see KO on P2. The Pokemon out of A1 and A2 requiring more hits to KO P2 will be designated to KO P1, and the other one will not get score points for being able to KO P1, or get a \+1 score for its highest damaging move against P1. In the event that A1 and A2 take the same number of hits to KO P2, the faster mon will take precedence. If the speeds are also a tie, then the AI mon with the lower slot ID will take precedence (but this should rarely come up and exists as a definitive tie breaker).  
* Suppose A1 and A2 both see KO on both P1 and P2. Let AFaster be the faster of A1 and A2, and let ASlower be the slower of the two (if speed tied, AFaster is the one with the lower slot ID). AFaster designates its KO based on the result of applying the Speed Preference function using it as the AI mon input. ASlower will select the opposite target of AFaster.  
* If a)both AI mons see KOs on distinct player mons, or b) if one AI mon sees KO on exactly one player mon and the other sees no KOs, or c) one AI mon sees KO on both player mons while the other sees KO on only one mon, then the choices are simply KO maximization. Keep in mind in the case of b), the AI mon that sees no KOs will not get the \+1 for highest damage against the target that the other AI mon is flagged to KO. 

