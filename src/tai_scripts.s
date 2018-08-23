.text
.thumb

.include "asm_defines.s"
.include "defines/tai_commands.s"

.equ POINTS_MINUS1, 0x082dc789
.equ POINTS_MINUS2, 0x082dc78c
.equ POINTS_MINUS3, 0x082dc78f
.equ POINTS_MINUS5, 0x082dc792
.equ POINTS_MINUS8, 0x082dc795
.equ POINTS_MINUS10, 0x082dc798
.equ POINTS_MINUS12, 0x082dc79b
.equ POINTS_MINUS30, 0x082dc79e
.equ POINTS_PLUS1, 0x082dc7a1
.equ POINTS_PLUS2, 0x082dc7a4
.equ POINTS_PLUS3, 0x082dc7a7
.equ POINTS_PLUS4, 0x082DD4D3 
.equ POINTS_PLUS5, 0x082dc7aa
.equ POINTS_PLUS10, 0x082dc7ad
.equ END_LOCATION, 0x082de34e

.equ SUPER_EFFECTIVE, 3
.equ NORMAL_EFFECTIVENESS, 2
.equ NOT_VERY_EFFECTIVE, 1
.equ NO_EFFECT, 0

.equ bank_target, 0x0
.equ bank_ai, 0x1
.equ bank_targetpartner, 0x2
.equ bank_aipartner, 0x3

.equ move_target_selected, 0
.equ move_target_depends, 1
.equ move_target_random, 4
.equ move_target_both, 8
.equ move_target_user, 0x10
.equ move_target_foes_and_ally, 0x20
.equ move_target_opponent_field, 0x40

.equ BANK_AFFECTING_HEALBLOCK, 0x0
.equ BANK_AFFECTING_EMBARGO, 0x1
.equ BANK_AFFECTING_GASTROACID, 0x2
.equ BANK_AFFECTING_MIRACLEEYE, 0x3
.equ BANK_AFFECTING_AQUARING, 0x4
.equ BANK_AFFECTING_MAGNETRISE, 0x5
.equ BANK_AFFECTING_TELEKINESIS, 0x6
.equ BANK_AFFECTING_LASERFOCUS, 0x7

.equ SIDE_AFFECTING_TAILWIND, 0x0
.equ SIDE_AFFECTING_LUCKYCHANT, 0x1
.equ SIDE_AFFECTING_AURORAVEIL, 0x2

.equ FIELD_AFFECTING_GRAVITY, 0x0
.equ FIELD_AFFECTING_TRICKROOM, 0x1
.equ FIELD_AFFECTING_WONDERROOM, 0x2
.equ FIELD_AFFECTING_MAGICROOM, 0x3
.equ FIELD_AFFECTING_TERRAINS, 0x4 @Read from Move ID

TAI_SCRIPT_0: @don't act stupid; bitfield 0x1
	jumpiftargetisally END_LOCATION
	getmovetarget
	jumpifbytevarEQ move_target_selected DISCOURAGE_NOTAFFECTED
	jumpifdoublebattle DISCOURAGE_MOVESBASEDONABILITIES
	getmovetarget
	jumpifbytevarEQ move_target_both DISCOURAGE_NOTAFFECTED
	jumpifbytevarNE move_target_foes_and_ally DISCOURAGE_MOVESBASEDONABILITIES
DISCOURAGE_NOTAFFECTED:
	jumpifeffectiveness_EQ NO_EFFECT POINTS_MINUS10
DISCOURAGE_MOVESBASEDONABILITIES:
	discourage_moves_based_on_abilities
	isoftype bank_target TYPE_GRASS
	jumpifbytevarNE 1 DISCOURAGE_MOVES_ON_SUBSTITUTE
DISCOURAGE_POWDER_ON_GRASS:
	getmoveid
	jumpifhwordvarinlist powder_moves POINTS_MINUS10
DISCOURAGE_MOVES_ON_SUBSTITUTE:
	jumpifnostatus2 bank_target STATUS2_SUBSTITUTE DISCOURAGE_MOVES_ON_SEMIINVULNERABLE
	affected_by_substitute
	jumpifbytevarNE 1 DISCOURAGE_MOVES_ON_SEMIINVULNERABLE
	getmovepower
	jumpifbytevarEQ 0 POINTS_MINUS10
DISCOURAGE_MOVES_ON_SEMIINVULNERABLE:
	isinsemiinvulnerablestate bank_target
	jumpifbytevarEQ 0 DISCOURAGE_STUPIDMOVEEFFECTS
	getmovetarget
	jumpifbytevarEQ move_target_user DISCOURAGE_STUPIDMOVEEFFECTS
	jumpifstrikessecond bank_ai bank_target DISCOURAGE_STUPIDMOVEEFFECTS @ai hits after poke is no longer in the semiinvlnerable state
	getmoveid
	movehitssemiinvulnerable bank_target 0xFFFF
	jumpifbytevarEQ 0x1 DISCOURAGE_STUPIDMOVEEFFECTS
	goto_cmd POINTS_MINUS10
