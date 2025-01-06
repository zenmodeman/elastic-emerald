# 1 "data/maps/RustboroCity_CuttersHouse/scripts.pory"

# 2 "data/maps/RustboroCity_CuttersHouse/scripts.pory"

# 3 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
RustboroCity_CuttersHouse_MapScripts::
# 4 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.byte 0
# 5 "data/maps/RustboroCity_CuttersHouse/scripts.pory"

# 6 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
RustboroCity_CuttersHouse_EventScript_Cutter::
# 7 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	lock
# 8 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	faceplayer
# 9 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	goto_if_set FLAG_RECEIVED_HM_CUT, RustboroCity_CuttersHouse_EventScript_ExplainCut
# 10 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	msgbox RustboroCity_CuttersHouse_Text_YouCanPutThisHMToGoodUse, MSGBOX_DEFAULT
# 11 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	giveitem ITEM_HM_CUT
# 12 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	setflag FLAG_RECEIVED_HM_CUT
# 13 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	msgbox RustboroCity_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
# 14 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
    call ExtraCutInformation
# 15 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	release
# 16 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	end
# 17 "data/maps/RustboroCity_CuttersHouse/scripts.pory"

# 18 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
RustboroCity_CuttersHouse_EventScript_ExplainCut::
# 19 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	msgbox RustboroCity_CuttersHouse_Text_ExplainCut, MSGBOX_DEFAULT
# 20 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	release
# 21 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	end
# 22 "data/maps/RustboroCity_CuttersHouse/scripts.pory"

# 23 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
RustboroCity_CuttersHouse_EventScript_Lass::
# 24 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	msgbox RustboroCity_CuttersHouse_Text_DadHelpedClearLandOfTrees, MSGBOX_NPC
# 25 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	end
# 26 "data/maps/RustboroCity_CuttersHouse/scripts.pory"

# 27 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
RustboroCity_CuttersHouse_Text_YouCanPutThisHMToGoodUse:
# 28 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "That determined expression…\n"
# 29 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "That limber way you move…\l"
# 30 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "And your well-trained POKéMON…\p"
# 31 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "You're obviously a skilled TRAINER!\p"
# 32 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "No, wait, don't say a word.\n"
# 33 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "I can tell just by looking at you.\p"
# 34 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "I'm sure that you can put this\n"
# 35 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "HIDDEN MACHINE to good use.\p"
# 36 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "No need to be modest or shy.\n"
# 37 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "Go on, take it!$"
# 38 "data/maps/RustboroCity_CuttersHouse/scripts.pory"

# 39 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
RustboroCity_CuttersHouse_Text_ExplainCut:
# 40 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "That HIDDEN MACHINE, or HM for\n"
# 41 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "short, is CUT.\p"
# 42 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "An HM move is one that can be used\n"
# 43 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "by POKéMON outside of battle.\p"
# 44 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "Any POKéMON that's learned CUT can\n"
# 45 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "chop down thin trees if the TRAINER\l"
# 46 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "has earned the STONE BADGE.$"
# 47 "data/maps/RustboroCity_CuttersHouse/scripts.pory"

# 48 "data/maps/RustboroCity_CuttersHouse/scripts.pory"

# 49 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
RustboroCity_CuttersHouse_Text_DadHelpedClearLandOfTrees:
# 50 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "When they were expanding the city of\n"
# 51 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "RUSTBORO, my dad helped out.\p"
# 52 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "He made his POKéMON use CUT to clear\n"
# 53 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "the land of trees.$"

ExtraCutInformation::
# 58 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	msgbox ExtraCutInformation_Text_0
# 59 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	msgbox ExtraCutInformation_Text_1
# 60 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 61 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	msgbox ExtraCutInformation_Text_2
# 62 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	msgbox ExtraCutInformation_Text_3
	return


ExtraCutInformation_Text_0:
# 58 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "Furthermore, in battle, this move can\n"
	.string "hit Grass types supereffectively,\l"
	.string "despite being a Normal move!$"

ExtraCutInformation_Text_1:
# 59 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "If you need help cutting trees, I can\n"
	.string "connect you up with one of my Scythers.$"

ExtraCutInformation_Text_2:
# 61 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "{PLAYER} received Scyther's Pager\n"
	.string "Information!$"

ExtraCutInformation_Text_3:
# 62 "data/maps/RustboroCity_CuttersHouse/scripts.pory"
	.string "Good luck on your journey, and always\n"
	.string "take control of the trees!$"
