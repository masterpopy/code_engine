#ifndef B_STRUCTS
#define B_STRUCTS

struct config
{
	u8 arg1;
	u8 arg2;
};

struct status_main
{
	u32 sleep : 3;
	u32 poison : 1;
	u32 burn : 1;
	u32 freeze : 1;
	u32 paralysis: 1;
	u32 toxic_poison : 1;
	u32 poison_counter : 4;
};

union main_status
{
	u32 int_status;
	struct status_main flags;
};

#define STATUS_SLEEP 0x7
#define STATUS_POISON 0x8
#define STATUS_BURN 0x10
#define STATUS_FREEZE 0x20
#define STATUS_PARALYSIS 0x40
#define STATUS_TOXIC_POISON 0x80
#define STATUS_CONFUSION 0x1

struct flags2
{
	u32 confusion : 3; //0x1 | 0x2 | 0x4
	u32 flinched : 1; //0x8
	u32 uproar : 3; //0x10 | 0x20 | 0x40
	u32 flag_x80 : 1; //0x80
	u32 bide : 2; //0x100 | 0x200
	u32 locked_and_confuse : 2; //0x400 | 0x800
	u32 multiple_turn_move : 1; //0x1000
	u32 trapped_in_wrap : 3; //0x2000 | 0x4000 | 0x8000
	u32 in_love : 4; //each bit for bank 0x10 000 | 0x20 000 | 0x40 0000 | 0x80 000
	u32 focus_energy : 1; //0x100 000
	u32 transformed : 1; //0x200 000
	u32 recharge : 1; //0x400 000
	u32 raged : 1; //0x800 000
	u32 substitute : 1;// 0x1 000 000
	u32 destinny_bond : 1; //0x2 000 000
	u32 cant_escape : 1; //0x4 000 000
	u32 nightmare : 1; //0x8 000 000
	u32 cursed : 1; //0x10 000 000
	u32 foresight : 1; //0x20 000 000
	u32 defense_curled : 1; //0x40 000 000
	u32 tormented : 1; //0x80 000 000
};

struct iv_set
{
	u32 iv_hp: 5;
	u32 iv_atk: 5;
	u32 iv_def: 5;
	u32 iv_spd: 5;
	u32 iv_sp_atk: 5;
	u32 iv_sp_def: 5;
};

struct battle_participant
{
	u16 species;//0
	u16 atk;//2
	u16 def;//4
	u16 spd;//6
	u16 sp_atk;//8
	u16 sp_def;//10
	u16 moves[4];//12
	struct iv_set ivs;//20
	u8 hp_buff;//24
	u8 atk_buff;//25
	u8 def_buff;//26
	u8 spd_buff;//27
	u8 sp_atk_buff;//
	u8 sp_def_buff;
	u8 acc_buff;
	u8 evasion_buff;
	u8 ability_id;//32
	u8 type1;
	u8 type2;
	u8 padd;
	u8 current_pp[4];
	u16 current_hp;
	u8 level;
	u8 happiness;
	u16 max_hp;
	u16 held_item;
	u8 poke_name[12];
	u8 trainer_name[8];
	u32 padd2;
	u32 pid;
	union main_status status;
	struct flags2 status2;
	u32 otid;
};

extern struct battle_participant battle_participants[4];

struct in_battle_weather
{
	u32 rain : 1;
	u32 downpour : 1;
	u32 permament_rain : 1;
	u32 sandstorm : 1;
	u32 permament_sandstorm : 1;
	u32 sun : 1;
	u32 permament_sun : 1;
	u32 hail : 1;
	//custom flags
	u32 permament_hail : 1;
	u32 fog : 1;
	u32 permament_fog : 1;
	u32 harsh_sun : 1;
	u32 heavy_rain : 1;
	u32 air_current : 1;
};

#define weather_rain 1
#define weather_downpour 2
#define weather_permament_rain 4
#define weather_sandstorm 8
#define weather_permament_sandstorm 0x10
#define weather_sun 0x20
#define weather_permament_sun 0x40
#define weather_hail 0x80
#define weather_permament_hail 0x100
#define weather_fog 0x200
#define weather_permament_fog 0x400
#define weather_harsh_sun 0x800
#define weather_heavy_rain 0x1000
#define weather_air_current 0x2000

union battle_weather
{
	u32 int_bw;
	struct in_battle_weather flags;
};

extern union battle_weather battle_weather;

struct b_stuff_duration
{
	u8 field0[32];
	u8 wish_duration[4];
	u8 id_of_wish_user[4];
	u8 weather_dur;
	u8 knocked_off_pokes[2];
};

