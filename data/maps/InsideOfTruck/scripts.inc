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
# 61 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_REMAINING_RELEARNER, 2
# 62 "data/maps/InsideOfTruck/scripts.pory"
	setvar VAR_REMAINING_TUTOR, 2
# 64 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_0
InsideOfTruck_EventScript_SetIntroFlags_3:
# 66 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_1
# 67 "data/maps/InsideOfTruck/scripts.pory"
	dynmultichoice 7, 100, TRUE, 3, 2, DYN_MULTICHOICE_CB_NONE, InsideOfTruck_EventScript_SetIntroFlags_Text_2, InsideOfTruck_EventScript_SetIntroFlags_Text_3, InsideOfTruck_EventScript_SetIntroFlags_Text_4
# 68 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_9
# 71 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_10
InsideOfTruck_EventScript_SetIntroFlags_2:
# 77 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_3
InsideOfTruck_EventScript_SetIntroFlags_7:
# 81 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_9
# 82 "data/maps/InsideOfTruck/scripts.pory"
	dynmultichoice 7, 100, TRUE, 3, 2, DYN_MULTICHOICE_CB_NONE, InsideOfTruck_EventScript_SetIntroFlags_Text_2, InsideOfTruck_EventScript_SetIntroFlags_Text_3, InsideOfTruck_EventScript_SetIntroFlags_Text_4
# 83 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_17
# 86 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_18
InsideOfTruck_EventScript_SetIntroFlags_6:
# 92 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_7
InsideOfTruck_EventScript_SetIntroFlags_15:
# 95 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_14
# 96 "data/maps/InsideOfTruck/scripts.pory"
	dynmultichoice 7, 100, TRUE, 3, 2, DYN_MULTICHOICE_CB_NONE, InsideOfTruck_EventScript_SetIntroFlags_Text_2, InsideOfTruck_EventScript_SetIntroFlags_Text_3, InsideOfTruck_EventScript_SetIntroFlags_Text_4
# 97 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_25
# 100 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_26
InsideOfTruck_EventScript_SetIntroFlags_14:
# 105 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_15
InsideOfTruck_EventScript_SetIntroFlags_23:
# 108 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_18
# 109 "data/maps/InsideOfTruck/scripts.pory"
	dynmultichoice 7, 100, TRUE, 3, 2, DYN_MULTICHOICE_CB_NONE, InsideOfTruck_EventScript_SetIntroFlags_Text_2, InsideOfTruck_EventScript_SetIntroFlags_Text_3, InsideOfTruck_EventScript_SetIntroFlags_Text_4
# 110 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_33
# 113 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_34
InsideOfTruck_EventScript_SetIntroFlags_22:
# 117 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_23
InsideOfTruck_EventScript_SetIntroFlags_31:
# 120 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_21
# 121 "data/maps/InsideOfTruck/scripts.pory"
	dynmultichoice 7, 100, TRUE, 3, 2, DYN_MULTICHOICE_CB_NONE, InsideOfTruck_EventScript_SetIntroFlags_Text_2, InsideOfTruck_EventScript_SetIntroFlags_Text_3, InsideOfTruck_EventScript_SetIntroFlags_Text_4
# 122 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_41
# 125 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_42
InsideOfTruck_EventScript_SetIntroFlags_30:
# 130 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_31
InsideOfTruck_EventScript_SetIntroFlags_39:
# 134 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_25
# 135 "data/maps/InsideOfTruck/scripts.pory"
	dynmultichoice 7, 100, TRUE, 3, 2, DYN_MULTICHOICE_CB_NONE, InsideOfTruck_EventScript_SetIntroFlags_Text_2, InsideOfTruck_EventScript_SetIntroFlags_Text_3, InsideOfTruck_EventScript_SetIntroFlags_Text_4
# 136 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_51
InsideOfTruck_EventScript_SetIntroFlags_50:
# 144 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_53
InsideOfTruck_EventScript_SetIntroFlags_38:
# 148 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_39
# 150 "data/maps/InsideOfTruck/scripts.pory"
	checkplayergender
# 151 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, MALE
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_46
# 153 "data/maps/InsideOfTruck/scripts.pory"
	compare VAR_RESULT, FEMALE
	goto_if_eq InsideOfTruck_EventScript_SetIntroFlags_47
InsideOfTruck_EventScript_SetIntroFlags_45:
# 156 "data/maps/InsideOfTruck/scripts.pory"
	releaseall
	return

