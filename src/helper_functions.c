#include "defines.h"
#include "static_references.h"

bool check_ability(u8 bank, u8 ability);
void set_attacking_move_type();
u8 get_airborne_state(u8 bank, u8 mode, u8 check_levitate);
u8 item_battle_effects(u8 switchid, u8 bank, u8 moveturn);
u8 affected_by_substitute(u8 substitute_bank);
u8 cant_become_paralyzed(u8 bank, u8 self_inflicted);
u8 cant_poison(u8 atk_bank, u8 def_bank, u8 self_inflicted);
u8 cant_become_burned(u8 bank, u8 self_inflicted);
u8 cant_become_freezed(u8 bank, u8 self_inflicted);
u8 cant_fall_asleep(u8 bank, u8 self_inflicted);
u8 berry_eaten(u8 howcall, u8 bank);
u32 percent_lose(u32 number, u16 percent);
bool find_move_in_table(u16 move, const u16* table_ptr);
u8 is_of_type(u8 bank, u8 type);
u8 set_type(u8 bank, u8 type);
u8 get_first_to_strike(u8 bank1, u8 bank2, u8 ignore_priority);
u16 get_poke_weight(u8 bank);
u8 get_attacking_move_type();
u16 type_effectiveness_calc(u16 move, u8 type, u8 atkbank, u8 defbank, u8 effectshandling);
void* get_move_battlescript_ptr(u32 move);
u8 get_target_of_move(u16 move, u8 target_given, u8 adjust);
void move_to_buff1(u16 move);
u8 check_mega_evo(u8 bank);
bool is_bank_present(u32 bank);
u8 can_lose_item(u8 bank, u8 stickyhold_check, u8 sticky_message);
u8 canlose_megastone(u8 bank, u16 item);
void b_load_sprite_opponent(struct pokemon* poke, u8 bank);
void b_load_sprite_player(struct pokemon* poke, u8 bank);
s8 get_move_position(u8 bank, u16 move);
u8 get_item_effect(u8 bank, u8 check_negating_effects);
u8 weather_abilities_effect();
u8* get_slide_msg(u16 trainerID, u8 caseID);
u8 ability_battle_effects(u8 switch_id, u8 bank, u8 ability_to_check, u8 special_cases_argument, u16 move);
u16 apply_statboost(u16 stat, u8 boost);
u32 percent_boost(u32 number, u16 percent);
bool move_effect_setter(bool primary, bool certain);
u8 cant_become_confused(u8 bank);
void bugbite_get_berry_effect(void);
bool is_in_tag_battle(void);
u8 get_battle_bank(u8 to_get);
void prep_string(u16 strID, u8 bank);
u8 get_bank_side(u8 bank);
void bs_push(void* to_return, void* now);
void bs_push_current(void* now);
//void revert_mega_to_normalform(u8 teamID, u8 opponent_side);
void revert_mega_to_normalform_new(u8 opponent_side);
bool not_impostered(u8 bank);
u32 random_value(u32 limit);
u8 z_protect_affects(u16 move); //JeremyZ
void check_weather_trio(void);

bool no_inline is_poke_valid(struct pokemon* poke)
{
    u16 species = get_attributes(poke, ATTR_SPECIES, 0);
    return (species != 0 && species != 412 && !get_attributes(poke, ATTR_IS_EGG, 0)); //JeremyZ
}

struct pokemon* no_inline get_party_ptr(u8 bank)
{
    if (get_bank_side(bank))
        return &party_opponent[0];
    return &party_player[0];
}

struct pokemon* no_inline get_bank_poke_ptr(u8 bank)
{
    return &get_party_ptr(bank)[battle_team_id_by_side[bank]];
}

u8 no_inline get_poke_ability_active_bank(){
	return get_poke_ability(get_bank_poke_ptr(active_bank));
}

u8 count_party_pokemon(u8 bank)
{
    u8 usable_pokes = 0;
    struct pokemon* poke = get_party_ptr(bank);
    for (u8 i = 0; i < 6; i++)
    {
        if (get_attributes(&poke[i], ATTR_CURRENT_HP, 0) != 0 && is_poke_valid(&poke[i]))
            usable_pokes++;
    }
    return usable_pokes;
}

void no_inline ability_switchin_effect(void)
{
    status3[new_battlestruct->various.active_bank].innerswitchinlock = 1;
    ability_battle_effects(24, new_battlestruct->various.active_bank, 0, 0, 0);
}

void no_inline change_attacker_item(void)
{
    active_bank = bank_attacker;
    bb2_setattributes_in_battle(0, 2, 0, 4, &battle_participants[bank_attacker].held_item);
    mark_buffer_bank_for_execution(bank_attacker);
}

void changestatvar_atk(u8 val)
{
    if (val)
    {
        battle_scripting.stat_changer = val;
        bs_push_current(BS_CHANGE_ATK_STAT);
    }
}

void changestatvar1_atk(void)
{
    changestatvar_atk(new_battlestruct->various.var1);
}

void changestatvar2_atk(void)
{
    changestatvar_atk(new_battlestruct->various.var2);
}

void frisk_target_item(void)
{   u16 curr_item=battle_participants[bank_target].held_item;
    if (curr_item)
    {
        last_used_item=curr_item;
        prep_string(0x19D,battle_scripting.active_bank);
        record_usage_of_item(bank_target, get_item_effect(bank_target, 0));
        battle_communication_struct.is_message_displayed=1;
    }
    else
        battle_communication_struct.is_message_displayed=0;
}

void zygarde_message_based_on_side(void)
{
    if (get_bank_side(battle_scripting.active_bank))
        prep_string(0x249,battle_scripting.active_bank);
    else
        prep_string(0x248,battle_scripting.active_bank);
    battle_communication_struct.is_message_displayed=1;
}

void set_type_msg_buffer(void)
{
    u8 move_type=battle_stuff_ptr->dynamic_move_type&0x3F;
    if (!move_type)
        move_type = move_table[current_move].type;
    battle_text_buff1[0] = 0xFD;
    battle_text_buff1[1] = 3;
    battle_text_buff1[2] = move_type;
    battle_text_buff1[3] = 0xFF;
}

void bad_dreams_damage_calc(void)
{
    damage_loc=get_1_8_of_max_hp(bank_target);
}

void mentalherb(void)
{
    u8 bank = battle_scripting.active_bank;
    void* toPush = NULL;
    if (disable_structs[bank].disable_timer)
    {
        disable_structs[bank].disable_timer = 0;
        disable_structs[bank].disabled_move = 0;
        toPush = BS_DISABLEEND;
    }
    else if (disable_structs[bank].encore_timer)
    {
        disable_structs[bank].encore_timer = 0;
        disable_structs[bank].encored_move = 0;
        toPush = BS_ENCOREEND;
    }
    else if (disable_structs[bank].taunt_timer)
    {
        disable_structs[bank].taunt_timer = 0;
        toPush = BS_TAUNTEND;
    }
    else if (new_battlestruct->bank_affecting[bank].heal_block)
    {
        new_battlestruct->bank_affecting[bank].heal_block = 0;
        toPush = BS_HEALBLOCKEND;
    }
    if (toPush)
        bs_push(battlescripts_curr_instruction -3, toPush);
}

void callasm_nop(void)
{

}

void set_var1_to_0(void)
{
    new_battlestruct->various.var1 = 0;
}

void hazards_bank_switcher(void)
{
    new_battlestruct->various.active_bank = bank_target;
    bank_target = new_battlestruct->various.var1;
}

void hazards_bank_return(void)
{
    bank_target = new_battlestruct->various.active_bank;
}

void leechseed_update(void)
{
    if (new_battlestruct->bank_affecting[bank_target].heal_block)
        damage_loc = 0;
    else if (get_item_effect(bank_target, 1) == ITEM_EFFECT_BIGROOT)
        damage_loc = percent_boost(damage_loc, 30);
}

static u8 check_beastboost(void)
{
    u8 raiser = 0;
    if (check_ability(bank_attacker, ABILITY_BEAST_BOOST))
    {
        u16 highest_stat = 0;
        u8 statID = 0;
        u16* stats = &battle_participants[bank_attacker].atk;
        for (u8 i = 0; i < 5; i++)
        {
            if (stats[i] > highest_stat)
            {
                highest_stat = stats[i];
                statID = i;
            }
        }
        u8* buffs = &battle_participants[bank_attacker].atk_buff;
        if (buffs[statID] != 0xC)
            raiser = 0x11 + statID;
    }
    return raiser;
}

void moxie_stat_raise(void)
{
    if (bank_attacker != bank_target && DAMAGING_MOVE(current_move))
    {
        u8 raiser = 0;
        void* bs = NULL;
        if (current_move == MOVE_FELL_STINGER)
            raiser = move_table[current_move].arg1, bs = BS_CHANGE_ATK_STAT_SELFINFLICTED;
        else if (check_ability(bank_attacker, ABILITY_MOXIE) && battle_participants[bank_attacker].atk_buff != 0xC)
        {
            raiser = 0x11, bs = BS_ATK_ABILITY_CHANGES_ATK_STAT;
            record_usage_of_ability(bank_attacker, ABILITY_MOXIE);
        }
        else if ((raiser = check_beastboost()))
        {
            bs = BS_ATK_ABILITY_CHANGES_ATK_STAT;
            record_usage_of_ability(bank_attacker, ABILITY_BEAST_BOOST);
        }
        if (raiser)
        {
            bs_push_current(bs);
            battle_scripting.stat_changer = raiser;
        }
    }
}

void grassyterrainn_heal(void)
{
    void* BS_instr = (void*)(read_word(battlescripts_curr_instruction));
    for (u8 i = 0; i < no_of_all_banks; i++)
    {
        if (!new_battlestruct->bank_affecting[i].grassyterrain_heal && GROUNDED(i) && !FULL_HP(i) && !SEMI_INVULNERABLE(i) && is_bank_present(i))
        {
            new_battlestruct->bank_affecting[i].grassyterrain_heal = 1;
            bs_push(battlescripts_curr_instruction - 3, BS_instr);
            battle_scripting.active_bank = i;
            damage_loc = get_1_16_of_max_hp(i) * -1;
            return;
        }
    }
    battlescripts_curr_instruction += 4;
}

void callitemeffects(void)
{
    item_battle_effects(1, active_bank, 0);
}

void damagecalc2(void)
{
    s32 damage = 0;
    type_effectiveness_calc(current_move, get_attacking_move_type(), bank_attacker, bank_target, 1);
    move_outcome.super_effective = 0;
    move_outcome.not_very_effective = 0;
    switch (current_move)
    {
    case MOVE_DRAGON_RAGE:
        damage = 40;
        break;
    case MOVE_SONIC_BOOM:
        damage = 20;
        break;
    case MOVE_SEISMIC_TOSS:
    case MOVE_NIGHT_SHADE:
        damage = battle_participants[bank_attacker].level;
        break;
	case MOVE_NATURES_MADNESS:
    case MOVE_SUPER_FANG:
        damage = battle_participants[bank_target].current_hp / 2;
        break;
	case MOVE_Z_TAPU:
		damage = battle_participants[bank_target].current_hp * 3 / 4;
		if (z_protect_affects(current_move))
			damage = battle_participants[bank_target].current_hp * 3 / 16;
		break;
    case MOVE_FINAL_GAMBIT:
        damage = battle_participants[bank_attacker].current_hp;
        break;
    case MOVE_PSYWAVE:
        damage = battle_participants[bank_attacker].level * 10 * (/*(__umodsi3(rng(),11)*/ random_value(11) + 5) / 100;
        break;
    case MOVE_ENDEAVOR:
        {
            damage = battle_participants[bank_target].current_hp - battle_participants[bank_attacker].current_hp;
            if (damage <= 0)
            {
                battlescripts_curr_instruction = (void*) 0x082D9F1A;
            }
        }
        break;
    }
    damage_loc = ATLEAST_ONE(damage);
}

void set_statchanger_to_arg1(void)
{
    battle_scripting.stat_changer = move_table[current_move].arg1;
}

void set_statchanger_to_arg2(void)
{
    battle_scripting.stat_changer = move_table[current_move].arg2;
}

void checksubstitute(void)
{
    if (affected_by_substitute(bank_target))
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
        battlescripts_curr_instruction += 4;
}

static u8 bit_to_stat(u8 value)
{
    if (value & 1)
        return 1;
    if (value & 2)
        return 2;
    if (value & 4)
        return 3;
    if (value & 8)
        return 4;
    if (value & 0x10)
        return 5;
    if (value & 0x20)
        return 6;
    if (value & 0x40)
        return 7;
    return 0;
}

static u8 get_howmany_stats_can_change_custom(u8 bank, bool self_inflicted, u8 stats_to_change, s8 by_how_much)
{
    u8 statsNO = 0;
    for (u8 i = 0; i < 7; i++)
    {
        if (stats_to_change & BIT_GET(i))
        {
            if (can_change_stat(bank, self_inflicted, by_how_much | bit_to_stat(BIT_GET(i))))
                statsNO++;
        }
    }

    return statsNO;
}

u8 get_howmany_stats_can_change(u8 bank, bool self_inflicted, u16 move)
{
    return get_howmany_stats_can_change_custom(bank, self_inflicted, move_table[move].arg1, move_table[move].arg2);
}

void multiplestats_prepare(void) //gets number of stats that get changed, u8 bank ptr location if no stats
{
    new_battlestruct->various.var1 = 0;

    u8 bank = read_byte(battlescripts_curr_instruction);
    bool self_inflicted = bank & 0x40;
    bank = get_battle_bank(BIC(bank, 0x40));

    u8 statsNO = get_howmany_stats_can_change(bank, self_inflicted, current_move);
    new_battlestruct->various.var2 = statsNO;

    if (statsNO)
        battlescripts_curr_instruction += 5;
    else
        battlescripts_curr_instruction = (void*)read_word(battlescripts_curr_instruction + 1);
}

void multiplestats_prepare_custom(void) //u8 bank, u8 stats to change, s8 by how much, ptr when fails
{
    new_battlestruct->various.var1 = 0;

    u8 bank = read_byte(battlescripts_curr_instruction);
    bool self_inflicted = bank & 0x40;
    bank = get_battle_bank(BIC(bank, 0x40));

    u8 statsNO = get_howmany_stats_can_change_custom(bank, self_inflicted, read_byte(battlescripts_curr_instruction + 1), read_word(battlescripts_curr_instruction + 2));
    new_battlestruct->various.var2 = statsNO;

    if (statsNO)
    {
        battlescripts_curr_instruction += 7;
    }
    else
        battlescripts_curr_instruction = (void*)read_word(battlescripts_curr_instruction + 3);
}



