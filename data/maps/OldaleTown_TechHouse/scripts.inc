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
# 19 "data/maps/OldaleTown_TechHouse/scripts.pory"
	goto TechTutorRejected
OldaleTown_TechHouse_Master_1:
# 21 "data/maps/OldaleTown_TechHouse/scripts.pory"
	releaseall
	end

OldaleTown_TechHouse_Master_2:
# 15 "data/maps/OldaleTown_TechHouse/scripts.pory"
	call ChooseTechMoveTutorMon
# 16 "data/maps/OldaleTown_TechHouse/scripts.pory"
	waitstate
# 17 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Master_Text_5
	goto OldaleTown_TechHouse_Master_1


ChooseTechMoveTutorMon::
# 26 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox ChooseTechMoveTutorMon_Text_0
# 27 "data/maps/OldaleTown_TechHouse/scripts.pory"
	special ChooseMonForCenterMoveTutor
# 28 "data/maps/OldaleTown_TechHouse/scripts.pory"
	waitstate
# 29 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_0x8004, PARTY_NOTHING_CHOSEN
	goto_if_ne ChooseTechMoveTutorMon_2
	return

ChooseTechMoveTutorMon_1:
# 30 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox ChooseTechMoveTutorMon_Text_1
# 31 "data/maps/OldaleTown_TechHouse/scripts.pory"
	setvar VAR_TEMP_9, MOVE_TUTOR_TECH
# 32 "data/maps/OldaleTown_TechHouse/scripts.pory"
	special TeachNPCMoveTutorMove
	return

ChooseTechMoveTutorMon_2:
# 29 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_0x8005, 0
	goto_if_ne ChooseTechMoveTutorMon_1
	return


TechTutorRejected::
# 37 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox TechTutorRejected_Text_0
# 38 "data/maps/OldaleTown_TechHouse/scripts.pory"
	releaseall
	end


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
	.string "Moves like Embargo, Gastro Acid, and\n"
	.string "Heal Block - people never think about\l"
	.string "these gems, but I do!$"

OldaleTown_TechHouse_Master_Text_3:
# 12 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "If you want to learn them, I'll teach\n"
	.string "you for no charge!$"

OldaleTown_TechHouse_Master_Text_4:
# 13 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Would you like to learn some niche\n"
	.string "moves?$"

OldaleTown_TechHouse_Master_Text_5:
# 17 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Come back anytime you want to learn a\n"
	.string "move!$"

ChooseTechMoveTutorMon_Text_0:
# 26 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Select pokemon to teach.$"

ChooseTechMoveTutorMon_Text_1:
# 30 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Teach Which Move?$"

TechTutorRejected_Text_0:
# 37 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Too bad, but come back if you change\n"
	.string "your mind!$"
