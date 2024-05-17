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
	special EnableNationalPokedex
# 60 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_REMAINING_RELEARNER, 1
# 61 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_REMAINING_TUTOR, 1
# 63 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_0
InsideOfTruck_EventScript_SetIntroFlags_3:
# 65 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_1
# 66 "data/maps/InsideOfTruck/scripts.pory"
	dynmultichoice 7, 100, TRUE, 3, 2, DYN_MULTICHOICE_CB_NONE, InsideOfTruck_EventScript_SetIntroFlags_Text_2, InsideOfTruck_EventScript_SetIntroFlags_Text_3, InsideOfTruck_EventScript_SetIntroFlags_Text_4
# 67 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_9
# 70 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_10
InsideOfTruck_EventScript_SetIntroFlags_2:
# 76 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_3
InsideOfTruck_EventScript_SetIntroFlags_7:
# 80 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_9
# 81 "data/maps/InsideOfTruck/scripts.pory"
	dynmultichoice 7, 100, TRUE, 3, 2, DYN_MULTICHOICE_CB_NONE, InsideOfTruck_EventScript_SetIntroFlags_Text_2, InsideOfTruck_EventScript_SetIntroFlags_Text_3, InsideOfTruck_EventScript_SetIntroFlags_Text_4
# 82 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_17
# 85 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_18
InsideOfTruck_EventScript_SetIntroFlags_6:
# 91 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_7
InsideOfTruck_EventScript_SetIntroFlags_15:
# 94 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_14
# 95 "data/maps/InsideOfTruck/scripts.pory"
	dynmultichoice 7, 100, TRUE, 3, 2, DYN_MULTICHOICE_CB_NONE, InsideOfTruck_EventScript_SetIntroFlags_Text_2, InsideOfTruck_EventScript_SetIntroFlags_Text_3, InsideOfTruck_EventScript_SetIntroFlags_Text_4
# 96 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_25
# 99 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_26
InsideOfTruck_EventScript_SetIntroFlags_14:
# 104 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_15
InsideOfTruck_EventScript_SetIntroFlags_23:
# 107 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_18
# 108 "data/maps/InsideOfTruck/scripts.pory"
	dynmultichoice 7, 100, TRUE, 3, 2, DYN_MULTICHOICE_CB_NONE, InsideOfTruck_EventScript_SetIntroFlags_Text_2, InsideOfTruck_EventScript_SetIntroFlags_Text_3, InsideOfTruck_EventScript_SetIntroFlags_Text_4
# 109 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_32
InsideOfTruck_EventScript_SetIntroFlags_22:
# 113 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_23
# 115 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_30
InsideOfTruck_EventScript_SetIntroFlags_29:
# 122 "data/maps/InsideOfTruck/scripts.pory"
	checkplayergender
# 123 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, MALE
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_35
# 125 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, FEMALE
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_36
InsideOfTruck_EventScript_SetIntroFlags_34:
# 128 "data/maps/InsideOfTruck/scripts.pory"
	releaseall
	return

InsideOfTruck_EventScript_SetIntroFlags_9:
# 68 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RESTRICTED_MODE
	goto InsideOfTruck_EventScript_SetIntroFlags_2

InsideOfTruck_EventScript_SetIntroFlags_10:
# 71 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_5
# 72 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_6
# 73 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_7
# 74 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_8
	goto InsideOfTruck_EventScript_SetIntroFlags_2

InsideOfTruck_EventScript_SetIntroFlags_17:
# 83 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RESOURCE_MODE
	goto InsideOfTruck_EventScript_SetIntroFlags_6

InsideOfTruck_EventScript_SetIntroFlags_18:
# 86 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_10
# 87 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_11
# 88 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_12
# 89 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_13
	goto InsideOfTruck_EventScript_SetIntroFlags_6

InsideOfTruck_EventScript_SetIntroFlags_25:
# 97 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_EV_MODE
	goto InsideOfTruck_EventScript_SetIntroFlags_14

InsideOfTruck_EventScript_SetIntroFlags_26:
# 100 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_15
# 101 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_16
# 102 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_17
	goto InsideOfTruck_EventScript_SetIntroFlags_14

