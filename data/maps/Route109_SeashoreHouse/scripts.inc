# 2 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 3 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_MapScripts::
# 4 "data/maps/Route109_SeashoreHouse/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Route109_SeashoreHouse_OnTransition
# 5 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.byte 0
# 6 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 7 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_OnTransition:
# 8 "data/maps/Route109_SeashoreHouse/scripts.pory"
	setflag FLAG_LANDMARK_SEASHORE_HOUSE
# 9 "data/maps/Route109_SeashoreHouse/scripts.pory"
	end
# 10 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 11 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_EventScript_Owner::
# 12 "data/maps/Route109_SeashoreHouse/scripts.pory"
	lock
# 13 "data/maps/Route109_SeashoreHouse/scripts.pory"
	faceplayer
# 14 "data/maps/Route109_SeashoreHouse/scripts.pory"
	goto_if_set FLAG_RECEIVED_6_SODA_POP, Route109_SeashoreHouse_EventScript_AlreadyReceivedSodaPop
# 15 "data/maps/Route109_SeashoreHouse/scripts.pory"
	goto_if_set FLAG_DEFEATED_SEASHORE_HOUSE, Route109_SeashoreHouse_EventScript_DefeatedTrainers
# 16 "data/maps/Route109_SeashoreHouse/scripts.pory"
	goto_if_set FLAG_TEMP_2, Route109_SeashoreHouse_EventScript_AlreadyGaveIntroduction
# 17 "data/maps/Route109_SeashoreHouse/scripts.pory"
	msgbox Route109_SeashoreHouse_Text_SeashoreHouseIntro, MSGBOX_DEFAULT
# 18 "data/maps/Route109_SeashoreHouse/scripts.pory"
	setflag FLAG_TEMP_2
# 19 "data/maps/Route109_SeashoreHouse/scripts.pory"
	release
# 20 "data/maps/Route109_SeashoreHouse/scripts.pory"
	end
# 21 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 22 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_EventScript_AlreadyGaveIntroduction::
# 23 "data/maps/Route109_SeashoreHouse/scripts.pory"
	msgbox Route109_SeashoreHouse_Text_ShowMeSomeHotMatches, MSGBOX_DEFAULT
# 24 "data/maps/Route109_SeashoreHouse/scripts.pory"
	release
# 25 "data/maps/Route109_SeashoreHouse/scripts.pory"
	end
# 26 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 27 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_EventScript_DefeatedTrainers::
# 28 "data/maps/Route109_SeashoreHouse/scripts.pory"
	msgbox Route109_SeashoreHouse_Text_TakeTheseSodaPopBottles, MSGBOX_DEFAULT
# 29 "data/maps/Route109_SeashoreHouse/scripts.pory"
	giveitem ITEM_SODA_POP, 6
# 30 "data/maps/Route109_SeashoreHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_BagFull
# 31 "data/maps/Route109_SeashoreHouse/scripts.pory"
	setflag FLAG_RECEIVED_6_SODA_POP
# 32 "data/maps/Route109_SeashoreHouse/scripts.pory"
	release
# 33 "data/maps/Route109_SeashoreHouse/scripts.pory"
	end
# 34 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 35 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_EventScript_BagFull::
# 36 "data/maps/Route109_SeashoreHouse/scripts.pory"
	msgbox Route109_SeashoreHouse_Text_BagFull, MSGBOX_DEFAULT
# 37 "data/maps/Route109_SeashoreHouse/scripts.pory"
	release
# 38 "data/maps/Route109_SeashoreHouse/scripts.pory"
	end
# 39 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 40 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_EventScript_AlreadyReceivedSodaPop::
# 41 "data/maps/Route109_SeashoreHouse/scripts.pory"
	showmoneybox 0, 0
# 42 "data/maps/Route109_SeashoreHouse/scripts.pory"
	msgbox Route109_SeashoreHouse_Text_WantToBuySodaPop, MSGBOX_YESNO
