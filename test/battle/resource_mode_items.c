#include "global.h"
#include "battle_util.h"
#include "event_data.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Zenmodeman: Non-Resource Mode restores a consumed held item after battle")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { MaxHP(100); HP(51); Item(ITEM_SITRUS_BERRY); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SCRATCH); }
    } THEN {
        EXPECT_EQ(player->item, ITEM_NONE);
        TryRestoreHeldItems();
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HELD_ITEM), ITEM_SITRUS_BERRY);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Resource Mode spends a normally consumed held item")
{
    GIVEN {
        FLAG_SET(FLAG_RESOURCE_MODE);
        PLAYER(SPECIES_WOBBUFFET) { MaxHP(100); HP(51); Item(ITEM_SITRUS_BERRY); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SCRATCH); }
    } THEN {
        EXPECT_EQ(player->item, ITEM_NONE);
        TryRestoreHeldItems();
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HELD_ITEM), ITEM_NONE);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Resource Mode restores a Flinged held item after battle")
{
    GIVEN {
        FLAG_SET(FLAG_RESOURCE_MODE);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_POISON_BARB); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_FLING); }
    } THEN {
        EXPECT_EQ(player->item, ITEM_NONE);
        TryRestoreHeldItems();
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HELD_ITEM), ITEM_POISON_BARB);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Resource Mode restores a Knocked Off held item after battle")
{
    GIVEN {
        FLAG_SET(FLAG_RESOURCE_MODE);
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_SITRUS_BERRY); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_KNOCK_OFF); }
    } THEN {
        EXPECT_EQ(player->item, ITEM_NONE);
        TryRestoreHeldItems();
        EXPECT_EQ(GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HELD_ITEM), ITEM_SITRUS_BERRY);
    }
}
