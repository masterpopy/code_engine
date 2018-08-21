#include "defines.h"
#include "static_references.h"

bool is_bank_present(u32 bank);
bool percent_chance(u8 percent);
struct pokemon* get_bank_poke_ptr(u8 bank);
bool is_poke_valid(const struct pokemon* poke);
void revert_form_change(bool mega_revert, u8 teamID, u8 side, const struct pokemon* poke);
u8 get_bank_side(u8 bank);
void setflag(u16 flag);
bool time_check(u8 from, u8 to); //JeremyZ

/*#pragma pack(push,1)
struct double_grass_tile{
    u16 tile_id;
    u8 percent;
};
#pragma pack(pop)

struct double_grass_tile double_grass_tiles[DOUBLE_WILD_TILES] = {
    {0xD, 70}
};*/

bool doubles_tile_check(void)
{
    return cur_map_get_blockid_at(sav1->x_coords + 7, sav1->y_coords + 7) == 0xD && percent_chance(70);
    /*for (u32 i = 0; i < DOUBLE_WILD_TILES; i++)
    {
        if (double_grass_tiles[i].tile_id == tile)
        {
            if (percent_chance(double_grass_tiles[i].percent))
                return 1;
            return 0;
        }
    }
    return 0;*/
}

bool wild_grass_battle(void* wild_data)
{
    u8 battle = consider_creating_wild_poke(wild_data, 0, 3);
    if (GET_CUSTOMFLAG (DOUBLE_WILD_BATTLES_FLAG) && DOUBLE_WILD_BATTLES && battle && doubles_tile_check() && !not_enough_for_doubles()) //consider double wild battles
    {
		party_opponent[1] = party_opponent[0];
        while (!consider_creating_wild_poke(wild_data, 0, 3));
        //party_opponent[1] = poke;
        battle_flags.double_battle = 1;
    }
    return battle;
}

void pokeball_chosen(u8 taskID)
{
    const u8* fail_msg = NULL; //wild double battle and (two pokes are alive or using pokeball via second pokemon when two are alive)
    if (WILD_DOUBLE_BATTLE &&
        ((is_bank_present(1) && is_bank_present(3)) || (bank_in_menu == 2 && is_bank_present(0))))
        {
            static const u8 text_impossible_to_aim[] = {0x0A, 0xF0, 0xAB, 0x0D, 0xA4, 0x03, 0xAB, 0x0E, 0x8A, 0x10, 0x06, 0x03, 0x79, 0x0E, 0x20, 0xB8, 0xFE, 0x0C, 0x9C, 0x0F, 0x24, 0x01, 0xD6, 0x09, 0xD2, 0x01, 0xD1, 0x10, 0xEC, 0x0A, 0x13, 0xAB, wait_for_pressed_key, 0xFF};
            //It's impossible to aim without being focused!

            fail_msg = text_impossible_to_aim;
        }
    else if (is_team_and_pc_full()) //full box
        fail_msg = text_BOX_IS_FULL;
    bool pyramid = is_in_battle_pyramid();
    if (fail_msg)
    {
        if (pyramid)
            pyramid_bag_print_msg(taskID, fail_msg, aftertext_pyramid_bag);
        else
            bag_print_msg(taskID, 1, fail_msg, aftertext_bag);
    }
    else
    {
        bag_remove_item(var_800E_last_used_item, 1);
        if (pyramid)
            item_used_exit_pyramid_bag(taskID);
        else
            item_used_exit_bag(taskID);
    }
}

bool ignore_second_poke_action(u8 bank)
{
    struct flags2 status2 = battle_participants[bank].status2;
    if (WILD_DOUBLE_BATTLE && bank == 2 && is_bank_present(0) && (menu_choice_pbs[0] == ACTION_RUN || (menu_choice_pbs[0] == ACTION_ITEM && get_item_pocket_id(var_800E_last_used_item) == POCKET_BALLS))) //wild double battle catch attempt
    {
        menu_choice_pbs[bank] = 12; //skips menu selection
        return 1;
    }
    else if (status2.recharge || status2.multiple_turn_move) //locked via battle effects
    {
        menu_choice_pbs[bank] = ACTION_MOVE;
        return 1;
    }
    return 0;
}

