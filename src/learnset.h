#ifndef ENGINE7_LEARNSETS_H
#define ENGINE7_LEARNSETS_H

#include "defines.h"

#define MOVE_BLANK 0x0000
#define END 0xFF
#define EGG_MOVESET 0x00000000
#define LEVEL_EVO 0x00

#pragma pack(push,1)
struct learnset{
	u16 move;
	u8 level;
};
#pragma pack(pop)

const struct learnset* learnset_table[ALL_POKES];


#endif //ENGINE7_LEARNSETS_H
