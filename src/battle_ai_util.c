#include "global.h"
#include "battle_z_move.h"
#include "malloc.h"
#include "battle.h"
#include "battle_anim.h"
#include "battle_ai_util.h"
#include "battle_ai_main.h"
#include "battle_ai_switch_items.h"
#include "battle_factory.h"
#include "battle_setup.h"
#include "event_data.h"
#include "data.h"
#include "item.h"
#include "move.h"
#include "pokemon.h"
#include "random.h"
#include "recorded_battle.h"
#include "util.h"
#include "constants/abilities.h"
#include "constants/battle_ai.h"
#include "constants/battle_move_effects.h"
#include "constants/hold_effects.h"
#include "constants/moves.h"
#include "constants/items.h"



// Functions
static bool32 AI_IsDoubleSpreadMove(u32 battlerAtk, u32 move)
{
    u32 numOfTargets = 0;
    u32 moveTargetType = GetBattlerMoveTargetType(battlerAtk, move);

    if (!IsSpreadMove(moveTargetType))
        return FALSE;

    for (u32 battlerDef = 0; battlerDef < MAX_BATTLERS_COUNT; battlerDef++)
    {
        if (battlerAtk == battlerDef)
            continue;

        if (moveTargetType == MOVE_TARGET_BOTH && battlerAtk == BATTLE_PARTNER(battlerDef))
            continue;

        if (IsBattlerAlive(battlerDef) && !IsSemiInvulnerable(battlerDef, move))
            numOfTargets++;
    }

    if (numOfTargets > 1)
        return TRUE;

    return FALSE;
}

u32 AI_GetDamage(u32 battlerAtk, u32 battlerDef, u32 moveIndex, enum DamageCalcContext calcContext, struct AiLogicData *aiData)
{
    if (calcContext == AI_ATTACKING && BattlerHasAi(battlerAtk))
    {

        if ((gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_RISKY) && !(gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_CONSERVATIVE)) // Risky assumes it deals max damage
            return aiData->simulatedDmg[battlerAtk][battlerDef][moveIndex].maximum;
        if ((gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_CONSERVATIVE) && !(gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_RISKY)) // Conservative assumes it deals min damage
            return aiData->simulatedDmg[battlerAtk][battlerDef][moveIndex].minimum;
        return aiData->simulatedDmg[battlerAtk][battlerDef][moveIndex].median; // Default assumes it deals median damage
    }
    else if (calcContext == AI_DEFENDING && BattlerHasAi(battlerDef))
    {
        if ((gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_RISKY) && !(gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_CONSERVATIVE)) // Risky assumes it takes min damage
            return aiData->simulatedDmg[battlerAtk][battlerDef][moveIndex].minimum;
        if ((gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_CONSERVATIVE) && !(gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_RISKY)) // Conservative assumes it takes max damage
            return aiData->simulatedDmg[battlerAtk][battlerDef][moveIndex].maximum;
        return aiData->simulatedDmg[battlerAtk][battlerDef][moveIndex].median; // Default assumes it takes median damage
    }
    else
    {
        return aiData->simulatedDmg[battlerAtk][battlerDef][moveIndex].median;
    }
}

bool32 AI_IsFaster(u32 battlerAi, u32 battlerDef, u32 move)
{
    return (AI_WhoStrikesFirst(battlerAi, battlerDef, move) == AI_IS_FASTER);
}

bool32 AI_IsSlower(u32 battlerAi, u32 battlerDef, u32 move)
{
    return (AI_WhoStrikesFirst(battlerAi, battlerDef, move) == AI_IS_SLOWER);
}

u32 GetAIChosenMove(u32 battlerId)
{
    return (gBattleMons[battlerId].moves[gAiBattleData->chosenMoveIndex[battlerId]]);
}

bool32 AI_RandLessThan(u32 val)
{
    if ((Random() % 0xFF) < val)
        return TRUE;
    return FALSE;
}

bool32 IsAiVsAiBattle(void)
{
    return (B_FLAG_AI_VS_AI_BATTLE && FlagGet(B_FLAG_AI_VS_AI_BATTLE));
}

bool32 BattlerHasAi(u32 battlerId)
{
    switch (GetBattlerPosition(battlerId))
    {
    case B_POSITION_PLAYER_LEFT:
        if (IsAiVsAiBattle())
            return TRUE;
    default:
        return FALSE;
    case B_POSITION_OPPONENT_LEFT:
        return TRUE;
    case B_POSITION_PLAYER_RIGHT:
        if ((gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER) || IsAiVsAiBattle())
            return TRUE;
        else
            return FALSE;
    case B_POSITION_OPPONENT_RIGHT:
        return TRUE;
    }
}

bool32 IsAiBattlerAware(u32 battlerId)
{
    if (gAiThinkingStruct->aiFlags[B_POSITION_OPPONENT_LEFT] & AI_FLAG_OMNISCIENT
     || gAiThinkingStruct->aiFlags[B_POSITION_OPPONENT_RIGHT] & AI_FLAG_OMNISCIENT)
        return TRUE;

    return BattlerHasAi(battlerId);
}

bool32 IsAiBattlerPredictingAbility(u32 battlerId)
{
    if (gAiThinkingStruct->aiFlags[B_POSITION_OPPONENT_LEFT] & AI_FLAG_WEIGH_ABILITY_PREDICTION
     || gAiThinkingStruct->aiFlags[B_POSITION_OPPONENT_RIGHT] & AI_FLAG_WEIGH_ABILITY_PREDICTION)
        return TRUE;

    return BattlerHasAi(battlerId);
}

bool32 IsBattlerPredictedToSwitch(u32 battler)
{
    // Check for prediction flag on AI, whether they're using those predictions this turn, and whether the AI thinks the player should switch
    if (gAiThinkingStruct->aiFlags[gAiLogicData->battlerDoingPrediction] & AI_FLAG_PREDICT_SWITCH
     || gAiThinkingStruct->aiFlags[gAiLogicData->battlerDoingPrediction] & AI_FLAG_PREDICT_SWITCH)
    {
        if (gAiLogicData->predictingSwitch && gAiLogicData->shouldSwitch & (1u << battler))
            return TRUE;
    }
    return FALSE;
}

// Either a predicted move or the last used move from an opposing battler
u32 GetIncomingMove(u32 battler, u32 opposingBattler, struct AiLogicData *aiData)
{
    if (gAiThinkingStruct->aiFlags[battler] & AI_FLAG_PREDICT_MOVE && aiData->predictingMove)
        return aiData->predictedMove[opposingBattler];

    return aiData->lastUsedMove[opposingBattler];
}

void ClearBattlerMoveHistory(u32 battlerId)
{
    memset(gBattleHistory->usedMoves[battlerId], 0, sizeof(gBattleHistory->usedMoves[battlerId]));
    memset(gBattleHistory->moveHistory[battlerId], 0, sizeof(gBattleHistory->moveHistory[battlerId]));
    gBattleHistory->moveHistoryIndex[battlerId] = 0;
}

void RecordLastUsedMoveBy(u32 battlerId, u32 move)
{
    u8 *index = &gBattleHistory->moveHistoryIndex[battlerId];

    if (++(*index) >= AI_MOVE_HISTORY_COUNT)
        *index = 0;
    gBattleHistory->moveHistory[battlerId][*index] = move;
}

void RecordKnownMove(u32 battler, u32 move)
{
    s32 moveIndex;

    for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (gBattleMons[battler].moves[moveIndex] == move)
            break;
    }

    if (moveIndex < MAX_MON_MOVES && gBattleHistory->usedMoves[battler][moveIndex] == MOVE_NONE)
    {
        gBattleHistory->usedMoves[battler][moveIndex] = move;
        gAiPartyData->mons[GetBattlerSide(battler)][gBattlerPartyIndexes[battler]].moves[moveIndex] = move;
    }
}

void RecordAllMoves(u32 battler)
{
    memcpy(gAiPartyData->mons[GetBattlerSide(battler)][gBattlerPartyIndexes[battler]].moves, gBattleMons[battler].moves, MAX_MON_MOVES * sizeof(u16));
}

void RecordAbilityBattle(u32 battlerId, u32 abilityId)
{
    gBattleHistory->abilities[battlerId] = abilityId;
    gAiPartyData->mons[GetBattlerSide(battlerId)][gBattlerPartyIndexes[battlerId]].ability = abilityId;
}

void ClearBattlerAbilityHistory(u32 battlerId)
{
    gBattleHistory->abilities[battlerId] = ABILITY_NONE;
}

void RecordItemEffectBattle(u32 battlerId, u32 itemEffect)
{
    gBattleHistory->itemEffects[battlerId] = itemEffect;
    gAiPartyData->mons[GetBattlerSide(battlerId)][gBattlerPartyIndexes[battlerId]].heldEffect = itemEffect;
}

void ClearBattlerItemEffectHistory(u32 battlerId)
{
    gBattleHistory->itemEffects[battlerId] = 0;
}

void SaveBattlerData(u32 battlerId)
{
    if (!BattlerHasAi(battlerId) && !gAiThinkingStruct->saved[battlerId].saved)
    {
        u32 i;

        gAiThinkingStruct->saved[battlerId].saved = TRUE;
        gAiThinkingStruct->saved[battlerId].ability = gBattleMons[battlerId].ability;
        gAiThinkingStruct->saved[battlerId].heldItem = gBattleMons[battlerId].item;
        gAiThinkingStruct->saved[battlerId].species = gBattleMons[battlerId].species;
        for (i = 0; i < 4; i++)
            gAiThinkingStruct->saved[battlerId].moves[i] = gBattleMons[battlerId].moves[i];
    }
    // Save and restore types even for AI controlled battlers in case it gets changed during move evaluation process.
    gAiThinkingStruct->saved[battlerId].types[0] = gBattleMons[battlerId].types[0];
    gAiThinkingStruct->saved[battlerId].types[1] = gBattleMons[battlerId].types[1];
}

static bool32 ShouldFailForIllusion(u32 illusionSpecies, u32 battlerId)
{
    u32 i, j;
    const struct LevelUpMove *learnset;

    if (gBattleHistory->abilities[battlerId] == ABILITY_ILLUSION)
        return FALSE;

    // Don't fall for Illusion if the mon used a move it cannot know.
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        u32 move = gBattleHistory->usedMoves[battlerId][i];
        if (move == MOVE_NONE)
            continue;

        learnset = GetSpeciesLevelUpLearnset(illusionSpecies);
        for (j = 0; learnset[j].move != MOVE_UNAVAILABLE; j++)
        {
            if (learnset[j].move == move)
                break;
        }
        // The used move is in the learnsets of the fake species.
        if (learnset[j].move != MOVE_UNAVAILABLE)
            continue;

        // The used move can be learned from Tm/Hm or Move Tutors.
        if (CanLearnTeachableMove(illusionSpecies, move))
            continue;

        // 'Illegal move', AI won't fail for the illusion.
        return FALSE;
    }

    return TRUE;
}

void SetBattlerData(u32 battlerId)
{
    if (!BattlerHasAi(battlerId) && gAiThinkingStruct->saved[battlerId].saved)
    {
        u32 i, species, illusionSpecies, side;
        side = GetBattlerSide(battlerId);

        // Simulate Illusion
        species = gBattleMons[battlerId].species;
        illusionSpecies = GetIllusionMonSpecies(battlerId);
        if (illusionSpecies != SPECIES_NONE && ShouldFailForIllusion(illusionSpecies, battlerId))
        {
            // If the battler's type has not been changed, AI assumes the types of the illusion mon.
            if (gBattleMons[battlerId].types[0] == gSpeciesInfo[species].types[0]
                && gBattleMons[battlerId].types[1] == gSpeciesInfo[species].types[1])
            {
                gBattleMons[battlerId].types[0] = gSpeciesInfo[illusionSpecies].types[0];
                gBattleMons[battlerId].types[1] = gSpeciesInfo[illusionSpecies].types[1];
            }
            species = illusionSpecies;
        }

        // Use the known battler's ability.
        if (gAiPartyData->mons[side][gBattlerPartyIndexes[battlerId]].ability != ABILITY_NONE)
            gBattleMons[battlerId].ability = gAiPartyData->mons[side][gBattlerPartyIndexes[battlerId]].ability;
        // Check if mon can only have one ability.
        else if (gSpeciesInfo[species].abilities[1] == ABILITY_NONE
                || gSpeciesInfo[species].abilities[1] == gSpeciesInfo[species].abilities[0])
            gBattleMons[battlerId].ability = gSpeciesInfo[species].abilities[0];
        // The ability is unknown.
        else
            gBattleMons[battlerId].ability = ABILITY_NONE;

        if (gAiPartyData->mons[side][gBattlerPartyIndexes[battlerId]].heldEffect == 0)
            gBattleMons[battlerId].item = 0;

        for (i = 0; i < MAX_MON_MOVES; i++)
        {
            if (gAiPartyData->mons[side][gBattlerPartyIndexes[battlerId]].moves[i] == 0)
                gBattleMons[battlerId].moves[i] = 0;
        }
    }
}

void RestoreBattlerData(u32 battlerId)
{
    if (!BattlerHasAi(battlerId) && gAiThinkingStruct->saved[battlerId].saved)
    {
        u32 i;

        gAiThinkingStruct->saved[battlerId].saved = FALSE;
        gBattleMons[battlerId].ability = gAiThinkingStruct->saved[battlerId].ability;
        gBattleMons[battlerId].item = gAiThinkingStruct->saved[battlerId].heldItem;
        gBattleMons[battlerId].species = gAiThinkingStruct->saved[battlerId].species;
        for (i = 0; i < 4; i++)
            gBattleMons[battlerId].moves[i] = gAiThinkingStruct->saved[battlerId].moves[i];
    }
    gBattleMons[battlerId].types[0] = gAiThinkingStruct->saved[battlerId].types[0];
    gBattleMons[battlerId].types[1] = gAiThinkingStruct->saved[battlerId].types[1];
}

u32 GetHealthPercentage(u32 battlerId)
{
    return (u32)((100 * gBattleMons[battlerId].hp) / gBattleMons[battlerId].maxHP);
}

bool32 AI_BattlerAtMaxHp(u32 battlerId)
{
    if (gAiLogicData->hpPercents[battlerId] == 100)
        return TRUE;
    return FALSE;
}


bool32 AI_CanBattlerEscape(u32 battler)
{
    enum ItemHoldEffect holdEffect = gAiLogicData->holdEffects[battler];

    if (B_GHOSTS_ESCAPE >= GEN_6 && IS_BATTLER_OF_TYPE(battler, TYPE_GHOST))
        return TRUE;
    if (holdEffect == HOLD_EFFECT_SHED_SHELL)
        return TRUE;

    return FALSE;
}

bool32 IsBattlerTrapped(u32 battlerAtk, u32 battlerDef)
{
    if (gBattleMons[battlerDef].status2 & (STATUS2_ESCAPE_PREVENTION | STATUS2_WRAPPED))
        return TRUE;
    if (gStatuses3[battlerDef] & (STATUS3_ROOTED | STATUS3_SKY_DROPPED))
        return TRUE;
    if (gFieldStatuses & STATUS_FIELD_FAIRY_LOCK)
        return TRUE;
    if (AI_IsAbilityOnSide(battlerAtk, ABILITY_SHADOW_TAG)
        && (B_SHADOW_TAG_ESCAPE >= GEN_4 && gAiLogicData->abilities[battlerDef] != ABILITY_SHADOW_TAG))
        return TRUE;
    if (AI_IsAbilityOnSide(battlerAtk, ABILITY_ARENA_TRAP)
        && IsBattlerGrounded(battlerAtk))
        return TRUE;
    if (AI_IsAbilityOnSide(battlerAtk, ABILITY_MAGNET_PULL)
        && IS_BATTLER_OF_TYPE(battlerAtk, TYPE_STEEL))
        return TRUE;

    return FALSE;
}

u32 GetTotalBaseStat(u32 species)
{
    return gSpeciesInfo[species].baseHP
        + gSpeciesInfo[species].baseAttack
        + gSpeciesInfo[species].baseDefense
        + gSpeciesInfo[species].baseSpeed
        + gSpeciesInfo[species].baseSpAttack
        + gSpeciesInfo[species].baseSpDefense;
}

bool32 IsTruantMonVulnerable(u32 battlerAI, u32 opposingBattler)
{
    int i;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        u32 move = gBattleHistory->usedMoves[opposingBattler][i];
        enum BattleMoveEffects effect = GetMoveEffect(move);
        if (effect == EFFECT_PROTECT && move != MOVE_ENDURE)
            return TRUE;
        if (effect == EFFECT_SEMI_INVULNERABLE && AI_IsSlower(battlerAI, opposingBattler, GetAIChosenMove(battlerAI)))
            return TRUE;
    }
    return FALSE;
}

// move checks
bool32 IsAffectedByPowder(u32 battler, u32 ability, enum ItemHoldEffect holdEffect)
{
    if (ability == ABILITY_OVERCOAT
        || (B_POWDER_GRASS >= GEN_6 && IS_BATTLER_OF_TYPE(battler, TYPE_GRASS))
        || holdEffect == HOLD_EFFECT_SAFETY_GOGGLES)
        return FALSE;
    return TRUE;
}

// This function checks if all physical/special moves are either unusable or unreasonable to use.
// Consider a pokemon boosting their attack against a ghost pokemon having only normal-type physical attacks.
bool32 MovesWithCategoryUnusable(u32 attacker, u32 target, u32 category)
{
    s32 i, moveType;
    u32 usable = 0;
    u16 *moves = GetMovesArray(attacker);
    u32 moveLimitations = gAiLogicData->moveLimitations[attacker];

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (IsMoveUnusable(i, moves[i], moveLimitations))
            continue;

        if (GetBattleMoveCategory(moves[i]) == category)
        {
            SetTypeBeforeUsingMove(moves[i], attacker);
            moveType = GetBattleMoveType(moves[i]);
            if (CalcTypeEffectivenessMultiplier(moves[i], moveType, attacker, target, gAiLogicData->abilities[target], FALSE) != 0)
                usable |= 1u << i;
        }
    }

    return (usable == 0);
}

// To save computation time this function has 2 variants. One saves, sets and restores battlers, while the other doesn't.
struct SimulatedDamage AI_CalcDamageSaveBattlers(u32 move, u32 battlerAtk, u32 battlerDef, uq4_12_t *typeEffectiveness, bool32 considerZPower)
{
    struct SimulatedDamage dmg;

    SaveBattlerData(battlerAtk);
    SaveBattlerData(battlerDef);
    SetBattlerData(battlerAtk);
    SetBattlerData(battlerDef);
    dmg = AI_CalcDamage(move, battlerAtk, battlerDef, typeEffectiveness, considerZPower, AI_GetWeather());
    RestoreBattlerData(battlerAtk);
    RestoreBattlerData(battlerDef);
    return dmg;
}

static inline s32 LowestRollDmg(s32 dmg)
{
    dmg *= MIN_ROLL_PERCENTAGE;
    dmg /= 100;
    return dmg;
}

static inline s32 HighestRollDmg(s32 dmg)
{
    dmg *= MAX_ROLL_PERCENTAGE;
    dmg /= 100;
    return dmg;
}

static inline s32 DmgRoll(s32 dmg)
{
    dmg *= DMG_ROLL_PERCENTAGE;
    dmg /= 100;
    return dmg;
}

bool32 IsDamageMoveUnusable(u32 battlerAtk, u32 battlerDef, u32 move, u32 moveType, uq4_12_t effectiveness, u32 weather)
{
    u32 battlerDefAbility;
    u32 partnerDefAbility;
    struct AiLogicData *aiData = gAiLogicData;

    if (effectiveness == UQ_4_12(0.0))
        return TRUE;
    if (gBattleStruct->battlerState[battlerDef].commandingDondozo)
        return TRUE;

    // aiData->abilities does not check for Mold Breaker since it happens during combat so it needs to be done manually
    if (IsMoldBreakerTypeAbility(battlerAtk, aiData->abilities[battlerAtk]) || MoveIgnoresTargetAbility(move))
    {
        battlerDefAbility = ABILITY_NONE;
        partnerDefAbility = ABILITY_NONE;
    }
    else
    {
        battlerDefAbility = aiData->abilities[battlerDef];
        partnerDefAbility = aiData->abilities[BATTLE_PARTNER(battlerDef)];
    }

    if (CanAbilityBlockMove(battlerAtk, battlerDef, aiData->abilities[battlerAtk], battlerDefAbility, move, ABILITY_CHECK_TRIGGER))
        return TRUE;

    if (CanAbilityAbsorbMove(battlerAtk, battlerDef, battlerDefAbility, move, moveType, ABILITY_CHECK_TRIGGER))
        return TRUE;

    // Limited to Lighning Rod and Storm Drain because otherwise the AI would consider Water Absorb, etc...
    if (partnerDefAbility == ABILITY_LIGHTNING_ROD || partnerDefAbility == ABILITY_STORM_DRAIN)
    {
        if (CanAbilityAbsorbMove(battlerAtk, BATTLE_PARTNER(battlerDef), partnerDefAbility, move, moveType, ABILITY_CHECK_TRIGGER))
            return TRUE;
    }

    if (HasWeatherEffect())
    {
        if (weather & B_WEATHER_SUN_PRIMAL && moveType == TYPE_WATER)
            return TRUE;
        if (weather & B_WEATHER_RAIN_PRIMAL && moveType == TYPE_FIRE)
            return TRUE;
    }

    switch (GetMoveEffect(move))
    {
    case EFFECT_DREAM_EATER:
        if (!AI_IsBattlerAsleepOrComatose(battlerDef))
            return TRUE;
        break;
    case EFFECT_BELCH:
        if (IsBelchPreventingMove(battlerAtk, move))
            return TRUE;
        break;
    case EFFECT_LAST_RESORT:
        if (!CanUseLastResort(battlerAtk))
            return TRUE;
        break;
    case EFFECT_LOW_KICK:
    case EFFECT_HEAT_CRASH:
        if (GetActiveGimmick(battlerDef) == GIMMICK_DYNAMAX)
            return TRUE;
        break;
    case EFFECT_FAIL_IF_NOT_ARG_TYPE:
        if (!IS_BATTLER_OF_TYPE(battlerAtk, GetMoveArgType(move)))
            return TRUE;
        break;
    case EFFECT_HIT_SET_REMOVE_TERRAIN:
        if (!(gFieldStatuses & STATUS_FIELD_TERRAIN_ANY) && GetMoveEffectArg_MoveProperty(move) == ARG_TRY_REMOVE_TERRAIN_FAIL)
            return TRUE;
        break;
    case EFFECT_POLTERGEIST:
        if (gAiLogicData->items[battlerDef] == ITEM_NONE || !IsBattlerItemEnabled(battlerDef))
            return TRUE;
        break;
    case EFFECT_FIRST_TURN_ONLY:
        if (!gDisableStructs[battlerAtk].isFirstTurn)
            return TRUE;
        break;
    case EFFECT_EXPLOSION:
    case EFFECT_MIND_BLOWN:
        if (battlerDefAbility == ABILITY_DAMP || partnerDefAbility == ABILITY_DAMP)
            return TRUE;
        break;
    default:
        break;
    }

    return FALSE;
}

static inline s32 GetDamageByRollType(s32 dmg, enum DamageRollType rollType)
{
    if (rollType == DMG_ROLL_LOWEST)
        return LowestRollDmg(dmg);
    else if (rollType == DMG_ROLL_HIGHEST)
        return HighestRollDmg(dmg);
    else
        return DmgRoll(dmg);
}

static inline s32 SetFixedMoveBasePower(u32 battlerAtk, u32 move)
{
    s32 fixedBasePower = 0, n = 0;
    switch (GetMoveEffect(move))
    {
    case EFFECT_ROLLOUT:
        n = gDisableStructs[battlerAtk].rolloutTimer - 1;
        fixedBasePower = CalcRolloutBasePower(battlerAtk, GetMovePower(move), n < 0 ? 5 : n);
        break;
    case EFFECT_FURY_CUTTER:
        fixedBasePower = CalcFuryCutterBasePower(GetMovePower(move), min(gDisableStructs[battlerAtk].furyCutterCounter + 1, 5));
        break;
    default:
        fixedBasePower = 0;
        break;
    }
    return fixedBasePower;
}

static inline void AI_StoreBattlerTypes(u32 battlerAtk, u32 *types)
{
    types[0] = gBattleMons[battlerAtk].types[0];
    types[1] = gBattleMons[battlerAtk].types[1];
    types[2] = gBattleMons[battlerAtk].types[2];
}

static inline void AI_RestoreBattlerTypes(u32 battlerAtk, u32 *types)
{
    gBattleMons[battlerAtk].types[0] = types[0];
    gBattleMons[battlerAtk].types[1] = types[1];
    gBattleMons[battlerAtk].types[2] = types[2];
}

static inline void CalcDynamicMoveDamage(struct DamageCalculationData *damageCalcData, u16 *medianDamage, u16 *minimumDamage, u16 *maximumDamage, enum ItemHoldEffect holdEffectAtk, u32 abilityAtk)
{
    u32 move = damageCalcData->move;
    enum BattleMoveEffects effect = GetMoveEffect(move);
    u16 median = *medianDamage;
    u16 minimum = *minimumDamage;
    u16 maximum = *maximumDamage;

    switch (effect)
    {
    case EFFECT_MULTI_HIT:
        if (move == MOVE_WATER_SHURIKEN && gBattleMons[damageCalcData->battlerAtk].species == SPECIES_GRENINJA_ASH)
        {
            median *= 3;
            minimum *= 3;
            maximum *= 3;
        }
        else if (abilityAtk == ABILITY_SKILL_LINK)
        {
            median *= 5;
            minimum *= 5;
            maximum *= 5;
        }
        else if (holdEffectAtk == HOLD_EFFECT_LOADED_DICE)
        {
            median *= 9;
            median /= 2;
            minimum *= 4;
            maximum *= 5;
        }
        else
        {
            median *= 3;
            minimum *= 2;
            maximum *= 5;
        }
        break;
    case EFFECT_ENDEAVOR:
        // If target has less HP than user, Endeavor does no damage
        median = maximum = minimum = max(0, gBattleMons[damageCalcData->battlerDef].hp - gBattleMons[damageCalcData->battlerAtk].hp);
        break;
    case EFFECT_FINAL_GAMBIT:
        median = maximum = minimum = gBattleMons[damageCalcData->battlerAtk].hp;
        break;
    case EFFECT_BEAT_UP:
        if (B_BEAT_UP >= GEN_5)
        {
            u32 partyCount = CalculatePartyCount(GetBattlerParty(damageCalcData->battlerAtk));
            u32 i;
            gBattleStruct->beatUpSlot = 0;
            damageCalcData->isCrit = FALSE;
            median = 0;
            for (i = 0; i < partyCount; i++)
                median += CalculateMoveDamage(damageCalcData, 0);
            maximum = minimum = median;
            gBattleStruct->beatUpSlot = 0;
        }
        break;
    default:
        break;
    }

    // Handle other multi-strike moves
    u32 strikeCount = GetMoveStrikeCount(move);
    if (strikeCount > 1 && effect != EFFECT_TRIPLE_KICK)
    {
        median *= strikeCount;
        minimum *= strikeCount;
        maximum *= strikeCount;
    }

    if (abilityAtk == ABILITY_PARENTAL_BOND
        && !strikeCount
        && effect != EFFECT_TRIPLE_KICK
        && effect != EFFECT_MULTI_HIT
        && !AI_IsDoubleSpreadMove(damageCalcData->battlerAtk, move))
    {
        median  += median  / (B_PARENTAL_BOND_DMG >= GEN_7 ? 4 : 2);
        minimum += minimum / (B_PARENTAL_BOND_DMG >= GEN_7 ? 4 : 2);
        maximum += maximum / (B_PARENTAL_BOND_DMG >= GEN_7 ? 4 : 2);
    }

    if (median == 0)
        median = 1;
    if (minimum == 0)
        minimum = 1;
    if (maximum == 0)
        maximum = 1;

    *medianDamage = median;
    *minimumDamage = minimum;
    *maximumDamage = maximum;
}

