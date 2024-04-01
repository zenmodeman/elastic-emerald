# 1 "data/maps/InsideOfTruck/scripts.pory"

# 2 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_MapScripts::
# 3 "data/maps/InsideOfTruck/scripts.pory"
	map_script MAP_SCRIPT_ON_LOAD, InsideOfTruck_OnLoad
# 4 "data/maps/InsideOfTruck/scripts.pory"
	map_script MAP_SCRIPT_ON_RESUME, InsideOfTruck_OnResume
# 5 "data/maps/InsideOfTruck/scripts.pory"
	.byte 0
# 6 "data/maps/InsideOfTruck/scripts.pory"

# 7 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_OnLoad:
# 8 "data/maps/InsideOfTruck/scripts.pory"
	setmetatile 4, 1, METATILE_InsideOfTruck_ExitLight_Top, FALSE
# 9 "data/maps/InsideOfTruck/scripts.pory"
	setmetatile 4, 2, METATILE_InsideOfTruck_ExitLight_Mid, FALSE
# 10 "data/maps/InsideOfTruck/scripts.pory"
	setmetatile 4, 3, METATILE_InsideOfTruck_ExitLight_Bottom, FALSE
# 11 "data/maps/InsideOfTruck/scripts.pory"
	end
# 12 "data/maps/InsideOfTruck/scripts.pory"

# 13 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_OnResume:
# 14 "data/maps/InsideOfTruck/scripts.pory"
	setstepcallback STEP_CB_TRUCK
# 15 "data/maps/InsideOfTruck/scripts.pory"
	end
# 16 "data/maps/InsideOfTruck/scripts.pory"

# 17 "data/maps/InsideOfTruck/scripts.pory"

# 18 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_EventScript_SetIntroFlagsMale::
# 19 "data/maps/InsideOfTruck/scripts.pory"
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F
# 20 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_LITTLEROOT_INTRO_STATE, 1
# 21 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_MOM
# 22 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_TRUCK
# 23 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_MOM
# 24 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_SIBLING
# 25 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_POKE_BALL
# 26 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 1
# 27 "data/maps/InsideOfTruck/scripts.pory"
	setdynamicwarp MAP_LITTLEROOT_TOWN, 3, 10
# 28 "data/maps/InsideOfTruck/scripts.pory"
	releaseall
# 29 "data/maps/InsideOfTruck/scripts.pory"
	end
# 30 "data/maps/InsideOfTruck/scripts.pory"

# 31 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_EventScript_SetIntroFlagsFemale::
# 32 "data/maps/InsideOfTruck/scripts.pory"
	setrespawn HEAL_LOCATION_LITTLEROOT_TOWN_MAYS_HOUSE_2F
# 33 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_LITTLEROOT_INTRO_STATE, 2
# 34 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_MOM
# 35 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_TRUCK
# 36 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_MOM
# 37 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_SIBLING
# 38 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_POKE_BALL
# 39 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 1
# 40 "data/maps/InsideOfTruck/scripts.pory"
	setdynamicwarp MAP_LITTLEROOT_TOWN, 12, 10
# 41 "data/maps/InsideOfTruck/scripts.pory"
	releaseall
# 42 "data/maps/InsideOfTruck/scripts.pory"
	end
# 43 "data/maps/InsideOfTruck/scripts.pory"

# 44 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_EventScript_MovingBox::
# 45 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_Text_BoxPrintedWithMonLogo, MSGBOX_SIGN
# 46 "data/maps/InsideOfTruck/scripts.pory"
	end
# 47 "data/maps/InsideOfTruck/scripts.pory"

# 48 "data/maps/InsideOfTruck/scripts.pory"
InsideOfTruck_Text_BoxPrintedWithMonLogo:
# 49 "data/maps/InsideOfTruck/scripts.pory"
	.string "The box is printed with a POKéMON logo.\p"
# 50 "data/maps/InsideOfTruck/scripts.pory"
	.string "It's a POKéMON brand moving and\n"