# 43 "data/maps/Route109_SeashoreHouse/scripts.pory"
	goto_if_eq VAR_RESULT, YES, Route109_SeashoreHouse_EventScript_BuySodaPop
# 44 "data/maps/Route109_SeashoreHouse/scripts.pory"
	msgbox Route109_SeashoreHouse_Text_ThatsTooBad, MSGBOX_DEFAULT
# 45 "data/maps/Route109_SeashoreHouse/scripts.pory"
	hidemoneybox
# 46 "data/maps/Route109_SeashoreHouse/scripts.pory"
	release
# 47 "data/maps/Route109_SeashoreHouse/scripts.pory"
	end
# 48 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 49 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_EventScript_BuySodaPop::
# 50 "data/maps/Route109_SeashoreHouse/scripts.pory"
	checkmoney 300
# 51 "data/maps/Route109_SeashoreHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_NotEnoughMoney
# 52 "data/maps/Route109_SeashoreHouse/scripts.pory"
	checkitemspace ITEM_SODA_POP
# 53 "data/maps/Route109_SeashoreHouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Route109_SeashoreHouse_EventScript_NotEnoughSpace
# 54 "data/maps/Route109_SeashoreHouse/scripts.pory"
	msgbox Route109_SeashoreHouse_Text_HereYouGo, MSGBOX_DEFAULT
# 55 "data/maps/Route109_SeashoreHouse/scripts.pory"
	removemoney 300
# 56 "data/maps/Route109_SeashoreHouse/scripts.pory"
	updatemoneybox
# 57 "data/maps/Route109_SeashoreHouse/scripts.pory"
.if OW_SHOW_ITEM_DESCRIPTIONS != OW_ITEM_DESCRIPTIONS_OFF
# 58 "data/maps/Route109_SeashoreHouse/scripts.pory"
	hidemoneybox
# 59 "data/maps/Route109_SeashoreHouse/scripts.pory"
	giveitem ITEM_SODA_POP
# 60 "data/maps/Route109_SeashoreHouse/scripts.pory"
.else
# 61 "data/maps/Route109_SeashoreHouse/scripts.pory"
	giveitem ITEM_SODA_POP
# 62 "data/maps/Route109_SeashoreHouse/scripts.pory"
	hidemoneybox
# 63 "data/maps/Route109_SeashoreHouse/scripts.pory"
.endif
# 64 "data/maps/Route109_SeashoreHouse/scripts.pory"
	release
# 65 "data/maps/Route109_SeashoreHouse/scripts.pory"
	end
# 66 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 67 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_EventScript_NotEnoughMoney::
# 68 "data/maps/Route109_SeashoreHouse/scripts.pory"
	msgbox Route109_SeashoreHouse_Text_NotEnoughMoney, MSGBOX_DEFAULT
# 69 "data/maps/Route109_SeashoreHouse/scripts.pory"
	hidemoneybox
# 70 "data/maps/Route109_SeashoreHouse/scripts.pory"
	release
# 71 "data/maps/Route109_SeashoreHouse/scripts.pory"
	end
# 72 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 73 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_EventScript_NotEnoughSpace::
# 74 "data/maps/Route109_SeashoreHouse/scripts.pory"
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
# 75 "data/maps/Route109_SeashoreHouse/scripts.pory"
	hidemoneybox
# 76 "data/maps/Route109_SeashoreHouse/scripts.pory"
	release
# 77 "data/maps/Route109_SeashoreHouse/scripts.pory"
	end
# 78 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 79 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_EventScript_Dwayne::
# 80 "data/maps/Route109_SeashoreHouse/scripts.pory"
	trainerbattle_single TRAINER_DWAYNE, Route109_SeashoreHouse_Text_DwayneIntro, Route109_SeashoreHouse_Text_DwayneDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
# 81 "data/maps/Route109_SeashoreHouse/scripts.pory"
	msgbox Route109_SeashoreHouse_Text_DwaynePostBattle, MSGBOX_AUTOCLOSE
