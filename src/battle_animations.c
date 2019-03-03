#include "defines.h"

u8 get_bank_side(u8 bank);
void move_anim_task_delete(u8 taskID);

struct task* get_task(u8 taskID)
{
    return &tasks[taskID];
}

void AnimTask_megaevo_swap_sprite(u8 taskID)
{
    struct task* curr_task = get_task(taskID);
    u8 objID = objID_pbs_moveanimations[animation_bank_attacker];
    struct object* poke_obj = &objects[objID];
    u16* state_tracker = &curr_task->private[10];
    switch (*state_tracker)
    {
        case 0: //hide sprite
            curr_task->private[11] = poke_obj->pos1.x;
            poke_obj->pos1.x = -64;
            (*state_tracker)++;
            break;
        case 1: //refresh graphics
            battle_anim_refresh_graphics_maybe(animation_bank_attacker, 1, objID);
            (*state_tracker)++;
            break;
        case 2: //add a task
            poke_obj->invisible = 0;
            u8 added_task_id = task_add(sub_80A4980, 5);
            curr_task->private[1] = added_task_id;
            tasks[added_task_id].private[0] = 0;
            tasks[added_task_id].private[2] = animation_bank_attacker;
            (*state_tracker)++;
            break;
        case 3: //wait for added task
            if (!task_is_running(curr_task->private[1]))
                (*state_tracker)++;
            break;
        default: //restore position, update altitude
            poke_obj->pos1.x = curr_task->private[11];
            poke_update_altitude(animation_bank_attacker, battle_participants[animation_bank_attacker].species);
            move_anim_task_delete(taskID);
            break;
    }
}

void AnimTask_animate_pokemon(u8 taskID) //argument is bank
{
    u8 bank = animation_bank_attacker;
    if (anim_arguments[0] == 1)
    { bank = animation_bank_target; }
    u16* first_call = get_task(taskID)->private;
    struct object* poke_obj = &objects[objID_pbs_moveanimations[bank]];
    if (*first_call == 0)
    {
        task_set_priv_u32(taskID, 2, (u32) poke_obj->callback);
        u16 species = battle_participants[bank].species;
        if (get_bank_side(bank))
            b_animate_opponent_poke(poke_obj, species, 0, 1);
        else
            b_animate_player_poke(poke_obj, species);
        *first_call = 1;
    } else
    {
        if (task_find_id_by_funcptr(task_do_poke_animation) == 0xFF &&
            task_find_id_by_funcptr(task_animate_poke_after_delay) == 0xFF)
        {
            poke_obj->callback = (void*) (task_get_priv_u32(taskID, 2));
            move_anim_task_delete(taskID);
        }
    }
}

void AnimTask_swapbanks(u8 taskID)
{
    u8 temp = animation_bank_attacker;
    animation_bank_attacker = animation_bank_target;
    animation_bank_target = temp;
    move_anim_task_delete(taskID);
}

void ANIMTASK_prepare_statargs(u8 taskID)
{
	if (new_battlestruct->various.dont_play_stat_anim)
	{ move_anim_task_delete(taskID); }
	else
	{
		u16 info = battle_graphics.graphics_data->anims_info->arg;
/*		anim_arguments[0] = (info & STAT_NEGATIVE); //bool goes down
		if ((anim_arguments[1] = (info & STAT_STATID)) == 7) { //colour ID
			new_battlestruct->various.dont_play_stat_anim = 1; //if the colour is gray, dont play anim later
		} */
		if ((anim_arguments[0] = (info & STAT_NEGATIVE))) { //bool goes down
			anim_arguments[1] = 7; //gray colour, if stat gose down
		} else {
			anim_arguments[1] = (info & STAT_STATID); //colour ID
		}
		anim_arguments[2] = 0;
		anim_arguments[3] = 0;
		anim_arguments[4] = (info & STAT_STAGES); //stages
		task_statchange_preparestruct(taskID);
	}

}

void AnimTask_target_attacks(u8 taskID)
{
    animation_bank_attacker = bank_target;
    animation_bank_target = bank_attacker;
    move_anim_task_delete(taskID);
}

void AnimTask_banks_to_partnerbanks(u8 taskID)
{
    animation_bank_attacker = bank_partner_atk;
    animation_bank_target = bank_partner_def;
    move_anim_task_delete(taskID);
}
