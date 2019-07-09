#include "defines.h"
#include "static_references.h"

u8 hp_condition(u8 bank, u8 percent);
bool check_ability(u8 bank, u8 ability);
u32 percent_lose(u32 number, u16 percent);
u32 percent_boost(u32 number, u16 percent);
u8 is_of_type(u8 bank, u8 type);
u16 get_airborne_state(u8 bank, u8 mode, u8 check_levitate);
u16 apply_type_effectiveness(u16 chained_effect, u8 move_type, u8 target_bank, u8 atk_bank, u8 airstatus);
u8 cant_poison(u8 atk_bank, u8 def_bank, u8 self_inflicted);
u8 get_attacking_move_type();
u8 item_battle_effects(u8 switchid, u8 bank, u8 move_turn);
u8 percent_chance(u8 percent);
void damage_calc(u16 move, u8 move_type, u8 atk_bank, u8 def_bank, u16 chained_effectiveness);
u8 find_move_in_table(u16 move, const u16* table_ptr);
u8 protect_affects(u16 move, u8 set);
u8 berry_eaten(u8 how_tocall, u8 bank);
u8 set_type(u8 bank, u8 type);
u8 get_target_of_move(u16 move, u8 target_given, u8 adjust);
void* get_move_battlescript_ptr(u32 move);
u8 affected_by_substitute(u8 bank);
u16 type_effectiveness_calc(u16 move, u8 move_type, u8 atk_bank, u8 def_bank, u8 effects_handling_and_recording);
void set_attacking_move_type();
//void revert_mega_to_normalform(u8 teamID, u8 opponent_side);
void revert_mega_to_normalform_new(u8 opponent_side);
bool is_bank_present(u32 bank);
u8 calculate_effect_chance(u8 bank, u16 move);
struct pokemon* get_bank_poke_ptr(u8 bank);
u16 get_item_extra_param(u16 item);
u8 try_cherrim_change(u8 bank);
u8 check_move_limitations(u8 bank, u8 not_usable_moves, u8 limitations);
u32 accuracy_percent(u16 move, u8 bankatk, u8 bankdef);
u8 is_poke_valid(struct pokemon* poke);
struct pokemon* get_party_ptr(u8 bank);
u8 ability_battle_effects(u8 switch_id, u8 bank, u8 ability_to_check, u8 special_cases_argument, u16 move);
u8 get_item_effect(u8 bank, u8 check_negating_effects);
u8 has_ability_effect(u8 bank, u8 mold_breaker);
s8 get_move_position(u8 bank, u16 move);
u8 weather_abilities_effect();
u8 count_party_pokemon(u8 bank);
u8* get_slide_msg(u16 trainerID, u8 caseID);
s8 get_priority(u16 move, u8 bank);
u8 cant_fall_asleep(u8 bank, u8 self_inflicted);
u8 cant_become_burned(u8 bank, u8 self_inflicted);
u8 cant_become_freezed(u8 bank, u8 self_inflicted);
u8 cant_become_paralyzed(u8 bank, u8 self_inflicted);
u8 change_stats(u8 bank, u8 bits, void* bs_unable);
void move_to_buff1(u16 move);
bool try_stealing_bank_item(u8 thief_bank, u8 victim_bank);
u8 check_field_for_ability(enum poke_abilities ability, u8 side_to_ignore, u8 mold);
enum poke_abilities get_ally_ability(u8 bank, u8 mold);
u8 findability_in_table(u8 ability, const u8* table);
u8 get_battle_bank(u8 to_get);
u8 check_if_move_failed(u8 bank);
void prep_string(u16 strID, u8 bank);
u8 get_bank_side(u8 bank);
void bs_push(void* to_return, void* now);
void bs_push_current(void* now);
void reset_multiple_turn_effects(u8 bank);
bool not_impostered(u8 bank);
bool does_move_make_contact(u16 move, u8 atk_bank); //JeremyZ
bool photon_geyser_special(u16 move); //JeremyZ
void moveeffect_set_status(u8 bank, u32 flag, u8 stringID); //JeremyZ
u32 random_value(u32 limit);
bool is_in_tag_battle(void);
bool clanging_scales_stat(void);
void revert_form_change_search(struct pokemon* poke);

void set_unburden(u8 bank)
{
	if (check_ability(bank, ABILITY_UNBURDEN))
	{
		status3[bank].unburden = 1;
	}
}

void atk7D_set_rain(void)
{
	battlescripts_curr_instruction++;
	if (battle_weather.flags.air_current || battle_weather.flags.harsh_sun)
	{
		battlescripts_curr_instruction = (void*) 0x082D9F1C; //but it failed script
	}
	else if (RAIN_WEATHER)
	{
		move_outcome.missed = 1;
		battle_communication_struct.multistring_chooser = 2;
	}
	else
	{
		battle_weather.int_bw = weather_rain;
		battle_communication_struct.multistring_chooser = 1;
		if (get_item_effect(bank_attacker, 1) == ITEM_EFFECT_DAMPROCK)
			battle_effects_duration.weather_dur = 8;
		else
			battle_effects_duration.weather_dur = 5;
	}
}

void atk95_set_sandstorm(void)
{
	battlescripts_curr_instruction++;
	if (battle_weather.flags.air_current || battle_weather.flags.harsh_sun || battle_weather.flags.heavy_rain)
	{
		battlescripts_curr_instruction = (void*) 0x082D9F1C; //but it failed script
	}
	else if (SANDSTORM_WEATHER)
	{
		move_outcome.missed = 1;
		battle_communication_struct.multistring_chooser = 2;
	}
	else
	{
		battle_weather.int_bw = weather_sandstorm;
		battle_communication_struct.multistring_chooser = 3;
		if (get_item_effect(bank_attacker, 1) == ITEM_EFFECT_SMOOTHROCK)
			battle_effects_duration.weather_dur = 8;
		else
			battle_effects_duration.weather_dur = 5;
	}
}

void atkBB_set_sunny(void)
{
	battlescripts_curr_instruction++;
	if (battle_weather.flags.air_current || battle_weather.flags.heavy_rain)
	{
		battlescripts_curr_instruction = (void*) 0x082D9F1C; //but it failed script
	}
	else if (SUN_WEATHER)
	{
		move_outcome.missed = 1;
		battle_communication_struct.multistring_chooser = 2;
	}
	else
	{
		battle_weather.int_bw = weather_sun;
		battle_communication_struct.multistring_chooser = 4;
		if (get_item_effect(bank_attacker, 1) == ITEM_EFFECT_HEATROCK)
			battle_effects_duration.weather_dur = 8;
		else
			battle_effects_duration.weather_dur = 5;
	}
}

void atkC8_set_hail(void)
{
	battlescripts_curr_instruction++;
	if (battle_weather.flags.air_current || battle_weather.flags.harsh_sun || battle_weather.flags.heavy_rain)
	{
		battlescripts_curr_instruction = (void*) 0x082D9F1C; //but it failed script
	}
	else if (HAIL_WEATHER)
	{
		move_outcome.missed = 1;
		battle_communication_struct.multistring_chooser = 2;
	}
	else
	{
		battle_weather.int_bw = weather_hail;
		battle_communication_struct.multistring_chooser = 5;
		if (get_item_effect(bank_attacker, 1) == ITEM_EFFECT_ICYROCK)
			battle_effects_duration.weather_dur = 8;
		else
			battle_effects_duration.weather_dur = 5;
	}
}

u8 count_alive_on_side(u8 bank)
{
	u8 alive_targets = 0;
	if (is_bank_present(bank))
	{
		alive_targets++;
	}
	if (is_bank_present(bank ^ 2))
	{
		alive_targets++;
	}
	return alive_targets;
}

void atk7E_set_reflect(void)
{
	battlescripts_curr_instruction++;
	u8 side = get_bank_side(bank_attacker);
	if (side_affecting_halfword[side].reflect_on)
	{
		move_outcome.missed = 1;
		battle_communication_struct.multistring_chooser = 0;
	}
	else
	{
		side_affecting_halfword[side].reflect_on = 1;
		if (get_item_effect(bank_attacker, 1) == ITEM_EFFECT_LIGHTCLAY)
			side_timers[side].reflect_timer = 8;
		else
			side_timers[side].reflect_timer = 5;
		side_timers[side].reflect_bank = bank_attacker;
		if (battle_flags.double_battle && count_alive_on_side(bank_attacker) == 2)
			battle_communication_struct.multistring_chooser = 2;
		else
			battle_communication_struct.multistring_chooser = 1;
	}
}

void atk92_set_lightscreen(void)
{
	battlescripts_curr_instruction++;
	u8 side = get_bank_side(bank_attacker);
	if (side_affecting_halfword[side].light_screen_on)
	{
		move_outcome.missed = 1;
		battle_communication_struct.multistring_chooser = 0;
	}
	else
	{
		side_affecting_halfword[side].light_screen_on = 1;
		if (get_item_effect(bank_attacker, 1) == ITEM_EFFECT_LIGHTCLAY)
			side_timers[side].lightscreen_timer = 8;
		else
			side_timers[side].lightscreen_timer = 5;
		side_timers[side].lightscreen_bank = bank_attacker;
		if (battle_flags.double_battle && count_alive_on_side(bank_attacker) == 2)
			battle_communication_struct.multistring_chooser = 4;
		else
			battle_communication_struct.multistring_chooser = 3;
	}
}

void atk96_weather_damage(void)
{
	battlescripts_curr_instruction++;
	s32 damage = 0;
	u8 ability = battle_participants[bank_attacker].ability_id;
	u8 ability_effect = has_ability_effect(bank_attacker, 0);
	if (weather_abilities_effect() && !(get_item_effect(bank_attacker, 1) == ITEM_EFFECT_SAFETYGOOGLES) &&
			!(ability_effect && (ability == ABILITY_MAGIC_GUARD || ability == ABILITY_OVERCOAT)) &&
			is_bank_present(bank_attacker))
	{
		if (SANDSTORM_WEATHER)
		{
			if (!(is_of_type(bank_attacker, TYPE_GROUND) || is_of_type(bank_attacker, TYPE_STEEL) ||
					is_of_type(bank_attacker, TYPE_ROCK)) && !(ability_effect &&
					(ability == ABILITY_SAND_FORCE || ability == ABILITY_SAND_RUSH || ability == ABILITY_SAND_VEIL)))
			{
				if (!(status3[bank_attacker].underground || status3[bank_attacker].underwater))
				{
					damage = ATLEAST_ONE(battle_participants[bank_attacker].max_hp >> 4);
				}
			}
		}
		else if (HAIL_WEATHER)
		{
		if (!(is_of_type(bank_attacker, TYPE_ICE)) && !(ability_effect && (ability == ABILITY_ICE_BODY || ability == ABILITY_SNOW_CLOAK)))
			{
				if (!(status3[bank_attacker].underground || status3[bank_attacker].underwater))
				{
					damage = ATLEAST_ONE(battle_participants[bank_attacker].max_hp >> 4);

					if (ability_effect && ability == ABILITY_ICE_BODY)
						damage *= -1;
				}
			}
		}
	}
	damage_loc = damage;
}

void atkE2_switchout_abilities(void)
{
	active_bank = get_battle_bank(read_byte(battlescripts_curr_instruction + 1));
	if (has_ability_effect(active_bank, 0))
	{
		u8 second_arg = bits_table[battle_stuff_ptr->field_58[active_bank]];
		switch (battle_participants[active_bank].ability_id)
		{
			case ABILITY_NATURAL_CURE:
				battle_participants[active_bank].status.int_status = 0;
				bb2_setattributes_in_battle(0, REQUEST_STATUS_BATTLE, second_arg, 4,
						&battle_participants[active_bank].status);
				mark_buffer_bank_for_execution(active_bank);
				break;
			case ABILITY_REGENERATOR:
			{
				u16* current_hp = &battle_participants[active_bank].current_hp;
				u16* max_hp = &battle_participants[active_bank].max_hp;
				if (current_hp)
				{
					//u16 added_hp = __udivsi3(*max_hp, 3);
					u16 added_hp = *max_hp / 3;
					if (*current_hp + added_hp > *max_hp)
					{
						added_hp = *max_hp - *current_hp;
					}
					*current_hp += added_hp;
					bb2_setattributes_in_battle(0, REQUEST_HP_BATTLE, second_arg, 2, current_hp);
					mark_buffer_bank_for_execution(active_bank);
				}
				break;
			}
			//Weather Trio
			case ABILITY_PRIMORDIAL_SEA:
			{
				if (battle_weather.flags.heavy_rain && !ability_battle_effects(15, active_bank, ABILITY_PRIMORDIAL_SEA, 0, 0)) {
					battle_weather.flags.downpour = 0;
					battle_weather.flags.rain = 0;
					battle_weather.flags.heavy_rain = 0;
				}
				break;
			}
			case ABILITY_DESOLATE_LAND:
			{
				if (battle_weather.flags.harsh_sun && !ability_battle_effects(15, active_bank, ABILITY_DESOLATE_LAND, 0, 0)) {
                    battle_weather.flags.sun = 0;
					battle_weather.flags.harsh_sun = 0;
				}
				break;
			}
			case ABILITY_DELTA_STREAM:
			{
				if (battle_weather.flags.air_current && !ability_battle_effects(15, active_bank, ABILITY_DELTA_STREAM, 0, 0)) {
					battle_weather.flags.air_current = 0;
				}
				break;
			}
		}
	}
	battlescripts_curr_instruction += 2;
}

void atk8D_multihit_move_loop_counter(void)
{
	u8 arg_counter = read_byte(battlescripts_curr_instruction + 1);
	if (arg_counter != 0)
		multihit_counter = arg_counter;
	else
	{
		if (check_ability(bank_attacker, ABILITY_SKILL_LINK))
			multihit_counter = 5;
		else if (battle_participants[bank_attacker].species == POKE_ASH_GRENJA && current_move == MOVE_WATER_SHURIKEN)
			multihit_counter = 3;
		else
		{
			u8 multihit = rng() & 3;
			if (multihit > 1)
				multihit = rng() & 3;
			multihit_counter = multihit + 2;
		}
	}
	battlescripts_curr_instruction += 2;
}

void atk42_jump_if_type(void)
{
	if (is_of_type(get_battle_bank(read_byte(battlescripts_curr_instruction + 1)),
			read_byte(battlescripts_curr_instruction + 2)))
		battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction + 3);
	else
		battlescripts_curr_instruction += 7;
}

void atk7F_set_leech_seed(void)
{
	if (move_outcome.missed || move_outcome.not_affected || move_outcome.failed || status3[bank_target].leech_seed)
	{
		move_outcome.missed = 1;
		battle_communication_struct.multistring_chooser = 1;
	}
	else if (is_of_type(bank_target, TYPE_GRASS))
	{
		move_outcome.missed = 1;
		battle_communication_struct.multistring_chooser = 2;
	}
	else
	{
		status3[bank_target].leech_seed_hp_receiver |= bank_attacker;
		status3[bank_target].leech_seed = 1;
		battle_communication_struct.multistring_chooser = 0;
	}
	battlescripts_curr_instruction++;
}

bool not_magicguard(u8 bank)
{
	if (check_ability(bank, ABILITY_MAGIC_GUARD))
		return 0;
	return 1;
}

static void hazard_type_dmg(enum poke_types type, void* BS_ptr)
{
	u32 damage = 0;
	u16 max_hp = battle_participants[active_bank].max_hp;
	switch (type_effectiveness_calc(0, type, active_bank ^ 1, active_bank, 0) >> 4)
	{
		case 1:
			damage = max_hp >> 5;
			break;
		case 2:
			damage = max_hp >> 4;
			break;
		case 4:
			damage = max_hp >> 3;
			break;
		case 8:
			damage = max_hp >> 2;
			break;
		case 16:
			damage = max_hp >> 1;
			break;
	}
	damage_loc = ATLEAST_ONE(damage);
	bs_push_current(BS_ptr);
}

bool is_class_FOUR(u8 bank);

bool entry_hazards_hook(void)
{
	bool effect = 0;
	u8 banks_side = get_bank_side(active_bank);
	struct side_affecting* ptr_to_struct = &new_battlestruct->side_affecting[banks_side];
	if (ptr_to_struct->lunardance)
	{
		ptr_to_struct->lunardance = 0;
		damage_loc = battle_participants[active_bank].max_hp * -1;
		battle_participants[active_bank].status.int_status = 0;
		bb2_setattributes_in_battle(0, REQUEST_STATUS_BATTLE, 0, 4, &battle_participants[active_bank].status);
		mark_buffer_bank_for_execution(active_bank);
		//heal pp
		bs_push_current(BS_LUNARDANCE);
		effect = 1;
	}
	else if (side_affecting_halfword[banks_side].spikes_on &&
			!(side_affecting_halfword[banks_side].spikes_damage_done) && GROUNDED(active_bank) &&
			not_magicguard(active_bank) && !is_class_FOUR(active_bank))
	{
		side_affecting_halfword[banks_side].spikes_damage_done = 1;
		damage_loc = ATLEAST_ONE(
				battle_participants[active_bank].max_hp / ((5 - side_timers[banks_side].spikes_amount) * 2));
		bs_push_current(BS_SPIKES);
		effect = 1;
	}
	else if (ptr_to_struct->stealthrock && !ptr_to_struct->stealthrock_done && not_magicguard(active_bank) &&
			!is_class_FOUR(active_bank))
	{
		ptr_to_struct->stealthrock_done = 1;
		hazard_type_dmg(TYPE_ROCK, BS_STEALTHROCK);
		effect = 1;
	}
	else if (ptr_to_struct->sticky_web && !ptr_to_struct->sticky_web_done && GROUNDED(active_bank))
	{
		ptr_to_struct->sticky_web_done = 1;
		bs_push_current(BS_STICKYWEB);
		battle_scripting.stat_changer = 0x93;
		effect = 1;
	}
	else if (ptr_to_struct->toxic_spikes_psn && !ptr_to_struct->toxic_spikes_done && GROUNDED(active_bank))
	{
		ptr_to_struct->toxic_spikes_done = 1;
		if (is_of_type(active_bank, TYPE_POISON))
		{
			effect = 1;
			ptr_to_struct->toxic_spikes_psn = 0;
			ptr_to_struct->toxic_spikes_badpsn = 0;
			bs_push_current(BS_TOXICSPIKESABSORBED);
		}
		else if (!cant_poison(active_bank, active_bank, 0))
		{
			if (ptr_to_struct->toxic_spikes_badpsn)
			{
				battle_participants[active_bank].status.flags.toxic_poison = 1;
				battle_communication_struct.multistring_chooser = 1;
			}
			else
			{
				battle_participants[active_bank].status.flags.poison = 1;
				battle_communication_struct.multistring_chooser = 0;
			}
			bs_push_current(BS_TOXICSPIKES);
			effect = 1;
			bb2_setattributes_in_battle(0, REQUEST_STATUS_BATTLE, 0, 4, &battle_participants[active_bank].status.flags);
			mark_buffer_bank_for_execution(active_bank);
		}
	}
	if (effect)
	{
		new_battlestruct->various.var1 = active_bank;
		battle_participants[active_bank].status2.destinny_bond = 0;
		hitmarker &= 0xFFFFFFBF; //same as above
	}
	return effect;
}

void switchin_newstruct_update(void)
{
	struct bank_affecting* ptr_to_struct = &new_battlestruct->bank_affecting[active_bank];
	struct bank_affecting previous_struct = new_battlestruct->bank_affecting[active_bank];
	memset(ptr_to_struct, 0, sizeof(struct bank_affecting));
	ptr_to_struct->type3 = TYPE_EGG;
	ptr_to_struct->just_switched_in = 1;
	ptr_to_struct->wish_hp = previous_struct.wish_hp;
	if (current_move == MOVE_BATON_PASS)
	{
		ptr_to_struct->aqua_ring = previous_struct.aqua_ring;
		ptr_to_struct->embargo = previous_struct.embargo;
		ptr_to_struct->powertrick = previous_struct.powertrick;
		ptr_to_struct->gastro_acided = previous_struct.gastro_acided;
		ptr_to_struct->heal_block = previous_struct.heal_block;
		if (previous_struct.powertrick)
		{
			u16* atk = &battle_participants[active_bank].atk;
			u16* def = &battle_participants[active_bank].def;
			u16 placeholder = *atk;
			*atk = *def;
			*def = placeholder;
		}
	}
	struct side_affecting* side_ptr = &new_battlestruct->side_affecting[get_bank_side(active_bank)];
	side_ptr->stealthrock_done = 0;
	side_ptr->sticky_web_done = 0;
	side_ptr->toxic_spikes_done = 0;
	side_ptr->lunardance_done = 0;
}

