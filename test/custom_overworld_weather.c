#include "global.h"
#include "battle.h"
#include "battle_util.h"
#include "constants/weather.h"
#include "field_weather.h"
#include "test/test.h"

TEST("Elastic-tests: diagonal fog does not create Misty Terrain at battle start")
{
    gWeatherPtr->currWeather = WEATHER_FOG_DIAGONAL;
    gFieldTimers.terrain = B_TERRAIN_NONE;

    EXPECT(!TryFieldEffects(FIELD_EFFECT_OVERWORLD_TERRAIN));
    EXPECT_EQ(gFieldTimers.terrain, B_TERRAIN_NONE);
}
