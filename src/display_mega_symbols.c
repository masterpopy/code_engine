#include "defines.h"
#include "megaimages/indicators.h"
#include "megaimages/mega_trigger.h"

u8 get_item_effect(u8 bank, u8 check_negating_effects);
u8 can_set_mega_trigger(u8 bank);
void healthbar_trigger_callback(struct object* self);
void healthbar_indicator_callback(struct object* self);
u8 is_in_triggering_state(u8 bank);
u8 is_multi_battle();

//返回activebank的设置mega类型
extern bool is_z_seted();
void revert_triggers(u8 bank);

const struct SpriteTiles mega_z_gfx[2] = {
        {indicatorsTiles, 0x60, 0x1234}, {z_mega_trigger, 0x400, 0x2345}
};
#define gfx_indicator mega_z_gfx[0]
#define gfx_trigger mega_z_gfx[1]

const struct SpritePalette mega_z_pals[2] = {
        {indicatorsPal, 0x1234}, {mega_triggerPal, 0x2345}
};
#define pal_indicator mega_z_pals[0]
#define pal_trigger mega_z_pals[1]


struct sprite mega_triggers[2] = {
        {0, 0x0, 0x0, 0x00, 0x0}, {0, 0x0, 0x8000, 0x800, 0}
};
#define mega_indicator mega_triggers[0]
#define mega_trigger mega_triggers[1]

struct template mega_z_templtes[2] = {
        {0x1234, 0x1234, &mega_indicator, (struct frame**) 0x82EC69C, 0, (struct rotscale_frame**) 0x82EC6A8,
                healthbar_indicator_callback},
        {0x2345, 0x2345, &mega_trigger, (struct frame**) 0x82EC69C, 0, (struct rotscale_frame**) 0x82EC6A8,
                healthbar_trigger_callback},
};

#define template_indicator mega_z_templtes[0]
#define template_trigger mega_z_templtes[1]

#define TRIGGER_NUM_IGNORED_COLORS 4

/* Declare the colors the trigger button ignores */
const u16 ignored_cols[TRIGGER_NUM_IGNORED_COLORS] = {0x2147, 0x424F, 0x31AA, 0x00E4};

u8 ignored_trigger_color(u16 color)
{
    for (u32 i = 0; i < TRIGGER_NUM_IGNORED_COLORS; ++i)
    {
        if (ignored_cols[i] == color)
            return 1;
    }
    return 0;
}

u16 calcEnabled(u16 clra)
{
    u16 clrb = 0x7FFF;

    u32 currentAlpha = 20;

    u32 rbmask = ((0x1F) | (0x1F << 10)), gmask = 0x1F << 5;
    u32 rbhalf = 0x4010, ghalf = 0x0200;

    // Red and blue
    u32 parta = clra & rbmask;
    u32 partb = clrb & rbmask;
    u32 part =
            (partb - parta) * (32 - ((currentAlpha < 0x100) ? currentAlpha : currentAlpha >> 12)) + parta * 32 + rbhalf;
    u16 clr = (part >> 5) & rbmask;

    // Green
    parta = clra & gmask;
    partb = clrb & gmask;
    part = (partb - parta) * (32 - ((currentAlpha < 0x100) ? currentAlpha : currentAlpha >> 12)) + parta * 32 + ghalf;
    clr |= (part >> 5) & gmask;

    return clr;
}

void* get_particle_pal(u16 ID)
{
    return &palette_obj_faded[gpu_pal_tags_index_of(ID)];
}

void healthbar_trigger_callback(struct object* self)
{
    switch (self->private[ANIM_STATE])
    {
        case HIDE:
            self->pos1.x = -32;
            self->pos1.y = 0;
            self->private[ANIM_STATE] = HIDDEN;
            break;
        case POS_BEHIND_HPBAR:
            self->pos1.x = -32;
            self->private[RELATIVE_X] = 16;
            if (!battle_flags.double_battle)
            {
                self->private[BASE_X] = SINGLES_HEALTHBOX_X;
                self->pos1.y = SINGLES_HEALTHBOX_Y;
            }
            else
            {
                if (self->private[BANK_TO_ATTACH_TRIGGER] == 0)
                {
                    self->private[BASE_X] = DBL_HB_0_X;
                    self->pos1.y = DBL_HB_0_Y;
                }
                else
                {
                    self->private[BASE_X] = DBL_HB_2_X;
                    self->pos1.y = DBL_HB_2_Y;
                }
            }
            self->private[ANIM_STATE] = SLIDE_OUT;
            break;

        case SLIDE_OUT:
        {
            if (self->private[RELATIVE_X] > 0)
            {
                self->pos1.x = self->private[BASE_X] + self->private[RELATIVE_X];
                self->private[RELATIVE_X] -= 2;
            }
            else
            {
                self->private[ANIM_STATE] = SLIDED_OUT;
            }
        }
            break;

        case SLIDE_IN:
        {
            if (self->private[RELATIVE_X] <= 16)
            {
                self->pos1.x = self->private[BASE_X] + self->private[RELATIVE_X];
                self->private[RELATIVE_X] += 2;
            }
            else
            {
                self->private[ANIM_STATE] = HIDE;
            }
        }
            break;

        case DISABLE:
            self->pos1.x = -32;
            //self->pos1.y = 0;
            self->private[ANIM_STATE] = DISABLED;
            break;
        case SLIDED_OUT:
        case HIDDEN:
        case DISABLED:
            break;
    }

    switch (self->private[PALLET_STATE])
    {
        case LIGHT_UP_TRIGGER:
        {
            struct palette* pal = get_particle_pal(0x2345);
            for (u8 i = 1; i < 16; i++)
            {
                if (ignored_trigger_color(mega_triggerPal[i]))
                    continue;
                pal->c[i] = calcEnabled(mega_triggerPal[i]);
            }
            self->private[PALLET_STATE] = TRIGGER_ON;
            break;
        }
        case REVERT_COLORS:
        {
            struct palette* pal = get_particle_pal(0x2345);
            for (u8 i = 1; i < 16; i++)
            {
                pal->c[i] = mega_triggerPal[i];
            }
            self->private[PALLET_STATE] = REGULAR;
            break;
        }
        case REGULAR:
        case TRIGGER_ON:
            break;
    }
}




