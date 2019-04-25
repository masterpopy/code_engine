#ifndef DEFINES_H
#define DEFINES_H

#include "types.h"
#include "config.h"

//defines for protect-like moves argument, arg1
#define PR_counter_incr 0x1
#define PR_fail_chance 0x2
#define PR_affects_allies 0x4
//defines for protect-like moves argument, arg2
#define PR_protect 0x1
#define PR_endure 0x2
#define PR_quick_guard 0x3
#define PR_wide_guard 0x4
#define PR_kings_shield 0x5
#define PR_spiky_shield 0x6
#define PR_mat_block 0x7
#define PR_crafty_shield 0x8
#define PR_baneful_bunker 0x9

#define CURRENT_Z_MOVE *((u16*)0x2037610)
enum move_split
{
    MOVE_PHYSICAL, //0
    MOVE_SPECIAL, //1
    MOVE_STATUS, //2
};

enum poke_sprite
{
    SPRITE_BACK = 0, SPRITE_FRONT = 1
};

enum poke_gender
{
    POKE_MALE = 0, POKE_FEMALE = 0xFE, POKE_GENDERLESS = 0xFF
};

enum menu_action
{
    ACTION_MOVE = 0, //0x0
    ACTION_ITEM, //0x1
    ACTION_SWITCH, //0x2
    ACTION_RUN, //0x3
};

enum item_pocket
{
    POCKET_ITEMS = 1, POCKET_BALLS, //0x2
    POCKET_TMS, //0x3
    POCKET_BERRIES, //0x4
    POCKET_KEYITEMS, //0x5
};

enum ball_index
{
    BALL_POKE, //0x0
    BALL_GREAT, //0x1
    BALL_SAFARI, //0x2
    BALL_ULTRA, //0x3
    BALL_MASTER, //0x4
    BALL_NET, //0x5
    BALL_DIVE, //0x6
    BALL_NEST, //0x7
    BALL_REPEAT, //0x8
    BALL_TIMER, //0x9
    BALL_LUXURY, //0xA
    BALL_PREMIER, //0xB
    //new balls
#if EXPANDED_POKEBALLS == true
    BALL_LEVEL, //0xC
    BALL_LURE, //0xD
    BALL_MOON, //0xE
    BALL_FRIEND, //0xF
    BALL_LOVE, //0x10
    BALL_HEAVY, //0x11
    BALL_FAST, //0x12
    BALL_SPORT, //0x13
    BALL_DUSK, //0x14
    BALL_QUICK, //0x15
    BALL_HEAL, //0x16
    BALL_CHERISH, //0x17
    BALL_PARK, //0x18
    BALL_DREAM, //0x19
    BALL_BEAST, //0x1A
#endif // EXPANDED_POKEBALLS
};

enum map_type
{
    MAP_TOWN = 1, MAP_CITY, //0x2
    MAP_ROUTE, //0x3
    MAP_CAVE, //0x4
    MAP_UNDERWATER, //0x5
    MAP_INSIDE = 8, MAP_SECRETBASE, //0x9
};

#include "./defines/poke_types.h"
#include "./defines/abilities.h"
#include "./defines/moves.h"
#include "./defines/get_attr.h"
#include "./defines/items.h"
#include "./defines/item_effects.h"
#include "./defines/pokes.h"
#include "./defines/flavours.h"

#include "battle_structs.h"
#include "battle_locations.h"
#include "new_battle_struct.h"
#include "vanilla_functions.h"

#define MOVE_PHYSICAL 0
#define MOVE_SPECIAL 1
#define MOVE_STATUS 2

#define STAT_ATTACK 1
#define STAT_DEFENCE 2
#define STAT_SPD 3
#define STAT_SP_ATK 4
#define STAT_SP_DEF 5
#define STAT_ACCURACY 6
#define STAT_EVASION 7
#define STAT_CONFUSION 8
#define STAT_SLEEP 9
#define STAT_POISON 10
#define STAT_FREEZE 11
#define STAT_PARALYSIS 12
#define STAT_BURN 13

#define STAT_PRINTABILITY       0x1
#define STAT_CHANGE_VALUES      0x2
#define STAT_SELFINFLICTED      0x40

