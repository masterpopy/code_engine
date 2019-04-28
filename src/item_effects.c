#include "defines.h"
#include "static_references.h"

u8 cant_fall_asleep(u8 bank, u8 self_inflicted);
u8 cant_become_burned(u8 bank, u8 self_inflicted);
u8 cant_become_freezed(u8 bank, u8 self_inflicted);
u8 cant_become_paralyzed(u8 bank, u8 self_inflicted);
u8 cant_poison(u8 atk_bank, u8 def_bank, u8 self_inflicted);
bool check_ability(u8 bank, u8 ability);
u8 get_item_effect(u8 bank, bool check_negating_effects);
bool has_ability_effect(u8 bank, u8 mold_breaker);
bool is_bank_present(u32 bank);
bool percent_chance(u8 percent);
bool does_move_make_contact(u16 move, u8 atk_bank);
bool is_of_type(u8 bank, u8 type);
void copy_status_condition_text(u8 bank, u8 confusion);
u8 get_attacking_move_type(void);
void move_to_buff1(u16 move);
struct pokemon* get_bank_poke_ptr(u8 bank);
bool can_poke_be_switched_into(u8 index, u8 bank);
u8 check_field_for_ability(enum poke_abilities ability, u8 side_to_ignore, u8 mold);
u8 get_bank_side(u8 bank);
void bs_push(void* to_return, void* now);
void bs_push_current(void* now);
void call_bc_move_exec(void* bs_ptr);
u32 random_value(u32 limit);

enum COMMON_ITEM_EFFECT
{
    NO_ITEM_EFFECT,
    NO_COMMON_ITEM_EFFECT,
    ALTER_NON_VOLATILE_STATUS,
    PP_RESTORE_ITEM,
    HP_RESTORE_ITEM,
};

u8 get_item_effect(u8 bank, bool check_negating_effects)
{
    u16 held_item = battle_participants[bank].held_item;
    if (check_negating_effects)
    {
        if (check_ability(bank, ABILITY_KLUTZ) || new_battlestruct->field_affecting.magic_room || new_battlestruct->bank_affecting[bank].embargo)
            return ITEM_EFFECT_NOEFFECT;
        if (get_item_pocket_id(held_item)==4 && check_field_for_ability(ABILITY_UNNERVE, get_bank_side(bank), 0))
            return ITEM_EFFECT_NOEFFECT;
    }
    if (held_item == ITEM_ENIGMABERRY)
    {
        return enigma_berry_battle[bank].battle_effect_x12;
    }
    else
    {
        return get_item_battle_function(held_item);
    }
}

bool hp_condition(u8 bank, u8 percent) //1 = 50 %, 2 = 25 %
{
    struct battle_participant* ptr_to_struct = &battle_participants[bank];
    if (ptr_to_struct->ability_id == ABILITY_GLUTTONY && has_ability_effect(bank, 0) && percent > 1)
    {
        percent--;
        record_usage_of_ability(bank, ABILITY_GLUTTONY);
    }
    if (ptr_to_struct->current_hp && ptr_to_struct->current_hp <= (ptr_to_struct->max_hp >> percent))
        return 1;
    return 0;
}

void setup_berry_consume_buffers(u8 bank)
{
    new_battlestruct->bank_affecting[bank].eaten_berry = 1;
    u8 bit = BIT_GET(battle_team_id_by_side[bank]);
    if(!get_bank_side(bank))
        new_battlestruct->party_bit.eaten_berry_player |= bit;
    else
        new_battlestruct->party_bit.eaten_berry_opponent |= bit;
}



void call_based_on_mode2(enum call_mode calling_mode, void* BS_END2, void* BS_RET)
{
    if (calling_mode == BATTLE_TURN)
        call_bc_move_exec(BS_END2);
    else if (calling_mode == MOVE_TURN)
        bs_push_current(BS_RET);
}

void call_based_on_mode(enum call_mode calling_mode, void* BS_ptr)
{
    /*if (calling_mode == BATTLE_TURN)
        call_bc_move_exec(BS_ptr);
    else if (calling_mode == MOVE_TURN)
        bs_push_current(BS_ptr);*/
    call_based_on_mode2(calling_mode, BS_ptr, BS_ptr);
}

