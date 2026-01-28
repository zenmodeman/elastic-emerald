# 1 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 2 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_MapScripts::
# 3 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_ProfessorBirchsLab_OnTransition
# 4 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_ProfessorBirchsLab_OnWarp
# 5 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_ProfessorBirchsLab_OnFrame
# 6 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.byte 0
# 7 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 8 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ State descriptions for VAR_DEX_UPGRADE_JOHTO_STARTER_STATE
# 9 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 1: Beat Elite Four, Dex upgrade ready
# 10 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 2: Received National Dex
# 11 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 3: Left lab after receiving National Dex
# 12 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 4: Entered lab after catching all Hoenn mons
# 13 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 5: Birch told player to choose Johto starter
# 14 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 6: Chose Johto starter
# 15 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 16 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ State descriptions for VAR_BIRCH_LAB_STATE
# 17 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 1: Never occurs
# 18 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 2: Chose starter
# 19 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 3: Received starter in lab
# 20 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 4: Defeated rival on Route 103
# 21 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	@ 5: Received pokedex
# 22 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 23 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_OnTransition:
# 24 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_SetupRivalGfxId
# 25 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call ProfBirch_EventScript_UpdateLocation
# 26 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_SetAfterJohtoStarterLayout
# 27 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_SetJohtoStarterLayout
# 28 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3, LittlerootTown_ProfessorBirchsLab_EventScript_CheckReadyForJohtoStarter
# 29 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 30 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 31 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_CheckReadyForJohtoStarter::
# 32 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	specialvar VAR_RESULT, HasAllHoennMons
# 33 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, LittlerootTown_ProfessorBirchsLab_EventScript_SetReadyForJohtoStarter
# 34 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectmovementtype LOCALID_BIRCHS_LAB_RIVAL, MOVEMENT_TYPE_WANDER_UP_AND_DOWN
# 35 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectxyperm LOCALID_BIRCHS_LAB_RIVAL, 5, 10
# 36 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 37 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 38 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SetReadyForJohtoStarter::
# 39 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4
# 40 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_SetJohtoStarterLayout
# 41 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 42 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SetJohtoStarterLayout::
# 43 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setmaplayoutindex LAYOUT_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB_WITH_TABLE
# 44 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 45 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 46 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SetAfterJohtoStarterLayout::
# 47 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setmaplayoutindex LAYOUT_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB_WITH_TABLE
# 48 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectmovementtype LOCALID_BIRCHS_LAB_RIVAL, MOVEMENT_TYPE_WANDER_UP_AND_DOWN
# 49 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectxyperm LOCALID_BIRCHS_LAB_RIVAL, 5, 10
# 50 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 51 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 52 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_OnWarp:
# 53 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_BIRCH_LAB_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_SetPlayerPosForReceiveStarter
# 54 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForDexUpgrade
# 55 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForDexUpgrade
# 56 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3, LittlerootTown_ProfessorBirchsLab_EventScript_AddRivalObject
# 57 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_AddRivalObject
# 58 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForJohtoStarters
# 59 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5, LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForJohtoStarters
# 60 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.2byte 0
# 61 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 62 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SetPlayerPosForReceiveStarter::
# 63 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	turnobject LOCALID_PLAYER, DIR_NORTH
# 64 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 65 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 66 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForDexUpgrade::
# 67 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	turnobject LOCALID_PLAYER, DIR_NORTH
# 68 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	addobject LOCALID_BIRCHS_LAB_BIRCH
# 69 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	addobject LOCALID_BIRCHS_LAB_RIVAL
# 70 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	turnobject LOCALID_BIRCHS_LAB_RIVAL, DIR_NORTH
# 71 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectxy LOCALID_BIRCHS_LAB_RIVAL, 5, 5
# 72 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	turnobject LOCALID_BIRCHS_LAB_BIRCH, DIR_SOUTH
# 73 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectxy LOCALID_BIRCHS_LAB_BIRCH, 6, 4
# 74 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	turnobject LOCALID_BIRCHS_LAB_AIDE, DIR_EAST
# 75 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectxy LOCALID_BIRCHS_LAB_AIDE, 10, 10
# 76 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 77 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 78 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_AddRivalObject::
# 79 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	addobject LOCALID_BIRCHS_LAB_RIVAL
# 80 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 81 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 82 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SetObjectPosForJohtoStarters::
# 83 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	addobject LOCALID_BIRCHS_LAB_CYNDAQUIL_BALL
# 84 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	addobject LOCALID_BIRCHS_LAB_TOTODILE_BALL
# 85 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	addobject LOCALID_BIRCHS_LAB_CHIKORITA_BALL
# 86 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	addobject LOCALID_BIRCHS_LAB_RIVAL
# 87 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	turnobject LOCALID_BIRCHS_LAB_CYNDAQUIL_BALL, DIR_SOUTH
# 88 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectxy LOCALID_BIRCHS_LAB_CYNDAQUIL_BALL, 8, 4
# 89 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	turnobject LOCALID_BIRCHS_LAB_TOTODILE_BALL, DIR_SOUTH
# 90 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectxy LOCALID_BIRCHS_LAB_TOTODILE_BALL, 9, 4
# 91 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	turnobject LOCALID_BIRCHS_LAB_CHIKORITA_BALL, DIR_SOUTH
# 92 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectxy LOCALID_BIRCHS_LAB_CHIKORITA_BALL, 10, 4
# 93 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	turnobject LOCALID_BIRCHS_LAB_BIRCH, DIR_SOUTH
# 94 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectxy LOCALID_BIRCHS_LAB_BIRCH, 6, 4
# 95 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	turnobject LOCALID_BIRCHS_LAB_RIVAL, DIR_EAST
# 96 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setobjectxy LOCALID_BIRCHS_LAB_RIVAL, 5, 5
# 97 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 98 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 99 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_OnFrame:
# 100 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_BIRCH_LAB_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_GiveStarterEvent
# 101 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_BIRCH_LAB_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_GivePokedexEvent
# 102 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_ProfessorBirchsLab_EventScript_UpgradeToNationalDex
# 103 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 4, LittlerootTown_ProfessorBirchsLab_EventScript_ChooseJohtoStarter
# 104 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.2byte 0
# 105 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 106 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
@ The starter is technically given prior to this on Route 101 by special ChooseStarter
# 107 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
@ This is just where the game tells you its yours and lets you nickname it
# 108 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_GiveStarterEvent::
# 109 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	lockall
# 110 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	bufferleadmonspeciesname STR_VAR_1
# 111 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	message LittlerootTown_ProfessorBirchsLab_Text_LikeYouToHavePokemon
# 112 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmessage
# 113 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 114 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitfanfare
# 115 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_WhyNotGiveNicknameToMon, MSGBOX_YESNO
# 116 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, LittlerootTown_ProfessorBirchsLab_EventScript_NicknameStarter
# 117 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_GoSeeRival
# 118 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 119 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 120 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_NicknameStarter::
# 121 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_0x8004, 0
# 122 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 123 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GoSeeRival
# 124 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 125 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 126 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_GoSeeRival::
# 127 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MightBeGoodIdeaToGoSeeRival, MSGBOX_YESNO
# 128 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, LittlerootTown_ProfessorBirchsLab_EventScript_AgreeToSeeRival
# 129 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_DeclineSeeingRival
# 130 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 131 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 132 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_AgreeToSeeRival::
# 133 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GetRivalToTeachYou, MSGBOX_DEFAULT
# 134 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	clearflag FLAG_HIDE_ROUTE_101_BOY
# 135 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_BIRCH_LAB_STATE, 3
# 136 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
# 137 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 138 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 139 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_DeclineSeeingRival::
# 140 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_DontBeThatWay, MSGBOX_YESNO
# 141 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, LittlerootTown_ProfessorBirchsLab_EventScript_AgreeToSeeRival
# 142 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_DeclineSeeingRival
# 143 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 144 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 145 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_GivePokedexEvent::
# 146 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	lockall
# 147 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnterLabForPokedex
# 148 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 149 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GivePokedex
# 150 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 151 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 152 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnterLabForPokedex:
# 153 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 154 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 155 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 156 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 157 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 158 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 159 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 160 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	step_end
# 161 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 162 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_UpgradeToNationalDex::
# 163 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	lockall
# 164 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay 30
# 165 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_OtherRegionsUpgradeToNational, MSGBOX_DEFAULT
# 166 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	closemessage
# 167 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_BIRCHS_LAB_BIRCH, LittlerootTown_ProfessorBirchsLab_Movement_BirchRetrievePokedexes
# 168 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 169 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay 20
# 170 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playse SE_CLICK
# 171 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay 10
# 172 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playse SE_CLICK
# 173 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay 10
# 174 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playse SE_CLICK
# 175 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay 10
# 176 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playse SE_CLICK
# 177 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay 20
# 178 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_BIRCHS_LAB_RIVAL, Common_Movement_WalkInPlaceFasterRight
# 179 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
# 180 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 181 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	checkplayergender
# 182 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayUpgradeComment
# 183 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanUpgradeComment
# 184 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playse SE_PC_ON
# 185 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitse
# 186 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay 20
# 187 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_BIRCHS_LAB_BIRCH, LittlerootTown_ProfessorBirchsLab_Movement_BirchReturnPokedex
# 188 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 189 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_BIRCHS_LAB_RIVAL, Common_Movement_WalkInPlaceFasterUp
# 190 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 191 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 192 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_OkayAllDone, MSGBOX_DEFAULT
# 193 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 194 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	message LittlerootTown_ProfessorBirchsLab_Text_PokedexUpgradedToNational
# 195 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmessage
# 196 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitfanfare
# 197 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_NATIONAL_DEX
# 198 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	special EnableNationalPokedex
# 199 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting2, MSGBOX_DEFAULT
# 200 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	closemessage
# 201 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCH
# 202 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_RIVAL
# 203 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2
# 204 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_SCOTT_BF_CALL_STEP_COUNTER, 0
# 205 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SCOTT_CALL_BATTLE_FRONTIER
# 206 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
# 207 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 208 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 209 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_MayUpgradeComment::
# 210 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayUpgradeSoCool, MSGBOX_DEFAULT
# 211 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	closemessage
# 212 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 213 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 214 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_BrendanUpgradeComment::
# 215 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanYouCanThankMe, MSGBOX_DEFAULT
# 216 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	closemessage
# 217 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 218 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 219 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Movement_BirchRetrievePokedexes:
# 220 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_left
# 221 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_in_place_faster_down
# 222 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay_16
# 223 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay_16
# 224 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_right
# 225 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_in_place_faster_down
# 226 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay_16
# 227 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay_16
# 228 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_right
# 229 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_down
# 230 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_down
# 231 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_down
# 232 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_down
# 233 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_right
# 234 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_right
# 235 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_right
# 236 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_in_place_faster_up
# 237 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	step_end
# 238 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 239 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Movement_BirchReturnPokedex:
# 240 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_left
# 241 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_left
# 242 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_left
# 243 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 244 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 245 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 246 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 247 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_left
# 248 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_in_place_faster_down
# 249 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	step_end
# 250 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 251 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_ChooseJohtoStarter::
# 252 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	lockall
# 253 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_PLAYER, LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnterLabForJohtoStarter
# 254 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 255 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CompletedDexChoosePokemon, MSGBOX_DEFAULT
# 256 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5
# 257 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
# 258 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 259 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 260 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Movement_PlayerEnterLabForJohtoStarter:
# 261 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 262 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 263 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 264 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 265 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 266 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 267 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_up
# 268 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	step_end
# 269 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 270 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_Aide::
# 271 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	lock
# 272 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	faceplayer
# 273 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_ge VAR_BIRCH_LAB_STATE, 3, LittlerootTown_ProfessorBirchsLab_EventScript_AideReceivedStarter
# 274 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_set FLAG_BIRCH_AIDE_MET, LittlerootTown_ProfessorBirchsLab_EventScript_AideAlreadyMet
# 275 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchAwayOnFieldwork, MSGBOX_DEFAULT
# 276 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_BIRCH_AIDE_MET
# 277 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 278 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 279 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 280 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_AideAlreadyMet::
# 281 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchIsntOneForDeskWork, MSGBOX_DEFAULT
# 282 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 283 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 284 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 285 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_AideReceivedStarter::
# 286 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchEnjoysRivalsHelpToo, MSGBOX_DEFAULT
# 287 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 288 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 289 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 290 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_Cyndaquil::
# 291 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 292 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_AlreadyChoseJohtoStarter
# 293 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_BIRCHS_LAB_BIRCH, Common_Movement_WalkInPlaceFasterRight
# 294 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 295 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	showmonpic SPECIES_CYNDAQUIL, 10, 3
# 296 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_YoullTakeCyndaquil, MSGBOX_YESNO
# 297 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_TakeYourTime
# 298 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GiveCyndaquil
# 299 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 300 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 301 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_Totodile::
# 302 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 303 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_AlreadyChoseJohtoStarter
# 304 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_BIRCHS_LAB_BIRCH, Common_Movement_WalkInPlaceFasterRight
# 305 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 306 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	showmonpic SPECIES_TOTODILE, 10, 3
# 307 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_YoullTakeTotodile, MSGBOX_YESNO
# 308 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_TakeYourTime
# 309 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GiveTotodile
# 310 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 311 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 312 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_Chikorita::
# 313 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 314 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_AlreadyChoseJohtoStarter
# 315 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_BIRCHS_LAB_BIRCH, Common_Movement_WalkInPlaceFasterRight
# 316 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 317 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	showmonpic SPECIES_CHIKORITA, 10, 3
# 318 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_YoullTakeChikorita, MSGBOX_YESNO
# 319 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_TakeYourTime
# 320 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GiveChikorita
# 321 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 322 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 323 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_AlreadyChoseJohtoStarter::
# 324 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BetterLeaveOthersAlone, MSGBOX_DEFAULT
# 325 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
# 326 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 327 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 328 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_TakeYourTime::
# 329 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	hidemonpic
# 330 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_TakeYourTimeAllInvaluable, MSGBOX_DEFAULT
# 331 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
# 332 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 333 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 334 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_GiveCyndaquil::
# 335 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_CYNDAQUIL
# 336 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CYNDAQUIL
# 337 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_CYNDAQUIL, 5
# 338 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, LittlerootTown_ProfessorBirchsLab_EventScript_SendCyndaquilToParty
# 339 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, LittlerootTown_ProfessorBirchsLab_EventScript_SendCyndaquilToPC
# 340 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	hidemonpic
# 341 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto Common_EventScript_NoMoreRoomForPokemon
# 342 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 343 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 344 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SendCyndaquilToParty::
# 345 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
# 346 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	removeobject LOCALID_BIRCHS_LAB_CYNDAQUIL_BALL
# 347 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 348 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedCyndaquil
# 349 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 350 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 351 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedCyndaquil
# 352 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 353 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 354 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SendCyndaquilToPC::
# 355 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
# 356 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	removeobject LOCALID_BIRCHS_LAB_CYNDAQUIL_BALL
# 357 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 358 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_CyndaquilTransferredToPC
# 359 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_NameReceivedBoxMon
# 360 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_CyndaquilTransferredToPC
# 361 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 362 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 363 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_CyndaquilTransferredToPC::
# 364 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_TransferredToPC
# 365 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedCyndaquil
# 366 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 367 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 368 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedCyndaquil::
# 369 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	hidemonpic
# 370 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting, MSGBOX_DEFAULT
# 371 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
# 372 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
# 373 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 374 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 375 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_GiveTotodile::
# 376 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_TOTODILE
# 377 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TOTODILE
# 378 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_TOTODILE, 5
# 379 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, LittlerootTown_ProfessorBirchsLab_EventScript_SendTotodileToParty
# 380 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, LittlerootTown_ProfessorBirchsLab_EventScript_SendTotodileToPC
# 381 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	hidemonpic
# 382 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto Common_EventScript_NoMoreRoomForPokemon
# 383 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 384 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 385 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SendTotodileToParty::
# 386 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
# 387 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	removeobject LOCALID_BIRCHS_LAB_TOTODILE_BALL
# 388 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 389 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedTotodile
# 390 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 391 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 392 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedTotodile
# 393 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 394 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 395 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SendTotodileToPC::
# 396 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
# 397 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	removeobject LOCALID_BIRCHS_LAB_TOTODILE_BALL
# 398 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 399 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_TotodileTransferredToPC
# 400 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_NameReceivedBoxMon
# 401 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TotodileTransferredToPC
# 402 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 403 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 404 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_TotodileTransferredToPC::
# 405 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_TransferredToPC
# 406 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedTotodile
# 407 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 408 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 409 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedTotodile::
# 410 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	hidemonpic
# 411 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting, MSGBOX_DEFAULT
# 412 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
# 413 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
# 414 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 415 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 416 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_GiveChikorita::
# 417 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_CHIKORITA
# 418 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CHIKORITA
# 419 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_CHIKORITA, 5
# 420 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, LittlerootTown_ProfessorBirchsLab_EventScript_SendChikoritaToParty
# 421 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, LittlerootTown_ProfessorBirchsLab_EventScript_SendChikoritaToPC
# 422 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	hidemonpic
# 423 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto Common_EventScript_NoMoreRoomForPokemon
# 424 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 425 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 426 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SendChikoritaToParty::
# 427 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
# 428 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	removeobject LOCALID_BIRCHS_LAB_CHIKORITA_BALL
# 429 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 430 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedChikorita
# 431 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 432 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 433 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedChikorita
# 434 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 435 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 436 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_SendChikoritaToPC::
# 437 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter
# 438 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	removeobject LOCALID_BIRCHS_LAB_CHIKORITA_BALL
# 439 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 440 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, LittlerootTown_ProfessorBirchsLab_EventScript_ChikoritaTransferredToPC
# 441 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_NameReceivedBoxMon
# 442 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ChikoritaTransferredToPC
# 443 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 444 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 445 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_ChikoritaTransferredToPC::
# 446 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_TransferredToPC
# 447 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedChikorita
# 448 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 449 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 450 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedChikorita::
# 451 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	hidemonpic
# 452 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting, MSGBOX_DEFAULT
# 453 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
# 454 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
# 455 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 456 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 457 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_ReceivedJohtoStarter::
# 458 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 459 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	message LittlerootTown_ProfessorBirchsLab_Text_ReceivedJohtoStarter
# 460 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmessage
# 461 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitfanfare
# 462 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 463 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 464 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_Birch::
# 465 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	lock
# 466 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	faceplayer
# 467 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5, LittlerootTown_ProfessorBirchsLab_EventScript_CanHaveAnyOneOfRarePokemon
# 468 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_GrassyPatchWaiting
# 469 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_unset FLAG_HAS_MATCH_CALL, LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister
# 470 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_unset FLAG_ENABLE_PROF_BIRCH_MATCH_CALL, EventScript_RegisterProfBirch
# 471 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister
# 472 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 473 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 474 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_CanHaveAnyOneOfRarePokemon::
# 475 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CanHaveAnyOneOfRarePokemon, MSGBOX_DEFAULT
# 476 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 477 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 478 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 479 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_GrassyPatchWaiting::
# 480 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting2, MSGBOX_DEFAULT
# 481 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 482 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 483 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 484 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
Old_LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister::
# 485 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_unset FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380, ProfBirch_EventScript_RatePokedexOrRegister
# 486 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3, ProfBirch_EventScript_RatePokedexOrRegister
# 487 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, ProfBirch_EventScript_RatePokedexOrRegister
# 488 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_BIRCH_LAB_STATE, 5, LittlerootTown_ProfessorBirchsLab_EventScript_PokemonAwait
# 489 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchRivalGoneHome, MSGBOX_DEFAULT
# 490 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 491 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 492 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 493 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
EventScript_RegisterProfBirch::
# 494 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox MatchCall_Text_BirchRegisterCall, MSGBOX_DEFAULT
# 495 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	closemessage
# 496 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay 30
# 497 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_REGISTER_MATCH_CALL
# 498 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox MatchCall_Text_RegisteredBirch, MSGBOX_DEFAULT
# 499 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitfanfare
# 500 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	closemessage
# 501 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	delay 30
# 502 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_ENABLE_PROF_BIRCH_MATCH_CALL
# 503 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_REGISTER_BIRCH_STATE, 2
# 504 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 505 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 506 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 507 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_GivePokedex::
# 508 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_HeardYouBeatRivalTakePokedex, MSGBOX_DEFAULT
# 509 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call LittlerootTown_ProfessorBirchsLab_EventScript_ReceivePokedex
# 510 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_ExplainPokedex, MSGBOX_DEFAULT
# 511 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	closemessage
# 512 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_BIRCHS_LAB_RIVAL, LittlerootTown_ProfessorBirchsLab_Movement_RivalApproachPlayer
# 513 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 514 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterRight
# 515 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmovement 0
# 516 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	checkplayergender
# 517 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayGivePokeBalls
# 518 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanGivePokeBalls
# 519 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_BIRCH_LAB_STATE, 5
# 520 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_ADVENTURE_STARTED
# 521 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_OLDALE_TOWN_STATE, 1
# 522 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_RIVAL_STATE, 4
# 523 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 3
# 524 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
# 525 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 526 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 527 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_MayGivePokeBalls::
# 528 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayGotPokedexTooTakeThese, MSGBOX_DEFAULT
# 529 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	giveitem ITEM_POKE_BALL, 5
# 530 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, FALSE, LittlerootTown_ProfessorBirchsLab_EventScript_MayNoRoomForPokeBalls
# 531 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CatchCutePokemonWithPokeBalls, MSGBOX_DEFAULT
# 532 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_RESULT, 0
# 533 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 534 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 535 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_BrendanGivePokeBalls::
# 536 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanGotPokedexTooTakeThese, MSGBOX_DEFAULT
# 537 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	giveitem ITEM_POKE_BALL, 5
# 538 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, FALSE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanNoRoomForPokeBalls
# 539 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CatchCoolPokemonWithPokeBalls, MSGBOX_DEFAULT
# 540 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_RESULT, 1
# 541 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 542 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 543 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_ReceivePokedex::
# 544 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 545 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	message LittlerootTown_ProfessorBirchsLab_Text_ReceivedPokedex
# 546 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitfanfare
# 547 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEDEX_GET
# 548 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	special SetUnlockedPokedexFlags
# 549 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
# 550 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_CABLE_CLUB_TUTORIAL_STATE, 1
# 551 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 552 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 553 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_PokemonAwait::
# 554 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CountlessPokemonAwait, MSGBOX_DEFAULT
# 555 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 556 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 557 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 558 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_MayNoRoomForPokeBalls::
# 559 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_OhYourBagsFull, MSGBOX_DEFAULT
# 560 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 561 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 562 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_BrendanNoRoomForPokeBalls::
# 563 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_HeyYourBagsFull, MSGBOX_DEFAULT
# 564 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 565 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 566 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Movement_RivalApproachPlayer:
# 567 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_down
# 568 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	walk_in_place_faster_left
# 569 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	step_end
# 570 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 571 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_Machine::
# 572 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine, MSGBOX_SIGN
# 573 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 574 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 575 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_Rival::
# 576 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	lock
# 577 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	faceplayer
# 578 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 5, LittlerootTown_ProfessorBirchsLab_EventScript_RivalFuturePlans
# 579 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6, LittlerootTown_ProfessorBirchsLab_EventScript_RivalHaveYouGoneToBattleFrontier
# 580 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_ge VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_ProfessorBirchsLab_EventScript_RivalTakeBreakFromFieldwork
# 581 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	checkplayergender
# 582 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayWhereShouldIGoNext
# 583 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanWhereShouldIGoNext
# 584 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 585 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 586 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 587 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_MayWhereShouldIGoNext::
# 588 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayWhereShouldIGoNext, MSGBOX_DEFAULT
# 589 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 590 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 591 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_BrendanWhereShouldIGoNext::
# 592 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanWhereShouldIGoNext, MSGBOX_DEFAULT
# 593 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 594 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 595 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_RivalFuturePlans::
# 596 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	checkplayergender
# 597 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayWhatNextImStayingHere
# 598 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanPreferCollectingSlowly
# 599 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 600 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 601 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 602 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_MayWhatNextImStayingHere::
# 603 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayWhatNextImStayingHere, MSGBOX_DEFAULT
# 604 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 605 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 606 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_BrendanPreferCollectingSlowly:
# 607 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanPreferCollectingSlowly, MSGBOX_DEFAULT
# 608 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 609 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 610 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_RivalHaveYouGoneToBattleFrontier::
# 611 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	checkplayergender
# 612 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayHaveYouGoneToBattleFrontier
# 613 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanHaveYouGoneToBattleFrontier
# 614 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 615 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 616 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 617 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_MayHaveYouGoneToBattleFrontier::
# 618 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayHaveYouGoneToBattleFrontier, MSGBOX_DEFAULT
# 619 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 620 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 621 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_BrendanHaveYouGoneToBattleFrontier::
# 622 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanHaveYouGoneToBattleFrontier, MSGBOX_DEFAULT
# 623 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 624 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 625 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_RivalTakeBreakFromFieldwork::
# 626 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	checkplayergender
# 627 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, MALE, LittlerootTown_ProfessorBirchsLab_EventScript_MayTakeBreakFromFieldwork
# 628 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_ProfessorBirchsLab_EventScript_BrendanTakeBreakFromFieldwork
# 629 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
# 630 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 631 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 632 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_MayTakeBreakFromFieldwork::
# 633 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_MayTakeBreakFromFieldwork, MSGBOX_DEFAULT
# 634 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 635 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 636 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_BrendanTakeBreakFromFieldwork::
# 637 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BrendanTakeBreakFromFieldwork, MSGBOX_DEFAULT
# 638 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	return
# 639 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 640 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_PC::
# 641 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_PCUsedForResearch, MSGBOX_SIGN
# 642 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 643 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 644 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_Bookshelf::
# 645 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_CrammedWithBooksOnPokemon, MSGBOX_SIGN
# 646 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 647 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 648 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_Book::
# 649 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BookTooHardToRead, MSGBOX_SIGN
# 650 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 651 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 652 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_EventScript_ScottAboardSSTidalCall::
# 653 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	lockall
# 654 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	pokenavcall LittlerootTown_ProfessorBirchsLab_Text_ScottAboardSSTidalCall
# 655 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmessage
# 656 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	clearflag FLAG_SCOTT_CALL_BATTLE_FRONTIER
# 657 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	releaseall
# 658 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	end
# 659 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 660 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BirchAwayOnFieldwork:
# 661 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Hunh? PROF. BIRCH?\p"
# 662 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "The PROF's away on fieldwork.\n"
# 663 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Ergo, he isn't here.\p"
# 664 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Oh, let me explain what fieldwork is.\p"
# 665 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It is to study things in the natural\n"
# 666 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "environment, like fields and mountains,\l"
# 667 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "instead of a laboratory.\p"
# 668 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "The PROF isn't one for doing desk work.\n"
# 669 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "He's the type of person who would\l"
# 670 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "rather go outside and experience\l"
# 671 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "things than read about them here.$"
# 672 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 673 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BirchIsntOneForDeskWork:
# 674 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "The PROF isn't one for doing desk work.\n"
# 675 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "He's the type of person who would\l"
# 676 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "rather go outside and experience\l"
# 677 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "things than read about them here.$"
# 678 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 679 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_Intro:
# 680 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
        .string "Oh, nice to meet you, {PLAYER}.\p"
