#include "global.h"
#include "pokemon.h"
#include "test/test.h"

TEST("Elastic-tests: Demo 2 Grimer forms retain their special bulk buff")
{
    EXPECT_EQ(GetSpeciesBaseSpDefense(SPECIES_GRIMER), 70);
    EXPECT_EQ(GetSpeciesBaseSpDefense(SPECIES_GRIMER_ALOLA), 70);
}

TEST("Elastic-tests: Demo 2 Hoenn species retain their custom bulk profiles")
{
    EXPECT_EQ(GetSpeciesBaseHP(SPECIES_GULPIN), 73);
    EXPECT_EQ(GetSpeciesBaseSpeed(SPECIES_GULPIN), 43);
    EXPECT_EQ(GetSpeciesBaseHP(SPECIES_SWALOT), 113);
    EXPECT_EQ(GetSpeciesBaseSpeed(SPECIES_SWALOT), 53);
    EXPECT_EQ(GetSpeciesBaseDefense(SPECIES_WAILMER), 45);
    EXPECT_EQ(GetSpeciesBaseSpDefense(SPECIES_WAILMER), 45);
    EXPECT_EQ(GetSpeciesBaseDefense(SPECIES_WAILORD), 55);
    EXPECT_EQ(GetSpeciesBaseSpDefense(SPECIES_WAILORD), 55);
}

TEST("Elastic-tests: Demo 2 Swablu retains its stats abilities and early evolution")
{
    struct Pokemon mon;

    EXPECT_EQ(GetSpeciesBaseHP(SPECIES_SWABLU), 55);
    EXPECT_EQ(GetSpeciesBaseAttack(SPECIES_SWABLU), 45);
    EXPECT_EQ(GetSpeciesBaseDefense(SPECIES_SWABLU), 65);
    EXPECT_EQ(GetSpeciesBaseSpAttack(SPECIES_SWABLU), 45);
    EXPECT_EQ(GetSpeciesBaseSpDefense(SPECIES_SWABLU), 80);
    EXPECT_EQ(GetSpeciesAbility(SPECIES_SWABLU, 0), ABILITY_NATURAL_CURE);
    EXPECT_EQ(GetSpeciesAbility(SPECIES_SWABLU, 1), ABILITY_CLOUD_NINE);
    EXPECT_EQ(GetSpeciesAbility(SPECIES_SWABLU, 2), ABILITY_FRIEND_GUARD);

    CreateMon(&mon, SPECIES_SWABLU, 31, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, NULL, CHECK_EVO), SPECIES_NONE);
    CreateMon(&mon, SPECIES_SWABLU, 32, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, NULL, CHECK_EVO), SPECIES_ALTARIA);
}

TEST("Elastic-tests: Demo 2 Foongus and Larvesta retain their custom stat spreads")
{
    EXPECT_EQ(GetSpeciesBaseHP(SPECIES_FOONGUS), 74);
    EXPECT_EQ(GetSpeciesBaseAttack(SPECIES_FOONGUS), 65);
    EXPECT_EQ(GetSpeciesBaseDefense(SPECIES_FOONGUS), 55);
    EXPECT_EQ(GetSpeciesBaseSpAttack(SPECIES_FOONGUS), 65);
    EXPECT_EQ(GetSpeciesBaseSpDefense(SPECIES_FOONGUS), 60);

    EXPECT_EQ(GetSpeciesBaseHP(SPECIES_LARVESTA), 75);
    EXPECT_EQ(GetSpeciesBaseAttack(SPECIES_LARVESTA), 85);
    EXPECT_EQ(GetSpeciesBaseDefense(SPECIES_LARVESTA), 65);
    EXPECT_EQ(GetSpeciesBaseSpAttack(SPECIES_LARVESTA), 50);
    EXPECT_EQ(GetSpeciesBaseSpDefense(SPECIES_LARVESTA), 75);
}

TEST("Elastic-tests: Sableye and Mawile families retain their early custom stat buffs")
{
    EXPECT_EQ(GetSpeciesBaseAttack(SPECIES_SABLEYE), 85);
    EXPECT_EQ(GetSpeciesBaseDefense(SPECIES_SABLEYE), 85);
    EXPECT_EQ(GetSpeciesBaseAttack(SPECIES_SABLEYE_MEGA), 95);
    EXPECT_EQ(GetSpeciesBaseSpeed(SPECIES_SABLEYE_MEGA), 30);

    EXPECT_EQ(GetSpeciesBaseAttack(SPECIES_MAWILE), 95);
    EXPECT_EQ(GetSpeciesBaseDefense(SPECIES_MAWILE), 95);
    EXPECT_EQ(GetSpeciesBaseSpAttack(SPECIES_MAWILE_MEGA), 75);
}

TEST("Elastic-tests: Badge two Beautifly and Dustox retain their custom second abilities")
{
    EXPECT_EQ(GetSpeciesAbility(SPECIES_BEAUTIFLY, 1), ABILITY_WIND_RIDER);
    EXPECT_EQ(GetSpeciesAbility(SPECIES_DUSTOX, 1), ABILITY_CORROSION);
}

TEST("Elastic-tests: Mystic and Dominate remain assigned to their intended species")
{
    EXPECT_EQ(GetSpeciesAbility(SPECIES_GOLDUCK, 0), ABILITY_MYSTIC);
    EXPECT_EQ(GetSpeciesAbility(SPECIES_NOCTOWL, 1), ABILITY_MYSTIC);
    EXPECT_EQ(GetSpeciesAbility(SPECIES_STANTLER, 1), ABILITY_MYSTIC);
    EXPECT_EQ(GetSpeciesAbility(SPECIES_LOUDRED, 1), ABILITY_DOMINATE);
    EXPECT_EQ(GetSpeciesAbility(SPECIES_EXPLOUD, 1), ABILITY_DOMINATE);
}