DISCOURAGE_STUPIDMOVEEFFECTS:
	jumpifmovescriptEQ 1 DISCOURAGE_THAT_MAY_FAIL	@Endeavour
	jumpifmovescriptEQ 2 DISCOURAGE_ONESTATUSER
	jumpifmovescriptEQ 3 DISCOURAGE_ONESTATTARGET
	jumpifmovescriptEQ 6 DISCOURAGE_MULTIPLESTATSCHANGE
	jumpifmovescriptEQ 7 DISCOURAGE_MULTIPLESTATSCHANGE
	jumpifmovescriptEQ 9 DISCOURAGE_CONFUSION
	jumpifmovescriptEQ 12 DISCOURAGE_SLEEP
	jumpifmovescriptEQ 13 DISCOURAGE_POISON
	jumpifmovescriptEQ 14 DISCOURAGE_POISON
	jumpifmovescriptEQ 15 DISCOURAGE_PARALYSIS
	jumpifmovescriptEQ 16 DISCOURAGE_BURNING
	jumpifmovescriptEQ 21 DISCOURAGE_SUICIDE
	jumpifmovescriptEQ 22 DISCOURAGE_SUICIDE
	jumpifmovescriptEQ 23 DISCOURAGE_EXPLOSION
	jumpifmovescriptEQ 24 DISCOURAGE_HEALBLOCK_AI @Draining Moves
	jumpifmovescriptEQ 25 DISCOURAGE_HPUSERHEAL
	jumpifmovescriptEQ 26 POINTS_MINUS8 @target healing
	jumpifmovescriptEQ 27 DISCOURAGE_CHARGE
	jumpifmovescriptEQ 28 DISCOURAGE_PSYCHOSHIFT
	jumpifmovescriptEQ 29 DISCOURAGE_HPUSERHEAL @Roost
	jumpifmovescriptEQ 30 DISCOURAGE_GRAVITY
	jumpifmovescriptEQ 31 DISCOURAGE_IDENTYFING
	jumpifmovescriptEQ 34 DISCOURAGE_PROTECT
	jumpifmovescriptEQ 37 DISCOURAGE_ATTRACT
	jumpifmovescriptEQ 38 DISCOURAGE_CAPTIVATE
	jumpifmovescriptEQ 41 DISCOURAGE_THIRDTYPEADD
	jumpifmovescriptEQ 42 DISCOURAGE_ABILITYCHANGE
	jumpifmovescriptEQ 43 DISCOURAGE_ROOMS
	jumpifmovescriptEQ 45 DISCOURAGE_GASTROACID
	jumpifmovescriptEQ 46 DISCOURAGE_EMBARGO
	jumpifmovescriptEQ 47 DISCOURAGE_NATURALGIFT
	jumpifmovescriptEQ 48 POINTS_MINUS10 @After You
	jumpifmovescriptEQ 50 POINTS_MINUS10 @Aromatic Mist ;target is not bank at this point
	jumpifmovescriptEQ 53 DISCOURAGE_ENTRYHAZARDS
	jumpifmovescriptEQ 54 DISCOURAGE_IFNOALLY @Follow Me/Rage Powder
	jumpifmovescriptEQ 55 DISCOURAGE_SYNCHRONOISE
	jumpifmovescriptEQ 56 DISCOURAGE_ONESTATUSER @Autonomize
	jumpifmovescriptEQ 60 DISCOURAGE_FOCUSENERGY
	jumpifmovescriptEQ 61 DISCOURAGE_TAUNT
	jumpifmovescriptEQ 62 DISCOURAGE_TORMENT
	jumpifmovescriptEQ 63 DISCOURAGE_HEALBLOCK
	jumpifmovescriptEQ 64 DISCOURAGE_MEANLOOK
	jumpifmovescriptEQ 65 DISCOURAGE_PERISHSONG
	jumpifmovescriptEQ 70 DISCOURAGE_ONEHITKO
	jumpifmovescriptEQ 72 DISCOURAGE_ROAR
	jumpifmovescriptEQ 73 DISCOURAGE_IFNOALLY @Ally Switch
	jumpifmovescriptEQ 75 DISCOURAGE_DISABLE
	jumpifmovescriptEQ 76 DISCOURAGE_ENCORE
	jumpifmovescriptEQ 77 DISCOURAGE_MIST
	jumpifmovescriptEQ 78 DISCOURAGE_LEECHSEED
	jumpifmovescriptEQ 80 POINTS_MINUS8		@Teleport
	jumpifmovescriptEQ 81 DISCOURAGE_IFNOLASTMOVE @Mimic
	jumpifmovescriptEQ 82 DISCOURAGE_ONESTATUSER @Minimize
	jumpifmovescriptEQ 83 DISCOURAGE_ONESTATUSER @Defense Curl
	jumpifmovescriptEQ 84 DISCOURAGE_REFLECT
	jumpifmovescriptEQ 85 DISCOURAGE_LIGHTSCREEN
	jumpifmovescriptEQ 86 DISCOURAGE_HAZE
	jumpifmovescriptEQ 88 DISCOURAGE_IFNOLASTMOVE @Mirror Move
	jumpifmovescriptEQ 89 DISCOURAGE_IFNOTASLEEP @Dream Eater
	jumpifmovescriptEQ 90 DISCOURAGE_NIGHTMARE
	jumpifmovescriptEQ 91 DISCOURAGE_TRANSFORM
	jumpifmovescriptEQ 92 POINTS_MINUS8 @Useless Moves like Splash
	jumpifmovescriptEQ 93 DISCOURAGE_HPUSERHEAL @ Rest
	jumpifmovescriptEQ 96 DISCOURAGE_SUBSTITUTE
	jumpifmovescriptEQ 100 DISCOURAGE_LOCKON
	jumpifmovescriptEQ 101 DISCOURAGE_IFNOLASTMOVE @Spite
	jumpifmovescriptEQ 102 DISCOURAGE_BERRYDRUM
	jumpifmovescriptEQ 104 DISCOURAGE_CURSE
	jumpifmovescriptEQ 107 DISCOURAGE_IFNOSLEEPUSER @Sleep Talk
	jumpifmovescriptEQ 108 DISCOURAGE_HEALBELL
	jumpifmovescriptEQ 110 DISCOURAGE_SAFEGUARD
	jumpifmovescriptEQ 111 DISCOURAGE_PAINSPLIT
	jumpifmovescriptEQ 114 DISCOURAGE_PSYCHUP
	jumpifmovescriptEQ 115 DISCOURAGE_FUTURESIGHT
	jumpifmovescriptEQ 118 DISCOURAGE_STOCKPILESTUFF
	jumpifmovescriptEQ 122 DISCOURAGE_IFNOALLY @Helping Hand
	jumpifmovescriptEQ 123 DISCOURAGE_TRICK
	jumpifmovescriptEQ 126 DISCOURAGE_INGRAIN
	jumpifmovescriptEQ 127 DISCOURAGE_BATONPASS
	jumpifmovescriptEQ 128 DISCOURAGE_RECYCLE
	jumpifmovescriptEQ 129 DISCOURAGE_IFNOSLEEPUSER @Snore
	jumpifmovescriptEQ 131 DISCOURAGE_YAWN
	jumpifmovescriptEQ 133 DISCOURAGE_IMPRISION
	jumpifmovescriptEQ 134 DISCOURAGE_REFRESH
	jumpifmovescriptEQ 135 DISCOURAGE_GRUDGE
	jumpifmovescriptEQ 138 DISCOURAGE_SPORTS
	jumpifmovescriptEQ 140 DISCOURAGE_TAILWIND
	jumpifmovescriptEQ 142 DISCOURAGE_FLING
	jumpifmovescriptEQ 144 DISCOURAGE_LUCKYCHANT
	jumpifmovescriptEQ 148 DISCOURAGE_AQUARING
	jumpifmovescriptEQ 149 DISCOURAGE_MAGNETRISE
	jumpifmovescriptEQ 151 DISCOURAGE_TERRAINS
	jumpifmovescriptEQ 153 DISCOURAGE_TELEKINESIS
	jumpifmovescriptEQ 155 DISCOURAGE_SOAK
	jumpifmovescriptEQ 156 DISCOURAGE_SHELLSMASH
	jumpifmovescriptEQ 158 DISCOURAGE_SHIFTGEAR
	jumpifmovescriptEQ 159 DISCOURAGE_QUASH
	jumpifmovescriptEQ 160 DISCOURAGE_FAKEOUT
	jumpifmovescriptEQ 161 DISCOURAGE_SANDSTORM
	jumpifmovescriptEQ 162 DISCOURAGE_RAINDANCE
	jumpifmovescriptEQ 163 DISCOURAGE_SUNNYDAY
	jumpifmovescriptEQ 164 DISCOURAGE_HAIL
	jumpifmovescriptEQ 165 DISCOURAGE_THAT_MAY_FAIL @Magnetic Flux
	jumpifmovescriptEQ 166 DISCOURAGE_VENOMDRENCH
	jumpifmovescriptEQ 168 DISCOURAGE_THAT_MAY_FAIL @Last Resort
	jumpifmovescriptEQ 172 POINTS_MINUS8 @Happy Hour
	jumpifmovescriptEQ 173 DISCOURAGE_FAIRYLOCK
	jumpifmovescriptEQ 174 DISCOURAGE_THAT_MAY_FAIL @Belch
	jumpifmovescriptEQ 182 DISCOURAGE_LASERFOCUS @Laser Focus
	jumpifmovescriptEQ 183 DISCOURAGE_AURORAVEIL @Aurora Veil
	goto_cmd END_LOCATION
DISCOURAGE_AURORAVEIL:
	jumpifnewsideaffecting bank_ai SIDE_AFFECTING_AURORAVEIL POINTS_MINUS10
	jumpifweather weather_hail | weather_permament_hail END_LOCATION
	scoreupdate -10
DISCOURAGE_LASERFOCUS:
	jumpifbankaffecting bank_ai BANK_AFFECTING_LASERFOCUS POINTS_MINUS10
	return_cmd
DISCOURAGE_SHIFTGEAR:
	jumpifstatbuffNE bank_ai STAT_ATK 0xC END_LOCATION
	jumpifstatbuffEQ bank_ai STAT_SPD 0xC POINTS_MINUS10
	return_cmd
DISCOURAGE_SHELLSMASH:
	jumpifability bank_ai 1 ABILITY_CONTRARY DISCOURAGE_SHELLSMASH_CONTRARY
	jumpifstatbuffNE bank_ai STAT_ATK 0xC END_LOCATION
	jumpifstatbuffNE bank_ai STAT_SP_ATK 0xC END_LOCATION
	jumpifstatbuffEQ bank_ai STAT_SPD 0xC POINTS_MINUS10
	return_cmd
DISCOURAGE_SHELLSMASH_CONTRARY:
	jumpifstatbuffNE bank_ai STAT_DEF 0xC END_LOCATION
	jumpifstatbuffEQ bank_ai STAT_SP_DEF 0xC POINTS_MINUS10
	return_cmd
DISCOURAGE_MULTIPLESTATSCHANGE:
	canmultiplestatwork
	jumpifbytevarEQ 0x0 POINTS_MINUS10
	return_cmd
DISCOURAGE_THAT_MAY_FAIL:
	jumpifcantusemove POINTS_MINUS10
	return_cmd
DISCOURAGE_PERISHSONG:
	jumpifstatus3 bank_target STATUS3_PERISHSONG POINTS_MINUS10
	return_cmd
DISCOURAGE_HAIL:
	jumpifweather weather_permament_hail | weather_hail | weather_harsh_sun | weather_heavy_rain | weather_air_current POINTS_MINUS10
	return_cmd
DISCOURAGE_SUNNYDAY:
	jumpifweather weather_permament_sun | weather_sun | weather_harsh_sun | weather_heavy_rain | weather_air_current POINTS_MINUS10
	return_cmd
DISCOURAGE_RAINDANCE:
	jumpifweather weather_permament_rain | weather_rain | weather_downpour | weather_harsh_sun | weather_heavy_rain | weather_air_current POINTS_MINUS10
	return_cmd
DISCOURAGE_SANDSTORM:
	jumpifweather weather_permament_sandstorm | weather_sandstorm | weather_harsh_sun | weather_heavy_rain | weather_air_current POINTS_MINUS10
	return_cmd
DISCOURAGE_FAIRYLOCK:
	jumpifnotdoublebattle DISCOURAGE_MEANLOOK
	return_cmd
DISCOURAGE_VENOMDRENCH:
	jumpifnostatus bank_target STATUS_BAD_POISON | STATUS_POISON POINTS_MINUS10
	goto_cmd DISCOURAGE_MULTIPLESTATSCHANGE
DISCOURAGE_FAKEOUT:
	jumpifnofirstturnfor bank_ai POINTS_MINUS8
	return_cmd
DISCOURAGE_QUASH:
	jumpifnotdoublebattle POINTS_MINUS10
	return_cmd
DISCOURAGE_SOAK:
	jumpifnotmove MOVE_SOAK END_LOCATION
	isoftype bank_target TYPE_WATER
	jumpifbytevarEQ 0x1 POINTS_MINUS10
	return_cmd
DISCOURAGE_TELEKINESIS:
	jumpifbankaffecting bank_target BANK_AFFECTING_TELEKINESIS POINTS_MINUS10
	return_cmd
DISCOURAGE_TERRAINS:
	jumpiffieldaffecting FIELD_AFFECTING_TERRAINS POINTS_MINUS10
	return_cmd
