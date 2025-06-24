# 1 "data/maps/DewfordTown_Gym/scripts.pory"

# 2 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_MapScripts::
# 3 "data/maps/DewfordTown_Gym/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, DewfordTown_Gym_OnTransition
# 4 "data/maps/DewfordTown_Gym/scripts.pory"
	.byte 0
# 5 "data/maps/DewfordTown_Gym/scripts.pory"

# 6 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_OnTransition:
# 7 "data/maps/DewfordTown_Gym/scripts.pory"
	call DewfordTown_Gym_EventScript_SetFlashLevel
# 8 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 9 "data/maps/DewfordTown_Gym/scripts.pory"

# 10 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_SetFlashLevel::
# 11 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_defeated TRAINER_BRAWLY_1, DewfordTown_Gym_EventScript_SetLightsOn
# 12 "data/maps/DewfordTown_Gym/scripts.pory"
	call DewfordTown_Gym_EventScript_CountTrainersDefeated
# 13 "data/maps/DewfordTown_Gym/scripts.pory"
	copyvar VAR_0x8001, VAR_0x8000
# 14 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_eq VAR_0x8000, 0, DewfordTown_Gym_EventScript_SetFlashLevel7
# 15 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_eq VAR_0x8000, 1, DewfordTown_Gym_EventScript_SetFlashLevel6
# 16 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_eq VAR_0x8000, 2, DewfordTown_Gym_EventScript_SetFlashLevel5
# 17 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_eq VAR_0x8000, 3, DewfordTown_Gym_EventScript_SetFlashLevel4
# 18 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_eq VAR_0x8000, 4, DewfordTown_Gym_EventScript_SetFlashLevel3
# 19 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_eq VAR_0x8000, 5, DewfordTown_Gym_EventScript_SetFlashLevel2
# 20 "data/maps/DewfordTown_Gym/scripts.pory"
	goto DewfordTown_Gym_EventScript_SetFlashLevel1
# 21 "data/maps/DewfordTown_Gym/scripts.pory"

# 22 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_SetLightsOn::
# 23 "data/maps/DewfordTown_Gym/scripts.pory"
	setflashlevel 0
# 24 "data/maps/DewfordTown_Gym/scripts.pory"
	return
# 25 "data/maps/DewfordTown_Gym/scripts.pory"

# 26 "data/maps/DewfordTown_Gym/scripts.pory"
@ Brightest
# 27 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_SetFlashLevel1::
# 28 "data/maps/DewfordTown_Gym/scripts.pory"
	setflashlevel 1
# 29 "data/maps/DewfordTown_Gym/scripts.pory"
	return
# 30 "data/maps/DewfordTown_Gym/scripts.pory"

# 31 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_SetFlashLevel2::
# 32 "data/maps/DewfordTown_Gym/scripts.pory"
	setflashlevel 2
# 33 "data/maps/DewfordTown_Gym/scripts.pory"
	return
# 34 "data/maps/DewfordTown_Gym/scripts.pory"

# 35 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_SetFlashLevel3::
# 36 "data/maps/DewfordTown_Gym/scripts.pory"
	setflashlevel 3
# 37 "data/maps/DewfordTown_Gym/scripts.pory"
	return
# 38 "data/maps/DewfordTown_Gym/scripts.pory"

# 39 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_SetFlashLevel4::
# 40 "data/maps/DewfordTown_Gym/scripts.pory"
	setflashlevel 4
# 41 "data/maps/DewfordTown_Gym/scripts.pory"
	return
# 42 "data/maps/DewfordTown_Gym/scripts.pory"

# 43 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_SetFlashLevel5::
# 44 "data/maps/DewfordTown_Gym/scripts.pory"
	setflashlevel 5
# 45 "data/maps/DewfordTown_Gym/scripts.pory"
	return
# 46 "data/maps/DewfordTown_Gym/scripts.pory"

# 47 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_SetFlashLevel6::
# 48 "data/maps/DewfordTown_Gym/scripts.pory"
	setflashlevel 6
# 49 "data/maps/DewfordTown_Gym/scripts.pory"
	return
# 50 "data/maps/DewfordTown_Gym/scripts.pory"

# 51 "data/maps/DewfordTown_Gym/scripts.pory"
@ Darkest
# 52 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_SetFlashLevel7::
# 53 "data/maps/DewfordTown_Gym/scripts.pory"
	setflashlevel 7
# 54 "data/maps/DewfordTown_Gym/scripts.pory"
	return
# 55 "data/maps/DewfordTown_Gym/scripts.pory"

# 56 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_BrightenRoom::
# 57 "data/maps/DewfordTown_Gym/scripts.pory"
	call DewfordTown_Gym_EventScript_CountTrainersDefeated
# 58 "data/maps/DewfordTown_Gym/scripts.pory"
	nop1
# 59 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_eq VAR_0x8000, VAR_0x8001, DewfordTown_Gym_EventScript_NoLightChange
# 60 "data/maps/DewfordTown_Gym/scripts.pory"
	copyvar VAR_0x8001, VAR_0x8000
# 61 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_eq VAR_0x8000, 1, DewfordTown_Gym_EventScript_AnimateFlash1Trainer
# 62 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_eq VAR_0x8000, 2, DewfordTown_Gym_EventScript_AnimateFlash2Trainers
# 63 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_eq VAR_0x8000, 3, DewfordTown_Gym_EventScript_AnimateFlash3Trainers
# 64 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_eq VAR_0x8000, 4, DewfordTown_Gym_EventScript_AnimateFlash4Trainers
# 65 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_eq VAR_0x8000, 5, DewfordTown_Gym_EventScript_AnimateFlash5Trainers
# 66 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_eq VAR_0x8000, 6, DewfordTown_Gym_EventScript_AnimateFlash6Trainers
# 67 "data/maps/DewfordTown_Gym/scripts.pory"

