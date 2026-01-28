#include "global.h"
#include "test/battle.h"

TO_DO_BATTLE_TEST("TODO: Write Mud Sport (Move Effect) test titles")
#include "global.h"
#include "test/battle.h"

ASSUMPTIONS {
    ASSUME(GetMoveEffect(MOVE_MUD_SPORT) == EFFECT_MUD_SPORT);
}

SINGLE_BATTLE_TEST("Zenmodeman: Mud Sport prevents paralysis from Thunder Wave")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_THUNDER_WAVE) == EFFECT_PARALYZE);
        ASSUME(GetMoveEffect(MOVE_SWORDS_DANCE) == EFFECT_ATTACK_UP_2);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_MUD_SPORT); }
        TURN { MOVE(player, MOVE_THUNDER_WAVE); }
        TURN { MOVE(player, MOVE_SWORDS_DANCE); }
    } SCENE {
        NOT STATUS_ICON(opponent, paralysis: TRUE);

        //This is solely to confirm that Thunder Wave against Mud Sport did not freeze the game
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SWORDS_DANCE, player);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Mud Sport prevents paralysis from Electric-type secondary effects")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_MUD_SPORT) == EFFECT_MUD_SPORT);
        ASSUME(MoveHasAdditionalEffectWithChance(MOVE_NUZZLE, MOVE_EFFECT_PARALYSIS, 100));
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_MUD_SPORT); }
        TURN { MOVE(opponent, MOVE_NUZZLE); }
    } SCENE {
        NOT STATUS_ICON(player, paralysis: TRUE);
    }
}