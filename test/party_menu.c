#include "global.h"
#include "battle.h"
#include "party_menu.h"
#include "pokemon.h"
#include "event_data.h"
#include "fieldmap.h"
#include "move_relearner.h"
#include "pokemon_summary_screen.h"
#include "constants/layouts.h"
#include "constants/region_map_sections.h"
#include "test/test.h"

#define TEST_MENU_DIR_DOWN     1
#define TEST_MENU_DIR_UP      -1
#define TEST_MENU_DIR_RIGHT    2

static void SetTestPartySize(enum BattleTrainer trainer, u8 partySize)
{
    for (u32 i = 0; i < PARTY_SIZE; i++)
        ZeroMonData(&gParties[trainer][i]);

    for (u32 i = 0; i < partySize; i++)
        CreateMon(&gParties[trainer][i], SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PRESET(0));

    gPartiesCount[trainer] = partySize;
}

TEST("Full multi partner party menu stops down navigation at partner party count")
{
    SetTestPartySize(B_TRAINER_PLAYER, PARTY_SIZE);
    SetTestPartySize(B_TRAINER_PARTNER, 2);
    gPartyMenu.layout = PARTY_LAYOUT_MULTI_FULL_PARTNER;

    EXPECT_EQ(Test_UpdatePartySelectionSingleLayout(1, TEST_MENU_DIR_DOWN, FALSE, 0), PARTY_SIZE + 1);
}

TEST("Full multi partner party menu allows down navigation through partner party count")
{
    SetTestPartySize(B_TRAINER_PLAYER, 2);
    SetTestPartySize(B_TRAINER_PARTNER, PARTY_SIZE);
    gPartyMenu.layout = PARTY_LAYOUT_MULTI_FULL_PARTNER;

    EXPECT_EQ(Test_UpdatePartySelectionSingleLayout(1, TEST_MENU_DIR_DOWN, FALSE, 0), 2);
}

TEST("Full multi partner party menu wraps cancel up to partner party count")
{
    SetTestPartySize(B_TRAINER_PLAYER, PARTY_SIZE);
    SetTestPartySize(B_TRAINER_PARTNER, 2);
    gPartyMenu.layout = PARTY_LAYOUT_MULTI_FULL_PARTNER;

    EXPECT_EQ(Test_UpdatePartySelectionSingleLayout(PARTY_SIZE + 1, TEST_MENU_DIR_UP, FALSE, 0), 1);
}

static void SetRelearnerTestParty(u16 species)
{
    SetTestPartySize(B_TRAINER_PLAYER, 2);
    CreateMon(&gParties[B_TRAINER_PLAYER][0], species, 50, 0, OTID_STRUCT_PRESET(0));
    // Make a level-up move available independently of the initial moveset.
    for (u32 i = 0; i < MAX_MON_MOVES; i++)
        SetMonMoveSlot(&gParties[B_TRAINER_PLAYER][0], MOVE_NONE, i);
    gPartyMenu.menuType = PARTY_MENU_TYPE_FIELD;
    gMapHeader.mapLayoutId = LAYOUT_LITTLEROOT_TOWN;
    gMapHeader.regionMapSectionId = MAPSEC_NONE;
    FlagClear(FLAG_RESOURCE_MODE);
    FlagClear(FLAG_BADGE04_GET);
    VarSet(VAR_REMAINING_RELEARNER, 0);
}

TEST("Elastic-tests: Party relearner appears for an eligible field Pokemon")
{
    SetRelearnerTestParty(SPECIES_WOBBUFFET);
    EXPECT(CanBoxMonRelearnAnyMove(&gParties[B_TRAINER_PLAYER][0].box));
    struct TestPartyMenuActions actions = Test_GetPartyMenuActions(0);
    EXPECT(actions.hasRelearner);
    EXPECT(actions.hasSummary);
    EXPECT(actions.cancelIsLast);
}

TEST("Elastic-tests: Party relearner excludes eggs and empty slots")
{
    SetRelearnerTestParty(SPECIES_WOBBUFFET);
    u8 isEgg = TRUE;
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_IS_EGG, &isEgg);
    EXPECT(!Test_GetPartyMenuActions(0).hasRelearner);
    ZeroMonData(&gParties[B_TRAINER_PLAYER][0]);
    EXPECT(!Test_GetPartyMenuActions(0).hasRelearner);
}

TEST("Elastic-tests: Party relearner is absent when no move remains to learn")
{
    SetRelearnerTestParty(SPECIES_DITTO);
    SetMonMoveSlot(&gParties[B_TRAINER_PLAYER][0], MOVE_TRANSFORM, 0);
    EXPECT(!CanBoxMonRelearnAnyMove(&gParties[B_TRAINER_PLAYER][0].box));
    EXPECT(!Test_GetPartyMenuActions(0).hasRelearner);
}

