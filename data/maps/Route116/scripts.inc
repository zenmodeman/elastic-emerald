# 1 "data/maps/Route116/scripts.pory"

# 2 "data/maps/Route116/scripts.pory"

# 3 "data/maps/Route116/scripts.pory"
.set LOCALID_BRINEY, 11
# 4 "data/maps/Route116/scripts.pory"
.set LOCALID_WANDAS_BF_OUTSIDE, 21
# 5 "data/maps/Route116/scripts.pory"

# 6 "data/maps/Route116/scripts.pory"
Route116_MapScripts::
# 7 "data/maps/Route116/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Route116_OnTransition
# 8 "data/maps/Route116/scripts.pory"
	map_script MAP_SCRIPT_ON_LOAD, Route116_OnLoad
# 9 "data/maps/Route116/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route116_OnFrame
# 10 "data/maps/Route116/scripts.pory"
	.byte 0
# 11 "data/maps/Route116/scripts.pory"

# 12 "data/maps/Route116/scripts.pory"
Route116_OnTransition:
# 13 "data/maps/Route116/scripts.pory"
	call_if_set FLAG_RECOVERED_DEVON_GOODS, Route116_EventScript_SetWandasBoyfriendPos
# 14 "data/maps/Route116/scripts.pory"
	call_if_eq VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_HideMapNamePopup
# 15 "data/maps/Route116/scripts.pory"
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_116_NORTH, AbnormalWeather_StartGroudonWeather
# 16 "data/maps/Route116/scripts.pory"
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_116_SOUTH, AbnormalWeather_StartGroudonWeather
# 17 "data/maps/Route116/scripts.pory"
	end
# 18 "data/maps/Route116/scripts.pory"

# 19 "data/maps/Route116/scripts.pory"
Route116_EventScript_SetWandasBoyfriendPos::
# 20 "data/maps/Route116/scripts.pory"
	setobjectxyperm LOCALID_WANDAS_BF_OUTSIDE, 38, 10
# 21 "data/maps/Route116/scripts.pory"
	return
# 22 "data/maps/Route116/scripts.pory"

# 23 "data/maps/Route116/scripts.pory"
Route116_OnLoad:
# 24 "data/maps/Route116/scripts.pory"
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_116_NORTH, AbnormalWeather_EventScript_PlaceTilesRoute116North
# 25 "data/maps/Route116/scripts.pory"
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_116_SOUTH, AbnormalWeather_EventScript_PlaceTilesRoute116South
# 26 "data/maps/Route116/scripts.pory"
	end
# 27 "data/maps/Route116/scripts.pory"

# 28 "data/maps/Route116/scripts.pory"
Route116_OnFrame:
# 29 "data/maps/Route116/scripts.pory"
	map_script_2 VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_EndEventAndCleanup_1
# 30 "data/maps/Route116/scripts.pory"
	.2byte 0
# 31 "data/maps/Route116/scripts.pory"

# 32 "data/maps/Route116/scripts.pory"
Route116_EventScript_WandasBoyfriend::
# 33 "data/maps/Route116/scripts.pory"
	lock
# 34 "data/maps/Route116/scripts.pory"
	faceplayer
# 35 "data/maps/Route116/scripts.pory"
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, Route116_EventScript_BoyfriendGruntLeftTunnel
# 36 "data/maps/Route116/scripts.pory"
	goto_if_set FLAG_DEVON_GOODS_STOLEN, Route116_EventScript_BoyfriendGruntInTunnel
# 37 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_WantToDigTunnel, MSGBOX_DEFAULT
# 38 "data/maps/Route116/scripts.pory"
	release
# 39 "data/maps/Route116/scripts.pory"
	end
# 40 "data/maps/Route116/scripts.pory"

# 41 "data/maps/Route116/scripts.pory"
Route116_EventScript_BoyfriendGruntLeftTunnel::
# 42 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_GoonHightailedItOutOfTunnel, MSGBOX_DEFAULT
# 43 "data/maps/Route116/scripts.pory"
	release
# 44 "data/maps/Route116/scripts.pory"
	end
# 45 "data/maps/Route116/scripts.pory"

# 46 "data/maps/Route116/scripts.pory"
Route116_EventScript_BoyfriendGruntInTunnel::
# 47 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_DiggingTunnelWhenGoonOrderedMeOut, MSGBOX_DEFAULT
# 48 "data/maps/Route116/scripts.pory"
	release
# 49 "data/maps/Route116/scripts.pory"
	end
# 50 "data/maps/Route116/scripts.pory"

# 51 "data/maps/Route116/scripts.pory"
Route116_EventScript_DevonEmployee::
# 52 "data/maps/Route116/scripts.pory"
	lock
# 53 "data/maps/Route116/scripts.pory"
	faceplayer
# 54 "data/maps/Route116/scripts.pory"
	goto_if_set FLAG_MET_DEVON_EMPLOYEE, Route116_EventScript_TryGiveRepeatBallAgain
# 55 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_ThankYouTokenOfAppreciation, MSGBOX_DEFAULT
# 56 "data/maps/Route116/scripts.pory"
	goto Route116_EventScript_GiveRepeatBall
# 57 "data/maps/Route116/scripts.pory"
	end
# 58 "data/maps/Route116/scripts.pory"

# 59 "data/maps/Route116/scripts.pory"
Route116_EventScript_GiveRepeatBall::
# 60 "data/maps/Route116/scripts.pory"
	setflag FLAG_MET_DEVON_EMPLOYEE
# 61 "data/maps/Route116/scripts.pory"
	giveitem ITEM_REPEAT_BALL
# 62 "data/maps/Route116/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Route116_EventScript_NoRoomForRepeatBall
# 63 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_NewBallAvailableAtMart, MSGBOX_DEFAULT
# 64 "data/maps/Route116/scripts.pory"
	closemessage
