# 1 "data/maps/RustboroCity_Mart/scripts.pory"

# 2 "data/maps/RustboroCity_Mart/scripts.pory"

# 3 "data/maps/RustboroCity_Mart/scripts.pory"
RustboroCity_Mart_MapScripts::
# 4 "data/maps/RustboroCity_Mart/scripts.pory"
	.byte 0
# 5 "data/maps/RustboroCity_Mart/scripts.pory"

# 6 "data/maps/RustboroCity_Mart/scripts.pory"

# 7 "data/maps/RustboroCity_Mart/scripts.pory"

# 8 "data/maps/RustboroCity_Mart/scripts.pory"
RustboroCity_Mart_EventScript_PokemartBasic::
# 9 "data/maps/RustboroCity_Mart/scripts.pory"
	pokemart RustboroCity_Mart_Pokemart_Basic
# 10 "data/maps/RustboroCity_Mart/scripts.pory"
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
# 11 "data/maps/RustboroCity_Mart/scripts.pory"
	release
# 12 "data/maps/RustboroCity_Mart/scripts.pory"
	end
# 13 "data/maps/RustboroCity_Mart/scripts.pory"

# 14 "data/maps/RustboroCity_Mart/scripts.pory"
	.align 2
# 15 "data/maps/RustboroCity_Mart/scripts.pory"
RustboroCity_Mart_Pokemart_Basic:
# 16 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 17 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_POTION
# 18 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_SUPER_POTION
# 19 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 20 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 21 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 22 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 23 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_X_SPEED
# 24 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_X_ATTACK
# 25 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_X_DEFENSE
# 26 "data/maps/RustboroCity_Mart/scripts.pory"
	pokemartlistend
# 27 "data/maps/RustboroCity_Mart/scripts.pory"

# 28 "data/maps/RustboroCity_Mart/scripts.pory"
RustboroCity_Mart_EventScript_PokemartExpanded::
# 29 "data/maps/RustboroCity_Mart/scripts.pory"
	pokemart RustboroCity_Mart_Pokemart_Expanded
# 30 "data/maps/RustboroCity_Mart/scripts.pory"
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
# 31 "data/maps/RustboroCity_Mart/scripts.pory"
	release
# 32 "data/maps/RustboroCity_Mart/scripts.pory"
	end
# 33 "data/maps/RustboroCity_Mart/scripts.pory"

# 34 "data/maps/RustboroCity_Mart/scripts.pory"
	.align 2
# 35 "data/maps/RustboroCity_Mart/scripts.pory"
RustboroCity_Mart_Pokemart_Expanded:
# 36 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 37 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_TIMER_BALL
# 38 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_REPEAT_BALL
# 39 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_POTION
# 40 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_SUPER_POTION
# 41 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 42 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 43 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 44 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 45 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_X_SPEED
# 46 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_X_ATTACK
# 47 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_X_DEFENSE
# 48 "data/maps/RustboroCity_Mart/scripts.pory"
	pokemartlistend
# 49 "data/maps/RustboroCity_Mart/scripts.pory"

# 50 "data/maps/RustboroCity_Mart/scripts.pory"
RustboroCity_Mart_EventScript_PokefanF::
# 51 "data/maps/RustboroCity_Mart/scripts.pory"
	msgbox RustboroCity_Mart_Text_BuyingHealsInCaseOfShroomish, MSGBOX_NPC
# 52 "data/maps/RustboroCity_Mart/scripts.pory"
	end
# 53 "data/maps/RustboroCity_Mart/scripts.pory"

# 54 "data/maps/RustboroCity_Mart/scripts.pory"
RustboroCity_Mart_EventScript_Boy::
# 55 "data/maps/RustboroCity_Mart/scripts.pory"
	msgbox RustboroCity_Mart_Text_ShouldBuySuperPotionsInstead, MSGBOX_NPC
# 56 "data/maps/RustboroCity_Mart/scripts.pory"
	end
# 57 "data/maps/RustboroCity_Mart/scripts.pory"

# 58 "data/maps/RustboroCity_Mart/scripts.pory"
RustboroCity_Mart_EventScript_BugCatcher::
# 59 "data/maps/RustboroCity_Mart/scripts.pory"
	msgbox RustboroCity_Mart_Text_GettingEscapeRopeJustInCase, MSGBOX_NPC
