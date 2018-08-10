#include "defines.h"


u8 get_item_effect(u8 bank, u8 check_negating_effects);
u32 get_battle_item_extra_param(u32 bank);
struct task* get_task(u8 taskID);
void* get_particle_pal(u16 ID);

enum drive_types
{
    DOUSE_DRIVE_EFFECT=1,
    BURN_DRIVE_EFFECT,
    CHILL_DRIVE_EFFECT,
    SHOCK_DRIVE_EFFECT
};

struct template rain_template = {0x27a6, 0x27a6, (struct sprite*)0x852496c, (struct frame **)0x8596BF8, 0,
				(struct rotscale_frame**) 0x85961a4, (void*)0x810721d};
struct template eletric_template = {0x2711, 0x2711, (struct sprite*)0x8524904, (struct frame **)0x82ec69c, 0,
				(struct rotscale_frame**) 0x82ec6a8, (void*)0x810a9dd};//0x810a9dd
				
void rain_task(u8 taskID)
{
	u16* state_tracker = get_task(taskID)->private;
    if (*state_tracker == 0)
    {
		*(state_tracker + 1) = anim_arguments[0];
		*(state_tracker + 2) = anim_arguments[1];
		*(state_tracker + 3) = anim_arguments[2];
	}
	(*state_tracker)++;
	if(task_0x82e7651(*state_tracker, *(state_tracker + 2)))
	{
		u16 x = task_0x82E7BE1(task_0x806f621(), 0xF0);
		u16 y = task_0x82E7BE1(task_0x806f621(), 0x50);
		struct template* template = &rain_template;
		if(anim_arguments[3] == 0x15)
			template = &eletric_template;
		template_instanciate_forward_search(template, x, y, 4);
	}
	if(*state_tracker == *(state_tracker + 3))
		move_anim_task_del(taskID);	
}

void move_anim_task_delete(u8 taskID)
{
	move_anim_task_del(taskID);
}


void AnimTask_HideShow_Sprite(u8 taskID)
{
    u8 objID = objID_pbs_moveanimations[animation_bank_target];
    struct object* poke_obj = &objects[objID];
    poke_obj->private[7] = poke_obj->pos1.x;
    poke_obj->pos1.x = -64;
	
	objID = objID_pbs_moveanimations[animation_bank_attacker];
    poke_obj = &objects[objID];
    poke_obj->private[7] = poke_obj->pos1.x;
    poke_obj->pos1.x = -64;
    
	move_anim_task_delete(taskID);
}

u16 is_using_two_frame_anim(u16 species)
{
    if (species == POKE_UNOWN || species == POKE_SPINDA || species == POKE_DEOXYS || species == POKE_CASTFORM || species > (POKE_ARCEUS - 1))
        return 0;
    return 1;
}

struct template const template_SLUDGE_WAVE = {0x27a6, 0x27a6, (struct sprite*)0x85249cc, (struct frame **)0x82ec69c, 0,
 (struct rotscale_frame**) 0x82ec6a8, (void*)0x810851d};

void* sub_0x8108ad4()//玩水
{
	if(anim_arguments[0] == 0x14)
		return (void*)&template_SLUDGE_WAVE;
	return (void*)0x8595268;
}

void  toxic_thread_task(u8 taskID)
{
	u16 particle_id = 0x27C3;
	u16* pal = get_particle_pal(particle_id);
	pal[4] = 0x7C1E;
	pal = get_particle_pal(particle_id + 1);
	pal[4] = 0x7C1E;
	move_anim_task_delete(taskID);
}

void STICKY_WEB_callback(struct object* obj)
{
	obj->pos1.x+=(s16)anim_arguments[0];
	obj->pos1.y+=(s16)anim_arguments[1];
	obj->callback=(void*)0x811067d;
}

u16 DRIVER_PALS[] = {0x7EEC, 0x1F, 0x7f75, 0x277f};

void Techno_Blast_change_pal(u8 taskID)
{
	u16 item_effect = get_battle_item_extra_param(animation_bank_attacker);
	if(get_item_effect(animation_bank_attacker, 1) == ITEM_EFFECT_DRIVES && item_effect <= 4)
    {
		u16* pal = get_particle_pal(0x27e4);
		pal += 1;
        *pal = DRIVER_PALS[item_effect - 1];
    }
	move_anim_task_delete(taskID);
}

void hex_task(u8 taskID)
{
	if (!battle_participants[animation_bank_target].status.int_status)
    {
		anim_arguments[7] = 5;
    }
    move_anim_task_delete(taskID);
}

void change_animation_bank_target()
{
	u8* bank= &animation_bank_attacker;
	*(bank+1)=*bank;
}

void change_animation_bank_attacker()
{
	u8* bank= &animation_bank_attacker;
	*bank=*(bank+1);
}


void foul_play_task(u8 taskID)
{
	get_task(taskID)->function=(void*)0x8117755;
	change_animation_bank_attacker();
}


void coil_callback(struct object *self)
{
	self->callback=(void*)0x81105b5;
	change_animation_bank_target();
}