# 65 "data/maps/Route116/scripts.pory"
	call_if_eq VAR_FACING, DIR_NORTH, Route116_EventScript_DevonEmployeeExit
# 66 "data/maps/Route116/scripts.pory"
	call_if_eq VAR_FACING, DIR_SOUTH, Route116_EventScript_DevonEmployeeExit
# 67 "data/maps/Route116/scripts.pory"
	call_if_eq VAR_FACING, DIR_WEST, Route116_EventScript_DevonEmployeeExit
# 68 "data/maps/Route116/scripts.pory"
	call_if_eq VAR_FACING, DIR_EAST, Route116_EventScript_DevonEmployeeExitEast
# 69 "data/maps/Route116/scripts.pory"
	removeobject VAR_LAST_TALKED
# 70 "data/maps/Route116/scripts.pory"
	clearflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_EMPLOYEE
# 71 "data/maps/Route116/scripts.pory"
	setflag FLAG_RECEIVED_REPEAT_BALL
# 72 "data/maps/Route116/scripts.pory"
	release
# 73 "data/maps/Route116/scripts.pory"
	end
# 74 "data/maps/Route116/scripts.pory"

# 75 "data/maps/Route116/scripts.pory"
Route116_EventScript_DevonEmployeeExit::
# 76 "data/maps/Route116/scripts.pory"
	applymovement VAR_LAST_TALKED, Route116_Movement_DevonEmployeeExit
# 77 "data/maps/Route116/scripts.pory"
	waitmovement 0
# 78 "data/maps/Route116/scripts.pory"
	return
# 79 "data/maps/Route116/scripts.pory"

# 80 "data/maps/Route116/scripts.pory"
Route116_EventScript_DevonEmployeeExitEast::
# 81 "data/maps/Route116/scripts.pory"
	applymovement VAR_LAST_TALKED, Route116_Movement_DevonEmployeeExitEast
# 82 "data/maps/Route116/scripts.pory"
	waitmovement 0
# 83 "data/maps/Route116/scripts.pory"
	return
# 84 "data/maps/Route116/scripts.pory"

# 85 "data/maps/Route116/scripts.pory"
Route116_EventScript_TryGiveRepeatBallAgain::
# 86 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_TokenOfAppreciation, MSGBOX_DEFAULT
# 87 "data/maps/Route116/scripts.pory"
	goto Route116_EventScript_GiveRepeatBall
# 88 "data/maps/Route116/scripts.pory"
	end
# 89 "data/maps/Route116/scripts.pory"

# 90 "data/maps/Route116/scripts.pory"
Route116_EventScript_NoRoomForRepeatBall::
# 91 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_BagIsJamPacked, MSGBOX_DEFAULT
# 92 "data/maps/Route116/scripts.pory"
	release
# 93 "data/maps/Route116/scripts.pory"
	end
# 94 "data/maps/Route116/scripts.pory"

# 95 "data/maps/Route116/scripts.pory"
Route116_Movement_DevonEmployeeExit:
# 96 "data/maps/Route116/scripts.pory"
	walk_left
# 97 "data/maps/Route116/scripts.pory"
	walk_left
# 98 "data/maps/Route116/scripts.pory"
	walk_left
# 99 "data/maps/Route116/scripts.pory"
	walk_left
# 100 "data/maps/Route116/scripts.pory"
	walk_left
# 101 "data/maps/Route116/scripts.pory"
	walk_left
# 102 "data/maps/Route116/scripts.pory"
	walk_left
# 103 "data/maps/Route116/scripts.pory"
	walk_left
# 104 "data/maps/Route116/scripts.pory"
	step_end
# 105 "data/maps/Route116/scripts.pory"

# 106 "data/maps/Route116/scripts.pory"
Route116_Movement_DevonEmployeeExitEast:
# 107 "data/maps/Route116/scripts.pory"
	walk_down
# 108 "data/maps/Route116/scripts.pory"
	walk_left
# 109 "data/maps/Route116/scripts.pory"
	walk_left
# 110 "data/maps/Route116/scripts.pory"
	walk_left
# 111 "data/maps/Route116/scripts.pory"
	walk_left
# 112 "data/maps/Route116/scripts.pory"
	walk_left
# 113 "data/maps/Route116/scripts.pory"
	walk_left
# 114 "data/maps/Route116/scripts.pory"
	walk_left
# 115 "data/maps/Route116/scripts.pory"
	walk_left
# 116 "data/maps/Route116/scripts.pory"
	walk_left
# 117 "data/maps/Route116/scripts.pory"
	step_end
# 118 "data/maps/Route116/scripts.pory"

# 119 "data/maps/Route116/scripts.pory"
Route116_EventScript_RouteSignRustboro::
# 120 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_RouteSignRustboro, MSGBOX_SIGN
# 121 "data/maps/Route116/scripts.pory"
	end
# 122 "data/maps/Route116/scripts.pory"

# 123 "data/maps/Route116/scripts.pory"
Route116_EventScript_RusturfTunnelSign::
# 124 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_RusturfTunnelSign, MSGBOX_SIGN
# 125 "data/maps/Route116/scripts.pory"
	end
# 126 "data/maps/Route116/scripts.pory"

# 127 "data/maps/Route116/scripts.pory"
Route116_EventScript_TunnelersRestHouseSign::
# 128 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_TunnelersRestHouse, MSGBOX_SIGN
# 129 "data/maps/Route116/scripts.pory"
	end
# 130 "data/maps/Route116/scripts.pory"

# 131 "data/maps/Route116/scripts.pory"
Route116_EventScript_TrainerTipsBToStopEvolution::
# 132 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_TrainerTipsBToStopEvolution, MSGBOX_SIGN
# 133 "data/maps/Route116/scripts.pory"
	end
# 134 "data/maps/Route116/scripts.pory"

# 135 "data/maps/Route116/scripts.pory"
Route116_EventScript_TrainerTipsBagHasPockets::
# 136 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_TrainerTipsBagHasPockets, MSGBOX_SIGN
# 137 "data/maps/Route116/scripts.pory"
	end
