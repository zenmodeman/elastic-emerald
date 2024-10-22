# 1 "data/maps/OldaleTown_TechHouse/scripts.pory"

# 2 "data/maps/OldaleTown_TechHouse/scripts.pory"
OldaleTown_TechHouse_MapScripts::
# 3 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.byte 0

OldaleTown_TechHouse_Master::
# 7 "data/maps/OldaleTown_TechHouse/scripts.pory"
	lock
# 8 "data/maps/OldaleTown_TechHouse/scripts.pory"
	faceplayer
# 9 "data/maps/OldaleTown_TechHouse/scripts.pory"
	goto_if_unset FLAG_TEMP_8, OldaleTown_TechHouse_Master_2
OldaleTown_TechHouse_Master_1:
# 15 "data/maps/OldaleTown_TechHouse/scripts.pory"
	setflag FLAG_TEMP_8
# 16 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Master_Text_4, MSGBOX_YESNO
# 17 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq OldaleTown_TechHouse_Master_5
# 22 "data/maps/OldaleTown_TechHouse/scripts.pory"
	call TechTutorRejected
OldaleTown_TechHouse_Master_4:
# 24 "data/maps/OldaleTown_TechHouse/scripts.pory"
	release
	end

OldaleTown_TechHouse_Master_2:
# 10 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Master_Text_0
# 11 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Master_Text_1
# 12 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Master_Text_2
# 13 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Master_Text_3
	goto OldaleTown_TechHouse_Master_1

OldaleTown_TechHouse_Master_5:
# 18 "data/maps/OldaleTown_TechHouse/scripts.pory"
	call ChooseTechMoveTutorMon
# 19 "data/maps/OldaleTown_TechHouse/scripts.pory"
	waitstate
# 20 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Master_Text_5
	goto OldaleTown_TechHouse_Master_4


OldaleTown_TechHouse_Sport_BugCatcher::
# 29 "data/maps/OldaleTown_TechHouse/scripts.pory"
	lock
# 30 "data/maps/OldaleTown_TechHouse/scripts.pory"
	faceplayer
# 31 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Sport_BugCatcher_Text_0
# 32 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Sport_BugCatcher_Text_1
# 33 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Sport_BugCatcher_Text_2
# 34 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Sport_BugCatcher_Text_3
# 35 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Sport_BugCatcher_Text_4
# 36 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Sport_BugCatcher_Text_5
# 37 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Sport_BugCatcher_Text_6
# 38 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Sport_BugCatcher_Text_7
# 39 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Sport_BugCatcher_Text_8
# 40 "data/maps/OldaleTown_TechHouse/scripts.pory"
	release
	end


OldaleTown_TechHouse_Mist_OldMan::
# 45 "data/maps/OldaleTown_TechHouse/scripts.pory"
	lock
# 46 "data/maps/OldaleTown_TechHouse/scripts.pory"
	faceplayer
# 47 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Mist_OldMan_Text_0
# 48 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Mist_OldMan_Text_1
# 49 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Mist_OldMan_Text_2
# 50 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Mist_OldMan_Text_3
# 51 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Mist_OldMan_Text_4
# 52 "data/maps/OldaleTown_TechHouse/scripts.pory"
	release
	end


OldaleTown_TechHouse_Embargo_Maniac::
# 57 "data/maps/OldaleTown_TechHouse/scripts.pory"
	lock
# 58 "data/maps/OldaleTown_TechHouse/scripts.pory"
	faceplayer
# 59 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Embargo_Maniac_Text_0
# 60 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Embargo_Maniac_Text_1
# 61 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Embargo_Maniac_Text_2
# 62 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Embargo_Maniac_Text_3
# 63 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Embargo_Maniac_Text_4
# 64 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Embargo_Maniac_Text_5
# 65 "data/maps/OldaleTown_TechHouse/scripts.pory"
	release
	end


OldaleTown_TechHouse_WonderRoom_Hiker::
# 70 "data/maps/OldaleTown_TechHouse/scripts.pory"
	lock
# 71 "data/maps/OldaleTown_TechHouse/scripts.pory"
	faceplayer
# 72 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_WonderRoom_Hiker_Text_0
# 73 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_WonderRoom_Hiker_Text_1
# 74 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_WonderRoom_Hiker_Text_2
# 75 "data/maps/OldaleTown_TechHouse/scripts.pory"
	faceplayer
# 76 "data/maps/OldaleTown_TechHouse/scripts.pory"
	release
	end


OldaleTown_TechHouse_Walker::
# 81 "data/maps/OldaleTown_TechHouse/scripts.pory"
	lock