InsideOfTruck_EventScript_SetIntroFlags_30:
# 116 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_21
# 117 "data/maps/InsideOfTruck/scripts.pory"
	dynmultichoice 5, 100, TRUE, 4, 0, DYN_MULTICHOICE_CB_NONE, InsideOfTruck_EventScript_SetIntroFlags_Text_22, InsideOfTruck_EventScript_SetIntroFlags_Text_23, InsideOfTruck_EventScript_SetIntroFlags_Text_24, InsideOfTruck_EventScript_SetIntroFlags_Text_25, InsideOfTruck_EventScript_SetIntroFlags_Text_26, InsideOfTruck_EventScript_SetIntroFlags_Text_27, InsideOfTruck_EventScript_SetIntroFlags_Text_28, InsideOfTruck_EventScript_SetIntroFlags_Text_29, InsideOfTruck_EventScript_SetIntroFlags_Text_30, InsideOfTruck_EventScript_SetIntroFlags_Text_31, InsideOfTruck_EventScript_SetIntroFlags_Text_32, InsideOfTruck_EventScript_SetIntroFlags_Text_33, InsideOfTruck_EventScript_SetIntroFlags_Text_34, InsideOfTruck_EventScript_SetIntroFlags_Text_35, InsideOfTruck_EventScript_SetIntroFlags_Text_36, InsideOfTruck_EventScript_SetIntroFlags_Text_37, InsideOfTruck_EventScript_SetIntroFlags_Text_38, InsideOfTruck_EventScript_SetIntroFlags_Text_39
# 118 "data/maps/InsideOfTruck/scripts.pory"
	copyvar VAR_MONOTYPE, VAR_RESULT
# 119 "data/maps/InsideOfTruck/scripts.pory"
	addvar VAR_MONOTYPE, 1
	goto InsideOfTruck_EventScript_SetIntroFlags_29

InsideOfTruck_EventScript_SetIntroFlags_32:
# 110 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_19
# 111 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_20
	goto InsideOfTruck_EventScript_SetIntroFlags_22

InsideOfTruck_EventScript_SetIntroFlags_35:
# 124 "data/maps/InsideOfTruck/scripts.pory"
	goto InsideOfTruck_EventScript_SetIntroFlagsMale
	goto InsideOfTruck_EventScript_SetIntroFlags_34

InsideOfTruck_EventScript_SetIntroFlags_36:
# 126 "data/maps/InsideOfTruck/scripts.pory"
	goto InsideOfTruck_EventScript_SetIntroFlagsFemale
	goto InsideOfTruck_EventScript_SetIntroFlags_34


InsideOfTruck_EventScript_SetIntroFlags_Text_0:
# 63 "data/maps/InsideOfTruck/scripts.pory"
	.string "Before begginning your game, let's\n"
	.string "configure some settings.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_1:
# 65 "data/maps/InsideOfTruck/scripts.pory"
	.string "Will you opt-in to Restricted Mode?$"

InsideOfTruck_EventScript_SetIntroFlags_Text_2:
# 66 "data/maps/InsideOfTruck/scripts.pory"
	.string "Yes$"

InsideOfTruck_EventScript_SetIntroFlags_Text_3:
# 66 "data/maps/InsideOfTruck/scripts.pory"
	.string "No$"

InsideOfTruck_EventScript_SetIntroFlags_Text_4:
# 66 "data/maps/InsideOfTruck/scripts.pory"
	.string "Info$"

InsideOfTruck_EventScript_SetIntroFlags_Text_5:
# 71 "data/maps/InsideOfTruck/scripts.pory"
	.string "Restricted mode adds constraints for\n"
	.string "balance reasons.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_6:
# 72 "data/maps/InsideOfTruck/scripts.pory"
	.string "Certain moves, items, and abilities are\n"
	.string "less available.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_7:
# 73 "data/maps/InsideOfTruck/scripts.pory"
	.string "Bag items can't be used during Trainer\n"
	.string "Battles.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_8:
# 74 "data/maps/InsideOfTruck/scripts.pory"
	.string "Item clause is forced during Gym Leader\n"
	.string "and Elite Four Battles.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_9:
# 80 "data/maps/InsideOfTruck/scripts.pory"
	.string "Will you opt-in to Resource Mode?$"

InsideOfTruck_EventScript_SetIntroFlags_Text_10:
# 86 "data/maps/InsideOfTruck/scripts.pory"
	.string "Resource Mode emphasizes finite supply\n"
	.string "to enforce more decision-making.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_11:
# 87 "data/maps/InsideOfTruck/scripts.pory"
	.string "TMs, tutors, and move relearners have\n"
	.string "limited use.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_12:
# 88 "data/maps/InsideOfTruck/scripts.pory"
	.string "Consumable items do not regenerate\n"
	.string "after battle, and berries cannot be\l"
	.string "planted.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_13:
