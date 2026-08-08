#include "global.h"
#include "event_data.h"
#include "party_menu.h"
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

static u8 CreateAbilityChangeFixture(void)
{
    u8 drizzleSlot = FindAbilitySlot(SPECIES_POLITOED, ABILITY_DRIZZLE);

    ZeroPlayerPartyMons();
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_POLITOED, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gParties[B_TRAINER_PLAYER][1], SPECIES_CHANSEY, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gParties[B_TRAINER_PLAYER][2], SPECIES_CHANSEY, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gParties[B_TRAINER_PLAYER][3], SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID);
    gPartiesCount[B_TRAINER_PLAYER] = 4;
    return drizzleSlot;
}

TEST("Zenmodeman: Tier Point ability changes reject a proposed ability above the party cap")
{
    u8 drizzleSlot = CreateAbilityChangeFixture();

    FlagSet(FLAG_TIERED);
    EXPECT_EQ(CountPartyTierPoints(), 18);
    EXPECT_EQ(CalcTierPointsAfterAbilityChange(0, drizzleSlot), 21);
    EXPECT(!IsTierPointAbilityChangeAllowed(0, drizzleSlot));
}

TEST("Zenmodeman: Tier Point ability change guard is inactive outside Tiered Mode")
{
    u8 drizzleSlot = CreateAbilityChangeFixture();

    EXPECT(IsTierPointAbilityChangeAllowed(0, drizzleSlot));
}
