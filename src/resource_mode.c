#include "global.h"
#include "event_data.h"
#include "config/resource_mode.h"
#include "constants/flags.h"
#include "constants/vars.h"

static u16 GetStartingMoveServicePoints(void)
{
    if (VarGet(VAR_MONOTYPE) != 0)
        return RESOURCE_MODE_MONOTYPE_BASE_POINTS;

    return RESOURCE_MODE_BASE_POINTS;
}

static u16 GetMoveServicePointsPerBadge(void)
{
    if (VarGet(VAR_MONOTYPE) != 0)
        return RESOURCE_MODE_MONOTYPE_POINTS_PER_BADGE;

    return RESOURCE_MODE_POINTS_PER_BADGE;
}

static u8 GetBadgeCount(void)
{
    u8 badgeCount = 0;

    for (u32 i = 0; i < NUM_BADGES; i++)
    {
        if (FlagGet(gBadgeFlags[i]))
            badgeCount++;
    }

    return badgeCount;
}

static u16 GetBadgeAffordanceThreshold(u8 badgeCount)
{
    if (badgeCount < RESOURCE_MODE_LATE_BADGE_START)
        return RESOURCE_MODE_EARLY_DEPLETION_REQUIRED;

    return badgeCount - RESOURCE_MODE_LATE_DEPLETION_OFFSET;
}

static void AwardMoveServicePoints(u16 varId, u8 badgeCount)
{
    u16 currentPoints = VarGet(varId);
    u16 pointsPerBadge = GetMoveServicePointsPerBadge();
    u16 noSpendPointsBeforeBadge = GetStartingMoveServicePoints()
                                 + (badgeCount - 1) * pointsPerBadge;
    u16 affordanceThreshold = GetBadgeAffordanceThreshold(badgeCount);

    VarSet(varId, currentPoints + pointsPerBadge);
    if (currentPoints + affordanceThreshold <= noSpendPointsBeforeBadge)
        VarSet(varId, VarGet(varId) + RESOURCE_MODE_AFFORDANCE_POINTS);
}

void InitializeMoveServicePoints(void)
{
    u16 startingPoints = GetStartingMoveServicePoints();

    VarSet(VAR_REMAINING_RELEARNER, startingPoints);
    VarSet(VAR_REMAINING_TUTOR, startingPoints);
}

void AwardMoveServicePointsForBadge(void)
{
    u8 badgeCount = GetBadgeCount();

    if (badgeCount == 0)
        return;

    AwardMoveServicePoints(VAR_REMAINING_RELEARNER, badgeCount);
    AwardMoveServicePoints(VAR_REMAINING_TUTOR, badgeCount);
}
