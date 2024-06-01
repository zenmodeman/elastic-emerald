# 1 "data/maps/OldaleRuins/scripts.pory"

# 2 "data/maps/OldaleRuins/scripts.pory"

# 3 "data/maps/OldaleRuins/scripts.pory"
OldaleRuins_MapScripts::
# 4 "data/maps/OldaleRuins/scripts.pory"
	.byte 0

OldaleRuins_EventScript_Maniac::
# 9 "data/maps/OldaleRuins/scripts.pory"
	lock
# 10 "data/maps/OldaleRuins/scripts.pory"
	faceplayer
# 11 "data/maps/OldaleRuins/scripts.pory"
	msgbox OldaleRuins_EventScript_Maniac_Text_0
# 12 "data/maps/OldaleRuins/scripts.pory"
	msgbox OldaleRuins_EventScript_Maniac_Text_1
# 13 "data/maps/OldaleRuins/scripts.pory"
	releaseall
	end


OldaleRuins_EventScript_Maniac_Text_0:
# 11 "data/maps/OldaleRuins/scripts.pory"
	.string "These gems are intriguing. I'm\n"
	.string "fascinated by this place and love to\l"
	.string "visit a lot. There's rumors that there's\l"
	.string "some key out there can unlock a portal\l"
	.string "to an anicent world.$"

OldaleRuins_EventScript_Maniac_Text_1:
# 12 "data/maps/OldaleRuins/scripts.pory"
	.string "Maybe they have something to do with\n"
	.string "gems like these. Then again, there's\l"
	.string "probably no truth behind any of this,\l"
	.string "but it's fun to imagine!$"
