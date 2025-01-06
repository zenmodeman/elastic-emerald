# 1 "data/maps/RustboroCity_Gym/scripts.pory"

# 2 "data/maps/RustboroCity_Gym/scripts.pory"

# 3 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_MapScripts::
# 4 "data/maps/RustboroCity_Gym/scripts.pory"
	.byte 0
# 5 "data/maps/RustboroCity_Gym/scripts.pory"

# 6 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_EventScript_Roxanne_Old::
# 7 "data/maps/RustboroCity_Gym/scripts.pory"
	trainerbattle_single TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxanneIntro, RustboroCity_Gym_Text_RoxanneDefeat, RustboroCity_Gym_EventScript_RoxanneDefeated, NO_MUSIC
# 8 "data/maps/RustboroCity_Gym/scripts.pory"
	specialvar VAR_RESULT, ShouldTryRematchBattle
# 9 "data/maps/RustboroCity_Gym/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, RustboroCity_Gym_EventScript_RoxanneRematch
# 10 "data/maps/RustboroCity_Gym/scripts.pory"
	goto_if_unset FLAG_RECEIVED_TM_ROCK_TOMB, RustboroCity_Gym_EventScript_GiveRockTomb
# 11 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RustboroCity_Gym_Text_RoxannePostBattle, MSGBOX_DEFAULT
# 12 "data/maps/RustboroCity_Gym/scripts.pory"
	release
# 13 "data/maps/RustboroCity_Gym/scripts.pory"
	end
# 14 "data/maps/RustboroCity_Gym/scripts.pory"

# 15 "data/maps/RustboroCity_Gym/scripts.pory"

# 16 "data/maps/RustboroCity_Gym/scripts.pory"
RestrictItemClause::
# 17 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox ExplainItemClause, MSGBOX_DEFAULT
# 18 "data/maps/RustboroCity_Gym/scripts.pory"
	release
# 19 "data/maps/RustboroCity_Gym/scripts.pory"
	end
# 20 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_EventScript_RoxanneDefeated::
# 21 "data/maps/RustboroCity_Gym/scripts.pory"
	message RustboroCity_Gym_Text_ReceivedStoneBadge
# 22 "data/maps/RustboroCity_Gym/scripts.pory"
	waitmessage
# 23 "data/maps/RustboroCity_Gym/scripts.pory"
	call Common_EventScript_PlayGymBadgeFanfare
# 24 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RustboroCity_Gym_Text_StoneBadgeInfoTakeThis, MSGBOX_DEFAULT
# 25 "data/maps/RustboroCity_Gym/scripts.pory"
	setflag FLAG_DEFEATED_RUSTBORO_GYM
# 26 "data/maps/RustboroCity_Gym/scripts.pory"
	setflag FLAG_BADGE01_GET
# 27 "data/maps/RustboroCity_Gym/scripts.pory"
	setvar VAR_RUSTBORO_CITY_STATE, 1
# 28 "data/maps/RustboroCity_Gym/scripts.pory"
	addvar VAR_PETALBURG_GYM_STATE, 1
# 29 "data/maps/RustboroCity_Gym/scripts.pory"
	setvar VAR_0x8008, 1
# 30 "data/maps/RustboroCity_Gym/scripts.pory"
	call Common_EventScript_SetGymTrainers
# 31 "data/maps/RustboroCity_Gym/scripts.pory"
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
# 32 "data/maps/RustboroCity_Gym/scripts.pory"
	goto RustboroCity_Gym_EventScript_GiveRockTomb
# 33 "data/maps/RustboroCity_Gym/scripts.pory"
	end
# 34 "data/maps/RustboroCity_Gym/scripts.pory"

# 35 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_EventScript_GiveRockTomb_Old::
# 36 "data/maps/RustboroCity_Gym/scripts.pory"
	giveitem ITEM_TM_ROCK_TOMB