# 681 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
        .string "PROF. BIRCH is often doing fieldwork,\n"
# 682 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
        .string "but he stayed put for your first day!\n"
# 683 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
        .string "he can be awfully thoughtful that way.$"
# 684 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_YourFirstDay:
# 685 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
        .string "PROF. BIRCH is often doing fieldwork,\n"
# 686 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
        .string "but he stayed put for your first day!\n"
# 687 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
        .string "he can be awfully thoughtful that way.$"
# 688 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 689 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BirchEnjoysRivalsHelpToo:
# 690 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH is studying the habitats\n"
# 691 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "and distribution of POKéMON.\p"
# 692 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "The PROF enjoys {RIVAL}'s help, too.\n"
# 693 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "There's a lot of love there.$"
# 694 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 695 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_LikeYouToHavePokemon:
# 696 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: So, {PLAYER}{KUN}.\p"
# 697 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I've heard so much about you from\n"
# 698 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "your father.\p"
# 699 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I've heard that you don't have your\n"
# 700 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "own POKéMON yet.\p"
# 701 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "But the way you battled earlier,\n"
# 702 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "you pulled it off with aplomb!\p"
# 703 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I guess you have your father's blood\n"
# 704 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "in your veins after all!\p"
# 705 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Oh, yes. As thanks for rescuing me,\n"
# 706 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I'd like you to have the POKéMON you\l"
# 707 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "used earlier.\p"
# 708 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "{PLAYER} received the {STR_VAR_1}!$"
# 709 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 710 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_WhyNotGiveNicknameToMon:
# 711 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: While you're at it, why not\n"
# 712 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "give a nickname to that {STR_VAR_1}?$"
# 713 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 714 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_MightBeGoodIdeaToGoSeeRival:
# 715 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: If you work at POKéMON\n"
# 716 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "and gain experience, I think you'll make\l"
# 717 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "an extremely good TRAINER.\p"
# 718 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "My kid, {RIVAL}, is also studying\n"
# 719 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "POKéMON while helping me out.\p"
# 720 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "{PLAYER}{KUN}, don't you think it might be\n"
# 721 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "a good idea to go see {RIVAL}?$"
# 722 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 723 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_GetRivalToTeachYou:
# 724 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: Great!\n"
# 725 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "{RIVAL} should be happy, too.\p"
# 726 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Get {RIVAL} to teach you what it\n"
# 727 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "means to be a TRAINER.$"
# 728 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 729 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_DontBeThatWay:
# 730 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: Oh, don't be that way.\n"
# 731 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You should go meet my kid.$"
# 732 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 733 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BirchRivalGoneHome:
# 734 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: {RIVAL}?\n"
# 735 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Gone home, I think.\p"
# 736 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Or maybe that kid's scrabbling around\n"
# 737 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "in tall grass again somewhere…\p"
# 738 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "If you or your POKéMON get tired,\n"
# 739 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "you should get some rest at home.$"
# 740 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 741 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_HeardYouBeatRivalTakePokedex:
# 742 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: Oh, hi, {PLAYER}{KUN}!\p"
# 743 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I heard you beat {RIVAL} on\n"
# 744 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "your first try. That's excellent!\p"
# 745 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "{RIVAL}'s been helping with my research\n"
# 746 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "for a long time.\p"
# 747 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "{RIVAL} has an extensive history as\n"
# 748 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "a TRAINER already.\p"
# 749 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Here, {PLAYER}{KUN}, I ordered this for my\n"
# 750 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "research, but I think you should have\l"
# 751 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "this POKéDEX.$"
# 752 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 753 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_ReceivedPokedex:
# 754 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "{PLAYER} received the POKéDEX!$"
# 755 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 756 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_ExplainPokedex:
# 757 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: The POKéDEX is a high-tech\n"
# 758 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "tool that automatically makes a record\l"
# 759 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "of any POKéMON you meet or catch.\p"
# 760 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "My kid, {RIVAL}, goes everywhere\n"
# 761 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "with it.\p"
# 762 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Whenever my kid catches a rare POKéMON\n"
# 763 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "and records its data in the POKéDEX,\l"
# 764 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "why, {RIVAL} looks for me while I'm out\l"
# 765 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "doing fieldwork, and shows me.$"
# 766 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 767 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_CountlessPokemonAwait:
# 768 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: Countless POKéMON\n"
# 769 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "await you!\p"
# 770 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Argh, I'm getting the itch to get out\n"
# 771 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "and do fieldwork again!$"
# 772 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 773 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_MayGotPokedexTooTakeThese:
# 774 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "MAY: Oh, wow, {PLAYER}{KUN}!\n"
# 775 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You got a POKéDEX, too!\p"
# 776 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "That's great! Just like me!\n"
# 777 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I've got something for you, too!$"
# 778 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 779 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_CatchCutePokemonWithPokeBalls:
# 780 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "MAY: It's fun if you can get a lot of\n"
# 781 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "POKéMON!\p"
# 782 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I'm going to look all over the place\n"
# 783 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "because I want different POKéMON.\p"
# 784 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "If I find any cute POKéMON, I'll catch\n"
# 785 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "them with POKé BALLS!$"
# 786 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 787 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_OhYourBagsFull:
# 788 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Oh? Your BAG's full.$"
# 789 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 790 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_MayWhereShouldIGoNext:
# 791 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "MAY: I wonder where I should go look\n"
# 792 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "for POKéMON next?$"
# 793 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 794 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BrendanGotPokedexTooTakeThese:
# 795 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "BRENDAN: Huh…\n"
# 796 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "So you got a POKéDEX, too.\p"
# 797 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Well then, here.\n"
# 798 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I'll give you these.$"
# 799 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 800 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_CatchCoolPokemonWithPokeBalls:
# 801 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "BRENDAN: You know it's more fun to\n"
# 802 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "have a whole bunch of POKéMON.\p"
# 803 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I'm going to explore all over the place\n"
# 804 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "to find different POKéMON.\p"
# 805 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "If I find any cool POKéMON, you bet\n"
# 806 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I'll try to get them with POKé BALLS.$"
# 807 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 808 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_HeyYourBagsFull:
# 809 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Hey, your BAG's full.$"
# 810 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 811 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BrendanWhereShouldIGoNext:
# 812 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "BRENDAN: Where should I look for\n"
# 813 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "POKéMON next…$"
# 814 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 815 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_SeriousLookingMachine:
# 816 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It's a serious-looking machine.\n"
# 817 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "The PROF must use this for research.$"
# 818 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 819 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_PCUsedForResearch:
# 820 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It's a PC used for research.\n"
# 821 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Better not mess around with it.$"
# 822 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 823 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_CrammedWithBooksOnPokemon:
# 824 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It's crammed with books on POKéMON.$"
# 825 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 826 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BookTooHardToRead:
# 827 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It's a book that's too hard to read.$"
# 828 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 829 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_OtherRegionsUpgradeToNational:
# 830 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: Now…\p"
# 831 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "{PLAYER}{KUN} and {RIVAL}, I've had the two\n"
# 832 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "of you help me study POKéMON.\p"
# 833 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Thanks to your help, new facts\n"
# 834 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "are coming to light.\p"
# 835 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It appears that in the HOENN region,\n"
# 836 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "there are also POKéMON from other\l"
# 837 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "regions.\p"
# 838 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It goes to show how rich and varied\n"
# 839 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "the natural environments of HOENN\l"
# 840 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "happen to be.\p"
# 841 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "That's why I think it's necessary for\n"
# 842 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "me to upgrade your POKéDEX to\l"
# 843 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "the NATIONAL Mode.\p"
# 844 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Here, let me see your POKéDEX units.$"
# 845 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 846 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_MayUpgradeSoCool:
# 847 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "MAY: Eheheh!\p"
# 848 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It's so cool that even my POKéDEX\n"
# 849 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "is getting updated!\p"
# 850 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It's because you went out and caught\n"
# 851 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "so many POKéMON, {PLAYER}{KUN}!$"
# 852 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 853 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BrendanYouCanThankMe:
# 854 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "BRENDAN: I went out all over HOENN\n"
# 855 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "and checked out POKéMON.\p"
# 856 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You can thank me for getting\n"
# 857 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "the NATIONAL Mode POKéDEX.\p"
# 858 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Yep, you're lucky, {PLAYER}!$"
# 859 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 860 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_OkayAllDone:
# 861 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: Okay, all done!$"
# 862 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 863 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_PokedexUpgradedToNational:
# 864 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "{PLAYER}'s POKéDEX was upgraded\n"
# 865 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "to the NATIONAL Mode!$"
# 866 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 867 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting2:
# 868 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: But listen.\n"
# 869 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You've become the CHAMPION,\l"
# 870 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "but your POKéMON journey isn't over.\p"
# 871 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "There is no end to the road\n"
# 872 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "that is POKéMON.\p"
# 873 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Somewhere, there is a grassy patch\n"
# 874 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "that's waiting for you!$"
# 875 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 876 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_MayTakeBreakFromFieldwork:
# 877 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "MAY: I think I'll take a short break\n"
# 878 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "from fieldwork.\p"
# 879 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I think I'll help the PROF here for\n"
# 880 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "a while.$"
# 881 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 882 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BrendanTakeBreakFromFieldwork:
# 883 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "BRENDAN: For the time being,\n"
# 884 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I'm taking a break from fieldwork.\p"
# 885 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I'll be helping out the PROF here\n"
# 886 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "for a while.$"
# 887 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 888 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_CompletedDexChoosePokemon:
# 889 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: Oh, {PLAYER}{KUN}!\n"
# 890 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Let's have a look at your POKéDEX.\p"
# 891 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "… … … … … …\n"
# 892 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "… … … … … …\p"
# 893 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Yes, there's no doubt about it.\p"
# 894 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You really have completed the HOENN\n"
# 895 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "region's POKéDEX.\p"
# 896 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "That's more than just impressive.\p"
# 897 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I have a gift for you.\p"
# 898 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Consider it my show of appreciation\n"
# 899 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "for the fantastic work you've done.\p"
# 900 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "My gift is a rare POKéMON only found\n"
# 901 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "in another region!\p"
# 902 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You can have any one of these\n"
# 903 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "three POKéMON!$"
# 904 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 905 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_CanHaveAnyOneOfRarePokemon:
# 906 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: These are rare POKéMON\n"
# 907 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "only found in another region!\p"
# 908 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You can have any one of these\n"
# 909 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "three POKéMON!$"
# 910 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 911 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_YoullTakeCyndaquil:
# 912 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: The FIRE POKéMON\n"
# 913 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "CYNDAQUIL caught your eye!\p"
# 914 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You're as sharp as ever!\p"
# 915 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "So the CYNDAQUIL is your choice?$"
# 916 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 917 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_YoullTakeTotodile:
# 918 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: The WATER POKéMON\n"
# 919 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "TOTODILE is your choice!\p"
# 920 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You know how to pick a good one.\p"
# 921 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "So, you'll take the TOTODILE?$"
# 922 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 923 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_YoullTakeChikorita:
# 924 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: The GRASS POKéMON\n"
# 925 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "CHIKORITA is your choice!\p"
# 926 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You sure know what you're doing.\p"
# 927 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "So, you'll take the CHIKORITA?$"
# 928 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 929 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_TakeYourTimeAllInvaluable:
# 930 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: Take your time before\n"
# 931 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "you decide.\p"
# 932 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "They're all invaluable POKéMON.$"
# 933 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 934 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
@ Unused
# 935 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_PickedFinePokemon:
# 936 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: I see!\n"
# 937 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You picked a fine POKéMON!$"
# 938 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 939 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_ReceivedJohtoStarter:
# 940 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "{PLAYER} received the {STR_VAR_1}\n"
# 941 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "from PROF. BIRCH!$"
# 942 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 943 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
@ Unused
# 944 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_NicknameJohtoStarter:
# 945 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Want to give a nickname to\n"
# 946 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "the {STR_VAR_1} you received?$"
# 947 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 948 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_GrassyPatchWaiting:
# 949 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "PROF. BIRCH: Listen, {PLAYER}{KUN}.\n"
# 950 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You've completed the HOENN POKéDEX,\l"
# 951 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "but your POKéMON journey isn't over.\p"
# 952 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "There is no end to the road\n"
# 953 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "that is POKéMON.\p"
# 954 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Somewhere, there is a grassy patch\n"
# 955 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "that's waiting for you!$"
# 956 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 957 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BetterLeaveOthersAlone:
# 958 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "You received the promised POKéMON.\n"
# 959 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Better leave the others alone.$"
# 960 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 961 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
@ Unused
# 962 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_DontHaveAnyRoomForPokemon:
# 963 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Oh, you don't have any room for\n"
# 964 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "this POKéMON.$"
# 965 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 966 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_MayWhatNextImStayingHere:
# 967 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "MAY: {PLAYER}{KUN}, after this…\n"
# 968 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "What are you going to do?\p"
# 969 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Are you going to keep battling\n"
# 970 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "and sharpening your skills?\p"
# 971 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Or are you going to try filling\n"
# 972 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "the NATIONAL POKéDEX?\p"
# 973 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I'm staying here to help the PROF.$"
# 974 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 975 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BrendanPreferCollectingSlowly:
# 976 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "BRENDAN: Rather than collecting\n"
# 977 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "POKéMON, I prefer slowly and \l"
# 978 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "steadily raising the one I chose.$"
# 979 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 980 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_MayHaveYouGoneToBattleFrontier:
# 981 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "MAY: Oh, hi, {PLAYER}{KUN}!\n"
# 982 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Have you gone to that place,\l"
# 983 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "the BATTLE FRONTIER?$"
# 984 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 985 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_BrendanHaveYouGoneToBattleFrontier:
# 986 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "BRENDAN: Hey, {PLAYER}!\n"
# 987 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Have you gone out to that place,\l"
# 988 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "the BATTLE FRONTIER?$"
# 989 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"

