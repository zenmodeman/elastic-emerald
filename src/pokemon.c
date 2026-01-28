#include "global.h"
#include "malloc.h"
#include "apprentice.h"
#include "battle.h"
#include "battle_ai_switch_items.h"
#include "battle_anim.h"
#include "battle_controllers.h"
#include "battle_message.h"
#include "battle_pike.h"
#include "battle_pyramid.h"
#include "battle_setup.h"
#include "battle_tower.h"
#include "battle_z_move.h"
#include "data.h"
#include "dexnav.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "evolution_scene.h"
#include "field_player_avatar.h"
#include "field_specials.h"
#include "field_weather.h"
#include "follower_npc.h"
#include "graphics.h"
#include "item.h"
#include "caps.h"
#include "link.h"
#include "main.h"
#include "overworld.h"
#include "m4a.h"
#include "party_menu.h"
#include "pokedex.h"
#include "pokeblock.h"
#include "pokemon.h"
#include "pokemon_animation.h"
#include "pokemon_icon.h"
#include "pokemon_summary_screen.h"
#include "pokemon_storage_system.h"
#include "random.h"
#include "recorded_battle.h"
#include "rtc.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "test_runner.h"
#include "text.h"
#include "trainer_hill.h"
#include "util.h"
#include "constants/abilities.h"
#include "constants/battle_frontier.h"
#include "constants/battle_move_effects.h"
#include "constants/battle_script_commands.h"
#include "constants/battle_partner.h"
#include "constants/battle_string_ids.h"
#include "constants/cries.h"
#include "constants/event_objects.h"
#include "constants/form_change_types.h"
#include "constants/hold_effects.h"
#include "constants/item_effects.h"
#include "constants/items.h"
#include "constants/layouts.h"
#include "constants/moves.h"
#include "constants/regions.h"
#include "constants/songs.h"
#include "constants/trainers.h"
#include "constants/union_room.h"
#include "constants/weather.h"
#include "wild_encounter.h"

#include "data/pokemon/center_tutor_moves.h"

#define FRIENDSHIP_EVO_THRESHOLD ((P_FRIENDSHIP_EVO_THRESHOLD >= GEN_8) ? 160 : 220)



struct SpeciesItem
{
    u16 species;
    u16 item;
};

static u16 CalculateBoxMonChecksum(struct BoxPokemon *boxMon);
static union PokemonSubstruct *GetSubstruct(struct BoxPokemon *boxMon, u32 personality, u8 substructType);
static void EncryptBoxMon(struct BoxPokemon *boxMon);
static void DecryptBoxMon(struct BoxPokemon *boxMon);
static void Task_PlayMapChosenOrBattleBGM(u8 taskId);
static bool8 ShouldSkipFriendshipChange(void);
void TrySpecialOverworldEvo();

EWRAM_DATA static u8 sLearningMoveTableID = 0;
EWRAM_DATA u8 gPlayerPartyCount = 0;
EWRAM_DATA u8 gEnemyPartyCount = 0;
EWRAM_DATA struct Pokemon gPlayerParty[PARTY_SIZE] = {0};
EWRAM_DATA struct Pokemon gEnemyParty[PARTY_SIZE] = {0};
EWRAM_DATA struct SpriteTemplate gMultiuseSpriteTemplate = {0};
EWRAM_DATA static struct MonSpritesGfxManager *sMonSpritesGfxManagers[MON_SPR_GFX_MANAGERS_COUNT] = {NULL};
EWRAM_DATA static u8 sTriedEvolving = 0;
EWRAM_DATA u16 gFollowerSteps = 0;

#include "data/abilities.h"
#if P_TUTOR_MOVES_ARRAY
#include "data/tutor_moves.h"
#endif // P_TUTOR_MOVES_ARRAY

u32 gExcessTierPoints = 0; //Global to keep track of whether Tier Points have been exceeded

// Used in an unreferenced function in RS.
// Unreferenced here and in FRLG.
struct CombinedMove
{
    u16 move1;
    u16 move2;
    u16 newMove;
};

static const struct CombinedMove sCombinedMoves[2] =
{
    {MOVE_EMBER, MOVE_GUST, MOVE_HEAT_WAVE},
    {0xFFFF, 0xFFFF, 0xFFFF}
};

// NOTE: The order of the elements in the array below is irrelevant.
// To reorder the pokedex, see the values in include/constants/pokedex.h.

#define HOENN_TO_NATIONAL(name)     [HOENN_DEX_##name - 1] = NATIONAL_DEX_##name

// Assigns all Hoenn Dex Indexes to a National Dex Index
static const u16 sHoennToNationalOrder[HOENN_DEX_COUNT - 1] =
{
    HOENN_TO_NATIONAL(TREECKO),
    HOENN_TO_NATIONAL(GROVYLE),
    HOENN_TO_NATIONAL(SCEPTILE),
    HOENN_TO_NATIONAL(TORCHIC),
    HOENN_TO_NATIONAL(COMBUSKEN),
    HOENN_TO_NATIONAL(BLAZIKEN),
    HOENN_TO_NATIONAL(MUDKIP),
    HOENN_TO_NATIONAL(MARSHTOMP),
    HOENN_TO_NATIONAL(SWAMPERT),
    HOENN_TO_NATIONAL(POOCHYENA),
    HOENN_TO_NATIONAL(MIGHTYENA),
    HOENN_TO_NATIONAL(ZIGZAGOON),
    HOENN_TO_NATIONAL(LINOONE),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GALARIAN_FORMS
    HOENN_TO_NATIONAL(OBSTAGOON),
#endif
    HOENN_TO_NATIONAL(WURMPLE),
    HOENN_TO_NATIONAL(SILCOON),
    HOENN_TO_NATIONAL(BEAUTIFLY),
    HOENN_TO_NATIONAL(CASCOON),
    HOENN_TO_NATIONAL(DUSTOX),
    HOENN_TO_NATIONAL(LOTAD),
    HOENN_TO_NATIONAL(LOMBRE),
    HOENN_TO_NATIONAL(LUDICOLO),
    HOENN_TO_NATIONAL(SEEDOT),
    HOENN_TO_NATIONAL(NUZLEAF),
    HOENN_TO_NATIONAL(SHIFTRY),
    HOENN_TO_NATIONAL(TAILLOW),
    HOENN_TO_NATIONAL(SWELLOW),
    HOENN_TO_NATIONAL(WINGULL),
    HOENN_TO_NATIONAL(PELIPPER),
    HOENN_TO_NATIONAL(RALTS),
    HOENN_TO_NATIONAL(KIRLIA),
    HOENN_TO_NATIONAL(GARDEVOIR),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GEN_4_CROSS_EVOS
    HOENN_TO_NATIONAL(GALLADE),
#endif
    HOENN_TO_NATIONAL(SURSKIT),
    HOENN_TO_NATIONAL(MASQUERAIN),
    HOENN_TO_NATIONAL(SHROOMISH),
    HOENN_TO_NATIONAL(BRELOOM),
    HOENN_TO_NATIONAL(SLAKOTH),
    HOENN_TO_NATIONAL(VIGOROTH),
    HOENN_TO_NATIONAL(SLAKING),
    HOENN_TO_NATIONAL(ABRA),
    HOENN_TO_NATIONAL(KADABRA),
    HOENN_TO_NATIONAL(ALAKAZAM),
    HOENN_TO_NATIONAL(NINCADA),
    HOENN_TO_NATIONAL(NINJASK),
    HOENN_TO_NATIONAL(SHEDINJA),
    HOENN_TO_NATIONAL(WHISMUR),
    HOENN_TO_NATIONAL(LOUDRED),
    HOENN_TO_NATIONAL(EXPLOUD),
    HOENN_TO_NATIONAL(MAKUHITA),
    HOENN_TO_NATIONAL(HARIYAMA),
    HOENN_TO_NATIONAL(GOLDEEN),
    HOENN_TO_NATIONAL(SEAKING),
    HOENN_TO_NATIONAL(MAGIKARP),
    HOENN_TO_NATIONAL(GYARADOS),
    HOENN_TO_NATIONAL(AZURILL),
    HOENN_TO_NATIONAL(MARILL),
    HOENN_TO_NATIONAL(AZUMARILL),
    HOENN_TO_NATIONAL(GEODUDE),
    HOENN_TO_NATIONAL(GRAVELER),
    HOENN_TO_NATIONAL(GOLEM),
    HOENN_TO_NATIONAL(NOSEPASS),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GEN_4_CROSS_EVOS
    HOENN_TO_NATIONAL(PROBOPASS),
#endif
    HOENN_TO_NATIONAL(SKITTY),
    HOENN_TO_NATIONAL(DELCATTY),
    HOENN_TO_NATIONAL(ZUBAT),
    HOENN_TO_NATIONAL(GOLBAT),
    HOENN_TO_NATIONAL(CROBAT),
    HOENN_TO_NATIONAL(TENTACOOL),
    HOENN_TO_NATIONAL(TENTACRUEL),
    HOENN_TO_NATIONAL(SABLEYE),
    HOENN_TO_NATIONAL(MAWILE),
    HOENN_TO_NATIONAL(ARON),
    HOENN_TO_NATIONAL(LAIRON),
    HOENN_TO_NATIONAL(AGGRON),
    HOENN_TO_NATIONAL(MACHOP),
    HOENN_TO_NATIONAL(MACHOKE),
    HOENN_TO_NATIONAL(MACHAMP),
    HOENN_TO_NATIONAL(MEDITITE),
    HOENN_TO_NATIONAL(MEDICHAM),
    HOENN_TO_NATIONAL(ELECTRIKE),
    HOENN_TO_NATIONAL(MANECTRIC),
    HOENN_TO_NATIONAL(PLUSLE),
    HOENN_TO_NATIONAL(MINUN),
    HOENN_TO_NATIONAL(MAGNEMITE),
    HOENN_TO_NATIONAL(MAGNETON),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GEN_4_CROSS_EVOS
    HOENN_TO_NATIONAL(MAGNEZONE),
#endif
    HOENN_TO_NATIONAL(VOLTORB),
    HOENN_TO_NATIONAL(ELECTRODE),
    HOENN_TO_NATIONAL(VOLBEAT),
    HOENN_TO_NATIONAL(ILLUMISE),
    HOENN_TO_NATIONAL(ODDISH),
    HOENN_TO_NATIONAL(GLOOM),
    HOENN_TO_NATIONAL(VILEPLUME),
    HOENN_TO_NATIONAL(BELLOSSOM),
    HOENN_TO_NATIONAL(DODUO),
    HOENN_TO_NATIONAL(DODRIO),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GEN_4_CROSS_EVOS
    HOENN_TO_NATIONAL(BUDEW),
    HOENN_TO_NATIONAL(ROSELIA),
    HOENN_TO_NATIONAL(ROSERADE),
#else
    HOENN_TO_NATIONAL(ROSELIA),
#endif
    HOENN_TO_NATIONAL(GULPIN),
    HOENN_TO_NATIONAL(SWALOT),
    HOENN_TO_NATIONAL(CARVANHA),
    HOENN_TO_NATIONAL(SHARPEDO),
    HOENN_TO_NATIONAL(WAILMER),
    HOENN_TO_NATIONAL(WAILORD),
    HOENN_TO_NATIONAL(NUMEL),
    HOENN_TO_NATIONAL(CAMERUPT),
    HOENN_TO_NATIONAL(SLUGMA),
    HOENN_TO_NATIONAL(MAGCARGO),
    HOENN_TO_NATIONAL(TORKOAL),
    HOENN_TO_NATIONAL(GRIMER),
    HOENN_TO_NATIONAL(MUK),
    HOENN_TO_NATIONAL(KOFFING),
    HOENN_TO_NATIONAL(WEEZING),
    HOENN_TO_NATIONAL(SPOINK),
    HOENN_TO_NATIONAL(GRUMPIG),
    HOENN_TO_NATIONAL(SANDSHREW),
    HOENN_TO_NATIONAL(SANDSLASH),
    HOENN_TO_NATIONAL(SPINDA),
    HOENN_TO_NATIONAL(SKARMORY),
    HOENN_TO_NATIONAL(TRAPINCH),
    HOENN_TO_NATIONAL(VIBRAVA),
    HOENN_TO_NATIONAL(FLYGON),
    HOENN_TO_NATIONAL(CACNEA),
    HOENN_TO_NATIONAL(CACTURNE),
    HOENN_TO_NATIONAL(SWABLU),
    HOENN_TO_NATIONAL(ALTARIA),
    HOENN_TO_NATIONAL(ZANGOOSE),
    HOENN_TO_NATIONAL(SEVIPER),
    HOENN_TO_NATIONAL(LUNATONE),
    HOENN_TO_NATIONAL(SOLROCK),
    HOENN_TO_NATIONAL(BARBOACH),
    HOENN_TO_NATIONAL(WHISCASH),
    HOENN_TO_NATIONAL(CORPHISH),
    HOENN_TO_NATIONAL(CRAWDAUNT),
    HOENN_TO_NATIONAL(BALTOY),
    HOENN_TO_NATIONAL(CLAYDOL),
    HOENN_TO_NATIONAL(LILEEP),
    HOENN_TO_NATIONAL(CRADILY),
    HOENN_TO_NATIONAL(ANORITH),
    HOENN_TO_NATIONAL(ARMALDO),
    HOENN_TO_NATIONAL(IGGLYBUFF),
    HOENN_TO_NATIONAL(JIGGLYPUFF),
    HOENN_TO_NATIONAL(WIGGLYTUFF),
    HOENN_TO_NATIONAL(FEEBAS),
    HOENN_TO_NATIONAL(MILOTIC),
    HOENN_TO_NATIONAL(CASTFORM),
    HOENN_TO_NATIONAL(STARYU),
    HOENN_TO_NATIONAL(STARMIE),
    HOENN_TO_NATIONAL(KECLEON),
    HOENN_TO_NATIONAL(SHUPPET),
    HOENN_TO_NATIONAL(BANETTE),
    HOENN_TO_NATIONAL(DUSKULL),
    HOENN_TO_NATIONAL(DUSCLOPS),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GEN_4_CROSS_EVOS
    HOENN_TO_NATIONAL(DUSKNOIR),
    HOENN_TO_NATIONAL(TROPIUS),
    HOENN_TO_NATIONAL(CHINGLING),
#else
    HOENN_TO_NATIONAL(TROPIUS),
#endif
    HOENN_TO_NATIONAL(CHIMECHO),
    HOENN_TO_NATIONAL(ABSOL),
    HOENN_TO_NATIONAL(VULPIX),
    HOENN_TO_NATIONAL(NINETALES),
    HOENN_TO_NATIONAL(PICHU),
    HOENN_TO_NATIONAL(PIKACHU),
    HOENN_TO_NATIONAL(RAICHU),
    HOENN_TO_NATIONAL(PSYDUCK),
    HOENN_TO_NATIONAL(GOLDUCK),
    HOENN_TO_NATIONAL(WYNAUT),
    HOENN_TO_NATIONAL(WOBBUFFET),
    HOENN_TO_NATIONAL(NATU),
    HOENN_TO_NATIONAL(XATU),
    HOENN_TO_NATIONAL(GIRAFARIG),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GEN_9_CROSS_EVOS
    HOENN_TO_NATIONAL(FARIGIRAF),
#endif
    HOENN_TO_NATIONAL(PHANPY),
    HOENN_TO_NATIONAL(DONPHAN),
    HOENN_TO_NATIONAL(PINSIR),
    HOENN_TO_NATIONAL(HERACROSS),
    HOENN_TO_NATIONAL(RHYHORN),
    HOENN_TO_NATIONAL(RHYDON),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GEN_4_CROSS_EVOS
    HOENN_TO_NATIONAL(RHYPERIOR),
#endif
    HOENN_TO_NATIONAL(SNORUNT),
    HOENN_TO_NATIONAL(GLALIE),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GEN_4_CROSS_EVOS
    HOENN_TO_NATIONAL(FROSLASS),
#endif
    HOENN_TO_NATIONAL(SPHEAL),
    HOENN_TO_NATIONAL(SEALEO),
    HOENN_TO_NATIONAL(WALREIN),
    HOENN_TO_NATIONAL(CLAMPERL),
    HOENN_TO_NATIONAL(HUNTAIL),
    HOENN_TO_NATIONAL(GOREBYSS),
    HOENN_TO_NATIONAL(RELICANTH),
    HOENN_TO_NATIONAL(CORSOLA),
#if P_NEW_EVOS_IN_REGIONAL_DEX && P_GALARIAN_FORMS
    HOENN_TO_NATIONAL(CURSOLA),
#endif
    HOENN_TO_NATIONAL(CHINCHOU),
    HOENN_TO_NATIONAL(LANTURN),
    HOENN_TO_NATIONAL(LUVDISC),
    HOENN_TO_NATIONAL(HORSEA),
    HOENN_TO_NATIONAL(SEADRA),
    HOENN_TO_NATIONAL(KINGDRA),
    HOENN_TO_NATIONAL(BAGON),
    HOENN_TO_NATIONAL(SHELGON),
    HOENN_TO_NATIONAL(SALAMENCE),
    HOENN_TO_NATIONAL(BELDUM),
    HOENN_TO_NATIONAL(METANG),
    HOENN_TO_NATIONAL(METAGROSS),
    HOENN_TO_NATIONAL(REGIROCK),
    HOENN_TO_NATIONAL(REGICE),
    HOENN_TO_NATIONAL(REGISTEEL),
    HOENN_TO_NATIONAL(LATIAS),
    HOENN_TO_NATIONAL(LATIOS),
    HOENN_TO_NATIONAL(KYOGRE),
    HOENN_TO_NATIONAL(GROUDON),
    HOENN_TO_NATIONAL(RAYQUAZA),
    HOENN_TO_NATIONAL(JIRACHI),
    HOENN_TO_NATIONAL(DEOXYS),
};

const struct SpindaSpot gSpindaSpotGraphics[] =
{
    {.x = 16, .y =  7, .image = INCBIN_U16("graphics/pokemon/spinda/spots/spot_0.1bpp")},
    {.x = 40, .y =  8, .image = INCBIN_U16("graphics/pokemon/spinda/spots/spot_1.1bpp")},
    {.x = 22, .y = 25, .image = INCBIN_U16("graphics/pokemon/spinda/spots/spot_2.1bpp")},
    {.x = 34, .y = 26, .image = INCBIN_U16("graphics/pokemon/spinda/spots/spot_3.1bpp")}
};

// In Battle Palace, moves are chosen based on the pokemons nature rather than by the player
// Moves are grouped into "Attack", "Defense", or "Support" (see PALACE_MOVE_GROUP_*)
// Each nature has a certain percent chance of selecting a move from a particular group
// and a separate percent chance for each group when at or below 50% HP
// The table below doesn't list percentages for Support because you can subtract the other two
// Support percentages are listed in comments off to the side instead
#define PALACE_STYLE(atk, def, atkLow, defLow) {atk, atk + def, atkLow, atkLow + defLow}

const struct NatureInfo gNaturesInfo[NUM_NATURES] =
{
    [NATURE_HARDY] =
    {
        .name = COMPOUND_STRING("Hardy"),
        .statUp = STAT_ATK,
        .statDown = STAT_ATK,
        .backAnim = 0,
        .pokeBlockAnim = {ANIM_HARDY, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(61, 7, 61, 7), //32% support >= 50% HP, 32% support < 50% HP
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_LONELY] =
    {
        .name = COMPOUND_STRING("Lonely"),
        .statUp = STAT_ATK,
        .statDown = STAT_DEF,
        .backAnim = 2,
        .pokeBlockAnim = {ANIM_LONELY, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlSupportHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(20, 25, 84, 8), //55%,  8%
        .battlePalaceFlavorText = B_MSG_GLINT_IN_EYE,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_BRAVE] =
    {
        .name = COMPOUND_STRING("Brave"),
        .statUp = STAT_ATK,
        .statDown = STAT_SPEED,
        .backAnim = 0,
        .pokeBlockAnim = {ANIM_BRAVE, AFFINE_TURN_UP},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighDefenseLow,
        .battlePalacePercents = PALACE_STYLE(70, 15, 32, 60), //15%, 8%
        .battlePalaceFlavorText = B_MSG_GETTING_IN_POS,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_ADAMANT] =
    {
        .name = COMPOUND_STRING("Adamant"),
        .statUp = STAT_ATK,
        .statDown = STAT_SPATK,
        .backAnim = 0,
        .pokeBlockAnim = {ANIM_ADAMANT, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(38, 31, 70, 15), //31%, 15%
        .battlePalaceFlavorText = B_MSG_GLINT_IN_EYE,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_NAUGHTY] =
    {
        .name = COMPOUND_STRING("Naughty"),
        .statUp = STAT_ATK,
        .statDown = STAT_SPDEF,
        .backAnim = 0,
        .pokeBlockAnim = {ANIM_NAUGHTY, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlDefenseHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(20, 70, 70, 22), //10%, 8%
        .battlePalaceFlavorText = B_MSG_GLINT_IN_EYE,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_BOLD] =
    {
        .name = COMPOUND_STRING("Bold"),
        .statUp = STAT_DEF,
        .statDown = STAT_ATK,
        .backAnim = 1,
        .pokeBlockAnim = {ANIM_BOLD, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlSupportHighDefenseLow,
        .battlePalacePercents = PALACE_STYLE(30, 20, 32, 58), //50%, 10%
        .battlePalaceFlavorText = B_MSG_GETTING_IN_POS,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_DOCILE] =
    {
        .name = COMPOUND_STRING("Docile"),
        .statUp = STAT_DEF,
        .statDown = STAT_DEF,
        .backAnim = 1,
        .pokeBlockAnim = {ANIM_DOCILE, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(56, 22, 56, 22), //22%, 22%
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_RANDOM,
    },
    [NATURE_RELAXED] =
    {
        .name = COMPOUND_STRING("Relaxed"),
        .statUp = STAT_DEF,
        .statDown = STAT_SPEED,
        .backAnim = 1,
        .pokeBlockAnim = {ANIM_RELAXED, AFFINE_TURN_UP_AND_DOWN},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlSupportHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(25, 15, 75, 15), //60%, 10%
        .battlePalaceFlavorText = B_MSG_GLINT_IN_EYE,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_IMPISH] =
    {
        .name = COMPOUND_STRING("Impish"),
        .statUp = STAT_DEF,
        .statDown = STAT_SPATK,
        .backAnim = 0,
        .pokeBlockAnim = {ANIM_IMPISH, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighDefenseLow,
        .battlePalacePercents = PALACE_STYLE(69, 6, 28, 55), //25%, 17%
        .battlePalaceFlavorText = B_MSG_GETTING_IN_POS,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_LAX] =
    {
        .name = COMPOUND_STRING("Lax"),
        .statUp = STAT_DEF,
        .statDown = STAT_SPDEF,
        .backAnim = 1,
        .pokeBlockAnim = {ANIM_LAX, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlSupportHighSupportLow,
        .battlePalacePercents = PALACE_STYLE(35, 10, 29, 6), //55%, 65%
        .battlePalaceFlavorText = B_MSG_GROWL_DEEPLY,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_TIMID] =
    {
        .name = COMPOUND_STRING("Timid"),
        .statUp = STAT_SPEED,
        .statDown = STAT_ATK,
        .backAnim = 2,
        .pokeBlockAnim = {ANIM_TIMID, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighSupportLow,
        .battlePalacePercents = PALACE_STYLE(62, 10, 30, 20), //28%, 50%
        .battlePalaceFlavorText = B_MSG_GROWL_DEEPLY,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_HASTY] =
    {
        .name = COMPOUND_STRING("Hasty"),
        .statUp = STAT_SPEED,
        .statDown = STAT_DEF,
        .backAnim = 0,
        .pokeBlockAnim = {ANIM_HASTY, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(58, 37, 88, 6), //5%, 6%
        .battlePalaceFlavorText = B_MSG_GLINT_IN_EYE,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_SERIOUS] =
    {
        .name = COMPOUND_STRING("Serious"),
        .statUp = STAT_SPEED,
        .statDown = STAT_SPEED,
        .backAnim = 1,
        .pokeBlockAnim = {ANIM_SERIOUS, AFFINE_TURN_DOWN},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlSupportHighSupportLow,
        .battlePalacePercents = PALACE_STYLE(34, 11, 29, 11), //55%, 60%
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_JOLLY] =
    {
        .name = COMPOUND_STRING("Jolly"),
        .statUp = STAT_SPEED,
        .statDown = STAT_SPATK,
        .backAnim = 0,
        .pokeBlockAnim = {ANIM_JOLLY, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlSupportHighDefenseLow,
        .battlePalacePercents = PALACE_STYLE(35, 5, 35, 60), //60%, 5%
        .battlePalaceFlavorText = B_MSG_GETTING_IN_POS,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_NAIVE] =
    {
        .name = COMPOUND_STRING("Naive"),
        .statUp = STAT_SPEED,
        .statDown = STAT_SPDEF,
        .backAnim = 0,
        .pokeBlockAnim = {ANIM_NAIVE, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(56, 22, 56, 22), //22%, 22%
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_RANDOM,
    },
    [NATURE_MODEST] =
    {
        .name = COMPOUND_STRING("Modest"),
        .statUp = STAT_SPATK,
        .statDown = STAT_ATK,
        .backAnim = 2,
        .pokeBlockAnim = {ANIM_MODEST, AFFINE_TURN_DOWN_SLOW},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlDefenseHighDefenseLow,
        .battlePalacePercents = PALACE_STYLE(35, 45, 34, 60), //20%, 6%
        .battlePalaceFlavorText = B_MSG_GETTING_IN_POS,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_MILD] =
    {
        .name = COMPOUND_STRING("Mild"),
        .statUp = STAT_SPATK,
        .statDown = STAT_DEF,
        .backAnim = 2,
        .pokeBlockAnim = {ANIM_MILD, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlDefenseHighSupportLow,
        .battlePalacePercents = PALACE_STYLE(44, 50, 34, 6), //6%, 60%
        .battlePalaceFlavorText = B_MSG_GROWL_DEEPLY,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_QUIET] =
    {
        .name = COMPOUND_STRING("Quiet"),
        .statUp = STAT_SPATK,
        .statDown = STAT_SPEED,
        .backAnim = 2,
        .pokeBlockAnim = {ANIM_QUIET, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(56, 22, 56, 22), //22%, 22%
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_BASHFUL] =
    {
        .name = COMPOUND_STRING("Bashful"),
        .statUp = STAT_SPATK,
        .statDown = STAT_SPATK,
        .backAnim = 2,
        .pokeBlockAnim = {ANIM_BASHFUL, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlDefenseHighDefenseLow,
        .battlePalacePercents = PALACE_STYLE(30, 58, 30, 58), //12%, 12%
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_RASH] =
    {
        .name = COMPOUND_STRING("Rash"),
        .statUp = STAT_SPATK,
        .statDown = STAT_SPDEF,
        .backAnim = 1,
        .pokeBlockAnim = {ANIM_RASH, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlSupportHighSupportLow,
        .battlePalacePercents = PALACE_STYLE(30, 13, 27, 6), //57%, 67%
        .battlePalaceFlavorText = B_MSG_GROWL_DEEPLY,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_CALM] =
    {
        .name = COMPOUND_STRING("Calm"),
        .statUp = STAT_SPDEF,
        .statDown = STAT_ATK,
        .backAnim = 1,
        .pokeBlockAnim = {ANIM_CALM, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlDefenseHighDefenseLow,
        .battlePalacePercents = PALACE_STYLE(40, 50, 25, 62), //10%, 13%
        .battlePalaceFlavorText = B_MSG_GETTING_IN_POS,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_GENTLE] =
    {
        .name = COMPOUND_STRING("Gentle"),
        .statUp = STAT_SPDEF,
        .statDown = STAT_DEF,
        .backAnim = 2,
        .pokeBlockAnim = {ANIM_GENTLE, AFFINE_TURN_DOWN_SLIGHT},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlDefenseHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(18, 70, 90, 5), //12%, 5%
        .battlePalaceFlavorText = B_MSG_GLINT_IN_EYE,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
    [NATURE_SASSY] =
    {
        .name = COMPOUND_STRING("Sassy"),
        .statUp = STAT_SPDEF,
        .statDown = STAT_SPEED,
        .backAnim = 1,
        .pokeBlockAnim = {ANIM_SASSY, AFFINE_TURN_UP_HIGH},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighSupportLow,
        .battlePalacePercents = PALACE_STYLE(88, 6, 22, 20), //6%, 58%
        .battlePalaceFlavorText = B_MSG_GROWL_DEEPLY,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_CAREFUL] =
    {
        .name = COMPOUND_STRING("Careful"),
        .statUp = STAT_SPDEF,
        .statDown = STAT_SPATK,
        .backAnim = 2,
        .pokeBlockAnim = {ANIM_CAREFUL, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlDefenseHighSupportLow,
        .battlePalacePercents = PALACE_STYLE(42, 50, 42, 5), //8%, 53%
        .battlePalaceFlavorText = B_MSG_GROWL_DEEPLY,
        .battlePalaceSmokescreen = PALACE_TARGET_WEAKER,
    },
    [NATURE_QUIRKY] =
    {
        .name = COMPOUND_STRING("Quirky"),
        .statUp = STAT_SPDEF,
        .statDown = STAT_SPDEF,
        .backAnim = 1,
        .pokeBlockAnim = {ANIM_QUIRKY, AFFINE_NONE},
        .natureGirlMessage = BattleFrontier_Lounge5_Text_NatureGirlAttackHighAttackLow,
        .battlePalacePercents = PALACE_STYLE(56, 22, 56, 22), //22%, 22%
        .battlePalaceFlavorText = B_MSG_EAGER_FOR_MORE,
        .battlePalaceSmokescreen = PALACE_TARGET_STRONGER,
    },
};

#include "data/graphics/pokemon.h"

#include "data/pokemon/trainer_class_lookups.h"
#include "data/pokemon/experience_tables.h"

#if P_LVL_UP_LEARNSETS >= GEN_9
#include "data/pokemon/level_up_learnsets/gen_9.h" // Scarlet/Violet
#elif P_LVL_UP_LEARNSETS >= GEN_8
#include "data/pokemon/level_up_learnsets/gen_8.h" // Sword/Shield
#elif P_LVL_UP_LEARNSETS >= GEN_7
#include "data/pokemon/level_up_learnsets/gen_7.h" // Ultra Sun/Ultra Moon
#elif P_LVL_UP_LEARNSETS >= GEN_6
#include "data/pokemon/level_up_learnsets/gen_6.h" // Omega Ruby/Alpha Sapphire
#elif P_LVL_UP_LEARNSETS >= GEN_5
#include "data/pokemon/level_up_learnsets/gen_5.h" // Black 2/White 2
#elif P_LVL_UP_LEARNSETS >= GEN_4
#include "data/pokemon/level_up_learnsets/gen_4.h" // HeartGold/SoulSilver
#elif P_LVL_UP_LEARNSETS >= GEN_3
#include "data/pokemon/level_up_learnsets/gen_3.h" // Ruby/Sapphire/Emerald
#elif P_LVL_UP_LEARNSETS >= GEN_2
#include "data/pokemon/level_up_learnsets/gen_2.h" // Crystal
#elif P_LVL_UP_LEARNSETS >= GEN_1
#include "data/pokemon/level_up_learnsets/gen_1.h" // Yellow
#endif

#include "data/pokemon/teachable_learnsets.h"
#include "data/pokemon/egg_moves.h"
#include "data/pokemon/form_species_tables.h"
#include "data/pokemon/form_change_tables.h"
#include "data/pokemon/form_change_table_pointers.h"
#include "data/object_events/object_event_pic_tables_followers.h"

#include "data/pokemon/species_info.h"

#define PP_UP_SHIFTS(val)           val,        (val) << 2,        (val) << 4,        (val) << 6
#define PP_UP_SHIFTS_INV(val) (u8)~(val), (u8)~((val) << 2), (u8)~((val) << 4), (u8)~((val) << 6)

// PP Up bonuses are stored for a Pokémon as a single byte.
// There are 2 bits (a value 0-3) for each move slot that
// represent how many PP Ups have been applied.
// The following arrays take a move slot id and return:
// gPPUpGetMask - A mask to get the number of PP Ups applied to that move slot
// gPPUpClearMask - A mask to clear the number of PP Ups applied to that move slot
// gPPUpAddValues - A value to add to the PP Bonuses byte to apply 1 PP Up to that move slot
const u8 gPPUpGetMask[MAX_MON_MOVES]   = {PP_UP_SHIFTS(3)};
const u8 gPPUpClearMask[MAX_MON_MOVES] = {PP_UP_SHIFTS_INV(3)};
const u8 gPPUpAddValues[MAX_MON_MOVES] = {PP_UP_SHIFTS(1)};

const u8 gStatStageRatios[MAX_STAT_STAGE + 1][2] =
{
    {10, 40}, // -6, MIN_STAT_STAGE
    {10, 35}, // -5
    {10, 30}, // -4
    {10, 25}, // -3
    {10, 20}, // -2
    {10, 15}, // -1
    {10, 10}, //  0, DEFAULT_STAT_STAGE
    {15, 10}, // +1
    {20, 10}, // +2
    {25, 10}, // +3
    {30, 10}, // +4
    {35, 10}, // +5
    {40, 10}, // +6, MAX_STAT_STAGE
};

// The classes used by other players in the Union Room.
// These should correspond with the overworld graphics in sUnionRoomObjGfxIds
const u16 gUnionRoomFacilityClasses[NUM_UNION_ROOM_CLASSES * GENDER_COUNT] =
{
    // Male classes
    FACILITY_CLASS_COOLTRAINER_M,
    FACILITY_CLASS_BLACK_BELT,
    FACILITY_CLASS_CAMPER,
    FACILITY_CLASS_YOUNGSTER,
    FACILITY_CLASS_PSYCHIC_M,
    FACILITY_CLASS_BUG_CATCHER,
    FACILITY_CLASS_PKMN_BREEDER_M,
    FACILITY_CLASS_GUITARIST,
    // Female classes
    FACILITY_CLASS_COOLTRAINER_F,
    FACILITY_CLASS_HEX_MANIAC,
    FACILITY_CLASS_PICNICKER,
    FACILITY_CLASS_LASS,
    FACILITY_CLASS_PSYCHIC_F,
    FACILITY_CLASS_BATTLE_GIRL,
    FACILITY_CLASS_PKMN_BREEDER_F,
    FACILITY_CLASS_BEAUTY
};

const struct SpriteTemplate gBattlerSpriteTemplates[MAX_BATTLERS_COUNT] =
{
    [B_POSITION_PLAYER_LEFT] = {
        .tileTag = TAG_NONE,
        .paletteTag = 0,
        .oam = &gOamData_BattleSpritePlayerSide,
        .anims = NULL,
        .images = gBattlerPicTable_PlayerLeft,
        .affineAnims = gAffineAnims_BattleSpritePlayerSide,
        .callback = SpriteCB_BattleSpriteStartSlideLeft,
    },
    [B_POSITION_OPPONENT_LEFT] = {
        .tileTag = TAG_NONE,
        .paletteTag = 0,
        .oam = &gOamData_BattleSpriteOpponentSide,
        .anims = NULL,
        .images = gBattlerPicTable_OpponentLeft,
        .affineAnims = gAffineAnims_BattleSpriteOpponentSide,
        .callback = SpriteCB_WildMon,
    },
    [B_POSITION_PLAYER_RIGHT] = {
        .tileTag = TAG_NONE,
        .paletteTag = 0,
        .oam = &gOamData_BattleSpritePlayerSide,
        .anims = NULL,
        .images = gBattlerPicTable_PlayerRight,
        .affineAnims = gAffineAnims_BattleSpritePlayerSide,
        .callback = SpriteCB_BattleSpriteStartSlideLeft,
    },
    [B_POSITION_OPPONENT_RIGHT] = {
        .tileTag = TAG_NONE,
        .paletteTag = 0,
        .oam = &gOamData_BattleSpriteOpponentSide,
        .anims = NULL,
        .images = gBattlerPicTable_OpponentRight,
        .affineAnims = gAffineAnims_BattleSpriteOpponentSide,
        .callback = SpriteCB_WildMon
    },
};

static const struct SpriteTemplate sTrainerBackSpriteTemplates[] =
{
    [TRAINER_BACK_PIC_BRENDAN] = {
        .tileTag = TAG_NONE,
        .paletteTag = 0,
        .oam = &gOamData_BattleSpritePlayerSide,
        .anims = NULL,
        .images = gTrainerBackPicTable_Brendan,
        .affineAnims = gAffineAnims_BattleSpritePlayerSide,
        .callback = SpriteCB_BattleSpriteStartSlideLeft,
    },
    [TRAINER_BACK_PIC_MAY] = {
        .tileTag = TAG_NONE,
        .paletteTag = 0,
        .oam = &gOamData_BattleSpritePlayerSide,
        .anims = NULL,
        .images = gTrainerBackPicTable_May,
        .affineAnims = gAffineAnims_BattleSpritePlayerSide,
        .callback = SpriteCB_BattleSpriteStartSlideLeft,
    },
    [TRAINER_BACK_PIC_RED] = {
        .tileTag = TAG_NONE,
        .paletteTag = 0,
        .oam = &gOamData_BattleSpritePlayerSide,
        .anims = NULL,
        .images = gTrainerBackPicTable_Red,
        .affineAnims = gAffineAnims_BattleSpritePlayerSide,
        .callback = SpriteCB_BattleSpriteStartSlideLeft,
    },
    [TRAINER_BACK_PIC_LEAF] = {
        .tileTag = TAG_NONE,
        .paletteTag = 0,
        .oam = &gOamData_BattleSpritePlayerSide,
        .anims = NULL,
        .images = gTrainerBackPicTable_Leaf,
        .affineAnims = gAffineAnims_BattleSpritePlayerSide,
        .callback = SpriteCB_BattleSpriteStartSlideLeft,
    },
    [TRAINER_BACK_PIC_RUBY_SAPPHIRE_BRENDAN] = {
        .tileTag = TAG_NONE,
        .paletteTag = 0,
        .oam = &gOamData_BattleSpritePlayerSide,
        .anims = NULL,
        .images = gTrainerBackPicTable_RubySapphireBrendan,
        .affineAnims = gAffineAnims_BattleSpritePlayerSide,
        .callback = SpriteCB_BattleSpriteStartSlideLeft,
    },
    [TRAINER_BACK_PIC_RUBY_SAPPHIRE_MAY] = {
        .tileTag = TAG_NONE,
        .paletteTag = 0,
        .oam = &gOamData_BattleSpritePlayerSide,
        .anims = NULL,
        .images = gTrainerBackPicTable_RubySapphireMay,
        .affineAnims = gAffineAnims_BattleSpritePlayerSide,
        .callback = SpriteCB_BattleSpriteStartSlideLeft,
    },
    [TRAINER_BACK_PIC_WALLY] = {
        .tileTag = TAG_NONE,
        .paletteTag = 0,
        .oam = &gOamData_BattleSpritePlayerSide,
        .anims = NULL,
        .images = gTrainerBackPicTable_Wally,
        .affineAnims = gAffineAnims_BattleSpritePlayerSide,
        .callback = SpriteCB_BattleSpriteStartSlideLeft,
    },
    [TRAINER_BACK_PIC_STEVEN] = {
        .tileTag = TAG_NONE,
        .paletteTag = 0,
        .oam = &gOamData_BattleSpritePlayerSide,
        .anims = NULL,
        .images = gTrainerBackPicTable_Steven,
        .affineAnims = gAffineAnims_BattleSpritePlayerSide,
        .callback = SpriteCB_BattleSpriteStartSlideLeft,
    },
};

#define NUM_SECRET_BASE_CLASSES 5
static const u8 sSecretBaseFacilityClasses[GENDER_COUNT][NUM_SECRET_BASE_CLASSES] =
{
    [MALE] = {
        FACILITY_CLASS_YOUNGSTER,
        FACILITY_CLASS_BUG_CATCHER,
        FACILITY_CLASS_RICH_BOY,
        FACILITY_CLASS_CAMPER,
        FACILITY_CLASS_COOLTRAINER_M
    },
    [FEMALE] = {
        FACILITY_CLASS_LASS,
        FACILITY_CLASS_SCHOOL_KID_F,
        FACILITY_CLASS_LADY,
        FACILITY_CLASS_PICNICKER,
        FACILITY_CLASS_COOLTRAINER_F
    }
};

static const u8 sGetMonDataEVConstants[] =
{
    MON_DATA_HP_EV,
    MON_DATA_ATK_EV,
    MON_DATA_DEF_EV,
    MON_DATA_SPEED_EV,
    MON_DATA_SPDEF_EV,
    MON_DATA_SPATK_EV
};

// For stat-raising items
static const u8 sStatsToRaise[] =
{
    STAT_ATK, STAT_ATK, STAT_DEF, STAT_SPEED, STAT_SPATK, STAT_SPDEF, STAT_ACC
};

// 3 modifiers each for how much to change friendship for different ranges
// 0-99, 100-199, 200+
static const s8 sFriendshipEventModifiers[][3] =
{
    [FRIENDSHIP_EVENT_GROW_LEVEL]      = { 5,  3,  2},
    [FRIENDSHIP_EVENT_VITAMIN]         = { 5,  3,  2},
    [FRIENDSHIP_EVENT_BATTLE_ITEM]     = { 1,  1,  0},
    [FRIENDSHIP_EVENT_LEAGUE_BATTLE]   = { 3,  2,  1},
    [FRIENDSHIP_EVENT_LEARN_TMHM]      = { 1,  1,  0},
    [FRIENDSHIP_EVENT_WALKING]         = { 1,  1,  1},
    [FRIENDSHIP_EVENT_FAINT_SMALL]     = {-1, -1, -1},
    [FRIENDSHIP_EVENT_FAINT_FIELD_PSN] = {-5, -5, -10},
    [FRIENDSHIP_EVENT_FAINT_LARGE]     = {-5, -5, -10},
};

#define HM_MOVES_END 0xFFFF

static const u16 sHMMoves[] =
{
    MOVE_CUT, MOVE_FLY, MOVE_SURF, MOVE_STRENGTH, MOVE_FLASH,
    MOVE_ROCK_SMASH, MOVE_WATERFALL, MOVE_DIVE, HM_MOVES_END
};

static const struct SpeciesItem sAlteringCaveWildMonHeldItems[] =
{
    {SPECIES_NONE,      ITEM_NONE},
    {SPECIES_MAREEP,    ITEM_GANLON_BERRY},
    {SPECIES_PINECO,    ITEM_APICOT_BERRY},
    {SPECIES_HOUNDOUR,  ITEM_BIG_MUSHROOM},
    {SPECIES_TEDDIURSA, ITEM_PETAYA_BERRY},
    {SPECIES_AIPOM,     ITEM_BERRY_JUICE},
    {SPECIES_SHUCKLE,   ITEM_BERRY_JUICE},
    {SPECIES_STANTLER,  ITEM_PETAYA_BERRY},
    {SPECIES_SMEARGLE,  ITEM_SALAC_BERRY},
};

static const struct OamData sOamData_64x64 =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 0,
    .paletteNum = 0,
    .affineParam = 0
};

static const struct SpriteTemplate sSpriteTemplate_64x64 =
{
    .tileTag = TAG_NONE,
    .paletteTag = TAG_NONE,
    .oam = &sOamData_64x64,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

// NOTE: Reordering this array will break compatibility with existing
// saves.
static const u32 sCompressedStatuses[] =
{
    STATUS1_NONE,
    STATUS1_SLEEP_TURN(1),
    STATUS1_SLEEP_TURN(2),
    STATUS1_SLEEP_TURN(3),
    STATUS1_SLEEP_TURN(4),
    STATUS1_SLEEP_TURN(5),
    STATUS1_POISON,
    STATUS1_BURN,
    STATUS1_FREEZE,
    STATUS1_PARALYSIS,
    STATUS1_TOXIC_POISON,
    STATUS1_FROSTBITE,
};

// Attempt to detect situations where the BoxPokemon struct is unable to
// contain all the values.
// TODO: Is it possible to compute:
// - The maximum experience.
// - The maximum PP.
// - The maximum HP.
// - The maximum form countdown.

// The following STATIC_ASSERT will prevent developers from compiling the game if the value of the constant on the left does not fit within the number of bits defined in PokemonSubstruct0 (currently located in include/pokemon.h).

// To successfully compile, developers will need to do one of the following:
// 1) Decrease the size of the constant.
// 2) Increase the number of bits both on the struct AND in the corresponding assert. This will likely break user's saves unless there is free space after the member that is being adjsted.
// 3) Repurpose unused IDs.

// EXAMPLES
// If a developer has added enough new items so that ITEMS_COUNT now equals 1200, they could...
// 1) remove new items until ITEMS_COUNT is 1023, the max value that will fit in 10 bits.
// 2) change heldItem:10 to heldItem:11 AND change the below assert for ITEMS_COUNT to check for (1 << 11).
// 3) repurpose IDs from other items that aren't being used, like ITEM_GOLD_TEETH or ITEM_SS_TICKET until ITEMS_COUNT equals 1023, the max value that will fit in 10 bits.

STATIC_ASSERT(NUM_SPECIES < (1 << 11), PokemonSubstruct0_species_TooSmall);
STATIC_ASSERT(NUMBER_OF_MON_TYPES + 1 <= (1 << 5), PokemonSubstruct0_teraType_TooSmall);
STATIC_ASSERT(ITEMS_COUNT < (1 << 10), PokemonSubstruct0_heldItem_TooSmall);
STATIC_ASSERT(MAX_LEVEL <= 100, PokemonSubstruct0_experience_PotentiallTooSmall); // Maximum of ~2 million exp.
STATIC_ASSERT(POKEBALL_COUNT <= (1 << 6), PokemonSubstruct0_pokeball_TooSmall);
STATIC_ASSERT(MOVES_COUNT_ALL < (1 << 11), PokemonSubstruct1_moves_TooSmall);
STATIC_ASSERT(ARRAY_COUNT(sCompressedStatuses) <= (1 << 4), PokemonSubstruct3_compressedStatus_TooSmall);
STATIC_ASSERT(MAX_LEVEL < (1 << 7), PokemonSubstruct3_metLevel_TooSmall);
STATIC_ASSERT(NUM_VERSIONS < (1 << 4), PokemonSubstruct3_metGame_TooSmall);
STATIC_ASSERT(MAX_DYNAMAX_LEVEL < (1 << 4), PokemonSubstruct3_dynamaxLevel_TooSmall);
STATIC_ASSERT(MAX_PER_STAT_IVS < (1 << 5), PokemonSubstruct3_ivs_TooSmall);
STATIC_ASSERT(NUM_NATURES <= (1 << 5), BoxPokemon_hiddenNatureModifier_TooSmall);

static u32 CompressStatus(u32 status)
{
    s32 i;
    for (i = 0; i < ARRAY_COUNT(sCompressedStatuses); i++)
    {
        if (sCompressedStatuses[i] == status)
            return i;
    }
    return 0; // STATUS1_NONE
}

static u32 UncompressStatus(u32 compressedStatus)
{
    if (compressedStatus < ARRAY_COUNT(sCompressedStatuses))
        return sCompressedStatuses[compressedStatus];
    else
        return STATUS1_NONE;
}

void ZeroBoxMonData(struct BoxPokemon *boxMon)
{
    u8 *raw = (u8 *)boxMon;
    u32 i;
    for (i = 0; i < sizeof(struct BoxPokemon); i++)
        raw[i] = 0;
}

u8 GetMonoType(){
    u8 varValue = VarGet(VAR_MONOTYPE);
    if (varValue == 0 || varValue >= NUMBER_OF_MON_TYPES){
        return TYPE_NONE;
    }else if (varValue >= 10){
        return varValue + 1;
    }else{
        return varValue;
    }
}

void ZeroMonData(struct Pokemon *mon)
{
    u32 arg;
    ZeroBoxMonData(&mon->box);
    arg = 0;
    SetMonData(mon, MON_DATA_STATUS, &arg);
    SetMonData(mon, MON_DATA_LEVEL, &arg);
    SetMonData(mon, MON_DATA_HP, &arg);
    SetMonData(mon, MON_DATA_MAX_HP, &arg);
    SetMonData(mon, MON_DATA_ATK, &arg);
    SetMonData(mon, MON_DATA_DEF, &arg);
    SetMonData(mon, MON_DATA_SPEED, &arg);
    SetMonData(mon, MON_DATA_SPATK, &arg);
    SetMonData(mon, MON_DATA_SPDEF, &arg);
    arg = MAIL_NONE;
    SetMonData(mon, MON_DATA_MAIL, &arg);
}

void ZeroPlayerPartyMons(void)
{
    s32 i;
    for (i = 0; i < PARTY_SIZE; i++)
        ZeroMonData(&gPlayerParty[i]);
}

void ZeroEnemyPartyMons(void)
{
    s32 i;
    for (i = 0; i < PARTY_SIZE; i++)
        ZeroMonData(&gEnemyParty[i]);
}

void CreateMon(struct Pokemon *mon, u16 species, u8 level, u8 fixedIV, u8 hasFixedPersonality, u32 fixedPersonality, u8 otIdType, u32 fixedOtId)
{
    u32 mail;
    ZeroMonData(mon);
    CreateBoxMon(&mon->box, species, level, fixedIV, hasFixedPersonality, fixedPersonality, otIdType, fixedOtId);
    SetMonData(mon, MON_DATA_LEVEL, &level);
    mail = MAIL_NONE;
    SetMonData(mon, MON_DATA_MAIL, &mail);
    CalculateMonStats(mon);
}

void CreateBoxMon(struct BoxPokemon *boxMon, u16 species, u8 level, u8 fixedIV, u8 hasFixedPersonality, u32 fixedPersonality, u8 otIdType, u32 fixedOtId)
{
    u8 speciesName[POKEMON_NAME_LENGTH + 1];
    u32 personality = Random32();
    u32 value;
    u16 checksum;
    u8 i;
    u8 availableIVs[NUM_STATS];
    u8 selectedIvs[NUM_STATS];
    bool32 isShiny;

    ZeroBoxMonData(boxMon);

    // Determine original trainer ID
    if (otIdType == OT_ID_RANDOM_NO_SHINY)
    {
        value = Random32();
        isShiny = FALSE;
    }
    else if (otIdType == OT_ID_PRESET)
    {
        value = fixedOtId;
        isShiny = GET_SHINY_VALUE(value, hasFixedPersonality ? fixedPersonality : personality) < SHINY_ODDS;
    }
    else // Player is the OT
    {
        value = gSaveBlock2Ptr->playerTrainerId[0]
              | (gSaveBlock2Ptr->playerTrainerId[1] << 8)
              | (gSaveBlock2Ptr->playerTrainerId[2] << 16)
              | (gSaveBlock2Ptr->playerTrainerId[3] << 24);

        if (P_FLAG_FORCE_NO_SHINY != 0 && FlagGet(P_FLAG_FORCE_NO_SHINY))
        {
            isShiny = FALSE;
        }
        else if (P_FLAG_FORCE_SHINY != 0 && FlagGet(P_FLAG_FORCE_SHINY))
        {
            isShiny = TRUE;
        }
        else if (P_ONLY_OBTAINABLE_SHINIES && InBattlePyramid())
        {
            isShiny = FALSE;
        }
        else if (P_NO_SHINIES_WITHOUT_POKEBALLS && !HasAtLeastOnePokeBall())
        {
            isShiny = FALSE;
        }
        else
        {
            u32 totalRerolls = 0;
            if (CheckBagHasItem(ITEM_SHINY_CHARM, 1))
                totalRerolls += I_SHINY_CHARM_ADDITIONAL_ROLLS;
            if (LURE_STEP_COUNT != 0)
                totalRerolls += 1;
            if (I_FISHING_CHAIN && gIsFishingEncounter)
                totalRerolls += CalculateChainFishingShinyRolls();
            if (gDexNavSpecies)
                totalRerolls += CalculateDexNavShinyRolls();

            while (GET_SHINY_VALUE(value, personality) >= SHINY_ODDS && totalRerolls > 0)
            {
                personality = Random32();
                totalRerolls--;
            }

            isShiny = GET_SHINY_VALUE(value, personality) < SHINY_ODDS;
        }
    }

    if (hasFixedPersonality)
        personality = fixedPersonality;

    SetBoxMonData(boxMon, MON_DATA_PERSONALITY, &personality);
    SetBoxMonData(boxMon, MON_DATA_OT_ID, &value);

    checksum = CalculateBoxMonChecksum(boxMon);
    SetBoxMonData(boxMon, MON_DATA_CHECKSUM, &checksum);
    EncryptBoxMon(boxMon);
    SetBoxMonData(boxMon, MON_DATA_IS_SHINY, &isShiny);
    StringCopy(speciesName, GetSpeciesName(species));
    SetBoxMonData(boxMon, MON_DATA_NICKNAME, speciesName);
    SetBoxMonData(boxMon, MON_DATA_LANGUAGE, &gGameLanguage);
    SetBoxMonData(boxMon, MON_DATA_OT_NAME, gSaveBlock2Ptr->playerName);
    SetBoxMonData(boxMon, MON_DATA_SPECIES, &species);
    SetBoxMonData(boxMon, MON_DATA_EXP, &gExperienceTables[gSpeciesInfo[species].growthRate][level]);
    SetBoxMonData(boxMon, MON_DATA_FRIENDSHIP, &gSpeciesInfo[species].friendship);
    value = GetCurrentRegionMapSectionId();
    SetBoxMonData(boxMon, MON_DATA_MET_LOCATION, &value);
    SetBoxMonData(boxMon, MON_DATA_MET_LEVEL, &level);
    SetBoxMonData(boxMon, MON_DATA_MET_GAME, &gGameVersion);
    value = ITEM_POKE_BALL;
    SetBoxMonData(boxMon, MON_DATA_POKEBALL, &value);
    SetBoxMonData(boxMon, MON_DATA_OT_GENDER, &gSaveBlock2Ptr->playerGender);

    u32 teraType = (boxMon->personality & 0x1) == 0 ? gSpeciesInfo[species].types[0] : gSpeciesInfo[species].types[1];
    SetBoxMonData(boxMon, MON_DATA_TERA_TYPE, &teraType);

    if (fixedIV < USE_RANDOM_IVS)
    {
        SetBoxMonData(boxMon, MON_DATA_HP_IV, &fixedIV);
        SetBoxMonData(boxMon, MON_DATA_ATK_IV, &fixedIV);
        SetBoxMonData(boxMon, MON_DATA_DEF_IV, &fixedIV);
        SetBoxMonData(boxMon, MON_DATA_SPEED_IV, &fixedIV);
        SetBoxMonData(boxMon, MON_DATA_SPATK_IV, &fixedIV);
        SetBoxMonData(boxMon, MON_DATA_SPDEF_IV, &fixedIV);
    }
    else
    {
        u32 iv;
        u32 ivRandom = Random32();
        value = (u16)ivRandom;

        iv = value & MAX_IV_MASK;
        SetBoxMonData(boxMon, MON_DATA_HP_IV, &iv);
        iv = (value & (MAX_IV_MASK << 5)) >> 5;
        SetBoxMonData(boxMon, MON_DATA_ATK_IV, &iv);
        iv = (value & (MAX_IV_MASK << 10)) >> 10;
        SetBoxMonData(boxMon, MON_DATA_DEF_IV, &iv);

        value = (u16)(ivRandom >> 16);

        iv = value & MAX_IV_MASK;
        SetBoxMonData(boxMon, MON_DATA_SPEED_IV, &iv);
        iv = (value & (MAX_IV_MASK << 5)) >> 5;
        SetBoxMonData(boxMon, MON_DATA_SPATK_IV, &iv);
        iv = (value & (MAX_IV_MASK << 10)) >> 10;
        SetBoxMonData(boxMon, MON_DATA_SPDEF_IV, &iv);

        if (gSpeciesInfo[species].perfectIVCount != 0)
        {
            iv = MAX_PER_STAT_IVS;
            // Initialize a list of IV indices.
            for (i = 0; i < NUM_STATS; i++)
            {
                availableIVs[i] = i;
            }

            // Select the IVs that will be perfected.
            for (i = 0; i < NUM_STATS && i < gSpeciesInfo[species].perfectIVCount; i++)
            {
                u8 index = Random() % (NUM_STATS - i);
                selectedIvs[i] = availableIVs[index];
                RemoveIVIndexFromList(availableIVs, index);
            }
            for (i = 0; i < NUM_STATS && i < gSpeciesInfo[species].perfectIVCount; i++)
            {
                switch (selectedIvs[i])
                {
                case STAT_HP:
                    SetBoxMonData(boxMon, MON_DATA_HP_IV, &iv);
                    break;
                case STAT_ATK:
                    SetBoxMonData(boxMon, MON_DATA_ATK_IV, &iv);
                    break;
                case STAT_DEF:
                    SetBoxMonData(boxMon, MON_DATA_DEF_IV, &iv);
                    break;
                case STAT_SPEED:
                    SetBoxMonData(boxMon, MON_DATA_SPEED_IV, &iv);
                    break;
                case STAT_SPATK:
                    SetBoxMonData(boxMon, MON_DATA_SPATK_IV, &iv);
                    break;
                case STAT_SPDEF:
                    SetBoxMonData(boxMon, MON_DATA_SPDEF_IV, &iv);
                    break;
                }
            }
        }
    }

    if (gSpeciesInfo[species].abilities[1])
    {
        value = personality & 1;
        SetBoxMonData(boxMon, MON_DATA_ABILITY_NUM, &value);
    }

    GiveBoxMonInitialMoveset(boxMon);
}

void CreateMonWithNature(struct Pokemon *mon, u16 species, u8 level, u8 fixedIV, u8 nature)
{
    u32 personality;

    do
    {
        personality = Random32();
    }
    while (nature != GetNatureFromPersonality(personality));

    CreateMon(mon, species, level, fixedIV, TRUE, personality, OT_ID_PLAYER_ID, 0);
}

void CreateMonWithGenderNatureLetter(struct Pokemon *mon, u16 species, u8 level, u8 fixedIV, u8 gender, u8 nature, u8 unownLetter)
{
    u32 personality;

    if ((u8)(unownLetter - 1) < NUM_UNOWN_FORMS)
    {
        u16 actualLetter;

        do
        {
            personality = Random32();
            actualLetter = GET_UNOWN_LETTER(personality);
        }
        while (nature != GetNatureFromPersonality(personality)
            || gender != GetGenderFromSpeciesAndPersonality(species, personality)
            || actualLetter != unownLetter - 1);
    }
    else
    {
        do
        {
            personality = Random32();
        }
        while (nature != GetNatureFromPersonality(personality)
            || gender != GetGenderFromSpeciesAndPersonality(species, personality));
    }

    CreateMon(mon, species, level, fixedIV, TRUE, personality, OT_ID_PLAYER_ID, 0);
}

// This is only used to create Wally's Ralts.
void CreateMaleMon(struct Pokemon *mon, u16 species, u8 level)
{
    u32 personality;
    u32 otId;

    do
    {
        otId = Random32();
        personality = Random32();
    }
    while (GetGenderFromSpeciesAndPersonality(species, personality) != MON_MALE);
    CreateMon(mon, species, level, USE_RANDOM_IVS, TRUE, personality, OT_ID_PRESET, otId);
}

void CreateMonWithIVsPersonality(struct Pokemon *mon, u16 species, u8 level, u32 ivs, u32 personality)
{
    CreateMon(mon, species, level, 0, TRUE, personality, OT_ID_PLAYER_ID, 0);
    SetMonData(mon, MON_DATA_IVS, &ivs);
    CalculateMonStats(mon);
}

void CreateMonWithIVsOTID(struct Pokemon *mon, u16 species, u8 level, u8 *ivs, u32 otId)
{
    CreateMon(mon, species, level, 0, FALSE, 0, OT_ID_PRESET, otId);
    SetMonData(mon, MON_DATA_HP_IV, &ivs[STAT_HP]);
    SetMonData(mon, MON_DATA_ATK_IV, &ivs[STAT_ATK]);
    SetMonData(mon, MON_DATA_DEF_IV, &ivs[STAT_DEF]);
    SetMonData(mon, MON_DATA_SPEED_IV, &ivs[STAT_SPEED]);
    SetMonData(mon, MON_DATA_SPATK_IV, &ivs[STAT_SPATK]);
    SetMonData(mon, MON_DATA_SPDEF_IV, &ivs[STAT_SPDEF]);
    CalculateMonStats(mon);
}

void CreateMonWithEVSpread(struct Pokemon *mon, u16 species, u8 level, u8 fixedIV, u8 evSpread)
{
    s32 i;
    s32 statCount = 0;
    u16 evAmount;
    u8 evsBits;

    CreateMon(mon, species, level, fixedIV, FALSE, 0, OT_ID_PLAYER_ID, 0);

    evsBits = evSpread;

    for (i = 0; i < NUM_STATS; i++)
    {
        if (evsBits & 1)
            statCount++;
        evsBits >>= 1;
    }

    evAmount = MAX_TOTAL_EVS / statCount;

    evsBits = 1;

    for (i = 0; i < NUM_STATS; i++)
    {
        if (evSpread & evsBits)
            SetMonData(mon, MON_DATA_HP_EV + i, &evAmount);
        evsBits <<= 1;
    }

    CalculateMonStats(mon);
}

void CreateBattleTowerMon(struct Pokemon *mon, struct BattleTowerPokemon *src)
{
    s32 i;
    u8 nickname[max(32, POKEMON_NAME_BUFFER_SIZE)];
    u8 language;
    u8 value;

    CreateMon(mon, src->species, src->level, 0, TRUE, src->personality, OT_ID_PRESET, src->otId);

    for (i = 0; i < MAX_MON_MOVES; i++)
        SetMonMoveSlot(mon, src->moves[i], i);

    SetMonData(mon, MON_DATA_PP_BONUSES, &src->ppBonuses);
    SetMonData(mon, MON_DATA_HELD_ITEM, &src->heldItem);
    SetMonData(mon, MON_DATA_FRIENDSHIP, &src->friendship);

    StringCopy(nickname, src->nickname);

    if (nickname[0] == EXT_CTRL_CODE_BEGIN && nickname[1] == EXT_CTRL_CODE_JPN)
    {
        language = LANGUAGE_JAPANESE;
        StripExtCtrlCodes(nickname);
    }
    else
    {
        language = GAME_LANGUAGE;
    }

    SetMonData(mon, MON_DATA_LANGUAGE, &language);
    SetMonData(mon, MON_DATA_NICKNAME, nickname);
    SetMonData(mon, MON_DATA_HP_EV, &src->hpEV);
    SetMonData(mon, MON_DATA_ATK_EV, &src->attackEV);
    SetMonData(mon, MON_DATA_DEF_EV, &src->defenseEV);
    SetMonData(mon, MON_DATA_SPEED_EV, &src->speedEV);
    SetMonData(mon, MON_DATA_SPATK_EV, &src->spAttackEV);
    SetMonData(mon, MON_DATA_SPDEF_EV, &src->spDefenseEV);
    value = src->abilityNum;
    SetMonData(mon, MON_DATA_ABILITY_NUM, &value);
    value = src->hpIV;
    SetMonData(mon, MON_DATA_HP_IV, &value);
    value = src->attackIV;
    SetMonData(mon, MON_DATA_ATK_IV, &value);
    value = src->defenseIV;
    SetMonData(mon, MON_DATA_DEF_IV, &value);
    value = src->speedIV;
    SetMonData(mon, MON_DATA_SPEED_IV, &value);
    value = src->spAttackIV;
    SetMonData(mon, MON_DATA_SPATK_IV, &value);
    value = src->spDefenseIV;
    SetMonData(mon, MON_DATA_SPDEF_IV, &value);
    MonRestorePP(mon);
    CalculateMonStats(mon);
}

void CreateBattleTowerMon_HandleLevel(struct Pokemon *mon, struct BattleTowerPokemon *src, bool8 lvl50)
{
    s32 i;
    u8 nickname[max(32, POKEMON_NAME_BUFFER_SIZE)];
    u8 level;
    u8 language;
    u8 value;

    if (gSaveBlock2Ptr->frontier.lvlMode != FRONTIER_LVL_50)
        level = GetFrontierEnemyMonLevel(gSaveBlock2Ptr->frontier.lvlMode);
    else if (lvl50)
        level = FRONTIER_MAX_LEVEL_50;
    else
        level = src->level;

    CreateMon(mon, src->species, level, 0, TRUE, src->personality, OT_ID_PRESET, src->otId);

    for (i = 0; i < MAX_MON_MOVES; i++)
        SetMonMoveSlot(mon, src->moves[i], i);

    SetMonData(mon, MON_DATA_PP_BONUSES, &src->ppBonuses);
    SetMonData(mon, MON_DATA_HELD_ITEM, &src->heldItem);
    SetMonData(mon, MON_DATA_FRIENDSHIP, &src->friendship);

    StringCopy(nickname, src->nickname);

    if (nickname[0] == EXT_CTRL_CODE_BEGIN && nickname[1] == EXT_CTRL_CODE_JPN)
    {
        language = LANGUAGE_JAPANESE;
        StripExtCtrlCodes(nickname);
    }
    else
    {
        language = GAME_LANGUAGE;
    }

    SetMonData(mon, MON_DATA_LANGUAGE, &language);
    SetMonData(mon, MON_DATA_NICKNAME, nickname);
    SetMonData(mon, MON_DATA_HP_EV, &src->hpEV);
    SetMonData(mon, MON_DATA_ATK_EV, &src->attackEV);
    SetMonData(mon, MON_DATA_DEF_EV, &src->defenseEV);
    SetMonData(mon, MON_DATA_SPEED_EV, &src->speedEV);
    SetMonData(mon, MON_DATA_SPATK_EV, &src->spAttackEV);
    SetMonData(mon, MON_DATA_SPDEF_EV, &src->spDefenseEV);
    value = src->abilityNum;
    SetMonData(mon, MON_DATA_ABILITY_NUM, &value);
    value = src->hpIV;
    SetMonData(mon, MON_DATA_HP_IV, &value);
    value = src->attackIV;
    SetMonData(mon, MON_DATA_ATK_IV, &value);
    value = src->defenseIV;
    SetMonData(mon, MON_DATA_DEF_IV, &value);
    value = src->speedIV;
    SetMonData(mon, MON_DATA_SPEED_IV, &value);
    value = src->spAttackIV;
    SetMonData(mon, MON_DATA_SPATK_IV, &value);
    value = src->spDefenseIV;
    SetMonData(mon, MON_DATA_SPDEF_IV, &value);
    MonRestorePP(mon);
    CalculateMonStats(mon);
}

void CreateApprenticeMon(struct Pokemon *mon, const struct Apprentice *src, u8 monId)
{
    s32 i;
    u16 evAmount;
    u8 language;
    u32 otId = gApprentices[src->id].otId;
    u32 personality = ((gApprentices[src->id].otId >> 8) | ((gApprentices[src->id].otId & 0xFF) << 8))
                    + src->party[monId].species + src->number;

    CreateMon(mon,
              src->party[monId].species,
              GetFrontierEnemyMonLevel(src->lvlMode - 1),
              MAX_PER_STAT_IVS,
              TRUE,
              personality,
              OT_ID_PRESET,
              otId);

    SetMonData(mon, MON_DATA_HELD_ITEM, &src->party[monId].item);
    for (i = 0; i < MAX_MON_MOVES; i++)
        SetMonMoveSlot(mon, src->party[monId].moves[i], i);

    evAmount = MAX_TOTAL_EVS / NUM_STATS;
    for (i = 0; i < NUM_STATS; i++)
        SetMonData(mon, MON_DATA_HP_EV + i, &evAmount);

    language = src->language;
    SetMonData(mon, MON_DATA_LANGUAGE, &language);
    SetMonData(mon, MON_DATA_OT_NAME, GetApprenticeNameInLanguage(src->id, language));
    CalculateMonStats(mon);
}

void CreateMonWithEVSpreadNatureOTID(struct Pokemon *mon, u16 species, u8 level, u8 nature, u8 fixedIV, u8 evSpread, u32 otId)
{
    s32 i;
    s32 statCount = 0;
    u8 evsBits;
    u16 evAmount;

    // i is reused as personality value
    do
    {
        i = Random32();
    } while (nature != GetNatureFromPersonality(i));

    CreateMon(mon, species, level, fixedIV, TRUE, i, OT_ID_PRESET, otId);
    evsBits = evSpread;
    for (i = 0; i < NUM_STATS; i++)
    {
        if (evsBits & 1)
            statCount++;
        evsBits >>= 1;
    }

    evAmount = MAX_TOTAL_EVS / statCount;
    evsBits = 1;
    for (i = 0; i < NUM_STATS; i++)
    {
        if (evSpread & evsBits)
            SetMonData(mon, MON_DATA_HP_EV + i, &evAmount);
        evsBits <<= 1;
    }

    CalculateMonStats(mon);
}

void ConvertPokemonToBattleTowerPokemon(struct Pokemon *mon, struct BattleTowerPokemon *dest)
{
    s32 i;
    u16 heldItem;

    dest->species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    heldItem = GetMonData(mon, MON_DATA_HELD_ITEM, NULL);

    if (heldItem == ITEM_ENIGMA_BERRY_E_READER)
        heldItem = ITEM_NONE;

    dest->heldItem = heldItem;

    for (i = 0; i < MAX_MON_MOVES; i++)
        dest->moves[i] = GetMonData(mon, MON_DATA_MOVE1 + i, NULL);

    dest->level = GetMonData(mon, MON_DATA_LEVEL, NULL);
    dest->ppBonuses = GetMonData(mon, MON_DATA_PP_BONUSES, NULL);
    dest->otId = GetMonData(mon, MON_DATA_OT_ID, NULL);
    dest->hpEV = GetMonData(mon, MON_DATA_HP_EV, NULL);
    dest->attackEV = GetMonData(mon, MON_DATA_ATK_EV, NULL);
    dest->defenseEV = GetMonData(mon, MON_DATA_DEF_EV, NULL);
    dest->speedEV = GetMonData(mon, MON_DATA_SPEED_EV, NULL);
    dest->spAttackEV = GetMonData(mon, MON_DATA_SPATK_EV, NULL);
    dest->spDefenseEV = GetMonData(mon, MON_DATA_SPDEF_EV, NULL);
    dest->friendship = GetMonData(mon, MON_DATA_FRIENDSHIP, NULL);
    dest->hpIV = GetMonData(mon, MON_DATA_HP_IV, NULL);
    dest->attackIV = GetMonData(mon, MON_DATA_ATK_IV, NULL);
    dest->defenseIV = GetMonData(mon, MON_DATA_DEF_IV, NULL);
    dest->speedIV  = GetMonData(mon, MON_DATA_SPEED_IV, NULL);
    dest->spAttackIV  = GetMonData(mon, MON_DATA_SPATK_IV, NULL);
    dest->spDefenseIV  = GetMonData(mon, MON_DATA_SPDEF_IV, NULL);
    dest->abilityNum = GetMonData(mon, MON_DATA_ABILITY_NUM, NULL);
    dest->personality = GetMonData(mon, MON_DATA_PERSONALITY, NULL);
    GetMonData(mon, MON_DATA_NICKNAME10, dest->nickname);
}

static void CreateEventMon(struct Pokemon *mon, u16 species, u8 level, u8 fixedIV, u8 hasFixedPersonality, u32 fixedPersonality, u8 otIdType, u32 fixedOtId)
{
    bool32 isModernFatefulEncounter = TRUE;

    CreateMon(mon, species, level, fixedIV, hasFixedPersonality, fixedPersonality, otIdType, fixedOtId);
    SetMonData(mon, MON_DATA_MODERN_FATEFUL_ENCOUNTER, &isModernFatefulEncounter);
}

// If FALSE, should load this game's Deoxys form. If TRUE, should load normal Deoxys form
bool8 ShouldIgnoreDeoxysForm(u8 caseId, u8 battler)
{
    switch (caseId)
    {
    case 0:
    default:
        return FALSE;
    case 1: // Player's side in battle
        if (!(gBattleTypeFlags & BATTLE_TYPE_MULTI))
            return FALSE;
        if (!gMain.inBattle)
            return FALSE;
        if (gLinkPlayers[GetMultiplayerId()].id == battler)
            return FALSE;
        break;
    case 2:
        break;
    case 3: // Summary Screen
        if (!(gBattleTypeFlags & BATTLE_TYPE_MULTI))
            return FALSE;
        if (!gMain.inBattle)
            return FALSE;
        if (battler == 1 || battler == 4 || battler == 5)
            return TRUE;
        return FALSE;
    case 4:
        break;
    case 5: // In move animation, e.g. in Role Play or Snatch
        if (gBattleTypeFlags & BATTLE_TYPE_LINK)
        {
            if (!gMain.inBattle)
                return FALSE;
            if (gBattleTypeFlags & BATTLE_TYPE_MULTI)
            {
                if (gLinkPlayers[GetMultiplayerId()].id == battler)
                    return FALSE;
            }
            else
            {
                if (IsOnPlayerSide(battler))
                    return FALSE;
            }
        }
        else
        {
            if (!gMain.inBattle)
                return FALSE;
            if (IsOnPlayerSide(battler))
                return FALSE;
        }
        break;
    }

    return TRUE;
}

u16 GetUnionRoomTrainerPic(void)
{
    u8 linkId;
    u32 arrId;

    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
        linkId = gRecordedBattleMultiplayerId ^ 1;
    else
        linkId = GetMultiplayerId() ^ 1;

    arrId = gLinkPlayers[linkId].trainerId % NUM_UNION_ROOM_CLASSES;
    arrId |= gLinkPlayers[linkId].gender * NUM_UNION_ROOM_CLASSES;
    return FacilityClassToPicIndex(gUnionRoomFacilityClasses[arrId]);
}

u16 GetUnionRoomTrainerClass(void)
{
    u8 linkId;
    u32 arrId;

    if (gBattleTypeFlags & BATTLE_TYPE_RECORDED_LINK)
        linkId = gRecordedBattleMultiplayerId ^ 1;
    else
        linkId = GetMultiplayerId() ^ 1;

    arrId = gLinkPlayers[linkId].trainerId % NUM_UNION_ROOM_CLASSES;
    arrId |= gLinkPlayers[linkId].gender * NUM_UNION_ROOM_CLASSES;
    return gFacilityClassToTrainerClass[gUnionRoomFacilityClasses[arrId]];
}

void CreateEnemyEventMon(void)
{
    s32 species = gSpecialVar_0x8004;
    s32 level = gSpecialVar_0x8005;
    s32 itemId = gSpecialVar_0x8006;

    ZeroEnemyPartyMons();
    CreateEventMon(&gEnemyParty[0], species, level, USE_RANDOM_IVS, FALSE, 0, OT_ID_PLAYER_ID, 0);
    if (itemId)
    {
        u8 heldItem[2];
        heldItem[0] = itemId;
        heldItem[1] = itemId >> 8;
        SetMonData(&gEnemyParty[0], MON_DATA_HELD_ITEM, heldItem);
    }
}

static u16 CalculateBoxMonChecksum(struct BoxPokemon *boxMon)
{
    u16 checksum = 0;
    union PokemonSubstruct *substruct0 = GetSubstruct(boxMon, boxMon->personality, 0);
    union PokemonSubstruct *substruct1 = GetSubstruct(boxMon, boxMon->personality, 1);
    union PokemonSubstruct *substruct2 = GetSubstruct(boxMon, boxMon->personality, 2);
    union PokemonSubstruct *substruct3 = GetSubstruct(boxMon, boxMon->personality, 3);
    s32 i;

    for (i = 0; i < (s32)ARRAY_COUNT(substruct0->raw); i++)
        checksum += substruct0->raw[i];

    for (i = 0; i < (s32)ARRAY_COUNT(substruct1->raw); i++)
        checksum += substruct1->raw[i];

    for (i = 0; i < (s32)ARRAY_COUNT(substruct2->raw); i++)
        checksum += substruct2->raw[i];

    for (i = 0; i < (s32)ARRAY_COUNT(substruct3->raw); i++)
        checksum += substruct3->raw[i];

    return checksum;
}

#define CALC_STAT(base, iv, ev, statIndex, field)               \
{                                                               \
    u8 baseStat = gSpeciesInfo[species].base;                   \
    s32 n = (((2 * baseStat + iv + ev / 4) * level) / 100) + 5; \
    n = ModifyStatByNature(nature, n, statIndex);               \
    if (B_FRIENDSHIP_BOOST == TRUE)                             \
        n = n + ((n * 10 * friendship) / (MAX_FRIENDSHIP * 100));\
    SetMonData(mon, field, &n);                                 \
}

void CalculateMonStats(struct Pokemon *mon)
{
    s32 oldMaxHP = GetMonData(mon, MON_DATA_MAX_HP, NULL);
    s32 currentHP = GetMonData(mon, MON_DATA_HP, NULL);
    s32 hpIV = GetMonData(mon, MON_DATA_HYPER_TRAINED_HP) ? MAX_PER_STAT_IVS : GetMonData(mon, MON_DATA_HP_IV, NULL);
    s32 hpEV = GetMonData(mon, MON_DATA_HP_EV, NULL);
    s32 attackIV = GetMonData(mon, MON_DATA_HYPER_TRAINED_ATK) ? MAX_PER_STAT_IVS : GetMonData(mon, MON_DATA_ATK_IV, NULL);
    s32 attackEV = GetMonData(mon, MON_DATA_ATK_EV, NULL);
    s32 defenseIV = GetMonData(mon, MON_DATA_HYPER_TRAINED_DEF) ? MAX_PER_STAT_IVS : GetMonData(mon, MON_DATA_DEF_IV, NULL);
    s32 defenseEV = GetMonData(mon, MON_DATA_DEF_EV, NULL);
    s32 speedIV = GetMonData(mon, MON_DATA_HYPER_TRAINED_SPEED) ? MAX_PER_STAT_IVS : GetMonData(mon, MON_DATA_SPEED_IV, NULL);
    s32 speedEV = GetMonData(mon, MON_DATA_SPEED_EV, NULL);
    s32 spAttackIV = GetMonData(mon, MON_DATA_HYPER_TRAINED_SPATK) ? MAX_PER_STAT_IVS : GetMonData(mon, MON_DATA_SPATK_IV, NULL);
    s32 spAttackEV = GetMonData(mon, MON_DATA_SPATK_EV, NULL);
    s32 spDefenseIV = GetMonData(mon, MON_DATA_HYPER_TRAINED_SPDEF) ? MAX_PER_STAT_IVS : GetMonData(mon, MON_DATA_SPDEF_IV, NULL);
    s32 spDefenseEV = GetMonData(mon, MON_DATA_SPDEF_EV, NULL);
    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    u8 friendship = GetMonData(mon, MON_DATA_FRIENDSHIP, NULL);
    s32 level = GetLevelFromMonExp(mon);
    s32 newMaxHP;

    u8 nature = GetMonData(mon, MON_DATA_HIDDEN_NATURE, NULL);

    SetMonData(mon, MON_DATA_LEVEL, &level);

    if (species == SPECIES_SHEDINJA)
    {
        newMaxHP = 1;
    }
    else
    {
        s32 n = 2 * gSpeciesInfo[species].baseHP + hpIV;
        newMaxHP = (((n + hpEV / 4) * level) / 100) + level + 10;
    }

    gBattleScripting.levelUpHP = newMaxHP - oldMaxHP;
    if (gBattleScripting.levelUpHP == 0)
        gBattleScripting.levelUpHP = 1;

    SetMonData(mon, MON_DATA_MAX_HP, &newMaxHP);

    CALC_STAT(baseAttack, attackIV, attackEV, STAT_ATK, MON_DATA_ATK)
    CALC_STAT(baseDefense, defenseIV, defenseEV, STAT_DEF, MON_DATA_DEF)
    CALC_STAT(baseSpeed, speedIV, speedEV, STAT_SPEED, MON_DATA_SPEED)
    CALC_STAT(baseSpAttack, spAttackIV, spAttackEV, STAT_SPATK, MON_DATA_SPATK)
    CALC_STAT(baseSpDefense, spDefenseIV, spDefenseEV, STAT_SPDEF, MON_DATA_SPDEF)

    // Since a pokemon's maxHP data could either not have
    // been initialized at this point or this pokemon is
    // just fainted, the check for oldMaxHP is important.
    if (currentHP == 0 && oldMaxHP != 0)
        return;

    // Only add to currentHP if newMaxHP went up.
    if (newMaxHP > oldMaxHP)
        currentHP += newMaxHP - oldMaxHP;

    // Ensure currentHP does not surpass newMaxHP.
    if (currentHP > newMaxHP)
        currentHP = newMaxHP;

    SetMonData(mon, MON_DATA_HP, &currentHP);
}

void BoxMonToMon(const struct BoxPokemon *src, struct Pokemon *dest)
{
    u32 value = 0;
    dest->box = *src;
    dest->status = GetBoxMonData(&dest->box, MON_DATA_STATUS, NULL);
    dest->hp = 0;
    dest->maxHP = 0;
    value = MAIL_NONE;
    SetMonData(dest, MON_DATA_MAIL, &value);
    value = GetBoxMonData(&dest->box, MON_DATA_HP_LOST);
    CalculateMonStats(dest);
    value = GetMonData(dest, MON_DATA_MAX_HP) - value;
    SetMonData(dest, MON_DATA_HP, &value);
}

u8 GetLevelFromMonExp(struct Pokemon *mon)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    u32 exp = GetMonData(mon, MON_DATA_EXP, NULL);
    s32 level = 1;

    while (level <= MAX_LEVEL && gExperienceTables[gSpeciesInfo[species].growthRate][level] <= exp)
        level++;

    return level - 1;
}

u8 GetLevelFromBoxMonExp(struct BoxPokemon *boxMon)
{
    u16 species = GetBoxMonData(boxMon, MON_DATA_SPECIES, NULL);
    u32 exp = GetBoxMonData(boxMon, MON_DATA_EXP, NULL);
    s32 level = 1;

    while (level <= MAX_LEVEL && gExperienceTables[gSpeciesInfo[species].growthRate][level] <= exp)
        level++;

    return level - 1;
}

u16 GiveMoveToMon(struct Pokemon *mon, u16 move)
{
    return GiveMoveToBoxMon(&mon->box, move);
}

u16 GiveMoveToBoxMon(struct BoxPokemon *boxMon, u16 move)
{
    s32 i;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        u16 existingMove = GetBoxMonData(boxMon, MON_DATA_MOVE1 + i, NULL);
        if (existingMove == MOVE_NONE)
        {
            u32 pp = GetMovePP(move);
            SetBoxMonData(boxMon, MON_DATA_MOVE1 + i, &move);
            SetBoxMonData(boxMon, MON_DATA_PP1 + i, &pp);
            return move;
        }
        if (existingMove == move)
            return MON_ALREADY_KNOWS_MOVE;
    }
    return MON_HAS_MAX_MOVES;
}

u16 GiveMoveToBattleMon(struct BattlePokemon *mon, u16 move)
{
    s32 i;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (mon->moves[i] == MOVE_NONE)
        {
            mon->moves[i] = move;
            mon->pp[i] = GetMovePP(move);
            return move;
        }
    }

    return MON_HAS_MAX_MOVES;
}

void SetMonMoveSlot(struct Pokemon *mon, u16 move, u8 slot)
{
    SetMonData(mon, MON_DATA_MOVE1 + slot, &move);
    u32 pp = GetMovePP(move);
    SetMonData(mon, MON_DATA_PP1 + slot, &pp);
}

static void SetMonMoveSlot_KeepPP(struct Pokemon *mon, u16 move, u8 slot)
{
    u8 ppBonuses = GetMonData(mon, MON_DATA_PP_BONUSES, NULL);
    u8 currPP = GetMonData(mon, MON_DATA_PP1 + slot, NULL);
    u8 newPP = CalculatePPWithBonus(move, ppBonuses, slot);
    u16 finalPP = min(currPP, newPP);

    SetMonData(mon, MON_DATA_MOVE1 + slot, &move);
    SetMonData(mon, MON_DATA_PP1 + slot, &finalPP);
}

void SetBattleMonMoveSlot(struct BattlePokemon *mon, u16 move, u8 slot)
{
    mon->moves[slot] = move;
    mon->pp[slot] = GetMovePP(move);
}

void GiveMonInitialMoveset(struct Pokemon *mon)
{
    GiveBoxMonInitialMoveset(&mon->box);
}

void GiveBoxMonInitialMoveset(struct BoxPokemon *boxMon) //Credit: AsparagusEduardo
{
    u16 species = GetBoxMonData(boxMon, MON_DATA_SPECIES, NULL);
    s32 level = GetLevelFromBoxMonExp(boxMon);
    s32 i;
    u16 moves[MAX_MON_MOVES] = {MOVE_NONE};
    u8 addedMoves = 0;
    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(species);

    for (i = 0; learnset[i].move != LEVEL_UP_MOVE_END; i++)
    {
        s32 j;
        bool32 alreadyKnown = FALSE;

        if (learnset[i].level > level)
            break;
        if (learnset[i].level == 0)
            continue;

        for (j = 0; j < addedMoves; j++)
        {
            if (moves[j] == learnset[i].move)
            {
                alreadyKnown = TRUE;
                break;
            }
        }

        if (!alreadyKnown)
        {
            if (addedMoves < MAX_MON_MOVES)
            {
                moves[addedMoves] = learnset[i].move;
                addedMoves++;
            }
            else
            {
                for (j = 0; j < MAX_MON_MOVES - 1; j++)
                    moves[j] = moves[j + 1];
                moves[MAX_MON_MOVES - 1] = learnset[i].move;
            }
        }
    }
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        SetBoxMonData(boxMon, MON_DATA_MOVE1 + i, &moves[i]);
        u32 pp = GetMovePP(moves[i]);
        SetBoxMonData(boxMon, MON_DATA_PP1 + i, &pp);
    }
}

u16 MonTryLearningNewMoveAtLevel(struct Pokemon *mon, bool32 firstMove, u32 level)
{
    u32 retVal = MOVE_NONE;
    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(species);

    // since you can learn more than one move per level
    // the game needs to know whether you decided to
    // learn it or keep the old set to avoid asking
    // you to learn the same move over and over again
    if (firstMove)
    {
        sLearningMoveTableID = 0;

        while (learnset[sLearningMoveTableID].level != level)
        {
            sLearningMoveTableID++;
            if (learnset[sLearningMoveTableID].move == LEVEL_UP_MOVE_END)
                return MOVE_NONE;
        }
    }

    //  Handler for Pokémon whose moves change upon form change.
    //  For example, if Zacian or Zamazenta should learn Iron Head,
    //  they're prevented from doing if they have Behemoth Blade/Bash,
    //  since it transforms into them while in their Crowned forms.
    const struct FormChange *formChanges = GetSpeciesFormChanges(species);

    for (u32 i = 0; formChanges != NULL && formChanges[i].method != FORM_CHANGE_TERMINATOR; i++)
    {
        if (formChanges[i].method == FORM_CHANGE_END_BATTLE
            && learnset[sLearningMoveTableID].move == formChanges[i].param3)
        {
            for (u32 j = 0; j < MAX_MON_MOVES; j++)
            {
                if (formChanges[i].param2 == GetMonData(mon, MON_DATA_MOVE1 + j))
                    return MOVE_NONE;
            }
        }
    }

    if (learnset[sLearningMoveTableID].level == level)
    {
        gMoveToLearn = learnset[sLearningMoveTableID].move;
        sLearningMoveTableID++;
        retVal = GiveMoveToMon(mon, gMoveToLearn);
    }

    return retVal;
}

u16 MonTryLearningNewMove(struct Pokemon *mon, bool8 firstMove)
{
    return MonTryLearningNewMoveAtLevel(mon, firstMove, GetMonData(mon, MON_DATA_LEVEL, NULL));
}

void DeleteFirstMoveAndGiveMoveToMon(struct Pokemon *mon, u16 move)
{
    s32 i;
    u16 moves[MAX_MON_MOVES];
    u8 pp[MAX_MON_MOVES];
    u8 ppBonuses;

    for (i = 0; i < MAX_MON_MOVES - 1; i++)
    {
        moves[i] = GetMonData(mon, MON_DATA_MOVE2 + i, NULL);
        pp[i] = GetMonData(mon, MON_DATA_PP2 + i, NULL);
    }

    ppBonuses = GetMonData(mon, MON_DATA_PP_BONUSES, NULL);
    ppBonuses >>= 2;
    moves[MAX_MON_MOVES - 1] = move;
    pp[MAX_MON_MOVES - 1] = GetMovePP(move);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        SetMonData(mon, MON_DATA_MOVE1 + i, &moves[i]);
        SetMonData(mon, MON_DATA_PP1 + i, &pp[i]);
    }

    SetMonData(mon, MON_DATA_PP_BONUSES, &ppBonuses);
}

void DeleteFirstMoveAndGiveMoveToBoxMon(struct BoxPokemon *boxMon, u16 move)
{
    s32 i;
    u16 moves[MAX_MON_MOVES];
    u8 pp[MAX_MON_MOVES];
    u8 ppBonuses;

    for (i = 0; i < MAX_MON_MOVES - 1; i++)
    {
        moves[i] = GetBoxMonData(boxMon, MON_DATA_MOVE2 + i, NULL);
        pp[i] = GetBoxMonData(boxMon, MON_DATA_PP2 + i, NULL);
    }

    ppBonuses = GetBoxMonData(boxMon, MON_DATA_PP_BONUSES, NULL);
    ppBonuses >>= 2;
    moves[MAX_MON_MOVES - 1] = move;
    pp[MAX_MON_MOVES - 1] = GetMovePP(move);

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        SetBoxMonData(boxMon, MON_DATA_MOVE1 + i, &moves[i]);
        SetBoxMonData(boxMon, MON_DATA_PP1 + i, &pp[i]);
    }

    SetBoxMonData(boxMon, MON_DATA_PP_BONUSES, &ppBonuses);
}

u8 CountAliveMonsInBattle(u8 caseId, u32 battler)
{
    u32 i;
    u32 retVal = 0;

    switch (caseId)
    {
    case BATTLE_ALIVE_EXCEPT_BATTLER:
        for (i = 0; i < gBattlersCount; i++)
        {
            if (i != battler && !(gAbsentBattlerFlags & (1u << i)))
                retVal++;
        }
        break;
    case BATTLE_ALIVE_EXCEPT_BATTLER_SIDE:
        for (i = 0; i < gBattlersCount; i++)
        {
            if (i != battler && i != BATTLE_PARTNER(battler) && !(gAbsentBattlerFlags & (1u << i)))
                retVal++;
        }
        break;
    case BATTLE_ALIVE_SIDE:
        for (i = 0; i < gBattlersCount; i++)
        {
            if (IsBattlerAlly(i, battler) && !(gAbsentBattlerFlags & (1u << i)))
                retVal++;
        }
        break;
    }

    return retVal;
}

u8 GetDefaultMoveTarget(u8 battlerId)
{
    u8 opposing = BATTLE_OPPOSITE(GetBattlerSide(battlerId));

    if (!IsDoubleBattle())
        return GetBattlerAtPosition(opposing);
    if (CountAliveMonsInBattle(BATTLE_ALIVE_EXCEPT_BATTLER, battlerId) > 1)
    {
        u8 position;

        if ((Random() & 1) == 0)
            position = BATTLE_PARTNER(opposing);
        else
            position = opposing;

        return GetBattlerAtPosition(position);
    }
    else
    {
        if ((gAbsentBattlerFlags & (1u << opposing)))
            return GetBattlerAtPosition(BATTLE_PARTNER(opposing));
        else
            return GetBattlerAtPosition(opposing);
    }
}

u8 GetMonGender(struct Pokemon *mon)
{
    return GetBoxMonGender(&mon->box);
}

u8 GetBoxMonGender(struct BoxPokemon *boxMon)
{
    u16 species = GetBoxMonData(boxMon, MON_DATA_SPECIES, NULL);
    u32 personality = GetBoxMonData(boxMon, MON_DATA_PERSONALITY, NULL);

    switch (gSpeciesInfo[species].genderRatio)
    {
    case MON_MALE:
    case MON_FEMALE:
    case MON_GENDERLESS:
        return gSpeciesInfo[species].genderRatio;
    }

    if (gSpeciesInfo[species].genderRatio > (personality & 0xFF))
        return MON_FEMALE;
    else
        return MON_MALE;
}

u8 GetGenderFromSpeciesAndPersonality(u16 species, u32 personality)
{
    switch (gSpeciesInfo[species].genderRatio)
    {
    case MON_MALE:
    case MON_FEMALE:
    case MON_GENDERLESS:
        return gSpeciesInfo[species].genderRatio;
    }

    if (gSpeciesInfo[species].genderRatio > (personality & 0xFF))
        return MON_FEMALE;
    else
        return MON_MALE;
}

bool32 IsPersonalityFemale(u16 species, u32 personality)
{
    return GetGenderFromSpeciesAndPersonality(species, personality) == MON_FEMALE;
}

u32 GetUnownSpeciesId(u32 personality)
{
    u16 unownLetter = GetUnownLetterByPersonality(personality);

    if (unownLetter == 0)
        return SPECIES_UNOWN;
    return unownLetter + SPECIES_UNOWN_B - 1;
}

void SetMultiuseSpriteTemplateToPokemon(u16 speciesTag, u8 battlerPosition)
{
    if (gMonSpritesGfxPtr != NULL)
        gMultiuseSpriteTemplate = gMonSpritesGfxPtr->templates[battlerPosition];
    else if (sMonSpritesGfxManagers[MON_SPR_GFX_MANAGER_A])
        gMultiuseSpriteTemplate = sMonSpritesGfxManagers[MON_SPR_GFX_MANAGER_A]->templates[battlerPosition];
    else if (sMonSpritesGfxManagers[MON_SPR_GFX_MANAGER_B])
        gMultiuseSpriteTemplate = sMonSpritesGfxManagers[MON_SPR_GFX_MANAGER_B]->templates[battlerPosition];
    else
        gMultiuseSpriteTemplate = gBattlerSpriteTemplates[battlerPosition];

    gMultiuseSpriteTemplate.paletteTag = speciesTag;
    if (battlerPosition == B_POSITION_PLAYER_LEFT || battlerPosition == B_POSITION_PLAYER_RIGHT)
        gMultiuseSpriteTemplate.anims = gAnims_MonPic;
    else
    {
        if (speciesTag > SPECIES_SHINY_TAG)
            speciesTag = speciesTag - SPECIES_SHINY_TAG;

        speciesTag = SanitizeSpeciesId(speciesTag);
        if (gSpeciesInfo[speciesTag].frontAnimFrames != NULL)
            gMultiuseSpriteTemplate.anims = gSpeciesInfo[speciesTag].frontAnimFrames;
        else
            gMultiuseSpriteTemplate.anims = gSpeciesInfo[SPECIES_NONE].frontAnimFrames;
    }
}

void SetMultiuseSpriteTemplateToTrainerBack(u16 trainerPicId, u8 battlerPosition)
{
    gMultiuseSpriteTemplate.paletteTag = trainerPicId;
    if (battlerPosition == B_POSITION_PLAYER_LEFT || battlerPosition == B_POSITION_PLAYER_RIGHT)
    {
        gMultiuseSpriteTemplate = sTrainerBackSpriteTemplates[trainerPicId];
        gMultiuseSpriteTemplate.anims = gTrainerBacksprites[trainerPicId].animation;
    }
    else
    {
        if (gMonSpritesGfxPtr != NULL)
            gMultiuseSpriteTemplate = gMonSpritesGfxPtr->templates[battlerPosition];
        else
            gMultiuseSpriteTemplate = gBattlerSpriteTemplates[battlerPosition];
        gMultiuseSpriteTemplate.anims = gAnims_Trainer;
    }
}

void SetMultiuseSpriteTemplateToTrainerFront(u16 trainerPicId, u8 battlerPosition)
{
    if (gMonSpritesGfxPtr != NULL)
        gMultiuseSpriteTemplate = gMonSpritesGfxPtr->templates[battlerPosition];
    else
        gMultiuseSpriteTemplate = gBattlerSpriteTemplates[battlerPosition];

    gMultiuseSpriteTemplate.paletteTag = trainerPicId;
    gMultiuseSpriteTemplate.anims = gAnims_Trainer;
}

static void EncryptBoxMon(struct BoxPokemon *boxMon)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(boxMon->secure.raw); i++)
    {
        boxMon->secure.raw[i] ^= boxMon->personality;
        boxMon->secure.raw[i] ^= boxMon->otId;
    }
}

static void DecryptBoxMon(struct BoxPokemon *boxMon)
{
    u32 i;
    for (i = 0; i < ARRAY_COUNT(boxMon->secure.raw); i++)
    {
        boxMon->secure.raw[i] ^= boxMon->otId;
        boxMon->secure.raw[i] ^= boxMon->personality;
    }
}

#define SUBSTRUCT_CASE(n, v1, v2, v3, v4)                               \
case n:                                                                 \
    {                                                                   \
                                                                        \
        switch (substructType)                                          \
        {                                                               \
        case 0:                                                         \
            substruct = &boxMon->secure.substructs[v1];                          \
            break;                                                      \
        case 1:                                                         \
            substruct = &boxMon->secure.substructs[v2];                          \
            break;                                                      \
        case 2:                                                         \
            substruct = &boxMon->secure.substructs[v3];                          \
            break;                                                      \
        case 3:                                                         \
            substruct = &boxMon->secure.substructs[v4];                          \
            break;                                                      \
        }                                                               \
        break;                                                          \
    }                                                                   \


static union PokemonSubstruct *GetSubstruct(struct BoxPokemon *boxMon, u32 personality, u8 substructType)
{
    union PokemonSubstruct *substruct = NULL;

    switch (personality % 24)
    {
        SUBSTRUCT_CASE( 0,0,1,2,3)
        SUBSTRUCT_CASE( 1,0,1,3,2)
        SUBSTRUCT_CASE( 2,0,2,1,3)
        SUBSTRUCT_CASE( 3,0,3,1,2)
        SUBSTRUCT_CASE( 4,0,2,3,1)
        SUBSTRUCT_CASE( 5,0,3,2,1)
        SUBSTRUCT_CASE( 6,1,0,2,3)
        SUBSTRUCT_CASE( 7,1,0,3,2)
        SUBSTRUCT_CASE( 8,2,0,1,3)
        SUBSTRUCT_CASE( 9,3,0,1,2)
        SUBSTRUCT_CASE(10,2,0,3,1)
        SUBSTRUCT_CASE(11,3,0,2,1)
        SUBSTRUCT_CASE(12,1,2,0,3)
        SUBSTRUCT_CASE(13,1,3,0,2)
        SUBSTRUCT_CASE(14,2,1,0,3)
        SUBSTRUCT_CASE(15,3,1,0,2)
        SUBSTRUCT_CASE(16,2,3,0,1)
        SUBSTRUCT_CASE(17,3,2,0,1)
        SUBSTRUCT_CASE(18,1,2,3,0)
        SUBSTRUCT_CASE(19,1,3,2,0)
        SUBSTRUCT_CASE(20,2,1,3,0)
        SUBSTRUCT_CASE(21,3,1,2,0)
        SUBSTRUCT_CASE(22,2,3,1,0)
        SUBSTRUCT_CASE(23,3,2,1,0)
    }

    return substruct;
}

/* GameFreak called GetMonData with either 2 or 3 arguments, for type
 * safety we have a GetMonData macro (in include/pokemon.h) which
 * dispatches to either GetMonData2 or GetMonData3 based on the number
 * of arguments. */
u32 GetMonData3(struct Pokemon *mon, s32 field, u8 *data)
{
    u32 ret;

    switch (field)
    {
    case MON_DATA_STATUS:
        ret = mon->status;
        break;
    case MON_DATA_LEVEL:
        ret = mon->level;
        break;
    case MON_DATA_HP:
        ret = mon->hp;
        break;
    case MON_DATA_MAX_HP:
        ret = mon->maxHP;
        break;
    case MON_DATA_ATK:
        ret = mon->attack;
        break;
    case MON_DATA_DEF:
        ret = mon->defense;
        break;
    case MON_DATA_SPEED:
        ret = mon->speed;
        break;
    case MON_DATA_SPATK:
        ret = mon->spAttack;
        break;
    case MON_DATA_SPDEF:
        ret = mon->spDefense;
        break;
    case MON_DATA_ATK2:
        ret = mon->attack;
        break;
    case MON_DATA_DEF2:
        ret = mon->defense;
        break;
    case MON_DATA_SPEED2:
        ret = mon->speed;
        break;
    case MON_DATA_SPATK2:
        ret = mon->spAttack;
        break;
    case MON_DATA_SPDEF2:
        ret = mon->spDefense;
        break;
    case MON_DATA_MAIL:
        ret = mon->mail;
        break;
    default:
        ret = GetBoxMonData(&mon->box, field, data);
        break;
    }
    return ret;
}

u32 GetMonData2(struct Pokemon *mon, s32 field)
{
    return GetMonData3(mon, field, NULL);
}

struct EvolutionTrackerBitfield
{
    u16 a: 5;
    u16 b: 5;
    u16 unused: 6;
};

union EvolutionTracker
{
    u16 value;
    struct EvolutionTrackerBitfield asField;
};


static u32 getCuratedOrRandomTeraType(u16 species, u32 personality){

    u32 monotype = GetMonoType();
    //Get a value of 0 to TYPE_FAIRY - 1; add 1 since 0 is TYPE_NONE, to get values between TYPE_NORMAL and TYPE_FAIRY
    u32 randomTeraType = (personality % TYPE_FAIRY) + 1;

    //Easiest way to deal with TYPE_MYSTERY is to just replace it with Stellar
    if (randomTeraType == TYPE_MYSTERY){
        randomTeraType = TYPE_STELLAR;
    }
    
    if (!FlagGet(FLAG_CURATED_TERA)){
        return randomTeraType;
    }

    //In monotype mode, bypass curated tera considerations if the random type is Monotype compatible
    //Note that because of a different check in `CanTerastallize`, this will only apply to Pokemon that don't exceed the Tier Points cap
    if (monotype != TYPE_NONE){
        if (randomTeraType == TYPE_STELLAR || randomTeraType == monotype){
            return randomTeraType;
        }
    }
/*
List of Tera Types: Normal Fire Water Electric Grass Ice Fighting Poison Ground Flying Psychic Bug Rock Ghost Dragon Dark Steel Fairy Stellar
*/


    //Standardize species for certain forms
    if (species >= SPECIES_ALCREMIE_STRAWBERRY_RUBY_CREAM && species <= SPECIES_ALCREMIE_STRAWBERRY_RAINBOW_SWIRL){
        species = SPECIES_ALCREMIE;
    }
    if (species >= SPECIES_ALCREMIE_BERRY_VANILLA_CREAM && species <= SPECIES_ALCREMIE_RIBBON_RAINBOW_SWIRL){
        species = SPECIES_ALCREMIE;
    }
    if (species >= SPECIES_MINIOR_ORANGE && species <= SPECIES_MINIOR_CORE_VIOLET){
        species = SPECIES_MINIOR;
    }
    if (species >= SPECIES_SILVALLY_FIGHTING && species <= SPECIES_SILVALLY_FAIRY){
        species = SPECIES_SILVALLY;
    }

    switch(species){
        //Pure Water Tera Types
        /*Not given a Tera Type because of points: Vaporeon, Suicune, Milotic, Floatzel, Manaphy, Greninja, Inteleon, Dondozo, Palafin
        */  

        case SPECIES_SQUIRTLE: case SPECIES_WARTORTLE: case SPECIES_BLASTOISE:
            return TYPE_DARK; //Dark Pulse; Steel might be a little too good
        case SPECIES_PSYDUCK:
            return TYPE_PSYCHIC;
        case SPECIES_GOLDUCK:
            return TYPE_GHOST;
        case SPECIES_POLIWAG: case SPECIES_POLIWHIRL:
            return TYPE_NORMAL;
        case SPECIES_POLITOED: 
            return TYPE_FAIRY;
        case SPECIES_SHELLDER:
            return TYPE_ICE;
        case SPECIES_KRABBY: case SPECIES_KINGLER:
            return TYPE_ROCK;
        case SPECIES_GOLDEEN: case SPECIES_SEAKING:
            return TYPE_FLYING;
        case SPECIES_STARYU:
            return TYPE_NORMAL;
        case SPECIES_MAGIKARP:
            return TYPE_DRAGON;
        case SPECIES_TOTODILE: case SPECIES_CROCONAW: case SPECIES_FERALIGATR:
            return TYPE_PSYCHIC; //Psychic Fangs
        case SPECIES_REMORAID: case SPECIES_OCTILLERY:
            return TYPE_NORMAL; //Wring Out
        case SPECIES_WAILMER: case SPECIES_WAILORD:
            return TYPE_GRASS;
        case SPECIES_CASTFORM_RAINY:
            return TYPE_STELLAR;
        case SPECIES_FEEBAS: 
            return TYPE_ELECTRIC;
        case SPECIES_LUVDISC:
            return TYPE_FAIRY;
        case SPECIES_HUNTAIL:
            return TYPE_FIRE;
        case SPECIES_GOREBYSS:
            return TYPE_BUG;
        case SPECIES_PIPLUP: case SPECIES_PRINPLUP:
            return TYPE_ICE;
        case SPECIES_BUIZEL: 
            return TYPE_GHOST;
        case SPECIES_SHELLOS:
            return TYPE_BUG;
        case SPECIES_FINNEON: case SPECIES_LUMINEON:
            return TYPE_STELLAR;
        case SPECIES_PHIONE:
            return TYPE_WATER;
        case SPECIES_PANPOUR: case SPECIES_SIMIPOUR:
            return TYPE_STELLAR; 
        case SPECIES_FROAKIE: case SPECIES_FROGADIER: 
            return TYPE_ICE;
        case SPECIES_CLAUNCHER: case SPECIES_CLAWITZER:
            return TYPE_FIGHTING;
        case SPECIES_WISHIWASHI: 
            return TYPE_GROUND;
        case SPECIES_SOBBLE: case SPECIES_DRIZZILE: 
            return TYPE_DRAGON;
        case SPECIES_WIGLETT: case SPECIES_WUGTRIO: //Maybe do Tera Water Dugtrio-Alola as a complement
            return TYPE_STEEL;

        //Pure Normal Tera Types
        /*Not given a Tera Type because of points: Chansey, Blissey, Tauros (Rock if returned), Porygon2, PorygonZ, Snorlax,
         Ursaring (Fighting if returned), Ambipom, Zangoose, Cinccino, Maushold
        */  
        case SPECIES_RATTATA: case SPECIES_RATICATE:
            return TYPE_ICE; //Ice Beam or Tera Blast; but mainly to keep the Fighting weakness. Was Bug for U-Turn beforehand
            //Wanted to tone down the Tera type because of 3-point shakiness 
        case SPECIES_MEOWTH: case SPECIES_PERSIAN:
            return TYPE_FLYING; //Technician Aerial Ace
        case SPECIES_LICKITUNG: case SPECIES_LICKILICKY:
            return TYPE_STELLAR; //Various coverage and giving a one-time boost to Wring Out
        case SPECIES_HAPPINY: 
            return TYPE_ICE;
        case SPECIES_KANGASKHAN:
            return TYPE_FIGHTING;
        case SPECIES_DITTO:
            return TYPE_STELLAR;
        case SPECIES_EEVEE:
            return TYPE_NORMAL;
        case SPECIES_PORYGON: 
            return TYPE_ELECTRIC;
        case SPECIES_MUNCHLAX: 
            return TYPE_GRASS; //Thick Fat and Seed Bomb
        case SPECIES_SENTRET: case SPECIES_FURRET:
            return TYPE_FAIRY;
        case SPECIES_STANTLER:
            return TYPE_GRASS; //Sap Sipper and Energy Ball + Trailblaze
        case SPECIES_DUNSPARCE: case SPECIES_DUDUNSPARCE:
            return TYPE_DRAGON; //Scale Shot, Dragon Tail, e.t.c.
        //Teddiursa line pivots the curated Tera Type
        case SPECIES_TEDDIURSA:
            return TYPE_BUG;
        case SPECIES_AIPOM: 
            return TYPE_DARK; //Technician Beat Up for the earlier game
        case SPECIES_SMEARGLE:
            return TYPE_GHOST; //Immunity for frailness
        case SPECIES_MILTANK:
            return TYPE_FAIRY; //Play Rough
        case SPECIES_ZIGZAGOON: case  SPECIES_LINOONE:
            return TYPE_NORMAL;     
        case SPECIES_SLAKOTH: case SPECIES_VIGOROTH: 
        case SPECIES_SLAKING: //Keeping the Tera Type for Stomping Tantrum & Truant synergy purposes though it cannot tera in Restricted Mode
            return TYPE_GROUND;
        case SPECIES_WHISMUR: case SPECIES_LOUDRED: case SPECIES_EXPLOUD:
            return TYPE_FIRE; //Overheat
        case SPECIES_SKITTY: case SPECIES_DELCATTY:
            return TYPE_NORMAL; //To double-up with Normalize
        case SPECIES_SPINDA:
            return TYPE_PSYCHIC; //Psybeam and Psychic
        case SPECIES_CASTFORM:
            return TYPE_STELLAR;
        case SPECIES_KECLEON:
            return TYPE_GHOST; 
        case SPECIES_BUNEARY: case SPECIES_LOPUNNY:
            return TYPE_FLYING; //Bounce and Acrobatics
        case SPECIES_GLAMEOW: case SPECIES_PURUGLY:
            return TYPE_BUG; //U-Turn
        case SPECIES_REGIGIGAS:
            return TYPE_FIGHTING; //Hammer Arm
        case SPECIES_WATCHOG: case SPECIES_PATRAT:
            return TYPE_PSYCHIC; //Potential also for Stellar
        case SPECIES_MINCCINO: 
            return TYPE_WATER; //Aqua Tail
        case SPECIES_LILLIPUP: case SPECIES_HERDIER: case SPECIES_STOUTLAND:
            return TYPE_FAIRY; //Play Rough
        case SPECIES_AUDINO:
            return TYPE_NORMAL; //More damage output
        case SPECIES_BOUFFALANT:
            return TYPE_BUG; //Megahorn
        case SPECIES_FURFROU:
            return TYPE_WATER; //Defensive Type + Surf
        case SPECIES_YUNGOOS: case SPECIES_GUMSHOOS:
            return TYPE_STEEL; //with Iron Head and Iron Tail, and will probably give it Hard Press
        case SPECIES_KOMALA:
            return TYPE_POISON; //Poison Jab and Gunk Shot
        case SPECIES_TYPE_NULL: case SPECIES_SILVALLY:
            return TYPE_STELLAR;
        case SPECIES_SKWOVET: case SPECIES_GREEDENT:
            return TYPE_FIGHTING; //Body Press which synergizes with Stuff Cheeks
        case SPECIES_DUBWOOL: case SPECIES_WOOLOO:
            return TYPE_FLYING; //Bounce 
        case SPECIES_LECHONK:  case SPECIES_OINKOLOGNE: case SPECIES_OINKOLOGNE_F:
            return TYPE_GROUND; //High Horsepower and Dig
        case SPECIES_TANDEMAUS:  
            return TYPE_GRASS; //Technican Bullet Seed        

        //Pure Grass
        /*
        Not given a Tera Type because of points: Tangrowth, Shaymin, Rillaboom, Eldagoss, Ogerpon
        */
        case SPECIES_TANGELA: 
            return TYPE_ROCK; //Ancient Power, Rock Slide, Rock Tomb
        case SPECIES_CHIKORITA: case SPECIES_BAYLEEF: case SPECIES_MEGANIUM:
            return TYPE_DRAGON; //Dragon Tail and Outrage
        case SPECIES_BELLOSSOM:
            return TYPE_STELLAR;
        case SPECIES_SUNKERN: case SPECIES_SUNFLORA:
            return TYPE_GROUND; //Earth Power
        case SPECIES_TREECKO: case SPECIES_GROVYLE: case SPECIES_SCEPTILE:
            return TYPE_ELECTRIC; //Thunder Punch; adjacency to mega evolving Lightning Rod
        case SPECIES_SEEDOT:
            return TYPE_FLYING;
        case SPECIES_SHROOMISH:
            return TYPE_BUG;
        case SPECIES_CACNEA:
            return TYPE_POISON;
        case SPECIES_TURTWIG: case SPECIES_GROTLE:
            return TYPE_DARK; //Crunch
        case SPECIES_CHERUBI: case SPECIES_CHERRIM: case SPECIES_CHERRIM_SUNSHINE:
            return TYPE_FIRE;
        case SPECIES_CARNIVINE:
            return TYPE_STEEL; //Levitate synergy
        case SPECIES_LEAFEON:
            return TYPE_GROUND; //Dig
        case SPECIES_SNIVY: case SPECIES_SERVINE: case SPECIES_SERPERIOR:
            return TYPE_NORMAL; //For Wring Out, but Water is an alternative
        case SPECIES_PANSAGE: case SPECIES_SIMISAGE:
            return TYPE_STELLAR;
        case SPECIES_PETILIL: case SPECIES_LILLIGANT:
            return TYPE_FAIRY;
        case SPECIES_MARACTUS:
            return TYPE_ROCK; //Water Absorb/Storm Drain synergy
        case SPECIES_CHESPIN: case SPECIES_QUILLADIN:
            return TYPE_ROCK;
        case SPECIES_GOGOAT:
            return TYPE_FIGHTING; //Body Press
        case SPECIES_FOMANTIS: case SPECIES_LURANTIS:
            return TYPE_DARK; //Knock Off, Fling, Night Slash
        case SPECIES_BOUNSWEET: case SPECIES_STEENEE: case SPECIES_TSAREENA:
            return TYPE_ICE; //Triple Axel; resisting Ice beam and being immune to freeze at the same time is pretty nice
        case SPECIES_GROOKEY: case SPECIES_THWACKEY:
            return TYPE_NORMAL;
        case SPECIES_GOSSIFLEUR:
            return TYPE_BUG;
        case SPECIES_SPRIGATITO: case SPECIES_FLORAGATO:
            return TYPE_PSYCHIC;
        case SPECIES_CAPSAKID:
            return TYPE_FIRE; //Until it evolves
        case SPECIES_OGERPON:
            return TYPE_GRASS; //The Tera is banned in restricted mode, but defining this because it's necessary for Ogerpon

        //Pure Psychic
        /*
        Not given a Tera Type because of points: Alakazam, Mew, Espeon, Azelf, Cresselia, Reuniclus, Necrozma
        */
        case SPECIES_ABRA: case SPECIES_KADABRA:
            return TYPE_GHOST; //Shadow Ball
        case SPECIES_DROWZEE: case SPECIES_HYPNO:
            return TYPE_FIGHTING;
        case SPECIES_UNOWN:
            return TYPE_STELLAR;
        case SPECIES_WYNAUT: case SPECIES_WOBBUFFET:
            return TYPE_NORMAL;
        case SPECIES_SPOINK: case SPECIES_GRUMPIG:
            return TYPE_GROUND;
        case SPECIES_CHINGLING: case SPECIES_CHIMECHO:
            return TYPE_STEEL; //Levitate synergy
        case SPECIES_DEOXYS_DEFENSE:
            return TYPE_DRAGON;
        case SPECIES_UXIE:
            return TYPE_GHOST; //Change that doesn't alter its weaknesses
        case SPECIES_MESPRIT: 
            return TYPE_FIGHTING; //Drain Punch and newly gained Revenge
        case SPECIES_MUNNA: case SPECIES_MUSHARNA:
            return TYPE_ROCK;
        case SPECIES_GOTHITA: case SPECIES_GOTHORITA: case SPECIES_GOTHITELLE:
            return TYPE_BUG; //type distribution coverage
        case SPECIES_SOLOSIS: case SPECIES_DUOSION: 
            return TYPE_WATER;
        case SPECIES_ELGYEM: case SPECIES_BEHEEYEM:
            return TYPE_STELLAR;
        case SPECIES_ESPURR:
            return TYPE_STELLAR; //Pivot type
        case SPECIES_MEOWSTIC:
            return TYPE_GRASS; //Energy Ball + Defensive Type
        case SPECIES_MEOWSTIC_F:
            return TYPE_PSYCHIC; //Extra damage
        case SPECIES_PONYTA_GALAR:
            return TYPE_DRAGON;
        case SPECIES_SLOWPOKE_GALAR:
            return TYPE_POISON; //Because of evos
        case SPECIES_HATENNA: case SPECIES_HATTREM:
            return TYPE_DARK;
        case SPECIES_FLITTLE: case SPECIES_ESPATHRA:
            return TYPE_FLYING; //Brave Bird physical option
        
        //Pure Fire
        /*
        Not given a Tera Type because of points: Arcanine, Typhlosion, Entei, Cinderace
        */
        case SPECIES_CHARMANDER: case SPECIES_CHARMELEON:
            return TYPE_DRAGON;    
        case SPECIES_VULPIX: case SPECIES_NINETALES:
            return TYPE_GHOST; //One of the rare Pure Fires to get Shadow Ball
        case SPECIES_GROWLITHE:
            return TYPE_STEEL; //Iron Head and Iron Tail
        case SPECIES_PONYTA: case SPECIES_RAPIDASH:
            return TYPE_FAIRY; //Play Rough
        case SPECIES_FLAREON:
            return TYPE_NORMAL; //For Facade Guts
        case SPECIES_MAGBY: case SPECIES_MAGMAR: case SPECIES_MAGMORTAR:
            return TYPE_ELECTRIC; //Thunderbolt
        case SPECIES_CYNDAQUIL: case SPECIES_QUILAVA: 
            return TYPE_GROUND; 
        case SPECIES_SLUGMA:
            return TYPE_ROCK; //To get Rock STAB before evolution
        case SPECIES_TORKOAL:
            return TYPE_BUG; //For type distributions
        case SPECIES_CASTFORM_SUNNY:
            return TYPE_STELLAR;
        case SPECIES_CHIMCHAR:
            return TYPE_FIGHTING; //Fighting STAB before Evo
        case SPECIES_TEPIG: 
            return TYPE_ROCK; 
        case SPECIES_PANSEAR: case SPECIES_SIMISEAR:
            return TYPE_STELLAR;
        case SPECIES_DARUMAKA: case SPECIES_DARMANITAN:
            return TYPE_PSYCHIC; //Tera exception for Zen Mode
        case SPECIES_HEATMOR:
            return TYPE_GRASS; //Giga Drain; and Flash Fire synergy
        case SPECIES_FENNEKIN: case SPECIES_BRAIXEN:
            return TYPE_PSYCHIC; //For Evo
        case SPECIES_LITTEN: case SPECIES_TORRACAT:
            return TYPE_BUG;
        case SPECIES_SCORBUNNY: case SPECIES_RABOOT:
            return TYPE_NORMAL;
        case SPECIES_FUECOCO: case SPECIES_CROCALOR:
            return TYPE_GHOST; //For Evo    
        case SPECIES_CHARCADET:
            return TYPE_FIRE; //Extra power until it evolves

        //Pure Electric
        /*
        Not given a Tera Type because of points: Raikou, Xurkitree, Zeraora, Regieleki, Bellibolt
        */
        case SPECIES_PICHU: case SPECIES_PIKACHU: case SPECIES_RAICHU:
            return TYPE_WATER; //Surf
        case SPECIES_VOLTORB: case SPECIES_ELECTRODE:
            return TYPE_STEEL; //Gains Flash Cannon; doesn't invert the weakness, but enables lead Volt Switch Tera into later pivoting
        case SPECIES_JOLTEON:
            return TYPE_FIGHTING;
        case SPECIES_ELEKID: case SPECIES_ELECTABUZZ: case SPECIES_ELECTIVIRE:
            return TYPE_GROUND; //Earthquake
        case SPECIES_MAREEP: case SPECIES_FLAAFFY: case SPECIES_AMPHAROS:
            return TYPE_DRAGON; //Dragon Pulse, Mega
        case SPECIES_ELECTRIKE: case SPECIES_MANECTRIC:
            return TYPE_ICE; //Ice Fang and Tera Blast; would be Tera Fire if it weren't for the Overheat plan
        case SPECIES_PLUSLE:
            return TYPE_ELECTRIC; //Damage output
        case SPECIES_MINUN:
            return TYPE_GRASS; //Grass Knot
        case SPECIES_SHINX: case SPECIES_LUXIO: case SPECIES_LUXRAY:
            return TYPE_DARK; //Crunch
        case SPECIES_PACHIRISU:
            return TYPE_FAIRY; //Mainly defensive
        case SPECIES_BLITZLE: case SPECIES_ZEBSTRIKA:
            return TYPE_FLYING; //Bounce
        case SPECIES_TYNAMO: case SPECIES_EELEKTRIK: case SPECIES_EELEKTROSS:
            return TYPE_STELLAR; //Coverage machine
        case SPECIES_YAMPER: case SPECIES_BOLTUND:
            return TYPE_PSYCHIC; //Psychic Fangs
        case SPECIES_PINCURCHIN:
            return TYPE_POISON; //Poison Jab
        case SPECIES_PAWMI:
            return TYPE_FIGHTING; //Pre-evo typing grant
        case SPECIES_TADBULB:
            return TYPE_WATER;
        
        //Pure Fighting
        case SPECIES_MANKEY: 
        // case SPECIES_PRIMEAPE:
            return TYPE_FLYING; //Acrobatics
        case SPECIES_MACHOP: case SPECIES_MACHOKE: case SPECIES_MACHAMP:
            return TYPE_STELLAR; //Ideally I'd want to do Fighting, but that seems too insane with Machamp's stats, so opting for Stellar instead
        case SPECIES_TYROGUE:
            return TYPE_FIGHTING;
        case SPECIES_HITMONLEE: 
            return TYPE_NORMAL; //Reckless Double-Edge
        case SPECIES_HITMONCHAN:
            return TYPE_STEEL; //Good Defensive typing; Bullet Punch Iron Fist; also pairs nicely with the Meteor Mash addition
        case SPECIES_HITMONTOP:
            return TYPE_FAIRY; //Technician Covet
        case SPECIES_MAKUHITA: case SPECIES_HARIYAMA:
            return TYPE_GROUND; //Headlong Rush and Thick Fat
        case SPECIES_RIOLU:
            return TYPE_STEEL; //for evo type
        case SPECIES_TIMBURR: case SPECIES_GURDURR: 
            return TYPE_ROCK;
        // case SPECIES_CONKELDURR:
            // return TYPE_STEEL; //Hard Press
        case SPECIES_THROH:
            return TYPE_FIRE; //Fire Punch
        // case SPECIES_SAWK:
        //     return TYPE_ROCK; //Rock Slide
        case SPECIES_MIENFOO: 
            return TYPE_BUG; //U-Turn
        // case SPECIES_MIENSHAO:
        // return TYPE_FIRE; //Blaze Kick
        case SPECIES_PANCHAM:
            return TYPE_DARK; //Evo type
        case SPECIES_CRABRAWLER:
            return TYPE_ICE; //Evo type
        case SPECIES_PASSIMIAN:
            return TYPE_POISON; //Gunk Shot
        case SPECIES_CLOBBOPUS: 
            return TYPE_WATER; //Liquidation and new move of Aqua Jet
        case SPECIES_GRAPPLOCT:
            return TYPE_DARK; //Technician Beat Up
        case SPECIES_FARFETCHD_GALAR: case SPECIES_SIRFETCHD:
            return TYPE_GRASS; //Leek Leaf Blade
        // case SPECIES_FALINKS:
        //     return TYPE_BUG; //First Impression, Lunge, Megahorn
        case SPECIES_KUBFU:
            return TYPE_FIGHTING; //Just a buff
        // case SPECIES_TAUROS_PALDEA_COMBAT:
        //     return TYPE_PSYCHIC; //Zen Headbutt
        
        //Normal/Flying
        case SPECIES_PIDGEY: case SPECIES_PIDGEOTTO:
            return TYPE_NORMAL; //Uproar
        case SPECIES_PIDGEOT:
            return TYPE_FIRE; //Heat Wave
        case SPECIES_SPEAROW: case SPECIES_FEAROW:
            return TYPE_BUG; //U-Turn
        case SPECIES_FARFETCHD:
            return TYPE_NORMAL; //Extra power
        case SPECIES_DODUO: case SPECIES_DODRIO:
            return TYPE_GROUND; //Stomping Tantrum; will also get High Horsepower by Tutor
        case SPECIES_HOOTHOOT: case SPECIES_NOCTOWL:
            return TYPE_FAIRY; //Moonblast
        case SPECIES_TAILLOW: 
            return TYPE_DARK; //Pursuit
        // case SPECIES_SWELLOW:
            // return TYPE_WATER; //Filler Tera
        case SPECIES_SWABLU:
            return TYPE_DRAGON; //Evo type
        case SPECIES_STARLY: case SPECIES_STARAVIA: 
        // case SPECIES_STARAPTOR:
            return TYPE_ICE; //Retains weakness to Rock
        case SPECIES_CHATOT:
            return TYPE_STEEL; //Get a lot of resistances
        case SPECIES_PIDOVE: case SPECIES_TRANQUILL: case SPECIES_UNFEZANT:
            return TYPE_DARK; //Night Slash
        case SPECIES_RUFFLET: case SPECIES_BRAVIARY:
            return TYPE_FIGHTING; //Superpower / Close Combat
        case SPECIES_FLETCHLING:
            return TYPE_FIRE;
        case SPECIES_PIKIPEK: case SPECIES_TRUMBEAK: case SPECIES_TOUCANNON:
            return TYPE_ROCK; //Rock Blast
        case SPECIES_SQUAWKABILLY: case SPECIES_SQUAWKABILLY_BLUE: case SPECIES_SQUAWKABILLY_WHITE: case SPECIES_SQUAWKABILLY_YELLOW:
            return TYPE_ELECTRIC;
        
        //Pure Bug
        case SPECIES_CATERPIE: case SPECIES_METAPOD:
            return TYPE_ELECTRIC; //Electroweb
        case SPECIES_PINSIR:
            return TYPE_FIGHTING; //Abundant fighting moves
        case SPECIES_PINECO:
            return TYPE_STEEL; //Evo type
        case SPECIES_WURMPLE:
            return TYPE_STELLAR; //Neutral type
        case SPECIES_SILCOON:
            return TYPE_FLYING; //Evo type
        case SPECIES_CASCOON:
            return TYPE_POISON; //Evo type
        case SPECIES_VOLBEAT:
            return TYPE_ELECTRIC; //Thunderbolt
        case SPECIES_ILLUMISE:
            return TYPE_FAIRY; //Draining Kiss
        case SPECIES_KRICKETOT: case SPECIES_KRICKETUNE:
            return TYPE_FLYING; //Aerial Ace
        case SPECIES_BURMY: case SPECIES_BURMY_SANDY: case SPECIES_BURMY_TRASH:
            return TYPE_BUG; 
        case SPECIES_KARRABLAST:
            return TYPE_BUG;
        case SPECIES_SHELMET:
            return TYPE_STEEL;
        case SPECIES_ACCELGOR:
            return TYPE_POISON; //Sludge Bomb
        case SPECIES_SCATTERBUG: case SPECIES_SPEWPA:
            return TYPE_GRASS; //To align with Vivillon
        case SPECIES_GRUBBIN:
            return TYPE_ELECTRIC; //Evo type
        case SPECIES_BLIPBUG:
            return TYPE_PSYCHIC; //Evo type
        case SPECIES_TAROUNTULA: case SPECIES_SPIDOPS:
            return TYPE_STELLAR; //Boosted First Impression, Sucker Punch, Revenge, and so forth
        case SPECIES_RELLOR:
            return TYPE_GROUND;

        //Pure Fairy
        /*Excluded because of Tier Points: Clefable, Florges, Sylveon
        */
        case SPECIES_CLEFFA: case SPECIES_CLEFAIRY: case SPECIES_CLEFABLE: 
            return TYPE_NORMAL;
        case SPECIES_TOGEPI:
            return TYPE_FLYING; //Evo type
        case SPECIES_SNUBBULL: case SPECIES_GRANBULL:
            return TYPE_FIGHTING; //Close 
        case SPECIES_MILCERY: case SPECIES_ALCREMIE:
            return TYPE_FIRE;
        case SPECIES_FLABEBE: case SPECIES_FLABEBE_BLUE: case SPECIES_FLABEBE_ORANGE:
        case SPECIES_FLABEBE_WHITE: case SPECIES_FLABEBE_YELLOW: case SPECIES_FLOETTE: case SPECIES_FLOETTE_BLUE:
        case SPECIES_FLOETTE_ORANGE: case SPECIES_FLOETTE_WHITE: case SPECIES_FLOETTE_YELLOW:
            return TYPE_GRASS;
        case SPECIES_SPRITZEE: case SPECIES_AROMATISSE:
            return TYPE_STELLAR;
        case SPECIES_COMFEY:
            return TYPE_GRASS;
            // return TYPE_FLYING; //Has acrobatics, though doesn't have the Atk to use it
        case SPECIES_FIDOUGH: case SPECIES_DACHSBUN:
            return TYPE_ICE; //Ice Fang and Well Baked Body synergy
        
        //Pure Ice
        case SPECIES_CASTFORM_SNOWY:
            return TYPE_STELLAR;
        case SPECIES_SNORUNT: case SPECIES_GLALIE:
            return TYPE_GROUND;
        case SPECIES_REGICE:
            return TYPE_ELECTRIC;
        case SPECIES_GLACEON:
            return TYPE_FAIRY;
        case SPECIES_VANILLITE: case SPECIES_VANILLISH:  case SPECIES_VANILLUXE:
            return TYPE_POISON;
        case SPECIES_CUBCHOO: case SPECIES_BEARTIC:
            return TYPE_FIGHTING;
        case SPECIES_CRYOGONAL:
            return TYPE_FIRE;
        case SPECIES_BERGMITE: case SPECIES_AVALUGG:
            return TYPE_ICE;
        case SPECIES_VULPIX_ALOLA:
            return TYPE_FAIRY;
        case SPECIES_DARUMAKA_GALAR: case SPECIES_DARMANITAN_GALAR:
            return TYPE_NORMAL; //Tera banned in Restricted mode
        case SPECIES_EISCUE: case SPECIES_EISCUE_NOICE:
            return TYPE_WATER;
        case SPECIES_GLASTRIER:
            return TYPE_DARK;
        case SPECIES_CETODDLE: case SPECIES_CETITAN:
            return TYPE_STEEL;
        
        //Pure Ground
        case SPECIES_SANDSHREW: case SPECIES_SANDSLASH:
            return TYPE_FAIRY;
        case SPECIES_DIGLETT: case SPECIES_DUGTRIO:
            return TYPE_FLYING; //Aerial Ace
        case SPECIES_CUBONE: case SPECIES_MAROWAK:
            return TYPE_FIGHTING; //Low Kick, Brick Break
        case SPECIES_PHANPY: case SPECIES_DONPHAN:
            return TYPE_FIRE; 
        case SPECIES_TRAPINCH:
            return TYPE_BUG; 
        case SPECIES_HIPPOPOTAS: case SPECIES_HIPPOWDON:
            return TYPE_WATER; //Muddy Water and such
        case SPECIES_DRILBUR:
            return TYPE_STEEL; //Evo type
        case SPECIES_MUDBRAY: case SPECIES_MUDSDALE:
            return TYPE_ROCK; //Rock coverage
        case SPECIES_SILICOBRA: case SPECIES_SANDACONDA:
            return TYPE_DRAGON; //Scale Shot, Outrage, Dragon Rush
        
        //Pure Rock
        case SPECIES_BONSLY: case SPECIES_SUDOWOODO:
            return TYPE_GRASS;
        case SPECIES_NOSEPASS:
            return TYPE_ELECTRIC;
        case SPECIES_REGIROCK:
            return TYPE_ICE; //Ice Punch; Regice
        case SPECIES_CRANIDOS: case SPECIES_RAMPARDOS:
            return TYPE_PSYCHIC; //Zen Headbutt
        case SPECIES_ROGGENROLA: case SPECIES_BOLDORE: case SPECIES_GIGALITH:
            return TYPE_STELLAR;
        case SPECIES_ROCKRUFF: case SPECIES_ROCKRUFF_OWN_TEMPO: 
            return TYPE_NORMAL;
        case SPECIES_LYCANROC_MIDDAY:
            return TYPE_FLYING;
        case SPECIES_LYCANROC_DUSK:
            return TYPE_DRAGON; //Outrage
        case SPECIES_LYCANROC_MIDNIGHT:
            return TYPE_GHOST; //Shadow Claw
        case SPECIES_ROLYCOLY:
            return TYPE_FIRE; //Evo Type
        case SPECIES_STONJOURNER:
            return TYPE_GROUND; //standard ground moves
        case SPECIES_KLAWF:
            return TYPE_WATER; //Crabhammer

        //Pure Ghost
        case SPECIES_MISDREAVUS: case SPECIES_MISMAGIUS:
            return TYPE_FAIRY; //Flutter Mane basis
        case SPECIES_SHUPPET: case SPECIES_BANETTE:
            return TYPE_DARK; //covering both its weaknesses and STAB Knock Off + Sucker Punch
        case SPECIES_DUSKULL: case SPECIES_DUSCLOPS: case SPECIES_DUSKNOIR:
            return TYPE_FIGHTING; //Leech Life
        case SPECIES_YAMASK:
        case SPECIES_COFAGRIGUS:
            return TYPE_POISON;
        case SPECIES_CORSOLA_GALAR: case SPECIES_CURSOLA:
            return TYPE_NORMAL;
        case SPECIES_SINISTEA: case SPECIES_SINISTEA_ANTIQUE: case SPECIES_POLTEAGEIST: case SPECIES_POLTEAGEIST_ANTIQUE:
            return TYPE_GRASS; //Giga Drain
        case SPECIES_GREAVARD: case SPECIES_HOUNDSTONE:
            return TYPE_STELLAR;
         
        //Pure Poison
        case SPECIES_EKANS: case SPECIES_ARBOK:
            return TYPE_DRAGON; //Breaking Swipe and Scale Shot
        case SPECIES_NIDORAN_M: case SPECIES_NIDORAN_F: case SPECIES_NIDORINO: case SPECIES_NIDORINA:
            return TYPE_GROUND; //Evo basis
        case SPECIES_GRIMER: case SPECIES_MUK:
            return TYPE_WATER; //Also giving it Dive
        case SPECIES_KOFFING: case SPECIES_WEEZING:
            return TYPE_FIRE; 
        case SPECIES_GULPIN: case SPECIES_SWALOT:
            return TYPE_GRASS; //Giga Drain
        case SPECIES_SEVIPER:
            return TYPE_STELLAR;
        case SPECIES_GARBODOR: case SPECIES_TRUBBISH:
            return TYPE_STEEL; //Also give it Hard Press

        //Pure Dark
        case SPECIES_UMBREON:
            return TYPE_POISON; //Alongside Acid Spray
        case SPECIES_POOCHYENA: case SPECIES_MIGHTYENA:
            return TYPE_GHOST; //Get Fighting Immunity
        case SPECIES_ABSOL:
            return TYPE_FAIRY; //Play Rough
        case SPECIES_PURRLOIN: case SPECIES_LIEPARD:
            return TYPE_STELLAR;
        case SPECIES_ZORUA: case SPECIES_ZOROARK:
            return TYPE_PSYCHIC; //Psychic(move)
        case SPECIES_MEOWTH_ALOLA: case SPECIES_PERSIAN_ALOLA:
            return TYPE_GRASS; //Seed Bomb
        case SPECIES_NICKIT: case SPECIES_THIEVUL:
            return TYPE_FIRE; //Burning Jealousy
        case SPECIES_MASCHIFF: case SPECIES_MABOSSTIFF:
            return TYPE_ELECTRIC; //Wild Charge

        //Bug/Flying
        
        case SPECIES_BUTTERFREE:
            return TYPE_FLYING; //Really strong Compoundeyes Hurricanes
        case SPECIES_SCYTHER:
            return TYPE_NORMAL; //Technician Double Hit
        case SPECIES_LEDYBA: case SPECIES_LEDIAN:
            return TYPE_FAIRY; //Gets a Dark resistance for Rattled; also is added Dazzling Gleam by tutor.
        case SPECIES_YANMA: case SPECIES_YANMEGA:
            return TYPE_GHOST; 
        case SPECIES_BEAUTIFLY:
            return TYPE_GROUND; //Great type synergy but reliant on Tera Blast; also given Mud-Slap for slightly more utility.
        case SPECIES_MASQUERAIN:
            return TYPE_WATER; //Regain its Water type
        case SPECIES_NINJASK:
            return TYPE_ICE; //Night Slash
        case SPECIES_MOTHIM:
            return TYPE_ELECTRIC; //Electroweb
        case SPECIES_COMBEE: case SPECIES_VESPIQUEN:
            return TYPE_STEEL; //Defensive typing
        case SPECIES_VIVILLON:
            return TYPE_GRASS;        
        
        //Grass/Poison
        case SPECIES_BULBASAUR: case SPECIES_IVYSAUR: case SPECIES_VENUSAUR:
            return TYPE_GROUND;
        case SPECIES_ODDISH: case SPECIES_GLOOM:
            return TYPE_POISON; //Keep going with the poison theme
        case SPECIES_VILEPLUME:
            return TYPE_FAIRY;
        case SPECIES_BELLSPROUT: case SPECIES_WEEPINBELL: case SPECIES_VICTREEBEL:
            return TYPE_DARK;
        case SPECIES_BUDEW: case SPECIES_ROSELIA: case SPECIES_ROSERADE:
            return TYPE_BUG; //Technician Pin Missile
        case SPECIES_FOONGUS: case SPECIES_AMOONGUSS:
            return TYPE_STELLAR; //More offensive possibility, and also as a counterbalance to Regenerator longevity

        //Pure Dragon
        /*Not included because of tier points: Haxorus, Goodra, Regidrago
        */
        case SPECIES_DRATINI: case SPECIES_DRAGONAIR:
            return TYPE_WATER;
        case SPECIES_BAGON: case SPECIES_SHELGON:
            return TYPE_FIRE; //Fire moves
        case SPECIES_AXEW: case SPECIES_FRAXURE:
            return TYPE_BUG; //First Impression
        case SPECIES_DRUDDIGON:
            return TYPE_FAIRY; //Just for type distributions. 
        case SPECIES_GOOMY: case SPECIES_SLIGGOO: 
            return TYPE_WATER; //Hydration and several water moves
        case SPECIES_JANGMO_O:
            return TYPE_FIGHTING; //Evo Basis

        //Pure Steel
        case SPECIES_REGISTEEL:
            return TYPE_ICE; //Ice Punch and Ice Spinner
        case SPECIES_KLINK: case SPECIES_KLANG: case SPECIES_KLINKLANG:
            return TYPE_FLYING; //Type inversion
        case SPECIES_MELMETAL:
            return TYPE_NORMAL;
        case SPECIES_CUFANT: case SPECIES_COPPERAJAH:
            return TYPE_FIRE; // Heat Crash
        case SPECIES_PERRSERKER:
            return TYPE_DARK; //Foul Play and Knock Off
        case SPECIES_ORTHWORM:
            return TYPE_ROCK; //Still gets the Earth Eater immunity to an otherwise weakness

        //Bug/Poison
        case SPECIES_WEEDLE: case SPECIES_KAKUNA:
            return TYPE_POISON; //stronger Poison Sting
        case SPECIES_BEEDRILL:
            return TYPE_DARK; //Knock Off, Throat Chop, Payback, Psychic immunity
        case SPECIES_VENONAT: case SPECIES_VENOMOTH:
            return TYPE_PSYCHIC; //Psychic move, and Psychic resistance
        case SPECIES_SPINARAK: case SPECIES_ARIADOS: 
            return TYPE_POISON; //Boosted Poison moves alongside Merciless
        case SPECIES_SKORUPI:
            return TYPE_DARK; //Evo type
        case SPECIES_VENIPEDE: case SPECIES_WHIRLIPEDE: case SPECIES_SCOLIPEDE:
            return TYPE_GROUND; //Stomping Tantrum and EQ
        //Rock/Water
        case SPECIES_OMANYTE: case SPECIES_OMASTAR:
            return TYPE_ELECTRIC;
        case SPECIES_KABUTO: case SPECIES_KABUTOPS:
            return TYPE_BUG; //Leech Life
        case SPECIES_CORSOLA:
            return TYPE_GRASS; //dodge quad resistance
        case SPECIES_RELICANTH:
            return TYPE_NORMAL; //Double-Edge
        case SPECIES_TIRTOUGA: case SPECIES_CARRACOSTA:
            return TYPE_DRAGON; 
        case SPECIES_BINACLE: case SPECIES_BARBARACLE:
            return TYPE_FIGHTING; //Mega basis
        case SPECIES_DREDNAW:
            return TYPE_ICE; //Ice Spinner

        //Ghost/Grass
        case SPECIES_PHANTUMP: case SPECIES_TREVENANT:
            return TYPE_GROUND; //Earthquake
        case SPECIES_PUMPKABOO: case SPECIES_PUMPKABOO_LARGE: case SPECIES_PUMPKABOO_SMALL: case SPECIES_PUMPKABOO_SUPER:
        case SPECIES_GOURGEIST: case SPECIES_GOURGEIST_LARGE: case SPECIES_GOURGEIST_SMALL: case SPECIES_GOURGEIST_SUPER:
            return TYPE_FIRE; //Flamethrower, Flame Charge
        case SPECIES_DECIDUEYE:
            return TYPE_FLYING; //Mimic former flying type
        case SPECIES_DHELMISE:
            return TYPE_WATER; //Liquidation
        case SPECIES_BRAMBLIN: case SPECIES_BRAMBLEGHAST:
            return TYPE_BUG; //Pounce and Skitter Smack
        case SPECIES_POLTCHAGEIST: case SPECIES_POLTCHAGEIST_ARTISAN: 
        case SPECIES_SINISTCHA: case SPECIES_SINISTCHA_MASTERPIECE:
            return TYPE_PSYCHIC; //Filler type

        //Rock/Ground
        case SPECIES_GEODUDE: case SPECIES_GRAVELER: case SPECIES_GOLEM:
            return TYPE_STEEL;
        case SPECIES_ONIX:
            return TYPE_DRAGON; //Dragon Breath; could also be Steel depending on overlap factors
        case SPECIES_RHYHORN: case SPECIES_RHYDON: case SPECIES_RHYPERIOR:
            return TYPE_NORMAL; //Rock Head Double-Edge
        case SPECIES_LARVITAR: case SPECIES_PUPITAR:
            return TYPE_DARK; //Evo basis

        //Steel/Psychic
        case SPECIES_BELDUM: case SPECIES_METANG: case SPECIES_METAGROSS:
            return TYPE_NORMAL; //Take Down for Beldum; Explosion for Metang
        case SPECIES_JIRACHI:
            return TYPE_FAIRY; //Moonblast
        case SPECIES_BRONZOR: case SPECIES_BRONZONG:
            return TYPE_GRASS; //Heatproof synergy
        case SPECIES_IRON_CROWN:
            return TYPE_FIGHTING; //Filler type
        
        //Water/Ground
        case SPECIES_WOOPER: case SPECIES_QUAGSIRE:
            return TYPE_ICE; //Avalanche
        case SPECIES_MARSHTOMP: case SPECIES_SWAMPERT:
            return TYPE_ROCK; //Rock Slide and such
        case SPECIES_GASTRODON:
            return TYPE_PSYCHIC;
        case SPECIES_PALPITOAD: case SPECIES_SEISMITOAD:
            return TYPE_FIGHTING; //Drain Punch
        case SPECIES_BARBOACH: case SPECIES_WHISCASH:
            return TYPE_STELLAR; //Additional Power boost

        //Psychic/Flying
        case SPECIES_NATU: case SPECIES_XATU:
            return TYPE_DARK; //Sucker Punch and Foul Play
        case SPECIES_WOOBAT: case SPECIES_SWOOBAT:
            return TYPE_PSYCHIC; //Extra damage
        case SPECIES_SIGILYPH:
            return TYPE_POISON; 
        case SPECIES_ORICORIO_PAU:
            return TYPE_FAIRY; //Make all Oricorios Fairy type since forms can be swapped
        case SPECIES_ARTICUNO_GALAR:
            return TYPE_ICE;
        case SPECIES_BRAVIARY_HISUI:
            return TYPE_NORMAL; //Regular Braviary homage
        
        //Psychic/Fairy
        /*Tier points exclusion: Gardevoir, Hatterene, Tapu Lele, Scream Tail
        */
        case SPECIES_MIME_JR:  case SPECIES_MR_MIME:
            return TYPE_ELECTRIC; //Thunderbolt, Technician Charge Beam
        case SPECIES_RALTS: case SPECIES_KIRLIA:
            return TYPE_GRASS; //Energy Ball
        case SPECIES_RAPIDASH_GALAR:
            return TYPE_DRAGON;

        //Ghost/Fire
        case SPECIES_LITWICK: case SPECIES_LAMPENT: case SPECIES_CHANDELURE:
            return TYPE_DARK; //Dark Pulse

        //The below is whatever since these are all restricted mode banned.
        case SPECIES_MAROWAK_ALOLA:
            return TYPE_DRAGON; //Outrage
        case SPECIES_TYPHLOSION_HISUI:
            return TYPE_GROUND;
        case SPECIES_SKELEDIRGE:
            return TYPE_FAIRY; 
        case SPECIES_CERULEDGE:
            return TYPE_FIGHTING;
        //Not bothering with Blacephalon since it's probably not available
        
        //Water/Flying
        case SPECIES_GYARADOS:
            return TYPE_DARK; //Mega basis
        case SPECIES_MANTYKE: case SPECIES_MANTINE: 
            return TYPE_ICE; //Blizzard
        case SPECIES_DUCKLETT: case SPECIES_SWANNA:
            return TYPE_FAIRY; //Alluring Voice
        case SPECIES_CRAMORANT:
            return TYPE_POISON; //Belch        

        //Water/Ice
        case SPECIES_DEWGONG:
            return TYPE_BUG; //Megahorn
        case SPECIES_CLOYSTER:
            return TYPE_NORMAL; //Spike Cannon; potential Tier Points 4+ mon, but currently not yet
        case SPECIES_LAPRAS:
            return TYPE_PSYCHIC; //Psychic Noise
        case SPECIES_SPHEAL: case SPECIES_SEALEO: case SPECIES_WALREIN:
            return TYPE_GROUND; //Earthquake/Stomping Tantrum
        case SPECIES_ARCTOVISH:
            return TYPE_ROCK; //Rock Blast
        
        //Dark/Flying
        /*Not included because of Tier Points: Mandibuzz, Moltres-Galar, Iron Jugulis
        */
        case SPECIES_MURKROW: case SPECIES_HONCHKROW:
            return TYPE_FIGHTING; //Superpower
        case SPECIES_VULLABY:
            return TYPE_ROCK; //More power in Monotype
        case SPECIES_BOMBIRDIER:
            return TYPE_NORMAL; //Rocky Payload
        //Not including Yveltal
        
        //Poison/Dark
        case SPECIES_STUNKY: case SPECIES_SKUNTANK:
            return TYPE_FIRE; //Temper Flare, Fire Blast
        case SPECIES_DRAPION:
            return TYPE_BUG; //pre-evo basis
        case SPECIES_MUK_ALOLA:
            return TYPE_ROCK; //Rock Slide
        case SPECIES_QWILFISH_HISUI: case SPECIES_OVERQWIL:
            return TYPE_ICE;
        
        //Steel/Rock
        case SPECIES_ARON: case SPECIES_LAIRON: case SPECIES_AGGRON:
            return TYPE_ICE; //Ice Punch and preserving not the best Tera Type
        case SPECIES_SHIELDON: case SPECIES_BASTIODON:
            return TYPE_DARK; //Foul Play boost
        case SPECIES_PROBOPASS:
            return TYPE_ELECTRIC; //A lot of electric moves
        
        //Steel/Fairy
        case SPECIES_MAWILE:
            return TYPE_DARK; //Sucker Punch    
        case SPECIES_KLEFKI:
            return TYPE_ELECTRIC;
        case SPECIES_MAGEARNA:
            return TYPE_PSYCHIC; 
        case SPECIES_TINKATON:
            return TYPE_ROCK;
        
        //Fire/Fighting
        case SPECIES_COMBUSKEN:  case SPECIES_BLAZIKEN:
            return TYPE_FLYING; //Brave Bird
        case SPECIES_MONFERNO: case SPECIES_INFERNAPE: 
            return TYPE_POISON; //Gunk Shot
        case SPECIES_EMBOAR:
            return TYPE_ROCK; //Reckless Head Smash
        case SPECIES_TAUROS_PALDEA_BLAZE:
            return TYPE_NORMAL; //Regular Tauros basis
        
        //Grass/Flying
        case SPECIES_HOPPIP: case SPECIES_SKIPLOOM: case SPECIES_JUMPLUFF:
            return TYPE_FLYING; //More power
        case SPECIES_TROPIUS:
            return TYPE_FIRE; //Sun Weather Ball
        case SPECIES_SHAYMIN_SKY:
            return TYPE_BUG;
        case SPECIES_ROWLET: case SPECIES_DARTRIX:
            return TYPE_GHOST; // Evo basis
        
        //Grass/Dragon
        /*Not included because of Tier Points: Dipplin, Hydrapple
        */
        case SPECIES_EXEGGUTOR_ALOLA:
            return TYPE_PSYCHIC; //Exeggcute basis
        case SPECIES_FLAPPLE:
            return TYPE_FLYING; //Acrobatics and Fly
        case SPECIES_APPLIN:
            return TYPE_BUG;
        case SPECIES_APPLETUN:
            return TYPE_FIGHTING; //Body Press and Superpower
        
        //Grass/Dark
        case SPECIES_CACTURNE:
            return TYPE_DARK; //Boosted Payback and Sucker Punch
            //Water Absorb + Shedding the Grass Type makes it quite good against Water types with Ice moves
        case SPECIES_NUZLEAF:
            return TYPE_FIGHTING; 
        case SPECIES_SHIFTRY:
            return TYPE_FLYING; //Air Slash and Hurricane Shiftry
        case SPECIES_ZARUDE:
            return TYPE_NORMAL; //Filler type
        case SPECIES_MEOWSCARADA:
            return TYPE_ELECTRIC; //Not much thought put into it since it can't tera in restricted mode
        case SPECIES_BRUTE_BONNET:
            return TYPE_FIGHTING;
        case SPECIES_WO_CHIEN:
            return TYPE_POISON; 
        
        //Electric/Flying
        /*Not included because of tier points: Zapdos, Thundurus
        */
        case SPECIES_ROTOM_FAN:
            return TYPE_GHOST;
        case SPECIES_EMOLGA:
            return TYPE_STEEL; //Resists both of the types SE against it
        case SPECIES_ORICORIO_POM_POM:
            return TYPE_FAIRY; //ALl Oricorios will have the same type
        case SPECIES_WATTREL: case SPECIES_KILOWATTREL:
            return TYPE_WATER; //Rain Dance synergy
    
        //Normal/Psychic
        case SPECIES_GIRAFARIG: case SPECIES_FARIGIRAF:
            return TYPE_WATER;
        case SPECIES_MELOETTA: 
            return TYPE_GHOST;
        case SPECIES_ORANGURU:
            return TYPE_GRASS; //Energy Ball
        case SPECIES_WYRDEER:
            return TYPE_GROUND; //Sap Sipper synergy
        case SPECIES_INDEEDEE_F: case SPECIES_INDEEDEE_M:
            return TYPE_FIGHTING;

        //Ghost/Ground
        case SPECIES_GOLETT: case SPECIES_GOLURK:
            return TYPE_FIGHTING; //Iron Fist
        case SPECIES_SANDYGAST: case SPECIES_PALOSSAND:
            return TYPE_GRASS; //Giga Drain and Water Compaction synergy
        case SPECIES_YAMASK_GALAR: case SPECIES_RUNERIGUS:
            return TYPE_ROCK; 
        
        //Ground/Dragon
        /*Not included because of Tier points: Garchomp, Zygarde
        */
        case SPECIES_VIBRAVA: case SPECIES_FLYGON:
            return TYPE_BUG; //Based on all of Flygon's bug moves
        case SPECIES_GIBLE: case SPECIES_GABITE: 
            return TYPE_FIRE;
        case SPECIES_ZYGARDE_10:
            return TYPE_DARK; //Crunch
        
        //Bug/Rock
        case SPECIES_SHUCKLE:
            return TYPE_BUG; //Choosing to not give Shuckle a new defensive type
        case SPECIES_ANORITH: case SPECIES_ARMALDO:
            return TYPE_NORMAL;
        case SPECIES_DWEBBLE: case SPECIES_CRUSTLE:
            return TYPE_GROUND;
        case SPECIES_KLEAVOR:
            return TYPE_FLYING; //Scyther basis
        
        //Bug/Steel
        case SPECIES_FORRETRESS:
            return TYPE_GROUND;
        case SPECIES_SCIZOR:
            return TYPE_ROCK; //Kleavor basis
        case SPECIES_WORMADAM_TRASH:
            return TYPE_GRASS; //Retains the fire weakness
        case SPECIES_ESCAVALIER:
            return TYPE_WATER; //Razor Shell
        case SPECIES_DURANT:
            return TYPE_DARK;
        case SPECIES_GENESECT:
            return TYPE_ROCK;
        
        //Bug/Grass
        case SPECIES_PARAS: case SPECIES_PARASECT:
            return TYPE_GROUND; //Dry Skin synergy
        case SPECIES_WORMADAM_PLANT:
            return TYPE_GHOST; //Shadow Ball
        case SPECIES_SEWADDLE: case SPECIES_SWADLOON: case SPECIES_LEAVANNY:
            return TYPE_DRAGON;
        
        //Steel/Ground
        /*Not included because of Tier Points: Steelix, Excadrill, Dugtrio-Alola, Iron Treads
        */
        case SPECIES_DIGLETT_ALOLA:
            return TYPE_WATER; //Relation to Wugtrio
        case SPECIES_STUNFISK_GALAR:
            return TYPE_GHOST; //Payback and Crunch
        
        //Fire/Flying
        /*Not included because of Tier Points: Charizard, Moltres, Talonflame
        */        
        case SPECIES_FLETCHINDER:
            return TYPE_BUG; //U-Turn
        case SPECIES_ORICORIO_BAILE:
            return TYPE_FAIRY; //Same tera type for each Oricorio form

        //Water/Poison
        /*Not included because of Tier Points: Toxapex
        */       
        case SPECIES_TENTACOOL: case SPECIES_TENTACRUEL:
            return TYPE_FIGHTING; //Mainly just choosing a type that isn't the most useful; keeps Psychic weakness
        case SPECIES_QWILFISH:
            return TYPE_POISON; //Extra damage output compared to Qwilfish-Hisui
        case SPECIES_SKRELP:
            return TYPE_ELECTRIC; //Thunderbolt
        case SPECIES_MAREANIE:
            return TYPE_DARK;

        //Water/Psychic
        /*Not included because of Tier Points: Slowbro, Slowking, Starmie, 
        */         
        case SPECIES_SLOWPOKE:
            return TYPE_GRASS; //Grass Knot
        case SPECIES_BRUXISH:
            return TYPE_ICE; //Strong Jaw boosted Ice Fang
        case SPECIES_VELUZA:
            return TYPE_DARK; //Sharpness Night Slash
        
        //Water/Dragon
        /*Not included because of Tier Points: Kingdra, Palkia, Dracovish, Walking Wake
        */                 
        case SPECIES_TATSUGIRI: case SPECIES_TATSUGIRI_DROOPY: case SPECIES_TATSUGIRI_STRETCHY:
            return TYPE_ICE; //boosted Icy Wind
        
        //Water/Dark
        /*Not included because of Tier Points: Greninja, Samurott-Hisui
        */                         
        case SPECIES_CARVANHA: case SPECIES_SHARPEDO:
            return TYPE_PSYCHIC; //Zen Headbutt
        case SPECIES_CRAWDAUNT:
            return TYPE_POISON; //Increase the incentive to use Sludge Bomb or Sludge Wave
        
        //Grass/Fairy
        /*Not included because of Tier Points: Whimsicott, Tapu Bulu
        */     
        case SPECIES_COTTONEE:
            return TYPE_GRASS; //Power boost and parallel with Petilil
        case SPECIES_MORELULL:
        case SPECIES_SHIINOTIC:
            return TYPE_WATER; //Rain Dish Weather Ball

        //Dragon/Flying
        /*Not included because of Tier Points: Dragonite, Salamence, Noivern
        */           
        case SPECIES_NOIBAT:
            return TYPE_ELECTRIC; //WIld Charge
        case SPECIES_ALTARIA:
            return TYPE_GRASS; //Solarbeam
        
        //Normal/Grass
        /*Not included because of Tier Points: Arboliva
        */
        case SPECIES_DEERLING: case SPECIES_DEERLING_AUTUMN: case SPECIES_DEERLING_SUMMER: case SPECIES_DEERLING_WINTER:
        case SPECIES_SAWSBUCK: case SPECIES_SAWSBUCK_AUTUMN: case SPECIES_SAWSBUCK_SUMMER: case SPECIES_SAWSBUCK_WINTER:
            return TYPE_WATER; //Sap Sipper synergy
        case SPECIES_SMOLIV: case SPECIES_DOLLIV:
            return TYPE_GROUND; 

        //Normal/Fairy
        case SPECIES_IGGLYBUFF: case SPECIES_JIGGLYPUFF: case SPECIES_WIGGLYTUFF:
            return TYPE_STEEL; //Gyro Ball and Steel Roller
        case SPECIES_AZURILL:
            return TYPE_WATER; //Evo basis
        
        //Poison/Fighting
        /*Not included because of Tier Points: Sneasler, Okidogi
        */
        case SPECIES_CROAGUNK: case SPECIES_TOXICROAK:
            return TYPE_ELECTRIC; //Thunder Punch
        
        //Bug/Water
        /*Not included because of Tier Points: Araquanid, Golisopod
        */
        case SPECIES_SURSKIT:
            return TYPE_FAIRY; 
        case SPECIES_DEWPIDER:
            return TYPE_DARK; //Bite
        
        //Steel/Dragon
        /*Not included because of Tier Points: Goodra-Hisui, Archaludon
        */
        case SPECIES_DURALUDON:
            return TYPE_ELECTRIC; 
        case SPECIES_SLIGGOO_HISUI:
            return TYPE_ROCK; //Keeps the same weaknesses
        
        
        //Fire/Rock
        /*Not included because of Tier Points: Coalossal and Arcanine-Hisui
        */
        case SPECIES_MAGCARGO:
            return TYPE_GRASS; //Defensive type, though there's also Solarbeam
        case SPECIES_CARKOL: 
            return TYPE_WATER; //Scald
        case SPECIES_GROWLITHE_HISUI:
            return TYPE_STEEL;

        //Water/Fighting
        /*Not included because of Tier Points: Urshifu-Rapid, Tauros-Paldea-Aqua, Quaquaval, Keldeo
        */
        case SPECIES_POLIWRATH:
            return TYPE_PSYCHIC; //For Fighting-type Tera coverage
        
        //Grass/Fighting
        /*/*Not included because of Tier Points: Chesnaught, Lilligant-Hisui, 
        */
        case SPECIES_BRELOOM:
            return TYPE_BUG;
        case SPECIES_VIRIZION:
            return TYPE_FLYING; //Slightly stronger Aerial Ace
        case SPECIES_DECIDUEYE_HISUI:
            return TYPE_GHOST; //Leveraging a lot of the Ghost moves the Rowlet line can learn
        
        //Grass/Psychic
        /*/*Not included because of Tier Points: Celebi, Iron Leaves 
        */        
        case SPECIES_EXEGGCUTE: case SPECIES_EXEGGUTOR:
            return TYPE_FIGHTING; //Low Kick
        case SPECIES_CALYREX: 
            return TYPE_GRASS; //extra power
        
        //Ice/Psychic
        case SPECIES_SMOOCHUM: case SPECIES_JYNX:
            return TYPE_FAIRY; //Draining Kiss and also give Alluring Voice
        case SPECIES_MR_MIME_GALAR: case SPECIES_MR_RIME:
            return TYPE_GRASS; //Grass Knot
        
        //All Dragon/Electric mons are currently 4+ points so no curated teras included

        //Normal/Dark
        /*Not included because of Tier Points: Obstagoon
        */
        case SPECIES_RATTATA_ALOLA: case SPECIES_RATICATE_ALOLA:
            return TYPE_BUG; //Resists Fighting and Thick Fat basis
        case SPECIES_ZIGZAGOON_GALAR: case SPECIES_LINOONE_GALAR: 
            return TYPE_POISON; //Gunk Shot and Cross Poison 

        //Dark/Dragon
        /*Not included because of Tier Points: Hydreigon, Roaring Moon
        */
        case SPECIES_DEINO: case SPECIES_ZWEILOUS:
            return TYPE_FIGHTING; //Superpower
        case SPECIES_GUZZLORD:
            return TYPE_GROUND; //Earthquake
        
        //Normal/Fighting
        /*Not included because of Tier Points: Bewear, Meloetta-Pirouette
        */
        case SPECIES_STUFFUL:
            return TYPE_ROCK; //Rock Slide and Fluffy synergy
        
        //Fighting/Psychic
        /*Not included because of Tier Points: Gallade
        */
        case SPECIES_MEDITITE: case SPECIES_MEDICHAM:
            return TYPE_ICE; //Ice Punch; Medicham is only applicable in Restricted Mode if it has Telepathy
        
        
        //Poison/Ground
        /*Not included because of Tier Points: Nidoking, Clodsire
        */
        case SPECIES_NIDOQUEEN:
            return TYPE_FIGHTING; //Superpower
        case SPECIES_WOOPER_PALDEA:
            return TYPE_ROCK; 
        
        //Ground/Dark
        /*Not included because of Tier Points: Krookodile, Ting-Lu
        */
        case SPECIES_SANDILE: case SPECIES_KROKOROK:
            return TYPE_WATER; //Aqua Tail
        
        //Rock/Flying
        /*Not included because of Tier Points: Aerodactyl, Archeops
        */
        case SPECIES_ARCHEN:
            return TYPE_GHOST;
        case SPECIES_MINIOR:
            return TYPE_STELLAR; 
        
        //Rock/Electric
        /*Not included because of Tier Points: Iron Thorns
        */
        case SPECIES_GEODUDE_ALOLA: case SPECIES_GRAVELER_ALOLA: case SPECIES_GOLEM_ALOLA:
            return TYPE_FIRE; //Fire Punch
        
        //All Bug/Fighting mons exceed the curated tera tier points
    
        //Bug/Fire
        /*Not included because of Tier Points: Volcarona
        */
        case SPECIES_LARVESTA: 
            return TYPE_FIGHTING; //Slither Wing basis
        case SPECIES_SIZZLIPEDE: case SPECIES_CENTISKORCH:
            return TYPE_DARK; //Knock Off and Crunch
        
        //Bug/Electric
        case SPECIES_JOLTIK: case SPECIES_GALVANTULA:
            return TYPE_POISON;
        case SPECIES_CHARJABUG: case SPECIES_VIKAVOLT:
            return TYPE_STEEL; //Flash Cannon
        
        //Ghost/Poison
        /*Not included because of Tier Points: Gengar and Pecharunt
        */
        case SPECIES_GASTLY: case SPECIES_HAUNTER:
            return TYPE_ELECTRIC; //Thunderbolt

        //Ghost/Dragon
        /*Not included because of Tier Points: Dragapult
        */
        case SPECIES_DREEPY: case SPECIES_DRAKLOAK:
            return TYPE_WATER; //Dive
        
        //Steel/Ghost
        /*Not included because of Tier Points: Aegislash and Gholdengo
        */
        case SPECIES_HONEDGE: case SPECIES_DOUBLADE:
            return TYPE_ROCK; //Couples with the Head Smash addition, which pairs with No Guard
        
        //Dragon/Fire
        /*Not included because of Tier Points: Gouging Fire
        */
        case SPECIES_TURTONATOR:
            return TYPE_STEEL; 
        
        //Water/Grass
        case SPECIES_LOTAD: case SPECIES_LOMBRE: case SPECIES_LUDICOLO:
            return TYPE_NORMAL; //Hyper Voice
        case SPECIES_OGERPON_WELLSPRING:
            return TYPE_WATER; //A necessity for Wellspring, but it can't tera in Restricted mode
        
        //Water/Fairy
        /*Not included because of Tier Points: Primarina and Tapu Fini
        */
        case SPECIES_MARILL: //Dig
        case SPECIES_AZUMARILL: //Only permitted for the Thick Fat exception
            return TYPE_GROUND;
        
        //Electric/Steel
        /*Not included because of Tier Points: Magneton, Magnezone, Togedemaru
        */
        case SPECIES_MAGNEMITE:
            return TYPE_BUG; 
        
        //All Psychic/Ghost mons exceed the Tier Points threshold

        //Fire/Psychic
        /*Not included because of Tier Points: Victini, Delphox, Armarouge
        */
        case SPECIES_DARMANITAN_ZEN:
            return TYPE_PSYCHIC; //Gets an extra power boost
        
        //Dark/Fighting
        /*Not included because of Tier Points: Urshifu-Single-Strike
        */
        case SPECIES_SCRAGGY: case SPECIES_SCRAFTY:
            return TYPE_DRAGON; //Dragon Claw
        case SPECIES_PANGORO:
            return TYPE_DARK; //Extra power and shedding Fighting weaknesses
        
        //Dark/Fire
        /*Not included because of Tier Points: Incineroar
        */
        case SPECIES_HOUNDOUR: case SPECIES_HOUNDOOM:
            return TYPE_PSYCHIC; //Psychic Fangs
        
        //Dragon/Ice
        /*Not included because of Tier Points: Baxcalibur
        */        
        case SPECIES_ARCTIBAX: case SPECIES_FRIGIBAX:
            return TYPE_DARK; //Crunch
        
        //Fairy/Flying
        /*Not included because of Tier Points: Togekiss and Enamorus
        */
        case SPECIES_TOGETIC:
            return TYPE_NORMAL; //Old normal type basis
        
        //Pure Flying
        case SPECIES_ROOKIDEE: case SPECIES_CORVISQUIRE:
            return TYPE_STEEL; //Evo basis
        
        //Fighting/Flying mons all have excess Tier Points

        //Fighting/Steel mons all have excess Tier Points

        //Poison/Flying
        /*Not included because of Tier Points: Crobat
        */
        case SPECIES_ZUBAT: case SPECIES_GOLBAT:
            return TYPE_GHOST; //Astonish, Shadow Ball, and Curse

        //Poison/Fire
        /*Not included because of Tier Points: Salazzle and Iron Moth
        */
        case SPECIES_SALANDIT:
            return TYPE_POISON; //Extra poison prowess
        
        //Poison/Psychic mons all have excess Tier Points

        //Poison/Dragon
        case SPECIES_DRAGALGE:
            return TYPE_WATER; //pre-evo basis
        
        //Ground/Flying
        /*Not included because of Tier Points: Gliscor and Landorus
        */
        case SPECIES_GLIGAR:
            return TYPE_BUG;
        
        //Rock/Poison
        /*Not included because of Tier Points: Nihilego and Glimmora
        */
        case SPECIES_GLIMMET:
            return TYPE_GROUND; //Earth Power
        
        //Rock/Grass
        case SPECIES_LILEEP: case SPECIES_CRADILY:
            return TYPE_POISON; //Sludge Bomb
        case SPECIES_OGERPON_CORNERSTONE:
            return TYPE_ROCK; //Added out of necessity but not applicable for Restricted Mode
        
        //Rock/Psychic
        /*Not included because of Tier Points: Iron Boulder
        */        
        case SPECIES_LUNATONE:
            return TYPE_FAIRY; //Moonblast
        case SPECIES_SOLROCK:
            return TYPE_FIRE; //Flare Blitz
        
        //Rock/Ice
        case SPECIES_AMAURA: case SPECIES_AURORUS:
            return TYPE_ELECTRIC; //Thunderbolt
        case SPECIES_AVALUGG_HISUI:
            return TYPE_ROCK;
        
        
        //Bug/Psychic
        case SPECIES_DOTTLER: case SPECIES_ORBEETLE:
            return TYPE_NORMAL; //Ghost immunity
        case SPECIES_RABSCA:
            return TYPE_FIRE; 
        
        //Ghost/Flying
        case SPECIES_DRIFLOON: case SPECIES_DRIFBLIM:
            return TYPE_DRAGON; //Type Distribution purposes
        case SPECIES_ORICORIO_SENSU:
            return TYPE_FAIRY; //Same tera type for each Oricorio
        
        //ALl Steel/Flying mons exceed Tier Points

        //Fire/Ground
        case SPECIES_NUMEL: case SPECIES_CAMERUPT:
            return TYPE_WATER; //Just for type distributions 
        
        //Water/Ghost
        /*Not included because of Tier Points: Basculegion
        */
        case SPECIES_FRILLISH: case SPECIES_JELLICENT: 
            return TYPE_ICE; //Ice Beam
        
        //Water/Electric
        /*Not included because of Tier Points: Rotom-Wash
        */
        case SPECIES_CHINCHOU: case SPECIES_LANTURN:
            return TYPE_BUG; //Signal Beam
        
        //Grass/Ground
        /*Not included because of Tier Points: Torterra
        */
        case SPECIES_TOEDSCOOL: case SPECIES_TOEDSCRUEL:
            return TYPE_POISON;
        
        //Grass/Steel
        /*Not included because of Tier Points: Ferrothorn, Kartana
        */
        case SPECIES_FERROSEED:
            return TYPE_DARK;
        
        //Electric/Fighting
        /*Not included because of Tier Points: Pawmot, Iron Hands
        */
        case SPECIES_PAWMO:
            return TYPE_GROUND;

        //Electric/Grass
        case SPECIES_ROTOM_MOW:
            return TYPE_GHOST;
        case SPECIES_VOLTORB_HISUI: case SPECIES_ELECTRODE_HISUI:
            return TYPE_BUG; //Signal Beam

        //Ice/Ground
        case SPECIES_SWINUB: case SPECIES_PILOSWINE: case SPECIES_MAMOSWINE:
            return TYPE_FLYING; //Thick Fat inversion - Fire becomes resisted and Ice becomes neutral 
        
        //Dragon/Fighting
        /*Not included because of Tier Points: Kommo-o
        */
        case SPECIES_HAKAMO_O:
            return TYPE_DARK;
        
        //All Dragon/Psychic mons are above Tier Points

        //Dark/Steel
        /*Not included because of Tier Points: Bisharp, Kingambit
        */
        case SPECIES_PAWNIARD:
            return TYPE_FIGHTING;
        
        //Dark/Psychic
        /*Not included because of Tier Points: Hoopa-Unbound
        */
        case SPECIES_INKAY: case SPECIES_MALAMAR:
            return TYPE_WATER; //Liquidation
        
        //Dark/Ice
        /*Not included because of Tier Points: Weavile and Chien-Pao
        */
        case SPECIES_SNEASEL:
            return TYPE_GHOST; //Shadow Claw

        //Dark/Fairy
        case SPECIES_IMPIDIMP: case SPECIES_MORGREM: case SPECIES_GRIMMSNARL:
            return TYPE_BUG;
        
        //Normal/Ground
        /*Not included because of Tier Points: Ursaluna
        */
        case SPECIES_DIGGERSBY:
            return TYPE_FIGHTING; //Superpower; note, only applicable when it doesn't have Huge Power in Restricted Mode

        //Normal/Ghost
        /*Not included because of Tier Points: Zoroark-Hisui
        */
        case SPECIES_ZORUA_HISUI:
            return TYPE_GHOST;

        //Normal/Dragon
        /*Not included because of Tier Points: Cyclizar
        */
        case SPECIES_DRAMPA:
            return TYPE_FIRE; //Flamethrower

        //All Fighting/Ghost mons exceed Tier Points

        //Poison/Normal
        case SPECIES_SHROODLE: case SPECIES_GRAFAIAI:
            return TYPE_FLYING; //Acrobatics
        
        //Poison/Fairy
        /*Not included because of Tier Points: Fezandipiti
        */
        case SPECIES_WEEZING_GALAR:
            return TYPE_ROCK; 

        //Ground/Electric
        /*Not included because of Tier Points: Sandy Shocks
        */
        case SPECIES_STUNFISK:
            return TYPE_STEEL;
        
        //Ground/Psychic
        case SPECIES_BALTOY: case SPECIES_CLAYDOL:
            return TYPE_ELECTRIC; //Levitate synergy
        
        //All Rock/Fighting mons exceed Tier Points

        //Rock/Dragon
        case SPECIES_TYRUNT: case SPECIES_TYRANTRUM:
            return TYPE_POISON; //Tera Poison Poison Fang Strong Jaw
        
        //Rock/Fairy
        /*Not included because of Tier Points: Diancie
        */
        case SPECIES_CARBINK:
            return TYPE_FAIRY; //Power Boost

        //Bug/Ground
        case SPECIES_NINCADA:
            return TYPE_GHOST;
        case SPECIES_WORMADAM_SANDY:
            return TYPE_ROCK;

        //Bug/Fairy
        case SPECIES_CUTIEFLY: case SPECIES_RIBOMBEE:
            return TYPE_PSYCHIC; //Psychic move

        //All Ghost/Fairy mons exceed Tier Points

        //Steel/Poison
        case SPECIES_VAROOM: case SPECIES_REVAVROOM:
            return TYPE_GROUND; //High Horsepower

        //Normal/Fire
        case SPECIES_LITLEO: case SPECIES_PYROAR:
            return TYPE_FLYING; //Acrobatics for Moxie lines
        
        //Grass/Fire
        case SPECIES_SCOVILLAIN:
            return TYPE_DRAGON; 
        case SPECIES_OGERPON_HEARTHFLAME:
            return TYPE_FIRE; //Added for necessity but not available for Restricted Mode

        //Grass/Ice
        case SPECIES_SNOVER: case SPECIES_ABOMASNOW:
            return TYPE_DRAGON; //Outrage
        
        //Electric/Normal
        case SPECIES_HELIOPTILE: case SPECIES_HELIOLISK:
            return TYPE_WATER; //Surf

        //Electric/Poison
        case SPECIES_TOXEL:
            return TYPE_STELLAR;
        case SPECIES_TOXTRICITY_AMPED: case SPECIES_TOXTRICITY_LOW_KEY:
            return TYPE_NORMAL; //Boomburst
        
        //Electric/Ice
        case SPECIES_ROTOM_FROST:
            return TYPE_GHOST;
        case SPECIES_ARCTOZOLT:
            return TYPE_ROCK; //Rock Slide and Meteor Beam

        //Electric/Fairy
        /*Not included because of Tier Points: Tapu Koko
        */
        case SPECIES_DEDENNE:
            return TYPE_GHOST;
        
        //Ice/Flying
        case SPECIES_ARTICUNO:
            return TYPE_ROCK; //Ancient Power and weakness Inversion
        case SPECIES_DELIBIRD:
            return TYPE_STELLAR; //Coverage machine
        
        //Ice/Bug
        case SPECIES_SNOM: case SPECIES_FROSMOTH:
            return TYPE_FLYING; //Air Slash
        
        //Ice/Steel
        case SPECIES_SANDSHREW_ALOLA: case SPECIES_SANDSLASH_ALOLA:
            return TYPE_FIGHTING;
        
        //Dark/Ghost
        case SPECIES_SABLEYE:
            return TYPE_STEEL; //Gyro Ball
        case SPECIES_SPIRITOMB:
            return TYPE_GHOST; //Power Boost
        
        //Normal/Water
        case SPECIES_BIBAREL:
            return TYPE_GROUND; //Dig
        
        //Ice/Fighting
        case SPECIES_CRABOMINABLE:
            return TYPE_WATER; //Crabhammer
        
        //All Ground/Fighting mons exceed tier points

        //All Rock/Dark mons exceed tier points

        //All Bug/Ghost mons exceed tier points

        //All Bug/Dark mons exceed tier points

        //All Fire/Steel mons exceed tier points

        //All Fire/Water mons exceed tier points

        //All Water/Steel mons exceed tier points

        //Electric/Ghost
        case SPECIES_ROTOM:
            return TYPE_ELECTRIC; //Power boost

        //Electric/Fire
        case SPECIES_ROTOM_HEAT:
            return TYPE_GHOST;
        
        //Electric/Psychic
        case SPECIES_RAICHU_ALOLA:
            return TYPE_FAIRY; 
        
        //Electric/Dark
        case SPECIES_MORPEKO: case SPECIES_MORPEKO_HANGRY:
            return TYPE_STELLAR; //Boosting both moves
        
        //Ice/Ghost
        case SPECIES_FROSLASS:
            return TYPE_NORMAL; 
        
        //All Ice/Fire mons exceed tier points

        //Ice/Fairy
        case SPECIES_NINETALES_ALOLA:
            return TYPE_POISON;

        //Dragon/Fairy mons are mega-only

        //All Fairy/Fighting mons exceed tier points
        default:
            return randomTeraType;
    }
}

/* GameFreak called GetBoxMonData with either 2 or 3 arguments, for type
 * safety we have a GetBoxMonData macro (in include/pokemon.h) which
 * dispatches to either GetBoxMonData2 or GetBoxMonData3 based on the
 * number of arguments. */
u32 GetBoxMonData3(struct BoxPokemon *boxMon, s32 field, u8 *data)
{
    s32 i;
    u32 retVal = 0;
    struct PokemonSubstruct0 *substruct0 = NULL;
    struct PokemonSubstruct1 *substruct1 = NULL;
    struct PokemonSubstruct2 *substruct2 = NULL;
    struct PokemonSubstruct3 *substruct3 = NULL;
    union EvolutionTracker evoTracker;

    // Any field greater than MON_DATA_ENCRYPT_SEPARATOR is encrypted and must be treated as such
    if (field > MON_DATA_ENCRYPT_SEPARATOR)
    {
        substruct0 = &(GetSubstruct(boxMon, boxMon->personality, 0)->type0);
        substruct1 = &(GetSubstruct(boxMon, boxMon->personality, 1)->type1);
        substruct2 = &(GetSubstruct(boxMon, boxMon->personality, 2)->type2);
        substruct3 = &(GetSubstruct(boxMon, boxMon->personality, 3)->type3);

        DecryptBoxMon(boxMon);

        if (CalculateBoxMonChecksum(boxMon) != boxMon->checksum)
        {
            boxMon->isBadEgg = TRUE;
            boxMon->isEgg = TRUE;
            substruct3->isEgg = TRUE;
        }

        switch (field)
        {
        case MON_DATA_NICKNAME:
        case MON_DATA_NICKNAME10:
        {
            if (boxMon->isBadEgg)
            {
                for (retVal = 0;
                    retVal < POKEMON_NAME_LENGTH && gText_BadEgg[retVal] != EOS;
                    data[retVal] = gText_BadEgg[retVal], retVal++) {}

                data[retVal] = EOS;
            }
            else if (boxMon->isEgg)
            {
                StringCopy(data, gText_EggNickname);
                retVal = StringLength(data);
            }
            else if (boxMon->language == LANGUAGE_JAPANESE)
            {
                data[0] = EXT_CTRL_CODE_BEGIN;
                data[1] = EXT_CTRL_CODE_JPN;

                for (retVal = 2, i = 0;
                    i < 5 && boxMon->nickname[i] != EOS;
                    data[retVal] = boxMon->nickname[i], retVal++, i++) {}

                data[retVal++] = EXT_CTRL_CODE_BEGIN;
                data[retVal++] = EXT_CTRL_CODE_ENG;
                data[retVal] = EOS;
            }
            else
            {
                retVal = 0;
                while (retVal < min(sizeof(boxMon->nickname), POKEMON_NAME_LENGTH))
                {
                    data[retVal] = boxMon->nickname[retVal];
                    retVal++;
                }

                // Vanilla Pokémon have 0s in nickname11 and nickname12
                // so if both are 0 we assume that this is a vanilla
                // Pokémon and replace them with EOS. This means that
                // two CHAR_SPACE at the end of a nickname are trimmed.
                if (field != MON_DATA_NICKNAME10 && POKEMON_NAME_LENGTH >= 12)
                {
                    if (substruct0->nickname11 == 0 && substruct0->nickname12 == 0)
                    {
                        data[retVal++] = EOS;
                        data[retVal++] = EOS;
                    }
                    else
                    {
                        data[retVal++] = substruct0->nickname11;
                        data[retVal++] = substruct0->nickname12;
                    }
                }
                else if (POKEMON_NAME_LENGTH >= 11)
                {
                    if (substruct0->nickname11 == 0)
                    {
                        data[retVal++] = EOS;
                    }
                    else
                    {
                        data[retVal++] = substruct0->nickname11;
                    }
                }

                data[retVal] = EOS;
            }
            break;
        }
        case MON_DATA_SPECIES:
            retVal = boxMon->isBadEgg ? SPECIES_EGG : substruct0->species;
            break;
        case MON_DATA_HELD_ITEM:
            retVal = substruct0->heldItem;
            break;
        case MON_DATA_EXP:
            retVal = substruct0->experience;
            break;
        case MON_DATA_PP_BONUSES:
            retVal = substruct0->ppBonuses;
            break;
        case MON_DATA_FRIENDSHIP:
            retVal = substruct0->friendship;
            break;
        case MON_DATA_MOVE1:
            retVal = substruct1->move1;
            break;
        case MON_DATA_MOVE2:
            retVal = substruct1->move2;
            break;
        case MON_DATA_MOVE3:
            retVal = substruct1->move3;
            break;
        case MON_DATA_MOVE4:
            retVal = substruct1->move4;
            break;
        case MON_DATA_PP1:
            retVal = substruct1->pp1;
            break;
        case MON_DATA_PP2:
            retVal = substruct1->pp2;
            break;
        case MON_DATA_PP3:
            retVal = substruct1->pp3;
            break;
        case MON_DATA_PP4:
            retVal = substruct1->pp4;
            break;
        case MON_DATA_HP_EV:
            retVal = substruct2->hpEV;
            break;
        case MON_DATA_ATK_EV:
            retVal = substruct2->attackEV;
            break;
        case MON_DATA_DEF_EV:
            retVal = substruct2->defenseEV;
            break;
        case MON_DATA_SPEED_EV:
            retVal = substruct2->speedEV;
            break;
        case MON_DATA_SPATK_EV:
            retVal = substruct2->spAttackEV;
            break;
        case MON_DATA_SPDEF_EV:
            retVal = substruct2->spDefenseEV;
            break;
        case MON_DATA_COOL:
            retVal = substruct2->cool;
            break;
        case MON_DATA_BEAUTY:
            retVal = substruct2->beauty;
            break;
        case MON_DATA_CUTE:
            retVal = substruct2->cute;
            break;
        case MON_DATA_SMART:
            retVal = substruct2->smart;
            break;
        case MON_DATA_TOUGH:
            retVal = substruct2->tough;
            break;
        case MON_DATA_SHEEN:
            retVal = substruct2->sheen;
            break;
        case MON_DATA_POKERUS:
            retVal = substruct3->pokerus;
            break;
        case MON_DATA_MET_LOCATION:
            retVal = substruct3->metLocation;
            break;
        case MON_DATA_MET_LEVEL:
            retVal = substruct3->metLevel;
            break;
        case MON_DATA_MET_GAME:
            retVal = substruct3->metGame;
            break;
        case MON_DATA_POKEBALL:
            retVal = substruct0->pokeball;
            break;
        case MON_DATA_OT_GENDER:
            retVal = substruct3->otGender;
            break;
        case MON_DATA_HP_IV:
            retVal = substruct3->hpIV;
            break;
        case MON_DATA_ATK_IV:
            retVal = substruct3->attackIV;
            break;
        case MON_DATA_DEF_IV:
            retVal = substruct3->defenseIV;
            break;
        case MON_DATA_SPEED_IV:
            retVal = substruct3->speedIV;
            break;
        case MON_DATA_SPATK_IV:
            retVal = substruct3->spAttackIV;
            break;
        case MON_DATA_SPDEF_IV:
            retVal = substruct3->spDefenseIV;
            break;
        case MON_DATA_IS_EGG:
            retVal = substruct3->isEgg;
            break;
        case MON_DATA_ABILITY_NUM:
            retVal = substruct3->abilityNum;
            break;
        case MON_DATA_COOL_RIBBON:
            retVal = substruct3->coolRibbon;
            break;
        case MON_DATA_BEAUTY_RIBBON:
            retVal = substruct3->beautyRibbon;
            break;
        case MON_DATA_CUTE_RIBBON:
            retVal = substruct3->cuteRibbon;
            break;
        case MON_DATA_SMART_RIBBON:
            retVal = substruct3->smartRibbon;
            break;
        case MON_DATA_TOUGH_RIBBON:
            retVal = substruct3->toughRibbon;
            break;
        case MON_DATA_CHAMPION_RIBBON:
            retVal = substruct3->championRibbon;
            break;
        case MON_DATA_WINNING_RIBBON:
            retVal = substruct3->winningRibbon;
            break;
        case MON_DATA_VICTORY_RIBBON:
            retVal = substruct3->victoryRibbon;
            break;
        case MON_DATA_ARTIST_RIBBON:
            retVal = substruct3->artistRibbon;
            break;
        case MON_DATA_EFFORT_RIBBON:
            retVal = substruct3->effortRibbon;
            break;
        case MON_DATA_MARINE_RIBBON:
            retVal = substruct3->marineRibbon;
            break;
        case MON_DATA_LAND_RIBBON:
            retVal = substruct3->landRibbon;
            break;
        case MON_DATA_SKY_RIBBON:
            retVal = substruct3->skyRibbon;
            break;
        case MON_DATA_COUNTRY_RIBBON:
            retVal = substruct3->countryRibbon;
            break;
        case MON_DATA_NATIONAL_RIBBON:
            retVal = substruct3->nationalRibbon;
            break;
        case MON_DATA_EARTH_RIBBON:
            retVal = substruct3->earthRibbon;
            break;
        case MON_DATA_WORLD_RIBBON:
            retVal = substruct3->worldRibbon;
            break;
        case MON_DATA_MODERN_FATEFUL_ENCOUNTER:
            retVal = substruct3->modernFatefulEncounter;
            break;
        case MON_DATA_SPECIES_OR_EGG:
            retVal = substruct0->species;
            if (substruct0->species && (substruct3->isEgg || boxMon->isBadEgg))
                retVal = SPECIES_EGG;
            break;
        case MON_DATA_IVS:
            retVal = substruct3->hpIV
                    | (substruct3->attackIV << 5)
                    | (substruct3->defenseIV << 10)
                    | (substruct3->speedIV << 15)
                    | (substruct3->spAttackIV << 20)
                    | (substruct3->spDefenseIV << 25);
            break;
        case MON_DATA_KNOWN_MOVES:
            if (substruct0->species && !substruct3->isEgg)
            {
                u16 *moves = (u16 *)data;
                s32 i = 0;

                while (moves[i] != MOVES_COUNT)
                {
                    u16 move = moves[i];
                    if (substruct1->move1 == move
                        || substruct1->move2 == move
                        || substruct1->move3 == move
                        || substruct1->move4 == move)
                        retVal |= (1u << i);
                    i++;
                }
            }
            break;
        case MON_DATA_RIBBON_COUNT:
            retVal = 0;
            if (substruct0->species && !substruct3->isEgg)
            {
                retVal += substruct3->coolRibbon;
                retVal += substruct3->beautyRibbon;
                retVal += substruct3->cuteRibbon;
                retVal += substruct3->smartRibbon;
                retVal += substruct3->toughRibbon;
                retVal += substruct3->championRibbon;
                retVal += substruct3->winningRibbon;
                retVal += substruct3->victoryRibbon;
                retVal += substruct3->artistRibbon;
                retVal += substruct3->effortRibbon;
                retVal += substruct3->marineRibbon;
                retVal += substruct3->landRibbon;
                retVal += substruct3->skyRibbon;
                retVal += substruct3->countryRibbon;
                retVal += substruct3->nationalRibbon;
                retVal += substruct3->earthRibbon;
                retVal += substruct3->worldRibbon;
            }
            break;
        case MON_DATA_RIBBONS:
            retVal = 0;
            if (substruct0->species && !substruct3->isEgg)
            {
                retVal = substruct3->championRibbon
                    | (substruct3->coolRibbon << 1)
                    | (substruct3->beautyRibbon << 4)
                    | (substruct3->cuteRibbon << 7)
                    | (substruct3->smartRibbon << 10)
                    | (substruct3->toughRibbon << 13)
                    | (substruct3->winningRibbon << 16)
                    | (substruct3->victoryRibbon << 17)
                    | (substruct3->artistRibbon << 18)
                    | (substruct3->effortRibbon << 19)
                    | (substruct3->marineRibbon << 20)
                    | (substruct3->landRibbon << 21)
                    | (substruct3->skyRibbon << 22)
                    | (substruct3->countryRibbon << 23)
                    | (substruct3->nationalRibbon << 24)
                    | (substruct3->earthRibbon << 25)
                    | (substruct3->worldRibbon << 26);
            }
            break;
        case MON_DATA_HYPER_TRAINED_HP:
            retVal = substruct1->hyperTrainedHP;
            break;
        case MON_DATA_HYPER_TRAINED_ATK:
            retVal = substruct1->hyperTrainedAttack;
            break;
        case MON_DATA_HYPER_TRAINED_DEF:
            retVal = substruct1->hyperTrainedDefense;
            break;
        case MON_DATA_HYPER_TRAINED_SPEED:
            retVal = substruct1->hyperTrainedSpeed;
            break;
        case MON_DATA_HYPER_TRAINED_SPATK:
            retVal = substruct1->hyperTrainedSpAttack;
            break;
        case MON_DATA_HYPER_TRAINED_SPDEF:
            retVal = substruct1->hyperTrainedSpDefense;
            break;
        case MON_DATA_IS_SHADOW:
            retVal = substruct3->isShadow;
            break;
        case MON_DATA_DYNAMAX_LEVEL:
            retVal = substruct3->dynamaxLevel;
            break;
        case MON_DATA_GIGANTAMAX_FACTOR:
            retVal = substruct3->gigantamaxFactor;
            break;
        case MON_DATA_TERA_TYPE:
            if (gSpeciesInfo[substruct0->species].forceTeraType)
            {
                retVal = gSpeciesInfo[substruct0->species].forceTeraType;
            }
            else if (substruct0->teraType == TYPE_NONE) // Tera Type hasn't been modified so we can just use the personality
            {
                retVal = getCuratedOrRandomTeraType(substruct0->species, boxMon->personality);
                // const u8 *types = gSpeciesInfo[substruct0->species].types;
                //retVal = (boxMon->personality & 0x1) == 0 ? types[0] : types[1];
            }
            else
            {
                retVal = substruct0->teraType;
            }
            break;
        case MON_DATA_EVOLUTION_TRACKER:
            evoTracker.asField.a = substruct1->evolutionTracker1;
            evoTracker.asField.b = substruct1->evolutionTracker2;
            evoTracker.asField.unused = 0;
            retVal = evoTracker.value;
            break;
        default:
            break;
        }
    }
    else
    {
        switch (field)
        {
        case MON_DATA_STATUS:
            retVal = UncompressStatus(boxMon->compressedStatus);
            break;
        case MON_DATA_HP_LOST:
            retVal = boxMon->hpLost;
            break;
        case MON_DATA_PERSONALITY:
            retVal = boxMon->personality;
            break;
        case MON_DATA_OT_ID:
            retVal = boxMon->otId;
            break;
        case MON_DATA_LANGUAGE:
            retVal = boxMon->language;
            break;
        case MON_DATA_SANITY_IS_BAD_EGG:
            retVal = boxMon->isBadEgg;
            break;
        case MON_DATA_SANITY_HAS_SPECIES:
            retVal = boxMon->hasSpecies;
            break;
        case MON_DATA_SANITY_IS_EGG:
            retVal = boxMon->isEgg;
            break;
        case MON_DATA_OT_NAME:
        {
            retVal = 0;

            while (retVal < PLAYER_NAME_LENGTH)
            {
                data[retVal] = boxMon->otName[retVal];
                retVal++;
            }

            data[retVal] = EOS;
            break;
        }
        case MON_DATA_MARKINGS:
            retVal = boxMon->markings;
            break;
        case MON_DATA_CHECKSUM:
            retVal = boxMon->checksum;
            break;
        case MON_DATA_IS_SHINY:
        {
            u32 shinyValue = GET_SHINY_VALUE(boxMon->otId, boxMon->personality);
            retVal = (shinyValue < SHINY_ODDS) ^ boxMon->shinyModifier;
            break;
        }
        case MON_DATA_HIDDEN_NATURE:
        {
            u32 nature = GetNatureFromPersonality(boxMon->personality);
            retVal = nature ^ boxMon->hiddenNatureModifier;
            break;
        }
        case MON_DATA_DAYS_SINCE_FORM_CHANGE:
            retVal = boxMon->daysSinceFormChange;
            break;
        default:
            break;
        }
    }

    if (field > MON_DATA_ENCRYPT_SEPARATOR)
        EncryptBoxMon(boxMon);

    return retVal;
}

u32 GetBoxMonData2(struct BoxPokemon *boxMon, s32 field)
{
    return GetBoxMonData3(boxMon, field, NULL);
}

#define SET8(lhs) (lhs) = *data
#define SET16(lhs) (lhs) = data[0] + (data[1] << 8)
#define SET32(lhs) (lhs) = data[0] + (data[1] << 8) + (data[2] << 16) + (data[3] << 24)

void SetMonData(struct Pokemon *mon, s32 field, const void *dataArg)
{
    const u8 *data = dataArg;

    switch (field)
    {
    case MON_DATA_STATUS:
        SET32(mon->status);
        SetBoxMonData(&mon->box, MON_DATA_STATUS, dataArg);
        break;
    case MON_DATA_LEVEL:
        SET8(mon->level);
        break;
    case MON_DATA_HP:
    {
        u32 hpLost;
        SET16(mon->hp);
        hpLost = mon->maxHP - mon->hp;
        SetBoxMonData(&mon->box, MON_DATA_HP_LOST, &hpLost);
        break;
    }
    case MON_DATA_HP_LOST:
    {
        u32 hpLost;
        SET16(hpLost);
        mon->hp = mon->maxHP - hpLost;
        SetBoxMonData(&mon->box, MON_DATA_HP_LOST, &hpLost);
        break;
    }
    case MON_DATA_MAX_HP:
        SET16(mon->maxHP);
        break;
    case MON_DATA_ATK:
        SET16(mon->attack);
        break;
    case MON_DATA_DEF:
        SET16(mon->defense);
        break;
    case MON_DATA_SPEED:
        SET16(mon->speed);
        break;
    case MON_DATA_SPATK:
        SET16(mon->spAttack);
        break;
    case MON_DATA_SPDEF:
        SET16(mon->spDefense);
        break;
    case MON_DATA_MAIL:
        SET8(mon->mail);
        break;
    case MON_DATA_SPECIES_OR_EGG:
        break;
    default:
        SetBoxMonData(&mon->box, field, data);
        break;
    }
}

void SetBoxMonData(struct BoxPokemon *boxMon, s32 field, const void *dataArg)
{
    const u8 *data = dataArg;

    struct PokemonSubstruct0 *substruct0 = NULL;
    struct PokemonSubstruct1 *substruct1 = NULL;
    struct PokemonSubstruct2 *substruct2 = NULL;
    struct PokemonSubstruct3 *substruct3 = NULL;

    if (field > MON_DATA_ENCRYPT_SEPARATOR)
    {
        substruct0 = &(GetSubstruct(boxMon, boxMon->personality, 0)->type0);
        substruct1 = &(GetSubstruct(boxMon, boxMon->personality, 1)->type1);
        substruct2 = &(GetSubstruct(boxMon, boxMon->personality, 2)->type2);
        substruct3 = &(GetSubstruct(boxMon, boxMon->personality, 3)->type3);

        DecryptBoxMon(boxMon);

        if (CalculateBoxMonChecksum(boxMon) != boxMon->checksum)
        {
            boxMon->isBadEgg = TRUE;
            boxMon->isEgg = TRUE;
            substruct3->isEgg = TRUE;
            EncryptBoxMon(boxMon);
            return;
        }

        switch (field)
        {
        case MON_DATA_NICKNAME:
        case MON_DATA_NICKNAME10:
        {
            s32 i;
            for (i = 0; i < min(sizeof(boxMon->nickname), POKEMON_NAME_LENGTH); i++)
                boxMon->nickname[i] = data[i];
            if (field != MON_DATA_NICKNAME10)
            {
                if (POKEMON_NAME_LENGTH >= 11)
                    substruct0->nickname11 = data[10];
                if (POKEMON_NAME_LENGTH >= 12)
                    substruct0->nickname12 = data[11];
            }
            else
            {
                substruct0->nickname11 = EOS;
                substruct0->nickname12 = EOS;
            }
            break;
        }
        case MON_DATA_SPECIES:
        {
            SET16(substruct0->species);
            if (substruct0->species)
                boxMon->hasSpecies = TRUE;
            else
                boxMon->hasSpecies = FALSE;
            break;
        }
        case MON_DATA_HELD_ITEM:
            SET16(substruct0->heldItem);
            break;
        case MON_DATA_EXP:
            SET32(substruct0->experience);
            break;
        case MON_DATA_PP_BONUSES:
            SET8(substruct0->ppBonuses);
            break;
        case MON_DATA_FRIENDSHIP:
            SET8(substruct0->friendship);
            break;
        case MON_DATA_MOVE1:
            SET16(substruct1->move1);
            break;
        case MON_DATA_MOVE2:
            SET16(substruct1->move2);
            break;
        case MON_DATA_MOVE3:
            SET16(substruct1->move3);
            break;
        case MON_DATA_MOVE4:
            SET16(substruct1->move4);
            break;
        case MON_DATA_PP1:
            SET8(substruct1->pp1);
            break;
        case MON_DATA_PP2:
            SET8(substruct1->pp2);
            break;
        case MON_DATA_PP3:
            SET8(substruct1->pp3);
            break;
        case MON_DATA_PP4:
            SET8(substruct1->pp4);
            break;
        case MON_DATA_HP_EV:
            SET8(substruct2->hpEV);
            break;
        case MON_DATA_ATK_EV:
            SET8(substruct2->attackEV);
            break;
        case MON_DATA_DEF_EV:
            SET8(substruct2->defenseEV);
            break;
        case MON_DATA_SPEED_EV:
            SET8(substruct2->speedEV);
            break;
        case MON_DATA_SPATK_EV:
            SET8(substruct2->spAttackEV);
            break;
        case MON_DATA_SPDEF_EV:
            SET8(substruct2->spDefenseEV);
            break;
        case MON_DATA_COOL:
            SET8(substruct2->cool);
            break;
        case MON_DATA_BEAUTY:
            SET8(substruct2->beauty);
            break;
        case MON_DATA_CUTE:
            SET8(substruct2->cute);
            break;
        case MON_DATA_SMART:
            SET8(substruct2->smart);
            break;
        case MON_DATA_TOUGH:
            SET8(substruct2->tough);
            break;
        case MON_DATA_SHEEN:
            SET8(substruct2->sheen);
            break;
        case MON_DATA_POKERUS:
            SET8(substruct3->pokerus);
            break;
        case MON_DATA_MET_LOCATION:
            SET8(substruct3->metLocation);
            break;
        case MON_DATA_MET_LEVEL:
            SET8(substruct3->metLevel);
            break;
        case MON_DATA_MET_GAME:
            SET8(substruct3->metGame);
            break;
        case MON_DATA_POKEBALL:
            SET8(substruct0->pokeball);
            break;
        case MON_DATA_OT_GENDER:
            SET8(substruct3->otGender);
            break;
        case MON_DATA_HP_IV:
            SET8(substruct3->hpIV);
            break;
        case MON_DATA_ATK_IV:
            SET8(substruct3->attackIV);
            break;
        case MON_DATA_DEF_IV:
            SET8(substruct3->defenseIV);
            break;
        case MON_DATA_SPEED_IV:
            SET8(substruct3->speedIV);
            break;
        case MON_DATA_SPATK_IV:
            SET8(substruct3->spAttackIV);
            break;
        case MON_DATA_SPDEF_IV:
            SET8(substruct3->spDefenseIV);
            break;
        case MON_DATA_IS_EGG:
            SET8(substruct3->isEgg);
            if (substruct3->isEgg)
                boxMon->isEgg = TRUE;
            else
                boxMon->isEgg = FALSE;
            break;
        case MON_DATA_ABILITY_NUM:
            SET8(substruct3->abilityNum);
            break;
        case MON_DATA_COOL_RIBBON:
            SET8(substruct3->coolRibbon);
            break;
        case MON_DATA_BEAUTY_RIBBON:
            SET8(substruct3->beautyRibbon);
            break;
        case MON_DATA_CUTE_RIBBON:
            SET8(substruct3->cuteRibbon);
            break;
        case MON_DATA_SMART_RIBBON:
            SET8(substruct3->smartRibbon);
            break;
        case MON_DATA_TOUGH_RIBBON:
            SET8(substruct3->toughRibbon);
            break;
        case MON_DATA_CHAMPION_RIBBON:
            SET8(substruct3->championRibbon);
            break;
        case MON_DATA_WINNING_RIBBON:
            SET8(substruct3->winningRibbon);
            break;
        case MON_DATA_VICTORY_RIBBON:
            SET8(substruct3->victoryRibbon);
            break;
        case MON_DATA_ARTIST_RIBBON:
            SET8(substruct3->artistRibbon);
            break;
        case MON_DATA_EFFORT_RIBBON:
            SET8(substruct3->effortRibbon);
            break;
        case MON_DATA_MARINE_RIBBON:
            SET8(substruct3->marineRibbon);
            break;
        case MON_DATA_LAND_RIBBON:
            SET8(substruct3->landRibbon);
            break;
        case MON_DATA_SKY_RIBBON:
            SET8(substruct3->skyRibbon);
            break;
        case MON_DATA_COUNTRY_RIBBON:
            SET8(substruct3->countryRibbon);
            break;
        case MON_DATA_NATIONAL_RIBBON:
            SET8(substruct3->nationalRibbon);
            break;
        case MON_DATA_EARTH_RIBBON:
            SET8(substruct3->earthRibbon);
            break;
        case MON_DATA_WORLD_RIBBON:
            SET8(substruct3->worldRibbon);
            break;
        case MON_DATA_MODERN_FATEFUL_ENCOUNTER:
            SET8(substruct3->modernFatefulEncounter);
            break;
        case MON_DATA_IVS:
        {
            u32 ivs;
            SET32(ivs);
            substruct3->hpIV = ivs & MAX_IV_MASK;
            substruct3->attackIV = (ivs >> 5) & MAX_IV_MASK;
            substruct3->defenseIV = (ivs >> 10) & MAX_IV_MASK;
            substruct3->speedIV = (ivs >> 15) & MAX_IV_MASK;
            substruct3->spAttackIV = (ivs >> 20) & MAX_IV_MASK;
            substruct3->spDefenseIV = (ivs >> 25) & MAX_IV_MASK;
            break;
        }
        case MON_DATA_HYPER_TRAINED_HP:
            SET8(substruct1->hyperTrainedHP);
            break;
        case MON_DATA_HYPER_TRAINED_ATK:
            SET8(substruct1->hyperTrainedAttack);
            break;
        case MON_DATA_HYPER_TRAINED_DEF:
            SET8(substruct1->hyperTrainedDefense);
            break;
        case MON_DATA_HYPER_TRAINED_SPEED:
            SET8(substruct1->hyperTrainedSpeed);
            break;
        case MON_DATA_HYPER_TRAINED_SPATK:
            SET8(substruct1->hyperTrainedSpAttack);
            break;
        case MON_DATA_HYPER_TRAINED_SPDEF:
            SET8(substruct1->hyperTrainedSpDefense);
            break;
        case MON_DATA_IS_SHADOW:
            SET8(substruct3->isShadow);
            break;
        case MON_DATA_DYNAMAX_LEVEL:
            SET8(substruct3->dynamaxLevel);
            break;
        case MON_DATA_GIGANTAMAX_FACTOR:
            SET8(substruct3->gigantamaxFactor);
            break;
        case MON_DATA_TERA_TYPE:
            SET8(substruct0->teraType);
            break;
        case MON_DATA_EVOLUTION_TRACKER:
        {
            union EvolutionTracker evoTracker;
            u32 evoTrackerValue;
            SET32(evoTrackerValue);
            evoTracker.value = evoTrackerValue;
            substruct1->evolutionTracker1 = evoTracker.asField.a;
            substruct1->evolutionTracker2 = evoTracker.asField.b;
            break;
        }
        default:
            break;
        }
    }
    else
    {
        switch (field)
        {
        case MON_DATA_STATUS:
        {
            u32 status;
            SET32(status);
            boxMon->compressedStatus = CompressStatus(status);
            break;
        }
        case MON_DATA_HP_LOST:
            SET16(boxMon->hpLost);
            break;
        case MON_DATA_PERSONALITY:
            SET32(boxMon->personality);
            break;
        case MON_DATA_OT_ID:
            SET32(boxMon->otId);
            break;
        case MON_DATA_LANGUAGE:
            SET8(boxMon->language);
            break;
        case MON_DATA_SANITY_IS_BAD_EGG:
            SET8(boxMon->isBadEgg);
            break;
        case MON_DATA_SANITY_HAS_SPECIES:
            SET8(boxMon->hasSpecies);
            break;
        case MON_DATA_SANITY_IS_EGG:
            SET8(boxMon->isEgg);
            break;
        case MON_DATA_OT_NAME:
        {
            s32 i;
            for (i = 0; i < PLAYER_NAME_LENGTH; i++)
                boxMon->otName[i] = data[i];
            break;
        }
        case MON_DATA_MARKINGS:
            SET8(boxMon->markings);
            break;
        case MON_DATA_CHECKSUM:
            SET16(boxMon->checksum);
            break;
        case MON_DATA_IS_SHINY:
        {
            u32 shinyValue = GET_SHINY_VALUE(boxMon->otId, boxMon->personality);
            bool32 isShiny;
            SET8(isShiny);
            boxMon->shinyModifier = (shinyValue < SHINY_ODDS) ^ isShiny;
            break;
        }
        case MON_DATA_HIDDEN_NATURE:
        {
            u32 nature = GetNatureFromPersonality(boxMon->personality);
            u32 hiddenNature;
            SET8(hiddenNature);
            boxMon->hiddenNatureModifier = nature ^ hiddenNature;
            break;
        }
        case MON_DATA_DAYS_SINCE_FORM_CHANGE:
            SET8(boxMon->daysSinceFormChange);
            break;
        }
    }

    if (field > MON_DATA_ENCRYPT_SEPARATOR)
    {
        boxMon->checksum = CalculateBoxMonChecksum(boxMon);
        EncryptBoxMon(boxMon);
    }
}

void CopyMon(void *dest, void *src, size_t size)
{
    memcpy(dest, src, size);
}

u8 GiveMonToPlayer(struct Pokemon *mon)
{
    s32 i;

    SetMonData(mon, MON_DATA_OT_NAME, gSaveBlock2Ptr->playerName);
    SetMonData(mon, MON_DATA_OT_GENDER, &gSaveBlock2Ptr->playerGender);
    SetMonData(mon, MON_DATA_OT_ID, gSaveBlock2Ptr->playerTrainerId);

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL) == SPECIES_NONE)
            break;
    }

    if (i >= PARTY_SIZE)
        return CopyMonToPC(mon);

    //Case for giving a mon when it exceeds points
    if (i < PARTY_SIZE && FlagGet(FLAG_TIERED)){
        gExcessTierPoints = 0; //Reset excess Tier Points before computing.
        u32 tierPoints = CountPartyTierPoints();
        tierPoints += GetMonTierPoints(GetMonData(mon, MON_DATA_SPECIES));
        if (tierPoints > TIER_POINTS_CAP){
            gExcessTierPoints = tierPoints - TIER_POINTS_CAP;
            return CopyMonToPC(mon);
        }
    }

    CopyMon(&gPlayerParty[i], mon, sizeof(*mon));
    gPlayerPartyCount = i + 1;
    return MON_GIVEN_TO_PARTY;
}

bool8 DepositPartyMonToPC_Auto(u8 partyId)
{
    s32 boxNo, boxPos;

    SetPCBoxToSendMon(VarGet(VAR_PC_BOX_TO_SEND_MON));
    boxNo = StorageGetCurrentBox();

    do {
        for (boxPos = 0; boxPos < IN_BOX_COUNT; boxPos++) {
            struct BoxPokemon *slot = GetBoxedMonPtr(boxNo, boxPos);
            if (GetBoxMonData(slot, MON_DATA_SPECIES, NULL) == SPECIES_NONE) {
                CopyMon(slot, &gPlayerParty[partyId].box, sizeof(gPlayerParty[partyId].box));

                // Move all slots after the boxed mon back by 1 slot
                for (u8 i = partyId; i + 1 < gPlayerPartyCount; i++)
                    CopyMon(&gPlayerParty[i], &gPlayerParty[i + 1], sizeof(struct Pokemon));
                ZeroMonData(&gPlayerParty[--gPlayerPartyCount]);

                gSpecialVar_MonBoxId  = boxNo;
                gSpecialVar_MonBoxPos = boxPos;

                if (GetPCBoxToSendMon() != boxNo)
                    FlagClear(FLAG_SHOWN_BOX_WAS_FULL_MESSAGE);
                VarSet(VAR_PC_BOX_TO_SEND_MON, boxNo);
                return TRUE;
            }
        }
        boxNo++;
        if (boxNo == TOTAL_BOXES_COUNT)
            boxNo = 0;
    } while (boxNo != StorageGetCurrentBox());

    return FALSE;
}

u8 CopyMonToPC(struct Pokemon *mon)
{
    s32 boxNo, boxPos;

    SetPCBoxToSendMon(VarGet(VAR_PC_BOX_TO_SEND_MON));

    boxNo = StorageGetCurrentBox();

    do
    {
        for (boxPos = 0; boxPos < IN_BOX_COUNT; boxPos++)
        {
            struct BoxPokemon *checkingMon = GetBoxedMonPtr(boxNo, boxPos);
            if (GetBoxMonData(checkingMon, MON_DATA_SPECIES, NULL) == SPECIES_NONE)
            {
                MonRestorePP(mon);
                CopyMon(checkingMon, &mon->box, sizeof(mon->box));
                gSpecialVar_MonBoxId = boxNo;
                gSpecialVar_MonBoxPos = boxPos;
                if (GetPCBoxToSendMon() != boxNo)
                    FlagClear(FLAG_SHOWN_BOX_WAS_FULL_MESSAGE);
                VarSet(VAR_PC_BOX_TO_SEND_MON, boxNo);
                return MON_GIVEN_TO_PC;
            }
        }

        boxNo++;
        if (boxNo == TOTAL_BOXES_COUNT)
            boxNo = 0;
    } while (boxNo != StorageGetCurrentBox());

    return MON_CANT_GIVE;
}

u8 CalculatePartyCount(struct Pokemon *party)
{
    u32 partyCount = 0;

    while (partyCount < PARTY_SIZE
        && GetMonData(&party[partyCount], MON_DATA_SPECIES, NULL) != SPECIES_NONE)
    {
        partyCount++;
    }

    return partyCount;
}

u8 CalculatePartyCountOfSide(u32 battler, struct Pokemon *party)
{
    s32 partyCount, partySize;
    GetAIPartyIndexes(battler, &partyCount, &partySize);

    while (partyCount < partySize
        && GetMonData(&party[partyCount], MON_DATA_SPECIES, NULL) != SPECIES_NONE)
    {
        partyCount++;
    }

    return partyCount;
}

u8 CalculatePlayerPartyCount(void)
{
    gPlayerPartyCount = CalculatePartyCount(gPlayerParty);
    return gPlayerPartyCount;
}

u8 CalculateEnemyPartyCount(void)
{
    gEnemyPartyCount = CalculatePartyCount(gEnemyParty);
    return gEnemyPartyCount;
}

u8 CalculateEnemyPartyCountInSide(u32 battler)
{
    return CalculatePartyCountOfSide(battler, gEnemyParty);
}

u8 GetMonsStateToDoubles(void)
{
    s32 aliveCount = 0;
    s32 i;
    CalculatePlayerPartyCount();

    if (OW_DOUBLE_APPROACH_WITH_ONE_MON)
        return PLAYER_HAS_TWO_USABLE_MONS;

    if (gPlayerPartyCount == 1)
        return gPlayerPartyCount; // PLAYER_HAS_ONE_MON

    for (i = 0; i < gPlayerPartyCount; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_EGG
         && GetMonData(&gPlayerParty[i], MON_DATA_HP, NULL) != 0
         && GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG, NULL) != SPECIES_NONE)
            aliveCount++;
    }

    return (aliveCount > 1) ? PLAYER_HAS_TWO_USABLE_MONS : PLAYER_HAS_ONE_USABLE_MON;
}

u8 GetMonsStateToDoubles_2(void)
{
    s32 aliveCount = 0;
    s32 i;

    if (OW_DOUBLE_APPROACH_WITH_ONE_MON
     || FollowerNPCIsBattlePartner())
        return PLAYER_HAS_TWO_USABLE_MONS;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        u32 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES_OR_EGG, NULL);
        if (species != SPECIES_EGG && species != SPECIES_NONE
         && GetMonData(&gPlayerParty[i], MON_DATA_HP, NULL) != 0)
            aliveCount++;
    }

    if (aliveCount == 1)
        return PLAYER_HAS_ONE_MON; // may have more than one, but only one is alive

    return (aliveCount > 1) ? PLAYER_HAS_TWO_USABLE_MONS : PLAYER_HAS_ONE_USABLE_MON;
}

u16 GetAbilityBySpecies(u16 species, u8 abilityNum)
{
    int i;

    if (abilityNum < NUM_ABILITY_SLOTS)
        gLastUsedAbility = gSpeciesInfo[species].abilities[abilityNum];
    else
        gLastUsedAbility = ABILITY_NONE;

    if (abilityNum >= NUM_NORMAL_ABILITY_SLOTS) // if abilityNum is empty hidden ability, look for other hidden abilities
    {
        for (i = NUM_NORMAL_ABILITY_SLOTS; i < NUM_ABILITY_SLOTS && gLastUsedAbility == ABILITY_NONE; i++)
        {
            gLastUsedAbility = gSpeciesInfo[species].abilities[i];
        }
    }

    for (i = 0; i < NUM_ABILITY_SLOTS && gLastUsedAbility == ABILITY_NONE; i++) // look for any non-empty ability
    {
        gLastUsedAbility = gSpeciesInfo[species].abilities[i];
    }

    return gLastUsedAbility;
}

u16 GetMonAbility(struct Pokemon *mon)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    u8 abilityNum = GetMonData(mon, MON_DATA_ABILITY_NUM, NULL);
    return GetAbilityBySpecies(species, abilityNum);
}

void CreateSecretBaseEnemyParty(struct SecretBase *secretBaseRecord)
{
    s32 i, j;

    ZeroEnemyPartyMons();
    *gBattleResources->secretBase = *secretBaseRecord;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (gBattleResources->secretBase->party.species[i])
        {
            CreateMon(&gEnemyParty[i],
                gBattleResources->secretBase->party.species[i],
                gBattleResources->secretBase->party.levels[i],
                15,
                TRUE,
                gBattleResources->secretBase->party.personality[i],
                OT_ID_RANDOM_NO_SHINY,
                0);

            SetMonData(&gEnemyParty[i], MON_DATA_HELD_ITEM, &gBattleResources->secretBase->party.heldItems[i]);

            for (j = 0; j < NUM_STATS; j++)
                SetMonData(&gEnemyParty[i], MON_DATA_HP_EV + j, &gBattleResources->secretBase->party.EVs[i]);

            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                SetMonData(&gEnemyParty[i], MON_DATA_MOVE1 + j, &gBattleResources->secretBase->party.moves[i * MAX_MON_MOVES + j]);
                u32 pp = GetMovePP(gBattleResources->secretBase->party.moves[i * MAX_MON_MOVES + j]);
                SetMonData(&gEnemyParty[i], MON_DATA_PP1 + j, &pp);
            }
        }
    }
}

u8 GetSecretBaseTrainerPicIndex(void)
{
    u8 facilityClass = sSecretBaseFacilityClasses[gBattleResources->secretBase->gender][gBattleResources->secretBase->trainerId[0] % NUM_SECRET_BASE_CLASSES];
    return gFacilityClassToPicIndex[facilityClass];
}

u8 GetSecretBaseTrainerClass(void)
{
    u8 facilityClass = sSecretBaseFacilityClasses[gBattleResources->secretBase->gender][gBattleResources->secretBase->trainerId[0] % NUM_SECRET_BASE_CLASSES];
    return gFacilityClassToTrainerClass[facilityClass];
}

bool8 IsPlayerPartyAndPokemonStorageFull(void)
{
    s32 i;

    for (i = 0; i < PARTY_SIZE; i++)
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL) == SPECIES_NONE)
            return FALSE;

    return IsPokemonStorageFull();
}

bool8 IsPokemonStorageFull(void)
{
    s32 i, j;

    for (i = 0; i < TOTAL_BOXES_COUNT; i++)
        for (j = 0; j < IN_BOX_COUNT; j++)
            if (GetBoxMonDataAt(i, j, MON_DATA_SPECIES) == SPECIES_NONE)
                return FALSE;

    return TRUE;
}

const u8 *GetSpeciesName(u16 species)
{
    species = SanitizeSpeciesId(species);
    if (gSpeciesInfo[species].speciesName[0] == 0)
        return gSpeciesInfo[SPECIES_NONE].speciesName;
    return gSpeciesInfo[species].speciesName;
}

const u8 *GetSpeciesCategory(u16 species)
{
    species = SanitizeSpeciesId(species);
    if (gSpeciesInfo[species].categoryName[0] == 0)
        return gSpeciesInfo[SPECIES_NONE].categoryName;
    return gSpeciesInfo[species].categoryName;
}

const u8 *GetSpeciesPokedexDescription(u16 species)
{
    species = SanitizeSpeciesId(species);
    if (gSpeciesInfo[species].description == NULL)
        return gSpeciesInfo[SPECIES_NONE].description;
    return gSpeciesInfo[species].description;
}

u16 GetSpeciesHeight(u16 species)
{
    return gSpeciesInfo[SanitizeSpeciesId(species)].height;
}

u16 GetSpeciesWeight(u16 species)
{
    return gSpeciesInfo[SanitizeSpeciesId(species)].weight;
}

const struct LevelUpMove *GetSpeciesLevelUpLearnset(u16 species)
{
    const struct LevelUpMove *learnset = gSpeciesInfo[SanitizeSpeciesId(species)].levelUpLearnset;
    if (learnset == NULL)
        return gSpeciesInfo[SPECIES_NONE].levelUpLearnset;
    return learnset;
}

const u16 *GetSpeciesTeachableLearnset(u16 species)
{
    const u16 *learnset = gSpeciesInfo[SanitizeSpeciesId(species)].teachableLearnset;
    if (learnset == NULL)
        return gSpeciesInfo[SPECIES_NONE].teachableLearnset;
    return learnset;
}

const u16 *GetSpeciesEggMoves(u16 species)
{
    const u16 *learnset = gSpeciesInfo[SanitizeSpeciesId(species)].eggMoveLearnset;
    if (learnset == NULL)
        return gSpeciesInfo[SPECIES_NONE].eggMoveLearnset;
    return learnset;
}

const struct Evolution *GetSpeciesEvolutions(u16 species)
{
    const struct Evolution *evolutions = gSpeciesInfo[SanitizeSpeciesId(species)].evolutions;
    if (evolutions == NULL)
        return gSpeciesInfo[SPECIES_NONE].evolutions;
    return evolutions;
}

const u16 *GetSpeciesFormTable(u16 species)
{
    const u16 *formTable = gSpeciesInfo[SanitizeSpeciesId(species)].formSpeciesIdTable;
    if (formTable == NULL)
        return gSpeciesInfo[SPECIES_NONE].formSpeciesIdTable;
    return formTable;
}

const struct FormChange *GetSpeciesFormChanges(u16 species)
{
    const struct FormChange *formChanges = gSpeciesInfo[SanitizeSpeciesId(species)].formChangeTable;
    if (formChanges == NULL)
        return gSpeciesInfo[SPECIES_NONE].formChangeTable;
    return formChanges;
}

u8 CalculatePPWithBonus(u16 move, u8 ppBonuses, u8 moveIndex)
{
    u8 basePP = GetMovePP(move);
    return basePP + ((basePP * 20 * ((gPPUpGetMask[moveIndex] & ppBonuses) >> (2 * moveIndex))) / 100);
}

void RemoveMonPPBonus(struct Pokemon *mon, u8 moveIndex)
{
    u8 ppBonuses = GetMonData(mon, MON_DATA_PP_BONUSES, NULL);
    ppBonuses &= gPPUpClearMask[moveIndex];
    SetMonData(mon, MON_DATA_PP_BONUSES, &ppBonuses);
}

void RemoveBattleMonPPBonus(struct BattlePokemon *mon, u8 moveIndex)
{
    mon->ppBonuses &= gPPUpClearMask[moveIndex];
}

void PokemonToBattleMon(struct Pokemon *src, struct BattlePokemon *dst)
{
    s32 i;
    u8 nickname[POKEMON_NAME_BUFFER_SIZE];

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        dst->moves[i] = GetMonData(src, MON_DATA_MOVE1 + i, NULL);
        dst->pp[i] = GetMonData(src, MON_DATA_PP1 + i, NULL);
    }

    dst->species = GetMonData(src, MON_DATA_SPECIES, NULL);
    dst->item = GetMonData(src, MON_DATA_HELD_ITEM, NULL);
    dst->ppBonuses = GetMonData(src, MON_DATA_PP_BONUSES, NULL);
    dst->friendship = GetMonData(src, MON_DATA_FRIENDSHIP, NULL);
    dst->experience = GetMonData(src, MON_DATA_EXP, NULL);
    dst->hpIV = GetMonData(src, MON_DATA_HP_IV, NULL);
    dst->attackIV = GetMonData(src, MON_DATA_ATK_IV, NULL);
    dst->defenseIV = GetMonData(src, MON_DATA_DEF_IV, NULL);
    dst->speedIV = GetMonData(src, MON_DATA_SPEED_IV, NULL);
    dst->spAttackIV = GetMonData(src, MON_DATA_SPATK_IV, NULL);
    dst->spDefenseIV = GetMonData(src, MON_DATA_SPDEF_IV, NULL);
    dst->personality = GetMonData(src, MON_DATA_PERSONALITY, NULL);
    dst->status1 = GetMonData(src, MON_DATA_STATUS, NULL);
    dst->level = GetMonData(src, MON_DATA_LEVEL, NULL);
    dst->hp = GetMonData(src, MON_DATA_HP, NULL);
    dst->maxHP = GetMonData(src, MON_DATA_MAX_HP, NULL);
    dst->attack = GetMonData(src, MON_DATA_ATK, NULL);
    dst->defense = GetMonData(src, MON_DATA_DEF, NULL);
    dst->speed = GetMonData(src, MON_DATA_SPEED, NULL);
    dst->spAttack = GetMonData(src, MON_DATA_SPATK, NULL);
    dst->spDefense = GetMonData(src, MON_DATA_SPDEF, NULL);
    dst->abilityNum = GetMonData(src, MON_DATA_ABILITY_NUM, NULL);
    dst->otId = GetMonData(src, MON_DATA_OT_ID, NULL);
    dst->types[0] = gSpeciesInfo[dst->species].types[0];
    dst->types[1] = gSpeciesInfo[dst->species].types[1];
    dst->types[2] = TYPE_MYSTERY;
    dst->isShiny = IsMonShiny(src);
    dst->ability = GetAbilityBySpecies(dst->species, dst->abilityNum);
    GetMonData(src, MON_DATA_NICKNAME, nickname);
    StringCopy_Nickname(dst->nickname, nickname);
    GetMonData(src, MON_DATA_OT_NAME, dst->otName);

    for (i = 0; i < NUM_BATTLE_STATS; i++)
        dst->statStages[i] = DEFAULT_STAT_STAGE;

    dst->status2 = 0;
}

void CopyPartyMonToBattleData(u32 battler, u32 partyIndex)
{
    u32 side = GetBattlerSide(battler);
    struct Pokemon *party = GetSideParty(side);
    PokemonToBattleMon(&party[partyIndex], &gBattleMons[battler]);
    gBattleStruct->hpOnSwitchout[side] = gBattleMons[battler].hp;
    UpdateSentPokesToOpponentValue(battler);
    ClearTemporarySpeciesSpriteData(battler, FALSE, FALSE);
}

bool8 ExecuteTableBasedItemEffect(struct Pokemon *mon, u16 item, u8 partyIndex, u8 moveIndex)
{
    return PokemonUseItemEffects(mon, item, partyIndex, moveIndex, FALSE);
}

#define UPDATE_FRIENDSHIP_FROM_ITEM()                                                                   \
{                                                                                                       \
    if ((retVal == 0 || friendshipOnly) && !ShouldSkipFriendshipChange() && friendshipChange == 0)      \
    {                                                                                                   \
        friendshipChange = itemEffect[itemEffectParam];                                                 \
        friendship = GetMonData(mon, MON_DATA_FRIENDSHIP, NULL);                                        \
        if (friendshipChange > 0 && holdEffect == HOLD_EFFECT_FRIENDSHIP_UP)                            \
            friendship += 150 * friendshipChange / 100;                                                 \
        else                                                                                            \
            friendship += friendshipChange;                                                             \
        if (friendshipChange > 0)                                                                       \
        {                                                                                               \
            if (GetMonData(mon, MON_DATA_POKEBALL, NULL) == ITEM_LUXURY_BALL)                           \
                friendship++;                                                                           \
            if (GetMonData(mon, MON_DATA_MET_LOCATION, NULL) == GetCurrentRegionMapSectionId())         \
                friendship++;                                                                           \
        }                                                                                               \
        if (friendship < 0)                                                                             \
            friendship = 0;                                                                             \
        if (friendship > MAX_FRIENDSHIP)                                                                \
            friendship = MAX_FRIENDSHIP;                                                                \
        SetMonData(mon, MON_DATA_FRIENDSHIP, &friendship);                                              \
        retVal = FALSE;                                                                                 \
    }                                                                                                   \
}

// EXP candies store an index for this table in their holdEffectParam.
const u32 sExpCandyExperienceTable[] = {
    [EXP_100 - 1] = 100,
    [EXP_800 - 1] = 800,
    [EXP_3000 - 1] = 3000,
    [EXP_10000 - 1] = 10000,
    [EXP_30000 - 1] = 30000,
};


s32 GetEVStatCap(void){
    if (!FlagGet(FLAG_EV_MODE)){
        return 0;
    }
    if (FlagGet(FLAG_BADGE07_GET)){
        return 252;
    }else if (FlagGet(FLAG_BADGE06_GET)){
        return 228;
    }else if (FlagGet(FLAG_BADGE05_GET)){
        return 192;
    }else if (FlagGet(FLAG_BADGE04_GET)){
        return 156;
    }else if (FlagGet(FLAG_BADGE03_GET)){
        return 120;
    }else if (FlagGet(FLAG_BADGE02_GET)){
        return 84;
    }else if (FlagGet(FLAG_BADGE01_GET)){
        return 48;
    }else{
        return 36;
    }
}

//Returns True if the evolution is prevented by Restricted Mode conditions, False otherwise.
//This is mainly used for cases where an alternate message should be sent. 
//For things like friendship evos, those can be handled in the direct evolution logic.
bool32 DoesNotMeetRestrictedEvoItemConditions(struct Pokemon *mon, u16 item){    
    u8 level =  GetMonData(mon, MON_DATA_LEVEL, 0);
    u32 species = GetMonData(mon, MON_DATA_SPECIES);

    // DebugPrintf("DoesNotMeetRestrictedEvoConditions is called for species %d with level %d", species, level);
    
    if (!FlagGet(FLAG_RESTRICTED_MODE)){
        return FALSE; //Checks don't matter if not in Restricted Mode
    }

    switch (species){
        case SPECIES_SLOWPOKE: case SPECIES_SLOWBRO_GALAR:
        case SPECIES_KADABRA: case SPECIES_GRAVELER: case SPECIES_MACHOKE : case SPECIES_HAUNTER:
            if (level < 32) return TRUE;
            break;
        case SPECIES_NIDORINO : case SPECIES_NIDORINA:
            if (level < 25) return TRUE;
        default:
            return FALSE;
    }
    return FALSE;
}

// Returns TRUE if the item has no effect on the Pokémon, FALSE otherwise
bool8 PokemonUseItemEffects(struct Pokemon *mon, u16 item, u8 partyIndex, u8 moveIndex, bool8 usedByAI)
{
    u32 dataUnsigned;
    s32 dataSigned, evCap, maxEVs;
    s32 friendship;
    s32 i;
    bool8 retVal = TRUE;
    const u8 *itemEffect;
    u8 itemEffectParam = ITEM_EFFECT_ARG_START;
    u32 temp1, temp2;
    s8 friendshipChange = 0;
    u8 holdEffect;
    u8 battler = MAX_BATTLERS_COUNT;
    u32 friendshipOnly = FALSE;
    u16 heldItem;
    u8 effectFlags;
    s8 evChange;
    u16 evCount;

    evCap = GetEVStatCap();

    maxEVs = evCap == 0 ? 0 : evCap * 2 + 6;


    evCap = GetEVStatCap();

    maxEVs = evCap == 0 ? 0 : evCap * 2 + 6;

    // Get item hold effect
    heldItem = GetMonData(mon, MON_DATA_HELD_ITEM, NULL);
    if (heldItem == ITEM_ENIGMA_BERRY_E_READER)
    #if FREE_ENIGMA_BERRY == FALSE
        holdEffect = gSaveBlock1Ptr->enigmaBerry.holdEffect;
    #else
        holdEffect = 0;
    #endif //FREE_ENIGMA_BERRY
    else
        holdEffect = GetItemHoldEffect(heldItem);

    // Skip using the item if it won't do anything
    if (GetItemEffect(item) == NULL && item != ITEM_ENIGMA_BERRY_E_READER)
        return TRUE;

    // Get item effect
    itemEffect = GetItemEffect(item);

    // Do item effect
    for (i = 0; i < ITEM_EFFECT_ARG_START; i++)
    {
        switch (i)
        {

        // Handle ITEM0 effects (infatuation, Dire Hit, X Attack). ITEM0_SACRED_ASH is handled in party_menu.c
        // Now handled in item battle scripts.
        case 0:
            break;

        // Handle ITEM1 effects (in-battle stat boosting effects)
        // Now handled in item battle scripts.
        case 1:
            break;
        // Formerly used by the item effects of the X Sp. Atk and the X Accuracy
        case 2:
            break;

        // Handle ITEM3 effects (Guard Spec, Rare Candy, cure status)
        case 3:
            // Rare Candy / EXP Candy
            if ((itemEffect[i] & ITEM3_LEVEL_UP)
             && GetMonData(mon, MON_DATA_LEVEL, NULL) != MAX_LEVEL)
            {
                u8 param = GetItemHoldEffectParam(item);
                dataUnsigned = 0;

                if (param == 0) // Rare Candy
                {
                    dataUnsigned = gExperienceTables[gSpeciesInfo[GetMonData(mon, MON_DATA_SPECIES, NULL)].growthRate][GetMonData(mon, MON_DATA_LEVEL, NULL) + 1];
                }
                else if (param - 1 < ARRAY_COUNT(sExpCandyExperienceTable)) // EXP Candies
                {
                    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
                    dataUnsigned = sExpCandyExperienceTable[param - 1] + GetMonData(mon, MON_DATA_EXP, NULL);

                    // if (B_RARE_CANDY_CAP && B_EXP_CAP_TYPE == EXP_CAP_HARD)
                    if (FlagGet(FLAG_LEVEL_CAP))
                    {
                        u32 currentLevelCap = GetCurrentLevelCap(CANDY_CAP);
                        if (dataUnsigned > gExperienceTables[gSpeciesInfo[species].growthRate][currentLevelCap])
                            dataUnsigned = gExperienceTables[gSpeciesInfo[species].growthRate][currentLevelCap];
                    }
                    else if (dataUnsigned > gExperienceTables[gSpeciesInfo[species].growthRate][MAX_LEVEL])
                    {
                        dataUnsigned = gExperienceTables[gSpeciesInfo[species].growthRate][MAX_LEVEL];
                    }
                }

                if (dataUnsigned != 0) // Failsafe
                {
                    SetMonData(mon, MON_DATA_EXP, &dataUnsigned);
                    CalculateMonStats(mon);
                    retVal = FALSE;
                }
            }

            // Cure status
            if ((itemEffect[i] & ITEM3_SLEEP) && HealStatusConditions(mon, STATUS1_SLEEP, battler) == 0)
                retVal = FALSE;
            if ((itemEffect[i] & ITEM3_POISON) && HealStatusConditions(mon, STATUS1_PSN_ANY | STATUS1_TOXIC_COUNTER, battler) == 0)
                retVal = FALSE;
            if ((itemEffect[i] & ITEM3_BURN) && HealStatusConditions(mon, STATUS1_BURN, battler) == 0)
                retVal = FALSE;
            if ((itemEffect[i] & ITEM3_FREEZE) && HealStatusConditions(mon, STATUS1_FREEZE | STATUS1_FROSTBITE, battler) == 0)
                retVal = FALSE;
            if ((itemEffect[i] & ITEM3_PARALYSIS) && HealStatusConditions(mon, STATUS1_PARALYSIS, battler) == 0)
                retVal = FALSE;
            break;

        // Handle ITEM4 effects (Change HP/Atk EVs, HP heal, PP heal, PP up, Revive, and evolution stones)
        case 4:
            effectFlags = itemEffect[i];

            // PP Up
            if (effectFlags & ITEM4_PP_UP)
            {
                u32 ppBonuses = GetMonData(mon, MON_DATA_PP_BONUSES, NULL);
                effectFlags &= ~ITEM4_PP_UP;
                dataUnsigned = (ppBonuses & gPPUpGetMask[moveIndex]) >> (moveIndex * 2);
                temp1 = CalculatePPWithBonus(GetMonData(mon, MON_DATA_MOVE1 + moveIndex, NULL), ppBonuses, moveIndex);
                if (dataUnsigned <= 2 && temp1 > 4)
                {
                    dataUnsigned = ppBonuses + gPPUpAddValues[moveIndex];
                    SetMonData(mon, MON_DATA_PP_BONUSES, &dataUnsigned);

                    dataUnsigned = CalculatePPWithBonus(GetMonData(mon, MON_DATA_MOVE1 + moveIndex, NULL), dataUnsigned, moveIndex) - temp1;
                    dataUnsigned = GetMonData(mon, MON_DATA_PP1 + moveIndex, NULL) + dataUnsigned;
                    SetMonData(mon, MON_DATA_PP1 + moveIndex, &dataUnsigned);
                    retVal = FALSE;
                }
            }
            temp1 = 0;

            // Loop through and try each of the remaining ITEM4 effects
            while (effectFlags != 0)
            {
                if (effectFlags & 1)
                {
                    switch (temp1)
                    {
                    case 0: // ITEM4_EV_HP
                    case 1: // ITEM4_EV_ATK
                        evCount = GetMonEVCount(mon);
                        temp2 = itemEffect[itemEffectParam];
                        dataSigned = GetMonData(mon, sGetMonDataEVConstants[temp1], NULL);
                        evChange = temp2;

                        if (evChange > 0) // Increasing EV (HP or Atk)
                        {
                            // Has EV increase limit already been reached?
                            // Replace MAX_TOTAL_EVS with a version relative to the EV cap 
                            if (evCount >= maxEVs)
                                return TRUE;

                            // if (itemEffect[10] & ITEM10_IS_VITAMIN)
                            //     evCap = EV_ITEM_RAISE_LIMIT;
                            // else
                            //     evCap = MAX_PER_STAT_EVS;

                            if (dataSigned >= evCap)
                                return TRUE;  // Prevents item use if the per-stat cap is already reached

                            if (dataSigned + evChange > evCap)
                                temp2 = evCap - dataSigned;
                            else
                                temp2 = evChange;

                            if (evCount + temp2 > maxEVs)
                                temp2 = maxEVs - evCount;

                            // Prevent item use if no EVs can be increased
                            if (temp2 == 0)
                                return TRUE;

                            // Apply the EV increase
                            dataSigned += temp2;
                        }
                        else if (evChange < 0) // Decreasing EV (HP or Atk)
                        {
                            if (dataSigned == 0)
                            {
                                // No EVs to lose, but make sure friendship updates anyway
                                friendshipOnly = TRUE;
                                itemEffectParam++;
                                break;
                            }
                            dataSigned += evChange;
                            if (I_BERRY_EV_JUMP == GEN_4 && dataSigned > 100)
                                dataSigned = 100;
                            if (dataSigned < 0)
                                dataSigned = 0;
                        }
                        else // Reset EV (HP or Atk)
                        {
                            if (dataSigned == 0)
                                break;

                            dataSigned = 0;
                        }

                        // Update EVs and stats
                        SetMonData(mon, sGetMonDataEVConstants[temp1], &dataSigned);
                        CalculateMonStats(mon);
                        itemEffectParam++;
                        retVal = FALSE;
                        break;

                    case 2: // ITEM4_HEAL_HP
                    {
                        u32 currentHP = GetMonData(mon, MON_DATA_HP, NULL);
                        u32 maxHP = GetMonData(mon, MON_DATA_MAX_HP, NULL);
                        // Check use validity.
                        if ((effectFlags & (ITEM4_REVIVE >> 2) && currentHP != 0)
                              || (!(effectFlags & (ITEM4_REVIVE >> 2)) && currentHP == 0))
                        {
                            itemEffectParam++;
                            break;
                        }

                        // Get amount of HP to restore
                        dataUnsigned = itemEffect[itemEffectParam++];
                        switch (dataUnsigned)
                        {
                        case ITEM6_HEAL_HP_FULL:
                            dataUnsigned = maxHP - currentHP;
                            break;
                        case ITEM6_HEAL_HP_HALF:
                            dataUnsigned = maxHP / 2;
                            if (dataUnsigned == 0)
                                dataUnsigned = 1;
                            break;
                        case ITEM6_HEAL_HP_LVL_UP:
                            dataUnsigned = gBattleScripting.levelUpHP;
                            break;
                        case ITEM6_HEAL_HP_QUARTER:
                            dataUnsigned = maxHP / 4;
                            if (dataUnsigned == 0)
                                dataUnsigned = 1;
                            break;
                        }

                        // Only restore HP if not at max health
                        if (maxHP != currentHP)
                        {
                            // Restore HP
                            dataUnsigned = currentHP + dataUnsigned;
                            if (dataUnsigned > maxHP)
                                dataUnsigned = maxHP;
                            SetMonData(mon, MON_DATA_HP, &dataUnsigned);
                            retVal = FALSE;
                        }
                        effectFlags &= ~(ITEM4_REVIVE >> 2);
                        break;
                    }
                    case 3: // ITEM4_HEAL_PP
                        if (!(effectFlags & (ITEM4_HEAL_PP_ONE >> 3)))
                        {
                            // Heal PP for all moves
                            for (temp2 = 0; (signed)(temp2) < (signed)(MAX_MON_MOVES); temp2++)
                            {
                                u32 move, ppBonus;
                                dataUnsigned = GetMonData(mon, MON_DATA_PP1 + temp2, NULL);
                                move = GetMonData(mon, MON_DATA_MOVE1 + temp2, NULL);
                                ppBonus = CalculatePPWithBonus(move, GetMonData(mon, MON_DATA_PP_BONUSES, NULL), temp2);
                                if (dataUnsigned != ppBonus)
                                {
                                    dataUnsigned += itemEffect[itemEffectParam];
                                    if (dataUnsigned > ppBonus)
                                        dataUnsigned = ppBonus;
                                    SetMonData(mon, MON_DATA_PP1 + temp2, &dataUnsigned);
                                    retVal = FALSE;
                                }
                            }
                            itemEffectParam++;
                        }
                        else
                        {
                            // Heal PP for one move
                            u16 move;
                            dataUnsigned = GetMonData(mon, MON_DATA_PP1 + moveIndex, NULL);
                            move = GetMonData(mon, MON_DATA_MOVE1 + moveIndex, NULL);
                            u32 ppBonus = CalculatePPWithBonus(move, GetMonData(mon, MON_DATA_PP_BONUSES, NULL), moveIndex);
                            if (dataUnsigned != ppBonus)
                            {
                                dataUnsigned += itemEffect[itemEffectParam++];
                                if (dataUnsigned > ppBonus)
                                    dataUnsigned = ppBonus;
                                SetMonData(mon, MON_DATA_PP1 + moveIndex, &dataUnsigned);
                                retVal = FALSE;
                            }
                        }
                        break;

                    // cases 4-6 are ITEM4_HEAL_PP_ONE, ITEM4_PP_UP, and ITEM4_REVIVE, which
                    // are already handled above by other cases or before the loop

                    case 7: // ITEM4_EVO_STONE
                        {
                            bool32 canStopEvo = TRUE;
                            u32 targetSpecies = GetEvolutionTargetSpecies(mon, EVO_MODE_ITEM_USE, item, NULL, &canStopEvo, CHECK_EVO);

                            if (targetSpecies != SPECIES_NONE && !DoesNotMeetRestrictedEvoItemConditions(mon, item))
                            {
                                GetEvolutionTargetSpecies(mon, EVO_MODE_ITEM_USE, item, NULL, &canStopEvo, DO_EVO);
                                BeginEvolutionScene(mon, targetSpecies, canStopEvo, partyIndex);
                                return FALSE;
                            }
                        }
                        break;
                    }
                }
                temp1++;
                effectFlags >>= 1;
            }
            break;

        // Handle ITEM5 effects (Change Def/SpDef/SpAtk/Speed EVs, PP Max, and friendship changes)
        case 5:
            effectFlags = itemEffect[i];
            temp1 = 0;

            // Loop through and try each of the ITEM5 effects
            while (effectFlags != 0)
            {
                if (effectFlags & 1)
                {
                    switch (temp1)
                    {
                    case 0: // ITEM5_EV_DEF
                    case 1: // ITEM5_EV_SPEED
                    case 2: // ITEM5_EV_SPDEF
                    case 3: // ITEM5_EV_SPATK
                        evCount = GetMonEVCount(mon);
                        temp2 = itemEffect[itemEffectParam];
                        dataSigned = GetMonData(mon, sGetMonDataEVConstants[temp1 + 2], NULL);
                        evChange = temp2;
                        if (evChange > 0) // Increasing EV
                        {
                            // Has EV increase limit already been reached?
                            if (evCount >= maxEVs)
                                return TRUE;

                            // if (itemEffect[10] & ITEM10_IS_VITAMIN)
                            //     evCap = EV_ITEM_RAISE_LIMIT;
                            // else
                            //     evCap = MAX_PER_STAT_EVS;

                            if (dataSigned >= evCap)
                                return TRUE;  // Prevents item use if the per-stat cap is already reached

                            if (dataSigned + evChange > evCap)
                                temp2 = evCap - dataSigned;
                            else
                                temp2 = evChange;

                            if (evCount + temp2 > maxEVs)
                                temp2 = maxEVs - evCount;

                            // Prevent item use if no EVs can be increased
                            if (temp2 == 0)
                                return TRUE;

                            // Apply the EV increase
                            dataSigned += temp2;
                        }
                        else if (evChange < 0) // Decreasing EV
                        {
                            if (dataSigned == 0)
                            {
                                // No EVs to lose, but make sure friendship updates anyway
                                friendshipOnly = TRUE;
                                itemEffectParam++;
                                break;
                            }
                            dataSigned += evChange;
                            if (I_BERRY_EV_JUMP == GEN_4 && dataSigned > 100)
                                dataSigned = 100;
                            if (dataSigned < 0)
                                dataSigned = 0;
                        }
                        else // Reset EV
                        {
                            if (dataSigned == 0)
                                break;

                            dataSigned = 0;
                        }

                        // Update EVs and stats
                        SetMonData(mon, sGetMonDataEVConstants[temp1 + 2], &dataSigned);
                        CalculateMonStats(mon);
                        retVal = FALSE;
                        itemEffectParam++;
                        break;

                    case 4: // ITEM5_PP_MAX
                    {
                        u32 ppBonuses = GetMonData(mon, MON_DATA_PP_BONUSES, NULL);
                        dataUnsigned = (ppBonuses & gPPUpGetMask[moveIndex]) >> (moveIndex * 2);
                        temp2 = CalculatePPWithBonus(GetMonData(mon, MON_DATA_MOVE1 + moveIndex, NULL), ppBonuses, moveIndex);

                        // Check if 3 PP Ups have been applied already, and that the move has a total PP of at least 5 (excludes Sketch)
                        if (dataUnsigned < 3 && temp2 >= 5)
                        {
                            dataUnsigned = ppBonuses;
                            dataUnsigned &= gPPUpClearMask[moveIndex];
                            dataUnsigned += gPPUpAddValues[moveIndex] * 3; // Apply 3 PP Ups (max)

                            SetMonData(mon, MON_DATA_PP_BONUSES, &dataUnsigned);
                            dataUnsigned = CalculatePPWithBonus(GetMonData(mon, MON_DATA_MOVE1 + moveIndex, NULL), dataUnsigned, moveIndex) - temp2;
                            dataUnsigned = GetMonData(mon, MON_DATA_PP1 + moveIndex, NULL) + dataUnsigned;
                            SetMonData(mon, MON_DATA_PP1 + moveIndex, &dataUnsigned);
                            retVal = FALSE;
                        }
                        break;
                    }
                    case 5: // ITEM5_FRIENDSHIP_LOW
                        // Changes to friendship are given differently depending on
                        // how much friendship the Pokémon already has.
                        // In general, Pokémon with lower friendship receive more,
                        // and Pokémon with higher friendship receive less.
                        if (GetMonData(mon, MON_DATA_FRIENDSHIP, NULL) < 100)
                            UPDATE_FRIENDSHIP_FROM_ITEM();
                        itemEffectParam++;
                        break;

                    case 6: // ITEM5_FRIENDSHIP_MID
                        if (GetMonData(mon, MON_DATA_FRIENDSHIP, NULL) >= 100 && GetMonData(mon, MON_DATA_FRIENDSHIP, NULL) < 200)
                            UPDATE_FRIENDSHIP_FROM_ITEM();
                        itemEffectParam++;
                        break;

                    case 7: // ITEM5_FRIENDSHIP_HIGH
                        if (GetMonData(mon, MON_DATA_FRIENDSHIP, NULL) >= 200)
                            UPDATE_FRIENDSHIP_FROM_ITEM();
                        itemEffectParam++;
                        break;
                    }
                }
                temp1++;
                effectFlags >>= 1;
            }
            break;
        }
    }
    return retVal;
}

bool8 HealStatusConditions(struct Pokemon *mon, u32 healMask, u8 battler)
{
    u32 status = GetMonData(mon, MON_DATA_STATUS, 0);

    if (status & healMask)
    {
        status &= ~healMask;
        SetMonData(mon, MON_DATA_STATUS, &status);
        if (gMain.inBattle && battler != MAX_BATTLERS_COUNT)
        {
            gBattleMons[battler].status1 &= ~healMask;
            if((healMask & STATUS1_SLEEP))
            {
                u32 i = 0;
                u32 battlerSide = GetBattlerSide(battler);
                struct Pokemon *party = GetSideParty(battlerSide);

                for (i = 0; i < PARTY_SIZE; i++)
                {
                    if (&party[i] == mon)
                    {
                        TryDeactivateSleepClause(battlerSide, i);
                        break;
                    }
                }
            }
        }
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

u8 GetItemEffectParamOffset(u32 battler, u16 itemId, u8 effectByte, u8 effectBit)
{
    const u8 *temp;
    const u8 *itemEffect;
    u8 offset;
    int i;
    u8 j;
    u8 effectFlags;

    offset = ITEM_EFFECT_ARG_START;

    temp = GetItemEffect(itemId);

    if (temp != NULL && !temp && itemId != ITEM_ENIGMA_BERRY_E_READER)
        return 0;

    if (itemId == ITEM_ENIGMA_BERRY_E_READER)
    {
        temp = gEnigmaBerries[battler].itemEffect;
    }

    itemEffect = temp;

    for (i = 0; i < ITEM_EFFECT_ARG_START; i++)
    {
        switch (i)
        {
        case 0:
        case 1:
        case 2:
        case 3:
            if (i == effectByte)
                return 0;
            break;
        case 4:
            effectFlags = itemEffect[4];
            if (effectFlags & ITEM4_PP_UP)
                effectFlags &= ~(ITEM4_PP_UP);
            j = 0;
            while (effectFlags)
            {
                if (effectFlags & 1)
                {
                    switch (j)
                    {
                    case 2: // ITEM4_HEAL_HP
                        if (effectFlags & (ITEM4_REVIVE >> 2))
                            effectFlags &= ~(ITEM4_REVIVE >> 2);
                        // fallthrough
                    case 0: // ITEM4_EV_HP
                        if (i == effectByte && (effectFlags & effectBit))
                            return offset;
                        offset++;
                        break;
                    case 1: // ITEM4_EV_ATK
                        if (i == effectByte && (effectFlags & effectBit))
                            return offset;
                        offset++;
                        break;
                    case 3: // ITEM4_HEAL_PP
                        if (i == effectByte && (effectFlags & effectBit))
                            return offset;
                        offset++;
                        break;
                    case 7: // ITEM4_EVO_STONE
                        if (i == effectByte)
                            return 0;
                        break;
                    }
                }
                j++;
                effectFlags >>= 1;
                if (i == effectByte)
                    effectBit >>= 1;
            }
            break;
        case 5:
            effectFlags = itemEffect[5];
            j = 0;
            while (effectFlags)
            {
                if (effectFlags & 1)
                {
                    switch (j)
                    {
                    case 0: // ITEM5_EV_DEF
                    case 1: // ITEM5_EV_SPEED
                    case 2: // ITEM5_EV_SPDEF
                    case 3: // ITEM5_EV_SPATK
                    case 4: // ITEM5_PP_MAX
                    case 5: // ITEM5_FRIENDSHIP_LOW
                    case 6: // ITEM5_FRIENDSHIP_MID
                        if (i == effectByte && (effectFlags & effectBit))
                            return offset;
                        offset++;
                        break;
                    case 7: // ITEM5_FRIENDSHIP_HIGH
                        if (i == effectByte)
                            return 0;
                        break;
                    }
                }
                j++;
                effectFlags >>= 1;
                if (i == effectByte)
                    effectBit >>= 1;
            }
            break;
        }
    }

    return offset;
}

static void BufferStatRoseMessage(s32 statIdx)
{
    gBattlerTarget = gBattlerInMenuId;
    StringCopy(gBattleTextBuff1, gStatNamesTable[sStatsToRaise[statIdx]]);
    if (B_X_ITEMS_BUFF >= GEN_7)
    {
        StringCopy(gBattleTextBuff2, gText_StatSharply);
        StringAppend(gBattleTextBuff2, gText_StatRose);
    }
    else
    {
        StringCopy(gBattleTextBuff2, gText_StatRose);
    }
    BattleStringExpandPlaceholdersToDisplayedString(gText_DefendersStatRose);
}

u8 *UseStatIncreaseItem(u16 itemId)
{
    const u8 *itemEffect;

    if (itemId == ITEM_ENIGMA_BERRY_E_READER)
    {
        if (gMain.inBattle)
            itemEffect = gEnigmaBerries[gBattlerInMenuId].itemEffect;
        else
        #if FREE_ENIGMA_BERRY == FALSE
            itemEffect = gSaveBlock1Ptr->enigmaBerry.itemEffect;
        #else
            itemEffect = 0;
        #endif //FREE_ENIGMA_BERRY
    }
    else
    {
        itemEffect = GetItemEffect(itemId);
    }

    gPotentialItemEffectBattler = gBattlerInMenuId;

    if (itemEffect[0] & ITEM0_DIRE_HIT)
    {
        gBattlerAttacker = gBattlerInMenuId;
        BattleStringExpandPlaceholdersToDisplayedString(gText_PkmnGettingPumped);
    }

    switch (itemEffect[1])
    {
        case ITEM1_X_ATTACK:
            BufferStatRoseMessage(STAT_ATK);
            break;
        case ITEM1_X_DEFENSE:
            BufferStatRoseMessage(STAT_DEF);
            break;
        case ITEM1_X_SPEED:
            BufferStatRoseMessage(STAT_SPEED);
            break;
        case ITEM1_X_SPATK:
            BufferStatRoseMessage(STAT_SPATK);
            break;
        case ITEM1_X_SPDEF:
            BufferStatRoseMessage(STAT_SPDEF);
            break;
        case ITEM1_X_ACCURACY:
            BufferStatRoseMessage(STAT_ACC);
            break;
    }

    if (itemEffect[3] & ITEM3_GUARD_SPEC)
    {
        gBattlerAttacker = gBattlerInMenuId;
        BattleStringExpandPlaceholdersToDisplayedString(gText_PkmnShroudedInMist);
    }

    return gDisplayedStringBattle;
}

u8 GetNature(struct Pokemon *mon)
{
    return GetMonData(mon, MON_DATA_PERSONALITY, 0) % NUM_NATURES;
}

u8 GetNatureFromPersonality(u32 personality)
{
    return personality % NUM_NATURES;
}

u32 GetGMaxTargetSpecies(u32 species)
{
    const struct FormChange *formChanges = GetSpeciesFormChanges(species);
    u32 i;
    for (i = 0; formChanges != NULL && formChanges[i].method != FORM_CHANGE_TERMINATOR; i++)
    {
        if (formChanges[i].method == FORM_CHANGE_BATTLE_GIGANTAMAX)
            return formChanges[i].targetSpecies;
    }
    return species;
}

bool32 DoesMonMeetAdditionalConditions(struct Pokemon *mon, const struct EvolutionParam *params, struct Pokemon *tradePartner, u32 partyId, bool32 *canStopEvo, enum EvoState evoState)
{
    u32 i, j;
    u32 heldItem = GetMonData(mon, MON_DATA_HELD_ITEM);
    u32 gender = GetMonGender(mon);
    u32 friendship = GetMonData(mon, MON_DATA_FRIENDSHIP, 0);
    u32 attack = GetMonData(mon, MON_DATA_ATK, 0);
    u32 defense = GetMonData(mon, MON_DATA_DEF, 0);
    u32 personality = GetMonData(mon, MON_DATA_PERSONALITY, 0);
    u16 upperPersonality = personality >> 16;
    u32 weather = GetCurrentWeather();
    u32 nature = GetNature(mon);
    bool32 removeHoldItem = FALSE;
    u32 removeBagItem = ITEM_NONE;
    u32 removeBagItemCount = 0;
    u32 evolutionTracker = GetMonData(mon, MON_DATA_EVOLUTION_TRACKER, 0);
    u32 level = GetMonData(mon, MON_DATA_LEVEL, 0);
    u32 partnerSpecies, partnerHeldItem;
    enum ItemHoldEffect partnerHoldEffect;

    if (tradePartner != NULL)
    {
        partnerSpecies = GetMonData(tradePartner, MON_DATA_SPECIES, 0);
        partnerHeldItem = GetMonData(tradePartner, MON_DATA_HELD_ITEM, 0);

        if (partnerHeldItem == ITEM_ENIGMA_BERRY_E_READER)
        #if FREE_ENIGMA_BERRY == FALSE
            partnerHoldEffect = gSaveBlock1Ptr->enigmaBerry.holdEffect;
        #else
            partnerHoldEffect = 0;
        #endif //FREE_ENIGMA_BERRY
        else
            partnerHoldEffect = GetItemHoldEffect(partnerHeldItem);
    }
    else
    {
        partnerSpecies = SPECIES_NONE;
        partnerHeldItem = ITEM_NONE;
        partnerHoldEffect = HOLD_EFFECT_NONE;
    }

    // Check for additional conditions (only if the primary method passes). Skips if there's no additional conditions.
    for (i = 0; params != NULL && params[i].condition != CONDITIONS_END; i++)
    {
        enum EvolutionConditions condition = params[i].condition;
        u32 currentCondition = FALSE;

        switch(condition)
        {
        // Gen 2
        case IF_GENDER:
            if (gender == GetMonGender(mon))
                currentCondition = TRUE;
            break;
        case IF_MIN_FRIENDSHIP:
            if (friendship >= params[i].arg1)
                currentCondition = TRUE;
            break;
        case IF_ATK_GT_DEF:
            if (attack > defense)
                currentCondition = TRUE;
            break;
        case IF_ATK_EQ_DEF:
            if (attack == defense)
                currentCondition = TRUE;
            break;
        case IF_ATK_LT_DEF:
            if (attack < defense)
                currentCondition = TRUE;
            break;
        case IF_TIME:
            if (GetTimeOfDay() == params[i].arg1)
                currentCondition = TRUE;

            break;
        case IF_NOT_TIME:
            if (GetTimeOfDay() != params[i].arg1)
                currentCondition = TRUE;
            break;
        case IF_HOLD_ITEM:
            if (heldItem == params[i].arg1)
            {
                currentCondition = TRUE;
                removeHoldItem = TRUE;
            }
            break;
        // Gen 3
        case IF_PID_UPPER_MODULO_10_GT:
            if ((upperPersonality % 10) > params[i].arg1)
                currentCondition = TRUE;
            break;
        case IF_PID_UPPER_MODULO_10_EQ:
            if ((upperPersonality % 10) == params[i].arg1)
                currentCondition = TRUE;
            break;
        case IF_PID_UPPER_MODULO_10_LT:
            if ((upperPersonality % 10) < params[i].arg1)
                currentCondition = TRUE;
            break;
        case IF_MIN_BEAUTY:
        {
            u32 beauty = GetMonData(mon, MON_DATA_BEAUTY, 0);
            if (beauty >= params[i].arg1)
                currentCondition = TRUE;
            break;
        }
        case IF_MIN_COOLNESS:
        {
            u32 coolness = GetMonData(mon, MON_DATA_COOL, 0);
            if (coolness >= params[i].arg1)
                currentCondition = TRUE;
            break;
        }
        case IF_MIN_SMARTNESS:
        // remember that even though it's called "Smart/Smartness" here,
        // from gen 6 and up it's known as "Clever/Cleverness."
        {
            u32 smartness = GetMonData(mon, MON_DATA_SMART, 0);
            if (smartness >= params[i].arg1)
                currentCondition = TRUE;
            break;
        }
        case IF_MIN_TOUGHNESS:
        {
            u32 toughness = GetMonData(mon, MON_DATA_TOUGH, 0);
            if (toughness >= params[i].arg1)
                currentCondition = TRUE;
            break;
        }
        case IF_MIN_CUTENESS:
        {
            u32 cuteness = GetMonData(mon, MON_DATA_CUTE, 0);
            if (cuteness >= params[i].arg1)
                currentCondition = TRUE;
            break;
        }
        // Gen 4
        case IF_SPECIES_IN_PARTY:
            for (j = 0; j < PARTY_SIZE; j++)
            {
                if (GetMonData(&gPlayerParty[j], MON_DATA_SPECIES, NULL) == params[i].arg1)
                {
                    currentCondition = TRUE;
                    break;
                }
            }
            break;
        case IF_IN_MAP:
            if (params[i].arg1 == ((gSaveBlock1Ptr->location.mapGroup) << 8 | gSaveBlock1Ptr->location.mapNum))
                currentCondition = TRUE;
            break;
        case IF_IN_MAPSEC:
            if (gMapHeader.regionMapSectionId == params[i].arg1)
                currentCondition = TRUE;
            break;
        case IF_KNOWS_MOVE:
            if (MonKnowsMove(mon, params[i].arg1))
                currentCondition = TRUE;
            break;
        // Gen 5
        case IF_TRADE_PARTNER_SPECIES:
            if (params[i].arg1 == partnerSpecies && partnerHoldEffect != HOLD_EFFECT_PREVENT_EVOLVE)
                currentCondition = TRUE;
            break;
        // Gen 6
        case IF_TYPE_IN_PARTY:
            for (j = 0; j < PARTY_SIZE; j++)
            {
                u16 currSpecies = GetMonData(&gPlayerParty[j], MON_DATA_SPECIES, NULL);
                if (gSpeciesInfo[currSpecies].types[0] == params[i].arg1
                 || gSpeciesInfo[currSpecies].types[1] == params[i].arg1)
                {
                    currentCondition = TRUE;
                    break;
                }
            }
            break;
        case IF_WEATHER:
            if (params[i].arg1 == WEATHER_RAIN)
            {
                if (weather == WEATHER_RAIN || weather == WEATHER_RAIN_THUNDERSTORM || weather == WEATHER_DOWNPOUR)
                    currentCondition = TRUE;
            }
            else if (params[i].arg1 == WEATHER_FOG)
            {
                if (weather == WEATHER_FOG_DIAGONAL || weather == WEATHER_FOG_HORIZONTAL)
                    currentCondition = TRUE;
            }
            else if (weather == params[i].arg1)
            {
                currentCondition = TRUE;
            }
            break;
        case IF_KNOWS_MOVE_TYPE:
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                if (GetMoveType(GetMonData(mon, MON_DATA_MOVE1 + j, NULL)) == params[i].arg1)
                {
                    currentCondition = TRUE;
                    break;
                }
            }
            break;
        // Gen 8
        case IF_NATURE:
            if (nature == params[i].arg1)
                currentCondition = TRUE;
            break;
        case IF_AMPED_NATURE:
            switch (nature)
            {
            case NATURE_HARDY:
            case NATURE_BRAVE:
            case NATURE_ADAMANT:
            case NATURE_NAUGHTY:
            case NATURE_DOCILE:
            case NATURE_IMPISH:
            case NATURE_LAX:
            case NATURE_HASTY:
            case NATURE_JOLLY:
            case NATURE_NAIVE:
            case NATURE_RASH:
            case NATURE_SASSY:
            case NATURE_QUIRKY:
                currentCondition = TRUE;
                break;
            }
            break;
        case IF_LOW_KEY_NATURE:
            switch (nature)
            {
            case NATURE_LONELY:
            case NATURE_BOLD:
            case NATURE_RELAXED:
            case NATURE_TIMID:
            case NATURE_SERIOUS:
            case NATURE_MODEST:
            case NATURE_MILD:
            case NATURE_QUIET:
            case NATURE_BASHFUL:
            case NATURE_CALM:
            case NATURE_GENTLE:
            case NATURE_CAREFUL:
                currentCondition = TRUE;
                break;
            }
            break;
        case IF_RECOIL_DAMAGE_GE:
            if (evolutionTracker >= params[i].arg1)
                currentCondition = TRUE;
            break;
        case IF_CURRENT_DAMAGE_GE:
        {
            u32 currentHp = GetMonData(mon, MON_DATA_HP, NULL);
            if (currentHp != 0 && (GetMonData(mon, MON_DATA_MAX_HP, NULL) - currentHp >= params[i].arg1))
                currentCondition = TRUE;
            break;
        }
        case IF_CRITICAL_HITS_GE:
            if (partyId != PARTY_SIZE && gPartyCriticalHits[partyId] >= params[i].arg1)
                currentCondition = TRUE;
            break;
        case IF_USED_MOVE_X_TIMES:
            if (evolutionTracker >= params[i].arg2)
                currentCondition = TRUE;
            break;
        // Gen 9
        case IF_DEFEAT_X_WITH_ITEMS:
            if (evolutionTracker >= params[i].arg3)
                currentCondition = TRUE;
            break;
        case IF_PID_MODULO_100_GT:
            if ((personality % 100) > params[i].arg1)
                currentCondition = TRUE;
            break;
        case IF_PID_MODULO_100_EQ:
            if ((personality % 100) == params[i].arg1)
                currentCondition = TRUE;
            break;
        case IF_PID_MODULO_100_LT:
            if ((personality % 100) < params[i].arg1)
                currentCondition = TRUE;
            break;
        case IF_MIN_OVERWORLD_STEPS:
            if (mon == GetFirstLiveMon() && gFollowerSteps >= params[i].arg1)
                currentCondition = TRUE;
            break;
        case IF_BAG_ITEM_COUNT:
            if (CheckBagHasItem(params[i].arg1, params[i].arg2))
            {
                currentCondition = TRUE;
                removeBagItem = params[i].arg1;
                removeBagItemCount = params[i].arg2;
                if (canStopEvo != NULL)
                    *canStopEvo = FALSE;
            }
            break;
        
        //Elastic additional criteria
        case IF_MIN_RESTRICTED_LEVEL:
            if (!FlagGet(FLAG_RESTRICTED_MODE) || level >= params[i].arg1){
                currentCondition = TRUE;
            }
            break;
        case IF_MONOTYPE_MATCHES_ONE_OF_TWO_TYPES:
            if (GetMonoType() == TYPE_NONE || GetMonoType() == params[i].arg1 || GetMonoType() == params[i].arg2){
                currentCondition = TRUE;
            }
            break;
        case CONDITIONS_END:
            break;
        }

        // check if an evolution is about to happen and items should be removed
        if (evoState == DO_EVO)
        {
            if (removeHoldItem)
            {
                u32 heldItem = ITEM_NONE;
                SetMonData(mon, MON_DATA_HELD_ITEM, &heldItem);
            }

            if (removeBagItem != ITEM_NONE)
                RemoveBagItem(removeBagItem, removeBagItemCount);
        }

        if (currentCondition == FALSE)
            return FALSE;
    }

    return TRUE;
}

u32 GetEvolutionTargetSpecies(struct Pokemon *mon, enum EvolutionMode mode, u16 evolutionItem, struct Pokemon *tradePartner, bool32 *canStopEvo, enum EvoState evoState)
{
    int i;
    u32 targetSpecies = SPECIES_NONE;
    u32 species = GetMonData(mon, MON_DATA_SPECIES, 0);
    u32 heldItem = GetMonData(mon, MON_DATA_HELD_ITEM, 0);
    u32 level = GetMonData(mon, MON_DATA_LEVEL, 0);
    u32 holdEffect;
    const struct Evolution *evolutions = GetSpeciesEvolutions(species);

    if (evolutions == NULL)
        return SPECIES_NONE;

    if (heldItem == ITEM_ENIGMA_BERRY_E_READER)
    #if FREE_ENIGMA_BERRY == FALSE
        holdEffect = gSaveBlock1Ptr->enigmaBerry.holdEffect;
    #else
        holdEffect = 0;
    #endif //FREE_ENIGMA_BERRY
    else
        holdEffect = GetItemHoldEffect(heldItem);

    // Prevent evolution with Everstone, unless we're just viewing the party menu with an evolution item
    if (holdEffect == HOLD_EFFECT_PREVENT_EVOLVE
        && mode != EVO_MODE_ITEM_CHECK
        && (P_KADABRA_EVERSTONE < GEN_4 || species != SPECIES_KADABRA))
        return SPECIES_NONE;

    switch (mode)
    {
    case EVO_MODE_NORMAL:
    case EVO_MODE_BATTLE_ONLY:
        for (i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
        {
            bool32 conditionsMet = FALSE;
            if (SanitizeSpeciesId(evolutions[i].targetSpecies) == SPECIES_NONE)
                continue;

            // Check main primary evolution method
            switch (evolutions[i].method)
            {
            case EVO_LEVEL:
                if (evolutions[i].param <= level)
                    conditionsMet = TRUE;
                break;
            case EVO_LEVEL_BATTLE_ONLY:
                if (mode == EVO_MODE_BATTLE_ONLY && evolutions[i].param <= level)
                    conditionsMet = TRUE;
                break;
            }

            if (conditionsMet && DoesMonMeetAdditionalConditions(mon, evolutions[i].params, NULL, PARTY_SIZE, canStopEvo, evoState))
            {
                // All checks passed, so stop checking the rest of the evolutions.
                // This is different from vanilla where the loop continues.
                // If you have overlapping evolutions, put the ones you want to happen first on top of the list.
                targetSpecies = evolutions[i].targetSpecies;
                break;
            }
        }
        break;
    case EVO_MODE_TRADE:
        for (i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
        {
            bool32 conditionsMet = FALSE;
            if (SanitizeSpeciesId(evolutions[i].targetSpecies) == SPECIES_NONE)
                continue;

            switch (evolutions[i].method)
            {
            case EVO_TRADE:
                conditionsMet = TRUE;
                break;
            }

            if (conditionsMet && DoesMonMeetAdditionalConditions(mon, evolutions[i].params, tradePartner, PARTY_SIZE, canStopEvo, evoState))
            {
                // All checks passed, so stop checking the rest of the evolutions.
                // This is different from vanilla where the loop continues.
                // If you have overlapping evolutions, put the ones you want to happen first on top of the list.
                targetSpecies = evolutions[i].targetSpecies;
                break;
            }
        }
        break;
    case EVO_MODE_ITEM_USE:
    case EVO_MODE_ITEM_CHECK:
        for (i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
        {
            bool32 conditionMet = FALSE;
            if (SanitizeSpeciesId(evolutions[i].targetSpecies) == SPECIES_NONE)
                continue;

            switch (evolutions[i].method)
            {
            case EVO_ITEM:
                if (evolutions[i].param == evolutionItem)
                    conditionMet = TRUE;
                break;
            }

            if (conditionMet && DoesMonMeetAdditionalConditions(mon, evolutions[i].params, NULL, PARTY_SIZE, canStopEvo, evoState))
            {
                // All checks passed, so stop checking the rest of the evolutions.
                // This is different from vanilla where the loop continues.
                // If you have overlapping evolutions, put the ones you want to happen first on top of the list.
                targetSpecies = evolutions[i].targetSpecies;
                if (canStopEvo != NULL)
                    *canStopEvo = FALSE;
                break;
            }
        }
        break;
    // Battle evolution without leveling; party slot is being passed into the evolutionItem arg.
    case EVO_MODE_BATTLE_SPECIAL:
        for (i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
        {
            bool32 conditionsMet = FALSE;
            if (SanitizeSpeciesId(evolutions[i].targetSpecies) == SPECIES_NONE)
                continue;

            switch (evolutions[i].method)
            {
                case EVO_BATTLE_END:
                    conditionsMet = TRUE;
                    break;
            }

            if (conditionsMet && DoesMonMeetAdditionalConditions(mon, evolutions[i].params, NULL, evolutionItem, canStopEvo, evoState))
            {
                // All checks passed, so stop checking the rest of the evolutions.
                // This is different from vanilla where the loop continues.
                // If you have overlapping evolutions, put the ones you want to happen first on top of the list.
                targetSpecies = evolutions[i].targetSpecies;
                break;
            }
        }
        break;
    // Overworld evolution without leveling; evolution method is being passed into the evolutionItem arg.
    case EVO_MODE_OVERWORLD_SPECIAL:
        for (i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
        {
            bool32 conditionsMet = FALSE;
            if (SanitizeSpeciesId(evolutions[i].targetSpecies) == SPECIES_NONE)
                continue;

            switch (evolutions[i].method)
            {
            case EVO_SCRIPT_TRIGGER:
            case EVO_SPIN:
                if (gSpecialVar_0x8000 == evolutions[i].param)
                    conditionsMet = TRUE;

                break;
            }

            if (conditionsMet && DoesMonMeetAdditionalConditions(mon, evolutions[i].params, NULL, PARTY_SIZE, canStopEvo, evoState))
            {
                // All checks passed, so stop checking the rest of the evolutions.
                // This is different from vanilla where the loop continues.
                // If you have overlapping evolutions, put the ones you want to happen first on top of the list.
                targetSpecies = evolutions[i].targetSpecies;
                break;
            }
        }
        break;
    }

    // Pikachu, Meowth, Eevee and Duraludon cannot evolve if they have the
    // Gigantamax Factor. We assume that is because their evolutions
    // do not have a Gigantamax Form.
    if (GetMonData(mon, MON_DATA_GIGANTAMAX_FACTOR, NULL)
     && GetGMaxTargetSpecies(species) != species
     && GetGMaxTargetSpecies(targetSpecies) == targetSpecies)
    {
        return SPECIES_NONE;
    }

    return targetSpecies;
}

bool8 IsMonPastEvolutionLevel(struct Pokemon *mon)
{
    int i;
    u16 species = GetMonData(mon, MON_DATA_SPECIES, 0);
    u8 level = GetMonData(mon, MON_DATA_LEVEL, 0);
    const struct Evolution *evolutions = GetSpeciesEvolutions(species);

    if (evolutions == NULL)
        return FALSE;

    for (i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
    {
        if (SanitizeSpeciesId(evolutions[i].targetSpecies) == SPECIES_NONE)
            continue;

        switch (evolutions[i].method)
        {
        case EVO_LEVEL:
            if (evolutions[i].param <= level)
                return TRUE;
            break;
        }
    }

    return FALSE;
}

u16 NationalPokedexNumToSpecies(u16 nationalNum)
{
    u16 species;

    if (!nationalNum)
        return 0;

    species = 1;

    while (species < (NUM_SPECIES) && gSpeciesInfo[species].natDexNum != nationalNum)
        species++;

    if (species == NUM_SPECIES)
        return NATIONAL_DEX_NONE;

    return GET_BASE_SPECIES_ID(species);
}

u16 NationalToHoennOrder(u16 nationalNum)
{
    u16 hoennNum;

    if (!nationalNum)
        return 0;

    hoennNum = 0;

    while (hoennNum < (HOENN_DEX_COUNT - 1) && sHoennToNationalOrder[hoennNum] != nationalNum)
        hoennNum++;

    if (hoennNum >= HOENN_DEX_COUNT - 1)
        return 0;

    return hoennNum + 1;
}

u16 SpeciesToNationalPokedexNum(u16 species)
{
    species = SanitizeSpeciesId(species);
    if (!species)
        return NATIONAL_DEX_NONE;

    return gSpeciesInfo[species].natDexNum;
}

u16 SpeciesToHoennPokedexNum(u16 species)
{
    if (!species)
        return 0;
    return NationalToHoennOrder(gSpeciesInfo[species].natDexNum);
}

u16 HoennToNationalOrder(u16 hoennNum)
{
    if (!hoennNum || hoennNum >= HOENN_DEX_COUNT)
        return 0;

    return sHoennToNationalOrder[hoennNum - 1];
}

// Spots can be drawn on Spinda's color indexes 1, 2, or 3
#define FIRST_SPOT_COLOR 1
#define LAST_SPOT_COLOR  3

// To draw a spot pixel, add 4 to the color index
#define SPOT_COLOR_ADJUSTMENT 4
/*
    The function below handles drawing the randomly-placed spots on Spinda's front sprite.
    Spinda has 4 spots, each with an entry in gSpindaSpotGraphics. Each entry contains
    a base x and y coordinate for the spot and a 16x16 binary image. Each bit in the image
    determines whether that pixel should be considered part of the spot.

    The position of each spot is randomized using the Spinda's personality. The entire 32 bit
    personality value is used, 4 bits for each coordinate of the 4 spots. If the personality
    value is 0x87654321, then 0x1 will be used for the 1st spot's x coord, 0x2 will be used for
    the 1st spot's y coord, 0x3 will be used for the 2nd spot's x coord, and so on. Each
    coordinate is calculated as (baseCoord + (given 4 bits of personality) - 8). In effect this
    means each spot can start at any position -8 to +7 off of its base coordinates (256 possibilities).

    The function then loops over the 16x16 spot image. For each bit in the spot's binary image, if
    the bit is set then it's part of the spot; try to draw it. A pixel is drawn on Spinda if the
    pixel is between FIRST_SPOT_COLOR and LAST_SPOT_COLOR (so only colors 1, 2, or 3 on Spinda will
    allow a spot to be drawn). These color indexes are Spinda's light brown body colors. To create
    the spot it adds 4 to the color index, so Spinda's spots will be colors 5, 6, and 7.

    The above is done in TRY_DRAW_SPOT_PIXEL two different ways: one with << 4, and one without.
    This is because Spinda's sprite is a 4 bits per pixel image, but the pointer to Spinda's pixels
    (destPixels) is an 8 bit pointer, so it addresses two pixels. Shifting by 4 accesses the 2nd
    of these pixels, so this is done every other time.
*/

// Draw spot pixel if this is Spinda's body color
#define TRY_DRAW_SPOT_PIXEL(pixels, shift) \
    if (((*(pixels) & (0xF << (shift))) >= (FIRST_SPOT_COLOR << (shift))) \
     && ((*(pixels) & (0xF << (shift))) <= (LAST_SPOT_COLOR << (shift)))) \
    { \
        *(pixels) += (SPOT_COLOR_ADJUSTMENT << (shift)); \
    }


void DrawSpindaSpots(u32 personality, u8 *dest, bool32 isSecondFrame)
{
    s32 i;
    for (i = 0; i < (s32)ARRAY_COUNT(gSpindaSpotGraphics); i++)
    {
        s32 row;
        u8 x = gSpindaSpotGraphics[i].x + (personality & 0x0F);
        u8 y = gSpindaSpotGraphics[i].y + ((personality & 0xF0) >> 4);

        if (isSecondFrame)
        {
            x -= 12;
            y += 56;
        }
        else
        {
            x -= 8;
            y -= 8;
        }

        for (row = 0; row < SPINDA_SPOT_HEIGHT; row++)
        {
            s32 column;
            s32 spotPixelRow = gSpindaSpotGraphics[i].image[row];

            for (column = x; column < x + SPINDA_SPOT_WIDTH; column++)
            {
                /* Get target pixels on Spinda's sprite */
                u8 *destPixels = dest + ((column / 8) * TILE_SIZE_4BPP) +
                    ((column % 8) / 2) +
                    ((y / 8) * TILE_SIZE_4BPP * 8) +
                    ((y % 8) * 4);

                /* Is this pixel in the 16x16 spot image part of the spot? */
                if (spotPixelRow & 1)
                {
                    /* destPixels addressess two pixels, alternate which */
                    /* of the two pixels is being considered for drawing */
                    if (column & 1)
                    {
                        /* Draw spot pixel if this is Spinda's body color */
                        TRY_DRAW_SPOT_PIXEL(destPixels, 4);
                    }
                    else
                    {
                        /* Draw spot pixel if this is Spinda's body color */
                        TRY_DRAW_SPOT_PIXEL(destPixels, 0);
                    }
                }

                spotPixelRow >>= 1;
            }

            y++;
        }

        personality >>= 8;
    }
}

void EvolutionRenameMon(struct Pokemon *mon, u16 oldSpecies, u16 newSpecies)
{
    u8 language;
    GetMonData(mon, MON_DATA_NICKNAME, gStringVar1);
    language = GetMonData(mon, MON_DATA_LANGUAGE, &language);
    if (language == GAME_LANGUAGE && !StringCompare(GetSpeciesName(oldSpecies), gStringVar1))
        SetMonData(mon, MON_DATA_NICKNAME, GetSpeciesName(newSpecies));
}

// The below two functions determine which side of a multi battle the trainer battles on
// 0 is the left (top in  party menu), 1 is right (bottom in party menu)
u8 GetPlayerFlankId(void)
{
    u8 flankId = 0;
    switch (gLinkPlayers[GetMultiplayerId()].id)
    {
    case 0:
    case 3:
        flankId = 0;
        break;
    case 1:
    case 2:
        flankId = 1;
        break;
    }
    return flankId;
}

u16 GetLinkTrainerFlankId(u8 linkPlayerId)
{
    u16 flankId = 0;
    switch (gLinkPlayers[linkPlayerId].id)
    {
    case 0:
    case 3:
        flankId = 0;
        break;
    case 1:
    case 2:
        flankId = 1;
        break;
    }
    return flankId;
}

s32 GetBattlerMultiplayerId(u16 id)
{
    s32 multiplayerId;
    for (multiplayerId = 0; multiplayerId < MAX_LINK_PLAYERS; multiplayerId++)
        if (gLinkPlayers[multiplayerId].id == id)
            break;
    return multiplayerId;
}

u8 GetTrainerEncounterMusicId(u16 trainerOpponentId)
{
    u32 sanitizedTrainerId = SanitizeTrainerId(trainerOpponentId);
    enum DifficultyLevel difficulty = GetTrainerDifficultyLevel(sanitizedTrainerId);

    if (InBattlePyramid())
        return GetTrainerEncounterMusicIdInBattlePyramid(trainerOpponentId);
    else if (InTrainerHillChallenge())
        return GetTrainerEncounterMusicIdInTrainerHill(trainerOpponentId);
    else
        return gTrainers[difficulty][sanitizedTrainerId].encounterMusic_gender & (F_TRAINER_FEMALE - 1);
}

u16 ModifyStatByNature(u8 nature, u16 stat, u8 statIndex)
{
    // Don't modify HP, Accuracy, or Evasion by nature
    if (statIndex <= STAT_HP || statIndex > NUM_NATURE_STATS || gNaturesInfo[nature].statUp == gNaturesInfo[nature].statDown)
        return stat;
    else if (statIndex == gNaturesInfo[nature].statUp)
        return stat * 110 / 100;
    else if (statIndex == gNaturesInfo[nature].statDown)
        return stat * 90 / 100;
    else
        return stat;
}

void AdjustFriendship(struct Pokemon *mon, u8 event)
{
    u16 species, heldItem;
    u8 holdEffect;
    s8 mod;

    if (ShouldSkipFriendshipChange())
        return;

    species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG, 0);
    heldItem = GetMonData(mon, MON_DATA_HELD_ITEM, 0);

    if (heldItem == ITEM_ENIGMA_BERRY_E_READER)
    {
        if (gMain.inBattle)
            holdEffect = gEnigmaBerries[0].holdEffect;
        else
        #if FREE_ENIGMA_BERRY == FALSE
            holdEffect = gSaveBlock1Ptr->enigmaBerry.holdEffect;
        #else
            holdEffect = 0;
        #endif //FREE_ENIGMA_BERRY
    }
    else
    {
        holdEffect = GetItemHoldEffect(heldItem);
    }

    if (species && species != SPECIES_EGG)
    {
        u8 friendshipLevel = 0;
        s16 friendship = GetMonData(mon, MON_DATA_FRIENDSHIP, 0);
        u32 opponentTrainerClass = GetTrainerClassFromId(TRAINER_BATTLE_PARAM.opponentA);

        if (friendship > 99)
            friendshipLevel++;
        if (friendship > 199)
            friendshipLevel++;

        if (event == FRIENDSHIP_EVENT_WALKING)
        {
            // 50% chance every 128 steps
            if (Random() & 1)
                return;
        }
        if (event == FRIENDSHIP_EVENT_LEAGUE_BATTLE)
        {
            // Only if it's a trainer battle with league progression significance
            if (!(gBattleTypeFlags & BATTLE_TYPE_TRAINER))
                return;
            if (!(opponentTrainerClass == TRAINER_CLASS_LEADER
                || opponentTrainerClass == TRAINER_CLASS_ELITE_FOUR
                || opponentTrainerClass == TRAINER_CLASS_CHAMPION))
                return;
        }

        mod = sFriendshipEventModifiers[event][friendshipLevel];
        if (mod > 0 && holdEffect == HOLD_EFFECT_FRIENDSHIP_UP)
            // 50% increase, rounding down
            mod = (150 * mod) / 100;

        friendship += mod;
        if (mod > 0)
        {
            if (GetMonData(mon, MON_DATA_POKEBALL, NULL) == ITEM_LUXURY_BALL)
                friendship++;
            if (GetMonData(mon, MON_DATA_MET_LOCATION, NULL) == GetCurrentRegionMapSectionId())
                friendship++;
        }

        if (friendship < 0)
            friendship = 0;
        if (friendship > MAX_FRIENDSHIP)
            friendship = MAX_FRIENDSHIP;

        SetMonData(mon, MON_DATA_FRIENDSHIP, &friendship);
    }
}

void MonGainEVs(struct Pokemon *mon, u16 defeatedSpecies)
{
    u8 evs[NUM_STATS];
    u16 evIncrease = 0;
    u16 totalEVs = 0;
    u16 heldItem;
    u8 holdEffect;
    int i, multiplier;
    u8 stat;
    u8 bonus;
    s32 evCap, maxEVs;

    evCap = GetEVStatCap();
    maxEVs = evCap == 0 ? 0 : evCap * 2 + 6;

    //Skip the EV check if not playing on EV mode
    if (!FlagGet(FLAG_EV_MODE)){
        return;
    }
    heldItem = GetMonData(mon, MON_DATA_HELD_ITEM, 0);
    if (heldItem == ITEM_ENIGMA_BERRY_E_READER)
    {
        if (gMain.inBattle)
            holdEffect = gEnigmaBerries[0].holdEffect;
        else
        #if FREE_ENIGMA_BERRY == FALSE
            holdEffect = gSaveBlock1Ptr->enigmaBerry.holdEffect;
        #else
            holdEffect = 0;
        #endif //FREE_ENIGMA_BERRY
    }
    else
    {
        holdEffect = GetItemHoldEffect(heldItem);
    }

    stat = GetItemSecondaryId(heldItem);
    bonus = GetItemHoldEffectParam(heldItem);

    for (i = 0; i < NUM_STATS; i++)
    {
        evs[i] = GetMonData(mon, MON_DATA_HP_EV + i, 0);
        totalEVs += evs[i];
    }

    for (i = 0; i < NUM_STATS; i++)
    {
        if (totalEVs >= maxEVs)
            break;

        if (CheckPartyHasHadPokerus(mon, 0))
            multiplier = 2;
        else
            multiplier = 1;

        switch (i)
        {
        case STAT_HP:
            if (holdEffect == HOLD_EFFECT_POWER_ITEM && stat == STAT_HP)
                evIncrease = (gSpeciesInfo[defeatedSpecies].evYield_HP + bonus) * multiplier;
            else
                evIncrease = gSpeciesInfo[defeatedSpecies].evYield_HP * multiplier;
            break;
        case STAT_ATK:
            if (holdEffect == HOLD_EFFECT_POWER_ITEM && stat == STAT_ATK)
                evIncrease = (gSpeciesInfo[defeatedSpecies].evYield_Attack + bonus) * multiplier;
            else
                evIncrease = gSpeciesInfo[defeatedSpecies].evYield_Attack * multiplier;
            break;
        case STAT_DEF:
            if (holdEffect == HOLD_EFFECT_POWER_ITEM && stat == STAT_DEF)
                evIncrease = (gSpeciesInfo[defeatedSpecies].evYield_Defense + bonus) * multiplier;
            else
                evIncrease = gSpeciesInfo[defeatedSpecies].evYield_Defense * multiplier;
            break;
        case STAT_SPEED:
            if (holdEffect == HOLD_EFFECT_POWER_ITEM && stat == STAT_SPEED)
                evIncrease = (gSpeciesInfo[defeatedSpecies].evYield_Speed + bonus) * multiplier;
            else
                evIncrease = gSpeciesInfo[defeatedSpecies].evYield_Speed * multiplier;
            break;
        case STAT_SPATK:
            if (holdEffect == HOLD_EFFECT_POWER_ITEM && stat == STAT_SPATK)
                evIncrease = (gSpeciesInfo[defeatedSpecies].evYield_SpAttack + bonus) * multiplier;
            else
                evIncrease = gSpeciesInfo[defeatedSpecies].evYield_SpAttack * multiplier;
            break;
        case STAT_SPDEF:
            if (holdEffect == HOLD_EFFECT_POWER_ITEM && stat == STAT_SPDEF)
                evIncrease = (gSpeciesInfo[defeatedSpecies].evYield_SpDefense + bonus) * multiplier;
            else
                evIncrease = gSpeciesInfo[defeatedSpecies].evYield_SpDefense * multiplier;
            break;
        }

        if (holdEffect == HOLD_EFFECT_MACHO_BRACE)
            evIncrease *= 2;

        if (totalEVs + (s16)evIncrease > maxEVs)
            evIncrease = ((s16)evIncrease + maxEVs) - (totalEVs + evIncrease);

        if (evs[i] + (s16)evIncrease > evCap)
        {
            int val1 = (s16)evIncrease + evCap;
            int val2 = evs[i] + evIncrease;
            evIncrease = val1 - val2;
        }

        evs[i] += evIncrease;
        totalEVs += evIncrease;
        SetMonData(mon, MON_DATA_HP_EV + i, &evs[i]);
    }
}

u16 GetMonEVCount(struct Pokemon *mon)
{
    int i;
    u16 count = 0;

    for (i = 0; i < NUM_STATS; i++)
        count += GetMonData(mon, MON_DATA_HP_EV + i, 0);

    return count;
}

void RandomlyGivePartyPokerus(struct Pokemon *party)
{
    u16 rnd = Random();
    if (rnd == 0x4000 || rnd == 0x8000 || rnd == 0xC000)
    {
        struct Pokemon *mon;

        do
        {
            rnd = Random() % PARTY_SIZE;
            mon = &party[rnd];
        }
        while (!GetMonData(mon, MON_DATA_SPECIES, 0) || GetMonData(mon, MON_DATA_IS_EGG, 0));

        if (!(CheckPartyHasHadPokerus(party, 1u << rnd)))
        {
            u8 rnd2;

            do
            {
                rnd2 = Random();
            }
            while ((rnd2 & 0x7) == 0);

            if (rnd2 & 0xF0)
                rnd2 &= 0x7;

            rnd2 |= (rnd2 << 4);
            rnd2 &= 0xF3;
            rnd2++;

            SetMonData(&party[rnd], MON_DATA_POKERUS, &rnd2);
        }
    }
}

u8 CheckPartyPokerus(struct Pokemon *party, u8 selection)
{
    u8 retVal;

    int partyIndex = 0;
    unsigned curBit = 1;
    retVal = 0;

    if (selection)
    {
        do
        {
            if ((selection & 1) && (GetMonData(&party[partyIndex], MON_DATA_POKERUS, 0) & 0xF))
                retVal |= curBit;
            partyIndex++;
            curBit <<= 1;
            selection >>= 1;
        }
        while (selection);
    }
    else if (GetMonData(&party[0], MON_DATA_POKERUS, 0) & 0xF)
    {
        retVal = 1;
    }

    return retVal;
}

u8 CheckPartyHasHadPokerus(struct Pokemon *party, u8 selection)
{
    u8 retVal;

    int partyIndex = 0;
    unsigned curBit = 1;
    retVal = 0;

    if (selection)
    {
        do
        {
            if ((selection & 1) && GetMonData(&party[partyIndex], MON_DATA_POKERUS, 0))
                retVal |= curBit;
            partyIndex++;
            curBit <<= 1;
            selection >>= 1;
        }
        while (selection);
    }
    else if (GetMonData(&party[0], MON_DATA_POKERUS, 0))
    {
        retVal = 1;
    }

    return retVal;
}

void UpdatePartyPokerusTime(u16 days)
{
    int i;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, 0))
        {
            u8 pokerus = GetMonData(&gPlayerParty[i], MON_DATA_POKERUS, 0);
            if (pokerus & 0xF)
            {
                if ((pokerus & 0xF) < days || days > 4)
                    pokerus &= 0xF0;
                else
                    pokerus -= days;

                if (pokerus == 0)
                    pokerus = 0x10;

                SetMonData(&gPlayerParty[i], MON_DATA_POKERUS, &pokerus);
            }
        }
    }
}

void PartySpreadPokerus(struct Pokemon *party)
{
    if ((Random() % 3) == 0)
    {
        int i;
        for (i = 0; i < PARTY_SIZE; i++)
        {
            if (GetMonData(&party[i], MON_DATA_SPECIES, 0))
            {
                u8 pokerus = GetMonData(&party[i], MON_DATA_POKERUS, 0);
                u8 curPokerus = pokerus;
                if (pokerus)
                {
                    if (pokerus & 0xF)
                    {
                        // Spread to adjacent party members.
                        if (i != 0 && !(GetMonData(&party[i - 1], MON_DATA_POKERUS, 0) & 0xF0))
                            SetMonData(&party[i - 1], MON_DATA_POKERUS, &curPokerus);
                        if (i != (PARTY_SIZE - 1) && !(GetMonData(&party[i + 1], MON_DATA_POKERUS, 0) & 0xF0))
                        {
                            SetMonData(&party[i + 1], MON_DATA_POKERUS, &curPokerus);
                            i++;
                        }
                    }
                }
            }
        }
    }
}

bool8 TryIncrementMonLevel(struct Pokemon *mon)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES, 0);
    u8 nextLevel = GetMonData(mon, MON_DATA_LEVEL, 0) + 1;
    u32 expPoints = GetMonData(mon, MON_DATA_EXP, 0);
    if (expPoints > gExperienceTables[gSpeciesInfo[species].growthRate][MAX_LEVEL])
    {
        expPoints = gExperienceTables[gSpeciesInfo[species].growthRate][MAX_LEVEL];
        SetMonData(mon, MON_DATA_EXP, &expPoints);
    }
    if (nextLevel > GetCurrentLevelCap(CANDY_CAP) || expPoints < gExperienceTables[gSpeciesInfo[species].growthRate][nextLevel])
    {
        return FALSE;
    }
    else
    {
        SetMonData(mon, MON_DATA_LEVEL, &nextLevel);
        return TRUE;
    }
}

static const u16 sUniversalMoves[] =
{
    MOVE_FRUSTRATION,
    MOVE_NATURAL_GIFT,
    MOVE_RAGE,
    MOVE_RETURN,
    MOVE_SECRET_POWER,
    MOVE_SUBSTITUTE,
    MOVE_TERA_BLAST,
};

u8 CanLearnTeachableMove(u16 species, u16 move)
{
    if (species == SPECIES_EGG)
    {
        return FALSE;
    }
    else if (species == SPECIES_MEW)
    {
        switch (move)
        {
        case MOVE_BADDY_BAD:
        case MOVE_BOUNCY_BUBBLE:
        case MOVE_BUZZY_BUZZ:
        case MOVE_DRAGON_ASCENT:
        case MOVE_FLOATY_FALL:
        case MOVE_FREEZY_FROST:
        case MOVE_GLITZY_GLOW:
        case MOVE_RELIC_SONG:
        case MOVE_SAPPY_SEED:
        case MOVE_SECRET_SWORD:
        case MOVE_SIZZLY_SLIDE:
        case MOVE_SPARKLY_SWIRL:
        case MOVE_SPLISHY_SPLASH:
        case MOVE_VOLT_TACKLE:
        case MOVE_ZIPPY_ZAP:
            return FALSE;
        default:
            return TRUE;
        }
    }
    else
    {
        u32 i, j;
        const u16 *teachableLearnset = GetSpeciesTeachableLearnset(species);
        for (i = 0; i < ARRAY_COUNT(sUniversalMoves); i++)
        {
            if (sUniversalMoves[i] == move)
            {
                if (!gSpeciesInfo[species].tmIlliterate)
                {
                    if (move == MOVE_TERA_BLAST && GET_BASE_SPECIES_ID(species) == SPECIES_TERAPAGOS)
                        return FALSE;
                    if (GET_BASE_SPECIES_ID(species) == SPECIES_PYUKUMUKU && (move == MOVE_HIDDEN_POWER || move == MOVE_RETURN || move == MOVE_FRUSTRATION))
                        return FALSE;
                    return TRUE;
                }
                else
                {
                    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(species);

                    if (P_TM_LITERACY < GEN_6)
                        return FALSE;

                    for (j = 0; j < MAX_LEVEL_UP_MOVES && learnset[j].move != LEVEL_UP_MOVE_END; j++)
                    {
                        if (learnset[j].move == move)
                            return TRUE;
                    }
                    return FALSE;
                }
            }
        }
        for (i = 0; teachableLearnset[i] != MOVE_UNAVAILABLE; i++)
        {
            if (teachableLearnset[i] == move)
                return TRUE;
        }
        return FALSE;
    }
}

u8 GetMoveRelearnerMoves(struct Pokemon *mon, u16 *moves)
{
    u16 learnedMoves[4];
    u8 numMoves = 0;
    u16 species = GetMonData(mon, MON_DATA_SPECIES, 0);
    u8 level = GetMonData(mon, MON_DATA_LEVEL, 0);
    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(species);
    int i, j, k;

    for (i = 0; i < MAX_MON_MOVES; i++)
        learnedMoves[i] = GetMonData(mon, MON_DATA_MOVE1 + i, 0);

    for (i = 0; i < MAX_LEVEL_UP_MOVES; i++)
    {
        u16 moveLevel;

        if (learnset[i].move == LEVEL_UP_MOVE_END)
            break;

        //Restricted Mode exception for Torch Song
        if (FlagGet(FLAG_RESTRICTED_MODE) && learnset[i].move == MOVE_TORCH_SONG){
            continue;
        }
        moveLevel = learnset[i].level;

        if (moveLevel <= level)
        {
            for (j = 0; j < MAX_MON_MOVES && learnedMoves[j] != learnset[i].move; j++)
                ;

            if (j == MAX_MON_MOVES)
            {
                for (k = 0; k < numMoves && moves[k] != learnset[i].move; k++)
                    ;

                if (k == numMoves)
                    moves[numMoves++] = learnset[i].move;
            }
        }
    }

    return numMoves;
}

u8 GetLevelUpMovesBySpecies(u16 species, u16 *moves)
{
    u8 numMoves = 0;
    int i;
    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(species);

    for (i = 0; i < MAX_LEVEL_UP_MOVES && learnset[i].move != LEVEL_UP_MOVE_END; i++)
         moves[numMoves++] = learnset[i].move;

     return numMoves;
}

u8 GetNumberOfRelearnableMoves(struct Pokemon *mon)
{
    u16 learnedMoves[MAX_MON_MOVES];
    u16 moves[MAX_LEVEL_UP_MOVES];
    u8 numMoves = 0;
    u16 species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG, 0);
    u8 level = GetMonData(mon, MON_DATA_LEVEL, 0);
    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(species);
    int i, j, k;

    if (species == SPECIES_EGG)
        return 0;

    for (i = 0; i < MAX_MON_MOVES; i++)
        learnedMoves[i] = GetMonData(mon, MON_DATA_MOVE1 + i, 0);

    for (i = 0; i < MAX_LEVEL_UP_MOVES; i++)
    {
        u16 moveLevel;

        if (learnset[i].move == LEVEL_UP_MOVE_END)
            break;

        moveLevel = learnset[i].level;

        if (moveLevel <= level)
        {
            for (j = 0; j < MAX_MON_MOVES && learnedMoves[j] != learnset[i].move; j++)
                ;

            if (j == MAX_MON_MOVES)
            {
                for (k = 0; k < numMoves && moves[k] != learnset[i].move; k++)
                    ;

                if (k == numMoves)
                    moves[numMoves++] = learnset[i].move;
            }
        }
    }

    return numMoves;
}

//Adds tutor moves from a tutorMoves array to an applicable moves pointer
static u8 AddTutorMoves(u16 species, u16 *applicable_moves, const u16 *tutorMoves, size_t numTutorMoves, u8 currentNumMoves){
    u8 addedMoves = 0;
    int i;

    for (i=0; i < numTutorMoves; i++){
        // if (species == SPECIES_SHINX && tutorMoves[i] == MOVE_MUD_SLAP){
        //     DebugPrintf("Mud Slap Shinx case reached. The bool result is %d", CanLearnTeachableMove(species, tutorMoves[i]));
        // }
        if (CanLearnTeachableMove(species, tutorMoves[i])){
            applicable_moves[currentNumMoves + addedMoves++] = tutorMoves[i];
        }

    }
    return addedMoves;
}

static u8 GetCenterTutorMoveList(u16 species, u16 *applicable_moves){
    u8 numMoves = 0;

    //pre-badge one, always applies
    numMoves += AddTutorMoves(species, applicable_moves, gPreGym1Tutor, ARRAY_COUNT(gPreGym1Tutor), numMoves);
    //pre-badge 1 moves not available in restricted
    if (!FlagGet(FLAG_RESTRICTED_MODE)){
        numMoves += AddTutorMoves(species, applicable_moves, gPreGym1TutorSetup, ARRAY_COUNT(gPreGym1TutorSetup), numMoves);   
    }

    //If acquired one badge
    if (FlagGet(FLAG_BADGE01_GET)){
        numMoves += AddTutorMoves(species, applicable_moves, gPreGym2Tutor, ARRAY_COUNT(gPreGym2Tutor), numMoves);
        //There are currently no moves but still including the check anyway
        if (!FlagGet(FLAG_RESTRICTED_MODE)){
            numMoves += AddTutorMoves(species, applicable_moves, gPreGym2TutorSetup, ARRAY_COUNT(gPreGym2TutorSetup), numMoves);   
        }
    }
    if (FlagGet(FLAG_BADGE02_GET)){
        numMoves += AddTutorMoves(species, applicable_moves, gPreGym3Tutor, ARRAY_COUNT(gPreGym3Tutor), numMoves);
        if (!FlagGet(FLAG_RESTRICTED_MODE)){
            numMoves += AddTutorMoves(species, applicable_moves, gPreGym3TutorSetup, ARRAY_COUNT(gPreGym3TutorSetup), numMoves);   
        }        
    }
    return numMoves;    
}

static u8 GetTechTutorMoveList(u16 species, u16 *applicable_moves){
    u8 numMoves = 0;

    // DebugPrintf("GetTechTutorMoveList is called");

    //pre-badge one, always applies
    numMoves += AddTutorMoves(species, applicable_moves, gTechTutorAlways, ARRAY_COUNT(gTechTutorAlways), numMoves);

    //If acquired one badge 
    if (FlagGet(FLAG_BADGE01_GET)){
        numMoves += AddTutorMoves(species, applicable_moves, gTechTutor1Badge, ARRAY_COUNT(gTechTutor1Badge), numMoves);
    }
    return numMoves;    
}

u8 GetNPCTutorMoveList(u16 species, u16 *applicable_moves){    
    if(VarGet(VAR_TEMP_9) == MOVE_TUTOR_CENTER){
        return GetCenterTutorMoveList(species, applicable_moves);
    }else if (VarGet(VAR_TEMP_9) == MOVE_TUTOR_TECH){
        return GetTechTutorMoveList(species, applicable_moves);
    }

    return 0;
}

u8 GetNPCTutorableMoves(struct Pokemon *mon, u16 *moves)
{
    u16 learnedMoves[4];
    u8 numMoves = 0;
    u16 species = GetMonData(mon, MON_DATA_SPECIES, 0);

    u16 applicable_tutor_moves[MAX_TUTOR_LIST] = {0};

    int i, j;

    if (species == SPECIES_EGG){
        return 0;
    }
    
    GetNPCTutorMoveList(species, applicable_tutor_moves);


    for (i = 0; i < MAX_MON_MOVES; i++)
        learnedMoves[i] = GetMonData(mon, MON_DATA_MOVE1 + i, 0);

    for (i=0; i< MAX_TUTOR_LIST; i++){
        if (!applicable_tutor_moves[i]){
            break;
        }
        for (j=0; j < MAX_MON_MOVES && learnedMoves[j] != applicable_tutor_moves[i]; j++){
            ;
        }
        //If the applicable move is not in the learned moves array, add it to the moves array
        if (j == MAX_MON_MOVES){
            moves[numMoves++] = applicable_tutor_moves[i];
        }
    }
    return numMoves;
}

//Simply use the CenterTutorableMoves number of tutorable moves
//To compute this, since it handles move overlaps
u8 GetNumberOfCenterTutorableMoves(struct Pokemon *mon)
{   
    u16 moves[MAX_TUTOR_LIST] = {0};
    return GetNPCTutorableMoves(mon, moves);
}
u16 SpeciesToPokedexNum(u16 species)
{
    if (IsNationalPokedexEnabled())
    {
        return SpeciesToNationalPokedexNum(species);
    }
    else
    {
        species = SpeciesToHoennPokedexNum(species);
        if (species <= HOENN_DEX_COUNT)
            return species;
        return 0xFFFF;
    }
}

bool32 IsSpeciesInHoennDex(u16 species)
{
    if (SpeciesToHoennPokedexNum(species) > HOENN_DEX_COUNT)
        return FALSE;
    else
        return TRUE;
}

u16 GetBattleBGM(void)
{
    if (gBattleTypeFlags & BATTLE_TYPE_LEGENDARY)
    {
        switch (GetMonData(&gEnemyParty[0], MON_DATA_SPECIES, NULL))
        {
        case SPECIES_RAYQUAZA:
            return MUS_VS_RAYQUAZA;
        case SPECIES_KYOGRE:
        case SPECIES_GROUDON:
            return MUS_VS_KYOGRE_GROUDON;
        case SPECIES_REGIROCK:
        case SPECIES_REGICE:
        case SPECIES_REGISTEEL:
        case SPECIES_REGIGIGAS:
        case SPECIES_REGIELEKI:
        case SPECIES_REGIDRAGO:
            return MUS_VS_REGI;
        default:
            return MUS_RG_VS_LEGEND;
        }
    }
    else if (gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK))
    {
        return MUS_VS_TRAINER;
    }
    else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER)
    {
        u8 trainerClass;

        if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
            trainerClass = GetFrontierOpponentClass(TRAINER_BATTLE_PARAM.opponentA);
        else if (gBattleTypeFlags & BATTLE_TYPE_TRAINER_HILL)
            trainerClass = TRAINER_CLASS_EXPERT;
        else
            trainerClass = GetTrainerClassFromId(TRAINER_BATTLE_PARAM.opponentA);

        switch (trainerClass)
        {
        case TRAINER_CLASS_AQUA_LEADER:
        case TRAINER_CLASS_MAGMA_LEADER:
            return MUS_VS_AQUA_MAGMA_LEADER;
        case TRAINER_CLASS_TEAM_AQUA:
        case TRAINER_CLASS_TEAM_MAGMA:
        case TRAINER_CLASS_AQUA_ADMIN:
        case TRAINER_CLASS_MAGMA_ADMIN:
            return MUS_VS_AQUA_MAGMA;
        case TRAINER_CLASS_LEADER:
            return MUS_VS_GYM_LEADER;
        case TRAINER_CLASS_CHAMPION:
            return MUS_VS_CHAMPION;
        case TRAINER_CLASS_RIVAL:
            if (gBattleTypeFlags & BATTLE_TYPE_FRONTIER)
                return MUS_VS_RIVAL;
            if (!StringCompare(GetTrainerNameFromId(TRAINER_BATTLE_PARAM.opponentA), gText_BattleWallyName))
                return MUS_VS_TRAINER;
            return MUS_VS_RIVAL;
        case TRAINER_CLASS_ELITE_FOUR:
            return MUS_VS_ELITE_FOUR;
        case TRAINER_CLASS_SALON_MAIDEN:
        case TRAINER_CLASS_DOME_ACE:
        case TRAINER_CLASS_PALACE_MAVEN:
        case TRAINER_CLASS_ARENA_TYCOON:
        case TRAINER_CLASS_FACTORY_HEAD:
        case TRAINER_CLASS_PIKE_QUEEN:
        case TRAINER_CLASS_PYRAMID_KING:
            return MUS_VS_FRONTIER_BRAIN;
        default:
            return MUS_VS_TRAINER;
        }
    }
    else
    {
        return MUS_VS_WILD;
    }
}

void PlayBattleBGM(void)
{
    ResetMapMusic();
    m4aMPlayAllStop();
    PlayBGM(GetBattleBGM());
}

void PlayMapChosenOrBattleBGM(u16 songId)
{
    ResetMapMusic();
    m4aMPlayAllStop();
    if (songId)
        PlayNewMapMusic(songId);
    else
        PlayNewMapMusic(GetBattleBGM());
}

// Identical to PlayMapChosenOrBattleBGM, but uses a task instead
// Only used by Battle Dome
#define tSongId data[0]
void CreateTask_PlayMapChosenOrBattleBGM(u16 songId)
{
    u8 taskId;

    ResetMapMusic();
    m4aMPlayAllStop();

    taskId = CreateTask(Task_PlayMapChosenOrBattleBGM, 0);
    gTasks[taskId].tSongId = songId;
}

static void Task_PlayMapChosenOrBattleBGM(u8 taskId)
{
    if (gTasks[taskId].tSongId)
        PlayNewMapMusic(gTasks[taskId].tSongId);
    else
        PlayNewMapMusic(GetBattleBGM());
    DestroyTask(taskId);
}

#undef tSongId

const u16 *GetMonFrontSpritePal(struct Pokemon *mon)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES_OR_EGG, NULL);
    bool32 isShiny = GetMonData(mon, MON_DATA_IS_SHINY, NULL);
    u32 personality = GetMonData(mon, MON_DATA_PERSONALITY, NULL);
    return GetMonSpritePalFromSpeciesAndPersonality(species, isShiny, personality);
}

const u16 *GetMonSpritePalFromSpeciesAndPersonality(u16 species, bool32 isShiny, u32 personality)
{
    return GetMonSpritePalFromSpecies(species, isShiny, IsPersonalityFemale(species, personality));
}

const u16 *GetMonSpritePalFromSpecies(u16 species, bool32 isShiny, bool32 isFemale)
{
    species = SanitizeSpeciesId(species);

    if (isShiny)
    {
    #if P_GENDER_DIFFERENCES
        if (gSpeciesInfo[species].shinyPaletteFemale != NULL && isFemale)
            return gSpeciesInfo[species].shinyPaletteFemale;
        else
    #endif
        if (gSpeciesInfo[species].shinyPalette != NULL)
            return gSpeciesInfo[species].shinyPalette;
        else
            return gSpeciesInfo[SPECIES_NONE].shinyPalette;
    }
    else
    {
    #if P_GENDER_DIFFERENCES
        if (gSpeciesInfo[species].paletteFemale != NULL && isFemale)
            return gSpeciesInfo[species].paletteFemale;
        else
    #endif
        if (gSpeciesInfo[species].palette != NULL)
            return gSpeciesInfo[species].palette;
        else
            return gSpeciesInfo[SPECIES_NONE].palette;
    }
}

bool8 IsMoveHM(u16 move)
{
    int i = 0;

    if (P_CAN_FORGET_HIDDEN_MOVE)
        return FALSE;

    while (sHMMoves[i] != HM_MOVES_END)
    {
        if (sHMMoves[i++] == move)
            return TRUE;
    }
    return FALSE;
}

bool8 IsMonSpriteNotFlipped(u16 species)
{
    return gSpeciesInfo[species].noFlip;
}

s8 GetMonFlavorRelation(struct Pokemon *mon, u8 flavor)
{
    u8 nature = GetNature(mon);
    return gPokeblockFlavorCompatibilityTable[nature * FLAVOR_COUNT + flavor];
}

s8 GetFlavorRelationByPersonality(u32 personality, u8 flavor)
{
    u8 nature = GetNatureFromPersonality(personality);
    return gPokeblockFlavorCompatibilityTable[nature * FLAVOR_COUNT + flavor];
}

bool8 IsTradedMon(struct Pokemon *mon)
{
    u8 otName[PLAYER_NAME_LENGTH + 1];
    u32 otId;
    GetMonData(mon, MON_DATA_OT_NAME, otName);
    otId = GetMonData(mon, MON_DATA_OT_ID, 0);
    return IsOtherTrainer(otId, otName);
}

bool8 IsOtherTrainer(u32 otId, u8 *otName)
{
    if (otId ==
        (gSaveBlock2Ptr->playerTrainerId[0]
      | (gSaveBlock2Ptr->playerTrainerId[1] << 8)
      | (gSaveBlock2Ptr->playerTrainerId[2] << 16)
      | (gSaveBlock2Ptr->playerTrainerId[3] << 24)))
    {
        int i;
        for (i = 0; otName[i] != EOS; i++)
            if (otName[i] != gSaveBlock2Ptr->playerName[i])
                return TRUE;
        return FALSE;
    }

    return TRUE;
}

void MonRestorePP(struct Pokemon *mon)
{
    BoxMonRestorePP(&mon->box);
}

void BoxMonRestorePP(struct BoxPokemon *boxMon)
{
    int i;

    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (GetBoxMonData(boxMon, MON_DATA_MOVE1 + i, 0))
        {
            u16 move = GetBoxMonData(boxMon, MON_DATA_MOVE1 + i, 0);
            u16 bonus = GetBoxMonData(boxMon, MON_DATA_PP_BONUSES, 0);
            u8 pp = CalculatePPWithBonus(move, bonus, i);
            SetBoxMonData(boxMon, MON_DATA_PP1 + i, &pp);
        }
    }
}

void SetMonPreventsSwitchingString(void)
{
    gLastUsedAbility = gBattleStruct->abilityPreventingSwitchout;

    gBattleTextBuff1[0] = B_BUFF_PLACEHOLDER_BEGIN;
    gBattleTextBuff1[1] = B_BUFF_MON_NICK_WITH_PREFIX;
    gBattleTextBuff1[2] = gBattleStruct->battlerPreventingSwitchout;
    gBattleTextBuff1[4] = B_BUFF_EOS;

    if (IsOnPlayerSide(gBattleStruct->battlerPreventingSwitchout))
        gBattleTextBuff1[3] = GetPartyIdFromBattlePartyId(gBattlerPartyIndexes[gBattleStruct->battlerPreventingSwitchout]);
    else
        gBattleTextBuff1[3] = gBattlerPartyIndexes[gBattleStruct->battlerPreventingSwitchout];

    PREPARE_MON_NICK_WITH_PREFIX_BUFFER(gBattleTextBuff2, gBattlerInMenuId, GetPartyIdFromBattlePartyId(gBattlerPartyIndexes[gBattlerInMenuId]))

    BattleStringExpandPlaceholders(gText_PkmnsXPreventsSwitching, gStringVar4, sizeof(gStringVar4));
}

static s32 GetWildMonTableIdInAlteringCave(u16 species)
{
    s32 i;
    for (i = 0; i < (s32) ARRAY_COUNT(sAlteringCaveWildMonHeldItems); i++)
        if (sAlteringCaveWildMonHeldItems[i].species == species)
            return i;
    return 0;
}

static inline bool32 CanFirstMonBoostHeldItemRarity(void)
{
    u32 ability;
    if (GetMonData(&gPlayerParty[0], MON_DATA_SANITY_IS_EGG))
        return FALSE;

    ability = GetMonAbility(&gPlayerParty[0]);
    if (ability == ABILITY_COMPOUND_EYES)
        return TRUE;
    else if ((OW_SUPER_LUCK >= GEN_8) && ability == ABILITY_SUPER_LUCK)
        return TRUE;
    return FALSE;
}

void SetWildMonHeldItem(void)
{
    if (!(gBattleTypeFlags & (BATTLE_TYPE_LEGENDARY | BATTLE_TYPE_TRAINER | BATTLE_TYPE_PYRAMID | BATTLE_TYPE_PIKE)))
    {
        u16 rnd;
        u16 species;
        u16 count = (WILD_DOUBLE_BATTLE) ? 2 : 1;
        u16 i;
        bool32 itemHeldBoost = CanFirstMonBoostHeldItemRarity();
        u16 chanceNoItem = itemHeldBoost ? 20 : 45;
        u16 chanceNotRare = itemHeldBoost ? 80 : 95;

        for (i = 0; i < count; i++)
        {
            if (GetMonData(&gEnemyParty[i], MON_DATA_HELD_ITEM, NULL) != ITEM_NONE)
                continue; // prevent overwriting previously set item

            rnd = Random() % 100;
            species = GetMonData(&gEnemyParty[i], MON_DATA_SPECIES, 0);
            if (gMapHeader.mapLayoutId == LAYOUT_ALTERING_CAVE)
            {
                s32 alteringCaveId = GetWildMonTableIdInAlteringCave(species);
                if (alteringCaveId != 0)
                {
                    // In active Altering Cave, use special item list
                    if (rnd < chanceNotRare)
                        continue;
                    SetMonData(&gEnemyParty[i], MON_DATA_HELD_ITEM, &sAlteringCaveWildMonHeldItems[alteringCaveId].item);
                }
                else
                {
                    // In inactive Altering Cave, use normal items
                    if (rnd < chanceNoItem)
                        continue;
                    if (rnd < chanceNotRare)
                        SetMonData(&gEnemyParty[i], MON_DATA_HELD_ITEM, &gSpeciesInfo[species].itemCommon);
                    else
                        SetMonData(&gEnemyParty[i], MON_DATA_HELD_ITEM, &gSpeciesInfo[species].itemRare);
                }
            }
            else
            {
                if (gSpeciesInfo[species].itemCommon == gSpeciesInfo[species].itemRare && gSpeciesInfo[species].itemCommon != ITEM_NONE)
                {
                    // Both held items are the same, 100% chance to hold item
                    SetMonData(&gEnemyParty[i], MON_DATA_HELD_ITEM, &gSpeciesInfo[species].itemCommon);
                }
                else
                {
                    if (rnd < chanceNoItem)
                        continue;
                    if (rnd < chanceNotRare)
                        SetMonData(&gEnemyParty[i], MON_DATA_HELD_ITEM, &gSpeciesInfo[species].itemCommon);
                    else
                        SetMonData(&gEnemyParty[i], MON_DATA_HELD_ITEM, &gSpeciesInfo[species].itemRare);
                }
            }
        }
    }
}

bool8 IsMonShiny(struct Pokemon *mon)
{
    return GetMonData(mon, MON_DATA_IS_SHINY, NULL);
}

const u8 *GetTrainerPartnerName(void)
{
    if (gBattleTypeFlags & BATTLE_TYPE_INGAME_PARTNER)
    {
        GetFrontierTrainerName(gStringVar1, gPartnerTrainerId);
        return gStringVar1;
    }
    else
    {
        u8 id = GetMultiplayerId();
        return gLinkPlayers[GetBattlerMultiplayerId(gLinkPlayers[id].id ^ 2)].name;
    }
}

#define READ_PTR_FROM_TASK(taskId, dataId)                      \
    (void *)(                                                   \
    ((u16)(gTasks[taskId].data[dataId]) |                       \
    ((u16)(gTasks[taskId].data[dataId + 1]) << 16)))

#define STORE_PTR_IN_TASK(ptr, taskId, dataId)                 \
{                                                              \
    gTasks[taskId].data[dataId] = (u32)(ptr);                  \
    gTasks[taskId].data[dataId + 1] = (u32)(ptr) >> 16;        \
}

#define sAnimId    data[2]
#define sAnimDelay data[3]

static void Task_AnimateAfterDelay(u8 taskId)
{
    if (--gTasks[taskId].sAnimDelay == 0)
    {
        LaunchAnimationTaskForFrontSprite(READ_PTR_FROM_TASK(taskId, 0), gTasks[taskId].sAnimId);
        DestroyTask(taskId);
    }
}

static void Task_PokemonSummaryAnimateAfterDelay(u8 taskId)
{
    if (--gTasks[taskId].sAnimDelay == 0)
    {
        StartMonSummaryAnimation(READ_PTR_FROM_TASK(taskId, 0), gTasks[taskId].sAnimId);
        SummaryScreen_SetAnimDelayTaskId(TASK_NONE);
        DestroyTask(taskId);
    }
}

void BattleAnimateFrontSprite(struct Sprite *sprite, u16 species, bool8 noCry, u8 panMode)
{
    if (gHitMarker & HITMARKER_NO_ANIMATIONS && !(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK)))
        DoMonFrontSpriteAnimation(sprite, species, noCry, panMode | SKIP_FRONT_ANIM);
    else
        DoMonFrontSpriteAnimation(sprite, species, noCry, panMode);
}

void DoMonFrontSpriteAnimation(struct Sprite *sprite, u16 species, bool8 noCry, u8 panModeAnimFlag)
{
    s8 pan;
    switch (panModeAnimFlag & (u8)~SKIP_FRONT_ANIM) // Exclude anim flag to get pan mode
    {
    case 0:
        pan = -25;
        break;
    case 1:
        pan = 25;
        break;
    default:
        pan = 0;
        break;
    }
    if (panModeAnimFlag & SKIP_FRONT_ANIM)
    {
        // No animation, only check if cry needs to be played
        if (!noCry)
            PlayCry_Normal(species, pan);
        sprite->callback = SpriteCallbackDummy;
    }
    else
    {
        if (!noCry)
        {
            PlayCry_Normal(species, pan);
            if (HasTwoFramesAnimation(species))
                StartSpriteAnim(sprite, 1);
        }
        if (gSpeciesInfo[species].frontAnimDelay != 0)
        {
            // Animation has delay, start delay task
            u8 taskId = CreateTask(Task_AnimateAfterDelay, 0);
            STORE_PTR_IN_TASK(sprite, taskId, 0);
            gTasks[taskId].sAnimId = gSpeciesInfo[species].frontAnimId;
            gTasks[taskId].sAnimDelay = gSpeciesInfo[species].frontAnimDelay;
        }
        else
        {
            // No delay, start animation
            LaunchAnimationTaskForFrontSprite(sprite, gSpeciesInfo[species].frontAnimId);
        }
        sprite->callback = SpriteCallbackDummy_2;
    }
}

void PokemonSummaryDoMonAnimation(struct Sprite *sprite, u16 species, bool8 oneFrame)
{
    if (!oneFrame && HasTwoFramesAnimation(species))
        StartSpriteAnim(sprite, 1);
    if (gSpeciesInfo[species].frontAnimDelay != 0)
    {
        // Animation has delay, start delay task
        u8 taskId = CreateTask(Task_PokemonSummaryAnimateAfterDelay, 0);
        STORE_PTR_IN_TASK(sprite, taskId, 0);
        gTasks[taskId].sAnimId = gSpeciesInfo[species].frontAnimId;
        gTasks[taskId].sAnimDelay = gSpeciesInfo[species].frontAnimDelay;
        SummaryScreen_SetAnimDelayTaskId(taskId);
        SetSpriteCB_MonAnimDummy(sprite);
    }
    else
    {
        // No delay, start animation
        StartMonSummaryAnimation(sprite, gSpeciesInfo[species].frontAnimId);
    }
}

void StopPokemonAnimationDelayTask(void)
{
    u8 delayTaskId = FindTaskIdByFunc(Task_PokemonSummaryAnimateAfterDelay);
    if (delayTaskId != TASK_NONE)
        DestroyTask(delayTaskId);
}

void BattleAnimateBackSprite(struct Sprite *sprite, u16 species)
{
    if (gHitMarker & HITMARKER_NO_ANIMATIONS && !(gBattleTypeFlags & (BATTLE_TYPE_LINK | BATTLE_TYPE_RECORDED_LINK)))
    {
        sprite->callback = SpriteCallbackDummy;
    }
    else
    {
        LaunchAnimationTaskForBackSprite(sprite, GetSpeciesBackAnimSet(species));
        sprite->callback = SpriteCallbackDummy_2;
    }
}

// Identical to GetOpposingLinkMultiBattlerId but for the player
// "rightSide" from that team's perspective, i.e. B_POSITION_*_RIGHT
static u8 UNUSED GetOwnOpposingLinkMultiBattlerId(bool8 rightSide)
{
    s32 i;
    s32 battler = 0;
    u8 multiplayerId = GetMultiplayerId();
    switch (gLinkPlayers[multiplayerId].id)
    {
    case 0:
    case 2:
        battler = rightSide ? 1 : 3;
        break;
    case 1:
    case 3:
        battler = rightSide ? 2 : 0;
        break;
    }
    for (i = 0; i < MAX_LINK_PLAYERS; i++)
    {
        if (gLinkPlayers[i].id == (s16)battler)
            break;
    }
    return i;
}

u8 GetOpposingLinkMultiBattlerId(bool8 rightSide, u8 multiplayerId)
{
    s32 i;
    s32 battler = 0;
    switch (gLinkPlayers[multiplayerId].id)
    {
    case 0:
    case 2:
        battler = rightSide ? 1 : 3;
        break;
    case 1:
    case 3:
        battler = rightSide ? 2 : 0;
        break;
    }
    for (i = 0; i < MAX_LINK_PLAYERS; i++)
    {
        if (gLinkPlayers[i].id == (s16)battler)
            break;
    }
    return i;
}

u16 FacilityClassToPicIndex(u16 facilityClass)
{
    return gFacilityClassToPicIndex[facilityClass];
}

u16 PlayerGenderToFrontTrainerPicId(u8 playerGender)
{
    if (playerGender != MALE)
        return FacilityClassToPicIndex(FACILITY_CLASS_MAY);
    else
        return FacilityClassToPicIndex(FACILITY_CLASS_BRENDAN);
}

void HandleSetPokedexFlag(u16 nationalNum, u8 caseId, u32 personality)
{
    u8 getFlagCaseId = (caseId == FLAG_SET_SEEN) ? FLAG_GET_SEEN : FLAG_GET_CAUGHT;
    if (!GetSetPokedexFlag(nationalNum, getFlagCaseId)) // don't set if it's already set
    {
        GetSetPokedexFlag(nationalNum, caseId);
        if (NationalPokedexNumToSpecies(nationalNum) == SPECIES_UNOWN)
            gSaveBlock2Ptr->pokedex.unownPersonality = personality;
        if (NationalPokedexNumToSpecies(nationalNum) == SPECIES_SPINDA)
            gSaveBlock2Ptr->pokedex.spindaPersonality = personality;
    }
}

bool8 HasTwoFramesAnimation(u16 species)
{
    return P_TWO_FRAME_FRONT_SPRITES
        && gSpeciesInfo[species].frontAnimFrames != sAnims_SingleFramePlaceHolder
        && species != SPECIES_UNOWN
        && !gTestRunnerHeadless;
}

static bool8 ShouldSkipFriendshipChange(void)
{
    if (gMain.inBattle && gBattleTypeFlags & (BATTLE_TYPE_FRONTIER))
        return TRUE;
    if (!gMain.inBattle && (InBattlePike() || InBattlePyramid()))
        return TRUE;
    return FALSE;
}

// The below functions are for the 'MonSpritesGfxManager', a method of allocating
// space for Pokémon sprites. These are only used for the summary screen Pokémon
// sprites (unless gMonSpritesGfxPtr is in use), but were set up for more general use.
// Only the 'default' mode (MON_SPR_GFX_MODE_NORMAL) is used, which is set
// up to allocate 4 sprites using the battler sprite templates (gBattlerSpriteTemplates).
// MON_SPR_GFX_MODE_BATTLE is identical but never used.
// MON_SPR_GFX_MODE_FULL_PARTY is set up to allocate 7 sprites (party + trainer?)
// using a generic 64x64 template, and is also never used.

// Between the unnecessarily large sizes below, a mistake allocating the spritePointers
// field, and the fact that ultimately only 1 of the 4 sprite positions is used, this
// system wastes a good deal of memory.

#define ALLOC_FAIL_BUFFER (1 << 0)
#define ALLOC_FAIL_STRUCT (1 << 1)
#define GFX_MANAGER_ACTIVE 0xA3 // Arbitrary value

static void InitMonSpritesGfx_Battle(struct MonSpritesGfxManager *gfx)
{
    u16 i, j;
    for (i = 0; i < gfx->numSprites; i++)
    {
        gfx->templates[i] = gBattlerSpriteTemplates[i];
        for (j = 0; j < gfx->numFrames; j++)
            gfx->frameImages[i * gfx->numFrames + j].data = &gfx->spritePointers[i][j * MON_PIC_SIZE];

        gfx->templates[i].images = &gfx->frameImages[i * gfx->numFrames];
    }
}

static void InitMonSpritesGfx_FullParty(struct MonSpritesGfxManager *gfx)
{
    u16 i, j;
    for (i = 0; i < gfx->numSprites; i++)
    {
        gfx->templates[i] = sSpriteTemplate_64x64;
        for (j = 0; j < gfx->numFrames; j++)
            gfx->frameImages[i * gfx->numSprites + j].data = &gfx->spritePointers[i][j * MON_PIC_SIZE];

        gfx->templates[i].images = &gfx->frameImages[i * gfx->numSprites];
        gfx->templates[i].anims = gAnims_MonPic;
        gfx->templates[i].paletteTag = i;
    }
}

struct MonSpritesGfxManager *CreateMonSpritesGfxManager(u8 managerId, u8 mode)
{
    u8 i;
    u8 failureFlags;
    struct MonSpritesGfxManager *gfx;

    failureFlags = 0;
    managerId %= MON_SPR_GFX_MANAGERS_COUNT;
    gfx = AllocZeroed(sizeof(*gfx));
    if (gfx == NULL)
        return NULL;

    switch (mode)
    {
    case MON_SPR_GFX_MODE_FULL_PARTY:
        gfx->numSprites = PARTY_SIZE + 1;
        gfx->numSprites2 = PARTY_SIZE + 1;
        gfx->numFrames = MAX_MON_PIC_FRAMES;
        gfx->dataSize = 1;
        gfx->mode = MON_SPR_GFX_MODE_FULL_PARTY;
        break;
 // case MON_SPR_GFX_MODE_BATTLE:
    case MON_SPR_GFX_MODE_NORMAL:
    default:
        gfx->numSprites = MAX_BATTLERS_COUNT;
        gfx->numSprites2 = MAX_BATTLERS_COUNT;
        gfx->numFrames = MAX_MON_PIC_FRAMES;
        gfx->dataSize = 1;
        gfx->mode = MON_SPR_GFX_MODE_NORMAL;
        break;
    }

    // Set up sprite / sprite pointer buffers
    gfx->spriteBuffer = AllocZeroed(gfx->dataSize * MON_PIC_SIZE * MAX_MON_PIC_FRAMES * gfx->numSprites);
    gfx->spritePointers = AllocZeroed(gfx->numSprites * 32); // ? Only * 4 is necessary, perhaps they were thinking bits.
    if (gfx->spriteBuffer == NULL || gfx->spritePointers == NULL)
    {
        failureFlags |= ALLOC_FAIL_BUFFER;
    }
    else
    {
        for (i = 0; i < gfx->numSprites; i++)
            gfx->spritePointers[i] = gfx->spriteBuffer + (gfx->dataSize * MON_PIC_SIZE * MAX_MON_PIC_FRAMES * i);
    }

    // Set up sprite structs
    gfx->templates = AllocZeroed(sizeof(struct SpriteTemplate) * gfx->numSprites);
    gfx->frameImages = AllocZeroed(sizeof(struct SpriteFrameImage) * gfx->numSprites * gfx->numFrames);
    if (gfx->templates == NULL || gfx->frameImages == NULL)
    {
        failureFlags |= ALLOC_FAIL_STRUCT;
    }
    else
    {
        for (i = 0; i < gfx->numFrames * gfx->numSprites; i++)
            gfx->frameImages[i].size = MON_PIC_SIZE;

        switch (gfx->mode)
        {
        case MON_SPR_GFX_MODE_FULL_PARTY:
            InitMonSpritesGfx_FullParty(gfx);
            break;
        case MON_SPR_GFX_MODE_NORMAL:
        case MON_SPR_GFX_MODE_BATTLE:
        default:
            InitMonSpritesGfx_Battle(gfx);
            break;
        }
    }

    // If either of the allocations failed free their respective members
    if (failureFlags & ALLOC_FAIL_STRUCT)
    {
        TRY_FREE_AND_SET_NULL(gfx->frameImages);
        TRY_FREE_AND_SET_NULL(gfx->templates);
    }
    if (failureFlags & ALLOC_FAIL_BUFFER)
    {
        TRY_FREE_AND_SET_NULL(gfx->spritePointers);
        TRY_FREE_AND_SET_NULL(gfx->spriteBuffer);
    }

    if (failureFlags)
    {
        // Clear, something failed to allocate
        memset(gfx, 0, sizeof(*gfx));
        Free(gfx);
    }
    else
    {
        gfx->active = GFX_MANAGER_ACTIVE;
        sMonSpritesGfxManagers[managerId] = gfx;
    }

    return sMonSpritesGfxManagers[managerId];
}

void DestroyMonSpritesGfxManager(u8 managerId)
{
    struct MonSpritesGfxManager *gfx;

    managerId %= MON_SPR_GFX_MANAGERS_COUNT;
    gfx = sMonSpritesGfxManagers[managerId];
    if (gfx == NULL)
        return;

    if (gfx->active != GFX_MANAGER_ACTIVE)
    {
        memset(gfx, 0, sizeof(*gfx));
    }
    else
    {
        TRY_FREE_AND_SET_NULL(gfx->frameImages);
        TRY_FREE_AND_SET_NULL(gfx->templates);
        TRY_FREE_AND_SET_NULL(gfx->spritePointers);
        TRY_FREE_AND_SET_NULL(gfx->spriteBuffer);
        memset(gfx, 0, sizeof(*gfx));
        Free(gfx);
    }
}

u8 *MonSpritesGfxManager_GetSpritePtr(u8 managerId, u8 spriteNum)
{
    struct MonSpritesGfxManager *gfx = sMonSpritesGfxManagers[managerId % MON_SPR_GFX_MANAGERS_COUNT];
    if (gfx->active != GFX_MANAGER_ACTIVE)
    {
        return NULL;
    }
    else
    {
        if (spriteNum >= gfx->numSprites)
            spriteNum = 0;

        return gfx->spritePointers[spriteNum];
    }
}

u16 GetFormSpeciesId(u16 speciesId, u8 formId)
{
    if (GetSpeciesFormTable(speciesId) != NULL)
        return GetSpeciesFormTable(speciesId)[formId];
    else
        return speciesId;
}

u8 GetFormIdFromFormSpeciesId(u16 formSpeciesId)
{
    u8 targetFormId = 0;

    if (GetSpeciesFormTable(formSpeciesId) != NULL)
    {
        for (targetFormId = 0; GetSpeciesFormTable(formSpeciesId)[targetFormId] != FORM_SPECIES_END; targetFormId++)
        {
            if (formSpeciesId == GetSpeciesFormTable(formSpeciesId)[targetFormId])
                break;
        }
    }
    return targetFormId;
}

// Returns the current species if no form change is possible
u32 GetFormChangeTargetSpecies(struct Pokemon *mon, enum FormChanges method, u32 arg)
{
    return GetFormChangeTargetSpeciesBoxMon(&mon->box, method, arg);
}

// Returns the current species if no form change is possible
u32 GetFormChangeTargetSpeciesBoxMon(struct BoxPokemon *boxMon, enum FormChanges method, u32 arg)
{
    u32 i;
    u32 species = GetBoxMonData(boxMon, MON_DATA_SPECIES, NULL);
    u32 targetSpecies = species;
    const struct FormChange *formChanges = GetSpeciesFormChanges(species);
    u16 heldItem;
    u32 ability;

    if (formChanges != NULL)
    {
        heldItem = GetBoxMonData(boxMon, MON_DATA_HELD_ITEM, NULL);
        ability = GetAbilityBySpecies(species, GetBoxMonData(boxMon, MON_DATA_ABILITY_NUM, NULL));

        for (i = 0; formChanges[i].method != FORM_CHANGE_TERMINATOR; i++)
        {
            if (method == formChanges[i].method && species != formChanges[i].targetSpecies)
            {
                switch (method)
                {
                case FORM_CHANGE_ITEM_HOLD:
                    if ((heldItem == formChanges[i].param1 || formChanges[i].param1 == ITEM_NONE)
                     && (ability == formChanges[i].param2 || formChanges[i].param2 == ABILITY_NONE))
                    {
                        // This is to prevent reverting to base form when giving the item to the corresponding form.
                        // Eg. Giving a Zap Plate to an Electric Arceus without an item (most likely to happen when using givemon)
                        bool32 currentItemForm = FALSE;
                        for (int j = 0; formChanges[j].method != FORM_CHANGE_TERMINATOR; j++)
                        {
                            if (species == formChanges[j].targetSpecies
                                && formChanges[j].param1 == heldItem
                                && formChanges[j].param1 != ITEM_NONE)
                            {
                                currentItemForm = TRUE;
                                break;
                            }
                        }
                        if (!currentItemForm)
                            targetSpecies = formChanges[i].targetSpecies;
                    }
                    break;
                case FORM_CHANGE_ITEM_USE:
                    if (arg == formChanges[i].param1)
                    {
                        bool32 pass = TRUE;
                        switch (formChanges[i].param2)
                        {
                        case DAY:
                            if (GetTimeOfDay() == TIME_NIGHT)
                                pass = FALSE;
                            break;
                        case NIGHT:
                            if (GetTimeOfDay() != TIME_NIGHT)
                                pass = FALSE;
                            break;
                        }

                        if (formChanges[i].param3 != STATUS1_NONE && GetBoxMonData(boxMon, MON_DATA_STATUS, NULL) & formChanges[i].param3)
                            pass = FALSE;

                        if (pass)
                            targetSpecies = formChanges[i].targetSpecies;
                    }
                    break;
                case FORM_CHANGE_ITEM_USE_MULTICHOICE:
                    if (arg == formChanges[i].param1)
                    {
                        if (formChanges[i].param2 == gSpecialVar_Result)
                            targetSpecies = formChanges[i].targetSpecies;
                    }
                    break;
                case FORM_CHANGE_MOVE:
                    if (BoxMonKnowsMove(boxMon, formChanges[i].param1) != formChanges[i].param2)
                        targetSpecies = formChanges[i].targetSpecies;
                    break;
                case FORM_CHANGE_BEGIN_BATTLE:
                case FORM_CHANGE_END_BATTLE:
                    if (heldItem == formChanges[i].param1 || formChanges[i].param1 == ITEM_NONE)
                        targetSpecies = formChanges[i].targetSpecies;
                    break;
                case FORM_CHANGE_END_BATTLE_TERRAIN:
                    if (gBattleEnvironment == formChanges[i].param1)
                        targetSpecies = formChanges[i].targetSpecies;
                    break;
                case FORM_CHANGE_WITHDRAW:
                case FORM_CHANGE_DEPOSIT:
                case FORM_CHANGE_FAINT:
                case FORM_CHANGE_DAYS_PASSED:
                    targetSpecies = formChanges[i].targetSpecies;
                    break;
                case FORM_CHANGE_STATUS:
                    if (GetBoxMonData(boxMon, MON_DATA_STATUS, NULL) & formChanges[i].param1)
                        targetSpecies = formChanges[i].targetSpecies;
                    break;
                case FORM_CHANGE_TIME_OF_DAY:
                    switch (formChanges[i].param1)
                    {
                    case DAY:
                        if (GetTimeOfDay() != TIME_NIGHT)
                            targetSpecies = formChanges[i].targetSpecies;
                        break;
                    case NIGHT:
                        if (GetTimeOfDay() == TIME_NIGHT)
                            targetSpecies = formChanges[i].targetSpecies;
                        break;
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }

    return targetSpecies;
}

void TrySetDayLimitToFormChange(struct Pokemon *mon)
{
    u32 i;
    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    const struct FormChange *formChanges = GetSpeciesFormChanges(species);

    for (i = 0; formChanges != NULL && formChanges[i].method != FORM_CHANGE_TERMINATOR; i++)
    {
        if (formChanges[i].method == FORM_CHANGE_DAYS_PASSED && species != formChanges[i].targetSpecies)
        {
            SetMonData(mon, MON_DATA_DAYS_SINCE_FORM_CHANGE, &formChanges[i].param1);
            break;
        }
    }
}

bool32 DoesSpeciesHaveFormChangeMethod(u16 species, enum FormChanges method)
{
    u32 i;
    const struct FormChange *formChanges = GetSpeciesFormChanges(species);

    for (i = 0; formChanges != NULL && formChanges[i].method != FORM_CHANGE_TERMINATOR; i++)
    {
        if (method == formChanges[i].method && species != formChanges[i].targetSpecies)
            return TRUE;
    }

    return FALSE;
}

u16 MonTryLearningNewMoveEvolution(struct Pokemon *mon, bool8 firstMove)
{
    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    u8 level = GetMonData(mon, MON_DATA_LEVEL, NULL);
    const struct LevelUpMove *learnset = GetSpeciesLevelUpLearnset(species);

    // Since you can learn more than one move per level,
    // the game needs to know whether you decided to
    // learn it or keep the old set to avoid asking
    // you to learn the same move over and over again.
    if (firstMove)
    {
        sLearningMoveTableID = 0;
    }
    while(learnset[sLearningMoveTableID].move != LEVEL_UP_MOVE_END)
    {
        while ((learnset[sLearningMoveTableID].level == 0 || learnset[sLearningMoveTableID].level == level)
             && !(P_EVOLUTION_LEVEL_1_LEARN >= GEN_8 && learnset[sLearningMoveTableID].level == 1))
        {
            //Hardcoding evo move override
            if (species == SPECIES_SKELEDIRGE && FlagGet(FLAG_RESTRICTED_MODE) && learnset[sLearningMoveTableID].move == MOVE_TORCH_SONG){
                gMoveToLearn = MOVE_INFERNO;
            }else{
                gMoveToLearn = learnset[sLearningMoveTableID].move;
            }
            sLearningMoveTableID++;
            return GiveMoveToMon(mon, gMoveToLearn);
        }
        sLearningMoveTableID++;
    }
    return 0;
}

// Removes the selected index from the given IV list and shifts the remaining
// elements to the left.
void RemoveIVIndexFromList(u8 *ivs, u8 selectedIv)
{
    s32 i, j;
    u8 temp[NUM_STATS];

    ivs[selectedIv] = 0xFF;
    for (i = 0; i < NUM_STATS; i++)
    {
        temp[i] = ivs[i];
    }

    j = 0;
    for (i = 0; i < NUM_STATS; i++)
    {
        if (temp[i] != 0xFF)
            ivs[j++] = temp[i];
    }
}

// Attempts to perform non-level/item related overworld evolutions; called by tryspecialevo command.
void TrySpecialOverworldEvo(void)
{
    u8 i;
    bool32 canStopEvo = gSpecialVar_0x8001;
    u16 tryMultiple = gSpecialVar_0x8002;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        u32 targetSpecies = GetEvolutionTargetSpecies(&gPlayerParty[i], EVO_MODE_OVERWORLD_SPECIAL, 0, NULL, &canStopEvo, CHECK_EVO);

        if (targetSpecies != SPECIES_NONE && !(sTriedEvolving & (1u << i)))
        {
            GetEvolutionTargetSpecies(&gPlayerParty[i], EVO_MODE_OVERWORLD_SPECIAL, 0, NULL, &canStopEvo, DO_EVO);
            sTriedEvolving |= 1u << i;
            if(gMain.callback2 == TrySpecialOverworldEvo) // This fixes small graphics glitches.
                EvolutionScene(&gPlayerParty[i], targetSpecies, canStopEvo, i);
            else
                BeginEvolutionScene(&gPlayerParty[i], targetSpecies, canStopEvo, i);

            if (tryMultiple)
                gCB2_AfterEvolution = TrySpecialOverworldEvo;
            else
                gCB2_AfterEvolution = CB2_ReturnToField;
            return;
        }
    }

    sTriedEvolving = 0;
    SetMainCallback2(CB2_ReturnToField);
}

bool32 SpeciesHasGenderDifferences(u16 species)
{
#if P_GENDER_DIFFERENCES
    if (gSpeciesInfo[species].frontPicFemale != NULL
     || gSpeciesInfo[species].backPicFemale != NULL
     || gSpeciesInfo[species].paletteFemale != NULL
     || gSpeciesInfo[species].shinyPaletteFemale != NULL
     || gSpeciesInfo[species].iconSpriteFemale != NULL)
        return TRUE;
#endif

    return FALSE;
}

bool32 TryFormChange(u32 monId, u32 side, enum FormChanges method)
{
    struct Pokemon *party = (side == B_SIDE_PLAYER) ? gPlayerParty : gEnemyParty;

    if (GetMonData(&party[monId], MON_DATA_SPECIES_OR_EGG, 0) == SPECIES_NONE
     || GetMonData(&party[monId], MON_DATA_SPECIES_OR_EGG, 0) == SPECIES_EGG)
        return FALSE;

    u32 currentSpecies = GetMonData(&party[monId], MON_DATA_SPECIES);
    u32 targetSpecies = GetFormChangeTargetSpecies(&party[monId], method, 0);

    if (targetSpecies == currentSpecies && gBattleStruct != NULL && gBattleStruct->changedSpecies[side][monId] != SPECIES_NONE)
        targetSpecies = gBattleStruct->changedSpecies[side][monId];

    if (targetSpecies != currentSpecies)
    {
        TryToSetBattleFormChangeMoves(&party[monId], method);
        SetMonData(&party[monId], MON_DATA_SPECIES, &targetSpecies);
        CalculateMonStats(&party[monId]);
        return TRUE;
    }

    return FALSE;
}

u16 SanitizeSpeciesId(u16 species)
{
    if (species > NUM_SPECIES || !IsSpeciesEnabled(species))
        return SPECIES_NONE;
    else
        return species;
}

bool32 IsSpeciesEnabled(u16 species)
{
    return gSpeciesInfo[species].baseHP > 0 || species == SPECIES_EGG;
}

void TryToSetBattleFormChangeMoves(struct Pokemon *mon, enum FormChanges method)
{
    int i, j;
    u16 species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    const struct FormChange *formChanges = GetSpeciesFormChanges(species);

    if (formChanges == NULL
        || (method != FORM_CHANGE_BEGIN_BATTLE && method != FORM_CHANGE_END_BATTLE))
        return;

    for (i = 0; formChanges[i].method != FORM_CHANGE_TERMINATOR; i++)
    {
        if (formChanges[i].method == method
            && formChanges[i].param2
            && formChanges[i].param3
            && formChanges[i].targetSpecies != species)
        {
            u16 originalMove = formChanges[i].param2;
            u16 newMove = formChanges[i].param3;

            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                u16 currMove = GetMonData(mon, MON_DATA_MOVE1 + j, NULL);
                if (currMove == originalMove)
                    SetMonMoveSlot_KeepPP(mon, newMove, j);
            }
            break;
        }
    }
}

u32 GetMonFriendshipScore(struct Pokemon *pokemon)
{
    u32 friendshipScore = GetMonData(pokemon, MON_DATA_FRIENDSHIP, NULL);

    if (friendshipScore == MAX_FRIENDSHIP)
        return FRIENDSHIP_MAX;
    if (friendshipScore >= 200)
        return FRIENDSHIP_200_TO_254;
    if (friendshipScore >= 150)
        return FRIENDSHIP_150_TO_199;
    if (friendshipScore >= 100)
        return FRIENDSHIP_100_TO_149;
    if (friendshipScore >= 50)
        return FRIENDSHIP_50_TO_99;
    if (friendshipScore >= 1)
        return FRIENDSHIP_1_TO_49;

    return FRIENDSHIP_NONE;
}

u32 GetMonAffectionHearts(struct Pokemon *pokemon)
{
    u32 friendship = GetMonData(pokemon, MON_DATA_FRIENDSHIP, NULL);

    if (friendship == MAX_FRIENDSHIP)
        return AFFECTION_FIVE_HEARTS;
    if (friendship >= 220)
        return AFFECTION_FOUR_HEARTS;
    if (friendship >= 180)
        return AFFECTION_THREE_HEARTS;
    if (friendship >= 130)
        return AFFECTION_TWO_HEARTS;
    if (friendship >= 80)
        return AFFECTION_ONE_HEART;

    return AFFECTION_NO_HEARTS;
}

void UpdateMonPersonality(struct BoxPokemon *boxMon, u32 personality)
{
    struct PokemonSubstruct0 *old0, *new0;
    struct PokemonSubstruct1 *old1, *new1;
    struct PokemonSubstruct2 *old2, *new2;
    struct PokemonSubstruct3 *old3, *new3;
    struct BoxPokemon old;

    bool32 isShiny = GetBoxMonData(boxMon, MON_DATA_IS_SHINY, NULL);
    u32 hiddenNature = GetBoxMonData(boxMon, MON_DATA_HIDDEN_NATURE, NULL);
    u32 teraType = GetBoxMonData(boxMon, MON_DATA_TERA_TYPE, NULL);

    old = *boxMon;
    old0 = &(GetSubstruct(&old, old.personality, 0)->type0);
    old1 = &(GetSubstruct(&old, old.personality, 1)->type1);
    old2 = &(GetSubstruct(&old, old.personality, 2)->type2);
    old3 = &(GetSubstruct(&old, old.personality, 3)->type3);

    new0 = &(GetSubstruct(boxMon, personality, 0)->type0);
    new1 = &(GetSubstruct(boxMon, personality, 1)->type1);
    new2 = &(GetSubstruct(boxMon, personality, 2)->type2);
    new3 = &(GetSubstruct(boxMon, personality, 3)->type3);

    DecryptBoxMon(&old);
    boxMon->personality = personality;
    *new0 = *old0;
    *new1 = *old1;
    *new2 = *old2;
    *new3 = *old3;
    boxMon->checksum = CalculateBoxMonChecksum(boxMon);
    EncryptBoxMon(boxMon);

    SetBoxMonData(boxMon, MON_DATA_IS_SHINY, &isShiny);
    SetBoxMonData(boxMon, MON_DATA_HIDDEN_NATURE, &hiddenNature);
    SetBoxMonData(boxMon, MON_DATA_TERA_TYPE, &teraType);
}

void HealPokemon(struct Pokemon *mon)
{
    u32 data;

    data = GetMonData(mon, MON_DATA_MAX_HP);
    SetMonData(mon, MON_DATA_HP, &data);

    data = STATUS1_NONE;
    SetMonData(mon, MON_DATA_STATUS, &data);

    MonRestorePP(mon);
}

void HealBoxPokemon(struct BoxPokemon *boxMon)
{
    u32 data;

    data = 0;
    SetBoxMonData(boxMon, MON_DATA_HP_LOST, &data);

    data = STATUS1_NONE;
    SetBoxMonData(boxMon, MON_DATA_STATUS, &data);

    BoxMonRestorePP(boxMon);
}

u16 GetCryIdBySpecies(u16 species)
{
    species = SanitizeSpeciesId(species);
    if (P_CRIES_ENABLED == FALSE || gSpeciesInfo[species].cryId >= CRY_COUNT || gTestRunnerHeadless)
        return CRY_NONE;
    return gSpeciesInfo[species].cryId;
}

u16 GetSpeciesPreEvolution(u16 species)
{
    int i, j;

    for (i = SPECIES_BULBASAUR; i < NUM_SPECIES; i++)
    {
        const struct Evolution *evolutions = GetSpeciesEvolutions(i);
        if (evolutions == NULL)
            continue;
        for (j = 0; evolutions[j].method != EVOLUTIONS_END; j++)
        {
            if (SanitizeSpeciesId(evolutions[j].targetSpecies) == species)
                return i;
        }
    }

    return SPECIES_NONE;
}

void UpdateDaysPassedSinceFormChange(u16 days)
{
    u32 i;
    for (i = 0; i < PARTY_SIZE; i++)
    {
        struct Pokemon *mon = &gPlayerParty[i];
        u32 currentSpecies = GetMonData(mon, MON_DATA_SPECIES);
        u8 daysSinceFormChange;

        if (currentSpecies == SPECIES_NONE)
            continue;

        daysSinceFormChange = GetMonData(mon, MON_DATA_DAYS_SINCE_FORM_CHANGE, 0);
        if (daysSinceFormChange == 0)
            continue;

        if (daysSinceFormChange > days)
            daysSinceFormChange -= days;
        else
            daysSinceFormChange = 0;

        SetMonData(mon, MON_DATA_DAYS_SINCE_FORM_CHANGE, &daysSinceFormChange);

        if (daysSinceFormChange == 0)
        {
            u32 targetSpecies = GetFormChangeTargetSpecies(mon, FORM_CHANGE_DAYS_PASSED, 0);

            if (targetSpecies != currentSpecies)
            {
                SetMonData(mon, MON_DATA_SPECIES, &targetSpecies);
                CalculateMonStats(mon);
            }
        }
    }
}

u32 CheckDynamicMoveType(struct Pokemon *mon, u32 move, u32 battler, enum MonState state)
{
    u32 moveType = GetDynamicMoveType(mon, move, battler, state);
    if (moveType != TYPE_NONE)
        return moveType;
    return GetMoveType(move);
}

uq4_12_t GetDynamaxLevelHPMultiplier(u32 dynamaxLevel, bool32 inverseMultiplier)
{
    if (inverseMultiplier)
        return UQ_4_12(1.0/(1.5 + 0.05 * dynamaxLevel));
    return UQ_4_12(1.5 + 0.05 * dynamaxLevel);
}

bool32 IsSpeciesRegionalForm(u32 species)
{
    return gSpeciesInfo[species].isAlolanForm
        || gSpeciesInfo[species].isGalarianForm
        || gSpeciesInfo[species].isHisuianForm
        || gSpeciesInfo[species].isPaldeanForm;
}

bool32 IsSpeciesRegionalFormFromRegion(u32 species, u32 region)
{
    switch (region)
    {
    case REGION_ALOLA:  return gSpeciesInfo[species].isAlolanForm;
    case REGION_GALAR:  return gSpeciesInfo[species].isGalarianForm;
    case REGION_HISUI:  return gSpeciesInfo[species].isHisuianForm;
    case REGION_PALDEA: return gSpeciesInfo[species].isPaldeanForm;
    default:            return FALSE;
    }
}

bool32 SpeciesHasRegionalForm(u32 species)
{
    u32 formId;
    const u16 *formTable = GetSpeciesFormTable(species);
    for (formId = 0; formTable != NULL && formTable[formId] != FORM_SPECIES_END; formId++)
    {
        if (IsSpeciesRegionalForm(formTable[formId]))
            return TRUE;
    }
    return FALSE;
}

u32 GetRegionalFormByRegion(u32 species, u32 region)
{
    u32 formId = 0;
    u32 firstFoundSpecies = 0;
    const u16 *formTable = GetSpeciesFormTable(species);

    if (formTable != NULL)
    {
        for (formId = 0; formTable[formId] != FORM_SPECIES_END; formId++)
        {
            if (firstFoundSpecies == 0)
                firstFoundSpecies = formTable[formId];

            if (IsSpeciesRegionalFormFromRegion(formTable[formId], region))
                return formTable[formId];
        }
        if (firstFoundSpecies != 0)
            return firstFoundSpecies;
    }
    return species;
}

bool32 IsSpeciesForeignRegionalForm(u32 species, u32 currentRegion)
{
    u32 i;
    for (i = 0; i < REGIONS_COUNT; i++)
    {
        if (currentRegion != i && IsSpeciesRegionalFormFromRegion(species, i))
            return TRUE;
        else if (currentRegion == i && SpeciesHasRegionalForm(species) && !IsSpeciesRegionalFormFromRegion(species, i))
            return TRUE;
    }
    return FALSE;
}

u32 GetTeraTypeFromPersonality(struct Pokemon *mon)
{
    const u8 *types = gSpeciesInfo[GetMonData(mon, MON_DATA_SPECIES)].types;
    return (GetMonData(mon, MON_DATA_PERSONALITY) & 0x1) == 0 ? types[0] : types[1];
}


u32 CalcTierPointsAfterEvolution(u8 partyId, u16 newSpecies)
{
    u32 total = 0;
    for (u8 i = 0; i < gPlayerPartyCount; i++) {
        if (i == partyId) {
            total += GetMonTierPoints(newSpecies);
        } else {
            u16 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL);
            if (species != SPECIES_NONE)
                total += GetMonTierPoints(species);
        }
    }
    return total;
}


u8 GetMonTierPoints(u16 species){
    //Start with default point value
    u8 defaultPointValue = 3;
    //species simplification
    if (species >= SPECIES_SAWSBUCK_SUMMER && species <= SPECIES_SAWSBUCK_WINTER){
        species = SPECIES_SAWSBUCK;
    }
    else if (species >= SPECIES_SCATTERBUG_POLAR && species <= SPECIES_SCATTERBUG_POKEBALL){
        species = SPECIES_SCATTERBUG;
    }
    else if (species >= SPECIES_SPEWPA_POLAR && species <= SPECIES_SPEWPA_POKEBALL){
        species = SPECIES_SPEWPA;
    }
    else if (species >= SPECIES_VIVILLON_POLAR && species <= SPECIES_VIVILLON_POKEBALL){
        species = SPECIES_VIVILLON;
    }else if  (species >= SPECIES_MINIOR_ORANGE && species <= SPECIES_MINIOR_CORE_VIOLET){
        species = SPECIES_MINIOR;
    }else if (species >= SPECIES_SILVALLY_FIGHTING && species <= SPECIES_SILVALLY_FAIRY){
        species = SPECIES_SILVALLY;
    }else if (species >= SPECIES_ALCREMIE_STRAWBERRY_RUBY_CREAM && species <= SPECIES_ALCREMIE_STRAWBERRY_RAINBOW_SWIRL){
        species = SPECIES_ALCREMIE;
    }
    else if (species >= SPECIES_ALCREMIE_BERRY_VANILLA_CREAM && species <= SPECIES_ALCREMIE_RIBBON_RAINBOW_SWIRL){
        species = SPECIES_ALCREMIE;
    }else if (species >= SPECIES_SQUAWKABILLY_GREEN && species <= SPECIES_SQUAWKABILLY_WHITE){
        species = SPECIES_SQUAWKABILLY;
    }else if (species >= SPECIES_PUMPKABOO_SMALL && species <= SPECIES_PUMPKABOO_SUPER){
        species = SPECIES_PUMPKABOO;
    }else if (species >= SPECIES_GOURGEIST_SMALL && species <= SPECIES_GOURGEIST_SUPER){
        species = SPECIES_GOURGEIST;
    }else if (species >= SPECIES_FLABEBE_YELLOW && species <= SPECIES_FLABEBE_WHITE){
        species = SPECIES_FLABEBE;
    }
    else if (species >= SPECIES_FLOETTE_YELLOW && species <= SPECIES_FLOETTE_WHITE){
        species = SPECIES_FLOETTE;
    }else if (species >= SPECIES_FLORGES_YELLOW && species <= SPECIES_FLORGES_WHITE){
        species = SPECIES_FLORGES;
    }

    switch(species){
        //6 Points Kanto
        case SPECIES_SLOWBRO_MEGA: case SPECIES_KANGASKHAN_MEGA:
        case SPECIES_CHARIZARD_MEGA_Y: //Inaccessible in Restricted Mode
        case SPECIES_CHANSEY:
        
        //6 Points Johto
        case SPECIES_BLISSEY: 
        
        //6 Points Hoenn
        case SPECIES_SHEDINJA: case SPECIES_SALAMENCE_MEGA: case SPECIES_METAGROSS_MEGA:
        
        //6 Points Sinnoh
        case SPECIES_LUCARIO_MEGA: case SPECIES_DARKRAI:
        
        //6 Points Kalos / Regionals
        case SPECIES_AEGISLASH: case SPECIES_GOODRA_HISUI:
        
        //6 Points Alola
        case SPECIES_MARSHADOW: case SPECIES_MAGEARNA: case SPECIES_MELMETAL: 
        
        //6 Points Galar
        case SPECIES_DRAGAPULT: case SPECIES_URSHIFU_SINGLE_STRIKE: case SPECIES_URSHIFU_RAPID_STRIKE:
        
        //6 Points Paldea
        case SPECIES_PALAFIN: case SPECIES_ARCHALUDON: case SPECIES_ANNIHILAPE: case SPECIES_GLIMMORA: case SPECIES_IRON_HANDS:
        
        //6 Points Past Paradox
        case SPECIES_GOUGING_FIRE: case SPECIES_RAGING_BOLT: case SPECIES_WALKING_WAKE: case SPECIES_GREAT_TUSK: case SPECIES_ROARING_MOON:
        
        //6 Points Future Paradox
        case SPECIES_IRON_VALIANT:
            return 6;
        
        //5 Points Kanto / Regionals
        case SPECIES_ARCANINE_HISUI: case SPECIES_SLOWBRO: case SPECIES_SNORLAX: case SPECIES_ZAPDOS: case SPECIES_DRAGONITE:
        
        //5 Points Kanto Megas
        case SPECIES_VENUSAUR_MEGA: case SPECIES_CHARIZARD_MEGA_X: case SPECIES_BEEDRILL_MEGA: case SPECIES_PINSIR_MEGA:
        case SPECIES_GYARADOS_MEGA: case SPECIES_AERODACTYL_MEGA:
        case SPECIES_ALAKAZAM_MEGA: case SPECIES_GENGAR_MEGA: //Potentially move these two to 4 points; under review
        
        //5 Points Johto / Regionals
        case SPECIES_TYPHLOSION_HISUI: case SPECIES_CROBAT: case SPECIES_SLOWKING: case SPECIES_SLOWKING_GALAR:
        case SPECIES_SCIZOR: case SPECIES_STEELIX: case SPECIES_SKARMORY: case SPECIES_TYRANITAR:

        //5 Points Johto Megas
        case SPECIES_STEELIX_MEGA: case SPECIES_SCIZOR_MEGA: case SPECIES_HOUNDOOM_MEGA: case SPECIES_TYRANITAR_MEGA:

        //5 Points Hoenn
        case SPECIES_BLAZIKEN: case SPECIES_MILOTIC: case SPECIES_SALAMENCE: case SPECIES_LATIAS: case SPECIES_LATIOS:

        //5 Points Hoenn Megas
        case SPECIES_SCEPTILE_MEGA: case SPECIES_SWAMPERT_MEGA: case SPECIES_BLAZIKEN_MEGA: 
        case SPECIES_LATIAS_MEGA: case SPECIES_LATIOS_MEGA: case SPECIES_MEDICHAM_MEGA: case SPECIES_AGGRON_MEGA: case SPECIES_MAWILE_MEGA:
        case SPECIES_SHARPEDO_MEGA: case SPECIES_SABLEYE_MEGA: case SPECIES_GARDEVOIR_MEGA:

        //5 Points Sinnoh
        case SPECIES_INFERNAPE: case SPECIES_GARCHOMP: case SPECIES_TANGROWTH: case SPECIES_TOGEKISS: case SPECIES_AZELF: case SPECIES_HEATRAN: 
        case SPECIES_MANAPHY: case SPECIES_SHAYMIN_SKY:

        //5 Points Sinnoh Megas
        case SPECIES_GARCHOMP_MEGA: case SPECIES_LOPUNNY_MEGA: case SPECIES_GALLADE_MEGA:

        //5 Points Unova / Regionals
        case SPECIES_EXCADRILL: case SPECIES_DARMANITAN: case SPECIES_DARMANITAN_GALAR: case SPECIES_DARMANITAN_GALAR_ZEN: case SPECIES_AMOONGUSS: case SPECIES_ALOMOMOLA:
        case SPECIES_FERROTHORN: case SPECIES_VOLCARONA: 
        case SPECIES_TERRAKION: case SPECIES_TORNADUS_THERIAN: case SPECIES_LANDORUS_INCARNATE: case SPECIES_LANDORUS_THERIAN: case SPECIES_GENESECT:
        
        //5 Points Kalos / Regionals
        case SPECIES_GRENINJA: case SPECIES_HAWLUCHA:
        case SPECIES_FLORGES: case SPECIES_FLORGES_BLUE: case SPECIES_FLORGES_ORANGE: case SPECIES_FLORGES_WHITE: case SPECIES_FLORGES_YELLOW:
        case SPECIES_ZYGARDE:
        
        //5 Points Kalos Megas
        case SPECIES_DIANCIE_MEGA:

        //5 Points Alola
        case SPECIES_PRIMARINA: case SPECIES_TOXAPEX: case SPECIES_GOLISOPOD: case SPECIES_MIMIKYU:
        case SPECIES_TAPU_KOKO: case SPECIES_TAPU_FINI: case SPECIES_TAPU_LELE: case SPECIES_NIHILEGO: case SPECIES_BUZZWOLE: case SPECIES_CELESTEELA: case SPECIES_ZERAORA:

        //5 Points Galar
        case SPECIES_RILLABOOM: case SPECIES_CINDERACE: case SPECIES_CORVIKNIGHT: case SPECIES_OBSTAGOON: case SPECIES_DRACOVISH:

        //5 Points Hisui 
        case SPECIES_URSALUNA: case SPECIES_BASCULEGION_M: case SPECIES_BASCULEGION_F: case SPECIES_SNEASLER: case SPECIES_ENAMORUS:

        //5 Points Paldea
        case SPECIES_MEOWSCARADA: case SPECIES_SKELEDIRGE: case SPECIES_GARGANACL: case SPECIES_DONDOZO: case SPECIES_GHOLDENGO: case SPECIES_KINGAMBIT:
        case SPECIES_IRON_MOTH: case SPECIES_BAXCALIBUR: case SPECIES_TING_LU:
        case SPECIES_URSALUNA_BLOODMOON: case SPECIES_IRON_BOULDER: case SPECIES_IRON_CROWN: case SPECIES_PECHARUNT:
        case SPECIES_HYDRAPPLE: case SPECIES_DIPPLIN: case SPECIES_OGERPON: case SPECIES_OGERPON_CORNERSTONE: case SPECIES_OGERPON_HEARTHFLAME: case SPECIES_OGERPON_WELLSPRING:
        //5 Points Paldea Eviolite
        case SPECIES_GLIMMET:
            return 5;
        
        //4 Points Kanto/Regionals
        case SPECIES_VENUSAUR: case SPECIES_CHARIZARD: case SPECIES_ARCANINE: case SPECIES_SLOWBRO_GALAR: case SPECIES_CLEFABLE: 
        case SPECIES_DUGTRIO_ALOLA: case SPECIES_ALAKAZAM: case SPECIES_MAROWAK: case SPECIES_MAROWAK_ALOLA: case SPECIES_NIDOKING: 
        case SPECIES_MUK_ALOLA: case SPECIES_GENGAR: case SPECIES_TAUROS: case SPECIES_TAUROS_PALDEA_AQUA: case SPECIES_TAUROS_PALDEA_BLAZE: 
        case SPECIES_TAUROS_PALDEA_COMBAT: case SPECIES_SCYTHER: case SPECIES_GYARADOS: case SPECIES_LAPRAS: case SPECIES_VAPOREON: 
        case SPECIES_OMASTAR: case SPECIES_KABUTOPS: case SPECIES_AERODACTYL: case SPECIES_ARTICUNO_GALAR: case SPECIES_ZAPDOS_GALAR: 
        case SPECIES_MOLTRES_GALAR: case SPECIES_MOLTRES: case SPECIES_STARMIE: case SPECIES_MEW: case SPECIES_CLOYSTER:
        //4 Points Kanto Eviolite
        case SPECIES_PRIMEAPE: case SPECIES_MAGNETON: case SPECIES_RHYDON:

        //4 Points Kanto Megas
        case SPECIES_BLASTOISE_MEGA: case SPECIES_PIDGEOT_MEGA:

        //4 Points Johto
        case SPECIES_TYPHLOSION: case SPECIES_AZUMARILL: case SPECIES_JUMPLUFF: case SPECIES_FORRETRESS: case SPECIES_ESPEON: case SPECIES_UMBREON: case SPECIES_HERACROSS: case SPECIES_KINGDRA:
        case SPECIES_URSARING: case SPECIES_PORYGON2: case SPECIES_RAIKOU: case SPECIES_ENTEI: case SPECIES_SUICUNE: case SPECIES_CELEBI:

        //4 Points Johto Megas
        case SPECIES_AMPHAROS_MEGA: case SPECIES_HERACROSS_MEGA:
        
        //4 Points Hoenn
        case SPECIES_SWAMPERT: case SPECIES_SWELLOW: case SPECIES_GARDEVOIR: case SPECIES_SLAKING: case SPECIES_AGGRON: case SPECIES_SHARPEDO: 
        case SPECIES_ZANGOOSE: case SPECIES_ARMALDO: case SPECIES_METAGROSS: case SPECIES_REGISTEEL: case SPECIES_JIRACHI:
        case SPECIES_MEDICHAM:

        //4 Points Hoenn Megas
        case SPECIES_GLALIE_MEGA: case SPECIES_BANETTE_MEGA: case SPECIES_ABSOL_MEGA: case SPECIES_MANECTRIC_MEGA: case SPECIES_CAMERUPT_MEGA: case SPECIES_ALTARIA_MEGA:

        //4 Points Sinnoh
        case SPECIES_TORTERRA: case SPECIES_EMPOLEON: case SPECIES_STARAPTOR: case SPECIES_ROSERADE: case SPECIES_BRONZONG: case SPECIES_LUCARIO: case SPECIES_HIPPOWDON:
        case SPECIES_DRAPION: case SPECIES_WEAVILE: case SPECIES_MAGNEZONE: case SPECIES_RHYPERIOR: case SPECIES_GLISCOR: case SPECIES_MAMOSWINE: case SPECIES_GALLADE:
        case SPECIES_AMBIPOM: case SPECIES_FLOATZEL: case SPECIES_PORYGON_Z: case SPECIES_ROTOM_WASH: case SPECIES_CRESSELIA: case SPECIES_SHAYMIN:
        case SPECIES_YANMEGA: case SPECIES_MISMAGIUS:

        //4 Points Sinnoh Megas
        case SPECIES_ABOMASNOW_MEGA:

        //4 Points Unova/Regionals
        case SPECIES_VICTINI: case SPECIES_SAMUROTT: case SPECIES_SAMUROTT_HISUI: case SPECIES_GIGALITH: case SPECIES_CONKELDURR: case SPECIES_SAWK: 
        case SPECIES_WHIMSICOTT: case SPECIES_SCOLIPEDE: case SPECIES_LILLIGANT_HISUI: case SPECIES_KROOKODILE: 
        case SPECIES_ZOROARK: case SPECIES_ZOROARK_HISUI: case SPECIES_REUNICLUS: case SPECIES_ARCHEOPS: case SPECIES_ESCAVALIER:
        case SPECIES_CHANDELURE: case SPECIES_HAXORUS: case SPECIES_MIENSHAO: case SPECIES_MANDIBUZZ: case SPECIES_DURANT: case SPECIES_HYDREIGON: case SPECIES_COBALION:
        case SPECIES_CINCCINO:  case SPECIES_CRUSTLE:  case SPECIES_TORNADUS: case SPECIES_KELDEO: case SPECIES_MELOETTA: case SPECIES_MELOETTA_PIROUETTE:
        case SPECIES_BISHARP: //Eviolite basis

        //4 Points Unova Megas
        case SPECIES_AUDINO_MEGA:

        //4 Points Kalos
        case SPECIES_CHESNAUGHT: case SPECIES_DELPHOX: case SPECIES_DIGGERSBY: case SPECIES_TALONFLAME: case SPECIES_SYLVEON: case SPECIES_GOODRA: case SPECIES_KLEFKI:
        case SPECIES_AVALUGG: case SPECIES_AVALUGG_HISUI: case SPECIES_NOIVERN: case SPECIES_DIANCIE: case SPECIES_HOOPA: case SPECIES_VOLCANION:
        //4 Points Kalos/Regionals Eviolite Mons
        case SPECIES_SLIGGOO_HISUI:

        //4 Points Alola
        case SPECIES_INCINEROAR: case SPECIES_MUDSDALE: case SPECIES_ARAQUANID: case SPECIES_SALAZZLE: case SPECIES_TOGEDEMARU: case SPECIES_TAPU_BULU: case SPECIES_KOMMO_O:
        case SPECIES_XURKITREE: case SPECIES_STAKATAKA: case SPECIES_NECROZMA:

        //4 Points Galar
        case SPECIES_INTELEON: case SPECIES_ELDEGOSS: case SPECIES_DREDNAW: case SPECIES_BARRASKEWDA: case SPECIES_COALOSSAL: case SPECIES_HATTERENE: case SPECIES_GRIMMSNARL: 
        case SPECIES_PERRSERKER: case SPECIES_EISCUE: case SPECIES_INDEEDEE_F: case SPECIES_INDEEDEE_M: case SPECIES_FALINKS:
        case SPECIES_DRACOZOLT: case SPECIES_GLASTRIER: case SPECIES_ZARUDE: case SPECIES_REGIELEKI: case SPECIES_REGIDRAGO: 
        
        //4 Points Hisui
        case SPECIES_KLEAVOR: case SPECIES_ENAMORUS_THERIAN:

        //4 Points Paldea
        case SPECIES_QUAQUAVAL: case SPECIES_BELLIBOLT: case SPECIES_LOKIX: case SPECIES_PAWMOT: case SPECIES_MAUSHOLD_THREE: case SPECIES_MAUSHOLD_FOUR: case SPECIES_DACHSBUN:
        case SPECIES_ARBOLIVA: case SPECIES_TINKATON: case SPECIES_ARMAROUGE: case SPECIES_CERULEDGE: case SPECIES_CYCLIZAR: case SPECIES_ORTHWORM: case SPECIES_FLAMIGO:
        case SPECIES_FARIGIRAF: case SPECIES_CLODSIRE: case SPECIES_WO_CHIEN: case SPECIES_BRUTE_BONNET: case SPECIES_SCREAM_TAIL: case SPECIES_SANDY_SHOCKS: case SPECIES_IRON_TREADS:
        case SPECIES_IRON_JUGULIS: case SPECIES_IRON_THORNS: case SPECIES_SLITHER_WING: case SPECIES_TERAPAGOS: case SPECIES_IRON_LEAVES: 
        case SPECIES_FEZANDIPITI: case SPECIES_MUNKIDORI: case SPECIES_OKIDOGI: case SPECIES_ESPATHRA: case SPECIES_KLAWF:
            return 4;
        
        //3 Points Kanto/Regionals
        case SPECIES_BLASTOISE: case SPECIES_RATICATE: case SPECIES_RAICHU: case SPECIES_RAICHU_ALOLA: case SPECIES_SANDSLASH: case SPECIES_NIDOQUEEN:  case SPECIES_NINETALES: 
        case SPECIES_NINETALES_ALOLA: case SPECIES_VILEPLUME: case SPECIES_PERSIAN_ALOLA: case SPECIES_DUGTRIO: case SPECIES_POLIWRATH: case SPECIES_MACHAMP: 
        case SPECIES_TENTACRUEL: case SPECIES_GOLEM: case SPECIES_GOLEM_ALOLA: case SPECIES_MUK: case SPECIES_ELECTRODE_HISUI: case SPECIES_KINGLER:
        case SPECIES_DODRIO: case SPECIES_EXEGGUTOR: case SPECIES_EXEGGUTOR_ALOLA: case SPECIES_HITMONLEE:
        case SPECIES_WEEZING: case SPECIES_WEEZING_GALAR: case SPECIES_KANGASKHAN: case SPECIES_JYNX: case SPECIES_PINSIR: case SPECIES_MR_MIME: case SPECIES_MR_MIME_GALAR:
        case SPECIES_JOLTEON: case SPECIES_ARTICUNO: case SPECIES_RAPIDASH: case SPECIES_RAPIDASH_GALAR:
        //3 Points Kanto Eviolite
        case SPECIES_DRAGONAIR: case SPECIES_GOLBAT: case SPECIES_GRAVELER: case SPECIES_GRAVELER_ALOLA: case SPECIES_MACHOKE: 
        case SPECIES_TANGELA: case SPECIES_ELECTABUZZ: case SPECIES_MAGMAR: 
            return 3;

        //3 Points Johto/Regionals
        case SPECIES_MEGANIUM: case SPECIES_LANTURN: case SPECIES_FERALIGATR: case SPECIES_AMPHAROS: case SPECIES_BELLOSSOM: case SPECIES_SUDOWOODO:
        case SPECIES_POLITOED: case SPECIES_WOBBUFFET: case SPECIES_SHUCKLE: case SPECIES_MANTINE: case SPECIES_HOUNDOOM: case SPECIES_DONPHAN:
        case SPECIES_SMEARGLE: case SPECIES_HITMONTOP: case SPECIES_MILTANK:
        //3 Points Johto/Regionals Eviolite
        case SPECIES_GLIGAR: case SPECIES_PUPITAR: case SPECIES_SNEASEL: case SPECIES_SNEASEL_HISUI:
        case SPECIES_QWILFISH_HISUI: case SPECIES_TOGETIC: case SPECIES_SKIPLOOM: case SPECIES_CORSOLA_GALAR: case SPECIES_GIRAFARIG:
            return 3;
        
        //3 Points Hoenn/Regionals
        case SPECIES_SCEPTILE: case SPECIES_LUDICOLO: case SPECIES_BRELOOM: case SPECIES_HARIYAMA: case SPECIES_NINJASK:
        case SPECIES_MANECTRIC: case SPECIES_TORKOAL: case SPECIES_GRUMPIG: case SPECIES_FLYGON:
        case SPECIES_CRAWDAUNT: case SPECIES_KECLEON: case SPECIES_WALREIN: case SPECIES_GOREBYSS:
        case SPECIES_RELICANTH: case SPECIES_REGICE: case SPECIES_REGIROCK: case SPECIES_DEOXYS_DEFENSE:
        //3 Points Hoenn/Regionals Eviolite
        case SPECIES_METANG: case SPECIES_SHELGON: case SPECIES_LAIRON: case SPECIES_VIGOROTH: case SPECIES_DUSCLOPS:
            return 3;

        //3 Points Sinnoh/Regionals
        case SPECIES_LUXRAY: case SPECIES_BASTIODON: case SPECIES_GASTRODON: case SPECIES_GASTRODON_EAST:
        case SPECIES_DRIFBLIM: case SPECIES_TOXICROAK: case SPECIES_LICKILICKY: case SPECIES_ELECTIVIRE: case SPECIES_MAGMORTAR:
        case SPECIES_DUSKNOIR: case SPECIES_PROBOPASS: case SPECIES_FROSLASS: case SPECIES_ROTOM_HEAT: case SPECIES_ROTOM_FAN:
        case SPECIES_ROTOM_MOW:  case SPECIES_ROTOM: case SPECIES_MESPRIT: case SPECIES_UXIE: case SPECIES_REGIGIGAS: 
        //3 Points Sinnoh Eviolite
        case SPECIES_MUNCHLAX: case SPECIES_GABITE:
            return 3;

        //3 Points Unova/Regionals
        case SPECIES_SERPERIOR: case SPECIES_EMBOAR: case SPECIES_STOUTLAND: case SPECIES_MUSHARNA: case SPECIES_UNFEZANT: 
        case SPECIES_ZEBSTRIKA: case SPECIES_SEISMITOAD: case SPECIES_THROH: case SPECIES_LILLIGANT: case SPECIES_SIGILYPH:
        case SPECIES_COFAGRIGUS: case SPECIES_CARRACOSTA: case SPECIES_SAWSBUCK: case SPECIES_JELLICENT: case SPECIES_GOTHITELLE: 
        case SPECIES_GALVANTULA: case SPECIES_KLINKLANG: case SPECIES_ACCELGOR: case SPECIES_STUNFISK: case SPECIES_STUNFISK_GALAR:
        case SPECIES_GOLURK: case SPECIES_BRAVIARY: case SPECIES_BRAVIARY_HISUI: case SPECIES_VIRIZION:
        //3 Points Unova Eviolite
        case SPECIES_ZWEILOUS: case SPECIES_FOONGUS: case SPECIES_FERROSEED: case SPECIES_VULLABY:
        case SPECIES_BOLDORE: case SPECIES_GURDURR: case SPECIES_COTTONEE:
            return 3;

        //3 Points Kalos/Regionals
        case SPECIES_VIVILLON: case SPECIES_PYROAR: case SPECIES_GOGOAT: case SPECIES_PANGORO: case SPECIES_FURFROU:
        case SPECIES_MEOWSTIC: case SPECIES_MEOWSTIC_F: case SPECIES_AURORUS: case SPECIES_TYRANTRUM: case SPECIES_AROMATISSE:
        case SPECIES_SLURPUFF: case SPECIES_BARBARACLE: case SPECIES_DRAGALGE: case SPECIES_HELIOLISK: case SPECIES_CARBINK: 
        case SPECIES_TREVENANT: case SPECIES_ZYGARDE_10:
        
        //3 Points Kalos Eviolite Mons
        case SPECIES_DOUBLADE: case SPECIES_SLIGGOO: case SPECIES_FLOETTE:
            return 3;
        
        //3 Points Alola
        case SPECIES_DECIDUEYE_HISUI: case SPECIES_DECIDUEYE: case SPECIES_VIKAVOLT:
        case SPECIES_ORICORIO_POM_POM: case SPECIES_ORICORIO_BAILE: case SPECIES_ORICORIO_PAU: case SPECIES_ORICORIO_SENSU: 
        case SPECIES_RIBOMBEE: case SPECIES_LYCANROC_DUSK: case SPECIES_LYCANROC_MIDDAY:
        case SPECIES_WISHIWASHI: case SPECIES_WISHIWASHI_SCHOOL: case SPECIES_SHIINOTIC: case SPECIES_BEWEAR:
        case SPECIES_TSAREENA: case SPECIES_COMFEY: case SPECIES_PASSIMIAN: case SPECIES_PALOSSAND: case SPECIES_PYUKUMUKU:
        case SPECIES_SILVALLY: case SPECIES_MINIOR: case SPECIES_KOMALA: case SPECIES_TURTONATOR: case SPECIES_DRAMPA:
        case SPECIES_BRUXISH: case SPECIES_GUZZLORD: 
        //4 Points Alola Eviolite Mons
        case SPECIES_HAKAMO_O: case SPECIES_MAREANIE: case SPECIES_WIMPOD: case SPECIES_TYPE_NULL:
            return 3;
        //3 Points Galar
        case SPECIES_GREEDENT: case SPECIES_ORBEETLE: case SPECIES_DUBWOOL: case SPECIES_BOLTUND:
        case SPECIES_APPLETUN: case SPECIES_SANDACONDA: case SPECIES_GRAPPLOCT: case SPECIES_CENTISKORCH:
        case SPECIES_CURSOLA: case SPECIES_TOXTRICITY_AMPED: case SPECIES_TOXTRICITY_LOW_KEY: case SPECIES_SIRFETCHD:
        case SPECIES_RUNERIGUS: case SPECIES_COPPERAJAH: case SPECIES_ALCREMIE: case SPECIES_FROSMOTH:
        case SPECIES_STONJOURNER: case SPECIES_MORPEKO: case SPECIES_ARCTOVISH: case SPECIES_ARCTOZOLT: case SPECIES_CALYREX: 
        case SPECIES_MR_RIME:
        //3 Points Galar Eviolite
        case SPECIES_DURALUDON: case SPECIES_DRAKLOAK: case SPECIES_GOSSIFLEUR: case SPECIES_LINOONE_GALAR: 
            return 3;

        //3 Points Hisui
        case SPECIES_OVERQWIL: 
            return 3;

        //3 Points Paldea
        case SPECIES_OINKOLOGNE_F: case SPECIES_OINKOLOGNE_M: case SPECIES_TOEDSCRUEL: case SPECIES_SQUAWKABILLY: case SPECIES_MABOSSTIFF: case SPECIES_KILOWATTREL: case SPECIES_BOMBIRDIER:
        case SPECIES_REVAVROOM: case SPECIES_HOUNDSTONE: case SPECIES_TATSUGIRI: case SPECIES_TATSUGIRI_DROOPY: case SPECIES_TATSUGIRI_STRETCHY:
        case SPECIES_VELUZA: case SPECIES_DUDUNSPARCE_THREE_SEGMENT: case SPECIES_DUDUNSPARCE_TWO_SEGMENT: case SPECIES_CETITAN:
        case SPECIES_SINISTCHA_MASTERPIECE: case SPECIES_SINISTCHA_UNREMARKABLE:
        //3 Points Paldea Eviolite Mons
        case SPECIES_ARCTIBAX: case SPECIES_TINKATUFF: case SPECIES_NACLSTACK:
            return 3;
        
        //Terminal 3 Points after badge 5; Starting 4 points
        case SPECIES_IVYSAUR: 
        case SPECIES_MARSHTOMP: case SPECIES_COMBUSKEN:
        case SPECIES_GROTLE: case SPECIES_MONFERNO:
        case SPECIES_FROGADIER:
        case SPECIES_RABOOT: case SPECIES_THWACKEY:
        case SPECIES_FLORAGATO:
        case SPECIES_KADABRA: case SPECIES_HAUNTER: case SPECIES_DUOSION:
        {
            if (FLAG_BADGE05_GET){
                return 3;
            }else{
                return 4;
            }
        }

        //Terminal 2 Points after 4 Badges; starting 4 Points
        case SPECIES_BUTTERFREE: 
        case SPECIES_DUSTOX:
        case SPECIES_TRUMBEAK: case SPECIES_STARAVIA:
        case SPECIES_LOMBRE: case SPECIES_NUZLEAF: 
        case SPECIES_FLAAFFY: case SPECIES_LUXIO:
            {
                if (FlagGet(FLAG_BADGE04_GET)){
                    return 2;
                }else if (FlagGet(FLAG_BADGE02_GET)){
                    return 3;
                }else{
                    return 4;
                }
            }


        //Terminal 2 Points after 5 Badges; starting 4 Points
        case SPECIES_QUILAVA:
            {
                if (FlagGet(FLAG_BADGE05_GET)){
                    return 2;
                }else if (FlagGet(FLAG_BADGE02_GET)){
                    return 3;
                }else{
                    return 4;
                }
            }
        //Terminal 2 Points after 6 Badges; starting 3 Points
        case SPECIES_CLAYDOL:
        case SPECIES_EELEKTROSS:
        case SPECIES_CRYOGONAL:
        case SPECIES_DHELMISE:
        case SPECIES_BRAMBLEGHAST:
        case SPECIES_VIBRAVA:
        {
            if (FlagGet(FLAG_BADGE06_GET)){
                return 2;
            }else{
                return 3;
            }            
        }
        //Terminal 2 Points after 5 Badges; starting 3 Points
        case SPECIES_SWALOT: case SPECIES_CAMERUPT: case SPECIES_ALTARIA: case SPECIES_RAMPARDOS:
        case SPECIES_WORMADAM_TRASH: case SPECIES_SPIRITOMB: case SPECIES_ABOMASNOW: case SPECIES_LEAFEON:
        case SPECIES_ROTOM_FROST: case SPECIES_SCRAFTY: case SPECIES_GARBODOR: case SPECIES_VANILLUXE: 
        case SPECIES_BEHEEYEM: case SPECIES_BEARTIC: case SPECIES_DRUDDIGON: case SPECIES_BOUFFALANT:
        case SPECIES_STANTLER: case SPECIES_WYRDEER: case SPECIES_CLAWITZER: case SPECIES_DEDENNE:
        case SPECIES_GOURGEIST: case SPECIES_LYCANROC_MIDNIGHT: case SPECIES_LURANTIS: case SPECIES_ORANGURU:
        case SPECIES_GRAFAIAI: case SPECIES_SCOVILLAIN:
        case SPECIES_CHARMELEON: case SPECIES_WARTORTLE: case SPECIES_BAYLEEF: case SPECIES_CROCONAW:
        case SPECIES_GROVYLE: case SPECIES_PRINPLUP: case SPECIES_SERVINE: case SPECIES_PIGNITE: case SPECIES_DEWOTT:
        case SPECIES_QUILLADIN:  case SPECIES_BRAIXEN: case SPECIES_DARTRIX: case SPECIES_TORRACAT: case SPECIES_BRIONNE:
        case SPECIES_DRIZZILE: case SPECIES_CROCALOR: case SPECIES_QUAXWELL:
        case SPECIES_LARVESTA: case SPECIES_RUFFLET: case SPECIES_CORVISQUIRE:
        case SPECIES_CARKOL: case SPECIES_POLIWHIRL: case SPECIES_PALPITOAD:
        case SPECIES_MUDBRAY: case SPECIES_HIPPOPOTAS: case SPECIES_DWEBBLE:
        case SPECIES_KOFFING: case SPECIES_VANILLISH: case SPECIES_DOLLIV:
        case SPECIES_GRIMER: case SPECIES_GRIMER_ALOLA: case SPECIES_TRUBBISH: case SPECIES_SILICOBRA:
        case SPECIES_CROAGUNK: case SPECIES_TIRTOUGA: case SPECIES_ARCHEN: case SPECIES_LILEEP:
        case SPECIES_BERGMITE: case SPECIES_KLINK: case SPECIES_FRAXURE: case SPECIES_SCRAGGY:
        case SPECIES_EELEKTRIK: case SPECIES_BINACLE: case SPECIES_TYRUNT: case SPECIES_AMAURA:
        case SPECIES_PONYTA: case SPECIES_PONYTA_GALAR: case SPECIES_OMANYTE: case SPECIES_KABUTO:
        case SPECIES_ANORITH: case SPECIES_SKORUPI: case SPECIES_SNOVER: case SPECIES_FRILLISH:
        case SPECIES_VAROOM: case SPECIES_LAMPENT: case SPECIES_RHYHORN: case SPECIES_SANDYGAST:
        case SPECIES_GOLETT: case SPECIES_SKRELP: case SPECIES_MIENFOO: case SPECIES_PAWNIARD:
        case SPECIES_PIKACHU: case SPECIES_EXEGGCUTE: case SPECIES_VOLTORB_HISUI: case SPECIES_CLEFAIRY:
        case SPECIES_STARYU: case SPECIES_ROSELIA: case SPECIES_MISDREAVUS: case SPECIES_CETODDLE:
        case SPECIES_SHELMET: case SPECIES_PHANTUMP: case SPECIES_LICKITUNG: case SPECIES_AIPOM:
        case SPECIES_YANMA: case SPECIES_DUNSPARCE: 
        {
            if (FlagGet(FLAG_BADGE05_GET)){
                return 2;
            }else{
                return 3;
            }            
        }

        //Terminal 2 Points after 4 Badges; starting 3 Points
        case SPECIES_PERSIAN: case SPECIES_HYPNO:
        case SPECIES_WEEPINBELL: case SPECIES_VICTREEBEL:
        case SPECIES_FEAROW: case SPECIES_ARBOK: case SPECIES_SANDSLASH_ALOLA:
        case SPECIES_VENOMOTH: case SPECIES_DEWGONG: case SPECIES_ELECTRODE:
        case SPECIES_HITMONCHAN: case SPECIES_FLAREON:
        case SPECIES_WIGGLYTUFF: case SPECIES_NOCTOWL: case SPECIES_XATU: case SPECIES_GRANBULL:
        case SPECIES_OCTILLERY: case SPECIES_PELIPPER: case SPECIES_MASQUERAIN:
        case SPECIES_SABLEYE: case SPECIES_MAWILE: case SPECIES_VOLBEAT: case SPECIES_ILLUMISE:
        case SPECIES_CACTURNE: case SPECIES_SOLROCK: case SPECIES_LUNATONE: case SPECIES_WHISCASH:
        case SPECIES_ABSOL: case SPECIES_TROPIUS: case SPECIES_CHIMECHO: case SPECIES_HUNTAIL:
        case SPECIES_VESPIQUEN: case SPECIES_CHERRIM: case SPECIES_LOPUNNY: case SPECIES_HONCHKROW:
        case SPECIES_PURUGLY: case SPECIES_SKUNTANK: case SPECIES_GLACEON: case SPECIES_LIEPARD:
        case SPECIES_SIMISAGE: case SPECIES_SIMISEAR: case SPECIES_SIMIPOUR: case SPECIES_AUDINO:
        case SPECIES_SWADLOON: case SPECIES_LEAVANNY: case SPECIES_WHIRLIPEDE: case SPECIES_CHARJABUG:
        case SPECIES_BASCULIN: case SPECIES_MARACTUS: case SPECIES_SWANNA: case SPECIES_EMOLGA:
        case SPECIES_HEATMOR: case SPECIES_RATICATE_ALOLA: case SPECIES_MALAMAR: case SPECIES_TOUCANNON:
        case SPECIES_GUMSHOOS:  case SPECIES_CRABOMINABLE: case SPECIES_CRAMORANT: case SPECIES_THIEVUL:
        case SPECIES_FLAPPLE: case SPECIES_WUGTRIO: case SPECIES_RABSCA: case SPECIES_KROKOROK:
        case SPECIES_SEADRA: case SPECIES_SEALEO: case SPECIES_GLOOM: 
        case SPECIES_DEWPIDER: case SPECIES_CHEWTLE: case SPECIES_STUFFUL: case SPECIES_MEOWTH_GALAR:
        case SPECIES_KRABBY: case SPECIES_CUBONE: case SPECIES_DRIFLOON: case SPECIES_TRANQUILL:
        case SPECIES_HATTREM: case SPECIES_MORGREM: case SPECIES_PILOSWINE: case SPECIES_BRONZOR:

        {
            if (FlagGet(FLAG_BADGE04_GET)){
                return 2;
            }else{
                return 3;
            }
        }

        //Terminal 2 Points after 3 Badges; starting 3 Points
        case SPECIES_PIDGEOTTO: case SPECIES_FLETCHINDER: case SPECIES_LOUDRED: case SPECIES_WAILMER:
        case SPECIES_SLOWPOKE: case SPECIES_SLOWPOKE_GALAR: case SPECIES_HONEDGE:
        case SPECIES_GROWLITHE: case SPECIES_GROWLITHE_HISUI:
        case SPECIES_ONIX: case SPECIES_NOSEPASS: case SPECIES_SHIELDON:
        case SPECIES_HOUNDOUR:
        case SPECIES_CARVANHA:
        case SPECIES_KIRLIA: case SPECIES_GOTHORITA:
        case SPECIES_DRILBUR:
        case SPECIES_DARUMAKA: case SPECIES_DARUMAKA_GALAR:
        case SPECIES_NIDORINO: case SPECIES_NIDORINA:
        case SPECIES_HERDIER:
        case SPECIES_STEENEE:
        case SPECIES_PAWMO:
        case SPECIES_BUIZEL: case SPECIES_ARROKUDA:
        {
            if (FlagGet(FLAG_BADGE03_GET)){
                return 2;
            }else{
                return 3;
            }
        }

        //Terminal 2 Points
        case SPECIES_GOLDUCK:
        case SPECIES_PIDGEOT:
        case SPECIES_DITTO:
        case SPECIES_EXPLOUD:
        case SPECIES_WAILORD:
        case SPECIES_CRADILY:
        case SPECIES_FINIZEN:
            return 2;

        
    //Terminal 1 Point after 5 Badges; starting 4 Points
        case SPECIES_BEEDRILL:
        case SPECIES_FURRET:
        case SPECIES_BEAUTIFLY:
        case SPECIES_BIBAREL:
        case SPECIES_KRICKETUNE:
        case SPECIES_SPIDOPS:
        {
            if (FlagGet(FLAG_BADGE05_GET)){
                return 1;
            }else if (FlagGet(FLAG_BADGE03_GET)){
                return 2;
            }else if (FlagGet(FLAG_BADGE02_GET)){
                return 3;
            }else{
                return 4;
            }
        }

    //Terminal 1 Point after 4 Badges; starting 4 Points
    case SPECIES_BULBASAUR:
    case SPECIES_MUDKIP: case SPECIES_TORCHIC:
    case SPECIES_TURTWIG:
    case SPECIES_FROAKIE:
    case SPECIES_SCORBUNNY: case SPECIES_GROOKEY: 
    case SPECIES_SPRIGATITO:
    {
        if (FlagGet(FLAG_BADGE04_GET)){
            return 1;
        }
        if (FlagGet(FLAG_BADGE03_GET)){
            return 2;
        }
        else if(FlagGet(FLAG_BADGE02_GET)){
            return 3;
        }else{
            return 4;
        }
    }

    //Terminal 1 Point after 5 Badges; starting 3 Points
        case SPECIES_PARASECT: case SPECIES_SEAKING:
        case SPECIES_LEDIAN: case SPECIES_ARIADOS: case SPECIES_SUNFLORA: case SPECIES_QWILFISH:
        case SPECIES_CORSOLA: case SPECIES_MAGCARGO: case SPECIES_DELIBIRD:
        case SPECIES_MIGHTYENA: case SPECIES_LINOONE: case SPECIES_DELCATTY: case SPECIES_PLUSLE:
        case SPECIES_MINUN: case SPECIES_SPINDA: case SPECIES_SEVIPER: case SPECIES_CASTFORM:
        case SPECIES_BANETTE: case SPECIES_LUVDISC: case SPECIES_WORMADAM_PLANT: case SPECIES_WORMADAM_SANDY:
        case SPECIES_MOTHIM: case SPECIES_PACHIRISU: case SPECIES_CHATOT: case SPECIES_CARNIVINE:
        case SPECIES_LUMINEON: case SPECIES_PHIONE: case SPECIES_SWOOBAT: case SPECIES_WATCHOG:
        case SPECIES_UNOWN: case SPECIES_TRAPINCH: case SPECIES_SWABLU: case SPECIES_LITLEO:
        case SPECIES_JOLTIK: case SPECIES_AXEW: case SPECIES_LITWICK: case SPECIES_VANILLITE:
        case SPECIES_CLAMPERL: case SPECIES_SPRITZEE: case SPECIES_SWIRLIX: case SPECIES_MILCERY:
        case SPECIES_PORYGON: case SPECIES_MINCCINO: 
        {
            if (FlagGet(FLAG_BADGE05_GET)){
                return 1;
            }else if (FlagGet(FLAG_BADGE04_GET)){
                return 2;
            }else{
                return 3;
            }
        }
    //Terminal 1 Point after 4 Badges; starting 3 Points
        case SPECIES_NUMEL: case SPECIES_BARBOACH: case SPECIES_BALTOY:
        case SPECIES_BUNEARY: case SPECIES_MURKROW: case SPECIES_DUCKLETT: case SPECIES_CUBCHOO:
        case SPECIES_ELGYEM: case SPECIES_INKAY: case SPECIES_CLAUNCHER: case SPECIES_PUMPKABOO: 
        case SPECIES_CRABRAWLER: case SPECIES_ROCKRUFF: case SPECIES_FOMANTIS:
        case SPECIES_APPLIN: case SPECIES_MIME_JR: case SPECIES_WIGLETT:
        case SPECIES_CAPSAKID: case SPECIES_RELLOR: case SPECIES_BRAMBLIN: case SPECIES_HAPPINY:
        case SPECIES_DRATINI: case SPECIES_LARVITAR: case SPECIES_BAGON: case SPECIES_GIBLE:
        case SPECIES_DEINO: case SPECIES_GOOMY: case SPECIES_JANGMO_O: case SPECIES_DREEPY: case SPECIES_FRIGIBAX: case SPECIES_RIOLU:
        case SPECIES_CHARMANDER: case SPECIES_SQUIRTLE: case SPECIES_CHIKORITA: case SPECIES_CYNDAQUIL: case SPECIES_TOTODILE:
        case SPECIES_TREECKO: case SPECIES_PIPLUP: case SPECIES_CHIMCHAR:case SPECIES_SNIVY: case SPECIES_TEPIG: case SPECIES_OSHAWOTT: case SPECIES_FENNEKIN: case SPECIES_CHESPIN:
        case SPECIES_ROWLET: case SPECIES_LITTEN: case SPECIES_POPPLIO: case SPECIES_SOBBLE: case SPECIES_FUECOCO: case SPECIES_QUAXLY: 
        case SPECIES_ABRA: case SPECIES_GASTLY: case SPECIES_SOLOSIS: 
        case SPECIES_MEDITITE: case SPECIES_SHUPPET: case SPECIES_DUSKULL: case SPECIES_GEODUDE: case SPECIES_GEODUDE_ALOLA: case SPECIES_ARON: 
        case SPECIES_ELEKID: case SPECIES_MAGBY: case SPECIES_SMOOCHUM: case SPECIES_BONSLY: case SPECIES_BUDEW:
        case SPECIES_NACLI: case SPECIES_TINKATINK: case SPECIES_ROGGENROLA: case SPECIES_MACHOP: case SPECIES_TIMBURR:
        case SPECIES_FIDOUGH: case SPECIES_CHINCHOU: case SPECIES_BLITZLE: case SPECIES_MEOWTH: case SPECIES_MEOWTH_ALOLA:
        case SPECIES_SIZZLIPEDE: case SPECIES_SHROODLE: case SPECIES_SANDILE: case SPECIES_TENTACOOL: case SPECIES_TOEDSCOOL: case SPECIES_MAGNEMITE:
        case SPECIES_VOLTORB: case SPECIES_TEDDIURSA: case SPECIES_CORPHISH: case SPECIES_CRANIDOS: case SPECIES_SHELLOS_EAST: case SPECIES_SHELLOS_WEST:
        case SPECIES_ZORUA: case SPECIES_ZORUA_HISUI: case SPECIES_MASCHIFF: case SPECIES_GREAVARD: case SPECIES_VENONAT: case SPECIES_DODUO: case SPECIES_PINECO: case SPECIES_HORSEA:
        case SPECIES_SKIDDO: case SPECIES_PANCHAM: case SPECIES_HATENNA: case SPECIES_IMPIDIMP: 
        case SPECIES_SALANDIT: case SPECIES_SEEL: case SPECIES_STUNKY: case SPECIES_YAMASK: case SPECIES_YAMASK_GALAR:
        case SPECIES_DEERLING: case SPECIES_CUFANT: case SPECIES_FLITTLE: case SPECIES_SLUGMA: case SPECIES_GLAMEOW: case SPECIES_CHARCADET: 
        case SPECIES_SINISTEA_PHONY: case SPECIES_SINISTEA_ANTIQUE: case SPECIES_POLTCHAGEIST_ARTISAN: case SPECIES_POLTCHAGEIST_COUNTERFEIT:
        case SPECIES_VULPIX: case SPECIES_VULPIX_ALOLA: case SPECIES_EEVEE: case SPECIES_PANSEAR: case SPECIES_SHELLDER: case SPECIES_PANPOUR:
        case SPECIES_PANSAGE: case SPECIES_TADBULB: case SPECIES_JIGGLYPUFF: case SPECIES_MUNNA: case SPECIES_PETILIL: case SPECIES_HELIOPTILE:  case SPECIES_SNORUNT:
        case SPECIES_KARRABLAST: case SPECIES_CLOBBOPUS:
        {
            if (FlagGet(FLAG_BADGE04_GET)){
                return 1;
            }else if (FlagGet(FLAG_BADGE03_GET)){
                return 2;
            }else{
                return 3;
            }
        }
    
    //Terminal 1 Point after 3 badges; starting 3 points
        case SPECIES_PIDGEY: case SPECIES_HOOTHOOT: case SPECIES_TAILLOW: case SPECIES_STARLY:
        case SPECIES_PIDOVE: case SPECIES_FLETCHLING: case SPECIES_PIKIPEK: case SPECIES_ROOKIDEE: case SPECIES_WATTREL:
        case SPECIES_LOTAD: case SPECIES_SEEDOT:
        case SPECIES_SENTRET: case SPECIES_BIDOOF: case SPECIES_LILLIPUP: case SPECIES_PATRAT: case SPECIES_YUNGOOS:
        case SPECIES_MAREEP: case SPECIES_SHINX:  case SPECIES_WYNAUT: case SPECIES_NIDORAN_M: case SPECIES_NIDORAN_F:
        case SPECIES_MARILL: case SPECIES_SURSKIT: case SPECIES_POLIWAG: case SPECIES_WINGULL:
        case SPECIES_POOCHYENA: case SPECIES_NICKIT: case SPECIES_HOPPIP: case SPECIES_ODDISH: case SPECIES_BELLSPROUT:
        case SPECIES_ROLYCOLY: case SPECIES_PAWMI: case SPECIES_EKANS: case SPECIES_GULPIN:
        case SPECIES_SANDSHREW: case SPECIES_SANDSHREW_ALOLA: case SPECIES_FLABEBE:
        case SPECIES_RATTATA: case SPECIES_RATTATA_ALOLA: case SPECIES_ZIGZAGOON: case SPECIES_ZIGZAGOON_GALAR:
        case SPECIES_SKWOVET: case SPECIES_WOOLOO: case SPECIES_WHISMUR: case SPECIES_LECHONK:
        case SPECIES_NYMBLE: case SPECIES_NINCADA: case SPECIES_SPEAROW: case SPECIES_NATU:
        case SPECIES_WOOPER: case SPECIES_WOOPER_PALDEA: case SPECIES_REMORAID:
        case SPECIES_MAKUHITA: case SPECIES_SNUBBULL: 
        case SPECIES_SHROOMISH: case SPECIES_PARAS: case SPECIES_MORELULL: case SPECIES_CHERUBI:
        case SPECIES_PHANPY: case SPECIES_ESPURR: case SPECIES_CUTIEFLY: case SPECIES_YAMPER: case SPECIES_TANDEMAUS:
        case SPECIES_SMOLIV: case SPECIES_DIGLETT: case SPECIES_DIGLETT_ALOLA:
        case SPECIES_ELECTRIKE: case SPECIES_FINNEON: case SPECIES_SPOINK: case SPECIES_CACNEA: case SPECIES_SPHEAL:
        case SPECIES_GOLDEEN: case SPECIES_SWINUB:
        {
            if (FlagGet(FLAG_BADGE03_GET)){
                return 1;
            }else if (FlagGet(FLAG_BADGE02_GET)){
                return 2;
            }else{
                return 3;
            }
        }    
    //Terminal 1 Point after 3 Badges; starting 2 points
        case SPECIES_BELDUM:
        case SPECIES_PSYDUCK:
        case SPECIES_DROWZEE:
        case SPECIES_FEEBAS:
        case SPECIES_RALTS:
        case SPECIES_TOXEL:
        case SPECIES_SLAKOTH:
        case SPECIES_TYROGUE:
        case SPECIES_SKITTY:
        case SPECIES_TYNAMO:
        {
            if (FlagGet(FLAG_BADGE03_GET)){
                return 1;
            }else{
                return 2;
            }
        }
    //Terminal 1 Point after 2 Badges; starting 2 points
    case SPECIES_ZUBAT: case SPECIES_WOOBAT: case SPECIES_NOIBAT:
    case SPECIES_TOGEPI: case SPECIES_IGGLYBUFF: case SPECIES_PICHU:
    case SPECIES_AZURILL: case SPECIES_CLEFFA: case SPECIES_SUNKERN:
    case SPECIES_SEWADDLE: case SPECIES_VENIPEDE: case SPECIES_SNOM:
    case SPECIES_CHINGLING:
        {
          if (FlagGet(FLAG_BADGE02_GET)){
                return 1;
            }else{
                return 2;
            }
        }

    //Terminal 1 Point after 1 Badge; Starting 2 points
        case SPECIES_METAPOD: case SPECIES_KAKUNA: case SPECIES_LEDYBA: case SPECIES_SPINARAK:
        case SPECIES_SILCOON: case SPECIES_CASCOON: case SPECIES_COMBEE:
        case SPECIES_BURMY: case SPECIES_BURMY_SANDY: case SPECIES_BURMY_TRASH:
        case SPECIES_SPEWPA: case SPECIES_GRUBBIN: case SPECIES_DOTTLER:
        case SPECIES_TAROUNTULA: case SPECIES_BOUNSWEET:
        {
          if (FlagGet(FLAG_BADGE01_GET)){
                return 1;
            }else{
                return 2;
            }
        }
    //Terminal 1 Point after 6 badges; Starting 2 Points
    case SPECIES_GLALIE:
    {
        if (FlagGet(FLAG_BADGE06_GET)){
            return 1;
        }else{
            return 2;
        }
    }

    //Terminal 1 Point
        case SPECIES_MAGIKARP:
        case SPECIES_CATERPIE: case SPECIES_WEEDLE: case SPECIES_WURMPLE: case SPECIES_KRICKETOT: 
        case SPECIES_SCATTERBUG: case SPECIES_BLIPBUG:
            return 1;
        default:   
            return defaultPointValue;
    }
}

//Get the points of the party other than the mon to replace.
u32 CountPartyTierPoints(){
    u16 i = 0;
    u32 tierPoints = 0;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES) != SPECIES_NONE
            && !GetMonData(&gPlayerParty[i], MON_DATA_IS_EGG)
            )
        {
            u16 species = GetMonData(&gPlayerParty[i], MON_DATA_SPECIES);
            tierPoints += GetMonTierPoints(species);
        }
    }
    return tierPoints;
}
