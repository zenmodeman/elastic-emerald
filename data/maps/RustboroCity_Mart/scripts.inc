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
	end


	.align 2
# 95 "data/maps/RustboroCity_Mart/scripts.pory"
Rustburo_MartItemsResourceEVless:
# 96 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 97 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_TIMER_BALL
# 98 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_REPEAT_BALL
# 99 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_POTION
# 100 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_SUPER_POTION
# 101 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 102 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 103 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 104 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 105 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_EXP_CANDY_XS
# 106 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_KELPSY_BERRY
# 107 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_X_DEFENSE
# 108 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_REPEL
	.2byte ITEM_NONE

	.align 2
# 111 "data/maps/RustboroCity_Mart/scripts.pory"
Rustburo_MartItemsResourceEVs:
# 112 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 113 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_TIMER_BALL
# 114 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_REPEAT_BALL
# 115 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_POTION
# 116 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_SUPER_POTION
# 117 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 118 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 119 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 120 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 121 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_EXP_CANDY_XS
# 122 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_KELPSY_BERRY
# 123 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_X_DEFENSE
# 124 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 125 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_MUSCLE_FEATHER
	.2byte ITEM_NONE

	.align 2
# 128 "data/maps/RustboroCity_Mart/scripts.pory"
Rustburo_MartItemsResourcefulEVless:
# 129 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 130 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_TIMER_BALL
# 131 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_REPEAT_BALL
# 132 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_POTION
# 133 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_SUPER_POTION
# 134 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 135 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 136 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 137 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 138 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_EXP_CANDY_XS
# 139 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_KELPSY_BERRY
# 140 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_X_DEFENSE
# 141 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 142 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_GENTLE_MINT
	.2byte ITEM_NONE

	.align 2
# 145 "data/maps/RustboroCity_Mart/scripts.pory"
Rustburo_MartItemsResourcefulEVs:
# 146 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 147 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_TIMER_BALL
# 148 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_REPEAT_BALL
# 149 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_POTION
# 150 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_SUPER_POTION
# 151 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 152 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 153 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 154 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_AWAKENING
# 155 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_EXP_CANDY_XS
# 156 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_KELPSY_BERRY
# 157 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_X_DEFENSE
# 158 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_REPEL
# 159 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_GENTLE_MINT
# 160 "data/maps/RustboroCity_Mart/scripts.pory"
	.2byte ITEM_MUSCLE_FEATHER
	.2byte ITEM_NONE
