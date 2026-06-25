#include "marioparty.h"
#include "mp1.h"

extern u16 mp1_D_800F5144;
extern u16 mp1_ContBtnTrg[4];

extern s32 mp1_D_800F6AF0_LogosSequence;
extern s32 mp1_D_800F6AF4_LogosSequence;

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
void SaveMp1PlayerCopyToMp1Player(void);
void SaveMp1PlayerToMp2PlayerCopy(void);
void SaveMp1PlayerToMp3PlayerCopy(void);
void mp1_LoadMinigameList(void);
s32 mp1_func_80072718(void);
void mp1_func_80072724(u8, u8, u8);
void mp1_func_800726AC(s16 a, s16 b);
void mp1_crash_screen_init(void);
void mp1_omOvlReturnEx(s16);

//TODO: should be in a header file
u8 GetMp3ExplanationSetting(void);
s16 GetMp3BattleMinigameCoins(void);
u8 GetMp2ExplanationSetting(void);

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

void mp1BootLogoMain_ovl66(void) {
    mp1_ExecBoardScene(D_800F6AD0_LogosSequence, mp1_D_800C597A);
}

omOvlHisData mp1_baseOverlays[] = {
    {0x81, 0x0000, 0x0091},
    {0x67, 0x0000, 0x0081}, //boot overlay
    {0x69, 0x0000, 0x0091}, //village
    {0x35, 0x0001, 0x0092}, //handles loading into the board
};

