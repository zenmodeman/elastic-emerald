# 1 "data/maps/DewfordGarden/scripts.pory"

# 2 "data/maps/DewfordGarden/scripts.pory"
DewfordGarden_MapScripts::
# 3 "data/maps/DewfordGarden/scripts.pory"
	.byte 0

DewfordGarden_School_Kid::
# 7 "data/maps/DewfordGarden/scripts.pory"
	lock
# 8 "data/maps/DewfordGarden/scripts.pory"
	faceplayer
# 9 "data/maps/DewfordGarden/scripts.pory"
	msgbox DewfordGarden_School_Kid_Text_0
	end


DewfordGarden_School_Kid_Text_0:
# 9 "data/maps/DewfordGarden/scripts.pory"
	.string "This place is so cool! Flowers, sand, and\n"
	.string "even a pond-it's got everything!$"