# 990 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
LittlerootTown_ProfessorBirchsLab_Text_ScottAboardSSTidalCall:
# 991 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "… … … … … …\n"
# 992 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "… … … … … Beep!\p"
# 993 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "SCOTT: Hi, hi, {PLAYER}!\n"
# 994 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It's me, SCOTT.\p"
# 995 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I'm aboard the S.S. TIDAL now.\n"
# 996 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "It feels great to be on the sea!\p"
# 997 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "By the way…\p"
# 998 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "There's this place that I'd like to\n"
# 999 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "invite you to for a visit.\p"
# 1000 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "If you're interested, board a ferry\n"
# 1001 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "at either SLATEPORT or LILYCOVE.\p"
# 1002 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I'll fill you in on the details when\n"
# 1003 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "we meet. I'll be waiting!\p"
# 1004 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "… … … … … …\n"
# 1005 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "… … … … … Click!$"

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister::
# 1010 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto_if_unset FLAG_HIDE_LITTLEROOT_TOWN_BIRCHS_LAB_UNKNOWN_0x380, LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_2
# 1012 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_3
# 1014 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 6
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_4
# 1016 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_BIRCH_LAB_STATE, 5
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_5
LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_1:
# 1020 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_LITTLEROOT_TOWN_STATE, 0
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_11
# 1022 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_LITTLEROOT_TOWN_STATE, 1
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_12
# 1026 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_LITTLEROOT_TOWN_STATE, 2
	goto_if_eq LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_13
LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_10:
# 1029 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	release
	end

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_2:
# 1011 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto ProfBirch_EventScript_RatePokedexOrRegister
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_1

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_3:
# 1013 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto ProfBirch_EventScript_RatePokedexOrRegister
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_1

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_4:
# 1015 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto ProfBirch_EventScript_RatePokedexOrRegister
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_1

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_5:
# 1017 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_PokemonAwait
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_1

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_11:
# 1021 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_Text_0
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_10

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_12:
# 1023 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_Text_1
# 1024 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_Text_2
# 1025 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto Littleroot_GetStarterOption
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_10

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_13:
# 1027 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox LittlerootTown_ProfessorBirchsLab_Text_BirchRivalGoneHome
	goto LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_10


Littleroot_GetStarterOption::
# 1034 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 0
	goto_if_eq Littleroot_GetStarterOption_2
Littleroot_GetStarterOption_1:
# 1037 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 1
	goto_if_eq Littleroot_GetStarterOption_5
# 1039 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 2
	goto_if_eq Littleroot_GetStarterOption_6
# 1041 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 3
	goto_if_eq Littleroot_GetStarterOption_7
# 1043 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 4
	goto_if_eq Littleroot_GetStarterOption_8
# 1045 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 5
	goto_if_eq Littleroot_GetStarterOption_9
