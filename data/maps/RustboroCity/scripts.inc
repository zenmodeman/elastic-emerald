# 1 "data/maps/RustboroCity/scripts.pory"

# 2 "data/maps/RustboroCity/scripts.pory"

# 3 "data/maps/RustboroCity/scripts.pory"
RustboroCity_MapScripts::
# 4 "data/maps/RustboroCity/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_OnTransition
# 5 "data/maps/RustboroCity/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RustboroCity_OnFrame
# 6 "data/maps/RustboroCity/scripts.pory"
	.byte 0
# 7 "data/maps/RustboroCity/scripts.pory"

# 8 "data/maps/RustboroCity/scripts.pory"
RustboroCity_OnTransition:
# 9 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_VISITED_RUSTBORO_CITY
# 10 "data/maps/RustboroCity/scripts.pory"
	call Common_EventScript_SetupRivalGfxId
# 11 "data/maps/RustboroCity/scripts.pory"
	call_if_eq VAR_RUSTBORO_CITY_STATE, 6, RustboroCity_EventScript_HideMapNamePopup
# 12 "data/maps/RustboroCity/scripts.pory"
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
# 13 "data/maps/RustboroCity/scripts.pory"
	goto_if_eq VAR_RUSTBORO_CITY_STATE, 6, RustboroCity_EventScript_PositionScientistForExit
# 14 "data/maps/RustboroCity/scripts.pory"
	end
# 15 "data/maps/RustboroCity/scripts.pory"

# 16 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_PositionScientistForExit::
# 17 "data/maps/RustboroCity/scripts.pory"
	goto_if_eq VAR_TEMP_0, 11, RustboroCity_EventScript_PositionScientistLeftExit
# 18 "data/maps/RustboroCity/scripts.pory"
	setobjectxyperm LOCALID_RUSTBORO_SCIENTIST, 12, 15
# 19 "data/maps/RustboroCity/scripts.pory"
	end
# 20 "data/maps/RustboroCity/scripts.pory"

# 21 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_PositionScientistLeftExit::
# 22 "data/maps/RustboroCity/scripts.pory"
	setobjectxyperm LOCALID_RUSTBORO_SCIENTIST, 11, 15
# 23 "data/maps/RustboroCity/scripts.pory"
	end
# 24 "data/maps/RustboroCity/scripts.pory"

# 25 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_HideMapNamePopup::
# 26 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_HIDE_MAP_NAME_POPUP
# 27 "data/maps/RustboroCity/scripts.pory"
	return
# 28 "data/maps/RustboroCity/scripts.pory"

# 29 "data/maps/RustboroCity/scripts.pory"
RustboroCity_OnFrame:
# 30 "data/maps/RustboroCity/scripts.pory"
	map_script_2 VAR_RUSTBORO_CITY_STATE, 6, RustboroCity_EventScript_ScientistAddMatchCall
# 31 "data/maps/RustboroCity/scripts.pory"
	.2byte 0
# 32 "data/maps/RustboroCity/scripts.pory"

# 33 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_ScientistAddMatchCall::
# 34 "data/maps/RustboroCity/scripts.pory"
	lockall
# 35 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_ROUTE104_STATE, 1
# 36 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_PLAYER, RustboroCity_Movement_PlayerWalkDown
# 37 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 38 "data/maps/RustboroCity/scripts.pory"
	playse SE_EXIT
# 39 "data/maps/RustboroCity/scripts.pory"
	delay 10
# 40 "data/maps/RustboroCity/scripts.pory"
	addobject LOCALID_RUSTBORO_SCIENTIST
# 41 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_SCIENTIST, RustboroCity_Movement_ScientistApproachPlayer
# 42 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 43 "data/maps/RustboroCity/scripts.pory"
	playse SE_PIN
# 44 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_SCIENTIST, Common_Movement_ExclamationMark
# 45 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 46 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_SCIENTIST, Common_Movement_Delay48
# 47 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 48 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 49 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 50 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_SCIENTIST, RustboroCity_Movement_ScientistWalkInPlaceDown
# 51 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 52 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_DevelopedNewPokenavFeature, MSGBOX_DEFAULT
# 53 "data/maps/RustboroCity/scripts.pory"
	closemessage
# 54 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_HAS_MATCH_CALL
# 55 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_SCIENTIST, Common_Movement_WalkInPlaceFasterLeft
# 56 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 57 "data/maps/RustboroCity/scripts.pory"
	playse SE_CLICK
# 58 "data/maps/RustboroCity/scripts.pory"
	delay 10
# 59 "data/maps/RustboroCity/scripts.pory"
	playse SE_CLICK
# 60 "data/maps/RustboroCity/scripts.pory"
	delay 10
# 61 "data/maps/RustboroCity/scripts.pory"
	playse SE_CLICK
# 62 "data/maps/RustboroCity/scripts.pory"
	delay 10
# 63 "data/maps/RustboroCity/scripts.pory"
	playse SE_CLICK
# 64 "data/maps/RustboroCity/scripts.pory"
	delay 20
# 65 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_SCIENTIST, Common_Movement_WalkInPlaceFasterDown
# 66 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 67 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_AddedMatchCallPleaseCallMrStone, MSGBOX_DEFAULT
# 68 "data/maps/RustboroCity/scripts.pory"
	closemessage
# 69 "data/maps/RustboroCity/scripts.pory"
	delay 20
# 70 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_MatchCallTutorial
# 71 "data/maps/RustboroCity/scripts.pory"

# 72 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_PleaseSelectPokenav::
# 73 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_PleaseSelectPokenav, MSGBOX_DEFAULT
# 74 "data/maps/RustboroCity/scripts.pory"
	closemessage
# 75 "data/maps/RustboroCity/scripts.pory"
	delay 10
# 76 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_MatchCallTutorial
# 77 "data/maps/RustboroCity/scripts.pory"

# 78 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_MatchCallTutorial::
# 79 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_ADDED_MATCH_CALL_TO_POKENAV
# 80 "data/maps/RustboroCity/scripts.pory"
	special ScriptMenu_CreateStartMenuForPokenavTutorial
# 81 "data/maps/RustboroCity/scripts.pory"
	waitstate
# 82 "data/maps/RustboroCity/scripts.pory"
	switch VAR_RESULT
# 83 "data/maps/RustboroCity/scripts.pory"
	case 0, RustboroCity_EventScript_PleaseSelectPokenav
# 84 "data/maps/RustboroCity/scripts.pory"
	case 1, RustboroCity_EventScript_PleaseSelectPokenav
# 85 "data/maps/RustboroCity/scripts.pory"
	case 2, RustboroCity_EventScript_PleaseSelectPokenav
# 86 "data/maps/RustboroCity/scripts.pory"
	case 4, RustboroCity_EventScript_PleaseSelectPokenav
# 87 "data/maps/RustboroCity/scripts.pory"
	case 5, RustboroCity_EventScript_PleaseSelectPokenav
# 88 "data/maps/RustboroCity/scripts.pory"
	case 6, RustboroCity_EventScript_PleaseSelectPokenav
# 89 "data/maps/RustboroCity/scripts.pory"
	case 7, RustboroCity_EventScript_PleaseSelectPokenav
# 90 "data/maps/RustboroCity/scripts.pory"
	case MULTI_B_PRESSED, RustboroCity_EventScript_PleaseSelectPokenav
# 91 "data/maps/RustboroCity/scripts.pory"
	special OpenPokenavForTutorial
# 92 "data/maps/RustboroCity/scripts.pory"
	waitstate
# 93 "data/maps/RustboroCity/scripts.pory"
	delay 20
# 94 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_IdBetterGetBackToWork, MSGBOX_DEFAULT
# 95 "data/maps/RustboroCity/scripts.pory"
	closemessage
# 96 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_SCIENTIST, RustboroCity_Movement_ScientistLeave
# 97 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 98 "data/maps/RustboroCity/scripts.pory"
	playse SE_EXIT
# 99 "data/maps/RustboroCity/scripts.pory"
	removeobject LOCALID_RUSTBORO_SCIENTIST
# 100 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_HIDE_RUSTBORO_CITY_SCIENTIST
# 101 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_RUSTBORO_CITY_STATE, 7
# 102 "data/maps/RustboroCity/scripts.pory"
	clearflag FLAG_HIDE_MAP_NAME_POPUP
# 103 "data/maps/RustboroCity/scripts.pory"
	releaseall
# 104 "data/maps/RustboroCity/scripts.pory"
	end
# 105 "data/maps/RustboroCity/scripts.pory"

# 106 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_ScientistWalkInPlaceDown:
# 107 "data/maps/RustboroCity/scripts.pory"
	walk_in_place_down
# 108 "data/maps/RustboroCity/scripts.pory"
	step_end
# 109 "data/maps/RustboroCity/scripts.pory"

# 110 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_PlayerWalkDown:
# 111 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 112 "data/maps/RustboroCity/scripts.pory"
	step_end
# 113 "data/maps/RustboroCity/scripts.pory"

# 114 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_ScientistApproachPlayer:
# 115 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 116 "data/maps/RustboroCity/scripts.pory"
	delay_16
# 117 "data/maps/RustboroCity/scripts.pory"
	step_end
# 118 "data/maps/RustboroCity/scripts.pory"

# 119 "data/maps/RustboroCity/scripts.pory"
@ Unused
# 120 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_ScientistWalkAroundPlayer:
# 121 "data/maps/RustboroCity/scripts.pory"
	delay_16
# 122 "data/maps/RustboroCity/scripts.pory"
	walk_left
# 123 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 124 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 125 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 126 "data/maps/RustboroCity/scripts.pory"
	walk_in_place_faster_up
# 127 "data/maps/RustboroCity/scripts.pory"
	delay_16
# 128 "data/maps/RustboroCity/scripts.pory"
	step_end
# 129 "data/maps/RustboroCity/scripts.pory"

# 130 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_ScientistLeave:
# 131 "data/maps/RustboroCity/scripts.pory"
	walk_up
# 132 "data/maps/RustboroCity/scripts.pory"
	step_end
# 133 "data/maps/RustboroCity/scripts.pory"

# 134 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_FatMan::
# 135 "data/maps/RustboroCity/scripts.pory"
	lock
# 136 "data/maps/RustboroCity/scripts.pory"
	faceplayer
# 137 "data/maps/RustboroCity/scripts.pory"
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_EventScript_FatManSawGrunt
# 138 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_WeShortenItToDevon, MSGBOX_DEFAULT
# 139 "data/maps/RustboroCity/scripts.pory"
	release
# 140 "data/maps/RustboroCity/scripts.pory"
	end
# 141 "data/maps/RustboroCity/scripts.pory"

# 142 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_FatManSawGrunt::
# 143 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_SneakyLookingManWentAroundCorner, MSGBOX_DEFAULT
# 144 "data/maps/RustboroCity/scripts.pory"
	release
# 145 "data/maps/RustboroCity/scripts.pory"
	end
# 146 "data/maps/RustboroCity/scripts.pory"

# 147 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_DevonEmployee2::
# 148 "data/maps/RustboroCity/scripts.pory"
	lock
# 149 "data/maps/RustboroCity/scripts.pory"
	faceplayer
# 150 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_YoureNewAroundHere, MSGBOX_DEFAULT
# 151 "data/maps/RustboroCity/scripts.pory"
	release
# 152 "data/maps/RustboroCity/scripts.pory"
	end
# 153 "data/maps/RustboroCity/scripts.pory"

# 154 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_Woman::
# 155 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_GymLeaderIsntEasyWithFire, MSGBOX_NPC
# 156 "data/maps/RustboroCity/scripts.pory"
	end
