# 1 "data/maps/OldaleTown_Mart/scripts.pory"

# 2 "data/maps/OldaleTown_Mart/scripts.pory"

# 3 "data/maps/OldaleTown_Mart/scripts.pory"
OldaleTown_Mart_MapScripts::
# 4 "data/maps/OldaleTown_Mart/scripts.pory"
	.byte 0
# 5 "data/maps/OldaleTown_Mart/scripts.pory"

# 6 "data/maps/OldaleTown_Mart/scripts.pory"

# 7 "data/maps/OldaleTown_Mart/scripts.pory"
OldaleTown_Mart_EventScript_Woman::
# 8 "data/maps/OldaleTown_Mart/scripts.pory"
	lock
# 9 "data/maps/OldaleTown_Mart/scripts.pory"
	faceplayer
# 10 "data/maps/OldaleTown_Mart/scripts.pory"
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_Mart_EventScript_PokeBallsInStock
# 11 "data/maps/OldaleTown_Mart/scripts.pory"
	msgbox OldaleTown_Mart_Text_PokeBallsAreSoldOut, MSGBOX_DEFAULT
# 12 "data/maps/OldaleTown_Mart/scripts.pory"
	release
# 13 "data/maps/OldaleTown_Mart/scripts.pory"
	end
# 14 "data/maps/OldaleTown_Mart/scripts.pory"

# 15 "data/maps/OldaleTown_Mart/scripts.pory"
OldaleTown_Mart_EventScript_PokeBallsInStock::
# 16 "data/maps/OldaleTown_Mart/scripts.pory"
	msgbox OldaleTown_Mart_Text_ImGoingToBuyPokeBalls, MSGBOX_DEFAULT
# 17 "data/maps/OldaleTown_Mart/scripts.pory"
	release
# 18 "data/maps/OldaleTown_Mart/scripts.pory"
	end
# 19 "data/maps/OldaleTown_Mart/scripts.pory"

# 20 "data/maps/OldaleTown_Mart/scripts.pory"
OldaleTown_Mart_EventScript_Boy::
# 21 "data/maps/OldaleTown_Mart/scripts.pory"
	msgbox OldaleTown_Mart_Text_RestoreHPWithPotion, MSGBOX_NPC
# 22 "data/maps/OldaleTown_Mart/scripts.pory"
	end
# 23 "data/maps/OldaleTown_Mart/scripts.pory"

# 24 "data/maps/OldaleTown_Mart/scripts.pory"
OldaleTown_Mart_Text_PokeBallsAreSoldOut:
# 25 "data/maps/OldaleTown_Mart/scripts.pory"
	.string "The clerk says they're all sold out.\n"
# 26 "data/maps/OldaleTown_Mart/scripts.pory"
	.string "I can't buy any POKé BALLS.$"
# 27 "data/maps/OldaleTown_Mart/scripts.pory"

# 28 "data/maps/OldaleTown_Mart/scripts.pory"
OldaleTown_Mart_Text_ImGoingToBuyPokeBalls:
# 29 "data/maps/OldaleTown_Mart/scripts.pory"
	.string "I'm going to buy a bunch of POKé BALLS\n"
# 30 "data/maps/OldaleTown_Mart/scripts.pory"
	.string "and catch a bunch of POKéMON!$"
# 31 "data/maps/OldaleTown_Mart/scripts.pory"

# 32 "data/maps/OldaleTown_Mart/scripts.pory"
OldaleTown_Mart_Text_RestoreHPWithPotion:
# 33 "data/maps/OldaleTown_Mart/scripts.pory"
	.string "If a POKéMON gets hurt and loses its HP\n"
# 34 "data/maps/OldaleTown_Mart/scripts.pory"
	.string "and faints, it won't be able to battle.\p"
# 35 "data/maps/OldaleTown_Mart/scripts.pory"
	.string "To prevent your POKéMON from fainting,\n"
# 36 "data/maps/OldaleTown_Mart/scripts.pory"
	.string "restore its HP with a POTION.$"

OldaleTown_Mart_EventScript_Clerk::
# 41 "data/maps/OldaleTown_Mart/scripts.pory"
	lock
# 42 "data/maps/OldaleTown_Mart/scripts.pory"
	faceplayer
# 43 "data/maps/OldaleTown_Mart/scripts.pory"
	message OldaleTown_Mart_EventScript_Clerk_Text_0
# 44 "data/maps/OldaleTown_Mart/scripts.pory"
	waitmessage
# 45 "data/maps/OldaleTown_Mart/scripts.pory"
	goto_if_set FLAG_ADVENTURE_STARTED, OldaleTown_Mart_EventScript_Clerk_2
# 57 "data/maps/OldaleTown_Mart/scripts.pory"
	pokemart BasicMartItems
OldaleTown_Mart_EventScript_Clerk_1:
# 59 "data/maps/OldaleTown_Mart/scripts.pory"
	msgbox OldaleTown_Mart_EventScript_Clerk_Text_1
# 60 "data/maps/OldaleTown_Mart/scripts.pory"
	release
	end

OldaleTown_Mart_EventScript_Clerk_2:
# 46 "data/maps/OldaleTown_Mart/scripts.pory"
	goto_if_set FLAG_RESOURCE_MODE, OldaleTown_Mart_EventScript_Clerk_18
