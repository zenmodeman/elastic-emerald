#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveEffect(MOVE_DRAIN_DOUSE) == EFFECT_DRAIN_DOUSE);
}

SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse inflicts a status that causes attacks to heal percentage of damage dealt")
{
    s16 damage;
    s16 healed;
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) 
        OPPONENT(SPECIES_WOBBUFFET) {HP(1);}
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { MOVE(opponent, MOVE_MEGA_KICK); }
    } SCENE {
        // First turn - Drain Douse is used
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAIN_DOUSE, player);

        // Second turn - Opponent attacks and gets healing
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MEGA_KICK, opponent);
        HP_BAR(player, captureDamage: &damage);
        HP_BAR(opponent, captureDamage: &healed);
    } THEN {
        //33% because not poison or water
        EXPECT_MUL_EQ(damage, Q_4_12(-0.33), healed);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse healing is inverted when attacking a Liquid Ooze Pokémon")
{
    s16 targetDamage;
    s16 attackerDamage;
    GIVEN {
        PLAYER(SPECIES_TENTACOOL) { Ability(ABILITY_LIQUID_OOZE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { MOVE(opponent, MOVE_MEGA_KICK); }
    } SCENE {
        // First turn - Drain Douse is used
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAIN_DOUSE, player);
        
        // Second turn - Opponent attacks and loses HP due to Liquid Ooze
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MEGA_KICK, opponent);
        HP_BAR(player, captureDamage: &targetDamage);
        HP_BAR(opponent, captureDamage: &attackerDamage);
    } THEN {
        //2/3rds because of Polison
        EXPECT_MUL_EQ(targetDamage, Q_4_12(0.67), attackerDamage);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse heals for two thirds when damaging a Poison-type target")
{
    s16 damage;
    s16 healed;

    GIVEN {
        PLAYER(SPECIES_NIDORINO) { Ability(ABILITY_POISON_POINT); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); MaxHP(200); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { MOVE(opponent, MOVE_MEGA_KICK); }
    } SCENE {
        HP_BAR(player, captureDamage: &damage);
        HP_BAR(opponent, captureDamage: &healed);
    } THEN {
        EXPECT_MUL_EQ(damage, Q_4_12(0.67), -healed);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse does not heal when the affected attacker deals no damage")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); MaxHP(200); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { MOVE(opponent, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(opponent->hp, 1);
    }
}


SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse healing stacks with a move's native drain")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_ABSORB) == EFFECT_ABSORB);
        PLAYER(SPECIES_WOBBUFFET) { HP(200); MaxHP(200); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); MaxHP(200); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { MOVE(opponent, MOVE_ABSORB); }
    } THEN {
        u32 damage = 200 - player->hp;
        EXPECT_EQ(opponent->hp, 1 + damage / 2 + damage * 33 / 100);
    }
}

DOUBLE_BATTLE_TEST("Zenmodeman: Drain Douse heals separately for each target hit by a spread move")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(200); MaxHP(200); }
        PLAYER(SPECIES_WYNAUT) { HP(200); MaxHP(200); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); MaxHP(400); }
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_DRAIN_DOUSE, target: opponentLeft); }
        TURN { MOVE(opponentLeft, MOVE_EARTHQUAKE); }
    } THEN {
        u32 damageLeft = 200 - playerLeft->hp;
        u32 damageRight = 200 - playerRight->hp;
        EXPECT_EQ(opponentLeft->hp, 1 + damageLeft * 33 / 100 + damageRight * 33 / 100);
    }
}

DOUBLE_BATTLE_TEST("Zenmodeman: Drain Douse handles normal and Liquid Ooze spread targets independently")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(200); MaxHP(200); }
        PLAYER(SPECIES_TENTACOOL) { HP(200); MaxHP(200); Ability(ABILITY_LIQUID_OOZE); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(100); MaxHP(400); }
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_DRAIN_DOUSE, target: opponentLeft); }
        TURN { MOVE(opponentLeft, MOVE_EARTHQUAKE); }
    } THEN {
        u32 damageNormal = 200 - playerLeft->hp;
        u32 damageOoze = 200 - playerRight->hp;
        EXPECT_EQ(opponentLeft->hp, 100 + damageNormal * 33 / 100 - damageOoze * 67 / 100);
    }
}

