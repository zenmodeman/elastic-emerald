# Custom Battle AI Logic Summary

## Documentation status

- **Last documented code commit:** `a2ef6c4bde` ("Add not already target guard for fast KO logic").
- **Uncommitted AI changes covered by this document:** The post-1.16.2 repair restores the narrow `AI_FLAG_HEAVY_SWITCHING` fast-KO rule, its regular-smart defensive-drop exception, weather-setter preservation, and repeated-switch immunity prediction on the rewritten upstream switching APIs. Eligible-reserve fallback is used when upstream does not pre-rank a suitable switch-in. Repeated-switch prediction uses both the stint counter and revealed party switch-in history, retains the standard prediction RNG gate, and avoids re-running active-target damage comparison after predicted-target scoring. Smart trainers continue to use prediction and assumptions instead of upstream omniscience and PP-stall knowledge. Test adaptations also cover the upstream `AI_FLAG_ASSUME_STAB` knowledge path and unified stat-change contracts for Rock Tomb and Coaching. All of these AI changes are currently uncommitted.

The commit above is the newest code revision whose applicable AI behavior has been reviewed for inclusion here. If this document is updated alongside uncommitted AI work, that work should be listed explicitly as uncommitted rather than attributed to the current commit. Once the work is committed, a later documentation pass should replace the uncommitted marker and advance the documented commit.

## Scope and reading guidance

This document summarizes the main battle-AI work introduced through my commits from January 2024 through July 2026. Merge commits, trainer-team-only edits, mechanical formatting changes, and tests that did not introduce behavior are omitted. Later "restore" commits are treated as continuations of the original feature rather than separate features.

The implementation is a heuristic, rule-based system. It scores moves, predicts damage and state transitions, chooses targets, and evaluates switches. It is not a search tree or learned policy. Much of the custom work tries to make that heuristic system reason under imperfect information without becoming trivially exploitable. It involves a lot of stochastic logic. 

The most important implementation files are:

- `src/battle_ai_main.c`: move scoring, damaging-move comparison, target selection, and decision flow.
- `src/battle_ai_util.c`: knowledge modeling, damage and speed helpers, status logic, simulated state changes, and effect predicates.
- `src/battle_ai_switch.c` and `src/battle_ai_items.c`: voluntary switching, switch-in selection, prediction, and trainer item use.
- `include/battle.h`: per-turn AI state, party history, predictions, and doubles coordination data.
- `include/constants/battle_ai.h` and `include/config/ai.h`: strategy composition and tuning gates.

## 1. Smart-trainer policy and information philosophy

### Prediction-oriented smart trainer

The custom `AI_FLAG_SMART_TRAINER` profile removes unconditional omniscience and PP-stall prevention from the upstream smart profile. It instead combines ordinary viability logic with smart switching, incoming-mon prediction, move prediction, and smart Terastalization.

This establishes the intended design philosophy: strong trainers should infer likely information and react to observed play rather than simply reading every hidden move and ability.

Key commits: `2a278a5a56`, `86a1b336ef`.

### Graduated opponent knowledge

The AI distinguishes among:

- explicitly revealed moves;
- inferred offensive STAB moves;
- selected likely status moves;
- observed or predicted abilities;
- known held-item effects;
- revealed party species and previously used switch-ins.

The upstream `AI_FLAG_ASSUME_STAB` path records eligible unrevealed STAB options while helpers such as `HasNoMovesKnown`, `HasAllKnownMoves`, `HasNoKnownNonProtectingMoves`, and `GetStatusMoveCount` let individual heuristics state how much evidence they require.

Unrevealed STAB estimates are filtered to avoid implausible predictions such as unusable recharge or two-turn attacks. When no attacks are known, physical-versus-special expectations can fall back to raw offensive stats with a level-sensitive comparison threshold.

Key commits: `59b76d3fcd`, `4bb634c651`, `829ec9c367`, `7ee8501957`.

### Item and ability revelation hooks

Earlier iterations recorded inferable items when their effects became visible, including Life Orb, Float Stone, Eviolite, and Assault Vest. Frisk was expanded to interact with item-manipulating moves, and Forewarn stores a warned move so its defensive effect can be included in effectiveness calculations.

