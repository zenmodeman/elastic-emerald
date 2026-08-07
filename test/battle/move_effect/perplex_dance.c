#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveEffect(MOVE_PERPLEX_DANCE) == EFFECT_PERPLEX_DANCE);
    ASSUME(GetMovePP(MOVE_PERPLEX_DANCE) == GetMovePP(MOVE_TEETER_DANCE));
    ASSUME(GetMovePriority(MOVE_PERPLEX_DANCE) == 1);
    ASSUME(GetMoveTarget(MOVE_PERPLEX_DANCE) == TARGET_SELECTED);
}

SINGLE_BATTLE_TEST("Zenmodeman: Perplex Dance lowers both offenses and confuses its user")
{
    GIVEN {
        PLAYER(SPECIES_SPINDA) { Ability(ABILITY_TANGLED_FEET); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PERPLEX_DANCE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PERPLEX_DANCE, player);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_CONFUSION, player);
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_ATK], DEFAULT_STAT_STAGE - 2);
        EXPECT_EQ(opponent->statStages[STAT_SPATK], DEFAULT_STAT_STAGE - 2);
        EXPECT_GT(player->volatiles.confusionTurns, 0);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Own Tempo prevents Perplex Dance self-confusion after its debuffs")
{
    GIVEN {
        PLAYER(SPECIES_SPINDA) { Ability(ABILITY_OWN_TEMPO); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PERPLEX_DANCE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PERPLEX_DANCE, player);
        ABILITY_POPUP(player, ABILITY_OWN_TEMPO);
        NOT ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_CONFUSION, player);
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_ATK], DEFAULT_STAT_STAGE - 2);
        EXPECT_EQ(opponent->statStages[STAT_SPATK], DEFAULT_STAT_STAGE - 2);
        EXPECT_EQ(player->volatiles.confusionTurns, 0);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Perplex Dance acts at plus one priority")
{
    GIVEN {
        PLAYER(SPECIES_SPINDA) { Ability(ABILITY_OWN_TEMPO); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_PERPLEX_DANCE); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PERPLEX_DANCE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
    }
}
