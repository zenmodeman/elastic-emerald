# 1 "data/scripts/field_move_scripts.pory"

# 2 "data/scripts/field_move_scripts.pory"

# 3 "data/scripts/field_move_scripts.pory"
@ Interact with cuttable tree
# 4 "data/scripts/field_move_scripts.pory"
EventScript_CutTree::
# 5 "data/scripts/field_move_scripts.pory"
	lockall
# 6 "data/scripts/field_move_scripts.pory"
	goto_if_unset FLAG_BADGE01_GET, EventScript_CheckTreeCantCut
# 7 "data/scripts/field_move_scripts.pory"
	checkpartymove MOVE_CUT
# 8 "data/scripts/field_move_scripts.pory"
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_AskScytherToCut
# 9 "data/scripts/field_move_scripts.pory"
	setfieldeffectargument 0, VAR_RESULT
# 10 "data/scripts/field_move_scripts.pory"
	bufferpartymonnick STR_VAR_1, VAR_RESULT
# 11 "data/scripts/field_move_scripts.pory"
	buffermovename STR_VAR_2, MOVE_CUT
# 12 "data/scripts/field_move_scripts.pory"
	msgbox Text_WantToCut, MSGBOX_YESNO
# 13 "data/scripts/field_move_scripts.pory"
	goto_if_eq VAR_RESULT, NO, EventScript_CancelCut
# 14 "data/scripts/field_move_scripts.pory"
	msgbox Text_MonUsedFieldMove, MSGBOX_DEFAULT
# 15 "data/scripts/field_move_scripts.pory"
	closemessage
# 16 "data/scripts/field_move_scripts.pory"
EventScript_CutTreeCommon:
# 17 "data/scripts/field_move_scripts.pory"
	isfollowerfieldmoveuser VAR_0x8004
# 18 "data/scripts/field_move_scripts.pory"
	setfieldeffectargument 3, VAR_0x8004 @ skip pose if so
# 19 "data/scripts/field_move_scripts.pory"
	dofieldeffect FLDEFF_USE_CUT_ON_TREE
# 20 "data/scripts/field_move_scripts.pory"
	waitstate
# 21 "data/scripts/field_move_scripts.pory"
EventScript_CutTreeDown:: @ fallthrough
# 22 "data/scripts/field_move_scripts.pory"
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
# 23 "data/scripts/field_move_scripts.pory"
	call_if_eq VAR_0x8004, TRUE, EventScript_FollowerFieldMove
# 24 "data/scripts/field_move_scripts.pory"
	applymovement VAR_LAST_TALKED, Movement_CutTreeDown
# 25 "data/scripts/field_move_scripts.pory"
	waitmovement 0
# 26 "data/scripts/field_move_scripts.pory"
	removeobject VAR_LAST_TALKED
# 27 "data/scripts/field_move_scripts.pory"
	releaseall
# 28 "data/scripts/field_move_scripts.pory"
	end
# 29 "data/scripts/field_move_scripts.pory"

# 30 "data/scripts/field_move_scripts.pory"
@ Use cut from party menu
# 31 "data/scripts/field_move_scripts.pory"
EventScript_UseCut::
# 32 "data/scripts/field_move_scripts.pory"
	lockall
# 33 "data/scripts/field_move_scripts.pory"
	goto EventScript_CutTreeCommon
# 34 "data/scripts/field_move_scripts.pory"

# 35 "data/scripts/field_move_scripts.pory"
Movement_CutTreeDown:
# 36 "data/scripts/field_move_scripts.pory"
	cut_tree
# 37 "data/scripts/field_move_scripts.pory"
	step_end
# 38 "data/scripts/field_move_scripts.pory"

# 39 "data/scripts/field_move_scripts.pory"
EventScript_CheckTreeCantCut::
# 40 "data/scripts/field_move_scripts.pory"
	msgbox Text_CantCut, MSGBOX_DEFAULT
# 41 "data/scripts/field_move_scripts.pory"
	releaseall
# 42 "data/scripts/field_move_scripts.pory"
	end
# 43 "data/scripts/field_move_scripts.pory"

# 44 "data/scripts/field_move_scripts.pory"
EventScript_CancelCut::
# 45 "data/scripts/field_move_scripts.pory"
	closemessage
# 46 "data/scripts/field_move_scripts.pory"
	releaseall
# 47 "data/scripts/field_move_scripts.pory"
	end
# 48 "data/scripts/field_move_scripts.pory"

# 49 "data/scripts/field_move_scripts.pory"
Text_WantToCut:
# 50 "data/scripts/field_move_scripts.pory"
	.string "This tree looks like it can be\n"
# 51 "data/scripts/field_move_scripts.pory"
	.string "CUT down!\p"
# 52 "data/scripts/field_move_scripts.pory"
	.string "Would you like to CUT it?$"
# 53 "data/scripts/field_move_scripts.pory"

# 54 "data/scripts/field_move_scripts.pory"
Text_MonUsedFieldMove:
# 55 "data/scripts/field_move_scripts.pory"
	.string "{STR_VAR_1} used {STR_VAR_2}!$"
# 56 "data/scripts/field_move_scripts.pory"

# 57 "data/scripts/field_move_scripts.pory"
Text_CantCut:
# 58 "data/scripts/field_move_scripts.pory"
	.string "This tree looks like it can be\n"
