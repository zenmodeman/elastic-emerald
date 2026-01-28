# 1 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 2 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_MapScripts::
# 3 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_1F_OnTransition
# 4 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.byte 0
# 5 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 6 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_OnTransition:
# 7 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	call_if_unset FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_BlockStairs
# 8 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 9 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 10 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_BlockStairs::
# 11 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	setobjectxyperm LOCALID_DEVON_CORP_STAIR_GUARD, 14, 2
# 12 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	setobjectmovementtype LOCALID_DEVON_CORP_STAIR_GUARD, MOVEMENT_TYPE_FACE_DOWN
# 13 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	return
# 14 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 15 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_Employee::
# 16 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	lock
# 17 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	faceplayer
# 18 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered
# 19 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright
# 20 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct, MSGBOX_DEFAULT
# 21 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	release
# 22 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 23 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 24 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright::
# 25 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright, MSGBOX_DEFAULT
# 26 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	release
# 27 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 28 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 29 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered::
# 30 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered, MSGBOX_DEFAULT
# 31 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	release
# 32 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 33 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 34 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_StairGuard::
# 35 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	lock
# 36 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	faceplayer
# 37 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome
# 38 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
# 39 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
# 40 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter, MSGBOX_DEFAULT
# 41 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	release
# 42 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 43 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 44 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome::
# 45 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere, MSGBOX_DEFAULT
# 46 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	release
# 47 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 48 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 49 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_GotRobbed::
# 50 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed, MSGBOX_DEFAULT
# 51 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	release
# 52 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 53 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 54 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_Greeter::
# 55 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	lock
# 56 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	faceplayer
# 57 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp
# 58 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
# 59 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
# 60 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
# 61 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	release
# 62 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 63 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 64 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp::
# 65 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
# 66 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	release
# 67 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 68 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 69 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed::
# 70 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_StaffGotRobbed, MSGBOX_DEFAULT
# 71 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	release
# 72 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 73 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 74 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_RocksMetalDisplay::
# 75 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay, MSGBOX_SIGN
# 76 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 77 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 78 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_ProductsDisplay::
# 79 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_ProductDisplay, MSGBOX_SIGN
# 80 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 81 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 82 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp:
# 83 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Hello and welcome to the DEVON\n"
# 84 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "CORPORATION.\p"
# 85 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "We're proud producers of items and\n"
# 86 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "medicine that enhance your life.$"
# 87 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 88 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_Text_StaffGotRobbed:
# 89 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "One of our research staff stupidly\n"
# 90 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "got robbed of an important parcel.$"
# 91 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 92 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct:
# 93 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Hey, those RUNNING SHOES!\n"
# 94 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "They're one of our products!\p"
# 95 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "It makes me happy when I see someone\n"
# 96 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "using something we made.$"
# 97 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 98 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright:
# 99 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "That stolen parcel…\p"
# 100 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Well, sure it's important, but it's not\n"
# 101 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "anything that anyone can use.\p"
# 102 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "In my estimation, that robber must not\n"
# 103 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "have been very bright.$"
# 104 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 105 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered:
# 106 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "It sounds like they've recovered\n"
# 107 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "the ripped-off DEVON GOODS.$"
# 108 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 109 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter:
# 110 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "I'm sorry, only authorized people\n"
# 111 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "are allowed to enter here.$"
# 112 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 113 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed:
# 114 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "It's beyond stupid.\n"
# 115 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "How could we get robbed?$"
# 116 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 117 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere:
# 118 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Hi, there!\n"
# 119 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "You're always welcome here!$"
# 120 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 121 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay:
# 122 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Samples of rocks and metal are\n"
# 123 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "displayed in the glass case.\p"
# 124 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "There's a panel with some writing\n"
# 125 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "on it…\p"
# 126 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "“DEVON CORPORATION got its start as\n"
# 127 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "a producer of stones from quarries.\p"
# 128 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "“The company also produced iron from\n"
# 129 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "filings in the sand.\p"
# 130 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "“From that humble start as a producer\n"
# 131 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "of raw materials, DEVON developed.\p"
# 132 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "“DEVON is now a manufacturer of a wide\n"
# 133 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "range of industrial products.”$"
# 134 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 135 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_Text_ProductDisplay:
# 136 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Prototypes and test products fill\n"
# 137 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "the glass display case.\p"
# 138 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "There's a panel with a description…\p"
# 139 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "“In addition to industrial products,\n"
# 140 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "DEVON now markets sundries and\l"
# 141 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "pharmaceuticals for better lifestyles.\p"
# 142 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "“Recently, DEVON has begun marketing\n"
# 143 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "tools for POKéMON TRAINERS, including\l"
# 144 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "POKé BALLS and POKéNAV systems.”$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer::
# 148 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	lock
# 149 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_0
# 150 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_1
# 152 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	checkitem ITEM_PLAIN_BOTTLE_CAP
# 153 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_1F_EventScript_IVTrainer_2
RustboroCity_DevonCorp_1F_EventScript_IVTrainer_1:
# 156 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	checkitem ITEM_BOTTLE_CAP
# 157 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_1F_EventScript_IVTrainer_5
RustboroCity_DevonCorp_1F_EventScript_IVTrainer_4:
# 160 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	checkitem ITEM_GOLD_BOTTLE_CAP
# 161 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_1F_EventScript_IVTrainer_8
RustboroCity_DevonCorp_1F_EventScript_IVTrainer_7:
# 164 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_5, ITEM_NONE
# 165 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	dynmultistack 0, 0, FALSE, 6, FALSE, ITEM_NONE, DYN_MULTICHOICE_CB_NONE
# 166 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_RESULT, ITEM_NONE
	goto_if_eq RustboroCity_DevonCorp_1F_EventScript_IVTrainer_11
