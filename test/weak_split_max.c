#include "global.h"
#include "constants/party_menu.h"
#include "event_data.h"
#include "pokemon.h"
#include "string_util.h"
#include "test/test.h"
#include "data/weak_split_max.h"

bool8 GetWeakSplitMaxStat(void);
u8 TrainMaxIV(void);

static struct Pokemon *CreateWeakSplitFixture(u16 species)
{
    ZeroPlayerPartyMons();
    CreateMonWithIVs(&gParties[B_TRAINER_PLAYER][0], species, 50, 0, OTID_STRUCT_PLAYER_ID, 0);
    gPartiesCount[B_TRAINER_PLAYER] = 1;
    gSpecialVar_0x8004 = 0;
    return &gParties[B_TRAINER_PLAYER][0];
}

TEST("Elastic-tests: Weak split service selects the intended attacking stat and label")
{
    u16 species = SPECIES_NONE;
    u16 stat = STAT_ATK;
    for (u32 i = 0; i < ARRAY_COUNT(sWeakSplitMaxAttackSpecies); i++)
        PARAMETRIZE { species = sWeakSplitMaxAttackSpecies[i]; stat = STAT_ATK; }
    for (u32 i = 0; i < ARRAY_COUNT(sWeakSplitMaxSpAttackSpecies); i++)
        PARAMETRIZE { species = sWeakSplitMaxSpAttackSpecies[i]; stat = STAT_SPATK; }

    struct Pokemon *mon = CreateWeakSplitFixture(species);
    VarSet(VAR_TEMP_1, STAT_DEF);
    EXPECT(GetWeakSplitMaxStat());
    EXPECT_EQ(VarGet(VAR_TEMP_1), stat);
    EXPECT_EQ(StringCompare(gStringVar2, stat == STAT_ATK ? COMPOUND_STRING("Attack") : COMPOUND_STRING("Special Attack")), 0);
    EXPECT_EQ(GetMonData(mon, MON_DATA_ATK_IV), 0);
    EXPECT_EQ(GetMonData(mon, MON_DATA_SPATK_IV), 0);
}

TEST("Elastic-tests: Weak split service rejects unlisted species")
{
    u16 species;
    for (species = 1; species < NUM_SPECIES; species++)
    {
        bool32 listed = FALSE;
        for (u32 i = 0; i < ARRAY_COUNT(sWeakSplitMaxAttackSpecies); i++)
            listed |= species == sWeakSplitMaxAttackSpecies[i];
        for (u32 i = 0; i < ARRAY_COUNT(sWeakSplitMaxSpAttackSpecies); i++)
            listed |= species == sWeakSplitMaxSpAttackSpecies[i];
        if (!listed && gSpeciesInfo[species].baseHP != 0)
            break;
    }
    EXPECT(species < NUM_SPECIES);
    CreateWeakSplitFixture(species);
    VarSet(VAR_TEMP_1, STAT_DEF);
    EXPECT(!GetWeakSplitMaxStat());
    EXPECT_EQ(VarGet(VAR_TEMP_1), STAT_DEF);
}

TEST("Elastic-tests: Weak split service rejects eggs of eligible species")
{
    u16 species = SPECIES_NONE;
    for (u32 i = 0; i < ARRAY_COUNT(sWeakSplitMaxAttackSpecies); i++)
        PARAMETRIZE { species = sWeakSplitMaxAttackSpecies[i]; }
    for (u32 i = 0; i < ARRAY_COUNT(sWeakSplitMaxSpAttackSpecies); i++)
        PARAMETRIZE { species = sWeakSplitMaxSpAttackSpecies[i]; }

    struct Pokemon *mon = CreateWeakSplitFixture(species);
    u8 isEgg = TRUE;
    SetMonData(mon, MON_DATA_IS_EGG, &isEgg);
    VarSet(VAR_TEMP_1, STAT_DEF);
    EXPECT(!GetWeakSplitMaxStat());
    EXPECT_EQ(VarGet(VAR_TEMP_1), STAT_DEF);
}

TEST("Elastic-tests: Weak split service rejects empty slots and cancelled selections")
{
    u16 slot = 0;
    PARAMETRIZE { slot = 1; }
    PARAMETRIZE { slot = PARTY_SIZE; }
    PARAMETRIZE { slot = PARTY_NOTHING_CHOSEN; }

    CreateWeakSplitFixture(sWeakSplitMaxSpAttackSpecies[0]);
    gSpecialVar_0x8004 = slot;
    VarSet(VAR_TEMP_1, STAT_DEF);
    EXPECT(!GetWeakSplitMaxStat());
    EXPECT_EQ(VarGet(VAR_TEMP_1), STAT_DEF);
}

TEST("Elastic-tests: Weak split training maximizes only the selected IV and recalculates stats")
{
    u16 species = SPECIES_NONE;
    u16 stat = STAT_ATK;
    for (u32 i = 0; i < ARRAY_COUNT(sWeakSplitMaxAttackSpecies); i++)
        PARAMETRIZE { species = sWeakSplitMaxAttackSpecies[i]; stat = STAT_ATK; }
    for (u32 i = 0; i < ARRAY_COUNT(sWeakSplitMaxSpAttackSpecies); i++)
        PARAMETRIZE { species = sWeakSplitMaxSpAttackSpecies[i]; stat = STAT_SPATK; }

    struct Pokemon *mon = CreateWeakSplitFixture(species);
    u32 oldStat = GetMonData(mon, MON_DATA_ATK + stat - STAT_ATK);
    EXPECT(GetWeakSplitMaxStat());
    EXPECT(TrainMaxIV());
    for (u32 i = 0; i < NUM_STATS; i++)
        EXPECT_EQ(GetMonData(mon, MON_DATA_HP_IV + i), i == stat ? MAX_PER_STAT_IVS : 0);
    EXPECT(GetMonData(mon, MON_DATA_ATK + stat - STAT_ATK) > oldStat);
    EXPECT(!TrainMaxIV());
    EXPECT_EQ(GetMonData(mon, MON_DATA_HP_IV + stat), MAX_PER_STAT_IVS);
}

TEST("Elastic-tests: Weak split service trains the chosen party member")
{
    struct Pokemon *first = CreateWeakSplitFixture(sWeakSplitMaxAttackSpecies[0]);
    struct Pokemon *chosen = &gParties[B_TRAINER_PLAYER][1];
    CreateMonWithIVs(chosen, sWeakSplitMaxSpAttackSpecies[0], 50, 0, OTID_STRUCT_PLAYER_ID, 0);
    gPartiesCount[B_TRAINER_PLAYER] = 2;
    gSpecialVar_0x8004 = 1;

    EXPECT(GetWeakSplitMaxStat());
    EXPECT_EQ(VarGet(VAR_TEMP_1), STAT_SPATK);
    EXPECT(TrainMaxIV());
    EXPECT_EQ(GetMonData(chosen, MON_DATA_SPATK_IV), MAX_PER_STAT_IVS);
    EXPECT_EQ(GetMonData(chosen, MON_DATA_ATK_IV), 0);
    EXPECT_EQ(GetMonData(first, MON_DATA_ATK_IV), 0);
    EXPECT_EQ(GetMonData(first, MON_DATA_SPATK_IV), 0);
}
