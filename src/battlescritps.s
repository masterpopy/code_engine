.text
.thumb

.include "asm_defines.s"
.include "defines/bs_commands.s"

//
//Poke Ball block
//

	

.global BS_BALL_BLOCK
BS_BALL_BLOCK:
	jumpifword 4 battle_flags BATTLE_TRAINER BS_TRAINER_BLOCK
	printstring 0x22B
	waitmessage 0x40
BALLBLOCK_CONTINUE:
	cmdf6
	setbyte 0x2024488 0xF
	cmd49 0x1 0x0
	end_cmd
BS_TRAINER_BLOCK:
	printstring 0x103
	waitmessage 0x40
	printstring 0x104
	waitmessage 0x40
	goto_cmd BALLBLOCK_CONTINUE

//Custom loss

.global BS_CUSTOM_LOSS
BS_CUSTOM_LOSS:
	printstring 0x22C
	waitmessage 0x40
	cmd76 1 19 //return to ball
	waitstate
	cmd76 1 20 //return to ball second poke
	waitstate
	trainer_slide 1
	waitstate
	printstring 0x22D
	waitmessage 0x30
	jumpifword Has_One_Bit_Common battle_flags BATTLE_MULTI BS_CUSTOM_SLIDE_TRAINER2
	end_cmd
BS_CUSTOM_SLIDE_TRAINER2:
	trainer_back_slide 1
	waitstate
	trainer_slide 3
	waitstate
	trainer_back_slide 3
	waitstate
	end_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@Trainer sliding
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	
.global BS_TRAINER_SLIDE_MSG_RETURN
BS_TRAINER_SLIDE_MSG_RETURN:
	callasm_cmd 133
	trainer_slide 1
	waitstate
	printstring 0x22F
	waitmessage 0x30
	trainer_back_slide 1
	waitstate
	callasm_cmd 134
	return_cmd
	
.global BS_TRAINER_SLIDE_MSG_END2	
BS_TRAINER_SLIDE_MSG_END2:
	call BS_TRAINER_SLIDE_MSG_RETURN
	end2

BS_POKE_FAINTS_EXP_SLIDEIN:
	callasm_cmd 135
	setbyte 0x02024490 0x0 @exp command state tracker
	giveexp 0
	end2
	
.global BS_PRINT_SPORT_FADED
BS_PRINT_SPORT_FADED:
	printstring 0x231
	waitmessage 0x40
	end2
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@Frisk battlescript
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global FRISK_BS
FRISK_BS:
	pause_cmd 0x20
	setbyte 0x202420C 0x0
FRISK_BS_MAIN:
	cmde1 FRISK_BS_END
	jumpifsecondarystatus 0x0 0x100000 FRISK_BS_ITER
	callasm_cmd 0x7 @@callasm from table
	waitmessage 0x40
FRISK_BS_ITER:
	addbyte 0x202420C 0x1
	goto_cmd FRISK_BS_MAIN
FRISK_BS_END:
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ bad dreams
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BAD_DREAMS_BS
BAD_DREAMS_BS:	
	pause_cmd 0x20
	setbyte 0x202420C 0x0
BAD_DREAMS_BS_MAIN:
	cmde1 BAD_DREAMS_BS_END
	jumpifstatus 0x0 0x7 BAD_DREAMS_BS_DAMAGE
	goto_cmd BAD_DREAMS_BS_ITER
BAD_DREAMS_BS_DAMAGE:
	jumpifsecondarystatus 0x0 0x100000 BAD_DREAMS_BS_ITER
	jumpifability 0x0 0x62 BAD_DREAMS_BS_ITER
	callasm_cmd 0xB @@callasm from table
	@@ playanimation
	printstring 0x1A2
	waitmessage 0x40
	graphicalhpupdate 0
	datahpupdate 0
	faintpokemon 0 0 0
BAD_DREAMS_BS_ITER:
	addbyte 0x202420C 0x1
	goto_cmd BAD_DREAMS_BS_MAIN
BAD_DREAMS_BS_END:
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Intimidate
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_INTIMIDATE
BS_INTIMIDATE:
	callasm_cmd 150
	.word BS_INTIMIDATE_END @jump if all two targets are behind substitute
	pause_cmd 0x20
	setbyte 0x202420C 0x0
	call BS_PRINT_ATK_ABILITY
	recordability bank_attacker
BS_INTIMIDATE_LOOP:
	cmde1 BAD_DREAMS_BS_END
	jumpifsubstituteaffects BS_INTIMIDATE_ITER
	setbyte StatChanger 0x91
	call BS_CHANGE_DEF_STAT
BS_INTIMIDATE_ITER:
	addbyte 0x202420C 0x1
	goto_cmd BS_INTIMIDATE_LOOP
BS_INTIMIDATE_END:
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ mega evolution and fervent wish
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_MEGA_EVO
BS_MEGA_EVO:
	callasm_cmd 88
	printstring 0x205
BS_MEGA_EVO_STUFF:
	playanimation bank_attacker 0x1E 0x0
	waitstate
	callasm_cmd 106
	callasm_cmd 89
	printstring 0x204
	waitmessage 0x40
	callasm_cmd 0
	end3
	
.global BS_FERVENT_EVO
BS_FERVENT_EVO:
	callasm_cmd 88
	printstring 0x206
	goto_cmd BS_MEGA_EVO_STUFF
	
.global BS_LIGHT_UP
BS_LIGHT_UP:
	callasm_cmd 88
	printstring 0x188
	goto_cmd BS_MEGA_EVO_STUFF

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ primal reversion
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_ALPHA_PRIMAL
BS_ALPHA_PRIMAL:
	pause_cmd 0x20
	playanimation bank_attacker 0x1F 0
BS_PRIMAL:
	waitstate
	callasm_cmd 106
	callasm_cmd 89
	printstring 0x210
	waitmessage 0x40
	callasm_cmd 0
	end3
	
.global BS_OMEGA_PRIMAL
BS_OMEGA_PRIMAL:
	pause_cmd 0x20
	playanimation bank_attacker 0x20 0
	goto_cmd BS_PRIMAL
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ telekinesis end
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_TELEKINESIS_ENDS_RET
BS_TELEKINESIS_ENDS_RET:
	printstring 0x1B9
	waitmessage 0x40
	return_cmd
	
.global BS_TELEKINESIS_ENDS_2
BS_TELEKINESIS_ENDS_2:
	call BS_TELEKINESIS_ENDS_RET
	end2
	