DISCOURAGE_MAGNETRISE:
	jumpifbankaffecting bank_ai BANK_AFFECTING_MAGNETRISE POINTS_MINUS10
	jumpifbankaffecting bank_ai BANK_AFFECTING_TELEKINESIS POINTS_MINUS10
	jumpifability bank_ai ABILITY_LEVITATE 1 POINTS_MINUS10
	return_cmd
DISCOURAGE_AQUARING:
	jumpifbankaffecting bank_ai BANK_AFFECTING_AQUARING POINTS_MINUS10
	return_cmd
DISCOURAGE_LUCKYCHANT:
	jumpifnewsideaffecting bank_ai SIDE_AFFECTING_LUCKYCHANT POINTS_MINUS10
	return_cmd
DISCOURAGE_FLING:
	jumpifitem bank_ai 0x0 POINTS_MINUS10
	return_cmd
DISCOURAGE_TAILWIND:
	jumpifnewsideaffecting bank_ai SIDE_AFFECTING_TAILWIND POINTS_MINUS10
	return_cmd
DISCOURAGE_SPORTS:
	discouragesports
	return_cmd
DISCOURAGE_GRUDGE:
	countalivepokes bank_ai
	jumpifbytevarEQ 0x0 POINTS_MINUS10
	return_cmd
DISCOURAGE_REFRESH:
	jumpifnostatus bank_ai STATUS_BURN | STATUS_PARALYSIS | STATUS_BAD_POISON | STATUS_POISON POINTS_MINUS10
	return_cmd
DISCOURAGE_IMPRISION:
	jumpifstatus3 bank_target STATUS3_IMPRISONED POINTS_MINUS10
	return_cmd
DISCOURAGE_YAWN:
	jumpifstatus2 bank_target STATUS3_YAWN POINTS_MINUS10
	goto_cmd DISCOURAGE_SLEEP
DISCOURAGE_RECYCLE:
	getusedhelditem bank_ai
	jumpifbytevarEQ 0x0 POINTS_MINUS10
	jumpifitem bank_ai 0x0 END_LOCATION
	scoreupdate -10
	return_cmd
DISCOURAGE_BATONPASS:
	countalivepokes bank_ai
	jumpifbytevarEQ 0x0 POINTS_MINUS10
	jumpifstatbuffGE bank_ai 0x1 0x6 END_LOCATION
	jumpifstatbuffGE bank_ai 0x2 0x6 END_LOCATION
	jumpifstatbuffGE bank_ai 0x3 0x6 END_LOCATION
	jumpifstatbuffGE bank_ai 0x4 0x6 END_LOCATION
	jumpifstatbuffGE bank_ai 0x5 0x6 END_LOCATION
	jumpifstatbuffGE bank_ai 0x6 0x6 END_LOCATION
	jumpifstatbuffGE bank_ai 0x7 0x6 END_LOCATION
	scoreupdate -10
	return_cmd
DISCOURAGE_INGRAIN:
	jumpifstatus3 bank_ai STATUS3_ROOTED POINTS_MINUS10
	goto_cmd DISCOURAGE_HEALBLOCK_AI
DISCOURAGE_TRICK:
	getitemeffect bank_target 0x0
	jumpifbytevarNE 0x0 END_LOCATION
	jumpifitem bank_ai 0x0 POINTS_MINUS10
	return_cmd
DISCOURAGE_STOCKPILESTUFF:
	jumpifmove MOVE_STOCKPILE DISCOURAGE_STOCKPILE
	jumpifmove MOVE_SWALLOW DISCOURAGE_SWALLOW
	jumpifmove MOVE_SPIT_UP DISCOURAGE_IFUSERNOSTOCKPILE
	return_cmd
DISCOURAGE_STOCKPILE:
	getstockpileuses bank_ai
	jumpifbytevarGE 2 POINTS_MINUS10
	return_cmd
DISCOURAGE_SWALLOW:
	call_cmd DISCOURAGE_HPUSERHEAL
DISCOURAGE_IFUSERNOSTOCKPILE:
	getstockpileuses bank_ai
	jumpifbytevarEQ 0x0 POINTS_MINUS10
	return_cmd
DISCOURAGE_FUTURESIGHT:
	jumpifsideaffecting bank_target SIDE_FUTUREATTACK POINTS_MINUS10
	return_cmd
DISCOURAGE_PSYCHUP:
	jumpifsamestatboosts bank_ai bank_target POINTS_MINUS10
	jumpifstatbuffGE bank_target 0x1 0x6 END_LOCATION
	jumpifstatbuffGE bank_target 0x2 0x6 END_LOCATION
	jumpifstatbuffGE bank_target 0x3 0x6 END_LOCATION
	jumpifstatbuffGE bank_target 0x4 0x6 END_LOCATION
	jumpifstatbuffGE bank_target 0x5 0x6 END_LOCATION
	jumpifstatbuffGE bank_target 0x6 0x6 END_LOCATION
	jumpifstatbuffGE bank_target 0x7 0x6 END_LOCATION
	jumpifstatbuffLT bank_ai 0x1 0x6 END_LOCATION
	jumpifstatbuffLT bank_ai 0x2 0x6 END_LOCATION
	jumpifstatbuffLT bank_ai 0x3 0x6 END_LOCATION
	jumpifstatbuffLT bank_ai 0x4 0x6 END_LOCATION
	jumpifstatbuffLT bank_ai 0x5 0x6 END_LOCATION
	jumpifstatbuffLT bank_ai 0x6 0x6 END_LOCATION
	jumpifstatbuffLT bank_ai 0x7 0x6 END_LOCATION
	scoreupdate -10
	return_cmd
DISCOURAGE_PAINSPLIT:
	jumpifhealthGE 86 bank_ai POINTS_MINUS10
	jumpifhealthLT 16 bank_target POINTS_MINUS10
	return_cmd
DISCOURAGE_SAFEGUARD:
	jumpifsideaffecting bank_ai SIDE_SAFEGUARD POINTS_MINUS10
	return_cmd
DISCOURAGE_HEALBELL:
	jumpifanypartymemberhasstatus bank_ai 0xFFFF END_LOCATION
	scoreupdate -10
	return_cmd
DISCOURAGE_IFNOSLEEPUSER:
	jumpifnostatus bank_ai STATUS_SLEEP POINTS_MINUS10
	return_cmd
DISCOURAGE_CURSE:
	isoftype bank_ai TYPE_GHOST
	jumpifbytevarEQ 0x1 DISCOURAGE_GHOSTCURSE
	jumpifability bank_ai ABILITY_CONTRARY 1 DISCOURAGE_CONTRARYCURSE
	jumpifstatbuffNE bank_ai STAT_ATK 0xC END_LOCATION
	jumpifstatbuffEQ bank_ai STAT_DEF 0xC POINTS_MINUS10
	return_cmd
DISCOURAGE_CONTRARYCURSE:
	jumpifstatbuffEQ bank_ai STAT_SPD 0xC POINTS_MINUS10
	return_cmd
DISCOURAGE_GHOSTCURSE:
	jumpifstatus2 bank_target STATUS2_CURSED POINTS_MINUS10
	jumpifhealthLT bank_ai 50 POINTS_MINUS10
	return_cmd
DISCOURAGE_BERRYDRUM:
	jumpifhealthLT bank_ai 50 POINTS_MINUS10
	jumpifstatbuffEQ bank_ai 0x1 0xC POINTS_MINUS10
	return_cmd
DISCOURAGE_LOCKON:
	islockon_on bank_ai bank_target
	jumpifbytevarEQ 0x1 POINTS_MINUS10
	jumpifability bank_ai ABILITY_NO_GUARD 1 POINTS_MINUS10
	jumpifability bank_target ABILITY_NO_GUARD 1 POINTS_MINUS10
	return_cmd
DISCOURAGE_SUBSTITUTE:
	jumpifstatus2 bank_ai STATUS2_SUBSTITUTE POINTS_MINUS10
	jumpifhealthLT bank_ai 26 POINTS_MINUS10
	jumpifability bank_target 1 ABILITY_INFILTRATOR POINTS_MINUS8
	return_cmd
DISCOURAGE_TRANSFORM:
	jumpifstatus bank_ai STATUS2_TRANSFORMED POINTS_MINUS10
	jumpifstatus bank_target STATUS2_TRANSFORMED | STATUS2_SUBSTITUTE POINTS_MINUS10
	return_cmd
DISCOURAGE_NIGHTMARE:
	jumpifstatus2 bank_target STATUS2_NIGHTMARE POINTS_MINUS10
DISCOURAGE_IFNOTASLEEP:
	jumpifnostatus bank_target STATUS_SLEEP POINTS_MINUS10
	return_cmd
DISCOURAGE_HAZE:
	jumpifstatbuffLT bank_target 0x1 0x5 POINTS_MINUS10
	jumpifstatbuffLT bank_target 0x2 0x5 POINTS_MINUS10
	jumpifstatbuffLT bank_target 0x3 0x5 POINTS_MINUS10
	jumpifstatbuffLT bank_target 0x4 0x5 POINTS_MINUS10
	jumpifstatbuffLT bank_target 0x5 0x5 POINTS_MINUS10
	jumpifstatbuffLT bank_target 0x6 0x5 POINTS_MINUS10
	jumpifstatbuffLT bank_target 0x7 0x5 POINTS_MINUS10
	jumpifstatbuffGE bank_ai 0x1 0x7 POINTS_MINUS10
	jumpifstatbuffGE bank_ai 0x2 0x7 POINTS_MINUS10
	jumpifstatbuffGE bank_ai 0x3 0x7 POINTS_MINUS10
	jumpifstatbuffGE bank_ai 0x4 0x7 POINTS_MINUS10
	jumpifstatbuffGE bank_ai 0x5 0x7 POINTS_MINUS10
	jumpifstatbuffGE bank_ai 0x6 0x7 POINTS_MINUS10
	jumpifstatbuffGE bank_ai 0x7 0x7 POINTS_MINUS10
	return_cmd
