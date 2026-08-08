#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "test/test.h"
#include "wild_encounter.h"

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