bool do_multiple_stats(u8 stats_to_change, s8 by_how_much)
{
    u16* done_stats = &new_battlestruct->various.var1;

    for (u8 i = 0; i < 7; i++)
    {
        if (stats_to_change & BIT_GET(i) && !(*done_stats & BIT_GET(i)))
        {
            *done_stats |= BIT_GET(i);
            battlescripts_curr_instruction -= 3;
            bs_push_current((void*)(read_word(battlescripts_curr_instruction + 3)));
            //battle_scripting.stat_changer = by_how_much | bit_to_stat(BIT_GET(i));
			battle_scripting.stat_changer = by_how_much | (i+1);
            if (new_battlestruct->various.var2 > 1)
            {
                battle_scripting.stat_changer |= STAT_MULTIPLE;
            }
            return 1;
        }
    }
    new_battlestruct->various.dont_play_stat_anim = 0;
    battlescripts_curr_instruction += 4;
    return 0;
}
void shadow_thief()
{
	//new_battlestruct->various.var1 = 0;
	new_battlestruct->various.var2 = 0;
	for (u8 i = 0; i < 7; i++)
	{
		u8 *def_stat = &battle_participants[bank_target].atk_buff + i;
		if(*def_stat > 6)
			new_battlestruct->various.var2+=1;
	}
	for (u8 i = 0; i < 7; i++)
    {
		u8 *def_stat = &battle_participants[bank_target].atk_buff + i;
		u8 *atk_stat = &battle_participants[bank_attacker].atk_buff + i;
		if(*def_stat>6 && *atk_stat<0xC)
		{
			*def_stat=6;
			u8 by_how_much=*def_stat-6;
			*atk_stat+=by_how_much;
			if(*atk_stat>0xC)
				*atk_stat=0xC;
			//妤?娴ｅ秵妲搁崣妯哄閻ㄥ嫭鏆熼崐?閸氼偆顑侀崣?,娴ｅ骸娲撴担宥嗘Ц閸欐ê瀵查惃鍕潣閹?
			if(by_how_much>3)
				by_how_much=3;
			//battle_scripting.stat_changer = (by_how_much<<4) | bit_to_stat(BIT_GET(i));
			battle_scripting.stat_changer = (by_how_much<<4) | (i+1);
			battlescripts_curr_instruction -= 3;
			bs_push_current((void*)(read_word(battlescripts_curr_instruction + 3)));
			if (new_battlestruct->various.var2 > 1)
            {
                battle_scripting.stat_changer |= STAT_MULTIPLE;
            }
			return;
		}
	}

	new_battlestruct->various.dont_play_stat_anim = 0;
    battlescripts_curr_instruction += 4;
}

void do_multiple_stats_from_movetable(void)
{
    s8 multiplier = 0;
    if (current_move == MOVE_GROWTH && weather_abilities_effect() && SUN_WEATHER) {multiplier = 0x10;}
	if(current_move == MOVE_CORE_ENFORCER)
		battlescripts_curr_instruction += 4;
	else if(current_move == MOVE_SPECTRAL_THIEF)
		shadow_thief();
    else
		do_multiple_stats(move_table[current_move].arg1, move_table[current_move].arg2 + multiplier);
}
u8 z_moves_power[800];
struct config z_move_config[20];
void apply_zmove_changes()
{
	u8 config = z_moves_power[current_move];
	if (config <= 13){
		if(config == 13)
			new_battlestruct->various.var2 = 6;
		else
			new_battlestruct->various.var2 = 0;
		if(do_multiple_stats(z_move_config[config].arg1, z_move_config[config].arg2))
			return;
	}
	else
	{
		u32 to_add = 4;
		switch (config - 14){
			case 0:
				battle_participants[bank_attacker].status2.focus_energy = 1;
				break;
			case 1:
				for (u8 i = 0; i < 7; i++)
				{
					u8 *atk_stat = &battle_participants[bank_attacker].atk_buff + i;
					if(*atk_stat < 6)
						*atk_stat = 6;
				}
				break;
			case 2:
				HEAL_USER:
				to_add = 5;
				damage_loc = (battle_participants[bank_attacker].max_hp) * -1;
				break;
			case 3:
				new_battlestruct->side_affecting[get_bank_side(bank_attacker)].lunardance = 1;
				break;
			case 4:
				if (battle_flags.double_battle)
				{
					side_timers[get_bank_side(bank_attacker)].followme_timer = 1;
					side_timers[get_bank_side(bank_attacker)].followme_target = bank_attacker;
				}
				break;
			case 5:
				if (is_of_type(bank_attacker, TYPE_GHOST))
					goto HEAL_USER;
				else
				{
					to_add = 0;
					new_battlestruct->various.var2 = 0;
					if(do_multiple_stats(0x1, 0x10))
						return;
				}
		}
		battlescripts_curr_instruction += to_add;
	}
}

void do_multiple_stats_custom(void) //ptr to do a stat change, u8 stats to change, s8 by how much
{
    u8 to_change = read_byte(battlescripts_curr_instruction + 4);
    s8 howmuch = read_word(battlescripts_curr_instruction + 5);
    if (!do_multiple_stats(to_change, howmuch))
        battlescripts_curr_instruction += 2;
}

void checkifcanconfuse_or_changestats(void)
{
    if (!cant_become_confused(bank_target) || can_change_stat(bank_target, 0, move_table[current_move].arg1))
        battlescripts_curr_instruction += 4;
    else
        battlescripts_curr_instruction = (void*)(read_word(battlescripts_curr_instruction));
}

void jumpifcantpoison(void)
{
    switch (cant_poison(bank_attacker, bank_target, 0))
    {
    case 0: //gets poisoned
        //record corrosion ability if is of steel or poison type
        if (is_of_type(bank_target, TYPE_STEEL) || is_of_type(bank_target, TYPE_POISON))
            record_usage_of_ability(bank_attacker, ABILITY_CORROSION);
        break;
    case 1: //already poisoned
        battlescripts_curr_instruction = (void*) 0x82D8F52;
        break;
    case 2: //other major condition
        battlescripts_curr_instruction = (void*) 0x82D9F1C;
        break;
    case 3: //type protection
        battlescripts_curr_instruction = (void*) 0x82D9F2E;
        break;
    case 4: //ability prevention
        last_used_ability = battle_participants[bank_target].ability_id;
        record_usage_of_ability(bank_target, last_used_ability);
        battlescripts_curr_instruction = (void*) 0x82D8F63;
        break;
    case 5: //safeguard
        battlescripts_curr_instruction = (void*) 0x82DAD01;
        break;
    }
}

void jumpifcantparalyze(void)
{
    switch (cant_become_paralyzed(bank_target, 0))
    {
    case 1: //already paralyzed
        battlescripts_curr_instruction = (void*) 0x82D9351;
        break;
    case 2: //other major condition
        battlescripts_curr_instruction = (void*) 0x82D9F1C;
        break;
    case 3: //type protection
        battlescripts_curr_instruction = (void*) 0x82D9F2E;
        break;
    case 4: //ability prevention
        last_used_ability = battle_participants[bank_target].ability_id;
        record_usage_of_ability(bank_target, last_used_ability);
        battlescripts_curr_instruction = (void*) 0x82D9362;
        break;
    }
}

void jumpifcantburn(void)
{
    switch (cant_become_burned(bank_target, 0))
    {
    case 1: //already burned
        battlescripts_curr_instruction = (void*) 0x82DA0BB;
        break;
    case 2: //other major condition
        battlescripts_curr_instruction = (void*) 0x82D9F1C;
        break;
    case 3: //type protection
        battlescripts_curr_instruction = (void*) 0x82D9F2E;
        break;
    }
}

void statustoeffect(void)
{
    new_battlestruct->move_effect.effect1 = move_table[current_move].arg1;
}

void statustoeffect2(void)
{
    new_battlestruct->move_effect.effect1 = move_table[current_move].arg2;
}

void half_hp_damage(void)
{
    damage_loc = ATLEAST_ONE(battle_participants[get_battle_bank(read_byte(battlescripts_curr_instruction))].max_hp / 2);
    battlescripts_curr_instruction++;
}

void jumpifonlyonepokemon(void)
{
    if (count_party_pokemon(bank_attacker) <= 1 + battle_flags.double_battle) //JeremyZ
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
        battlescripts_curr_instruction += 4;
}

void setlunardanceeffect(void)
{
    new_battlestruct->side_affecting[get_bank_side(bank_attacker)].lunardance = 1;
    damage_loc = battle_participants[bank_attacker].current_hp;
    hitmarker |= HITMARKER_IGNORE_SUBSTITUTE;
}

u8 moveargweather_check(u8 arg)
{
    if (weather_abilities_effect())
    {
        if (arg & 1 && battle_weather.int_bw & (weather_downpour | weather_heavy_rain | weather_permament_rain | weather_rain))
            return 1;
        if (arg & 2 && battle_weather.int_bw & (weather_harsh_sun | weather_permament_sun | weather_sun))
            return 1;
        if (arg & 4 && battle_weather.int_bw & (weather_permament_sandstorm | weather_sandstorm))
            return 1;
        if (arg & 8 && battle_weather.int_bw & (weather_hail | weather_permament_hail))
            return 1;
        if (arg & 0x10 && battle_weather.int_bw & (weather_fog | weather_permament_fog))
            return 1;
        if (arg & 0x20 && battle_weather.int_bw & weather_air_current)
            return 1;
    }
	if (arg & 0x40 && new_battlestruct->field_affecting.grassy_terrain)
        return 1;
    return 0;
}

void weatherhpheal(void)
{
    u8 bank = get_battle_bank(read_byte(battlescripts_curr_instruction));
    battlescripts_curr_instruction++;
	//if(current_move==MOVE_RECOVER)
	if (check_ability(bank_attacker, ABILITY_MEGA_LAUNCHER) && find_move_in_table(current_move, &megalauncher_moves_table[0]))
		damage_loc = (battle_participants[bank].max_hp * 3 / 4) *-1;
    if (moveargweather_check(move_table[current_move].arg1))
        damage_loc = (battle_participants[bank].max_hp * 2 / 3) *-1;
    else if (moveargweather_check(move_table[current_move].arg2))
        damage_loc = percent_lose(battle_participants[bank].max_hp, 75) *-1;
}

void checkifcantransfercondition(void)
{
    struct battle_participant* attacker_struct = &battle_participants[bank_attacker];
    struct battle_participant* target_struct = &battle_participants[bank_target];
    u8 fail = 1;
    if (attacker_struct->status.flags.burn && !cant_become_burned(bank_target, 0))
    {
        target_struct->status.flags.burn = 1;
        fail = 0;
    }
    else if (attacker_struct->status.flags.freeze && !cant_become_freezed(bank_target, 0))
    {
        target_struct->status.flags.freeze = 1;
        fail = 0;
    }
    else if (attacker_struct->status.flags.sleep && !cant_fall_asleep(bank_target, 0))
    {
        target_struct->status.flags.sleep = attacker_struct->status.flags.sleep;
        fail = 0;
    }
    else if (attacker_struct->status.flags.paralysis && !cant_become_paralyzed(bank_target, 0))
    {
        target_struct->status.flags.paralysis = 1;
        fail = 0;
    }
    else if ((attacker_struct->status.flags.poison || attacker_struct->status.flags.toxic_poison) && !cant_become_freezed(bank_target, 0))
    {
        target_struct->status.flags.poison = attacker_struct->status.flags.poison;
        target_struct->status.flags.toxic_poison = attacker_struct->status.flags.toxic_poison;
        fail = 0;
    }
    if (fail)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        battlescripts_curr_instruction += 4;
        active_bank = bank_target;
        bb2_setattributes_in_battle(0, REQUEST_STATUS_BATTLE, 0, 4, &target_struct->status);
        mark_buffer_bank_for_execution(bank_target);
    }
}

void choosestatusinflictiontext(void)
{
    //todo
}

void roostactivation(void)
{
    u16 max_hp = battle_participants[bank_attacker].max_hp;
    if (max_hp == battle_participants[bank_attacker].current_hp)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        u16 half_hp = max_hp / 2;
        if (half_hp * 2 < max_hp)
            half_hp++; //rounding up
        damage_loc = half_hp * (-1);
        battlescripts_curr_instruction += 4;
        if (is_of_type(bank_attacker, TYPE_FLYING))
        {
            u8 *type1 = &battle_participants[bank_attacker].type1;
            u8 *type2 = &battle_participants[bank_attacker].type2;
            u8 type3 = new_battlestruct->bank_affecting[bank_attacker].type3;
            if (*type1 == TYPE_FLYING && *type2 == TYPE_FLYING && (type3 == TYPE_EGG || type3 == TYPE_FLYING))
            {//pure flying type
                set_type(bank_attacker, TYPE_NORMAL);
                new_battlestruct->bank_affecting[bank_attacker].roost = 4; //pure type-flying, becomes normal type
            }
            else
            {
                if (*type1 == TYPE_FLYING)
                {
                    if (*type2 != TYPE_FLYING)
                        *type1 = *type2;
                    else
                        *type1 = type3;
                    new_battlestruct->bank_affecting[bank_attacker].roost = 1;
                }
                else if (*type2 == TYPE_FLYING)
                {
                    if (*type1 != TYPE_FLYING)
                        *type2 = *type1;
                    else
                        *type2 = type3;
                    new_battlestruct->bank_affecting[bank_attacker].roost = 2;
                }
                else
                {
                    if (*type1 != TYPE_FLYING)
                        new_battlestruct->bank_affecting[bank_attacker].type3 = *type1;
                    else
                        new_battlestruct->bank_affecting[bank_attacker].type3 = *type2;
                    new_battlestruct->bank_affecting[bank_attacker].roost = 3;
                }
            }
        }
    }
}

void gravitysetter(void)
{
    if (new_battlestruct->field_affecting.gravity)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        battlescripts_curr_instruction += 4;
        new_battlestruct->field_affecting.gravity = 5;
        new_battlestruct->various.var1 = 0;
    }
}

