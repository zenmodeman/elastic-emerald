#include "global.h"
#include "test/battle.h"

TO_DO_BATTLE_TEST("Echoed Voice's power is multiplied for every consecutive turn used, capped at 5");
TO_DO_BATTLE_TEST("Echoed Voice's power is reset when using a different move");
TO_DO_BATTLE_TEST("Echoed Voice's power is increased even if it misses");
TO_DO_BATTLE_TEST("Echoed Voice's power is increased even if it's blocked by Protect");

/*
 * Comprehensive test suite for Echoed Voice implementation
 * 
 * Tests the battle-wide counter system that tracks consecutive
 * Echoed Voice uses across all battlers.
 */


#include "battle.h"
#include "battle_util.h"

// Test helper macros
#define EXPECT_ECHOED_VOICE_COUNTER(expected) \
    EXPECT_EQ((u16)(gBattleStruct->echoedVoiceCounter), (u16)expected)



// Test 1: Basic single battler usage
SINGLE_BATTLE_TEST("Zenmodeman: Echoed Voice powers up with consecutive uses by same battler")
{
    GIVEN {
        PLAYER(SPECIES_CHATOT) { Moves(MOVE_ECHOED_VOICE, MOVE_TACKLE, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_EXPLOUD) { Moves(MOVE_TACKLE, MOVE_CELEBRATE); }
    } WHEN {
        TURN {MOVE(player, MOVE_CELEBRATE);}
        EXPECT_ECHOED_VOICE_COUNTER(0);

        TURN { MOVE(player, MOVE_ECHOED_VOICE); }
        EXPECT_ECHOED_VOICE_COUNTER(1);
        
        TURN { MOVE(player, MOVE_ECHOED_VOICE); }
        EXPECT_ECHOED_VOICE_COUNTER(2);
        
        TURN { MOVE(player, MOVE_ECHOED_VOICE); }
        EXPECT_ECHOED_VOICE_COUNTER(3);
        
        TURN { MOVE(player, MOVE_TACKLE); }
        EXPECT_ECHOED_VOICE_COUNTER(0);
        
        // Turn 5: Chain restarts
        TURN { MOVE(player, MOVE_ECHOED_VOICE); }
        EXPECT_ECHOED_VOICE_COUNTER(1);
    }
}

// Test 2: Cross-battler usage (key feature)
SINGLE_BATTLE_TEST("Zenmodeman: Echoed Voice powers up across different battlers")
{
    GIVEN {
        PLAYER(SPECIES_CHATOT) { Moves(MOVE_ECHOED_VOICE, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_EXPLOUD) { Moves(MOVE_ECHOED_VOICE, MOVE_CELEBRATE); }
    } WHEN {
        // Turn 1: Player uses Echoed Voice
        TURN { MOVE(player, MOVE_ECHOED_VOICE); }
        EXPECT_ECHOED_VOICE_COUNTER(1);
        
        // Turn 2: Opponent uses Echoed Voice (should power up)
        TURN { MOVE(opponent, MOVE_ECHOED_VOICE); }
        EXPECT_ECHOED_VOICE_COUNTER(2);
        
        // Turn 3: Player uses Echoed Voice again (should power up further)
        TURN { MOVE(player, MOVE_ECHOED_VOICE); }
        EXPECT_ECHOED_VOICE_COUNTER(3);
    }
}

// Test 3: Flinch/Paralysis prevention
SINGLE_BATTLE_TEST("Zenmodeman: Echoed Voice chain breaks when move execution is prevented")
{
    GIVEN {
        PLAYER(SPECIES_CHATOT) { Moves(MOVE_ECHOED_VOICE, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_CROBAT) { Moves(MOVE_IRON_HEAD, MOVE_ECHOED_VOICE, MOVE_CELEBRATE); }
    } WHEN {
        // Turn 1: Player uses Echoed Voice
        TURN { MOVE(player, MOVE_ECHOED_VOICE); }
        EXPECT_ECHOED_VOICE_COUNTER(1);
        
        // Turn 2: Player flinches from Fake Out, can't use Echoed Voice
        TURN { 
            MOVE(opponent, MOVE_IRON_HEAD); 
            MOVE(player, MOVE_ECHOED_VOICE); // This won't execute due to flinch
        }
        EXPECT_ECHOED_VOICE_COUNTER(0); // Chain broken
        
        // Turn 3: Chain restarts
        TURN { MOVE(player, MOVE_ECHOED_VOICE); }
        EXPECT_ECHOED_VOICE_COUNTER(1);
    }
}

// Test 4: Sleep/Paralysis prevention
SINGLE_BATTLE_TEST("Zenmodeman: Echoed Voice chain breaks when battler is asleep or paralyzed")
{
    GIVEN {
        PLAYER(SPECIES_CHATOT) { Moves(MOVE_ECHOED_VOICE, MOVE_CELEBRATE); Status1(STATUS1_SLEEP); }
        OPPONENT(SPECIES_EXPLOUD) { Moves(MOVE_TACKLE, MOVE_CELEBRATE); }
    } WHEN {
        // Turn 1: Player tries Echoed Voice but is asleep
        TURN { MOVE(player, MOVE_ECHOED_VOICE); } // Won't execute
        EXPECT_ECHOED_VOICE_COUNTER(0);
        
        // Turn 2: Player wakes up and uses Echoed Voice
        TURN { MOVE(player, MOVE_ECHOED_VOICE); }
        EXPECT_ECHOED_VOICE_COUNTER(1);
    }
}

// Test 5: Protect/Miss still counts (PP is reduced)
SINGLE_BATTLE_TEST("Zenmodeman: Echoed Voice chain continues even when blocked by Protect or missed")
{
    GIVEN {
        PLAYER(SPECIES_CHATOT) { Moves(MOVE_ECHOED_VOICE, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_EXPLOUD) { Moves(MOVE_PROTECT, MOVE_ECHOED_VOICE, MOVE_CELEBRATE); }
    } WHEN {
        // Turn 1: Player uses Echoed Voice
        TURN { MOVE(player, MOVE_ECHOED_VOICE); }
        EXPECT_ECHOED_VOICE_COUNTER(1);
        
        // Turn 2: Opponent uses Protect, Player's Echoed Voice is blocked but PP is consumed
        TURN { 
            MOVE(opponent, MOVE_PROTECT);
            MOVE(player, MOVE_ECHOED_VOICE); // Blocked but PP reduced
        }
        EXPECT_ECHOED_VOICE_COUNTER(2); // Chain continues
        
        // Turn 3: Opponent uses Echoed Voice (should be powered up)
        TURN { MOVE(opponent, MOVE_ECHOED_VOICE); }
        EXPECT_ECHOED_VOICE_COUNTER(3);
    }
}

// Test 6: Pokemon fainting after using Echoed Voice
SINGLE_BATTLE_TEST("Zenmodeman: Echoed Voice chain continues after user faints")
{
    GIVEN {
        PLAYER(SPECIES_CHATOT) { HP(1); Moves(MOVE_ECHOED_VOICE, MOVE_CELEBRATE); }
        PLAYER(SPECIES_PIDGEOT) { Moves(MOVE_ECHOED_VOICE, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_EXPLOUD) { Moves(MOVE_TACKLE, MOVE_CELEBRATE); }
    } WHEN {
        // Turn 1: Chatot uses Echoed Voice, then faints to Tackle
        TURN { 
            MOVE(player, MOVE_ECHOED_VOICE); 
            MOVE(opponent, MOVE_TACKLE); // Chatot faints
        }
        EXPECT_ECHOED_VOICE_COUNTER(1);
        
        // Turn 2: Send in Pidgeot, use Echoed Voice (should be powered up)
        TURN { 
            SEND_OUT(player, 1); // Pidgeot
            MOVE(player, MOVE_ECHOED_VOICE); 
        }
        EXPECT_ECHOED_VOICE_COUNTER(2);
    }
}

// Test 7: Maximum power cap
SINGLE_BATTLE_TEST("Echoed Voice caps at 200 base power")
{
    GIVEN {
        PLAYER(SPECIES_CHATOT) { Moves(MOVE_AMNESIA, MOVE_ECHOED_VOICE, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_EXPLOUD) { Moves(MOVE_AMNESIA, MOVE_ECHOED_VOICE, MOVE_CELEBRATE); }
    } WHEN {
        //Boost SP.Def to avoid dying
        TURN{             
            MOVE(player, MOVE_AMNESIA); 
            MOVE(opponent, MOVE_AMNESIA); // Chatot faints
        }
        TURN{             
            MOVE(player, MOVE_AMNESIA); 
            MOVE(opponent, MOVE_AMNESIA); // Chatot faints
        }
        TURN{             
            MOVE(player, MOVE_AMNESIA); 
            MOVE(opponent, MOVE_AMNESIA); // Chatot faints
        }

        // Build up to maximum power
        TURN { MOVE(player, MOVE_ECHOED_VOICE); }    
        TURN { MOVE(opponent, MOVE_ECHOED_VOICE); }  
        TURN { MOVE(player, MOVE_ECHOED_VOICE); }    
        TURN { MOVE(opponent, MOVE_ECHOED_VOICE); }  
        TURN { MOVE(player, MOVE_ECHOED_VOICE); }    
        TURN { MOVE(opponent, MOVE_ECHOED_VOICE); }

        //The cap is 4
        EXPECT_ECHOED_VOICE_COUNTER(4);
        
    }
}

// Test 8: Double battle scenario
DOUBLE_BATTLE_TEST("Echoed Voice works correctly in double battles")
{
    GIVEN {
        PLAYER(SPECIES_CHATOT) { Moves(MOVE_ECHOED_VOICE, MOVE_CELEBRATE); }
        PLAYER(SPECIES_PIDGEOT) { Moves(MOVE_ECHOED_VOICE, MOVE_TACKLE, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_EXPLOUD) { Moves(MOVE_ECHOED_VOICE, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_LOUDRED) { Moves(MOVE_TACKLE, MOVE_CELEBRATE); }
    } WHEN {
        // Turn 1: Both player Pokemon use Echoed Voice
        TURN { 
            MOVE(playerLeft, MOVE_ECHOED_VOICE, target: opponentLeft); 
            MOVE(playerRight, MOVE_ECHOED_VOICE, target: opponentRight);
        }
        EXPECT_ECHOED_VOICE_COUNTER(1); // Should only increment once per turn
        
        // Turn 2: Opponent uses Echoed Voice (should be powered up)
        TURN { MOVE(opponentLeft, MOVE_ECHOED_VOICE, target: playerLeft); }
        EXPECT_ECHOED_VOICE_COUNTER(2);
        
        // Turn 3: Break chain
        TURN { MOVE(playerRight, MOVE_TACKLE, target: opponentLeft); }
        EXPECT_ECHOED_VOICE_COUNTER(0);
    }
}

// Test 9: Counter reset scenarios
SINGLE_BATTLE_TEST("Echoed Voice counter resets correctly in various scenarios")
{
    GIVEN {
        PLAYER(SPECIES_CHATOT) { Moves(MOVE_ECHOED_VOICE, MOVE_TACKLE, MOVE_CELEBRATE); }
        OPPONENT(SPECIES_EXPLOUD) { Moves(MOVE_TACKLE, MOVE_CELEBRATE); }
    } WHEN {
        // Build up counter
        TURN { MOVE(player, MOVE_ECHOED_VOICE); }
        EXPECT_ECHOED_VOICE_COUNTER(1);
        
        // Reset with different move
        TURN { MOVE(player, MOVE_TACKLE); }
        EXPECT_ECHOED_VOICE_COUNTER(0);
        
        // Build up again
        TURN { MOVE(player, MOVE_ECHOED_VOICE); }
        EXPECT_ECHOED_VOICE_COUNTER(1);
        
        // Reset when neither battler uses Echoed Voice
        TURN { 
            MOVE(player, MOVE_TACKLE); 
            MOVE(opponent, MOVE_TACKLE); 
        }
        EXPECT_ECHOED_VOICE_COUNTER(0);
    }
}
