# Custom Battle AI Logic Summary

## Documentation status

- **Last documented code commit:** `9febfb4eb7` ("Additional tests and merge restorations").
- **Previously uncommitted changes now identified in history:** Cut's Grass-target critical-hit stage is in `ec25d70aa6`; curated fallback Tera assignment is in `eb69f0ece0`; singles matchup-commitment switching is in `53239d220d`. These references reconcile the previously documented changes without claiming review of all intervening AI changes.
- **Uncommitted AI changes covered by this document:** Restricted Mode ignores Choice Band and Choice Scarf effects for player-owned Pokémon with active Gorilla Tactics, including AI held-effect modeling and shared damage/Speed calculations. The historical backward audit also restores Powder's complete-moveset knowledge guard on the current AI API.

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

Regression tests pin both sides of that contract: all prediction and imperfect-information assumption flags must remain present, while `AI_FLAG_OMNISCIENT` and `AI_FLAG_PP_STALL_PREVENTION` must remain absent.

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

Powder is rejected for lacking a Fire target move only after all four target move slots are known. With an incomplete moveset, the AI preserves Powder as a candidate instead of treating unrevealed slots as proof that no Fire move exists. Omniscient trainers naturally satisfy the complete-knowledge condition; ordinary trainers can satisfy it through revealed or inferred move history.

Unrevealed STAB estimates are filtered to avoid implausible predictions such as unusable recharge or two-turn attacks. When no attacks are known, physical-versus-special expectations can fall back to raw offensive stats with a level-sensitive comparison threshold.

Key commits: `59b76d3fcd`, `4bb634c651`, `829ec9c367`, `7ee8501957`.

### Item and ability revelation hooks

Earlier iterations recorded inferable items when their effects became visible, including Life Orb, Float Stone, Eviolite, and Assault Vest. Frisk was expanded to interact with item-manipulating moves. Forewarn stores its announced move in switch-cleared volatile state and halves damage from that move only; because this modifier is in the shared damage path, AI estimates and live damage remain aligned.

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

### Befuddle status modeling

Befuddle is a 70-power special Bug-type spread move with a guaranteed additional effect that independently attempts to paralyze, poison, or put each foe to sleep. It uses the existing per-target random-status handling shared with Dire Claw, so status immunities, Protect, and Sleep Clause remain aligned with ordinary damaging-move execution.

Key commit: `02b670576c`.

### Chilling Water Ice-type power boost

Chilling Water receives an additional 1.5x power modifier when its user is currently Ice-type. The check uses the battler's active battle types, including temporary type changes and Terastallization. Because the modifier lives in the shared damage calculation, live battle damage and AI damage estimates use the same rule.

Key commit: `67fd498d45`.

### Merry activation and calculation parity

Merry activates once its user completes Present, Heal Pulse, or Bestow. The resulting volatile state multiplies power, accuracy, and Speed by 1.5. Power is applied in the shared damage context and Speed and accuracy use the same helpers consumed by AI evaluation, so the AI's damage estimates, move reliability, and turn-order model stay aligned with live execution.

Key commit: `78fdff7719`.

### Perplex Dance

Perplex Dance is Spinda's priority signature status move. The AI values its two-stage Attack and Sp. Atk drops through the shared stat-change scorer, penalizes the move's self-confusion drawback when applicable, and therefore recognizes Own Tempo as removing that drawback. In doubles, partners avoid redundantly selecting it into the same target, and the move is rejected when both affected stats are already minimized.

Key commit: `04e8acf271`.

## 3. Imperfect-information switching and counterplay

### Matchup commitment for fast-KO switching

In singles, an active Pokemon using `AI_FLAG_SMART_SWITCHING` may switch from a fast KO while it remains uncommitted to the matchup. The shared safeguards still require the player to be faster, an actual-state calculation using revealed moves plus Hidden STAB inference to find a KO, a suitable switch-in, and at least 75% HP for most Pokemon or 50% HP for Regenerator Pokemon. Slow KOs do not trigger this path, and the final switch remains a 50% roll.