# 82 "data/maps/Route109_SeashoreHouse/scripts.pory"
	end
# 83 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 84 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_EventScript_Simon::
# 85 "data/maps/Route109_SeashoreHouse/scripts.pory"
	trainerbattle_single TRAINER_SIMON, Route109_SeashoreHouse_Text_SimonIntro, Route109_SeashoreHouse_Text_SimonDefeated, Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
# 86 "data/maps/Route109_SeashoreHouse/scripts.pory"
	msgbox Route109_SeashoreHouse_Text_SimonPostBattle, MSGBOX_AUTOCLOSE
# 87 "data/maps/Route109_SeashoreHouse/scripts.pory"
	end
# 88 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 89 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_EventScript_CheckTrainersCompletion::
# 90 "data/maps/Route109_SeashoreHouse/scripts.pory"
	goto_if_not_defeated TRAINER_DWAYNE, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
# 91 "data/maps/Route109_SeashoreHouse/scripts.pory"
	goto_if_not_defeated TRAINER_JOHANNA, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
# 92 "data/maps/Route109_SeashoreHouse/scripts.pory"
	goto_if_not_defeated TRAINER_SIMON, Route109_SeashoreHouse_EventScript_TrainersNotCompleted
# 93 "data/maps/Route109_SeashoreHouse/scripts.pory"
	setflag FLAG_DEFEATED_SEASHORE_HOUSE
# 94 "data/maps/Route109_SeashoreHouse/scripts.pory"
	release
# 95 "data/maps/Route109_SeashoreHouse/scripts.pory"
	end
# 96 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 97 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_EventScript_TrainersNotCompleted::
# 98 "data/maps/Route109_SeashoreHouse/scripts.pory"
	release
# 99 "data/maps/Route109_SeashoreHouse/scripts.pory"
	end
# 100 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 101 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_Text_SeashoreHouseIntro:
# 102 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "I'm the owner of the SEASHORE HOUSE.\n"
# 103 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "But you can call me MR. SEA!\p"
# 104 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "What I love above all is to see hot\n"
# 105 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "POKéMON battles.\p"
# 106 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "Let me see that your heart burns hot!\p"
# 107 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "If you can defeat all the TRAINERS\n"
# 108 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "here, I'll reward your efforts.$"
# 109 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 110 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_Text_ShowMeSomeHotMatches:
# 111 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "Show me some hot matches!\p"
# 112 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "I run this SEASHORE HOUSE just for\n"
# 113 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "that reason alone!$"
# 114 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 115 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_Text_TakeTheseSodaPopBottles:
# 116 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "You're scorching hot!\n"
# 117 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "Those battles blazed!\l"
# 118 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "I'm more than just satisfied!\p"
# 119 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "As thanks for showing me your hot\n"
# 120 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "streak, I want you to take these.\p"
# 121 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "It's half a dozen bottles of SODA POP!$"
# 122 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 123 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_Text_BagFull:
# 124 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "Oh, but hey, your BAG's jammed full.\n"
# 125 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "I'll hang on to these for you.$"
# 126 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 127 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_Text_WantToBuySodaPop:
# 128 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "Want to buy some SODA POP?\n"
# 129 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "POKéMON love it!\p"
# 130 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "Just ¥300 a bottle!\n"
# 131 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "Buy some!$"
# 132 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 133 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_Text_HereYouGo:
# 134 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "Here you go!$"
# 135 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 136 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_Text_NotEnoughMoney:
# 137 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "You don't have the money.$"
# 138 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 139 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_Text_ThatsTooBad:
# 140 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "No?\n"
# 141 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "That's too bad.$"
# 142 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 143 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_Text_DwayneIntro:
# 144 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "If you're looking for a battle in the\n"
# 145 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "SEASHORE HOUSE, you'll find no\l"
# 146 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "hotter TRAINER than me, matey!$"
# 147 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 148 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_Text_DwayneDefeated:
# 149 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "That was a hot battle!\n"
# 150 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "I can accept that loss, matey!$"
# 151 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 152 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_Text_DwaynePostBattle:
# 153 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "Whenever I'm in SLATEPORT, I enjoy\n"
# 154 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "hot battles and ice-cold SODA POP!$"
# 155 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 156 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_Text_JohannaIntro:
# 157 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "Boring battles aren't worth the effort.\p"
# 158 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "Fiery hot battles are what toughen up\n"
# 159 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "TRAINERS and POKéMON!$"
# 160 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 161 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_Text_JohannaDefeated:
# 162 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "That's hot!$"
# 163 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 164 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_Text_JohannaPostBattle:
# 165 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "Whew, I'm all thirsty.\n"
# 166 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "Maybe I'll have a SODA POP.$"
# 167 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 168 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_Text_SimonIntro:
# 169 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "I'm going to show you how great\n"
# 170 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "my POKéMON are, but don't cry!$"
# 171 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 172 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_Text_SimonDefeated:
# 173 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "…I lost, but I won't cry…$"
# 174 "data/maps/Route109_SeashoreHouse/scripts.pory"