# 59 "data/scripts/field_move_scripts.pory"
	.string "CUT down!$"
# 60 "data/scripts/field_move_scripts.pory"

# 61 "data/scripts/field_move_scripts.pory"
@ Use rock smash from party menu
# 62 "data/scripts/field_move_scripts.pory"
EventScript_UseRockSmash::
# 63 "data/scripts/field_move_scripts.pory"
	lockall
# 64 "data/scripts/field_move_scripts.pory"
	goto EventScript_RockSmashCommon
# 65 "data/scripts/field_move_scripts.pory"

# 66 "data/scripts/field_move_scripts.pory"
@ Interact with smashable rock
# 67 "data/scripts/field_move_scripts.pory"
EventScript_RockSmash::
# 68 "data/scripts/field_move_scripts.pory"
	lockall
# 69 "data/scripts/field_move_scripts.pory"
	goto_if_unset FLAG_BADGE03_GET, EventScript_CantSmashRock
# 70 "data/scripts/field_move_scripts.pory"
	checkpartymove MOVE_ROCK_SMASH
# 71 "data/scripts/field_move_scripts.pory"
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CantSmashRock
# 72 "data/scripts/field_move_scripts.pory"
	setfieldeffectargument 0, VAR_RESULT
# 73 "data/scripts/field_move_scripts.pory"
	bufferpartymonnick STR_VAR_1, VAR_RESULT
# 74 "data/scripts/field_move_scripts.pory"
	buffermovename STR_VAR_2, MOVE_ROCK_SMASH
# 75 "data/scripts/field_move_scripts.pory"
	msgbox Text_WantToSmash, MSGBOX_YESNO
# 76 "data/scripts/field_move_scripts.pory"
	goto_if_eq VAR_RESULT, NO, EventScript_CancelSmash
# 77 "data/scripts/field_move_scripts.pory"
	msgbox Text_MonUsedFieldMove, MSGBOX_DEFAULT
# 78 "data/scripts/field_move_scripts.pory"
	closemessage
# 79 "data/scripts/field_move_scripts.pory"
EventScript_RockSmashCommon:
# 80 "data/scripts/field_move_scripts.pory"
	@ check if follower should use the field move
# 81 "data/scripts/field_move_scripts.pory"
	isfollowerfieldmoveuser VAR_0x8004
# 82 "data/scripts/field_move_scripts.pory"
	setfieldeffectargument 3, VAR_0x8004 @ skip pose if so
# 83 "data/scripts/field_move_scripts.pory"
	dofieldeffect FLDEFF_USE_ROCK_SMASH
# 84 "data/scripts/field_move_scripts.pory"
	waitstate
# 85 "data/scripts/field_move_scripts.pory"
EventScript_SmashRock:: @ fallthrough
# 86 "data/scripts/field_move_scripts.pory"
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
# 87 "data/scripts/field_move_scripts.pory"
	call_if_eq VAR_0x8004, TRUE, EventScript_FollowerFieldMove
# 88 "data/scripts/field_move_scripts.pory"
	applymovement VAR_LAST_TALKED, Movement_SmashRock
# 89 "data/scripts/field_move_scripts.pory"
	waitmovement 0
# 90 "data/scripts/field_move_scripts.pory"
	removeobject VAR_LAST_TALKED
# 91 "data/scripts/field_move_scripts.pory"
	specialvar VAR_RESULT, TryUpdateRusturfTunnelState
# 92 "data/scripts/field_move_scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, EventScript_EndSmash
# 93 "data/scripts/field_move_scripts.pory"
	special RockSmashWildEncounter
# 94 "data/scripts/field_move_scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, EventScript_EndSmash
# 95 "data/scripts/field_move_scripts.pory"
	waitstate
# 96 "data/scripts/field_move_scripts.pory"
	releaseall
# 97 "data/scripts/field_move_scripts.pory"
	end
# 98 "data/scripts/field_move_scripts.pory"

# 99 "data/scripts/field_move_scripts.pory"
EventScript_FollowerFieldMove:
# 100 "data/scripts/field_move_scripts.pory"
	getdirectiontoface VAR_0x8005, OBJ_EVENT_ID_FOLLOWER, OBJ_EVENT_ID_PLAYER
# 101 "data/scripts/field_move_scripts.pory"
	specialvar VAR_0x8006, GetPlayerFacingDirection
# 102 "data/scripts/field_move_scripts.pory"
	goto_if_eq VAR_0x8005, DIR_NONE, EventScript_FollowerFieldMoveEnd
# 103 "data/scripts/field_move_scripts.pory"
	@ Swap follower and player
# 104 "data/scripts/field_move_scripts.pory"
	call EventScript_FollowerSwap
# 105 "data/scripts/field_move_scripts.pory"
	@ Face follower in direction and jump
# 106 "data/scripts/field_move_scripts.pory"
	switch VAR_0x8006
# 107 "data/scripts/field_move_scripts.pory"
	case DIR_NORTH, EventScript_FollowerJumpNorth
# 108 "data/scripts/field_move_scripts.pory"
	case DIR_EAST, EventScript_FollowerJumpEast
# 109 "data/scripts/field_move_scripts.pory"
	case DIR_SOUTH, EventScript_FollowerJumpSouth
