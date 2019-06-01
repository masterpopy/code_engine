#include "cppdefines.h"
#include "learnset.h"
#include "static_references.h"

struct learnset_iterator
{
    struct pokemon* poke;
    u8 poke_lvl;
    u8 learnset_lvl;
    u16 learnset_move;
    const struct learnset* poke_moveset;
    u8 index;
    u8 itr_result;
    u16 data;

    learnset_iterator(){}

    no_inline learnset_iterator(struct pokemon* poke)
    {
        poke_moveset = learnset_table[poke->spieces];
        poke_lvl = poke->level;
        this->poke = poke;
        index = 0;
    }

    bool no_inline has_next_and_store_current()
    {
        u8 lvl = poke_moveset[index].level;
        u16 move = poke_moveset[index].move;
        bool result = move != MOVE_BLANK && lvl != END;
        if (result)
        {
            learnset_lvl = lvl;
            learnset_move = move;
        }
        return result;
    }

    //返回true继续遍历，返回false终止遍历
    typedef bool (* learnset_callback)(learnset_iterator*);

    //返回被callback终止的索引,如果遍历完成则返回0xFF
    u8 begin_itr(learnset_callback callback)
    {
        while (has_next_and_store_current())
        {
            if (!callback(this))
            {
                return index;
            }
            index++;
        }
        return END;
    }

    u16 no_inline teach_move_in_available_slot0(){
        move_to_learn = poke_moveset[slot_in_learnset_table].move;
        slot_in_learnset_table++;
        return teach_move_in_available_slot(poke, move_to_learn);
    }
};


extern "C" void fill_with_default_moves(struct pokemon* poke)
{
    struct learnset_iterator itr = learnset_iterator(poke);
    itr.poke_lvl = get_lvl_from_exp(poke);
    auto cb=[](learnset_iterator* itr)-> bool
    {
        if (itr->learnset_lvl <= itr->poke_lvl)
        {
            if (teach_move_in_available_slot(itr->poke, itr->learnset_move) ==
                    0xFFFF) //there's no room for this move
                new_move_for_the_first(itr->poke, itr->learnset_move);
            return true;
        }
        return false;
    };
    itr.begin_itr(cb);
}

u16 teach_move_evolving(struct pokemon* poke)
{
    struct learnset_iterator itr = learnset_iterator(poke);
    if (poke->padding_maybe >> 7 & 1)
    {
        poke->padding_maybe ^= 128;
        slot_in_learnset_table = itr.begin_itr([](struct learnset_iterator* poke_data)->bool{
            return poke_data->learnset_lvl != LEVEL_EVO;
        });
    }
    if (itr.poke_moveset[slot_in_learnset_table].level != LEVEL_EVO)
        return 0;
    return itr.teach_move_in_available_slot0();
}

extern "C" u16 teach_move_player(struct pokemon* poke, u8 slot)
{
    struct learnset_iterator itr = learnset_iterator(poke);
    if (slot != 0)//slot=0 意味着这个精灵尚未习得技能，需要从头学
    {
        slot_in_learnset_table = itr.begin_itr([](struct learnset_iterator* poke_data)->bool
        {
            return poke_data->learnset_lvl < poke_data->poke_lvl;
        });
    }
    if (itr.poke_moveset[slot_in_learnset_table].level != itr.poke_lvl)
        return teach_move_evolving(poke);
    return itr.teach_move_in_available_slot0();
}

extern "C" bool find_move_in_table2(u16 move, u16* table_ptr, u8 table_length)
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
    struct learnset_iterator itr = learnset_iterator(poke);
    while (itr.has_next_and_store_current() && number_of_moves < MAX_RELEARNABLE)
    {
        if (itr.learnset_lvl < itr.poke_lvl)
        {
            u16 known_move = itr.learnset_move;
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

extern "C" u8 get_relearnable_moves(struct pokemon* poke, u16 moves_table[])
{
    return relearnable_moves(poke, moves_table);
}

extern "C" u8 get_number_of_relearnable_moves(struct pokemon* poke)
{
    return relearnable_moves(poke, 0);
}

extern "C" u8 learnsanydamagingmove(u16 poke)
{
    struct learnset_iterator itr;
    itr.poke_moveset = learnset_table[poke];
    return itr.begin_itr([](struct learnset_iterator* poke_moveset)->bool
    {
        return !move_table[poke_moveset->learnset_move].base_power;
    }) != END;
}

extern "C" bool can_learn_move_from_learnset(struct pokemon* poke,u16 move){
    auto itr = learnset_iterator(poke);
    itr.data = move;
    return itr.begin_itr([](struct learnset_iterator* itr)->bool{
        return itr->learnset_lvl <= itr->poke_lvl && itr->learnset_move != itr->data;
    }) != END;
}