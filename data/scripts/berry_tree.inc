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
BerryTree_EventScript_WantToMulch::
# 39 "data/scripts/berry_tree.pory"
.if OW_BERRY_MULCH_USAGE == TRUE
# 40 "data/scripts/berry_tree.pory"
	msgbox BerryTree_Text_WantToMulch, MSGBOX_YESNO
# 41 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, YES, BerryTree_EventScript_ChooseMulchToUse
# 42 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, NO, BerryTree_EventScript_CancelPlanting
# 43 "data/scripts/berry_tree.pory"
.endif
# 44 "data/scripts/berry_tree.pory"
	end
# 45 "data/scripts/berry_tree.pory"

# 46 "data/scripts/berry_tree.pory"
BerryTree_EventScript_WantToPlantMulch::
# 47 "data/scripts/berry_tree.pory"
.if OW_BERRY_MULCH_USAGE == TRUE
# 48 "data/scripts/berry_tree.pory"
	message BerryTree_Text_ItsSoftLoamySoil
# 49 "data/scripts/berry_tree.pory"
	waitmessage
# 50 "data/scripts/berry_tree.pory"
	multichoice 0, 0, MULTI_BERRY_PLOT, FALSE
# 51 "data/scripts/berry_tree.pory"
	switch VAR_RESULT
# 52 "data/scripts/berry_tree.pory"
	case 0, BerryTree_EventScript_ChooseMulchToUse
# 53 "data/scripts/berry_tree.pory"
	case 1, BerryTree_EventScript_ChooseBerryToPlant
# 54 "data/scripts/berry_tree.pory"
	case 2, BerryTree_EventScript_CancelPlanting
# 55 "data/scripts/berry_tree.pory"
	case MULTI_B_PRESSED, BerryTree_EventScript_CancelPlanting
# 56 "data/scripts/berry_tree.pory"

# 57 "data/scripts/berry_tree.pory"
BerryTree_EventScript_ChooseMulchToUse::
# 58 "data/scripts/berry_tree.pory"
	fadescreen FADE_TO_BLACK
# 59 "data/scripts/berry_tree.pory"
	closemessage
# 60 "data/scripts/berry_tree.pory"
	special Bag_ChooseMulch
# 61 "data/scripts/berry_tree.pory"
	waitstate
# 62 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_ITEM_ID, 0, BerryTree_EventScript_CancelPlanting
# 63 "data/scripts/berry_tree.pory"
	removeitem VAR_ITEM_ID
# 64 "data/scripts/berry_tree.pory"
	call BerryTree_EventScript_UseMulch
# 65 "data/scripts/berry_tree.pory"
.endif
# 66 "data/scripts/berry_tree.pory"

# 67 "data/scripts/berry_tree.pory"
BerryTree_EventScript_ChooseBerryToPlant::
# 68 "data/scripts/berry_tree.pory"
	fadescreen FADE_TO_BLACK
# 69 "data/scripts/berry_tree.pory"
	closemessage
# 70 "data/scripts/berry_tree.pory"
	special Bag_ChooseBerry
# 71 "data/scripts/berry_tree.pory"
	waitstate
# 72 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_ITEM_ID, 0, BerryTree_EventScript_CancelPlanting
# 73 "data/scripts/berry_tree.pory"
	removeitem VAR_ITEM_ID
# 74 "data/scripts/berry_tree.pory"
	call BerryTree_EventScript_PlantBerry
# 75 "data/scripts/berry_tree.pory"

# 76 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CancelPlanting::
# 77 "data/scripts/berry_tree.pory"
	release
# 78 "data/scripts/berry_tree.pory"
	end
# 79 "data/scripts/berry_tree.pory"

# 80 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckBerryStage1::
# 81 "data/scripts/berry_tree.pory"
	lockall
# 82 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryCountString
# 83 "data/scripts/berry_tree.pory"
	message BerryTree_Text_BerryGrowthStage1
# 84 "data/scripts/berry_tree.pory"
	waitmessage
# 85 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 86 "data/scripts/berry_tree.pory"
	goto BerryTree_EventScript_WantToWater
# 87 "data/scripts/berry_tree.pory"

# 88 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckBerryStage2::
# 89 "data/scripts/berry_tree.pory"
	lockall
# 90 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryName
# 91 "data/scripts/berry_tree.pory"
	message BerryTree_Text_BerryGrowthStage2
# 92 "data/scripts/berry_tree.pory"
	waitmessage
# 93 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 94 "data/scripts/berry_tree.pory"
	goto BerryTree_EventScript_WantToWater