bool does_move_target_multiple(void)
{
	bool retval = 0;
	if (battle_flags.double_battle)
	{
		u8 alive_targets = count_alive_on_side(bank_target);
		bool alive_atk_ally = is_bank_present(bank_attacker ^ 2);
		if (move_table[current_move].target == move_target_both)
		{
			retval = (alive_targets == 2);
		}
		else if (move_table[current_move].target == move_target_foes_and_ally)
		{
			retval = (alive_targets == 2 || (alive_targets == 1 && alive_atk_ally));
		}
	}
	return retval;
}

/*bool calc_recoil_dmg(u8 bank, u16 move)
{
	if ((check_ability(bank, ABILITY_ROCK_HEAD) || check_ability(bank, ABILITY_MAGIC_GUARD)) && move != MOVE_STRUGGLE)
	{
		record_usage_of_ability(bank, battle_participants[bank].ability_id);
		return 0;
	}
	u16 recoil_dmg;
	//formula is dmg = HP dealt / arg2 or MaxHP / arg2 if value is negative
	s8 arg = move_table[move].arg2;
	if (arg < 0)
		recoil_dmg = battle_participants[bank].max_hp / (arg * -1);
	else
		recoil_dmg = hp_dealt / arg;
	damage_loc = ATLEAST_ONE(recoil_dmg);
	return 1;
}*/

u8 can_lose_item(u8 bank, u8 stickyhold_check, u8 sticky_message);

void copy_status_condition_text(u8 bank, u8 confusion);

void status_to_effect();

bool move_effect2_setter(void)
{
	u8* move_effect = &battle_communication_struct.move_effect;
	if (!MOVE_WORKED)
	{
		*move_effect = 0;
		return 0;
	} //if move didn't work, its effect can't work either

	//get bank
	u8 bank = bank_target;
	if (*move_effect & EFFECT2_AFFECTSUSER)
		bank = bank_attacker;

	bank_partner_def = bank; //for scripts

	void* matcher = battlescripts_curr_instruction;

	bool substitute = (affected_by_substitute(bank) && !(*move_effect & EFFECT2_AFFECTSUSER));

	struct battle_participant* applier_bank = &battle_participants[bank];
	u16 current_hp = applier_bank->current_hp;

	switch (BIC(*move_effect, EFFECT2_AFFECTSUSER))
	{
		case 10: //heal target's status
		{
			u32* status = &applier_bank->status.int_status;
			if (!substitute && applier_bank->status.int_status && (move_table[current_move].arg1 & *status) &&
					current_hp)
			{
				copy_status_condition_text(bank, 0);
				*status = 0;
				active_bank = bank;
				bb2_setattributes_in_battle(0, REQUEST_STATUS_BATTLE, 0, 4, status);
				mark_buffer_bank_for_execution(active_bank);
				bs_push_current((void*) 0x82DB361);
			}
		}
			break;
		case 11: //wrap
			if (!substitute && !applier_bank->status2.trapped_in_wrap && current_hp &&
					battle_participants[bank_attacker].current_hp)
			{
				if (get_item_effect(bank_attacker, 1) == ITEM_EFFECT_GRIPCLAW)
					applier_bank->status2.trapped_in_wrap = 7;
				else
					applier_bank->status2.trapped_in_wrap = 4 + (rng() & 1);
				battle_stuff_ptr->binding_move[bank] = current_move;
				battle_stuff_ptr->binded_by[bank] = bank_attacker;
				bs_push_current(BS_BINDEFFECT);
				static const u16 trapping_moves[8] = {MOVE_BIND, MOVE_WHIRLPOOL, MOVE_WRAP, MOVE_CLAMP, MOVE_SAND_TOMB,
						MOVE_FIRE_SPIN, MOVE_MAGMA_STORM, MOVE_INFESTATION};
				for (u8 i = 0; i < 8; i++)
				{
					if (current_move == trapping_moves[i])
					{
						battle_communication_struct.multistring_chooser = i;
						break;
					}
				}
			}
			break;
		case 12: //clear stat changes
			if (current_hp)
			{
				u8 effect = 0;
				u8* stat_ptr = &battle_participants[bank].hp_buff;
				for (u8 i = 0; i < 8; i++)
				{
					if (*(stat_ptr + i) != 6)
					{
						effect++;
						*(stat_ptr + i) = 6;
					}
				}
				if (effect)
					bs_push_current(BS_CLEARSMOG);
			}
			break;
		case 13: //steal item
			if (!substitute && battle_participants[bank_attacker].current_hp && !battle_flags.flag_x4000000 &&
					!WILD_ATTACKER)
			{
				u16* targets_item = &applier_bank->held_item;
				u16* attackers_item = &battle_participants[bank_attacker].held_item;
				if (*targets_item && !CHECK_KNOCKED_OFF(bank_target) && *attackers_item == 0 &&
						can_lose_item(bank_target, 1, 1))
				{
					if (!ITEM_STEAL && !get_bank_side(bank_attacker) && battle_flags.trainer)
					{
						new_battlestruct->various.returns_item |= bits_table[battle_team_id_by_side[bank_attacker]];
					}
					bs_push_current((void*) 0x82DB422);
					last_used_item = *targets_item;
					*attackers_item = *targets_item;
					*targets_item = 0;
					if (get_bank_side(bank_attacker)) //save player's item
					{
						SET_KNOCKED_OFF(bank_target);
					}
					else
					{
						active_bank = bank_target;
						bb2_setattributes_in_battle(0, REQUEST_HELDITEM_BATTLE, 0, 2, targets_item);
						mark_buffer_bank_for_execution(active_bank);
					}
					active_bank = bank_attacker;
					bb2_setattributes_in_battle(0, REQUEST_HELDITEM_BATTLE, 0, 2, attackers_item);
					mark_buffer_bank_for_execution(active_bank);
					battle_stuff_ptr->choiced_move[bank] = 0;
				}
			}
			break;
		case 14: //smack poke down
			if (current_hp && new_battlestruct->bank_affecting[bank].smacked_down == 0 &&
					(!GROUNDED(bank) || status3[bank].on_air ||
							new_battlestruct->bank_affecting[bank].sky_drop_attacker ||
							new_battlestruct->bank_affecting[bank].sky_drop_target))
			{
				new_battlestruct->bank_affecting[bank].smacked_down = 1;
				new_battlestruct->bank_affecting[bank].magnet_rise = 0;
				new_battlestruct->bank_affecting[bank].telekinesis = 0;
				status3[bank].on_air = 0;
				bs_push_current(BS_SMACKDOWN);
			}
			break;
		case 15: //rapid spin
			if (battle_participants[bank_attacker].current_hp)
			{
				bs_push_current((void*) 0x82DAFC3);
			}
			break;
		case 16: //knock off
			if (!substitute && applier_bank->held_item && can_lose_item(bank, 1, 1) &&
					battle_participants[bank_attacker].current_hp)
			{
				last_used_item = applier_bank->held_item;
				applier_bank->held_item = 0;
				battle_effects_duration.knocked_off_pokes[get_bank_side(
						bank)] |= bits_table[battle_team_id_by_side[bank]];
				bs_push_current((void*) 0x082DB168);
				battle_stuff_ptr->choiced_move[bank] = 0;
				set_unburden(bank_target);
			}
			break;
		case 17: //lose type
			if (current_hp)
			{
				u8 type = move_table[current_move].arg1;
				if (applier_bank->type1 == type)
					applier_bank->type1 = TYPE_EGG;
				if (applier_bank->type2 == type)
					applier_bank->type2 = TYPE_EGG;
				if (new_battlestruct->bank_affecting[bank].type3 == type)
					new_battlestruct->bank_affecting[bank].type3 = TYPE_EGG;
				bs_push_current(BS_BURNUP);
			}
			break;
		/*case 48: //recoil
			if (battle_participants[bank_attacker].current_hp && TARGET_TURN_DAMAGED &&
					calc_recoil_dmg(bank_attacker, current_move))
			{
				bs_push_current((void*) 0x082DB3F4);
			}
			break;*/
		case 0xb1: //recharge needed
			if (current_hp)
			{
				applier_bank->status2.recharge = 1;
				disable_structs[bank].recharge_counter = 2;
				locked_move[bank] = current_move;
				*move_effect = 0;
			}
			break;
		case 50: //rage setter
			if (current_hp)
				applier_bank->status2.raged = 1;
			break;
		case 51: //payday
			if (!get_bank_side(bank))
			{
				u16 to_give = 5 * applier_bank->level;
				if (payday_money + to_give > 0xFFFF)
					payday_money = 0xFFFF;
				else
				{
					payday_money += to_give;
					bs_push_current((void*) 0x082DB3D6);
				}
			}
			break;
		case 52: //uproar
			if (applier_bank->status2.uproar == 0 && current_hp)
			{
				applier_bank->status2.uproar = 3;
				applier_bank->status2.multiple_turn_move = 1;
				locked_move[bank] = current_move;
				bs_push_current((void*) 0x82DB3C2);
			}
			break;
		case 53: //set thrash
			if (applier_bank->status2.locked_and_confuse == 0 && current_hp)
			{
				applier_bank->status2.locked_and_confuse = 2 + (rng() & 1);
				applier_bank->status2.multiple_turn_move = 1;
				locked_move[bank] = current_move;
			}
			break;
		case 54: //berry eating
		{
			u16* berry = &battle_participants[bank].held_item;
			if (MOVE_WORKED && !substitute && *berry && get_item_pocket_id(*berry) == 4)
			{
				bool arg = (move_table[current_move].arg2 == 0xA);
				if (arg && !battle_participants[bank_attacker].current_hp)
				{
					break;
				} //to get the bug bite effect, attacker must be alive
				last_used_item = *berry;
				*berry = 0;
				active_bank = bank;
				bb2_setattributes_in_battle(0, REQUEST_HELDITEM_BATTLE, 0, 2, berry);
				mark_buffer_bank_for_execution(bank);


				if (!arg) //incinerate; berry destroy, no effect
					bs_push_current(BS_INCINERATEBERRY);
				else //pluck, bug bite; get berry's effect
					bs_push_current(BS_BUGBITE);
			}
		}
			break;
		case 55: //set twoturn move
			battle_participants[bank].status2.multiple_turn_move = 1;
			locked_move[bank] = current_move;
			break;
		case 56: //flame burst
			if (battle_flags.double_battle)
			{
				u8 target_ally = bank_target ^0x2;
				if (is_bank_present(target_ally) && !check_ability(target_ally, ABILITY_MAGIC_GUARD))
				{
					damage_loc = get_1_16_of_max_hp(target_ally);
					bank_partner_def = target_ally;
					bs_push_current(BS_FLAMEBURST);
				}
			}
			break;
		case 57: // thousand waves
			if (!substitute && current_hp && !battle_participants[bank_target].status2.cant_escape)
			{
				bs_push_current(BS_DAMAGETRAP);
			}
			break;
	}

	*move_effect = 0;
	if (matcher == battlescripts_curr_instruction)
		return 0;
	return 1;
}

void clear_twoturn(u8 bank)
{
	status3[bank].on_air = 0;
	status3[bank].underwater = 0;
	status3[bank].underground = 0;
	status3[bank].phantomforce = 0;
	new_battlestruct->bank_affecting[bank].sky_drop_attacker = 0;
	new_battlestruct->bank_affecting[bank].sky_drop_target = 0;
}

