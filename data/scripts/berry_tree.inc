# 1 "data/scripts/berry_tree.pory"

# 2 "data/scripts/berry_tree.pory"

# 3 "data/scripts/berry_tree.pory"
BerryTreeScript::
# 4 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryTreeData
# 5 "data/scripts/berry_tree.pory"
	switch VAR_0x8004
# 6 "data/scripts/berry_tree.pory"
	case BERRY_STAGE_SPARKLING, BerryTree_EventScript_Sparkling
# 7 "data/scripts/berry_tree.pory"
	case BERRY_STAGE_NO_BERRY, BerryTree_EventScript_CheckSoil
# 8 "data/scripts/berry_tree.pory"
	case BERRY_STAGE_PLANTED, BerryTree_EventScript_CheckBerryStage1
# 9 "data/scripts/berry_tree.pory"
	case BERRY_STAGE_SPROUTED, BerryTree_EventScript_CheckBerryStage2
# 10 "data/scripts/berry_tree.pory"
	case BERRY_STAGE_TALLER, BerryTree_EventScript_CheckBerryStage3
# 11 "data/scripts/berry_tree.pory"
	case BERRY_STAGE_TRUNK, BerryTree_EventScript_CheckBerryStageTrunk
# 12 "data/scripts/berry_tree.pory"
	case BERRY_STAGE_BUDDING, BerryTree_EventScript_CheckBerryStageBudding
# 13 "data/scripts/berry_tree.pory"
	case BERRY_STAGE_FLOWERING, BerryTree_EventScript_CheckBerryStage4
# 14 "data/scripts/berry_tree.pory"
	case BERRY_STAGE_BERRIES, BerryTree_EventScript_CheckBerryFullyGrown
# 15 "data/scripts/berry_tree.pory"
	end
# 16 "data/scripts/berry_tree.pory"

# 17 "data/scripts/berry_tree.pory"
BerryTree_EventScript_Sparkling::
# 18 "data/scripts/berry_tree.pory"
	lockall
# 19 "data/scripts/berry_tree.pory"
	message BerryTree_Text_ExclamationPoint
# 20 "data/scripts/berry_tree.pory"
	waitmessage
# 21 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 22 "data/scripts/berry_tree.pory"
	releaseall
# 23 "data/scripts/berry_tree.pory"
	end
# 24 "data/scripts/berry_tree.pory"

# 25 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckSoil::
# 26 "data/scripts/berry_tree.pory"
	lock
# 27 "data/scripts/berry_tree.pory"
	faceplayer
# 28 "data/scripts/berry_tree.pory"
	specialvar VAR_RESULT, PlayerHasBerries
# 29 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, TRUE, BerryTree_EventScript_WantToPlant
# 30 "data/scripts/berry_tree.pory"
	specialvar VAR_RESULT, PlayerHasMulch
# 31 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, TRUE, BerryTree_EventScript_WantToMulch
# 32 "data/scripts/berry_tree.pory"
	message BerryTree_Text_ItsSoftLoamySoil
# 33 "data/scripts/berry_tree.pory"
	waitmessage
# 34 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 35 "data/scripts/berry_tree.pory"
	release
# 36 "data/scripts/berry_tree.pory"
	end
# 37 "data/scripts/berry_tree.pory"

# 38 "data/scripts/berry_tree.pory"

# 39 "data/scripts/berry_tree.pory"
BerryTree_EventScript_WantToMulch::
# 40 "data/scripts/berry_tree.pory"
.if OW_BERRY_MULCH_USAGE == TRUE
# 41 "data/scripts/berry_tree.pory"
	msgbox BerryTree_Text_WantToMulch, MSGBOX_YESNO
# 42 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, YES, BerryTree_EventScript_ChooseMulchToUse
# 43 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, NO, BerryTree_EventScript_CancelPlanting
# 44 "data/scripts/berry_tree.pory"
.endif
# 45 "data/scripts/berry_tree.pory"
	end
# 46 "data/scripts/berry_tree.pory"

# 47 "data/scripts/berry_tree.pory"
BerryTree_EventScript_WantToPlantMulch::
# 48 "data/scripts/berry_tree.pory"
.if OW_BERRY_MULCH_USAGE == TRUE
# 49 "data/scripts/berry_tree.pory"
	message BerryTree_Text_ItsSoftLoamySoil
# 50 "data/scripts/berry_tree.pory"
	waitmessage
# 51 "data/scripts/berry_tree.pory"
	multichoice 0, 0, MULTI_BERRY_PLOT, FALSE
# 52 "data/scripts/berry_tree.pory"
	switch VAR_RESULT
# 53 "data/scripts/berry_tree.pory"
	case 0, BerryTree_EventScript_ChooseMulchToUse
# 54 "data/scripts/berry_tree.pory"
	case 1, BerryTree_EventScript_ChooseBerryToPlant
