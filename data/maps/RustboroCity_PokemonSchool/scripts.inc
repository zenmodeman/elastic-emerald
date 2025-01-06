# 1 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 2 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
.set LOCALID_RIVAL, 7
# 3 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
.set LOCALID_TEACHER, 5
# 4 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
.set LOCALID_ROXANNE, 8
# 5 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 6 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_MapScripts::
# 7 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, TrainerSchoolTransition
# 8 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.byte 0
# 9 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 10 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_Blackboard::
# 11 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	lockall
# 12 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_Text_BlackboardListsStatusChanges, MSGBOX_DEFAULT
# 13 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
# 14 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 15 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 16 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic::
# 17 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	message RustboroCity_PokemonSchool_Text_ReadWhichTopic
# 18 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmessage
# 19 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	multichoicegrid 8, 1, MULTI_STATUS_INFO, 3, FALSE
# 20 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	switch VAR_RESULT
# 21 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	case 0, RustboroCity_PokemonSchool_EventScript_Poison
# 22 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	case 1, RustboroCity_PokemonSchool_EventScript_Paralysis
# 23 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	case 2, RustboroCity_PokemonSchool_EventScript_Sleep
# 24 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	case 3, RustboroCity_PokemonSchool_EventScript_Burn
# 25 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	case 4, RustboroCity_PokemonSchool_EventScript_Freeze
# 26 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	case 5, RustboroCity_PokemonSchool_EventScript_ExitTopicSelect
# 27 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	case MULTI_B_PRESSED, RustboroCity_PokemonSchool_EventScript_ExitTopicSelect
# 28 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 29 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 30 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_Poison::
# 31 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_Text_ExplainPoison, MSGBOX_DEFAULT
# 32 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
# 33 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 34 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 35 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_Paralysis::
# 36 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_Text_ExplainParalysis, MSGBOX_DEFAULT
# 37 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
# 38 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 39 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 40 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_Sleep::
# 41 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_Text_ExplainSleep, MSGBOX_DEFAULT
# 42 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
# 43 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 44 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 45 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_Burn::
# 46 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_Text_ExplainBurn, MSGBOX_DEFAULT
# 47 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
# 48 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 49 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 50 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_Freeze::
# 51 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_Text_ExplainFreeze, MSGBOX_DEFAULT
# 52 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	goto RustboroCity_PokemonSchool_EventScript_ChooseBlackboardTopic
# 53 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 54 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 55 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_ExitTopicSelect::
# 56 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	releaseall
# 57 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 58 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 59 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_GameboyKid1::
# 60 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_Text_TradingRightNow, MSGBOX_NPC
# 61 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 62 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 63 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_GameboyKid2::
# 64 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_Text_AlwaysWantedSeedot, MSGBOX_NPC
# 65 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 66 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 67 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_RichBoy::
# 68 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_Text_PokemontCantUseManMadeItems, MSGBOX_NPC
# 69 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 70 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 71 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_Lass::
# 72 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_Text_ConfusedPokemonAttacksItself, MSGBOX_NPC
# 73 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 74 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 75 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_SchoolKidM::
# 76 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_Text_PokemonHealItselfWithBerry, MSGBOX_NPC
# 77 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 78 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 79 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_StudentNotebook::
# 80 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_Text_StudentsNotes, MSGBOX_SIGN
# 81 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 82 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 83 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_Teacher::
# 84 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	lock
# 85 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	faceplayer
# 86 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	goto_if_set FLAG_RECEIVED_QUICK_CLAW, RustboroCity_PokemonSchool_EventScript_GaveQuickClaw
# 87 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call_if_eq VAR_FACING, DIR_EAST, RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsEast
# 88 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call_if_eq VAR_FACING, DIR_WEST, RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsWest
# 89 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw, MSGBOX_DEFAULT
# 90 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	giveitem ITEM_QUICK_CLAW
# 91 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
# 92 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	closemessage
# 93 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
# 94 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement 0
# 95 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	setflag FLAG_RECEIVED_QUICK_CLAW
# 96 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	release
# 97 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 98 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 99 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsEast::
# 100 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement VAR_LAST_TALKED, RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsEast
# 101 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement 0
# 102 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	return
# 103 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 104 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_TeacherCheckOnStudentsWest::
# 105 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement VAR_LAST_TALKED, RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsWest
# 106 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement 0
# 107 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	return
# 108 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 109 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_GaveQuickClaw::
# 110 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_Text_ExplainQuickClaw, MSGBOX_DEFAULT
# 111 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	closemessage
# 112 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
# 113 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement 0
# 114 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	release
# 115 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 116 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 117 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsWest:
# 118 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_left
# 119 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_down
# 120 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_down
# 121 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 122 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_in_place_faster_down
# 123 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	delay_16
# 124 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	delay_16
# 125 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	delay_16
# 126 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_down
# 127 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_in_place_faster_left
# 128 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	delay_16
# 129 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	delay_16
# 130 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 131 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	delay_16
# 132 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	delay_16
# 133 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	delay_8
# 134 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 135 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_left
# 136 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_left
# 137 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 138 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 139 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 140 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	step_end
# 141 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 142 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Movement_TeacherCheckOnStudentsEast:
# 143 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 144 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 145 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_down
# 146 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_down
# 147 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_left
# 148 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_left
# 149 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_in_place_faster_down
# 150 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	delay_16
# 151 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	delay_16
# 152 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	delay_16
# 153 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_down
# 154 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_in_place_faster_left
# 155 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	delay_16
# 156 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	delay_16
# 157 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 158 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	delay_16
# 159 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	delay_16
# 160 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	delay_8
# 161 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 162 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 163 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 164 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 165 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_left
# 166 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_left
# 167 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	step_end
# 168 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 169 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_Scott::
# 170 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	lock
# 171 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	faceplayer
# 172 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	goto_if_set FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE, RustboroCity_PokemonSchool_EventScript_ScottWatchStudents
# 173 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	goto_if_set FLAG_MET_SCOTT_RUSTBORO, RustboroCity_PokemonSchool_EventScript_ScottSpokeAlready
# 174 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	goto_if_set FLAG_BADGE01_GET, RustboroCity_PokemonSchool_EventScript_ScottGreetHasBadge
# 175 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_Text_ScottMetAlreadyCut, MSGBOX_DEFAULT
# 176 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	addvar VAR_SCOTT_STATE, 1
# 177 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	setflag FLAG_MET_SCOTT_RUSTBORO
# 178 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	release
# 179 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 180 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 181 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_ScottSpokeAlready::
# 182 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	goto_if_set FLAG_BADGE01_GET, RustboroCity_PokemonSchool_EventScript_ScottNoticeBadge
# 183 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown, MSGBOX_DEFAULT
# 184 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	release
# 185 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 186 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 187 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_ScottGreetHasBadge::
# 188 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_Text_ScottMetAlreadyStoneBadge, MSGBOX_DEFAULT
# 189 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	goto RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge
# 190 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 191 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 192 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_ScottNoticeBadge::
# 193 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_Text_ScottStoneBadge, MSGBOX_DEFAULT
# 194 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	goto RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge
# 195 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 196 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 197 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_MetScottAfterBadge::
# 198 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	addvar VAR_SCOTT_STATE, 1
# 199 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	setflag FLAG_MET_SCOTT_AFTER_OBTAINING_STONE_BADGE
# 200 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	release
# 201 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 202 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 203 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_EventScript_ScottWatchStudents::
# 204 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown, MSGBOX_DEFAULT
# 205 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	release
# 206 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	end
# 207 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 208 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Text_BlackboardListsStatusChanges:
# 209 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "The blackboard lists status changes\n"
# 210 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "that may affect POKéMON in battle.$"
# 211 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 212 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Text_ReadWhichTopic:
# 213 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Which topic do you want to read?$"
# 214 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 215 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Text_ExplainPoison:
# 216 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "If a POKéMON is poisoned, it will\n"
# 217 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "steadily lose HP.\p"
# 218 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "The effects of poison remain after\n"
# 219 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "a battle.\p"
# 220 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "A poisoned POKéMON's HP will drop\n"
# 221 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "while it is traveling.\p"
# 222 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Heal a poisoning using an ANTIDOTE.$"
# 223 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 224 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Text_ExplainParalysis:
# 225 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "If a POKéMON becomes paralyzed,\n"
# 226 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "its SPEED drops.\p"
# 227 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "It may also not be able to move while\n"
# 228 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "it is in battle.\p"
# 229 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Paralysis remains after battle.\n"
# 230 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Cure it using a PARLYZ HEAL.$"
# 231 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 232 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Text_ExplainSleep:
# 233 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "If a POKéMON falls asleep, it will be\n"
# 234 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "unable to attack.\p"
# 235 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "A POKéMON may wake up on its own,\n"
# 236 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "but if a battle ends while it is\l"
# 237 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "sleeping, it will stay asleep.\p"
# 238 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Wake it up using an AWAKENING.$"
# 239 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 240 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Text_ExplainBurn:
# 241 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "A burn reduces ATTACK power, and it\n"
# 242 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "steadily reduces the victim's HP.\p"
# 243 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "A burn lingers after battle.\n"
# 244 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Cure a burn using a BURN HEAL.$"
# 245 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 246 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Text_ExplainFreeze:
# 247 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "If a POKéMON is frozen, it becomes\n"
# 248 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "completely helpless.\p"
# 249 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "It will remain frozen after battle.\n"
# 250 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Thaw it out using an ICE HEAL.$"
# 251 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 252 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Text_StudentsWhoDontStudyGetQuickClaw:
# 253 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Students who don't study get a little\n"
# 254 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "taste of my QUICK CLAW.\p"
# 255 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Whether or not you are a good student \n"
# 256 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "will be evident from the way you use\l"
# 257 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "this item.$"
# 258 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 259 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Text_ExplainQuickClaw:
# 260 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "A POKéMON holding the QUICK CLAW will\n"
# 261 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "occasionally speed up and get to move\l"
# 262 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "before its opponent.\p"
# 263 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "There are many other items that are\n"
# 264 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "meant to be held by POKéMON.\p"
# 265 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Just those alone will give you many\n"
# 266 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "topics to study!$"
# 267 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 268 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Text_TradingRightNow:
# 269 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "I'm trading POKéMON with my friend\n"
# 270 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "right now.$"
# 271 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 272 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Text_AlwaysWantedSeedot:
# 273 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "I always wanted a SEEDOT, and\n"
# 274 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "I'm finally getting one!$"
# 275 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 276 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Text_PokemontCantUseManMadeItems:
# 277 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "POKéMON can hold items, but they\n"
# 278 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "don't know what to do with man-made\l"
# 279 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "items like POTION and ANTIDOTE.$"
# 280 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 281 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Text_ConfusedPokemonAttacksItself:
# 282 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "You know how some POKéMON moves can\n"
# 283 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "confuse a POKéMON?\p"
# 284 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "A confused POKéMON will sometimes\n"
# 285 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "attack itself without meaning to.\p"
# 286 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "But once it leaves battle, it will\n"
# 287 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "return to normal.$"
# 288 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 289 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Text_PokemonHealItselfWithBerry:
# 290 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "A POKéMON holding a BERRY will heal\n"
# 291 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "itself…\p"
# 292 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "There are many kinds of items that\n"
# 293 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "POKéMON can hold…\p"
# 294 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Boy, it sure is hard taking notes\n"
# 295 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "down…$"
# 296 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 297 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Text_StudentsNotes:
# 298 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "It's this student's notebook…\p"
# 299 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "POKéMON are to be caught using\n"
# 300 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "POKé BALLS.\p"
# 301 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Up to six POKéMON can accompany\n"
# 302 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "a TRAINER.\p"
# 303 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "A TRAINER is someone who catches\n"
# 304 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "POKéMON, raises them, and battles\l"
# 305 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "with them.\p"
# 306 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "A TRAINER's mission is to defeat\n"
# 307 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "the strong TRAINERS who await\l"
# 308 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "challengers in POKéMON GYMS.$"
# 309 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 310 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Text_ScottMetAlreadyCut:
# 311 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Hello? Didn't we meet before?\n"
# 312 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "I think back in PETALBURG CITY.\p"
# 313 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Let me introduce myself.\n"
# 314 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "My name's SCOTT.\p"
# 315 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "I've been traveling everywhere in\n"
# 316 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "search of outstanding TRAINERS.\p"
# 317 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "More specifically, I'm looking for\n"
# 318 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "POKéMON battle experts.\p"
# 319 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "So, what brings you to this SCHOOL?\n"
# 320 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Are you a TRAINER, too?\p"
# 321 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "The first thing you should do is to\n"
# 322 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "have a POKéMON learn the move CUT.\p"
# 323 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "If I remember correctly, someone in\n"
# 324 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "this town has CUT.$"
# 325 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 326 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Text_StudentTalentLevelUnknown:
# 327 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "SCOTT: Hmm…\p"
# 328 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "The talent levels of the students here\n"
# 329 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "are unknown. The potential's there.$"
# 330 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 331 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Text_ScottStoneBadge:
# 332 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "SCOTT: Oh, what's that?\p"
# 333 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "It's a STONE BADGE, isn't it?\n"
# 334 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "That's pretty impressive, I'd say.\p"
# 335 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "But, you know, I would've loved to see\n"
# 336 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "you in battle.\p"
# 337 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "It's hard to tell what you're like as\n"
# 338 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "a TRAINER from a LEAGUE BADGE.$"
# 339 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 340 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RustboroCity_PokemonSchool_Text_ScottMetAlreadyStoneBadge:
# 341 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Hello? Didn't we meet before?\n"
# 342 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "I think back in PETALBURG CITY.\p"
# 343 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Let me introduce myself.\n"
# 344 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "My name's SCOTT.\p"
# 345 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "I've been traveling everywhere in\n"
# 346 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "search of outstanding TRAINERS.\p"
# 347 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "More specifically, I'm looking for\n"
# 348 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "POKéMON battle experts.\p"
# 349 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Oh, what's that?\n"
# 350 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "It's a STONE BADGE, isn't it?\p"
# 351 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "That's pretty impressive, I'd say, for\n"
# 352 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "a starting TRAINER like yourself.\p"
# 353 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "But, you know, I would've loved to see\n"
# 354 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "you in battle.\p"
# 355 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "It's hard to tell what you're like as\n"
# 356 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "a TRAINER from a LEAGUE BADGE.$"

