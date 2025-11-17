#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "caps.h"
#include "pokemon.h"

/*
if isHardCap is true, the level cap is for gaining experience; otherwise, it's for rare candies / exp candies
*/
u32 GetCurrentLevelCap(bool32 isHardCap)
{
    static const u32 sLevelCapFlagMap[][2] =
    {   
        {TRAINER_FLAGS_START + TRAINER_TIANA, 8},
        {TRAINER_FLAGS_START + TRAINER_GRUNT_PETALBURG_WOODS, 11},
        {TRAINER_FLAGS_START + TRAINER_DARREN, 13},
        {FLAG_BADGE01_GET, 15},
        {FLAG_BADGE02_GET, 19},
        {FLAG_RIVAL_112_DEFEATED, 23},
        {FLAG_BADGE03_GET, 26},
        {FLAG_BADGE04_GET, 33},
        {FLAG_BADGE05_GET, 36},
        {FLAG_BADGE06_GET, 42},
        {FLAG_BADGE07_GET, 50},
        {FLAG_BADGE08_GET, 58},
        {FLAG_IS_CHAMPION, 67},
    };

    u32 i;
    u32 candyCap;

    if (!FlagGet(FLAG_LEVEL_CAP)){
        return MAX_LEVEL;
    }


    for (i = 0; i < ARRAY_COUNT(sLevelCapFlagMap); i++)
    {
        if (!FlagGet(sLevelCapFlagMap[i][0])){
            candyCap = sLevelCapFlagMap[i][1];
            if (isHardCap){
                if (sLevelCapFlagMap[i][0] == FLAG_IS_CHAMPION){
                    //To DO: make this + 0 outside the Pokemon League map areas and make it +3 inside the map areas
                    return candyCap + 3;
                }
                return candyCap + 1;
            }
            return candyCap;
        }

    }

    // else if (B_LEVEL_CAP_TYPE == LEVEL_CAP_VARIABLE)
    // {
    //     return VarGet(B_LEVEL_CAP_VARIABLE);
    // }

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

u32 GetCurrentEVCap(void)
{

    static const u16 sEvCapFlagMap[][2] = {
        // Define EV caps for each milestone
        {FLAG_BADGE01_GET, 30},
        {FLAG_BADGE02_GET, 90},
        {FLAG_BADGE03_GET, 150},
        {FLAG_BADGE04_GET, 210},
        {FLAG_BADGE05_GET, 270},
        {FLAG_BADGE06_GET, 330},
        {FLAG_BADGE07_GET, 390},
        {FLAG_BADGE08_GET, 450},
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
