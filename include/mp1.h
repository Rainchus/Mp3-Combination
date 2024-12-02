#ifndef _MP1_H_
#define _MP1_H_

#include "ultra64.h"
#include "marioparty.h"

typedef struct mp1BoardState {
/* 0x00 */ char unk_00[0x02];
/* 0x02 */ s16 curBoardIndex;
/* 0x04 */ s16 playType; //lite play, standard play, full play (20, 35, 50 turns)
/* 0x06 */ s16 maxTurns;
/* 0x08 */ s16 curTurn;
/* 0x0A */ char unk_0A[0x12];
/* 0x1C */ s16 playerIndex;
/* 0x1E */ char unk_1E[4];
/* 0x22 */ u8 saveSetting;
/* 0x23 */ u8 minigameExplanation;
/* 0x24 */ u8 messageSpeed;
/* 0x25 */ char unk_25[3];
} mp1BoardState; //0x28 in size???

u32 mp1_osGetCount(void);
void PushMp1MinigamesPlayedList(void);
void mp1_func_8006D7D8(s32 arg0, char* arg1, s32 arg2, s32 arg3);
void SaveMp1PlayerStructs(void);
void PushMp1BoardState(void);
void PushMp1OvlHis(void);
void PopMp1OvlHis(void);
void LoadMp1PlayerStructs(void);
void PopMp1BoardState(void);
void mp1_HuPrcEnd(void);

extern omOvlHisData mp1_omovlhis[12];
extern omOvlHisData mp1_omovlhis_copy[12];
extern s16 mp1_omovlhisidx;
extern mp1_GW_PLAYER mp1_PlayersCopy[4];
extern u8 mp1_D_800ED5E3;
extern u16 mp1_D_800ED5DE;
extern mp1BoardState mp1_BoardState;
extern mp1BoardState mp1_BoardStateCopy;
extern u8 mp1_D_800F64F2;

#endif