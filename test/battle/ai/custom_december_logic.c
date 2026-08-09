#include "global.h"
#include "test/battle.h"
#include "battle_ai_main.h"
#include "battle_ai_util.h"

SINGLE_BATTLE_TEST("Zenmodeman: AI move history retains the prior three-turn observation order")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_TACKLE); }
        TURN { MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TACKLE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
    } THEN {
        EXPECT_EQ(FindMoveUsedXTurnsAgo(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), 1), MOVE_TACKLE);
    }
}

AI_SINGLE_BATTLE_TEST("Zenmodeman: AI values giving Ring Target to a foe")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_RING_TARGET].holdEffect == HOLD_EFFECT_RING_TARGET);
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Item(ITEM_RING_TARGET); Moves(MOVE_TRICK, MOVE_CELEBRATE); }
    } WHEN {
        TURN { SCORE_EQ_VAL(opponent, MOVE_TRICK, AI_SCORE_DEFAULT + WEAK_EFFECT); }
    }
}

AI_SINGLE_BATTLE_TEST("Zenmodeman: Soak AI skips setup when it already has a two-hit KO", u16 spAttack, s32 expectedScore)
{
    u16 spAttack;
    s32 expectedScore;

    PARAMETRIZE { spAttack = 1;   expectedScore = AI_SCORE_DEFAULT + DECENT_EFFECT; }
    PARAMETRIZE { spAttack = 500; expectedScore = AI_SCORE_DEFAULT; }

    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT | AI_FLAG_OMNISCIENT);
        PLAYER(SPECIES_WOBBUFFET) { HP(200); MaxHP(200); }
        OPPONENT(SPECIES_WOBBUFFET) { SpAttack(spAttack); Moves(MOVE_SOAK, MOVE_THUNDER_SHOCK); }
    } WHEN {
        TURN { SCORE_EQ_VAL(opponent, MOVE_SOAK, expectedScore); }
    }
}

AI_SINGLE_BATTLE_TEST("Zenmodeman: Soak AI skips setup when the target can KO first", u16 playerSpAttack, s32 expectedScore)
{
    u16 playerSpAttack;
    s32 expectedScore;

    PARAMETRIZE { playerSpAttack = 1;   expectedScore = AI_SCORE_DEFAULT + DECENT_EFFECT; }
    PARAMETRIZE { playerSpAttack = 500; expectedScore = AI_SCORE_DEFAULT; }

    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT | AI_FLAG_OMNISCIENT);
        PLAYER(SPECIES_WOBBUFFET) { SpAttack(playerSpAttack); Moves(MOVE_PSYCHIC); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(100); MaxHP(100); SpDefense(1); SpAttack(1); Moves(MOVE_SOAK, MOVE_THUNDER_SHOCK); }
    } WHEN {
        TURN { SCORE_EQ_VAL(opponent, MOVE_SOAK, expectedScore); }
    }
}
