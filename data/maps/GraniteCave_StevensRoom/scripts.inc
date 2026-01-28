# 1 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 2 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_MapScripts::
# 3 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.byte 0
# 4 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 5 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_EventScript_Steven::
# 6 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	lock
# 7 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	faceplayer
# 8 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	msgbox GraniteCave_StevensRoom_Text_ImStevenLetterForMe, MSGBOX_DEFAULT
# 9 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	setvar VAR_0x8004, ITEM_LETTER
# 10 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	call Common_EventScript_PlayerHandedOverTheItem
# 11 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	setflag FLAG_DELIVERED_STEVEN_LETTER
# 12 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	call Steven_Gives_Tera_Orb
# 13 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	msgbox GraniteCave_StevensRoom_Text_CouldBecomeChampionLetsRegister, MSGBOX_DEFAULT
# 14 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	closemessage
# 15 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	delay 30
# 16 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	playfanfare MUS_REGISTER_MATCH_CALL
# 17 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	msgbox GraniteCave_StevensRoom_Text_RegisteredSteven, MSGBOX_DEFAULT
# 18 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	waitfanfare
# 19 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	closemessage
# 20 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	delay 30
# 21 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	setflag FLAG_REGISTERED_STEVEN_POKENAV
# 22 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	msgbox GraniteCave_StevensRoom_Text_IveGotToHurryAlong, MSGBOX_DEFAULT
# 23 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	closemessage
# 24 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	call_if_eq VAR_FACING, DIR_NORTH, GraniteCave_StevensRoom_EventScript_StevenExitNorth
# 25 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	call_if_eq VAR_FACING, DIR_SOUTH, GraniteCave_StevensRoom_EventScript_StevenExitSouth
# 26 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	call_if_eq VAR_FACING, DIR_WEST, GraniteCave_StevensRoom_EventScript_StevenExitWestEast
# 27 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	call_if_eq VAR_FACING, DIR_EAST, GraniteCave_StevensRoom_EventScript_StevenExitWestEast
# 28 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	playse SE_EXIT
# 29 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	removeobject LOCALID_GRANITE_CAVE_STEVEN
# 30 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	release
# 31 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	end
# 32 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 33 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_EventScript_StevenExitNorth::
# 34 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	applymovement LOCALID_GRANITE_CAVE_STEVEN, GraniteCave_StevensRoom_Movement_StevenExit
# 35 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	waitmovement 0
# 36 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	return
# 37 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 38 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_EventScript_StevenExitWestEast::
# 39 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	applymovement LOCALID_PLAYER, GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit
# 40 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	applymovement LOCALID_GRANITE_CAVE_STEVEN, GraniteCave_StevensRoom_Movement_StevenExit
# 41 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	waitmovement 0
# 42 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	return
# 43 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 44 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_EventScript_StevenExitSouth::
# 45 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	applymovement LOCALID_PLAYER, GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit
# 46 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	applymovement LOCALID_GRANITE_CAVE_STEVEN, GraniteCave_StevensRoom_Movement_StevenExitSouth
# 47 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	waitmovement 0
# 48 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	return
# 49 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 50 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_EventScript_BagFull::
# 51 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	msgbox GraniteCave_StevensRoom_Text_OhBagIsFull, MSGBOX_DEFAULT
# 52 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	return
# 53 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 54 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_Movement_StevenExit:
# 55 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_up
# 56 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_up
# 57 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_up
# 58 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_up
# 59 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_up
# 60 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	delay_8
# 61 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	step_end
# 62 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 63 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit:
# 64 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	delay_16
# 65 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	delay_16
# 66 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	delay_16
# 67 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_in_place_faster_up
# 68 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	step_end
# 69 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 70 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_Movement_StevenExitSouth:
# 71 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_left
# 72 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_up
# 73 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_up
# 74 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_up
# 75 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_right
# 76 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_up
# 77 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_up
# 78 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	delay_8
# 79 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	step_end
# 80 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 81 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_Text_ImStevenLetterForMe:
# 82 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "My name is STEVEN.\p"
# 83 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "I'm interested in rare stones,\n"
# 84 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "so I travel here and there.\p"
# 85 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "Oh?\n"
# 86 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "A LETTER for me?$"
# 87 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 88 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_Text_ThankYouTakeThis:
# 89 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "STEVEN: Okay, thank you.\p"
# 90 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "You went through all this trouble to\n"
# 91 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "deliver that. I need to thank you.\p"
# 92 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "Let me see…\n"
# 93 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "I'll give you this TM.\p"
# 94 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "It contains my favorite move,\n"
# 95 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "STEEL WING.$"
# 96 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 97 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_Text_CouldBecomeChampionLetsRegister:
# 98 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "STEVEN: Your POKéMON appear quite\n"
# 99 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "capable.\p"
# 100 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "If you keep training, you could even\n"
# 101 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "become the CHAMPION of the POKéMON\l"
# 102 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "LEAGUE one day. That's what I think.\p"
# 103 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "I know, since we've gotten to know each\n"
# 104 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "other, let's register one another in\l"
# 105 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "our POKéNAVS.\p"
# 106 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "… … … … … …$"
# 107 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 108 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_Text_RegisteredSteven:
# 109 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "Registered STEVEN\n"
# 110 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "in the POKéNAV.$"
# 111 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 112 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_Text_IveGotToHurryAlong:
# 113 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "Now, I've got to hurry along.$"
# 114 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 115 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_Text_OhBagIsFull:
# 116 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "Oh, your BAG is full…\n"
# 117 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "That's too bad, then.$"

Steven_Gives_Tera_Orb::
# 123 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	msgbox Steven_Gives_Tera_Orb_Text_0
# 124 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	msgbox Steven_Gives_Tera_Orb_Text_1
# 125 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	msgbox Steven_Gives_Tera_Orb_Text_2
# 126 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	msgbox Steven_Gives_Tera_Orb_Text_3
# 127 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	giveitem ITEM_TERA_ORB
# 128 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Steven_Gives_Tera_Orb_2
Steven_Gives_Tera_Orb_1:
# 131 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	setflag FLAG_TERA_CHARGED
# 132 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	msgbox Steven_Gives_Tera_Orb_Text_4
	return

Steven_Gives_Tera_Orb_2:
# 129 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	call Common_EventScript_ShowBagIsFull
	goto Steven_Gives_Tera_Orb_1


Steven_Gives_Tera_Orb_Text_0:
# 123 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "STEVEN: Okay, thank you.$"

Steven_Gives_Tera_Orb_Text_1:
# 124 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "You went through all this trouble to\n"
	.string "deliver that. I need to thank you.$"

Steven_Gives_Tera_Orb_Text_2:
# 125 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "Let me see…$"

Steven_Gives_Tera_Orb_Text_3:
# 126 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "I'll give you a Tera Orb. These haven't\n"
	.string "caught on in the Hoenn Region yet.$"

Steven_Gives_Tera_Orb_Text_4:
# 132 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "With this, you'll be able to use the\n"
	.string "Terastal Phenomenon with your Pokemon!$"