# 157 "data/maps/RustboroCity/scripts.pory"

# 158 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_Man1::
# 159 "data/maps/RustboroCity/scripts.pory"
	lock
# 160 "data/maps/RustboroCity/scripts.pory"
	faceplayer
# 161 "data/maps/RustboroCity/scripts.pory"
	goto_if_set FLAG_BADGE01_GET, RustboroCity_EventScript_Man1HaveBadge
# 162 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_HaveYouChallengedGym, MSGBOX_DEFAULT
# 163 "data/maps/RustboroCity/scripts.pory"
	release
# 164 "data/maps/RustboroCity/scripts.pory"
	end
# 165 "data/maps/RustboroCity/scripts.pory"

# 166 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_Man1HaveBadge::
# 167 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_HeyThatsRustborosGymBadge, MSGBOX_DEFAULT
# 168 "data/maps/RustboroCity/scripts.pory"
	release
# 169 "data/maps/RustboroCity/scripts.pory"
	end
# 170 "data/maps/RustboroCity/scripts.pory"

# 171 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_Boy2::
# 172 "data/maps/RustboroCity/scripts.pory"
	lock
# 173 "data/maps/RustboroCity/scripts.pory"
	faceplayer
# 174 "data/maps/RustboroCity/scripts.pory"
	goto_if_set FLAG_RECEIVED_POKENAV, RustboroCity_EventScript_Boy2BrineyLeftTunnel
# 175 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_MrBrineyWalksInTheTunnel, MSGBOX_DEFAULT
# 176 "data/maps/RustboroCity/scripts.pory"
	release
# 177 "data/maps/RustboroCity/scripts.pory"
	end
# 178 "data/maps/RustboroCity/scripts.pory"

# 179 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_Boy2BrineyLeftTunnel::
# 180 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_MrBrineyLovesPeeko, MSGBOX_DEFAULT
# 181 "data/maps/RustboroCity/scripts.pory"
	release
# 182 "data/maps/RustboroCity/scripts.pory"
	end
# 183 "data/maps/RustboroCity/scripts.pory"

# 184 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_Twin::
# 185 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_WowYouHavePokemon, MSGBOX_NPC
# 186 "data/maps/RustboroCity/scripts.pory"
	end
# 187 "data/maps/RustboroCity/scripts.pory"

# 188 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_NinjaBoy::
# 189 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_CatchRarePokemonIfIGoToSchool, MSGBOX_SIGN
# 190 "data/maps/RustboroCity/scripts.pory"
	end
# 191 "data/maps/RustboroCity/scripts.pory"

# 192 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_TunnelSign::
# 193 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_TunnelNearingCompletion, MSGBOX_SIGN
# 194 "data/maps/RustboroCity/scripts.pory"
	end
# 195 "data/maps/RustboroCity/scripts.pory"

# 196 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_DevonCorpSign::
# 197 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_DevonCorpSign, MSGBOX_SIGN
# 198 "data/maps/RustboroCity/scripts.pory"
	end
# 199 "data/maps/RustboroCity/scripts.pory"

# 200 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_GymSign::
# 201 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_GymSign, MSGBOX_SIGN
# 202 "data/maps/RustboroCity/scripts.pory"
	end
# 203 "data/maps/RustboroCity/scripts.pory"

# 204 "data/maps/RustboroCity/scripts.pory"
@ Unused
# 205 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_DevonCorpBranchOfficeSign::
# 206 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_DevonCorpBranchOfficeSign, MSGBOX_SIGN
# 207 "data/maps/RustboroCity/scripts.pory"
	end
# 208 "data/maps/RustboroCity/scripts.pory"

# 209 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_CitySign::
# 210 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_CitySign, MSGBOX_SIGN
# 211 "data/maps/RustboroCity/scripts.pory"
	end
# 212 "data/maps/RustboroCity/scripts.pory"

# 213 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_TrainersSchoolSign::
# 214 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_TrainersSchoolSign, MSGBOX_SIGN
# 215 "data/maps/RustboroCity/scripts.pory"
	end
# 216 "data/maps/RustboroCity/scripts.pory"

# 217 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_CuttersHouseSign::
# 218 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_CuttersHouse, MSGBOX_SIGN
# 219 "data/maps/RustboroCity/scripts.pory"
	end
# 220 "data/maps/RustboroCity/scripts.pory"

# 221 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_LittleBoy::
# 222 "data/maps/RustboroCity/scripts.pory"
	lock
# 223 "data/maps/RustboroCity/scripts.pory"
	faceplayer
# 224 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_PokemonCanChangeLookFromExp, MSGBOX_DEFAULT
# 225 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_LITTLE_BOY, Common_Movement_FaceOriginalDirection
# 226 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 227 "data/maps/RustboroCity/scripts.pory"
	release
# 228 "data/maps/RustboroCity/scripts.pory"
	end
# 229 "data/maps/RustboroCity/scripts.pory"

# 230 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_LittleGirl::
# 231 "data/maps/RustboroCity/scripts.pory"
	lock
# 232 "data/maps/RustboroCity/scripts.pory"
	faceplayer
# 233 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_PokemonChangeShape, MSGBOX_DEFAULT
# 234 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_LITTLE_GIRL, Common_Movement_FaceOriginalDirection
# 235 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 236 "data/maps/RustboroCity/scripts.pory"
	release
# 237 "data/maps/RustboroCity/scripts.pory"
	end
# 238 "data/maps/RustboroCity/scripts.pory"

# 239 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_Man2::
# 240 "data/maps/RustboroCity/scripts.pory"
	lock
# 241 "data/maps/RustboroCity/scripts.pory"
	faceplayer
# 242 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_TradePokemonGrowFast, MSGBOX_DEFAULT
# 243 "data/maps/RustboroCity/scripts.pory"
	release
# 244 "data/maps/RustboroCity/scripts.pory"
	end
# 245 "data/maps/RustboroCity/scripts.pory"

# 246 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_StolenGoodsTrigger0::
# 247 "data/maps/RustboroCity/scripts.pory"
	lockall
# 248 "data/maps/RustboroCity/scripts.pory"
	setobjectxyperm LOCALID_RUSTBORO_DEVON_EMPLOYEE, 14, 21
# 249 "data/maps/RustboroCity/scripts.pory"
	setobjectmovementtype LOCALID_RUSTBORO_DEVON_EMPLOYEE, MOVEMENT_TYPE_FACE_RIGHT
# 250 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_0x8004, 0
# 251 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_StolenGoodsScene
# 252 "data/maps/RustboroCity/scripts.pory"
	end
# 253 "data/maps/RustboroCity/scripts.pory"

# 254 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_StolenGoodsTrigger1::
# 255 "data/maps/RustboroCity/scripts.pory"
	lockall
# 256 "data/maps/RustboroCity/scripts.pory"
	setobjectxyperm LOCALID_RUSTBORO_DEVON_EMPLOYEE, 14, 21
# 257 "data/maps/RustboroCity/scripts.pory"
	setobjectmovementtype LOCALID_RUSTBORO_DEVON_EMPLOYEE, MOVEMENT_TYPE_FACE_RIGHT
# 258 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_0x8004, 1
# 259 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_StolenGoodsScene
# 260 "data/maps/RustboroCity/scripts.pory"
	end
# 261 "data/maps/RustboroCity/scripts.pory"

# 262 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_StolenGoodsTrigger2::
# 263 "data/maps/RustboroCity/scripts.pory"
	lockall
# 264 "data/maps/RustboroCity/scripts.pory"
	setobjectxyperm LOCALID_RUSTBORO_DEVON_EMPLOYEE, 14, 21
# 265 "data/maps/RustboroCity/scripts.pory"
	setobjectmovementtype LOCALID_RUSTBORO_DEVON_EMPLOYEE, MOVEMENT_TYPE_FACE_RIGHT
# 266 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_0x8004, 2
# 267 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_StolenGoodsScene
# 268 "data/maps/RustboroCity/scripts.pory"
	end
# 269 "data/maps/RustboroCity/scripts.pory"

# 270 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_StolenGoodsTrigger3::
# 271 "data/maps/RustboroCity/scripts.pory"
	lockall
# 272 "data/maps/RustboroCity/scripts.pory"
	setobjectxyperm LOCALID_RUSTBORO_DEVON_EMPLOYEE, 14, 21
# 273 "data/maps/RustboroCity/scripts.pory"
	setobjectmovementtype LOCALID_RUSTBORO_DEVON_EMPLOYEE, MOVEMENT_TYPE_FACE_RIGHT
# 274 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_0x8004, 3
# 275 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_StolenGoodsScene
# 276 "data/maps/RustboroCity/scripts.pory"
	end
# 277 "data/maps/RustboroCity/scripts.pory"

# 278 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_StolenGoodsTrigger4::
# 279 "data/maps/RustboroCity/scripts.pory"
	lockall
# 280 "data/maps/RustboroCity/scripts.pory"
	setobjectxyperm LOCALID_RUSTBORO_DEVON_EMPLOYEE, 14, 21
# 281 "data/maps/RustboroCity/scripts.pory"
	setobjectmovementtype LOCALID_RUSTBORO_DEVON_EMPLOYEE, MOVEMENT_TYPE_FACE_RIGHT
# 282 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_0x8004, 4
# 283 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_StolenGoodsScene
# 284 "data/maps/RustboroCity/scripts.pory"
	end
# 285 "data/maps/RustboroCity/scripts.pory"

# 286 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_StolenGoodsScene::
# 287 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_OutOfTheWay, MSGBOX_DEFAULT
# 288 "data/maps/RustboroCity/scripts.pory"
	closemessage
# 289 "data/maps/RustboroCity/scripts.pory"
	playbgm MUS_ENCOUNTER_AQUA, FALSE
# 290 "data/maps/RustboroCity/scripts.pory"
	addobject LOCALID_RUSTBORO_GRUNT
# 291 "data/maps/RustboroCity/scripts.pory"
	addobject LOCALID_RUSTBORO_DEVON_EMPLOYEE
# 292 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_GRUNT, RustboroCity_Movement_GruntEscape
# 293 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 294 "data/maps/RustboroCity/scripts.pory"
	removeobject LOCALID_RUSTBORO_GRUNT
# 295 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, RustboroCity_Movement_EmployeeChaseGrunt1
# 296 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 297 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_WaitDontTakeMyGoods, MSGBOX_DEFAULT
# 298 "data/maps/RustboroCity/scripts.pory"
	closemessage
# 299 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, RustboroCity_Movement_EmployeeChaseGrunt2
# 300 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 301 "data/maps/RustboroCity/scripts.pory"
	fadedefaultbgm
# 302 "data/maps/RustboroCity/scripts.pory"
	removeobject LOCALID_RUSTBORO_DEVON_EMPLOYEE
# 303 "data/maps/RustboroCity/scripts.pory"
	setobjectxyperm LOCALID_RUSTBORO_DEVON_EMPLOYEE, 30, 10
# 304 "data/maps/RustboroCity/scripts.pory"
	clearflag FLAG_HIDE_RUSTBORO_CITY_DEVON_EMPLOYEE_1
# 305 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_DEVON_GOODS_STOLEN
# 306 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_RUSTBORO_CITY_STATE, 2
# 307 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_RUSTURF_TUNNEL_STATE, 2
# 308 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_ROUTE116_STATE, 1
# 309 "data/maps/RustboroCity/scripts.pory"
	clearflag FLAG_HIDE_ROUTE_116_MR_BRINEY
