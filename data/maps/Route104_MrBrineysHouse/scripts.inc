# 1 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 2 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 3 "data/maps/Route104_MrBrineysHouse/scripts.pory"
.set LOCALID_BRINEY, 1
# 4 "data/maps/Route104_MrBrineysHouse/scripts.pory"
.set LOCALID_PEEKO, 2
# 5 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 6 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_MapScripts::
# 7 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Route104_MrBrineysHouse_OnTransition
# 8 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.byte 0
# 9 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 10 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_OnTransition:
# 11 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setflag FLAG_LANDMARK_MR_BRINEY_HOUSE
# 12 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	call_if_eq VAR_BRINEY_HOUSE_STATE, 1, Route104_MrBrineysHouse_EventScript_SetBrineyPeekoPos
# 13 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	call_if_set FLAG_RECEIVED_POKENAV, Route104_MrBrineysHouse_EventScript_HideRustboroRival
# 14 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	end
# 15 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 16 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_HideRustboroRival::
# 17 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
# 18 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	return
# 19 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 20 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_SetBrineyPeekoPos::
# 21 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setobjectxyperm LOCALID_BRINEY, 9, 3
# 22 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setobjectmovementtype LOCALID_BRINEY, MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_UP_RIGHT
# 23 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setobjectxyperm LOCALID_PEEKO, 9, 6
# 24 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setobjectmovementtype LOCALID_PEEKO, MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_RIGHT_DOWN
# 25 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	return
# 26 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 27 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_Briney::
# 28 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	lock
# 29 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	faceplayer
# 30 "data/maps/Route104_MrBrineysHouse/scripts.pory"
    // goto_if_unset FLAG_DEMO_GUARD, BrineysHouse_DemoMessage