static inline bool32 ShouldCalcCritDamage(u32 battlerAtk, u32 battlerDef, u32 move, struct AiLogicData *aiData)
{
    s32 critChanceIndex = 0;

    // Get crit chance
    if (GetGenConfig(GEN_CONFIG_CRIT_CHANCE) == GEN_1)
        critChanceIndex = CalcCritChanceStageGen1(battlerAtk, battlerDef, move, FALSE, aiData->abilities[battlerAtk], aiData->abilities[battlerDef], aiData->holdEffects[battlerAtk]);
    else
        critChanceIndex = CalcCritChanceStage(battlerAtk, battlerDef, move, FALSE, aiData->abilities[battlerAtk], aiData->abilities[battlerDef], aiData->holdEffects[battlerAtk]);

    if (critChanceIndex == CRITICAL_HIT_ALWAYS)
        return TRUE;
    if (critChanceIndex >= RISKY_AI_CRIT_STAGE_THRESHOLD // Not guaranteed but above Risky threshold
        && (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_RISKY)
        && GetGenConfig(GEN_CONFIG_CRIT_CHANCE) != GEN_1)
        return TRUE;
    if (critChanceIndex >= RISKY_AI_CRIT_THRESHOLD_GEN_1 // Not guaranteed but above Risky threshold
        && (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_RISKY)
        && GetGenConfig(GEN_CONFIG_CRIT_CHANCE) == GEN_1)
        return TRUE;
    return FALSE;
}

struct SimulatedDamage AI_CalcDamage(u32 move, u32 battlerAtk, u32 battlerDef, uq4_12_t *typeEffectiveness, bool32 considerZPower, u32 weather)
{
    struct SimulatedDamage simDamage;
    s32 moveType;
    enum BattleMoveEffects moveEffect = GetMoveEffect(move);
    uq4_12_t effectivenessMultiplier;
    bool32 isDamageMoveUnusable = FALSE;
    bool32 toggledGimmick = FALSE;
    struct AiLogicData *aiData = gAiLogicData;
    gAiLogicData->aiCalcInProgress = TRUE;

    const u32 BATTLER_NONE = 255; 

    //Need to test this aiBattler approach which aims to allow the simulated tera to apply for either the attacker or defender, 
    //depending on who's the AI mon
    u32 aiBattler = BATTLER_NONE;
    
    if (GetBattlerSide(battlerAtk) == B_SIDE_OPPONENT){
        aiBattler = battlerAtk;
    }else if (GetBattlerSide(battlerDef) == B_SIDE_OPPONENT){
        aiBattler = battlerDef;
    }

    if (moveEffect == EFFECT_NATURE_POWER)
        move = GetNaturePowerMove(battlerAtk);

    //TODO: The AI Tera simulation currently only applies when 
    

    // Temporarily enable gimmicks for damage calcs if planned
    if (aiBattler != BATTLER_NONE
        && gBattleStruct->gimmick.usableGimmick[aiBattler] 
    && GetActiveGimmick(aiBattler) == GIMMICK_NONE
    && !(gBattleStruct->gimmick.usableGimmick[aiBattler] == GIMMICK_TERA && !AI_ShouldTerastal(aiBattler))
    && !(gBattleStruct->gimmick.usableGimmick[aiBattler] == GIMMICK_Z_MOVE && !considerZPower))
    {
        // Set Z-Move variables if needed
        if (gBattleStruct->gimmick.usableGimmick[aiBattler] == GIMMICK_Z_MOVE && IsViableZMove(aiBattler, move))
            gBattleStruct->zmove.baseMoves[aiBattler] = move;

        toggledGimmick = TRUE;
        SetActiveGimmick(aiBattler, gBattleStruct->gimmick.usableGimmick[aiBattler]);
    }

    SetDynamicMoveCategory(battlerAtk, battlerDef, move);
    SetTypeBeforeUsingMove(move, battlerAtk);
    moveType = GetBattleMoveType(move);
    effectivenessMultiplier = CalcTypeEffectivenessMultiplier(move, moveType, battlerAtk, battlerDef, aiData->abilities[battlerDef], FALSE);

    u32 movePower = GetMovePower(move);
    if (movePower)
        isDamageMoveUnusable = IsDamageMoveUnusable(battlerAtk, battlerDef, move, moveType, effectivenessMultiplier, weather);

    if (movePower && !isDamageMoveUnusable)
    {
        u32 types[3];
        AI_StoreBattlerTypes(battlerAtk, types);

        ProteanTryChangeType(battlerAtk, aiData->abilities[battlerAtk], move, moveType);
        s32 fixedBasePower = SetFixedMoveBasePower(battlerAtk, move);

        struct DamageCalculationData damageCalcData;
        damageCalcData.battlerAtk = battlerAtk;
        damageCalcData.battlerDef = battlerDef;
        damageCalcData.move = move;
        damageCalcData.moveType = moveType;
        damageCalcData.isCrit = ShouldCalcCritDamage(battlerAtk, battlerDef, move, aiData);
        damageCalcData.randomFactor = FALSE;
        damageCalcData.updateFlags = FALSE;





        if (moveEffect == EFFECT_TRIPLE_KICK)
        {
            for (gMultiHitCounter = GetMoveStrikeCount(move); gMultiHitCounter > 0; gMultiHitCounter--) // The global is used to simulate actual damage done
            {
                s32 damageByRollType = 0;

                s32 oneTripleKickHit = CalculateMoveDamageVars(&damageCalcData, fixedBasePower,
                                                               effectivenessMultiplier, weather,
                                                               aiData->holdEffects[battlerAtk], aiData->holdEffects[battlerDef],
                                                               aiData->abilities[battlerAtk], aiData->abilities[battlerDef]);

                damageByRollType = GetDamageByRollType(oneTripleKickHit, DMG_ROLL_LOWEST);
                simDamage.minimum += ApplyModifiersAfterDmgRoll(damageByRollType, &damageCalcData, effectivenessMultiplier,
                                                                aiData->holdEffects[battlerAtk], aiData->holdEffects[battlerDef],
                                                                aiData->abilities[battlerAtk], aiData->abilities[battlerDef]);


                damageByRollType = GetDamageByRollType(oneTripleKickHit, DMG_ROLL_DEFAULT);
                simDamage.median += ApplyModifiersAfterDmgRoll(damageByRollType, &damageCalcData, effectivenessMultiplier,
                                                               aiData->holdEffects[battlerAtk], aiData->holdEffects[battlerDef],
                                                               aiData->abilities[battlerAtk], aiData->abilities[battlerDef]);

                damageByRollType = GetDamageByRollType(oneTripleKickHit, DMG_ROLL_HIGHEST);
                simDamage.maximum += ApplyModifiersAfterDmgRoll(damageByRollType, &damageCalcData, effectivenessMultiplier,
                                                                aiData->holdEffects[battlerAtk], aiData->holdEffects[battlerDef],
                                                                aiData->abilities[battlerAtk], aiData->abilities[battlerDef]);
            }
        }
        else
        {
            u32 damage = CalculateMoveDamageVars(&damageCalcData, fixedBasePower,
                                                 effectivenessMultiplier, weather,
                                                 aiData->holdEffects[battlerAtk], aiData->holdEffects[battlerDef],
                                                 aiData->abilities[battlerAtk], aiData->abilities[battlerDef]);

            simDamage.minimum = GetDamageByRollType(damage, DMG_ROLL_LOWEST);
            simDamage.minimum = ApplyModifiersAfterDmgRoll(simDamage.minimum, &damageCalcData, effectivenessMultiplier,
                                                           aiData->holdEffects[battlerAtk], aiData->holdEffects[battlerDef],
                                                           aiData->abilities[battlerAtk], aiData->abilities[battlerDef]);

            simDamage.median = GetDamageByRollType(damage, DMG_ROLL_DEFAULT);
            simDamage.median = ApplyModifiersAfterDmgRoll(simDamage.median, &damageCalcData, effectivenessMultiplier,
                                                          aiData->holdEffects[battlerAtk], aiData->holdEffects[battlerDef],
                                                          aiData->abilities[battlerAtk], aiData->abilities[battlerDef]);

            simDamage.maximum = GetDamageByRollType(damage, DMG_ROLL_HIGHEST);
            simDamage.maximum = ApplyModifiersAfterDmgRoll(simDamage.maximum, &damageCalcData, effectivenessMultiplier,
                                                           aiData->holdEffects[battlerAtk], aiData->holdEffects[battlerDef],
                                                           aiData->abilities[battlerAtk], aiData->abilities[battlerDef]);
                                                    
        }

        if (GetActiveGimmick(battlerAtk) != GIMMICK_Z_MOVE)
        {
            CalcDynamicMoveDamage(&damageCalcData,
                                  &simDamage.median,
                                  &simDamage.minimum,
                                  &simDamage.maximum,
                                  aiData->holdEffects[battlerAtk],
                                  aiData->abilities[battlerAtk]);
        }

        AI_RestoreBattlerTypes(battlerAtk, types);
    }
    else
    {
        simDamage.minimum = 0;
        simDamage.median = 0;
        simDamage.maximum = 0;
    }

    // convert multiper to AI_EFFECTIVENESS_xX
    *typeEffectiveness = effectivenessMultiplier;

    // Undo temporary settings
    gBattleStruct->dynamicMoveType = 0;
    gBattleStruct->swapDamageCategory = FALSE;
    if (aiBattler != BATTLER_NONE){
        gBattleStruct->zmove.baseMoves[aiBattler] = MOVE_NONE;
        if (toggledGimmick)
        SetActiveGimmick(aiBattler, GIMMICK_NONE);
    }
    gAiLogicData->aiCalcInProgress = FALSE;
    return simDamage;
}

bool32 AI_IsDamagedByRecoil(u32 battler)
{
    u32 ability = gAiLogicData->abilities[battler];
    if (ability == ABILITY_MAGIC_GUARD || ability == ABILITY_ROCK_HEAD)
        return FALSE;
    return TRUE;
}

// Decide whether move having an additional effect for .
static bool32 AI_IsMoveEffectInPlus(u32 battlerAtk, u32 battlerDef, u32 move, s32 noOfHitsToKo)
{
    u32 i;
    u32 abilityDef = gAiLogicData->abilities[battlerDef];
    u32 abilityAtk = gAiLogicData->abilities[battlerAtk];

    switch (GetMoveEffect(move))
    {
    case EFFECT_HIT_ESCAPE:
        if (CountUsablePartyMons(battlerAtk) != 0 && ShouldPivot(battlerAtk, battlerDef, abilityDef, move, gAiThinkingStruct->movesetIndex))
            return TRUE;
        break;
    case EFFECT_FELL_STINGER:
        if (BattlerStatCanRise(battlerAtk, abilityAtk, STAT_ATK) && noOfHitsToKo == 1)
            return TRUE;
        break;
    case EFFECT_PURSUIT:
        if(noOfHitsToKo == 1)
            return TRUE;
        break;
    default:
        break;
    }

    // check ADDITIONAL_EFFECTS
    u32 additionalEffectCount = GetMoveAdditionalEffectCount(move);
    for (i = 0; i < additionalEffectCount; i++)
    {
        const struct AdditionalEffect *additionalEffect = GetMoveAdditionalEffectById(move, i);
        // Consider move effects that target self
        if (additionalEffect->self)
        {
            switch (additionalEffect->moveEffect)
            {
                case MOVE_EFFECT_ATK_PLUS_1:
                case MOVE_EFFECT_ATK_PLUS_2:
                    if (BattlerStatCanRise(battlerAtk, abilityAtk, STAT_ATK))
                        return TRUE;
                    break;
                case MOVE_EFFECT_DEF_PLUS_1:
                case MOVE_EFFECT_DEF_PLUS_2:
                    if (BattlerStatCanRise(battlerAtk, abilityAtk, STAT_DEF))
                        return TRUE;
                    break;
                case MOVE_EFFECT_SPD_PLUS_1:
                case MOVE_EFFECT_SPD_PLUS_2:
                    if (BattlerStatCanRise(battlerAtk, abilityAtk, STAT_SPEED))
                        return TRUE;
                    break;
                case MOVE_EFFECT_SP_ATK_PLUS_1:
                case MOVE_EFFECT_SP_ATK_PLUS_2:
                    if (BattlerStatCanRise(battlerAtk, abilityAtk, STAT_SPATK))
                        return TRUE;
                    break;
                case MOVE_EFFECT_EVS_PLUS_1:
                case MOVE_EFFECT_EVS_PLUS_2:
                    if (BattlerStatCanRise(battlerAtk, abilityAtk, STAT_EVASION))
                        return TRUE;
                    break;
                case MOVE_EFFECT_ACC_PLUS_1:
                case MOVE_EFFECT_ACC_PLUS_2:
                    if (BattlerStatCanRise(battlerAtk, abilityAtk, STAT_ACC))
                        return TRUE;
                    break;
                case MOVE_EFFECT_ALL_STATS_UP:
                    for (i = STAT_ATK; i <= NUM_STATS; i++)
                    {
                        if (BattlerStatCanRise(battlerAtk, abilityAtk, i))
                            return TRUE;
                    }
                    break;
            }
        }
        else // consider move effects that hinder the target
        {
            switch (additionalEffect->moveEffect)
            {
                case MOVE_EFFECT_POISON:
                case MOVE_EFFECT_TOXIC:
                    if (AI_CanPoison(battlerAtk, battlerDef, abilityDef, move, MOVE_NONE))
                        return TRUE;
                    break;
                case MOVE_EFFECT_BURN:
                    if (AI_CanBurn(battlerAtk, battlerDef, abilityDef, BATTLE_PARTNER(battlerAtk), move, MOVE_NONE))
                        return TRUE;
                    break;
                case MOVE_EFFECT_FREEZE_OR_FROSTBITE:
                    if (CanBeFrozen(battlerAtk, battlerDef, abilityDef))
                        return TRUE;
                    break;
                case MOVE_EFFECT_PARALYSIS:
                    if (AI_CanParalyze(battlerAtk, battlerDef, abilityDef, move, MOVE_NONE))
                        return TRUE;
                    break;
                case MOVE_EFFECT_CONFUSION:
                    if (AI_CanConfuse(battlerAtk, battlerDef, abilityDef, BATTLE_PARTNER(battlerAtk), move, MOVE_NONE))
                        return TRUE;
                    break;
                case MOVE_EFFECT_FLINCH:
                    if (ShouldTryToFlinch(battlerAtk, battlerDef, abilityAtk, abilityDef, move))
                        return TRUE;
                    break;
                case MOVE_EFFECT_ATK_MINUS_1:
                    if (ShouldLowerStat(battlerAtk, battlerDef, abilityDef, STAT_ATK + (additionalEffect->moveEffect - MOVE_EFFECT_ATK_MINUS_1)) && noOfHitsToKo != 1)
                        return TRUE;
                    break;
                case MOVE_EFFECT_DEF_MINUS_1:
                case MOVE_EFFECT_DEF_MINUS_2:
                    if (ShouldLowerDefense(battlerAtk, battlerDef, abilityDef) && noOfHitsToKo != 1)
                        return TRUE;
                    break;
                case MOVE_EFFECT_SPD_MINUS_1:
                case MOVE_EFFECT_SPD_MINUS_2:
                    if (ShouldLowerSpeed(battlerAtk, battlerDef, abilityDef) && noOfHitsToKo != 1)
                        return TRUE;
                    break;
                case MOVE_EFFECT_SP_ATK_MINUS_1:
                case MOVE_EFFECT_SP_ATK_MINUS_2:
                    if (ShouldLowerSpAtk(battlerAtk, battlerDef, abilityDef) && noOfHitsToKo != 1)
                        return TRUE;
                    break;                
                case MOVE_EFFECT_SP_DEF_MINUS_1:
                case MOVE_EFFECT_SP_DEF_MINUS_2:
                    if (ShouldLowerSpDef(battlerAtk, battlerDef, abilityDef) && noOfHitsToKo != 1)
                        return TRUE;
                    break;                      
                case MOVE_EFFECT_ACC_MINUS_1:
                case MOVE_EFFECT_ACC_MINUS_2:
                    if (ShouldLowerAccuracy(battlerAtk, battlerDef, abilityDef) && noOfHitsToKo != 1)
                        return TRUE;
                    break;  
                case MOVE_EFFECT_EVS_MINUS_1:
                case MOVE_EFFECT_EVS_MINUS_2:
                    if (ShouldLowerStat(battlerAtk, battlerDef, abilityDef, STAT_ATK + (additionalEffect->moveEffect - MOVE_EFFECT_ATK_MINUS_2)) && noOfHitsToKo != 1)
                        return TRUE;
                    // if (ShouldLowerEvasion(battlerAtk, battlerDef, abilityDef) && noOfHitsToKo != 1)
                    //     return TRUE;    
                    break;                
            }
        }
    }

    return FALSE;
}

static bool32 AI_IsMoveEffectInMinus(u32 battlerAtk, u32 battlerDef, u32 move, s32 noOfHitsToKo)
{
    u32 abilityAtk = gAiLogicData->abilities[battlerAtk];
    u32 abilityDef = gAiLogicData->abilities[battlerDef];
    u8 i;

    switch (GetMoveEffect(move))
    {
    case EFFECT_MAX_HP_50_RECOIL:
    case EFFECT_MIND_BLOWN:
    case EFFECT_EXPLOSION:
    case EFFECT_FINAL_GAMBIT:
        return TRUE;
    case EFFECT_RECOIL:
    case EFFECT_RECOIL_IF_MISS:
        if (AI_IsDamagedByRecoil(battlerAtk))
            return TRUE;
        break;
    default:
    {
        u32 additionalEffectCount = GetMoveAdditionalEffectCount(move);
        for (i = 0; i < additionalEffectCount; i++)
        {
            const struct AdditionalEffect *additionalEffect = GetMoveAdditionalEffectById(move, i);
            switch (additionalEffect->moveEffect)
            {
                case MOVE_EFFECT_ATK_MINUS_1:
                case MOVE_EFFECT_DEF_MINUS_1:
                case MOVE_EFFECT_SPD_MINUS_1:
                case MOVE_EFFECT_SP_ATK_MINUS_1:
                case MOVE_EFFECT_SP_DEF_MINUS_1:
                case MOVE_EFFECT_EVS_MINUS_1:
                case MOVE_EFFECT_ACC_MINUS_1:
                case MOVE_EFFECT_ATK_MINUS_2:
                case MOVE_EFFECT_DEF_MINUS_2:
                case MOVE_EFFECT_SPD_MINUS_2:
                case MOVE_EFFECT_SP_ATK_MINUS_2:
                case MOVE_EFFECT_SP_DEF_MINUS_2:
                case MOVE_EFFECT_EVS_MINUS_2:
                case MOVE_EFFECT_ACC_MINUS_2:
                case MOVE_EFFECT_V_CREATE:
                case MOVE_EFFECT_ATK_DEF_DOWN:
                case MOVE_EFFECT_DEF_SPDEF_DOWN:
                    if ((additionalEffect->self && abilityAtk != ABILITY_CONTRARY)
                        || (noOfHitsToKo != 1 && abilityDef == ABILITY_CONTRARY && !DoesBattlerIgnoreAbilityChecks(battlerAtk, abilityAtk, move)))
                        return TRUE;
                    break;
                case MOVE_EFFECT_RECHARGE:
                    return additionalEffect->self;
                case MOVE_EFFECT_ATK_PLUS_1:
                case MOVE_EFFECT_DEF_PLUS_1:
                case MOVE_EFFECT_SPD_PLUS_1:
                case MOVE_EFFECT_SP_ATK_PLUS_1:
                case MOVE_EFFECT_SP_DEF_PLUS_1:
                case MOVE_EFFECT_EVS_PLUS_1:
                case MOVE_EFFECT_ACC_PLUS_1:
                case MOVE_EFFECT_ATK_PLUS_2:
                case MOVE_EFFECT_DEF_PLUS_2:
                case MOVE_EFFECT_SPD_PLUS_2:
                case MOVE_EFFECT_SP_ATK_PLUS_2:
                case MOVE_EFFECT_SP_DEF_PLUS_2:
                case MOVE_EFFECT_EVS_PLUS_2:
                case MOVE_EFFECT_ACC_PLUS_2:
                case MOVE_EFFECT_ALL_STATS_UP:
                    if ((additionalEffect->self && abilityAtk == ABILITY_CONTRARY))
                        //Not sure why the below is here
                        // || (noOfHitsToKo != 1 && !(abilityDef == ABILITY_CONTRARY && !DoesBattlerIgnoreAbilityChecks(battlerAtk, abilityAtk, move))))
                        return TRUE;
                    break;
            }
        }
        break;
    }
    }
    return FALSE;
}

// Checks if one of the moves has side effects or perks, assuming equal dmg or equal no of hits to KO
s32 AI_WhichMoveBetter(u32 move1, u32 move2, u32 battlerAtk, u32 battlerDef, s32 noOfHitsToKo)
{
    bool32 effect1, effect2;
    u32 defAbility = gAiLogicData->abilities[battlerDef];
    u32 atkAbility = gAiLogicData->abilities[battlerAtk];

    // Check if physical moves hurt.
    if (gAiLogicData->holdEffects[battlerAtk] != HOLD_EFFECT_PROTECTIVE_PADS && atkAbility != ABILITY_LONG_REACH
        && (gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_ROCKY_HELMET
        || defAbility == ABILITY_IRON_BARBS || defAbility == ABILITY_ROUGH_SKIN))
    {
        bool32 moveContact1 = MoveMakesContact(move1);
        bool32 moveContact2 = MoveMakesContact(move2);
        if (moveContact1 && !moveContact2)
            return -1;
        if (moveContact2 && !moveContact1)
            return 1;
    }

    // Check additional effects.
    effect1 = AI_IsMoveEffectInMinus(battlerAtk, battlerDef, move1, noOfHitsToKo);
    effect2 = AI_IsMoveEffectInMinus(battlerAtk, battlerDef, move2, noOfHitsToKo);
    if (effect2 && !effect1)
        return 1;
    if (effect1 && !effect2)
        return -1;

    effect1 = AI_IsMoveEffectInPlus(battlerAtk, battlerDef, move1, noOfHitsToKo);
    effect2 = AI_IsMoveEffectInPlus(battlerAtk, battlerDef, move2, noOfHitsToKo);
    if (effect2 && !effect1)
        return -1;
    if (effect1 && !effect2)
        return 1;

    return 0;
}

u32 GetNoOfHitsToKO(u32 dmg, s32 hp)
{
    if (dmg == 0)
        return 0;
    return hp / (dmg + 1) + 1;
}

u32 GetNoOfHitsToKOBattlerDmg(u32 dmg, u32 battlerDef)
{
    return GetNoOfHitsToKO(dmg, gBattleMons[battlerDef].hp);
}

u32 GetNoOfHitsToKOBattler(u32 battlerAtk, u32 battlerDef, u32 moveIndex, enum DamageCalcContext calcContext)
{
    return GetNoOfHitsToKOBattlerDmg(AI_GetDamage(battlerAtk, battlerDef, moveIndex, calcContext, gAiLogicData), battlerDef);
}

u32 GetCurrDamageHpPercent(u32 battlerAtk, u32 battlerDef, enum DamageCalcContext calcContext)
{
    int bestDmg = AI_GetDamage(battlerAtk, battlerDef, gAiThinkingStruct->movesetIndex, calcContext, gAiLogicData);

    return (bestDmg * 100) / gBattleMons[battlerDef].maxHP;
}

uq4_12_t AI_GetMoveEffectiveness(u32 move, u32 battlerAtk, u32 battlerDef)
{
    uq4_12_t typeEffectiveness;
    u32 moveType;

    SaveBattlerData(battlerAtk);
    SaveBattlerData(battlerDef);

    SetBattlerData(battlerAtk);
    SetBattlerData(battlerDef);

    gBattleStruct->dynamicMoveType = 0;
    SetTypeBeforeUsingMove(move, battlerAtk);
    moveType = GetBattleMoveType(move);
    //TODO: Have custom type effectiveness calculations for Proactive Color Change

    typeEffectiveness = CalcTypeEffectivenessMultiplier(move, moveType, battlerAtk, battlerDef, gAiLogicData->abilities[battlerDef], FALSE);

    RestoreBattlerData(battlerAtk);
    RestoreBattlerData(battlerDef);

    return typeEffectiveness;
}

/* Checks to see if AI will move ahead of another battler
 * The function uses a stripped down version of the checks from GetWhichBattlerFasterArgs
 * Output:
    * AI_IS_FASTER: is user(ai) faster
    * AI_IS_SLOWER: is target faster
*/
s32 AI_WhoStrikesFirst(u32 battlerAI, u32 battler, u32 moveConsidered)
{
    u32 speedBattlerAI, speedBattler;
    enum ItemHoldEffect holdEffectAI = gAiLogicData->holdEffects[battlerAI];
    enum ItemHoldEffect holdEffectPlayer = gAiLogicData->holdEffects[battler];
    u32 abilityAI = gAiLogicData->abilities[battlerAI];
    u32 abilityPlayer = gAiLogicData->abilities[battler];

    u32 predictedMove = GetIncomingMove(battlerAI, battler, gAiLogicData);

    s8 aiPriority = GetBattleMovePriority(battlerAI, abilityAI, moveConsidered);
    s8 playerPriority = GetBattleMovePriority(battler, abilityPlayer, predictedMove);

    if (aiPriority > playerPriority)
        return AI_IS_FASTER;
    else if (aiPriority < playerPriority)
        return AI_IS_SLOWER;

    speedBattlerAI = GetBattlerTotalSpeedStatArgs(battlerAI, abilityAI, holdEffectAI);
    speedBattler   = GetBattlerTotalSpeedStatArgs(battler, abilityPlayer, holdEffectPlayer);

    if (holdEffectAI == HOLD_EFFECT_LAGGING_TAIL && holdEffectPlayer != HOLD_EFFECT_LAGGING_TAIL)
        return AI_IS_SLOWER;
    else if (holdEffectAI != HOLD_EFFECT_LAGGING_TAIL && holdEffectPlayer == HOLD_EFFECT_LAGGING_TAIL)
        return AI_IS_FASTER;

    if (abilityAI == ABILITY_STALL && abilityPlayer != ABILITY_STALL)
        return AI_IS_SLOWER;
    else if (abilityAI != ABILITY_STALL && abilityPlayer == ABILITY_STALL)
        return AI_IS_FASTER;

    if (speedBattlerAI > speedBattler)
    {
        if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM)
            return AI_IS_SLOWER;
        else
            return AI_IS_FASTER;
    }
    else if (speedBattlerAI == speedBattler)
    {
        return AI_IS_FASTER;
    }
    else
    {
        if (gFieldStatuses & STATUS_FIELD_TRICK_ROOM)
            return AI_IS_FASTER;
        else
            return AI_IS_SLOWER;
    }

    return AI_IS_SLOWER;
}

static bool32 CanEndureHit(u32 battler, u32 battlerTarget, u32 move)
{
    enum BattleMoveEffects effect = GetMoveEffect(move);
    if (!AI_BattlerAtMaxHp(battlerTarget) || effect == EFFECT_MULTI_HIT)
        return FALSE;
    if (GetMoveStrikeCount(move) > 1 && !(effect == EFFECT_DRAGON_DARTS && IsValidDoubleBattle(battlerTarget)))
        return FALSE;
    if (gAiLogicData->holdEffects[battlerTarget] == HOLD_EFFECT_FOCUS_SASH)
        return TRUE;

    if (!DoesBattlerIgnoreAbilityChecks(battler, gAiLogicData->abilities[battler], move))
    {
        if (B_STURDY >= GEN_5 && gAiLogicData->abilities[battlerTarget] == ABILITY_STURDY)
            return TRUE;
        if (gBattleMons[battlerTarget].species == SPECIES_MIMIKYU_DISGUISED)
            return TRUE;
    }

    return FALSE;
}

