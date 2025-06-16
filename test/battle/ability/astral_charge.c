#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(!IsBattleMoveStatus(MOVE_FAIRY_WIND));
    ASSUME(!IsBattleMoveStatus(MOVE_PSYSHOCK));
    ASSUME(!IsBattleMoveStatus(MOVE_TACKLE));
    ASSUME(GetMoveType(MOVE_FAIRY_WIND) == TYPE_FAIRY);
    ASSUME(GetMoveType(MOVE_PSYSHOCK) == TYPE_PSYCHIC);
    ASSUME(GetMoveType(MOVE_TACKLE) == TYPE_NORMAL);
}

SINGLE_BATTLE_TEST("Zenmodeman: Astral Charge raises Sp. Attack by 1 when hit by a Fairy or Psychic-type attack")
{
    u16 move;

    PARAMETRIZE { move = MOVE_FAIRY_WIND; }
    PARAMETRIZE { move = MOVE_PSYSHOCK; }
    PARAMETRIZE { move = MOVE_TACKLE; }

    GIVEN {
        PLAYER(SPECIES_ESPEON) { Ability(ABILITY_ASTRAL_CHARGE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, opponent);
        HP_BAR(player);
        if (move == MOVE_FAIRY_WIND || move == MOVE_PSYSHOCK) {
            ABILITY_POPUP(player, ABILITY_ASTRAL_CHARGE);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        } else {
            NONE_OF {
                ABILITY_POPUP(player, ABILITY_ASTRAL_CHARGE);
                ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
            }
        }
    } THEN {
        if (move == MOVE_FAIRY_WIND || move == MOVE_PSYSHOCK) {
            EXPECT_EQ(player->statStages[STAT_SPATK], DEFAULT_STAT_STAGE + 1);
        } else {
            EXPECT_EQ(player->statStages[STAT_SPATK], DEFAULT_STAT_STAGE);
        }
    }
}