void hide_trigger_on_pressing_A()
{
    u8 trigger_id = new_battlestruct->mega_related.trigger_id;
    if (objects[trigger_id].private[ANIM_STATE] == SLIDE_OUT || objects[trigger_id].private[ANIM_STATE] == SLIDED_OUT)
        objects[trigger_id].private[ANIM_STATE] = SLIDE_IN;
}

u8 hide_trigger()
{
    u8 trigger_id = new_battlestruct->mega_related.trigger_id;
    u8 can_b_button_work = 0;
    if(is_z_seted()){
        revert_triggers(active_bank);
        return can_b_button_work;
    }
    hide_trigger_on_pressing_A();
    if (objects[trigger_id].private[ANIM_STATE] == DISABLED ||
        objects[trigger_id].private[ANIM_STATE] == HIDDEN || objects[trigger_id].private[RELATIVE_X] == 0)
    {
        can_b_button_work = 1;
    }
    return can_b_button_work;
}

void position_trigger()
{
    u8 set_mode = can_set_mega_trigger(active_bank);
    if (!set_mode){
        if (is_z_seted() == 0)
            hide_trigger_on_pressing_A();
        return;
    }

    u8 trigger_id = new_battlestruct->mega_related.trigger_id;
    if (objects[trigger_id].private[ANIM_STATE] == HIDDEN)
    {
        struct object* self = &objects[trigger_id];
        self->private[BANK_TO_ATTACH_TRIGGER] = active_bank;
        self->private[ANIM_STATE] = POS_BEHIND_HPBAR;
        u16 attr = self->anim_data_offset;
        if(set_mode == 1)
            attr += 16;
        self->final_oam.attr2 = (self->final_oam.attr2 & 0xFC00) | attr;
    }
}

bool not_mega_or_primal(u8 bank)
{
    bool not_mega = false;
    if ((bank & 1) && (!(new_battlestruct->mega_related.ai_party_z_check & bits_table[battle_team_id_by_side[bank]])) &&
        (!(new_battlestruct->mega_related.ai_party_mega_check & bits_table[battle_team_id_by_side[bank]])))
    {
        not_mega = true;
    }
    else if (!(bank & 1) &&
             (!(new_battlestruct->mega_related.party_z_check & bits_table[battle_team_id_by_side[bank]])) &&
             (!(new_battlestruct->mega_related.party_mega_check & bits_table[battle_team_id_by_side[bank]])))
    {
        not_mega = true;
    }
    return not_mega;
}

void healthbar_indicator_callback(struct object* self)
{
    if (!self->private[DISABLED_INDICATOR])
    {
        u8 bank = self->private[0];
        struct object* healthbox = &objects[healthbox_obj_id_pbs[bank]];

        if (battle_outcome || (healthbox->invisible) || not_mega_or_primal(bank))
        {
            self->pos1.x = -8;
            return;
        }
        if (battle_participants[bank].current_hp == 0)
        {
            self->private[DISABLED_INDICATOR] = 1; //Kill this indicator for the whole battle.
            self->pos1.x = -8;
            return;
        }
        if (!self->private[PRIMAL_CHECK_COMPLETE])
        {
            self->private[PRIMAL_CHECK_COMPLETE] = 1;
            if (get_item_effect(bank, 0) == ITEM_EFFECT_PRIMALORB)
            {
                u8 quality = get_item_quality(battle_participants[bank].held_item);
                if (quality == 1 || quality == 2)
                {
                    self->final_oam.attr2 += (3 - quality);
                }
            }
        }
        u8 lvl = battle_participants[bank].level;
        char buf[10];
        u8 stringlen = (u8) (int_to_str(buf, lvl, 0, 3) - (void*) buf);

        if (bank & 1)
        {
            self->pos1.x = healthbox->pos1.x + 36 + 14 - 5 * stringlen;
        }
        else
        {
            self->pos1.x = healthbox->pos1.x + 44 + 14 - 5 * stringlen;
        }

        self->pos2.x = healthbox->pos2.x;
        self->pos1.y = healthbox->pos1.y - 5;
        // Mirror healthbox priority
        u8 priority = ((healthbox->final_oam.attr2 >> 10) & 3);
        self->final_oam.attr2 = (self->final_oam.attr2 & ~0xC00) | (priority << 10);
    }
}

