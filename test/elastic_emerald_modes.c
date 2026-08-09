#include "global.h"
#include "battle_setup.h"
#include "caps.h"
#include "event_data.h"
#include "field_specials.h"
#include "item.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "string_util.h"
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

TEST("Zenmodeman: Merge guard: EV Mode restores badge-based per-stat caps")
{
    EXPECT_EQ(GetEVStatCap(), 0);

    FlagSet(FLAG_EV_MODE);
    EXPECT_EQ(GetEVStatCap(), 36);
    FlagSet(FLAG_BADGE01_GET);
    EXPECT_EQ(GetEVStatCap(), 48);
    FlagSet(FLAG_BADGE02_GET);
    EXPECT_EQ(GetEVStatCap(), 84);
    FlagSet(FLAG_BADGE03_GET);
    EXPECT_EQ(GetEVStatCap(), 120);
    FlagSet(FLAG_BADGE04_GET);
    EXPECT_EQ(GetEVStatCap(), 156);
    FlagSet(FLAG_BADGE05_GET);
    EXPECT_EQ(GetEVStatCap(), 192);
    FlagSet(FLAG_BADGE06_GET);
    EXPECT_EQ(GetEVStatCap(), 228);
    FlagSet(FLAG_BADGE07_GET);
    EXPECT_EQ(GetEVStatCap(), MAX_PER_STAT_EVS);
}

TEST("Zenmodeman: Merge guard: Pokemon gain EVs only in EV Mode")
{
    struct Pokemon mon;

    CreateMon(&mon, SPECIES_WOBBUFFET, 5, 0, OTID_STRUCT_PLAYER_ID);
    MonGainEVs(&mon, SPECIES_CATERPIE);
    EXPECT_EQ(GetMonEVCount(&mon), 0);

    FlagSet(FLAG_EV_MODE);
    MonGainEVs(&mon, SPECIES_CATERPIE);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HP_EV), gSpeciesInfo[SPECIES_CATERPIE].evYield_HP);
}

TEST("Zenmodeman: Merge guard: EV items work only in EV Mode")
{
    struct Pokemon mon;

    CreateMon(&mon, SPECIES_WOBBUFFET, 5, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT(PokemonUseItemEffects(&mon, ITEM_HP_UP, 0, 0, FALSE));
    EXPECT_EQ(GetMonEVCount(&mon), 0);

    FlagSet(FLAG_EV_MODE);
    EXPECT(!PokemonUseItemEffects(&mon, ITEM_HP_UP, 0, 0, FALSE));
    EXPECT_GT(GetMonData(&mon, MON_DATA_HP_EV), 0);
    EXPECT_LE(GetMonData(&mon, MON_DATA_HP_EV), GetEVStatCap());
}

TEST("Zenmodeman: Merge guard: EV Mode enforces per-stat and derived total caps")
{
    struct Pokemon mon;
    u32 ev;

    FlagSet(FLAG_EV_MODE);
    CreateMon(&mon, SPECIES_WOBBUFFET, 5, 0, OTID_STRUCT_PLAYER_ID);

    ev = GetEVStatCap();
    SetMonData(&mon, MON_DATA_HP_EV, &ev);
    MonGainEVs(&mon, SPECIES_CATERPIE);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HP_EV), GetEVStatCap());

    ev = GetEVStatCap();
    SetMonData(&mon, MON_DATA_ATK_EV, &ev);
    ev = 6;
    SetMonData(&mon, MON_DATA_DEF_EV, &ev);
    MonGainEVs(&mon, SPECIES_CATERPIE);
    EXPECT_EQ(GetMonEVCount(&mon), GetEVStatCap() * 2 + 6);
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

TEST("Zenmodeman: Original expanded Tier Points preserve representative four five and six point species")
{
    struct Pokemon mon;

    CreateMon(&mon, SPECIES_CHARIZARD, 50, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetMonTierPoints(&mon), 4);
    CreateMon(&mon, SPECIES_SNORLAX, 50, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetMonTierPoints(&mon), 5);
    CreateMon(&mon, SPECIES_SHEDINJA, 50, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetMonTierPoints(&mon), 6);
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

TEST("Zenmodeman: Tiered PC placement computes the party budget around the destination slot")
{
    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_SNORLAX, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_CHARIZARD, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[2], SPECIES_SHEDINJA, 50, 0, OTID_STRUCT_PLAYER_ID);

    EXPECT_EQ(CountPartyPointsExcept(1), 11);
    EXPECT_EQ(CountPartyPointsExcept(2), 9);
    EXPECT_EQ(CountPartyPointsExcept(5), 15);
}

