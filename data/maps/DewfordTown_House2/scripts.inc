# 1 "data/maps/DewfordTown_House2/scripts.pory"

# 2 "data/maps/DewfordTown_House2/scripts.pory"
DewfordTown_House2_MapScripts::
# 3 "data/maps/DewfordTown_House2/scripts.pory"
	.byte 0
# 4 "data/maps/DewfordTown_House2/scripts.pory"

# 5 "data/maps/DewfordTown_House2/scripts.pory"
DewfordTown_House2_EventScript_Man::
# 6 "data/maps/DewfordTown_House2/scripts.pory"
	lock
# 7 "data/maps/DewfordTown_House2/scripts.pory"
	faceplayer
# 8 "data/maps/DewfordTown_House2/scripts.pory"
	goto_if_set FLAG_RECEIVED_SILK_SCARF, DewfordTown_House2_EventScript_ExplainSilkScarf
# 9 "data/maps/DewfordTown_House2/scripts.pory"
	msgbox DewfordTown_House2_Text_WantYouToHaveSilkScarf, MSGBOX_DEFAULT
# 10 "data/maps/DewfordTown_House2/scripts.pory"
	giveitem ITEM_SILK_SCARF
# 11 "data/maps/DewfordTown_House2/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, DewfordTown_House2_EventScript_NoRoomForScarf
# 12 "data/maps/DewfordTown_House2/scripts.pory"
	setflag FLAG_RECEIVED_SILK_SCARF
# 13 "data/maps/DewfordTown_House2/scripts.pory"
	release
# 14 "data/maps/DewfordTown_House2/scripts.pory"
	end
# 15 "data/maps/DewfordTown_House2/scripts.pory"

# 16 "data/maps/DewfordTown_House2/scripts.pory"
DewfordTown_House2_EventScript_NoRoomForScarf::
# 17 "data/maps/DewfordTown_House2/scripts.pory"
	msgbox DewfordTown_House2_Text_NoRoom, MSGBOX_DEFAULT
# 18 "data/maps/DewfordTown_House2/scripts.pory"
	release
# 19 "data/maps/DewfordTown_House2/scripts.pory"
	end
# 20 "data/maps/DewfordTown_House2/scripts.pory"

# 21 "data/maps/DewfordTown_House2/scripts.pory"
DewfordTown_House2_EventScript_ExplainSilkScarf::
# 22 "data/maps/DewfordTown_House2/scripts.pory"
	msgbox DewfordTown_House2_Text_ExplainSilkScarf, MSGBOX_DEFAULT
# 23 "data/maps/DewfordTown_House2/scripts.pory"
	release
# 24 "data/maps/DewfordTown_House2/scripts.pory"
	end
# 25 "data/maps/DewfordTown_House2/scripts.pory"

# 26 "data/maps/DewfordTown_House2/scripts.pory"
DewfordTown_House2_EventScript_Boy::
# 27 "data/maps/DewfordTown_House2/scripts.pory"
	msgbox DewfordTown_House2_Text_BrawlySoCool, MSGBOX_NPC
# 28 "data/maps/DewfordTown_House2/scripts.pory"
	end
# 29 "data/maps/DewfordTown_House2/scripts.pory"

# 30 "data/maps/DewfordTown_House2/scripts.pory"
DewfordTown_House2_Text_WantYouToHaveSilkScarf:
# 31 "data/maps/DewfordTown_House2/scripts.pory"
	.string "Gorge your eyes on this!\p"
# 32 "data/maps/DewfordTown_House2/scripts.pory"
	.string "It's a SILK SCARF. It's right at the\n"
# 33 "data/maps/DewfordTown_House2/scripts.pory"
	.string "cutting edge of fashion, yeah!\p"
# 34 "data/maps/DewfordTown_House2/scripts.pory"
	.string "Oh, I can see your eyes twinkling!\n"
# 35 "data/maps/DewfordTown_House2/scripts.pory"
	.string "You appreciate my dazzling style!\p"
# 36 "data/maps/DewfordTown_House2/scripts.pory"
	.string "Oh, you're a delight!\n"
# 37 "data/maps/DewfordTown_House2/scripts.pory"
	.string "Here you go. I want you to have it!$"
# 38 "data/maps/DewfordTown_House2/scripts.pory"

# 39 "data/maps/DewfordTown_House2/scripts.pory"
DewfordTown_House2_Text_NoRoom:
# 40 "data/maps/DewfordTown_House2/scripts.pory"
	.string "Oh, you don't have room?\p"
# 41 "data/maps/DewfordTown_House2/scripts.pory"
	.string "Now, listen tight, this SCARF is a must-\n"
# 42 "data/maps/DewfordTown_House2/scripts.pory"
	.string "have! Why, I would sell all my items\l"
# 43 "data/maps/DewfordTown_House2/scripts.pory"
	.string "in order to get it!$"
# 44 "data/maps/DewfordTown_House2/scripts.pory"

