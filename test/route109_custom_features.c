#include "global.h"
#include "battle.h"
#include "battle_main.h"
#include "battle_pyramid.h"
#include "battle_setup.h"
#include "caps.h"
#include "constants/layouts.h"
#include "difficulty.h"
#include "data.h"
#include "event_data.h"
#include "region_map.h"
#include "test/test.h"
#include "trainer_hill.h"

void WasTrainerBattleWithTwoOpponents(void);
void RerollSleepTurnsAfterBattle(void);

#define TEST_BRINEY_LOCATION_DEWFORD 2

static void SetCurrentMap(u16 mapGroup, u16 mapNum)
{
    gSaveBlock1Ptr->location.mapGroup = mapGroup;
    gSaveBlock1Ptr->location.mapNum = mapNum;
}

static void CreateDamagedStatusedPlayerMon(void)
{
    u32 hp = 1;
    u32 status = STATUS1_BURN;

    ZeroPlayerPartyMons();
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HP, &hp);
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_STATUS, &status);
    gPartiesCount[B_TRAINER_PLAYER] = 1;
    SetCurrentDifficultyLevel(DIFFICULTY_NORMAL);
    gMapHeader.mapLayoutId = LAYOUT_LITTLEROOT_TOWN;
    VarSet(VAR_TRAINER_HILL_IS_ACTIVE, 0);
    TRAINER_BATTLE_PARAM.opponentB = TRAINER_NONE;
}

TEST("Zenmodeman: Route 109: Cassia is a route boss without classifying ordinary beach trainers")
{
    EXPECT(IsRouteBossTrainer(TRAINER_CASSIA));
    EXPECT(!IsRouteBossTrainer(TRAINER_EDMOND));
    EXPECT(!IsRouteBossTrainer(TRAINER_RICKY_1));
}

TEST("Zenmodeman: Route 109: rival progression raises every beach trainer by three levels")
{
    static const u16 trainers[] = {
        TRAINER_LOLA_1, TRAINER_RICKY_1, TRAINER_CASSIA, TRAINER_SIMON,
        TRAINER_HUEY, TRAINER_EDMOND, TRAINER_DWAYNE, TRAINER_JOHANNA,
        TRAINER_HAILEY, TRAINER_CHANDLER,
    };
    u32 i;

    for (i = 0; i < ARRAY_COUNT(trainers); i++)
        EXPECT_EQ(GetTrainerLevelModifier(trainers[i]), 0);

    FlagSet(FLAG_RIVAL_110_DEFEATED);
    for (i = 0; i < ARRAY_COUNT(trainers); i++)
        EXPECT_EQ(GetTrainerLevelModifier(trainers[i]), 3);
}

TEST("Zenmodeman: Route 109: unrelated trainers do not inherit beach level scaling")
{
    FlagSet(FLAG_RIVAL_110_DEFEATED);
    EXPECT_EQ(GetTrainerLevelModifier(TRAINER_ROXANNE_1), 0);
}

TEST("Zenmodeman: Route 109: Cindy badge scaling is cumulative")
{
    EXPECT_EQ(GetTrainerLevelModifier(TRAINER_CINDY_1), 0);
    FlagSet(FLAG_BADGE01_GET);
    EXPECT_EQ(GetTrainerLevelModifier(TRAINER_CINDY_1), 3);
    FlagSet(FLAG_BADGE02_GET);
    EXPECT_EQ(GetTrainerLevelModifier(TRAINER_CINDY_1), 7);
}

TEST("Zenmodeman: Route 109: Darren progression scales the connected trainer group")
{
    FlagSet(TRAINER_FLAGS_START + TRAINER_DARREN);
    EXPECT_EQ(GetTrainerLevelModifier(TRAINER_LYLE), 2);
    EXPECT_EQ(GetTrainerLevelModifier(TRAINER_JAMES_1), 2);
    EXPECT_EQ(GetTrainerLevelModifier(TRAINER_AURELIO), 2);
}