# 55 "data/scripts/berry_tree.pory"
	case 2, BerryTree_EventScript_CancelPlanting
# 56 "data/scripts/berry_tree.pory"
	case MULTI_B_PRESSED, BerryTree_EventScript_CancelPlanting
# 57 "data/scripts/berry_tree.pory"

# 58 "data/scripts/berry_tree.pory"
BerryTree_EventScript_ChooseMulchToUse::
# 59 "data/scripts/berry_tree.pory"
	fadescreen FADE_TO_BLACK
# 60 "data/scripts/berry_tree.pory"
	closemessage
# 61 "data/scripts/berry_tree.pory"
	special Bag_ChooseMulch
# 62 "data/scripts/berry_tree.pory"
	waitstate
# 63 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_ITEM_ID, 0, BerryTree_EventScript_CancelPlanting
# 64 "data/scripts/berry_tree.pory"
	removeitem VAR_ITEM_ID
# 65 "data/scripts/berry_tree.pory"
	call BerryTree_EventScript_UseMulch
# 66 "data/scripts/berry_tree.pory"
.endif
# 67 "data/scripts/berry_tree.pory"

# 68 "data/scripts/berry_tree.pory"
BerryTree_EventScript_ChooseBerryToPlant::
# 69 "data/scripts/berry_tree.pory"
	fadescreen FADE_TO_BLACK
# 70 "data/scripts/berry_tree.pory"
	closemessage
# 71 "data/scripts/berry_tree.pory"
	special Bag_ChooseBerry
# 72 "data/scripts/berry_tree.pory"
	waitstate
# 73 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_ITEM_ID, 0, BerryTree_EventScript_CancelPlanting
# 74 "data/scripts/berry_tree.pory"
	removeitem VAR_ITEM_ID
# 75 "data/scripts/berry_tree.pory"
	call BerryTree_EventScript_PlantBerry
# 76 "data/scripts/berry_tree.pory"

# 77 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CancelPlanting::
# 78 "data/scripts/berry_tree.pory"
	release
# 79 "data/scripts/berry_tree.pory"
	end
# 80 "data/scripts/berry_tree.pory"

# 81 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckBerryStage1::
# 82 "data/scripts/berry_tree.pory"
	lockall
# 83 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryCountString
# 84 "data/scripts/berry_tree.pory"
	message BerryTree_Text_BerryGrowthStage1
# 85 "data/scripts/berry_tree.pory"
	waitmessage
# 86 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 87 "data/scripts/berry_tree.pory"
	goto BerryTree_EventScript_WantToWater
# 88 "data/scripts/berry_tree.pory"

# 89 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckBerryStage2::
# 90 "data/scripts/berry_tree.pory"
	lockall
# 91 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryName
# 92 "data/scripts/berry_tree.pory"
	message BerryTree_Text_BerryGrowthStage2
# 93 "data/scripts/berry_tree.pory"
	waitmessage
# 94 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 95 "data/scripts/berry_tree.pory"
	goto BerryTree_EventScript_WantToWater
# 96 "data/scripts/berry_tree.pory"

# 97 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckBerryStage3::
# 98 "data/scripts/berry_tree.pory"
	lockall
# 99 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryName
# 100 "data/scripts/berry_tree.pory"
	message BerryTree_Text_BerryGrowthStage3
# 101 "data/scripts/berry_tree.pory"
	waitmessage
# 102 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 103 "data/scripts/berry_tree.pory"
	goto BerryTree_EventScript_WantToWater
# 104 "data/scripts/berry_tree.pory"

# 105 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckBerryStageTrunk::
# 106 "data/scripts/berry_tree.pory"
	lockall
# 107 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryName
# 108 "data/scripts/berry_tree.pory"
	message BerryTree_Text_BerryGrowthStageTrunk
# 109 "data/scripts/berry_tree.pory"
	waitmessage
# 110 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 111 "data/scripts/berry_tree.pory"
	goto BerryTree_EventScript_WantToWater
# 112 "data/scripts/berry_tree.pory"

# 113 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckBerryStageBudding::
# 114 "data/scripts/berry_tree.pory"
	lockall
# 115 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryName
# 116 "data/scripts/berry_tree.pory"
	message BerryTree_Text_BerryGrowthStageBudding
# 117 "data/scripts/berry_tree.pory"
	waitmessage
# 118 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 119 "data/scripts/berry_tree.pory"
	goto BerryTree_EventScript_WantToWater
# 120 "data/scripts/berry_tree.pory"

# 121 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckBerryStage4::
# 122 "data/scripts/berry_tree.pory"
	call BerryTree_EventScript_GetCareAdverb
# 123 "data/scripts/berry_tree.pory"
	lockall
# 124 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryName
# 125 "data/scripts/berry_tree.pory"
	message BerryTree_Text_BerryGrowthStage4
