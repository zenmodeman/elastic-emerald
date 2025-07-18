#include "global.h"
#include "battle.h"
#include "constants/battle_ai.h"
#include "battle_ai_main.h"
#include "battle_ai_util.h"
#include "battle_util.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_main.h"
#include "constants/hold_effects.h"
#include "battle_setup.h"
#include "data.h"
#include "item.h"
#include "party_menu.h"
#include "pokemon.h"
#include "random.h"
#include "util.h"
#include "constants/abilities.h"
#include "constants/item_effects.h"
#include "constants/battle_move_effects.h"
#include "constants/items.h"
#include "constants/moves.h"

// Debug toggle variables for battle_ai_switch_items
static bool32 sDebugSwitchDecisions = FALSE;
static bool32 sDebugItemDecisions = FALSE;
static bool32 sDebugSwitchReasons = FALSE;
static bool32 sDebugMonEvaluation = FALSE;
static bool32 sDebugTypeMatchups = FALSE;
static bool32 sDebugDamageCalculations = FALSE;
static bool32 sDebugHazardCalculations = FALSE;
static bool32 sDebugStatusConditions = FALSE;
static bool32 sDebugAbilityChecks = FALSE;
static bool32 sDebugPlayerPrediction = FALSE;

// Debug macros for cleaner code
#define DEBUG_SWITCH(format, ...) do { if (sDebugSwitchDecisions) DebugPrintf("[SWITCH] " format, ##__VA_ARGS__); } while(0)
#define DEBUG_ITEM(format, ...) do { if (sDebugItemDecisions) DebugPrintf("[ITEM] " format, ##__VA_ARGS__); } while(0)
#define DEBUG_REASON(format, ...) do { if (sDebugSwitchReasons) DebugPrintf("[REASON] " format, ##__VA_ARGS__); } while(0)
#define DEBUG_MON_EVAL(format, ...) do { if (sDebugMonEvaluation) DebugPrintf("[MON_EVAL] " format, ##__VA_ARGS__); } while(0)
#define DEBUG_TYPE(format, ...) do { if (sDebugTypeMatchups) DebugPrintf("[TYPE] " format, ##__VA_ARGS__); } while(0)
#define DEBUG_DAMAGE(format, ...) do { if (sDebugDamageCalculations) DebugPrintf("[DAMAGE] " format, ##__VA_ARGS__); } while(0)
#define DEBUG_HAZARD(format, ...) do { if (sDebugHazardCalculations) DebugPrintf("[HAZARD] " format, ##__VA_ARGS__); } while(0)
#define DEBUG_STATUS(format, ...) do { if (sDebugStatusConditions) DebugPrintf("[STATUS] " format, ##__VA_ARGS__); } while(0)
#define DEBUG_ABILITY(format, ...) do { if (sDebugAbilityChecks) DebugPrintf("[ABILITY] " format, ##__VA_ARGS__); } while(0)
#define DEBUG_PREDICT(format, ...) do { if (sDebugPlayerPrediction) DebugPrintf("[PREDICT] " format, ##__VA_ARGS__); } while(0)

// Function to toggle debug categories
void SetBattleAISwitchItemsDebug(u32 category, bool32 enabled)
{
    switch (category)
    {
    case 0: sDebugSwitchDecisions = enabled; break;
    case 1: sDebugItemDecisions = enabled; break;
    case 2: sDebugSwitchReasons = enabled; break;
    case 3: sDebugMonEvaluation = enabled; break;
    case 4: sDebugTypeMatchups = enabled; break;
    case 5: sDebugDamageCalculations = enabled; break;
    case 6: sDebugHazardCalculations = enabled; break;
    case 7: sDebugStatusConditions = enabled; break;
    case 8: sDebugAbilityChecks = enabled; break;
    case 9: sDebugPlayerPrediction = enabled; break;
    case 99: // Enable all
        sDebugSwitchDecisions = sDebugItemDecisions = sDebugSwitchReasons =
        sDebugMonEvaluation = sDebugTypeMatchups = sDebugDamageCalculations =
        sDebugHazardCalculations = sDebugStatusConditions = sDebugAbilityChecks =
        sDebugPlayerPrediction = enabled;
        break;
    }
}


// // Enable all debug output
// SetBattleAISwitchItemsDebug(DEBUG_ALL_CATEGORIES, TRUE);

// // Enable only switch-related debugging
// SetBattleAISwitchItemsDebug(DEBUG_SWITCH_DECISIONS, TRUE);
// SetBattleAISwitchItemsDebug(DEBUG_SWITCH_REASONS, TRUE);
// SetBattleAISwitchItemsDebug(DEBUG_DAMAGE_CALCULATIONS, TRUE);

// // Enable only item debugging
// SetBattleAISwitchItemsDebug(DEBUG_ITEM_DECISIONS, TRUE);
// SetBattleAISwitchItemsDebug(DEBUG_STATUS_CONDITIONS, TRUE);

// // Disable all debugging
// SetBattleAISwitchItemsDebug(DEBUG_ALL_CATEGORIES, FALSE);


// this file's functions
static bool32 HasSuperEffectiveMoveAgainstOpponents(u32 battler, bool32 noRng);
static bool32 FindMonWithFlagsAndSuperEffective(u32 battler, u16 flags, u32 moduloPercent);
static bool32 ShouldUseItem(u32 battler);
static bool32 AiExpectsToFaintPlayer(u32 battler);
static bool32 AI_ShouldHeal(u32 battler, u32 healAmount);
static bool32 AI_OpponentCanFaintAiWithMod(u32 battler, u32 healAmount);
static u32 GetSwitchinHazardsDamage(u32 battler, struct BattlePokemon *battleMon);
static bool32 CanAbilityTrapOpponent(u16 ability, u32 opponent);


//Custom static function
static bool32 FindHealAbsorbMonWithSwitches(u32 battler, u16 move, u32 numRequiredSwitches);

#define MIN_SWITCHES_FOR_PREDICTION 3

static void InitializeSwitchinCandidate(struct Pokemon *mon)
{
    PokemonToBattleMon(mon, &AI_DATA->switchinCandidate.battleMon);
    AI_DATA->switchinCandidate.hypotheticalStatus = FALSE;
}

u32 GetSwitchChance(enum ShouldSwitchScenario shouldSwitchScenario)
{
    // Modify these cases if you want unique behaviour based on other data (trainer class, difficulty, etc.)
    switch(shouldSwitchScenario)
    {
        case SHOULD_SWITCH_WONDER_GUARD:
            return SHOULD_SWITCH_WONDER_GUARD_PERCENTAGE;
        case SHOULD_SWITCH_ABSORBS_MOVE:
            return SHOULD_SWITCH_ABSORBS_MOVE_PERCENTAGE;
        case SHOULD_SWITCH_TRAPPER:
            return SHOULD_SWITCH_TRAPPER_PERCENTAGE;
        case SHOULD_SWITCH_FREE_TURN:
            return SHOULD_SWITCH_FREE_TURN_PERCENTAGE;
        case SHOULD_SWITCH_TRUANT:
            return SHOULD_SWITCH_TRUANT_PERCENTAGE;
        case SHOULD_SWITCH_ALL_MOVES_BAD:
            return SHOULD_SWITCH_ALL_MOVES_BAD_PERCENTAGE;
        case SHOULD_SWITCH_PERISH_SONG:
            return SHOULD_SWITCH_PERISH_SONG_PERCENTAGE;
        case SHOULD_SWITCH_YAWN:
            return SHOULD_SWITCH_YAWN_PERCENTAGE;
        case SHOULD_SWITCH_BADLY_POISONED:
            return SHOULD_SWITCH_BADLY_POISONED_PERCENTAGE;
        case SHOULD_SWITCH_BADLY_POISONED_STATS_RAISED:
            return SHOULD_SWITCH_BADLY_POISONED_STATS_RAISED_PERCENTAGE;
        case SHOULD_SWITCH_CURSED:
            return SHOULD_SWITCH_CURSED_PERCENTAGE;
        case SHOULD_SWITCH_CURSED_STATS_RAISED:
            return SHOULD_SWITCH_CURSED_STATS_RAISED_PERCENTAGE;
        case SHOULD_SWITCH_NIGHTMARE:
            return SHOULD_SWITCH_NIGHTMARE_PERCENTAGE;
        case SHOULD_SWITCH_NIGHTMARE_STATS_RAISED:
            return SHOULD_SWITCH_NIGHTMARE_STATS_RAISED_PERCENTAGE;
        case SHOULD_SWITCH_SEEDED:
            return SHOULD_SWITCH_SEEDED_PERCENTAGE;
        case SHOULD_SWITCH_SEEDED_STATS_RAISED:
            return SHOULD_SWITCH_SEEDED_STATS_RAISED_PERCENTAGE;
        case SHOULD_SWITCH_INFATUATION:
            return SHOULD_SWITCH_INFATUATION_PERCENTAGE;
        case SHOULD_SWITCH_HASBADODDS:
            return SHOULD_SWITCH_HASBADODDS_PERCENTAGE;
        case SHOULD_SWITCH_NATURAL_CURE_STRONG:
            return SHOULD_SWITCH_NATURAL_CURE_STRONG_PERCENTAGE;
        case SHOULD_SWITCH_NATURAL_CURE_STRONG_STATS_RAISED:
            return SHOULD_SWITCH_NATURAL_CURE_STRONG_STATS_RAISED_PERCENTAGE;
        case SHOULD_SWITCH_NATURAL_CURE_WEAK:
            return SHOULD_SWITCH_NATURAL_CURE_WEAK_PERCENTAGE;
        case SHOULD_SWITCH_NATURAL_CURE_WEAK_STATS_RAISED:
            return SHOULD_SWITCH_NATURAL_CURE_WEAK_STATS_RAISED_PERCENTAGE;
        case SHOULD_SWITCH_REGENERATOR:
            return SHOULD_SWITCH_REGENERATOR_PERCENTAGE;
        case SHOULD_SWITCH_REGENERATOR_STATS_RAISED:
            return SHOULD_SWITCH_REGENERATOR_STATS_RAISED_PERCENTAGE;
        case SHOULD_SWITCH_ENCORE_STATUS:
            return SHOULD_SWITCH_ENCORE_STATUS_PERCENTAGE;
        case SHOULD_SWITCH_ENCORE_DAMAGE:
            return SHOULD_SWITCH_ENCORE_DAMAGE_PERCENTAGE;
        case SHOULD_SWITCH_CHOICE_LOCKED:
            return SHOULD_SWITCH_CHOICE_LOCKED_PERCENTAGE;
        case SHOULD_SWITCH_ATTACKING_STAT_MINUS_TWO:
            return SHOULD_SWITCH_ATTACKING_STAT_MINUS_TWO_PERCENTAGE;
        case SHOULD_SWITCH_ATTACKING_STAT_MINUS_THREE_PLUS:
            return SHOULD_SWITCH_ATTACKING_STAT_MINUS_THREE_PLUS_PERCENTAGE;
        default:
            return 100;
    }
}

u32 GetThinkingBattler(u32 battler)
{
    if (AI_DATA->aiSwitchPredictionInProgress)
        return AI_DATA->battlerDoingPrediction;
    return battler;
}

static bool32 IsAceMon(u32 battler, u32 monPartyId)
{
    if (AI_THINKING_STRUCT->aiFlags[GetThinkingBattler(battler)] & AI_FLAG_ACE_POKEMON
            && !gBattleStruct->battlerState[battler].forcedSwitch
            && monPartyId == CalculateEnemyPartyCountInSide(battler)-1)
        return TRUE;
    if (AI_THINKING_STRUCT->aiFlags[GetThinkingBattler(battler)] & AI_FLAG_DOUBLE_ACE_POKEMON
            && !gBattleStruct->battlerState[battler].forcedSwitch
            && (monPartyId == CalculateEnemyPartyCount()-1 || monPartyId == CalculateEnemyPartyCount()-2))
        return TRUE;
    return FALSE;
}

static bool32 AreStatsRaised(u32 battler)
{
    u8 buffedStatsValue = 0;
    s32 i;

    for (i = 0; i < NUM_BATTLE_STATS; i++)
    {
        if (gBattleMons[battler].statStages[i] > DEFAULT_STAT_STAGE)
            buffedStatsValue += gBattleMons[battler].statStages[i] - DEFAULT_STAT_STAGE;
    }

    return (buffedStatsValue > STAY_IN_STATS_RAISED);
}

void GetAIPartyIndexes(u32 battler, s32 *firstId, s32 *lastId)
{
    if (BATTLE_TWO_VS_ONE_OPPONENT && (battler & BIT_SIDE) == B_SIDE_OPPONENT)
    {
        *firstId = 0, *lastId = PARTY_SIZE;
    }
    else if (gBattleTypeFlags & (BATTLE_TYPE_TWO_OPPONENTS | BATTLE_TYPE_INGAME_PARTNER | BATTLE_TYPE_TOWER_LINK_MULTI))
    {
        if ((battler & BIT_FLANK) == B_FLANK_LEFT)
            *firstId = 0, *lastId = PARTY_SIZE / 2;
        else
            *firstId = PARTY_SIZE / 2, *lastId = PARTY_SIZE;
    }
    else
    {
        *firstId = 0, *lastId = PARTY_SIZE;
    }
}

static inline bool32 SetSwitchinAndSwitch(u32 battler, u32 switchinId)
{
    gBattleStruct->AI_monToSwitchIntoId[battler] = switchinId;
    return TRUE;
}

