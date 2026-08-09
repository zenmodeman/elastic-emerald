#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Zenmodeman: Mystic boosts Psychic damage by fifty percent without boosting other types", s16 damage)
{
    enum Move move;
    enum Ability ability;

    PARAMETRIZE { move = MOVE_WATER_GUN; ability = ABILITY_CLOUD_NINE; }
    PARAMETRIZE { move = MOVE_WATER_GUN; ability = ABILITY_MYSTIC; }
    PARAMETRIZE { move = MOVE_CONFUSION; ability = ABILITY_CLOUD_NINE; }
    PARAMETRIZE { move = MOVE_CONFUSION; ability = ABILITY_MYSTIC; }
    GIVEN {
        ASSUME(GetMoveType(MOVE_WATER_GUN) == TYPE_WATER);
        ASSUME(GetMoveType(MOVE_CONFUSION) == TYPE_PSYCHIC);
        PLAYER(SPECIES_GOLDUCK) { Ability(ability); SpAttack(100); }
        OPPONENT(SPECIES_WOBBUFFET) { SpDefense(100); }
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_EQ(results[0].damage, results[1].damage);
        EXPECT_MUL_EQ(results[2].damage, Q_4_12(1.5), results[3].damage);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Dominate raises Attack when the opponent has lower Defense", s16 damage)
{
    enum Ability ability;

    PARAMETRIZE { ability = ABILITY_SOUNDPROOF; }
    PARAMETRIZE { ability = ABILITY_DOMINATE; }
    GIVEN {
        ASSUME(GetMoveCategory(MOVE_SCRATCH) == DAMAGE_CATEGORY_PHYSICAL);
        PLAYER(SPECIES_WOBBUFFET) { Defense(100); SpDefense(200); }
        OPPONENT(SPECIES_EXPLOUD) { Ability(ability); Attack(100); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        if (ability == ABILITY_DOMINATE)
        {
            ABILITY_POPUP(opponent, ABILITY_DOMINATE);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
            MESSAGE("The opposing Exploud's Attack rose!");
        }
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("Zenmodeman: Dominate raises Special Attack when the opponent has lower Special Defense", s16 damage)
{
    enum Ability ability;

    PARAMETRIZE { ability = ABILITY_SOUNDPROOF; }
    PARAMETRIZE { ability = ABILITY_DOMINATE; }
    GIVEN {
        ASSUME(GetMoveCategory(MOVE_HYPER_VOICE) == DAMAGE_CATEGORY_SPECIAL);
        PLAYER(SPECIES_WOBBUFFET) { Defense(200); SpDefense(100); }
        OPPONENT(SPECIES_EXPLOUD) { Ability(ability); SpAttack(100); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_HYPER_VOICE); }
    } SCENE {
        if (ability == ABILITY_DOMINATE)
        {
            ABILITY_POPUP(opponent, ABILITY_DOMINATE);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
            MESSAGE("The opposing Exploud's Sp. Atk rose!");
        }
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.5), results[1].damage);
    }
}