void atk49_move_end_turn(void)
{
#define INC_END_EVENTS battle_scripting.cmd49_state_tracker++;
#define case_max 40
	u8 effect = 0;
	u16 last_move;
	if (last_used_move == 0xFFFF)
		last_move = 0;
	else
		last_move = last_used_move;
	new_battlestruct->bank_affecting[bank_attacker].lastmove_fail = !MOVE_WORKED; //JeremyZ
	u8 arg1 = read_byte(battlescripts_curr_instruction + 1);
	u8 arg2 = read_byte(battlescripts_curr_instruction + 2);
	u8 current_move_type = get_attacking_move_type();
	struct battle_participant* target_struct = &battle_participants[bank_target];
	struct battle_participant* attacker_struct = &battle_participants[bank_attacker];
	while (effect == 0)
	{
		switch (battle_scripting.cmd49_state_tracker)
		{
			case 0: //safe attacker bank, clear no animation bits
				new_battlestruct->various.cmd49_safeattacker_bank = bank_attacker;
				new_battlestruct->various.dont_play_move_anim = 0;
				new_battlestruct->various.dont_play_stat_anim = 0;
				INC_END_EVENTS
			case 1: //spiky shield recoil
				if (new_battlestruct->bank_affecting[bank_attacker].spikyshield_damage && attacker_struct->current_hp &&
						not_magicguard(bank_attacker))
				{
					effect = 1;
					damage_loc = get_1_8_of_max_hp(bank_attacker);
					bs_push_current(BS_SPIKYSHIELD);
					new_battlestruct->bank_affecting[bank_attacker].spikyshield_damage = 0;
					move_outcome.missed = 0;
				}  // king shield recoil
				else if (new_battlestruct->bank_affecting[bank_attacker].kingsshield_damage &&
						attacker_struct->atk_buff != 0)
				{
					new_battlestruct->bank_affecting[bank_attacker].kingsshield_damage = 0;
					battle_scripting.stat_changer = 0xA1;
					move_outcome.missed = 0;
					bs_push_current(BS_CHANGE_ATK_STAT);
					effect = 1;
				}
				else if (new_battlestruct->bank_affecting[bank_attacker].banefulbunker_damage &&
						!cant_poison(bank_target, bank_attacker, 0)) //JeremyZ
				{
					new_battlestruct->bank_affecting[bank_attacker].banefulbunker_damage = 0;
					attacker_struct->status.flags.poison = 1;
					active_bank = bank_attacker;
					bb2_setattributes_in_battle(0, REQUEST_STATUS_BATTLE, 0, 4, &attacker_struct->status.flags);
					mark_buffer_bank_for_execution(active_bank);
					bs_push_current((void*) (0x082DB386));
					battle_communication_struct.multistring_chooser = 0;
					bank_partner_def = bank_attacker;
					effect = 1;
				}
				INC_END_EVENTS
				break;
			case 2: //rage checker
				if (target_struct->current_hp && target_struct->status2.raged && bank_target != bank_attacker &&
						get_bank_side(bank_target) != get_bank_side(bank_attacker) && MOVE_WORKED &&
						TARGET_TURN_DAMAGED && DAMAGING_MOVE(current_move) && target_struct->atk_buff != 0xC)
				{
					target_struct->atk_buff++;
					bs_push_current((void*) 0x082DAE0D); //rage is building
					effect = 1;
				}
				INC_END_EVENTS
				break;
			case 3: //defrosting via fire type move
				if (target_struct->current_hp && target_struct->status.flags.freeze && TARGET_TURN_DAMAGED &&
						MOVE_WORKED && (current_move_type == TYPE_FIRE || current_move == MOVE_SCALD || current_move == MOVE_STEAM_ERUPTION))
				{
					target_struct->status.flags.freeze = 0;
					active_bank = bank_target;
					bs_push_current((void*) 0x082DB282);
					effect = 1;
					bb2_setattributes_in_battle(0, REQUEST_STATUS_BATTLE, 0, 4, &target_struct->status);
					mark_buffer_bank_for_execution(active_bank);
				}
				INC_END_EVENTS
				break;
			case 4: // user ability activation on strike
				if (ability_battle_effects(10, bank_attacker, 0, 0, 0))
					effect = 1;
				INC_END_EVENTS
				break;
			case 5: // user items activation on strike (setting life orb bit or accumulating shell bell hp
				if (item_battle_effects(4, bank_attacker, 0))
					effect = 1;
				INC_END_EVENTS
				break;
			case 6: //target's synchronize activation
				if (ability_battle_effects(7, bank_target, 0, 0, 0))
					effect = 1;
				INC_END_EVENTS
				break;
			case 7: //target's ability activation on strike
				if (ability_battle_effects(4, bank_target, 0, 0, 0))
					effect = 1;
				INC_END_EVENTS
				break;
			case 8: //target's items activation on strike
				if (item_battle_effects(2, bank_target, 0))
					effect = 1;
				INC_END_EVENTS
				break;
			case 9: //attacker synchronize activation
				if (ability_battle_effects(8, bank_attacker, 0, 0, 0))
					effect = 1;
				INC_END_EVENTS
				break;
			case 10: //held items
			{
				for (u8 i = 0; i < no_of_all_banks; i++)
				{
					u16* changed_item = &battle_stuff_ptr->changed_held_items[i];
					if (*changed_item)
					{
						battle_participants[i].held_item = *changed_item;
						*changed_item = 0;
					}
				}
			}
				INC_END_EVENTS;
				break;
			case 11: //choice move update
			{
				if (!SEPARATE_COURSE)
				{
					u16 attacker_item = get_item_effect(bank_attacker, 1);
					u16* choice_move = &battle_stuff_ptr->choiced_move[bank_attacker];
					if (CHOICE_ITEM(attacker_item) && last_used_move != MOVE_STRUGGLE &&
							(hitmarker & HITMARKER_OBEYS) && (*choice_move == 0 || *choice_move == 0xFFFF))
					{
						if ((last_used_move == MOVE_BATON_PASS || last_used_move == MOVE_VOLT_SWITCH ||
								last_used_move == MOVE_UTURN) && move_outcome.failed)
						{
							INC_END_EVENTS
							break;
						}
						*choice_move = last_used_move;
					}
					if (get_move_position(bank_attacker, *choice_move) == -1)
						*choice_move = 0;

				}
				INC_END_EVENTS
				break;
			}
			case 12: //hide attacker/target sprite in a semi invulnerable state
				if (!(hitmarker & HITMARKER_NO_ANIMATIONS))
				{
					if (SEMI_INVULNERABLE(bank_attacker))
					{
						active_bank = bank_attacker;
						prepare_pokemon_battle_sprite_manipulation_buffer(0, 1);
						mark_buffer_bank_for_execution(active_bank);
					}
					if (SEMI_INVULNERABLE(bank_target))
					{
						active_bank = bank_target;
						prepare_pokemon_battle_sprite_manipulation_buffer(0, 1);
						mark_buffer_bank_for_execution(active_bank);
					}
				}
				INC_END_EVENTS
				break;
			case 13: //refresh/restore user sprite in second turn of dive
				if (!MOVE_WORKED || !SEMI_INVULNERABLE(bank_attacker) || check_failure_due_to_status(bank_attacker))
				{
					active_bank = bank_attacker;
					prepare_pokemon_battle_sprite_manipulation_buffer(0, 0);
					mark_buffer_bank_for_execution(active_bank);
					clear_twoturn(bank_attacker);
					special_statuses[bank_attacker].restored_bank_sprite = 1;
				}
				INC_END_EVENTS
				break;
			case 14: //refresh/restore defender's sprite
				if (!special_statuses[bank_target].restored_bank_sprite && (bank_target < no_of_all_banks) &&
						!(SEMI_INVULNERABLE(bank_target)))
				{
					active_bank = bank_target;
					prepare_pokemon_battle_sprite_manipulation_buffer(0, 0);
					mark_buffer_bank_for_execution(active_bank);
					clear_twoturn(bank_target);
				}
				INC_END_EVENTS
			case 15: //item move end turn
				if (multihit_counter != 0 && multihit_counter != 1 && item_battle_effects(3, 0, 0))
				{
					effect = 1;
					break;
				}
				INC_END_EVENTS
			case 16: //status immunities
				if (multihit_counter != 0 && multihit_counter != 1 && ability_battle_effects(5, 0, 0, 0, 0))
				{
					effect = 1;
					break;
				}
				INC_END_EVENTS
			case 17: // clear substitute bits
				if (multihit_counter != 0 || multihit_counter != 1)
				{
					for (u8 i = 0; i < no_of_all_banks; i++)
					{
						if (disable_structs[i].substitute_hp == 0)
							battle_participants[i].status2.substitute = 0;
					}
				}
				INC_END_EVENTS
			case 18: //clear turn bits
				if (new_battlestruct->various.bust_mimikyu)
				{
					new_battlestruct->various.bust_mimikyu = 0;
					special_statuses[bank_attacker].moveturn_losthp = 0;
					special_statuses[bank_attacker].moveturn_losthp_physical = 0;
					special_statuses[bank_attacker].moveturn_losthp_special = 0;
					if (get_item_effect(bank_attacker, 1) == ITEM_EFFECT_LIFEORB)
					{
						new_battlestruct->various.life_orbed = 1;
					}
				}
				bank_attacker = new_battlestruct->various.cmd49_safeattacker_bank;
				new_battlestruct->various.magicbounce = 0; //avoids endless loops if magic bounce meets magic bounce or magic coat
				new_battlestruct->various.protean_msg = 0; //protean message
				new_battlestruct->various.gem_boost = 0; //gem boost
				new_battlestruct->various.gravity_levitate = 0; //gravity levitate message
				INC_END_EVENTS
			case 19: //setup buffer for conversion, sketch etc.
				if (!SEPARATE_COURSE)
				{
					if (hitmarker & HITMARKER_PURSUIT_TRAP)
					{
						active_bank = bank_attacker;
						bank_attacker = bank_target;
						bank_target = active_bank;
						hitmarker &= 0xFFFFEFFF;
					}
					if (hitmarker & HITMARKER_ATTACKSTRING_PRINTED) //used by sketch
						sketchable_move_used[bank_attacker] = last_used_move;
					if (!(absent_bank_flags & bits_table[bank_attacker] &
							battle_stuff_ptr->absent_bank_flags_prev_turn) && last_move != MOVE_BATON_PASS)
					{
						if ((hitmarker & HITMARKER_OBEYS))
						{
							current_move_used[bank_attacker] = current_move;
							calling_move_used[bank_attacker] = last_used_move;
						}
						else
						{
							current_move_used[bank_attacker] = 0xFFFF;
							calling_move_used[bank_attacker] = 0xFFFF;
						}
						if (!(hitmarker & HITMARKER_FAINTED(bank_target)))
							attacked_by[bank_target] = bank_attacker;
						if ((hitmarker & HITMARKER_OBEYS) && MOVE_WORKED)
						{
							move_hit_with_pbs[bank_target] = current_move;
							move_type_hit_with_pbs[bank_target] = current_move_type;
						}
						else
							move_hit_with_pbs[bank_target] = 0xFFFF;
					}
					new_battlestruct->bank_affecting[bank_attacker].lastmove_type = current_move_type + 0x80;
				}
				INC_END_EVENTS
				break;
			case 20: //setup mirror_move_buffers
				if (!SEPARATE_COURSE)
				{
					if (!(absent_bank_flags & bits_table[bank_attacker] &
							battle_stuff_ptr->absent_bank_flags_prev_turn) &&
							move_table[current_move].move_flags.flags.affected_by_mirrormove &&
							(hitmarker & HITMARKER_OBEYS) && bank_attacker != bank_target &&
							!(hitmarker & HITMARKER_FAINTED(bank_target)) && MOVE_WORKED)
					{
						battle_stuff_ptr->mirror_moves_pbs[bank_target] = last_used_move;
						battle_stuff_ptr->mirror_move_set_pbs[bank_target].moves_per_target[bank_attacker] = last_used_move;
					}
				}
				INC_END_EVENTS
				break;
			case 21: //parental bond
			{
				if ((new_battlestruct->various.parental_bond_mode == PBOND_PARENT) && MOVE_WORKED &&
						TARGET_TURN_DAMAGED && !(hitmarker & HITMARKER_IMMOBILE_DUE_TO_STATUS) &&
						battle_participants[bank_target].current_hp && battle_participants[bank_attacker].current_hp)
				{
					multihit_counter = 1;
					new_battlestruct->various.parental_bond_mode = PBOND_CHILD;
					//hitmarker &= 0xFDF1E1FF;
					hitmarker |= HITMARKER_NO_PPDEDUCT;
					attack_iteration_cleanup();
					battle_scripting.cmd49_state_tracker = 0;
					//bank_attacker = bank_target;
					//bank_target = get_target_of_move(current_move, 0, 0);
					//set_attacking_move_type();
					battlescripts_curr_instruction = get_move_battlescript_ptr(current_move);
					bs_push_current((void*) (0x82DB87D));
					effect = 1;
				}/*else if(current_move==MOVE_INSTRUCT){
				bank_attacker = bank_target;
				bank_target = get_target_of_move(current_move, 0, 0);
				set_attacking_move_type();
				attack_iteration_cleanup();
				hitmarker &= 0xFDF1E1FF;
				battle_scripting.cmd49_state_tracker=0;
				battlescripts_curr_instruction = get_move_battlescript_ptr(current_move);
				bs_push_current((void *)(0x82DB87D));
				effect=1;
			}*/
				else
				{
					INC_END_EVENTS;
				}
				break;
			}
			case 22: //primary effects
				if (!check_if_move_failed(bank_attacker) && move_effect2_setter())
					effect = 1;
				INC_END_EVENTS;
				break;
			case 23: //color change
				bank_attacker = new_battlestruct->various.cmd49_safeattacker_bank;
				if (ability_battle_effects(21, bank_target, 0, 0, 0))
					effect = 1;
				INC_END_EVENTS
				break;
			case 24: //dual target moves
				if (!(hitmarker & HITMARKER_IMMOBILE_DUE_TO_STATUS) &&
						move_table[current_move].target == move_target_both && battle_flags.double_battle &&
						!protect_structs[bank_attacker].flag0_onlystruggle &&
						!(hitmarker & HITMARKER_NO_ATTACKSTRING) && is_bank_present(bank_target ^ 2))
				{
					bank_target = bank_target ^ 2;
					hitmarker |= HITMARKER_NO_ATTACKSTRING;
					attack_iteration_cleanup();
					battle_scripting.cmd49_state_tracker = 0;
					battlescripts_curr_instruction = get_move_battlescript_ptr(current_move);
					bs_push_current((void*) 0x82DB87D);
					effect = 1;
					new_battlestruct->bank_affecting[bank_attacker].move_worked_thisturn |= MOVE_WORKED;
					break;
				}
				INC_END_EVENTS
				break;
			case 25: //triple target moves
				if (!(hitmarker & HITMARKER_IMMOBILE_DUE_TO_STATUS) &&
						move_table[current_move].target == move_target_foes_and_ally && battle_flags.double_battle &&
						!protect_structs[bank_attacker].flag0_onlystruggle)
				{
					if ((move_table[current_move].script_id == 23 || move_table[current_move].script_id == 192) &&
							move_outcome.explosion_stop) //stop explosion if damp on, JeremyZ
					{
						move_outcome.explosion_stop = 0;
						INC_END_EVENTS
						break;
					}
					u8 next_target = bank_target + 1;
					while (next_target < no_of_all_banks &&
							(!is_bank_present(next_target) || next_target == bank_attacker))
						next_target++;
					if (is_bank_present(next_target))
					{
						bank_target = next_target;
						hitmarker |= HITMARKER_NO_ATTACKSTRING;
						attack_iteration_cleanup();
						battle_scripting.cmd49_state_tracker = 0;
						battlescripts_curr_instruction = get_move_battlescript_ptr(current_move);
						bs_push_current((void*) (0x82DB87D));
						effect = 1;
						new_battlestruct->bank_affecting[bank_attacker].move_worked_thisturn |= MOVE_WORKED;
						break;
					}
				}
				INC_END_EVENTS
				break;
			case 26: //life orb damage
				if (attacker_struct->current_hp && !new_battlestruct->various.sheerforce_bonus)
				{
					if (new_battlestruct->various.life_orbed && not_magicguard(bank_attacker))
					{
						damage_loc = ATLEAST_ONE(attacker_struct->max_hp / 10);
						bs_push_current(BS_LIFEORB);
						record_usage_of_item(bank_attacker, ITEM_EFFECT_LIFEORB);
						effect = 1;
					}
					else if (new_battlestruct->various.accumulated_damage &&
							attacker_struct->current_hp < attacker_struct->max_hp)
					{
						damage_loc = -ATLEAST_ONE(new_battlestruct->various.accumulated_damage / 8);
						another_active_bank = bank_attacker;
						battle_scripting.active_bank = bank_attacker;
						last_used_item = attacker_struct->held_item;
						bs_push_current((void*) 0x82DB7F7);
						record_usage_of_item(bank_attacker, ITEM_EFFECT_SHELLBELL);
						effect = 1;
					}
				}
				new_battlestruct->various.parental_bond_mode = 0;
				new_battlestruct->various.gem_boost = 0;
				new_battlestruct->various.life_orbed = 0;
				new_battlestruct->various.sheerforce_bonus = 0;
				new_battlestruct->various.accumulated_damage = 0;
				INC_END_EVENTS
				break;
			case 27: //set this move as previous and mark move as used
				if (last_used_move)
					new_battlestruct->various.previous_move = last_used_move;
				else
					new_battlestruct->various.previous_move = current_move;
				s8 pos = get_move_position(bank_attacker, current_move);
				if (pos == -1)
					pos = get_move_position(bank_attacker, last_used_move);
				if (pos != -1)
					new_battlestruct->bank_affecting[bank_attacker].usedmoves |= bits_table[pos];
				INC_END_EVENTS
			case 28: //item move end turn
				if ((multihit_counter == 0 || multihit_counter == 1) && item_battle_effects(3, 0, 0))
				{
					effect = 1;
					break;
				}
				INC_END_EVENTS
			case 29: //status immunities
				bank_attacker = new_battlestruct->various.active_bank;
				if ((multihit_counter == 0 || multihit_counter == 1) && ability_battle_effects(5, 0, 0, 0, 0))
				{
					effect = 1;
					break;
				}
				INC_END_EVENTS
			case 30: // clear substitute bits
				if (multihit_counter == 0 || multihit_counter == 1)
				{
					for (u8 i = 0; i < no_of_all_banks; i++)
					{
						if (disable_structs[i].substitute_hp == 0)
						{
							battle_participants[i].status2.substitute = 0;
						}
					}
				}
				INC_END_EVENTS
				break;
			case 31: //pickpocket ability activation on strike
				bank_attacker = new_battlestruct->various.cmd49_safeattacker_bank;
				if (ability_battle_effects(22, bank_target, 0, 0, 0))
					effect = 1;
				INC_END_EVENTS
				break;
			case 32: //red card/eject button and emergency exit
				if (item_battle_effects(6, bank_target, 0) || ability_battle_effects(23, bank_target, 0, 0, 0))
					effect = 1;
				INC_END_EVENTS
				break;
			case 33: //meloetta
				bank_attacker = new_battlestruct->various.cmd49_safeattacker_bank;
				if (MOVE_WORKED && current_move == MOVE_RELIC_SONG &&
						!battle_participants[bank_attacker].status2.transformed)
				{
					u16* species = &battle_participants[bank_attacker].species;
					if (*species == POKE_MELOETTA_ARIA)
					{
						effect = 1;
						new_battlestruct->various.var1 = POKE_MELOETTA_PIROUETTE;
					}
					else if (*species == POKE_MELOETTA_PIROUETTE)
					{
						effect = 1;
						new_battlestruct->various.var1 = POKE_MELOETTA_ARIA;
					}
					if (effect)
					{
						new_battlestruct->various.var2 = 0x21E;
						battle_scripting.active_bank = bank_attacker;
						bs_push_current(&zen_change_bs);
					}
				}
				INC_END_EVENTS
				break;
			case 34: //clear move effect struct
				memset(&new_battlestruct->move_effect, 0, sizeof(struct move_effects));
				INC_END_EVENTS
				break;
			case 35: //dancer & instruct
			{
				if (new_battlestruct->various.original_dancer != 0 && new_battlestruct->various.original_dancer != 5)
				{
					while (new_battlestruct->various.secondary_dancer < no_of_all_banks && !effect)
					{
						new_battlestruct->various.secondary_dancer++;
						u8 dancer_to_check = new_battlestruct->various.secondary_dancer - 1;
						if (battle_participants[dancer_to_check].current_hp &&
								check_ability(dancer_to_check, ABILITY_DANCER) &&
								new_battlestruct->various.original_dancer != new_battlestruct->various.secondary_dancer)
						{
							bank_attacker = dancer_to_check;
							bank_target = get_target_of_move(current_move, 0, 0);
							set_attacking_move_type();
							attack_iteration_cleanup();
							hitmarker &= 0xFDF1E1FF;
							hitmarker |= HITMARKER_NO_PPDEDUCT;
							battle_scripting.cmd49_state_tracker = 0;
							if (current_move != MOVE_PETAL_DANCE)
							{
								battlescripts_curr_instruction = get_move_battlescript_ptr(current_move);
							}
							else
							{
								battlescripts_curr_instruction = get_move_battlescript_ptr(MOVE_POUND);
							}

							bs_push_current((void*) (0x82DB87D));
							effect = 1;
							break;
						}
					}
				}
				if (!effect)
				{
					INC_END_EVENTS
				}
				break;
			}
			case 36: //get burnt by Beak Blast, JeremyZ
			{
				if (new_battlestruct->bank_affecting[bank_target].beak_blast_charge == 2 &&
						does_move_make_contact(current_move, bank_attacker) && MOVE_WORKED &&
						(special_statuses[bank_target].moveturn_losthp) &&
						battle_participants[bank_attacker].current_hp && !cant_become_burned(bank_attacker, 0))
				{
					new_battlestruct->move_effect.effect1 = MOVEEFFECT_BRN | MOVEEFFECT_AFFECTSUSER;
					bs_push_current(BS_BEAKBLAST);
					hitmarker |= HITMAKRER_IGNORE_SAFEGUARD;
					effect = 1;
				}
				INC_END_EVENTS
				break;
			}
			case 37: //set Shell Trap, JeremyZ
			{
				if (new_battlestruct->bank_affecting[bank_target].shell_trap_charge == 2 &&
						(move_table[current_move].split & photon_geyser_special(current_move)) == MOVE_PHYSICAL &&
						(bank_attacker ^ bank_target) != 2 && MOVE_WORKED &&
						(special_statuses[bank_target].moveturn_losthp))
				{
					new_battlestruct->bank_affecting[bank_target].shell_trap_charge = 3;
					effect = 1;
				}
				INC_END_EVENTS
				break;
			}
			case 38: //set Rage Powder, JeremyZ
			{
				if (current_move == MOVE_RAGE_POWDER)
					new_battlestruct->bank_affecting[bank_attacker].rage_powder = 1;
				else
					new_battlestruct->bank_affecting[bank_attacker].rage_powder = 0;
				INC_END_EVENTS
				break;
			}
			case 39: //Clanging Scales & Clangorous Soulblaze, JeremyZ
			{
				if ((current_move == MOVE_CLANGING_SCALES || current_move == MOVE_Z_KOMMO_O) && clanging_scales_stat())
					effect = 1;
				INC_END_EVENTS
				break;
			}
			default:
				battle_scripting.cmd49_state_tracker = case_max;
		}

		if (arg1 == 1 && effect == 0)
			battle_scripting.cmd49_state_tracker = case_max;
		else if (arg1 == 2 && arg2 == battle_scripting.cmd49_state_tracker)
			battle_scripting.cmd49_state_tracker = case_max;
		if (battle_scripting.cmd49_state_tracker >= case_max)
			break;
	}

	if (battle_scripting.cmd49_state_tracker >= case_max && effect == 0)
		battlescripts_curr_instruction += 3;
}

bool healblock_forbidden_moves(u16 move, u8 with_leechseed)
{
    static const u16 healthblock_forbidden_moves[] = {MOVE_ABSORB,MOVE_MEGA_DRAIN,MOVE_GIGA_DRAIN,MOVE_LEECH_LIFE
			,MOVE_DRAINING_KISS,MOVE_DRAIN_PUNCH,MOVE_DREAM_EATER
			,MOVE_HORN_LEECH,MOVE_OBLIVION_WING,MOVE_PARABOLIC_CHARGE
			,MOVE_MILK_DRINK,MOVE_HEAL_PULSE,MOVE_REST,MOVE_RECOVER
			,MOVE_MOONLIGHT,MOVE_MORNING_SUN,MOVE_SLACK_OFF,MOVE_SYNTHESIS
			,MOVE_ROOST,MOVE_SOFTBOILED,0xFFFF};

	if (find_move_in_table(move, healthblock_forbidden_moves))
		return 1;
	else if (move == MOVE_LEECH_SEED && with_leechseed)
		return 1;
	return 0;
}

bool gravity_forbidden_move(u16 move)
{
	static const u16 gravity_forbidden_moves[] = {MOVE_TELEKINESIS, MOVE_MAGNET_RISE, MOVE_SPLASH, MOVE_BOUNCE,
			MOVE_FLY, MOVE_FLYING_PRESS, MOVE_JUMP_KICK, MOVE_HIGH_JUMP_KICK, MOVE_SKY_DROP, 0xFFFF};
	if (find_move_in_table(move, gravity_forbidden_moves))
		return 1;
	return 0;
}

bool embargo_forbidden_move(u16 move)
{
	if (move == MOVE_FLING)
		return 1;
	return 0;
}

bool aromaveil_affected_move(u16 move)
{
	if (move == MOVE_TORMENT || move == MOVE_TAUNT || move == MOVE_HEAL_BLOCK || move == MOVE_DISABLE ||
			move == MOVE_ATTRACT || move == MOVE_ENCORE)
		return 1;
	return 0;
}

void check_and_set_parental_bond();