# 110 "data/scripts/field_move_scripts.pory"
	case DIR_WEST, EventScript_FollowerJumpWest
# 111 "data/scripts/field_move_scripts.pory"
EventScript_FollowerFieldMoveEnd:
# 112 "data/scripts/field_move_scripts.pory"
	return
# 113 "data/scripts/field_move_scripts.pory"

# 114 "data/scripts/field_move_scripts.pory"
EventScript_FollowerSwap:
# 115 "data/scripts/field_move_scripts.pory"
	switch VAR_0x8005
# 116 "data/scripts/field_move_scripts.pory"
	case DIR_NORTH, EventScript_FollowerMoveNorth
# 117 "data/scripts/field_move_scripts.pory"
	case DIR_EAST, EventScript_FollowerMoveEast
# 118 "data/scripts/field_move_scripts.pory"
	case DIR_SOUTH, EventScript_FollowerMoveSouth
# 119 "data/scripts/field_move_scripts.pory"
	case DIR_WEST, EventScript_FollowerMoveWest
# 120 "data/scripts/field_move_scripts.pory"
	return
# 121 "data/scripts/field_move_scripts.pory"

# 122 "data/scripts/field_move_scripts.pory"
EventScript_FollowerMoveNorth:
# 123 "data/scripts/field_move_scripts.pory"
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_WalkUp
# 124 "data/scripts/field_move_scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkDown
# 125 "data/scripts/field_move_scripts.pory"
	waitmovement 0
# 126 "data/scripts/field_move_scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceUp
# 127 "data/scripts/field_move_scripts.pory"
	waitmovement 0
# 128 "data/scripts/field_move_scripts.pory"
	return
# 129 "data/scripts/field_move_scripts.pory"

# 130 "data/scripts/field_move_scripts.pory"
EventScript_FollowerMoveEast:
# 131 "data/scripts/field_move_scripts.pory"
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_WalkRight
# 132 "data/scripts/field_move_scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkLeft
# 133 "data/scripts/field_move_scripts.pory"
	waitmovement 0
# 134 "data/scripts/field_move_scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
# 135 "data/scripts/field_move_scripts.pory"
	waitmovement 0
# 136 "data/scripts/field_move_scripts.pory"
	return
# 137 "data/scripts/field_move_scripts.pory"

# 138 "data/scripts/field_move_scripts.pory"
EventScript_FollowerMoveSouth:
# 139 "data/scripts/field_move_scripts.pory"
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_WalkDown
# 140 "data/scripts/field_move_scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkUp
# 141 "data/scripts/field_move_scripts.pory"
	waitmovement 0
# 142 "data/scripts/field_move_scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
# 143 "data/scripts/field_move_scripts.pory"
	waitmovement 0
# 144 "data/scripts/field_move_scripts.pory"
	return
# 145 "data/scripts/field_move_scripts.pory"

# 146 "data/scripts/field_move_scripts.pory"
EventScript_FollowerMoveWest:
# 147 "data/scripts/field_move_scripts.pory"
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_WalkLeft
# 148 "data/scripts/field_move_scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Movement_WalkRight
# 149 "data/scripts/field_move_scripts.pory"
	waitmovement 0
# 150 "data/scripts/field_move_scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
# 151 "data/scripts/field_move_scripts.pory"
	waitmovement 0
# 152 "data/scripts/field_move_scripts.pory"
	return
# 153 "data/scripts/field_move_scripts.pory"

# 154 "data/scripts/field_move_scripts.pory"
EventScript_FollowerJumpNorth:
# 155 "data/scripts/field_move_scripts.pory"
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_JumpUp
# 156 "data/scripts/field_move_scripts.pory"
	waitmovement 0
# 157 "data/scripts/field_move_scripts.pory"
	return
# 158 "data/scripts/field_move_scripts.pory"

# 159 "data/scripts/field_move_scripts.pory"
EventScript_FollowerJumpEast:
# 160 "data/scripts/field_move_scripts.pory"
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_JumpRight
# 161 "data/scripts/field_move_scripts.pory"
	waitmovement 0
# 162 "data/scripts/field_move_scripts.pory"
	return
# 163 "data/scripts/field_move_scripts.pory"

# 164 "data/scripts/field_move_scripts.pory"
EventScript_FollowerJumpSouth:
# 165 "data/scripts/field_move_scripts.pory"
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_JumpDown
# 166 "data/scripts/field_move_scripts.pory"
	waitmovement 0
# 167 "data/scripts/field_move_scripts.pory"
	return
# 168 "data/scripts/field_move_scripts.pory"

# 169 "data/scripts/field_move_scripts.pory"
EventScript_FollowerJumpWest:
# 170 "data/scripts/field_move_scripts.pory"
	applymovement OBJ_EVENT_ID_FOLLOWER, Movement_JumpLeft
# 171 "data/scripts/field_move_scripts.pory"
	waitmovement 0
# 172 "data/scripts/field_move_scripts.pory"
	return
# 173 "data/scripts/field_move_scripts.pory"

# 174 "data/scripts/field_move_scripts.pory"
EventScript_EndSmash::
# 175 "data/scripts/field_move_scripts.pory"
	releaseall
# 176 "data/scripts/field_move_scripts.pory"
	end
