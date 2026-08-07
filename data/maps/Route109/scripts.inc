# 1 "data/maps/Route109/scripts.pory"

# 2 "data/maps/Route109/scripts.pory"
	.include "data/maps/Route109/scripts.raw.inc"

Route109_EventScript_Edmond::
# 6 "data/maps/Route109/scripts.pory"
	lock
# 7 "data/maps/Route109/scripts.pory"
	faceplayer
# 9 "data/maps/Route109/scripts.pory"
	goto_if_set TRAINER_FLAGS_START + TRAINER_EDMOND, Route109_EventScript_Edmond_2
# 15 "data/maps/Route109/scripts.pory"
	trainerbattle_single TRAINER_EDMOND, Route109_Text_EdmondIntro, Route109_Text_EdmondDefeated
# 16 "data/maps/Route109/scripts.pory"
	specialvar VAR_RESULT, WasTrainerBattleWithTwoOpponents
# 17 "data/maps/Route109/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq Route109_EventScript_Edmond_5
Route109_EventScript_Edmond_4:
# 32 "data/maps/Route109/scripts.pory"
	msgbox Route109_Text_EdmondPostBattle
# 33 "data/maps/Route109/scripts.pory"
	release
	return

Route109_EventScript_Edmond_2:
# 10 "data/maps/Route109/scripts.pory"
	msgbox Route109_Text_EdmondPostBattle
# 11 "data/maps/Route109/scripts.pory"
	release
	return

Route109_EventScript_Edmond_5:
# 18 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Edmond_Text_0
# 19 "data/maps/Route109/scripts.pory"
	goto_if_set FLAG_RESOURCE_MODE, Route109_EventScript_Edmond_8
# 26 "data/maps/Route109/scripts.pory"
	giveItem ITEM_WATER_GEM
Route109_EventScript_Edmond_7:
# 28 "data/maps/Route109/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Route109_EventScript_Edmond_11
	goto Route109_EventScript_Edmond_4

Route109_EventScript_Edmond_8:
# 20 "data/maps/Route109/scripts.pory"
	compare VAR_MONOTYPE, 0
	goto_if_ne Route109_EventScript_Edmond_13
# 23 "data/maps/Route109/scripts.pory"
	giveItem ITEM_WATER_GEM, 3
	goto Route109_EventScript_Edmond_7

Route109_EventScript_Edmond_11:
# 29 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Edmond_Text_1
	goto Route109_EventScript_Edmond_4

Route109_EventScript_Edmond_13:
# 21 "data/maps/Route109/scripts.pory"
	giveItem ITEM_WATER_GEM, 6
	goto Route109_EventScript_Edmond_7


Route109_EventScript_Cassia::
# 37 "data/maps/Route109/scripts.pory"
	lock
# 38 "data/maps/Route109/scripts.pory"
	faceplayer
# 40 "data/maps/Route109/scripts.pory"
	goto_if_set TRAINER_FLAGS_START + TRAINER_CASSIA, Route109_EventScript_Cassia_2
# 46 "data/maps/Route109/scripts.pory"
	goto_if_set FLAG_RESTRICTED_MODE, Route109_EventScript_Cassia_6
Route109_EventScript_Cassia_4:
# 53 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_HUEY, Route109_EventScript_Cassia_10
# 54 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_EDMOND, Route109_EventScript_Cassia_10
# 55 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_RICKY_1, Route109_EventScript_Cassia_10
# 56 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_LOLA_1, Route109_EventScript_Cassia_10
# 57 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_CHANDLER, Route109_EventScript_Cassia_10
# 58 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_HAILEY, Route109_EventScript_Cassia_10
# 59 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_DWAYNE, Route109_EventScript_Cassia_10
# 60 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_JOHANNA, Route109_EventScript_Cassia_10
# 61 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_SIMON, Route109_EventScript_Cassia_10
# 67 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_4, MSGBOX_YESNO
# 68 "data/maps/Route109/scripts.pory"
	compare VAR_RESULT, NO
	goto_if_eq Route109_EventScript_Cassia_29
# 74 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_6
# 75 "data/maps/Route109/scripts.pory"
	trainerbattle_no_intro TRAINER_CASSIA, Route109_Text_CassiaDefeated
# 76 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_7
# 77 "data/maps/Route109/scripts.pory"
	goto_if_set FLAG_RESOURCE_MODE, Route109_EventScript_Cassia_32
# 84 "data/maps/Route109/scripts.pory"
	giveItem ITEM_POWER_HERB
