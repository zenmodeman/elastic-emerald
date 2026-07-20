#include "global.h"
#include "battle_setup.h"
#include "event_data.h"
#include "item.h"
#include "pokemon.h"
#include "test/test.h"

void PopulateMonotypeResistBerriesInPC(void);

static u8 FindAbilitySlot(u16 species, u16 ability)
{
    u8 slot;

    for (slot = 0; slot < NUM_ABILITY_SLOTS; slot++)
    {
        if (GetSpeciesAbility(species, slot) == ability)
            return slot;
    }

    return NUM_ABILITY_SLOTS;
}

TEST("Zenmodeman: Merge guard: Monotype save values decode across the Fairy type gap")
{
    VarSet(VAR_MONOTYPE, TYPE_FIRE - 1);
    EXPECT_EQ(GetMonoType(), TYPE_FIRE);

    VarSet(VAR_MONOTYPE, TYPE_FAIRY - 1);
    EXPECT_EQ(GetMonoType(), TYPE_FAIRY);

    VarSet(VAR_MONOTYPE, 0);
    EXPECT_EQ(GetMonoType(), TYPE_NONE);
}

TEST("Zenmodeman: Merge guard: Monotype startup seeds only super-effective resist berries")
{
    VarSet(VAR_MONOTYPE, TYPE_FIRE - 1);
    PopulateMonotypeResistBerriesInPC();

    EXPECT(CheckPCHasItem(ITEM_PASSHO_BERRY, 12));
    EXPECT(CheckPCHasItem(ITEM_SHUCA_BERRY, 12));
    EXPECT(CheckPCHasItem(ITEM_CHARTI_BERRY, 12));
    EXPECT(!CheckPCHasItem(ITEM_OCCA_BERRY, 1));
}

TEST("Zenmodeman: Merge guard: Tier Points treat eggs as zero points")
{
    struct Pokemon mon;
    u8 isEgg = TRUE;

    CreateMon(&mon, SPECIES_CHANSEY, 5, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetMonTierPoints(&mon), 6);
    SetMonData(&mon, MON_DATA_IS_EGG, &isEgg);
    EXPECT_EQ(GetMonTierPoints(&mon), 0);
}

TEST("Zenmodeman: Merge guard: Tier Points account for a weather-setting ability")
{
    struct Pokemon mon;
    u8 abilitySlot = FindAbilitySlot(SPECIES_POLITOED, ABILITY_DRIZZLE);

    EXPECT_NE(abilitySlot, NUM_ABILITY_SLOTS);
    CreateMon(&mon, SPECIES_POLITOED, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_ABILITY_NUM, &abilitySlot);
    EXPECT_EQ(GetMonTierPoints(&mon), 6);
}

TEST("Zenmodeman: Merge guard: Tier Points account for badge progression")
{
    struct Pokemon mon;
    u8 abilitySlot = FindAbilitySlot(SPECIES_VULPIX, ABILITY_FLASH_FIRE);

    EXPECT_NE(abilitySlot, NUM_ABILITY_SLOTS);
    CreateMon(&mon, SPECIES_VULPIX, 20, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_ABILITY_NUM, &abilitySlot);
    EXPECT_EQ(GetMonTierPoints(&mon), 3);

    FlagSet(FLAG_BADGE04_GET);
    EXPECT_EQ(GetMonTierPoints(&mon), 1);
}

TEST("Zenmodeman: Merge guard: Tier Points preserve the default value for a null candidate")
{
    EXPECT_EQ(GetMonTierPoints(NULL), 3);
}

TEST("Zenmodeman: Merge guard: Party Tier Points exclude eggs and empty slots")
{
    u8 isEgg = TRUE;

    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_CHANSEY, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_DRAGAPULT, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[1], MON_DATA_IS_EGG, &isEgg);
    EXPECT_EQ(CountPartyTierPoints(), 6);
}

