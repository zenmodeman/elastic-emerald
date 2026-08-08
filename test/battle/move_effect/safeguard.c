#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Zenmodeman: Safeguard lasts four more turns when used before an opponent acts")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_SAFEGUARD) == EFFECT_SAFEGUARD);
        PLAYER(SPECIES_WOBBUFFET) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(50); }
    } WHEN {
        TURN { MOVE(player, MOVE_SAFEGUARD); MOVE(opponent, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(gSideTimers[B_SIDE_PLAYER].safeguardTimer, 4);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Safeguard gains a turn when used after all opponents have acted")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_SAFEGUARD) == EFFECT_SAFEGUARD);
        PLAYER(SPECIES_WOBBUFFET) { Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(50); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_SAFEGUARD); }
    } THEN {
        EXPECT_EQ(gSideTimers[B_SIDE_OPPONENT].safeguardTimer, 5);
    }
}