InsideOfTruck_EventScript_SetIntroFlags_9:
# 69 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RESTRICTED_MODE
	goto InsideOfTruck_EventScript_SetIntroFlags_2

InsideOfTruck_EventScript_SetIntroFlags_10:
# 72 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_5
# 73 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_6
# 74 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_7
# 75 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_8
	goto InsideOfTruck_EventScript_SetIntroFlags_2

InsideOfTruck_EventScript_SetIntroFlags_17:
# 84 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_RESOURCE_MODE
	goto InsideOfTruck_EventScript_SetIntroFlags_6

InsideOfTruck_EventScript_SetIntroFlags_18:
# 87 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_10
# 88 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_11
# 89 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_12
# 90 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_13
	goto InsideOfTruck_EventScript_SetIntroFlags_6

InsideOfTruck_EventScript_SetIntroFlags_25:
# 98 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_EV_MODE
	goto InsideOfTruck_EventScript_SetIntroFlags_14

InsideOfTruck_EventScript_SetIntroFlags_26:
# 101 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_15
# 102 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_16
# 103 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_17
	goto InsideOfTruck_EventScript_SetIntroFlags_14

InsideOfTruck_EventScript_SetIntroFlags_33:
# 111 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_LEVEL_CAP
	goto InsideOfTruck_EventScript_SetIntroFlags_22

InsideOfTruck_EventScript_SetIntroFlags_34:
# 114 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_19
# 115 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_20
	goto InsideOfTruck_EventScript_SetIntroFlags_22

InsideOfTruck_EventScript_SetIntroFlags_41:
# 123 "data/maps/InsideOfTruck/scripts.pory"
	setflag FLAG_CURATED_TERA
	goto InsideOfTruck_EventScript_SetIntroFlags_30

InsideOfTruck_EventScript_SetIntroFlags_42:
# 126 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_22
# 127 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_23
# 128 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_24
	goto InsideOfTruck_EventScript_SetIntroFlags_30

InsideOfTruck_EventScript_SetIntroFlags_46:
# 152 "data/maps/InsideOfTruck/scripts.pory"
	goto InsideOfTruck_EventScript_SetIntroFlagsMale
	goto InsideOfTruck_EventScript_SetIntroFlags_45

InsideOfTruck_EventScript_SetIntroFlags_47:
# 154 "data/maps/InsideOfTruck/scripts.pory"
	goto InsideOfTruck_EventScript_SetIntroFlagsFemale
	goto InsideOfTruck_EventScript_SetIntroFlags_45

InsideOfTruck_EventScript_SetIntroFlags_51:
# 137 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_26
# 138 "data/maps/InsideOfTruck/scripts.pory"
	dynmultichoice 5, 100, TRUE, 4, 0, DYN_MULTICHOICE_CB_NONE, InsideOfTruck_EventScript_SetIntroFlags_Text_27, InsideOfTruck_EventScript_SetIntroFlags_Text_28, InsideOfTruck_EventScript_SetIntroFlags_Text_29, InsideOfTruck_EventScript_SetIntroFlags_Text_30, InsideOfTruck_EventScript_SetIntroFlags_Text_31, InsideOfTruck_EventScript_SetIntroFlags_Text_32, InsideOfTruck_EventScript_SetIntroFlags_Text_33, InsideOfTruck_EventScript_SetIntroFlags_Text_34, InsideOfTruck_EventScript_SetIntroFlags_Text_35, InsideOfTruck_EventScript_SetIntroFlags_Text_36, InsideOfTruck_EventScript_SetIntroFlags_Text_37, InsideOfTruck_EventScript_SetIntroFlags_Text_38, InsideOfTruck_EventScript_SetIntroFlags_Text_39, InsideOfTruck_EventScript_SetIntroFlags_Text_40, InsideOfTruck_EventScript_SetIntroFlags_Text_41, InsideOfTruck_EventScript_SetIntroFlags_Text_42, InsideOfTruck_EventScript_SetIntroFlags_Text_43, InsideOfTruck_EventScript_SetIntroFlags_Text_44
# 139 "data/maps/InsideOfTruck/scripts.pory"
	copyvar VAR_MONOTYPE, VAR_RESULT
# 140 "data/maps/InsideOfTruck/scripts.pory"
	addvar VAR_MONOTYPE, 1
# 141 "data/maps/InsideOfTruck/scripts.pory"
	addvar VAR_REMAINING_RELEARNER, 2