// Check if target has means to faint ai mon.
bool32 CanTargetFaintAi(u32 battlerDef, u32 battlerAtk)
{
    struct AiLogicData *aiData = gAiLogicData;
    s32 moveIndex;
    u16 *moves = GetMovesArray(battlerDef);
    u32 moveLimitations = aiData->moveLimitations[battlerDef];

    for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (IsMoveUnusable(moveIndex, moves[moveIndex], moveLimitations))
            continue;

        if (AI_GetDamage(battlerDef, battlerAtk, moveIndex, AI_DEFENDING, aiData) >= gBattleMons[battlerAtk].hp
            && !CanEndureHit(battlerDef, battlerAtk, moves[moveIndex]))
            return TRUE;
    }

    return FALSE;
}


static s8 GetStatStageDifference(s8 statDelta, s8 monStatStage){
    s8 resultantStat = monStatStage + statDelta;
    if (resultantStat > MAX_STAT_STAGE){
        statDelta -= (resultantStat - MAX_STAT_STAGE);
    }else if (resultantStat < MIN_STAT_STAGE){
        statDelta += (MIN_STAT_STAGE - resultantStat);
    }
    return statDelta;
}

//Applies simulated that changes that SHOULD be later reversed by ReverseSimulatedStatChanges
struct StatsDelta ApplySimulatedStatChanges(u32 battlerAtk, u32 battlerDef, struct StatsDelta requestedStatChanges){
    struct StatsDelta workingStatChanges = requestedStatChanges;
    u32 targetAbility = GetBattlerAbility(battlerDef);
    u32 mulValue = 1;

    if (targetAbility == ABILITY_SIMPLE && !DoesBattlerIgnoreAbilityChecks(battlerAtk, GetBattlerAbility(battlerAtk), MOVE_IRRELEVANT)){
        mulValue = 2;
    }

    //Modifying Working Stat Changes so that it can be passed for reversal sake

    workingStatChanges.atk      = GetStatStageDifference(workingStatChanges.atk * mulValue, gBattleMons[battlerDef].statStages[STAT_ATK]);
    gBattleMons[battlerDef].statStages[STAT_ATK] += workingStatChanges.atk;

    workingStatChanges.def      = GetStatStageDifference(workingStatChanges.def * mulValue, gBattleMons[battlerDef].statStages[STAT_DEF]);
    gBattleMons[battlerDef].statStages[STAT_DEF] += workingStatChanges.def;

    workingStatChanges.speed      = GetStatStageDifference(workingStatChanges.speed * mulValue, gBattleMons[battlerDef].statStages[STAT_SPEED]);
    gBattleMons[battlerDef].statStages[STAT_SPEED] += workingStatChanges.speed;    

    workingStatChanges.spAtk      = GetStatStageDifference(workingStatChanges.spAtk * mulValue, gBattleMons[battlerDef].statStages[STAT_SPATK]);
    gBattleMons[battlerDef].statStages[STAT_SPATK] += workingStatChanges.spAtk;   

    workingStatChanges.spDef      = GetStatStageDifference(workingStatChanges.spDef * mulValue, gBattleMons[battlerDef].statStages[STAT_SPDEF]);
    gBattleMons[battlerDef].statStages[STAT_SPDEF] += workingStatChanges.spDef;

    workingStatChanges.accuracy      = GetStatStageDifference(workingStatChanges.accuracy * mulValue, gBattleMons[battlerDef].statStages[STAT_ACC]);
    gBattleMons[battlerDef].statStages[STAT_ACC] += workingStatChanges.accuracy; 

    workingStatChanges.evasion      = GetStatStageDifference(workingStatChanges.evasion * mulValue, gBattleMons[battlerDef].statStages[STAT_EVASION]);
    gBattleMons[battlerDef].statStages[STAT_EVASION] += workingStatChanges.evasion;    

    return workingStatChanges;
} 

//This function does not do any checks, since the simulation function has already checked that the stat changes are valid.
//This just aims to restore the stats to what they were beforehand
void ReverseSimulatedStatChanges(u32 battler, struct StatsDelta statChangesMade){
    gBattleMons[battler].statStages[STAT_ATK] -= statChangesMade.atk;

    gBattleMons[battler].statStages[STAT_DEF] -= statChangesMade.def;

    gBattleMons[battler].statStages[STAT_SPATK] -= statChangesMade.spAtk;   

    gBattleMons[battler].statStages[STAT_SPDEF] -= statChangesMade.spDef;

    gBattleMons[battler].statStages[STAT_SPEED] -= statChangesMade.speed;    

    gBattleMons[battler].statStages[STAT_ACC] -= statChangesMade.accuracy; 

    gBattleMons[battler].statStages[STAT_EVASION] -= statChangesMade.evasion;    

}

u32 NoOfHitsForTargetToFaintAI(u32 battlerDef, u32 battlerAtk)
{
    u32 i;
    u32 currNumberOfHits;
    u32 leastNumberOfHits = UNKNOWN_NO_OF_HITS;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        currNumberOfHits = GetNoOfHitsToKOBattler(battlerDef, battlerAtk, i, AI_DEFENDING);
        // DebugPrintf("For move %d, the number of hits to KO is %d", i, currNumberOfHits);
        if (currNumberOfHits != 0)
        {
            if (currNumberOfHits < leastNumberOfHits)
                leastNumberOfHits = currNumberOfHits;
        }
    }
    return leastNumberOfHits;
}

u32 GetBestDmgMoveFromBattler(u32 battlerAtk, u32 battlerDef, enum DamageCalcContext calcContext)
{
    struct AiLogicData *aiData = gAiLogicData;
    u32 moveIndex;
    u32 move = 0;
    u32 bestDmg = 0;
    u16 *moves = GetMovesArray(battlerAtk);
    u32 moveLimitations = aiData->moveLimitations[battlerAtk];

    for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (IsMoveUnusable(moveIndex, moves[moveIndex], moveLimitations))
            continue;

        if (bestDmg < AI_GetDamage(battlerAtk, battlerDef, moveIndex, calcContext, aiData))
        {
            bestDmg = AI_GetDamage(battlerAtk, battlerDef, moveIndex, calcContext, aiData);
            move = moves[moveIndex];
        }
    }
    return move;
}

u32 GetBestDmgFromBattler(u32 battler, u32 battlerTarget, enum DamageCalcContext calcContext)
{
    struct AiLogicData *aiData = gAiLogicData;
    u32 moveIndex;
    u32 bestDmg = 0;
    u16 *moves = GetMovesArray(battler);
    u32 moveLimitations = aiData->moveLimitations[battler];


    for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (IsMoveUnusable(moveIndex, moves[moveIndex], moveLimitations))
            continue;

        u32 damage = AI_GetDamage(battler, battlerTarget, moveIndex, calcContext, aiData);
        if (bestDmg < damage)
            bestDmg = damage;

    }

    return bestDmg;
}

//This is a damage calculation that involves recomputing damage, to take into account mid-battle stat projections.
s32 GetBestRecomputedDmgFromBattler(u32 battler, u32 battlerTarget){
    u16 battlerMoves[MAX_MON_MOVES];
    s32 bestDmg = 0;
    u32 i;
    uq4_12_t effectiveness;

    u32 weather = AI_GetWeather();
    GetMovesArrayWithHiddenSTAB(battler, battlerMoves);
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        s32 dmgCalculated = 0;
        u32 battlerMove = battlerMoves[i];
        if (battlerMove != MOVE_NONE && battlerMove != MOVE_UNAVAILABLE && !IsBattleMoveStatus(battlerMove))
        {
            dmgCalculated = AI_CalcDamage(battlerMove, battler, battlerTarget, &effectiveness, FALSE, weather).median;
            if (dmgCalculated > bestDmg)
            {
                bestDmg = dmgCalculated;
            }
        }
    }
    return bestDmg;
}


// Check if AI mon has the means to faint the target with any of its moves.
// If numHits > 1, check if the target will be KO'ed by that number of hits (ignoring healing effects)
bool32 CanAIFaintTarget(u32 battlerAtk, u32 battlerDef, u32 numHits)
{
    struct AiLogicData *aiData = gAiLogicData;
    s32 moveIndex, dmg;
    u16 *moves = gBattleMons[battlerAtk].moves;
    u32 moveLimitations = aiData->moveLimitations[battlerAtk];

    for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (IsMoveUnusable(moveIndex, moves[moveIndex], moveLimitations))
            continue;

        dmg = AI_GetDamage(battlerAtk, battlerDef, moveIndex, AI_ATTACKING, aiData);

        if (numHits)
            dmg *= numHits;

        if (gBattleMons[battlerDef].hp <= dmg)
        {
            if (numHits > 1)
                return TRUE;

            if (!CanEndureHit(battlerAtk, battlerDef, moves[moveIndex]))
                return TRUE;
        }
    }

    return FALSE;
}

bool32 CanTargetMoveFaintAi(u32 move, u32 battlerDef, u32 battlerAtk, u32 nHits)
{
    u32 indexSlot = GetMoveSlot(GetMovesArray(battlerDef), move);
    if (indexSlot < MAX_MON_MOVES)
    {
        if (GetNoOfHitsToKO(AI_GetDamage(battlerDef, battlerAtk, indexSlot, AI_DEFENDING, gAiLogicData), gBattleMons[battlerAtk].hp) <= nHits)
            return TRUE;
    }
    return FALSE;
}

// Check if target has means to faint ai mon after modding hp/dmg
bool32 CanTargetFaintAiWithMod(u32 battlerDef, u32 battlerAtk, s32 hpMod, s32 dmgMod)
{
    struct AiLogicData *aiData = gAiLogicData;
    u32 moveIndex;
    s32 dmg;
    u16 *moves = GetMovesArray(battlerDef);
    u32 hpCheck = gBattleMons[battlerAtk].hp + hpMod;
    u32 moveLimitations = aiData->moveLimitations[battlerAtk];

    if (hpCheck > gBattleMons[battlerAtk].maxHP)
        hpCheck = gBattleMons[battlerAtk].maxHP;

    for (moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (IsMoveUnusable(moveIndex, moves[moveIndex], moveLimitations))
            continue;

        dmg = AI_GetDamage(battlerDef, battlerAtk, moveIndex, AI_DEFENDING, aiData);
        
        if (dmgMod)
            dmg *= dmgMod;

        if (dmg >= hpCheck)
            return TRUE;
    }

    return FALSE;
}

bool32 AI_IsAbilityOnSide(u32 battlerId, u32 ability)
{
    if (IsBattlerAlive(battlerId) && gAiLogicData->abilities[battlerId] == ability)
        return TRUE;
    else if (IsBattlerAlive(BATTLE_PARTNER(battlerId)) && gAiLogicData->abilities[BATTLE_PARTNER(battlerId)] == ability)
        return TRUE;
    else
        return FALSE;
}

u32 AI_GetBattlerAbility(u32 battler)
{
    if (gAbilitiesInfo[gBattleMons[battler].ability].cantBeSuppressed)
        return gBattleMons[battler].ability;

    if (gStatuses3[battler] & STATUS3_GASTRO_ACID)
        return ABILITY_NONE;

    if (IsNeutralizingGasOnField()
     && gBattleMons[battler].ability != ABILITY_NEUTRALIZING_GAS
     && GetBattlerHoldEffectIgnoreAbility(battler, TRUE) != HOLD_EFFECT_ABILITY_SHIELD)
        return ABILITY_NONE;

    return gBattleMons[battler].ability;
}

// does NOT include ability suppression checks
s32 AI_DecideKnownAbilityForTurn(u32 battlerId)
{
    u32 validAbilities[NUM_ABILITY_SLOTS];
    u8 i, numValidAbilities = 0;
    u32 knownAbility = AI_GetBattlerAbility(battlerId);
    u32 indexAbility;
    u32 abilityAiRatings[NUM_ABILITY_SLOTS] = {0};

    // We've had ability overwritten by e.g. Worry Seed. It is not part of gAiPartyData in case of switching
    if (gDisableStructs[battlerId].overwrittenAbility)
        return gDisableStructs[battlerId].overwrittenAbility;

    // The AI knows its own ability.
    if (IsAiBattlerAware(battlerId))
        return knownAbility;

    // Check neutralizing gas, gastro acid
    if (knownAbility == ABILITY_NONE)
        return knownAbility;

    if (gAiPartyData->mons[GetBattlerSide(battlerId)][gBattlerPartyIndexes[battlerId]].ability != ABILITY_NONE)
        return gAiPartyData->mons[GetBattlerSide(battlerId)][gBattlerPartyIndexes[battlerId]].ability;

    // Abilities that prevent fleeing - treat as always known
    if (knownAbility == ABILITY_SHADOW_TAG || knownAbility == ABILITY_MAGNET_PULL || knownAbility == ABILITY_ARENA_TRAP)
        return knownAbility;

    for (i = 0; i < NUM_ABILITY_SLOTS; i++)
    {
        indexAbility = gSpeciesInfo[gBattleMons[battlerId].species].abilities[i];
        if (indexAbility != ABILITY_NONE)
        {
            abilityAiRatings[numValidAbilities] = gAbilitiesInfo[indexAbility].aiRating;
            validAbilities[numValidAbilities++] = indexAbility;
        }
    }

    if (numValidAbilities > 0 && IsAiBattlerPredictingAbility(battlerId))
        return validAbilities[RandomWeighted(RNG_AI_PREDICT_ABILITY, abilityAiRatings[0], abilityAiRatings[1], abilityAiRatings[2])];

    if (numValidAbilities > 0)
        return validAbilities[RandomUniform(RNG_AI_ABILITY, 0, numValidAbilities - 1)];

    return ABILITY_NONE; // Unknown.
}

enum ItemHoldEffect AI_DecideHoldEffectForTurn(u32 battlerId)
{
    enum ItemHoldEffect holdEffect;

    if (!IsAiBattlerAware(battlerId))
        holdEffect = gAiPartyData->mons[GetBattlerSide(battlerId)][gBattlerPartyIndexes[battlerId]].heldEffect;
    else
        holdEffect = GetBattlerHoldEffect(battlerId, FALSE);

    if (gAiThinkingStruct->aiFlags[battlerId] & AI_FLAG_NEGATE_UNAWARE)
        return holdEffect;

    if (gStatuses3[battlerId] & STATUS3_EMBARGO)
        return HOLD_EFFECT_NONE;
    if (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM)
        return HOLD_EFFECT_NONE;
    if (gAiLogicData->abilities[battlerId] == ABILITY_KLUTZ && !(gStatuses3[battlerId] & STATUS3_GASTRO_ACID))
        return HOLD_EFFECT_NONE;

    return holdEffect;
}

bool32 DoesBattlerIgnoreAbilityChecks(u32 battlerAtk, u32 atkAbility, u32 move)
{
    if (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_NEGATE_UNAWARE)
        return FALSE;   // AI handicap flag: doesn't understand ability suppression concept

    if (IsMoldBreakerTypeAbility(battlerAtk, atkAbility) || MoveIgnoresTargetAbility(move))
        return TRUE;

    return FALSE;
}

static inline bool32 AI_WeatherHasEffect(void)
{
    if (gAiThinkingStruct->aiFlags[B_POSITION_OPPONENT_LEFT] & AI_FLAG_NEGATE_UNAWARE
     || gAiThinkingStruct->aiFlags[B_POSITION_OPPONENT_RIGHT] & AI_FLAG_NEGATE_UNAWARE)
        return TRUE;   // AI doesn't understand weather supression (handicap)

    return gAiLogicData->weatherHasEffect;  // weather damping abilities are announced
}

u32 AI_GetWeather(void)
{
    if (gBattleWeather == B_WEATHER_NONE)
        return B_WEATHER_NONE;
    if (!AI_WeatherHasEffect())
        return B_WEATHER_NONE;
    return gBattleWeather;
}

enum WeatherState IsWeatherActive(u32 flags)
{
    enum WeatherState state = WEATHER_INACTIVE;

    if (gBattleWeather & flags)
        state = WEATHER_ACTIVE;
    else
        state = WEATHER_INACTIVE;

    if (!AI_WeatherHasEffect())
    {
        if (state == WEATHER_ACTIVE)
            state = WEATHER_ACTIVE_BUT_BLOCKED;
        else
            state = WEATHER_INACTIVE_AND_BLOCKED;
    }

    return state;
}

bool32 IsAromaVeilProtectedEffect(enum BattleMoveEffects moveEffect)
{
    switch (moveEffect)
    {
    case EFFECT_DISABLE:
    case EFFECT_ATTRACT:
    case EFFECT_ENCORE:
    case EFFECT_TORMENT:
    case EFFECT_TAUNT:
    case EFFECT_HEAL_BLOCK:
        return TRUE;
    default:
        return FALSE;
    }
}

bool32 IsNonVolatileStatusMove(u32 move)
{
    return GetMoveNonVolatileStatus(move) != MOVE_EFFECT_NONE;
}

bool32 IsConfusionMoveEffect(enum BattleMoveEffects moveEffect)
{
    switch (moveEffect)
    {
    case EFFECT_CONFUSE:
    case EFFECT_SWAGGER:
    case EFFECT_FLATTER:
        return TRUE;
    default:
        return FALSE;
    }
}

bool32 IsHazardMove(u32 move)
{
    // Hazard setting moves like Stealth Rock, Spikes, etc.
    u32 i, moveEffect = GetMoveEffect(move);
    switch (moveEffect)
    {
    case EFFECT_SPIKES:
    case EFFECT_TOXIC_SPIKES:
    case EFFECT_STICKY_WEB:
    case EFFECT_STEALTH_ROCK:
        return TRUE;
    }

    u32 additionalEffectCount = GetMoveAdditionalEffectCount(move);
    for (i = 0; i < additionalEffectCount; i++)
    {
        const struct AdditionalEffect *additionalEffect = GetMoveAdditionalEffectById(move, i);
        switch (additionalEffect->moveEffect)
        {
        case MOVE_EFFECT_STEELSURGE:
            return TRUE;
        }
    }
    return FALSE;
}

bool32 IsHazardClearingMove(u32 move)
{
    // Hazard clearing effects like Rapid Spin, Tidy Up, etc.
    u32 i, moveEffect = GetMoveEffect(move);
    switch (moveEffect)
    {
    case EFFECT_RAPID_SPIN:
    case EFFECT_TIDY_UP:
        return TRUE;
    case EFFECT_DEFOG:
        if (B_DEFOG_EFFECT_CLEARING >= GEN_6)
            return TRUE;
        break;
    }

    u32 additionalEffectCount = GetMoveAdditionalEffectCount(move);
    for (i = 0; i < additionalEffectCount; i++)
    {
        const struct AdditionalEffect *additionalEffect = GetMoveAdditionalEffectById(move, i);
        switch (additionalEffect->moveEffect)
        {
        case MOVE_EFFECT_DEFOG:
            return TRUE;
        }
    }

    return FALSE;
}

bool32 IsAllyProtectingFromMove(u32 battlerAtk, u32 attackerMove, u32 allyMove)
{
    enum BattleMoveEffects effect = GetMoveEffect(allyMove);

    if (effect != EFFECT_PROTECT)
    {
        return FALSE;
    }
    else
    {
        enum ProtectMethod protectMethod = GetMoveProtectMethod(allyMove);

        if (protectMethod == PROTECT_QUICK_GUARD)
        {
            u32 priority = GetBattleMovePriority(battlerAtk, gAiLogicData->abilities[battlerAtk], attackerMove);
            return (priority > 0);
        }

        if (IsBattleMoveStatus(attackerMove))
        {
            switch (protectMethod)
            {
            case PROTECT_NORMAL:
            case PROTECT_CRAFTY_SHIELD:
            case PROTECT_MAX_GUARD:
            case PROTECT_WIDE_GUARD:
                return TRUE;

            default:
                return FALSE;
            }
        }
        else
        {
            switch (protectMethod)
            {
            case PROTECT_CRAFTY_SHIELD:
                return FALSE;
            default:
                return TRUE;
            }
        }
    }
}

bool32 IsMoveRedirectionPrevented(u32 battlerAtk, u32 move, u32 atkAbility)
{
    if (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_NEGATE_UNAWARE)
        return FALSE;

    enum BattleMoveEffects effect = GetMoveEffect(move);
    if (effect == EFFECT_SKY_DROP
      || effect == EFFECT_SNIPE_SHOT
      || atkAbility == ABILITY_PROPELLER_TAIL
      || atkAbility == ABILITY_STALWART)
        return TRUE;
    return FALSE;
}

bool32 IsSemiInvulnerable(u32 battlerDef, u32 move)
{
    if (gStatuses3[battlerDef] & STATUS3_PHANTOM_FORCE)
        return TRUE;
    else if (gBattleStruct->battlerState[battlerDef].commandingDondozo)
        return TRUE;
    else if (!MoveDamagesAirborne(move) && gStatuses3[battlerDef] & STATUS3_ON_AIR)
        return TRUE;
    else if (!MoveDamagesUnderWater(move) && gStatuses3[battlerDef] & STATUS3_UNDERWATER)
        return TRUE;
    else if (!MoveDamagesUnderground(move) && gStatuses3[battlerDef] & STATUS3_UNDERGROUND)
        return TRUE;
    else
        return FALSE;
}

bool32 IsMoveEncouragedToHit(u32 battlerAtk, u32 battlerDef, u32 move)
{
    u32 weather;
    if (IsSemiInvulnerable(battlerDef, move))
        return FALSE;

    //TODO - anticipate protect move?

    // always hits
    if (gStatuses3[battlerDef] & STATUS3_ALWAYS_HITS || gDisableStructs[battlerDef].battlerWithSureHit == battlerAtk)
        return TRUE;

    if (gAiLogicData->abilities[battlerDef] == ABILITY_NO_GUARD || gAiLogicData->abilities[battlerAtk] == ABILITY_NO_GUARD)
        return TRUE;

    u32 nonVolatileStatus = GetMoveNonVolatileStatus(move);
    if (B_TOXIC_NEVER_MISS >= GEN_6
        && nonVolatileStatus == MOVE_EFFECT_TOXIC
        && IS_BATTLER_OF_TYPE(battlerAtk, TYPE_POISON))
        return TRUE;

    // discouraged from hitting
    weather = AI_GetWeather();
    if ((weather & B_WEATHER_SUN) && MoveHas50AccuracyInSun(move))
        return FALSE;

    //May need to add Frisk here
    if ((weather & B_WEATHER_RAIN) && MoveAlwaysHitsInRain(move))
        return TRUE;
    if ((weather & (B_WEATHER_HAIL | B_WEATHER_SNOW)) && MoveAlwaysHitsInHailSnow(move))
        return TRUE;
    if (B_MINIMIZE_DMG_ACC >= GEN_6 && (gStatuses3[battlerDef] & STATUS3_MINIMIZED) && MoveIncreasesPowerToMinimizedTargets(move))
        return TRUE;
    if (GetMoveAccuracy(move) == 0)
        return TRUE;

    return FALSE;
}

bool32 ShouldTryOHKO(u32 battlerAtk, u32 battlerDef, u32 atkAbility, u32 defAbility, u32 move)
{
    enum ItemHoldEffect holdEffect = gAiLogicData->holdEffects[battlerDef];
    u32 accuracy = gAiLogicData->moveAccuracy[battlerAtk][battlerDef][gAiThinkingStruct->movesetIndex];

    gPotentialItemEffectBattler = battlerDef;
    if (holdEffect == HOLD_EFFECT_FOCUS_BAND && (Random() % 100) < gAiLogicData->holdEffectParams[battlerDef])
        return FALSE;   //probabilistically speaking, focus band should activate so dont OHKO
    else if (holdEffect == HOLD_EFFECT_FOCUS_SASH && AI_BattlerAtMaxHp(battlerDef))
        return FALSE;

    if (!DoesBattlerIgnoreAbilityChecks(battlerAtk, atkAbility, move) && defAbility == ABILITY_STURDY)
        return FALSE;

    if ((((gStatuses3[battlerDef] & STATUS3_ALWAYS_HITS)
        && gDisableStructs[battlerDef].battlerWithSureHit == battlerAtk)
        || atkAbility == ABILITY_NO_GUARD || defAbility == ABILITY_NO_GUARD)
        && gBattleMons[battlerAtk].level >= gBattleMons[battlerDef].level)
    {
        return TRUE;
    }
    else    // test the odds
    {
        u32 odds = accuracy + (gBattleMons[battlerAtk].level - gBattleMons[battlerDef].level);
        if (B_SHEER_COLD_ACC >= GEN_7 && move == MOVE_SHEER_COLD && !IS_BATTLER_OF_TYPE(gBattlerAttacker, TYPE_ICE))
            odds -= 10;
        if (Random() % 100 + 1 < odds && gBattleMons[battlerAtk].level >= gBattleMons[battlerDef].level)
            return TRUE;
    }
    return FALSE;
}

bool32 ShouldSetSandstorm(u32 battler, u32 ability, enum ItemHoldEffect holdEffect)
{
    if (IsWeatherActive(B_WEATHER_SANDSTORM | B_WEATHER_PRIMAL_ANY) != WEATHER_INACTIVE)
        return FALSE;

    if (ability == ABILITY_SAND_VEIL
     || ability == ABILITY_SAND_RUSH
     || ability == ABILITY_SAND_FORCE
     || ability == ABILITY_OVERCOAT
     || ability == ABILITY_MAGIC_GUARD
     || holdEffect == HOLD_EFFECT_SAFETY_GOGGLES
     || IS_BATTLER_ANY_TYPE(battler, TYPE_ROCK, TYPE_GROUND, TYPE_STEEL)
     || HasMoveWithEffect(battler, EFFECT_SHORE_UP)
     || HasMoveWithEffect(battler, EFFECT_WEATHER_BALL))
    {
        return TRUE;
    }
    return FALSE;
}

bool32 ShouldSetHail(u32 battler, u32 ability, enum ItemHoldEffect holdEffect)
{
    if (IsWeatherActive(B_WEATHER_HAIL | B_WEATHER_SNOW | B_WEATHER_PRIMAL_ANY) != WEATHER_INACTIVE)
        return FALSE;

    if (ability == ABILITY_SNOW_CLOAK
     || ability == ABILITY_ICE_BODY
     || ability == ABILITY_FORECAST
     || ability == ABILITY_SLUSH_RUSH
     || ability == ABILITY_MAGIC_GUARD
     || ability == ABILITY_OVERCOAT
     || holdEffect == HOLD_EFFECT_SAFETY_GOGGLES
     || IS_BATTLER_OF_TYPE(battler, TYPE_ICE)
     || HasMoveWithFlag(battler, MoveAlwaysHitsInHailSnow)
     || HasMoveWithEffect(battler, EFFECT_AURORA_VEIL)
     || HasMoveWithEffect(battler, EFFECT_WEATHER_BALL))
    {
        return TRUE;
    }
    return FALSE;
}

bool32 ShouldSetRain(u32 battlerAtk, u32 atkAbility, enum ItemHoldEffect holdEffect)
{
    if (IsWeatherActive(B_WEATHER_RAIN | B_WEATHER_PRIMAL_ANY) != WEATHER_INACTIVE)
        return FALSE;

    if (holdEffect != HOLD_EFFECT_UTILITY_UMBRELLA
     && (atkAbility == ABILITY_SWIFT_SWIM
      || atkAbility == ABILITY_FORECAST
      || atkAbility == ABILITY_HYDRATION
      || atkAbility == ABILITY_RAIN_DISH
      || atkAbility == ABILITY_DRY_SKIN
      || HasMoveWithFlag(battlerAtk, MoveAlwaysHitsInRain)
      || HasMoveWithEffect(battlerAtk, EFFECT_WEATHER_BALL)
      || HasMoveWithType(battlerAtk, TYPE_WATER)))
    {
        return TRUE;
    }
    return FALSE;
}

