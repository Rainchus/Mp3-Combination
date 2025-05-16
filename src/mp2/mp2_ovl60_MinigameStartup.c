#include "mp2.h"

void mp2_func_80102A14_3BE174_name_60(void);
void mp2_func_80102AF0_3BE250_name_60(void);
void mp2_func_801085A0_3C3D00_name_60(s32);
void mp2_func_80105B94_3C12F4_name_60(void);

extern s16 mp2_D_801148F2_3D0052_name_60;
extern s16 mp2_D_801148F4_3D0054_name_60;
extern s16 mp2_D_80114AC2_3D0222_name_60;

void mp2_func_80102830_3BDF90_name_60(void) {
    s16 var_v0_2;
    s32 temp_s0;
    s32 i;

    mp2_func_80102A14_3BE174_name_60();
    if ((mp2_GwSystem.minigameExplanations == 1)) {
        mp2_func_801085A0_3C3D00_name_60(0);
        return;
    }

    switch (mp2_D_801148F2_3D0052_name_60) {
    case 6:
    case 7:
        mp2_func_801085A0_3C3D00_name_60(0);
        return;
    }

    mp2_PlayMusic(0x16);
    mp2_omSetStatBit(mp2_omAddObj(0x7FDA, 0U, 0U, -1, &mp2_func_80079E60_7AA60), 0xA0);
    mp2_func_80018E30_19A30(1);
    temp_s0 = mp2_func_80018E78_19A78();
    mp2_ScissorSet(temp_s0, 0.0f, 0.0f, 320.0f, 240.0f);
    mp2_ViewportSet(temp_s0, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    mp2_func_800202DC_20EDC(0, 10.0f, 500.0f, 5000.0f);
    mp2_D_800FA610_FB210 = 2500.0f;

    mp2_D_800FD474_FE074.x = 0;
    mp2_D_800FD474_FE074.y = 0;
    mp2_D_800FD474_FE074.z = 0;

    mp2_D_8010274C_10334C.x = 0;
    mp2_D_8010274C_10334C.y = 0;
    mp2_D_8010274C_10334C.z = 0;
    
    mp2_func_80102AF0_3BE250_name_60();
    mp2_omAddPrcObj(&mp2_func_80105B94_3C12F4_name_60, 0x1001U, 0x800, 0);
    
    for (i = 0; i < 4; i++) {
        if (mp2_GwPlayer[i].group == 0) {
            break;
        }
    }

    mp2_D_801148F4_3D0054_name_60 = mp2_D_80114AC2_3D0222_name_60 = i;
    mp2_InitFadeIn(0, 0x10);
}


