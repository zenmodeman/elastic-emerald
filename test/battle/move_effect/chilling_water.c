#include "global.h"
#include "test/battle.h"

ASSUMPTIONS {
    ASSUME(GetMoveEffect(MOVE_CHILLING_WATER) == EFFECT_HIT);
    ASSUME(GetMoveType(MOVE_CHILLING_WATER) == TYPE_WATER);
    ASSUME(GetSpeciesType(SPECIES_GLALIE, 0) == TYPE_ICE);
    ASSUME(GetSpeciesType(SPECIES_GLALIE, 1) == TYPE_ICE);
}

SINGLE_BATTLE_TEST("Zenmodeman: Chilling Water is 50 percent stronger when used by an Ice type")
{
    s16 damage[2];

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_GLALIE);
    } WHEN {
        TURN { MOVE(player, MOVE_CHILLING_WATER); }
        TURN { MOVE(player, MOVE_REFLECT_TYPE); }
        TURN { MOVE(player, MOVE_CHILLING_WATER); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CHILLING_WATER, player);
        HP_BAR(opponent, captureDamage: &damage[0]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_REFLECT_TYPE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CHILLING_WATER, player);
        HP_BAR(opponent, captureDamage: &damage[1]);
    } THEN {
        EXPECT_MUL_EQ(damage[0], UQ_4_12(1.5), damage[1]);
    }
}