void GEAR_GRIND_callback(struct object* obj)
{
	obj->pos1.x += (s16)anim_arguments[0];
	obj->pos1.y += (s16)anim_arguments[1];
	obj->callback=(void*)0x815a1b1;
}

const struct coords8 v_creator_pos[] = {{-65,-35},{23,-35},{-65,1}};
void v_creator_callback(struct object *self)
{
	/*switch(anim_arguments[5])
	{
		case 1:
			pos_neg_center->y = -35;
			pos_neg_center->x = -65;
			break;
		case 2:
			pos_neg_center->y = -35;
			pos_neg_center->x = 23;
			break;
		case 3:
			pos_neg_center->y = 1;
			pos_neg_center->x = -65;
			break;
		default:
			pos_neg_center->y = 1;
	}*/
	u16 arg = anim_arguments[5];
	if(arg >= 1 && arg <=3){
		self->pos_neg_center = v_creator_pos[arg - 1];
	}else{
		self->pos_neg_center.y = 1;
	}
	self->callback=(void*)0x8109365;
}

u8 stat_get_bits_arg(bool self_inflicted, bool print_ability, bool change_stats)
{
	u8 bits = 0;
	if (self_inflicted)
		bits |= STAT_SELFINFLICTED;
	if (print_ability)
		bits |= STAT_PRINTABILITY;
	if (change_stats)
		bits |= STAT_CHANGE_VALUES;
	return bits;
}

bool can_change_stat(u8 bank, bool self_inflicted, u8 statchanger)
{
	battle_scripting.stat_changer = statchanger;
	if (change_stats(bank, stat_get_bits_arg(self_inflicted, 0, 0), 0) == STAT_CHANGED)
		return 1;
	return 0;
}

const struct evolution_sub* GET_EVO_TABLE(u16 species){
	return (*evo_table)[species];
}

