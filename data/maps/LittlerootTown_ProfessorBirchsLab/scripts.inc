# 1 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 2 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
.set LOCALID_AIDE, 1
# 3 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
.set LOCALID_BIRCH, 2
# 4 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
.set LOCALID_RIVAL, 3
# 5 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
.set LOCALID_BALL_CYNDAQUIL, 4
# 6 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
.set LOCALID_BALL_TOTODILE, 5
# 7 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
.set LOCALID_BALL_CHIKORITA, 6
# 8 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 9 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_MapScripts::
# 10 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_ProfessorBirchsLab_OnTransition
# 11 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_ProfessorBirchsLab_OnWarp
# 12 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_ProfessorBirchsLab_OnFrame
# 13 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.byte 0
# 14 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 15 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ State descriptions for VAR_DEX_UPGRADE_JOHTO_STARTER_STATE
# 16 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 1: Beat Elite Four, Dex upgrade ready
# 17 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 2: Received National Dex
# 18 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 3: Left lab after receiving National Dex
# 19 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 4: Entered lab after catching all Hoenn mons
# 20 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 5: Birch told player to choose Johto starter
# 21 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 6: Chose Johto starter
# 22 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 23 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ State descriptions for VAR_BIRCH_LAB_STATE
# 24 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 1: Never occurs
# 25 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 2: Chose starter
# 26 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 3: Received starter in lab
# 27 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 4: Defeated rival on Route 103
# 28 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 5: Received pokedex
# 29 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 30 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_OnTransition:
# 31 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_SetupRivalGfxId
# 32 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call ProfBirch_EventScript_UpdateLocation
# 33 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_SetAfterJohtoStarterLayout
# 34 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_SetJohtoStarterLayout
# 35 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3, LittlerootTown_ProfessorBirchsLab_EventScript_CheckReadyForJohtoStarter
# 36 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 37 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 38 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_CheckReadyForJohtoStarter::
# 39 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	specialvar VAR_RESULT, HasAllHoennMons
# 40 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, LittlerootTown_ProfessorBirchsLab_EventScript_SetReadyForJohtoStarter
# 41 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectmovementtype LOCALID_RIVAL, MOVEMENT_TYPE_WANDER_UP_AND_DOWN
# 42 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectxyperm LOCALID_RIVAL, 5, 10
# 43 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 44 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 45 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SetReadyForJohtoStarter::
# 46 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4
# 47 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_SetJohtoStarterLayout
# 48 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 49 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SetJohtoStarterLayout::
# 50 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setmaplayoutindex LAYOUT_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB_WITH_TABLE
# 51 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 52 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 53 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SetAfterJohtoStarterLayout::
# 54 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setmaplayoutindex LAYOUT_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB_WITH_TABLE
# 55 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectmovementtype LOCALID_RIVAL, MOVEMENT_TYPE_WANDER_UP_AND_DOWN
# 56 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectxyperm LOCALID_RIVAL, 5, 10
# 57 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 58 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 59 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_OnWarp:
# 60 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_BIRCH_LAB_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_SetPlayerPosForReceiveStarter
# 61 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForDexUpgrade
# 62 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForDexUpgrade
# 63 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3, LittlerootTown_ProfessorBirchsLab_EventScript_AddRivalObject
# 64 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_AddRivalObject
# 65 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForJohtoStarters
# 66 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForJohtoStarters
# 67 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.2byte 0
# 68 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 69 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SetPlayerPosForReceiveStarter::
# 70 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 71 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 72 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 73 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForDexUpgrade::
# 74 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	turnobject OBJ_EVENT_ID_PLAYER, DIR_NORTH
# 75 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	addobject LOCALID_BIRCH
# 76 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	addobject LOCALID_RIVAL
# 77 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	turnobject LOCALID_RIVAL, DIR_NORTH
# 78 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectxy LOCALID_RIVAL, 5, 5
# 79 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	turnobject LOCALID_BIRCH, DIR_SOUTH
# 80 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectxy LOCALID_BIRCH, 6, 4
# 81 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	turnobject LOCALID_AIDE, DIR_EAST
# 82 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectxy LOCALID_AIDE, 10, 10
# 83 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 84 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 85 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_AddRivalObject::
# 86 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	addobject LOCALID_RIVAL
# 87 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 88 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 89 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForJohtoStarters::
# 90 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	addobject LOCALID_BALL_CYNDAQUIL
# 91 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	addobject LOCALID_BALL_TOTODILE
# 92 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	addobject LOCALID_BALL_CHIKORITA
# 93 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	addobject LOCALID_RIVAL
# 94 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	turnobject LOCALID_BALL_CYNDAQUIL, DIR_SOUTH
# 95 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectxy LOCALID_BALL_CYNDAQUIL, 8, 4
# 96 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	turnobject LOCALID_BALL_TOTODILE, DIR_SOUTH
# 97 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectxy LOCALID_BALL_TOTODILE, 9, 4
# 98 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	turnobject LOCALID_BALL_CHIKORITA, DIR_SOUTH
# 99 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectxy LOCALID_BALL_CHIKORITA, 10, 4
# 100 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	turnobject LOCALID_BIRCH, DIR_SOUTH
# 101 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectxy LOCALID_BIRCH, 6, 4
# 102 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	turnobject LOCALID_RIVAL, DIR_EAST
# 103 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectxy LOCALID_RIVAL, 5, 5
# 104 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 105 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 106 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_OnFrame:
# 107 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_BIRCH_LAB_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_GiveStarterEvent
# 108 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_BIRCH_LAB_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_GivePokedexEvent
# 109 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_ProfessorBirchsLab_EventScript_UpgradeToNationalDex
# 110 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_ChooseJohtoStarter
# 111 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.2byte 0
# 112 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 113 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
@ The starter is technically given prior to this on Route 101 by special ChooseStarter
# 114 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
@ This is just where the game tells you its yours and lets you nickname it
# 115 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_GiveStarterEvent::
# 116 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	lockall
# 117 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	bufferleadmonspeciesname STR_VAR_1
# 118 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	message LittlerootTown_ProfessorBirchsLab_Text_LikeYouToHavePokemon
# 119 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmessage
# 120 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 121 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitfanfare
# 122 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_WhyNotGiveNicknameToMon, MSGBOX_YESNO
# 123 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, LittlerootTown_ProfessorBirchsLab_EventScript_NicknameStarter
# 124 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_GoSeeRival
# 125 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 126 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 127 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_NicknameStarter::
# 128 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_0x8004, 0
# 129 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 130 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GoSeeRival
# 131 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 132 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 133 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_GoSeeRival::
# 134 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MightBeGoodIdeaToGoSeeRival, MSGBOX_YESNO
# 135 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, LittlerootTown_ProfessorBirchsLab_EventScript_AgreeToSeeRival
# 136 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_DeclineSeeingRival
# 137 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 138 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 139 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_AgreeToSeeRival::
# 140 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GetRivalToTeachYou, MSGBOX_DEFAULT
# 141 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	clearflag FLAG_HIDE_ROUTE_101_BOY
# 142 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_BIRCH_LAB_STATE, 3
# 143 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
# 144 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 145 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 146 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_DeclineSeeingRival::
# 147 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DontBeThatWay, MSGBOX_YESNO
# 148 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, LittlerootTown_ProfessorBirchsLab_EventScript_AgreeToSeeRival
# 149 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_DeclineSeeingRival
# 150 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 151 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 152 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_GivePokedexEvent::
# 153 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	lockall
# 154 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnterLabForPokedex
# 155 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 156 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GivePokedex
# 157 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 158 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 159 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnterLabForPokedex:
# 160 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 161 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 162 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 163 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 164 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 165 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 166 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 167 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	step_end
# 168 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 169 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_UpgradeToNationalDex::
# 170 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	lockall
# 171 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay 30
# 172 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_OtherRegionsUpgradeToNational, MSGBOX_DEFAULT
# 173 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	closemessage
# 174 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_BIRCH, LittlerootTown_ProfessorBirchsLab_Movement_BirchRetrievePokedexes
# 175 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 176 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay 20
# 177 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playse SE_CLICK
# 178 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay 10
# 179 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playse SE_CLICK
# 180 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay 10
# 181 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playse SE_CLICK
# 182 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay 10
# 183 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playse SE_CLICK
# 184 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay 20
# 185 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFasterRight
# 186 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
# 187 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 188 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	checkplayergender
# 189 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayUpgradeComment
# 190 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanUpgradeComment
# 191 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playse SE_PC_ON
# 192 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitse
# 193 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay 20
# 194 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_BIRCH, LittlerootTown_ProfessorBirchsLab_Movement_BirchReturnPokedex
# 195 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 196 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFasterUp
# 197 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 198 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 199 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_OkayAllDone, MSGBOX_DEFAULT
# 200 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 201 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	message LittlerootTown_ProfessorBirchsLab_Text_PokedexUpgradedToNational
# 202 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmessage
# 203 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitfanfare
# 204 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_NATIONAL_DEX
# 205 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	special EnableNationalPokedex
# 206 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting2, MSGBOX_DEFAULT
# 207 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	closemessage
# 208 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCH
# 209 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_RIVAL
# 210 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2
# 211 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_SCOTT_BF_CALL_STEP_COUNTER, 0
# 212 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SCOTT_CALL_BATTLE_FRONTIER
# 213 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
# 214 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 215 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 216 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_MayUpgradeComment::
# 217 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayUpgradeSoCool, MSGBOX_DEFAULT
# 218 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	closemessage
# 219 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 220 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 221 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_BrendanUpgradeComment::
# 222 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanYouCanThankMe, MSGBOX_DEFAULT
# 223 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	closemessage
# 224 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 225 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 226 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Movement_BirchRetrievePokedexes:
# 227 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_left
# 228 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_in_place_faster_down
# 229 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay_16
# 230 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay_16
# 231 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_right
# 232 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_in_place_faster_down
# 233 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay_16
# 234 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay_16
# 235 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_right
# 236 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_down
# 237 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_down
# 238 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_down
# 239 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_down
# 240 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_right
# 241 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_right
# 242 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_right
# 243 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_in_place_faster_up
# 244 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	step_end
# 245 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 246 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Movement_BirchReturnPokedex:
# 247 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_left
# 248 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_left
# 249 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_left
# 250 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 251 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 252 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 253 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 254 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_left
# 255 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_in_place_faster_down
# 256 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	step_end
# 257 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 258 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_ChooseJohtoStarter::
# 259 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	lockall
# 260 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnterLabForJohtoStarter
# 261 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 262 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CompletedDexChoosePokemon, MSGBOX_DEFAULT
# 263 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5
# 264 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
# 265 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 266 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 267 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnterLabForJohtoStarter:
# 268 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 269 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 270 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 271 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 272 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 273 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 274 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 275 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	step_end
# 276 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 277 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_Aide::
# 278 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	lock
# 279 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	faceplayer
# 280 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_ge VAR_BIRCH_LAB_STATE, 3, LittlerootTown_ProfessorBirchsLab_EventScript_AideReceivedStarter
# 281 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_set FLAG_BIRCH_AIDE_MET, LittlerootTown_ProfessorBirchsLab_EventScript_AideAlreadyMet
# 282 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchAwayOnFieldwork, MSGBOX_DEFAULT
# 283 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_BIRCH_AIDE_MET
# 284 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 285 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 286 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 287 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_AideAlreadyMet::
# 288 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchIsntOneForDeskWork, MSGBOX_DEFAULT
# 289 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 290 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 291 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 292 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_AideReceivedStarter::
# 293 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchEnjoysRivalsHelpToo, MSGBOX_DEFAULT
# 294 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 295 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 296 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 297 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_Cyndaquil::
# 298 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 299 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_AlreadyChoseJohtoStarter
# 300 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterRight
# 301 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 302 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	showmonpic SPECIES_CYNDAQUIL, 10, 3
# 303 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_YoullTakeCyndaquil, MSGBOX_YESNO
# 304 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_TakeYourTime
# 305 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GiveCyndaquil
# 306 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 307 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 308 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_Totodile::
# 309 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 310 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_AlreadyChoseJohtoStarter
# 311 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterRight
# 312 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 313 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	showmonpic SPECIES_TOTODILE, 10, 3
# 314 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_YoullTakeTotodile, MSGBOX_YESNO
# 315 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_TakeYourTime
# 316 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GiveTotodile
# 317 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 318 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 319 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_Chikorita::
# 320 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 321 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_AlreadyChoseJohtoStarter
# 322 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterRight
# 323 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 324 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	showmonpic SPECIES_CHIKORITA, 10, 3
# 325 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_YoullTakeChikorita, MSGBOX_YESNO
# 326 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_TakeYourTime
# 327 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GiveChikorita
# 328 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 329 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 330 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_AlreadyChoseJohtoStarter::
# 331 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BetterLeaveOthersAlone, MSGBOX_DEFAULT
# 332 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
# 333 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 334 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 335 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_TakeYourTime::
# 336 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	hidemonpic
# 337 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_TakeYourTimeAllInvaluable, MSGBOX_DEFAULT
# 338 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
# 339 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 340 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 341 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_GiveCyndaquil::
# 342 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_CYNDAQUIL
# 343 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CYNDAQUIL
# 344 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_CYNDAQUIL, 5
# 345 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, LittlerootTown_ProfessorBirchsLab_EventScript_SendCyndaquilToParty
# 346 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, LittlerootTown_ProfessorBirchsLab_EventScript_SendCyndaquilToPC
# 347 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	hidemonpic
# 348 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto Common_EventScript_NoMoreRoomForPokemon
# 349 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 350 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 351 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SendCyndaquilToParty::
# 352 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
# 353 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	removeobject LOCALID_BALL_CYNDAQUIL
# 354 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 355 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedCyndaquil
# 356 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 357 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 358 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedCyndaquil
# 359 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 360 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 361 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SendCyndaquilToPC::
# 362 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
# 363 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	removeobject LOCALID_BALL_CYNDAQUIL
# 364 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 365 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_CyndaquilTransferredToPC
# 366 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_NameReceivedBoxMon
# 367 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_CyndaquilTransferredToPC
# 368 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 369 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 370 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_CyndaquilTransferredToPC::
# 371 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_TransferredToPC
# 372 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedCyndaquil
# 373 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 374 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 375 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedCyndaquil::
# 376 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	hidemonpic
# 377 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting, MSGBOX_DEFAULT
# 378 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
# 379 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
# 380 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 381 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 382 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_GiveTotodile::
# 383 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_TOTODILE
# 384 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TOTODILE
# 385 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_TOTODILE, 5
# 386 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, LittlerootTown_ProfessorBirchsLab_EventScript_SendTotodileToParty
# 387 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, LittlerootTown_ProfessorBirchsLab_EventScript_SendTotodileToPC
# 388 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	hidemonpic
# 389 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto Common_EventScript_NoMoreRoomForPokemon
# 390 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 391 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 392 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SendTotodileToParty::
# 393 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
# 394 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	removeobject LOCALID_BALL_TOTODILE
# 395 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 396 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedTotodile
# 397 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 398 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 399 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedTotodile
# 400 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 401 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 402 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SendTotodileToPC::
# 403 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
# 404 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	removeobject LOCALID_BALL_TOTODILE
# 405 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 406 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_TotodileTransferredToPC
# 407 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_NameReceivedBoxMon
# 408 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TotodileTransferredToPC
# 409 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 410 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 411 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_TotodileTransferredToPC::
# 412 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_TransferredToPC
# 413 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedTotodile
# 414 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 415 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 416 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedTotodile::
# 417 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	hidemonpic
# 418 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting, MSGBOX_DEFAULT
# 419 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
# 420 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
# 421 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 422 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 423 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_GiveChikorita::
# 424 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_CHIKORITA
# 425 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CHIKORITA
# 426 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_CHIKORITA, 5
# 427 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, LittlerootTown_ProfessorBirchsLab_EventScript_SendChikoritaToParty
# 428 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, LittlerootTown_ProfessorBirchsLab_EventScript_SendChikoritaToPC
# 429 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	hidemonpic
# 430 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto Common_EventScript_NoMoreRoomForPokemon
# 431 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 432 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 433 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SendChikoritaToParty::
# 434 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
# 435 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	removeobject LOCALID_BALL_CHIKORITA
# 436 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 437 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedChikorita
# 438 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 439 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 440 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedChikorita
# 441 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 442 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 443 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SendChikoritaToPC::
# 444 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
# 445 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	removeobject LOCALID_BALL_CHIKORITA
# 446 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 447 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_ChikoritaTransferredToPC
# 448 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_NameReceivedBoxMon
# 449 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ChikoritaTransferredToPC
# 450 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 451 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 452 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_ChikoritaTransferredToPC::
# 453 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_TransferredToPC
# 454 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedChikorita
# 455 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 456 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 457 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedChikorita::
# 458 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	hidemonpic
# 459 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting, MSGBOX_DEFAULT
# 460 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
# 461 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
# 462 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 463 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 464 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter::
# 465 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 466 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	message LittlerootTown_ProfessorBirchsLab_Text_ReceivedJohtoStarter
# 467 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmessage
# 468 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitfanfare
# 469 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 470 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 471 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_Birch::
# 472 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	lock
# 473 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	faceplayer
# 474 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5, LittlerootTown_ProfessorBirchsLab_EventScript_CanHaveAnyOneOfRarePokemon
# 475 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_GrassyPatchWaiting
# 476 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_unset FLAG_HAS_MATCH_CALL, LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister
# 477 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_unset FLAG_ENABLE_PROF_BIRCH_MATCH_CALL, EventScript_RegisterProfBirch
# 478 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister
# 479 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 480 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 481 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_CanHaveAnyOneOfRarePokemon::
# 482 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CanHaveAnyOneOfRarePokemon, MSGBOX_DEFAULT
# 483 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 484 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 485 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 486 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_GrassyPatchWaiting::
# 487 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting2, MSGBOX_DEFAULT
# 488 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 489 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 490 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 491 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 492 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
EventScript_RegisterProfBirch::
# 493 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox MatchCall_Text_BirchRegisterCall, MSGBOX_DEFAULT
# 494 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	closemessage
# 495 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay 30
# 496 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_REGISTER_MATCH_CALL
# 497 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox MatchCall_Text_RegisteredBirch, MSGBOX_DEFAULT
# 498 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitfanfare
# 499 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	closemessage
# 500 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay 30
# 501 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_ENABLE_PROF_BIRCH_MATCH_CALL
# 502 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_REGISTER_BIRCH_STATE, 2
# 503 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 504 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 505 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 506 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_GivePokedex::
# 507 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_HeardYouBeatRivalTakePokedex, MSGBOX_DEFAULT
# 508 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivePokedex
# 509 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_ExplainPokedex, MSGBOX_DEFAULT
# 510 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	closemessage
# 511 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_RIVAL, LittlerootTown_ProfessorBirchsLab_Movement_RivalApproachPlayer
# 512 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 513 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
# 514 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 515 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	checkplayergender
# 516 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayGivePokeBalls
# 517 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanGivePokeBalls
# 518 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_BIRCH_LAB_STATE, 5
# 519 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_ADVENTURE_STARTED
# 520 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_OLDALE_TOWN_STATE, 1
# 521 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_RIVAL_STATE, 4
# 522 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 3
# 523 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
# 524 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 525 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 526 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_MayGivePokeBalls::
# 527 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayGotPokedexTooTakeThese, MSGBOX_DEFAULT
# 528 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	giveitem ITEM_POKE_BALL, 5
# 529 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, FALSE, LittlerootTown_ProfessorBirchsLab_EventScript_MayNoRoomForPokeBalls
# 530 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CatchCutePokemonWithPokeBalls, MSGBOX_DEFAULT
# 531 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_RESULT, 0
# 532 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 533 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 534 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_BrendanGivePokeBalls::
# 535 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanGotPokedexTooTakeThese, MSGBOX_DEFAULT
# 536 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	giveitem ITEM_POKE_BALL, 5
# 537 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, FALSE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanNoRoomForPokeBalls
# 538 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CatchCoolPokemonWithPokeBalls, MSGBOX_DEFAULT
# 539 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_RESULT, 1
# 540 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 541 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 542 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_ReceivePokedex::
# 543 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 544 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	message LittlerootTown_ProfessorBirchsLab_Text_ReceivedPokedex
# 545 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitfanfare
# 546 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEDEX_GET
# 547 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	special SetUnlockedPokedexFlags
# 548 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
# 549 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_CABLE_CLUB_TUTORIAL_STATE, 1
# 550 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 551 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 552 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_PokemonAwait::
# 553 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CountlessPokemonAwait, MSGBOX_DEFAULT
# 554 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 555 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 556 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 557 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_MayNoRoomForPokeBalls::
# 558 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_OhYourBagsFull, MSGBOX_DEFAULT
# 559 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 560 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 561 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_BrendanNoRoomForPokeBalls::
# 562 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_HeyYourBagsFull, MSGBOX_DEFAULT
# 563 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 564 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 565 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Movement_RivalApproachPlayer:
# 566 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_down
# 567 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_in_place_faster_left
# 568 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	step_end
# 569 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 570 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_Machine::
# 571 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine, MSGBOX_SIGN
# 572 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 573 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 574 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_Rival::
# 575 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	lock
# 576 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	faceplayer
# 577 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5, LittlerootTown_ProfessorBirchsLab_EventScript_RivalFuturePlans
# 578 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_RivalHaveYouGoneToBattleFrontier
# 579 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_RivalTakeBreakFromFieldwork
# 580 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	checkplayergender
# 581 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayWhereShouldIGoNext
# 582 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanWhereShouldIGoNext
# 583 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 584 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 585 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 586 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_MayWhereShouldIGoNext::
# 587 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayWhereShouldIGoNext, MSGBOX_DEFAULT
# 588 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 589 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 590 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_BrendanWhereShouldIGoNext::
# 591 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanWhereShouldIGoNext, MSGBOX_DEFAULT
# 592 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 593 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 594 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_RivalFuturePlans::
# 595 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	checkplayergender
# 596 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayWhatNextImStayingHere
# 597 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanPreferCollectingSlowly
# 598 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 599 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 600 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 601 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_MayWhatNextImStayingHere::
# 602 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayWhatNextImStayingHere, MSGBOX_DEFAULT
# 603 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 604 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 605 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_BrendanPreferCollectingSlowly:
# 606 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanPreferCollectingSlowly, MSGBOX_DEFAULT
# 607 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 608 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 609 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_RivalHaveYouGoneToBattleFrontier::
# 610 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	checkplayergender
# 611 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayHaveYouGoneToBattleFrontier
# 612 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanHaveYouGoneToBattleFrontier
# 613 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 614 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 615 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 616 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_MayHaveYouGoneToBattleFrontier::
# 617 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayHaveYouGoneToBattleFrontier, MSGBOX_DEFAULT
# 618 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 619 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 620 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_BrendanHaveYouGoneToBattleFrontier::
# 621 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanHaveYouGoneToBattleFrontier, MSGBOX_DEFAULT
# 622 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 623 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 624 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_RivalTakeBreakFromFieldwork::
# 625 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	checkplayergender
# 626 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayTakeBreakFromFieldwork
# 627 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanTakeBreakFromFieldwork
# 628 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 629 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 630 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 631 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_MayTakeBreakFromFieldwork::
# 632 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayTakeBreakFromFieldwork, MSGBOX_DEFAULT
# 633 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 634 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 635 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_BrendanTakeBreakFromFieldwork::
# 636 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanTakeBreakFromFieldwork, MSGBOX_DEFAULT
# 637 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 638 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 639 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_PC::
# 640 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_PCUsedForResearch, MSGBOX_SIGN
# 641 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 642 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 643 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_Bookshelf::
# 644 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CrammedWithBooksOnPokemon, MSGBOX_SIGN
# 645 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 646 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 647 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_Book::
# 648 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BookTooHardToRead, MSGBOX_SIGN
# 649 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 650 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 651 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_ScottAboardSSTidalCall::
# 652 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	lockall
# 653 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	pokenavcall LittlerootTown_ProfessorBirchsLab_Text_ScottAboardSSTidalCall
# 654 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmessage
# 655 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	clearflag FLAG_SCOTT_CALL_BATTLE_FRONTIER
# 656 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
# 657 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 658 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 659 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BirchAwayOnFieldwork:
# 660 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Hunh? PROF. BIRCH?\p"
# 661 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "The PROF's away on fieldwork.\n"
# 662 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Ergo, he isn't here.\p"
# 663 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Oh, let me explain what fieldwork is.\p"
# 664 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It is to study things in the natural\n"
# 665 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "environment, like fields and mountains,\l"
# 666 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "instead of a laboratory.\p"
# 667 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "The PROF isn't one for doing desk work.\n"
# 668 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "He's the type of person who would\l"
# 669 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "rather go outside and experience\l"
# 670 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "things than read about them here.$"
# 671 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 672 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BirchIsntOneForDeskWork:
# 673 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "The PROF isn't one for doing desk work.\n"
# 674 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "He's the type of person who would\l"
# 675 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "rather go outside and experience\l"
# 676 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "things than read about them here.$"
# 677 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 678 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BirchEnjoysRivalsHelpToo:
# 679 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH is studying the habitats\n"
# 680 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "and distribution of POKéMON.\p"
# 681 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "The PROF enjoys {RIVAL}'s help, too.\n"
# 682 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "There's a lot of love there.$"
# 683 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 684 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_LikeYouToHavePokemon:
# 685 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: So, {PLAYER}{KUN}.\p"
# 686 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I've heard so much about you from\n"
# 687 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "your father.\p"
# 688 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I've heard that you don't have your\n"
# 689 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "own POKéMON yet.\p"
# 690 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "But the way you battled earlier,\n"
# 691 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "you pulled it off with aplomb!\p"
# 692 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I guess you have your father's blood\n"
# 693 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "in your veins after all!\p"
# 694 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Oh, yes. As thanks for rescuing me,\n"
# 695 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I'd like you to have the POKéMON you\l"
# 696 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "used earlier.\p"
# 697 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "{PLAYER} received the {STR_VAR_1}!$"
# 698 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 699 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_WhyNotGiveNicknameToMon:
# 700 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: While you're at it, why not\n"
# 701 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "give a nickname to that {STR_VAR_1}?$"
# 702 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 703 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_MightBeGoodIdeaToGoSeeRival:
# 704 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: If you work at POKéMON\n"
# 705 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "and gain experience, I think you'll make\l"
# 706 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "an extremely good TRAINER.\p"
# 707 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "My kid, {RIVAL}, is also studying\n"
# 708 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "POKéMON while helping me out.\p"
# 709 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "{PLAYER}{KUN}, don't you think it might be\n"
# 710 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "a good idea to go see {RIVAL}?$"
# 711 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 712 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_GetRivalToTeachYou:
# 713 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: Great!\n"
# 714 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "{RIVAL} should be happy, too.\p"
# 715 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Get {RIVAL} to teach you what it\n"
# 716 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "means to be a TRAINER.$"
# 717 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 718 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_DontBeThatWay:
# 719 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: Oh, don't be that way.\n"
# 720 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You should go meet my kid.$"
# 721 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 722 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BirchRivalGoneHome:
# 723 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: {RIVAL}?\n"
# 724 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Gone home, I think.\p"
# 725 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Or maybe that kid's scrabbling around\n"
# 726 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "in tall grass again somewhere…\p"
# 727 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "If you or your POKéMON get tired,\n"
# 728 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "you should get some rest at home.$"
# 729 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 730 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_HeardYouBeatRivalTakePokedex:
# 731 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: Oh, hi, {PLAYER}{KUN}!\p"
# 732 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I heard you beat {RIVAL} on\n"
# 733 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "your first try. That's excellent!\p"
# 734 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "{RIVAL}'s been helping with my research\n"
# 735 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "for a long time.\p"
# 736 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "{RIVAL} has an extensive history as\n"
# 737 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "a TRAINER already.\p"
# 738 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Here, {PLAYER}{KUN}, I ordered this for my\n"
# 739 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "research, but I think you should have\l"
# 740 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "this POKéDEX.$"
# 741 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 742 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_ReceivedPokedex:
# 743 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "{PLAYER} received the POKéDEX!$"
# 744 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 745 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_ExplainPokedex:
# 746 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: The POKéDEX is a high-tech\n"
# 747 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "tool that automatically makes a record\l"
# 748 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "of any POKéMON you meet or catch.\p"
# 749 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "My kid, {RIVAL}, goes everywhere\n"
# 750 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "with it.\p"
# 751 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Whenever my kid catches a rare POKéMON\n"
# 752 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "and records its data in the POKéDEX,\l"
# 753 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "why, {RIVAL} looks for me while I'm out\l"
# 754 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "doing fieldwork, and shows me.$"
# 755 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 756 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_CountlessPokemonAwait:
# 757 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: Countless POKéMON\n"
# 758 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "await you!\p"
# 759 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Argh, I'm getting the itch to get out\n"
# 760 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "and do fieldwork again!$"
# 761 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 762 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_MayGotPokedexTooTakeThese:
# 763 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "MAY: Oh, wow, {PLAYER}{KUN}!\n"
# 764 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You got a POKéDEX, too!\p"
# 765 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "That's great! Just like me!\n"
# 766 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I've got something for you, too!$"
# 767 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 768 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_CatchCutePokemonWithPokeBalls:
# 769 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "MAY: It's fun if you can get a lot of\n"
# 770 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "POKéMON!\p"
# 771 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I'm going to look all over the place\n"
# 772 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "because I want different POKéMON.\p"
# 773 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "If I find any cute POKéMON, I'll catch\n"
# 774 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "them with POKé BALLS!$"
# 775 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 776 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_OhYourBagsFull:
# 777 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Oh? Your BAG's full.$"
# 778 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 779 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_MayWhereShouldIGoNext:
# 780 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "MAY: I wonder where I should go look\n"
# 781 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "for POKéMON next?$"
# 782 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 783 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BrendanGotPokedexTooTakeThese:
# 784 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "BRENDAN: Huh…\n"
# 785 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "So you got a POKéDEX, too.\p"
# 786 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Well then, here.\n"
# 787 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I'll give you these.$"
# 788 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 789 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_CatchCoolPokemonWithPokeBalls:
# 790 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "BRENDAN: You know it's more fun to\n"
# 791 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "have a whole bunch of POKéMON.\p"
# 792 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I'm going to explore all over the place\n"
# 793 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "to find different POKéMON.\p"
# 794 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "If I find any cool POKéMON, you bet\n"
# 795 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I'll try to get them with POKé BALLS.$"
# 796 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 797 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_HeyYourBagsFull:
# 798 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Hey, your BAG's full.$"
# 799 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 800 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BrendanWhereShouldIGoNext:
# 801 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "BRENDAN: Where should I look for\n"
# 802 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "POKéMON next…$"
# 803 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 804 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine:
# 805 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It's a serious-looking machine.\n"
# 806 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "The PROF must use this for research.$"
# 807 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 808 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_PCUsedForResearch:
# 809 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It's a PC used for research.\n"
# 810 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Better not mess around with it.$"
# 811 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 812 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_CrammedWithBooksOnPokemon:
# 813 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It's crammed with books on POKéMON.$"
# 814 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 815 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BookTooHardToRead:
# 816 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It's a book that's too hard to read.$"
# 817 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 818 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_OtherRegionsUpgradeToNational:
# 819 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: Now…\p"
# 820 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "{PLAYER}{KUN} and {RIVAL}, I've had the two\n"
# 821 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "of you help me study POKéMON.\p"
# 822 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Thanks to your help, new facts\n"
# 823 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "are coming to light.\p"
# 824 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It appears that in the HOENN region,\n"
# 825 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "there are also POKéMON from other\l"
# 826 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "regions.\p"
# 827 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It goes to show how rich and varied\n"
# 828 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "the natural environments of HOENN\l"
# 829 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "happen to be.\p"
# 830 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "That's why I think it's necessary for\n"
# 831 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "me to upgrade your POKéDEX to\l"
# 832 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "the NATIONAL Mode.\p"
# 833 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Here, let me see your POKéDEX units.$"
# 834 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 835 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_MayUpgradeSoCool:
# 836 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "MAY: Eheheh!\p"
# 837 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It's so cool that even my POKéDEX\n"
# 838 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "is getting updated!\p"
# 839 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It's because you went out and caught\n"
# 840 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "so many POKéMON, {PLAYER}{KUN}!$"
# 841 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 842 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BrendanYouCanThankMe:
# 843 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "BRENDAN: I went out all over HOENN\n"
# 844 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "and checked out POKéMON.\p"
# 845 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You can thank me for getting\n"
# 846 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "the NATIONAL Mode POKéDEX.\p"
# 847 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Yep, you're lucky, {PLAYER}!$"
# 848 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 849 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_OkayAllDone:
# 850 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: Okay, all done!$"
# 851 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 852 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_PokedexUpgradedToNational:
# 853 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "{PLAYER}'s POKéDEX was upgraded\n"
# 854 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "to the NATIONAL Mode!$"
# 855 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 856 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting2:
# 857 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: But listen.\n"
# 858 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You've become the CHAMPION,\l"
# 859 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "but your POKéMON journey isn't over.\p"
# 860 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "There is no end to the road\n"
# 861 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "that is POKéMON.\p"
# 862 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Somewhere, there is a grassy patch\n"
# 863 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "that's waiting for you!$"
# 864 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 865 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_MayTakeBreakFromFieldwork:
# 866 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "MAY: I think I'll take a short break\n"
# 867 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "from fieldwork.\p"
# 868 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I think I'll help the PROF here for\n"
# 869 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "a while.$"
# 870 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 871 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BrendanTakeBreakFromFieldwork:
# 872 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "BRENDAN: For the time being,\n"
# 873 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I'm taking a break from fieldwork.\p"
# 874 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I'll be helping out the PROF here\n"
# 875 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "for a while.$"
# 876 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 877 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_CompletedDexChoosePokemon:
# 878 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: Oh, {PLAYER}{KUN}!\n"
# 879 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Let's have a look at your POKéDEX.\p"
# 880 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "… … … … … …\n"
# 881 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "… … … … … …\p"
# 882 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Yes, there's no doubt about it.\p"
# 883 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You really have completed the HOENN\n"
# 884 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "region's POKéDEX.\p"
# 885 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "That's more than just impressive.\p"
# 886 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I have a gift for you.\p"
# 887 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Consider it my show of appreciation\n"
# 888 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "for the fantastic work you've done.\p"
# 889 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "My gift is a rare POKéMON only found\n"
# 890 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "in another region!\p"
# 891 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You can have any one of these\n"
# 892 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "three POKéMON!$"
# 893 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 894 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_CanHaveAnyOneOfRarePokemon:
# 895 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: These are rare POKéMON\n"
# 896 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "only found in another region!\p"
# 897 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You can have any one of these\n"
# 898 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "three POKéMON!$"
# 899 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 900 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_YoullTakeCyndaquil:
# 901 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: The FIRE POKéMON\n"
# 902 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "CYNDAQUIL caught your eye!\p"
# 903 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You're as sharp as ever!\p"
# 904 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "So the CYNDAQUIL is your choice?$"
# 905 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 906 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_YoullTakeTotodile:
# 907 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: The WATER POKéMON\n"
# 908 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "TOTODILE is your choice!\p"
# 909 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You know how to pick a good one.\p"
# 910 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "So, you'll take the TOTODILE?$"
# 911 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 912 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_YoullTakeChikorita:
# 913 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: The GRASS POKéMON\n"
# 914 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "CHIKORITA is your choice!\p"
# 915 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You sure know what you're doing.\p"
# 916 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "So, you'll take the CHIKORITA?$"
# 917 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 918 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_TakeYourTimeAllInvaluable:
# 919 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: Take your time before\n"
# 920 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "you decide.\p"
# 921 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "They're all invaluable POKéMON.$"
# 922 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 923 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
@ Unused
# 924 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_PickedFinePokemon:
# 925 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: I see!\n"
# 926 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You picked a fine POKéMON!$"
# 927 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 928 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_ReceivedJohtoStarter:
# 929 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "{PLAYER} received the {STR_VAR_1}\n"
# 930 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "from PROF. BIRCH!$"
# 931 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 932 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
@ Unused
# 933 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_NicknameJohtoStarter:
# 934 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Want to give a nickname to\n"
# 935 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "the {STR_VAR_1} you received?$"
# 936 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 937 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting:
# 938 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: Listen, {PLAYER}{KUN}.\n"
# 939 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You've completed the HOENN POKéDEX,\l"
# 940 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "but your POKéMON journey isn't over.\p"
# 941 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "There is no end to the road\n"
# 942 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "that is POKéMON.\p"
# 943 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Somewhere, there is a grassy patch\n"
# 944 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "that's waiting for you!$"
# 945 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 946 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BetterLeaveOthersAlone:
# 947 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You received the promised POKéMON.\n"
# 948 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Better leave the others alone.$"
# 949 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 950 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
@ Unused
# 951 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_DontHaveAnyRoomForPokemon:
# 952 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Oh, you don't have any room for\n"
# 953 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "this POKéMON.$"
# 954 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 955 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_MayWhatNextImStayingHere:
# 956 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "MAY: {PLAYER}{KUN}, after this…\n"
# 957 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "What are you going to do?\p"
# 958 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Are you going to keep battling\n"
# 959 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "and sharpening your skills?\p"
# 960 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Or are you going to try filling\n"
# 961 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "the NATIONAL POKéDEX?\p"
# 962 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I'm staying here to help the PROF.$"
# 963 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 964 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BrendanPreferCollectingSlowly:
# 965 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "BRENDAN: Rather than collecting\n"
# 966 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "POKéMON, I prefer slowly and \l"
# 967 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "steadily raising the one I chose.$"
# 968 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 969 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_MayHaveYouGoneToBattleFrontier:
# 970 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "MAY: Oh, hi, {PLAYER}{KUN}!\n"
# 971 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Have you gone to that place,\l"
# 972 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "the BATTLE FRONTIER?$"
# 973 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 974 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BrendanHaveYouGoneToBattleFrontier:
# 975 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "BRENDAN: Hey, {PLAYER}!\n"
# 976 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Have you gone out to that place,\l"
# 977 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "the BATTLE FRONTIER?$"
# 978 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 979 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_ScottAboardSSTidalCall:
# 980 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "… … … … … …\n"
# 981 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "… … … … … Beep!\p"
# 982 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "SCOTT: Hi, hi, {PLAYER}!\n"
# 983 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It's me, SCOTT.\p"
# 984 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I'm aboard the S.S. TIDAL now.\n"
# 985 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It feels great to be on the sea!\p"
# 986 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "By the way…\p"
# 987 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "There's this place that I'd like to\n"
# 988 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "invite you to for a visit.\p"
# 989 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "If you're interested, board a ferry\n"
# 990 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "at either SLATEPORT or LILYCOVE.\p"
# 991 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I'll fill you in on the details when\n"
# 992 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "we meet. I'll be waiting!\p"
# 993 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "… … … … … …\n"
# 994 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "… … … … … Click!$"

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister::
# 999 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_unset FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380, LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_2
# 1001 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_3
# 1003 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_4
# 1005 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_BIRCH_LAB_STATE, 5
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_5
LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_1:
# 1009 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_LITTLEROOT_TOWN_STATE, 0
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_11
# 1011 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_LITTLEROOT_TOWN_STATE, 1
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_12
# 1015 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_LITTLEROOT_TOWN_STATE, 2
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_13
LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_10:
# 1018 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_2:
# 1000 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto ProfBirch_EventScript_RatePokedexOrRegister
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_1

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_3:
# 1002 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto ProfBirch_EventScript_RatePokedexOrRegister
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_1

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_4:
# 1004 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto ProfBirch_EventScript_RatePokedexOrRegister
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_1

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_5:
# 1006 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_PokemonAwait
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_1

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_11:
# 1010 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_Text_0
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_10

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_12:
# 1012 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_Text_1
# 1013 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_Text_2
# 1014 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto Littleroot_GetStarterOption
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_10

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_13:
# 1016 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchRivalGoneHome
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_10


