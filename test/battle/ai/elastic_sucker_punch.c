#include "global.h"
#include "test/battle.h"
#include "battle_ai_util.h"
#include "battle_ai_record.h"

AI_SINGLE_BATTLE_TEST("Elastic-tests: first Sucker Punch ignores status prediction and the player's selected action")
{
    u32 playerMove;
    PARAMETRIZE { playerMove = MOVE_CELEBRATE; }
    PARAMETRIZE { playerMove = MOVE_TACKLE; }
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_PREDICT_MOVE | AI_FLAG_MOVE_OMNISCIENCE);
        PLAYER(SPECIES_WOBBUFFET) { HP(1000); MaxHP(1000); Speed(1); Moves(MOVE_CELEBRATE, MOVE_TACKLE); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); Moves(MOVE_SUCKER_PUNCH); }
    } WHEN {
        TURN { MOVE(player, playerMove); SCORE_EQ_VAL(opponent, MOVE_SUCKER_PUNCH, AI_SCORE_DEFAULT); }
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: known status-only targets disincentivize the first Sucker Punch")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_MOVE_OMNISCIENCE);
        PLAYER(SPECIES_WOBBUFFET) { Speed(10); Moves(MOVE_CELEBRATE); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); Moves(MOVE_SUCKER_PUNCH); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); SCORE_LT_VAL(opponent, MOVE_SUCKER_PUNCH, AI_SCORE_DEFAULT); }
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: incomplete status-only knowledge does not prove Sucker Punch cannot trigger")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE);
        PLAYER(SPECIES_WOBBUFFET) { Speed(10); Moves(MOVE_CELEBRATE, MOVE_TACKLE); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); Moves(MOVE_TACKLE, MOVE_SUCKER_PUNCH); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); EXPECT_MOVE(opponent, MOVE_TACKLE); }
        TURN { MOVE(player, MOVE_CELEBRATE); SCORE_EQ_VAL(opponent, MOVE_SUCKER_PUNCH, AI_SCORE_DEFAULT); }
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: a failed Sucker Punch attempt enables next-turn 50 percent caution")
{
    PASSES_RANDOMLY(50, 100, RNG_AI_SUCKER_PUNCH);
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE);
        PLAYER(SPECIES_WOBBUFFET) { Speed(10); Moves(MOVE_CELEBRATE, MOVE_TACKLE); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); Moves(MOVE_SUCKER_PUNCH); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); SCORE_EQ_VAL(opponent, MOVE_SUCKER_PUNCH, AI_SCORE_DEFAULT); }
        TURN { MOVE(player, MOVE_CELEBRATE); SCORE_LT_VAL(opponent, MOVE_SUCKER_PUNCH, AI_SCORE_DEFAULT); }
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Sucker Punch two or three turns ago needs recent status evidence")
{
    u32 age;
    bool32 status;
    PARAMETRIZE { age = 2; status = FALSE; }
    PARAMETRIZE { age = 2; status = TRUE; }
    PARAMETRIZE { age = 3; status = FALSE; }
    PARAMETRIZE { age = 3; status = TRUE; }
    if (status)
        PASSES_RANDOMLY(50, 100, RNG_AI_SUCKER_PUNCH);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(1000); MaxHP(1000); Speed(1); Moves(MOVE_TACKLE, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1000); MaxHP(1000); Speed(100); Moves(MOVE_SUCKER_PUNCH, MOVE_TACKLE); }
    } WHEN {
        TURN { MOVE(player, status ? MOVE_CELEBRATE : MOVE_TACKLE); MOVE(opponent, MOVE_SUCKER_PUNCH); }
        for (u32 i = 1; i < age; i++)
            TURN { MOVE(player, MOVE_TACKLE); MOVE(opponent, MOVE_TACKLE); }
    } THEN {
        memset(gAiThinkingStruct->aiFlags, 0, sizeof(gAiThinkingStruct->aiFlags));
        EXPECT_EQ(ShouldDisincentivizeSuckerPunch(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)), status);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: three subsequent moves age Sucker Punch out of move-use history")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(100); Moves(MOVE_CELEBRATE); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(1); Moves(MOVE_SUCKER_PUNCH, MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_SUCKER_PUNCH); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
    } THEN {
        memset(gAiThinkingStruct->aiFlags, 0, sizeof(gAiThinkingStruct->aiFlags));
        enum BattlerId atk = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        EXPECT_NE(FindMoveUsedXTurnsAgo(atk, 0), MOVE_SUCKER_PUNCH);
        EXPECT_NE(FindMoveUsedXTurnsAgo(atk, 1), MOVE_SUCKER_PUNCH);
        EXPECT_NE(FindMoveUsedXTurnsAgo(atk, 2), MOVE_SUCKER_PUNCH);
        EXPECT_EQ(ShouldDisincentivizeSuckerPunch(atk, GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)), FALSE);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: switching clears recent action history but preserves revealed moves")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(10); Moves(MOVE_CELEBRATE); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(10); Moves(MOVE_SUCKER_PUNCH); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(10); Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_SUCKER_PUNCH); }
        TURN { MOVE(player, MOVE_CELEBRATE); SWITCH(opponent, 1); }
        TURN { MOVE(player, MOVE_CELEBRATE); SWITCH(opponent, 0); }
    } THEN {
        memset(gAiThinkingStruct->aiFlags, 0, sizeof(gAiThinkingStruct->aiFlags));
        enum BattlerId atk = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        EXPECT_NE(FindMoveUsedXTurnsAgo(atk, 0), MOVE_SUCKER_PUNCH);
        EXPECT_NE(FindMoveUsedXTurnsAgo(atk, 1), MOVE_SUCKER_PUNCH);
        EXPECT_NE(FindMoveUsedXTurnsAgo(atk, 2), MOVE_SUCKER_PUNCH);
        EXPECT_EQ(gAiPartyData->mons[B_TRAINER_OPPONENT_A][0].moves[0], MOVE_SUCKER_PUNCH);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: an older Sucker Punch attempt warrants caution against a fresh switch-in")
{
    PASSES_RANDOMLY(50, 100, RNG_AI_SUCKER_PUNCH);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(1000); MaxHP(1000); Speed(1); Moves(MOVE_TACKLE); }
        PLAYER(SPECIES_WOBBUFFET) { HP(1000); MaxHP(1000); Speed(1); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1000); MaxHP(1000); Speed(100); Moves(MOVE_SUCKER_PUNCH, MOVE_TACKLE); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); MOVE(opponent, MOVE_SUCKER_PUNCH); }
        TURN { MOVE(player, MOVE_TACKLE); MOVE(opponent, MOVE_TACKLE); }
        TURN { SWITCH(player, 1); MOVE(opponent, MOVE_TACKLE); }
    } THEN {
        memset(gAiThinkingStruct->aiFlags, 0, sizeof(gAiThinkingStruct->aiFlags));
        EXPECT_EQ(ShouldDisincentivizeSuckerPunch(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), GetBattlerAtPosition(B_POSITION_PLAYER_LEFT)), TRUE);
    }
}