extern struct b_stuff_duration battle_effects_duration;

struct b_enigma_berry
{
	u8 berry_name[7];
	u8 battle_effect_x12;
	u8 field8[18];
	u8 quality;
	u8 field1B;
};

extern struct b_enigma_berry enigma_berry_battle[4];

struct b_scripting
{
	u8 field_0;
	u8 field_1;
	u8 field_2;
	u8 field_3;
	u32 bide_damage;
	u8 field_8;
	u8 field_9;
	u8 field_A;
	u8 field_B;
	u8 field_C;
	u8 field_D;
	u8 damage_multiplier;
	u8 fieldF;
	u8 AnimInfo1;
	u8 AnimInfo2;
	u8 field12;
	u8 field13;
	u8 cmd49_state_tracker;
	u8 field15;
	u8 field16;
	u8 active_bank;
	u8 field18;
	u8 field19;
	u8 stat_changer;
	u8 field1B;
	u8 cmd23_state_tracker;
	u8 field1D;
	u8 field1E;
	u8 field1F;
	u8 field20;
	u8 field21;
	u8 field22;
	u8 field23;
	u8 field24;
	u8 field25;
};

extern struct b_scripting battle_scripting;

struct mirror_move_set_per_bank
{
	u16 moves_per_target[4];
};

extern struct mirror_move_set_per_bank mirror_move_set_pbs;

struct palette
{
	u16 c[16];
};

extern struct palette palette_obj_faded[16];

struct battle_stuff
{
	u8 end_turn_statetracker1; //0x0
	u8 end_turn_checked_bank; //0x1
	u8 field_2; //0x2
	u8 end_turn_statetracker2; //0x3
	u16 binding_move[4]; //0x4 - 0xB
	u8 move_target[4]; //0xC - 0xF
	u8 expgetter_id; //0x10
	u8 field_11; //0x11
	u8 wildvictorysong; //0x12
	u8 dynamic_move_type; //0x13
	u8 binded_by[4];//0x14-0x17
	u8 field_18[48]; //0x18-0x47
	u8 pre_attacks_bank_counter; //0x48
	u8 field_49; //0x49
	u8 money_multiplier; //0x4A
	u8 field_4B; //0x4B
	u8 switch_in_ability_bank_counter; //0x4C
	u8 field_4D; //0x4D
	u8 field_4E; //0x4E
	u8 field_4F; //0x4F
	u16 exp;    //0x50
	u8 field_52; //0x52
	u8 sentin_pokes; //0x53
	u8 field_54; //0x54
	u8 field_55; //0x55
	u8 field_56; //0x56
	u8 field_57; //0x57
	u8 field_58[4]; //0x58 - 0x5B
	u8 field_5C[17]; //0x5C - 0x6C
	u8 caught_nick[15]; //0x6D - 0x7B
	u8 safari_rate; //0x7C
	u8 field_7D; //0x7D
	u8 field_7E; //0x7E
	u8 castform_switch_form; //0x7F
	u8 chosen_move_position[4]; //0x80
	u8 field_84; //0x84
	u8 field_85; //0x85
	u8 field_86; //0x86
	u8 field_87; //0x87
	u8 field_88; //0x88
	u8 field_89; //0x89
	u8 field_8A; //0x8A
	u8 field_8B; //0x8B
	u8 field_8C; //0x8C
	u8 field_8D; //0x8D
	u8 str_movetype; //0x8E
	u8 expgetter_bank; //0x8F
	u8 field_90; //0x90
	u8 absent_bank_flags_prev_turn; //0x91
	u8 field_92[6]; //0x92-0x97
	u16 mirror_moves_pbs[4]; //0x98-0x9F
	u8 field_A0; //0xA0
	u8 field_A1; //0xA1
	u8 field_A2; //0xA2
	u8 field_A3; //0xA3
	u8 field_A4; //0xA4
	u8 field_A5; //0xA5
	u8 field_A6; //0xA6
	u8 field_A7; //0xA7
	u16 hp_on_switchout[4]; //0xA8 - 0xAF
	u8 field_B0; //0xB0
	u8 curr_hp_bad_scale; //0xB1
	u8 synchronize_effect_chooser; //0xB2
	u8 field_B3[5];
	u16 used_held_items[4]; //0xB8-0xBF
	u8 field_C0[8]; //0xC0-0xC7
	u16 choiced_move[4]; //0xC8-0xCF (checked in cmd49)
	u16 changed_held_items[4]; //0xD0-0xD8 (later written to battlestruct in cmd49)
	u8 intimidate_user; //0xD8
	u8 switch_in_item_bank_counter; //0xD9
	u8 field_DA; //0xDA
	u8 field_DB; //0xDB
	u8 field_DC; //0xDC
	u8 field_DD; //0xDD
	u8 field_DE; //0xDE
	u8 got_exp_from; //0xDF
	struct mirror_move_set_per_bank mirror_move_set_pbs[4]; //0xE0-0xFF
	struct palette castform_pal[4]; //0x100 - 0x179
	u8 field_180[34]; //0x180 - 0x1A1
	u8 battle_load_weather_from_map_flag; //0x1A2
	u8 atk_canceller_state_tracker; //0x1A3
	u8 field_1A4[240]; //0x1A4-0x293
	u8 switchout_index[4]; //0x294-0x297
	u8 field_298[11];
	u8 field_2A3;
};