# 95 "data/scripts/berry_tree.pory"

# 96 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckBerryStage3::
# 97 "data/scripts/berry_tree.pory"
	lockall
# 98 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryName
# 99 "data/scripts/berry_tree.pory"
	message BerryTree_Text_BerryGrowthStage3
# 100 "data/scripts/berry_tree.pory"
	waitmessage
# 101 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 102 "data/scripts/berry_tree.pory"
	goto BerryTree_EventScript_WantToWater
# 103 "data/scripts/berry_tree.pory"

# 104 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckBerryStageTrunk::
# 105 "data/scripts/berry_tree.pory"
	lockall
# 106 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryName
# 107 "data/scripts/berry_tree.pory"
	message BerryTree_Text_BerryGrowthStageTrunk
# 108 "data/scripts/berry_tree.pory"
	waitmessage
# 109 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 110 "data/scripts/berry_tree.pory"
	goto BerryTree_EventScript_WantToWater
# 111 "data/scripts/berry_tree.pory"

# 112 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckBerryStageBudding::
# 113 "data/scripts/berry_tree.pory"
	lockall
# 114 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryName
# 115 "data/scripts/berry_tree.pory"
	message BerryTree_Text_BerryGrowthStageBudding
# 116 "data/scripts/berry_tree.pory"
	waitmessage
# 117 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 118 "data/scripts/berry_tree.pory"
	goto BerryTree_EventScript_WantToWater
# 119 "data/scripts/berry_tree.pory"

# 120 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckBerryStage4::
# 121 "data/scripts/berry_tree.pory"
	call BerryTree_EventScript_GetCareAdverb
# 122 "data/scripts/berry_tree.pory"
	lockall
# 123 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryName
# 124 "data/scripts/berry_tree.pory"
	message BerryTree_Text_BerryGrowthStage4
# 125 "data/scripts/berry_tree.pory"
	waitmessage
# 126 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 127 "data/scripts/berry_tree.pory"
	goto BerryTree_EventScript_WantToWater
# 128 "data/scripts/berry_tree.pory"

# 129 "data/scripts/berry_tree.pory"
@ VAR_0x8005 here is the number of times watered
# 130 "data/scripts/berry_tree.pory"
@ Buffered by ObjectEventInteractionGetBerryTreeData
# 131 "data/scripts/berry_tree.pory"
BerryTree_EventScript_GetCareAdverb::
# 132 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_0x8005, 0, BerryTree_EventScript_SetAdverbPoor
# 133 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_0x8005, 4, BerryTree_EventScript_SetAdverbGreat
# 134 "data/scripts/berry_tree.pory"
	bufferstring STR_VAR_2, BerryTree_Text_CareAdverbGood
# 135 "data/scripts/berry_tree.pory"
	return
# 136 "data/scripts/berry_tree.pory"

# 137 "data/scripts/berry_tree.pory"
BerryTree_EventScript_SetAdverbGreat::
# 138 "data/scripts/berry_tree.pory"
	bufferstring STR_VAR_2, BerryTree_Text_CareAdverbGreat
# 139 "data/scripts/berry_tree.pory"
	return
# 140 "data/scripts/berry_tree.pory"

# 141 "data/scripts/berry_tree.pory"
BerryTree_EventScript_SetAdverbPoor::
# 142 "data/scripts/berry_tree.pory"
	bufferstring STR_VAR_2, BerryTree_Text_CareAdverbPoor
# 143 "data/scripts/berry_tree.pory"
	return
# 144 "data/scripts/berry_tree.pory"

# 145 "data/scripts/berry_tree.pory"
@ VAR_0x8006 here is the number of berries
# 146 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckBerryFullyGrown::
# 147 "data/scripts/berry_tree.pory"
	buffernumberstring STR_VAR_2, VAR_0x8006
# 148 "data/scripts/berry_tree.pory"
	lock
# 149 "data/scripts/berry_tree.pory"
	faceplayer
# 150 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryCountString
# 151 "data/scripts/berry_tree.pory"
.if OW_BERRY_MUTATIONS == TRUE
# 152 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, TRUE, BerryTree_EventScript_CheckBerryFullyGrown_Mutation
# 153 "data/scripts/berry_tree.pory"
.endif
# 154 "data/scripts/berry_tree.pory"
	msgbox BerryTree_Text_WantToPick, MSGBOX_YESNO
