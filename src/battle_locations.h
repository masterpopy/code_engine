#ifndef B_LOCATIONS
#define B_LOCATIONS

//#include "types.h"

extern u16 battle_turn_random_no;
extern u8 last_used_ability;
extern u16 last_used_item;
extern u8 banks_by_side[4];
/*extern u8 bank_attacker;
extern u8 bank_target;
extern u8 bank_partner_atk;
extern u8 bank_partner_def;*/
extern u8 bank_attacker0[4];
#define bank_attacker bank_attacker0[0]
#define bank_target bank_attacker0[1]
#define bank_partner_atk bank_attacker0[2]
#define bank_partner_def bank_attacker0[3]

extern u8 crit_loc;
extern u8 abilities_by_banks[4];
extern u16 curr_move_BP;
extern u16 current_move;
extern u16 last_used_move;
extern u16 last_used_moves[4];
extern s32 damage_loc;
extern u8 no_of_all_banks;
extern u8 battle_text_buff1[0x10];
extern u8 battle_text_buff2[0x10];
extern u8 battle_text_buff3[0x10];
extern u8 displayed_string_in_battle[0x100];
extern u8 displayed_string_ov[1000];
extern u8 active_bank;
extern void* battlescripts_curr_instruction;
extern void* move_anim_cursor;
extern u8 multihit_counter;
extern u16 chosen_move_by_banks[4];
extern u16 dynamic_base_power;
extern u8 animation_bank_attacker;
//extern u8 animation_bank_target;
#define  animation_bank_target ((u8*)&animation_bank_attacker)[1]
extern u8 turn_order[4];
extern u16 battle_team_id_by_side[4];
extern u16 sketchable_move_used[4];
extern u16 calling_move_used[4];
extern u16 current_move_used[4];
extern u8 attacked_by[4];
extern u8 another_active_bank;
extern u8 absent_bank_flags;
extern u8 battle_outcome;
extern u8 current_move_position;
extern u8 current_move_turn;
extern u16 move_hit_with_pbs[4];
extern u16 move_type_hit_with_pbs[4];
extern u16 locked_move[4];
extern u16 payday_money;
extern s32 hp_dealt;
extern u8 battle_state_mode;
extern u8 battle_state_mode_first_assigned;
extern const u8 terrain_to_type_table[10];
extern u8 battle_env_bg;
extern u8 battle_chosen_bg;
extern u32 taken_damage[4];
extern u8 hurt_by[4];
extern u8 slot_in_learnset_table;
extern u16 move_to_learn;
extern u8* tai_current_instruction;
extern u8 tai_bank;
extern u32 battle_execution_buffer;
extern const u16 some_strings_table[4];
extern const u16 protect_chance_table[4];
extern void *b_c;
extern u8 menu_choice_pbs[4];
extern u8 objID_pbs_moveanimations[4];
extern u8 anim_execution_buffer;
extern u16 var_8015_trainer_opponent_A;
extern u16 trainer_opponent_B;
extern u16 partner_trainer;
extern void* tasks_for_banks[4];
extern u8 graphical_elements_pbs[4];
extern void *b_x[4];
extern u8 healthbox_obj_id_pbs[4];
extern u8 move_selection_chosen_target_pbs[4];
extern u8 moves_to_choose_pbs[4];
extern u8 move_selection_cursor_pbs[4];
extern const u32 bits_table[32];
extern u32 PiD_pbs[4];
extern u8 decompression_buffer[0xF80];

extern const u8 nick_male_sign[5];
extern const u8 nick_female_sign[5];
extern const u8 nick_genderless_sign[4];
extern const u8 text_Wild_[6];
extern const u8 text_Foe_[5];
extern const u8 text_Foe[4];
extern const u8 text_Ally[5];
extern const u8 text_Ally_[6];
extern const u8 text_ENIGMA_BERRY[13];
extern const u8 text__BERRY[7];
extern const u8 text_BOX_IS_FULL[19];
extern const u8 text_empty_string_00[1];
extern const u8 text_poke_used_move[11];
extern const u8 text_exclamation_mark_00[2];

