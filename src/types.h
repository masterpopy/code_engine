#ifndef ENGINE_TYPES_H
#define ENGINE_TYPES_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#include <stdbool.h> //typedef u8 bool;

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;

#define NULL 0

typedef void (*command)(void);

#endif /* ENGINE_TYPES_H */
