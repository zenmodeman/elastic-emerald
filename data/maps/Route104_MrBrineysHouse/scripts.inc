# 1 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 2 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_MapScripts::
# 3 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Route104_MrBrineysHouse_OnTransition
# 4 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.byte 0
# 5 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 6 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_OnTransition:
# 7 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setflag FLAG_LANDMARK_MR_BRINEY_HOUSE
# 8 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	call_if_eq VAR_BRINEY_HOUSE_STATE, 1, Route104_MrBrineysHouse_EventScript_SetBrineyPeekoPos
# 9 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	call_if_set FLAG_RECEIVED_POKENAV, Route104_MrBrineysHouse_EventScript_HideRustboroRival
# 10 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	end
# 11 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 12 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_HideRustboroRival::
# 13 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
# 14 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	return
# 15 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 16 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_SetBrineyPeekoPos::
# 17 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setobjectxyperm LOCALID_BRINEYS_HOUSE_BRINEY, 9, 3
# 18 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setobjectmovementtype LOCALID_BRINEYS_HOUSE_BRINEY, MOVEMENT_TYPE_WALK_SEQUENCE_DOWN_LEFT_UP_RIGHT
# 19 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setobjectxyperm LOCALID_BRINEYS_HOUSE_PEEKO, 9, 6
# 20 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setobjectmovementtype LOCALID_BRINEYS_HOUSE_PEEKO, MOVEMENT_TYPE_WALK_SEQUENCE_LEFT_UP_RIGHT_DOWN
# 21 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	return
# 22 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 23 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_Briney::
# 24 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	lock
# 25 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	faceplayer
# 26 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	// goto_if_unset FLAG_DEMO_GUARD, BrineysHouse_DemoMessage
# 27 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	call_if_unset FLAG_MR_BRINEY_SAILING_INTRO, Route104_MrBrineysHouse_EventScript_SailingIntro
# 28 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	goto_if_unset FLAG_DELIVERED_STEVEN_LETTER, Route104_MrBrineysHouse_EventScript_SailBothDeliveries
# 29 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	goto_if_unset FLAG_DELIVERED_DEVON_GOODS, Route104_MrBrineysHouse_EventScript_SailDeliverPackage
# 30 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	goto Route104_MrBrineysHouse_EventScript_WhereAreWeBound
# 31 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	end
# 32 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 33 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_SailingIntro::
# 34 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setflag FLAG_MR_BRINEY_SAILING_INTRO
# 35 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	msgbox Route104_MrBrineysHouse_Text_WaitUpPeeko, MSGBOX_DEFAULT
# 36 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	msgbox Route104_MrBrineysHouse_Text_ItsYouLetsSailToDewford, MSGBOX_YESNO
# 37 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	goto_if_eq VAR_RESULT, NO, Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
# 38 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
# 39 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	end
# 40 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 41 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_WhereAreWeBound::
# 42 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	message Route104_MrBrineysHouse_Text_WhereAreWeBound
# 43 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	waitmessage
# 44 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	multichoicedefault 20, 8, MULTI_BRINEY_OFF_DEWFORD, 1, FALSE
# 45 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	switch VAR_RESULT
# 46 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	case 0, Route104_MrBrineysHouse_EventScript_SailToDewford
# 47 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	case 1, Route104_MrBrineysHouse_EventScript_DeclineSailing
# 48 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	case MULTI_B_PRESSED, Route104_MrBrineysHouse_EventScript_DeclineSailing
# 49 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	end
# 50 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 51 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_SailBothDeliveries::
# 52 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	msgbox Route104_MrBrineysHouse_Text_NeedToMakeDeliveriesSailToDewford, MSGBOX_YESNO
# 53 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	goto_if_eq VAR_RESULT, NO, Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
# 54 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
# 55 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	end
# 56 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 57 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_SailDeliverPackage::
# 58 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	msgbox Route104_MrBrineysHouse_Text_NeedToDeliverPackageSailToDewford, MSGBOX_YESNO
# 59 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	goto_if_eq VAR_RESULT, NO, Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing
# 60 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	goto Route104_MrBrineysHouse_EventScript_SailToDewford
# 61 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	end
# 62 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 63 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_DeclineDeliverySailing::
# 64 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	msgbox Route104_MrBrineysHouse_Text_DeclineDeliverySail, MSGBOX_DEFAULT
# 65 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	release
# 66 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	end
# 67 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 68 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_DeclineSailing::
# 69 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	msgbox Route104_MrBrineysHouse_Text_TellMeWheneverYouWantToSail, MSGBOX_DEFAULT
# 70 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	release
# 71 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	end
# 72 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 73 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_SailToDewford::
# 74 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	msgbox Route104_MrBrineysHouse_Text_SetSailForDewford, MSGBOX_DEFAULT
# 75 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	call EventScript_BackupMrBrineyLocation
# 76 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setvar VAR_BOARD_BRINEY_BOAT_STATE, 1
# 77 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	clearflag FLAG_HIDE_ROUTE_104_MR_BRINEY
# 78 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setflag FLAG_HIDE_BRINEYS_HOUSE_MR_BRINEY
# 79 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setflag FLAG_HIDE_BRINEYS_HOUSE_PEEKO
# 80 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setvar VAR_RUSTBORO_CITY_STATE, 8
# 81 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setvar VAR_ROUTE104_STATE, 2
# 82 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setflag FLAG_HIDE_RUSTBORO_CITY_RIVAL
# 83 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	setflag FLAG_HIDE_ROUTE_104_RIVAL
# 84 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	warp MAP_ROUTE104, 13, 51
# 85 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	waitstate
# 86 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	releaseall
# 87 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	end
# 88 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 89 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_EventScript_Peeko::
# 90 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	lock
# 91 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	faceplayer
# 92 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	waitse
# 93 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	playmoncry SPECIES_WINGULL, CRY_MODE_NORMAL
# 94 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	msgbox Route104_MrBrineysHouse_Text_Peeko, MSGBOX_DEFAULT
# 95 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	waitmoncry
# 96 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	release
# 97 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	end
# 98 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 99 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_Text_WaitUpPeeko:
# 100 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "MR. BRINEY: Hold on, lass!\n"
# 101 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "Wait up, PEEKO!$"
# 102 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 103 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_Text_ItsYouLetsSailToDewford:
# 104 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "Hm? You're {PLAYER}{KUN}!\n"
# 105 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "You saved my darling PEEKO!\l"
# 106 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "We owe so much to you!\p"
# 107 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "What's that?\n"
# 108 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "You want to sail with me?\p"
# 109 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "Hmhm…\p"
# 110 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "You have a LETTER bound for DEWFORD\n"
# 111 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "and a package for SLATEPORT, then?\p"
# 112 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "Quite the busy life you must lead!\p"
# 113 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "But, certainly, what you're asking is\n"
# 114 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "no problem at all.\p"
# 115 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "You've come to the right man!\n"
# 116 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "We'll set sail for DEWFORD.$"
# 117 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 118 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_Text_SetSailForDewford:
# 119 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "MR. BRINEY: DEWFORD it is, then!\p"
# 120 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "Anchors aweigh!\n"
# 121 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "PEEKO, we're setting sail, my darling!$"
# 122 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 123 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_Text_DeclineDeliverySail:
# 124 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "MR. BRINEY: Is that so?\n"
# 125 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "Your deliveries can wait?\p"
# 126 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "You just go on and tell me whenever\n"
# 127 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "you want to set sail!$"
# 128 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 129 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_Text_NeedToMakeDeliveriesSailToDewford:
# 130 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "MR. BRINEY: Ahoy!\n"
# 131 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "I know exactly what you want to say!\p"
# 132 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "You're to deliver a LETTER to DEWFORD\n"
# 133 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "and a package to SLATEPORT.\p"
# 134 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "What you need me to do is no problem\n"
# 135 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "at all--I'm the man for the job!\p"
# 136 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "First, we'll set sail for DEWFORD.$"
# 137 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 138 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_Text_NeedToDeliverPackageSailToDewford:
# 139 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "MR. BRINEY: Ahoy!\n"
# 140 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "I know exactly what you want to say!\p"
# 141 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "You're to deliver a package to\n"
# 142 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "CAPT. STERN in SLATEPORT.\p"
# 143 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "What you need me to do is no problem\n"
# 144 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "at all--I'm the man for the job!\p"
# 145 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "First, we'll set sail for DEWFORD.$"
# 146 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 147 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_Text_WhereAreWeBound:
# 148 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "MR. BRINEY: Ahoy!\n"
# 149 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "For you, I'll go out to sea anytime!\p"
# 150 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "Now, my friend, where are we bound?$"
# 151 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 152 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_Text_TellMeWheneverYouWantToSail:
# 153 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "MR. BRINEY: Is that so?\n"
# 154 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "Well, PEEKO owes her life to you.\p"
# 155 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "You just go on and tell me whenever\n"
# 156 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "you want to set sail!$"
# 157 "data/maps/Route104_MrBrineysHouse/scripts.pory"

# 158 "data/maps/Route104_MrBrineysHouse/scripts.pory"
Route104_MrBrineysHouse_Text_Peeko:
# 159 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "PEEKO: Pii piihyoro!$"

BrineysHouse_DemoMessage::
# 165 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	msgbox BrineysHouse_DemoMessage_Text_0
# 166 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	releaseall
	end


BrineysHouse_DemoMessage_Text_0:
# 165 "data/maps/Route104_MrBrineysHouse/scripts.pory"
	.string "This demo does not go to Dewford until\n"
	.string "v.0.2.0 releases.$"
