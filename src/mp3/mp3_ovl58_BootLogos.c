//new functions for the boot logo overlay

#include "marioparty.h"
#include "mp3.h"
#include "mp3/game/hmfman.h"

#define OVL_RESULTS_SCENE 0x47
#define OVL_GAME_END_SCENE 0x71

void mp3_BootLogosEntryFunc(void);
void mp3_BootLogosEntryFunc2(void);
void func_80105AF0_3D72A0_name_58(mp3_omObjData*);
void func_80105C80_3D7430_name_58(void);
void func_80105BA4_3D7354_name_58(mp3_omObjData*);
void mp3_BootLogosSetup(void);
void func_80105C14_3D73C4_name_58(mp3_omObjData*);
void InitializeInitialMinigameList(void);
void mp3_ovlEventCall(OvlEntrypoint*, s16);
void SaveMp3PlayerToMp1PlayerCopy(void);
void SaveMp3PlayerToMp2PlayerCopy(void);

mp3_Process* mp3_D_80105F10_3D76C0_name_58 = 0;
s32 D_80105F00_3D76B0_name_58 = 0; //if initial boot
s32 D_80105F04_3D76B4_name_58 = 0;

extern s8 mp3_D_800D6A58_D7658;
extern s16 mp3_omovlevtno;

static omOvlHisData LoadIntoResultsSceneHis[] = {
    0x0000007A, 0x0002, 0x0092,
    0x0000007A, 0x0002, 0x0092,
    0x00000077, 0x0000, 0x0091,
    OVL_RESULTS_SCENE, 0x0001, 0x0192, 
};

//overlay table for function to run (loads function index 0 on boot, 1 otherwise)
OvlEntrypoint mp3BootLogosOvlEntry[] = {
    {0, mp3_BootLogosEntryFunc},
    {1, mp3_BootLogosEntryFunc2},
    {-1, NULL},
};

//initial function ran on overlay load (loads another function from mp3BootLogosOvlEntry to run)
void mp3BootLogoMain(void) {
    mp3_ovlEventCall(mp3BootLogosOvlEntry, mp3_omovlevtno);
}

void mp3_LoadMinigameFromBoot(void) {
    s32 localOverlayID = ForeignMinigameIDToGame(ForeignMinigameIndexToLoad);

    mp3_GwSystem.minigame_index = localOverlayID;

    omOvlHisData ovlHisMinigameExplanation[] = {
        {0x7A, 0x0002, 0x0092},
        {0x7A, 0x0002, 0x0092},
        {0x77, 0x0000, 0x0091},
        {OVL_RESULTS_SCENE, 0x0001, 0x0192},
    };

    for (int i = 0; i < ARRAY_COUNT(ovlHisMinigameExplanation); i++) {
        mp3_omovlhis[i] = ovlHisMinigameExplanation[i];
    }

    mp3_omovlhisidx = 3;
    mp3_omOvlCallEx(0x70, 0, 0x0192); //load minigame explanation overlay
}

void mp3_LoadIntoResultsScene(void) {
    for (int i = 0; i < ARRAY_COUNT(LoadIntoResultsSceneHis); i++) {
        mp3_omovlhis[i] = LoadIntoResultsSceneHis[i];
    }

    PopMp3BoardState();
    SaveMp3PlayerCopyToMp3Player();
    mp3_D_800B1A30 = 1; //set that there is at least 1 controller active

    if (mp3_GwSystem.current_turn > mp3_GwSystem.total_turns) {
        //set up credits scene
        mp3_omovlhis[3].overlayID = OVL_RESULTS_SCENE;
        mp3_D_800CD2A2 = 0; //required for credits to correctly go back to game select
        mp3_omovlhisidx = 3;
    } else if (mp3_GwSystem.current_turn - 4 == mp3_GwSystem.total_turns) {
        //set up last 5 turns
        omOvlHisData last5Turns[] = {
            {0x7A, 0x0002, 0x0092},
            {0x7A, 0x0002, 0x0092},
            {0x77, 0x0000, 0x0091},
            {0x47, 0x0001, 0x0192},
            {0x71, 0x0000, 0x0012},
            {0x01, 0x0000, 0x0014},
        };
        //set last 5 turns event
        s32 i;
        for (i = 0; i < ARRAY_COUNT(last5Turns); i++) {
            mp3_omovlhis[i] = last5Turns[i];
        }
        mp3_omovlhisidx = 3;
        mp3_D_800CD2A2 = 1; //required for board events to load back into the board correctly
        // func_800F8610_10C230_Copy(0x48, 2, 0x192, curBoardIndex);
        mp3_omOvlCallEx(0x51, 2, 0x192); //last 5 turns
        return;        
    } else { //else normal board load
        mp3_omovlhis[3].overlayID = OVL_RESULTS_SCENE;
        mp3_D_800CD2A2 = 1; //required for board events to load back into the board correctly
        mp3_omovlhisidx = 3;
    }
    mp3_omOvlCallEx(OVL_GAME_END_SCENE, 0x0000, 0x12); //load results scene overlay
}