# 68 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_NoLightChange::
# 69 "data/maps/DewfordTown_Gym/scripts.pory"
	return
# 70 "data/maps/DewfordTown_Gym/scripts.pory"

# 71 "data/maps/DewfordTown_Gym/scripts.pory"
@ NOTE: A little confusingly, a larger animateflash param value is a smaller flash radius
# 72 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_AnimateFlash1Trainer::
# 73 "data/maps/DewfordTown_Gym/scripts.pory"
	playse SE_SWITCH
# 74 "data/maps/DewfordTown_Gym/scripts.pory"
	animateflash 6
# 75 "data/maps/DewfordTown_Gym/scripts.pory"
	call DewfordTown_Gym_EventScript_SetFlashLevel
# 76 "data/maps/DewfordTown_Gym/scripts.pory"
	return
# 77 "data/maps/DewfordTown_Gym/scripts.pory"

# 78 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_AnimateFlash2Trainers::
# 79 "data/maps/DewfordTown_Gym/scripts.pory"
	playse SE_SWITCH
# 80 "data/maps/DewfordTown_Gym/scripts.pory"
	animateflash 5
# 81 "data/maps/DewfordTown_Gym/scripts.pory"
	call DewfordTown_Gym_EventScript_SetFlashLevel
# 82 "data/maps/DewfordTown_Gym/scripts.pory"
	return
# 83 "data/maps/DewfordTown_Gym/scripts.pory"

# 84 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_AnimateFlash3Trainers::
# 85 "data/maps/DewfordTown_Gym/scripts.pory"
	playse SE_SWITCH
# 86 "data/maps/DewfordTown_Gym/scripts.pory"
	animateflash 4
# 87 "data/maps/DewfordTown_Gym/scripts.pory"
	call DewfordTown_Gym_EventScript_SetFlashLevel
# 88 "data/maps/DewfordTown_Gym/scripts.pory"
	return
# 89 "data/maps/DewfordTown_Gym/scripts.pory"

# 90 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_AnimateFlash4Trainers::
# 91 "data/maps/DewfordTown_Gym/scripts.pory"
	playse SE_SWITCH
# 92 "data/maps/DewfordTown_Gym/scripts.pory"
	animateflash 3
# 93 "data/maps/DewfordTown_Gym/scripts.pory"
	call DewfordTown_Gym_EventScript_SetFlashLevel
# 94 "data/maps/DewfordTown_Gym/scripts.pory"
	return
# 95 "data/maps/DewfordTown_Gym/scripts.pory"

# 96 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_AnimateFlash5Trainers::
# 97 "data/maps/DewfordTown_Gym/scripts.pory"
	playse SE_SWITCH
# 98 "data/maps/DewfordTown_Gym/scripts.pory"
	animateflash 2
# 99 "data/maps/DewfordTown_Gym/scripts.pory"
	call DewfordTown_Gym_EventScript_SetFlashLevel
# 100 "data/maps/DewfordTown_Gym/scripts.pory"
	return
# 101 "data/maps/DewfordTown_Gym/scripts.pory"

# 102 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_AnimateFlash6Trainers::
# 103 "data/maps/DewfordTown_Gym/scripts.pory"
	playse SE_SWITCH
# 104 "data/maps/DewfordTown_Gym/scripts.pory"
	animateflash 1
# 105 "data/maps/DewfordTown_Gym/scripts.pory"
	call DewfordTown_Gym_EventScript_SetFlashLevel
# 106 "data/maps/DewfordTown_Gym/scripts.pory"
	return
# 107 "data/maps/DewfordTown_Gym/scripts.pory"

# 108 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_AnimateFlashFullBrightness::
# 109 "data/maps/DewfordTown_Gym/scripts.pory"
	playse SE_SWITCH
# 110 "data/maps/DewfordTown_Gym/scripts.pory"
	animateflash 0
# 111 "data/maps/DewfordTown_Gym/scripts.pory"
	call DewfordTown_Gym_EventScript_SetFlashLevel
# 112 "data/maps/DewfordTown_Gym/scripts.pory"
	return
# 113 "data/maps/DewfordTown_Gym/scripts.pory"

# 114 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_CountTrainersDefeated::
# 115 "data/maps/DewfordTown_Gym/scripts.pory"
	setvar VAR_0x8000, 0
# 116 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_not_defeated TRAINER_TAKAO, DewfordTown_Gym_EventScript_CheckJocelyn
# 117 "data/maps/DewfordTown_Gym/scripts.pory"
	addvar VAR_0x8000, 1
# 118 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_CheckJocelyn::
# 119 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_not_defeated TRAINER_JOCELYN, DewfordTown_Gym_EventScript_CheckLaura
# 120 "data/maps/DewfordTown_Gym/scripts.pory"
	addvar VAR_0x8000, 1
# 121 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_CheckLaura::
# 122 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_not_defeated TRAINER_LAURA, DewfordTown_Gym_EventScript_CheckBrenden
# 123 "data/maps/DewfordTown_Gym/scripts.pory"
	addvar VAR_0x8000, 1
# 124 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_CheckBrenden::
# 125 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_not_defeated TRAINER_BRENDEN, DewfordTown_Gym_EventScript_CheckCristian
# 126 "data/maps/DewfordTown_Gym/scripts.pory"
	addvar VAR_0x8000, 1
# 127 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_CheckCristian::
# 128 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_not_defeated TRAINER_CRISTIAN, DewfordTown_Gym_EventScript_CheckLilith
# 129 "data/maps/DewfordTown_Gym/scripts.pory"
	addvar VAR_0x8000, 1
# 130 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_CheckLilith::
# 131 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_not_defeated TRAINER_LILITH, DewfordTown_Gym_EventScript_StopCountingTrainers
# 132 "data/maps/DewfordTown_Gym/scripts.pory"
	addvar VAR_0x8000, 1
