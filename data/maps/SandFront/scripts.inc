# 1 "data/maps/SandFront/scripts.pory"

# 2 "data/maps/SandFront/scripts.pory"
SandFront_MapScripts::
# 3 "data/maps/SandFront/scripts.pory"
	.byte 0

Sandfront_IcyRock_Ruin_Maniac::
# 7 "data/maps/SandFront/scripts.pory"
	lock
# 8 "data/maps/SandFront/scripts.pory"
	faceplayer
# 9 "data/maps/SandFront/scripts.pory"
	msgbox Sandfront_IcyRock_Ruin_Maniac_Text_0
# 10 "data/maps/SandFront/scripts.pory"
	msgbox Sandfront_IcyRock_Ruin_Maniac_Text_1
# 11 "data/maps/SandFront/scripts.pory"
	msgbox Sandfront_IcyRock_Ruin_Maniac_Text_2
# 12 "data/maps/SandFront/scripts.pory"
	release
	end


Sandfront_IcyRock_Ruin_Maniac_Text_0:
# 9 "data/maps/SandFront/scripts.pory"
	.string "The Icy rock that was lying here ...$"

Sandfront_IcyRock_Ruin_Maniac_Text_1:
# 10 "data/maps/SandFront/scripts.pory"
	.string "I wonder if it drifted here from\n"
	.string "somewhere.$"

Sandfront_IcyRock_Ruin_Maniac_Text_2:
# 11 "data/maps/SandFront/scripts.pory"
	.string "There might be something to explore\n"
	.string "around here. But alas, I don't have a\l"
	.string "Surfing Pokemon!$"
