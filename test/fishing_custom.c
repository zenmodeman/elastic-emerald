#include "global.h"
#include "event_data.h"
#include "fishing.h"
#include "pokemon.h"
#include "test/test.h"

static u8 FindAbilitySlot(enum Species species, enum Ability ability)
{
    u8 slot;

    for (slot = 0; slot < NUM_ABILITY_SLOTS; slot++)
    {
        if (GetSpeciesAbility(species, slot) == ability)
            return slot;
    }
    return NUM_ABILITY_SLOTS;
}

TEST("Zenmodeman: Fishing retains its shortened rounds and extended reel windows")
{
    EXPECT_EQ(GetFishingMinRoundsRange(OLD_ROD), 1);
    EXPECT_EQ(GetFishingMinRoundsRange(GOOD_ROD), 2);
    EXPECT_EQ(GetFishingMinRoundsRange(SUPER_ROD), 3);
    EXPECT_EQ(GetFishingReelTimeout(OLD_ROD), 45);
    EXPECT_EQ(GetFishingReelTimeout(GOOD_ROD), 42);
    EXPECT_EQ(GetFishingReelTimeout(SUPER_ROD), 39);
    EXPECT_EQ(GetFishingMoreDotsChance(GOOD_ROD, 0), 15);
    EXPECT_EQ(GetFishingMoreDotsChance(GOOD_ROD, 1), 3);
    EXPECT_EQ(GetFishingMoreDotsChance(SUPER_ROD, 0), 30);
    EXPECT_EQ(GetFishingMoreDotsChance(SUPER_ROD, 1), 15);
}

TEST("Zenmodeman: Fishing early-input grace requires a later round near completion and a roll below forty")
{
    EXPECT(ShouldForgiveFishingEarlyPress(1, 4, 6, 39));
    EXPECT(!ShouldForgiveFishingEarlyPress(0, 4, 6, 39));
    EXPECT(!ShouldForgiveFishingEarlyPress(1, 3, 6, 39));
    EXPECT(!ShouldForgiveFishingEarlyPress(1, 4, 6, 40));
}

static void SetFishingLead(enum Species species, enum Ability ability)
{
    u8 abilitySlot = FindAbilitySlot(species, ability);

    ZeroPlayerPartyMons();
    CreateMon(&gParties[B_TRAINER_PLAYER][0], species, 20, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_ABILITY_NUM, &abilitySlot);
}

TEST("Zenmodeman: Suction Cups fishing rewards require Suction Cups on the lead")
{
    SetFishingLead(SPECIES_INKAY, ABILITY_SUCTION_CUPS);
    EXPECT(CanPlayerGetSuctionCupsFishingItem());

    SetFishingLead(SPECIES_INKAY, ABILITY_CONTRARY);
    EXPECT(!CanPlayerGetSuctionCupsFishingItem());
}

TEST("Zenmodeman: Suction Cups fishing rewards reject an Egg lead")
{
    u8 isEgg = TRUE;

    SetFishingLead(SPECIES_INKAY, ABILITY_SUCTION_CUPS);
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_IS_EGG, &isEgg);
    EXPECT(!CanPlayerGetSuctionCupsFishingItem());
}

TEST("Zenmodeman: Suction Cups fishing third guaranteed reward waits for badge two")
{
    SetFishingLead(SPECIES_INKAY, ABILITY_SUCTION_CUPS);
    VarSet(VAR_SUCTION_CUPS, 2);
    EXPECT(!CanPlayerGetSuctionCupsFishingItem());

    FlagSet(FLAG_BADGE02_GET);
    EXPECT(CanPlayerGetSuctionCupsFishingItem());
}

TEST("Zenmodeman: Suction Cups fishing repeat rewards are disabled in Resource Mode")
{
    SetFishingLead(SPECIES_INKAY, ABILITY_SUCTION_CUPS);
    VarSet(VAR_SUCTION_CUPS, 3);
    FlagSet(FLAG_RESOURCE_MODE);
    EXPECT(!CanPlayerGetSuctionCupsFishingItem());
}
