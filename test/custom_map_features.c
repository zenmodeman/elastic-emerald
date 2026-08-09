#include "global.h"
#include "constants/event_objects.h"
#include "constants/event_bg.h"
#include "constants/weather.h"
#include "overworld.h"
#include "test/test.h"

extern const u8 RustboroCity_House1_EventScript_Trader[];
extern const u8 DewfordTown_EventScript_GoodRod_Fisherman[];
extern const u8 DewfordTown_OldManGifter[];
extern const u8 Route104_EventScript_BattleMayTreecko[];
extern const u8 Route104_EventScript_BattleBrendanTreecko[];
extern const u8 RustburoRival_GiveBottleCap[];
extern const u8 EventScript_CutTree[];
extern const u8 EventScript_AskScytherToCut[];
extern const u8 Common_EventScript_PkmnCenterTutor[];
extern const u8 DewfordTown_PokemonCenter_1F_EventScript_Maniac[];
extern const u8 TrainerSchool_Breeder[];
extern const u8 TrainerSchool_GiveEgg[];

static const struct ObjectEventTemplate *FindObjectByLocalId(const struct MapEvents *events, u8 localId)
{
    u32 i;

    for (i = 0; i < events->objectEventCount; i++)
    {
        if (events->objectEvents[i].localId == localId)
            return &events->objectEvents[i];
    }

    return NULL;
}

static const struct ObjectEventTemplate *FindItemBall(const struct MapEvents *events, enum Item item)
{
    u32 i;

    for (i = 0; i < events->objectEventCount; i++)
    {
        const struct ObjectEventTemplate *object = &events->objectEvents[i];

        if (object->graphicsId == OBJ_EVENT_GFX_ITEM_BALL
         && object->trainerRange_berryTreeId == item)
            return object;
    }

    return NULL;
}

static const struct ObjectEventTemplate *FindObjectByScript(const struct MapEvents *events, const u8 *script)
{
    u32 i;

    for (i = 0; i < events->objectEventCount; i++)
    {
        if (events->objectEvents[i].script == script)
            return &events->objectEvents[i];
    }

    return NULL;
}

static bool32 HasCoordTrigger(const struct MapEvents *events, s16 x, s16 y, u16 trigger, u16 index)
{
    u32 i;

    for (i = 0; i < events->coordEventCount; i++)
    {
        const struct CoordEvent *event = &events->coordEvents[i];

        if (event->x == x && event->y == y && event->trigger == trigger && event->index == index)
            return TRUE;
    }

    return FALSE;
}

static bool32 HasHiddenItem(const struct MapEvents *events, s16 x, s16 y, enum Item item, u16 flag)
{
    u32 i;

    for (i = 0; i < events->bgEventCount; i++)
    {
        const struct BgEvent *event = &events->bgEvents[i];

        if (event->kind == BG_EVENT_HIDDEN_ITEM
         && event->x == x
         && event->y == y
         && event->bgUnion.hiddenItem.item == item
         && event->bgUnion.hiddenItem.hiddenItemId + FLAG_HIDDEN_ITEMS_START == flag)
            return TRUE;
    }

    return FALSE;
}

static bool32 ScriptRangeContainsHalfword(const u8 *start, const u8 *end, u16 value)
{
    while (start + 1 < end)
    {
        if (start[0] == (value & 0xFF) && start[1] == (value >> 8))
            return TRUE;
        start++;
    }

    return FALSE;
}

static bool32 ScriptRangeContainsPointer(const u8 *start, const u8 *end, const u8 *target)
{
    uintptr_t value = (uintptr_t)target;

    while (start + 3 < end)
    {
        if (start[0] == (value & 0xFF)
         && start[1] == ((value >> 8) & 0xFF)
         && start[2] == ((value >> 16) & 0xFF)
         && start[3] == ((value >> 24) & 0xFF))
            return TRUE;
        start++;
    }

    return FALSE;
}

TEST("Zenmodeman: Oldale ride caller retains every approach trigger")
{
    static const s16 coords[][2] = {
        {10, 10}, {9, 10}, {8, 10}, {8, 7}, {11, 10},
        {12, 7}, {10, 11}, {9, 11}, {11, 11},
    };
    const struct MapEvents *events = Overworld_GetMapHeaderByGroupAndId(
        MAP_GROUP(MAP_OLDALE_TOWN), MAP_NUM(MAP_OLDALE_TOWN))->events;
    u32 i;

    for (i = 0; i < ARRAY_COUNT(coords); i++)
        EXPECT(HasCoordTrigger(events, coords[i][0], coords[i][1], VAR_OLDALE_TOWN_STATE, 1));
}