u8 check_if_cannot_attack(void)
{
	u8 effect = 0;
	check_and_set_parental_bond();
	struct battle_participant* attacker_struct = &battle_participants[bank_attacker];
	u8* state_tracker = &battle_stuff_ptr->atk_canceller_state_tracker;
	while (effect == 0)
	{
		switch (*state_tracker)
		{
			case 0: //flag clear
				attacker_struct->status2.destinny_bond = 0;
				status3[bank_attacker].grudge = 0;
				new_battlestruct->bank_affecting[active_bank].head_blown = 0; //JeremyZ
				break;
			case 1: //check if asleep
				if (check_ability(bank_attacker, ABILITY_COMATOSE))
				{
					attacker_struct->status.flags.sleep = 1;
					break;
				}
				if (attacker_struct->status.flags.sleep)
				{
					if (uproar_wakeup_check(bank_attacker))
					{
						effect = 2;
						attacker_struct->status.flags.sleep = 0;
						attacker_struct->status2.nightmare = 0;
						battle_communication_struct.multistring_chooser = 1;
						bs_push_current((void*) 0x82DB220);
					}
					else
					{
						attacker_struct->status.flags.sleep--;
						if (!attacker_struct->status.flags.sleep || (check_ability(bank_attacker, ABILITY_EARLY_BIRD) &&
								!(--attacker_struct->status.flags.sleep)))
						{
							effect = 2;
							attacker_struct->status2.nightmare = 0;
							battle_communication_struct.multistring_chooser = 0;
							bs_push_current((void*) 0x82DB220);
						}
						else if (current_move != MOVE_SLEEP_TALK && current_move != MOVE_SNORE)
						{
							effect = 1;
							hitmarker |= HITMARKER_IMMOBILE_DUE_TO_STATUS;
							battlescripts_curr_instruction = (void*) 0x82DB213;
						}
					}
				}
				break;
			case 2: //check if frozen
				if (attacker_struct->status.flags.freeze)
				{
					if (percent_chance(20))
					{
						effect = 2;
						attacker_struct->status.flags.freeze = 0;
						battle_communication_struct.multistring_chooser = 0;
						bs_push_current((void*) 0x82DB277);
					}
					else if (!find_move_in_table(current_move, user_thawing_moves))
					{
						effect = 1;
						hitmarker |= HITMARKER_IMMOBILE_DUE_TO_STATUS;
						battlescripts_curr_instruction = (void*) 0x82DB26A;
					}
				}
				break;
			case 3: //check truant
				if (check_ability(bank_attacker, ABILITY_TRUANT) &&
						(disable_structs[bank_attacker].truant_counter & 0x80))
				{
					battle_communication_struct.multistring_chooser = 0;
					battlescripts_curr_instruction = (void*) 0x082DB6AD;
					move_outcome.missed = 1;
					effect = 3;
				}
				break;
			case 4: //check recharge
				if (attacker_struct->status2.recharge)
				{
					battle_communication_struct.move_effect = 0;
					attacker_struct->status2.recharge = 0;
					disable_structs[bank_attacker].recharge_counter = 0;
					battlescripts_curr_instruction = (void*) 0x82D9462;
					effect = 3;
				}

				break;
			case 5: //check flinched
				if (attacker_struct->status2.flinched)
				{
					attacker_struct->status2.flinched = 0;
					battlescripts_curr_instruction = (void*) 0x82DB29B;
					effect = 3;
					protect_structs[bank_attacker].flag2_flinch_immobility = 1;
				}
				break;
			case 6: //check if attack is disabled
				if (!SEPARATE_COURSE && disable_structs[bank_attacker].disabled_move == current_move && current_move)
				{
					protect_structs[bank_attacker].flag1_used_disabled_move = 1;
					battle_scripting.active_bank = bank_attacker;
					battlescripts_curr_instruction = (void*) 0x82DAE14;
					effect = 3;
				}
				break;
			case 7: //check if can't use move due to taunt
				if (disable_structs[bank_attacker].taunt_timer && move_table[current_move].split == 2)
				{
					effect = 3;
					protect_structs[bank_attacker].flag2_used_taunted_move = 1;
					battlescripts_curr_instruction = (void*) 0x82DB0A4;
				}
				break;
			case 8: //check imprisioned
				if (!SEPARATE_COURSE && check_if_imprisioned(bank_attacker, current_move))
				{
					effect = 3;
					protect_structs[bank_attacker].flag1_used_imprisoned_move = 1;
					battlescripts_curr_instruction = (void*) 0x82DB176;
				}
				break;
			case 9: //check heal block
				if (new_battlestruct->bank_affecting[bank_attacker].heal_block &&
						healblock_forbidden_moves(current_move, 0))
				{
					effect = 4;
					battlescripts_curr_instruction = BS_HEALBLOCK_PREVENTS;
				}
				break;
			case 10: //check gravity
				if (new_battlestruct->field_affecting.gravity && gravity_forbidden_move(current_move))
				{
					effect = 4;
					battlescripts_curr_instruction = BS_GRAVITY_PREVENTS;
				}
				break;
			case 11: //check embargo
				if (new_battlestruct->bank_affecting[bank_attacker].embargo && embargo_forbidden_move(current_move))
				{
					effect = 4;
					battlescripts_curr_instruction = BS_EMBARGO_PREVENTS;
				}
				break;
			case 12: //check confusion
				if (attacker_struct->status2.confusion)
				{
					attacker_struct->status2.confusion--;
					if (attacker_struct->status2.confusion == 0)
					{
						bs_push_current((void*) 0x82DB300); //snapped out of confusion
					}
					else if (percent_chance(67)) //manages to hit the target
					{
						bs_push_current((void*) 0x82DB2BD);
						battle_communication_struct.multistring_chooser = 0;
					}
					else //hits itself
					{
						battlescripts_curr_instruction = (void*) 0x82DB2BD;
						battle_communication_struct.multistring_chooser = 1;
						bank_target = bank_attacker;
						damage_calc(MOVE_CONFUSION_DMG, TYPE_EGG, bank_attacker, bank_attacker, 0x64);
						protect_structs[bank_attacker].flag1_confusion_self_damage = 1;
						hitmarker |= HITMARKER_IMMOBILE_DUE_TO_STATUS;
					}
					effect = 1;
				}
				break;
			case 13: //check paralysis
				if (attacker_struct->status.flags.paralysis && percent_chance(25))
				{
					effect = 1;
					protect_structs[bank_attacker].flag0_prlz_immobility = 1;
					battlescripts_curr_instruction = (void*) 0x82DB28B;
					hitmarker |= HITMARKER_IMMOBILE_DUE_TO_STATUS;
				}
				break;
			case 14: //check infatuation
				if (attacker_struct->status2.in_love)
				{
					battle_scripting.active_bank = get_bank_in_love(attacker_struct->status2.in_love);
					if (percent_chance(50)) //in love cannot attack
					{
						bs_push((void*) 0x82DB334, (void*) 0x82DB327);
						protect_structs[bank_attacker].flag1_love_immobility = 1;
						effect = 3;
					}
					else
					{
						bs_push_current((void*) 0x82DB327);
						effect = 1;
					}
				}
				break;
			case 15: //check bide
				if (attacker_struct->status2.bide)
				{
					attacker_struct->status2.bide--;
					if (attacker_struct->status2.bide == 0) //unleashing energy
					{
						if (taken_damage[bank_attacker] == 0) //got no damage
							battlescripts_curr_instruction = (void*) 0x82DADC4;
						else
						{
							current_move = MOVE_BIDE;
							battle_scripting.bide_damage = taken_damage[bank_attacker] * 2;
							battlescripts_curr_instruction = (void*) 0x82DAD7C;
							bank_target = hurt_by[bank_attacker];
							if (!is_bank_present(bank_target)) //poke's not longer on the battlefield
								bank_target = get_target_of_move(MOVE_BIDE, 1, 1);
						}
					}
					else //storing energy
						battlescripts_curr_instruction = (void*) 0x82DAD71;
					effect = 1;
				}
				break;
			case 16: //aroma veil protection
				if (aromaveil_affected_move(current_move))
				{
					u8 aroma = check_field_for_ability(ABILITY_AROMA_VEIL, get_bank_side(bank_attacker), 1);
					if (aroma)
					{
						effect = 4;
						battlescripts_curr_instruction = BS_AROMAVEIL_PREVENTS;
						last_used_ability = ABILITY_AROMA_VEIL;
						record_usage_of_ability(aroma - 1, ABILITY_AROMA_VEIL);
					}
				}
				break;
			case 17: //check thawing effect
				if (attacker_struct->status.flags.freeze && find_move_in_table(current_move, user_thawing_moves))
				{
					attacker_struct->status.flags.freeze = 0;
					bs_push_current((void*) 0x82DB277);
					battle_communication_struct.multistring_chooser = 1;
				}
				break;
			case 18: //weather prevents move usage, JeremyZ
				if (weather_abilities_effect() && battle_weather.flags.heavy_rain &&
						get_attacking_move_type() == TYPE_FIRE)
				{
					effect = 3;
					battlescripts_curr_instruction = BS_HEAVYRAIN_PREVENTS;
				}
				else if (weather_abilities_effect() && battle_weather.flags.harsh_sun &&
						get_attacking_move_type() == TYPE_WATER)
				{
					effect = 3;
					battlescripts_curr_instruction = BS_HARSHSUN_PREVENTS;
				}
				break;
			case 19: //powder
				if (new_battlestruct->bank_affecting[bank_attacker].powder && get_attacking_move_type() == TYPE_FIRE)
				{
					new_battlestruct->bank_affecting[bank_attacker].powder = 0;
					effect = 1;
					damage_loc = get_1_4_of_max_hp(bank_attacker);
					battlescripts_curr_instruction = BS_POWDER;
				}
				break;
			case 20: //Shell Trap, JeremyZ
				if (new_battlestruct->bank_affecting[bank_attacker].shell_trap_charge != 3 &&
						current_move == MOVE_SHELL_TRAP)
				{
					effect = 3; //effect = 1或2都不可以，暂时不知道为什么
					battlescripts_curr_instruction = BS_HARSHSUN_PREVENTS; //Needs Revision
				}
				break;
			case 21: //Psychic Terrain, JeremyZ
				if (new_battlestruct->field_affecting.psychic_terrain && GROUNDED(bank_target) &&
						get_priority(current_move, bank_attacker) >= 1 &&
						get_bank_side(bank_target) != get_bank_side(bank_attacker))
				{
					effect = 1;
					battlescripts_curr_instruction = BS_CANTUSE_PRIORITY_TERRAIN;
				}
				break;
			case 22: //Queenly Majesty, Dazzling
			{
				u8 QM_present = check_field_for_ability(ABILITY_QUEENLY_MAJESTY, get_bank_side(bank_attacker), 1);
				u8 DZ_present = check_field_for_ability(ABILITY_DAZZLING, get_bank_side(bank_attacker), 1);

				if ((QM_present || DZ_present) &&
					get_priority(current_move, bank_attacker) >= 1 &&
					get_bank_side(bank_target) != get_bank_side(bank_attacker))
				{
					if (QM_present) {
						bank_target = QM_present - 1;
						record_usage_of_ability(bank_target, ABILITY_QUEENLY_MAJESTY);
					}
					else {
						bank_target = DZ_present - 1;
						record_usage_of_ability(bank_target, ABILITY_DAZZLING);
					}
					effect = 1;
					battlescripts_curr_instruction = BS_CANTUSE_PRIORITY;
				}
				break;
			}
			case 23: //Destiny Bond
				if (current_move == MOVE_DESTINY_BOND && last_used_moves[bank_attacker] == MOVE_DESTINY_BOND)
				{
					move_outcome.failed = 1;
					effect = 1;
					battlescripts_curr_instruction = (void*) 0x082D9F1A;
				}
		}
		if (effect == 2)
		{
			active_bank = bank_attacker;
			bb2_setattributes_in_battle(0, REQUEST_STATUS_BATTLE, 0, 4, &attacker_struct->status);
			mark_buffer_bank_for_execution(active_bank);
		}
		else if (effect >= 3)
		{
			hitmarker |= HITMARKER_IMMOBILE_DUE_TO_STATUS;
			reset_multiple_turn_effects(bank_attacker);
		}
		*state_tracker += 1;
		if (*state_tracker > 23 && effect == 0)
			break;
	}
	return effect;
}

u8 immune_to_powder_moves(u8 def_bank, u16 move)
{
	u8 immune = 0;
	if (find_move_in_table(move, powder_moves))
	{
		if (is_of_type(def_bank, TYPE_GRASS))
		{
			immune = 1;
			battlescripts_curr_instruction = bs_printmove_failed;
		}
		else if (get_item_effect(def_bank, 1) == ITEM_EFFECT_SAFETYGOOGLES)
		{
			immune = 1;
			record_usage_of_item(def_bank, ITEM_EFFECT_SAFETYGOOGLES);
			battlescripts_curr_instruction = bs_printmove_failed;
		}
	}
	return immune;
}

const u8 parental_ban_list[] = {23, 39, 47, 66, 67, 70, 71, 98, 116, 125, 142, 157, 0xFF};

bool is_in_parental_bond_banlist()
{
	u8 effect = move_table[current_move].script_id;
	bool is_banned = false;
	for (u8 i = 0; parental_ban_list[i] != 0xFF; i++)
	{
		if (effect == parental_ban_list[i])
		{
			is_banned = true;
			break;
		}
	}
	if (current_move == MOVE_ENDEAVOR || current_move == MOVE_FINAL_GAMBIT)
	{
		is_banned = true;
	}
	return is_banned;
}

void check_and_set_parental_bond(void)
{
	if (check_ability(bank_attacker, ABILITY_PARENTAL_BOND) && new_battlestruct->various.parental_bond_mode == 0)
	{
		if (does_move_target_multiple() || is_in_parental_bond_banlist())
		{
			new_battlestruct->various.parental_bond_mode = PBOND_DONT_SET;
		}
		else if (DAMAGING_MOVE(current_move))
		{
			new_battlestruct->various.parental_bond_mode = PBOND_PARENT;
			multihit_counter = 2;
		}
	}
}

bool check_if_twoturns_move(u16 move)
{
	u8 script_id = move_table[move].script_id;
	if (script_id == 71 /*all two turns moves' effect */ || script_id == 157 /*Sky Drop's effect*/)
		return 1;
	return 0;
}

bool is_there_no_target(u16 move)
{
	if (!is_bank_present(bank_target) && !is_bank_present(bank_target ^ 2))
	{
		if (move_table[move].target == move_target_foes_and_ally)
		{
			if (is_bank_present(bank_attacker ^ 2))
				return 0;
		}
		return 1;
	}
	return 0;
}

u32 get_z_moves(u32 move);

void atk00_move_canceller(void)
{
	if (battle_outcome)
	{
		battle_state_mode = 0xC;
		return;
	}
	if (battle_participants[bank_attacker].current_hp == 0 && !(hitmarker & HITMARKER_NO_ATTACKSTRING))
	{
		hitmarker |= HITMARKER_IMMOBILE_DUE_TO_STATUS;
		battlescripts_curr_instruction = (void*) 0x082D8A4E; //bs_endturn and end
		return;
	}
	if (is_there_no_target(current_move))
	{
		battlescripts_curr_instruction = bs_printmove_failed; //no target, but it failed
		return;
	}
	else if (check_if_cannot_attack())
		return;
	else if (ability_battle_effects(2, bank_target, 0, 0, 0))
		return;
	else if (ability_battle_effects(3, bank_target, 0, 0, 0))
		return;
	else if (immune_to_powder_moves(bank_target, current_move))
		return;
	else if (check_ability(bank_attacker, ABILITY_PRANKSTER) &&
			bank_attacker != bank_target &&
			is_of_type(bank_target, TYPE_DARK) &&
			!DAMAGING_MOVE(current_move)) //Dark type blocks Prankster
	{
		battlescripts_curr_instruction = bs_printmove_failed;
		return;
	}
	else if (!(hitmarker & HITMARKER_NO_PPDEDUCT) &&
			battle_participants[bank_attacker].current_pp[current_move_position] == 0 &&
			current_move != MOVE_STRUGGLE && !battle_participants[bank_attacker].status2.multiple_turn_move &&
			((hitmarker & (HITMARKER_NO_ATTACKSTRING | 0x800000)) == 0) && new_battlestruct->various.magicbounce == 0)
	{
		move_outcome.missed = 1;
		battlescripts_curr_instruction = (void*) 0x082DB07A; //no pp bs
		return;
	}
	hitmarker &= 0xFF7FFFFF;
	if (!(hitmarker & HITMARKER_OBEYS) && !battle_participants[bank_attacker].status2.multiple_turn_move)
	{
		u8 disobedient = is_poke_disobedient();
		if (disobedient == 2)
		{
			hitmarker |= HITMARKER_OBEYS;
			return;
		}
		else if (disobedient)
		{
			move_outcome.missed = 1;
			return;
		}
	}
	hitmarker |= HITMARKER_OBEYS;
	if (protect_structs[bank_target].flag0_bouncemove &&
			move_table[current_move].move_flags.flags.affected_by_magic_coat &&
			new_battlestruct->various.magicbounce == 0) //magic coat check
	{
		protect_structs[bank_target].flag0_bouncemove = 0;
		last_used_moves[bank_attacker] = current_move;
		pressure_pp_lose(bank_attacker, bank_target, MOVE_MAGIC_COAT);
		new_battlestruct->various.magicbounce = 1;
		bs_push_current((void*) 0x082DB194);
		return;
	}
	else if ((battle_participants[bank_target].ability_id == ABILITY_MAGIC_BOUNCE &&
			has_ability_effect(bank_target, 1)) && move_table[current_move].move_flags.flags.affected_by_magic_coat &&
			new_battlestruct->various.magicbounce == 0 && !protect_affects(current_move, 0) &&
			!SEMI_INVULNERABLE(bank_target))
	{
		new_battlestruct->various.magicbounce = 1;
		last_used_moves[bank_attacker] = current_move;
		bs_push_current(BS_MAGICBOUNCE);
		return;
	}
	for (u8 i = 0; i < no_of_all_banks; i++)
	{
		if (protect_structs[turn_order[i]].flag0_stealmove &&
				move_table[current_move].move_flags.flags.affected_by_snatch)
		{
			new_battlestruct->various.original_dancer = 5; // dancer cannot activate on a snatched move
			pressure_pp_lose(bank_attacker, bank_target, MOVE_SNATCH);
			protect_structs[turn_order[i]].flag0_stealmove = 0;
			battle_scripting.active_bank = turn_order[i];
			bs_push_current((void*) 0x82DB1AC);
			return;
		}
	}
	if (special_statuses[bank_target].lightning_rod_redirected)
	{
		special_statuses[bank_target].lightning_rod_redirected = 0;
		if (new_battlestruct->various.stormdrain)
		{
			new_battlestruct->various.stormdrain = 0;
			last_used_ability = ABILITY_STORM_DRAIN;
		}
		else
			last_used_ability = ABILITY_LIGHTNING_ROD;
		bs_push_current((void*) 0x082DB53E);
		record_usage_of_ability(bank_target, last_used_ability);
		return;
	}
	if (protect_affects(current_move, 0) && !(current_move == MOVE_CURSE && is_of_type(bank_attacker, TYPE_GHOST)))
	{
		u8 twoturn = check_if_twoturns_move(current_move);
		if (!twoturn || (twoturn &&
				battle_participants[bank_attacker].status2.multiple_turn_move)) //not two turn or twoturn's attacking turn
		{
			battle_communication_struct.field6 = 1;
			move_outcome.missed = 1;
			move_hit_with_pbs[bank_target] = 0;
			move_type_hit_with_pbs[bank_target] = 0;
			if (!twoturn)
				reset_multiple_turn_effects(bank_attacker);
		}
	}
	battlescripts_curr_instruction++;
	if (get_z_moves(current_move))
	{
		if (bank_attacker == 0)
		{    /*	if(bank_attacker==0)
				{
					new_battlestruct->mega_related.z_happened_pbs|=0x1;
					objects[new_battlestruct->mega_related.trigger_id].private[ANIM_STATE]=DISABLE;
				}
				else if(bank_attacker==2)
				{
					new_battlestruct->mega_related.z_happened_pbs|=0x5;
					objects[new_battlestruct->mega_related.trigger_id].private[ANIM_STATE]=DISABLE;
				}
			*/
			if (!battle_flags.multibattle)
			{
				new_battlestruct->mega_related.z_happened_pbs |= 0x5;
			}
			else
			{
				new_battlestruct->mega_related.z_happened_pbs |= 0x1;
			}
			objects[new_battlestruct->mega_related.trigger_id].private[ANIM_STATE] = DISABLE;
		}
		else if (bank_attacker == 2)
		{
			if (!battle_flags.multibattle)
			{
				new_battlestruct->mega_related.z_happened_pbs |= 0x5;
			}
			else
			{
				new_battlestruct->mega_related.z_happened_pbs |= 0x4;
			}
			objects[new_battlestruct->mega_related.trigger_id].private[ANIM_STATE] = DISABLE;
		}
		else if (!(new_battlestruct->mega_related.z_happened_pbs &
				(BIT_GET(bank_attacker) | BIT_GET(bank_attacker ^ 2))))
		{
			new_battlestruct->mega_related.z_happened_pbs |= BIT_GET(bank_attacker);
		}
		//battlescripts_curr_instruction = BS_START_Z;
		bs_push_current(BS_START_Z);
		
		//If user is of ability Illusion, then it turns off illusion when using Z-move.
		if (check_ability(bank_attacker, ABILITY_ILLUSION) &&
				new_battlestruct->bank_affecting[bank_attacker].illusion_on)
		{
			new_battlestruct->bank_affecting[bank_attacker].illusion_on = 0;
			new_battlestruct->bank_affecting[bank_attacker].illusion_hit = 1;
			bs_push_current(BS_ILLUSION_OFF2);
			battle_participants[bank_attacker].status2.transformed = 0;
		}		
	}
}

void atk88_drain_damage(void)
{
	s32 damage = 0;
	if (!(new_battlestruct->bank_affecting[bank_attacker].heal_block && healblock_forbidden_moves(current_move, 0)))
	{
		u8 percent_restore = move_table[current_move].arg1;
		u8 rounding = move_table[current_move].arg2;
		damage = percent_lose(hp_dealt, 100 - percent_restore);
		if (rounding && __umodsi3(hp_dealt, damage * ((100 * hp_dealt + 100 - percent_restore) / 100)) &&
				damage != hp_dealt)
			damage++;
		if (get_item_effect(bank_attacker, 1) == ITEM_EFFECT_BIGROOT)
			damage = percent_boost(damage, 30);
	}
	damage_loc = ATLEAST_ONE(damage) * -1;
	battlescripts_curr_instruction++;
}

bool symbiosis_effect(u8 bank)
{
	if (new_battlestruct->various.trigger_symbiosis)
	{
		new_battlestruct->various.trigger_symbiosis = 0;
		u8 ally_bank = bank ^2;
		if (get_ally_ability(bank, 0) == ABILITY_SYMBIOSIS && try_stealing_bank_item(bank, ally_bank))
		{
			bs_push_current(BS_SYMBIOSIS);
			record_usage_of_ability(ally_bank, ABILITY_SYMBIOSIS);
			bank_partner_atk = battle_scripting.active_bank = bank, bank_partner_def = ally_bank; //for animation and strings
			return 1;
		}
	}
	return 0;
}

void setup_berry_consume_buffers(u8 bank);

void atk6A_remove_item(void)
{
	u8 bank = get_battle_bank(read_byte(battlescripts_curr_instruction + 1));
	battlescripts_curr_instruction += 2;
	u16* item = &battle_participants[bank].held_item;
	if (*item)
	{
		new_battlestruct->various.trigger_symbiosis = 1;
		set_unburden(bank);
		battle_stuff_ptr->used_held_items[bank] = *item;
		new_battlestruct->various.recently_used_item = *item;
		*item = 0;
	}
	if (!berry_eaten(bank, true) && !(symbiosis_effect(bank)))
	{
		active_bank = bank;
		bb2_setattributes_in_battle(0, REQUEST_HELDITEM_BATTLE, 0, 2, item);
		mark_buffer_bank_for_execution(bank);
	}
}

void atkA3_disable_move(void)
{
	u16 move = last_used_moves[bank_target];
	s8 position = get_move_position(bank_target, move);
	if (move && position != -1 && disable_structs[bank_target].disabled_move == 0 &&
			battle_participants[bank_target].current_pp[position])
	{
		u16 move = battle_participants[bank_target].moves[position];
		move_to_buff1(move);
		disable_structs[bank_target].disabled_move = move;
		disable_structs[bank_target].disable_timer = 4;
		battlescripts_curr_instruction += 5;
	}
	else
		battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction + 1);
}