TrainerSchoolTransition::
# 360 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call Common_EventScript_SetupRivalGfxId
	return


TrainerSchool_Lecture::
# 365 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_TeacherIntro
# 366 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_RoxanneSpeech
# 367 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_RivalInterjection
# 368 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_RoxanneReply
# 369 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_RivalReadyForRoxanneBattle
# 370 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_TeacherFinalRemarks
	return


TrainerSchool_TeacherIntro::
# 376 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement LOCALID_TEACHER, TeacherLecture_MovesTowardsClass
# 377 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement LOCALID_TEACHER
# 378 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_0
# 379 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_1
# 380 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_2
# 381 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement LOCALID_TEACHER, TeacherLecture_Right_And_Face_Down
# 382 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement LOCALID_TEACHER
# 383 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_3
# 384 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_4
# 385 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_5
# 386 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement LOCALID_TEACHER, TeacherLecture_Left_And_Face_Down
# 387 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement LOCALID_TEACHER
# 388 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_6
# 389 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_7
# 390 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_8
# 391 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_9
# 392 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_10
# 393 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement LOCALID_TEACHER, TeacherLecture_MovesAwayFromClass
# 394 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement LOCALID_TEACHER
	return


TrainerSchool_RoxanneSpeech::
# 398 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement LOCALID_ROXANNE, RoxanneLecture_MoveTowardsClass
# 399 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement LOCALID_ROXANNE
# 400 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RoxanneSpeech_Text_0
# 401 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RoxanneSpeech_Text_1
# 402 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RoxanneSpeech_Text_2
# 403 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RoxanneSpeech_Text_3
# 404 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RoxanneSpeech_Text_4
# 405 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RoxanneSpeech_Text_5
# 406 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RoxanneSpeech_Text_6
# 407 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RoxanneSpeech_Text_7
# 408 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RoxanneSpeech_Text_8
# 409 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RoxanneSpeech_Text_9
# 410 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RoxanneSpeech_Text_10
# 411 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RoxanneSpeech_Text_11
# 412 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RoxanneSpeech_Text_12
# 413 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RoxanneSpeech_Text_13
# 414 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RoxanneSpeech_Text_14
# 415 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RoxanneSpeech_Text_15
# 416 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RoxanneSpeech_Text_16
# 417 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RoxanneSpeech_Text_17
# 418 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	playse SE_APPLAUSE
# 419 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitse
	return