The current policy goes further and gives the AI complete player held-item knowledge, including benched party members. This is deliberately more permissive than its move and ability knowledge model and feeds both damage simulation and switching.

Key commits: `ac7f19cbd6`, `ece86112ff`, `3c07dac5ed`, `1f6633f157`, `6cf60d5e69`.

## 2. Move scoring and damage-line comparison

### Effect viability before best-damage preference

The scoring order was reworked so move-effect viability is established before the best-damaging-move bonus is awarded. A move that is invalid, strategically poor, or scored below the default should not become desirable merely because it has the largest raw damage number.

This is the foundation for comparing damaging utility moves against pure attacks without erasing their effect-specific scoring.

Key commits: `7a57d6931d`, `d15ae7979e`.

### KO turns plus meaningful damage gaps

Damaging moves are primarily compared by turns to KO, then by reliability and effect quality. A custom damage-gap rule also distinguishes attacks with the same nominal KO count when one deals materially more damage. OHKOs are excluded from that secondary gap comparison so redundant overkill does not distort selection.

Key commits: `7829b03a9c`, `69e70069a6`.

### Binding-move comparison

The current upstream damage comparison does not assume speculative future binding turns. Effect-specific viability can still account for immediate tactical value, including:

- initial move damage;
- Binding Band and Grip Claw behavior;
- Magic Guard immunity;
- the possibility that an escapable target switches out;
- whether binding improves the reachable KO line rather than merely adding hypothetical residual damage.

Regression coverage now explicitly preserves this non-speculative merged behavior: a weaker binding move is not promoted above the stronger direct attack solely by assuming future trapped turns.

Key commits: `cf246c99c5`, `64d81988c7`, `41dd243ec6`, `bd83b55fb4`.

### Consumable resist-berry simulation

Resist berries are modeled across turns. The first hit uses berry-reduced damage; later hits are recomputed with the berry temporarily removed, after which AI state is restored. Moves with equal nominal KO timing can then be compared by their two-turn damage line rather than assuming the berry applies forever.

Key commit: `6cf60d5e69`.

### Guaranteed additional-effect valuation

Guaranteed stat drops and other secondary effects are scored only when they are useful and the target is expected to survive. The system accounts for Sheer Force suppressing applicable effects and uses stat-specific predicates rather than awarding a uniform utility bonus.

Key commits: `93531a3cea`, `6e5f7576f7`.

## 3. Imperfect-information switching and counterplay

### Weather-setter preservation

General fast-KO switching is disabled. The remaining contextual rule applies in singles to smart-switching trainers whose active Pokemon has Drizzle, Drought, Sand Stream, or Snow Warning. If the setter would act after the opponent and an actual-state damage calculation using the opponent's revealed moves plus Hidden STAB inference finds a KO, the AI may preserve the setter.

Preservation additionally requires that the player has not targeted the setter with either a damaging or status move during its current field stint, that the setter retains at least 75% of its maximum HP, that at least three other living Pokemon in that trainer's party benefit from the setter's weather, and that an eligible reserve exists. The targeting memory resets when the setter switches out. The HP gate limits preservation to setters with enough longevity to contribute again after returning. A party Pokemon counts once if either of the following applies:

- it has a positively weather-interacting ability such as Swift Swim, Chlorophyll, Sand Rush, or Slush Rush;
- it is Grass-type in sun or Ice-type in hail/snow.

When every gate passes, the AI has a 50% chance to switch to the standard most-suitable party Pokemon, falling back to the first eligible reserve when the upstream ranker returns no candidate. The KO check respects current battle conditions and survival effects such as Focus Sash and Sturdy. It does not use the abandoned clean-state model.

Regression coverage explicitly checks both sides of the critical survival ordering: a slower unprotected setter with three weather allies may be preserved, while a faster setter, a setter whose Focus Sash prevents the inferred KO, or a setter already targeted by the player stays in.

Key commits: `5440fb44b4`, `a2ef6c4bde`.

### Heavy-switching fast-KO preservation

