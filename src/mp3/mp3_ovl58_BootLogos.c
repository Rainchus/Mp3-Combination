//new functions for the boot logo overlay

#include "marioparty.h"
#include "mp3.h"

void func_80105AF0_3D72A0_name_58(mp3_omObjData*);
void func_80105C80_3D7430_name_58(void);
void func_80105BA4_3D7354_name_58(mp3_omObjData*);
void mp3_BootLogosSetup(void);
void func_80105C14_3D73C4_name_58(mp3_omObjData*);

extern s8 mp3_D_800D6A58_D7658;

mp3_Process* mp3_D_80105F10_3D76C0_name_58 = 0;

/* .data */
s32 D_80105F00_3D76B0_name_58 = 0;
s32 D_80105F04_3D76B4_name_58 = 0;

void mp3_BootLogosSetup(void) {
    mp3_Hu3DCamInit(1);
    mp3_omInitObjMan(0x10, 4);
    mp3_D_800D6A58_D7658 = 1;
    
    if (D_80105F00_3D76B0_name_58 == 0) {
        mp3_GWContErrorSet();
        mp3_D_80105F10_3D76C0_name_58 = mp3_omAddPrcObj(func_80105C80_3D7430_name_58, 0xAU, 0, 0);
        mp3_omAddObj(0x3E8, 0U, 0U, -1, func_80105AF0_3D72A0_name_58);
    } else {
        mp3_D_80105F10_3D76C0_name_58 = mp3_omAddPrcObj(func_80105C80_3D7430_name_58, 0xAU, 0, 0);
        mp3_omAddObj(0x3E8, 0U, 0U, -1, func_80105AF0_3D72A0_name_58);
        mp3_omAddObj(0xA, 0U, 0U, -1, func_80105C14_3D73C4_name_58);
    }
}

void mp3_BootLogosEntryFunc(void) {
    D_80105F00_3D76B0_name_58 = 0;
    mp3_BootLogosSetup();
}

void func_80105ACC_3D727C_name_58(void) {
    D_80105F00_3D76B0_name_58 = 1;
    mp3_BootLogosSetup();
}

void func_80105AF0_3D72A0_name_58(mp3_omObjData* arg0) {
    if (((mp3_D_800D530C_D5F0C != 0) || (D_80105F04_3D76B4_name_58 != 0)) && (mp3_WipeStatGet() == 0)) {
        mp3_WipeColorSet(0U, 0U, 0U);
        mp3_WipeCreateOut(0xB, 9);
        arg0->func = &func_80105BA4_3D7354_name_58;
        
        if ((mp3_D_800D530C_D5F0C != 0) && (mp3_WipeStatGet() == 0)) {
            mp3_WipeColorSet(0U, 0U, 0U);
            mp3_WipeCreateOut(0xB, 9);
            arg0->func = &func_80105BA4_3D7354_name_58;
        }
    }
}

void func_80105BA4_3D7354_name_58(mp3_omObjData* arg0) {
    if (mp3_WipeStatGet() == 0) {
        mp3_func_8005F524_60124();
        if (D_80105F00_3D76B0_name_58 != 0) {
            mp3_omOvlGotoEx(0x7A, 2, 0x92U);
            return;
        }
        mp3_omOvlCallEx(0x7A, 2, 0x92U);
        mp3_omOvlHisChg(1, 0x7A, 2, 0x92);
    }
}

void func_80105C14_3D73C4_name_58(mp3_omObjData* arg0) {
    s32 temp_v0;

    if (mp3_WipeStatGet() == 0) {
        temp_v0 = mp3_GWContErrorGet();
        if ((temp_v0 == 1) && (mp3_CheckControllerRead(0) != 0) && (mp3_D_800D5558_D6158[0] & 0x1000)) {
            D_80105F04_3D76B4_name_58 = temp_v0;
        }
    }
}

void func_80105C80_3D7430_name_58(void) {
    u16 temp_v0;
    u16 temp_v0_3;
    u16 temp_s0_3;
    u16 temp_v0_2;
    u16 temp_v0_4;

    temp_v0 = mp3_func_8000B838_C438(0x00110000);
    temp_v0_2 = mp3_InitEspriteSlot(temp_v0, 0, 1);
    mp3_func_8000BBD4_C7D4(temp_v0_2, 0xA0, 0x78);
    mp3_func_8000BB54_C754(temp_v0_2);
    mp3_func_8000BCC8_C8C8(temp_v0_2, 0xFFFF);
    mp3_WipeCreateIn(0xB, 30);

    while (mp3_WipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }
    
    mp3_HuPrcSleep(37);
    mp3_WipeCreateOut(0xB, 9);
    
    while (mp3_WipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }
    
    mp3_func_8000C184_CD84(temp_v0_2);
    mp3_func_80055670_56270(temp_v0);
    mp3_HuPrcSleep(9);
    temp_v0_3 = mp3_func_8000B838_C438(0x00110001);
    temp_v0_4 = mp3_InitEspriteSlot(temp_v0_3, 0, 1);
    mp3_func_8000BBD4_C7D4(temp_v0_4, 0xA0, 0x78);
    mp3_func_8000BB54_C754(temp_v0_4);
    mp3_func_8000BCC8_C8C8(temp_v0_4, 0xFFFF);
    mp3_WipeCreateIn(0xB, 9);
    
    while (mp3_WipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }
    
    mp3_HuPrcSleep(37);
    mp3_WipeCreateOut(0xB, 9);
    
    while (mp3_WipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }
    
    mp3_func_8000C184_CD84(temp_v0_4);
    mp3_func_80055670_56270(temp_v0_3);
    mp3_HuPrcSleep(9);
    temp_s0_3 = mp3_InitEspriteSlot(mp3_func_8000B838_C438(0x110002), 0, 1);
    mp3_func_8000BBD4_C7D4(temp_s0_3, 0xA0, 0x78);
    mp3_func_8000BB54_C754(temp_s0_3);
    mp3_func_8000BCC8_C8C8(temp_s0_3, 0xFFFF);
    mp3_WipeCreateIn(0xB, 9);
    
    while (mp3_WipeStatGet() != 0) {
        mp3_HuPrcVSleep();
    }
    
    mp3_HuPrcSleep(37);
    mp3_D_800D530C_D5F0C = 1;
    
    while (1) {
        mp3_HuPrcVSleep();
    }
}