TEST("Zenmodeman: Merge guard: Evolution Tier Point projection does not mutate the party")
{
    u16 originalSpecies;

    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_HAPPINY, 30, 0, OTID_STRUCT_PLAYER_ID);
    gPlayerPartyCount = 1;
    originalSpecies = GetMonData(&gPlayerParty[0], MON_DATA_SPECIES);

    EXPECT_EQ(CalcTierPointsAfterEvolution(0, SPECIES_CHANSEY), 6);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_SPECIES), originalSpecies);
}

TEST("Zenmodeman: Merge guard: Ability Tier Point projection does not mutate the party")
{
    u8 originalAbility;
    u8 drizzleSlot = FindAbilitySlot(SPECIES_POLITOED, ABILITY_DRIZZLE);

    EXPECT_NE(drizzleSlot, NUM_ABILITY_SLOTS);
    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_POLITOED, 50, 0, OTID_STRUCT_PLAYER_ID);
    gPlayerPartyCount = 1;
    originalAbility = GetMonData(&gPlayerParty[0], MON_DATA_ABILITY_NUM);

    EXPECT_EQ(CalcTierPointsAfterAbilityChange(0, drizzleSlot), 6);
    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_ABILITY_NUM), originalAbility);
}

TEST("Zenmodeman: Merge guard: Restricted Mode item clause bags duplicate party items")
{
    u16 leftovers = ITEM_LEFTOVERS;

    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_WYNAUT, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM, &leftovers);
    SetMonData(&gPlayerParty[1], MON_DATA_HELD_ITEM, &leftovers);
    FlagSet(FLAG_RESTRICTED_MODE);

    BattleSetup_EnforceRestrictedModeItemClause();

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM), ITEM_LEFTOVERS);
    EXPECT_EQ(GetMonData(&gPlayerParty[1], MON_DATA_HELD_ITEM), ITEM_NONE);
    EXPECT(CheckBagHasItem(ITEM_LEFTOVERS, 1));
}

TEST("Zenmodeman: Merge guard: Invalid monotype save values decode as no monotype")
{
    VarSet(VAR_MONOTYPE, NUMBER_OF_MON_TYPES);
    EXPECT_EQ(GetMonoType(), TYPE_NONE);
    VarSet(VAR_MONOTYPE, 255);
    EXPECT_EQ(GetMonoType(), TYPE_NONE);
}

TEST("Zenmodeman: Merge guard: Item clause is inactive outside Restricted Mode")
{
    u16 item = ITEM_LEFTOVERS;

    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_WYNAUT, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM, &item);
    SetMonData(&gPlayerParty[1], MON_DATA_HELD_ITEM, &item);

    BattleSetup_EnforceRestrictedModeItemClause();

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM), ITEM_LEFTOVERS);
    EXPECT_EQ(GetMonData(&gPlayerParty[1], MON_DATA_HELD_ITEM), ITEM_LEFTOVERS);
}

TEST("Zenmodeman: Merge guard: Restricted Mode item clause preserves unique held items")
{
    u16 leftovers = ITEM_LEFTOVERS;
    u16 blackSludge = ITEM_BLACK_SLUDGE;

    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_WYNAUT, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM, &leftovers);
    SetMonData(&gPlayerParty[1], MON_DATA_HELD_ITEM, &blackSludge);
    FlagSet(FLAG_RESTRICTED_MODE);

    BattleSetup_EnforceRestrictedModeItemClause();

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM), ITEM_LEFTOVERS);
    EXPECT_EQ(GetMonData(&gPlayerParty[1], MON_DATA_HELD_ITEM), ITEM_BLACK_SLUDGE);
}

TEST("Zenmodeman: Merge guard: Item clause keeps the first of three duplicate items")
{
    u16 item = ITEM_LEFTOVERS;

    ZeroPlayerPartyMons();
    for (u32 i = 0; i < 3; i++)
    {
        CreateMon(&gPlayerParty[i], SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID);
        SetMonData(&gPlayerParty[i], MON_DATA_HELD_ITEM, &item);
    }
    FlagSet(FLAG_RESTRICTED_MODE);

    BattleSetup_EnforceRestrictedModeItemClause();

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM), ITEM_LEFTOVERS);
    EXPECT_EQ(GetMonData(&gPlayerParty[1], MON_DATA_HELD_ITEM), ITEM_NONE);
    EXPECT_EQ(GetMonData(&gPlayerParty[2], MON_DATA_HELD_ITEM), ITEM_NONE);
    EXPECT(CheckBagHasItem(ITEM_LEFTOVERS, 2));
}