#define STAT_CHANGED        0x0
#define STAT_UNABLE         0x1
#define STAT_CANT_GO_UP     0x2
#define STAT_CANT_GO_DOWN   0x3


#define EFFECT2_AFFECTSUSER 0x40

#define BACKGROUND_GRASS 0x0
#define BACKGROUND_LONG_GRASS 0x1
#define BACKGROUND_SAND 0x2
#define BACKGROUND_UNDERWATER 0x3
#define BACKGROUND_WATER 0x4
#define BACKGROUND_POND 0x5
#define BACKGROUND_ROCK 0x6
#define BACKGROUND_CAVE 0x7
#define BACKGROUND_INDOORS 0x8
#define BACKGROUND_INDOORS_2 0x9
//new ones
#define BACKGROUND_FRONTIER 10
#define BACKGROUND_GROUDON 11
#define BACKGROUND_KYORGE 12
#define BACKGROUND_RAYQUAZA 13
#define BACKGROUND_LEADER 14
#define BACKGROUND_CHAMPION 15
#define BACKGROUND_GYM 16
#define BACKGROUND_TEAM_MAGMA 17
#define BACKGROUND_TEAM_AQUA 18
#define BACKGROUND_ELITEFOUR1 19
#define BACKGROUND_ELITEFOUR2 20
#define BACKGROUND_ELITEFOUR3 21
#define BACKGROUND_ELITEFOUR4 22

enum trainer_class
{
    CLASS_PKMN_TRAINER0, //0
    CLASS_PKMN_TRAINER1, //1
    CLASS_HIKER, //2
    CLASS_TEAM_AQUA, //3
    CLASS_PKMN_BREEDER, //4
    CLASS_COOLTRAINER, //5
    CLASS_BIRDKEEPER, //6
    CLASS_COLLECTOR, //7
    CLASS_SWIMMER_MALE, //8
    CLASS_TEAM_MAGMA, //9
    CLASS_EXPERT, //xA
    CLASS_AQUA_ADMIN, //xB
    CLASS_BLACK_BELT, //xC
    CLASS_AQUA_LEADER, //xD
    CLASS_HEX_MANIAC, //xE
    CLASS_AROMA_LADY, //xF
    CLASS_RUIN_MANIAC, //x10
    CLASS_INTERVIEWER, //x11
    CLASS_TUBER_FEMALE, //x12
    CLASS_TUBER_MALE, //x13
    CLASS_LADY, //x14
    CLASS_BEAUTY, //x15
    CLASS_RICH_BOY, //x16
    CLASS_POKEMANIAC, //x17
    CLASS_GUITARIST, //x18
    CLASS_KINDLER, //x19
    CLASS_CAMPER, //x1A
    CLASS_PICKNICKER, //x1B
    CLASS_BUG_MANIAC, //x1C
    CLASS_PSYCHIC, //x1D
    CLASS_GENTLEMAN, //x1E
    CLASS_ELITE_FOUR, //x1F
    CLASS_LEADER, //x20
    CLASS_CHAMPION = 0x26,
    CLASS_MAGMA_ADMIN = 0x31,
    CLASS_PKMN_TRAINER_RIVAL = 0x32,
    CLASS_MAGMA_LEADER = 0x35,
    CLASS_DOME_ACE = 0x3B,
    CLASS_PALACE_MAVEN, //0x3C
    CLASS_ARENA_TYCOON, //0x3D
    CLASS_FACTORY_HEAD, //0x3E
    CLASS_PIKE_QUEEN, //0x3F
    CLASS_PYRAMID_KING, //0x40
    CLASS_PKMN_TRAINER2, //0x41
};

#define OUTCOME_WIN 0x1
#define OUTCOME_LOSS 0x2
#define OUTCOME_DRAW 0x3
#define OUTCOME_RAN 0x4

#define POKE_BURMY(species) (species == POKE_BURMY_PLANT || species == POKE_BURMY_SAND || species == POKE_BURMY_TRASH)

#define STAT_NEGATIVE 0x80
#define STAT_STAGES 0x70
#define STAT_STATID 0x7
#define STAT_MULTIPLE 0x8