# 126 "data/scripts/berry_tree.pory"
	waitmessage
# 127 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 128 "data/scripts/berry_tree.pory"
	goto BerryTree_EventScript_WantToWater
# 129 "data/scripts/berry_tree.pory"

# 130 "data/scripts/berry_tree.pory"
@ VAR_0x8005 here is the number of times watered
# 131 "data/scripts/berry_tree.pory"
@ Buffered by ObjectEventInteractionGetBerryTreeData
# 132 "data/scripts/berry_tree.pory"
BerryTree_EventScript_GetCareAdverb::
# 133 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_0x8005, 0, BerryTree_EventScript_SetAdverbPoor
# 134 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_0x8005, 4, BerryTree_EventScript_SetAdverbGreat
# 135 "data/scripts/berry_tree.pory"
	bufferstring STR_VAR_2, BerryTree_Text_CareAdverbGood
# 136 "data/scripts/berry_tree.pory"
	return
# 137 "data/scripts/berry_tree.pory"

# 138 "data/scripts/berry_tree.pory"
BerryTree_EventScript_SetAdverbGreat::
# 139 "data/scripts/berry_tree.pory"
	bufferstring STR_VAR_2, BerryTree_Text_CareAdverbGreat
# 140 "data/scripts/berry_tree.pory"
	return
# 141 "data/scripts/berry_tree.pory"

# 142 "data/scripts/berry_tree.pory"
BerryTree_EventScript_SetAdverbPoor::
# 143 "data/scripts/berry_tree.pory"
	bufferstring STR_VAR_2, BerryTree_Text_CareAdverbPoor
# 144 "data/scripts/berry_tree.pory"
	return
# 145 "data/scripts/berry_tree.pory"

# 146 "data/scripts/berry_tree.pory"
@ VAR_0x8006 here is the number of berries
# 147 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckBerryFullyGrown::
# 148 "data/scripts/berry_tree.pory"
	buffernumberstring STR_VAR_2, VAR_0x8006
# 149 "data/scripts/berry_tree.pory"
	lock
# 150 "data/scripts/berry_tree.pory"
	faceplayer
# 151 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryCountString
# 152 "data/scripts/berry_tree.pory"
.if OW_BERRY_MUTATIONS == TRUE
# 153 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, TRUE, BerryTree_EventScript_CheckBerryFullyGrown_Mutation
# 154 "data/scripts/berry_tree.pory"
.endif
# 155 "data/scripts/berry_tree.pory"
	msgbox BerryTree_Text_WantToPick, MSGBOX_YESNO
# 156 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, YES, BerryTree_EventScript_PickBerry
# 157 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, NO, BerryTree_EventScript_CancelPickingBerry
# 158 "data/scripts/berry_tree.pory"

# 159 "data/scripts/berry_tree.pory"
.set BERRY_NORMAL_BAG_FULL, 0
# 160 "data/scripts/berry_tree.pory"
.set BERRY_NORMAL_SPACE_IN_BAG, 1
# 161 "data/scripts/berry_tree.pory"
.set BERRY_MUTATION_BAG_FULL, 2
# 162 "data/scripts/berry_tree.pory"
.set BERRY_MUTATION_SPACE_IN_BAG, 3
# 163 "data/scripts/berry_tree.pory"

# 164 "data/scripts/berry_tree.pory"
BerryTree_EventScript_PickBerry::
# 165 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionPickBerryTree
# 166 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_0x8004, BERRY_NORMAL_BAG_FULL, BerryTree_EventScript_BerryPocketFull
# 167 "data/scripts/berry_tree.pory"
.if OW_BERRY_MUTATIONS == TRUE
# 168 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_0x8004, BERRY_MUTATION_BAG_FULL, BerryTree_EventScript_BerryPocketFull_Mutation
# 169 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_0x8004, BERRY_MUTATION_SPACE_IN_BAG, BerryTree_EventScript_PickBerry_Mutation
# 170 "data/scripts/berry_tree.pory"
.endif
# 171 "data/scripts/berry_tree.pory"
	special IncrementDailyPickedBerries
# 172 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionRemoveBerryTree
# 173 "data/scripts/berry_tree.pory"
	message BerryTree_Text_PickedTheBerry
# 174 "data/scripts/berry_tree.pory"
	playfanfare MUS_OBTAIN_BERRY
# 175 "data/scripts/berry_tree.pory"
	waitmessage
# 176 "data/scripts/berry_tree.pory"
	waitfanfare
# 177 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 178 "data/scripts/berry_tree.pory"
	message BerryTree_Text_PutAwayBerry
# 179 "data/scripts/berry_tree.pory"
	waitmessage
# 180 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 181 "data/scripts/berry_tree.pory"
	release
# 182 "data/scripts/berry_tree.pory"
	end
# 183 "data/scripts/berry_tree.pory"