DISCOURAGE_LIGHTSCREEN:
	jumpifsideaffecting bank_ai SIDE_LIGHTSCREEN POINTS_MINUS10
	return_cmd
DISCOURAGE_REFLECT:
	jumpifsideaffecting bank_ai SIDE_REFLECT POINTS_MINUS10
	return_cmd
DISCOURAGE_LEECHSEED:
	isoftype bank_target TYPE_GRASS
	jumpifbytevarEQ 0x1 POINTS_MINUS10
	jumpifstatus3 bank_target STATUS3_SEEDED POINTS_MINUS10
	checkability bank_target ABILITY_LIQUID_OOZE 1
	jumpifbytevarEQ 0x1 POINTS_MINUS10
	return_cmd
DISCOURAGE_MIST:
	jumpifsideaffecting bank_ai SIDE_MIST POINTS_MINUS10
	return_cmd
DISCOURAGE_ENCORE:
	jumpifanymovedisabled_or_encored bank_target 0x1 POINTS_MINUS10
	goto_cmd DISCOURAGE_IFNOLASTMOVE
DISCOURAGE_DISABLE:
	jumpifanymovedisabled_or_encored bank_target 0x0 POINTS_MINUS10
DISCOURAGE_IFNOLASTMOVE:
	getlastusedmove bank_target
	jumpifwordvarEQ 0x0 POINTS_MINUS10
	jumpifwordvarEQ 0xFFFF POINTS_MINUS10
	return_cmd
DISCOURAGE_IFNOALLY:
	isbankpresent bank_aipartner
	jumpifbytevarEQ 0x0 POINTS_MINUS10
	return_cmd
DISCOURAGE_ROAR:
	countalivepokes bank_target
	jumpifbytevarEQ 0x0 POINTS_MINUS10
	checkability bank_target ABILITY_SUCTION_CUPS 1
	jumpifbytevarEQ 0x1 POINTS_MINUS10
	return_cmd
DISCOURAGE_ONEHITKO:
	jumpifleveldifference lvai_lower POINTS_MINUS10
	getability bank_target 1
	jumpifbytevarEQ ABILITY_STURDY POINTS_MINUS10
	return_cmd
DISCOURAGE_MEANLOOK:
	getitemeffect bank_target 1
	jumpifbytevarEQ ITEM_EFFECT_SHEDSHELL POINTS_MINUS10
	jumpifstatus2 bank_target STATUS2_TRAPPED | STATUS2_WRAPPED POINTS_MINUS10
	return_cmd
DISCOURAGE_HEALBLOCK:
	jumpifbankaffecting bank_target BANK_AFFECTING_HEALBLOCK POINTS_MINUS10
	return_cmd
DISCOURAGE_TORMENT:
	jumpifstatus2 bank_target STATUS2_TORMENTED POINTS_MINUS10
	return_cmd
DISCOURAGE_TAUNT:
	jumpiftargettaunted POINTS_MINUS10
	return_cmd
DISCOURAGE_FOCUSENERGY:
	jumpifstatus2 bank_ai STATUS2_PUMPEDUP POINTS_MINUS10
	return_cmd
DISCOURAGE_SYNCHRONOISE:
	sharetype bank_ai bank_target
	jumpifbytevarEQ 0x0 POINTS_MINUS10
	return_cmd
DISCOURAGE_IFNOTDOUBLE:
	jumpifnotdoublebattle POINTS_MINUS8
	return_cmd
DISCOURAGE_ENTRYHAZARDS:
	countalivepokes bank_target
	jumpifbytevarEQ 0 POINTS_MINUS10
	discouragehazards
	return_cmd
DISCOURAGE_NATURALGIFT:
	getitempocket bank_ai
	jumpifbytevarNE 4 POINTS_MINUS10
	call_cmd DISCOURAGE_WONDERROOM
	jumpifbankaffecting bank_ai BANK_AFFECTING_EMBARGO POINTS_MINUS8
	return_cmd
DISCOURAGE_EMBARGO:
	jumpifbankaffecting bank_target BANK_AFFECTING_EMBARGO POINTS_MINUS10
	call_cmd DISCOURAGE_MAGICROOM
	getability bank_target 1
	jumpifbytevarEQ ABILITY_KLUTZ POINTS_MINUS8
	return_cmd
DISCOURAGE_GASTROACID:
	jumpifbankaffecting bank_target BANK_AFFECTING_GASTROACID POINTS_MINUS10
	getability bank_target 0
	jumpifbytevarEQ ABILITY_STANCE_CHANGE POINTS_MINUS8
	jumpifbytevarEQ ABILITY_MULTITYPE POINTS_MINUS8
	return_cmd
DISCOURAGE_ROOMS:
	jumpifmove MOVE_TRICK_ROOM DISCOURAGE_TRICKROOM
	jumpifmove MOVE_WONDER_ROOM DISCOURAGE_WONDERROOM
	jumpifmove MOVE_MAGIC_ROOM DISCOURAGE_MAGICROOM
	return_cmd
DISCOURAGE_TRICKROOM:
	jumpiffieldaffecting FIELD_AFFECTING_TRICKROOM POINTS_MINUS10
	return_cmd
DISCOURAGE_WONDERROOM:
	jumpiffieldaffecting FIELD_AFFECTING_WONDERROOM POINTS_MINUS10
	return_cmd
DISCOURAGE_MAGICROOM:
	jumpiffieldaffecting FIELD_AFFECTING_MAGICROOM POINTS_MINUS10
	return_cmd
DISCOURAGE_ABILITYCHANGE:
	canchangeability bank_ai bank_target
	jumpifbytevarEQ 0x0 POINTS_MINUS10
	return_cmd
DISCOURAGE_ONESTATUSER:
	isstatchangepositive
	jumpifbytevarEQ 0x0 POINTS_MINUS10
	getstatvaluemovechanges bank_ai
	jumpifbytevarEQ 0xC POINTS_MINUS10
	return_cmd
DISCOURAGE_ONESTATTARGET:
	isstatchangepositive
	jumpifbytevarEQ 0x1 POINTS_MINUS10
	getstatvaluemovechanges bank_target
	jumpifbytevarEQ 0x0 POINTS_MINUS10
	return_cmd
DISCOURAGE_CONFUSION:
	jumpifstatus2 bank_target STATUS2_CONFUSION POINTS_MINUS10
	getability bank_target 1
	jumpifbytevarEQ ABILITY_OWN_TEMPO POINTS_MINUS10
	return_cmd
DISCOURAGE_SLEEP:
	getability bank_target 1
	jumpifbytevarEQ ABILITY_INSOMNIA POINTS_MINUS10
	jumpifbytevarEQ ABILITY_VITAL_SPIRIT POINTS_MINUS10
	jumpifstatus2 bank_target STATUS2_UPROAR POINTS_MINUS10
	goto_cmd DISCOURAGE_IF_CANTBESTATUSED
DISCOURAGE_POISON:
	getability bank_target 1
	jumpifbytevarEQ ABILITY_IMMUNITY POINTS_MINUS10
	goto_cmd DISCOURAGE_IF_CANTBESTATUSED
DISCOURAGE_PARALYSIS:
	isoftype bank_target TYPE_ELECTRIC
	jumpifbytevarEQ 0x1 POINTS_MINUS10
	goto_cmd DISCOURAGE_IF_CANTBESTATUSED
DISCOURAGE_BURNING:
	isoftype bank_target TYPE_FIRE
	jumpifbytevarEQ 0x1 POINTS_MINUS10
	getability bank_target 1
	jumpifbytevarEQ ABILITY_WATER_VEIL POINTS_MINUS10
DISCOURAGE_IF_CANTBESTATUSED:
	jumpifstatus bank_target 0xFFFF POINTS_MINUS10
	jumpifsideaffecting bank_target SIDE_SAFEGUARD POINTS_MINUS10
	return_cmd
DISCOURAGE_EXPLOSION:
	jumpiffatal END_LOCATION
DISCOURAGE_SUICIDE:
	countalivepokes bank_ai
	jumpifbytevarEQ 0 POINTS_MINUS10
	return_cmd
DISCOURAGE_HEALBLOCK_AI:
	jumpifbankaffecting bank_ai BANK_AFFECTING_HEALBLOCK POINTS_MINUS10
	return_cmd
DISCOURAGE_HPUSERHEAL:
	jumpifhealthGE bank_ai 95 POINTS_MINUS12
	goto_cmd DISCOURAGE_HEALBLOCK_AI
DISCOURAGE_CHARGE:
	jumpifstatus3 bank_ai STATUS3_CHARGED DISCOURAGE_ONESTATUSER
	return_cmd
DISCOURAGE_PSYCHOSHIFT:
	jumpifnostatus bank_ai 0xFFFF POINTS_MINUS10
	jumpifstatus bank_target 0xFFFF POINTS_MINUS10
	return_cmd
