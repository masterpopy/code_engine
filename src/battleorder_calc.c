#include "defines.h"
#include "static_references.h"

u16 get_speed(u8 bank);
u8 percent_chance(u8 percent);
u8 hp_condition(u8 bank, u8 percent);
u8 get_item_effect(u8 bank, u8 check_negating_effects);
u8 has_ability_effect(u8 bank, u8 mold_breaker);

bool check_ability(u8 bank, u8 ability)
{
    if (has_ability_effect(bank, 0) && battle_participants[bank].ability_id == ability)
        return 1;
    return 0;
}

s8 get_priority(u16 move, u8 bank)
{
    s8 priority = move_table[move].priority;
    if (check_ability(bank, ABILITY_GALE_WINGS) && move_table[move].type == TYPE_FLYING && FULL_HP(bank))
        priority++;
    else if (check_ability(bank, ABILITY_PRANKSTER) && move_table[move].split == 2)
        priority++;
    else if (check_ability(bank, ABILITY_TRIAGE))
    {
        u8 scriptID = move_table[move].script_id;
        if (scriptID == 24 || scriptID == 25 || scriptID == 26 || scriptID == 29 || scriptID == 89 || scriptID == 124 || scriptID == 21) //damage drain, heal user, heal target, roost, dream eater, wish, lunar dance
            priority += 3;
    }
    return priority;
}

s8 get_bracket_alteration_factor(u8 bank, u8 item_effect) // will be used for quick claw message
{
    switch(item_effect)
    {
    case ITEM_EFFECT_QUICKCLAW:
        if(__umodsi3(battle_turn_random_no, 0x64) < get_item_quality(battle_participants[bank].held_item))
            return 1;
        break;
    case ITEM_EFFECT_CUSTAPBERRY:
        if(hp_condition(bank, 2))
            return 1;
        break;
    case ITEM_EFFECT_LAGGINGTAIL:
        return -1;
    }
    return 0;
}

u8 get_first_to_strike(u8 bank1, u8 bank2, u8 ignore_priority)
{
    u8 quash1=new_battlestruct->bank_affecting[bank1].quashed;
    u8 quash2=new_battlestruct->bank_affecting[bank2].quashed;
    u8 faster=2;

    if (quash1 && !quash2)
        faster=1;
    else if (!quash1 && quash2)
        faster=0;
    else if (!ignore_priority)
    {
        s8 priority1 = 0;
        s8 priority2 = 0;
        u16 move1 = battle_participants[bank1].moves[battle_stuff_ptr->chosen_move_position[bank1]];
        u16 move2 = battle_participants[bank2].moves[battle_stuff_ptr->chosen_move_position[bank2]];
        if(menu_choice_pbs[bank1]==0)
            priority1 = get_priority(move1, bank1);
        if(menu_choice_pbs[bank2]==0)
            priority2 = get_priority(move2, bank2);
        if (priority1 > priority2)
            faster=0;
        else if (priority2 > priority1)
            faster=1;
    }
    if(faster==2)
    {
        s8 bracket1=get_bracket_alteration_factor(bank1,get_item_effect(bank1,1));
        s8 bracket2=get_bracket_alteration_factor(bank2,get_item_effect(bank2,1));
        if (bracket1 > bracket2)
            faster=0;
        else if (bracket1 < bracket2)
            faster=1;
        else
            { //faster moves first unless trick room is active
                u8 stall1 = check_ability(bank1,ABILITY_STALL);
                u8 stall2 = check_ability(bank2,ABILITY_STALL);
                if(stall1 && !stall2)
                    faster=1;
                else if(stall2 && !stall1)
                    faster=0;
                else
                {
                    u16 speed1 = get_speed(bank1);
                    u16 speed2 = get_speed(bank2);
                    if (new_battlestruct->field_affecting.trick_room || (stall1 && stall2)) //swapping speeds will do the job
                    {
                        u16 placeholder = speed1;
                        speed1 = speed2;
                        speed2 = placeholder;
                    }
                    if (speed1 > speed2)
                        faster=0;
                    else if (speed2 > speed1)
                        faster=1;
                    else if(rng()&1)
                        faster=0;
                }
            }
    }
    return faster;
}