# 155 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, YES, BerryTree_EventScript_PickBerry
# 156 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, NO, BerryTree_EventScript_CancelPickingBerry
# 157 "data/scripts/berry_tree.pory"

# 158 "data/scripts/berry_tree.pory"
.set BERRY_NORMAL_BAG_FULL, 0
# 159 "data/scripts/berry_tree.pory"
.set BERRY_NORMAL_SPACE_IN_BAG, 1
# 160 "data/scripts/berry_tree.pory"
.set BERRY_MUTATION_BAG_FULL, 2
# 161 "data/scripts/berry_tree.pory"
.set BERRY_MUTATION_SPACE_IN_BAG, 3
# 162 "data/scripts/berry_tree.pory"

# 163 "data/scripts/berry_tree.pory"
BerryTree_EventScript_PickBerry::
# 164 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionPickBerryTree
# 165 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_0x8004, BERRY_NORMAL_BAG_FULL, BerryTree_EventScript_BerryPocketFull
# 166 "data/scripts/berry_tree.pory"
.if OW_BERRY_MUTATIONS == TRUE
# 167 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_0x8004, BERRY_MUTATION_BAG_FULL, BerryTree_EventScript_BerryPocketFull_Mutation
# 168 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_0x8004, BERRY_MUTATION_SPACE_IN_BAG, BerryTree_EventScript_PickBerry_Mutation
# 169 "data/scripts/berry_tree.pory"
.endif
# 170 "data/scripts/berry_tree.pory"
	special IncrementDailyPickedBerries
# 171 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionRemoveBerryTree
# 172 "data/scripts/berry_tree.pory"
	message BerryTree_Text_PickedTheBerry
# 173 "data/scripts/berry_tree.pory"
	delay 10
# 174 "data/scripts/berry_tree.pory"
	showberrydescription
# 175 "data/scripts/berry_tree.pory"
	playfanfare MUS_OBTAIN_BERRY
# 176 "data/scripts/berry_tree.pory"
	waitmessage
# 177 "data/scripts/berry_tree.pory"
	waitfanfare
# 178 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 179 "data/scripts/berry_tree.pory"
	message BerryTree_Text_PutAwayBerry
# 180 "data/scripts/berry_tree.pory"
	waitmessage
# 181 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 182 "data/scripts/berry_tree.pory"
	hideitemdescription
# 183 "data/scripts/berry_tree.pory"
	release
# 184 "data/scripts/berry_tree.pory"
	end
# 185 "data/scripts/berry_tree.pory"

# 186 "data/scripts/berry_tree.pory"
BerryTree_EventScript_BerryPocketFull::
# 187 "data/scripts/berry_tree.pory"
	message BerryTree_Text_BerryPocketFull
# 188 "data/scripts/berry_tree.pory"
	waitmessage
# 189 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 190 "data/scripts/berry_tree.pory"
	release
# 191 "data/scripts/berry_tree.pory"
	end
# 192 "data/scripts/berry_tree.pory"

# 193 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CancelPickingBerry::
# 194 "data/scripts/berry_tree.pory"
	message BerryTree_Text_BerryLeftUnpicked
# 195 "data/scripts/berry_tree.pory"
	waitmessage
# 196 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 197 "data/scripts/berry_tree.pory"
	release
# 198 "data/scripts/berry_tree.pory"
	end
# 199 "data/scripts/berry_tree.pory"

# 200 "data/scripts/berry_tree.pory"
BerryTree_EventScript_ItemUsePlantBerry::
# 201 "data/scripts/berry_tree.pory"
	lockall
# 202 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryTreeData
# 203 "data/scripts/berry_tree.pory"
	call BerryTree_EventScript_PlantBerry
# 204 "data/scripts/berry_tree.pory"
	releaseall
# 205 "data/scripts/berry_tree.pory"
	end
# 206 "data/scripts/berry_tree.pory"

# 207 "data/scripts/berry_tree.pory"
BerryTree_EventScript_WantToWater::
# 208 "data/scripts/berry_tree.pory"
.if OW_BERRY_PESTS == TRUE
# 209 "data/scripts/berry_tree.pory"
	call BerryTree_EventScript_CheckForPests
# 210 "data/scripts/berry_tree.pory"
.endif
# 211 "data/scripts/berry_tree.pory"
.if OW_BERRY_WEEDS == TRUE
# 212 "data/scripts/berry_tree.pory"
	call BerryTree_EventScript_CheckForWeed
# 213 "data/scripts/berry_tree.pory"
.endif
# 214 "data/scripts/berry_tree.pory"
	checkitem ITEM_WAILMER_PAIL