void atkA4_encore_move(void)
{
	u16 move = last_used_moves[bank_target];
	s8 position = get_move_position(bank_target, move);
	static const u16 encore_forbidden_moves[] = {MOVE_STRUGGLE, MOVE_ENCORE, MOVE_MIRROR_MOVE, MOVE_MIMIC,
			MOVE_TRANSFORM, MOVE_SKETCH, 0xFFFF};
	if (move && position != -1 && disable_structs[bank_target].encored_move == 0 &&
			battle_participants[bank_target].current_pp[position] && !find_move_in_table(move, encore_forbidden_moves))
	{
		battlescripts_curr_instruction += 5;
		disable_structs[bank_target].encored_move = move;
		disable_structs[bank_target].encore_timer = 3;
		disable_structs[bank_target].encored_index = position;
	}
	else
		battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction + 1);
}

void atkD0_set_taunt(void)
{
	void* failjump = (void*) read_word(battlescripts_curr_instruction + 1);
	if (disable_structs[bank_target].taunt_timer || ability_battle_effects(17, bank_target, ABILITY_AROMA_VEIL, 1, 0))
		battlescripts_curr_instruction = failjump;
	else if (battle_participants[bank_target].ability_id == ABILITY_OBLIVIOUS && has_ability_effect(bank_target, 1))
	{
		battlescripts_curr_instruction = failjump;
		record_usage_of_ability(bank_target, ABILITY_OBLIVIOUS);
	}
	else
	{
		disable_structs[bank_target].taunt_timer = 3;
		battlescripts_curr_instruction += 5;
	}
}

void atkB5_furycutter_calc(void)
{
	u8* cutter_timer = &disable_structs[bank_attacker].fury_cutter_timer;
	if (!MOVE_WORKED)
	{
		*cutter_timer = 0;
		battlescripts_curr_instruction = (void*) 0x82D8A5E;
	}
	else
	{
		if (last_used_moves[bank_attacker] != MOVE_FURY_CUTTER)
			*cutter_timer = 0;

		if (*cutter_timer < 4)
			*cutter_timer += 1;
		dynamic_base_power = move_table[current_move].base_power * *cutter_timer;
		battlescripts_curr_instruction++;
	}
}

void atkEB_set_type_to_terrain(void)
{
	u8 terrain_type;
	if (new_battlestruct->field_affecting.grassy_terrain)
		terrain_type = TYPE_GRASS;
	else if (new_battlestruct->field_affecting.misty_terrain)
		terrain_type = TYPE_FAIRY;
	else if (new_battlestruct->field_affecting.electic_terrain)
		terrain_type = TYPE_ELECTRIC;
	else if (new_battlestruct->field_affecting.psychic_terrain)
		terrain_type = TYPE_PSYCHIC;
	else
		terrain_type = terrain_to_type_table[battle_env_bg];
	if (is_of_type(bank_attacker, terrain_type))
		battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction + 1);
	else
	{
		battlescripts_curr_instruction += 5;
		set_type(bank_attacker, terrain_type);
		battle_text_buff1[0] = 0xFD;
		battle_text_buff1[1] = 3;
		battle_text_buff1[2] = terrain_type;
		battle_text_buff1[3] = 0xFF;
	}
}

void atk0F_resultmessage(void)
{
	if (battle_execution_buffer == 0)
	{
		battlescripts_curr_instruction++;
		u16 string_id = 0;
		if (move_outcome.missed && !(move_outcome.not_affected && battle_communication_struct.field6 <= 2))
			string_id = some_strings_table[battle_communication_struct.field6];
		else if (move_outcome.super_effective && MOVE_WORKED)
			string_id = 0xDE;
		else if (move_outcome.not_very_effective && MOVE_WORKED)
			string_id = 0xDD;
		else if (move_outcome.not_affected)
			string_id = 0x1B;
		else if (move_outcome.failed)
			string_id = 0xE5;
		else if (move_outcome.one_hit_ko && MOVE_WORKED)
			string_id = 0xDA;
		if (move_outcome.endured)
		{
			move_outcome.hanged_on_using_item = 0;
			move_outcome.sturdied = 0;
			bs_push_current((void*) 0x82DB1C7);
		}
		else if (move_outcome.hanged_on_using_item && MOVE_WORKED)
		{
			move_outcome.hanged_on_using_item = 0;
			move_outcome.sturdied = 0;
			if (!last_used_item)
				last_used_item = battle_participants[bank_target].held_item;
			bs_push_current((void*) 0x82DB816);
		}
		else if (move_outcome.sturdied && MOVE_WORKED)
		{
			move_outcome.sturdied = 0;
			bs_push_current(BS_STURDYENDURES);
		}
		if (string_id)
		{
			battle_communication_struct.is_message_displayed = 1;
			prep_string(string_id, bank_attacker);
		}
	}
}

void atk70_record_ability_of_bank(void)
{
	u8 bank = get_battle_bank(read_byte(battlescripts_curr_instruction + 1));
	record_usage_of_ability(bank, battle_participants[bank].ability_id);
	battlescripts_curr_instruction += 2;
}

void atk77_set_protect_stuff(void)
{
	//Detect, Protect, Endure, King's Shield, Quick Guard, Spiky Shield, Wide Guard, Mat Block, Crafty Shield

	u8* counter = &disable_structs[bank_attacker].protect_uses;
	//check if previous move resets counter if it wasn't a 'protect' move or if it is a protect move resets counter
	u16 previous_move = last_used_moves[bank_attacker];
	u8 pr_flags = move_table[current_move].arg1;
	if (move_table[previous_move].script_id != 34 || !(pr_flags & PR_counter_incr))
		*counter = 0;

	bool fail = 0;
	u8 pr_case = move_table[current_move].arg2;
	//check if all pokemon have already moved
	if (current_move_turn == no_of_all_banks - 1)
		fail = 1;
	else
	{
		//check if it passes consecutive chance of happening
		if (pr_flags & PR_fail_chance && (*counter > 3 || protect_chance_table[*counter] < rng()))
			fail = 1;
		else
		{
			u8 atk_side = get_bank_side(bank_attacker);
			switch (pr_case)
			{
				case PR_protect:
					protect_structs[bank_attacker].flag0_protect = 1;
					break;
				case PR_endure:
					protect_structs[bank_attacker].flag0_endure = 1;
					break;
				case PR_wide_guard:
					if (new_battlestruct->side_affecting[atk_side].wide_guard)
						fail = 1;
					else
						new_battlestruct->side_affecting[atk_side].wide_guard = 1;
					break;
				case PR_quick_guard:
					if (new_battlestruct->side_affecting[atk_side].quick_guard)
						fail = 1;
					else
						new_battlestruct->side_affecting[atk_side].quick_guard = 1;
					break;
				case PR_kings_shield:
					new_battlestruct->bank_affecting[bank_attacker].kings_shield = 1;
					break;
				case PR_spiky_shield:
					new_battlestruct->bank_affecting[bank_attacker].spiky_shield = 1;
					break;
				case PR_baneful_bunker:
					new_battlestruct->bank_affecting[bank_attacker].baneful_bunker = 1;
					break;
				case PR_mat_block:
					if (new_battlestruct->side_affecting[atk_side].mat_block ||
							!disable_structs[bank_attacker].is_first_turn)
						fail = 1;
					else
						new_battlestruct->side_affecting[atk_side].mat_block = 1;
					break;
				case PR_crafty_shield:
					if (new_battlestruct->side_affecting[atk_side].crafty_shield)
						fail = 1;
					else
						new_battlestruct->side_affecting[atk_side].crafty_shield = 1;
					break;
				default:
					fail = 1;
			}
		}
	}
	//sadly move failed
	if (fail)
	{
		move_outcome.failed = 1;
		battlescripts_curr_instruction = (void*) 0x082D9F1C;
		*counter = 0;
	}
	else
	{
		battlescripts_curr_instruction++;
		if (pr_flags & PR_counter_incr)
			*counter += 1;
		//choose text to display
		if (pr_flags & PR_affects_allies)
		{
			battle_communication_struct.multistring_chooser = 2;
			move_to_buff1(current_move);
		}
		else if (pr_case == PR_endure)
			battle_communication_struct.multistring_chooser = 0;
		else
			battle_communication_struct.multistring_chooser = 1;
	}
}

void atk0C_datahpupdate(void)
{
	if (battle_execution_buffer)
	{
		return;
	}
	u8 bank = get_battle_bank(read_byte(battlescripts_curr_instruction + 1));
	battlescripts_curr_instruction += 2;
	active_bank = bank;
	bool itemheal = new_battlestruct->bank_affecting[bank].itemheal;
	new_battlestruct->bank_affecting[bank].itemheal = 0;
	if (!MOVE_WORKED && !itemheal)
	{
		if (special_statuses[bank].moveturn_losthp == 0)
			special_statuses[bank].moveturn_losthp = 0xFFFF;
	}
	else
	{
		u8 split = move_table[current_move].split;
		if (affected_by_substitute(bank) && damage_loc > 0) //JeremyZ
		{
			u8* substitute_hp = &disable_structs[bank].substitute_hp;
			if (damage_loc > *substitute_hp)
			{
				hp_dealt = *substitute_hp;
				*substitute_hp = 0;
				if (special_statuses[bank].moveturn_losthp == 0)
					special_statuses[bank].moveturn_losthp = hp_dealt;
			}
			else
			{
				*substitute_hp -= damage_loc;
				hp_dealt = damage_loc;
				if (special_statuses[bank].moveturn_losthp == 0)
					special_statuses[bank].moveturn_losthp = damage_loc;
			}
			if (*substitute_hp == 0)
			{
				bs_push_current((void*) 0x082DB6FB);
			}
		}
		else if (new_battlestruct->various.bust_mimikyu && bank == bank_target && damage_loc == 0)
		{
			special_statuses[bank].moveturn_losthp = 1;
			if (split == 0)
			{
				special_statuses[bank].moveturn_losthp_physical = 1;
			}
			else
			{
				special_statuses[bank].moveturn_losthp_special = 1;
			}
			if (not_impostered(bank))
			{
				battle_scripting.active_bank = bank;
				bs_push_current(BS_MIMIKYU_BUST);
				new_battlestruct->various.var1 = POKE_MIMIKYU_BUSTED;
				new_battlestruct->various.var2 = 0x24B;
			}
		}
		else
		{
			hitmarker &= 0xFFFFFEFF;
			u16* current_hp = &battle_participants[bank].current_hp;
			if (damage_loc >= 0) //damage is subbed
			{
				if (hitmarker & 0x20)
					hitmarker ^= 0x20;
				else
				{
					taken_damage[bank] += damage_loc;
					if (bank == bank_target)
						hurt_by[bank] = bank_attacker;
					else
						hurt_by[bank] = bank_target;
				}
				if (damage_loc >= *current_hp)
					hp_dealt = *current_hp;
				else
					hp_dealt = damage_loc;
				*current_hp -= hp_dealt;
				if (special_statuses[bank].moveturn_losthp == 0 && !(hitmarker & 0x100000))
					special_statuses[bank].moveturn_losthp = hp_dealt;
				if (split == 0 && !(hitmarker & 0x100000))
				{
					special_statuses[bank].moveturn_losthp_physical = hp_dealt;
					protect_structs[bank].physical_damage = hp_dealt;
					if (bank == bank_attacker)
					{
						special_statuses[bank].moveturn_physical_bank = bank_target;
						protect_structs[bank].counter_target = bank_target;
					}
					else
					{
						special_statuses[bank].moveturn_physical_bank = bank_attacker;
						protect_structs[bank].counter_target = bank_attacker;
					}
				}
				else if (split == 1 && !(hitmarker & 0x100000))
				{
					special_statuses[bank].moveturn_losthp_special = hp_dealt;
					protect_structs[bank].special_damage = hp_dealt;
					if (bank == bank_attacker)
					{
						special_statuses[bank].moveturn_special_bank = bank_target;
						protect_structs[bank].mirrorcoat_target = bank_target;
					}
					else
					{
						special_statuses[bank].moveturn_special_bank = bank_attacker;
						protect_structs[bank].mirrorcoat_target = bank_attacker;
					}
				}
			}
			else //damage is added
			{
				*current_hp = *current_hp + (damage_loc * (-1));
				if (*current_hp > battle_participants[bank].max_hp)
					*current_hp = battle_participants[bank].max_hp;
			}
			hitmarker &= 0xFFEFFFFF;
			active_bank = bank;
			bb2_setattributes_in_battle(0, 0x2A, 0, 2, current_hp);
			mark_buffer_bank_for_execution(active_bank);
		}
	}
}

void atkD4_wish_effect(void)
{
	u8* wish_duration = &battle_effects_duration.wish_duration[bank_attacker];
	u8* wish_bank = &battle_effects_duration.id_of_wish_user[bank_attacker];
	u8 fail = 0;
	switch (read_byte(battlescripts_curr_instruction + 1))
	{
		case 0: //prepare a wish
			if (*wish_duration)
				fail = 1;
			else
			{
				*wish_duration = 2;
				*wish_bank = battle_team_id_by_side[bank_attacker];
				u16 wish_hp = battle_participants[bank_attacker].max_hp / 2;
				if (wish_hp * 2 < battle_participants[bank_attacker].max_hp)
					wish_hp += 1;
				new_battlestruct->bank_affecting[bank_attacker].wish_hp = wish_hp;
			}
			break;
		case 1: //get wish effect
			if (battle_participants[bank_target].max_hp == battle_participants[bank_target].current_hp ||
					new_battlestruct->bank_affecting[bank_target].heal_block)
				fail = 1;
			else
			{
				battle_text_buff1[0] = 0xFD;
				battle_text_buff1[1] = 4;
				battle_text_buff1[2] = bank_target;
				battle_text_buff1[3] = *wish_bank;
				battle_text_buff1[4] = 0xFF;
				damage_loc = new_battlestruct->bank_affecting[bank_target].wish_hp * (-1);
			}
			break;
	}
	if (fail)
		battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction + 2);
	else
		battlescripts_curr_instruction += 6;
	return;
}

void atk93_ko_move(void)
{
	u8 atk_lvl = battle_participants[bank_attacker].level;
	u8 def_lvl = battle_participants[bank_target].level;
	bool fail = 0;
	if (atk_lvl < def_lvl
		|| (current_move == MOVE_SHEER_COLD && is_of_type(bank_target, TYPE_ICE)))
	{
		fail = 1;
		battle_communication_struct.multistring_chooser = 1;
	}
	else
	{
		if (check_ability(bank_target, ABILITY_STURDY))
		{
			move_outcome.missed = 1;
			battlescripts_curr_instruction = (void*) 0x082DB552;
			record_usage_of_ability(bank_target, ABILITY_STURDY);
			return;
		}
		
		u8 accuracy = atk_lvl - def_lvl + move_table[current_move].accuracy;
		if (current_move == MOVE_SHEER_COLD && !is_of_type(bank_attacker, TYPE_ICE))
			accuracy -= 10;
		
		if ((MUST_HIT(bank_attacker, bank_target)) || accuracy >= 100 || percent_chance(accuracy))
		{
			damage_loc = battle_participants[bank_target].current_hp;
			move_outcome.super_effective = 0;
			move_outcome.not_very_effective = 0;
			move_outcome.one_hit_ko = 1;
		}
		else
		{
			fail = 1;
			battle_communication_struct.multistring_chooser = 0;
		}
	}
	if (fail)
		battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction + 1);
	else
		battlescripts_curr_instruction += 5;
}

void atkA7_set_alwayshits_flag(void)
{
	status3[bank_target].always_hits = 2;
	disable_structs[bank_target].always_hits_bank = bank_attacker;
	battlescripts_curr_instruction++;
}

void atkBE_rapidspin_away(void)
{
	u8 banks_side = get_bank_side(bank_attacker);
	if (battle_participants[bank_attacker].status2.trapped_in_wrap)
	{
		battle_participants[bank_attacker].status2.trapped_in_wrap = 0;
		battle_scripting.active_bank = bank_target;
		move_to_buff1(battle_stuff_ptr->binding_move[bank_attacker]);
		bs_push_current((void*) 0x82DAFC5);
	}
	else if (status3[bank_attacker].leech_seed)
	{
		status3[bank_attacker].leech_seed = 0;
		status3[bank_attacker].leech_seed_hp_receiver = 0;
		bs_push_current((void*) 0x82DAFD6);
	}
	else if (side_affecting_halfword[banks_side].spikes_on)
	{
		side_affecting_halfword[banks_side].spikes_on = 0;
		side_timers[banks_side].spikes_amount = 0;
		bs_push_current((void*) 0x82DAFDD);
	}
	else if (new_battlestruct->side_affecting[banks_side].toxic_spikes_psn)
	{
		new_battlestruct->side_affecting[banks_side].toxic_spikes_psn = 0;
		new_battlestruct->side_affecting[banks_side].toxic_spikes_badpsn = 0;
		battle_communication_struct.multistring_chooser = 2;
		bs_push_current(BS_RAPIDSPIN_SPINS);
	}
	else if (new_battlestruct->side_affecting[banks_side].stealthrock)
	{
		new_battlestruct->side_affecting[banks_side].stealthrock = 0;
		battle_communication_struct.multistring_chooser = 0;
		bs_push_current(BS_RAPIDSPIN_SPINS);
	}
	else if (new_battlestruct->side_affecting[banks_side].sticky_web)
	{
		new_battlestruct->side_affecting[banks_side].sticky_web = 0;
		battle_communication_struct.multistring_chooser = 1;
		bs_push_current(BS_RAPIDSPIN_SPINS);
	}
	else
		battlescripts_curr_instruction++;
}

u8 can_select_this_random_move(u16 move)
{
	u8 can = 1;
	u8 script_id = move_table[move].script_id;
	switch (current_move)
	{
		case MOVE_ASSIST:
			if (script_id == 34 || script_id == 73 || script_id == 72 || script_id == 123 || script_id ==
					99) //fly/dig/dive plus protect-like moves plus roar/whirlwind plus trick/switcheroo plus covet/thief
				can = 0;
			else if (move == MOVE_BESTOW || move == MOVE_BOUNCE || move == MOVE_DRAGON_TAIL ||
					move == MOVE_CIRCLE_THROW || move == MOVE_FOCUS_PUNCH || move == MOVE_RAGE_POWDER ||
					move == MOVE_SHADOW_FORCE || move == MOVE_FEINT || move == MOVE_PHANTOM_FORCE ||
					move == MOVE_DESTINY_BOND || move == MOVE_HOLD_HANDS || move == MOVE_TRANSFORM)
				can = 0;
			else
				goto SHAREDWITHASSIST;
			break;
		case MOVE_SLEEP_TALK:
			if (script_id == 71) //two-turn moves
			{
				can = 0;
				break;
			}
		SHAREDWITHASSIST:
			if (move == MOVE_ASSIST || move == MOVE_SLEEP_TALK || move == MOVE_BELCH || move == MOVE_BIDE ||
					move == MOVE_CHATTER || move == MOVE_COPYCAT || move == MOVE_HOLD_HANDS || move == MOVE_ME_FIRST ||
					move == MOVE_METRONOME || move == MOVE_MIMIC || move == MOVE_MIRROR_MOVE ||
					move == MOVE_NATURE_POWER || move == MOVE_SKETCH || move == MOVE_STRUGGLE)
				can = 0;
			break;
	}
	return can;
}

u32 random_value(u32);

void atkDE_assistmovechoose(void)
{
	struct pokemon* poke = get_party_ptr(bank_attacker);
	u8 viable_pokes = 0;
	for (u8 i = 0; i < 6; i++)
	{
		if (i != battle_team_id_by_side[bank_attacker] && get_attributes(&poke[i], ATTR_CURRENT_HP, 0) &&
				is_poke_valid(&poke[i]))
			viable_pokes |= BIT_GET(i);
	}
	while (viable_pokes)
	{
		u8 chosen_poke;
		do
		{
			chosen_poke = random_value(6);
		} while (!(viable_pokes & bits_table[chosen_poke])); //choose poke
		u8 viable_moves = 0;
		u16 move[4];
		for (u8 i = 0; i < 4; i++)
		{
			move[i] = get_attributes(&poke[chosen_poke], ATTR_ATTACK_1 + i, 0);
			if (move[i] && can_select_this_random_move(move[i]))
				viable_moves |= BIT_GET(i);
		}
		if (viable_moves) //move can be found
		{
			u8 chosen_move;
			do
			{
				chosen_move = rng() % 4/*__umodsi3(rng(), 4)*/;
			} while (!(viable_moves & bits_table[chosen_move])); //choose move
			randomly_chosen_move = move[chosen_move];
			hitmarker &= 0xFFFFFBFF;
			bank_target = get_target_of_move(randomly_chosen_move, 0, 0);
			battlescripts_curr_instruction += 5;
			return;
		}
			//no viable moves for this pokemon
		else
		{
			viable_pokes ^= bits_table[chosen_poke];
		} //we can xor this bit since we know it's set
	}
	battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction + 1);
}

