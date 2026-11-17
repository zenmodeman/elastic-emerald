#include "global.h"
#include "test/battle.h"
#include "battle_ai_util.h"

AI_SINGLE_BATTLE_TEST("Elastic-tests: fast-KO escapes are disabled below eighty percent HP")
{
    u32 hp;
    PARAMETRIZE { hp = 75; }
    PARAMETRIZE { hp = 79; }
    GIVEN {
        AI_FLAGS(AI_FLAG_BASIC_TRAINER | AI_FLAG_SMART_SWITCHING | AI_FLAG_ASSUME_STAB);
        PLAYER(SPECIES_MEWTWO) { Level(100); SpAttack(500); Speed(100); Moves(MOVE_CELEBRATE, MOVE_PSYCHIC); }
        OPPONENT(SPECIES_SNORLAX) { Level(100); HP(hp); MaxHP(100); SpDefense(200); Speed(1); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_TYRANITAR) { Speed(10); Moves(MOVE_CRUNCH); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); EXPECT_MOVE(opponent, MOVE_TACKLE); }
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: fast-KO escape includes the exact eighty percent boundary")
{
    PASSES_RANDOMLY(50, 100, RNG_AI_SWITCH_HASBADODDS);
    GIVEN {
        AI_FLAGS(AI_FLAG_BASIC_TRAINER | AI_FLAG_SMART_SWITCHING | AI_FLAG_ASSUME_STAB);
        PLAYER(SPECIES_MEWTWO) { Level(100); SpAttack(500); Speed(100); Moves(MOVE_CELEBRATE, MOVE_PSYCHIC); }
        OPPONENT(SPECIES_SNORLAX) { Level(100); HP(80); MaxHP(100); SpDefense(200); Speed(1); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_TYRANITAR) { Speed(10); Moves(MOVE_CRUNCH); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); EXPECT_SWITCH(opponent, 1); }
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: Regenerator fast-KO escape includes its exact full-heal boundary")
{
    PASSES_RANDOMLY(50, 100, RNG_AI_SWITCH_HASBADODDS);
    GIVEN {
        AI_FLAGS(AI_FLAG_BASIC_TRAINER | AI_FLAG_SMART_SWITCHING | AI_FLAG_ASSUME_STAB);
        PLAYER(SPECIES_MEWTWO) { Level(100); SpAttack(500); Speed(100); Moves(MOVE_CELEBRATE, MOVE_PSYCHIC); }
        OPPONENT(SPECIES_SNORLAX) { Level(100); HP(67); MaxHP(100); Ability(ABILITY_REGENERATOR); SpDefense(200); Speed(1); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_TYRANITAR) { Speed(10); Moves(MOVE_CRUNCH); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); EXPECT_SWITCH(opponent, 1); }
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: Regenerator does not escape a fast KO for partial healing")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_BASIC_TRAINER | AI_FLAG_SMART_SWITCHING | AI_FLAG_ASSUME_STAB);
        PLAYER(SPECIES_MEWTWO) { Level(100); SpAttack(500); Speed(100); Moves(MOVE_CELEBRATE, MOVE_PSYCHIC); }
        OPPONENT(SPECIES_SNORLAX) { Level(100); HP(68); MaxHP(100); Ability(ABILITY_REGENERATOR); SpDefense(200); Speed(1); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_TYRANITAR) { Speed(10); Moves(MOVE_CRUNCH); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); EXPECT_MOVE(opponent, MOVE_TACKLE); }
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: full-value Regenerator can escape a committed fast-KO matchup")
{
    PASSES_RANDOMLY(50, 100, RNG_AI_SWITCH_HASBADODDS);
    GIVEN {
        AI_FLAGS(AI_FLAG_BASIC_TRAINER | AI_FLAG_SMART_SWITCHING | AI_FLAG_ASSUME_STAB);
        PLAYER(SPECIES_SLAKING) { Level(100); Attack(200); Speed(120); Ability(ABILITY_VITAL_SPIRIT); Moves(MOVE_BULLDOZE, MOVE_DOUBLE_EDGE, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_SNORLAX) { Level(100); HP(200); MaxHP(200); Defense(100); Speed(150); Ability(ABILITY_REGENERATOR); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_TYRANITAR) { Speed(10); Level(100); HP(500); MaxHP(500); Defense(500); Moves(MOVE_CRUNCH); }
    } WHEN {
        TURN { MOVE(player, MOVE_BULLDOZE); EXPECT_MOVE(opponent, MOVE_TACKLE); }
        TURN { MOVE(player, MOVE_CELEBRATE); EXPECT_SWITCH(opponent, 1); }
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: ordinary commitment survives successful hits into Substitute")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_BASIC_TRAINER | AI_FLAG_SMART_SWITCHING | AI_FLAG_ASSUME_STAB);
        PLAYER(SPECIES_MEWTWO) { Level(100); HP(1000); MaxHP(1000); SpAttack(150); Speed(100); Moves(MOVE_SUBSTITUTE, MOVE_NASTY_PLOT, MOVE_PSYCHIC); }
        OPPONENT(SPECIES_SNORLAX) { Level(100); HP(200); MaxHP(200); SpDefense(200); Attack(1); Speed(1); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_TYRANITAR) { Speed(10); Moves(MOVE_CRUNCH); }
    } WHEN {
        TURN { MOVE(player, MOVE_SUBSTITUTE); EXPECT_MOVE(opponent, MOVE_TACKLE); }
        TURN { MOVE(player, MOVE_NASTY_PLOT); EXPECT_MOVE(opponent, MOVE_TACKLE); }
        TURN { MOVE(player, MOVE_NASTY_PLOT); EXPECT_MOVE(opponent, MOVE_TACKLE); }
    } THEN {
        EXPECT_EQ((u32)gBattleStruct->battlerState[GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT)].fastKoCommitted, TRUE);
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: fast-KO fallback rejects replacements that cannot survive until acting")
{
    u32 hp, speed;
    PARAMETRIZE { hp = 1; speed = 200; }
    PARAMETRIZE { hp = 170; speed = 1; }
    GIVEN {
        AI_FLAGS(AI_FLAG_BASIC_TRAINER | AI_FLAG_SMART_SWITCHING | AI_FLAG_ASSUME_STAB);
        PLAYER(SPECIES_MEWTWO) { Level(100); SpAttack(200); Speed(100); Moves(MOVE_CELEBRATE, MOVE_PSYCHIC); }
        OPPONENT(SPECIES_SNORLAX) { Level(100); HP(70); MaxHP(70); SpDefense(200); Speed(1); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_SNORLAX) { Level(100); HP(hp); MaxHP(200); SpDefense(200); Speed(speed); Moves(MOVE_TACKLE); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); EXPECT_MOVE(opponent, MOVE_TACKLE); }
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: fast-KO escapes reject hazard-lethal replacements")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_BASIC_TRAINER | AI_FLAG_SMART_SWITCHING | AI_FLAG_ASSUME_STAB);
        PLAYER(SPECIES_MEWTWO) { Level(100); Speed(100); Moves(MOVE_STEALTH_ROCK, MOVE_CELEBRATE); }
        PLAYER(SPECIES_MEWTWO) { Level(100); SpAttack(500); Speed(100); Moves(MOVE_CELEBRATE, MOVE_PSYCHIC); }
        OPPONENT(SPECIES_SNORLAX) { Level(100); HP(140); MaxHP(140); SpDefense(200); Speed(1); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_TYRANITAR) { Speed(10); HP(1); Moves(MOVE_CRUNCH); }
    } WHEN {
        TURN { MOVE(player, MOVE_STEALTH_ROCK); EXPECT_MOVE(opponent, MOVE_TACKLE); }
        TURN { SWITCH(player, 1); EXPECT_MOVE(opponent, MOVE_TACKLE); }
        TURN { MOVE(player, MOVE_CELEBRATE); EXPECT_MOVE(opponent, MOVE_TACKLE); }
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: a faster replacement can enter when it survives one hit but not two")
{
    PASSES_RANDOMLY(50, 100, RNG_AI_SWITCH_HASBADODDS);
    GIVEN {
        AI_FLAGS(AI_FLAG_BASIC_TRAINER | AI_FLAG_SMART_SWITCHING | AI_FLAG_ASSUME_STAB);
        PLAYER(SPECIES_MEWTWO) { Level(100); SpAttack(200); Speed(100); Moves(MOVE_CELEBRATE, MOVE_PSYCHIC); }
        OPPONENT(SPECIES_SNORLAX) { Level(100); HP(70); MaxHP(70); SpDefense(200); Speed(1); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_SNORLAX) { Level(100); HP(170); MaxHP(200); SpDefense(200); Speed(200); Moves(MOVE_TACKLE); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); EXPECT_SWITCH(opponent, 1); }
    }
}
