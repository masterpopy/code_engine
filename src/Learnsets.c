#include "defines.h"

#if BUILD_LEARNSETS == true

#include "Learnsets.h"
#include "static_references.h"


struct learnset_iterator
{
    //基本常用缓存信息
    struct pokemon* poke;
    u8 poke_lvl;
    //当前迭代技能数据
    u8 level;
    u16 move;
    //迭代索引
    const struct learnset* poke_moveset;
    u8 index;
};

static struct learnset_iterator learnset_itr(struct pokemon* poke)
{
    struct learnset_iterator itr;
    itr.poke_moveset = learnset_table[poke->spieces];
    itr.poke_lvl = poke->level;
    itr.poke = poke;
    itr.index = 0;
    return itr;
}


bool has_next_and_store_current(struct learnset_iterator* itr)
{
    const struct learnset* poke_moveset = &itr->poke_moveset[itr->index];
    u8 lvl = poke_moveset->level;
    u16 move = poke_moveset->move;
    if (move != MOVE_BLANK && lvl != END)
    {
        itr->level = lvl;
        itr->move = move;
        return true;
    }
    return false;
}

//返回true继续遍历，返回false终止遍历
typedef bool (* learnset_callback)(struct learnset_iterator* poke_data);

//返回被callback终止的索引,如果遍历完成则返回0xFF
u32 begin_itr(struct learnset_iterator* itr, learnset_callback callback)
{
    while (has_next_and_store_current(itr))
    {
        if (!callback(itr))
        {
            return itr->index;
        }
        itr->index++;
    }
    return END;
}


void fill_with_default_moves(struct pokemon* poke)
{
    struct learnset_iterator itr = learnset_itr(poke);

    bool cb(struct learnset_iterator* poke_data)
    {
        if (poke_data->level <= poke_data->poke_lvl)
        {
            if (teach_move_in_available_slot(poke_data->poke, poke_data->move) ==
                    0xFFFF) //there's no room for this move
                new_move_for_the_first(poke_data->poke, poke_data->move);
            return true;
        }
        return false;
    }

    begin_itr(&itr, cb);
}

u16 teach_move_evolving(struct pokemon* poke)
{
    struct learnset_iterator itr = learnset_itr(poke);
    if (poke->padding_maybe >> 7 & 1)
    {
        poke->padding_maybe ^= 128;
        bool cb(struct learnset_iterator* poke_data)
        {
            return poke_data->level != LEVEL_EVO;
        }
        slot_in_learnset_table = begin_itr(&itr, cb);
    }
    if (itr.poke_moveset[slot_in_learnset_table].level != LEVEL_EVO)
        return 0;
    move_to_learn = itr.poke_moveset[slot_in_learnset_table].move;
    slot_in_learnset_table++;
    return teach_move_in_available_slot(poke, move_to_learn);
}

u16 teach_move_player(struct pokemon* poke, u8 slot)
{
    struct learnset_iterator itr = learnset_itr(poke);
    if (slot != 0)//slot=0 意味着这个精灵尚未习得技能，需要从头学
    {
        bool cb(struct learnset_iterator* poke_data)
        {
            return poke_data->level != poke_data->poke_lvl;
        }
        slot_in_learnset_table = begin_itr(&itr, cb);
    }
    if (itr.poke_moveset[slot_in_learnset_table].level != itr.poke_lvl)
        return teach_move_evolving(poke);
    move_to_learn = itr.poke_moveset[slot_in_learnset_table].move;
    slot_in_learnset_table++;
    return teach_move_in_available_slot(poke, move_to_learn);
}

bool find_move_in_table2(u16 move, u16* table_ptr, u8 table_length)
{
    for (u8 i = 0; i < table_length; i++)
    {
        if (table_ptr[i] == move)
        {
            return i;
        }
    }
    return false;
}

#define MAX_RELEARNABLE 24

u8 relearnable_moves(struct pokemon* poke, u16 moves_table[])
{
    u8 number_of_moves = 0;
    struct learnset_iterator itr = learnset_itr(poke);
    while (has_next_and_store_current(&itr) && number_of_moves < MAX_RELEARNABLE)
    {
        if (itr.level < itr.poke_lvl)
        {
            u16 known_move = itr.move;
            if (!find_move_in_table2(known_move, poke->moves, 4) &&
                    !find_move_in_table2(known_move, moves_table, number_of_moves))
            {
                number_of_moves++;
                if (moves_table)
                {
                    moves_table[number_of_moves] = known_move;
                }
            }
        }
        else
            break;
        itr.index++;
    }
    return number_of_moves;
}

u8 get_relearnable_moves(struct pokemon* poke, u16 moves_table[])
{
    return relearnable_moves(poke, moves_table);
}

u8 get_number_of_relearnable_moves(struct pokemon* poke)
{
    return relearnable_moves(poke, 0);
}

u8 learnsanydamagingmove(u16 poke)
{
    struct learnset_iterator itr;
    itr.poke_moveset = learnset_table[poke];
    bool cb(struct learnset_iterator* poke_moveset)
    {
        return !move_table[poke_moveset->move].base_power;
    }
    return begin_itr(&itr, cb) != END;
}

#endif