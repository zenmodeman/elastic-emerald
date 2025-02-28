# 1 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"

# 2 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"

# 3 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
.set LOCALID_NURSE, 1
# 4 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"

# 5 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
DewfordTown_PokemonCenter_1F_MapScripts::
# 6 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordTown_PokemonCenter_1F_OnTransition
# 7 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
# 8 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	.byte 0
# 9 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"

# 10 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
DewfordTown_PokemonCenter_1F_OnTransition:
# 11 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	setrespawn HEAL_LOCATION_DEWFORD_TOWN
# 12 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	call Common_EventScript_UpdateBrineyLocation
# 13 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	end
# 14 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"

# 15 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
DewfordTown_PokemonCenter_1F_EventScript_Nurse::
# 16 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	setvar VAR_0x800B, LOCALID_NURSE
# 17 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	call Common_EventScript_PkmnCenterNurse
# 18 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	waitmessage
# 19 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	waitbuttonpress
# 20 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	release
# 21 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	end
# 22 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"

# 23 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
DewfordTown_PokemonCenter_1F_EventScript_PokefanF::
# 24 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	msgbox DewfordTown_PokemonCenter_1F_Text_StoneCavern, MSGBOX_NPC
# 25 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	end
# 26 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"

# 27 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
DewfordTown_PokemonCenter_1F_EventScript_Man::
# 28 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	msgbox DewfordTown_PokemonCenter_1F_Text_FaintedMonCanUseHM, MSGBOX_NPC
# 29 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	end
# 30 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"

# 31 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
DewfordTown_PokemonCenter_1F_Text_StoneCavern:
# 32 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	.string "There's a stone cavern at the edge\n"
# 33 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	.string "of town.\p"
# 34 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	.string "I've heard you can find rare stones\n"
# 35 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	.string "there.$"
# 36 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"

# 37 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
DewfordTown_PokemonCenter_1F_Text_FaintedMonCanUseHM:
# 38 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	.string "Even if a POKéMON faints and can't\n"
# 39 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	.string "battle, it can still use a move learned\l"
# 40 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	.string "from a HIDDEN MACHINE (HM).$"

DewfordTown_PokemonCenter_1F_EventScript_Maniac::
# 46 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	lock
# 47 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	msgbox DewfordTown_PokemonCenter_1F_EventScript_Maniac_Text_0
# 48 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	msgbox DewfordTown_PokemonCenter_1F_EventScript_Maniac_Text_1
# 49 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	msgbox DewfordTown_PokemonCenter_1F_EventScript_Maniac_Text_2
# 50 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	msgbox DewfordTown_PokemonCenter_1F_EventScript_Maniac_Text_3
# 51 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	msgbox DewfordTown_PokemonCenter_1F_EventScript_Maniac_Text_4
# 52 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	msgbox DewfordTown_PokemonCenter_1F_EventScript_Maniac_Text_5
# 53 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	release
	return


DewfordTown_PokemonCenter_1F_EventScript_Maniac_Text_0:
# 47 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	.string "Steel-types are finely tuned machines,\n"
	.string "and my mechanical skills help them stay\l"
	.string "in top form.$"

DewfordTown_PokemonCenter_1F_EventScript_Maniac_Text_1:
# 48 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	.string "But they have a rough time against\n"
	.string "Brawly's Fighting-types...$"

DewfordTown_PokemonCenter_1F_EventScript_Maniac_Text_2:
# 49 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	.string "The first time I faced him, my\n"
	.string "meticulously optimized Steel squad got\l"
	.string "utterly dismantled. A total systems\l"
	.string "failure!$"

DewfordTown_PokemonCenter_1F_EventScript_Maniac_Text_3:
# 50 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	.string "Brawly's all about leveraging mass\n"
	.string "against his foes with Low Kick, and,\l"
	.string "well…$"

DewfordTown_PokemonCenter_1F_EventScript_Maniac_Text_4:
# 51 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	.string "my Pokemon are polished, sturdy, and\n"
	.string "unfortunately weighty.$"

DewfordTown_PokemonCenter_1F_EventScript_Maniac_Text_5:
# 52 "data/maps/DewfordTown_PokemonCenter_1F/scripts.pory"
	.string "But this was no problem I couldn't\n"
	.string "optimize. When I unearthed a Float\l"
	.string "Stone in Granite Cave, I made Low Kick\l"
	.string "irrelevant!$"