The logic begins with hard preconditions, followed by an extensible outer-check layer and then shared inner checks. Singles and the absence of prior targeting by a player's damaging or status move are hard gates evaluated before any outer reason, preventing unnecessary hypothetical calculations and ensuring future outer checks cannot bypass the targeting policy. Each independent reason to consider the behavior is stored as a named boolean, and passing any outer check admits the battler to the same inner safeguards. The current outer checks are `AI_FLAG_HEAVY_SWITCHING` and the defensive-drop exception described below; future reasons can be added to their combined eligibility condition without duplicating the common logic. Once any outer check qualifies, there is a 50% chance to preserve an active Pokemon when all of the following inner conditions are true: the opponent is faster, an actual-state calculation using revealed moves plus Hidden STAB inference finds a KO, and the standard switch-in ranking found a suitable replacement. The HP gate is at least 75% for most Pokemon and at least 50% for Regenerator Pokemon. `AI_FLAG_HEAVY_SWITCHING` is deliberately absent from `AI_FLAG_SMART_TRAINER`, so ordinary smart trainers receive only the defensive-drop exception rather than generalized fast-KO switching.

Regular `AI_FLAG_SMART_SWITCHING` can use the same response without the heavy-switching flag only when the current KO depends on negative Defense or Special Defense stages: after restoring both defensive stages to neutral, no move in that same revealed-plus-Hidden-STAB information set may still KO. The pre-existing targeting guard means player-applied drops such as Screech disable the response, while self-inflicted drops and reactive drops from effects such as Obstruct remain eligible. The temporary defensive-stage changes are restored immediately after calculation.

Focused regression coverage verifies the heavy-switching flag and ordinary-smart exclusion, plus each defensive-drop origin: Close Combat-style AI self-drops and Obstruct can enable the switch, while Screech trips the prior-targeting hard gate and cannot. Weather-setter coverage separately verifies the suitable-switch-in, 50% roll, HP, Speed, survival, ally-count, and prior-targeting gates.

This replacement is currently uncommitted.

### Scrapped generalized fast-KO experiments

Earlier versions attempted broad fast-KO preservation based on revealed versus inferred damage, literal-lead recognition, quad-effective Hidden STAB windows, and a clean-state simulation that removed player-created type, ability, grounding, immunity-bypass, defensive-stage, and Speed-stage changes. That approach was removed because its complexity produced little payoff and could over-penalize ordinary offensive Pokemon and player tech moves. The new heavy-switching rule restores only its narrow fast-KO core and defensive-drop comparison; the concise older history is retained here for context.

The original bad-odds and fast-KO progression is represented by commits `7829b03a9c`, `ff6f0ac1bb`, `a676dccb29`, `fda788dcf4`, and `efda8256b3`. Clean-state and literal-lead work was introduced in `6f1d67a6f4`, refined in `8d856e4bcf`, and given its final quad-effective Hidden STAB window in `4547aff533` before being scrapped by `5440fb44b4`.

Dig/free-turn switching and broad type-matchup switching were also removed or disabled after testing because they produced poor or exploitable behavior.

### Absorption and immunity switches

The AI can switch into type immunities, blocking abilities, or healing absorbers, but checks whether staying in can outspeed and KO first. Absorber switching is probabilistic rather than guaranteed to prevent deterministic baiting.

The implementation centralizes type and move-property absorbers and uses dynamic move types where necessary.

Key commits: `b497956f2b`, `2a278a5a56`, `7ee8501957`, `9335949404`.

### Repeated-switch immunity prediction

The current immunity-abuse countermeasure is singles-only and overlays the normal scoring pass:

1. Score moves normally and identify the highest-scored damaging move.
2. Track voluntary player hard switches and pivot moves during the current AI battler's field stint.
3. After five such switches, consider revealed, living, benched player Pokemon that could absorb, block, or type-immune the selected attack. Revealed party switch-in counts provide a fallback when a test or alternate switch path does not update the dedicated stint counter.
4. Rank candidates first by prior switch-in count, then by immunity quality: healing absorber, ability blocker, then type immunity.
5. Apply the configured prediction RNG gate and rescore against the predicted switch-in.

Forced switches are excluded from the counter. The stint counter resets when the AI changes battlers. This design targets repeated immunity cycling without granting universal team omniscience.

Key commits: `2a278a5a56`, `9335949404`.

### Switch and item decision diagnostics

Category-based debug output can independently trace switch decisions, reasons, candidate evaluation, type matchups, damage, hazards, statuses, abilities, player prediction, and trainer items.

