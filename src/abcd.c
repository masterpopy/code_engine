#include "defines.h"

u8 get_item_effect(u8 bank, u8 check_negating_effects);
u32 get_battle_item_extra_param(u32 bank);
struct task* get_task(u8 taskID);
void* get_particle_pal(u16 ID);
void move_anim_task_delete(u8 taskID);
void change_animation_bank_attacker();
void change_animation_bank_target();


struct template rain_template = {
        0x27a6, 0x27a6, (struct sprite*) 0x852496c, (struct frame**) 0x8596BF8, 0, (struct rotscale_frame**) 0x85961a4,
        (void*) 0x810721d};
struct template eletric_template = {
        0x2711, 0x2711, (struct sprite*) 0x8524904, (struct frame**) 0x82ec69c, 0, (struct rotscale_frame**) 0x82ec6a8,
        (void*) 0x810a9dd};//0x810a9dd
struct template const template_SLUDGE_WAVE = {
        0x27a6, 0x27a6, (struct sprite*) 0x85249cc, (struct frame**) 0x82ec69c, 0, (struct rotscale_frame**) 0x82ec6a8,
        (void*) 0x810851d};
const u16 DRIVER_PALS[] = {0x7EEC, 0x1F, 0x7f75, 0x277f};
const struct coords8 v_creator_pos[] = {{-65, -35}, {23, -35}, {-65, 1}};

void rain_task(u8 taskID)
{
    u16* state_tracker = get_task(taskID)->private;
    if (*state_tracker == 0)
    {
        memcpy(state_tracker + 1, anim_arguments, 6);
        /**(state_tracker + 1) = anim_arguments[0];
        *(state_tracker + 2) = anim_arguments[1];
        *(state_tracker + 3) = anim_arguments[2];*/
    }
    (*state_tracker)++;
    if (task_0x82e7651(*state_tracker, *(state_tracker + 2)))
    {
        u16 x = task_0x82E7BE1(task_0x806f621(), 0xF0);
        u16 y = task_0x82E7BE1(task_0x806f621(), 0x50);
        struct template* template = &rain_template;
        if (anim_arguments[3] == 0x15)
            template = &eletric_template;
        template_instanciate_forward_search(template, x, y, 4);
    }
    if (*state_tracker == *(state_tracker + 3))
        move_anim_task_delete(taskID);
}

void AnimTask_HideShow_Sprite0(u8 bank)
{
    struct object* poke_obj = &objects[objID_pbs_moveanimations[bank]];
    poke_obj->private[7] = poke_obj->pos1.x;
    poke_obj->pos1.x = -64;
}


void AnimTask_HideShow_Sprite(u8 taskID)
{
    /*u8 objID = objID_pbs_moveanimations[animation_bank_target];
    struct object* poke_obj = &objects[objID];
    poke_obj->private[7] = poke_obj->pos1.x;
    poke_obj->pos1.x = -64;

    objID = objID_pbs_moveanimations[animation_bank_attacker];
    poke_obj = &objects[objID];
    poke_obj->private[7] = poke_obj->pos1.x;
    poke_obj->pos1.x = -64;*/
    AnimTask_HideShow_Sprite0(animation_bank_target);
    AnimTask_HideShow_Sprite0(animation_bank_attacker);
    move_anim_task_delete(taskID);
}

bool is_using_two_frame_anim(u16 species)
{
    return !(species == POKE_UNOWN || species == POKE_SPINDA || species == POKE_DEOXYS || species == POKE_CASTFORM ||
            species > POKE_SHAYMIN_LAND);
}


void* sub_0x8108ad4()//玩水
{
    return anim_arguments[0] == 0x14 ? (void*) &template_SLUDGE_WAVE : (void*) 0x8595268;
}

void STICKY_WEB_callback(struct object* obj)
{
    obj->pos1.x += (s16) anim_arguments[0];
    obj->pos1.y += (s16) anim_arguments[1];
    obj->callback = (void*) 0x811067d;
}