TEST("Zenmodeman: Tiered egg hatch detects current-party excess only after the egg becomes a Pokemon")
{
    u8 isEgg = TRUE;

    FlagSet(FLAG_TIERED);
    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_CHANSEY, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[1], SPECIES_CHANSEY, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[2], SPECIES_CHANSEY, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gPlayerParty[3], SPECIES_CHARIZARD, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[3], MON_DATA_IS_EGG, &isEgg);

    EXPECT_EQ(GetCurrentPartyTierPointExcess(), 0);
    isEgg = FALSE;
    SetMonData(&gPlayerParty[3], MON_DATA_IS_EGG, &isEgg);
    EXPECT_EQ(GetCurrentPartyTierPointExcess(), 2);

    FlagClear(FLAG_TIERED);
    EXPECT_EQ(GetCurrentPartyTierPointExcess(), 0);
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

TEST("Zenmodeman: Merge guard: Scatterbug patterns share Tier Points")
{
    struct Pokemon base;
    struct Pokemon form;

    CreateMon(&base, SPECIES_SCATTERBUG, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&form, SPECIES_SCATTERBUG_POKEBALL, 50, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetMonTierPoints(&base), GetMonTierPoints(&form));
}

TEST("Zenmodeman: Merge guard: Spewpa patterns share Tier Points")
{
    struct Pokemon base;
    struct Pokemon form;

    CreateMon(&base, SPECIES_SPEWPA, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&form, SPECIES_SPEWPA_POKEBALL, 50, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetMonTierPoints(&base), GetMonTierPoints(&form));
}

TEST("Zenmodeman: Merge guard: Squawkabilly colors share Tier Points")
{
    struct Pokemon base;
    struct Pokemon form;

    CreateMon(&base, SPECIES_SQUAWKABILLY, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&form, SPECIES_SQUAWKABILLY_WHITE, 50, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetMonTierPoints(&base), GetMonTierPoints(&form));
}

TEST("Zenmodeman: Merge guard: Pumpkaboo sizes share Tier Points")
{
    struct Pokemon base;
    struct Pokemon form;

    CreateMon(&base, SPECIES_PUMPKABOO, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&form, SPECIES_PUMPKABOO_SUPER, 50, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetMonTierPoints(&base), GetMonTierPoints(&form));
}

TEST("Zenmodeman: Merge guard: Gourgeist sizes share Tier Points")
{
    struct Pokemon base;
    struct Pokemon form;

    CreateMon(&base, SPECIES_GOURGEIST, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&form, SPECIES_GOURGEIST_SUPER, 50, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetMonTierPoints(&base), GetMonTierPoints(&form));
}

TEST("Zenmodeman: Merge guard: Flabebe colors share Tier Points")
{
    struct Pokemon base;
    struct Pokemon form;

    CreateMon(&base, SPECIES_FLABEBE, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&form, SPECIES_FLABEBE_WHITE, 50, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetMonTierPoints(&base), GetMonTierPoints(&form));
}

TEST("Zenmodeman: Merge guard: Floette colors share Tier Points")
{
    struct Pokemon base;
    struct Pokemon form;

    CreateMon(&base, SPECIES_FLOETTE, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&form, SPECIES_FLOETTE_WHITE, 50, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetMonTierPoints(&base), GetMonTierPoints(&form));
}

TEST("Zenmodeman: Merge guard: Florges colors share Tier Points")
{
    struct Pokemon base;
    struct Pokemon form;

    CreateMon(&base, SPECIES_FLORGES, 50, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&form, SPECIES_FLORGES_WHITE, 50, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetMonTierPoints(&base), GetMonTierPoints(&form));
}

TEST("Zenmodeman: Merge guard: Politoed without Drizzle keeps its base Tier Points")
{
    struct Pokemon mon;
    u8 abilitySlot = FindAbilitySlot(SPECIES_POLITOED, ABILITY_DAMP);

    EXPECT_NE(abilitySlot, NUM_ABILITY_SLOTS);
    CreateMon(&mon, SPECIES_POLITOED, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_ABILITY_NUM, &abilitySlot);
    EXPECT_EQ(GetMonTierPoints(&mon), 3);
}

TEST("Zenmodeman: Merge guard: Pelipper with Drizzle costs six Tier Points")
{
    struct Pokemon mon;
    u8 abilitySlot = FindAbilitySlot(SPECIES_PELIPPER, ABILITY_DRIZZLE);

    EXPECT_NE(abilitySlot, NUM_ABILITY_SLOTS);
    CreateMon(&mon, SPECIES_PELIPPER, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_ABILITY_NUM, &abilitySlot);
    EXPECT_EQ(GetMonTierPoints(&mon), 6);
}

