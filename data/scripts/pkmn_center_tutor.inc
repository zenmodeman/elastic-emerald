Common_EventScript_PkmnCenterTutor::
# 2 "data/scripts/pkmn_center_tutor.pory"
	lock
# 3 "data/scripts/pkmn_center_tutor.pory"
	faceplayer
# 5 "data/scripts/pkmn_center_tutor.pory"
	goto_if_set FLAG_RESOURCE_MODE, Common_EventScript_PkmnCenterTutor_8
Common_EventScript_PkmnCenterTutor_6:
# 7 "data/scripts/pkmn_center_tutor.pory"
	goto_if_set FLAG_RESOURCE_MODE, Common_EventScript_PkmnCenterTutor_5
Common_EventScript_PkmnCenterTutor_4:
# 14 "data/scripts/pkmn_center_tutor.pory"
	msgbox Common_EventScript_PkmnCenterTutor_Text_2, MSGBOX_YESNO
# 15 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_RESULT, 1
	goto_if_eq Common_EventScript_PkmnCenterTutor_13
Common_EventScript_PkmnCenterTutor_1:
# 19 "data/scripts/pkmn_center_tutor.pory"
	releaseall
	return

Common_EventScript_PkmnCenterTutor_2:
# 6 "data/scripts/pkmn_center_tutor.pory"
	msgbox Common_EventScript_PkmnCenterTutor_Text_0
	goto Common_EventScript_PkmnCenterTutor_1

Common_EventScript_PkmnCenterTutor_3:
# 8 "data/scripts/pkmn_center_tutor.pory"
	buffernumberstring STR_VAR_1, VAR_REMAINING_TUTOR
# 9 "data/scripts/pkmn_center_tutor.pory"
	msgbox Common_EventScript_PkmnCenterTutor_Text_1, MSGBOX_YESNO
# 10 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_RESULT, 1
	goto_if_eq Common_EventScript_PkmnCenterTutor_11
	goto Common_EventScript_PkmnCenterTutor_1

Common_EventScript_PkmnCenterTutor_5:
# 7 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_REMAINING_TUTOR, 0
	goto_if_gt Common_EventScript_PkmnCenterTutor_3
	goto Common_EventScript_PkmnCenterTutor_4

Common_EventScript_PkmnCenterTutor_8:
# 5 "data/scripts/pkmn_center_tutor.pory"
	compare VAR_REMAINING_TUTOR, 0
	goto_if_eq Common_EventScript_PkmnCenterTutor_2
	goto Common_EventScript_PkmnCenterTutor_6

Common_EventScript_PkmnCenterTutor_11:
# 11 "data/scripts/pkmn_center_tutor.pory"
	call ChooseMoveTutorMon
	goto Common_EventScript_PkmnCenterTutor_1

Common_EventScript_PkmnCenterTutor_13:
# 16 "data/scripts/pkmn_center_tutor.pory"
	call ChooseMoveTutorMon
	goto Common_EventScript_PkmnCenterTutor_1


ChooseMoveTutorMon::
# 23 "data/scripts/pkmn_center_tutor.pory"
	msgbox ChooseMoveTutorMon_Text_0
# 24 "data/scripts/pkmn_center_tutor.pory"
	special ChooseMonForCenterMoveTutor
	return


Common_EventScript_PkmnCenterTutor_Text_0:
# 6 "data/scripts/pkmn_center_tutor.pory"
	.string "Sorry, you don't have any tutor points.\n"
	.string "Come back when you have acquired a gym\l"
	.string "badge.$"

Common_EventScript_PkmnCenterTutor_Text_1:
# 9 "data/scripts/pkmn_center_tutor.pory"
	.string "Welcome, you have {STR_VAR_1} tutor\n"
	.string "points. Are you interested in teaching\l"
	.string "a move?$"

Common_EventScript_PkmnCenterTutor_Text_2:
# 14 "data/scripts/pkmn_center_tutor.pory"
	.string "Welcome, are you interested in teaching\n"
	.string "a move?$"

ChooseMoveTutorMon_Text_0:
# 23 "data/scripts/pkmn_center_tutor.pory"
	.string "Select pokemon to teach$"
