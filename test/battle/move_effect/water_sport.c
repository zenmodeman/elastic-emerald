#include "global.h"
#include "test/battle.h"

TO_DO_BATTLE_TEST("TODO: Write Water Sport (Move Effect) test titles")
#include "global.h"
#include "test/battle.h"

ASSUMPTIONS{
    ASSUME(GetMoveEffect(MOVE_WATER_SPORT) == EFFECT_WATER_SPORT);
}
SINGLE_BATTLE_TEST("Zenmodeman: Water Sport prevents burn from Will-o-Wisp")
{
    GIVEN {
        // ASSUME(GetMoveEffect(MOVE_WILL_O_WISP) == EFFECT_WILL_O_WISP); No longer valid after change to the effect
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


SINGLE_BATTLE_TEST("Water Sport reduces the damage of Fire Type moves by 67% (Gen5+)")
{
    s16 playerDmg[2];
    s16 opponentDmg[2];
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_FIRE_PLEDGE); MOVE(opponent, MOVE_FIRE_PLEDGE); }
        TURN { MOVE(player, MOVE_WATER_SPORT); }
        TURN { MOVE(player, MOVE_FIRE_PLEDGE); MOVE(opponent, MOVE_FIRE_PLEDGE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FIRE_PLEDGE, player);
        HP_BAR(opponent, captureDamage: &opponentDmg[0]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FIRE_PLEDGE, opponent);
        HP_BAR(player, captureDamage: &playerDmg[0]);

        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_SPORT, player);

        ANIMATION(ANIM_TYPE_MOVE, MOVE_FIRE_PLEDGE, player);
        HP_BAR(opponent, captureDamage: &opponentDmg[1]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FIRE_PLEDGE, opponent);
        HP_BAR(player, captureDamage: &playerDmg[1]);

    } THEN {
        EXPECT_MUL_EQ(opponentDmg[0], Q_4_12(0.33), opponentDmg[1]);
        EXPECT_MUL_EQ(playerDmg[0], Q_4_12(0.33), playerDmg[1]);
    }
}
