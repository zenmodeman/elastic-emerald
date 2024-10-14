# 1 "data/maps/OldaleTown_TechHouse/scripts.pory"

# 2 "data/maps/OldaleTown_TechHouse/scripts.pory"
OldaleTown_TechHouse_MapScripts::
# 3 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.byte 0

OldaleTown_TechHouse_Master::
# 7 "data/maps/OldaleTown_TechHouse/scripts.pory"
	lock
# 8 "data/maps/OldaleTown_TechHouse/scripts.pory"
	faceplayer
# 9 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Master_Text_0
# 10 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Master_Text_1
# 11 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Master_Text_2
# 12 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Master_Text_3
# 13 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Master_Text_4, MSGBOX_YESNO
# 14 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq OldaleTown_TechHouse_Master_2
OldaleTown_TechHouse_Master_1:
# 55 "data/maps/OldaleTown_TechHouse/scripts.pory"
	releaseall
	end

OldaleTown_TechHouse_Master_2:
# 15 "data/maps/OldaleTown_TechHouse/scripts.pory"
	dynmultichoice 5, 100, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, OldaleTown_TechHouse_Master_Text_5, OldaleTown_TechHouse_Master_Text_6, OldaleTown_TechHouse_Master_Text_7, OldaleTown_TechHouse_Master_Text_8, OldaleTown_TechHouse_Master_Text_9, OldaleTown_TechHouse_Master_Text_10, OldaleTown_TechHouse_Master_Text_11, OldaleTown_TechHouse_Master_Text_12, OldaleTown_TechHouse_Master_Text_13, OldaleTown_TechHouse_Master_Text_14, OldaleTown_TechHouse_Master_Text_15, OldaleTown_TechHouse_Master_Text_16, OldaleTown_TechHouse_Master_Text_17, OldaleTown_TechHouse_Master_Text_18, OldaleTown_TechHouse_Master_Text_19, OldaleTown_TechHouse_Master_Text_20
# 18 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq OldaleTown_TechHouse_Master_5
# 20 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq OldaleTown_TechHouse_Master_6
# 22 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq OldaleTown_TechHouse_Master_7
# 24 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq OldaleTown_TechHouse_Master_8
# 26 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_RESULT, 3
	goto_if_eq OldaleTown_TechHouse_Master_9
# 28 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_RESULT, 4
	goto_if_eq OldaleTown_TechHouse_Master_10
# 30 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_RESULT, 5
	goto_if_eq OldaleTown_TechHouse_Master_11
# 32 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_RESULT, 6
	goto_if_eq OldaleTown_TechHouse_Master_12
# 34 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_RESULT, 7
	goto_if_eq OldaleTown_TechHouse_Master_13
# 36 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_RESULT, 8
	goto_if_eq OldaleTown_TechHouse_Master_14
# 38 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_RESULT, 9
	goto_if_eq OldaleTown_TechHouse_Master_15
# 40 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_RESULT, 10
	goto_if_eq OldaleTown_TechHouse_Master_16
# 42 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_RESULT, 11
	goto_if_eq OldaleTown_TechHouse_Master_17
# 44 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_RESULT, 12
	goto_if_eq OldaleTown_TechHouse_Master_18
# 46 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_RESULT, 13
	goto_if_eq OldaleTown_TechHouse_Master_19
# 48 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_RESULT, 14
	goto_if_eq OldaleTown_TechHouse_Master_20
# 50 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_RESULT, 15
	goto_if_eq OldaleTown_TechHouse_Master_21
OldaleTown_TechHouse_Master_4:
# 53 "data/maps/OldaleTown_TechHouse/scripts.pory"
	goto TeachTechMasterTutorMove
	goto OldaleTown_TechHouse_Master_1

OldaleTown_TechHouse_Master_5:
# 19 "data/maps/OldaleTown_TechHouse/scripts.pory"
	goto TechTutorRejected
	goto OldaleTown_TechHouse_Master_4

OldaleTown_TechHouse_Master_6:
# 21 "data/maps/OldaleTown_TechHouse/scripts.pory"
	setvar VAR_0x8005, MOVE_BLOCK
	goto OldaleTown_TechHouse_Master_4

OldaleTown_TechHouse_Master_7:
# 23 "data/maps/OldaleTown_TechHouse/scripts.pory"
	setvar VAR_0x8005, MOVE_HOLD_BACK
	goto OldaleTown_TechHouse_Master_4

OldaleTown_TechHouse_Master_8:
# 25 "data/maps/OldaleTown_TechHouse/scripts.pory"
	setvar VAR_0x8005, MOVE_EMBARGO
	goto OldaleTown_TechHouse_Master_4

OldaleTown_TechHouse_Master_9:
# 27 "data/maps/OldaleTown_TechHouse/scripts.pory"
	setvar VAR_0x8005, MOVE_CORROSIVE_GAS
	goto OldaleTown_TechHouse_Master_4

OldaleTown_TechHouse_Master_10:
# 29 "data/maps/OldaleTown_TechHouse/scripts.pory"
	setvar VAR_0x8005, MOVE_HEAL_BLOCK
	goto OldaleTown_TechHouse_Master_4

OldaleTown_TechHouse_Master_11:
# 31 "data/maps/OldaleTown_TechHouse/scripts.pory"
	setvar VAR_0x8005, MOVE_LASER_FOCUS
	goto OldaleTown_TechHouse_Master_4

OldaleTown_TechHouse_Master_12:
# 33 "data/maps/OldaleTown_TechHouse/scripts.pory"
	setvar VAR_0x8005, MOVE_MUD_SPORT
	goto OldaleTown_TechHouse_Master_4