// Note that as many return statements as possible are INTENTIONALLY put after all of the loops;
// the function can take a max of about 0.06s to run, and this prevents the player from identifying
// whether the mon will switch or not by seeing how long the delay is before they select a move
static bool32 ShouldSwitchIfHasBadOdds(u32 battler)
{
    //Variable initialization
    u8 opposingPosition, atkType1, atkType2, defType1, defType2;
    s32 i, damageDealt = 0, maxDamageDealt = 0, damageTaken = 0, maxDamageTaken = 0;
    u32 aiMove, playerMove, aiBestMove = MOVE_NONE, aiAbility = AI_DATA->abilities[battler], opposingBattler, weather = AI_GetWeather();
    bool32 getsOneShot = FALSE, hasStatusMove = FALSE, hasSuperEffectiveMove = FALSE;
    u16 typeEffectiveness = UQ_4_12(1.0), aiMoveEffect; //baseline typing damage
    uq4_12_t effectiveness;

    DEBUG_REASON("--- Checking if should switch due to bad odds ---");

    // Only use this if AI_FLAG_SMART_SWITCHING is set for the trainer
    if (!(AI_THINKING_STRUCT->aiFlags[GetThinkingBattler(battler)] & AI_FLAG_SMART_SWITCHING))
    {
        DEBUG_REASON("Smart switching not enabled - skipping bad odds check");
        return FALSE;
    }

    // Double Battles aren't included in AI_FLAG_SMART_MON_CHOICE. Defaults to regular switch in logic
    if (IsDoubleBattle())
    {
        DEBUG_REASON("Double battle - skipping bad odds check");
        return FALSE;
    }

    opposingPosition = BATTLE_OPPOSITE(GetBattlerPosition(battler));
    opposingBattler = GetBattlerAtPosition(opposingPosition);
    DEBUG_REASON("Analyzing matchup: AI battler %d vs opponent %d", battler, opposingBattler);

    // Gets types of player (opposingBattler) and computer (battler)
    atkType1 = gBattleMons[opposingBattler].types[0];
    atkType2 = gBattleMons[opposingBattler].types[1];
    defType1 = gBattleMons[battler].types[0];
    defType2 = gBattleMons[battler].types[1];

    // Check AI moves for damage dealt
    DEBUG_DAMAGE("Analyzing AI's moves:");
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        aiMove = gBattleMons[battler].moves[i];
        aiMoveEffect = GetMoveEffect(aiMove);
        if (aiMove != MOVE_NONE)
        {
            DEBUG_DAMAGE("Move %d: %d (effect: %d)", i, aiMove, aiMoveEffect);

            // Check if mon has an "important" status move
            if (aiMoveEffect == EFFECT_REFLECT || aiMoveEffect == EFFECT_LIGHT_SCREEN
            || aiMoveEffect == EFFECT_SPIKES || aiMoveEffect == EFFECT_TOXIC_SPIKES || aiMoveEffect == EFFECT_STEALTH_ROCK || aiMoveEffect == EFFECT_STICKY_WEB || aiMoveEffect == EFFECT_LEECH_SEED
            || aiMoveEffect == EFFECT_EXPLOSION
            || aiMoveEffect == EFFECT_SLEEP || aiMoveEffect == EFFECT_YAWN || aiMoveEffect == EFFECT_TOXIC || aiMoveEffect == EFFECT_WILL_O_WISP || aiMoveEffect == EFFECT_PARALYZE
            || aiMoveEffect == EFFECT_TRICK || aiMoveEffect == EFFECT_TRICK_ROOM || aiMoveEffect== EFFECT_WONDER_ROOM || aiMoveEffect ==  EFFECT_PSYCHO_SHIFT || aiMoveEffect == EFFECT_FIRST_TURN_ONLY
            )
            {
                hasStatusMove = TRUE;
                DEBUG_DAMAGE("Found important status move: %d", aiMove);
            }

            // Only check damage if it's a damaging move
            if (!IsBattleMoveStatus(aiMove))
            {
                // Check if mon has a super effective move
                uq4_12_t effectiveness = AI_GetMoveEffectiveness(aiMove, battler, opposingBattler);
                if (effectiveness >= UQ_4_12(2.0))
                {
                    hasSuperEffectiveMove = TRUE;
                    DEBUG_DAMAGE("Found super effective move: %d (effectiveness: %d)", aiMove, effectiveness);
                }

                // Get maximum damage mon can deal
                damageDealt = AI_DATA->simulatedDmg[battler][opposingBattler][i].expected;
                DEBUG_DAMAGE("Move %d damage: %d", aiMove, damageDealt);
                if(damageDealt > maxDamageDealt)
                {
                    maxDamageDealt = damageDealt;
                    aiBestMove = aiMove;
                    DEBUG_DAMAGE("New best move: %d (damage: %d)", aiBestMove, maxDamageDealt);
                }
            }
        }
    }
    DEBUG_DAMAGE("AI analysis complete - Max damage: %d, Has status move: %s, Has SE move: %s",
                 maxDamageDealt, hasStatusMove ? "YES" : "NO", hasSuperEffectiveMove ? "YES" : "NO");

    // Calculate type advantage
    DEBUG_TYPE("Calculating type matchup - Attacker: %d/%d vs Defender: %d/%d", atkType1, atkType2, defType1, defType2);
    typeEffectiveness = uq4_12_multiply(typeEffectiveness, (GetTypeModifier(atkType1, defType1)));
    if (atkType2 != atkType1)
        typeEffectiveness = uq4_12_multiply(typeEffectiveness, (GetTypeModifier(atkType2, defType1)));
    if (defType2 != defType1)
    {
        typeEffectiveness = uq4_12_multiply(typeEffectiveness, (GetTypeModifier(atkType1, defType2)));
        if (atkType2 != atkType1)
            typeEffectiveness = uq4_12_multiply(typeEffectiveness, (GetTypeModifier(atkType2, defType2)));
    }
    DEBUG_TYPE("Final type effectiveness: %d (1.0 = %d)", typeEffectiveness, UQ_4_12(1.0));

    // Get max damage mon could take
    DEBUG_DAMAGE("Analyzing opponent's moves (revealed + STAB only):");
    u16 opponentMoves[MAX_MON_MOVES];
    GetMovesArrayWithHiddenSTAB(opposingBattler, opponentMoves);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        playerMove = opponentMoves[i];
        if (playerMove != MOVE_NONE && playerMove != MOVE_UNAVAILABLE && !IsBattleMoveStatus(playerMove) && GetMoveEffect(playerMove) != EFFECT_FOCUS_PUNCH)
        {
            damageTaken = AI_CalcDamage(playerMove, opposingBattler, battler, &effectiveness, FALSE, weather, DMG_ROLL_HIGHEST).expected;
            DEBUG_DAMAGE("Opponent move %d: %d damage", playerMove, damageTaken);
            if (damageTaken > maxDamageTaken)
            {
                maxDamageTaken = damageTaken;
                DEBUG_DAMAGE("New max damage taken: %d", maxDamageTaken);
            }
        }
        else if (playerMove != MOVE_NONE && playerMove != MOVE_UNAVAILABLE)
        {
            DEBUG_DAMAGE("Skipping opponent move %d (status/Focus Punch)", playerMove);
        }
    }
    DEBUG_DAMAGE("Opponent analysis complete - Max damage to AI: %d (AI HP: %d/%d)",
                 maxDamageTaken, gBattleMons[battler].hp, gBattleMons[battler].maxHP);

    // Check if mon gets one shot
    bool32 hasFocusSash = (gItemsInfo[gBattleMons[battler].item].holdEffect == HOLD_EFFECT_FOCUS_SASH);
    bool32 hasSturdy = (!IsMoldBreakerTypeAbility(opposingBattler, gBattleMons[opposingBattler].ability) && B_STURDY >= GEN_5 && aiAbility == ABILITY_STURDY);
    if(maxDamageTaken > gBattleMons[battler].hp && !(hasFocusSash || hasSturdy))
    {
        getsOneShot = TRUE;
        DEBUG_REASON("AI mon gets OHKO'd (damage: %d, HP: %d, Focus Sash: %s, Sturdy: %s)",
                     maxDamageTaken, gBattleMons[battler].hp, hasFocusSash ? "YES" : "NO", hasSturdy ? "YES" : "NO");
    }

    // Check if current mon can outspeed and KO in spite of bad matchup, and don't switch out if it can
    if(maxDamageDealt > gBattleMons[opposingBattler].hp)
    {
        bool32 isFaster = AI_IsFaster(battler, opposingBattler, aiBestMove);
        DEBUG_REASON("AI can OHKO opponent (damage: %d, opponent HP: %d, AI faster: %s)",
                     maxDamageDealt, gBattleMons[opposingBattler].hp, isFaster ? "YES" : "NO");
        if (isFaster)
        {
            DEBUG_REASON("Not switching - AI can outspeed and OHKO");
            return FALSE;
        }
    }

    // If we don't have any other viable options, don't switch out
    if (AI_DATA->mostSuitableMonId[battler] == PARTY_SIZE)
    {
        DEBUG_REASON("Not switching - no suitable replacement mon available");
        return FALSE;
    }

    // Start assessing whether or not mon has bad odds
    DEBUG_REASON("=== Bad Odds Decision Logic ===");
    DEBUG_REASON("Gets OHKO: %s, Type effectiveness: %d, AI HP: %d/%d",
                 getsOneShot ? "YES" : "NO", typeEffectiveness, gBattleMons[battler].hp, gBattleMons[battler].maxHP);

    // Jump straight to switching out in cases where mon gets OHKO'd
    bool32 opponentFaster = (gBattleMons[opposingBattler].speed > gBattleMons[battler].speed);
    bool32 cantFourKO = (maxDamageDealt < gBattleMons[opposingBattler].hp / 4);
    bool32 hasGoodHP = (gBattleMons[battler].hp >= ((gBattleMons[battler].maxHP * 3) / 4));
    bool32 hasRegenHP = (aiAbility == ABILITY_REGENERATOR && gBattleMons[battler].hp >= gBattleMons[battler].maxHP / 4);

    if ((
        // If the player OHKOs and outspeeds OR OHKOs, doesn't outspeed but isn't 4KO'd
        (getsOneShot && opponentFaster)
            || (getsOneShot && !opponentFaster && cantFourKO))
        && (hasGoodHP || hasRegenHP)) // And the current mon has at least 3/4 their HP, or 1/4 HP and Regenerator
    {
        DEBUG_REASON("OHKO scenario - Opponent faster: %s, Can't 4KO: %s, Good HP: %s, Regen HP: %s",
                     opponentFaster ? "YES" : "NO", cantFourKO ? "YES" : "NO",
                     hasGoodHP ? "YES" : "NO", hasRegenHP ? "YES" : "NO");

        // 50% chance to stay in regardless
        u32 switchChance = GetSwitchChance(SHOULD_SWITCH_HASBADODDS);
        if (RandomPercentage(RNG_AI_SWITCH_HASBADODDS, (100 - switchChance)) && !AI_DATA->aiSwitchPredictionInProgress)
        {
            DEBUG_REASON("RNG check failed (%d%% chance) - staying in", switchChance);
            return FALSE;
        }

        DEBUG_REASON("Switching due to OHKO scenario");
        return SetSwitchinAndSwitch(battler, PARTY_SIZE);
    }

    // General bad type matchups have more wiggle room
    if (typeEffectiveness >= UQ_4_12(2.0)) // If the player has at least a 2x type advantage
    {
        DEBUG_REASON("Bad type matchup (2x+ effectiveness) - checking conditions");
        bool32 hasGoodHPForType = (gBattleMons[battler].hp >= gBattleMons[battler].maxHP / 2);
        bool32 hasRegenHPForType = (aiAbility == ABILITY_REGENERATOR && gBattleMons[battler].hp >= gBattleMons[battler].maxHP / 4);

        if (!hasSuperEffectiveMove && (hasGoodHPForType || hasRegenHPForType))
        {
            DEBUG_REASON("No SE move, good HP (%s) or regen HP (%s)",
                         hasGoodHPForType ? "YES" : "NO", hasRegenHPForType ? "YES" : "NO");

            // Then check if they have an important status move, which is worth using even in a bad matchup
            if (hasStatusMove)
            {
                DEBUG_REASON("Has important status move - staying in despite bad matchup");
                return FALSE;
            }

            // 50% chance to stay in regardless
            u32 switchChance = GetSwitchChance(SHOULD_SWITCH_HASBADODDS);
            if (RandomPercentage(RNG_AI_SWITCH_HASBADODDS, (100 - switchChance)) && !AI_DATA->aiSwitchPredictionInProgress)
            {
                DEBUG_REASON("RNG check failed (%d%% chance) - staying in", switchChance);
                return FALSE;
            }

            DEBUG_REASON("Switching due to bad type matchup");
            return SetSwitchinAndSwitch(battler, PARTY_SIZE);
        }
    }
    DEBUG_REASON("No bad odds conditions met - staying in");
    return FALSE;
}

static bool32 ShouldSwitchIfTruant(u32 battler)
{
    // Switch if mon with truant is bodied by Protect or invulnerability spam
    if (AI_DATA->abilities[battler] == ABILITY_TRUANT
        && IsTruantMonVulnerable(battler, gBattlerTarget)
        && gDisableStructs[battler].truantCounter
        && gBattleMons[battler].hp >= gBattleMons[battler].maxHP / 2
        && AI_DATA->mostSuitableMonId[battler] != PARTY_SIZE)
    {
        if (RandomPercentage(RNG_AI_SWITCH_TRUANT, GetSwitchChance(SHOULD_SWITCH_TRUANT)))
            return SetSwitchinAndSwitch(battler, PARTY_SIZE);
    }
    return FALSE;
}


static bool32 ShouldSwitchIfAllMovesBad(u32 battler)
{
    u32 moveIndex;
    u32 opposingBattler = GetOppositeBattler(battler);
    u32 aiMove;

    // Switch if no moves affect opponents
    if (IsDoubleBattle())
    {
        u32 opposingPartner = GetBattlerAtPosition(BATTLE_PARTNER(opposingBattler));
        for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
        {
            aiMove = gBattleMons[battler].moves[moveIndex];
            if ((AI_GetMoveEffectiveness(aiMove, battler, opposingBattler) > UQ_4_12(0.0)
                    || AI_GetMoveEffectiveness(aiMove, battler, opposingPartner) > UQ_4_12(0.0))
                    && aiMove != MOVE_NONE)
                return FALSE;
        }
    }
    else
    {
        for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
        {
            aiMove = gBattleMons[battler].moves[moveIndex];
            if (!IsMoveIneffective(aiMove, battler, opposingBattler))
                return FALSE;
        }
    }

    if (RandomPercentage(RNG_AI_SWITCH_ALL_MOVES_BAD, GetSwitchChance(SHOULD_SWITCH_ALL_MOVES_BAD)))
        return SetSwitchinAndSwitch(battler, PARTY_SIZE);
    return FALSE;
}

static bool32 FindMonThatHitsWonderGuard(u32 battler)
{
    u32 opposingBattler = GetOppositeBattler(battler);
    s32 i, j;
    s32 firstId;
    s32 lastId; // + 1
    struct Pokemon *party = NULL;
    u16 move;

    if (IsDoubleBattle())
        return FALSE;

    if (AI_DATA->abilities[opposingBattler] != ABILITY_WONDER_GUARD)
        return FALSE;

    // Check if Pokémon has a super effective move.
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        move = gBattleMons[battler].moves[i];
        if (move != MOVE_NONE)
        {
            if (AI_GetMoveEffectiveness(move, battler, opposingBattler) >= UQ_4_12(2.0))
                return FALSE;
        }
    }

    // Get party information.
    GetAIPartyIndexes(battler, &firstId, &lastId);
    party = GetBattlerParty(battler);

    // Find a Pokémon in the party that has a super effective move.
    for (i = firstId; i < lastId; i++)
    {
        if (!IsValidForBattle(&party[i]))
            continue;
        if (i == gBattlerPartyIndexes[battler])
            continue;
        if (IsAceMon(battler, i))
            continue;

        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            move = GetMonData(&party[i], MON_DATA_MOVE1 + j);
            if (move != MOVE_NONE)
            {
                // Found a mon
                if (AI_GetMoveEffectiveness(move, battler, opposingBattler) >= UQ_4_12(2.0) && RandomPercentage(RNG_AI_SWITCH_WONDER_GUARD, GetSwitchChance(SHOULD_SWITCH_WONDER_GUARD)))
                    return SetSwitchinAndSwitch(battler, i);
            }
        }
    }

    return FALSE; // There is not a single Pokémon in the party that has a super effective move against a mon with Wonder Guard.
}

static bool32 FindMonThatAbsorbsOpponentsMove(u32 battler)
{
    u8 battlerIn1, battlerIn2;
    u8 numAbsorbingAbilities = 0;
    u16 absorbingTypeAbilities[3]; // Array size is maximum number of absorbing abilities for a single type
    s32 firstId;
    s32 lastId;
    struct Pokemon *party;
    u16 monAbility, aiMove;
    u32 opposingBattler = GetOppositeBattler(battler);
    u32 incomingMove = AI_DATA->lastUsedMove[opposingBattler];
    u32 incomingType = GetMoveType(incomingMove);
    u32 predictedMove = incomingMove; // Update for move prediction
    u32 predictedType = GetMoveType(predictedMove);
    bool32 isOpposingBattlerChargingOrInvulnerable = (IsSemiInvulnerable(opposingBattler, incomingMove) || IsTwoTurnNotSemiInvulnerableMove(opposingBattler, incomingMove));
    s32 i, j;

    DEBUG_ABILITY("--- FindMonThatAbsorbsOpponentsMove ---");
    DEBUG_ABILITY("Incoming move: %d (type: %d), Predicted move: %d (type: %d)",
                  incomingMove, incomingType, predictedMove, predictedType);
    DEBUG_ABILITY("Opponent charging/invulnerable: %s", isOpposingBattlerChargingOrInvulnerable ? "YES" : "NO");


    if (GetBattlerSide(battler) == B_SIDE_OPPONENT){ //Making these checks that only apply for the AI's side
        if (!(AI_THINKING_STRUCT->aiFlags[GetThinkingBattler(battler)] & AI_FLAG_SMART_SWITCHING))
            return FALSE;
        if (gBattleStruct->prevTurnSpecies[battler] != gBattleMons[battler].species) // AI mon has changed, player's behaviour no longer reliable; note to override this if using AI_FLAG_PREDICT_MOVE
            return FALSE; 
        if (HasSuperEffectiveMoveAgainstOpponents(battler, TRUE) && (RandomPercentage(RNG_AI_SWITCH_ABSORBING_STAY_IN, STAY_IN_ABSORBING_PERCENTAGE) || AI_DATA->aiSwitchPredictionInProgress))
            return FALSE;
        if (AreStatsRaised(battler))
            return FALSE;
        // Don't switch if mon could outspeed and OHKO 
        for (i = 0; i < MAX_MON_MOVES; i++)
        {
            aiMove = gBattleMons[battler].moves[i];
            if (aiMove != MOVE_NONE)
            {
                // Only check damage if it's a damaging move
                if (!IsBattleMoveStatus(aiMove))
                {
                    if ((AI_DATA->simulatedDmg[battler][opposingBattler][i].expected > gBattleMons[opposingBattler].hp) && AI_IsFaster(battler, opposingBattler, aiMove))
                        return FALSE;
                }
            }
        }
    }    


    if (IsDoubleBattle())
    {
        battlerIn1 = battler;
        if (gAbsentBattlerFlags & (1u << GetPartnerBattler(battler)))
            battlerIn2 = battler;
        else
            battlerIn2 = GetPartnerBattler(battler);
    }
    else
    {
        battlerIn1 = battler;
        battlerIn2 = battler;
    }

    // Create an array of possible absorb abilities so the AI considers all of them
    DEBUG_ABILITY("Determining absorbing abilities for type %d:", predictedType);
    if (predictedType == TYPE_FIRE)
    {
        absorbingTypeAbilities[numAbsorbingAbilities++] = ABILITY_FLASH_FIRE;
        DEBUG_ABILITY("Added Flash Fire");
    }
    else if (predictedType == TYPE_WATER || (isOpposingBattlerChargingOrInvulnerable && incomingType == TYPE_WATER))
    {
        absorbingTypeAbilities[numAbsorbingAbilities++] = ABILITY_WATER_ABSORB;
        absorbingTypeAbilities[numAbsorbingAbilities++] = ABILITY_DRY_SKIN;
        DEBUG_ABILITY("Added Water Absorb, Dry Skin");
        if (B_REDIRECT_ABILITY_IMMUNITY >= GEN_5)
        {
            absorbingTypeAbilities[numAbsorbingAbilities++] = ABILITY_STORM_DRAIN;
            DEBUG_ABILITY("Added Storm Drain");
        }
    }
    else if (predictedType == TYPE_ELECTRIC || (isOpposingBattlerChargingOrInvulnerable && incomingType == TYPE_ELECTRIC))
    {
        absorbingTypeAbilities[numAbsorbingAbilities++] = ABILITY_VOLT_ABSORB;
        absorbingTypeAbilities[numAbsorbingAbilities++] = ABILITY_MOTOR_DRIVE;
        DEBUG_ABILITY("Added Volt Absorb, Motor Drive");
        if (B_REDIRECT_ABILITY_IMMUNITY >= GEN_5)
        {
            absorbingTypeAbilities[numAbsorbingAbilities++] = ABILITY_LIGHTNING_ROD;
            DEBUG_ABILITY("Added Lightning Rod");
        }
    }
    else if (predictedType == TYPE_GRASS || (isOpposingBattlerChargingOrInvulnerable && incomingType == TYPE_GRASS))
    {
        absorbingTypeAbilities[numAbsorbingAbilities++] = ABILITY_SAP_SIPPER;
        DEBUG_ABILITY("Added Sap Sipper");
    }
    else if (predictedType == TYPE_GROUND || (isOpposingBattlerChargingOrInvulnerable && incomingType == TYPE_GROUND))
    {
        absorbingTypeAbilities[numAbsorbingAbilities++] = ABILITY_EARTH_EATER;
        absorbingTypeAbilities[numAbsorbingAbilities++] = ABILITY_LEVITATE;
        DEBUG_ABILITY("Added Earth Eater, Levitate");
    }
    else if (IsSoundMove(predictedMove) || (isOpposingBattlerChargingOrInvulnerable && IsSoundMove(incomingMove)))
    {
        absorbingTypeAbilities[numAbsorbingAbilities++] = ABILITY_SOUNDPROOF;
        DEBUG_ABILITY("Added Soundproof");
    }
    else
    {
        DEBUG_ABILITY("No absorbing abilities for this move type - returning false");
        return FALSE;
    }
    DEBUG_ABILITY("Total absorbing abilities found: %d", numAbsorbingAbilities);

    // Check current mon for all absorbing abilities
    DEBUG_ABILITY("Checking if current mon already has absorbing ability:");
    for (i = 0; i < numAbsorbingAbilities; i++)
    {
        if (gBattleMons[battler].ability == absorbingTypeAbilities[i])
        {
            DEBUG_ABILITY("Current mon already has absorbing ability %d - not switching", absorbingTypeAbilities[i]);
            return FALSE;
        }
    }

    // Check party for mon with ability that absorbs move
    GetAIPartyIndexes(battler, &firstId, &lastId);
    party = GetBattlerParty(battler);
    DEBUG_ABILITY("Checking party slots %d to %d for absorbing abilities", firstId, lastId - 1);

    for (i = firstId; i < lastId; i++)
    {
        if (!IsValidForBattle(&party[i]))
            continue;
        if (i == gBattlerPartyIndexes[battlerIn1])
            continue;
        if (i == gBattlerPartyIndexes[battlerIn2])
            continue;
        if (i == gBattleStruct->monToSwitchIntoId[battlerIn1])
            continue;
        if (i == gBattleStruct->monToSwitchIntoId[battlerIn2])
            continue;
        if (IsAceMon(battler, i))
            continue;

        monAbility = GetMonAbility(&party[i]);
        DEBUG_ABILITY("Checking party slot %d (species: %d, ability: %d)", i, GetMonData(&party[i], MON_DATA_SPECIES), monAbility);

        for (j = 0; j < numAbsorbingAbilities; j++)
        {
            // Found a mon
            if (absorbingTypeAbilities[j] == monAbility)
            {
                u32 switchChance = GetSwitchChance(SHOULD_SWITCH_ABSORBS_MOVE);
                DEBUG_ABILITY("Found absorbing mon! Ability %d matches, switch chance: %d%%", monAbility, switchChance);
                if (RandomPercentage(RNG_AI_SWITCH_ABSORBING, switchChance))
                {
                    DEBUG_ABILITY("RNG passed - switching to absorbing mon in slot %d", i);
                    return SetSwitchinAndSwitch(battler, i);
                }
                else
                {
                    DEBUG_ABILITY("RNG failed - not switching despite having absorbing mon");
                }
            }
        }
    }
    DEBUG_ABILITY("No suitable absorbing mon found in party");
    return FALSE;
}