# 37 "data/maps/RustboroCity_Gym/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 38 "data/maps/RustboroCity_Gym/scripts.pory"
	setflag FLAG_RECEIVED_TM_ROCK_TOMB
# 39 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RustboroCity_Gym_Text_ExplainRockTomb, MSGBOX_DEFAULT
# 40 "data/maps/RustboroCity_Gym/scripts.pory"
	release
# 41 "data/maps/RustboroCity_Gym/scripts.pory"
	end
# 42 "data/maps/RustboroCity_Gym/scripts.pory"

# 43 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_EventScript_RoxanneRematch::
# 44 "data/maps/RustboroCity_Gym/scripts.pory"
	trainerbattle_rematch_double TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxannePreRematch, RustboroCity_Gym_Text_RoxanneRematchDefeat, RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons
# 45 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RustboroCity_Gym_Text_RoxannePostRematch, MSGBOX_AUTOCLOSE
# 46 "data/maps/RustboroCity_Gym/scripts.pory"
	end
# 47 "data/maps/RustboroCity_Gym/scripts.pory"

# 48 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_EventScript_Josh::
# 49 "data/maps/RustboroCity_Gym/scripts.pory"
	trainerbattle_single TRAINER_JOSH, RustboroCity_Gym_Text_JoshIntro, RustboroCity_Gym_Text_JoshDefeat
# 50 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RustboroCity_Gym_Text_JoshPostBattle, MSGBOX_AUTOCLOSE
# 51 "data/maps/RustboroCity_Gym/scripts.pory"
	end
# 52 "data/maps/RustboroCity_Gym/scripts.pory"

# 53 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_EventScript_Tommy::
# 54 "data/maps/RustboroCity_Gym/scripts.pory"
	trainerbattle_single TRAINER_TOMMY, RustboroCity_Gym_Text_TommyIntro, RustboroCity_Gym_Text_TommyDefeat
# 55 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RustboroCity_Gym_Text_TommyPostBattle, MSGBOX_AUTOCLOSE
# 56 "data/maps/RustboroCity_Gym/scripts.pory"
	end
# 57 "data/maps/RustboroCity_Gym/scripts.pory"

# 58 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_EventScript_Marc::
# 59 "data/maps/RustboroCity_Gym/scripts.pory"
	trainerbattle_single TRAINER_MARC, RustboroCity_Gym_Text_MarcIntro, RustboroCity_Gym_Text_MarcDefeat
# 60 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RustboroCity_Gym_Text_MarcPostBattle, MSGBOX_AUTOCLOSE
# 61 "data/maps/RustboroCity_Gym/scripts.pory"
	end
# 62 "data/maps/RustboroCity_Gym/scripts.pory"

# 63 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_EventScript_GymGuide::
# 64 "data/maps/RustboroCity_Gym/scripts.pory"
	lock
# 65 "data/maps/RustboroCity_Gym/scripts.pory"
	faceplayer
# 66 "data/maps/RustboroCity_Gym/scripts.pory"
	goto_if_set FLAG_DEFEATED_RUSTBORO_GYM, RustboroCity_Gym_EventScript_GymGuidePostVictory
# 67 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RustboroCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
# 68 "data/maps/RustboroCity_Gym/scripts.pory"
	release
# 69 "data/maps/RustboroCity_Gym/scripts.pory"
	end
# 70 "data/maps/RustboroCity_Gym/scripts.pory"

# 71 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_EventScript_GymGuidePostVictory::
# 72 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RustboroCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
# 73 "data/maps/RustboroCity_Gym/scripts.pory"
	release
# 74 "data/maps/RustboroCity_Gym/scripts.pory"
	end
# 75 "data/maps/RustboroCity_Gym/scripts.pory"

# 76 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_EventScript_LeftGymStatue::
# 77 "data/maps/RustboroCity_Gym/scripts.pory"
	lockall
# 78 "data/maps/RustboroCity_Gym/scripts.pory"
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
# 79 "data/maps/RustboroCity_Gym/scripts.pory"
	goto RustboroCity_Gym_EventScript_GymStatue
