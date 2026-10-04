#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Elastic-tests: Color Change changes type before an incoming move resolves")
{
    GIVEN {
        ASSUME(GetSpeciesType(SPECIES_KECLEON, 0) != TYPE_PSYCHIC && GetSpeciesType(SPECIES_KECLEON, 1) != TYPE_PSYCHIC);
        ASSUME(GetMoveType(MOVE_PSYWAVE) == TYPE_PSYCHIC);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_KECLEON) { Ability(ABILITY_COLOR_CHANGE); }
    } WHEN {
        TURN { MOVE(player, MOVE_PSYWAVE); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_COLOR_CHANGE);
        MESSAGE("The opposing Kecleon's type changed to Psychic!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PSYWAVE, player);
    }
}

SINGLE_BATTLE_TEST("Color Change does not change the type when hit by a move that's the same type as itself")
{
    GIVEN {
        ASSUME(GetSpeciesType(SPECIES_KECLEON, 0) == TYPE_NORMAL || GetSpeciesType(SPECIES_KECLEON, 1) == TYPE_NORMAL);
        ASSUME(GetMoveType(MOVE_SCRATCH) == TYPE_NORMAL);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_KECLEON) { Ability(ABILITY_COLOR_CHANGE); }
    } WHEN {
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        NONE_OF {
            ABILITY_POPUP(opponent, ABILITY_COLOR_CHANGE);
            MESSAGE("The opposing Kecleon's Color Change made it the Normal type!");
        }
    }
}

SINGLE_BATTLE_TEST("Color Change does not change the type of a dual-type Pokemon when hit by a move that shares its primary type")
{
    GIVEN {
        PLAYER(SPECIES_KECLEON) { Ability(ABILITY_COLOR_CHANGE); }
        OPPONENT(SPECIES_SLOWBRO);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SKILL_SWAP); MOVE(player, MOVE_PSYCHO_CUT); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SKILL_SWAP, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PSYCHO_CUT, player);
        NONE_OF {
            ABILITY_POPUP(opponent, ABILITY_COLOR_CHANGE);
            MESSAGE("The opposing Slowbro's Color Change made it the Psychic type!");
        }
    }
}