void Techno_Blast_change_pal(u8 taskID)
{
    u16 item_effect = get_battle_item_extra_param(animation_bank_attacker);
    if (get_item_effect(animation_bank_attacker, 1) == ITEM_EFFECT_DRIVES && item_effect <= 4)
    {
        u16* pal = get_particle_pal(0x27e4);
        pal[1] = DRIVER_PALS[item_effect - 1];
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

/*void change_animation_bank_target()
{
	u8* bank= &animation_bank_attacker;
	bank[1] = bank[0];
}

void change_animation_bank_attacker()
{
	u8* bank= &animation_bank_attacker;
	bank[0] = bank[1];
}*/


void foul_play_task(u8 taskID)
{
    get_task(taskID)->function = (void*) 0x8117755;
    change_animation_bank_attacker();
}


void coil_callback(struct object* self)
{
    self->callback = (void*) 0x81105b5;
    change_animation_bank_target();
}


void GEAR_GRIND_callback(struct object* obj)
{
    obj->pos1.x += (s16) anim_arguments[0];
    obj->pos1.y += (s16) anim_arguments[1];
    obj->callback = (void*) 0x815a1b1;
}

void v_creator_callback(struct object* self)
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
    if (arg >= 1 && arg <= 3)
    {
        self->pos_neg_center = v_creator_pos[arg - 1];
    }
    else
    {
        self->pos_neg_center.y = 1;
    }
    self->callback = (void*) 0x8109365;
}

bool can_change_stat(u8 bank, bool self_inflicted, u8 statchanger)
{
    battle_scripting.stat_changer = statchanger;
    return change_stats(bank, stat_get_bits_arg(self_inflicted, 0, 0), 0) == STAT_CHANGED;
}

const struct evolution_sub* GET_EVO_TABLE(u16 species)
{
    return (*evo_table)[species];
}

void __attribute__((long_call)) setflag(u32 flag);

void sub_82E1810(u32 a1)
{
    u16 flag = DISABLED_EXP_FLAG;
    if (a1)
        setflag(flag);
    else
        clearflag(flag);
}

u16 lowest_evo(u16 species)
{
    u16 count = 0;
    for (u16 lower_poke = 1; lower_poke < ALL_POKES; lower_poke++)
    {
        if (count > 6)
            break;
        const struct evolution_sub* evos = (*evo_table)[lower_poke];
        for (u8 j = 0; j < 5; j++)
        {
            const struct evolution_sub* evo = &evos[j];
            if (evo->poke == species && evo->method < 0xFA)
            {
                species = lower_poke;
                lower_poke = 1;
                count++;
                break;
            }
        }
    }
    return species;
}

/*
u8 __attribute__((long_call)) is_move_a_HM(u16 move);
u32 __attribute__((long_call)) check_TM_compatibility(u32 species, u16 move);
u32 __attribute__((long_call)) check_if_move_learnt(struct pokemon* species, u16 move);
u16 __attribute__((long_call)) script_read_halfword(void* ptr);

u8 tm_index(u16 move)
{
    static const u8 tms[] = {0xF, 0x13, 0x39, 0x46, 0x94, 0xF9, 0x7F};
    const u8 size = sizeof(tms);
    if (move == 0x123)
        return size;
    for (u8 i = 0; i < size; i++)
    {
        if (tms[i] == move)
            return i;
    }
    return 0xff;
}


bool check_attack(struct pokemon* poke, u16 sp, u16 move, u8 tm)
{
    if (tm != 0xFF)
    {
        return check_TM_compatibility(sp, tm + 99);
    }
    return check_if_move_learnt(poke, move);
}

bool check_attack_new(void* script)
{
    u16 move = script_read_halfword(script);
    u8 tm = tm_index(move);
    u8 i;
    for (i = 0; i < 6; i++)
    {
        struct pokemon* poke = &party_player[i];
        u16 sp = get_attributes(poke, ATTR_SPECIES, 0);
        if (!sp)
            break;
        if (!get_attributes(poke, ATTR_IS_EGG, 0) && check_attack(poke, sp, move, tm))
        {
            var_8004 = sp;
            break;
        }
    }
    var_800D_lastresult = i;
    return 0;
}*/