# 177 "data/scripts/field_move_scripts.pory"

# 178 "data/scripts/field_move_scripts.pory"
Movement_WalkUp:
# 179 "data/scripts/field_move_scripts.pory"
	walk_up
# 180 "data/scripts/field_move_scripts.pory"
	step_end
# 181 "data/scripts/field_move_scripts.pory"

# 182 "data/scripts/field_move_scripts.pory"
Movement_JumpUp:
# 183 "data/scripts/field_move_scripts.pory"
	jump_in_place_up
# 184 "data/scripts/field_move_scripts.pory"
	step_end
# 185 "data/scripts/field_move_scripts.pory"

# 186 "data/scripts/field_move_scripts.pory"
Movement_WalkRight:
# 187 "data/scripts/field_move_scripts.pory"
	walk_right
# 188 "data/scripts/field_move_scripts.pory"
	step_end
# 189 "data/scripts/field_move_scripts.pory"

# 190 "data/scripts/field_move_scripts.pory"
Movement_JumpRight:
# 191 "data/scripts/field_move_scripts.pory"
	jump_in_place_right
# 192 "data/scripts/field_move_scripts.pory"
	step_end
# 193 "data/scripts/field_move_scripts.pory"

# 194 "data/scripts/field_move_scripts.pory"
Movement_WalkDown:
# 195 "data/scripts/field_move_scripts.pory"
	walk_down
# 196 "data/scripts/field_move_scripts.pory"
	step_end
# 197 "data/scripts/field_move_scripts.pory"

# 198 "data/scripts/field_move_scripts.pory"
Movement_JumpDown:
# 199 "data/scripts/field_move_scripts.pory"
	jump_in_place_down
# 200 "data/scripts/field_move_scripts.pory"
	step_end
# 201 "data/scripts/field_move_scripts.pory"

# 202 "data/scripts/field_move_scripts.pory"
Movement_WalkLeft:
# 203 "data/scripts/field_move_scripts.pory"
	walk_left
# 204 "data/scripts/field_move_scripts.pory"
	step_end
# 205 "data/scripts/field_move_scripts.pory"

# 206 "data/scripts/field_move_scripts.pory"
Movement_JumpLeft:
# 207 "data/scripts/field_move_scripts.pory"
	jump_in_place_left
# 208 "data/scripts/field_move_scripts.pory"
	step_end
# 209 "data/scripts/field_move_scripts.pory"

# 210 "data/scripts/field_move_scripts.pory"
Movement_SmashRock:
# 211 "data/scripts/field_move_scripts.pory"
	rock_smash_break
# 212 "data/scripts/field_move_scripts.pory"
	step_end
# 213 "data/scripts/field_move_scripts.pory"

# 214 "data/scripts/field_move_scripts.pory"
EventScript_CantSmashRock::
# 215 "data/scripts/field_move_scripts.pory"
	msgbox Text_CantSmash, MSGBOX_DEFAULT
# 216 "data/scripts/field_move_scripts.pory"
	releaseall
# 217 "data/scripts/field_move_scripts.pory"
	end
# 218 "data/scripts/field_move_scripts.pory"

# 219 "data/scripts/field_move_scripts.pory"
EventScript_CancelSmash::
# 220 "data/scripts/field_move_scripts.pory"
	closemessage
# 221 "data/scripts/field_move_scripts.pory"
	releaseall
# 222 "data/scripts/field_move_scripts.pory"
	end
# 223 "data/scripts/field_move_scripts.pory"

# 224 "data/scripts/field_move_scripts.pory"
Text_WantToSmash:
# 225 "data/scripts/field_move_scripts.pory"
	.string "This rock appears to be breakable.\n"
# 226 "data/scripts/field_move_scripts.pory"
	.string "Would you like to use ROCK SMASH?$"
# 227 "data/scripts/field_move_scripts.pory"

# 228 "data/scripts/field_move_scripts.pory"
Text_CantSmash:
# 229 "data/scripts/field_move_scripts.pory"
	.string "It's a rugged rock, but a POKéMON\n"
# 230 "data/scripts/field_move_scripts.pory"
	.string "may be able to smash it.$"
# 231 "data/scripts/field_move_scripts.pory"

# 232 "data/scripts/field_move_scripts.pory"
EventScript_StrengthBoulder::
# 233 "data/scripts/field_move_scripts.pory"
	lockall
# 234 "data/scripts/field_move_scripts.pory"
	goto_if_unset FLAG_BADGE04_GET, EventScript_CantStrength
# 235 "data/scripts/field_move_scripts.pory"
	goto_if_set FLAG_SYS_USE_STRENGTH, EventScript_CheckActivatedBoulder
# 236 "data/scripts/field_move_scripts.pory"
	checkpartymove MOVE_STRENGTH
# 237 "data/scripts/field_move_scripts.pory"
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CantStrength
# 238 "data/scripts/field_move_scripts.pory"
	setfieldeffectargument 0, VAR_RESULT
# 239 "data/scripts/field_move_scripts.pory"
	msgbox Text_WantToStrength, MSGBOX_YESNO
# 240 "data/scripts/field_move_scripts.pory"
	goto_if_eq VAR_RESULT, NO, EventScript_CancelStrength
# 241 "data/scripts/field_move_scripts.pory"
	closemessage
