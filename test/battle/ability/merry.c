#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Zenmodeman: Merry activates after Delibird uses a gifting move")
{
    GIVEN {
        ASSUME(IsGiftingMove(MOVE_PRESENT));
        PLAYER(SPECIES_DELIBIRD) { Ability(ABILITY_MERRY); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PRESENT); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_MERRY);
    } THEN {
        EXPECT(gBattleMons[B_POSITION_PLAYER_LEFT].volatiles.merry);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Merry activates from every custom gifting move", enum Move move)
{
    enum Move move;

    PARAMETRIZE { move = MOVE_PRESENT; }
    PARAMETRIZE { move = MOVE_HEAL_PULSE; }
    PARAMETRIZE { move = MOVE_BESTOW; }
    GIVEN {
        PLAYER(SPECIES_DELIBIRD) { Ability(ABILITY_MERRY); Item(ITEM_ORAN_BERRY); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(200); MaxHP(300); }
    } WHEN {
        TURN { MOVE(player, move); }
    } THEN {
        EXPECT(gBattleMons[B_POSITION_PLAYER_LEFT].volatiles.merry);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: activated Merry boosts damage by fifty percent", s16 damage)
{
    u32 j;
    enum Ability ability;
    s16 healing;
    PARAMETRIZE { j = 0; }
    PARAMETRIZE { j = 1; }
    GIVEN {
        ability = j == 0 ? ABILITY_KLUTZ : ABILITY_MERRY;
        PLAYER(SPECIES_DELIBIRD) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(300); MaxHP(400); }
    } WHEN {
        TURN { MOVE(player, MOVE_HEAL_PULSE); }
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HEAL_PULSE, player);
        HP_BAR(opponent, captureDamage: &healing);
        if (j == 1)
            ABILITY_POPUP(player, ABILITY_MERRY);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent, captureDamage: &results[j].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(1.5), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: activated Merry boosts accuracy and Speed")
{
    enum BattlerId playerId;
    enum BattlerId opponentId;

    GIVEN {
        PLAYER(SPECIES_DELIBIRD) { Ability(ABILITY_MERRY); Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(300); MaxHP(400); Speed(120); }
    } WHEN {
        TURN { MOVE(player, MOVE_HEAL_PULSE); }
        TURN { MOVE(player, MOVE_SCRATCH); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent);
    } THEN {
        playerId = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
        opponentId = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        EXPECT_EQ(GetTotalAccuracy(playerId, opponentId,
                                   MOVE_PRESENT, ABILITY_MERRY, ABILITY_NONE,
                                   HOLD_EFFECT_NONE, HOLD_EFFECT_NONE), 150);
    }
}