extern struct battle_stuff* battle_stuff_ptr;

struct special_status
{
	u8 statloweringflag : 1;
	u8 lightning_rod_redirected : 1;
	u8 restored_bank_sprite: 1;
	u8 intimidated_a_poke : 1;
	u8 traced : 1;
	u8 flag20 : 1;
	u8 flag40 : 1;
	u8 focus_banded : 1;
	u8 field1[3];
	u32 moveturn_losthp;
	u32 moveturn_losthp_physical;
	u32 moveturn_losthp_special;
	u8 moveturn_physical_bank;
	u8 moveturn_special_bank;
	u8 field12;
	u8 field13;
};

extern struct special_status special_statuses[4];

struct status_3
{
	u32 leech_seed_hp_receiver : 2; // 2 bits
	u32 leech_seed : 1; //4
	u32 always_hits : 2; //x8 | x10
	u32 perish_song : 1; //x20
	u32 on_air : 1; //x40
	u32 underground : 1;//80
	u32 minimized : 1; //x100
	u32 charged_up : 1; //x200
	u32 rooted : 1; //x400
	u32 yawn : 2; //x800 || x1000
	u32 imprision : 1; //x2000
	u32 grudge : 1; //x4000
	u32 atk_cant_crt : 1; //x8000
	u32 mud_sport : 1; //x10 000
	u32 watersport : 1; //x20 000
	u32 underwater : 1; //x40 000
	u32 switchinlock : 1; //x80 000
	u32 unburden : 1; //x100 000 (previously trace)
	u32 phantomforce : 1; //x200 000
	u32 focus_punch_charge : 1; //x400 000
	u32 innerswitchinlock : 1; //x800 000
};

extern struct status_3 status3[4];

struct disable_struct
{
	u8 field1[4];
	u16 disabled_move;
	u16 encored_move;
	u8 protect_uses;
	u8 stockpile_counter;
	u8 substitute_hp;
	u8 disable_timer;
	u8 encored_index;
	u8 fieldD;
	u8 encore_timer;
	u8 perishsong_timer;
	u8 fury_cutter_timer;
	u8 rollout_timer;
	u8 charge_timer;
	u8 taunt_timer;
	u8 bank_preventing_escape;
	u8 always_hits_bank;
	u8 is_first_turn;
	u8 field17;
	s8 truant_counter;
	u8 recharge_counter;
	u8 field1A;
	u8 field1B;
};

extern struct disable_struct disable_structs[4];

struct protect_struct
{
	u8 flag0_protect : 1;
	u8 flag0_endure : 1;
	u8 flag0_onlystruggle : 1;
	u8 flag0_helpinghand : 1;
	u8 flag0_bouncemove : 1;
	u8 flag0_stealmove : 1;
	u8 flag0_unknown: 1;
	u8 flag0_prlz_immobility: 1;
	u8 flag1_confusion_self_damage: 1;
	u8 flag1_noteffective: 1;
	u8 flag1_chargingturn: 1; //dive, dig etc.
	u8 flag1_smokeballflee: 1;
	u8 flag1_runaway_flee: 1;
	u8 flag1_used_imprisoned_move: 1;
	u8 flag1_love_immobility: 1;
	u8 flag1_used_disabled_move: 1;
	u8 flag2_used_taunted_move: 1;
	u8 flag2_unknown: 1;
	u8 flag2_flinch_immobility : 1;
	u8 flag2_notfirststrike : 1;
	u8 flag2_free: 4;
	u8 field3;
	u32 physical_damage;
	u32 special_damage;
	u8 counter_target;
	u8 mirrorcoat_target;
	u16 fieldE;
};

extern struct protect_struct protect_structs[4];

struct flags_ability
{
	u32 flag1_flashfire : 1;
};

struct ability_flags
{
	struct flags_ability flags_ability[4];
};