# 89 "data/maps/InsideOfTruck/scripts.pory"
	.string "Choosing to not play with Resource\n"
	.string "Mode grants much more flexibility.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_14:
# 94 "data/maps/InsideOfTruck/scripts.pory"
	.string "Will you play in EV-Mode?$"

InsideOfTruck_EventScript_SetIntroFlags_Text_15:
# 100 "data/maps/InsideOfTruck/scripts.pory"
	.string "EV-Mode means effort values can be\n"
	.string "acquired, and trainers can also have\l"
	.string "them.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_16:
# 101 "data/maps/InsideOfTruck/scripts.pory"
	.string "To prevent requiring full EVs\n"
	.string "immediately, there are EV caps\l"
	.string "throughout.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_17:
# 102 "data/maps/InsideOfTruck/scripts.pory"
	.string "If not playing in EV-mode, the player\n"
	.string "cannot increase effort values, and\l"
	.string "trainers will not have them.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_18:
# 107 "data/maps/InsideOfTruck/scripts.pory"
	.string "Will you do a monotype run?$"

InsideOfTruck_EventScript_SetIntroFlags_Text_19:
# 110 "data/maps/InsideOfTruck/scripts.pory"
	.string "For monotype runs, each monotype has\n"
	.string "custom wild encounters and gifts.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_20:
# 111 "data/maps/InsideOfTruck/scripts.pory"
	.string "Split Evolutions are constrained: a\n"
	.string "Wurmple in Mono Poison will always\l"
	.string "evolve into a Cascoon.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_21:
# 116 "data/maps/InsideOfTruck/scripts.pory"
	.string "Please choose the monotype.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_22:
# 117 "data/maps/InsideOfTruck/scripts.pory"
	.string "Normal$"

InsideOfTruck_EventScript_SetIntroFlags_Text_23:
# 117 "data/maps/InsideOfTruck/scripts.pory"
	.string "Fighting$"

InsideOfTruck_EventScript_SetIntroFlags_Text_24:
# 117 "data/maps/InsideOfTruck/scripts.pory"
	.string "Flying$"

InsideOfTruck_EventScript_SetIntroFlags_Text_25:
# 117 "data/maps/InsideOfTruck/scripts.pory"
	.string "Poison$"

InsideOfTruck_EventScript_SetIntroFlags_Text_26:
# 117 "data/maps/InsideOfTruck/scripts.pory"
	.string "Ground$"

InsideOfTruck_EventScript_SetIntroFlags_Text_27:
# 117 "data/maps/InsideOfTruck/scripts.pory"
	.string "Rock$"

InsideOfTruck_EventScript_SetIntroFlags_Text_28:
# 117 "data/maps/InsideOfTruck/scripts.pory"
	.string "Bug$"

InsideOfTruck_EventScript_SetIntroFlags_Text_29:
# 117 "data/maps/InsideOfTruck/scripts.pory"
	.string "Ghost$"

InsideOfTruck_EventScript_SetIntroFlags_Text_30:
# 117 "data/maps/InsideOfTruck/scripts.pory"
	.string "Steel$"

InsideOfTruck_EventScript_SetIntroFlags_Text_31:
# 117 "data/maps/InsideOfTruck/scripts.pory"
	.string "Fire$"

InsideOfTruck_EventScript_SetIntroFlags_Text_32:
# 117 "data/maps/InsideOfTruck/scripts.pory"
	.string "Water$"

InsideOfTruck_EventScript_SetIntroFlags_Text_33:
# 117 "data/maps/InsideOfTruck/scripts.pory"
	.string "Grass$"

InsideOfTruck_EventScript_SetIntroFlags_Text_34:
# 117 "data/maps/InsideOfTruck/scripts.pory"
	.string "Electric$"

InsideOfTruck_EventScript_SetIntroFlags_Text_35:
# 117 "data/maps/InsideOfTruck/scripts.pory"
	.string "Psychic$"

InsideOfTruck_EventScript_SetIntroFlags_Text_36:
# 117 "data/maps/InsideOfTruck/scripts.pory"
	.string "Ice$"

InsideOfTruck_EventScript_SetIntroFlags_Text_37:
# 117 "data/maps/InsideOfTruck/scripts.pory"
	.string "Dragon$"

InsideOfTruck_EventScript_SetIntroFlags_Text_38:
# 117 "data/maps/InsideOfTruck/scripts.pory"
	.string "Dark$"

InsideOfTruck_EventScript_SetIntroFlags_Text_39:
# 117 "data/maps/InsideOfTruck/scripts.pory"
	.string "Fairy$"
