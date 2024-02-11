#ifndef STD_TYPES_H_INCLUDED
#define STD_TYPES_H_INCLUDED

#define F_CPU 16000000UL
#include "util/delay.h"

#define NULL_PTR       ((void*)0)
#define TRUE                 (1u)
#define FALSE                (0u)

#define LOGIC_HIGH           (1u)
#define LOGIC_LOW            (0u)

#define NULL				((void*)0)

typedef unsigned char         u8;
typedef unsigned short       u16;
typedef unsigned int         u32;
typedef unsigned long long   u64;
typedef        char           s8;
typedef signed short         s16;
typedef signed int           s32;
typedef signed long long     s64;
typedef float                f32;
typedef double               d64;



#endif // STD_TYPES_H_INCLUDED
