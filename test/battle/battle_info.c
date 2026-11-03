#include "global.h"
#include "test/battle.h"
#include "battle_debug.h"
#include "test/test.h"

// Exercise the read-only menu's wrapper, including its ability substitution and
// restoration, rather than just the lower-level AI calculator.
SINGLE_BATTLE_TEST("Elastic-tests: battle info separates normal and critical rolls and respects critical blockers")
{
    enum Ability ability;
    bool32 blocked;
    PARAMETRIZE { ability = ABILITY_NONE; blocked = FALSE; }
    PARAMETRIZE { ability = ABILITY_SHELL_ARMOR; blocked = TRUE; }
    PARAMETRIZE { ability = ABILITY_BATTLE_ARMOR; blocked = TRUE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
    } THEN {
        struct SimulatedDamage normal, critical;
        gAiLogicData->abilities[opponent] = ABILITY_NONE;
        normal = Test_BattleInfoCalcAiDamage(MOVE_TACKLE, opponent, player, ability, FALSE);
        critical = Test_BattleInfoCalcAiDamage(MOVE_TACKLE, opponent, player, ability, TRUE);
        EXPECT_GT(normal.minimum, 0);
        EXPECT(normal.maximum >= normal.minimum);
        if (blocked)
            EXPECT_EQ(critical.maximum, normal.maximum);
        else
            EXPECT_GT(critical.maximum, normal.maximum);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: battle info leaves status and fixed damage unchanged by critical rolls")
{
    enum Move move;
    PARAMETRIZE { move = MOVE_CELEBRATE; }
    PARAMETRIZE { move = MOVE_SEISMIC_TOSS; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Level(50); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
    } THEN {
        struct SimulatedDamage normal, critical;
        normal = Test_BattleInfoCalcAiDamage(move, opponent, player, ABILITY_NONE, FALSE);
        critical = Test_BattleInfoCalcAiDamage(move, opponent, player, ABILITY_NONE, TRUE);
        EXPECT_EQ(normal.minimum, move == MOVE_CELEBRATE ? 0 : 50);
        EXPECT_EQ(normal.maximum, normal.minimum);
        EXPECT_EQ(critical.maximum, normal.maximum);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: battle info restores ability knowledge and temporary calculation state")
{
    bool32 critical;
    bool32 wasCalculating;
    PARAMETRIZE { critical = FALSE; wasCalculating = FALSE; }
    PARAMETRIZE { critical = TRUE; wasCalculating = FALSE; }
    PARAMETRIZE { critical = FALSE; wasCalculating = TRUE; }
    PARAMETRIZE { critical = TRUE; wasCalculating = TRUE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_KECLEON) { Ability(ABILITY_PROTEAN); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
    } THEN {
        struct BattlePokemon savedAttacker = gBattleMons[opponent];
        struct BattlePokemon savedDefender = gBattleMons[player];
        struct SimulatedDamage immune, neutral;
        gAiLogicData->abilities[opponent] = ABILITY_PROTEAN;
        gAiLogicData->abilities[player] = ABILITY_WATER_ABSORB;
        gAiLogicData->aiCalcInProgress = wasCalculating;
        gBattleStruct->dynamicMoveType = TYPE_FIRE;
        gBattleStruct->dynamicMoveCategory = DAMAGE_CATEGORY_SPECIAL;
        gBattleStruct->magnitudeBasePower = 123;
        gBattleStruct->presentBasePower = 45;
        gMultiHitCounter = 3;

        immune = Test_BattleInfoCalcAiDamage(MOVE_WATER_GUN, opponent, player, ABILITY_WATER_ABSORB, critical);
        neutral = Test_BattleInfoCalcAiDamage(MOVE_WATER_GUN, opponent, player, ABILITY_NONE, critical);
        EXPECT_EQ(immune.maximum, 0);
        EXPECT_GT(neutral.maximum, 0);
        EXPECT_EQ(gAiLogicData->abilities[player], ABILITY_WATER_ABSORB);
        EXPECT_EQ(gAiLogicData->abilities[opponent], ABILITY_PROTEAN);
        EXPECT_EQ(gBattleMons[player].ability, savedDefender.ability);
        EXPECT_EQ(gBattleMons[opponent].ability, savedAttacker.ability);
        EXPECT_EQ(gBattleMons[opponent].types[0], savedAttacker.types[0]);
        EXPECT_EQ(gBattleMons[opponent].types[1], savedAttacker.types[1]);
        EXPECT_EQ(gBattleMons[opponent].types[2], savedAttacker.types[2]);
        EXPECT_EQ(gAiLogicData->aiCalcInProgress, wasCalculating);
        EXPECT_EQ(gBattleStruct->dynamicMoveType, TYPE_FIRE);
        EXPECT_EQ(gBattleStruct->dynamicMoveCategory, DAMAGE_CATEGORY_SPECIAL);
        EXPECT_EQ(gBattleStruct->magnitudeBasePower, 123);
        EXPECT_EQ(gBattleStruct->presentBasePower, 45);
        EXPECT_EQ(gMultiHitCounter, 3);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: battle info critical rolls ignore defensive boosts instead of scaling normal damage")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
    } THEN {
        struct SimulatedDamage normal, critical, boostedNormal, boostedCritical;
        gAiLogicData->abilities[opponent] = ABILITY_NONE;
        gBattleMons[player].statStages[STAT_DEF] = DEFAULT_STAT_STAGE;
        normal = Test_BattleInfoCalcAiDamage(MOVE_TACKLE, opponent, player, ABILITY_NONE, FALSE);
        critical = Test_BattleInfoCalcAiDamage(MOVE_TACKLE, opponent, player, ABILITY_NONE, TRUE);
        gBattleMons[player].statStages[STAT_DEF] = MAX_STAT_STAGE;
        boostedNormal = Test_BattleInfoCalcAiDamage(MOVE_TACKLE, opponent, player, ABILITY_NONE, FALSE);
        boostedCritical = Test_BattleInfoCalcAiDamage(MOVE_TACKLE, opponent, player, ABILITY_NONE, TRUE);
        EXPECT_GT(normal.maximum, boostedNormal.maximum);
        EXPECT_EQ(critical.maximum, boostedCritical.maximum);
        EXPECT_EQ(gBattleMons[player].statStages[STAT_DEF], MAX_STAT_STAGE);
    }
}

TEST("Elastic-tests: battle info damage window preserves options and damage tilemaps")
{
    EXPECT(Test_BattleInfoDamageWindowFitsVram());
}

SINGLE_BATTLE_TEST("Elastic-tests: player damage uses actual critical blockers and restores AI ability knowledge")
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_NONE; }
    PARAMETRIZE { ability = ABILITY_BATTLE_ARMOR; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
    } THEN {
        struct SimulatedDamage normal, critical, status;
        gBattleMons[player].ability = ABILITY_NONE;
        gBattleMons[opponent].ability = ability;
        // Deliberately stale knowledge must not control the player's display.
        gAiLogicData->abilities[player] = ABILITY_SNIPER;
        gAiLogicData->abilities[opponent] = ability == ABILITY_NONE ? ABILITY_BATTLE_ARMOR : ABILITY_NONE;
        normal = Test_BattleInfoCalcPlayerDamage(MOVE_TACKLE, player, opponent, FALSE);
        critical = Test_BattleInfoCalcPlayerDamage(MOVE_TACKLE, player, opponent, TRUE);
        status = Test_BattleInfoCalcPlayerDamage(MOVE_CELEBRATE, player, opponent, TRUE);
        EXPECT_GT(normal.minimum, 0);
        if (ability == ABILITY_BATTLE_ARMOR)
            EXPECT_EQ(critical.maximum, normal.maximum);
        else
            EXPECT_GT(critical.maximum, normal.maximum);
        EXPECT_EQ(status.minimum, 0);
        EXPECT_EQ(status.maximum, 0);
        EXPECT_EQ(gBattleMons[player].ability, ABILITY_NONE);
        EXPECT_EQ(gBattleMons[opponent].ability, ability);
        EXPECT_EQ(gAiLogicData->abilities[player], ABILITY_SNIPER);
        EXPECT_EQ(gAiLogicData->abilities[opponent], ability == ABILITY_NONE ? ABILITY_BATTLE_ARMOR : ABILITY_NONE);
    }
}
