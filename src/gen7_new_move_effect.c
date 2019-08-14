#include "defines.h"
#include "static_references.h"

u16 apply_statboost(u16 stat, u8 boost);
u8 get_bank_side(u8 bank);
bool is_bank_present(u32 bank);
u8 has_ability_effect(u8 bank, u8 mold_breaker);
bool check_ability(u8 bank, u8 ability);
void atk0C_datahpupdate(void);
u8 is_of_type(u8 bank, u8 type);
u8 get_item_effect(u8 bank, u8 check_negating_effects);
void update_rtc(void);
void prep_string(u16 strID, u8 bank);
s8 get_priority(u16 move, u8 bank);
void bs_push_current(void* now);
u8 check_field_for_ability(enum poke_abilities ability, u8 side_to_ignore, u8 mold);

bool time_check(u8 from, u8 to)
{
	update_rtc();
	u8 hour = rtc_hex.hour;
	if (to >= from)
	{
		if (hour >= from && hour <= to)
			return 1;
		return 0;
	}
	else
	{
		if (hour >= from || hour <= to)
			return 1;
		return 0;
	}
}

//Rage Powder
bool is_immune_to_powder(u8 bank)
{
	if (is_of_type(bank, TYPE_GRASS) || check_ability(bank, ABILITY_OVERCOAT) ||
		get_item_effect(bank_attacker, 1) == ITEM_EFFECT_SAFETYGOOGLES)
		return 1;
	return 0;
}

//Photon Geyser & Z_Necrozma
bool photon_geyser_special(u16 move)
{
	if (move == MOVE_PHOTON_GEYSER || move == MOVE_Z_NECROZMA)
	{
		u16 attack_stat = apply_statboost(battle_participants[bank_attacker].atk,
				battle_participants[bank_attacker].atk_buff);
		u16 spatk_stat = apply_statboost(battle_participants[bank_attacker].sp_atk,
				battle_participants[bank_attacker].sp_atk_buff);
		if (attack_stat > spatk_stat)
			return 0; //switch to a physical move
	}
	return 1; // remain a special move
}

//Pollen Puff, JeremyZ
void atkF9_pollen_puff(void)
{
	if ((bank_target ^ bank_attacker) == 2)
	{ //Targeting Friend
		dynamic_base_power = 0;
		if (battle_participants[bank_target].current_hp >= battle_participants[bank_target].max_hp)
			battlescripts_curr_instruction = (void*) 0x082D9EFB;
		else if (new_battlestruct->bank_affecting[bank_target].heal_block)
			battlescripts_curr_instruction = BS_HEALBLOCK_PREVENTS;
		else
		{
			damage_loc = (battle_participants[bank_target].max_hp / 2) * (-1);
			battlescripts_curr_instruction = (void*) 0x082D9EE1;
		}
	}
	else
		dynamic_base_power = move_table[current_move].base_power;
	if (dynamic_base_power)
		battlescripts_curr_instruction = (void*) 0x082D8A30;
}

//Mind Blown
void jumpifuserheadblown(void)
{
	if (!new_battlestruct->bank_affecting[bank_attacker].head_blown) //Not Jump
		battlescripts_curr_instruction += 4;
	else //Jump
		battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
}

void atkFA_blowifnotdamp(void)
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
	damage_loc = (battle_participants[bank_attacker].max_hp + 1) / 2;
	if (check_ability(bank_attacker, ABILITY_MAGIC_GUARD) || new_battlestruct->bank_affecting[active_bank].head_blown)
		damage_loc = 0;
	//set head_blown flag
	new_battlestruct->bank_affecting[active_bank].head_blown = 1;
	battlescripts_curr_instruction++; //Needs Revision
}

//Spotlight
void set_spotlight(void)
{
	u8 target_side = get_bank_side(bank_target);
	side_timers[target_side].followme_timer = 1;
	side_timers[target_side].followme_target = bank_target;
}

//Throat Chop
void set_throatchop(void)
{
	void* failjump = (void*) read_word(battlescripts_curr_instruction /*+ 1*/);
	if (new_battlestruct->bank_affecting[bank_target].throatchop_timer)
		battlescripts_curr_instruction = failjump;
	else
	{
		new_battlestruct->bank_affecting[bank_target].throatchop_timer = 2;
		battlescripts_curr_instruction += 4;//5;
	}
}

//Speed Swap
void speed_swap(void)
{
	u16 speed_temp = battle_participants[bank_attacker].spd;
	battle_participants[bank_attacker].spd = battle_participants[bank_target].spd;
	battle_participants[bank_target].spd = speed_temp;
}

//Beak Blast
void set_beak_charge(void)
{
	for (u8 i = 0; i < 4; i++)
	{
		if (menu_choice_pbs[i] == 0 && chosen_move_by_banks[i] == MOVE_BEAK_BLAST
			&& !(disable_structs[i].truant_counter & 1) && !(protect_structs[i].flag0_onlystruggle))
		{
			new_battlestruct->bank_affecting[i].beak_blast_charge = 1;
		}
		else
			new_battlestruct->bank_affecting[i].beak_blast_charge = 0;
	}
}

//Shell Trap
void set_shell_charge(void)
{
	for (u8 i = 0; i < 4; i++)
	{
		if (menu_choice_pbs[i] == 0 && chosen_move_by_banks[i] == MOVE_SHELL_TRAP &&
			!battle_participants[i].status.flags.sleep
			&& !(disable_structs[i].truant_counter & 1) && !(protect_structs[i].flag0_onlystruggle))
		{
			new_battlestruct->bank_affecting[i].shell_trap_charge = 1;
		}
		else
			new_battlestruct->bank_affecting[i].shell_trap_charge = 0;
	}
}

