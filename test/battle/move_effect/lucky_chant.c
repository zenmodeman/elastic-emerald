#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Lucky Chant prevents critical hits on the user's side")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_LUCKY_CHANT) == EFFECT_LUCKY_CHANT);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_LUCKY_CHANT); MOVE(player, MOVE_SCRATCH, criticalHit: TRUE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        NOT MESSAGE("A critical hit!");
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Lucky Chant gains a turn when used after all opponents have acted")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_LUCKY_CHANT) == EFFECT_LUCKY_CHANT);
        PLAYER(SPECIES_WOBBUFFET) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(50); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_LUCKY_CHANT); }
    } THEN {
        EXPECT_EQ(gSideTimers[B_SIDE_OPPONENT].luckyChantTimer, 5);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Lucky Chant is extended by three turns by Dedicated")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_LUCKY_CHANT) == EFFECT_LUCKY_CHANT);
        PLAYER(SPECIES_WOBBUFFET) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_DEDICATED); Speed(50); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_LUCKY_CHANT); }
    } THEN {
        EXPECT_EQ(gSideTimers[B_SIDE_OPPONENT].luckyChantTimer, 8);
    }
}
