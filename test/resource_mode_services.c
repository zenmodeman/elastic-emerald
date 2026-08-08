#include "global.h"
#include "config/resource_mode.h"
#include "event_data.h"
#include "test/test.h"

void InitializeMoveServicePoints(void);
void AwardMoveServicePointsForBadge(void);

static void SetBadgeCount(u32 count)
{
    for (u32 i = 0; i < count; i++)
        FlagSet(gBadgeFlags[i]);
}

TEST("Zenmodeman: Move services: normal teams start with the base tutor and relearner points")
{
    InitializeMoveServicePoints();
    EXPECT_EQ(VarGet(VAR_REMAINING_RELEARNER), RESOURCE_MODE_BASE_POINTS);
    EXPECT_EQ(VarGet(VAR_REMAINING_TUTOR), RESOURCE_MODE_BASE_POINTS);
}

TEST("Zenmodeman: Move services: monotype teams receive the larger starting allowance")
{
    VarSet(VAR_MONOTYPE, TYPE_FIRE);
    InitializeMoveServicePoints();
    EXPECT_EQ(VarGet(VAR_REMAINING_RELEARNER), RESOURCE_MODE_MONOTYPE_BASE_POINTS);
    EXPECT_EQ(VarGet(VAR_REMAINING_TUTOR), RESOURCE_MODE_MONOTYPE_BASE_POINTS);
}

TEST("Zenmodeman: Move services: no points are awarded without a badge")
{
    VarSet(VAR_REMAINING_RELEARNER, 2);
    VarSet(VAR_REMAINING_TUTOR, 1);
    AwardMoveServicePointsForBadge();
    EXPECT_EQ(VarGet(VAR_REMAINING_RELEARNER), 2);
    EXPECT_EQ(VarGet(VAR_REMAINING_TUTOR), 1);
}

TEST("Zenmodeman: Move services: early badges add one point without assistance when unspent")
{
    SetBadgeCount(1);
    VarSet(VAR_REMAINING_RELEARNER, RESOURCE_MODE_BASE_POINTS);
    VarSet(VAR_REMAINING_TUTOR, RESOURCE_MODE_BASE_POINTS);
    AwardMoveServicePointsForBadge();
    EXPECT_EQ(VarGet(VAR_REMAINING_RELEARNER), RESOURCE_MODE_BASE_POINTS + 1);
    EXPECT_EQ(VarGet(VAR_REMAINING_TUTOR), RESOURCE_MODE_BASE_POINTS + 1);
}

TEST("Zenmodeman: Move services: early badges restore an extra point after depletion")
{
    SetBadgeCount(1);
    VarSet(VAR_REMAINING_RELEARNER, RESOURCE_MODE_BASE_POINTS - 1);
    VarSet(VAR_REMAINING_TUTOR, RESOURCE_MODE_BASE_POINTS - 1);
    AwardMoveServicePointsForBadge();
    EXPECT_EQ(VarGet(VAR_REMAINING_RELEARNER), RESOURCE_MODE_BASE_POINTS + 1);
    EXPECT_EQ(VarGet(VAR_REMAINING_TUTOR), RESOURCE_MODE_BASE_POINTS + 1);
}

TEST("Zenmodeman: Move services: late badges require increasing depletion for assistance")
{
    SetBadgeCount(5);
    VarSet(VAR_REMAINING_RELEARNER, 5);
    VarSet(VAR_REMAINING_TUTOR, 6);
    AwardMoveServicePointsForBadge();
    EXPECT_EQ(VarGet(VAR_REMAINING_RELEARNER), 7);
    EXPECT_EQ(VarGet(VAR_REMAINING_TUTOR), 7);
}

TEST("Zenmodeman: Move services: monotype badge awards use their larger increment")
{
    VarSet(VAR_MONOTYPE, TYPE_FIRE);
    SetBadgeCount(1);
    VarSet(VAR_REMAINING_RELEARNER, RESOURCE_MODE_MONOTYPE_BASE_POINTS);
    VarSet(VAR_REMAINING_TUTOR, RESOURCE_MODE_MONOTYPE_BASE_POINTS - 2);
    AwardMoveServicePointsForBadge();
    EXPECT_EQ(VarGet(VAR_REMAINING_RELEARNER), RESOURCE_MODE_MONOTYPE_BASE_POINTS + 2);
    EXPECT_EQ(VarGet(VAR_REMAINING_TUTOR), RESOURCE_MODE_MONOTYPE_BASE_POINTS + 1);
}

TEST("Zenmodeman: Move services: tutor and relearner assistance are calculated independently")
{
    SetBadgeCount(4);
    VarSet(VAR_REMAINING_RELEARNER, 5);
    VarSet(VAR_REMAINING_TUTOR, 6);
    AwardMoveServicePointsForBadge();
    EXPECT_EQ(VarGet(VAR_REMAINING_RELEARNER), 7);
    EXPECT_EQ(VarGet(VAR_REMAINING_TUTOR), 7);
}