# 184 "data/scripts/berry_tree.pory"
BerryTree_EventScript_BerryPocketFull::
# 185 "data/scripts/berry_tree.pory"
	message BerryTree_Text_BerryPocketFull
# 186 "data/scripts/berry_tree.pory"
	waitmessage
# 187 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 188 "data/scripts/berry_tree.pory"
	release
# 189 "data/scripts/berry_tree.pory"
	end
# 190 "data/scripts/berry_tree.pory"

# 191 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CancelPickingBerry::
# 192 "data/scripts/berry_tree.pory"
	message BerryTree_Text_BerryLeftUnpicked
# 193 "data/scripts/berry_tree.pory"
	waitmessage
# 194 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 195 "data/scripts/berry_tree.pory"
	release
# 196 "data/scripts/berry_tree.pory"
	end
# 197 "data/scripts/berry_tree.pory"

# 198 "data/scripts/berry_tree.pory"
BerryTree_EventScript_ItemUsePlantBerry::
# 199 "data/scripts/berry_tree.pory"
	lockall
# 200 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryTreeData
# 201 "data/scripts/berry_tree.pory"
	call BerryTree_EventScript_PlantBerry
# 202 "data/scripts/berry_tree.pory"
	releaseall
# 203 "data/scripts/berry_tree.pory"
	end
# 204 "data/scripts/berry_tree.pory"

# 205 "data/scripts/berry_tree.pory"
BerryTree_EventScript_WantToWater::
# 206 "data/scripts/berry_tree.pory"
.if OW_BERRY_PESTS == TRUE
# 207 "data/scripts/berry_tree.pory"
	call BerryTree_EventScript_CheckForPests
# 208 "data/scripts/berry_tree.pory"
.endif
# 209 "data/scripts/berry_tree.pory"
.if OW_BERRY_WEEDS == TRUE
# 210 "data/scripts/berry_tree.pory"
	call BerryTree_EventScript_CheckForWeed
# 211 "data/scripts/berry_tree.pory"
.endif
# 212 "data/scripts/berry_tree.pory"
	checkitem ITEM_WAILMER_PAIL
# 213 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, FALSE, BerryTree_EventScript_DontWater
# 214 "data/scripts/berry_tree.pory"
	specialvar VAR_RESULT, CanWaterBerryPlot
# 215 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, FALSE, BerryTree_EventScript_DontWater
# 216 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryName
# 217 "data/scripts/berry_tree.pory"
	msgbox BerryTree_Text_WantToWater, MSGBOX_YESNO
# 218 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, YES, BerryTree_EventScript_WaterBerry
# 219 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, NO, BerryTree_EventScript_DontWater
# 220 "data/scripts/berry_tree.pory"

# 221 "data/scripts/berry_tree.pory"
BerryTree_EventScript_DontWater::
# 222 "data/scripts/berry_tree.pory"
	releaseall
# 223 "data/scripts/berry_tree.pory"
	end
# 224 "data/scripts/berry_tree.pory"

# 225 "data/scripts/berry_tree.pory"
BerryTree_EventScript_ItemUseWailmerPail::
# 226 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryTreeData
# 227 "data/scripts/berry_tree.pory"
	lockall
# 228 "data/scripts/berry_tree.pory"
BerryTree_EventScript_WaterBerry::
# 229 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryName
# 230 "data/scripts/berry_tree.pory"
	message BerryTree_Text_WateredTheBerry
# 231 "data/scripts/berry_tree.pory"
	waitmessage
# 232 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionWaterBerryTree
# 233 "data/scripts/berry_tree.pory"
	special DoWateringBerryTreeAnim
# 234 "data/scripts/berry_tree.pory"
	waitstate
# 235 "data/scripts/berry_tree.pory"
	message BerryTree_Text_PlantIsDelighted
# 236 "data/scripts/berry_tree.pory"
	waitmessage
# 237 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 238 "data/scripts/berry_tree.pory"
	releaseall
# 239 "data/scripts/berry_tree.pory"
	end
# 240 "data/scripts/berry_tree.pory"

# 241 "data/scripts/berry_tree.pory"
BerryTree_EventScript_PlantBerry::
# 242 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionPlantBerryTree
# 243 "data/scripts/berry_tree.pory"
	incrementgamestat GAME_STAT_PLANTED_BERRIES
# 244 "data/scripts/berry_tree.pory"
	special IncrementDailyPlantedBerries
# 245 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryCountString
# 246 "data/scripts/berry_tree.pory"
	message BerryTree_Text_PlantedOneBerry
# 247 "data/scripts/berry_tree.pory"
	waitmessage
# 248 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 249 "data/scripts/berry_tree.pory"
	return
# 250 "data/scripts/berry_tree.pory"

# 251 "data/scripts/berry_tree.pory"
BerryTree_Text_ItsSoftLoamySoil:
# 252 "data/scripts/berry_tree.pory"
	.string "It's soft, loamy soil.$"