# 133 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_StopCountingTrainers::
# 134 "data/maps/DewfordTown_Gym/scripts.pory"
	return
# 135 "data/maps/DewfordTown_Gym/scripts.pory"

# 136 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_Brawly_Old::
# 137 "data/maps/DewfordTown_Gym/scripts.pory"
	trainerbattle_single TRAINER_BRAWLY_1, DewfordTown_Gym_Text_BrawlyIntro, DewfordTown_Gym_Text_BrawlyDefeat, DewfordTown_Gym_EventScript_BrawlyDefeated, NO_MUSIC
# 138 "data/maps/DewfordTown_Gym/scripts.pory"
	specialvar VAR_RESULT, ShouldTryRematchBattle
# 139 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, DewfordTown_Gym_EventScript_BrawlyRematch
# 140 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_unset FLAG_RECEIVED_TM_LOW_KICK, DewfordTown_Gym_EventScript_GiveLowKick
# 141 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_Text_BrawlyPostBattle, MSGBOX_DEFAULT
# 142 "data/maps/DewfordTown_Gym/scripts.pory"
	release
# 143 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 144 "data/maps/DewfordTown_Gym/scripts.pory"

# 145 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_BrawlyDefeated::
# 146 "data/maps/DewfordTown_Gym/scripts.pory"
	call DewfordTown_Gym_EventScript_AnimateFlashFullBrightness
# 147 "data/maps/DewfordTown_Gym/scripts.pory"
	message DewfordTown_Gym_Text_ReceivedKnuckleBadge
# 148 "data/maps/DewfordTown_Gym/scripts.pory"
	waitmessage
# 149 "data/maps/DewfordTown_Gym/scripts.pory"
	call Common_EventScript_PlayGymBadgeFanfare
# 150 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_Text_KnuckleBadgeInfoTakeThis, MSGBOX_DEFAULT
# 151 "data/maps/DewfordTown_Gym/scripts.pory"
	setflag FLAG_DEFEATED_DEWFORD_GYM
# 152 "data/maps/DewfordTown_Gym/scripts.pory"
	setflag FLAG_BADGE02_GET
# 153 "data/maps/DewfordTown_Gym/scripts.pory"
	addvar VAR_PETALBURG_GYM_STATE, 1
# 154 "data/maps/DewfordTown_Gym/scripts.pory"
	call_if_eq VAR_PETALBURG_GYM_STATE, 6, Common_EventScript_ReadyPetalburgGymForBattle
# 155 "data/maps/DewfordTown_Gym/scripts.pory"
	setvar VAR_0x8008, 2
# 156 "data/maps/DewfordTown_Gym/scripts.pory"
	call Common_EventScript_SetGymTrainers
# 157 "data/maps/DewfordTown_Gym/scripts.pory"
	call DewfordTown_Gym_EventScript_GiveBulkUp
# 158 "data/maps/DewfordTown_Gym/scripts.pory"
	closemessage
# 159 "data/maps/DewfordTown_Gym/scripts.pory"
	delay 30
# 160 "data/maps/DewfordTown_Gym/scripts.pory"
	playfanfare MUS_REGISTER_MATCH_CALL
# 161 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_Text_RegisteredBrawly, MSGBOX_DEFAULT
# 162 "data/maps/DewfordTown_Gym/scripts.pory"
	waitfanfare
# 163 "data/maps/DewfordTown_Gym/scripts.pory"
	closemessage
# 164 "data/maps/DewfordTown_Gym/scripts.pory"
	delay 30
# 165 "data/maps/DewfordTown_Gym/scripts.pory"
	setflag FLAG_ENABLE_BRAWLY_MATCH_CALL
# 166 "data/maps/DewfordTown_Gym/scripts.pory"
	setvar VAR_ROXANNE_CALL_STEP_COUNTER, 0
# 167 "data/maps/DewfordTown_Gym/scripts.pory"
	setflag FLAG_ENABLE_ROXANNE_FIRST_CALL
# 168 "data/maps/DewfordTown_Gym/scripts.pory"
	goto DewfordTown_Gym_EventScript_GiveLowKick
# 169 "data/maps/DewfordTown_Gym/scripts.pory"
	release
# 170 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 171 "data/maps/DewfordTown_Gym/scripts.pory"

# 172 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_GiveBulkUp::
# 173 "data/maps/DewfordTown_Gym/scripts.pory"
	giveitem ITEM_TM_LOW_KICK
# 174 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_eq VAR_RESULT, 0, Common_EventScript_BagIsFull
# 175 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_Text_ExplainBulkUp, MSGBOX_DEFAULT
# 176 "data/maps/DewfordTown_Gym/scripts.pory"
	setflag FLAG_RECEIVED_TM_LOW_KICK
# 177 "data/maps/DewfordTown_Gym/scripts.pory"
	return
# 178 "data/maps/DewfordTown_Gym/scripts.pory"

# 179 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_GiveBulkUp2:
# 180 "data/maps/DewfordTown_Gym/scripts.pory"
	giveitem ITEM_TM_LOW_KICK
# 181 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
# 182 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_Text_ExplainBulkUp, MSGBOX_DEFAULT
# 183 "data/maps/DewfordTown_Gym/scripts.pory"
	setflag FLAG_RECEIVED_TM_LOW_KICK
# 184 "data/maps/DewfordTown_Gym/scripts.pory"
	release
# 185 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 186 "data/maps/DewfordTown_Gym/scripts.pory"

# 187 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_BrawlyRematch::
# 188 "data/maps/DewfordTown_Gym/scripts.pory"
	trainerbattle_rematch_double TRAINER_BRAWLY_1, DewfordTown_Gym_Text_BrawlyPreRematch, DewfordTown_Gym_Text_BrawlyRematchDefeat, DewfordTown_Gym_Text_BrawlyRematchNeedTwoMons