bool32 ShouldSetSun(u32 battlerAtk, u32 atkAbility, enum ItemHoldEffect holdEffect)
{
    if (IsWeatherActive(B_WEATHER_SUN | B_WEATHER_PRIMAL_ANY) != WEATHER_INACTIVE)
        return FALSE;

    if (holdEffect != HOLD_EFFECT_UTILITY_UMBRELLA
     && (atkAbility == ABILITY_CHLOROPHYLL
      || atkAbility == ABILITY_FLOWER_GIFT
      || atkAbility == ABILITY_FORECAST
      || atkAbility == ABILITY_LEAF_GUARD
      || atkAbility == ABILITY_SOLAR_POWER
      || atkAbility == ABILITY_HARVEST
      || HasMoveWithEffect(battlerAtk, EFFECT_SOLAR_BEAM)
      || HasMoveWithEffect(battlerAtk, EFFECT_MORNING_SUN)
      || HasMoveWithEffect(battlerAtk, EFFECT_SYNTHESIS)
      || HasMoveWithEffect(battlerAtk, EFFECT_MOONLIGHT)
      || HasMoveWithEffect(battlerAtk, EFFECT_WEATHER_BALL)
      || HasMoveWithEffect(battlerAtk, EFFECT_GROWTH)
      || HasMoveWithType(battlerAtk, TYPE_FIRE)))
    {
        return TRUE;
    }
    return FALSE;
}

bool32 ShouldSetSnow(u32 battler, u32 ability, enum ItemHoldEffect holdEffect)
{
    if (IsWeatherActive(B_WEATHER_SNOW | B_WEATHER_HAIL | B_WEATHER_PRIMAL_ANY) != WEATHER_INACTIVE)
        return FALSE;

    if (ability == ABILITY_SNOW_CLOAK
     || ability == ABILITY_ICE_BODY
     || ability == ABILITY_FORECAST
     || ability == ABILITY_SLUSH_RUSH
     || IS_BATTLER_OF_TYPE(battler, TYPE_ICE)
     || HasMoveWithFlag(battler, MoveAlwaysHitsInHailSnow)
     || HasMoveWithEffect(battler, EFFECT_AURORA_VEIL)
     || HasMoveWithEffect(battler, EFFECT_WEATHER_BALL))
    {
        return TRUE;
    }
    return FALSE;
}

void ProtectChecks(u32 battlerAtk, u32 battlerDef, u32 move, u32 predictedMove, s32 *score)
{
    // TODO more sophisticated logic
    u32 uses = gDisableStructs[battlerAtk].protectUses;

    /*if (GetMoveResultFlags(predictedMove) & (MOVE_RESULT_NO_EFFECT | MOVE_RESULT_MISSED))
    {
        ADJUST_SCORE_PTR(-5);
        return;
    }*/

    if (uses == 0)
    {
        if (predictedMove != MOVE_NONE && predictedMove != 0xFFFF && !IsBattleMoveStatus(predictedMove))
            ADJUST_SCORE_PTR(DECENT_EFFECT);
        else if (Random() % 256 < 100)
            ADJUST_SCORE_PTR(WEAK_EFFECT);
    }
    else
    {
        if (IsDoubleBattle())
            ADJUST_SCORE_PTR(-(2 * min(uses, 3)));
        else
            ADJUST_SCORE_PTR(-(min(uses, 3)));
    }

    if (gBattleMons[battlerAtk].status1 & (STATUS1_PSN_ANY | STATUS1_BURN | STATUS1_FROSTBITE)
     || gBattleMons[battlerAtk].status2 & (STATUS2_CURSED | STATUS2_INFATUATION)
     || gStatuses3[battlerAtk] & (STATUS3_PERISH_SONG | STATUS3_LEECHSEED | STATUS3_YAWN))
    {
        ADJUST_SCORE_PTR(-1);
    }

    if (gBattleMons[battlerDef].status1 & STATUS1_TOXIC_POISON
      || gBattleMons[battlerDef].status2 & (STATUS2_CURSED | STATUS2_INFATUATION)
      || gStatuses3[battlerDef] & (STATUS3_PERISH_SONG | STATUS3_LEECHSEED | STATUS3_YAWN))
        ADJUST_SCORE_PTR(DECENT_EFFECT);
}

// stat stages
bool32 ShouldLowerStat(u32 battlerAtk, u32 battlerDef, u32 abilityDef, u32 stat)
{
    if (gBattleMons[battlerDef].statStages[stat] == MIN_STAT_STAGE)
        return FALSE;

    if (gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CLEAR_AMULET)
        return FALSE;

    switch (abilityDef)
    {
    case ABILITY_SPEED_BOOST:
        if (stat == STAT_SPEED)
            return FALSE;
    case ABILITY_HYPER_CUTTER:
        if (stat == STAT_ATK)
            return FALSE;
    case ABILITY_BIG_PECKS:
        if (stat == STAT_DEF)
            return FALSE;
    // case ABILITY_ILLUMINATE:
    //     if (B_ILLUMINATE_EFFECT < GEN_9)
    //         break;
    case ABILITY_KEEN_EYE:
    case ABILITY_MINDS_EYE:
        if (stat == STAT_ACC)
            return FALSE;
    case ABILITY_FLOWER_VEIL:
        if (IS_BATTLER_OF_TYPE(battlerDef, TYPE_GRASS))
            return FALSE;
        break;
    case ABILITY_CONTRARY:
    case ABILITY_CLEAR_BODY:
    case ABILITY_WHITE_SMOKE:
    case ABILITY_FULL_METAL_BODY:
        return FALSE;
    }

    // This should be a viability check
    if (stat == STAT_SPEED)
    {
        // If AI is faster and doesn't have any mons left, lowering speed doesn't give any
        return !(AI_IsFaster(battlerAtk, battlerDef, gAiThinkingStruct->moveConsidered)
            && CountUsablePartyMons(battlerAtk) == 0
            && !HasMoveWithEffect(battlerAtk, EFFECT_ELECTRO_BALL));
    }

    return TRUE;
}

bool32 BattlerStatCanRise(u32 battler, u32 battlerAbility, u32 stat)
{
    if ((gBattleMons[battler].statStages[stat] < MAX_STAT_STAGE && battlerAbility != ABILITY_CONTRARY)
      || (battlerAbility == ABILITY_CONTRARY && gBattleMons[battler].statStages[stat] > MIN_STAT_STAGE))
        return TRUE;
    return FALSE;
}

bool32 AreBattlersStatsMaxed(u32 battlerId)
{
    u32 i;
    for (i = STAT_ATK; i < NUM_BATTLE_STATS; i++)
    {
        if (gBattleMons[battlerId].statStages[i] < MAX_STAT_STAGE)
            return FALSE;
    }
    return TRUE;
}

bool32 AnyStatIsRaised(u32 battlerId)
{
    u32 i;

    for (i = STAT_ATK; i < NUM_BATTLE_STATS; i++)
    {
        if (gBattleMons[battlerId].statStages[i] > DEFAULT_STAT_STAGE)
            return TRUE;
    }
    return FALSE;
}

u32 CountPositiveStatStages(u32 battlerId)
{
    u32 count = 0;
    u32 i;
    for (i = STAT_ATK; i < NUM_BATTLE_STATS; i++)
    {
        if (gBattleMons[battlerId].statStages[i] > DEFAULT_STAT_STAGE)
            count++;
    }
    return count;
}

u32 CountNegativeStatStages(u32 battlerId)
{
    u32 count = 0;
    u32 i;
    for (i = STAT_ATK; i < NUM_BATTLE_STATS; i++)
    {
        if (gBattleMons[battlerId].statStages[i] < DEFAULT_STAT_STAGE)
            count++;
    }
    return count;
}


uq4_12_t GetAtkSpAtkGapThreshold(u32 battlerDef){
    u32 level = gBattleMons[battlerDef].level;
    if (level <= 20){
        return UQ_4_12(1.5);
    }
    else if (level <= 30){
        return UQ_4_12(1.35);
    }
    else if (level <= 40){
        return UQ_4_12(1.2);
    }
    return UQ_4_12(1.15);
}


bool32 ShouldLowerAttack(u32 battlerAtk, u32 battlerDef, u32 defAbility)
{
    if (AI_IsFaster(battlerAtk, battlerDef, gAiThinkingStruct->moveConsidered)
            && (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_TRY_TO_FAINT)
            && CanAIFaintTarget(battlerAtk, battlerDef, 0))
        return FALSE; // Don't bother lowering stats if can kill enemy.
        
    //Still valid to go below -2 if can't make enough progress
    if ((gBattleMons[battlerDef].statStages[STAT_ATK] > 4 || !CanAIFaintTarget(battlerAtk, battlerDef, 4))
      && (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_PHYSICAL)
      //Estimate based on raw stats when lacking move knowledge
      || (!HasAllKnownMoves(battlerDef) && !HasDamagingMove(battlerDef) 
      && (UQ_4_12_TO_INT(gBattleMons[battlerDef].attack * GetAtkSpAtkGapThreshold(battlerDef)) >= gBattleMons[battlerDef].spAttack))) 
      && defAbility != ABILITY_CONTRARY
      && defAbility != ABILITY_CLEAR_BODY
      && defAbility != ABILITY_WHITE_SMOKE
      && defAbility != ABILITY_FULL_METAL_BODY
      && defAbility != ABILITY_HYPER_CUTTER
      && !(gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_MIST)
      && gAiLogicData->holdEffects[battlerDef] != HOLD_EFFECT_CLEAR_AMULET)
        return TRUE;
    return FALSE;
}

//Checks if the user has guards against general stat reduction
bool32 IsStatReductionGuarded(u32 battler){
    if (gAiLogicData->holdEffects[battler] == HOLD_EFFECT_CLEAR_AMULET){
        return TRUE;
    }

    if (gSideStatuses[GetBattlerSide(battler)] & SIDE_STATUS_MIST){
        return TRUE;
    }
    switch (GetBattlerAbility(battler)){
        case ABILITY_CONTRARY:
        case ABILITY_CLEAR_BODY:
        case ABILITY_WHITE_SMOKE:
        case ABILITY_FULL_METAL_BODY:
            return TRUE;
        case ABILITY_COMPETITIVE:
            if (HasMoveWithCategory(battler, DAMAGE_CATEGORY_SPECIAL)){
                return TRUE;
            }
            break;
        case ABILITY_DEFIANT:
            if (HasMoveWithCategory(battler, DAMAGE_CATEGORY_PHYSICAL)){
                return TRUE;
            }
            break;
        default:
            return FALSE;
    }
    return FALSE;
}

bool32 ShouldLowerDefense(u32 battlerAtk, u32 battlerDef, u32 defAbility)
{
    if (AI_IsFaster(battlerAtk, battlerDef, gAiThinkingStruct->moveConsidered)
            && (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_TRY_TO_FAINT)
            && CanAIFaintTarget(battlerAtk, battlerDef, 0))
        return FALSE; // Don't bother lowering stats if can kill enemy.

    if (gBattleMons[battlerDef].statStages[STAT_DEF] > 4
      && HasMoveWithCategory(battlerAtk, DAMAGE_CATEGORY_PHYSICAL)
      && defAbility != ABILITY_CONTRARY
      && defAbility != ABILITY_CLEAR_BODY
      && defAbility != ABILITY_WHITE_SMOKE
      && defAbility != ABILITY_FULL_METAL_BODY
      && defAbility != ABILITY_BIG_PECKS
      && !(gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_MIST)
      && gAiLogicData->holdEffects[battlerDef] != HOLD_EFFECT_CLEAR_AMULET)
        return TRUE;
    return FALSE;
}

bool32 ShouldLowerSpeed(u32 battlerAtk, u32 battlerDef, u32 defAbility)
{
    if (defAbility == ABILITY_CONTRARY
     || defAbility == ABILITY_CLEAR_BODY
     || defAbility == ABILITY_FULL_METAL_BODY
     || defAbility == ABILITY_WHITE_SMOKE
     || (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_MIST)
     || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CLEAR_AMULET)
        return FALSE;

    return (AI_IsSlower(battlerAtk, battlerDef, gAiThinkingStruct->moveConsidered));
}


bool32 ShouldLowerSpAtk(u32 battlerAtk, u32 battlerDef, u32 defAbility)
{
    if (AI_IsFaster(battlerAtk, battlerDef, gAiThinkingStruct->moveConsidered)
            && (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_TRY_TO_FAINT)
            && CanAIFaintTarget(battlerAtk, battlerDef, 0))
        return FALSE; // Don't bother lowering stats if can kill enemy.

    //Still valid to go below -2 if can't make enough progress
    if ((gBattleMons[battlerDef].statStages[STAT_SPATK] > 4 || !CanAIFaintTarget(battlerAtk, battlerDef, 4))
      && (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_SPECIAL)
      || (!HasAllKnownMoves(battlerDef) && !HasDamagingMove(battlerDef) && (UQ_4_12_TO_INT(gBattleMons[battlerDef].spAttack * GetAtkSpAtkGapThreshold(battlerDef)) >= gBattleMons[battlerDef].attack)))
      && defAbility != ABILITY_CONTRARY
      && defAbility != ABILITY_CLEAR_BODY
      && defAbility != ABILITY_FULL_METAL_BODY
      && defAbility != ABILITY_WHITE_SMOKE
      && !(gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_MIST)
      && gAiLogicData->holdEffects[battlerDef] != HOLD_EFFECT_CLEAR_AMULET)
        return TRUE;
    return FALSE;
}

bool32 ShouldLowerSpDef(u32 battlerAtk, u32 battlerDef, u32 defAbility)
{
    if (AI_IsFaster(battlerAtk, battlerDef, gAiThinkingStruct->moveConsidered)
            && (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_TRY_TO_FAINT)
            && CanAIFaintTarget(battlerAtk, battlerDef, 0))
        return FALSE; // Don't bother lowering stats if can kill enemy.

    if (gBattleMons[battlerDef].statStages[STAT_SPDEF] > 4
      && HasMoveWithCategory(battlerAtk, DAMAGE_CATEGORY_SPECIAL)
      && !AreAllMovesOfSplitIneffective(battlerAtk, battlerDef, DAMAGE_CATEGORY_SPECIAL)
      && defAbility != ABILITY_CONTRARY
      && defAbility != ABILITY_CLEAR_BODY
      && defAbility != ABILITY_FULL_METAL_BODY
      && defAbility != ABILITY_WHITE_SMOKE
      && !(gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_MIST)
      && gAiLogicData->holdEffects[battlerDef] != HOLD_EFFECT_CLEAR_AMULET)
        return TRUE;
    return FALSE;
}

//Various checks to determine whether a move does nothing
//I ended up adding additional checks to this because the change in switch ai logic means move scores aren't being used anymore
bool32 IsMoveIneffective(u32 move, u32 battlerAtk, u32 battlerDef){
    u32 moveEffect = gMovesInfo[move].effect;

    if (move == MOVE_NONE){
        return TRUE;
    }
    if (AI_GetMoveEffectiveness(move, battlerAtk, battlerDef) == UQ_4_12(0.0)){
        return TRUE;
    }
    if (CanAbilityBlockMove(battlerAtk, battlerDef, gAiLogicData->abilities[battlerAtk], gAiLogicData->abilities[battlerDef], move, ABILITY_CHECK_TRIGGER_AI)){
        return TRUE;
    }
    if (gDisableStructs[gBattlerAttacker].disabledMove == move){
        return TRUE;
    }
    
    switch (moveEffect){
        case EFFECT_TORMENT:
            if (moveEffect == EFFECT_TORMENT && gBattleMons[battlerDef].status2 & STATUS2_TORMENT){
                return TRUE;}
            break;
        case EFFECT_DISABLE:
            if (gDisableStructs[battlerDef].disableTimer > 0){
                return TRUE;}
            break;
        
        default:
            break;
    }
    if (move == MOVE_TORMENT && gBattleMons[battlerDef].status2 & STATUS2_TORMENT){
        return TRUE;
    }
    //Factor pp into this eventually
    return FALSE;
}

bool32 AreAllMovesOfSplitIneffective(u32 battlerAtk, u32 battlerDef, u32 category){
    u32 i;
    u32 currentMove;
    for (i = 0; i < MAX_MON_MOVES; i++){
        currentMove = gBattleMons[battlerAtk].moves[i];
        //
        if (GetBattleMoveCategory(currentMove) != category){
            continue;
        }
        //At least one move of the split is effective
        if (!IsMoveIneffective(currentMove, battlerAtk, battlerDef)){
            return FALSE;
        }
    }
    return TRUE;
}

bool32 HasIneffectiveDamagingMove(u32 battlerAtk, u32 battlerDef){
    u32 i;
    u32 currentMove;
    for (i = 0; i < MAX_MON_MOVES; i++){
        currentMove = gBattleMons[battlerAtk].moves[i];
        //
        if (gMovesInfo[currentMove].power == 0){
            continue;
        }
        //A damaging move is ineffective
        if (IsMoveIneffective(currentMove, battlerAtk, battlerDef)){
            return TRUE;
        }
    }
    //This can include if all moves are status moves
    return FALSE;    
}

//Made this index identification function because I couldn't find it in the codebase, though I'm pretty sure it's somewhere.
u32 FindMoveIndex(u32 battler, u32 move){
    u32 i;
    u32 currentMove;
    for (i = 0; i < MAX_MON_MOVES; i++){
        currentMove = gBattleMons[battler].moves[i];
        if (currentMove == move){
            return i;
        }
    }
    return MOVE_UNAVAILABLE;
}


bool32 ShouldLowerAccuracy(u32 battlerAtk, u32 battlerDef, u32 defAbility)
{
    if (AI_IsFaster(battlerAtk, battlerDef, gAiThinkingStruct->moveConsidered)
            && (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_TRY_TO_FAINT)
            && CanAIFaintTarget(battlerAtk, battlerDef, 0))
        return FALSE; // Don't bother lowering stats if can kill enemy.

    if (defAbility != ABILITY_CONTRARY
      && defAbility != ABILITY_CLEAR_BODY
      && defAbility != ABILITY_WHITE_SMOKE
      && defAbility != ABILITY_FULL_METAL_BODY
      && defAbility != ABILITY_KEEN_EYE
      && defAbility != ABILITY_MINDS_EYE
    //   && (B_ILLUMINATE_EFFECT >= GEN_9 && defAbility != ABILITY_ILLUMINATE)
      && !(gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_MIST)
      && gAiLogicData->holdEffects[battlerDef] != HOLD_EFFECT_CLEAR_AMULET)
        return TRUE;
    return FALSE;
}

bool32 ShouldLowerEvasion(u32 battlerAtk, u32 battlerDef, u32 defAbility)
{
    if (AI_IsFaster(battlerAtk, battlerDef, gAiThinkingStruct->moveConsidered)
            && (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_TRY_TO_FAINT)
            && CanAIFaintTarget(battlerAtk, battlerDef, 0))
        return FALSE; // Don't bother lowering stats if can kill enemy.

    //Was originally just DEFAULT_STAT_STAGE, but I think that's too punishing
    if (gBattleMons[battlerDef].statStages[STAT_EVASION] > DEFAULT_STAT_STAGE - 3
      && defAbility != ABILITY_CONTRARY
      && defAbility != ABILITY_CLEAR_BODY
      && defAbility != ABILITY_FULL_METAL_BODY
      && defAbility != ABILITY_WHITE_SMOKE
      && !(gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_MIST)
      && gAiLogicData->holdEffects[battlerDef] != HOLD_EFFECT_CLEAR_AMULET)
        return TRUE;
    return FALSE;
}

bool32 CanIndexMoveFaintTarget(u32 battlerAtk, u32 battlerDef, u32 moveIndex, enum DamageCalcContext calcContext)
{
    s32 dmg;
    u16 *moves = gBattleMons[battlerAtk].moves;

    if (IsDoubleBattle() && battlerDef == BATTLE_PARTNER(battlerAtk))
        dmg = gAiLogicData->simulatedDmg[battlerAtk][battlerDef][moveIndex].maximum; // Attacking partner, be careful
    else
        dmg = AI_GetDamage(battlerAtk, battlerDef, moveIndex, calcContext, gAiLogicData);

    if (gBattleMons[battlerDef].hp <= dmg && !CanEndureHit(battlerAtk, battlerDef, moves[moveIndex]))
        return TRUE;
    return FALSE;
}

bool32 CanIndexMoveGuaranteeFaintTarget(u32 battlerAtk, u32 battlerDef, u32 moveIndex)
{
    s32 dmg;
    u16 *moves = gBattleMons[battlerAtk].moves;

    dmg = gAiLogicData->simulatedDmg[battlerAtk][battlerDef][moveIndex].minimum; // Explictly care about guaranteed KOs universally

    if (gBattleMons[battlerDef].hp <= dmg && !CanEndureHit(battlerAtk, battlerDef, moves[moveIndex]))
        return TRUE;
    return FALSE;
}

u16 *GetMovesArray(u32 battler)
{
    // DebugPrintf("Getting result from GetMovesArray function for the first move of battler %d:  %d", battler, gBattleMons[battler].moves[0]);
    if (IsAiBattlerAware(battler) || IsAiBattlerAware(BATTLE_PARTNER(battler)))
        return gBattleMons[battler].moves;
    else
        return gBattleHistory->usedMoves[battler];
}



bool32 DoesBattlerTypeMatchMove(u32 battler, u32 move){
    u32 types[3];
    u32 moveType = gMovesInfo[move].type;

    GetBattlerTypes(battler, FALSE, types);

    if (types[0] == moveType || types[1] == moveType || types[2] == moveType){
        return TRUE;
    }

    return FALSE;
}


/*
When computing moves of non-AI battlers, also read unrevealed STAB damaging moves.
This is important for better damage threshold estimates, and will eventually be used in the switch logic.
But ordinary GetMovesArray should be used for move-specific logic, such as whether the player has revealed Brick Break. 
*/
u16 *GetMovesArrayWithHiddenSTAB(u32 battler, u16 *moves){
    int i;
    struct BattlePokemon *bufferPoke = (struct BattlePokemon *) &gBattleResources->bufferB[battler][4];
    bool32 isMoveAware =  IsAiBattlerAware(battler) || IsAiBattlerAware(BATTLE_PARTNER(battler));

    for (i = 0; i < MAX_MON_MOVES; i++){
        if (isMoveAware){
            //use gBattleMons in this case because the other approach ended up having problems
            moves[i] = gBattleMons[battler].moves[i];
        }
        else{
            moves[i] = gBattleHistory->usedMoves[battler][i];
            if (moves[i] == 0 && DoesBattlerTypeMatchMove(battler, bufferPoke->moves[i])){
                moves[i] = gBattleMons[battler].moves[i];
                //Use bufferPoke in the case that gBattleMons hasn't yet been filled.
                if (moves[i] == 0){
                    moves[i] = bufferPoke->moves[i];
                }
                
            }
        }
    }
    return moves;
}

bool32 HasOnlyMovesWithCategory(u32 battlerId, u32 category, bool32 onlyOffensive)
{
    u32 i;
    u16 *moves = GetMovesArray(battlerId);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (onlyOffensive && IsBattleMoveStatus(moves[i]))
            continue;
        if (moves[i] != MOVE_NONE && moves[i] != MOVE_UNAVAILABLE && GetBattleMoveCategory(moves[i]) != category)
            return FALSE;
    }

    return TRUE;
}

bool32 HasMoveWithCategory(u32 battler, u32 category)
{
    u32 i;
    u16 *moves = GetMovesArray(battler);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] != MOVE_NONE && moves[i] != MOVE_UNAVAILABLE && GetBattleMoveCategory(moves[i]) == category)
            return TRUE;
    }
    return FALSE;
}

bool32 HasNoMovesKnown(u32 battler){

    u32 i;
    u16 *moves = GetMovesArray(battler);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] != MOVE_NONE && moves[i] != MOVE_UNAVAILABLE)
            return FALSE;
    }
    return TRUE;
}

u32 GetStatusMoveCount(u32 battler){
    u32 statusCount = 0;
    u32 i;
    u16 *moves = GetMovesArray(battler);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] != MOVE_NONE && moves[i] != MOVE_UNAVAILABLE && IsBattleMoveStatus(moves[i])){
            statusCount += 1;
        }
    }
    return statusCount;
}

bool32 HasNoKnownNonProtectingMoves(u32 battler){
    u32 i;
    u16 *moves = GetMovesArray(battler);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        u32 move = moves[i];
        if (move != MOVE_NONE && move != MOVE_UNAVAILABLE && gMovesInfo[move].effect != EFFECT_PROTECT && gMovesInfo[move].effect != EFFECT_MAT_BLOCK)
            return FALSE;
    }
    return TRUE; 
}


bool32 HasAllKnownMoves(u32 battler){
    // DebugPrintf("HasAllKnownMoves called");
    u32 i;
    u16 *moves = GetMovesArray(battler);
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        u32 move = moves[i];
        // DebugPrintf("This move is %d", move);
        if (move == MOVE_NONE || move == MOVE_UNAVAILABLE){
            // DebugPrintf("Reached HasAllKnownMoves False case");
            return FALSE;
        }
    }
    // DebugPrintf("Reached HasAllKnownMoves True case");

    return TRUE; 
}

/*
Used for logic such as gem use, getting strongest attack of a given type
Can also be used to check if a mon has a move of a given type that does damage, by checking that the return value is not MOVE_NONE
*/
u32 GetBestDmgMoveofType(u32 battlerAtk, u32 battlerDef, u32 type){
    u32 bestMove = MOVE_NONE;
    u32 bestDmg = 0;
    u32 i;
    u16 *moves = GetMovesArray(battlerAtk);

    for (i = 0; i < MAX_MON_MOVES; i++){
        if ((moves[i] == MOVE_NONE || moves[i] == MOVE_UNAVAILABLE || gMovesInfo[moves[i]].type != type)){
            continue;
        }
        if (gAiLogicData->simulatedDmg[battlerAtk][battlerDef][i].median > bestDmg){
            bestMove = moves[i];
            bestDmg = gAiLogicData->simulatedDmg[battlerAtk][battlerDef][i].median;
        }
    }
    return bestMove;
}

bool32 HasMoveWithType(u32 battler, u32 type)
{
    s32 i;
    u16 *moves = GetMovesArray(battler);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] != MOVE_NONE && moves[i] != MOVE_UNAVAILABLE && GetMoveType(moves[i]) == type)
            return TRUE;
    }

    return FALSE;
}

bool32 HasContactMove(u32 battlerId){
    s32 i;
    u16 *moves = GetMovesArray(battlerId);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] != MOVE_NONE && moves[i] != MOVE_UNAVAILABLE
            && MoveMakesContact(moves[i]))
            return TRUE;
    }

    return FALSE;   
}

bool32 HasMoveWithEffect(u32 battlerId, enum BattleMoveEffects effect)

{
    s32 i;
    u16 *moves = GetMovesArray(battlerId);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] != MOVE_NONE && moves[i] != MOVE_UNAVAILABLE
            && GetMoveEffect(moves[i]) == effect)
            return TRUE;
    }

    return FALSE;
}

bool32 HasMinimizeDoubleMove(u32 battlerId){
    s32 i;
    u16 *moves = GetMovesArray(battlerId);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] != MOVE_NONE && moves[i] != MOVE_UNAVAILABLE
            && gMovesInfo[moves[i]].minimizeDoubleDamage == TRUE)
            return TRUE;
    }

    return FALSE;
}
bool32 HasBattlerSideMoveWithEffect(u32 battler, u32 effect)
{
    if (HasMoveWithEffect(battler, effect))
        return TRUE;
    if (IsDoubleBattle() && HasMoveWithEffect(BATTLE_OPPOSITE(battler), effect))
        return TRUE;
    return FALSE;
}

// HasBattlerSideMoveWithEffect checks if the AI knows a side has a move effect,
// while HasBattlerSideUsedMoveWithEffect checks if the side has ever used a move effect.
// The former acts the same way as the latter if AI_FLAG_OMNISCIENT isn't used.
bool32 HasBattlerSideUsedMoveWithEffect(u32 battler, u32 effect)
{
    u32 i;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (GetMoveEffect(gBattleHistory->usedMoves[battler][i]) == effect)
            return TRUE;
        if (IsDoubleBattle() && GetMoveEffect(gBattleHistory->usedMoves[BATTLE_OPPOSITE(battler)][i]) == effect)
            return TRUE;
    }
    return FALSE;
}

bool32 HasNonVolatileMoveEffect(u32 battlerId, u32 effect)
{
    s32 i;
    u16 *moves = GetMovesArray(battlerId);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (GetMoveNonVolatileStatus(moves[i]) == effect)
            return TRUE;
    }

    return FALSE;
}

