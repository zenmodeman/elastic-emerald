Common_EventScript_PkmnCenterTutor::
# 2 "data/scripts/pkmn_center_tutor.pory"
	lock
# 3 "data/scripts/pkmn_center_tutor.pory"
	faceplayer
# 4 "data/scripts/pkmn_center_tutor.pory"
	msgbox Common_EventScript_PkmnCenterTutor_Text_0
# 5 "data/scripts/pkmn_center_tutor.pory"
	dynmultichoice 0, 100, FALSE, 4, 0, DYN_MULTICHOICE_CB_NONE, Common_EventScript_PkmnCenterTutor_Text_1, Common_EventScript_PkmnCenterTutor_Text_2, Common_EventScript_PkmnCenterTutor_Text_3, Common_EventScript_PkmnCenterTutor_Text_4
# 6 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_RESULT, 0
	goto_if_eq Common_EventScript_PkmnCenterTutor_2
# 8 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_RESULT, 1
	goto_if_eq Common_EventScript_PkmnCenterTutor_3
# 10 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_RESULT, 2
	goto_if_eq Common_EventScript_PkmnCenterTutor_4
# 12 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_RESULT, 3
	goto_if_eq Common_EventScript_PkmnCenterTutor_5
# 12 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq Common_EventScript_PkmnCenterTutor_5
Common_EventScript_PkmnCenterTutor_1:
# 15 "data/scripts/pkmn_center_tutor.pory"
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
	call CheckTriumphs
	goto Common_EventScript_PkmnCenterTutor_1

Common_EventScript_PkmnCenterTutor_5:
# 13 "data/scripts/pkmn_center_tutor.pory"
	goto CenterRejected
	goto Common_EventScript_PkmnCenterTutor_1


CenterMoveTutor::
# 19 "data/scripts/pkmn_center_tutor.pory"
	goto_if_set FLAG_RESOURCE_MODE, CenterMoveTutor_8
CenterMoveTutor_6:
# 27 "data/scripts/pkmn_center_tutor.pory"
	goto_if_set FLAG_RESOURCE_MODE, CenterMoveTutor_5
CenterMoveTutor_4:
# 36 "data/scripts/pkmn_center_tutor.pory"
	msgbox CenterMoveTutor_Text_1, MSGBOX_YESNO
# 37 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_RESULT, 1
	goto_if_eq CenterMoveTutor_15
CenterMoveTutor_1:
# 43 "data/scripts/pkmn_center_tutor.pory"
	release
	return

CenterMoveTutor_2:
# 20 "data/scripts/pkmn_center_tutor.pory"
	msgbox CenterMoveTutor_Text_0
# 21 "data/scripts/pkmn_center_tutor.pory"
	msgbox CenterMoveTutor_Text_1, MSGBOX_YESNO
# 22 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_RESULT, 1
	goto_if_eq CenterMoveTutor_11
	goto CenterMoveTutor_1

CenterMoveTutor_3:
# 28 "data/scripts/pkmn_center_tutor.pory"
	buffernumberstring STR_VAR_1, VAR_REMAINING_TUTOR
# 29 "data/scripts/pkmn_center_tutor.pory"
	msgbox CenterMoveTutor_Text_3, MSGBOX_YESNO
# 30 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_RESULT, 1
	goto_if_eq CenterMoveTutor_13
	goto CenterMoveTutor_1

CenterMoveTutor_5:
# 27 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_REMAINING_TUTOR, 0
	goto_if_gt CenterMoveTutor_3
	goto CenterMoveTutor_4

CenterMoveTutor_8:
# 19 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_REMAINING_TUTOR, 0
	goto_if_eq CenterMoveTutor_2
	goto CenterMoveTutor_6

CenterMoveTutor_11:
# 23 "data/scripts/pkmn_center_tutor.pory"
	call ChooseMoveTutorMon
# 24 "data/scripts/pkmn_center_tutor.pory"
	waitstate
# 25 "data/scripts/pkmn_center_tutor.pory"
	msgbox CenterMoveTutor_Text_2
	goto CenterMoveTutor_1

CenterMoveTutor_13:
# 31 "data/scripts/pkmn_center_tutor.pory"
	call ChooseMoveTutorMon
# 32 "data/scripts/pkmn_center_tutor.pory"
	waitstate
# 33 "data/scripts/pkmn_center_tutor.pory"
	msgbox CenterMoveTutor_Text_2
	goto CenterMoveTutor_1

CenterMoveTutor_15:
# 38 "data/scripts/pkmn_center_tutor.pory"
	call ChooseMoveTutorMon
# 39 "data/scripts/pkmn_center_tutor.pory"
	waitstate
# 40 "data/scripts/pkmn_center_tutor.pory"
	msgbox CenterMoveTutor_Text_2
	goto CenterMoveTutor_1


