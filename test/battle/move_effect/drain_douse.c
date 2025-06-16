#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveEffect(MOVE_DRAIN_DOUSE) == EFFECT_DRAIN_DOUSE);
}

SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse inflicts a status that causes attacks to heal 50% of damage dealt")
{
    s16 damage;
    s16 healed;
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) 
        OPPONENT(SPECIES_WOBBUFFET) {HP(1);}
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { MOVE(opponent, MOVE_MEGA_KICK); }
    } SCENE {
        // First turn - Drain Douse is used
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAIN_DOUSE, player);

        // Second turn - Opponent attacks and gets healing
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MEGA_KICK, opponent);
        HP_BAR(player, captureDamage: &damage);
        HP_BAR(opponent, captureDamage: &healed);
    } THEN {
        EXPECT_MUL_EQ(damage, Q_4_12(-0.5), healed);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse healing is inverted when attacking a Liquid Ooze Pokémon")
{
    s16 targetDamage;
    s16 attackerDamage;
    GIVEN {
        PLAYER(SPECIES_TENTACOOL) { Ability(ABILITY_LIQUID_OOZE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { MOVE(opponent, MOVE_MEGA_KICK); }
    } SCENE {
        // First turn - Drain Douse is used
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAIN_DOUSE, player);
        
        // Second turn - Opponent attacks and loses HP due to Liquid Ooze
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MEGA_KICK, opponent);
        HP_BAR(player, captureDamage: &targetDamage);
        HP_BAR(opponent, captureDamage: &attackerDamage);
    } THEN {
        EXPECT_MUL_EQ(targetDamage, Q_4_12(0.5), attackerDamage);
    }
}


// SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse healing stacks with moves that already heal")
// {
//     s16 damage;
//     s16 healedFromMove;
//     s16 healedFromDrainDouse;
//     GIVEN {
//         ASSUME(GetMoveEffect(MOVE_ABSORB) == EFFECT_ABSORB);
//         PLAYER(SPECIES_WOBBUFFET) { HP(1); }
//         OPPONENT(SPECIES_WOBBUFFET) { HP(1); }
//     } WHEN {
//         TURN { MOVE(opponent, MOVE_DRAIN_DOUSE); }
//         TURN { MOVE(opponent, MOVE_ABSORB); }
//     } SCENE {
//         // First turn - Drain Douse is used
//         ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAIN_DOUSE, opponent);
        
//         // Second turn - Opponent uses Absorb which has its own healing
//         ANIMATION(ANIM_TYPE_MOVE, MOVE_ABSORB, opponent);
//         HP_BAR(player, captureDamage: &damage);
//         // First healing from Absorb's effect
//         HP_BAR(opponent, captureDamage: &healedFromMove);
//         // Second healing from Drain Douse status
//         HP_BAR(opponent, captureDamage: &healedFromDrainDouse);
//     } THEN {
//         // Absorb heals 50% of damage
//         EXPECT_MUL_EQ(damage, Q_4_12(0.5), healedFromMove);
//         // Drain Douse also heals 50% of damage
//         EXPECT_MUL_EQ(damage, Q_4_12(0.5), healedFromDrainDouse);
//     }
// }

// DOUBLE_BATTLE_TEST("Zenmodeman: Drain Douse with spread move heals from sum of damage dealt")
// {
//     s16 damageLeft;
//     s16 damageRight;
//     s16 healed;
//     GIVEN {
//         PLAYER(SPECIES_WOBBUFFET);
//         PLAYER(SPECIES_WYNAUT);
//         OPPONENT(SPECIES_WOBBUFFET) { HP(1); }
//         OPPONENT(SPECIES_WYNAUT);
//     } WHEN {
//         TURN { MOVE(playerLeft, MOVE_DRAIN_DOUSE, target: opponentLeft); }
//         TURN { MOVE(opponentLeft, MOVE_EARTHQUAKE); }
//     } SCENE {
//         // First turn - Drain Douse is used
//         ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAIN_DOUSE, playerLeft);
        
//         // Second turn - Opponent uses Earthquake (hits both player Pokémon)
//         ANIMATION(ANIM_TYPE_MOVE, MOVE_EARTHQUAKE, opponentLeft);
//         HP_BAR(playerLeft, captureDamage: &damageLeft);
//         HP_BAR(playerRight, captureDamage: &damageRight);
//         HP_BAR(opponentLeft, captureDamage: &healed);
//     } THEN {
//         // Should heal 50% of the total damage dealt to both targets
//         EXPECT_MUL_EQ(damageLeft + damageRight, Q_4_12(0.5), healed);
//     }
// }

// DOUBLE_BATTLE_TEST("Zenmodeman: Drain Douse with mixed Liquid Ooze targets calculates net healing")
// {
//     s16 damageNormal;
//     s16 damageOoze;
//     s16 healedAmount;
//     GIVEN {
//         PLAYER(SPECIES_WOBBUFFET);
//         PLAYER(SPECIES_TENTACOOL) { Ability(ABILITY_LIQUID_OOZE); }
//         OPPONENT(SPECIES_WOBBUFFET);
//         OPPONENT(SPECIES_WYNAUT);
//     } WHEN {
//         TURN { MOVE(opponentLeft, MOVE_DRAIN_DOUSE, target: playerLeft); }
//         TURN { MOVE(opponentLeft, MOVE_EARTHQUAKE); }
//     } SCENE {
//         // First turn - Drain Douse is used
//         ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAIN_DOUSE, opponentLeft);
        
//         // Second turn - Opponent uses Earthquake (hits both player Pokémon)
//         ANIMATION(ANIM_TYPE_MOVE, MOVE_EARTHQUAKE, opponentLeft);
//         HP_BAR(playerLeft, captureDamage: &damageNormal);
//         HP_BAR(playerRight, captureDamage: &damageOoze);
        
//         // Calculate expected net healing
//         s16 expectedHealing = (damageNormal * 0.5) - (damageOoze * 0.5);
        
//         if (expectedHealing > 0) {
//             // Net positive healing
//             HP_BAR(opponentLeft, captureDamage: &healedAmount);
//             EXPECT_EQ(healedAmount, expectedHealing);
//         } else {
//             // Net negative healing (damage from Liquid Ooze)
//             ABILITY_POPUP(playerRight, ABILITY_LIQUID_OOZE);
//             MESSAGE("The opposing Wobbuffet sucked up the liquid ooze!");
//             HP_BAR(opponentLeft, captureDamage: &healedAmount);
//             EXPECT_EQ(healedAmount, expectedHealing);
//         }
//     }
// }

// DOUBLE_BATTLE_TEST("Zenmodeman: Drain Douse healing only considers damage from current attack")
// {
//     s16 damageFromFirst;
//     s16 damageFromSecond;
//     s16 healed;
//     GIVEN {
//         PLAYER(SPECIES_WOBBUFFET) { HP(100); MaxHP(100); }
//         PLAYER(SPECIES_WYNAUT);
//         OPPONENT(SPECIES_WOBBUFFET) { HP(1); }
//         OPPONENT(SPECIES_WYNAUT);
//     } WHEN {
//         TURN { MOVE(playerLeft, MOVE_DRAIN_DOUSE, target: opponentLeft); }
//         TURN { 
//             MOVE(opponentLeft, MOVE_TACKLE, target: playerLeft); 
//             MOVE(opponentRight, MOVE_TACKLE, target: playerLeft);
//         }
//     } SCENE {
//         // First turn - Drain Douse is used
//         ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAIN_DOUSE, playerLeft);
        
//         // Second turn - First opponent attacks
//         ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, opponentLeft);
//         HP_BAR(playerLeft, captureDamage: &damageFromFirst);
//         HP_BAR(opponentLeft, captureDamage: &healed);
        
//         // Second opponent attacks - should not heal from previous damage
//         ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, opponentRight);
//         HP_BAR(playerLeft, captureDamage: &damageFromSecond);
//         // No healing should occur for the second opponent
//     } THEN {
//         // Only the first opponent should heal
//         EXPECT_MUL_EQ(damageFromFirst, Q_4_12(0.5), healed);
//     }
// }

// DOUBLE_BATTLE_TEST("Zenmodeman: Drain Douse works correctly with Protect")
// {
//     s16 damage;
//     s16 healed;
//     GIVEN {
//         PLAYER(SPECIES_WOBBUFFET);
//         PLAYER(SPECIES_WYNAUT);
//         OPPONENT(SPECIES_WOBBUFFET) { HP(1); }
//         OPPONENT(SPECIES_WYNAUT);
//     } WHEN {
//         TURN { MOVE(playerLeft, MOVE_DRAIN_DOUSE, target: opponentLeft); }
//         TURN { 
//             MOVE(playerLeft, MOVE_PROTECT);
//             MOVE(opponentLeft, MOVE_EARTHQUAKE);
//         }
//     } SCENE {
//         // First turn - Drain Douse is used
//         ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAIN_DOUSE, playerLeft);
        
//         // Second turn - Player protects
//         ANIMATION(ANIM_TYPE_MOVE, MOVE_PROTECT, playerLeft);
        
//         // Opponent uses Earthquake
//         ANIMATION(ANIM_TYPE_MOVE, MOVE_EARTHQUAKE, opponentLeft);
//         MESSAGE("Wobbuffet protected itself!");
//         HP_BAR(playerRight, captureDamage: &damage); // Only right player takes damage
//         HP_BAR(opponentLeft, captureDamage: &healed);
//     } THEN {
//         // Should only heal from damage to unprotected Pokémon
//         EXPECT_MUL_EQ(damage, Q_4_12(0.5), healed);
//     }
// }

// SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse healing doesn't trigger message if at full HP")
// {
//     GIVEN {
//         PLAYER(SPECIES_WOBBUFFET);
//         OPPONENT(SPECIES_WOBBUFFET) { MaxHP(100); HP(100); }
//     } WHEN {
//         TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
//         TURN { MOVE(opponent, MOVE_TACKLE); }
//     } SCENE {
//         // First turn - Drain Douse is used
//         ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAIN_DOUSE, player);
        
//         // Second turn - Opponent attacks at full HP
//         ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, opponent);
//         HP_BAR(player);
        
//         // No healing message should appear since opponent is at full HP
//         NONE_OF {
//             MESSAGE("The opposing Wobbuffet drained energy with its liquid!");
//         }
//     }
// }

// SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse healing triggers Liquid Ooze message even at full HP")
// {
//     GIVEN {
//         PLAYER(SPECIES_TENTACOOL) { Ability(ABILITY_LIQUID_OOZE); }
//         OPPONENT(SPECIES_WOBBUFFET) { MaxHP(100); HP(100); }
//     } WHEN {
//         TURN { MOVE(opponent, MOVE_DRAIN_DOUSE); }
//         TURN { MOVE(opponent, MOVE_TACKLE); }
//     } SCENE {
//         // First turn - Drain Douse is used
//         ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAIN_DOUSE, opponent);
        
//         // Second turn - Opponent attacks and loses HP due to Liquid Ooze
//         ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, opponent);
//         HP_BAR(player);
//         HP_BAR(opponent);
//         ABILITY_POPUP(player, ABILITY_LIQUID_OOZE);
//         MESSAGE("The opposing Wobbuffet sucked up the liquid ooze!");
//     }
// }


