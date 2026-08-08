#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Zenmodeman: Solar Core doubles special damage in sun", s16 damage)
{
    enum Move setup;
    PARAMETRIZE { setup = MOVE_CELEBRATE; }
    PARAMETRIZE { setup = MOVE_SUNNY_DAY; }
    GIVEN {
        ASSUME(GetMoveCategory(MOVE_HYPER_VOICE) == DAMAGE_CATEGORY_SPECIAL);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_SOLAR_CORE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, setup); MOVE(player, MOVE_HYPER_VOICE); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(2.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Solar Core does not boost physical damage in sun", s16 damage)
{
    enum Move setup;
    PARAMETRIZE { setup = MOVE_CELEBRATE; }
    PARAMETRIZE { setup = MOVE_SUNNY_DAY; }
    GIVEN {
        ASSUME(GetMoveCategory(MOVE_SCRATCH) == DAMAGE_CATEGORY_PHYSICAL);
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_SOLAR_CORE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, setup); MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Utility Umbrella suppresses Solar Core", s16 damage)
{
    enum Move setup;
    PARAMETRIZE { setup = MOVE_CELEBRATE; }
    PARAMETRIZE { setup = MOVE_SUNNY_DAY; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_SOLAR_CORE); Item(ITEM_UTILITY_UMBRELLA); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, setup); MOVE(player, MOVE_HYPER_VOICE); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Cloud Nine suppresses Solar Core", s16 damage)
{
    enum Move setup;
    PARAMETRIZE { setup = MOVE_CELEBRATE; }
    PARAMETRIZE { setup = MOVE_SUNNY_DAY; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_SOLAR_CORE); }
        OPPONENT(SPECIES_GOLDUCK) { Ability(ABILITY_CLOUD_NINE); }
    } WHEN {
        TURN { MOVE(opponent, setup); MOVE(player, MOVE_HYPER_VOICE); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Limber blocks Speed drops from status moves")
{
    GIVEN {
        ASSUME_STAT_CHANGE(MOVE_STRING_SHOT, speed: -2);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PERSIAN) { Ability(ABILITY_LIMBER); }
    } WHEN {
        TURN { MOVE(player, MOVE_STRING_SHOT); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_LIMBER);
        MESSAGE("The opposing Persian's Speed was not lowered!");
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_SPEED], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Limber blocks Speed drops from damaging moves")
{
    GIVEN {
        ASSUME_MOVE_EFFECT_STAT_CHANGE(MOVE_ROCK_TOMB, speed: -1);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PERSIAN) { Ability(ABILITY_LIMBER); }
    } WHEN {
        TURN { MOVE(player, MOVE_ROCK_TOMB); }
    } SCENE {
        HP_BAR(opponent);
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_SPEED], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Limber permits the user's own Speed drops")
{
    GIVEN {
        ASSUME_MOVE_EFFECT_STAT_CHANGE(MOVE_HAMMER_ARM, self: TRUE, speed: -1);
        PLAYER(SPECIES_PERSIAN) { Ability(ABILITY_LIMBER); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_HAMMER_ARM); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPEED], DEFAULT_STAT_STAGE - 1);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Inner Focus preserves Focus Punch after physical damage")
{
    GIVEN {
        PLAYER(SPECIES_ZUBAT) { Ability(ABILITY_INNER_FOCUS); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_FOCUS_PUNCH); MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        HP_BAR(player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FOCUS_PUNCH, player);
        HP_BAR(opponent);
        NOT MESSAGE("Zubat lost its focus and couldn't move!");
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Focus Punch still fails after damage without Inner Focus")
{
    GIVEN {
        PLAYER(SPECIES_ZUBAT) { Ability(ABILITY_INFILTRATOR); Speed(1); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); }
    } WHEN {
        TURN { MOVE(player, MOVE_FOCUS_PUNCH); MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        HP_BAR(player);
        MESSAGE("Zubat lost its focus and couldn't move!");
        NOT HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Tailwind lets Razor Wind attack without charging")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TAILWIND); }
        TURN { MOVE(player, MOVE_RAZOR_WIND); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TAILWIND, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_RAZOR_WIND, player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Truant makes Slack Off heal three quarters")
{
    GIVEN {
        PLAYER(SPECIES_SLAKING) { Ability(ABILITY_TRUANT); HP(1); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SLACK_OFF); }
    } THEN {
        EXPECT_EQ(player->hp, 76);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Slack Off retains half healing without Truant")
{
    GIVEN {
        PLAYER(SPECIES_SLAKING) { Ability(ABILITY_VITAL_SPIRIT); HP(1); MaxHP(100); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SLACK_OFF); }
    } THEN {
        EXPECT_EQ(player->hp, 51);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Refresh can cure its user's sleep")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Status1(STATUS1_SLEEP_TURN(3)); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_REFRESH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_REFRESH, player);
        STATUS_ICON(player, none: TRUE);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Refresh can cure its user's freeze")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Status1(STATUS1_FREEZE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_REFRESH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_REFRESH, player);
        STATUS_ICON(player, none: TRUE);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Refresh bypasses full paralysis")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Status1(STATUS1_PARALYSIS); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_REFRESH, WITH_RNG(RNG_PARALYSIS, 0)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_REFRESH, player);
        STATUS_ICON(player, none: TRUE);
        NOT MESSAGE("Wobbuffet is paralyzed! It can't move!");
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Big Pecks preserves positive Defense stages against critical hits", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_KEEN_EYE; }
    PARAMETRIZE { ability = ABILITY_BIG_PECKS; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PIDGEY) { Ability(ability); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_HARDEN); }
        TURN { MOVE(player, MOVE_SCRATCH, criticalHit: TRUE); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_GT(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Big Pecks preserves Reflect against critical physical hits", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_KEEN_EYE; }
    PARAMETRIZE { ability = ABILITY_BIG_PECKS; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PIDGEY) { Ability(ability); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_REFLECT); }
        TURN { MOVE(player, MOVE_SCRATCH, criticalHit: TRUE); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_GT(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Big Pecks preserves Aurora Veil against critical physical hits", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_KEEN_EYE; }
    PARAMETRIZE { ability = ABILITY_BIG_PECKS; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PIDGEY) { Ability(ability); }
    } WHEN {
        TURN { MOVE(player, MOVE_SNOWSCAPE); MOVE(opponent, MOVE_AURORA_VEIL); }
        TURN { MOVE(player, MOVE_SCRATCH, criticalHit: TRUE); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_GT(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Big Pecks does not preserve Aurora Veil against critical special hits", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_KEEN_EYE; }
    PARAMETRIZE { ability = ABILITY_BIG_PECKS; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PIDGEY) { Ability(ability); }
    } WHEN {
        TURN { MOVE(player, MOVE_SNOWSCAPE); MOVE(opponent, MOVE_AURORA_VEIL); }
        TURN { MOVE(player, MOVE_WATER_GUN, criticalHit: TRUE); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Big Pecks preserves positive Defense stages against Chip Away", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_KEEN_EYE; }
    PARAMETRIZE { ability = ABILITY_BIG_PECKS; }
    GIVEN {
        ASSUME(MoveIgnoresDefenseEvasionStages(MOVE_CHIP_AWAY));
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_PIDGEY) { Ability(ability); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_HARDEN); }
        TURN { MOVE(player, MOVE_CHIP_AWAY); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_GT(results[0].damage, results[1].damage);
    }
}