TEST("Zenmodeman: Merge guard: Item clause ignores held items on eggs")
{
    u16 item = ITEM_LEFTOVERS;
    u8 isEgg = TRUE;

    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_WYNAUT, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM, &item);
    SetMonData(&gPlayerParty[1], MON_DATA_HELD_ITEM, &item);
    SetMonData(&gPlayerParty[1], MON_DATA_IS_EGG, &isEgg);
    FlagSet(FLAG_RESTRICTED_MODE);

    BattleSetup_EnforceRestrictedModeItemClause();

    EXPECT_EQ(GetMonData(&gPlayerParty[1], MON_DATA_HELD_ITEM), ITEM_LEFTOVERS);
}

TEST("Zenmodeman: Merge guard: Reapplying item clause does not bag items twice")
{
    u16 item = ITEM_LEFTOVERS;

    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_WYNAUT, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM, &item);
    SetMonData(&gPlayerParty[1], MON_DATA_HELD_ITEM, &item);
    FlagSet(FLAG_RESTRICTED_MODE);

    BattleSetup_EnforceRestrictedModeItemClause();
    BattleSetup_EnforceRestrictedModeItemClause();

    EXPECT(CheckBagHasItem(ITEM_LEFTOVERS, 1));
    EXPECT(!CheckBagHasItem(ITEM_LEFTOVERS, 2));
}

TEST("Zenmodeman: Merge guard: Party Tier Points equal the sum of member values")
{
    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_CHANSEY, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID);

    EXPECT_EQ(CountPartyTierPoints(), GetMonTierPoints(&gPlayerParty[0]) + GetMonTierPoints(&gPlayerParty[1]));
}

TEST("Zenmodeman: Merge guard: Evolution Tier Point projection includes the rest of the party")
{
    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_HAPPINY, 30, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_WOBBUFFET, 30, 0, OTID_STRUCT_PLAYER_ID);
    gPlayerPartyCount = 2;

    EXPECT_EQ(CalcTierPointsAfterEvolution(0, SPECIES_CHANSEY),
              6 + GetMonTierPoints(&gPlayerParty[1]));
}

TEST("Zenmodeman: Merge guard: Ability Tier Point projection includes the rest of the party")
{
    u8 drizzleSlot = FindAbilitySlot(SPECIES_POLITOED, ABILITY_DRIZZLE);

    EXPECT_NE(drizzleSlot, NUM_ABILITY_SLOTS);
    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_POLITOED, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID);
    gPlayerPartyCount = 2;

    EXPECT_EQ(CalcTierPointsAfterAbilityChange(0, drizzleSlot),
              6 + GetMonTierPoints(&gPlayerParty[1]));
}

TEST("Zenmodeman: Merge guard: Empty parties have zero projected Tier Points")
{
    ZeroPlayerPartyMons();
    gPlayerPartyCount = 0;

    EXPECT_EQ(CountPartyTierPoints(), 0);
    EXPECT_EQ(CalcTierPointsAfterEvolution(0, SPECIES_CHANSEY), 0);
    EXPECT_EQ(CalcTierPointsAfterAbilityChange(0, 0), 0);
}

TEST("Zenmodeman: Merge guard: Sawsbuck seasonal forms share Tier Points")
{
    struct Pokemon base;
    struct Pokemon form;

    CreateMon(&base, SPECIES_SAWSBUCK, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&form, SPECIES_SAWSBUCK_WINTER, 50, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetMonTierPoints(&base), GetMonTierPoints(&form));
}

TEST("Zenmodeman: Merge guard: Vivillon patterns share Tier Points")
{
    struct Pokemon base;
    struct Pokemon form;

    CreateMon(&base, SPECIES_VIVILLON, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&form, SPECIES_VIVILLON_POKEBALL, 50, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetMonTierPoints(&base), GetMonTierPoints(&form));
}

