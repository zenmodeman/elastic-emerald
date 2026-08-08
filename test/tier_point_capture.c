#include "global.h"
#include "event_data.h"
#include "pokemon.h"
#include "test/test.h"

static void CreateTierPointCaptureFixture(struct Pokemon *caughtMon)
{
    u32 i;

    ZeroPlayerPartyMons();
    for (i = 0; i < 3; i++)
        CreateMon(&gParties[B_TRAINER_PLAYER][i], SPECIES_CHANSEY, 20, 0, OTID_STRUCT_PLAYER_ID);
    CreateMon(caughtMon, SPECIES_VULPIX, 20, 0, OTID_STRUCT_PLAYER_ID);
}

TEST("Zenmodeman: Tier Point capture projects the caught Pokemon against the current party")
{
    struct Pokemon caughtMon;

    CreateTierPointCaptureFixture(&caughtMon);
    FlagSet(FLAG_TIERED);
    EXPECT_EQ(CountPartyTierPoints(), 18);
    EXPECT_EQ(GetMonTierPoints(&caughtMon), 3);
    EXPECT_EQ(GetPartyTierPointExcessWithMon(&caughtMon), 1);
}

TEST("Zenmodeman: Tier Point capture has no excess at or below the cap")
{
    struct Pokemon caughtMon;

    CreateTierPointCaptureFixture(&caughtMon);
    ZeroMonData(&gParties[B_TRAINER_PLAYER][2]);
    FlagSet(FLAG_TIERED);
    EXPECT_EQ(GetPartyTierPointExcessWithMon(&caughtMon), 0);
}

TEST("Zenmodeman: Tier Point capture projection is disabled outside Tiered Mode")
{
    struct Pokemon caughtMon;

    CreateTierPointCaptureFixture(&caughtMon);
    EXPECT_EQ(GetPartyTierPointExcessWithMon(&caughtMon), 0);
}

TEST("Zenmodeman: Tier Point capture projection does not mutate either Pokemon collection")
{
    struct Pokemon caughtMon;
    u16 caughtSpecies;

    CreateTierPointCaptureFixture(&caughtMon);
    FlagSet(FLAG_TIERED);
    caughtSpecies = GetMonData(&caughtMon, MON_DATA_SPECIES);
    EXPECT_EQ(GetPartyTierPointExcessWithMon(&caughtMon), 1);
    EXPECT_EQ(CalculatePlayerPartyCount(), 3);
    EXPECT_EQ(GetMonData(&caughtMon, MON_DATA_SPECIES), caughtSpecies);
}