# 45 "data/maps/DewfordTown_House2/scripts.pory"
DewfordTown_House2_Text_ExplainSilkScarf:
# 46 "data/maps/DewfordTown_House2/scripts.pory"
	.string "The SILK SCARF raises the power of\n"
# 47 "data/maps/DewfordTown_House2/scripts.pory"
	.string "NORMAL-type moves.\p"
# 48 "data/maps/DewfordTown_House2/scripts.pory"
	.string "It's a marvelous SCARF that will go\n"
# 49 "data/maps/DewfordTown_House2/scripts.pory"
	.string "with almost all POKéMON!$"
# 50 "data/maps/DewfordTown_House2/scripts.pory"

# 51 "data/maps/DewfordTown_House2/scripts.pory"
DewfordTown_House2_Text_BrawlySoCool:
# 52 "data/maps/DewfordTown_House2/scripts.pory"
	.string "Wow, you bothered to cross the sea\n"
# 53 "data/maps/DewfordTown_House2/scripts.pory"
	.string "to visit DEWFORD?\p"
# 54 "data/maps/DewfordTown_House2/scripts.pory"
	.string "Did you maybe come here because you\n"
# 55 "data/maps/DewfordTown_House2/scripts.pory"
	.string "heard about BRAWLY?\p"
# 56 "data/maps/DewfordTown_House2/scripts.pory"
	.string "He's so cool…\n"
# 57 "data/maps/DewfordTown_House2/scripts.pory"
	.string "Everyone idolizes him.$"

DewfordTown_OldManGifter::
# 62 "data/maps/DewfordTown_House2/scripts.pory"
	lock
# 63 "data/maps/DewfordTown_House2/scripts.pory"
	faceplayer
# 64 "data/maps/DewfordTown_House2/scripts.pory"
	goto_if_set FLAG_DEWFORD_GIFT_MAN, DewfordTown_OldManGifter_2
# 69 "data/maps/DewfordTown_House2/scripts.pory"
	msgbox DewfordTown_OldManGifter_Text_1
# 70 "data/maps/DewfordTown_House2/scripts.pory"
	msgbox DewfordTown_OldManGifter_Text_2
# 72 "data/maps/DewfordTown_House2/scripts.pory"
	compare VAR_MONOTYPE, TYPE_NONE
	goto_if_eq DewfordTown_OldManGifter_5
# 72 "data/maps/DewfordTown_House2/scripts.pory"
	compare VAR_MONOTYPE, TYPE_FLYING
	goto_if_eq DewfordTown_OldManGifter_5
# 72 "data/maps/DewfordTown_House2/scripts.pory"
	compare VAR_MONOTYPE, TYPE_ICE - 1
	goto_if_eq DewfordTown_OldManGifter_5
# 99 "data/maps/DewfordTown_House2/scripts.pory"
	msgbox DewfordTown_OldManGifter_Text_14
# 100 "data/maps/DewfordTown_House2/scripts.pory"
	giveitem ITEM_CHERISH_BALL
# 101 "data/maps/DewfordTown_House2/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq DewfordTown_OldManGifter_16
# 104 "data/maps/DewfordTown_House2/scripts.pory"
	setflag FLAG_DEWFORD_GIFT_MAN
DewfordTown_OldManGifter_15:
# 107 "data/maps/DewfordTown_House2/scripts.pory"
	msgbox DewfordTown_OldManGifter_Text_15
DewfordTown_OldManGifter_4:
# 109 "data/maps/DewfordTown_House2/scripts.pory"
	release
	end

DewfordTown_OldManGifter_2:
# 65 "data/maps/DewfordTown_House2/scripts.pory"
	msgbox DewfordTown_OldManGifter_Text_0
# 66 "data/maps/DewfordTown_House2/scripts.pory"
	release
	end

DewfordTown_OldManGifter_5:
# 73 "data/maps/DewfordTown_House2/scripts.pory"
	msgbox DewfordTown_OldManGifter_Text_3
# 74 "data/maps/DewfordTown_House2/scripts.pory"
	msgbox DewfordTown_OldManGifter_Text_4
# 75 "data/maps/DewfordTown_House2/scripts.pory"
	msgbox DewfordTown_OldManGifter_Text_5
# 76 "data/maps/DewfordTown_House2/scripts.pory"
	msgbox DewfordTown_OldManGifter_Text_6
# 77 "data/maps/DewfordTown_House2/scripts.pory"
	msgbox DewfordTown_OldManGifter_Text_7
# 78 "data/maps/DewfordTown_House2/scripts.pory"
	msgbox DewfordTown_OldManGifter_Text_8, MSGBOX_YESNO
# 79 "data/maps/DewfordTown_House2/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq DewfordTown_OldManGifter_12
# 96 "data/maps/DewfordTown_House2/scripts.pory"
	msgbox DewfordTown_OldManGifter_Text_13
	goto DewfordTown_OldManGifter_4

