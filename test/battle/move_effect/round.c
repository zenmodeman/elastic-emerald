#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveEffect(MOVE_ROUND) == EFFECT_ROUND);
}

SINGLE_BATTLE_TEST("Zenmodeman: Round does not carry its power boost into the next turn after an earlier battler cannot move")
{
    s16 damage[2];
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Status1(STATUS1_SLEEP_TURN(3)); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_ROUND); MOVE(opponent, MOVE_ROUND); }
        TURN { MOVE(player, MOVE_ROUND); MOVE(opponent, MOVE_ROUND); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROUND, opponent);
        HP_BAR(player, captureDamage: &damage[0]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROUND, opponent);
        HP_BAR(player, captureDamage: &damage[1]);
    } THEN {
        EXPECT_EQ(damage[0], damage[1]);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Round boosts a later use on either side and resets before the next turn")
{
    s16 damage[3];
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_ROUND); MOVE(opponent, MOVE_ROUND); }
        TURN { MOVE(player, MOVE_ROUND); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROUND, player);
        HP_BAR(opponent, captureDamage: &damage[0]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROUND, opponent);
        HP_BAR(player, captureDamage: &damage[1]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROUND, player);
        HP_BAR(opponent, captureDamage: &damage[2]);
    } THEN {
        EXPECT_MUL_EQ(damage[0], Q_4_12(2.0), damage[1]);
        EXPECT_EQ(damage[0], damage[2]);
    }
}

DOUBLE_BATTLE_TEST("Zenmodeman: Round chains restart at base power each turn")
{
    s16 damage[4];
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {
            MOVE(opponentLeft, MOVE_ROUND, target: playerLeft);
            MOVE(opponentRight, MOVE_ROUND, target: playerLeft);
        }
        TURN {
            MOVE(opponentLeft, MOVE_ROUND, target: playerLeft);
            MOVE(opponentRight, MOVE_ROUND, target: playerLeft);
        }
    } SCENE {
        HP_BAR(playerLeft, captureDamage: &damage[0]);
        HP_BAR(playerLeft, captureDamage: &damage[1]);
        HP_BAR(playerLeft, captureDamage: &damage[2]);
        HP_BAR(playerLeft, captureDamage: &damage[3]);
    } THEN {
        EXPECT_MUL_EQ(damage[0], Q_4_12(2.0), damage[1]);
        EXPECT_EQ(damage[0], damage[2]);
        EXPECT_EQ(damage[1], damage[3]);
    }
}

DOUBLE_BATTLE_TEST("Round allows other battlers which also selected the moves to immediately use the move, ignoring turn order")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_LAGGING_TAIL].holdEffect == HOLD_EFFECT_LAGGING_TAIL);
        ASSUME(GetMoveAdditionalEffectById(MOVE_IRON_HEAD, 0)->moveEffect == MOVE_EFFECT_FLINCH);
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Item(ITEM_LAGGING_TAIL); }
    } WHEN {
        TURN {
            MOVE(playerRight, MOVE_CELEBRATE);
            MOVE(opponentLeft, MOVE_ROUND, target: playerLeft);
            MOVE(playerLeft, MOVE_IRON_HEAD, target: opponentRight);
            MOVE(opponentRight, MOVE_ROUND, target: playerLeft);
        }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, playerRight);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROUND, opponentLeft);
        NOT ANIMATION(ANIM_TYPE_MOVE, MOVE_IRON_HEAD, playerLeft);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROUND, opponentRight);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_IRON_HEAD, playerLeft);
    }
}

DOUBLE_BATTLE_TEST("Round usages beyond the first one has double base power")
{
    s16 damage[2];
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {
            MOVE(opponentLeft, MOVE_ROUND, target: playerLeft);
            MOVE(opponentRight, MOVE_ROUND, target: playerLeft);
        }
    } SCENE {
        HP_BAR(playerLeft, captureDamage: &damage[0]);
        HP_BAR(playerLeft, captureDamage: &damage[1]);
    } THEN {
        EXPECT_MUL_EQ(damage[0], Q_4_12(2.0), damage[1]);
    }
}

DOUBLE_BATTLE_TEST("Round still preserves the turn order outside of the other Round users moving immediately")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {
            MOVE(opponentLeft, MOVE_ROUND, target: playerLeft);
            MOVE(playerRight, MOVE_CELEBRATE);
            MOVE(playerLeft, MOVE_CELEBRATE);
            MOVE(opponentRight, MOVE_ROUND, target: playerLeft); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROUND, opponentLeft);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROUND, opponentRight);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, playerRight);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, playerLeft);
    }
}
DOUBLE_BATTLE_TEST("Round still preserves the turn order outside of the other Round users moving immediately with switch")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WYNAUT);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {
            SWITCH(playerRight, 2);
            MOVE(opponentLeft, MOVE_ROUND, target: playerLeft);
            MOVE(playerLeft, MOVE_CELEBRATE);
            MOVE(opponentRight, MOVE_ROUND, target: playerLeft);
        }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROUND, opponentLeft);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROUND, opponentRight);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, playerLeft);
    }
}

DOUBLE_BATTLE_TEST("Round causes opposing Pokémon to use Round immediately")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_LAGGING_TAIL].holdEffect == HOLD_EFFECT_LAGGING_TAIL);
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Item(ITEM_LAGGING_TAIL); }
    } WHEN {
        TURN { MOVE(opponentLeft, MOVE_CELEBRATE); MOVE(playerRight, MOVE_ROUND, target: opponentLeft); MOVE(playerLeft, MOVE_CELEBRATE, target: opponentRight); MOVE(opponentRight, MOVE_ROUND, target: playerLeft); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponentLeft);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROUND, playerRight);
        NOT ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, playerLeft);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROUND, opponentRight);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, playerLeft);
    }
}

DOUBLE_BATTLE_TEST("Round usages beyond the first one has double base power even if the first attacker fainted")
{
    s16 damage[2];
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); Item(ITEM_LIFE_ORB); }
        OPPONENT(SPECIES_WOBBUFFET) { Item(ITEM_LIFE_ORB); }
    } WHEN {
        TURN {
            MOVE(opponentLeft, MOVE_ROUND, target: playerLeft);
            MOVE(opponentRight, MOVE_ROUND, target: playerLeft);
        }
    } SCENE {
        HP_BAR(playerLeft, captureDamage: &damage[0]);
        HP_BAR(playerLeft, captureDamage: &damage[1]);
    } THEN {
        EXPECT_MUL_EQ(damage[0], Q_4_12(2.0), damage[1]);
    }
}
