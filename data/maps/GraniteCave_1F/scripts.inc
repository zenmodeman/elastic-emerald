# 1 "data/maps/GraniteCave_1F/scripts.pory"

# 2 "data/maps/GraniteCave_1F/scripts.pory"
.set LOCALID_RYUJI, 3
# 3 "data/maps/GraniteCave_1F/scripts.pory"
.set LOCALID_DAICHI, 4
# 4 "data/maps/GraniteCave_1F/scripts.pory"
.set LOCALID_KENJI, 5
# 5 "data/maps/GraniteCave_1F/scripts.pory"

# 6 "data/maps/GraniteCave_1F/scripts.pory"
GraniteCave_1F_MapScripts::
# 7 "data/maps/GraniteCave_1F/scripts.pory"
	.byte 0
# 8 "data/maps/GraniteCave_1F/scripts.pory"

# 9 "data/maps/GraniteCave_1F/scripts.pory"
GraniteCave_1F_EventScript_Hiker::
# 10 "data/maps/GraniteCave_1F/scripts.pory"
	lock
# 11 "data/maps/GraniteCave_1F/scripts.pory"
	faceplayer
# 12 "data/maps/GraniteCave_1F/scripts.pory"
	goto_if_set FLAG_RECEIVED_HM_FLASH, GraniteCave_1F_EventScript_ReceivedFlash
# 13 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_Text_GetsDarkAheadHereYouGo, MSGBOX_DEFAULT
# 14 "data/maps/GraniteCave_1F/scripts.pory"
	giveitem ITEM_HM_FLASH
# 15 "data/maps/GraniteCave_1F/scripts.pory"
	setflag FLAG_RECEIVED_HM_FLASH
# 16 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
# 17 "data/maps/GraniteCave_1F/scripts.pory"
	release
# 18 "data/maps/GraniteCave_1F/scripts.pory"
	end
# 19 "data/maps/GraniteCave_1F/scripts.pory"

# 20 "data/maps/GraniteCave_1F/scripts.pory"
GraniteCave_1F_EventScript_ReceivedFlash::
# 21 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_Text_ExplainFlash, MSGBOX_DEFAULT
# 22 "data/maps/GraniteCave_1F/scripts.pory"
	release
# 23 "data/maps/GraniteCave_1F/scripts.pory"
	end
# 24 "data/maps/GraniteCave_1F/scripts.pory"

# 25 "data/maps/GraniteCave_1F/scripts.pory"
GraniteCave_1F_Text_GetsDarkAheadHereYouGo:
# 26 "data/maps/GraniteCave_1F/scripts.pory"
	.string "Hey, you.\n"
# 27 "data/maps/GraniteCave_1F/scripts.pory"
	.string "It gets awfully dark ahead.\l"
# 28 "data/maps/GraniteCave_1F/scripts.pory"
	.string "It'll be tough trying to explore.\p"
# 29 "data/maps/GraniteCave_1F/scripts.pory"
	.string "That guy who came by earlier…\n"
# 30 "data/maps/GraniteCave_1F/scripts.pory"
	.string "STEVEN, I think it was.\p"
# 31 "data/maps/GraniteCave_1F/scripts.pory"
	.string "He knew how to use FLASH, so he ought\n"
# 32 "data/maps/GraniteCave_1F/scripts.pory"
	.string "to be all right, but…\p"
# 33 "data/maps/GraniteCave_1F/scripts.pory"
	.string "Well, for us HIKERS, helping out those\n"
# 34 "data/maps/GraniteCave_1F/scripts.pory"
	.string "that we meet is our motto.\p"
# 35 "data/maps/GraniteCave_1F/scripts.pory"
	.string "Here you go, I'll pass this on to you.$"
# 36 "data/maps/GraniteCave_1F/scripts.pory"

# 37 "data/maps/GraniteCave_1F/scripts.pory"
GraniteCave_1F_Text_ExplainFlash:
# 38 "data/maps/GraniteCave_1F/scripts.pory"
	.string "Teach that hidden move FLASH to\n"
# 39 "data/maps/GraniteCave_1F/scripts.pory"
	.string "a POKéMON and use it.\p"
