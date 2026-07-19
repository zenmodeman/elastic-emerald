EventScript_StartTrainerApproach::
	selectapproachingtrainer
	lockfortrainer
EventScript_TrainerApproach::
	special PlayTrainerEncounterMusic
	special DoTrainerApproach
	waitstate
	goto EventScript_ShowTrainerIntroMsg

EventScript_TryDoNormalTrainerBattle::
	lock
	faceplayer
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
	applymovement VAR_LAST_TALKED, Movement_RevealTrainer
	waitmovement 0
	clearflag FLAG_SAFE_FOLLOWER_MOVEMENT
	specialvar VAR_RESULT, GetTrainerFlag
	goto_if_ne VAR_RESULT, FALSE, EventScript_NoNormalTrainerBattle
	special PlayTrainerEncounterMusic
	special SetTrainerFacingDirection
	goto EventScript_ShowTrainerIntroMsg

EventScript_NoNormalTrainerBattle::
	gotopostbattlescript

EventScript_TryDoDoubleTrainerBattle::
	lock
	faceplayer
	call EventScript_RevealTrainer
	specialvar VAR_RESULT, GetTrainerFlag
	goto_if_ne VAR_RESULT, FALSE, EventScript_NoDoubleTrainerBattle
	special HasEnoughMonsForDoubleBattle
	goto_if_ne VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS, EventScript_NotEnoughMonsForDoubleBattle
	special PlayTrainerEncounterMusic
	special SetTrainerFacingDirection
	goto EventScript_ShowTrainerIntroMsg

EventScript_NotEnoughMonsForDoubleBattle::
	special ShowTrainerCantBattleSpeech
	waitmessage
	waitbuttonpress
	release
	end

EventScript_NoDoubleTrainerBattle::
	gotopostbattlescript

EventScript_DoNoIntroTrainerBattle::
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
	applymovement VAR_LAST_TALKED, Movement_RevealTrainer
	waitmovement 0
	clearflag FLAG_SAFE_FOLLOWER_MOVEMENT
	special PlayTrainerEncounterMusic
	call EventScript_TryTrainerPreBattleHeal
	dotrainerbattle
	gotopostbattlescript

EventScript_TryDoRematchBattle::
	call EventScript_RevealTrainer
	specialvar VAR_RESULT, IsTrainerReadyForRematch
	goto_if_eq VAR_RESULT, FALSE, EventScript_NoRematchTrainerBattle
	special PlayTrainerEncounterMusic
	special SetTrainerFacingDirection
	special ShowTrainerIntroSpeech
	waitmessage
	waitbuttonpress
	call EventScript_TryTrainerPreBattleHeal
	special BattleSetup_StartRematchBattle
	waitstate
	releaseall
	end

EventScript_NoRematchTrainerBattle::
	gotopostbattlescript

EventScript_TryDoDoubleRematchBattle::
	specialvar VAR_RESULT, IsTrainerReadyForRematch
	goto_if_eq VAR_RESULT, FALSE, EventScript_NoDoubleRematchTrainerBattle
	special HasEnoughMonsForDoubleBattle
	goto_if_ne VAR_RESULT, PLAYER_HAS_TWO_USABLE_MONS, EventScript_NotEnoughMonsForDoubleRematchBattle
	special PlayTrainerEncounterMusic
	special SetTrainerFacingDirection
	special ShowTrainerIntroSpeech
	waitmessage
	waitbuttonpress
	call EventScript_TryTrainerPreBattleHeal
	special BattleSetup_StartRematchBattle
	waitstate
	releaseall
	end

EventScript_NoDoubleRematchTrainerBattle::
	gotopostbattlescript

EventScript_NotEnoughMonsForDoubleRematchBattle::
	special ShowTrainerCantBattleSpeech
	waitmessage
	waitbuttonpress
	release
	end