# 215 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, FALSE, BerryTree_EventScript_DontWater
# 216 "data/scripts/berry_tree.pory"
	specialvar VAR_RESULT, CanWaterBerryPlot
# 217 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, FALSE, BerryTree_EventScript_DontWater
# 218 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryName
# 219 "data/scripts/berry_tree.pory"
	msgbox BerryTree_Text_WantToWater, MSGBOX_YESNO
# 220 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, YES, BerryTree_EventScript_WaterBerry
# 221 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, NO, BerryTree_EventScript_DontWater
# 222 "data/scripts/berry_tree.pory"

# 223 "data/scripts/berry_tree.pory"
BerryTree_EventScript_DontWater::
# 224 "data/scripts/berry_tree.pory"
	releaseall
# 225 "data/scripts/berry_tree.pory"
	end
# 226 "data/scripts/berry_tree.pory"

# 227 "data/scripts/berry_tree.pory"
BerryTree_EventScript_ItemUseWailmerPail::
# 228 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryTreeData
# 229 "data/scripts/berry_tree.pory"
	lockall
# 230 "data/scripts/berry_tree.pory"
BerryTree_EventScript_WaterBerry::
# 231 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryName
# 232 "data/scripts/berry_tree.pory"
	message BerryTree_Text_WateredTheBerry
# 233 "data/scripts/berry_tree.pory"
	waitmessage
# 234 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionWaterBerryTree
# 235 "data/scripts/berry_tree.pory"
	special DoWateringBerryTreeAnim
# 236 "data/scripts/berry_tree.pory"
	waitstate
# 237 "data/scripts/berry_tree.pory"
	message BerryTree_Text_PlantIsDelighted
# 238 "data/scripts/berry_tree.pory"
	waitmessage
# 239 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 240 "data/scripts/berry_tree.pory"
	releaseall
# 241 "data/scripts/berry_tree.pory"
	end
# 242 "data/scripts/berry_tree.pory"

# 243 "data/scripts/berry_tree.pory"
BerryTree_EventScript_PlantBerry::
# 244 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionPlantBerryTree
# 245 "data/scripts/berry_tree.pory"
	incrementgamestat GAME_STAT_PLANTED_BERRIES
# 246 "data/scripts/berry_tree.pory"
	special IncrementDailyPlantedBerries
# 247 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionGetBerryCountString
# 248 "data/scripts/berry_tree.pory"
	message BerryTree_Text_PlantedOneBerry
# 249 "data/scripts/berry_tree.pory"
	waitmessage
# 250 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 251 "data/scripts/berry_tree.pory"
	return
# 252 "data/scripts/berry_tree.pory"

# 253 "data/scripts/berry_tree.pory"
BerryTree_Text_ItsSoftLoamySoil:
# 254 "data/scripts/berry_tree.pory"
	.string "It's soft, loamy soil.$"
# 255 "data/scripts/berry_tree.pory"

# 256 "data/scripts/berry_tree.pory"
BerryTree_Text_WantToPlant:
# 257 "data/scripts/berry_tree.pory"
	.string "It's soft, loamy soil.\n"
# 258 "data/scripts/berry_tree.pory"
	.string "Want to plant a BERRY?$"
# 259 "data/scripts/berry_tree.pory"

# 260 "data/scripts/berry_tree.pory"
BerryTree_Text_PlantedOneBerry:
# 261 "data/scripts/berry_tree.pory"
	.string "{PLAYER} planted one {STR_VAR_1} in\n"
# 262 "data/scripts/berry_tree.pory"
	.string "the soft, loamy soil.$"
# 263 "data/scripts/berry_tree.pory"

# 264 "data/scripts/berry_tree.pory"
BerryTree_Text_BerryGrowthStage1:
# 265 "data/scripts/berry_tree.pory"
.if OW_BERRY_SIX_STAGES == TRUE
# 266 "data/scripts/berry_tree.pory"
	.string "This is where you planted the\n{STR_VAR_1}!$"
# 267 "data/scripts/berry_tree.pory"
.else
# 268 "data/scripts/berry_tree.pory"
	.string "One {STR_VAR_1} was planted here.$"
# 269 "data/scripts/berry_tree.pory"
.endif
# 270 "data/scripts/berry_tree.pory"

# 271 "data/scripts/berry_tree.pory"
BerryTree_Text_BerryGrowthStage2:
# 272 "data/scripts/berry_tree.pory"
.if OW_BERRY_SIX_STAGES == TRUE
# 273 "data/scripts/berry_tree.pory"
	.string "The {STR_VAR_1} is sprouting!$"