TEST("Zenmodeman: Merge guard: Silvally type forms share Tier Points")
{
    struct Pokemon base;
    struct Pokemon form;

    CreateMon(&base, SPECIES_SILVALLY, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&form, SPECIES_SILVALLY_FAIRY, 50, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetMonTierPoints(&base), GetMonTierPoints(&form));
}

TEST("Zenmodeman: Merge guard: Minior core forms share Tier Points")
{
    struct Pokemon base;
    struct Pokemon form;

    CreateMon(&base, SPECIES_MINIOR, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&form, SPECIES_MINIOR_CORE_VIOLET, 50, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetMonTierPoints(&base), GetMonTierPoints(&form));
}

TEST("Zenmodeman: Merge guard: Alcremie decorations share Tier Points")
{
    struct Pokemon base;
    struct Pokemon form;

    CreateMon(&base, SPECIES_ALCREMIE, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&form, SPECIES_ALCREMIE_STRAWBERRY_RAINBOW_SWIRL, 50, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetMonTierPoints(&base), GetMonTierPoints(&form));
}

TEST("Zenmodeman: Merge guard: No monotype does not seed resist berries")
{
    VarSet(VAR_MONOTYPE, 0);
    PopulateMonotypeResistBerriesInPC();

    EXPECT(!CheckPCHasItem(ITEM_OCCA_BERRY, 1));
    EXPECT(!CheckPCHasItem(ITEM_PASSHO_BERRY, 1));
    EXPECT(!CheckPCHasItem(ITEM_CHOPLE_BERRY, 1));
}

TEST("Zenmodeman: Merge guard: Evolution projection ignores egg teammates")
{
    u8 isEgg = TRUE;

    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_HAPPINY, 30, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_CHANSEY, 30, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[1], MON_DATA_IS_EGG, &isEgg);
    gPlayerPartyCount = 2;

    EXPECT_EQ(CalcTierPointsAfterEvolution(0, SPECIES_CHANSEY), 6);
}

TEST("Zenmodeman: Merge guard: Ability projection ignores egg teammates")
{
    u8 isEgg = TRUE;
    u8 drizzleSlot = FindAbilitySlot(SPECIES_POLITOED, ABILITY_DRIZZLE);

    EXPECT_NE(drizzleSlot, NUM_ABILITY_SLOTS);
    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_POLITOED, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_CHANSEY, 30, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[1], MON_DATA_IS_EGG, &isEgg);
    gPlayerPartyCount = 2;

    EXPECT_EQ(CalcTierPointsAfterAbilityChange(0, drizzleSlot), 6);
}

TEST("Zenmodeman: Merge guard: Item clause ignores empty party slots")
{
    u16 item = ITEM_LEFTOVERS;

    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM, &item);
    SetMonData(&gPlayerParty[1], MON_DATA_HELD_ITEM, &item);
    FlagSet(FLAG_RESTRICTED_MODE);

    BattleSetup_EnforceRestrictedModeItemClause();

    EXPECT_EQ(GetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM), ITEM_LEFTOVERS);
    EXPECT_EQ(GetMonData(&gPlayerParty[1], MON_DATA_HELD_ITEM), ITEM_LEFTOVERS);
}

TEST("Zenmodeman: Merge guard: Egg items do not reserve an item-clause slot")
{
    u16 item = ITEM_LEFTOVERS;
    u8 isEgg = TRUE;

    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_WYNAUT, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[0], MON_DATA_IS_EGG, &isEgg);
    SetMonData(&gPlayerParty[0], MON_DATA_HELD_ITEM, &item);
    CreateMon(&gPlayerParty[1], SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[1], MON_DATA_HELD_ITEM, &item);
    FlagSet(FLAG_RESTRICTED_MODE);

    BattleSetup_EnforceRestrictedModeItemClause();

    EXPECT_EQ(GetMonData(&gPlayerParty[1], MON_DATA_HELD_ITEM), ITEM_LEFTOVERS);
}
