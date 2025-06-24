# 1 "data/maps/RustboroCity_House1/scripts.pory"

# 2 "data/maps/RustboroCity_House1/scripts.pory"

# 3 "data/maps/RustboroCity_House1/scripts.pory"
RustboroCity_House1_MapScripts::
# 4 "data/maps/RustboroCity_House1/scripts.pory"
	.byte 0
# 5 "data/maps/RustboroCity_House1/scripts.pory"

# 6 "data/maps/RustboroCity_House1/scripts.pory"
RustboroCity_House1_EventScript_Trader_Logic::
# 7 "data/maps/RustboroCity_House1/scripts.pory"
	goto_if_set FLAG_RUSTBORO_NPC_TRADE_COMPLETED, RustboroCity_House1_EventScript_TradeCompleted
# 8 "data/maps/RustboroCity_House1/scripts.pory"
	setvar VAR_0x8008, INGAME_TRADE_SEEDOT
# 9 "data/maps/RustboroCity_House1/scripts.pory"
	copyvar VAR_0x8004, VAR_0x8008
# 10 "data/maps/RustboroCity_House1/scripts.pory"
	specialvar VAR_RESULT, GetInGameTradeSpeciesInfo
# 11 "data/maps/RustboroCity_House1/scripts.pory"
	copyvar VAR_0x8009, VAR_RESULT
# 12 "data/maps/RustboroCity_House1/scripts.pory"
	msgbox RustboroCity_House1_Text_IllTradeIfYouWant, MSGBOX_YESNO
# 13 "data/maps/RustboroCity_House1/scripts.pory"
	goto_if_eq VAR_RESULT, NO, RustboroCity_House1_EventScript_DeclineTrade
# 14 "data/maps/RustboroCity_House1/scripts.pory"
	special ChoosePartyMon
# 15 "data/maps/RustboroCity_House1/scripts.pory"
	waitstate
# 16 "data/maps/RustboroCity_House1/scripts.pory"
	copyvar VAR_0x800A, VAR_0x8004
# 17 "data/maps/RustboroCity_House1/scripts.pory"
	goto_if_eq VAR_0x8004, PARTY_NOTHING_CHOSEN, RustboroCity_House1_EventScript_DeclineTrade
# 18 "data/maps/RustboroCity_House1/scripts.pory"
	copyvar VAR_0x8005, VAR_0x800A
# 19 "data/maps/RustboroCity_House1/scripts.pory"
	specialvar VAR_RESULT, GetTradeSpecies
# 20 "data/maps/RustboroCity_House1/scripts.pory"
	copyvar VAR_0x800B, VAR_RESULT
# 21 "data/maps/RustboroCity_House1/scripts.pory"
	goto_if_ne VAR_RESULT, VAR_0x8009, RustboroCity_House1_EventScript_NotRequestedMon
# 22 "data/maps/RustboroCity_House1/scripts.pory"
	copyvar VAR_0x8004, VAR_0x8008
# 23 "data/maps/RustboroCity_House1/scripts.pory"
	copyvar VAR_0x8005, VAR_0x800A
# 24 "data/maps/RustboroCity_House1/scripts.pory"
	special CreateInGameTradePokemon
# 25 "data/maps/RustboroCity_House1/scripts.pory"
	special DoInGameTradeScene
# 26 "data/maps/RustboroCity_House1/scripts.pory"
	waitstate
# 27 "data/maps/RustboroCity_House1/scripts.pory"
	msgbox RustboroCity_House1_Text_PleaseBeGoodToMyPokemon, MSGBOX_DEFAULT
# 28 "data/maps/RustboroCity_House1/scripts.pory"
	setflag FLAG_RUSTBORO_NPC_TRADE_COMPLETED
# 29 "data/maps/RustboroCity_House1/scripts.pory"
	release
# 30 "data/maps/RustboroCity_House1/scripts.pory"
	end
# 31 "data/maps/RustboroCity_House1/scripts.pory"

# 32 "data/maps/RustboroCity_House1/scripts.pory"
RustboroCity_House1_EventScript_DeclineTrade::
# 33 "data/maps/RustboroCity_House1/scripts.pory"
	msgbox RustboroCity_House1_Text_YouDontWantToThatsOkay, MSGBOX_DEFAULT
# 34 "data/maps/RustboroCity_House1/scripts.pory"
	release
# 35 "data/maps/RustboroCity_House1/scripts.pory"
	end
# 36 "data/maps/RustboroCity_House1/scripts.pory"

# 37 "data/maps/RustboroCity_House1/scripts.pory"
RustboroCity_House1_EventScript_NotRequestedMon::
# 38 "data/maps/RustboroCity_House1/scripts.pory"
	bufferspeciesname STR_VAR_1, VAR_0x8009
# 39 "data/maps/RustboroCity_House1/scripts.pory"
	msgbox RustboroCity_House1_Text_DoesntLookLikeMonToMe, MSGBOX_DEFAULT
# 40 "data/maps/RustboroCity_House1/scripts.pory"
	release
# 41 "data/maps/RustboroCity_House1/scripts.pory"
	end
# 42 "data/maps/RustboroCity_House1/scripts.pory"

# 43 "data/maps/RustboroCity_House1/scripts.pory"
RustboroCity_House1_EventScript_TradeCompleted::
# 44 "data/maps/RustboroCity_House1/scripts.pory"
	msgbox RustboroCity_House1_Text_AnyPokemonCanBeCute, MSGBOX_DEFAULT
# 45 "data/maps/RustboroCity_House1/scripts.pory"
	release
# 46 "data/maps/RustboroCity_House1/scripts.pory"
	end
# 47 "data/maps/RustboroCity_House1/scripts.pory"