# 60 "data/maps/RustboroCity_Mart/scripts.pory"
	end
# 61 "data/maps/RustboroCity_Mart/scripts.pory"

# 62 "data/maps/RustboroCity_Mart/scripts.pory"
RustboroCity_Mart_Text_BuyingHealsInCaseOfShroomish:
# 63 "data/maps/RustboroCity_Mart/scripts.pory"
	.string "I'm buying some PARLYZ HEALS and\n"
# 64 "data/maps/RustboroCity_Mart/scripts.pory"
	.string "ANTIDOTES.\p"
# 65 "data/maps/RustboroCity_Mart/scripts.pory"
	.string "Just in case I run into SHROOMISH\n"
# 66 "data/maps/RustboroCity_Mart/scripts.pory"
	.string "in PETALBURG WOODS.$"
# 67 "data/maps/RustboroCity_Mart/scripts.pory"

# 68 "data/maps/RustboroCity_Mart/scripts.pory"
RustboroCity_Mart_Text_ShouldBuySuperPotionsInstead:
# 69 "data/maps/RustboroCity_Mart/scripts.pory"
	.string "My POKéMON evolved.\n"
# 70 "data/maps/RustboroCity_Mart/scripts.pory"
	.string "It has a lot of HP now.\p"
# 71 "data/maps/RustboroCity_Mart/scripts.pory"
	.string "I should buy SUPER POTIONS for it\n"
# 72 "data/maps/RustboroCity_Mart/scripts.pory"
	.string "instead of ordinary POTIONS.$"
# 73 "data/maps/RustboroCity_Mart/scripts.pory"

# 74 "data/maps/RustboroCity_Mart/scripts.pory"
RustboroCity_Mart_Text_GettingEscapeRopeJustInCase:
# 75 "data/maps/RustboroCity_Mart/scripts.pory"
	.string "I'm getting an ESCAPE ROPE just in\n"
# 76 "data/maps/RustboroCity_Mart/scripts.pory"
	.string "case I get lost in a cave.\p"
# 77 "data/maps/RustboroCity_Mart/scripts.pory"
	.string "I just need to use it to get back to\n"
# 78 "data/maps/RustboroCity_Mart/scripts.pory"
	.string "the entrance.$"

RustboroCity_Mart_EventScript_Clerk::
# 83 "data/maps/RustboroCity_Mart/scripts.pory"
	lock
# 84 "data/maps/RustboroCity_Mart/scripts.pory"
	faceplayer
# 85 "data/maps/RustboroCity_Mart/scripts.pory"
	message gText_HowMayIServeYou
# 86 "data/maps/RustboroCity_Mart/scripts.pory"
	waitmessage
# 88 "data/maps/RustboroCity_Mart/scripts.pory"
	goto_if_set FLAG_RESOURCE_MODE, RustboroCity_Mart_EventScript_Clerk_15
RustboroCity_Mart_EventScript_Clerk_13:
# 90 "data/maps/RustboroCity_Mart/scripts.pory"
	goto_if_set FLAG_RESOURCE_MODE, RustboroCity_Mart_EventScript_Clerk_12
RustboroCity_Mart_EventScript_Clerk_10:
# 92 "data/maps/RustboroCity_Mart/scripts.pory"
	goto_if_unset FLAG_RESOURCE_MODE, RustboroCity_Mart_EventScript_Clerk_9
RustboroCity_Mart_EventScript_Clerk_7:
# 94 "data/maps/RustboroCity_Mart/scripts.pory"
	goto_if_unset FLAG_RESOURCE_MODE, RustboroCity_Mart_EventScript_Clerk_6
RustboroCity_Mart_EventScript_Clerk_1:
# 100 "data/maps/RustboroCity_Mart/scripts.pory"
	msgbox RustboroCity_Mart_EventScript_Clerk_Text_0
# 101 "data/maps/RustboroCity_Mart/scripts.pory"
	release
	end

RustboroCity_Mart_EventScript_Clerk_2:
# 89 "data/maps/RustboroCity_Mart/scripts.pory"
	pokemart Rustburo_MartItemsResourceEVs
	goto RustboroCity_Mart_EventScript_Clerk_1

