# 1 "data/maps/PetalburgCity_Mart/scripts.pory"

# 2 "data/maps/PetalburgCity_Mart/scripts.pory"

# 3 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_MapScripts::
# 4 "data/maps/PetalburgCity_Mart/scripts.pory"
	.byte 0
# 5 "data/maps/PetalburgCity_Mart/scripts.pory"

# 6 "data/maps/PetalburgCity_Mart/scripts.pory"
	.align 2
# 7 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_Pokemart_Basic:
# 8 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 9 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_POTION
# 10 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 11 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 12 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 13 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 14 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 15 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_X_SPEED
# 16 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_X_ATTACK
# 17 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_X_DEFENSE
# 18 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ORANGE_MAIL
# 19 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_NONE
# 20 "data/maps/PetalburgCity_Mart/scripts.pory"
	release
# 21 "data/maps/PetalburgCity_Mart/scripts.pory"
	end
# 22 "data/maps/PetalburgCity_Mart/scripts.pory"

# 23 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_EventScript_ExpandedItems::
# 24 "data/maps/PetalburgCity_Mart/scripts.pory"
	pokemart PetalburgCity_Mart_Pokemart_Expanded
# 25 "data/maps/PetalburgCity_Mart/scripts.pory"
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
# 26 "data/maps/PetalburgCity_Mart/scripts.pory"
	release
# 27 "data/maps/PetalburgCity_Mart/scripts.pory"
	end
# 28 "data/maps/PetalburgCity_Mart/scripts.pory"

# 29 "data/maps/PetalburgCity_Mart/scripts.pory"
	.align 2
# 30 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_Pokemart_Expanded:
# 31 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 32 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_GREAT_BALL
# 33 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_POTION
# 34 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_SUPER_POTION
# 35 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 36 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 37 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 38 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 39 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 40 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_X_SPEED
# 41 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_X_ATTACK
# 42 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_X_DEFENSE
# 43 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ORANGE_MAIL
# 44 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_NONE
# 45 "data/maps/PetalburgCity_Mart/scripts.pory"
	release
# 46 "data/maps/PetalburgCity_Mart/scripts.pory"
	end
# 47 "data/maps/PetalburgCity_Mart/scripts.pory"

# 48 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_EventScript_Woman::
# 49 "data/maps/PetalburgCity_Mart/scripts.pory"
	msgbox PetalburgCity_Mart_Text_WeakWillGrowStronger, MSGBOX_NPC
# 50 "data/maps/PetalburgCity_Mart/scripts.pory"
	end
# 51 "data/maps/PetalburgCity_Mart/scripts.pory"

# 52 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_EventScript_Boy::
# 53 "data/maps/PetalburgCity_Mart/scripts.pory"
	msgbox PetalburgCity_Mart_Text_RepelIsUseful, MSGBOX_NPC
# 54 "data/maps/PetalburgCity_Mart/scripts.pory"
	end
# 55 "data/maps/PetalburgCity_Mart/scripts.pory"

# 56 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_EventScript_Man::
# 57 "data/maps/PetalburgCity_Mart/scripts.pory"
	msgbox PetalburgCity_Mart_Text_TakeSomeAntidotesWithYou, MSGBOX_NPC
# 58 "data/maps/PetalburgCity_Mart/scripts.pory"
	end
# 59 "data/maps/PetalburgCity_Mart/scripts.pory"

# 60 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_Text_WeakWillGrowStronger:
# 61 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "Even if a POKéMON is weak now,\n"
# 62 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "it will grow stronger.\p"
# 63 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "The most important thing is love!\n"
# 64 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "Love for your POKéMON!$"
# 65 "data/maps/PetalburgCity_Mart/scripts.pory"

# 66 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_Text_RepelIsUseful:
# 67 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "Do you use REPEL?\n"
# 68 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "It keeps POKéMON away, so it's\l"
# 69 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "useful when you're in a hurry.$"
# 70 "data/maps/PetalburgCity_Mart/scripts.pory"

# 71 "data/maps/PetalburgCity_Mart/scripts.pory"
PetalburgCity_Mart_Text_TakeSomeAntidotesWithYou:
# 72 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "Do you have any ANTIDOTES with\n"
# 73 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "you?\p"
# 74 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "If you walk around with a poisoned\n"
# 75 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "POKéMON, it will lose HP until it faints.\l"
# 76 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "Take some ANTIDOTES with you.$"

PetalburgCity_Mart_EventScript_Clerk::
# 82 "data/maps/PetalburgCity_Mart/scripts.pory"
	lock
# 83 "data/maps/PetalburgCity_Mart/scripts.pory"
	faceplayer
# 84 "data/maps/PetalburgCity_Mart/scripts.pory"
	message PetalburgCity_Mart_EventScript_Clerk_Text_0
# 85 "data/maps/PetalburgCity_Mart/scripts.pory"
	waitmessage
# 86 "data/maps/PetalburgCity_Mart/scripts.pory"
	goto_if_set FLAG_RESOURCE_MODE, PetalburgCity_Mart_EventScript_Clerk_15
PetalburgCity_Mart_EventScript_Clerk_13:
# 88 "data/maps/PetalburgCity_Mart/scripts.pory"
	goto_if_set FLAG_RESOURCE_MODE, PetalburgCity_Mart_EventScript_Clerk_12
