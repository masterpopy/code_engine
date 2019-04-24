#if BUILD_LEARNSETS == true

#include "Learnsets.h"
#include "static_references.h"

const struct learnset* get_learnset_table(struct pokemon* poke){
	return learnset_table[poke->spieces];
}

#define LITOR_END 0xff

#pragma pack(push,1)
struct learnset_base{
    struct pokemon* poke;
    u8 poke_lvl;
};
#pragma pack(pop)
struct learnset_iterator{
    struct learnset_base base;
    u8 index;
    const struct learnset* poke_moveset;
};

struct learnset_iterator get_literator(struct pokemon* poke){
    struct learnset_iterator liter;
    liter.poke_moveset = get_learnset_table(poke);
    liter.base.poke_lvl = poke->level;
    liter.base.poke = poke;
    return liter;
}


bool has_next(struct learnset_iterator* liter){
    const struct learnset* poke_moveset = liter->poke_moveset;
    u32 i = liter->index;
    return poke_moveset[i].move != MOVE_BLANK && poke_moveset[i].level != 0xFF;
}

const struct learnset* next_moveset(struct learnset_iterator* liter){
    const struct learnset* poke_moveset = liter->poke_moveset;
    return &poke_moveset[liter->index++];
}

//返回true继续遍历，返回false终止遍历
typedef bool (*learnset_callback)(const struct learnset* poke_moveset, struct learnset_base* poke_data);

//返回被callback终止的索引,如果遍历完成则返回0xFF
u32 begin_litor(struct learnset_iterator* literator, void* callback){
    while(has_next(literator)){
        const struct learnset* next = next_moveset(literator);
        if(!((learnset_callback)callback)(next, &literator->base)){
            return literator->index - 1;
        }
    }
    return LITOR_END;
}


/*bool fill_with_default_moves_callback(const struct learnset* poke_moveset, struct learnset_base* poke_data){
    if (poke_moveset->level <= poke_data->poke_lvl)
    {
        if (teach_move_in_available_slot(poke_data->poke, poke_moveset->move) == 0xFFFF) //there's no room for this move
            new_move_for_the_first(poke_data->poke, poke_moveset->move);
        return true;
    }
    return false;
}*/


void fill_with_default_moves(struct pokemon* poke)
{
    struct learnset_iterator liter = get_literator(poke);
    struct learnset_iterator* literator = &liter;

    bool fill_with_default_moves_callback(const struct learnset* poke_moveset, struct learnset_base* poke_data){
        if (poke_moveset->level <= poke_data->poke_lvl)
        {
            if (teach_move_in_available_slot(poke_data->poke, poke_moveset->move) == 0xFFFF) //there's no room for this move
                new_move_for_the_first(poke_data->poke, poke_moveset->move);
            return true;
        }
        return false;
    }

    begin_litor(literator, fill_with_default_moves_callback);
}




u16 teach_move_evolving(struct pokemon* poke)
{
	struct learnset_iterator litor = get_literator(poke);
	if (poke->padding_maybe >> 7 & 1) {
		poke->padding_maybe ^= 128;
		bool teach_move_evolving_callback(const struct learnset* poke_moveset){
            return poke_moveset->level != LEVEL_EVO;
        }
        begin_litor(&litor, teach_move_evolving_callback);
        slot_in_learnset_table = litor.index;
    }
    const struct learnset* poke_moveset = litor.poke_moveset;
	if (poke_moveset[slot_in_learnset_table].level != LEVEL_EVO)
		return 0;
	move_to_learn = poke_moveset[slot_in_learnset_table].move;
	slot_in_learnset_table++;
	return teach_move_in_available_slot(poke, move_to_learn);
}



u16 teach_move_player(struct pokemon* poke, u8 slot)
{
	struct learnset_iterator litor = get_literator(poke);
	if (slot != 0)
    {
        bool teach_move_player_callback(const struct learnset* poke_moveset, struct learnset_base* poke_data){
            return poke_moveset->level != poke_data->poke_lvl;
        }
        begin_litor(&litor, teach_move_player_callback);
        slot_in_learnset_table = litor.index;
    }
    const struct learnset* poke_moveset = litor.poke_moveset;
    if (poke_moveset[slot_in_learnset_table].level != litor.base.poke_lvl)
        return teach_move_evolving(poke);
    move_to_learn = poke_moveset[slot_in_learnset_table].move;
    slot_in_learnset_table++;
    return teach_move_in_available_slot(poke, move_to_learn);
}

bool find_move_in_table2(u16 move, u16 *table_ptr, u8 table_length)
{
    for (u8 i = 0; i < table_length; i++) {
        if (table_ptr[i] == move) { return i; }
    }
    return false;
}

#define MAX_RELEARNABLE 24

u8 relearnable_moves(struct pokemon* poke, u16 moves_table[])
{

    u8 number_of_moves = 0;
    struct learnset_iterator litor = get_literator(poke);
	while(has_next(&litor) && number_of_moves < MAX_RELEARNABLE){
        const struct learnset* poke_moveset = next_moveset((&litor));
        if(poke_moveset->level < litor.base.poke_lvl){

            u16 known_move = poke_moveset->move;
            if (!find_move_in_table2(known_move, poke->moves, 4) &&
                    !find_move_in_table2(known_move, moves_table, number_of_moves))
            {
                if (!moves_table) {
                    return 1;
                }
                moves_table[number_of_moves++] = known_move;
            }
        } else break;
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
    struct learnset_iterator litor;
    litor.poke_moveset = learnset_table[poke];
    bool learnsanydamagingmove_callback(const struct learnset* poke_moveset){
        return !move_table[poke_moveset->move].base_power;
    }
    return begin_litor(&litor, learnsanydamagingmove_callback) != LITOR_END;
}

#endif