TEST("Elastic-tests: Astral Charge remains assigned to Ledian and the Gothitelle line")
{
    EXPECT_EQ(GetSpeciesAbility(SPECIES_LEDIAN, 2), ABILITY_ASTRAL_CHARGE);
    EXPECT_EQ(GetSpeciesAbility(SPECIES_GOTHORITA, 0), ABILITY_ASTRAL_CHARGE);
    EXPECT_EQ(GetSpeciesAbility(SPECIES_GOTHITELLE, 0), ABILITY_ASTRAL_CHARGE);
}

TEST("Elastic-tests: Early Astral Charge batch species retain their custom stat buffs")
{
    EXPECT_EQ(GetSpeciesBaseSpAttack(SPECIES_QWILFISH), 65);
    EXPECT_EQ(GetSpeciesBaseSpAttack(SPECIES_QWILFISH_HISUI), 65);
    EXPECT_EQ(GetSpeciesBaseSpDefense(SPECIES_QWILFISH_HISUI), 65);
    EXPECT_EQ(GetSpeciesBaseHP(SPECIES_LUVDISC), 53);
    EXPECT_EQ(GetSpeciesBaseDefense(SPECIES_LUVDISC), 65);
    EXPECT_EQ(GetSpeciesBaseSpeed(SPECIES_LUVDISC), 107);
    EXPECT_EQ(GetSpeciesBaseSpDefense(SPECIES_LUVDISC), 75);
    EXPECT_EQ(GetSpeciesBaseHP(SPECIES_CRANIDOS), 72);
    EXPECT_EQ(GetSpeciesBaseHP(SPECIES_SHIELDON), 35);
    EXPECT_EQ(GetSpeciesBaseDefense(SPECIES_BOUNSWEET), 48);
    EXPECT_EQ(GetSpeciesBaseSpDefense(SPECIES_BOUNSWEET), 48);
    EXPECT_EQ(GetSpeciesBaseAttack(SPECIES_STEENEE), 60);
    EXPECT_EQ(GetSpeciesBaseDefense(SPECIES_STEENEE), 58);
    EXPECT_EQ(GetSpeciesBaseSpDefense(SPECIES_STEENEE), 58);
}

TEST("Elastic-tests: Early Astral Charge batch evolution levels remain reduced")
{
    struct Pokemon mon;

    CreateMon(&mon, SPECIES_CLAUNCHER, 31, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, NULL, CHECK_EVO), SPECIES_CLAWITZER);
    CreateMon(&mon, SPECIES_NOIBAT, 35, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, NULL, CHECK_EVO), SPECIES_NOIVERN);
    CreateMon(&mon, SPECIES_IMPIDIMP, 24, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, NULL, CHECK_EVO), SPECIES_MORGREM);
    CreateMon(&mon, SPECIES_MORGREM, 36, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, NULL, CHECK_EVO), SPECIES_GRIMMSNARL);
    CreateMon(&mon, SPECIES_DREEPY, 35, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, NULL, CHECK_EVO), SPECIES_DRAKLOAK);
    CreateMon(&mon, SPECIES_DRAKLOAK, 56, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, NULL, CHECK_EVO), SPECIES_DRAGAPULT);
    CreateMon(&mon, SPECIES_SHROODLE, 25, 0, OTID_STRUCT_PLAYER_ID);
    EXPECT_EQ(GetEvolutionTargetSpecies(&mon, EVO_MODE_NORMAL, ITEM_NONE, NULL, NULL, CHECK_EVO), SPECIES_GRAFAIAI);
}

TEST("Elastic-tests: May 2025 evolution rebalance levels remain intact")
{
    static const struct
    {
        enum Species species;
        u32 level;
    } cases[] =
    {
        { SPECIES_SPOINK, 26 },
        { SPECIES_CACNEA, 26 },
        { SPECIES_SNORUNT, 32 },
        { SPECIES_VANILLITE, 25 },
        { SPECIES_PANCHAM, 30 },
        { SPECIES_BINACLE, 34 },
        { SPECIES_SILICOBRA, 32 },
    };
    u32 i;

    for (i = 0; i < ARRAY_COUNT(cases); i++)
        EXPECT_EQ(GetSpeciesEvolutions(cases[i].species)[0].param, cases[i].level);
}

TEST("Elastic-tests: Shuppet retains its May 2025 special bulk buff")
{
    EXPECT_EQ(GetSpeciesBaseSpDefense(SPECIES_SHUPPET), 43);
}

TEST("Elastic-tests: Noibat retains its pre-Dewford custom stat buffs")
{
    EXPECT_EQ(GetSpeciesBaseHP(SPECIES_NOIBAT), 45);
    EXPECT_EQ(GetSpeciesBaseDefense(SPECIES_NOIBAT), 40);
    EXPECT_EQ(GetSpeciesBaseSpeed(SPECIES_NOIBAT), 65);
    EXPECT_EQ(GetSpeciesBaseSpAttack(SPECIES_NOIBAT), 55);
}

TEST("Elastic-tests: Delibird retains Merry as its primary ability")
{
    EXPECT_EQ(GetSpeciesAbility(SPECIES_DELIBIRD, 0), ABILITY_MERRY);
    EXPECT_EQ(GetSpeciesAbility(SPECIES_DELIBIRD, 1), ABILITY_HUSTLE);
    EXPECT_EQ(GetSpeciesAbility(SPECIES_DELIBIRD, 2), ABILITY_VITAL_SPIRIT);
}

TEST("Elastic-tests: Beautifly retains its custom Mud-Slap tutor compatibility")
{
    EXPECT(CanLearnTeachableMove(SPECIES_BEAUTIFLY, MOVE_MUD_SLAP));
}