# 40 "data/maps/GraniteCave_1F/scripts.pory"
	.string "It lights up even the inky darkness\n"
# 41 "data/maps/GraniteCave_1F/scripts.pory"
	.string "of caves.\p"
# 42 "data/maps/GraniteCave_1F/scripts.pory"
	.string "But, to use it, you need the GYM BADGE\n"
# 43 "data/maps/GraniteCave_1F/scripts.pory"
	.string "from DEWFORD's POKéMON GYM.$"

GraniteCave_1F_ProtectivePad_Kenji::
# 47 "data/maps/GraniteCave_1F/scripts.pory"
	lock
# 48 "data/maps/GraniteCave_1F/scripts.pory"
	faceplayer
# 49 "data/maps/GraniteCave_1F/scripts.pory"
	goto_if_set TRAINER_FLAGS_START + TRAINER_KENJI, GraniteCave_1F_ProtectivePad_Kenji_2
GraniteCave_1F_ProtectivePad_Kenji_1:
# 52 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_ProtectivePad_Kenji_Text_0
# 53 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_ProtectivePad_Kenji_Text_1, MSGBOX_YESNO
# 54 "data/maps/GraniteCave_1F/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq GraniteCave_1F_ProtectivePad_Kenji_5
# 64 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_ProtectivePad_Kenji_Text_7
# 65 "data/maps/GraniteCave_1F/scripts.pory"
	applymovement LOCALID_KENJI, Common_Movement_FaceOriginalDirection
# 66 "data/maps/GraniteCave_1F/scripts.pory"
	waitmovement LOCALID_KENJI
GraniteCave_1F_ProtectivePad_Kenji_4:
# 68 "data/maps/GraniteCave_1F/scripts.pory"
	release
	end

GraniteCave_1F_ProtectivePad_Kenji_2:
# 50 "data/maps/GraniteCave_1F/scripts.pory"
	goto Kenji_Beaten
	goto GraniteCave_1F_ProtectivePad_Kenji_1

GraniteCave_1F_ProtectivePad_Kenji_5:
# 55 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_ProtectivePad_Kenji_Text_2
# 56 "data/maps/GraniteCave_1F/scripts.pory"
	trainerbattle_no_intro TRAINER_KENJI, GraniteCave_1F_ProtectivePad_Kenji_Text_3
# 57 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_ProtectivePad_Kenji_Text_4
# 58 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_ProtectivePad_Kenji_Text_5
# 59 "data/maps/GraniteCave_1F/scripts.pory"
	giveitem ITEM_PROTECTIVE_PADS
# 60 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_ProtectivePad_Kenji_Text_6
# 61 "data/maps/GraniteCave_1F/scripts.pory"
	applymovement LOCALID_KENJI, Common_Movement_FaceOriginalDirection
# 62 "data/maps/GraniteCave_1F/scripts.pory"
	waitmovement LOCALID_KENJI
	goto GraniteCave_1F_ProtectivePad_Kenji_4


Kenji_Beaten::
# 72 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox Kenji_Beaten_Text_0
# 73 "data/maps/GraniteCave_1F/scripts.pory"
	applymovement LOCALID_KENJI, Common_Movement_FaceOriginalDirection
# 74 "data/maps/GraniteCave_1F/scripts.pory"
	waitmovement LOCALID_KENJI
# 75 "data/maps/GraniteCave_1F/scripts.pory"
	release
	end


GraniteCave_1F_MuscleBand_Daichi::
# 80 "data/maps/GraniteCave_1F/scripts.pory"
	lock
# 81 "data/maps/GraniteCave_1F/scripts.pory"
	faceplayer
# 82 "data/maps/GraniteCave_1F/scripts.pory"
	goto_if_set TRAINER_FLAGS_START + TRAINER_DAICHI, GraniteCave_1F_MuscleBand_Daichi_2
GraniteCave_1F_MuscleBand_Daichi_1:
# 85 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_MuscleBand_Daichi_Text_0
# 86 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_MuscleBand_Daichi_Text_1, MSGBOX_YESNO
# 88 "data/maps/GraniteCave_1F/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq GraniteCave_1F_MuscleBand_Daichi_5
# 98 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_MuscleBand_Daichi_Text_7
# 99 "data/maps/GraniteCave_1F/scripts.pory"
	applymovement LOCALID_DAICHI, Common_Movement_FaceOriginalDirection
