#include "global.h"
#include "test/battle.h"
#include "battle_ai_util.h"

ASSUMPTIONS
{
    ASSUME(GetSpeciesAbility(SPECIES_HITMONCHAN, 0) == ABILITY_BOXERS_GUARD);
    ASSUME(IsPunchingMove(MOVE_FIRE_PUNCH));
    ASSUME(IsPunchingMove(MOVE_ICE_PUNCH));
    ASSUME(IsPunchingMove(MOVE_THUNDER_PUNCH));
    ASSUME(IsPunchingMove(MOVE_MACH_PUNCH));
    ASSUME(!IsPunchingMove(MOVE_CELEBRATE));
    ASSUME(GetItemHoldEffect(ITEM_PUNCHING_GLOVE) == HOLD_EFFECT_PUNCHING_GLOVE);
    ASSUME(GetMoveCategory(MOVE_SCRATCH) == DAMAGE_CATEGORY_PHYSICAL);
    ASSUME(GetMoveCategory(MOVE_SWIFT) == DAMAGE_CATEGORY_SPECIAL);
}

SINGLE_BATTLE_TEST("Elastic-tests: Boxer's Guard adds 10% Defense per punching move and effective Punching Glove", s16 damage)
{
    u32 punchCount = 0, defense = 100;
    enum Item item = ITEM_NONE;
    enum Ability ability = ABILITY_BOXERS_GUARD;
    static const u16 expectedDefense[][2] = {
        {100, 110},
        {110, 120},
        {120, 130},
        {130, 140},
        {140, 150},
    };

    for (u32 punches = 0; punches < ARRAY_COUNT(expectedDefense); punches++)
    {
        for (u32 glove = 0; glove < ARRAY_COUNT(expectedDefense[0]); glove++)
        {
            for (u32 control = 0; control < 2; control++)
            {
                PARAMETRIZE {
                    punchCount = punches;
                    item = glove ? ITEM_PUNCHING_GLOVE : ITEM_NONE;
                    ability = control ? ABILITY_INNER_FOCUS : ABILITY_BOXERS_GUARD;
                    defense = control ? expectedDefense[punches][glove] : 100;
                }
            }
        }
    }

    GIVEN {
        PLAYER(SPECIES_HITMONCHAN) {
            Ability(ability);
            Defense(defense);
            Speed(1);
            HP(300);
            Item(item);
            Moves(punchCount >= 1 ? MOVE_FIRE_PUNCH : MOVE_CELEBRATE,
                  punchCount >= 2 ? MOVE_ICE_PUNCH : MOVE_NONE,
                  punchCount >= 3 ? MOVE_THUNDER_PUNCH : MOVE_NONE,
                  punchCount >= 4 ? MOVE_MACH_PUNCH : MOVE_NONE);
        }
        OPPONENT(SPECIES_WOBBUFFET) { Level(100); Attack(250); Speed(100); }
    } WHEN {
        TURN {
            MOVE(opponent, MOVE_SCRATCH, criticalHit: FALSE, WITH_RNG(RNG_DAMAGE_MODIFIER, 0));
            MOVE(player, punchCount > 0 ? MOVE_FIRE_PUNCH : MOVE_CELEBRATE);
        }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
    } THEN {
        EXPECT_EQ(player->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
    } FINALLY {
        for (u32 pair = 0; pair < ARRAY_COUNT(expectedDefense) * ARRAY_COUNT(expectedDefense[0]); pair++)
            EXPECT_EQ(results[2 * pair].damage, results[2 * pair + 1].damage);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Boxer's Guard follows the defensive stat used by the incoming move", s16 damage)
{
    enum Ability ability;
    enum Move move;
    PARAMETRIZE { ability = ABILITY_BOXERS_GUARD; move = MOVE_SWIFT; }
    PARAMETRIZE { ability = ABILITY_INNER_FOCUS; move = MOVE_SWIFT; }
    PARAMETRIZE { ability = ABILITY_BOXERS_GUARD; move = MOVE_PSYSHOCK; }
    PARAMETRIZE { ability = ABILITY_INNER_FOCUS; move = MOVE_PSYSHOCK; }

    GIVEN {
        PLAYER(SPECIES_HITMONCHAN) {
            Ability(ability);
            Speed(1);
            HP(300);
            Item(ITEM_PUNCHING_GLOVE);
            Moves(MOVE_FIRE_PUNCH, MOVE_ICE_PUNCH, MOVE_THUNDER_PUNCH, MOVE_MACH_PUNCH);
        }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(100); }
    } WHEN {
        TURN {
            MOVE(opponent, move, criticalHit: FALSE, WITH_RNG(RNG_DAMAGE_MODIFIER, 0));
            MOVE(player, MOVE_FIRE_PUNCH);
        }
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
        EXPECT_LT(results[2].damage, results[3].damage);
    }
}

SINGLE_BATTLE_TEST("Elastic-tests: Magic Room suppresses the Punching Glove bonus from Boxer's Guard", s16 damage)
{
    enum Item item;
    PARAMETRIZE { item = ITEM_PUNCHING_GLOVE; }
    PARAMETRIZE { item = ITEM_NONE; }

    GIVEN {
        PLAYER(SPECIES_HITMONCHAN) {
            Ability(ABILITY_BOXERS_GUARD);
            Item(item);
            Moves(MOVE_CELEBRATE);
        }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_MAGIC_ROOM); }
        TURN { MOVE(opponent, MOVE_SCRATCH, criticalHit: FALSE, WITH_RNG(RNG_DAMAGE_MODIFIER, 0)); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MAGIC_ROOM, opponent);
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
    }
}

