#include "defines.h"
#include "static_references.h"

struct trainer_slide_info{
    u16 trainerID;
    u16 caseID;
    u8* txt_last_switchin;
    u8* txt_last_lowHP;
    u8* txt_first_down;
};
u8 slide_1[]={0xFD, 15, 0x0F, 0x0B, 0x0A, 0xAB, 0x07, 0x31, 0x07, 0x51, 0x0B, 0x2B, 0x08, 0x79, 0x01, 0x28, 0xAB, 0xFF};
u8 slide_2[]={0x05, 0x0B, 0x04, 0xE9, 0xAB, 0x0D, 0x98, 0x03, 0x0A, 0x0B, 0xF5, 0x02, 0x78, 0x0B, 0x2B, 0x08, 0x79, 0x08, 0x9E, 0xAB, 0xFF};
u8 slide_3[]={0x01, 0xAA, 0x0E, 0x03, 0x03, 0x0A, 0x01, 0xD6, 0x02, 0xCD, 0xB8, 0x07, 0x25, 0x0D, 0xE6, 0x08, 0x29, 0xFE, 0x01, 0xD6, 0x05, 0x6E, 0x04, 0x62, 0x09, 0xD9, 0x08, 0xC7, 0x0F, 0x7E, 0x0B, 0x4E, 0x04, 0xF4, 0x05, 0x87, 0x05, 0x6E, 0xAB, 0xFF};


struct trainer_slide_info sliding_trainers[NO_OF_SLIDING_MSG_TRAINERS] = {
    {0, 0, NULL, NULL, NULL},
	{0x106, 0, slide_1, slide_2, slide_3},
	//{0x106, 0, slide_1, slide_2, slide_3},
	{0x107, 0, slide_1, slide_2, slide_3},
	{0x108, 0, slide_1, slide_2, slide_3},
	{0x109, 0, slide_1, slide_2, slide_3}
};

u8 get_trainer_opponent_A_class()
{
	return (*trainer_table)[var_8015_trainer_opponent_A].class;
}
/*
u8 get_trainer_class_by_bank(u8 bank){
	u16* trainerID = &var_8015_trainer_opponent_A;
	if(bank == 1)
		return trainerID[0];
	else if(bank == 2)
		return trainerID[2];
	else if(bank == 3)
		return trainerID[1];
	return 0;
}
*/
/*
void* trainer_callback(u8 caseID)
{
	
	if(caseID==1)
	{
		u16 value=0xffff;
		for (u8 i=0; i<6; i++)
			set_attributes(party_oppenent+i, ATTR_ATTACK+i, &value);
	}
}
*/
u8* get_slide_msg(u16 trainerID, u8 caseID)
{
    u8* txt_ptr = NULL;
    if (!battle_flags.multibattle)
    {
        for (u16 i = 0; i < NO_OF_SLIDING_MSG_TRAINERS; i++)
        {
            struct trainer_slide_info* curr_trainer = &sliding_trainers[i];
            if (trainerID == curr_trainer->trainerID)
            {
                u8** txt_ptrs = &curr_trainer->txt_last_switchin;
				//if(curr_trainer->caseID == caseID)
				//	trainer_callback(curr_trainer->caseID);
                return txt_ptrs[caseID];
            }
        }

    }
    return txt_ptr;
}
