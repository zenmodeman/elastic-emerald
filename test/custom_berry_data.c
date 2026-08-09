#include "global.h"
#include "berry.h"
#include "constants/berry.h"
#include "test/test.h"

static void ExpectBerryYield(enum BerryId id, u8 minYield, u8 maxYield)
{
    EXPECT_EQ((u32)GetBerryInfo(id)->minYield, minYield);
    EXPECT_EQ((u32)GetBerryInfo(id)->maxYield, maxYield);
}

TEST("Zenmodeman: standard berries use the eight to twelve yield range")
{
    ExpectBerryYield(BERRY_ID_CHERI, 8, 12);
    ExpectBerryYield(BERRY_ID_PECHA, 8, 12);
    ExpectBerryYield(BERRY_ID_ORAN, 8, 12);
    ExpectBerryYield(BERRY_ID_LIECHI, 8, 12);
    ExpectBerryYield(BERRY_ID_LANSAT, 8, 12);
    ExpectBerryYield(BERRY_ID_ENIGMA, 8, 12);
}

TEST("Zenmodeman: pinch healing berries use the six to eight yield range")
{
    static const enum BerryId berries[] = {
        BERRY_ID_FIGY,
        BERRY_ID_WIKI,
        BERRY_ID_MAGO,
        BERRY_ID_AGUAV,
        BERRY_ID_IAPAPA,
    };
    u32 i;

    for (i = 0; i < ARRAY_COUNT(berries); i++)
        ExpectBerryYield(berries[i], 6, 8);
}

TEST("Zenmodeman: resistance berries use the three to four yield range")
{
    static const enum BerryId berries[] = {
        BERRY_ID_OCCA,
        BERRY_ID_PASSHO,
        BERRY_ID_WACAN,
        BERRY_ID_RINDO,
        BERRY_ID_YACHE,
        BERRY_ID_CHOPLE,
        BERRY_ID_KEBIA,
        BERRY_ID_SHUCA,
        BERRY_ID_COBA,
        BERRY_ID_PAYAPA,
        BERRY_ID_TANGA,
        BERRY_ID_CHARTI,
        BERRY_ID_KASIB,
        BERRY_ID_HABAN,
        BERRY_ID_COLBUR,
        BERRY_ID_BABIRI,
        BERRY_ID_CHILAN,
        BERRY_ID_ROSELI,
    };
    u32 i;

    for (i = 0; i < ARRAY_COUNT(berries); i++)
        ExpectBerryYield(berries[i], 3, 4);
}

TEST("Zenmodeman: special reactive berries use the four to six yield range")
{
    ExpectBerryYield(BERRY_ID_JABOCA, 4, 6);
    ExpectBerryYield(BERRY_ID_ROWAP, 4, 6);
    ExpectBerryYield(BERRY_ID_KEE, 4, 6);
    ExpectBerryYield(BERRY_ID_MARANGA, 4, 6);
}