# 1047 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 6
	goto_if_eq Littleroot_GetStarterOption_10
# 1049 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 7
	goto_if_eq Littleroot_GetStarterOption_11
# 1051 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 8
	goto_if_eq Littleroot_GetStarterOption_12
# 1054 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 9
	goto_if_eq Littleroot_GetStarterOption_13
# 1056 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 10
	goto_if_eq Littleroot_GetStarterOption_14
# 1058 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 11
	goto_if_eq Littleroot_GetStarterOption_15
# 1060 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 12
	goto_if_eq Littleroot_GetStarterOption_16
# 1062 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 13
	goto_if_eq Littleroot_GetStarterOption_17
# 1064 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 14
	goto_if_eq Littleroot_GetStarterOption_18
# 1066 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 15
	goto_if_eq Littleroot_GetStarterOption_19
# 1068 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 16
	goto_if_eq Littleroot_GetStarterOption_20
# 1070 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 17
	goto_if_eq Littleroot_GetStarterOption_21
# 1072 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_MONOTYPE, 18
	goto_if_eq Littleroot_GetStarterOption_22
Littleroot_GetStarterOption_4:
# 1075 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	waitmessage
# 1076 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox Littleroot_GetStarterOption_Text_0
# 1077 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	giveItem ITEM_POKEMON_BOX_LINK
# 1078 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox Littleroot_GetStarterOption_Text_1
# 1079 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	checkplayergender
# 1080 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MALE
	goto_if_eq Littleroot_GetStarterOption_42
