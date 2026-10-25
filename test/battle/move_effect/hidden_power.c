#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Elastic-tests: Hidden Power fails for species other than Unown")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_HIDDEN_POWER); }
    } SCENE {
        MESSAGE("Wobbuffet used Hidden Power!");
        MESSAGE("But Wobbuffet can't use the move!");
        NONE_OF {
            ANIMATION(ANIM_TYPE_MOVE, MOVE_HIDDEN_POWER, player);
            HP_BAR(opponent);
        }
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Hidden Power supports Unown forms and Fairy typing")
{
    u32 species;
    PARAMETRIZE { species = SPECIES_UNOWN; }
    PARAMETRIZE { species = SPECIES_UNOWN_B; }
    PARAMETRIZE { species = SPECIES_UNOWN_EXCLAMATION; }
    GIVEN {
        PLAYER(species);
        OPPONENT(SPECIES_SABLEYE);
    } WHEN {
        TURN { MOVE(player, MOVE_HIDDEN_POWER); }
    } SCENE {
        MESSAGE("Hidden Power became Fairy type!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HIDDEN_POWER, player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Hidden Power has 60 base power regardless of IVs or generation", s16 damage)
{
    u32 iv, config;
    PARAMETRIZE { iv = 0; config = GEN_5; }
    PARAMETRIZE { iv = 31; config = GEN_5; }
    PARAMETRIZE { iv = 0; config = GEN_6; }
    PARAMETRIZE { iv = 31; config = GEN_6; }
    GIVEN {
        WITH_CONFIG(CONFIG_B_HIDDEN_POWER_DMG, config);
        ASSUME(GetMovePower(MOVE_HIDDEN_POWER) == 60);
        PLAYER(SPECIES_UNOWN) {
            HPIV(iv); AttackIV(iv); DefenseIV(iv);
            SpAttackIV(iv); SpDefenseIV(iv); SpeedIV(iv);
            Attack(100); SpAttack(100);
        }
        OPPONENT(SPECIES_WOBBUFFET) { SpDefense(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_HIDDEN_POWER); }
    } SCENE {
        MESSAGE("Hidden Power became Bug type!");
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
        EXPECT_EQ(results[0].damage, results[2].damage);
        EXPECT_EQ(results[0].damage, results[3].damage);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Hidden Power selects its type against the switched-in opponent")
{
    GIVEN {
        PLAYER(SPECIES_UNOWN);
        OPPONENT(SPECIES_SABLEYE);
        OPPONENT(SPECIES_GYARADOS) { Ability(ABILITY_MOXIE); }
    } WHEN {
        TURN { SWITCH(opponent, 1); MOVE(player, MOVE_HIDDEN_POWER); }
    } SCENE {
        MESSAGE("Hidden Power became Electric type!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HIDDEN_POWER, player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Hidden Power factors weather into its type selection")
{
    GIVEN {
        PLAYER(SPECIES_UNOWN);
        OPPONENT(SPECIES_TANGELA);
    } WHEN {
        TURN { MOVE(player, MOVE_SUNNY_DAY); }
        TURN { MOVE(player, MOVE_HIDDEN_POWER); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SUNNY_DAY, player);
        MESSAGE("Hidden Power became Fire type!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HIDDEN_POWER, player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Hidden Power factors the user's type boosters and Gems")
{
    u32 item;
    PARAMETRIZE { item = ITEM_CHARCOAL; }
    PARAMETRIZE { item = ITEM_FLAME_PLATE; }
    PARAMETRIZE { item = ITEM_FIRE_GEM; }
    GIVEN {
        PLAYER(SPECIES_UNOWN) { Item(item); }
        OPPONENT(SPECIES_TANGELA);
    } WHEN {
        TURN { MOVE(player, MOVE_HIDDEN_POWER); }
    } SCENE {
        MESSAGE("Hidden Power became Fire type!");
        if (item == ITEM_FIRE_GEM)
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HIDDEN_POWER, player);
        HP_BAR(opponent);
    } THEN {
        if (item == ITEM_FIRE_GEM)
            EXPECT_EQ(player->item, ITEM_NONE);
        else
            EXPECT_EQ(player->item, item);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Hidden Power ignores unrevealed opposing items")
{
    GIVEN {
        PLAYER(SPECIES_UNOWN) { Item(ITEM_CHARCOAL); }
        OPPONENT(SPECIES_TANGELA) { Item(ITEM_OCCA_BERRY); }
    } WHEN {
        TURN { MOVE(player, MOVE_HIDDEN_POWER); }
    } SCENE {
        MESSAGE("Hidden Power became Fire type!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_BERRY, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HIDDEN_POWER, player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Hidden Power only accounts for Levitate after it is revealed")
{
    GIVEN {
        PLAYER(SPECIES_UNOWN);
        OPPONENT(SPECIES_BRONZONG) { Ability(ABILITY_LEVITATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_HIDDEN_POWER); }
        TURN { MOVE(player, MOVE_HIDDEN_POWER); }
    } SCENE {
        MESSAGE("Hidden Power became Ground type!");
        ABILITY_POPUP(opponent, ABILITY_LEVITATE);
        MESSAGE("Hidden Power became Ghost type!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HIDDEN_POWER, player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Hidden Power announces its type before Proactive Color Change")
{
    GIVEN {
        PLAYER(SPECIES_UNOWN);
        OPPONENT(SPECIES_KECLEON) { Ability(ABILITY_COLOR_CHANGE); }
    } WHEN {
        TURN { MOVE(player, MOVE_HIDDEN_POWER); }
    } SCENE {
        MESSAGE("Hidden Power became Fighting type!");
        ABILITY_POPUP(opponent, ABILITY_COLOR_CHANGE);
        MESSAGE("The opposing Kecleon's type changed to Fighting!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HIDDEN_POWER, player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Hidden Power preserves the legacy Counter exception")
{
    u32 config = GEN_3;
    PARAMETRIZE { config = GEN_2; }
    PARAMETRIZE { config = GEN_3; }
    GIVEN {
        WITH_CONFIG(CONFIG_B_HIDDEN_POWER_COUNTER, config);
        PLAYER(SPECIES_UNOWN) { HP(1000); MaxHP(1000); Attack(100); SpAttack(100); Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1000); MaxHP(1000); SpDefense(100); Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_HIDDEN_POWER); MOVE(opponent, MOVE_MIRROR_COAT); }
        TURN { MOVE(player, MOVE_HIDDEN_POWER); MOVE(opponent, MOVE_COUNTER); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HIDDEN_POWER, player);
        MESSAGE("The opposing Wobbuffet used Mirror Coat!");
        MESSAGE("But it failed!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HIDDEN_POWER, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_COUNTER, opponent);
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: Hidden Power ignores AI ability omniscience when choosing its type")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_OMNISCIENT);
        PLAYER(SPECIES_BRONZONG) { Ability(ABILITY_LEVITATE); Moves(MOVE_CELEBRATE); }
        OPPONENT(SPECIES_UNOWN) { Moves(MOVE_HIDDEN_POWER); }
    } WHEN {
        TURN { EXPECT_MOVE(opponent, MOVE_HIDDEN_POWER); }
    } SCENE {
        MESSAGE("Hidden Power became Ground type!");
        ABILITY_POPUP(player, ABILITY_LEVITATE);
        NOT HP_BAR(player);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Hidden Power remembers revealed abilities across switches")
{
    GIVEN {
        PLAYER(SPECIES_UNOWN);
        OPPONENT(SPECIES_BRONZONG) { Ability(ABILITY_LEVITATE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_HIDDEN_POWER); }
        TURN { SWITCH(opponent, 1); MOVE(player, MOVE_CELEBRATE); }
        TURN { SWITCH(opponent, 0); MOVE(player, MOVE_HIDDEN_POWER); }
    } SCENE {
        MESSAGE("Hidden Power became Ground type!");
        ABILITY_POPUP(opponent, ABILITY_LEVITATE);
        MESSAGE("Hidden Power became Ghost type!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HIDDEN_POWER, player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Hidden Power avoids absorption abilities only after revelation")
{
    GIVEN {
        PLAYER(SPECIES_UNOWN);
        OPPONENT(SPECIES_SCIZOR) { Ability(ABILITY_FLASH_FIRE); }
    } WHEN {
        TURN { MOVE(player, MOVE_HIDDEN_POWER); }
        TURN { MOVE(player, MOVE_HIDDEN_POWER); }
    } SCENE {
        MESSAGE("Hidden Power became Fire type!");
        ABILITY_POPUP(opponent, ABILITY_FLASH_FIRE);
        MESSAGE("Hidden Power became Fighting type!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HIDDEN_POWER, player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Hidden Power does not consume a Gem for its nominal Normal type")
{
    GIVEN {
        PLAYER(SPECIES_UNOWN) { Item(ITEM_NORMAL_GEM); }
        OPPONENT(SPECIES_TANGELA);
    } WHEN {
        TURN { MOVE(player, MOVE_HIDDEN_POWER); }
    } SCENE {
        MESSAGE("Hidden Power became Flying type!");
        NOT ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HIDDEN_POWER, player);
        HP_BAR(opponent);
    } THEN {
        EXPECT_EQ(player->item, ITEM_NORMAL_GEM);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Hidden Power boosts Unown damage using Attack relative to Special Attack", s16 damage)
{
    enum Move move;
    u32 attack, spAttack;
    PARAMETRIZE { move = MOVE_SILVER_WIND; attack = 100; spAttack = 100; }
    PARAMETRIZE { move = MOVE_HIDDEN_POWER; attack = 100; spAttack = 100; }
    PARAMETRIZE { move = MOVE_SILVER_WIND; attack = 200; spAttack = 100; }
    PARAMETRIZE { move = MOVE_HIDDEN_POWER; attack = 200; spAttack = 100; }
    PARAMETRIZE { move = MOVE_SILVER_WIND; attack = 100; spAttack = 200; }
    PARAMETRIZE { move = MOVE_HIDDEN_POWER; attack = 100; spAttack = 200; }
    GIVEN {
        ASSUME(GetMovePower(MOVE_SILVER_WIND) == 60);
        ASSUME(GetMoveCategory(MOVE_SILVER_WIND) == DAMAGE_CATEGORY_SPECIAL);
        ASSUME(GetMoveType(MOVE_SILVER_WIND) == TYPE_BUG);
        PLAYER(SPECIES_UNOWN) { Attack(attack); SpAttack(spAttack); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1000); MaxHP(1000); SpDefense(100); }
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.25), results[1].damage);
        EXPECT_MUL_EQ(results[2].damage, Q_4_12(1.5), results[3].damage);
        EXPECT_MUL_EQ(results[4].damage, Q_4_12(1.125), results[5].damage);
    }
}
