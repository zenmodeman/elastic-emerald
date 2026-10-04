#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Elastic-tests: Overwhelm Beam deals damage before replacing the target ability")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_SHADOW_TAG); }
    } WHEN {
        TURN { MOVE(player, MOVE_OVERWHELM_BEAM); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_OVERWHELM_BEAM, player);
        HP_BAR(opponent);
        ABILITY_POPUP(opponent, ABILITY_SHADOW_TAG);
    } THEN {
        EXPECT_EQ(opponent->ability, ABILITY_INSOMNIA);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Overwhelm Beam protections block the rider without blocking damage")
{
    u32 species;
    enum Ability ability;
    u32 item;
    PARAMETRIZE { species = SPECIES_WOBBUFFET; ability = ABILITY_SHADOW_TAG; item = ITEM_ABILITY_SHIELD; }
    PARAMETRIZE { species = SPECIES_WOBBUFFET; ability = ABILITY_SHADOW_TAG; item = ITEM_COVERT_CLOAK; }
    PARAMETRIZE { species = SPECIES_ARCEUS; ability = ABILITY_MULTITYPE; item = ITEM_NONE; }
    PARAMETRIZE { species = SPECIES_DUSTOX; ability = ABILITY_SHIELD_DUST; item = ITEM_NONE; }
    PARAMETRIZE { species = SPECIES_HYPNO; ability = ABILITY_INSOMNIA; item = ITEM_NONE; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(species) { Ability(ability); Item(item); }
    } WHEN {
        TURN { MOVE(player, MOVE_OVERWHELM_BEAM); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_OVERWHELM_BEAM, player);
        HP_BAR(opponent);
    } THEN {
        EXPECT_EQ(opponent->ability, ability);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Sheer Force suppresses Overwhelm Beam's ability overwrite")
{
    GIVEN {
        PLAYER(SPECIES_NIDOKING) { Ability(ABILITY_SHEER_FORCE); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_SHADOW_TAG); }
    } WHEN {
        TURN { MOVE(player, MOVE_OVERWHELM_BEAM); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_OVERWHELM_BEAM, player);
        HP_BAR(opponent);
    } THEN {
        EXPECT_EQ(opponent->ability, ABILITY_SHADOW_TAG);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Overwhelm Beam cannot overwrite an ability through Substitute")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_SHADOW_TAG); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_SUBSTITUTE); MOVE(player, MOVE_OVERWHELM_BEAM); }
    } THEN {
        EXPECT_EQ(opponent->ability, ABILITY_SHADOW_TAG);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Overwhelm Beam cannot overwrite an ability on a miss")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_SHADOW_TAG); }
    } WHEN {
        TURN { MOVE(player, MOVE_OVERWHELM_BEAM, hit: FALSE); }
    } THEN {
        EXPECT_EQ(opponent->ability, ABILITY_SHADOW_TAG);
    }
}
