# 1 "data/maps/Route109/scripts.pory"

# 2 "data/maps/Route109/scripts.pory"
	.include "data/maps/Route109/scripts.raw.inc"

Route109_EventScript_Edmond::
# 6 "data/maps/Route109/scripts.pory"
	trainerbattle_single TRAINER_EDMOND, Route109_Text_EdmondIntro, Route109_Text_EdmondDefeated, Route109_EventScript_EdmondDefeated
# 7 "data/maps/Route109/scripts.pory"
	msgbox Route109_Text_EdmondPostBattle, MSGBOX_AUTOCLOSE
	end


Route109_EventScript_EdmondDefeated::
# 12 "data/maps/Route109/scripts.pory"
	specialvar VAR_RESULT, WasTrainerBattleWithTwoOpponents
# 13 "data/maps/Route109/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq Route109_EventScript_EdmondDefeated_2
Route109_EventScript_EdmondDefeated_1:
# 28 "data/maps/Route109/scripts.pory"
	msgbox Route109_Text_EdmondPostBattle
# 29 "data/maps/Route109/scripts.pory"
	releaseall
	end

Route109_EventScript_EdmondDefeated_2:
# 14 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_EdmondDefeated_Text_0
# 15 "data/maps/Route109/scripts.pory"
	goto_if_set FLAG_RESOURCE_MODE, Route109_EventScript_EdmondDefeated_5
# 22 "data/maps/Route109/scripts.pory"
	giveItem ITEM_WATER_GEM
Route109_EventScript_EdmondDefeated_4:
# 24 "data/maps/Route109/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Route109_EventScript_EdmondDefeated_8
	goto Route109_EventScript_EdmondDefeated_1

Route109_EventScript_EdmondDefeated_5:
# 16 "data/maps/Route109/scripts.pory"
	compare VAR_MONOTYPE, 0
	goto_if_ne Route109_EventScript_EdmondDefeated_10
# 19 "data/maps/Route109/scripts.pory"
	giveItem ITEM_WATER_GEM, 3
	goto Route109_EventScript_EdmondDefeated_4

Route109_EventScript_EdmondDefeated_8:
# 25 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_EdmondDefeated_Text_1
	goto Route109_EventScript_EdmondDefeated_1

Route109_EventScript_EdmondDefeated_10:
# 17 "data/maps/Route109/scripts.pory"
	giveItem ITEM_WATER_GEM, 6
	goto Route109_EventScript_EdmondDefeated_4


Route109_EventScript_Cassia::
# 34 "data/maps/Route109/scripts.pory"
	lock
# 35 "data/maps/Route109/scripts.pory"
	faceplayer
# 37 "data/maps/Route109/scripts.pory"
	goto_if_set TRAINER_FLAGS_START + TRAINER_CASSIA, Route109_EventScript_Cassia_2
# 43 "data/maps/Route109/scripts.pory"
	goto_if_set FLAG_RESTRICTED_MODE, Route109_EventScript_Cassia_6
Route109_EventScript_Cassia_4:
# 50 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_HUEY, Route109_EventScript_Cassia_10
# 51 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_EDMOND, Route109_EventScript_Cassia_10
# 52 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_RICKY_1, Route109_EventScript_Cassia_10
# 53 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_LOLA_1, Route109_EventScript_Cassia_10
# 54 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_CHANDLER, Route109_EventScript_Cassia_10
# 55 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_HAILEY, Route109_EventScript_Cassia_10
# 56 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_DWAYNE, Route109_EventScript_Cassia_10
# 57 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_JOHANNA, Route109_EventScript_Cassia_10
# 58 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_SIMON, Route109_EventScript_Cassia_10
# 64 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_4, MSGBOX_YESNO
# 65 "data/maps/Route109/scripts.pory"
	compare VAR_RESULT, NO
	goto_if_eq Route109_EventScript_Cassia_29
# 71 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_6
# 72 "data/maps/Route109/scripts.pory"
	trainerbattle_no_intro TRAINER_CASSIA, Route109_Text_CassiaDefeated
# 73 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_7
# 74 "data/maps/Route109/scripts.pory"
	goto_if_set FLAG_RESOURCE_MODE, Route109_EventScript_Cassia_32
# 81 "data/maps/Route109/scripts.pory"
	giveItem ITEM_POWER_HERB
Route109_EventScript_Cassia_31:
# 83 "data/maps/Route109/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Route109_EventScript_Cassia_36
# 89 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_9
# 90 "data/maps/Route109/scripts.pory"
	release
	return