void gravity_ender(void)
{
    u8 effect = 1;
    void* instruction = NULL;
    if (new_battlestruct->various.var1 == 0)
        new_battlestruct->various.var2 = bank_attacker; //bank attacker conserving
    for (u8 i = 0; i < no_of_all_banks; i++)
    {
        if (new_battlestruct->bank_affecting[i].telekinesis)
        {
            new_battlestruct->bank_affecting[i].telekinesis = 0;
            bank_attacker = i;
            instruction = BS_TELEKINESIS_ENDS_RET;
            effect = 1;
        }
        else if (new_battlestruct->bank_affecting[i].magnet_rise)
        {
            new_battlestruct->bank_affecting[i].magnet_rise = 0;
            bank_attacker = i;
            effect = 1;
            instruction = BS_MAGNETRISEEND;
        }
        else if (status3[i].on_air)
        {
            status3[i].on_air = 0;
            battle_participants[i].status2.multiple_turn_move = 0;
            bank_attacker = i;
            instruction = BS_GRAVITYBRINGSDOWN;
            effect = 1;
        }
        else if (check_ability(i, ABILITY_LEVITATE) && !new_battlestruct->various.gravity_levitate)
        {
            new_battlestruct->various.gravity_levitate = 1;
            bank_attacker = i;
            instruction = BS_GRAVITYBRINGSDOWN;
            effect = 1;
        }
    }
    if (effect && instruction)
    {
        new_battlestruct->various.var1++;
        bs_push(battlescripts_curr_instruction - 3, instruction);
    }
    else if (!effect)
    {
        bank_attacker = new_battlestruct->various.var2;
    }
}

void setidentifierbit(void)
{
    if (new_battlestruct->bank_affecting[bank_target].miracle_eyed || battle_participants[bank_target].status2.foresight)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        battlescripts_curr_instruction += 4;
        if (move_table[current_move].arg1)
            new_battlestruct->bank_affecting[bank_target].miracle_eyed = 1;
        else
            battle_participants[bank_target].status2.foresight = 1;
    }
}

void breakprotection(void)
{
    u8 banks_side = get_bank_side(bank_target);
    u8 effect = 0;
    if (protect_structs[bank_target].flag0_protect)
    {
        protect_structs[bank_target].flag0_protect = 0;
        effect = 1;
    }
    if (new_battlestruct->bank_affecting[bank_target].spiky_shield)
    {
        new_battlestruct->bank_affecting[bank_target].spiky_shield = 0;
        effect = 1;
    }
    if (new_battlestruct->bank_affecting[bank_target].kings_shield)
    {
        new_battlestruct->bank_affecting[bank_target].kings_shield = 0;
        effect = 1;
    }
    if (new_battlestruct->side_affecting[banks_side].quick_guard)
    {
        new_battlestruct->side_affecting[banks_side].quick_guard = 0;
        effect = 1;
    }
    if (new_battlestruct->side_affecting[banks_side].mat_block)
    {
        new_battlestruct->side_affecting[banks_side].mat_block = 0;
        effect = 1;
    }
    if (new_battlestruct->side_affecting[banks_side].wide_guard)
    {
        new_battlestruct->side_affecting[banks_side].wide_guard = 0;
        effect = 1;
    }
    if (new_battlestruct->side_affecting[banks_side].crafty_shield)
    {
        new_battlestruct->side_affecting[banks_side].crafty_shield = 0;
        effect = 1;
    }
    if (effect)
    {
        u8 arg1 = move_table[current_move].arg1;
        battle_communication_struct.multistring_chooser = 0 + (arg1 & 1);
    }
    else
        battle_communication_struct.multistring_chooser = 2;
}

void suckerpunchchecker(void)
{
    if (move_table[battle_participants[bank_target].moves[battle_stuff_ptr->chosen_move_position[bank_target]]].split == 2 ||
        get_bank_turn_order(bank_attacker) > get_bank_turn_order(bank_target))
          battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
        battlescripts_curr_instruction += 4;
}

void oppositegenderscheck(void)
{
    struct battle_participant* target_struct = &battle_participants[bank_target];
    struct battle_participant* attacker_struct = &battle_participants[bank_attacker];
    u8 gender_atk = gender_from_pid(attacker_struct->species, attacker_struct->pid);
    u8 gender_def = gender_from_pid(target_struct->species, target_struct->pid);
    if (gender_atk != 0xFF && gender_def != 0xFF && gender_atk != gender_def)
        battlescripts_curr_instruction += 4;
    else
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
}

void setthirdtype(void)
{
    u8 type = move_table[current_move].arg1;
    if (is_of_type(bank_target, type))
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        battlescripts_curr_instruction += 4;
        new_battlestruct->bank_affecting[bank_target].type3 = type;
        battle_text_buff1[0] = 0xFD;
        battle_text_buff1[1] = 0x3;
        battle_text_buff1[2] = type;
        battle_text_buff1[3] = 0xFF;
    }
}

const u8 forbidenabilitiestable1[] = {ABILITY_WONDER_GUARD, ABILITY_STANCE_CHANGE, ABILITY_ILLUSION, ABILITY_MULTITYPE, ABILITY_SCHOOLING, ABILITY_COMATOSE, ABILITY_SHIELDS_DOWN,ABILITY_DISGUISE, ABILITY_RKS_SYSTEM, ABILITY_BATTLE_BOND, ABILITY_POWER_CONSTRUCT, 0xFF};
const u8 forbidenabilitiestable2[] = {ABILITY_MULTITYPE,  ABILITY_STANCE_CHANGE, ABILITY_DISGUISE, ABILITY_BATTLE_BOND, ABILITY_SHIELDS_DOWN, ABILITY_POWER_CONSTRUCT, ABILITY_SCHOOLING, ABILITY_COMATOSE, ABILITY_RKS_SYSTEM, 0xFF}; //
const u8 forbidenabilitiestable3[] = {ABILITY_WONDER_GUARD, ABILITY_STANCE_CHANGE,  ABILITY_MULTITYPE, ABILITY_ILLUSION, ABILITY_FLOWER_GIFT, ABILITY_FORECAST, ABILITY_IMPOSTER, ABILITY_TRACE, ABILITY_COMATOSE,
                                    ABILITY_ZEN_MODE, ABILITY_POWER_OF_ALCHEMY, ABILITY_RECEIVER, ABILITY_DISGUISE, ABILITY_SCHOOLING, ABILITY_SHIELDS_DOWN, ABILITY_BATTLE_BOND, ABILITY_RKS_SYSTEM, ABILITY_POWER_CONSTRUCT, 0xFF};
const u8 forbidenabilitiestable4[] = {ABILITY_MULTITYPE, ABILITY_TRUANT, ABILITY_STANCE_CHANGE, ABILITY_SCHOOLING, ABILITY_COMATOSE, ABILITY_SHIELDS_DOWN, ABILITY_DISGUISE, ABILITY_BATTLE_BOND, ABILITY_RKS_SYSTEM, ABILITY_POWER_CONSTRUCT, 0xFF};

bool findability_in_table(u8 ability, const u8* table)
{
    for (u32 i = 0; table[i] != 0xFF; i++)
    {
        if (table[i] == ability)
            return 1;
    }
    return 0;
}

void ability_change(void)
{ //table goes Swapping/attackers change/targets change
    u8 fail = 0;
    u8* ability_atk = &battle_participants[bank_attacker].ability_id;
    u8* ability_def = &battle_participants[bank_target].ability_id;
    switch (move_table[current_move].arg1)
    {
        case 0: //swapping abilities
            if (findability_in_table(*ability_atk, forbidenabilitiestable1) || findability_in_table(*ability_def, forbidenabilitiestable1))
                fail = 1;
            else
            {
                u8 placeholder = *ability_atk;
                *ability_atk = *ability_def;
                *ability_def = placeholder;
                battle_communication_struct.multistring_chooser = 0;
                status3[*ability_atk].switchinlock = status3[*ability_def].switchinlock = 1;
            }
            break;
        case 1: //attacker's ability becomes target's
            if (*ability_atk == *ability_def || findability_in_table(*ability_atk, forbidenabilitiestable2) || findability_in_table(*ability_def, forbidenabilitiestable3))
                fail = 1;
            else
            {
                last_used_ability = *ability_atk = *ability_def;
                battle_communication_struct.multistring_chooser = 1;
                status3[*ability_atk].switchinlock = 1;
            }
            break;
        case 2: //target's ability becomes attacker
            if (*ability_atk == *ability_def || findability_in_table(*ability_def, forbidenabilitiestable4) || findability_in_table(*ability_atk, forbidenabilitiestable3))
                fail = 1;
            else
            {
                last_used_ability = *ability_def = *ability_atk;
                battle_communication_struct.multistring_chooser = 2;
                status3[*ability_def].switchinlock = 1;
            }
            break;
        case 3: //target's ability becomes the one in arg2
            {
                u8 newability = move_table[current_move].arg2;
                if (*ability_def == newability || findability_in_table(*ability_def, forbidenabilitiestable4))
                    fail = 1;
                else
                {
                    *ability_def = newability;
                    last_used_ability = newability;
                    battle_communication_struct.multistring_chooser = 2;
                    status3[*ability_def].switchinlock = 1;
                }
            }
            break;
        default:
            fail = 1;
    }
    if (fail)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        battlescripts_curr_instruction += 4;
        abilities_by_banks[bank_attacker] = *ability_atk;
        abilities_by_banks[bank_target] = *ability_def;
		check_weather_trio(); //Weather Trio
    }
}

void roomsetter(void)
{ //order of table trickoff 0, trickon 1, wonderoff 2, wonderon 3, magicoff 4, magicon 5
    switch (current_move)
    {
    case MOVE_TRICK_ROOM:
        if (new_battlestruct->field_affecting.trick_room)
        {
            battle_communication_struct.multistring_chooser = 0;
            new_battlestruct->field_affecting.trick_room = 0;
        }
        else
        {
            battle_communication_struct.multistring_chooser = 1;
            new_battlestruct->field_affecting.trick_room = 5;
        }
        break;
    case MOVE_WONDER_ROOM:
        if (new_battlestruct->field_affecting.wonder_room)
        {
            battle_communication_struct.multistring_chooser = 2;
            new_battlestruct->field_affecting.wonder_room = 0;
        }
        else
        {
            battle_communication_struct.multistring_chooser = 3;
            new_battlestruct->field_affecting.wonder_room = 5;
        }
        break;
    case MOVE_MAGIC_ROOM:
        if (new_battlestruct->field_affecting.magic_room)
        {
            battle_communication_struct.multistring_chooser = 4;
            new_battlestruct->field_affecting.magic_room = 0;
        }
        else
        {
            battle_communication_struct.multistring_chooser = 5;
            new_battlestruct->field_affecting.magic_room = 5;
        }
        break;
    }
}

bool is_immune_to_powder(u8 bank); //JeremyZ

void countercalc(void)
{
    u32 physical_damage = protect_structs[bank_attacker].physical_damage;
    u32 special_damage = protect_structs[bank_attacker].special_damage;
    u8 physical_bank = protect_structs[bank_attacker].counter_target;
    u8 special_target = protect_structs[bank_attacker].mirrorcoat_target;
    u8 attackers_side = get_bank_side(bank_attacker);
    u8 followme = 0;
    if (side_timers[attackers_side ^ 1].followme_timer && battle_participants[side_timers[attackers_side ^ 1].followme_target].current_hp
		&& !(is_immune_to_powder(bank_attacker) && new_battlestruct->bank_affecting[side_timers[attackers_side ^ 1].followme_target].rage_powder)) //Rage Powder, JeremyZ
        followme = 1;
    u32 damage = 0;
    u8 fail = 0;
    u8 damage_boots = 100;

    switch (current_move)
    {
    case MOVE_METAL_BURST:
        damage_boots = 50;
        if (special_damage)
            goto MIRRORCOAT;
        else if (physical_damage)
            goto COUNTER;
        else
            fail = 1;
        break;
    COUNTER:
    case MOVE_COUNTER:
        if (physical_damage)
        {
            if (followme)
                bank_target = side_timers[attackers_side ^ 1].followme_target;
            else if (battle_participants[physical_bank].current_hp && get_bank_side(physical_bank) != attackers_side)
                bank_target = physical_bank;
            else
            {
                for (u8 i = 0; i < no_of_all_banks; i++)
                {
                    if (attackers_side != get_bank_side(i) && battle_participants[i].current_hp)
                        bank_target = i;
                    else if (i == no_of_all_banks)
                        fail = 1;
                }
            }
            damage = percent_boost(physical_damage, damage_boots);
        }
        else
            fail = 1;
        break;
    MIRRORCOAT:
    case MOVE_MIRROR_COAT:
        if (special_damage)
        {
            if (followme)
                bank_target = side_timers[attackers_side ^ 1].followme_target;
            else if (battle_participants[special_target].current_hp && get_bank_side(special_target) != attackers_side)
                bank_target = special_target;
            else
            {
                for (u8 i = 0; i < no_of_all_banks; i++)
                {
                    if (attackers_side != get_bank_side(i) && battle_participants[i].current_hp)
                        bank_target = i;
                    else if (i == no_of_all_banks)
                        fail = 1;
                }
            }
            damage = percent_boost(special_damage, damage_boots);
        }
        else
            fail = 1;
        break;
    }
    if (fail)
    {
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
        special_statuses[bank_attacker].flag20 = 1;
    }
    else
    {
        battlescripts_curr_instruction += 4;
        damage_loc = damage;
    }
}

void gastroacid(void)
{
    u16 targets_ability = battle_participants[bank_target].ability_id;
    if (findability_in_table(targets_ability, forbidenabilitiestable2))
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        battlescripts_curr_instruction += 4;
        new_battlestruct->bank_affecting[bank_target].gastro_acided = 1;
		check_weather_trio(); //Weather Trio
    }
}

bool is_embargo_on(u8 bank)
{
    if (is_bank_present(bank))
        return new_battlestruct->bank_affecting[bank].embargo;
    return 0;
}

void setembargo(void)
{
    if (is_embargo_on(bank_target))
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        new_battlestruct->bank_affecting[bank_target].embargo = 5;
        battlescripts_curr_instruction += 4;
    }
}