# 1083 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
Littleroot_GetStarterOption_41:
# 1085 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	goto LittlerootTown_ProfessorBirchsLab_EventScript_GoSeeRival
	return

Littleroot_GetStarterOption_2:
# 1035 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterGeneralScript
	goto Littleroot_GetStarterOption_1

Littleroot_GetStarterOption_5:
# 1038 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterNormalScript
	goto Littleroot_GetStarterOption_4

Littleroot_GetStarterOption_6:
# 1040 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterFightingScript
	goto Littleroot_GetStarterOption_4

Littleroot_GetStarterOption_7:
# 1042 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterFlyingScript
	goto Littleroot_GetStarterOption_4

Littleroot_GetStarterOption_8:
# 1044 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterPoisonScript
	goto Littleroot_GetStarterOption_4

Littleroot_GetStarterOption_9:
# 1046 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterGroundScript
	goto Littleroot_GetStarterOption_4

Littleroot_GetStarterOption_10:
# 1048 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterRockScript
	goto Littleroot_GetStarterOption_4

Littleroot_GetStarterOption_11:
# 1050 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterBugScript
	goto Littleroot_GetStarterOption_4

Littleroot_GetStarterOption_12:
# 1052 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterGhostScript
	goto Littleroot_GetStarterOption_4

Littleroot_GetStarterOption_13:
# 1055 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterSteelScript
	goto Littleroot_GetStarterOption_4

Littleroot_GetStarterOption_14:
# 1057 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterFireScript
	goto Littleroot_GetStarterOption_4

Littleroot_GetStarterOption_15:
# 1059 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterWaterScript
	goto Littleroot_GetStarterOption_4

Littleroot_GetStarterOption_16:
# 1061 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterGrassScript
	goto Littleroot_GetStarterOption_4

Littleroot_GetStarterOption_17:
# 1063 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterElectricScript
	goto Littleroot_GetStarterOption_4

