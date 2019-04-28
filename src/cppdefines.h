#ifndef ENGINE7_CPPDEFINES_H
#define ENGINE7_CPPDEFINES_H
#ifndef DEFINES_H

#ifndef __cplusplus
#define __cplusplus
#endif

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#define true 1
#define false 0

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;

#include "config.h"



enum move_split
{
    MOVE_PHYSICAL, //0
    MOVE_SPECIAL, //1
    MOVE_STATUS, //2
};

enum poke_sprite
{
    SPRITE_BACK = 0, SPRITE_FRONT = 1
};

enum poke_gender
{
    POKE_MALE = 0, POKE_FEMALE = 0xFE, POKE_GENDERLESS = 0xFF
};

enum menu_action
{
    ACTION_MOVE = 0, //0x0
    ACTION_ITEM, //0x1
    ACTION_SWITCH, //0x2
    ACTION_RUN, //0x3
};

enum item_pocket
{
    POCKET_ITEMS = 1, POCKET_BALLS, //0x2
    POCKET_TMS, //0x3
    POCKET_BERRIES, //0x4
    POCKET_KEYITEMS, //0x5
};

enum ball_index
{
    BALL_POKE, //0x0
    BALL_GREAT, //0x1
    BALL_SAFARI, //0x2
    BALL_ULTRA, //0x3
    BALL_MASTER, //0x4
    BALL_NET, //0x5
    BALL_DIVE, //0x6
    BALL_NEST, //0x7
    BALL_REPEAT, //0x8
    BALL_TIMER, //0x9
    BALL_LUXURY, //0xA
    BALL_PREMIER, //0xB
    //new balls
#if EXPANDED_POKEBALLS == true
    BALL_LEVEL, //0xC
    BALL_LURE, //0xD
    BALL_MOON, //0xE
    BALL_FRIEND, //0xF
    BALL_LOVE, //0x10
    BALL_HEAVY, //0x11
    BALL_FAST, //0x12
    BALL_SPORT, //0x13
    BALL_DUSK, //0x14
    BALL_QUICK, //0x15
    BALL_HEAL, //0x16
    BALL_CHERISH, //0x17
    BALL_PARK, //0x18
    BALL_DREAM, //0x19
    BALL_BEAST, //0x1A
#endif // EXPANDED_POKEBALLS
};

enum map_type
{
    MAP_TOWN = 1, MAP_CITY, //0x2
    MAP_ROUTE, //0x3
    MAP_CAVE, //0x4
    MAP_UNDERWATER, //0x5
    MAP_INSIDE = 8, MAP_SECRETBASE, //0x9
};

#include "./defines/poke_types.h"
#include "./defines/abilities.h"
#include "./defines/moves.h"
#include "./defines/get_attr.h"
#include "./defines/items.h"
#include "./defines/item_effects.h"
#include "./defines/pokes.h"
#include "./defines/flavours.h"

#include "./defines/battle_structs_cpp.h"
#include "battle_locations.h"
#include "new_battle_struct.h"
#include "vanilla_functions.h"

#endif
#endif //ENGINE7_CPPDEFINES_H