# 100 "data/maps/GraniteCave_1F/scripts.pory"
	waitmovement LOCALID_DAICHI
GraniteCave_1F_MuscleBand_Daichi_4:
# 102 "data/maps/GraniteCave_1F/scripts.pory"
	release
	end

GraniteCave_1F_MuscleBand_Daichi_2:
# 83 "data/maps/GraniteCave_1F/scripts.pory"
	goto Daichi_Beaten
	goto GraniteCave_1F_MuscleBand_Daichi_1

GraniteCave_1F_MuscleBand_Daichi_5:
# 89 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_MuscleBand_Daichi_Text_2
# 90 "data/maps/GraniteCave_1F/scripts.pory"
	trainerbattle_no_intro TRAINER_DAICHI, GraniteCave_1F_MuscleBand_Daichi_Text_3
# 91 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_MuscleBand_Daichi_Text_4
# 92 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_MuscleBand_Daichi_Text_5
# 93 "data/maps/GraniteCave_1F/scripts.pory"
	giveitem ITEM_MUSCLE_BAND
# 94 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_MuscleBand_Daichi_Text_6
# 95 "data/maps/GraniteCave_1F/scripts.pory"
	applymovement LOCALID_DAICHI, Common_Movement_FaceOriginalDirection
# 96 "data/maps/GraniteCave_1F/scripts.pory"
	waitmovement LOCALID_DAICHI
	goto GraniteCave_1F_MuscleBand_Daichi_4


Daichi_Beaten::
# 107 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox Daichi_Beaten_Text_0
# 108 "data/maps/GraniteCave_1F/scripts.pory"
	applymovement LOCALID_DAICHI, Common_Movement_FaceOriginalDirection
# 109 "data/maps/GraniteCave_1F/scripts.pory"
	waitmovement LOCALID_DAICHI
# 110 "data/maps/GraniteCave_1F/scripts.pory"
	release
	end


GraniteCave_1F_BlackBelt_Leader_Ryuji::
# 115 "data/maps/GraniteCave_1F/scripts.pory"
	lock
# 116 "data/maps/GraniteCave_1F/scripts.pory"
	faceplayer
# 117 "data/maps/GraniteCave_1F/scripts.pory"
	goto_if_unset FLAG_BADGE02_GET, GraniteCave_1F_BlackBelt_Leader_Ryuji_2
# 123 "data/maps/GraniteCave_1F/scripts.pory"
	goto_if_set TRAINER_FLAGS_START + TRAINER_DAICHI, GraniteCave_1F_BlackBelt_Leader_Ryuji_7
GraniteCave_1F_BlackBelt_Leader_Ryuji_6:
# 148 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_12
# 149 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_13
# 150 "data/maps/GraniteCave_1F/scripts.pory"
	applymovement LOCALID_RYUJI, Common_Movement_FaceOriginalDirection
# 151 "data/maps/GraniteCave_1F/scripts.pory"
	waitmovement LOCALID_RYUJI
GraniteCave_1F_BlackBelt_Leader_Ryuji_1:
# 154 "data/maps/GraniteCave_1F/scripts.pory"
	release
	end

GraniteCave_1F_BlackBelt_Leader_Ryuji_2:
# 118 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_0
# 119 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_1
# 120 "data/maps/GraniteCave_1F/scripts.pory"
	applymovement LOCALID_RYUJI, Common_Movement_FaceOriginalDirection
# 121 "data/maps/GraniteCave_1F/scripts.pory"
	waitmovement LOCALID_RYUJI
	goto GraniteCave_1F_BlackBelt_Leader_Ryuji_1

GraniteCave_1F_BlackBelt_Leader_Ryuji_5:
# 124 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_2
# 125 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_3, MSGBOX_YESNO
# 126 "data/maps/GraniteCave_1F/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq GraniteCave_1F_BlackBelt_Leader_Ryuji_10
# 142 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_11
# 143 "data/maps/GraniteCave_1F/scripts.pory"
	applymovement LOCALID_RYUJI, Common_Movement_FaceOriginalDirection
