#include "global.h"
#include "constants/event_objects.h"
#include "overworld.h"
#include "test/test.h"

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
