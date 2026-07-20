#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Zenmodeman: Honey Gather grants Honey at the end of the turn")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_HONEY].holdEffect == HOLD_EFFECT_RESTORE_PCT_HP);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_COMBEE) { Ability(ABILITY_HONEY_GATHER); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ABILITY_POPUP(opponent, ABILITY_HONEY_GATHER);
        MESSAGE("The opposing Combee found one Honey!");
    } THEN {
        EXPECT_EQ(opponent->item, ITEM_HONEY);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Honey Gather grants and immediately uses Honey if its HP is low enough")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_HONEY].holdEffect == HOLD_EFFECT_RESTORE_PCT_HP);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_COMBEE) { MaxHP(100); HP(75); Ability(ABILITY_HONEY_GATHER); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ABILITY_POPUP(opponent, ABILITY_HONEY_GATHER);
        MESSAGE("The opposing Combee found one Honey!");
    } THEN {
        EXPECT_EQ(opponent->item, ITEM_NONE);
        EXPECT_GT(opponent->hp, 75);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Honey Gather does not grant Honey if the battler already has an item")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_HONEY].holdEffect == HOLD_EFFECT_RESTORE_PCT_HP);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_COMBEE) { Ability(ABILITY_HONEY_GATHER); Item(ITEM_ORAN_BERRY); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        NOT ABILITY_POPUP(opponent, ABILITY_HONEY_GATHER);
    } THEN {
        EXPECT_EQ(opponent->item, ITEM_ORAN_BERRY);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Honey Gather keeps newly found Honey above the 75 percent activation threshold")
{
    GIVEN {
        ASSUME(gItemsInfo[ITEM_HONEY].holdEffect == HOLD_EFFECT_RESTORE_PCT_HP);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_COMBEE) { MaxHP(100); HP(76); Ability(ABILITY_HONEY_GATHER); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(opponent->item, ITEM_HONEY);
        EXPECT_EQ(opponent->hp, 76);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Suppressed Honey Gather does not create Honey")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_GASTRO_ACID) == EFFECT_GASTRO_ACID);
        PLAYER(SPECIES_WOBBUFFET) { Speed(200); }
        OPPONENT(SPECIES_COMBEE) { Speed(1); Ability(ABILITY_HONEY_GATHER); }
    } WHEN {
        TURN { MOVE(player, MOVE_GASTRO_ACID); MOVE(opponent, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(opponent->item, ITEM_NONE);
    }
}