.global BS_PRINT_DEF_ABILITY
BS_PRINT_DEF_ABILITY:
	printstring 0x195 @target ability
	waitmessage 0x40
	return_cmd
	
BS_PRINT_SCR_ACTIVE_ABILITY:
	printstring 0x232
	waitmessage 0x40
	return_cmd
	
BS_PRINT_ATK_ABILITY:
	printstring 0x237
	waitmessage 0x40
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ target ability changes attacker's stat
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_DEF_ABILITY_CHANGES_ATK_STAT
BS_DEF_ABILITY_CHANGES_ATK_STAT:
	waitstate
	call BS_PRINT_DEF_ABILITY
	
.global BS_CHANGE_ATK_STAT
BS_CHANGE_ATK_STAT:
	statbuffchange bank_attacker ONE_STAT_RETURN
	jumpifbyte Equals 0x2024337 0x1 ONE_STAT_USER_STATANIM
	goto_cmd ONE_STAT_PRINT
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ attacker ability changes attacker's stat
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_ATK_ABILITY_CHANGES_ATK_STAT
BS_ATK_ABILITY_CHANGES_ATK_STAT:
	waitstate
	call BS_PRINT_ATK_ABILITY
	
.global BS_CHANGE_ATK_STAT_SELFINFLICTED
BS_CHANGE_ATK_STAT_SELFINFLICTED:
	statbuffchange bank_attacker | STAT_SELF_INFLICTED ONE_STAT_RETURN
	jumpifbyte Equals 0x2024337 0x1 ONE_STAT_USER_STATANIM
	goto_cmd ONE_STAT_PRINT
	
.global BS_ATK_ABILITY_CHANGES_ATK_STAT_END3
BS_ATK_ABILITY_CHANGES_ATK_STAT_END3:
	call BS_ATK_ABILITY_CHANGES_ATK_STAT
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ target ability changes target's stat
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_DEF_ABILITY_CHANGES_DEF_STAT
BS_DEF_ABILITY_CHANGES_DEF_STAT:
	waitstate
	call BS_PRINT_DEF_ABILITY
	
.global BS_CHANGE_DEF_STAT_SELFINFLICTED
BS_CHANGE_DEF_STAT_SELFINFLICTED:
	statbuffchange bank_target | STAT_SELF_INFLICTED ONE_STAT_RETURN
BS_CHANGE_DEF_STAT_ANIMPRINT:
	jumpifbyte Equals 0x2024337 0x1 ONE_STAT_TARGET_STATANIM
	goto_cmd ONE_STAT_PRINT
	
.global BS_CHANGE_DEF_STAT
BS_CHANGE_DEF_STAT:
	statbuffchange bank_target ONE_STAT_RETURN
	goto_cmd BS_CHANGE_DEF_STAT_ANIMPRINT
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Defiant and Competitive
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_DEFIANT
BS_DEFIANT:
	pause_cmd 0x25
	setbyte StatChanger 0x21
BS_DEFIANT_STATCHANGE:
	callasm_cmd 156 @turns on stat animation
	call BS_DEF_ABILITY_CHANGES_DEF_STAT
	return_cmd
	
.global BS_COMPETITIVE
BS_COMPETITIVE:
	pause_cmd 0x25
	setbyte StatChanger 0x24
	goto_cmd BS_DEFIANT_STATCHANGE
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Weak Armor
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_WEAK_ARMOR
BS_WEAK_ARMOR:
	waitstate
	call BS_PRINT_DEF_ABILITY
	setbyte StatChanger 0x92
	call BS_CHANGE_DEF_STAT_SELFINFLICTED
	setbyte StatChanger 0x23
	call BS_CHANGE_DEF_STAT_SELFINFLICTED
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ item stat raise scripting active
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_ITEMSTATRAISE
BS_ITEMSTATRAISE:
	playanimation bank_scripting_active 0x7 0
	waitanimation
	statbuffchange bank_scripting_active | STAT_SELF_INFLICTED BS_ITEMSTATRAISE_RET
	jumpifbyte Not_Equal_To MultiStringChooser 1 BS_ITEMSTATRAISE_RET
	set_statchange_values
	playanimation bank_scripting_active 0x1 0x2024484
	printstring 0x23D
	waitmessage 0x40
	removeitem bank_scripting_active
BS_ITEMSTATRAISE_RET:
	return_cmd
	
.global BS_ITEMSTATRAISE_END2
BS_ITEMSTATRAISE_END2:
	call BS_ITEMSTATRAISE
	end2
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ weakness policy
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_WEAKNESSPOLICY
BS_WEAKNESSPOLICY:
	callasm_cmd 153 @prepare custom multiple stats
	.byte bank_scripting_active | STAT_SELF_INFLICTED, MLTS_ATK | MLTS_SPATK, 0x20
	.word BS_WEAKNESSPOLICY_RETURN
	callasm_cmd 154 @raise multiple stats
	.word BS_ITEMSTATRAISE
	.byte MLTS_ATK | MLTS_SPATK, 0x20
BS_WEAKNESSPOLICY_RETURN:
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ bug bite stat raise
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_BUGBITE_STATRAISE
BS_BUGBITE_STATRAISE:
	statbuffchange bank_scripting_active | STAT_SELF_INFLICTED BS_BUGBITE_STATRAISE_RET
	jumpifbyte Not_Equal_To MultiStringChooser 1 ONE_STAT_PRINT
	set_statchange_values
	playanimation bank_scripting_active 0x1 0x2024484
	printstring 0x23D
	waitmessage 0x40
BS_BUGBITE_STATRAISE_RET:
	return_cmd
	
.global BS_BUGBITE_HEALCONDITION
BS_BUGBITE_HEALCONDITION:
	playanimation bank_scripting_active 0x7 0x0
	printfromtable 0x085CC95A
	waitmessage 0x40
	statusiconeupdate bank_scripting_active
	return_cmd
	
.global BS_BUGBITE_PERSIMBERRY
BS_BUGBITE_PERSIMBERRY:
	playanimation bank_scripting_active 0x7 0x0
	printstring 0x128
	waitmessage 0x40
	return_cmd
	
.global BS_BERRYHPHEAL
BS_BERRYHPHEAL:
	playanimation bank_scripting_active 7 0x0
	printstring 0x12A
	waitmessage 0x40
	orword HitMarker HITMARKER_HITSSUBSTITUTE
	graphicalhpupdate bank_scripting_active
	datahpupdate bank_scripting_active
	return_cmd
	