# 310 "data/maps/RustboroCity/scripts.pory"
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_PEEKO
# 311 "data/maps/RustboroCity/scripts.pory"
	clearflag FLAG_HIDE_RUSTURF_TUNNEL_AQUA_GRUNT
# 312 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
# 313 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
# 314 "data/maps/RustboroCity/scripts.pory"
	releaseall
# 315 "data/maps/RustboroCity/scripts.pory"
	end
# 316 "data/maps/RustboroCity/scripts.pory"

# 317 "data/maps/RustboroCity/scripts.pory"
@ Unused
# 318 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_ShadyCharacterTookOff::
# 319 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_ShadyCharacterTookOffTowardsTunnel, MSGBOX_DEFAULT
# 320 "data/maps/RustboroCity/scripts.pory"
	return
# 321 "data/maps/RustboroCity/scripts.pory"

# 322 "data/maps/RustboroCity/scripts.pory"
@ Unused
# 323 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_YouGotItThankYou::
# 324 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_YouGotItThankYou, MSGBOX_DEFAULT
# 325 "data/maps/RustboroCity/scripts.pory"
	return
# 326 "data/maps/RustboroCity/scripts.pory"

# 327 "data/maps/RustboroCity/scripts.pory"
@ Unknown, unused employee movements. Based on the differences in movement theyre for approaching an object (probably the player) in different positions
# 328 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_EmployeeApproachUp::
# 329 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, RustboroCity_Movement_EmployeeApproachUp
# 330 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 331 "data/maps/RustboroCity/scripts.pory"
	return
# 332 "data/maps/RustboroCity/scripts.pory"

# 333 "data/maps/RustboroCity/scripts.pory"
@ Unused, see above
# 334 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_EmployeeApproachLeft::
# 335 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, RustboroCity_Movement_EmployeeApproachLeft
# 336 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 337 "data/maps/RustboroCity/scripts.pory"
	return
# 338 "data/maps/RustboroCity/scripts.pory"

# 339 "data/maps/RustboroCity/scripts.pory"
@ Unused, see above
# 340 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_EmployeeApproachRight::
# 341 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, RustboroCity_Movement_EmployeeApproachRight
# 342 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 343 "data/maps/RustboroCity/scripts.pory"
	return
# 344 "data/maps/RustboroCity/scripts.pory"

# 345 "data/maps/RustboroCity/scripts.pory"
@ Unused, see above
# 346 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_EmployeeApproachDown::
# 347 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, RustboroCity_Movement_EmployeeApproachDown
# 348 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 349 "data/maps/RustboroCity/scripts.pory"
	return
# 350 "data/maps/RustboroCity/scripts.pory"

# 351 "data/maps/RustboroCity/scripts.pory"
@ Unused, similar movement to the above scripts
# 352 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_EmployeeApproachPlayerFar::
# 353 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, RustboroCity_Movement_EmployeeApproachPlayerFar
# 354 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 355 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 356 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 357 "data/maps/RustboroCity/scripts.pory"
	return
# 358 "data/maps/RustboroCity/scripts.pory"

# 359 "data/maps/RustboroCity/scripts.pory"
@ Unused
# 360 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_GruntEscapeExtended:
# 361 "data/maps/RustboroCity/scripts.pory"
	walk_faster_right
# 362 "data/maps/RustboroCity/scripts.pory"
	walk_faster_right
# 363 "data/maps/RustboroCity/scripts.pory"
	walk_fast_right
# 364 "data/maps/RustboroCity/scripts.pory"
	walk_fast_right
# 365 "data/maps/RustboroCity/scripts.pory"
	walk_fast_right
# 366 "data/maps/RustboroCity/scripts.pory"
	walk_fast_right
# 367 "data/maps/RustboroCity/scripts.pory"
	walk_fast_up
# 368 "data/maps/RustboroCity/scripts.pory"
	walk_fast_up
# 369 "data/maps/RustboroCity/scripts.pory"
	walk_fast_up
# 370 "data/maps/RustboroCity/scripts.pory"
	walk_fast_up
# 371 "data/maps/RustboroCity/scripts.pory"
	walk_fast_up
# 372 "data/maps/RustboroCity/scripts.pory"
	walk_fast_up
# 373 "data/maps/RustboroCity/scripts.pory"
	walk_fast_up
# 374 "data/maps/RustboroCity/scripts.pory"
	walk_fast_up
# 375 "data/maps/RustboroCity/scripts.pory"
	walk_fast_up
# 376 "data/maps/RustboroCity/scripts.pory"
	walk_fast_up
# 377 "data/maps/RustboroCity/scripts.pory"
	walk_fast_up
# 378 "data/maps/RustboroCity/scripts.pory"
	step_end
# 379 "data/maps/RustboroCity/scripts.pory"

# 380 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_GruntEscape:
# 381 "data/maps/RustboroCity/scripts.pory"
	walk_faster_right
# 382 "data/maps/RustboroCity/scripts.pory"
	walk_faster_right
# 383 "data/maps/RustboroCity/scripts.pory"
	walk_fast_right
# 384 "data/maps/RustboroCity/scripts.pory"
	walk_fast_right
# 385 "data/maps/RustboroCity/scripts.pory"
	walk_fast_right
# 386 "data/maps/RustboroCity/scripts.pory"
	walk_fast_right
# 387 "data/maps/RustboroCity/scripts.pory"
	walk_fast_right
# 388 "data/maps/RustboroCity/scripts.pory"
	walk_fast_up
# 389 "data/maps/RustboroCity/scripts.pory"
	walk_fast_up
# 390 "data/maps/RustboroCity/scripts.pory"
	walk_fast_up
# 391 "data/maps/RustboroCity/scripts.pory"
	walk_fast_up
# 392 "data/maps/RustboroCity/scripts.pory"
	walk_fast_up
# 393 "data/maps/RustboroCity/scripts.pory"
	walk_fast_up
# 394 "data/maps/RustboroCity/scripts.pory"
	walk_fast_up
# 395 "data/maps/RustboroCity/scripts.pory"
	walk_fast_up
# 396 "data/maps/RustboroCity/scripts.pory"
	walk_fast_up
# 397 "data/maps/RustboroCity/scripts.pory"
	step_end
# 398 "data/maps/RustboroCity/scripts.pory"

# 399 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_EmployeeChaseGrunt1:
# 400 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 401 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 402 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 403 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 404 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 405 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 406 "data/maps/RustboroCity/scripts.pory"
	walk_in_place_faster_up
# 407 "data/maps/RustboroCity/scripts.pory"
	step_end
# 408 "data/maps/RustboroCity/scripts.pory"

# 409 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_EmployeeChaseGrunt2:
# 410 "data/maps/RustboroCity/scripts.pory"
	walk_up
# 411 "data/maps/RustboroCity/scripts.pory"
	walk_up
# 412 "data/maps/RustboroCity/scripts.pory"
	walk_up
# 413 "data/maps/RustboroCity/scripts.pory"
	walk_up
# 414 "data/maps/RustboroCity/scripts.pory"
	walk_up
# 415 "data/maps/RustboroCity/scripts.pory"
	walk_up
# 416 "data/maps/RustboroCity/scripts.pory"
	walk_up
# 417 "data/maps/RustboroCity/scripts.pory"
	step_end
# 418 "data/maps/RustboroCity/scripts.pory"

# 419 "data/maps/RustboroCity/scripts.pory"
@ Functionally unused
# 420 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_EmployeeApproachUp:
# 421 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 422 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 423 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 424 "data/maps/RustboroCity/scripts.pory"
	step_end
# 425 "data/maps/RustboroCity/scripts.pory"

# 426 "data/maps/RustboroCity/scripts.pory"
@ Functionally unused
# 427 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_EmployeeApproachLeft:
# 428 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 429 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 430 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 431 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 432 "data/maps/RustboroCity/scripts.pory"
	step_end
# 433 "data/maps/RustboroCity/scripts.pory"

# 434 "data/maps/RustboroCity/scripts.pory"
@ Functionally unused
# 435 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_EmployeeApproachRight:
# 436 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 437 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 438 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 439 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 440 "data/maps/RustboroCity/scripts.pory"
	step_end
# 441 "data/maps/RustboroCity/scripts.pory"

# 442 "data/maps/RustboroCity/scripts.pory"
@ Functionally unused
# 443 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_EmployeeApproachDown:
# 444 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 445 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 446 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 447 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 448 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 449 "data/maps/RustboroCity/scripts.pory"
	step_end
# 450 "data/maps/RustboroCity/scripts.pory"

# 451 "data/maps/RustboroCity/scripts.pory"
@ Functionally unused
# 452 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_EmployeeApproachPlayerFar:
# 453 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 454 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 455 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 456 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 457 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 458 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 459 "data/maps/RustboroCity/scripts.pory"
	walk_in_place_faster_down
# 460 "data/maps/RustboroCity/scripts.pory"
	step_end
# 461 "data/maps/RustboroCity/scripts.pory"

# 462 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_DevonEmployee1::
# 463 "data/maps/RustboroCity/scripts.pory"
	lock
# 464 "data/maps/RustboroCity/scripts.pory"
	faceplayer
# 465 "data/maps/RustboroCity/scripts.pory"
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_EventScript_ReturnGoodsSpokeToEmployee
# 466 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_ShadyCharacterTookOffTowardsTunnel, MSGBOX_DEFAULT
# 467 "data/maps/RustboroCity/scripts.pory"
	release
# 468 "data/maps/RustboroCity/scripts.pory"
	end
# 469 "data/maps/RustboroCity/scripts.pory"

# 470 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_ReturnGoodsSpokeToEmployee::
# 471 "data/maps/RustboroCity/scripts.pory"
	waitse
# 472 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_TEMP_1, 4
# 473 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_ReturnGoods
# 474 "data/maps/RustboroCity/scripts.pory"
	end
# 475 "data/maps/RustboroCity/scripts.pory"

# 476 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_HelpGetGoodsTrigger0::
# 477 "data/maps/RustboroCity/scripts.pory"
	lockall
# 478 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_TEMP_1, 0
# 479 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_EmployeeAskToGetGoods
# 480 "data/maps/RustboroCity/scripts.pory"
	end
# 481 "data/maps/RustboroCity/scripts.pory"

# 482 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_HelpGetGoodsTrigger1::
# 483 "data/maps/RustboroCity/scripts.pory"
	lockall
# 484 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_TEMP_1, 1
# 485 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_EmployeeAskToGetGoods
# 486 "data/maps/RustboroCity/scripts.pory"
	end
# 487 "data/maps/RustboroCity/scripts.pory"

# 488 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_HelpGetGoodsTrigger2::
# 489 "data/maps/RustboroCity/scripts.pory"
	lockall
# 490 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_TEMP_1, 2
# 491 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_EmployeeAskToGetGoods
# 492 "data/maps/RustboroCity/scripts.pory"
	end
# 493 "data/maps/RustboroCity/scripts.pory"

# 494 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_HelpGetGoodsTrigger3::
# 495 "data/maps/RustboroCity/scripts.pory"
	lockall
# 496 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_TEMP_1, 3
# 497 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_EmployeeAskToGetGoods
# 498 "data/maps/RustboroCity/scripts.pory"
	end
# 499 "data/maps/RustboroCity/scripts.pory"