TrainerSchool_RivalInterjection::
# 423 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement LOCALID_RIVAL, Common_Movement_FaceLeft
# 424 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement LOCALID_RIVAL
# 425 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RivalInterjection_Text_0
# 426 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RivalInterjection_Text_1
	return


TrainerSchool_RoxanneReply::
# 430 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement LOCALID_ROXANNE, Common_Movement_FaceRight
# 431 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement LOCALID_ROXANNE
# 432 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RoxanneReply_Text_0
# 433 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RoxanneReply_Text_1
	return


TrainerSchool_RivalReadyForRoxanneBattle::
# 438 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RivalReadyForRoxanneBattle_Text_0
# 439 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement LOCALID_RIVAL, RivalLecture_MoveTowardsRoxanne
# 440 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement LOCALID_RIVAL
# 441 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RivalReadyForRoxanneBattle_Text_1, MSGBOX_AUTOCLOSE
# 442 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	special SavePlayerParty
# 443 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	checkplayergender
# 444 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_RESULT, MALE
	goto_if_eq TrainerSchool_RivalReadyForRoxanneBattle_2
# 447 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	ai_vs_ai_battle TRAINER_BRENDAN_TRAINER_SCHOOL, TRAINER_ROXANNE_4, TrainerSchool_RivalReadyForRoxanneBattle_Text_2
TrainerSchool_RivalReadyForRoxanneBattle_1:
# 449 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	clearflag FLAG_AI_AI_BATTLE
# 450 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	special LoadPlayerParty
# 451 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RivalReadyForRoxanneBattle_Text_3
# 452 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RivalReadyForRoxanneBattle_Text_4
# 453 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement LOCALID_ROXANNE, Common_Movement_FaceDown
# 454 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RivalReadyForRoxanneBattle_Text_5
# 455 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RivalReadyForRoxanneBattle_Text_6
# 456 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_RivalReadyForRoxanneBattle_Text_7
	return

