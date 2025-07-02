#include "global.h"
#include "test/battle.h"

TO_DO_BATTLE_TEST("Anticipation causes notifies if an opponent has a super-effective move");
TO_DO_BATTLE_TEST("Anticipation causes notifies if an opponent has a One-hit KO move");
TO_DO_BATTLE_TEST("Anticipation causes notifies if an opponent has a Self-Destruct or Explosion (Gen4)");
TO_DO_BATTLE_TEST("Anticipation treats Self-Destruct and Explosion like all other Normal types (Gen5+)");

TO_DO_BATTLE_TEST("Anticipation considers Scrappy and Normalize into their effectiveness (Gen4)");
TO_DO_BATTLE_TEST("Anticipation doesn't consider Scrappy and Normalize into their effectiveness (Gen5+)");
TO_DO_BATTLE_TEST("Anticipation considers Gravity into their effectiveness (Gen4)");
TO_DO_BATTLE_TEST("Anticipation doesn't consider Gravity into their effectiveness (Gen5+)");
TO_DO_BATTLE_TEST("Anticipation doesn't trigger from Counter, Metal Burst or Mirror Coat (Gen4)");
TO_DO_BATTLE_TEST("Anticipation counts Counter, Metal Burst or Mirror Coat as attacking moves of their types (Gen5+)");
TO_DO_BATTLE_TEST("Anticipation considers Synchronoise as an ordinary Psychic-type move");
TO_DO_BATTLE_TEST("Anticipation considers Freeze-Dry as an ordinary Ice-type move");
TO_DO_BATTLE_TEST("Anticipation considers Flying Press as an ordinary Fighting-type move");
TO_DO_BATTLE_TEST("Anticipation considers Aura Wheel as an ordinary Electric-type move");
TO_DO_BATTLE_TEST("Anticipation considers Inverse Battle types"); //Check with Normal-type moves
TO_DO_BATTLE_TEST("Anticipation treats dynamic move types as their base type (Normal)"); // Judgment, Weather Ball, Natural Gift, Techno Blast, Revelation Dance, Multi Attack
TO_DO_BATTLE_TEST("Anticipation treats Hidden Power as Normal Type (Gen4-5)");
TO_DO_BATTLE_TEST("Anticipation treats Hidden Power as its dynamic type (Gen6+)");
TO_DO_BATTLE_TEST("Anticipation does not consider Strong Winds on type matchups");
TO_DO_BATTLE_TEST("Anticipation does not consider ate-abilities");

SINGLE_BATTLE_TEST("Zenmodeman: Anticipation has Solid Rock reduction when sent out against a SE move", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_ANTICIPATION; }
    PARAMETRIZE { ability = ABILITY_DRY_SKIN; }
    GIVEN {
        PLAYER(SPECIES_PIDGEY) {Moves(MOVE_WING_ATTACK, MOVE_CELEBRATE);}
        OPPONENT(SPECIES_AIPOM) {Moves(MOVE_BATON_PASS);}
        OPPONENT(SPECIES_TOXICROAK) { Ability(ability); Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN{MOVE(opponent, MOVE_BATON_PASS); SEND_OUT(opponent, 1);}
        TURN { MOVE(player, MOVE_WING_ATTACK); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[1].damage, UQ_4_12(0.75), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Anticipation has double reduction when sent out against a quad effective move", s16 damage)
{
    u32 ability;
    PARAMETRIZE { ability = ABILITY_ANTICIPATION; }
    PARAMETRIZE { ability = ABILITY_DRY_SKIN; }
    GIVEN {
        PLAYER(SPECIES_BRONZOR) {Moves(MOVE_CONFUSION, MOVE_CELEBRATE);}
        OPPONENT(SPECIES_AIPOM) {Moves(MOVE_BATON_PASS);}
        OPPONENT(SPECIES_TOXICROAK) { Ability(ability); Moves(MOVE_CELEBRATE);}
    } WHEN {
        TURN{MOVE(opponent, MOVE_BATON_PASS); SEND_OUT(opponent, 1);}
        TURN { MOVE(player, MOVE_CONFUSION); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[1].damage, UQ_4_12(0.565), results[0].damage);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Anticipation does not have reduction when the mon is sent out in a subsequent turn", s16 damage){
    u32 ability;
    PARAMETRIZE { ability = ABILITY_ANTICIPATION; }
    PARAMETRIZE { ability = ABILITY_DRY_SKIN; }
    GIVEN {
        PLAYER(SPECIES_MUDKIP) {HP(1); Moves(MOVE_TACKLE, MOVE_CELEBRATE);}
        PLAYER(SPECIES_BRONZOR) {Moves(MOVE_CONFUSION);}
        OPPONENT(SPECIES_AIPOM) {Moves(MOVE_BATON_PASS);}
        OPPONENT(SPECIES_TOXICROAK) { Ability(ability); Moves(MOVE_CELEBRATE, MOVE_POISON_JAB); }
    } WHEN {
        TURN{MOVE(opponent, MOVE_BATON_PASS); SEND_OUT(opponent, 1);}
        TURN { MOVE(opponent, MOVE_POISON_JAB); SEND_OUT(player, 1); }
        TURN { MOVE(player, MOVE_CONFUSION); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[1].damage, UQ_4_12(1.0), results[0].damage);
    }
}