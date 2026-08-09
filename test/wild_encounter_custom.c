#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "test/test.h"
#include "wild_encounter.h"

extern const struct WildPokemon gGraniteCave_B1F_LandMons[];
extern const struct WildPokemon gGraniteCave_B2F_LandMons[];
extern const struct WildPokemon gDewfordGarden0_LandMons[];
extern const struct WildPokemon gDewfordGarden0_ShakeMons[];

static void SetMonotype(enum Type type)
{
    if (type == TYPE_NONE)
        VarSet(VAR_MONOTYPE, 0);
    else if (type > TYPE_MYSTERY)
        VarSet(VAR_MONOTYPE, type - 1);
    else
        VarSet(VAR_MONOTYPE, type);
}

TEST("Zenmodeman: Monotype wild Snorunt is female for a Ghost evolution")
{
    SetMonotype(TYPE_GHOST);
    CreateWildMon(SPECIES_SNORUNT, 20);
    EXPECT_EQ(GetMonGender(&gParties[B_TRAINER_OPPONENT_A][0]), MON_FEMALE);
}

TEST("Zenmodeman: Monotype wild Ralts is male for a Fighting evolution")
{
    SetMonotype(TYPE_FIGHTING);
    CreateWildMon(SPECIES_RALTS, 20);
    EXPECT_EQ(GetMonGender(&gParties[B_TRAINER_OPPONENT_A][0]), MON_MALE);
}

TEST("Zenmodeman: Monotype wild Burmy is male for its Flying evolution")
{
    SetMonotype(TYPE_FLYING);
    CreateWildMon(SPECIES_BURMY, 20);
    EXPECT_EQ(GetMonGender(&gParties[B_TRAINER_OPPONENT_A][0]), MON_MALE);
}

TEST("Zenmodeman: Monotype wild Burmy is female for cloak type evolutions")
{
    enum Type type;

    PARAMETRIZE { type = TYPE_GRASS; }
    PARAMETRIZE { type = TYPE_GROUND; }
    PARAMETRIZE { type = TYPE_STEEL; }

    SetMonotype(type);
    CreateWildMon(SPECIES_BURMY, 20);
    EXPECT_EQ(GetMonGender(&gParties[B_TRAINER_OPPONENT_A][0]), MON_FEMALE);
}

TEST("Zenmodeman: Sweet Scent double battle chance is consumed by one encounter check")
{
    ZeroPlayerPartyMons();
    CreateMon(&gParties[B_TRAINER_PLAYER][0], SPECIES_WOBBUFFET, 20, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(&gParties[B_TRAINER_PLAYER][1], SPECIES_WYNAUT, 20, 0, OTID_STRUCT_PLAYER_ID);

    SetSweetScentDoubleBattleChance(100);
    EXPECT(TryDoDoubleWildBattle());
    EXPECT(!TryDoDoubleWildBattle());
}

TEST("Zenmodeman: Granite Cave retains its expanded early encounter roster and level band")
{
    static const enum Species b1fSpecies[] =
    {
        SPECIES_ZUBAT, SPECIES_ZUBAT, SPECIES_ARON, SPECIES_ARON,
        SPECIES_SABLEYE, SPECIES_MAWILE, SPECIES_MAKUHITA, SPECIES_WOOBAT,
        SPECIES_GRUBBIN, SPECIES_JOLTIK, SPECIES_ONIX, SPECIES_SLOWPOKE_GALAR,
        SPECIES_NOIBAT, SPECIES_IMPIDIMP,
    };
    static const enum Species b2fSpecies[] =
    {
        SPECIES_ZUBAT, SPECIES_ZUBAT, SPECIES_ARON, SPECIES_ARON,
        SPECIES_SABLEYE, SPECIES_MAWILE, SPECIES_ONIX, SPECIES_WOOBAT,
        SPECIES_GRUBBIN, SPECIES_JOLTIK, SPECIES_MAKUHITA, SPECIES_SLOWPOKE_GALAR,
        SPECIES_NOIBAT, SPECIES_IMPIDIMP,
    };
    u32 i;

    for (i = 0; i < ARRAY_COUNT(b1fSpecies); i++)
    {
        EXPECT_EQ(gGraniteCave_B1F_LandMons[i].species, b1fSpecies[i]);
        EXPECT_EQ(gGraniteCave_B1F_LandMons[i].minLevel, 10);
        EXPECT_EQ(gGraniteCave_B1F_LandMons[i].maxLevel, 13);
        EXPECT_EQ(gGraniteCave_B2F_LandMons[i].species, b2fSpecies[i]);
        EXPECT_EQ(gGraniteCave_B2F_LandMons[i].minLevel, 10);
        EXPECT_EQ(gGraniteCave_B2F_LandMons[i].maxLevel, 13);
    }
}

TEST("Zenmodeman: Dewford Garden retains its custom land and shaking encounter leads")
{
    static const enum Species landSpecies[] =
    {
        SPECIES_BOUNSWEET, SPECIES_BOUNSWEET, SPECIES_DEWPIDER, SPECIES_DEWPIDER,
        SPECIES_NICKIT, SPECIES_LECHONK, SPECIES_PAWMI, SPECIES_BONSLY,
        SPECIES_SNOM, SPECIES_SLOWPOKE_GALAR, SPECIES_BULBASAUR, SPECIES_FLETCHLING,
        SPECIES_BAGON, SPECIES_CHARMANDER,
    };
    static const enum Species shakeSpecies[] =
    {
        SPECIES_LEDYBA, SPECIES_WEEDLE, SPECIES_PIDGEY, SPECIES_SHROODLE, SPECIES_BLIPBUG,
    };
    u32 i;

    for (i = 0; i < ARRAY_COUNT(landSpecies); i++)
    {
        EXPECT_EQ(gDewfordGarden0_LandMons[i].species, landSpecies[i]);
        EXPECT_EQ(gDewfordGarden0_LandMons[i].minLevel, 10);
        EXPECT_EQ(gDewfordGarden0_LandMons[i].maxLevel, 13);
    }
    for (i = 0; i < ARRAY_COUNT(shakeSpecies); i++)
    {
        EXPECT_EQ(gDewfordGarden0_ShakeMons[i].species, shakeSpecies[i]);
        EXPECT_EQ(gDewfordGarden0_ShakeMons[i].minLevel, 10);
        EXPECT_EQ(gDewfordGarden0_ShakeMons[i].maxLevel, 13);
    }
}