Player-facing debug features are controlled by a saved runtime Option-menu setting in both debug and non-debug builds. Debug battles apply their menu-selected AI flags only while that setting is enabled; ordinary battles retain the normal AI-flag setup path. Compiler debug logging remains a build-time facility.

When runtime debug mode is disabled, the in-battle Select menu is read-only and omits AI flags, AI knowledge, AI party state, miscellaneous mutation controls, and instant victory. Its reduced `AI Dmg` page calculates minimum and maximum damage against each of the player's species ability slots independently. It snapshots and restores battler and calculation state for every hypothetical ability and deliberately avoids displaying AI scores or using the AI's inferred player ability as the sole result.

If the player's ability has been publicly overwritten during battle, such as by Skill Swap, Trace, Worry Seed, Mummy, or Wandering Spirit, the `AI Dmg` page instead shows one column using that actual current ability. If the ability is actively suppressed by Gastro Acid or another battler's Neutralizing Gas, the page shows a single `None` column and calculates damage without a defender ability. This suppression check respects Ability Shield and abilities that cannot be suppressed, and deliberately ignores Mold Breaker so ordinary ability bypass does not change the column header. An unchanged natural ability continues to use all species slots so the display does not reveal the AI's prediction.

The read-only property pages use player-facing values rather than editor fields: PP is shown as current/maximum, stats use named numeric values, hazards show layers or presence, and statuses show `Active`/`Inactive`. Editor-only bulk actions such as the Moves and Stat Stages `All` entries are omitted. Their detail pages temporarily replace the complete main-list pane with a full-width, normal-font overlay, keeping labels on the left and right-aligning values within the visible screen bounds. Randomly determined remaining durations such as Sleep and Confusion are deliberately reduced to presence only. Public deterministic counters, including Toxic progression and fixed-duration effects such as Encore and Heal Block, remain visible.

Both full-debug and read-only menus provide a `Player Dmg` page. It calculates minimum and maximum rolls for the active player's moves against every living opposing battler using actual current battler abilities rather than AI-inferred ability state. Doubles show both opposing targets and allow L/R to change the active player attacker. The calculation snapshots and restores battler and shared damage-calculation state.

In the read-only `AI Dmg` page, the opposing attacker defaults to the opposing battler selected before opening the page, including battler 3. In doubles, L/R switches between living opposing attackers without changing the selected player defender.

The all-moves-bad switching check treats move scores below 98 as bad, leaving only moves close to the neutral baseline outside that switch trigger.

Key commits: `7ee8501957`, `dea75e5c6d`, `dc794373b3`, `3ee4fe2a78`, `272b903eeb`, `995fbe355c`.

## 4. Doubles coordination

### Damage-optimized target allocation

Each AI battler computes whether it can KO either opponent and stores a preferred KO target for the turn. Partners coordinate using KO timing, their relative speeds, and which target each partner can uniquely remove. This prevents both AI battlers from wasting attacks on the same target when they could secure two KOs or make better combined progress.

If neither immediate KO allocation applies, a battler can decline damage scoring on the current target when the other opponent is at least two hits easier to remove.

Key commits: `8d8f319d02`, `a27a48156d`, `7dfb075b05`, `934f83278c`.

### Partner-aware effect de-duplication

The AI reads its partner's chosen move and target so it can avoid duplicating:

- the same major move effect;
- the same guaranteed additional effect on the same target;
- redundant speed drops;
- Follow Me, Helping Hand, screens, and related support actions;
- support aimed at an ally that is switching or cannot benefit.

AI-controlled partner decisions are read from stored decisions rather than transient nested-calculation state.

Key commits: `c098ddca1c`, `321ef0e57c`.

### Speed-control simulation

Speed boosts and drops are judged by whether they actually flip a relevant speed relationship. In doubles, self-speed boosts focus on the faster opponent, while targeted drops consider whether that move is better aimed at the other foe and whether the partner has already covered the drop.

The logic also checks whether the opponent has a fast KO line and uses probabilistic scoring where speed control is helpful but not decisive. Rock Tomb received a dedicated doubles pass using these principles.

Key commits: `c098ddca1c`, `321ef0e57c`.

### Coaching and temporary state simulation

