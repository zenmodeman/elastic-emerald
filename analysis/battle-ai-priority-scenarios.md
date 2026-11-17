# Battle AI: 200 priority design scenarios

A workbook for deciding what satisfying opponent play should look like in Elastic Emerald. These are questions, not recommendations or descriptions of implemented behavior. Your answers may later inform AI changes; unanswered questions authorize no behavior changes.

## How to use this workbook

Work roughly in ID order. Earlier batches prioritize foundational policies and common, consequential decisions; later batches add team planning, doubles, and specialized interactions. This is a qualitative design priority order, not a measured ranking of encounter frequency. A doubles-focused design pass can start with AI-141–170 after the foundational questions.

Each stable ID identifies one decision boundary. In **My thoughts**, describe the behavior you would enjoy, alternatives you would tolerate, and any exceptions. Where useful, say what player strategy should be rewarded, what evidence the AI may use, whether behavior should be guaranteed or probabilistic, and whether trainer strength should matter. “Unsure” and “leave this exploitable” are valid answers. Numerical thresholds are optional.

Assume singles, equal levels, and a strong ordinary trainer unless stated otherwise. AI means the opponent; player means you. The AI knows its own team and selected ally actions. Player information is revealed only as stated, with inference and item knowledge intentionally left open where relevant. Stated damage, survival, legality, and turn order define the hypothetical fixture; they are not results from running the game. No unstated critical hit, miss, switch, or hidden move is guaranteed. A “safe” action is safe against the specified evidence, not every possible unseen option.

Pokémon are concrete illustrations, not assertions about authored trainer teams, encounter availability, or current learnset compatibility. Proposed combinations must be checked against Elastic mechanics before implementation. If a move, ability, or item differs here from mainline Pokémon, the Elastic runtime is authoritative. Endgame trades must use the game's actual victory resolution rather than assuming a draw.

## Review baseline and limits

Prepared against repository HEAD `36f677bbe58c5ac15cd2dc75f5f6064ea58baed1` (uncommitted workbook). Reviewed the AI skill, its behavior summary, AI flags/configuration, selected knowledge/switching source paths, and relevant Elastic history. This is a design elicitation set, not an exhaustive code audit, balance study, or validation of all examples. No builds or battle tests were run.

Elastic-specific context informed the questions without being treated as an immutable specification:

- Matchup commitment replaced broader fast-KO switching experiments (`53239d220d`, with later refinements described in the AI reference).
- General player-switch simulation was suppressed while the observed-switch immunity path remained; explicit trainer Tera assignment gates eligibility (`58c29f391e`).
- Hidden STAB assumptions were separated from revealed move/effect knowledge (`db9df93b11`); the Elastic knowledge profile includes item omniscience (`3b01725fcc`). These policies are deliberately open for reconsideration below.
- Existing configuration and inherited Expansion heuristics show implementation choices, not evidence of your preferred play. Stale “uncommitted” labels in the behavior summary are not used as commit-status authority here.

Reference: [AI behavior summary](../skills/modify-elastic-emerald-ai-logic/references/behavior-summary.md). Only the narrow source/history areas above were reviewed; the summary's broader audit baseline is not advanced by this workbook.

## Priority map

| IDs | Focus |
| --- | --- |
| 001–040 | Information, player agency, switching commitment, prediction |
| 041–080 | Attacks, turn order, setup, disruption |
| 081–120 | Recovery, residual pressure, hazards, switch-ins |
| 121–140 | Team resources, weather, terrain, Tera |
| 141–170 | Doubles targeting, support, coordinated plans |
| 171–200 | Elastic mechanics, unusual tactics, trainer identity and consistency |

## General policy notes

Use this space for principles that should apply across several scenarios. Keep individual answers attached to their stable IDs; if two answers conflict, note which should take precedence.

> 
> 

## 01 · Information and fairness (001–010)

### AI-001: Unrevealed coverage surprise

**Situation:** The player's Gyarados has shown only Waterfall. The AI's Grass-type can win unless Gyarados carries an unrevealed coverage attack.

**Decision to consider:** What kinds of coverage, if any, may the AI anticipate before revelation, and should the player's surprise set earn a free opening?

**My thoughts:**