static bool32 ShouldSwitchIfOpponentChargingOrInvulnerable(u32 battler)
{
    u32 opposingBattler = GetOppositeBattler(battler);
    u32 incomingMove = AI_DATA->lastUsedMove[opposingBattler];
    bool32 isOpposingBattlerChargingOrInvulnerable = (IsSemiInvulnerable(opposingBattler, incomingMove) || IsTwoTurnNotSemiInvulnerableMove(opposingBattler, incomingMove));

    if (IsDoubleBattle() || !(AI_THINKING_STRUCT->aiFlags[GetThinkingBattler(battler)] & AI_FLAG_SMART_SWITCHING))
        return FALSE;

    if (isOpposingBattlerChargingOrInvulnerable && AI_DATA->mostSuitableMonId[battler] != PARTY_SIZE && RandomPercentage(RNG_AI_SWITCH_FREE_TURN, GetSwitchChance(SHOULD_SWITCH_FREE_TURN)))
        return SetSwitchinAndSwitch(battler, PARTY_SIZE);

    return FALSE;
}

static bool32 ShouldSwitchIfTrapperInParty(u32 battler)
{
    s32 firstId;
    s32 lastId;
    struct Pokemon *party;
    s32 i;
    u16 monAbility;
    s32 opposingBattler =  GetOppositeBattler(battler);

    // Only use this if AI_FLAG_SMART_SWITCHING is set for the trainer
    if (!(AI_THINKING_STRUCT->aiFlags[GetThinkingBattler(battler)] & AI_FLAG_SMART_SWITCHING))
        return FALSE;

    // Check if current mon has an ability that traps opponent
    if (CanAbilityTrapOpponent(gBattleMons[battler].ability, opposingBattler))
        return FALSE;

    // Check party for mon with ability that traps opponent
    GetAIPartyIndexes(battler, &firstId, &lastId);
    party = GetBattlerParty(battler);

    for (i = firstId; i < lastId; i++)
    {
        if (IsAceMon(battler, i))
            return FALSE;

        monAbility = GetMonAbility(&party[i]);

        if (CanAbilityTrapOpponent(monAbility, opposingBattler) || (CanAbilityTrapOpponent(AI_GetBattlerAbility(opposingBattler), opposingBattler) && monAbility == ABILITY_TRACE))
        {
            // If mon in slot i is the most suitable switchin candidate, then it's a trapper than wins 1v1
            if (i == AI_DATA->mostSuitableMonId[battler] && RandomPercentage(RNG_AI_SWITCH_FREE_TURN, GetSwitchChance(SHOULD_SWITCH_FREE_TURN)))
                return SetSwitchinAndSwitch(battler, PARTY_SIZE);
        }
    }
    return FALSE;
}

static bool32 ShouldSwitchIfBadlyStatused(u32 battler)
{
    bool32 switchMon = FALSE;
    u16 monAbility = AI_DATA->abilities[battler];
    u16 holdEffect = AI_DATA->holdEffects[battler];
    u8 opposingPosition = BATTLE_OPPOSITE(GetBattlerPosition(battler));
    u8 opposingBattler = GetBattlerAtPosition(opposingPosition);
    bool32 hasStatRaised = AnyStatIsRaised(battler);

    //Perish Song
    if (gStatuses3[battler] & STATUS3_PERISH_SONG
        && gDisableStructs[battler].perishSongTimer == 0
        && monAbility != ABILITY_SOUNDPROOF
        && RandomPercentage(RNG_AI_SWITCH_PERISH_SONG, GetSwitchChance(SHOULD_SWITCH_PERISH_SONG)))
        return SetSwitchinAndSwitch(battler, PARTY_SIZE);

    if (AI_THINKING_STRUCT->aiFlags[GetThinkingBattler(battler)] & AI_FLAG_SMART_SWITCHING)
    {
        //Yawn
        if (gStatuses3[battler] & STATUS3_YAWN
            && CanBeSlept(battler, monAbility, BLOCKED_BY_SLEEP_CLAUSE)
            && gBattleMons[battler].hp > gBattleMons[battler].maxHP / 3
            && RandomPercentage(RNG_AI_SWITCH_YAWN, GetSwitchChance(SHOULD_SWITCH_YAWN)))
        {
            switchMon = TRUE;

            // If we don't have a good switchin, not worth switching
            if (AI_DATA->mostSuitableMonId[battler] == PARTY_SIZE)
                switchMon = FALSE;

            // Check if Active Pokemon can KO opponent instead of switching
            // Will still fall asleep, but take out opposing Pokemon first
            if (AiExpectsToFaintPlayer(battler))
                switchMon = FALSE;

            // Checks to see if active Pokemon can do something against sleep
            if ((monAbility == ABILITY_NATURAL_CURE
                || monAbility == ABILITY_SHED_SKIN
                || monAbility == ABILITY_EARLY_BIRD)
                || holdEffect == (HOLD_EFFECT_CURE_SLP | HOLD_EFFECT_CURE_STATUS)
                || HasMove(battler, MOVE_SLEEP_TALK)
                || (HasMoveEffect(battler, MOVE_SNORE) && AI_GetMoveEffectiveness(MOVE_SNORE, battler, opposingBattler) >= UQ_4_12(2.0))
                || (IsBattlerGrounded(battler)
                    && (HasMove(battler, MOVE_MISTY_TERRAIN) || HasMove(battler, MOVE_ELECTRIC_TERRAIN)))
                )
                switchMon = FALSE;

            // Check if Active Pokemon evasion boosted and might be able to dodge until awake
            if (gBattleMons[battler].statStages[STAT_EVASION] > (DEFAULT_STAT_STAGE + 3)
                && AI_DATA->abilities[opposingBattler] != ABILITY_UNAWARE
                && AI_DATA->abilities[opposingBattler] != ABILITY_KEEN_EYE
                && AI_DATA->abilities[opposingBattler] != ABILITY_MINDS_EYE
                && (B_ILLUMINATE_EFFECT >= GEN_9 && AI_DATA->abilities[opposingBattler] != ABILITY_ILLUMINATE)
                && !(gBattleMons[battler].status2 & STATUS2_FORESIGHT)
                && !(gStatuses3[battler] & STATUS3_MIRACLE_EYED))
                switchMon = FALSE;
            
            if (switchMon)
                return SetSwitchinAndSwitch(battler, PARTY_SIZE);
        }

        // Secondary Damage
        if (monAbility != ABILITY_MAGIC_GUARD
            && !AiExpectsToFaintPlayer(battler)
            && AI_DATA->mostSuitableMonId[battler] != PARTY_SIZE)
        {
            //Toxic
            if (((gBattleMons[battler].status1 & STATUS1_TOXIC_COUNTER) >= STATUS1_TOXIC_TURN(2))
                && gBattleMons[battler].hp >= (gBattleMons[battler].maxHP / 3)
                && AI_DATA->mostSuitableMonId[battler] != PARTY_SIZE
                && (hasStatRaised ? RandomPercentage(RNG_AI_SWITCH_BADLY_POISONED, GetSwitchChance(SHOULD_SWITCH_BADLY_POISONED_STATS_RAISED)) : RandomPercentage(RNG_AI_SWITCH_BADLY_POISONED, GetSwitchChance(SHOULD_SWITCH_BADLY_POISONED))))
                return SetSwitchinAndSwitch(battler, PARTY_SIZE);

            //Cursed
            if (gBattleMons[battler].status2 & STATUS2_CURSED){
                if (HasMoveEffect(opposingBattler, EFFECT_PROTECT) && (hasStatRaised ? RandomPercentage(RNG_AI_SWITCH_CURSED, GetSwitchChance(SHOULD_SWITCH_CURSED_STATS_RAISED)) : RandomPercentage(RNG_AI_SWITCH_CURSED, GetSwitchChance(SHOULD_SWITCH_CURSED)))){
                    return SetSwitchinAndSwitch(battler, PARTY_SIZE);
                }else if (!CanAIFaintTarget(battler, opposingBattler, 4) && RandomPercentage(RNG_AI_SWITCH_CURSED, 50)){
                    return SetSwitchinAndSwitch(battler, PARTY_SIZE);
                }
            }

            //Nightmare
            if (gBattleMons[battler].status2 & STATUS2_NIGHTMARE
                && (hasStatRaised ? RandomPercentage(RNG_AI_SWITCH_NIGHTMARE, GetSwitchChance(SHOULD_SWITCH_NIGHTMARE_STATS_RAISED)) : RandomPercentage(RNG_AI_SWITCH_NIGHTMARE, GetSwitchChance(SHOULD_SWITCH_NIGHTMARE))))
                return SetSwitchinAndSwitch(battler, PARTY_SIZE);

            //Leech Seed
            if (gStatuses3[battler] & STATUS3_LEECHSEED
                && (hasStatRaised ? RandomPercentage(RNG_AI_SWITCH_SEEDED, GetSwitchChance(SHOULD_SWITCH_SEEDED_STATS_RAISED)) : RandomPercentage(RNG_AI_SWITCH_SEEDED, GetSwitchChance(SHOULD_SWITCH_SEEDED))))
                return SetSwitchinAndSwitch(battler, PARTY_SIZE);
        }

        // Infatuation
        if (gBattleMons[battler].status2 & STATUS2_INFATUATION
            && !AiExpectsToFaintPlayer(battler)
            && AI_DATA->mostSuitableMonId[battler] != PARTY_SIZE
            && RandomPercentage(RNG_AI_SWITCH_INFATUATION, GetSwitchChance(SHOULD_SWITCH_INFATUATION)))
            return SetSwitchinAndSwitch(battler, PARTY_SIZE);
    }

    return FALSE;
}

static bool32 ShouldSwitchIfAbilityBenefit(u32 battler)
{
    bool32 hasStatRaised = AnyStatIsRaised(battler);

    //Check if ability is blocked
    if (gStatuses3[battler] & STATUS3_GASTRO_ACID
        || IsNeutralizingGasOnField())
        return FALSE;

    switch(AI_DATA->abilities[battler])
    {
        case ABILITY_NATURAL_CURE:
            //Attempt to cure bad ailment
            if (gBattleMons[battler].status1 & (STATUS1_SLEEP | STATUS1_FREEZE | STATUS1_TOXIC_POISON)
                && AI_DATA->mostSuitableMonId[battler] != PARTY_SIZE
                && (hasStatRaised ? RandomPercentage(RNG_AI_SWITCH_NATURAL_CURE, GetSwitchChance(SHOULD_SWITCH_NATURAL_CURE_STRONG_STATS_RAISED)) : RandomPercentage(RNG_AI_SWITCH_NATURAL_CURE, GetSwitchChance(SHOULD_SWITCH_NATURAL_CURE_STRONG))))
                break;
            //Attempt to cure lesser ailment
            if ((gBattleMons[battler].status1 & STATUS1_ANY)
                && (gBattleMons[battler].hp >= gBattleMons[battler].maxHP / 2)
                && AI_DATA->mostSuitableMonId[battler] != PARTY_SIZE
                && (hasStatRaised ? RandomPercentage(RNG_AI_SWITCH_NATURAL_CURE, GetSwitchChance(SHOULD_SWITCH_NATURAL_CURE_WEAK_STATS_RAISED)) : RandomPercentage(RNG_AI_SWITCH_NATURAL_CURE, GetSwitchChance(SHOULD_SWITCH_NATURAL_CURE_WEAK))))
                break;

            return FALSE;

        case ABILITY_REGENERATOR:
            //Don't switch if ailment
            if (gBattleMons[battler].status1 & STATUS1_ANY)
                return FALSE;
            if ((gBattleMons[battler].hp <= ((gBattleMons[battler].maxHP * 2) / 3))
                 && AI_DATA->mostSuitableMonId[battler] != PARTY_SIZE
                 && (hasStatRaised ? RandomPercentage(RNG_AI_SWITCH_REGENERATOR, GetSwitchChance(SHOULD_SWITCH_REGENERATOR_STATS_RAISED)) : RandomPercentage(RNG_AI_SWITCH_REGENERATOR, GetSwitchChance(SHOULD_SWITCH_REGENERATOR))))
                break;

            return FALSE;

        default:
            return FALSE;
    }

    return SetSwitchinAndSwitch(battler, PARTY_SIZE);
}

static bool32 HasSuperEffectiveMoveAgainstOpponents(u32 battler, bool32 noRng)
{
    s32 i;
    u16 move;

    u32 opposingPosition = BATTLE_OPPOSITE(GetBattlerPosition(battler));
    u32 opposingBattler = GetBattlerAtPosition(opposingPosition);

    if (!(gAbsentBattlerFlags & (1u << opposingBattler)))
    {
        for (i = 0; i < MAX_MON_MOVES; i++)
        {
            move = gBattleMons[battler].moves[i];
            if (move == MOVE_NONE)
                continue;

            if (AI_GetMoveEffectiveness(move, battler, opposingBattler) >= UQ_4_12(2.0))
            {
                if (noRng)
                    return TRUE;
                if (Random() % 10 != 0)
                    return TRUE;
            }
        }
    }
    if (!IsDoubleBattle())
        return FALSE;

    opposingBattler = GetBattlerAtPosition(BATTLE_PARTNER(opposingPosition));

    if (!(gAbsentBattlerFlags & (1u << opposingBattler)))
    {
        for (i = 0; i < MAX_MON_MOVES; i++)
        {
            move = gBattleMons[battler].moves[i];
            if (move == MOVE_NONE)
                continue;

            if (AI_GetMoveEffectiveness(move, battler, opposingBattler) >= UQ_4_12(2.0))
            {
                if (noRng)
                    return TRUE;
                if (Random() % 10 != 0)
                    return TRUE;
            }
        }
    }

    return FALSE;
}

