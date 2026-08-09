#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "caps.h"
#include "pokemon.h"

u32 GetCurrentLevelCap(bool32 isHardCap)
{
    static const u32 sLevelCapFlagMap[][2] =
    {   
        {TRAINER_FLAGS_START + TRAINER_TIANA, 8},
        {TRAINER_FLAGS_START + TRAINER_GRUNT_PETALBURG_WOODS, 11},
        {TRAINER_FLAGS_START + TRAINER_DARREN, 13},
        {FLAG_BADGE01_GET, 15},
        {FLAG_BADGE02_GET, 19},
        {FLAG_RIVAL_110_DEFEATED, 23},
        {FLAG_BADGE03_GET, 26},
        {FLAG_BADGE04_GET, 33},
        {FLAG_BADGE05_GET, 36},
        {FLAG_BADGE06_GET, 42},
        {FLAG_BADGE07_GET, 50},
        {FLAG_BADGE08_GET, 58},
        {FLAG_IS_CHAMPION, 70},
    };

    u32 i;

    (void)isHardCap;

    if (!FlagGet(FLAG_LEVEL_CAP))
        return MAX_LEVEL;

    for (i = 0; i < ARRAY_COUNT(sLevelCapFlagMap); i++)
    {
        if (!FlagGet(sLevelCapFlagMap[i][0]))
            return sLevelCapFlagMap[i][1];
    }

    // Expansion variable cap support can be restored here if needed.
    // if (B_LEVEL_CAP_TYPE == LEVEL_CAP_VARIABLE)
    //     return min(VarGet(B_LEVEL_CAP_VARIABLE), MAX_LEVEL);

    return MAX_LEVEL;
}

u32 GetSoftLevelCapExpValue(u32 level, u32 expValue)
{
    static const u32 sExpScalingDown[5] = { 4, 8, 16, 32, 64 };
    static const u32 sExpScalingUp[5]   = { 16, 8, 4, 2, 1 };

    u32 levelDifference;
    u32 currentLevelCap = GetCurrentLevelCap(HARD_CAP);

    if (B_EXP_CAP_TYPE == EXP_CAP_NONE)
        return expValue;

    if (level < currentLevelCap)
    {
        if (B_LEVEL_CAP_EXP_UP)
        {
            levelDifference = currentLevelCap - level;
            if (levelDifference > ARRAY_COUNT(sExpScalingUp) - 1)
                return expValue + (expValue / sExpScalingUp[ARRAY_COUNT(sExpScalingUp) - 1]);
            else
                return expValue + (expValue / sExpScalingUp[levelDifference]);
        }
        else
        {
            return expValue;
        }
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_HARD)
    {
        return 0;
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_SOFT)
    {
        levelDifference = level - currentLevelCap;
        if (levelDifference > ARRAY_COUNT(sExpScalingDown) - 1)
            return expValue / sExpScalingDown[ARRAY_COUNT(sExpScalingDown) - 1];
        else
            return expValue / sExpScalingDown[levelDifference];
    }
    else
    {
       return expValue;
    }
}

u32 GetSplitExpProgressionValue(u32 expValue, u32 participants, u32 badgeCount)
{
    if (participants <= 1 || badgeCount >= NUM_BADGES)
        return expValue;

    // At zero badges this is ordinary split Exp. Each badge shifts one
    // eighth of the reward from the shared portion into every participant's
    // personal reward, reaching full Exp after badge eight.
    return expValue * (badgeCount * participants + NUM_BADGES - badgeCount)
         / (NUM_BADGES * participants);
}

u32 GetCurrentEVCap(void)
{
    static const u16 sEvCapFlagMap[][2] = {
        // Define EV caps for each milestone
        {FLAG_BADGE01_GET, MAX_TOTAL_EVS *  1 / 17},
        {FLAG_BADGE02_GET, MAX_TOTAL_EVS *  3 / 17},
        {FLAG_BADGE03_GET, MAX_TOTAL_EVS *  5 / 17},
        {FLAG_BADGE04_GET, MAX_TOTAL_EVS *  7 / 17},
        {FLAG_BADGE05_GET, MAX_TOTAL_EVS *  9 / 17},
        {FLAG_BADGE06_GET, MAX_TOTAL_EVS * 11 / 17},
        {FLAG_BADGE07_GET, MAX_TOTAL_EVS * 13 / 17},
        {FLAG_BADGE08_GET, MAX_TOTAL_EVS * 15 / 17},
        {FLAG_IS_CHAMPION, MAX_TOTAL_EVS},
    };

    if (B_EV_CAP_TYPE == EV_CAP_FLAG_LIST)
    {
        for (u32 evCap = 0; evCap < ARRAY_COUNT(sEvCapFlagMap); evCap++)
        {
            if (!FlagGet(sEvCapFlagMap[evCap][0]))
                return sEvCapFlagMap[evCap][1];
        }
    }
    else if (B_EV_CAP_TYPE == EV_CAP_VARIABLE)
    {
        return VarGet(B_EV_CAP_VARIABLE);
    }
    else if (B_EV_CAP_TYPE == EV_CAP_NO_GAIN)
    {
        return 0;
    }

    return MAX_TOTAL_EVS;
}

u32 GetEVStatCap(void)
{
    if (!FlagGet(FLAG_EV_MODE))
        return 0;
    if (FlagGet(FLAG_BADGE07_GET))
        return MAX_PER_STAT_EVS;
    if (FlagGet(FLAG_BADGE06_GET))
        return 228;
    if (FlagGet(FLAG_BADGE05_GET))
        return 192;
    if (FlagGet(FLAG_BADGE04_GET))
        return 156;
    if (FlagGet(FLAG_BADGE03_GET))
        return 120;
    if (FlagGet(FLAG_BADGE02_GET))
        return 84;
    if (FlagGet(FLAG_BADGE01_GET))
        return 48;

    return 36;
}
