Common_EventScript_PkmnCenterTutor::
# 2 "data/scripts/pkmn_center_tutor.pory"
	lock
# 3 "data/scripts/pkmn_center_tutor.pory"
	faceplayer
# 4 "data/scripts/pkmn_center_tutor.pory"
	msgbox Common_EventScript_PkmnCenterTutor_Text_0
# 5 "data/scripts/pkmn_center_tutor.pory"
	dynmultichoice 0, 100, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, Common_EventScript_PkmnCenterTutor_Text_1, Common_EventScript_PkmnCenterTutor_Text_2, Common_EventScript_PkmnCenterTutor_Text_3
# 6 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_RESULT, 0
	goto_if_eq Common_EventScript_PkmnCenterTutor_2
# 8 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_RESULT, 1
	goto_if_eq Common_EventScript_PkmnCenterTutor_3
# 10 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_RESULT, 2
	goto_if_eq Common_EventScript_PkmnCenterTutor_4
# 10 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq Common_EventScript_PkmnCenterTutor_4
Common_EventScript_PkmnCenterTutor_1:
# 13 "data/scripts/pkmn_center_tutor.pory"
	msgbox Common_EventScript_PkmnCenterTutor_Text_4
# 14 "data/scripts/pkmn_center_tutor.pory"
	release
	return

Common_EventScript_PkmnCenterTutor_2:
# 7 "data/scripts/pkmn_center_tutor.pory"
	call CenterMoveTutor
	goto Common_EventScript_PkmnCenterTutor_1

Common_EventScript_PkmnCenterTutor_3:
# 9 "data/scripts/pkmn_center_tutor.pory"
	call TakeCenterNap
	goto Common_EventScript_PkmnCenterTutor_1

Common_EventScript_PkmnCenterTutor_4:
# 11 "data/scripts/pkmn_center_tutor.pory"
	goto CenterRejected
	goto Common_EventScript_PkmnCenterTutor_1


CenterMoveTutor::
# 18 "data/scripts/pkmn_center_tutor.pory"
	goto_if_set FLAG_RESOURCE_MODE, CenterMoveTutor_7
CenterMoveTutor_5:
# 20 "data/scripts/pkmn_center_tutor.pory"
	goto_if_set FLAG_RESOURCE_MODE, CenterMoveTutor_4
CenterMoveTutor_3:
# 27 "data/scripts/pkmn_center_tutor.pory"
	msgbox CenterMoveTutor_Text_2, MSGBOX_YESNO
# 28 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_RESULT, 1
	goto_if_eq CenterMoveTutor_12
	return

CenterMoveTutor_1:
# 19 "data/scripts/pkmn_center_tutor.pory"
	msgbox CenterMoveTutor_Text_0
	return

CenterMoveTutor_2:
# 21 "data/scripts/pkmn_center_tutor.pory"
	buffernumberstring STR_VAR_1, VAR_REMAINING_TUTOR
# 22 "data/scripts/pkmn_center_tutor.pory"
	msgbox CenterMoveTutor_Text_1, MSGBOX_YESNO
# 23 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_RESULT, 1
	goto_if_eq CenterMoveTutor_10
	return

CenterMoveTutor_4:
# 20 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_REMAINING_TUTOR, 0
	goto_if_gt CenterMoveTutor_2
	goto CenterMoveTutor_3

CenterMoveTutor_7:
# 18 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_REMAINING_TUTOR, 0
	goto_if_eq CenterMoveTutor_1
	goto CenterMoveTutor_5

CenterMoveTutor_10:
# 24 "data/scripts/pkmn_center_tutor.pory"
	call ChooseMoveTutorMon
	return

CenterMoveTutor_12:
# 29 "data/scripts/pkmn_center_tutor.pory"
	call ChooseMoveTutorMon
	return


ChooseMoveTutorMon::
# 35 "data/scripts/pkmn_center_tutor.pory"
	msgbox ChooseMoveTutorMon_Text_0
# 36 "data/scripts/pkmn_center_tutor.pory"
	special ChooseMonForCenterMoveTutor
# 37 "data/scripts/pkmn_center_tutor.pory"
	waitstate