# 51 "data/maps/InsideOfTruck/scripts.pory"
	.string "delivery service.$"

InsideOfTruck_EventScript_SetIntroFlags::
# 57 "data/maps/InsideOfTruck/scripts.pory"
	lockall
# 58 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_HIDE_MAP_NAME_POPUP
# 59 "data/maps/InsideOfTruck/scripts.pory"
	msgbox BeforeBegginning
# 60 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_0
InsideOfTruck_EventScript_SetIntroFlags_3:
# 62 "data/maps/InsideOfTruck/scripts.pory"
	dynmultichoice 10, 100, TRUE, 3, 0, DYN_MULTICHOICE_CB_NONE, InsideOfTruck_EventScript_SetIntroFlags_Text_1, InsideOfTruck_EventScript_SetIntroFlags_Text_2, InsideOfTruck_EventScript_SetIntroFlags_Text_3
# 63 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_9
# 66 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_10
InsideOfTruck_EventScript_SetIntroFlags_2:
# 69 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_3
# 71 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_4
InsideOfTruck_EventScript_SetIntroFlags_7:
# 73 "data/maps/InsideOfTruck/scripts.pory"
	dynmultichoice 10, 100, TRUE, 3, 0, DYN_MULTICHOICE_CB_NONE, InsideOfTruck_EventScript_SetIntroFlags_Text_1, InsideOfTruck_EventScript_SetIntroFlags_Text_2, InsideOfTruck_EventScript_SetIntroFlags_Text_3
# 74 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_17
# 77 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_18
InsideOfTruck_EventScript_SetIntroFlags_6:
# 80 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_7
# 82 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_5
InsideOfTruck_EventScript_SetIntroFlags_15:
# 84 "data/maps/InsideOfTruck/scripts.pory"
	dynmultichoice 10, 100, TRUE, 3, 0, DYN_MULTICHOICE_CB_NONE, InsideOfTruck_EventScript_SetIntroFlags_Text_1, InsideOfTruck_EventScript_SetIntroFlags_Text_2, InsideOfTruck_EventScript_SetIntroFlags_Text_3
# 85 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_24
InsideOfTruck_EventScript_SetIntroFlags_14:
# 88 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_15
# 90 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_22
InsideOfTruck_EventScript_SetIntroFlags_21:
# 97 "data/maps/InsideOfTruck/scripts.pory"
	checkplayergender
# 98 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, MALE
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_27
# 100 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, FEMALE
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_28
InsideOfTruck_EventScript_SetIntroFlags_26:
# 103 "data/maps/InsideOfTruck/scripts.pory"
	releaseall
	return

InsideOfTruck_EventScript_SetIntroFlags_9:
# 64 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RESTRICTED_MODE
	goto InsideOfTruck_EventScript_SetIntroFlags_2

InsideOfTruck_EventScript_SetIntroFlags_10:
# 67 "data/maps/InsideOfTruck/scripts.pory"
	msgbox RestrictedModeInfo
	goto InsideOfTruck_EventScript_SetIntroFlags_2

InsideOfTruck_EventScript_SetIntroFlags_17:
# 75 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RESOURCE_MODE
	goto InsideOfTruck_EventScript_SetIntroFlags_6

InsideOfTruck_EventScript_SetIntroFlags_18:
# 78 "data/maps/InsideOfTruck/scripts.pory"
	msgbox ResourceModeInfo
	goto InsideOfTruck_EventScript_SetIntroFlags_6

