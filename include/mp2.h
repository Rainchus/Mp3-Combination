#ifndef _MP2_H_
#define _MP2_H_

#include "ultra64.h"
#include "marioparty.h"

typedef struct {
    /* 0x00 */ s16 unk_2E;
    /* 0x02 */ u8  unk_30[6];
} GwCommonEntry; // size = 0x8

//probably a lot wrong here; mostly copied from mp3 then edited (however the size is correct)
typedef struct mp2_GW_COMMON {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 languageIndex;
    /* 0x02 */ u16 mgRecord[8];
    /* 0x12 */ char pad12[4];
    /* 0x16 */ u8 mgUnlock[7];
    /* 0x30 */ u8 unk_1D[0x10];
    /* 0x2E */ GwCommonEntry entries[6];
    /* 0x60 */ char unk_60[0x10];
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s16 unk74;                             /* inferred */
    /* 0x76 */ u8 unk76;                             /* inferred */
    /* 0x77 */ u8 unk77;                             /* inferred */
    /* 0x78 */ u8 pad78;
    /* 0x79 */ u8 pad79;
    /* 0x7A */ u8 unk7A;
    /* 0x7B */ char pad7B[0x14];                    /* maybe part of unk77[0x15]? */
    /* 0x8F */ u8 flag[0xC];
    /* 0x9B */ char pad9B[7];
    /* 0xA2 */ s8 unk9E;
    /* 0xA3 */ s8 unk9F;
    /* 0xA4 */ s8 unkA0;
    /* 0xA5 */ s8 unkA1;
    /* 0xA6 */ s8 unkA2;
    /* 0xA7 */ char padA7[0x1D];
} mp2_GW_COMMON;                                        /* size = 0xC4 */    

extern mp2_GW_COMMON mp2_GwCommon;

typedef struct {
    u8 unk0[8];
    s8 recentMinigames[6][5]; /* recent minigames per player, up to 2 */
} UnkData_E0290;

typedef struct Unk800DF6B6 {
    s8 unk_00[6];
} Unk800DF6B6;

extern UnkData_E0290 D_800DF690_E0290;
extern Unk800DF6B6 D_800DF6B6_E02B6;

void mp2_func_8004CA14_4D614(s32, s32);
void mp2_func_8006135C_61F5C(s32, s32, s32);
u32 mp2_osGetCount(void);
void mp2_StoreBattleMinigameCoins(void);
s32 mp2_func_8007ee0c_7fa0c(void*, void*, void*, s32);
s32 mp2_omOvlCallEx(s32 overlayID, s16 event, s16 stat);
void mp2__ClearFlag(s32);
s32 mp2__CheckFlag(s32);
s32 mp2_omOvlGotoEx(s32, s16, u16);
void mp2_omInitObjMan(s32, s32);
mp2_omObjData* mp2_omAddObj(s16, u16, u16, s16, void*);
void mp2_PlayMusic(s16);
s32 mp2_func_80018E78_19A78(void); //get current cam index
void mp2_func_800202DC_20EDC(s32, f32, f32, f32);
void mp2_omSetStatBit(mp2_omObjData *obj, u16 stat);
void mp2_func_80079E60_7AA60(void);
void mp2_ScissorSet(u8 arg0, f32 x1, f32 y1, f32 x2, f32 y2);
void mp2_ViewportSet(u8, f32, f32, f32, f32, f32, f32);
void mp2_func_80018E30_19A30(s32);
void mp2_func_80020070_20C70(s32);
void mp2_func_80068410_69010(void);
void mp2_func_8008F624_90224(s32, s32, s32);
s32 mp2_HuGetPadInserted(s32);
s32 mp2_func_80068448_69048(void);
void mp2_SprAnimKill(s16);
s16 mp2_func_8001A2F8_1AEF8(s32);
void mp2_espDispOn(s32);
void mp2_espPosSet(s32, s32, s32);
void mp2_func_8001A788_1B388(s32, u16);
s32 mp2_func_8001AAAC_1B6AC(s16, s32, s32);
void mp2_func_8001AC44_1B844(u16);
s32 mp2_func_8008F618_90218(void);
void mp2_InitFadeIn(s32, s32);
void mp2_InitFadeOut(s32, s32);
void mp2_omOvlHisChg(s16 arg0, s32 overlay, s16 event, s16 stat);
void mp2_HuPrcVSleep(void);
void mp2_func_80079294_79E94(void);
void mp2_func_80077EF0_78AF0(void);
void mp2_func_8007B9B8_7C5B8(void);
void mp2_func_8007BA44_7C644(void);
void mp2_func_8008CE5C_8DA5C(void);
void mp2_ClearPlayerCoinsMgAndMgBonus(void);
void mp2_func_80067EF8_68AF8(s32);
void mp2_func_80017800_18400(s32);
void mp2_omOvlKill(void);
void mp2_omOvlHisChg(s16 arg0, s32 overlay, s16 event, s16 stat);
void PushMp2BoardState(void);
void PushMp2MinigamesPlayedList(void);