# 138 "data/maps/Route116/scripts.pory"

# 139 "data/maps/Route116/scripts.pory"
Route116_EventScript_Briney::
# 140 "data/maps/Route116/scripts.pory"
	lock
# 141 "data/maps/Route116/scripts.pory"
	faceplayer
# 142 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_ScoundrelMadeOffWithPeeko, MSGBOX_DEFAULT
# 143 "data/maps/Route116/scripts.pory"
	setvar VAR_ROUTE116_STATE, 2
# 144 "data/maps/Route116/scripts.pory"
	release
# 145 "data/maps/Route116/scripts.pory"
	end
# 146 "data/maps/Route116/scripts.pory"

# 147 "data/maps/Route116/scripts.pory"
Route116_EventScript_BrineyTrigger::
# 148 "data/maps/Route116/scripts.pory"
	lockall
# 149 "data/maps/Route116/scripts.pory"
	applymovement LOCALID_BRINEY, Common_Movement_WalkInPlaceFasterRight
# 150 "data/maps/Route116/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
# 151 "data/maps/Route116/scripts.pory"
	waitmovement 0
# 152 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_ScoundrelMadeOffWithPeeko, MSGBOX_DEFAULT
# 153 "data/maps/Route116/scripts.pory"
	setvar VAR_ROUTE116_STATE, 2
# 154 "data/maps/Route116/scripts.pory"
	releaseall
# 155 "data/maps/Route116/scripts.pory"
	end
# 156 "data/maps/Route116/scripts.pory"

# 157 "data/maps/Route116/scripts.pory"
Route116_EventScript_GlassesMan::
# 158 "data/maps/Route116/scripts.pory"
	lock
# 159 "data/maps/Route116/scripts.pory"
	faceplayer
# 160 "data/maps/Route116/scripts.pory"
	checkitem ITEM_BLACK_GLASSES
# 161 "data/maps/Route116/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Route116_EventScript_PlayerHasGlasses
# 162 "data/maps/Route116/scripts.pory"
	specialvar VAR_RESULT, FoundBlackGlasses
# 163 "data/maps/Route116/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Route116_EventScript_FoundGlassesNotOnPlayer
# 164 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_CanYouHelpMeFindGlasses, MSGBOX_DEFAULT
# 165 "data/maps/Route116/scripts.pory"
	release
# 166 "data/maps/Route116/scripts.pory"
	end
# 167 "data/maps/Route116/scripts.pory"

# 168 "data/maps/Route116/scripts.pory"
Route116_EventScript_FoundGlassesNotOnPlayer::
# 169 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_CantFindGlassesNotHere, MSGBOX_DEFAULT
# 170 "data/maps/Route116/scripts.pory"
	closemessage
# 171 "data/maps/Route116/scripts.pory"
	goto Route116_EventScript_GlassesManExit
# 172 "data/maps/Route116/scripts.pory"
	end
# 173 "data/maps/Route116/scripts.pory"

# 174 "data/maps/Route116/scripts.pory"
Route116_EventScript_PlayerHasGlasses::
# 175 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_CanYouHelpMeFindGlasses, MSGBOX_DEFAULT
# 176 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_MayISeeThoseGlasses, MSGBOX_DEFAULT
# 177 "data/maps/Route116/scripts.pory"
	specialvar VAR_RESULT, FoundBlackGlasses
# 178 "data/maps/Route116/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Route116_EventScript_FoundGlassesOnPlayer
# 179 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_NotWhatImLookingFor, MSGBOX_DEFAULT
# 180 "data/maps/Route116/scripts.pory"
	release
# 181 "data/maps/Route116/scripts.pory"
	end
# 182 "data/maps/Route116/scripts.pory"

# 183 "data/maps/Route116/scripts.pory"
Route116_EventScript_FoundGlassesOnPlayer::
# 184 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_NotWhatImLookingForMaybeTheyArentHere, MSGBOX_DEFAULT
# 185 "data/maps/Route116/scripts.pory"
	closemessage
# 186 "data/maps/Route116/scripts.pory"
	goto Route116_EventScript_GlassesManExit
# 187 "data/maps/Route116/scripts.pory"
	end
# 188 "data/maps/Route116/scripts.pory"

# 189 "data/maps/Route116/scripts.pory"
Route116_EventScript_GlassesManExit::
# 190 "data/maps/Route116/scripts.pory"
	delay 20
# 191 "data/maps/Route116/scripts.pory"
	call_if_eq VAR_FACING, DIR_NORTH, Route116_EventScript_GlassesManExitNormal
# 192 "data/maps/Route116/scripts.pory"
	call_if_eq VAR_FACING, DIR_SOUTH, Route116_EventScript_GlassesManExitNormal
# 193 "data/maps/Route116/scripts.pory"
	call_if_eq VAR_FACING, DIR_WEST, Route116_EventScript_GlassesManExitNormal
# 194 "data/maps/Route116/scripts.pory"
	call_if_eq VAR_FACING, DIR_EAST, Route116_EventScript_GlassesManExitEast
# 195 "data/maps/Route116/scripts.pory"
	removeobject VAR_LAST_TALKED
# 196 "data/maps/Route116/scripts.pory"
	release
# 197 "data/maps/Route116/scripts.pory"
	end
# 198 "data/maps/Route116/scripts.pory"

# 199 "data/maps/Route116/scripts.pory"
Route116_EventScript_GlassesManExitNormal::
# 200 "data/maps/Route116/scripts.pory"
	applymovement VAR_LAST_TALKED, Route116_Movement_GlassesManExit
# 201 "data/maps/Route116/scripts.pory"
	waitmovement 0
# 202 "data/maps/Route116/scripts.pory"
	return
# 203 "data/maps/Route116/scripts.pory"