struct tai_state
{
	u8 phase;
	u8 moveset_index;
	u16 curr_move;
	s8 score[4];
	u32 var;
	u32 scripts_to_run;
	u8 move_state_flags;
	u8 curr_script;
};

struct used_moves
{
	u16 moves[4];
	u16 unkown[4];
};

struct battle_history
{
	struct used_moves used_moves[4];
	u8 ability[4];
	u8 item[4];
};

struct b_resources_secretbaseinfo
{
	u8 field0;
	u8 field1;
	u8 trainer_name[6];
};

struct battle_stack
{
	void* stack_data[8];
	u8 stack_height;
	u8 undefined[3];
};

struct lvlup_stats
{
	u16 hp;
	u16 atk;
	u16 def;
	u16 spd;
	u16 spatk;
	u16 spdef;
	u16 field_C;
};

struct b_resources_table
{
	struct b_resources_secretbaseinfo* secretbase_opponent;
	struct ability_flags* ability_flags_ptr;
	struct battle_stack* battlescript_stack;
	struct battle_stack* callback_stack;
	struct lvlup_stats* before_lvl_up;
	struct tai_state* tai_state;
	struct battle_history* battle_history;
	void* taiscripts_stack;
};

extern struct b_resources_table* battle_resources;

struct b_communication
{
	u8 field0;
	u8 field1;
	u8 field2;
	u8 move_effect;
	u8 field4;
	u8 multistring_chooser;
	u8 field6;
	u8 is_message_displayed;
};

extern struct b_communication battle_communication_struct;

struct move_outcome
{
	u8 missed : 1;
	u8 super_effective : 1;
	u8 not_very_effective : 1;
	u8 not_affected : 1;
	u8 one_hit_ko : 1;
	u8 failed : 1;
	u8 endured : 1;
	u8 hanged_on_using_item : 1;
	u8 sturdied : 1;
	u8 explosion_stop : 1;
};

extern struct move_outcome move_outcome;

//temp
u32 hitmarker;
#define HITMARKER_NO_ANIMATIONS 0x80
#define HITMARKER_IGNORE_SUBSTITUTE 0x100
#define HITMARKER_NO_ATTACKSTRING 0x200 //used in dual foe and user defrosting moves
#define HITMARKER_ATTACKSTRING_PRINTED 0x400
#define HITMARKER_NO_PPDEDUCT 0x800
#define HITMARKER_PURSUIT_TRAP 0x1000
#define HITMAKRER_IGNORE_SAFEGUARD 0x2000
#define HITMARKER_FLEE 0x8000
#define HITMARKER_IGNORE_ON_AIR 0x10000
#define HITMERKER_IGNORE_UNDERGROUND 0x20000
#define HITMARKER_IGNORE_UNDERWATER 0x40000
#define HITMARKER_IMMOBILE_DUE_TO_STATUS 0x80000
#define HITMARKER_OBEYS 0x2000000
#define HITMARKER_FAINTED(bank) (bits_table[bank]>>0x1C)

struct side_affecting_hword
{
	u16 reflect_on : 1;
	u16 light_screen_on : 1;
	u16 unkown1 : 2;
	u16 spikes_on : 1;
	u16 safeguard_on : 1;
	u16 unkown2 : 2;
	u16 mist_on : 1;
	u16 spikes_damage_done : 1;
};

extern struct side_affecting_hword side_affecting_halfword[2];

struct prop_flags
{
	u8 makes_contact : 1;//1
	u8 affected_by_protect : 1;//2
	u8 affected_by_magic_coat : 1;//4
	u8 affected_by_snatch : 1;//8
	u8 affected_by_mirrormove :1;//x10
	u8 affected_by_kingsrock :1;//x20
	u8 raised_crit_ratio :1;//x40
	u8 unused_bit : 1;//x80
};

union move_flags
{
	u8 int_flag;
	struct prop_flags flags;
};

struct move_info
{
	u8 script_id;
	u8 base_power;
	u8 type;
	u8 accuracy;
	u8 pp;
	u8 effect_chance;
	u8 target;
	s8 priority;
	union move_flags move_flags;
	u8 arg1;
	u8 split;
	u8 arg2;
};

//extern struct move_info move_info;

struct fraction_buff2
{
	u8 numerator;
	u8 denumenator;
	u16 padding;
};

extern const struct fraction_buff2 fraction_stat_buffs2[0xC];