Littleroot_GetStarterOption::
# 1023 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 0
	goto_if_eq Littleroot_GetStarterOption_2
Littleroot_GetStarterOption_1:
# 1026 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 1
	goto_if_eq Littleroot_GetStarterOption_5
# 1028 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 2
	goto_if_eq Littleroot_GetStarterOption_6
Littleroot_GetStarterOption_4:
# 1031 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmessage
# 1032 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
	end

Littleroot_GetStarterOption_2:
# 1024 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterGeneralScript
	goto Littleroot_GetStarterOption_1

Littleroot_GetStarterOption_5:
# 1027 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterNormalScript
	goto Littleroot_GetStarterOption_4

Littleroot_GetStarterOption_6:
# 1029 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterFightingScript
	goto Littleroot_GetStarterOption_4


StarterGeneralScript::
# 1038 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGeneralScript_Text_0
# 1039 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	dynmultichoice 20, 100, TRUE, 5, 0, DYN_MULTICHOICE_CB_NONE, StarterGeneralScript_Text_1, StarterGeneralScript_Text_2, StarterGeneralScript_Text_3
# 1040 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq StarterGeneralScript_2
# 1050 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq StarterGeneralScript_3
# 1060 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq StarterGeneralScript_4
StarterGeneralScript_1:
# 1071 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1072 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1073 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterGeneralScript_2:
# 1041 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGeneralScript_Text_4
# 1043 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_TREECKO, 5, ITEM_ORAN_BERRY
# 1045 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterGeneralScript_8
	goto StarterGeneralScript_1