# 204 "data/maps/Route116/scripts.pory"
Route116_EventScript_GlassesManExitEast::
# 205 "data/maps/Route116/scripts.pory"
	applymovement VAR_LAST_TALKED, Route116_Movement_GlassesManExitEast
# 206 "data/maps/Route116/scripts.pory"
	waitmovement 0
# 207 "data/maps/Route116/scripts.pory"
	return
# 208 "data/maps/Route116/scripts.pory"

# 209 "data/maps/Route116/scripts.pory"
Route116_Movement_GlassesManExit:
# 210 "data/maps/Route116/scripts.pory"
	walk_left
# 211 "data/maps/Route116/scripts.pory"
	walk_left
# 212 "data/maps/Route116/scripts.pory"
	walk_left
# 213 "data/maps/Route116/scripts.pory"
	walk_left
# 214 "data/maps/Route116/scripts.pory"
	walk_left
# 215 "data/maps/Route116/scripts.pory"
	walk_left
# 216 "data/maps/Route116/scripts.pory"
	walk_left
# 217 "data/maps/Route116/scripts.pory"
	walk_left
# 218 "data/maps/Route116/scripts.pory"
	walk_left
# 219 "data/maps/Route116/scripts.pory"
	step_end
# 220 "data/maps/Route116/scripts.pory"

# 221 "data/maps/Route116/scripts.pory"
Route116_Movement_GlassesManExitEast:
# 222 "data/maps/Route116/scripts.pory"
	walk_up
# 223 "data/maps/Route116/scripts.pory"
	walk_left
# 224 "data/maps/Route116/scripts.pory"
	walk_left
# 225 "data/maps/Route116/scripts.pory"
	walk_left
# 226 "data/maps/Route116/scripts.pory"
	walk_left
# 227 "data/maps/Route116/scripts.pory"
	walk_left
# 228 "data/maps/Route116/scripts.pory"
	walk_left
# 229 "data/maps/Route116/scripts.pory"
	walk_left
# 230 "data/maps/Route116/scripts.pory"
	walk_left
# 231 "data/maps/Route116/scripts.pory"
	walk_left
# 232 "data/maps/Route116/scripts.pory"
	step_end
# 233 "data/maps/Route116/scripts.pory"

# 234 "data/maps/Route116/scripts.pory"
Route116_EventScript_Joey::
# 235 "data/maps/Route116/scripts.pory"
	trainerbattle_single TRAINER_JOEY, Route116_Text_JoeyIntro, Route116_Text_JoeyDefeat
# 236 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_JoeyPostBattle, MSGBOX_AUTOCLOSE
# 237 "data/maps/Route116/scripts.pory"
	end
# 238 "data/maps/Route116/scripts.pory"

# 239 "data/maps/Route116/scripts.pory"
Route116_EventScript_Jose::
# 240 "data/maps/Route116/scripts.pory"
	trainerbattle_single TRAINER_JOSE, Route116_Text_JoseIntro, Route116_Text_JoseDefeat
# 241 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_JosePostBattle, MSGBOX_AUTOCLOSE
# 242 "data/maps/Route116/scripts.pory"
	end
# 243 "data/maps/Route116/scripts.pory"

# 244 "data/maps/Route116/scripts.pory"
Route116_EventScript_Jerry::
# 245 "data/maps/Route116/scripts.pory"
	trainerbattle_single TRAINER_JERRY_1, Route116_Text_JerryIntro, Route116_Text_JerryDefeat, Route116_EventScript_TryRegisterJerryAfterBattle
# 246 "data/maps/Route116/scripts.pory"
	specialvar VAR_RESULT, ShouldTryRematchBattle
# 247 "data/maps/Route116/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Route116_EventScript_RematchJerry
# 248 "data/maps/Route116/scripts.pory"
	setvar VAR_0x8004, TRAINER_JERRY_1
# 249 "data/maps/Route116/scripts.pory"
	specialvar VAR_RESULT, IsTrainerRegistered
# 250 "data/maps/Route116/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Route116_EventScript_TryRegisterJerry
# 251 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_JerryPostBattle, MSGBOX_DEFAULT
# 252 "data/maps/Route116/scripts.pory"
	release
# 253 "data/maps/Route116/scripts.pory"
	end
# 254 "data/maps/Route116/scripts.pory"

# 255 "data/maps/Route116/scripts.pory"
Route116_EventScript_TryRegisterJerryAfterBattle::
# 256 "data/maps/Route116/scripts.pory"
	goto_if_set FLAG_HAS_MATCH_CALL, Route116_EventScript_RegisterJerryAfterBattle
# 257 "data/maps/Route116/scripts.pory"
	release
# 258 "data/maps/Route116/scripts.pory"
	end
# 259 "data/maps/Route116/scripts.pory"

# 260 "data/maps/Route116/scripts.pory"
Route116_EventScript_RegisterJerryAfterBattle::
# 261 "data/maps/Route116/scripts.pory"
	special PlayerFaceTrainerAfterBattle
# 262 "data/maps/Route116/scripts.pory"
	waitmovement 0
# 263 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_JerryRegister2, MSGBOX_DEFAULT
# 264 "data/maps/Route116/scripts.pory"
	register_matchcall TRAINER_JERRY_1
# 265 "data/maps/Route116/scripts.pory"
	release
# 266 "data/maps/Route116/scripts.pory"
	end
# 267 "data/maps/Route116/scripts.pory"

# 268 "data/maps/Route116/scripts.pory"
Route116_EventScript_TryRegisterJerry::
# 269 "data/maps/Route116/scripts.pory"
	goto_if_set FLAG_HAS_MATCH_CALL, Route116_EventScript_RegisterJerry
# 270 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_JerryPostBattle, MSGBOX_DEFAULT
# 271 "data/maps/Route116/scripts.pory"
	release
# 272 "data/maps/Route116/scripts.pory"
	end
# 273 "data/maps/Route116/scripts.pory"