Littleroot_GetStarterOption_18:
# 1065 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterPsychicScript
	goto Littleroot_GetStarterOption_4

Littleroot_GetStarterOption_19:
# 1067 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterIceScript
	goto Littleroot_GetStarterOption_4

Littleroot_GetStarterOption_20:
# 1069 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterDragonScript
	goto Littleroot_GetStarterOption_4

Littleroot_GetStarterOption_21:
# 1071 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterDarkScript
	goto Littleroot_GetStarterOption_4

Littleroot_GetStarterOption_22:
# 1073 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call StarterFairyScript
	goto Littleroot_GetStarterOption_4

Littleroot_GetStarterOption_42:
# 1081 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	goto Littleroot_GetStarterOption_41


StarterGeneralScript::
# 1090 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGeneralScript_Text_0
# 1091 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	dynmultichoice 20, 100, TRUE, 5, 0, DYN_MULTICHOICE_CB_NONE, StarterGeneralScript_Text_1, StarterGeneralScript_Text_2, StarterGeneralScript_Text_3
# 1092 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq StarterGeneralScript_2
# 1103 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq StarterGeneralScript_3
# 1114 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq StarterGeneralScript_4
StarterGeneralScript_1:
# 1126 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1127 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1128 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterGeneralScript_2:
# 1093 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGeneralScript_Text_4
# 1095 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_TREECKO, 5, ITEM_ENIGMA_BERRY
# 1097 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterGeneralScript_8
	goto StarterGeneralScript_1

StarterGeneralScript_3:
# 1104 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGeneralScript_Text_6
# 1106 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_TORCHIC, 5, ITEM_ENIGMA_BERRY
# 1108 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterGeneralScript_10
	goto StarterGeneralScript_1

StarterGeneralScript_4:
# 1115 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGeneralScript_Text_8
# 1117 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_MUDKIP, 5, ITEM_ENIGMA_BERRY
# 1119 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterGeneralScript_12
	goto StarterGeneralScript_1

StarterGeneralScript_8:
# 1098 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1099 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGeneralScript_Text_5
# 1100 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1101 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 0
	goto StarterGeneralScript_1

StarterGeneralScript_10:
# 1109 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1110 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGeneralScript_Text_7
# 1111 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1112 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 1
	goto StarterGeneralScript_1

StarterGeneralScript_12:
# 1120 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1121 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGeneralScript_Text_9
# 1122 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1123 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 2
	goto StarterGeneralScript_1


StarterNormalScript::
# 1131 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterNormalScript_Text_0
# 1133 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_LILLIPUP, 5, ITEM_ENIGMA_BERRY
# 1135 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterNormalScript_2
StarterNormalScript_1:
# 1142 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1143 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterNormalScript_2:
# 1136 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1137 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterNormalScript_Text_1
# 1138 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1139 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1140 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 0
	goto StarterNormalScript_1


StarterFightingScript::
# 1147 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterFightingScript_Text_0
# 1149 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_TIMBURR, 5, ITEM_ENIGMA_BERRY
# 1151 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterFightingScript_2
StarterFightingScript_1:
# 1158 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1159 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterFightingScript_2:
# 1152 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1153 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterFightingScript_Text_1
# 1154 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1155 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1156 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 2
	goto StarterFightingScript_1


StarterFlyingScript::
# 1163 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterFlyingScript_Text_0
# 1165 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_FLETCHLING, 5, ITEM_ENIGMA_BERRY
# 1167 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterFlyingScript_2
StarterFlyingScript_1:
# 1174 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1175 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterFlyingScript_2:
# 1168 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1169 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterFlyingScript_Text_1
# 1170 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1171 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1172 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 1
	goto StarterFlyingScript_1


StarterPoisonScript::
# 1179 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterPoisonScript_Text_0
# 1181 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_EKANS, 5, ITEM_ENIGMA_BERRY
# 1183 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterPoisonScript_2
StarterPoisonScript_1:
# 1190 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1191 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterPoisonScript_2:
# 1184 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1185 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterPoisonScript_Text_1
# 1186 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1187 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1188 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 1
	goto StarterPoisonScript_1


StarterGroundScript::
# 1195 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGroundScript_Text_0
# 1197 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_SANDSHREW, 5, ITEM_ENIGMA_BERRY
# 1199 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterGroundScript_2
StarterGroundScript_1:
# 1206 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1207 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterGroundScript_2:
# 1200 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1201 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGroundScript_Text_1
# 1202 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1203 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1204 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 2
	goto StarterGroundScript_1


StarterRockScript::
# 1211 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterRockScript_Text_0
# 1213 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_NACLI, 5, ITEM_ENIGMA_BERRY
# 1215 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterRockScript_2
StarterRockScript_1:
# 1222 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1223 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterRockScript_2:
# 1216 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1217 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterRockScript_Text_1
# 1218 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1219 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1220 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 1
	goto StarterRockScript_1


StarterBugScript::
# 1227 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterBugScript_Text_0
# 1229 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_SEWADDLE, 5, ITEM_ENIGMA_BERRY
# 1231 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterBugScript_2
StarterBugScript_1:
# 1238 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1239 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterBugScript_2:
# 1232 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1233 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterBugScript_Text_1
# 1234 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1235 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1236 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 0
	goto StarterBugScript_1


StarterGhostScript::
# 1243 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGhostScript_Text_0
# 1245 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_GASTLY, 5, ITEM_ENIGMA_BERRY
# 1247 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterGhostScript_2
StarterGhostScript_1:
# 1254 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1255 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterGhostScript_2:
# 1248 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1249 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGhostScript_Text_1
# 1250 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1251 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1252 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 1
	goto StarterGhostScript_1


StarterSteelScript::
# 1259 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterSteelScript_Text_0
# 1261 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_SANDSHREW_ALOLA, 5, ITEM_ENIGMA_BERRY
# 1263 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterSteelScript_2
StarterSteelScript_1:
# 1270 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1271 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterSteelScript_2:
# 1264 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1265 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterSteelScript_Text_1
# 1266 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1267 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1268 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 0
	goto StarterSteelScript_1


StarterFireScript::
# 1275 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterFireScript_Text_0
# 1277 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_TORCHIC, 5, ITEM_ENIGMA_BERRY
# 1279 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterFireScript_2
StarterFireScript_1:
# 1286 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1287 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterFireScript_2:
# 1280 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1281 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGeneralScript_Text_7
# 1282 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1283 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1284 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 1
	goto StarterFireScript_1


StarterWaterScript::
# 1291 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterWaterScript_Text_0
# 1293 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_MUDKIP, 5, ITEM_ENIGMA_BERRY
# 1295 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterWaterScript_2
StarterWaterScript_1:
# 1302 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1303 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterWaterScript_2:
# 1296 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1297 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGeneralScript_Text_9
# 1298 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1299 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1300 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 2
	goto StarterWaterScript_1


StarterGrassScript::
# 1307 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGrassScript_Text_0
# 1309 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_TREECKO, 5, ITEM_ENIGMA_BERRY
# 1311 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterGrassScript_2
StarterGrassScript_1:
# 1318 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1319 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterGrassScript_2:
# 1312 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1313 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterGeneralScript_Text_5
# 1314 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1315 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1316 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 0
	goto StarterGrassScript_1


StarterElectricScript::
# 1323 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterElectricScript_Text_0
# 1325 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_PAWMI, 5, ITEM_ENIGMA_BERRY
# 1327 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterElectricScript_2
StarterElectricScript_1:
# 1334 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1335 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterElectricScript_2:
# 1328 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1329 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterElectricScript_Text_1
# 1330 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1331 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1332 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 2
	goto StarterElectricScript_1


StarterPsychicScript::
# 1339 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterPsychicScript_Text_0
# 1341 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_DROWZEE, 5, ITEM_ENIGMA_BERRY
# 1343 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterPsychicScript_2
StarterPsychicScript_1:
# 1350 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1351 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterPsychicScript_2:
# 1344 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1345 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterPsychicScript_Text_1
# 1346 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1347 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1348 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 2
	goto StarterPsychicScript_1


