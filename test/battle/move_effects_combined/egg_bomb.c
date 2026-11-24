#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Elastic-tests: Egg Bomb lowers Defense by one stage and Serene Grace doubles its chance")
{
    enum Ability ability;
    u32 chance;

    PARAMETRIZE { ability = ABILITY_NATURAL_CURE; chance = 50; }
    PARAMETRIZE { ability = ABILITY_SERENE_GRACE; chance = 100; }
    PASSES_RANDOMLY(chance, 100, RNG_SECONDARY_EFFECT);

    GIVEN {
        PLAYER(SPECIES_CHANSEY) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_EGG_BOMB); }
    } SCENE {
        MESSAGE("The opposing Wobbuffet's Defense fell!");
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_DEF], DEFAULT_STAT_STAGE - 1);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Egg Bomb's critical-hit stage stacks with Chansey's Lucky Punch")
{
    enum Item item;
    u32 odds;

    PARAMETRIZE { item = ITEM_NONE; odds = 8; }
    PARAMETRIZE { item = ITEM_LUCKY_PUNCH; odds = 1; }
    PASSES_RANDOMLY(1, odds, RNG_CRITICAL_HIT);

    GIVEN {
        WITH_CONFIG(B_CRIT_CHANCE, GEN_9);
        PLAYER(SPECIES_CHANSEY) { Item(item); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_EGG_BOMB); }
    } SCENE {
        MESSAGE("A critical hit!");
    }
}
