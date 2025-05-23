#include "mp2.h"
//fully decompiled boot logos overlay

void mp2_func_80102950_36DAF0_BootLogos(mp2_omObjData* arg0);
void mp2_func_80102A6C_36DC0C_BootLogos(void);
void mp2_func_80102AD8_36DC78_BootLogos(void);
void mp2_func_80102A04_36DBA4_BootLogos(void);
void mp2_LoadMinigameList(void);

extern s8 mp2_D_80102708_103308;
extern u16 mp2_D_801011FC_101DFC;
extern u16 mp2_D_8010163C_10223C;

s32 mp2_D_80102D50_36DEF0_BootLogos = 0;
s32 mp2_D_80102D54_36DEF4_BootLogos = 0;

omOvlHisData LoadIntoResultsSceneHis[] = {

};

mp2_Process* mp2_D_80102D60_36DF00_BootLogos = 0;

void mp2_BootLogosSetup(void) {
    mp2_func_80020070_20C70(1);
    mp2_omInitObjMan(16, 4);
    mp2_D_80102708_103308 = 1;
    if (mp2_D_80102D50_36DEF0_BootLogos == 0) {
        mp2_func_80068410_69010();
        mp2_D_80102D60_36DF00_BootLogos = mp2_omAddPrcObj(mp2_func_80102AD8_36DC78_BootLogos, 0xA, 0, 0);
        mp2_omAddObj(1000, 0, 0, -1, mp2_func_80102950_36DAF0_BootLogos);
    } else {
        mp2_D_80102D60_36DF00_BootLogos = mp2_omAddPrcObj(mp2_func_80102AD8_36DC78_BootLogos, 0xA, 0, 0);
        mp2_omAddObj(1000, 0, 0, -1, mp2_func_80102950_36DAF0_BootLogos);
        mp2_omAddObj(10, 0, 0, -1, mp2_func_80102A6C_36DC0C_BootLogos);
    }
}

void mp2_LoadIntoResultsScene(void) {
    omOvlHisData resultsSceneHis[5];
    for (int i = 0; i < ARRAY_COUNT(LoadIntoResultsSceneHis); i++) {
        resultsSceneHis[i] = LoadIntoResultsSceneHis[i];
    }
    ForeignMinigameIndexToLoad = -1;
    resultsSceneHis[3].overlayID = 0x47; //set overlay ID for board
    mp2_omOvlCallEx(0x71, 0x0000, 0x12); //load results scene overlay
}

void mp2_LoadOriginalGame(void) {
    if (CurBaseGame == MP1_BASE) {
        //load into mp1
    } else if (CurBaseGame == MP3_BASE) {
        //load into mp3
    }
    //code should never get here
}

void mp2_LoadMinigameFromBoot(void) {
    s32 localOverlayID = ForeignMinigameIDToGame(ForeignMinigameIndexToLoad);
    s32 minigameExplanationOverlayID; //this is split into 2 overlays in this game

    if (localOverlayID < 30) {
        minigameExplanationOverlayID = 0x5F;
    } else {
        minigameExplanationOverlayID = 0x60;
    }

    mp2_GwSystem.chosenMinigameIndex = localOverlayID;
    
    omOvlHisData temp[] = {
        0x00000062, 0x0000, 0x0192,
        0x00000062, 0x0000, 0x0192,
        0x0000005B, 0x0000, 0x1014,
        0x0000003D, 0x0001, 0x0192,
    };

    for (int i = 0; i < ARRAY_COUNT(temp); i++) {
        mp2_omovlhis[i] = temp[i];
    }

    mp2_omovlhisidx = 3;
    CopyMp3_gPlayerCopy_To_Mp2();
    mp2_omOvlCallEx(minigameExplanationOverlayID, 0, 0x94); //load minigame explanation overlay
}

void mp2_BootLogosEntryFunc(void) {
    mp2_LoadMinigameList();

    if (CurBaseGame == MP2_BASE && ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INDEX_BOOT_VAL) {
        //normal boot into mp2 with boot sequences
        ForeignMinigameIndexToLoad = -1;
        mp2_D_80102D50_36DEF0_BootLogos = 0;
        mp2_BootLogosSetup();        
    } else if (CurBaseGame == MP2_BASE && ForeignMinigameIndexToLoad == -1) {
        //mp2 is the base game and we have loaded into the boot overlay with no minigame to load
        //therefore, we need to load into the results scene to then load back into the board
        //set up the necessary overlay history to accomplish this
        mp2_LoadIntoResultsScene();
    } else { //isn't mp2 base, load minigame or boot back into original game
        if (ForeignMinigameIndexToLoad == -1) {
            //load back into original game
            mp2_LoadOriginalGame();
        } else { //load into minigame from boot
            mp2_LoadMinigameFromBoot();
        }
    }
}

void mp2_func_8010292C_36DACC_BootLogos(void) {
    mp2_D_80102D50_36DEF0_BootLogos = 1;
    mp2_BootLogosSetup();
}

void mp2_func_80102950_36DAF0_BootLogos(mp2_omObjData* arg0) {
    if (((mp2_D_801011FC_101DFC != 0) || (mp2_D_80102D54_36DEF4_BootLogos != 0)) && (mp2_func_8008F618_90218() == 0)) {
        mp2_func_8008F624_90224(0, 0, 0);
        mp2_InitFadeOut(0, 9);
        arg0->func_ptr = &mp2_func_80102A04_36DBA4_BootLogos;
        if ((mp2_D_801011FC_101DFC != 0) && (mp2_func_8008F618_90218() == 0)) {
            mp2_func_8008F624_90224(0, 0, 0);
            mp2_InitFadeOut(0, 9);
            arg0->func_ptr = &mp2_func_80102A04_36DBA4_BootLogos;
        }
    }
}

void mp2_func_80102A04_36DBA4_BootLogos(void) {
    if (mp2_func_8008F618_90218() == 0) {
        if (mp2_D_80102D50_36DEF0_BootLogos != 0) {
            mp2_omOvlGotoEx(0x62, 1, 0x193);
            return;
        }
        mp2_omOvlCallEx(0x62, 1, 0x193);
        mp2_omOvlHisChg(1, 0x62, 0, 0x192);
    }
}

void mp2_func_80102A6C_36DC0C_BootLogos(void) {
    s32 temp_v0;

    if (mp2_func_8008F618_90218() == 0) {
        temp_v0 = mp2_func_80068448_69048();
        if ((temp_v0 == 1) && (mp2_HuGetPadInserted(0) != 0) && (mp2_D_8010163C_10223C & 0x1000)) {
            mp2_D_80102D54_36DEF4_BootLogos = temp_v0;
        }
    }
}

void mp2_func_80102AD8_36DC78_BootLogos(void) {
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