void atkA9_sleeptalkmovechoose(void) //void* success_ptr
{
	u8 usable_bitfield = 0;
	for (u8 i = 0; i < 4; i++)
	{
		if (can_select_this_random_move(battle_participants[bank_attacker].moves[i]))
		{
			usable_bitfield |= (BIT_GET(i));
		}
	}
	usable_bitfield = check_move_limitations(bank_attacker, usable_bitfield, 0xFF);
	if (usable_bitfield)
	{
		u8 chosen_id;
		do
		{
			chosen_id = rng() & 3;
		} while (!(usable_bitfield & bits_table[chosen_id]));
		u16 move = battle_participants[bank_attacker].moves[chosen_id];
		randomly_chosen_move = move;
		current_move_position = chosen_id;
		hitmarker &= 0xFFFFFBFF;
		bank_target = get_target_of_move(move, 0, 0);
		battlescripts_curr_instruction = (void*) (read_word(battlescripts_curr_instruction + 1));
	}
	else
		battlescripts_curr_instruction += 5;
}

void atk9E_metronome_chooser(void)
{
#define MOVE_MAX 621
	static const u16 metronome_forbidden_moves[] = {MOVE_AFTER_YOU, MOVE_ASSIST, MOVE_BELCH, MOVE_BESTOW,
			MOVE_CELEBRATE, MOVE_CHATTER, MOVE_COPYCAT, MOVE_COUNTER, MOVE_COVET, MOVE_CRAFTY_SHIELD, MOVE_DESTINY_BOND,
			MOVE_DETECT, MOVE_DIAMOND_STORM, MOVE_ENDURE, MOVE_FEINT, MOVE_FOCUS_PUNCH, MOVE_FOLLOW_ME,
			MOVE_FREEZE_SHOCK, MOVE_HAPPY_HOUR, MOVE_HELPING_HAND, MOVE_HOLD_HANDS, MOVE_HYPERSPACE_HOLE, MOVE_ICE_BURN,
			MOVE_KINGS_SHIELD, MOVE_LIGHT_OF_RUIN, MOVE_MAT_BLOCK, MOVE_ME_FIRST, MOVE_METRONOME, MOVE_MIMIC,
			MOVE_MIRROR_COAT, MOVE_MIRROR_MOVE, MOVE_NATURE_POWER, MOVE_PROTECT, MOVE_QUASH, MOVE_QUICK_GUARD,
			MOVE_RAGE_POWDER, MOVE_RELIC_SONG, MOVE_SECRET_SWORD, MOVE_SKETCH, MOVE_SLEEP_TALK, MOVE_SNARL, MOVE_SNATCH,
			MOVE_SNORE, MOVE_SPIKY_SHIELD, MOVE_STEAM_ERUPTION, MOVE_STRUGGLE, MOVE_SWITCHEROO, MOVE_TECHNO_BLAST,
			MOVE_THIEF, MOVE_THOUSAND_ARROWS, MOVE_THOUSAND_WAVES, MOVE_TRANSFORM, MOVE_TRICK, MOVE_VCREATE,
			MOVE_WIDE_GUARD, 0xFFFF};
	do
	{
		current_move = random_value(MOVE_MAX)/*__umodsi3(rng(), MOVE_MAX)*/ + 1;
	} while (find_move_in_table(current_move, metronome_forbidden_moves));

	hitmarker &= 0xFFFFFBFF;
	battlescripts_curr_instruction = get_move_battlescript_ptr(current_move);
	bank_target = get_target_of_move(current_move, 0, 0);
	set_attacking_move_type();
}

void atkC5_hide_pre_attack(void)
{
	switch (current_move)
	{
		case MOVE_BOUNCE:
		case MOVE_FLY:
			status3[bank_attacker].on_air = 1;
			break;
		case MOVE_DIG:
			status3[bank_attacker].underground = 1;
			break;
		case MOVE_DIVE:
			status3[bank_attacker].underwater = 1;
			break;
		case MOVE_PHANTOM_FORCE:
		case MOVE_SHADOW_FORCE:
			status3[bank_attacker].phantomforce = 1;
			break;
	}
	battlescripts_curr_instruction++;
}

void atkC6_unhide_post_attack(void)
{
	clear_twoturn(bank_attacker);
	if (current_move == MOVE_SKY_DROP)
	{
		clear_twoturn(bank_target);
		u8 objID = objID_pbs_moveanimations[animation_bank_target];
		struct object* poke_obj = &objects[objID];
		poke_obj->pos1.x = poke_obj->private[7];

		objID = objID_pbs_moveanimations[animation_bank_attacker];
		poke_obj = &objects[objID];
		poke_obj->pos1.x = poke_obj->private[7];
	}

	battlescripts_curr_instruction++;
}

void atkCC_nature_power(void)
{
	hitmarker &= 0xFFFFFBFF;
	if (new_battlestruct->field_affecting.grassy_terrain)
		current_move = MOVE_ENERGY_BALL;
	else if (new_battlestruct->field_affecting.misty_terrain)
		current_move = MOVE_MOONBLAST;
	else if (new_battlestruct->field_affecting.electic_terrain)
		current_move = MOVE_THUNDERBOLT;
	else if (new_battlestruct->field_affecting.psychic_terrain)
		current_move = MOVE_PSYCHIC;
	else
	{
		static const u16 naturepower_table[] = {MOVE_ENERGY_BALL /*GRASS*/, MOVE_ENERGY_BALL /*LONG GRASS*/,
				MOVE_EARTH_POWER /*SAND*/, MOVE_HYDRO_PUMP /*UNDERWATER*/, MOVE_HYDRO_PUMP /*WATER*/,
				MOVE_HYDRO_PUMP /*POND*/, MOVE_POWER_GEM /*ROCK*/, MOVE_POWER_GEM /*CAVE*/, MOVE_TRI_ATTACK,
				MOVE_TRI_ATTACK};
		current_move = naturepower_table[battle_env_bg]; //JeremyZ
	}
	bank_target = get_target_of_move(current_move, 0, 0);
	set_attacking_move_type();
	bs_push(get_move_battlescript_ptr(current_move), battlescripts_curr_instruction + 1);
}

void atkB7_present_calc(void)
{
	u32 random_rumber = __umodsi3(rng() + 100, 101);
	if (random_rumber < 40)
		dynamic_base_power = 40;
	else if (random_rumber < 70)
		dynamic_base_power = 80;
	else if (random_rumber < 80)
		dynamic_base_power = 120;
	else
	{
		dynamic_base_power = 0;
		if (battle_participants[bank_target].current_hp >= battle_participants[bank_target].max_hp)
			battlescripts_curr_instruction = (void*) 0x082D9EFB;
		else if (new_battlestruct->bank_affecting[bank_target].heal_block)
			battlescripts_curr_instruction = BS_HEALBLOCK_PREVENTS;
		else
		{
			damage_loc = get_1_4_of_max_hp(bank_target) * (-1);
			battlescripts_curr_instruction = (void*) 0x082D9EE1;
		}
	}
	if (dynamic_base_power)
		battlescripts_curr_instruction = (void*) 0x082D8A30;
}

void atk13_printfromtable(void)
{
	if (battle_execution_buffer)
	{
		return;
	}
	u16* string_id = (u16*) read_word(battlescripts_curr_instruction + 1);
	string_id += battle_communication_struct.multistring_chooser;

	u8 lower = battle_scripting.stat_changer & 0x80;
	u16 string_to_read = *string_id;
	battle_communication_struct.is_message_displayed = 1;
	prep_string(string_to_read, bank_attacker);
	battlescripts_curr_instruction += 5;
	u8 bank = battle_scripting.active_bank;
	if (((string_to_read == 0x23D || string_to_read == 0x197) && lower && bank == bank_target &&
			get_bank_side(bank) != get_bank_side(bank_attacker) && new_battlestruct->bank_affecting[bank].stat_lowered)
			|| (new_battlestruct->side_affecting[get_bank_side(bank)].sticky_web_done && new_battlestruct->bank_affecting[bank].stat_lowered))
	{
		new_battlestruct->bank_affecting[bank].stat_lowered = 0;
		if (check_ability(bank, ABILITY_DEFIANT) && battle_participants[bank].atk_buff != 0xC)
		{
			record_usage_of_ability(bank, ABILITY_DEFIANT);
			bs_push_current(BS_DEFIANT);
		}
		else if (check_ability(bank, ABILITY_COMPETITIVE) && battle_participants[bank].sp_atk_buff != 0xC)
		{
			record_usage_of_ability(bank, ABILITY_COMPETITIVE);
			bs_push_current(BS_COMPETITIVE);
		}
	}
}

struct revert_form_struct
{
	u16 current_species;
	u16 base_form;
};

void revert_form_change(bool mega_revert, u8 teamID, u8 side, struct pokemon* poke)
{
	if (mega_revert)
		revert_mega_to_normalform_new(side);//JeremyZ
	else
	{
		u16 current_hp = get_attributes(poke, ATTR_CURRENT_HP, 0);
		u16 species = get_attributes(poke, ATTR_SPECIES, 0);
		if (species == POKE_ZYGARDE_100 && battle_outcome) //JeremyZ
		{
			u16 base_species = POKE_ZYGARDE_10;
			if ((side && (new_battlestruct->party_bit.is_base_z50_ai & bits_table[teamID])) ||
					(!side && (new_battlestruct->party_bit.is_base_z50_user & bits_table[teamID])))
			{
				if (side)
				{
					new_battlestruct->party_bit.is_base_z50_ai = 0;
				}
				else
				{
					new_battlestruct->party_bit.is_base_z50_user = 0;
				}
				base_species = POKE_ZYGARDE_50; //JeremyZ
			}
			set_attributes(poke, ATTR_SPECIES, &base_species);
			calculate_stats_pokekmon(poke);
			u16 total_hp = get_attributes(poke, ATTR_TOTAL_HP, 0);
			if (current_hp > total_hp)
				set_attributes(poke, ATTR_CURRENT_HP, &total_hp);
			else //JeremyZ
				set_attributes(poke, ATTR_CURRENT_HP, &current_hp);
		}
		else
		{
			//change mmikkyu only when it faints and at the end of battle, not on switchout
			if (species != POKE_AEGISLASH_BLADE && current_hp && !battle_outcome)
			{
				return;
			}
			static const struct revert_form_struct revert_mapping[] = {{POKE_CHERRIM_SUNSHINE, POKE_CHERRIM},
					{POKE_AEGISLASH_BLADE, POKE_AEGISLASH_SHIELD}, {POKE_DARMANITAN_ZEN, POKE_DARMANITAN},
					{POKE_MELOETTA_PIROUETTE, POKE_MELOETTA_ARIA}, {POKE_MINIOR_METEOR, POKE_MINIOR_CORE},
					{POKE_WISHIWASHI_SCHOOL, POKE_WISHIWASHI}, {POKE_ASH_GRENJA, POKE_GRENINJA},
					{POKE_MIMIKYU_BUSTED, POKE_MIMIKYU}, {0x42b, 0x34D}, {0x421, 0x301}, {0x42a, 0x34c}, {0x422, 0x357},
					{0xFFFF, 0}};
			for (u32 i = 0; revert_mapping[i].current_species != 0xFFFF; i++)
			{
				if (species == revert_mapping[i].current_species)
				{
					species = revert_mapping[i].base_form;
					if (species == POKE_MINIOR_CORE)
					{
						u8 change = __umodsi3(get_attributes(poke, ATTR_PID, 0), 7);/*random_value(7)*/
						if (change)
							species = 0x3EA + change;
					}
					set_attributes(poke, ATTR_SPECIES, (void*) &species);
					calculate_stats_pokekmon(poke);
					break;
				}
			}

		}
	}
	revert_form_change_search(poke);
}

void atk56_prepare_fainting_cry(void)
{
	u8 bank = get_battle_bank(read_byte(battlescripts_curr_instruction + 1));
	battlescripts_curr_instruction += 2;
	active_bank = bank;
	prepare_fainting_cry(0);
	mark_buffer_bank_for_execution(bank);
	new_battlestruct->side_affecting[get_bank_side(bank)].ally_fainted_last_turn = 2;
	new_battlestruct->various.switch_in_cos_switch = 0;
}

void atkE1_intimidate_loop(void)
{
	u8 bank = battle_stuff_ptr->intimidate_user;
	battle_scripting.active_bank = bank;
	u8 side = get_bank_side(bank);
	battle_text_buff1[0] = 0xFD;
	battle_text_buff1[1] = 9;
	battle_text_buff1[2] = battle_participants[bank].ability_id;
	battle_text_buff1[3] = 0xFF;
	while (bank_target < no_of_all_banks)
	{
		if (side != get_bank_side(bank_target) && is_bank_present(bank_target))
		{
			battlescripts_curr_instruction += 5;
			return;
		}
		bank_target++;
	}
	battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction + 1);
}

void atk47_set_statchange_values(void)
{
	battlescripts_curr_instruction++;
	battle_scripting.AnimInfo2 = 0;

	u8 statchanger = battle_scripting.stat_changer;
	u8* statgfx = &battle_scripting.AnimInfo1;

	//first three bits is colour
//	if (statchanger & STAT_MULTIPLE)
//		*statgfx = 7;
//	else
//	{
		static const u8 statID_to_colorID[] = {0, 1, 3, 5, 6, 2, 4};
		//colors: atk = 0, def = 1, acc = 2, spd = 3, 4 = evs, 5 = spatk, 6 = spdef
		*statgfx = statID_to_colorID[(statchanger & STAT_STATID) - 1];
//	}

	//0x10 and 0x20 and 0x40 is intensity
	*statgfx |= (statchanger & STAT_STAGES);

	//last bit is whether goes down
	*statgfx |= (statchanger & STAT_NEGATIVE);
}

void atkE4_secretpowereffect(void)
{
	struct field_affecting* terrains = &new_battlestruct->field_affecting;
	u8* effect = &battle_communication_struct.move_effect;
	if (terrains->electic_terrain) //paralysis
		*effect = 5;
	else if (terrains->grassy_terrain) //sleep
		*effect = 1;
	else if (terrains->misty_terrain) //sp atk by one down
		*effect = 0x1B;
	else
	{
		switch (battle_env_bg)
		{
			case 0: //normal grass; sleep
				*effect = 1;
				break;
			case 1: //tall grass; poison
				*effect = 2;
				break;
			case 2: //sand; acc by one down
				*effect = 0x1D;
				break;
			case 3: //underwater; def by one down
				*effect = 0x19;
				break;
			case 4: //surf water; atk by one down
				*effect = 0x18;
				break;
			case 5: //pond water; spd by one down
				*effect = 0x1A;
				break;
			case 6: //rocky area; confusion
				*effect = 7;
				break;
			case 7: //cave; flinching
				*effect = 8;
				break;
			case 8: //plain building; paralysis
			case 9: //strange grass; paralysis
				*effect = 5;
				break;
		}
	}
	battlescripts_curr_instruction++;
}

void moveeffect_set_status(u8 bank, u32 flag, u8 stringID)
{
	battle_participants[bank].status.int_status = flag;
	active_bank = bank;
	bb2_setattributes_in_battle(0, REQUEST_STATUS_BATTLE, 0, 4, &battle_participants[bank].status);
	mark_buffer_bank_for_execution(active_bank);
	bs_push_current(BS_GOT_STATUS);
	battle_communication_struct.multistring_chooser = stringID;
	//set synchronize
	if (bank_target != bank_attacker && flag != STATUS_FREEZE && flag != STATUS_SLEEP)
		new_battlestruct->move_effect.synchro_effect[bank] = flag;
}

bool moveeffect_handle_psn(u8 bank, u32 flag, u8 stringID)
{
	bool effect = 0;
	switch (cant_poison(bank_attacker, bank, 0))
	{
		case 0:
			effect = 1;
			moveeffect_set_status(bank, flag, stringID);
			break;
	}
	return effect;
}

u8 cant_become_confused(u8 bank)
{
	//0 == can become confused
	//1 == already confused
	//4 == ability doesn't allow it
	//5 == safeguard protection
	//8 == misty terrain protection
	if (battle_participants[bank].status2.confusion)
		return 1;
	if (is_class_FOUR(bank))
		return 2;
	if (check_ability(bank, ABILITY_OWN_TEMPO))
		return 4;
	if (side_affecting_halfword[get_bank_side(bank)].safeguard_on && !(hitmarker & HITMAKRER_IGNORE_SAFEGUARD))
		return 5;
	if (new_battlestruct->field_affecting.misty_terrain && GROUNDED(bank))
		return 8;
	return 0;
}

bool move_effect_setter(bool primary, bool certain)
{
	u16* move_effect = &new_battlestruct->move_effect.effect1;
	u8 bank = bank_target;
	if (*move_effect & MOVEEFFECT_AFFECTSUSER)
	{
		bank = bank_attacker;
	}

	if (!is_bank_present(bank))
	{
		battlescripts_curr_instruction++;
		return 0;
	} //dont do anything if the bank is dead

	//check things that may make move effect ineffective
	bool substitute = (bank == bank_target && affected_by_substitute(bank));
	bool shielddust = (bank == bank_target && check_ability(bank, ABILITY_SHIELD_DUST) && !primary);
	bool sheerforce = (new_battlestruct->various.sheerforce_bonus && !primary);

	bool effect = 0;
	bool effect_block = (substitute || shielddust || sheerforce);

	if ((*move_effect) & MOVEEFFECT_STATCHANGE)
	{
		*move_effect = BIC(*move_effect, MOVEEFFECT_STATCHANGE);
		if (!effect_block)
		{
			u8 bits = STAT_CHANGE_VALUES;

			if ((*move_effect & MOVEEFFECT_AFFECTSUSER))
				bits |= STAT_SELFINFLICTED;
			u8 ret = change_stats(bank, bits, battlescripts_curr_instruction);
			if (ret == STAT_CHANGED)
			{
				//stat was changed
				effect = 1;
				if (bank == bank_attacker)
					bs_push_current(ONE_STAT_USER_STATANIM);
				else
					bs_push_current(ONE_STAT_TARGET_STATANIM);
			}
		}
	}
	else if ((*move_effect) & MOVEEFFECT_MULTIPLESTATS)
	{
		*move_effect = BIC(*move_effect, MOVEEFFECT_MULTIPLESTATS);
		if (!effect_block)
		{
			effect = 1;
			if (certain || primary)
				bs_push_current(BS_MULTIPLESTATCHANCE_ATK_CERTAIN);
			else
				bs_push_current(BS_MULTIPLESTATCHANCE_ATK);
		}
	}
	else if ((*move_effect) & MOVEEFFECT_TOXIC)
	{
		*move_effect = BIC(*move_effect, MOVEEFFECT_TOXIC);
		if (!effect_block)
		{
			effect = moveeffect_handle_psn(bank, STATUS_TOXIC_POISON, 1);
		}
	}
	else if ((*move_effect) & MOVEEFFECT_PSN)
	{
		*move_effect = BIC(*move_effect, MOVEEFFECT_PSN);
		if (!effect_block)
		{
			effect = moveeffect_handle_psn(bank, STATUS_POISON, 0);
		}
	}
	else if ((*move_effect) & MOVEEFFECT_BRN)
	{
		*move_effect = BIC(*move_effect, MOVEEFFECT_BRN);
		if (!effect_block)
		{
			switch (cant_become_burned(bank, 0))
			{
				case 0:
					effect = 1;
					moveeffect_set_status(bank, STATUS_BURN, 2);
					break;
			}
		}
	}
	else if ((*move_effect) & MOVEEFFECT_FRZ)
	{
		*move_effect = BIC(*move_effect, MOVEEFFECT_FRZ);
		if (!effect_block)
		{
			switch (cant_become_freezed(bank, 0))
			{
				case 0:
					effect = 1;
					moveeffect_set_status(bank, STATUS_FREEZE, 3);
					break;
			}
		}
	}
	else if ((*move_effect) & MOVEEFFECT_SLP)
	{
		*move_effect = BIC(*move_effect, MOVEEFFECT_SLP);
		if (!effect_block)
		{
			switch (cant_fall_asleep(bank, 0))
			{
				case 0:
					effect = 1;
					moveeffect_set_status(bank, rng() % 4/*__umodsi3(rng(), 4)*/ + 2, 4);
					break;
			}
		}
	}
	else if ((*move_effect) & MOVEEFFECT_PRLZ)
	{
		*move_effect = BIC(*move_effect, MOVEEFFECT_PRLZ);
		if (!effect_block)
		{
			switch (cant_become_paralyzed(bank, 0))
			{
				case 0:
					effect = 1;
					moveeffect_set_status(bank, STATUS_PARALYSIS, 5);
					break;
			}
		}
	}
	else if ((*move_effect) & MOVEEFFECT_CONFUSE)
	{
		*move_effect = BIC(*move_effect, MOVEEFFECT_CONFUSE);
		if (!effect_block)
		{
			switch (cant_become_confused(bank))
			{
				case 0: //can confuse
					effect = 1;
					battle_participants[bank].status2.confusion = 2 + rng() % 4/*__umodsi3(rng(), 4)*/;
					bs_push_current((void*) (0x082DB3E6)); //poke became confused
					break;
			}
		}
	}
	else if ((*move_effect) & MOVEEFFECT_FLINCH)
	{
		*move_effect = BIC(*move_effect, MOVEEFFECT_FLINCH);
		if (!effect_block)
		{
			if (check_ability(bank, ABILITY_INNER_FOCUS))
			{
				if (primary || certain)
				{
					effect = 1;
					record_usage_of_ability(bank, ABILITY_INNER_FOCUS);
					bs_push_current((void*) (0x82DB603));
				}
			}
			else
				battle_participants[bank].status2.flinched = 1;
		}
	}

	if (!effect && !((*move_effect) & MOVEEFFECT_ALL)) //no effect and no flag is set
		battlescripts_curr_instruction++;
	bank_partner_def = bank;
	return effect;
}