static bool32 FindMonWithFlagsAndSuperEffective(u32 battler, u16 flags, u32 percentChance)
{
    u32 battlerIn1, battlerIn2;
    s32 firstId;
    s32 lastId; // + 1
    struct Pokemon *party;
    s32 i, j;
    u16 move;

    //Separate the parts pertinent to AI-only logic vs predicting player logic
    if (GetBattlerSide(battler) == B_SIDE_OPPONENT){
        // Similar functionality handled more thoroughly by ShouldSwitchIfHasBadOdds
        if (AI_THINKING_STRUCT->aiFlags[GetThinkingBattler(battler)] & AI_FLAG_SMART_SWITCHING)
            return FALSE;
    }

    // if (GetBattlerSide(battler) == B_SIDE_PLAYER){
    //     DebugPrintf("Last Landed move for player is %d", gLastLandedMoves[battler]);
    // }

    if (gLastLandedMoves[battler] == MOVE_NONE)
        return FALSE;
    if (gLastLandedMoves[battler] == MOVE_UNAVAILABLE)
        return FALSE;
    if (gLastHitBy[battler] == 0xFF)
        return FALSE;
    if (IsBattleMoveStatus(gLastLandedMoves[battler]))
        return FALSE;

    if (IsDoubleBattle())
    {
        battlerIn1 = battler;
        if (gAbsentBattlerFlags & (1u << GetPartnerBattler(battler)))
            battlerIn2 = battler;
        else
            battlerIn2 = GetPartnerBattler(battler);
    }
    else
    {
        battlerIn1 = battler;
        battlerIn2 = battler;
    }

    GetAIPartyIndexes(battler, &firstId, &lastId);
    party = GetBattlerParty(battler);

    for (i = firstId; i < lastId; i++)
    {
        u16 species, monAbility;
        uq4_12_t typeMultiplier;
        u16 moveFlags = 0;

        if (!IsValidForBattle(&party[i]))
            continue;
        if (i == gBattlerPartyIndexes[battlerIn1])
            continue;
        if (i == gBattlerPartyIndexes[battlerIn2])
            continue;
        if (i == gBattleStruct->monToSwitchIntoId[battlerIn1])
            continue;
        if (i == gBattleStruct->monToSwitchIntoId[battlerIn2])
            continue;
        if (IsAceMon(battler, i))
            continue;

        species = GetMonData(&party[i], MON_DATA_SPECIES_OR_EGG);
        monAbility = GetMonAbility(&party[i]);
        typeMultiplier = CalcPartyMonTypeEffectivenessMultiplier(gLastLandedMoves[battler], species, monAbility);
        UpdateMoveResultFlags(typeMultiplier, &moveFlags);
        if (moveFlags & flags)
        {
            if (GetBattlerSide(battler) == B_SIDE_PLAYER){
                if (RandomPercentage(RNG_AI_SWITCH_SE_DEFENSIVE, percentChance)){
                    DEBUG_PREDICT("The custom Player Side call occurred, species is %d, and i is %d.", species, i);
                    return SetSwitchinAndSwitch(battler, i);
                }else{
                    DEBUG_PREDICT("Reached the immunity check, but RNG call did not go through.");
                }
            }
            battlerIn1 = gLastHitBy[battler];

            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                move = GetMonData(&party[i], MON_DATA_MOVE1 + j);
                if (move == 0)
                    continue;

                if (AI_GetMoveEffectiveness(move, battler, battlerIn1) >= UQ_4_12(2.0) && (RandomPercentage(RNG_AI_SWITCH_SE_DEFENSIVE, percentChance) || AI_DATA->aiSwitchPredictionInProgress))
                    return SetSwitchinAndSwitch(battler, i);
            }
        }
    }

    return FALSE;
}

static bool32 CanMonSurviveHazardSwitchin(u32 battler)
{
    u32 battlerIn1, battlerIn2;
    u32 hazardDamage = 0, battlerHp = gBattleMons[battler].hp;
    u32 ability = AI_DATA->abilities[battler], aiMove;
    s32 firstId, lastId, i, j;
    struct Pokemon *party;

    if (ability == ABILITY_REGENERATOR)
        battlerHp = (battlerHp * 133) / 100; // Account for Regenerator healing

    hazardDamage = GetSwitchinHazardsDamage(battler, &gBattleMons[battler]);

    // Battler will faint to hazards, check to see if another mon can clear them
    if (hazardDamage > battlerHp)
    {
        if (IsDoubleBattle())
        {
            battlerIn1 = battler;
            if (gAbsentBattlerFlags & (1u << GetPartnerBattler(battler)))
                battlerIn2 = battler;
            else
                battlerIn2 = GetPartnerBattler(battler);
        }
        else
        {
            battlerIn1 = battler;
            battlerIn2 = battler;
        }

        GetAIPartyIndexes(battler, &firstId, &lastId);
        party = GetBattlerParty(battler);

        for (i = firstId; i < lastId; i++)
        {
            if (!IsValidForBattle(&party[i]))
                continue;
            if (i == gBattlerPartyIndexes[battlerIn1])
                continue;
            if (i == gBattlerPartyIndexes[battlerIn2])
                continue;
            if (i == gBattleStruct->monToSwitchIntoId[battlerIn1])
                continue;
            if (i == gBattleStruct->monToSwitchIntoId[battlerIn2])
                continue;
            if (IsAceMon(battler, i))
                continue;

            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                aiMove = GetMonData(&party[i], MON_DATA_MOVE1 + j, NULL);
                if (IsHazardClearingMove(aiMove)) // Have a mon that can clear the hazards, so switching out is okay
                    return TRUE;
            }
        }
        // Faints to hazards and party can't clear them, don't switch out
        return FALSE;
    }
    return TRUE;
}

static bool32 ShouldSwitchIfEncored(u32 battler)
{
    u32 encoredMove = gDisableStructs[battler].encoredMove;
    u32 opposingBattler = GetOppositeBattler(battler);

    // Only use this if AI_FLAG_SMART_SWITCHING is set for the trainer
    if (!(AI_THINKING_STRUCT->aiFlags[GetThinkingBattler(battler)] & AI_FLAG_SMART_SWITCHING))
        return FALSE;

    // If not Encore'd don't switch
    if (encoredMove == MOVE_NONE)
        return FALSE;

    // Switch out if status move
    if (GetMoveCategory(encoredMove) == DAMAGE_CATEGORY_STATUS && RandomPercentage(RNG_AI_SWITCH_ENCORE, GetSwitchChance(SHOULD_SWITCH_ENCORE_STATUS)))
        return SetSwitchinAndSwitch(battler, PARTY_SIZE);

    // Stay in if effective move
    else if (AI_GetMoveEffectiveness(encoredMove, battler, opposingBattler) >= UQ_4_12(2.0))
        return FALSE;

    // Switch out 50% of the time otherwise
    else if ((RandomPercentage(RNG_AI_SWITCH_ENCORE, GetSwitchChance(SHOULD_SWITCH_ENCORE_DAMAGE)) || AI_DATA->aiSwitchPredictionInProgress) && AI_DATA->mostSuitableMonId[battler] != PARTY_SIZE)
        return SetSwitchinAndSwitch(battler, PARTY_SIZE);

    return FALSE;
}

static bool32 ShouldSwitchIfBadChoiceLock(u32 battler)
{
    u32 holdEffect = GetBattlerHoldEffect(battler, FALSE);

    if (HOLD_EFFECT_CHOICE(holdEffect) && IsBattlerItemEnabled(battler))
    {
        if (GetMoveCategory(AI_DATA->lastUsedMove[battler]) == DAMAGE_CATEGORY_STATUS && RandomPercentage(RNG_AI_SWITCH_CHOICE_LOCKED, GetSwitchChance(SHOULD_SWITCH_CHOICE_LOCKED)))
            return SetSwitchinAndSwitch(battler, PARTY_SIZE);
    }

    return FALSE;
}

// AI should switch if it's become setup fodder and has something better to switch to
static bool32 ShouldSwitchIfAttackingStatsLowered(u32 battler)
{
    s8 attackingStage = gBattleMons[battler].statStages[STAT_ATK];
    s8 spAttackingStage = gBattleMons[battler].statStages[STAT_SPATK];

    // Only use this if AI_FLAG_SMART_SWITCHING is set for the trainer
    if (!(AI_THINKING_STRUCT->aiFlags[GetThinkingBattler(battler)] & AI_FLAG_SMART_SWITCHING))
        return FALSE;

    // Physical attacker (This check needs improvement)
    if ((UQ_4_12_TO_INT(gBattleMons[battler].attack * GetAtkSpAtkGapThreshold(battler)) > gBattleMons[battler].spAttack) && HasMoveWithCategory(battler, DAMAGE_CATEGORY_PHYSICAL))
    {
        //Being a little more aggressive for now; in the future, stage checks will be less frequent
        //Because I'll incorporate damage checks

        // Don't switch if attack isn't below -3
        if (attackingStage > DEFAULT_STAT_STAGE - 4)
            return FALSE;
        // 50% chance if attack at -4 and have a good candidate mon
        else if (attackingStage <= DEFAULT_STAT_STAGE - 4)
        {
            if (AI_DATA->mostSuitableMonId[battler] != PARTY_SIZE && (RandomPercentage(RNG_AI_SWITCH_STATS_LOWERED, GetSwitchChance(SHOULD_SWITCH_ATTACKING_STAT_MINUS_TWO)) || AI_DATA->aiSwitchPredictionInProgress))
                return SetSwitchinAndSwitch(battler, PARTY_SIZE);
        }
        // // If at -6, switch out regardless
        // else if ((attackingStage == DEFAULT_STAT_STAGE - 6) && RandomPercentage(RNG_AI_SWITCH_STATS_LOWERED, GetSwitchChance(SHOULD_SWITCH_ATTACKING_STAT_MINUS_THREE_PLUS)))
        //     return SetSwitchinAndSwitch(battler, PARTY_SIZE);
    }

    // Special attacker (This check needs improvement)
    else if ((UQ_4_12_TO_INT(gBattleMons[battler].spAttack * GetAtkSpAtkGapThreshold(battler)) > gBattleMons[battler].attack) && HasMoveWithCategory(battler, DAMAGE_CATEGORY_SPECIAL))
    {
        // Don't switch if attack isn't below -3
        if (spAttackingStage > DEFAULT_STAT_STAGE - 4)
            return FALSE;
        // 50% chance if attack at -4 and have a good candidate mon
        else if (spAttackingStage <= DEFAULT_STAT_STAGE - 4)
        {
            if (AI_DATA->mostSuitableMonId[battler] != PARTY_SIZE && (RandomPercentage(RNG_AI_SWITCH_STATS_LOWERED, GetSwitchChance(SHOULD_SWITCH_ATTACKING_STAT_MINUS_TWO)) || AI_DATA->aiSwitchPredictionInProgress))
                return SetSwitchinAndSwitch(battler, PARTY_SIZE);
        }
        // If at -6, switch out regardless
        // else if ((spAttackingStage == DEFAULT_STAT_STAGE - 6) && RandomPercentage(RNG_AI_SWITCH_STATS_LOWERED, GetSwitchChance(SHOULD_SWITCH_ATTACKING_STAT_MINUS_THREE_PLUS)))
        //     return SetSwitchinAndSwitch(battler, PARTY_SIZE);
    }
    return FALSE;
}

static bool32 HasGoodSubstituteMove(u32 battler)
{
    int i;
    u32 aiMove, aiMoveEffect, opposingBattler = GetOppositeBattler(battler);
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        aiMove = gBattleMons[battler].moves[i];
        aiMoveEffect = GetMoveEffect(aiMove);
        if (IsSubstituteEffect(aiMoveEffect))
        {
            if (IncreaseSubstituteMoveScore(battler, opposingBattler, aiMove) > 0)
                return TRUE;
        }
    }
    return FALSE;
}

//NOTE: Need to verify whether AiPartyMon indexes align with SetSwitchinAndSwitch indices
//Follow-up to Note: Seems to be so, since testing seems to have succeeded, but try to confirm in the future.
static bool32 FindHealAbsorbMonWithSwitches(u32 battler, u16 move, u32 numRequiredSwitches){

    u32 i, count;
    u32 moveType = GetMoveType(move);
    struct AiPartyMon *aiMons;

    if(IsValidDoubleBattle(battler)){
        //Only consider singles for now.
        return FALSE;
    }

    if (moveType != TYPE_ELECTRIC && moveType != TYPE_WATER && moveType != TYPE_GROUND){
        return FALSE;
    }

    aiMons = AI_PARTY->mons[GetBattlerSide(battler)];

    count = AI_PARTY->count[GetBattlerSide(battler)];

    for (i=0; i < count; i++){
        u16 monAbility = aiMons[i].ability;
        bool32 isAbilityTypeMatch =  (
            (monAbility == ABILITY_VOLT_ABSORB && moveType == TYPE_ELECTRIC)
            || (monAbility == ABILITY_EARTH_EATER && moveType == TYPE_GROUND)
            || ((monAbility == ABILITY_WATER_ABSORB || monAbility == ABILITY_DRY_SKIN) && moveType == TYPE_WATER)
        );

        if (!isAbilityTypeMatch) continue;
        if (aiMons[i].species == gBattleMons[battler].species) continue;
        //The switch-in mon needs to have had a large enough track record of switching in
        else if (aiMons[i].switchInCount < numRequiredSwitches) continue;

        //Perform a switch with an absorbing mon that doesn't violate the above conditions
        if (RandomPercentage(RNG_AI_SWITCH_ABSORBING_STAY_IN, 50)){
            DebugPrintf("HealAbsorb check was passed, but RNG check failed.");
            return FALSE;
        }else{
            DebugPrintf("HealAbsorb RNG check passed.");
            return SetSwitchinAndSwitch(battler, i);
        }
    }
    return FALSE;

}

