#include "global.h"
#include "event_data.h"
#include "field_move.h"
#include "test/test.h"

TEST("Zenmodeman: Flash remains usable without the Knuckle Badge while Cut stays badge gated")
{
    FlagClear(FLAG_BADGE01_GET);
    FlagClear(FLAG_BADGE02_GET);

    EXPECT(IsFieldMoveUnlocked(FIELD_MOVE_FLASH));
    EXPECT(!IsFieldMoveUnlocked(FIELD_MOVE_CUT));
}