StarterIceScript::
# 1355 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterIceScript_Text_0
# 1357 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_SANDSHREW_ALOLA, 5, ITEM_ENIGMA_BERRY
# 1359 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterIceScript_2
StarterIceScript_1:
# 1366 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1367 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterIceScript_2:
# 1360 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1361 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterSteelScript_Text_1
# 1362 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1363 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1364 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 0
	goto StarterIceScript_1


StarterDragonScript::
# 1371 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterDragonScript_Text_0
# 1373 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_GIBLE, 5, ITEM_ENIGMA_BERRY
# 1375 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterDragonScript_2
StarterDragonScript_1:
# 1382 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1383 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterDragonScript_2:
# 1376 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1377 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterDragonScript_Text_1
# 1378 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1379 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1380 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 2
	goto StarterDragonScript_1


StarterDarkScript::
# 1387 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterDarkScript_Text_0
# 1389 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_HOUNDOUR, 5, ITEM_ENIGMA_BERRY
# 1391 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterDarkScript_2
StarterDarkScript_1:
# 1398 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1399 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterDarkScript_2:
# 1392 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1393 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterDarkScript_Text_1
# 1394 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1395 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1396 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 0
	goto StarterDarkScript_1


StarterFairyScript::
# 1403 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterFairyScript_Text_0
# 1405 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	givemon SPECIES_FIDOUGH, 5, ITEM_ENIGMA_BERRY
# 1407 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq StarterFairyScript_2
StarterFairyScript_1:
# 1414 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 1415 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	return

StarterFairyScript_2:
# 1408 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 1409 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox StarterFairyScript_Text_1
# 1410 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setflag FLAG_STARTER_ACQUIRED
# 1411 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call NicknamePartyMon
# 1412 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	setvar VAR_STARTER_MON, 1
	goto StarterFairyScript_1


NicknamePartyMon::
# 1419 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	msgbox NicknamePartyMon_Text_0, MSGBOX_YESNO
# 1420 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	hidemonpic
# 1421 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq NicknamePartyMon_1
	return

NicknamePartyMon_1:
# 1422 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 1423 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
	return


LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_Text_0:
# 1021 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Hello, {PLAYER}! Have you met {RIVAL} yet?$"

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_Text_1:
# 1023 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Ah, you've met {RIVAL}. Hope you two\n"
	.string "can get along.$"

LittlerootTown_ProfessorBirchsLab_EventScript_TryRatePokedexOrRegister_Text_2:
# 1024 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Now, I'm sure you're raring to start your\n"
	.string "journey!$"

Littleroot_GetStarterOption_Text_0:
# 1076 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Now that you have a Pokemon, every\n"
	.string "trainer these days needs a Box Link as\l"
	.string "well. Here you go!$"

Littleroot_GetStarterOption_Text_1:
# 1078 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "With the Box link, you'll be able to\n"
	.string "access your Pokemon PC wherever you\l"
	.string "go. It's great when you need to work in\l"
	.string "the field a lot!$"

StarterGeneralScript_Text_0:
# 1090 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Now for your starter, which type do you\n"
	.string "prefer?$"

StarterGeneralScript_Text_1:
# 1091 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Grass$"

StarterGeneralScript_Text_2:
# 1091 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Fire$"

StarterGeneralScript_Text_3:
# 1091 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Water$"

StarterGeneralScript_Text_4:
# 1093 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I see, if you like Grass types, then\n"
	.string "Treecko will be a perfect fit!$"

StarterGeneralScript_Text_5:
# 1099 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Treecko!$"

StarterGeneralScript_Text_6:
# 1104 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I see, if you like Fire types, then\n"
	.string "Torchic will be a perfect fit!$"

StarterGeneralScript_Text_7:
# 1110 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Torchic!$"

StarterGeneralScript_Text_8:
# 1115 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I see, if you like Water types, then\n"
	.string "Mudkip will be a perfect fit!$"

StarterGeneralScript_Text_9:
# 1121 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Mudkip!$"

StarterNormalScript_Text_0:
# 1131 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I hear you're a fan of Normal Types, So\n"
	.string "Lillipup will be a perfect fit!$"

StarterNormalScript_Text_1:
# 1137 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Lillipup!$"

StarterFightingScript_Text_0:
# 1147 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I hear you're a fan of Fighting Types,\n"
	.string "So Timburr will be a perfect fit!$"

StarterFightingScript_Text_1:
# 1153 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Timburr!$"

StarterFlyingScript_Text_0:
# 1163 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I hear you're a fan of Flying Types, So\n"
	.string "Fletchling will be a perfect fit!$"

StarterFlyingScript_Text_1:
# 1169 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Fletchling!$"

StarterPoisonScript_Text_0:
# 1179 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I hear you're a fan of Poison Types, So\n"
	.string "Ekans will be a perfect fit!$"

StarterPoisonScript_Text_1:
# 1185 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Ekans!$"

StarterGroundScript_Text_0:
# 1195 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I hear you're a fan of Ground Types, So\n"
	.string "Sandshrew will be a perfect fit!$"

StarterGroundScript_Text_1:
# 1201 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Sandshrew!$"

StarterRockScript_Text_0:
# 1211 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I hear you're a fan of Rock Types, So\n"
	.string "Nacli will be a perfect fit!$"

StarterRockScript_Text_1:
# 1217 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Nacli!$"

StarterBugScript_Text_0:
# 1227 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I hear you're a fan of Bug Types, So\n"
	.string "Sewaddle will be a perfect fit!$"

StarterBugScript_Text_1:
# 1233 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Sewaddle!$"

StarterGhostScript_Text_0:
# 1243 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I hear you're a fan of Ghost Types, So\n"
	.string "Gastly will be a perfect fit!$"

StarterGhostScript_Text_1:
# 1249 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Gastly!$"

StarterSteelScript_Text_0:
# 1259 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I hear you're a fan of Steel Types, So\n"
	.string "Sandshrew-Alola will be a perfect fit!$"

StarterSteelScript_Text_1:
# 1265 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Sandshrew-Alola!$"

StarterFireScript_Text_0:
# 1275 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I hear you're a fan of Fire Types, So\n"
	.string "Torchic will be a perfect fit!$"

StarterWaterScript_Text_0:
# 1291 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I hear you're a fan of Water Types, So\n"
	.string "Mudkip will be a perfect fit!$"

StarterGrassScript_Text_0:
# 1307 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I hear you're a fan of Grass Types, So\n"
	.string "Treecko will be a perfect fit!$"

StarterElectricScript_Text_0:
# 1323 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I hear you're a fan of Electric Types,\n"
	.string "So Pawmi will be a perfect fit!$"

StarterElectricScript_Text_1:
# 1329 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Pawmi!$"

StarterPsychicScript_Text_0:
# 1339 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I hear you're a fan of Psychic Types, So\n"
	.string "Drowzee will be a perfect fit!$"

StarterPsychicScript_Text_1:
# 1345 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Drowzee!$"

StarterIceScript_Text_0:
# 1355 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I hear you're a fan of Ice Types, So\n"
	.string "Sandshrew-Alola will be a perfect fit!$"

StarterDragonScript_Text_0:
# 1371 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I hear you're a fan of Dragon Types, So\n"
	.string "Gible will be a perfect fit!$"

StarterDragonScript_Text_1:
# 1377 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Gible!$"

StarterDarkScript_Text_0:
# 1387 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I hear you're a fan of Dark Types, So\n"
	.string "Houndour will be a perfect fit!$"

StarterDarkScript_Text_1:
# 1393 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Houndour!$"

StarterFairyScript_Text_0:
# 1403 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "I hear you're a fan of Fairy Types, So\n"
	.string "Fidough will be a perfect fit!$"

StarterFairyScript_Text_1:
# 1409 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Received Fidough!$"

NicknamePartyMon_Text_0:
# 1419 "data/maps/LittlerootTown_ProfessorBirchsLab/scripts.pory"
	.string "Give it a nickname?$"
