Common_EventScript_PkmnCenterTutor::
	lock
	faceplayer
	goto_if_set FLAG_RESOURCE_MODE, Common_EventScript_PkmnCenterTutor_4
Common_EventScript_PkmnCenterTutor_3:
	msgbox Common_EventScript_PkmnCenterTutor_Text_1
Common_EventScript_PkmnCenterTutor_1:
	releaseall
	return

Common_EventScript_PkmnCenterTutor_2:
	msgbox Common_EventScript_PkmnCenterTutor_Text_0
	goto Common_EventScript_PkmnCenterTutor_1

Common_EventScript_PkmnCenterTutor_4:
	compare VAR_REMAINING_TUTOR, 0
	goto_if_eq Common_EventScript_PkmnCenterTutor_2
	goto Common_EventScript_PkmnCenterTutor_3


Common_EventScript_PkmnCenterTutor_Text_0:
	.string "Sorry, you ran out of tutor points.\n"
	.string "Maybe acquire more badges$"

Common_EventScript_PkmnCenterTutor_Text_1:
	.string "Welcome, are you interested in teaching\n"
	.string "a move?$"