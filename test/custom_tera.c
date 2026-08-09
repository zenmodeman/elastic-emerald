#include "global.h"
#include "battle_terastal.h"
#include "config/battle.h"
#include "event_data.h"
#include "pokemon.h"
#include "test/test.h"

static void SetMonotype(enum Type type)
{
    if (type == TYPE_NONE)
        VarSet(VAR_MONOTYPE, 0);
    else if (type > TYPE_MYSTERY)
        VarSet(VAR_MONOTYPE, type - 1);
    else
        VarSet(VAR_MONOTYPE, type);
}

TEST("Zenmodeman: Tera Orb charging remains intentionally cost free")
{
    EXPECT_EQ(B_FLAG_TERA_ORB_CHARGED, FLAG_TERA_CHARGED);
    EXPECT_EQ(B_FLAG_TERA_ORB_NO_COST, FLAG_TERA_CHARGED);
}

TEST("Zenmodeman: Random Tera assignment spans non-native types")
{
    EXPECT_EQ(GetCustomTeraType(SPECIES_JOLTEON, TYPE_WATER - 1), TYPE_WATER);
    EXPECT_EQ(GetCustomTeraType(SPECIES_JOLTEON, TYPE_MYSTERY - 1), TYPE_STELLAR);
}

TEST("Zenmodeman: Curated Tera assigns the latest electric-species types")
{
    FlagSet(FLAG_CURATED_TERA);

    EXPECT_EQ(GetCustomTeraType(SPECIES_JOLTEON, 0), TYPE_FIRE);
    EXPECT_EQ(GetCustomTeraType(SPECIES_VIKAVOLT, 0), TYPE_GRASS);
    EXPECT_EQ(GetCustomTeraType(SPECIES_RAICHU_ALOLA, 0), TYPE_NORMAL);
}

TEST("Zenmodeman: Curated Tera retains the surviving early Water-species adjustments")
{
    FlagSet(FLAG_CURATED_TERA);

    EXPECT_EQ(GetCustomTeraType(SPECIES_KRABBY, 0), TYPE_ROCK);
    EXPECT_EQ(GetCustomTeraType(SPECIES_KINGLER, 0), TYPE_ROCK);
    EXPECT_EQ(GetCustomTeraType(SPECIES_STARYU, 0), TYPE_NORMAL);
}

TEST("Zenmodeman: Monotype-compatible random Tera bypasses a curated type")
{
    FlagSet(FLAG_CURATED_TERA);
    SetMonotype(TYPE_WATER);

    EXPECT_EQ(GetCustomTeraType(SPECIES_JOLTEON, TYPE_WATER - 1), TYPE_WATER);
}

TEST("Zenmodeman: Pokemon creation stores its custom Tera assignment")
{
    struct Pokemon mon;

    FlagSet(FLAG_CURATED_TERA);
    CreateMonWithIVsPersonality(&mon, SPECIES_JOLTEON, 5, 0, 1);

    EXPECT_EQ(GetMonData(&mon, MON_DATA_TERA_TYPE), TYPE_FIRE);
}

TEST("Zenmodeman: Restricted Tera permits every Pokemon below four Tier Points")
{
    EXPECT(!IsRestrictedModeTeraCombinationBanned(SPECIES_MEW, ABILITY_SYNCHRONIZE, 3));
    EXPECT(IsRestrictedModeTeraCombinationBanned(SPECIES_MEW, ABILITY_SYNCHRONIZE, 4));
}

TEST("Zenmodeman: Restricted Tera exceptions depend on the lower power ability")
{
    EXPECT(!IsRestrictedModeTeraCombinationBanned(SPECIES_AZUMARILL, ABILITY_THICK_FAT, 4));
    EXPECT(IsRestrictedModeTeraCombinationBanned(SPECIES_AZUMARILL, ABILITY_HUGE_POWER, 4));
    EXPECT(!IsRestrictedModeTeraCombinationBanned(SPECIES_DIGGERSBY, ABILITY_CHEEK_POUCH, 4));
    EXPECT(IsRestrictedModeTeraCombinationBanned(SPECIES_DIGGERSBY, ABILITY_HUGE_POWER, 4));
    EXPECT(!IsRestrictedModeTeraCombinationBanned(SPECIES_MEDICHAM, ABILITY_TELEPATHY, 4));
    EXPECT(IsRestrictedModeTeraCombinationBanned(SPECIES_MEDICHAM, ABILITY_PURE_POWER, 4));
}

TEST("Zenmodeman: Restricted Tera weather speed and armor exceptions remain ability aware")
{
    EXPECT(!IsRestrictedModeTeraCombinationBanned(SPECIES_GIGALITH, ABILITY_STURDY, 4));
    EXPECT(IsRestrictedModeTeraCombinationBanned(SPECIES_GIGALITH, ABILITY_SAND_STREAM, 4));
    EXPECT(!IsRestrictedModeTeraCombinationBanned(SPECIES_BLAZIKEN, ABILITY_BLAZE, 4));
    EXPECT(IsRestrictedModeTeraCombinationBanned(SPECIES_BLAZIKEN, ABILITY_SPEED_BOOST, 4));
    EXPECT(!IsRestrictedModeTeraCombinationBanned(SPECIES_POLTEAGEIST, ABILITY_CURSED_BODY, 4));
    EXPECT(IsRestrictedModeTeraCombinationBanned(SPECIES_POLTEAGEIST, ABILITY_WEAK_ARMOR, 4));
}