bool handle_leppa(u8 bank, u8 PP_to_restore, enum call_mode calling_mode, void* BS_END2, void* BS_RET)
{
    u16 chosen_move; u8 slot;
    struct battle_participant *Leppa = &battle_participants[bank];
    for (slot = 0; slot < 4; slot++)
    {
        chosen_move = Leppa->moves[slot];
        if (chosen_move && !Leppa->current_pp[slot])
        {
            //found a move with 0 pp, now calc the new amount to set
            u8 total_pp = calc_total_move_pp(chosen_move, get_attributes(get_bank_poke_ptr(bank), ATTR_PP_BONUS, 0), slot);
            if (total_pp < PP_to_restore)
                PP_to_restore = total_pp;

            move_to_buff1(chosen_move);

            call_based_on_mode2(calling_mode, BS_END2, BS_RET);

            active_bank = bank;
            bb2_setattributes_in_battle(0, REQUEST_PPMOVE1_BATTLE + slot, 0, 1, &PP_to_restore);
            mark_buffer_bank_for_execution(bank);

            if(!Leppa->status2.transformed && !(disable_structs[bank].truant_counter & 0x80))
                Leppa->current_pp[slot] = PP_to_restore;

            return 1;
        }
    }
    return 0;
}

u8 white_herb_effect(u8 bank, enum call_mode calling_mode)
{
    u8 effect = NO_ITEM_EFFECT;
    u8* stat = &battle_participants[bank].atk_buff;
    for (u8 i = 0; i < 7; i++)
    {
        if (*(stat + i) < 6)
        {
            *(stat + i) = 6;
            effect = NO_COMMON_ITEM_EFFECT;
        }
    }
    if (effect)
    {
        battle_scripting.active_bank = bank;
        active_bank = bank;
        bank_attacker = bank;
        call_based_on_mode2(calling_mode, (void*) 0x082DB7AE, (void*) 0x082DB7B4);
    }
    return effect;
}

u8 get_all_item_quality(u8 bank)
{
    if (battle_participants[bank].held_item == ITEM_ENIGMABERRY)
        return enigma_berry_battle[bank].quality;
    else
        return get_item_quality(battle_participants[bank].held_item);
}

u8 mental_herb_effect(u8 bank, enum call_mode calling_mode)
{
    u8 effect = NO_ITEM_EFFECT;
    if (disable_structs[bank].disable_timer || disable_structs[bank].encore_timer || disable_structs[bank].taunt_timer || battle_participants[bank].status2.tormented || battle_participants[bank].status2.in_love || new_battlestruct->bank_affecting[bank].heal_block)
    {
        effect = NO_COMMON_ITEM_EFFECT;
        call_based_on_mode2(calling_mode, BS_MENTALHERB_END2, BS_MENTALHERB);
        battle_scripting.active_bank = bank;
        active_bank = bank;
        bank_attacker = bank;
    }
    return effect;
}

bool stat_raise_berry(u8 bank, bool checkHP, u8 item_effect, enum call_mode calling_mode)
{
    bool effect = 0;
    if (!checkHP || hp_condition(bank, 2))
    {
        if (item_effect == ITEM_EFFECT_STARFBERRY)
        {
            u8 doable = 0;
            for (u8 i = 0; i < 5; i++)
            {
                if (can_change_stat(bank, 1, 0x21 + i))
                    doable |= BIT_GET(i);
            }
            while (doable)
            {
                u8 rand = random_value(5);
                if (doable & BIT_GET(rand))
                {
                    battle_scripting.stat_changer = 0x21 + rand;
                    effect = 1;
                    break;
                }
            }
        }
        else
        {
            u8 stat_to_raise = item_effect - ITEM_EFFECT_LIECHIBERRY + 1;
            battle_scripting.stat_changer = 0x10 + stat_to_raise;
            if (change_stats(bank, stat_get_bits_arg(1, 0, 0), 0) == STAT_CHANGED)
                effect = 1;
        }
        if (effect)
        {
            battle_scripting.active_bank = bank;
            call_based_on_mode2(calling_mode, BS_ITEMSTATRAISE_END2, BS_ITEMSTATRAISE);
        }
    }
    return effect;
}

bool item_try_stat_raise(u8 statchanger)
{
    u8 bank = battle_scripting.active_bank;
    battle_scripting.stat_changer = statchanger;
    if (is_bank_present(bank) && MOVE_WORKED && TARGET_TURN_DAMAGED && change_stats(bank, stat_get_bits_arg(1, 0, 0), battlescripts_curr_instruction) == STAT_CHANGED)
    {
        bs_push_current(BS_ITEMSTATRAISE);
        return 1;
    }
    return 0;
}

enum COMMON_ITEM_EFFECT berry_status_heal(u8 bank, u32 flags, enum call_mode calling_mode, void* BS_ptr)
{
    u32* status_flags = &battle_participants[bank].status.int_status;
    if (*status_flags & flags)
    {
        *status_flags = BIC(*status_flags, flags);
        call_based_on_mode(calling_mode, BS_ptr);
        return ALTER_NON_VOLATILE_STATUS;
    }
    return NO_ITEM_EFFECT;
}