void dp11_objects_pingpong(struct object* parent_object)
{
    u8 child_object_id = parent_object->private[3];
    s16 pong = get_pingpong((s16) parent_object->private[0], (s16) parent_object->private[2]);
    u16 ychange = parent_object->private[2] + pong;
    objects[child_object_id].pos2.y = ychange;
    if (child_object_id == healthbox_obj_id_pbs[0])
    {
        u8 trigger_id = new_battlestruct->mega_related.trigger_id;
        u8 indi_id = new_battlestruct->mega_related.indicator_id_pbs[0];
        if (objects[trigger_id].private[ANIM_STATE] != DISABLED &&
            objects[trigger_id].private[BANK_TO_ATTACH_TRIGGER] == 0)
        {
            objects[trigger_id].pos2.y = ychange;
        }
        if (!objects[indi_id].private[DISABLED_INDICATOR])
        {
            objects[indi_id].pos2.y = ychange;
        }
    }
    else if (child_object_id == healthbox_obj_id_pbs[2])
    {
        u8 trigger_id = new_battlestruct->mega_related.trigger_id;
        u8 indi_id = new_battlestruct->mega_related.indicator_id_pbs[2];
        if (objects[trigger_id].private[ANIM_STATE] != DISABLED &&
            objects[trigger_id].private[BANK_TO_ATTACH_TRIGGER] == 2)
        {
            objects[trigger_id].pos2.y = ychange;
        }
        if (!objects[indi_id].private[DISABLED_INDICATOR])
        {
            objects[indi_id].pos2.y = ychange;
        }
    }
    else if (child_object_id == healthbox_obj_id_pbs[1])
    {
        u8 indi_id = new_battlestruct->mega_related.indicator_id_pbs[1];
        if (!objects[indi_id].private[DISABLED_INDICATOR])
        {
            objects[indi_id].pos2.y = ychange;
        }
    }
    else if (child_object_id == healthbox_obj_id_pbs[3])
    {
        u8 indi_id = new_battlestruct->mega_related.indicator_id_pbs[3];
        if (!objects[indi_id].private[DISABLED_INDICATOR])
        {
            objects[indi_id].pos2.y = ychange;
        }
    }
    parent_object->private[0] = (parent_object->private[0] + parent_object->private[1]) & 0xFF;
}

void healthbar_shake(struct object* parent_object)
{
    u8 child_object_id = parent_object->private[1];
    u16 ychange = parent_object->private[0];
    objects[child_object_id].pos2.y = ychange;
    parent_object->private[0] = -parent_object->private[0];
    u16* reps = &parent_object->private[2];
    struct mega_related* mega = &new_battlestruct->mega_related;
    struct object* indi_obj = NULL;

    if (child_object_id == healthbox_obj_id_pbs[0])
    {
        indi_obj = &objects[mega->indicator_id_pbs[0]];
    }
    else if (child_object_id == healthbox_obj_id_pbs[1])
    {
        indi_obj = &objects[mega->indicator_id_pbs[1]];
    }
    else if (child_object_id == healthbox_obj_id_pbs[2])
    {
        indi_obj = &objects[mega->indicator_id_pbs[2]];
    }
    else if (child_object_id == healthbox_obj_id_pbs[3])
    {
        indi_obj = &objects[mega->indicator_id_pbs[3]];
    }

    if (indi_obj && !indi_obj->private[DISABLED_INDICATOR])
    {
        indi_obj->pos2.y = ychange;
    }
    (*reps)++;
    if (*reps == 0x15)
    {
        if (indi_obj)
        {
            indi_obj->pos2.x = 0;
            indi_obj->pos2.y = 0;
        }
        objects[child_object_id].pos2.x = 0;
        objects[child_object_id].pos2.y = 0;
        obj_delete_and_free_tiles(parent_object);
    }
}

void healthbar_load_graphics(u8 state)
{
    u8 objid;
    if (state == 2)
    {
        gpu_pal_obj_alloc_tag_and_apply(&pal_indicator);
        gpu_tile_obj_decompress_alloc_tag_and_upload(&gfx_indicator);
        gpu_pal_obj_alloc_tag_and_apply(&pal_trigger);
        gpu_tile_obj_decompress_alloc_tag_and_upload(&gfx_trigger);
        for (u8 bank = 0; bank < no_of_all_banks; ++bank)
        {
            objid = template_instanciate_forward_search(&template_indicator, 1, 0, 1);
            objects[objid].private[0] = bank;
            new_battlestruct->mega_related.indicator_id_pbs[bank] = objid;
        }
        new_battlestruct->mega_related.trigger_id = template_instanciate_forward_search(&template_trigger, 130, 90, 1);
    }
}