void atk15_setmoveeffectchance(void)
{

	if (!MOVE_WORKED)
	{
		battlescripts_curr_instruction++;
		battle_scripting.field16 = 0;
		return;
	} //don't do anything if move doesn't work
	if (TARGET_TURN_DAMAGED /*&& !affected_by_substitute(bank_target)*/)
	{
		u8 chosen_effect = new_battlestruct->side_affecting[bank_attacker & 1].pledge_effect;
		bool effect_of_pledge = false;
		switch (chosen_effect)
		{
			case 1:
				if (!new_battlestruct->side_affecting[bank_target & 1].swamp_spd_reduce)
				{
					battlescripts_curr_instruction++;
					new_battlestruct->side_affecting[bank_target & 1].swamp_spd_reduce = 5;
					bs_push_current(&swamp_bs);
					effect_of_pledge = true;
				}
				break;
			case 2:
				if (!new_battlestruct->side_affecting[bank_target & 1].sea_of_fire)
				{
					battlescripts_curr_instruction++;
					new_battlestruct->side_affecting[bank_target & 1].sea_of_fire = 5;
					bs_push_current(&fire_sea_bs);
					effect_of_pledge = true;
				}
				break;
			case 3:
				if (!new_battlestruct->side_affecting[bank_attacker & 1].rainbow)
				{
					battlescripts_curr_instruction++;
					new_battlestruct->side_affecting[bank_attacker & 1].rainbow = 5;
					bs_push_current(&rainbow_bs);
					effect_of_pledge = true;
				}
				break;
		}
		if (effect_of_pledge)
		{
			return;
		}
	}

	//bool res= true;
	u8 percent = move_table[current_move].effect_chance;
	u8 chance;
	if (current_move == MOVE_SECRET_POWER)
		chance = percent_chance(percent);
	else
		chance = calculate_effect_chance(bank_attacker, current_move);
	u16* move_effect = &new_battlestruct->move_effect.effect1;
	if (*move_effect & MOVEEFFECT_ALL)
	{
		if (percent == 100)
			move_effect_setter(0, 1);
		else if (chance)
			move_effect_setter(0, 0);
			//run the command again for moves with multiple flags, so each one has an individual chance of happening
		else if (!(*move_effect & MOVEEFFECT_ONECALC))
		{
			for (u16 i = 2;; i++)
			{
				if (*move_effect & (1 << i))
				{
					*move_effect = BIC(*move_effect, (1 << i));
					break;
				}
			}
		}
	}
	else
		battlescripts_curr_instruction++;


	battle_scripting.field16 = 0;
}

void atk16_setmoveeffectprimary(void)
{
	move_effect_setter(1, 0);
}

void atk17_setmoveeffectsecondary(void)
{
	move_effect_setter(0, 0);
}

void atk5D_moneyreward(void)
{
	u32 money = get_trainer_money(var_8015_trainer_opponent_A);
	if (battle_flags.multibattle)
		money += get_trainer_money(trainer_opponent_B);
	if (new_battlestruct->various.happyhour_bonus)
		money *= 2;
	give_money(&sav1->money, money);
	battle_text_buff1[0] = 0xFD;
	battle_text_buff1[1] = 1;
	battle_text_buff1[2] = 4;
	battle_text_buff1[3] = 5;
	battle_text_buff1[4] = money;
	battle_text_buff1[5] = money >> 8;
	battle_text_buff1[6] = money >> 0x10;
	battle_text_buff1[7] = money >> 0x18;
	battle_text_buff1[8] = 0xFF;
	battlescripts_curr_instruction++;
}

void atk5C_hitanimation(void)
{
	u8 bank = get_battle_bank(read_byte(battlescripts_curr_instruction + 1));
	battlescripts_curr_instruction += 2;
	if (MOVE_WORKED && !affected_by_substitute(bank_target))
	{
		active_bank = bank;
		bb29_hit_animation(0);
		mark_buffer_bank_for_execution(bank);
		if (battle_participants[bank].ability_id == ABILITY_ILLUSION &&
				new_battlestruct->bank_affecting[bank].illusion_on && damage_loc > 0 && DAMAGING_MOVE(current_move) &&
				bank != bank_attacker && bank == bank_target)
		{
			new_battlestruct->bank_affecting[bank].illusion_on = 0;
			new_battlestruct->bank_affecting[bank].illusion_hit = 1;
			bs_push_current(BS_ILLUSION_OFF);
			battle_participants[bank].status2.transformed = 0;
		}
	}
}

void atk02_attackstring(void)
{
	if (!battle_execution_buffer)
	{
		u8 type = get_attacking_move_type();
		if (check_ability(bank_attacker, ABILITY_PROTEAN) && current_move != MOVE_STRUGGLE && !move_outcome.failed &&
				!new_battlestruct->various.protean_msg)
		{
			new_battlestruct->various.protean_msg = 1;
			if (!is_of_type(bank_attacker, type))
			{
				last_used_ability = ABILITY_PROTEAN;
				record_usage_of_ability(bank_attacker, ABILITY_PROTEAN);
				set_type(bank_attacker, type);
				battle_text_buff1[0] = 0xFD;
				battle_text_buff1[1] = 0x3;
				battle_text_buff1[2] = type;
				battle_text_buff1[3] = 0xFF;
				bs_push_current(BS_PROTEAN);
			}
		}
		else
		{
			battlescripts_curr_instruction++;
			if (!((hitmarker & HITMARKER_NO_ATTACKSTRING) || (hitmarker & HITMARKER_ATTACKSTRING_PRINTED)))
			{
				if (new_battlestruct->side_affecting[bank_attacker & 1].pledge_effect)
				{
					bs_push_current(&combined_move_bs);
				}
				else
				{
					prep_string(4, bank_attacker);
					battle_communication_struct.is_message_displayed = 0;
				}
				hitmarker |= HITMARKER_ATTACKSTRING_PRINTED;
			}
		}
	}
}

void atk78_explodeifnotdamp(void)
{
	for (u8 i = 0; i < 4; i++)
	{
		if (is_bank_present(i) && battle_participants[i].ability_id == ABILITY_DAMP && has_ability_effect(i, 1))
		{
			bank_target = i;
			last_used_ability = ABILITY_DAMP;
			record_usage_of_ability(i, ABILITY_DAMP);
			move_outcome.failed = 1;
			move_outcome.explosion_stop = 1;
			battlescripts_curr_instruction = (void*) (0x082DB560);
			return;
		}
	}
	damage_loc = battle_participants[bank_attacker].current_hp;
	active_bank = bank_attacker;
	prepare_health_bar_update_buffer(0, 0x7FFF);
	mark_buffer_bank_for_execution(active_bank);
	for (u8 i = 0; i < 4; i++)
	{
		if (is_bank_present(i) && i != bank_attacker)
		{
			bank_target = i;
			break;
		}
	}
	battlescripts_curr_instruction++;
}

void atkD2_itemswap(void)
{
	if (!battle_flags.flag_x4000000 && !WILD_ATTACKER)
	{
		u16* target_item = &battle_participants[bank_target].held_item;
		u16* attacker_item = &battle_participants[bank_attacker].held_item;
		if (!(*target_item == 0 && *attacker_item == 0) && can_lose_item(bank_attacker, 0, 0) &&
				can_lose_item(bank_target, 1, 1))
		{
			battle_text_buff1[0] = 0xFD;
			battle_text_buff1[1] = 0xA;
			battle_text_buff1[2] = *target_item;
			battle_text_buff1[3] = *target_item >> 0x8;
			battle_text_buff1[4] = 0xFF;
			battle_text_buff2[0] = 0xFD;
			battle_text_buff2[1] = 0xA;
			battle_text_buff2[2] = *attacker_item;
			battle_text_buff2[3] = *attacker_item >> 0x8;
			battle_text_buff2[4] = 0xFF;
			u8* string_chooser = &battle_communication_struct.multistring_chooser;
			if (*target_item == 0)
				*string_chooser = 1;
			else if (*attacker_item == 0)
				*string_chooser = 0;
			else
				*string_chooser = 2;
			battlescripts_curr_instruction += 5;
			battle_stuff_ptr->changed_held_items[bank_attacker] = *target_item;
			active_bank = bank_attacker;
			bb2_setattributes_in_battle(0, REQUEST_HELDITEM_BATTLE, 0, 2, target_item);
			mark_buffer_bank_for_execution(bank_attacker);
			active_bank = bank_target;
			*target_item = *attacker_item;
			*attacker_item = 0;
			bb2_setattributes_in_battle(0, REQUEST_HELDITEM_BATTLE, 0, 2, target_item);
			mark_buffer_bank_for_execution(bank_target);
			if (!ITEM_SWAP && battle_flags.trainer)//set items to return later
			{
				u8 bank = bank_attacker;
				if (get_bank_side(bank_attacker))
					bank = bank_target;
				new_battlestruct->various.returns_swap |= bits_table[battle_team_id_by_side[bank]];
			}
		}
	}
	battlescripts_curr_instruction = (void*) (read_word(battlescripts_curr_instruction + 1));
}

static void give_one_ev(struct pokemon* poke, u8 attr)
{
	u16 stat = get_attributes(poke, attr, 0);
	if (stat < 252)
	{
		stat++;
		set_attributes(poke, attr, &stat);
	}
}

void evs_update(struct pokemon* poke, u16 defeated_species)
{
	u16 evs_total = 0;
	for (u8 i = 0; i < 6; i++)
	{
		evs_total += get_attributes(poke, ATTR_HP_EV + i, 0);
	}
	u8 pokerus = specific_pokerus_check(poke, 0);
	u8 power_item = 0xFF;
	u16 item = (get_attributes(poke, ATTR_HELD_ITEM, 0));
	if (get_item_battle_function(item) == ITEM_EFFECT_MACHOBRACE)
	{
		power_item = (u8) get_item_extra_param(item);
	}
	const struct poke_basestats* stats = &((*basestat_table)[defeated_species]);
	for (u8 curr_stat = 0; curr_stat < 6; curr_stat++)
	{
		u8 to_add = 0;
		u8 power_bonus = 0;
		switch (curr_stat)
		{
			case 0:
				to_add = stats->evs_hp;
				break;
			case 1:
				to_add = stats->evs_atk;
				break;
			case 2:
				to_add = stats->evs_def;
				break;
			case 3:
				to_add = stats->evs_spd;
				break;
			case 4:
				to_add = stats->evs_spatk;
				break;
			case 5:
				to_add = stats->evs_spdef;
				break;
		}
		if (pokerus)
			to_add *= 2;
		if (power_item == 0)
			to_add *= 2;
		else if (item && (power_item - 1) == curr_stat)
		{
			power_bonus = 4;
			if (pokerus)
				power_bonus *= 2;
			item = 0;
		}
		if (evs_total > MAX_EVS)
		{
			item = 0;
			for (u8 i = 0; i < 6; i++)
				set_attributes(poke, ATTR_HP_EV + i, &item);
			return;
		}
		while (to_add > 0 || power_bonus > 0)
		{
			if (evs_total >= MAX_EVS)
				return;
			if (to_add)
			{
				give_one_ev(poke, ATTR_HP_EV + curr_stat);
				to_add--;
				evs_total++;
			}
			else if (power_bonus)
			{
				give_one_ev(poke, ATTR_HP_EV + (power_item - 1));
				power_bonus--;
				evs_total++;
			}
		}
	}
	return;
}

bool is_poke_usable(struct pokemon* poke)
{
	u16 species = get_attributes(poke, ATTR_SPECIES_2, 0);
	if (species != 0 && species != POKE_EGG && get_attributes(poke, ATTR_CURRENT_HP, 0))
		return 1;
	return 0;
}

void atk23_exp_evs_lvlup(void)
{
#define exp_for_poke damage_loc
	if (battle_execution_buffer)
	{
		return;
	} // wait for the things to get done
	u8* tracker = &battle_scripting.cmd23_state_tracker;
	u16* sentin_exp = &battle_stuff_ptr->exp;
	u8 bank = get_battle_bank(read_byte(battlescripts_curr_instruction + 1));
	bank_partner_atk = bank;
	u8* exp_getter_id = &battle_stuff_ptr->expgetter_id;

	switch (*tracker)
	{
		case 0: //check if poke should get exp
			if (!get_bank_side(bank) || BATTLE_FRONTIER_BATTLE || battle_flags.safari || battle_flags.flagx800 ||
					battle_flags.link || battle_flags.flag_x2000000 || battle_flags.flag_x4000000)
			{
				*tracker = 6; //set last case
				break;
			}
			battle_stuff_ptr->got_exp_from |= bits_table[battle_team_id_by_side[bank]];
			(*tracker)++;
		case 1: //get exp and pokes that will get exp
		{
			u8 via_expshare = 0;
			u8 via_sentin = 0;
			u8 sent_in = sent_pokes_to_opponent[bank >> 1];
			expshare_exp = 0;
			for (u8 i = 0; i < 6; i++)
			{
				struct pokemon* poke = &party_player[i];
				if (is_poke_usable(poke))
				{
					if (sent_in & BIT_GET(i))
						via_sentin++;
					if (GETS_VIA_EXPSHARE(get_item_battle_function(get_attributes(poke, ATTR_HELD_ITEM, 0))))
						via_expshare++;
				}
				else
					sent_in &= ~(BIT_GET(i)); //no exp for that poke
			}
			struct battle_participant* oppponent = &battle_participants[bank];
			u16 exp = (*basestat_table)[oppponent->species].exp_yield * oppponent->level / 7;
			if (EXP_DIVIDE == true && via_expshare)
			{
			    exp /= (2 + battle_flags.double_battle);
			}
#if (EXP_DIVIDE == true)
				*sentin_exp = ATLEAST_ONE(exp / via_sentin);
				expshare_exp = ATLEAST_ONE(exp / via_expshare);
#else
				expshare_exp =*sentin_exp = ATLEAST_ONE(exp);
#endif

			*exp_getter_id = 0;
			battle_stuff_ptr->sentin_pokes = sent_in;
			(*tracker)++;
		}
		case 2: //loop; set exp value to the poke in expgetter_id and print message
		{
			exp_for_poke = 0;
			u8* sentin_pokes = &battle_stuff_ptr->sentin_pokes;
			struct pokemon* poke = &party_player[*exp_getter_id];
			u8 held_item = get_item_battle_function(get_attributes(poke, ATTR_HELD_ITEM, 0));
			if (is_poke_usable(poke) && (GETS_VIA_EXPSHARE(held_item) || *sentin_pokes & 1))
			{
				//update evs
				if (!GET_CUSTOMFLAG(DISABLED_EVS_FLAG))
					evs_update(poke, battle_participants[bank].species);

				//play victory music
				if (!battle_flags.trainer && !is_bank_present(1) && !is_bank_present(3) &&
						(is_bank_present(0) || is_bank_present(2)) && !battle_stuff_ptr->wildvictorysong)
				{
					stop_battle_music();
					play_song_check_flag(0x161);
					battle_stuff_ptr->wildvictorysong++;
				}

				if (get_attributes(poke, ATTR_LEVEL, 0) < MAX_LEVEL &&
						!GET_CUSTOMFLAG(DISABLED_EXP_FLAG)) //apply experience
				{
					if (*sentin_pokes & 1)
						exp_for_poke = *sentin_exp;
					else
						exp_for_poke = 0;
					if (GETS_VIA_EXPSHARE(held_item))
					{
						if (EXP_DIVIDE == false && *sentin_pokes & 1)
							exp_for_poke = *sentin_exp;
						else
							exp_for_poke += expshare_exp;
						if (EXP_DIVIDE == false && !(*sentin_pokes & 1))
						 exp_for_poke /= 2;
					}
					if (held_item == ITEM_EFFECT_LUCKYEGG)
						exp_for_poke = PERCENT_100(exp_for_poke, 200);
					if (battle_flags.trainer)
						exp_for_poke = PERCENT_100(exp_for_poke, 150);
					u16 bs_id = 0x149;
					if (is_poke_traded(poke) && !battle_flags.player_ingame_partner && (*sentin_exp & 1))
					{
						exp_for_poke = PERCENT_100(exp_for_poke, 150);
						bs_id++;
					}
					battle_stuff_ptr->expgetter_bank = 0;
					if (battle_flags.double_battle && is_bank_present(2) && battle_team_id_by_side[2] == *exp_getter_id)
						battle_stuff_ptr->expgetter_bank = 2;
					if(*exp_getter_id == 0 || !expshare_exp){
						//buffer poke name
						battle_text_buff1[0] = 0xFD;
						battle_text_buff1[1] = 4;
						battle_text_buff1[2] = battle_stuff_ptr->expgetter_bank;
						battle_text_buff1[3] = *exp_getter_id;
						battle_text_buff1[4] = 0xFF;

						//buffer 'gained' or 'gained a boosted'
						battle_text_buff2[0] = 0xFD;
						battle_text_buff2[1] = 0;
						battle_text_buff2[2] = bs_id;
						battle_text_buff2[3] = bs_id >> 8;
						battle_text_buff2[4] = 0xFF;

						//buffer exp number
						battle_text_buff3[0] = 0xFD;
						battle_text_buff3[1] = 1;
						battle_text_buff3[2] = 2; //halfword
						battle_text_buff3[3] = 5; //max digits
						battle_text_buff3[4] = exp_for_poke;
						battle_text_buff3[5] = exp_for_poke >> 8;
						battle_text_buff3[6] = 0xFF;

						prep_string(0xD, battle_stuff_ptr->expgetter_bank);
					}
					(*tracker)++;
				}
				else
					*tracker = 5; //just got evs
			}
			else
			{
				*tracker = 5;
			}
			(*sentin_pokes) >>= 1; //clear bits so it won't try to give experience to that poke again
		}
			break;
		case 3: //give exp and move expbar
			active_bank = battle_stuff_ptr->expgetter_bank;
			battle_bufferB[active_bank].command_id = 0;
			u16* lvl_stats = &battle_resources->before_lvl_up->hp;
			struct pokemon* poke = &party_player[*exp_getter_id];
			for (u8 i = 0; i < 6; i++)
			{
				lvl_stats[i] = get_attributes(poke, ATTR_TOTAL_HP + i, 0);
			}
			bb19_receive_exp(0, *exp_getter_id, exp_for_poke);
			mark_buffer_bank_for_execution(active_bank);
			(*tracker)++;
			break;
		case 4: //lvl up if necessary
		{
			active_bank = battle_stuff_ptr->expgetter_bank;
			u8* bufferB = &battle_bufferB[active_bank].command_id;
			if (bufferB[0] == 0x21 && bufferB[1] == 0xB) //prepare lvl up box
			{
				//get poke name
				battle_text_buff1[0] = 0xFD;
				battle_text_buff1[1] = 4;
				battle_text_buff1[2] = active_bank;
				battle_text_buff1[3] = *exp_getter_id;
				battle_text_buff1[4] = 0xFF;

				//get level
				battle_text_buff2[0] = 0xFD;
				battle_text_buff2[1] = 1;
				battle_text_buff2[2] = 1;
				battle_text_buff2[3] = 3;
				struct pokemon* poke = &party_player[*exp_getter_id];
				u8 level = get_attributes(poke, ATTR_LEVEL, 0);
				battle_text_buff2[4] = level;
				battle_text_buff2[5] = 0xFF;

				happiness_algorithm(poke, 0); //add happiness because of level up

				bs_push_current((void*) (0x082DABBD)); //level up battlescript

				exp_for_poke = read_hword(&bufferB[2]); //exp for another lvl

				leveled_up_in_battle |= bits_table[*exp_getter_id]; //set poke as leveled up, so it can evolve after it

				struct battle_participant* lvluper = NULL; //get changed stats via level up
				if (battle_team_id_by_side[0] == *exp_getter_id ||
						(battle_team_id_by_side[2] == *exp_getter_id && battle_flags.double_battle))
					lvluper = &battle_participants[active_bank];
				if (lvluper)
				{
					lvluper->level = level;
					lvluper->current_hp = get_attributes(poke, ATTR_CURRENT_HP, 0);
					lvluper->max_hp = get_attributes(poke, ATTR_TOTAL_HP, 0);
					u16* stats = &lvluper->atk;
					for (u8 i = 0; i < 5; i++)
					{
						stats[i] = get_attributes(poke, ATTR_ATTACK + i, 0);
					}
				}
			}
			else
				exp_for_poke = 0;
			(*tracker)++;
		}
			break;
		case 5: //check if we should give exp again(lvl up), increment looper or exit
			if (exp_for_poke)
				*tracker = 3; //give exp again
			else
			{
				if (*exp_getter_id == 5)
					*tracker = 6; //finish exp giving
				else {
					if(*exp_getter_id == 0 && !GET_CUSTOMFLAG(DISABLED_EXP_FLAG) && expshare_exp){
						prep_string(0x26b, battle_stuff_ptr->expgetter_bank);
					}
					*tracker = 2; //looper increment
				}
				(*exp_getter_id)++;
			}
			break;
		case 6: //exp giving finished
		default:
			battlescripts_curr_instruction += 2;
			break;
	}
}

