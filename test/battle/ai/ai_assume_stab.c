#include "global.h"
#include "test/battle.h"
#include "battle_ai_util.h"
#include "pokemon.h"

AI_SINGLE_BATTLE_TEST("AI_FLAG_ASSUME_STAB sees the player's STAB moves")
{
    u32 aiFlag = 0;
    PARAMETRIZE { aiFlag = AI_FLAG_ASSUME_STAB; }
    PARAMETRIZE { aiFlag = AI_FLAG_OMNISCIENT; }
    PARAMETRIZE { aiFlag = 0; }
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT | AI_FLAG_SMART_MON_CHOICES | aiFlag);
        PLAYER(SPECIES_TYPHLOSION) { Speed(5); Moves(MOVE_TACKLE, MOVE_FLAMETHROWER); }
        OPPONENT(SPECIES_ZIGZAGOON) { Speed(1); Moves(MOVE_TACKLE); Level(1); }
        OPPONENT(SPECIES_SCIZOR) { Speed(4); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_BLISSEY) { Speed(4); Moves(MOVE_TACKLE); }
    } WHEN {
        if (aiFlag == AI_FLAG_ASSUME_STAB || aiFlag == AI_FLAG_OMNISCIENT)
            TURN { MOVE(player, MOVE_TACKLE); EXPECT_MOVE(opponent, MOVE_TACKLE); EXPECT_SEND_OUT(opponent, 2); }
        else
            TURN { MOVE(player, MOVE_TACKLE); EXPECT_MOVE(opponent, MOVE_TACKLE); EXPECT_SEND_OUT(opponent, 1); }
    }
}

AI_SINGLE_BATTLE_TEST("AI_FLAG_ASSUME_STAB does not see the player's non-STAB moves")
{
    u32 aiFlag = 0;
    PARAMETRIZE { aiFlag = AI_FLAG_ASSUME_STAB; }
    PARAMETRIZE { aiFlag = AI_FLAG_OMNISCIENT; }
    PARAMETRIZE { aiFlag = 0; }
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT | AI_FLAG_SMART_MON_CHOICES | aiFlag);
        PLAYER(SPECIES_GOREBYSS) { Speed(5); Moves(MOVE_TACKLE, MOVE_FLAMETHROWER); }
        OPPONENT(SPECIES_ZIGZAGOON) { Speed(1); Moves(MOVE_TACKLE); Level(1); }
        OPPONENT(SPECIES_SCIZOR) { Speed(4); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_BLISSEY) { Speed(4); Moves(MOVE_TACKLE); }
    } WHEN {
        if (aiFlag == AI_FLAG_OMNISCIENT)
            TURN { MOVE(player, MOVE_TACKLE); EXPECT_MOVE(opponent, MOVE_TACKLE); EXPECT_SEND_OUT(opponent, 2); }
        else
            TURN { MOVE(player, MOVE_TACKLE); EXPECT_MOVE(opponent, MOVE_TACKLE); EXPECT_SEND_OUT(opponent, 1); }
    }
}

