#include "global.h"
#include "battle_setup.h"
#include "constants/battle_setup.h"
#include "event_scripts.h"
#include "test/test.h"

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