.global BS_BERRYHPHEAL_REMOVEITEM
BS_BERRYHPHEAL_REMOVEITEM:
	call BS_BERRYHPHEAL
	removeitem bank_scripting_active
	return_cmd
	
.global BS_HEALCONFUSE_BERRY
BS_HEALCONFUSE_BERRY:
	call BS_BERRYHPHEAL
	seteffect1 MOVEEFFECT_CONFUSE | MOVEEFFECT_AFFECTSUSER
	seteffectprimary
	return_cmd
	
.global BS_HEALCONFUSE_BERRY_REMOVEITEM
BS_HEALCONFUSE_BERRY_REMOVEITEM:
	call BS_HEALCONFUSE_BERRY
	removeitem bank_scripting_active
	return_cmd
	
.global BS_HEALCONFUSE_BERRY_REMOVEITEM_END2
BS_HEALCONFUSE_BERRY_REMOVEITEM_END2:
	call BS_HEALCONFUSE_BERRY_REMOVEITEM
	end2
	
.global BS_LANSATBERRY
BS_LANSATBERRY:
	playanimation bank_scripting_active 7 0x0
	printstring 0x146
	waitmessage 0x40
	return_cmd
	
.global BS_LANSATBERRY_REMOVEITEM
BS_LANSATBERRY_REMOVEITEM:
	call BS_LANSATBERRY
	removeitem bank_scripting_active
	return_cmd
	
.global BS_LEPPABERRY
BS_LEPPABERRY:
	playanimation bank_scripting_active 7 0x0
	printstring 0x12B
	waitmessage 0x40
	return_cmd
	
.global BS_LEPPABERRY_REMOVEITEM
BS_LEPPABERRY_REMOVEITEM:
	call BS_LEPPABERRY
	removeitem bank_scripting_active
	return_cmd
	
.global BS_LEPPABERRY_REMOVEITEM_END2
BS_LEPPABERRY_REMOVEITEM_END2:
	call BS_LEPPABERRY_REMOVEITEM
	end2
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Terrain surges
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_ELECTRIC_SURGE
BS_ELECTRIC_SURGE:
	pause_cmd 0x20
	call BS_PRINT_SCR_ACTIVE_ABILITY
	printstring 0x1FD @electric currain runs across the battlefield
	waitmessage 0x40
	callasm_cmd 141 @check battle pokemon for terrain seeds
	end3
	
.global BS_MISTY_SURGE
BS_MISTY_SURGE:
	pause_cmd 0x20
	call BS_PRINT_SCR_ACTIVE_ABILITY
	printstring 0x1FB @electric currain runs across the battlefield
	waitmessage 0x40
	callasm_cmd 141 @check battle pokemon for terrain seeds
	end3
	
.global BS_GRASSY_SURGE
BS_GRASSY_SURGE:
	pause_cmd 0x20
	call BS_PRINT_SCR_ACTIVE_ABILITY
	printstring 0x1FC @electric currain runs across the battlefield
	waitmessage 0x40
	callasm_cmd 141 @check battle pokemon for terrain seeds
	end3
	
.global BS_PSYCHIC_SURGE
BS_PSYCHIC_SURGE:
	pause_cmd 0x20
	call BS_PRINT_SCR_ACTIVE_ABILITY
	printstring 0x233 @electric currain runs across the battlefield
	waitmessage 0x40
	callasm_cmd 141 @check battle pokemon for terrain seeds
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS after poke fainted
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_ATK_FAINTED
BS_ATK_FAINTED:
	playfaintingcry bank_attacker
	pause_cmd 0x40
	cmd1a bank_attacker
	cmd1b bank_attacker
	printstring 0x1c
	callasm_cmd 23 @reset var
	callasm_cmd 142 @check soul heart on the whole field
	callasm_cmd 163 @reverts mega
	.byte bank_attacker
	return_cmd
	
.global BS_DEF_FAINTED
BS_DEF_FAINTED:
	playfaintingcry bank_target
	pause_cmd 0x40
	cmd1a bank_target
	cmd1b bank_target
	printstring 0x1d
	callasm_cmd 20 @check Fell Stinger and Moxie
	callasm_cmd 23 @reset var
	callasm_cmd 142 @check soul heart on the whole field
	callasm_cmd 160 @ash_greninja_check
	callasm_cmd 163 @reverts mega
	.byte bank_target
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS receiver
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_RECEIVER
BS_RECEIVER:
	pause_cmd 0x10
	call BS_PRINT_ATK_ABILITY
	callasm_cmd 157
	printstring 0x240
	waitmessage 0x40
	return_cmd

@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS cant use priority move
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_CANTUSE_PRIORITY
BS_CANTUSE_PRIORITY:
	attackstring
	ppreduce
	pause_cmd 0x10
	call BS_PRINT_DEF_ABILITY
	printstring 0x238
	waitmessage 0x30
	goto_cmd ENDTURN

.global BS_CANTUSE_PRIORITY_TERRAIN
BS_CANTUSE_PRIORITY_TERRAIN:
	attackstring
	ppreduce
	pause_cmd 0x10
	printstring 0x238
	waitmessage 0x30
	goto_cmd ENDTURN	
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS got a status condition
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_GOT_STATUS
BS_GOT_STATUS:
	statusanimation 2
	printfromtable condition_strings
	waitmessage 0x40
	statusiconeupdate 2
	waitstate
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ multiple stat chance bank attacker
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_MULTIPLESTATCHANCE_ATK_CERTAIN
BS_MULTIPLESTATCHANCE_ATK_CERTAIN:
	callasm_cmd 28 @checks if can change stats and gets how many
	.byte bank_attacker | STAT_SELF_INFLICTED
	.word BS_MULTIPLESTATCHANCE_ATK_CERTAIN_DO
BS_MULTIPLESTATCHANCE_ATK_CERTAIN_DO:
	callasm_cmd 29 @do all stat changes
	.word BS_CHANGE_ATK_STAT_SELFINFLICTED
	return_cmd

.global BS_MULTIPLESTATCHANCE_ATK
BS_MULTIPLESTATCHANCE_ATK:
	callasm_cmd 28 @checks if can change stats and gets how many
	.byte bank_attacker | STAT_SELF_INFLICTED
	.word BS_MULTIPLESTATCHANCE_ATK_RET
	callasm_cmd 29 @do all stat changes
	.word BS_MULTIPLESTATCHANCE_ATK_DOSTATS
BS_MULTIPLESTATCHANCE_ATK_RET:
	return_cmd