Coaching is evaluated by temporarily applying its Attack and Defense boosts to the ally, recomputing damage and survival, then reversing exactly the changes that were applied. The simulation respects stage limits, Contrary, Simple, ability-based stat-drop guards, Mold Breaker-like bypasses, and related edge cases.

The AI avoids Coaching when the partner will be removed before benefiting, and distinguishes fast and slow opponent KO lines when judging whether the defensive boost matters.

Key commits: `4a52d27b94`, `0d40937518`, `a0437698e7`, `0abf70faf9`.

## 5. Status, setup, and sustain heuristics

### Stat-lowering decisions

Dedicated `ShouldLower*` helpers evaluate each stat separately. They consider target immunity or punishment abilities, current stages, whether the target uses the corresponding offensive split, raw-stat estimates when moves are unknown, speed-order changes, and whether the AI should simply take an available KO.

The same predicates are reused by pure status moves, damaging moves with guaranteed drops, and pivot moves such as Parting Shot.

Key commits: `8e63c039d1`, `93531a3cea`, `6e5f7576f7`.

### Paralysis as tactical speed control

Paralysis scoring considers more than whether the target can be paralyzed. It values:

- flipping speed order;
- enabling flinch strategies;
- status-dependent power bonuses;
- synergy with existing infatuation;
- Prankster emergency use against a faster lethal opponent;
- Quick Feet and other cases where paralysis may help the target.

The incentive scales probabilistically with the number and strength of useful conditions.

Key commit: `50a6b64898`.

### Screens and anti-repetition memory

Reflect and Light Screen infer the opponent's likely attacking split from revealed attacks or raw stats. They account for screen-breaking moves and reduce repeated use when the opponent has demonstrated repeated screen removal. Move-history helpers provide consecutive-use and turns-ago queries for these decisions.

Key commits: `9b1bdd30a6`, `ab155b1388`.

### Recovery and Rest

Recovery logic compares healing against expected incoming damage, speed order, KO risk after healing, remaining party members, and repeated recovery use. Consecutive recovery effects receive a sliding probabilistic penalty, reaching a complete refusal after sustained repetition.

Rest receives separate survival estimates for its sleep turns and accounts for Early Bird and probabilistic Shed Skin curing. The AI avoids healing when it will still be KOed through the recovery amount.

Trainer-item healing uses similar logic: heal when the item changes survival or meaningfully outpaces expected damage, rather than at a fixed HP threshold alone.

Key commits: `6e5f7576f7`, `08b7585ba5`, `7ee8501957`.

### Setup and progress checks

Setup is discouraged when residual damage will KO the user, the opponent can immediately erase or exploit boosts, or the AI already has a clean KO. First-turn forced setup received a stronger explicit score, while ordinary setup remains conditional on expected survival and payoff.

Defense Curl specifically recognizes Rollout synergy and checks whether the user survives long enough to exploit it.

Key commits: `08e1147141`, `f3fb33af5a`, `efda8256b3`.

## 6. Bespoke effect integrations

The following move and custom-mechanic families received explicit AI treatment. These are important examples of how new effects currently enter the heuristic architecture.