# 82 "data/maps/OldaleTown_TechHouse/scripts.pory"
	faceplayer
# 83 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Walker_Text_0
# 84 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Walker_Text_1
# 85 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Walker_Text_2
# 86 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox OldaleTown_TechHouse_Walker_Text_3
# 87 "data/maps/OldaleTown_TechHouse/scripts.pory"
	release
	end


ChooseTechMoveTutorMon::
# 92 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox ChooseTechMoveTutorMon_Text_0
# 93 "data/maps/OldaleTown_TechHouse/scripts.pory"
	special ChooseMonForCenterMoveTutor
# 94 "data/maps/OldaleTown_TechHouse/scripts.pory"
	waitstate
# 95 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_0x8004, PARTY_NOTHING_CHOSEN
	goto_if_ne ChooseTechMoveTutorMon_2
	return

ChooseTechMoveTutorMon_1:
# 96 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox ChooseTechMoveTutorMon_Text_1
# 97 "data/maps/OldaleTown_TechHouse/scripts.pory"
	setvar VAR_TEMP_9, MOVE_TUTOR_TECH
# 98 "data/maps/OldaleTown_TechHouse/scripts.pory"
	special TeachNPCMoveTutorMove
	return

ChooseTechMoveTutorMon_2:
# 95 "data/maps/OldaleTown_TechHouse/scripts.pory"
	compare VAR_0x8005, 0
	goto_if_ne ChooseTechMoveTutorMon_1
	return


TechTutorRejected::
# 103 "data/maps/OldaleTown_TechHouse/scripts.pory"
	msgbox TechTutorRejected_Text_0
	return


OldaleTown_TechHouse_Master_Text_0:
# 10 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Welcome! I'm known around here as the\n"
	.string "Tech Sage!$"

OldaleTown_TechHouse_Master_Text_1:
# 11 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "You see, while most folks focus on the\n"
	.string "obvious strengths and weaknesses of\l"
	.string "Pokémon battles, I find beauty in the\l"
	.string "overlooked.$"

OldaleTown_TechHouse_Master_Text_2:
# 12 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Moves like Embargo, Gastro Acid, and\n"
	.string "Heal Block - people never think about\l"
	.string "these gems, but I do!$"

OldaleTown_TechHouse_Master_Text_3:
# 13 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "If you want to learn them, I'll teach\n"
	.string "you for no charge!$"

OldaleTown_TechHouse_Master_Text_4:
# 16 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Would you like to learn some niche\n"
	.string "moves?$"

OldaleTown_TechHouse_Master_Text_5:
# 20 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Come back anytime you want to learn a\n"
	.string "move!$"

OldaleTown_TechHouse_Sport_BugCatcher_Text_0:
# 31 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "As a bug catcher, my Beautifly,\n"
	.string "Masquerain, and Ninjask get dismissed\l"
	.string "for their Fire and Electric weaknesses\l"
	.string "a lot.$"

OldaleTown_TechHouse_Sport_BugCatcher_Text_1:
# 32 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "But I've got a strategy for that. You\n"
	.string "see, my Masquerain knows Water Sport\l"
	.string "and Mud Sport!$"

OldaleTown_TechHouse_Sport_BugCatcher_Text_2:
# 33 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Masquerain isn't a fan of Rain, but\n"
	.string "Water Sport deters Fire moves even\l"
	.string "better than Rain Dance does!$"

OldaleTown_TechHouse_Sport_BugCatcher_Text_3:
# 34 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "And unlike Rain Dance, Water Sport\n"
	.string "keeps my bugs safe from burn, even when\l"
	.string "facing the hottest Fire moves.$"

OldaleTown_TechHouse_Sport_BugCatcher_Text_4:
# 35 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "There's no feeling better than making\n"
	.string "Flamethrowers weaker than Embers!$"

OldaleTown_TechHouse_Sport_BugCatcher_Text_5:
# 36 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "And with Mud Sport, Electric attacks\n"
	.string "don't just lose power - they also can't\l"
	.string "paralyze.$"

OldaleTown_TechHouse_Sport_BugCatcher_Text_6:
# 37 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "That means my Bug-types can take a\n"
	.string "Thunderbolt without worrying about\l"
	.string "getting slowed down!$"

OldaleTown_TechHouse_Sport_BugCatcher_Text_7:
# 38 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "If you're interested in this strategy\n"
	.string "yourself, grab a Damp Rock and Smooth\l"
	.string "Rock. They'll help these moves last\l"
	.string "longer.$"