DOUBLE_BATTLE_TEST("Zenmodeman: Drain Douse healing only uses damage from the affected attacker's move")
{
    s16 damage;
    s16 healed;

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(200); MaxHP(200); }
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); MaxHP(200); }
        OPPONENT(SPECIES_WYNAUT) { HP(1); MaxHP(200); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_DRAIN_DOUSE, target: opponentLeft); }
        TURN {
            MOVE(opponentLeft, MOVE_TACKLE, target: playerLeft);
            MOVE(opponentRight, MOVE_TACKLE, target: playerLeft);
        }
    } SCENE {
        HP_BAR(playerLeft, captureDamage: &damage);
        HP_BAR(opponentLeft, captureDamage: &healed);
    } THEN {
        EXPECT_MUL_EQ(damage, Q_4_12(0.33), -healed);
        EXPECT_EQ(opponentRight->hp, 1);
    }
}

DOUBLE_BATTLE_TEST("Zenmodeman: Drain Douse spread healing ignores a protected target")
{
    s16 damage;
    s16 healed;

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(200); MaxHP(200); }
        PLAYER(SPECIES_WYNAUT) { HP(200); MaxHP(200); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); MaxHP(200); }
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_DRAIN_DOUSE, target: opponentLeft); }
        TURN {
            MOVE(playerLeft, MOVE_PROTECT);
            MOVE(opponentLeft, MOVE_EARTHQUAKE);
        }
    } SCENE {
        HP_BAR(playerRight, captureDamage: &damage);
        HP_BAR(opponentLeft, captureDamage: &healed);
    } THEN {
        EXPECT_MUL_EQ(damage, Q_4_12(0.33), -healed);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse at full HP reports the drain without increasing HP")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(100); HP(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { MOVE(opponent, MOVE_TACKLE); }
    } SCENE {
        MESSAGE("The opposing Wobbuffet drained energy with its liquid!");
    } THEN {
        EXPECT_EQ(opponent->hp, 100);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse Liquid Ooze still damages an attacker at full HP")
{
    GIVEN {
        PLAYER(SPECIES_TENTACOOL) { Ability(ABILITY_LIQUID_OOZE); }
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(100); HP(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { MOVE(opponent, MOVE_TACKLE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_LIQUID_OOZE);
        MESSAGE("The opposing Wobbuffet sucked up the liquid ooze!");
    } THEN {
        EXPECT_LT(opponent->hp, 100);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse heals for half the damage dealt to a Water-type target")
{
    GIVEN {
        PLAYER(SPECIES_SQUIRTLE) { HP(200); MaxHP(200); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); MaxHP(200); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { MOVE(opponent, MOVE_MEGA_KICK); }
    } THEN {
        u32 damage = 200 - player->hp;
        EXPECT_EQ(opponent->hp, 1 + damage / 2);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse uses the Poison rate for a Poison Water target")
{
    GIVEN {
        PLAYER(SPECIES_TENTACOOL) { HP(200); MaxHP(200); Ability(ABILITY_CLEAR_BODY); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); MaxHP(200); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { MOVE(opponent, MOVE_MEGA_KICK); }
    } THEN {
        u32 damage = 200 - player->hp;
        EXPECT_EQ(opponent->hp, 1 + damage * 67 / 100);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse receives the custom 40 percent Big Root boost")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(200); MaxHP(200); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); MaxHP(300); Item(ITEM_BIG_ROOT); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { MOVE(opponent, MOVE_MEGA_KICK); }
    } THEN {
        u32 damage = 200 - player->hp;
        u32 baseDrain = damage * 33 / 100;
        EXPECT_EQ(opponent->hp, 1 + baseDrain * 140 / 100);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Heal Block suppresses Drain Douse recovery")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_HEAL_BLOCK) == EFFECT_HEAL_BLOCK);
        PLAYER(SPECIES_WOBBUFFET) { Speed(200); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); MaxHP(200); Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { MOVE(player, MOVE_HEAL_BLOCK); MOVE(opponent, MOVE_MEGA_KICK); }
    } THEN {
        EXPECT_EQ(opponent->hp, 1);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Magic Guard blocks Drain Douse Liquid Ooze damage")
{
    GIVEN {
        PLAYER(SPECIES_TENTACOOL) { Ability(ABILITY_LIQUID_OOZE); }
        OPPONENT(SPECIES_CLEFFA) { HP(100); MaxHP(100); Ability(ABILITY_MAGIC_GUARD); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { MOVE(opponent, MOVE_MEGA_KICK); }
    } THEN {
        EXPECT_EQ(opponent->hp, 100);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse only heals from the HP removed by a lethal hit")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(10); MaxHP(200); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); MaxHP(200); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { MOVE(opponent, MOVE_MEGA_KICK); }
    } THEN {
        EXPECT_EQ(player->hp, 0);
        EXPECT_EQ(opponent->hp, 4);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse and native drain both invert against Liquid Ooze")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_ABSORB) == EFFECT_ABSORB);
        PLAYER(SPECIES_TENTACOOL) { HP(200); MaxHP(200); Ability(ABILITY_LIQUID_OOZE); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(100); MaxHP(200); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { MOVE(opponent, MOVE_ABSORB); }
    } THEN {
        u32 damage = 200 - player->hp;
        EXPECT_EQ(opponent->hp, 100 - damage / 2 - damage * 67 / 100);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse fails when the target is already doused")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAIN_DOUSE, player);
        MESSAGE("But it failed!");
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse is cleared when the affected battler switches out")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(200); MaxHP(200); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); MaxHP(200); }
        OPPONENT(SPECIES_WYNAUT);
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { SWITCH(opponent, 1); }
        TURN { SWITCH(opponent, 0); }
        TURN { MOVE(opponent, MOVE_MEGA_KICK); }
    } THEN {
        EXPECT_EQ(opponent->hp, 1);
    }
}

DOUBLE_BATTLE_TEST("Zenmodeman: Drain Douse does not drain damage dealt to the attacker's ally")
{
    GIVEN {
        PLAYER(SPECIES_GASTLY);
        PLAYER(SPECIES_HAUNTER);
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); MaxHP(200); }
        OPPONENT(SPECIES_WYNAUT) { HP(200); MaxHP(200); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_DRAIN_DOUSE, target: opponentLeft); }
        TURN { MOVE(opponentLeft, MOVE_EARTHQUAKE); }
    } THEN {
        EXPECT_LT(opponentRight->hp, 200);
        EXPECT_EQ(opponentLeft->hp, 1);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse does not heal from damage dealt to a Substitute")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(200); MaxHP(200); Speed(200); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); MaxHP(200); Speed(1); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { MOVE(player, MOVE_SUBSTITUTE); MOVE(opponent, MOVE_MEGA_KICK); }
    } THEN {
        EXPECT_EQ(opponent->hp, 1);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse does not heal from a Wonder Guard immunity")
{
    GIVEN {
        PLAYER(SPECIES_SHEDINJA) { Ability(ABILITY_WONDER_GUARD); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); MaxHP(200); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { MOVE(opponent, MOVE_TACKLE); }
    } THEN {
        EXPECT_EQ(opponent->hp, 1);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Drain Douse heals after a multi-hit attack")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(200); MaxHP(200); }
        OPPONENT(SPECIES_WOBBUFFET) { HP(1); MaxHP(200); }
    } WHEN {
        TURN { MOVE(player, MOVE_DRAIN_DOUSE); }
        TURN { MOVE(opponent, MOVE_FURY_SWIPES); }
    } THEN {
        EXPECT_GT(opponent->hp, 1);
    }
}