- **Knock Off and item manipulation:** avoids generic item-removal bonuses overpowering damage logic; Trick, Switcheroo, Bestow, Sticky Barb, Ring Target, Sticky Hold, substitute, and item-transfer legality receive contextual checks. Commits: `8e63c039d1`, `93531a3cea`, `920ea368f5`, `cd5f2fdc9b`.
- **Parting Shot and pivoting:** reuses Attack and Special Attack reduction value, switch availability, target state, and pivot safety. Commits: `8e63c039d1`, `8911bb3be4`.
- **Pain Split:** estimates post-hit HP when moving second and scores the resulting split rather than using static HP thresholds. Commit: `6e5f7576f7`.
- **Soak:** checks whether the user can exploit Water typing with Electric, Grass, or Freeze-Dry-like effects, whether direct damage already wins quickly, danger to the user, and recent Soak use. Commit: `920ea368f5`.
- **Camouflage:** considers defensive value against inferred STABs, new STAB opportunities, terrain type, Flower Veil/Flower Shield synergy, and whether direct offense already 2HKOs. Commit: `6e5f7576f7`.
- **Mist and anti-stat-drop effects:** valued when the matchup is expected to last and the user is not in immediate lethal danger. Commit: `6e5f7576f7`.
- **Leech Seed:** values long-term progress only when immediate KO lines do not make it unnecessary and integrates seed pressure with recovery decisions. Commits: `50a6b64898`, `a9de966b7a`.
- **Water Sport and Mud Sport:** checks whether the opponent has known or inferred Fire/Electric offense, whether the user is weak to it, and custom Damp healing interactions. Commits: `9b7f7206c0`, `9fe2bc8d56`, `8911bb3be4`.
- **Damp healing and pivot synergy:** evaluates the custom Water Sport/Rain healing effect, survival after healing, and Flip Turn access. Commit: `8911bb3be4`.
- **Swallow and Stockpile:** uses the custom healing formula, HP bands, Stockpile count, and Gluttony synergy rather than upstream fixed assumptions. Commits: `c3e648e71c`, `8bd215017a`.
- **Echoed Voice:** recognizes its escalating custom effect and gives limited incentive when immediate offensive pressure is low and Torment does not block the sequence. Commits: `83efbbf34e`, `cd5f2fdc9b`.
- **Defense Curl and Rollout:** explicitly values the combo if the user can survive its setup turn. Commit: `f3fb33af5a`.
- **Refresh and team cleansing:** uses `ShouldCureStatus` so Refresh, Jungle Healing, and similar moves are valued only for statuses worth curing; custom Refresh can cure all relevant statuses. Commits: `6fc7851af8`, `6cf60d5e69`.
- **Follow Me and Helping Hand:** avoids use without a viable partner, against redundant partner support, when the ally is switching or using a status move, and when Good as Gold blocks the benefit. Commit: `6cf60d5e69`.
- **Tailwind, Magnet Rise, and speed support:** fixes target/type checks and evaluates whether speed changes cross actual thresholds for the user or ally. Commits: `c098ddca1c`, `6cf60d5e69`.
- **Drain Douse:** custom draining behavior was integrated into move-end absorption processing, and AI/test maintenance preserves its classification with other drain effects. Commits: `432b00e197`, `f3744907b1`, `be3390bd51`.
- **Metal Rush:** runtime chooses its Speed boost or Defense drop from effective weight. The Defense rider now follows ordinary stat-loss prevention, consistent with the AI's generic `CanLowerStat` policy; the custom weight-selected rider is not otherwise given bespoke AI utility scoring.
- **Custom defensive abilities:** AI calculations were adapted for Covered/Fur Layer, Illuminate accuracy behavior, Frisk item interactions, Forewarn's warned move, Damp healing, and other project-specific ability effects. Commits: `751228c71d`, `51107271f3`, `ece86112ff`, `1f6633f157`, `8911bb3be4`.

## 7. Terastalization logic

### Defensive Tera decision

`AI_ShouldTerastal` compares the battler's current defensive typing with its Tera type against the opponent's known or inferred STABs. It avoids Tera when doing so introduces a new STAB weakness, removes a valuable immunity or double resistance, or otherwise worsens immediate survival. If Tera has no defensive type cost, the AI is generally willing to use it.

Damage simulation can evaluate the AI's own prospective Tera defensively, but it does not pre-emptively assume an uncommitted player Tera.

Key commits: `7fdbe2f144`, `bd8658f64c`, `10f438d2f0`, `7829b03a9c`.

## 8. Architecture observations for examination

### Strengths

- The system has a rich imperfect-information model instead of a single omniscience toggle.
- Many decisions are expressed in reusable predicates for survival, stat value, move knowledge, and speed order.
- Temporary simulation enables tactical evaluation of Coaching, Tera, resist berries, and binding sequences.
- Doubles logic explicitly coordinates partner targets and support effects.
- RNG is often used intentionally to prevent a correct heuristic from becoming deterministic and exploitable.

### Structural pressure points
- Several simulations temporarily mutate global battle or AI state and must restore it exactly. Nested calculations can invalidate assumptions about transient globals.
- Singles and doubles concerns are interleaved in large scoring functions.
- Knowledge policy is not completely uniform: held items are currently fully known while moves, abilities, and party information remain graduated.
- Many heuristics combine hard rejection, additive scoring, and probability gates, making global behavior difficult to reason about compositionally.