DISCOURAGE_GRAVITY:
	jumpiffieldaffecting FIELD_AFFECTING_GRAVITY POINTS_MINUS10
	return_cmd
DISCOURAGE_IDENTYFING:
	jumpifstatus2 bank_target STATUS2_IDENTIFIED POINTS_MINUS8
	jumpifbankaffecting bank_target BANK_AFFECTING_MIRACLEEYE POINTS_MINUS8
	return_cmd
DISCOURAGE_PROTECT:
	jumpifstatus2 bank_target STATUS2_RECHARGE POINTS_MINUS10
	getprotectuses bank_ai
	jumpifbytevarGE 2 POINTS_MINUS5
	return_cmd
DISCOURAGE_ATTRACT:
	isbankinlovewith bank_target bank_ai
	jumpifbytevarEQ 1 POINTS_MINUS10
DISCOURAGE_UNLESS_OPPOSITEGENDERS:
	getgender bank_ai
	jumpifbytevarEQ 0xFF POINTS_MINUS10
	vartovar2
	getgender bank_target
	jumpifbytevarEQ 0xFF POINTS_MINUS10
	jumpifvarsEQ POINTS_MINUS10
	return_cmd
DISCOURAGE_CAPTIVATE:
	call_cmd DISCOURAGE_UNLESS_OPPOSITEGENDERS
	goto_cmd DISCOURAGE_ONESTATTARGET
DISCOURAGE_THIRDTYPEADD:
	jumpifcantaddthirdtype bank_target END_LOCATION
	goto_cmd POINTS_MINUS10
	
TAI_SCRIPT_2: @ENCOURAGE a fatal move; bitfield 0x4
	jumpiftargetisally END_LOCATION
	jumpifattackerhasnodamagingmoves END_LOCATION
	jumpiffatal ENCOURAGE_FATAL
	jumpifmostpowerful MOST_POWERFUL_MOVE
	return_cmd
ENCOURAGE_FATAL:
	jumpifmovescriptEQ 23 END_LOCATION @Explosion
	jumpifstrikesfirst bank_ai bank_target POINTS_PLUS4
	scoreupdate 2
	return_cmd
MOST_POWERFUL_MOVE:
	jumpifhasnostatusmoves bank_ai POINTS_PLUS3
	jumpifstatusmovesnotworthusing bank_ai POINTS_PLUS3
	getbestdamagelefthp bank_ai bank_target
	jumpifbytevarLT 11 POINTS_PLUS2
	jumpifbytevarLT 31 POINTS_PLUS1
	jumpifbytevarGE 61 END_LOCATION
	jumpifrandGE 0x50 POINTS_PLUS1
	return_cmd
	
IS_TARGET_UNABLETOESCAPE:
	getitemeffect bank_target 1
	jumpifbytevarEQ 1 AI_VAR_RETURN_0
	jumpifstatus2 bank_target STATUS2_WRAPPED | STATUS2_TRAPPED AI_VAR_RETURN_1
	abilitypreventsescape bank_ai bank_target
	return_cmd
IS_AI_UNABLETOESCAPE:	
	jumpifstatus2 bank_ai STATUS2_WRAPPED | STATUS2_TRAPPED AI_VAR_RETURN_1
	abilitypreventsescape bank_target bank_ai
	return_cmd
AI_VAR_RETURN_0:
	setbytevar 0x0
	return_cmd
AI_VAR_RETURN_1:
	setbytevar 0x1
	return_cmd
	
TAI_SCRIPT_1: @encourage moves that make most sense; bitfield 0x2
	jumpiftargetisally END_LOCATION
	call_cmd LOGIC_BASED_ON_HELDITEM
	call_cmd LOGIC_BASED_ON_ABILITIES
	call_cmd LOGIC_BASED_ON_MOVEEFFECTS
	return_cmd
LOGIC_BASED_ON_MOVEEFFECTS:
	jumpifmovescriptEQ 2 LOGIC_ONESTATUSER
	jumpifmovescriptEQ 3 LOGIC_ONESTATTARGET
	jumpifmovescriptEQ 9 LOGIC_ONESTATTARGET
	jumpifmovescriptEQ 12 LOGIC_PUTTOSLEEP
	jumpifmovescriptEQ 13 LOGIC_APPLYSTATCONDITION
	jumpifmovescriptEQ 14 LOGIC_APPLYSTATCONDITION
	jumpifmovescriptEQ 15 LOGIC_APPLYPARALYSIS
	jumpifmovescriptEQ 16 LOGIC_APPLYSTATCONDITION
	jumpifmovescriptEQ 19 LOGIC_RECOIL
	jumpifmovescriptEQ 25 LOGIC_HPHEAL
	jumpifmovescriptEQ 27 LOGIC_CHARGE
	jumpifmovescriptEQ 29 LOGIC_HPHEAL	@Roost
	jumpifmovescriptEQ 31 LOGIC_IDENTYFING
	jumpifmovescriptEQ 34 LOGIC_PROTECT
	jumpifmovescriptEQ 40 LOGIC_WRAP
	jumpifmovescriptEQ 64 LOGIC_MEANLOOK
	jumpifmovescriptEQ 65 LOGIC_PERISHSONG
	jumpifmovescriptEQ 70 LOGIC_ONEHITKO
	jumpifmovescriptEQ 72 LOGIC_ROAR
	jumpifmovescriptEQ 83 LOGIC_DEFENSECURL
	jumpifmovescriptEQ 93 LOGIC_REST
	jumpifmovescriptEQ 100 LOGIC_LOCKON
	jumpifmovescriptEQ 102 LOGIC_BELLYDRUM
	jumpifmovescriptEQ 104 LOGIC_CURSE
	jumpifmovescriptEQ 113 LOGIC_RAPIDSPIN
	jumpifmovescriptEQ 120 LOGIC_FOCUSPUNCH
	jumpifmovescriptEQ 130 LOGIC_BRICKBREAK
	jumpifmovescriptEQ 163 LOGIC_SUNNYDAY
	return_cmd
LOGIC_IDENTYFING:
	call_cmd CAN_TARGET_FAINT_USER
	jumpifbytevarEQ 0x1 POINTS_MINUS2
	jumpifstatbuffGE bank_target STAT_EVASION 7 POINTS_PLUS2
	return_cmd
LOGIC_CHARGE:
	call_cmd LOGIC_ONESTATUSER
	jumpifstatus3 bank_ai STATUS3_CHARGED END_LOCATION
	jumpifhasattackingmovewithtype bank_ai TYPE_ELECTRIC POINTS_PLUS1
	return_cmd
LOGIC_DEFENSECURL:
	call_cmd LOGIC_ONESTATUSER
	jumpifstatus2 bank_ai STATUS2_CURLED END_LOCATION
	jumpifhasmove bank_ai MOVE_ROLLOUT POINTS_PLUS1
	jumpifhasmove bank_ai MOVE_ICE_BALL POINTS_PLUS1
	return_cmd
LOGIC_BRICKBREAK:
	jumpifsideaffecting bank_target SIDE_REFLECT | SIDE_LIGHTSCREEN POINTS_PLUS1
	return_cmd
LOGIC_ONEHITKO:
	islockon_on bank_ai bank_target
	jumpifbytevarEQ 0x1 POINTS_PLUS4
	return_cmd
LOGIC_LOCKON:
	jumpifability bank_ai ABILITY_NO_GUARD 1 POINTS_MINUS5
	jumpifability bank_target ABILITY_NO_GUARD 1 POINTS_MINUS5
	hasmovewithaccuracylower bank_ai 100
	jumpifbytevarEQ 0x0 POINTS_MINUS1
	hasmovewithaccuracylower bank_ai 40
	jumpifbytevarEQ 0x1 POINTS_PLUS2
	hasmovewithaccuracylower bank_ai 86
	jumpifbytevarEQ 0x1 POINTS_PLUS1
	return_cmd
ENCOURAGE_IF_DREAMEATERNIGHTMARE:
	jumpifhasmove bank_ai MOVE_DREAM_EATER POINTS_PLUS1
	jumpifhasmove bank_ai MOVE_NIGHTMARE POINTS_PLUS1
	return_cmd
LOGIC_PUTTOSLEEP:
	call_cmd ENCOURAGE_IF_DREAMEATERNIGHTMARE
LOGIC_APPLYSTATCONDITION:
	call_cmd CAN_TARGET_FAINT_USER
	jumpifbytevarEQ 1 POINTS_MINUS3
	return_cmd
LOGIC_APPLYPARALYSIS:
	call_cmd LOGIC_APPLYSTATCONDITION
	jumpifstrikesfirst bank_target bank_ai POINTS_PLUS4
	scoreupdate 3
	return_cmd
LOGIC_SUNNYDAY:
	cantargetfaintuser 1
	jumpifbytevarEQ 0x1 POINTS_MINUS1
	jumpifability bank_ai 1 ABILITY_CHLOROPHYLL POINTS_PLUS2
	jumpifhasmove bank_ai MOVE_SOLAR_BEAM POINTS_PLUS2
	jumpifhasmove bank_ai MOVE_GROWTH POINTS_PLUS2
	jumpifhasmove bank_ai MOVE_SYNTHESIS POINTS_PLUS2
	isoftype bank_ai TYPE_FIRE
	jumpifbytevarEQ 0x1 POINTS_PLUS2
	return_cmd