void naturalgift(void)
{
    u16 item = battle_participants[bank_attacker].held_item;
    u8 effect = 1;
    if (battle_participants[bank_attacker].ability_id == ABILITY_KLUTZ || new_battlestruct->bank_affecting[bank_attacker].embargo || new_battlestruct->field_affecting.magic_room)
        effect = 0;
    if (!effect || !item || get_item_pocket_id(item) != 4)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
        battlescripts_curr_instruction += 4;
}

void slot_bank2_turn_after_bank1(u8 bank1_turn, u8 bank2_turn, u8 bank2)
{
    if (bank1_turn == 0 && bank2_turn == 2)
    {
        turn_order[2] = turn_order[1];
        turn_order[1] = bank2;
    }
    else if (bank1_turn == 0 && bank2_turn == 3)
    {
        turn_order[3] = turn_order[2];
        turn_order[2] = turn_order[1];
        turn_order[1] = bank2;
    }
    else if (bank1_turn == 1 && bank2_turn ==3)//attacker == 1 target == 3
    {
        turn_order[3] = turn_order[2];
        turn_order[2] = bank2;
    }
}

void afteryou_check(void) //0 - first, 1 - second, 2 - third, 3 - fourth
{
    u8 target_turn = get_bank_turn_order(bank_target);
    u8 attacker_turn = get_bank_turn_order(bank_attacker);
    if (target_turn < attacker_turn || target_turn - 1 == attacker_turn)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        battlescripts_curr_instruction += 4;
        slot_bank2_turn_after_bank1(attacker_turn,target_turn,bank_target);
    }
}

void powder_setter(void)
{
    new_battlestruct->bank_affecting[bank_target].powder = 1;
}
void jumpifnoally(void)
{
    u8 ally_bank = bank_attacker ^ 2;
    if (is_bank_present(ally_bank))
    {
        battlescripts_curr_instruction += 4;
        bank_target = ally_bank;
    }
    else
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
}

void electrify(void)
{
    if (get_bank_turn_order(bank_attacker) > get_bank_turn_order(bank_target) || new_battlestruct->bank_affecting[bank_target].electrify)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        new_battlestruct->bank_affecting[bank_target].electrify = 1;
        battlescripts_curr_instruction += 4;
    }
}

void set_entry_hazards(void)
{
    u8 fail = 0;
    u8 targets_side = get_bank_side(bank_target);
    struct side_affecting* target_struct = &new_battlestruct->side_affecting[targets_side];
    u8* string_chooser = &battle_communication_struct.multistring_chooser;
    switch (current_move)
    {
    case MOVE_SPIKES:
        if (side_timers[targets_side].spikes_amount >= 3)
            fail = 1;
        else
        {
            side_timers[targets_side].spikes_amount++;
            side_affecting_halfword[targets_side].spikes_on = 1;
            *string_chooser = 0;
        }
        break;
    case MOVE_STEALTH_ROCK:
        if (target_struct->stealthrock)
            fail = 1;
        else
        {
            target_struct->stealthrock = 1;
            *string_chooser = 1;
        }
        break;
    case MOVE_TOXIC_SPIKES:
        *string_chooser = 2;
        if (target_struct->toxic_spikes_psn && target_struct->toxic_spikes_badpsn)
            fail = 1;
        else if(target_struct->toxic_spikes_psn)
            target_struct->toxic_spikes_badpsn = 1;
        else
            target_struct->toxic_spikes_psn = 1;
        break;
    case MOVE_STICKY_WEB:
        if (target_struct->sticky_web)
            fail = 1;
        else
        {
            *string_chooser = 3;
            target_struct->sticky_web = 1;
        }
        break;
    }
    if (fail)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
        battlescripts_curr_instruction += 4;
}

void jumpifnotdoublebattle(void)
{
    if (battle_flags.double_battle)
        battlescripts_curr_instruction += 4;
    else
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
}

void jumpifattackerandtargetdontsharetypes(void)
{
    u8 type1 = battle_participants[bank_attacker].type1;
    u8 type2 = battle_participants[bank_attacker].type2;
    u8 type3 = new_battlestruct->bank_affecting[bank_attacker].type3;
    if ((is_of_type(bank_target, type1) && type1 != TYPE_EGG) || (is_of_type(bank_target, type2) && type2 != TYPE_EGG) || (is_of_type(bank_target, type3) && type3 != TYPE_EGG))
        battlescripts_curr_instruction += 4;
    else
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
}

void try_autotonomize(void)
{
    u8* auto_uses = &new_battlestruct->bank_affecting[bank_attacker].autonomize_uses;
    if (get_poke_weight(bank_attacker) == 1)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        *auto_uses += 1;
        battlescripts_curr_instruction += 4;
    }
}

void set_iondeluge(void)
{
    if (new_battlestruct->field_affecting.ion_deluge)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        battlescripts_curr_instruction += 4;
        new_battlestruct->field_affecting.ion_deluge = 1;
    }
}

void reflecttypes(void)
{
    new_battlestruct->bank_affecting[bank_attacker].type3 = new_battlestruct->bank_affecting[bank_target].type3;
    battle_participants[bank_attacker].type1 = battle_participants[bank_target].type1;
    battle_participants[bank_attacker].type2 = battle_participants[bank_target].type2;
}

void sethealblock(void)
{
    if (new_battlestruct->bank_affecting[bank_target].heal_block)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        new_battlestruct->bank_affecting[bank_target].heal_block = 5;
        battlescripts_curr_instruction += 4;
    }
}

void traptarget(void)
{
    battle_participants[bank_target].status2.cant_escape = 1;
    disable_structs[bank_target].bank_preventing_escape = bank_attacker;
}

void mefirst_check(void)
{
    u16 chosen_move = chosen_move_by_banks[bank_target];
    static const u16 mefirstforbiddenmoves[] = {MOVE_COVET, MOVE_THIEF, MOVE_STRUGGLE, MOVE_CHATTER, MOVE_COUNTER, MOVE_METAL_BURST, MOVE_LIGHT_SCREEN, MOVE_ME_FIRST, MOVE_FOCUS_PUNCH, 0xFFFF};
    if (get_bank_turn_order(bank_target) > current_move_turn && move_table[chosen_move].base_power && !find_move_in_table(chosen_move, &mefirstforbiddenmoves[0]))
     {
         battlescripts_curr_instruction += 4;
         new_battlestruct->bank_affecting[bank_attacker].me_first = 1;
         new_battlestruct->various.var1 = chosen_move;
     }
    else
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
}

void jump_to_move_bs(void)
{
    battle_scripting.field18 = 0;
    battle_scripting.field19 = 0;
    hitmarker &= 0xFFFFFBFF;
    hitmarker |= HITMARKER_NO_PPDEDUCT;
    u16 move = new_battlestruct->various.var1;
    battlescripts_curr_instruction = get_move_battlescript_ptr(move);
    current_move = move;
    bank_target = get_target_of_move(move, 0, 1);
}

void setluckychant(void)
{
    u8 side = get_bank_side(bank_attacker);
    if (new_battlestruct->side_affecting[side].lucky_chant)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        new_battlestruct->side_affecting[side].lucky_chant = 5;
        new_battlestruct->side_affecting[side].lucky_chant_bank = bank_attacker;
        battlescripts_curr_instruction += 4;
    }
}

void settailwind(void)
{
    u8 side = get_bank_side(bank_attacker);
    if (new_battlestruct->side_affecting[side].tailwind)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        new_battlestruct->side_affecting[side].tailwind = 5;
        new_battlestruct->side_affecting[side].tailwind_bank = bank_attacker;
        battlescripts_curr_instruction += 4;
    }
}

void cansetnightmare(void)
{
    if (battle_participants[bank_target].status.flags.sleep && battle_participants[bank_target].status2.nightmare == 0)
    {
        battle_participants[bank_target].status2.nightmare = 1;
        battlescripts_curr_instruction += 4;
    }
    else
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
}

void bellydrum(void)
{
    u16 halvedmaxhp = battle_participants[bank_attacker].max_hp / 2;
    u8* buff = &battle_participants[bank_attacker].hp_buff + move_table[current_move].arg1;
    if (battle_participants[bank_attacker].current_hp > halvedmaxhp && *buff != 0xC)
    {
        *buff = 0xC;
        damage_loc = halvedmaxhp;
        battlescripts_curr_instruction += 4;
    }
    else
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
}

void setmagnetrise(void)
{
    struct bank_affecting* magnetrise = &new_battlestruct->bank_affecting[bank_attacker];
    if (magnetrise->magnet_rise || magnetrise->smacked_down || status3[bank_attacker].rooted)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        battlescripts_curr_instruction += 4;
        magnetrise->magnet_rise = 5;
    }
}

void settelekinesis(void)
{
    struct bank_affecting* telekinesis = &new_battlestruct->bank_affecting[bank_target];
    if (telekinesis->telekinesis || telekinesis->smacked_down || status3[bank_target].rooted)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        battlescripts_curr_instruction += 4;
        telekinesis->telekinesis = 5;
    }
}

void setpowertrick(void)
{
    u16* atk = &battle_participants[bank_attacker].atk;
    u16* def = &battle_participants[bank_attacker].def;
    u16 placeholder = *atk;
    *atk = *def;
    *def = placeholder;
    new_battlestruct->bank_affecting[bank_attacker].powertrick ^= 1;
}

void make_pokemon_one_type(void)
{
    u8 type = move_table[current_move].arg1 & 0x1F;
    if (battle_participants[bank_target].type1 == type && (battle_participants[bank_target].type2 == type || battle_participants[bank_target].type2 == TYPE_EGG) && (new_battlestruct->bank_affecting[bank_target].type3 == type || new_battlestruct->bank_affecting[bank_target].type3 == TYPE_EGG))
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        battlescripts_curr_instruction += 4;
        set_type(bank_target, type);
        battle_text_buff1[0] = 0xFD;
        battle_text_buff1[1] = 3;
        battle_text_buff1[2] = type;
        battle_text_buff1[3] = 0xFF;
    }
    return;
}

void defog_effect(void)
{
    bank_attacker = turn_order[current_move_turn];
    u8 attackers_side = get_bank_side(bank_attacker);
    u8 effect = 0;
    u8 targets_side = get_bank_side(bank_target);
    struct side_affecting_hword* target_side = &side_affecting_halfword[targets_side];
    struct side_timer* target_timer = &side_timers[targets_side];
    void* ptr_to_script = 0;
    if (target_side->reflect_on)
    {
        effect = 1;
        target_side->reflect_on = 0;
        target_timer->reflect_timer = 0;
        bank_attacker = target_timer->reflect_bank;
        ptr_to_script = &defogblows_bs;
        move_to_buff1(MOVE_REFLECT);
    }
    else if (target_side->light_screen_on)
    {
        effect = 1;
        target_side->light_screen_on = 0;
        target_timer->lightscreen_timer = 0;
        bank_attacker = target_timer->lightscreen_bank;
        ptr_to_script = &defogblows_bs;
        move_to_buff1(MOVE_LIGHT_SCREEN);
    }
    else if (target_side->mist_on)
    {
        effect = 1;
        target_side->mist_on = 0;
        target_timer->mist_timer = 0;
        bank_attacker = target_timer->mist_bank;
        ptr_to_script = &defogblows_bs;
        move_to_buff1(MOVE_MIST);
    }
    else if (target_side->safeguard_on)
    {
        effect = 1;
        target_side->safeguard_on = 0;
        target_timer->safeguard_timer = 0;
        bank_attacker = target_timer->safeguard_bank;
        ptr_to_script = &defogblows_bs;
        move_to_buff1(MOVE_SAFEGUARD);
    }
    else if (target_side->spikes_on)
    {
        effect = 1;
        target_side->spikes_on = 0;
        target_timer->spikes_amount = 0;
        bank_attacker = bank_target;
        ptr_to_script = (void*) 0x082DAFDD;
    }
    else if (new_battlestruct->side_affecting[targets_side].stealthrock)
    {
        effect = 1;
        new_battlestruct->side_affecting[targets_side].stealthrock = 0;
        battle_communication_struct.multistring_chooser = 0;
        bank_attacker = bank_target;
        ptr_to_script = BS_RAPIDSPIN_SPINS;
    }
    else if (new_battlestruct->side_affecting[targets_side].toxic_spikes_psn)
    {
        effect = 1;
        new_battlestruct->side_affecting[targets_side].toxic_spikes_psn = 0;
        new_battlestruct->side_affecting[targets_side].toxic_spikes_badpsn = 0;
        battle_communication_struct.multistring_chooser = 2;
        bank_attacker = bank_target;
        ptr_to_script = BS_RAPIDSPIN_SPINS;
    }
    else if (new_battlestruct->side_affecting[targets_side].sticky_web)
    {
        effect = 1;
        new_battlestruct->side_affecting[targets_side].sticky_web = 0;
        battle_communication_struct.multistring_chooser = 1;
        bank_attacker = bank_target;
        ptr_to_script = BS_RAPIDSPIN_SPINS;
    }
    else if (side_affecting_halfword[attackers_side].spikes_on)
    {
        effect = 1;
        side_affecting_halfword[attackers_side].spikes_on = 0;
        side_timers[attackers_side].spikes_amount = 0;
        ptr_to_script = (void*) 0x082DAFDD;
    }
    else if (new_battlestruct->side_affecting[attackers_side].stealthrock)
    {
        effect = 1;
        new_battlestruct->side_affecting[attackers_side].stealthrock = 0;
        ptr_to_script = BS_RAPIDSPIN_SPINS;
    }
    else if (new_battlestruct->side_affecting[attackers_side].toxic_spikes_psn)
    {
        effect = 1;
        new_battlestruct->side_affecting[attackers_side].toxic_spikes_psn = 0;
        new_battlestruct->side_affecting[attackers_side].toxic_spikes_badpsn = 0;
        ptr_to_script = BS_RAPIDSPIN_SPINS;
    }
    else if (new_battlestruct->side_affecting[attackers_side].sticky_web)
    {
        effect = 1;
        new_battlestruct->side_affecting[attackers_side].sticky_web = 0;
        ptr_to_script = BS_RAPIDSPIN_SPINS;
    }
    if (effect)
    {
        if (battle_communication_struct.multistring_chooser == 0)
                battle_communication_struct.multistring_chooser = 2;
        bs_push(battlescripts_curr_instruction - 3, ptr_to_script);
    }
    else if (effect == 0 && battle_communication_struct.multistring_chooser == 0)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        bank_attacker = turn_order[current_move_turn];
        battlescripts_curr_instruction += 4;
    }
}

