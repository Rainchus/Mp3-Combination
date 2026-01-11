#include "marioparty.h"
#include "mp1.h"

s32 mp1_D_800F6AF0_LogosSequence = 0;
s32 mp1_D_800F6AF4_LogosSequence = 0;

void mp1_ExecBoardScene(OvlEntrypoint* arg0, s16 arg1);
void mp1_InitCameras(s16 count);
s16 mp1_InitSprite(s32);
void mp1_SetBasicSpritePos(s32, s16, s16);
s32 mp1_func_80019060(s32, s16, s16);
void mp1_ShowBasicSprite(s32);
void mp1_func_80018D84(u16, s32);
void mp1_SetFadeInTypeAndTime(s16 a, s16 b);
void mp1_func_80067704(s16);
s32 mp1_func_800141FC(s16);
void mp1_func_800191F8(s32);
void func_800F6704_LogosSequence(mp1_omObjData* arg0);
void func_800F6774_LogosSequence(void);
void func_800F67E0_LogosSequence(void);
void func_800F686C_LogosSequence(void);

void SaveMp1PlayerToMp2PlayerCopy(void);
void SaveMp1PlayerToMp3PlayerCopy(void);
void mp1_LoadMinigameList(void);
s32 mp1_func_80072718(void);
void mp1_func_80072724(u8, u8, u8);
void mp1_func_800726AC(s16 a, s16 b);

extern u8 mp1_D_800C572F;
mp1_Process* mp1_D_800F6B00_LogosSequence= NULL;
extern s8 mp1_omSysPauseEnableFlag;

void mp1_BootLogosEntryFunc(void);
void mp1_BootLogosEntryFunc2(void);

OvlEntrypoint D_800F6AD0_LogosSequence[] = {
    {0, mp1_BootLogosEntryFunc},
    {1, mp1_BootLogosEntryFunc2},
    {-1, 0},
};

void mp1BootLogoMain(void) {
    mp1_ExecBoardScene(D_800F6AD0_LogosSequence, mp1_D_800C597A);
}

void mp1_LoadMinigameFromBoot(void) {
    #define OVL_RESULTS_SCENE 0x40
    s32 localOverlayID = ForeignMinigameIDToGame(ForeignMinigameIndexToLoad);

    mp1_GwSystem.curMinigame = localOverlayID;

    omOvlHisData ovlHisMinigameExplanation[] = {
        {0x81, 0x0000, 0x0091},
        {0x67, 0x0000, 0x0081}, //boot overlay
    };
    

    for (int i = 0; i < ARRAY_COUNT(ovlHisMinigameExplanation); i++) {
        mp1_omovlhis[i] = ovlHisMinigameExplanation[i];
    }

    mp1_omovlhisidx = 2;
    mp1_omOvlCallEx(0x6F, 0, 0x84); //load instructions overlay
    #undef OVL_RESULTS_SCENE
}

void mp1_BootLogosSetup(void) {
    mp1_InitCameras(1);
    mp1_omInitObjMan(0x10, 4);
    mp1_omSysPauseEnableFlag = 1;
    mp1_D_800F6B00_LogosSequence = mp1_omAddPrcObj(func_800F686C_LogosSequence, 0xA, 0, 0);
    mp1_omAddObj(0x3E8, 0, 0, -1, func_800F6704_LogosSequence);
    if ((mp1_D_800F6AF0_LogosSequence != 0) && (mp1_D_800C572F == 0)) {
        mp1_omAddObj(0xA, 0, 0, -1, func_800F67E0_LogosSequence);
    }
}

void mp1_LoadIntoResultsScene(void) {

}

void mp1_LoadOriginalGame(void) {
    if (CurBaseGame == MP2_BASE) {
        //load into mp2
        // ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
        SaveMp1PlayerToMp2PlayerCopy(); //copy mp1 player structs to mp2's gPlayer Copy
        ComboSwitchGameToMp2();
    } else if (CurBaseGame == MP3_BASE) {
        //load into mp3
        // ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
        SaveMp1PlayerToMp3PlayerCopy(); //copy mp1 player structs to mp3's gPlayer Copy
        ComboSwitchGameToMp3();
    }
    //code should never get here
}

void mp1_BootLogosEntryFunc(void) {
    mp1_LoadMinigameList();

    //this handles if the player waits on the title screen then loads back into the boot overlays
    if (CurBaseGame == MP1_BASE && mp1_omovlhisidx == 1) {
        //normal boot into mp3 with boot sequences
        ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
        mp1_D_800F6AF0_LogosSequence = 0; //set is initial boot
        mp1_BootLogosSetup();
        return;
    }

    if (CurBaseGame == MP1_BASE && ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INDEX_BOOT_VAL) {
        //normal boot into mp1 with boot sequences
        ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
        mp1_D_800F6AF0_LogosSequence = 0; //set is initial boot
        mp1_BootLogosSetup();        
    } else if (CurBaseGame == MP1_BASE && ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INVALID_ID) {
        //mp1 is the base game and we have loaded into the boot overlay with no minigame to load
        //therefore, we need to load into the results scene to then load back into the board
        //set up the necessary overlay history to accomplish this
        mp1_LoadIntoResultsScene();
    } else { //isn't mp1 base, load minigame or boot back into original game
        if (ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INVALID_ID) {
            //just played mp1 minigame, load back into original game
            mp1_LoadOriginalGame();
        } else { //load into minigame from boot
            mp1_LoadMinigameFromBoot();
        }
    }

    // mp1_D_800F6AF0_LogosSequence = 0;
    // mp1_BootLogosSetup();
}

