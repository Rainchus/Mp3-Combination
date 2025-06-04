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

void mp3_LoadMinigameFromBoot(void) {
    mp3_omOvlCallEx(0x70, 0, 0x192); //load minigame explanation overlay, which then loads the minigame
}

void mp3_LoadIntoResultsScene(void) {
    for (int i = 0; i < ARRAY_COUNT(LoadIntoResultsSceneHis); i++) {
        mp3_omovlhis[i] = LoadIntoResultsSceneHis[i];
    }

    mp3_omovlhis[3].overlayID = 0x47; //set overlay ID for board
    mp3_D_800CD2A2 = 1; //required for board events to load back into the board correctly
    mp3_D_800B1A30 = 1; //set that there is at least 1 controller active
    mp3_omovlhisidx = 3;
    PopMp3BoardState();
    SaveMp3PlayerCopyToMp3Player();
    
    //TODO: verify this call to results scene
    //TODO: set ovlhisidx as well
    mp3_omOvlCallEx(0x71, 0x0000, 0x12); //load results scene overlay
}

void mp3_LoadOriginalGame(void) {
    if (CurBaseGame == MP1_BASE) {
        //load into mp1
    } else if (CurBaseGame == MP2_BASE) {
        //load into mp2
    }
    //code should never get here
}

void mp3_BootLogosSetup(void) {
    mp3_Hu3DCamInit(1);
    mp3_omInitObjMan(0x10, 4);
    mp3_D_800D6A58_D7658 = 1;

    InitializeInitialMinigameList();
    mp3_LoadMinigameList();
    
    if (D_80105F00_3D76B0_name_58 == 0) {
        mp3_GWContErrorSet();
        mp3_D_80105F10_3D76C0_name_58 = mp3_omAddPrcObj(func_80105C80_3D7430_name_58, 0xA, 0, 0);
        mp3_omAddObj(0x3E8, 0U, 0U, -1, func_80105AF0_3D72A0_name_58);
    } else {
        mp3_D_80105F10_3D76C0_name_58 = mp3_omAddPrcObj(func_80105C80_3D7430_name_58, 0xA, 0, 0);
        mp3_omAddObj(0x3E8, 0U, 0U, -1, func_80105AF0_3D72A0_name_58);
        mp3_omAddObj(0xA, 0U, 0U, -1, func_80105C14_3D73C4_name_58);
    }
}

void mp3_BootLogosEntryFunc(void) {
    mp3_LoadMinigameList();

    //this handles if the player waits on the title screen then loads back into the boot overlays
    if (CurBaseGame == MP3_BASE && mp3_omovlhisidx == 1) {
        //normal boot into mp3 with boot sequences
        ForeignMinigameIndexToLoad = -1;
        D_80105F00_3D76B0_name_58 = 0;
        mp3_BootLogosSetup();
        return;
    }

    if (CurBaseGame == MP3_BASE && ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INDEX_BOOT_VAL) {
        //normal boot into mp3 with boot sequences
        ForeignMinigameIndexToLoad = -1;
        D_80105F00_3D76B0_name_58 = 0;
        mp3_BootLogosSetup();        
    } else if (CurBaseGame == MP3_BASE && ForeignMinigameIndexToLoad == -1) {
        //mp3 is the base game and we have loaded into the boot overlay with no minigame to load
        //therefore, we need to load into the results scene to then load back into the board
        //set up the necessary overlay history to accomplish this
        mp3_LoadIntoResultsScene();
    } else { //isn't mp2 base, load minigame or boot back into original game
        if (ForeignMinigameIndexToLoad == -1) {
            //load back into original game
            mp3_LoadOriginalGame();
        } else { //load into minigame from boot
            mp3_LoadMinigameFromBoot();
        }
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

void DoCustomLogos(void) {
    //TODO: fill in logic for custom logos
}

void func_80105C80_3D7430_name_58(void) {
    u16 temp_v0;
    u16 temp_v0_3;
    u16 temp_s0_3;
    u16 temp_v0_2;
    u16 temp_v0_4;

    // temp_v0 = mp3_func_8000B838_C438(0x00110000);
    // temp_v0_2 = mp3_InitEspriteSlot(temp_v0, 0, 1);
    // mp3_func_8000BBD4_C7D4(temp_v0_2, 0xA0, 0x78);
    // mp3_func_8000BB54_C754(temp_v0_2);
    // mp3_func_8000BCC8_C8C8(temp_v0_2, 0xFFFF);
    // mp3_WipeCreateIn(0xB, 30);

    // while (mp3_WipeStatGet() != 0) {
    //     mp3_HuPrcVSleep();
    // }
    
    // mp3_HuPrcSleep(37);
    // mp3_WipeCreateOut(0xB, 9);
    
    // while (mp3_WipeStatGet() != 0) {
    //     mp3_HuPrcVSleep();
    // }
    
    // mp3_func_8000C184_CD84(temp_v0_2);
    // mp3_func_80055670_56270(temp_v0);
    // mp3_HuPrcSleep(9);
    // temp_v0_3 = mp3_func_8000B838_C438(0x00110001);
    // temp_v0_4 = mp3_InitEspriteSlot(temp_v0_3, 0, 1);
    // mp3_func_8000BBD4_C7D4(temp_v0_4, 0xA0, 0x78);
    // mp3_func_8000BB54_C754(temp_v0_4);
    // mp3_func_8000BCC8_C8C8(temp_v0_4, 0xFFFF);
    // mp3_WipeCreateIn(0xB, 9);
    
    // while (mp3_WipeStatGet() != 0) {
    //     mp3_HuPrcVSleep();
    // }
    
    // mp3_HuPrcSleep(37);
    // mp3_WipeCreateOut(0xB, 9);
    
    // while (mp3_WipeStatGet() != 0) {
    //     mp3_HuPrcVSleep();
    // }
    
    // mp3_func_8000C184_CD84(temp_v0_4);
    // mp3_func_80055670_56270(temp_v0_3);
    // mp3_HuPrcSleep(9);
    mp3_HuPrcSleep(9);
    DoCustomLogos();
    //TODO: make this show a combined n64 logo, nintendo logo text, hudson logo text
    //just shows hudson logo text currently
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
