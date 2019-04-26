#ifndef NEW_STRUCT
#define NEW_STRUCT

//JeremyZ
#define NIGHT_FIRST_HOUR    18
#define NIGHT_LAST_HOUR     5

struct real_time_clock_hex{
    u16 field0;
    u8 hour;
    u8 minute;
    u8 second;
};

extern struct real_time_clock_hex rtc_hex;

struct bank_affecting{
    u8 embargo : 3;
    u8 electrify : 1;
    u8 telekinesis: 3;
    u8 magnet_rise : 3;
    u8 heal_block : 3;
    u8 aqua_ring : 1;
    u8 powder : 1;
    u8 smacked_down : 1;
    u8 quashed : 1;
    u8 just_switched_in : 1;
    u8 miracle_eyed : 1;
    u8 eaten_berry : 1;
    u8 cherrim_form : 1;
    u8 gastro_acided : 1;
    u8 spiky_shield : 1;
    u8 kings_shield : 1;
    u8 baneful_bunker : 1;
    u8 sky_drop_attacker : 1;
    u8 sky_drop_target : 1;
    u8 me_first : 1;
    u8 weakness2 : 1;
    u8 entry_message : 1;
    u8 powertrick : 1;
    u8 kingsshield_damage : 1;
    u8 spikyshield_damage : 1;
    u8 banefulbunker_damage : 1;
    u8 grassyterrain_heal : 1;
    u8 slowstart_duration : 3;
    u8 aegislash_form : 2; //0 = not aegi, 1 = defensive, 2 = attacking
    u8 killer_bank : 2;
    u8 same_move_used : 3;
    u8 move_failed : 1;
    u8 type3 : 5;
    u8 stat_lowered : 1;
    u8 roost : 3;
    u8 usedmoves : 4;
    s8 stockpile_def_changes;
    s8 stockpile_sp_def_changes;
    u8 autonomize_uses;
    u8 lastmove_type;
    u16 wish_hp;
    u32 transform_tid;
    u8 illusion_on : 1;
    u8 illusion_hit : 1;
    u8 illusion_ball : 6;
    u8 illusion_nick[11];
    u8 skips_turn : 1;
    u8 caught : 1;
    u8 always_crit : 2;
    u8 itemheal : 1;
	u8 throatchop_timer : 2; //JeremyZ	
	u8 rage_powder : 1; //JeremyZ
	u8 beak_blast_charge : 2; //JeremyZ
	u8 shell_trap_charge : 2; //JeremyZ
	u8 lastmove_fail : 1; //JeremyZ
	u8 head_blown : 1; //JeremyZ
	u8 stockpile_counter : 2; //JeremyZ
	u8 move_worked_thisturn : 1; //JeremyZ
};

struct side_affecting{
    u8 sticky_web : 1;
    u8 sticky_web_done : 1;
    u8 toxic_spikes_psn : 1;
    u8 toxic_spikes_badpsn : 1;
    u8 toxic_spikes_done : 1;
    u8 stealthrock : 1;
    u8 stealthrock_done : 1;
    u8 lucky_chant : 3;
    u8 lucky_chant_bank : 2;
    u8 tailwind : 3;
    u8 tailwind_bank : 2;
    u8 wide_guard : 1;
    u8 quick_guard : 1;
    u8 crafty_shield : 1;
    u8 swamp_spd_reduce : 3;
    u8 sea_of_fire : 3;
    u8 rainbow : 3;
    u8 mat_block : 1;
    u8 lunardance : 1;
    u8 lunardance_done : 1;
    u8 ally_fainted_last_turn : 2;
    u8 pledge_effect : 2; //1 for grass, 2 for fire , 3 for water
    u8 aurora_veil : 4;
};

struct field_affecting{
    u32 trick_room : 3; //0-2
    u32 wonder_room : 3; //3-5
    u32 magic_room : 3; //6-8
    u32 grassy_terrain : 4; //9-12
    u32 electic_terrain : 4; //13-16
    u32 misty_terrain : 4; //17-20
    u32 psychic_terrain : 4; //21-24
    u32 ion_deluge : 3; //25-27
    u32 gravity : 3; //28-30
    u32 round_chosen : 1; //31
    u8 watersport : 3; //0-2
    u8 mudsport : 3; //3-5
    u8 fairy_lock : 2; //6-7
    u8 echo_voice_counter : 3; //0-3
};