/*
void sub_8100128(u8 taskID)
{
  struct task* task = &tasks[taskID];
  u8 objid=task->private[2];
  struct object* obj = &objects[objid];
  u16 *tracker = &task->private[0];
  if ( *tracker == 7 )
  {
    obj->pos1.x +=obj->pos2.x;
    obj->pos1.y += obj->pos2.y;
    obj->pos2.x = 0;
    obj->pos2.y = 0;
    obj->private[0] = 10;
    obj->private[1] = obj->pos1.x;
    obj->private[2] = task->private[6];
    obj->private[3] = obj->pos1.y;
    obj->private[4] = task->private[7];
    obj->private[5] = sub_8100504(obj);
    task->private[4] += 2;
    task->private[3] = 4;
    obj->y_height_related = task->private[4] ;
    sub_80081A8(obj, task->private[3]);
    sub_80A68D4(obj);
    (*tracker)++;
  }
  if ( *tracker > 7 )
  {
    if ( *tracker == 11 )
    {
      obj->pos1.x += obj->pos2.x;
      obj->pos1.y += obj->pos2.y;
      obj->pos2.x= 0;
      obj->pos2.y = 0;
      obj->private[0] = 10;
      obj->private[1] = obj->pos1.x;
      obj->private[2] = task->private[8];
      obj->private[3] = obj->pos1.y;
      obj->private[4] = task->private[9];
      obj->private[5] = sub_8100504(obj);
      task->private[4] -= 2;
      task->private[3] = 6;
      obj->y_height_related= task->private[4];
      sub_80081A8(obj, task->private[3]);
      sub_80A68D4(obj);
      (*tracker)++;
    }
    if ( *tracker > 11 )
    {
      if ( *tracker == 13 )
      {
        if ( !task->private[12] )
          move_anim_task_del(taskID);
      }
      else if ( *tracker >= 13 )
      {
        if ( *tracker == 255 )
        {
          task->private[1]++;
          if (  task->private[1] > 5 )
          {
            task->private[1]= 0;
            *tracker = task->private[15];
          }
        }
      }
      else
      {
        sub_8100524(task, taskID);
        if ( sub_80A6900(obj))
        {
          obj_delete_and_free_tiles(obj);
          (*tracker)++;
        }
      }
    }
    else
    {
      if ( *tracker == 9 )
      {
        obj->pos1.x += obj->pos2.x;
        obj->pos1.y += obj->pos2.y;
        obj->pos2.x= 0;
        obj->pos2.y = 0;
        obj->private[0] = 10;
        obj->private[1] = obj->pos1.x;
        obj->private[2] = task->private[6] - task->private[5] * (task->private[10] / 2 + 10);
        obj->private[3] = obj->pos1.y;
        obj->private[4] = (task->private[11] / 2 + 10) * task->private[5] + task->private[7];
        obj->private[5] = sub_8100504(obj);
        task->private[3] = 5;
        obj->y_height_related= task->private[4];
        sub_80081A8(obj, task->private[3]);
        sub_80A68D4(obj);
        (*tracker)++;
      }
      if ( *tracker <= 9 )
      {
        sub_8100524(task, taskID);
        if ( sub_80A6900(obj))
        {
          task->private[15] = 9;
          *tracker = 255;
        }
      }
      else
      {
        sub_8100524(task, taskID);
        if ( sub_80A6900(obj))
        {
          task->private[15] = 11;
          *tracker = 255;
        }
      }
    }
  }
  else
  {
    if ( *tracker == 3 )
    {
      obj->pos1.x +=  obj->pos2.x;
      obj->pos1.y += obj->pos2.y;
      obj->pos2.x= 0;
      obj->pos2.y = 0;
      obj->private[0] = 10;
      obj->private[1] = obj->pos1.x;
      obj->private[2] = task->private[6] - task->private[5] * ((task->private[10] >> 1) + 10);
      obj->private[3] =  obj->pos1.y;
      obj->private[4] = task->private[7] - task->private[5] * ((task->private[11] >> 1) + 10);
      obj->private[5] = sub_8100504(obj);
      task->private[3] = 2;
      obj->y_height_related= task->private[4];
      sub_80081A8(obj, task->private[3]);
      sub_80A68D4(obj);
      (*tracker)++;
    }
    if ( *tracker > 3 )
    {
      if ( *tracker == 5 )
      {
        obj->pos1.x += obj->pos2.x;
        obj->pos1.y += obj->pos2.y;
        obj->pos2.x= 0;
        obj->pos2.y = 0;
        obj->private[0] = 10;
        obj->private[1] = obj->pos1.x;
        obj->private[2] = ((task->private[10] >> 1) + 10) * task->private[5] + task->private[6];
        obj->private[3] = obj->pos1.y;
        obj->private[4] = ((task->private[11] >> 1) + 10) * task->private[5] + task->private[7];
        obj->private[5] = sub_8100504(obj);
        task->private[4] -= 2;
        task->private[3] = 3;
        obj->y_height_related= task->private[4];
        sub_80081A8(obj, task->private[3]);
        sub_80A68D4(obj);
        (*tracker)++;
      }
      if ( *tracker < 5 )
      {
        sub_8100524(task, taskID);
        if ( sub_80A6900(obj))
        {
          task->private[15] = 5;
          *tracker = 255;
        }
      }
      else
      {
        sub_8100524(task, taskID);
        if ( sub_80A6900(obj))
        {
           task->private[15] = 7;
          *tracker = 255;
        }
      }
    }
    else
    {
      if ( *tracker == 1 )
      {
        obj->pos1.x += obj->pos2.x;
        obj->pos1.y += obj->pos2.y;
        obj->pos2.x = 0;
        obj->pos2.y = 0;
        obj->private[0] = 10;
        obj->private[1] = obj->pos1.x;
        obj->private[2] = task->private[6];
        obj->private[3] = obj->pos1.y;
        obj->private[4] = task->private[7];
        obj->private[5] = sub_8100504(obj);
        task->private[4] += 2;
        task->private[3] = 1;
        obj->y_height_related =  task->private[4];
        sub_80081A8(obj, task->private[3]);
        sub_80A68D4(obj);
        (*tracker)++;
      }
      if ( *tracker > 1 )
      {
        sub_8100524(task, taskID);
        if ( sub_80A6900(obj))
        {
          task->private[15] = 3;
          *tracker = 255;
        }
      }
      else if ( *tracker==0 )
      {
        sub_8100524(task, taskID);
        if ( sub_80A6900(obj))
        {
          task->private[15] = 1;
          *tracker = 255;
        }
      }
    }
  }
}*/
/*
extern u16 unknown_func(void*);
void sub_0x80FFFC0(u8 taskID)
{
	struct task* task=&tasks[taskID];
	task->private[4]=sub_80a82e4(animation_bank_target) - 1;
	task->private[6]=sub_80a5c6c(animation_bank_target, 2);
	task->private[7]=sub_80a5c6c(animation_bank_target, 3);
	task->private[10]=sub_80a861c(animation_bank_target, 1);
	task->private[11]=sub_80a861c(animation_bank_target, 0);
	if(sub_80a6a30(animation_bank_target))
		task->private[5] = 1;
    else 
		task->private[5] = (~1)+1;
	u16 k = (task->private[5] << 6) - 0x38;
	task->private[9] = k;
	task->private[8] = task->private[7] - k + task->private[6];
	
	u8 objid=template_instanciate_forward_search((void*)0x8592778, 
		task->private[8], task->private[9], task->private[4]);
	task->private[2]=objid;//0xC
	if(objid == 64)
		move_anim_task_del(taskID);
	struct object* obj =  &objects[objid];
	obj->anim_unkown_counter = 0xa;
	obj->private[1] = task->private[8];
	u16 r0 = unknown_func(&task->private);
	//u16 r0 = task->private[10];
	//r0 = ((r0 >> 0x1f) + r0) >> 1; // ???
	//r0 += 0xA;
	//r0 *= task->private[5];
	//r0 += task->private[7];
	obj->private[4]=r0;
	obj->private[5]=sub_8100504(obj);
	sub_80A68D4(obj);
	
	task->function=(void*)(sub_8100128+1);
}*/
/*
void sub_0x80FFFC0(struct task* task)
{
	if(anim_arguments[0] != 0x3f)
	{
		task->function=(void*)(0x8100129);
	}
	else
	{
		task->function=sub_8100128+1;
	}
}*/


