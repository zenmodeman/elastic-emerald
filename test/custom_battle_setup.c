#include "global.h"
#include "battle_setup.h"
#include "constants/battle_setup.h"
#include "data.h"
#include "event_scripts.h"
#include "test/test.h"

extern u32 CalculateTrainerPartyMoney(const struct Trainer *trainer, u32 multiplier, bool32 isDoubleBattle, bool32 hasTwoOpponents);

TEST("Zenmodeman: continue-after-loss trainer battles retain no-intro setup")
{
    TRAINER_BATTLE_PARAM.mode = TRAINER_BATTLE_CONTINUE_AFTER_LOSE;

    EXPECT_EQ(BattleSetup_ConfigureTrainerBattle(NULL), EventScript_DoNoIntroTrainerBattle);
    EXPECT_EQ(GetTrainerBattleMode(), TRAINER_BATTLE_CONTINUE_AFTER_LOSE);
}

TEST("Zenmodeman: continue-after-loss and early-rival battle modes remain distinct")
{
    EXPECT_NE(TRAINER_BATTLE_CONTINUE_AFTER_LOSE, TRAINER_BATTLE_EARLY_RIVAL);
    EXPECT_EQ(TRAINER_BATTLE_CONTINUE_AFTER_LOSE, 14);
    EXPECT_EQ(TRAINER_BATTLE_EARLY_RIVAL, 15);
}

TEST("Zenmodeman: Youngster James rematches always reuse his custom opening team")
{
    u32 i;

    for (i = 0; i < REMATCHES_COUNT; i++)
        EXPECT_EQ(gRematchTable[REMATCH_JAMES].trainerIds[i], TRAINER_JAMES_1);
    EXPECT_EQ(gRematchTable[REMATCH_JAMES].mapGroup, MAP_GROUP(MAP_PETALBURG_WOODS));
    EXPECT_EQ(gRematchTable[REMATCH_JAMES].mapNum, MAP_NUM(MAP_PETALBURG_WOODS));
}

TEST("Zenmodeman: trainer prize money uses the sum of every party level")
{
    static const struct TrainerMon party[] = {{.lvl = 7}, {.lvl = 11}, {.lvl = 13}};
    static const struct Trainer trainer = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .partySize = ARRAY_COUNT(party),
        .party = party,
    };
    u32 trainerMoney = gTrainerClasses[trainer.trainerClass].money ?: 5;
    u32 totalLevels = 7 + 11 + 13;

    EXPECT_EQ(CalculateTrainerPartyMoney(&trainer, 1, FALSE, FALSE), 4 * totalLevels * trainerMoney);
    EXPECT_NE(CalculateTrainerPartyMoney(&trainer, 1, FALSE, FALSE), 4 * party[ARRAY_COUNT(party) - 1].lvl * trainerMoney);
}

TEST("Zenmodeman: trainer prize money doubles for one double-battle opponent only")
{
    static const struct TrainerMon party[] = {{.lvl = 10}, {.lvl = 12}};
    static const struct Trainer trainer = {
        .trainerClass = TRAINER_CLASS_YOUNGSTER,
        .partySize = ARRAY_COUNT(party),
        .party = party,
    };
    u32 singlesMoney = CalculateTrainerPartyMoney(&trainer, 1, FALSE, FALSE);

    EXPECT_EQ(CalculateTrainerPartyMoney(&trainer, 1, TRUE, FALSE), 2 * singlesMoney);
    EXPECT_EQ(CalculateTrainerPartyMoney(&trainer, 1, TRUE, TRUE), singlesMoney);
    EXPECT_EQ(CalculateTrainerPartyMoney(&trainer, 3, FALSE, FALSE), 3 * singlesMoney);
}
