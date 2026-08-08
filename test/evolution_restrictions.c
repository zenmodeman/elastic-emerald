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

static void CreateHappyMon(struct Pokemon *mon, enum Species species, u32 level)
{
    u32 friendship = MAX_FRIENDSHIP;

    CreateMon(mon, species, level, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(mon, MON_DATA_FRIENDSHIP, &friendship);
}

static enum Species GetNormalEvolution(struct Pokemon *mon)
{
    return GetEvolutionTargetSpecies(mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, NULL, CHECK_EVO);
}

TEST("Zenmodeman: Evolution restrictions: normal mode ignores item evolution level guards")
{
    struct Pokemon mon;

    CreateMon(&mon, SPECIES_NIDORINO, 20, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT(!DoesNotMeetRestrictedEvoItemConditions(&mon, ITEM_MOON_STONE));
}

TEST("Zenmodeman: Evolution restrictions: Nidorina and Nidorino require level 25 in Restricted Mode")
{
    enum Species species;
    struct Pokemon mon;

    PARAMETRIZE { species = SPECIES_NIDORINA; }
    PARAMETRIZE { species = SPECIES_NIDORINO; }
    FlagSet(FLAG_RESTRICTED_MODE);
    CreateMon(&mon, species, 24, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT(DoesNotMeetRestrictedEvoItemConditions(&mon, ITEM_MOON_STONE));
}

TEST("Zenmodeman: Evolution restrictions: Nidorina and Nidorino unlock at level 25")
{
    enum Species species;
    struct Pokemon mon;

    PARAMETRIZE { species = SPECIES_NIDORINA; }
    PARAMETRIZE { species = SPECIES_NIDORINO; }
    FlagSet(FLAG_RESTRICTED_MODE);
    CreateMon(&mon, species, 25, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT(!DoesNotMeetRestrictedEvoItemConditions(&mon, ITEM_MOON_STONE));
}

TEST("Zenmodeman: Evolution restrictions: trade and Slowpoke item evolutions require level 32")
{
    enum Species species;
    struct Pokemon mon;

    PARAMETRIZE { species = SPECIES_SLOWPOKE; }
    PARAMETRIZE { species = SPECIES_SLOWBRO_GALAR; }
    PARAMETRIZE { species = SPECIES_KADABRA; }
    PARAMETRIZE { species = SPECIES_GRAVELER; }
    PARAMETRIZE { species = SPECIES_MACHOKE; }
    PARAMETRIZE { species = SPECIES_HAUNTER; }
    FlagSet(FLAG_RESTRICTED_MODE);
    CreateMon(&mon, species, 31, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT(DoesNotMeetRestrictedEvoItemConditions(&mon, ITEM_LINKING_CORD));
}

TEST("Zenmodeman: Evolution restrictions: trade and Slowpoke item evolutions unlock at level 32")
{
    enum Species species;
    struct Pokemon mon;

    PARAMETRIZE { species = SPECIES_SLOWPOKE; }
    PARAMETRIZE { species = SPECIES_SLOWBRO_GALAR; }
    PARAMETRIZE { species = SPECIES_KADABRA; }
    PARAMETRIZE { species = SPECIES_GRAVELER; }
    PARAMETRIZE { species = SPECIES_MACHOKE; }
    PARAMETRIZE { species = SPECIES_HAUNTER; }
    FlagSet(FLAG_RESTRICTED_MODE);
    CreateMon(&mon, species, 32, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT(!DoesNotMeetRestrictedEvoItemConditions(&mon, ITEM_LINKING_CORD));
}

TEST("Zenmodeman: Evolution restrictions: unrelated item evolutions remain unrestricted")
{
    struct Pokemon mon;

    FlagSet(FLAG_RESTRICTED_MODE);
    CreateMon(&mon, SPECIES_PIKACHU, 5, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT(!DoesNotMeetRestrictedEvoItemConditions(&mon, ITEM_THUNDER_STONE));
}

TEST("Zenmodeman: Evolution restrictions: blocked item evolution remains visible to item checks")
{
    struct Pokemon mon;

    FlagSet(FLAG_RESTRICTED_MODE);
    CreateMon(&mon, SPECIES_NIDORINO, 24, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_ITEM_CHECK, ITEM_MOON_STONE, NULL, NULL, CHECK_EVO), SPECIES_NIDOKING);
    EXPECT(DoesNotMeetRestrictedEvoItemConditions(&mon, ITEM_MOON_STONE));
}

TEST("Zenmodeman: Evolution restrictions: Woobat can evolve below level 18 outside Restricted Mode")
{
    struct Pokemon mon;

    CreateHappyMon(&mon, SPECIES_WOOBAT, 17);
    EXPECT_EQ(GetNormalEvolution(&mon), SPECIES_SWOOBAT);
}

TEST("Zenmodeman: Evolution restrictions: Restricted Mode blocks Woobat below level 18")
{
    struct Pokemon mon;

    FlagSet(FLAG_RESTRICTED_MODE);
    CreateHappyMon(&mon, SPECIES_WOOBAT, 17);
    EXPECT_EQ(GetNormalEvolution(&mon), SPECIES_NONE);
}

TEST("Zenmodeman: Evolution restrictions: Restricted Mode allows Woobat at level 18")
{
    struct Pokemon mon;

    FlagSet(FLAG_RESTRICTED_MODE);
    CreateHappyMon(&mon, SPECIES_WOOBAT, 18);
    EXPECT_EQ(GetNormalEvolution(&mon), SPECIES_SWOOBAT);
}

TEST("Zenmodeman: Evolution restrictions: Restricted Mode blocks Golbat below level 30")
{
    struct Pokemon mon;

    FlagSet(FLAG_RESTRICTED_MODE);
    CreateHappyMon(&mon, SPECIES_GOLBAT, 29);
    EXPECT_EQ(GetNormalEvolution(&mon), SPECIES_NONE);
}

TEST("Zenmodeman: Evolution restrictions: Restricted Mode allows Golbat at level 30")
{
    struct Pokemon mon;

    FlagSet(FLAG_RESTRICTED_MODE);
    CreateHappyMon(&mon, SPECIES_GOLBAT, 30);
    EXPECT_EQ(GetNormalEvolution(&mon), SPECIES_CROBAT);
}

TEST("Zenmodeman: Evolution restrictions: Fletchling evolves when monotype mode is disabled")
{
    struct Pokemon mon;

    CreateMon(&mon, SPECIES_FLETCHLING, 17, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetNormalEvolution(&mon), SPECIES_FLETCHINDER);
}

TEST("Zenmodeman: Evolution restrictions: Fire monotype permits Fletchling evolution")
{
    struct Pokemon mon;

    SetMonotype(TYPE_FIRE);
    CreateMon(&mon, SPECIES_FLETCHLING, 17, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetNormalEvolution(&mon), SPECIES_FLETCHINDER);
}

TEST("Zenmodeman: Evolution restrictions: Flying monotype permits Fletchling evolution")
{
    struct Pokemon mon;

    SetMonotype(TYPE_FLYING);
    CreateMon(&mon, SPECIES_FLETCHLING, 17, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetNormalEvolution(&mon), SPECIES_FLETCHINDER);
}

TEST("Zenmodeman: Evolution restrictions: incompatible monotype blocks Fletchling evolution")
{
    struct Pokemon mon;

    SetMonotype(TYPE_WATER);
    CreateMon(&mon, SPECIES_FLETCHLING, 17, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetNormalEvolution(&mon), SPECIES_NONE);
}

TEST("Zenmodeman: Evolution restrictions: Water monotype permits Magikarp evolution")
{
    struct Pokemon mon;

    SetMonotype(TYPE_WATER);
    CreateMon(&mon, SPECIES_MAGIKARP, 20, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetNormalEvolution(&mon), SPECIES_GYARADOS);
}

TEST("Zenmodeman: Evolution restrictions: Flying monotype permits Magikarp evolution")
{
    struct Pokemon mon;

    SetMonotype(TYPE_FLYING);
    CreateMon(&mon, SPECIES_MAGIKARP, 20, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetNormalEvolution(&mon), SPECIES_GYARADOS);
}

TEST("Zenmodeman: Evolution restrictions: incompatible monotype blocks Magikarp evolution")
{
    struct Pokemon mon;

    SetMonotype(TYPE_FIRE);
    CreateMon(&mon, SPECIES_MAGIKARP, 20, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetNormalEvolution(&mon), SPECIES_NONE);
}

TEST("Zenmodeman: Evolution restrictions: Restricted and monotype gates compose independently")
{
    struct Pokemon mon;

    FlagSet(FLAG_RESTRICTED_MODE);
    SetMonotype(TYPE_FIRE);
    CreateMon(&mon, SPECIES_FLETCHLING, 17, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetNormalEvolution(&mon), SPECIES_FLETCHINDER);
}