void atk84_jumpifcannotsleep(void)
{
	void* jump_loc = (void*) read_word(battlescripts_curr_instruction + 1);
	u8 sweet = check_field_for_ability(ABILITY_SWEET_VEIL, get_bank_side(bank_attacker), 1);
	if (uproar_wakeup_check(bank_target))
		battlescripts_curr_instruction = jump_loc;
	else
	{
		if (check_ability(bank_target, ABILITY_INSOMNIA) || check_ability(bank_target, ABILITY_VITAL_SPIRIT))
		{
			record_usage_of_ability(bank_target, battle_participants[bank_target].ability_id);
			battle_communication_struct.multistring_chooser = 2;
			battlescripts_curr_instruction = jump_loc;
		}
		else if (sweet)
		{
			record_usage_of_ability(sweet - 1, ABILITY_SWEET_VEIL);
			battle_communication_struct.multistring_chooser = 3;
			battlescripts_curr_instruction = jump_loc;
		}
		else if (new_battlestruct->field_affecting.misty_terrain && GROUNDED(bank_target))
		{
			battle_communication_struct.multistring_chooser = 4;
			battlescripts_curr_instruction = jump_loc;
		}
		else if (new_battlestruct->field_affecting.electic_terrain && GROUNDED(bank_target))
		{
			battle_communication_struct.multistring_chooser = 5;
			battlescripts_curr_instruction = jump_loc;
		}
		else
			battlescripts_curr_instruction += 5;
	}
}

void atkE8_settypebasedhalvers(void)
{
	void* fail_loc = (void*) (read_word(battlescripts_curr_instruction + 1));
	if (current_move == MOVE_MUD_SPORT && !new_battlestruct->field_affecting.mudsport)
	{
		battle_communication_struct.multistring_chooser = 0;
		new_battlestruct->field_affecting.mudsport = 5;
		battlescripts_curr_instruction += 5;
	}
	else if (current_move == MOVE_WATER_SPORT && !new_battlestruct->field_affecting.watersport)
	{
		battle_communication_struct.multistring_chooser = 1;
		new_battlestruct->field_affecting.watersport = 5;
		battlescripts_curr_instruction += 5;
	}
	else
		battlescripts_curr_instruction = fail_loc;
}

void atk09_attackanimation(void)
{
	if (battle_execution_buffer)
	{
		return;
	}
	//check if animation doesnt play
	if (((hitmarker & HITMARKER_NO_ANIMATIONS) || new_battlestruct->various.dont_play_move_anim || !MOVE_WORKED) &&
			current_move != MOVE_TRANSFORM && current_move != MOVE_SUBSTITUTE)
	{
	}
		//animation MAY play
	else
	{
		u8 move_trgt = move_table[current_move].target;
		//check if it's not hitting another target in multi-target moves
		if (!((move_trgt == move_target_both || move_trgt == move_target_foes_and_ally ||
				move_trgt == move_target_depends) && battle_scripting.field19))
		{
			//at this point animation plays
			if (find_move_in_table(current_move, dancing_moves) && new_battlestruct->various.original_dancer == 0)
			{
				new_battlestruct->various.original_dancer = (bank_attacker + 1);
			}
			active_bank = bank_attacker;
			bbF_move_animation(0, current_move, battle_scripting.field18, curr_move_BP, damage_loc,
					battle_participants[bank_attacker].happiness, &disable_structs[bank_attacker], multihit_counter);
			mark_buffer_bank_for_execution(active_bank);
		}
	}
	battle_scripting.field18++;
	battle_scripting.field19++;
	battlescripts_curr_instruction++;
}

void atk89_changestats(void) //BANK orred by 0x40 if self inflicted and fail address
{
	u8 bank = read_byte(battlescripts_curr_instruction + 1);
	u8 bits = bank & 0x40;
	bank = get_battle_bank(BIC(bank, 0x40));
	if (change_stats(bank, bits | STAT_CHANGE_VALUES | STAT_PRINTABILITY,
			(void*) read_word(battlescripts_curr_instruction + 2)) != STAT_UNABLE)
		battlescripts_curr_instruction += 6;
}

void atk45_playanimation(void) //u8 bank, u8 animID, void halfword helper
{
	u8 bank = get_battle_bank(read_byte(battlescripts_curr_instruction + 1));
	u8 animID = read_byte(battlescripts_curr_instruction + 2);
	u16 info = 0;
	void* info_ptr = (void*) read_word(battlescripts_curr_instruction + 3);
	if (info_ptr)
		info = read_hword(info_ptr);

	//always play animation for certain things no matter whether battle scene is on or off
	static const u8 always_play[] = {0, 2, 3, 0x11, 0x1E, 0x1F, 0x20, 0x21, 0xFF};
	if (!(hitmarker & HITMARKER_NO_ANIMATIONS) || (findability_in_table(animID, always_play)))
	{
		active_bank = bank;
		bb34_battle_animation(0, animID, info);
		mark_buffer_bank_for_execution(bank);
	}
	battlescripts_curr_instruction += 7;
}

bool exec_castform_script(u8 bank, bool use_end3);

bool exec_cherrim_script(u8 bank, bool use_end3);

void atkE7_check_castform_cherrim(void)
{
	battlescripts_curr_instruction++;
	if (exec_castform_script(battle_scripting.active_bank, 1))
	{
		return;
	};
	if (exec_cherrim_script(battle_scripting.active_bank, 1))
	{
		return;
	};
}

void atk41_call(void)
{
	bs_push(battlescripts_curr_instruction + 5, (void*) read_word(battlescripts_curr_instruction + 1));
}

//extern BS commands in other files
void atk01_accuracy_calc(void);
void atk04_critcalc(void);
void atk05_dmg_calc(void);
void atk07_final_dmg_calc(void);
void atk83_callasm(void);
void atkEF_ballthrow(void);
void atkF0_copy_caught_poke(void);
void atkF1_setpoke_as_caught(void);
void atkF2_display_dex_info(void);
void atkF3_nickname_caught_poke(void);
void atkF9_pollen_puff(void); //JeremyZ
void atkFA_blowifnotdamp(void); //JeremyZ

const command bs_commands[] = {atk00_move_canceller,    //	0
		atk01_accuracy_calc,    //	1
		atk02_attackstring,    //	2
		(void*) 0x8046A3D,    //	3
		atk04_critcalc,    //	4
		atk05_dmg_calc,    //	5
		(void*) 0x8047039,    //	6
		atk07_final_dmg_calc,    //	7
		(void*) 0x8047AA5,    //	8
		atk09_attackanimation,    //	9
		(void*) 0x8047DC9,    //	 0xA
		(void*) 0x8047DE9,    //	 0xB
		atk0C_datahpupdate,    //	 0xC
		(void*) 0x80482BD,    //	 0xD
		(void*) 0x8048311,    //	 0xE
		atk0F_resultmessage,    //	 0xF
		(void*) 0x8048591,    //	 0x10
		(void*) 0x80485D1,    //	 0x11
		(void*) 0x8048615,    //	 0x12
		atk13_printfromtable,    //	 0x13
		(void*) 0x80486C5,    //	 0x14
		atk15_setmoveeffectchance,    //	 0x15
		atk16_setmoveeffectprimary,    //	 0x16
		atk17_setmoveeffectsecondary,    //	 0x17
		(void*) 0x8049AE1,    //	 0x18
		(void*) 0x8049B5D,    //	 0x19
		(void*) 0x8049E41,    //	 0x1A
		(void*) 0x8049E7D,    //	 0x1B
		(void*) 0x8049F05,    //	 0x1C
		(void*) 0x8049F7D,    //	 0x1D
		(void*) 0x8049FF5,    //	 0x1E
		(void*) 0x804A0DD,    //	 0x1F
		(void*) 0x804A155,    //	 0x20
		(void*) 0x804A24D,    //	 0x21
		(void*) 0x804A2D1,    //	 0x22
		atk23_exp_evs_lvlup,    //	 0x23
		(void*) 0x804ACD1,    //	 0x24
		(void*) 0x804AF71,    //	 0x25
		(void*) 0x804AF89,    //	 0x26
		(void*) 0x804AFA1,    //	 0x27
		(void*) 0x804AFE9,    //	 0x28
		(void*) 0x804B009,    //	 0x29
		(void*) 0x804B0A9,    //	 0x2A
		(void*) 0x804B151,    //	 0x2B
		(void*) 0x804B205,    //	 0x2C
		(void*) 0x804B28D,    //	 0x2D
		(void*) 0x804B311,    //	 0x2E
		(void*) 0x804B339,    //	 0x2F
		(void*) 0x804B365,    //	 0x30
		(void*) 0x804B391,    //	 0x31
		(void*) 0x804B3E5,    //	 0x32
		(void*) 0x804B451,    //	 0x33
		(void*) 0x804B47D,    //	 0x34
		(void*) 0x804B4B5,    //	 0x35
		(void*) 0x804B4F9,    //	 0x36
		(void*) 0x804B525,    //	 0x37
		(void*) 0x804B55D,    //	 0x38
		(void*) 0x804B5A1,    //	 0x39
		(void*) 0x804B5E1,    //	 0x3A
		(void*) 0x804B601,    //	 0x3B
		(void*) 0x804B659,    //	 0x3C
		(void*) 0x804B665,    //	 0x3D
		(void*) 0x804B6A5,    //	 0x3E
		(void*) 0x804B6BD,    //	 0x3F
		(void*) 0x804643D,    //	 0x40
		atk41_call,    //	 0x41
		atk42_jump_if_type,    //	 0x42
		(void*) 0x804B785,    //	 0x43
		(void*) 0x804B7D1,    //	 0x44
		atk45_playanimation,    //	 0x45
		(void*) 0x804B8B1,    //	 0x46
		atk47_set_statchange_values,    //	 0x47
		(void*) 0x804B9D9,    //	 0x48
		atk49_move_end_turn,    //	 0x49
		(void*) 0x804C5F5,    //	 0x4A
		(void*) 0x804C845,    //	 0x4B
		(void*) 0x804C895,    //	 0x4C
		(void*) 0x804C905,    //	 0x4D
		(void*) 0x804CAE9,    //	 0x4E
		(void*) 0x804CBB1,    //	 0x4F
		(void*) 0x804CF89,    //	 0x50
		(void*) 0x804D821,    //	 0x51
		(void*) 0x804DAAD,    //	 0x52
		(void*) 0x804DDA9,    //	 0x53
		(void*) 0x804DDD9,    //	 0x54
		(void*) 0x804DE15,    //	 0x55
		atk56_prepare_fainting_cry,    //	 0x56
		(void*) 0x804DE81,    //	 0x57
		(void*) 0x804DEB9,    //	 0x58
		(void*) 0x804DEED,    //	 0x59
		(void*) 0x804E039,    //	 0x5A
		(void*) 0x804E3C9,    //	 0x5B
		atk5C_hitanimation,    //	 0x5C
		atk5D_moneyreward,    //	 0x5D
		(void*) 0x804E765,    //	 0x5E
		(void*) 0x804E819,    //	 0x5F
		(void*) 0x804E869,    //	 0x60
		(void*) 0x804E899,    //	 0x61
		(void*) 0x804E961,    //	 0x62
		(void*) 0x804E991,    //	 0x63
		(void*) 0x804E9F5,    //	 0x64
		(void*) 0x804EA85,    //	 0x65
		(void*) 0x804EB2D,    //	 0x66
		(void*) 0x804EBC1,    //	 0x67
		(void*) 0x804ECA5,    //	 0x68
		(void*) 0x804ECDD,    //	 0x69
		atk6A_remove_item,    //	 0x6A
		(void*) 0x804EEC9,    //	 0x6B
		(void*) 0x804EF05,    //	 0x6C
		(void*) 0x804F4D5,    //	 0x6D
		(void*) 0x804F4ED,    //	 0x6E
		(void*) 0x804F50D,    //	 0x6F
		atk70_record_ability_of_bank,    //	 0x70
		(void*) 0x804F59D,    //	 0x71
		(void*) 0x804F5B5,    //	 0x72
		(void*) 0x804F5F9,    //	 0x73
		(void*) 0x804F6A5,    //	 0x74
		(void*) 0x804F755,    //	 0x75
		(void*) 0x804F7AD,    //	 0x76
		atk77_set_protect_stuff,    //	 0x77
		atk78_explodeifnotdamp,    //	 0x78
		(void*) 0x804FFE5,    //	 0x79
		(void*) 0x8050045,    //	 0x7A
		(void*) 0x80500E9,    //	 0x7B
		(void*) 0x8050165,    //	 0x7C
		atk7D_set_rain,    //	 0x7D
		atk7E_set_reflect,    //	 0x7E
		atk7F_set_leech_seed,    //	 0x7F
		(void*) 0x80504A9,    //	 0x80
		(void*) 0x8050529,    //	 0x81
		(void*) 0x80505F9,    //	 0x82
		atk83_callasm,    //	 0x83
		atk84_jumpifcannotsleep,    //	 0x84
		(void*) 0x8050769,    //	 0x85
		(void*) 0x80507E5,    //	 0x86
		(void*) 0x8050905,    //	 0x87
		atk88_drain_damage,    //	 0x88
		atk89_changestats,    //	 0x89
		(void*) 0x8050EED,    //	 0x8A
		(void*) 0x8050F41,    //	 0x8B
		(void*) 0x8050FB1,    //	 0x8C
		atk8D_multihit_move_loop_counter,    //	 0x8D
		(void*) 0x805103D,    //	 0x8E
		(void*) 0x805112D,    //	 0x8F
		(void*) 0x8051425,    //	 0x90
		(void*) 0x80515C9,    //	 0x91
		atk92_set_lightscreen,    //	 0x92
		atk93_ko_move,    //	 0x93
		(void*) 0x8051A85,    //	 0x94
		atk95_set_sandstorm,    //	 0x95
		atk96_weather_damage,    //	 0x96
		(void*) 0x8051C91,    //	 0x97
		(void*) 0x8051E49,    //	 0x98
		(void*) 0x8051F59,    //	 0x99
		(void*) 0x8052001,    //	 0x9A
		(void*) 0x805205D,    //	 0x9B
		(void*) 0x80521FD,    //	 0x9C
		(void*) 0x8052301,    //	 0x9D
		atk9E_metronome_chooser,    //	 0x9E
		(void*) 0x8052585,    //	 0x9F
		(void*) 0x80525B5,    //	 0xA0
		(void*) 0x8052609,    //	 0xA1
		(void*) 0x8052701,    //	 0xA2
		atkA3_disable_move,    //	 0xA3
		atkA4_encore_move,    //	 0xA4
		(void*) 0x8052A71,    //	 0xA5
		(void*) 0x8052B35,    //	 0xA6
		atkA7_set_alwayshits_flag,    //	 0xA7
		(void*) 0x8052D8D,    //	 0xA8
		atkA9_sleeptalkmovechoose,    //	 0xA9
		(void*) 0x8053151,    //	 0xAA
		(void*) 0x80531E1,    //	 0xAB
		(void*) 0x80531F9,    //	 0xAC
		(void*) 0x8053261,    //	 0xAD
		(void*) 0x8053439,    //	 0xAE
		(void*) 0x805371D,    //	 0xAF
		(void*) 0x80537A1,    //	 0xB0
		(void*) 0x805382D,    //	 0xB1
		(void*) 0x805385D,    //	 0xB2
		(void*) 0x8053915,    //	 0xB3
		(void*) 0x8053A91,    //	 0xB4
		atkB5_furycutter_calc,    //	 0xB5
		(void*) 0x8053BAD,    //	 0xB6
		atkB7_present_calc,    //	 0xB7
		(void*) 0x8053CFD,    //	 0xB8
		(void*) 0x8053DA5,    //	 0xB9
		(void*) 0x8053EC9,    //	 0xBA
		atkBB_set_sunny,    //	 0xBB
		(void*) 0x80540B5,    //	 0xBC
		(void*) 0x8054135,    //	 0xBD
		atkBE_rapidspin_away,    //	 0xBE
		(void*) 0x80542C9,    //	 0xBF
		(void*) 0x80542F9,    //	 0xC0
		(void*) 0x8054401,    //	 0xC1
		(void*) 0x8054525,    //	 0xC2
		(void*) 0x8054599,    //	 0xC3
		(void*) 0x80546E5,    //	 0xC4
		atkC5_hide_pre_attack,    //	 0xC5
		atkC6_unhide_post_attack,    //	 0xC6
		(void*) 0x8054A09,    //	 0xC7
		atkC8_set_hail,    //	 0xC8
		(void*) 0x8054AA1,    //	 0xC9
		(void*) 0x8054B3D,    //	 0xCA
		(void*) 0x8054B89,    //	 0xCB
		atkCC_nature_power,    //	 0xCC
		(void*) 0x8054C61,    //	 0xCD
		(void*) 0x8054CE5,    //	 0xCE
		(void*) 0x8054D3D,    //	 0xCF
		atkD0_set_taunt,    //	 0xD0
		(void*) 0x8054E0D,    //	 0xD1
		atkD2_itemswap,    //	 0xD2
		(void*) 0x8055149,    //	 0xD3
		atkD4_wish_effect,    //	 0xD4
		(void*) 0x8055295,    //	 0xD5
		(void*) 0x80552ED,    //	 0xD6
		(void*) 0x805534D,    //	 0xD7
		(void*) 0x80553BD,    //	 0xD8
		(void*) 0x8055429,    //	 0xD9
		(void*) 0x805548D,    //	 0xDA
		(void*) 0x8055525,    //	 0xDB
		(void*) 0x805562D,    //	 0xDC
		(void*) 0x8055685,    //	 0xDD
		atkDE_assistmovechoose,    //	 0xDE
		(void*) 0x805589D,    //	 0xDF
		(void*) 0x8055921,    //	 0xE0
		atkE1_intimidate_loop,    //	 0xE1
		atkE2_switchout_abilities,    //	 0xE2
		(void*) 0x8055AF5,    //	 0xE3
		atkE4_secretpowereffect,    //	 0xE4
		(void*) 0x8055C01,    //	 0xE5
		(void*) 0x8055DFD,    //	 0xE6
		atkE7_check_castform_cherrim,    //	 0xE7
		atkE8_settypebasedhalvers,    //	 0xE8
		(void*) 0x8055F5D,    //	 0xE9
		(void*) 0x8056015,    //	 0xEA
		(void*) 0x80560BD,    //	 0xEB
		(void*) 0x805616D,    //	 0xEC
		(void*) 0x8056231,    //	 0xED
		(void*) 0x8056285,    //	 0xEE
		atkEF_ballthrow,    //	 0xEF
		atkF0_copy_caught_poke,    //	 0xF0
		atkF1_setpoke_as_caught,    //	 0xF1
		atkF2_display_dex_info,    //	 0xF2
		atkF3_nickname_caught_poke,    //	 0xF3
		(void*) 0x8056E79,    //	 0xF4
		(void*) 0x8056EA9,    //	 0xF5
		(void*) 0x8056ED1,    //	 0xF6
		(void*) 0x8056EDD,    //	 0xF7
		(void*) 0x8056EF9,    //	 0xF8
		atkF9_pollen_puff,    //	 0xF9, JeremyZ
		atkFA_blowifnotdamp,    //	 0xFA, JeremyZ
};

void execute_bs_command(void)
{
	if (battle_execution_buffer)
	{
		return;
	}
	bs_commands[read_byte(battlescripts_curr_instruction)]();
}
