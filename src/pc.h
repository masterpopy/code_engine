#ifndef ENGINE7_PC_H
#define ENGINE7_PC_H

#include "defines.h"


struct ov_script
{ //0x3000e40
    u8 push_counter;
    u8 mode;
    u8 comp_result;
    u8 padd;
    void* waiting_routine;
    void* curr_instruction;//0x 3000e48
    void* stack[20];
    void* commands_table_start;
    void* commands_table_end;
    u32 vars[4];
};

extern struct ov_script over_world_script;

struct pokemon_pc
{
    u32 data[20];
};

struct save_block3
{
    u8 current_box;
    u8 pad0;
    u16 padd1;
    struct pokemon_pc pc_pokes[14][30];
    u8 name[14][9];//8344
    u8 bg[14];//83C2
};

extern struct save_block3* sav3;

#define EXPANDED_BOX 8
#define MAX_BOX_COUNT (EXPANDED_BOX + 14) //22

struct save_block3_new
{
    u8 name[EXPANDED_BOX][9];
    u8 bg[EXPANDED_BOX];//100 bytes
    struct pokemon_pc pc_pokes[EXPANDED_BOX][30];
};

extern struct save_block3_new new_sav3;

#endif //ENGINE7_PC_H
