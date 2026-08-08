#include "global.h"
#include "test/test.h"
#include "constants/battle_ai.h"

TEST("Zenmodeman: Smart Trainer composes prediction and imperfect information flags")
{
    EXPECT_EQ(AI_FLAG_SMART_TRAINER & AI_FLAG_PREDICTION, AI_FLAG_PREDICTION);
    EXPECT_EQ(AI_FLAG_SMART_TRAINER & AI_FLAG_ASSUMPTIONS, AI_FLAG_ASSUMPTIONS);
    EXPECT(AI_FLAG_SMART_TRAINER & AI_FLAG_SMART_SWITCHING);
    EXPECT(AI_FLAG_SMART_TRAINER & AI_FLAG_SMART_TERA);
}

TEST("Zenmodeman: Smart Trainer excludes omniscience and upstream PP stall prevention")
{
    EXPECT(!(AI_FLAG_SMART_TRAINER & AI_FLAG_OMNISCIENT));
    EXPECT(!(AI_FLAG_SMART_TRAINER & AI_FLAG_PP_STALL_PREVENTION));
}