DewfordTown_OldManGifter_12:
# 80 "data/maps/DewfordTown_House2/scripts.pory"
	givemon SPECIES_DELIBIRD, 15, ITEM_CHERISH_BALL, ITEM_CHERISH_BALL, NATURE_HASTY, 0, 1, 0, 0, 0, 0, 0, 0, 20, 22, 30, 26, 24, 20, MOVE_PRESENT, MOVE_ICE_SHARD, MOVE_REVERSAL, MOVE_AIR_CUTTER
# 82 "data/maps/DewfordTown_House2/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 83 "data/maps/DewfordTown_House2/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PC
	goto_if_eq DewfordTown_OldManGifter_20
# 85 "data/maps/DewfordTown_House2/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq DewfordTown_OldManGifter_21
# 88 "data/maps/DewfordTown_House2/scripts.pory"
	msgbox DewfordTown_OldManGifter_Text_11
# 89 "data/maps/DewfordTown_House2/scripts.pory"
	release
	end

DewfordTown_OldManGifter_16:
# 102 "data/maps/DewfordTown_House2/scripts.pory"
	call Common_EventScript_ShowBagIsFull
	goto DewfordTown_OldManGifter_15

DewfordTown_OldManGifter_19:
# 92 "data/maps/DewfordTown_House2/scripts.pory"
	setflag FLAG_DEWFORD_GIFT_MAN
# 93 "data/maps/DewfordTown_House2/scripts.pory"
	msgbox DewfordTown_OldManGifter_Text_12
	goto DewfordTown_OldManGifter_4

DewfordTown_OldManGifter_20:
# 84 "data/maps/DewfordTown_House2/scripts.pory"
	msgbox DewfordTown_OldManGifter_Text_9
	goto DewfordTown_OldManGifter_19

DewfordTown_OldManGifter_21:
# 86 "data/maps/DewfordTown_House2/scripts.pory"
	msgbox DewfordTown_OldManGifter_Text_10
	goto DewfordTown_OldManGifter_19


DewfordTown_OldManGifter_Text_0:
# 65 "data/maps/DewfordTown_House2/scripts.pory"
	.string "I've got a good feeling. You and\n"
	.string "DELIBIRD will make folks around you\l"
	.string "smile.$"

DewfordTown_OldManGifter_Text_1:
# 69 "data/maps/DewfordTown_House2/scripts.pory"
	.string "I travelled the world when I was young,\n"
	.string "and received a lot of help.$"

DewfordTown_OldManGifter_Text_2:
# 70 "data/maps/DewfordTown_House2/scripts.pory"
	.string "Looking back, it was the little gifts\n"
	.string "and moments that stayed with me.$"

DewfordTown_OldManGifter_Text_3:
# 73 "data/maps/DewfordTown_House2/scripts.pory"
	.string "A DELIBIRD once helped me cross some\n"
	.string "snowy mountains.$"

DewfordTown_OldManGifter_Text_4:
# 74 "data/maps/DewfordTown_House2/scripts.pory"
	.string "We've been good friends ever since...$"

DewfordTown_OldManGifter_Text_5:
# 75 "data/maps/DewfordTown_House2/scripts.pory"
	.string "But maybe it'd be happier seeing more of\n"
	.string "the world.$"

DewfordTown_OldManGifter_Text_6:
# 76 "data/maps/DewfordTown_House2/scripts.pory"
	.string "You're travelling all across HOENN,\n"
	.string "right?$"

DewfordTown_OldManGifter_Text_7:
# 77 "data/maps/DewfordTown_House2/scripts.pory"
	.string "I think DELIBIRD would do great with\n"
	.string "you.$"

DewfordTown_OldManGifter_Text_8:
# 78 "data/maps/DewfordTown_House2/scripts.pory"
	.string "Would you like to take care of it?$"

DewfordTown_OldManGifter_Text_9:
# 84 "data/maps/DewfordTown_House2/scripts.pory"
	.string "Delibird was sent to the PC!$"

DewfordTown_OldManGifter_Text_10:
# 86 "data/maps/DewfordTown_House2/scripts.pory"
	.string "Received Delibird!$"

DewfordTown_OldManGifter_Text_11:
# 88 "data/maps/DewfordTown_House2/scripts.pory"
	.string "It seems like that can't take Delibird\n"
	.string "right now. That's a shame.$"

DewfordTown_OldManGifter_Text_12:
# 93 "data/maps/DewfordTown_House2/scripts.pory"
	.string "I look forward to hearing your travels\n"
	.string "with DELIBIRD!$"

DewfordTown_OldManGifter_Text_13:
# 96 "data/maps/DewfordTown_House2/scripts.pory"
	.string "That's a shame. I bet Delibird would love\n"
	.string "to travel with you.$"

DewfordTown_OldManGifter_Text_14:
# 99 "data/maps/DewfordTown_House2/scripts.pory"
	.string "Here, have a token of the wonderful\n"
	.string "memories I made.$"

DewfordTown_OldManGifter_Text_15:
# 107 "data/maps/DewfordTown_House2/scripts.pory"
	.string "Good luck on your journey!$"