# 80 "data/maps/RustboroCity_Gym/scripts.pory"
	end
# 81 "data/maps/RustboroCity_Gym/scripts.pory"

# 82 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_EventScript_RightGymStatue::
# 83 "data/maps/RustboroCity_Gym/scripts.pory"
	lockall
# 84 "data/maps/RustboroCity_Gym/scripts.pory"
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
# 85 "data/maps/RustboroCity_Gym/scripts.pory"
	goto RustboroCity_Gym_EventScript_GymStatue
# 86 "data/maps/RustboroCity_Gym/scripts.pory"
	end
# 87 "data/maps/RustboroCity_Gym/scripts.pory"

# 88 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_EventScript_GymStatueCertified::
# 89 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RustboroCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
# 90 "data/maps/RustboroCity_Gym/scripts.pory"
	releaseall
# 91 "data/maps/RustboroCity_Gym/scripts.pory"
	end
# 92 "data/maps/RustboroCity_Gym/scripts.pory"

# 93 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_EventScript_GymStatue::
# 94 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RustboroCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
# 95 "data/maps/RustboroCity_Gym/scripts.pory"
	releaseall
# 96 "data/maps/RustboroCity_Gym/scripts.pory"
	end
# 97 "data/maps/RustboroCity_Gym/scripts.pory"

# 98 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_EventScript_RegisterRoxanne::
# 99 "data/maps/RustboroCity_Gym/scripts.pory"
	lockall
# 100 "data/maps/RustboroCity_Gym/scripts.pory"
	pokenavcall RustboroCity_Gym_Text_RoxanneRegisterCall
# 101 "data/maps/RustboroCity_Gym/scripts.pory"
	waitmessage
# 102 "data/maps/RustboroCity_Gym/scripts.pory"
	delay 30
# 103 "data/maps/RustboroCity_Gym/scripts.pory"
	playfanfare MUS_REGISTER_MATCH_CALL
# 104 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RustboroCity_Gym_Text_RegisteredRoxanne, MSGBOX_DEFAULT
# 105 "data/maps/RustboroCity_Gym/scripts.pory"
	waitfanfare
# 106 "data/maps/RustboroCity_Gym/scripts.pory"
	closemessage
# 107 "data/maps/RustboroCity_Gym/scripts.pory"
	delay 30
# 108 "data/maps/RustboroCity_Gym/scripts.pory"
	setflag FLAG_ENABLE_ROXANNE_MATCH_CALL
# 109 "data/maps/RustboroCity_Gym/scripts.pory"
	clearflag FLAG_ENABLE_ROXANNE_FIRST_CALL
# 110 "data/maps/RustboroCity_Gym/scripts.pory"
	releaseall
# 111 "data/maps/RustboroCity_Gym/scripts.pory"
	end
# 112 "data/maps/RustboroCity_Gym/scripts.pory"

# 113 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_GymGuideAdvice:
# 114 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Yo, how's it going?\p"
# 115 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Listen, my friend!\n"
# 116 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Would you like to become the CHAMPION?\p"
# 117 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "I'm no TRAINER, not me, but I can\n"
# 118 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "sure give you winning advice.\p"
# 119 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "That's settled, then! We'll aim for the\n"
# 120 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "POKéMON CHAMPIONSHIP together!\p"
# 121 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "It's your job as a TRAINER to collect\n"
# 122 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "GYM BADGES, am I right?\p"
# 123 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "But GYM LEADERS aren't pushovers!\p"
# 124 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "And that's where I come in!\n"
# 125 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "I'm here to provide expert advice!\p"
# 126 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "ROXANNE, the GYM LEADER, is a user\n"
# 127 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "of ROCK-type POKéMON.\p"
# 128 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "The ROCK type is very durable, but\n"
# 129 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "it can't stand WATER-type and\l"
# 130 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "GRASS-type moves.\p"
# 131 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Come see me afterwards, if you beat\n"
# 132 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "the GYM LEADER.\p"
# 133 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Well, go for it!$"
# 134 "data/maps/RustboroCity_Gym/scripts.pory"

