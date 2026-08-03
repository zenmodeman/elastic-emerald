# 1 "data/maps/Route109/scripts.pory"

# 2 "data/maps/Route109/scripts.pory"
	.include "data/maps/Route109/scripts.raw.inc"

Route109_EventScript_Cassia::
# 6 "data/maps/Route109/scripts.pory"
	lock
# 7 "data/maps/Route109/scripts.pory"
	faceplayer
# 9 "data/maps/Route109/scripts.pory"
	goto_if_set TRAINER_FLAGS_START + TRAINER_CASSIA, Route109_EventScript_Cassia_2
# 15 "data/maps/Route109/scripts.pory"
	goto_if_set FLAG_RESTRICTED_MODE, Route109_EventScript_Cassia_6
Route109_EventScript_Cassia_4:
# 22 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_HUEY, Route109_EventScript_Cassia_10
# 23 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_EDMOND, Route109_EventScript_Cassia_10
# 24 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_RICKY_1, Route109_EventScript_Cassia_10
# 25 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_LOLA_1, Route109_EventScript_Cassia_10
# 26 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_CHANDLER, Route109_EventScript_Cassia_10
# 27 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_HAILEY, Route109_EventScript_Cassia_10
# 28 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_DWAYNE, Route109_EventScript_Cassia_10
# 29 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_JOHANNA, Route109_EventScript_Cassia_10
# 30 "data/maps/Route109/scripts.pory"
	goto_if_unset TRAINER_FLAGS_START + TRAINER_SIMON, Route109_EventScript_Cassia_10
# 36 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_4, MSGBOX_YESNO
# 37 "data/maps/Route109/scripts.pory"
	compare VAR_RESULT, NO
	goto_if_eq Route109_EventScript_Cassia_29
# 43 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_6
# 44 "data/maps/Route109/scripts.pory"
	trainerbattle_no_intro TRAINER_CASSIA, Route109_Text_CassiaDefeated
# 45 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_7
# 46 "data/maps/Route109/scripts.pory"
	goto_if_set FLAG_RESOURCE_MODE, Route109_EventScript_Cassia_32
# 53 "data/maps/Route109/scripts.pory"
	giveItem ITEM_POWER_HERB
Route109_EventScript_Cassia_31:
# 55 "data/maps/Route109/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq Route109_EventScript_Cassia_36
# 61 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_9
# 62 "data/maps/Route109/scripts.pory"
	release
	return

Route109_EventScript_Cassia_2:
# 10 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_0
# 11 "data/maps/Route109/scripts.pory"
	release
	return

Route109_EventScript_Cassia_5:
# 16 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_1
# 17 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_2
# 18 "data/maps/Route109/scripts.pory"
	release
	return

Route109_EventScript_Cassia_6:
# 15 "data/maps/Route109/scripts.pory"
	goto_if_set FLAG_BADGE03_GET, Route109_EventScript_Cassia_5
	goto Route109_EventScript_Cassia_4

Route109_EventScript_Cassia_10:
# 31 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_3
# 32 "data/maps/Route109/scripts.pory"
	release
	return

Route109_EventScript_Cassia_29:
# 38 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_5
# 39 "data/maps/Route109/scripts.pory"
	release
	return

Route109_EventScript_Cassia_32:
# 47 "data/maps/Route109/scripts.pory"
	compare VAR_MONOTYPE, 0
	goto_if_ne Route109_EventScript_Cassia_38
# 50 "data/maps/Route109/scripts.pory"
	giveItem ITEM_POWER_HERB, 12
	goto Route109_EventScript_Cassia_31

Route109_EventScript_Cassia_36:
# 56 "data/maps/Route109/scripts.pory"
	msgbox Route109_EventScript_Cassia_Text_8
# 57 "data/maps/Route109/scripts.pory"
	release
	return

Route109_EventScript_Cassia_38:
# 48 "data/maps/Route109/scripts.pory"
	giveItem ITEM_POWER_HERB, 18
	goto Route109_EventScript_Cassia_31


Route109_EventScript_Cassia_Text_0:
# 10 "data/maps/Route109/scripts.pory"
	.string "Keep cultivating that strength. Even\n"
	.string "the hardiest growth needs patience.$"

Route109_EventScript_Cassia_Text_1:
# 16 "data/maps/Route109/scripts.pory"
	.string "This beach has some up-and-coming\n"
	.string "trainers. But I see you have three\l"
	.string "BADGES now!$"

Route109_EventScript_Cassia_Text_2:
# 17 "data/maps/Route109/scripts.pory"
	.string "I hope you'll remember the joys and\n"
	.string "experiences you had here throughout\l"
	.string "the rest of your journey.$"

Route109_EventScript_Cassia_Text_3:
# 31 "data/maps/Route109/scripts.pory"
	.string "I study Trainers who cross this beach.\n"
	.string "Defeat every Trainer on the ROUTE 109\l"
	.string "beach and inside the SEASHORE HOUSE,\l"
	.string "then return.$"

Route109_EventScript_Cassia_Text_4:
# 36 "data/maps/Route109/scripts.pory"
	.string "You've weathered every Trainer on this\n"
	.string "beach, even those in the SEASHORE\l"
	.string "HOUSE. Your strength has taken root.\l"
	.string "Shall we see how well it stands against\l"
	.string "mine?$"

Route109_EventScript_Cassia_Text_5:
# 38 "data/maps/Route109/scripts.pory"
	.string "No bloom should be hurried. Return when\n"
	.string "you are ready.$"

Route109_EventScript_Cassia_Text_6:
# 43 "data/maps/Route109/scripts.pory"
	.string "Excellent. Let our battle bloom!$"

Route109_EventScript_Cassia_Text_7:
# 45 "data/maps/Route109/scripts.pory"
	.string "A promise should always bear fruit. This\n"
	.string "rare herb is yours.$"

Route109_EventScript_Cassia_Text_8:
# 56 "data/maps/Route109/scripts.pory"
	.string "There was no room in either your BAG or\n"
	.string "your PC for the POWER HERB.$"

Route109_EventScript_Cassia_Text_9:
# 61 "data/maps/Route109/scripts.pory"
	.string "A POWER HERB lets a POKéMON use a move\n"
	.string "that charges up without having to wait.\l"
	.string "It is consumed, so choose its moment\l"
	.string "with care.$"

Route109_Text_CassiaDefeated::
# 65 "data/maps/Route109/scripts.pory"
	.string "What splendid growth!$"