TrainerSchool_RivalReadyForRoxanneBattle_2:
# 445 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	ai_vs_ai_battle TRAINER_MAY_TRAINER_SCHOOL, TRAINER_ROXANNE_4, TrainerSchool_RivalReadyForRoxanneBattle_Text_2
	goto TrainerSchool_RivalReadyForRoxanneBattle_1


TrainerSchool_TeacherFinalRemarks::
# 460 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherFinalRemarks_Text_0
# 461 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherFinalRemarks_Text_1
# 462 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherFinalRemarks_Text_2
# 463 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	fadescreen FADE_TO_BLACK
# 464 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	setflag FLAG_HIDE_AFTER_LECTURE
# 465 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	setvar VAR_TRAINER_SCHOOL_STATE, 1
# 466 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	removeobject LOCALID_ROXANNE
# 467 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	removeobject LOCALID_RIVAL
# 468 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	removeobject 9
# 469 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	removeobject 11
# 470 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	removeobject 12
# 471 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	removeobject 14
# 472 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	fadescreen FADE_FROM_BLACK
	return


TrainerSchool_BugCatcher::
# 476 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	lock
# 477 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	faceplayer
# 478 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_BugCatcher_Text_0
# 479 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_BugCatcher_Text_1
# 480 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	release
	return