BS_MULTIPLESTATCHANCE_ATK_DOSTATS:
	statbuffchange bank_attacker | STAT_SELF_INFLICTED BS_MULTIPLESTATCHANCE_ATK_DOSTATS_RET
	jumpifbyte Equals 0x2024337 0x1 ONE_STAT_USER_STATANIM
BS_MULTIPLESTATCHANCE_ATK_DOSTATS_RET:
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Moody BS
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_MOODY
BS_MOODY:
	pause_cmd 0x10
	call BS_PRINT_ATK_ABILITY
	callasm_cmd 5 @raise one stat
	callasm_cmd 6 @lower the other
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ set move effect return
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_DEF_ABILITY_STATUS
BS_DEF_ABILITY_STATUS:
	waitstate
	call BS_PRINT_DEF_ABILITY
	seteffectsecondary
	return_cmd
	
.global BS_ATK_ABILITY_STATUS
BS_ATK_ABILITY_STATUS:
	waitstate
	call BS_PRINT_ATK_ABILITY
	seteffectsecondary
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS CURSED BODY
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_CURSEDBODY
BS_CURSEDBODY:
	waitstate
	call BS_PRINT_DEF_ABILITY
	printstring 0x196
	waitmessage 0x40
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Mummy
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_MUMMY
BS_MUMMY:
	waitstate
	call BS_PRINT_DEF_ABILITY
	printstring 0x194
	waitmessage 0x40
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Rough Skin
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_ROUGHSKIN
BS_ROUGHSKIN:
	waitstate
	call BS_PRINT_DEF_ABILITY
	orword HitMarker HITMARKER_HITSSUBSTITUTE
BS_ATTACKER_HURT:
	graphicalhpupdate bank_attacker
	datahpupdate bank_attacker
	printstring 0x23B
	waitmessage 0x40
	faintpokemon bank_attacker 0 0
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Anger Point
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_ANGERPOINT
BS_ANGERPOINT:
	waitstate
	call BS_PRINT_DEF_ABILITY
	printstring 0x1A9
	waitmessage 0x40
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Aftermath
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_AFTERMATH
BS_AFTERMATH:
	waitstate
	call BS_PRINT_DEF_ABILITY
	graphicalhpupdate bank_attacker
	datahpupdate bank_attacker
	printstring 0x192
	waitmessage 0x40
	faintpokemon bank_attacker 0 0
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Cute Charm
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_CUTECHARM
BS_CUTECHARM:
	waitstate
	call BS_PRINT_DEF_ABILITY
	status2animation bank_attacker STATUS2_INLOVE
	printstring 0x23C
	waitmessage 0x40
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Download
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_DOWNLOAD
BS_DOWNLOAD:
	pause_cmd 0x10
	call BS_PRINT_ATK_ABILITY
	call BS_CHANGE_ATK_STAT_SELFINFLICTED
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Forewarn
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_FOREWARN
BS_FOREWARN:
	pause_cmd 0x10
	call BS_PRINT_SCR_ACTIVE_ABILITY
	printstring 0x181
	waitmessage 0x40
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Anticipation
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_ANTICIPATION
BS_ANTICIPATION:
	pause_cmd 0x10
	call BS_PRINT_SCR_ACTIVE_ABILITY
	printstring 0x183
	waitmessage 0x40
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Protean
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_PROTEAN
BS_PROTEAN:
	call BS_PRINT_ATK_ABILITY
	printstring 0x218
	waitmessage 0x40
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Ability HP change
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

BS_ABILITYHPCHANGE:
	call BS_PRINT_ATK_ABILITY
BS_ATTACKER_HPUDPATE:
	graphicalhpupdate bank_attacker
	datahpupdate bank_attacker
	faintpokemon bank_attacker 0 0
	return_cmd

.global BS_ABILITYHPCHANGE_END2
BS_ABILITYHPCHANGE_END2:
	call BS_ABILITYHPCHANGE
	end2
	
.global BS_ABILITYHPCHANGE_END3
BS_ABILITYHPCHANGE_END3:
	call BS_ABILITYHPCHANGE
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Harvest
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_HARVEST
BS_HARVEST:
	call BS_PRINT_ATK_ABILITY
	recycleitem BS_HARVEST_END
	printstring 0x186
	waitmessage 0x40
BS_HARVEST_END:
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Snow Warning
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_SNOWWARNING
BS_SNOWWARNING:
	pause_cmd 0x10
	call BS_PRINT_SCR_ACTIVE_ABILITY
	printstring 0xF3
	playanimation bank_scripting_active 13 0x0
	waitanimation
	call BS_CHECKCASTFORMCHERRIM
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Drought
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_DROUGHT
BS_DROUGHT:
	pause_cmd 0x10
	call BS_PRINT_SCR_ACTIVE_ABILITY
	printstring 0xF0
	playanimation bank_scripting_active 11 0x0
	waitanimation
	call BS_CHECKCASTFORMCHERRIM
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Drizzle
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_DRIZZLE
BS_DRIZZLE:
	pause_cmd 0x10
	call BS_PRINT_SCR_ACTIVE_ABILITY
	printstring 0xE8
	playanimation bank_scripting_active 10 0x0
	waitanimation
	call BS_CHECKCASTFORMCHERRIM
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Sandstream
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_SANDSTREAM
BS_SANDSTREAM:
	pause_cmd 0x10
	call BS_PRINT_SCR_ACTIVE_ABILITY
	printstring 0xED
	playanimation bank_scripting_active 12 0x0
	waitanimation
	call BS_CHECKCASTFORMCHERRIM
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Air Lock
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_AIRLOCK
BS_AIRLOCK:
	pause_cmd 0x10
	call BS_PRINT_ATK_ABILITY
	printstring 0x185
	waitmessage 0x40
	call BS_CHECKCASTFORMCHERRIM
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Desolate Land
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_DESOLATELAND
BS_DESOLATELAND:
	pause_cmd 0x10
	call BS_PRINT_SCR_ACTIVE_ABILITY
	printstring 0x17E
	playanimation bank_scripting_active 11 0x0
	waitanimation
	call BS_CHECKCASTFORMCHERRIM
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Primordial Sea
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_PRIMORDIALSEA
BS_PRIMORDIALSEA:
	pause_cmd 0x10
	call BS_PRINT_SCR_ACTIVE_ABILITY
	printstring 0x17F
	playanimation bank_scripting_active 10 0x0
	waitanimation
	call BS_CHECKCASTFORMCHERRIM
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Delta Stream
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_DELTASTREAM
BS_DELTASTREAM:
	pause_cmd 0x10
	call BS_PRINT_SCR_ACTIVE_ABILITY
	printstring 0x180
	waitmessage 0x40
	call BS_CHECKCASTFORMCHERRIM
	end3
	
