PacifidlogTown_House5_MapScripts::
	.byte 0

PacifidlogTown_House5_EventScript_MirageIslandWatcher::
	lock
	faceplayer
	specialvar VAR_RESULT, IsMirageIslandPresent
	goto_if_eq VAR_RESULT, TRUE, PacifidlogTown_House5_EventScript_MirageIslandPresent
	msgbox PacifidlogTown_House5_Text_CantSeeMirageIsland, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House5_EventScript_MirageIslandPresent::
	msgbox PacifidlogTown_House5_Text_CanSeeMirageIsland, MSGBOX_DEFAULT
	release
	end

PacifidlogTown_House5_EventScript_Gentleman::
	msgbox PacifidlogTown_House5_Text_MirageIslandRespondsToChosenTrainers, MSGBOX_NPC
	end

PacifidlogTown_House5_Text_CantSeeMirageIsland:
	.string "I can't see MIRAGE ISLAND…$"

PacifidlogTown_House5_Text_CanSeeMirageIsland:
	.string "Oh! Oh my!\n"
	.string "I can see MIRAGE ISLAND!$"

PacifidlogTown_House5_Text_MirageIslandRespondsToChosenTrainers:
	.string "MIRAGE ISLAND…\p"
	.string "They say it reveals itself only to\n"
	.string "TRAINERS who have proven themselves.$"