const u16 copycat_forbidden_moves[] = {MOVE_ASSIST, MOVE_BELCH, MOVE_BESTOW, MOVE_CHATTER, MOVE_CIRCLE_THROW, MOVE_COPYCAT, MOVE_COUNTER, MOVE_COVET, MOVE_DESTINY_BOND, MOVE_DETECT, MOVE_DRAGON_TAIL, MOVE_ENDURE, MOVE_FEINT, MOVE_FOCUS_PUNCH, MOVE_FOLLOW_ME, MOVE_HELPING_HAND, MOVE_HOLD_HANDS, MOVE_KINGS_SHIELD, MOVE_MAT_BLOCK, MOVE_ME_FIRST, MOVE_METRONOME, MOVE_MIMIC, MOVE_MIRROR_COAT, MOVE_MIRROR_MOVE, MOVE_NATURE_POWER, MOVE_PROTECT, MOVE_RAGE_POWDER, MOVE_ROAR, MOVE_SKETCH, MOVE_SLEEP_TALK, MOVE_SNATCH, MOVE_SPIKY_SHIELD, MOVE_STRUGGLE, MOVE_SWITCHEROO, MOVE_THIEF, MOVE_TRANSFORM, MOVE_TRICK, MOVE_WHIRLWIND, 0x0, 0xFFFF};

void copycat_move(void)
{
    if (find_move_in_table(new_battlestruct->various.previous_move, copycat_forbidden_moves))
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        new_battlestruct->various.var1 = new_battlestruct->various.previous_move;
        battlescripts_curr_instruction += 4;
    }
}



void psycho_swaps(void)
{
    u8 stat1 = move_table[current_move].arg1;
    if (stat1)
        battle_communication_struct.multistring_chooser = 0;
    else
        battle_communication_struct.multistring_chooser = 1;
    u8 stat2 = move_table[current_move].arg2;
    for (u8 i = 0; i < 8; i++)
    {
        u8 *atk_stat = &battle_participants[bank_attacker].hp_buff + i;
        u8 *def_stat = &battle_participants[bank_target].hp_buff + i;
        u8 placeholder = *atk_stat;
        if (stat1 == 0)
        {
            *atk_stat = *def_stat;
            *def_stat = placeholder;
        }
        else if (i == stat1)
        {
            *atk_stat = *def_stat;
            *def_stat = placeholder;
            battle_text_buff1[0] = 0xFD;
            battle_text_buff1[1] = 5;
            battle_text_buff1[2] = i;
            battle_text_buff1[3] = 0xFF;
        }
        else if (i == stat2)
        {
            *atk_stat = *def_stat;
            *def_stat = placeholder;
            battle_text_buff2[0] = 0xFD;
            battle_text_buff2[1] = 5;
            battle_text_buff2[2] = i;
            battle_text_buff2[3] = 0xFF;
        }
    }
}

void psychosplits()
{
    switch (current_move)
    {
    case MOVE_POWER_SPLIT:
        {
            u16 *atk_atk = &battle_participants[bank_attacker].atk;
            u16 *atk_trg = &battle_participants[bank_target].atk;
            u16 average = (*atk_atk + *atk_trg) / 2;
            *atk_atk = average;
            *atk_trg = average;

            atk_atk = &battle_participants[bank_attacker].sp_atk;
            atk_trg = &battle_participants[bank_target].sp_atk;
            average = (*atk_atk + *atk_trg) / 2;
            *atk_atk = average;
            *atk_trg = average;

            battle_text_buff1[0] = 0xFD;
            battle_text_buff1[1] = 0;
            battle_text_buff1[2] = 0xF2;
            battle_text_buff1[3] = 1;
            battle_text_buff1[4] = 0xFF;
        }
        break;
    case MOVE_GUARD_SPLIT:
        {
            u16 *def_def = &battle_participants[bank_attacker].def;
            u16 *def_trg = &battle_participants[bank_target].def;
            u16 average = (*def_def + *def_trg) / 2;
            *def_def = average;
            *def_trg = average;

            def_def = &battle_participants[bank_attacker].sp_def;
            def_trg = &battle_participants[bank_target].sp_def;
            average = (*def_def + *def_trg) / 2;
            *def_def = average;
            *def_trg = average;

            battle_text_buff1[0] = 0xFD;
            battle_text_buff1[1] = 0;
            battle_text_buff1[2] = 0xF3;
            battle_text_buff1[3] = 1;
            battle_text_buff1[4] = 0xFF;
        }
        break;
    }
}

void stockpile_record(void)
{
    struct battle_participant* attacker_stats = &battle_participants[bank_attacker];
    u8* stockpile_def = &bank_partner_atk;
    u8* stockpile_spdef = &bank_partner_def;
    struct bank_affecting* attacker_stockpile = &new_battlestruct->bank_affecting[bank_attacker];
    switch (read_byte(battlescripts_curr_instruction))
    {
    case 0:
        *stockpile_def = attacker_stats->def_buff;
        *stockpile_spdef = attacker_stats->sp_def_buff;
		attacker_stockpile->stockpile_counter++;
        break;
    case 1:
        attacker_stockpile->stockpile_def_changes += (attacker_stats->def_buff - *stockpile_def);
        attacker_stockpile->stockpile_sp_def_changes += (attacker_stats->sp_def_buff - *stockpile_spdef);
        break;
    case 2: //reset stat buffs
        {
            attacker_stats->def_buff -= attacker_stockpile->stockpile_def_changes;
            attacker_stats->sp_def_buff -= attacker_stockpile->stockpile_sp_def_changes;
            new_battlestruct->various.var2 = 0;
            attacker_stockpile->stockpile_def_changes = 0;
            attacker_stockpile->stockpile_sp_def_changes = 0;
			attacker_stockpile->stockpile_counter = 0;
        }
        break;
    }
    battlescripts_curr_instruction++;
}

void twoturn_moves(void)
{
    u8 adder;
    u8* stringchooser = &battle_communication_struct.multistring_chooser;
    if (move_table[current_move].split == 2)
        adder = 0;
    else
        adder = move_table[current_move].arg2;
    switch (current_move)
    {
    case MOVE_GEOMANCY:
        *stringchooser = 0;
        break;
    case MOVE_SKY_ATTACK:
        *stringchooser = 1;
        break;
    case MOVE_SKULL_BASH:
        *stringchooser = 2;
        break;
    case MOVE_SOLAR_BEAM:
        *stringchooser = 3;
        break;
    case MOVE_BOUNCE:
        *stringchooser = 4;
        break;
    case MOVE_ICE_BURN:
        *stringchooser = 5;
        break;
    case MOVE_FREEZE_SHOCK:
        *stringchooser = 6;
        break;
    case MOVE_RAZOR_WIND:
        *stringchooser = 7;
        break;
    case MOVE_PHANTOM_FORCE:
    case MOVE_SHADOW_FORCE:
        *stringchooser = 8;
        break;
    case MOVE_FLY:
        *stringchooser = 9;
        break;
    case MOVE_DIG:
        *stringchooser = 10;
        break;
    case MOVE_DIVE:
        *stringchooser = 11;
        break;
    }
    battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction + 4 * adder);
}

void powerherb_check(void)
{
    if (get_item_effect(bank_attacker, 1) == ITEM_EFFECT_POWERHERB)
    {
        last_used_item = battle_participants[bank_attacker].held_item;
        bs_push((void*) read_word(battlescripts_curr_instruction), BS_POWERHERB);
    }
    else
        battlescripts_curr_instruction += 4;
}

void reset_terrains(struct field_affecting* field)
{
    field->misty_terrain = 0;
    field->psychic_terrain = 0;
    field->grassy_terrain = 0;
    field->electic_terrain = 0;
}

u8 terrains_get_turns(u8 bank)
{
    if (get_item_effect(bank, 1) == ITEM_EFFECT_TERRAINEXPANDER)
        return 8;
    return 5;
}

void call_bc_move_exec(void* bs_ptr);
void set_terrain(void)
{
    u8 fail = 0;
    struct field_affecting* field = &new_battlestruct->field_affecting;
    u8 turns = terrains_get_turns(bank_attacker);
    switch (current_move)
    {
    case MOVE_MISTY_TERRAIN:
        if (field->misty_terrain)
            fail = 1;
        else
        {
            reset_terrains(field);
            field->misty_terrain = turns;
            battle_communication_struct.multistring_chooser = 0;
        }
        break;
    case MOVE_GRASSY_TERRAIN:
        if (field->grassy_terrain)
            fail = 1;
        else
        {
            reset_terrains(field);
            field->grassy_terrain = turns;
            battle_communication_struct.multistring_chooser = 1;
        }
        break;
    case MOVE_ELECTRIC_TERRAIN:
        if (field->electic_terrain)
            fail = 1;
        else
        {
            reset_terrains(field);
            field->electic_terrain = turns;
            battle_communication_struct.multistring_chooser = 2;
        }
        break;
    case MOVE_PSYCHIC_TERRAIN:
	case MOVE_Z_MEW:
        if (field->psychic_terrain)
            fail = 1;
        else
        {
            reset_terrains(field);
            field->psychic_terrain = turns;
            battle_communication_struct.multistring_chooser = 3;
        }
        break;
	case MOVE_Z_LYCANROC:
		reset_terrains(field);
		battle_communication_struct.multistring_chooser = 4;
		break;
    }
    if (fail)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
        battlescripts_curr_instruction += 4;
}

void setaquaring(void)
{
    if (new_battlestruct->bank_affecting[bank_attacker].aqua_ring)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        battlescripts_curr_instruction += 4;
        new_battlestruct->bank_affecting[bank_attacker].aqua_ring = 1;
    }
    return;
}
const u8* get_trainer_opponent_A_name(u8* text);
void get_trainer_name_for_mega(void)
{
    const u8* trainer_name;
    //to do multi battle checks
    if (get_bank_side(bank_attacker))
    {
        trainer_name = get_trainer_opponent_A_name(battle_text_buff3);
    }
    else
    {
        trainer_name = sav2->name;
    }
    strcpy_xFF_terminated_0(battle_text_buff3, trainer_name);
}

void update_hpbar(u8 bank)
{
    struct pokemon* poke_address;
    if (get_bank_side(bank))
        poke_address = &party_opponent[battle_team_id_by_side[bank]];
    else
        poke_address = &party_player[battle_team_id_by_side[bank]];
    u8 obj_ID = graphical_elements_pbs[bank];
    update_bank_graphical_elements(obj_ID, poke_address, 0); //0 updates all things; gender, exp, hp, etc.
}

void mega_evo_updatehpbar(void)
{
    update_hpbar(bank_attacker);
}

void mega_evo_pursuit_check(void)
{
    battlescripts_curr_instruction -= 3;
    if (!check_mega_evo(bank_attacker))
        battlescripts_curr_instruction += 3;
}

void jumpifuserhasnoHP(void)
{
    if (battle_participants[bank_attacker].current_hp)
        battlescripts_curr_instruction += 4;
    else
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
}

void quash_setter(void) //0 - first, 1 - second, 2 - third, 3 - fourth
{
    u8 target_turn = get_bank_turn_order(bank_target);
    u8 attacker_turn = get_bank_turn_order(bank_attacker);
    if (target_turn < attacker_turn)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        new_battlestruct->bank_affecting[bank_attacker].quashed = 1;
        battlescripts_curr_instruction += 4;
        if (battle_flags.double_battle)
        {
            switch (target_turn)
            {
            case 1:
                turn_order[1] = turn_order[2];
            case 2:
                turn_order[2] = turn_order[3];
            case 3:
                turn_order[3] = bank_target;
            }
        }
    }
}

void beatup_getloopcounter(void)
{
    struct pokemon* poke;
    if (get_bank_side(bank_attacker))
        poke = &party_opponent[0];
    else
        poke = &party_player[0];
    u8 counter = 0;
    for (u8 i = 0; i < 6; i++)
    {
        u16 species = get_attributes(&poke[i], ATTR_SPECIES, 0);
        if (species != 0 && species != 412 && get_attributes(&poke[i], ATTR_CURRENT_HP, 0))
            counter++;
    }
    multihit_counter = counter;
}

void canuse_allyswitch(void)
{
    u8 ally_bank = bank_attacker ^ 2;
    if (is_bank_present(ally_bank) && battle_flags.double_battle)
    {
        battlescripts_curr_instruction += 4;
    }
    else
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
}

