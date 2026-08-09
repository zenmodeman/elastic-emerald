#include "global.h"
#include "berry.h"
#include "constants/berry.h"
#include "test/test.h"

TEST("Zenmodeman: slow and rare berries retain their custom Gen 3 yields")
{
    static const struct {
        enum BerryId id;
        u8 minYield;
        u8 maxYield;
    } yields[] = {
        {BERRY_ID_LUM,              2,  3},
        {BERRY_ID_SPELON,           2,  3},
        {BERRY_ID_PAMTRE,           2,  3},
        {BERRY_ID_WATMEL,           2,  3},
        {BERRY_ID_DURIN,            2,  3},
        {BERRY_ID_BELUE,            2,  3},
        {BERRY_ID_LIECHI,           2,  3},
        {BERRY_ID_GANLON,           2,  3},
        {BERRY_ID_SALAC,            2,  3},
        {BERRY_ID_PETAYA,           2,  3},
        {BERRY_ID_APICOT,           2,  3},
        {BERRY_ID_LANSAT,           4,  6},
        {BERRY_ID_STARF,            2,  3},
        {BERRY_ID_ENIGMA,           6, 10},
        {BERRY_ID_MICLE,            4,  6},
        {BERRY_ID_CUSTAP,           2,  3},
        {BERRY_ID_JABOCA,           2,  3},
        {BERRY_ID_ROWAP,            2,  3},
        {BERRY_ID_KEE,              3,  4},
        {BERRY_ID_MARANGA,          2,  3},
        {BERRY_ID_ENGIMA_E_READER,  2,  3},
    };
    u32 i;

    for (i = 0; i < ARRAY_COUNT(yields); i++)
    {
        EXPECT_EQ((u32)GetBerryInfo(yields[i].id)->minYield, yields[i].minYield);
        EXPECT_EQ((u32)GetBerryInfo(yields[i].id)->maxYield, yields[i].maxYield);
    }
}

TEST("Zenmodeman: common berries remain outside the rare-berry yield override")
{
    EXPECT_EQ((u32)GetBerryInfo(BERRY_ID_CHERI)->minYield, 2);
    EXPECT_EQ((u32)GetBerryInfo(BERRY_ID_CHERI)->maxYield, 3);
    EXPECT_EQ((u32)GetBerryInfo(BERRY_ID_ORAN)->minYield, 2);
    EXPECT_EQ((u32)GetBerryInfo(BERRY_ID_ORAN)->maxYield, 3);
}
