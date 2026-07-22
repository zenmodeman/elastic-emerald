#include "global.h"
#include "berry.h"
#include "clock.h"
#include "dewford_trend.h"
#include "event_data.h"
#include "field_specials.h"
#include "field_weather.h"
#include "lottery_corner.h"
#include "main.h"
#include "overworld.h"
#include "pokerus.h"
#include "random.h"
#include "rtc.h"
#include "time_events.h"
#include "tv.h"
#include "wallclock.h"
#include "constants/form_change_types.h"
#include "apricorn_tree.h"

#include "fake_rtc.h"

static void UpdatePerDay(struct Time *localTime);
static void UpdatePerMinute(struct Time *localTime);

void InitTimeBasedEvents(void)
{
    FlagSet(FLAG_SYS_CLOCK_SET);
    RtcCalcLocalTime();
    gSaveBlock2Ptr->lastBerryTreeUpdate = gLocalTime;
    VarSet(VAR_DAYS, gLocalTime.days);
}

void DoTimeBasedEvents(void)
{
    if (FlagGet(FLAG_SYS_CLOCK_SET) && !InPokemonCenter())
    {
        // DebugPrintf("This is inside of DoTimeBasedEvents");
        RtcCalcLocalTime();
        UpdatePerDay(&gLocalTime);
        UpdatePerMinute(&gLocalTime);
    }
}

void UpdateDailySeed(void)
{
    gSaveBlock1Ptr->dailySeed = Random32();
}

static void UpdatePerDay(struct Time *localTime)
{

    // DebugPrintf("At the start of UpdatePerDay");

    u16 *days = GetVarPointer(VAR_DAYS);
    u16 daysSince;

    // DebugPrintf("days: %d; localDays: %d", *days, localTime->days);
    if (*days != localTime->days && *days <= localTime->days)
    {
        daysSince = localTime->days - *days;
        // DebugPrintf("Inside of the change day block with daysSince: %d", daysSince);
        ClearDailyFlags();
        UpdateDailySeed();
        UpdateDewfordTrendPerDay(daysSince);
        UpdateTVShowsPerDay(daysSince);
        UpdateWeatherPerDay(daysSince);
        UpdatePartyPokerusTime(daysSince);
        UpdateMirageRnd(daysSince);
        UpdateBirchState(daysSince);
        UpdateFrontierManiac(daysSince);
        UpdateFrontierGambler(daysSince);
        SetShoalItemFlag(daysSince);
        SetRandomLotteryNumber(daysSince);
        UpdateDaysPassedSinceFormChange(daysSince);
        DailyResetApricornTrees();
        *days = localTime->days;
        DebugPrintf("Updating days to %d", *days);
    }
}

//Advances time by 8 hours to represent rest
void NpcAdvanceTime(void){
    FakeRtc_AdvanceTimeBy(0, 8, 0, 0);
}


static void UpdatePerMinute(struct Time *localTime)
{
    struct Time difference;
    int minutes;
    CalcTimeDifference(&difference, &gSaveBlock2Ptr->lastBerryTreeUpdate, localTime);
    minutes = 24 * 60 * difference.days + 60 * difference.hours + difference.minutes;
    
    //Hacky fix for weird negatives between rtc and real time.
    if (minutes < 0){
        gSaveBlock2Ptr->lastBerryTreeUpdate = *localTime;
    }
    // DebugPrintf("Berries local Time days: %d; minutes: %d", localTime->days, minutes);
    if (minutes != 0)
    {
        if (minutes >= 0)
        {
            BerryTreeTimeUpdate(minutes);
            gSaveBlock2Ptr->lastBerryTreeUpdate = *localTime;
        }
    }
}

void FormChangeTimeUpdate()
{
    s32 i;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        TryFormChange(&gParties[B_TRAINER_PLAYER][i], FORM_CHANGE_TIME_OF_DAY, B_TRAINER_PLAYER);
    }
}

static void ReturnFromStartWallClock(void)
{
    InitTimeBasedEvents();
    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

void StartWallClock(void)
{
    SetMainCallback2(CB2_StartWallClock);
    gMain.savedCallback = ReturnFromStartWallClock;
}