void mp3_LoadOriginalGame(void) {
    if (CurBaseGame == MP1_BASE) {
        //load into mp1
        SaveMp3PlayerToMp1PlayerCopy(); //copy mp3 player structs to mp1's gPlayer Copy
        ComboSwitchGameToMp1();
    } else if (CurBaseGame == MP2_BASE) {
        //load into mp2
        SaveMp3PlayerToMp2PlayerCopy(); //copy mp3 player structs to mp2's gPlayer Copy
        ComboSwitchGameToMp2();
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
        ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
        D_80105F00_3D76B0_name_58 = 0; //set is initial boot
        mp3_BootLogosSetup();
        return;
    }

    if (CurBaseGame == MP3_BASE && ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INDEX_BOOT_VAL) {
        //normal boot into mp3 with boot sequences
        ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
        D_80105F00_3D76B0_name_58 = 0; //set is initial boot
        mp3_BootLogosSetup();        
    } else if (CurBaseGame == MP3_BASE && ForeignMinigameIndexToLoad == -1) {
        //mp3 is the base game and we have loaded into the boot overlay with no minigame to load
        //therefore, this means we need to load the "results" scene after a minigame, to then load back into the board
        //set up the necessary overlay history to accomplish this
        mp3_LoadIntoResultsScene();
    } else { //isn't mp3 base, load minigame or boot back into original game
        if (ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INVALID_ID) {
            //just played mp3 minigame, load back into original game
            mp3_LoadOriginalGame();
        } else { //load into minigame from boot
            mp3_LoadMinigameFromBoot();
        }
    }
}

void mp3_BootLogosEntryFunc2(void) {
    mp3_LoadMinigameList();

    //this handles if the player waits on the title screen then loads back into the boot overlays
    if (CurBaseGame == MP3_BASE && mp3_omovlhisidx == 1) {
        //normal boot into mp3 with boot sequences
        ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
        D_80105F00_3D76B0_name_58 = 1; //set not initial boot
        mp3_BootLogosSetup();
        return;
    }

    if (CurBaseGame == MP3_BASE && ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INDEX_BOOT_VAL) {
        //normal boot into mp3 with boot sequences
        ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
        D_80105F00_3D76B0_name_58 = 1; //set not initial boot
        mp3_BootLogosSetup();        
    } else if (CurBaseGame == MP3_BASE && ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INVALID_ID) {
        //mp3 is the base game and we have loaded into the boot overlay with no minigame to load
        //therefore, we need to load into the results scene to then load back into the board
        //set up the necessary overlay history to accomplish this
        mp3_LoadIntoResultsScene();
    } else { //isn't mp3 base, load minigame or boot back into original game
        if (ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INVALID_ID) {
            //load back into original game
            mp3_LoadOriginalGame();
        } else { //load into minigame from boot
            mp3_LoadMinigameFromBoot();
        }
    }
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

void mp3_DrawDebugText(s32 xPos, s32 yPos, char* str);

s32 D_8010D4A4_4E6664_inst = 0x48;
s16 spriteIDs[1] = {-1};

void mp3_Hu3DModelPosSet(s16, f32, f32, f32);
void mp3_Hu3DModelScaleSet(s16, f32, f32, f32);

void DoCustomLogos(void) {
    // void* image0;
    // void* image1;
    // void* image2;
    // void* converted;
    // s32 i;
    // s32 mainFS_ID = 0x00170048;

    // image2 = mp3_DataRead(0x170007);
    // for (i = 0; i < 4; i++, mainFS_ID+= 2) {
    //     image0 = mp3_DataRead(mainFS_ID);
    //     image1 = mp3_DataRead(mainFS_ID+1);
    //     converted = ConvertHVQSToRGBA(image1, image0, image2);
    //     AddToDisplayQueue(converted);
    // }

    // for (s32 i = 0; i < 20; i++) {
    //     mp3_HuPrcSleep(1);
    // }
}

void func_80105C80_3D7430_name_58(void) {
    u16 temp_s0_3;
    // u16 temp_v0;
    // u16 temp_v0_3;
    // u16 temp_s0_3;
    // u16 temp_v0_2;
    // u16 temp_v0_4;

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