#define SEPARATE_COURSE (new_battlestruct->various.instruct_phase || new_battlestruct->various.secondary_dancer)
#define MOVE_WORKED !(move_outcome.failed || move_outcome.missed || move_outcome.not_affected)
#define TARGET_TURN_DAMAGED (special_statuses[bank_target].moveturn_losthp)
#define DAMAGING_MOVE(move) (move_table[move].split!=2)
#define CHOICE_ITEM(effect) (effect == ITEM_EFFECT_CHOICEBAND || effect == ITEM_EFFECT_CHOICESCARF || effect == ITEM_EFFECT_CHOICESPECS)
#define CHERRIM_ID(species) (species == POKE_CHERRIM || species == POKE_CHERRIM_SUNSHINE)
#define AEGISLASH_ID(species) (species == POKE_AEGISLASH_BLADE || species == POKE_AEGISLASH_SHIELD)
#define SEMI_INVULNERABLE(bank) (status3[bank].underground || status3[bank].underwater || status3[bank].on_air || status3[bank].phantomforce || new_battlestruct->bank_affecting[bank].sky_drop_attacker || new_battlestruct->bank_affecting[bank].sky_drop_target)
#define MUST_HIT(bank_atk, bank_def) (status3[bank_def].always_hits && disable_structs[bank_def].always_hits_bank == bank_atk)
#define CHECK_KNOCKED_OFF(bank) (battle_effects_duration.knocked_off_pokes[get_bank_side(bank)] & bits_table[battle_team_id_by_side[bank]])
#define SET_KNOCKED_OFF(bank) (battle_effects_duration.knocked_off_pokes[get_bank_side(bank)] |= bits_table[battle_team_id_by_side[bank]])
#define WILD_DOUBLE_BATTLE (battle_flags.double_battle && !battle_flags.trainer && !battle_flags.link)
#define WILD_ATTACKER (!battle_flags.trainer && !battle_flags.link && (bank_attacker & 1) && !(bank_target & 1))
#define read_byte(ptr) (*((u8*)(ptr)))
#define read_hword(ptr) (read_byte(ptr) | ((read_byte(ptr + 1)) << 8))
#define BATTLE_FRONTIER_BATTLE (battle_flags.frontier_general || battle_flags.battle_dome || battle_flags.battle_palace || battle_flags.battle_arena || battle_flags.battle_factory || battle_flags.flag_x100000 || battle_flags.battle_pyramid)
#define ATLEAST_ONE(value)(value != 0 ? value : 1)
#define PERCENT_100(value, percent)((value * percent) / 100)
#define GETS_VIA_EXPSHARE(held_item)((GENVI_EXPSHARE == false && held_item == ITEM_EFFECT_EXPSHARE) || (GENVI_EXPSHARE == true && checkitem(ITEM_EXPSHARE, 1) /*&& getflag(EXPSHARE_FLAG)*/))
#define COIN_FLIP(option1, option2)((rng() & 1) ? option1 : option2)
#define GET_CUSTOMFLAG(flagID)((flagID == 0 ? 0 : (getflag(flagID))))
#define get_1_16_of_max_hp(bank)(ATLEAST_ONE(battle_participants[bank].max_hp >> 4))
#define get_1_8_of_max_hp(bank)(ATLEAST_ONE(battle_participants[bank].max_hp >> 3))
#define get_1_4_of_max_hp(bank)(ATLEAST_ONE(battle_participants[bank].max_hp >> 2))
#define BIC(value, bit)(value & (~(bit)))
#define BANK_PSN(bank)((battle_participants[bank].status.flags.poison || battle_participants[bank].status.flags.toxic_poison))
#define FULL_HP(bank)((battle_participants[bank].current_hp) && (battle_participants[bank].current_hp == battle_participants[bank].max_hp))
#define RAIN_WEATHER ((battle_weather.flags.rain || battle_weather.flags.downpour || battle_weather.flags.permament_rain || battle_weather.flags.heavy_rain))
#define SUN_WEATHER ((battle_weather.flags.sun || battle_weather.flags.permament_sun || battle_weather.flags.harsh_sun))
#define SANDSTORM_WEATHER ((battle_weather.flags.sandstorm || battle_weather.flags.permament_sandstorm))
#define HAIL_WEATHER ((battle_weather.flags.hail || battle_weather.flags.permament_hail))
#define BIT_GET(bit)(((1 << bit)))


