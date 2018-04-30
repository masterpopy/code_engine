#include "defines.h"

struct recording_evo{
    u8 action : 3;
    u8 evo_trigger : 3;
};

void update_battle_record(u8 bank, u8 action)
{
    u16* curr_byte = &no_of_recorded_bytes[bank];
    if (viewing_recorded_battle != 2 && *curr_byte < 664)
    {
        if (!new_battlestruct->various.recorded_mega)
        {
            u8 user_trigger = new_battlestruct->mega_related.user_trigger;
            if (user_trigger)
            {
                struct recording_evo mega_evo;
                mega_evo.action = action;
                mega_evo.evo_trigger = user_trigger;
                action = *(u8*)(&mega_evo);
                new_battlestruct->various.recorded_mega = 1;
            }
        }
        battle_record[bank].action[*curr_byte] = action;
        *curr_byte += 1;
    }
}

u8 read_recorded_battle_byte(u8 bank)
{
    u16* curr_byte = &no_of_recorded_bytes[bank];
    u8 read_byte = battle_record[bank].action[*curr_byte];
    if (*curr_byte > 663 || read_byte == 0xFF)
    {
        battle_outcome = var_800D_lastresult = 5;
        pal_fade_control_reset_maybe();
        fadescreen_related(-1, 0, 0, 0x10, 0);
        set_callback2(&quit_recorded_battle);
    }
    else
    {
        *curr_byte += 1;
        if (read_byte > 4)
        {
            struct recording_evo mega_evo;
            *(u8*) (&mega_evo) = read_byte;
            new_battlestruct->mega_related.user_trigger = mega_evo.evo_trigger;
            read_byte = mega_evo.action;
        }
    }
    return read_byte;
}