AI_DOUBLE_BATTLE_TEST("AI correctly records assumed STAB moves")
{
    u32 aiFlag = 0;
    // Not checking Omniscient here because it doesn't change the battle history
    PARAMETRIZE { aiFlag = AI_FLAG_ASSUME_STAB; }
    PARAMETRIZE { aiFlag = 0; }
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_CHECK_VIABILITY | AI_FLAG_TRY_TO_FAINT | aiFlag);
        PLAYER(SPECIES_TYPHLOSION) { Moves(MOVE_TACKLE, MOVE_FLAMETHROWER, MOVE_SMOG); }
        PLAYER(SPECIES_ZIGZAGOON) { Moves(MOVE_TACKLE, MOVE_HEADBUTT, MOVE_THUNDERBOLT); }
        OPPONENT(SPECIES_ZIGZAGOON) { Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_ZIGZAGOON) { Moves(MOVE_TACKLE); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_TACKLE, target:opponentLeft); MOVE(playerRight, MOVE_THUNDERBOLT, target:opponentRight); }
    } THEN {
        if (aiFlag == AI_FLAG_ASSUME_STAB)
        {
            EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_LEFT][0], MOVE_TACKLE);
            EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_LEFT][1], MOVE_FLAMETHROWER);
            EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_LEFT][2], MOVE_NONE);
            EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_LEFT][3], MOVE_NONE);

            EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_RIGHT][0], MOVE_TACKLE);
            EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_RIGHT][1], MOVE_HEADBUTT);
            EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_RIGHT][2], MOVE_THUNDERBOLT);
            EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_RIGHT][3], MOVE_NONE);
        }
        else if (aiFlag == 0)
        {
            EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_LEFT][0], MOVE_TACKLE);
            EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_LEFT][1], MOVE_NONE);
            EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_LEFT][2], MOVE_NONE);
            EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_LEFT][3], MOVE_NONE);

            EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_RIGHT][0], MOVE_NONE);
            EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_RIGHT][1], MOVE_NONE);
            EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_RIGHT][2], MOVE_THUNDERBOLT);
            EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_RIGHT][3], MOVE_NONE);
        }
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: STAB assumptions exclude unrevealed charging and recharge moves")
{
    u32 species, move;
    PARAMETRIZE { species = SPECIES_CHARIZARD; move = MOVE_FLY; }
    PARAMETRIZE { species = SPECIES_VENUSAUR; move = MOVE_SOLAR_BEAM; }
    PARAMETRIZE { species = SPECIES_SNORLAX; move = MOVE_SKULL_BASH; }
    PARAMETRIZE { species = SPECIES_SNORLAX; move = MOVE_HYPER_BEAM; }
    PARAMETRIZE { species = SPECIES_CHARIZARD; move = MOVE_BLAST_BURN; }
    GIVEN {
        ASSUME(IsSpeciesOfType(species, GetMoveType(move)));
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_ASSUME_STAB);
        PLAYER(species) { Moves(MOVE_CELEBRATE, move); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_LEFT][0], MOVE_CELEBRATE);
        EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_LEFT][1], MOVE_NONE);
        EXPECT_EQ(gAiPartyData->mons[B_TRAINER_PLAYER][0].moves[1], MOVE_NONE);
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: STAB restrictions retain revealed recharge moves")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_ASSUME_STAB);
        PLAYER(SPECIES_SNORLAX) { Moves(MOVE_HYPER_BEAM); }
        OPPONENT(SPECIES_BLISSEY) { Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_HYPER_BEAM); }
    } THEN {
        EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_LEFT][0], MOVE_HYPER_BEAM);
        EXPECT_EQ(gAiPartyData->mons[B_TRAINER_PLAYER][0].moves[0], MOVE_HYPER_BEAM);
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: STAB charge skipping requires known Power Herb")
{
    u32 flags;
    PARAMETRIZE { flags = AI_FLAG_ASSUME_STAB; }
    PARAMETRIZE { flags = AI_FLAG_ASSUME_STAB | AI_FLAG_ITEM_OMNISCIENCE; }
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | flags);
        PLAYER(SPECIES_CHARIZARD) { Item(ITEM_POWER_HERB); Moves(MOVE_CELEBRATE, MOVE_FLY, MOVE_BLAST_BURN); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_LEFT][1],
            flags & AI_FLAG_ITEM_OMNISCIENCE ? MOVE_FLY : MOVE_NONE);
        EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_LEFT][2], MOVE_NONE);
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: STAB Solar Beam inference follows weather and known Utility Umbrella")
{
    u32 ability, item;
    PARAMETRIZE { ability = ABILITY_DROUGHT; item = ITEM_NONE; }
    PARAMETRIZE { ability = ABILITY_DRIZZLE; item = ITEM_NONE; }
    PARAMETRIZE { ability = ABILITY_DROUGHT; item = ITEM_UTILITY_UMBRELLA; }
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_ASSUME_STAB | AI_FLAG_ITEM_OMNISCIENCE);
        PLAYER(SPECIES_VENUSAUR) { Item(item); Moves(MOVE_CELEBRATE, MOVE_SOLAR_BEAM); }
        OPPONENT(SPECIES_TORKOAL) { Ability(ability); Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_LEFT][1],
            ability == ABILITY_DROUGHT && item == ITEM_NONE ? MOVE_SOLAR_BEAM : MOVE_NONE);
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: Tailwind permits unrevealed STAB Razor Wind inference")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_ASSUME_STAB);
        PLAYER(SPECIES_CHARIZARD) { Moves(MOVE_TAILWIND, MOVE_RAZOR_WIND, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_TAILWIND); }
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(gBattleHistory->usedMoves[B_POSITION_PLAYER_LEFT][1], MOVE_RAZOR_WIND);
    }
}