# 175 "data/maps/Route109_SeashoreHouse/scripts.pory"
Route109_SeashoreHouse_Text_SimonPostBattle:
# 176 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "If one of my POKéMON knew the move\n"
# 177 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "for carrying me across water on its\l"
# 178 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "back, I could get rid of this inner tube.$"

Route109_SeashoreHouse_EventScript_Johanna::
# 183 "data/maps/Route109_SeashoreHouse/scripts.pory"
	trainerbattle_single TRAINER_JOHANNA, Route109_SeashoreHouse_Text_JohannaIntro, Route109_SeashoreHouse_Text_JohannaDefeated, Route109_SeashoreHouse_EventScript_JohannaReward
# 184 "data/maps/Route109_SeashoreHouse/scripts.pory"
	msgbox Route109_SeashoreHouse_Text_JohannaPostBattle, MSGBOX_AUTOCLOSE
	end


Route109_SeashoreHouse_EventScript_JohannaReward::
# 189 "data/maps/Route109_SeashoreHouse/scripts.pory"
	msgbox Route109_SeashoreHouse_EventScript_JohannaReward_Text_0
# 190 "data/maps/Route109_SeashoreHouse/scripts.pory"
	msgbox Route109_SeashoreHouse_EventScript_JohannaReward_Text_1
# 191 "data/maps/Route109_SeashoreHouse/scripts.pory"
	giveItem ITEM_TM_LUCKY_CHANT, 6
# 192 "data/maps/Route109_SeashoreHouse/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Route109_SeashoreHouse_EventScript_JohannaReward_2
Route109_SeashoreHouse_EventScript_JohannaReward_1:
# 195 "data/maps/Route109_SeashoreHouse/scripts.pory"
	goto Route109_SeashoreHouse_EventScript_CheckTrainersCompletion
	return

Route109_SeashoreHouse_EventScript_JohannaReward_2:
# 193 "data/maps/Route109_SeashoreHouse/scripts.pory"
	msgbox Route109_SeashoreHouse_EventScript_JohannaReward_Text_2
	goto Route109_SeashoreHouse_EventScript_JohannaReward_1


Route109_SeashoreHouse_EventScript_JohannaReward_Text_0:
# 189 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "I lost, but Lucky Chant always\n"
	.string "reassures me!$"

Route109_SeashoreHouse_EventScript_JohannaReward_Text_1:
# 190 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "Here, you should try it out too.$"

Route109_SeashoreHouse_EventScript_JohannaReward_Text_2:
# 193 "data/maps/Route109_SeashoreHouse/scripts.pory"
	.string "There's no room in your BAG or your PC\n"
	.string "for the LUCKY CHANT TMs.$"
