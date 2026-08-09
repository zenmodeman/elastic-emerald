#include "global.h"
#include "test/battle.h"

AI_SINGLE_BATTLE_TEST("Zenmodeman: Defense Curl AI values Rollout setup only when it can survive two hits", enum Move playerMove)
{
    enum Move playerMove;

    PARAMETRIZE { playerMove = MOVE_SCRATCH; }
    PARAMETRIZE { playerMove = MOVE_HYPER_BEAM; }
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT | AI_FLAG_OMNISCIENT);
        PLAYER(SPECIES_WOBBUFFET) { Moves(playerMove); Attack(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_DEFENSE_CURL, MOVE_ROLLOUT); HP(200); MaxHP(200); Defense(100); }
    } WHEN {
        if (playerMove == MOVE_SCRATCH)
            TURN { MOVE(player, playerMove); SCORE_EQ_VAL(opponent, MOVE_DEFENSE_CURL, AI_SCORE_DEFAULT + 3); }
        else
            TURN { MOVE(player, playerMove); SCORE_EQ_VAL(opponent, MOVE_DEFENSE_CURL, AI_SCORE_DEFAULT + 2); }
    }
}

AI_SINGLE_BATTLE_TEST("Zenmodeman: screen AI infers an unknown attacker's likely damage split from raw stats", u16 attack, u16 spAttack, enum Move expectedMove)
{
    u16 attack;
    u16 spAttack;
    enum Move expectedMove;

    PARAMETRIZE { attack = 150; spAttack = 50; expectedMove = MOVE_REFLECT; }
    PARAMETRIZE { attack = 50; spAttack = 150; expectedMove = MOVE_LIGHT_SCREEN; }
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_SCRATCH); Attack(attack); SpAttack(spAttack); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_REFLECT, MOVE_LIGHT_SCREEN, MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); EXPECT_MOVE(opponent, expectedMove); }
    }
}

AI_SINGLE_BATTLE_TEST("Zenmodeman: screen AI respects a revealed attack category over raw stat inference")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_OMNISCIENT);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_SWIFT); Attack(150); SpAttack(50); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_REFLECT, MOVE_LIGHT_SCREEN, MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_SWIFT); EXPECT_MOVE(opponent, MOVE_LIGHT_SCREEN); }
    }
}