bool32 IsPowerBasedOnStatus(u32 battlerId, enum BattleMoveEffects effect, u32 argument)
{
    s32 i;
    u16 *moves = GetMovesArray(battlerId);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] != MOVE_NONE && moves[i] != MOVE_UNAVAILABLE
            && GetMoveEffect(moves[i]) == effect
            && (GetMoveEffectArg_Status(moves[i]) & argument))
            return TRUE;
    }

    return FALSE;
}

bool32 HasMoveWithAdditionalEffect(u32 battlerId, u32 moveEffect)
{
    s32 i;
    u16 *moves = GetMovesArray(battlerId);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] != MOVE_NONE && moves[i] != MOVE_UNAVAILABLE
            && MoveHasAdditionalEffect(moves[i], moveEffect))
            return TRUE;
    }

    return FALSE;
}

bool32 HasBattlerSideMoveWithAdditionalEffect(u32 battler, u32 moveEffect)
{
    if (HasMoveWithAdditionalEffect(battler, moveEffect))
        return TRUE;
    if (IsDoubleBattle() && HasMoveWithAdditionalEffect(BATTLE_OPPOSITE(battler), moveEffect))
        return TRUE;
    return FALSE;
}

// HasBattlerSideMoveWithAdditionalEffect checks if the AI knows a side has a move effect,
// while HasBattlerSideUsedMoveWithAdditionalEffect checks if the side has ever used a move effect.
// The former acts the same way as the latter if AI_FLAG_OMNISCIENT isn't used.
bool32 HasBattlerSideUsedMoveWithAdditionalEffect(u32 battler, u32 moveEffect)
{
    u32 i;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (MoveHasAdditionalEffect(gBattleHistory->usedMoves[battler][i], moveEffect))
            return TRUE;
        if (IsDoubleBattle() && MoveHasAdditionalEffect(gBattleHistory->usedMoves[BATTLE_OPPOSITE(battler)][i], moveEffect))
            return TRUE;
    }
    return FALSE;
}

bool32 HasMoveWithCriticalHitChance(u32 battlerId)
{
    s32 i;
    u16 *moves = GetMovesArray(battlerId);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] != MOVE_NONE && moves[i] != MOVE_UNAVAILABLE
            && GetMoveCriticalHitStage(moves[i]) > 0)
            return TRUE;
    }

    return FALSE;
}

bool32 HasMoveWithMoveEffectExcept(u32 battlerId, u32 moveEffect, enum BattleMoveEffects exception)
{
    s32 i;
    u16 *moves = GetMovesArray(battlerId);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] != MOVE_NONE && moves[i] != MOVE_UNAVAILABLE
            && GetMoveEffect(moves[i]) != exception
            && MoveHasAdditionalEffect(moves[i], moveEffect))
            return TRUE;
    }

    return FALSE;
}

bool32 HasMove(u32 battlerId, u32 move)
{
    s32 i;
    u16 *moves = GetMovesArray(battlerId);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] != MOVE_NONE && moves[i] != MOVE_UNAVAILABLE && moves[i] == move)
            return TRUE;
    }

    return FALSE;
}

bool32 HasAnyKnownMove(u32 battlerId)
{
    s32 i;
    u16 *moves = GetMovesArray(battlerId);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] != MOVE_NONE)
            return TRUE;
    }

    return FALSE;
}

bool32 HasMoveThatLowersOwnStats(u32 battlerId)
{
    s32 i, j;
    u32 aiMove;
    u16 *moves = GetMovesArray(battlerId);
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        aiMove = moves[i];
        if (aiMove != MOVE_NONE && aiMove != MOVE_UNAVAILABLE)
        {
            u32 additionalEffectCount = GetMoveAdditionalEffectCount(aiMove);
            for (j = 0; j < additionalEffectCount; j++)
            {
                const struct AdditionalEffect *additionalEffect = GetMoveAdditionalEffectById(aiMove, j);
                if (IsSelfStatLoweringEffect(additionalEffect->moveEffect) && additionalEffect->self)
                    return TRUE;
            }
        }
    }
    return FALSE;
}

bool32 HasMoveWithLowAccuracy(u32 battlerAtk, u32 battlerDef, u32 accCheck, bool32 ignoreStatus, u32 atkAbility, u32 defAbility, u32 atkHoldEffect, u32 defHoldEffect)
{
    s32 i;
    u16 *moves = GetMovesArray(battlerAtk);
    u32 moveLimitations = gAiLogicData->moveLimitations[battlerAtk];

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (IsMoveUnusable(i, moves[i], moveLimitations))
            continue;

        if (ignoreStatus && IsBattleMoveStatus(moves[i]))
            continue;
        else if ((!IsBattleMoveStatus(moves[i]) && GetMoveAccuracy(moves[i]) == 0)
              || GetBattlerMoveTargetType(battlerAtk, moves[i]) & (MOVE_TARGET_USER | MOVE_TARGET_OPPONENTS_FIELD))
            continue;

        if (gAiLogicData->moveAccuracy[battlerAtk][battlerDef][i] <= accCheck)
            return TRUE;
    }

    return FALSE;
}

bool32 HasSleepMoveWithLowAccuracy(u32 battlerAtk, u32 battlerDef)
{
    u32 i;
    u16 *moves = GetMovesArray(battlerAtk);
    u32 moveLimitations = gAiLogicData->moveLimitations[battlerAtk];

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (IsMoveUnusable(i, moves[i], moveLimitations))
            continue;

        if (GetMoveNonVolatileStatus(moves[i]) == MOVE_EFFECT_SLEEP
        && gAiLogicData->moveAccuracy[battlerAtk][battlerDef][i] < 85)
            return TRUE;
    }
    return FALSE;
}

bool32 HasHealingEffect(u32 battlerId)
{
    s32 i;
    u16 *moves = GetMovesArray(battlerId);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] != MOVE_NONE && moves[i] != MOVE_UNAVAILABLE && IsHealingMove(moves[i]))
            return TRUE;
    }

    return FALSE;
}

bool32 IsTrappingMove(u32 move)
{
    switch (GetMoveEffect(move))
    {
    case EFFECT_MEAN_LOOK:
    case EFFECT_FAIRY_LOCK:
    //case EFFECT_NO_RETREAT:   // TODO
        return TRUE;
    default:
        return MoveHasAdditionalEffect(move, MOVE_EFFECT_PREVENT_ESCAPE)
            || MoveHasAdditionalEffect(move, MOVE_EFFECT_WRAP);
    }
}

bool32 HasTrappingMoveEffect(u32 battler)
{
    s32 i;
    u16 *moves = GetMovesArray(battler);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] != MOVE_NONE && moves[i] != MOVE_UNAVAILABLE && IsTrappingMove(moves[i]))
            return TRUE;
    }

    return FALSE;
}

bool32 HasThawingMove(u32 battler)
{
    s32 i;
    u16 *moves = GetMovesArray(battler);
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] != MOVE_NONE && moves[i] != MOVE_UNAVAILABLE && MoveThawsUser(moves[i]))
            return TRUE;
    }
    return FALSE;
}

bool32 IsUngroundingEffect(enum BattleMoveEffects effect)
{
    switch (effect)
    {
    case EFFECT_MAGNET_RISE:
        return TRUE;
    default:
        return FALSE;
    }
}

// for anger point
bool32 IsAttackBoostMoveEffect(enum BattleMoveEffects effect)
{
    switch (effect)
    {
    case EFFECT_ATTACK_UP:
    case EFFECT_ATTACK_UP_2:
    case EFFECT_ATTACK_ACCURACY_UP:
    case EFFECT_ATTACK_SPATK_UP:
    case EFFECT_DRAGON_DANCE:
    case EFFECT_COIL:
    case EFFECT_BELLY_DRUM:
    case EFFECT_BULK_UP:
    case EFFECT_GROWTH:
    case EFFECT_FILLET_AWAY:
        return TRUE;
    default:
        return FALSE;
    }
}

bool32 IsStatRaisingEffect(enum BattleMoveEffects effect)
{
    switch (effect)
    {
    case EFFECT_ATTACK_UP:
    case EFFECT_ATTACK_UP_2:
    case EFFECT_DEFENSE_UP:
    case EFFECT_DEFENSE_UP_2:
    case EFFECT_DEFENSE_UP_3:
    case EFFECT_SPEED_UP:
    case EFFECT_SPEED_UP_2:
    case EFFECT_SPECIAL_ATTACK_UP:
    case EFFECT_SPECIAL_ATTACK_UP_2:
    case EFFECT_SPECIAL_ATTACK_UP_3:
    case EFFECT_SPECIAL_DEFENSE_UP:
    case EFFECT_SPECIAL_DEFENSE_UP_2:
    case EFFECT_ACCURACY_UP:
    case EFFECT_ACCURACY_UP_2:
    case EFFECT_EVASION_UP:
    case EFFECT_EVASION_UP_2:
    case EFFECT_MINIMIZE:
    case EFFECT_DEFENSE_CURL:
    case EFFECT_CALM_MIND:
    case EFFECT_COSMIC_POWER:
    case EFFECT_DRAGON_DANCE:
    case EFFECT_ACUPRESSURE:
    case EFFECT_SHELL_SMASH:
    case EFFECT_SHIFT_GEAR:
    case EFFECT_ATTACK_ACCURACY_UP:
    case EFFECT_ATTACK_SPATK_UP:
    case EFFECT_GROWTH:
    case EFFECT_COIL:
    case EFFECT_QUIVER_DANCE:
    case EFFECT_BULK_UP:
    case EFFECT_GEOMANCY:
    case EFFECT_STOCKPILE:
    case EFFECT_VICTORY_DANCE:
        return TRUE;
    case EFFECT_CHARGE:
        return B_CHARGE_SPDEF_RAISE >= GEN_5;
    default:
        return FALSE;
    }
}

bool32 IsStatLoweringEffect(enum BattleMoveEffects effect)
{
    // ignore other potentially-beneficial effects like defog, gravity
    switch (effect)
    {
    case EFFECT_ATTACK_DOWN:
    case EFFECT_DEFENSE_DOWN:
    case EFFECT_SPEED_DOWN:
    case EFFECT_SPECIAL_ATTACK_DOWN:
    case EFFECT_SPECIAL_DEFENSE_DOWN:
    case EFFECT_ACCURACY_DOWN:
    case EFFECT_EVASION_DOWN:
    case EFFECT_ATTACK_DOWN_2:
    case EFFECT_DEFENSE_DOWN_2:
    case EFFECT_SPEED_DOWN_2:
    case EFFECT_SPECIAL_ATTACK_DOWN_2:
    case EFFECT_SPECIAL_DEFENSE_DOWN_2:
    case EFFECT_ACCURACY_DOWN_2:
    case EFFECT_EVASION_DOWN_2:
    case EFFECT_TICKLE:
    case EFFECT_CAPTIVATE:
    case EFFECT_NOBLE_ROAR:
    case EFFECT_MEMENTO:
        return TRUE;
    default:
        return FALSE;
    }
}

bool32 IsSelfStatLoweringEffect(enum BattleMoveEffects effect)
{
    // Self stat lowering moves like Overheart, Superpower etc.
    switch (effect)
    {
    case MOVE_EFFECT_ATK_MINUS_1:
    case MOVE_EFFECT_DEF_MINUS_1:
    case MOVE_EFFECT_SPD_MINUS_1:
    case MOVE_EFFECT_SP_ATK_MINUS_1:
    case MOVE_EFFECT_SP_DEF_MINUS_1:
    case MOVE_EFFECT_EVS_MINUS_1:
    case MOVE_EFFECT_ACC_MINUS_1:
    case MOVE_EFFECT_ATK_MINUS_2:
    case MOVE_EFFECT_DEF_MINUS_2:
    case MOVE_EFFECT_SPD_MINUS_2:
    case MOVE_EFFECT_SP_ATK_MINUS_2:
    case MOVE_EFFECT_SP_DEF_MINUS_2:
    case MOVE_EFFECT_EVS_MINUS_2:
    case MOVE_EFFECT_ACC_MINUS_2:
    case MOVE_EFFECT_V_CREATE:
    case MOVE_EFFECT_ATK_DEF_DOWN:
    case MOVE_EFFECT_DEF_SPDEF_DOWN:
        return TRUE;
    default:
        return FALSE;
    }
}

bool32 IsSwitchOutEffect(enum BattleMoveEffects effect)
{
    // Switch out effects like U-Turn, Volt Switch, etc.
    switch (effect)
    {
    case EFFECT_TELEPORT:
        if (B_TELEPORT_BEHAVIOR >= GEN_8)
            return TRUE;
    case EFFECT_HIT_ESCAPE:
    case EFFECT_PARTING_SHOT:
    case EFFECT_BATON_PASS:
    case EFFECT_CHILLY_RECEPTION:
    case EFFECT_SHED_TAIL:
        return TRUE;
    default:
        return FALSE;
    }
}

bool32 IsSubstituteEffect(enum BattleMoveEffects effect)
{
    // Substitute effects like Substitute, Shed Tail, etc.
    switch (effect)
    {
    case EFFECT_SUBSTITUTE:
    case EFFECT_SHED_TAIL:
        return TRUE;
    default:
        return FALSE;
    }
}

bool32 IsChaseEffect(enum BattleMoveEffects effect)
{
    // Effects that hit switching out mons like Pursuit
    switch (effect)
    {
    case EFFECT_PURSUIT:
        return TRUE;
    default:
        return FALSE;
    }
}

static inline bool32 IsMoveSleepClauseTrigger(u32 move)
{
    u32 i;
    enum BattleMoveEffects effect = GetMoveEffect(move);

    // Sleeping effects like Sleep Powder, Yawn, Dark Void, etc.
    switch (effect)
    {
    case EFFECT_YAWN:
    case EFFECT_DARK_VOID:
        return TRUE;
    default:
        break;
    }
    switch(GetMoveNonVolatileStatus(move))
    {
    case MOVE_EFFECT_SLEEP:
        return TRUE;
    }

    // Sleeping effects like G-Max Befuddle, G-Max Snooze, etc.
    u32 additionalEffectCount = GetMoveAdditionalEffectCount(move);
    for (i = 0; i < additionalEffectCount; i++)
    {
        const struct AdditionalEffect *additionalEffect = GetMoveAdditionalEffectById(move, i);
        switch (additionalEffect->moveEffect)
        {
        // Skip MOVE_EFFECT_SLEEP as moves with a secondary chance of applying sleep are allowed by Smogon's rules (ie. Relic Song)
        case MOVE_EFFECT_EFFECT_SPORE_SIDE:
        case MOVE_EFFECT_YAWN_FOE:
            return TRUE;
        }
    }
    return FALSE;
}

bool32 HasDamagingMove(u32 battlerId)
{
    u32 i;
    u16 *moves = GetMovesArray(battlerId);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] != MOVE_NONE && moves[i] != MOVE_UNAVAILABLE && !IsBattleMoveStatus(moves[i]))
            return TRUE;
    }

    return FALSE;
}

bool32 HasDamagingMoveOfType(u32 battlerId, u32 type)
{
    s32 i;
    u16 *moves = GetMovesArray(battlerId);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] != MOVE_NONE && moves[i] != MOVE_UNAVAILABLE
          && GetMoveType(moves[i]) == type && !IsBattleMoveStatus(moves[i]))
            return TRUE;
    }

    return FALSE;
}

bool32 HasMoveWithFlag(u32 battler, MoveFlag getFlag)
{
    u16 *moves = GetMovesArray(battler);
    u32 moveLimitations = gAiLogicData->moveLimitations[battler];

    for (s32 moveIndex = 0; moveIndex < MAX_MON_MOVES; moveIndex++)
    {
        if (IsMoveUnusable(moveIndex, moves[moveIndex], moveLimitations))
            continue;

        if (getFlag(moves[moveIndex]))
            return TRUE;
    }
    return FALSE;
}

bool32 IsTwoTurnNotSemiInvulnerableMove(u32 battlerAtk, u32 move)
{
    switch (GetMoveEffect(move))
    {
    case EFFECT_SOLAR_BEAM:
    case EFFECT_TWO_TURNS_ATTACK:
        return !(gAiLogicData->holdEffects[battlerAtk] == HOLD_EFFECT_POWER_HERB
              || (AI_GetWeather() & GetMoveTwoTurnAttackWeather(move)));
    default:
        return FALSE;
    }
}

static u32 GetLeechSeedDamage(u32 battlerId)
{
    u32 damage = 0;
    if ((gStatuses3[battlerId] & STATUS3_LEECHSEED)
     && gBattleMons[gStatuses3[battlerId] & STATUS3_LEECHSEED_BATTLER].hp != 0)
     {
        damage = GetNonDynamaxMaxHP(battlerId) / 8;
        if (damage == 0)
            damage = 1;
     }
     return damage;
}

static u32 GetNightmareDamage(u32 battlerId)
{
    u32 damage = 0;
    if ((gBattleMons[battlerId].status2 & STATUS2_NIGHTMARE) && gBattleMons[battlerId].status1 & STATUS1_SLEEP)
    {
        damage = GetNonDynamaxMaxHP(battlerId) / 4;
        if (damage == 0)
            damage = 1;
    }
    return damage;
}

static u32 GetCurseDamage(u32 battlerId)
{
    u32 damage = 0;
    if (gBattleMons[battlerId].status2 & STATUS2_CURSED)
    {
        damage = GetNonDynamaxMaxHP(battlerId) / 4;
        if (damage == 0)
            damage = 1;
    }
    return damage;
}

static u32 GetTrapDamage(u32 battlerId)
{
    // ai has no knowledge about turns remaining
    u32 damage = 0;
    enum ItemHoldEffect holdEffect = gAiLogicData->holdEffects[gBattleStruct->wrappedBy[battlerId]];
    if (gBattleMons[battlerId].status2 & STATUS2_WRAPPED)
    {
        if (holdEffect == HOLD_EFFECT_BINDING_BAND)
            damage = GetNonDynamaxMaxHP(battlerId) / (B_BINDING_DAMAGE >= GEN_6 ? 6 : 8);
        else
            damage = GetNonDynamaxMaxHP(battlerId) / (B_BINDING_DAMAGE >= GEN_6 ? 8 : 16);

        if (damage == 0)
            damage = 1;
    }
    return damage;
}

static u32 GetPoisonDamage(u32 battlerId)
{
    u32 damage = 0;

    if (gAiLogicData->abilities[battlerId] == ABILITY_POISON_HEAL)
        return damage;

    if (gBattleMons[battlerId].status1 & STATUS1_POISON)
    {
        damage = gBattleMons[battlerId].maxHP / 8;
        if (damage == 0)
            damage = 1;
    }
    else if (gBattleMons[battlerId].status1 & STATUS1_TOXIC_POISON)
    {
        u32 status1Temp = gBattleMons[battlerId].status1;
        damage = gBattleMons[battlerId].maxHP / 16;
        if (damage == 0)
            damage = 1;
        if ((status1Temp & STATUS1_TOXIC_COUNTER) != STATUS1_TOXIC_TURN(15)) // not 16 turns
            status1Temp += STATUS1_TOXIC_TURN(1);
        damage *= (status1Temp & STATUS1_TOXIC_COUNTER) >> 8;
    }
    return damage;
}

static bool32 BattlerAffectedBySandstorm(u32 battlerId, u32 ability)
{
    if (!IS_BATTLER_ANY_TYPE(battlerId, TYPE_ROCK, TYPE_GROUND, TYPE_STEEL)
      && ability != ABILITY_SAND_VEIL
      && ability != ABILITY_SAND_FORCE
      && ability != ABILITY_SAND_RUSH
      && ability != ABILITY_OVERCOAT)
        return TRUE;
    return FALSE;
}

static bool32 BattlerAffectedByHail(u32 battlerId, u32 ability)
{
    if (!IS_BATTLER_OF_TYPE(battlerId, TYPE_ICE)
      && ability != ABILITY_SNOW_CLOAK
      && ability != ABILITY_OVERCOAT
      && ability != ABILITY_ICE_BODY)
        return TRUE;
    return FALSE;
}

static u32 GetWeatherDamage(u32 battlerId)
{
    u32 ability = gAiLogicData->abilities[battlerId];
    enum ItemHoldEffect holdEffect = gAiLogicData->holdEffects[battlerId];
    u32 damage = 0;
    u32 weather = AI_GetWeather();
    if (!weather)
        return 0;

    if (weather & B_WEATHER_SANDSTORM)
    {
        if (BattlerAffectedBySandstorm(battlerId, ability)
          && !(gStatuses3[battlerId] & (STATUS3_UNDERGROUND | STATUS3_UNDERWATER))
          && holdEffect != HOLD_EFFECT_SAFETY_GOGGLES)
        {
            damage = GetNonDynamaxMaxHP(battlerId) / 16;
            if (damage == 0)
                damage = 1;
        }
    }
    if ((weather & B_WEATHER_HAIL) && ability != ABILITY_ICE_BODY)
    {
        if (BattlerAffectedByHail(battlerId, ability)
          && !(gStatuses3[battlerId] & (STATUS3_UNDERGROUND | STATUS3_UNDERWATER))
          && holdEffect != HOLD_EFFECT_SAFETY_GOGGLES)
        {
            damage = GetNonDynamaxMaxHP(battlerId) / 16;
            if (damage == 0)
                damage = 1;
        }
    }
    return damage;
}

u32 GetBattlerSecondaryDamage(u32 battlerId)
{
    u32 secondaryDamage;

    if (gAiLogicData->abilities[battlerId] == ABILITY_MAGIC_GUARD)
        return FALSE;

    secondaryDamage = GetLeechSeedDamage(battlerId)
     + GetNightmareDamage(battlerId)
     + GetCurseDamage(battlerId)
     + GetTrapDamage(battlerId)
     + GetPoisonDamage(battlerId)
     + GetWeatherDamage(battlerId);

    return secondaryDamage;
}

bool32 BattlerWillFaintFromWeather(u32 battler, u32 ability)
{
    if ((BattlerAffectedBySandstorm(battler, ability) || BattlerAffectedByHail(battler, ability))
      && gBattleMons[battler].hp <= max(1, gBattleMons[battler].maxHP / 16))
        return TRUE;

    return FALSE;
}

bool32 BattlerWillFaintFromSecondaryDamage(u32 battler, u32 ability)
{
    if (GetBattlerSecondaryDamage(battler) != 0
      && gBattleMons[battler].hp <= max(1, gBattleMons[battler].maxHP / 16))
        return TRUE;
    return FALSE;
}

static bool32 AnyUsefulStatIsRaised(u32 battler)
{
    u32 statId;

    for (statId = STAT_ATK; statId < NUM_BATTLE_STATS; statId++)
    {
        if (gBattleMons[battler].statStages[statId] > DEFAULT_STAT_STAGE)
        {
            switch (statId)
            {
            case STAT_ATK:
                if (HasMoveWithCategory(battler, DAMAGE_CATEGORY_PHYSICAL))
                    return TRUE;
                break;
            case STAT_SPATK:
                if (HasMoveWithCategory(battler, DAMAGE_CATEGORY_SPECIAL))
                    return TRUE;
                break;
            case STAT_SPEED:
                return TRUE;
            }
        }
    }

    return FALSE;
}

static bool32 PartyBattlerShouldAvoidHazards(u32 currBattler, u32 switchBattler)
{
    struct Pokemon *mon = &GetBattlerParty(currBattler)[switchBattler];
    u32 ability = GetMonAbility(mon);   // we know our own party data
    enum ItemHoldEffect holdEffect;
    u32 species = GetMonData(mon, MON_DATA_SPECIES);
    u32 flags = gSideStatuses[GetBattlerSide(currBattler)] & (SIDE_STATUS_SPIKES | SIDE_STATUS_STEALTH_ROCK | SIDE_STATUS_STEELSURGE | SIDE_STATUS_STICKY_WEB | SIDE_STATUS_TOXIC_SPIKES);
    s32 hazardDamage = 0;
    u32 type1 = gSpeciesInfo[species].types[0];
    u32 type2 = gSpeciesInfo[species].types[1];
    u32 maxHp = GetMonData(mon, MON_DATA_MAX_HP);

    if (flags == 0)
        return FALSE;

    if (ability == ABILITY_MAGIC_GUARD)
        return FALSE;
    if (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM || ability == ABILITY_KLUTZ)
        holdEffect = HOLD_EFFECT_NONE;
    else
        holdEffect = gItemsInfo[GetMonData(mon, MON_DATA_HELD_ITEM)].holdEffect;
    if (holdEffect == HOLD_EFFECT_HEAVY_DUTY_BOOTS)
        return FALSE;

    if (flags & SIDE_STATUS_STEALTH_ROCK)
        hazardDamage += GetStealthHazardDamageByTypesAndHP(TYPE_SIDE_HAZARD_POINTED_STONES, type1, type2, maxHp);
    if ((flags & SIDE_STATUS_STEELSURGE))
        hazardDamage += GetStealthHazardDamageByTypesAndHP(TYPE_SIDE_HAZARD_SHARP_STEEL, type1, type2, maxHp);

    if (flags & SIDE_STATUS_SPIKES && ((type1 != TYPE_FLYING && type2 != TYPE_FLYING
        && ability != ABILITY_LEVITATE && holdEffect != HOLD_EFFECT_AIR_BALLOON)
        || holdEffect == HOLD_EFFECT_IRON_BALL || gFieldStatuses & STATUS_FIELD_GRAVITY))
    {
        s32 spikesDmg = maxHp / ((5 - gSideTimers[GetBattlerSide(currBattler)].spikesAmount) * 2);
        if (spikesDmg == 0)
            spikesDmg = 1;
        hazardDamage += spikesDmg;
    }

    if (hazardDamage >= GetMonData(mon, MON_DATA_HP))
        return TRUE;
    return FALSE;
}

enum AIPivot ShouldPivot(u32 battlerAtk, u32 battlerDef, u32 defAbility, u32 move, u32 moveIndex)
{
    bool32 hasStatBoost = AnyUsefulStatIsRaised(battlerAtk) || gBattleMons[battlerDef].statStages[STAT_EVASION] >= 9; //Significant boost in evasion for any class
    u32 battlerToSwitch;

    battlerToSwitch = gBattleStruct->AI_monToSwitchIntoId[battlerAtk];

    // Palafin always wants to activate Zero to Hero
    if (gBattleMons[battlerAtk].species == SPECIES_PALAFIN_ZERO
        && gBattleMons[battlerAtk].ability == ABILITY_ZERO_TO_HERO
        && CountUsablePartyMons(battlerAtk) != 0)
        return SHOULD_PIVOT;

    if (PartyBattlerShouldAvoidHazards(battlerAtk, battlerToSwitch))
        return DONT_PIVOT;