Route109_EventScript_Cassia_31:
# 86 "data/maps/Route109/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Route109_EventScript_Cassia_36
# 92 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_9
# 93 "data/maps/Route109/scripts.pory"
	release
	return

Route109_EventScript_Cassia_2:
# 41 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_0
# 42 "data/maps/Route109/scripts.pory"
	release
	return

Route109_EventScript_Cassia_5:
# 47 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_1
# 48 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_2
# 49 "data/maps/Route109/scripts.pory"
	release
	return

Route109_EventScript_Cassia_6:
# 46 "data/maps/Route109/scripts.pory"
	goto_if_set FLAG_BADGE03_GET, Route109_EventScript_Cassia_5
	goto Route109_EventScript_Cassia_4

Route109_EventScript_Cassia_10:
# 62 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_3
# 63 "data/maps/Route109/scripts.pory"
	release
	return

Route109_EventScript_Cassia_29:
# 69 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_5
# 70 "data/maps/Route109/scripts.pory"
	release
	return

Route109_EventScript_Cassia_32:
# 78 "data/maps/Route109/scripts.pory"
	compare VAR_MONOTYPE, 0
	goto_if_ne Route109_EventScript_Cassia_38
# 81 "data/maps/Route109/scripts.pory"
	giveItem ITEM_POWER_HERB, 12
	goto Route109_EventScript_Cassia_31

Route109_EventScript_Cassia_36:
# 87 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_8
# 88 "data/maps/Route109/scripts.pory"
	release
	return

Route109_EventScript_Cassia_38:
# 79 "data/maps/Route109/scripts.pory"
	giveItem ITEM_POWER_HERB, 18
	goto Route109_EventScript_Cassia_31


Route109_EventScript_Edmond_Text_0:
# 18 "data/maps/Route109/scripts.pory"
	.string "You steadied us both! Take these WATER\n"
	.string "GEMS for winning the harder battle.$"

Route109_EventScript_Edmond_Text_1:
# 29 "data/maps/Route109/scripts.pory"
	.string "There was no room in either your BAG or\n"
	.string "your PC for the WATER GEMS.$"

Route109_EventScript_Cassia_Text_0:
# 41 "data/maps/Route109/scripts.pory"
	.string "Keep cultivating that strength. Even\n"
	.string "the hardiest growth needs patience.$"

Route109_EventScript_Cassia_Text_1:
# 47 "data/maps/Route109/scripts.pory"
	.string "This beach has some up-and-coming\n"
	.string "trainers. But I see you have three\l"
	.string "BADGES now!$"

Route109_EventScript_Cassia_Text_2:
# 48 "data/maps/Route109/scripts.pory"
	.string "I hope you'll remember the joys and\n"
	.string "experiences you had here throughout\l"
	.string "the rest of your journey.$"

Route109_EventScript_Cassia_Text_3:
# 62 "data/maps/Route109/scripts.pory"
	.string "I study Trainers who cross this beach.\n"
	.string "Defeat every Trainer on the ROUTE 109\l"
	.string "beach and inside the SEASHORE HOUSE,\l"
	.string "then return.$"

Route109_EventScript_Cassia_Text_4:
# 67 "data/maps/Route109/scripts.pory"
	.string "You've weathered every Trainer on this\n"
	.string "beach, even those in the SEASHORE\l"
	.string "HOUSE. Your strength has taken root.\l"
	.string "Shall we see how well it stands against\l"
	.string "mine?$"

Route109_EventScript_Cassia_Text_5:
# 69 "data/maps/Route109/scripts.pory"
	.string "No bloom should be hurried. Return when\n"
	.string "you are ready.$"

Route109_EventScript_Cassia_Text_6:
# 74 "data/maps/Route109/scripts.pory"
	.string "Excellent. Let our battle bloom!$"

Route109_EventScript_Cassia_Text_7:
# 76 "data/maps/Route109/scripts.pory"
	.string "A promise should always bear fruit. This\n"
	.string "rare herb is yours.$"

Route109_EventScript_Cassia_Text_8:
# 87 "data/maps/Route109/scripts.pory"
	.string "There was no room in either your BAG or\n"
	.string "your PC for the POWER HERB.$"

Route109_EventScript_Cassia_Text_9:
# 92 "data/maps/Route109/scripts.pory"
	.string "A POWER HERB lets a POKéMON use a move\n"
	.string "that charges up without having to wait.\l"
	.string "It is consumed, so choose its moment\l"
	.string "with care.$"

Route109_Text_CassiaDefeated::
# 96 "data/maps/Route109/scripts.pory"
	.string "What splendid growth!$"