TrainerSchool_Breeder::
# 484 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	lock
# 485 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	faceplayer
# 486 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	goto_if_set FLAG_RECEIVED_TRAINER_SCHOOL_EGG, TrainerSchool_Breeder_2
# 489 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_MONOTYPE, TYPE_NONE
	goto_if_eq TrainerSchool_Breeder_5
# 489 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_MONOTYPE, TYPE_NORMAL
	goto_if_eq TrainerSchool_Breeder_5
# 489 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_MONOTYPE, TYPE_FAIRY - 1
	goto_if_eq TrainerSchool_Breeder_5
# 489 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_MONOTYPE, TYPE_ELECTRIC - 1
	goto_if_eq TrainerSchool_Breeder_5
# 490 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_MONOTYPE, TYPE_POISON
	goto_if_eq TrainerSchool_Breeder_5
# 490 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_MONOTYPE, TYPE_ICE - 1
	goto_if_eq TrainerSchool_Breeder_5
# 490 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_MONOTYPE, TYPE_PSYCHIC - 1
	goto_if_eq TrainerSchool_Breeder_5
# 505 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_Breeder_Text_1
# 506 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_Breeder_Text_13
TrainerSchool_Breeder_1:
# 509 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	release
	end

TrainerSchool_Breeder_2:
# 487 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_Breeder_Text_0
	goto TrainerSchool_Breeder_1

TrainerSchool_Breeder_5:
# 491 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_Breeder_Text_1
# 492 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_Breeder_Text_2
# 493 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_Breeder_Text_3
# 494 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	dynmultichoice 0, 100, FALSE, 5, 0, DYN_MULTICHOICE_CB_NONE, TrainerSchool_Breeder_Text_4, TrainerSchool_Breeder_Text_5, TrainerSchool_Breeder_Text_6, TrainerSchool_Breeder_Text_7, TrainerSchool_Breeder_Text_8
# 495 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq TrainerSchool_Breeder_20
# 495 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq TrainerSchool_Breeder_20
# 497 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq TrainerSchool_Breeder_21
# 497 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_RESULT, 3
	goto_if_eq TrainerSchool_Breeder_21
# 502 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_Breeder_Text_12
	goto TrainerSchool_Breeder_1

TrainerSchool_Breeder_20:
# 496 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_Breeder_Text_9
	goto TrainerSchool_Breeder_1

TrainerSchool_Breeder_21:
# 498 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_Breeder_Text_10
# 499 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_Breeder_Text_11
# 500 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_GiveEgg
	goto TrainerSchool_Breeder_1


TrainerSchool_GiveEgg::
# 514 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_MONOTYPE, TYPE_NONE
	goto_if_eq TrainerSchool_GiveEgg_1
# 526 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_MONOTYPE, TYPE_NORMAL
	goto_if_eq TrainerSchool_GiveEgg_2
# 526 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_MONOTYPE, TYPE_FAIRY - 1
	goto_if_eq TrainerSchool_GiveEgg_2
# 529 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_MONOTYPE, TYPE_ELECTRIC - 1
	goto_if_eq TrainerSchool_GiveEgg_3
# 529 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_MONOTYPE, TYPE_POISON
	goto_if_eq TrainerSchool_GiveEgg_3
# 532 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_MONOTYPE, TYPE_ICE - 1
	goto_if_eq TrainerSchool_GiveEgg_4
# 532 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_MONOTYPE, TYPE_PSYCHIC - 1
	goto_if_eq TrainerSchool_GiveEgg_4
	return

TrainerSchool_GiveEgg_1:
# 515 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	random 3
# 516 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq TrainerSchool_GiveEgg_15
# 519 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq TrainerSchool_GiveEgg_16
# 522 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_RESULT, 2
	goto_if_eq TrainerSchool_GiveEgg_17
	return

TrainerSchool_GiveEgg_2:
# 527 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	giveegg SPECIES_IGGLYBUFF
# 528 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_ProcessEgg
	return

TrainerSchool_GiveEgg_3:
# 530 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	giveegg SPECIES_TOXEL
# 531 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_ProcessEgg
	return

