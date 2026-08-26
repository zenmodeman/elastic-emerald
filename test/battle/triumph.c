#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "test/battle.h"

AI_SINGLE_BATTLE_TEST("Zenmodeman: Triumph survives the complete trainer battle teardown")
{
    GIVEN {
        PLAYER(SPECIES_WINGULL) { Level(23); Moves(MOVE_WATER_GUN); }
        OPPONENT(SPECIES_CHATOT) { Level(20); HP(1); Moves(MOVE_SPLASH); }
        OPPONENT(SPECIES_CLAUNCHER) { Level(21); HP(1); Moves(MOVE_SPLASH); }
    } WHEN {
        TURN { MOVE(player, MOVE_WATER_GUN); EXPECT_SEND_OUT(opponent, 1); }
        TURN { MOVE(player, MOVE_WATER_GUN); }
    } THEN {
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_TRIUMPH), 1);
    }
}