.global BS_CHECKCASTFORMCHERRIM
BS_CHECKCASTFORMCHERRIM:
	setbyte BankScriptingActive 0x0
BS_CASTFORMCHECK_LOOP:
	checkcastform
	addbyte BankScriptingActive 0x1
	jumpifarraynotequal BankScriptingActive no_of_all_banks 1 BS_CASTFORMCHECK_LOOP
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Castform Switch
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_CASTFORMSWITCH
BS_CASTFORMSWITCH:
	castformchangeanim
BS_CASTSWITCHWAITPRINT:
	waitanimation
	printstring 0x13A
	waitmessage 0x40
	return_cmd
	
.global BS_CASTFORMSWITCH_END3
BS_CASTFORMSWITCH_END3:
	call BS_CASTFORMSWITCH
	end3
	
.global BS_CHERRIMSWITCH
BS_CHERRIMSWITCH:
	callasm_cmd 114 @sets transformed species to 0
	playanimation bank_scripting_active 0x21 0x0
	goto_cmd BS_CASTSWITCHWAITPRINT
	
.global BS_CHERRIMSWITCH_END3
BS_CHERRIMSWITCH_END3:
	call BS_CHERRIMSWITCH
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Trace
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_TRACE
BS_TRACE:
	pause_cmd 0x10
	printstring 0xD0
	waitanimation
	callasm_cmd 0	@calls switch-in abilities
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Imposter
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_IMPOSTER
BS_IMPOSTER:
	pause_cmd 0x10
	call BS_PRINT_ATK_ABILITY
	callasm_cmd 116 @sets palette change
	transformdataexecution
	attackanimation
	waitanimation
	printstring 0x7D
	waitmessage 0x40
	callasm_cmd 0	@calls switch-in abilities
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Illusion
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_ILLUSION_OFF
BS_ILLUSION_OFF:
	playanimation bank_target 0x21 0x0
	waitanimation
	callasm_cmd 112	@updates the hp box
	callasm_cmd 113	@sets the graphical transformed species to 0
	printstring 0x217
	waitmessage 0x40
	return_cmd
	
.global BS_ILLUSION_OFF2
BS_ILLUSION_OFF2:
	playanimation bank_attacker 0x21 0x0
	waitanimation
	waitmessage 0x40
	return_cmd		
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Slow Start
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_SLOWSTART_MSG1
BS_SLOWSTART_MSG1:
	pause_cmd 0x10
	call BS_PRINT_SCR_ACTIVE_ABILITY
	printstring 0x182
	waitmessage 0x40
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Dark Aura
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_DARKAURA
BS_DARKAURA:
	pause_cmd 0x10
	call BS_PRINT_SCR_ACTIVE_ABILITY
	printstring 0x19C
	waitmessage 0x40
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Fairy Aura
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_FAIRYAURA
BS_FAIRYAURA:
	pause_cmd 0x10
	call BS_PRINT_SCR_ACTIVE_ABILITY
	printstring 0x19B
	waitmessage 0x40
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Aura Break
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_AURABREAK
BS_AURABREAK:
	pause_cmd 0x10
	call BS_PRINT_SCR_ACTIVE_ABILITY
	printstring 0x19a
	waitmessage 0x40
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Mold Breaker
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_MOLDBREAKER
BS_MOLDBREAKER:
	pause_cmd 0x10
	call BS_PRINT_SCR_ACTIVE_ABILITY
	printfromtable moldbreaker_strings
	waitmessage 0x40
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Unnerve
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_UNNERVE
BS_UNNERVE:
	pause_cmd 0x10
	call BS_PRINT_ATK_ABILITY
	printstring 0x199
	waitmessage 0x40
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Pressure
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_PRESSURE
BS_PRESSURE:
	pause_cmd 0x10
	call BS_PRINT_SCR_ACTIVE_ABILITY
	printstring 0x198
	waitmessage 0x40
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Sturdy endures hit
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_STURDYENDURES
BS_STURDYENDURES:
	pause_cmd 0x10
	call BS_PRINT_DEF_ABILITY
	printstring 0x99
	waitmessage 0x40
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Pick UP
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_PICKUP
BS_PICKUP:
	call BS_PRINT_ATK_ABILITY
	pause_cmd 0x15
	printstring 0x140
	waitmessage 0x40
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Cheek Pouch
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_CHEEKPOUCH
BS_CHEEKPOUCH:
	call BS_PRINT_SCR_ACTIVE_ABILITY
	graphicalhpupdate bank_scripting_active
	datahpupdate bank_scripting_active
	printstring 0x241
	waitmessage 0x40
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS PickPocket
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_PICKPOCKET
BS_PICKPOCKET:
	call BS_PRINT_DEF_ABILITY
	playanimation bank_target 0x22 0
	printstring 0x193
	waitmessage 0x40
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Magician
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_MAGICIAN
BS_MAGICIAN:
	call BS_PRINT_ATK_ABILITY
	playanimation bank_target 16 0
	printstring 0x8E
	waitmessage 0x40
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Magic Bounce
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_MAGICBOUNCE
BS_MAGICBOUNCE:
	attackstring
	ppreduce
	pause_cmd 0x10
	call BS_PRINT_DEF_ABILITY
	goto_cmd 0x082DB199 @Magic Coat BS
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Telepathy
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_TELEPATHY
BS_TELEPATHY:
	ppreduce
	attackstring
	pause_cmd 0x10
	call BS_PRINT_DEF_ABILITY
	printstring 0x21A
	waitmessage 0x40
	goto_cmd ENDTURN
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Symbiosis
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_SYMBIOSIS
BS_SYMBIOSIS:
	playanimation bank_scripting_active 0x23 0x0
	printstring 0x1B6
	waitmessage 0x40
	callasm_cmd 22 @call switch in item effects
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Healer
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_HEALER
BS_HEALER:
	pause_cmd 0x10
	call BS_PRINT_ATK_ABILITY
	printstring 0x187
	waitmessage 0x40
	statusiconeupdate bank_scripting_active
	end3
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Synchronize
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_SYNCHRONIZE
BS_SYNCHRONIZE:
	call BS_PRINT_SCR_ACTIVE_ABILITY
	seteffectprimary
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Stat Raise Immune ability
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_IMMUNESTATRAISE_ABILITY
BS_IMMUNESTATRAISE_ABILITY:
	ppreduce
	attackstring
	pause_cmd 0x10
	call BS_DEF_ABILITY_CHANGES_DEF_STAT
	goto_cmd ENDTURN
	