OldaleTown_TechHouse_Sport_BugCatcher_Text_8:
# 39 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "When you've got a team of bugs, you\n"
	.string "need all the time you can get!$"

OldaleTown_TechHouse_Mist_OldMan_Text_0:
# 47 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Ah, Mist... Now that's a move with\n"
	.string "history.$"

OldaleTown_TechHouse_Mist_OldMan_Text_1:
# 48 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Back in the day, my Milotic's Mist\n"
	.string "shielded me from so many Intimidates,\l"
	.string "Snarls, and especially Parting Shots in\l"
	.string "tournament battles!$"

OldaleTown_TechHouse_Mist_OldMan_Text_2:
# 49 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "And with an Icy Rock, I could keep that\n"
	.string "Mist up for most of a Double Battle!$"

OldaleTown_TechHouse_Mist_OldMan_Text_3:
# 50 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "But now with all this new technology,\n"
	.string "like the Clear Amulet, I suppose not\l"
	.string "many trainers see the need for Mist\l"
	.string "anymore.$"

OldaleTown_TechHouse_Mist_OldMan_Text_4:
# 51 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Sure, the Clear Amulet is much easier to\n"
	.string "use, but there's something so\l"
	.string "satisfying about setting up your own\l"
	.string "protective Mist, don't you think?$"

OldaleTown_TechHouse_Embargo_Maniac_Text_0:
# 59 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "I've got a fellow collector friend who's\n"
	.string "a big chance freak. You might even bump\l"
	.string "into him on your journey.$"

OldaleTown_TechHouse_Embargo_Maniac_Text_1:
# 60 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "He's obsessed with held items that rely\n"
	.string "on lucky chances, like Focus Band and\l"
	.string "Starf Berry.$"

OldaleTown_TechHouse_Embargo_Maniac_Text_2:
# 61 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "And he only collects Pokemon with the\n"
	.string "ability Sticky Hold, to avoid\l"
	.string "counterplay like Knock Off, Trick, and\l"
	.string "Corrosive Gas.$"

OldaleTown_TechHouse_Embargo_Maniac_Text_3:
# 62 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "But... I’ve found plenty of ways to mess\n"
	.string "up his plan, hehe.$"

OldaleTown_TechHouse_Embargo_Maniac_Text_4:
# 63 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Sure, there’s the obvious stuff like\n"
	.string "Neutralizing Gas or Mold Breaker, which\l"
	.string "he knew about but was hoping people\l"
	.string "wouldn't use on him.$"

OldaleTown_TechHouse_Embargo_Maniac_Text_5:
# 64 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "But he never saw Embargo or Magic Room\n"
	.string "coming! Sticky Hold can't protect him\l"
	.string "from those, what a rookie!$"

OldaleTown_TechHouse_WonderRoom_Hiker_Text_0:
# 72 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "My Rock-types are tough as boulders\n"
	.string "when it comes to physical hits, but\l"
	.string "Special Attacks? That's where they\l"
	.string "crumble.$"

OldaleTown_TechHouse_WonderRoom_Hiker_Text_1:
# 73 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "But with my Stonjourner using Wonder\n"
	.string "Room, I can flip the script and swap\l"
	.string "their defenses!$"

OldaleTown_TechHouse_WonderRoom_Hiker_Text_2:
# 74 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "That way, even my Rocks can take on\n"
	.string "those tricky Special Attackers without\l"
	.string "breaking a sweat!$"

OldaleTown_TechHouse_Walker_Text_0:
# 83 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Hey there! If you're into niche\n"
	.string "strategies, you've come to the right\l"
	.string "place!$"

OldaleTown_TechHouse_Walker_Text_1:
# 84 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "I’m not as dedicated as the rest of the\n"
	.string "folks here, but I love listening to their\l"
	.string "ideas.$"

OldaleTown_TechHouse_Walker_Text_2:
# 85 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Our leader's known as the Tech Master.\n"
	.string "He's spent decades perfecting moves\l"
	.string "most people wouldn’t even consider.$"

OldaleTown_TechHouse_Walker_Text_3:
# 86 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "You gotta respect that kind of\n"
	.string "dedication.$"

ChooseTechMoveTutorMon_Text_0:
# 92 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Select pokemon to teach.$"

ChooseTechMoveTutorMon_Text_1:
# 96 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Teach Which Move?$"

TechTutorRejected_Text_0:
# 103 "data/maps/OldaleTown_TechHouse/scripts.pory"
	.string "Too bad, but come back if you change\n"
	.string "your mind!$"
