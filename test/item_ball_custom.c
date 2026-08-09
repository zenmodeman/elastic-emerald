#include "global.h"
#include "event_data.h"
#include "item_ball.h"
#include "overworld.h"
#include "test/test.h"

static void ReadItemBallTemplate(enum Item item, u8 amount)
{
    static struct ObjectEventTemplate object;
    static struct MapEvents events;

    object = (struct ObjectEventTemplate) {
        .movementRangeX = amount,
        .trainerRange_berryTreeId = item,
    };
    events = (struct MapEvents) {
        .objectEventCount = 1,
        .objectEvents = &object,
    };
    gMapHeader.events = &events;
    gSpecialVar_LastTalked = 1;
    GetItemBallIdAndAmountFromTemplate();
}

TEST("Zenmodeman: Ground TMs yield one copy outside Resource Mode and retain encoded quantities within it")
{
    ReadItemBallTemplate(ITEM_TM_ROOST, 3);
    EXPECT_EQ(gSpecialVar_Result, ITEM_TM_ROOST);
    EXPECT_EQ(gSpecialVar_0x8009, 1);

    FlagSet(FLAG_RESOURCE_MODE);
    ReadItemBallTemplate(ITEM_TM_ROOST, 3);
    EXPECT_EQ(gSpecialVar_Result, ITEM_TM_ROOST);
    EXPECT_EQ(gSpecialVar_0x8009, 3);
}

TEST("Zenmodeman: Non-TM ground items retain encoded quantities outside Resource Mode")
{
    ReadItemBallTemplate(ITEM_POTION, 3);
    EXPECT_EQ(gSpecialVar_Result, ITEM_POTION);
    EXPECT_EQ(gSpecialVar_0x8009, 3);
}