void allyswitch_dataswitch(void)
{
    u8 ally_bank = bank_attacker ^ 2;
    // paritcipant struct
    struct battle_participant attacker1 = battle_participants[bank_attacker];
    battle_participants[bank_attacker] = battle_participants[ally_bank];
    battle_participants[ally_bank] = attacker1;

    //disable struct
    struct disable_struct attacker2 = disable_structs[bank_attacker];
    disable_structs[bank_attacker] = disable_structs[ally_bank];
    disable_structs[ally_bank] = attacker2;

    //protect struct
    struct protect_struct attacker3 = protect_structs[bank_attacker];
    protect_structs[bank_attacker] = protect_structs[ally_bank];
    protect_structs[ally_bank] = attacker3;

    //status3
    struct status_3 attacker4 = status3[bank_attacker];
    status3[bank_attacker] = status3[ally_bank];
    status3[ally_bank] = attacker4;

    //special status
    struct special_status attacker5 = special_statuses[bank_attacker];
    special_statuses[bank_attacker] = special_statuses[ally_bank];
    special_statuses[ally_bank] = attacker5;

    //new battle struct
    struct bank_affecting attacker6 = new_battlestruct->bank_affecting[bank_attacker];
    new_battlestruct->bank_affecting[bank_attacker] = new_battlestruct->bank_affecting[ally_bank];
    new_battlestruct->bank_affecting[ally_bank] = attacker6;

    //tai move history
    struct used_moves attacker7 = battle_resources->battle_history->used_moves[bank_attacker];
    battle_resources->battle_history->used_moves[bank_attacker] = battle_resources->battle_history->used_moves[ally_bank];
    battle_resources->battle_history->used_moves[ally_bank] = attacker7;

    //abilities in RAM
    u8 attackerability = abilities_by_banks[bank_attacker];
    abilities_by_banks[bank_attacker] = abilities_by_banks[ally_bank];
    abilities_by_banks[ally_bank] = attackerability;

    //in-party position
    u16* partyAttacker = &battle_team_id_by_side[bank_attacker];
    u16* partyAlly = &battle_team_id_by_side[ally_bank];
    struct pokemon* poke;
    if (get_bank_side(bank_attacker))
        poke = &party_opponent[0];
    else
        poke = &party_player[0];

    struct pokemon attacker8 = poke[*partyAttacker];
    poke[*partyAttacker] = poke[*partyAlly];
    poke[*partyAlly] = attacker8;

    //selected move
    u16 attacker9 = chosen_move_by_banks[bank_attacker];
    chosen_move_by_banks[bank_attacker] = chosen_move_by_banks[ally_bank];
    chosen_move_by_banks[ally_bank] = attacker9;

    u8 attacker10 = battle_stuff_ptr->chosen_move_position[bank_attacker];
    battle_stuff_ptr->chosen_move_position[bank_attacker] = battle_stuff_ptr->chosen_move_position[ally_bank];
    battle_stuff_ptr->chosen_move_position[ally_bank] = attacker10;

    u8 attacker11 = battle_stuff_ptr->move_target[bank_attacker];
    battle_stuff_ptr->move_target[bank_attacker] = battle_stuff_ptr->move_target[ally_bank];
    battle_stuff_ptr->move_target[ally_bank] = attacker11;

    if (!get_bank_side(ally_bank))
    {
        u8 attacker13 = move_selection_cursor_pbs[bank_attacker];
        move_selection_cursor_pbs[bank_attacker] = move_selection_cursor_pbs[ally_bank];
        move_selection_cursor_pbs[ally_bank] = attacker13;
    }

    u16 attacker14 = last_used_moves[bank_attacker];
    last_used_moves[bank_attacker] = last_used_moves[ally_bank];
    last_used_moves[ally_bank] = attacker14;

    //objects
    u8* objCase = &battle_scripting.field21;
    battle_scripting.field22 = 0;

     *objCase = 21;
     c2_80777E8(); //fade screen

    *objCase = 3;
    while (*objCase < 21)
    {
        c2_80777E8(); //load everything
    }

    //turn order
    u16 atk_order = get_bank_turn_order(bank_attacker);
    u16 ally_order = get_bank_turn_order(ally_bank);
    turn_order[atk_order] = ally_bank;
    turn_order[ally_order] = bank_attacker;

    battle_scripting.active_bank = ally_bank;
}

bool check_magneticflux_bank(u8 bank)
{
    if (is_bank_present(bank) && (check_ability(bank, ABILITY_PLUS) || check_ability(bank, ABILITY_MINUS)))
        return 1;
    return 0;
}

void can_magneticflux_work(void)
{
    u8 side = get_bank_side(bank_attacker);
    for (u8 i = 0; i < no_of_all_banks; i++)
    {
        if (side == get_bank_side(i) && check_magneticflux_bank(i) && get_howmany_stats_can_change(i, 1, current_move))
        {
            battlescripts_curr_instruction += 4;
            another_active_bank = 0;
            bank_partner_def = bank_attacker; //save bank
            return;
        }
    }
    battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
}

void magnetic_flux_effect(void)
{
    u8 side = get_bank_side(bank_attacker);
    for (u8 i = 0; i < no_of_all_banks; i++)
    {
        if (side == get_bank_side(i) && !(another_active_bank & BIT_GET(i)) && check_magneticflux_bank(i))
        {
            another_active_bank |= BIT_GET(i);
            bs_push(battlescripts_curr_instruction - 3, BS_MULTIPLESTATCHANCE_ATK_CERTAIN);
            bank_attacker = i;
            return;
        }
    }
    bank_attacker = bank_partner_def; //restore bank
}

bool check_flowershield_bank(u8 bank, u16 move)
{
    if (is_bank_present(bank) && is_of_type(bank, TYPE_GRASS))
    {
        if (move_table[move].type != TYPE_GROUND || GROUNDED(bank))
            return 1;
    }
    return 0;
}

void canuse_flowershield(void)
{
    for (u8 i = 0; i < no_of_all_banks; i++)
    {
        if (check_flowershield_bank(i, current_move) && get_howmany_stats_can_change(i, 1, current_move))
        {
            battlescripts_curr_instruction += 4;
            another_active_bank = 0;
            bank_partner_def = bank_attacker; //save bank
            return;
        }
    }
    battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
}

void flowershield_effect(void)
{
    for (u8 i = 0; i < no_of_all_banks; i++)
    {
        if (!(another_active_bank & BIT_GET(i)) && check_flowershield_bank(i, current_move))
        {
            another_active_bank |= BIT_GET(i);
            bs_push(battlescripts_curr_instruction - 3, BS_MULTIPLESTATCHANCE_ATK_CERTAIN);
            bank_attacker = i;
            return;
        }
    }
    bank_attacker = bank_partner_def; //restore bank
}

void canuselastresort(void)
{
    s8 lastresort_pos = get_move_position(bank_attacker, current_move);
    u8 known_moves = 0;
    u8 fail = 0;
    if (lastresort_pos != -1)
    {
        u16* move_ptr = &battle_participants[bank_attacker].moves[0];
        for (u8 i = 0; i < 4; i++)
        {
            u16 move = move_ptr[i];
            if (move)
            {
                known_moves++;
                if (i != lastresort_pos && !(new_battlestruct->bank_affecting[bank_attacker].usedmoves & BIT_GET(i)))
                {
                    fail = 1;
                    break;
                }
            }
        }
    }
    if (fail || known_moves <= 1)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
        battlescripts_curr_instruction += 4;
}

void topsyturvy_effect(void)
{
    u8 reversed_stats = 0;
    for (u8 i = 0; i < 7; i++)
    {
        u8* stat = &battle_participants[bank_target].atk_buff + i;
        if (*stat != 6)
        {
            reversed_stats++;
            if (*stat < 6)
            {
                *stat += (6 - *stat) * 2;
            }
            else //*stat > 6
            {
                *stat -= (*stat - 6) * 2;
            }
        }
    }
    if (reversed_stats)
        battlescripts_curr_instruction += 4;
    else
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
}

void bestow_effect(void)
{
    u16* user_item = &battle_participants[bank_attacker].held_item;
    u16* target_item = &battle_participants[bank_target].held_item;
    if (*user_item && (can_lose_item(bank_attacker, 1, 0)) && !(*target_item) && canlose_megastone(bank_target, *user_item))
    {
        battlescripts_curr_instruction += 4;
        *target_item = *user_item;
        last_used_item = *user_item;
        *user_item = 0;
        active_bank = bank_attacker;
        bb2_setattributes_in_battle(0, REQUEST_HELDITEM_BATTLE, 0, 2, user_item);
        mark_buffer_bank_for_execution(active_bank);
        active_bank = bank_target;
        bb2_setattributes_in_battle(0, REQUEST_HELDITEM_BATTLE, 0, 2, target_item);
        mark_buffer_bank_for_execution(active_bank);
    }
    else
    {
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    }
}

void conversion_effect(void)
{
    u8 effect = 0;
    u8 type = 0;
    if (current_move == MOVE_CONVERSION)
    {
        type = move_table[battle_participants[bank_attacker].moves[0]].type;
        if (!is_of_type(bank_attacker, type))
            effect = 1;
    }
    else //current move == MOVE_CONVERSION2
    {
        u8 searched_moves = 0;
        u32 searched_moves_bitfield = 0;
        u8 last_type = new_battlestruct->bank_affecting[bank_target].lastmove_type;
        if (last_type)
        {
            last_type &= 0x3F;
            if (last_type >= TYPE_FAIRY)
                last_type -= 5;
            while (searched_moves < 18)
            {
                type = /*__umodsi3(rng(), 0x18)*/ random_value(0x18);
                if (type != TYPE_EGG && (type <= 0x11 || type == TYPE_FAIRY) && ((searched_moves_bitfield & bits_table[type]) == 0))
                {
                    searched_moves_bitfield |= bits_table[type];
                    searched_moves++;
                    if (type >= TYPE_FAIRY)
                        type -= 5;
                    u8 effectiveness = type_effectiveness_table[last_type][type];
                    if (type == 0x12)
                        type = TYPE_FAIRY;
                    if (!is_of_type(bank_attacker, type) && (effectiveness == 0 || effectiveness == 5))
                    {
                        effect = 1;
                        break;
                    }
                }
            }
        }
    }
    if (effect)
    {
        battlescripts_curr_instruction += 4;
        battle_text_buff1[0] = 0xFD;
        battle_text_buff1[1] = 3;
        battle_text_buff1[2] = type;
        battle_text_buff1[3] = 0xFF;
        set_type(bank_attacker, type);
    }
    else
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
}

//not functions delcarations, just addresses for BS
extern void PARTYHEAL_USER();
extern void PARTYHEAL_ALLY();
extern void PARTYHEAL_TEAM();

void party_heal(void)
{
    u8 ability_to_ignore = 0;
    u8 ignore_at_users = 0;
    if (current_move == MOVE_HEAL_BELL)
        ability_to_ignore = ABILITY_SOUNDPROOF;
    else if (current_move == MOVE_AROMATHERAPY)
    {
        ability_to_ignore = ABILITY_SAP_SIPPER;
        ignore_at_users = 1;
    }
    u8 effect = 0;
    u32* user_status = &battle_participants[bank_attacker].status.int_status;
    u32 condition = 0;
    u8 pos = 0;
    u8 ally = bank_attacker ^ 2;
    struct pokemon* poke = get_party_ptr(bank_attacker);
    void* instuction = 0;
    if (*user_status && (!check_ability(bank_attacker, ability_to_ignore) || ignore_at_users))
    {
        effect = 1;
        pos = battle_team_id_by_side[bank_attacker];
        condition = *user_status;
        *user_status = 0;
        active_bank = bank_attacker;
        bb2_setattributes_in_battle(0, REQUEST_STATUS_BATTLE, 0, 4, user_status);
        mark_buffer_bank_for_execution(active_bank);
        instuction = &PARTYHEAL_USER;
    }
    else if (is_bank_present(ally) && battle_participants[ally].status.int_status && !check_ability(ally, ability_to_ignore))
    {
        effect = 1;
        pos = battle_team_id_by_side[ally];
        condition = battle_participants[ally].status.int_status;
        battle_participants[ally].status.int_status = 0;
        active_bank = ally;
        battle_scripting.active_bank = ally;
        bb2_setattributes_in_battle(0, REQUEST_STATUS_BATTLE, 0, 4, &battle_participants[ally].status.int_status);
        mark_buffer_bank_for_execution(active_bank);
        instuction = &PARTYHEAL_ALLY;
    }
    else
    {
        for (u8 i = 0; i < 6; i++)
        {
            condition = get_attributes(&poke[i], ATTR_STATUS_AILMENT, 0);
            u8 ability = get_poke_ability(&poke[i]);
            if (is_poke_valid(&poke[i]) && condition && ability_to_ignore != ability)
            {
                effect = 1;
                pos = i;
                instuction = &PARTYHEAL_TEAM;
                u32 zero = 0;
                set_attributes(&poke[i], ATTR_STATUS_AILMENT, &zero);
                break;
            }
        }
    }
    if (effect)
    {
        bs_push(battlescripts_curr_instruction - 3, instuction);
        //PSN/BRN/PAR/SLP/FRZ
        u8* string = &battle_communication_struct.multistring_chooser;
        if ((condition & STATUS_POISON) || (condition & STATUS_TOXIC_POISON))
            *string = 0;
        else if (condition & STATUS_BURN)
            *string = 1;
        else if (condition & STATUS_PARALYSIS)
            *string = 2;
        else if (condition & STATUS_SLEEP)
            *string = 3;
        else if (condition & STATUS_FREEZE)
            *string = 4;
        u8* text_buff = &battle_text_buff1[0];
        if (get_bank_side(bank_attacker))
        {
            if (battle_flags.trainer)
                text_buff = strcpy_xFF_terminated_0(text_buff, (void*) 0x085CBD8B);
            else
                text_buff = strcpy_xFF_terminated_0(text_buff, (void*) 0x085CBD85);
        }
        get_attributes(&poke[pos], ATTR_NAME, text_buff);
    }
}

void accupressure_effect(void)
{
    u32 checked_stats_bitfield = 0;
    u8 checked_stats_int = 0;
    u8 stat;
    u8* statvalue = &battle_participants[bank_target].atk_buff;
    while (checked_stats_int < 7)
    {
        stat = random_value(7)/*__umodsi3(rng(), 7)*/;
        if (!(checked_stats_bitfield & bits_table[stat]))
        {
            checked_stats_bitfield |= bits_table[stat];
            checked_stats_int++;
            if (*(statvalue + stat) != 0xC)
            {
                battle_scripting.stat_changer = 0x21 + stat;
                battlescripts_curr_instruction += 4;
                return;
            }
        }
    }
    battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
}

void mega_primal_cry(void)
{
    play_cry(battle_participants[new_battlestruct->various.active_bank].species,-0x19,0x5);
}

void canusefling(void)
{
    u16 item = battle_participants[bank_attacker].held_item;
    if (item == 0 || item == ITEM_REDORB || item == ITEM_BLUEORB || item == ITEM_ABILITYCAPSULE || ((item >= 0x236 && item <= 0x246) || item == 0x24A)
		|| get_item_pocket_id(item) == 2 || get_item_pocket_id(item) == 3 || (get_item_pocket_id(item) == 4 && (check_ability(bank_target, ABILITY_UNNERVE) || check_ability(bank_target ^ 2, ABILITY_UNNERVE)))
		|| !can_lose_item(bank_attacker, 0, 0) || check_ability(bank_attacker, ABILITY_KLUTZ) || new_battlestruct->bank_affecting[bank_attacker].embargo || new_battlestruct->field_affecting.magic_room)
		battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
        battlescripts_curr_instruction += 4;
}

void happyhour_effect(void)
{
    new_battlestruct->various.happyhour_bonus = 1;
}

void canuseskydrop(void)
{
    if (bank_target == (bank_attacker ^ 2) || new_battlestruct->field_affecting.gravity)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else if (get_poke_weight(bank_target) >= 2000)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction + 4);
    else
        battlescripts_curr_instruction += 8;
}

