#include "marioparty.h"

typedef struct mp2_omObjData {
/* 0x00 */ u16 stat;
/* 0x02 */ s16 next_idx_alloc;
/* 0x04 */ s16 prio;
/* 0x06 */ s16 prev;
/* 0x08 */ s16 next;
/* 0x0A */ s16 next_idx;
/* 0x0C */ s16 group;
/* 0x0E */ s16 group_idx;
/* 0x10 */ s32 unk_10;
/* 0x14 */ void* func_ptr;
/* 0x18 */ Vec3f trans;
/* 0x24 */ Vec3f rot;
/* 0x30 */ Vec3f scale;
/* 0x3C */ u16 mdlcnt;
// /* 0x3E */ char unk_3E[2];
/* 0x40 */ s16* model;
/* 0x44 */ u16 mtncnt;
// /* 0x46 */ char unk_46[2];
/* 0x48 */ s16* motion;
/* 0x4C */ u8 work[4];
/* 0x50 */ void* unk_50;
} mp2_omObjData; //sizeof 0x54

typedef struct UnkBoardStatus {
    char unk0[2];
    s16 unk_02;
    char unk4[0x1A];
    s16 unk_1E;
    s16 unk_20;
    s16 unk_22;
    s16 unk_24;
    s16 unk_26;
} UnkBoardStatus; //sizeof 0x28

void mp2_omInitObjMan(s32, s32);
void mp2_func_80079E60_7AA60(void);
void CopyMp3_gPlayerCopy_To_Mp2(void);
void mp2__SetFlag(s32);
void mp2_func_80102D54_D5D44_Debug(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void mp2_func_80026D28_27928(s32);
void mp2_func_80026DAC_279AC(s32, s32, s32, s32);
void mp2_func_80026E00_27A00(s32, f32, f32, f32);
NORETURN void ComboSwitchGameToMp3(void);

extern s8 mp2_D_80107400_DA3F0_Debug;
extern s8 mp2_D_800F93CD_F9FCD;
extern u32 mp2_D_800CD408_CE008;
extern s32 mp2_MinigameIndexToLoad;
extern UnkBoardStatus mp2_D_800F93A8;
extern s32 mp3_LoadBackFromMp2;
extern mp3_PlayerData mp3_PlayersCopy[4];

//main ovl_00 function. gets ran immediately upon loading the overlay
void func_80102800_D57F0_Debug_2(void) {
    s32 i;

    mp2_D_800F93A8.unk_20 = mp2_MinigameIndexToLoad;
    mp2_D_800F93A8.unk_22 = 0x55;

    if (mp2_MinigameIndexToLoad == -1) {
        for (i = 0; i < 4; i++) {
            s32 coinsEarned = mp2_gPlayers[i].coins - mp3_PlayersCopy[i].coins;
            //update mp3 player coins and coin star
            mp3_PlayersCopy[i].coins += coinsEarned;
            mp3_PlayersCopy[i].minigameCoinsTotal += coinsEarned;
        }
        mp3_LoadBackFromMp2 = TRUE;
        ComboSwitchGameToMp3();
        return; //this isn't actually reached anyway
    } else {
        mp2_MinigameIndexToLoad = -1;
    }

    CopyMp3_gPlayerCopy_To_Mp2();
    
    mp2_D_80107400_DA3F0_Debug = 0;
    mp2__SetFlag(0x19);
    mp2_D_800F93CD_F9FCD = 1; //skips instructions screen

    mp2_omInitObjMan(0x32, 0);
    mp2_func_80102D54_D5D44_Debug(2300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    mp2_func_80026D28_27928(1);
    mp2_func_80026DAC_279AC(0, 0x80, 0x80, 0x80);
    mp2_func_80026DAC_279AC(1, 0x60, 0x60, 0x10);
    mp2_func_80026E00_27A00(1, 100.0f, -100.0f, 100.0f);
    
    mp2_omOvlCallEx(func_8003F6F0_402F0(mp2_D_800F93A8.unk_20), 0, 0x84);
}