void mp1_LoadMinigameFromBoot(void) {
    #define OVL_RESULTS_SCENE 0x40
    s32 localOverlayID = ForeignMinigameIDToGame(ForeignMinigameIndexToLoad);

    mp1_GwSystem.curMinigame = localOverlayID;

    for (int i = 0; i < ARRAY_COUNT(mp1_baseOverlays); i++) {
        mp1_omovlhis[i] = mp1_baseOverlays[i];
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
    mp1_HuPrcSleep(10); //sleep 10 frames so wipe inits (fixes pop in bugs on minigame loads from boot)
}

void mp1_LoadIntoResultsScene(void) {
    for (int i = 0; i < ARRAY_COUNT(mp1_baseOverlays); i++) {
        mp1_omovlhis[i] = mp1_baseOverlays[i];
    }

    PopMp1BoardState();
    SaveMp1PlayerCopyToMp1Player();

    //if game should end, make overlay results scene returns to the ending game scene
    //otherwise, go to board
    if (mp1_GwSystem.currentTurn > mp1_GwSystem.maxTurns) {
        mp1_omovlhisidx = 3;
        mp1_D_800D86B0 = 0; //related to overlay loading; needs to be 0 for end game
        mp1_omovlhisidx++;
        mp1_omOvlHisChg(0, 0x43, 0, 0x92); //push end game scene event
        mp1_omOvlCallEx(0x7C, 0x0000, 0x14); //load results scene overlay (after minigame)
        return;
    } else if ((mp1_GwSystem.currentTurn + 4 == mp1_GwSystem.maxTurns)) { //TODO: has no midturn mingame check. Unsure if wanted but possibly in the future
        mp1_D_800D86B0 = 1;  //related to overlay loading; needs to be 1 if not going into end game (where winner is decided)
        mp1_omovlhisidx = 3;
        mp1_omovlhisidx++; //add 1 to push last 5 turns event to ovl history
        mp1_omOvlHisChg(0, 0x3F, 0, 0x92); //push last 5 turns event
        mp1_omOvlCallEx(0x7C, 0x0000, 0x14); //load results scene overlay (after minigame)
        return;
    } else { //set overlay ID for board
        mp1_D_800D86B0 = 1; //related to overlay loading; needs to be 1 if not going into end game (where winner is decided)
        mp1_omovlhisidx = 3;
        mp1_omOvlCallEx(0x7C, 0x0000, 0x14); //load results scene overlay (after minigame)
    }
}

// void mp1_LoadIntoResultsScene(void) {
//     for (int i = 0; i < ARRAY_COUNT(mp1_baseOverlays); i++) {
//         mp1_omovlhis[i] = mp1_baseOverlays[i];
//     }

//     PopMp1BoardState();
//     SaveMp1PlayerCopyToMp1Player();

//     //if game should end, make overlay results scene returns to the ending game scene
//     //otherwise, go to board
//     if (mp1_GwSystem.currentTurn > mp1_GwSystem.maxTurns) {
//         mp1_omovlhisidx = 2;
//         mp1_D_800D86B0 = 0; //related to overlay loading; needs to be 0 for end game
//         mp1_omovlhisidx++;
//         mp1_omOvlHisChg(0, 0x43, 0, 0x92); //push end game scene event
//     } else if (mp1_GwSystem.currentTurn + 4 == mp1_GwSystem.maxTurns) {
//         mp1_D_800D86B0 = 1;  //related to overlay loading; needs to be 1 if not going into end game (where winner is decided)
//         mp1_omovlhisidx = 2;
//         mp1_omovlhisidx++; //add 1 to push last 5 turns event to ovl history
//         mp1_omOvlHisChg(0, 0x3F, 0, 0x92); //push last 5 turns event
//     } else { //set overlay ID for board
//         mp1_D_800D86B0 = 1; //related to overlay loading; needs to be 1 if not going into end game (where winner is decided)
//         mp1_omovlhisidx = 2;
//     }

//     mp1_omOvlCallEx(0x7C, 0x0000, 0x14); //load results scene overlay (after minigame)
// }

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

// void mp2_BootLogosEntryFunc(void) {
//     mp2_crash_screen_init();
//     mp2_LoadMinigameList();
//     mp2_func_80068410_69010(); //set pad data so title screen functions correctly after game swaps

//     if (CurBaseGame == MP3_BASE) {
//         mp2_GwSystem.minigameExplanations = GetMp3ExplanationSetting();
//         mp2_BattleMinigameCoins = GetMp3BattleMinigameCoins();
//     } else if (CurBaseGame == MP1_BASE) {
//         mp2_GwSystem.minigameExplanations = GetMp1ExplanationSetting();
//     }

//     //this handles if the player waits on the title screen then loads back into the boot overlays
//     if (CurBaseGame == MP2_BASE && mp2_omovlhisidx == 1) {
//         //normal boot into mp3 with boot sequences
//         ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
//         mp2_D_80102D50_36DEF0_BootLogos = 0; //set is initial boot
//         mp2_BootLogosSetup();
//         return;
//     }

//     if (CurBaseGame == MP2_BASE && ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INDEX_BOOT_VAL) {
//         //normal boot into mp2 with boot sequences
//         ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
//         mp2_D_80102D50_36DEF0_BootLogos = 0; //set is initial boot
//         mp2_BootLogosSetup();        
//     } else if (CurBaseGame == MP2_BASE && ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INVALID_ID) {
//         //mp2 is the base game and we have loaded into the boot overlay with no minigame to load
//         //therefore, we need to load into the results scene to then load back into the board
//         //set up the necessary overlay history to accomplish this
//         mp2_LoadIntoResultsScene();
//     } else { //isn't mp2 base, load minigame or boot back into original game
//         if (ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INVALID_ID) {
//             //just played mp2 minigame, load back into original game
//             mp2_LoadOriginalGame();
//         } else { //load into minigame from boot
//             mp2_LoadMinigameFromBoot();
//         }
//     }
// }

void mp1_BootLogosEntryFunc(void) {
    mp1_crash_screen_init();
    mp1_LoadMinigameList();

    if (CurBaseGame == MP3_BASE) {
        mp1_GwSystem.minigameExplanation = GetMp3ExplanationSetting();
    } else if (CurBaseGame == MP2_BASE) {
        mp1_GwSystem.minigameExplanation = GetMp2ExplanationSetting();
    }

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
}

void mp1_BootLogosEntryFunc2(void) {
    mp1_crash_screen_init();
    mp1_LoadMinigameList();

    if (CurBaseGame == MP3_BASE) {
        mp1_GwSystem.minigameExplanation = GetMp3ExplanationSetting();
    } else if (CurBaseGame == MP2_BASE) {
        mp1_GwSystem.minigameExplanation = GetMp2ExplanationSetting();
    }

    //this handles if the player waits on the title screen then loads back into the boot overlays
    if (CurBaseGame == MP1_BASE && mp1_omovlhisidx == 1) {
        // //tldr; ovl66 and ovl67 were combined into 1 and this allows this to happen by properly returning after the cutscene where the characters jump into the pipe
        // if (ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INVALID_ID) {
        //     mp1_omovlhisidx = -1;
        //     mp1_omOvlCallEx(0x82, 0, 0x91);
        //     return;
        // }
        //normal boot into mp3 with boot sequences
        ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
        mp1_D_800F6AF0_LogosSequence = 1; //set is NOT initial boot
        mp1_BootLogosSetup();
        return;
    }

    if (CurBaseGame == MP1_BASE && ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INDEX_BOOT_VAL) {
        //normal boot into mp1 with boot sequences
        ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
        mp1_D_800F6AF0_LogosSequence = 1; //set is NOT initial boot
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