void skydropup(void)
{
    new_battlestruct->bank_affecting[bank_attacker].sky_drop_attacker = 1;
    new_battlestruct->bank_affecting[bank_target].sky_drop_target = 1;
    battle_participants[bank_attacker].status2.multiple_turn_move = 1;
    locked_move[bank_attacker] = current_move;
}

void canusefairylock(void)
{
    struct field_affecting* lock = &new_battlestruct->field_affecting;
    if (lock->fairy_lock)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        lock->fairy_lock = 2;
        battlescripts_curr_instruction += 4;
    }
}

void healthbox_target_update(void)
{
    update_hpbar(bank_target);
}

void target_transformed_species_to_0(void)
{
    (*battle_graphics.graphics_data->species_info)[bank_target].transformed_species = 0;
}

void scr_active_transformed_species_to_0(void)
{
    (*battle_graphics.graphics_data->species_info)[battle_scripting.active_bank].transformed_species = 0;
}

void attacker_bank_exchange(void)
{
    u8 temp = bank_attacker;
    bank_attacker = new_battlestruct->various.active_bank;
    new_battlestruct->various.active_bank = temp;
}

void species_data_change(u8 bank, u16 new_species)
{
	struct pokemon* poke = get_bank_poke_ptr(bank);
    calculate_stats_pokekmon(poke);
    u16* species =  &battle_participants[bank].species;
    *species = new_species;
    active_bank = bank;
    bb2_setattributes_in_battle(0, REQUEST_SPECIES_BATTLE, 0, 2, species);
    mark_buffer_bank_for_execution(active_bank);
}

void form_change_change_species(void)
{
    species_data_change(battle_scripting.active_bank, new_battlestruct->various.var1);
}

void in_battle_form_change(u8 bank, bool change_hp, bool change_type)
{
    (*battle_graphics.graphics_data->species_info)[bank].transformed_species = 0;
    struct pokemon* poke = get_bank_poke_ptr(bank);
    calculate_stats_pokekmon(poke);
    struct battle_participant* battle_poke = &battle_participants[bank];
    if(change_type)
    {
        const struct poke_basestats* PokeStats = &((*basestat_table)[battle_poke->species]);
        battle_poke->type1 = PokeStats->type1;
        battle_poke->type2 = PokeStats->type2;
    }
    if(change_hp)
    {
        u16 hp_diff=battle_poke->max_hp - battle_poke->current_hp;
        battle_poke->max_hp = get_attributes(poke, ATTR_TOTAL_HP, 0);
        battle_poke->current_hp = battle_poke->max_hp - hp_diff;
        set_attributes(poke, ATTR_CURRENT_HP, &(battle_poke->current_hp));
        calculate_stats_pokekmon(poke);
        update_hpbar(bank);
    }
	memcpy(&battle_poke->atk, &poke->attack, 10);
//    battle_poke->atk = get_attributes(poke, ATTR_ATTACK, 0);
//    battle_poke->def = get_attributes(poke, ATTR_DEFENCE, 0);
//    battle_poke->spd = get_attributes(poke, ATTR_SPEED, 0);
//    battle_poke->sp_atk = get_attributes(poke, ATTR_SPECIAL_ATTACK, 0);
//    battle_poke->sp_def = get_attributes(poke, ATTR_SPECIAL_DEFENCE, 0);
}

void stat_only_form_change(void)
{
    in_battle_form_change(battle_scripting.active_bank,false,false);
}

void type_stat_form_change(void)
{
    in_battle_form_change(battle_scripting.active_bank,false,true);
}

void hp_stat_form_change(void)
{
    in_battle_form_change(battle_scripting.active_bank,true,false);
}

void ash_greninja_check(void)
{
    bool side = get_bank_side(bank_attacker);
	if(!not_impostered(bank_attacker))
		return;
    if(battle_participants[bank_attacker].species==POKE_GRENINJA && check_ability(bank_attacker,ABILITY_BATTLE_BOND) &&
       (!(side && new_battlestruct->party_bit.battle_bond_ai & bits_table[battle_team_id_by_side[bank_attacker]]) ||
        (!side && new_battlestruct->party_bit.battle_bond_user & bits_table[battle_team_id_by_side[bank_attacker]])))
    {
        if(side)
        {
            new_battlestruct->party_bit.battle_bond_ai |= bits_table[battle_team_id_by_side[bank_attacker]];
        }
        else
        {
            new_battlestruct->party_bit.battle_bond_user |= bits_table[battle_team_id_by_side[bank_attacker]];
        }
        new_battlestruct->various.var1 = POKE_ASH_GRENJA;
        battle_scripting.active_bank=bank_attacker;
        new_battlestruct->various.var2 = 0x247;
        bs_push_current(BS_BATTLE_BOND);
    }
}

void set_transfrom_palchange(void)
{
   (*battle_graphics.graphics_data->species_info)[bank_attacker].pal_change = 1;
    new_battlestruct->bank_affecting[bank_attacker].transform_tid = get_attributes(get_bank_poke_ptr(bank_target), ATTR_TID, 0);
}

void bug_bite_set_berry_eaten(void)
{
    berry_eaten(bank_attacker,false);
}

void belch_canceler(void)
{
    if(!((get_bank_side(bank_attacker) && new_battlestruct->party_bit.eaten_berry_opponent&bits_table[battle_team_id_by_side[bank_attacker]])
       || (!get_bank_side(bank_attacker) && new_battlestruct->party_bit.eaten_berry_player&bits_table[battle_team_id_by_side[bank_attacker]])))
    {
        battlescripts_curr_instruction = (void *) 0x082D9F1A;
        move_outcome.failed = 1;
    }
}

void print_from_nbsvar2(void)
{
    prep_string(new_battlestruct->various.var2, battle_scripting.active_bank);
    battle_communication_struct.is_message_displayed=1;
}

void attackerhp_to_zero(void)
{
    active_bank = bank_attacker;
    prepare_health_bar_update_buffer(0, 0x7FFF);
    mark_buffer_bank_for_execution(active_bank);
}

void reset_bg2x(void)
{
    bg2X_battle = 0;
}

void print_attack_message(void)
{
    current_move = chosen_move_by_banks[bank_attacker];
    prep_string(4, bank_attacker);
    battle_communication_struct.is_message_displayed = 1;
}

void check_and_set_pledge(void)
{
    u8 pledge_effect=0;
    u8 bank_ally=bank_attacker^2;
    u16 first_mon_move=current_move;
    u16 second_mon_move=0;
    if(battle_flags.double_battle)
    {
        if(get_bank_turn_order(bank_ally)>get_bank_turn_order(bank_attacker))
        {
            if(is_bank_present(bank_ally) && get_bank_turn_order(bank_ally)>get_bank_turn_order(bank_attacker) &&
               menu_choice_pbs[bank_ally]==0)
            {
                second_mon_move=chosen_move_by_banks[bank_ally];
            }
        }
        if(first_mon_move==MOVE_GRASS_PLEDGE)
        {
            if(second_mon_move==MOVE_WATER_PLEDGE)
            {
                pledge_effect=1;
            }
            else if(second_mon_move==MOVE_FIRE_PLEDGE)
            {
                pledge_effect=2;
            }
        }
        else if(first_mon_move==MOVE_WATER_PLEDGE)
        {
            if(second_mon_move==MOVE_FIRE_PLEDGE)
            {
                pledge_effect=3;
            }
            else if(second_mon_move==MOVE_GRASS_PLEDGE)
            {
                pledge_effect=1;
            }
        }
        else if(first_mon_move==MOVE_FIRE_PLEDGE)
        {
            if(second_mon_move==MOVE_GRASS_PLEDGE)
            {
                pledge_effect=2;
            }
            else if(second_mon_move==MOVE_WATER_PLEDGE)
            {
                pledge_effect=3;
            }
        }
    }
    if(pledge_effect)
    {
        new_battlestruct->side_affecting[bank_ally&1].pledge_effect=pledge_effect;
        print_attack_message();
        slot_bank2_turn_after_bank1(get_bank_turn_order(bank_attacker),get_bank_turn_order(bank_ally),bank_ally);
    }
    else
    {
        battlescripts_curr_instruction=(void *)CANCELER_FAIL;
    }
}

u16 get_move_from_pledge(u8 bank)
{
    switch(new_battlestruct->side_affecting[bank&1].pledge_effect)
    {
        case 1:
            return MOVE_GRASS_PLEDGE;
        case 2:
            return MOVE_FIRE_PLEDGE;
        case 3:
            return MOVE_WATER_PLEDGE;
    }
    return 0;
}

void set_message_bank_buffer_to_ally(void)
{
    battle_scripting.active_bank=bank_attacker^2;
}

void print_combined_attack_message(void)
{
    current_move=get_move_from_pledge(bank_attacker);
    prep_string(0x220, bank_attacker);
    battle_communication_struct.is_message_displayed = 1;
}

void set_fire_sea(void)
{
    battle_scripting.active_bank=bank_target;
    prep_string(0x223, 0);
    battle_communication_struct.is_message_displayed = 1;
}

void set_swamp(void)
{
    battle_scripting.active_bank=bank_target;
    prep_string(0x225, 0);
    battle_communication_struct.is_message_displayed = 1;
}

void set_rainbow(void)
{
    battle_scripting.active_bank=bank_attacker;
    prep_string(0x226, 0);
    battle_communication_struct.is_message_displayed = 1;
}

void save_trainerslide_pokeobj(void)
{
    u8 objID = objID_pbs_moveanimations[get_bank_by_player_ai(1)];
    new_battlestruct->various.var1 = objID;
}

void restore_trainerslide_pokeobj(void)
{
    u8 objID = new_battlestruct->various.var1;
    u8 bank = get_bank_by_player_ai(1);
    objID_pbs_moveanimations[bank] = objID;
    if (battle_participants[bank].current_hp)
        b_load_sprite_opponent(get_bank_poke_ptr(bank), bank);
}

void conider_trainermsg_firstfaint(void)
{
    u8 bank = get_bank_by_player_ai(1);
    if (!battle_participants[bank].current_hp && count_party_pokemon(bank))
    {
        //check switch-in last poke
        if ((new_battlestruct->various.trainer_slide_msg = get_slide_msg(var_8015_trainer_opponent_A, 2))
             && !new_battlestruct->various.trainer_msg_after_first_poke_done)
        {
            new_battlestruct->various.trainer_msg_after_first_poke_done = 1;
            bs_push_current(BS_TRAINER_SLIDE_MSG_RETURN);
        }
    }
}

void can_purify_work(void)
{
    if (battle_participants[bank_target].status.int_status && !check_ability(bank_target, ABILITY_COMATOSE))
    {
        battlescripts_curr_instruction += 4;
        battle_participants[bank_target].status.int_status = 0;
        active_bank = bank_target;
        bb2_setattributes_in_battle(0, REQUEST_STATUS_BATTLE, 0, 4, &battle_participants[bank_target].status.int_status);
        mark_buffer_bank_for_execution(active_bank);
    }
    else
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
}

void dont_play_move_anim(void)
{
    new_battlestruct->various.dont_play_move_anim = 1;
}

void jump_if_can_poison(void)
{
    if (!cant_poison(bank_attacker, bank_target, 0))
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
        battlescripts_curr_instruction += 4;
}

void set_laser_focus(void)
{
    if (new_battlestruct->bank_affecting[bank_attacker].always_crit)
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
    {
        new_battlestruct->bank_affecting[bank_attacker].always_crit = 2;
        battlescripts_curr_instruction += 4;
    }
}

void set_aurora_veil(void)
{
    u8 side = get_bank_side(bank_attacker);
    if (!new_battlestruct->side_affecting[side].aurora_veil && weather_abilities_effect() && HAIL_WEATHER)
    {
        u8 turns = 5;
        if (get_item_effect(bank_attacker, 1) == ITEM_EFFECT_LIGHTCLAY)
            turns = 8;
        new_battlestruct->side_affecting[side].aurora_veil = turns;
        battlescripts_curr_instruction += 4;
    }
    else
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
}

void check_terrain_seeds(void)
{
    for (u8 i = 0; i < no_of_all_banks; i++)
    {
        enum item_effects item = get_item_effect(i, 1);
        u8 stat = 0;
        if (new_battlestruct->field_affecting.grassy_terrain && item == ITEM_EFFECT_GRASSYSEED)
            stat = 0x12;
        else if (new_battlestruct->field_affecting.electic_terrain && item == ITEM_EFFECT_ELECTRICSEED)
            stat = 0x12;
        else if (new_battlestruct->field_affecting.misty_terrain && item == ITEM_EFFECT_MISTYSEED)
            stat = 0x15;
        else if (new_battlestruct->field_affecting.psychic_terrain && item == ITEM_EFFECT_PSYCHICSEED)
            stat = 0x15;
        if (stat)
        {
            battle_scripting.active_bank = i;
            battle_scripting.stat_changer = stat;
            last_used_item = battle_participants[i].held_item;
            bs_push(battlescripts_curr_instruction - 3, BS_ITEMSTATRAISE);
            break;
        }
    }
}

void check_soulheart(void)
{
    u16* done = &new_battlestruct->various.var1;
    //conserve the bank
    if (*done == 0)
        new_battlestruct->various.var2 = bank_attacker;
    for (u8 i = 0; i < no_of_all_banks; i++)
    {
        if (check_ability(i, ABILITY_SOUL_HEART) && is_bank_present(i) && !(*done & BIT_GET(i)))
        {
            *done |= BIT_GET(i);
            record_usage_of_ability(i, ABILITY_SOUL_HEART);
            battle_scripting.stat_changer = 0x14;
            bank_attacker = i;
            bs_push(battlescripts_curr_instruction - 3, BS_ATK_ABILITY_CHANGES_ATK_STAT);
            return;
        }
        static const u8 cant_receive_abilities[] = {ABILITY_FLOWER_GIFT, ABILITY_FORECAST, ABILITY_ILLUSION, ABILITY_IMPOSTER, ABILITY_MULTITYPE, ABILITY_STANCE_CHANGE, ABILITY_TRACE, ABILITY_WONDER_GUARD, ABILITY_ZEN_MODE};
        if ((check_ability(i, ABILITY_POWER_OF_ALCHEMY) || check_ability(i, ABILITY_RECEIVER)) && !battle_participants[i ^ 2].current_hp
                 && !findability_in_table(battle_participants[i ^ 2].ability_id ,cant_receive_abilities) && is_bank_present(i) && !(*done & BIT_GET(i)))
        {

            *done |= BIT_GET(i);
            bank_attacker = i;
            bs_push(battlescripts_curr_instruction - 3, BS_RECEIVER);
            return;
        }
    }
    //return the bank
    bank_attacker = new_battlestruct->various.var2;
}