extern const u8 text_lower[];
extern const u8 text_sharply_[];
extern const u8 text_rose[];
extern const u8 text_harshly_[];
extern const u8 text_fell[];

extern const u8 text_wally_b_start[];
extern const u8 text_legendary_b_start[];
extern const u8 text_wild_double_b_start[];
extern const u8 text_wild_b_start[];
extern const u8 text_trainer_multi_b_start[];
extern const u8 text_trainer_b_start[];
extern const u8 text_fcx10_got_away_safely[];
extern const u8 text_fcx10_one_fled[];
extern const u8 text_fcx10_two_fled[];

extern const u8 text_player_defeated_fdx20[];
extern const u8 text_player_beat_fdx20_and_fdx21[];
extern const u8 text_player_lost_to_fdx20[];
extern const u8 text_player_lost_to_fdx20_and_fdx21[];
extern const u8 text_player_battled_to_draw_against_fdx20[];
extern const u8 text_player_battled_to_draw_against_fdx20_and_fdx21[];

extern const u8 text_opponent_sendout_multi[];
extern const u8 text_opponent_sendout_playerpartner[];
extern const u8 text_opponent_sendout_link[];
extern const u8 text_opponent_sendouts_two[];
extern const u8 text_opponent_single_sendout_link[];
extern const u8 text_opponent_sendout_single[];

extern const u8 text_thatsenough_come_back[];
extern const u8 text_xfd0_come_back[];
extern const u8 text_ok_come_back[];
extern const u8 text_good_come_back[];
extern const u8 text_fdx20_withdrew[];
extern const u8 text_fdx22_withdrew[];
extern const u8 text_trainerA_withdrew[];

//extern const u8 text_go_fdx0[];
extern const u8 text_do_it_fdx0[];
extern const u8 text_your_foe_is_weak_getem_fdx0[];
extern const u8 text_go_for_it_fdx0[];
extern const u8 text_fdx22_sent_out[];
extern const u8 text_fdx20_sent_out[];
extern const u8 text_trainerB_sent_out[];
extern const u8 text_trainerA_sent_out[];

//extern const u8 text_GO_xfd5[];
extern const u8 text_player_sendout_ingame_partner[];
extern const u8 text_player_sendout_partner[];
extern const u8 text_GO_xfd5_and_xfd7[];

enum CastformForm{
    CastformNormal, //0
    CastformFire, //1
    CastformWater, //2
    CastformIce, //3
    CastformNoChange = 0xFF,
};

enum CherrimForm{
    CherrimNormal, //0
    CherrimSunny, //1
    CherrimNoChange = 0xFF,
};

extern enum CastformForm castform_form[4];
extern u8 viewing_recorded_battle;
extern u16 no_of_recorded_bytes[4];
extern u16 var_800D_lastresult;
extern u16 var_800E_last_used_item;
extern u16 randomly_chosen_move;
extern s16 BG1Y_battle;
extern s16 bg2X_battle;
extern s16 bg2Y_battle;
extern u8 battle_some_link_id;
extern u8 script_text_buffer1[0x100];
extern u8 script_text_buffer2[0x100];
extern u8 script_text_buffer3[0x100];
extern const u8 text_someones[10];
extern const u8 text_LANETTES[10];
extern const u8 text_yesno_battle[15];
extern u8 sent_pokes_to_opponent[2];
extern u16 expshare_exp;
extern u8 bank_in_menu;
extern u8 old_curr_full_box_id;
extern s16 battle_BG3_X;
extern u8 leveled_up_in_battle;
extern u16 (*buffer_moves)[2];
extern void* battle_executed_routine;
extern const u8* opponentwon_text;
extern u16 anim_arguments[8];
extern u16 var_8004;
extern u16 var_8005;
extern u16 var_8006;
extern u16 var_8007;
extern u8 which_spotted_trainer;
extern u8 partner_sprite;
extern u8 player_backsprite;

