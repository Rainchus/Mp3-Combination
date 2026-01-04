#include "mp2.h"

void mp2_func_80102A14_3ABBB4_name_5F(void);
void mp2_func_80102AF0_3ABC90_name_5F(void);
void func_801085A0_3B1740_name_5F(s32);
extern s16 mp2_D_80114DC4_3BDF64_name_5F;
extern s16 mp2_D_80114F70_3BE110_name_5F;
void mp2_func_80105B94_3AED34_name_5F(void);
extern s16 mp2_D_80114DC0_3BDF60_name_5F;
extern s16 mp2_D_80114DC2_3BDF62_name_5F;
extern s16 mp2_D_80114E4A_3BDFEA_name_5F;
extern s32 mp2_D_80114E4C_3BDFEC_name_5F;
extern s32 mp2_D_80114E50_3BDFF0_name_5F;
extern s32 mp2_D_80114E54_3BDFF4_name_5F;
void Mp2SwapGameIfNeeded(void);

void mp2_func_80102830_3AB9D0_name_5F(void) {
    s32 temp_s0;
    s32 i;

    Mp2SwapGameIfNeeded(); //doesn't return if game swap happens
    //if mp3 is base game, load mp3 player copy into mp2 player structs
    if (CurBaseGame == MP3_BASE) {
        LoadMp3PlayerCopyToMp2();
    }
    mp2_func_80102A14_3ABBB4_name_5F();
    if (mp2_GwSystem.minigameExplanations == 1) {
        func_801085A0_3B1740_name_5F(0);
        return;
    }
    switch (mp2_D_80114DC2_3BDF62_name_5F) {
    case 6:
    case 7:
        func_801085A0_3B1740_name_5F(0);
        return;
    }
    
    mp2_PlayMusic(0x16);
    mp2_omSetStatBit(mp2_omAddObj(0x7FDA, 0U, 0U, -1, mp2_func_80079E60_7AA60), 0xA0U);
    mp2_func_80018E30_19A30(1);
    temp_s0 = mp2_func_80018E78_19A78();
    mp2_ScissorSet(temp_s0, 0.0f, 0.0f, 320.0f, 240.0f);
    mp2_ViewportSet(temp_s0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    mp2_func_800202DC_20EDC(0, 10.0f, 500.0f, 5000.0f);
    mp2_D_800FA610_FB210 = 2500.0f;
    mp2_D_800FD474_FE074.x = 0.0f;
    mp2_D_800FD474_FE074.y = 0.0f;
    mp2_D_800FD474_FE074.z = 0.0f;
    mp2_D_8010274C_10334C.x = 0.0f;
    mp2_D_8010274C_10334C.y = 0.0f;
    mp2_D_8010274C_10334C.z = 0.0f;
    mp2_func_80102AF0_3ABC90_name_5F();
    mp2_omAddPrcObj(&mp2_func_80105B94_3AED34_name_5F, 0x1001U, 0x800, 0);
    
    for (i = 0; i < 4; i++) {
        if (mp2_GwPlayer[i].group == 0) {
            break;
        }
    }
    
    mp2_D_80114DC4_3BDF64_name_5F = mp2_D_80114F70_3BE110_name_5F = i;
    mp2_InitFadeIn(0, 0x10);
}

void func_801085A0_3B1740_name_5F(s32 arg0) {
    s16 minigameOverlayID;

    mp2_func_8008CE5C_8DA5C();
    if (CurBaseGame == MP2_BASE) {
        mp2_func_800727F0_733F0();
    }
    mp2_func_80067EF8_68AF8(-1);
    
    if (arg0 != 0) {
        mp2_func_80017800_18400(mp2_D_80114E54_3BDFF4_name_5F);
        mp2_func_80017800_18400(mp2_D_80114E4C_3BDFEC_name_5F);
        mp2_func_80017800_18400(mp2_D_80114E50_3BDFF0_name_5F);
        mp2_omOvlKill();
    }
    
    if (mp2_D_80114E4A_3BDFEA_name_5F != 0) {
        mp2_omOvlCallEx(mp2_D_800CAD90[mp2_D_80114DC0_3BDF60_name_5F].unk_00, 0, 0x14);
        minigameOverlayID = mp2_func_8003F6F0_402F0(mp2_GwSystem.chosenMinigameIndex);
        mp2_omOvlHisChg(1, minigameOverlayID, 0, 0x14);
        return;
    } 
    
    mp2__ClearFlag(0x15);
    if ((mp2__CheckFlag(0x13) != 0) || !(mp2__CheckFlag(0xC) == 0)) {
        mp2_omOvlGotoEx(mp2_D_800CAD90[mp2_D_80114DC0_3BDF60_name_5F].unk_00, 0, 0x14);
        return;
    }
    
    switch (mp2_D_80114DC2_3BDF62_name_5F) {
        case 6:
        case 5:
        case 4:
            mp2_omOvlGotoEx(mp2_D_800CAD90[mp2_D_80114DC0_3BDF60_name_5F].unk_00, 0, 0x14);
            return;
        case 7:
            mp2_GwSystem.current_board_index = (u16) mp2_D_80114DC0_3BDF60_name_5F - 0x3A;
            mp2_D_800F8D18[2] = 1;
            mp2_D_800F8D18[1] = 0xE;
            mp2_omOvlGotoEx(mp2_D_800CAD90[mp2_D_80114DC0_3BDF60_name_5F].unk_00, 0, 0x12);
            return;
            
        case 3:
            mp2_omOvlCallEx(mp2_D_800CAD90[mp2_D_80114DC0_3BDF60_name_5F].unk_00, 0, 0x14);
            if (CurBaseGame == MP2_BASE) {
                mp2_omOvlHisChg(1, 0x6F, 0, 0x14); //original code; push battle results scene to history
            } else {
                mp2_omOvlHisChg(1, 0x57, 0, 0x14); //push boot logos overlay (has logic for returning to original game)
            }
            return;
    }

    mp2_omOvlCallEx(mp2_D_800CAD90[mp2_D_80114DC0_3BDF60_name_5F].unk_00, 0, 0x14);
    if (CurBaseGame == MP2_BASE) {
        mp2_omOvlHisChg(1, 0x70, 0, 0x14); //original code; push results scene to history
    } else {
        mp2_omOvlHisChg(1, 0x57, 0, 0x14); //push boot logos overlay (has logic for returning to original game)
    }
}