# 135 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_GymGuidePostVictory:
# 136 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Whoa! What a breathtaking victory!\n"
# 137 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "My cheering must've worked!\p"
# 138 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Great!\n"
# 139 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Check your TRAINER CARD.\p"
# 140 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "The STONE BADGE you got should be\n"
# 141 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "properly recorded on it.\p"
# 142 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "In other words…\p"
# 143 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "You've climbed the first step on\n"
# 144 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "the stairs to the CHAMPIONSHIP!\p"
# 145 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "That's got to feel awesome!$"
# 146 "data/maps/RustboroCity_Gym/scripts.pory"

# 147 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_JoshIntro:
# 148 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Roxanne gave me her first Geodude!\n"
# 149 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "I'll show you what we can do!$"
# 150 "data/maps/RustboroCity_Gym/scripts.pory"

# 151 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_JoshDefeat:
# 152 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "You were too good for me…$"
# 153 "data/maps/RustboroCity_Gym/scripts.pory"

# 154 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_JoshPostBattle:
# 155 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "You haven't seen anything of the ROCK\n"
# 156 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "type's terrifying power!$"
# 157 "data/maps/RustboroCity_Gym/scripts.pory"

# 158 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_TommyIntro:
# 159 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "If you can't beat me, you won't stand\n"
# 160 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "a chance against ROXANNE!$"
# 161 "data/maps/RustboroCity_Gym/scripts.pory"

# 162 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_TommyDefeat:
# 163 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Wow! You've got some potential!$"
# 164 "data/maps/RustboroCity_Gym/scripts.pory"

# 165 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_TommyPostBattle:
# 166 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "ROXANNE is stronger than me by\n"
# 167 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "several times.\p"
# 168 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "You'd better be on your guard!$"
# 169 "data/maps/RustboroCity_Gym/scripts.pory"

# 170 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_MarcIntro:
# 171 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "We might be in the middle of town,\n"
# 172 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "but so what?\p"
# 173 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "My ROCK POKéMON need room to\n"
# 174 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "rampage!$"
# 175 "data/maps/RustboroCity_Gym/scripts.pory"

# 176 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_MarcDefeat:
# 177 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Oh, man oh man!\n"
# 178 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Our challenger is one feisty customer!$"
# 179 "data/maps/RustboroCity_Gym/scripts.pory"

# 180 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_MarcPostBattle:
# 181 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "I have to hand it to our LEADER.\p"
# 182 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "It took smarts and sense for her to\n"
# 183 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "pick the ROCK type at her young age.$"
# 184 "data/maps/RustboroCity_Gym/scripts.pory"

# 185 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_RoxanneIntro:
# 186 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Hello, I am ROXANNE, the RUSTBORO\n"
# 187 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "POKéMON GYM LEADER.\p"
# 188 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "I became a GYM LEADER so that I might\n"
# 189 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "apply what I learned at the POKéMON\l"
# 190 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "TRAINER'S SCHOOL in battle.\p"
# 191 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Would you kindly demonstrate how you\n"
# 192 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "battle, and with which POKéMON?$"
# 193 "data/maps/RustboroCity_Gym/scripts.pory"

# 194 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_RoxanneDefeat:
# 195 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "So…\n"
# 196 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "I lost…\p"
# 197 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "It seems that I still have much more\n"
# 198 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "to learn…\p"
# 199 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "I understand.\p"
# 200 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "The POKéMON LEAGUE's rules state\n"
# 201 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "that TRAINERS are to be given this\l"
# 202 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "if they defeat a GYM LEADER.\p"
# 203 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Please accept the official POKéMON\n"
# 204 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "LEAGUE STONE BADGE.$"
# 205 "data/maps/RustboroCity_Gym/scripts.pory"