# 274 "data/scripts/berry_tree.pory"
.else
# 275 "data/scripts/berry_tree.pory"
	.string "{STR_VAR_1} has sprouted.$"
# 276 "data/scripts/berry_tree.pory"
.endif
# 277 "data/scripts/berry_tree.pory"

# 278 "data/scripts/berry_tree.pory"
BerryTree_Text_BerryGrowthStage3:
# 279 "data/scripts/berry_tree.pory"
.if OW_BERRY_SIX_STAGES == TRUE
# 280 "data/scripts/berry_tree.pory"
	.string "The {STR_VAR_1}'s seedling is growing well!$"
# 281 "data/scripts/berry_tree.pory"
.else
# 282 "data/scripts/berry_tree.pory"
	.string "This {STR_VAR_1} plant is growing taller.$"
# 283 "data/scripts/berry_tree.pory"
.endif
# 284 "data/scripts/berry_tree.pory"

# 285 "data/scripts/berry_tree.pory"
BerryTree_Text_BerryGrowthStageTrunk:
# 286 "data/scripts/berry_tree.pory"
	.string "The {STR_VAR_1}'s trunk is getting bigger!$"
# 287 "data/scripts/berry_tree.pory"

# 288 "data/scripts/berry_tree.pory"
BerryTree_Text_BerryGrowthStageBudding:
# 289 "data/scripts/berry_tree.pory"
	.string "The {STR_VAR_1} tree has buds!$"
# 290 "data/scripts/berry_tree.pory"

# 291 "data/scripts/berry_tree.pory"
BerryTree_Text_BerryGrowthStage4:
# 292 "data/scripts/berry_tree.pory"
.if OW_BERRY_SIX_STAGES == TRUE
# 293 "data/scripts/berry_tree.pory"
	.string "The {STR_VAR_1} tree is in bloom!$"
# 294 "data/scripts/berry_tree.pory"
.else
# 295 "data/scripts/berry_tree.pory"
	.string "These {STR_VAR_1} flowers are blooming\n"
# 296 "data/scripts/berry_tree.pory"
	.string "{STR_VAR_2}.$"
# 297 "data/scripts/berry_tree.pory"
.endif
# 298 "data/scripts/berry_tree.pory"

# 299 "data/scripts/berry_tree.pory"
BerryTree_Text_CareAdverbGreat:
# 300 "data/scripts/berry_tree.pory"
	.string "very beautifully$"
# 301 "data/scripts/berry_tree.pory"

# 302 "data/scripts/berry_tree.pory"
BerryTree_Text_CareAdverbPoor:
# 303 "data/scripts/berry_tree.pory"
	.string "cutely$"
# 304 "data/scripts/berry_tree.pory"

# 305 "data/scripts/berry_tree.pory"
BerryTree_Text_CareAdverbGood:
# 306 "data/scripts/berry_tree.pory"
	.string "prettily$"
# 307 "data/scripts/berry_tree.pory"

# 308 "data/scripts/berry_tree.pory"
BerryTree_Text_WantToPick:
# 309 "data/scripts/berry_tree.pory"
	.string "You found {STR_VAR_2} {STR_VAR_1}!\p"
# 310 "data/scripts/berry_tree.pory"
	.string "Do you want to pick the\n"
# 311 "data/scripts/berry_tree.pory"
	.string "{STR_VAR_1}?$"
# 312 "data/scripts/berry_tree.pory"

# 313 "data/scripts/berry_tree.pory"
BerryTree_Text_PickedTheBerry:
# 314 "data/scripts/berry_tree.pory"
	.string "{PLAYER} picked the {STR_VAR_2} {STR_VAR_1}.$"
# 315 "data/scripts/berry_tree.pory"

# 316 "data/scripts/berry_tree.pory"
BerryTree_Text_PutAwayBerry:
# 317 "data/scripts/berry_tree.pory"
	.string "{PLAYER} put away the {STR_VAR_1}\n"
# 318 "data/scripts/berry_tree.pory"
	.string "in the BAG's BERRIES POCKET.\p"
# 319 "data/scripts/berry_tree.pory"
	.string "The soil returned to its soft and\n"
# 320 "data/scripts/berry_tree.pory"
	.string "loamy state.$"
# 321 "data/scripts/berry_tree.pory"

# 322 "data/scripts/berry_tree.pory"
BerryTree_Text_BerryPocketFull:
# 323 "data/scripts/berry_tree.pory"
	.string "The BAG's BERRIES POCKET is full.\p"
