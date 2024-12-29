# 1 "data/maps/Route104/scripts.pory"

# 2 "data/maps/Route104/scripts.pory"

# 3 "data/maps/Route104/scripts.pory"
@ NOTE: Route 104's sail to Dewford script references local IDs from Dewford's map.
# 4 "data/maps/Route104/scripts.pory"
@  These are labeled in DewfordTown/scripts.inc
# 5 "data/maps/Route104/scripts.pory"
.set LOCALID_RIVAL, 34
# 6 "data/maps/Route104/scripts.pory"

# 7 "data/maps/Route104/scripts.pory"
Route104_MapScripts::
# 8 "data/maps/Route104/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route104_OnFrame
# 9 "data/maps/Route104/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Route104_OnTransition
# 10 "data/maps/Route104/scripts.pory"
	.byte 0
# 11 "data/maps/Route104/scripts.pory"

# 12 "data/maps/Route104/scripts.pory"
Route104_OnFrame:
# 13 "data/maps/Route104/scripts.pory"
	map_script_2 VAR_BOARD_BRINEY_BOAT_STATE, 1, Route104_EventScript_StartSailToDewford
# 14 "data/maps/Route104/scripts.pory"
	.2byte 0
# 15 "data/maps/Route104/scripts.pory"

# 16 "data/maps/Route104/scripts.pory"
Route104_EventScript_StartSailToDewford::
# 17 "data/maps/Route104/scripts.pory"
	lockall
# 18 "data/maps/Route104/scripts.pory"
	goto Route104_EventScript_SailToDewford
# 19 "data/maps/Route104/scripts.pory"
	end
# 20 "data/maps/Route104/scripts.pory"

# 21 "data/maps/Route104/scripts.pory"
Route104_OnTransition:
# 22 "data/maps/Route104/scripts.pory"
	call Common_EventScript_SetupRivalGfxId
# 23 "data/maps/Route104/scripts.pory"
	call Route104_EventScript_TrySetRivalPos
# 24 "data/maps/Route104/scripts.pory"
	call Route104_EventScript_ShowOrHideWhiteHerbFlorist
# 25 "data/maps/Route104/scripts.pory"
	end
# 26 "data/maps/Route104/scripts.pory"

# 27 "data/maps/Route104/scripts.pory"
Route104_EventScript_ShowOrHideWhiteHerbFlorist::
# 28 "data/maps/Route104/scripts.pory"
	goto_if_unset FLAG_MET_PRETTY_PETAL_SHOP_OWNER, Route104_EventScript_HideWhiteHerbFlorist
# 29 "data/maps/Route104/scripts.pory"
	goto_if_unset FLAG_BADGE03_GET, Route104_EventScript_HideWhiteHerbFlorist
# 30 "data/maps/Route104/scripts.pory"
	clearflag FLAG_HIDE_ROUTE_104_WHITE_HERB_FLORIST
# 31 "data/maps/Route104/scripts.pory"
	return
# 32 "data/maps/Route104/scripts.pory"

# 33 "data/maps/Route104/scripts.pory"
Route104_EventScript_HideWhiteHerbFlorist::
# 34 "data/maps/Route104/scripts.pory"
	setflag FLAG_HIDE_ROUTE_104_WHITE_HERB_FLORIST
# 35 "data/maps/Route104/scripts.pory"
	return
# 36 "data/maps/Route104/scripts.pory"

# 37 "data/maps/Route104/scripts.pory"
Route104_EventScript_TrySetRivalPos::
# 38 "data/maps/Route104/scripts.pory"
	goto_if_ge VAR_BOARD_BRINEY_BOAT_STATE, 1, Route104_EventScript_DontSetRivalPos
# 39 "data/maps/Route104/scripts.pory"
	goto_if_set FLAG_MET_RIVAL_RUSTBORO, Route104_EventScript_DontSetRivalPos
# 40 "data/maps/Route104/scripts.pory"
	goto_if_unset FLAG_REGISTER_RIVAL_POKENAV, Route104_EventScript_DontSetRivalPos
# 41 "data/maps/Route104/scripts.pory"
	setobjectxyperm LOCALID_RIVAL, 17, 52
# 42 "data/maps/Route104/scripts.pory"
	return
# 43 "data/maps/Route104/scripts.pory"

# 44 "data/maps/Route104/scripts.pory"
Route104_EventScript_DontSetRivalPos::
# 45 "data/maps/Route104/scripts.pory"
	return
# 46 "data/maps/Route104/scripts.pory"

# 47 "data/maps/Route104/scripts.pory"
Route104_EventScript_Rival::
# 48 "data/maps/Route104/scripts.pory"
	lockall
# 49 "data/maps/Route104/scripts.pory"
	setvar VAR_0x8008, 1
# 50 "data/maps/Route104/scripts.pory"
	applymovement LOCALID_RIVAL, Common_Movement_FacePlayer
# 51 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 52 "data/maps/Route104/scripts.pory"
	goto Route104_EventScript_RivalEncounter
# 53 "data/maps/Route104/scripts.pory"

# 54 "data/maps/Route104/scripts.pory"
Route104_EventScript_RivalTrigger::
# 55 "data/maps/Route104/scripts.pory"
	lockall
# 56 "data/maps/Route104/scripts.pory"
	setflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
# 57 "data/maps/Route104/scripts.pory"
	setvar VAR_RUSTBORO_CITY_STATE, 8
# 58 "data/maps/Route104/scripts.pory"
	setvar VAR_ROUTE104_STATE, 2
# 59 "data/maps/Route104/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 60 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 61 "data/maps/Route104/scripts.pory"
	delay 10
# 62 "data/maps/Route104/scripts.pory"
	addobject LOCALID_RIVAL
# 63 "data/maps/Route104/scripts.pory"
	clearflag FLAG_HIDE_ROUTE_104_RIVAL
# 64 "data/maps/Route104/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_PlayerBackUp
# 65 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 66 "data/maps/Route104/scripts.pory"
	applymovement LOCALID_RIVAL, Route104_Movement_RivalExitBrineysCottage
# 67 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 68 "data/maps/Route104/scripts.pory"
	delay 20
# 69 "data/maps/Route104/scripts.pory"
	setvar VAR_0x8008, 0
# 70 "data/maps/Route104/scripts.pory"
	call RustboroCity_EventScript_PlayRivalMusic
# 71 "data/maps/Route104/scripts.pory"
	playse SE_PIN
# 72 "data/maps/Route104/scripts.pory"
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
# 73 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 74 "data/maps/Route104/scripts.pory"
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
# 75 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 76 "data/maps/Route104/scripts.pory"
	goto Route104_EventScript_RivalEncounter
# 77 "data/maps/Route104/scripts.pory"

# 78 "data/maps/Route104/scripts.pory"
@ Unused, shares script with Rustboro encounter instead
# 79 "data/maps/Route104/scripts.pory"
Route104_EventScript_PlayRivalMusic::
# 80 "data/maps/Route104/scripts.pory"
	checkplayergender
# 81 "data/maps/Route104/scripts.pory"
	goto_if_eq VAR_RESULT, MALE, Route104_EventScript_PlayMayMusic
# 82 "data/maps/Route104/scripts.pory"
	goto_if_eq VAR_RESULT, FEMALE, Route104_EventScript_PlayBrendanMusic
# 83 "data/maps/Route104/scripts.pory"
	return
# 84 "data/maps/Route104/scripts.pory"

# 85 "data/maps/Route104/scripts.pory"
Route104_EventScript_PlayMayMusic::
# 86 "data/maps/Route104/scripts.pory"
	playbgm MUS_ENCOUNTER_MAY, TRUE
# 87 "data/maps/Route104/scripts.pory"
	return
# 88 "data/maps/Route104/scripts.pory"

# 89 "data/maps/Route104/scripts.pory"
Route104_EventScript_PlayBrendanMusic::
# 90 "data/maps/Route104/scripts.pory"
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
# 91 "data/maps/Route104/scripts.pory"
	return
# 92 "data/maps/Route104/scripts.pory"

# 93 "data/maps/Route104/scripts.pory"
Route104_EventScript_RivalEncounter::
# 94 "data/maps/Route104/scripts.pory"
	checkplayergender
# 95 "data/maps/Route104/scripts.pory"
	goto_if_eq VAR_RESULT, MALE, Route104_EventScript_MayEncounter
# 96 "data/maps/Route104/scripts.pory"
	goto_if_eq VAR_RESULT, FEMALE, Route104_EventScript_BrendanEncounter
# 97 "data/maps/Route104/scripts.pory"
	end
# 98 "data/maps/Route104/scripts.pory"

# 99 "data/maps/Route104/scripts.pory"
Route104_EventScript_MayEncounter::
# 100 "data/maps/Route104/scripts.pory"
	goto_if_set FLAG_DEFEATED_RIVAL_ROUTE_104, Route104_EventScript_MayDefeated
# 101 "data/maps/Route104/scripts.pory"
	goto_if_set FLAG_REGISTER_RIVAL_POKENAV, Route104_EventScript_MayAskToBattle
# 102 "data/maps/Route104/scripts.pory"
	setflag FLAG_REGISTER_RIVAL_POKENAV
# 103 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_MayWeShouldRegister, MSGBOX_DEFAULT
# 104 "data/maps/Route104/scripts.pory"
	closemessage
# 105 "data/maps/Route104/scripts.pory"
	delay 30
# 106 "data/maps/Route104/scripts.pory"
	playfanfare MUS_REGISTER_MATCH_CALL
# 107 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_RegisteredMay, MSGBOX_DEFAULT
# 108 "data/maps/Route104/scripts.pory"
	waitfanfare
# 109 "data/maps/Route104/scripts.pory"
	closemessage
# 110 "data/maps/Route104/scripts.pory"
	delay 30
# 111 "data/maps/Route104/scripts.pory"
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
# 112 "data/maps/Route104/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_PlayerFaceRival
# 113 "data/maps/Route104/scripts.pory"
	applymovement LOCALID_RIVAL, Route104_Movement_RivalWalkSlowLeft
# 114 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_MayHowsYourPokedex, MSGBOX_DEFAULT
# 115 "data/maps/Route104/scripts.pory"
	closemessage
# 116 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 117 "data/maps/Route104/scripts.pory"
	applymovement LOCALID_RIVAL, Route104_Movement_RivalApproachPlayer
# 118 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 119 "data/maps/Route104/scripts.pory"
	copyobjectxytoperm LOCALID_RIVAL
