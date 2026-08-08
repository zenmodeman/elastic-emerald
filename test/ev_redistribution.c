#include "global.h"
#include "event_data.h"
#include "pokemon_summary_screen.h"
#include "test/test.h"

static void EnableEvMode(void)
{
    FlagSet(FLAG_EV_MODE);
}

TEST("Zenmodeman: EV redistribution accepts a conserved spread within the current stat cap")
{
    const u8 evs[NUM_STATS] = {36, 36, 0, 0, 0, 0};

    EnableEvMode();
    EXPECT(IsValidEvRedistribution(evs, 72));
}

TEST("Zenmodeman: EV redistribution rejects creation or loss of EVs")
{
    const u8 evs[NUM_STATS] = {36, 32, 0, 0, 0, 0};

    EnableEvMode();
    EXPECT(!IsValidEvRedistribution(evs, 72));
    EXPECT(!IsValidEvRedistribution(evs, 64));
}

TEST("Zenmodeman: EV redistribution enforces the current badge based per stat cap")
{
    const u8 evs[NUM_STATS] = {40, 32, 0, 0, 0, 0};

    EnableEvMode();
    EXPECT(!IsValidEvRedistribution(evs, 72));

    FlagSet(FLAG_BADGE01_GET);
    EXPECT(IsValidEvRedistribution(evs, 72));
}

TEST("Zenmodeman: EV redistribution rejects all positive EVs when EV Mode is disabled")
{
    const u8 evs[NUM_STATS] = {4, 0, 0, 0, 0, 0};

    EXPECT(!IsValidEvRedistribution(evs, 4));
}