# 324 "data/scripts/berry_tree.pory"
	.string "The {STR_VAR_1} couldn't be taken.$"
# 325 "data/scripts/berry_tree.pory"

# 326 "data/scripts/berry_tree.pory"
BerryTree_Text_BerryLeftUnpicked:
# 327 "data/scripts/berry_tree.pory"
	.string "{PLAYER} left the {STR_VAR_1}\n"
# 328 "data/scripts/berry_tree.pory"
	.string "unpicked.$"
# 329 "data/scripts/berry_tree.pory"

# 330 "data/scripts/berry_tree.pory"
BerryTree_Text_WantToWater:
# 331 "data/scripts/berry_tree.pory"
	.string "Want to water the {STR_VAR_1} with the\n"
# 332 "data/scripts/berry_tree.pory"
	.string "WAILMER PAIL?$"
# 333 "data/scripts/berry_tree.pory"

# 334 "data/scripts/berry_tree.pory"
BerryTree_Text_WateredTheBerry:
# 335 "data/scripts/berry_tree.pory"
	.string "{PLAYER} watered the {STR_VAR_1}.$"
# 336 "data/scripts/berry_tree.pory"

# 337 "data/scripts/berry_tree.pory"
BerryTree_Text_PlantIsDelighted:
# 338 "data/scripts/berry_tree.pory"
	.string "The plant seems to be delighted.$"
# 339 "data/scripts/berry_tree.pory"

# 340 "data/scripts/berry_tree.pory"
BerryTree_Text_ExclamationPoint:
# 341 "data/scripts/berry_tree.pory"
	.string "!$"
# 342 "data/scripts/berry_tree.pory"

# 343 "data/scripts/berry_tree.pory"
.if OW_BERRY_MUTATIONS == TRUE
# 344 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckBerryFullyGrown_Mutation:
# 345 "data/scripts/berry_tree.pory"
	msgbox BerryTree_Text_WantToPick_Mutation, MSGBOX_YESNO
# 346 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, YES, BerryTree_EventScript_PickBerry
# 347 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, NO, BerryTree_EventScript_CancelPickingBerry_Mutation
# 348 "data/scripts/berry_tree.pory"

# 349 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CancelPickingBerry_Mutation::
# 350 "data/scripts/berry_tree.pory"
	message BerryTree_Text_BerryLeftUnpicked_Mutation
# 351 "data/scripts/berry_tree.pory"
	waitmessage
# 352 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 353 "data/scripts/berry_tree.pory"
	release
# 354 "data/scripts/berry_tree.pory"
	end
# 355 "data/scripts/berry_tree.pory"

# 356 "data/scripts/berry_tree.pory"
BerryTree_EventScript_BerryPocketFull_Mutation::
# 357 "data/scripts/berry_tree.pory"
	message BerryTree_Text_BerryPocketFull_Mutation
# 358 "data/scripts/berry_tree.pory"
	waitmessage
# 359 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 360 "data/scripts/berry_tree.pory"
	release
# 361 "data/scripts/berry_tree.pory"
	end
# 362 "data/scripts/berry_tree.pory"

# 363 "data/scripts/berry_tree.pory"
BerryTree_EventScript_PickBerry_Mutation::
# 364 "data/scripts/berry_tree.pory"
	special IncrementDailyPickedBerries
# 365 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionRemoveBerryTree
# 366 "data/scripts/berry_tree.pory"
	message BerryTree_Text_PickedTheBerry_Mutation
# 367 "data/scripts/berry_tree.pory"
	playfanfare MUS_OBTAIN_BERRY
# 368 "data/scripts/berry_tree.pory"
	waitmessage
# 369 "data/scripts/berry_tree.pory"
	waitfanfare
# 370 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 371 "data/scripts/berry_tree.pory"
	message BerryTree_Text_PutAwayBerry_Mutation
# 372 "data/scripts/berry_tree.pory"
	waitmessage
# 373 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 374 "data/scripts/berry_tree.pory"
	release
# 375 "data/scripts/berry_tree.pory"
	end
# 376 "data/scripts/berry_tree.pory"

# 377 "data/scripts/berry_tree.pory"
BerryTree_Text_WantToPick_Mutation:
# 378 "data/scripts/berry_tree.pory"
	.string "You found {STR_VAR_2} {STR_VAR_1}\n"
# 379 "data/scripts/berry_tree.pory"
	.string "and 1 {STR_VAR_3}!\p"