# 144 "data/maps/GraniteCave_1F/scripts.pory"
	waitmovement LOCALID_RYUJI
	goto GraniteCave_1F_BlackBelt_Leader_Ryuji_1

GraniteCave_1F_BlackBelt_Leader_Ryuji_7:
# 123 "data/maps/GraniteCave_1F/scripts.pory"
	goto_if_set TRAINER_FLAGS_START + TRAINER_KENJI, GraniteCave_1F_BlackBelt_Leader_Ryuji_5
	goto GraniteCave_1F_BlackBelt_Leader_Ryuji_6

GraniteCave_1F_BlackBelt_Leader_Ryuji_10:
# 127 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_4
# 128 "data/maps/GraniteCave_1F/scripts.pory"
	trainerbattle_no_intro TRAINER_RYUJI, GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_5
# 129 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_6
# 130 "data/maps/GraniteCave_1F/scripts.pory"
	giveitem ITEM_BLACK_BELT
# 131 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_7
# 132 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_8
# 133 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_9
# 134 "data/maps/GraniteCave_1F/scripts.pory"
	msgbox GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_10
# 135 "data/maps/GraniteCave_1F/scripts.pory"
	fadescreen FADE_TO_BLACK
# 136 "data/maps/GraniteCave_1F/scripts.pory"
	setflag FLAG_HIDE_GRANITE_BLACK_BELTS
# 137 "data/maps/GraniteCave_1F/scripts.pory"
	removeobject LOCALID_RYUJI
# 138 "data/maps/GraniteCave_1F/scripts.pory"
	removeobject LOCALID_KENJI
# 139 "data/maps/GraniteCave_1F/scripts.pory"
	removeobject LOCALID_DAICHI
# 140 "data/maps/GraniteCave_1F/scripts.pory"
	fadescreen FADE_FROM_BLACK
	goto GraniteCave_1F_BlackBelt_Leader_Ryuji_1


GraniteCave_1F_ProtectivePad_Kenji_Text_0:
# 52 "data/maps/GraniteCave_1F/scripts.pory"
	.string "With my Protective Pads, hitting these\n"
	.string "rocks don't phase me, for me or my\l"
	.string "Pokemon!$"

GraniteCave_1F_ProtectivePad_Kenji_Text_1:
# 53 "data/maps/GraniteCave_1F/scripts.pory"
	.string "I'll show you my pads first hand. How\n"
	.string "about it?$"

GraniteCave_1F_ProtectivePad_Kenji_Text_2:
# 55 "data/maps/GraniteCave_1F/scripts.pory"
	.string "Prepare yourself!$"

GraniteCave_1F_ProtectivePad_Kenji_Text_3:
# 56 "data/maps/GraniteCave_1F/scripts.pory"
	.string "We got crushed!$"

GraniteCave_1F_ProtectivePad_Kenji_Text_4:
# 57 "data/maps/GraniteCave_1F/scripts.pory"
	.string "My Protective Pads weren't enough. I'll\n"
	.string "have to improve on my other techniques.$"

GraniteCave_1F_ProtectivePad_Kenji_Text_5:
# 58 "data/maps/GraniteCave_1F/scripts.pory"
	.string "But I'm impressed with your skill. Here,\n"
	.string "have some Protective Pads yourself.$"

GraniteCave_1F_ProtectivePad_Kenji_Text_6:
# 60 "data/maps/GraniteCave_1F/scripts.pory"
	.string "I'll go back to improving my skills.$"

GraniteCave_1F_ProtectivePad_Kenji_Text_7:
# 64 "data/maps/GraniteCave_1F/scripts.pory"
	.string "Back to training, then.$"

Kenji_Beaten_Text_0:
# 72 "data/maps/GraniteCave_1F/scripts.pory"
	.string "I still have more techniques to hone.$"

GraniteCave_1F_MuscleBand_Daichi_Text_0:
# 85 "data/maps/GraniteCave_1F/scripts.pory"
	.string "My Pokemon and I wear a Muscle Band to\n"
	.string "show our might. These rocks are\l"
	.string "nothing!$"

