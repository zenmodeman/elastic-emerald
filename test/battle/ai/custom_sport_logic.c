#include "global.h"
#include "test/battle.h"
#include "battle_ai_main.h"

AI_SINGLE_BATTLE_TEST("Zenmodeman: Mud Sport is valued against a known Electric attack that is not resisted")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_VIABILITY | AI_FLAG_OMNISCIENT);
        PLAYER(SPECIES_PIKACHU) { Moves(MOVE_THUNDER_SHOCK); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_MUD_SPORT, MOVE_CELEBRATE); }
    } WHEN {
        TURN {
            SCORE_EQ_VAL(opponent, MOVE_MUD_SPORT, AI_SCORE_DEFAULT + DECENT_EFFECT);
            SCORE_EQ_VAL(opponent, MOVE_CELEBRATE, AI_SCORE_DEFAULT);
        }
    }
}

AI_SINGLE_BATTLE_TEST("Zenmodeman: Mud Sport receives no threat bonus when Electric is resisted")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_VIABILITY | AI_FLAG_OMNISCIENT);
        PLAYER(SPECIES_PIKACHU) { Moves(MOVE_THUNDER_SHOCK); }
        OPPONENT(SPECIES_QUAGSIRE) { Moves(MOVE_MUD_SPORT, MOVE_CELEBRATE); }
    } WHEN {
        TURN { SCORE_EQ_VAL(opponent, MOVE_MUD_SPORT, AI_SCORE_DEFAULT); }
    }
}

AI_SINGLE_BATTLE_TEST("Zenmodeman: Water Sport combines Fire protection with Damp pivot healing value")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_VIABILITY | AI_FLAG_OMNISCIENT);
        PLAYER(SPECIES_CHARMANDER) { Moves(MOVE_EMBER); Speed(10); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_DAMP); Moves(MOVE_WATER_SPORT, MOVE_FLIP_TURN); Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(50); }
    } WHEN {
        TURN { SCORE_EQ_VAL(opponent, MOVE_WATER_SPORT, AI_SCORE_DEFAULT + DECENT_EFFECT + WEAK_EFFECT); }
    }
}

AI_SINGLE_BATTLE_TEST("Zenmodeman: Damp adds pivot value after Water Sport is active")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_VIABILITY | AI_FLAG_OMNISCIENT);
        PLAYER(SPECIES_CHARMANDER) { Moves(MOVE_EMBER); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_DAMP); Moves(MOVE_WATER_SPORT, MOVE_FLIP_TURN); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_EMBER); EXPECT_MOVE(opponent, MOVE_WATER_SPORT); }
        TURN { SCORE_EQ_VAL(opponent, MOVE_FLIP_TURN, AI_SCORE_DEFAULT - BEST_EFFECT); }
    }
}
