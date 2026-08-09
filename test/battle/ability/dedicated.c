#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Zenmodeman: Dedicated extends screens by three turns", enum Move move)
{
    enum Move move;

    PARAMETRIZE { move = MOVE_REFLECT; }
    PARAMETRIZE { move = MOVE_LIGHT_SCREEN; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(100); }
        OPPONENT(SPECIES_CHIMECHO) { Ability(ABILITY_DEDICATED); Speed(50); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, move); }
    } THEN {
        if (move == MOVE_REFLECT)
            EXPECT_EQ(gSideTimers[B_SIDE_OPPONENT].reflectTimer, 7);
        else
            EXPECT_EQ(gSideTimers[B_SIDE_OPPONENT].lightscreenTimer, 7);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Dedicated extends weather and terrain by three turns", enum Move move)
{
    enum Move move;

    PARAMETRIZE { move = MOVE_RAIN_DANCE; }
    PARAMETRIZE { move = MOVE_ELECTRIC_TERRAIN; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(100); }
        OPPONENT(SPECIES_CHIMECHO) { Ability(ABILITY_DEDICATED); Speed(50); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, move); }
    } THEN {
        if (move == MOVE_RAIN_DANCE)
            EXPECT_EQ(gBattleStruct->weatherDuration, 7);
        else
            EXPECT_EQ(gFieldTimers.terrainTimer, 7);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Dedicated extends rooms and Tailwind by three turns", enum Move move)
{
    enum Move move;

    PARAMETRIZE { move = MOVE_TRICK_ROOM; }
    PARAMETRIZE { move = MOVE_TAILWIND; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(100); }
        OPPONENT(SPECIES_CHIMECHO) { Ability(ABILITY_DEDICATED); Speed(50); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, move); }
    } THEN {
        if (move == MOVE_TRICK_ROOM)
            EXPECT_EQ(gFieldTimers.trickRoomTimer, 7);
        else
            EXPECT_EQ(gSideTimers[B_SIDE_OPPONENT].tailwindTimer, 6);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Dedicated extends Mist Safeguard and sports by three turns", enum Move move)
{
    enum Move move;

    PARAMETRIZE { move = MOVE_MIST; }
    PARAMETRIZE { move = MOVE_SAFEGUARD; }
    PARAMETRIZE { move = MOVE_MUD_SPORT; }
    PARAMETRIZE { move = MOVE_WATER_SPORT; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(100); }
        OPPONENT(SPECIES_CHIMECHO) { Ability(ABILITY_DEDICATED); Speed(50); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, move); }
    } THEN {
        if (move == MOVE_MIST)
            EXPECT_EQ(gSideTimers[B_SIDE_OPPONENT].mistTimer, 7);
        else if (move == MOVE_SAFEGUARD)
            EXPECT_EQ(gSideTimers[B_SIDE_OPPONENT].safeguardTimer, 8);
        else if (move == MOVE_MUD_SPORT)
            EXPECT_EQ(gFieldTimers.mudSportTimer, 7);
        else
            EXPECT_EQ(gFieldTimers.waterSportTimer, 7);
    }
}