# 253 "data/scripts/berry_tree.pory"

# 254 "data/scripts/berry_tree.pory"
BerryTree_Text_WantToPlant:
# 255 "data/scripts/berry_tree.pory"
	.string "It's soft, loamy soil.\n"
# 256 "data/scripts/berry_tree.pory"
	.string "Want to plant a BERRY?$"
# 257 "data/scripts/berry_tree.pory"

# 258 "data/scripts/berry_tree.pory"
BerryTree_Text_PlantedOneBerry:
# 259 "data/scripts/berry_tree.pory"
	.string "{PLAYER} planted one {STR_VAR_1} in\n"
# 260 "data/scripts/berry_tree.pory"
	.string "the soft, loamy soil.$"
# 261 "data/scripts/berry_tree.pory"

# 262 "data/scripts/berry_tree.pory"
BerryTree_Text_BerryGrowthStage1:
# 263 "data/scripts/berry_tree.pory"
.if OW_BERRY_SIX_STAGES == TRUE
# 264 "data/scripts/berry_tree.pory"
	.string "This is where you planted the\n{STR_VAR_1}!$"
# 265 "data/scripts/berry_tree.pory"
.else
# 266 "data/scripts/berry_tree.pory"
	.string "One {STR_VAR_1} was planted here.$"
# 267 "data/scripts/berry_tree.pory"
.endif
# 268 "data/scripts/berry_tree.pory"

# 269 "data/scripts/berry_tree.pory"
BerryTree_Text_BerryGrowthStage2:
# 270 "data/scripts/berry_tree.pory"
.if OW_BERRY_SIX_STAGES == TRUE
# 271 "data/scripts/berry_tree.pory"
	.string "The {STR_VAR_1} is sprouting!$"
# 272 "data/scripts/berry_tree.pory"
.else
# 273 "data/scripts/berry_tree.pory"
	.string "{STR_VAR_1} has sprouted.$"
# 274 "data/scripts/berry_tree.pory"
.endif
# 275 "data/scripts/berry_tree.pory"

# 276 "data/scripts/berry_tree.pory"
BerryTree_Text_BerryGrowthStage3:
# 277 "data/scripts/berry_tree.pory"
.if OW_BERRY_SIX_STAGES == TRUE
# 278 "data/scripts/berry_tree.pory"
	.string "The {STR_VAR_1}'s seedling is growing well!$"
# 279 "data/scripts/berry_tree.pory"
.else
# 280 "data/scripts/berry_tree.pory"
	.string "This {STR_VAR_1} plant is growing taller.$"
# 281 "data/scripts/berry_tree.pory"
.endif
# 282 "data/scripts/berry_tree.pory"

# 283 "data/scripts/berry_tree.pory"
BerryTree_Text_BerryGrowthStageTrunk:
# 284 "data/scripts/berry_tree.pory"
	.string "The {STR_VAR_1}'s trunk is getting bigger!$"
# 285 "data/scripts/berry_tree.pory"

# 286 "data/scripts/berry_tree.pory"
BerryTree_Text_BerryGrowthStageBudding:
# 287 "data/scripts/berry_tree.pory"
	.string "The {STR_VAR_1} tree has buds!$"
# 288 "data/scripts/berry_tree.pory"

# 289 "data/scripts/berry_tree.pory"
BerryTree_Text_BerryGrowthStage4:
# 290 "data/scripts/berry_tree.pory"
.if OW_BERRY_SIX_STAGES == TRUE
# 291 "data/scripts/berry_tree.pory"
	.string "The {STR_VAR_1} tree is in bloom!$"
# 292 "data/scripts/berry_tree.pory"
.else
# 293 "data/scripts/berry_tree.pory"
	.string "These {STR_VAR_1} flowers are blooming\n"
# 294 "data/scripts/berry_tree.pory"
	.string "{STR_VAR_2}.$"
# 295 "data/scripts/berry_tree.pory"
.endif
# 296 "data/scripts/berry_tree.pory"

# 297 "data/scripts/berry_tree.pory"
BerryTree_Text_CareAdverbGreat:
# 298 "data/scripts/berry_tree.pory"
	.string "very beautifully$"
# 299 "data/scripts/berry_tree.pory"

# 300 "data/scripts/berry_tree.pory"
BerryTree_Text_CareAdverbPoor:
# 301 "data/scripts/berry_tree.pory"
	.string "cutely$"
# 302 "data/scripts/berry_tree.pory"

# 303 "data/scripts/berry_tree.pory"
BerryTree_Text_CareAdverbGood:
# 304 "data/scripts/berry_tree.pory"
	.string "prettily$"
# 305 "data/scripts/berry_tree.pory"

# 306 "data/scripts/berry_tree.pory"
BerryTree_Text_WantToPick:
# 307 "data/scripts/berry_tree.pory"
	.string "You found {STR_VAR_2} {STR_VAR_1}!\p"