enum COMMON_ITEM_EFFECT berry_HP_heal(u8 bank, bool checkHP, u32 HP, enum call_mode calling_mode, void* BS_ptr)
{
    if ((!checkHP || hp_condition(bank, 1)) && !new_battlestruct->bank_affecting[bank_target].heal_block)
    {
        damage_loc = ATLEAST_ONE(HP) * (-1);
        call_based_on_mode(calling_mode, BS_ptr);
        return HP_RESTORE_ITEM;
    }
    return NO_ITEM_EFFECT;
}

enum COMMON_ITEM_EFFECT berry_heal_confuse(u8 bank, bool checkHP, u8 item_effect, u8 quality, enum call_mode calling_mode, void* BS_HEALHP, void* BS_HEALCONFUSE)
{
    if ((!checkHP || hp_condition(bank, 2)) && !new_battlestruct->bank_affecting[bank].heal_block)
    {
        damage_loc = ATLEAST_ONE(battle_participants[bank].max_hp / quality) * (-1);
        if (get_poke_flavour_relation(battle_participants[bank].pid, item_effect - ITEM_EFFECT_FIGYBERRY) == FLAVOUR_DISLIKED)
            call_based_on_mode(calling_mode, BS_HEALCONFUSE);
        else
            call_based_on_mode(calling_mode, BS_HEALHP);

        battle_text_buff1[0] = 0xFD;
        battle_text_buff1[1] = 8;
        battle_text_buff1[2] = 1;
        battle_text_buff1[3] = 0xFF;

        return HP_RESTORE_ITEM;
    }
    return NO_ITEM_EFFECT;
}

enum COMMON_ITEM_EFFECT berry_handle_lansat(u8 bank, bool checkHP, enum call_mode calling_mode, void* BS_ptr)
{
    if ((!checkHP || hp_condition(bank, 2)) && !(battle_participants[bank].status2.focus_energy))
    {
        battle_participants[bank].status2.focus_energy = 1;
        call_based_on_mode(calling_mode, BS_ptr);
        return NO_COMMON_ITEM_EFFECT;
    }
    return NO_ITEM_EFFECT;
}
u32 random_value(u32 limit);
u8 get_random_to_switch(u8 bank)
{
    u32 to_switch = 0;
    for (u8 i = 0; i < 6; i++)
    {
        if (can_poke_be_switched_into(i, bank))
            to_switch |= BIT_GET(i);
    }
    if (!to_switch) {return 6;} //cant find anyone available to switch
    u8 to_ret;
    do
    {
        to_ret = /*__umodsi3(rng(), 6)*/random_value(6);
    } while (!(BIT_GET(to_ret) & to_switch));
    return to_ret;
}

u8 item_force_switching(u8 bank, void* BS_ptr)
{
    if (MOVE_WORKED && TARGET_TURN_DAMAGED && is_bank_present(bank) && multihit_counter <= 1)
    {
        u8 ID_toswitch = get_random_to_switch(bank);
        if (ID_toswitch != 6)
        {
            new_battlestruct->various.var1 = ID_toswitch;
            new_battlestruct->various.active_bank = bank;
            bs_push_current(BS_ptr);
            return NO_COMMON_ITEM_EFFECT;
        }
    }
    return 0;
}