SINGLE_BATTLE_TEST("Color Change does not change the type of a dual-type Pokemon when hit by a move that shares its secondary type")
{
    GIVEN {
        PLAYER(SPECIES_KECLEON) { Ability(ABILITY_COLOR_CHANGE); }
        OPPONENT(SPECIES_SLOWBRO);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SKILL_SWAP); MOVE(player, MOVE_PSYCHO_CUT); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SKILL_SWAP, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PSYCHO_CUT, player);
        NONE_OF {
            ABILITY_POPUP(opponent, ABILITY_COLOR_CHANGE);
            MESSAGE("The opposing Slowbro's Color Change made it the Psychic type!");
        }
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Color Change uses the Electrify-modified type before move resolution")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_KECLEON) { Ability(ABILITY_COLOR_CHANGE); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_ELECTRIFY); MOVE(player, MOVE_PSYCHO_CUT); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_COLOR_CHANGE);
        MESSAGE("The opposing Kecleon's type changed to Electric!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PSYCHO_CUT, player);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Color Change activates before Future Sight resolves")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_KECLEON) { Ability(ABILITY_COLOR_CHANGE); }
    } WHEN {
        TURN { MOVE(player, MOVE_FUTURE_SIGHT); }
        TURN {}
        TURN {}
    } SCENE {
        MESSAGE("The opposing Kecleon took the Future Sight attack!");
        ABILITY_POPUP(opponent, ABILITY_COLOR_CHANGE);
        MESSAGE("The opposing Kecleon's type changed to Psychic!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FUTURE_SIGHT, player);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Color Change activates before Doom Desire resolves")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_KECLEON) { Ability(ABILITY_COLOR_CHANGE); }
    } WHEN {
        TURN { MOVE(player, MOVE_DOOM_DESIRE); }
        TURN {}
        TURN {}
    } SCENE {
        MESSAGE("The opposing Kecleon took the Doom Desire attack!");
        ABILITY_POPUP(opponent, ABILITY_COLOR_CHANGE);
        MESSAGE("The opposing Kecleon's type changed to Steel!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DOOM_DESIRE, player);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Color Change uses Electrify's type before a delayed attack resolves")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_KECLEON) { Ability(ABILITY_COLOR_CHANGE); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_CELEBRATE); MOVE(player, MOVE_FUTURE_SIGHT); }
        TURN {}
        TURN { MOVE(opponent, MOVE_ELECTRIFY); }
    } SCENE {
        MESSAGE("The opposing Kecleon took the Future Sight attack!");
        ABILITY_POPUP(opponent, ABILITY_COLOR_CHANGE);
        MESSAGE("The opposing Kecleon's type changed to Electric!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FUTURE_SIGHT, player);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Color Change uses Normalize's type before a delayed attack resolves")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_NORMALIZE); }
        OPPONENT(SPECIES_KECLEON) { Ability(ABILITY_COLOR_CHANGE); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_CELEBRATE); MOVE(player, MOVE_FUTURE_SIGHT); }
        TURN { MOVE(player, MOVE_SOAK); }
        TURN {}
    } SCENE {
        MESSAGE("Wobbuffet used Soak!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SOAK, player);
        MESSAGE("The opposing Kecleon transformed into the Water type!");
        MESSAGE("The opposing Kecleon took the Future Sight attack!");
        ABILITY_POPUP(opponent, ABILITY_COLOR_CHANGE);
        MESSAGE("The opposing Kecleon's type changed to Normal!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FUTURE_SIGHT, player);
    }
}

SINGLE_BATTLE_TEST("Color Change does not change the type to Normal when a Pokemon is hit by Struggle")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_KECLEON) { Ability(ABILITY_COLOR_CHANGE); }
    } WHEN {
        TURN { MOVE(player, MOVE_SOAK); }
        TURN { MOVE(player, MOVE_STRUGGLE); }
        TURN {}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SOAK, player);
        MESSAGE("The opposing Kecleon transformed into the Water type!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STRUGGLE, player);
        NONE_OF {
            ABILITY_POPUP(opponent, ABILITY_COLOR_CHANGE);
            MESSAGE("The opposing Kecleon's type changed to Normal!");
        }
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Proactive Color Change activates before a Sheer Force-boosted move resolves")
{
    GIVEN {
        PLAYER(SPECIES_KECLEON) { Ability(ABILITY_COLOR_CHANGE); }
        OPPONENT(SPECIES_NIDOKING) { Ability(ABILITY_SHEER_FORCE); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_EMBER); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_COLOR_CHANGE);
        MESSAGE("Kecleon's type changed to Fire!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_EMBER, opponent);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Proactive Color Change does not activate through Protect")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_EMBER) == TYPE_FIRE);
        PLAYER(SPECIES_KECLEON) { Ability(ABILITY_COLOR_CHANGE); Speed(100); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(10); }
    } WHEN {
        TURN { MOVE(player, MOVE_PROTECT); MOVE(opponent, MOVE_EMBER); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PROTECT, player);
        NOT ABILITY_POPUP(player, ABILITY_COLOR_CHANGE);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Proactive Color Change grants immunity to Prankster-boosted Dark status moves")
{
    GIVEN {
        WITH_CONFIG(B_PRANKSTER_DARK_TYPES, GEN_7);
        ASSUME(GetMoveType(MOVE_TAUNT) == TYPE_DARK);
        ASSUME(IsBattleMoveStatus(MOVE_TAUNT));
        ASSUME(GetSpeciesType(SPECIES_KECLEON, 0) != TYPE_DARK && GetSpeciesType(SPECIES_KECLEON, 1) != TYPE_DARK);
        PLAYER(SPECIES_KECLEON) { Ability(ABILITY_COLOR_CHANGE); }
        OPPONENT(SPECIES_VOLBEAT) { Ability(ABILITY_PRANKSTER); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_TAUNT); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_COLOR_CHANGE);
        MESSAGE("Kecleon's type changed to Dark!");
        NOT ANIMATION(ANIM_TYPE_MOVE, MOVE_TAUNT, opponent);
        MESSAGE("It doesn't affect Kecleon…");
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Proactive Color Change grants immunity to powder moves after becoming Grass type")
{
    GIVEN {
        WITH_CONFIG(B_POWDER_GRASS, GEN_6);
        ASSUME(GetMoveType(MOVE_STUN_SPORE) == TYPE_GRASS);
        ASSUME(IsPowderMove(MOVE_STUN_SPORE));
        ASSUME(GetSpeciesType(SPECIES_KECLEON, 0) != TYPE_GRASS && GetSpeciesType(SPECIES_KECLEON, 1) != TYPE_GRASS);
        PLAYER(SPECIES_KECLEON) { Ability(ABILITY_COLOR_CHANGE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_STUN_SPORE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_COLOR_CHANGE);
        MESSAGE("Kecleon's type changed to Grass!");
        NOT ANIMATION(ANIM_TYPE_MOVE, MOVE_STUN_SPORE, opponent);
        MESSAGE("It doesn't affect Kecleon…");
    }
}
