/*
 * Example usage of the battle_ai_switch_items debug system
 * 
 * This file demonstrates how to use the debug toggles and what kind of output
 * you can expect from each category.
 */

#include "global.h"
#include "battle_ai_switch_items.h"

/*
 * Debug Categories Available:
 * 
 * DEBUG_SWITCH_DECISIONS (0) - High-level switch decision flow
 *   - When ShouldSwitch is called
 *   - Basic battle state info (HP, species, etc.)
 *   - Whether switching is possible (trapped, rooted, etc.)
 *   - Final switch decision outcome
 * 
 * DEBUG_ITEM_DECISIONS (1) - Item usage decisions
 *   - When ShouldUseItem is called
 *   - Available items being evaluated
 *   - Item usage conditions and decisions
 *   - Final item usage outcome
 * 
 * DEBUG_SWITCH_REASONS (2) - Specific reasons for switching
 *   - Which switch condition triggered (bad odds, status, etc.)
 *   - Detailed reasoning for each switch scenario
 *   - RNG outcomes for probabilistic switches
 * 
 * DEBUG_MON_EVALUATION (3) - Pokemon evaluation for switching
 *   - Party member analysis
 *   - Switchin candidate evaluation
 *   - Mon suitability scoring
 * 
 * DEBUG_TYPE_MATCHUPS (4) - Type effectiveness calculations
 *   - Attacker vs defender type analysis
 *   - Type effectiveness multipliers
 *   - Type-based switch decisions
 * 
 * DEBUG_DAMAGE_CALCULATIONS (5) - Damage analysis
 *   - Move damage calculations
 *   - OHKO/2HKO analysis
 *   - Best move selection
 * 
 * DEBUG_HAZARD_CALCULATIONS (6) - Entry hazard analysis
 *   - Stealth Rock, Spikes damage
 *   - Hazard survival calculations
 *   - Switch-in safety evaluation
 * 
 * DEBUG_STATUS_CONDITIONS (7) - Status effect analysis
 *   - Current status conditions
 *   - Status-based switch decisions
 *   - Status cure item evaluation
 * 
 * DEBUG_ABILITY_CHECKS (8) - Ability-based decisions
 *   - Absorbing ability detection
 *   - Ability matchup analysis
 *   - Ability-based switch logic
 * 
 * DEBUG_PLAYER_PREDICTION (9) - Player behavior prediction
 *   - Switch prediction logic
 *   - Player move analysis
 *   - Immunity/absorption prediction
 */

// Example function to enable specific debug categories
void EnableBattleAIDebugExample(void)
{
    // Enable all debug categories
    SetBattleAISwitchItemsDebug(DEBUG_ALL_CATEGORIES, TRUE);
    
    // Or enable specific categories:
    // SetBattleAISwitchItemsDebug(DEBUG_SWITCH_DECISIONS, TRUE);
    // SetBattleAISwitchItemsDebug(DEBUG_SWITCH_REASONS, TRUE);
    // SetBattleAISwitchItemsDebug(DEBUG_DAMAGE_CALCULATIONS, TRUE);
}

// Example function to disable debug output
void DisableBattleAIDebugExample(void)
{
    // Disable all debug categories
    SetBattleAISwitchItemsDebug(DEBUG_ALL_CATEGORIES, FALSE);
}

// Example function to enable only switch-related debugging
void EnableSwitchDebuggingOnly(void)
{
    // Disable all first
    SetBattleAISwitchItemsDebug(DEBUG_ALL_CATEGORIES, FALSE);
    
    // Enable only switch-related categories
    SetBattleAISwitchItemsDebug(DEBUG_SWITCH_DECISIONS, TRUE);
    SetBattleAISwitchItemsDebug(DEBUG_SWITCH_REASONS, TRUE);
    SetBattleAISwitchItemsDebug(DEBUG_TYPE_MATCHUPS, TRUE);
    SetBattleAISwitchItemsDebug(DEBUG_DAMAGE_CALCULATIONS, TRUE);
}

// Example function to enable only item-related debugging
void EnableItemDebuggingOnly(void)
{
    // Disable all first
    SetBattleAISwitchItemsDebug(DEBUG_ALL_CATEGORIES, FALSE);
    
    // Enable only item-related categories
    SetBattleAISwitchItemsDebug(DEBUG_ITEM_DECISIONS, TRUE);
    SetBattleAISwitchItemsDebug(DEBUG_STATUS_CONDITIONS, TRUE);
}

/*
 * Example debug output you might see:
 * 
 * [SWITCH] === ShouldSwitch called for battler 1 (species: 25, HP: 45/120) ===
 * [SWITCH] === AI Switch Decision Logic ===
 * [SWITCH] Single battle - battler: 1
 * [SWITCH] Party range: 0 to 5
 * [SWITCH] Available mons to switch to: 3
 * [SWITCH] === Checking Switch Conditions (in priority order) ===
 * [REASON] --- Checking if should switch due to bad odds ---
 * [REASON] Analyzing matchup: AI battler 1 vs opponent 0
 * [DAMAGE] Analyzing AI's moves:
 * [DAMAGE] Move 0: 85 (effect: 1)
 * [DAMAGE] Move 85 damage: 45
 * [DAMAGE] New best move: 85 (damage: 45)
 * [TYPE] Calculating type matchup - Attacker: 13/13 vs Defender: 4/4
 * [TYPE] Final type effectiveness: 8192 (1.0 = 4096)
 * [DAMAGE] Analyzing opponent's moves:
 * [DAMAGE] Opponent move 55: 78 damage
 * [DAMAGE] New max damage taken: 78
 * [REASON] === Bad Odds Decision Logic ===
 * [REASON] Gets OHKO: NO, Type effectiveness: 8192, AI HP: 45/120
 * [REASON] No bad odds conditions met - staying in
 * [SWITCH] No switch conditions met - staying in
 * 
 * [ITEM] === ShouldUseItem called for battler 1 ===
 * [ITEM] Checking available items:
 * [ITEM] Evaluating item 17 (usage type: 1)
 * [ITEM] Checking HP restore item (heal amount: 50)
 * [ITEM] --- AI_ShouldHeal: battler 1, heal amount 50 ---
 * [ITEM] Current HP: 45/120, Opponent: 0
 * [ITEM] HP threshold: 30, Missing HP: 75, Low HP: NO, Fainted: NO, Worth healing: YES
 * [ITEM] Opponent can still faint after heal: NO, Final decision: HEAL
 * [ITEM] HP restore decision: USE
 * [ITEM] === USING ITEM 17 ===
 */