# 166 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq RustboroCity_DevonCorp_1F_EventScript_IVTrainer_11
RustboroCity_DevonCorp_1F_EventScript_IVTrainer_10:
# 169 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_RESULT, ITEM_PLAIN_BOTTLE_CAP
	goto_if_eq RustboroCity_DevonCorp_1F_EventScript_IVTrainer_16
# 186 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_RESULT, ITEM_BOTTLE_CAP
	goto_if_eq RustboroCity_DevonCorp_1F_EventScript_IVTrainer_17
# 203 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_RESULT, ITEM_GOLD_BOTTLE_CAP
	goto_if_eq RustboroCity_DevonCorp_1F_EventScript_IVTrainer_18
RustboroCity_DevonCorp_1F_EventScript_IVTrainer_15:
# 220 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	releaseall
	end

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_2:
# 154 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_2, ITEM_PLAIN_BOTTLE_CAP
	goto RustboroCity_DevonCorp_1F_EventScript_IVTrainer_1

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_5:
# 158 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_3, ITEM_BOTTLE_CAP
	goto RustboroCity_DevonCorp_1F_EventScript_IVTrainer_4

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_8:
# 162 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_4, ITEM_GOLD_BOTTLE_CAP
	goto RustboroCity_DevonCorp_1F_EventScript_IVTrainer_7

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_11:
# 167 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	goto RustboroCity_DevonCorp_1F_IVTrainer_Farewell
	goto RustboroCity_DevonCorp_1F_EventScript_IVTrainer_10

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_16:
# 170 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_6
# 171 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	waitmessage
# 172 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	call IVTrainer_ChooseStat
# 173 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	call IVTrainer_ChooseMon
# 174 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	specialvar VAR_RESULT, TrainPlainIV
# 175 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq RustboroCity_DevonCorp_1F_EventScript_IVTrainer_23
# 181 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 182 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	waitfanfare
# 183 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	removeitem ITEM_PLAIN_BOTTLE_CAP, 1
# 184 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_8
# 185 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	waitmessage
	goto RustboroCity_DevonCorp_1F_EventScript_IVTrainer_15

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_17:
# 187 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_9
# 188 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	waitmessage
# 189 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	call IVTrainer_ChooseStat
# 190 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	call IVTrainer_ChooseMon
# 191 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	specialvar VAR_RESULT, TrainMaxIV
# 192 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq RustboroCity_DevonCorp_1F_EventScript_IVTrainer_26
# 198 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 199 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	waitfanfare
# 200 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	removeitem ITEM_BOTTLE_CAP, 1
# 201 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_8
# 202 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	waitmessage
	goto RustboroCity_DevonCorp_1F_EventScript_IVTrainer_15

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_18:
# 204 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_10
# 205 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	waitmessage
# 206 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	call IVTrainer_ChooseMon
# 207 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	specialvar VAR_RESULT, TrainMaxIVs
# 208 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq RustboroCity_DevonCorp_1F_EventScript_IVTrainer_29
# 214 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 215 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	waitfanfare
# 216 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	removeitem ITEM_GOLD_BOTTLE_CAP, 1
# 217 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_8
# 218 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	waitmessage
	goto RustboroCity_DevonCorp_1F_EventScript_IVTrainer_15

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_23:
# 176 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_7
# 177 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	waitmessage
# 178 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	releaseall
	end

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_26:
# 193 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_7
# 194 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	waitmessage
# 195 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	releaseall
	end

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_29:
# 209 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_11
# 210 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	waitmessage
# 211 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	releaseall
	end