PetalburgCity_Mart_EventScript_Clerk_10:
# 90 "data/maps/PetalburgCity_Mart/scripts.pory"
	goto_if_unset FLAG_RESOURCE_MODE, PetalburgCity_Mart_EventScript_Clerk_9
PetalburgCity_Mart_EventScript_Clerk_7:
# 92 "data/maps/PetalburgCity_Mart/scripts.pory"
	goto_if_unset FLAG_RESOURCE_MODE, PetalburgCity_Mart_EventScript_Clerk_6
PetalburgCity_Mart_EventScript_Clerk_1:
# 95 "data/maps/PetalburgCity_Mart/scripts.pory"
	msgbox PetalburgCity_Mart_EventScript_Clerk_Text_1
# 96 "data/maps/PetalburgCity_Mart/scripts.pory"
	release
	end

PetalburgCity_Mart_EventScript_Clerk_2:
# 87 "data/maps/PetalburgCity_Mart/scripts.pory"
	pokemart Petalburg_MartItemsResourceEVs
	goto PetalburgCity_Mart_EventScript_Clerk_1

PetalburgCity_Mart_EventScript_Clerk_3:
# 89 "data/maps/PetalburgCity_Mart/scripts.pory"
	pokemart Petalburg_MartItemsResourceEVless
	goto PetalburgCity_Mart_EventScript_Clerk_1

PetalburgCity_Mart_EventScript_Clerk_4:
# 91 "data/maps/PetalburgCity_Mart/scripts.pory"
	pokemart Petalburg_MartItemsResourcefulEVs
	goto PetalburgCity_Mart_EventScript_Clerk_1

PetalburgCity_Mart_EventScript_Clerk_5:
# 93 "data/maps/PetalburgCity_Mart/scripts.pory"
	pokemart Petalburg_MartItemsResourcefulEVless
	goto PetalburgCity_Mart_EventScript_Clerk_1

PetalburgCity_Mart_EventScript_Clerk_6:
# 92 "data/maps/PetalburgCity_Mart/scripts.pory"
	goto_if_unset FLAG_EV_MODE, PetalburgCity_Mart_EventScript_Clerk_5
	goto PetalburgCity_Mart_EventScript_Clerk_1

PetalburgCity_Mart_EventScript_Clerk_9:
# 90 "data/maps/PetalburgCity_Mart/scripts.pory"
	goto_if_set FLAG_EV_MODE, PetalburgCity_Mart_EventScript_Clerk_4
	goto PetalburgCity_Mart_EventScript_Clerk_7

PetalburgCity_Mart_EventScript_Clerk_12:
# 88 "data/maps/PetalburgCity_Mart/scripts.pory"
	goto_if_unset FLAG_EV_MODE, PetalburgCity_Mart_EventScript_Clerk_3
	goto PetalburgCity_Mart_EventScript_Clerk_10

PetalburgCity_Mart_EventScript_Clerk_15:
# 86 "data/maps/PetalburgCity_Mart/scripts.pory"
	goto_if_set FLAG_EV_MODE, PetalburgCity_Mart_EventScript_Clerk_2
	goto PetalburgCity_Mart_EventScript_Clerk_13


	.align 2
# 100 "data/maps/PetalburgCity_Mart/scripts.pory"
Petalburg_MartItemsResourceEVless:
# 101 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 102 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_POTION
# 103 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_EXP_CANDY_XS
# 104 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 105 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 106 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 107 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 108 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 109 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_X_DEFENSE
# 110 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ORANGE_MAIL
# 111 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_KELPSY_BERRY
	.2byte ITEM_NONE

	.align 2
# 114 "data/maps/PetalburgCity_Mart/scripts.pory"
Petalburg_MartItemsResourceEVs:
# 115 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 116 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_POTION
# 117 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_EXP_CANDY_XS
# 118 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 119 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 120 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 121 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 122 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 123 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_X_DEFENSE
# 124 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ORANGE_MAIL
# 125 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_RESIST_FEATHER
# 126 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_KELPSY_BERRY
	.2byte ITEM_NONE

	.align 2
# 129 "data/maps/PetalburgCity_Mart/scripts.pory"
Petalburg_MartItemsResourcefulEVless:
# 130 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 131 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_POTION
# 132 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_EXP_CANDY_XS
# 133 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 134 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 135 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 136 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 137 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 138 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_X_DEFENSE
# 139 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ORANGE_MAIL
# 140 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_LAX_MINT
# 141 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_KELPSY_BERRY
	.2byte ITEM_NONE

	.align 2
# 144 "data/maps/PetalburgCity_Mart/scripts.pory"
Petalburg_MartItemsResourcefulEVs:
# 145 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 146 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_POTION
# 147 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_EXP_CANDY_XS
# 148 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 149 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 150 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 151 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 152 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 153 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_X_DEFENSE
# 154 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_ORANGE_MAIL
# 155 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_LAX_MINT
# 156 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_RESIST_FEATHER
# 157 "data/maps/PetalburgCity_Mart/scripts.pory"
	.2byte ITEM_KELPSY_BERRY
	.2byte ITEM_NONE

PetalburgCity_Mart_EventScript_Clerk_Text_0:
# 84 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "How May I serve you?$"

PetalburgCity_Mart_EventScript_Clerk_Text_1:
# 95 "data/maps/PetalburgCity_Mart/scripts.pory"
	.string "Please Come Again$"