InsideOfTruck_EventScript_SetIntroFlags_22:
# 91 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_6
# 92 "data/maps/InsideOfTruck/scripts.pory"
	dynmultichoice 10, 100, TRUE, 5, 0, DYN_MULTICHOICE_CB_NONE, InsideOfTruck_EventScript_SetIntroFlags_Text_7, InsideOfTruck_EventScript_SetIntroFlags_Text_8, InsideOfTruck_EventScript_SetIntroFlags_Text_9, InsideOfTruck_EventScript_SetIntroFlags_Text_10, InsideOfTruck_EventScript_SetIntroFlags_Text_11, InsideOfTruck_EventScript_SetIntroFlags_Text_12, InsideOfTruck_EventScript_SetIntroFlags_Text_13, InsideOfTruck_EventScript_SetIntroFlags_Text_14, InsideOfTruck_EventScript_SetIntroFlags_Text_15, InsideOfTruck_EventScript_SetIntroFlags_Text_16, InsideOfTruck_EventScript_SetIntroFlags_Text_17, InsideOfTruck_EventScript_SetIntroFlags_Text_18, InsideOfTruck_EventScript_SetIntroFlags_Text_19, InsideOfTruck_EventScript_SetIntroFlags_Text_20, InsideOfTruck_EventScript_SetIntroFlags_Text_21, InsideOfTruck_EventScript_SetIntroFlags_Text_22, InsideOfTruck_EventScript_SetIntroFlags_Text_23, InsideOfTruck_EventScript_SetIntroFlags_Text_24
# 93 "data/maps/InsideOfTruck/scripts.pory"
	copyvar VAR_MONOTYPE, VAR_RESULT
# 94 "data/maps/InsideOfTruck/scripts.pory"
	addvar VAR_MONOTYPE, 1
	goto InsideOfTruck_EventScript_SetIntroFlags_21

InsideOfTruck_EventScript_SetIntroFlags_24:
# 86 "data/maps/InsideOfTruck/scripts.pory"
	msgbox MonotypeInfo
	goto InsideOfTruck_EventScript_SetIntroFlags_14

InsideOfTruck_EventScript_SetIntroFlags_27:
# 99 "data/maps/InsideOfTruck/scripts.pory"
	goto InsideOfTruck_EventScript_SetIntroFlagsMale
	goto InsideOfTruck_EventScript_SetIntroFlags_26

InsideOfTruck_EventScript_SetIntroFlags_28:
# 101 "data/maps/InsideOfTruck/scripts.pory"
	goto InsideOfTruck_EventScript_SetIntroFlagsFemale
	goto InsideOfTruck_EventScript_SetIntroFlags_26


InsideOfTruck_EventScript_SetIntroFlags_Text_0:
# 60 "data/maps/InsideOfTruck/scripts.pory"
	.string "Will you opt-in to Restricted Mode?$"

InsideOfTruck_EventScript_SetIntroFlags_Text_1:
# 62 "data/maps/InsideOfTruck/scripts.pory"
	.string "Yes$"

InsideOfTruck_EventScript_SetIntroFlags_Text_2:
# 62 "data/maps/InsideOfTruck/scripts.pory"
	.string "No$"

InsideOfTruck_EventScript_SetIntroFlags_Text_3:
# 62 "data/maps/InsideOfTruck/scripts.pory"
	.string "Info$"

InsideOfTruck_EventScript_SetIntroFlags_Text_4:
# 71 "data/maps/InsideOfTruck/scripts.pory"
	.string "Will you opt-in to Resource Mode?$"

InsideOfTruck_EventScript_SetIntroFlags_Text_5:
# 82 "data/maps/InsideOfTruck/scripts.pory"
	.string "Will you do a monotype run?$"

InsideOfTruck_EventScript_SetIntroFlags_Text_6:
# 91 "data/maps/InsideOfTruck/scripts.pory"
	.string "Please choose the monotype.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_7:
# 92 "data/maps/InsideOfTruck/scripts.pory"
	.string "Normal$"

InsideOfTruck_EventScript_SetIntroFlags_Text_8:
# 92 "data/maps/InsideOfTruck/scripts.pory"
	.string "Fighting$"

InsideOfTruck_EventScript_SetIntroFlags_Text_9:
# 92 "data/maps/InsideOfTruck/scripts.pory"
	.string "Flying$"