IVTrainer_ChooseStat::
# 225 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox IVTrainer_ChooseStat_Text_0
# 226 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	dynmultichoice 20, 100, FALSE, 5, 0, DYN_MULTICHOICE_CB_NONE, IVTrainer_ChooseStat_Text_1, IVTrainer_ChooseStat_Text_2, IVTrainer_ChooseStat_Text_3, IVTrainer_ChooseStat_Text_4, IVTrainer_ChooseStat_Text_5, IVTrainer_ChooseStat_Text_6, RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_5
# 227 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_RESULT, 6
	goto_if_eq IVTrainer_ChooseStat_2
# 227 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_RESULT, MULTI_B_PRESSED
	goto_if_eq IVTrainer_ChooseStat_2
IVTrainer_ChooseStat_1:
# 230 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	copyvar VAR_TEMP_1, VAR_RESULT
	return

IVTrainer_ChooseStat_2:
# 228 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	goto RustboroCity_DevonCorp_1F_IVTrainer_Farewell
	goto IVTrainer_ChooseStat_1


RustboroCity_DevonCorp_1F_IVTrainer_Farewell::
# 233 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_IVTrainer_Farewell_Text_0
# 234 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	releaseall
	end


IVTrainer_ChooseMon::
# 239 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox IVTrainer_ChooseMon_Text_0
# 240 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	special ChoosePartyMon
# 241 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	waitstate
# 242 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_0x8004, PARTY_NOTHING_CHOSEN
	goto_if_eq IVTrainer_ChooseMon_1
	return

IVTrainer_ChooseMon_1:
# 243 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox IVTrainer_ChooseMon_Text_1
# 244 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	waitmessage
# 245 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	releaseall
	end


RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_0:
# 149 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Greetings, I am versed in Hyper Training\n"
	.string "Pokemon. If you have any bottle caps, I\l"
	.string "can help you train your pokemon.$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_1:
# 150 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "What caps would you be willing to offer?$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_2:
# 154 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Plain Capsules$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_3:
# 158 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Regular Capsules$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_4:
# 162 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Gold Capsules$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_5:
# 164 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Never Mind$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_6:
# 170 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "For this capsule, I can give you\n"
	.string "moderate training in one stat.$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_7:
# 176 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "This Pokemon already exceeds my\n"
	.string "training capacities for this stat!\l"
	.string "Please come again with other training.$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_8:
# 184 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "It's done. Your Pokémon looks much\n"
	.string "stronger now.$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_9:
# 187 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "For this capsule, I can maximize one\n"
	.string "stat.$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_10:
# 204 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "For this capsule, I can maximize all your\n"
	.string "pokemon's stats.$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_11:
# 209 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "This Pokemon already exceeds my\n"
	.string "training capacities for these stats!\l"
	.string "Please come again with other training.$"

IVTrainer_ChooseStat_Text_0:
# 225 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Which stat should I train?$"

IVTrainer_ChooseStat_Text_1:
# 226 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "HP$"

IVTrainer_ChooseStat_Text_2:
# 226 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Atk$"

IVTrainer_ChooseStat_Text_3:
# 226 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Def$"

IVTrainer_ChooseStat_Text_4:
# 226 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Speed$"

IVTrainer_ChooseStat_Text_5:
# 226 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Sp.atk$"

IVTrainer_ChooseStat_Text_6:
# 226 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Sp.def$"

RustboroCity_DevonCorp_1F_IVTrainer_Farewell_Text_0:
# 233 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Alright, have a nice day!$"

IVTrainer_ChooseMon_Text_0:
# 239 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Alright, Please choose a Pokemon to\n"
	.string "train.$"

IVTrainer_ChooseMon_Text_1:
# 243 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Having trouble deciding? Take your\n"
	.string "time.$"