# 189 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_Text_BrawlyPostRematch, MSGBOX_AUTOCLOSE
# 190 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 191 "data/maps/DewfordTown_Gym/scripts.pory"

# 192 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_Takao::
# 193 "data/maps/DewfordTown_Gym/scripts.pory"
	trainerbattle_single TRAINER_TAKAO, DewfordTown_Gym_Text_TakaoIntro, DewfordTown_Gym_Text_TakaoDefeat, DewfordTown_Gym_EventScript_TakaoBrightenRoom
# 194 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_Text_TakaoPostBattle, MSGBOX_AUTOCLOSE
# 195 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 196 "data/maps/DewfordTown_Gym/scripts.pory"

# 197 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_TakaoBrightenRoom::
# 198 "data/maps/DewfordTown_Gym/scripts.pory"
	call DewfordTown_Gym_EventScript_BrightenRoom
# 199 "data/maps/DewfordTown_Gym/scripts.pory"
	release
# 200 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 201 "data/maps/DewfordTown_Gym/scripts.pory"

# 202 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_Jocelyn::
# 203 "data/maps/DewfordTown_Gym/scripts.pory"
	trainerbattle_single TRAINER_JOCELYN, DewfordTown_Gym_Text_JocelynIntro, DewfordTown_Gym_Text_JocelynDefeat, DewfordTown_Gym_EventScript_JocelynBrightenRoom
# 204 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_Text_JocelynPostBattle, MSGBOX_AUTOCLOSE
# 205 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 206 "data/maps/DewfordTown_Gym/scripts.pory"

# 207 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_JocelynBrightenRoom::
# 208 "data/maps/DewfordTown_Gym/scripts.pory"
	call DewfordTown_Gym_EventScript_BrightenRoom
# 209 "data/maps/DewfordTown_Gym/scripts.pory"
	release
# 210 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 211 "data/maps/DewfordTown_Gym/scripts.pory"

# 212 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_Laura::
# 213 "data/maps/DewfordTown_Gym/scripts.pory"
	trainerbattle_single TRAINER_LAURA, DewfordTown_Gym_Text_LauraIntro, DewfordTown_Gym_Text_LauraDefeat, DewfordTown_Gym_EventScript_LauraBrightenRoom
# 214 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_Text_LauraPostBattle, MSGBOX_AUTOCLOSE
# 215 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 216 "data/maps/DewfordTown_Gym/scripts.pory"

# 217 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_LauraBrightenRoom::
# 218 "data/maps/DewfordTown_Gym/scripts.pory"
	call DewfordTown_Gym_EventScript_BrightenRoom
# 219 "data/maps/DewfordTown_Gym/scripts.pory"
	release
# 220 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 221 "data/maps/DewfordTown_Gym/scripts.pory"

# 222 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_Brenden::
# 223 "data/maps/DewfordTown_Gym/scripts.pory"
	trainerbattle_single TRAINER_BRENDEN, DewfordTown_Gym_Text_BrendenIntro, DewfordTown_Gym_Text_BrendenDefeat, DewfordTown_Gym_EventScript_BrendenBrightenRoom
# 224 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_Text_BrendenPostBattle, MSGBOX_AUTOCLOSE
# 225 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 226 "data/maps/DewfordTown_Gym/scripts.pory"

# 227 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_BrendenBrightenRoom::
# 228 "data/maps/DewfordTown_Gym/scripts.pory"
	call DewfordTown_Gym_EventScript_BrightenRoom
# 229 "data/maps/DewfordTown_Gym/scripts.pory"
	release
# 230 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 231 "data/maps/DewfordTown_Gym/scripts.pory"

# 232 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_Cristian::
# 233 "data/maps/DewfordTown_Gym/scripts.pory"
	trainerbattle_single TRAINER_CRISTIAN, DewfordTown_Gym_Text_CristianIntro, DewfordTown_Gym_Text_CristianDefeat, DewfordTown_Gym_EventScript_CristianBrightenRoom
# 234 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_Text_CristianPostBattle, MSGBOX_AUTOCLOSE
# 235 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 236 "data/maps/DewfordTown_Gym/scripts.pory"

# 237 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_CristianBrightenRoom::
# 238 "data/maps/DewfordTown_Gym/scripts.pory"
	call DewfordTown_Gym_EventScript_BrightenRoom
# 239 "data/maps/DewfordTown_Gym/scripts.pory"
	release
# 240 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 241 "data/maps/DewfordTown_Gym/scripts.pory"

# 242 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_Lilith::
# 243 "data/maps/DewfordTown_Gym/scripts.pory"
	trainerbattle_single TRAINER_LILITH, DewfordTown_Gym_Text_LilithIntro, DewfordTown_Gym_Text_LilithDefeat, DewfordTown_Gym_EventScript_LilithBrightenRoom
# 244 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_Text_LilithPostBattle, MSGBOX_AUTOCLOSE
# 245 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 246 "data/maps/DewfordTown_Gym/scripts.pory"

# 247 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_LilithBrightenRoom::
# 248 "data/maps/DewfordTown_Gym/scripts.pory"
	call DewfordTown_Gym_EventScript_BrightenRoom
# 249 "data/maps/DewfordTown_Gym/scripts.pory"
	release
# 250 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 251 "data/maps/DewfordTown_Gym/scripts.pory"

# 252 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_GymGuide::
# 253 "data/maps/DewfordTown_Gym/scripts.pory"
	lock
# 254 "data/maps/DewfordTown_Gym/scripts.pory"
	faceplayer
# 255 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_set FLAG_DEFEATED_DEWFORD_GYM, DewfordTown_Gym_EventScript_GymGuidePostVictory
# 256 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
# 257 "data/maps/DewfordTown_Gym/scripts.pory"
	release
