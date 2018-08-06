#include "defines.h"
#include "static_references.h"

u16 apply_statboost(u16 stat, u8 boost);
u8 get_bank_side(u8 bank);
bool is_bank_present(u8 bank);
u8 has_ability_effect(u8 bank, u8 mold_breaker);
bool check_ability(u8 bank, u8 ability);
void atk0C_datahpupdate(void);
u8 is_of_type(u8 bank, u8 type);
u8 get_item_effect(u8 bank, u8 check_negating_effects);
void update_rtc(void);
void prep_string(u16 strID, u8 bank);

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
	struct pokemon* poke_address;
	if (opponent_side)
		poke_address = &party_opponent[0];
	else
		poke_address = &party_player[0];
	for (u8 i = 0; i < 6; i++)
	{
		u16 mega_current_species = get_attributes(poke_address + i, ATTR_SPECIES, 0);
		u16 current_hp = get_attributes(poke_address + i, ATTR_CURRENT_HP, 0);
		if (current_hp && !battle_outcome)
			continue;
		u16 species_to_revert = 0;
		const struct evolution_sub* evos = GET_EVO_TABLE(mega_current_species);
		if (mega_current_species == 0x42E)
			species_to_revert = ((u16*) sav1->balls_pocket)[i];
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
			set_attributes(poke_address + i, ATTR_SPECIES, &species_to_revert);
			calculate_stats_pokekmon(poke_address + i);
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