TEST("Zenmodeman: Oldale ride caller keeps its stable local id and interaction")
{
    const struct MapEvents *events = Overworld_GetMapHeaderByGroupAndId(
        MAP_GROUP(MAP_OLDALE_TOWN), MAP_NUM(MAP_OLDALE_TOWN))->events;
    const struct ObjectEventTemplate *rideCaller = FindObjectByLocalId(events, 11);

    EXPECT_NE(rideCaller, NULL);
    EXPECT_EQ(rideCaller->graphicsId, OBJ_EVENT_GFX_MYSTERY_GIFT_MAN);
    EXPECT_NE(rideCaller->script, NULL);
}

TEST("Zenmodeman: Petalburg Grove retains Birch and its ambient Pokemon")
{
    static const u16 expectedGraphics[] = {
        OBJ_EVENT_GFX_PROF_BIRCH,
        OBJ_EVENT_GFX_SPECIES(BULBASAUR),
        OBJ_EVENT_GFX_SPECIES(CHIKORITA),
        OBJ_EVENT_GFX_SPECIES(VULPIX),
    };
    const struct MapEvents *events = Overworld_GetMapHeaderByGroupAndId(
        MAP_GROUP(MAP_PETALBURG_GROVE), MAP_NUM(MAP_PETALBURG_GROVE))->events;
    u32 i;

    for (i = 0; i < ARRAY_COUNT(expectedGraphics); i++)
    {
        const struct ObjectEventTemplate *object = FindObjectByLocalId(events, i + 3);

        EXPECT_NE(object, NULL);
        EXPECT_EQ(object->graphicsId, expectedGraphics[i]);
    }

    EXPECT_EQ(FindObjectByLocalId(events, 3)->flagId, FLAG_HIDE_PETALBURG_GROVE_BIRCH);
}

TEST("Zenmodeman: Dewford Garden school kid retains the corrected placement and interaction")
{
    const struct MapEvents *events = Overworld_GetMapHeaderByGroupAndId(
        MAP_GROUP(MAP_DEWFORD_GARDEN), MAP_NUM(MAP_DEWFORD_GARDEN))->events;
    const struct ObjectEventTemplate *schoolKid = FindObjectByLocalId(events, 1);

    EXPECT_NE(schoolKid, NULL);
    EXPECT_EQ(schoolKid->graphicsId, OBJ_EVENT_GFX_SCHOOL_KID_M);
    EXPECT_EQ(schoolKid->x, 6);
    EXPECT_EQ(schoolKid->y, 12);
    EXPECT_NE(schoolKid->script, NULL);
}

TEST("Zenmodeman: Dewford Pokemon Center retains its tutor and Float Stone hint NPCs")
{
    const struct MapEvents *events = Overworld_GetMapHeaderByGroupAndId(
        MAP_GROUP(MAP_DEWFORD_TOWN_POKEMON_CENTER_1F), MAP_NUM(MAP_DEWFORD_TOWN_POKEMON_CENTER_1F))->events;
    const struct ObjectEventTemplate *tutor = FindObjectByScript(events, Common_EventScript_PkmnCenterTutor);
    const struct ObjectEventTemplate *maniac = FindObjectByScript(events, DewfordTown_PokemonCenter_1F_EventScript_Maniac);

    EXPECT_NE(tutor, NULL);
    EXPECT_EQ(tutor->graphicsId, OBJ_EVENT_GFX_WOMAN_3);
    EXPECT_EQ(tutor->x, 14);
    EXPECT_EQ(tutor->y, 2);
    EXPECT_EQ(tutor->script, Common_EventScript_PkmnCenterTutor);

    EXPECT_NE(maniac, NULL);
    EXPECT_EQ(maniac->graphicsId, OBJ_EVENT_GFX_MANIAC);
    EXPECT_EQ(maniac->x, 17);
    EXPECT_EQ(maniac->y, 8);
    EXPECT_EQ(maniac->script, DewfordTown_PokemonCenter_1F_EventScript_Maniac);
}

TEST("Zenmodeman: Granite Cave retains Steven's Tera Orb interaction object")
{
    const struct MapEvents *events = Overworld_GetMapHeaderByGroupAndId(
        MAP_GROUP(MAP_GRANITE_CAVE_STEVENS_ROOM), MAP_NUM(MAP_GRANITE_CAVE_STEVENS_ROOM))->events;
    const struct ObjectEventTemplate *steven = FindObjectByLocalId(events, LOCALID_GRANITE_CAVE_STEVEN);

    EXPECT_NE(steven, NULL);
    EXPECT_EQ(steven->graphicsId, OBJ_EVENT_GFX_STEVEN);
    EXPECT_EQ(steven->x, 7);
    EXPECT_EQ(steven->y, 8);
    EXPECT_EQ(steven->flagId, FLAG_HIDE_GRANITE_CAVE_STEVEN);
    EXPECT_NE(steven->script, NULL);
}

