# 1 "data/maps/PetalburgGrove/scripts.pory"

# 2 "data/maps/PetalburgGrove/scripts.pory"
.set LOCALID_WANDERING_WOMAN, 1
# 3 "data/maps/PetalburgGrove/scripts.pory"
.set LOCALID_PETALBURG_GROVE_BIRCH, 3
# 4 "data/maps/PetalburgGrove/scripts.pory"
PetalburgGrove_MapScripts::
# 5 "data/maps/PetalburgGrove/scripts.pory"
	.byte 0

PetalburgGrove_WanderingWoman::
# 9 "data/maps/PetalburgGrove/scripts.pory"
	lock
# 10 "data/maps/PetalburgGrove/scripts.pory"
	faceplayer
# 11 "data/maps/PetalburgGrove/scripts.pory"
	msgbox PetalburgGrove_WanderingWoman_Text_0
# 12 "data/maps/PetalburgGrove/scripts.pory"
	closemessage
# 13 "data/maps/PetalburgGrove/scripts.pory"
	applymovement LOCALID_WANDERING_WOMAN, Common_Movement_FaceOriginalDirection
# 14 "data/maps/PetalburgGrove/scripts.pory"
	waitmovement 0
# 15 "data/maps/PetalburgGrove/scripts.pory"
	releaseall
	end


PetalburgGrove_ProfessorBirch::
# 20 "data/maps/PetalburgGrove/scripts.pory"
	lock
# 21 "data/maps/PetalburgGrove/scripts.pory"
	faceplayer
# 22 "data/maps/PetalburgGrove/scripts.pory"
	msgbox PetalburgGrove_ProfessorBirch_Text_0
# 23 "data/maps/PetalburgGrove/scripts.pory"
	closemessage
# 24 "data/maps/PetalburgGrove/scripts.pory"
	setflag FLAG_HIDE_PETALBURG_GROVE_BIRCH
# 25 "data/maps/PetalburgGrove/scripts.pory"
	removeobject LOCALID_PETALBURG_GROVE_BIRCH
# 26 "data/maps/PetalburgGrove/scripts.pory"
	releaseall
	end


PetalburgGrove_Bulbasaur::
# 31 "data/maps/PetalburgGrove/scripts.pory"
	lock
# 32 "data/maps/PetalburgGrove/scripts.pory"
	faceplayer
# 33 "data/maps/PetalburgGrove/scripts.pory"
	waitse
# 34 "data/maps/PetalburgGrove/scripts.pory"
	playmoncry SPECIES_BULBASAUR, CRY_MODE_NORMAL
# 35 "data/maps/PetalburgGrove/scripts.pory"
	msgbox PetalburgGrove_Bulbasaur_Text_0
# 36 "data/maps/PetalburgGrove/scripts.pory"
	waitmoncry
# 37 "data/maps/PetalburgGrove/scripts.pory"
	release
	end


PetalburgGrove_Chikorita::
# 42 "data/maps/PetalburgGrove/scripts.pory"
	lock
# 43 "data/maps/PetalburgGrove/scripts.pory"
	faceplayer
# 44 "data/maps/PetalburgGrove/scripts.pory"
	waitse
# 45 "data/maps/PetalburgGrove/scripts.pory"
	playmoncry SPECIES_CHIKORITA, CRY_MODE_NORMAL
# 46 "data/maps/PetalburgGrove/scripts.pory"
	msgbox PetalburgGrove_Chikorita_Text_0
# 47 "data/maps/PetalburgGrove/scripts.pory"
	waitmoncry
# 48 "data/maps/PetalburgGrove/scripts.pory"
	release
	end


PetalburgGrove_Vulpix::
# 53 "data/maps/PetalburgGrove/scripts.pory"
	lock
# 54 "data/maps/PetalburgGrove/scripts.pory"
	faceplayer
# 55 "data/maps/PetalburgGrove/scripts.pory"
	waitse
# 56 "data/maps/PetalburgGrove/scripts.pory"
	playmoncry SPECIES_VULPIX, CRY_MODE_NORMAL
# 57 "data/maps/PetalburgGrove/scripts.pory"
	msgbox PetalburgGrove_Vulpix_Text_0
# 58 "data/maps/PetalburgGrove/scripts.pory"
	waitmoncry
# 59 "data/maps/PetalburgGrove/scripts.pory"
	release
	end


PetalburgGrove_WanderingWoman_Text_0:
# 11 "data/maps/PetalburgGrove/scripts.pory"
	.string "This place is so peaceful. I love seeing\n"
	.string "the Pokemon here.$"

PetalburgGrove_ProfessorBirch_Text_0:
# 22 "data/maps/PetalburgGrove/scripts.pory"
	.string "PROF. BIRCH: Oh, {PLAYER}{KUN}!\p"
	.string "Take a look at this grove. Isn't it\n"
	.string "lively?\p"
	.string "VULPIX lives right alongside\n"
	.string "GRASS-type POKéMON like CHIKORITA and\l"
	.string "BULBASAUR.\p"
	.string "I see you've earned your first BADGE,\n"
	.string "too. Congratulations!\p"
	.string "Your next stop is elsewhere, but you\n"
	.string "came here to observe this place anyway.\p"
	.string "That's the spirit! POKéMON are\n"
	.string "everywhere. Habitats like this are full\l"
	.string "of discoveries.\p"
	.string "Well, my field notes are done. I'd better\n"
	.string "get back to the LAB.\p"
	.string "Best of luck on your adventure!$"

PetalburgGrove_Bulbasaur_Text_0:
# 35 "data/maps/PetalburgGrove/scripts.pory"
	.string "BULBASAUR is resting in a cool patch of\n"
	.string "grass.$"

PetalburgGrove_Chikorita_Text_0:
# 46 "data/maps/PetalburgGrove/scripts.pory"
	.string "CHIKORITA sways its leaf towards the\n"
	.string "flowers.$"

PetalburgGrove_Vulpix_Text_0:
# 57 "data/maps/PetalburgGrove/scripts.pory"
	.string "VULPIX is curled up with its tails\n"
	.string "tucked neatly around it.$"