# 242 "data/scripts/field_move_scripts.pory"
	dofieldeffect FLDEFF_USE_STRENGTH
# 243 "data/scripts/field_move_scripts.pory"
	waitstate
# 244 "data/scripts/field_move_scripts.pory"
	goto EventScript_ActivateStrength
# 245 "data/scripts/field_move_scripts.pory"
	end
# 246 "data/scripts/field_move_scripts.pory"

# 247 "data/scripts/field_move_scripts.pory"
EventScript_UseStrength::
# 248 "data/scripts/field_move_scripts.pory"
	lockall
# 249 "data/scripts/field_move_scripts.pory"
	dofieldeffect FLDEFF_USE_STRENGTH
# 250 "data/scripts/field_move_scripts.pory"
	waitstate
# 251 "data/scripts/field_move_scripts.pory"
	goto EventScript_ActivateStrength
# 252 "data/scripts/field_move_scripts.pory"
	end
# 253 "data/scripts/field_move_scripts.pory"

# 254 "data/scripts/field_move_scripts.pory"
EventScript_ActivateStrength::
# 255 "data/scripts/field_move_scripts.pory"
	setflag FLAG_SYS_USE_STRENGTH
# 256 "data/scripts/field_move_scripts.pory"
	msgbox Text_MonUsedStrength, MSGBOX_DEFAULT
# 257 "data/scripts/field_move_scripts.pory"
	releaseall
# 258 "data/scripts/field_move_scripts.pory"
	end
# 259 "data/scripts/field_move_scripts.pory"

# 260 "data/scripts/field_move_scripts.pory"
EventScript_CantStrength::
# 261 "data/scripts/field_move_scripts.pory"
	msgbox Text_CantStrength, MSGBOX_DEFAULT
# 262 "data/scripts/field_move_scripts.pory"
	releaseall
# 263 "data/scripts/field_move_scripts.pory"
	end
# 264 "data/scripts/field_move_scripts.pory"

# 265 "data/scripts/field_move_scripts.pory"
EventScript_CheckActivatedBoulder::
# 266 "data/scripts/field_move_scripts.pory"
	msgbox Text_StrengthActivated, MSGBOX_DEFAULT
# 267 "data/scripts/field_move_scripts.pory"
	releaseall
# 268 "data/scripts/field_move_scripts.pory"
	end
# 269 "data/scripts/field_move_scripts.pory"

# 270 "data/scripts/field_move_scripts.pory"
EventScript_CancelStrength::
# 271 "data/scripts/field_move_scripts.pory"
	closemessage
# 272 "data/scripts/field_move_scripts.pory"
	releaseall
# 273 "data/scripts/field_move_scripts.pory"
	end
# 274 "data/scripts/field_move_scripts.pory"

# 275 "data/scripts/field_move_scripts.pory"
Text_WantToStrength:
# 276 "data/scripts/field_move_scripts.pory"
	.string "It's a big boulder, but a POKéMON\n"
# 277 "data/scripts/field_move_scripts.pory"
	.string "may be able to push it aside.\p"
# 278 "data/scripts/field_move_scripts.pory"
	.string "Would you like to use STRENGTH?$"
# 279 "data/scripts/field_move_scripts.pory"

# 280 "data/scripts/field_move_scripts.pory"
Text_MonUsedStrength:
# 281 "data/scripts/field_move_scripts.pory"
	.string "{STR_VAR_1} used STRENGTH!\p"
# 282 "data/scripts/field_move_scripts.pory"
	.string "{STR_VAR_1}'s STRENGTH made it\n"
# 283 "data/scripts/field_move_scripts.pory"
	.string "possible to move boulders around!$"
# 284 "data/scripts/field_move_scripts.pory"

# 285 "data/scripts/field_move_scripts.pory"
Text_CantStrength:
# 286 "data/scripts/field_move_scripts.pory"
	.string "It's a big boulder, but a POKéMON\n"
# 287 "data/scripts/field_move_scripts.pory"
	.string "may be able to push it aside.$"
# 288 "data/scripts/field_move_scripts.pory"

# 289 "data/scripts/field_move_scripts.pory"
Text_StrengthActivated:
# 290 "data/scripts/field_move_scripts.pory"
	.string "STRENGTH made it possible to move\n"
# 291 "data/scripts/field_move_scripts.pory"
	.string "boulders around.$"
# 292 "data/scripts/field_move_scripts.pory"

# 293 "data/scripts/field_move_scripts.pory"
EventScript_UseWaterfall::
# 294 "data/scripts/field_move_scripts.pory"
	lockall
# 295 "data/scripts/field_move_scripts.pory"
	checkpartymove MOVE_WATERFALL
# 296 "data/scripts/field_move_scripts.pory"
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CantWaterfall
# 297 "data/scripts/field_move_scripts.pory"
	bufferpartymonnick STR_VAR_1, VAR_RESULT
# 298 "data/scripts/field_move_scripts.pory"
	setfieldeffectargument 0, VAR_RESULT
# 299 "data/scripts/field_move_scripts.pory"
	msgbox Text_WantToWaterfall, MSGBOX_YESNO
# 300 "data/scripts/field_move_scripts.pory"
	goto_if_eq VAR_RESULT, NO, EventScript_EndWaterfall