# 308 "data/scripts/berry_tree.pory"
	.string "Do you want to pick the\n"
# 309 "data/scripts/berry_tree.pory"
	.string "{STR_VAR_1}?$"
# 310 "data/scripts/berry_tree.pory"

# 311 "data/scripts/berry_tree.pory"
BerryTree_Text_PickedTheBerry:
# 312 "data/scripts/berry_tree.pory"
	.string "{PLAYER} picked the {STR_VAR_2} {STR_VAR_1}.$"
# 313 "data/scripts/berry_tree.pory"

# 314 "data/scripts/berry_tree.pory"
BerryTree_Text_PutAwayBerry:
# 315 "data/scripts/berry_tree.pory"
	.string "{PLAYER} put away the {STR_VAR_1}\n"
# 316 "data/scripts/berry_tree.pory"
	.string "in the BAG's BERRIES POCKET.\p"
# 317 "data/scripts/berry_tree.pory"
	.string "The soil returned to its soft and\n"
# 318 "data/scripts/berry_tree.pory"
	.string "loamy state.$"
# 319 "data/scripts/berry_tree.pory"

# 320 "data/scripts/berry_tree.pory"
BerryTree_Text_BerryPocketFull:
# 321 "data/scripts/berry_tree.pory"
	.string "The BAG's BERRIES POCKET is full.\p"
# 322 "data/scripts/berry_tree.pory"
	.string "The {STR_VAR_1} couldn't be taken.$"
# 323 "data/scripts/berry_tree.pory"

# 324 "data/scripts/berry_tree.pory"
BerryTree_Text_BerryLeftUnpicked:
# 325 "data/scripts/berry_tree.pory"
	.string "{PLAYER} left the {STR_VAR_1}\n"
# 326 "data/scripts/berry_tree.pory"
	.string "unpicked.$"
# 327 "data/scripts/berry_tree.pory"

# 328 "data/scripts/berry_tree.pory"
BerryTree_Text_WantToWater:
# 329 "data/scripts/berry_tree.pory"
	.string "Want to water the {STR_VAR_1} with the\n"
# 330 "data/scripts/berry_tree.pory"
	.string "WAILMER PAIL?$"
# 331 "data/scripts/berry_tree.pory"

# 332 "data/scripts/berry_tree.pory"
BerryTree_Text_WateredTheBerry:
# 333 "data/scripts/berry_tree.pory"
	.string "{PLAYER} watered the {STR_VAR_1}.$"
# 334 "data/scripts/berry_tree.pory"

# 335 "data/scripts/berry_tree.pory"
BerryTree_Text_PlantIsDelighted:
# 336 "data/scripts/berry_tree.pory"
	.string "The plant seems to be delighted.$"
# 337 "data/scripts/berry_tree.pory"

# 338 "data/scripts/berry_tree.pory"
BerryTree_Text_ExclamationPoint:
# 339 "data/scripts/berry_tree.pory"
	.string "!$"
# 340 "data/scripts/berry_tree.pory"

# 341 "data/scripts/berry_tree.pory"
.if OW_BERRY_MUTATIONS == TRUE
# 342 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckBerryFullyGrown_Mutation:
# 343 "data/scripts/berry_tree.pory"
	msgbox BerryTree_Text_WantToPick_Mutation, MSGBOX_YESNO
# 344 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, YES, BerryTree_EventScript_PickBerry
# 345 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, NO, BerryTree_EventScript_CancelPickingBerry_Mutation
# 346 "data/scripts/berry_tree.pory"

# 347 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CancelPickingBerry_Mutation::
# 348 "data/scripts/berry_tree.pory"
	message BerryTree_Text_BerryLeftUnpicked_Mutation
# 349 "data/scripts/berry_tree.pory"
	waitmessage
# 350 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 351 "data/scripts/berry_tree.pory"
	release
# 352 "data/scripts/berry_tree.pory"
	end
# 353 "data/scripts/berry_tree.pory"

# 354 "data/scripts/berry_tree.pory"
BerryTree_EventScript_BerryPocketFull_Mutation::
# 355 "data/scripts/berry_tree.pory"
	message BerryTree_Text_BerryPocketFull_Mutation
# 356 "data/scripts/berry_tree.pory"
	waitmessage
# 357 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 358 "data/scripts/berry_tree.pory"
	release
# 359 "data/scripts/berry_tree.pory"
	end
# 360 "data/scripts/berry_tree.pory"

# 361 "data/scripts/berry_tree.pory"
BerryTree_EventScript_PickBerry_Mutation::
# 362 "data/scripts/berry_tree.pory"
	special IncrementDailyPickedBerries
# 363 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionRemoveBerryTree
# 364 "data/scripts/berry_tree.pory"
	message BerryTree_Text_PickedTheBerry_Mutation