# 120 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_MayMinesDecentLetsBattle, MSGBOX_YESNO
# 121 "data/maps/Route104/scripts.pory"
	goto_if_eq VAR_RESULT, YES, Route104_EventScript_BattleMay
# 122 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_MayHaventRaisedPokemon, MSGBOX_DEFAULT
# 123 "data/maps/Route104/scripts.pory"
	call Route104_EventScript_RestoreMusic
# 124 "data/maps/Route104/scripts.pory"
	releaseall
# 125 "data/maps/Route104/scripts.pory"
	end
# 126 "data/maps/Route104/scripts.pory"

# 127 "data/maps/Route104/scripts.pory"
Route104_Movement_RivalWalkSlowLeft:
# 128 "data/maps/Route104/scripts.pory"
	walk_slow_left
# 129 "data/maps/Route104/scripts.pory"
	step_end
# 130 "data/maps/Route104/scripts.pory"

# 131 "data/maps/Route104/scripts.pory"
Route104_Movement_RivalApproachPlayer:
# 132 "data/maps/Route104/scripts.pory"
	walk_down
# 133 "data/maps/Route104/scripts.pory"
	face_right
# 134 "data/maps/Route104/scripts.pory"
	step_end
# 135 "data/maps/Route104/scripts.pory"

# 136 "data/maps/Route104/scripts.pory"
Route104_Movement_PlayerFaceRival:
# 137 "data/maps/Route104/scripts.pory"
	delay_4
# 138 "data/maps/Route104/scripts.pory"
	walk_in_place_faster_left
# 139 "data/maps/Route104/scripts.pory"
	step_end
# 140 "data/maps/Route104/scripts.pory"

# 141 "data/maps/Route104/scripts.pory"
Route104_EventScript_MayAskToBattle::
# 142 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_MayLetsBattle, MSGBOX_YESNO
# 143 "data/maps/Route104/scripts.pory"
	goto_if_eq VAR_RESULT, YES, Route104_EventScript_BattleMay
# 144 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_MayHaventRaisedPokemon, MSGBOX_DEFAULT
# 145 "data/maps/Route104/scripts.pory"
	releaseall
# 146 "data/maps/Route104/scripts.pory"
	end
# 147 "data/maps/Route104/scripts.pory"

# 148 "data/maps/Route104/scripts.pory"
Route104_EventScript_BattleMay::
# 149 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_MayIntro, MSGBOX_DEFAULT
# 150 "data/maps/Route104/scripts.pory"
	switch VAR_STARTER_MON
# 151 "data/maps/Route104/scripts.pory"
	case 0, Route104_EventScript_BattleMayTreecko
# 152 "data/maps/Route104/scripts.pory"
	case 1, Route104_EventScript_BattleMayTorchic
# 153 "data/maps/Route104/scripts.pory"
	case 2, Route104_EventScript_BattleMayMudkip
# 154 "data/maps/Route104/scripts.pory"
	end
# 155 "data/maps/Route104/scripts.pory"

# 156 "data/maps/Route104/scripts.pory"
Route104_EventScript_MayDefeated::
# 157 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_MayPostBattle, MSGBOX_DEFAULT
# 158 "data/maps/Route104/scripts.pory"
	call_if_eq VAR_0x8008, 0, Route104_EventScript_RestoreMusic
# 159 "data/maps/Route104/scripts.pory"
	releaseall
# 160 "data/maps/Route104/scripts.pory"
	end
# 161 "data/maps/Route104/scripts.pory"

# 162 "data/maps/Route104/scripts.pory"
Route104_EventScript_RestoreMusic::
# 163 "data/maps/Route104/scripts.pory"
	savebgm MUS_DUMMY
# 164 "data/maps/Route104/scripts.pory"
	fadedefaultbgm
# 165 "data/maps/Route104/scripts.pory"
	return
# 166 "data/maps/Route104/scripts.pory"

# 167 "data/maps/Route104/scripts.pory"
Route104_EventScript_BattleMayTreecko::
# 168 "data/maps/Route104/scripts.pory"
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_TREECKO, Route104_Text_MayDefeat
# 169 "data/maps/Route104/scripts.pory"
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
# 170 "data/maps/Route104/scripts.pory"
	goto Route104_EventScript_MayDefeated
# 171 "data/maps/Route104/scripts.pory"
	end
# 172 "data/maps/Route104/scripts.pory"

# 173 "data/maps/Route104/scripts.pory"
Route104_EventScript_BattleMayTorchic::
# 174 "data/maps/Route104/scripts.pory"
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_TORCHIC, Route104_Text_MayDefeat
# 175 "data/maps/Route104/scripts.pory"
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
# 176 "data/maps/Route104/scripts.pory"
	goto Route104_EventScript_MayDefeated
# 177 "data/maps/Route104/scripts.pory"
	end
# 178 "data/maps/Route104/scripts.pory"

# 179 "data/maps/Route104/scripts.pory"
Route104_EventScript_BattleMayMudkip::
# 180 "data/maps/Route104/scripts.pory"
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_MUDKIP, Route104_Text_MayDefeat
# 181 "data/maps/Route104/scripts.pory"
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
# 182 "data/maps/Route104/scripts.pory"
	goto Route104_EventScript_MayDefeated
# 183 "data/maps/Route104/scripts.pory"
	end
# 184 "data/maps/Route104/scripts.pory"

# 185 "data/maps/Route104/scripts.pory"
Route104_EventScript_BrendanEncounter::
# 186 "data/maps/Route104/scripts.pory"
	goto_if_set FLAG_DEFEATED_RIVAL_ROUTE_104, Route104_EventScript_BrendanDefeated
# 187 "data/maps/Route104/scripts.pory"
	goto_if_set FLAG_REGISTER_RIVAL_POKENAV, Route104_EventScript_BrendanAskToBattle
# 188 "data/maps/Route104/scripts.pory"
	setflag FLAG_REGISTER_RIVAL_POKENAV
# 189 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_BrendanWeShouldRegister, MSGBOX_DEFAULT
# 190 "data/maps/Route104/scripts.pory"
	closemessage
# 191 "data/maps/Route104/scripts.pory"
	delay 30
# 192 "data/maps/Route104/scripts.pory"
	playfanfare MUS_REGISTER_MATCH_CALL
# 193 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_RegisteredBrendan, MSGBOX_DEFAULT
# 194 "data/maps/Route104/scripts.pory"
	waitfanfare
# 195 "data/maps/Route104/scripts.pory"
	closemessage
# 196 "data/maps/Route104/scripts.pory"
	delay 30
# 197 "data/maps/Route104/scripts.pory"
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
# 198 "data/maps/Route104/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_PlayerFaceRival
# 199 "data/maps/Route104/scripts.pory"
	applymovement LOCALID_RIVAL, Route104_Movement_RivalWalkSlowLeft
# 200 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_BrendanHowsYourPokedex, MSGBOX_DEFAULT
# 201 "data/maps/Route104/scripts.pory"
	closemessage
# 202 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 203 "data/maps/Route104/scripts.pory"
	applymovement LOCALID_RIVAL, Route104_Movement_RivalApproachPlayer
# 204 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 205 "data/maps/Route104/scripts.pory"
	copyobjectxytoperm LOCALID_RIVAL
# 206 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_BrendanDoingGreatLetsBattle, MSGBOX_YESNO
# 207 "data/maps/Route104/scripts.pory"
	goto_if_eq VAR_RESULT, YES, Route104_EventScript_BattleBrendan
# 208 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_BrendanNoConfidence, MSGBOX_DEFAULT
# 209 "data/maps/Route104/scripts.pory"
	call Route104_EventScript_RestoreMusic
# 210 "data/maps/Route104/scripts.pory"
	releaseall
# 211 "data/maps/Route104/scripts.pory"
	end
# 212 "data/maps/Route104/scripts.pory"

# 213 "data/maps/Route104/scripts.pory"
Route104_EventScript_BrendanAskToBattle::
# 214 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_BrendanLetsBattle, MSGBOX_YESNO
# 215 "data/maps/Route104/scripts.pory"
	goto_if_eq VAR_RESULT, YES, Route104_EventScript_BattleBrendan
# 216 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_BrendanNoConfidence, MSGBOX_DEFAULT
# 217 "data/maps/Route104/scripts.pory"
	releaseall
# 218 "data/maps/Route104/scripts.pory"
	end
# 219 "data/maps/Route104/scripts.pory"

# 220 "data/maps/Route104/scripts.pory"
Route104_EventScript_BattleBrendan::
# 221 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_BrendanIntro, MSGBOX_DEFAULT
# 222 "data/maps/Route104/scripts.pory"
	switch VAR_STARTER_MON
# 223 "data/maps/Route104/scripts.pory"
	case 0, Route104_EventScript_BattleBrendanTreecko
# 224 "data/maps/Route104/scripts.pory"
	case 1, Route104_EventScript_BattleBrendanTorchic
# 225 "data/maps/Route104/scripts.pory"
	case 2, Route104_EventScript_BattleBrendanMudkip
# 226 "data/maps/Route104/scripts.pory"
	end
# 227 "data/maps/Route104/scripts.pory"

# 228 "data/maps/Route104/scripts.pory"
Route104_EventScript_BrendanDefeated::
# 229 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_BrendanPostBattle, MSGBOX_DEFAULT
# 230 "data/maps/Route104/scripts.pory"
	call_if_eq VAR_0x8008, 0, Route104_EventScript_RestoreMusic
# 231 "data/maps/Route104/scripts.pory"
	releaseall
# 232 "data/maps/Route104/scripts.pory"
	end
# 233 "data/maps/Route104/scripts.pory"

# 234 "data/maps/Route104/scripts.pory"
Route104_EventScript_BattleBrendanTreecko::
# 235 "data/maps/Route104/scripts.pory"
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_TREECKO, Route104_Text_BrendanDefeat
# 236 "data/maps/Route104/scripts.pory"
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
# 237 "data/maps/Route104/scripts.pory"
	goto Route104_EventScript_BrendanDefeated
# 238 "data/maps/Route104/scripts.pory"
	end
# 239 "data/maps/Route104/scripts.pory"

# 240 "data/maps/Route104/scripts.pory"
Route104_EventScript_BattleBrendanTorchic::
# 241 "data/maps/Route104/scripts.pory"
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_TORCHIC, Route104_Text_BrendanDefeat
# 242 "data/maps/Route104/scripts.pory"
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
# 243 "data/maps/Route104/scripts.pory"
	goto Route104_EventScript_BrendanDefeated