    if (!IsDoubleBattle())
    {
        if (CountUsablePartyMons(battlerAtk) == 0)
            return CAN_TRY_PIVOT; // can't switch, but attack might still be useful

        if (IsBattlerPredictedToSwitch(battlerDef))
            return SHOULD_PIVOT; // Try pivoting so you can switch to a better matchup to counter your new opponent

        if (AI_IsFaster(battlerAtk, battlerDef, move)) // Attacker goes first
        {
            if (!CanAIFaintTarget(battlerAtk, battlerDef, 0)) // Can't KO foe otherwise
            {
                if (CanAIFaintTarget(battlerAtk, battlerDef, 2))
                {
                    // attacker can kill target in two hits (theoretically)
                    if (CanTargetFaintAi(battlerDef, battlerAtk))
                        return SHOULD_PIVOT;   // Won't get the two turns, pivot

                    if (!IsBattleMoveStatus(move) && ((gAiLogicData->shouldSwitch & (1u << battlerAtk))
                        || (AI_BattlerAtMaxHp(battlerDef) && (gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_FOCUS_SASH
                        || (B_STURDY >= GEN_5 && defAbility == ABILITY_STURDY)
                        || defAbility == ABILITY_MULTISCALE
                        || defAbility == ABILITY_SHADOW_SHIELD))))
                        return SHOULD_PIVOT;   // pivot to break sash/sturdy/multiscale
                }
                else if (!hasStatBoost)
                {
                    if (!IsBattleMoveStatus(move) && (AI_BattlerAtMaxHp(battlerDef) && (gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_FOCUS_SASH
                        || (B_STURDY >= GEN_5 && defAbility == ABILITY_STURDY)
                        || defAbility == ABILITY_MULTISCALE
                        || defAbility == ABILITY_SHADOW_SHIELD)))
                        return SHOULD_PIVOT;   // pivot to break sash/sturdy/multiscale

                    if (gAiLogicData->shouldSwitch & (1u << battlerAtk))
                        return SHOULD_PIVOT;

                    /* TODO - check if switchable mon unafffected by/will remove hazards
                    if (gSideStatuses[battlerAtk] & SIDE_STATUS_SPIKES && switchScore >= SWITCHING_INCREASE_CAN_REMOVE_HAZARDS)
                        return SHOULD_PIVOT;*/

                    /*if (BattlerWillFaintFromSecondaryDamage(battlerAtk, gAiLogicData->abilities[battlerAtk]) && switchScore >= SWITCHING_INCREASE_WALLS_FOE)
                        return SHOULD_PIVOT;*/

                    /*if (IsClassDamager(class) && switchScore >= SWITCHING_INCREASE_HAS_SUPER_EFFECTIVE_MOVE)
                    {
                        bool32 physMoveInMoveset = PhysicalMoveInMoveset(battlerAtk);
                        bool32 specMoveInMoveset = SpecialMoveInMoveset(battlerAtk);

                        //Pivot if attacking stats are bad
                        if (physMoveInMoveset && !specMoveInMoveset)
                        {
                            if (STAT_STAGE_ATK < 6)
                                return SHOULD_PIVOT;
                        }
                        else if (!physMoveInMoveset && specMoveInMoveset)
                        {
                            if (STAT_STAGE_SPATK < 6)
                                return SHOULD_PIVOT;
                        }
                        else if (physMoveInMoveset && specMoveInMoveset)
                        {
                            if (STAT_STAGE_ATK < 6 && STAT_STAGE_SPATK < 6)
                                return SHOULD_PIVOT;
                        }

                        return SHOULD_PIVOT;
                    }*/
                }
            }
        }
        else // Opponent Goes First
        {
            if (CanTargetFaintAi(battlerDef, battlerAtk))
            {
                if (GetMoveEffect(move) == EFFECT_TELEPORT)
                    return DONT_PIVOT; // If you're going to faint because you'll go second, use a different move
                else
                    return CAN_TRY_PIVOT; // You're probably going to faint anyways so if for some reason you don't, better switch
            }
            else if (CanTargetFaintAiWithMod(battlerDef, battlerAtk, 0, 2)) // Foe can 2HKO AI
            {
                if (CanAIFaintTarget(battlerAtk, battlerDef, 0))
                {
                    if (!BattlerWillFaintFromSecondaryDamage(battlerAtk, gAiLogicData->abilities[battlerAtk]))
                        return CAN_TRY_PIVOT; // Use this move to KO if you must
                }
                else // Can't KO the foe
                {
                    return SHOULD_PIVOT;
                }
            }
            else // Foe can 3HKO+ AI
            {
                if (CanAIFaintTarget(battlerAtk, battlerDef, 0))
                {
                    if (!BattlerWillFaintFromSecondaryDamage(battlerAtk, gAiLogicData->abilities[battlerAtk]) // This is the only move that can KO
                      && !hasStatBoost) //You're not wasting a valuable stat boost
                    {
                        return CAN_TRY_PIVOT;
                    }
                }
                else if (CanAIFaintTarget(battlerAtk, battlerDef, 2))
                {
                    // can knock out foe in 2 hits
                    if (IsBattleMoveStatus(move) && ((gAiLogicData->shouldSwitch & (1u << battlerAtk)) //Damaging move
                      //&& (switchScore >= SWITCHING_INCREASE_RESIST_ALL_MOVES + SWITCHING_INCREASE_KO_FOE //remove hazards
                     || (gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_FOCUS_SASH && AI_BattlerAtMaxHp(battlerDef))))
                        return DONT_PIVOT; // Pivot to break the sash
                    else
                        return CAN_TRY_PIVOT;
                }
                else
                {
                    //if (IsClassDamager(class) && switchScore >= SWITCHING_INCREASE_KO_FOE)
                        //return SHOULD_PIVOT; //Only switch if way better matchup

                    if (!hasStatBoost)
                    {
                        // TODO - check if switching prevents/removes hazards
                        //if (gSideStatuses[battlerAtk] & SIDE_STATUS_SPIKES && switchScore >= SWITCHING_INCREASE_CAN_REMOVE_HAZARDS)
                            //return SHOULD_PIVOT;

                        // TODO - not always a good idea
                        //if (BattlerWillFaintFromSecondaryDamage(battlerAtk) && switchScore >= SWITCHING_INCREASE_HAS_SUPER_EFFECTIVE_MOVE)
                            //return SHOULD_PIVOT;

                        /*if (IsClassDamager(class) && switchScore >= SWITCHING_INCREASE_HAS_SUPER_EFFECTIVE_MOVE)
                        {
                            bool32 physMoveInMoveset = PhysicalMoveInMoveset(battlerAtk);
                            bool32 specMoveInMoveset = SpecialMoveInMoveset(battlerAtk);

                            //Pivot if attacking stats are bad
                            if (physMoveInMoveset && !specMoveInMoveset)
                            {
                                if (STAT_STAGE_ATK < 6)
                                    return SHOULD_PIVOT;
                            }
                            else if (!physMoveInMoveset && specMoveInMoveset)
                            {
                                if (STAT_STAGE_SPATK < 6)
                                    return SHOULD_PIVOT;
                            }
                            else if (physMoveInMoveset && specMoveInMoveset)
                            {
                                if (STAT_STAGE_ATK < 6 && STAT_STAGE_SPATK < 6)
                                    return SHOULD_PIVOT;
                            }
                        }*/

                        return CAN_TRY_PIVOT;
                    }
                }
            }
        }
    }

    return DONT_PIVOT;
}

bool32 CanKnockOffItem(u32 battler, u32 item)
{
    if (item == ITEM_NONE)
        return FALSE;

    if (!(gBattleTypeFlags & (BATTLE_TYPE_EREADER_TRAINER
      | BATTLE_TYPE_FRONTIER
      | BATTLE_TYPE_LINK
      | BATTLE_TYPE_RECORDED_LINK
      | BATTLE_TYPE_SECRET_BASE
      | (B_TRAINERS_KNOCK_OFF_ITEMS == TRUE ? BATTLE_TYPE_TRAINER : 0)
      )) && IsOnPlayerSide(battler))
        return FALSE;

    if (gAiLogicData->abilities[battler] == ABILITY_STICKY_HOLD)
        return FALSE;

    if (!CanBattlerGetOrLoseItem(battler, item))
        return FALSE;

    return TRUE;
}

// status checks
bool32 IsBattlerIncapacitated(u32 battler, u32 ability)
{
    if ((gBattleMons[battler].status1 & STATUS1_FREEZE) && !HasThawingMove(battler))
        return TRUE;    // if battler has thawing move we assume they will definitely use it, and thus being frozen should be neglected

    if (gBattleMons[battler].status1 & STATUS1_SLEEP && !HasMoveWithEffect(battler, EFFECT_SLEEP_TALK))
        return TRUE;

    if (gBattleMons[battler].status2 & STATUS2_RECHARGE || (ability == ABILITY_TRUANT && gDisableStructs[battler].truantCounter != 0))
        return TRUE;

    return FALSE;
}

bool32 AI_CanPutToSleep(u32 battlerAtk, u32 battlerDef, u32 defAbility, u32 move, u32 partnerMove)
{
    if (!CanBeSlept(battlerAtk, battlerDef, defAbility, BLOCKED_BY_SLEEP_CLAUSE)
      || DoesSubstituteBlockMove(battlerAtk, battlerDef, move)
      || PartnerMoveEffectIsStatusSameTarget(BATTLE_PARTNER(battlerAtk), battlerDef, partnerMove))   // shouldn't try to sleep mon that partner is trying to make sleep
        return FALSE;
    return TRUE;
}

static inline bool32 DoesBattlerBenefitFromAllVolatileStatus(u32 battler, u32 ability)
{
    if (ability == ABILITY_MARVEL_SCALE
     || ability == ABILITY_QUICK_FEET
     || ability == ABILITY_MAGIC_GUARD
     || (ability == ABILITY_GUTS && HasMoveWithCategory(battler, DAMAGE_CATEGORY_PHYSICAL))
     || HasMoveWithEffect(battler, EFFECT_FACADE)
     || HasMoveWithEffect(battler, EFFECT_PSYCHO_SHIFT))
        return TRUE;
    return FALSE;
}

bool32 ShouldPoison(u32 battlerAtk, u32 battlerDef)
{
    u32 abilityDef = gAiLogicData->abilities[battlerDef];
    // Battler can be poisoned and has move/ability that synergizes with being poisoned
    if (CanBePoisoned(battlerAtk, battlerDef, gAiLogicData->abilities[battlerAtk], abilityDef) && (
        DoesBattlerBenefitFromAllVolatileStatus(battlerDef, abilityDef)
        || abilityDef == ABILITY_POISON_HEAL
        || (abilityDef == ABILITY_TOXIC_BOOST && HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_PHYSICAL))))
    {
        if (battlerAtk == battlerDef) // Targeting self
            return TRUE;
        else
            return FALSE;
    }
    if (battlerAtk == battlerDef)
        return FALSE;
    else
        return TRUE;
}

bool32 ShouldBurn(u32 battlerAtk, u32 battlerDef, u32 abilityDef)
{
    // Battler can be burned and has move/ability that synergizes with being burned
    if (CanBeBurned(battlerAtk, battlerDef, abilityDef) && (
        DoesBattlerBenefitFromAllVolatileStatus(battlerDef, abilityDef)
        || abilityDef == ABILITY_HEATPROOF
        || (abilityDef == ABILITY_FLARE_BOOST && HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_SPECIAL))))
    {
        if (battlerAtk == battlerDef) // Targeting self
            return TRUE;
        else
            return FALSE;
    }

    if (battlerAtk == battlerDef)
        return FALSE;
    else
        return TRUE;
}

bool32 ShouldFreezeOrFrostbite(u32 battlerAtk, u32 battlerDef, u32 abilityDef)
{
    if (!B_USE_FROSTBITE)
    {
        if (CanBeFrozen(battlerAtk, battlerDef, abilityDef))
        {
            if (battlerAtk == battlerDef) // Targeting self
                return FALSE;
            else
                return TRUE;
        }
        return FALSE;
    }
    else
    {
        // Battler can be frostbitten and has move/ability that synergizes with being frostbitten
        if (CanBeFrozen(battlerAtk, battlerDef, abilityDef)
            && DoesBattlerBenefitFromAllVolatileStatus(battlerDef, abilityDef))
        {
            if (battlerAtk == battlerDef) // Targeting self
                return TRUE;
            else
                return FALSE;
        }

        if (battlerAtk == battlerDef)
            return FALSE;
        else
            return TRUE;
    }
}

bool32 ShouldParalyze(u32 battlerAtk, u32 battlerDef, u32 abilityDef)
{
    // Battler can be paralyzed and has move/ability that synergizes with being paralyzed
    if (CanBeParalyzed(battlerAtk, battlerDef, abilityDef) && (
        DoesBattlerBenefitFromAllVolatileStatus(battlerDef, abilityDef)))
    {
        if (battlerAtk == battlerDef) // Targeting self
            return TRUE;
        else
            return FALSE;
    }
    if (battlerAtk == battlerDef)
        return FALSE;
    else
        return TRUE;
}

bool32 AI_CanPoison(u32 battlerAtk, u32 battlerDef, u32 defAbility, u32 move, u32 partnerMove)
{
    if (!CanBePoisoned(battlerAtk, battlerDef, gAiLogicData->abilities[battlerAtk], defAbility)
      || gAiLogicData->effectiveness[battlerAtk][battlerDef][gAiThinkingStruct->movesetIndex] == UQ_4_12(0.0)
      || DoesSubstituteBlockMove(battlerAtk, battlerDef, move)
      || PartnerMoveEffectIsStatusSameTarget(BATTLE_PARTNER(battlerAtk), battlerDef, partnerMove))
        return FALSE;

    return TRUE;
}

bool32 AI_CanParalyze(u32 battlerAtk, u32 battlerDef, u32 defAbility, u32 move, u32 partnerMove)
{
    if (!CanBeParalyzed(battlerAtk, battlerDef, defAbility)
      || gAiLogicData->effectiveness[battlerAtk][battlerDef][gAiThinkingStruct->movesetIndex] == UQ_4_12(0.0)
      || DoesSubstituteBlockMove(battlerAtk, battlerDef, move)
      || PartnerMoveEffectIsStatusSameTarget(BATTLE_PARTNER(battlerAtk), battlerDef, partnerMove)
      || gFieldStatuses & STATUS_FIELD_MUDSPORT
      )
      
        return FALSE;
    return TRUE;
}

bool32 AI_CanBeConfused(u32 battlerAtk, u32 battlerDef, u32 move, u32 ability)
{
    if ((gBattleMons[battlerDef].status2 & STATUS2_CONFUSION)
     || (ability == ABILITY_OWN_TEMPO && !DoesBattlerIgnoreAbilityChecks(battlerAtk, gAiLogicData->abilities[battlerAtk], move))
     || IsBattlerTerrainAffected(battlerDef, STATUS_FIELD_MISTY_TERRAIN)
     || gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_SAFEGUARD
     || DoesSubstituteBlockMove(battlerAtk, battlerDef, move))
        return FALSE;
    return TRUE;
}

bool32 AI_CanConfuse(u32 battlerAtk, u32 battlerDef, u32 defAbility, u32 battlerAtkPartner, u32 move, u32 partnerMove)
{
    if (GetBattlerMoveTargetType(battlerAtk, move) == MOVE_TARGET_FOES_AND_ALLY
     && AI_CanBeConfused(battlerAtk, battlerDef, move, defAbility)
     && !AI_CanBeConfused(battlerAtk, BATTLE_PARTNER(battlerDef), move, gAiLogicData->abilities[BATTLE_PARTNER(battlerDef)]))
        return FALSE;

    if (!AI_CanBeConfused(battlerAtk, battlerDef, move, defAbility)
     || DoesPartnerHaveSameMoveEffect(battlerAtkPartner, battlerDef, move, partnerMove))
        return FALSE;

    return TRUE;
}

bool32 AI_CanBurn(u32 battlerAtk, u32 battlerDef, u32 defAbility, u32 battlerAtkPartner, u32 move, u32 partnerMove)
{
    if (!CanBeBurned(battlerAtk, battlerDef, defAbility)
      || gAiLogicData->effectiveness[battlerAtk][battlerDef][gAiThinkingStruct->movesetIndex] == UQ_4_12(0.0)
      || DoesSubstituteBlockMove(battlerAtk, battlerDef, move)
      || PartnerMoveEffectIsStatusSameTarget(battlerAtkPartner, battlerDef, partnerMove)
      || gFieldStatuses & STATUS_FIELD_WATERSPORT)
    {
        return FALSE;
    }
    return TRUE;
}

bool32 AI_CanGiveFrostbite(u32 battlerAtk, u32 battlerDef, u32 defAbility, u32 battlerAtkPartner, u32 move, u32 partnerMove)
{
    if (!CanBeFrozen(battlerAtk, battlerDef, defAbility)
      || gAiLogicData->effectiveness[battlerAtk][battlerDef][gAiThinkingStruct->movesetIndex] == UQ_4_12(0.0)
      || DoesSubstituteBlockMove(battlerAtk, battlerDef, move)
      || PartnerMoveEffectIsStatusSameTarget(battlerAtkPartner, battlerDef, partnerMove))
    {
        return FALSE;
    }
    return TRUE;
}

bool32 AI_CanBeInfatuated(u32 battlerAtk, u32 battlerDef, u32 defAbility)
{
    if ((gBattleMons[battlerDef].status2 & STATUS2_INFATUATION)
      || gAiLogicData->effectiveness[battlerAtk][battlerDef][gAiThinkingStruct->movesetIndex] == UQ_4_12(0.0)
      || defAbility == ABILITY_OBLIVIOUS
      || !AreBattlersOfOppositeGender(battlerAtk, battlerDef)
      || AI_IsAbilityOnSide(battlerDef, ABILITY_AROMA_VEIL))
        return FALSE;
    return TRUE;
}

u32 ShouldTryToFlinch(u32 battlerAtk, u32 battlerDef, u32 atkAbility, u32 defAbility, u32 move)
{
    if (((!IsMoldBreakerTypeAbility(battlerAtk, gAiLogicData->abilities[battlerAtk]) && (defAbility == ABILITY_SHIELD_DUST || defAbility == ABILITY_COVERED || defAbility == ABILITY_INNER_FOCUS))
      || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_COVERT_CLOAK
      || DoesSubstituteBlockMove(battlerAtk, battlerDef, move)
      || AI_IsSlower(battlerAtk, battlerDef, move))) // Opponent goes first
    {
        return 0;
    }
    else if ((atkAbility == ABILITY_SERENE_GRACE
      || gBattleMons[battlerDef].status1 & STATUS1_PARALYSIS
      || gBattleMons[battlerDef].status2 & STATUS2_INFATUATION
      || gBattleMons[battlerDef].status2 & STATUS2_CONFUSION)
      || ((AI_IsFaster(battlerAtk, battlerDef, move)) && CanTargetFaintAi(battlerDef, battlerAtk)))
    {
        return 2;   // good idea to flinch
    }

    return 0;   // don't try to flinch
}

bool32 ShouldTrap(u32 battlerAtk, u32 battlerDef, u32 move)
{
    if (AI_CanBattlerEscape(battlerDef))
        return FALSE;

    if (IsBattlerTrapped(battlerAtk, battlerDef))
        return FALSE;

    if (BattlerWillFaintFromSecondaryDamage(battlerDef, gAiLogicData->abilities[battlerDef]))
        return TRUE;    // battler is taking secondary damage with low HP

    if (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_STALL)
    {
        if (!CanTargetFaintAi(battlerDef, battlerAtk))
            return TRUE;    // attacker goes first and opponent can't kill us
    }

    return FALSE;
}

bool32 ShouldFakeOut(u32 battlerAtk, u32 battlerDef, u32 move)
{
    if ((!gDisableStructs[battlerAtk].isFirstTurn && MoveHasAdditionalEffectWithChance(move, MOVE_EFFECT_FLINCH, 100))
    || gAiLogicData->abilities[battlerAtk] == ABILITY_GORILLA_TACTICS
    || gAiLogicData->holdEffects[battlerAtk] == HOLD_EFFECT_CHOICE_BAND
    || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_COVERT_CLOAK
    || DoesSubstituteBlockMove(battlerAtk, battlerDef, move)
    || (!IsMoldBreakerTypeAbility(battlerAtk, gAiLogicData->abilities[battlerAtk])
    && (gAiLogicData->abilities[battlerDef] == ABILITY_SHIELD_DUST || gAiLogicData->abilities[battlerDef] == ABILITY_COVERED || gAiLogicData->abilities[battlerDef] == ABILITY_INNER_FOCUS)))
        return FALSE;

    return TRUE;
}

u32 FindMoveUsedXTurnsAgo(u32 battlerId, u32 x)
{
    s32 i, index = gBattleHistory->moveHistoryIndex[battlerId];
    for (i = 0; i < x; i++)
    {
        if (--index < 0)
            index = AI_MOVE_HISTORY_COUNT - 1;
    }
    return gBattleHistory->moveHistory[battlerId][index];
}

bool32 IsWakeupTurn(u32 battler)
{
    // Check if rest was used 2 turns ago
    if ((gBattleMons[battler].status1 & STATUS1_SLEEP) == 1 && GetMoveEffect(FindMoveUsedXTurnsAgo(battler, 2)) == EFFECT_REST)
        return TRUE;
    else // no way to know
        return FALSE;
}

bool32 AnyPartyMemberStatused(u32 battlerId, bool32 checkSoundproof)
{
    struct Pokemon *party;
    u32 i, battlerOnField1, battlerOnField2;

    party = GetBattlerParty(battlerId);

    if (IsDoubleBattle())
    {
        battlerOnField1 = gBattlerPartyIndexes[battlerId];
        battlerOnField2 = gBattlerPartyIndexes[GetPartnerBattler(battlerId)];
        // Check partner's status
        if ((GetGenConfig(GEN_CONFIG_HEAL_BELL_SOUNDPROOF) == GEN_5
            || gAiLogicData->abilities[BATTLE_PARTNER(battlerId)] != ABILITY_SOUNDPROOF
            || !checkSoundproof)
         && GetMonData(&party[battlerOnField2], MON_DATA_STATUS) != STATUS1_NONE)
            return TRUE;
    }
    else // In singles there's only one battlerId by side.
    {
        battlerOnField1 = gBattlerPartyIndexes[battlerId];
        battlerOnField2 = gBattlerPartyIndexes[battlerId];
    }

    // Check attacker's status
    if ((GetGenConfig(GEN_CONFIG_HEAL_BELL_SOUNDPROOF) == GEN_5
      || GetGenConfig(GEN_CONFIG_HEAL_BELL_SOUNDPROOF) >= GEN_8
      || gAiLogicData->abilities[battlerId] != ABILITY_SOUNDPROOF || !checkSoundproof)
     && GetMonData(&party[battlerOnField1], MON_DATA_STATUS) != STATUS1_NONE)
        return TRUE;

    // Check inactive party mons' status
    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (i == battlerOnField1 || i == battlerOnField2)
            continue;
        if (GetGenConfig(GEN_CONFIG_HEAL_BELL_SOUNDPROOF) < GEN_5
         && checkSoundproof
         && GetMonAbility(&party[i]) == ABILITY_SOUNDPROOF)
            continue;
        if (GetMonData(&party[i], MON_DATA_STATUS) != STATUS1_NONE)
            return TRUE;
    }

    return FALSE;
}

u32 GetBattlerSideSpeedAverage(u32 battler)
{
    u32 speed1 = 0;
    u32 speed2 = 0;
    u32 numBattlersAlive = 0;

    if (IsBattlerAlive(battler))
    {
        speed1 = gAiLogicData->speedStats[battler];
        numBattlersAlive++;
    }

    if (IsDoubleBattle() && IsBattlerAlive(BATTLE_PARTNER(battler)))
    {
        speed2 = gAiLogicData->speedStats[BATTLE_PARTNER(battler)];
        numBattlersAlive++;
    }

    return (speed1 + speed2) / numBattlersAlive;
}

bool32 ShouldUseRecoilMove(u32 battlerAtk, u32 battlerDef, u32 recoilDmg, u32 moveIndex)
{
    if (recoilDmg >= gBattleMons[battlerAtk].hp //Recoil kills attacker
      && CountUsablePartyMons(battlerDef) != 0) //Foe has more than 1 target left
    {
        if (recoilDmg >= gBattleMons[battlerDef].hp && !CanAIFaintTarget(battlerAtk, battlerDef, 0))
            return TRUE; //If it's the only KO move then just use it
        else
            return FALSE; //Not as good to use move if you'll faint and not win
    }

    return TRUE;
}

bool32 ShouldAbsorb(u32 battlerAtk, u32 battlerDef, u32 move, s32 damage)
{
    if (move == 0xFFFF || AI_IsFaster(battlerAtk, battlerDef, move))
    {
        // using item or user goes first
        s32 healDmg = (GetMoveAbsorbPercentage(move) * damage) / 100;

        if (gStatuses3[battlerAtk] & STATUS3_HEAL_BLOCK)
            healDmg = 0;

        if (CanTargetFaintAi(battlerDef, battlerAtk)
          && !CanTargetFaintAiWithMod(battlerDef, battlerAtk, healDmg, 0))
            return TRUE;    // target can faint attacker unless they heal
        else if (!CanTargetFaintAi(battlerDef, battlerAtk) && gAiLogicData->hpPercents[battlerAtk] < 60 && (Random() % 3))
            return TRUE;    // target can't faint attacker at all, attacker health is about half, 2/3rds rate of encouraging healing
    }
    else
    {
        // opponent goes first
        if (!CanTargetFaintAi(battlerDef, battlerAtk))
            return TRUE;
    }

    return FALSE;
}

//Get the number of times in a row a given moveEffect has been used.
u32 GetConsecutiveMoveEffectUse(u32 battler, u32 moveEffect){
    u32 numUses = 0;
    u32 prevTurnNum;
    for (prevTurnNum = 1; prevTurnNum <= AI_MOVE_HISTORY_COUNT; prevTurnNum++){
        if (moveEffect == GetMoveEffect(FindMoveUsedXTurnsAgo(battler, prevTurnNum))){
            numUses++;
        }
        //Stop after the first miss
        else{
            break;
        }
    }
    return numUses;
}



bool32 ShouldRecover(u32 battlerAtk, u32 battlerDef, u32 move, u32 healPercent, enum DamageCalcContext calcContext)
{
    s32 healAmount = (healPercent * gBattleMons[battlerAtk].maxHP) / 100;
    u32 consecutiveMoveEffectUse = 0; 
    
    if (gStatuses3[battlerAtk] & STATUS3_HEAL_BLOCK){
        return FALSE;
    }

    if (move != 0 && move != 0xFFFF){
        consecutiveMoveEffectUse = GetConsecutiveMoveEffectUse(battlerAtk, GetMoveEffect(move));
    }
    

    //Ignore recovering if mon gets outdamaged
    //this may need to be tweaked for stall strats such as Toxic or Leech Seed
    if (GetBestDmgFromBattler(battlerDef, battlerAtk, AI_DEFENDING) > healAmount){
        return FALSE;
    }

    //Sliding disincentive for multiple consecutive uses; 33% chance to not use if used the previous turn; 100% chance to not use if used 3 turns in a row.
    //This may also need to be tweaked for stall strats
    if (AI_RandLessThan(85 * consecutiveMoveEffectUse)){
        return FALSE;
    }

    if (move == 0xFFFF || AI_IsFaster(battlerAtk, battlerDef, move))
    {
        // using item or user going first

        //Removing damage for now; originally `s32 healAmount = (healPercent * damage) / 100;` was being used,
        //But I don't understand why this is being done.
        // s32 damage = AI_GetDamage(battlerAtk, battlerDef, gAiThinkingStruct->movesetIndex, calcContext, gAiLogicData);

        if (CanTargetFaintAi(battlerDef, battlerAtk)
          && !CanTargetFaintAiWithMod(battlerDef, battlerAtk, healAmount, 0))
            return TRUE;    // target can faint attacker unless they heal
        else if (!CanTargetFaintAi(battlerDef, battlerAtk) && gAiLogicData->hpPercents[battlerAtk] < 60 && (AI_RandLessThan(85))){
            // DebugPrintf("Faster RNG check is reached");
            return TRUE;    // target can't faint attacker at all, attacker health is about half, 1/3rds rate of encouraging healing
        }
            
    }
    //Logic for slower AI
    if (gAiLogicData->hpPercents[battlerAtk] < 50){
        return TRUE;
    }
    //~50% chance to heal when about less then 2/3 HP and slower
    if (gAiLogicData->hpPercents[battlerAtk] < 65 && AI_RandLessThan(127)){
        return TRUE;
    }
    return FALSE;
}