bool is_poke_caught(u16 species)
{
    return get_or_set_pokedex_flags(species_to_national_dex(species), 1);
}

bool is_poke_ultrabeast(u16 species)
{
	return ((species > 0x34D && species < 0x355) || (species > 0x42E && species < 0x433)); //JeremyZ
}

u32 calc_ball_formula(enum ball_index ball_no, struct battle_participant* catching)
{
    u8 multiplier = 10;
    u8 catchrate = (*basestat_table)[catching->species].catch_rate;
    switch (ball_no)
    {
    //case BALL_PREMIER: case BALL_LUXURY: case BALL_POKE: case BALL_MASTER:
    //case BALL_FRIEND: case BALL_HEAL: case BALL_CHERISH:
    default: multiplier = 10;
        break;
    case BALL_SAFARI:
        catchrate = battle_stuff_ptr->safari_rate * 1275 / 100;
    case BALL_GREAT:
    #if EXPANDED_POKEBALLS
    case BALL_SPORT:
    #endif // EXPANDED_POKEBALLS
        multiplier = 15;
        break;
    case BALL_ULTRA:
        multiplier = 20;
        break;
    case BALL_NET:
        if (catching->type1 == TYPE_BUG || catching->type1 == TYPE_WATER || catching->type2 == TYPE_BUG || catching->type2 == TYPE_WATER)
            multiplier = 35;
        break;
    case BALL_DIVE:
        if (sav1_get_map_type() == MAP_UNDERWATER)
            multiplier = 35;
        break;
    case BALL_NEST:
        {
            u8 level = catching->level;
            if (level < 30) //JeremyZ
                multiplier = 41 - level;
        }
        break;
    case BALL_REPEAT:
        if (is_poke_caught(catching->species))
            multiplier = 35;
        break;
    case BALL_TIMER:
        multiplier = battle_trace.battle_turn_counter * 3 + 10; //JeremyZ
        if (multiplier > 40)
            multiplier = 40;
        break;
    #if EXPANDED_POKEBALLS == true
    case BALL_LEVEL:
        {
            u8 opp_level = catching->level;
            u8 pl_level = battle_participants[bank_attacker].level;
            if (opp_level >= pl_level)
                multiplier = 10;
            else if (pl_level < opp_level * 2)
                multiplier = 20;
            else if (pl_level < opp_level * 3)
                multiplier = 40;
            else
                multiplier = 80;
        }
        break;
    case BALL_FAST:
        if ((*basestat_table)[catching->species].base_spd >= 100)
            multiplier = 40;
        break;
    case BALL_LOVE:
        {
            struct battle_participant* catcher = &battle_participants[bank_attacker];
            u16 species = catcher->species;
            if (species == catching->species)
            {
                u8 gender1 = gender_from_pid(species, catcher->pid);
                u8 gender2 = gender_from_pid(species, catching->pid);
                if (gender1 != 0xFF && gender2 != 0xFF && gender1 != gender2)
                    multiplier = 80;
            }
        }
        break;
    case BALL_QUICK:
        if (battle_trace.battle_turn_counter == 0)
            multiplier = 50; //JeremyZ
        break;
    case BALL_HEAVY:
        {
            u16 weight = get_height_or_weight(species_to_national_dex(catching->species), 1);
            s16 changed_rate = catchrate;
            if (weight < 1024) {changed_rate -= 20;}
            else if (weight < 2048) {}
            else if (weight < 3072) {changed_rate += 20;}
            else if (weight < 4096) {changed_rate += 30;}
            else {changed_rate += 40;}
			if (changed_rate < 1) //JeremyZ
				changed_rate = 1;
            if (changed_rate >= 0 && changed_rate <= 255) {catchrate = changed_rate;}
        }
        break;
    case BALL_LURE:
        if (new_battlestruct->various.fishing_battle)
            multiplier = 30;
        break;
    case BALL_DUSK:
        if (curr_mapheader.type == MAP_CAVE || time_check(NIGHT_FIRST_HOUR, NIGHT_LAST_HOUR)) //JeremyZ
            multiplier = 30;
        break;
    case BALL_MOON:
        {
            const struct evolution_sub* evo = GET_EVO_TABLE(catching->species);
            for (u8 i = 0; i < NUM_OF_EVOS; i++)
            {
                if (evo[i].method == 7 && evo[i].paramter == ITEM_MOONSTONE)
                {
                    multiplier = 40;
                    break;
                }
            }
        }
        break;
    case BALL_BEAST:
        if (is_poke_ultrabeast(catching->species))
            multiplier = 50;
		else 
			multiplier = 1;
        break;
    #endif // EXPANDED_POKEBALLS
    }
    u16 hp_max = catching->max_hp * 3;
    u32 formula = (catchrate * multiplier / 10) * (hp_max - catching->current_hp * 2) / hp_max;
    if (catching->status.flags.sleep || catching->status.flags.freeze)
        formula *= 2;
    else if (catching->status.int_status)
        formula = PERCENT_100(formula, 150);
    return 1048560 / Sqrt(Sqrt(16711680 / formula));
}
/*
bool get_or_set_master_ball_flag()
{
	if (getflag(DISABLE_BALL_MASTER_FLAG))
		return false;
	setflag(DISABLE_BALL_MASTER_FLAG);
	return true;
}
*/
void atkEF_ballthrow(void)
{
    if (battle_execution_buffer){return;}

    u8 catch_bank = bank_attacker ^ 1;
    if (!is_bank_present(catch_bank)) {catch_bank ^= 2;}

    bank_target = catch_bank;
    active_bank = bank_attacker;
    u8 ball_shakes;
    void* throw_bs;
    if (battle_flags.wally)
    {
        ball_shakes = 4;
        throw_bs = (void*)(0x082DBDCA); //wally bs script
    }
    else if (battle_flags.trainer || GET_CUSTOMFLAG(CANT_CATCH_FLAG))
    {
        ball_shakes = 5;
        throw_bs = &BS_BALL_BLOCK; //trainer blocked ball script
    }
    else
    {
        enum ball_index ball_no = itemID_to_ballID(last_used_item);
		
		 //calculate ball shakes
        u32 formula = calc_ball_formula(ball_no, &battle_participants[catch_bank]);
        ball_shakes = 0;
        while (rng() < formula && ball_shakes <= 3)
                ball_shakes++;
		
        if (ball_no == BALL_MASTER )
		{
			battle_trace.flags |= 2;
		}
        else if (last_used_item < 11)
        {
            u8* attempt = &battle_trace.catch_attempts[last_used_item];
            if (*attempt < 254)
                (*attempt)++;
        }
       
        u8* string_chooser = &battle_communication_struct.multistring_chooser;
        if (ball_no == BALL_MASTER || ball_shakes == 4) //catching successful
        {
            new_battlestruct->bank_affecting[bank_target].caught = 1;
            ball_shakes = 4;
            throw_bs = &capture_exp_bs; //script poke caught
            struct pokemon* poke = get_bank_poke_ptr(catch_bank);
            set_attributes(poke, ATTR_POKEBALL, &last_used_item);
            #if EXPANDED_POKEBALLS == true
            if (ball_no == BALL_FRIEND)
            {
                u8 happiness = 200;
                set_attributes(poke, ATTR_HAPPINESS, &happiness);
            }
            else if (ball_no == BALL_HEAL)
            {
                poke_restore_pp(poke);
                u32 value = 0;
                set_attributes(poke, ATTR_STATUS_AILMENT, &value);
                //value = get_attributes(poke, ATTR_TOTAL_HP, 0);
                set_attributes(poke, ATTR_CURRENT_HP, &poke->total_hp);
            }
            #endif // EXPANDED_POKEBALLS
            if (sp86_update_pokemon_quantity() == 6)
                *string_chooser = 0;
            else
                *string_chooser = 1;
        }
        else //fail :(
        {
            *string_chooser = ball_shakes;
            throw_bs = (void*)(0x082DBDD4); //script poke got away from poke ball
        }
    }
    prepare_ball_throw_anim(0, ball_shakes);
    mark_buffer_bank_for_execution(active_bank);
    battlescripts_curr_instruction = throw_bs;
}

