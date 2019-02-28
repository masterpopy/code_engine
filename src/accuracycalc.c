#include "defines.h"
#include "static_references.h"

u8 is_of_type(u8 bank, u8 type);
u32 percent_boost(u32 number, u16 percent);
u32 percent_lose(u32 number, u16 percent);
s8 get_priority(u16 move, u8 bank);
u16 type_effectiveness_calc(u16 move, u8 move_type, u8 atk_bank, u8 def_bank, u8 effects_handling_and_recording);
u8 get_attacking_move_type();
u8 get_item_effect(u8 bank, u8 check_negating_effects);
u8 ability_battle_effects(u8 switch_id, u8 bank, u8 ability_to_check, u8 special_cases_argument, u16 move);
u8 has_ability_effect(u8 bank, u8 mold_breaker);
u8 weather_abilities_effect();
bool does_move_make_contact(u16 move, u8 atk_bank);
u8 find_move_in_table(u16 move, const u16* table_ptr);
u8 check_ability(u8 bank, u8 ability);
u8 get_bank_side(u8 bank);
u32 random_value(u32 limit);
u8 check_field_for_ability(enum poke_abilities ability, u8 side_to_ignore, u8 mold);

u8 protect_affects(u16 move, u8 set)
{
    u8 effect = 0;
    u8 protect_flag = move_table[move].move_flags.flags.affected_by_protect;
    if(!protect_flag)
        return effect;
    u8 split = move_table[move].split;
    u8 contact = does_move_make_contact(move, bank_attacker);
    u8 target = move_table[move].target;
    u8 targets_side = get_bank_side(bank_target);
    if (protect_structs[bank_target].flag0_protect)
        effect = 1;
    else if (new_battlestruct->bank_affecting[bank_target].kings_shield && split != 2)
    {
        effect = 1;
        if (contact && set)
            new_battlestruct->bank_affecting[bank_attacker].kingsshield_damage = 1;
    }
    else if (new_battlestruct->bank_affecting[bank_target].spiky_shield)
    {
        effect = 1;
        if (contact && set)
            new_battlestruct->bank_affecting[bank_attacker].spikyshield_damage = 1;
    }
    else if (new_battlestruct->bank_affecting[bank_target].baneful_bunker)
    {
        effect = 1;
        if (contact && set)
            new_battlestruct->bank_affecting[bank_attacker].banefulbunker_damage = 1;
    }
    else if (new_battlestruct->side_affecting[targets_side].crafty_shield && split == 2)
        effect = 1;
    else if (new_battlestruct->side_affecting[targets_side].quick_guard && get_priority(current_move, bank_attacker) > 0)
        effect = 1;
    else if (new_battlestruct->side_affecting[targets_side].mat_block && split != 2)
        effect = 1;
    else if (new_battlestruct->side_affecting[targets_side].wide_guard && (target == move_target_both || target == move_target_foes_and_ally))
        effect = 1;
    return effect;
}

u8 protect_affecting_moves(u16 move)
{
    u8 effect = protect_affects(move, 1);
    if (effect)
    {
        move_outcome.missed = 1;
        jump_if_move_has_no_effect(7, move);
        battle_communication_struct.field6 = 1;
    }
    return effect;
}

u8 accuracy_helper_replacement(u16 move)
{
    u8 done_status = 0;
    if (
        (status3[bank_target].always_hits && disable_structs[bank_target].always_hits_bank == bank_attacker)
        || check_ability(bank_attacker, ABILITY_NO_GUARD)
        || check_ability(bank_target, ABILITY_NO_GUARD)
        || (current_move == MOVE_TOXIC && is_of_type(bank_attacker, TYPE_POISON))
        || (new_battlestruct->bank_affecting[bank_target].telekinesis && move_table[current_move].script_id != 70)
        ) //lock-on/mind reader checked, then no guard, always hiting toxic on poison types, then always hitting telekinesis except OHKO moves
    {
        jump_if_move_has_no_effect(7, move);
        done_status = 1;
    }
    else if (((status3[bank_target].on_air || new_battlestruct->bank_affecting[bank_target].sky_drop_attacker || new_battlestruct->bank_affecting[bank_target].sky_drop_target) && !(hitmarker & HITMARKER_IGNORE_ON_AIR))
             || (status3[bank_target].underground && !(hitmarker & HITMERKER_IGNORE_UNDERGROUND))
             || (status3[bank_target].underwater && !(hitmarker & HITMARKER_IGNORE_UNDERWATER))
             || status3[bank_target].phantomforce)
    {
        move_outcome.missed = 1;
        jump_if_move_has_no_effect(7, move);
        done_status = 1;
    }
    else if (((current_move == MOVE_THUNDER || current_move == MOVE_HURRICANE) && weather_abilities_effect() && RAIN_WEATHER)
             || (current_move == MOVE_BLIZZARD && weather_abilities_effect() && HAIL_WEATHER)
             || (find_move_in_table(current_move, pressing_moves_table) && status3[bank_target].minimized)
             || (move_table[move].accuracy == 0))
    {
        jump_if_move_has_no_effect(7, move);
        done_status = 1;
    }
    hitmarker &= 0xFFF8FFFF; //clearing all above hitmarer flags
    return done_status;
}