# 274 "data/maps/Route116/scripts.pory"
Route116_EventScript_RegisterJerry::
# 275 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_JerryRegister1, MSGBOX_DEFAULT
# 276 "data/maps/Route116/scripts.pory"
	register_matchcall TRAINER_JERRY_1
# 277 "data/maps/Route116/scripts.pory"
	release
# 278 "data/maps/Route116/scripts.pory"
	end
# 279 "data/maps/Route116/scripts.pory"

# 280 "data/maps/Route116/scripts.pory"
Route116_EventScript_RematchJerry::
# 281 "data/maps/Route116/scripts.pory"
	trainerbattle_rematch TRAINER_JERRY_1, Route116_Text_JerryRematchIntro, Route116_Text_JerryRematchDefeat
# 282 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_JerryPostRematch, MSGBOX_AUTOCLOSE
# 283 "data/maps/Route116/scripts.pory"
	end
# 284 "data/maps/Route116/scripts.pory"

# 285 "data/maps/Route116/scripts.pory"
Route116_EventScript_Clark::
# 286 "data/maps/Route116/scripts.pory"
	trainerbattle_single TRAINER_CLARK, Route116_Text_ClarkIntro, Route116_Text_ClarkDefeat
# 287 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_ClarkPostBattle, MSGBOX_AUTOCLOSE
# 288 "data/maps/Route116/scripts.pory"
	end
# 289 "data/maps/Route116/scripts.pory"

# 290 "data/maps/Route116/scripts.pory"
Route116_EventScript_Janice::
# 291 "data/maps/Route116/scripts.pory"
	trainerbattle_single TRAINER_JANICE, Route116_Text_JaniceIntro, Route116_Text_JaniceDefeat
# 292 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_JanicePostBattle, MSGBOX_AUTOCLOSE
# 293 "data/maps/Route116/scripts.pory"
	end
# 294 "data/maps/Route116/scripts.pory"

# 295 "data/maps/Route116/scripts.pory"
Route116_EventScript_Karen::
# 296 "data/maps/Route116/scripts.pory"
	trainerbattle_single TRAINER_KAREN_1, Route116_Text_KarenIntro, Route116_Text_KarenDefeat, Route116_EventScript_TryRegisterKarenAfterBattle
# 297 "data/maps/Route116/scripts.pory"
	specialvar VAR_RESULT, ShouldTryRematchBattle
# 298 "data/maps/Route116/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Route116_EventScript_RematchKaren
# 299 "data/maps/Route116/scripts.pory"
	setvar VAR_0x8004, TRAINER_KAREN_1
# 300 "data/maps/Route116/scripts.pory"
	specialvar VAR_RESULT, IsTrainerRegistered
# 301 "data/maps/Route116/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Route116_EventScript_TryRegisterKaren
# 302 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_KarenPostBattle, MSGBOX_DEFAULT
# 303 "data/maps/Route116/scripts.pory"
	release
# 304 "data/maps/Route116/scripts.pory"
	end
# 305 "data/maps/Route116/scripts.pory"

# 306 "data/maps/Route116/scripts.pory"
Route116_EventScript_TryRegisterKarenAfterBattle::
# 307 "data/maps/Route116/scripts.pory"
	goto_if_set FLAG_HAS_MATCH_CALL, Route116_EventScript_RegisterKarenAfterBattle
# 308 "data/maps/Route116/scripts.pory"
	release
# 309 "data/maps/Route116/scripts.pory"
	end
# 310 "data/maps/Route116/scripts.pory"

# 311 "data/maps/Route116/scripts.pory"
Route116_EventScript_RegisterKarenAfterBattle::
# 312 "data/maps/Route116/scripts.pory"
	special PlayerFaceTrainerAfterBattle
# 313 "data/maps/Route116/scripts.pory"
	waitmovement 0
# 314 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_KarenRegister2, MSGBOX_DEFAULT
# 315 "data/maps/Route116/scripts.pory"
	register_matchcall TRAINER_KAREN_1
# 316 "data/maps/Route116/scripts.pory"
	release
# 317 "data/maps/Route116/scripts.pory"
	end
# 318 "data/maps/Route116/scripts.pory"

# 319 "data/maps/Route116/scripts.pory"
Route116_EventScript_TryRegisterKaren::
# 320 "data/maps/Route116/scripts.pory"
	goto_if_set FLAG_HAS_MATCH_CALL, Route116_EventScript_RegisterKaren
# 321 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_KarenPostBattle, MSGBOX_DEFAULT
# 322 "data/maps/Route116/scripts.pory"
	release
# 323 "data/maps/Route116/scripts.pory"
	end
# 324 "data/maps/Route116/scripts.pory"

# 325 "data/maps/Route116/scripts.pory"
Route116_EventScript_RegisterKaren::
# 326 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_KarenRegister1, MSGBOX_DEFAULT
# 327 "data/maps/Route116/scripts.pory"
	register_matchcall TRAINER_KAREN_1
# 328 "data/maps/Route116/scripts.pory"
	release
# 329 "data/maps/Route116/scripts.pory"
	end
# 330 "data/maps/Route116/scripts.pory"

# 331 "data/maps/Route116/scripts.pory"
Route116_EventScript_RematchKaren::
# 332 "data/maps/Route116/scripts.pory"
	trainerbattle_rematch TRAINER_KAREN_1, Route116_Text_KarenRematchIntro, Route116_Text_KarenRematchDefeat
# 333 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_KarenPostRematch, MSGBOX_AUTOCLOSE
# 334 "data/maps/Route116/scripts.pory"
	end
# 335 "data/maps/Route116/scripts.pory"

# 336 "data/maps/Route116/scripts.pory"
Route116_EventScript_Sarah::
# 337 "data/maps/Route116/scripts.pory"
	trainerbattle_single TRAINER_SARAH, Route116_Text_SarahIntro, Route116_Text_SarahDefeat
# 338 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_SarahPostBattle, MSGBOX_AUTOCLOSE
# 339 "data/maps/Route116/scripts.pory"
	end