struct side_timer
{
	u8 reflect_timer;
	u8 reflect_bank;
	u8 lightscreen_timer;
	u8 lightscreen_bank;
	u8 mist_timer;
	u8 mist_bank;
	u8 safeguard_timer;
	u8 safeguard_bank;
	u8 followme_timer;
	u8 followme_target;
	u8 spikes_amount;
	u8 fieldB;
};

extern struct side_timer side_timers[2];

struct battleflags
{
	u32 double_battle : 1; //1
	u32 link : 1; //2
	u32 battle : 1; //4
	u32 trainer : 1; //8
	u32 save_birch : 1; //0x10
	u32 flagx20 : 1; //0x20
	u32 player_partner : 1; //0x40
	u32 safari : 1; //0x80
	u32 frontier_general : 1; //0x100
	u32 wally : 1; //0x200
	u32 roaming : 1; //0x400
	u32 flagx800 : 1; //0x800
	u32 flagx1000 : 1; //0x1000
	u32 legendary : 1; //0x2000
	u32 regis : 1; //0x4000
	u32 multibattle : 1; //0x8000
	u32 battle_dome : 1; //0x10 000
	u32 battle_palace : 1; //0x20 000
	u32 battle_arena : 1; //0x40 000
	u32 battle_factory : 1; //0x80 000
	u32 flag_x100000 : 1; //0x100 000
	u32 battle_pyramid : 1; //0x200 000
	u32 player_ingame_partner : 1; //0x400 000
	u32 flag_x800000 : 1; //0x800 000
	u32 recorded_battle : 1;// 0x1 000 000
	u32 flag_x2000000 : 1; //0x2 000 000
	u32 flag_x4000000 : 1; //0x4 000 000
	u32 secret_base : 1; //0x8 000 000
	u32 groudon : 1; //0x10 000 000
	u32 kyorge : 1; //0x20 000 000
	u32 rayquaza : 1; //0x40 000 000
	u32 flag_x80000000 : 1; //0x80 000 000
};

extern struct battleflags battle_flags;

struct pokemon
{
	u32 PID;
	u32 OTID;
	char name[10];
	char language;
	char badegg;
	char OT_name[7];
	char markings;            // only the lowest 4 bits are used
	u16 checksum;
	u16 padding_maybe;        //get_attr 6a674
	u16 spieces;
	u16 item;
	u32 exp;
	char pointup;
	//char	PointUp1 : 2;	// @0x42,
	//char	PointUp2 : 2;	// @0x44,
	//char	PointUp3 : 2;	// @0x46,
	char bIntimate : 8;
	u16 unk0;
	u16 moves[4];        // ID of the Skill
	char movePP[4];        // Skill Points
	char evs_hp;
	char evs_atk;
	char evs_def;
	char evs_spd;
	char evs_spatk;
	char evs_spdef;
	char beauty[0x06];        // 帅气 美丽 可爱 聪明 强壮 光滑
	u32 virus : 4;        // @0x00, if any bit is set, ポケルスがかかる
	u32 blackpoint : 4;        // @0x04, if any bit is set, 黑点
	u32 catchplace : 8;
	u32 catchlevel : 7;
	u32 gameversion : 4;    // @0x17, game version (sapphire=1, ruby=2, emerald=3, fire=4, leaf=5)
	u32 ball : 4;        // @0x1B, Poke-Ball type (Write twice, why?)
	u32 unk1 : 1;            // @0x1F, 0
	u32 iv_hp : 5;
	u32 iv_atk : 5;
	u32 iv_def : 5;
	u32 iv_spd : 5;
	u32 iv_spatk : 5;
	u32 iv_spdef : 5;
	u32 isEgg : 1;
	u32 ability : 1;
	u32 ribbon0 : 3;
	u32 ribbon1 : 3;
	u32 ribbon2 : 3;
	u32 ribbon3 : 3;
	u32 ribbon4 : 3;
	u32 ribbon5 : 12;
	u32 unk2 : 4;
	u32 obedience : 1;
	// only for active (in group) pokemons
	char status;        // bit0-2:异常状态,
	char unkonw[3];
	char level;
	char pokerus;        // this is always 'FF'
	u16 current_hp;
	u16 total_hp;
	u16 attack;
	u16 defense;
	u16 speed;
	u16 sp_attack;
	u16 sp_defense;
};

extern struct pokemon party_opponent[6];
extern struct pokemon party_player[6];

struct battle_buffer
{
	u8 command_id;
	u8 args[511];
};

extern struct battle_buffer battle_bufferA[4];
extern struct battle_buffer battle_bufferB[4];

struct task
{ //8+32=40
	void* function;
	u8 id;
	u8 previous;
	u8 next;
	u8 priority;
	u16 array[16];
};