void atkF1_setpoke_as_caught(void)
{
    struct pokemon* poke = get_bank_poke_ptr(bank_target);
    u16 species = (get_attributes(poke, ATTR_SPECIES, 0));
    if (is_poke_caught(species))
        battlescripts_curr_instruction = (void*)(read_word(battlescripts_curr_instruction + 1));
    else
    {
        update_seen_and_caught_pokemon(species_to_national_dex(species), 3, get_attributes(poke, ATTR_PID, 0));
        battlescripts_curr_instruction += 5;
    }
}

u8 partnerbattle_count_player_pokes(void)
{
    u8 count = 0;
    for (u8 i = 0; i < 3; i++)
    {
        if (is_poke_valid(&party_player[i]))
            count++;
    }
    return count;
}

void atkF0_copy_caught_poke(void)
{
    const struct pokemon* poke = get_bank_poke_ptr(bank_target);
    revert_form_change(0, battle_team_id_by_side[bank_target], get_bank_side(bank_target), poke);
    u8 ret;
    if ((battle_flags.player_ingame_partner || battle_flags.player_partner) && partnerbattle_count_player_pokes() >= 3) //its a partner battle, so add to pc
        ret = poke_add_to_pc(poke);
    else
        ret = generate_pokemon_data_for_player(poke);
	//define
    if (ret) //went to PC instead of party
    {
        strcpy_xFF_terminated_0(script_text_buffer1, get_box_name_ptr(get_variable_value(0x4036)));
        get_attributes(poke, ATTR_NAME, script_text_buffer2);
        u8* string_chooser = &battle_communication_struct.multistring_chooser;
        if (sp1E8_is_curr_box_full())
        {
            *string_chooser = 2;
            strcpy_xFF_terminated_0(script_text_buffer3, get_box_name_ptr(old_curr_full_box_id));
        }
        else
            *string_chooser = 0;
        if (getflag(0x8AB))
            (*string_chooser)++;
    }
    battle_trace.caught_species = get_attributes(poke, ATTR_SPECIES, 0);
    get_attributes(poke, ATTR_NAME, battle_trace.caught_name);
	pokemon_slot_purge(poke);
    battlescripts_curr_instruction++;
}