OldaleTown_Mart_EventScript_Clerk_16:
# 48 "data/maps/OldaleTown_Mart/scripts.pory"
	goto_if_set FLAG_RESOURCE_MODE, OldaleTown_Mart_EventScript_Clerk_15
OldaleTown_Mart_EventScript_Clerk_13:
# 50 "data/maps/OldaleTown_Mart/scripts.pory"
	goto_if_unset FLAG_RESOURCE_MODE, OldaleTown_Mart_EventScript_Clerk_12
OldaleTown_Mart_EventScript_Clerk_10:
# 52 "data/maps/OldaleTown_Mart/scripts.pory"
	goto_if_unset FLAG_RESOURCE_MODE, OldaleTown_Mart_EventScript_Clerk_9
	goto OldaleTown_Mart_EventScript_Clerk_1

OldaleTown_Mart_EventScript_Clerk_5:
# 47 "data/maps/OldaleTown_Mart/scripts.pory"
	pokemart StockedMartItemsResourceEVs
	goto OldaleTown_Mart_EventScript_Clerk_1

OldaleTown_Mart_EventScript_Clerk_6:
# 49 "data/maps/OldaleTown_Mart/scripts.pory"
	pokemart StockedMartItemsResourceEVless
	goto OldaleTown_Mart_EventScript_Clerk_1

OldaleTown_Mart_EventScript_Clerk_7:
# 51 "data/maps/OldaleTown_Mart/scripts.pory"
	pokemart StockedMartItemsResourcefulEVs
	goto OldaleTown_Mart_EventScript_Clerk_1

OldaleTown_Mart_EventScript_Clerk_8:
# 53 "data/maps/OldaleTown_Mart/scripts.pory"
	pokemart StockedMartItemsResourcefulEVless
	goto OldaleTown_Mart_EventScript_Clerk_1

OldaleTown_Mart_EventScript_Clerk_9:
# 52 "data/maps/OldaleTown_Mart/scripts.pory"
	goto_if_unset FLAG_EV_MODE, OldaleTown_Mart_EventScript_Clerk_8
	goto OldaleTown_Mart_EventScript_Clerk_1

OldaleTown_Mart_EventScript_Clerk_12:
# 50 "data/maps/OldaleTown_Mart/scripts.pory"
	goto_if_set FLAG_EV_MODE, OldaleTown_Mart_EventScript_Clerk_7
	goto OldaleTown_Mart_EventScript_Clerk_10

OldaleTown_Mart_EventScript_Clerk_15:
# 48 "data/maps/OldaleTown_Mart/scripts.pory"
	goto_if_unset FLAG_EV_MODE, OldaleTown_Mart_EventScript_Clerk_6
	goto OldaleTown_Mart_EventScript_Clerk_13

OldaleTown_Mart_EventScript_Clerk_18:
# 46 "data/maps/OldaleTown_Mart/scripts.pory"
	goto_if_set FLAG_EV_MODE, OldaleTown_Mart_EventScript_Clerk_5
	goto OldaleTown_Mart_EventScript_Clerk_16


	.align 2
# 64 "data/maps/OldaleTown_Mart/scripts.pory"
BasicMartItems:
# 65 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_POTION
# 66 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 67 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 68 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 69 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_EXP_CANDY_XS
# 70 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_REPEL
	.2byte ITEM_NONE

	.align 2
# 73 "data/maps/OldaleTown_Mart/scripts.pory"
StockedMartItemsResourceEVless:
# 74 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 75 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_POTION
# 76 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 77 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 78 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 79 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_EXP_CANDY_XS
# 80 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_POMEG_BERRY
# 81 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_REPEL
	.2byte ITEM_NONE

	.align 2
# 84 "data/maps/OldaleTown_Mart/scripts.pory"
StockedMartItemsResourceEVs:
# 85 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 86 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_POTION
# 87 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 88 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 89 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 90 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_EXP_CANDY_XS
# 91 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_POMEG_BERRY
# 92 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 93 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_HEALTH_FEATHER
	.2byte ITEM_NONE

	.align 2
# 96 "data/maps/OldaleTown_Mart/scripts.pory"
StockedMartItemsResourcefulEVless:
# 97 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 98 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_POTION
# 99 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 100 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 101 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 102 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_EXP_CANDY_XS
# 103 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_POMEG_BERRY
# 104 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 105 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_SERIOUS_MINT
	.2byte ITEM_NONE

	.align 2
# 108 "data/maps/OldaleTown_Mart/scripts.pory"
StockedMartItemsResourcefulEVs:
# 109 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 110 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_POTION
# 111 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 112 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 113 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 114 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_EXP_CANDY_XS
# 115 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_POMEG_BERRY
# 116 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 117 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_SERIOUS_MINT
# 118 "data/maps/OldaleTown_Mart/scripts.pory"
	.2byte ITEM_HEALTH_FEATHER
	.2byte ITEM_NONE

OldaleTown_Mart_EventScript_Clerk_Text_0:
# 43 "data/maps/OldaleTown_Mart/scripts.pory"
	.string "How May I serve you?$"

OldaleTown_Mart_EventScript_Clerk_Text_1:
# 59 "data/maps/OldaleTown_Mart/scripts.pory"
	.string "Please Come Again$"