# 380 "data/scripts/berry_tree.pory"
	.string "Do you want to pick them?$"
# 381 "data/scripts/berry_tree.pory"

# 382 "data/scripts/berry_tree.pory"
BerryTree_Text_BerryLeftUnpicked_Mutation:
# 383 "data/scripts/berry_tree.pory"
	.string "{PLAYER} left the {STR_VAR_1}\n"
# 384 "data/scripts/berry_tree.pory"
	.string "and the {STR_VAR_3} unpicked.$"
# 385 "data/scripts/berry_tree.pory"

# 386 "data/scripts/berry_tree.pory"
BerryTree_Text_BerryPocketFull_Mutation:
# 387 "data/scripts/berry_tree.pory"
	.string "The BAG's BERRIES POCKET is full.\p"
# 388 "data/scripts/berry_tree.pory"
	.string "The {STR_VAR_1} and the\n"
# 389 "data/scripts/berry_tree.pory"
	.string "{STR_VAR_3} couldn't be taken.$"
# 390 "data/scripts/berry_tree.pory"

# 391 "data/scripts/berry_tree.pory"
BerryTree_Text_PickedTheBerry_Mutation:
# 392 "data/scripts/berry_tree.pory"
	.string "{PLAYER} picked the {STR_VAR_2} {STR_VAR_1}\n"
# 393 "data/scripts/berry_tree.pory"
	.string "and the {STR_VAR_3}.$"
# 394 "data/scripts/berry_tree.pory"

# 395 "data/scripts/berry_tree.pory"
BerryTree_Text_PutAwayBerry_Mutation:
# 396 "data/scripts/berry_tree.pory"
	.string "{PLAYER} put away the {STR_VAR_1}\n"
# 397 "data/scripts/berry_tree.pory"
	.string "and the {STR_VAR_3} in the BAG's\l"
# 398 "data/scripts/berry_tree.pory"
	.string "BERRIES POCKET.\p"
# 399 "data/scripts/berry_tree.pory"
	.string "The soil returned to its soft and\n"
# 400 "data/scripts/berry_tree.pory"
	.string "loamy state.$"
# 401 "data/scripts/berry_tree.pory"
.endif
# 402 "data/scripts/berry_tree.pory"

# 403 "data/scripts/berry_tree.pory"
.if OW_BERRY_MULCH_USAGE == TRUE
# 404 "data/scripts/berry_tree.pory"
BerryTree_EventScript_UseMulch::
# 405 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionApplyMulch
# 406 "data/scripts/berry_tree.pory"
	message BerryTree_Text_ScatteredMulch
# 407 "data/scripts/berry_tree.pory"
	waitmessage
# 408 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 409 "data/scripts/berry_tree.pory"
	return
# 410 "data/scripts/berry_tree.pory"

# 411 "data/scripts/berry_tree.pory"
BerryTree_Text_WantToMulch:
# 412 "data/scripts/berry_tree.pory"
	.string "It's soft, loamy soil.\n"
# 413 "data/scripts/berry_tree.pory"
	.string "Put down some fertilizer?$"
# 414 "data/scripts/berry_tree.pory"

# 415 "data/scripts/berry_tree.pory"
BerryTree_Text_ScatteredMulch:
# 416 "data/scripts/berry_tree.pory"
	.string "{PLAYER} scattered the {STR_VAR_1}\n"
# 417 "data/scripts/berry_tree.pory"
	.string "on the soft, loamy soil.$"
# 418 "data/scripts/berry_tree.pory"
.endif
# 419 "data/scripts/berry_tree.pory"

# 420 "data/scripts/berry_tree.pory"
.if OW_BERRY_WEEDS == TRUE
# 421 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckForWeed::
# 422 "data/scripts/berry_tree.pory"
	specialvar VAR_RESULT, ObjectEventInteractionBerryHasWeed
# 423 "data/scripts/berry_tree.pory"
	call_if_eq VAR_RESULT, TRUE, BerryTree_EventScript_WeedIsGrowing
# 424 "data/scripts/berry_tree.pory"
	return
# 425 "data/scripts/berry_tree.pory"

# 426 "data/scripts/berry_tree.pory"
BerryTree_EventScript_WeedIsGrowing::
# 427 "data/scripts/berry_tree.pory"
	msgbox BerryTree_Text_WeedIsGrowing, MSGBOX_YESNO
# 428 "data/scripts/berry_tree.pory"
	goto_if_eq VAR_RESULT, YES, BerryTree_EventScript_PullOutWeed