# 500 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_EmployeeAskToGetGoods::
# 501 "data/maps/RustboroCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 0, RustboroCity_EventScript_EmployeeFacePlayerUp1
# 502 "data/maps/RustboroCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 1, RustboroCity_EventScript_EmployeeFacePlayerLeft1
# 503 "data/maps/RustboroCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 2, RustboroCity_EventScript_EmployeeFacePlayerDown1
# 504 "data/maps/RustboroCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 3, RustboroCity_EventScript_EmployeeApproachPlayerDown1
# 505 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_INTERACTED_WITH_DEVON_EMPLOYEE_GOODS_STOLEN
# 506 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_RUSTBORO_CITY_STATE, 3
# 507 "data/maps/RustboroCity/scripts.pory"
	copyobjectxytoperm LOCALID_RUSTBORO_DEVON_EMPLOYEE
# 508 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_HelpMeIWasRobbed, MSGBOX_DEFAULT
# 509 "data/maps/RustboroCity/scripts.pory"
	releaseall
# 510 "data/maps/RustboroCity/scripts.pory"
	end
# 511 "data/maps/RustboroCity/scripts.pory"

# 512 "data/maps/RustboroCity/scripts.pory"
@ The below movement scripts are either partially or fully duplicated by the movement scripts when the player returns the goods
# 513 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_EmployeeFacePlayerUp1::
# 514 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterUp
# 515 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 516 "data/maps/RustboroCity/scripts.pory"
	playse SE_PIN
# 517 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
# 518 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 519 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_Delay48
# 520 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 521 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
# 522 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 523 "data/maps/RustboroCity/scripts.pory"
	return
# 524 "data/maps/RustboroCity/scripts.pory"

# 525 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_EmployeeFacePlayerLeft1::
# 526 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterLeft
# 527 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 528 "data/maps/RustboroCity/scripts.pory"
	playse SE_PIN
# 529 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
# 530 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 531 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_Delay48
# 532 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 533 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_FaceRight
# 534 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 535 "data/maps/RustboroCity/scripts.pory"
	return
# 536 "data/maps/RustboroCity/scripts.pory"

# 537 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_EmployeeFacePlayerDown1::
# 538 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterDown
# 539 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 540 "data/maps/RustboroCity/scripts.pory"
	playse SE_PIN
# 541 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
# 542 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 543 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_Delay48
# 544 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 545 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 546 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 547 "data/maps/RustboroCity/scripts.pory"
	return
# 548 "data/maps/RustboroCity/scripts.pory"

# 549 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_EmployeeApproachPlayerDown1::
# 550 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterDown
# 551 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 552 "data/maps/RustboroCity/scripts.pory"
	playse SE_PIN
# 553 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
# 554 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 555 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_Delay48
# 556 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 557 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, RustboroCity_Movement_EmployeeApproachPlayerDown
# 558 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 559 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 560 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 561 "data/maps/RustboroCity/scripts.pory"
	return
# 562 "data/maps/RustboroCity/scripts.pory"

# 563 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_EmployeeApproachPlayerDown:
# 564 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 565 "data/maps/RustboroCity/scripts.pory"
	step_end
# 566 "data/maps/RustboroCity/scripts.pory"

# 567 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_ReturnGoodsTrigger0::
# 568 "data/maps/RustboroCity/scripts.pory"
	lockall
# 569 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_TEMP_1, 0
# 570 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_ReturnGoods
# 571 "data/maps/RustboroCity/scripts.pory"
	end
# 572 "data/maps/RustboroCity/scripts.pory"

# 573 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_ReturnGoodsTrigger1::
# 574 "data/maps/RustboroCity/scripts.pory"
	lockall
# 575 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_TEMP_1, 1
# 576 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_ReturnGoods
# 577 "data/maps/RustboroCity/scripts.pory"
	end
# 578 "data/maps/RustboroCity/scripts.pory"

# 579 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_ReturnGoodsTrigger2::
# 580 "data/maps/RustboroCity/scripts.pory"
	lockall
# 581 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_TEMP_1, 2
# 582 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_ReturnGoods
# 583 "data/maps/RustboroCity/scripts.pory"
	end
# 584 "data/maps/RustboroCity/scripts.pory"

# 585 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_ReturnGoodsTrigger3::
# 586 "data/maps/RustboroCity/scripts.pory"
	lockall
# 587 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_TEMP_1, 3
# 588 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_ReturnGoods
# 589 "data/maps/RustboroCity/scripts.pory"
	end
# 590 "data/maps/RustboroCity/scripts.pory"

# 591 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_ReturnGoods::
# 592 "data/maps/RustboroCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 0, RustboroCity_EventScript_EmployeeFacePlayerUp2
# 593 "data/maps/RustboroCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 1, RustboroCity_EventScript_EmployeeFacePlayerLeft2
# 594 "data/maps/RustboroCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 2, RustboroCity_EventScript_EmployeeFacePlayerDown2
# 595 "data/maps/RustboroCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 3, RustboroCity_EventScript_EmployeeApproachPlayerDown2
# 596 "data/maps/RustboroCity/scripts.pory"
	call_if_eq VAR_TEMP_1, 4, RustboroCity_EventScript_EmployeeFacePlayerRight
# 597 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_YouGotItThankYou, MSGBOX_DEFAULT
# 598 "data/maps/RustboroCity/scripts.pory"
	giveitem ITEM_GREAT_BALL
# 599 "data/maps/RustboroCity/scripts.pory"
	call_if_eq VAR_RESULT, FALSE, RustboroCity_EventScript_BagFull
# 600 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_PleaseComeWithMe, MSGBOX_DEFAULT
# 601 "data/maps/RustboroCity/scripts.pory"
	closemessage
# 602 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_RETURNED_DEVON_GOODS
# 603 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_HIDE_RUSTBORO_CITY_DEVON_EMPLOYEE_1
# 604 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_RUSTBORO_CITY_STATE, 5
# 605 "data/maps/RustboroCity/scripts.pory"
	delay 30
# 606 "data/maps/RustboroCity/scripts.pory"
	warp MAP_RUSTBORO_CITY_DEVON_CORP_3F, 2, 2
# 607 "data/maps/RustboroCity/scripts.pory"
	waitstate
# 608 "data/maps/RustboroCity/scripts.pory"
	releaseall
# 609 "data/maps/RustboroCity/scripts.pory"
	end
# 610 "data/maps/RustboroCity/scripts.pory"

# 611 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_BagFull::
# 612 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_YoureLoadedWithItems, MSGBOX_DEFAULT
# 613 "data/maps/RustboroCity/scripts.pory"
	return
# 614 "data/maps/RustboroCity/scripts.pory"

# 615 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_EmployeeFacePlayerUp2::
# 616 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterUp
# 617 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 618 "data/maps/RustboroCity/scripts.pory"
	playse SE_PIN
# 619 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
# 620 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 621 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_Delay48
# 622 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 623 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterDown
# 624 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 625 "data/maps/RustboroCity/scripts.pory"
	return
# 626 "data/maps/RustboroCity/scripts.pory"

# 627 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_EmployeeFacePlayerLeft2::
# 628 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterRight
# 629 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 630 "data/maps/RustboroCity/scripts.pory"
	playse SE_PIN
# 631 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
# 632 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 633 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_Delay48
# 634 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 635 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_FaceLeft
# 636 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 637 "data/maps/RustboroCity/scripts.pory"
	return
# 638 "data/maps/RustboroCity/scripts.pory"

# 639 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_EmployeeFacePlayerDown2::
# 640 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterDown
# 641 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 642 "data/maps/RustboroCity/scripts.pory"
	playse SE_PIN
# 643 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
# 644 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 645 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_Delay48
# 646 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 647 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 648 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 649 "data/maps/RustboroCity/scripts.pory"
	return
# 650 "data/maps/RustboroCity/scripts.pory"

# 651 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_EmployeeApproachPlayerDown2::
# 652 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterDown
# 653 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 654 "data/maps/RustboroCity/scripts.pory"
	playse SE_PIN
# 655 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
# 656 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 657 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_Delay48
# 658 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 659 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, RustboroCity_Movement_EmployeeApproachPlayerDown
# 660 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 661 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 662 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 663 "data/maps/RustboroCity/scripts.pory"
	return
# 664 "data/maps/RustboroCity/scripts.pory"

# 665 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_EmployeeFacePlayerRight::
# 666 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_WalkInPlaceFasterLeft
# 667 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 668 "data/maps/RustboroCity/scripts.pory"
	playse SE_PIN
# 669 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_ExclamationMark
# 670 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 671 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_DEVON_EMPLOYEE, Common_Movement_Delay48
# 672 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 673 "data/maps/RustboroCity/scripts.pory"
	return
# 674 "data/maps/RustboroCity/scripts.pory"

# 675 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_Rival::
# 676 "data/maps/RustboroCity/scripts.pory"
	lockall
# 677 "data/maps/RustboroCity/scripts.pory"
	call_if_unset FLAG_MET_RIVAL_RUSTBORO, RustboroCity_EventScript_PlayRivalMusic
# 678 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_FacePlayer
# 679 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 680 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_RivalEncounter
# 681 "data/maps/RustboroCity/scripts.pory"

# 682 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_PlayRivalMusic::
# 683 "data/maps/RustboroCity/scripts.pory"
	checkplayergender
# 684 "data/maps/RustboroCity/scripts.pory"
	goto_if_eq VAR_RESULT, MALE, RustboroCity_EventScript_PlayMayMusic
# 685 "data/maps/RustboroCity/scripts.pory"
	goto_if_eq VAR_RESULT, FEMALE, RustboroCity_EventScript_PlayBrendanMusic
# 686 "data/maps/RustboroCity/scripts.pory"
	return
# 687 "data/maps/RustboroCity/scripts.pory"

# 688 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_PlayMayMusic::
# 689 "data/maps/RustboroCity/scripts.pory"
	playbgm MUS_ENCOUNTER_MAY, TRUE
# 690 "data/maps/RustboroCity/scripts.pory"
	return
# 691 "data/maps/RustboroCity/scripts.pory"

# 692 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_PlayBrendanMusic::
# 693 "data/maps/RustboroCity/scripts.pory"
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
# 694 "data/maps/RustboroCity/scripts.pory"
	return
# 695 "data/maps/RustboroCity/scripts.pory"

# 696 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_RivalTrigger0::
# 697 "data/maps/RustboroCity/scripts.pory"
	lockall
# 698 "data/maps/RustboroCity/scripts.pory"
	call RustboroCity_EventScript_PlayRivalMusic
# 699 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_WalkInPlaceFasterDown
# 700 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 701 "data/maps/RustboroCity/scripts.pory"
	playse SE_PIN
# 702 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_ExclamationMark
# 703 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 704 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_Delay48
# 705 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 706 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, RustboroCity_Movement_RivalApproachPlayer0
# 707 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 708 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 709 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 710 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_RivalEncounter
# 711 "data/maps/RustboroCity/scripts.pory"

# 712 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_RivalTrigger1::
# 713 "data/maps/RustboroCity/scripts.pory"
	lockall
# 714 "data/maps/RustboroCity/scripts.pory"
	call RustboroCity_EventScript_PlayRivalMusic
# 715 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_WalkInPlaceFasterDown
# 716 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 717 "data/maps/RustboroCity/scripts.pory"
	playse SE_PIN
# 718 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_ExclamationMark
# 719 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 720 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_Delay48
# 721 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 722 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, RustboroCity_Movement_RivalApproachPlayer1
# 723 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 724 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 725 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 726 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_RivalEncounter
# 727 "data/maps/RustboroCity/scripts.pory"

# 728 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_RivalTrigger2::
# 729 "data/maps/RustboroCity/scripts.pory"
	lockall
# 730 "data/maps/RustboroCity/scripts.pory"
	call RustboroCity_EventScript_PlayRivalMusic