bool32 ShouldSetScreen(u32 battlerAtk, u32 battlerDef, enum BattleMoveEffects moveEffect)
{
    u32 atkSide = GetBattlerSide(battlerAtk);
    // Don't waste a turn if screens will be broken
    if (HasMoveWithEffect(battlerDef, EFFECT_BRICK_BREAK)
     || HasMoveWithEffect(battlerDef, EFFECT_RAGING_BULL
    || HasMoveWithEffect(battlerDef, EFFECT_DEFOG))){
        if (GetConsecutiveMoveEffectUse(battlerDef, EFFECT_BRICK_BREAK) >= 2 
        || GetConsecutiveMoveEffectUse(battlerDef, EFFECT_RAGING_BULL) >= 2
        || GetConsecutiveMoveEffectUse(battlerDef, EFFECT_DEFOG) >= 2){
            // DebugPrintf("Double use check is reached");
            return FALSE; 
        }
        else if (AI_RandLessThan(127)){//Otherwise just a 50% chance to not incentivize
            // DebugPrintf("50 percent RNG check is reached");
            return FALSE;
        }
     }
        

    switch (moveEffect)
    {
    case EFFECT_AURORA_VEIL:
        // Use only in Hail and only if AI doesn't already have Reflect, Light Screen or Aurora Veil itself active.
        if ((AI_GetWeather() & (B_WEATHER_HAIL | B_WEATHER_SNOW))
            && !(gSideStatuses[atkSide] & (SIDE_STATUS_REFLECT | SIDE_STATUS_LIGHTSCREEN | SIDE_STATUS_AURORA_VEIL)))
            return TRUE;
        break;
    case EFFECT_REFLECT:
        if (gSideStatuses[atkSide] & SIDE_STATUS_REFLECT){
            return FALSE;
        }
        // Gauge use on either whether the opponent has revealed a move of the split, or best fit on the player mon's stats
        if ((HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_PHYSICAL))
        //Estimate based on raw stats when lacking move knowledge
        || (!HasAllKnownMoves(battlerDef) && !HasDamagingMove(battlerDef) && (UQ_4_12_TO_INT(gBattleMons[battlerDef].attack * GetAtkSpAtkGapThreshold(battlerDef)) >= gBattleMons[battlerDef].spAttack)
            && !(gSideStatuses[atkSide] & SIDE_STATUS_REFLECT)))
            return TRUE;
        break;
    case EFFECT_LIGHT_SCREEN:
        if (gSideStatuses[atkSide] & SIDE_STATUS_LIGHTSCREEN){
            return FALSE;
        }

        // Gauge use on either whether the opponent has revealed a move of the split, or best fit on the player mon's stats
        if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_SPECIAL)
        || (!HasAllKnownMoves(battlerDef) && !HasDamagingMove(battlerDef) 
        && (UQ_4_12_TO_INT(gBattleMons[battlerDef].spAttack * GetAtkSpAtkGapThreshold(battlerDef)) >= gBattleMons[battlerDef].attack)))
            return TRUE;
        break;
    default:
        break;
    }

    return FALSE;
}

// Partner Logic
bool32 IsValidDoubleBattle(u32 battlerAtk)
{
    if (IsDoubleBattle()
      && ((IsBattlerAlive(BATTLE_OPPOSITE(battlerAtk)) && IsBattlerAlive(BATTLE_PARTNER(BATTLE_OPPOSITE(battlerAtk)))) || IsBattlerAlive(BATTLE_PARTNER(battlerAtk))))
        return TRUE;
    return FALSE;
}

bool32 OnlyOnePlayerDoublesMon(){
    u32 playerBattler1 = 0;
    u32 playerBattler2;

    if (!IsDoubleBattle()){
        return FALSE;
    }
    playerBattler2 = BATTLE_PARTNER(playerBattler1);

    return !IsBattlerAlive(playerBattler1) || !IsBattlerAlive(playerBattler2); 
}

u32 GetAllyChosenMove(u32 battlerId)
{
    u32 partnerBattler = BATTLE_PARTNER(battlerId);

    if (!IsBattlerAlive(partnerBattler) || !IsAiBattlerAware(partnerBattler))
        return MOVE_NONE;
    else if (partnerBattler > battlerId) // Battler with the lower id chooses the move first.
    //NOTE: For now, I decided to remove guessing based on the previous move used by the partner.
    //Probably best of the lower index mon to make a separate decision. 
    //But there may be considerations based on what moves the ally has.      
    // return gLastMoves[partnerBattler];
        return MOVE_NONE;
    else
        return gBattleMons[partnerBattler].moves[gBattleStruct->chosenMovePositions[partnerBattler]];
}

//PARTNER_MOVE_EFFECT_IS_SAME
bool32 DoesPartnerHaveSameMoveEffect(u32 battlerAtkPartner, u32 battlerDef, u32 move, u32 partnerMove)
{
    if (!IsDoubleBattle())
        return FALSE;

    if (GetMoveEffect(move) == GetMoveEffect(partnerMove)
      && partnerMove != MOVE_NONE
      && gBattleStruct->moveTarget[battlerAtkPartner] == battlerDef)
    {
        return TRUE;
    }
    return FALSE;
}

//PARTNER_MOVE_EFFECT_IS_SAME_NO_TARGET
bool32 PartnerHasSameMoveEffectWithoutTarget(u32 battlerAtkPartner, u32 move, u32 partnerMove)
{
    if (!IsDoubleBattle())
        return FALSE;

    if (GetMoveEffect(move) == GetMoveEffect(partnerMove)
      && partnerMove != MOVE_NONE)
        return TRUE;
    return FALSE;
}

//PARTNER_MOVE_EFFECT_IS_STATUS_SAME_TARGET
bool32 PartnerMoveEffectIsStatusSameTarget(u32 battlerAtkPartner, u32 battlerDef, u32 partnerMove)
{
    if (!IsDoubleBattle())
        return FALSE;

    enum BattleMoveEffects partnerEffect = GetMoveEffect(partnerMove);
    u32 nonVolatileStatus = GetMoveNonVolatileStatus(partnerMove);
    if (partnerMove != MOVE_NONE
     && gBattleStruct->moveTarget[battlerAtkPartner] == battlerDef
     && (nonVolatileStatus == MOVE_EFFECT_POISON
       || nonVolatileStatus == MOVE_EFFECT_TOXIC
       || nonVolatileStatus == MOVE_EFFECT_SLEEP
       || nonVolatileStatus == MOVE_EFFECT_PARALYSIS
       || nonVolatileStatus == MOVE_EFFECT_BURN
       || partnerEffect == EFFECT_YAWN))
        return TRUE;
    return FALSE;
}

bool32 IsMoveEffectWeather(u32 move)
{
    enum BattleMoveEffects effect = GetMoveEffect(move);
    if (move != MOVE_NONE
     && (effect == EFFECT_SUNNY_DAY
      || effect == EFFECT_RAIN_DANCE
      || effect == EFFECT_SANDSTORM
      || effect == EFFECT_HAIL
      || effect == EFFECT_SNOWSCAPE
      || effect == EFFECT_CHILLY_RECEPTION))
        return TRUE;
    return FALSE;
}

//PARTNER_MOVE_EFFECT_IS_TERRAIN
bool32 PartnerMoveEffectIsTerrain(u32 battlerAtkPartner, u32 partnerMove)
{
    if (!IsDoubleBattle())
        return FALSE;

    enum BattleMoveEffects partnerEffect = GetMoveEffect(partnerMove);
    if (partnerMove != MOVE_NONE
     && (partnerEffect == EFFECT_GRASSY_TERRAIN
      || partnerEffect == EFFECT_MISTY_TERRAIN
      || partnerEffect == EFFECT_ELECTRIC_TERRAIN
      || partnerEffect == EFFECT_PSYCHIC_TERRAIN))
        return TRUE;

    return FALSE;
}

//PARTNER_MOVE_EFFECT_IS
bool32 PartnerMoveEffectIs(u32 battlerAtkPartner, u32 partnerMove, enum BattleMoveEffects effectCheck)
{
    if (!IsDoubleBattle())
        return FALSE;

    if (partnerMove != MOVE_NONE && GetMoveEffect(partnerMove) == effectCheck)
        return TRUE;

    return FALSE;
}

//PARTNER_MOVE_IS_TAILWIND_TRICKROOM
bool32 PartnerMoveIs(u32 battlerAtkPartner, u32 partnerMove, u32 moveCheck)
{
    if (!IsDoubleBattle())
        return FALSE;

    if (partnerMove != MOVE_NONE && partnerMove == moveCheck)
        return TRUE;
    return FALSE;
}

//PARTNER_MOVE_IS_SAME
bool32 PartnerMoveIsSameAsAttacker(u32 battlerAtkPartner, u32 battlerDef, u32 move, u32 partnerMove)
{
    if (!IsDoubleBattle())
        return FALSE;

    if (partnerMove != MOVE_NONE && move == partnerMove && gBattleStruct->moveTarget[battlerAtkPartner] == battlerDef)
        return TRUE;
    return FALSE;
}

//PARTNER_MOVE_IS_SAME_NO_TARGET
bool32 PartnerMoveIsSameNoTarget(u32 battlerAtkPartner, u32 move, u32 partnerMove)
{
    if (!IsDoubleBattle())
        return FALSE;
    if (partnerMove != MOVE_NONE && move == partnerMove)
        return TRUE;
    return FALSE;
}

bool32 PartnerMoveActivatesSleepClause(u32 partnerMove)
{
    if (!IsDoubleBattle() || !IsSleepClauseEnabled())
        return FALSE;
    return IsMoveSleepClauseTrigger(partnerMove);
}

bool32 ShouldUseWishAromatherapy(u32 battlerAtk, u32 battlerDef, u32 move)
{
    u32 i;
    s32 firstId, lastId;
    struct Pokemon* party;
    bool32 hasStatus = AnyPartyMemberStatused(battlerAtk, IsSoundMove(move));
    bool32 needHealing = FALSE;

    GetAIPartyIndexes(battlerAtk, &firstId, &lastId);
    party = GetBattlerParty(battlerAtk);

    if (CountUsablePartyMons(battlerAtk) == 0
      && (CanTargetFaintAi(battlerDef, battlerAtk) || BattlerWillFaintFromSecondaryDamage(battlerAtk, gAiLogicData->abilities[battlerAtk])))
        return FALSE; // Don't heal if last mon and will faint

    for (i = 0; i < PARTY_SIZE; i++)
    {
        u32 currHp = GetMonData(&party[i], MON_DATA_HP);
        u32 maxHp = GetMonData(&party[i], MON_DATA_MAX_HP);

        if (!GetMonData(&party[i], MON_DATA_IS_EGG, NULL) && currHp > 0)
        {
            if ((currHp * 100) / maxHp < 65 // Less than 65% health remaining
              && i >= firstId && i < lastId) // Can only switch to mon on your team
            {
                needHealing = TRUE;
            }
        }
    }

    if (!IsDoubleBattle())
    {
        switch (GetMoveEffect(move))
        {
        case EFFECT_WISH:
            if (needHealing)
                return TRUE;
            break;
        case EFFECT_HEAL_BELL:
            if (hasStatus)
                return TRUE;
            break;
        default:
            break;
        }
    }
    else
    {
        switch (GetMoveEffect(move))
        {
        case EFFECT_WISH:
            return ShouldRecover(battlerAtk, battlerDef, move, 50, AI_DEFENDING); // Switch recovery isn't good idea in doubles
        case EFFECT_HEAL_BELL:
            if (hasStatus)
                return TRUE;
            break;
        default:
            break;
        }
    }

    return FALSE;
}

#define SIZE_G_BATTLE_MONS (sizeof(struct BattlePokemon) * MAX_BATTLERS_COUNT)

struct BattlePokemon *AllocSaveBattleMons(void)
{
    struct BattlePokemon *savedBattleMons = Alloc(SIZE_G_BATTLE_MONS);
    memcpy(savedBattleMons, gBattleMons, SIZE_G_BATTLE_MONS);
    return savedBattleMons;
}

void FreeRestoreBattleMons(struct BattlePokemon *savedBattleMons)
{
    memcpy(gBattleMons, savedBattleMons, SIZE_G_BATTLE_MONS);
    Free(savedBattleMons);
}

// party logic
s32 AI_CalcPartyMonDamage(u32 move, u32 battlerAtk, u32 battlerDef, struct BattlePokemon switchinCandidate, enum DamageCalcContext calcContext)
{
    struct SimulatedDamage dmg;
    uq4_12_t effectiveness;
    struct BattlePokemon *savedBattleMons = AllocSaveBattleMons();

    if (calcContext == AI_ATTACKING)
    {
        gBattleMons[battlerAtk] = switchinCandidate;
        gAiThinkingStruct->saved[battlerDef].saved = TRUE;
        SetBattlerAiData(battlerAtk, gAiLogicData); // set known opposing battler data
        gAiThinkingStruct->saved[battlerDef].saved = FALSE;
    }
    else if (calcContext == AI_DEFENDING)
    {
        gBattleMons[battlerDef] = switchinCandidate;
        gAiThinkingStruct->saved[battlerAtk].saved = TRUE;
        SetBattlerAiData(battlerDef, gAiLogicData); // set known opposing battler data
        gAiThinkingStruct->saved[battlerAtk].saved = FALSE;
    }

    dmg = AI_CalcDamage(move, battlerAtk, battlerDef, &effectiveness, FALSE, AI_GetWeather());

    // restores original gBattleMon struct
    FreeRestoreBattleMons(savedBattleMons);

    if (calcContext == AI_ATTACKING)
    {
        SetBattlerAiData(battlerAtk, gAiLogicData);
        if (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_RISKY && !(gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_CONSERVATIVE))
            return dmg.maximum;
        else if (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_CONSERVATIVE && !(gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_RISKY))
            return dmg.minimum;
        else
            return dmg.median;
    }

    else if (calcContext == AI_DEFENDING)
    {
        SetBattlerAiData(battlerDef, gAiLogicData);
        if (gAiThinkingStruct->aiFlags[battlerDef] & AI_FLAG_RISKY && !(gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_CONSERVATIVE))
            return dmg.minimum;
        else if (gAiThinkingStruct->aiFlags[battlerDef] & AI_FLAG_CONSERVATIVE && !(gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_RISKY))
            return dmg.maximum;
        else
            return dmg.median;
    }

    return dmg.median;
}

u32 AI_WhoStrikesFirstPartyMon(u32 battlerAtk, u32 battlerDef, struct BattlePokemon switchinCandidate, u32 moveConsidered)
{
    struct BattlePokemon *savedBattleMons = AllocSaveBattleMons();
    gBattleMons[battlerAtk] = switchinCandidate;

    SetBattlerAiData(battlerAtk, gAiLogicData);
    u32 aiMonFaster = AI_IsFaster(battlerAtk, battlerDef, moveConsidered);
    FreeRestoreBattleMons(savedBattleMons);
    SetBattlerAiData(battlerAtk, gAiLogicData);

    return aiMonFaster;
}

s32 CountUsablePartyMons(u32 battlerId)
{
    s32 battlerOnField1, battlerOnField2, i, ret;
    struct Pokemon *party;
    party = GetBattlerParty(battlerId);

    if (IsDoubleBattle())
    {
        battlerOnField1 = gBattlerPartyIndexes[battlerId];
        battlerOnField2 = gBattlerPartyIndexes[GetPartnerBattler(battlerId)];
    }
    else // In singles there's only one battlerId by side.
    {
        battlerOnField1 = gBattlerPartyIndexes[battlerId];
        battlerOnField2 = gBattlerPartyIndexes[battlerId];
    }

    ret = 0;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (i != battlerOnField1 && i != battlerOnField2
         && GetMonData(&party[i], MON_DATA_HP) != 0
         && GetMonData(&party[i], MON_DATA_SPECIES_OR_EGG) != SPECIES_NONE
         && GetMonData(&party[i], MON_DATA_SPECIES_OR_EGG) != SPECIES_EGG)
        {
            ret++;
        }
    }

    return ret;
}

bool32 IsPartyFullyHealedExceptBattler(u32 battlerId)
{
    struct Pokemon *party;
    u32 i;
    party = GetBattlerParty(battlerId);

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (i != gBattlerPartyIndexes[battlerId]
         && GetMonData(&party[i], MON_DATA_HP) != 0
         && GetMonData(&party[i], MON_DATA_SPECIES_OR_EGG) != SPECIES_NONE
         && GetMonData(&party[i], MON_DATA_SPECIES_OR_EGG) != SPECIES_EGG
         && GetMonData(&party[i], MON_DATA_HP) < GetMonData(&party[i], MON_DATA_MAX_HP))
            return FALSE;
    }
    return TRUE;
}

bool32 PartyHasMoveCategory(u32 battlerId, u32 category)
{
    struct Pokemon *party = GetBattlerParty(battlerId);
    u32 i, j;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&party[i], MON_DATA_HP, NULL) == 0)
            continue;

        for (j = 0; j < MAX_MON_MOVES; j++)
        {
            u32 move = GetMonData(&party[i], MON_DATA_MOVE1 + j, NULL);
            u32 pp = GetMonData(&party[i], MON_DATA_PP1 + j, NULL);

            if (pp > 0 && move != MOVE_NONE)
            {
                //TODO - handle photon geyser, light that burns the sky
                if (GetMoveCategory(move) == category)
                    return TRUE;
            }
        }
    }

    return FALSE;
}

bool32 SideHasMoveCategory(u32 battlerId, u32 category)
{
    if (IsDoubleBattle())
    {
        if (HasMoveWithCategory(battlerId, category) || HasMoveWithCategory(BATTLE_PARTNER(battlerId), category))
            return TRUE;
    }
    else
    {
        if (HasMoveWithCategory(battlerId, category))
            return TRUE;
    }
    return FALSE;
}

bool32 IsAbilityOfRating(u32 ability, s8 rating)
{
    if (gAbilitiesInfo[ability].aiRating >= rating)
        return TRUE;
    return FALSE;
}

static const u16 sRecycleEncouragedItems[] =
{
    ITEM_CHESTO_BERRY,
    ITEM_LUM_BERRY,
    ITEM_STARF_BERRY,
    ITEM_SITRUS_BERRY,
    ITEM_MICLE_BERRY,
    ITEM_CUSTAP_BERRY,
    ITEM_MENTAL_HERB,
    ITEM_FOCUS_SASH,
    ITEM_SALAC_BERRY,
    ITEM_LIECHI_BERRY,
    ITEM_AGUAV_BERRY,
    ITEM_FIGY_BERRY,
    ITEM_IAPAPA_BERRY,
    ITEM_MAGO_BERRY,
    ITEM_WIKI_BERRY,
    ITEM_MENTAL_HERB,
    ITEM_POWER_HERB,
    ITEM_BERRY_JUICE,
    ITEM_WEAKNESS_POLICY,
    ITEM_BLUNDER_POLICY,
    ITEM_KEE_BERRY,
    ITEM_MARANGA_BERRY,
    // TODO expand this
};

// Its assumed that the berry is strategically given, so no need to check benefits of the berry
bool32 IsStatBoostingBerry(u32 item)
{
    switch (item)
    {
    case ITEM_LIECHI_BERRY:
    case ITEM_GANLON_BERRY:
    case ITEM_SALAC_BERRY:
    case ITEM_PETAYA_BERRY:
    case ITEM_APICOT_BERRY:
    //case ITEM_LANSAT_BERRY:
    case ITEM_STARF_BERRY:
    case ITEM_MICLE_BERRY:
        return TRUE;
    default:
        return FALSE;
    }
}

bool32 ShouldRestoreHpBerry(u32 battlerAtk, u32 item)
{
    switch (item)
    {
    case ITEM_ORAN_BERRY:
        if (gBattleMons[battlerAtk].maxHP <= 50)
            return TRUE;    // Only worth it in the early game
        return FALSE;
    case ITEM_SITRUS_BERRY:
    case ITEM_FIGY_BERRY:
    case ITEM_WIKI_BERRY:
    case ITEM_MAGO_BERRY:
    case ITEM_AGUAV_BERRY:
    case ITEM_IAPAPA_BERRY:
        return TRUE;
    default:
        return FALSE;
    }
}

bool32 IsRecycleEncouragedItem(u32 item)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(sRecycleEncouragedItems); i++)
    {
        if (item == sRecycleEncouragedItems[i])
            return TRUE;
    }
    return FALSE;
}

static enum AIScore IncreaseStatUpScoreInternal(u32 battlerAtk, u32 battlerDef, enum StatChange statId, bool32 considerContrary)
{
    enum AIScore tempScore = NO_INCREASE;
    u32 noOfHitsToFaint = NoOfHitsForTargetToFaintAI(battlerDef, battlerAtk);
    // DebugPrintf("Stat up internal score: Number of hits to KO is %d", noOfHitsToFaint);
    u32 aiIsFaster = AI_IsFaster(battlerAtk, battlerDef, TRUE);
    u32 shouldSetUp = ((noOfHitsToFaint >= 2 && aiIsFaster) || (noOfHitsToFaint >= 3 && !aiIsFaster) || noOfHitsToFaint == UNKNOWN_NO_OF_HITS);


    u32 i;



    if (considerContrary && gAiLogicData->abilities[battlerAtk] == ABILITY_CONTRARY)
        return NO_INCREASE;

    // Don't increase stats if opposing battler has Unaware
    if (HasBattlerSideAbility(battlerDef, ABILITY_UNAWARE, gAiLogicData))
        return NO_INCREASE;

    // Don't increase stat if AI is at +4

    if (gBattleMons[battlerAtk].statStages[statId] >= MAX_STAT_STAGE - 2)
        return NO_INCREASE;



    // Don't increase stat if AI has less then 70% HP and number of hits isn't known
    if (gAiLogicData->hpPercents[battlerAtk] < 70 && noOfHitsToFaint == UNKNOWN_NO_OF_HITS)
        return NO_INCREASE;


    

    // Don't set up if AI is dead to residual damage from weather
    if (GetBattlerSecondaryDamage(battlerAtk) >= gBattleMons[battlerAtk].hp)
        return NO_INCREASE;
    

    // Don't increase stats if opposing battler has Opportunist
    if (gAiLogicData->abilities[battlerDef] == ABILITY_OPPORTUNIST)
        return NO_INCREASE;

    
    // DebugPrintf("statId is %d", statId);

    // Don't increase stats if opposing battler has Encore
    if (HasBattlerSideMoveWithEffect(battlerDef, EFFECT_ENCORE))
        return NO_INCREASE;

    // Don't increase stats if opposing battler has used Haze effect
    if (HasBattlerSideUsedMoveWithEffect(battlerDef, EFFECT_HAZE)
        || HasBattlerSideUsedMoveWithAdditionalEffect(battlerDef, MOVE_EFFECT_CLEAR_SMOG)
        || HasBattlerSideUsedMoveWithAdditionalEffect(battlerDef, MOVE_EFFECT_HAZE))
        return NO_INCREASE;

    // Don't increase if AI is at +1 and opponent has Haze effect
    if (gBattleMons[battlerAtk].statStages[statId] >= MAX_STAT_STAGE - 5 && (HasBattlerSideMoveWithEffect(battlerDef, EFFECT_HAZE)
        || HasBattlerSideMoveWithAdditionalEffect(battlerDef, MOVE_EFFECT_CLEAR_SMOG)
        || HasBattlerSideMoveWithAdditionalEffect(battlerDef, MOVE_EFFECT_HAZE)))
        return NO_INCREASE;

    // Predicting switch
    if (IsBattlerPredictedToSwitch(battlerDef))
    {
        struct Pokemon *playerParty = GetBattlerParty(battlerDef);
        // If expected switchin outspeeds and has Encore, don't increase
        for (i = 0; i < MAX_MON_MOVES; i++)
        {
            if (GetMoveEffect(GetMonData(&playerParty[gAiLogicData->mostSuitableMonId[battlerDef]], MON_DATA_MOVE1 + i, NULL)) == EFFECT_ENCORE
                && GetMonData(&playerParty[gAiLogicData->mostSuitableMonId[battlerDef]], MON_DATA_PP1 + i, NULL) > 0);
            {
                if (GetMonData(&playerParty[gAiLogicData->mostSuitableMonId[battlerDef]], MON_DATA_SPEED, NULL) > gBattleMons[battlerAtk].speed)
                    return NO_INCREASE;
            }
        }
        // Otherwise if predicting switch, stat increases are great momentum
        tempScore += WEAK_EFFECT;
    }

    switch (statId)
    {
    case STAT_CHANGE_ATK:
        if (HasMoveWithCategory(battlerAtk, DAMAGE_CATEGORY_PHYSICAL) && shouldSetUp)
            tempScore += WEAK_EFFECT;
        break;
    case STAT_CHANGE_DEF:
        if ((HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_PHYSICAL) || HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_SPECIAL)) && shouldSetUp)
        {
            if (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_STALL)
                tempScore += DECENT_EFFECT;
            else
                tempScore += WEAK_EFFECT;
        }
        break;
    case STAT_CHANGE_SPEED:
        if ((noOfHitsToFaint >= 3 && !aiIsFaster) || noOfHitsToFaint == UNKNOWN_NO_OF_HITS)
            tempScore += DECENT_EFFECT;
        break;
    case STAT_CHANGE_SPATK:
        if (HasMoveWithCategory(battlerAtk, DAMAGE_CATEGORY_SPECIAL) && shouldSetUp)
            tempScore += DECENT_EFFECT;
        break;
    case STAT_CHANGE_SPDEF:
        if ((HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_SPECIAL) || !HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_PHYSICAL)) && shouldSetUp)
        {
            if (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_STALL)
                tempScore += DECENT_EFFECT;
            else
                tempScore += WEAK_EFFECT;
        }
        break;
    case STAT_CHANGE_ATK_2:
        if (HasMoveWithCategory(battlerAtk, DAMAGE_CATEGORY_PHYSICAL) && shouldSetUp)
            tempScore += DECENT_EFFECT;
        break;
    case STAT_CHANGE_DEF_2:
        if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_PHYSICAL) || !HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_SPECIAL))
        {
            if (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_STALL)
                tempScore += DECENT_EFFECT;
            else
                tempScore += WEAK_EFFECT;
        }
        break;
    case STAT_CHANGE_SPEED_2:
        if ((noOfHitsToFaint >= 3 && !aiIsFaster) || noOfHitsToFaint == UNKNOWN_NO_OF_HITS)
            tempScore += DECENT_EFFECT;
        break;
    case STAT_CHANGE_SPATK_2:
        if (HasMoveWithCategory(battlerAtk, DAMAGE_CATEGORY_SPECIAL) && shouldSetUp)
            tempScore += DECENT_EFFECT;
        break;
    case STAT_CHANGE_SPDEF_2:
        if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_SPECIAL) || !HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_PHYSICAL))
        {
            if (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_STALL)
                tempScore += DECENT_EFFECT;
            else
                tempScore += WEAK_EFFECT;
        }
        break;
    case STAT_CHANGE_ACC:
        if (gBattleMons[battlerAtk].statStages[STAT_ACC] <= 3) // Increase only if necessary
            tempScore += WEAK_EFFECT;
        break;
    case STAT_CHANGE_EVASION:
        // DebugPrintf("STAT_CHANGE_EVASION case reached");
        if (shouldSetUp){
            tempScore += WEAK_EFFECT;
        }else if (noOfHitsToFaint >= 2 && AI_RandLessThan(128)){
            tempScore += WEAK_EFFECT;
        }
        break;
    }

    return tempScore;
}

u32 IncreaseStatUpScore(u32 battlerAtk, u32 battlerDef, enum StatChange statChangeId)
{   
    return IncreaseStatUpScoreInternal(battlerAtk, battlerDef, statChangeId, TRUE);
}

u32 IncreaseStatUpScoreContrary(u32 battlerAtk, u32 battlerDef, enum StatChange statId)
{
    return IncreaseStatUpScoreInternal(battlerAtk, battlerDef, statId, FALSE);
}

void IncreasePoisonScore(u32 battlerAtk, u32 battlerDef, u32 move, s32 *score)
{
    if (((gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_TRY_TO_FAINT) && CanAIFaintTarget(battlerAtk, battlerDef, 0))
            || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_PSN || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_STATUS)
        return;

    if (AI_CanPoison(battlerAtk, battlerDef, gAiLogicData->abilities[battlerDef], move, gAiLogicData->partnerMove) && gAiLogicData->hpPercents[battlerDef] > 20)
    {
        if (!HasDamagingMove(battlerDef))
            ADJUST_SCORE_PTR(DECENT_EFFECT);

        if (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_STALL && HasMoveWithEffect(battlerAtk, EFFECT_PROTECT))
            ADJUST_SCORE_PTR(WEAK_EFFECT);    // stall tactic

        if (IsPowerBasedOnStatus(battlerAtk, EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_PSN_ANY)
         || HasMoveWithEffect(battlerAtk, EFFECT_VENOM_DRENCH)
         || gAiLogicData->abilities[battlerAtk] == ABILITY_MERCILESS)
            ADJUST_SCORE_PTR(DECENT_EFFECT);
        else
            ADJUST_SCORE_PTR(WEAK_EFFECT);
    }
}