# 258 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 259 "data/maps/DewfordTown_Gym/scripts.pory"

# 260 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_GymGuidePostVictory::
# 261 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
# 262 "data/maps/DewfordTown_Gym/scripts.pory"
	release
# 263 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 264 "data/maps/DewfordTown_Gym/scripts.pory"

# 265 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_LeftGymStatue::
# 266 "data/maps/DewfordTown_Gym/scripts.pory"
	lockall
# 267 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_set FLAG_BADGE02_GET, DewfordTown_Gym_EventScript_GymStatueCertified
# 268 "data/maps/DewfordTown_Gym/scripts.pory"
	goto DewfordTown_Gym_EventScript_GymStatue
# 269 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 270 "data/maps/DewfordTown_Gym/scripts.pory"

# 271 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_RightGymStatue::
# 272 "data/maps/DewfordTown_Gym/scripts.pory"
	lockall
# 273 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_set FLAG_BADGE02_GET, DewfordTown_Gym_EventScript_GymStatueCertified
# 274 "data/maps/DewfordTown_Gym/scripts.pory"
	goto DewfordTown_Gym_EventScript_GymStatue
# 275 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 276 "data/maps/DewfordTown_Gym/scripts.pory"

# 277 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_GymStatueCertified::
# 278 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
# 279 "data/maps/DewfordTown_Gym/scripts.pory"
	releaseall
# 280 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 281 "data/maps/DewfordTown_Gym/scripts.pory"

# 282 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_EventScript_GymStatue::
# 283 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_Text_GymStatue, MSGBOX_DEFAULT
# 284 "data/maps/DewfordTown_Gym/scripts.pory"
	releaseall
# 285 "data/maps/DewfordTown_Gym/scripts.pory"
	end
# 286 "data/maps/DewfordTown_Gym/scripts.pory"

# 287 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_GymGuideAdvice:
# 288 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Hey, how's it going, CHAMPION-\n"
# 289 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "bound {PLAYER}?\p"
# 290 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "DEWFORD's GYM LEADER BRAWLY commands\n"
# 291 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "FIGHTING-type POKéMON.\p"
# 292 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Going against him with NORMAL-type\n"
# 293 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "POKéMON is asking for trouble.\p"
# 294 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "FIGHTING POKéMON will lay a serious\n"
# 295 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "smack down on NORMAL POKéMON,\l"
# 296 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "so be careful!\p"
# 297 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "What's worse, the GYM is as dark as\n"
# 298 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "the ocean floor.\p"
# 299 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "But it will get brighter after defeating\n"
# 300 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "the TRAINERS in your way.\p"
# 301 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Hey, okay, go for it!$"
# 302 "data/maps/DewfordTown_Gym/scripts.pory"

# 303 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_GymGuidePostVictory:
# 304 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Whoah! It's turned too bright in here!\p"
# 305 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Your future is bright, too!$"
# 306 "data/maps/DewfordTown_Gym/scripts.pory"

# 307 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_TakaoIntro:
# 308 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Might is right!\n"
# 309 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Come on!$"
# 310 "data/maps/DewfordTown_Gym/scripts.pory"

# 311 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_TakaoDefeat:
# 312 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Not enough power…$"
# 313 "data/maps/DewfordTown_Gym/scripts.pory"

# 314 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_TakaoPostBattle:
# 315 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Your skill overcame my strength!\n"
# 316 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Your technique is commendable!$"
# 317 "data/maps/DewfordTown_Gym/scripts.pory"

# 318 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_JocelynIntro:
# 319 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "There's no need for BRAWLY to be\n"
# 320 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "involved!\p"
# 321 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "I'll crush you!$"
# 322 "data/maps/DewfordTown_Gym/scripts.pory"

# 323 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_JocelynDefeat:
# 324 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "But… How?\n"
# 325 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "How could I lose so easily?$"
# 326 "data/maps/DewfordTown_Gym/scripts.pory"

# 327 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_JocelynPostBattle:
# 328 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "I'm not going to waste this loss.\n"
# 329 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "I'll use it to motivate me to train!\p"
# 330 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "One day I'll become a GYM LEADER…\p"
# 331 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "No, I'll become the POKéMON LEAGUE\n"
# 332 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "CHAMPION!$"
# 333 "data/maps/DewfordTown_Gym/scripts.pory"

# 334 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_LauraIntro:
# 335 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Don't you dare brush me off!\n"
# 336 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "It's not my fault if you cry!$"
# 337 "data/maps/DewfordTown_Gym/scripts.pory"

# 338 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_LauraDefeat:
# 339 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Waaaaaaah!\n"
# 340 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "I lost!$"
# 341 "data/maps/DewfordTown_Gym/scripts.pory"

# 342 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_LauraPostBattle:
# 343 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "I battle in the dark to make my heart\n"
# 344 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "stronger.\p"
# 345 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "But because it's so dark, I can never\n"
# 346 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "see BRAWLY's face…$"
# 347 "data/maps/DewfordTown_Gym/scripts.pory"

# 348 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_LilithIntro:
# 349 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Ufufu…\n"
# 350 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Are you stumbling around in the dark?$"
# 351 "data/maps/DewfordTown_Gym/scripts.pory"

# 352 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_LilithDefeat:
# 353 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Oh, you…\n"
# 354 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "I don't want to know you!$"
# 355 "data/maps/DewfordTown_Gym/scripts.pory"

# 356 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_LilithPostBattle:
# 357 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "You deserve to stay lost and end up\n"
# 358 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "back at the entrance again!$"
# 359 "data/maps/DewfordTown_Gym/scripts.pory"

# 360 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_BrendenIntro:
# 361 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "I'll show you the gumption of\n"
# 362 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "a sailing man!$"
# 363 "data/maps/DewfordTown_Gym/scripts.pory"