void atkF2_display_dex_info(void)
{
    if (fadescreen_info.is_fading){return;}
    u8* tracker = &battle_communication_struct.field0;
    switch (*tracker)
    {
    case 0: //fade screen
        fadescreen_related(-1, 0, 0, 0x10, 0);
        (*tracker)++;
        break;
    case 1: //prepare dex display
        {
            rboxes_free();
            struct battle_participant* target = &battle_participants[bank_target];
            tracker[1] = prepare_poke_dex_display(species_to_national_dex(target->species), target->otid, target->pid);
            (*tracker)++;
        }
        break;
    case 2: //change vblank to the battle one
        if (super.callback2 == battle_callback2 && !tasks[tracker[1]].id)
        {
            super.vblank_callback = battle_vblank;
            (*tracker)++;
        }
        break;
    case 3: //load battle elements
        sub_80356D0();
        load_battletextbox_and_elements();
        battle_BG3_X = 0x100;
        (*tracker)++;
        break;
    case 4: //fade to battle graphics
        if (!sub_8001AD4())
        {
            fadescreen_related(0xFFFF, 0, 0x10, 0, 0);
            gpu_sync_bg_show(0);
            gpu_sync_bg_show(3);
            (*tracker)++;
        }
        break;
    default: //increment battle script
        battlescripts_curr_instruction++;
    }
}

