#include "global.h"
#include "test/battle.h"

ASSUMPTIONS{
    ASSUME(GetMoveEffect(MOVE_WATER_SPORT) == EFFECT_WATER_SPORT);
}
SINGLE_BATTLE_TEST("Zenmodeman: Water Sport prevents burn from Will-o-Wisp")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_WILL_O_WISP) == EFFECT_WILL_O_WISP);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_WATER_SPORT); }
        TURN { MOVE(player, MOVE_WILL_O_WISP); }
        TURN { MOVE(player, MOVE_SWORDS_DANCE); }
    } SCENE {
        NOT STATUS_ICON(opponent, burn: TRUE);

        //This is solely to confirm that Will-o-Wisp against Water Sport did not freeze the game, which happened in the past
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SWORDS_DANCE, player); 
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Water Sport prevents burn from Fire-type secondary effects")
{
    GIVEN{
        ASSUME(MoveHasAdditionalEffectWithChance(MOVE_INFERNO, MOVE_EFFECT_BURN, 100));
        PLAYER(SPECIES_WOBBUFFET); 
        OPPONENT(SPECIES_WOBBUFFET);
    }WHEN {
        TURN { MOVE(player, MOVE_WATER_SPORT); }
        TURN { MOVE(opponent, MOVE_INFERNO); }
    } SCENE {
        NOT STATUS_ICON(player, burn: TRUE);
    }
}