LOGIC_CURSE:
	isoftype bank_ai TYPE_GHOST
	jumpifbytevarEQ 0x0 END_LOCATION
	cantargetfaintuser 1
	jumpifbytevarEQ 0x1 POINTS_MINUS1
	call_cmd IS_TARGET_UNABLETOESCAPE
	call_cmd PLUS1_IF_VAR_NE_0
	call_cmd PLUS1_IF_VAR_NE_0
	return_cmd
LOGIC_RECOIL: @Don't risk using recoil move, if it won't make difference
	getability bank_ai 1
	jumpifbytevarEQ ABILITY_ROCK_HEAD END_LOCATION
	isrecoilmovenecessary
	jumpifbytevarEQ 0x0 POINTS_MINUS3
	return_cmd
LOGIC_HPHEAL:
	jumpifhealthLT bank_ai 26 POINTS_PLUS4
	jumpifhealthGE bank_ai 67 END_LOCATION
	getlastusedmove bank_ai
	vartovar2
	getmoveid
	jumpifvarsEQ END_LOCATION
	jumpifhealthLT bank_ai 56 POINTS_PLUS2
	return_cmd
LOGIC_ROAR_ON_EVASION_BOOST:
	jumpifability bank_ai 1 ABILITY_NO_GUARD END_LOCATION
	jumpifability bank_target 1 ABILITY_NO_GUARD END_LOCATION
	jumpifstatus2 bank_target STATUS2_IDENTIFIED END_LOCATION
	jumpifbankaffecting bank_target BANK_AFFECTING_MIRACLEEYE END_LOCATION
	jumpifstatbuffGE bank_ai STAT_EVASION 7 POINTS_PLUS2
	return_cmd
LOGIC_ROAR_ON_SUBSTITUTE:
	jumpifnostatus2 bank_target STATUS2_SUBSTITUTE END_LOCATION
	getbestdamagelefthp bank_ai bank_target
	jumpifbytevarGE 25 END_LOCATION
	jumpifability bank_ai 1 ABILITY_INFILTRATOR END_LOCATION
	scoreupdate 3
	return_cmd
LOGIC_ROAR:
	scoreupdate -1 @to not use it when it's not necessary
	cantargetfaintuser 1
	jumpifbytevarEQ 1 POINTS_MINUS5
	call_cmd LOGIC_ROAR_ON_EVASION_BOOST
	call_cmd LOGIC_ROAR_ON_SUBSTITUTE
	jumpifstatbuffGE bank_target STAT_ATK 7 POINTS_PLUS3
	jumpifstatbuffGE bank_target STAT_SP_ATK 7 POINTS_PLUS3
	return_cmd
LOGIC_REST:
	cantargetfaintuser 1
	call_cmd PLUS1_IF_VAR_NE_0
	return_cmd
HAS_ATTACKER_PRIORITY_MOVE:
	hasprioritymove bank_ai
	return_cmd
PLUS1_IF_VAR_NE_0:
	jumpifbytevarNE 0x0 POINTS_PLUS1
	return_cmd
LOGIC_BELLYDRUM:
	hasanymovewithsplit bank_ai SPLIT_PHYSICAL
	jumpifbytevarEQ 0x0 POINTS_MINUS3
	gettypeofattacker bank_ai
	jumpifbytevarEQ SPLIT_SPECIAL POINTS_MINUS1
	cantargetfaintuser 1
	jumpifbytevarEQ 1 POINTS_MINUS1
	call_cmd HAS_ATTACKER_PRIORITY_MOVE
	call_cmd PLUS1_IF_VAR_NE_0
	return_cmd
LOGIC_FOCUSPUNCH:
	jumpifstatus2 bank_ai STATUS2_SUBSTITUTE POINTS_PLUS2
	return_cmd
LOGIC_PROTECT:
	getprotectuses bank_ai
	jumpifbytevarNE 0 END_LOCATION
	jumpifmove MOVE_ENDURE LOGIC_ENDURE
	isinsemiinvulnerablestate bank_target
	jumpifbytevarEQ 1 POINTS_PLUS5
	isintruantturn bank_target
	jumpifbytevarEQ 1 POINTS_PLUS5
	jumpifstatus3 bank_target STATUS3_PERISHSONG POINTS_PLUS2
	return_cmd
LOGIC_ENDURE:
	jumpifhealthLT bank_ai 25 POINTS_MINUS2
	cantargetfaintuser 1
	jumpifbytevarEQ 0x0 POINTS_MINUS1
	jumpifhasmove bank_ai MOVE_FLAIL POINTS_PLUS1
	jumpifhasmove bank_ai MOVE_REVERSAL POINTS_PLUS1
	return_cmd
LOGIC_TRAPPING:
	jumpifhasmove bank_ai MOVE_PERISH_SONG POINTS_PLUS2
	jumpifstatus2 bank_target STATUS2_CURSED POINTS_PLUS2
	jumpifhasmove bank_ai MOVE_CURSE POINTS_PLUS1
	return_cmd
LOGIC_MEANLOOK:
	call_cmd IS_TARGET_UNABLETOESCAPE
	jumpifbytevarEQ 0x1 END_LOCATION
	call_cmd LOGIC_TRAPPING
	return_cmd
LOGIC_WRAP:
	jumpifstatus2 bank_target STATUS2_WRAPPED END_LOCATION
	call_cmd LOGIC_TRAPPING
	return_cmd
LOGIC_RAPIDSPIN:
	arehazardson bank_ai
	jumpifbytevarEQ 1 POINTS_PLUS2
	return_cmd
LOGIC_PERISHSONG:
	jumpifstatus3 bank_ai STATUS3_PERISHSONG END_LOCATION
	call_cmd IS_TARGET_UNABLETOESCAPE
	jumpifbytevarEQ 0x0 END_LOCATION
	jumpifhealthLT bank_ai 31 END_LOCATION
	call_cmd POINTS_PLUS3
	jumpifhasmovewithscript bank_ai 34 POINTS_PLUS1
	return_cmd
CAN_TARGET_FAINT_USER:
	cantargetfaintuser 1
	jumpifbytevarEQ 0x1 END_LOCATION
	jumpifstrikesfirst bank_ai bank_target END_LOCATION
	cantargetfaintuser 2
	return_cmd
LOGIC_ONESTATUSER:
	call_cmd CAN_TARGET_FAINT_USER
	jumpifbytevarEQ 0x1 POINTS_MINUS2
	logiconestatuser
	return_cmd
LOGIC_ONESTATTARGET:
	call_cmd CAN_TARGET_FAINT_USER
	jumpifbytevarEQ 0x1 POINTS_MINUS3
	logiconestattarget
	return_cmd
LOGIC_BASED_ON_ABILITIES: @To do Contrary
	getability bank_ai 1
	jumpifbytevarEQ ABILITY_SPEED_BOOST ABILITY_USER_SPEEDBOOST
	jumpifbytevarEQ ABILITY_SERENE_GRACE ABILITY_USER_SERENEGRACE
	jumpifbytevarEQ ABILITY_TRUANT ABILITY_USER_TRUANT
	return_cmd
ABILITY_USER_SERENEGRACE:
	jumpifability bank_target 1 ABILITY_SHIELD_DUST END_LOCATION
	getmoveeffectchance
	jumpifbytevarEQ 0x0 END_LOCATION
	call_cmd POINTS_PLUS1
	jumpifstatus bank_target STATUS_PARALYSIS SERENEGRACE_FLINCHPARHAX
	return_cmd
SERENEGRACE_FLINCHPARHAX:
	jumpifability bank_target 1 ABILITY_INNER_FOCUS END_LOCATION
	jumpifstrikessecond bank_ai bank_target END_LOCATION
	jumpifmovescriptEQ 11 POINTS_PLUS1
	return_cmd
IFBATONPASS_PLUS1:
	jumpifmove MOVE_BATON_PASS POINTS_PLUS1
	return_cmd
ABILITY_USER_TRUANT:
	jumpifmovescriptEQ 39 POINTS_PLUS1 @recharge needed
	return_cmd
ABILITY_USER_SPEEDBOOST:
	call_cmd IFBATONPASS_PLUS1
	jumpifstrikesfirst bank_ai bank_target END_LOCATION
	getprotectuses bank_ai
	jumpifbytevarNE 0x0 END_LOCATION
	jumpifmove MOVE_ENDURE END_LOCATION
	jumpifmovescriptNE 34 END_LOCATION
	goto_cmd POINTS_PLUS1