Route109_EventScript_Cassia_2:
# 38 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_0
# 39 "data/maps/Route109/scripts.pory"
	release
	return

Route109_EventScript_Cassia_5:
# 44 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_1
# 45 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_2
# 46 "data/maps/Route109/scripts.pory"
	release
	return

Route109_EventScript_Cassia_6:
# 43 "data/maps/Route109/scripts.pory"
	goto_if_set FLAG_BADGE03_GET, Route109_EventScript_Cassia_5
	goto Route109_EventScript_Cassia_4

Route109_EventScript_Cassia_10:
# 59 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_3
# 60 "data/maps/Route109/scripts.pory"
	release
	return

Route109_EventScript_Cassia_29:
# 66 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_5
# 67 "data/maps/Route109/scripts.pory"
	release
	return

Route109_EventScript_Cassia_32:
# 75 "data/maps/Route109/scripts.pory"
	compare VAR_MONOTYPE, 0
	goto_if_ne Route109_EventScript_Cassia_38
# 78 "data/maps/Route109/scripts.pory"
	giveItem ITEM_POWER_HERB, 12
	goto Route109_EventScript_Cassia_31

Route109_EventScript_Cassia_36:
# 84 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_8
# 85 "data/maps/Route109/scripts.pory"
	release
	return

Route109_EventScript_Cassia_38:
# 76 "data/maps/Route109/scripts.pory"
	giveItem ITEM_POWER_HERB, 18
	goto Route109_EventScript_Cassia_31


Route109_EventScript_EdmondDefeated_Text_0:
# 14 "data/maps/Route109/scripts.pory"
	.string "You steadied us both! Take these WATER\n"
	.string "GEMS for winning the harder battle.$"

Route109_EventScript_EdmondDefeated_Text_1:
# 25 "data/maps/Route109/scripts.pory"
	.string "There was no room in either your BAG or\n"
	.string "your PC for the WATER GEMS.$"

Route109_EventScript_Cassia_Text_0:
# 38 "data/maps/Route109/scripts.pory"
	.string "Keep cultivating that strength. Even\n"
	.string "the hardiest growth needs patience.$"

Route109_EventScript_Cassia_Text_1:
# 44 "data/maps/Route109/scripts.pory"
	.string "This beach has some up-and-coming\n"
	.string "trainers. But I see you have three\l"
	.string "BADGES now!$"

Route109_EventScript_Cassia_Text_2:
# 45 "data/maps/Route109/scripts.pory"
	.string "I hope you'll remember the joys and\n"
	.string "experiences you had here throughout\l"
	.string "the rest of your journey.$"

Route109_EventScript_Cassia_Text_3:
# 59 "data/maps/Route109/scripts.pory"
	.string "I study Trainers who cross this beach.\n"
	.string "Defeat every Trainer on the ROUTE 109\l"
	.string "beach and inside the SEASHORE HOUSE,\l"
	.string "then return.$"

Route109_EventScript_Cassia_Text_4:
# 64 "data/maps/Route109/scripts.pory"
	.string "You've weathered every Trainer on this\n"
	.string "beach, even those in the SEASHORE\l"
	.string "HOUSE. Your strength has taken root.\l"
	.string "Shall we see how well it stands against\l"
	.string "mine?$"

Route109_EventScript_Cassia_Text_5:
# 66 "data/maps/Route109/scripts.pory"
	.string "No bloom should be hurried. Return when\n"
	.string "you are ready.$"

Route109_EventScript_Cassia_Text_6:
# 71 "data/maps/Route109/scripts.pory"
	.string "Excellent. Let our battle bloom!$"

Route109_EventScript_Cassia_Text_7:
# 73 "data/maps/Route109/scripts.pory"
	.string "A promise should always bear fruit. This\n"
	.string "rare herb is yours.$"

Route109_EventScript_Cassia_Text_8:
# 84 "data/maps/Route109/scripts.pory"
	.string "There was no room in either your BAG or\n"
	.string "your PC for the POWER HERB.$"

Route109_EventScript_Cassia_Text_9:
# 89 "data/maps/Route109/scripts.pory"
	.string "A POWER HERB lets a POKéMON use a move\n"
	.string "that charges up without having to wait.\l"
	.string "It is consumed, so choose its moment\l"
	.string "with care.$"

Route109_Text_CassiaDefeated::
# 93 "data/maps/Route109/scripts.pory"
	.string "What splendid growth!$"
