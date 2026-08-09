#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Zenmodeman: Cute Charm strengthens enticing debuffs only against the opposite gender", enum Gender targetGender, u8 expectedStage)
{
    enum Gender targetGender;
    u8 expectedStage;

    PARAMETRIZE { targetGender = MON_FEMALE; expectedStage = DEFAULT_STAT_STAGE - 3; }
    PARAMETRIZE { targetGender = MON_MALE; expectedStage = DEFAULT_STAT_STAGE - 2; }
    GIVEN {
        PLAYER(SPECIES_CLEFAIRY) { Gender(MON_MALE); Ability(ABILITY_CUTE_CHARM); }
        OPPONENT(SPECIES_WOBBUFFET) { Gender(targetGender); }
    } WHEN {
        TURN { MOVE(player, MOVE_CHARM); }
    } THEN {
        EXPECT_EQ(gBattleMons[B_POSITION_OPPONENT_LEFT].statStages[STAT_ATK], expectedStage);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Frisk makes item-interacting attacks bypass accuracy checks")
{
    GIVEN {
        ASSUME(GetMoveAccuracy(MOVE_POLTERGEIST) < 100);
        PLAYER(SPECIES_SHUPPET) { Ability(ABILITY_FRISK); }
        OPPONENT(SPECIES_WOBBUFFET) { Item(ITEM_ORAN_BERRY); }
    } WHEN {
        TURN { MOVE(player, MOVE_POLTERGEIST, hit: FALSE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POLTERGEIST, player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Frisk does not guarantee ordinary inaccurate attacks")
{
    GIVEN {
        ASSUME(!IsItemInteractingMove(MOVE_ROCK_SLIDE));
        PLAYER(SPECIES_SHUPPET) { Ability(ABILITY_FRISK); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_ROCK_SLIDE, hit: FALSE); }
    } SCENE {
        MESSAGE("The opposing Wobbuffet avoided the attack!");
    }
}
