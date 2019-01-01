#include "defines.h"

void revert_form_change(u8 mega_revert, u8 teamID, u8 side, struct pokemon* poke);
u16 try_illusion_change(u8 bank, struct pokemon* poke);
//struct pokemon* get_party_ptr(u8 bank);
bool percent_chance(u8 percent);
void  __attribute__((long_call)) setflag(u32 flag);
void alloc_new_struct(void)//b06d0
{
    battle_stuff_ptr = (struct battle_stuff*) malloc_and_clear(sizeof(struct battle_stuff));
    new_battlestruct = (struct new_battle_struct*) malloc_and_clear(sizeof(struct new_battle_struct));
    //apply Egg Type
    for (u8 i = 0; i < 4; i++)
    {
        new_battlestruct->bank_affecting[i].type3 = TYPE_EGG;
    }
    #if ITEM_SWAP == false
    for (u8 i = 0; i < 6; i++)
    {
        struct pokemon* poke = &party_player[i];
        new_battlestruct->various.original_held_item[i] = get_attributes(poke, ATTR_HELD_ITEM, 0);
    }
    #endif // ITEM_SWAP
    if (INVERSE_FLAG && getflag(INVERSE_FLAG))
    {
        new_battlestruct->various.inverse_battle = 1;
    }
    if (FISHING_FLAG && getflag(FISHING_FLAG))
    {
        new_battlestruct->various.fishing_battle = 1;
        clearflag(FISHING_FLAG);
    }
}

void try_burmy_change(u8 id, struct pokemon* poke)
{
    if (new_battlestruct->various.sent_in_player & bits_table[id])
    {
        u16 species = get_attributes(poke, ATTR_SPECIES, 0);
        if (POKE_BURMY(species))
        {
            u16 to_change;
            if (battle_env_bg >= 8)
                to_change = POKE_BURMY_TRASH;
            else if (battle_env_bg == BACKGROUND_SAND || battle_env_bg >= BACKGROUND_ROCK)
                to_change = POKE_BURMY_SAND;
            else
                to_change = POKE_BURMY_PLANT;
            if (species != to_change)
            {
                set_attributes(poke, ATTR_SPECIES, &to_change);
                calculate_stats_pokekmon(poke);
            }
        }
    }
}
bool is_bank_present(u32 bank);
void free_new_struct(void)
{
    //revert forms to default ones
    for (u8 i = 0; i < 6; i++)
    {
        struct pokemon* poke = &party_player[i];
        revert_form_change(1, i, 0, poke);
        revert_form_change(0, i, 0, poke);
        try_burmy_change(i, poke);
        #if STAT_RECALC == true
        calculate_stats_pokekmon(poke);
        #endif // STAT_RECALC
        #if ITEMS_STEAL == false //return stolen items
            if (new_battlestruct->various.returns_item & bits_table[i])
            {
                u16 zero = 0;
                set_attributes(poke, ATTR_HELD_ITEM, &zero);
            }
        #endif // ITEMS_STEAL
        #if ITEM_SWAP == false //return swapped item
            if (new_battlestruct->various.returns_swap & bits_table[i])
            {
                set_attributes(poke, ATTR_HELD_ITEM, &new_battlestruct->various.original_held_item[i]);
            }
        #endif // ITEM_SWAP ABILITY_HONEY_GATHER
		if(get_poke_ability(poke)== ABILITY_HONEY_GATHER && get_attributes(poke, ATTR_HELD_ITEM, 0)== 0)
		{
			u8 percent = get_attributes(poke, ATTR_LEVEL, 0);
			percent = percent / 4;
			if (percent_chance(percent))
			{
				u16 item= rng() % 4 + 617;
				set_attributes(poke, ATTR_HELD_ITEM, &item);
			}
		}
    }
    free(battle_stuff_ptr);
    free(new_battlestruct);
	u32* battle_flags = (u32*)0x02022FEC;//battle_flags
    *battle_flags &= 1024;
	battle_chosen_bg = 0;
}