TEST("Zenmodeman: Merge guard: Vulpix with Drought drops after badge eight")
{
    struct Pokemon mon;
    u8 abilitySlot = FindAbilitySlot(SPECIES_VULPIX, ABILITY_DROUGHT);

    EXPECT_NE(abilitySlot, NUM_ABILITY_SLOTS);
    CreateMon(&mon, SPECIES_VULPIX, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_ABILITY_NUM, &abilitySlot);
    EXPECT_EQ(GetMonTierPoints(&mon), 6);
    FlagSet(FLAG_BADGE08_GET);
    EXPECT_EQ(GetMonTierPoints(&mon), 5);
}

TEST("Zenmodeman: Merge guard: EV cap uses the highest earned badge without requiring earlier flags")
{
    FlagSet(FLAG_EV_MODE);
    FlagSet(FLAG_BADGE06_GET);
    EXPECT_EQ(GetEVStatCap(), 228);
}

TEST("Zenmodeman: Merge guard: Electric monotype seeds only its Ground resist berry")
{
    VarSet(VAR_MONOTYPE, TYPE_ELECTRIC - 1);
    PopulateMonotypeResistBerriesInPC();

    EXPECT(CheckPCHasItem(ITEM_SHUCA_BERRY, 12));
    EXPECT(!CheckPCHasItem(ITEM_CHOPLE_BERRY, 1));
    EXPECT(!CheckPCHasItem(ITEM_YACHE_BERRY, 1));
}

TEST("Zenmodeman: Merge guard: Normal monotype seeds only its Fighting resist berry")
{
    VarSet(VAR_MONOTYPE, TYPE_NORMAL);
    PopulateMonotypeResistBerriesInPC();

    EXPECT(CheckPCHasItem(ITEM_CHOPLE_BERRY, 12));
    EXPECT(!CheckPCHasItem(ITEM_COLBUR_BERRY, 1));
}

TEST("Zenmodeman: Merge guard: Dragon monotype seeds Ice Dragon and Fairy resist berries")
{
    VarSet(VAR_MONOTYPE, TYPE_DRAGON - 1);
    PopulateMonotypeResistBerriesInPC();

    EXPECT(CheckPCHasItem(ITEM_YACHE_BERRY, 12));
    EXPECT(CheckPCHasItem(ITEM_HABAN_BERRY, 12));
    EXPECT(CheckPCHasItem(ITEM_ROSELI_BERRY, 12));
    EXPECT(!CheckPCHasItem(ITEM_CHOPLE_BERRY, 1));
}

TEST("Zenmodeman: Merge guard: Ghost monotype seeds Ghost and Dark resist berries")
{
    VarSet(VAR_MONOTYPE, TYPE_GHOST);
    PopulateMonotypeResistBerriesInPC();

    EXPECT(CheckPCHasItem(ITEM_KASIB_BERRY, 12));
    EXPECT(CheckPCHasItem(ITEM_COLBUR_BERRY, 12));
    EXPECT(!CheckPCHasItem(ITEM_CHOPLE_BERRY, 1));
}

TEST("Zenmodeman: Merge guard: Restricted item clause handles two duplicate groups independently")
{
    u16 leftovers = ITEM_LEFTOVERS;
    u16 blackSludge = ITEM_BLACK_SLUDGE;

    ZeroPlayerPartyMons();
    for (u32 i = 0; i < 4; i++)
        CreateMon(&gParties[B_TRAINER_PLAYER][i], SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HELD_ITEM, &leftovers);
    SetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_HELD_ITEM, &blackSludge);
    SetMonData(&gParties[B_TRAINER_PLAYER][2], MON_DATA_HELD_ITEM, &leftovers);
    SetMonData(&gParties[B_TRAINER_PLAYER][3], MON_DATA_HELD_ITEM, &blackSludge);
    FlagSet(FLAG_RESTRICTED_MODE);

    BattleSetup_EnforceRestrictedModeItemClause();

    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HELD_ITEM), ITEM_LEFTOVERS);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_HELD_ITEM), ITEM_BLACK_SLUDGE);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][2], MON_DATA_HELD_ITEM), ITEM_NONE);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][3], MON_DATA_HELD_ITEM), ITEM_NONE);
    EXPECT(CheckBagHasItem(ITEM_LEFTOVERS, 1));
    EXPECT(CheckBagHasItem(ITEM_BLACK_SLUDGE, 1));
}