# 244 "data/maps/Route104/scripts.pory"
	end
# 245 "data/maps/Route104/scripts.pory"

# 246 "data/maps/Route104/scripts.pory"
Route104_EventScript_BattleBrendanMudkip::
# 247 "data/maps/Route104/scripts.pory"
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_MUDKIP, Route104_Text_BrendanDefeat
# 248 "data/maps/Route104/scripts.pory"
	setflag FLAG_DEFEATED_RIVAL_ROUTE_104
# 249 "data/maps/Route104/scripts.pory"
	goto Route104_EventScript_BrendanDefeated
# 250 "data/maps/Route104/scripts.pory"
	end
# 251 "data/maps/Route104/scripts.pory"

# 252 "data/maps/Route104/scripts.pory"
Route104_Movement_PlayerBackUp:
# 253 "data/maps/Route104/scripts.pory"
	lock_facing_direction
# 254 "data/maps/Route104/scripts.pory"
	walk_down
# 255 "data/maps/Route104/scripts.pory"
	unlock_facing_direction
# 256 "data/maps/Route104/scripts.pory"
	step_end
# 257 "data/maps/Route104/scripts.pory"

# 258 "data/maps/Route104/scripts.pory"
Route104_Movement_RivalExitBrineysCottage:
# 259 "data/maps/Route104/scripts.pory"
	walk_down
# 260 "data/maps/Route104/scripts.pory"
	step_end
# 261 "data/maps/Route104/scripts.pory"

# 262 "data/maps/Route104/scripts.pory"
Route104_EventScript_ExpertF::
# 263 "data/maps/Route104/scripts.pory"
	lock
# 264 "data/maps/Route104/scripts.pory"
	faceplayer
# 265 "data/maps/Route104/scripts.pory"
	goto_if_set FLAG_RECEIVED_CHESTO_BERRY_ROUTE_104, Route104_EventScript_ReceivedBerry
# 266 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_PlantBerriesInSoilTakeThis, MSGBOX_DEFAULT
# 267 "data/maps/Route104/scripts.pory"
	giveitem ITEM_CHESTO_BERRY
# 268 "data/maps/Route104/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 269 "data/maps/Route104/scripts.pory"
	setflag FLAG_RECEIVED_CHESTO_BERRY_ROUTE_104
# 270 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_TrainersOftenMakeMonHoldBerries, MSGBOX_DEFAULT
# 271 "data/maps/Route104/scripts.pory"
	release
# 272 "data/maps/Route104/scripts.pory"
	end
# 273 "data/maps/Route104/scripts.pory"

# 274 "data/maps/Route104/scripts.pory"
Route104_EventScript_ReceivedBerry::
# 275 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_TrainersOftenMakeMonHoldBerries, MSGBOX_DEFAULT
# 276 "data/maps/Route104/scripts.pory"
	release
# 277 "data/maps/Route104/scripts.pory"
	end
# 278 "data/maps/Route104/scripts.pory"

# 279 "data/maps/Route104/scripts.pory"
Route104_EventScript_WhiteHerbFlorist::
# 280 "data/maps/Route104/scripts.pory"
	lock
# 281 "data/maps/Route104/scripts.pory"
	faceplayer
# 282 "data/maps/Route104/scripts.pory"
	goto_if_set FLAG_RECEIVED_WHITE_HERB, Route104_EventScript_ReceivedWhiteHerb
# 283 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_DontNeedThisTakeIt, MSGBOX_DEFAULT
# 284 "data/maps/Route104/scripts.pory"
	giveitem ITEM_WHITE_HERB
# 285 "data/maps/Route104/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 286 "data/maps/Route104/scripts.pory"
	setflag FLAG_RECEIVED_WHITE_HERB
# 287 "data/maps/Route104/scripts.pory"
	release
# 288 "data/maps/Route104/scripts.pory"
	end
# 289 "data/maps/Route104/scripts.pory"

# 290 "data/maps/Route104/scripts.pory"
Route104_EventScript_ReceivedWhiteHerb::
# 291 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_FlowerShopSellingSaplings, MSGBOX_DEFAULT
# 292 "data/maps/Route104/scripts.pory"
	release
# 293 "data/maps/Route104/scripts.pory"
	end
# 294 "data/maps/Route104/scripts.pory"

# 295 "data/maps/Route104/scripts.pory"
Route104_EventScript_Girl1::
# 296 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_BrineyLivesInSeasideCottage, MSGBOX_NPC
# 297 "data/maps/Route104/scripts.pory"
	end
# 298 "data/maps/Route104/scripts.pory"

# 299 "data/maps/Route104/scripts.pory"
Route104_EventScript_BugCatcher::
# 300 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_WhatsItLikeAtBottomOfSea, MSGBOX_SIGN
# 301 "data/maps/Route104/scripts.pory"
	end
# 302 "data/maps/Route104/scripts.pory"

# 303 "data/maps/Route104/scripts.pory"
Route104_EventScript_BrineysCottageSign::
# 304 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_MrBrineysCottage, MSGBOX_SIGN
# 305 "data/maps/Route104/scripts.pory"
	end
# 306 "data/maps/Route104/scripts.pory"

# 307 "data/maps/Route104/scripts.pory"
Route104_EventScript_RouteSignPetalburg::
# 308 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_RouteSignPetalburg, MSGBOX_SIGN
# 309 "data/maps/Route104/scripts.pory"
	end
# 310 "data/maps/Route104/scripts.pory"

# 311 "data/maps/Route104/scripts.pory"
Route104_EventScript_RouteSignRustboro::
# 312 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_RouteSignRustboro, MSGBOX_SIGN
# 313 "data/maps/Route104/scripts.pory"
	end
# 314 "data/maps/Route104/scripts.pory"

# 315 "data/maps/Route104/scripts.pory"
Route104_EventScript_FlowerShopSign::
# 316 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_PrettyPetalFlowShop, MSGBOX_SIGN
# 317 "data/maps/Route104/scripts.pory"
	end
# 318 "data/maps/Route104/scripts.pory"

# 319 "data/maps/Route104/scripts.pory"
Route104_EventScript_TrainerTipsDoubleBattles::
# 320 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_TrainerTipsDoubleBattles, MSGBOX_SIGN
# 321 "data/maps/Route104/scripts.pory"
	end
# 322 "data/maps/Route104/scripts.pory"

# 323 "data/maps/Route104/scripts.pory"
Route104_EventScript_Boy1::
# 324 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_ThrowBallAtWeakenedPokemon, MSGBOX_NPC
# 325 "data/maps/Route104/scripts.pory"
	end
# 326 "data/maps/Route104/scripts.pory"

# 327 "data/maps/Route104/scripts.pory"
Route104_EventScript_Woman::
# 328 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_OnlyThrowBallAtWildPokemon, MSGBOX_NPC
# 329 "data/maps/Route104/scripts.pory"
	end
# 330 "data/maps/Route104/scripts.pory"

# 331 "data/maps/Route104/scripts.pory"

# 332 "data/maps/Route104/scripts.pory"
Route104_EventScript_ReceivedBulletSeed::
# 333 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_TMsAreOneTimeUse, MSGBOX_DEFAULT
# 334 "data/maps/Route104/scripts.pory"
	release
# 335 "data/maps/Route104/scripts.pory"
	end
# 336 "data/maps/Route104/scripts.pory"

# 337 "data/maps/Route104/scripts.pory"
Route104_EventScript_Girl2::
# 338 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_ImNotATrainer, MSGBOX_NPC
# 339 "data/maps/Route104/scripts.pory"
	end
# 340 "data/maps/Route104/scripts.pory"

# 341 "data/maps/Route104/scripts.pory"
Route104_EventScript_SailToDewford::
# 342 "data/maps/Route104/scripts.pory"
	setobjectsubpriority LOCALID_BRINEY_R104, MAP_ROUTE104, 0
# 343 "data/maps/Route104/scripts.pory"
	setobjectsubpriority OBJ_EVENT_ID_PLAYER, MAP_ROUTE104, 0
# 344 "data/maps/Route104/scripts.pory"
	applymovement LOCALID_BRINEY_R104, Route104_Movement_BrineyBoardBoat
# 345 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 346 "data/maps/Route104/scripts.pory"
	removeobject LOCALID_BRINEY_R104
# 347 "data/maps/Route104/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_PlayerBoardBoat
# 348 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 349 "data/maps/Route104/scripts.pory"
	hideobjectat OBJ_EVENT_ID_PLAYER, MAP_ROUTE104
# 350 "data/maps/Route104/scripts.pory"
	call Common_EventScript_PlayBrineysBoatMusic
# 351 "data/maps/Route104/scripts.pory"
	goto_if_set FLAG_ENABLE_NORMAN_MATCH_CALL, Route104_EventScript_SailToDewfordNoCall
# 352 "data/maps/Route104/scripts.pory"
	goto_if_unset FLAG_ENABLE_NORMAN_MATCH_CALL, Route104_EventScript_SailToDewfordDadCalls
# 353 "data/maps/Route104/scripts.pory"
	end
# 354 "data/maps/Route104/scripts.pory"

# 355 "data/maps/Route104/scripts.pory"
Route104_EventScript_SailToDewfordNoCall::
# 356 "data/maps/Route104/scripts.pory"
	applymovement LOCALID_BOAT_R104, Route104_Movement_SailToDewford
# 357 "data/maps/Route104/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_SailToDewford
# 358 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 359 "data/maps/Route104/scripts.pory"
	goto Route104_EventScript_ArriveInDewford
# 360 "data/maps/Route104/scripts.pory"

# 361 "data/maps/Route104/scripts.pory"
Route104_EventScript_SailToDewfordDadCalls::
# 362 "data/maps/Route104/scripts.pory"
	applymovement LOCALID_BOAT_R104, Route104_Movement_SailToDewfordBeforeDadCalls
# 363 "data/maps/Route104/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_SailToDewfordBeforeDadCalls
# 364 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 365 "data/maps/Route104/scripts.pory"
	pokenavcall Route104_Text_DadPokenavCall
# 366 "data/maps/Route104/scripts.pory"
	waitmessage
# 367 "data/maps/Route104/scripts.pory"
	delay 30
# 368 "data/maps/Route104/scripts.pory"
	playfanfare MUS_REGISTER_MATCH_CALL
# 369 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_RegisteredDadInPokenav, MSGBOX_DEFAULT
# 370 "data/maps/Route104/scripts.pory"
	waitfanfare
# 371 "data/maps/Route104/scripts.pory"
	closemessage