# 301 "data/scripts/field_move_scripts.pory"
	msgbox Text_MonUsedWaterfall, MSGBOX_DEFAULT
# 302 "data/scripts/field_move_scripts.pory"
	dofieldeffect FLDEFF_USE_WATERFALL
# 303 "data/scripts/field_move_scripts.pory"
	goto EventScript_EndWaterfall
# 304 "data/scripts/field_move_scripts.pory"

# 305 "data/scripts/field_move_scripts.pory"
EventScript_CannotUseWaterfall::
# 306 "data/scripts/field_move_scripts.pory"
	lockall
# 307 "data/scripts/field_move_scripts.pory"

# 308 "data/scripts/field_move_scripts.pory"
EventScript_CantWaterfall::
# 309 "data/scripts/field_move_scripts.pory"
	msgbox Text_CantWaterfall, MSGBOX_DEFAULT
# 310 "data/scripts/field_move_scripts.pory"

# 311 "data/scripts/field_move_scripts.pory"
EventScript_EndWaterfall::
# 312 "data/scripts/field_move_scripts.pory"
	releaseall
# 313 "data/scripts/field_move_scripts.pory"
	end
# 314 "data/scripts/field_move_scripts.pory"

# 315 "data/scripts/field_move_scripts.pory"
Text_CantWaterfall:
# 316 "data/scripts/field_move_scripts.pory"
	.string "A wall of water is crashing down with\n"
# 317 "data/scripts/field_move_scripts.pory"
	.string "a mighty roar.$"
# 318 "data/scripts/field_move_scripts.pory"

# 319 "data/scripts/field_move_scripts.pory"
Text_WantToWaterfall:
# 320 "data/scripts/field_move_scripts.pory"
	.string "It's a large waterfall.\n"
# 321 "data/scripts/field_move_scripts.pory"
	.string "Would you like to use WATERFALL?$"
# 322 "data/scripts/field_move_scripts.pory"

# 323 "data/scripts/field_move_scripts.pory"
Text_MonUsedWaterfall:
# 324 "data/scripts/field_move_scripts.pory"
	.string "{STR_VAR_1} used WATERFALL.$"
# 325 "data/scripts/field_move_scripts.pory"

# 326 "data/scripts/field_move_scripts.pory"
EventScript_UseDive::
# 327 "data/scripts/field_move_scripts.pory"
	lockall
# 328 "data/scripts/field_move_scripts.pory"
	checkpartymove MOVE_DIVE
# 329 "data/scripts/field_move_scripts.pory"
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CantDive
# 330 "data/scripts/field_move_scripts.pory"
	bufferpartymonnick STR_VAR_1, VAR_RESULT
# 331 "data/scripts/field_move_scripts.pory"
	setfieldeffectargument 0, VAR_RESULT
# 332 "data/scripts/field_move_scripts.pory"
	setfieldeffectargument 1, 1
# 333 "data/scripts/field_move_scripts.pory"
	msgbox Text_WantToDive, MSGBOX_YESNO
# 334 "data/scripts/field_move_scripts.pory"
	goto_if_eq VAR_RESULT, NO, EventScript_EndDive
# 335 "data/scripts/field_move_scripts.pory"
	msgbox Text_MonUsedDive, MSGBOX_DEFAULT
# 336 "data/scripts/field_move_scripts.pory"
	dofieldeffect FLDEFF_USE_DIVE
# 337 "data/scripts/field_move_scripts.pory"
	goto EventScript_EndDive
# 338 "data/scripts/field_move_scripts.pory"
	end
# 339 "data/scripts/field_move_scripts.pory"

# 340 "data/scripts/field_move_scripts.pory"
EventScript_CantDive::
# 341 "data/scripts/field_move_scripts.pory"
	msgbox Text_CantDive, MSGBOX_DEFAULT
# 342 "data/scripts/field_move_scripts.pory"
	releaseall
# 343 "data/scripts/field_move_scripts.pory"
	end
# 344 "data/scripts/field_move_scripts.pory"

# 345 "data/scripts/field_move_scripts.pory"
EventScript_EndDive::
# 346 "data/scripts/field_move_scripts.pory"
	releaseall
# 347 "data/scripts/field_move_scripts.pory"
	end
# 348 "data/scripts/field_move_scripts.pory"

# 349 "data/scripts/field_move_scripts.pory"
EventScript_UseDiveUnderwater::
# 350 "data/scripts/field_move_scripts.pory"
	lockall
# 351 "data/scripts/field_move_scripts.pory"
	checkpartymove MOVE_DIVE
# 352 "data/scripts/field_move_scripts.pory"
	goto_if_eq VAR_RESULT, PARTY_SIZE, EventScript_CantSurface
# 353 "data/scripts/field_move_scripts.pory"
	bufferpartymonnick STR_VAR_1, VAR_RESULT
# 354 "data/scripts/field_move_scripts.pory"
	setfieldeffectargument 0, VAR_RESULT
# 355 "data/scripts/field_move_scripts.pory"
	setfieldeffectargument 1, 1
# 356 "data/scripts/field_move_scripts.pory"
	msgbox Text_WantToSurface, MSGBOX_YESNO
# 357 "data/scripts/field_move_scripts.pory"
	goto_if_eq VAR_RESULT, NO, EventScript_EndSurface
