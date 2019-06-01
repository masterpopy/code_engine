#ifndef VANILLA_FUNCTIONS
#define VANILLA_FUNCTIONS

#ifdef __cplusplus
extern "C"{
#endif
#define longcall __attribute__((long_call))
#define no_inline __attribute__((noinline)) //禁止编译器inline节省空间

void __attribute__((long_call)) pokemon_slot_purge(const struct pokemon* poke);
void* __attribute__((long_call)) int_to_str(void* buffer, s32 num, u8 format, u8 max_digits);
void* __attribute__((long_call)) u_int_to_str(void* buffer, u32 num, u8 format, u8 max_digits);
u8 __attribute__((long_call)) get_item_battle_function(u16 item_id);
u8 __attribute__((long_call)) get_item_quality(u16 item_id);
void __attribute__((long_call)) record_usage_of_ability(u8 bank, u8 ability);
u8 __attribute__((long_call)) calc_total_move_pp(u16 move_id, u8 pp_bonus, u8 moveset_slot);
void __attribute__((long_call)) mark_buffer_bank_for_execution(u8 bank);
u8 __attribute__((long_call)) get_item_pocket_id(u16 itemID);
u8* __attribute__((long_call)) strcpy_xFF_terminated_0(u8* destination, const u8* text_to_copy);
u8 __attribute__((long_call)) gender_from_pid(u16 species, u32 PID);
s8 __attribute__((long_call)) itemid_to_berryid(u16 itemID);
u16 __attribute__((long_call)) species_to_national_dex(u16 species);
u16 __attribute__((long_call)) get_height_or_weight(u16 national_dex_index, u8 which_one);
u8 __attribute__((long_call)) get_bank_turn_order(u8 bank);
enum poke_flavour_status __attribute__((long_call)) get_poke_flavour_relation(u32 pid, u8 flavour);
void __attribute__((long_call)) jump_if_move_has_no_effect(u8 howmuchtoadd, u16 move);
void __attribute__((long_call)) record_usage_of_item(u8 bank, u8 item_effect);
void __attribute__((long_call)) pressure_pp_lose(u8 bank_atk, u8 bank_def, u16 move);
u8 __attribute__((long_call)) is_poke_disobedient();
u8 __attribute__((long_call)) uproar_wakeup_check(u8 bank);
u8 __attribute__((long_call)) check_if_imprisioned(u8 bank, u16 move);
u8 __attribute__((long_call)) get_bank_in_love(u8 arg);
void __attribute__((long_call)) attack_iteration_cleanup();
void __attribute__((long_call)) prepare_pokemon_battle_sprite_manipulation_buffer(u8 unknown, u8 unknown2);
u8 __attribute__((long_call)) check_failure_due_to_status(u8 bank);
void __attribute__((long_call)) sub_803CEDC(u8 bank1, u8 bank2);

u8 __attribute__((long_call)) item_is_mail(u8 itemID);
u8 __attribute__((long_call)) get_lvl_from_exp(const struct pokemon*);
u16 __attribute__((long_call)) teach_move_in_available_slot(const struct pokemon* , u16 move);
void __attribute__((long_call)) new_move_for_the_first(const struct pokemon*, u16 move);
void __attribute__((long_call)) clear_atk_up_if_hit_flag_unless_enraged();
void __attribute__((long_call)) bc_bs_executer();
void __attribute__((long_call)) calculate_stats_pokekmon(const struct pokemon* poke);
void __attribute__((long_call)) refresh_graphics(u8 bank, u8 arg2, u8 objID);
void __attribute__((long_call)) task_delete(u8 taskID);
void __attribute__((long_call)) move_anim_task_del(u8 taskID);
void __attribute__((long_call)) prepare_health_bar_update_buffer(u8 bufferID, s16 hp_change);
s8 __attribute__((long_call)) compare_two_strings(const u8* string1, const u8* string2);
const u8* __attribute__((long_call)) get_trainername_address(u16 trainerID);
void __attribute__((long_call)) decompress_battle_healthbar_and_font();
void __attribute__((long_call)) update_bank_graphical_elements(u8 objID, struct pokemon* poke, u8 element);
void __attribute__((long_call)) play_sound(u16 songID);
void __attribute__((long_call)) play_cry(u16 species, u8 param1, u8 param2);
u32 __attribute__((long_call)) get_item_lastword(u16 itemID);
u8 __attribute__((long_call)) checkitem(u16 itemID, u16 quantity);
void __attribute__((long_call)) prepare_fainting_cry(u8 bufferID);
void __attribute__((long_call)) bx_move_chosing_menu();
s16 __attribute__((long_call)) get_pingpong(s16 phase, s16 scale);
u8 __attribute__((long_call)) gpu_pal_tags_index_of(u16 tag);
void __attribute__((long_call)) set_obj_pos(u8 ID, u16 x, u16 y);
void __attribute__((long_call)) c2_80777E8(void);
void __attribute__((long_call)) obj_delete(struct object*);
void __attribute__((long_call)) update_bank_sprite(u8 bank);
void __attribute__((long_call)) bank_sprite_sth(u8 bank);
u8 __attribute__((long_call)) get_poke_ability(struct pokemon* poke);
u8 __attribute__((long_call)) get_overworld_weather();
u32 __attribute__((long_call)) get_trainer_money(u16 trainerID);
void __attribute__((long_call)) give_money(u32* owned_money, u32 to_add);
u8 __attribute__((long_call)) ai_switch_perish_song();
void __attribute__((long_call)) prepare_chosen_option(u8 bufferID, u8 optionID, u16 unkown);
u8 __attribute__((long_call)) ai_switch_sth1();
u8 __attribute__((long_call)) ai_switch_sth2();
u8 __attribute__((long_call)) ai_is_statbuffed();
u8 __attribute__((long_call)) ai_switch_sth3(u8 arg1, u8 arg2);
u32 __attribute__((long_call)) malloc_and_clear(u16 size);
void __attribute__((long_call)) bbp05_send_out_poke();
void __attribute__((long_call)) bbl05_set_out_poke();
void __attribute__((long_call)) bbp06_return_poke_to_pokeball();
void __attribute__((long_call)) bbo_06_return_poke_to_ball();
void __attribute__((long_call)) bbp15_open_bag();
void __attribute__((long_call)) bbp16_open_poke_menu();
void __attribute__((long_call)) bbp2F_trainer_ball_throw();
u8 __attribute__((long_call)) b_link_related(u8 switchID, u8 bank);
void __attribute__((long_call)) load_poke_sprite_deoxys_form(void* sprite_ptr, void* dst, u16 species_no, u32 PiD, enum poke_sprite sprite);
void __attribute__((long_call)) load_poke_sprite(void* sprite_ptr, void* dst, u16 species_no, u32 PiD, enum poke_sprite sprite);
void* __attribute__((long_call)) poke_get_pal(u16 species, u32 TiD, u32 PiD);
void __attribute__((long_call)) gpu_pal_apply(const struct palette* src, u16 index, u16 num_colours);
void __attribute__((long_call)) gpu_pal_decompress_apply(const struct palette* src, u16 index, u16 num_colours);
void* __attribute__((long_call)) shorten_str_to_10(void* src);
void* __attribute__((long_call)) str_append(const u8* dst, const u8* src);
enum poke_gender __attribute__((long_call)) poke_get_gender(struct pokemon* poke);
void* __attribute__((long_call)) sub_8075094(void* string, u16 arg2, u16 arg3, u16 arg4, u8* rboxID);
void __attribute__((long_call)) sub_8075198(void* ptr, void* pixles, u8 arg3);
void __attribute__((long_call)) rboxid_08003574(u8 rboxID);
void __attribute__((long_call)) pal_fade_1(u16 arg1, u16 arg2, u8 arg3, u16 arg4);
void __attribute__((long_call)) battle_callback1();
void __attribute__((long_call)) poke_update_altitude(u8 bank, u16 species);
u8 __attribute__((long_call)) b_get_sprite_y(u8 bank);
void __attribute__((long_call)) pal_fade_control_reset_maybe();
u8 __attribute__((long_call)) fadescreen_related(u32 arg0, u8 arg1, u8 arg2, u8 arg3, u16 arg4);
void __attribute__((long_call)) quit_recorded_battle();
u8 __attribute__((long_call)) prepare_party_mail_to_give(struct pokemon* poke, u16 item);
u8 __attribute__((long_call)) specific_pokerus_check(struct pokemon* poke, u8 caseid);
u8 __attribute__((long_call)) link_get_multiplayer_id();
void* __attribute__((long_call)) get_status_text(void* dst);
u8 __attribute__((long_call)) get_bank_by_player_ai(u8 id);
void __attribute__((long_call)) buffer_item(u16 itemID, void* dst);
bool __attribute__((long_call)) getflag(u16 flagID);
void __attribute__((long_call)) clearflag(u16 flagID);
void* __attribute__((long_call)) copy_opponent_a_lose_text(void);
void* __attribute__((long_call)) copy_opponent_b_lose_text(void);
void __attribute__((long_call)) get_frontier_opponent_battleend_text(u16 trainerID, u8 textID);
void __attribute__((long_call)) x4000000_get_battle_text(u16 trainerID, u8 textID);
void __attribute__((long_call)) get_frontier_trainer_name(void* dst, u16 trainerID);
u8 __attribute__((long_call)) get_secretbase_trainerclass();
u8 __attribute__((long_call)) get_frontier_opponent_class(u16 trainerID);
u8 __attribute__((long_call)) get_x4000000_trainerclass(u16 trainerID);
void __attribute__((long_call)) get_x4000000_trainername(void* dst, u16 trainerID);
u8 __attribute__((long_call)) get_trainerxC00_trainerclass(void);
u8 __attribute__((long_call)) get_x800_trainerclass(void);
void __attribute__((long_call)) get_x800_trainername(void* dst);
u8 __attribute__((long_call)) get_linkpbs_id(u8 bank);
bool __attribute__((long_call)) is_poke_traded(struct pokemon* poke);
void __attribute__((long_call)) happiness_algorithm(struct pokemon* poke, u8 caseid);
bool __attribute__((long_call)) consider_creating_wild_poke(void* poke_data, u8 encounter_type, u8 repel_intimidate_check);
bool __attribute__((long_call)) not_enough_for_doubles(void);
bool __attribute__((long_call)) is_in_battle_pyramid(void);
bool __attribute__((long_call)) is_team_and_pc_full(void);
void __attribute__((long_call)) item_used_exit_bag(u8 taskID);
void __attribute__((long_call)) item_used_exit_pyramid_bag(u8 taskID);
void __attribute__((long_call)) bag_print_msg(u8 taskID, u8 font, const u8* text, void* return_function);
void __attribute__((long_call)) pyramid_bag_print_msg(u8 taskID, const u8* text, void* return_function);
void __attribute__((long_call)) aftertext_bag(u8 taskID);
void __attribute__((long_call)) aftertext_pyramid_bag(u8 taskID);
u16 __attribute__((long_call)) bag_remove_item(u16 itemID, u16 quantity);
enum ball_index __attribute__((long_call)) itemID_to_ballID(u16 itemID);
enum map_type __attribute__((long_call)) sav1_get_map_type(void);
u8 __attribute__((long_call)) get_or_set_pokedex_flags(u16 nationalNO, u8 caseid);
u8 __attribute__((long_call)) sp86_update_pokemon_quantity(void);
u16 __attribute__((long_call)) Sqrt(u32 val);
void __attribute__((long_call)) prepare_ball_throw_anim(u8 bufferID, u8 shakeID);
void __attribute__((long_call)) update_seen_and_caught_pokemon(u16 nationalNO, u8 caseID, u32 PiD);
u8 __attribute__((long_call)) generate_pokemon_data_for_player(const struct pokemon* poke);
u8 __attribute__((long_call)) poke_add_to_pc(const struct pokemon* poke);
bool __attribute__((long_call)) sp1E8_is_curr_box_full(void);
u16 __attribute__((long_call)) get_variable_value(u16 varID);
u8* __attribute__((long_call)) get_box_name_ptr(u8 boxID);
void __attribute__((long_call)) rboxes_free(void);
u8 __attribute__((long_call)) prepare_poke_dex_display(u16 nationalNO, u32 TiD, u32 PiD);
void __attribute__((long_call)) battle_callback2(void);
void __attribute__((long_call)) battle_vblank(void);
void __attribute__((long_call)) sub_80356D0(void);
void __attribute__((long_call)) load_battletextbox_and_elements(void);
bool __attribute__((long_call)) sub_8001AD4(void);
u8 __attribute__((long_call)) gpu_sync_bg_show(u8 bgid);
void __attribute__((long_call)) sub_8056A3C(u8 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4);
void __attribute__((long_call)) sub_8056B74(u8 arg0);
void __attribute__((long_call)) sub_8056BAC(u8 arg0);
void __attribute__((long_call)) sub_80A2390(u8 arg0);
void __attribute__((long_call)) battle_display_rbox(const u8* text_ptr, u8 flags);
void __attribute__((long_call)) prepare_string_inserter(u8 caseID, void* text_ptr, u16 species, u8 gender, u32 PiD, void* callback2);
u16 __attribute__((long_call)) cur_map_get_blockid_at(s16 x_to, s16 y_from);
void __attribute__((long_call)) obj_change_img_if_possible(struct object*, u8 img_id);
void __attribute__((long_call)) oac_wild_poke_enters_move_right(struct object*);
void __attribute__((long_call)) oac_wild_poke_animate_after_fading(struct object*);
void __attribute__((long_call)) b_animate_opponent_poke(struct object*, u16 species, bool no_cry, u8 bitfield);
void __attribute__((long_call)) b_animate_player_poke(struct object*, u16 species);
void __attribute__((long_call)) prepare_healthbox_sliding(u8 bank);
void __attribute__((long_call)) set_healthbox_visible(u8 object);
void __attribute__((long_call)) poke_restore_pp(struct pokemon*);
bool __attribute__((long_call)) not_in_battle(void);
void __attribute__((long_call)) stop_battle_music(void);
void __attribute__((long_call)) play_song_check_flag(u16 songID);
void __attribute__((long_call)) c2_exit_to_overworld_1_continue_scripts_restart_music(void);
void __attribute__((long_call)) c2_whiteout(void);
bool __attribute__((long_call)) frontier_sth(void);
void __attribute__((long_call)) rematch_trainer_flag_set(void);
void __attribute__((long_call)) set_battled_trainers_flags(void);
void __attribute__((long_call)) set_rematched_trainer_as_defeated(void);
void __attribute__((long_call)) end_battle(void);
void __attribute__((long_call)) battle_anim_refresh_graphics_maybe(u8 bank, u8 arg1, u8 objID);
u8 __attribute__((long_call)) task_add(void* function_ptr, u8 priority);
u8 __attribute__((long_call)) task_is_running(u8 taskID);
void __attribute__((long_call)) sub_80A4980(u8 taskID);
u32 __attribute__((long_call)) task_get_priv_u32(u8 taskID, u8 privateID);
void __attribute__((long_call)) task_set_priv_u32(u8 taskID, u8 privateID, u32 value);
void __attribute__((long_call)) task_do_poke_animation(u8 taskID);
void __attribute__((long_call)) task_animate_poke_after_delay(u8 taskID);
u8 __attribute__((long_call)) task_find_id_by_funcptr(void* function_ptr);
u8 __attribute__((long_call)) sav1_get_map_battleground(void);
void __attribute__((long_call)) tilemap_decompress_wram_BGconfig(u8 bgID, const void* tilemap, u16 arg2, u16 arg3);
void __attribute__((long_call)) bgid_send_tilemap(u8 bgID);
void __attribute__((long_call)) bgid_set_tilemap(u8 bgID);
void __attribute__((long_call)) frame_battletextbox(void);
void __attribute__((long_call)) turn_values_cleanup(u8 arg0);
bool __attribute__((long_call)) sub_8041728(void);
bool __attribute__((long_call)) sub_8041364(void);
void __attribute__((long_call)) fighting_mode_off(void);
void __attribute__((long_call)) create_trainer_pokemon(struct pokemon*, u16 trainerID, bool purge);
void __attribute__((long_call)) set_music_for_battle(u16 songID);
void __attribute__((long_call)) prepare_ov_to_battle_transition(u8 changeID);
void __attribute__((long_call)) sub_8163A8C(u8 taskID);
void __attribute__((long_call)) gpu_bg_config_set_field(u8 bgID, u8 arg1, u8 arg2);
void __attribute__((long_call)) lcd_io_set(u8 lcdID, u16 value);
void __attribute__((long_call)) gpu_decompress_tile_obj_alloc_tag_and_upload(void* tileObj);
void __attribute__((long_call)) task_add_01_battle_start(u8 screenchange, u16 songID);
bool __attribute__((long_call)) is_ov_to_battle_transition_done(void);
void __attribute__((long_call)) battlestructs_setup(void);
void __attribute__((long_call)) pokemon_purge_opponent(void);
void __attribute__((long_call)) sp28_party_to_save(void);
void __attribute__((long_call)) sp29_party_from_save(void);
void __attribute__((long_call)) obj_delete_and_free_tiles(struct object *parent_object);
void __attribute__((long_call)) gpu_pal_obj_alloc_tag_and_apply(const struct SpritePalette*);
void __attribute__((long_call)) gpu_tile_obj_decompress_alloc_tag_and_upload(const struct SpriteTiles*);
u8 __attribute__((long_call)) template_instanciate_forward_search(void* ptr, u16 x, u8 y, u8 derp);
void __attribute__((long_call)) task_statchange_preparestruct(u8 taskID);
void __attribute__((long_call)) change_order_in_battle(u8 bank);
void __attribute__((long_call)) sub_81B8E80(u8 bank, u8 pokeID, u8 sth);
void __attribute__((long_call)) sub_80571DC(u8 bank, u8 pokeID);
void __attribute__((long_call)) buffer_pokemon_species(u8* dst, u16 species);
void __attribute__((long_call)) update_rtc(void); //JeremyZ

u32 __attribute__((long_call)) __udivsi3(u32 numerator, u32 denumerator);

//u32 __attribute__((long_call)) __umodsi3(u32 numerator, u32 denumerator);

bool __attribute__((long_call)) task_0x82e7651(u16 arg1, u16 arg2);
u32 __attribute__((long_call)) task_0x806f621();
u16 __attribute__((long_call)) task_0x82E7BE1(u32 arg1, u8 arg2);

////memset and memcpy
#include <string.h>

//malloc and free
#include <stdlib.h>

//buffer preparers
void __attribute__((long_call)) bb2_setattributes_in_battle(u8 buffer, u8 data_request, u8 unkown, u8 data_to_add, void* ptr_to_attribute);
void __attribute__((long_call)) bbF_move_animation(u8 buffID, u16 moveID, u8 turn, u16 power, s32 dmg, u8 happiness, struct disable_struct*, u8 multihit);
void __attribute__((long_call)) bb10_printstring(u8 buffID, u16 stringID);
void __attribute__((long_call)) bb19_receive_exp(u8 bufferID, u8 pokeID, u16 exp);
void __attribute__((long_call)) bb1B_status_animation(u8 buffer, bool status2, u32 status);
void __attribute__((long_call)) bb29_hit_animation(u8 bufferID);
void __attribute__((long_call)) bb34_battle_animation(u8 buffID, u8 animID, u16 info);

//functions rewritten in ASM to get rid of long calls
u32 read_word(const void*);
u16 rng(void);

inline void LZ77UnCompVram(const void* src, void* dst){
    __asm("swi 0x12"::"r"(src), "r"(dst):);
}
inline void LZ77UnCompWram(const void* src, void* dst){
    __asm("swi 0x11"::"r"(src), "r"(dst):);
}
inline void CpuSet(void* src, void* dst, u32 mode){
    __asm("swi 0xB"::"r"(src), "r"(dst), "r"(mode):);
}
u16 get_attributes(const struct pokemon* poke_address, u8 request, void* dst);
void set_attributes(const struct pokemon* poke_address, u8 request, void* new_value);
void set_callback2(void* ptr);
u32 __umodsi3(u32, u32);

#ifdef __cplusplus
}
#endif

#endif /* VANILLA_FUNCTIONS */