# 372 "data/maps/Route104/scripts.pory"
	delay 30
# 373 "data/maps/Route104/scripts.pory"
	setflag FLAG_ENABLE_NORMAN_MATCH_CALL
# 374 "data/maps/Route104/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_SailToDewfordAfterDadCalls
# 375 "data/maps/Route104/scripts.pory"
	applymovement LOCALID_BOAT_R104, Route104_Movement_SailToDewfordAfterDadCalls, MAP_ROUTE104
# 376 "data/maps/Route104/scripts.pory"
	waitmovement LOCALID_BOAT_R104, MAP_ROUTE104
# 377 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 378 "data/maps/Route104/scripts.pory"
	goto Route104_EventScript_ArriveInDewford
# 379 "data/maps/Route104/scripts.pory"

# 380 "data/maps/Route104/scripts.pory"
Route104_EventScript_ArriveInDewford::
# 381 "data/maps/Route104/scripts.pory"
	delay 50
# 382 "data/maps/Route104/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_PlayerExitBoat
# 383 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 384 "data/maps/Route104/scripts.pory"
	call Common_EventScript_StopBrineysBoatMusic
# 385 "data/maps/Route104/scripts.pory"
	showobjectat OBJ_EVENT_ID_PLAYER, MAP_DEWFORD_TOWN
# 386 "data/maps/Route104/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Route104_Movement_PlayerMoveForBriney
# 387 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 388 "data/maps/Route104/scripts.pory"
	setobjectxyperm LOCALID_BRINEY_DEWFORD, 12, 8
# 389 "data/maps/Route104/scripts.pory"
	addobject LOCALID_BRINEY_DEWFORD
# 390 "data/maps/Route104/scripts.pory"
	setobjectsubpriority LOCALID_BRINEY_DEWFORD, MAP_DEWFORD_TOWN, 0
# 391 "data/maps/Route104/scripts.pory"
	clearflag FLAG_HIDE_MR_BRINEY_DEWFORD_TOWN
# 392 "data/maps/Route104/scripts.pory"
	applymovement LOCALID_BRINEY_DEWFORD, Route104_Movement_BrineyExitBoat
# 393 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 394 "data/maps/Route104/scripts.pory"
	addobject LOCALID_BOAT_DEWFORD
# 395 "data/maps/Route104/scripts.pory"
	clearflag FLAG_HIDE_MR_BRINEY_BOAT_DEWFORD_TOWN
# 396 "data/maps/Route104/scripts.pory"
	call Common_EventScript_StopBrineysBoatMusic
# 397 "data/maps/Route104/scripts.pory"
	setflag FLAG_HIDE_ROUTE_104_MR_BRINEY_BOAT
# 398 "data/maps/Route104/scripts.pory"
	hideobjectat LOCALID_BOAT_R104, MAP_ROUTE104
# 399 "data/maps/Route104/scripts.pory"
	copyvar VAR_BRINEY_LOCATION, VAR_0x8008
# 400 "data/maps/Route104/scripts.pory"
	resetobjectsubpriority OBJ_EVENT_ID_PLAYER, MAP_ROUTE104
# 401 "data/maps/Route104/scripts.pory"
	resetobjectsubpriority LOCALID_BRINEY_DEWFORD, MAP_DEWFORD_TOWN
# 402 "data/maps/Route104/scripts.pory"
	copyobjectxytoperm LOCALID_BRINEY_DEWFORD
# 403 "data/maps/Route104/scripts.pory"
	setvar VAR_BOARD_BRINEY_BOAT_STATE, 0
# 404 "data/maps/Route104/scripts.pory"
	goto_if_unset FLAG_DELIVERED_STEVEN_LETTER, Route104_EventScript_DeliverLetterReminder
# 405 "data/maps/Route104/scripts.pory"
	goto_if_set FLAG_DELIVERED_STEVEN_LETTER, Route104_EventScript_LandedInDewford
# 406 "data/maps/Route104/scripts.pory"
	end
# 407 "data/maps/Route104/scripts.pory"

# 408 "data/maps/Route104/scripts.pory"
Route104_EventScript_DeliverLetterReminder::
# 409 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_LandedInDewfordDeliverLetter, MSGBOX_DEFAULT
# 410 "data/maps/Route104/scripts.pory"
	releaseall
# 411 "data/maps/Route104/scripts.pory"
	end
# 412 "data/maps/Route104/scripts.pory"

# 413 "data/maps/Route104/scripts.pory"
Route104_EventScript_LandedInDewford::
# 414 "data/maps/Route104/scripts.pory"
	msgbox DewfordTown_Text_BrineyLandedInDewford, MSGBOX_DEFAULT
# 415 "data/maps/Route104/scripts.pory"
	releaseall
# 416 "data/maps/Route104/scripts.pory"
	end
# 417 "data/maps/Route104/scripts.pory"

# 418 "data/maps/Route104/scripts.pory"
Route104_Movement_SailToDewfordBeforeDadCalls:
# 419 "data/maps/Route104/scripts.pory"
	walk_down
# 420 "data/maps/Route104/scripts.pory"
	walk_down
# 421 "data/maps/Route104/scripts.pory"
	walk_down
# 422 "data/maps/Route104/scripts.pory"
	walk_down
# 423 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 424 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 425 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 426 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 427 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 428 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 429 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 430 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 431 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 432 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 433 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 434 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 435 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 436 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 437 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 438 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 439 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 440 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 441 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 442 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 443 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 444 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 445 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 446 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 447 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 448 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 449 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 450 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 451 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 452 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 453 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 454 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 455 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 456 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 457 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 458 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 459 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 460 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 461 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 462 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 463 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 464 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 465 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 466 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 467 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 468 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 469 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 470 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 471 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 472 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 473 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 474 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 475 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 476 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 477 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 478 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 479 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 480 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 481 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 482 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 483 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 484 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 485 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 486 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 487 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 488 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 489 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 490 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 491 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 492 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 493 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 494 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 495 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 496 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 497 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 498 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 499 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 500 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 501 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 502 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 503 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 504 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 505 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 506 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 507 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 508 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 509 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 510 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 511 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 512 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 513 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 514 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 515 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 516 "data/maps/Route104/scripts.pory"
	step_end
# 517 "data/maps/Route104/scripts.pory"

# 518 "data/maps/Route104/scripts.pory"
Route104_Movement_SailToDewfordAfterDadCalls:
# 519 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 520 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 521 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 522 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 523 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 524 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 525 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 526 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 527 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 528 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 529 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 530 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 531 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 532 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 533 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 534 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 535 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 536 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 537 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 538 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 539 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 540 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 541 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 542 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 543 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 544 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 545 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 546 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 547 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 548 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 549 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 550 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 551 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 552 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 553 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 554 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 555 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 556 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 557 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 558 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 559 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 560 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 561 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 562 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 563 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 564 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 565 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 566 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 567 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 568 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 569 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 570 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 571 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 572 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 573 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 574 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 575 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 576 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 577 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 578 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 579 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 580 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 581 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 582 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 583 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 584 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 585 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 586 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 587 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 588 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 589 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 590 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 591 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 592 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 593 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 594 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 595 "data/maps/Route104/scripts.pory"
	walk_right
# 596 "data/maps/Route104/scripts.pory"
	walk_right
# 597 "data/maps/Route104/scripts.pory"
	walk_down
# 598 "data/maps/Route104/scripts.pory"
	walk_down
# 599 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 600 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 601 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 602 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 603 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 604 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 605 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 606 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 607 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 608 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 609 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 610 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 611 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 612 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 613 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 614 "data/maps/Route104/scripts.pory"
	walk_down
# 615 "data/maps/Route104/scripts.pory"
	walk_down
# 616 "data/maps/Route104/scripts.pory"
	step_end
# 617 "data/maps/Route104/scripts.pory"

# 618 "data/maps/Route104/scripts.pory"
Route104_Movement_SailToDewford:
# 619 "data/maps/Route104/scripts.pory"
	walk_down
# 620 "data/maps/Route104/scripts.pory"
	walk_down
# 621 "data/maps/Route104/scripts.pory"
	walk_down
# 622 "data/maps/Route104/scripts.pory"
	walk_down
# 623 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 624 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 625 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 626 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 627 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 628 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 629 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 630 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 631 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 632 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 633 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 634 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 635 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 636 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 637 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 638 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 639 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 640 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 641 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 642 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 643 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 644 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 645 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 646 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 647 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 648 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 649 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 650 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 651 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 652 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 653 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 654 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 655 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 656 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 657 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 658 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 659 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 660 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 661 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 662 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 663 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 664 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 665 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 666 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 667 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 668 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 669 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 670 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 671 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 672 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 673 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 674 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 675 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 676 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 677 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 678 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 679 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 680 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 681 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 682 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 683 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 684 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 685 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 686 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 687 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 688 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 689 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 690 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 691 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 692 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 693 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 694 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 695 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 696 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 697 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 698 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 699 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 700 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 701 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 702 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 703 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 704 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 705 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 706 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 707 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 708 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 709 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 710 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 711 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 712 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 713 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 714 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 715 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 716 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 717 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 718 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 719 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 720 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 721 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 722 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 723 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 724 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 725 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 726 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 727 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 728 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 729 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 730 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 731 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 732 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 733 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 734 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 735 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 736 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 737 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 738 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 739 "data/maps/Route104/scripts.pory"
	walk_faster_down
# 740 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 741 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 742 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 743 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 744 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 745 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 746 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 747 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 748 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 749 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 750 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 751 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 752 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 753 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 754 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 755 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 756 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 757 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 758 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 759 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 760 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 761 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 762 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 763 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 764 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 765 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 766 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 767 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 768 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 769 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 770 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 771 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 772 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 773 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 774 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 775 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 776 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 777 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 778 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 779 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 780 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 781 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 782 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 783 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 784 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 785 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 786 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 787 "data/maps/Route104/scripts.pory"
	walk_faster_right
# 788 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 789 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 790 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 791 "data/maps/Route104/scripts.pory"
	walk_fast_right
# 792 "data/maps/Route104/scripts.pory"
	walk_right
# 793 "data/maps/Route104/scripts.pory"
	walk_right
# 794 "data/maps/Route104/scripts.pory"
	walk_down
# 795 "data/maps/Route104/scripts.pory"
	walk_down
# 796 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 797 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 798 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 799 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 800 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 801 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 802 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 803 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 804 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 805 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 806 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 807 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 808 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 809 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 810 "data/maps/Route104/scripts.pory"
	walk_fast_down