extern struct task tasks[16];

struct frame
{
	u16 data;
	u16 duration;
};

struct rotscale_frame
{
	u16 scale_delta_x;
	u16 scale_delta_y;
	u8 rot_delta;
	u8 duration;
	u16 field_6;
};

struct sprite
{
	u8 y;
	u8 flags1;
	u16 x_and_flag2;
	u16 attr2;//4~7位是调色板
	u16 rotscaleinfo;
};

struct coords16
{
	u16 x;
	u16 y;
};

struct coords8
{
	u8 x;
	u8 y;
};

struct object;
typedef void (* object_callback)(struct object*);

struct graphic{
	void* img;
	u32 size;
};

struct animate_template
{
	u16 tiles_tag;
	u16 pal_tag;
	struct sprite* oam;
	struct frame** animation;
	struct graphic* graphics;
	struct rotscale_frame** rotscale;
	object_callback callback;
};

struct object//68
{
	struct sprite final_oam;//0
	struct frame** animation_table;//8
	void* gfx_table;//12
	void* rotscale_table;//16
	struct animate_template* animate_template;//20
	u32 field_18;//24
	void* callback;//28
	struct coords16 pos1;//32
	struct coords16 pos2;//36
	struct coords8 pos_neg_center;//40
	u8 anim_number;//42
	u8 anim_frame;//43
	u8 anim_delay_countdown;//44
	u8 anim_unkown_counter;//45
	u16 array[8];//46
	u8 in_use : 1;//62
	u8 flag2 : 1;
	u8 invisible : 1;
	u8 flags : 5;
	u8 bitfield2;//63
	u16 anim_data_offset;//64
	u8 field_42;//66
	u8 y_height_related;//67
};

struct SpriteTiles
{
	const void* image;
	u16 size;
	u16 tag;
};

struct SpritePalette
{
	const void* data;
	u16 tag;
};

extern struct object objects[64];

//Pokemon Basestats table

struct poke_basestats
{
	u8 base_hp;
	u8 base_atk;
	u8 base_def;
	u8 base_spd;
	u8 base_spatk;
	u8 base_spdef;
	u8 type1;
	u8 type2;
	u8 catch_rate;
	u8 exp_yield;
	u16 evs_hp : 2;
	u16 evs_atk : 2;
	u16 evs_def : 2;
	u16 evs_spd : 2;
	u16 evs_spatk : 2;
	u16 evs_spdef : 2;
	u16 unused : 4;
	u16 item1;
	u16 item2;
	u8 gender_ratio;
	u8 hatching;
	u8 friendship;
	u8 exp_curve;
	u8 egg_group1;
	u8 egg_group2;
	u8 ability1;
	u8 ability2;
	u8 safari_flee_rate;
	u8 dex_colour;
	u8 padding1;
	u8 padding2;
};

extern const struct poke_basestats (* basestat_table)[ALL_POKES];

struct battle_info_struct
{
	u8 user_team_faint_counter;
	u8 ai_team_faint_counter;
	u8 field2;
	u8 field3;
	u8 field4;
	u8 flags;
	u16 user_team_species;
	u8 pokemon_name_string_1[11];
	u8 battle_turn_counter;
	u8 pokemon_name_string_2[11]; //0x14
	u8 pad; //0x1F
	u16 logged; //0x20
	u16 user_team_move; //0x22
	u16 ai_team_move; //0x24
	u16 ai_team_species; //0x26
	u16 caught_species; //0x28
	u8 caught_name[10];
	u8 catch_attempts[11];
};

extern struct battle_info_struct battle_trace;

//Item Table

struct item_struct
{
	u8 name[14];
	u16 index;
	u16 price;
	u8 held_effect;
	u8 held_effect_quality;
	void* desc_pointer;
	u16 mystery_value;
	u8 pocket_no;
	u8 type_of_item;
	void* field_usage_code;
	u32 battle_usage;
	void* battle_usage_code;
	u32 extra_param;
};

extern const struct item_struct (* item_table)[ALL_ITEMS];

//Evolution table

struct evolution_sub
{
	u8 method;
	u8 filler;
	u16 paramter;
	u16 poke;
	u8 pad1;
	u8 pad2;
};

extern const struct evolution_sub (* evo_table)[ALL_POKES][NUM_OF_EVOS];

struct b_graphics_loc
{
	void* beg_decompressed_sprites; //ptr to the decompressed sprite of the first pokemon
	void* decompressed_sprite[4]; //four pointers to decompressed sprites
	struct animate_template sprite_template[4];
	struct graphic graphics[4][4];
};

