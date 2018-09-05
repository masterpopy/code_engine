.text

//banks
.equ bank_attacker, 0x0
.equ bank_target, 0x1
.equ attacker_partner, 0x2
.equ target_partner, 0x3

//sides for commands A, B
.equ side_attacker, 0x2
.equ side_target, 0x3

//background IDs
.equ BG_DARK, 0x1
.equ BG_GHOST, 0x2
.equ BG_PSYCHIC, 0x3
.equ BG_IMPACT_ON_OPPONENT, 0x4
.equ BG_IMPACT_ON_PLAYER, 0x5
.equ BG_IMPACT_CONTESTS, 0x6
.equ BG_DRILL_BATTLE, 0x7
.equ BG_DRILL_CONTESTS, 0x8
.equ BG_HIGHSPEED_ON_OPPONENT, 0x9
.equ BG_HIGHSPEED_ON_PLAYER, 0xA
.equ BG_THUNDER, 0xB
.equ BG_GUILLOTINE_ON_OPPONENT, 0xC
.equ BG_GUILLOTINE_ON_PLAYER, 0xD
.equ BG_GUILLOTINE_CONTESTS, 0xE
.equ BG_ICE, 0xF
.equ BG_COSMIC, 0x10
.equ BG_SEISMICTOSS_SKUUPPERCUT, 0x11
.equ BG_FLYING_BATTLE, 0x12
.equ BG_FLYING_CONTESTS, 0x13
.equ BG_AURORABEAM, 0x14
.equ BG_FISSURE, 0x15
.equ BG_BUG_ON_OPPONENT, 0x16
.equ BG_BUG_ON_PLAYER, 0x17
.equ BG_SOLARBEAM_ON_OPPONENT, 0x18
.equ BG_SOLARBEAM_ON_PLAYER, 0x19
.equ BG_SOLARBEAM_CONTESTS, 0x1A

//pals for pal fading tasks
.equ PAL_BG, 0x1
.equ PAL_ATK, 0x2
.equ PAL_DEF, 0x4
.equ PAL_ATK_PARTNER, 0x8
.equ PAL_DEF_PARTNER, 0x10
.equ PAL_ALL_BANKS, 0x780
.equ PAL_PLAYER1, 0x80
.equ PAL_PLAYER2, 0x100
.equ PAL_OPPONENT1, 0x200
.equ PAL_OPPONENT2, 0x400

//commands
.macro loadparticle loadparticleID
.byte 0x0
.hword \loadparticleID
.endm

.macro unloadparticle unloadparticleID
.byte 0x1
.hword \unloadparticleID
.endm

//22
.macro launchtemplate launchtemplatePtr launchtemplatePriority launchtemplateArgsNo launchtemplatearg0 launchtemplatearg1 launchtemplatearg2 launchtemplatearg3 launchtemplatearg4 launchtemplatearg5 launchtemplatearg6 launchtemplatearg7 launchtemplatearg8
.byte 0x2
.word \launchtemplatePtr
.byte \launchtemplatePriority
.byte \launchtemplateArgsNo
.hword \launchtemplatearg0
.hword \launchtemplatearg1
.hword \launchtemplatearg2
.hword \launchtemplatearg3
.hword \launchtemplatearg4
.hword \launchtemplatearg5
.hword \launchtemplatearg6
.hword \launchtemplatearg7
.hword \launchtemplatearg8
.endm

.macro launchtask launchtaskPtr launchtaskPriority launchtaskArgsNo launchtaskarg0 launchtaskarg1 launchtaskarg2 launchtaskarg3 launchtaskarg4 launchtaskarg5 launchtaskarg6 launchtaskarg7 launchtaskarg8
.byte 0x3
.word \launchtaskPtr
.byte \launchtaskPriority
.byte \launchtaskArgsNo
.hword \launchtaskarg0
.hword \launchtaskarg1
.hword \launchtaskarg2
.hword \launchtaskarg3
.hword \launchtaskarg4
.hword \launchtaskarg5
.hword \launchtaskarg6
.hword \launchtaskarg7
.hword \launchtaskarg8
.endm

.macro pause pause_cmdToWait
.byte 0x4
.byte \pause_cmdToWait
.endm

.macro waitanimation
.byte 0x5
.endm

.macro endanimation
.byte 0x8
.endm

.macro playsound1 playsound1ID
.byte 0x9
.hword \playsound1ID
.endm

.macro pokespritetoBG animABank
.byte 0xA
.byte \animABank
.endm

.macro pokespritefromBG animBBank
.byte 0xB
.byte \animBBank
.endm

.macro setblends setblends_value
.byte 0xC
.hword \setblends_value
.endm

.macro resetblends
.byte 0xD
.endm

.macro call call_cmd_ptr
.byte 0xE
.word \call_cmd_ptr
.endm

.macro return
.byte 0xF
.endm

.macro setarg setargID setargValue
.byte 0x10
.byte \setargID
.hword \setargValue
.endm

.macro choosetwoturnanim choosetwoturnanim1 choosetwoturnanim2
.byte 0x11
.word \choosetwoturnanim1
.word \choosetwoturnanim2
.endm