# 340 "data/maps/Route116/scripts.pory"

# 341 "data/maps/Route116/scripts.pory"
Route116_EventScript_Dawson::
# 342 "data/maps/Route116/scripts.pory"
	trainerbattle_single TRAINER_DAWSON, Route116_Text_DawsonIntro, Route116_Text_DawsonDefeat
# 343 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_DawsonPostBattle, MSGBOX_AUTOCLOSE
# 344 "data/maps/Route116/scripts.pory"
	end
# 345 "data/maps/Route116/scripts.pory"

# 346 "data/maps/Route116/scripts.pory"
Route116_EventScript_Devan::
# 347 "data/maps/Route116/scripts.pory"
	trainerbattle_single TRAINER_DEVAN, Route116_Text_DevanIntro, Route116_Text_DevanDefeat
# 348 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_DevanPostBattle, MSGBOX_AUTOCLOSE
# 349 "data/maps/Route116/scripts.pory"
	end
# 350 "data/maps/Route116/scripts.pory"

# 351 "data/maps/Route116/scripts.pory"
Route116_EventScript_Johnson::
# 352 "data/maps/Route116/scripts.pory"
	trainerbattle_single TRAINER_JOHNSON, Route116_Text_JohnsonIntro, Route116_Text_JohnsonDefeat
# 353 "data/maps/Route116/scripts.pory"
	msgbox Route116_Text_JohnsonPostBattle, MSGBOX_AUTOCLOSE
# 354 "data/maps/Route116/scripts.pory"
	end
# 355 "data/maps/Route116/scripts.pory"

# 356 "data/maps/Route116/scripts.pory"
Route116_Text_ScoundrelMadeOffWithPeeko:
# 357 "data/maps/Route116/scripts.pory"
	.string "Ohhh, what am I to do?\p"
# 358 "data/maps/Route116/scripts.pory"
	.string "We were on our walk, PEEKO and I, when\n"
# 359 "data/maps/Route116/scripts.pory"
	.string "we were jumped by an odd thug…\p"
# 360 "data/maps/Route116/scripts.pory"
	.string "The scoundrel made off with my\n"
# 361 "data/maps/Route116/scripts.pory"
	.string "darling PEEKO!\p"
# 362 "data/maps/Route116/scripts.pory"
	.string "Wrrrooooooaaaar! PEEKO!$"
# 363 "data/maps/Route116/scripts.pory"

# 364 "data/maps/Route116/scripts.pory"
Route116_Text_WantToDigTunnel:
# 365 "data/maps/Route116/scripts.pory"
	.string "Nnn… Roar!\p"
# 366 "data/maps/Route116/scripts.pory"
	.string "I want to dig that tunnel!$"
# 367 "data/maps/Route116/scripts.pory"

# 368 "data/maps/Route116/scripts.pory"
Route116_Text_DiggingTunnelWhenGoonOrderedMeOut:
# 369 "data/maps/Route116/scripts.pory"
	.string "Nnn… Roar!\n"
# 370 "data/maps/Route116/scripts.pory"
	.string "What's going on?\p"
# 371 "data/maps/Route116/scripts.pory"
	.string "I was digging the tunnel without any\n"
# 372 "data/maps/Route116/scripts.pory"
	.string "tools when some goon ordered me out!\p"
# 373 "data/maps/Route116/scripts.pory"
	.string "That tunnel's filled with POKéMON\n"
# 374 "data/maps/Route116/scripts.pory"
	.string "that react badly to loud noises.\l"
# 375 "data/maps/Route116/scripts.pory"
	.string "They could cause an uproar.\p"
# 376 "data/maps/Route116/scripts.pory"
	.string "That's why we stopped using heavy\n"
# 377 "data/maps/Route116/scripts.pory"
	.string "equipment for tunneling…\p"
# 378 "data/maps/Route116/scripts.pory"
	.string "I'm worried that the goon will do\n"
# 379 "data/maps/Route116/scripts.pory"
	.string "something stupid and startle the\l"
# 380 "data/maps/Route116/scripts.pory"
	.string "POKéMON into an uproar.$"
# 381 "data/maps/Route116/scripts.pory"

# 382 "data/maps/Route116/scripts.pory"
Route116_Text_GoonHightailedItOutOfTunnel:
# 383 "data/maps/Route116/scripts.pory"
	.string "Nnn… Roar!\p"
# 384 "data/maps/Route116/scripts.pory"
	.string "That goofy goon hightailed it out of\n"
# 385 "data/maps/Route116/scripts.pory"
	.string "the tunnel! I can go back to digging!$"
# 386 "data/maps/Route116/scripts.pory"

# 387 "data/maps/Route116/scripts.pory"
Route116_Text_ThankYouTokenOfAppreciation:
# 388 "data/maps/Route116/scripts.pory"
	.string "Oh! It's you!\p"
# 389 "data/maps/Route116/scripts.pory"
	.string "You're that person who not only helped\n"
# 390 "data/maps/Route116/scripts.pory"
	.string "me in PETALBURG WOODS, but also got\l"
# 391 "data/maps/Route116/scripts.pory"
	.string "back my stolen package and then even\l"
# 392 "data/maps/Route116/scripts.pory"
	.string "graciously delivered it to SLATEPORT!\p"
# 393 "data/maps/Route116/scripts.pory"
	.string "CAPT. STERN informed us that the\n"
# 394 "data/maps/Route116/scripts.pory"
	.string "package arrived, too!\p"
# 395 "data/maps/Route116/scripts.pory"
	.string "I thank you very, very much!\p"
# 396 "data/maps/Route116/scripts.pory"
	.string "Why, if I were a rain cloud, I would\n"
# 397 "data/maps/Route116/scripts.pory"
	.string "shower you with gratitude and hail\l"
# 398 "data/maps/Route116/scripts.pory"
	.string "you as a hero!\p"
