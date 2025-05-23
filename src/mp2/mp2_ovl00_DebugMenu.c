#include "mp2.h"
//fully decompiled boot logos overlay

void mp2_func_80102950_36DAF0_DebugMenu(mp2_omObjData* arg0);
void mp2_func_80102A6C_36DC0C_DebugMenu(void);
void mp2_func_80102AD8_36DC78_DebugMenu(void);
void mp2_func_80102A04_36DBA4_DebugMenu(void);
void mp2_LoadMinigameList(void);

extern s8 mp2_D_80102708_103308;
extern u16 mp2_D_801011FC_101DFC;
extern u16 mp2_D_8010163C_10223C;

s32 mp2_D_80102D50_36DEF0_DebugMenu = 0;
s32 mp2_D_80102D54_36DEF4_DebugMenu = 0;

mp2_Process* mp2_D_80102D60_36DF00_DebugMenu = 0;

void mp2_DebugMenuSetup(void) {
    mp2_func_80020070_20C70(1);
    mp2_omInitObjMan(16, 4);
    mp2_D_80102708_103308 = 1;

    //this handles how each game is loaded back into
    switch (CurBaseGame) {
    case MP1_BASE:
        ForeignMinigameIndexToLoad = -1;
        ComboSwitchGameToMp1();
        break;
    case MP2_BASE: //this should never happen
        break;
    case MP3_BASE:
        ForeignMinigameIndexToLoad = -1;
        ComboSwitchGameToMp3();
        break;
    }

    // if (mp2_D_80102D50_36DEF0_DebugMenu == 0) {
    //     mp2_func_80068410_69010();
    //     mp2_D_80102D60_36DF00_DebugMenu = mp2_omAddPrcObj(mp2_func_80102AD8_36DC78_DebugMenu, 0xA, 0, 0);
    //     mp2_omAddObj(1000, 0, 0, -1, mp2_func_80102950_36DAF0_DebugMenu);
    // } else {
    //     mp2_D_80102D60_36DF00_DebugMenu = mp2_omAddPrcObj(mp2_func_80102AD8_36DC78_DebugMenu, 0xA, 0, 0);
    //     mp2_omAddObj(1000, 0, 0, -1, mp2_func_80102950_36DAF0_DebugMenu);
    //     mp2_omAddObj(10, 0, 0, -1, mp2_func_80102A6C_36DC0C_DebugMenu);
    // }
}

//this is only ran when we need to return to a different game
void mp2_ovl00EntryFunc(void) {
    mp2_D_80102D50_36DEF0_DebugMenu = 0;
    mp2_DebugMenuSetup(); 
}

void mp2_func_8010292C_36DACC_DebugMenu(void) {
    mp2_D_80102D50_36DEF0_DebugMenu = 1;
    mp2_DebugMenuSetup();
}

void mp2_func_80102950_36DAF0_DebugMenu(mp2_omObjData* arg0) {
    if (((mp2_D_801011FC_101DFC != 0) || (mp2_D_80102D54_36DEF4_DebugMenu != 0)) && (mp2_func_8008F618_90218() == 0)) {
        mp2_func_8008F624_90224(0, 0, 0);
        mp2_InitFadeOut(0, 9);
        arg0->func_ptr = &mp2_func_80102A04_36DBA4_DebugMenu;
        if ((mp2_D_801011FC_101DFC != 0) && (mp2_func_8008F618_90218() == 0)) {
            mp2_func_8008F624_90224(0, 0, 0);
            mp2_InitFadeOut(0, 9);
            arg0->func_ptr = &mp2_func_80102A04_36DBA4_DebugMenu;
        }
    }
}

void mp2_func_80102A04_36DBA4_DebugMenu(void) {
    if (mp2_func_8008F618_90218() == 0) {
        if (mp2_D_80102D50_36DEF0_DebugMenu != 0) {
            mp2_omOvlGotoEx(0x62, 1, 0x193);
            return;
        }
        mp2_omOvlCallEx(0x62, 1, 0x193);
        mp2_omOvlHisChg(1, 0x62, 0, 0x192);
    }
}

void mp2_func_80102A6C_36DC0C_DebugMenu(void) {
    s32 temp_v0;

    if (mp2_func_8008F618_90218() == 0) {
        temp_v0 = mp2_func_80068448_69048();
        if ((temp_v0 == 1) && (mp2_HuGetPadInserted(0) != 0) && (mp2_D_8010163C_10223C & 0x1000)) {
            mp2_D_80102D54_36DEF4_DebugMenu = temp_v0;
        }
    }
}

void mp2_func_80102AD8_36DC78_DebugMenu(void) {
    s16 temp_v0;
    u16 temp_s0;

    temp_v0 = mp2_func_8001A2F8_1AEF8(0x90000);
    temp_s0 = mp2_func_8001AAAC_1B6AC(temp_v0, 0, 1);
    mp2_espPosSet(temp_s0, 0xA0, 0x78);
    mp2_espDispOn(temp_s0);
    mp2_func_8001A788_1B388(temp_s0, 0xFFFF);
    mp2_InitFadeIn(0, 0x1E);
    while (mp2_func_8008F618_90218() != 0) {
        mp2_HuPrcVSleep();
    }
    mp2_HuPrcSleep(45);
    mp2_InitFadeOut(0, 9);
    
    while (mp2_func_8008F618_90218() != 0) {
        mp2_HuPrcVSleep();
    }
    
    mp2_func_8001AC44_1B844(temp_s0);
    mp2_SprAnimKill(temp_v0);
    mp2_HuPrcSleep(9);
    temp_v0 = mp2_func_8001A2F8_1AEF8(0x90001);
    temp_s0 = mp2_func_8001AAAC_1B6AC(temp_v0, 0, 1);
    mp2_espPosSet(temp_s0, 0xA0, 0x78);
    mp2_espDispOn(temp_s0);
    mp2_func_8001A788_1B388(temp_s0, -1);
    mp2_InitFadeIn(0, 9);
    
    while (mp2_func_8008F618_90218() != 0) {
        mp2_HuPrcVSleep();
    }
    mp2_HuPrcSleep(45);
    mp2_InitFadeOut(0, 9);
    
    while (mp2_func_8008F618_90218() != 0) {
        mp2_HuPrcVSleep();
    }
    
    mp2_func_8001AC44_1B844(temp_s0);
    mp2_SprAnimKill(temp_v0);
    mp2_HuPrcSleep(9);
    temp_s0 = mp2_func_8001AAAC_1B6AC(mp2_func_8001A2F8_1AEF8(0x90002), 0, 1);
    mp2_espPosSet(temp_s0, 0xA0, 0x78);
    mp2_espDispOn(temp_s0);
    mp2_func_8001A788_1B388(temp_s0, -1);
    mp2_InitFadeIn(0, 9);
    
    while (mp2_func_8008F618_90218() != 0) {
        mp2_HuPrcVSleep();
    }
    
    mp2_HuPrcSleep(45);
    mp2_D_801011FC_101DFC = 1;
    while (1) {
        mp2_HuPrcVSleep();
    }
}