# 731 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_WalkInPlaceFasterDown
# 732 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 733 "data/maps/RustboroCity/scripts.pory"
	playse SE_PIN
# 734 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_ExclamationMark
# 735 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 736 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_Delay48
# 737 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 738 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, RustboroCity_Movement_RivalApproachPlayer2
# 739 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 740 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 741 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 742 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_RivalEncounter
# 743 "data/maps/RustboroCity/scripts.pory"

# 744 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_RivalTrigger3::
# 745 "data/maps/RustboroCity/scripts.pory"
	lockall
# 746 "data/maps/RustboroCity/scripts.pory"
	call RustboroCity_EventScript_PlayRivalMusic
# 747 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_WalkInPlaceFasterDown
# 748 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 749 "data/maps/RustboroCity/scripts.pory"
	playse SE_PIN
# 750 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_ExclamationMark
# 751 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 752 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_Delay48
# 753 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 754 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, RustboroCity_Movement_RivalApproachPlayer3
# 755 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 756 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 757 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 758 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_RivalEncounter
# 759 "data/maps/RustboroCity/scripts.pory"

# 760 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_RivalTrigger4::
# 761 "data/maps/RustboroCity/scripts.pory"
	lockall
# 762 "data/maps/RustboroCity/scripts.pory"
	call RustboroCity_EventScript_PlayRivalMusic
# 763 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_WalkInPlaceFasterDown
# 764 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 765 "data/maps/RustboroCity/scripts.pory"
	playse SE_PIN
# 766 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_ExclamationMark
# 767 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 768 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_Delay48
# 769 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 770 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, RustboroCity_Movement_RivalApproachPlayer4
# 771 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 772 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 773 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 774 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_RivalEncounter
# 775 "data/maps/RustboroCity/scripts.pory"

# 776 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_RivalTrigger5::
# 777 "data/maps/RustboroCity/scripts.pory"
	lockall
# 778 "data/maps/RustboroCity/scripts.pory"
	call RustboroCity_EventScript_PlayRivalMusic
# 779 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_WalkInPlaceFasterDown
# 780 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 781 "data/maps/RustboroCity/scripts.pory"
	playse SE_PIN
# 782 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_ExclamationMark
# 783 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 784 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_Delay48
# 785 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 786 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, RustboroCity_Movement_RivalApproachPlayer5
# 787 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 788 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 789 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 790 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_RivalEncounter
# 791 "data/maps/RustboroCity/scripts.pory"

# 792 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_RivalTrigger6::
# 793 "data/maps/RustboroCity/scripts.pory"
	lockall
# 794 "data/maps/RustboroCity/scripts.pory"
	call RustboroCity_EventScript_PlayRivalMusic
# 795 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_WalkInPlaceFasterDown
# 796 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 797 "data/maps/RustboroCity/scripts.pory"
	playse SE_PIN
# 798 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_ExclamationMark
# 799 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 800 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_Delay48
# 801 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 802 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, RustboroCity_Movement_RivalApproachPlayer6
# 803 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 804 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 805 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 806 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_RivalEncounter
# 807 "data/maps/RustboroCity/scripts.pory"

# 808 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_RivalTrigger7::
# 809 "data/maps/RustboroCity/scripts.pory"
	lockall
# 810 "data/maps/RustboroCity/scripts.pory"
	call RustboroCity_EventScript_PlayRivalMusic
# 811 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_WalkInPlaceFasterDown
# 812 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 813 "data/maps/RustboroCity/scripts.pory"
	playse SE_PIN
# 814 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_ExclamationMark
# 815 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 816 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, Common_Movement_Delay48
# 817 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 818 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_RUSTBORO_RIVAL, RustboroCity_Movement_RivalApproachPlayer7
# 819 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 820 "data/maps/RustboroCity/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 821 "data/maps/RustboroCity/scripts.pory"
	waitmovement 0
# 822 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_RivalEncounter
# 823 "data/maps/RustboroCity/scripts.pory"

# 824 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_RivalEncounter::
# 825 "data/maps/RustboroCity/scripts.pory"
	checkplayergender
# 826 "data/maps/RustboroCity/scripts.pory"
	goto_if_eq VAR_RESULT, MALE, RustboroCity_EventScript_MayEncounter
# 827 "data/maps/RustboroCity/scripts.pory"
	goto_if_eq VAR_RESULT, FEMALE, RustboroCity_EventScript_BrendanEncounter
# 828 "data/maps/RustboroCity/scripts.pory"
	end
# 829 "data/maps/RustboroCity/scripts.pory"

# 830 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_MayEncounter::
# 831 "data/maps/RustboroCity/scripts.pory"
	goto_if_set FLAG_DEFEATED_RIVAL_RUSTBORO, RustboroCity_EventScript_MayBrineyHint
# 832 "data/maps/RustboroCity/scripts.pory"
	goto_if_set FLAG_MET_RIVAL_RUSTBORO, RustboroCity_EventScript_MayAskToBattle
# 833 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_MET_RIVAL_RUSTBORO
# 834 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_MayHiLetsRegister, MSGBOX_DEFAULT
# 835 "data/maps/RustboroCity/scripts.pory"
	closemessage
# 836 "data/maps/RustboroCity/scripts.pory"
	delay 30
# 837 "data/maps/RustboroCity/scripts.pory"
	playfanfare MUS_REGISTER_MATCH_CALL
# 838 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_RegisteredMay, MSGBOX_DEFAULT
# 839 "data/maps/RustboroCity/scripts.pory"
	waitfanfare
# 840 "data/maps/RustboroCity/scripts.pory"
	closemessage
# 841 "data/maps/RustboroCity/scripts.pory"
	delay 30
# 842 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
# 843 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_RUSTBORO_CITY_STATE, 8
# 844 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_ROUTE104_STATE, 2
# 845 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_0x8008, 0
# 846 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_MayPassedBrineyWantToBattle, MSGBOX_YESNO
# 847 "data/maps/RustboroCity/scripts.pory"
	goto_if_eq VAR_RESULT, YES, RustboroCity_EventScript_BattleMay
# 848 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_MayOhHaventRaisedPokemonEnough, MSGBOX_DEFAULT
# 849 "data/maps/RustboroCity/scripts.pory"
	call RustboroCity_EventScript_RestoreBgm
# 850 "data/maps/RustboroCity/scripts.pory"
	releaseall
# 851 "data/maps/RustboroCity/scripts.pory"
	end
# 852 "data/maps/RustboroCity/scripts.pory"

# 853 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_MayAskToBattle::
# 854 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_0x8008, 1
# 855 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_MayWantToBattle, MSGBOX_YESNO
# 856 "data/maps/RustboroCity/scripts.pory"
	goto_if_eq VAR_RESULT, YES, RustboroCity_EventScript_BattleMay
# 857 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_MayOhHaventRaisedPokemonEnough, MSGBOX_DEFAULT
# 858 "data/maps/RustboroCity/scripts.pory"
	releaseall
# 859 "data/maps/RustboroCity/scripts.pory"
	end
# 860 "data/maps/RustboroCity/scripts.pory"

# 861 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_BattleMay::
# 862 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_MayImNotGoingToLose, MSGBOX_DEFAULT
# 863 "data/maps/RustboroCity/scripts.pory"
	switch VAR_STARTER_MON
# 864 "data/maps/RustboroCity/scripts.pory"
	case 0, RustboroCity_EventScript_BattleMayTreecko
# 865 "data/maps/RustboroCity/scripts.pory"
	case 1, RustboroCity_EventScript_BattleMayTorchic
# 866 "data/maps/RustboroCity/scripts.pory"
	case 2, RustboroCity_EventScript_BattleMayMudkip
# 867 "data/maps/RustboroCity/scripts.pory"
	end
# 868 "data/maps/RustboroCity/scripts.pory"

# 869 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_MayBrineyHint::
# 870 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_MayMrBrineyHint, MSGBOX_DEFAULT
# 871 "data/maps/RustboroCity/scripts.pory"
	call_if_eq VAR_0x8008, 0, RustboroCity_EventScript_RestoreBgm
# 872 "data/maps/RustboroCity/scripts.pory"
	releaseall
# 873 "data/maps/RustboroCity/scripts.pory"
	end
# 874 "data/maps/RustboroCity/scripts.pory"

# 875 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_RestoreBgm::
# 876 "data/maps/RustboroCity/scripts.pory"
	savebgm MUS_DUMMY
# 877 "data/maps/RustboroCity/scripts.pory"
	fadedefaultbgm
# 878 "data/maps/RustboroCity/scripts.pory"
	return
# 879 "data/maps/RustboroCity/scripts.pory"

# 880 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_BattleMayTreecko::
# 881 "data/maps/RustboroCity/scripts.pory"
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_TREECKO, RustboroCity_Text_MayDefeat
# 882 "data/maps/RustboroCity/scripts.pory"
	call(RustburoRival_GiveBottleCap)
# 883 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
# 884 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_MayBrineyHint
# 885 "data/maps/RustboroCity/scripts.pory"
	end
# 886 "data/maps/RustboroCity/scripts.pory"

# 887 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_BattleMayTorchic::
# 888 "data/maps/RustboroCity/scripts.pory"
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_TORCHIC, RustboroCity_Text_MayDefeat
# 889 "data/maps/RustboroCity/scripts.pory"
	call(RustburoRival_GiveBottleCap)
# 890 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
# 891 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_MayBrineyHint
# 892 "data/maps/RustboroCity/scripts.pory"
	end
# 893 "data/maps/RustboroCity/scripts.pory"

# 894 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_BattleMayMudkip::
# 895 "data/maps/RustboroCity/scripts.pory"
	trainerbattle_no_intro TRAINER_MAY_RUSTBORO_MUDKIP, RustboroCity_Text_MayDefeat
# 896 "data/maps/RustboroCity/scripts.pory"
	call(RustburoRival_GiveBottleCap)
# 897 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
# 898 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_MayBrineyHint
# 899 "data/maps/RustboroCity/scripts.pory"
	end
# 900 "data/maps/RustboroCity/scripts.pory"

# 901 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_BrendanEncounter::
# 902 "data/maps/RustboroCity/scripts.pory"
	goto_if_set FLAG_DEFEATED_RIVAL_RUSTBORO, RustboroCity_EventScript_BrendanBrineyHint
# 903 "data/maps/RustboroCity/scripts.pory"
	goto_if_set FLAG_MET_RIVAL_RUSTBORO, RustboroCity_EventScript_BrendanAskToBattle
# 904 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_MET_RIVAL_RUSTBORO
# 905 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_BrendanHiLetsRegister, MSGBOX_DEFAULT
# 906 "data/maps/RustboroCity/scripts.pory"
	closemessage
# 907 "data/maps/RustboroCity/scripts.pory"
	delay 30
# 908 "data/maps/RustboroCity/scripts.pory"
	playfanfare MUS_REGISTER_MATCH_CALL
# 909 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_RegisteredBrendan, MSGBOX_DEFAULT
# 910 "data/maps/RustboroCity/scripts.pory"
	waitfanfare
# 911 "data/maps/RustboroCity/scripts.pory"
	closemessage
# 912 "data/maps/RustboroCity/scripts.pory"
	delay 30
# 913 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_ENABLE_RIVAL_MATCH_CALL
# 914 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_RUSTBORO_CITY_STATE, 8
# 915 "data/maps/RustboroCity/scripts.pory"
	setvar VAR_ROUTE104_STATE, 2
# 916 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_BrendanPassedBrineyWantToBattle, MSGBOX_YESNO
# 917 "data/maps/RustboroCity/scripts.pory"
	goto_if_eq VAR_RESULT, YES, RustboroCity_EventScript_BattleBrendan