AI_SINGLE_BATTLE_TEST("Elastic-tests: Known or predicted Boxer's Guard uses full mitigation in AI damage")
{
    enum Ability actualAbility;
    PARAMETRIZE { actualAbility = ABILITY_BOXERS_GUARD; }
    PARAMETRIZE { actualAbility = ABILITY_INNER_FOCUS; }

    GIVEN {
        AI_FLAGS(AI_FLAG_CHECK_BAD_MOVE | AI_FLAG_ABILITY_OMNISCIENCE);
        PLAYER(SPECIES_HITMONCHAN) {
            Ability(actualAbility);
            Defense(100);
            HP(300);
            Item(ITEM_PUNCHING_GLOVE);
            Moves(MOVE_CELEBRATE, MOVE_FIRE_PUNCH, MOVE_ICE_PUNCH);
        }
        OPPONENT(SPECIES_WOBBUFFET) { Level(100); Attack(250); Moves(MOVE_SCRATCH); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); EXPECT_MOVE(opponent, MOVE_SCRATCH); }
    } THEN {
        enum BattlerId attacker = GetBattlerAtPosition(B_POSITION_OPPONENT_LEFT);
        enum BattlerId defender = GetBattlerAtPosition(B_POSITION_PLAYER_LEFT);
        struct AiCalcValues calc = { .move = MOVE_SCRATCH };
        enum Ability savedAbility = gAiLogicData->abilities[defender];
        u32 savedDefense = gBattleMons[defender].defense;
        s32 cachedDamage = gAiLogicData->simulatedDmg[attacker][defender][0].median;

        // Exercise a prediction even when the actual ability is Inner Focus.
        gAiLogicData->abilities[defender] = ABILITY_BOXERS_GUARD;
        SaveBattlerData(defender);
        SetBattlerData(defender);
        s32 estimatedDamage = AI_CalcDamage(&calc, attacker, defender).median;
        RestoreBattlerData(defender);

        gAiLogicData->abilities[defender] = ABILITY_INNER_FOCUS;
        gBattleMons[defender].defense = 130;
        s32 damageAtBoostedDefense = AI_CalcDamage(&calc, attacker, defender).median;
        gBattleMons[defender].defense = savedDefense;
        gAiLogicData->abilities[defender] = savedAbility;

        EXPECT_GT(estimatedDamage, 0);
        EXPECT_EQ(estimatedDamage, damageAtBoostedDefense);
        if (actualAbility == ABILITY_BOXERS_GUARD)
            EXPECT_EQ(cachedDamage, estimatedDamage);
        else
            EXPECT_GT(cachedDamage, estimatedDamage);
        EXPECT_EQ(gBattleHistory->usedMoves[defender][1], MOVE_NONE);
        EXPECT_EQ(gBattleHistory->usedMoves[defender][2], MOVE_NONE);
        EXPECT_EQ(gBattleHistory->itemEffects[defender], HOLD_EFFECT_NONE);
        EXPECT_EQ(gBattleMons[defender].moves[1], MOVE_FIRE_PUNCH);
        EXPECT_EQ(gBattleMons[defender].item, ITEM_PUNCHING_GLOVE);
    }
}