TEST("Zenmodeman: Route 109: rival and Champion milestones use the revised level caps")
{
    FlagSet(FLAG_LEVEL_CAP);
    FlagSet(TRAINER_FLAGS_START + TRAINER_TIANA);
    FlagSet(TRAINER_FLAGS_START + TRAINER_GRUNT_PETALBURG_WOODS);
    FlagSet(TRAINER_FLAGS_START + TRAINER_DARREN);
    FlagSet(FLAG_BADGE01_GET);
    FlagSet(FLAG_BADGE02_GET);
    EXPECT_EQ(GetCurrentLevelCap(TRUE), 23);
    FlagSet(FLAG_RIVAL_110_DEFEATED);
    EXPECT_EQ(GetCurrentLevelCap(TRUE), 26);
    FlagSet(FLAG_BADGE03_GET);
    FlagSet(FLAG_BADGE04_GET);
    FlagSet(FLAG_BADGE05_GET);
    FlagSet(FLAG_BADGE06_GET);
    FlagSet(FLAG_BADGE07_GET);
    FlagSet(FLAG_BADGE08_GET);
    EXPECT_EQ(GetCurrentLevelCap(TRUE), 70);
}

TEST("Zenmodeman: Route 109: Edmond reward detection distinguishes two-opponent battles")
{
    Test_SetTrainerBattleHadTwoOpponents(FALSE);
    gBattleTypeFlags = 0;
    TRAINER_BATTLE_PARAM.opponentB = TRAINER_NONE;
    WasTrainerBattleWithTwoOpponents();
    EXPECT_EQ(gSpecialVar_Result, FALSE);

    // The recorded launch state must survive both transient battle flags and
    // trainer parameters being cleared before the field callback runs.
    Test_SetTrainerBattleHadTwoOpponents(TRUE);
    gBattleTypeFlags = 0;
    TRAINER_BATTLE_PARAM.opponentB = TRAINER_NONE;
    WasTrainerBattleWithTwoOpponents();
    EXPECT_EQ(gSpecialVar_Result, TRUE);

    // Consuming the result prevents repeat rewards on later conversations.
    TRAINER_BATTLE_PARAM.opponentB = TRAINER_HAILEY;
    WasTrainerBattleWithTwoOpponents();
    EXPECT_EQ(gSpecialVar_Result, FALSE);
}

TEST("Zenmodeman: Route 109 Fly failsafe returns stranded Briney to Dewford")
{
    struct RegionMap regionMap = { .mapSecId = MAPSEC_LITTLEROOT_TOWN };

    SetCurrentMap(MAP_GROUP(MAP_ROUTE109), MAP_NUM(MAP_ROUTE109));
    FlagSet(FLAG_HIDE_ROUTE_104_MR_BRINEY);
    FlagSet(FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT);
    FlagSet(FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN);
    FlagSet(FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN);

    SetFlyDestination(&regionMap);

    EXPECT(FlagGet(FLAG_HIDE_ROUTE_109_MR_BRINEY));
    EXPECT(FlagGet(FLAG_HIDE_ROUTE_109_MR_BRINEY_BOAT));
    EXPECT(!FlagGet(FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN));
    EXPECT(!FlagGet(FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN));
    EXPECT_EQ(VarGet(VAR_BRINEY_LOCATION), TEST_BRINEY_LOCATION_DEWFORD);
}

TEST("Zenmodeman: Route 109 Fly failsafe does not move Briney after Slateport")
{
    struct RegionMap regionMap = { .mapSecId = MAPSEC_LITTLEROOT_TOWN };

    SetCurrentMap(MAP_GROUP(MAP_ROUTE109), MAP_NUM(MAP_ROUTE109));
    FlagSet(FLAG_VISITED_SLATEPORT_CITY);
    FlagSet(FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN);

    SetFlyDestination(&regionMap);

    EXPECT(!FlagGet(FLAG_HIDE_ROUTE_109_MR_BRINEY));
    EXPECT(FlagGet(FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN));
}