bool32 ShouldSwitch(u32 battler)
{
    u32 battlerIn1, battlerIn2;
    s32 firstId;
    s32 lastId; // + 1
    struct Pokemon *party;
    s32 i;
    s32 availableToSwitch;

    DEBUG_SWITCH("=== ShouldSwitch called for battler %d (species: %d, HP: %d/%d) ===",
                 battler, gBattleMons[battler].species, gBattleMons[battler].hp, gBattleMons[battler].maxHP);

    // Check escape prevention conditions
    if (gBattleMons[battler].status2 & (STATUS2_WRAPPED | STATUS2_ESCAPE_PREVENTION))
    {
        DEBUG_SWITCH("Cannot switch - trapped by wrap/escape prevention");
        return FALSE;
    }
    if (gStatuses3[battler] & STATUS3_ROOTED)
    {
        DEBUG_SWITCH("Cannot switch - rooted by Ingrain");
        return FALSE;
    }
    if (IsAbilityPreventingEscape(battler))
    {
        DEBUG_SWITCH("Cannot switch - ability preventing escape");
        return FALSE;
    }
    if (gBattleTypeFlags & BATTLE_TYPE_ARENA)
    {
        DEBUG_SWITCH("Cannot switch - Arena battle type");
        return FALSE;
    }
    
    if (GetBattlerSide(battler) == B_SIDE_PLAYER){
        DEBUG_PREDICT("=== Player Switch Prediction Logic ===");
        //Special player switch-in check
        //Note, even if player mon can outspeed and OHKO, still carry through with the check, to prevent switch abuse in these cases

        u32 aiBattler = GetOpposingSideBattler(battler);
        struct AiPartyMon *aiMons = AI_PARTY->mons[GetBattlerSide(battler)];
        u16 aiBestDmgMove;
        u16 storedMove;
        bool32 immuneMonFound;

        DEBUG_PREDICT("AI battler: %d, Player battler: %d", aiBattler, battler);

        //AI battler must be able to do damage
        u32 bestDamage = GetBestDmgFromBattler(aiBattler, battler);
        if (bestDamage == 0){
            DEBUG_PREDICT("Player ShouldSwitch call: player mon takes no damage from AI mon's damaging moves; aborted.");
            return FALSE;
        }
        DEBUG_PREDICT("AI's best damage against player: %d", bestDamage);

        aiBestDmgMove = (u16)GetBestDmgMoveFromBattler(aiBattler, battler);
        DEBUG_PREDICT("AI's best damage move: %d", aiBestDmgMove);

        //Before the standard check for immunity looping, do a check for immunity healing abilities just to prevent them from getting
        //infinite healing
        if (FindHealAbsorbMonWithSwitches(battler, aiBestDmgMove, MIN_SWITCHES_FOR_PREDICTION)){
            DEBUG_PREDICT("Heal Absorb mon check is being reached - switching!");
            return TRUE;
        }

        u32 switchCount = aiMons[gBattlerPartyIndexes[battler]].switchInCount;
        DEBUG_PREDICT("Current mon switch count: %d (required: %d)", switchCount, MIN_SWITCHES_FOR_PREDICTION);
        if (switchCount < MIN_SWITCHES_FOR_PREDICTION){
            DEBUG_PREDICT("Player ShouldSwitch call: Current mon hasn't switched out enough; aborted.");
            return FALSE;
        }

        //Switch prediction only triggered if the player mon is immune to one of the battler's moves
        bool32 hasIneffectiveMove = HasIneffectiveDamagingMove(aiBattler, battler);
        DEBUG_PREDICT("AI has ineffective move against player: %s", hasIneffectiveMove ? "YES" : "NO");
        if (!hasIneffectiveMove){
            DEBUG_PREDICT("Player ShouldSwitch call: player mon isn't immune to AI mon's moves; aborted.");
            return FALSE;
        }


        //Temporary inject last used move for FindMonThatAbsorbsOpponentsMove
        storedMove = AI_DATA->lastUsedMove[aiBattler];
        AI_DATA->lastUsedMove[aiBattler] = aiBestDmgMove;
        DEBUG_PREDICT("Testing absorb logic - injected move: %d (stored: %d)", aiBestDmgMove, storedMove);
        immuneMonFound = FindMonThatAbsorbsOpponentsMove(battler);
        AI_DATA->lastUsedMove[aiBattler] = storedMove;
        DEBUG_PREDICT("Absorb mon found: %s", immuneMonFound ? "YES" : "NO");
        if (immuneMonFound){
            DEBUG_PREDICT("Player Switch logic on Absorb is triggered - switching!");
            return TRUE;
        }

        //Temporary inject last landed move for FindMonWithFlagsAndSuperEffective
        storedMove = gLastLandedMoves[aiBattler];
        gLastLandedMoves[battler] = aiBestDmgMove;
        DEBUG_PREDICT("Testing immunity logic - injected move: %d (stored: %d)", aiBestDmgMove, storedMove);
        immuneMonFound = FindMonWithFlagsAndSuperEffective(battler, MOVE_RESULT_DOESNT_AFFECT_FOE, 50);
        gLastLandedMoves[battler] = storedMove;
        DEBUG_PREDICT("Immune mon found: %s", immuneMonFound ? "YES" : "NO");
        if (immuneMonFound){
            DEBUG_PREDICT("Player Switch logic on Immunity is triggered - switching!");
            return TRUE;
        }else{
            DEBUG_PREDICT("Player Switch logic on immunity/Absorb is not triggered - staying in.");
            return FALSE;
        }
    }
    // Sequence Switching AI never switches mid-battle
    if (AI_THINKING_STRUCT->aiFlags[GetThinkingBattler(battler)] & AI_FLAG_SEQUENCE_SWITCHING)
    {
        DEBUG_SWITCH("Sequence switching AI - never switches mid-battle");
        return FALSE;
    }

    DEBUG_SWITCH("=== AI Switch Decision Logic ===");
    availableToSwitch = 0;

    if (IsDoubleBattle())
    {
        u32 partner = GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerAtPosition(battler)));
        battlerIn1 = battler;
        if (gAbsentBattlerFlags & (1u << partner))
            battlerIn2 = battler;
        else
            battlerIn2 = partner;
        DEBUG_SWITCH("Double battle - battlerIn1: %d, battlerIn2: %d", battlerIn1, battlerIn2);
    }
    else
    {
        battlerIn1 = battler;
        battlerIn2 = battler;
        DEBUG_SWITCH("Single battle - battler: %d", battler);
    }

    GetAIPartyIndexes(battler, &firstId, &lastId);
    party = GetBattlerParty(battler);
    DEBUG_SWITCH("Party range: %d to %d", firstId, lastId - 1);

    for (i = firstId; i < lastId; i++)
    {
        if (!IsValidForBattle(&party[i]))
            continue;
        if (i == gBattlerPartyIndexes[battlerIn1])
            continue;
        if (i == gBattlerPartyIndexes[battlerIn2])
            continue;
        if (i == gBattleStruct->monToSwitchIntoId[battlerIn1])
            continue;
        if (i == gBattleStruct->monToSwitchIntoId[battlerIn2])
            continue;
        if (IsAceMon(battler, i))
        {
            DEBUG_SWITCH("Slot %d is ace mon - skipping for now", i);
            continue;
        }

        availableToSwitch++;
    }

    DEBUG_SWITCH("Available mons to switch to: %d", availableToSwitch);
    if (availableToSwitch == 0)
    {
        DEBUG_SWITCH("No available mons to switch to - staying in");
        return FALSE;
    }

    // NOTE: The sequence of the below functions matter! Do not change unless you have carefully considered the outcome.
    // Since the order is sequential, and some of these functions prompt switch to specific party members.

    // FindMon functions can prompt a switch to specific party members that override GetMostSuitableMonToSwitchInto
    // The rest can prompt a switch to party member returned by GetMostSuitableMonToSwitchInto

    DEBUG_SWITCH("=== Checking Switch Conditions (in priority order) ===");

    if (FindMonThatHitsWonderGuard(battler))
    {
        DEBUG_REASON("SWITCHING: Found mon that hits Wonder Guard");
        return TRUE;
    }
    if ((AI_THINKING_STRUCT->aiFlags[GetThinkingBattler(battler)] & AI_FLAG_SMART_SWITCHING) && (CanMonSurviveHazardSwitchin(battler) == FALSE))
    {
        DEBUG_REASON("NOT SWITCHING: Cannot survive hazard switch-in");
        return FALSE;
    }
    if (HasGoodSubstituteMove(battler))
    {
        DEBUG_REASON("NOT SWITCHING: Has good substitute move");
        return FALSE;
    }
    if (ShouldSwitchIfTrapperInParty(battler))
    {
        DEBUG_REASON("SWITCHING: Trapper in party");
        return TRUE;
    }
    if (FindMonThatAbsorbsOpponentsMove(battler))
    {
        DEBUG_REASON("SWITCHING: Found mon that absorbs opponent's move");
        return TRUE;
    }
    if (ShouldSwitchIfOpponentChargingOrInvulnerable(battler))
    {
        DEBUG_REASON("SWITCHING: Opponent charging or invulnerable");
        return TRUE;
    }
    if (ShouldSwitchIfTruant(battler))
    {
        DEBUG_REASON("SWITCHING: Truant vulnerability");
        return TRUE;
    }
    if (ShouldSwitchIfAllMovesBad(battler))
    {
        DEBUG_REASON("SWITCHING: All moves are bad/ineffective");
        return TRUE;
    }
    if (ShouldSwitchIfBadlyStatused(battler))
    {
        DEBUG_REASON("SWITCHING: Badly statused");
        return TRUE;
    }
    if (ShouldSwitchIfAbilityBenefit(battler))
    {
        DEBUG_REASON("SWITCHING: Ability benefit (Natural Cure/Regenerator)");
        return TRUE;
    }
    if (ShouldSwitchIfHasBadOdds(battler))
    {
        DEBUG_REASON("SWITCHING: Has bad odds in current matchup");
        return TRUE;
    }
    if (ShouldSwitchIfEncored(battler))
    {
        DEBUG_REASON("SWITCHING: Encored into bad move");
        return TRUE;
    }
    if (ShouldSwitchIfBadChoiceLock(battler))
    {
        DEBUG_REASON("SWITCHING: Bad choice item lock");
        return TRUE;
    }
    if (ShouldSwitchIfAttackingStatsLowered(battler))
    {
        DEBUG_REASON("SWITCHING: Attacking stats severely lowered");
        return TRUE;
    }

    // Removing switch capabilites under specific conditions
    // These Functions prevent the "FindMonWithFlagsAndSuperEffective" from getting out of hand.
    // We don't use FindMonWithFlagsAndSuperEffective with AI_FLAG_SMART_SWITCHING, so we can bail early.
    DEBUG_SWITCH("=== Final Switch Checks ===");
    if (AI_THINKING_STRUCT->aiFlags[GetThinkingBattler(battler)] & AI_FLAG_SMART_SWITCHING)
    {
        DEBUG_REASON("NOT SWITCHING: Smart switching enabled - skipping default logic");
        return FALSE;
    }
    if (HasSuperEffectiveMoveAgainstOpponents(battler, FALSE))
    {
        DEBUG_REASON("NOT SWITCHING: Has super effective move against opponents");
        return FALSE;
    }
    if (AreStatsRaised(battler))
    {
        DEBUG_REASON("NOT SWITCHING: Stats are raised");
        return FALSE;
    }

    // Default Function
    // Can prompt switch if AI has a pokemon in party that resists current opponent & has super effective move
    DEBUG_SWITCH("Checking default switch logic (type matchup + super effective move)");
    if (FindMonWithFlagsAndSuperEffective(battler, MOVE_RESULT_DOESNT_AFFECT_FOE, 50))
    {
        DEBUG_REASON("SWITCHING: Found immune mon with super effective move (50% chance)");
        return TRUE;
    }
    if (FindMonWithFlagsAndSuperEffective(battler, MOVE_RESULT_NOT_VERY_EFFECTIVE, 33))
    {
        DEBUG_REASON("SWITCHING: Found resistant mon with super effective move (33% chance)");
        return TRUE;
    }

    DEBUG_SWITCH("No switch conditions met - staying in");
    return FALSE;
}

bool32 IsSwitchinValid(u32 battler)
{
    // Edge case: See if partner already chose to switch into the same mon
    if (IsDoubleBattle())
    {
        u32 partner = GetBattlerAtPosition(BATTLE_PARTNER(GetBattlerAtPosition(battler)));
        if (gBattleStruct->AI_monToSwitchIntoId[battler] == PARTY_SIZE) // Generic switch
        {
            if ((AI_DATA->shouldSwitch & (1u << partner)) && AI_DATA->monToSwitchInId[partner] == AI_DATA->mostSuitableMonId[battler])
            {
                return FALSE;
            }
        }
        else // Override switch
        {
            if ((AI_DATA->shouldSwitch & (1u << partner)) && AI_DATA->monToSwitchInId[partner] == gBattleStruct->AI_monToSwitchIntoId[battler])
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}

void AI_TrySwitchOrUseItem(u32 battler)
{
    struct Pokemon *party;
    u8 battlerIn1, battlerIn2;
    s32 firstId;
    s32 lastId; // + 1
    u8 battlerPosition = GetBattlerPosition(battler);
    party = GetBattlerParty(battler);

    if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
    {
        if (AI_DATA->shouldSwitch & (1u << battler) && IsSwitchinValid(battler))
        {
            BtlController_EmitTwoReturnValues(battler, 1, B_ACTION_SWITCH, 0);
            if (gBattleStruct->AI_monToSwitchIntoId[battler] == PARTY_SIZE)
            {
                s32 monToSwitchId = AI_DATA->mostSuitableMonId[battler];
                if (monToSwitchId == PARTY_SIZE)
                {
                    if (!IsDoubleBattle())
                    {
                        battlerIn1 = GetBattlerAtPosition(battlerPosition);
                        battlerIn2 = battlerIn1;
                    }
                    else
                    {
                        battlerIn1 = GetBattlerAtPosition(battlerPosition);
                        battlerIn2 = GetBattlerAtPosition(BATTLE_PARTNER(battlerPosition));
                    }

                    GetAIPartyIndexes(battler, &firstId, &lastId);

                    for (monToSwitchId = (lastId-1); monToSwitchId >= firstId; monToSwitchId--)
                    {
                        if (!IsValidForBattle(&party[monToSwitchId]))
                            continue;
                        if (monToSwitchId == gBattlerPartyIndexes[battlerIn1])
                            continue;
                        if (monToSwitchId == gBattlerPartyIndexes[battlerIn2])
                            continue;
                        if (monToSwitchId == gBattleStruct->monToSwitchIntoId[battlerIn1])
                            continue;
                        if (monToSwitchId == gBattleStruct->monToSwitchIntoId[battlerIn2])
                            continue;
                        if (IsAceMon(battler, monToSwitchId))
                            continue;

                        break;
                    }
                }

                gBattleStruct->AI_monToSwitchIntoId[battler] = monToSwitchId;
            }

            gBattleStruct->monToSwitchIntoId[battler] = gBattleStruct->AI_monToSwitchIntoId[battler];
            AI_DATA->monToSwitchInId[battler] = gBattleStruct->AI_monToSwitchIntoId[battler];
            return;
        }
        else if (ShouldUseItem(battler))
        {
            return;
        }
    }

    BtlController_EmitTwoReturnValues(battler, BUFFER_B, B_ACTION_USE_MOVE, BATTLE_OPPOSITE(battler) << 8);
}

// If there are two(or more) mons to choose from, always choose one that has baton pass
// as most often it can't do much on its own.
static u32 GetBestMonBatonPass(struct Pokemon *party, int firstId, int lastId, u8 invalidMons, int aliveCount, u32 battler, u32 opposingBattler)
{
    int i, j, bits = 0;

    for (i = firstId; i < lastId; i++)
    {
        if (invalidMons & (1u << i))
            continue;

        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            if (GetMonData(&party[i], MON_DATA_MOVE1 + j, NULL) == MOVE_BATON_PASS)
            {
                bits |= 1u << i;
                break;
            }
        }
    }

    if ((aliveCount == 2 || (aliveCount > 2 && Random() % 3 == 0)) && bits)
    {
        do
        {
            i = (Random() % (lastId - firstId)) + firstId;
        } while (!(bits & (1 << i)));
        return i;
    }

    return PARTY_SIZE;
}

static u32 GetBestMonTypeMatchup(struct Pokemon *party, int firstId, int lastId, u8 invalidMons, u32 battler, u32 opposingBattler)
{
    int i, bits = 0;

    while (bits != 0x3F) // All mons were checked.
    {
        uq4_12_t bestResist = UQ_4_12(1.0);
        int bestMonId = PARTY_SIZE;
        // Find the mon whose type is the most suitable defensively.
        for (i = firstId; i < lastId; i++)
        {
            if (!((1u << i) & invalidMons) && !((1u << i) & bits))
            {
                u16 species = GetMonData(&party[i], MON_DATA_SPECIES);
                uq4_12_t typeEffectiveness = UQ_4_12(1.0);

                u8 atkType1 = gBattleMons[opposingBattler].types[0];
                u8 atkType2 = gBattleMons[opposingBattler].types[1];
                u8 defType1 = gSpeciesInfo[species].types[0];
                u8 defType2 = gSpeciesInfo[species].types[1];

                typeEffectiveness = uq4_12_multiply(typeEffectiveness, (GetTypeModifier(atkType1, defType1)));
                if (atkType2 != atkType1)
                    typeEffectiveness = uq4_12_multiply(typeEffectiveness, (GetTypeModifier(atkType2, defType1)));
                if (defType2 != defType1)
                {
                    typeEffectiveness = uq4_12_multiply(typeEffectiveness, (GetTypeModifier(atkType1, defType2)));
                    if (atkType2 != atkType1)
                        typeEffectiveness = uq4_12_multiply(typeEffectiveness, (GetTypeModifier(atkType2, defType2)));
                }
                if (typeEffectiveness < bestResist)
                {
                    bestResist = typeEffectiveness;
                    bestMonId = i;
                }
            }
        }

        // Ok, we know the mon has the right typing but does it have at least one super effective move?
        if (bestMonId != PARTY_SIZE)
        {
            for (i = 0; i < MAX_MON_MOVES; i++)
            {
                u32 move = GetMonData(&party[bestMonId], MON_DATA_MOVE1 + i);
                if (move != MOVE_NONE && AI_GetMoveEffectiveness(move, battler, opposingBattler) >= UQ_4_12(2.0))
                    break;
            }

            if (i != MAX_MON_MOVES)
                return bestMonId; // Has both the typing and at least one super effective move.

            bits |= (1u << bestMonId); // Sorry buddy, we want something better.
        }
        else
        {
            bits = 0x3F; // No viable mon to switch.
        }
    }

    return PARTY_SIZE;
}

static u32 GetBestMonDmg(struct Pokemon *party, int firstId, int lastId, u8 invalidMons, u32 battler, u32 opposingBattler)
{
    int i, j;
    int dmg, bestDmg = 0;
    int bestMonId = PARTY_SIZE;
    u32 rollType = GetDmgRollType(battler);

    u32 aiMove;

    // If we couldn't find the best mon in terms of typing, find the one that deals most damage.
    for (i = firstId; i < lastId; i++)
    {
        if ((1 << (i)) & invalidMons)
            continue;
        InitializeSwitchinCandidate(&party[i]);
        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            aiMove = AI_DATA->switchinCandidate.battleMon.moves[j];
            if (aiMove != MOVE_NONE && !IsBattleMoveStatus(aiMove))
            {
                aiMove = GetMonData(&party[i], MON_DATA_MOVE1 + j);
                dmg = AI_CalcPartyMonDamage(aiMove, battler, opposingBattler, AI_DATA->switchinCandidate.battleMon, TRUE, rollType);
                if (bestDmg < dmg)
                {
                    bestDmg = dmg;
                    bestMonId = i;
                }
            }
        }
    }

    return bestMonId;
}

bool32 IsMonGrounded(u16 heldItemEffect, u32 ability, u8 type1, u8 type2)
{
    // List that makes mon not grounded
    if (type1 == TYPE_FLYING || type2 == TYPE_FLYING || ability == ABILITY_LEVITATE
         || (heldItemEffect == HOLD_EFFECT_AIR_BALLOON && !(ability == ABILITY_KLUTZ || (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM))))
    {
        // List that overrides being off the ground
        if ((heldItemEffect == HOLD_EFFECT_IRON_BALL && !(ability == ABILITY_KLUTZ || (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM))) || (gFieldStatuses & STATUS_FIELD_GRAVITY) || (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM))
            return TRUE;
        else
            return FALSE;
    }
    else
        return TRUE;
}

