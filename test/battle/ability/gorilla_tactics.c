#include "global.h"
#include "event_data.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Gorilla Tactics boosts physical damage by 50%", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_ZEN_MODE; }
    PARAMETRIZE { ability = ABILITY_GORILLA_TACTICS; }

    GIVEN {
        PLAYER(SPECIES_DARMANITAN_GALAR) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Gorilla Tactics stacks with Choice Band to reach 2.25x Attack", s16 damage)
{
    enum Ability ability;
    enum Item item;
    PARAMETRIZE { ability = ABILITY_ZEN_MODE;         item = ITEM_NONE; }
    PARAMETRIZE { ability = ABILITY_GORILLA_TACTICS;  item = ITEM_NONE; }
    PARAMETRIZE { ability = ABILITY_GORILLA_TACTICS;  item = ITEM_CHOICE_BAND; }

    GIVEN {
        ASSUME(GetItemHoldEffect(ITEM_CHOICE_BAND) == HOLD_EFFECT_CHOICE_BAND);
        PLAYER(SPECIES_DARMANITAN_GALAR) { Ability(ability); Item(item); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5),  results[1].damage);
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(2.25), results[2].damage);
    }
}

SINGLE_BATTLE_TEST("Gorilla Tactics does not boost damage while Dynamaxed", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_ZEN_MODE; }
    PARAMETRIZE { ability = ABILITY_GORILLA_TACTICS; }

    GIVEN {
        PLAYER(SPECIES_DARMANITAN_GALAR) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH, gimmick: GIMMICK_DYNAMAX); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MAX_STRIKE, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Gorilla Tactics does not lock moves while Dynamaxed")
{
    GIVEN {
        PLAYER(SPECIES_DARMANITAN_GALAR) { Ability(ABILITY_GORILLA_TACTICS); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH, gimmick: GIMMICK_DYNAMAX); }
        TURN { MOVE(player, MOVE_FLAME_CHARGE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MAX_STRIKE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MAX_FLARE, player);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Restricted Gorilla Tactics ignores Choice Band but keeps its own boost", s16 damage)
{
    enum Item item;
    enum Ability ability;
    PARAMETRIZE { item = ITEM_NONE; ability = ABILITY_GORILLA_TACTICS; }
    PARAMETRIZE { item = ITEM_CHOICE_BAND; ability = ABILITY_GORILLA_TACTICS; }
    PARAMETRIZE { item = ITEM_NONE; ability = ABILITY_ZEN_MODE; }

    GIVEN {
        FlagSet(FLAG_RESTRICTED_MODE);
        PLAYER(SPECIES_DARMANITAN_GALAR) { Ability(ability); Item(item); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
        EXPECT_MUL_EQ(results[2].damage, Q_4_12(1.5), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Choice Scarf is ignored only for Restricted Gorilla Tactics")
{
    bool32 restricted;
    enum Ability ability;
    PARAMETRIZE { restricted = FALSE; ability = ABILITY_GORILLA_TACTICS; }
    PARAMETRIZE { restricted = TRUE; ability = ABILITY_GORILLA_TACTICS; }
    PARAMETRIZE { restricted = TRUE; ability = ABILITY_ZEN_MODE; }

    GIVEN {
        if (restricted)
            FlagSet(FLAG_RESTRICTED_MODE);
        else
            FlagClear(FLAG_RESTRICTED_MODE);
        PLAYER(SPECIES_DARMANITAN_GALAR) { Ability(ability); Item(ITEM_CHOICE_SCARF); Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(120); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); MOVE(opponent, MOVE_SPLASH); }
    } SCENE {
        if (restricted && ability == ABILITY_GORILLA_TACTICS) {
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SPLASH, opponent);
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        } else {
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SPLASH, opponent);
        }
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Restricted opponent Gorilla Tactics retains Choice Band", s16 damage)
{
    enum Item item;
    PARAMETRIZE { item = ITEM_NONE; }
    PARAMETRIZE { item = ITEM_CHOICE_BAND; }

    GIVEN {
        FlagSet(FLAG_RESTRICTED_MODE);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_DARMANITAN_GALAR) { Ability(ABILITY_GORILLA_TACTICS); Item(item); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Restricted opponent Gorilla Tactics retains Choice Scarf")
{
    GIVEN {
        FlagSet(FLAG_RESTRICTED_MODE);
        PLAYER(SPECIES_WOBBUFFET) { Speed(120); }
        OPPONENT(SPECIES_DARMANITAN_GALAR) { Ability(ABILITY_GORILLA_TACTICS); Item(ITEM_CHOICE_SCARF); Speed(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_SPLASH); MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SPLASH, player);
    }
}
