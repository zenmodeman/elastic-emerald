#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Effect Spore only inflicts status on contact")
{
    enum Move move;

    PARAMETRIZE { move = MOVE_SCRATCH; }
    PARAMETRIZE { move = MOVE_SWIFT; }
    GIVEN {
        ASSUME(MoveMakesContact(MOVE_SCRATCH));
        ASSUME(!MoveMakesContact(MOVE_SWIFT));
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_BRELOOM) { Ability(ABILITY_EFFECT_SPORE); }
    } WHEN {
        TURN { MOVE(player, move, WITH_RNG(RNG_EFFECT_SPORE, 1)); }
        TURN {}
    } SCENE {
        if (MoveMakesContact(move)) {
            ABILITY_POPUP(opponent, ABILITY_EFFECT_SPORE);
            ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PSN, player);
            MESSAGE("Wobbuffet was poisoned!");
            STATUS_ICON(player, poison: TRUE);
        } else {
            NONE_OF {
                ABILITY_POPUP(opponent, ABILITY_EFFECT_SPORE);
                ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PSN, player);
                MESSAGE("Wobbuffet was poisoned!");
                STATUS_ICON(player, poison: TRUE);
            }
        }
    }
}

SINGLE_BATTLE_TEST("Effect Spore causes poison 3.3% (Gen3), 10% (Gen4) and 9% (Gen5+) of the time")
{
    u32 config, passes, trials;
    PARAMETRIZE { config = GEN_3; passes = 1; trials = 30;  } // 3.3%
    PARAMETRIZE { config = GEN_4; passes = 1; trials = 10;  } // 10%
    PARAMETRIZE { config = GEN_5; passes = 9; trials = 100; } // 9%
    PASSES_RANDOMLY(passes, trials, RNG_EFFECT_SPORE);
    GIVEN {
        WITH_CONFIG(B_ABILITY_TRIGGER_CHANCE, config);
        ASSUME(MoveMakesContact(MOVE_SCRATCH));
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_BRELOOM) { Ability(ABILITY_EFFECT_SPORE); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
        TURN {}
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_EFFECT_SPORE);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PSN, player);
        MESSAGE("Wobbuffet was poisoned!");
        STATUS_ICON(player, poison: TRUE);
    }
}

SINGLE_BATTLE_TEST("Effect Spore causes paralysis 3.3% (Gen3) and 10% (Gen4+) of the time")
{
    u32 config, passes, trials;
    PARAMETRIZE { config = GEN_3; passes = 1; trials = 30; } // 3.3%
    PARAMETRIZE { config = GEN_4; passes = 1; trials = 10; } // 10%
    PARAMETRIZE { config = GEN_5; passes = 1; trials = 10; } // 10%
    PASSES_RANDOMLY(passes, trials, RNG_EFFECT_SPORE);
    GIVEN {
        WITH_CONFIG(B_ABILITY_TRIGGER_CHANCE, config);
        ASSUME(MoveMakesContact(MOVE_SCRATCH));
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_BRELOOM) { Ability(ABILITY_EFFECT_SPORE); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
        TURN {}
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_EFFECT_SPORE);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PRZ, player);
        MESSAGE("Wobbuffet is paralyzed, so it may be unable to move!");
        STATUS_ICON(player, paralysis: TRUE);
    }
}

SINGLE_BATTLE_TEST("Effect Spore causes sleep 3.3% (Gen3), 10% (Gen4) and 11% (Gen5+) of the time")
{
    u32 config, passes, trials;
    PARAMETRIZE { config = GEN_3; passes = 1;  trials = 30; }  // 3.3%
    PARAMETRIZE { config = GEN_4; passes = 1;  trials = 10; }  // 10%
    PARAMETRIZE { config = GEN_5; passes = 11; trials = 100; } // 11%
    PASSES_RANDOMLY(passes, trials, RNG_EFFECT_SPORE);
    GIVEN {
        WITH_CONFIG(B_ABILITY_TRIGGER_CHANCE, config);
        ASSUME(MoveMakesContact(MOVE_SCRATCH));
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_BRELOOM) { Ability(ABILITY_EFFECT_SPORE); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
        TURN {}
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_EFFECT_SPORE);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_SLP, player);
        MESSAGE("Wobbuffet fell asleep!");
        STATUS_ICON(player, sleep: TRUE);
    }
}

SINGLE_BATTLE_TEST("Effect Spore will check if it can inflict status onto attacker, not itself")
{
    u32 config, passes, trials;
    PARAMETRIZE { config = GEN_3; passes = 1;  trials = 30; }  // 3.3%
    PARAMETRIZE { config = GEN_4; passes = 1;  trials = 10; }  // 10%
    PARAMETRIZE { config = GEN_5; passes = 11; trials = 100; } // 11%
    PASSES_RANDOMLY(passes, trials, RNG_EFFECT_SPORE);
    GIVEN {
        WITH_CONFIG(B_ABILITY_TRIGGER_CHANCE, config);
        ASSUME(MoveMakesContact(MOVE_SCRATCH));
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_BRELOOM) { Status1(STATUS1_BURN); Ability(ABILITY_EFFECT_SPORE); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_EFFECT_SPORE);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_SLP, player);
        MESSAGE("Wobbuffet fell asleep!");
        STATUS_ICON(player, sleep: TRUE);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Effect Spore remaps a blocked proc to another valid status")
{
    GIVEN {
        WITH_CONFIG(B_ABILITY_TRIGGER_CHANCE, GEN_5);
        ASSUME(MoveMakesContact(MOVE_SCRATCH));
        PLAYER(SPECIES_TOXEL);
        OPPONENT(SPECIES_BRELOOM) { Ability(ABILITY_EFFECT_SPORE); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH, WITH_RNG(RNG_EFFECT_SPORE, 0)); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_EFFECT_SPORE);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_SLP, player);
        MESSAGE("Toxel fell asleep!");
        STATUS_ICON(player, sleep: TRUE);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Effect Spore does not count contact attempts when no status can be inflicted")
{
    GIVEN {
        WITH_CONFIG(B_ABILITY_TRIGGER_CHANCE, GEN_5);
        ASSUME(MoveMakesContact(MOVE_SCRATCH));
        PLAYER(SPECIES_TOXEL) { Ability(ABILITY_INSOMNIA); }
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_BRELOOM) { Ability(ABILITY_EFFECT_SPORE); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH, WITH_RNG(RNG_EFFECT_SPORE, 0)); }
        TURN { MOVE(player, MOVE_SCRATCH, WITH_RNG(RNG_EFFECT_SPORE, 0)); }
        TURN { MOVE(player, MOVE_SCRATCH, WITH_RNG(RNG_EFFECT_SPORE, 0)); }
        TURN { SWITCH(player, 1); }
        TURN { MOVE(player, MOVE_SCRATCH, WITH_RNG(RNG_EFFECT_SPORE, 30)); }
    } SCENE {
        NONE_OF {
            ABILITY_POPUP(opponent, ABILITY_EFFECT_SPORE);
            ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PSN, player);
            ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PRZ, player);
            ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_SLP, player);
            STATUS_ICON(player, poison: TRUE);
            STATUS_ICON(player, paralysis: TRUE);
            STATUS_ICON(player, sleep: TRUE);
        }
    }
}
