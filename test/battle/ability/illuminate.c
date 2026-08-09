#include "global.h"
#include "test/battle.h"

DOUBLE_BATTLE_TEST("Zenmodeman: Illuminate spotlights its user after an illuminating move")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_VOLBEAT) { Ability(ABILITY_ILLUMINATE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponentLeft, MOVE_LIGHT_SCREEN); }
    } SCENE {
        ABILITY_POPUP(opponentLeft, ABILITY_ILLUMINATE);
    }
}

DOUBLE_BATTLE_TEST("Zenmodeman: Illuminate ignores moves outside the illuminating category")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_VOLBEAT) { Ability(ABILITY_ILLUMINATE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponentLeft, MOVE_REFLECT); }
    } SCENE {
        NOT ABILITY_POPUP(opponentLeft, ABILITY_ILLUMINATE);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Illuminate permits its own accuracy to be lowered")
{
    PASSES_RANDOMLY(75, 100, RNG_ACCURACY);
    GIVEN {
        ASSUME(GetMoveAccuracy(MOVE_SCRATCH) == 100);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_VOLBEAT) { Ability(ABILITY_ILLUMINATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_SAND_ATTACK); MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SAND_ATTACK, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Illuminate ignores evasion abilities")
{
    PASSES_RANDOMLY(100, 100, RNG_ACCURACY);
    GIVEN {
        ASSUME(GetMoveAccuracy(MOVE_POUND) == 100);
        PLAYER(SPECIES_SANDSHREW) { Ability(ABILITY_SAND_VEIL); }
        OPPONENT(SPECIES_VOLBEAT) { Ability(ABILITY_ILLUMINATE); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_SANDSTORM); }
        TURN { MOVE(opponent, MOVE_POUND); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POUND, opponent);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Illuminate ignores evasion items")
{
    PASSES_RANDOMLY(100, 100, RNG_ACCURACY);
    GIVEN {
        ASSUME(GetMoveAccuracy(MOVE_POUND) == 100);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_BRIGHTPOWDER); }
        OPPONENT(SPECIES_VOLBEAT) { Ability(ABILITY_ILLUMINATE); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_POUND); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POUND, opponent);
    }
}
