#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveEffect(MOVE_METAL_RUSH) == EFFECT_METAL_RUSH);
    ASSUME(GetSpeciesWeight(SPECIES_ARON) == 600);
    ASSUME(GetSpeciesWeight(SPECIES_COPPERAJAH) == 6500);
}

SINGLE_BATTLE_TEST("Zenmodeman: Metal Rush raises the user's Speed by 1 if the user weighs 50kg or less")
{
    GIVEN {
        PLAYER(SPECIES_ARON) { Item(ITEM_FLOAT_STONE); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(999), MaxHP(999); }
    } WHEN {
        TURN { MOVE(player, MOVE_METAL_RUSH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_METAL_RUSH, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        NOT ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(opponent->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Metal Rush lowers the target's Defense by 1 if the user weighs 200kg or more")
{
    GIVEN {
        PLAYER(SPECIES_COPPERAJAH) { Ability(ABILITY_HEAVY_METAL); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(999), MaxHP(999); }
    } WHEN {
        TURN { MOVE(player, MOVE_METAL_RUSH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_METAL_RUSH, player);
        NOT ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE);
        EXPECT_EQ(opponent->statStages[STAT_DEF], DEFAULT_STAT_STAGE - 1);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Metal Rush has no stat rider for middle-weight users")
{
    GIVEN {
        PLAYER(SPECIES_ARON);
        OPPONENT(SPECIES_WOBBUFFET) { HP(999), MaxHP(999); }
    } WHEN {
        TURN { MOVE(player, MOVE_METAL_RUSH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_METAL_RUSH, player);
        NONE_OF {
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE);
        EXPECT_EQ(opponent->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
    }
}


SINGLE_BATTLE_TEST("Zenmodeman: Sheer Force suppresses Metal Rush's heavy-user Defense drop")
{
    GIVEN {
        PLAYER(SPECIES_COPPERAJAH) { Ability(ABILITY_SHEER_FORCE); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(999), MaxHP(999); }
    } WHEN {
        TURN { MOVE(player, MOVE_METAL_RUSH); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE);
        EXPECT_EQ(opponent->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Light Metal's 40kg cap gives Metal Rush its light-user rider")
{
    GIVEN {
        PLAYER(SPECIES_COPPERAJAH) { Ability(ABILITY_LIGHT_METAL); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(999); MaxHP(999); }
    } WHEN {
        TURN { MOVE(player, MOVE_METAL_RUSH); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(opponent->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Heavy Metal's 200kg floor gives Metal Rush its heavy-user rider")
{
    GIVEN {
        PLAYER(SPECIES_ARON) { Ability(ABILITY_HEAVY_METAL); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(999); MaxHP(999); }
    } WHEN {
        TURN { MOVE(player, MOVE_METAL_RUSH); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE);
        EXPECT_EQ(opponent->statStages[STAT_DEF], DEFAULT_STAT_STAGE - 1);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Float Stone alone leaves a very heavy Metal Rush user in the middle band")
{
    GIVEN {
        PLAYER(SPECIES_COPPERAJAH) { Item(ITEM_FLOAT_STONE); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(999); MaxHP(999); }
    } WHEN {
        TURN { MOVE(player, MOVE_METAL_RUSH); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE);
        EXPECT_EQ(opponent->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Float Stone applies after Light Metal's cap for Metal Rush")
{
    GIVEN {
        PLAYER(SPECIES_COPPERAJAH) { Ability(ABILITY_LIGHT_METAL); Item(ITEM_FLOAT_STONE); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(999); MaxHP(999); }
    } WHEN {
        TURN { MOVE(player, MOVE_METAL_RUSH); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(opponent->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Contrary reverses Metal Rush's light-user Speed boost")
{
    GIVEN {
        PLAYER(SPECIES_ARON) { Ability(ABILITY_CONTRARY); Item(ITEM_FLOAT_STONE); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(999); MaxHP(999); }
    } WHEN {
        TURN { MOVE(player, MOVE_METAL_RUSH); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE - 1);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Contrary reverses Metal Rush's heavy-user Defense drop")
{
    GIVEN {
        PLAYER(SPECIES_COPPERAJAH) { Ability(ABILITY_HEAVY_METAL); }
        OPPONENT(SPECIES_SHUCKLE) { HP(999); MaxHP(999); Ability(ABILITY_CONTRARY); }
    } WHEN {
        TURN { MOVE(player, MOVE_METAL_RUSH); }
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_DEF], DEFAULT_STAT_STAGE + 1);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Metal Rush has no weight rider when blocked by Protect")
{
    GIVEN {
        PLAYER(SPECIES_COPPERAJAH) { Ability(ABILITY_HEAVY_METAL); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(999); MaxHP(999); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_PROTECT); MOVE(player, MOVE_METAL_RUSH); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE);
        EXPECT_EQ(opponent->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Clear Body blocks Metal Rush's heavy-user Defense drop")
{
    GIVEN {
        PLAYER(SPECIES_COPPERAJAH) { Ability(ABILITY_HEAVY_METAL); }
        OPPONENT(SPECIES_BELDUM) { HP(999); MaxHP(999); Ability(ABILITY_CLEAR_BODY); }
    } WHEN {
        TURN { MOVE(player, MOVE_METAL_RUSH); }
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Mirror Armor reflects Metal Rush's heavy-user Defense drop")
{
    GIVEN {
        PLAYER(SPECIES_COPPERAJAH) { Ability(ABILITY_HEAVY_METAL); }
        OPPONENT(SPECIES_CORVIKNIGHT) { HP(999); MaxHP(999); Ability(ABILITY_MIRROR_ARMOR); }
    } WHEN {
        TURN { MOVE(player, MOVE_METAL_RUSH); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_DEF], DEFAULT_STAT_STAGE - 1);
        EXPECT_EQ(opponent->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
    }
}