InsideOfTruck_EventScript_SetIntroFlags_Text_10:
# 92 "data/maps/InsideOfTruck/scripts.pory"
	.string "Poison$"

InsideOfTruck_EventScript_SetIntroFlags_Text_11:
# 92 "data/maps/InsideOfTruck/scripts.pory"
	.string "Ground$"

InsideOfTruck_EventScript_SetIntroFlags_Text_12:
# 92 "data/maps/InsideOfTruck/scripts.pory"
	.string "Rock$"

InsideOfTruck_EventScript_SetIntroFlags_Text_13:
# 92 "data/maps/InsideOfTruck/scripts.pory"
	.string "Bug$"

InsideOfTruck_EventScript_SetIntroFlags_Text_14:
# 92 "data/maps/InsideOfTruck/scripts.pory"
	.string "Ghost$"

InsideOfTruck_EventScript_SetIntroFlags_Text_15:
# 92 "data/maps/InsideOfTruck/scripts.pory"
	.string "Steel$"

InsideOfTruck_EventScript_SetIntroFlags_Text_16:
# 92 "data/maps/InsideOfTruck/scripts.pory"
	.string "Fire$"

InsideOfTruck_EventScript_SetIntroFlags_Text_17:
# 92 "data/maps/InsideOfTruck/scripts.pory"
	.string "Water$"

InsideOfTruck_EventScript_SetIntroFlags_Text_18:
# 92 "data/maps/InsideOfTruck/scripts.pory"
	.string "Grass$"

InsideOfTruck_EventScript_SetIntroFlags_Text_19:
# 92 "data/maps/InsideOfTruck/scripts.pory"
	.string "Electric$"

InsideOfTruck_EventScript_SetIntroFlags_Text_20:
# 92 "data/maps/InsideOfTruck/scripts.pory"
	.string "Psychic$"

InsideOfTruck_EventScript_SetIntroFlags_Text_21:
# 92 "data/maps/InsideOfTruck/scripts.pory"
	.string "Ice$"

InsideOfTruck_EventScript_SetIntroFlags_Text_22:
# 92 "data/maps/InsideOfTruck/scripts.pory"
	.string "Dragon$"

InsideOfTruck_EventScript_SetIntroFlags_Text_23:
# 92 "data/maps/InsideOfTruck/scripts.pory"
	.string "Dark$"

InsideOfTruck_EventScript_SetIntroFlags_Text_24:
# 92 "data/maps/InsideOfTruck/scripts.pory"
	.string "Fairy$"

BeforeBegginning::
# 106 "data/maps/InsideOfTruck/scripts.pory"
	.string "Before begginning your game, \n"
	.string "Let's configure some settings. \p$"

RestrictedModeInfo::
# 111 "data/maps/InsideOfTruck/scripts.pory"
	.string "Restricted mode adds constraints, \n"
	.string "for balance reasons.\p"
	.string "Certain moves, items, and abilities \n"
	.string "are less available.\p"
	.string "Bag items can't be used \n"
	.string "in trainer battles. \p"
	.string "Item Clause is enforced \n"
	.string "for certain boss fights. \p$"

ResourceModeInfo::
# 122 "data/maps/InsideOfTruck/scripts.pory"
	.string "Restricted mode emphasizes finite supply, \n"
	.string "for those who want more decision-making. \p"
	.string "TMs, tutors, and move relearners \n"
	.string "have limited use.\p"
	.string "Consumable items do not regenerate, \n"
	.string "and berries can't be planted. \p$"

MonotypeInfo::
# 131 "data/maps/InsideOfTruck/scripts.pory"
	.string "For monotype runs, each monotype has \n"
	.string "custom wild encounters and gifts. \p"
	.string "Split Evolutions are constrained: A Wurmple in\n"
	.string "Mono Poison will always evolve into a Cascoon. \p$"

random::
# 138 "data/maps/InsideOfTruck/scripts.pory"
	.string "Temporary test \n$"