> Eliminating Hidden STAB (so it doesn't have a move like Bounce, but maybe it has Temper Flare), in general, coverage should not be considered if it is not revealed. One thing that might be worth making sure is that Forewarn revealed coverage moves are properly treated as revealed moves.
> Rare cases are when a Pokemon has a meaningful non-STAB signature or semi-signature move, e.g. Archaludon with Electro Shot; such cases can be handled with case-by-case exceptions. In the case of Electro Shot, it is also a recharge move so it would only be revealed if the mon is known to hold a Power Herb or Rain is up.
> In the event that the player mon is holding a Mega Stone and the player mon is elligible to mega still, any gained STABs from the mega will be factored into hidden STAB. For example, a Gyrados with the mega stone equipped will include Crunch as a hidden STAB move, even if it hasn't Mega'd yet, so long as it is possible for it to Mega. So a non-Mega'd Gyarados will have 3 possible hidden STAB types, but once it has mega'd, Flying loses its Hidden STAB applicability.

### AI-002: Hidden STAB threat

**Situation:** A newly seen Garchomp threatens the AI's Electric-type, but has revealed no attacks.

**Decision to consider:** May the AI estimate an unseen Ground STAB attack, and should that estimate justify switching as strongly as a revealed Earthquake?

**My thoughts:**

> As per my approach to hidden STAB, yes the AI should estimate the damage, but not be privy to the specific move. Hardcoded exceptions apply for specific classes of moves that are a little conditional to be treated as normal (e.g. Recharge attacks or 2-turn moves when their 2-turn properties would not be ignorable). 
> Considerations to switch out based on KO should apply the same for Hidden STAB estimations and revealed moves. Pokemon that underspeed and KO will not trigger the switch mechanisms because I want to reward slow Pokemon that are required to take hits before they can get value. For fast KOs, my commitment mechnanism applies. The AI mon will not switch out if it has successfully landed a move on a target it was expecting to target at least once after it had switched in; if the move fails, is blocked by Protect, or the mon switches before the move lands, then the commitment hasn't occurred. For now, I'm thinking hitting a substitute on a non-switch still counts for a commit. If a mon has committed, it will not switch out despite being outsped and OHKO'd. However, I'm thinking AI mons that underspeed and have Regenerator can switch out despite meeting the commit check, so long as they would get the full healing amount from Regenerator. 
> Outspeed OHKO checks will only apply to mons with 80% or more HP, unless they have regenerator where the condition is instead just that they can obtain the full regenerator healing amount. Of course, the switch check only has an RNG chance to happen rather than being guarenteed (currently going with 50% change), and the switch check still has to consider that there are good switch-ins that don't trivially just die to the expected hit damage, followed by being outsped and OHKO'd after switch-in (this also would consider hazard damage if applicable).


### AI-003: Inferred damage versus inferred effects

**Situation:** The AI estimates damage from an unrevealed Fighting STAB on Lucario. Its own team has Reflect active; Brick Break has never been shown.

**Decision to consider:** Should an offensive damage assumption also let the AI anticipate screen removal, or must that strategic effect be revealed separately?

**My thoughts:**

> In general, the AI should not have knowledge of hidden moves in terms of their precise effects. I may later consider that signature moves in particular can have their explicit moves known (e.g. Spirit Break on Grimmsnarl), since knowing Grimmsnarl has Spirit Break is a very reasonable assumption, but I'll refrain from that initially. 
> 

### AI-004: Exact hidden item knowledge

**Situation:** The player's full-health Dragonite has not exposed its item. Whether it has a damage booster changes the AI's survival estimate.

**Decision to consider:** Should strong trainers know the exact item immediately, infer a shortlist, or wait for evidence? Would the same rule apply to unseen reserves?

**My thoughts:**

> I'm currently going with items being known. This should just be covered by the specific flag. 
> 

### AI-005: Ability guessing

**Situation:** The player's Pokémon has several legal abilities. One makes the AI's preferred attack ineffective; none has been revealed.

**Decision to consider:** Should the AI favor the common ability, hedge between possibilities, or risk the attack until it learns? What makes a guess fair?

**My thoughts:**

> Ability guessing should be performed, but it can use the weighted mechanism Expansion has. Down the line, more specific ability guesses might be something to add, like the AI guessing Sand Veil if it misses on a Garchomp in Sand whose item isn't Brightpowder or similar things and there aren't additional evasion mechanisms in play. This would most likely have to be done with a combination of specific case assumptions for certain abilities, and only if other possible abilities do not also give away that information.
> 

### AI-006: Unseen party information

**Situation:** The player has shown two Pokémon. A third, unrevealed teammate would perfectly counter the AI's setup sweeper.

**Decision to consider:** Should the AI plan only around seen species, assume generic remaining threats, or know roster identities? How much should concealing a reserve matter?

**My thoughts:**

> For now, no consideration for unrevealed player party Pokemon.
> 

### AI-007: Reading the player's selected action

**Situation:** The player chooses a status move while facing an AI Sucker Punch user. No previous turn establishes a pattern.

**Decision to consider:** What information may inform the AI's Sucker Punch decision? Specify the boundary between prediction and access to the actual submitted action.

**My thoughts:**

> For simplicity, I'm thinking in the general case, Sucker Punch should not be disincentivized before the AI mon has used the move at least once in the previous 3 turns, unless it knows that the player mon has no moves that could trigger Sucker Punch. 
> If Sucker Punch was used in the previous turn, the AI mon will take a 50% chance to disincentivize the move the next turn. If Sucker Punch has been used N (2 or 3) turns ago, the 50% RNG disincentive check only occurs if the player mon has used a status move within N turns, or the player mon has no previous turn moves (because it swithced in last turn). 


### AI-008: Unexpected damage as evidence

**Situation:** A revealed neutral attack deals much more damage than the AI expected, consistent with a boost item or an unusual offensive spread.

**Decision to consider:** How much may the AI infer from this hit, and should it keep multiple explanations until more evidence arrives?

**My thoughts:**

> The standard AI will involve the AI knowing the player mon's stats and held item, so no inference is needed for these. But inference makes sense when only one of the player mon's possible abilities could account for that unexpected damage. In the case of such an inference, the ability can be set to the AI knowing what it is in that case. E.g. Azumarill could only do the damage it showed if it has Huge Power.
> 

### AI-009: Remembering through switches

**Situation:** The player reveals Ice Beam, switches out, and brings the same Pokémon back several turns later.

**Decision to consider:** What knowledge should persist across switches, and which temporary properties must be forgotten or refreshed?

**My thoughts:**

> Revealed or inferred information should persist across switches, including things like knowing Azumarill has Huge Power based on damage. 
> 

### AI-010: Learning across rematches

**Situation:** The player loses to a boss and retries with the same unusual strategy, then changes one hidden move.

**Decision to consider:** Should the boss remember the previous attempt, reset completely, or have an explicitly signaled adaptive mode? How should changed sets be treated?

**My thoughts:**

> For simplicity, no retaining information from previous fights (which can also be rationalized by the possibility that the player changed sets)
> 


## 02 · Rewarding player-created openings (011–020)

### AI-011: Speed-control payoff

**Situation:** The player's Rock Tomb makes a previously faster AI attacker slower and vulnerable to a follow-up KO. The AI has already attacked successfully in this matchup.

**Decision to consider:** Should the AI accept the changed matchup, escape immediately, or sometimes escape? How much payoff should the setup turn buy?

**My thoughts:**

> 
> 

### AI-012: Defensive-drop payoff

**Situation:** The player spends a turn using Screech on a healthy physical wall rather than attacking. A subsequent attack now threatens a KO.

**Decision to consider:** Should a switch erase this investment routinely, only under special conditions, or rarely? Does it matter whether Screech also dealt damage?

**My thoughts:**

> 
> 

### AI-013: Type-changing trap

**Situation:** The player uses Soak on an AI defender to enable a subsequent Electric attack. Before Soak, the AI was comfortable staying in.

**Decision to consider:** Should the AI recognize and flee the planned combo, remain committed, or require evidence of the follow-up attack first?

**My thoughts:**

> 
> 

### AI-014: Ability-removal payoff

**Situation:** The player suppresses a defensive ability that had made the AI Pokémon difficult to damage.

**Decision to consider:** How readily should the AI switch to restore its ability, and should deliberate ability manipulation be rewarded differently from ordinary damage pressure?

**My thoughts:**

> 
> 

### AI-015: Grounding an immunity

**Situation:** The player uses a legal grounding effect to make an airborne AI Pokémon vulnerable to Ground attacks.

**Decision to consider:** Should the AI treat this as a newly losing matchup that warrants switching, or as a tactical success the player should usually exploit?

**My thoughts:**

> 
> 

### AI-016: Encore into harmless setup

**Situation:** The player successfully Encores an AI Pokémon into a setup move that no longer helps. A viable reserve exists.

**Decision to consider:** Should the AI reliably switch, sometimes remain trapped, or distinguish ordinary Encore punishment from a complete no-progress loop?

**My thoughts:**

> 
> 

### AI-017: Disable removes the only answer

**Situation:** The player Disables the AI's only move that meaningfully threatens the active target, leaving weak but usable attacks.

**Decision to consider:** How weak must the remaining plan be before switching is appropriate, and should the player still earn at least one advantageous turn?

**My thoughts:**

> 
> 

### AI-018: Taunt against a support specialist

**Situation:** The player Taunts an AI support Pokémon whose only damaging move is weak. Its team still needs the support later.

**Decision to consider:** Should it attack, switch, or accept being expendable? What separates a reasonable escape from negating the player's disruption?

**My thoughts:**

> 
> 

### AI-019: Protect as a scouting reward

**Situation:** The player uses Protect to discover an AI attack and can now bring in a resistance next turn.

**Decision to consider:** How much should the AI vary its follow-up after being scouted, and should it need observed switching before anticipating the counter?

**My thoughts:**

> 
> 

### AI-020: Creative combo discovered late

**Situation:** The player reveals an unusual two-move interaction that bypasses the AI's normal defense and wins a KO.

**Decision to consider:** Should the AI immediately adapt for remaining teammates, require repetition, or preserve the strategy's usefulness for the rest of the battle?

**My thoughts:**

> 
> 


## 03 · Commitment and voluntary switching (021–030)

### AI-021: Bad matchup on first contact

**Situation:** A healthy AI Pokémon faces a faster player attacker whose revealed move guarantees a KO. The AI has not yet acted successfully against it, and a safe reserve exists.

**Decision to consider:** Should it switch reliably, probabilistically, or stay to make the encounter less evasive? What evidence and HP conditions should matter?

**My thoughts:**

> 
> 

### AI-022: Bad matchup after commitment

**Situation:** Use the same lethal position as AI-021, but the AI successfully attacked this opponent on an earlier turn without a player switch.

**Decision to consider:** Should that prior commitment change its willingness to escape, even though the present damage calculation is identical?

**My thoughts:**

> 
> 

### AI-023: Commitment after a self-targeting move

**Situation:** The AI used Recover successfully while the player stayed in. On the following turn, it faces a faster KO threat.

**Decision to consider:** Should recovery establish commitment as strongly as a successful attack? Would Protect or weather setup count the same way?

**My thoughts:**

> 
> 

### AI-024: Failed action and commitment

**Situation:** The AI tried to attack, but the player blocked it with Protect. Next turn the same faster KO threat remains.

**Decision to consider:** Should merely attempting an action establish commitment, or should a miss, immunity, Protect, and other failures preserve an escape opportunity?

**My thoughts:**

> 
> 

### AI-025: Player pivot after the AI acts

**Situation:** The AI attacks successfully, then a slower player pivot brings in a counter before the turn ends.

**Decision to consider:** Should the AI be committed to the old matchup, the new one, or neither? How much opportunity should slow pivoting create?

**My thoughts:**

> 
> 

### AI-026: Sacrificing a healthy attacker

**Situation:** The AI can switch a threatened healthy attacker into a safe wall, but staying would deal useful damage before eventually fainting.

**Decision to consider:** How should it weigh preserving material against making progress and keeping the battle moving?

**My thoughts:**

> 
> 

### AI-027: Low-health escape

**Situation:** An AI Pokémon at low HP cannot act before being KOed, but a resistance could take the incoming attack cheaply.

**Decision to consider:** Should low HP make it expendable, or should even a nearly fainted Pokémon be preserved when switching is cheap?

**My thoughts:**

> 
> 

### AI-028: Regenerator exception

**Situation:** A threatened Regenerator Pokémon can escape, heal, and become useful again. A non-Regenerator Pokémon in the same position would stay.

**Decision to consider:** How much extra switching should the ability justify, and when does repeated regeneration become frustrating rather than satisfying opposition?

**My thoughts:**

> 
> 

### AI-029: Boosted attacker facing danger

**Situation:** The AI has invested two turns in setup. A newly revealed player attack now threatens to remove it before it can move.

**Decision to consider:** Should it protect the boosts by attacking, abandon them by switching, or use survival odds and remaining sweep potential to decide?

**My thoughts:**

> 
> 

### AI-030: No genuinely safe reserve

**Situation:** The active AI Pokémon loses its matchup, but every replacement takes heavy damage or creates another losing position.

**Decision to consider:** Should it still switch to improve the odds slightly, or stay and trade damage? What prevents purposeless switching?

**My thoughts:**

> 
> 


## 04 · Prediction, adaptation, and exploitable patterns (031–040)

### AI-031: First immunity pivot

**Situation:** The AI's Electric attack threatens a KO, and the player has previously shown a Ground-type reserve but has not yet pivoted it into this attack.

**Decision to consider:** Should the AI take the obvious attack or immediately predict the immune switch? How much initial counterplay should the player receive?

**My thoughts:**

> 
> 

### AI-032: Repeated immunity cycling

**Situation:** The player repeatedly alternates a Ground-type and a Flying-type to blank the AI's Electric and Ground attacks.

**Decision to consider:** When should the AI adapt, what evidence should count, and how often should it still choose the straightforward attack?

**My thoughts:**

> 
> 

### AI-033: Coverage prediction has a cost

**Situation:** The AI can hit a predicted Ground-type switch with coverage, but that move loses badly if the active Water-type stays in.

**Decision to consider:** What confidence or payoff should justify abandoning the strong current-target move? Should a prediction ever be mandatory?

**My thoughts:**

> 
> 

### AI-034: Unseen immune reserve

**Situation:** The player has not revealed a Ground-type, but actually has one in reserve. The AI's Electric move is otherwise strongest.

**Decision to consider:** Should adaptation be limited to observed candidates, even after many switches, or may generic roster expectations justify an immunity prediction?

**My thoughts:**

> 
> 

### AI-035: Double switch

**Situation:** The AI expects the player to switch to a revealed wall and could switch simultaneously to its own wallbreaker.

**Decision to consider:** Should voluntary double switches exist for ordinary smart trainers, and how much uncertainty should prevent them?

**My thoughts:**

> 
> 

### AI-036: Predicting a setup turn

**Situation:** The player has repeatedly used Dragon Dance after forcing this matchup. The AI can punish setup or defend against an immediate attack.

**Decision to consider:** Should history alter the decision, and how quickly should the AI stop trusting the pattern when the player changes plans?

**My thoughts:**

> 
> 

### AI-037: Predicting recovery

**Situation:** A player wall is in recovery range. Taunt punishes Recover, while direct damage is better if it attacks.

**Decision to consider:** How should the AI balance the obvious immediate threat against a likely recovery turn without reading the selected move?

**My thoughts:**

> 
> 

### AI-038: Sucker Punch mind game

**Situation:** Both sides know that AI Sucker Punch wins against an attack but fails against the player's status move. The AI has a weaker unconditional attack.

**Decision to consider:** Should this be random, history-sensitive, or mostly deterministic? What makes the player feel they outplayed the opponent?

**My thoughts:**

> 
> 

### AI-039: History stops being relevant

**Situation:** The player used the same switch three times, then reveals that the old recipient is now too weak to survive entry hazards.

**Decision to consider:** How quickly should the AI discard its learned pattern when public state changes make that pattern unattractive?

**My thoughts:**

> 
> 

### AI-040: Repeated battle-state loop

**Situation:** The battle returns to the same active Pokémon, HP bands, and available moves several times because both sides keep pivoting.

**Decision to consider:** Should the AI deliberately break the loop at some cost, and which repeatable player strategies should remain legitimate rather than trigger adaptation?

**My thoughts:**

> 
> 


## 05 · Damage, reliability, and immediate KOs (041–050)

### AI-041: Two guaranteed finishing moves

**Situation:** The target has little HP. Both an accurate weak attack and a powerful attack guarantee a KO; neither has a relevant secondary effect.

**Decision to consider:** Should accuracy, PP, contact risk, or information concealment decide, and should excess damage ever matter?

**My thoughts:**

> 
> 

### AI-042: Reliable two-hit line versus risky KO

**Situation:** An accurate attack guarantees a two-hit KO if the AI survives, while an inaccurate attack can KO immediately but loses on a miss.

**Decision to consider:** How should survival, remaining team size, and player pressure change the willingness to gamble?

**My thoughts:**

> 
> 

### AI-043: Damage-roll KO

**Situation:** One attack KOs only on high damage rolls; another guarantees useful chip but never KOs immediately.

**Decision to consider:** Should the AI reason in KO probabilities, a preferred representative roll, or a conservative threshold? What risk feels fair when it is ahead versus behind?

**My thoughts:**

> 
> 

### AI-044: Same hit count, different damage

**Situation:** Two moves both need three hits against the current target, but one deals substantially more damage and helps a teammate finish it.

**Decision to consider:** How much should meaningful chip break a nominal hits-to-KO tie, especially if the target can switch or heal?

**My thoughts:**

> 
> 

### AI-045: Guaranteed utility versus damage

**Situation:** A stronger attack and a weaker guaranteed stat-drop attack need the same number of hits. The drop could protect the AI on the next turn.

**Decision to consider:** When should useful utility outweigh raw damage, and should it lose its bonus if the target is already being KOed?

**My thoughts:**

> 
> 

### AI-046: Fishing for a secondary effect

**Situation:** A weaker attack has a small chance to burn or flinch; a stronger attack gives dependable progress.

**Decision to consider:** Should ordinary AI gamble on incidental effects, and should desperation or repeated failed attempts change its preference?

**My thoughts:**

> 
> 

### AI-047: Recoil on the finishing blow

**Situation:** The AI can KO with a recoil move but will faint from recoil. A weaker move leaves the target alive and may let it retaliate.

**Decision to consider:** When is the trade desirable, and how should last-Pokémon victory resolution alter the choice?

**My thoughts:**

> 
> 

### AI-048: Contact punishment

**Situation:** A contact attack KOs Ferrothorn but costs substantial HP through revealed contact punishment. A noncontact attack takes another turn.

**Decision to consider:** Should the AI pay HP to secure the KO, preserve its attacker, or compare the value of what remains afterward?

**My thoughts:**

> 
> 

### AI-049: Focus Sash and multi-hit attacks

**Situation:** A revealed Focus Sash would stop a single-hit KO. A multi-hit move can finish the target but has less reliable total damage.

**Decision to consider:** How strongly should the AI prefer bypassing the Sash, and should unrevealed item policy change that preference?

**My thoughts:**

> 
> 

### AI-050: Immune strongest attack

**Situation:** The AI's nominally strongest move is ineffective against a revealed immunity, while a weak coverage move makes progress.

**Decision to consider:** Should immunity always remove the move from consideration, or are there deliberate bluffing or prediction cases where selecting it remains acceptable?

**My thoughts:**

> 
> 


## 06 · Turn order and speed control (051–060)

### AI-051: Weak priority saves a turn

**Situation:** The AI is slower and will be KOed before its strongest move, but a weaker priority attack deals meaningful chip without KOing.

**Decision to consider:** Should it always take the chip, sometimes choose a predicted winning line, or prefer switching when available?

**My thoughts:**

> 
> 

### AI-052: Priority versus a slower KO

**Situation:** The AI's ordinary attack KOs if it gets to act; priority cannot KO, but guarantees damage before a faster revealed threat.

**Decision to consider:** How should it compare a likely loss with guaranteed chip against a lower-probability immediate win?

**My thoughts:**

> 
> 

### AI-053: Speed tie

**Situation:** Two attackers each KO the other and their effective Speeds are tied. The AI can instead choose weak priority or switch.

**Decision to consider:** Should it accept the tie, avoid it, or vary by how much the team needs the active Pokémon?

**My thoughts:**

> 
> 

### AI-054: Paralysis flips the matchup

**Situation:** Thunder Wave lets a slower AI attacker move first on later turns, and the AI survives the turn spent using it.

**Decision to consider:** How much should the change in turn order matter compared with attacking immediately, independent of full-paralysis luck?

**My thoughts:**

> 
> 

### AI-055: Speed drop without an immediate flip

**Situation:** Rock Tomb slows a very fast player attacker but does not make the current AI Pokémon faster. A reserve would benefit.

**Decision to consider:** Should future teammates justify the move, or should speed control usually require an immediate payoff?

**My thoughts:**

> 
> 

### AI-056: Boosting Speed beyond necessity

**Situation:** The AI already outspeeds the active target and can KO in two hits. An additional boost would help against a previously revealed faster reserve.

**Decision to consider:** When should known future threats justify extra setup over current damage?

**My thoughts:**

> 
> 

### AI-057: Tailwind with too little time

**Situation:** Tailwind would help several AI teammates, but its setter is likely to faint and the next turn may be spent switching.

**Decision to consider:** How many productive turns should the AI expect before treating temporary speed control as worthwhile?

**My thoughts:**

> 
> 

### AI-058: Trick Room reverses an advantage

**Situation:** The AI is slower than the current opponent but faster than most revealed reserves. Trick Room helps now and may hurt later.

**Decision to consider:** Should it prioritize the current matchup, the remaining roster, or reserve Trick Room for a dedicated slow attacker?

**My thoughts:**

> 
> 

### AI-059: Speed control versus priority offense

**Situation:** The player's main revealed finishing move has priority, so lowering ordinary Speed does not stop the immediate threat.

**Decision to consider:** Should the AI reject speed control entirely or value it for nonpriority moves and later matchups?

**My thoughts:**

> 
> 

### AI-060: Temporary speed effect expires

**Situation:** The player's Tailwind expires after this turn. The AI can spend a turn defending and then naturally outspeed next turn.

**Decision to consider:** How strongly should exact public expiration timing encourage stalling rather than attacking or applying new speed control?

**My thoughts:**

> 
> 


## 07 · Setup, sweeping, and overextension (061–070)

### AI-061: Free setup opportunity

**Situation:** The player is locked into a resisted weak attack. AI Dragon Dance would establish a strong winning position, while attacking makes modest progress.

**Decision to consider:** Should the AI reliably exploit the free turn, or leave some opportunities unused to preserve approachable play?

**My thoughts:**

> 
> 

### AI-062: Setup versus an available KO

**Situation:** The AI can KO now or use Swords Dance while surviving the target's known response. Boosting could threaten the next Pokémon.

**Decision to consider:** When should sweep potential justify giving up a guaranteed immediate removal?

**My thoughts:**

> 
> 

### AI-063: Setup into uncertain coverage

**Situation:** The player has revealed only passive moves, but has two unknown slots. The AI can safely boost against everything actually shown.

**Decision to consider:** How much should unknown information discourage setup, and should concealing offense successfully bait the AI?

**My thoughts:**

> 
> 

### AI-064: Boosting within a healing loop

**Situation:** A player wall heals off the AI's current damage. One boost would break the loop, but costs a turn of exposure.

**Decision to consider:** Should the AI actively seek the damage threshold needed to beat recovery instead of repeatedly attacking?

**My thoughts:**

> 
> 

### AI-065: Setup into revealed Haze

**Situation:** The player has already shown Haze and can use it safely. The AI also has a reasonable direct attack.

**Decision to consider:** Should boosting become forbidden, merely less likely, or return as an option after the player stops choosing Haze?

**My thoughts:**

> 
> 

### AI-066: Unaware and offensive setup

**Situation:** The player's Unaware ability is revealed. The AI's offensive boost would not improve damage against this target, but could help against reserves.

**Decision to consider:** When is setting up still purposeful, and should hidden-ability uncertainty produce a different choice?

**My thoughts:**

> 
> 

### AI-067: Belly Drum at real risk

**Situation:** Belly Drum creates a sweep threat but spends enough HP that a revealed attack may finish the AI that turn.

**Decision to consider:** What survival confidence and later payoff should be required for a high-cost setup plan?

**My thoughts:**

> 
> 

### AI-068: Shell Smash and defensive cost

**Situation:** Shell Smash makes the AI faster and stronger but newly vulnerable to revealed priority. A direct attack is safe but weaker.

**Decision to consider:** Should it reject the boost, accept the priority trade, or consider whether the player will actually choose the finisher?

**My thoughts:**

> 
> 

### AI-069: Substitute as an investment

**Situation:** A Substitute absorbs status or enables setup, but its HP cost brings the AI into range of a faster attack after it breaks.

**Decision to consider:** How should the AI value protection and information against the concrete loss of survival margin?

**My thoughts:**

> 
> 

### AI-070: Stop boosting and cash in

**Situation:** The AI already has enough boosts to KO the active target and threaten known reserves. Another boost improves only extreme future cases.

**Decision to consider:** What should make it stop setting up, and how should you distinguish sensible preparation from frustrating overboosting?

**My thoughts:**

> 
> 


## 08 · Disruption, stat drops, and denial (071–080)

### AI-071: Attack drop against physical pressure

**Situation:** Charm prevents a physical attacker from securing its next KO, while the AI's direct attack cannot finish it.

**Decision to consider:** Should preventing the KO outweigh immediate damage, and how should a likely player switch reduce the value of the drop?

**My thoughts:**

> 
> 

### AI-072: Wrong offensive stat

**Situation:** The player has revealed only special attacks, but its species can also run physical moves. The AI can lower Attack or deal useful damage.

**Decision to consider:** How much evidence should make an offensive-stat drop pointless, and should incomplete knowledge preserve a small chance of using it?

**My thoughts:**

> 
> 

### AI-073: Parting Shot as a combined action

**Situation:** Parting Shot weakens the player and brings in a teammate, but either stat drop alone has little value against the current target.

**Decision to consider:** Should the AI evaluate the safe transition as a whole, and when should direct damage beat this combined utility?

**My thoughts:**

> 
> 

### AI-074: Taunt before setup

**Situation:** The player's Dragon Dance is revealed, but its attacks are also threatening. AI Taunt prevents setup at the cost of immediate damage.

**Decision to consider:** When should denying a possible future sweep outweigh addressing the current attack threat?

**My thoughts:**

> 
> 

### AI-075: Encore after an attack

**Situation:** The player just used a resisted attack. Encore would lock it, but the player has several reserves and can switch.

**Decision to consider:** Should the AI value the forced switch and tempo even if it cannot trap the target?

**My thoughts:**

> 
> 

### AI-076: Punishment ability revealed

**Situation:** A revealed Defiant or Contrary interaction makes the AI's otherwise useful stat-lowering move benefit the player.

**Decision to consider:** Should the AI exclude the move, retain it for immediate KO damage, or ever accept the boost to obtain another important effect?

**My thoughts:**

> 
> 

### AI-077: Remove boosts or take damage

**Situation:** A boosted player attacker is dangerous. Haze or Clear Smog removes the boosts but does not prevent a hit this turn.

**Decision to consider:** How much survival margin should justify clearing boosts instead of switching, attacking, or making a sacrifice?

**My thoughts:**

> 
> 

### AI-078: Phazing a prepared sweeper

**Situation:** The player has accumulated several boosts behind a durable position. The AI can use a legal phazing move if it survives until execution.

**Decision to consider:** Should reliable boost removal take priority, and how should hazard damage or the risk of a worse replacement affect that choice?

**My thoughts:**

> 
> 

### AI-079: Disruption after its purpose expires

**Situation:** Taunt is available, but the target's known support move has no remaining useful target and its attacks are now the real threat.

**Decision to consider:** How carefully should the AI distinguish an available status move from one that still matters?

**My thoughts:**

> 
> 

### AI-080: Counterplay to disruptive player tech

**Situation:** The player repeatedly uses low-damage disruption that makes the AI's strongest move unattractive, without creating a guaranteed win.

**Decision to consider:** Should the AI tolerate the impaired plan, seek a new line, or eventually switch? What separates a clever soft lock from an unacceptable loop?

**My thoughts:**

> 
> 


## 09 · Recovery and defensive tempo (081–090)

### AI-081: Healing changes survival

**Situation:** AI Recover raises HP enough to survive the player's next known attack and retaliate afterward. Attacking now loses the AI Pokémon.

**Decision to consider:** Should recovery be strongly preferred, and how much uncertainty about damage should weaken that preference?

**My thoughts:**

> 
> 

### AI-082: Healing cannot save the user

**Situation:** Even after Recover, the player's faster revealed attack still guarantees a KO. Another AI move could at least deal damage.

**Decision to consider:** Should healing be excluded, or can a plausible predicted nonattack justify attempting it?

**My thoughts:**

> 
> 

### AI-083: Healing versus finishing

**Situation:** The AI can KO the active target now or heal safely while leaving that target alive. Its remaining opponents include a known threat.

**Decision to consider:** When should preserving HP for later beat removing an opponent immediately?

**My thoughts:**

> 
> 

### AI-084: Repeated recovery creates a wall

**Situation:** The player deals slightly less damage than the AI heals, so Recover can sustain a long loop but gains little progress.

**Decision to consider:** Should the AI keep healing, introduce a chance to attack, or impose a repetition limit? Which defensive player plans should this reward?

**My thoughts:**

> 
> 

### AI-085: Recovery under accelerating Toxic

**Situation:** Recover survives this turn, but increasing Toxic damage makes the same plan fail soon. Switching clears the escalation but exposes a teammate.

**Decision to consider:** How far ahead should the AI look before abandoning recovery, and should it spend one more heal to improve the transition?

**My thoughts:**

> 
> 

### AI-086: Slower recovery

**Situation:** A slow wall survives the incoming hit and can then Recover. If it attacks instead, the following hit will KO it.

**Decision to consider:** Should it evaluate post-hit HP explicitly, and how should a possible critical hit affect an otherwise sustainable line?

**My thoughts:**

> 
> 

### AI-087: Rest without immediate curing

**Situation:** Rest fully heals the AI but gives the player several opportunities while it sleeps. Its awake alternative is weak damage.

**Decision to consider:** What expected survival and eventual payoff make Rest reasonable, and should a player setup opportunity count heavily against it?

**My thoughts:**

> 
> 

### AI-088: Wish for a teammate

**Situation:** The AI can use Wish and later pass it to an injured reserve, but doing so requires surviving a turn and arranging a safe switch.

**Decision to consider:** How much planning should a strong ordinary trainer perform to execute the pass rather than use Wish only for itself?

**My thoughts:**

> 
> 

### AI-089: Protect secures public recovery

**Situation:** Protect guarantees a known end-of-turn recovery tick or Wish arrival, but gives the player room to set up.

**Decision to consider:** Should the AI normally take guaranteed healing, or account for setup pressure enough to break the expected Protect pattern?

**My thoughts:**

> 
> 

### AI-090: Healing item as a trainer turn

**Situation:** The trainer may spend a limited healing item to save a useful attacker. This consumes its action and may create another healing loop.

**Decision to consider:** When should item use be justified, and should its priorities differ from using a recovery move with renewable PP?

**My thoughts:**

> 
> 


## 10 · Status and residual win conditions (091–100)

### AI-091: Burn prevents a physical KO

**Situation:** Will-O-Wisp would let the AI survive a physical attacker but can miss. Its damaging move cannot KO the player.

**Decision to consider:** Should it favor the defensive status attempt, and how should this differ from emergency paralysis that relies on a full-paralysis roll?

**My thoughts:**

> 
> 

### AI-092: Status helps the opponent

**Situation:** The player has revealed Guts, Poison Heal, or another relevant status benefit. A normally useful status move would activate it.

**Decision to consider:** Should the AI avoid the status absolutely, or accept it when another consequence still wins the immediate exchange?

**My thoughts:**

> 
> 

### AI-093: Toxic against a recovery wall

**Situation:** Direct attacks cannot overcome the player's healing. Toxic creates eventual pressure if it lands and remains active.

**Decision to consider:** Should the AI recognize this as a primary win condition, and how should known cleansing or switching options reduce its value?

**My thoughts:**

> 
> 

### AI-094: Poison versus a more valuable status

**Situation:** The AI can poison now, but a teammate could later burn or paralyze the same target with greater strategic benefit.

**Decision to consider:** Should it reserve the status slot for a future plan, or take guaranteed present progress?

**My thoughts:**

> 
> 

### AI-095: Sleep as a free-turn engine

**Situation:** A legal sleep attempt could enable setup, but direct damage is already effective. The target has not shown a sleep counter.

**Decision to consider:** How aggressively should the AI pursue sleep, and how much setup should it attempt after sleep succeeds?

**My thoughts:**

> 
> 

### AI-096: Sleep Clause already blocks the plan

**Situation:** The applicable sleep rules make another sleep attempt fail while a previously affected player Pokémon remains asleep.

**Decision to consider:** Should the move be fully excluded, and should the AI actively plan around whether removing the sleeper will reopen the option?

**My thoughts:**

> 
> 

### AI-097: Leech Seed and immediate pressure

**Situation:** Leech Seed would create recovery and residual damage, but the AI can instead take a reliable two-hit KO with attacks.

**Decision to consider:** How long must the matchup be expected to last before seeding deserves the setup turn?

**My thoughts:**

> 
> 

### AI-098: Residual damage already secures the KO

**Situation:** The target will faint to established poison or binding damage at turn end if it remains active. The AI can defend, heal, or attack.

**Decision to consider:** Should it avoid redundant damage, and how much should a possible player switch keep an attack attractive?

**My thoughts:**

> 
> 

### AI-099: Binding as a long plan

**Situation:** A weak binding attack creates residual pressure and restricts escape. A stronger direct attack makes more immediate progress.

**Decision to consider:** Which future turns may the AI reasonably count on, and how should uncertain duration or escape options limit its valuation?

**My thoughts:**

> 
> 

### AI-100: Cure status or preserve momentum

**Situation:** The AI can remove a harmful status, but the status is currently tolerable and attacking keeps offensive pressure.

**Decision to consider:** What makes a status worth curing: immediate survival, long-term role, chance of lost turns, or some combination?

**My thoughts:**

> 
> 


## 11 · Entry hazards and field maintenance (101–110)

### AI-101: Opening hazards versus damage

**Situation:** The AI lead can set Stealth Rock safely or deal substantial damage immediately. Several player reserves remain unseen.

**Decision to consider:** How much future switching should justify hazards without knowing the full roster, and should dedicated leads behave differently?

**My thoughts:**

> 
> 

### AI-102: Hazards in a short endgame

**Situation:** Only one player Pokémon remains, already active. The AI's hazard move has no expected switch-in target.

**Decision to consider:** Should hazards be excluded unless a concrete forced-switch interaction exists, even if the trainer normally prioritizes them?

**My thoughts:**

> 
> 

### AI-103: Additional hazard layer

**Situation:** One layer is already active. Another layer adds future damage but costs a turn the AI could spend attacking.

**Decision to consider:** How should marginal benefit, remaining reserves, and expected entries determine whether to stack further?

**My thoughts:**

> 
> 

### AI-104: Known hazard immunity

**Situation:** The player's revealed remaining roster has effective ways to ignore the relevant entry hazard. The AI can still set it.

**Decision to consider:** Should the AI abandon that hazard, anticipate item removal or suppression, or continue only when a concrete plan makes it matter?

**My thoughts:**

> 
> 

### AI-105: Removal saves the reserve

**Situation:** Hazards would KO the AI's key reserve on entry. Its active remover can clear them now but may take heavy damage doing so.

**Decision to consider:** How much should it sacrifice to restore access to that teammate, and should the teammate's specific future role matter?

**My thoughts:**

> 
> 

### AI-106: Removal versus an immediate KO

**Situation:** The AI can KO the player now or clear hazards. Removing the player may prevent hazards being set again, but leaves the field dirty.

**Decision to consider:** Which action should win when both offer substantial team value, and what future cost should be compared?

**My thoughts:**

> 
> 

### AI-107: Removal repeatedly blocked

**Situation:** The player has demonstrated a reliable legal way to block the AI's hazard removal. Repeating removal gives away turns.

**Decision to consider:** How quickly should the AI stop retrying, and should it attack the blocker or predict its departure?

**My thoughts:**

> 
> 

### AI-108: Hazards versus repeated removal

**Situation:** The player has repeatedly removed the AI's hazards at low cost. The setter can attack or continue setting them.

**Decision to consider:** When should the AI accept that the hazard plan is not working, and should it ever deliberately exhaust removal PP?

**My thoughts:**

> 
> 

### AI-109: Hazard damage changes switching

**Situation:** The AI has a type-resistant reserve, but hazards plus the expected incoming attack would KO it. Staying active at least deals damage.

**Decision to consider:** Should entry cost override the apparent defensive matchup absolutely, and how much uncertain incoming damage can it risk?

**My thoughts:**

> 
> 

### AI-110: Toxic Spikes absorption

**Situation:** An AI Poison-type can legally absorb Toxic Spikes on entry, improving the whole team's position, but is a mediocre immediate matchup.

**Decision to consider:** Should clearing the field justify choosing it over a stronger combat replacement, and how much HP can it spend doing so?

**My thoughts:**

> 
> 


## 12 · Replacement selection, pivots, and sacrifices (111–120)

### AI-111: Replacement after a faint

**Situation:** The player just KOed the AI's active Pokémon. One reserve wins the immediate matchup; another is the team's best answer to a different revealed threat.

**Decision to consider:** Should replacement selection maximize the current matchup or preserve specialized answers for later?

**My thoughts:**

> 
> 

### AI-112: Revenge killer versus durable answer

**Situation:** A fast reserve can KO the weakened player but cannot take its attacks well. A slower wall handles it safely but gives less momentum.

**Decision to consider:** Which kind of replacement should be preferred, and how should remaining HP and known priority change the choice?

**My thoughts:**

> 
> 

### AI-113: Only answer to the sweeper

**Situation:** The AI's one reliable answer to a revealed player sweeper also makes the best switch into the current attack, but would become too weak afterward.

**Decision to consider:** Should it spend that answer for present safety or preserve it and sacrifice something less valuable?

**My thoughts:**

> 
> 

### AI-114: Choosing a sacrifice

**Situation:** Every switch-in is bad, and the active AI Pokémon is valuable later. One reserve has almost no remaining role.

**Decision to consider:** Should the AI deliberately sacrifice that reserve, and how much team-role reasoning is appropriate for ordinary strong trainers?

**My thoughts:**

> 
> 

### AI-115: U-turn with no useful destination

**Situation:** U-turn deals competitive damage, but every available replacement worsens the position. A nonpivot attack lets the AI stay.

**Decision to consider:** Should the pivot be penalized for its forced transition even when its immediate damage is attractive?

**My thoughts:**

> 
> 

### AI-116: Slow pivot enables a threat

**Situation:** A durable AI pivot can take a hit and bring in a fragile attacker without exposing it to that hit.

**Decision to consider:** Should securing a safe arrival outweigh modest direct damage, and how valuable must the incoming attacker's matchup be?

**My thoughts:**

> 
> 

### AI-117: Fast pivot exposes the recipient

**Situation:** A fast AI pivot moves before the player, so its replacement must absorb the selected attack. The current Pokémon could survive comfortably.

**Decision to consider:** How carefully should replacement survival constrain pivot use, especially when the player's precise move is uncertain?

**My thoughts:**

> 
> 

### AI-118: Switch to absorb an attack

**Situation:** The AI has a revealed absorption ability on a reserve. Switching it into the expected attack gives healing or a boost, but coverage would punish it.

**Decision to consider:** Should this be an occasional read, a standard defensive response, or require a demonstrated player pattern?

**My thoughts:**

> 
> 

### AI-119: Intimidate cycling

**Situation:** The AI can repeatedly rotate an Intimidate user and a resistance to suppress a physical player attacker, at some hazard and chip cost.

**Decision to consider:** How much cycling should be allowed before prioritizing progress, and should a player lacking a counter be permitted to exploit predictability?

**My thoughts:**

> 
> 

### AI-120: Escape trapping versus keep attacking

**Situation:** The AI has a legal pivot or other escape option from a trapping situation. Staying can deal damage but loses the Pokémon eventually.

**Decision to consider:** When should it recognize escape as the main objective, and should preserving player trapping strategies limit that recognition?

**My thoughts:**

> 
> 


## 13 · Team plans and limited resources (121–130)

### AI-121: Team win condition versus local win

**Situation:** The AI can win the current exchange by exposing its only remaining sweeper to severe damage. A weaker teammate can instead make partial progress.

**Decision to consider:** How explicitly should it protect a team win condition, and must that role be authored or may it infer it from the remaining matchup?

**My thoughts:**

> 
> 

### AI-122: Break the wall for a teammate

**Situation:** An AI attacker cannot beat the player wall alone, but can weaken it enough for a reserve to sweep. Switching preserves HP without making progress.

**Decision to consider:** Should it intentionally commit to a losing local trade to create the team's winning line?

**My thoughts:**

> 
> 

### AI-123: Spend a resist berry now

**Situation:** The AI's known resist berry makes one dangerous matchup survivable. Preserving it could help against a later revealed attacker of the same type.

**Decision to consider:** Should it regard consuming the berry as a planned resource expenditure, or simply use the best immediate matchup?

**My thoughts:**

> 
> 

### AI-124: One-time survival for setup

**Situation:** A known Focus Sash lets a full-health AI attacker survive a hit and set up. Attacking immediately would also consume the Sash but get damage now.

**Decision to consider:** When should the guaranteed survival turn be invested in setup rather than immediate offense?

**My thoughts:**

> 
> 

### AI-125: Choice-lock commitment

**Situation:** The AI's Choice item boosts its attack, but locking into the strongest move invites a revealed immune reserve. A weaker move covers both targets.

**Decision to consider:** How much should future lock consequences influence the initial choice without restoring broad switch prediction?

**My thoughts:**

> 
> 

### AI-126: Trick away a valuable item

**Situation:** The AI can cripple a wall by transferring its Choice item, but loses the offensive boost it needs against another known opponent.

**Decision to consider:** Should it trade its own future role for disruption, and what evidence makes that exchange worthwhile?

**My thoughts:**

> 
> 

### AI-127: Knock Off versus immediate damage

**Situation:** Knock Off removes a revealed important item, while another move deals substantially more damage and could secure a faster KO.

**Decision to consider:** How should long-term item denial compare with the current damage line, especially if the target is likely to faint soon anyway?

**My thoughts:**

> 
> 

### AI-128: Preserve scarce attack PP

**Situation:** The AI has only a few PP left on its sole answer to a revealed threat. A weaker move is adequate against the current target.

**Decision to consider:** Should it conserve that move deliberately, and how much slower progress is acceptable for PP management?

**My thoughts:**

> 
> 

### AI-129: Player PP-stall strategy

**Situation:** The player uses Protect, recovery, and immunities to deplete a powerful AI attack. The sequence is legal and consumes player resources too.

**Decision to consider:** Should the AI recognize and resist PP stalling, or should this remain a rewarded strategic route? Where would you draw the boundary?

**My thoughts:**

> 
> 

### AI-130: Last-Pokémon losing position

**Situation:** The AI cannot win with ordinary damage but has a low-probability status or critical-hit route. No switch or resource remains.

**Decision to consider:** Should it pursue the tiny winning chance, maximize damage, or choose a fast resolution? Does the answer change for a boss?

**My thoughts:**

> 
> 


## 14 · Weather, terrain, and Terastalization (131–140)

### AI-131: Weather setter versus commitment

**Situation:** An AI weather setter faces a bad matchup after already acting successfully. Preserving it would renew weather for several teammates later.

**Decision to consider:** Should weather-team value override ordinary commitment, or should setters obey the same escape limits as other Pokémon?

**My thoughts:**

> 
> 

### AI-132: Weather war

**Situation:** The player has a revealed opposing weather setter. The AI can switch to restore its own weather but risks entering a predictable back-and-forth.

**Decision to consider:** How much should it spend to win weather control, and when should it attack through unfavorable weather instead?

**My thoughts:**

> 
> 

### AI-133: Weather helps both sides

**Situation:** Rain boosts the AI's Water offense but also activates a revealed player speed ability that creates immediate danger.

**Decision to consider:** Should it reject its usual weather plan, delay it, or use it only if a teammate can handle the beneficiary?

**My thoughts:**

> 
> 

### AI-134: Field expiration and attack timing

**Situation:** A revealed field effect that weakens the AI's attack expires this turn. Protect or a support move could delay offense until next turn.

**Decision to consider:** Should the AI plan around the exact timer, and how much free player setup risk should it accept to do so?

**My thoughts:**

> 
> 

### AI-135: Terrain protects a future plan

**Situation:** Setting terrain would block a relevant status or priority interaction under the configured mechanics, helping a reserve more than the setter.

**Decision to consider:** Should this team protection justify the action, and must the benefiting teammate already have a clear entry route?

**My thoughts:**

> 
> 

### AI-136: Defensive Tera prevents a KO

**Situation:** An explicitly eligible AI Pokémon can Tera to survive a revealed otherwise lethal attack. Another player attack would punish the new type but has not been shown.

**Decision to consider:** Should it take the immediate rescue, hedge against generic coverage, or reserve Tera for a higher-value teammate?

**My thoughts:**

> 
> 

### AI-137: Offensive Tera secures removal

**Situation:** Tera turns the AI's attack into a guaranteed KO without improving its defense. A teammate could later need Tera to survive.

**Decision to consider:** When should guaranteed offensive value justify spending the team's single transformation?

**My thoughts:**

> 
> 

### AI-138: Tera trades one weakness for another

**Situation:** The player's revealed moves include both the attack Tera would solve and another attack that beats the transformed type.

**Decision to consider:** How confident must move prediction be before the AI chooses Tera, and should probabilistic reads be allowed here?

**My thoughts:**

> 
> 

### AI-139: Player Tera remains unannounced

**Situation:** The AI has a strong attack against the player's current type, but the player could Tera into an immunity or resistance this turn.

**Decision to consider:** Should the AI ever anticipate an unused player Tera, and what public evidence would justify sacrificing its current best attack?

**My thoughts:**

> 
> 

### AI-140: Eligible now versus better later

**Situation:** Two AI Pokémon have explicitly assigned Tera types. The active one gains a modest benefit now; the reserve has a known potentially decisive use.

**Decision to consider:** How should the AI compare immediate value against an uncertain future opportunity, and should authored team plans guide this choice?

**My thoughts:**

> 
> 


## 15 · Doubles damage and target allocation (141–150)

### AI-141: Two available KOs

**Situation:** In doubles, each AI attacker can KO either opposing Pokémon, and both act before the opponents. Separate targets would secure two KOs.

**Decision to consider:** Should coordinated target allocation be guaranteed for strong trainers, and should weaker trainers sometimes duplicate their attacks?

**My thoughts:**

> 
> 

### AI-142: Combined damage required

**Situation:** Neither AI attacker can KO alone, but both together can remove one dangerous opponent before it acts. Splitting attacks removes neither.

**Decision to consider:** When should focus fire beat spreading damage, and how should differing speeds affect the combined plan?

**My thoughts:**

> 
> 

### AI-143: One flexible attacker

**Situation:** One AI partner can KO either opponent; the other can KO only one. Both survive the turn if targets are allocated well.

**Decision to consider:** Should the flexible attacker always leave the restricted target to its partner, or can target importance justify another allocation?

**My thoughts:**

> 
> 

### AI-144: Threat versus easy KO

**Situation:** The AI can remove a passive weakened support Pokémon or concentrate damage on a healthy sweeper that threatens both partners.

**Decision to consider:** How should danger, removal certainty, and the support Pokémon's remaining utility determine the priority target?

**My thoughts:**

> 
> 

### AI-145: Overkill as insurance

**Situation:** One AI attack probably KOs a target but can miss or low-roll. A second attack would usually be redundant but insures against failure.

**Decision to consider:** How much reliability should justify duplicate targeting, and should the AI instead plan around the alternate target that could survive and act?

**My thoughts:**

> 
> 

### AI-146: Spread damage versus single removal

**Situation:** A spread attack damages both foes substantially. A single-target attack removes one immediately but leaves the other untouched.

**Decision to consider:** When should reducing opposing actions outweigh larger total damage, especially if the survivor can KO an AI partner?

**My thoughts:**

> 
> 

### AI-147: Friendly fire with a benefit

**Situation:** Earthquake hits both opponents and the AI's partner, which has a revealed ability that can benefit from the hit but still loses HP.

**Decision to consider:** How should ally benefit, actual HP cost, and opponent removals combine? Should beneficial friendly fire require an authored combo?

**My thoughts:**

> 
> 

### AI-148: Friendly fire costs an ally

**Situation:** A spread attack KOs the AI's nearly spent partner and both opponents. A safe attack preserves the ally but removes only one foe.

**Decision to consider:** Should it deliberately sacrifice the ally, and how should remaining reserves and actual victory rules affect acceptance?

**My thoughts:**

> 
> 

### AI-149: Protect prediction changes targets

**Situation:** A low-health player attacker is likely to Protect, while its partner threatens the AI. Protect has been revealed but is not guaranteed.

**Decision to consider:** Should the AI redirect attacks away from the obvious Protect, and what prevents the player from exploiting that expectation by attacking?

**My thoughts:**

> 
> 

### AI-150: Redirection changes a KO plan

**Situation:** A revealed Follow Me or Rage Powder user can redirect a crucial single-target attack under the current legality rules. Spread damage remains available.

**Decision to consider:** Should the AI plan around possible redirection, remove the redirector first, or trust its current-target attack until the support action is observed repeatedly?

**My thoughts:**

> 
> 


## 16 · Doubles support and partner coordination (151–160)

### AI-151: Helping Hand crosses the KO threshold

**Situation:** Helping Hand lets the partner guarantee a KO before a dangerous foe acts. The support user's own attack cannot achieve that outcome.

**Decision to consider:** Should the AI prefer the combined KO consistently, and how should partner accuracy or a possible Protect weaken the plan?

**My thoughts:**

> 
> 

### AI-152: Helping Hand without an attacking ally

**Situation:** The AI's partner has already selected a switch, recovery move, or other action that cannot use Helping Hand.

**Decision to consider:** Should this make Helping Hand unavailable, and must an AI-controlled partner's decision always be treated as known?

**My thoughts:**

> 
> 

### AI-153: Redirection buys setup

**Situation:** An AI redirector can absorb attacks so its partner sets up, but may faint and leave the team with fewer actions next turn.

**Decision to consider:** How much expected payoff should justify the sacrifice, and should the plan account for revealed spread attacks that bypass redirection?

**My thoughts:**

> 
> 

### AI-154: Fake Out saves the partner

**Situation:** Fake Out can stop the foe that would otherwise KO the AI's partner. Attacking the other slot would deal more damage but lose the ally.

**Decision to consider:** Should saving the ally dominate, and does the ally need a meaningful selected action for the rescue to be worthwhile?

**My thoughts:**

> 
> 

### AI-155: Fake Out into a blocker

**Situation:** A revealed ability, terrain, typing, or other effect prevents Fake Out from stopping the intended foe in this fixture.

**Decision to consider:** Should the AI redirect Fake Out to another useful target, abandon it, or retain it for damage when that damage matters?

**My thoughts:**

> 
> 

### AI-156: Partner already covered the drop

**Situation:** The first AI partner's selected speed-lowering attack already establishes favorable turn order. The second can lower Speed again or use stronger damage.

**Decision to consider:** Should the second always avoid redundant speed control, and how should accuracy uncertainty or a different target keep it useful?

**My thoughts:**

> 
> 

### AI-157: Screen and offensive partner

**Situation:** An AI support Pokémon can set Reflect to keep its partner alive through a physical hit. Its direct attack would not remove the threat.

**Decision to consider:** Should survival of the partner's planned action be the main screen criterion, and how should mixed opposing damage alter the choice?

**My thoughts:**

> 
> 

### AI-158: Coaching changes survival and damage

**Situation:** Coaching lets a physical partner survive a hit and reach a KO threshold, but the partner acts before or after different foes.

**Decision to consider:** How precisely should the AI account for action order before treating the support as successful?

**My thoughts:**

> 
> 

### AI-159: Heal an ally or remove a foe

**Situation:** An AI healer can rescue its injured partner. Alternatively, attacking could remove the opponent threatening that partner.

**Decision to consider:** Should removing the threat be preferred when both plans preserve the ally, and how should uncertainty distinguish the choices?

**My thoughts:**

> 
> 

### AI-160: Two supports and no progress

**Situation:** Both AI partners have attractive support moves, but using both leaves the player free to set up without taking damage.

**Decision to consider:** Should at least one partner normally attack, or are multi-turn defensive plans acceptable when they have a concrete payoff?

**My thoughts:**

> 
> 


## 17 · Doubles field plans, switching, and endgames (161–170)

### AI-161: Trick Room setter needs protection

**Situation:** An AI slow attacker benefits enormously from Trick Room, but the setter may be KOed before using it unless its partner intervenes.

**Decision to consider:** Should the pair commit both actions to establishing the field, and what payoff makes that investment preferable to immediate attacks?

**My thoughts:**

> 
> 

### AI-162: Trick Room expires after this turn

**Situation:** The AI's slow attackers currently move first, but Trick Room ends at turn end. Renewing it now would interact with its still-active state.

**Decision to consider:** Should the AI use a coordinated timing plan, wait until it expires, or avoid complex renewal reads unless the player has shown a stalling pattern?

**My thoughts:**

> 
> 

### AI-163: Tailwind helps only one partner

**Situation:** Tailwind changes the faster AI partner's matchups but leaves the slower partner behind both opponents. A direct attack threatens a KO.

**Decision to consider:** How much benefit to one ally is enough, and should the ally's selected move determine whether the speed advantage matters?

**My thoughts:**

> 
> 

### AI-164: Weather change disrupts ally action

**Situation:** The AI's weather setter can improve its own attack but would weaken or invalidate the partner's already selected weather-dependent action.

**Decision to consider:** Should partner plan consistency override local benefit, and can both decisions be reconsidered together?

**My thoughts:**

> 
> 

### AI-165: One safe reserve, two threatened actives

**Situation:** Both AI actives want to switch, but only one available reserve survives the expected attacks. The other must stay or take a bad switch.

**Decision to consider:** Which active should receive the safe reserve: the more valuable Pokémon, the more threatened one, or the one with less useful damage to offer?

**My thoughts:**

> 
> 

### AI-166: Switch leaves the partner exposed

**Situation:** An AI support Pokémon can escape danger, but its departure removes a protective ability or other field benefit keeping its partner alive.

**Decision to consider:** How strongly should partner survival restrict voluntary switches, and can sacrificing the support be preferable?

**My thoughts:**

> 
> 

### AI-167: Human ally with uncertain action

**Situation:** In a multi battle, the AI's ally is human-controlled and has not publicly committed to an action the AI is allowed to know.

**Decision to consider:** Should the AI use a conservative independent plan, predict the ally, or rely only on signaled coordination? What information access is fair?

**My thoughts:**

> 
> 

### AI-168: Two trainers sharing a side

**Situation:** Two independent AI trainers battle together. Their teams can coordinate attacks, but they have separate identities and potentially separate resources.

**Decision to consider:** Should they coordinate as perfectly as one trainer, and how should shared-side opportunities be allocated without favoring a fixed slot?

**My thoughts:**

> 
> 

### AI-169: Delayed attack lands into a switch

**Situation:** A public delayed attack will land on a doubles slot this turn. A switch could save the active Pokémon but expose the replacement to that hit and current attacks.

**Decision to consider:** How far should combined damage planning extend, and should keeping the partner's safe action change who takes the hit?

**My thoughts:**

> 
> 

### AI-170: One opponent left in doubles

**Situation:** Both AI partners face one remaining player Pokémon. One AI attacker can guarantee the KO before the other acts; the second could heal or prepare for an uncertain failure.

**Decision to consider:** Should it optimize the guaranteed finish, insure against disruption, or avoid pointless support once victory is secured?

**My thoughts:**

> 
> 


## 18 · Elastic-specific mechanics and planned combinations (171–180)

### AI-171: Adaptive Unown Hidden Power

**Situation:** Unown's Hidden Power selects an effective type for its resolved target under Elastic's rules. The AI is considering switching to a fixed-type absorber.

**Decision to consider:** Should the AI recognize that the attack adapts after the switch, and what knowledge should it need about Unown's signature mechanic?

**My thoughts:**

> 
> 

### AI-172: Tied adaptive types with different consequences

**Situation:** Several Hidden Power types tie for the best runtime score, but trigger different revealed abilities or later interactions. Execution can select among those tied types.

**Decision to consider:** Should the AI evaluate all tied outcomes, a representative outcome, or a conservative bound? How much risk should an otherwise equal tie introduce?

**My thoughts:**

> 
> 

### AI-173: Proactive Color Change sequencing

**Situation:** A player Color Change Pokémon would change type in response to an AI attack under Elastic's mechanic. A follow-up attack could exploit the resulting type.

**Decision to consider:** How much should the AI plan the sequence rather than maximize the first hit, especially when the player can switch before the follow-up?

**My thoughts:**

> 
> 

### AI-174: Forewarn narrows the threat

**Situation:** A publicly warned move is weakened by Elastic Forewarn, while another revealed attack is not. The AI can choose its attack or decide whether to stay.

**Decision to consider:** Should both sides' move selection and survival estimates exploit that exact warned-move distinction, and should the effect encourage prediction?

**My thoughts:**

> 
> 

### AI-175: Damp and Water Sport investment

**Situation:** An AI Damp user can gain Elastic's Water Sport healing benefit and later pivot. The immediate alternative deals damage without establishing that plan.

**Decision to consider:** When should healing plus future pivot value justify Water Sport, and should the plan require a useful reserve and survivable setup turn?

**My thoughts:**

> 
> 

### AI-176: Merry activation costs tempo

**Situation:** An AI Merry user can activate its Elastic bonuses through an eligible support action, while direct offense would pressure the player immediately.

**Decision to consider:** How much should the activation's future power, accuracy, and Speed justify a currently modest support turn?

**My thoughts:**

> 
> 

### AI-177: Perplex Dance and self-confusion

**Situation:** AI Spinda can sharply reduce the target's offensive stats with Perplex Dance, but risks its self-confusion drawback unless its ability prevents it.

**Decision to consider:** How should guaranteed disruption compare with the drawback, and how much more aggressively should an immune-to-confusion user choose it?

**My thoughts:**

> 
> 

### AI-178: Stockpile and custom Swallow

**Situation:** An AI Stockpile user can cash in its current stockpile for Elastic's configured Swallow healing or keep it for a longer plan.

**Decision to consider:** Should the AI seek a survival threshold, preserve accumulated value, or follow a simple recovery policy? How should Gluttony alter the decision?

**My thoughts:**

> 
> 

### AI-179: Ice-type Chilling Water utility

**Situation:** An AI currently Ice-type user receives Elastic's Chilling Water power benefit, while the move also reduces a surviving target's Attack where legal.

**Decision to consider:** How should it value this combined damage and protection, and should a temporary type change make it reconsider the move immediately?

**My thoughts:**

> 
> 

### AI-180: Metal Rush weight-dependent rider

**Situation:** Metal Rush gives its configured Speed boost or Defense-drop rider according to effective weight. A public weight-changing effect can change which rider applies.

**Decision to consider:** Should the AI plan around the current rider and its payoff, or is accurate damage with only basic utility recognition sufficient for this mechanic?

**My thoughts:**

> 
> 


## 19 · Unusual tactics and fragile decision boundaries (181–190)

### AI-181: Two-turn attack as a player opening

**Situation:** The AI's charge or semi-invulnerable attack has high payoff but gives the player a public turn to defend, switch, or set up. No charge-skip effect applies.

**Decision to consider:** How much counterplay should lower its desirability, and should some trainers deliberately retain telegraphed attacks as exploitable weaknesses?

**My thoughts:**

> 
> 

### AI-182: Power Herb enables a surprise

**Situation:** A known effective Power Herb makes a normally two-turn attack immediate. Without knowledge of that item, the same attack is speculative.

**Decision to consider:** Should charge-skip knowledge change offensive inference and defensive switching together, or should some implications require seeing the move?

**My thoughts:**

> 
> 

### AI-183: Recharge attack finishes or exposes

**Situation:** A recharge move guarantees a KO, but its subsequent inactive turn may let a revealed reserve set up. A weaker attack leaves the current foe alive.

**Decision to consider:** How much should the AI account for the next matchup before choosing the immediate KO?

**My thoughts:**

> 
> 

### AI-184: Counter or Mirror Coat read

**Situation:** The player has revealed both an attack and a nonattacking option. The AI's reactive damage move wins only if the matching attack is chosen.

**Decision to consider:** Should it treat the move as a probabilistic read, require repeated behavior, or mostly avoid it when a useful unconditional action exists?

**My thoughts:**

> 
> 

### AI-185: Focus Punch behind a shield

**Situation:** AI Focus Punch succeeds if its protective setup holds or the player does not land a disrupting hit. A weaker attack always executes.

**Decision to consider:** Which public conditions make the plan reliable enough, and how much should player move history influence the attempt?

**My thoughts:**

> 
> 

### AI-186: Destiny Bond threat

**Situation:** The player has revealed Destiny Bond and can legally threaten a trade this turn. The AI can KO with damage or spend a turn on a useful nonattack.

**Decision to consider:** Should it reliably avoid the trade, sometimes call the bluff, or accept it when the opposing Pokémon is more valuable?

**My thoughts:**

> 
> 

### AI-187: Perish countdown escape

**Situation:** An AI Pokémon has a public perish countdown and a legal escape route. Switching now is safe; staying one more turn could remove the player.

**Decision to consider:** How close to expiration should it wait, and should the prospect of a useful trade override preservation?

**My thoughts:**

> 
> 

### AI-188: Pain Split after taking damage

**Situation:** A slower AI user expects a large hit before Pain Split, making the post-hit HP exchange much better than the current HP numbers suggest.

**Decision to consider:** Should it commit to that recovery line based on expected damage, and how should a possible player status move undermine it?

**My thoughts:**

> 
> 

### AI-189: Known item transfer backfires

**Situation:** Trick or Bestow would give the player an item that improves its known plan, while the AI would gain little or nothing useful.

**Decision to consider:** Should transfer moves be excluded unless the exchange has a clear benefit, and how should legality restrictions interact with strategic evaluation?

**My thoughts:**

> 
> 

### AI-190: Last-turn simultaneous fainting

**Situation:** An AI sacrifice move, recoil attack, or residual-damage sequence removes the final Pokémon on both sides. The game's configured resolution determines who wins.

**Decision to consider:** Should the AI deliberately choose the resolved winning trade, avoid losing trades absolutely, or value a dramatic finish differently for certain trainers?

**My thoughts:**

> 
> 


## 20 · Trainer identity, randomness, and acceptance boundaries (191–200)

### AI-191: Beginner versus expert, same position

**Situation:** An early-route trainer and a late-game boss each face the same obvious KO opportunity, with a tempting but inferior setup move available.

**Decision to consider:** Which basic competencies should every trainer share, and which mistakes are acceptable only for weaker trainers?

**My thoughts:**

> 
> 

### AI-192: Thematic plan versus tactical escape

**Situation:** A trainer's identity centers on a particular weather, status, or combo plan. An off-theme attack is clearly better in the current position.

**Decision to consider:** How much should personality constrain optimal play, and should that commitment be visible enough for players to exploit intentionally?

**My thoughts:**

> 
> 

### AI-193: Boss-specific preparation

**Situation:** A boss has an authored team combo and knows exactly how its own parts work. The player's unusual counter remains hidden.

**Decision to consider:** Should the boss execute its own plan more reliably without gaining extra player information, or are different knowledge privileges appropriate and signaled?

**My thoughts:**

> 
> 

### AI-194: Randomness among reasonable actions

**Situation:** Two moves offer different but credible plans. One is slightly stronger under the current estimates, but choosing it every time becomes predictable.

**Decision to consider:** How wide should the acceptable choice set be, and should randomness apply only among near-equals or sometimes permit a clear concession?

**My thoughts:**

> 
> 

### AI-195: Repeated independent switch rolls

**Situation:** A switch heuristic has a moderate chance to trigger on each eligible turn. Several failures in a row leave the AI in danger; repeated successes cause evasive cycling.

**Decision to consider:** Should probabilities be independent, use memory, or have cooldowns? Which resulting streaks would feel acceptable rather than broken?

**My thoughts:**

> 
> 

### AI-196: Deterministic exploit after discovery

**Situation:** A player discovers that a specific public position always makes the AI choose one move, enabling a clever repeatable counter.

**Decision to consider:** Should solving that pattern remain a reward, or should the AI diversify once exploited? Which kinds of deterministic behavior are desirable?

**My thoughts:**

> 
> 

### AI-197: Risk appetite when ahead or behind

**Situation:** The AI can choose a reliable modest line or a risky high-payoff line. Its remaining team is either clearly favored or nearly lost.

**Decision to consider:** Should team advantage change risk tolerance, and how much should the same visible local position produce different play because of the reserves?

**My thoughts:**

> 
> 

### AI-198: Public calculability versus hidden heuristics

**Situation:** The player can inspect damage ranges and public battle state, yet cannot see the AI's internal scores or random decisions.

**Decision to consider:** How predictable should action selection be from that information, and what unexplained deviations would make the AI feel unfair?

**My thoughts:**

> 
> 

### AI-199: Rule conflict across earlier answers

**Situation:** Your preferred commitment rule says stay in, but your preferred team-preservation rule says save the only counter to a revealed sweeper.

**Decision to consider:** Which principles should outrank others, and should exceptions be narrow authored rules or general evaluations of winning chances?

**My thoughts:**

> 
> 

### AI-200: Minimum acceptable versus ideal behavior

**Situation:** A future implementation can handle common cases coherently but cannot model every rare interaction or long plan. More complex reasoning may add inconsistency.

**Decision to consider:** Which earlier IDs are nonnegotiable, which can use a simple fallback, and which should intentionally remain exploitable? Identify your first implementation priorities.

**My thoughts:**

> 
> 