# 206 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_ReceivedStoneBadge:
# 207 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "{PLAYER} received the STONE BADGE\n"
# 208 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "from ROXANNE.$"
# 209 "data/maps/RustboroCity_Gym/scripts.pory"

# 210 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_StoneBadgeInfoTakeThis:
# 211 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "The STONE BADGE heightens the ATTACK\n"
# 212 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "power of your POKéMON.\p"
# 213 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "It also enables them to use the HM move\n"
# 214 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "CUT outside of battle.\p"
# 215 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Please take this with you, too.$"
# 216 "data/maps/RustboroCity_Gym/scripts.pory"

# 217 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_ExplainRockTomb:
# 218 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "That TECHNICAL MACHINE, TM39,\n"
# 219 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "contains ROCK TOMB.\p"
# 220 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "It not only inflicts damage by dropping\n"
# 221 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "rocks, it also lowers SPEED.\p"
# 222 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "If you use a TM, it instantly teaches\n"
# 223 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "the move to a POKéMON.$"
# 224 "data/maps/RustboroCity_Gym/scripts.pory"

# 225 "data/maps/RustboroCity_Gym/scripts.pory"

# 226 "data/maps/RustboroCity_Gym/scripts.pory"
ExplainItemClause:
# 227 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "You have Duplicate Held Items. \p"
# 228 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "League sanctioned matches, \n"
# 229 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Must have item diversity. \p"
# 230 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Please return without duplicates.$" 
# 231 "data/maps/RustboroCity_Gym/scripts.pory"

# 232 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_RoxannePostBattle:
# 233 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Since you are so strong, you should\n"
# 234 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "challenge other GYM LEADERS.\p"
# 235 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "By battling many TRAINERS, you should\n"
# 236 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "learn many things.$"
# 237 "data/maps/RustboroCity_Gym/scripts.pory"

# 238 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_GymStatue:
# 239 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "RUSTBORO CITY POKéMON GYM$"
# 240 "data/maps/RustboroCity_Gym/scripts.pory"

# 241 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_GymStatueCertified:
# 242 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "RUSTBORO CITY POKéMON GYM\p"
# 243 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "ROXANNE'S CERTIFIED TRAINERS:\n"
# 244 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "{PLAYER}$"
# 245 "data/maps/RustboroCity_Gym/scripts.pory"

# 246 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_RoxanneRegisterCall:
# 247 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "… … … … … …\n"
# 248 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "… … … … … Beep!\p"
# 249 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "ROXANNE: Oh, hello, {PLAYER}?\n"
# 250 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "This is ROXANNE of RUSTBORO CITY.\p"
# 251 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "I heard from BRAWLY that you're\n"
# 252 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "moving up through the ranks of\l"
# 253 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "TRAINERS at an incredible clip.\p"
# 254 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Well, I'd rather not think that\n"
# 255 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "I can't beat you.\p"
# 256 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "I promise, I will shape up my GYM\n"
# 257 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "so that you may challenge us again.\p"
# 258 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "I hope you'll be looking forward to\n"
# 259 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "that occasion as much as me!\p"
# 260 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "… … … … … …\n"
# 261 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "… … … … … Click!$"
# 262 "data/maps/RustboroCity_Gym/scripts.pory"

# 263 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_RegisteredRoxanne:
# 264 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Registered GYM LEADER ROXANNE\n"
# 265 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "in the POKéNAV.$"
# 266 "data/maps/RustboroCity_Gym/scripts.pory"

# 267 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_RoxannePreRematch:
# 268 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "ROXANNE: I'm so glad to see you again.\n"
# 269 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "I'm ROXANNE, the GYM LEADER here.\p"
# 270 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "I'm sure we've both experienced many\n"
# 271 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "battles since we last met.\p"
# 272 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "I would like to see how much better\n"
# 273 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "we've become. Let us battle!$"
# 274 "data/maps/RustboroCity_Gym/scripts.pory"