# 358 "data/scripts/field_move_scripts.pory"
	msgbox Text_MonUsedDive, MSGBOX_DEFAULT
# 359 "data/scripts/field_move_scripts.pory"
	dofieldeffect FLDEFF_USE_DIVE
# 360 "data/scripts/field_move_scripts.pory"
	goto EventScript_EndSurface
# 361 "data/scripts/field_move_scripts.pory"
	end
# 362 "data/scripts/field_move_scripts.pory"

# 363 "data/scripts/field_move_scripts.pory"
EventScript_CantSurface::
# 364 "data/scripts/field_move_scripts.pory"
	lockall
# 365 "data/scripts/field_move_scripts.pory"
	msgbox Text_CantSurface, MSGBOX_DEFAULT
# 366 "data/scripts/field_move_scripts.pory"
	goto EventScript_EndSurface
# 367 "data/scripts/field_move_scripts.pory"
	end
# 368 "data/scripts/field_move_scripts.pory"

# 369 "data/scripts/field_move_scripts.pory"
EventScript_EndSurface::
# 370 "data/scripts/field_move_scripts.pory"
	releaseall
# 371 "data/scripts/field_move_scripts.pory"
	end
# 372 "data/scripts/field_move_scripts.pory"

# 373 "data/scripts/field_move_scripts.pory"
EventScript_DigCommon:
# 374 "data/scripts/field_move_scripts.pory"
	isfollowerfieldmoveuser VAR_0x8004
# 375 "data/scripts/field_move_scripts.pory"
	setfieldeffectargument 3, VAR_0x8004 @ skip pose if true
# 376 "data/scripts/field_move_scripts.pory"
	dofieldeffect FLDEFF_USE_DIG
# 377 "data/scripts/field_move_scripts.pory"
	waitstate
# 378 "data/scripts/field_move_scripts.pory"
EventScript_DigSealedChamber:: @ fallthrough
# 379 "data/scripts/field_move_scripts.pory"
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
# 380 "data/scripts/field_move_scripts.pory"
	call_if_eq VAR_0x8004, TRUE, EventScript_FollowerFieldMove
# 381 "data/scripts/field_move_scripts.pory"
	callnative DoBrailleDigEffect
# 382 "data/scripts/field_move_scripts.pory"
	releaseall
# 383 "data/scripts/field_move_scripts.pory"
	end
# 384 "data/scripts/field_move_scripts.pory"

# 385 "data/scripts/field_move_scripts.pory"
@ Use Dig from party menu
# 386 "data/scripts/field_move_scripts.pory"
EventScript_UseDig::
# 387 "data/scripts/field_move_scripts.pory"
	lockall
# 388 "data/scripts/field_move_scripts.pory"
	goto EventScript_DigCommon
# 389 "data/scripts/field_move_scripts.pory"

# 390 "data/scripts/field_move_scripts.pory"

EventScript_CutGrassCommon:
	isfollowerfieldmoveuser VAR_0x8004
	setfieldeffectargument 3, VAR_0x8004 @ skip pose if true
	dofieldeffect FLDEFF_USE_CUT_ON_GRASS
	waitstate

@ Use Cut grass from party menu
EventScript_UseCutGrass::
	lockall
	goto EventScript_CutGrassCommon

Text_CantDive:
# 391 "data/scripts/field_move_scripts.pory"
	.string "The sea is deep here. A POKéMON\n"
# 392 "data/scripts/field_move_scripts.pory"
	.string "may be able to go underwater.$"
# 393 "data/scripts/field_move_scripts.pory"

# 394 "data/scripts/field_move_scripts.pory"
Text_WantToDive:
# 395 "data/scripts/field_move_scripts.pory"
	.string "The sea is deep here.\n"
# 396 "data/scripts/field_move_scripts.pory"
	.string "Would you like to use DIVE?$"
# 397 "data/scripts/field_move_scripts.pory"

# 398 "data/scripts/field_move_scripts.pory"
Text_MonUsedDive:
# 399 "data/scripts/field_move_scripts.pory"
	.string "{STR_VAR_1} used DIVE.$"
# 400 "data/scripts/field_move_scripts.pory"

# 401 "data/scripts/field_move_scripts.pory"
Text_CantSurface:
# 402 "data/scripts/field_move_scripts.pory"
	.string "Light is filtering down from above.\n"
# 403 "data/scripts/field_move_scripts.pory"
	.string "A POKéMON may be able to surface.$"
# 404 "data/scripts/field_move_scripts.pory"

# 405 "data/scripts/field_move_scripts.pory"
Text_WantToSurface:
# 406 "data/scripts/field_move_scripts.pory"
	.string "Light is filtering down from above.\n"
# 407 "data/scripts/field_move_scripts.pory"
	.string "Would you like to use DIVE?$"
# 408 "data/scripts/field_move_scripts.pory"

# 409 "data/scripts/field_move_scripts.pory"
EventScript_FailSweetScent::
# 410 "data/scripts/field_move_scripts.pory"
	msgbox Text_FailSweetScent, MSGBOX_SIGN
# 411 "data/scripts/field_move_scripts.pory"
	end
# 412 "data/scripts/field_move_scripts.pory"

# 413 "data/scripts/field_move_scripts.pory"
Text_FailSweetScent:
# 414 "data/scripts/field_move_scripts.pory"
	.string "Looks like there's nothing here…$"
