#include "global.h"
#include "test/battle.h"

// These are deliberately small examples.  AI-vs-AI simulations use the
// complete battle engine, so a designated set can use every PLAYER/OPPONENT
// field supported by ordinary battle tests.

AI_VS_AI_SINGLE_BATTLE_TEST("ZenmodemanSim: AI-vs-AI simulator runs simplified special attackers to completion")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_SMART_TRAINER);
        PLAYER(SPECIES_CHARIZARD) {
            Level(50);
            Nature(NATURE_MODEST);
            Ability(ABILITY_BLAZE);
            Item(ITEM_CHARCOAL);
            Moves(MOVE_FLAMETHROWER, MOVE_AIR_SLASH, MOVE_DRAGON_PULSE, MOVE_ROOST);
        }
        OPPONENT(SPECIES_BLASTOISE) {
            Level(50);
            Nature(NATURE_MODEST);
            Ability(ABILITY_TORRENT);
            Item(ITEM_MYSTIC_WATER);
            Moves(MOVE_SURF, MOVE_ICE_BEAM, MOVE_AURA_SPHERE, MOVE_PROTECT);
        }
    } THEN {
        EXPECT(gBattleOutcome == B_OUTCOME_WON
            || gBattleOutcome == B_OUTCOME_LOST
            || gBattleOutcome == B_OUTCOME_DREW);
    }
}

AI_VS_AI_SINGLE_BATTLE_TEST("ZenmodemanSim: AI-vs-AI simulator supports physical designated sets")
{
    GIVEN {
        AI_FLAGS(AI_FLAG_SMART_TRAINER);
        PLAYER(SPECIES_BRELOOM) {
            Level(50);
            Nature(NATURE_ADAMANT);
            Ability(ABILITY_TECHNICIAN);
            Item(ITEM_MUSCLE_BAND);
            Moves(MOVE_MACH_PUNCH, MOVE_BULLET_SEED, MOVE_ROCK_TOMB, MOVE_SPORE);
        }
        OPPONENT(SPECIES_LUCARIO) {
            Level(50);
            Nature(NATURE_ADAMANT);
            Ability(ABILITY_INNER_FOCUS);
            Item(ITEM_BLACK_BELT);
            Moves(MOVE_CLOSE_COMBAT, MOVE_BULLET_PUNCH, MOVE_CRUNCH, MOVE_SWORDS_DANCE);
        }
    } THEN {
        EXPECT(gBattleOutcome == B_OUTCOME_WON
            || gBattleOutcome == B_OUTCOME_LOST
            || gBattleOutcome == B_OUTCOME_DREW);
    }
}