# 811 "data/maps/Route104/scripts.pory"
	walk_down
# 812 "data/maps/Route104/scripts.pory"
	walk_down
# 813 "data/maps/Route104/scripts.pory"
	step_end
# 814 "data/maps/Route104/scripts.pory"

# 815 "data/maps/Route104/scripts.pory"
Route104_Movement_PlayerBoardBoat:
# 816 "data/maps/Route104/scripts.pory"
	walk_left
# 817 "data/maps/Route104/scripts.pory"
	walk_down
# 818 "data/maps/Route104/scripts.pory"
	walk_down
# 819 "data/maps/Route104/scripts.pory"
	step_end
# 820 "data/maps/Route104/scripts.pory"

# 821 "data/maps/Route104/scripts.pory"
Route104_Movement_PlayerExitBoat:
# 822 "data/maps/Route104/scripts.pory"
	walk_down
# 823 "data/maps/Route104/scripts.pory"
	step_end
# 824 "data/maps/Route104/scripts.pory"

# 825 "data/maps/Route104/scripts.pory"
Route104_Movement_PlayerMoveForBriney:
# 826 "data/maps/Route104/scripts.pory"
	walk_down
# 827 "data/maps/Route104/scripts.pory"
	walk_left
# 828 "data/maps/Route104/scripts.pory"
	walk_in_place_faster_right
# 829 "data/maps/Route104/scripts.pory"
	step_end
# 830 "data/maps/Route104/scripts.pory"

# 831 "data/maps/Route104/scripts.pory"
Route104_Movement_BrineyBoardBoat:
# 832 "data/maps/Route104/scripts.pory"
	walk_down
# 833 "data/maps/Route104/scripts.pory"
	walk_down
# 834 "data/maps/Route104/scripts.pory"
	step_end
# 835 "data/maps/Route104/scripts.pory"

# 836 "data/maps/Route104/scripts.pory"
Route104_Movement_BrineyExitBoat:
# 837 "data/maps/Route104/scripts.pory"
	walk_down
# 838 "data/maps/Route104/scripts.pory"
	walk_in_place_faster_left
# 839 "data/maps/Route104/scripts.pory"
	step_end
# 840 "data/maps/Route104/scripts.pory"

# 841 "data/maps/Route104/scripts.pory"
Route104_EventScript_Ivan::
# 842 "data/maps/Route104/scripts.pory"
	trainerbattle_single TRAINER_IVAN, Route104_Text_IvanIntro, Route104_Text_IvanDefeat
# 843 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_IvanPostBattle, MSGBOX_AUTOCLOSE
# 844 "data/maps/Route104/scripts.pory"
	end
# 845 "data/maps/Route104/scripts.pory"

# 846 "data/maps/Route104/scripts.pory"

# 847 "data/maps/Route104/scripts.pory"
Route104_EventScript_Haley::
# 848 "data/maps/Route104/scripts.pory"
	trainerbattle_single TRAINER_HALEY_1, Route104_Text_HaleyIntro, Route104_Text_HaleyDefeat, Route104_EventScript_TryRegisterHaleyAfterBattle
# 849 "data/maps/Route104/scripts.pory"
	specialvar VAR_RESULT, ShouldTryRematchBattle
# 850 "data/maps/Route104/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Route104_EventScript_RematchHaley
# 851 "data/maps/Route104/scripts.pory"
	setvar VAR_0x8004, TRAINER_HALEY_1
# 852 "data/maps/Route104/scripts.pory"
	specialvar VAR_RESULT, IsTrainerRegistered
# 853 "data/maps/Route104/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Route104_EventScript_TryRegisterHaley
# 854 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_HaleyPostBattle, MSGBOX_DEFAULT
# 855 "data/maps/Route104/scripts.pory"
	release
# 856 "data/maps/Route104/scripts.pory"
	end
# 857 "data/maps/Route104/scripts.pory"

# 858 "data/maps/Route104/scripts.pory"
Route104_EventScript_TryRegisterHaleyAfterBattle::
# 859 "data/maps/Route104/scripts.pory"
	special PlayerFaceTrainerAfterBattle
# 860 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 861 "data/maps/Route104/scripts.pory"
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterHaleyAfterBattle
# 862 "data/maps/Route104/scripts.pory"
	release
# 863 "data/maps/Route104/scripts.pory"
	end
# 864 "data/maps/Route104/scripts.pory"

# 865 "data/maps/Route104/scripts.pory"
Route104_EventScript_RegisterHaleyAfterBattle::
# 866 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_HaleyRegister2, MSGBOX_DEFAULT
# 867 "data/maps/Route104/scripts.pory"
	register_matchcall TRAINER_HALEY_1
# 868 "data/maps/Route104/scripts.pory"
	release
# 869 "data/maps/Route104/scripts.pory"
	end
# 870 "data/maps/Route104/scripts.pory"

# 871 "data/maps/Route104/scripts.pory"
Route104_EventScript_TryRegisterHaley::
# 872 "data/maps/Route104/scripts.pory"
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterHaley
# 873 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_HaleyPostBattle, MSGBOX_DEFAULT
# 874 "data/maps/Route104/scripts.pory"
	release
# 875 "data/maps/Route104/scripts.pory"
	end
# 876 "data/maps/Route104/scripts.pory"

# 877 "data/maps/Route104/scripts.pory"
Route104_EventScript_RegisterHaley::
# 878 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_HaleyRegister1, MSGBOX_DEFAULT
# 879 "data/maps/Route104/scripts.pory"
	register_matchcall TRAINER_HALEY_1
# 880 "data/maps/Route104/scripts.pory"
	release
# 881 "data/maps/Route104/scripts.pory"
	end
# 882 "data/maps/Route104/scripts.pory"

# 883 "data/maps/Route104/scripts.pory"
Route104_EventScript_RematchHaley::
# 884 "data/maps/Route104/scripts.pory"
	trainerbattle_rematch TRAINER_HALEY_1, Route104_Text_HaleyRematchIntro, Route104_Text_HaleyRematchDefeat
# 885 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_HaleyPostRematch, MSGBOX_AUTOCLOSE
# 886 "data/maps/Route104/scripts.pory"
	end
# 887 "data/maps/Route104/scripts.pory"

# 888 "data/maps/Route104/scripts.pory"
Route104_EventScript_Winston::
# 889 "data/maps/Route104/scripts.pory"
	trainerbattle_single TRAINER_WINSTON_1, Route104_Text_WinstonIntro, Route104_Text_WinstonDefeat, Route104_EventScript_TryRegisterWinstonAfterBattle
# 890 "data/maps/Route104/scripts.pory"
	specialvar VAR_RESULT, ShouldTryRematchBattle
# 891 "data/maps/Route104/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Route104_EventScript_RematchWinston
# 892 "data/maps/Route104/scripts.pory"
	setvar VAR_0x8004, TRAINER_WINSTON_1
# 893 "data/maps/Route104/scripts.pory"
	specialvar VAR_RESULT, IsTrainerRegistered
# 894 "data/maps/Route104/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Route104_EventScript_TryRegisterWinston
# 895 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_WinstonPostBattle, MSGBOX_DEFAULT
# 896 "data/maps/Route104/scripts.pory"
	release
# 897 "data/maps/Route104/scripts.pory"
	end
# 898 "data/maps/Route104/scripts.pory"

# 899 "data/maps/Route104/scripts.pory"
Route104_EventScript_TryRegisterWinstonAfterBattle::
# 900 "data/maps/Route104/scripts.pory"
	special PlayerFaceTrainerAfterBattle
# 901 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 902 "data/maps/Route104/scripts.pory"
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterWinstonAfterBattle
# 903 "data/maps/Route104/scripts.pory"
	release
# 904 "data/maps/Route104/scripts.pory"
	end
# 905 "data/maps/Route104/scripts.pory"

# 906 "data/maps/Route104/scripts.pory"
Route104_EventScript_RegisterWinstonAfterBattle::
# 907 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_WinstonRegister2, MSGBOX_DEFAULT
# 908 "data/maps/Route104/scripts.pory"
	register_matchcall TRAINER_WINSTON_1
# 909 "data/maps/Route104/scripts.pory"
	release
# 910 "data/maps/Route104/scripts.pory"
	end
# 911 "data/maps/Route104/scripts.pory"

# 912 "data/maps/Route104/scripts.pory"
Route104_EventScript_TryRegisterWinston::
# 913 "data/maps/Route104/scripts.pory"
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterWinston
# 914 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_WinstonPostBattle, MSGBOX_DEFAULT
# 915 "data/maps/Route104/scripts.pory"
	release
# 916 "data/maps/Route104/scripts.pory"
	end
# 917 "data/maps/Route104/scripts.pory"

# 918 "data/maps/Route104/scripts.pory"
Route104_EventScript_RegisterWinston::
# 919 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_WinstonRegister1, MSGBOX_DEFAULT
# 920 "data/maps/Route104/scripts.pory"
	register_matchcall TRAINER_WINSTON_1
# 921 "data/maps/Route104/scripts.pory"
	release
# 922 "data/maps/Route104/scripts.pory"
	end
# 923 "data/maps/Route104/scripts.pory"

# 924 "data/maps/Route104/scripts.pory"
Route104_EventScript_RematchWinston::
# 925 "data/maps/Route104/scripts.pory"
	trainerbattle_rematch TRAINER_WINSTON_1, Route104_Text_WinstonRematchIntro, Route104_Text_WinstonRematchDefeat
# 926 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_WinstonPostRematch, MSGBOX_AUTOCLOSE
# 927 "data/maps/Route104/scripts.pory"
	end
# 928 "data/maps/Route104/scripts.pory"

# 929 "data/maps/Route104/scripts.pory"
Route104_EventScript_TryRegisterCindyAfterBattle::
# 930 "data/maps/Route104/scripts.pory"
	special PlayerFaceTrainerAfterBattle
# 931 "data/maps/Route104/scripts.pory"
	waitmovement 0
# 932 "data/maps/Route104/scripts.pory"
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterCindyAfterBattle
# 933 "data/maps/Route104/scripts.pory"
	release
# 934 "data/maps/Route104/scripts.pory"
	end
# 935 "data/maps/Route104/scripts.pory"

# 936 "data/maps/Route104/scripts.pory"
Route104_EventScript_RegisterCindyAfterBattle::
# 937 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_CindyRegister2, MSGBOX_DEFAULT
# 938 "data/maps/Route104/scripts.pory"
	register_matchcall TRAINER_CINDY_1
