#include "global.h"
#include "event_data.h"
#include "field_specials.h"
#include "move_relearner.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "constants/abilities.h"
#include "constants/flags.h"
#include "constants/species.h"
#include "constants/vars.h"

EWRAM_DATA u32 gExcessTierPoints = 0;

bool8 DepositPartyMonToPC_Auto(u8 partyId)
{
    s32 boxNo, boxPos;

    SetPCBoxToSendMon(VarGet(VAR_PC_BOX_TO_SEND_MON));
    boxNo = StorageGetCurrentBox();

    do {
        for (boxPos = 0; boxPos < IN_BOX_COUNT; boxPos++) {
            struct BoxPokemon *slot = GetBoxedMonPtr(boxNo, boxPos);
            if (GetBoxMonData(slot, MON_DATA_SPECIES, NULL) == SPECIES_NONE) {
                CopyMon(slot, &gParties[B_TRAINER_PLAYER][partyId].box, sizeof(gParties[B_TRAINER_PLAYER][partyId].box));

                // Move all slots after the boxed mon back by 1 slot
                for (u8 i = partyId; i + 1 < gPartiesCount[B_TRAINER_PLAYER]; i++)
                    CopyMon(&gParties[B_TRAINER_PLAYER][i], &gParties[B_TRAINER_PLAYER][i + 1], sizeof(struct Pokemon));
                ZeroMonData(&gParties[B_TRAINER_PLAYER][--gPartiesCount[B_TRAINER_PLAYER]]);

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


u8 GetMonoType(void)
{
    u8 varValue = VarGet(VAR_MONOTYPE);

    if (varValue == 0 || varValue >= NUMBER_OF_MON_TYPES)
        return TYPE_NONE;
    if (varValue >= 10)
        return varValue + 1;
    return varValue;
}

u32 CalcTierPointsAfterEvolution(u8 partyId, u16 newSpecies)
{
    u32 total = 0;
    struct Pokemon tempMon;
    for (u8 i = 0; i < gPartiesCount[B_TRAINER_PLAYER]; i++) {
        if (i == partyId) {
            // Create temporary mon with new species to calculate points
            tempMon = gParties[B_TRAINER_PLAYER][i];
            SetMonData(&tempMon, MON_DATA_SPECIES, &newSpecies);
            total += GetMonTierPoints(&tempMon);
        } else {
            total += GetMonTierPoints(&gParties[B_TRAINER_PLAYER][i]);
        }
    }
    return total;
}

u32 CalcTierPointsAfterAbilityChange(u8 partyId, u8 newAbilityNum)
{
    u32 total = 0;
    struct Pokemon tempMon;
    for (u8 i = 0; i < gPartiesCount[B_TRAINER_PLAYER]; i++) {
        if (i == partyId) {
            tempMon = gParties[B_TRAINER_PLAYER][i];
            SetMonData(&tempMon, MON_DATA_ABILITY_NUM, &newAbilityNum);
            total += GetMonTierPoints(&tempMon);
        } else {
            total += GetMonTierPoints(&gParties[B_TRAINER_PLAYER][i]);
        }
    }
    return total;
}

u8 GetMonTierPoints(struct Pokemon *mon){
    u16 species;
    u8 abilityNum;
    u32 ability;

    if (mon == NULL){
        return 3; //Default
    }
    //Treating eggs as 0 until they hatch
    if (GetMonData(mon, MON_DATA_IS_EGG)){
        return 0;
    }
    species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    abilityNum = GetMonData(mon, MON_DATA_ABILITY_NUM, NULL);
    ability =  GetAbilityBySpecies(species, abilityNum);

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
        //Special Ability Logic: Drizzle
        case SPECIES_POLITOED:
            if (ability == ABILITY_DRIZZLE){
                return 6;
            }else{
                return 3;
            }
        case SPECIES_PELIPPER:
            if (ability == ABILITY_DRIZZLE){
                return 6;
            }else{
                if (FlagGet(FLAG_BADGE05_GET)){
                return 2;
                }else{
                return 3;
                }
            }

        //Special Ability Logic: Drought
        case SPECIES_VULPIX:
            if (ability == ABILITY_DROUGHT){
                if (FlagGet(FLAG_BADGE08_GET)){
                    return 5;
                }else{
                    return 6;
                }

            }else{
                if (FlagGet(FLAG_BADGE04_GET)){
                    return 1;
                }else if (FlagGet(FLAG_BADGE03_GET)){
                    return 2;
                }else{
                    return 3;
                }
            }
        case SPECIES_NINETALES:
            if (ability == ABILITY_DROUGHT){
                return 6;
            }else{
                return 3;
            }


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
        case SPECIES_ALAKAZAM: case SPECIES_MAROWAK: case SPECIES_MAROWAK_ALOLA:
        case SPECIES_MUK_ALOLA: case SPECIES_GENGAR: case SPECIES_TAUROS: case SPECIES_TAUROS_PALDEA_AQUA: case SPECIES_TAUROS_PALDEA_BLAZE:
        case SPECIES_TAUROS_PALDEA_COMBAT: case SPECIES_SCYTHER: case SPECIES_GYARADOS: case SPECIES_LAPRAS: case SPECIES_VAPOREON:
        case SPECIES_AERODACTYL: case SPECIES_ARTICUNO_GALAR: case SPECIES_ZAPDOS_GALAR:
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
        case SPECIES_SWAMPERT: case SPECIES_SWELLOW: case SPECIES_GARDEVOIR: case SPECIES_SLAKING:
        case SPECIES_ZANGOOSE: case SPECIES_METAGROSS: case SPECIES_REGISTEEL: case SPECIES_JIRACHI:
        case SPECIES_MEDICHAM:

        //4 Points Hoenn Megas
        case SPECIES_GLALIE_MEGA: case SPECIES_BANETTE_MEGA: case SPECIES_ABSOL_MEGA: case SPECIES_MANECTRIC_MEGA: case SPECIES_CAMERUPT_MEGA: case SPECIES_ALTARIA_MEGA:

        //4 Points Sinnoh
        case SPECIES_TORTERRA: case SPECIES_EMPOLEON: case SPECIES_STARAPTOR: case SPECIES_ROSERADE: case SPECIES_BRONZONG: case SPECIES_LUCARIO: case SPECIES_HIPPOWDON:
        case SPECIES_DRAPION: case SPECIES_WEAVILE: case SPECIES_MAGNEZONE: case SPECIES_RHYPERIOR: case SPECIES_GLISCOR: case SPECIES_MAMOSWINE: case SPECIES_GALLADE:
        case SPECIES_AMBIPOM: case SPECIES_FLOATZEL: case SPECIES_PORYGON_Z: case SPECIES_ROTOM_WASH: case SPECIES_CRESSELIA: case SPECIES_SHAYMIN:
        case SPECIES_MISMAGIUS:

        //4 Points Sinnoh Megas
        case SPECIES_ABOMASNOW_MEGA:

        //4 Points Unova/Regionals
        case SPECIES_VICTINI: case SPECIES_SAMUROTT: case SPECIES_SAMUROTT_HISUI: case SPECIES_GIGALITH: case SPECIES_CONKELDURR: case SPECIES_SAWK:
        case SPECIES_WHIMSICOTT: case SPECIES_LILLIGANT_HISUI: case SPECIES_KROOKODILE:
        case SPECIES_ZOROARK: case SPECIES_ZOROARK_HISUI: case SPECIES_REUNICLUS: case SPECIES_ARCHEOPS: case SPECIES_ESCAVALIER:
        case SPECIES_CHANDELURE: case SPECIES_HAXORUS: case SPECIES_MIENSHAO: case SPECIES_MANDIBUZZ: case SPECIES_DURANT: case SPECIES_HYDREIGON: case SPECIES_COBALION:
        case SPECIES_CINCCINO: case SPECIES_TORNADUS: case SPECIES_KELDEO: case SPECIES_MELOETTA: case SPECIES_MELOETTA_PIROUETTE:
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
        case SPECIES_XURKITREE: case SPECIES_STAKATAKA: case SPECIES_NECROZMA: case SPECIES_SILVALLY:

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
        case SPECIES_FEZANDIPITI: case SPECIES_MUNKIDORI: case SPECIES_OKIDOGI:
            return 4;

        //3 Points Kanto/Regionals
        case SPECIES_BLASTOISE: case SPECIES_RATICATE: case SPECIES_RAICHU: case SPECIES_RAICHU_ALOLA: case SPECIES_SANDSLASH: case SPECIES_NIDOQUEEN:
        case SPECIES_NINETALES_ALOLA: case SPECIES_VILEPLUME: case SPECIES_PERSIAN_ALOLA: case SPECIES_DUGTRIO: case SPECIES_POLIWRATH: case SPECIES_MACHAMP:
        case SPECIES_TENTACRUEL: case SPECIES_GOLEM: case SPECIES_GOLEM_ALOLA: case SPECIES_MUK: case SPECIES_ELECTRODE_HISUI: case SPECIES_KINGLER:
        case SPECIES_DODRIO: case SPECIES_EXEGGUTOR: case SPECIES_EXEGGUTOR_ALOLA: case SPECIES_HITMONLEE: case SPECIES_HITMONCHAN:
        case SPECIES_WEEZING: case SPECIES_WEEZING_GALAR: case SPECIES_KANGASKHAN: case SPECIES_JYNX: case SPECIES_PINSIR: case SPECIES_MR_MIME: case SPECIES_MR_MIME_GALAR:
        case SPECIES_JOLTEON: case SPECIES_ARTICUNO: case SPECIES_RAPIDASH: case SPECIES_RAPIDASH_GALAR: case SPECIES_WIGGLYTUFF:

        //3 Points Kanto Eviolite
        case SPECIES_DRAGONAIR: case SPECIES_GOLBAT: case SPECIES_GRAVELER: case SPECIES_GRAVELER_ALOLA: case SPECIES_MACHOKE:
        case SPECIES_TANGELA: case SPECIES_ELECTABUZZ: case SPECIES_MAGMAR:
            return 3;

        //3 Points Johto/Regionals
        case SPECIES_MEGANIUM: case SPECIES_LANTURN: case SPECIES_FERALIGATR: case SPECIES_AMPHAROS: case SPECIES_BELLOSSOM: case SPECIES_SUDOWOODO:
        case SPECIES_WOBBUFFET: case SPECIES_SHUCKLE: case SPECIES_MANTINE: case SPECIES_HOUNDOOM: case SPECIES_DONPHAN:
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
        case SPECIES_WORMADAM_TRASH: case SPECIES_SPIRITOMB:

        //3 Points Sinnoh Eviolite
        case SPECIES_MUNCHLAX: case SPECIES_GABITE:
            return 3;

        //3 Points Unova/Regionals
        case SPECIES_SERPERIOR: case SPECIES_EMBOAR: case SPECIES_STOUTLAND: case SPECIES_MUSHARNA: case SPECIES_UNFEZANT:
        case SPECIES_ZEBSTRIKA: case SPECIES_SEISMITOAD: case SPECIES_THROH: case SPECIES_LILLIGANT: case SPECIES_SIGILYPH:
        case SPECIES_COFAGRIGUS: case SPECIES_CARRACOSTA: case SPECIES_SAWSBUCK: case SPECIES_JELLICENT: case SPECIES_GOTHITELLE:
        case SPECIES_GALVANTULA: case SPECIES_KLINKLANG: case SPECIES_ACCELGOR: case SPECIES_STUNFISK: case SPECIES_STUNFISK_GALAR:
        case SPECIES_GOLURK: case SPECIES_BRAVIARY: case SPECIES_BRAVIARY_HISUI: case SPECIES_VIRIZION:
        case SPECIES_DARMANITAN_ZEN: //Zen Mode Unovan Darmanitan is lower points
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
        case SPECIES_MINIOR: case SPECIES_KOMALA: case SPECIES_TURTONATOR: case SPECIES_DRAMPA:
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
        case SPECIES_SINISTCHA_MASTERPIECE: case SPECIES_SINISTCHA_UNREMARKABLE: case SPECIES_BRAMBLEGHAST:

        //3 Points Paldea Eviolite Mons
        case SPECIES_ARCTIBAX: case SPECIES_TINKATUFF: case SPECIES_NACLSTACK:
            return 3;

        //Terminal 3 points after 8 badges; starting 4 points
        case SPECIES_YANMEGA: case SPECIES_CRUSTLE: case SPECIES_ARMALDO: case SPECIES_SHARPEDO: case SPECIES_ESPATHRA:
        case SPECIES_KABUTOPS: case SPECIES_OMASTAR: case SPECIES_SCOLIPEDE: case SPECIES_NIDOKING:
        {
            if (FlagGet(FLAG_BADGE08_GET)){
                return 3;
            }else{
                return 4;
            }
        }

        //Terminal 3 points after 7 badges; starting 4 points
        case SPECIES_AGGRON: case SPECIES_KLAWF: case SPECIES_DUGTRIO_ALOLA:
        {
            if (FlagGet(FLAG_BADGE07_GET)){
                return 3;
            }else{
                return 4;
            }
        }

        //Terminal 3 Points after badge 5; Starting 4 points
        case SPECIES_IVYSAUR:
        case SPECIES_MARSHTOMP: case SPECIES_COMBUSKEN:
        case SPECIES_GROTLE: case SPECIES_MONFERNO:
        case SPECIES_FROGADIER:
        case SPECIES_RABOOT: case SPECIES_THWACKEY:
        case SPECIES_FLORAGATO:
        case SPECIES_KADABRA: case SPECIES_HAUNTER: case SPECIES_DUOSION:
        {
            if (FlagGet(FLAG_BADGE05_GET)){
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
        case SPECIES_ABOMASNOW: case SPECIES_LEAFEON:
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
        case SPECIES_WORMADAM_SANDY:
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
        case SPECIES_FLAREON: case SPECIES_NOCTOWL: case SPECIES_XATU: case SPECIES_GRANBULL:
        case SPECIES_OCTILLERY: case SPECIES_MASQUERAIN:
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
        case SPECIES_BANETTE: case SPECIES_LUVDISC: case SPECIES_WORMADAM_PLANT:
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
        case SPECIES_VULPIX_ALOLA: case SPECIES_EEVEE: case SPECIES_PANSEAR: case SPECIES_SHELLDER: case SPECIES_PANPOUR:
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

static bool32 IsFreeMoveRelearnerTierException(u16 species)
{
    switch (species)
    {
    case SPECIES_BEEDRILL:
        return TRUE;
    default:
        return FALSE;
    }
}

static bool32 IsFreeCenterTutorTierException(u16 species)
{
    switch (species)
    {
    //Currently redundant but keeping this check until
    //I have identified a mon that has a conditional 2-point ability variation
    case SPECIES_BEEDRILL:
        return TRUE;
    default:
        //Because MoveRelearner Tier points are more lenient, they naturally apply here
        return IsFreeMoveRelearnerTierException(species);
    }
}



static bool32 DoesSpeciesOrEvolutionExceedTierPointThreshold(struct Pokemon *mon, u16 species, u8 threshold)
{
    u32 i;
    u8 abilityNum;
    struct Pokemon tempMon = *mon;
    const struct Evolution *evolutions;

    SetMonData(&tempMon, MON_DATA_SPECIES, &species);

    for (abilityNum = 0; abilityNum < NUM_ABILITY_SLOTS; abilityNum++)
    {
        if (GetSpeciesAbility(species, abilityNum) == ABILITY_NONE)
            continue;

        SetMonData(&tempMon, MON_DATA_ABILITY_NUM, &abilityNum);
        if (GetMonTierPoints(&tempMon) > threshold)
            return TRUE;
    }

    evolutions = GetSpeciesEvolutions(species);
    if (evolutions == NULL)
        return FALSE;

    for (i = 0; evolutions[i].method != EVOLUTIONS_END; i++)
    {
        u16 targetSpecies = SanitizeSpeciesId(evolutions[i].targetSpecies);

        if (targetSpecies == SPECIES_NONE)
            continue;

        if (DoesSpeciesOrEvolutionExceedTierPointThreshold(mon, targetSpecies, threshold))
            return TRUE;
    }

    return FALSE;
}

bool32 IsMonFreeCenterTutorEligible(struct Pokemon *mon)
{
    u16 species;

    if (mon == NULL || GetMonData(mon, MON_DATA_IS_EGG))
        return FALSE;

    species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    if (species == SPECIES_NONE || GetMonTierPoints(mon) > 1)
        return FALSE;

    if (IsFreeCenterTutorTierException(species))
        return FALSE;

    return !DoesSpeciesOrEvolutionExceedTierPointThreshold(mon, species, 1);
}

bool32 CanMonUseCenterTutorWithCurrentResources(struct Pokemon *mon)
{
    if (GetNumberOfCenterTutorableMoves(mon) == 0)
        return FALSE;

    if (!FlagGet(FLAG_RESOURCE_MODE) || VarGet(VAR_TEMP_9) != MOVE_TUTOR_CENTER || VarGet(VAR_REMAINING_TUTOR) > 0)
        return TRUE;

    return IsMonFreeCenterTutorEligible(mon);
}

bool32 IsMonFreeMoveRelearnerEligible(struct Pokemon *mon)
{
    u16 species;

    if (mon == NULL || GetMonData(mon, MON_DATA_IS_EGG))
        return FALSE;

    species = GetMonData(mon, MON_DATA_SPECIES, NULL);
    if (species == SPECIES_NONE || GetMonTierPoints(mon) > 2)
        return FALSE;

    if (IsFreeMoveRelearnerTierException(species))
        return FALSE;

    return !DoesSpeciesOrEvolutionExceedTierPointThreshold(mon, species, 2);
}

bool32 CanMonUseMoveRelearnerWithCurrentResources(struct Pokemon *mon)
{
    if (!CanBoxMonRelearnAnyMove(&mon->box))
        return FALSE;

    if (!FlagGet(FLAG_RESOURCE_MODE) || VarGet(VAR_REMAINING_RELEARNER) > 0)
        return TRUE;

    return IsMonFreeMoveRelearnerEligible(mon);
}

//Get the points of the party other than the mon to replace.
u32 CountPartyTierPoints(){
    u16 i = 0;
    u32 tierPoints = 0;

    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES) != SPECIES_NONE
            && !GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_IS_EGG)
            )
        {
            tierPoints += GetMonTierPoints(&gParties[B_TRAINER_PLAYER][i]);
        }
    }
    return tierPoints;
}

u32 GetPartyTierPointExcessWithMon(struct Pokemon *mon)
{
    u32 tierPoints;

    if (!FlagGet(FLAG_TIERED) || mon == NULL)
        return 0;

    tierPoints = CountPartyTierPoints() + GetMonTierPoints(mon);
    return tierPoints > TIER_POINTS_CAP ? tierPoints - TIER_POINTS_CAP : 0;
}

u32 GetCurrentPartyTierPointExcess(void)
{
    u32 tierPoints;

    if (!FlagGet(FLAG_TIERED))
        return 0;

    tierPoints = CountPartyTierPoints();
    return tierPoints > TIER_POINTS_CAP ? tierPoints - TIER_POINTS_CAP : 0;
}