# 918 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_BrendanNoConfidenceInPokemon, MSGBOX_DEFAULT
# 919 "data/maps/RustboroCity/scripts.pory"
	call RustboroCity_EventScript_RestoreBgm
# 920 "data/maps/RustboroCity/scripts.pory"
	releaseall
# 921 "data/maps/RustboroCity/scripts.pory"
	end
# 922 "data/maps/RustboroCity/scripts.pory"

# 923 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_BrendanAskToBattle::
# 924 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_BrendanWantToBattle, MSGBOX_YESNO
# 925 "data/maps/RustboroCity/scripts.pory"
	goto_if_eq VAR_RESULT, YES, RustboroCity_EventScript_BattleBrendan
# 926 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_BrendanNoConfidenceInPokemon, MSGBOX_DEFAULT
# 927 "data/maps/RustboroCity/scripts.pory"
	releaseall
# 928 "data/maps/RustboroCity/scripts.pory"
	end
# 929 "data/maps/RustboroCity/scripts.pory"

# 930 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_BattleBrendan::
# 931 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_BrendanIWontGoEasy, MSGBOX_DEFAULT
# 932 "data/maps/RustboroCity/scripts.pory"
	switch VAR_STARTER_MON
# 933 "data/maps/RustboroCity/scripts.pory"
	case 0, RustboroCity_EventScript_BattleBrendanTreecko
# 934 "data/maps/RustboroCity/scripts.pory"
	case 1, RustboroCity_EventScript_BattleBrendanTorchic
# 935 "data/maps/RustboroCity/scripts.pory"
	case 2, RustboroCity_EventScript_BattleBrendanMudkip
# 936 "data/maps/RustboroCity/scripts.pory"
	end
# 937 "data/maps/RustboroCity/scripts.pory"

# 938 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_BrendanBrineyHint::
# 939 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_BrendanMrBrineyHint, MSGBOX_DEFAULT
# 940 "data/maps/RustboroCity/scripts.pory"
	call_if_eq VAR_0x8008, 0, RustboroCity_EventScript_RestoreBgm
# 941 "data/maps/RustboroCity/scripts.pory"
	releaseall
# 942 "data/maps/RustboroCity/scripts.pory"
	end
# 943 "data/maps/RustboroCity/scripts.pory"

# 944 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_BattleBrendanTreecko::
# 945 "data/maps/RustboroCity/scripts.pory"
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_TREECKO, RustboroCity_Text_BrendanDefeat
# 946 "data/maps/RustboroCity/scripts.pory"
	call(RustburoRival_GiveBottleCap)
# 947 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
# 948 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_BrendanBrineyHint
# 949 "data/maps/RustboroCity/scripts.pory"
	end
# 950 "data/maps/RustboroCity/scripts.pory"

# 951 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_BattleBrendanTorchic::
# 952 "data/maps/RustboroCity/scripts.pory"
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_TORCHIC, RustboroCity_Text_BrendanDefeat
# 953 "data/maps/RustboroCity/scripts.pory"
	call(RustburoRival_GiveBottleCap)
# 954 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
# 955 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_BrendanBrineyHint
# 956 "data/maps/RustboroCity/scripts.pory"
	end
# 957 "data/maps/RustboroCity/scripts.pory"

# 958 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_BattleBrendanMudkip::
# 959 "data/maps/RustboroCity/scripts.pory"
	trainerbattle_no_intro TRAINER_BRENDAN_RUSTBORO_MUDKIP, RustboroCity_Text_BrendanDefeat
# 960 "data/maps/RustboroCity/scripts.pory"
	call(RustburoRival_GiveBottleCap)
# 961 "data/maps/RustboroCity/scripts.pory"
	setflag FLAG_DEFEATED_RIVAL_RUSTBORO
# 962 "data/maps/RustboroCity/scripts.pory"
	goto RustboroCity_EventScript_BrendanBrineyHint
# 963 "data/maps/RustboroCity/scripts.pory"
	end
# 964 "data/maps/RustboroCity/scripts.pory"

# 965 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_RivalApproachPlayer0:
# 966 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 967 "data/maps/RustboroCity/scripts.pory"
	walk_left
# 968 "data/maps/RustboroCity/scripts.pory"
	walk_left
# 969 "data/maps/RustboroCity/scripts.pory"
	walk_left
# 970 "data/maps/RustboroCity/scripts.pory"
	walk_left
# 971 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 972 "data/maps/RustboroCity/scripts.pory"
	step_end
# 973 "data/maps/RustboroCity/scripts.pory"

# 974 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_RivalApproachPlayer1:
# 975 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 976 "data/maps/RustboroCity/scripts.pory"
	walk_left
# 977 "data/maps/RustboroCity/scripts.pory"
	walk_left
# 978 "data/maps/RustboroCity/scripts.pory"
	walk_left
# 979 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 980 "data/maps/RustboroCity/scripts.pory"
	step_end
# 981 "data/maps/RustboroCity/scripts.pory"

# 982 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_RivalApproachPlayer2:
# 983 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 984 "data/maps/RustboroCity/scripts.pory"
	walk_left
# 985 "data/maps/RustboroCity/scripts.pory"
	walk_left
# 986 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 987 "data/maps/RustboroCity/scripts.pory"
	step_end
# 988 "data/maps/RustboroCity/scripts.pory"

# 989 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_RivalApproachPlayer3:
# 990 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 991 "data/maps/RustboroCity/scripts.pory"
	walk_left
# 992 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 993 "data/maps/RustboroCity/scripts.pory"
	step_end
# 994 "data/maps/RustboroCity/scripts.pory"

# 995 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_RivalApproachPlayer4:
# 996 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 997 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 998 "data/maps/RustboroCity/scripts.pory"
	step_end
# 999 "data/maps/RustboroCity/scripts.pory"

# 1000 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_RivalApproachPlayer5:
# 1001 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 1002 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 1003 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 1004 "data/maps/RustboroCity/scripts.pory"
	step_end
# 1005 "data/maps/RustboroCity/scripts.pory"

# 1006 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_RivalApproachPlayer6:
# 1007 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 1008 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 1009 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 1010 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 1011 "data/maps/RustboroCity/scripts.pory"
	step_end
# 1012 "data/maps/RustboroCity/scripts.pory"

# 1013 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Movement_RivalApproachPlayer7:
# 1014 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 1015 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 1016 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 1017 "data/maps/RustboroCity/scripts.pory"
	walk_right
# 1018 "data/maps/RustboroCity/scripts.pory"
	walk_down
# 1019 "data/maps/RustboroCity/scripts.pory"
	step_end
# 1020 "data/maps/RustboroCity/scripts.pory"

# 1021 "data/maps/RustboroCity/scripts.pory"
RustboroCity_EventScript_Boy1::
# 1022 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_Text_YouCanHave2On2Battle, MSGBOX_NPC
# 1023 "data/maps/RustboroCity/scripts.pory"
	end
# 1024 "data/maps/RustboroCity/scripts.pory"

# 1025 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_WeShortenItToDevon:
# 1026 "data/maps/RustboroCity/scripts.pory"
	.string "The DEVON CORPORATION…\n"
# 1027 "data/maps/RustboroCity/scripts.pory"
	.string "We all just shorten it to DEVON.\p"
# 1028 "data/maps/RustboroCity/scripts.pory"
	.string "That company makes all sorts of\n"
# 1029 "data/maps/RustboroCity/scripts.pory"
	.string "convenient products.$"
# 1030 "data/maps/RustboroCity/scripts.pory"

# 1031 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_SneakyLookingManWentAroundCorner:
# 1032 "data/maps/RustboroCity/scripts.pory"
	.string "Hm? A sneaky-looking man?\p"
# 1033 "data/maps/RustboroCity/scripts.pory"
	.string "Come to think of it, yes, a shady-\n"
# 1034 "data/maps/RustboroCity/scripts.pory"
	.string "looking guy went around the corner.$"
# 1035 "data/maps/RustboroCity/scripts.pory"

# 1036 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_HaveYouChallengedGym:
# 1037 "data/maps/RustboroCity/scripts.pory"
	.string "Have you taken the POKéMON GYM\n"
# 1038 "data/maps/RustboroCity/scripts.pory"
	.string "challenge?\p"
# 1039 "data/maps/RustboroCity/scripts.pory"
	.string "When you get that shiny GYM BADGE\n"
# 1040 "data/maps/RustboroCity/scripts.pory"
	.string "in hand, I guess TRAINERS begin to\l"
# 1041 "data/maps/RustboroCity/scripts.pory"
	.string "realize what is required of them.$"
# 1042 "data/maps/RustboroCity/scripts.pory"

# 1043 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_HeyThatsRustborosGymBadge:
# 1044 "data/maps/RustboroCity/scripts.pory"
	.string "Hey, that's RUSTBORO's GYM BADGE!\p"
# 1045 "data/maps/RustboroCity/scripts.pory"
	.string "Out of all the POKéMON GYM BADGES,\n"
# 1046 "data/maps/RustboroCity/scripts.pory"
	.string "RUSTBORO's is the coolest, I'd say.$"
# 1047 "data/maps/RustboroCity/scripts.pory"

# 1048 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_YoureNewAroundHere:
# 1049 "data/maps/RustboroCity/scripts.pory"
	.string "Oh? Who might you be?\n"
# 1050 "data/maps/RustboroCity/scripts.pory"
	.string "You're a new face around these parts.\p"
# 1051 "data/maps/RustboroCity/scripts.pory"
	.string "Have you just transferred into the\n"
# 1052 "data/maps/RustboroCity/scripts.pory"
	.string "POKéMON TRAINER'S SCHOOL?$"
# 1053 "data/maps/RustboroCity/scripts.pory"

# 1054 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_GymLeaderIsntEasyWithFire:
# 1055 "data/maps/RustboroCity/scripts.pory"
	.string "I challenged the GYM LEADER, but…\p"
# 1056 "data/maps/RustboroCity/scripts.pory"
	.string "It's not going to be easy winning with\n"
# 1057 "data/maps/RustboroCity/scripts.pory"
	.string "my FIRE-type POKéMON…\p"
# 1058 "data/maps/RustboroCity/scripts.pory"
	.string "FIRE-type POKéMON don't match up\n"
# 1059 "data/maps/RustboroCity/scripts.pory"
	.string "well against ROCK-type POKéMON…$"
# 1060 "data/maps/RustboroCity/scripts.pory"

# 1061 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_MrBrineyWalksInTheTunnel:
# 1062 "data/maps/RustboroCity/scripts.pory"
	.string "The old sailor MR. BRINEY lives in\n"
# 1063 "data/maps/RustboroCity/scripts.pory"
	.string "a cottage by the sea.\p"
# 1064 "data/maps/RustboroCity/scripts.pory"
	.string "He goes for walks in the tunnel every\n"
# 1065 "data/maps/RustboroCity/scripts.pory"
	.string "so often.$"
# 1066 "data/maps/RustboroCity/scripts.pory"

# 1067 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_MrBrineyLovesPeeko:
# 1068 "data/maps/RustboroCity/scripts.pory"
	.string "The old sailor MR. BRINEY lives in\n"
# 1069 "data/maps/RustboroCity/scripts.pory"
	.string "a cottage by the sea.\p"
# 1070 "data/maps/RustboroCity/scripts.pory"
	.string "He said he was going shopping in\n"
# 1071 "data/maps/RustboroCity/scripts.pory"
	.string "SLATEPORT for his pet, PEEKO.\p"
