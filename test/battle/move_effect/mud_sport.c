#include "global.h"
#include "test/battle.h"

TO_DO_BATTLE_TEST("TODO: Write Mud Sport (Move Effect) test titles")
#include "global.h"
#include "test/battle.h"

ASSUMPTIONS {
    ASSUME(GetMoveEffect(MOVE_MUD_SPORT) == EFFECT_MUD_SPORT);
}

SINGLE_BATTLE_TEST("Zenmodeman: Mud Sport prevents paralysis from Thunder Wave")
{
GIVEN {
        // ASSUME(GetMoveEffect(MOVE_THUNDER_WAVE) == EFFECT_PARALYZE); No longer holds after change to the effect
        ASSUME(GetMoveEffect(MOVE_SWORDS_DANCE) == EFFECT_ATTACK_UP_2);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_MUD_SPORT); }
        TURN { MOVE(player, MOVE_THUNDER_WAVE); }
        TURN { MOVE(player, MOVE_SWORDS_DANCE); }
    } SCENE {
        NOT STATUS_ICON(opponent, paralysis: TRUE);

        //This is solely to confirm that Thunder Wave against Mud Sport did not freeze the game
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SWORDS_DANCE, player);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Mud Sport prevents paralysis from Electric-type secondary effects")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_MUD_SPORT) == EFFECT_MUD_SPORT);
        ASSUME(MoveHasAdditionalEffectWithChance(MOVE_NUZZLE, MOVE_EFFECT_PARALYSIS, 100));
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_MUD_SPORT); }
        TURN { MOVE(opponent, MOVE_NUZZLE); }
    } SCENE {
        NOT STATUS_ICON(player, paralysis: TRUE);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Mud Sport does not block paralysis from non-Electric secondary effects")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_BODY_SLAM) == TYPE_NORMAL);
        ASSUME(MoveHasAdditionalEffect(MOVE_BODY_SLAM, MOVE_EFFECT_PARALYSIS));
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_MUD_SPORT); }
        TURN { MOVE(opponent, MOVE_BODY_SLAM, WITH_RNG(RNG_SECONDARY_EFFECT, TRUE)); }
    } SCENE {
        STATUS_ICON(player, paralysis: TRUE);
    }
}

SINGLE_BATTLE_TEST("Mud Sport reduces the damage of Electric Type moves by 50% (Gen3-4) or 67% (Gen5+)")
{
    u32 config;
    s16 playerDmg[2];
    s16 opponentDmg[2];
    PARAMETRIZE { config = GEN_4; }
    PARAMETRIZE { config = GEN_5; }
    GIVEN {
        WITH_CONFIG(B_SPORT_DMG_REDUCTION, config);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SHOCK_WAVE); MOVE(opponent, MOVE_SHOCK_WAVE); }
        TURN { MOVE(player, MOVE_MUD_SPORT); }
        TURN { MOVE(player, MOVE_SHOCK_WAVE); MOVE(opponent, MOVE_SHOCK_WAVE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SHOCK_WAVE, player);
        HP_BAR(opponent, captureDamage: &opponentDmg[0]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SHOCK_WAVE, opponent);
        HP_BAR(player, captureDamage: &playerDmg[0]);

        ANIMATION(ANIM_TYPE_MOVE, MOVE_MUD_SPORT, player);

        ANIMATION(ANIM_TYPE_MOVE, MOVE_SHOCK_WAVE, player);
        HP_BAR(opponent, captureDamage: &opponentDmg[1]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SHOCK_WAVE, opponent);
        HP_BAR(player, captureDamage: &playerDmg[1]);

    } THEN {
        if (config >= GEN_5) {
            EXPECT_MUL_EQ(opponentDmg[0], Q_4_12(0.33), opponentDmg[1]);
            EXPECT_MUL_EQ(playerDmg[0], Q_4_12(0.33), playerDmg[1]);
        }
        else {
            EXPECT_MUL_EQ(opponentDmg[0], Q_4_12(0.5), opponentDmg[1]);
            EXPECT_MUL_EQ(playerDmg[0], Q_4_12(0.5), playerDmg[1]);
        }
    }
}