TEST("Zenmodeman: Granite Cave retains its custom Float Stone and Rock Gem item balls")
{
    const struct MapEvents *b1fEvents = Overworld_GetMapHeaderByGroupAndId(
        MAP_GROUP(MAP_GRANITE_CAVE_B1F), MAP_NUM(MAP_GRANITE_CAVE_B1F))->events;
    const struct MapEvents *stevenEvents = Overworld_GetMapHeaderByGroupAndId(
        MAP_GROUP(MAP_GRANITE_CAVE_STEVENS_ROOM), MAP_NUM(MAP_GRANITE_CAVE_STEVENS_ROOM))->events;
    const struct ObjectEventTemplate *floatStone = FindItemBall(b1fEvents, ITEM_FLOAT_STONE);
    const struct ObjectEventTemplate *rockGem = FindItemBall(stevenEvents, ITEM_ROCK_GEM);

    EXPECT_NE(floatStone, NULL);
    EXPECT_EQ(floatStone->x, 15);
    EXPECT_EQ(floatStone->y, 21);
    EXPECT_EQ(floatStone->flagId, FLAG_ITEM_GRANITE_CAVE_B1F_FLOAT_STONE);
    EXPECT_NE(rockGem, NULL);
    EXPECT_EQ(rockGem->x, 10);
    EXPECT_EQ(rockGem->y, 9);
    EXPECT_EQ(rockGem->flagId, FLAG_ITEM_GRANITE_ROCK_GEMS);
}

TEST("Zenmodeman: Granite Cave retains the three custom Black Belt encounters")
{
    static const s16 expectedCoords[][2] = {{5, 10}, {3, 10}, {4, 8}};
    const struct MapEvents *events = Overworld_GetMapHeaderByGroupAndId(
        MAP_GROUP(MAP_GRANITE_CAVE_1F), MAP_NUM(MAP_GRANITE_CAVE_1F))->events;
    u32 i;
    u32 found = 0;

    for (i = 0; i < events->objectEventCount; i++)
    {
        const struct ObjectEventTemplate *object = &events->objectEvents[i];
        u32 j;

        if (object->graphicsId != OBJ_EVENT_GFX_BLACK_BELT)
            continue;
        EXPECT_EQ(object->flagId, FLAG_HIDE_GRANITE_BLACK_BELTS);
        EXPECT_NE(object->script, NULL);
        for (j = 0; j < ARRAY_COUNT(expectedCoords); j++)
        {
            if (object->x == expectedCoords[j][0] && object->y == expectedCoords[j][1])
                found++;
        }
    }
    EXPECT_EQ(found, ARRAY_COUNT(expectedCoords));
}

TEST("Zenmodeman: Flannery's gym retains diagonal fog on both floors")
{
    const struct MapHeader *firstFloor = Overworld_GetMapHeaderByGroupAndId(
        MAP_GROUP(MAP_LAVARIDGE_TOWN_GYM_1F), MAP_NUM(MAP_LAVARIDGE_TOWN_GYM_1F));
    const struct MapHeader *basement = Overworld_GetMapHeaderByGroupAndId(
        MAP_GROUP(MAP_LAVARIDGE_TOWN_GYM_B1F), MAP_NUM(MAP_LAVARIDGE_TOWN_GYM_B1F));

    EXPECT_EQ(firstFloor->weather, WEATHER_FOG_DIAGONAL);
    EXPECT_EQ(basement->weather, WEATHER_FOG_DIAGONAL);
}

TEST("Zenmodeman: Route 104 rival branches retain their Bottle Cap reward call")
{
    EXPECT(ScriptRangeContainsPointer(
        Route104_EventScript_BattleMayTreecko,
        Route104_EventScript_BattleMayTreecko + 48,
        RustburoRival_GiveBottleCap));
    EXPECT(ScriptRangeContainsPointer(
        Route104_EventScript_BattleBrendanTreecko,
        Route104_EventScript_BattleBrendanTreecko + 48,
        RustburoRival_GiveBottleCap));
}

TEST("Zenmodeman: Cut retains its fallback to the custom Scyther interaction")
{
    EXPECT(ScriptRangeContainsPointer(
        EventScript_CutTree,
        EventScript_CutTree + 32,
        EventScript_AskScytherToCut));
}

TEST("Zenmodeman: Rustboro trade retains its compiled monotype guard")
{
    const struct MapEvents *events = Overworld_GetMapHeaderByGroupAndId(
        MAP_GROUP(MAP_RUSTBORO_CITY_HOUSE1), MAP_NUM(MAP_RUSTBORO_CITY_HOUSE1))->events;
    const struct ObjectEventTemplate *trader = FindObjectByLocalId(events, 1);

    EXPECT_NE(trader, NULL);
    EXPECT_EQ(trader->script, RustboroCity_House1_EventScript_Trader);
    EXPECT(ScriptRangeContainsHalfword(
        RustboroCity_House1_EventScript_Trader,
        RustboroCity_House1_EventScript_Trader + 24,
        VAR_MONOTYPE));
}