# 31 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	call_if_unset FLAG_MR_BRINEY_SAILING_INTRO, Route104_MrBrineysHouse_EventScript_SailingIntro
# 32 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	goto_if_unset FLAG_DELIVERED_STEVEN_LETTER, Route104_MrBrineysHouse_EventScript_SailBothDeliveries
# 33 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	goto_if_unset FLAG_DELIVERED_DEVON_GOODS, Route104_MrBrineysHouse_EventScript_SailDeliverPackage
# 34 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	goto Route104_MrBrineysHouse_EventScript_WhereAreWeBound
# 35 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	end
# 36 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 37 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_SailingIntro::
# 38 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setflag FLAG_MR_BRINEY_SAILING_INTRO
# 39 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	msgbox Route104_MrBrineysHouse_Text_WaitUpPeeko, MSGBOX_DEFAULT
# 40 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	msgbox Route104_MrBrineysHouse_Text_ItsYouLetsSailToDewford, MSGBOX_YESNO
# 41 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	goto_if_eq VAR_RESULT, NO, Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
# 42 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
# 43 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	end
# 44 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 45 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_WhereAreWeBound::
# 46 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	message Route104_MrBrineysHouse_Text_WhereAreWeBound
# 47 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	waitmessage
# 48 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	multichoicedefault 20, 8, MULTI_BRINEY_OFF_DEWFORD, 1, FALSE
# 49 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	switch VAR_RESULT
# 50 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	case 0, Route104_MrBrineysHouse_EventScript_SailToDewford
# 51 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	case 1, Route104_MrBrineysHouse_EventScript_DeclineSailing
# 52 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	case MULTI_B_PRESSED, Route104_MrBrineysHouse_EventScript_DeclineSailing
# 53 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	end
# 54 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 55 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_SailBothDeliveries::
# 56 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	msgbox Route104_MrBrineysHouse_Text_NeedToMakeDeliveriesSailToDewford, MSGBOX_YESNO
# 57 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	goto_if_eq VAR_RESULT, NO, Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
# 58 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
# 59 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	end
# 60 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 61 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_SailDeliverPackage::
# 62 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	msgbox Route104_MrBrineysHouse_Text_NeedToDeliverPackageSailToDewford, MSGBOX_YESNO
# 63 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	goto_if_eq VAR_RESULT, NO, Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
# 64 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
# 65 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	end
# 66 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 67 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing::
# 68 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	msgbox Route104_MrBrineysHouse_Text_DeclineDeliverySail, MSGBOX_DEFAULT
# 69 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	release
# 70 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	end
# 71 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 72 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_DeclineSailing::
# 73 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	msgbox Route104_MrBrineysHouse_Text_TellMeWheneverYouWantToSail, MSGBOX_DEFAULT
# 74 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	release
# 75 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	end
# 76 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 77 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_SailToDewford::
# 78 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	msgbox Route104_MrBrineysHouse_Text_SetSailForDewford, MSGBOX_DEFAULT
# 79 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	call EventScript_BackupMrBrineyLocation
# 80 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setvar VAR_BOARD_BRINEY_BOAT_STATE, 1
# 81 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	clearflag FLAG_HIDE_ROUTE_104_MR_BRINEY
# 82 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
# 83 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
# 84 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setvar VAR_RUSTBORO_CITY_STATE, 8
# 85 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setvar VAR_ROUTE104_STATE, 2
# 86 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
# 87 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setflag FLAG_HIDE_ROUTE_104_RIVAL
# 88 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	warp MAP_ROUTE104, 13, 51
# 89 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	waitstate
# 90 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	releaseall
# 91 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	end
# 92 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 93 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_Peeko::
# 94 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	lock
# 95 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	faceplayer
# 96 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	waitse
# 97 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
# 98 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	msgbox Route104_MrBrineysHouse_Text_Peeko, MSGBOX_DEFAULT
# 99 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	waitmoncry
# 100 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	release
# 101 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	end
# 102 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 103 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_Text_WaitUpPeeko:
# 104 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "MR. BRINEY: Hold on, lass!\n"
# 105 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "Wait up, PEEKO!$"
# 106 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 107 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_Text_ItsYouLetsSailToDewford:
# 108 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "Hm? You're {PLAYER}{KUN}!\n"
# 109 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "You saved my darling PEEKO!\l"
# 110 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "We owe so much to you!\p"
# 111 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "What's that?\n"
# 112 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "You want to sail with me?\p"
# 113 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "Hmhm…\p"
# 114 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "You have a LETTER bound for DEWFORD\n"
# 115 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "and a package for SLATEPORT, then?\p"
# 116 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "Quite the busy life you must lead!\p"
# 117 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "But, certainly, what you're asking is\n"
# 118 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "no problem at all.\p"
# 119 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "You've come to the right man!\n"
# 120 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "We'll set sail for DEWFORD.$"
# 121 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 122 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_Text_SetSailForDewford:
# 123 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "MR. BRINEY: DEWFORD it is, then!\p"
# 124 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "Anchors aweigh!\n"
# 125 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "PEEKO, we're setting sail, my darling!$"
# 126 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 127 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_Text_DeclineDeliverySail:
# 128 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "MR. BRINEY: Is that so?\n"
# 129 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "Your deliveries can wait?\p"
# 130 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "You just go on and tell me whenever\n"
# 131 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "you want to set sail!$"
# 132 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 133 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_Text_NeedToMakeDeliveriesSailToDewford:
# 134 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "MR. BRINEY: Ahoy!\n"
# 135 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "I know exactly what you want to say!\p"
# 136 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "You're to deliver a LETTER to DEWFORD\n"
# 137 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "and a package to SLATEPORT.\p"
# 138 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "What you need me to do is no problem\n"
# 139 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "at all--I'm the man for the job!\p"
# 140 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "First, we'll set sail for DEWFORD.$"
# 141 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 142 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_Text_NeedToDeliverPackageSailToDewford:
# 143 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "MR. BRINEY: Ahoy!\n"
# 144 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "I know exactly what you want to say!\p"
# 145 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "You're to deliver a package to\n"
# 146 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "CAPT. STERN in SLATEPORT.\p"
# 147 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "What you need me to do is no problem\n"
# 148 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "at all--I'm the man for the job!\p"
# 149 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "First, we'll set sail for DEWFORD.$"
# 150 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 151 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_Text_WhereAreWeBound:
# 152 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "MR. BRINEY: Ahoy!\n"
# 153 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "For you, I'll go out to sea anytime!\p"
# 154 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "Now, my friend, where are we bound?$"
# 155 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 156 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_Text_TellMeWheneverYouWantToSail:
# 157 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "MR. BRINEY: Is that so?\n"
# 158 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "Well, PEEKO owes her life to you.\p"
# 159 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "You just go on and tell me whenever\n"
# 160 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "you want to set sail!$"
# 161 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 162 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_Text_Peeko:
# 163 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "PEEKO: Pii piihyoro!$"

BrineysHouse_DemoMessage::
# 169 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	msgbox BrineysHouse_DemoMessage_Text_0
# 170 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	releaseall
	end


BrineysHouse_DemoMessage_Text_0:
# 169 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "This demo does not go to Dewford until\n"
	.string "v.0.2.0 releases.$"