# 399 "data/maps/Route116/scripts.pory"
	.string "For you, the most wonderful TRAINER,\n"
# 400 "data/maps/Route116/scripts.pory"
	.string "I bear good news!\p"
# 401 "data/maps/Route116/scripts.pory"
	.string "Recently, our company developed\n"
# 402 "data/maps/Route116/scripts.pory"
	.string "a new kind of POKé BALL.\p"
# 403 "data/maps/Route116/scripts.pory"
	.string "As a token of our appreciation, this\n"
# 404 "data/maps/Route116/scripts.pory"
	.string "is our gift to our wonderful TRAINER!$"
# 405 "data/maps/Route116/scripts.pory"

# 406 "data/maps/Route116/scripts.pory"
Route116_Text_NewBallAvailableAtMart:
# 407 "data/maps/Route116/scripts.pory"
	.string "Our new POKé BALL will be available\n"
# 408 "data/maps/Route116/scripts.pory"
	.string "at the POKéMON MART in RUSTBORO.\p"
# 409 "data/maps/Route116/scripts.pory"
	.string "Please do try it out!\n"
# 410 "data/maps/Route116/scripts.pory"
	.string "Thank you and bye-bye!$"
# 411 "data/maps/Route116/scripts.pory"

# 412 "data/maps/Route116/scripts.pory"
Route116_Text_BagIsJamPacked:
# 413 "data/maps/Route116/scripts.pory"
	.string "Your BAG is jam-packed.\n"
# 414 "data/maps/Route116/scripts.pory"
	.string "I can't give you this REPEAT BALL.$"
# 415 "data/maps/Route116/scripts.pory"

# 416 "data/maps/Route116/scripts.pory"
Route116_Text_TokenOfAppreciation:
# 417 "data/maps/Route116/scripts.pory"
	.string "As a token of our appreciation for\n"
# 418 "data/maps/Route116/scripts.pory"
	.string "your delivering our package, I have\l"
# 419 "data/maps/Route116/scripts.pory"
	.string "a gift of a new kind of POKé BALL\l"
# 420 "data/maps/Route116/scripts.pory"
	.string "for our most wonderful TRAINER!$"
# 421 "data/maps/Route116/scripts.pory"

# 422 "data/maps/Route116/scripts.pory"
Route116_Text_CanYouHelpMeFindGlasses:
# 423 "data/maps/Route116/scripts.pory"
	.string "I dropped my glasses…\n"
# 424 "data/maps/Route116/scripts.pory"
	.string "Can you help me find them?$"
# 425 "data/maps/Route116/scripts.pory"

# 426 "data/maps/Route116/scripts.pory"
Route116_Text_MayISeeThoseGlasses:
# 427 "data/maps/Route116/scripts.pory"
	.string "Those glasses!\n"
# 428 "data/maps/Route116/scripts.pory"
	.string "May I see them for a second?$"
# 429 "data/maps/Route116/scripts.pory"

# 430 "data/maps/Route116/scripts.pory"
Route116_Text_NotWhatImLookingForMaybeTheyArentHere:
# 431 "data/maps/Route116/scripts.pory"
	.string "Hmm…\n"
# 432 "data/maps/Route116/scripts.pory"
	.string "These are BLACKGLASSES.\l"
# 433 "data/maps/Route116/scripts.pory"
	.string "They're not what I'm looking for…\p"
# 434 "data/maps/Route116/scripts.pory"
	.string "Maybe my glasses aren't around\n"
# 435 "data/maps/Route116/scripts.pory"
	.string "here…$"
# 436 "data/maps/Route116/scripts.pory"

# 437 "data/maps/Route116/scripts.pory"
Route116_Text_CantFindGlassesNotHere:
# 438 "data/maps/Route116/scripts.pory"
	.string "Hmm…\n"
# 439 "data/maps/Route116/scripts.pory"
	.string "I can't find my glasses anywhere…\l"
# 440 "data/maps/Route116/scripts.pory"
	.string "Maybe they're not around here…$"
# 441 "data/maps/Route116/scripts.pory"

# 442 "data/maps/Route116/scripts.pory"
Route116_Text_NotWhatImLookingFor:
# 443 "data/maps/Route116/scripts.pory"
	.string "Hmm…\n"
# 444 "data/maps/Route116/scripts.pory"
	.string "These are BLACKGLASSES.\l"
# 445 "data/maps/Route116/scripts.pory"
	.string "They're not what I'm looking for…$"
# 446 "data/maps/Route116/scripts.pory"

# 447 "data/maps/Route116/scripts.pory"
Route116_Text_RouteSignRustboro:
# 448 "data/maps/Route116/scripts.pory"
	.string "ROUTE 116\n"
# 449 "data/maps/Route116/scripts.pory"
	.string "{LEFT_ARROW} RUSTBORO CITY$"
# 450 "data/maps/Route116/scripts.pory"

# 451 "data/maps/Route116/scripts.pory"
Route116_Text_RusturfTunnelSign:
# 452 "data/maps/Route116/scripts.pory"
	.string "RUSTURF TUNNEL\n"
# 453 "data/maps/Route116/scripts.pory"
	.string "“Linking RUSTBORO and VERDANTURF\p"
# 454 "data/maps/Route116/scripts.pory"
	.string "“The tunnel project has been\n"
# 455 "data/maps/Route116/scripts.pory"
	.string "canceled.”$"
# 456 "data/maps/Route116/scripts.pory"

# 457 "data/maps/Route116/scripts.pory"
Route116_Text_TunnelersRestHouse:
# 458 "data/maps/Route116/scripts.pory"
	.string "TUNNELER'S REST HOUSE$"
# 459 "data/maps/Route116/scripts.pory"

# 460 "data/maps/Route116/scripts.pory"
Route116_Text_TrainerTipsBToStopEvolution:
# 461 "data/maps/Route116/scripts.pory"
	.string "TRAINER TIPS\p"