void mp1_BootLogosEntryFunc2(void) {
    mp1_LoadMinigameList();

    //this handles if the player waits on the title screen then loads back into the boot overlays
    if (CurBaseGame == MP1_BASE && mp1_omovlhisidx == 1) {
        //normal boot into mp3 with boot sequences
        ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
        mp1_D_800F6AF0_LogosSequence = 1;
        mp1_BootLogosSetup();
        return;
    }

    if (CurBaseGame == MP1_BASE && ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INDEX_BOOT_VAL) {
        //normal boot into mp1 with boot sequences
        ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
        mp1_D_800F6AF0_LogosSequence = 1;
        mp1_BootLogosSetup();        
    } else if (CurBaseGame == MP1_BASE && ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INVALID_ID) {
        //mp1 is the base game and we have loaded into the boot overlay with no minigame to load
        //therefore, we need to load into the results scene to then load back into the board
        //set up the necessary overlay history to accomplish this
        mp1_LoadIntoResultsScene();
    } else { //isn't mp1 base, load minigame or boot back into original game
        if (ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INVALID_ID) {
            //just played mp1 minigame, load back into original game
            mp1_LoadOriginalGame();
        } else { //load into minigame from boot
            mp1_LoadMinigameFromBoot();
        }
    }
}

extern u16 mp1_D_800F5144;
extern u16 mp1_ContBtnTrg[4];

void func_800F6704_LogosSequence(mp1_omObjData* arg0) {
    if (((mp1_D_800F5144 != 0) || (mp1_D_800F6AF4_LogosSequence != 0)) && (mp1_func_80072718() == 0)) {
        mp1_func_80072724(0, 0, 0);
        mp1_func_800726AC(0, 9);
        arg0->func_ptr = func_800F6774_LogosSequence;
    }
}

void func_800F6774_LogosSequence(void) {
    if (mp1_func_80072718() == 0) {
        if (mp1_D_800F6AF4_LogosSequence != 0) {
            mp1_omOvlGotoEx(0x67, 1, 0x91);
            return;
        }
        mp1_omOvlCallEx(0x61, 0, 0x91);
        mp1_omOvlHisChg(1, 0x81, 0, 0x91);
    }
}

void func_800F67E0_LogosSequence(void) {
    s32 temp_v0;
    s32 i;
    
    if (mp1_func_80072718() == 0) {
        for (i = 0; i < 4; i++) {
            temp_v0 = mp1_func_800141FC(i);
            if (temp_v0 == 1) {
                if (mp1_ContBtnTrg[i] & 0x1000) {
                    mp1_D_800F6AF4_LogosSequence = temp_v0;
                }
                break;
            }
        }
    }
}

void func_800F686C_LogosSequence(void) {
    s16 sprite;
    u16 temp_s0;

    sprite = mp1_InitSprite(0x9006D);
    temp_s0 = mp1_func_80019060(sprite, 0, 1);
    mp1_SetBasicSpritePos(temp_s0, 160, 120);
    mp1_ShowBasicSprite(temp_s0);
    mp1_func_80018D84(temp_s0, 0xFFFF);
    mp1_SetFadeInTypeAndTime(0, 30);
    
    while (mp1_func_80072718() != 0) {
        mp1_HuPrcVSleep();
    }
    
    mp1_HuPrcSleep(0x2D);
    mp1_func_800726AC(0, 9);
    
    while (mp1_func_80072718() != 0) {
        mp1_HuPrcVSleep();
    }
    
    mp1_func_800191F8(temp_s0);
    mp1_func_80067704(sprite);
    mp1_HuPrcSleep(9);
    sprite = mp1_InitSprite(0x9006E);
    temp_s0 = mp1_func_80019060(sprite, 0, 1);
    mp1_SetBasicSpritePos(temp_s0, 0xA0, 0x78);
    mp1_ShowBasicSprite(temp_s0);
    mp1_func_80018D84(temp_s0, 0xFFFF);
    mp1_SetFadeInTypeAndTime(0, 9);
    
    while (mp1_func_80072718() != 0) {
        mp1_HuPrcVSleep();
    }
    
    mp1_HuPrcSleep(0x2D);
    mp1_func_800726AC(0, 9);
    
    while (mp1_func_80072718() != 0) {
        mp1_HuPrcVSleep();
    }
    mp1_func_800191F8(temp_s0);
    mp1_func_80067704(sprite);
    mp1_HuPrcSleep(9);
    temp_s0 = mp1_func_80019060(mp1_InitSprite(0x9006F), 0, 1);
    mp1_SetBasicSpritePos(temp_s0, 0xA0, 0x78);
    mp1_ShowBasicSprite(temp_s0);
    mp1_func_80018D84(temp_s0, 0xFFFF);
    mp1_SetFadeInTypeAndTime(0, 9);
    
    while (mp1_func_80072718() != 0) {
        mp1_HuPrcVSleep();
    }

    mp1_HuPrcSleep(0x2D);
    mp1_D_800F5144 = 1;

    while (1) {
        mp1_HuPrcVSleep();    
    }

}