# 429 "data/scripts/berry_tree.pory"
	return
# 430 "data/scripts/berry_tree.pory"

# 431 "data/scripts/berry_tree.pory"
BerryTree_EventScript_PullOutWeed::
# 432 "data/scripts/berry_tree.pory"
	special ObjectEventInteractionPullBerryWeed
# 433 "data/scripts/berry_tree.pory"
	message BerryTree_Text_PulledOutTheWeed
# 434 "data/scripts/berry_tree.pory"
	waitmessage
# 435 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 436 "data/scripts/berry_tree.pory"
	return
# 437 "data/scripts/berry_tree.pory"

# 438 "data/scripts/berry_tree.pory"
BerryTree_Text_WeedIsGrowing:
# 439 "data/scripts/berry_tree.pory"
	.string "A weed is growing here.\n"
# 440 "data/scripts/berry_tree.pory"
	.string "Do you want to pull it out?$"
# 441 "data/scripts/berry_tree.pory"

# 442 "data/scripts/berry_tree.pory"
BerryTree_Text_PulledOutTheWeed:
# 443 "data/scripts/berry_tree.pory"
	.string "{PLAYER} pulled out the weed!$"
# 444 "data/scripts/berry_tree.pory"
.endif
# 445 "data/scripts/berry_tree.pory"

# 446 "data/scripts/berry_tree.pory"
.if OW_BERRY_PESTS == TRUE
# 447 "data/scripts/berry_tree.pory"
BerryTree_EventScript_CheckForPests::
# 448 "data/scripts/berry_tree.pory"
	specialvar VAR_RESULT, ObjectEventInteractionBerryHasPests
# 449 "data/scripts/berry_tree.pory"
	call_if_eq VAR_RESULT, TRUE, BerryTree_EventScript_EncounterPests
# 450 "data/scripts/berry_tree.pory"
	return
# 451 "data/scripts/berry_tree.pory"

# 452 "data/scripts/berry_tree.pory"
BerryTree_EventScript_EncounterPests::
# 453 "data/scripts/berry_tree.pory"
	message BerryTree_Text_APokemonAppeared
# 454 "data/scripts/berry_tree.pory"
	waitmessage
# 455 "data/scripts/berry_tree.pory"
	waitbuttonpress
# 456 "data/scripts/berry_tree.pory"
	dowildbattle
# 457 "data/scripts/berry_tree.pory"
	return
# 458 "data/scripts/berry_tree.pory"

# 459 "data/scripts/berry_tree.pory"
BerryTree_Text_APokemonAppeared:
# 460 "data/scripts/berry_tree.pory"
	.string "A Pokémon appeared!$"
# 461 "data/scripts/berry_tree.pory"
.endif

BerryTree_EventScript_WantToPlant::
# 466 "data/scripts/berry_tree.pory"
	goto_if_unset FLAG_RESOURCE_MODE, BerryTree_EventScript_WantToPlant_2
BerryTree_EventScript_WantToPlant_1:
	end

BerryTree_EventScript_WantToPlant_2:
# 467 "data/scripts/berry_tree.pory"
	specialvar VAR_RESULT, PlayerHasMulch
# 468 "data/scripts/berry_tree.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq BerryTree_EventScript_WantToPlant_5
BerryTree_EventScript_WantToPlant_4:
# 471 "data/scripts/berry_tree.pory"
	msgbox BerryTree_Text_WantToPlant, MSGBOX_YESNO
# 472 "data/scripts/berry_tree.pory"
	compare VAR_RESULT, YES
	goto_if_eq BerryTree_EventScript_WantToPlant_7
# 474 "data/scripts/berry_tree.pory"
	compare VAR_RESULT, NO
	goto_if_eq BerryTree_EventScript_WantToPlant_8
	goto BerryTree_EventScript_WantToPlant_1

BerryTree_EventScript_WantToPlant_5:
# 469 "data/scripts/berry_tree.pory"
	goto BerryTree_EventScript_WantToPlantMulch
	goto BerryTree_EventScript_WantToPlant_4

BerryTree_EventScript_WantToPlant_7:
# 473 "data/scripts/berry_tree.pory"
	goto BerryTree_EventScript_ChooseBerryToPlant
	goto BerryTree_EventScript_WantToPlant_1

BerryTree_EventScript_WantToPlant_8:
# 475 "data/scripts/berry_tree.pory"
	goto BerryTree_EventScript_CancelPlanting
	goto BerryTree_EventScript_WantToPlant_1