# 939 "data/maps/Route104/scripts.pory"
	release
# 940 "data/maps/Route104/scripts.pory"
	end
# 941 "data/maps/Route104/scripts.pory"

# 942 "data/maps/Route104/scripts.pory"
Route104_EventScript_TryRegisterCindy::
# 943 "data/maps/Route104/scripts.pory"
	goto_if_set FLAG_HAS_MATCH_CALL, Route104_EventScript_RegisterCindy
# 944 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_CindyPostBattle, MSGBOX_DEFAULT
# 945 "data/maps/Route104/scripts.pory"
	release
# 946 "data/maps/Route104/scripts.pory"
	end
# 947 "data/maps/Route104/scripts.pory"

# 948 "data/maps/Route104/scripts.pory"
Route104_EventScript_RegisterCindy::
# 949 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_CindyRegister1, MSGBOX_DEFAULT
# 950 "data/maps/Route104/scripts.pory"
	register_matchcall TRAINER_CINDY_1
# 951 "data/maps/Route104/scripts.pory"
	release
# 952 "data/maps/Route104/scripts.pory"
	end
# 953 "data/maps/Route104/scripts.pory"

# 954 "data/maps/Route104/scripts.pory"
Route104_EventScript_RematchCindy::
# 955 "data/maps/Route104/scripts.pory"
	trainerbattle_rematch TRAINER_CINDY_1, Route104_Text_CindyRematchIntro, Route104_Text_CindyRematchDefeat
# 956 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_CindyPostRematch, MSGBOX_AUTOCLOSE
# 957 "data/maps/Route104/scripts.pory"
	end
# 958 "data/maps/Route104/scripts.pory"

# 959 "data/maps/Route104/scripts.pory"
Route104_EventScript_Gina::
# 960 "data/maps/Route104/scripts.pory"
	trainerbattle_double TRAINER_GINA_AND_MIA_1, Route104_Text_GinaIntro, Route104_Text_GinaDefeat, Route104_Text_GinaNotEnoughMons
# 961 "data/maps/Route104/scripts.pory"
	special GetPlayerBigGuyGirlString
# 962 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_GinaPostBattle, MSGBOX_DEFAULT
# 963 "data/maps/Route104/scripts.pory"
	release
# 964 "data/maps/Route104/scripts.pory"
	end
# 965 "data/maps/Route104/scripts.pory"

# 966 "data/maps/Route104/scripts.pory"
Route104_EventScript_Mia::
# 967 "data/maps/Route104/scripts.pory"
	trainerbattle_double TRAINER_GINA_AND_MIA_1, Route104_Text_MiaIntro, Route104_Text_MiaDefeat, Route104_Text_MiaNotEnoughMons
# 968 "data/maps/Route104/scripts.pory"
	special GetPlayerBigGuyGirlString
# 969 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_MiaPostBattle, MSGBOX_DEFAULT
# 970 "data/maps/Route104/scripts.pory"
	release
# 971 "data/maps/Route104/scripts.pory"
	end
# 972 "data/maps/Route104/scripts.pory"

# 973 "data/maps/Route104/scripts.pory"
Route104_EventScript_Darian::
# 974 "data/maps/Route104/scripts.pory"
	trainerbattle_single TRAINER_DARIAN, Route104_Text_DarianIntro, Route104_Text_DarianDefeat
# 975 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_DarianPostBattle, MSGBOX_AUTOCLOSE
# 976 "data/maps/Route104/scripts.pory"
	end
# 977 "data/maps/Route104/scripts.pory"

# 978 "data/maps/Route104/scripts.pory"
Route104_Text_BrineyLivesInSeasideCottage:
# 979 "data/maps/Route104/scripts.pory"
	.string "That seaside cottage is where\n"
# 980 "data/maps/Route104/scripts.pory"
	.string "MR. BRINEY lives.\p"
# 981 "data/maps/Route104/scripts.pory"
	.string "He was once a mighty sailor who never\n"
# 982 "data/maps/Route104/scripts.pory"
	.string "feared the sea, however stormy.$"
# 983 "data/maps/Route104/scripts.pory"

# 984 "data/maps/Route104/scripts.pory"
Route104_Text_WhatsItLikeAtBottomOfSea:
# 985 "data/maps/Route104/scripts.pory"
	.string "The sea, huh?\p"
# 986 "data/maps/Route104/scripts.pory"
	.string "I wonder what it's like at the bottom\n"
# 987 "data/maps/Route104/scripts.pory"
	.string "of the sea?$"
# 988 "data/maps/Route104/scripts.pory"

# 989 "data/maps/Route104/scripts.pory"
Route104_Text_ThrowBallAtWeakenedPokemon:
# 990 "data/maps/Route104/scripts.pory"
	.string "If you're going to throw a POKé BALL,\n"
# 991 "data/maps/Route104/scripts.pory"
	.string "weaken the wild POKéMON first.\p"
# 992 "data/maps/Route104/scripts.pory"
	.string "It will be easier to catch if it's been\n"
# 993 "data/maps/Route104/scripts.pory"
	.string "poisoned, burned, or lulled to sleep.$"
# 994 "data/maps/Route104/scripts.pory"

# 995 "data/maps/Route104/scripts.pory"
Route104_Text_OnlyThrowBallAtWildPokemon:
# 996 "data/maps/Route104/scripts.pory"
	.string "You're a thief if you try to steal\n"
# 997 "data/maps/Route104/scripts.pory"
	.string "someone else's POKéMON.\p"
# 998 "data/maps/Route104/scripts.pory"
	.string "You should throw POKé BALLS only at\n"
# 999 "data/maps/Route104/scripts.pory"
	.string "wild POKéMON.$"
# 1000 "data/maps/Route104/scripts.pory"

# 1001 "data/maps/Route104/scripts.pory"
Route104_Text_ImNotATrainer:
# 1002 "data/maps/Route104/scripts.pory"
	.string "Oh, no, I'm not a TRAINER.\p"
# 1003 "data/maps/Route104/scripts.pory"
	.string "But that's right, if TRAINERS lock eyes,\n"
# 1004 "data/maps/Route104/scripts.pory"
	.string "it's a challenge to battle.\p"
# 1005 "data/maps/Route104/scripts.pory"
	.string "If you don't want to battle, stay out\n"
# 1006 "data/maps/Route104/scripts.pory"
	.string "of their sight.$"
# 1007 "data/maps/Route104/scripts.pory"

# 1008 "data/maps/Route104/scripts.pory"
Route104_Text_LikeFillingMouthWithSeedsTakeThis:
# 1009 "data/maps/Route104/scripts.pory"
	.string "I like filling my mouth with seeds,\n"
# 1010 "data/maps/Route104/scripts.pory"
	.string "then spitting them out fast!\p"
# 1011 "data/maps/Route104/scripts.pory"
	.string "You can have this, so you try it out!\p"
# 1012 "data/maps/Route104/scripts.pory"
	.string "Use it on a POKéMON, and it will learn\n"
# 1013 "data/maps/Route104/scripts.pory"
	.string "a move for firing seeds rapidly.$"
# 1014 "data/maps/Route104/scripts.pory"

# 1015 "data/maps/Route104/scripts.pory"
Route104_Text_TMsAreOneTimeUse:
# 1016 "data/maps/Route104/scripts.pory"
	.string "A word of advice!\p"
# 1017 "data/maps/Route104/scripts.pory"
	.string "A TM, TECHNICAL MACHINE, is good only\n"
# 1018 "data/maps/Route104/scripts.pory"
	.string "for one-time use.\p"
# 1019 "data/maps/Route104/scripts.pory"
	.string "Once you use it, it's gone.\n"
# 1020 "data/maps/Route104/scripts.pory"
	.string "Think twice before using it!$"
# 1021 "data/maps/Route104/scripts.pory"

# 1022 "data/maps/Route104/scripts.pory"
Route104_Text_DontNeedThisTakeIt:
# 1023 "data/maps/Route104/scripts.pory"
	.string "This FLOWER SHOP started selling\n"
# 1024 "data/maps/Route104/scripts.pory"
	.string "saplings recently.\p"
# 1025 "data/maps/Route104/scripts.pory"
	.string "It made me so happy, I went overboard\n"
# 1026 "data/maps/Route104/scripts.pory"
	.string "shopping.\p"
# 1027 "data/maps/Route104/scripts.pory"
	.string "I don't need this WHITE HERB anymore.\n"
# 1028 "data/maps/Route104/scripts.pory"
	.string "Would you take it, please?$"
# 1029 "data/maps/Route104/scripts.pory"

# 1030 "data/maps/Route104/scripts.pory"
Route104_Text_FlowerShopSellingSaplings:
# 1031 "data/maps/Route104/scripts.pory"
	.string "This FLOWER SHOP started selling\n"
# 1032 "data/maps/Route104/scripts.pory"
	.string "saplings recently.\p"
# 1033 "data/maps/Route104/scripts.pory"
	.string "It made me so happy, I went overboard\n"
# 1034 "data/maps/Route104/scripts.pory"
	.string "shopping. Where should I put them?$"
# 1035 "data/maps/Route104/scripts.pory"

# 1036 "data/maps/Route104/scripts.pory"
Route104_Text_MrBrineysCottage:
# 1037 "data/maps/Route104/scripts.pory"
	.string "MR. BRINEY'S COTTAGE$"
# 1038 "data/maps/Route104/scripts.pory"

# 1039 "data/maps/Route104/scripts.pory"
Route104_Text_RouteSignPetalburg:
# 1040 "data/maps/Route104/scripts.pory"
	.string "ROUTE 1O4\n"
# 1041 "data/maps/Route104/scripts.pory"
	.string "{RIGHT_ARROW} PETALBURG CITY$"
# 1042 "data/maps/Route104/scripts.pory"

# 1043 "data/maps/Route104/scripts.pory"
Route104_Text_RouteSignRustboro:
# 1044 "data/maps/Route104/scripts.pory"
	.string "ROUTE 1O4\n"
# 1045 "data/maps/Route104/scripts.pory"
	.string "{UP_ARROW} RUSTBORO CITY$"
# 1046 "data/maps/Route104/scripts.pory"

# 1047 "data/maps/Route104/scripts.pory"
Route104_Text_PrettyPetalFlowShop:
# 1048 "data/maps/Route104/scripts.pory"
	.string "PRETTY PETAL FLOWER SHOP$"
# 1049 "data/maps/Route104/scripts.pory"

