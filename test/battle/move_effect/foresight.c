#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    ASSUME(GetMoveEffect(MOVE_FORESIGHT) == EFFECT_FORESIGHT);
}

SINGLE_BATTLE_TEST("Foresight removes Ghost's type immunity to Normal and Fighting types")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_SCRATCH) == TYPE_NORMAL);
        ASSUME(GetMoveType(MOVE_LOW_KICK) == TYPE_FIGHTING);
        ASSUME(GetSpeciesType(SPECIES_GENGAR, 0) == TYPE_GHOST);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_FORESIGHT, MOVE_SCRATCH, MOVE_LOW_KICK); }
        OPPONENT(SPECIES_GENGAR) { Moves(MOVE_SPLASH); }
    } WHEN {
        TURN { MOVE(player, MOVE_FORESIGHT); MOVE(opponent, MOVE_SPLASH); }
        TURN { MOVE(player, MOVE_SCRATCH); MOVE(opponent, MOVE_SPLASH); }
        TURN { MOVE(player, MOVE_LOW_KICK); MOVE(opponent, MOVE_SPLASH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FORESIGHT, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_LOW_KICK, player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Foresight always hits unless the target is semi-invulnerable")
{
    bool32 semiInvulnerable = FALSE;
    PARAMETRIZE { semiInvulnerable = FALSE; }
    PARAMETRIZE { semiInvulnerable = TRUE; }

    GIVEN {
        ASSUME_STAT_CHANGE(MOVE_DOUBLE_TEAM, evasion: +1);
        ASSUME(GetMoveEffect(MOVE_FLY) == EFFECT_SEMI_INVULNERABLE);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_FORESIGHT, MOVE_SPLASH); Speed(10); }
        OPPONENT(SPECIES_SQUAWKABILLY) { Moves(MOVE_DOUBLE_TEAM, MOVE_FLY); Speed(20); }
    } WHEN {
        if (semiInvulnerable)
            TURN { MOVE(player, MOVE_FORESIGHT); MOVE(opponent, MOVE_FLY); }
        else
            TURN { MOVE(player, MOVE_FORESIGHT); MOVE(opponent, MOVE_DOUBLE_TEAM); }

        if (semiInvulnerable)
            TURN { MOVE(player, MOVE_SPLASH); SKIP_TURN(opponent); }
    } SCENE {
        if (semiInvulnerable) {
            MESSAGE("The opposing Squawkabilly avoided the attack!");
        } else {
            ANIMATION(ANIM_TYPE_MOVE, MOVE_DOUBLE_TEAM, opponent);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
            ANIMATION(ANIM_TYPE_MOVE, MOVE_FORESIGHT, player);
        }
    }
}

SINGLE_BATTLE_TEST("Foresight causes moves against the target to ignore positive evasion stat stages")
{
    PASSES_RANDOMLY(100, 100, RNG_ACCURACY);
    GIVEN {
        ASSUME_STAT_CHANGE(MOVE_DOUBLE_TEAM, evasion: +1);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_FORESIGHT, MOVE_SCRATCH); Speed(10); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_DOUBLE_TEAM, MOVE_SPLASH); Speed(20); }
    } WHEN {
        TURN { MOVE(player, MOVE_FORESIGHT); MOVE(opponent, MOVE_DOUBLE_TEAM); }
        TURN { MOVE(player, MOVE_SCRATCH); MOVE(opponent, MOVE_SPLASH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DOUBLE_TEAM, opponent);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FORESIGHT, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Foresight repeat override ignores the generational failure setting")
{
    u32 genConfig = GEN_2;
    PARAMETRIZE { genConfig = GEN_2; }
    PARAMETRIZE { genConfig = GEN_5; }
    GIVEN {
        WITH_CONFIG(B_FORESIGHT_FAIL, genConfig);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_FORESIGHT); }
        TURN { MOVE(player, MOVE_FORESIGHT); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FORESIGHT, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FORESIGHT, player);
        NOT MESSAGE("But it failed!");
    } THEN {
        EXPECT_EQ(player->statStages[STAT_ACC], DEFAULT_STAT_STAGE + 2);
    }
}

SINGLE_BATTLE_TEST("Foresight doesn't fail if the target is already under its effect (Gen 3-4)")
{
    u32 genConfig = GEN_3;
    PARAMETRIZE { genConfig = GEN_3; }
    PARAMETRIZE { genConfig = GEN_4; }
    GIVEN {
        WITH_CONFIG(B_FORESIGHT_FAIL, genConfig);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_FORESIGHT); }
        TURN { MOVE(player, MOVE_FORESIGHT); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FORESIGHT, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FORESIGHT, player);
        NOT MESSAGE("But it failed!");
    }
}

TO_DO_BATTLE_TEST("Foresight causes accuracy/evasion stat changes only between the user/target when the user's accuracy stage is less than the target's evasion stage (Gen 2)")
TO_DO_BATTLE_TEST("Foresight causes all moves against the target to ignore evasion stat changes (Gen 3)")
TO_DO_BATTLE_TEST("Foresight causes all moves against the target to ignore only positive evasion stat changes (Gen 4+)") // Eg. Doesn't ignore Sweet Scent
TO_DO_BATTLE_TEST("Foresight doesn't cause moves used against the target to always hit (Gen 2-3)")
TO_DO_BATTLE_TEST("Foresight causes moves used against the target to always hit (Gen 4+)")
TO_DO_BATTLE_TEST("Baton Pass passes Foresight's effect (Gen 2)");
TO_DO_BATTLE_TEST("Baton Pass doesn't pass Foresight's effect (Gen 3+)");

SINGLE_BATTLE_TEST("Zenmodeman: Foresight and Odor Sleuth raise the user's Accuracy", enum Move move)
{
    enum Move move;

    PARAMETRIZE { move = MOVE_FORESIGHT; }
    PARAMETRIZE { move = MOVE_ODOR_SLEUTH; }
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Moves(move); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
    } THEN {
        EXPECT_EQ(player->statStages[STAT_ACC], DEFAULT_STAT_STAGE + 1);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Foresight can repeat to raise Accuracy again")
{
    GIVEN {
        WITH_CONFIG(B_FORESIGHT_FAIL, GEN_9);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_FORESIGHT); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_FORESIGHT); }
        TURN { MOVE(player, MOVE_FORESIGHT); }
    } THEN {
        EXPECT_EQ(player->statStages[STAT_ACC], DEFAULT_STAT_STAGE + 2);
    }
}