EventScript_RevealTrainer::
	setflag FLAG_SAFE_FOLLOWER_MOVEMENT
	applymovement VAR_LAST_TALKED, Movement_RevealTrainer
	waitmovement 0
	clearflag FLAG_SAFE_FOLLOWER_MOVEMENT
	return

Movement_RevealTrainer:
	reveal_trainer
	step_end

EventScript_ShowTrainerIntroMsg::
	special ShowTrainerIntroSpeech
	waitmessage
	waitbuttonpress
	special TryPrepareSecondApproachingTrainer
	goto_if_eq VAR_RESULT, TRUE, EventScript_TrainerApproach
	goto EventScript_DoTrainerBattle

EventScript_DoTrainerBattle::
	call EventScript_TryTrainerPreBattleHeal
	dotrainerbattle
	@ Below battle mode check only needed in FRLG
	specialvar VAR_RESULT, GetTrainerBattleMode
	goto_if_eq VAR_RESULT, TRAINER_BATTLE_SINGLE, EventScript_EndTrainerBattle
	goto_if_eq VAR_RESULT, TRAINER_BATTLE_CONTINUE_SCRIPT, EventScript_EndTrainerBattle
	goto_if_eq VAR_RESULT, TRAINER_BATTLE_CONTINUE_SCRIPT_NO_MUSIC, EventScript_EndTrainerBattle
	goto_if_eq VAR_RESULT, TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE, EventScript_EndTrainerBattle
	goto_if_eq VAR_RESULT, TRAINER_BATTLE_CONTINUE_SCRIPT_DOUBLE_NO_MUSIC, EventScript_EndTrainerBattle
EventScript_EndTrainerBattle::
	gotobeatenscript
	releaseall
	end

EventScript_TryTrainerPreBattleHeal::
	specialvar VAR_RESULT, TryHealPlayerPartyBeforeTrainerBattle
	goto_if_eq VAR_RESULT, TRAINER_PRE_BATTLE_HEAL_NONE, EventScript_DidNotHealBeforeTrainerBattle
	playse SE_USE_ITEM
	goto_if_eq VAR_RESULT, TRAINER_PRE_BATTLE_HEAL_OLD_GATEAU, EventScript_TrainerUsedOldGateau
	goto_if_eq VAR_RESULT, TRAINER_PRE_BATTLE_HEAL_LAVA_COOKIE, EventScript_TrainerUsedLavaCookies
	goto_if_eq VAR_RESULT, TRAINER_PRE_BATTLE_HEAL_PEWTER_CRUNCHIES, EventScript_TrainerUsedPewterCrunchies
	goto_if_eq VAR_RESULT, TRAINER_PRE_BATTLE_HEAL_RAGE_CANDY_BAR, EventScript_TrainerUsedRageCandyBars
	goto_if_eq VAR_RESULT, TRAINER_PRE_BATTLE_HEAL_HEAL_POWDER, EventScript_TrainerUsedHealPowder
	goto_if_eq VAR_RESULT, TRAINER_PRE_BATTLE_HEAL_FULL_HEAL, EventScript_TrainerUsedFullHeals
	goto_if_eq VAR_RESULT, TRAINER_PRE_BATTLE_HEAL_CASTELIACONE, EventScript_TrainerUsedCasteliacones
	goto_if_eq VAR_RESULT, TRAINER_PRE_BATTLE_HEAL_LUMIOSE_GALETTE, EventScript_TrainerUsedLumioseGalettes
	goto_if_eq VAR_RESULT, TRAINER_PRE_BATTLE_HEAL_SHALOUR_SABLE, EventScript_TrainerUsedShalourSables
	goto_if_eq VAR_RESULT, TRAINER_PRE_BATTLE_HEAL_BIG_MALASADA, EventScript_TrainerUsedBigMalasadas
	goto_if_eq VAR_RESULT, TRAINER_PRE_BATTLE_HEAL_LUM_BERRY, EventScript_TrainerUsedLumBerries
	goto_if_eq VAR_RESULT, TRAINER_PRE_BATTLE_HEAL_JUBILIFE_MUFFIN, EventScript_TrainerUsedJubilifeMuffins
	msgbox TrainerBattle_Text_PartyFullyHealed
	return