# 38 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_0x8004, PARTY_NOTHING_CHOSEN
	goto_if_ne ChooseMoveTutorMon_3
ChooseMoveTutorMon_2:
# 43 "data/scripts/pkmn_center_tutor.pory"
	goto CenterRejected
	return

ChooseMoveTutorMon_1:
# 39 "data/scripts/pkmn_center_tutor.pory"
	msgbox ChooseMoveTutorMon_Text_1
# 40 "data/scripts/pkmn_center_tutor.pory"
	setvar VAR_TEMP_9, MOVE_TUTOR_CENTER
# 41 "data/scripts/pkmn_center_tutor.pory"
	special TeachNPCMoveTutorMove
	return

ChooseMoveTutorMon_3:
# 38 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_0x8005, 0
	goto_if_ne ChooseMoveTutorMon_1
	goto ChooseMoveTutorMon_2


TakeCenterNap::
# 48 "data/scripts/pkmn_center_tutor.pory"
	msgbox TakeCenterNap_Text_0, MSGBOX_YESNO
# 49 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_RESULT, 1
	goto_if_eq TakeCenterNap_1
	return

TakeCenterNap_1:
# 50 "data/scripts/pkmn_center_tutor.pory"
	fadescreen FADE_TO_BLACK
# 51 "data/scripts/pkmn_center_tutor.pory"
	special NpcAdvanceTime
# 52 "data/scripts/pkmn_center_tutor.pory"
	fadescreen FADE_FROM_BLACK
# 53 "data/scripts/pkmn_center_tutor.pory"
	msgbox TakeCenterNap_Text_1
	return


CenterRejected::
# 58 "data/scripts/pkmn_center_tutor.pory"
	msgbox CenterRejected_Text_0
# 59 "data/scripts/pkmn_center_tutor.pory"
	release
	end


Common_EventScript_PkmnCenterTutor_Text_0:
# 4 "data/scripts/pkmn_center_tutor.pory"
	.string "Welcome, to the Pokemon Center Service\n"
	.string "Station. How May I help you?$"

Common_EventScript_PkmnCenterTutor_Text_1:
# 5 "data/scripts/pkmn_center_tutor.pory"
	.string "Tutor Move$"

Common_EventScript_PkmnCenterTutor_Text_2:
# 5 "data/scripts/pkmn_center_tutor.pory"
	.string "Take a Rest$"

Common_EventScript_PkmnCenterTutor_Text_3:
# 5 "data/scripts/pkmn_center_tutor.pory"
	.string "Cancel$"

Common_EventScript_PkmnCenterTutor_Text_4:
# 13 "data/scripts/pkmn_center_tutor.pory"
	.string "Have a nice day!$"

CenterMoveTutor_Text_0:
# 19 "data/scripts/pkmn_center_tutor.pory"
	.string "Sorry, you don't have any tutor points.\n"
	.string "You can get more points by acquiring\l"
	.string "gym badges.$"

CenterMoveTutor_Text_1:
# 22 "data/scripts/pkmn_center_tutor.pory"
	.string "You have {STR_VAR_1} tutor points.\n"
	.string "Are you interested in teaching a move?$"

CenterMoveTutor_Text_2:
# 27 "data/scripts/pkmn_center_tutor.pory"
	.string "Are you interested in teaching a move?$"

ChooseMoveTutorMon_Text_0:
# 35 "data/scripts/pkmn_center_tutor.pory"
	.string "Select pokemon to teach$"

ChooseMoveTutorMon_Text_1:
# 39 "data/scripts/pkmn_center_tutor.pory"
	.string "Teach Which Move?$"

TakeCenterNap_Text_0:
# 48 "data/scripts/pkmn_center_tutor.pory"
	.string "Would you like to take an 8-hour rest\n"
	.string "here?$"

TakeCenterNap_Text_1:
# 53 "data/scripts/pkmn_center_tutor.pory"
	.string "Hope you had a nice rest!$"

CenterRejected_Text_0:
# 58 "data/scripts/pkmn_center_tutor.pory"
	.string "Come back if you change your mind!$"