# 364 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_BrendenDefeat:
# 365 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "How'd this happen?\n"
# 366 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "It's not like me to lose this way!$"
# 367 "data/maps/DewfordTown_Gym/scripts.pory"

# 368 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_BrendenPostBattle:
# 369 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Oh, aye! You're worthy of seeing\n"
# 370 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "our GYM LEADER.$"
# 371 "data/maps/DewfordTown_Gym/scripts.pory"

# 372 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_CristianIntro:
# 373 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "If you mean to pass, it has to be\n"
# 374 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "through me!$"
# 375 "data/maps/DewfordTown_Gym/scripts.pory"

# 376 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_CristianDefeat:
# 377 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Grrrrr!\n"
# 378 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Vastly overpowered!$"
# 379 "data/maps/DewfordTown_Gym/scripts.pory"

# 380 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_CristianPostBattle:
# 381 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "You win!\n"
# 382 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Go after that BADGE!$"
# 383 "data/maps/DewfordTown_Gym/scripts.pory"

# 384 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_BrawlyIntro:
# 385 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "I'm BRAWLY!\n"
# 386 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "DEWFORD's GYM LEADER!\p"
# 387 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "I've been churned in the rough waves\n"
# 388 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "of these parts, and I've grown tough\l"
# 389 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "in the pitch-black cave!\p"
# 390 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "So you wanted to challenge me?\n"
# 391 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Let me see what you're made of!$"
# 392 "data/maps/DewfordTown_Gym/scripts.pory"

# 393 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_BrawlyDefeat:
# 394 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Whoah, wow! You made a much bigger\n"
# 395 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "splash than I expected!\p"
# 396 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "You swamped me!\p"
# 397 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Okay, you've got me.\n"
# 398 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Take this GYM BADGE!$"
# 399 "data/maps/DewfordTown_Gym/scripts.pory"

# 400 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_ReceivedKnuckleBadge:
# 401 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "{PLAYER} received the KNUCKLE BADGE\n"
# 402 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "from BRAWLY.$"
# 403 "data/maps/DewfordTown_Gym/scripts.pory"

# 404 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_KnuckleBadgeInfoTakeThis:
# 405 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "The KNUCKLE BADGE makes all POKéMON\n"
# 406 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "up to Level 30, even those you get in\l"
# 407 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "trades, obey without question.\p"
# 408 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "And, you'll be able to use the HM move\n"
# 409 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "FLASH outside of battle.\p"
# 410 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "If you'd like, use this TECHNICAL\n"
# 411 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "MACHINE, too.$"
# 412 "data/maps/DewfordTown_Gym/scripts.pory"

# 413 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_ExplainBulkUp:
# 414 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "That TM08 contains BULK UP.\p"
# 415 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "It's a move that raises both ATTACK\n"
# 416 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "and DEFENSE stats.\p"
# 417 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "… … … … … …$"
# 418 "data/maps/DewfordTown_Gym/scripts.pory"

# 419 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_RegisteredBrawly:
# 420 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Registered GYM LEADER BRAWLY\n"
# 421 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "in the POKéNAV.$"
# 422 "data/maps/DewfordTown_Gym/scripts.pory"

# 423 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_BrawlyPostBattle:
# 424 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "I can see your talent becoming a giant\n"
# 425 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "wave to cause a storm of astonishment\l"
# 426 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "among TRAINERS one day!$"
# 427 "data/maps/DewfordTown_Gym/scripts.pory"

# 428 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_GymStatue:
# 429 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "DEWFORD TOWN POKéMON GYM$"
# 430 "data/maps/DewfordTown_Gym/scripts.pory"

# 431 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_GymStatueCertified:
# 432 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "DEWFORD TOWN POKéMON GYM\p"
# 433 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "BRAWLY'S CERTIFIED TRAINERS:\n"
# 434 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "{PLAYER}$"
# 435 "data/maps/DewfordTown_Gym/scripts.pory"

# 436 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_BrawlyPreRematch:
# 437 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "BRAWLY: A wave may draw back, but it\n"
# 438 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "always returns to the shore.\p"
# 439 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "A giant wave of a talent like you…\n"
# 440 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "I knew you would return!\p"
# 441 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Show me how much higher\n"
# 442 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "you've gone!$"
# 443 "data/maps/DewfordTown_Gym/scripts.pory"

# 444 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_BrawlyRematchDefeat:
# 445 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Wow!\n"
# 446 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Swamped again!$"
# 447 "data/maps/DewfordTown_Gym/scripts.pory"

# 448 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_BrawlyPostRematch:
# 449 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "BRAWLY: Battling is vast and it's deep.\n"
# 450 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "You can't see the bottom.\l"
# 451 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "It's just like the sea of HOENN!$"
# 452 "data/maps/DewfordTown_Gym/scripts.pory"

# 453 "data/maps/DewfordTown_Gym/scripts.pory"
DewfordTown_Gym_Text_BrawlyRematchNeedTwoMons:
# 454 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "BRAWLY: A wave may draw back, but it\n"
# 455 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "always returns to the shore.\p"
# 456 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "A giant wave of a talent like you…\n"
# 457 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "I knew you would return!\p"
# 458 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Oh? You only have one POKéMON\n"
# 459 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "that can battle.\p"
# 460 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "I'm sorry, but I'd like you to come back\n"
# 461 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "with at least two POKéMON.$"

DewfordTown_Gym_EventScript_Brawly::
# 464 "data/maps/DewfordTown_Gym/scripts.pory"
	lock
# 465 "data/maps/DewfordTown_Gym/scripts.pory"
	faceplayer
# 466 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_unset FLAG_RECEIVED_TM_LOW_KICK, DewfordTown_Gym_EventScript_Brawly_2
DewfordTown_Gym_EventScript_Brawly_1:
# 475 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_Text_BrawlyPostBattle
# 476 "data/maps/DewfordTown_Gym/scripts.pory"
	release
	end

