#include "global.h"
#include "battle_setup.h"
#include "time_events.h"
#include "event_data.h"
#include "field_weather.h"
#include "pokemon.h"
#include "random.h"
#include "overworld.h"
#include "rtc.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "task.h"
#include "constants/event_objects.h"
#include "constants/items.h"
#include "constants/species.h"
#include "constants/vars.h"

static u16 ChooseMirageIslandEncounterSpecies(void);

static u32 GetMirageRnd(void)
{
    u32 hi = VarGet(VAR_MIRAGE_RND_H);
    u32 lo = VarGet(VAR_MIRAGE_RND_L);
    return (hi << 16) | lo;
}

static void SetMirageRnd(u32 rnd)
{
    VarSet(VAR_MIRAGE_RND_H, rnd >> 16);
    VarSet(VAR_MIRAGE_RND_L, rnd);
}

// unused
void InitMirageRnd(void)
{
    SetMirageRnd(Random32());
}

void UpdateMirageRnd(u16 days)
{
    u16 daysPassed = days;
    s32 rnd = GetMirageRnd();
    while (days)
    {
        rnd = ISO_RANDOMIZE2(rnd);
        days--;
    }
    SetMirageRnd(rnd);
    VarSet(VAR_MIRAGE_ISLAND_SPECIES, ChooseMirageIslandEncounterSpecies());
    VarSet(VAR_MIRAGE_ISLAND_ROLL_DAY, VarGet(VAR_DAYS) + daysPassed + 1);
}

bool8 IsMirageIslandPresent(void)
{
    return FlagGet(FLAG_MIRAGE_ISLAND_UNLOCKED);
}

// This is the single eligibility list for Mirage Island. Add explicit exclusions
// here if an otherwise-valid species receives a dedicated encounter elsewhere.
static bool32 IsMirageIslandEncounterSpecies(u16 species, enum Type monotype)
{
    const struct SpeciesInfo *speciesInfo = &gSpeciesInfo[species];
    u32 baseStatTotal;

    // Only offer each Pokédex species' canonical form. This excludes Mega,
    // Primal, regional, and battle-only forms without maintaining a second list.
    if (NationalPokedexNumToSpecies(speciesInfo->natDexNum) != species)
        return FALSE;

    if (!(speciesInfo->isRestrictedLegendary
       || speciesInfo->isSubLegendary
       || speciesInfo->isMythical
       || speciesInfo->isUltraBeast
       || speciesInfo->isParadox))
        return FALSE;

    baseStatTotal = speciesInfo->baseHP
                  + speciesInfo->baseAttack
                  + speciesInfo->baseDefense
                  + speciesInfo->baseSpeed
                  + speciesInfo->baseSpAttack
                  + speciesInfo->baseSpDefense;
    if (baseStatTotal < 550 || baseStatTotal > 600)
        return FALSE;

    if (monotype != TYPE_NONE
     && speciesInfo->types[0] != monotype
     && speciesInfo->types[1] != monotype)
        return FALSE;

    return TRUE;
}

static u16 ChooseMirageIslandEncounterSpecies(void)
{
    enum Type monotype = GetMonoType();
    u16 species;
    u16 eligibleCount = 0;
    u16 selectedIndex;

    for (species = 1; species < NUM_SPECIES; species++)
        if (IsMirageIslandEncounterSpecies(species, monotype))
            eligibleCount++;

    if (eligibleCount == 0)
        return SPECIES_NONE;

    selectedIndex = GetMirageRnd() % eligibleCount;
    for (species = 1; species < NUM_SPECIES; species++)
    {
        if (IsMirageIslandEncounterSpecies(species, monotype) && selectedIndex-- == 0)
            return species;
    }

    return SPECIES_NONE;
}

void PrepareMirageIslandEncounter(void)
{
    u16 dayMarker = VarGet(VAR_DAYS) + 1;
    u16 species = VarGet(VAR_MIRAGE_ISLAND_SPECIES);

    if (VarGet(VAR_MIRAGE_ISLAND_ROLL_DAY) != dayMarker || species == SPECIES_NONE)
    {
        species = ChooseMirageIslandEncounterSpecies();
        VarSet(VAR_MIRAGE_ISLAND_SPECIES, species);
        VarSet(VAR_MIRAGE_ISLAND_ROLL_DAY, dayMarker);
    }

    if (species == SPECIES_NONE || VarGet(VAR_MIRAGE_ISLAND_ENCOUNTER_DAY) == dayMarker)
    {
        gSpecialVar_Result = FALSE;
        return;
    }

    VarSet(VAR_OBJ_GFX_ID_0, OBJ_EVENT_MON + species);
    gSpecialVar_Result = TRUE;
}

void StartMirageIslandEncounter(void)
{
    CreateScriptedWildMon(VarGet(VAR_MIRAGE_ISLAND_SPECIES), 50, ITEM_NONE);
    BattleSetup_StartLegendaryBattle();
}

void UpdateShoalTideFlag(void)
{
    static const u8 tide[] =
    {
        1, // 00
        1, // 01
        1, // 02
        0, // 03
        0, // 04
        0, // 05
        0, // 06
        0, // 07
        0, // 08
        1, // 09
        1, // 10
        1, // 11
        1, // 12
        1, // 13
        1, // 14
        0, // 15
        0, // 16
        0, // 17
        0, // 18
        0, // 19
        0, // 20
        1, // 21
        1, // 22
        1, // 23
    };

    if (IsMapTypeOutdoors(GetLastUsedWarpMapType()))
    {
        RtcCalcLocalTime();
        if (tide[gLocalTime.hours])
            FlagSet(FLAG_SYS_SHOAL_TIDE);
        else
            FlagClear(FLAG_SYS_SHOAL_TIDE);
    }
}

static void Task_WaitWeather(u8 taskId)
{
    if (IsWeatherChangeComplete())
    {
        ScriptContext_Enable();
        DestroyTask(taskId);
    }
}

void WaitWeather(void)
{
    CreateTask(Task_WaitWeather, 80);
}

void InitBirchState(void)
{
    *GetVarPointer(VAR_BIRCH_STATE) = 0;
}

void UpdateBirchState(u16 days)
{
    u16 *state = GetVarPointer(VAR_BIRCH_STATE);
    *state += days;
    *state %= 7;
}