.global BS_IMMUNE_ABILITY
BS_IMMUNE_ABILITY:
	ppreduce
	attackstring
	pause_cmd 0x10
	callasm_cmd 9 @buffer type
	printstring 0x18F
	waitmessage 0x40
	goto_cmd ENDTURN
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Burn Up effect
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_BURNUP
BS_BURNUP:
	printstring 0x23F
	waitmessage 0x40
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Toxic, Flame, Life Orbs
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_TOXICORB
BS_TOXICORB:
	pause_cmd 0x10
	statusanimation bank_attacker
	printstring 0x1A0
BS_ORBICONUPDATE:
	waitmessage 0x40
	statusiconeupdate bank_attacker
	end2
	
.global BS_FLAMEORB
BS_FLAMEORB:
	pause_cmd 0x10
	statusanimation bank_attacker
	printstring 0x19F
	goto_cmd BS_ORBICONUPDATE
	
.global BS_LIFEORB
BS_LIFEORB:
	pause_cmd 0x10
	graphicalhpupdate bank_attacker
	datahpupdate bank_attacker
	printstring 0x1AE
BS_WAITMSG_FAINTATTACKER:
	waitmessage 0x40
	faintpokemon bank_attacker 0 0
	return_cmd
	
.global BS_ROCKYHELMET
BS_ROCKYHELMET:
	playanimation bank_attacker 15 0
	graphicalhpupdate bank_attacker
	datahpupdate bank_attacker
	printstring 0x1A4
	goto_cmd BS_WAITMSG_FAINTATTACKER
	
.global BS_STICKYBARB
BS_STICKYBARB:
	playanimation bank_attacker 15 0
	graphicalhpupdate bank_attacker
	datahpupdate bank_attacker
	printstring 0x1A3
	call BS_WAITMSG_FAINTATTACKER
	end2
	
.global BS_AIRBALLOON_SWITCHIN
BS_AIRBALLOON_SWITCHIN:
	pause_cmd 0x10
	printstring 0x1A1
	waitmessage 0x40
	end2
	
.global BS_AIRBALLOON_POPS
BS_AIRBALLOON_POPS:
	printstring 0x1A5
	waitmessage 0x40
	removeitem bank_target
	return_cmd
	
.global BS_POWERHERB
BS_POWERHERB:
	pause_cmd 0x10
	playanimation bank_attacker 7 0
	printstring 0x1F7
	waitmessage 0x40
	removeitem bank_attacker
	return_cmd

.global BS_POWDER
BS_POWDER:
	attackstring
	ppreduce
	pause_cmd 0x10
	printstring 0x1E1
	waitmessage 0x40
	hitanim bank_attacker
	waitanimation
	call BS_ATTACKER_HPUDPATE
	goto_cmd ENDTURN
	
.global BS_DESTINYKNOT
BS_DESTINYKNOT:
	status2animation bank_attacker STATUS2_INLOVE
	printstring 0x1A6
	waitmessage 0x40
	return_cmd
	
.global BS_MENTALHERB
BS_MENTALHERB:
	playanimation bank_scripting_active 7 0x0
	callasm_cmd 13
	removeitem bank_scripting_active
	return_cmd
	
.global BS_MENTALHERB_END2
BS_MENTALHERB_END2:
	call BS_MENTALHERB
	end2
	
.global BS_GEM_MSG
BS_GEM_MSG:
	pause_cmd 0x40
	printstring 0x219
	waitmessage 0x40
	removeitem bank_attacker
	return_cmd
	
.global BS_START_Z
BS_START_Z:
	printstring 0x18D
	callasm_cmd 171
	waitmessage 0x40
	playanimation bank_attacker 0x25 0x0
	callasm_cmd 106
	waitstate
	callasm_cmd 166
	.word BS_CHANGE_ATK_STAT_SELFINFLICTED
	return_cmd
	orword 0x2024280 0x100
	graphicalhpupdate 0x1
	datahpupdate 0x1
	printstring 0x4B
	waitmessage 0x40
	return_cmd
	
.global BS_BERRY_DMG_REDUCE
BS_BERRY_DMG_REDUCE:
	pause_cmd 0x20
	playanimation bank_target 7 0x0
	printstring 0x22A
	waitmessage 0x40
	removeitem bank_target
	return_cmd
	
BS_ITEMSWITCH_REMOVEPLAY:
	waitmessage 0x40
	removeitem bank_scripting_active
	playanimation bank_newstruct 0x24 0x0
	waitanimation
	return_cmd
	
.global BS_REDCARD_SWITCH
BS_REDCARD_SWITCH:
	jumpifcannotswitch bank_newstruct | 0x80 BS_ITEM_SWITCH_RET @this should be checked beforehand
	printstring 0x1A8
	call BS_ITEMSWITCH_REMOVEPLAY
	callasm_cmd 159 @prepare switchin data
	.byte bank_newstruct
	swithchoutabilities bank_newstruct
BS_ITEMSWITCH_ACTUALSWITCH:
	return_to_ball bank_newstruct
	waitstate
	switch1 bank_newstruct
	switch2 bank_newstruct
	switch3 bank_newstruct 0x0
	waitstate
	printstring 0x154
	switchineffects bank_newstruct
BS_ITEM_SWITCH_RET:
	return_cmd
	
.global BS_EJECTBUTTON_SWITCH
BS_EJECTBUTTON_SWITCH:
	jumpifcannotswitch bank_newstruct | 0x80 BS_ITEM_SWITCH_RET @this should be checked beforehand
	printstring 0x1AC
	call BS_ITEMSWITCH_REMOVEPLAY
BS_EJECTBUTTONLIKE_SWITCHING_PART:
	openpartyscreen bank_newstruct BS_ITEM_SWITCH_RET
	swithchoutabilities bank_newstruct
	waitstate
	switch_handle_order bank_newstruct 0x2
	goto_cmd BS_ITEMSWITCH_ACTUALSWITCH
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Emergency Exit
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_WIMPOUT
BS_WIMPOUT:
	call BS_PRINT_DEF_ABILITY
	playanimation bank_newstruct 0x24 0x0
	waitanimation
	goto_cmd BS_EJECTBUTTONLIKE_SWITCHING_PART
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Usage Prevention
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_HEALBLOCK_PREVENTS
BS_HEALBLOCK_PREVENTS:
	attackstring
	pause_cmd 0x20
	printstring 0x1B1