LOGIC_BASED_ON_HELDITEM:
	getitemeffect bank_ai 1
	jumpifbytevarEQ ITEM_EFFECT_SITRUSBERRY HELDITEM_USER_SITRUS
	jumpifbytevarEQ ITEM_EFFECT_CHESTOBERRY HELDITEM_USER_CHESTO
	jumpifbytevarEQ ITEM_EFFECT_LIECHIBERRY HELDITEM_USER_BERRYSTATRAISE
	jumpifbytevarEQ ITEM_EFFECT_GANLONBERRY HELDITEM_USER_BERRYSTATRAISE
	jumpifbytevarEQ ITEM_EFFECT_SALACBERRY HELDITEM_USER_BERRYSTATRAISE
	jumpifbytevarEQ ITEM_EFFECT_PETAYABERRY HELDITEM_USER_BERRYSTATRAISE
	jumpifbytevarEQ ITEM_EFFECT_APICOTBERRY HELDITEM_USER_BERRYSTATRAISE
	jumpifbytevarEQ ITEM_EFFECT_STARFBERRY HELDITEM_USER_BERRYSTATRAISE
	jumpifbytevarEQ ITEM_EFFECT_LANSATBERRY HELDITEM_USER_BERRYFOCUSENERGY
	jumpifbytevarEQ ITEM_EFFECT_WHITEHERB HELDITEM_USER_WHITEHERB
	jumpifbytevarEQ ITEM_EFFECT_CHOICEBAND HELDITEM_USER_CHOICEBAND
	jumpifbytevarEQ ITEM_EFFECT_CHOICESPECS HELDITEM_USER_CHOICESPECS
	jumpifbytevarEQ ITEM_EFFECT_CHOICESCARF HELDITEM_USER_CHOICESCARF
	jumpifbytevarEQ ITEM_EFFECT_SCOPELENS HELDITEM_USER_ENCOURAGECRITS
	jumpifbytevarEQ ITEM_EFFECT_LUCKYPUNCH HELDITEM_USER_ENCOURAGECRITS
	jumpifbytevarEQ ITEM_EFFECT_STICK HELDITEM_USER_ENCOURAGECRITS
	jumpifbytevarEQ ITEM_EFFECT_LEFTOVERS HELDITEM_USER_LEFTOVERS
	jumpifbytevarEQ ITEM_EFFECT_WIDELENS HELDITEM_USER_WIDELENS
	jumpifbytevarEQ ITEM_EFFECT_ZOOMLENS HELDITEM_USER_ZOOMLENS
	jumpifbytevarEQ ITEM_EFFECT_HEATROCK HELDITEM_USER_HEATROCK
	jumpifbytevarEQ ITEM_EFFECT_ICYROCK HELDITEM_USER_ICYROCK
	jumpifbytevarEQ ITEM_EFFECT_SMOOTHROCK HELDITEM_USER_SMOOTHROCK
	jumpifbytevarEQ ITEM_EFFECT_DAMPROCK HELDITEM_USER_DAMPROCK
	jumpifbytevarEQ ITEM_EFFECT_LIGHTCLAY HELDITEM_USER_LIGHTCLAY
	jumpifbytevarEQ ITEM_EFFECT_BINDINGBAND HELDITEM_USER_ENCOURAGEWRAP
	jumpifbytevarEQ ITEM_EFFECT_GRIPCLAW HELDITEM_USER_ENCOURAGEWRAP
	return_cmd
.align 1
MOVES_LOWERING_USERS_STAT:
.hword MOVE_CURSE, MOVE_OVERHEAT, MOVE_DRACO_METEOR, MOVE_LEAF_STORM, MOVE_SHELL_SMASH, 0xFFFF
HELDITEM_USER_ENCOURAGEWRAP:
	jumpifnostatus2 bank_target STATUS2_WRAPPED POINTS_PLUS1
	return_cmd
HELDITEM_USER_CHESTO:
	jumpifhealthGE 50 bank_ai END_LOCATION
	jumpifhasmove bank_ai MOVE_REST POINTS_PLUS1
	return_cmd
HELDITEM_USER_LIGHTCLAY:
	jumpifmove MOVE_REFLECT POINTS_PLUS1
	jumpifmove MOVE_LIGHT_SCREEN POINTS_PLUS1
	return_cmd
HELDITEM_USER_DAMPROCK:
	jumpifmove MOVE_RAIN_DANCE POINTS_PLUS1
	return_cmd
HELDITEM_USER_SMOOTHROCK:
	jumpifmove MOVE_SANDSTORM POINTS_PLUS1
	return_cmd
HELDITEM_USER_ICYROCK:
	jumpifmove MOVE_HAIL POINTS_PLUS1
	return_cmd
HELDITEM_USER_HEATROCK:
	jumpifmove MOVE_SUNNY_DAY POINTS_PLUS1
	return_cmd
HELDITEM_USER_ZOOMLENS:
	jumpifstrikesfirst bank_ai bank_target END_LOCATION
HELDITEM_USER_WIDELENS:
	islockon_on bank_ai bank_target
	jumpifbytevarEQ 0x1 END_LOCATION
	jumpifability bank_ai ABILITY_NO_GUARD 1 END_LOCATION
	jumpifability bank_target ABILITY_NO_GUARD 1 END_LOCATION
	getmoveaccuracy
	jumpifbytevarLT 79 POINTS_PLUS2
	jumpifbytevarLT 91 POINTS_PLUS1
	return_cmd
HELDITEM_USER_LEFTOVERS:
	jumpifmove MOVE_ENDURE END_LOCATION
	jumpifhealthGE bank_ai 89 END_LOCATION
	getprotectuses bank_ai
	jumpifbytevarNE 0x0 END_LOCATION
	jumpifmovescriptNE 34 END_LOCATION @Protect Spamming to restore HP
	jumpifhealthLT bank_ai 25 POINTS_PLUS2
	goto_cmd POINTS_PLUS1
HELDITEM_USER_ENCOURAGECRITS:
	hashighcriticalratio
	jumpifbytevarEQ 0x1 POINTS_PLUS1
	return_cmd
HELDITEM_USER_CHOICEITEM_ENCOURAGE_VOLTSWITCH:
	countalivepokes bank_ai
	jumpifbytevarEQ 0x0 END_LOCATION
	jumpifmovescriptEQ 35 POINTS_PLUS2
	return_cmd
HELDITEM_USER_CHOICESPECS:
	getmovesplit
	jumpifbytevarNE SPLIT_SPECIAL POINTS_MINUS12
	call_cmd HELDITEM_USER_CHOICEITEM_ENCOURAGE_VOLTSWITCH
	jumpifmostpowerful POINTS_PLUS2
	return_cmd
HELDITEM_USER_CHOICEBAND:
	getmovesplit
	jumpifbytevarNE SPLIT_PHYSICAL POINTS_MINUS12
	call_cmd HELDITEM_USER_CHOICEITEM_ENCOURAGE_VOLTSWITCH
	jumpifmostpowerful POINTS_PLUS2
	return_cmd
HELDITEM_USER_CHOICESCARF:
	getmovesplit
	jumpifbytevarEQ SPLIT_STATUS POINTS_MINUS12
	call_cmd HELDITEM_USER_CHOICEITEM_ENCOURAGE_VOLTSWITCH
	jumpifmostpowerful POINTS_PLUS2
	return_cmd
HELDITEM_USER_WHITEHERB:
	getmoveid
	jumpifhwordvarinlist MOVES_LOWERING_USERS_STAT POINTS_PLUS1
	return_cmd
HELDITEM_USER_SITRUS:
	jumpifmove MOVE_BELLY_DRUM POINTS_PLUS1
	return_cmd
HELDITEM_USER_BERRYFOCUSENERGY:
	jumpifstatus2 bank_ai STATUS2_PUMPEDUP END_LOCATION
HELDITEM_USER_BERRYSTATRAISE:
	cantargetfaintuser 1
	jumpifbytevarEQ 0x0 END_LOCATION
	jumpifmove MOVE_ENDURE POINTS_PLUS2
	return_cmd

TAI_SCRIPT_3: @ENCOURAGE status moves if it's a first turn; bitfield 0x8
	jumpiftargetisally END_LOCATION
	getmovesplit
	jumpifbytevarNE SPLIT_STATUS END_LOCATION
	getbattleturncounter
	jumpifbytevarNE 0x00 END_LOCATION
	jumpifrandLT 0x50 END_LOCATION
	scoreupdate 2
	return_cmd
	
TAI_SCRIPT_7: @Act Smart During Double Battles
	jumpiftargetisally CONSIDER_MOVE_ON_ALLY
	canusemultitargetmove
	jumpifbytevarEQ 0x0 POINTS_MINUS10
	getpartnerchosenmove
	jumpifwordvarEQ MOVE_HELPING_HAND PARTNER_CHOSE_HELPING_HAND
	return_cmd
PARTNER_CHOSE_HELPING_HAND:
	getmovesplit
	jumpifbytevarEQ SPLIT_STATUS POINTS_MINUS12
	return_cmd
CONSIDER_MOVE_ON_ALLY:
	jumpifmove MOVE_HELPING_HAND CONSIDER_HELPINGHAND
	goto_cmd POINTS_MINUS30
CONSIDER_HELPINGHAND:
	getpartnerchosenmove
	jumpifwordvarEQ 0x0 HELPING_HAND_IFPARTNERCANATTACK
	getvarmovepower
	jumpifbytevarEQ 0x0 POINTS_MINUS10
	scoreupdate 1
	return_cmd
HELPING_HAND_IFPARTNERCANATTACK:
	hasanydamagingmoves bank_aipartner
	jumpifbytevarEQ 0x0 POINTS_MINUS10
	return_cmd
	
TAI_SCRIPT_1D: @roaming
	call_cmd IS_AI_UNABLETOESCAPE
	jumpifbytevarEQ 0x1 END_LOCATION
	flee