.macro jumpifmoveturnEQ jumpifmoveturnEQturn jumpifmoveturnEQPTR
.byte 0x12
.byte \jumpifmoveturnEQturn
.word \jumpifmoveturnEQPTR
.endm

.macro goto goto_cmdPtr
.byte 0x13
.word \goto_cmdPtr
.endm

.macro loadBG1 loadBG1ID
.byte 0x14
.byte \loadBG1ID
.endm

.macro loaddefaultBG
.byte 0x15
.endm

.macro waitforBG
.byte 0x16
.endm

.macro waitfortransparentBG
.byte 0x17
.endm

.macro loadBG2 loadBG2ID
.byte 0x18
.byte \loadBG2ID
.endm

.macro playsound2 playsound2ID playsound2Unkown
.byte 0x19
.hword \playsound2ID
.byte \playsound2Unkown
.endm

.macro pancontrol anim1Aarg1
.byte 0x1A
.byte \anim1Aarg1
.endm

.macro playsoundpanchange anim1BsongID anim1BArg3 anim1BArg4 anim1BArg5 anim1BArg6
.byte 0x1B
.hword \anim1BsongID
.byte \anim1BArg3
.byte \anim1BArg4
.byte \anim1BArg5
.byte \anim1BArg6
.endm

.macro soundcomplex anim1Carg1 anim1Carg2 anim1Carg3 anim1Carg4
.byte 0x1C
.hword \anim1Carg1
.byte \anim1Carg2
.byte \anim1Carg3
.byte \anim1Carg4
.endm

.macro playsound3 anim1Darg1 anim1Darg2 anim1Darg3
.byte 0x1D
.hword \anim1Darg1
.byte \anim1Darg2
.byte \anim1Darg3
.endm

.macro set_BLDCNT set_BLDCNTvalue
.byte 0x1E
.hword \set_BLDCNTvalue
.endm

.macro launchsoundtask launchsoundtaskPtr launchsoundtaskArgsNo launchsoundtaskarg0 launchsoundtaskarg1 launchsoundtaskarg2 launchsoundtaskarg3 launchsoundtaskarg4 launchsoundtaskarg5 launchsoundtaskarg6 launchsoundtaskarg7
.byte 0x1F
.word \launchsoundtaskPtr
.byte \launchsoundtaskArgsNo
.hword \launchsoundtaskarg0
.hword \launchsoundtaskarg1
.hword \launchsoundtaskarg2
.hword \launchsoundtaskarg3
.hword \launchsoundtaskarg4
.hword \launchsoundtaskarg5
.hword \launchsoundtaskarg6
.hword \launchsoundtaskarg7
.endm

.macro waitforsound
.byte 0x20
.endm

.macro jumpifargmatches jumpifargmatchesargID jumpifargmatchesValue jumpifargmatchesPtr
.byte 0x21
.byte \jumpifargmatchesargID
.hword \jumpifargmatchesValue
.word \jumpifargmatchesPtr
.endm

.macro anim22 anim22bank
.byte 0x22
.byte \anim22bank
.endm

.macro anim23 anim23bank
.byte 0x23
.byte \anim23bank
.endm

.macro jumpifnotinbattle jumpifnotinbattlePTR
.byte 0x24
.word \jumpifnotinbattlePTR
.endm

.macro chooseBG chooseBG1 chooseBG2 chooseBG3
.byte 0x25
.byte \chooseBG1
.byte \chooseBG2
.byte \chooseBG3
.endm

.macro playsoundpanchange2 anim26H0 anim26B0 anim26B1 anim26B2 anim26B3
.byte 0x26
.hword \anim26H0
.byte \anim26B0
.byte \anim26B1
.byte \anim26B2
.byte \anim26B3
.endm

.macro playsoundpanchange3 anim27H0 anim27B0 anim27B1 anim27B2 anim27B3
.byte 0x27
.hword \anim27H0
.byte \anim27B0
.byte \anim27B1
.byte \anim27B2
.byte \anim27B3
.endm

.macro leftbankBG_over_partnerBG anim28Bank
.byte 0x28
.byte \anim28Bank
.endm

.macro bankBG_over_partnerBG
.byte 0x29
.endm

.macro leftopponentbankBG_over_partnerBG anim2Aarg
.byte 0x2A
.byte \anim2Aarg
.endm

.macro makebankinvisible makebankinvisibleBank
.byte 0x2B
.byte \makebankinvisibleBank
.endm

.macro makebankvisible makebankvisibleBank
.byte 0x2C
.byte \makebankvisibleBank
.endm

.macro stopmusic
.byte 0x2F
.endm

//objtemplate

.macro objtemplate objtemplatetiletag objtemplatepaltag objtemplateoam objtemplateimageanim objtemplategfx objtemplaterotscale objtemplatecallback
.hword \objtemplatetiletag
.hword \objtemplatepaltag
.word \objtemplateoam
.word \objtemplateimageanim
.word \objtemplategfx
.word \objtemplaterotscale
.word \objtemplatecallback
.endm

//supercommands

.macro unsetscrollingBG
loaddefaultBG
waitforBG
setarg 0x7 0xffff
waitfortransparentBG
.endm