TEST("Zenmodeman: Dewford fisherman retains the Good Rod reward and completion flag")
{
    const struct MapEvents *events = Overworld_GetMapHeaderByGroupAndId(
        MAP_GROUP(MAP_DEWFORD_TOWN), MAP_NUM(MAP_DEWFORD_TOWN))->events;
    const struct ObjectEventTemplate *fisherman = FindObjectByLocalId(events, 3);

    EXPECT_NE(fisherman, NULL);
    EXPECT_EQ(fisherman->graphicsId, OBJ_EVENT_GFX_FISHERMAN);
    EXPECT_EQ(fisherman->script, DewfordTown_EventScript_GoodRod_Fisherman);
    EXPECT(ScriptRangeContainsHalfword(
        DewfordTown_EventScript_GoodRod_Fisherman,
        DewfordTown_EventScript_GoodRod_Fisherman + 80,
        ITEM_GOOD_ROD));
    EXPECT(ScriptRangeContainsHalfword(
        DewfordTown_EventScript_GoodRod_Fisherman,
        DewfordTown_EventScript_GoodRod_Fisherman + 80,
        FLAG_RECEIVED_GOOD_ROD));
}

TEST("Zenmodeman: Route 106 retains its custom hidden Dive Ball")
{
    const struct MapEvents *events = Overworld_GetMapHeaderByGroupAndId(
        MAP_GROUP(MAP_ROUTE106), MAP_NUM(MAP_ROUTE106))->events;

    EXPECT(HasHiddenItem(events, 41, 11, ITEM_DIVE_BALL, FLAG_HIDDEN_ITEM_ROUTE_106_DIVE_BALL));
}

TEST("Zenmodeman: Dewford old man retains the monotype-aware Delibird gift")
{
    const struct MapEvents *events = Overworld_GetMapHeaderByGroupAndId(
        MAP_GROUP(MAP_DEWFORD_TOWN_HOUSE2), MAP_NUM(MAP_DEWFORD_TOWN_HOUSE2))->events;
    const struct ObjectEventTemplate *oldMan = FindObjectByLocalId(events, 3);

    EXPECT_NE(oldMan, NULL);
    EXPECT_EQ(oldMan->graphicsId, OBJ_EVENT_GFX_OLD_MAN);
    EXPECT_EQ(oldMan->script, DewfordTown_OldManGifter);
    EXPECT(ScriptRangeContainsHalfword(DewfordTown_OldManGifter, DewfordTown_OldManGifter + 240, VAR_MONOTYPE));
    EXPECT(ScriptRangeContainsHalfword(DewfordTown_OldManGifter, DewfordTown_OldManGifter + 240, SPECIES_DELIBIRD));
    EXPECT(ScriptRangeContainsHalfword(DewfordTown_OldManGifter, DewfordTown_OldManGifter + 240, FLAG_DEWFORD_GIFT_MAN));
}

TEST("Zenmodeman: Trainer School breeder retains its monotype egg service")
{
    const struct MapEvents *events = Overworld_GetMapHeaderByGroupAndId(
        MAP_GROUP(MAP_RUSTBORO_CITY_POKEMON_SCHOOL), MAP_NUM(MAP_RUSTBORO_CITY_POKEMON_SCHOOL))->events;
    const struct ObjectEventTemplate *breeder = FindObjectByScript(events, TrainerSchool_Breeder);

    EXPECT_NE(breeder, NULL);
    EXPECT_EQ(breeder->graphicsId, OBJ_EVENT_GFX_GIRL_2);
    EXPECT(ScriptRangeContainsHalfword(TrainerSchool_Breeder, TrainerSchool_Breeder + 180, FLAG_RECEIVED_TRAINER_SCHOOL_EGG));
    EXPECT(ScriptRangeContainsHalfword(TrainerSchool_Breeder, TrainerSchool_Breeder + 180, VAR_MONOTYPE));
    EXPECT(ScriptRangeContainsHalfword(TrainerSchool_GiveEgg, TrainerSchool_GiveEgg + 180, SPECIES_IGGLYBUFF));
    EXPECT(ScriptRangeContainsHalfword(TrainerSchool_GiveEgg, TrainerSchool_GiveEgg + 180, SPECIES_TOXEL));
    EXPECT(ScriptRangeContainsHalfword(TrainerSchool_GiveEgg, TrainerSchool_GiveEgg + 180, SPECIES_SMOOCHUM));
    EXPECT(ScriptRangeContainsHalfword(TrainerSchool_GiveEgg, TrainerSchool_GiveEgg + 180, SPECIES_GLIGAR));
}