# 1050 "data/maps/Route104/scripts.pory"
Route104_Text_TrainerTipsDoubleBattles:
# 1051 "data/maps/Route104/scripts.pory"
	.string "TRAINER TIPS\p"
# 1052 "data/maps/Route104/scripts.pory"
	.string "In the HOENN region there are pairs\n"
# 1053 "data/maps/Route104/scripts.pory"
	.string "of TRAINERS who challenge others\l"
# 1054 "data/maps/Route104/scripts.pory"
	.string "for 2-on-2 POKéMON battles called\l"
# 1055 "data/maps/Route104/scripts.pory"
	.string "DOUBLE BATTLES.\p"
# 1056 "data/maps/Route104/scripts.pory"
	.string "In a DOUBLE BATTLE, the TRAINER must\n"
# 1057 "data/maps/Route104/scripts.pory"
	.string "send out two POKéMON, the one at the\l"
# 1058 "data/maps/Route104/scripts.pory"
	.string "left of the list and the top one.\l"
# 1059 "data/maps/Route104/scripts.pory"
	.string "Watch how POKéMON are lined up.$"
# 1060 "data/maps/Route104/scripts.pory"

# 1061 "data/maps/Route104/scripts.pory"
Route104_Text_MayWeShouldRegister:
# 1062 "data/maps/Route104/scripts.pory"
	.string "MAY: Oh, hi, {PLAYER}{KUN}!\p"
# 1063 "data/maps/Route104/scripts.pory"
	.string "DEVON upgraded your POKéNAV with\n"
# 1064 "data/maps/Route104/scripts.pory"
	.string "the MATCH CALL system, huh?\p"
# 1065 "data/maps/Route104/scripts.pory"
	.string "We should register each other so we\n"
# 1066 "data/maps/Route104/scripts.pory"
	.string "can get in contact anytime.$"
# 1067 "data/maps/Route104/scripts.pory"

# 1068 "data/maps/Route104/scripts.pory"
Route104_Text_RegisteredMay:
# 1069 "data/maps/Route104/scripts.pory"
	.string "{PLAYER} registered MAY\n"
# 1070 "data/maps/Route104/scripts.pory"
	.string "in the POKéNAV.$"
# 1071 "data/maps/Route104/scripts.pory"

# 1072 "data/maps/Route104/scripts.pory"
Route104_Text_MayHowsYourPokedex:
# 1073 "data/maps/Route104/scripts.pory"
	.string "MAY: Oh, by the way, {PLAYER}{KUN},\n"
# 1074 "data/maps/Route104/scripts.pory"
	.string "how's your POKéDEX coming along?$"
# 1075 "data/maps/Route104/scripts.pory"

# 1076 "data/maps/Route104/scripts.pory"
Route104_Text_MayMinesDecentLetsBattle:
# 1077 "data/maps/Route104/scripts.pory"
	.string "Mine's looking pretty decent.\n"
# 1078 "data/maps/Route104/scripts.pory"
	.string "So…\l"
# 1079 "data/maps/Route104/scripts.pory"
	.string "How about a little battle?$"
# 1080 "data/maps/Route104/scripts.pory"

# 1081 "data/maps/Route104/scripts.pory"
Route104_Text_MayHaventRaisedPokemon:
# 1082 "data/maps/Route104/scripts.pory"
	.string "MAY: Oh, what's the matter?\p"
# 1083 "data/maps/Route104/scripts.pory"
	.string "Haven't you caught or raised your\n"
# 1084 "data/maps/Route104/scripts.pory"
	.string "POKéMON very much?\p"
# 1085 "data/maps/Route104/scripts.pory"
	.string "That's not very good for a TRAINER!$"
# 1086 "data/maps/Route104/scripts.pory"

# 1087 "data/maps/Route104/scripts.pory"
Route104_Text_MayLetsBattle:
# 1088 "data/maps/Route104/scripts.pory"
	.string "MAY: So, what do you think?\n"
# 1089 "data/maps/Route104/scripts.pory"
	.string "How about a little battle here?$"
# 1090 "data/maps/Route104/scripts.pory"

# 1091 "data/maps/Route104/scripts.pory"
Route104_Text_MayIntro:
# 1092 "data/maps/Route104/scripts.pory"
	.string "MAY: You just became a TRAINER,\n"
# 1093 "data/maps/Route104/scripts.pory"
	.string "{PLAYER}{KUN}. I'm not going to lose!$"
# 1094 "data/maps/Route104/scripts.pory"

# 1095 "data/maps/Route104/scripts.pory"
Route104_Text_MayDefeat:
# 1096 "data/maps/Route104/scripts.pory"
	.string "Yikes!\n"
# 1097 "data/maps/Route104/scripts.pory"
	.string "You're better than I expected!$"
# 1098 "data/maps/Route104/scripts.pory"

# 1099 "data/maps/Route104/scripts.pory"
Route104_Text_MayPostBattle:
# 1100 "data/maps/Route104/scripts.pory"
	.string "MAY: I can tell you've gotten pretty\n"
# 1101 "data/maps/Route104/scripts.pory"
	.string "good with the way you handle POKéMON.\p"
# 1102 "data/maps/Route104/scripts.pory"
	.string "But instead of only making them\n"
# 1103 "data/maps/Route104/scripts.pory"
	.string "battle, you should be like MR. BRINEY.\p"
# 1104 "data/maps/Route104/scripts.pory"
	.string "It's important to become friends with\n"
# 1105 "data/maps/Route104/scripts.pory"
	.string "POKéMON, too.$"
# 1106 "data/maps/Route104/scripts.pory"

# 1107 "data/maps/Route104/scripts.pory"
Route104_Text_BrendanWeShouldRegister:
# 1108 "data/maps/Route104/scripts.pory"
	.string "BRENDAN: Oh, hey, {PLAYER}!\p"
# 1109 "data/maps/Route104/scripts.pory"
	.string "Cool, you had DEVON install the MATCH\n"
# 1110 "data/maps/Route104/scripts.pory"
	.string "CALL system on your POKéNAV!\p"
# 1111 "data/maps/Route104/scripts.pory"
	.string "Let's register each other in our\n"
# 1112 "data/maps/Route104/scripts.pory"
	.string "POKéNAVS so we can keep in touch.$"
# 1113 "data/maps/Route104/scripts.pory"

# 1114 "data/maps/Route104/scripts.pory"
Route104_Text_RegisteredBrendan:
# 1115 "data/maps/Route104/scripts.pory"
	.string "{PLAYER} registered BRENDAN\n"
# 1116 "data/maps/Route104/scripts.pory"
	.string "in the POKéNAV.$"
# 1117 "data/maps/Route104/scripts.pory"

# 1118 "data/maps/Route104/scripts.pory"
Route104_Text_BrendanHowsYourPokedex:
# 1119 "data/maps/Route104/scripts.pory"
	.string "BRENDAN: {PLAYER}, how's your POKéDEX?\n"
# 1120 "data/maps/Route104/scripts.pory"
	.string "Have you filled in any pages yet?$"
# 1121 "data/maps/Route104/scripts.pory"

# 1122 "data/maps/Route104/scripts.pory"
Route104_Text_BrendanDoingGreatLetsBattle:
# 1123 "data/maps/Route104/scripts.pory"
	.string "Me, I'm doing great!\p"
# 1124 "data/maps/Route104/scripts.pory"
	.string "Want to check out how good I am with\n"
# 1125 "data/maps/Route104/scripts.pory"
	.string "a battle?$"
# 1126 "data/maps/Route104/scripts.pory"

# 1127 "data/maps/Route104/scripts.pory"
Route104_Text_BrendanNoConfidence:
# 1128 "data/maps/Route104/scripts.pory"
	.string "BRENDAN: What's the matter? Don't have\n"
# 1129 "data/maps/Route104/scripts.pory"
	.string "any confidence in your POKéMON?$"
# 1130 "data/maps/Route104/scripts.pory"

# 1131 "data/maps/Route104/scripts.pory"
Route104_Text_BrendanLetsBattle:
# 1132 "data/maps/Route104/scripts.pory"
	.string "BRENDAN: What's up?\n"
# 1133 "data/maps/Route104/scripts.pory"
	.string "Want to have a battle with me?$"
# 1134 "data/maps/Route104/scripts.pory"

# 1135 "data/maps/Route104/scripts.pory"
Route104_Text_BrendanIntro:
# 1136 "data/maps/Route104/scripts.pory"
	.string "BRENDAN: I know you just became\n"
# 1137 "data/maps/Route104/scripts.pory"
	.string "a TRAINER, but I won't go easy!$"
# 1138 "data/maps/Route104/scripts.pory"

# 1139 "data/maps/Route104/scripts.pory"
Route104_Text_BrendanDefeat:
# 1140 "data/maps/Route104/scripts.pory"
	.string "Hmm…\n"
# 1141 "data/maps/Route104/scripts.pory"
	.string "You're pretty good.$"
# 1142 "data/maps/Route104/scripts.pory"

# 1143 "data/maps/Route104/scripts.pory"
Route104_Text_BrendanPostBattle:
# 1144 "data/maps/Route104/scripts.pory"
	.string "BRENDAN: You've gotten pretty decent\n"
# 1145 "data/maps/Route104/scripts.pory"
	.string "at handling POKéMON.\p"
# 1146 "data/maps/Route104/scripts.pory"
	.string "But, you know, you shouldn't just be\n"
# 1147 "data/maps/Route104/scripts.pory"
	.string "making POKéMON battle.\p"
# 1148 "data/maps/Route104/scripts.pory"
	.string "Like MR. BRINEY, it's important to\n"
# 1149 "data/maps/Route104/scripts.pory"
	.string "become friends with your POKéMON.$"

Route104_EventScript_Jimmy::
# 1166 "data/maps/Route104/scripts.pory"
	trainerbattle_single TRAINER_JIMMY, Route104_Text_JimmyIntro, Route104_Text_JimmyDefeat
# 1167 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_BillyPostBattle, MSGBOX_AUTOCLOSE
	end


Route104_EventScript_Ayumu::
# 1172 "data/maps/Route104/scripts.pory"
	trainerbattle_single TRAINER_AYUMU, Route104_EventScript_Ayumu_Text_0, Route104_EventScript_Ayumu_Text_1, Route104_EventScript_Ayumu_PostBattle
# 1173 "data/maps/Route104/scripts.pory"
	msgbox Route104_EventScript_Ayumu_Text_2, MSGBOX_AUTOCLOSE
	end