void IncreaseBurnScore(u32 battlerAtk, u32 battlerDef, u32 move, s32 *score)
{
    if (((gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_TRY_TO_FAINT) && CanAIFaintTarget(battlerAtk, battlerDef, 0))
            || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_BRN || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_STATUS)
        return;

    if (AI_CanBurn(battlerAtk, battlerDef, gAiLogicData->abilities[battlerDef], BATTLE_PARTNER(battlerAtk), move, gAiLogicData->partnerMove))
    {
        if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_PHYSICAL)
            || (!(gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_OMNISCIENT) // Not Omniscient but expects physical attacker
                && gSpeciesInfo[gBattleMons[battlerDef].species].baseAttack >= gSpeciesInfo[gBattleMons[battlerDef].species].baseSpAttack + 10))
        {
            if (GetMoveCategory(GetBestDmgMoveFromBattler(battlerDef, battlerAtk, AI_DEFENDING)) == DAMAGE_CATEGORY_PHYSICAL)
                ADJUST_SCORE_PTR(DECENT_EFFECT);
            else
                ADJUST_SCORE_PTR(WEAK_EFFECT);
        }

        if (IsPowerBasedOnStatus(battlerAtk, EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_BURN)
          || IsPowerBasedOnStatus(BATTLE_PARTNER(battlerAtk), EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_BURN))
            ADJUST_SCORE_PTR(WEAK_EFFECT);
    }
}

void IncreaseParalyzeScore(u32 battlerAtk, u32 battlerDef, u32 move, s32 *score)
{
    if (((gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_TRY_TO_FAINT) && CanAIFaintTarget(battlerAtk, battlerDef, 0))
            || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_PAR || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_STATUS)
        return;

    if (AI_CanParalyze(battlerAtk, battlerDef, gAiLogicData->abilities[battlerDef], move, gAiLogicData->partnerMove))
    {
        u32 atkSpeed = gAiLogicData->speedStats[battlerAtk];
        u32 defSpeed = gAiLogicData->speedStats[battlerDef];
        bool32 paralyzingBenefitsOutspeeding = (gAiLogicData->abilities[battlerDef] != ABILITY_QUICK_FEET)
        && (defSpeed >= atkSpeed && defSpeed / 2 < atkSpeed);
        bool32 hasParalysisBenefittingMove = IsPowerBasedOnStatus(battlerAtk, EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_PARALYSIS);
        bool32 helpsWithFlinching = (paralyzingBenefitsOutspeeding || (atkSpeed > defSpeed)) && (HasMoveWithMoveEffectExcept(battlerAtk, MOVE_EFFECT_FLINCH, EFFECT_FIRST_TURN_ONLY));
        bool32 targetIsInfatuated = gBattleMons[battlerDef].status2 & STATUS2_INFATUATION;
        u32 conditionSum = paralyzingBenefitsOutspeeding + hasParalysisBenefittingMove + helpsWithFlinching + targetIsInfatuated;

        //Give big score and return in the case of being a Prankster mon with a status paralysis move, if the opposing mon just outspeeds and KOs
        if (CanTargetFaintAi(battlerDef, battlerAtk) && defSpeed > atkSpeed && IsBattleMoveStatus(move)
        && gAiLogicData->abilities[battlerAtk] == ABILITY_PRANKSTER){  
            if (!IsDoubleBattle() || OnlyOnePlayerDoublesMon()){
                ADJUST_SCORE(GOOD_EFFECT);
                return;
            }else if (AI_RandLessThan(127)){ //Making this a chance if two player mons in
                ADJUST_SCORE(DECENT_EFFECT);
                return;
            }
        }
        if (conditionSum >=4){
            ADJUST_SCORE_PTR(GOOD_EFFECT); //In the unlikely case of all conditions, it's high-score and guarenteed
        }else if (conditionSum >= 2){
            u32 randVal = conditionSum >=3 ? 220 : 190; //220 is ~85% chance and 190 is ~75% chance
            if (AI_RandLessThan(randVal)){
                ADJUST_SCORE_PTR(GOOD_EFFECT);
            }else{
                ADJUST_SCORE_PTR(WEAK_EFFECT);
            }
        }else if (conditionSum == 1 && paralyzingBenefitsOutspeeding){//paralysisBenefittingOutspeed gets more value than other solo conditions
            if (AI_RandLessThan(127)){ //~50% chance
                ADJUST_SCORE_PTR(DECENT_EFFECT);
            }else{
                ADJUST_SCORE_PTR(WEAK_EFFECT);
            }
        }else if (conditionSum == 1){ //Only one condition that isn't the outspeed condition
            ADJUST_SCORE_PTR(WEAK_EFFECT);
        }else{
            if (AI_RandLessThan(127)){ //If no conditions, only 50% chance to +1, meaning generally only 25% chance to be used
                ADJUST_SCORE_PTR(WEAK_EFFECT);
            }
        }
        if ((defSpeed >= atkSpeed && defSpeed / 2 < atkSpeed) // You'll go first after paralyzing foe
          || IsPowerBasedOnStatus(battlerAtk, EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_PARALYSIS)
          || (HasMoveWithMoveEffectExcept(battlerAtk, MOVE_EFFECT_FLINCH, EFFECT_FIRST_TURN_ONLY)) // filter out Fake Out
          || gBattleMons[battlerDef].status2 & STATUS2_INFATUATION
          || gBattleMons[battlerDef].status2 & STATUS2_CONFUSION)
            ADJUST_SCORE_PTR(GOOD_EFFECT);
        else
            ADJUST_SCORE_PTR(DECENT_EFFECT);
    }
}

void IncreaseSleepScore(u32 battlerAtk, u32 battlerDef, u32 move, s32 *score)
{
    if (((gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_TRY_TO_FAINT) && CanAIFaintTarget(battlerAtk, battlerDef, 0) && GetMoveEffect(GetBestDmgMoveFromBattler(battlerAtk, battlerDef, AI_ATTACKING)) != EFFECT_FOCUS_PUNCH)
            || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_SLP || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_STATUS)
        return;

    if (AI_CanPutToSleep(battlerAtk, battlerDef, gAiLogicData->abilities[battlerDef], move, gAiLogicData->partnerMove))
        ADJUST_SCORE_PTR(DECENT_EFFECT);
    else
        return;

    if ((HasMoveWithEffect(battlerAtk, EFFECT_DREAM_EATER) || HasMoveWithEffect(battlerAtk, EFFECT_NIGHTMARE))
      && !(HasMoveWithEffect(battlerDef, EFFECT_SNORE) || HasMoveWithEffect(battlerDef, EFFECT_SLEEP_TALK)))
        ADJUST_SCORE_PTR(WEAK_EFFECT);

    if (IsPowerBasedOnStatus(battlerAtk, EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_SLEEP)
      || IsPowerBasedOnStatus(BATTLE_PARTNER(battlerAtk), EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_SLEEP))
        ADJUST_SCORE_PTR(WEAK_EFFECT);
}

void IncreaseConfusionScore(u32 battlerAtk, u32 battlerDef, u32 move, s32 *score)
{
    if (((gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_TRY_TO_FAINT) && CanAIFaintTarget(battlerAtk, battlerDef, 0))
            || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_CONFUSION || gAiLogicData->holdEffects[battlerDef] == HOLD_EFFECT_CURE_STATUS)
        return;

    if (AI_CanConfuse(battlerAtk, battlerDef, gAiLogicData->abilities[battlerDef], BATTLE_PARTNER(battlerAtk), move, gAiLogicData->partnerMove)
      && gAiLogicData->holdEffects[battlerDef] != HOLD_EFFECT_CURE_CONFUSION
      && gAiLogicData->holdEffects[battlerDef] != HOLD_EFFECT_CURE_STATUS)
    {
        if (gBattleMons[battlerDef].status1 & STATUS1_PARALYSIS
          || gBattleMons[battlerDef].status2 & STATUS2_INFATUATION
          || (gAiLogicData->abilities[battlerAtk] == ABILITY_SERENE_GRACE && HasMoveWithMoveEffectExcept(battlerAtk, MOVE_EFFECT_FLINCH, EFFECT_FIRST_TURN_ONLY)))
            ADJUST_SCORE_PTR(DECENT_EFFECT);
        else
            ADJUST_SCORE_PTR(WEAK_EFFECT);
    }
}

void IncreaseFrostbiteScore(u32 battlerAtk, u32 battlerDef, u32 move, s32 *score)
{
    if ((gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_TRY_TO_FAINT) && CanAIFaintTarget(battlerAtk, battlerDef, 0))
        return;

    if (AI_CanGiveFrostbite(battlerAtk, battlerDef, gAiLogicData->abilities[battlerDef], BATTLE_PARTNER(battlerAtk), move, gAiLogicData->partnerMove))
    {
        if (HasMoveWithCategory(battlerDef, DAMAGE_CATEGORY_SPECIAL)
            || (!(gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_OMNISCIENT) // Not Omniscient but expects special attacker
                && gSpeciesInfo[gBattleMons[battlerDef].species].baseSpAttack >= gSpeciesInfo[gBattleMons[battlerDef].species].baseAttack + 10))
        {
            if (GetMoveCategory(GetBestDmgMoveFromBattler(battlerDef, battlerAtk, AI_DEFENDING)) == DAMAGE_CATEGORY_SPECIAL)
                ADJUST_SCORE_PTR(DECENT_EFFECT);
            else
                ADJUST_SCORE_PTR(WEAK_EFFECT);
        }

        if (IsPowerBasedOnStatus(battlerAtk, EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_FROSTBITE)
          || IsPowerBasedOnStatus(BATTLE_PARTNER(battlerAtk), EFFECT_DOUBLE_POWER_ON_ARG_STATUS, STATUS1_FROSTBITE))
            ADJUST_SCORE_PTR(WEAK_EFFECT);
    }
}

bool32 AI_MoveMakesContact(u32 ability, enum ItemHoldEffect holdEffect, u32 move)
{
    if (MoveMakesContact(move)
      && ability != ABILITY_LONG_REACH
      && holdEffect != HOLD_EFFECT_PROTECTIVE_PADS)
        return TRUE;
    return FALSE;
}

//TODO - this could use some more sophisticated logic
bool32 ShouldUseZMove(u32 battlerAtk, u32 battlerDef, u32 chosenMove)
{
    // simple logic. just upgrades chosen move to z move if possible, unless regular move would kill opponent
    if ((IsDoubleBattle()) && battlerDef == BATTLE_PARTNER(battlerAtk))
        return FALSE;   // don't use z move on partner
    if (HasTrainerUsedGimmick(battlerAtk, GIMMICK_Z_MOVE))
        return FALSE;   // can't use z move twice

    if (IsViableZMove(battlerAtk, chosenMove))
    {
        uq4_12_t effectiveness;
        u32 zMove = GetUsableZMove(battlerAtk, chosenMove);
        struct SimulatedDamage dmg;

        if (gBattleMons[battlerDef].ability == ABILITY_DISGUISE
            && !MoveIgnoresTargetAbility(zMove)
            && (gBattleMons[battlerDef].species == SPECIES_MIMIKYU_DISGUISED || gBattleMons[battlerDef].species == SPECIES_MIMIKYU_TOTEM_DISGUISED))
            return FALSE; // Don't waste a Z-Move busting disguise
        if (gBattleMons[battlerDef].ability == ABILITY_ICE_FACE
            && !MoveIgnoresTargetAbility(zMove)
            && gBattleMons[battlerDef].species == SPECIES_EISCUE_ICE && IsBattleMovePhysical(chosenMove))
            return FALSE; // Don't waste a Z-Move busting Ice Face

        if (IsBattleMoveStatus(chosenMove) && !IsBattleMoveStatus(zMove))
            return FALSE;
        else if (!IsBattleMoveStatus(chosenMove) && IsBattleMoveStatus(zMove))
            return FALSE;

        dmg = AI_CalcDamageSaveBattlers(chosenMove, battlerAtk, battlerDef, &effectiveness, FALSE);

        if (!IsBattleMoveStatus(chosenMove) && dmg.minimum >= gBattleMons[battlerDef].hp)
            return FALSE;   // don't waste damaging z move if can otherwise faint target

        return TRUE;
    }

    return FALSE;
}

bool32 AI_ShouldTerastal(u32 battler){
    u32 opponentTypes[3];
    u32 battlerToFocus = BATTLE_OPPOSITE(battler);
    u32 teraType = GetBattlerTeraType(battler);


    //No type cost to tera, so always tera
    if (teraType == TYPE_STELLAR){
        return TRUE;
    }

    //Want to improve this in the future, but just working with slots for now
    if (IsDoubleBattle() && !IsBattlerAlive(battlerToFocus)){
        battlerToFocus = BATTLE_PARTNER(battlerToFocus);
    }
    GetBattlerTypes(battlerToFocus, FALSE, opponentTypes);
    //If player STABs are already SE, might as well tera
    if (
    CalcTypeEffectivenessMultiplier(MOVE_CONSTRICT, opponentTypes[0], battlerToFocus, battler, gAiLogicData->abilities[battlerToFocus], FALSE) > UQ_4_12(1.0)
    || CalcTypeEffectivenessMultiplier(MOVE_CONSTRICT, opponentTypes[1], battlerToFocus, battler, gAiLogicData->abilities[battlerToFocus], FALSE) > UQ_4_12(1.0)
    ){
        return TRUE;
    }

    //Don't tera if it would go from a STAB immunity to not having a STAB immunity. 
    else if (CalcTypeEffectivenessMultiplier(MOVE_CONSTRICT, opponentTypes[0], battlerToFocus, battler, gAiLogicData->abilities[battlerToFocus], FALSE) == UQ_4_12(0)
    && CalcTypeEffectivenessMultiplier(MOVE_CONSTRICT, opponentTypes[1], battlerToFocus, battler, gAiLogicData->abilities[battlerToFocus], FALSE) == UQ_4_12(0)
    && (GetTypeModifier(opponentTypes[0], teraType) > UQ_4_12(0) || GetTypeModifier(opponentTypes[1], teraType) > UQ_4_12(0))){
        return FALSE;
    }
    //If STABs are not SE against current type but are SE against Tera type, do not tera
    else if (GetTypeModifier(opponentTypes[0], teraType) > UQ_4_12(1.0) || GetTypeModifier(opponentTypes[1], teraType) > UQ_4_12(1.0)){
        return FALSE;
    }

    //If both STABs are resisted by existing type, but tera is not resisted by at least one of the types, do not tera
    if (
       CalcTypeEffectivenessMultiplier(MOVE_CONSTRICT, opponentTypes[0], battlerToFocus, battler, gAiLogicData->abilities[battlerToFocus], FALSE) < UQ_4_12(1.0)
       && CalcTypeEffectivenessMultiplier(MOVE_CONSTRICT, opponentTypes[1], battlerToFocus, battler, gAiLogicData->abilities[battlerToFocus], FALSE) < UQ_4_12(1.0)
       && (GetTypeModifier(opponentTypes[0], teraType) >= UQ_4_12(1.0) || GetTypeModifier(opponentTypes[1], teraType) >= UQ_4_12(1.0))
    ){
        return FALSE;
    }

    //If no other checks have been met, prioritize tera
     
    return TRUE;
} 

bool32 AI_IsBattlerAsleepOrComatose(u32 battlerId)
{
    return (gBattleMons[battlerId].status1 & STATUS1_SLEEP) || gAiLogicData->abilities[battlerId] == ABILITY_COMATOSE;
}

s32 AI_TryToClearStats(u32 battlerAtk, u32 battlerDef, bool32 isDoubleBattle)
{
    if (isDoubleBattle)
        return min(CountPositiveStatStages(battlerDef) + CountPositiveStatStages(BATTLE_PARTNER(battlerDef)), 7);
    else
        return min(CountPositiveStatStages(battlerDef), 4);
}

bool32 AI_ShouldCopyStatChanges(u32 battlerAtk, u32 battlerDef)
{
    u8 i;
    // Want to copy positive stat changes
    for (i = STAT_ATK; i < NUM_BATTLE_STATS; i++)
    {
        if (gBattleMons[battlerDef].statStages[i] > gBattleMons[battlerAtk].statStages[i])
        {
            switch (i)
            {
            case STAT_ATK:
                return (HasMoveWithCategory(battlerAtk, DAMAGE_CATEGORY_PHYSICAL));
            case STAT_SPATK:
                return (HasMoveWithCategory(battlerAtk, DAMAGE_CATEGORY_SPECIAL));
            case STAT_ACC:
                return (HasLowAccuracyMove(battlerAtk, battlerDef));
            case STAT_EVASION:
            case STAT_SPEED:
                return TRUE;
            case STAT_DEF:
            case STAT_SPDEF:
                return (gAiThinkingStruct->aiFlags[battlerAtk] & AI_FLAG_STALL);
            }
        }
    }

    return FALSE;
}

//TODO - track entire opponent party data to determine hazard effectiveness
bool32 AI_ShouldSetUpHazards(u32 battlerAtk, u32 battlerDef, struct AiLogicData *aiData)
{
    if (aiData->abilities[battlerDef] == ABILITY_MAGIC_BOUNCE
     || CountUsablePartyMons(battlerDef) == 0
     || HasMoveWithEffect(battlerDef, EFFECT_RAPID_SPIN)
     || HasMoveWithEffect(battlerDef, EFFECT_TIDY_UP)
     || HasMoveWithEffect(battlerDef, EFFECT_DEFOG)
     || HasMoveWithAdditionalEffect(battlerDef, MOVE_EFFECT_DEFOG)
     || HasMoveWithEffect(battlerDef, EFFECT_MAGIC_COAT))
        return FALSE;

    return TRUE;
}

void IncreaseTidyUpScore(u32 battlerAtk, u32 battlerDef, u32 move, s32 *score)
{
    if (gSideStatuses[GetBattlerSide(battlerAtk)] & SIDE_STATUS_HAZARDS_ANY && CountUsablePartyMons(battlerAtk) != 0)
        ADJUST_SCORE_PTR(GOOD_EFFECT);
    if (gSideStatuses[GetBattlerSide(battlerDef)] & SIDE_STATUS_HAZARDS_ANY && CountUsablePartyMons(battlerDef) != 0)
        ADJUST_SCORE_PTR(-2);

    if (gBattleMons[battlerAtk].status2 & STATUS2_SUBSTITUTE && AI_IsFaster(battlerAtk, battlerDef, move))
        ADJUST_SCORE_PTR(-10);
    if (gBattleMons[battlerDef].status2 & STATUS2_SUBSTITUTE)
        ADJUST_SCORE_PTR(GOOD_EFFECT);

    if (gStatuses3[battlerAtk] & STATUS3_LEECHSEED)
        ADJUST_SCORE_PTR(DECENT_EFFECT);
    if (gStatuses3[battlerDef] & STATUS3_LEECHSEED)
        ADJUST_SCORE_PTR(-2);
}

bool32 AI_ShouldSpicyExtract(u32 battlerAtk, u32 battlerAtkPartner, u32 move, struct AiLogicData *aiData)
{
    u32 preventsStatLoss;
    u32 partnerAbility;
    u32 partnerHoldEffect = aiData->holdEffects[battlerAtkPartner];

    if (DoesBattlerIgnoreAbilityChecks(battlerAtk, aiData->abilities[battlerAtk], move))
        partnerAbility = ABILITY_NONE;
    else
        partnerAbility = aiData->abilities[battlerAtkPartner];

    if (gBattleMons[battlerAtkPartner].statStages[STAT_ATK] == MAX_STAT_STAGE
     || partnerAbility == ABILITY_CONTRARY
     || partnerAbility == ABILITY_GOOD_AS_GOLD
     || HasMoveWithEffect(BATTLE_OPPOSITE(battlerAtk), EFFECT_FOUL_PLAY)
     || HasMoveWithEffect(BATTLE_OPPOSITE(battlerAtkPartner), EFFECT_FOUL_PLAY))
        return FALSE;

    preventsStatLoss = (partnerAbility == ABILITY_CLEAR_BODY
                     || partnerAbility == ABILITY_FULL_METAL_BODY
                     || partnerAbility == ABILITY_WHITE_SMOKE
                     || partnerHoldEffect == HOLD_EFFECT_CLEAR_AMULET);

    switch (GetMoveEffect(aiData->partnerMove))
    {
    case EFFECT_DEFENSE_UP:
    case EFFECT_DEFENSE_UP_2:
    case EFFECT_DEFENSE_UP_3:
    case EFFECT_BULK_UP:
    case EFFECT_STOCKPILE:
        if (!preventsStatLoss)
            return FALSE;
    default:
        break;
    }

    return (preventsStatLoss
         && AI_IsFaster(battlerAtk, battlerAtkPartner, TRUE)
         && HasMoveWithCategory(battlerAtkPartner, DAMAGE_CATEGORY_PHYSICAL));
}

u32 IncreaseSubstituteMoveScore(u32 battlerAtk, u32 battlerDef, u32 move)
{
    enum BattleMoveEffects effect = GetMoveEffect(move);
    u32 scoreIncrease = 0;
    if (effect == EFFECT_SUBSTITUTE) // Substitute specific
    {
        if (HasAnyKnownMove(battlerDef) && GetBestDmgFromBattler(battlerDef, battlerAtk, AI_DEFENDING) < gBattleMons[battlerAtk].maxHP / 4)
            scoreIncrease += DECENT_EFFECT;
    }
    else if (effect == EFFECT_SHED_TAIL) // Shed Tail specific
    {
        if ((ShouldPivot(battlerAtk, battlerDef, gAiLogicData->abilities[battlerDef], move, gAiThinkingStruct->movesetIndex))
        && (HasAnyKnownMove(battlerDef) && (GetBestDmgFromBattler(battlerDef, battlerAtk, AI_DEFENDING) < gBattleMons[battlerAtk].maxHP / 2)))
            scoreIncrease += DECENT_EFFECT;
    }

    if (gStatuses3[battlerDef] & STATUS3_PERISH_SONG)
    scoreIncrease += WEAK_EFFECT;

    if (gBattleMons[battlerDef].status1 & STATUS1_SLEEP)
        scoreIncrease += DECENT_EFFECT;
    else if (gBattleMons[battlerDef].status1 & (STATUS1_BURN | STATUS1_PSN_ANY | STATUS1_FROSTBITE))
        scoreIncrease += WEAK_EFFECT;

    if (IsBattlerPredictedToSwitch(battlerDef))
        scoreIncrease += DECENT_EFFECT;

    if (HasNonVolatileMoveEffect(battlerDef, MOVE_EFFECT_SLEEP)
     || HasNonVolatileMoveEffect(battlerDef, MOVE_EFFECT_TOXIC)
     || HasNonVolatileMoveEffect(battlerDef, MOVE_EFFECT_PARALYSIS)
     || HasNonVolatileMoveEffect(battlerDef, MOVE_EFFECT_BURN)
     || HasMoveWithEffect(battlerDef, EFFECT_CONFUSE)
     || HasMoveWithEffect(battlerDef, EFFECT_LEECH_SEED)){
        if (AI_RandLessThan(127)){
            scoreIncrease += GOOD_EFFECT;
        }else{
            scoreIncrease +=WEAK_EFFECT;
        }
     }

    if (gAiLogicData->hpPercents[battlerAtk] > 70){
        scoreIncrease += WEAK_EFFECT;
        if ( gAiLogicData->holdEffects[battlerAtk] == HOLD_EFFECT_EVASION_UP && AI_RandLessThan(127)){
            scoreIncrease += WEAK_EFFECT;
        }
    }
    return scoreIncrease;
}

bool32 HasLowAccuracyMove(u32 battlerAtk, u32 battlerDef)
{
    int i;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (gAiLogicData->moveAccuracy[battlerAtk][battlerDef][i] <= LOW_ACCURACY_THRESHOLD)
            return TRUE;
    }
    return FALSE;
}

bool32 IsBattlerItemEnabled(u32 battler)
{
    if (gAiThinkingStruct->aiFlags[battler] & AI_FLAG_NEGATE_UNAWARE)
        return TRUE;
    if (gFieldStatuses & STATUS_FIELD_MAGIC_ROOM)
        return FALSE;
    if (gStatuses3[battler] & STATUS3_EMBARGO)
        return FALSE;
    if (gBattleMons[battler].ability == ABILITY_KLUTZ && !(gStatuses3[battler] & STATUS3_GASTRO_ACID))
        return FALSE;
    return TRUE;
}

bool32 HasBattlerSideAbility(u32 battler, u32 ability, struct AiLogicData *aiData)
{
    if (aiData->abilities[battler] == ability)
        return TRUE;
    if (IsDoubleBattle() && gAiLogicData->abilities[BATTLE_PARTNER(battler)] == ability)
        return TRUE;
    return FALSE;
}

u32 GetFriendlyFireKOThreshold(u32 battler)
{
    if (gAiThinkingStruct->aiFlags[battler] & AI_FLAG_RISKY)
        return FRIENDLY_FIRE_RISKY_THRESHOLD;
    if (gAiThinkingStruct->aiFlags[battler] & AI_FLAG_CONSERVATIVE)
        return FRIENDLY_FIRE_CONSERVATIVE_THRESHOLD;

    return FRIENDLY_FIRE_NORMAL_THRESHOLD;
}

bool32 IsMoxieTypeAbility(u32 ability)
{
    switch (ability)
    {
    case ABILITY_MOXIE:
    case ABILITY_BEAST_BOOST:
    case ABILITY_CHILLING_NEIGH:
    case ABILITY_AS_ONE_ICE_RIDER:
    case ABILITY_GRIM_NEIGH:
    case ABILITY_AS_ONE_SHADOW_RIDER:
        return TRUE;
    default:
        return FALSE;
    }
}

// Should the AI use a spread move to deliberately activate its partner's ability?
bool32 ShouldTriggerAbility(u32 battler, u32 ability)
{
    switch (ability)
    {
        case ABILITY_LIGHTNING_ROD:
        case ABILITY_STORM_DRAIN:
            if (B_REDIRECT_ABILITY_IMMUNITY < GEN_5)
                return FALSE;
            else
                return (BattlerStatCanRise(battler, ability, STAT_SPATK) && HasMoveWithCategory(battler, DAMAGE_CATEGORY_SPECIAL));

        case ABILITY_DEFIANT:
        case ABILITY_JUSTIFIED:
        case ABILITY_MOXIE:
        case ABILITY_SAP_SIPPER:
        case ABILITY_THERMAL_EXCHANGE:
            return (BattlerStatCanRise(battler, ability, STAT_ATK) && HasMoveWithCategory(battler, DAMAGE_CATEGORY_PHYSICAL));

        case ABILITY_COMPETITIVE:
            return (BattlerStatCanRise(battler, ability, STAT_SPATK) && HasMoveWithCategory(battler, DAMAGE_CATEGORY_SPECIAL));

        case ABILITY_CONTRARY:
            return TRUE;

        case ABILITY_DRY_SKIN:
        case ABILITY_VOLT_ABSORB:
        case ABILITY_WATER_ABSORB:
            return (gAiThinkingStruct->aiFlags[battler] & AI_FLAG_HP_AWARE);

        case ABILITY_RATTLED:
        case ABILITY_STEAM_ENGINE:
            return BattlerStatCanRise(battler, ability, STAT_SPEED);

        case ABILITY_FLASH_FIRE:
            return (HasMoveWithType(battler, TYPE_FIRE) && !gDisableStructs[battler].flashFireBoosted);

        case ABILITY_WATER_COMPACTION:
        case ABILITY_WELL_BAKED_BODY:
            return (BattlerStatCanRise(battler, ability, STAT_DEF));

        default:
            return FALSE;
    }
}

u32 GetThinkingBattler(u32 battler)
{
    if (gAiLogicData->aiPredictionInProgress)
        return gAiLogicData->battlerDoingPrediction;
    return battler;
}