extern u16 mp2_BattleMinigameCoins;
extern s16 mp2_D_800E1F50_E2B50;
extern s16 mp2_D_801148F0_3D0050_name_60;
extern s16 mp2_D_801148F2_3D0052_name_60;
extern s16 mp2_D_8011497A_3D00DA_name_60;
extern s32 mp2_D_8011497C_3D00DC_name_60;
extern s32 mp2_D_80114980_3D00E0_name_60;
extern s32 mp2_D_80114984_3D00E4_name_60;
extern u16 mp2_D_800CD416_CE016;
extern s16 mp2_D_800E2132_E2D32;
extern u16 mp2_D_800E2134_E2D34;
extern s16 mp2_D_800E2136_E2D36;
extern u32 mp2_D_800FA63C_FB23C;
extern u32 mp2_D_80101650_102250;
extern s8 mp2_D_80102708_103308;
extern u16 mp2_D_801011FC_101DFC;
extern u16 mp2_D_8010163C_10223C;
extern f32 mp2_D_800FA610_FB210;
extern Vec mp2_D_800FD474_FE074;
extern Vec mp2_D_8010274C_10334C;
extern omOvlHisData mp2_omovlhis[12];
extern s16 mp2_omovlhisidx;
extern s16 mp2_omovlhisidx_copy;
extern mp2_GW_PLAYER mp2_GwPlayerCopy[4];
extern s16 mp2_hidden_block_coins_space_index;
extern s16 mp2_hidden_block_star_space_index;
extern mp2_GW_SYSTEM mp2_GwSystemCopy;
extern s16 mp2_BattleMinigameCoins_Copy;
extern s32 mp2_DrawPrevMinigameList;
extern mp2_GW_SYSTEM mp2_GwSystem;

typedef struct UnkomOvl {
    s32 unk_00;
    u16 unk_04;
    char unk_06[2]; //unused pad?
} UnkomOvl;

extern UnkomOvl mp2_D_800CAD90[]; //matches D_800A1920_A2520 in mp3
extern s16 mp2_D_800F8D18[];

typedef struct mp2_jump_buf
{
    void *sp;
    void *func;
    u32 regs[21];
} mp2_jump_buf;

typedef void (*process_func)();

typedef struct mp2_Process {
/* 0x00 */ struct mp2_Process *next;
/* 0x04 */ struct mp2_Process *youngest_child;
/* 0x08 */ struct mp2_Process *oldest_child;
/* 0x0C */ struct mp2_Process *relative;
/* 0x10 */ struct mp2_Process *parent_oldest_child;
/* 0x14 */ struct mp2_Process *new_process;
/* 0x18 */ void *heap;
/* 0x1C */ u16 exec_mode;
/* 0x1E */ u16 stat;
/* 0x20 */ u16 priority;
/* 0x22 */ s16 dtor_idx;
/* 0x24 */ s32 sleep_time;
/* 0x28 */ void *base_sp;
/* 0x2C */ mp2_jump_buf prc_jump;
/* 0x88 */ process_func destructor;
/* 0x8C */ void *user_data;
} mp2_Process; //sizeof 0x90

mp2_Process* mp2_omAddPrcObj(void* userFunc, u16 priority, s32 stack_size, s32 extra_data_size);
void mp2_HuPrcSleep(s32 frames);

#endif