# 48 "data/maps/RustboroCity_House1/scripts.pory"
RustboroCity_House1_EventScript_Hiker::
# 49 "data/maps/RustboroCity_House1/scripts.pory"
	msgbox RustboroCity_House1_Text_AllSortsOfPlaces, MSGBOX_NPC
# 50 "data/maps/RustboroCity_House1/scripts.pory"
	end
# 51 "data/maps/RustboroCity_House1/scripts.pory"

# 52 "data/maps/RustboroCity_House1/scripts.pory"
RustboroCity_House1_Text_IllTradeIfYouWant:
# 53 "data/maps/RustboroCity_House1/scripts.pory"
	.string "Huh? My POKéMON is cute?\n"
# 54 "data/maps/RustboroCity_House1/scripts.pory"
	.string "Sure, I knew that.\p"
# 55 "data/maps/RustboroCity_House1/scripts.pory"
	.string "But if you really want, I'm willing\n"
# 56 "data/maps/RustboroCity_House1/scripts.pory"
	.string "to trade it to you.\p"
# 57 "data/maps/RustboroCity_House1/scripts.pory"
	.string "I'll trade you my {STR_VAR_2} for\n"
# 58 "data/maps/RustboroCity_House1/scripts.pory"
	.string "a {STR_VAR_1} if you want.$"
# 59 "data/maps/RustboroCity_House1/scripts.pory"

# 60 "data/maps/RustboroCity_House1/scripts.pory"
RustboroCity_House1_Text_PleaseBeGoodToMyPokemon:
# 61 "data/maps/RustboroCity_House1/scripts.pory"
	.string "Eheheh…\n"
# 62 "data/maps/RustboroCity_House1/scripts.pory"
	.string "Please be good to my POKéMON.$"
# 63 "data/maps/RustboroCity_House1/scripts.pory"

# 64 "data/maps/RustboroCity_House1/scripts.pory"
RustboroCity_House1_Text_DoesntLookLikeMonToMe:
# 65 "data/maps/RustboroCity_House1/scripts.pory"
	.string "Huh? That doesn't look anything like\n"
# 66 "data/maps/RustboroCity_House1/scripts.pory"
	.string "a {STR_VAR_1} to me.$"
# 67 "data/maps/RustboroCity_House1/scripts.pory"

# 68 "data/maps/RustboroCity_House1/scripts.pory"
RustboroCity_House1_Text_YouDontWantToThatsOkay:
# 69 "data/maps/RustboroCity_House1/scripts.pory"
	.string "Oh, if you don't want to, that's okay.\n"
# 70 "data/maps/RustboroCity_House1/scripts.pory"
	.string "But my POKéMON is cute, you know…$"
# 71 "data/maps/RustboroCity_House1/scripts.pory"

# 72 "data/maps/RustboroCity_House1/scripts.pory"
RustboroCity_House1_Text_AnyPokemonCanBeCute:
# 73 "data/maps/RustboroCity_House1/scripts.pory"
	.string "Any POKéMON can be cute if you raise\n"
# 74 "data/maps/RustboroCity_House1/scripts.pory"
	.string "it with care and kindness.$"
# 75 "data/maps/RustboroCity_House1/scripts.pory"

# 76 "data/maps/RustboroCity_House1/scripts.pory"
RustboroCity_House1_Text_AllSortsOfPlaces:
# 77 "data/maps/RustboroCity_House1/scripts.pory"
	.string "In all sorts of places, there are all\n"
# 78 "data/maps/RustboroCity_House1/scripts.pory"
	.string "sorts of POKéMON and people.\p"
# 79 "data/maps/RustboroCity_House1/scripts.pory"
	.string "I find that fascinating, so I go to all\n"
# 80 "data/maps/RustboroCity_House1/scripts.pory"
	.string "sorts of places.$"

RustboroCity_House1_EventScript_Trader::
# 84 "data/maps/RustboroCity_House1/scripts.pory"
	lock
# 85 "data/maps/RustboroCity_House1/scripts.pory"
	faceplayer
# 86 "data/maps/RustboroCity_House1/scripts.pory"
	compare VAR_MONOTYPE, 0
	goto_if_ne RustboroCity_House1_EventScript_Trader_2
# 94 "data/maps/RustboroCity_House1/scripts.pory"
	call RustboroCity_House1_EventScript_Trader_Logic
	return

RustboroCity_House1_EventScript_Trader_2:
# 87 "data/maps/RustboroCity_House1/scripts.pory"
	msgbox RustboroCity_House1_EventScript_Trader_Text_0
# 88 "data/maps/RustboroCity_House1/scripts.pory"
	msgbox RustboroCity_House1_EventScript_Trader_Text_1
# 89 "data/maps/RustboroCity_House1/scripts.pory"
	msgbox RustboroCity_House1_EventScript_Trader_Text_2
# 90 "data/maps/RustboroCity_House1/scripts.pory"
	msgbox RustboroCity_House1_EventScript_Trader_Text_3
# 91 "data/maps/RustboroCity_House1/scripts.pory"
	release
	end


RustboroCity_House1_EventScript_Trader_Text_0:
# 87 "data/maps/RustboroCity_House1/scripts.pory"
	.string "I went looking for a RALTS...$"

RustboroCity_House1_EventScript_Trader_Text_1:
# 88 "data/maps/RustboroCity_House1/scripts.pory"
	.string "But I ended up catching a LOTAD\n"
	.string "instead.$"

RustboroCity_House1_EventScript_Trader_Text_2:
# 89 "data/maps/RustboroCity_House1/scripts.pory"
	.string "I was a little bummed at first...$"

RustboroCity_House1_EventScript_Trader_Text_3:
# 90 "data/maps/RustboroCity_House1/scripts.pory"
	.string "But now LOTAD and I are real pals!$"