# 462 "data/maps/Route116/scripts.pory"
	.string "If you want to stop a POKéMON from\n"
# 463 "data/maps/Route116/scripts.pory"
	.string "evolving, press the B Button while it\l"
# 464 "data/maps/Route116/scripts.pory"
	.string "is trying to evolve.\l"
# 465 "data/maps/Route116/scripts.pory"
	.string "The startled POKéMON will stop.\p"
# 466 "data/maps/Route116/scripts.pory"
	.string "This is called an evolution cancel.$"
# 467 "data/maps/Route116/scripts.pory"

# 468 "data/maps/Route116/scripts.pory"
Route116_Text_TrainerTipsBagHasPockets:
# 469 "data/maps/Route116/scripts.pory"
	.string "TRAINER TIPS\p"
# 470 "data/maps/Route116/scripts.pory"
	.string "Your BAG has several POCKETS.\p"
# 471 "data/maps/Route116/scripts.pory"
	.string "Items you obtain are automatically\n"
# 472 "data/maps/Route116/scripts.pory"
	.string "placed in the appropriate POCKETS.\p"
# 473 "data/maps/Route116/scripts.pory"
	.string "No TRAINER can afford to be without\n"
# 474 "data/maps/Route116/scripts.pory"
	.string "a BAG of their own.$"

Elias_Beaten::
# 479 "data/maps/Route116/scripts.pory"
	msgbox Elias_Beaten_Text_0
# 480 "data/maps/Route116/scripts.pory"
	releaseall
	return


Route116_EventScript_Elias::
# 484 "data/maps/Route116/scripts.pory"
	lockall
# 485 "data/maps/Route116/scripts.pory"
	faceplayer
# 486 "data/maps/Route116/scripts.pory"
	goto_if_set TRAINER_FLAGS_START + TRAINER_ELIAS, Route116_EventScript_Elias_2
Route116_EventScript_Elias_1:
# 489 "data/maps/Route116/scripts.pory"
	msgbox Route116_EventScript_Elias_Text_0
# 490 "data/maps/Route116/scripts.pory"
	msgbox Route116_EventScript_Elias_Text_1
# 491 "data/maps/Route116/scripts.pory"
	msgbox Route116_EventScript_Elias_Text_2, MSGBOX_YESNO
# 492 "data/maps/Route116/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq Route116_EventScript_Elias_5
# 509 "data/maps/Route116/scripts.pory"
	msgbox Route116_EventScript_Elias_Text_6
Route116_EventScript_Elias_4:
# 511 "data/maps/Route116/scripts.pory"
	releaseall
	end

Route116_EventScript_Elias_2:
# 487 "data/maps/Route116/scripts.pory"
	goto Elias_Beaten
	goto Route116_EventScript_Elias_1

Route116_EventScript_Elias_5:
# 493 "data/maps/Route116/scripts.pory"
	msgbox Route116_EventScript_Elias_Text_3
# 494 "data/maps/Route116/scripts.pory"
	trainerbattle_no_intro TRAINER_ELIAS, Route116_EventScript_Elias_Text_4
# 495 "data/maps/Route116/scripts.pory"
	msgbox Route116_EventScript_Elias_Text_5
# 496 "data/maps/Route116/scripts.pory"
	goto_if_set FLAG_RESOURCE_MODE, Route116_EventScript_Elias_9
# 503 "data/maps/Route116/scripts.pory"
	giveItem ITEM_EJECT_BUTTON, 1
Route116_EventScript_Elias_8:
# 505 "data/maps/Route116/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Route116_EventScript_Elias_12
	goto Route116_EventScript_Elias_4

Route116_EventScript_Elias_9:
# 497 "data/maps/Route116/scripts.pory"
	compare VAR_MONOTYPE, TYPE_NONE
	goto_if_eq Route116_EventScript_Elias_14
# 500 "data/maps/Route116/scripts.pory"
	giveItem ITEM_EJECT_BUTTON, 6
	goto Route116_EventScript_Elias_8

Route116_EventScript_Elias_12:
# 506 "data/maps/Route116/scripts.pory"
	call Common_EventScript_ShowBagIsFull
	goto Route116_EventScript_Elias_4

Route116_EventScript_Elias_14:
# 498 "data/maps/Route116/scripts.pory"
	giveItem ITEM_EJECT_BUTTON, 3
	goto Route116_EventScript_Elias_8


Elias_Beaten_Text_0:
# 479 "data/maps/Route116/scripts.pory"
	.string "Are you getting a hang of the art of\n"
	.string "the Eject Button?$"

Route116_EventScript_Elias_Text_0:
# 489 "data/maps/Route116/scripts.pory"
	.string "I love jumping from place to place. My\n"
	.string "Pokemon like to move as well, so I've\l"
	.string "been fond of the Eject Button item.$"

Route116_EventScript_Elias_Text_1:
# 490 "data/maps/Route116/scripts.pory"
	.string "With an Eject Button, they can promptly\n"
	.string "leave the battle to come in later.$"

Route116_EventScript_Elias_Text_2:
# 491 "data/maps/Route116/scripts.pory"
	.string "Would you like to see my Pokemon in\n"
	.string "action?$"

Route116_EventScript_Elias_Text_3:
# 493 "data/maps/Route116/scripts.pory"
	.string "Glad to here it. I'll show you what we do!$"

Route116_EventScript_Elias_Text_4:
# 494 "data/maps/Route116/scripts.pory"
	.string "We got outplayed!$"

Route116_EventScript_Elias_Text_5:
# 495 "data/maps/Route116/scripts.pory"
	.string "You sure showed your stuff. I know\n"
	.string "where my Pokemon have to improve. As\l"
	.string "thanks, I'll let you in on the fun too!$"

Route116_EventScript_Elias_Text_6:
# 509 "data/maps/Route116/scripts.pory"
	.string "Oh, too bad. Let me know if you change\n"
	.string "your mind.$"