# 365 "data/scripts/berry_tree.pory"
	playfanfare MUS_OBTAIN_BERRY
# 366 "data/scripts/berry_tree.pory"
	waitmessage
# 367 "data/scripts/berry_tree.pory"
	waitfanfare
# 368 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 369 "data/scripts/berry_tree.pory"
	message BerryTree_Text_PutAwayBerry_Mutation
# 370 "data/scripts/berry_tree.pory"
	waitmessage
# 371 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 372 "data/scripts/berry_tree.pory"
	release
# 373 "data/scripts/berry_tree.pory"
	end
# 374 "data/scripts/berry_tree.pory"

# 375 "data/scripts/berry_tree.pory"
BerryTree_Text_WantToPick_Mutation:
# 376 "data/scripts/berry_tree.pory"
	.string "You found {STR_VAR_2} {STR_VAR_1}\n"
# 377 "data/scripts/berry_tree.pory"
	.string "and 1 {STR_VAR_3}!\p"
# 378 "data/scripts/berry_tree.pory"
	.string "Do you want to pick them?$"
# 379 "data/scripts/berry_tree.pory"

# 380 "data/scripts/berry_tree.pory"
BerryTree_Text_BerryLeftUnpicked_Mutation:
# 381 "data/scripts/berry_tree.pory"
	.string "{PLAYER} left the {STR_VAR_1}\n"
# 382 "data/scripts/berry_tree.pory"
	.string "and the {STR_VAR_3} unpicked.$"
# 383 "data/scripts/berry_tree.pory"

# 384 "data/scripts/berry_tree.pory"
BerryTree_Text_BerryPocketFull_Mutation:
# 385 "data/scripts/berry_tree.pory"
	.string "The BAG's BERRIES POCKET is full.\p"
# 386 "data/scripts/berry_tree.pory"
	.string "The {STR_VAR_1} and the\n"
# 387 "data/scripts/berry_tree.pory"
	.string "{STR_VAR_3} couldn't be taken.$"
# 388 "data/scripts/berry_tree.pory"

# 389 "data/scripts/berry_tree.pory"
BerryTree_Text_PickedTheBerry_Mutation:
# 390 "data/scripts/berry_tree.pory"
	.string "{PLAYER} picked the {STR_VAR_2} {STR_VAR_1}\n"
# 391 "data/scripts/berry_tree.pory"
	.string "and the {STR_VAR_3}.$"
# 392 "data/scripts/berry_tree.pory"

# 393 "data/scripts/berry_tree.pory"
BerryTree_Text_PutAwayBerry_Mutation:
# 394 "data/scripts/berry_tree.pory"
	.string "{PLAYER} put away the {STR_VAR_1}\n"
# 395 "data/scripts/berry_tree.pory"
	.string "and the {STR_VAR_3} in the BAG's\l"
# 396 "data/scripts/berry_tree.pory"
	.string "BERRIES POCKET.\p"
# 397 "data/scripts/berry_tree.pory"
	.string "The soil returned to its soft and\n"
# 398 "data/scripts/berry_tree.pory"
	.string "loamy state.$"
# 399 "data/scripts/berry_tree.pory"
.endif
# 400 "data/scripts/berry_tree.pory"

# 401 "data/scripts/berry_tree.pory"
.if OW_BERRY_MULCH_USAGE == TRUE
# 402 "data/scripts/berry_tree.pory"
BerryTree_EventScript_UseMulch::
# 403 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionApplyMulch
# 404 "data/scripts/berry_tree.pory"
	message BerryTree_Text_ScatteredMulch
# 405 "data/scripts/berry_tree.pory"
	waitmessage
# 406 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 407 "data/scripts/berry_tree.pory"
	return
# 408 "data/scripts/berry_tree.pory"

# 409 "data/scripts/berry_tree.pory"
BerryTree_Text_WantToMulch:
# 410 "data/scripts/berry_tree.pory"
	.string "It's soft, loamy soil.\n"
# 411 "data/scripts/berry_tree.pory"
	.string "Put down some fertilizer?$"
# 412 "data/scripts/berry_tree.pory"

# 413 "data/scripts/berry_tree.pory"
BerryTree_Text_ScatteredMulch:
# 414 "data/scripts/berry_tree.pory"
	.string "{PLAYER} scattered the {STR_VAR_1}\n"
# 415 "data/scripts/berry_tree.pory"
	.string "on the soft, loamy soil.$"
# 416 "data/scripts/berry_tree.pory"
.endif
# 417 "data/scripts/berry_tree.pory"

# 418 "data/scripts/berry_tree.pory"
.if OW_BERRY_WEEDS == TRUE
# 419 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckForWeed::
# 420 "data/scripts/berry_tree.pory"
	specialvar VAR_RESULT, ObjectEventInteractionBerryHasWeed