BS_PPREDUCE_FAIL_WAITMSG_ENDTURN:
	waitmessage 0x40
	ppreduce
	orbyte MoveOutcome OutcomeFailed
	goto_cmd ENDTURN
	
.global BS_GRAVITY_PREVENTS
BS_GRAVITY_PREVENTS:
	attackstring
	pause_cmd 0x20
	printstring 0x1B2
	goto_cmd BS_PPREDUCE_FAIL_WAITMSG_ENDTURN
	
.global BS_EMBARGO_PREVENTS
BS_EMBARGO_PREVENTS:
	attackstring
	pause_cmd 0x20
	printstring 0x1B3
	goto_cmd BS_PPREDUCE_FAIL_WAITMSG_ENDTURN
	
.global BS_HEAVYRAIN_PREVENTS
BS_HEAVYRAIN_PREVENTS:
	attackstring
	pause_cmd 0x20
	printstring 0x1BD
	goto_cmd BS_PPREDUCE_FAIL_WAITMSG_ENDTURN
	
.global BS_HARSHSUN_PREVENTS
BS_HARSHSUN_PREVENTS:
	attackstring
	pause_cmd 0x20
	printstring 0x1BE
	goto_cmd BS_PPREDUCE_FAIL_WAITMSG_ENDTURN
	
.global BS_AROMAVEIL_PREVENTS
BS_AROMAVEIL_PREVENTS:
	attackstring
	pause_cmd 0x20
	printstring 0x1B4
	goto_cmd BS_PPREDUCE_FAIL_WAITMSG_ENDTURN
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Entry Hazards: Spikes, Stealth Rock, Sticky Web, Toxic Spikes
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_SPIKES
BS_SPIKES:
	callasm_cmd 15 @save target bank
	graphicalhpupdate bank_target
	datahpupdate bank_target
	printstring 0x95
BS_HAZARDSDMG:
	waitmessage 0x40
	faintpokemon bank_target 0 0
	faintpokemon bank_target 1 0x82DAEB1
	callasm_cmd 16 @restore saved bank
	return_cmd
	
.global BS_STEALTHROCK
BS_STEALTHROCK:
	callasm_cmd 15 @save target bank
	graphicalhpupdate bank_target
	datahpupdate bank_target
	printstring 0x1AA
	goto_cmd BS_HAZARDSDMG
	
.global BS_STICKYWEB
BS_STICKYWEB:
	callasm_cmd 15 @save target bank
	printstring 0x1AB
	waitmessage 0x40
	call BS_CHANGE_DEF_STAT
	callasm_cmd 16 @restore saved bank
	return_cmd
	
.global BS_TOXICSPIKES
BS_TOXICSPIKES:
	callasm_cmd 15 @save target bank
	statusanimation bank_target
	printfromtable condition_strings
	waitmessage 0x40
	statusiconeupdate bank_target
	waitstate
	callasm_cmd 16 @restore saved bank
	return_cmd
	
.global BS_TOXICSPIKESABSORBED
BS_TOXICSPIKESABSORBED:
	callasm_cmd 15 @save target bank
	chosenstatusanimation bank_target 0 STATUS_POISON
	printstring 0x1EC
	waitmessage 0x40
	callasm_cmd 16 @restore saved bank
	return_cmd
	
.global BS_LUNARDANCE
BS_LUNARDANCE:
	callasm_cmd 15 @save target bank
	playanimation bank_target 22 0
	graphicalhpupdate bank_target
	datahpupdate bank_target
	statusiconeupdate bank_target
	printstring 0x1B8
	waitmessage 0x40
	callasm_cmd 16 @restore saved bank
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Things end
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_HEALBLOCKEND
BS_HEALBLOCKEND:
	printstring 0x1A7
	waitmessage 0x40
	return_cmd
	
.global BS_HEALBLOCKEND_END2
BS_HEALBLOCKEND_END2:
	call BS_HEALBLOCKEND
	end2
	
.global BS_ROOMEND
BS_ROOMEND:
	printfromtable rooms_strings
	waitmessage 0x40
	end2
	
.global BS_MAGNETRISEEND
BS_MAGNETRISEEND:
	printstring 0x1BB
	waitmessage 0x40
	return_cmd
	
.global BS_MAGNETRISEEND_END2
BS_MAGNETRISEEND_END2:
	call BS_MAGNETRISEEND
	end2
	
.global BS_GRAVITYEND
BS_GRAVITYEND:
	printstring 0x1C2
	waitmessage 0x40
	end2
	
.global BS_GRAVITYBRINGSDOWN
BS_GRAVITYBRINGSDOWN:
	printstring 0x1D7
	waitmessage 0x40
	return_cmd
	
.global BS_EMBARGOEND
BS_EMBARGOEND:
	printstring 0x1BA
	waitmessage 0x40
	end2
	
.global BS_TAUNTEND
BS_TAUNTEND:
	printstring 0x1AF
	waitmessage 0x40
	return_cmd
	
.global BS_TAUNTEND_END2
BS_TAUNTEND_END2:
	call BS_TAUNTEND
	end2
	
.global BS_DISABLEEND
BS_DISABLEEND:
	printstring 0x86
	waitmessage 0x40
	return_cmd
	
.global BS_ENCOREEND
BS_ENCOREEND:
	printstring 0x88
	waitmessage 0x40
	return_cmd
	
.global BS_TORMENTEND
BS_TORMENTEND:
	printstring 0x1B0
	waitmessage 0x40
	return_cmd
	
.global BS_TERRAINEND
BS_TERRAINEND:
	printfromtable terrainend_strings
	waitmessage 0x40
	end2

.global BS_THROATCHOPEND
BS_THROATCHOPEND:
	printstring 0x260
	waitmessage 0x40
	return_cmd

.global BS_THROATCHOPEND_END2
BS_THROATCHOPEND_END2:
	call BS_THROATCHOPEND
	end2
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Some move effects
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_SMACKDOWN
BS_SMACKDOWN:
	printstring 0x1EB
	waitmessage 0x40
	return_cmd
	
.global BS_AQUARING
BS_AQUARING:
	pause_cmd 0x20
	printstring 0x1FF
	waitmessage 0x40
	graphicalhpupdate bank_attacker
	datahpupdate bank_attacker
	end3
	
