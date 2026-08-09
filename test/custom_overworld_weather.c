#include "global.h"
#include "battle.h"
#include "battle_util.h"
#include "constants/weather.h"
#include "field_weather.h"
#include "test/test.h"

TEST("Zenmodeman: diagonal fog does not create Misty Terrain at battle start")
{
    gWeatherPtr->currWeather = WEATHER_FOG_DIAGONAL;
    gFieldStatuses = 0;

    EXPECT(!TryFieldEffects(FIELD_EFFECT_OVERWORLD_TERRAIN));
    EXPECT(!(gFieldStatuses & STATUS_FIELD_MISTY_TERRAIN));
}