TrainerSchool_GiveEgg_4:
# 533 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	giveegg SPECIES_SMOOCHUM
# 534 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_ProcessEgg
	return

TrainerSchool_GiveEgg_15:
# 517 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	giveegg SPECIES_IGGLYBUFF
# 518 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_ProcessEgg
	return

TrainerSchool_GiveEgg_16:
# 520 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	giveegg SPECIES_TOXEL
# 521 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_ProcessEgg
	return

TrainerSchool_GiveEgg_17:
# 523 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	giveegg SPECIES_SMOOCHUM
# 524 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_ProcessEgg
	return


TrainerSchool_ProcessEgg::
# 539 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq TrainerSchool_ProcessEgg_1
# 543 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PC
	goto_if_eq TrainerSchool_ProcessEgg_2
# 548 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_ProcessEgg_Text_2
	return

TrainerSchool_ProcessEgg_1:
# 540 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 541 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_ProcessEgg_Text_0
# 542 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	setflag FLAG_RECEIVED_TRAINER_SCHOOL_EGG
	return

TrainerSchool_ProcessEgg_2:
# 544 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 545 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_ProcessEgg_Text_1
# 546 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	setflag FLAG_RECEIVED_TRAINER_SCHOOL_EGG
	return


# 553 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RivalLecture_MoveTowardsRoxanne:
# 554 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_left
# 555 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 556 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 557 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_left
# 558 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_left
# 559 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_left
# 560 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_left
# 561 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_down
# 562 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	face_left
# 563 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	step_end

# 565 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RoxanneLecture_MoveTowardsClass:
# 566 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 567 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_down
# 568 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_down
# 569 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_left
# 570 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	face_down
# 571 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	step_end

# 574 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
TeacherLecture_Right_And_Face_Down:
# 575 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 576 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	face_down
# 577 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	step_end

# 580 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
TeacherLecture_Left_And_Face_Down:
# 581 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_left
# 582 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	face_down
# 583 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	step_end

# 586 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
TeacherLecture_MovesTowardsClass:
# 587 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_left
# 588 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_down
# 589 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_down
# 590 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 591 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	face_down
# 592 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	step_end

# 595 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
TeacherLecture_MovesAwayFromClass:
# 596 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_left
# 597 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 598 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 599 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 600 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	face_down
# 601 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	step_end

TrainerSchool_TriggerLeft::
# 607 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	lockall
# 608 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox ClassStartsMessage
# 609 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, LeftTriggerMovement
# 610 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 611 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_Lecture
# 612 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	releaseall
	end


# 617 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
LeftTriggerMovement:
# 618 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 619 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 620 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 621 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 622 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 623 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 624 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 625 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 626 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 627 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 628 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 629 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 630 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	face_up
# 631 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	step_end

TrainerSchool_TriggerUp::
# 635 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	lockall
# 636 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox ClassStartsMessage
# 637 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, UpTriggerMovement
# 638 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 639 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_Lecture
# 640 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	releaseall
	end


# 644 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
UpTriggerMovement:
# 645 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 646 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 647 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 648 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 649 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 650 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 651 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 652 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 653 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 654 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 655 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	face_up
# 656 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	step_end

TrainerSchool_TriggerUpRight::
# 660 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	lockall
# 661 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox ClassStartsMessage
# 662 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, UpRightTriggerMovement
# 663 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 664 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_Lecture
# 665 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	releaseall
	end


# 669 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
UpRightTriggerMovement:
# 670 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 671 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 672 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 673 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 674 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 675 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 676 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 677 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 678 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 679 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	face_up
# 680 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	step_end

TrainerSchool_TriggerRight::
# 685 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	lockall
# 686 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	face_up
# 687 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox ClassStartsMessage
# 688 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, RightTriggerMovement
# 689 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 690 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_Lecture
# 691 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	releaseall
	end


# 695 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RightTriggerMovement:
# 696 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 697 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 698 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 699 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 700 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 701 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 702 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 703 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 704 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 705 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	face_up
# 706 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	step_end

TrainerSchool_TeacherIntro_Text_0:
# 378 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Good morning, class! Today, we have a\n"
	.string "special guest joining us - Roxanne!$"

TrainerSchool_TeacherIntro_Text_1:
# 379 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "You know her as our city's Gym Leader,\n"
	.string "but some of you remember her as one of\l"
	.string "our star pupils!$"

TrainerSchool_TeacherIntro_Text_2:
# 380 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "She's here to share her insider\n"
	.string "perspective on today's topic.$"

TrainerSchool_TeacherIntro_Text_3:
# 383 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Our lesson today is about the Terastal\n"
	.string "phenomenon, first discovered in the\l"
	.string "Paldea region.$"

TrainerSchool_TeacherIntro_Text_4:
# 384 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Thanks to advances in Tera Orbs,\n"
	.string "trainers worldwide can now use this\l"
	.string "incredible technique.$"