extern const u32 battletextbox_tileset[];
extern const u32 battletextbox_tilemap[];
extern const struct palette battletextbox_pal[];
extern const struct palette bg_frontier_pal[];
extern const struct palette bg_groudon_pal[];
extern const struct palette bg_kyorge_pal[];
extern const struct palette bg_gym_pal[];
extern const struct palette bg_leader_pal[];
extern const struct palette bg_teamaqua_pal[];
extern const struct palette bg_teammagma_pal[];
extern const struct palette bg_elitefour1_pal[];
extern const struct palette bg_elitefour2_pal[];
extern const struct palette bg_elitefour3_pal[];
extern const struct palette bg_elitefour4_pal[];
extern const struct palette bg_champion_pal[];
extern const struct palette bg_rayquaza_pal[];
extern const u32 bg_rayquaza_tileset[];
extern const u32 bg_rayquaza_tilemap[];
extern const u32 bg_boss_tileset[];
extern const u32 bg_boss_tilemap[];
extern const u32 entry_bg_ray_tilemap[];
extern const u32 entry_bg_ray_tileset[];

extern const u32 bg_grass_tileset[];
extern const u32 bg_longgrass_tileset[];
extern const u32 bg_sand_tileset[];
extern const u32 bg_underwater_tileset[];
extern const u32 bg_water_tileset[];
extern const u32 bg_pond_tileset[];
extern const u32 bg_rock_tileset[];
extern const u32 bg_cave_tileset[];
extern const u32 bg_indoors_tileset[];

extern const u32 bg_grass_tilemap[];
extern const u32 bg_longgrass_tilemap[];
extern const u32 bg_sand_tilemap[];
extern const u32 bg_underwater_tilemap[];
extern const u32 bg_water_tilemap[];
extern const u32 bg_pond_tilemap[];
extern const u32 bg_rock_tilemap[];
extern const u32 bg_cave_tilemap[];
extern const u32 bg_indoors_tilemap[];

extern const u32 entry_bg_grass_tileset[];
extern const u32 entry_bg_longgrass_tileset[];
extern const u32 entry_bg_sand_tileset[];
extern const u32 entry_bg_underwater_tileset[];
extern const u32 entry_bg_water_tileset[];
extern const u32 entry_bg_pond_tileset[];
extern const u32 entry_bg_rock_tileset[];
extern const u32 entry_bg_cave_tileset[];
extern const u32 entry_bg_indoors_tileset[];

extern const u32 entry_bg_grass_tilemap[];
extern const u32 entry_bg_longgrass_tilemap[];
extern const u32 entry_bg_sand_tilemap[];
extern const u32 entry_bg_underwater_tilemap[];
extern const u32 entry_bg_water_tilemap[];
extern const u32 entry_bg_pond_tilemap[];
extern const u32 entry_bg_rock_tilemap[];
extern const u32 entry_bg_cave_tilemap[];
extern const u32 entry_bg_indoors_tilemap[];

extern const struct palette bg_grass_pal[];
extern const struct palette bg_longgrass_pal[];
extern const struct palette bg_sand_pal[];
extern const struct palette bg_underwater_pal[];
extern const struct palette bg_water_pal[];
extern const struct palette bg_pond_pal[];
extern const struct palette bg_rock_pal[];
extern const struct palette bg_cave_pal[];
extern const struct palette bg_indoors1_pal[];
extern const struct palette bg_indoors2_pal[];

extern const u8 poison_status_flag[];
extern const u8 sleep_status_flag[];
extern const u8 paralysis_status_flag[];
extern const u8 burn_status_flag[];
extern const u8 freeze_status_flag[];
extern const u8 trainerclass_names[0x41][13];
extern const u8 *battle_strings_table[369];
extern const u8* const stat_names_table[8];
extern const u8* const negative_flavour_table[5];

extern u8 bs_return[1];
extern u8 bs_printmove_failed[];

#endif /* B_LOCATIONS */