Route104_EventScript_Ayumu_PostBattle::
# 1178 "data/maps/Route104/scripts.pory"
	msgbox Route104_EventScript_Ayumu_PostBattle_Text_0
# 1179 "data/maps/Route104/scripts.pory"
	msgbox Route104_EventScript_Ayumu_PostBattle_Text_1
# 1180 "data/maps/Route104/scripts.pory"
	releaseall
	end


Route104_EventScript_Cindy::
# 1185 "data/maps/Route104/scripts.pory"
	trainerbattle_single TRAINER_CINDY_1, Route104_Text_CindyIntro, Route104_Text_CindyDefeat, Route104_EventScript_CindyIsWillingToRematch
# 1186 "data/maps/Route104/scripts.pory"
	goto Route104_EventScriptCindyRematch
	return


Route104_EventScriptCindyRematch::
# 1190 "data/maps/Route104/scripts.pory"
	goto_if_set FLAG_TEMP_1, Route104_EventScriptCindyRematch_1
# 1193 "data/maps/Route104/scripts.pory"
	msgbox Route104_EventScriptCindyRematch_Text_0, MSGBOX_YESNO
# 1194 "data/maps/Route104/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Route104_EventScriptCindyRematch_4
# 1199 "data/maps/Route104/scripts.pory"
	msgbox Route104_EventScriptCindyRematch_Text_2
# 1200 "data/maps/Route104/scripts.pory"
	releaseall
	end

Route104_EventScriptCindyRematch_1:
# 1191 "data/maps/Route104/scripts.pory"
	goto Route104_EventScript_Cindy_NextTimeRoute
	return

Route104_EventScriptCindyRematch_4:
# 1195 "data/maps/Route104/scripts.pory"
	msgbox Route104_EventScriptCindyRematch_Text_1
# 1196 "data/maps/Route104/scripts.pory"
	trainerbattle_no_intro TRAINER_CINDY_1, Route104_Text_CindyDefeat
# 1197 "data/maps/Route104/scripts.pory"
	goto Route104_EventScript_CindyAfterRematch
	return


Route104_EventScript_Cindy_NextTimeRoute::
# 1207 "data/maps/Route104/scripts.pory"
	msgbox Route104_EventScript_Cindy_NextTimeRoute_Text_0
# 1208 "data/maps/Route104/scripts.pory"
	releaseall
	end


Route104_EventScript_CindyIsWillingToRematch::
# 1213 "data/maps/Route104/scripts.pory"
	setflag FLAG_TEMP_1
# 1214 "data/maps/Route104/scripts.pory"
	msgbox Route104_EventScript_CindyIsWillingToRematch_Text_0
# 1215 "data/maps/Route104/scripts.pory"
	goto Route104_EventScript_Cindy_NextTimeRoute
	return


Route104_EventScript_CindyAfterRematch::
# 1219 "data/maps/Route104/scripts.pory"
	setflag FLAG_TEMP_1
# 1220 "data/maps/Route104/scripts.pory"
	msgbox Route104_EventScript_CindyAfterRematch_Text_0
# 1221 "data/maps/Route104/scripts.pory"
	msgbox Route104_EventScript_CindyAfterRematch_Text_1
# 1222 "data/maps/Route104/scripts.pory"
	releaseall
	end


Route104_EventScript_Billy::
# 1227 "data/maps/Route104/scripts.pory"
	trainerbattle_single TRAINER_BILLY, Route104_Text_BillyIntro, Route104_Text_BillyDefeat, Route104_EventScript_BillyGift
# 1228 "data/maps/Route104/scripts.pory"
	msgbox Route104_Text_BillyPostBattle, MSGBOX_AUTOCLOSE
	end


Route104_EventScript_BillyGift::
# 1233 "data/maps/Route104/scripts.pory"
	msgbox Route104_EventScript_BillyGift_Text_0
# 1234 "data/maps/Route104/scripts.pory"
	giveitem ITEM_SERIOUS_MINT
# 1235 "data/maps/Route104/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Route104_EventScript_BillyGift_2
Route104_EventScript_BillyGift_1:
# 1238 "data/maps/Route104/scripts.pory"
	releaseall
	end

Route104_EventScript_BillyGift_2:
# 1236 "data/maps/Route104/scripts.pory"
	call Common_EventScript_ShowBagIsFull
	goto Route104_EventScript_BillyGift_1


Route104_EventScript_Boy2::
# 1243 "data/maps/Route104/scripts.pory"
	lock
# 1244 "data/maps/Route104/scripts.pory"
	faceplayer
# 1245 "data/maps/Route104/scripts.pory"
	goto_if_set FLAG_RECEIVED_TM_HELPING_HAND, Route104_EventScript_Boy2_2
# 1248 "data/maps/Route104/scripts.pory"
	msgbox Route104_EventScript_Boy2_Text_1
# 1249 "data/maps/Route104/scripts.pory"
	msgbox Route104_EventScript_Boy2_Text_2
# 1250 "data/maps/Route104/scripts.pory"
	goto_if_set FLAG_RESOURCE_MODE, Route104_EventScript_Boy2_6
# 1256 "data/maps/Route104/scripts.pory"
	giveItem ITEM_TM_HELPING_HAND
# 1257 "data/maps/Route104/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Route104_EventScript_Boy2_11
Route104_EventScript_Boy2_5:
# 1261 "data/maps/Route104/scripts.pory"
	msgbox Route104_EventScript_Boy2_Text_3
# 1262 "data/maps/Route104/scripts.pory"
	setflag FLAG_RECEIVED_TM_HELPING_HAND
Route104_EventScript_Boy2_1:
# 1264 "data/maps/Route104/scripts.pory"
	release
	end

Route104_EventScript_Boy2_2:
# 1246 "data/maps/Route104/scripts.pory"
	msgbox Route104_EventScript_Boy2_Text_0
	goto Route104_EventScript_Boy2_1

Route104_EventScript_Boy2_6:
# 1251 "data/maps/Route104/scripts.pory"
	giveitem ITEM_TM_HELPING_HAND, 6
# 1252 "data/maps/Route104/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Route104_EventScript_Boy2_9
	goto Route104_EventScript_Boy2_5

Route104_EventScript_Boy2_9:
# 1253 "data/maps/Route104/scripts.pory"
	call Common_EventScript_ShowBagIsFull
	goto Route104_EventScript_Boy2_5

Route104_EventScript_Boy2_11:
# 1258 "data/maps/Route104/scripts.pory"
	call Common_EventScript_ShowBagIsFull
	goto Route104_EventScript_Boy2_5


Route104_EventScript_Ayumu_Text_0:
# 1172 "data/maps/Route104/scripts.pory"
	.string "My darling Pokemon are simply\n"
	.string "irresistible.$"

Route104_EventScript_Ayumu_Text_1:
# 1172 "data/maps/Route104/scripts.pory"
	.string "What? Even their charm wasn't enough?$"

Route104_EventScript_Ayumu_Text_2:
# 1173 "data/maps/Route104/scripts.pory"
	.string "We'll continue to hone our cuteness!$"

Route104_EventScript_Ayumu_PostBattle_Text_0:
# 1178 "data/maps/Route104/scripts.pory"
	.string "Oh, we couldn’t win... but wasn’t their\n"
	.string "charm simply enchanting?$"

Route104_EventScript_Ayumu_PostBattle_Text_1:
# 1179 "data/maps/Route104/scripts.pory"
	.string "With Cute Charm on their side, moves\n"
	.string "like Charm and Fake Tears shine even\l"
	.string "brighter when used against the right\l"
	.string "foe!$"

Route104_EventScriptCindyRematch_Text_0:
# 1193 "data/maps/Route104/scripts.pory"
	.string "Hey, {PLAYER}, Would you like a\n"
	.string "rematch?$"

Route104_EventScriptCindyRematch_Text_1:
# 1195 "data/maps/Route104/scripts.pory"
	.string "Then let's get started!$"

Route104_EventScriptCindyRematch_Text_2:
# 1199 "data/maps/Route104/scripts.pory"
	.string "Aw, I was looking forward to a rematch...$"

Route104_EventScript_Cindy_NextTimeRoute_Text_0:
# 1207 "data/maps/Route104/scripts.pory"
	.string "The next time you come back to this\n"
	.string "route, if you feel like battling again,\l"
	.string "feel free to talk to me!$"

Route104_EventScript_CindyIsWillingToRematch_Text_0:
# 1214 "data/maps/Route104/scripts.pory"
	.string "My Pokemon are great at earning money\n"
	.string "from wild battles, but I wanted to prove\l"
	.string "we could win in real battles too...$"

Route104_EventScript_CindyAfterRematch_Text_0:
# 1220 "data/maps/Route104/scripts.pory"
	.string "Guess I still couldn't pull it off.$"

Route104_EventScript_CindyAfterRematch_Text_1:
# 1221 "data/maps/Route104/scripts.pory"
	.string "The next time you come back to this\n"
	.string "route, if you feel like battling again,\l"
	.string "I'll be down!$"

Route104_EventScript_BillyGift_Text_0:
# 1233 "data/maps/Route104/scripts.pory"
	.string "That was a nice battle! Here, you can\n"
	.string "have one of the mints that I've been\l"
	.string "giving to my Pokemon.$"

Route104_EventScript_Boy2_Text_0:
# 1246 "data/maps/Route104/scripts.pory"
	.string "It's always great to lend a Helping\n"
	.string "Hand!$"

Route104_EventScript_Boy2_Text_1:
# 1248 "data/maps/Route104/scripts.pory"
	.string "Hey there! A team works best when\n"
	.string "everyone helps each other out. That's\l"
	.string "especially true for Double Battles!$"

Route104_EventScript_Boy2_Text_2:
# 1249 "data/maps/Route104/scripts.pory"
	.string "Here, take this TM and give it a try!$"

Route104_EventScript_Boy2_Text_3:
# 1261 "data/maps/Route104/scripts.pory"
	.string "Helping Hand lets your Pokémon boost\n"
	.string "its ally's power. It's perfect for Double\l"
	.string "Battles.$"

Route104_Text_JimmyIntro::
# 1153 "data/maps/Route104/scripts.pory"
	.string "My Pokemon love messing with the sand!$"

Route104_Text_JimmyDefeat::
# 1157 "data/maps/Route104/scripts.pory"
	.string "Our Sand moves were no match!$"

Route104_Text_JimmyPostBattle::
# 1161 "data/maps/Route104/scripts.pory"
	.string "Sand is great to explore. Sometimes I\n"
	.string "find cool items on the ground.$"