# 275 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_RoxanneRematchDefeat:
# 276 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Grr…\n"
# 277 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Again, I have lost…$"
# 278 "data/maps/RustboroCity_Gym/scripts.pory"

# 279 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_RoxannePostRematch:
# 280 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "ROXANNE: I still have much to learn\n"
# 281 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "when it comes to battling POKéMON.\p"
# 282 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "That awareness makes me love battling\n"
# 283 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "all that much more!$"
# 284 "data/maps/RustboroCity_Gym/scripts.pory"

# 285 "data/maps/RustboroCity_Gym/scripts.pory"
RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons:
# 286 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "ROXANNE: I'm so glad to see you again.\n"
# 287 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "I'm ROXANNE, the GYM LEADER here.\p"
# 288 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "I'm sure we've both experienced many\n"
# 289 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "battles since we last met.\p"
# 290 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "I would like to see how much better\n"
# 291 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "we've become…\p"
# 292 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Oh, no…\n"
# 293 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "You only have one POKéMON with you?\p"
# 294 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Please return with at least one more\n"
# 295 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "POKéMON.$"

RustboroCity_Gym_EventScript_Roxanne::
# 299 "data/maps/RustboroCity_Gym/scripts.pory"
	lock
# 300 "data/maps/RustboroCity_Gym/scripts.pory"
	goto_if_unset FLAG_RECEIVED_TM_ROCK_TOMB, RustboroCity_Gym_EventScript_Roxanne_2
RustboroCity_Gym_EventScript_Roxanne_1:
# 309 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RustboroCity_Gym_Text_RoxannePostBattle
# 310 "data/maps/RustboroCity_Gym/scripts.pory"
	release
	end

RustboroCity_Gym_EventScript_Roxanne_2:
# 301 "data/maps/RustboroCity_Gym/scripts.pory"
	goto_if_set FLAG_RESTRICTED_MODE, RustboroCity_Gym_EventScript_Roxanne_5
RustboroCity_Gym_EventScript_Roxanne_4:
# 307 "data/maps/RustboroCity_Gym/scripts.pory"
	goto RoxanneFirstGymBattleScript
	goto RustboroCity_Gym_EventScript_Roxanne_1

RustboroCity_Gym_EventScript_Roxanne_5:
# 302 "data/maps/RustboroCity_Gym/scripts.pory"
	specialvar VAR_RESULT, DoesPlayerFollowItemClause
# 303 "data/maps/RustboroCity_Gym/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq RustboroCity_Gym_EventScript_Roxanne_7
	goto RustboroCity_Gym_EventScript_Roxanne_4

RustboroCity_Gym_EventScript_Roxanne_7:
# 304 "data/maps/RustboroCity_Gym/scripts.pory"
	goto Roxanne_Restrict_Item_Clause
	goto RustboroCity_Gym_EventScript_Roxanne_4


RoxanneFirstGymBattleScript::
# 315 "data/maps/RustboroCity_Gym/scripts.pory"
	faceplayer
# 316 "data/maps/RustboroCity_Gym/scripts.pory"
	goto_if_set FLAG_RESTRICTED_MODE, RoxanneFirstGymBattleScript_2
RoxanneFirstGymBattleScript_1:
# 322 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RoxanneFirstGymBattleScript_Text_0
# 323 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RoxanneFirstGymBattleScript_Text_1
# 324 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RoxanneFirstGymBattleScript_Text_2
# 325 "data/maps/RustboroCity_Gym/scripts.pory"
	playse SE_USE_ITEM
# 326 "data/maps/RustboroCity_Gym/scripts.pory"
	special HealPlayerParty
# 327 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RoxanneFirstGymBattleScript_Text_3
# 328 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RoxanneFirstGymBattleScript_Text_4
# 329 "data/maps/RustboroCity_Gym/scripts.pory"
	dynmultichoice 0, 100, TRUE, 2, 0, DYN_MULTICHOICE_CB_NONE, RoxanneFirstGymBattleScript_Text_5, RoxanneFirstGymBattleScript_Text_6