TEST("Zenmodeman: Route 109 Fly failsafe ignores flights from other maps")
{
    struct RegionMap regionMap = { .mapSecId = MAPSEC_LITTLEROOT_TOWN };

    SetCurrentMap(MAP_GROUP(MAP_ROUTE104), MAP_NUM(MAP_ROUTE104));
    FlagSet(FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN);

    SetFlyDestination(&regionMap);

    EXPECT(!FlagGet(FLAG_HIDE_ROUTE_109_MR_BRINEY));
    EXPECT(FlagGet(FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN));
}

TEST("Zenmodeman: Trainer healing: route bosses fully heal regardless of trainer class")
{
    CreateDamagedStatusedPlayerMon();
    TRAINER_BATTLE_PARAM.opponentA = TRAINER_CASSIA;

    EXPECT_EQ(TryHealPlayerPartyBeforeTrainerBattle(), TRAINER_PRE_BATTLE_HEAL_FULL);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HP), GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_MAX_HP));
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_STATUS), STATUS1_NONE);
}

TEST("Zenmodeman: Trainer healing: professional trainer classes fully heal")
{
    CreateDamagedStatusedPlayerMon();
    TRAINER_BATTLE_PARAM.opponentA = TRAINER_ROXANNE_1;

    EXPECT_EQ(CurrentBattlePyramidLocation(), PYRAMID_LOCATION_NONE);
    EXPECT(!InTrainerHillChallenge());
    EXPECT_EQ(GetTrainerClassFromId(TRAINER_ROXANNE_1), TRAINER_CLASS_LEADER);
    EXPECT_EQ(TryHealPlayerPartyBeforeTrainerBattle(), TRAINER_PRE_BATTLE_HEAL_FULL);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HP), GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_MAX_HP));
}

TEST("Zenmodeman: Trainer healing: status-healing classes preserve HP")
{
    CreateDamagedStatusedPlayerMon();
    TRAINER_BATTLE_PARAM.opponentA = TRAINER_PATRICIA;

    EXPECT_EQ(TryHealPlayerPartyBeforeTrainerBattle(), TRAINER_PRE_BATTLE_HEAL_OLD_GATEAU);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HP), 1);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_STATUS), STATUS1_NONE);
}

TEST("Zenmodeman: Trainer healing: ordinary trainer classes do not heal")
{
    CreateDamagedStatusedPlayerMon();
    TRAINER_BATTLE_PARAM.opponentA = TRAINER_CALVIN_1;

    EXPECT_EQ(TryHealPlayerPartyBeforeTrainerBattle(), TRAINER_PRE_BATTLE_HEAL_NONE);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HP), 1);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_STATUS), STATUS1_BURN);
}

TEST("Zenmodeman: Trainer healing: a full-healing second opponent takes precedence")
{
    CreateDamagedStatusedPlayerMon();
    TRAINER_BATTLE_PARAM.opponentA = TRAINER_CALVIN_1;
    TRAINER_BATTLE_PARAM.opponentB = TRAINER_ROXANNE_1;

    EXPECT_EQ(TryHealPlayerPartyBeforeTrainerBattle(), TRAINER_PRE_BATTLE_HEAL_FULL);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_STATUS), STATUS1_NONE);
}

TEST("Zenmodeman: Trainer healing: post-battle sleep rerolls without changing other statuses")
{
    u32 sleep = STATUS1_SLEEP_TURN(1);
    u32 poison = STATUS1_POISON;
    u32 rerolled;

    ZeroPlayerPartyMons();
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gParties[B_TRAINER_PLAYER][1], SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_STATUS, &sleep);
    SetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_STATUS, &poison);
    gPartiesCount[B_TRAINER_PLAYER] = 2;

    RerollSleepTurnsAfterBattle();
    rerolled = GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_STATUS);
    EXPECT(rerolled == STATUS1_SLEEP_TURN(2)
        || rerolled == STATUS1_SLEEP_TURN(3)
        || rerolled == STATUS1_SLEEP_TURN(4));
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_STATUS), STATUS1_POISON);
}
