#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Zenmodeman: AI records Float Stone when Low Kick exposes its weight effect")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_LOW_KICK) == EFFECT_LOW_KICK);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_LOW_KICK); }
        OPPONENT(SPECIES_SNORLAX) { Item(ITEM_FLOAT_STONE); Moves(MOVE_TACKLE); }
    } WHEN {
        TURN { MOVE(player, MOVE_LOW_KICK); }
    } SCENE {
        HP_BAR(opponent);
    } THEN {
        EXPECT_EQ(gBattleHistory->itemEffects[B_POSITION_OPPONENT_LEFT], HOLD_EFFECT_FLOAT_STONE);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: AI records Eviolite when its defensive boost applies")
{
    GIVEN {
        ASSUME(GetMoveCategory(MOVE_TACKLE) == DAMAGE_CATEGORY_PHYSICAL);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_PORYGON2) { Item(ITEM_EVIOLITE); Moves(MOVE_TACKLE); }
    } WHEN {
        TURN { MOVE(player, MOVE_TACKLE); }
    } SCENE {
        HP_BAR(opponent);
    } THEN {
        EXPECT_EQ(gBattleHistory->itemEffects[B_POSITION_OPPONENT_LEFT], HOLD_EFFECT_EVIOLITE);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: AI records Assault Vest only when its special defense boost applies")
{
    GIVEN {
        ASSUME(GetMoveCategory(MOVE_WATER_GUN) == DAMAGE_CATEGORY_SPECIAL);
        PLAYER(SPECIES_SQUIRTLE) { Moves(MOVE_WATER_GUN); Speed(100); }
        OPPONENT(SPECIES_MACHOP) { Item(ITEM_ASSAULT_VEST); Moves(MOVE_TACKLE); Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_WATER_GUN); MOVE(opponent, MOVE_TACKLE); }
    } SCENE {
        HP_BAR(opponent);
        HP_BAR(player);
    } THEN {
        EXPECT_EQ(gBattleHistory->itemEffects[B_POSITION_OPPONENT_LEFT], HOLD_EFFECT_ASSAULT_VEST);
    }
}