TrainerSchool_TeacherIntro_Text_5:
# 385 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "While Tera Orbs are still pricey to\n"
	.string "produce, our own Devon Corp is working\l"
	.string "hard to make them available to more\l"
	.string "trainers!$"

TrainerSchool_TeacherIntro_Text_6:
# 388 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Terastalization has revolutionized\n"
	.string "Pokemon battles.$"

TrainerSchool_TeacherIntro_Text_7:
# 389 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "It opens up new strategies and brings\n"
	.string "out unexpected strengths in every\l"
	.string "Pokemon.$"

TrainerSchool_TeacherIntro_Text_8:
# 390 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Naturally, Hoenn's Gym Leaders - our\n"
	.string "region's Type Experts,$"

TrainerSchool_TeacherIntro_Text_9:
# 391 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "were among the first to receive Tera\n"
	.string "Orbs.$"

TrainerSchool_TeacherIntro_Text_10:
# 392 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "And now, let's hear from Roxanne, who'll\n"
	.string "share what Terastalization means to\l"
	.string "her!$"

TrainerSchool_RoxanneSpeech_Text_0:
# 400 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Thank you for having me here today.\n"
	.string "It's an honor to speak with the next\l"
	.string "generation of Hoenn's finest trainers.$"

TrainerSchool_RoxanneSpeech_Text_1:
# 401 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Terastalization is a fascinating\n"
	.string "phenomenon, one that initially\l"
	.string "challenged my perspective.$"

TrainerSchool_RoxanneSpeech_Text_2:
# 402 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "As many of you know, I have a deep\n"
	.string "admiration for Rocks and Rock-type\l"
	.string "Pokemon.$"

TrainerSchool_RoxanneSpeech_Text_3:
# 403 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "To me, Rock Pokemon represent\n"
	.string "resilience, stability, and timeless\l"
	.string "beauty. Their legacy is as enduring as\l"
	.string "the earth itself.$"

TrainerSchool_RoxanneSpeech_Text_4:
# 404 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "When I was younger, seeing a Geodude\n"
	.string "use Rock Polish for the first time\l"
	.string "inspired me to study harder.$"

TrainerSchool_RoxanneSpeech_Text_5:
# 405 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "When I was learning, it felt as though I\n"
	.string "was polishing myself into a gem, just\l"
	.string "like my beloved Rock-types.$"

TrainerSchool_RoxanneSpeech_Text_6:
# 406 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Rocks have always held a special place\n"
	.string "in my heart, their beauty as timeless\l"
	.string "and awe-inspiring as the stars in the\l"
	.string "night sky.$"

TrainerSchool_RoxanneSpeech_Text_7:
# 407 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "So, when I first saw non-Rock Pokemon\n"
	.string "Terastalizing into Rock-types, I felt\l"
	.string "conflicted.$"

TrainerSchool_RoxanneSpeech_Text_8:
# 408 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "I worried it might diminish what made\n"
	.string "Rock-types special.$"

TrainerSchool_RoxanneSpeech_Text_9:
# 409 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "But then I met a Runerigus and her\n"
	.string "daughter - Galarian Yamask - while\l"
	.string "exploring an ancient ruins.$"

TrainerSchool_RoxanneSpeech_Text_10:
# 410 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Runerigus captivated me, with her\n"
	.string "rune-carved form exuding the same\l"
	.string "elegance and durability I cherish in\l"
	.string "Rock Pokemon.$"

TrainerSchool_RoxanneSpeech_Text_11:
# 411 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Though she wasn't a Rock-type, she\n"
	.string "resonated with me in a way that felt\l"
	.string "deeply familiar.$"

TrainerSchool_RoxanneSpeech_Text_12:
# 412 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "The first time she Terastalized into a\n"
	.string "Rock-type, it was breathtaking.$"

TrainerSchool_RoxanneSpeech_Text_13:
# 413 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "She embodied the rugged beauty and\n"
	.string "unyielding strength of stone, as if she\l"
	.string "had been one all along.$"

TrainerSchool_RoxanneSpeech_Text_14:
# 414 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "To those who, like me, are devoted to\n"
	.string "one Type, I encourage you to embrace\l"
	.string "the possibilities Terastalization\l"
	.string "offers.$"

TrainerSchool_RoxanneSpeech_Text_15:
# 415 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Your beloved Type can find new\n"
	.string "expressions through Terastalization,\l"
	.string "revealing forms and qualities you may\l"
	.string "come to cherish just as much.$"

TrainerSchool_RoxanneSpeech_Text_16:
# 416 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "And to those of you who might challenge\n"
	.string "my gym in the future -$"

TrainerSchool_RoxanneSpeech_Text_17:
# 417 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "My Yamask and Runerigus will shine like\n"
	.string "the finest gemstones, and I look\l"
	.string "forward to sharing that brilliance with\l"
	.string "you!$"