.global BS_FLAMEBURST
BS_FLAMEBURST:
	graphicalhpupdate bank_partner_def
	datahpupdate bank_partner_def
	printstring 0x21B
	waitmessage 0x40
	faintpokemon bank_partner_def 0 0
	return_cmd
	
.global BS_DAMAGETRAP
BS_DAMAGETRAP:
	callasm_cmd 68 @sets the trapped bit
	printstring 0x8F
	waitmessage 0x40
	return_cmd
	
.global BS_SPIKYSHIELD
BS_SPIKYSHIELD:
	pause_cmd 0x20
	goto_cmd BS_ATTACKER_HURT
	
.global BS_CLEARSMOG
BS_CLEARSMOG:
	printstring 0x1E2
	waitmessage 0x40
	return_cmd
	
BS_MOVEFIRST:
	printstring 0x130
	playanimation bank_attacker 7 0x0
	printstring 0x203
	waitmessage 0x40
	return_cmd
	
.global BS_QUICKCLAW
BS_QUICKCLAW:
	call BS_MOVEFIRST
	end2
	
.global BS_CUSTAPBERRY
BS_CUSTAPBERRY:
	call BS_MOVEFIRST
	removeitem bank_attacker
	end2
	
.global BS_INCINERATEBERRY
BS_INCINERATEBERRY:
	printstring 0x1D6
	waitmessage 0x40
	return_cmd
	
.global BS_BUGBITE
BS_BUGBITE:
	printstring 0x1D5
	waitmessage 0x40
	callasm_cmd 158 @do berry effect if it can do something
	callasm_cmd 117 @sets berry as eaten
	return_cmd

.global BS_RAPIDSPIN_SPINS
BS_RAPIDSPIN_SPINS:
	printfromtable rapidspin_strings
	waitmessage 0x40
	return_cmd
	
.global BS_LEECHSEED
BS_LEECHSEED:
	playanimation bank_attacker 14 0x02024484
	orword HitMarker HITMARKER_HITSSUBSTITUTE
	graphicalhpupdate bank_attacker
	datahpupdate bank_attacker
	copyarray damage_loc hp_dealt 4
	jumpifability bank_attacker ABILITY_LIQUID_OOZE 0x082DAD47
	callasm_cmd 17 @big root and heal block
	manipulatedamage 0x0 @change sign
	goto_cmd 0x82DAD3C @continue leech seed
	
.global BS_BINDEFFECT
BS_BINDEFFECT:
	printfromtable bind_strings
	waitmessage 0x40
	return_cmd
	
.global CANT_CONFUSE_DUETOABILITY_PRINT_END2
CANT_CONFUSE_DUETOABILITY_PRINT_END2:
	call CANT_CONFUSE_DUETOABILITY_PRINT
	end2
	
.global BS_BEAKBLAST
BS_BEAKBLAST:
	waitstate
	seteffectsecondary
	return_cmd	
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ Cant select a move from menu
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_CANTSELECT_GRAVITY
BS_CANTSELECT_GRAVITY:
	printstring2 0x201
	cmd44
	
.global BS_CANTSELECT_HEALBLOCK
BS_CANTSELECT_HEALBLOCK:
	printstring2 0x202
	cmd44
	
.global BS_CANTSELECT_ASSAULTVEST
BS_CANTSELECT_ASSAULTVEST:
	printstring2 0x200
	cmd44
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ BS Grassy Terrain Heal
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_GRASSYTERRAIN_HEAL
BS_GRASSYTERRAIN_HEAL:
	callasm_cmd 21
	.word BS_GRASSY_HEAL
	end2
	
BS_GRASSY_HEAL:
	playanimation bank_scripting_active 0x15 0x0
	graphicalhpupdate bank_scripting_active
	datahpupdate bank_scripting_active
	printstring 0x1C6
	waitmessage 0x40
	return_cmd
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ 'hook' into part of the bs that asks if you want to switch out after opponent's poke faints
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
BS_ASK_FOR_SWITCHING:
	jumpifword Has_One_Bit_Common battle_flags BATTLE_DOUBLE | BATTLE_LINK | BATTLE_FRONTIER_GENERAL | BATTLE_DOME | BATTLE_PALACE | BATTLE_ARENA | BATTLE_FACTORY | BATTLE_FLAG_x100000 | BATTLE_FLAG_x2000000 0x82DA8D0
	callasm_cmd 1
	.word 0x82DA8D0
	goto_cmd 0x82DA865
	
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@ In battle form(e) changes
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
.global BS_FORMCHANGE_WITH_TYPE_CHANGE
BS_FORMCHANGE_WITH_TYPE_CHANGE:
	call BS_FORMCHANGE_GENERAL
	callasm_cmd 118 @type_stat_form_change
	end2
	
BS_STAT_ONLY_FORMCHANGE_RET:
	call BS_FORMCHANGE_GENERAL
	callasm_cmd 115 @setup_form_change_buffers_outer
	return_cmd

.global BS_STAT_ONLY_FORMCHANGE_END2
BS_STAT_ONLY_FORMCHANGE_END2:
	call BS_STAT_ONLY_FORMCHANGE_RET
	end2
	
.global BS_STAT_ONLY_FORMCHANGE_END3
BS_STAT_ONLY_FORMCHANGE_END3:
	call BS_STAT_ONLY_FORMCHANGE_RET
	end3
	
.global BS_ZYGARDE_FORM_CHANGE
BS_ZYGARDE_FORM_CHANGE:
	callasm_cmd 161 @zygarde_message_based_on_side
	waitmessage 0x40
BS_FORMCHANGE_WITH_HP_CHANGE:	
	call BS_FORMCHANGE_GENERAL
	callasm_cmd 162  @hp_stat_form_change
	end2
		
BS_FORMCHANGE_GENERAL:
	printstring 0x130
	callasm_cmd 119 @change species
	playanimation 0xA 0x21 0x0
	waitstate
	callasm_cmd 122 @prints string in var2
	waitmessage 0x40
	return_cmd

.global BS_BATTLE_BOND
BS_BATTLE_BOND:
	printstring 0x246
	waitmessage 0x40
	call BS_FORMCHANGE_GENERAL
	callasm_cmd 115 @stat_only_form_change
	return_cmd
	
.global BS_MIMIKYU_BUST
BS_MIMIKYU_BUST:
	printstring 0x24C
	waitmessage 0x40
	call BS_FORMCHANGE_GENERAL
	callasm_cmd 118 @type_stat_form_change
	return_cmd
