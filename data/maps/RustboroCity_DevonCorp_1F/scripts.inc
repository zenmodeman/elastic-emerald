# 1 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 2 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 3 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
.set LOCALID_STAIR_GUARD, 2
# 4 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 5 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_MapScripts::
# 6 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_1F_OnTransition
# 7 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.byte 0
# 8 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 9 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_OnTransition:
# 10 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	call_if_unset FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_BlockStairs
# 11 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 12 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 13 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_BlockStairs::
# 14 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	setobjectxyperm LOCALID_STAIR_GUARD, 14, 2
# 15 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	setobjectmovementtype LOCALID_STAIR_GUARD, MOVEMENT_TYPE_FACE_DOWN
# 16 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	return
# 17 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 18 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_Employee::
# 19 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	lock
# 20 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	faceplayer
# 21 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered
# 22 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright
# 23 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct, MSGBOX_DEFAULT
# 24 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	release
# 25 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 26 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 27 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright::
# 28 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright, MSGBOX_DEFAULT
# 29 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	release
# 30 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 31 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 32 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered::
# 33 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered, MSGBOX_DEFAULT
# 34 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	release
# 35 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 36 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 37 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_StairGuard::
# 38 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	lock
# 39 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	faceplayer
# 40 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome
# 41 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
# 42 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
# 43 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter, MSGBOX_DEFAULT
# 44 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	release
# 45 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 46 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 47 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome::
# 48 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere, MSGBOX_DEFAULT
# 49 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	release
# 50 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 51 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 52 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_GotRobbed::
# 53 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed, MSGBOX_DEFAULT
# 54 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	release
# 55 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 56 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 57 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_Greeter::
# 58 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	lock
# 59 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	faceplayer
# 60 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp
# 61 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
# 62 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
# 63 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
# 64 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	release
# 65 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 66 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 67 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp::
# 68 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
# 69 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	release
# 70 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 71 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 72 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed::
# 73 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_StaffGotRobbed, MSGBOX_DEFAULT
# 74 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	release
# 75 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 76 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 77 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_RocksMetalDisplay::
# 78 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay, MSGBOX_SIGN
# 79 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 80 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 81 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_EventScript_ProductsDisplay::
# 82 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_Text_ProductDisplay, MSGBOX_SIGN
# 83 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	end
# 84 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 85 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp:
# 86 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Hello and welcome to the DEVON\n"
# 87 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "CORPORATION.\p"
# 88 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "We're proud producers of items and\n"
# 89 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "medicine that enhance your life.$"
# 90 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 91 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_Text_StaffGotRobbed:
# 92 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "One of our research staff stupidly\n"
# 93 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "got robbed of an important parcel.$"
# 94 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 95 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct:
# 96 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Hey, those RUNNING SHOES!\n"
# 97 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "They're one of our products!\p"
# 98 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "It makes me happy when I see someone\n"
# 99 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "using something we made.$"
# 100 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 101 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright:
# 102 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "That stolen parcel…\p"
# 103 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Well, sure it's important, but it's not\n"
# 104 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "anything that anyone can use.\p"
# 105 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "In my estimation, that robber must not\n"
# 106 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "have been very bright.$"
# 107 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 108 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered:
# 109 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "It sounds like they've recovered\n"
# 110 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "the ripped-off DEVON GOODS.$"
# 111 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 112 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter:
# 113 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "I'm sorry, only authorized people\n"
# 114 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "are allowed to enter here.$"
# 115 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 116 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed:
# 117 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "It's beyond stupid.\n"
# 118 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "How could we get robbed?$"
# 119 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 120 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere:
# 121 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Hi, there!\n"
# 122 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "You're always welcome here!$"
# 123 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 124 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay:
# 125 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Samples of rocks and metal are\n"
# 126 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "displayed in the glass case.\p"
# 127 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "There's a panel with some writing\n"
# 128 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "on it…\p"
# 129 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "“DEVON CORPORATION got its start as\n"
# 130 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "a producer of stones from quarries.\p"
# 131 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "“The company also produced iron from\n"
# 132 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "filings in the sand.\p"
# 133 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "“From that humble start as a producer\n"
# 134 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "of raw materials, DEVON developed.\p"
# 135 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "“DEVON is now a manufacturer of a wide\n"
# 136 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "range of industrial products.”$"
# 137 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"

# 138 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
RustboroCity_DevonCorp_1F_Text_ProductDisplay:
# 139 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Prototypes and test products fill\n"
# 140 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "the glass display case.\p"
# 141 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "There's a panel with a description…\p"
# 142 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "“In addition to industrial products,\n"
# 143 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "DEVON now markets sundries and\l"
# 144 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "pharmaceuticals for better lifestyles.\p"
# 145 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "“Recently, DEVON has begun marketing\n"
# 146 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "tools for POKéMON TRAINERS, including\l"
# 147 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "POKé BALLS and POKéNAV systems.”$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer::
# 153 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	lock
# 154 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_0
# 155 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_1
# 157 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	checkitem ITEM_PLAIN_BOTTLE_CAP
# 158 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_1F_EventScript_IVTrainer_2
RustboroCity_DevonCorp_1F_EventScript_IVTrainer_1:
# 161 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	checkitem ITEM_BOTTLE_CAP
# 162 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_1F_EventScript_IVTrainer_5
RustboroCity_DevonCorp_1F_EventScript_IVTrainer_4:
# 165 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	checkitem ITEM_GOLD_BOTTLE_CAP
# 166 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_DevonCorp_1F_EventScript_IVTrainer_8
RustboroCity_DevonCorp_1F_EventScript_IVTrainer_7:
# 169 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_5, ITEM_NONE
# 170 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	dynmultistack 0, 0, TRUE, 6, FALSE, ITEM_NONE, DYN_MULTICHOICE_CB_NONE
# 171 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_RESULT, ITEM_NONE
	goto_if_eq RustboroCity_DevonCorp_1F_EventScript_IVTrainer_11