void receiver_effect(void)
{
    u8 new_ability = battle_participants[bank_attacker ^ 2].ability_id;
    battle_participants[bank_attacker].ability_id = new_ability;
    abilities_by_banks[bank_attacker] = new_ability;
    record_usage_of_ability(bank_attacker, new_ability);
    last_used_ability = new_ability;
}

void canuse_strengthsap(void)
{
    //move fails only when target's stat is already at -6
    u8 statID = move_table[current_move].arg1 & 0xF;
    u8 stat_multiplier = *(&battle_participants[bank_target].hp_buff + (statID));
    if (stat_multiplier) //move works
    {
        battlescripts_curr_instruction += 4;
        //get stat value * multiplier

        u32 to_heal = apply_statboost(*(&battle_participants[bank_target].atk + (statID - 1)), stat_multiplier);
        if (get_item_effect(bank_attacker, 1) == ITEM_EFFECT_BIGROOT)
            to_heal = percent_boost(to_heal, 30);

        damage_loc = to_heal *(-1);
    }
    else
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);

}

void jumpifattackerfullhp(void)
{
    if (FULL_HP(bank_attacker))
        battlescripts_curr_instruction = (void*) read_word(battlescripts_curr_instruction);
    else
        battlescripts_curr_instruction += 4;
}

void set_effect1_formove(void)
{
	u16 effect = read_hword(battlescripts_curr_instruction);
	bool substitute = affected_by_substitute(bank_target);
	if ((effect & MOVEEFFECT_AFFECTSUSER) || !substitute) {
		new_battlestruct->move_effect.effect1 = effect;
		battlescripts_curr_instruction += 2;
	}
}

void shiftgear_checkifworks(void)
{
    u8 statsNO = 0;
    set_statchanger_to_arg1();
    if (change_stats(bank_attacker, stat_get_bits_arg(1, 0, 0), battlescripts_curr_instruction) == STAT_CHANGED)
        statsNO++;

    set_statchanger_to_arg2();
    if (change_stats(bank_attacker, stat_get_bits_arg(1, 0, 0), battlescripts_curr_instruction) == STAT_CHANGED)
        statsNO++;

    if (statsNO)
    {
        new_battlestruct->various.var2 = statsNO;
        battlescripts_curr_instruction += 4;
    }
    else
        battlescripts_curr_instruction = (void*)read_word(battlescripts_curr_instruction);
}

void shiftgear_orr_if_multiple(void)
{
    if (new_battlestruct->various.var2 > 1)
        battle_scripting.stat_changer |= STAT_MULTIPLE;
}

void dont_stat_if_multiple(void)
{
    if (new_battlestruct->various.var2 > 1)
        new_battlestruct->various.dont_play_stat_anim = 1;
}

void jumpifalloppositepokemonbehindsubstitute(void)
{
    u8 bank1 = bank_attacker ^ 1;
    u8 bank2 = bank1 ^ 2;
    if (affected_by_substitute(bank1) && affected_by_substitute(bank2))
        battlescripts_curr_instruction = (void*)read_word(battlescripts_curr_instruction);
    else
        battlescripts_curr_instruction += 4;
}

void triattackrand(void)
{
    u16* effect = &new_battlestruct->move_effect.effect1;
    switch (random_value(3)/*__umodsi3(rng(), 3)*/)
    {
    case 0:
        *effect = MOVEEFFECT_BRN;
        break;
    case 1:
        *effect = MOVEEFFECT_FRZ;
        break;
    default:
        *effect = MOVEEFFECT_PRLZ;
        break;
    }
}

void jumpifnotarg1type(void)
{
    if (!is_of_type(bank_attacker, move_table[current_move].arg1))
        battlescripts_curr_instruction = (void*)read_word(battlescripts_curr_instruction);
    else
        battlescripts_curr_instruction += 4;
}

void set_stats_to_play(void)
{
    new_battlestruct->various.dont_play_stat_anim = 0;
}

void prepare_switchbank_data(void)
{
    u8 bank = get_battle_bank(read_byte(battlescripts_curr_instruction));
    battlescripts_curr_instruction++;

    u8 pokeID = new_battlestruct->various.var1;
    battle_stuff_ptr->field_5C[bank] = pokeID;
    battle_stuff_ptr->field_58[bank] = battle_team_id_by_side[bank];
    if (!is_in_tag_battle())
        change_order_in_battle(bank);
    if ((battle_flags.link && battle_flags.frontier_general) || (battle_flags.link && battle_flags.player_partner) || (battle_flags.frontier_general && battle_flags.flag_x2000000))
    {
        sub_81B8E80(bank, pokeID, 0);
        sub_81B8E80(bank ^ 2, pokeID, 1);
    }
    if (battle_flags.player_partner)
        sub_80571DC(bank, pokeID);
}

void jump_if_forcesetflag_set(void)
{
    if (GET_CUSTOMFLAG(FORCE_SET_FLAG))
        battlescripts_curr_instruction = (void*)read_word(battlescripts_curr_instruction);
    else
        battlescripts_curr_instruction += 4;
}

void revert_mega(void) //bank
{
    u8 bank = get_battle_bank(read_byte(battlescripts_curr_instruction++));
    revert_mega_to_normalform_new(get_bank_side(bank)); //JeremyZ
}

void instruct_canceler(void)
{
    u16 last_target_move = calling_move_used[bank_target];
    if(last_target_move == 0x0 || last_target_move == 0xFFFF || last_target_move!=current_move_used[bank_target] || battle_participants[bank_target].current_hp==0
       || move_table[last_target_move].script_id ==39 || find_move_in_table(last_target_move,instruct_banlist) || find_move_in_table(last_target_move,moves_calling_another_move)
        || find_move_in_table(last_target_move,moves_with_charging_turn))
    {
        battlescripts_curr_instruction = (void *) 0x082D9F1A;
        move_outcome.failed = 1;
    }
    else
    {
        new_battlestruct->various.var2 = last_target_move;
    }
}

void set_instruct(void)
{
    new_battlestruct->various.instruct_phase = 1;
    bank_attacker = bank_target;
    current_move =new_battlestruct->various.var2;
    bank_target = get_target_of_move(current_move, 0, 0);
    set_attacking_move_type();
    attack_iteration_cleanup();
    hitmarker &= 0xFDF1D9FF;
    battle_scripting.cmd49_state_tracker=0;
    battlescripts_curr_instruction = get_move_battlescript_ptr(current_move);
    bs_push_current((void*)(0x82DB87D));
}

void set_spotlight(void); //Spotlight, JeremyZ
void set_throatchop(void); //Throat Chop, JeremyZ
void speed_swap(void); //Speed Swap, JeremyZ
void jumpifuserheadblown(void); //Mind Blown, JeremyZ
void print_start_z(void); //Start Z, JeremyZ
void jumpifnostockpile(void); //Spit Up, JeremyZ
void calc_recoil_dmg2(void); //Recoil damage, JeremyZ
void clanging_scales_stat(void); //Clanging Scales, Clangorous Soulblaze, JeremyZ

const command callasm_table[] = {&ability_switchin_effect /*0*/, &jump_if_forcesetflag_set /*1*/, &change_attacker_item /*2*/, &callasm_nop /*3*/, &callasm_nop /*4*/,
&changestatvar1_atk /*5*/, &changestatvar2_atk /*6*/, &frisk_target_item /*7*/, &callasm_nop /*8*/, &set_type_msg_buffer /*9*/, &callasm_nop /*10*/, &bad_dreams_damage_calc /*11*/,
&callasm_nop /*12*/, &mentalherb /*13*/, &callasm_nop /*14*/, &hazards_bank_switcher /*15*/, &hazards_bank_return /*16*/, &leechseed_update /*17*/,
&callasm_nop /*18*/, &callasm_nop /*19*/, &moxie_stat_raise /*20*/, &grassyterrainn_heal /*21*/, &callitemeffects /*22*/,
&set_var1_to_0 /*23*/, &damagecalc2 /*24*/, &set_statchanger_to_arg1 /*25*/, &checksubstitute /*26*/, &callasm_nop /*27*/,
&multiplestats_prepare /*28*/, &do_multiple_stats_from_movetable /*29*/, &callasm_nop /*30*/, &checkifcanconfuse_or_changestats /*31*/, &callasm_nop /*32*/,
&jumpifcantpoison /*33*/, &jumpifcantparalyze /*34*/, &jumpifcantburn /*35*/, &statustoeffect /*36*/, &half_hp_damage /*37*/,
&jumpifonlyonepokemon /*38*/, &setlunardanceeffect /*39*/, &weatherhpheal /*40*/, &checkifcantransfercondition /*41*/, &choosestatusinflictiontext /*42*/,
&roostactivation /*43*/, &gravitysetter /*44*/, &gravity_ender /*45*/, &setidentifierbit /*46*/, &breakprotection /*47*/,
&suckerpunchchecker /*48*/, &oppositegenderscheck /*49*/, &setthirdtype /*50*/, &ability_change /*51*/, &roomsetter /*52*/, &countercalc /*53*/,
&gastroacid /*54*/, &setembargo /*55*/, &naturalgift /*56*/, &afteryou_check /*57*/, &powder_setter /*58*/, &jumpifnoally /*59*/,
&electrify /*60*/, &set_entry_hazards /*61*/, &jumpifnotdoublebattle /*62*/, &jumpifattackerandtargetdontsharetypes /*63*/,
&try_autotonomize /*64*/, &set_iondeluge /*65*/, &reflecttypes /*66*/, &sethealblock /*67*/, &traptarget /*68*/, &mefirst_check /*69*/,
&jump_to_move_bs /*70*/, &setluckychant /*71*/, &settailwind /*72*/, &cansetnightmare /*73*/, &bellydrum /*74*/, &setmagnetrise /*75*/,
&settelekinesis /*76*/, &setpowertrick /*77*/, &make_pokemon_one_type /*78*/, &defog_effect /*79*/, &copycat_move /*80*/,
&psycho_swaps /*81*/, &psychosplits /*82*/, &stockpile_record /*83*/, &twoturn_moves /*84*/, &powerherb_check /*85*/, &set_terrain /*86*/,
&setaquaring /*87*/, &get_trainer_name_for_mega /*88*/, &mega_evo_updatehpbar /*89*/, &mega_evo_pursuit_check /*90*/,
&jumpifuserhasnoHP /*91*/, &quash_setter /*92*/, &beatup_getloopcounter /*93*/, &canuse_allyswitch /*94*/, &allyswitch_dataswitch /*95*/,
&can_magneticflux_work /*96*/, &magnetic_flux_effect /*97*/, &canuse_flowershield /*98*/, &flowershield_effect /*99*/, &canuselastresort /*100*/,
&topsyturvy_effect /*101*/, &bestow_effect /*102*/, &conversion_effect /*103*/, &party_heal /*104*/, &accupressure_effect /*105*/, &mega_primal_cry /*106*/,
&canusefling /*107*/, &happyhour_effect /*108*/, &canuseskydrop /*109*/, &skydropup /*110*/, &canusefairylock /*111*/, &healthbox_target_update /*112*/,
&target_transformed_species_to_0 /*113*/, &scr_active_transformed_species_to_0 /*114*/, &stat_only_form_change /*115*/, &set_transfrom_palchange /*116*/,
&bug_bite_set_berry_eaten /*117*/, &type_stat_form_change/*118*/, &form_change_change_species/*119*/, &belch_canceler/*120*/,
&attacker_bank_exchange/*121*/, &print_from_nbsvar2/*122*/, &attackerhp_to_zero /*123*/, &reset_bg2x /*124*/, &check_and_set_pledge/*125*/,
&print_combined_attack_message/*126*/, &print_attack_message/*127*/, &set_message_bank_buffer_to_ally /*128*/, &set_fire_sea /*129*/, &set_swamp/*130*/,
&set_rainbow/*131*/, &callasm_nop/*132*/, &save_trainerslide_pokeobj /*133*/, &restore_trainerslide_pokeobj /*134*/, &conider_trainermsg_firstfaint /*135*/,
&can_purify_work /*136*/, &dont_play_move_anim /*137*/, &jump_if_can_poison /*138*/, &set_laser_focus /*139*/, &set_aurora_veil /*140*/, &check_terrain_seeds /*141*/,
&check_soulheart /*142*/, &canuse_strengthsap /*143*/, &jumpifattackerfullhp /*144*/, &set_effect1_formove /*145*/, &set_statchanger_to_arg2 /*146*/,
&shiftgear_checkifworks /*147*/, &shiftgear_orr_if_multiple /*148*/, &dont_stat_if_multiple /*149*/, &jumpifalloppositepokemonbehindsubstitute /*150*/,
&triattackrand /*151*/, &statustoeffect2 /*152*/, &multiplestats_prepare_custom /*153*/, &do_multiple_stats_custom /*154*/, &jumpifnotarg1type /*155*/,
&set_stats_to_play /*156*/, &receiver_effect /*157*/, &bugbite_get_berry_effect /*158*/, &prepare_switchbank_data /*159*/, &ash_greninja_check /*160*/,
&zygarde_message_based_on_side/*161*/, &hp_stat_form_change /*162*/, &revert_mega /*163*/, &instruct_canceler /*164*/, &set_instruct /*165*/,
&apply_zmove_changes/*166*/, &set_spotlight/*167*/, &set_throatchop/*168*/, &speed_swap/*169*/, &jumpifuserheadblown/*170*/,
&print_start_z/*171*/, &jumpifnostockpile/*172*/, &calc_recoil_dmg2/*173*/, &clanging_scales_stat/*174*/};

void atk83_callasm(void)
{
    u16 command_id = read_hword(battlescripts_curr_instruction + 1);
    battlescripts_curr_instruction += 3;
    callasm_table[command_id]();
}