# 415 "data/scripts/field_move_scripts.pory"

# 416 "data/scripts/field_move_scripts.pory"
@ Interact with a tree that can be shaken
# 417 "data/scripts/field_move_scripts.pory"
EventScript_Shake::
# 418 "data/scripts/field_move_scripts.pory"
	lockall
# 419 "data/scripts/field_move_scripts.pory"
	setfieldeffectargument 0, VAR_RESULT
# 420 "data/scripts/field_move_scripts.pory"
	msgbox Text_WantToShake, MSGBOX_YESNO
# 421 "data/scripts/field_move_scripts.pory"
	compare VAR_RESULT, NO
# 422 "data/scripts/field_move_scripts.pory"
	goto_if_eq EventScript_CancelShake
# 423 "data/scripts/field_move_scripts.pory"
	goto EventScript_ShakeTree
# 424 "data/scripts/field_move_scripts.pory"
	end
# 425 "data/scripts/field_move_scripts.pory"

# 426 "data/scripts/field_move_scripts.pory"
EventScript_CancelShake::
# 427 "data/scripts/field_move_scripts.pory"
	closemessage
# 428 "data/scripts/field_move_scripts.pory"
	releaseall
# 429 "data/scripts/field_move_scripts.pory"
	end
# 430 "data/scripts/field_move_scripts.pory"

# 431 "data/scripts/field_move_scripts.pory"
EventScript_ShakeTree::
# 432 "data/scripts/field_move_scripts.pory"
	setvar VAR_0x8004, 1  @ vertical pan
# 433 "data/scripts/field_move_scripts.pory"
	setvar VAR_0x8005, 1  @ horizontal pan
# 434 "data/scripts/field_move_scripts.pory"
	setvar VAR_0x8006, 8  @ num shakes
# 435 "data/scripts/field_move_scripts.pory"
	setvar VAR_0x8007, 5  @ shake delay
# 436 "data/scripts/field_move_scripts.pory"
	special ShakeCamera
# 437 "data/scripts/field_move_scripts.pory"
	waitstate
# 438 "data/scripts/field_move_scripts.pory"
	special ShakeWildEncounter
# 439 "data/scripts/field_move_scripts.pory"
	compare VAR_RESULT, FALSE
# 440 "data/scripts/field_move_scripts.pory"
	goto_if_eq EventScript_EndShake
# 441 "data/scripts/field_move_scripts.pory"
	waitstate
# 442 "data/scripts/field_move_scripts.pory"

# 443 "data/scripts/field_move_scripts.pory"
EventScript_EndShake::
# 444 "data/scripts/field_move_scripts.pory"
	releaseall
# 445 "data/scripts/field_move_scripts.pory"
	end
# 446 "data/scripts/field_move_scripts.pory"

# 447 "data/scripts/field_move_scripts.pory"
Text_NoPokemonToShake:
# 448 "data/scripts/field_move_scripts.pory"
	.string "It's a moderate sized tree.\n"
# 449 "data/scripts/field_move_scripts.pory"

# 450 "data/scripts/field_move_scripts.pory"
Text_WantToShake:
# 451 "data/scripts/field_move_scripts.pory"
	.string "It's a moderate sized tree.\n"
# 452 "data/scripts/field_move_scripts.pory"
	.string "Would you like to shake it?$"

EventScript_AskScytherToCut::
# 457 "data/scripts/field_move_scripts.pory"
	setvar VAR_0x8009, 1
# 458 "data/scripts/field_move_scripts.pory"
	bufferspeciesname 0, SPECIES_SCYTHER
# 459 "data/scripts/field_move_scripts.pory"
	buffermovename 1, MOVE_CUT
# 460 "data/scripts/field_move_scripts.pory"
	msgbox EventScript_AskScytherToCut_Text_0
# 461 "data/scripts/field_move_scripts.pory"
	msgbox EventScript_AskScytherToCut_Text_1, MSGBOX_YESNO
# 462 "data/scripts/field_move_scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq EventScript_AskScytherToCut_2
EventScript_AskScytherToCut_1:
# 465 "data/scripts/field_move_scripts.pory"
	msgbox Text_MonUsedFieldMove, MSGBOX_DEFAULT
# 466 "data/scripts/field_move_scripts.pory"
	closemessage
# 467 "data/scripts/field_move_scripts.pory"
	setvar VAR_0x8008, MOVE_CUT
# 468 "data/scripts/field_move_scripts.pory"
	dofieldeffect FLDEFF_USE_CUT_ON_TREE
# 469 "data/scripts/field_move_scripts.pory"
	waitstate
# 470 "data/scripts/field_move_scripts.pory"
	goto EventScript_CutTreeDown
	end

EventScript_AskScytherToCut_2:
# 463 "data/scripts/field_move_scripts.pory"
	goto EventScript_CancelCut
	goto EventScript_AskScytherToCut_1


EventScript_AskScytherToCut_Text_0:
# 460 "data/scripts/field_move_scripts.pory"
	.string "This tree looks like it can be cut down!$"

EventScript_AskScytherToCut_Text_1:
# 461 "data/scripts/field_move_scripts.pory"
	.string "Call Cutter's Scyther to Cut it?$"