EventScript_TrainerUsedOldGateau::
	msgbox TrainerBattle_Text_HexManiacUsedOldGateau
	return
EventScript_TrainerUsedLavaCookies::
	msgbox TrainerBattle_Text_NinjaBoyUsedLavaCookies
	return
EventScript_TrainerUsedPewterCrunchies::
	msgbox TrainerBattle_Text_CollectorUsedPewterCrunchies
	return
EventScript_TrainerUsedRageCandyBars::
	msgbox TrainerBattle_Text_GuitaristUsedRageCandyBars
	return
EventScript_TrainerUsedHealPowder::
	msgbox TrainerBattle_Text_RangerUsedHealPowder
	return
EventScript_TrainerUsedFullHeals::
	msgbox TrainerBattle_Text_CooltrainerUsedFullHeals
	return
EventScript_TrainerUsedCasteliacones::
	msgbox TrainerBattle_Text_BeautyUsedCasteliacones
	return
EventScript_TrainerUsedLumioseGalettes::
	msgbox TrainerBattle_Text_ParasolLadyUsedLumioseGalettes
	return
EventScript_TrainerUsedShalourSables::
	msgbox TrainerBattle_Text_PsychicUsedShalourSables
	return
EventScript_TrainerUsedBigMalasadas::
	msgbox TrainerBattle_Text_PokefanUsedBigMalasadas
	return
EventScript_TrainerUsedLumBerries::
	msgbox TrainerBattle_Text_AromaLadyUsedLumBerries
	return
EventScript_TrainerUsedJubilifeMuffins::
	msgbox TrainerBattle_Text_InterviewerUsedJubilifeMuffins
EventScript_DidNotHealBeforeTrainerBattle::
	return

TrainerBattle_Text_PartyFullyHealed:
	.string "({STR_VAR_1} fully healed your\nPokémon before the battle!)$"

TrainerBattle_Text_HexManiacUsedOldGateau:
	.string "(The Hex Maniac gave each of your\nPokémon an Old Gateau!)$"

TrainerBattle_Text_NinjaBoyUsedLavaCookies:
	.string "(The Ninja Boy gave all your\nPokémon Lava Cookies!)$"

TrainerBattle_Text_CollectorUsedPewterCrunchies:
	.string "(The Collector gave all your\nPokémon Pewter Crunchies!)$"

TrainerBattle_Text_GuitaristUsedRageCandyBars:
	.string "(The Guitarist gave all your\nPokémon Rage Candy Bars!)$"

TrainerBattle_Text_RangerUsedHealPowder:
	.string "(The Pokémon Ranger treated your\nPokémon with Heal Powder!)$"

TrainerBattle_Text_CooltrainerUsedFullHeals:
	.string "(The Cooltrainer gave all your\nPokémon Full Heals!)$"

TrainerBattle_Text_BeautyUsedCasteliacones:
	.string "(The Beauty gave all your\nPokémon Casteliacones!)$"

TrainerBattle_Text_ParasolLadyUsedLumioseGalettes:
	.string "(The Parasol Lady gave all your\nPokémon Lumiose Galettes!)$"

TrainerBattle_Text_PsychicUsedShalourSables:
	.string "(The Psychic gave all your\nPokémon Shalour Sables!)$"

TrainerBattle_Text_PokefanUsedBigMalasadas:
	.string "(The Pokéfan gave all your\nPokémon Big Malasadas!)$"

TrainerBattle_Text_AromaLadyUsedLumBerries:
	.string "(The Aroma Lady gave all your\nPokémon Lum Berries!)$"

TrainerBattle_Text_InterviewerUsedJubilifeMuffins:
	.string "(The Interviewer gave all your\nPokémon Jubilife Muffins!)$"

Std_MsgboxAutoclose::
	message NULL
	waitmessage
	waitbuttonpress
	release
	return