TrainerSchool_RivalInterjection_Text_0:
# 425 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "{RIVAL}: Hmm, that's an interesting\n"
	.string "speech, but I think it'd be nice if we\l"
	.string "got to see Terastalization in action.$"

TrainerSchool_RivalInterjection_Text_1:
# 426 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "I'd like you have a fight if you wouldn't\n"
	.string "mind.$"

TrainerSchool_RoxanneReply_Text_0:
# 432 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Roxanne: Ah that boldness, you\n"
	.string "definitely take after Birch.$"

TrainerSchool_RoxanneReply_Text_1:
# 433 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Sure, I'm down for a quick one-on-one\n"
	.string "demonstration. It'd be a good lesson\l"
	.string "for the class too.$"

TrainerSchool_RivalReadyForRoxanneBattle_Text_0:
# 438 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "{RIVAL}: Great!$"

TrainerSchool_RivalReadyForRoxanneBattle_Text_1:
# 441 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "I can't wait to see what Tera is like.$"

TrainerSchool_RivalReadyForRoxanneBattle_Text_2:
# 445 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "The battle has concluded!$"

TrainerSchool_RivalReadyForRoxanneBattle_Text_3:
# 451 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "{RIVAL}: Wow, I had the type\n"
	.string "advantage but I completely lost!$"

TrainerSchool_RivalReadyForRoxanneBattle_Text_4:
# 452 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Roxanne: My Yamask shines brilliantly\n"
	.string "when she becomes Rock-type!$"

TrainerSchool_RivalReadyForRoxanneBattle_Text_5:
# 454 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Roxanne: Did you see class? When\n"
	.string "Yamask becomes Rock-type, her move\l"
	.string "Curse takes a whole new form.$"

TrainerSchool_RivalReadyForRoxanneBattle_Text_6:
# 455 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "With it, she sharpens both her defense\n"
	.string "and offense like a Rock-type would!$"

TrainerSchool_RivalReadyForRoxanneBattle_Text_7:
# 456 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "{RIVAL}: Fascinating indeed, I can\n"
	.string "see how Yamask becomes more flexible\l"
	.string "with Tera. Now I'm excited for the\l"
	.string "Terastal era!$"

TrainerSchool_TeacherFinalRemarks_Text_0:
# 460 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Teacher: Well, unexpected as that fight\n"
	.string "was, it sure made for an interesting\l"
	.string "learning experience.$"

TrainerSchool_TeacherFinalRemarks_Text_1:
# 461 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Thank you Roxanne and {RIVAL}.$"

TrainerSchool_TeacherFinalRemarks_Text_2:
# 462 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Our time is up, so class is dismissed. I\n"
	.string "hope to see you all again for the next\l"
	.string "lesson!$"

TrainerSchool_BugCatcher_Text_0:
# 478 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Roxanne's speech was inspiring!$"

TrainerSchool_BugCatcher_Text_1:
# 479 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "I can't help but wonder - what Pokemon\n"
	.string "would be the most fascinating to\l"
	.string "Terastalize into Bug-types?$"

TrainerSchool_Breeder_Text_0:
# 487 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Please take good care of the egg.$"

TrainerSchool_Breeder_Text_1:
# 491 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "I love breeding Pokemon, but hatching\n"
	.string "eggs can be so time-consuming.$"

TrainerSchool_Breeder_Text_2:
# 492 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "I wonder if there are any ways to help\n"
	.string "hatch them faster.$"

TrainerSchool_Breeder_Text_3:
# 493 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Do you have any ideas?$"

TrainerSchool_Breeder_Text_4:
# 494 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Aroma Veil$"

TrainerSchool_Breeder_Text_5:
# 494 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Flame Body$"

TrainerSchool_Breeder_Text_6:
# 494 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Lucky Chant$"

TrainerSchool_Breeder_Text_7:
# 494 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Magma Armor$"

TrainerSchool_Breeder_Text_8:
# 494 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "No Idea$"

TrainerSchool_Breeder_Text_9:
# 496 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Hmm, I don't think those would help.$"

TrainerSchool_Breeder_Text_10:
# 498 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Oh, I think I've vaguely heard of that\n"
	.string "somewhere before. It might be right!$"

TrainerSchool_Breeder_Text_11:
# 499 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "As thanks, here, have one of my eggs.$"

TrainerSchool_Breeder_Text_12:
# 502 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Oh, too bad you weren't able to help...$"

TrainerSchool_Breeder_Text_13:
# 506 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "If only there was a way to help hatch\n"
	.string "them faster.$"

TrainerSchool_ProcessEgg_Text_0:
# 541 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "The egg was added to your party!$"

TrainerSchool_ProcessEgg_Text_1:
# 545 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "The egg was added to your PC!$"

TrainerSchool_ProcessEgg_Text_2:
# 548 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Sorry, you didn't have space for the\n"
	.string "egg.$"

ClassStartsMessage::
# 603 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Get seated everybody. Class is in\n"
	.string "session.$"
