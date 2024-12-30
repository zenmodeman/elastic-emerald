# 1 "data/maps/RustboroCity_PokemonSchool/scripts.pory"

# 2 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
.set LOCALID_RIVAL, 8
# 3 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
.set LOCALID_TEACHER, 6
# 4 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
.set LOCALID_ROXANNE, 9
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
RustboroCity_PokemonSchool_EventScript_TeacherOld::
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


RustboroCity_PokemonSchool_EventScript_Teacher::
# 364 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	lock
# 365 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_EventScript_Teacher_Text_0
# 366 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	ai_vs_ai_battle TRAINER_ROXANNE_4, TRAINER_WALTER_4
# 367 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox RustboroCity_PokemonSchool_EventScript_Teacher_Text_1
# 368 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	release
	end


TrainerSchool_Lecture::
# 376 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_TeacherIntro
	return


TrainerSchool_TeacherIntro::
# 381 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement LOCALID_TEACHER, TeacherLecture_MovesTowardsClass
# 382 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement LOCALID_TEACHER
# 383 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_0
# 384 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_1
# 385 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_2
# 386 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement LOCALID_TEACHER, TeacherLecture_Right_And_Face_Down
# 387 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement LOCALID_TEACHER
# 388 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_3
# 389 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_4
# 390 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_5
# 391 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement LOCALID_TEACHER, TeacherLecture_Left_And_Face_Down
# 392 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement LOCALID_TEACHER
# 393 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_6
# 394 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_7
# 395 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_8
# 396 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_9
# 397 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox TrainerSchool_TeacherIntro_Text_10
# 398 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement LOCALID_TEACHER, TeacherLecture_MovesAwayFromClass
# 399 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement LOCALID_TEACHER
	return


# 402 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
TeacherLecture_Right_And_Face_Down:
# 403 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 404 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	face_down
# 405 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	step_end

# 408 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
TeacherLecture_Left_And_Face_Down:
# 409 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_left
# 410 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	face_down
# 411 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	step_end

# 414 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
TeacherLecture_MovesTowardsClass:
# 415 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_left
# 416 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_down
# 417 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_down
# 418 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 419 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	face_down
# 420 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	step_end

# 423 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
TeacherLecture_MovesAwayFromClass:
# 424 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_left
# 425 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 426 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 427 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 428 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	face_down
# 429 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	step_end

TrainerSchool_TriggerLeft::
# 435 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	lockall
# 436 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox ClassStartsMessage
# 437 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, LeftTriggerMovement
# 438 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 439 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_Lecture
# 440 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	releaseall
	end


# 445 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
LeftTriggerMovement:
# 446 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 447 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 448 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 449 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 450 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 451 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 452 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 453 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 454 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 455 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 456 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 457 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 458 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	face_up
# 459 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	step_end

TrainerSchool_TriggerUp::
# 463 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	lockall
# 464 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox ClassStartsMessage
# 465 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, UpTriggerMovement
# 466 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 467 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_Lecture
# 468 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	releaseall
	end


# 472 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
UpTriggerMovement:
# 473 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 474 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 475 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 476 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 477 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 478 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 479 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 480 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 481 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 482 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 483 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	face_up
# 484 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	step_end

TrainerSchool_TriggerUpRight::
# 488 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	lockall
# 489 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox ClassStartsMessage
# 490 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, UpRightTriggerMovement
# 491 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 492 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_Lecture
# 493 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	releaseall
	end


# 497 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
UpRightTriggerMovement:
# 498 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 499 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 500 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 501 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 502 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 503 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 504 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 505 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 506 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 507 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	face_up
# 508 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	step_end

TrainerSchool_TriggerRight::
# 513 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	lockall
# 514 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	face_up
# 515 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	msgbox ClassStartsMessage
# 516 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, RightTriggerMovement
# 517 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	waitmovement OBJ_EVENT_ID_PLAYER
# 518 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	call TrainerSchool_Lecture
# 519 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	releaseall
	end


# 523 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
RightTriggerMovement:
# 524 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 525 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 526 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 527 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 528 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 529 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 530 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 531 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_up
# 532 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	walk_right
# 533 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	face_up
# 534 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	step_end

RustboroCity_PokemonSchool_EventScript_Teacher_Text_0:
# 365 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Roxanne is going to help me\n"
	.string "demonstrate Terastallization to the\l"
	.string "class.$"

RustboroCity_PokemonSchool_EventScript_Teacher_Text_1:
# 367 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Hope that was a good showcase.$"

TrainerSchool_TeacherIntro_Text_0:
# 383 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Welcome again class. Today is a special\n"
	.string "lesson, since as you can see, Roxanne\l"
	.string "has joined us.$"

TrainerSchool_TeacherIntro_Text_1:
# 384 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "She's now our City's Gym Leader but\n"
	.string "some of you were here when she was one\l"
	.string "of our school's brightest pupils.$"

TrainerSchool_TeacherIntro_Text_2:
# 385 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "She has an interesting perspective on\n"
	.string "our topic today.$"

TrainerSchool_TeacherIntro_Text_3:
# 388 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Today's lesson is on the Terastal\n"
	.string "phenomenon discovered in Paldea not\l"
	.string "too long ago.$"

TrainerSchool_TeacherIntro_Text_4:
# 389 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "With progressing advancements in Tera\n"
	.string "Orbs, the phenomenon can now manifest\l"
	.string "across the globe.$"

TrainerSchool_TeacherIntro_Text_5:
# 390 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Tera Orbs are still expensive to\n"
	.string "manufacture, but our very own Devon\l"
	.string "Corp is working towards their\l"
	.string "accessibility!$"

TrainerSchool_TeacherIntro_Text_6:
# 393 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Terastalization is the biggest\n"
	.string "gamechanger to Pokemon battles.$"

TrainerSchool_TeacherIntro_Text_7:
# 394 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "It adds several dimensions to every\n"
	.string "Pokemon, and unlocks possibilites never\l"
	.string "seen before.$"

TrainerSchool_TeacherIntro_Text_8:
# 395 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Naturally, Hoenn's Gym Leaders, our\n"
	.string "region's Type Experts,$"

TrainerSchool_TeacherIntro_Text_9:
# 396 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "were some of the first in our region to\n"
	.string "get Tera Orbs.$"

TrainerSchool_TeacherIntro_Text_10:
# 397 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Now give it up to Roxanne, who's going\n"
	.string "to talk about what Terastalization\l"
	.string "means to her.$"

ClassStartsMessage::
# 431 "data/maps/RustboroCity_PokemonSchool/scripts.pory"
	.string "Get seated everybody. Class is in\n"
	.string "session.$"
