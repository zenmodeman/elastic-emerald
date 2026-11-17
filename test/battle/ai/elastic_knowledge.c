#include "global.h"
#include "test/battle.h"
#include "battle_ai_util.h"
#include "battle_ai_record.h"
#include "battle_ai_switch.h"
#include "battle_gimmick.h"

AI_SINGLE_BATTLE_TEST("Elastic-tests: Archaludon Electro Shot inference needs known charge skipping")
{
    u64 flags;
    u32 item, ability, species;
    bool32 expected;
    PARAMETRIZE { species = SPECIES_ARCHALUDON; flags = 0; item = ITEM_NONE; ability = ABILITY_NONE; expected = FALSE; }
    PARAMETRIZE { species = SPECIES_ARCHALUDON; flags = 0; item = ITEM_POWER_HERB; ability = ABILITY_NONE; expected = FALSE; }
    PARAMETRIZE { species = SPECIES_ARCHALUDON; flags = AI_FLAG_ITEM_OMNISCIENCE; item = ITEM_POWER_HERB; ability = ABILITY_NONE; expected = TRUE; }
    PARAMETRIZE { species = SPECIES_ARCHALUDON; flags = 0; item = ITEM_NONE; ability = ABILITY_DRIZZLE; expected = TRUE; }
    PARAMETRIZE { species = SPECIES_ARCHALUDON; flags = AI_FLAG_ITEM_OMNISCIENCE; item = ITEM_UTILITY_UMBRELLA; ability = ABILITY_DRIZZLE; expected = FALSE; }
    PARAMETRIZE { species = SPECIES_DURALUDON; flags = AI_FLAG_ITEM_OMNISCIENCE; item = ITEM_POWER_HERB; ability = ABILITY_NONE; expected = FALSE; }
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_ASSUME_STAB | flags);
        PLAYER(species) { Speed(10); Item(item); Moves(MOVE_CELEBRATE, MOVE_ELECTRO_SHOT); }
        OPPONENT(SPECIES_PELIPPER) { Speed(10); Ability(ability); Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        enum Move moves[MAX_MON_MOVES];
        GetDamageMoves(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT), moves);
        EXPECT_EQ(moves[1], expected ? MOVE_ELECTRO_SHOT : MOVE_NONE);
        EXPECT_EQ(GetMovesArray(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT))[1], MOVE_NONE);
        EXPECT_EQ(gAiPartyData->mons[B_TRAINER_PLAYER][0].moves[1], MOVE_NONE);
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: prospective Mega STAB needs a known matching stone and unused Mega")
{
    u32 item;
    u64 flags;
    bool32 spent, expected;
    PARAMETRIZE { item = ITEM_GYARADOSITE; flags = AI_FLAG_ITEM_OMNISCIENCE; spent = FALSE; expected = TRUE; }
    PARAMETRIZE { item = ITEM_GYARADOSITE; flags = 0; spent = FALSE; expected = FALSE; }
    PARAMETRIZE { item = ITEM_GYARADOSITE; flags = AI_FLAG_ITEM_OMNISCIENCE; spent = TRUE; expected = FALSE; }
    PARAMETRIZE { item = ITEM_VENUSAURITE; flags = AI_FLAG_ITEM_OMNISCIENCE; spent = FALSE; expected = FALSE; }
    PARAMETRIZE { item = ITEM_NONE; flags = AI_FLAG_ITEM_OMNISCIENCE; spent = FALSE; expected = FALSE; }
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_ASSUME_STAB | flags);
        PLAYER(SPECIES_GYARADOS) { Speed(10); Item(item); Moves(MOVE_WATERFALL, MOVE_CRUNCH, MOVE_AERIAL_ACE, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(10); Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        enum BattlerId battler = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
        if (spent)
            SetGimmickAsActivated(battler, GIMMICK_MEGA);
        enum Move moves[MAX_MON_MOVES];
        GetDamageMoves(battler, moves);
        EXPECT_EQ(moves[0], MOVE_WATERFALL);
        EXPECT_EQ(moves[1], expected ? MOVE_CRUNCH : MOVE_NONE);
        EXPECT_EQ(moves[2], MOVE_AERIAL_ACE);
        EXPECT_EQ(GetMovesArray(battler)[1], MOVE_NONE);
        EXPECT_EQ(gAiPartyData->mons[B_TRAINER_PLAYER][0].moves[1], MOVE_NONE);
        EXPECT_EQ(gBattleMons[battler].species, SPECIES_GYARADOS);
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: actual Mega Gyarados loses unrevealed Flying STAB eligibility")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_ASSUME_STAB | AI_FLAG_ITEM_OMNISCIENCE);
        PLAYER(SPECIES_GYARADOS) { Speed(10); Item(ITEM_GYARADOSITE); Moves(MOVE_WATERFALL, MOVE_CRUNCH, MOVE_AERIAL_ACE, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(10); Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE, gimmick: GIMMICK_MEGA); }
    } THEN {
        enum BattlerId battler = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
        enum Move moves[MAX_MON_MOVES];
        GetDamageMoves(battler, moves);
        EXPECT_EQ(gBattleMons[battler].species, SPECIES_GYARADOS_MEGA);
        EXPECT_EQ(moves[0], MOVE_WATERFALL);
        EXPECT_EQ(moves[1], MOVE_CRUNCH);
        EXPECT_EQ(moves[2], MOVE_NONE);
        EXPECT_EQ(GetMovesArray(battler)[1], MOVE_NONE);
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: Forewarn coverage knowledge persists across switches")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_ASSUME_STAB);
        PLAYER(SPECIES_GYARADOS) { Speed(10); Moves(MOVE_CELEBRATE, MOVE_FLAMETHROWER, MOVE_WATER_GUN); }
        PLAYER(SPECIES_MAGIKARP) { Speed(10); Moves(MOVE_CELEBRATE); }
        OPPONENT(SPECIES_MUSHARNA) { Speed(10); Ability(ABILITY_FOREWARN); Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
        TURN { SWITCH(player, 1); }
        TURN { SWITCH(player, 0); }
    } THEN {
        enum BattlerId battler = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
        enum Move moves[MAX_MON_MOVES];
        GetDamageMoves(battler, moves);
        EXPECT_EQ(moves[1], MOVE_FLAMETHROWER);
        EXPECT_EQ(GetMovesArray(battler)[1], MOVE_FLAMETHROWER);
        EXPECT_EQ(GetMovesArray(battler)[2], MOVE_NONE);
        EXPECT_EQ(gAiPartyData->mons[B_TRAINER_PLAYER][0].moves[1], MOVE_FLAMETHROWER);
        EXPECT_EQ(gAiPartyData->mons[B_TRAINER_PLAYER][1].moves[1], MOVE_NONE);
    }
}

AI_DOUBLE_BATTLE_TEST("Elastic-tests: Forewarn records only its announced opponent and move")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE);
        PLAYER(SPECIES_GYARADOS) { Speed(10); Moves(MOVE_CELEBRATE, MOVE_FLAMETHROWER); }
        PLAYER(SPECIES_MAGIKARP) { Speed(10); Moves(MOVE_CELEBRATE, MOVE_WATER_GUN); }
        OPPONENT(SPECIES_MUSHARNA) { Speed(10); Ability(ABILITY_FOREWARN); Moves(MOVE_CELEBRATE); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(10); Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_CELEBRATE); MOVE(playerRight, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(GetMovesArray(GetBattlerAtPosition(B_POSITION_PLAYER_LEFT))[1], MOVE_FLAMETHROWER);
        EXPECT_EQ(GetMovesArray(GetBattlerAtPosition(B_POSITION_PLAYER_RIGHT))[1], MOVE_NONE);
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: item omniscience does not reveal hidden moves or abilities")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_ELASTIC_KNOWLEDGE);
        PLAYER(SPECIES_AZUMARILL) { Speed(10); Ability(ABILITY_HUGE_POWER); Item(ITEM_CHOICE_BAND); Moves(MOVE_CELEBRATE, MOVE_ICE_PUNCH); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(10); Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(gAiPartyData->mons[B_TRAINER_PLAYER][0].item, ITEM_CHOICE_BAND);
        EXPECT_EQ(gAiPartyData->mons[B_TRAINER_PLAYER][0].ability, ABILITY_NONE);
        EXPECT_EQ(gAiPartyData->mons[B_TRAINER_PLAYER][0].moves[1], MOVE_NONE);
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: unseen player reserves do not become immunity prediction candidates")
{
    u32 species;
    PARAMETRIZE { species = SPECIES_GEODUDE; }
    PARAMETRIZE { species = SPECIES_GENGAR; }
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_ELASTIC_KNOWLEDGE | AI_FLAG_PREDICT_SWITCH | AI_FLAG_PREDICT_INCOMING_MON);
        PLAYER(SPECIES_MAGIKARP) { HP(1000); MaxHP(1000); Speed(10); Moves(MOVE_CELEBRATE); }
        PLAYER(species) { Speed(10); Moves(MOVE_CELEBRATE); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(10); Moves(MOVE_THUNDERBOLT); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); EXPECT_MOVE(opponent, MOVE_THUNDERBOLT); }
    } THEN {
        gAiBattleData->playerSwitchesDuringAiStint = 5;
        EXPECT_EQ(TryChooseImmunityPredictionSwitchin(GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT), GetBattlerAtPosition(B_POSITION_PLAYER_LEFT), MOVE_THUNDERBOLT), FALSE);
        EXPECT_EQ(gAiPartyData->mons[B_TRAINER_PLAYER][1].species, SPECIES_NONE);
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: Forewarn-revealed coverage informs fast-KO switching before use")
{
    PASSES_RANDOMLY(50, 100, RNG_AI_SWITCH_HASBADODDS);
    GIVEN {
        AI_FLAGS(AI_FLAG_BASIC_TRAINER | AI_FLAG_SMART_SWITCHING | AI_FLAG_ASSUME_STAB);
        PLAYER(SPECIES_GYARADOS) { Level(100); SpAttack(200); Speed(100); Moves(MOVE_CELEBRATE, MOVE_FLAMETHROWER); }
        OPPONENT(SPECIES_TANGELA) { Level(100); HP(70); MaxHP(70); SpDefense(100); Speed(1); Ability(ABILITY_FOREWARN); Moves(MOVE_TACKLE); }
        OPPONENT(SPECIES_TYRANITAR) { Speed(10); Level(100); HP(500); MaxHP(500); SpDefense(500); Moves(MOVE_CRUNCH); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); EXPECT_SWITCH(opponent, 1); }
    }
}
