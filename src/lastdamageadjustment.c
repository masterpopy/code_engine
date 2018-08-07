#include "defines.h"
#include "static_references.h"

u8 get_all_item_quality(u8 bank);
bool find_move_in_table(u16 move, const u16* table_ptr);
void setup_berry_consume_buffers(u8 bank);
u8 get_item_effect(u8 bank, u8 check_negating_effects);
u8 has_ability_effect(u8 bank, u8 mold_breaker, u8 gastro);
bool check_ability(u8 bank, u8 ability);
void bs_push_current(void* now);
bool not_impostered(u8 bank); //JeremyZ
u32 random_value(u32 limit);

bool affected_by_substitute(u8 substitute_bank)
{
    if (battle_participants[substitute_bank].status2.substitute)
    {
        if (!(hitmarker & HITMARKER_IGNORE_SUBSTITUTE || disable_structs[substitute_bank].substitute_hp == 0
              || (check_ability(bank_attacker, ABILITY_INFILTRATOR) && bank_attacker != substitute_bank)
              || find_move_in_table(current_move, sound_moves)))
        {
            return true;
        }
    }
    return false;
}

void atk07_final_dmg_calc(void)
{
    if (battle_execution_buffer) {return;}
    battlescripts_curr_instruction++;

    if(battle_participants[bank_target].species == POKE_MIMIKYU && check_ability(bank_target,ABILITY_DISGUISE)
       && has_ability_effect(bank_target, 1, 1) && MOVE_WORKED && !affected_by_substitute(bank_target) && not_impostered(bank_target)) //JeremyZ
    {
        new_battlestruct->various.bust_mimikyu = 1;
        damage_loc = 0;
        move_outcome.super_effective = 0;
        move_outcome.not_very_effective = 0;
        move_outcome.one_hit_ko = 0;
    }
    else
    {
        if (new_battlestruct->various.berry_damage_redux)
        {
            u16 item = battle_participants[bank_target].held_item;
            new_battlestruct->various.berry_damage_redux = 0;
            if (MOVE_WORKED && DAMAGING_MOVE(current_move) && item)
            {
                battle_scripting.active_bank = bank_target;
                last_used_item = item;
                bs_push_current(BS_BERRY_DMG_REDUCE);
                setup_berry_consume_buffers(bank_target);
            }
        }
        damage_loc = ATLEAST_ONE(damage_loc);
        if (!affected_by_substitute(bank_target))
        {
            u16 target_hp = battle_participants[bank_target].current_hp;
            if (protect_structs[bank_target].flag0_endure && (damage_loc >= target_hp))
            {
                damage_loc = target_hp - 1;
                move_outcome.endured = 1;
            }
            else if ((current_move == MOVE_FALSE_SWIPE || current_move == MOVE_HOLD_BACK) && (damage_loc >= target_hp) && !(move_outcome.failed || move_outcome.missed || move_outcome.not_affected))
            {
                damage_loc = target_hp - 1;
            }
            else if (battle_participants[bank_target].ability_id == ABILITY_STURDY && has_ability_effect(bank_target, 1, 1) && (damage_loc >= target_hp) && target_hp == battle_participants[bank_target].max_hp)
            {
                damage_loc = target_hp - 1;
                move_outcome.sturdied = 1;
            }
            else
            {
                switch (get_item_effect(bank_target, 1))
                {
                case ITEM_EFFECT_FOCUSSASH:
                    if ((damage_loc >= target_hp) && target_hp == battle_participants[bank_target].max_hp)
                    {
                        damage_loc = target_hp - 1;
                        move_outcome.hanged_on_using_item = 1;
                        last_used_item = battle_participants[bank_target].held_item;
                        battle_participants[bank_target].held_item = 0;
                        active_bank = bank_target;
                        bb2_setattributes_in_battle(0, 2, 0, 2, &battle_participants[bank_target].held_item);
                        mark_buffer_bank_for_execution(bank_target);
                    }
                    break;
                case ITEM_EFFECT_FOCUSBAND:
                    if ((damage_loc >= target_hp) && (/*__umodsi3(rng(), 100)*/random_value(100) + 1) < get_all_item_quality(bank_target))
                    {
                        damage_loc = target_hp - 1;
                        move_outcome.hanged_on_using_item = 1;
                        last_used_item = battle_participants[bank_target].held_item;
                    }
                    break;
                }
            }
        }
    }
}