u8 item_battle_effects(u8 switchid, u8 bank, u8 move_turn)
{
    u8 item_effect = get_item_effect(bank, 1);
    u8 effect = NO_ITEM_EFFECT;

    u8 quality = get_all_item_quality(bank);
    switch (switchid)
    {
    case 0: //switch in items
        switch (item_effect)
        {
        case ITEM_EFFECT_AMULETCOIN:
            {
                u8* money_multiplier = &battle_stuff_ptr->money_multiplier;
                if (!get_bank_side(bank) && *money_multiplier != 2)
                {
                    *money_multiplier = 2;
                    effect = NO_COMMON_ITEM_EFFECT;
                }
            }
            break;
        case ITEM_EFFECT_WHITEHERB:
            effect = white_herb_effect(bank, BATTLE_TURN);
            break;
        case ITEM_EFFECT_AIRBALLOON:
            if (!new_battlestruct->field_affecting.gravity)
            {
                effect = NO_COMMON_ITEM_EFFECT;
                new_battlestruct->various.active_bank = bank;
                call_bc_move_exec(BS_AIRBALLOON_SWITCHIN);
                record_usage_of_item(bank, ITEM_EFFECT_AIRBALLOON);
            }
            break;
		case ITEM_EFFECT_ELECTRICSEED:
			if(new_battlestruct->field_affecting.electic_terrain)
				effect = item_try_stat_raise(0x12);
            break;
				
		case ITEM_EFFECT_GRASSYSEED:
			if(new_battlestruct->field_affecting.grassy_terrain)
				effect = item_try_stat_raise(0x12);
            break;
		case ITEM_EFFECT_MISTYSEED:
			if(new_battlestruct->field_affecting.misty_terrain)
				effect = item_try_stat_raise(0x15);
            break;
				
		case ITEM_EFFECT_PSYCHICSEED:
			if(new_battlestruct->field_affecting.psychic_terrain)
				effect = item_try_stat_raise(0x15);
            break;
        }
        break;
    case 1: //battle end turn
        switch (item_effect)
        {
        case ITEM_EFFECT_ORANBERRY:
            if (!move_turn)
                effect = berry_HP_heal(bank, 1, quality, BATTLE_TURN, (void*) 0x082DB7C4);
            break;
        case ITEM_EFFECT_SITRUSBERRY:
            if (!move_turn)
                effect = berry_HP_heal(bank, 1, get_1_4_of_max_hp(bank), BATTLE_TURN, (void*) 0x082DB7C4);
            break;
        case ITEM_EFFECT_CHERIBERRY:
            effect = berry_status_heal(bank, STATUS_PARALYSIS, BATTLE_TURN, (void*) 0x082DB706);
            break;
        case ITEM_EFFECT_CHESTOBERRY:
            effect = berry_status_heal(bank, STATUS_SLEEP, BATTLE_TURN, (void*) 0x082DB766);
            break;
        case ITEM_EFFECT_PECHABERRY:
            effect = berry_status_heal(bank, STATUS_POISON | STATUS_TOXIC_POISON, BATTLE_TURN, (void*) 0x082DB71E);
            break;
        case ITEM_EFFECT_RAWSTBERRY:
            effect = berry_status_heal(bank, STATUS_BURN, BATTLE_TURN, (void*) 0x082DB736);
            break;
        case ITEM_EFFECT_ASPEARBERRY:
            effect = berry_status_heal(bank, STATUS_FREEZE, BATTLE_TURN, (void*) 0x082DB74E);
            break;
        case ITEM_EFFECT_LEPPABERRY:
            if(!move_turn)
                effect = handle_leppa(bank, quality, BATTLE_TURN, BS_LEPPABERRY_REMOVEITEM_END2, 0);
            break;
        case ITEM_EFFECT_PERSIMBERRY:
            if (battle_participants[bank].status2.confusion)
            {
                battle_participants[bank].status2.confusion = 0;
                effect = NO_COMMON_ITEM_EFFECT;
                call_bc_move_exec((void*)0x82DB77E);
            }
            break;
        case ITEM_EFFECT_LUMBERRY:
            if (battle_participants[bank].status.int_status || battle_participants[bank].status2.confusion)
            {
                copy_status_condition_text(bank, 1);
                battle_participants[bank].status2.confusion = 0;
                battle_participants[bank].status.int_status = 0;
                effect = ALTER_NON_VOLATILE_STATUS;
                call_bc_move_exec((void*)0x082DB794);
            }
            break;
        case ITEM_EFFECT_FIGYBERRY:
        case ITEM_EFFECT_WIKIBERRY:
        case ITEM_EFFECT_MAGOBERRY:
        case ITEM_EFFECT_AGUAVBERRY:
        case ITEM_EFFECT_IAPAPABERRY:
            effect = berry_heal_confuse(bank, 1, item_effect, quality, BATTLE_TURN, (void*) 0x082DB7C4, BS_HEALCONFUSE_BERRY_REMOVEITEM_END2);
            break;
        case ITEM_EFFECT_LIECHIBERRY:
        case ITEM_EFFECT_GANLONBERRY:
        case ITEM_EFFECT_SALACBERRY:
        case ITEM_EFFECT_PETAYABERRY:
        case ITEM_EFFECT_APICOTBERRY:
        case ITEM_EFFECT_STARFBERRY:
            effect = stat_raise_berry(bank, 1, item_effect, BATTLE_TURN);
            break;
        case ITEM_EFFECT_LANSATBERRY:
            effect = berry_handle_lansat(bank, 1, BATTLE_TURN, (void*)0x82DB869);
            break;
        case ITEM_EFFECT_WHITEHERB:
            effect = white_herb_effect(bank, BATTLE_TURN);
            break;
        case ITEM_EFFECT_MENTALHERB:
            effect = mental_herb_effect(bank, BATTLE_TURN);
            break;
        case ITEM_EFFECT_STICKYBARB:
            STICKYBARB:
            if (battle_participants[bank].current_hp && !move_turn && !(has_ability_effect(bank, 0) && battle_participants[bank].ability_id == ABILITY_MAGIC_GUARD))
            {
                effect = NO_COMMON_ITEM_EFFECT;
                damage_loc = get_1_8_of_max_hp(bank);
                call_bc_move_exec(BS_STICKYBARB);
                record_usage_of_item(bank, item_effect);
            }
            break;
        case ITEM_EFFECT_BLACKSLUDGE:
            if (!is_of_type(bank, TYPE_POISON))
                goto STICKYBARB;
        case ITEM_EFFECT_LEFTOVERS:
            if (battle_participants[bank].max_hp != battle_participants[bank].current_hp && battle_participants[bank].current_hp && !move_turn && !new_battlestruct->bank_affecting[bank_target].heal_block)
            {
                effect = HP_RESTORE_ITEM;
                damage_loc = get_1_16_of_max_hp(bank) * (-1);
                call_bc_move_exec((void*)0x082DB7F1);
                record_usage_of_item(bank, item_effect);
            }
            break;
        }
        if(effect)
        {
            active_bank = bank;
            battle_scripting.active_bank = bank;
            bank_attacker = bank;
        }
        break;
    case 2: //having effect on target items
        active_bank = bank;
        battle_scripting.active_bank = bank;
        u8 move_type = get_attacking_move_type();
        switch (item_effect)
        {
        case ITEM_EFFECT_WEAKNESSPOLICY:
            if (MOVE_WORKED && TARGET_TURN_DAMAGED && move_outcome.super_effective && battle_participants[bank].current_hp
                && (can_change_stat(bank, 1, 0x21) || can_change_stat(bank, 1, 0x24)))
            {
                effect = NO_COMMON_ITEM_EFFECT;
                bs_push_current(BS_WEAKNESSPOLICY);
            }
            break;
        case ITEM_EFFECT_ROCKYHELMET:
            if (does_move_make_contact(current_move, bank_attacker) && (MOVE_WORKED && TARGET_TURN_DAMAGED)
                 && !(battle_participants[bank_attacker].status2.substitute) && battle_participants[bank_attacker].current_hp)
            {
                damage_loc = ATLEAST_ONE(battle_participants[bank_attacker].max_hp / 6);
                effect = NO_COMMON_ITEM_EFFECT;
                bs_push_current(BS_ROCKYHELMET);
                record_usage_of_item(bank, ITEM_EFFECT_ROCKYHELMET);
            }
            break;
        case ITEM_EFFECT_STICKYBARB:
            if (does_move_make_contact(current_move, bank_attacker) && (MOVE_WORKED && TARGET_TURN_DAMAGED) && !(battle_participants[bank_attacker].status2.substitute) && battle_participants[bank_attacker].current_hp && battle_participants[bank_attacker].held_item == 0)
            {
                effect = NO_COMMON_ITEM_EFFECT;
                u16* target_item = &battle_participants[bank].held_item;
                u16* attacker_item = &battle_participants[bank_attacker].held_item;
                *attacker_item = *target_item;
                *target_item = 0;
                active_bank = bank;
                bb2_setattributes_in_battle(0, REQUEST_HELDITEM_BATTLE, 0, 2, target_item);
                mark_buffer_bank_for_execution(bank);
                active_bank = bank_attacker;
                bb2_setattributes_in_battle(0, REQUEST_HELDITEM_BATTLE, 0, 2, attacker_item);
                mark_buffer_bank_for_execution(active_bank);
                bs_push_current(&stickybarbswap);
                bank = bank_attacker;
            }
            break;
        case ITEM_EFFECT_AIRBALLOON:
            if (MOVE_WORKED && TARGET_TURN_DAMAGED)
            {
                effect = NO_COMMON_ITEM_EFFECT;
                bs_push_current(BS_AIRBALLOON_POPS);
            }
            break;
        case ITEM_EFFECT_DESTINYKNOT:
            if ((battle_participants[bank].status2.in_love & BIT_GET(bank_attacker)) && battle_participants[bank].current_hp && !check_ability(bank_attacker, ABILITY_OBLIVIOUS))
            {
                if (!(battle_participants[bank_attacker].status2.in_love & BIT_GET(bank)))
                {
                    battle_participants[bank_attacker].status2.in_love |= BIT_GET(bank);
                    effect = NO_COMMON_ITEM_EFFECT;
                    bs_push_current(BS_DESTINYKNOT);
                }
            }
            break;
        case ITEM_EFFECT_LUMINOUSMOSS:
            if (move_type == TYPE_WATER)
                effect = item_try_stat_raise(0x15);
            break;
        case ITEM_EFFECT_CELLBATTERY:
            if (move_type == TYPE_ELECTRIC)
                effect = item_try_stat_raise(0x11);
            break;
        case ITEM_EFFECT_SNOWBALL:
            if (move_type == TYPE_ICE)
                effect = item_try_stat_raise(0x11);
            break;
        case ITEM_EFFECT_ABSORBBULB:
            if (move_type == TYPE_WATER)
                effect = item_try_stat_raise(0x14);
            break;
        }
        break;
    case 3: //move turn
        for (u8 i = 0; i < no_of_all_banks; i++)
        {
            item_effect = get_item_effect(i, 1);
            quality = get_all_item_quality(i);
            last_used_item = battle_participants[i].held_item;
            bank = i;
            switch (item_effect)
            {
            case ITEM_EFFECT_ORANBERRY:
                if (!move_turn)
                    effect = berry_HP_heal(bank, 1, quality, MOVE_TURN, BS_BERRYHPHEAL_REMOVEITEM);
                break;
            case ITEM_EFFECT_SITRUSBERRY:
                if (!move_turn)
                    effect = berry_HP_heal(bank, 1, get_1_4_of_max_hp(bank), MOVE_TURN, BS_BERRYHPHEAL_REMOVEITEM);
                break;
            case ITEM_EFFECT_CHERIBERRY:
                effect = berry_status_heal(bank, STATUS_PARALYSIS, MOVE_TURN, (void*) 0x82DB70C);
                break;
            case ITEM_EFFECT_CHESTOBERRY:
                effect = berry_status_heal(bank, STATUS_SLEEP, MOVE_TURN, (void*) 0x82DB76C);
                break;
            case ITEM_EFFECT_PECHABERRY:
                effect = berry_status_heal(bank, STATUS_POISON | STATUS_TOXIC_POISON, MOVE_TURN, (void*) 0x82DB724);
                break;
            case ITEM_EFFECT_RAWSTBERRY:
                effect = berry_status_heal(bank, STATUS_BURN, MOVE_TURN, (void*) 0x82DB73C);
                break;
            case ITEM_EFFECT_ASPEARBERRY:
                effect = berry_status_heal(bank, STATUS_FREEZE, MOVE_TURN, (void*) 0x82DB754);
                break;
            case ITEM_EFFECT_PERSIMBERRY:
                if (battle_participants[bank].status2.confusion)
                {
                    battle_participants[bank].status2.confusion = 0;
                    effect = NO_COMMON_ITEM_EFFECT;
                    bs_push_current((void*) 0x82DB784);
                }
                break;
            case ITEM_EFFECT_LUMBERRY:
                if (battle_participants[bank].status.int_status || battle_participants[bank].status2.confusion)
                {
                    copy_status_condition_text(bank, 1);
                    battle_participants[bank].status2.confusion = 0;
                    battle_participants[bank].status.int_status = 0;
                    effect = ALTER_NON_VOLATILE_STATUS;
                    bs_push_current((void*) 0x82DB79A);
                }
                break;
            case ITEM_EFFECT_LEPPABERRY:
                if (multihit_counter <= 1)
                    effect = handle_leppa(bank, quality, MOVE_TURN, 0, BS_LEPPABERRY_REMOVEITEM);
                break;
            case ITEM_EFFECT_FIGYBERRY:
            case ITEM_EFFECT_WIKIBERRY:
            case ITEM_EFFECT_MAGOBERRY:
            case ITEM_EFFECT_AGUAVBERRY:
            case ITEM_EFFECT_IAPAPABERRY:
                effect = berry_heal_confuse(bank, 1, item_effect, quality, MOVE_TURN, BS_BERRYHPHEAL_REMOVEITEM, BS_HEALCONFUSE_BERRY_REMOVEITEM);
                break;
            case ITEM_EFFECT_LIECHIBERRY:
            case ITEM_EFFECT_GANLONBERRY:
            case ITEM_EFFECT_SALACBERRY:
            case ITEM_EFFECT_PETAYABERRY:
            case ITEM_EFFECT_APICOTBERRY:
            case ITEM_EFFECT_STARFBERRY:
                effect = stat_raise_berry(i, 1, item_effect, MOVE_TURN);
                break;
            case ITEM_EFFECT_LANSATBERRY:
                effect = berry_handle_lansat(bank, 1, MOVE_TURN, BS_LANSATBERRY_REMOVEITEM);
                break;
            case ITEM_EFFECT_WHITEHERB:
                effect = white_herb_effect(bank, MOVE_TURN);
                break;
            case ITEM_EFFECT_MENTALHERB:
                effect = mental_herb_effect(bank, MOVE_TURN);
                break;
            }
            if (effect)
            {
                bank_attacker = bank;
                active_bank = bank;
                another_active_bank = bank;
                battle_scripting.active_bank = bank;
                break;
            }
        }
        break;
    case 4:
        {
            quality = get_all_item_quality(bank_attacker);
            item_effect = get_item_effect(bank_attacker, 1);
            switch (item_effect)
            {
            case ITEM_EFFECT_KINGSROCK:
                if (MOVE_WORKED && special_statuses[bank_target].moveturn_losthp && percent_chance(quality) && move_table[current_move].move_flags.flags.affected_by_kingsrock)
                {
                    battle_participants[bank_target].status2.flinched = 1;
                    record_usage_of_item(bank_attacker, ITEM_EFFECT_KINGSROCK);
                }
                break;
            case ITEM_EFFECT_SHELLBELL:
                if (MOVE_WORKED && special_statuses[bank_target].moveturn_losthp && special_statuses[bank_target].moveturn_losthp != 0xFFFF && bank_target != bank_attacker
                    && battle_participants[bank_attacker].current_hp && battle_participants[bank_attacker].current_hp <= battle_participants[bank_attacker].max_hp &&
                    !new_battlestruct->bank_affecting[bank_target].heal_block)
                {
                    new_battlestruct->various.accumulated_damage += special_statuses[bank_target].moveturn_losthp;
                    special_statuses[bank_target].moveturn_losthp = 0;
                }
                break;
            case ITEM_EFFECT_LIFEORB:
                if (MOVE_WORKED && special_statuses[bank_target].moveturn_losthp && special_statuses[bank_target].moveturn_losthp != 0xFFFF &&
                     bank_target != bank_attacker)
                {
                    new_battlestruct->various.life_orbed = 1;
                }
                break;
            }
        }
        break;
    case 5: //toxic and flame orb
        if(battle_participants[bank].current_hp)
        {
            switch (item_effect)
            {
            case ITEM_EFFECT_FLAMEORB:
                if (!cant_become_burned(bank, 1))
                {
                    effect = ALTER_NON_VOLATILE_STATUS;
                    battle_participants[bank].status.flags.burn = 1;
                    call_bc_move_exec(BS_FLAMEORB);
                    record_usage_of_item(bank, ITEM_EFFECT_FLAMEORB);
                }
                break;
            case ITEM_EFFECT_TOXICORB:
                if (!cant_poison(bank, bank, 1))
                {
                    effect = ALTER_NON_VOLATILE_STATUS;
                    battle_participants[bank].status.flags.toxic_poison = 1;
                    call_bc_move_exec(BS_TOXICORB);
                    record_usage_of_item(bank, ITEM_EFFECT_TOXICORB);
                }
                break;
            }
        }
        break;
    case 6: //red card and eject button
        battle_scripting.active_bank = bank;
        switch (item_effect)
        {
        case ITEM_EFFECT_REDCARD:
            effect = item_force_switching(bank_attacker, BS_REDCARD_SWITCH);
            break;
        case ITEM_EFFECT_EJECTBUTTON:
            effect = item_force_switching(bank_target, BS_EJECTBUTTON_SWITCH);
            break;
        }
        break;
    }
    if (effect)
    {
        u16 item = battle_participants[bank].held_item;
        last_used_item = item;
        if (get_item_pocket_id(item) == 4)
            setup_berry_consume_buffers(bank);
        if (effect == ALTER_NON_VOLATILE_STATUS)
        {
            active_bank = bank;
            bb2_setattributes_in_battle(0, 0x28, 0, 4, &battle_participants[bank].status.flags);
            mark_buffer_bank_for_execution(bank);
        }
        else if (effect == HP_RESTORE_ITEM)
            new_battlestruct->bank_affecting[bank].itemheal = 1;
    }
    return effect;
}