# 421 "data/scripts/berry_tree.pory"
	call_if_eq VAR_RESULT, TRUE, BerryTree_EventScript_WeedIsGrowing
# 422 "data/scripts/berry_tree.pory"
	return
# 423 "data/scripts/berry_tree.pory"

# 424 "data/scripts/berry_tree.pory"
BerryTree_EventScript_WeedIsGrowing::
# 425 "data/scripts/berry_tree.pory"
	msgbox BerryTree_Text_WeedIsGrowing, MSGBOX_YESNO
# 426 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, YES, BerryTree_EventScript_PullOutWeed
# 427 "data/scripts/berry_tree.pory"
	return
# 428 "data/scripts/berry_tree.pory"

# 429 "data/scripts/berry_tree.pory"
BerryTree_EventScript_PullOutWeed::
# 430 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionPullBerryWeed
# 431 "data/scripts/berry_tree.pory"
	message BerryTree_Text_PulledOutTheWeed
# 432 "data/scripts/berry_tree.pory"
	waitmessage
# 433 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 434 "data/scripts/berry_tree.pory"
	return
# 435 "data/scripts/berry_tree.pory"

# 436 "data/scripts/berry_tree.pory"
BerryTree_Text_WeedIsGrowing:
# 437 "data/scripts/berry_tree.pory"
	.string "A weed is growing here.\n"
# 438 "data/scripts/berry_tree.pory"
	.string "Do you want to pull it out?$"
# 439 "data/scripts/berry_tree.pory"

# 440 "data/scripts/berry_tree.pory"
BerryTree_Text_PulledOutTheWeed:
# 441 "data/scripts/berry_tree.pory"
	.string "{PLAYER} pulled out the weed!$"
# 442 "data/scripts/berry_tree.pory"
.endif
# 443 "data/scripts/berry_tree.pory"

# 444 "data/scripts/berry_tree.pory"
.if OW_BERRY_PESTS == TRUE
# 445 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckForPests::
# 446 "data/scripts/berry_tree.pory"
	specialvar VAR_RESULT, ObjectEventInteractionBerryHasPests
# 447 "data/scripts/berry_tree.pory"
	call_if_eq VAR_RESULT, TRUE, BerryTree_EventScript_EncounterPests
# 448 "data/scripts/berry_tree.pory"
	return
# 449 "data/scripts/berry_tree.pory"

# 450 "data/scripts/berry_tree.pory"
BerryTree_EventScript_EncounterPests::
# 451 "data/scripts/berry_tree.pory"
	message BerryTree_Text_APokemonAppeared
# 452 "data/scripts/berry_tree.pory"
	waitmessage
# 453 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 454 "data/scripts/berry_tree.pory"
	dowildbattle
# 455 "data/scripts/berry_tree.pory"
	return
# 456 "data/scripts/berry_tree.pory"

# 457 "data/scripts/berry_tree.pory"
BerryTree_Text_APokemonAppeared:
# 458 "data/scripts/berry_tree.pory"
	.string "A Pokémon appeared!$"
# 459 "data/scripts/berry_tree.pory"
.endif

BerryTree_EventScript_WantToPlant::
# 464 "data/scripts/berry_tree.pory"
	goto_if_unset FLAG_RESOURCE_MODE, BerryTree_EventScript_WantToPlant_2
BerryTree_EventScript_WantToPlant_1:
	end

BerryTree_EventScript_WantToPlant_2:
# 465 "data/scripts/berry_tree.pory"
	specialvar VAR_RESULT, PlayerHasMulch
# 466 "data/scripts/berry_tree.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq BerryTree_EventScript_WantToPlant_5
BerryTree_EventScript_WantToPlant_4:
# 469 "data/scripts/berry_tree.pory"
	msgbox BerryTree_Text_WantToPlant, MSGBOX_YESNO
# 470 "data/scripts/berry_tree.pory"
	compare VAR_RESULT, YES
	goto_if_eq BerryTree_EventScript_WantToPlant_7
# 472 "data/scripts/berry_tree.pory"
	compare VAR_RESULT, NO
	goto_if_eq BerryTree_EventScript_WantToPlant_8
	goto BerryTree_EventScript_WantToPlant_1

BerryTree_EventScript_WantToPlant_5:
# 467 "data/scripts/berry_tree.pory"
	goto BerryTree_EventScript_WantToPlantMulch
	goto BerryTree_EventScript_WantToPlant_4

BerryTree_EventScript_WantToPlant_7:
# 471 "data/scripts/berry_tree.pory"
	goto BerryTree_EventScript_ChooseBerryToPlant
	goto BerryTree_EventScript_WantToPlant_1

BerryTree_EventScript_WantToPlant_8:
# 473 "data/scripts/berry_tree.pory"
	goto BerryTree_EventScript_CancelPlanting
	goto BerryTree_EventScript_WantToPlant_1

