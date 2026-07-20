MirageIsland_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, MirageIsland_OnTransition
	.byte 0

MirageIsland_OnTransition:
	special PrepareMirageIslandEncounter
	goto_if_eq VAR_RESULT, FALSE, MirageIsland_EventScript_HideEncounter
	clearflag FLAG_TEMP_12
	end

MirageIsland_EventScript_HideEncounter:
	setflag FLAG_TEMP_12
	end

MirageIsland_EventScript_Encounter::
	lock
	faceplayer
	message MirageIsland_Text_Encounter
	waitmessage
	waitbuttonpress
	special StartMirageIslandEncounter
	waitstate
	copyvar VAR_MIRAGE_ISLAND_ENCOUNTER_DAY, VAR_DAYS
	addvar VAR_MIRAGE_ISLAND_ENCOUNTER_DAY, 1
	setflag FLAG_TEMP_12
	removeobject LOCALID_MIRAGE_ISLAND_ENCOUNTER
	release
	end

MirageIsland_EventScript_ExitPortal::
	lock
	faceplayer
	msgbox MirageIsland_Text_ExitPortal, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, MirageIsland_EventScript_DeclineExit
	warp MAP_ROUTE130, 54, 11
	waitstate
	end

MirageIsland_EventScript_DeclineExit:
	release
	end

MirageIsland_Text_Encounter:
	.string "A mysterious POKéMON is watching you…$"

MirageIsland_Text_ExitPortal:
	.string "The stone reflects the waves of\n"
	.string "ROUTE 130. Return there?$"