StarterGeneralScript_3:
# 1051 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGeneralScript_Text_6
# 1053 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_TORCHIC, 5, ITEM_ORAN_BERRY
# 1055 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterGeneralScript_10
	goto StarterGeneralScript_1

StarterGeneralScript_4:
# 1061 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGeneralScript_Text_8
# 1063 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_MUDKIP, 5, ITEM_ORAN_BERRY
# 1065 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterGeneralScript_12
	goto StarterGeneralScript_1

StarterGeneralScript_8:
# 1046 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1047 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGeneralScript_Text_5
# 1048 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
	goto StarterGeneralScript_1

StarterGeneralScript_10:
# 1056 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1057 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGeneralScript_Text_7
# 1058 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
	goto StarterGeneralScript_1

StarterGeneralScript_12:
# 1066 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1067 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGeneralScript_Text_9
# 1068 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
	goto StarterGeneralScript_1


StarterNormalScript::
# 1076 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterNormalScript_Text_0
# 1078 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_LILLIPUP, 5, ITEM_ORAN_BERRY
# 1080 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterNormalScript_2
StarterNormalScript_1:
# 1086 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1087 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterNormalScript_2:
# 1081 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1082 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterNormalScript_Text_1
# 1083 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1084 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
	goto StarterNormalScript_1