# 330 "data/maps/RustboroCity_Gym/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq RoxanneFirstGymBattleScript_5
# 341 "data/maps/RustboroCity_Gym/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq RoxanneFirstGymBattleScript_6
RoxanneFirstGymBattleScript_4:
# 352 "data/maps/RustboroCity_Gym/scripts.pory"
	release
	end

RoxanneFirstGymBattleScript_2:
# 317 "data/maps/RustboroCity_Gym/scripts.pory"
	specialvar VAR_RESULT, DoesPlayerFollowItemClause
# 318 "data/maps/RustboroCity_Gym/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq RoxanneFirstGymBattleScript_9
	goto RoxanneFirstGymBattleScript_1

RoxanneFirstGymBattleScript_5:
# 331 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RoxanneFirstGymBattleScript_Text_7
# 332 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RoxanneFirstGymBattleScript_Text_8
# 333 "data/maps/RustboroCity_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_NONE
	goto_if_eq RoxanneFirstGymBattleScript_12
# 333 "data/maps/RustboroCity_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_GRASS - 1
	goto_if_eq RoxanneFirstGymBattleScript_12
# 333 "data/maps/RustboroCity_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_WATER - 1
	goto_if_eq RoxanneFirstGymBattleScript_12
# 333 "data/maps/RustboroCity_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_FIGHTING
	goto_if_eq RoxanneFirstGymBattleScript_12
# 334 "data/maps/RustboroCity_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_STEEL
	goto_if_eq RoxanneFirstGymBattleScript_12
# 334 "data/maps/RustboroCity_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_GROUND
	goto_if_eq RoxanneFirstGymBattleScript_12
# 337 "data/maps/RustboroCity_Gym/scripts.pory"
	trainerbattle_no_intro TRAINER_ROXANNE_1_3MON, RustboroCity_Gym_Text_RoxanneDefeat
RoxanneFirstGymBattleScript_11:
# 340 "data/maps/RustboroCity_Gym/scripts.pory"
	call RustboroCity_Gym_EventScript_RoxanneDefeated
	goto RoxanneFirstGymBattleScript_4

RoxanneFirstGymBattleScript_6:
# 342 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RoxanneFirstGymBattleScript_Text_9
# 343 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RoxanneFirstGymBattleScript_Text_8
# 344 "data/maps/RustboroCity_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_NONE
	goto_if_eq RoxanneFirstGymBattleScript_26
# 344 "data/maps/RustboroCity_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_GRASS - 1
	goto_if_eq RoxanneFirstGymBattleScript_26
# 344 "data/maps/RustboroCity_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_WATER - 1
	goto_if_eq RoxanneFirstGymBattleScript_26
# 344 "data/maps/RustboroCity_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_FIGHTING
	goto_if_eq RoxanneFirstGymBattleScript_26
# 345 "data/maps/RustboroCity_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_STEEL
	goto_if_eq RoxanneFirstGymBattleScript_26
# 345 "data/maps/RustboroCity_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_GROUND
	goto_if_eq RoxanneFirstGymBattleScript_26
# 348 "data/maps/RustboroCity_Gym/scripts.pory"
	trainerbattle_no_intro TRAINER_ROXANNE_1_3MON_DOUBLES, RustboroCity_Gym_Text_RoxanneDefeat
RoxanneFirstGymBattleScript_25:
# 350 "data/maps/RustboroCity_Gym/scripts.pory"
	call RustboroCity_Gym_EventScript_RoxanneDefeated
	goto RoxanneFirstGymBattleScript_4

RoxanneFirstGymBattleScript_9:
# 319 "data/maps/RustboroCity_Gym/scripts.pory"
	goto Roxanne_Restrict_Item_Clause
	goto RoxanneFirstGymBattleScript_1

RoxanneFirstGymBattleScript_12:
# 335 "data/maps/RustboroCity_Gym/scripts.pory"
	trainerbattle_no_intro TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxanneDefeat
	goto RoxanneFirstGymBattleScript_11