# 142 "data/maps/InsideOfTruck/scripts.pory"
	addvar VAR_REMAINING_TUTOR, 2
	goto InsideOfTruck_EventScript_SetIntroFlags_50

InsideOfTruck_EventScript_SetIntroFlags_53:
# 145 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_45
# 146 "data/maps/InsideOfTruck/scripts.pory"
	msgbox InsideOfTruck_EventScript_SetIntroFlags_Text_46
	goto InsideOfTruck_EventScript_SetIntroFlags_38


InsideOfTruck_EventScript_SetIntroFlags_Text_0:
# 64 "data/maps/InsideOfTruck/scripts.pory"
	.string "Before begginning your game, let's\n"
	.string "configure some settings.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_1:
# 66 "data/maps/InsideOfTruck/scripts.pory"
	.string "Will you opt-in to Restricted Mode?$"

InsideOfTruck_EventScript_SetIntroFlags_Text_2:
# 67 "data/maps/InsideOfTruck/scripts.pory"
	.string "Yes$"

InsideOfTruck_EventScript_SetIntroFlags_Text_3:
# 67 "data/maps/InsideOfTruck/scripts.pory"
	.string "No$"

InsideOfTruck_EventScript_SetIntroFlags_Text_4:
# 67 "data/maps/InsideOfTruck/scripts.pory"
	.string "Info$"

InsideOfTruck_EventScript_SetIntroFlags_Text_5:
# 72 "data/maps/InsideOfTruck/scripts.pory"
	.string "Restricted mode adds constraints for\n"
	.string "balance reasons.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_6:
# 73 "data/maps/InsideOfTruck/scripts.pory"
	.string "Certain moves, items, and abilities are\n"
	.string "less available.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_7:
# 74 "data/maps/InsideOfTruck/scripts.pory"
	.string "Bag items can't be used during Trainer\n"
	.string "Battles.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_8:
# 75 "data/maps/InsideOfTruck/scripts.pory"
	.string "Item clause is forced during Gym Leader\n"
	.string "and Elite Four Battles.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_9:
# 81 "data/maps/InsideOfTruck/scripts.pory"
	.string "Will you opt-in to Resource Mode?$"

InsideOfTruck_EventScript_SetIntroFlags_Text_10:
# 87 "data/maps/InsideOfTruck/scripts.pory"
	.string "Resource Mode emphasizes finite supply\n"
	.string "to enforce more decision-making.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_11:
# 88 "data/maps/InsideOfTruck/scripts.pory"
	.string "TMs, tutors, and move relearners have\n"
	.string "limited use.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_12:
# 89 "data/maps/InsideOfTruck/scripts.pory"
	.string "Consumable items do not regenerate\n"
	.string "after battle, and berries cannot be\l"
	.string "planted.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_13:
# 90 "data/maps/InsideOfTruck/scripts.pory"
	.string "Choosing to not play with Resource\n"
	.string "Mode grants much more flexibility.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_14:
# 95 "data/maps/InsideOfTruck/scripts.pory"
	.string "Will you play in EV-Mode?$"

InsideOfTruck_EventScript_SetIntroFlags_Text_15:
# 101 "data/maps/InsideOfTruck/scripts.pory"
	.string "EV-Mode means effort values can be\n"
	.string "acquired, and trainers can also have\l"
	.string "them.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_16:
# 102 "data/maps/InsideOfTruck/scripts.pory"
	.string "To prevent requiring full EVs\n"
	.string "immediately, there are EV caps\l"
	.string "throughout.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_17:
# 103 "data/maps/InsideOfTruck/scripts.pory"
	.string "If not playing in EV-mode, the player\n"
	.string "cannot increase effort values, and\l"
	.string "trainers will not have them.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_18:
# 108 "data/maps/InsideOfTruck/scripts.pory"
	.string "Will you play with level caps?$"

InsideOfTruck_EventScript_SetIntroFlags_Text_19:
# 114 "data/maps/InsideOfTruck/scripts.pory"
	.string "This mode prevents you from exceeding\n"
	.string "certain levels based on progression.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_20:
# 115 "data/maps/InsideOfTruck/scripts.pory"
	.string "Most of the time, the level cap for\n"
	.string "experience gain is 1 higher than the\l"
	.string "cap for rare candies or exp. candies$"

InsideOfTruck_EventScript_SetIntroFlags_Text_21:
# 120 "data/maps/InsideOfTruck/scripts.pory"
	.string "Will you play with curated teras?$"