//Mega Related
void revert_mega_to_normalform_new(u8 opponent_side)
{
	struct pokemon* poke_address = opponent_side ? party_opponent : party_player;
	for (struct pokemon* i = poke_address + 6; poke_address < i; poke_address++)
	{
		if (poke_address->current_hp && !battle_outcome)
			continue;
		u16 species_to_revert = 0;
		u16 mega_current_species = poke_address->spieces;
		const struct evolution_sub* evos = GET_EVO_TABLE(mega_current_species);
		if (mega_current_species == POKE_ULTRA_NECROZMA)
			species_to_revert = ((u16*) sav1->balls_pocket)[opponent_side];
		for (u8 j = 0; j < NUM_OF_EVOS; j++)
		{
			if (evos[j].method == 0xFF)
			{
				species_to_revert = evos[j].poke;
				break;
			}
		}
		if (species_to_revert)
		{
			set_attributes(poke_address, ATTR_SPECIES, &species_to_revert);
			calculate_stats_pokekmon(poke_address);
		}
	}
	return;
}

//Start Z
void print_start_z(void)
{
	prep_string(new_battlestruct->various.var2, bank_attacker);
	battle_communication_struct.is_message_displayed = 1;
}

//Spit Up
void jumpifnostockpile(void)
{
	if (new_battlestruct->bank_affecting[bank_attacker].stockpile_counter) //Not Jump
		battlescripts_curr_instruction += 4;
	else //Jump
		battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
}

//Z Move Protected
u8 z_protect_affects(u16 move)
{
    u8 split = move_table[move].split;
    u8 target = move_table[move].target;
    u8 targets_side = get_bank_side(bank_target);
	return (move >= MOVE_Z_NORMAL_PHYS && move <= MOVE_Z_ASH_GRENINJA &&
		(protect_structs[bank_target].flag0_protect ||
		(new_battlestruct->bank_affecting[bank_target].kings_shield && split != 2) ||
		(new_battlestruct->bank_affecting[bank_target].spiky_shield) ||
		(new_battlestruct->bank_affecting[bank_target].baneful_bunker) ||
		(new_battlestruct->side_affecting[targets_side].quick_guard && get_priority(current_move, bank_attacker) > 0) ||
		(new_battlestruct->side_affecting[targets_side].mat_block && split != 2) ||
		(new_battlestruct->side_affecting[targets_side].wide_guard && (target == move_target_both || target == move_target_foes_and_ally))
		));
}

//Calculate Recoil Damage
void calc_recoil_dmg2(void)
{
	if ((check_ability(bank_attacker, ABILITY_ROCK_HEAD) || check_ability(bank_attacker, ABILITY_MAGIC_GUARD)) && current_move != MOVE_STRUGGLE) {
		record_usage_of_ability(bank_attacker, battle_participants[bank_attacker].ability_id);
		damage_loc = 0;
		battle_communication_struct.multistring_chooser = 0;
	}
	else {
		u16 recoil_dmg;
		//formula is dmg = HP dealt / arg2 or MaxHP / arg2 if value is negative
		s8 arg = move_table[current_move].arg2;
		if (arg < 0)
			recoil_dmg = battle_participants[bank_attacker].max_hp / (arg * -1);
		else
			recoil_dmg = hp_dealt / arg;
		damage_loc = ATLEAST_ONE(recoil_dmg);
		battle_communication_struct.multistring_chooser = 1;
	}
	battlescripts_curr_instruction++;
}

//Effects of Clanging Scales and Clangorous Soulblaze
bool clanging_scales_stat(void)
{	
	if ((MOVE_WORKED || new_battlestruct->bank_affecting[bank_attacker].move_worked_thisturn) //move has worked at least once this turn
		&& (!battle_flags.double_battle || !is_bank_present(bank_target ^ 2) || bank_target > (bank_target ^ 2))) //if it is the last target
	{
		if (current_move == MOVE_CLANGING_SCALES)
		{
			bs_push_current(BS_CHANGE_ATK_STAT);
			battle_scripting.stat_changer = move_table[current_move].arg1;
		}
		if (current_move == MOVE_Z_KOMMO_O)
			bs_push_current(BS_MULTIPLESTATCHANCE_ATK_CERTAIN);
		return 1;
	}
	return 0;
}


bool check_ability_with_mold(u8 bank, u8 ability) {
	return (has_ability_effect(bank, 1) && battle_participants[bank].ability_id == ability);
}

void check_weather_trio(void) {
	if (battle_weather.flags.heavy_rain && !check_field_for_ability(ABILITY_PRIMORDIAL_SEA, 3, 0)) {
		battle_weather.flags.downpour = 0;
		battle_weather.flags.rain = 0;
		battle_weather.flags.heavy_rain = 0;
	}
	if (battle_weather.flags.harsh_sun && !check_field_for_ability(ABILITY_DESOLATE_LAND, 3, 0)) {
		battle_weather.flags.sun = 0;
		battle_weather.flags.harsh_sun = 0;
	}
	if (battle_weather.flags.air_current && !check_field_for_ability(ABILITY_DELTA_STREAM, 3, 0)) {
		battle_weather.flags.air_current = 0;
	}
}