TEST("Zenmodeman: Merge guard: Restricted item clause detects duplicates separated by an egg")
{
    u16 item = ITEM_LEFTOVERS;
    u8 isEgg = TRUE;

    ZeroPlayerPartyMons();
    for (u32 i = 0; i < 3; i++)
        CreateMon(&gParties[B_TRAINER_PLAYER][i], SPECIES_WOBBUFFET, 50, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HELD_ITEM, &item);
    SetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_IS_EGG, &isEgg);
    SetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_HELD_ITEM, &item);
    SetMonData(&gParties[B_TRAINER_PLAYER][2], MON_DATA_HELD_ITEM, &item);
    FlagSet(FLAG_RESTRICTED_MODE);

    BattleSetup_EnforceRestrictedModeItemClause();

    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_HELD_ITEM), ITEM_LEFTOVERS);
    EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][2], MON_DATA_HELD_ITEM), ITEM_NONE);
    EXPECT(CheckBagHasItem(ITEM_LEFTOVERS, 1));
}

TEST("Zenmodeman: Merge guard: Free tutor eligibility rejects null Pokemon")
{
    EXPECT(!IsMonFreeCenterTutorEligible(NULL));
    EXPECT(!IsMonFreeMoveRelearnerEligible(NULL));
}

TEST("Zenmodeman: Merge guard: Free tutor eligibility rejects eggs")
{
    struct Pokemon mon;
    u8 isEgg = TRUE;

    CreateMon(&mon, SPECIES_CATERPIE, 5, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_IS_EGG, &isEgg);
    EXPECT(!IsMonFreeCenterTutorEligible(&mon));
    EXPECT(!IsMonFreeMoveRelearnerEligible(&mon));
}

TEST("Zenmodeman: Ability tutor offers and applies either distinct niche ability")
{
    u8 abilitySlot = FindAbilitySlot(SPECIES_LITLEO, ABILITY_RIVALRY);

    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_LITLEO, 20, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[0], MON_DATA_ABILITY_NUM, &abilitySlot);
    gSpecialVar_0x8004 = 0;

    EXPECT_EQ(GetTutorAbility(), 2);
    EXPECT_EQ(StringCompare(gStringVar2, gAbilitiesInfo[ABILITY_UNNERVE].name), 0);
    EXPECT_EQ(StringCompare(gStringVar3, gAbilitiesInfo[ABILITY_MOXIE].name), 0);

    gSpecialVar_Result = 1;
    SetTutorAbility();
    EXPECT_EQ(GetMonAbility(&gPlayerParty[0]), ABILITY_MOXIE);
}

TEST("Zenmodeman: Ability tutor applies its only option regardless of stale menu result")
{
    u8 abilitySlot = FindAbilitySlot(SPECIES_FLETCHLING, ABILITY_GALE_WINGS);

    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_FLETCHLING, 20, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[0], MON_DATA_ABILITY_NUM, &abilitySlot);
    gSpecialVar_0x8004 = 0;

    EXPECT_EQ(GetTutorAbility(), 1);
    EXPECT_EQ(StringCompare(gStringVar2, gAbilitiesInfo[ABILITY_BIG_PECKS].name), 0);

    gSpecialVar_Result = 99;
    SetTutorAbility();
    EXPECT_EQ(GetMonAbility(&gPlayerParty[0]), ABILITY_BIG_PECKS);
}

TEST("Zenmodeman: Ability tutor leaves Pokemon with no niche option unchanged")
{
    u8 abilitySlot = FindAbilitySlot(SPECIES_BULBASAUR, ABILITY_OVERGROW);

    ZeroPlayerPartyMons();
    CreateMon(&gPlayerParty[0], SPECIES_BULBASAUR, 20, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&gPlayerParty[0], MON_DATA_ABILITY_NUM, &abilitySlot);
    gSpecialVar_0x8004 = 0;

    EXPECT_EQ(GetTutorAbility(), 0);
    gSpecialVar_Result = 0;
    SetTutorAbility();
    EXPECT_EQ(GetMonAbility(&gPlayerParty[0]), ABILITY_OVERGROW);
}

TEST("Zenmodeman: Resource free tutors reject Beedrill's explicit tier exception")
{
    struct Pokemon mon;

    CreateMon(&mon, SPECIES_BEEDRILL, 20, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT(!IsMonFreeCenterTutorEligible(&mon));
    EXPECT(!IsMonFreeMoveRelearnerEligible(&mon));
}

TEST("Zenmodeman: Resource free tutors inspect stronger future evolutions")
{
    struct Pokemon mon;

    CreateMon(&mon, SPECIES_CATERPIE, 5, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT(!IsMonFreeCenterTutorEligible(&mon));
    EXPECT(!IsMonFreeMoveRelearnerEligible(&mon));
}