struct b_species_info
{
	u16 invisible : 1; //0x1
	u16 flag_x2 : 1; //0x2
	u16 substitute : 1; //0x4
	u16 flag_x8 : 1; //0x8
	u16 HPnumbers : 1; //0x10 not bar but raw numbers
	//rest seems unused ?
	u16 flag_x20 : 1; //0x20
	u16 flag_x40 : 1; //0x40
	u16 flag_x80 : 1; //0x80
	u16 flag_x100 : 1; //0x100
	u16 flag_x200 : 1; //0x200
	u16 flag_x400 : 1; //0x400
	u16 flag_x800 : 1; //0x800
	u16 pal_change : 1; //0x1000
	u16 transformed_species;
};

struct anim_info
{
	u16 arg;
};

struct b_graphics_data
{
	struct b_species_info (* species_info)[4]; //ptr to an array of b_species_info
	void* field4;
	struct anim_info* anims_info;
};

struct battle_graphics_struct
{
	struct b_graphics_data* graphics_data;
	struct b_graphics_loc* graphics_loc;
};

extern struct battle_graphics_struct battle_graphics;

struct sprite_poke
{
	void* sprite;
	u16 unkown;
	u16 species;
};

extern const struct sprite_poke (* front_sprites)[ALL_POKES];
extern const struct sprite_poke (* back_sprites)[ALL_POKES];

extern const u8 (* poke_name_table)[ALL_POKES][11];

struct button
{
	u16 A : 1;
	u16 B : 1;
	u16 SELECT : 1;
	u16 START : 1;
	u16 RIGHT : 1;
	u16 LEFT : 1;
	u16 UP : 1;
	u16 DOWN : 1;
	u16 R : 1;
	u16 L : 1;
};

enum buttons{
	A = 1,
	B = 0x2,
	SELECT = 0x4,
	START = 0x8,
	RIGHT = 0x10,
	LEFT = 0x20,
	UP = 0x40,
	DOWN = 0x80,
	R = 0x100,
	L = 0x200
};

struct superstate //0x030022C0
{
	void* callback1;
	void* callback2;
	void* callback_backup;
	void* vblank_callback;
	void* hblank_callback;
	void* field14;
	void* field18;
	u32 bits_to_wait_for;
	u32 some_timer;
	u32 field24;
	u16 buttons0;
	u16 buttons1;
	u16 buttons2;
	struct button pressed_buttons;//0x030022ee
};

extern struct superstate super;

struct warp
{
	u8 map_bank;
	u8 map_no;
	s16 x_coords;
	s16 y_coords;
	u16 field6;
};

struct owned_items
{
	u16 itemID;
	u16 amount;
};

struct npc_state
{
	u8 field0; //0
	u8 field1; //1
	u8 field2; //2
	u8 field3; //3
	u8 oam_id; //4
	u8 spriteID; //5
	u8 movement_type;// 6
	u8 walking_type; //7
	u8 localID; //8
	u8 map_no; //9
	u8 map_bank; //xA
	u8 height; //xB
	u32 field_C; //xC
	u16 pos_x; //x10
	u16 pox_y;
	u16 pos_x_plus7;
	u16 pos_y_plus7;
	u8 walking_direction;
	u8 field_19;
	u8 field_1A;
	u8 field_1B;
	u8 field_1C;
	u8 plantID;
	u8 field_1E;
	u8 field_1F;
	u8 field_20;
	u8 field_21;
	u8 field_22;
	u8 field_23;
};

struct rom_npc
{
	u8 localID; //0
	u8 spriteID; //1
	u16 field2; //2
	s16 x_pos; //4
	s16 y_pos; //6
	u8 height; //8
	u8 behaviour;//9
	u16 behaviour_property;// xA
	u8 is_trainer; //xC
	u8 fieldD; //xD
	u16 radius_plantID; //xE
	void* script; //x10
	u16 flag; //x14
	u16 field16; //x16
};

struct planted_berry
{
	u8 berryID;
	u8 state;
	u16 minutes_stage;
	u8 yield;
	u8 watered;
	u8 field6;
	u8 field7;
};

struct secret_base
{
	u8 baseID; //0
	u8 owner_state; //1
	u8 owner_name[7]; //2
	u8 trainerID[4]; //9
	u8 font; //xD
	u16 fieldE; //xE
	u8 enters; //x10
	u8 field11; //x11
	u8 used_decorationsID[16]; //x12
	u8 decoration_positions[16];
	u8 field32;
	u8 field33;
	u32 PiD[6];
	u16 moves[6][4];
	u16 species[6];
	u16 held_items[6];
	u8 levels[6];
	u8 evs[6];
};