RoxanneFirstGymBattleScript_26:
# 346 "data/maps/RustboroCity_Gym/scripts.pory"
	trainerbattle_no_intro TRAINER_ROXANNE_1_DOUBLES, RustboroCity_Gym_Text_RoxanneDefeat
	goto RoxanneFirstGymBattleScript_25


Roxanne_Restrict_Item_Clause::
# 357 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox Roxanne_Restrict_Item_Clause_Text_0
# 358 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox Roxanne_Restrict_Item_Clause_Text_1
# 359 "data/maps/RustboroCity_Gym/scripts.pory"
	release
	end


RustboroCity_Gym_EventScript_GiveRockTomb::
# 364 "data/maps/RustboroCity_Gym/scripts.pory"
	goto_if_unset FLAG_RESOURCE_MODE, RustboroCity_Gym_EventScript_GiveRockTomb_2
# 369 "data/maps/RustboroCity_Gym/scripts.pory"
	giveitem ITEM_TM_ROCK_TOMB, 3
# 370 "data/maps/RustboroCity_Gym/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 371 "data/maps/RustboroCity_Gym/scripts.pory"
	setflag FLAG_RECEIVED_TM_ROCK_TOMB
RustboroCity_Gym_EventScript_GiveRockTomb_1:
# 373 "data/maps/RustboroCity_Gym/scripts.pory"
	msgbox RustboroCity_Gym_Text_ExplainRockTomb, MSGBOX_DEFAULT
# 374 "data/maps/RustboroCity_Gym/scripts.pory"
	release
	end

RustboroCity_Gym_EventScript_GiveRockTomb_2:
# 365 "data/maps/RustboroCity_Gym/scripts.pory"
	giveitem ITEM_TM_ROCK_TOMB
# 366 "data/maps/RustboroCity_Gym/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 367 "data/maps/RustboroCity_Gym/scripts.pory"
	setflag FLAG_RECEIVED_TM_ROCK_TOMB
	goto RustboroCity_Gym_EventScript_GiveRockTomb_1


RoxanneFirstGymBattleScript_Text_0:
# 322 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Hello, I am Roxanne, the Rustboro City\n"
	.string "POKéMON Gym Leader.$"

RoxanneFirstGymBattleScript_Text_1:
# 323 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "After battling with my Gym Trainers,\n"
	.string "your Pokémon must be exhausted.$"

RoxanneFirstGymBattleScript_Text_2:
# 324 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Here, let me heal them for you.$"

RoxanneFirstGymBattleScript_Text_3:
# 327 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "I became a GYM LEADER so that I might\n"
	.string "apply what I learned at the POKéMON\l"
	.string "TRAINER'S SCHOOL in battle.$"

RoxanneFirstGymBattleScript_Text_4:
# 328 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Would you like to have a Single or a\n"
	.string "Double Battle?$"

RoxanneFirstGymBattleScript_Text_5:
# 329 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Single Battle$"

RoxanneFirstGymBattleScript_Text_6:
# 329 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Double Battle$"

RoxanneFirstGymBattleScript_Text_7:
# 331 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Oh, you want a simple head-to-head.\n"
	.string "Fine by me.$"

RoxanneFirstGymBattleScript_Text_8:
# 332 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Would you kindly demonstrate how you\n"
	.string "battle, and with which POKéMON?$"

RoxanneFirstGymBattleScript_Text_9:
# 342 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Oh, you want a more complex battle. I'm\n"
	.string "down!$"

Roxanne_Restrict_Item_Clause_Text_0:
# 357 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "Hello, you wish to challenge me?$"

Roxanne_Restrict_Item_Clause_Text_1:
# 358 "data/maps/RustboroCity_Gym/scripts.pory"
	.string "As per League rules, please make sure\n"
	.string "your team does not carry duplicate\l"
	.string "items.$"