GraniteCave_1F_MuscleBand_Daichi_Text_1:
# 86 "data/maps/GraniteCave_1F/scripts.pory"
	.string "We'll win Pokemon battles too. Wanna see\n"
	.string "how strong we are?$"

GraniteCave_1F_MuscleBand_Daichi_Text_2:
# 89 "data/maps/GraniteCave_1F/scripts.pory"
	.string "Let's go!$"

GraniteCave_1F_MuscleBand_Daichi_Text_3:
# 90 "data/maps/GraniteCave_1F/scripts.pory"
	.string "We need more power!$"

GraniteCave_1F_MuscleBand_Daichi_Text_4:
# 91 "data/maps/GraniteCave_1F/scripts.pory"
	.string "We weren't enough. I'll have to keep\n"
	.string "getting stronger!$"

GraniteCave_1F_MuscleBand_Daichi_Text_5:
# 92 "data/maps/GraniteCave_1F/scripts.pory"
	.string "But I can see your power. Your Pokemon\n"
	.string "should wear a Muscle Band too!$"

GraniteCave_1F_MuscleBand_Daichi_Text_6:
# 94 "data/maps/GraniteCave_1F/scripts.pory"
	.string "I'll go back to getting stronger.$"

GraniteCave_1F_MuscleBand_Daichi_Text_7:
# 98 "data/maps/GraniteCave_1F/scripts.pory"
	.string "Okay, I'll get stronger!$"

Daichi_Beaten_Text_0:
# 107 "data/maps/GraniteCave_1F/scripts.pory"
	.string "I'm going to toughen up!$"

GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_0:
# 118 "data/maps/GraniteCave_1F/scripts.pory"
	.string "These rocks are wonderful training. No\n"
	.string "wonder Brawly became skilled enough to\l"
	.string "train with Bruno. I strive to beat\l"
	.string "Brawly one day.$"

GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_1:
# 119 "data/maps/GraniteCave_1F/scripts.pory"
	.string "Now if you'll excuse me, I need to get\n"
	.string "back to training.$"

GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_2:
# 124 "data/maps/GraniteCave_1F/scripts.pory"
	.string "Wow, you've beaten my students and\n"
	.string "Brawly too?$"

GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_3:
# 125 "data/maps/GraniteCave_1F/scripts.pory"
	.string "I'd love to train my duo Pokemon with\n"
	.string "you. What do you say?$"

GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_4:
# 127 "data/maps/GraniteCave_1F/scripts.pory"
	.string "I'll show you my experience!$"

GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_5:
# 128 "data/maps/GraniteCave_1F/scripts.pory"
	.string "As expected of a Knuckle Badge holder!$"

GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_6:
# 129 "data/maps/GraniteCave_1F/scripts.pory"
	.string "Truly wonderful fighting! You're worthy\n"
	.string "of a Black Belt$"

GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_7:
# 131 "data/maps/GraniteCave_1F/scripts.pory"
	.string "Wear that and stay proud of your\n"
	.string "strength!$"

GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_8:
# 132 "data/maps/GraniteCave_1F/scripts.pory"
	.string "My students and I have been training\n"
	.string "here long enough. We should head\l"
	.string "somewhere else.$"

GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_9:
# 133 "data/maps/GraniteCave_1F/scripts.pory"
	.string "One day I hope you meet my master. He's\n"
	.string "a true expert!$"

GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_10:
# 134 "data/maps/GraniteCave_1F/scripts.pory"
	.string "Farewell!$"

GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_11:
# 142 "data/maps/GraniteCave_1F/scripts.pory"
	.string "Too bad, then I'll keep training!$"

GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_12:
# 148 "data/maps/GraniteCave_1F/scripts.pory"
	.string "Oh, you beat Brawly? You're mighty\n"
	.string "tough.$"

GraniteCave_1F_BlackBelt_Leader_Ryuji_Text_13:
# 149 "data/maps/GraniteCave_1F/scripts.pory"
	.string "I'm still not done my training, but you\n"
	.string "might want to fight my students.$"