# 1072 "data/maps/RustboroCity/scripts.pory"
	.string "That old sea dog, he must really love\n"
# 1073 "data/maps/RustboroCity/scripts.pory"
	.string "that PEEKO.$"
# 1074 "data/maps/RustboroCity/scripts.pory"

# 1075 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_WowYouHavePokemon:
# 1076 "data/maps/RustboroCity/scripts.pory"
	.string "Wow, you have POKéMON with you, too.\p"
# 1077 "data/maps/RustboroCity/scripts.pory"
	.string "When I get bigger, I'm going to go\n"
# 1078 "data/maps/RustboroCity/scripts.pory"
	.string "places with POKéMON, too.$"
# 1079 "data/maps/RustboroCity/scripts.pory"

# 1080 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_CatchRarePokemonIfIGoToSchool:
# 1081 "data/maps/RustboroCity/scripts.pory"
	.string "POKéMON TRAINER'S SCHOOL!\p"
# 1082 "data/maps/RustboroCity/scripts.pory"
	.string "If I go to this school, will I be able\n"
# 1083 "data/maps/RustboroCity/scripts.pory"
	.string "to catch rare POKéMON easily?$"
# 1084 "data/maps/RustboroCity/scripts.pory"

# 1085 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_PokemonCanChangeLookFromExp:
# 1086 "data/maps/RustboroCity/scripts.pory"
	.string "If a POKéMON gains experience in\n"
# 1087 "data/maps/RustboroCity/scripts.pory"
	.string "battles, it can sometimes change in\l"
# 1088 "data/maps/RustboroCity/scripts.pory"
	.string "the way it looks.$"
# 1089 "data/maps/RustboroCity/scripts.pory"

# 1090 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_PokemonChangeShape:
# 1091 "data/maps/RustboroCity/scripts.pory"
	.string "A POKéMON changes shape?\n"
# 1092 "data/maps/RustboroCity/scripts.pory"
	.string "If one did that, I would be shocked!$"
# 1093 "data/maps/RustboroCity/scripts.pory"

# 1094 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_TradePokemonGrowFast:
# 1095 "data/maps/RustboroCity/scripts.pory"
	.string "A POKéMON you get in a trade from\n"
# 1096 "data/maps/RustboroCity/scripts.pory"
	.string "someone grows fast.\p"
# 1097 "data/maps/RustboroCity/scripts.pory"
	.string "But if you don't have certain GYM\n"
# 1098 "data/maps/RustboroCity/scripts.pory"
	.string "BADGES, it may not obey you…$"
# 1099 "data/maps/RustboroCity/scripts.pory"

# 1100 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_OutOfTheWay:
# 1101 "data/maps/RustboroCity/scripts.pory"
	.string "Get out!\n"
# 1102 "data/maps/RustboroCity/scripts.pory"
	.string "Out of the way!$"
# 1103 "data/maps/RustboroCity/scripts.pory"

# 1104 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_WaitDontTakeMyGoods:
# 1105 "data/maps/RustboroCity/scripts.pory"
	.string "Wait! Pleeeaaase!\p"
# 1106 "data/maps/RustboroCity/scripts.pory"
	.string "Don't take my GOODS!$"
# 1107 "data/maps/RustboroCity/scripts.pory"

# 1108 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_HelpMeIWasRobbed:
# 1109 "data/maps/RustboroCity/scripts.pory"
	.string "Oh, it's you!\p"
# 1110 "data/maps/RustboroCity/scripts.pory"
	.string "You're that fantastic TRAINER who\n"
# 1111 "data/maps/RustboroCity/scripts.pory"
	.string "helped me in PETALBURG WOODS!\p"
# 1112 "data/maps/RustboroCity/scripts.pory"
	.string "Help me! I was robbed by TEAM AQUA!\n"
# 1113 "data/maps/RustboroCity/scripts.pory"
	.string "I have to get the DEVON GOODS back!\p"
# 1114 "data/maps/RustboroCity/scripts.pory"
	.string "If I don't…\n"
# 1115 "data/maps/RustboroCity/scripts.pory"
	.string "I'm going to be in serious trouble.$"
# 1116 "data/maps/RustboroCity/scripts.pory"

# 1117 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_ShadyCharacterTookOffTowardsTunnel:
# 1118 "data/maps/RustboroCity/scripts.pory"
	.string "That shady character, I think he took\n"
# 1119 "data/maps/RustboroCity/scripts.pory"
	.string "off towards the tunnel over there.$"
# 1120 "data/maps/RustboroCity/scripts.pory"

# 1121 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_YouGotItThankYou:
# 1122 "data/maps/RustboroCity/scripts.pory"
	.string "Oh! How did it go?\n"
# 1123 "data/maps/RustboroCity/scripts.pory"
	.string "The DEVON GOODS?\p"
# 1124 "data/maps/RustboroCity/scripts.pory"
	.string "You did!\n"
# 1125 "data/maps/RustboroCity/scripts.pory"
	.string "You got them back!\p"
# 1126 "data/maps/RustboroCity/scripts.pory"
	.string "You really are a great TRAINER!\p"
# 1127 "data/maps/RustboroCity/scripts.pory"
	.string "I know! As my thanks, I'll give you\n"
# 1128 "data/maps/RustboroCity/scripts.pory"
	.string "another GREAT BALL!$"
# 1129 "data/maps/RustboroCity/scripts.pory"

# 1130 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_YoureLoadedWithItems:
# 1131 "data/maps/RustboroCity/scripts.pory"
	.string "You're loaded with items.\n"
# 1132 "data/maps/RustboroCity/scripts.pory"
	.string "I can't give you this GREAT BALL.$"
# 1133 "data/maps/RustboroCity/scripts.pory"

# 1134 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_PleaseComeWithMe:
# 1135 "data/maps/RustboroCity/scripts.pory"
	.string "Excuse me, please!\n"
# 1136 "data/maps/RustboroCity/scripts.pory"
	.string "Please come with me!$"
# 1137 "data/maps/RustboroCity/scripts.pory"

# 1138 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_MayHiLetsRegister:
# 1139 "data/maps/RustboroCity/scripts.pory"
	.string "MAY: Oh, hi, {PLAYER}{KUN}!\p"
# 1140 "data/maps/RustboroCity/scripts.pory"
	.string "You had a MATCH CALL feature put\n"
# 1141 "data/maps/RustboroCity/scripts.pory"
	.string "on your POKéNAV!\p"
# 1142 "data/maps/RustboroCity/scripts.pory"
	.string "Let's register each other so we can\n"
# 1143 "data/maps/RustboroCity/scripts.pory"
	.string "contact one another anytime!\p"
# 1144 "data/maps/RustboroCity/scripts.pory"
	.string "… … … … … …$"
# 1145 "data/maps/RustboroCity/scripts.pory"

# 1146 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_RegisteredMay:
# 1147 "data/maps/RustboroCity/scripts.pory"
	.string "Registered MAY\n"
# 1148 "data/maps/RustboroCity/scripts.pory"
	.string "in the POKéNAV.$"
# 1149 "data/maps/RustboroCity/scripts.pory"

# 1150 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_MayPassedBrineyWantToBattle:
# 1151 "data/maps/RustboroCity/scripts.pory"
	.string "MAY: Oh, by the way, I passed\n"
# 1152 "data/maps/RustboroCity/scripts.pory"
	.string "MR. BRINEY in PETALBURG WOODS.\p"
# 1153 "data/maps/RustboroCity/scripts.pory"
	.string "I guess he's on his way home to his\n"
# 1154 "data/maps/RustboroCity/scripts.pory"
	.string "cottage by the sea.\p"
# 1155 "data/maps/RustboroCity/scripts.pory"
	.string "How's your POKéDEX coming along,\n"
# 1156 "data/maps/RustboroCity/scripts.pory"
	.string "{PLAYER}{KUN}? Mine's looking pretty decent!\p"
# 1157 "data/maps/RustboroCity/scripts.pory"
	.string "So…\n"
# 1158 "data/maps/RustboroCity/scripts.pory"
	.string "How about a little battle?$"
# 1159 "data/maps/RustboroCity/scripts.pory"

# 1160 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_MayOhHaventRaisedPokemonEnough:
# 1161 "data/maps/RustboroCity/scripts.pory"
	.string "MAY: Oh, what's the matter?\p"
# 1162 "data/maps/RustboroCity/scripts.pory"
	.string "Haven't you caught or raised your\n"
# 1163 "data/maps/RustboroCity/scripts.pory"
	.string "POKéMON very much?\p"
# 1164 "data/maps/RustboroCity/scripts.pory"
	.string "That's not very good for a TRAINER!$"
# 1165 "data/maps/RustboroCity/scripts.pory"

# 1166 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_MayWantToBattle:
# 1167 "data/maps/RustboroCity/scripts.pory"
	.string "MAY: So, what do you think?\n"
# 1168 "data/maps/RustboroCity/scripts.pory"
	.string "How about a little battle here?$"
# 1169 "data/maps/RustboroCity/scripts.pory"

# 1170 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_MayImNotGoingToLose:
# 1171 "data/maps/RustboroCity/scripts.pory"
	.string "MAY: You just became a TRAINER,\n"
# 1172 "data/maps/RustboroCity/scripts.pory"
	.string "{PLAYER}{KUN}. I'm not going to lose!$"
# 1173 "data/maps/RustboroCity/scripts.pory"

# 1174 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_MayDefeat:
# 1175 "data/maps/RustboroCity/scripts.pory"
	.string "Yikes!\n"
# 1176 "data/maps/RustboroCity/scripts.pory"
	.string "You're better than I expected!$"
# 1177 "data/maps/RustboroCity/scripts.pory"

# 1178 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_MayMrBrineyHint:
# 1179 "data/maps/RustboroCity/scripts.pory"
	.string "MAY: Oh, by the way, MR. BRINEY, who\n"
# 1180 "data/maps/RustboroCity/scripts.pory"
	.string "I just passed…\p"
# 1181 "data/maps/RustboroCity/scripts.pory"
	.string "{PLAYER}{KUN}, you just moved here so you\n"
# 1182 "data/maps/RustboroCity/scripts.pory"
	.string "might not know this, but MR. BRINEY\l"
# 1183 "data/maps/RustboroCity/scripts.pory"
	.string "was once a revered seafarer.$"
# 1184 "data/maps/RustboroCity/scripts.pory"

# 1185 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_BrendanHiLetsRegister:
# 1186 "data/maps/RustboroCity/scripts.pory"
	.string "BRENDAN: Oh, hey, {PLAYER}!\p"
# 1187 "data/maps/RustboroCity/scripts.pory"
	.string "You had a MATCH CALL feature put\n"
# 1188 "data/maps/RustboroCity/scripts.pory"
	.string "on your POKéNAV! Cool!\p"
# 1189 "data/maps/RustboroCity/scripts.pory"
	.string "Let's register each other so we can\n"
# 1190 "data/maps/RustboroCity/scripts.pory"
	.string "get in touch anytime!\p"
# 1191 "data/maps/RustboroCity/scripts.pory"
	.string "… … … … … …$"
# 1192 "data/maps/RustboroCity/scripts.pory"

# 1193 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_RegisteredBrendan:
# 1194 "data/maps/RustboroCity/scripts.pory"
	.string "Registered BRENDAN\n"
# 1195 "data/maps/RustboroCity/scripts.pory"
	.string "in the POKéNAV.$"
# 1196 "data/maps/RustboroCity/scripts.pory"

# 1197 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_BrendanPassedBrineyWantToBattle:
# 1198 "data/maps/RustboroCity/scripts.pory"
	.string "BRENDAN: By the way, {PLAYER}, I walked\n"
