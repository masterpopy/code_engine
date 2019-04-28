#include "defines.h"
#include "static_references.h"

u8 get_item_effect(u8 bank, u8 check_negating_effects);
u16 check_z_move(u32 move, u32 bank);
u16 get_mega_species(u8 bank, u8 chosen_method);
bool is_in_tag_battle(void);


void reset_indicators_height_except_bank(u8 bank)
{
	struct mega_related* mega = &new_battlestruct->mega_related;
	for (u8 i = 0; i < no_of_all_banks; i++)
	{
		if (i != bank)
		{
			objects[mega->indicator_id_pbs[i]].pos2.y = 0;
		}
	}
}

void revert_triggers(u8 bank){
	struct object* trigger = &objects[new_battlestruct->mega_related.trigger_id];
	if (trigger->private[PALLET_STATE] == TRIGGER_ON)
	{
		trigger->private[PALLET_STATE] = REVERT_COLORS;
	}
	if (bank == 0)
		new_battlestruct->mega_related.user_trigger = 0;
	else if (bank == 2)
		new_battlestruct->mega_related.ally_trigger = 0;
}

void clear_triggers(u8 bank)
{
	revert_triggers(bank);
	reset_indicators_height_except_bank(bank);
}

void set_mega_triggers(u8 bank, u8 set_mode)
{
	if (bank == 0)
		new_battlestruct->mega_related.user_trigger = set_mode;
	else if (bank == 2)
		new_battlestruct->mega_related.ally_trigger = set_mode;
	if (battle_flags.link)
		new_battlestruct->mega_related.link_indicator[bank] = set_mode;
}

u32 get_item_extra_param(u32 item)
{
	return (*item_table)[item].extra_param;
}

u32 get_battle_item_extra_param(u32 bank)
{
	return get_item_extra_param(battle_participants[bank].held_item);
}

#define choosen_z_move(bank)(check_z_move(battle_participants[bank].moves[move_selection_cursor_pbs[bank]], bank))


bool can_set_z_trigger(u8 bank)
{
	if (!(checkitem(622, 1) && choosen_z_move(bank)))
		return false;
	struct mega_related* mega = &new_battlestruct->mega_related;
	if (bank == 0 && mega->user_trigger != 1 &&
		((battle_flags.multibattle && !(mega->z_happened_pbs & 0x1)) || !(mega->z_happened_pbs & 0x5)))
	{
		return true;
	}
	else if (bank == 2 && mega->user_trigger != 1 && mega->ally_trigger != 1 &&
			 ((battle_flags.multibattle && !(mega->z_happened_pbs & 0x4)) || !(mega->z_happened_pbs & 0x5)))
	{
		return true;
	}
	return false;
}

u16 get_mega_species(u8 bank, u8 chosen_method)
{
	u16 species = battle_participants[bank].species;
	u16 target_species = 0;
	u16 item_effect = get_item_effect(bank, 0);
	const struct evolution_sub* evo = GET_EVO_TABLE(species);
	for (u8 i = 0; i < NUM_OF_EVOS; i++)
	{
		u8 method = evo[i].method;
		if (method == chosen_method)
		{
			switch (method)
			{
				case 0xFB: // regular mega
				{
					if (item_effect == ITEM_EFFECT_MEGASTONE)
					{
						CHECK_SPECIES:
						if (evo[i].poke == get_battle_item_extra_param(bank))
						{
							target_species = get_battle_item_extra_param(bank);
						}
					}
				}
					break;
				case 0xFD: //primal
				{
					if (item_effect == ITEM_EFFECT_PRIMALORB)
					{
						goto CHECK_SPECIES;
					}
				}
					break;
				case 0xFC: //fervent wish mega
				{
					//JeremyZ, cannot mega if holding z-crystal
					if (item_effect == ITEM_EFFECT_ZCRYSTAL)
						break;
					u16 fervent_move = evo[i].paramter;
					if (fervent_move)
					{
						for (u8 j = 0; j < 4; j++)
						{
							if (battle_participants[bank].moves[j] == fervent_move)
							{
								SET_SPECIES:
								target_species = evo[i].poke;
								break;
							}
						}
					}
				}
					break;
				case 0xFA: //Ultra Burst
					// if(item_effect == ITEM_EFFECT_ZCRYSTAL)
					if (battle_participants[bank].held_item == 0x283) //JeremyZ
						goto SET_SPECIES;
					break;
			}
		}
		if (target_species)
			break;
	}
	return target_species;
}

u8 can_set_mega_trigger(u8 bank) //JeremyZ
{
	struct mega_related* mega = &new_battlestruct->mega_related;
	bool res = 0;
	int mega_mode = 0;
	if (bank == 0 && mega->user_trigger < 3 &&
		((battle_flags.multibattle && !(mega->evo_happened_pbs & 0x1)) || !(mega->evo_happened_pbs & 0x5)))
	{
		res = true;
	}
	else if (bank == 2 && mega->user_trigger < 3 && mega->ally_trigger < 3 &&
			 ((battle_flags.multibattle && !(mega->evo_happened_pbs & 0x4)) || !(mega->evo_happened_pbs & 0x5)))
	{
		res = true;
	}
	if (res && checkitem(KEYSTONE, 1))
	{
		if (get_mega_species(bank, 0xFB))
		{
			//normal
			mega_mode = 3;
		}
		else if (get_mega_species(bank, 0xFC))
		{
			//fervent wish mega
			mega_mode = 3; //2;
		}
	}
	//Ultra Burst
	if (mega_mode == 0 && get_mega_species(bank, 0xFA))
		mega_mode = 2;
	//Z-Move
	else if (mega_mode == 0 && can_set_z_trigger(bank))
		mega_mode = 1;
	return mega_mode;
}


void set_mega_triggers_for_user_team(u8 bank)
{
	u8 set_mode = can_set_mega_trigger(bank);
	if (set_mode)
	{
		set_mega_triggers(bank, set_mode);
		objects[new_battlestruct->mega_related.trigger_id].private[PALLET_STATE] = LIGHT_UP_TRIGGER;
		play_sound(2);
	}

}

/*void revert_mega_to_normalform(u8 teamID, u8 opponent_side)
{
	struct pokemon* poke_address;
	if (opponent_side)
		poke_address = &party_opponent[teamID];
	else
		poke_address = &party_player[teamID];
	u16 mega_current_species = get_attributes(poke_address, ATTR_SPECIES, 0);
	u16 species_to_revert = 0;
	const struct evolution_sub* evos = GET_EVO_TABLE(mega_current_species);
	if (mega_current_species == 0x42E)
		species_to_revert = ((u16*) sav1->balls_pocket)[teamID];
	for (u8 i = 0; i < NUM_OF_EVOS; i++)
	{
		if (evos[i].method == 0xFF)
		{
			species_to_revert = evos[i].poke;
			break;
		}
	}
	if (species_to_revert)
	{
		set_attributes(poke_address, ATTR_SPECIES, &species_to_revert);
		calculate_stats_pokekmon(poke_address);
	}
	return;
}*/

