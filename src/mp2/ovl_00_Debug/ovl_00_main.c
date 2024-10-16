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

void mp2_omInitObjMan(s32, s32);
void mp2_func_80079E60_7AA60(void);

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

extern s8 mp2_D_80107400_DA3F0_Debug;
void mp2__SetFlag(s32);
extern s8 mp2_D_800F93CD_F9FCD;
extern u32 mp2_D_800CD408_CE008;
void mp2_func_80102D54_D5D44_Debug(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void mp2_func_80026D28_27928(s32);
void mp2_func_80026DAC_279AC(s32, s32, s32, s32);
void mp2_func_80026E00_27A00(s32, f32, f32, f32);
extern s32 mp2_MinigameIndexToLoad;
extern UnkBoardStatus mp2_D_800F93A8;

//main ovl_00 function. gets ran immediately upon loading the overlay
void func_80102800_D57F0_Debug_2(void) {
    s32 i;

    CopyMp3_gPlayerCopy_To_Mp2();
    
    mp2_D_80107400_DA3F0_Debug = 0;
    mp2__SetFlag(0x19);
    mp2_D_800F93CD_F9FCD = 1; //skips instructions screen
    if (mp2_D_800CD408_CE008 < 0x47U) {
        //award players coins collected during minigame
        for (i = 0; i < 4; i++) {
            s16 totalCoins = mp2_gPlayers[i].coins + mp2_gPlayers[i].extra_coins_collected_during_minigame;
            mp2_gPlayers[i].coins = totalCoins;
            if (totalCoins > 999) {
                mp2_gPlayers[i].coins = 999;
            }
            if (mp2_gPlayers[i].coins < 0) {
                mp2_gPlayers[i].coins = 0;
            }
            mp2_gPlayers[i].extra_coins_collected_during_minigame = 0;
        }
    }
    
    mp2_omInitObjMan(0x32, 0);
    mp2_func_80102D54_D5D44_Debug(2300.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    mp2_func_80026D28_27928(1);
    mp2_func_80026DAC_279AC(0, 0x80, 0x80, 0x80);
    mp2_func_80026DAC_279AC(1, 0x60, 0x60, 0x10);
    mp2_func_80026E00_27A00(1, 100.0f, -100.0f, 100.0f);
    
    //mp2_omAddObj(0x7FDA, 0U, 0U, -1, &mp2_func_80079E60_7AA60);
    //_SetFlag(0xC); //related to who shows up in the minigame explanation

    mp2_D_800F93A8.unk_20 = mp2_MinigameIndexToLoad;
    mp2_D_800F93A8.unk_22 = 0x55;
    // mp2_D_800F93A8.unk_20 = 0x17;
    // mp2_D_800F93A8.unk_22 = 0x55;
    // mp2_gPlayers[1].flags = 1;
    // mp2_gPlayers[2].flags = 1;
    // mp2_gPlayers[3].flags = 1;

    // mp2_gPlayers[1].characterID = 2;
    // mp2_gPlayers[2].characterID = 3;
    // mp2_gPlayers[3].characterID = 4;

    // mp2_gPlayers[0].group = 0;
    // mp2_gPlayers[1].group = 1;
    // mp2_gPlayers[2].group = 1;
    // mp2_gPlayers[3].group = 1;
    mp2_omOvlCallEx(func_8003F6F0_402F0(mp2_D_800F93A8.unk_20), 0, 0x84);
}