TEST("Elastic-tests: Party relearner is unavailable outside the field menu")
{
    SetRelearnerTestParty(SPECIES_WOBBUFFET);
    gPartyMenu.menuType = PARTY_MENU_TYPE_IN_BATTLE;
    EXPECT(!Test_GetPartyMenuActions(0).hasRelearner);
    gPartyMenu.menuType = PARTY_MENU_TYPE_CHOOSE_HALF;
    EXPECT(!Test_GetPartyMenuActions(0).hasRelearner);
}

TEST("Elastic-tests: Party relearner respects rental and Pike facility restrictions")
{
    SetRelearnerTestParty(SPECIES_WOBBUFFET);
    gMapHeader.mapLayoutId = LAYOUT_BATTLE_FRONTIER_BATTLE_PIKE_ROOM_NORMAL;
    EXPECT(!Test_GetPartyMenuActions(0).hasRelearner);
    gMapHeader.mapLayoutId = LAYOUT_BATTLE_FRONTIER_BATTLE_FACTORY_BATTLE_ROOM;
    EXPECT(!Test_GetPartyMenuActions(0).hasRelearner);
    gMapHeader.mapLayoutId = LAYOUT_BATTLE_TENT_BATTLE_ROOM;
    gMapHeader.regionMapSectionId = MAPSEC_SLATEPORT_CITY;
    EXPECT(!Test_GetPartyMenuActions(0).hasRelearner);
}

TEST("Elastic-tests: Party relearner requires points when the Pokemon is not eligible for free service")
{
    SetRelearnerTestParty(SPECIES_BEEDRILL);
    FlagSet(FLAG_RESOURCE_MODE);
    EXPECT(!Test_GetPartyMenuActions(0).hasRelearner);
    VarSet(VAR_REMAINING_RELEARNER, 1);
    EXPECT(Test_GetPartyMenuActions(0).hasRelearner);
    EXPECT_EQ(VarGet(VAR_REMAINING_RELEARNER), 1);
}

TEST("Elastic-tests: Party relearner allows free service after the evolution chain meets the tier limit")
{
    SetRelearnerTestParty(SPECIES_CATERPIE);
    FlagSet(FLAG_RESOURCE_MODE);
    EXPECT(!Test_GetPartyMenuActions(0).hasRelearner);
    FlagSet(FLAG_BADGE04_GET);
    EXPECT(Test_GetPartyMenuActions(0).hasRelearner);
    EXPECT_EQ(VarGet(VAR_REMAINING_RELEARNER), 0);
}

TEST("Elastic-tests: Party relearner opens level moves directly for the selected Pokemon")
{
    SetRelearnerTestParty(SPECIES_WOBBUFFET);
    struct TestPartyMenuActions actions = Test_GetPartyMenuActions(0);
    EXPECT(actions.opensRelearnerDirectly);
    EXPECT_EQ(actions.count, 5);
    // A previous summary-screen visit must not select another move-learning category.
    gMoveRelearnerState = MOVE_RELEARNER_TM_MOVES;
    gRelearnMode = RELEARN_MODE_PSS_PAGE_BATTLE_MOVES;
    EXPECT(Test_PreparePartyMoveRelearner(1));
    EXPECT_EQ(gMoveRelearnerState, MOVE_RELEARNER_LEVEL_UP_MOVES);
    EXPECT_EQ(gRelearnMode, RELEARN_MODE_PARTY_MENU);
    EXPECT_EQ(gLastViewedMonIndex, 1);
    EXPECT_EQ(gSpecialVar_0x8004, 1);
}

TEST("Elastic-tests: Party relearner fits alongside four field moves without losing standard actions")
{
    SetRelearnerTestParty(SPECIES_WOBBUFFET);
    const u16 moves[MAX_MON_MOVES] = {MOVE_SURF, MOVE_FLY, MOVE_FLASH, MOVE_STRENGTH};
    for (u32 i = 0; i < MAX_MON_MOVES; i++)
        SetMonMoveSlot(&gParties[B_TRAINER_PLAYER][0], moves[i], i);
    struct TestPartyMenuActions actions = Test_GetPartyMenuActions(0);
    EXPECT_EQ(actions.count, 9);
    EXPECT_EQ(actions.fieldMoveCount, 4);
    EXPECT(actions.hasRelearner);
    EXPECT(actions.hasSummary);
    EXPECT(actions.hasSwitch);
    EXPECT(actions.hasItem);
    EXPECT(actions.cancelIsLast);
}
