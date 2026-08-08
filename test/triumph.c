#include "global.h"
#include "battle.h"
#include "battle_main.h"
#include "battle_setup.h"
#include "battle_util.h"
#include "event_data.h"
#include "test/test.h"

static void SetUpTriumphBattle(u8 playerLevel, u8 opponentLevel)
{
    memset(gBattleMons, 0, sizeof(gBattleMons));
    memset(gBattlerPartyIndexes, 0, sizeof(gBattlerPartyIndexes));
    gBattleTypeFlags = BATTLE_TYPE_TRAINER;
    gBattlersCount = 2;
    gAbsentBattlerFlags = 0;
    gBattleTriumphPartyMask = 0;
    gBattlerPositions[0] = B_POSITION_PLAYER_LEFT;
    gBattlerPositions[1] = B_POSITION_OPPONENT_LEFT;
    gBattlerPositions[2] = B_POSITION_PLAYER_RIGHT;
    gBattlerPositions[3] = B_POSITION_OPPONENT_RIGHT;
    gBattleMons[0].species = SPECIES_WOBBUFFET;
    gBattleMons[0].level = playerLevel;
    gBattleMons[1].species = SPECIES_ZIGZAGOON;
    gBattleMons[1].level = opponentLevel;
}

static void SetUpTriumphAward(u32 triumph)
{
    ZeroPlayerPartyMons();
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_WOBBUFFET, 20, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_TRIUMPH, &triumph);
    gBattleTypeFlags = BATTLE_TYPE_TRAINER;
    gBattleTriumphPartyMask = 1;
    TRAINER_BATTLE_PARAM.opponentA = TRAINER_CALVIN_1;
    TRAINER_BATTLE_PARAM.opponentB = TRAINER_NONE;
}

TEST("Zenmodeman: Triumph marks a sole eligible battler present for a trainer KO")
{
    SetUpTriumphBattle(20, 15);

    TryMarkBattleTriumph(1, FALSE);

    EXPECT_EQ(gBattleTriumphPartyMask, 1);
}

TEST("Zenmodeman: Triumph rejects opponents more than five levels lower")
{
    SetUpTriumphBattle(21, 15);

    TryMarkBattleTriumph(1, TRUE);

    EXPECT_EQ(gBattleTriumphPartyMask, 0);
}

TEST("Zenmodeman: Triumph doubles credit requires and follows the direct attacker")
{
    SetUpTriumphBattle(20, 20);
    gBattlersCount = 4;
    gBattleTypeFlags |= BATTLE_TYPE_DOUBLE;
    gBattleMons[2].species = SPECIES_WOBBUFFET;
    gBattleMons[2].level = 20;
    gBattlerPartyIndexes[2] = 1;

    TryMarkBattleTriumph(1, FALSE);
    EXPECT_EQ(gBattleTriumphPartyMask, 0);

    gBattlerAttacker = 2;
    TryMarkBattleTriumph(1, TRUE);
    EXPECT_EQ(gBattleTriumphPartyMask, 1 << 1);
}

TEST("Zenmodeman: Triumph awards marked Pokemon after a first trainer victory")
{
    SetUpTriumphAward(0);

    AwardBattleTriumphs();

    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_TRIUMPH), 1);
    EXPECT_EQ(gBattleTriumphPartyMask, 0);
}

TEST("Zenmodeman: Triumph cannot be farmed from defeated trainers")
{
    SetUpTriumphAward(4);
    FlagSet(TRAINER_FLAGS_START + TRAINER_CALVIN_1);

    AwardBattleTriumphs();

    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_TRIUMPH), 4);
    EXPECT_EQ(gBattleTriumphPartyMask, 0);
}

TEST("Zenmodeman: Triumph excludes facilities and caps ordinary counts at thirty")
{
    SetUpTriumphAward(MAX_TRIUMPH_COUNT);
    AwardBattleTriumphs();
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_TRIUMPH), MAX_TRIUMPH_COUNT);

    SetUpTriumphAward(9);
    gBattleTypeFlags |= BATTLE_TYPE_FRONTIER;
    AwardBattleTriumphs();
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_TRIUMPH), 9);
}
