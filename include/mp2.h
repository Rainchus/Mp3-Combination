#ifndef _MP2_H_
#define _MP2_H_

#include "ultra64.h"
#include "marioparty.h"

typedef struct mp2_GW_SYSTEM {
    /* 0x00 - 800F93A8 */ s16 unk_00;
    /* 0x02 - 800F93AA */ s16 current_board_index;
    /* 0x04 - 800F93AC */ s16 current_game_length; // 00=Lite Play,01=Standard Play,02=Full Play,03=Custom Play
    /* 0x06 - 800F93AE */ s16 total_turns;
    /* 0x08 - 800F93B0 */ s16 current_turn;
    /* 0x0A - 800F93B2 */ s16 unk_0A;
    /* 0x0C - 800F93B4 */ s16 star_spawn_indices[7];
    /* 0x1A - 800F93C2 */ s16 unk_1A;
    /* 0x1C - 800F93C4 */ s16 unk_1C;
    /* 0x1E - 800F93C6 */ s16 current_player_index;
    /* 0x20 - 800F93C8 */ s16 chosenMinigameIndex;
    /* 0x22 - 800F93CA */ s16 curPlayerAbsSpaceIndex;
    /* 0x24 - 800F93CC */ char unk_24[1];
    /* 0x25 - 800F93CD */ s8 minigameExplanations; //0x25
    /* 0x26 - 800F93CE */ char unk_26[2];
} mp2_GW_SYSTEM; //sizeof 0x28?

void mp2_func_8004CA14_4D614(s32, s32);
void mp2_func_8006135C_61F5C(s32, s32, s32);
u32 mp2_osGetCount(void);
void mp2_StoreBattleMinigameCoins(void);
s32 mp2_func_8007ee0c_7fa0c(void*, void*, void*, s32);
s32 mp2_omOvlCallEx(s32 overlayID, s16 event, s16 stat);
s32 mp2_func_8003F6F0_402F0(s32);
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
extern mp2_GW_SYSTEM mp2_GwSystem; //was mp2_BoardState

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