OldaleTown_TechHouse_Master_13:
# 35 "data/maps/OldaleTown_TechHouse/scripts.pory"
	setvar VAR_0x8005, MOVE_MIST
	goto OldaleTown_TechHouse_Master_4

OldaleTown_TechHouse_Master_14:
# 37 "data/maps/OldaleTown_TechHouse/scripts.pory"
	setvar VAR_0x8005, MOVE_WATER_SPORT
	goto OldaleTown_TechHouse_Master_4

OldaleTown_TechHouse_Master_15:
# 39 "data/maps/OldaleTown_TechHouse/scripts.pory"
	setvar VAR_0x8005, MOVE_SPITE
	goto OldaleTown_TechHouse_Master_4

OldaleTown_TechHouse_Master_16:
# 41 "data/maps/OldaleTown_TechHouse/scripts.pory"
	setvar VAR_0x8005, MOVE_MAGIC_ROOM
	goto OldaleTown_TechHouse_Master_4

OldaleTown_TechHouse_Master_17:
# 43 "data/maps/OldaleTown_TechHouse/scripts.pory"
	setvar VAR_0x8005, MOVE_WONDER_ROOM
	goto OldaleTown_TechHouse_Master_4

OldaleTown_TechHouse_Master_18:
# 45 "data/maps/OldaleTown_TechHouse/scripts.pory"
	setvar VAR_0x8005, MOVE_IMPRISON
	goto OldaleTown_TechHouse_Master_4

OldaleTown_TechHouse_Master_19:
# 47 "data/maps/OldaleTown_TechHouse/scripts.pory"
	setvar VAR_0x8005, MOVE_VENOM_DRENCH
	goto OldaleTown_TechHouse_Master_4

OldaleTown_TechHouse_Master_20:
# 49 "data/maps/OldaleTown_TechHouse/scripts.pory"
	setvar VAR_0x8005, MOVE_SWALLOW
	goto OldaleTown_TechHouse_Master_4

OldaleTown_TechHouse_Master_21:
# 51 "data/maps/OldaleTown_TechHouse/scripts.pory"
	setvar VAR_0x8005, MOVE_TELEKINESIS
	goto OldaleTown_TechHouse_Master_4


TechTutorRejected::
# 60 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox TechTutorRejected_Text_0
# 61 "data/maps/OldaleTown_TechHouse/scripts.pory"
	releaseall
	end


TeachTechMasterTutorMove::
# 66 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox TeachTechMasterTutorMove_Text_0
# 67 "data/maps/OldaleTown_TechHouse/scripts.pory"
	fadescreen FADE_TO_BLACK
# 68 "data/maps/OldaleTown_TechHouse/scripts.pory"
	special ChooseMonForMoveTutor
# 69 "data/maps/OldaleTown_TechHouse/scripts.pory"
	waitstate
# 70 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq TeachTechMasterTutorMove_2
TeachTechMasterTutorMove_1:
# 73 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox TeachTechMasterTutorMove_Text_1
# 74 "data/maps/OldaleTown_TechHouse/scripts.pory"
	releaseall
	end

TeachTechMasterTutorMove_2:
# 71 "data/maps/OldaleTown_TechHouse/scripts.pory"
	goto TechTutorRejected
	goto TeachTechMasterTutorMove_1


OldaleTown_TechHouse_Master_Text_0:
# 9 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Welcome! I'm known around here as the\n"
	.string "Tech Sage!$"

OldaleTown_TechHouse_Master_Text_1:
# 10 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "You see, while most folks focus on the\n"
	.string "obvious strengths and weaknesses of\l"
	.string "Pokémon battles, I find beauty in the\l"
	.string "overlooked.$"

OldaleTown_TechHouse_Master_Text_2:
# 11 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Moves like Embargo, Mist, and Laser\n"
	.string "Focus - people never think about these\l"
	.string "gems, but I do!$"

OldaleTown_TechHouse_Master_Text_3:
# 12 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "If you want to learn them, I'll teach\n"
	.string "you for no charge!$"

OldaleTown_TechHouse_Master_Text_4:
# 13 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Would you like to learn some niche\n"
	.string "moves?$"

OldaleTown_TechHouse_Master_Text_5:
# 15 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Block$"

OldaleTown_TechHouse_Master_Text_6:
# 15 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Hold Back$"

OldaleTown_TechHouse_Master_Text_7:
# 15 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Embargo$"

OldaleTown_TechHouse_Master_Text_8:
# 15 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Corrosive Gas$"

OldaleTown_TechHouse_Master_Text_9:
# 16 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Heal Block$"

OldaleTown_TechHouse_Master_Text_10:
# 16 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Laser Focus$"

OldaleTown_TechHouse_Master_Text_11:
# 16 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Mud Sport$"

OldaleTown_TechHouse_Master_Text_12:
# 16 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Mist$"

OldaleTown_TechHouse_Master_Text_13:
# 16 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Water Sport$"

OldaleTown_TechHouse_Master_Text_14:
# 16 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Spite$"

OldaleTown_TechHouse_Master_Text_15:
# 17 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Magic Room$"

OldaleTown_TechHouse_Master_Text_16:
# 17 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Wonder Room$"

OldaleTown_TechHouse_Master_Text_17:
# 17 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Imprison$"

OldaleTown_TechHouse_Master_Text_18:
# 17 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Venom Drench$"

OldaleTown_TechHouse_Master_Text_19:
# 17 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Swallow$"

OldaleTown_TechHouse_Master_Text_20:
# 17 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Telekinesis$"

TechTutorRejected_Text_0:
# 60 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Too bad, but come back if you change\n"
	.string "your mind!$"

TeachTechMasterTutorMove_Text_0:
# 66 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Teach Move to which Pokemon?$"

TeachTechMasterTutorMove_Text_1:
# 73 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Hope you like the move!$"
