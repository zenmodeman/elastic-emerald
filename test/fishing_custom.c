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
