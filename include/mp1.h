#ifndef _MP1_H_
#define _MP1_H_

#include "ultra64.h"
#include "marioparty.h"

typedef struct mp1_GameStatus {
/* 0x00 */ s16 unk_00;
/* 0x02 */ s16 curBoardIndex;
/* 0x04 */ s16 playType; //lite play, standard play, full play (20, 35, 50 turns)
/* 0x06 */ s16 maxTurns;
/* 0x08 */ s16 currentTurn;
/* 0x0A */ s16 chosenStarSpaceIndex;
/* 0x0C */ s16 starSpaces[7];
/* 0x1A */ s16 unk_1A;
/* 0x1C */ s16 curPlayerIndex;
/* 0x1E */ s16 curMinigame;
/* 0x20 */ s16 curSpaceIndex;
/* 0x22 */ u8 saveSetting;
/* 0x23 */ s8 minigameExplanation;
/* 0x24 */ u8 messageSpeed;
/* 0x25 */ char unk_25;
} mp1_GameStatus; //sizeof 0x26

typedef struct mp1_GwCommon_s {
/* 0x00 */ u8 unk0;
/* 0x01 */ char unk_01[1];
/* 0x02 */ s16 mgRecord[8];
/* 0x12 */ u8 mgUnlock[7];
/* 0x19 */ u8 mgBuy[7];
/* 0x20 */ u16 boardRecord[8][2];
/* 0x40 */ u32 coinNum;
/* 0x44 */ s16 starNum;
/* 0x46 */ s8 unk_46;
/* 0x47 */ s8 boardItem;
/* 0x48 */ u8 flag[12];
/* 0x54 */ s16 boardWork[32];
} mp1_GWCOMMON; //sizeof 0x94

typedef struct unk_Struct04 {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ char padC[0x18];
    /* 0x24 */ f32 unk_24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ char pad30[0x10];
    /* 0x40 */ s16* unk_40;
} unk_Struct04; /* size = 0x44 */

typedef struct mp1_Object {
/* 0x00 */ struct mp1_Object *prev; // may be NULL
/* 0x04 */ struct mp1_Object *next;
/* 0x08 */ s16 unk_08;
/* 0x0A */ u16 unk_0A;
/* 0x0C */ Vec3f coords;
/* 0x18 */ Vec3f unk_18;
/* 0x24 */ f32 xScale;
/* 0x28 */ f32 yScale;
/* 0x2C */ f32 zScale;
/* 0x30 */ f32 unk_30;
/* 0x34 */ f32 unk_34;
/* 0x38 */ f32 unk_38;
/* 0x3C */ unk_Struct04* unk_3C;
/* 0x3C */ unk_Struct04* unk_40;
/* 0x44 */ f32 unk_44;
/* 0x48 */ f32 unk_48;
/* 0x4C */ s32 unk_4C;
/* 0x50 */ char unk_50[3];
/* 0x53 */ s8 unk_53;
/* 0x50 */ char unk_54[0x38];
/* 0x8C */ struct mp1_Object* unk_8C;
} mp1_Object; // //sizeof 0xAC? (this and mpSource_object are the same struct)

typedef struct {
    s16 activationType;
    s16 executionType;
    void (*eventFunc)();
} EventListEntry;

typedef struct EventTableEntry {
    s16 spaceIndex;
    EventListEntry* eventList;
} EventTableEntry;

typedef struct mp1_SpaceData {
    s8 unk0;
    u8 spaceType;
    s16 unk2;
    Vec3f coords;
    f32 sx, sy, sz;
    EventListEntry *eventList;
} mp1_SpaceData;

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
void mp1_HuPrcVSleep(void);
void mp1_HuPrcSleep(s32);
void mp1_omInitObjMan(s32, s32);

extern s16 mp1_D_800D86B0;
extern omOvlHisData mp1_omovlhis[12];
extern omOvlHisData mp1_omovlhis_copy[12];
extern s16 mp1_omovlhisidx;
extern mp1_GW_PLAYER mp1_PlayersCopy[4];
extern mp1_GameStatus mp1_GwSystem;
extern mp1_GameStatus mp1_GwSystemCopy;
extern mp1_GWCOMMON mp1_GwCommon;
extern mp1_GWCOMMON mp1_GwCommonCopy;
extern u8 mp1_D_800F64F2;

#endif