// Gets hazard damage
static u32 GetSwitchinHazardsDamage(u32 battler, struct BattlePokemon *battleMon)
{
    u8 defType1 = battleMon->types[0], defType2 = battleMon->types[1], tSpikesLayers;
    u16 heldItemEffect = ItemId_GetHoldEffect(battleMon->item);
    u32 maxHP = battleMon->maxHP, ability = battleMon->ability, status = battleMon->status1;
    u32 spikesDamage = 0, tSpikesDamage = 0, hazardDamage = 0;
    u32 hazardFlags = gSideStatuses[GetBattlerSide(battler)] & (SIDE_STATUS_SPIKES | SIDE_STATUS_STEALTH_ROCK | SIDE_STATUS_STICKY_WEB | SIDE_STATUS_TOXIC_SPIKES | SIDE_STATUS_SAFEGUARD);

    // Check ways mon might avoid all hazards
    if (ability != ABILITY_MAGIC_GUARD || (heldItemEffect == HOLD_EFFECT_HEAVY_DUTY_BOOTS &&
        !((gFieldStatuses & STATUS_FIELD_MAGIC_ROOM) || ability == ABILITY_KLUTZ)))
    {
        // Stealth Rock
        if ((hazardFlags & SIDE_STATUS_STEALTH_ROCK) && heldItemEffect != HOLD_EFFECT_HEAVY_DUTY_BOOTS)
            hazardDamage += GetStealthHazardDamageByTypesAndHP(TYPE_SIDE_HAZARD_POINTED_STONES, defType1, defType2, battleMon->maxHP);
        // G-Max Steelsurge
        if ((hazardFlags & SIDE_STATUS_STEELSURGE) && heldItemEffect != HOLD_EFFECT_HEAVY_DUTY_BOOTS)
            hazardDamage += GetStealthHazardDamageByTypesAndHP(TYPE_SIDE_HAZARD_SHARP_STEEL, defType1, defType2, battleMon->maxHP);
        // Spikes
        if ((hazardFlags & SIDE_STATUS_SPIKES) && IsMonGrounded(heldItemEffect, ability, defType1, defType2))
        {
            spikesDamage = maxHP / ((5 - gSideTimers[GetBattlerSide(battler)].spikesAmount) * 2);
            if (spikesDamage == 0)
                spikesDamage = 1;
            hazardDamage += spikesDamage;
        }

        if ((hazardFlags & SIDE_STATUS_TOXIC_SPIKES) && (defType1 != TYPE_POISON && defType2 != TYPE_POISON
            && defType1 != TYPE_STEEL && defType2 != TYPE_STEEL
            && ability != ABILITY_IMMUNITY && ability != ABILITY_POISON_HEAL && ability != ABILITY_COMATOSE
            && status == 0
            && !(hazardFlags & SIDE_STATUS_SAFEGUARD)
            && !IsAbilityOnSide(battler, ABILITY_PASTEL_VEIL)
            && !IsBattlerTerrainAffected(battler, STATUS_FIELD_MISTY_TERRAIN)
            && !IsAbilityStatusProtected(battler, ability)
            && heldItemEffect != HOLD_EFFECT_CURE_PSN && heldItemEffect != HOLD_EFFECT_CURE_STATUS
            && IsMonGrounded(heldItemEffect, ability, defType1, defType2)))
        {
            tSpikesLayers = gSideTimers[GetBattlerSide(battler)].toxicSpikesAmount;
            if (tSpikesLayers == 1)
            {
                tSpikesDamage = maxHP / 8;
                if (tSpikesDamage == 0)
                    tSpikesDamage = 1;
            }
            else if (tSpikesLayers >= 2)
            {
                tSpikesDamage = maxHP / 16;
                if (tSpikesDamage == 0)
                    tSpikesDamage = 1;
            }
            hazardDamage += tSpikesDamage;
        }
    }
    return hazardDamage;
}

// Gets damage / healing from weather
static s32 GetSwitchinWeatherImpact(void)
{
    s32 weatherImpact = 0, maxHP = AI_DATA->switchinCandidate.battleMon.maxHP, ability = AI_DATA->switchinCandidate.battleMon.ability;
    u32 holdEffect = ItemId_GetHoldEffect(AI_DATA->switchinCandidate.battleMon.item);

    if (HasWeatherEffect())
    {
        // Damage
        if (holdEffect != HOLD_EFFECT_SAFETY_GOGGLES && ability != ABILITY_MAGIC_GUARD && ability != ABILITY_OVERCOAT)
        {
            if ((gBattleWeather & B_WEATHER_HAIL)
             && (AI_DATA->switchinCandidate.battleMon.types[0] != TYPE_ICE || AI_DATA->switchinCandidate.battleMon.types[1] != TYPE_ICE)
             && ability != ABILITY_SNOW_CLOAK && ability != ABILITY_ICE_BODY)
            {
                weatherImpact = maxHP / 16;
                if (weatherImpact == 0)
                    weatherImpact = 1;
            }
            else if ((gBattleWeather & B_WEATHER_SANDSTORM)
                && (AI_DATA->switchinCandidate.battleMon.types[0] != TYPE_GROUND && AI_DATA->switchinCandidate.battleMon.types[1] != TYPE_GROUND
                && AI_DATA->switchinCandidate.battleMon.types[0] != TYPE_ROCK && AI_DATA->switchinCandidate.battleMon.types[1] != TYPE_ROCK
                && AI_DATA->switchinCandidate.battleMon.types[0] != TYPE_STEEL && AI_DATA->switchinCandidate.battleMon.types[1] != TYPE_STEEL
                && ability != ABILITY_SAND_VEIL && ability != ABILITY_SAND_RUSH && ability != ABILITY_SAND_FORCE))
            {
                weatherImpact = maxHP / 16;
                if (weatherImpact == 0)
                    weatherImpact = 1;
            }
        }
        if ((gBattleWeather & B_WEATHER_SUN) && holdEffect != HOLD_EFFECT_UTILITY_UMBRELLA
         && (ability == ABILITY_SOLAR_POWER || ability == ABILITY_DRY_SKIN))
        {
            weatherImpact = maxHP / 8;
            if (weatherImpact == 0)
                weatherImpact = 1;
        }

        // Healing
        if (gBattleWeather & B_WEATHER_RAIN && holdEffect != HOLD_EFFECT_UTILITY_UMBRELLA)
        {
            if (ability == ABILITY_DRY_SKIN)
            {
                weatherImpact = -(maxHP / 8);
                if (weatherImpact == 0)
                    weatherImpact = -1;
            }
            else if (ability == ABILITY_RAIN_DISH)
            {
                weatherImpact = -(maxHP / 16);
                if (weatherImpact == 0)
                    weatherImpact = -1;
            }
        }
        if (((gBattleWeather & B_WEATHER_HAIL) || (gBattleWeather & B_WEATHER_SNOW)) && ability == ABILITY_ICE_BODY)
        {
            weatherImpact = -(maxHP / 16);
            if (weatherImpact == 0)
                weatherImpact = -1;
        }
    }
    return weatherImpact;
}

// Gets one turn of recurring healing
static u32 GetSwitchinRecurringHealing(void)
{
    u32 recurringHealing = 0, maxHP = AI_DATA->switchinCandidate.battleMon.maxHP, ability = AI_DATA->switchinCandidate.battleMon.ability;
    u32 holdEffect = ItemId_GetHoldEffect(AI_DATA->switchinCandidate.battleMon.item);

    // Items
    if (ability != ABILITY_KLUTZ)
    {
        if (holdEffect == HOLD_EFFECT_BLACK_SLUDGE && (AI_DATA->switchinCandidate.battleMon.types[0] == TYPE_POISON || AI_DATA->switchinCandidate.battleMon.types[1] == TYPE_POISON))
        {
            recurringHealing = maxHP / 16;
            if (recurringHealing == 0)
                recurringHealing = 1;
        }
        else if (holdEffect == HOLD_EFFECT_LEFTOVERS)
        {
            recurringHealing = maxHP / 16;
            if (recurringHealing == 0)
                recurringHealing = 1;
        }
    } // Intentionally omitting Shell Bell for its inconsistency

    // Abilities
    if (ability == ABILITY_POISON_HEAL && (AI_DATA->switchinCandidate.battleMon.status1 & STATUS1_POISON))
    {
        u32 healing = maxHP / 8;
        if (healing == 0)
            healing = 1;
        recurringHealing += healing;
    }
    return recurringHealing;
}

// Gets one turn of recurring damage
static u32 GetSwitchinRecurringDamage(void)
{
    u32 passiveDamage = 0, maxHP = AI_DATA->switchinCandidate.battleMon.maxHP, ability = AI_DATA->switchinCandidate.battleMon.ability;
    u32 holdEffect = ItemId_GetHoldEffect(AI_DATA->switchinCandidate.battleMon.item);

    // Items
    if (ability != ABILITY_MAGIC_GUARD && ability != ABILITY_KLUTZ)
    {
        if (holdEffect == HOLD_EFFECT_BLACK_SLUDGE && AI_DATA->switchinCandidate.battleMon.types[0] != TYPE_POISON && AI_DATA->switchinCandidate.battleMon.types[1] != TYPE_POISON)
        {
            passiveDamage = maxHP / 8;
            if (passiveDamage == 0)
                passiveDamage = 1;
        }
        else if (holdEffect == HOLD_EFFECT_LIFE_ORB && ability != ABILITY_SHEER_FORCE)
        {
            passiveDamage = maxHP / 10;
            if (passiveDamage == 0)
                passiveDamage = 1;
        }
        else if (holdEffect == HOLD_EFFECT_STICKY_BARB)
        {
            passiveDamage = maxHP / 6;
            if(passiveDamage == 0)
                passiveDamage = 1;
        }
    }
    return passiveDamage;
}

// Gets one turn of status damage
static u32 GetSwitchinStatusDamage(u32 battler)
{
    u8 defType1 = AI_DATA->switchinCandidate.battleMon.types[0], defType2 = AI_DATA->switchinCandidate.battleMon.types[1];
    u8 tSpikesLayers = gSideTimers[GetBattlerSide(battler)].toxicSpikesAmount;
    u16 heldItemEffect = ItemId_GetHoldEffect(AI_DATA->switchinCandidate.battleMon.item);
    u32 status = AI_DATA->switchinCandidate.battleMon.status1, ability = AI_DATA->switchinCandidate.battleMon.ability, maxHP = AI_DATA->switchinCandidate.battleMon.maxHP;
    u32 statusDamage = 0;

    // Status condition damage
    if ((status != 0) && AI_DATA->switchinCandidate.battleMon.ability != ABILITY_MAGIC_GUARD)
    {
        if (status & STATUS1_BURN)
        {
            if (B_BURN_DAMAGE >= GEN_7)
                statusDamage = maxHP / 16;
            else
                statusDamage = maxHP / 8;
            if(ability == ABILITY_HEATPROOF)
                statusDamage = statusDamage / 2;
            if (statusDamage == 0)
                statusDamage = 1;
        }
        else if (status & STATUS1_FROSTBITE)
        {
            if (B_BURN_DAMAGE >= GEN_7)
                statusDamage = maxHP / 16;
            else
                statusDamage = maxHP / 8;
            if (statusDamage == 0)
                statusDamage = 1;
        }
        else if ((status & STATUS1_POISON) && ability != ABILITY_POISON_HEAL)
        {
            statusDamage = maxHP / 8;
            if (statusDamage == 0)
                statusDamage = 1;
        }
        else if ((status & STATUS1_TOXIC_POISON) && ability != ABILITY_POISON_HEAL)
        {
            if ((status & STATUS1_TOXIC_COUNTER) != STATUS1_TOXIC_TURN(15)) // not 16 turns
                AI_DATA->switchinCandidate.battleMon.status1 += STATUS1_TOXIC_TURN(1);
            statusDamage = maxHP / 16;
            if (statusDamage == 0)
                statusDamage = 1;
            statusDamage *= AI_DATA->switchinCandidate.battleMon.status1 & STATUS1_TOXIC_COUNTER >> 8;
        }
    }

    // Apply hypothetical poisoning from Toxic Spikes, which means the first turn of damage already added in GetSwitchinHazardsDamage
    // Do this last to skip one iteration of Poison / Toxic damage, and start counting Toxic damage one turn later.
    if (tSpikesLayers != 0 && (defType1 != TYPE_POISON && defType2 != TYPE_POISON
        && ability != ABILITY_IMMUNITY && ability != ABILITY_POISON_HEAL
        && status == 0
        && !(heldItemEffect == HOLD_EFFECT_HEAVY_DUTY_BOOTS
            && (((gFieldStatuses & STATUS_FIELD_MAGIC_ROOM) || ability == ABILITY_KLUTZ)))
        && heldItemEffect != HOLD_EFFECT_CURE_PSN && heldItemEffect != HOLD_EFFECT_CURE_STATUS
        && IsMonGrounded(heldItemEffect, ability, defType1, defType2)))
    {
        if (tSpikesLayers == 1)
        {
            AI_DATA->switchinCandidate.battleMon.status1 = STATUS1_POISON; // Assign "hypothetical" status to the switchin candidate so we can get the damage it would take from TSpikes
            AI_DATA->switchinCandidate.hypotheticalStatus = TRUE;
        }
        if (tSpikesLayers == 2)
        {
            AI_DATA->switchinCandidate.battleMon.status1 = STATUS1_TOXIC_POISON; // Assign "hypothetical" status to the switchin candidate so we can get the damage it would take from TSpikes
            AI_DATA->switchinCandidate.battleMon.status1 += STATUS1_TOXIC_TURN(1);
            AI_DATA->switchinCandidate.hypotheticalStatus = TRUE;
        }
    }
    return statusDamage;
}

// Gets number of hits to KO factoring in hazards, healing held items, status, and weather
static u32 GetSwitchinHitsToKO(s32 damageTaken, u32 battler)
{
    u32 startingHP = AI_DATA->switchinCandidate.battleMon.hp - GetSwitchinHazardsDamage(battler, &AI_DATA->switchinCandidate.battleMon);
    s32 weatherImpact = GetSwitchinWeatherImpact(); // Signed to handle both damage and healing in the same value
    u32 recurringDamage = GetSwitchinRecurringDamage();
    u32 recurringHealing = GetSwitchinRecurringHealing();
    u32 statusDamage = GetSwitchinStatusDamage(battler);
    u32 hitsToKO = 0, singleUseItemHeal = 0;
    u16 maxHP = AI_DATA->switchinCandidate.battleMon.maxHP, item = AI_DATA->switchinCandidate.battleMon.item, heldItemEffect = ItemId_GetHoldEffect(item);
    u8 weatherDuration = gWishFutureKnock.weatherDuration, holdEffectParam = ItemId_GetHoldEffectParam(item);
    u32 opposingBattler = GetOppositeBattler(battler);
    u32 opposingAbility = gBattleMons[opposingBattler].ability, ability = AI_DATA->switchinCandidate.battleMon.ability;
    bool32 usedSingleUseHealingItem = FALSE, opponentCanBreakMold = IsMoldBreakerTypeAbility(opposingBattler, opposingAbility);
    s32 currentHP = startingHP;

    // No damage being dealt
    if ((damageTaken + statusDamage + recurringDamage <= recurringHealing) || damageTaken + statusDamage + recurringDamage == 0)
        return startingHP;

    // Mon fainted to hazards
    if (startingHP == 0)
        return 1;

    // Find hits to KO
    while (currentHP > 0)
    {
        // Remove weather damage when it would run out
        if (weatherImpact != 0 && weatherDuration == 0)
            weatherImpact = 0;

        // Take attack damage for the turn
        currentHP = currentHP - damageTaken;

        // One shot prevention effects
        if (damageTaken >= maxHP && startingHP == maxHP && (heldItemEffect == HOLD_EFFECT_FOCUS_SASH || (!opponentCanBreakMold && B_STURDY >= GEN_5 && ability == ABILITY_STURDY)) && hitsToKO < 1)
            currentHP = 1;

        // If mon is still alive, apply weather impact first, as it might KO the mon before it can heal with its item (order is weather -> item -> status)
        if (currentHP != 0)
            currentHP = currentHP - weatherImpact;

        // Check if we're at a single use healing item threshold
        if (AI_DATA->switchinCandidate.battleMon.ability != ABILITY_KLUTZ && usedSingleUseHealingItem == FALSE
         && !(opposingAbility == ABILITY_UNNERVE && GetPocketByItemId(item) == POCKET_BERRIES))
        {
            switch (heldItemEffect)
            {
            case HOLD_EFFECT_RESTORE_HP:
                if (currentHP < maxHP / 2)
                    singleUseItemHeal = holdEffectParam;
                break;
            case HOLD_EFFECT_RESTORE_PCT_HP:
                if (currentHP < maxHP / 2)
                {
                    singleUseItemHeal = maxHP / holdEffectParam;
                    if (singleUseItemHeal == 0)
                        singleUseItemHeal = 1;
                }
                break;
            case HOLD_EFFECT_CONFUSE_SPICY:
            case HOLD_EFFECT_CONFUSE_DRY:
            case HOLD_EFFECT_CONFUSE_SWEET:
            case HOLD_EFFECT_CONFUSE_BITTER:
            case HOLD_EFFECT_CONFUSE_SOUR:
                if (currentHP < maxHP / CONFUSE_BERRY_HP_FRACTION)
                {
                    singleUseItemHeal = maxHP / holdEffectParam;
                    if (singleUseItemHeal == 0)
                        singleUseItemHeal = 1;
                }
                break;
            }

            // If we used one, apply it without overcapping our maxHP
            if (singleUseItemHeal > 0)
            {
                if ((currentHP + singleUseItemHeal) > maxHP)
                    currentHP = maxHP;
                else
                    currentHP = currentHP + singleUseItemHeal;
                usedSingleUseHealingItem = TRUE;
            }
        }

        // Healing from items occurs before status so we can do the rest in one line
        if (currentHP >= 0)
            currentHP = currentHP + recurringHealing - recurringDamage - statusDamage;

        // Recalculate toxic damage if needed
        if (AI_DATA->switchinCandidate.battleMon.status1 & STATUS1_TOXIC_POISON)
            statusDamage = GetSwitchinStatusDamage(battler);

        // Reduce weather duration
        if (weatherDuration != 0)
            weatherDuration--;

        hitsToKO++;
    }

    // Disguise will always add an extra hit to KO
    if (opponentCanBreakMold && AI_DATA->switchinCandidate.battleMon.species == SPECIES_MIMIKYU_DISGUISED)
        hitsToKO++;

    // If mon had a hypothetical status from TSpikes, clear it
    if (AI_DATA->switchinCandidate.hypotheticalStatus == TRUE)
    {
        AI_DATA->switchinCandidate.battleMon.status1 = 0;
        AI_DATA->switchinCandidate.hypotheticalStatus = FALSE;
    }
    return hitsToKO;
}