# 1199 "data/maps/RustboroCity/scripts.pory"
	.string "by MR. BRINEY in PETALBURG WOODS.\p"
# 1200 "data/maps/RustboroCity/scripts.pory"
	.string "I bet he was on his way home to his\n"
# 1201 "data/maps/RustboroCity/scripts.pory"
	.string "cottage by the sea.\p"
# 1202 "data/maps/RustboroCity/scripts.pory"
	.string "{PLAYER}, how's your POKéDEX?\n"
# 1203 "data/maps/RustboroCity/scripts.pory"
	.string "Have you filled in any pages yet?\p"
# 1204 "data/maps/RustboroCity/scripts.pory"
	.string "Mine rules.\p"
# 1205 "data/maps/RustboroCity/scripts.pory"
	.string "Want to have a battle to test how\n"
# 1206 "data/maps/RustboroCity/scripts.pory"
	.string "far you've progressed?$"
# 1207 "data/maps/RustboroCity/scripts.pory"

# 1208 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_BrendanNoConfidenceInPokemon:
# 1209 "data/maps/RustboroCity/scripts.pory"
	.string "BRENDAN: What's the matter? Don't have\n"
# 1210 "data/maps/RustboroCity/scripts.pory"
	.string "any confidence in your POKéMON?$"
# 1211 "data/maps/RustboroCity/scripts.pory"

# 1212 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_BrendanWantToBattle:
# 1213 "data/maps/RustboroCity/scripts.pory"
	.string "BRENDAN: What's up?\n"
# 1214 "data/maps/RustboroCity/scripts.pory"
	.string "Want to have a battle with me?$"
# 1215 "data/maps/RustboroCity/scripts.pory"

# 1216 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_BrendanIWontGoEasy:
# 1217 "data/maps/RustboroCity/scripts.pory"
	.string "BRENDAN: I know you just became\n"
# 1218 "data/maps/RustboroCity/scripts.pory"
	.string "a TRAINER, but I won't go easy!$"
# 1219 "data/maps/RustboroCity/scripts.pory"

# 1220 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_BrendanDefeat:
# 1221 "data/maps/RustboroCity/scripts.pory"
	.string "Hmm…\n"
# 1222 "data/maps/RustboroCity/scripts.pory"
	.string "You're pretty good.$"
# 1223 "data/maps/RustboroCity/scripts.pory"

# 1224 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_BrendanMrBrineyHint:
# 1225 "data/maps/RustboroCity/scripts.pory"
	.string "BRENDAN: By the way, you know\n"
# 1226 "data/maps/RustboroCity/scripts.pory"
	.string "MR. BRINEY? The guy I just passed?\p"
# 1227 "data/maps/RustboroCity/scripts.pory"
	.string "I bet you didn't know this, since you\n"
# 1228 "data/maps/RustboroCity/scripts.pory"
	.string "just moved here, {PLAYER}, but\l"
# 1229 "data/maps/RustboroCity/scripts.pory"
	.string "MR. BRINEY was once a great sailor.$"
# 1230 "data/maps/RustboroCity/scripts.pory"

# 1231 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_TunnelNearingCompletion:
# 1232 "data/maps/RustboroCity/scripts.pory"
	.string "“Timesaving tunnel nearing\n"
# 1233 "data/maps/RustboroCity/scripts.pory"
	.string "completion!”\p"
# 1234 "data/maps/RustboroCity/scripts.pory"
	.string "…Is what it says on the sign, but\n"
# 1235 "data/maps/RustboroCity/scripts.pory"
	.string "there's also a big “X” splashed\l"
# 1236 "data/maps/RustboroCity/scripts.pory"
	.string "across it in red paint…$"
# 1237 "data/maps/RustboroCity/scripts.pory"

# 1238 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_DevonCorpSign:
# 1239 "data/maps/RustboroCity/scripts.pory"
	.string "DEVON CORPORATION\p"
# 1240 "data/maps/RustboroCity/scripts.pory"
	.string "“For all your living needs, we make\n"
# 1241 "data/maps/RustboroCity/scripts.pory"
	.string "it all.”$"
# 1242 "data/maps/RustboroCity/scripts.pory"

# 1243 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_GymSign:
# 1244 "data/maps/RustboroCity/scripts.pory"
	.string "RUSTBORO CITY POKéMON GYM\n"
# 1245 "data/maps/RustboroCity/scripts.pory"
	.string "LEADER: ROXANNE\p"
# 1246 "data/maps/RustboroCity/scripts.pory"
	.string "“The ROCK-loving honors student!”$"
# 1247 "data/maps/RustboroCity/scripts.pory"

# 1248 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_DevonCorpBranchOfficeSign:
# 1249 "data/maps/RustboroCity/scripts.pory"
	.string "DEVON CORP. BRANCH OFFICE\p"
# 1250 "data/maps/RustboroCity/scripts.pory"
	.string "“Access limited to DEVON employees\n"
# 1251 "data/maps/RustboroCity/scripts.pory"
	.string "and authorized personnel.”$"
# 1252 "data/maps/RustboroCity/scripts.pory"

# 1253 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_CitySign:
# 1254 "data/maps/RustboroCity/scripts.pory"
	.string "RUSTBORO CITY\p"
# 1255 "data/maps/RustboroCity/scripts.pory"
	.string "“The city probing the integration of\n"
# 1256 "data/maps/RustboroCity/scripts.pory"
	.string "nature and science.”$"
# 1257 "data/maps/RustboroCity/scripts.pory"

# 1258 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_TrainersSchoolSign:
# 1259 "data/maps/RustboroCity/scripts.pory"
	.string "POKéMON TRAINER'S SCHOOL\p"
# 1260 "data/maps/RustboroCity/scripts.pory"
	.string "“We'll teach you anything about\n"
# 1261 "data/maps/RustboroCity/scripts.pory"
	.string "POKéMON!”$"
# 1262 "data/maps/RustboroCity/scripts.pory"

# 1263 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_CuttersHouse:
# 1264 "data/maps/RustboroCity/scripts.pory"
	.string "CUTTER'S HOUSE$"
# 1265 "data/maps/RustboroCity/scripts.pory"

# 1266 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_DevelopedNewPokenavFeature:
# 1267 "data/maps/RustboroCity/scripts.pory"
	.string "I've been developing an added feature\n"
# 1268 "data/maps/RustboroCity/scripts.pory"
	.string "for the POKéNAV…\p"
# 1269 "data/maps/RustboroCity/scripts.pory"
	.string "And it turned out great!\p"
# 1270 "data/maps/RustboroCity/scripts.pory"
	.string "{PLAYER}, may I see that POKéNAV?\n"
# 1271 "data/maps/RustboroCity/scripts.pory"
	.string "The one our PRESIDENT gave you?$"
# 1272 "data/maps/RustboroCity/scripts.pory"

# 1273 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_AddedMatchCallPleaseCallMrStone:
# 1274 "data/maps/RustboroCity/scripts.pory"
	.string "There you go, {PLAYER}!\p"
# 1275 "data/maps/RustboroCity/scripts.pory"
	.string "I added a new feature named\n"
# 1276 "data/maps/RustboroCity/scripts.pory"
	.string "MATCH CALL to your POKéNAV.\p"
# 1277 "data/maps/RustboroCity/scripts.pory"
	.string "Using the MATCH CALL feature,\n"
# 1278 "data/maps/RustboroCity/scripts.pory"
	.string "you can chat with people who have\l"
# 1279 "data/maps/RustboroCity/scripts.pory"
	.string "been registered in your POKéNAV.\p"
# 1280 "data/maps/RustboroCity/scripts.pory"
	.string "{PLAYER}, our PRESIDENT STONE should\n"
# 1281 "data/maps/RustboroCity/scripts.pory"
	.string "be registered in your POKéNAV.\p"
# 1282 "data/maps/RustboroCity/scripts.pory"
	.string "Test it out.\n"
# 1283 "data/maps/RustboroCity/scripts.pory"
	.string "Please give our PRESIDENT a call.$"
# 1284 "data/maps/RustboroCity/scripts.pory"

# 1285 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_PleaseSelectPokenav:
# 1286 "data/maps/RustboroCity/scripts.pory"
	.string "Please select the POKéNAV.$"
# 1287 "data/maps/RustboroCity/scripts.pory"

# 1288 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_IdBetterGetBackToWork:
# 1289 "data/maps/RustboroCity/scripts.pory"
	.string "Okay, I'd better get back to work.\n"
# 1290 "data/maps/RustboroCity/scripts.pory"
	.string "Please take care, {PLAYER}!$"
# 1291 "data/maps/RustboroCity/scripts.pory"

# 1292 "data/maps/RustboroCity/scripts.pory"
RustboroCity_Text_YouCanHave2On2Battle:
# 1293 "data/maps/RustboroCity/scripts.pory"
	.string "Did you know this?\p"
# 1294 "data/maps/RustboroCity/scripts.pory"
	.string "You can have a 2-on-2 battle even\n"
# 1295 "data/maps/RustboroCity/scripts.pory"
	.string "if you're not with another TRAINER.\p"
# 1296 "data/maps/RustboroCity/scripts.pory"
	.string "If you catch the eyes of two TRAINERS\n"
# 1297 "data/maps/RustboroCity/scripts.pory"
	.string "when you have two or more POKéMON,\l"
# 1298 "data/maps/RustboroCity/scripts.pory"
	.string "they'll both challenge you.\p"
# 1299 "data/maps/RustboroCity/scripts.pory"
	.string "Don't you think it'd be cool if you\n"
# 1300 "data/maps/RustboroCity/scripts.pory"
	.string "could beat two TRAINERS by yourself?$"

RustboroCity_EventScript_LectureInformant::
# 1305 "data/maps/RustboroCity/scripts.pory"
	lock
# 1306 "data/maps/RustboroCity/scripts.pory"
	faceplayer
# 1307 "data/maps/RustboroCity/scripts.pory"
	msgbox RustboroCity_EventScript_LectureInformant_Text_0
# 1308 "data/maps/RustboroCity/scripts.pory"
	release
	end


RustburoRival_GiveBottleCap::
# 1313 "data/maps/RustboroCity/scripts.pory"
	msgbox RustburoRival_GiveBottleCap_Text_0
# 1314 "data/maps/RustboroCity/scripts.pory"
	msgbox RustburoRival_GiveBottleCap_Text_1
# 1315 "data/maps/RustboroCity/scripts.pory"
	giveitem ITEM_BOTTLE_CAP
# 1316 "data/maps/RustboroCity/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq RustburoRival_GiveBottleCap_1
	return

RustburoRival_GiveBottleCap_1:
# 1317 "data/maps/RustboroCity/scripts.pory"
	call Common_EventScript_ShowBagIsFull
	return


RustboroCity_EventScript_LectureInformant_Text_0:
# 1307 "data/maps/RustboroCity/scripts.pory"
	.string "Roxanne's away from the Gym right now.\n"
	.string "She's doing a guest lecture at the\l"
	.string "Trainer's School.$"

RustburoRival_GiveBottleCap_Text_0:
# 1313 "data/maps/RustboroCity/scripts.pory"
	.string "Your skill as a trainer is growing so\n"
	.string "fast.$"

RustburoRival_GiveBottleCap_Text_1:
# 1314 "data/maps/RustboroCity/scripts.pory"
	.string "I found a Bottle Cap, but I don't think\n"
	.string "my team is ready for Hyper Training.\l"
	.string "Here, maybe you'll make better use of\l"
	.string "it!$"