DewfordTown_Gym_EventScript_Brawly_2:
# 467 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_set FLAG_RESTRICTED_MODE, DewfordTown_Gym_EventScript_Brawly_5
DewfordTown_Gym_EventScript_Brawly_4:
# 473 "data/maps/DewfordTown_Gym/scripts.pory"
	goto BrawlyFirstGymBattleScript
	goto DewfordTown_Gym_EventScript_Brawly_1

DewfordTown_Gym_EventScript_Brawly_5:
# 468 "data/maps/DewfordTown_Gym/scripts.pory"
	specialvar VAR_RESULT, DoesPlayerFollowItemClause
# 469 "data/maps/DewfordTown_Gym/scripts.pory"
	compare VAR_RESULT, FALSE
	goto_if_eq DewfordTown_Gym_EventScript_Brawly_7
	goto DewfordTown_Gym_EventScript_Brawly_4

DewfordTown_Gym_EventScript_Brawly_7:
# 470 "data/maps/DewfordTown_Gym/scripts.pory"
	goto Brawly_Restrict_Item_Clause
	goto DewfordTown_Gym_EventScript_Brawly_4


BrawlyFirstGymBattleScript::
# 482 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox BrawlyFirstGymBattleScript_Text_0
# 483 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox BrawlyFirstGymBattleScript_Text_1
# 484 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox BrawlyFirstGymBattleScript_Text_2
# 485 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox BrawlyFirstGymBattleScript_Text_3
# 486 "data/maps/DewfordTown_Gym/scripts.pory"
	playse SE_USE_ITEM
# 487 "data/maps/DewfordTown_Gym/scripts.pory"
	special HealPlayerParty
# 488 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox BrawlyFirstGymBattleScript_Text_4
# 489 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox BrawlyFirstGymBattleScript_Text_5
# 490 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox BrawlyFirstGymBattleScript_Text_6
# 491 "data/maps/DewfordTown_Gym/scripts.pory"
	dynmultichoice 0, 100, TRUE, 2, 0, DYN_MULTICHOICE_CB_NONE, BrawlyFirstGymBattleScript_Text_7, BrawlyFirstGymBattleScript_Text_8
# 492 "data/maps/DewfordTown_Gym/scripts.pory"
	compare VAR_RESULT, 0
	goto_if_eq BrawlyFirstGymBattleScript_2
# 506 "data/maps/DewfordTown_Gym/scripts.pory"
	compare VAR_RESULT, 1
	goto_if_eq BrawlyFirstGymBattleScript_3
BrawlyFirstGymBattleScript_1:
# 519 "data/maps/DewfordTown_Gym/scripts.pory"
	release
	end

BrawlyFirstGymBattleScript_2:
# 493 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox BrawlyFirstGymBattleScript_Text_9
# 494 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox BrawlyFirstGymBattleScript_Text_10
# 495 "data/maps/DewfordTown_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_NONE
	goto_if_eq BrawlyFirstGymBattleScript_7
# 495 "data/maps/DewfordTown_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_FLYING
	goto_if_eq BrawlyFirstGymBattleScript_7
# 495 "data/maps/DewfordTown_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_PSYCHIC - 1
	goto_if_eq BrawlyFirstGymBattleScript_7
# 496 "data/maps/DewfordTown_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_FAIRY - 1
	goto_if_eq BrawlyFirstGymBattleScript_7
# 496 "data/maps/DewfordTown_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_POISON
	goto_if_eq BrawlyFirstGymBattleScript_7
# 496 "data/maps/DewfordTown_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_GHOST
	goto_if_eq BrawlyFirstGymBattleScript_7
# 497 "data/maps/DewfordTown_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_BUG
	goto_if_eq BrawlyFirstGymBattleScript_7
# 497 "data/maps/DewfordTown_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_WATER -1
	goto_if_eq BrawlyFirstGymBattleScript_7
# 502 "data/maps/DewfordTown_Gym/scripts.pory"
	trainerbattle_no_intro TRAINER_BRAWLY_1_3MON, DewfordTown_Gym_Text_BrawlyDefeat
BrawlyFirstGymBattleScript_6:
# 505 "data/maps/DewfordTown_Gym/scripts.pory"
	call DewfordTown_Gym_EventScript_BrawlyDefeated
	goto BrawlyFirstGymBattleScript_1

BrawlyFirstGymBattleScript_3:
# 507 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox BrawlyFirstGymBattleScript_Text_11
# 508 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox BrawlyFirstGymBattleScript_Text_10
# 509 "data/maps/DewfordTown_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_NONE
	goto_if_eq BrawlyFirstGymBattleScript_25
# 509 "data/maps/DewfordTown_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_FLYING
	goto_if_eq BrawlyFirstGymBattleScript_25
# 509 "data/maps/DewfordTown_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_PSYCHIC - 1
	goto_if_eq BrawlyFirstGymBattleScript_25
# 510 "data/maps/DewfordTown_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_FAIRY - 1
	goto_if_eq BrawlyFirstGymBattleScript_25
# 510 "data/maps/DewfordTown_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_POISON
	goto_if_eq BrawlyFirstGymBattleScript_25
# 510 "data/maps/DewfordTown_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_GHOST
	goto_if_eq BrawlyFirstGymBattleScript_25
# 511 "data/maps/DewfordTown_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_BUG
	goto_if_eq BrawlyFirstGymBattleScript_25
# 511 "data/maps/DewfordTown_Gym/scripts.pory"
	compare VAR_MONOTYPE, TYPE_WATER -1
	goto_if_eq BrawlyFirstGymBattleScript_25
# 515 "data/maps/DewfordTown_Gym/scripts.pory"
	trainerbattle_no_intro TRAINER_BRAWLY_1_3MON_DOUBLES, DewfordTown_Gym_Text_BrawlyDefeat
