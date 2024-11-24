#ifndef _MP2_H_
#define _MP2_H_

#include "ultra64.h"
#include "marioparty.h"

#define MP2_BOARD_STATE_STRUCT_SIZE 0x30

u32 mp2_osGetCount(void);
extern omOvlHisData mp2_omovlhis[12];
extern s16 mp2_omovlhisidx;
extern u8 mp2_BoardStateCopy[MP2_BOARD_STATE_STRUCT_SIZE];
extern mp2_GW_PLAYER mp2_PlayersCopy[4];

#endif