ChooseMoveTutorMon::
# 46 "data/scripts/pkmn_center_tutor.pory"
	msgbox ChooseMoveTutorMon_Text_0
# 47 "data/scripts/pkmn_center_tutor.pory"
	setvar VAR_TEMP_9, MOVE_TUTOR_CENTER
# 48 "data/scripts/pkmn_center_tutor.pory"
	special ChooseMonForCenterMoveTutor
# 49 "data/scripts/pkmn_center_tutor.pory"
	waitstate
# 50 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_0x8004, PARTY_NOTHING_CHOSEN
	goto_if_ne ChooseMoveTutorMon_3
ChooseMoveTutorMon_2:
# 54 "data/scripts/pkmn_center_tutor.pory"
	goto CenterRejected
	return

ChooseMoveTutorMon_1:
# 51 "data/scripts/pkmn_center_tutor.pory"
	msgbox ChooseMoveTutorMon_Text_1
# 52 "data/scripts/pkmn_center_tutor.pory"
	special TeachNPCMoveTutorMove
	return

ChooseMoveTutorMon_3:
# 50 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_0x8005, 0
	goto_if_ne ChooseMoveTutorMon_1
	goto ChooseMoveTutorMon_2


TakeCenterNap::
# 59 "data/scripts/pkmn_center_tutor.pory"
	msgbox TakeCenterNap_Text_0, MSGBOX_YESNO
# 60 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_RESULT, 1
	goto_if_eq TakeCenterNap_1
	return

TakeCenterNap_1:
# 61 "data/scripts/pkmn_center_tutor.pory"
	fadescreen FADE_TO_BLACK
# 62 "data/scripts/pkmn_center_tutor.pory"
	special NpcAdvanceTime
# 63 "data/scripts/pkmn_center_tutor.pory"
	fadescreen FADE_FROM_BLACK
# 64 "data/scripts/pkmn_center_tutor.pory"
	msgbox TakeCenterNap_Text_1
	return


CheckTriumphs::
# 69 "data/scripts/pkmn_center_tutor.pory"
	msgbox CheckTriumphs_Text_0
# 70 "data/scripts/pkmn_center_tutor.pory"
	special ChoosePartyMon
# 71 "data/scripts/pkmn_center_tutor.pory"
	waitstate
# 72 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_0x8004, PARTY_NOTHING_CHOSEN
	goto_if_ne CheckTriumphs_1
	return

CheckTriumphs_1:
# 73 "data/scripts/pkmn_center_tutor.pory"
	special Script_BufferChosenMonTriumph
# 74 "data/scripts/pkmn_center_tutor.pory"
	msgbox gStringVar4
	return


CenterRejected::
# 79 "data/scripts/pkmn_center_tutor.pory"
	msgbox CenterRejected_Text_0
# 80 "data/scripts/pkmn_center_tutor.pory"
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
	.string "Check Triumphs$"

Common_EventScript_PkmnCenterTutor_Text_4:
# 5 "data/scripts/pkmn_center_tutor.pory"
	.string "Cancel$"

CenterMoveTutor_Text_0:
# 20 "data/scripts/pkmn_center_tutor.pory"
	.string "You don't have any tutor points. Only\n"
	.string "certain Pokemon that the League has\l"
	.string "made exceptions for can be tutored.$"

CenterMoveTutor_Text_1:
# 21 "data/scripts/pkmn_center_tutor.pory"
	.string "Are you interested in teaching a move?$"

CenterMoveTutor_Text_2:
# 25 "data/scripts/pkmn_center_tutor.pory"
	.string "Have a nice day.$"

CenterMoveTutor_Text_3:
# 29 "data/scripts/pkmn_center_tutor.pory"
	.string "You have {STR_VAR_1} tutor points.\n"
	.string "Are you interested in teaching a move?$"

ChooseMoveTutorMon_Text_0:
# 46 "data/scripts/pkmn_center_tutor.pory"
	.string "Select pokemon to teach.$"

ChooseMoveTutorMon_Text_1:
# 51 "data/scripts/pkmn_center_tutor.pory"
	.string "Teach Which Move?$"

TakeCenterNap_Text_0:
# 59 "data/scripts/pkmn_center_tutor.pory"
	.string "Would you like to take an 8-hour rest\n"
	.string "here?$"

TakeCenterNap_Text_1:
# 64 "data/scripts/pkmn_center_tutor.pory"
	.string "Hope you had a nice rest!$"

CheckTriumphs_Text_0:
# 69 "data/scripts/pkmn_center_tutor.pory"
	.string "Whose triumphs would you like to check?$"

CenterRejected_Text_0:
# 79 "data/scripts/pkmn_center_tutor.pory"
	.string "Come back if you change your mind!$"