static u16 GetSwitchinTypeMatchup(u32 opposingBattler, struct BattlePokemon battleMon)
{

    // Check type matchup
    u16 typeEffectiveness = UQ_4_12(1.0);
    u8 atkType1 = gSpeciesInfo[gBattleMons[opposingBattler].species].types[0], atkType2 = gSpeciesInfo[gBattleMons[opposingBattler].species].types[1],
    defType1 = battleMon.types[0], defType2 = battleMon.types[1];

    // Multiply type effectiveness by a factor depending on type matchup
    typeEffectiveness = uq4_12_multiply(typeEffectiveness, (GetTypeModifier(atkType1, defType1)));
    if (atkType2 != atkType1)
        typeEffectiveness = uq4_12_multiply(typeEffectiveness, (GetTypeModifier(atkType2, defType1)));
    if (defType2 != defType1)
    {
        typeEffectiveness = uq4_12_multiply(typeEffectiveness, (GetTypeModifier(atkType1, defType2)));
        if (atkType2 != atkType1)
            typeEffectiveness = uq4_12_multiply(typeEffectiveness, (GetTypeModifier(atkType2, defType2)));
    }
    return typeEffectiveness;
}

static int GetRandomSwitchinWithBatonPass(int aliveCount, int bits, int firstId, int lastId, int currentMonId)
{
    // Breakout early if there aren't any Baton Pass mons to save computation time
    if (bits == 0)
        return PARTY_SIZE;

    // GetBestMonBatonPass randomly chooses between all mons that met Baton Pass check
    if ((aliveCount == 2 || (aliveCount > 2 && Random() % 3 == 0)) && bits)
    {
        do
        {
            return (Random() % (lastId - firstId)) + firstId;
        } while (!(bits & (1 << (currentMonId))));
    }

    // Catch any other cases (such as only one mon alive and it has Baton Pass)
    else
        return PARTY_SIZE;
}

static s32 GetMaxDamagePlayerCouldDealToSwitchin(u32 battler, u32 opposingBattler, struct BattlePokemon battleMon)
{
    int i = 0;
    u32 playerMove;
    s32 damageTaken = 0, maxDamageTaken = 0;
    u16 playerMoves[MAX_MON_MOVES];

    // Use GetMovesArrayWithHiddenSTAB to only consider revealed moves + STAB moves
    GetMovesArrayWithHiddenSTAB(opposingBattler, playerMoves);

    DEBUG_DAMAGE("Analyzing player moves for switch-in damage (revealed + STAB only):");

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        playerMove = playerMoves[i];
        if (playerMove != MOVE_NONE && playerMove != MOVE_UNAVAILABLE && !IsBattleMoveStatus(playerMove) && GetMoveEffect(playerMove) != EFFECT_FOCUS_PUNCH)
        {
            damageTaken = AI_CalcPartyMonDamage(playerMove, opposingBattler, battler, battleMon, FALSE, DMG_ROLL_HIGHEST);
            DEBUG_DAMAGE("Player move %d: %d damage to switch-in", playerMove, damageTaken);
            if (damageTaken > maxDamageTaken)
            {
                maxDamageTaken = damageTaken;
                DEBUG_DAMAGE("New max damage to switch-in: %d", maxDamageTaken);
            }
        }
        else if (playerMove != MOVE_NONE && playerMove != MOVE_UNAVAILABLE)
        {
            DEBUG_DAMAGE("Skipping player move %d (status/Focus Punch)", playerMove);
        }
    }

    if (GetBattlerSide(battler) == B_SIDE_OPPONENT){
        DEBUG_DAMAGE("The max damage that switched in mon %d takes is %d (using revealed+STAB moves only)", battleMon.species, maxDamageTaken);
    }

    return maxDamageTaken;
}

static bool32 CanAbilityTrapOpponent(u16 ability, u32 opponent)
{
    if ((B_GHOSTS_ESCAPE >= GEN_6 && IS_BATTLER_OF_TYPE(opponent, TYPE_GHOST)))
        return FALSE;
    else if (ability == ABILITY_SHADOW_TAG)
    {
        if (B_SHADOW_TAG_ESCAPE >= GEN_4 && AI_DATA->abilities[opponent] == ABILITY_SHADOW_TAG) // Check if ability exists in species
            return FALSE;
        else
            return TRUE;
    }
    else if (ability == ABILITY_ARENA_TRAP && IsBattlerGrounded(opponent))
        return TRUE;
    else if (ability == ABILITY_MAGNET_PULL && IS_BATTLER_OF_TYPE(opponent, TYPE_STEEL))
        return TRUE;
    else
        return FALSE;
}

static inline bool32 IsFreeSwitch(enum SwitchType switchType, u32 battlerSwitchingOut, u32 opposingBattler)
{
    bool32 movedSecond = GetBattlerTurnOrderNum(battlerSwitchingOut) > GetBattlerTurnOrderNum(opposingBattler) ? TRUE : FALSE;

    // Switch out effects
    if (!IsDoubleBattle()) // Not handling doubles' additional complexity
    {
        if (IsSwitchOutEffect(GetMoveEffect(gCurrentMove)) && movedSecond)
            return TRUE;
        if (AI_DATA->ejectButtonSwitch)
            return TRUE;
        if (AI_DATA->ejectPackSwitch)
        {
            u32 opposingAbility = AI_GetBattlerAbility(opposingBattler);
            // If faster, not a free switch; likely lowered own stats
            if (!movedSecond && opposingAbility != ABILITY_INTIMIDATE && opposingAbility != ABILITY_SUPERSWEET_SYRUP) // Intimidate triggers switches before turn starts
                return FALSE;
            // Otherwise, free switch
            return TRUE;
        }
    }

    // Post KO check has to be last because the GetMostSuitableMonToSwitchInto call in OpponentHandleChoosePokemon assumes a KO rather than a forced switch choice
    if (switchType == SWITCH_AFTER_KO)
        return TRUE;
    else
        return FALSE;
}

static inline bool32 CanSwitchinWin1v1(u32 hitsToKOAI, u32 hitsToKOPlayer, bool32 isSwitchinFirst, bool32 isFreeSwitch)
{
    // Free switch, need to outspeed or take 1 extra hit
    if (isFreeSwitch)
    {
        if (hitsToKOAI > hitsToKOPlayer || (hitsToKOAI == hitsToKOPlayer && isSwitchinFirst))
            return TRUE;
    }
    // Mid battle switch, need to take 1 or 2 extra hits depending on speed
    if (hitsToKOAI > hitsToKOPlayer + 1 || (hitsToKOAI == hitsToKOPlayer + 1 && isSwitchinFirst))
        return TRUE;
    return FALSE;
}

// This function splits switching behaviour depending on whether the switch is free.
// Everything runs in the same loop to minimize computation time. This makes it harder to read, but hopefully the comments can guide you!
static u32 GetBestMonIntegrated(struct Pokemon *party, int firstId, int lastId, u32 battler, u32 opposingBattler, u32 battlerIn1, u32 battlerIn2, enum SwitchType switchType)
{
    int revengeKillerId = PARTY_SIZE, slowRevengeKillerId = PARTY_SIZE, fastThreatenId = PARTY_SIZE, slowThreatenId = PARTY_SIZE, damageMonId = PARTY_SIZE;
    int batonPassId = PARTY_SIZE, typeMatchupId = PARTY_SIZE, typeMatchupEffectiveId = PARTY_SIZE, defensiveMonId = PARTY_SIZE, aceMonId = PARTY_SIZE, trapperId = PARTY_SIZE;
    int i, j, aliveCount = 0, bits = 0, aceMonCount = 0;
    s32 defensiveMonHitKOThreshold = 3; // 3HKO threshold that candidate defensive mons must exceed
    s32 playerMonHP = gBattleMons[opposingBattler].hp, maxDamageDealt = 0, damageDealt = 0;
    u32 aiMove, hitsToKOAI, maxHitsToKO = 0;
    u16 bestResist = UQ_4_12(1.0), bestResistEffective = UQ_4_12(1.0), typeMatchup;
    bool32 isFreeSwitch = IsFreeSwitch(switchType, battlerIn1, opposingBattler), isSwitchinFirst, canSwitchinWin1v1;

    // Iterate through mons
    for (i = firstId; i < lastId; i++)
    {
        // Check mon validity
        if (!IsValidForBattle(&party[i])
            || gBattlerPartyIndexes[battlerIn1] == i
            || gBattlerPartyIndexes[battlerIn2] == i
            || i == gBattleStruct->monToSwitchIntoId[battlerIn1]
            || i == gBattleStruct->monToSwitchIntoId[battlerIn2])
        {
            continue;
        }
        // Save Ace Pokemon for last
        else if (IsAceMon(battler, i))
        {
            aceMonId = i;
            aceMonCount++;
            continue;
        }
        else
            aliveCount++;

        InitializeSwitchinCandidate(&party[i]);

        // While not really invalid per se, not really wise to switch into this mon
        if (AI_DATA->switchinCandidate.battleMon.ability == ABILITY_TRUANT && IsTruantMonVulnerable(battler, opposingBattler))
            continue;

        // Get max number of hits for player to KO AI mon and type matchup for defensive switching
        hitsToKOAI = GetSwitchinHitsToKO(GetMaxDamagePlayerCouldDealToSwitchin(battler, opposingBattler, AI_DATA->switchinCandidate.battleMon), battler);
        typeMatchup = GetSwitchinTypeMatchup(opposingBattler, AI_DATA->switchinCandidate.battleMon);

        // Track max hits to KO and set defensive mon
        if(hitsToKOAI > maxHitsToKO)
        {
            maxHitsToKO = hitsToKOAI;
            if(maxHitsToKO > defensiveMonHitKOThreshold)
                defensiveMonId = i;
        }

        // Check through current mon's moves
        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            aiMove = AI_DATA->switchinCandidate.battleMon.moves[j];

            if (aiMove != MOVE_NONE && !IsBattleMoveStatus(aiMove))
            {
                if (AI_THINKING_STRUCT->aiFlags[GetThinkingBattler(battler)] & AI_FLAG_CONSERVATIVE)
                    damageDealt = AI_CalcPartyMonDamage(aiMove, battler, opposingBattler, AI_DATA->switchinCandidate.battleMon, TRUE, DMG_ROLL_LOWEST);
                else
                    damageDealt = AI_CalcPartyMonDamage(aiMove, battler, opposingBattler, AI_DATA->switchinCandidate.battleMon, TRUE, DMG_ROLL_DEFAULT);
            }

            // Offensive switchin decisions are based on which whether switchin moves first and whether it can win a 1v1
            isSwitchinFirst = AI_WhoStrikesFirstPartyMon(battler, opposingBattler, AI_DATA->switchinCandidate.battleMon, aiMove);
            canSwitchinWin1v1 = CanSwitchinWin1v1(hitsToKOAI, GetNoOfHitsToKOBattlerDmg(damageDealt, opposingBattler), isSwitchinFirst, isFreeSwitch);

            // Check for Baton Pass; hitsToKO requirements mean mon can boost and BP without dying whether it's slower or not
            if (aiMove == MOVE_BATON_PASS)
            {
                if ((isSwitchinFirst && hitsToKOAI > 1) || hitsToKOAI > 2) // Need to take an extra hit if slower
                    bits |= 1u << i;
            }

            // Check that good type matchups get at least two turns and set best type matchup mon
            if (typeMatchup < bestResist)
            {
                if (canSwitchinWin1v1)
                {
                    bestResist = typeMatchup;
                    typeMatchupId = i;
                }
            }

            // Check for mon with resistance and super effective move for best type matchup mon with effective move
            if (aiMove != MOVE_NONE && !IsBattleMoveStatus(aiMove))
            {
                if (typeMatchup < bestResistEffective)
                {
                    if (AI_GetMoveEffectiveness(aiMove, battler, opposingBattler) >= UQ_4_12(2.0))
                    {
                        if (canSwitchinWin1v1)
                        {
                            bestResistEffective = typeMatchup;
                            typeMatchupEffectiveId = i;
                        }
                    }
                }

                // If a self destruction move doesn't OHKO, don't factor it into revenge killing
                if (GetMoveEffect(aiMove) == EFFECT_EXPLOSION && damageDealt < playerMonHP)
                    continue;

                // Check that mon isn't one shot and set best damage mon
                if (damageDealt > maxDamageDealt)
                {
                    if((isFreeSwitch && hitsToKOAI > 1) || hitsToKOAI > 2) // This is a "default", we have uniquely low standards
                    {
                        maxDamageDealt = damageDealt;
                        damageMonId = i;
                    }
                }

                // Check if current mon can revenge kill in some capacity
                // If AI mon can one shot
                if (damageDealt > playerMonHP)
                {
                    if (canSwitchinWin1v1)
                    {
                        if (isSwitchinFirst)
                            revengeKillerId = i;
                        else
                            slowRevengeKillerId = i;
                    }
                }

                // If AI mon can two shot
                if (damageDealt > playerMonHP / 2)
                {
                    if (canSwitchinWin1v1)
                    {
                        if (isSwitchinFirst)
                            fastThreatenId = i;
                        else
                            slowThreatenId = i;
                    }
                }

                // If mon can trap
                if ((CanAbilityTrapOpponent(AI_DATA->switchinCandidate.battleMon.ability, opposingBattler)
                    || (CanAbilityTrapOpponent(AI_GetBattlerAbility(opposingBattler), opposingBattler) && AI_DATA->switchinCandidate.battleMon.ability == ABILITY_TRACE))
                    && CountUsablePartyMons(opposingBattler) > 0
                    && canSwitchinWin1v1)
                    trapperId = i;
            }
        }
    }

    batonPassId = GetRandomSwitchinWithBatonPass(aliveCount, bits, firstId, lastId, i);

    // Different switching priorities depending on switching mid battle vs switching after a KO or slow switch
    if (isFreeSwitch)
    {
        // Return Trapper > Revenge Killer > Type Matchup > Baton Pass > Best Damage
        if (trapperId != PARTY_SIZE)                    return trapperId;
        else if (revengeKillerId != PARTY_SIZE)         return revengeKillerId;
        else if (slowRevengeKillerId != PARTY_SIZE)     return slowRevengeKillerId;
        else if (fastThreatenId != PARTY_SIZE)          return fastThreatenId;
        else if (slowThreatenId != PARTY_SIZE)          return slowThreatenId;
        else if (typeMatchupEffectiveId != PARTY_SIZE)  return typeMatchupEffectiveId;
        else if (typeMatchupId != PARTY_SIZE)           return typeMatchupId;
        else if (batonPassId != PARTY_SIZE)             return batonPassId;
        else if (damageMonId != PARTY_SIZE)             return damageMonId;
    }
    else
    {
        // Return Trapper > Type Matchup > Best Defensive > Baton Pass
        if (trapperId != PARTY_SIZE)                    return trapperId;
        else if (typeMatchupEffectiveId != PARTY_SIZE)  return typeMatchupEffectiveId;
        else if (typeMatchupId != PARTY_SIZE)           return typeMatchupId;
        else if (defensiveMonId != PARTY_SIZE)          return defensiveMonId;
        else if (batonPassId != PARTY_SIZE)             return batonPassId;
    }
    // If ace mon is the last available Pokemon and U-Turn/Volt Switch or Eject Pack/Button was used - switch to the mon.
    if (aceMonId != PARTY_SIZE && CountUsablePartyMons(battler) <= aceMonCount
     && (IsSwitchOutEffect(GetMoveEffect(gCurrentMove)) || AI_DATA->ejectButtonSwitch || AI_DATA->ejectPackSwitch))
        return aceMonId;

    return PARTY_SIZE;
}

