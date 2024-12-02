#ifndef _MP2_H_
#define _MP2_H_

#include "ultra64.h"
#include "marioparty.h"

typedef struct mp2_BoardState {
    s16 unk_00;
    s16 curBoardIndex;
    s16 unk_04;
    s16 maxTurns;
    s16 curTurn;
    s16 unk_0A;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    s16 unk_22;
    u8 unk_24;
    u8 minigameExplanations; //0x25
    s16 unk_26;
    s16 unk_28;
    s16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
} mp2_BoardStatus;

u32 mp2_osGetCount(void);
void mp2_StoreBattleMinigameCoins(void);
extern omOvlHisData mp2_omovlhis[12];
extern s16 mp2_omovlhisidx;
extern s16 mp2_omovlhisidx_copy;
extern mp2_GW_PLAYER mp2_PlayersCopy[4];
extern s16 mp2_hidden_block_coins_space_index;
extern s16 mp2_hidden_block_star_space_index;
extern mp2_BoardStatus mp2_BoardStateCopy;
extern s16 mp2_BattleMinigameCoins_Copy;
extern mp2_BoardStatus mp2_BoardState;

#endif
