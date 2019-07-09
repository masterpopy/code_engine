#include "learnset.h"
#include "static_references.h"


const struct learnset* get_learset_table(struct pokemon* poke){
	return learnset_table[poke->spieces];
}


void fill_with_default_moves(struct pokemon* poke)
{
    u8 level = get_lvl_from_exp(poke);
    const struct learnset* const poke_moveset = get_learset_table(poke);
    for (u8 i = 0; poke_moveset[i].move != MOVE_BLANK && poke_moveset[i].level != 0xFF; i++)
    {
        if (poke_moveset[i].level <= level)
        {
            if (teach_move_in_available_slot(poke, poke_moveset[i].move) == 0xFFFF) //there's no room for this move
                new_move_for_the_first(poke, poke_moveset[i].move);
        }
    }
}

u16 teach_move_evolving(struct pokemon* poke)
{
	const struct learnset* const poke_moveset = get_learset_table(poke);
	if (poke->padding_maybe >> 7 & 1) {
		poke->padding_maybe ^= 128;
		for (slot_in_learnset_table = 0; ; slot_in_learnset_table++)
		{
			if (poke_moveset[slot_in_learnset_table].move == MOVE_BLANK || poke_moveset[slot_in_learnset_table].level == 0xFF)
				return 0;
			else if (poke_moveset[slot_in_learnset_table].level == LEVEL_EVO)
				break;
		}
	}
	if (poke_moveset[slot_in_learnset_table].level != LEVEL_EVO)
		return 0;
	move_to_learn = poke_moveset[slot_in_learnset_table].move;
	slot_in_learnset_table++;
	return teach_move_in_available_slot(poke, move_to_learn);
}

u16 teach_move_player(struct pokemon* poke, u8 slot)
{
	const struct learnset* const poke_moveset = get_learset_table(poke);
	u8 level = get_attributes(poke, ATTR_LEVEL, 0);
	if (slot != 0)
    {
        for (slot_in_learnset_table = 0; ; slot_in_learnset_table++)
        {
            if (poke_moveset[slot_in_learnset_table].move == MOVE_BLANK || poke_moveset[slot_in_learnset_table].level == 0xFF)
                goto TRY_MOVE_EVOLVING;
            else if (poke_moveset[slot_in_learnset_table].level == level)
                break;
        }
    }
    TRY_MOVE_EVOLVING:
    if (poke_moveset[slot_in_learnset_table].level != level)
        return teach_move_evolving(poke);
    move_to_learn = poke_moveset[slot_in_learnset_table].move;
    slot_in_learnset_table++;
    return teach_move_in_available_slot(poke, move_to_learn);
}

bool find_move_in_table2(u16 move, u16 *table_ptr, u8 table_length)
{
    for (u8 i = 0; i < table_length; i++) {
        if (table_ptr[i] == move) { return true; }
    }
    return false;
}

#define MAX_RELEARNABLE 24

u8 relearnable_moves(struct pokemon* poke, u16 moves_table[])
{
    u8 number_of_moves = 0;
    /*u16 known_moves[4];
    for (u8 j = 0; j < 4; j++)
    {
        known_moves[j] = get_attributes(poke, ATTR_ATTACK_1 + j, 0);
    }*/
	u16* known_moves = poke->moves;
	const struct learnset* const poke_moveset = get_learset_table(poke);
	u8 level = get_attributes(poke, ATTR_LEVEL, 0);
	for (u8 i = 0; poke_moveset[i].move != MOVE_BLANK && poke_moveset[i].level != 0xFF; i++)
    {
        if (poke_moveset[i].level <= level)
        {
            u16 known_move = poke_moveset[i].move;
            if (known_move != known_moves[0] && known_move != known_moves[1] && known_move != known_moves[2] && known_move != known_moves[3] && number_of_moves < MAX_RELEARNABLE)
            {
				if (!moves_table) {
					number_of_moves++;
					break;
				}
                else if (!find_move_in_table2(known_move, moves_table, number_of_moves)) {
                    moves_table[number_of_moves] = known_move;
					number_of_moves++;
				}
            }
        }
    }
    return number_of_moves;
}

u8 get_relearnable_moves(struct pokemon* poke, u16 moves_table[])
{
    return relearnable_moves(poke, &moves_table[0]);
}

u8 get_number_of_relearnable_moves(struct pokemon* poke)
{
    return relearnable_moves(poke, 0);
}

u8 learnsanydamagingmove(u16 poke)
{
    const struct learnset* const poke_moveset = learnset_table[poke];
    for (u8 i = 0; poke_moveset[i].move != MOVE_BLANK && poke_moveset[i].level != 0xFF; i++)
    {
        if (move_table[poke_moveset[i].move].base_power)
            return 1;
    }
    return 0;
}