struct pokeblock
{
	u8 index;
	u8 spicy_lvl;
	u8 dry_lvl;
	u8 sweet_lvl;
	u8 bitter_lvl;
	u8 sour_lvl;
	u8 feel;
	u8 unkown;
};

struct saveblock1
{
	s16 x_coords;
	s16 y_coords;
	u8 map_bank;
	u8 map_no;
	u8 field_6[14];
	struct warp empty_warp;
	struct warp healing_spot;
	struct warp escape_place;
	u16 map_song;
	u8 ov_weather;
	u8 weather_specifier;
	u8 flash_on_map;
	u8 field_31;
	u16 map_footer_no;
	u8 field_34[496];
	u8 field_224[15];
	u8 field_233;
	u8 poke_quantity;
	u8 alignment_padding[3];
	struct pokemon player_party[6];
	u32 money;
	u16 coints;
	u16 item_on_select;
	struct owned_items PC_items[50];
	struct owned_items items_pocket[30];
	struct owned_items key_items_pocket[30];
	struct owned_items balls_pocket[16];
	struct owned_items tms_pocket[64];
	struct owned_items berries_pocket[46];
	struct pokeblock pokeblocks[40];
	u8 seenflags_1[52];
	u16 berry_blending_results[3];
	u16 field_9C2[3];
	u16 step_counter_to_xFF;
	u8 pokenav_matchcall[64];
	u8 field_A0A[38];
	struct npc_state npc_states_rom[16];
	struct rom_npc map_npcs[64];
	u8 flags[300];
	u16 vars[256];
	u32 encrypted_counters[64];
	struct planted_berry planted_berries[128];
	struct secret_base secret_bases[20];
	u8 field_271C[5128];
	u8 seenflags_2[52];
};

extern struct saveblock1* sav1;//0x3d88 sav3=0x83D0

struct saveblock2
{
	u8 name[8];
	u8 gender;
	u8 field_9;
	u8 TiD_1;
	u8 TiD_2;
	u8 TiD_3;
	u8 TiD_4;
	u16 hours_played;
	u8 mintues_played;
	u8 seconds_played;
	u8 frames_played;
	u8 buttons_style;
	u8 txt_speed_frame;
	u8 battle_scene_style_sound;
	u8 field16;
	u8 field17;
	u8 dex_order;
	u8 dex_mode;
	u8 national_dex;
	u8 field1B;
	u32 unown_PiD;
	u32 spinda_PiD;
	u8 field24[4];
	u8 caught_flags[52];
	u8 seen_flags[52];
};

extern struct saveblock2* sav2;//0xF2C

struct battle_record_pbs
{
	u8 action[664];
};

extern struct battle_record_pbs battle_record[4];

struct stat_fractions
{
	u8 dividend;
	u8 divisor;
};

struct battle_link
{
	u8 field_0[8];
	u8 trainer_name[8];
	u8 field_10[8];
	u16 bank_id;
	u16 field_1A;
};

extern struct battle_link battle_link_pbs[4];

struct trainer_data
{
	u8 custom_moves : 1;
	u8 custom_item : 1;
	u8 trainer_class;
	u8 music : 7;
	u8 gender : 1;
	u8 sprite;
	u8 name[10];
	u8 field_E;
	u16 items[4];
	u8 flags[4];
	u32 ai_scripts;
	u8 poke_number;
	u8 padd[3];
	struct poke_trainer_data* poke_data;
};

extern const struct trainer_data (* trainer_table)[864];

struct fadescreen_exec
{
	u16 BLDCNT;
	u8 field2;
	u8 field3;
	u16 BLDY;
	u8 field6;
	u8 flags : 7;
	u8 is_fading : 1;
};

extern struct fadescreen_exec fadescreen_info;

struct mapheader
{
	void* footer;
	void* events;
	void* scripts;
	void* connections;
	u16 music_id;
	u16 footer_id;
	u8 name;
	u8 light;
	u8 weather;
	u8 type;
	u8 field_18;
	u8 can_dig;
	u8 show_name;
	u8 battletype;
};

extern struct mapheader curr_mapheader;

struct b_background_info
{
	const void* tileset;
	const void* tilemap;
	const void* entry_tileset;
	const void* entry_tilemap;
	const void* pal;
};

struct move_background_info
{
	const void* tileset;
	const void* tilemap;
	const void* pal;
};

struct img_size
{
	void* img;
	u32 size;
};

struct trainerhrow_position
{
	u8 pos1;
	u8 pos2;
	u16 padd;
};

#endif /* B_STRUCTS */