u32 accuracy_percent(u16 move, u8 bankatk, u8 bankdef)
{
    u32 accuracy;
	u8 evs_buff = battle_participants[bankdef].evasion_buff;
	if (new_battlestruct->field_affecting.gravity)
		evs_buff -= 2;
	if (find_move_in_table(move, ignore_targetstats_moves) || check_ability(bankatk, ABILITY_UNAWARE))
		evs_buff = 6;
	else if (evs_buff > 6 && (battle_participants[bankdef].status2.foresight || new_battlestruct->bank_affecting[bankdef].miracle_eyed
							  || (battle_participants[bankatk].ability_id == ABILITY_KEEN_EYE && has_ability_effect(bankatk, 0))))
		evs_buff = 6;

	u8 accuracy_buff = battle_participants[bankatk].acc_buff;
	if (battle_participants[bankdef].ability_id == ABILITY_UNAWARE && has_ability_effect(bankdef, 1))
		accuracy_buff = 6;

	u8 move_accuracy = move_table[move].accuracy;
	if (has_ability_effect(bankdef, 1) && battle_participants[bankdef].ability_id == ABILITY_WONDER_SKIN && !DAMAGING_MOVE(move) && move_accuracy > 0)
		move_accuracy = 50;
	else if ((move == MOVE_THUNDER || move == MOVE_HURRICANE) && weather_abilities_effect() && SUN_WEATHER)
		move_accuracy = 50;
	s8 buff = accuracy_buff + 6 - evs_buff;
	if (buff < 0)
		buff = 0;
	else if (buff > 0xC)
		buff = 0xC;

	//accuracy = __udivsi3(move_accuracy * fraction_stat_buffs2[buff].numerator, fraction_stat_buffs2[buff].denumenator);
	accuracy = move_accuracy * fraction_stat_buffs2[buff].numerator / fraction_stat_buffs2[buff].denumenator;
	if (has_ability_effect(bankatk, 0))
	{
		switch (battle_participants[bankatk].ability_id)
		{
		case ABILITY_COMPOUND_EYES:
			accuracy = percent_boost(accuracy, 30);
			break;
		case ABILITY_HUSTLE:
			if (move_table[move].split == MOVE_PHYSICAL)
			{
				accuracy = percent_lose(accuracy, 20);
			}
			break;
		}
	}
	if (ability_battle_effects(13, bankatk, ABILITY_VICTORY_STAR, 0, 0))
	{
		accuracy = percent_boost(accuracy, 10);
	}
	if (has_ability_effect(bankdef, 1))
	{
		switch (battle_participants[bankdef].ability_id)
		{
		case ABILITY_SAND_VEIL:
			if (weather_abilities_effect() && SANDSTORM_WEATHER)
				accuracy = percent_lose(accuracy, 20);
			break;
		case ABILITY_SNOW_CLOAK:
			if (weather_abilities_effect() && HAIL_WEATHER)
				accuracy = percent_lose(accuracy, 20);
			break;
		case ABILITY_TANGLED_FEET:
			if (battle_participants[bankdef].status2.confusion)
				accuracy = percent_lose(accuracy, 50);
			break;
		}
	}
	if (get_item_effect(bankdef, 1) == ITEM_EFFECT_BRIGHTPOWDER)
		accuracy = percent_lose(accuracy, 10);
	switch (get_item_effect(bankatk, 1))
	{
	case ITEM_EFFECT_WIDELENS:
		accuracy = percent_boost(accuracy, 10);
		break;
	case ITEM_EFFECT_ZOOMLENS:
		if (get_bank_turn_order(bankdef) < get_bank_turn_order(bankatk))
			accuracy = percent_boost(accuracy, 20);
		break;
	}
	if (weather_abilities_effect() && (battle_weather.flags.fog || battle_weather.flags.permament_fog))
		accuracy = percent_lose(accuracy, 40);	
    return accuracy;
}

void atk01_accuracy_calc(void)
{
    u32 jump_loc = read_word(battlescripts_curr_instruction + 1);
    u16 arg = read_hword(battlescripts_curr_instruction + 5);
    u16 checked_move=current_move;
    if (arg == 0)
    {
        if(new_battlestruct->various.parental_bond_mode==PBOND_CHILD)
        {
            battlescripts_curr_instruction += 7;
        }
        else
        {
            if(arg!=0)
            {
                checked_move=arg; //Used in doom desire.
            }
            if (!protect_affecting_moves(checked_move) && !accuracy_helper_replacement(checked_move))
            {
                u16 accuracy = accuracy_percent(checked_move, bank_attacker, bank_target);
                //if (__umodsi3(rng(), 100) + 1 > accuracy)
                if(random_value(100) + 1 > accuracy)
                {
                    move_outcome.missed = 1;
                    if (battle_flags.double_battle && (move_table[checked_move].target == 0x8 || move_table[checked_move].target == 0x20))
                    {
                        battle_communication_struct.field6 = 2;
                    }
                    else
                    {
                        battle_communication_struct.field6 = 0;
                    }
                    type_effectiveness_calc(checked_move, get_attacking_move_type(), bank_attacker, bank_target, 1);
                    move_outcome.not_affected = 0;
                }
                jump_if_move_has_no_effect(7, checked_move);
            }
        }
    }
    else //not checking accuracy
    {
        if (status3[bank_target].always_hits && arg == 0xFFFF && disable_structs[bank_target].always_hits_bank == bank_attacker)
        {
            battlescripts_curr_instruction += 7;
        }
        else
        {
            if (status3[bank_target].on_air || status3[bank_target].underground || status3[bank_target].underwater || new_battlestruct->bank_affecting[bank_target].sky_drop_attacker || new_battlestruct->bank_affecting[bank_target].sky_drop_target)
            {
                battlescripts_curr_instruction = (void*)jump_loc;
            }
            else
            {
                if (!protect_affecting_moves(checked_move))
                {
                    battlescripts_curr_instruction += 7;
                }
            }
        }
    }
}