RustboroCity_DevonCorp_1F_EventScript_IVTrainer_10:
# 174 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_RESULT, ITEM_PLAIN_BOTTLE_CAP
	goto_if_eq RustboroCity_DevonCorp_1F_EventScript_IVTrainer_14
RustboroCity_DevonCorp_1F_EventScript_IVTrainer_13:
# 191 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	releaseall
	end

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_2:
# 159 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_2, ITEM_PLAIN_BOTTLE_CAP
	goto RustboroCity_DevonCorp_1F_EventScript_IVTrainer_1

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_5:
# 163 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_3, ITEM_BOTTLE_CAP
	goto RustboroCity_DevonCorp_1F_EventScript_IVTrainer_4

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_8:
# 167 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	dynmultipush RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_4, ITEM_GOLD_BOTTLE_CAP
	goto RustboroCity_DevonCorp_1F_EventScript_IVTrainer_7

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_11:
# 172 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	goto RustboroCity_DevonCorp_1F_IVTrainer_Farewell
	goto RustboroCity_DevonCorp_1F_EventScript_IVTrainer_10

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_14:
# 175 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_6
# 176 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	call IVTrainer_ChooseStat
# 177 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	call IVTrainer_ChooseMon
# 178 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	specialvar VAR_RESULT, TrainPlainIV
# 179 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq RustboroCity_DevonCorp_1F_EventScript_IVTrainer_17
# 185 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	playfanfare MUS_LEVEL_UP
# 186 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	waitfanfare
# 187 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	removeitem ITEM_PLAIN_BOTTLE_CAP, 1
# 188 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_8
# 189 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	waitmessage
	goto RustboroCity_DevonCorp_1F_EventScript_IVTrainer_13

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_17:
# 180 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_7
# 181 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	waitmessage
# 182 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	releaseall
	end


IVTrainer_ChooseStat::
# 196 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox IVTrainer_ChooseStat_Text_0
# 197 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	dynmultichoice 20, 100, TRUE, 5, 0, DYN_MULTICHOICE_CB_NONE, IVTrainer_ChooseStat_Text_1, IVTrainer_ChooseStat_Text_2, IVTrainer_ChooseStat_Text_3, IVTrainer_ChooseStat_Text_4, IVTrainer_ChooseStat_Text_5, IVTrainer_ChooseStat_Text_6, RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_5
# 198 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_RESULT, 6
	goto_if_eq IVTrainer_ChooseStat_2
IVTrainer_ChooseStat_1:
# 201 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	copyvar VAR_TEMP_1, VAR_RESULT
	return

IVTrainer_ChooseStat_2:
# 199 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	goto RustboroCity_DevonCorp_1F_IVTrainer_Farewell
	goto IVTrainer_ChooseStat_1


RustboroCity_DevonCorp_1F_IVTrainer_Farewell::
# 204 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox RustboroCity_DevonCorp_1F_IVTrainer_Farewell_Text_0
# 205 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	releaseall
	end


IVTrainer_ChooseMon::
# 210 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox IVTrainer_ChooseMon_Text_0
# 211 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	special ChoosePartyMon
# 212 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	waitstate
# 213 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	compare VAR_0x8004, PARTY_NOTHING_CHOSEN
	goto_if_eq IVTrainer_ChooseMon_1
	return

IVTrainer_ChooseMon_1:
# 214 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	msgbox IVTrainer_ChooseMon_Text_1
# 215 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	waitmessage
# 216 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	releaseall
	end


RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_0:
# 154 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Greetings, I am versed in Hyper Training\n"
	.string "Pokemon. If you have any bottle\l"
	.string "capsules, I can help you train your\l"
	.string "pokemon.$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_1:
# 155 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "What capsules would you be willing to\n"
	.string "offer?$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_2:
# 159 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Plain Capsules$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_3:
# 163 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Regular Capsules$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_4:
# 167 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Gold Capsules$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_5:
# 169 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Never Mind$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_6:
# 175 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "For this capsule, I can give you\n"
	.string "moderate training in one stat.$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_7:
# 180 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "This Pokemon already exceeds my\n"
	.string "training capacities for this stat!\l"
	.string "Please come again with other training.$"

RustboroCity_DevonCorp_1F_EventScript_IVTrainer_Text_8:
# 188 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "It's done. Your Pokémon looks much\n"
	.string "stronger now.$"

IVTrainer_ChooseStat_Text_0:
# 196 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Which stat should I train?$"

IVTrainer_ChooseStat_Text_1:
# 197 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "HP$"

IVTrainer_ChooseStat_Text_2:
# 197 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Atk$"

IVTrainer_ChooseStat_Text_3:
# 197 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Def$"

IVTrainer_ChooseStat_Text_4:
# 197 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Speed$"

IVTrainer_ChooseStat_Text_5:
# 197 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Sp.atk$"

IVTrainer_ChooseStat_Text_6:
# 197 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Sp.def$"

RustboroCity_DevonCorp_1F_IVTrainer_Farewell_Text_0:
# 204 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Alright, have a nice day!$"

IVTrainer_ChooseMon_Text_0:
# 210 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Alright, Please choose a Pokemon to\n"
	.string "train.$"

IVTrainer_ChooseMon_Text_1:
# 214 "data/maps/RustboroCity_DevonCorp_1F/scripts.pory"
	.string "Having trouble deciding? Take your\n"
	.string "time.$"
