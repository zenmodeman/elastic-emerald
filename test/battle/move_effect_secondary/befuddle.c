#include "global.h"
#include "test/battle.h"

DOUBLE_BATTLE_TEST("Elastic-tests: Befuddle damages and inflicts paralysis, poison, or sleep on both foes")
{
    u32 moveEffect;
    u32 status;

    PARAMETRIZE { moveEffect = MOVE_EFFECT_PARALYSIS; status = STATUS1_PARALYSIS; }
    PARAMETRIZE { moveEffect = MOVE_EFFECT_POISON; status = STATUS1_POISON; }
    PARAMETRIZE { moveEffect = MOVE_EFFECT_SLEEP; status = STATUS1_SLEEP; }

    GIVEN {
        ASSUME(GetMovePower(MOVE_BEFUDDLE) == 70);
        ASSUME(GetMoveType(MOVE_BEFUDDLE) == TYPE_BUG);
        ASSUME(GetMoveCategory(MOVE_BEFUDDLE) == DAMAGE_CATEGORY_SPECIAL);
        ASSUME(GetMoveTarget(MOVE_BEFUDDLE) == TARGET_BOTH);
        ASSUME(MoveHasAdditionalEffectWithChance(MOVE_BEFUDDLE, MOVE_EFFECT_RANDOM_FROM_LIST, 100));
        PLAYER(SPECIES_BUTTERFREE);
        PLAYER(SPECIES_CATERPIE);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_BEFUDDLE, WITH_RNG(RNG_RANDOM_FROM_LIST, (moveEffect == MOVE_EFFECT_POISON ? 0 : moveEffect == MOVE_EFFECT_PARALYSIS ? 1 : 2))); }
    } SCENE {
        HP_BAR(opponentLeft);
        HP_BAR(opponentRight);
    } THEN {
        EXPECT(opponentLeft->status1 & status);
        EXPECT(opponentRight->status1 & status);
    }
}

DOUBLE_BATTLE_TEST("Elastic-tests: Protect blocks Befuddle's damage and status")
{
    GIVEN {
        ASSUME(GetMoveTarget(MOVE_BEFUDDLE) == TARGET_BOTH);
        PLAYER(SPECIES_BUTTERFREE);
        PLAYER(SPECIES_CATERPIE);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {
            MOVE(opponentLeft, MOVE_PROTECT);
            MOVE(playerLeft, MOVE_BEFUDDLE, WITH_RNG(RNG_RANDOM_FROM_LIST, 1));
        }
    } SCENE {
        NOT HP_BAR(opponentLeft);
        HP_BAR(opponentRight);
    } THEN {
        EXPECT_EQ(opponentLeft->status1, STATUS1_NONE);
        EXPECT_EQ(opponentRight->status1, STATUS1_PARALYSIS);
    }
}