BrawlyFirstGymBattleScript_24:
# 517 "data/maps/DewfordTown_Gym/scripts.pory"
	call DewfordTown_Gym_EventScript_BrawlyDefeated
	goto BrawlyFirstGymBattleScript_1

BrawlyFirstGymBattleScript_7:
# 500 "data/maps/DewfordTown_Gym/scripts.pory"
	trainerbattle_no_intro TRAINER_BRAWLY_1, DewfordTown_Gym_Text_BrawlyDefeat
	goto BrawlyFirstGymBattleScript_6

BrawlyFirstGymBattleScript_25:
# 513 "data/maps/DewfordTown_Gym/scripts.pory"
	trainerbattle_no_intro TRAINER_BRAWLY_1_DOUBLES, DewfordTown_Gym_Text_BrawlyDefeat
	goto BrawlyFirstGymBattleScript_24


Brawly_Restrict_Item_Clause::
# 524 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox Brawly_Restrict_Item_Clause_Text_0
# 525 "data/maps/DewfordTown_Gym/scripts.pory"
	release
	end


DewfordTown_Gym_EventScript_GiveLowKick::
# 530 "data/maps/DewfordTown_Gym/scripts.pory"
	compare VAR_MONOTYPE, 0
	goto_if_gt DewfordTown_Gym_EventScript_GiveLowKick_2
# 534 "data/maps/DewfordTown_Gym/scripts.pory"
	addvar VAR_REMAINING_TUTOR, 1
# 535 "data/maps/DewfordTown_Gym/scripts.pory"
	addvar VAR_REMAINING_RELEARNER, 1
DewfordTown_Gym_EventScript_GiveLowKick_1:
# 539 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_unset FLAG_RESOURCE_MODE, DewfordTown_Gym_EventScript_GiveLowKick_6
# 544 "data/maps/DewfordTown_Gym/scripts.pory"
	giveitem ITEM_TM_LOW_KICK, 3
# 545 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 546 "data/maps/DewfordTown_Gym/scripts.pory"
	setflag FLAG_RECEIVED_TM_LOW_KICK
DewfordTown_Gym_EventScript_GiveLowKick_5:
# 548 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_EventScript_GiveLowKick_Text_0
# 549 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_EventScript_GiveLowKick_Text_1
# 550 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_EventScript_GiveLowKick_Text_2
# 551 "data/maps/DewfordTown_Gym/scripts.pory"
	msgbox DewfordTown_Gym_EventScript_GiveLowKick_Text_3
# 552 "data/maps/DewfordTown_Gym/scripts.pory"
	release
	end

DewfordTown_Gym_EventScript_GiveLowKick_2:
# 531 "data/maps/DewfordTown_Gym/scripts.pory"
	addvar VAR_REMAINING_TUTOR, 2
# 532 "data/maps/DewfordTown_Gym/scripts.pory"
	addvar VAR_REMAINING_RELEARNER, 2
	goto DewfordTown_Gym_EventScript_GiveLowKick_1

DewfordTown_Gym_EventScript_GiveLowKick_6:
# 540 "data/maps/DewfordTown_Gym/scripts.pory"
	giveitem ITEM_TM_LOW_KICK
# 541 "data/maps/DewfordTown_Gym/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 542 "data/maps/DewfordTown_Gym/scripts.pory"
	setflag FLAG_RECEIVED_TM_LOW_KICK
	goto DewfordTown_Gym_EventScript_GiveLowKick_5


BrawlyFirstGymBattleScript_Text_0:
# 482 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "I'm BRAWLY!\n"
	.string "DEWFORD's GYM LEADER!$"

BrawlyFirstGymBattleScript_Text_1:
# 483 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "I've been churned in the rough waves\n"
	.string "of these parts.$"

BrawlyFirstGymBattleScript_Text_2:
# 484 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "But I'm sure you've had it tough in my\n"
	.string "gym as well.$"

BrawlyFirstGymBattleScript_Text_3:
# 485 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Here, let me heal your POKéMON for you.$"

BrawlyFirstGymBattleScript_Text_4:
# 488 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "I've grown tough in the pitch-black\n"
	.string "cave!$"

BrawlyFirstGymBattleScript_Text_5:
# 489 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "So you wanted to challenge me?$"

BrawlyFirstGymBattleScript_Text_6:
# 490 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Would you like to have a Single or a\n"
	.string "Double Battle?$"

BrawlyFirstGymBattleScript_Text_7:
# 491 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Single Battle$"

BrawlyFirstGymBattleScript_Text_8:
# 491 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Double Battle$"

BrawlyFirstGymBattleScript_Text_9:
# 493 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "One on One? That's what I'm talking\n"
	.string "about!$"

BrawlyFirstGymBattleScript_Text_10:
# 494 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Let me see what you're made of!$"

BrawlyFirstGymBattleScript_Text_11:
# 507 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Two on Two? You'll see our pair training!$"

Brawly_Restrict_Item_Clause_Text_0:
# 524 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "I'd love to fight, but League rules say\n"
	.string "I can't if you carry duplicate items.$"

DewfordTown_Gym_EventScript_GiveLowKick_Text_0:
# 548 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Here, take this TM. It's one of my\n"
	.string "favorite moves. LOW KICK.$"

DewfordTown_Gym_EventScript_GiveLowKick_Text_1:
# 549 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "It's all about weight and timing-$"

DewfordTown_Gym_EventScript_GiveLowKick_Text_2:
# 550 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "The bigger they are, the harder they\n"
	.string "fall!$"

DewfordTown_Gym_EventScript_GiveLowKick_Text_3:
# 551 "data/maps/DewfordTown_Gym/scripts.pory"
	.string "Use it well, and you'll have 'em hitting\n"
	.string "the mat in no time!$"
