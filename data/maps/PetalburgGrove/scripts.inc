# 1 "data/maps/PetalburgGrove/scripts.pory"

# 2 "data/maps/PetalburgGrove/scripts.pory"
.set LOCALID_WANDERING_WOMAN, 1
# 3 "data/maps/PetalburgGrove/scripts.pory"
PetalburgGrove_MapScripts::
# 4 "data/maps/PetalburgGrove/scripts.pory"
	.byte 0

PetalburgGrove_WanderingWoman::
# 8 "data/maps/PetalburgGrove/scripts.pory"
	lock
# 9 "data/maps/PetalburgGrove/scripts.pory"
	faceplayer
# 10 "data/maps/PetalburgGrove/scripts.pory"
	msgbox PetalburgGrove_WanderingWoman_Text_0
# 11 "data/maps/PetalburgGrove/scripts.pory"
	closemessage
# 12 "data/maps/PetalburgGrove/scripts.pory"
	applymovement LOCALID_WANDERING_WOMAN, Common_Movement_FaceOriginalDirection
# 13 "data/maps/PetalburgGrove/scripts.pory"
	waitmovement 0
# 14 "data/maps/PetalburgGrove/scripts.pory"
	releaseall
	end


PetalburgGrove_WanderingWoman_Text_0:
# 10 "data/maps/PetalburgGrove/scripts.pory"
	.string "This place is so peaceful. I love seeing\n"
	.string "the Pokemon here.$"