.align 4
tai_command_table:
.byte 0x79, 0x11, 0x13, 0x08	@0x0
.byte 0xB9, 0x11, 0x13, 0x08	@0x1
.byte 0xF9, 0x11, 0x13, 0x08	@0x2
.byte 0x39, 0x12, 0x13, 0x08	@0x3
.byte 0x79, 0x12, 0x13, 0x08	@0x4
.byte 0xBD, 0x12, 0x13, 0x08	@0x5
.byte 0x25, 0x13, 0x13, 0x08	@0x6
.byte 0x8D, 0x13, 0x13, 0x08	@0x7
.byte 0xF5, 0x13, 0x13, 0x08	@0x8
.byte 0x5D, 0x14, 0x13, 0x08	@0x9
.byte 0xD1, 0x14, 0x13, 0x08	@0xA
.byte 0x45, 0x15, 0x13, 0x08	@0xB
.byte 0xB9, 0x15, 0x13, 0x08	@0xC
.byte 0x2D, 0x16, 0x13, 0x08	@0xD
.byte 0x9D, 0x16, 0x13, 0x08	@0xE
.byte 0x0D, 0x17, 0x13, 0x08	@0xF
.byte 0x89, 0x17, 0x13, 0x08	@0x10
.byte 0x05, 0x18, 0x13, 0x08	@0x11
.byte 0x41, 0x18, 0x13, 0x08	@0x12
.byte 0x7D, 0x18, 0x13, 0x08	@0x13
.byte 0xB9, 0x18, 0x13, 0x08	@0x14
.byte 0xF5, 0x18, 0x13, 0x08	@0x15
.byte 0x49, 0x19, 0x13, 0x08	@0x16
.byte 0x9D, 0x19, 0x13, 0x08	@0x17
.byte 0xF1, 0x19, 0x13, 0x08	@0x18
.byte 0x45, 0x1A, 0x13, 0x08	@0x19
.byte 0x89, 0x1A, 0x13, 0x08	@0x1A
.byte 0xCD, 0x1A, 0x13, 0x08	@0x1B
.byte 0x35, 0x1B, 0x13, 0x08	@0x1C
.byte 0xA1, 0x1B, 0x13, 0x08	@0x1D
.byte 0x0D, 0x1C, 0x13, 0x08	@0x1E
.byte 0x7D, 0x1C, 0x13, 0x08	@0x1F
.byte 0xED, 0x1C, 0x13, 0x08	@0x20
.byte 0x5D, 0x1D, 0x13, 0x08	@0x21
.byte 0x81, 0x1D, 0x13, 0x08	@0x22
.byte 0x1D, 0x1F, 0x13, 0x08	@0x23
.word tai24_ismostpowerful + 1	@0x24
.byte 0x4D, 0x21, 0x13, 0x08	@0x25
.byte 0xA5, 0x21, 0x13, 0x08	@0x26
.byte 0xE1, 0x21, 0x13, 0x08	@0x27
.word tai28_jumpifstrikesfirst + 1	@0x28
.word tai29_jumpifstrikessecond + 1	@0x29
.word tai2A_discourage_moves_based_on_abilities + 1	@0x2A
.word tai2B_affected_by_substitute + 1	@0x2B
.byte 0xBD, 0x22, 0x13, 0x08	@0x2C
.byte 0xB9, 0x23, 0x13, 0x08	@0x2D
.byte 0xD5, 0x23, 0x13, 0x08	@0x2E
.word tai2F_getability + 1		@0x2F
.byte 0x15, 0x26, 0x13, 0x08	@0x30
.word tai31_jumpifeffectiveness_EQ + 1	@0x31
.word tai32_jumpifeffectiveness_NE + 1	@0x32
.word tai33_is_in_semiinvulnerable_state + 1	@0x33
.byte 0xD9, 0x27, 0x13, 0x08	@0x34
.byte 0xB9, 0x28, 0x13, 0x08	@0x35
.word tai36_jumpifweather + 1	@0x36
.byte 0x01, 0x2A, 0x13, 0x08	@0x37
.byte 0x4D, 0x2A, 0x13, 0x08	@0x38
.byte 0x99, 0x2A, 0x13, 0x08	@0x39
.byte 0x01, 0x2B, 0x13, 0x08	@0x3A
.byte 0x69, 0x2B, 0x13, 0x08	@0x3B
.byte 0xD1, 0x2B, 0x13, 0x08	@0x3C
.word tai3D_jumpiffatal + 1		@0x3D
.word tai3E_jumpifnotfatal + 1	@0x3E
.word tai3F_jumpifhasmove + 1				@0x3F
.byte 0x49, 0x2F, 0x13, 0x08	@0x40
.byte 0x21, 0x30, 0x13, 0x08	@0x41
.byte 0x19, 0x31, 0x13, 0x08	@0x42
.byte 0xFD, 0x31, 0x13, 0x08	@0x43
.byte 0x85, 0x32, 0x13, 0x08	@0x44
.byte 0x15, 0x33, 0x13, 0x08	@0x45
.byte 0x29, 0x33, 0x13, 0x08	@0x46
.byte 0x89, 0x33, 0x13, 0x08	@0x47
.word tai48_getitemeffect + 1	@0x48
.byte 0x95, 0x34, 0x13, 0x08	@0x49
.byte 0xED, 0x34, 0x13, 0x08	@0x4A
.byte 0x39, 0x35, 0x13, 0x08	@0x4B
.byte 0x85, 0x35, 0x13, 0x08	@0x4C
.byte 0xAD, 0x35, 0x13, 0x08	@0x4D
.byte 0xF9, 0x35, 0x13, 0x08	@0x4E
.byte 0x25, 0x36, 0x13, 0x08	@0x4F
.byte 0x51, 0x36, 0x13, 0x08	@0x50
.word tai51_getprotectuses + 1				@0x51
.word tai52_movehitssemiinvulnerable + 1	@0x52
.word tai53_getmovetarget + 1				@0x53
.word tai54_getvarmovetarget + 1			@0x54
.word tai55_isstatchangepositive + 1		@0x55
.word tai56_getstatvaluemovechanges + 1		@0x56
.word tai57_jumpifbankaffecting + 1			@0x57
.byte 0xE1, 0x36, 0x13, 0x08	@0x58
.byte 0x11, 0x37, 0x13, 0x08	@0x59
.byte 0x31, 0x37, 0x13, 0x08	@0x5A
.byte 0x55, 0x37, 0x13, 0x08	@0x5B
.byte 0x2D, 0x38, 0x13, 0x08	@0x5C
.byte 0x7D, 0x38, 0x13, 0x08	@0x5D
.byte 0xCD, 0x38, 0x13, 0x08	@0x5E
.word tai5F_is_of_type + 1		@0x5F
.word tai60_checkability + 1	@0x60
.byte 0x1D, 0x39, 0x13, 0x08	@0x61
.byte 0x15, 0x34, 0x13, 0x08	@0x62
.word tai63_jumpiffieldaffecting + 1	@0x63
.word tai64_isbankinlovewith + 1		@0x64
.word tai65_vartovar2 + 1			@0x65
.word tai66_jumpifvarsEQ + 1		@0x66
.word tai67_jumpifcantaddthirdtype + 1 	@0x67
.word tai68_canchangeability + 1 		@0x68
.word tai69_getitempocket + 1 			@0x69
.word tai6A_discouragehazards + 1 		@0x6A
.word tai6B_sharetype + 1 				@0x6B
.word tai6C_isbankpresent + 1			@0x6C 
.word tai6D_jumpifwordvarEQ + 1  		@0x6D
.word tai6E_islockon_on + 1 			@0x6E
.word tai6F_discouragesports + 1 		@0x6F
.word tai70_jumpifnewsideaffecting + 1 	@0x70
.word tai71_getmovesplit + 1    		@0x71
.word tai72_cantargetfaintuser + 1 		@0x72
.word tai73_hashighcriticalratio + 1 	@0x73
.word tai74_getmoveaccuracy + 1 		@0x74
.word tai75_logiconestatuser + 1 		@0x75
.word tai76_logiconestattarget + 1 		@0x76
.word tai77_abilitypreventsescape + 1 	@0x77
.word tai78_setbytevar + 1 				@0x78
.word tai79_arehazardson + 1 			@0x79
.word tai7A_gettypeofattacker + 1 		@0x7A
.word tai7B_hasanymovewithsplit + 1 	@0x7B
.word tai7C_hasprioritymove + 1 		@0x7C
.word tai7D_getbestdamage_lefthp + 1 	@0x7D
.word tai7E_isrecoilmove_necessary + 1  @0x7E
.word tai7F_isintruantturn + 1 			@0x7F
.word tai80_getmoveeffectchance + 1 	@0x80
.word tai81_hasmovewithaccuracylower + 1 	@0x81
.word tai82_getpartnerchosenmove + 1 		@0x82
.word tai83_hasanydamagingmoves + 1 	@0x83
.word tai84_jumpifcantusemove + 1		@0x84
.word tai85_canmultiplestatwork + 1 	@0x85
.word tai86_jumpifhasattackingmovewithtype + 1 		@0x86
.word tai87_jumpifhasnostatusmoves + 1		@0x87
.word tai88_jumpifstatusmovesnotworthusing + 1 		@0x88
.word tai89_jumpifsamestatboosts + 1							@0x89
.word tai8A_can_use_multitarget_move + 1					@0x8A

.align 2
correct_0x2ddf6A:
.hword 0xB6,0xC5,0xFFFF