InsideOfTruck_EventScript_SetIntroFlags_Text_22:
# 126 "data/maps/InsideOfTruck/scripts.pory"
	.string "Curated teras means each pokemon with\n"
	.string "have a pre-determined tera type.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_23:
# 127 "data/maps/InsideOfTruck/scripts.pory"
	.string "This adds another layer to balancing\n"
	.string "and niches for different Pokemon.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_24:
# 128 "data/maps/InsideOfTruck/scripts.pory"
	.string "If you do not choose curated teras, a\n"
	.string "Pokemon's tera type will be random.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_25:
# 134 "data/maps/InsideOfTruck/scripts.pory"
	.string "Will you do a monotype run?$"

InsideOfTruck_EventScript_SetIntroFlags_Text_26:
# 137 "data/maps/InsideOfTruck/scripts.pory"
	.string "Please choose the monotype.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_27:
# 138 "data/maps/InsideOfTruck/scripts.pory"
	.string "Normal$"

InsideOfTruck_EventScript_SetIntroFlags_Text_28:
# 138 "data/maps/InsideOfTruck/scripts.pory"
	.string "Fighting$"

InsideOfTruck_EventScript_SetIntroFlags_Text_29:
# 138 "data/maps/InsideOfTruck/scripts.pory"
	.string "Flying$"

InsideOfTruck_EventScript_SetIntroFlags_Text_30:
# 138 "data/maps/InsideOfTruck/scripts.pory"
	.string "Poison$"

InsideOfTruck_EventScript_SetIntroFlags_Text_31:
# 138 "data/maps/InsideOfTruck/scripts.pory"
	.string "Ground$"

InsideOfTruck_EventScript_SetIntroFlags_Text_32:
# 138 "data/maps/InsideOfTruck/scripts.pory"
	.string "Rock$"

InsideOfTruck_EventScript_SetIntroFlags_Text_33:
# 138 "data/maps/InsideOfTruck/scripts.pory"
	.string "Bug$"

InsideOfTruck_EventScript_SetIntroFlags_Text_34:
# 138 "data/maps/InsideOfTruck/scripts.pory"
	.string "Ghost$"

InsideOfTruck_EventScript_SetIntroFlags_Text_35:
# 138 "data/maps/InsideOfTruck/scripts.pory"
	.string "Steel$"

InsideOfTruck_EventScript_SetIntroFlags_Text_36:
# 138 "data/maps/InsideOfTruck/scripts.pory"
	.string "Fire$"

InsideOfTruck_EventScript_SetIntroFlags_Text_37:
# 138 "data/maps/InsideOfTruck/scripts.pory"
	.string "Water$"

InsideOfTruck_EventScript_SetIntroFlags_Text_38:
# 138 "data/maps/InsideOfTruck/scripts.pory"
	.string "Grass$"

InsideOfTruck_EventScript_SetIntroFlags_Text_39:
# 138 "data/maps/InsideOfTruck/scripts.pory"
	.string "Electric$"

InsideOfTruck_EventScript_SetIntroFlags_Text_40:
# 138 "data/maps/InsideOfTruck/scripts.pory"
	.string "Psychic$"

InsideOfTruck_EventScript_SetIntroFlags_Text_41:
# 138 "data/maps/InsideOfTruck/scripts.pory"
	.string "Ice$"

InsideOfTruck_EventScript_SetIntroFlags_Text_42:
# 138 "data/maps/InsideOfTruck/scripts.pory"
	.string "Dragon$"

InsideOfTruck_EventScript_SetIntroFlags_Text_43:
# 138 "data/maps/InsideOfTruck/scripts.pory"
	.string "Dark$"

InsideOfTruck_EventScript_SetIntroFlags_Text_44:
# 138 "data/maps/InsideOfTruck/scripts.pory"
	.string "Fairy$"

InsideOfTruck_EventScript_SetIntroFlags_Text_45:
# 145 "data/maps/InsideOfTruck/scripts.pory"
	.string "For monotype runs, each monotype has\n"
	.string "custom wild encounters and gifts.$"

InsideOfTruck_EventScript_SetIntroFlags_Text_46:
# 146 "data/maps/InsideOfTruck/scripts.pory"
	.string "Split Evolutions are constrained: a\n"
	.string "Wurmple in Mono Poison will always\l"
	.string "evolve into a Cascoon.$"
