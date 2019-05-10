#include "defines.h"


u8 get_bank_side(u8);
u8 get_bank_identity(u8);
extern u16 word_3005D30;

//new:
#pragma long_calls

extern void bbp_set_to7(u8);//send_trinaer_img
extern void bbp_set_to4(u8);//prepare_poke_img
extern u32 sub_806D4A4(u16);
extern void sub_806F01C(u32, u32, u32);
extern void sub_81A56B4();
extern u8 get_ability(u16, u8);


#pragma long_calls_off

/*
 * some record
 *
 *08032824:battle_routine_set
 * bbp_cmd:
 * 1d 1d 58 00,
 * 00 00 00 00,
 * 1,
 * 2e 00 58 00,
 * 7 7 7 7,
 * 4 4 4 4,
 * 10 0 0 4,
 * 2f,
 * 12 ff 58 00
 */

/*void bbp_send_trainer_img()
{
    if (battle_execution_buffer)
        return;
    active_bank = 0;
    do
    {
        struct battle_participant* bp = &battle_participants[active_bank];
        if (!battle_flags.safari || get_bank_side(active_bank))// safari
        {
            memcpy(bp, battle_bufferB[active_bank].args, 0x58*2);
            bp->type1 = basestat_table[bp->species]->type1;
            bp->type2 = basestat_table[bp->species]->type1;
            bp->ability_id = get_ability(bp->species, bp->ivs.ability_bit);
            *(battle_stuff_ptr->hp_on_switchout + 2 * get_bank_side(active_bank)) = bp->current_hp;
            memset(&bp->hp_buff, 6, 7);
            struct flags2 flags21 = {0};
            bp->status2 = flags21;
        }
        else
        {
            memset(bp, 0, 0x58*2);
        }
        if (!get_bank_identity(active_bank))
        {
            bbp_set_to7(0);
            mark_buffer_bank_for_execution(active_bank);
        }
        if (battle_flags.trainer)       // //trainer
        {
            if (get_bank_identity(active_bank) == 1)
            {
                bbp_set_to7(0);
                mark_buffer_bank_for_execution(active_bank);
            }
            if (get_bank_side(active_bank) == 1 && *(u32*) &battle_flags & 0x63F0902)
            {
                sub_806F01C(sub_806D4A4(bp->species), 2u, bp->pid);
            }
        }
        else if (get_bank_side(active_bank) == 1)
        {
            if (!*(u32*) &battle_flags & 0x63F0902)
            {
                sub_806F01C(sub_806D4A4(bp->species), 2u, bp->pid);
            }
            bbp_set_to4(0);
            mark_buffer_bank_for_execution(active_bank);
            word_3005D30 = get_attributes(&party_opponent[battle_team_id_by_side[active_bank]], ATTR_SPECIES, 0);
        }
        if (battle_flags.player_partner && (get_bank_identity(active_bank) >= 2))
        {
            bbp_set_to7(0);
            mark_buffer_bank_for_execution(active_bank);
        }
        if (battle_flags.multibattle && get_bank_identity(active_bank) == 3)
        {
            bbp_set_to7(0);
            mark_buffer_bank_for_execution(active_bank);
        }
        if (battle_flags.battle_arena)
            sub_81A56B4();
        ++active_bank;
    } while (active_bank < no_of_all_banks);

    battle_executed_routine = (void*) 0x803AF81;

}*/
void prep_string(u16 strID, u8 bank);

extern u8 bbp_for_banks[4];
extern void longcall battle_buffer_reset(u8,void*,u8);

void set_bank_cmd(u8 bank,u8 cmd){
    battle_bufferA[bank].command_id=cmd;
    mark_buffer_bank_for_execution(bank);
}

void bbo_new4(){
    if(battle_execution_buffer) return;
    set_bank_cmd(3,0x2f);
    battle_executed_routine = (void*) 0x803B3CC+1;
}

void bbo_new3(){
    if(battle_execution_buffer) return;
    battle_flags.double_battle = 1;
    absent_bank_flags |= BIT_GET(2);
    set_bank_cmd(3,4);
}


void bbo_new2(){
    if(!battle_execution_buffer){
        tasks_for_banks[3] = (void*) (0x0805F180|1);
        no_of_all_banks = 4;

        banks_by_side[3] = 3;
        battle_team_id_by_side[3] = 1;
        party_opponent[1] = party_opponent[0];
        set_bank_cmd(3,0);
        battle_executed_routine = bbo_new3;
    }
}

void bbo_new1(){
    //repoint sub_803B3CC
    //First printstring inbattle
    //set pokemon data
    //move pokemon and showpokemon
    if(battle_execution_buffer) return;
    prep_string(0,0);
    battle_executed_routine = bbo_new2;
}