//#define LZ77UnCompWram(src, dest) __asm__("mov r0, %0\n\t mov r1, %1\n\t swi 0x11\n\t" : :"r"(src), "r"(dest) : "r0","r1","r2","r3")
//#define LZ77UnCompVram(src, dest) __asm__("mov r0, %0\n\t mov r1, %1\n\t swi 0x12\n\t" : :"r"(src), "r"(dest) : "r0","r1","r2","r3")

#define TRAINER_STEVEN 0xC03
#define PARTNER_ANIMATES 0x8000
#define PARTNER_CUSTOM 0x4000

#define REQUEST_SPECIES_BATTLE  0x1
#define REQUEST_HELDITEM_BATTLE 0x2
#define REQUEST_PPMOVE1_BATTLE  0x9
#define REQUEST_PPMOVE2_BATTLE  0xA
#define REQUEST_PPMOVE3_BATTLE  0xB
#define REQUEST_PPMOVE4_BATTLE  0xC
#define REQUEST_STATUS_BATTLE   0x28
#define REQUEST_HP_BATTLE       0x2A

#define GROUNDED(bank) (get_airborne_state(bank, 0, 1) <= 2)

#define Space 0x00
#define JumpLine 0xFE
#define BuffCharac 0xFD
#define Apos 0xB4
#define Comma 0xB8
#define Dot 0xAD
#define Exclam 0xAB
#define Interro 0xAC
#define Termin 0xFF
#define Dash 0xAE
#define Slash 0xBA

#define wait_for_pressed_key 0xFC, 0x09

#define Poke_e 0x1B

#define A_ 0xBB
#define B_ 0xBC
#define C_ 0xBD
#define D_ 0xBE
#define E_ 0xBF
#define F_ 0xC0
#define G_ 0xC1
#define H_ 0xC2
#define I_ 0xC3
#define J_ 0xC4
#define K_ 0xC5
#define L_ 0xC6
#define M_ 0xC7
#define N_ 0xC8
#define O_ 0xC9
#define P_ 0xCA
#define Q_ 0xCB
#define R_ 0xCC
#define S_ 0xCD
#define T_ 0xCE
#define U_ 0xCF
#define V_ 0xD0
#define W_ 0xD1
#define X_ 0xD2
#define Y_ 0xD3
#define Z_ 0xD4

#define a_ 0xD5
#define b_ 0xD6
#define c_ 0xD7
#define d_ 0xD8
#define e_ 0xD9
#define f_ 0xDA
#define g_ 0xDB
#define h_ 0xDC
#define i_ 0xDD
#define j_ 0xDE
#define k_ 0xDF
#define l_ 0xE0
#define m_ 0xE1
#define n_ 0xE2
#define o_ 0xE3
#define p_ 0xE4
#define q_ 0xE5
#define r_ 0xE6
#define s_ 0xE7
#define t_ 0xE8
#define u_ 0xE9
#define v_ 0xEA
#define w_ 0xEB
#define x_ 0xEC
#define y_ 0xED
#define z_ 0xEE

//Mega icons related
enum mega_trigger_properties
{
    BANK_TO_ATTACH_TRIGGER, ANIM_STATE, PALLET_STATE, RELATIVE_X, BASE_X
};

enum mega_trigger_animation_states
{
    HIDE, POS_BEHIND_HPBAR, SLIDE_OUT, SLIDE_IN, DISABLE, SLIDED_OUT, HIDDEN, DISABLED
};

enum mega_trigger_pallet_states
{
    REGULAR, LIGHT_UP_TRIGGER, TRIGGER_ON, REVERT_COLORS
};


enum mega_indicator_properties
{
    DISABLED_INDICATOR = 1, PRIMAL_CHECK_COMPLETE
};

enum call_mode
{
    BATTLE_TURN, MOVE_TURN
};

bool can_change_stat(u8 bank, bool self_inflicted, u8 statchanger);
const struct evolution_sub* GET_EVO_TABLE(u16 species);

#define stat_get_bits_arg(self_inflicted, print_ability, change_stats) (0 | (self_inflicted ? STAT_SELFINFLICTED:0)|(print_ability ? STAT_PRINTABILITY:0)|(change_stats ? STAT_CHANGE_VALUES:0))
u8 change_stats(u8 bank, u8 bits, void* bs_unable);

#endif /* DEFINES_H */