struct various{
    u8 active_bank : 2;
    u8 cmd49_safeattacker_bank: 2;
    u8 inverse_battle : 1;
    u8 fishing_battle : 1;
    u8 magicbounce : 1;
    u8 stormdrain : 1;
    u16 var1;
    u16 var2;
    u16 recently_used_item;
    u16 previous_move;
    u16 accumulated_damage;
    u8 move_primary_effect;
    u8 parental_bond_mode: 2;
    u8 life_orbed : 1;
    u8 sheerforce_bonus : 1;
    u8 ate_bonus : 1;
    u8 gem_boost : 1;
    u8 happyhour_bonus : 1;
    u8 berry_damage_redux : 1;
    u8 trigger_symbiosis: 1;
    u8 switch_in_cos_switch : 1; //and not because a poke fainted or it is the first one
    u8 protean_msg : 1;
    u8 recorded_mega : 1;
    u8 sent_in_player : 6;
    u8 returns_item : 6;
    u8 gravity_levitate : 1;
    #if ITEM_SWAP == false
    u16 original_held_item[6];
    u8 returns_swap : 6;
    #endif // ITEMS_SWAP
    u8* trainer_slide_msg;
    u8 trainer_msg_on_switch_in_done : 1;
    u8 trainer_msg_on_low_health_done : 1;
    u8 trainer_msg_after_first_poke_done : 1;
    u8 dont_play_move_anim : 1;
    u8 dont_play_stat_anim : 1;
    u8 bust_mimikyu : 1;
    u8 original_dancer : 3;
    u8 secondary_dancer : 3;
    u8 instruct_phase : 1;
};

#define PBOND_PARENT 2
#define PBOND_CHILD 1
#define PBOND_DONT_SET 3

struct mega_related
{
    u32 user_trigger: 2; // 0x0 for not set, 0x1 for z, 0x2 for ultra burst, 0x3 for mega (stone & wish)
    u32 ally_trigger: 2;
    u32 evo_happened_pbs: 4;
    u32 party_mega_check: 6;
    u32 ai_party_mega_check: 6;
    u32 trigger_id : 8;
    u8 indicator_id_pbs[4];
    u8 link_indicator[4];
    u16 z_happened_pbs: 4;
    u16 party_z_check: 6;
    u16 ai_party_z_check: 6;
};

struct tai_related{
    u16 saved_species[4];
    u16 saved_item[4];
    u8 saved_ability[4];
    u16 var2;
};

struct party_bits{
    u8 battle_bond_user: 6;
    u8 battle_bond_ai: 6;
    u8 is_base_z50_user: 6;
    u8 is_base_z50_ai: 6;
    u8 eaten_berry_player : 6;
    u8 eaten_berry_opponent : 6;
};

#define MOVEEFFECT_SLP      0x7
#define MOVEEFFECT_PSN      0x8
#define MOVEEFFECT_BRN      0x10
#define MOVEEFFECT_FRZ      0x20
#define MOVEEFFECT_PRLZ     0x40
#define MOVEEFFECT_TOXIC    0x80
#define MOVEEFFECT_CONFUSE  0x100
#define MOVEEFFECT_FLINCH   0x200
#define MOVEEFFECT_STATCHANGE   0x400
#define MOVEEFFECT_MULTIPLESTATS   0x800
#define MOVEEFFECT_ALL (MOVEEFFECT_SLP | MOVEEFFECT_PSN | MOVEEFFECT_BRN | MOVEEFFECT_FRZ | MOVEEFFECT_PRLZ | MOVEEFFECT_TOXIC | MOVEEFFECT_CONFUSE | MOVEEFFECT_FLINCH | MOVEEFFECT_STATCHANGE | MOVEEFFECT_MULTIPLESTATS)

#define MOVEEFFECT_AFFECTSUSER 0x4000
#define MOVEEFFECT_ONECALC  0x8000

struct move_effects{
    u16 effect1;
    u16 synchro_effect[4];
};

struct new_battle_struct{
    struct bank_affecting bank_affecting[4];
    struct side_affecting side_affecting[2];
    struct field_affecting field_affecting;
    struct move_effects move_effect;
    struct various various;
    struct mega_related mega_related;
    struct tai_related trainer_AI;
    struct party_bits party_bit;
};

extern struct new_battle_struct* new_battlestruct;

#endif /* NEW_STRUCT */