u8 stat_raise_berry_bug_bite(u8 bank, u8 item_effect)
{
    if (stat_raise_berry(bank, 0, item_effect, 0xFF))
    {
        bs_push_current(BS_BUGBITE_STATRAISE);
        return 2;
    }
    return 0;
}

void bugbite_get_berry_effect(void)
{
    u8 bank = bank_attacker;
    battle_scripting.active_bank = bank;
    u8 effect = 0;
    u8 item_effect = get_item_battle_function(last_used_item);
    u8 quality = get_item_quality(last_used_item);
    copy_status_condition_text(bank, 1); //for berries that heal status conditions
    switch (item_effect)
    {
    case ITEM_EFFECT_ORANBERRY:
        if (!FULL_HP(bank))
            effect = berry_HP_heal(bank, 0, quality, MOVE_TURN, BS_BERRYHPHEAL);
        break;
    case ITEM_EFFECT_SITRUSBERRY:
        if (!FULL_HP(bank))
            effect = berry_HP_heal(bank, 0, get_1_4_of_max_hp(bank), MOVE_TURN, BS_BERRYHPHEAL);
        break;
    case ITEM_EFFECT_CHERIBERRY:
        effect = berry_status_heal(bank, STATUS_PARALYSIS, MOVE_TURN, BS_BUGBITE_HEALCONDITION);
        break;
    case ITEM_EFFECT_CHESTOBERRY:
        effect = berry_status_heal(bank, STATUS_SLEEP, MOVE_TURN, BS_BUGBITE_HEALCONDITION);
        break;
    case ITEM_EFFECT_PECHABERRY:
        effect = berry_status_heal(bank, STATUS_POISON | STATUS_TOXIC_POISON, MOVE_TURN, BS_BUGBITE_HEALCONDITION);
        break;
    case ITEM_EFFECT_RAWSTBERRY:
        effect = berry_status_heal(bank, STATUS_BURN, MOVE_TURN, BS_BUGBITE_HEALCONDITION);
        break;
    case ITEM_EFFECT_ASPEARBERRY:
        effect = berry_status_heal(bank, STATUS_FREEZE, MOVE_TURN, BS_BUGBITE_HEALCONDITION);
        break;
    case ITEM_EFFECT_PERSIMBERRY:
        if (battle_participants[bank].status2.confusion)
        {
            battle_participants[bank].status2.confusion = 0;
            effect = NO_COMMON_ITEM_EFFECT;
            bs_push_current(BS_BUGBITE_PERSIMBERRY);
        }
        break;
    case ITEM_EFFECT_LUMBERRY:
        if (battle_participants[bank].status.int_status || battle_participants[bank].status2.confusion)
        {
            battle_participants[bank].status2.confusion = 0;
            battle_participants[bank].status.int_status = 0;
            effect = ALTER_NON_VOLATILE_STATUS;
            bs_push_current(BS_BUGBITE_HEALCONDITION);
        }
        break;
    case ITEM_EFFECT_LEPPABERRY:
        effect = handle_leppa(bank, quality, MOVE_TURN, 0, BS_LEPPABERRY);
        break;
    case ITEM_EFFECT_FIGYBERRY:
    case ITEM_EFFECT_WIKIBERRY:
    case ITEM_EFFECT_MAGOBERRY:
    case ITEM_EFFECT_AGUAVBERRY:
    case ITEM_EFFECT_IAPAPABERRY:
        effect = berry_heal_confuse(bank, 0, item_effect, quality, MOVE_TURN, BS_BERRYHPHEAL, BS_HEALCONFUSE_BERRY);
        break;
    case ITEM_EFFECT_LIECHIBERRY:
    case ITEM_EFFECT_GANLONBERRY:
    case ITEM_EFFECT_SALACBERRY:
    case ITEM_EFFECT_PETAYABERRY:
    case ITEM_EFFECT_APICOTBERRY:
    case ITEM_EFFECT_STARFBERRY:
        effect = stat_raise_berry_bug_bite(bank, item_effect);
        break;
    case ITEM_EFFECT_LANSATBERRY:
        effect = berry_handle_lansat(bank, 0, MOVE_TURN, BS_LANSATBERRY);
        break;
    }
    if (effect == ALTER_NON_VOLATILE_STATUS)
    {
        active_bank = bank;
        bb2_setattributes_in_battle(0, REQUEST_STATUS_BATTLE, 0, 4, &battle_participants[bank].status);
        mark_buffer_bank_for_execution(bank);
    }
    setup_berry_consume_buffers(bank);
}

bool berry_eaten(u8 bank, bool from_remove_item)
{
    bool cheek_pouch = 0;
    if (new_battlestruct->bank_affecting[bank].eaten_berry)
    {
        new_battlestruct->bank_affecting[bank].eaten_berry = 0;
        if (check_ability(bank, ABILITY_CHEEK_POUCH) && !FULL_HP(bank))
        {
            cheek_pouch = 1;
            new_battlestruct->bank_affecting[bank].itemheal = 1;
            damage_loc = ATLEAST_ONE(battle_participants[bank].max_hp / 3) * -1;

            if(from_remove_item)
            {
                battlescripts_curr_instruction -=2;
            }
            bs_push_current(BS_CHEEKPOUCH);
            battle_scripting.active_bank = bank;

            record_usage_of_ability(bank, ABILITY_CHEEK_POUCH);
        }
    }
    return cheek_pouch;
}
