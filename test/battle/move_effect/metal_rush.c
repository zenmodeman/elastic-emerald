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
        PLAYER(SPECIES_COPPERAJAH);
        OPPONENT(SPECIES_WOBBUFFET) { HP(999), MaxHP(999); }
    } WHEN {
        TURN { MOVE(player, MOVE_METAL_RUSH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_METAL_RUSH, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
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
