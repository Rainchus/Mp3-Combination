#include "mp2.h"

void mp2_func_80102A14_3ABBB4_name_5F(void);
void mp2_func_80102AF0_3ABC90_name_5F(void);
void mp2_func_801085A0_3B1740_name_5F(s32);
extern s16 mp2_D_80114DC4_3BDF64_name_5F;
extern s16 mp2_D_80114F70_3BE110_name_5F;
void mp2_func_80105B94_3AED34_name_5F(void);
extern s16 mp2_D_80114DC0_3BDF60_name_5F;
extern s16 mp2_D_80114DC2_3BDF62_name_5F;
extern s16 mp2_D_80114E4A_3BDFEA_name_5F;
extern s32 mp2_D_80114E4C_3BDFEC_name_5F;
extern s32 mp2_D_80114E50_3BDFF0_name_5F;
extern s32 mp2_D_80114E54_3BDFF4_name_5F;

void func_80102830_3AB9D0_name_5F(void) {
    s32 temp_s0;
    s32 i;

    mp2_func_80102A14_3ABBB4_name_5F();
    if (mp2_GwSystem.minigameExplanations == 1) {
        mp2_func_801085A0_3B1740_name_5F(0);
        return;
    }
    switch (mp2_D_80114DC2_3BDF62_name_5F) {
    case 6:
    case 7:
        mp2_func_801085A0_3B1740_name_5F(0);
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