StarterFightingScript::
# 1091 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterFightingScript_Text_0
# 1093 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_TIMBURR, 5, ITEM_ORAN_BERRY
# 1095 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterFightingScript_2
StarterFightingScript_1:
# 1101 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1102 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterFightingScript_2:
# 1096 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1097 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterFightingScript_Text_1
# 1098 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1099 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
	goto StarterFightingScript_1


NicknamePartyMon::
# 1108 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox NicknamePartyMon_Text_0, MSGBOX_YESNO
# 1109 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	hidemonpic
# 1110 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq NicknamePartyMon_1
	return

NicknamePartyMon_1:
# 1111 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 1112 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
	return


LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_Text_0:
# 1010 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Hello, {PLAYER}! Have you met {RIVAL} yet?$"

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_Text_1:
# 1012 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Ah, you've met {RIVAL}. Hope you two\n"
	.string "can get along.$"

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_Text_2:
# 1013 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Now, I'm sure you're raring to start your\n"
	.string "journey!$"

StarterGeneralScript_Text_0:
# 1038 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Now for your starter, which type do you\n"
	.string "prefer?$"

StarterGeneralScript_Text_1:
# 1039 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Grass$"

StarterGeneralScript_Text_2:
# 1039 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Fire$"

StarterGeneralScript_Text_3:
# 1039 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Water$"

StarterGeneralScript_Text_4:
# 1041 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I see, if you like Grass types, then\n"
	.string "Treecko will be a perfect fit!$"

StarterGeneralScript_Text_5:
# 1047 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Treecko!$"

StarterGeneralScript_Text_6:
# 1051 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I see, if you like Fire types, then\n"
	.string "Torchic will be a perfect fit!$"

StarterGeneralScript_Text_7:
# 1057 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Torchic!$"

StarterGeneralScript_Text_8:
# 1061 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I see, if you like Water types, then\n"
	.string "Mudkip will be a perfect fit!$"

StarterGeneralScript_Text_9:
# 1067 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Mudkip!$"

StarterNormalScript_Text_0:
# 1076 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I hear you're a fan of Normal Types, So\n"
	.string "Lillipup will be a perfect fit!$"

StarterNormalScript_Text_1:
# 1082 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Lillipup!$"

StarterFightingScript_Text_0:
# 1091 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I hear you're a fan of Fighting Types,\n"
	.string "So Timburr will be a perfect fit!$"

StarterFightingScript_Text_1:
# 1097 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Timburr!$"

NicknamePartyMon_Text_0:
# 1108 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Give it a nickname?$"
