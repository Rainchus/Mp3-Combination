//new functions for the boot logo overlay

#include "marioparty.h"
#include "mp3.h"

void func_80105AF0_3D72A0_name_58(mp3_omObjData*);
void func_80105C80_3D7430_name_58(void);
void func_80105BA4_3D7354_name_58(mp3_omObjData*);
void mp3_BootLogosSetup(void);
void func_80105C14_3D73C4_name_58(mp3_omObjData*);
void InitializeInitialMinigameList(void);

extern s8 mp3_D_800D6A58_D7658;

mp3_Process* mp3_D_80105F10_3D76C0_name_58 = 0;

/* .data */
s32 D_80105F00_3D76B0_name_58 = 0; //if no controller
s32 D_80105F04_3D76B4_name_58 = 0;

static omOvlHisData LoadIntoResultsSceneHis[] = {
    0x0000007A, 0x0002, 0x0092,
    0x0000007A, 0x0002, 0x0092,
    0x00000077, 0x0000, 0x0091,
    0x00000047, 0x0001, 0x0192, //the 0x47 here is the board overlay ID. it gets replaced 
};

void mp3_BootLogosSetup(void) {
    mp3_Hu3DCamInit(1);
    mp3_omInitObjMan(0x10, 4);
    mp3_D_800D6A58_D7658 = 1;

    InitializeInitialMinigameList();
    mp3_LoadMinigameList();
    
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
    mp3_LoadMinigameList();

    //we are loading from another game, determine if we should load minigame or boot back into original game
    if (CurBaseGame != MP3_BASE) {
        if (ForeignMinigameIndexToLoad == -1) { //we already loaded the minigame, go back to original game

        } else { //first time booting in from foreign mario party game, load minigame

        }
        return;
    }

    //base game is mp3, check action to do
    if (ForeignMinigameIndexToLoad == -2) { //normal boot into mp3 with boot sequences
        D_80105F00_3D76B0_name_58 = 0;
        mp3_BootLogosSetup();        
    } else if (ForeignMinigameIndexToLoad != -1) {
        //we have loaded into the boot overlay and do not have a minigame to load
        //therefore, we need to load into the results scene to then load back into the board
        //set up the necessary overlay history to accomplish this
        omOvlHisData resultsSceneHis[5];
        for (int i = 0; i < ARRAY_COUNT(LoadIntoResultsSceneHis); i++) {
            resultsSceneHis[i] = LoadIntoResultsSceneHis[i];
        }
        ForeignMinigameIndexToLoad = -1;
        resultsSceneHis[3].overlayID = 0x47; //set overlay ID for board
        mp3_omOvlCallEx(0x71, 0x0000, 0x12); //load results scene overlay
    } else { //else, coming from another game, load mp3 minigame

    }
}

void func_80105ACC_3D727C_name_58(void) {
    D_80105F00_3D76B0_name_58 = 1; //set no controller
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