An opposing Pokemon becomes committed after it successfully resolves a move during a turn in which the player's active Pokemon never switches. Damaging, status, and self-targeting moves all qualify. Failure to act and no-effect results such as misses, immunity, failure, or Protect do not qualify. Commitment is finalized at the end of the turn so a player pivot that occurs after the opposing move still prevents commitment to the old matchup. The state persists for that active Pokemon's field stint and resets when it switches out.

This commitment gate applies only to the fast-KO reason. Perish Song, ineffective Encore or choice locks, and the other independent switch reasons retain their own rules. Weather setters no longer receive a separate preservation path, and the heavy-switching and defensive-drop entry checks are suppressed.

Focused regression coverage verifies the initial uncommitted switch, successful attacks and self-targeting moves, Protect-blocked moves, player pivots, the HP thresholds, faster-threat requirement, and ordinary survival checks.

Key commit: `53239d220d`.

### Scrapped generalized fast-KO experiments

Earlier versions attempted broad fast-KO preservation based on revealed versus inferred damage, literal-lead recognition, quad-effective Hidden STAB windows, and a clean-state simulation that removed player-created type, ability, grounding, immunity-bypass, defensive-stage, and Speed-stage changes. That approach was removed because its complexity produced little payoff and could over-penalize ordinary offensive Pokemon and player tech moves. The current commitment rule restores only the narrow actual-state fast-KO core; the concise older history is retained here for context.

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

The logic also checks whether the opponent has a fast KO line and uses probabilistic scoring where speed control is helpful but not decisive. Rock Tomb received a dedicated doubles pass using these principles. The restored partner check temporarily applies the partner's guaranteed Speed drop to both the target's stage and the AI's cached Speed value, tests whether that already establishes the desired ordering, and restores both values before continuing. A focused doubles regression test ensures a second Rock Tomb is not rewarded over Rock Slide once the partner has already covered the useful Speed drop.

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

The raw-stat fallback is used only while the opponent's complete moveset is not known and no damaging move has been revealed or inferred. Once the AI knows an attack category, that evidence takes precedence over the fallback.

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

