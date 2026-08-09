#include "global.h"
#include "battle_main.h"
#include "caps.h"
#include "event_data.h"
#include "party_menu.h"
#include "pokemon.h"
#include "string_util.h"
#include "test/test.h"

static void SetTwoBadgePreRivalLevelCap(void)
{
    FlagSet(FLAG_LEVEL_CAP);
    FlagSet(TRAINER_FLAGS_START + TRAINER_TIANA);
    FlagSet(TRAINER_FLAGS_START + TRAINER_GRUNT_PETALBURG_WOODS);
    FlagSet(TRAINER_FLAGS_START + TRAINER_DARREN);
    FlagSet(FLAG_BADGE01_GET);
    FlagSet(FLAG_BADGE02_GET);
}

TEST("Zenmodeman: Level caps: candies are rejected at the active runtime cap")
{
    SetTwoBadgePreRivalLevelCap();

    EXPECT_EQ(GetCurrentLevelCap(CANDY_CAP), 23);
    EXPECT(Test_CanUseLevelUpCandy(22));
    EXPECT(!Test_CanUseLevelUpCandy(23));

    FlagClear(FLAG_LEVEL_CAP);
    EXPECT(Test_CanUseLevelUpCandy(23));
}

TEST("Zenmodeman: Level caps: Exp Candy cannot raise experience beyond the runtime cap")
{
    struct Pokemon mon;
    enum GrowthRate growthRate = gSpeciesInfo[SPECIES_WOBBUFFET].growthRate;

    SetTwoBadgePreRivalLevelCap();
    CreateMon(&mon, SPECIES_WOBBUFFET, 22, 0, OTID_STRUCT_PLAYER_ID);

    EXPECT(!PokemonUseItemEffects(&mon, ITEM_EXP_CANDY_XL, 0, 0, FALSE));
    EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL), 23);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_EXP), gExperienceTables[growthRate][23]);
}

TEST("Zenmodeman: Trainer scaling: newly eligible evolutions preserve configured properties")
{
    struct Pokemon mon;
    enum Move move = MOVE_STUN_SPORE;
    enum Item item = ITEM_BIG_ROOT;
    u8 abilityNum = 1;
    u8 nature;

    CreateMon(&mon, SPECIES_CUTIEFLY, 25, 0, OTID_STRUCT_PLAYER_ID);
    SetMonData(&mon, MON_DATA_MOVE1, &move);
    SetMonData(&mon, MON_DATA_HELD_ITEM, &item);
    SetMonData(&mon, MON_DATA_ABILITY_NUM, &abilityNum);
    nature = GetNature(&mon);

    Test_TryEvolveTrainerMonForLevelModifier(&mon, 22, 3);

    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), SPECIES_RIBOMBEE);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_LEVEL), 25);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_MOVE1), move);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_HELD_ITEM), item);
    EXPECT_EQ(GetMonData(&mon, MON_DATA_ABILITY_NUM), abilityNum);
    EXPECT_EQ(GetNature(&mon), nature);
}

TEST("Zenmodeman: Trainer scaling: authored unevolved species remain unevolved")
{
    struct Pokemon mon;

    CreateMon(&mon, SPECIES_CUTIEFLY, 26, 0, OTID_STRUCT_PLAYER_ID);
    Test_TryEvolveTrainerMonForLevelModifier(&mon, 25, 1);

    EXPECT_EQ(GetMonData(&mon, MON_DATA_SPECIES), SPECIES_CUTIEFLY);
}