static u32 GetNextMonInParty(struct Pokemon *party, int firstId, int lastId, u32 battlerIn1, u32 battlerIn2)
{
    u32 i;
    // Iterate through mons
    for (i = firstId; i < lastId; i++)
    {
        // Check mon validity
        if (!IsValidForBattle(&party[i])
            || gBattlerPartyIndexes[battlerIn1] == i
            || gBattlerPartyIndexes[battlerIn2] == i
            || i == gBattleStruct->monToSwitchIntoId[battlerIn1]
            || i == gBattleStruct->monToSwitchIntoId[battlerIn2])
        {
            continue;
        }
        return i;
    }
    return PARTY_SIZE;
}

u32 GetMostSuitableMonToSwitchInto(u32 battler, enum SwitchType switchType)
{
    u32 opposingBattler = 0;
    u32 bestMonId = PARTY_SIZE;
    u32 battlerIn1 = 0, battlerIn2 = 0;
    s32 firstId = 0;
    s32 lastId = 0; // + 1
    struct Pokemon *party;

    if (gBattleStruct->monToSwitchIntoId[battler] != PARTY_SIZE)
        return gBattleStruct->monToSwitchIntoId[battler];
    if (gBattleTypeFlags & BATTLE_TYPE_ARENA)
        return gBattlerPartyIndexes[battler] + 1;

    if (IsDoubleBattle())
    {
        battlerIn1 = battler;
        if (gAbsentBattlerFlags & (1u << GetPartnerBattler(battler)))
            battlerIn2 = battler;
        else
            battlerIn2 = GetPartnerBattler(battler);

        opposingBattler = BATTLE_OPPOSITE(battlerIn1);
        if (gAbsentBattlerFlags & (1u << opposingBattler))
            opposingBattler ^= BIT_FLANK;
    }
    else
    {
        opposingBattler = GetOppositeBattler(battler);
        battlerIn1 = battler;
        battlerIn2 = battler;
    }

    GetAIPartyIndexes(battler, &firstId, &lastId);
    party = GetBattlerParty(battler);

    if (AI_THINKING_STRUCT->aiFlags[GetThinkingBattler(battler)] & AI_FLAG_SEQUENCE_SWITCHING)
    {
        bestMonId = GetNextMonInParty(party, firstId, lastId, battlerIn1, battlerIn2);
        return bestMonId;
    }

    // Only use better mon selection if AI_FLAG_SMART_MON_CHOICES is set for the trainer.
    if (AI_THINKING_STRUCT->aiFlags[GetThinkingBattler(battler)] & AI_FLAG_SMART_MON_CHOICES && !IsDoubleBattle()) // Double Battles aren't included in AI_FLAG_SMART_MON_CHOICE. Defaults to regular switch in logic
    {
        bestMonId = GetBestMonIntegrated(party, firstId, lastId, battler, opposingBattler, battlerIn1, battlerIn2, switchType);
        return bestMonId;
    }

    // This all handled by the GetBestMonIntegrated function if the AI_FLAG_SMART_MON_CHOICES flag is set
    else
    {
        s32 i, aliveCount = 0, aceMonCount = 0;
        u32 invalidMons = 0, aceMonId = PARTY_SIZE;
        // Get invalid slots ids.
        for (i = firstId; i < lastId; i++)
        {
            if (!IsValidForBattle(&party[i])
                || gBattlerPartyIndexes[battlerIn1] == i
                || gBattlerPartyIndexes[battlerIn2] == i
                || i == gBattleStruct->monToSwitchIntoId[battlerIn1]
                || i == gBattleStruct->monToSwitchIntoId[battlerIn2]
                || (GetMonAbility(&party[i]) == ABILITY_TRUANT && IsTruantMonVulnerable(battler, opposingBattler))) // While not really invalid per se, not really wise to switch into this mon.
            {
                invalidMons |= 1u << i;
            }
            else if (IsAceMon(battler, i)) // Save Ace Pokemon for last.
            {
                aceMonId = i;
                aceMonCount++;
                invalidMons |= 1u << i;
            }
            else
            {
                aliveCount++;
            }
        }
        bestMonId = GetBestMonBatonPass(party, firstId, lastId, invalidMons, aliveCount, battler, opposingBattler);
        if (bestMonId != PARTY_SIZE)
            return bestMonId;

        bestMonId = GetBestMonTypeMatchup(party, firstId, lastId, invalidMons, battler, opposingBattler);
        if (bestMonId != PARTY_SIZE)
            return bestMonId;

        bestMonId = GetBestMonDmg(party, firstId, lastId, invalidMons, battler, opposingBattler);
        if (bestMonId != PARTY_SIZE)
            return bestMonId;

        // If ace mon is the last available Pokemon and U-Turn/Volt Switch or Eject Pack/Button was used - switch to the mon.
        if (aceMonId != PARTY_SIZE && CountUsablePartyMons(battler) <= aceMonCount
        && (IsSwitchOutEffect(GetMoveEffect(gCurrentMove)) || AI_DATA->ejectButtonSwitch || AI_DATA->ejectPackSwitch))
            return aceMonId;

        return PARTY_SIZE;
    }
}

static bool32 AiExpectsToFaintPlayer(u32 battler)
{
    u8 target = gBattleStruct->aiChosenTarget[battler];

    if (gBattleStruct->aiMoveOrAction[battler] > 3)
        return FALSE; // AI not planning to use move

    if (GetBattlerSide(target) != GetBattlerSide(battler)
      && CanIndexMoveFaintTarget(battler, target, gBattleStruct->aiMoveOrAction[battler], 0)
      && AI_IsFaster(battler, target, GetAIChosenMove(battler)))
    {
        // We expect to faint the target and move first -> dont use an item
        return TRUE;
    }

    return FALSE;
}

//battleUsageID example: EFFECT_ITEM_HEAL_AND_CURE_STATUS
bool32 HasHealItemWithEffect(u8 battleUsageID){
    s32 i;
    for (i = 0; i < MAX_TRAINER_ITEMS; i++){
        u16 item;
        const u8 *itemEffects;
        item = gBattleResources->battleHistory->trainerItems[i];
        if (item == ITEM_NONE)
            continue;
        itemEffects = ItemId_GetEffect(item);
        if (itemEffects == NULL)
            continue;
        if (ItemId_GetBattleUsage(item) == battleUsageID){
            // DebugPrintf("Item match holds true.");
            return TRUE;
        }
    }
    return FALSE;
}
static bool32 ShouldUseItem(u32 battler)
{
    struct Pokemon *party;
    s32 i;
    u8 validMons = 0;
    bool32 shouldUse = FALSE;

    DEBUG_ITEM("=== ShouldUseItem called for battler %d ===", battler);

    if (IsAiVsAiBattle())
    {
        DEBUG_ITEM("AI vs AI battle - no item usage");
        return FALSE;
    }

    // If teaming up with player and Pokemon is on the right, or Pokemon is currently held by Sky Drop
    if ((gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER && GetBattlerPosition(battler) == B_POSITION_PLAYER_RIGHT)
       || gStatuses3[battler] & STATUS3_SKY_DROPPED)
    {
        DEBUG_ITEM("Cannot use items - partner battle or sky dropped");
        return FALSE;
    }

    if (gStatuses3[battler] & STATUS3_EMBARGO)
    {
        DEBUG_ITEM("Cannot use items - under Embargo");
        return FALSE;
    }

    if (AiExpectsToFaintPlayer(battler))
    {
        DEBUG_ITEM("Expecting to faint player - not using items");
        return FALSE;
    }

    party = GetBattlerParty(battler);

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (IsValidForBattle(&party[i]))
        {
            validMons++;
        }
    }

    DEBUG_ITEM("Checking available items:");
    for (i = 0; i < MAX_TRAINER_ITEMS; i++)
    {
        u16 item;
        const u8 *itemEffects;
        u8 battlerSide;

        item = gBattleResources->battleHistory->trainerItems[i];
        if (item == ITEM_NONE)
            continue;
        itemEffects = ItemId_GetEffect(item);
        if (itemEffects == NULL)
            continue;

        u8 battleUsage = ItemId_GetBattleUsage(item);
        DEBUG_ITEM("Evaluating item %d (usage type: %d)", item, battleUsage);

        switch (battleUsage)
        {
        case EFFECT_ITEM_HEAL_AND_CURE_STATUS:
            DEBUG_ITEM("Checking Full Restore usage");
            shouldUse = AI_ShouldHeal(battler, 700);
            DEBUG_ITEM("Full Restore decision: %s", shouldUse ? "USE" : "DON'T USE");
            break;
        case EFFECT_ITEM_RESTORE_HP:
            {
                u32 healAmount = itemEffects[GetItemEffectParamOffset(battler, item, 4, ITEM4_HEAL_HP)];
                DEBUG_ITEM("Checking HP restore item (heal amount: %d)", healAmount);
                shouldUse = AI_ShouldHeal(battler, healAmount);
                DEBUG_ITEM("HP restore decision: %s", shouldUse ? "USE" : "DON'T USE");
            }
            break;
        case EFFECT_ITEM_CURE_STATUS:
            DEBUG_ITEM("Checking status cure item");
            DEBUG_STATUS("Current status1: 0x%X, status2: 0x%X", gBattleMons[battler].status1, gBattleMons[battler].status2);
            if (itemEffects[3] & ITEM3_SLEEP && gBattleMons[battler].status1 & STATUS1_SLEEP)
            {
                shouldUse = TRUE;
                DEBUG_ITEM("Using item to cure sleep");
            }
            if (itemEffects[3] & ITEM3_POISON && (gBattleMons[battler].status1 & STATUS1_POISON
                                               || gBattleMons[battler].status1 & STATUS1_TOXIC_POISON))
            {
                shouldUse = TRUE;
                DEBUG_ITEM("Using item to cure poison");
            }
            if (itemEffects[3] & ITEM3_BURN && gBattleMons[battler].status1 & STATUS1_BURN)
            {
                shouldUse = TRUE;
                DEBUG_ITEM("Using item to cure burn");
            }
            if (itemEffects[3] & ITEM3_FREEZE && (gBattleMons[battler].status1 & STATUS1_FREEZE || gBattleMons[battler].status1 & STATUS1_FROSTBITE))
            {
                shouldUse = TRUE;
                DEBUG_ITEM("Using item to cure freeze/frostbite");
            }
            if (itemEffects[3] & ITEM3_PARALYSIS && gBattleMons[battler].status1 & STATUS1_PARALYSIS)
            {
                shouldUse = TRUE;
                DEBUG_ITEM("Using item to cure paralysis");
            }
            if (itemEffects[3] & ITEM3_CONFUSION && gBattleMons[battler].status2 & STATUS2_CONFUSION)
            {
                shouldUse = TRUE;
                DEBUG_ITEM("Using item to cure confusion");
            }
            break;
        case EFFECT_ITEM_INCREASE_STAT:
        case EFFECT_ITEM_INCREASE_ALL_STATS:
            DEBUG_ITEM("Checking stat boost item (first turn: %s)", gDisableStructs[battler].isFirstTurn ? "YES" : "NO");
            if (!gDisableStructs[battler].isFirstTurn
                || AI_OpponentCanFaintAiWithMod(battler, 0))
            {
                DEBUG_ITEM("Not using stat boost - not first turn or opponent can faint");
                break;
            }
            shouldUse = TRUE;
            DEBUG_ITEM("Using stat boost item");
            break;
        case EFFECT_ITEM_SET_FOCUS_ENERGY:
            DEBUG_ITEM("Checking Focus Energy item");
            if (!gDisableStructs[battler].isFirstTurn
                || gBattleMons[battler].status2 & STATUS2_FOCUS_ENERGY_ANY
                || AI_OpponentCanFaintAiWithMod(battler, 0))
            {
                DEBUG_ITEM("Not using Focus Energy - not first turn, already focused, or opponent can faint");
                break;
            }
            shouldUse = TRUE;
            DEBUG_ITEM("Using Focus Energy item");
            break;
        case EFFECT_ITEM_SET_MIST:
            battlerSide = GetBattlerSide(battler);
            DEBUG_ITEM("Checking Mist item (first turn: %s, mist active: %s)",
                       gDisableStructs[battler].isFirstTurn ? "YES" : "NO",
                       (gSideStatuses[battlerSide] & SIDE_STATUS_MIST) ? "YES" : "NO");
            if (gDisableStructs[battler].isFirstTurn && !(gSideStatuses[battlerSide] & SIDE_STATUS_MIST))
            {
                shouldUse = TRUE;
                DEBUG_ITEM("Using Mist item");
            }
            break;
        case EFFECT_ITEM_REVIVE:
            gBattleStruct->itemPartyIndex[battler] = GetFirstFaintedPartyIndex(battler);
            DEBUG_ITEM("Checking Revive item (fainted mon index: %d)", gBattleStruct->itemPartyIndex[battler]);
            if (gBattleStruct->itemPartyIndex[battler] != PARTY_SIZE) // Revive if possible.
            {
                shouldUse = TRUE;
                DEBUG_ITEM("Using Revive item on party slot %d", gBattleStruct->itemPartyIndex[battler]);
            }
            break;
        case EFFECT_ITEM_USE_POKE_FLUTE:
            DEBUG_ITEM("Checking Poke Flute (asleep: %s)", (gBattleMons[battler].status1 & STATUS1_SLEEP) ? "YES" : "NO");
            if (gBattleMons[battler].status1 & STATUS1_SLEEP)
            {
                shouldUse = TRUE;
                DEBUG_ITEM("Using Poke Flute to wake up");
            }
            break;
        default:
            DEBUG_ITEM("Unknown item usage type: %d", battleUsage);
            return FALSE;
        }
        if (shouldUse)
        {
            DEBUG_ITEM("=== USING ITEM %d ===", item);
            // Set selected party ID to current battler if none chosen.
            if (gBattleStruct->itemPartyIndex[battler] == PARTY_SIZE)
                gBattleStruct->itemPartyIndex[battler] = gBattlerPartyIndexes[battler];
            BtlController_EmitTwoReturnValues(battler, BUFFER_B, B_ACTION_USE_ITEM, 0);
            gBattleStruct->chosenItem[battler] = item;
            gBattleResources->battleHistory->trainerItems[i] = 0;
            return shouldUse;
        }
    }

    DEBUG_ITEM("No items to use");
    return FALSE;
}

static bool32 AI_ShouldHeal(u32 battler, u32 healAmount)
{
    //Should be refined in the future and probably not just use the opposite slot
    u32 battlerOpposite = BATTLE_OPPOSITE(GetBattlerPosition(battler));
    bool32 shouldHeal = FALSE;

    DEBUG_ITEM("--- AI_ShouldHeal: battler %d, heal amount %d ---", battler, healAmount);
    DEBUG_ITEM("Current HP: %d/%d, Opponent: %d", gBattleMons[battler].hp, gBattleMons[battler].maxHP, battlerOpposite);

    //Idea is that if there are no Pokemon left, AI mon would faint, and is slower, might as well heal.
    u32 usablePartyMons = CountUsablePartyMons(battler);
    bool32 opponentCanFaint = CanTargetFaintAi(battlerOpposite, battler);
    bool32 aiFaster = AI_IsFaster(battler, battlerOpposite, MOVE_IRRELEVANT);

    DEBUG_ITEM("Usable party mons: %d, Opponent can faint: %s, AI faster: %s",
               usablePartyMons, opponentCanFaint ? "YES" : "NO", aiFaster ? "YES" : "NO");

    if (usablePartyMons == 0 && opponentCanFaint && !aiFaster)
    {
        shouldHeal = TRUE;
        DEBUG_ITEM("Last mon scenario - healing to buy time");
        return shouldHeal;
    }

    u32 hpThreshold = gBattleMons[battler].maxHP / 4;
    u32 missingHP = gBattleMons[battler].maxHP - gBattleMons[battler].hp;
    bool32 lowHP = (gBattleMons[battler].hp < hpThreshold);
    bool32 fainted = (gBattleMons[battler].hp == 0);
    bool32 worthHealing = (healAmount != 0 && missingHP > healAmount);

    DEBUG_ITEM("HP threshold: %d, Missing HP: %d, Low HP: %s, Fainted: %s, Worth healing: %s",
               hpThreshold, missingHP, lowHP ? "YES" : "NO", fainted ? "YES" : "NO", worthHealing ? "YES" : "NO");

    if (lowHP || fainted || worthHealing)
    {
        // We have low enough HP to consider healing
        bool32 opponentCanStillFaint = AI_OpponentCanFaintAiWithMod(battler, healAmount);
        shouldHeal = !opponentCanStillFaint; // if target can kill us even after we heal, why bother
        DEBUG_ITEM("Opponent can still faint after heal: %s, Final decision: %s",
                   opponentCanStillFaint ? "YES" : "NO", shouldHeal ? "HEAL" : "DON'T HEAL");
    }
    else
    {
        DEBUG_ITEM("HP too high to consider healing");
    }

    return shouldHeal;
}

static bool32 AI_OpponentCanFaintAiWithMod(u32 battler, u32 healAmount)
{
    u32 i;
    // Check special cases to NOT heal
    for (i = 0; i < gBattlersCount; i++)
    {
        if (GetBattlerSide(i) == B_SIDE_PLAYER && CanTargetFaintAiWithMod(i, battler, healAmount, 0))
        {
            // Target is expected to faint us
            return TRUE;
        }
    }
    return FALSE;
}