void battle_yesnorbox_move_cursor(u8* cursor)
{
    play_sound(5);
    sub_8056BAC(*cursor);
    *cursor ^= 1;
    sub_8056B74(*cursor);
}

void atkF3_nickname_caught_poke(void)
{
    if (fadescreen_info.is_fading){return;}
    u8* tracker = &battle_communication_struct.field0;
    struct pokemon* poke = get_bank_poke_ptr(bank_target);
    switch (*tracker)
    {
    case 0: //display yes no rbox
        sub_8056A3C(0x18, 8, 0x1D, 0xD, 0);
        battle_display_rbox(text_yesno_battle, 0xC);
        (*tracker)++;
        tracker[1] = 0;
        sub_8056B74(0);
        break;
    case 1: //handle buttons
        {
            struct button Button = super.pressed_buttons;
            if (Button.DOWN && tracker[1] == 0) //move down
                battle_yesnorbox_move_cursor(&tracker[1]);
            if (Button.UP && tracker[1] == 1) //move up
                battle_yesnorbox_move_cursor(&tracker[1]);
            if ((Button.A && tracker[1]) == 1 || Button.B) //no nicknaming poke
            {
                play_sound(5);
                *tracker = 4;
            }
            else if (Button.A && tracker[1] == 0) //nickname poke
            {
                play_sound(5);
                sub_80A2390(3); //fade screen
                (*tracker)++;
            }
        }
        break;
    case 2: //prepare string inserter
        {
            rboxes_free();
            u8* poke_nick = battle_stuff_ptr->caught_nick;
            get_attributes(poke, ATTR_NAME, poke_nick);
            u16 species = get_attributes(poke, ATTR_SPECIES, 0);
            u32 PiD = get_attributes(poke, ATTR_PID, 0);
            prepare_string_inserter(2, poke_nick, species, gender_from_pid(species, PiD), PiD, battle_callback2);
            (*tracker)++;
        }
        break;
    case 3: //set nick
        if (super.callback2 != battle_callback2) {break;}
        set_attributes(poke, ATTR_NAME, battle_stuff_ptr->caught_nick);
    SCRIPT_JUMP:
        battlescripts_curr_instruction = (void*)(read_word(battlescripts_curr_instruction + 1));
        break;
    case 4: //no nicknaming was done
        if (sp86_update_pokemon_quantity() == 6)
            battlescripts_curr_instruction += 5;
        else
            goto SCRIPT_JUMP;
        break;
    }
}

void oac_wild_poke_enters(struct object* obj)
{
    if (fadescreen_related(0x10000 << obj->private[0], 0, 0xA, 0xA, 0x2108))
    {
        obj_change_img_if_possible(obj, 0);
        obj->callback = oac_wild_poke_enters_move_right;
    }
}

void slide_healthbox(u8 bank)
{
    prepare_healthbox_sliding(bank);
    set_healthbox_visible(healthbox_obj_id_pbs[bank]);
}

void oac_wild_poke_enters_fade_to_normal(struct object* obj)
{
    if (obj->bitfield2 & 0x10)
    {
        u8 bank = obj->private[0];
        if (fadescreen_related(0x10000 << bank, 0, 0xA, 0, 0x2108))
        {
            //synchronize healthox sliding
            if (bank == 3)
            {
                slide_healthbox(bank);
                slide_healthbox(1);
            }
            else if (!WILD_DOUBLE_BATTLE)
                slide_healthbox(1);
            obj_change_img_if_possible(obj, 0);
            obj->callback = oac_wild_poke_animate_after_fading;
        }
    }
}
