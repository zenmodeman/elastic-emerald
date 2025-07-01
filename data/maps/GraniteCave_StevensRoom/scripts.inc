# 1 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 2 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 3 "data/maps/GraniteCave_StevensRoom/scripts.pory"
.set LOCALID_STEVEN, 1
# 4 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 5 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_MapScripts::
# 6 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.byte 0
# 7 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 8 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_EventScript_Steven::
# 9 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	lock
# 10 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	faceplayer
# 11 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	msgbox GraniteCave_StevensRoom_Text_ImStevenLetterForMe, MSGBOX_DEFAULT
# 12 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	setvar VAR_0x8004, ITEM_LETTER
# 13 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	call Common_EventScript_PlayerHandedOverTheItem
# 14 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	setflag FLAG_DELIVERED_STEVEN_LETTER
# 15 "data/maps/GraniteCave_StevensRoom/scripts.pory"
    call Steven_Gives_Tera_Orb
# 16 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	msgbox GraniteCave_StevensRoom_Text_CouldBecomeChampionLetsRegister, MSGBOX_DEFAULT
# 17 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	closemessage
# 18 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	delay 30
# 19 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	playfanfare MUS_REGISTER_MATCH_CALL
# 20 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	msgbox GraniteCave_StevensRoom_Text_RegisteredSteven, MSGBOX_DEFAULT
# 21 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	waitfanfare
# 22 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	closemessage
# 23 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	delay 30
# 24 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	setflag FLAG_REGISTERED_STEVEN_POKENAV
# 25 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	msgbox GraniteCave_StevensRoom_Text_IveGotToHurryAlong, MSGBOX_DEFAULT
# 26 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	closemessage
# 27 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	call_if_eq VAR_FACING, DIR_NORTH, GraniteCave_StevensRoom_EventScript_StevenExitNorth
# 28 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	call_if_eq VAR_FACING, DIR_SOUTH, GraniteCave_StevensRoom_EventScript_StevenExitSouth
# 29 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	call_if_eq VAR_FACING, DIR_WEST, GraniteCave_StevensRoom_EventScript_StevenExitWestEast
# 30 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	call_if_eq VAR_FACING, DIR_EAST, GraniteCave_StevensRoom_EventScript_StevenExitWestEast
# 31 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	playse SE_EXIT
# 32 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	removeobject LOCALID_STEVEN
# 33 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	release
# 34 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	end
# 35 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 36 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_EventScript_StevenExitNorth::
# 37 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	applymovement LOCALID_STEVEN, GraniteCave_StevensRoom_Movement_StevenExit
# 38 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	waitmovement 0
# 39 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	return
# 40 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 41 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_EventScript_StevenExitWestEast::
# 42 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit
# 43 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	applymovement LOCALID_STEVEN, GraniteCave_StevensRoom_Movement_StevenExit
# 44 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	waitmovement 0
# 45 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	return
# 46 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 47 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_EventScript_StevenExitSouth::
# 48 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit
# 49 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	applymovement LOCALID_STEVEN, GraniteCave_StevensRoom_Movement_StevenExitSouth
# 50 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	waitmovement 0
# 51 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	return
# 52 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 53 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_EventScript_BagFull::
# 54 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	msgbox GraniteCave_StevensRoom_Text_OhBagIsFull, MSGBOX_DEFAULT
# 55 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	return
# 56 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 57 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_Movement_StevenExit:
# 58 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_up
# 59 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_up
# 60 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_up
# 61 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_up
# 62 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_up
# 63 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	delay_8
# 64 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	step_end
# 65 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 66 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_Movement_PlayerTurnTowardExit:
# 67 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	delay_16
# 68 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	delay_16
# 69 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	delay_16
# 70 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_in_place_faster_up
# 71 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	step_end
# 72 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 73 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_Movement_StevenExitSouth:
# 74 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_left
# 75 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_up
# 76 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_up
# 77 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_up
# 78 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_right
# 79 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_up
# 80 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	walk_up
# 81 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	delay_8
# 82 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	step_end
# 83 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 84 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_Text_ImStevenLetterForMe:
# 85 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "My name is STEVEN.\p"
# 86 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "I'm interested in rare stones,\n"
# 87 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "so I travel here and there.\p"
# 88 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "Oh?\n"
# 89 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "A LETTER for me?$"
# 90 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 91 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_Text_ThankYouTakeThis:
# 92 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "STEVEN: Okay, thank you.\p"
# 93 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "You went through all this trouble to\n"
# 94 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "deliver that. I need to thank you.\p"
# 95 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "Let me see…\n"
# 96 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "I'll give you this TM.\p"
# 97 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "It contains my favorite move,\n"
# 98 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "STEEL WING.$"
# 99 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 100 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_Text_CouldBecomeChampionLetsRegister:
# 101 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "STEVEN: Your POKéMON appear quite\n"
# 102 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "capable.\p"
# 103 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "If you keep training, you could even\n"
# 104 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "become the CHAMPION of the POKéMON\l"
# 105 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "LEAGUE one day. That's what I think.\p"
# 106 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "I know, since we've gotten to know each\n"
# 107 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "other, let's register one another in\l"
# 108 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "our POKéNAVS.\p"
# 109 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "… … … … … …$"
# 110 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 111 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_Text_RegisteredSteven:
# 112 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "Registered STEVEN\n"
# 113 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "in the POKéNAV.$"
# 114 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 115 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_Text_IveGotToHurryAlong:
# 116 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "Now, I've got to hurry along.$"
# 117 "data/maps/GraniteCave_StevensRoom/scripts.pory"

# 118 "data/maps/GraniteCave_StevensRoom/scripts.pory"
GraniteCave_StevensRoom_Text_OhBagIsFull:
# 119 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "Oh, your BAG is full…\n"
# 120 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "That's too bad, then.$"

Steven_Gives_Tera_Orb::
# 126 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	msgbox Steven_Gives_Tera_Orb_Text_0
# 127 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	msgbox Steven_Gives_Tera_Orb_Text_1
# 128 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	msgbox Steven_Gives_Tera_Orb_Text_2
# 129 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	msgbox Steven_Gives_Tera_Orb_Text_3
# 130 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	giveitem ITEM_TERA_ORB
# 131 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Steven_Gives_Tera_Orb_2
Steven_Gives_Tera_Orb_1:
# 134 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	setflag FLAG_TERA_CHARGED
# 135 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	msgbox Steven_Gives_Tera_Orb_Text_4
	return

Steven_Gives_Tera_Orb_2:
# 132 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	call Common_EventScript_ShowBagIsFull
	goto Steven_Gives_Tera_Orb_1


Steven_Gives_Tera_Orb_Text_0:
# 126 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "STEVEN: Okay, thank you.$"

Steven_Gives_Tera_Orb_Text_1:
# 127 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "You went through all this trouble to\n"
	.string "deliver that. I need to thank you.$"

Steven_Gives_Tera_Orb_Text_2:
# 128 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "Let me see…$"

Steven_Gives_Tera_Orb_Text_3:
# 129 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "I'll give you a Tera Orb. These haven't\n"
	.string "caught on in the Hoenn Region yet.$"

Steven_Gives_Tera_Orb_Text_4:
# 135 "data/maps/GraniteCave_StevensRoom/scripts.pory"
	.string "With this, you'll be able to use the\n"
	.string "Terastal Phenomenon with your Pokemon!$"