- **Knock Off and item manipulation:** avoids generic item-removal bonuses overpowering damage logic; Trick, Switcheroo, Bestow, Sticky Barb, Ring Target, Sticky Hold, substitute, and item-transfer legality receive contextual checks. Resource Mode additionally treats Trick/Switcheroo as unusable when a wild consumable would move to the player; damaging steal moves keep their damage while their shared legality check suppresses the transfer. Commits: `8e63c039d1`, `93531a3cea`, `920ea368f5`, `cd5f2fdc9b`, `0799104ebb`.
- **Parting Shot and pivoting:** reuses Attack and Special Attack reduction value, switch availability, target state, and pivot safety. Commits: `8e63c039d1`, `8911bb3be4`.
- **Pain Split:** estimates post-hit HP when moving second and scores the resulting split rather than using static HP thresholds. Commit: `6e5f7576f7`.
- **Soak:** checks whether the user can exploit Water typing with Electric, Grass, or Freeze-Dry-like effects, whether direct damage already wins quickly, danger to the user, and recent Soak use. Commit: `920ea368f5`.
- **Camouflage:** considers defensive value against inferred STABs, new STAB opportunities, terrain type, Flower Veil/Flower Shield synergy, and whether direct offense already 2HKOs. Commit: `6e5f7576f7`.
- **Mist and anti-stat-drop effects:** valued when the matchup is expected to last and the user is not in immediate lethal danger. Commit: `6e5f7576f7`.
- **Leech Seed:** values long-term progress only when immediate KO lines do not make it unnecessary and integrates seed pressure with recovery decisions. Commits: `50a6b64898`, `a9de966b7a`.
- **Water Sport and Mud Sport:** checks only opposing targets for known damaging Fire/Electric offense and rewards the protection only when the user does not resist that type. The older generic any-move heuristic was a merge regression; the current port uses current move-knowledge and type APIs. Commits: `9b7f7206c0`, `9fe2bc8d56`, `8911bb3be4`, `9febfb4eb7`.
- **Damp healing and pivot synergy:** Water Sport gains extra value when a Damp user has a damaging pivot, a usable reserve, and survives after the one-third heal; once Water Sport is active, Damp adds an extra incentive to hit-and-switch effects. Commits: `8911bb3be4`, `9febfb4eb7`.
- **Swallow and Stockpile:** uses the custom healing formula, HP bands, Stockpile count, and Gluttony synergy rather than upstream fixed assumptions. Commits: `c3e648e71c`, `8bd215017a`.
- **Echoed Voice:** recognizes its escalating custom effect and gives limited incentive when immediate offensive pressure is low and Torment does not block the sequence. Commits: `83efbbf34e`, `cd5f2fdc9b`.
- **Defense Curl and Rollout:** explicitly values the combo if the user can survive its setup turn. Commit: `f3fb33af5a`.
- **Refresh and team cleansing:** uses `ShouldCureStatus` so Refresh, Jungle Healing, and similar moves are valued only for statuses worth curing; custom Refresh can cure all relevant statuses. Commits: `6fc7851af8`, `6cf60d5e69`.
- **Follow Me and Helping Hand:** avoids use without a viable partner, against redundant partner support, when the ally is switching or using a status move, and when Good as Gold blocks the benefit. Commit: `6cf60d5e69`.
- **Tailwind, Magnet Rise, and speed support:** fixes target/type checks and evaluates whether speed changes cross actual thresholds for the user or ally. Commits: `c098ddca1c`, `6cf60d5e69`.
- **Drain Douse:** custom draining behavior was integrated into move-end absorption processing, and AI/test maintenance preserves its classification with other drain effects. Commits: `432b00e197`, `f3744907b1`, `be3390bd51`.
- **Metal Rush:** runtime chooses its Speed boost or Defense drop from effective weight. The Defense rider now follows ordinary stat-loss prevention, consistent with the AI's generic `CanLowerStat` policy; the custom weight-selected rider is not otherwise given bespoke AI utility scoring.
- **Custom defensive, offensive, and status abilities:** AI calculations were adapted for Covered/Fur Layer, Illuminate accuracy behavior, Frisk item interactions, Forewarn's warned move, Damp healing, and other project-specific ability effects. Mystic multiplies Psychic move power by 1.5 in the shared damage pipeline, while Dominate follows Download's switch-in comparison and raises Attack or Special Attack accordingly. Astral Charge raises Special Attack by one stage after its bearer takes an effective damaging Psychic- or Fairy-type hit; status moves and ineffective hits do not trigger it. The shared burn modifier also treats Hyper Cutter and Flare Boost like Guts for physical attacks, so live damage and AI estimates omit burn's halving penalty for those abilities. Commits: `751228c71d`, `51107271f3`, `ece86112ff`, `1f6633f157`, `8911bb3be4`, `06ed994876`, `007c0519bb`, `9fcc4a7c21`, `9129bf865f`, `9febfb4eb7`.
- **Solar Core and Big Pecks parity:** the shared damage calculation again applies Solar Core's doubled special Attack in effective sun and preserves Big Pecks' physical defensive stages and Reflect/Aurora Veil protection against critical hits and Chip Away, so runtime and AI damage estimates use the same restored custom rules. Restoration commit: `9febfb4eb7`.

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

### Restricted Mode Gorilla Tactics and Choice items

Choice Band and Choice Scarf return no effective held-item effect while Gorilla Tactics is active on a player-owned Pokémon in Restricted Mode. Opponents and AI-controlled partners retain their Choice-item effects. The shared damage and Speed helpers also apply this rule using their supplied ability, so AI simulations use their modeled ability rather than discovering a hidden one. The normal AI held-effect cache applies the same filter after its existing negation checks; the suppression-unaware handicap retains its existing early return. Gorilla Tactics keeps its own Attack boost and move lock. Choice Specs and unrestricted battles retain their normal effects. Suppressing or replacing Gorilla Tactics restores normal item behavior, subject to other item-negation rules. The held item itself remains present.

Key commit: uncommitted.
