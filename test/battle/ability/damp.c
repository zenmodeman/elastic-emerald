#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Damp prevents Explosion-like moves from enemies")
{
    enum Move move;
    PARAMETRIZE { move = MOVE_EXPLOSION; }
    PARAMETRIZE { move = MOVE_SELF_DESTRUCT; }
    PARAMETRIZE { move = MOVE_MIND_BLOWN; }
    PARAMETRIZE { move = MOVE_MISTY_EXPLOSION; }
    GIVEN {
        PLAYER(SPECIES_PARAS) { Ability(ABILITY_DAMP); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, move); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_DAMP);
        NONE_OF { HP_BAR(player); HP_BAR(opponent); }
    }
}

DOUBLE_BATTLE_TEST("Damp prevents Explosion-like moves from enemies in a double battle")
{
    enum Move move;
    PARAMETRIZE { move = MOVE_EXPLOSION; }
    PARAMETRIZE { move = MOVE_SELF_DESTRUCT; }
    PARAMETRIZE { move = MOVE_MIND_BLOWN; }
    PARAMETRIZE { move = MOVE_MISTY_EXPLOSION; }
    GIVEN {
        PLAYER(SPECIES_PARAS) { Ability(ABILITY_DAMP); }
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponentLeft, move); }
    } SCENE {
        ABILITY_POPUP(playerLeft, ABILITY_DAMP);
        NONE_OF { HP_BAR(playerLeft); HP_BAR(opponentLeft); HP_BAR(playerRight); HP_BAR(opponentRight); }
    }
}

SINGLE_BATTLE_TEST("Damp prevents Explosion-like moves from self")
{
    enum Move move;
    PARAMETRIZE { move = MOVE_EXPLOSION; }
    PARAMETRIZE { move = MOVE_SELF_DESTRUCT; }
    PARAMETRIZE { move = MOVE_MIND_BLOWN; }
    PARAMETRIZE { move = MOVE_MISTY_EXPLOSION; }
    GIVEN {
        PLAYER(SPECIES_PARAS) { Ability(ABILITY_DAMP); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_DAMP);
        NONE_OF { HP_BAR(player); HP_BAR(opponent); }
    }
}

SINGLE_BATTLE_TEST("Damp prevents damage from Aftermath")
{
    GIVEN {
        ASSUME(MoveMakesContact(MOVE_SCRATCH));
        PLAYER(SPECIES_PARAS) { Ability(ABILITY_DAMP); }
        OPPONENT(SPECIES_VOLTORB) { Ability(ABILITY_AFTERMATH); HP(1); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); SEND_OUT(opponent, 1); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_AFTERMATH);
        ABILITY_POPUP(player, ABILITY_DAMP);
        NONE_OF { HP_BAR(player); }
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Damp heals one third HP when Water Sport creates moisture")
{
    GIVEN {
        PLAYER(SPECIES_PSYDUCK) { HP(30); MaxHP(90); Ability(ABILITY_DAMP); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_WATER_SPORT); }
    } THEN {
        EXPECT_EQ(player->hp, 60);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Damp moisture healing does not exceed maximum HP")
{
    GIVEN {
        PLAYER(SPECIES_PSYDUCK) { HP(90); MaxHP(90); Ability(ABILITY_DAMP); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_WATER_SPORT); }
    } SCENE {
        NOT ABILITY_POPUP(player, ABILITY_DAMP);
    } THEN {
        EXPECT_EQ(player->hp, 90);
    }
}

DOUBLE_BATTLE_TEST("Zenmodeman: Water Sport heals every damaged Damp battler")
{
    GIVEN {
        PLAYER(SPECIES_PSYDUCK) { HP(30); MaxHP(90); Ability(ABILITY_DAMP); }
        PLAYER(SPECIES_GOLDUCK) { HP(45); MaxHP(90); Ability(ABILITY_DAMP); }
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(opponentLeft, MOVE_WATER_SPORT); }
    } THEN {
        EXPECT_EQ(playerLeft->hp, 60);
        EXPECT_EQ(playerRight->hp, 75);
    }
}

//TO_DO_BATTLE_TEST("Damp affects non-adjacent Pokémon (triples)")