RustboroCity_Mart_EventScript_Clerk_3:
# 91 "data/maps/RustboroCity_Mart/scripts.pory"
	pokemart Rustburo_MartItemsResourceEVless
	goto RustboroCity_Mart_EventScript_Clerk_1

RustboroCity_Mart_EventScript_Clerk_4:
# 93 "data/maps/RustboroCity_Mart/scripts.pory"
	pokemart Rustburo_MartItemsResourcefulEVless
	goto RustboroCity_Mart_EventScript_Clerk_1

RustboroCity_Mart_EventScript_Clerk_5:
# 95 "data/maps/RustboroCity_Mart/scripts.pory"
	pokemart Rustburo_MartItemsResourcefulEVless
	goto RustboroCity_Mart_EventScript_Clerk_1

RustboroCity_Mart_EventScript_Clerk_6:
# 94 "data/maps/RustboroCity_Mart/scripts.pory"
	goto_if_unset FLAG_EV_MODE, RustboroCity_Mart_EventScript_Clerk_5
	goto RustboroCity_Mart_EventScript_Clerk_1

RustboroCity_Mart_EventScript_Clerk_9:
# 92 "data/maps/RustboroCity_Mart/scripts.pory"
	goto_if_set FLAG_EV_MODE, RustboroCity_Mart_EventScript_Clerk_4
	goto RustboroCity_Mart_EventScript_Clerk_7

RustboroCity_Mart_EventScript_Clerk_12:
# 90 "data/maps/RustboroCity_Mart/scripts.pory"
	goto_if_unset FLAG_EV_MODE, RustboroCity_Mart_EventScript_Clerk_3
	goto RustboroCity_Mart_EventScript_Clerk_10

RustboroCity_Mart_EventScript_Clerk_15:
# 88 "data/maps/RustboroCity_Mart/scripts.pory"
	goto_if_set FLAG_EV_MODE, RustboroCity_Mart_EventScript_Clerk_2
	goto RustboroCity_Mart_EventScript_Clerk_13


	.align 2
# 105 "data/maps/RustboroCity_Mart/scripts.pory"
Rustburo_MartItemsResourceEVless:
# 106 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 107 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_GREAT_BALL
# 108 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_POTION
# 109 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_SUPER_POTION
# 110 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 111 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 112 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 113 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 114 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_EXP_CANDY_XS
# 115 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_HONDEW_BERRY
# 116 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_X_ACCURACY
# 117 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_REPEL
	.2byte ITEM_NONE

	.align 2
# 120 "data/maps/RustboroCity_Mart/scripts.pory"
Rustburo_MartItemsResourceEVs:
# 121 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 122 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_GREAT_BALL
# 123 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_POTION
# 124 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_SUPER_POTION
# 125 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 126 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 127 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 128 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 129 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_EXP_CANDY_XS
# 130 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_HONDEW_BERRY
# 131 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_X_ACCURACY
# 132 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 133 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_MUSCLE_FEATHER
	.2byte ITEM_NONE

	.align 2
# 136 "data/maps/RustboroCity_Mart/scripts.pory"
Rustburo_MartItemsResourcefulEVless:
# 137 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 138 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_GREAT_BALL
# 139 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_POTION
# 140 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_SUPER_POTION
# 141 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 142 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 143 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 144 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 145 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_EXP_CANDY_XS
# 146 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_HONDEW_BERRY
# 147 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_X_ACCURACY
# 148 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 149 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_GENTLE_MINT
	.2byte ITEM_NONE

	.align 2
# 152 "data/maps/RustboroCity_Mart/scripts.pory"
Rustburo_MartItemsResourcefulEVs:
# 153 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 154 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_GREAT_BALL
# 155 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_POTION
# 156 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_SUPER_POTION
# 157 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 158 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 159 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 160 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 161 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_EXP_CANDY_XS
# 162 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_HONDEW_BERRY
# 163 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_X_ACCURACY
# 164 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 165 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_GENTLE_MINT
# 166 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_MUSCLE_FEATHER
	.2byte ITEM_NONE

RustboroCity_Mart_EventScript_Clerk_Text_0:
# 100 "data/maps/RustboroCity_Mart/scripts.pory"
	.string "Please Come Again$"
