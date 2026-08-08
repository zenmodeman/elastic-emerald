#include "global.h"
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
