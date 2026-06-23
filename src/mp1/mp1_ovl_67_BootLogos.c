#include "marioparty.h"
#include "mp1.h"

void func_800F6AD4_LogosSequenceCopy(void);
void func_800F6E10_LogosSequenceCopy(void);
void mp1_omOvlReturnEx(s16);

typedef struct UnkStruct {
    char unk_00[0x10];
} UnkStruct; //sizeof 0x10

s32 mp1_func_8000B358(void);
void mp1_func_8006073C(void);
void mp1_func_80063A5C(UnkStruct*);
void mp1_func_800F6778_LogosSequenceCopy(void);
void mp1_func_800F6C1C_LogosSequenceCopy(void);
void mp1_func_800F6C6C_LogosSequenceCopy(void);
s32 mp1_func_800F6CEC_LogosSequenceCopy(void);

extern s32 mp1_D_800F6F70_LogosSequenceCopy;
extern OSMesgQueue mp1_D_800F6FB0_LogosSequenceCopy;
extern void* mp1_D_800F6FC8_LogosSequenceCopy;
void mp1_LoadOriginalGame(void);
u8 GetMp3ExplanationSetting(void);
u8 GetMp2ExplanationSetting(void);
void mp1_ExecBoardScene(OvlEntrypoint* arg0, s16 arg1);
void mp1_LoadMinigameList(void);
void mp1_LoadIntoResultsScene(void);
void mp1_LoadMinigameFromBoot(void);

OvlEntrypoint D_800F6F50_LogosSequenceCopy[] = {
    {0, func_800F6AD4_LogosSequenceCopy},
    {1, func_800F6E10_LogosSequenceCopy},
    {-1, 0},
};

void mp1BootLogoMain_ovl67(void) {
    mp1_ExecBoardScene(D_800F6F50_LogosSequenceCopy, mp1_D_800C597A);
}
void func_800F6AD4_LogosSequenceCopy(void) {
    mp1_omInitObjMan(0xA, 0xA);

    //mp1_crash_screen_init();
    mp1_LoadMinigameList();

    if (CurBaseGame == MP3_BASE) {
        mp1_GwSystem.minigameExplanation = GetMp3ExplanationSetting();
    } else if (CurBaseGame == MP2_BASE) {
        mp1_GwSystem.minigameExplanation = GetMp2ExplanationSetting();
    }

    //this handles if the player waits on the title screen then loads back into the boot overlays
    if (CurBaseGame == MP1_BASE && mp1_omovlhisidx == 1) {
        //normal boot into mp1 with boot sequences
        ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
    } else if (CurBaseGame == MP1_BASE && ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INDEX_BOOT_VAL) {
        //normal boot into mp1 with boot sequences
        //ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;      
    } else if (CurBaseGame == MP1_BASE && ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INVALID_ID) {
        //mp1 is the base game and we have loaded into the boot overlay with no minigame to load
        //therefore, we need to load into the results scene to then load back into the board
        //set up the necessary overlay history to accomplish this
        mp1_LoadIntoResultsScene();
        return;
    } else { //isn't mp1 base, load minigame or boot back into original game
        if (ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INVALID_ID) {
            //just played mp1 minigame, load back into original game
            mp1_LoadOriginalGame();
        } else { //load into minigame from boot
            mp1_LoadMinigameFromBoot();
        }
        return;
    }

    mp1_omOvlGotoEx(0x66, 0, 0x91);
}

void func_800F6E10_LogosSequenceCopy(void) {
    mp1_omInitObjMan(0xA, 0xA);

    //mp1_crash_screen_init();
    mp1_LoadMinigameList();

    if (CurBaseGame == MP3_BASE) {
        mp1_GwSystem.minigameExplanation = GetMp3ExplanationSetting();
    } else if (CurBaseGame == MP2_BASE) {
        mp1_GwSystem.minigameExplanation = GetMp2ExplanationSetting();
    }

    //this handles if the player waits on the title screen then loads back into the boot overlays
    if (CurBaseGame == MP1_BASE && mp1_omovlhisidx == 1) {
        //normal boot into mp1 with boot sequences
        ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
    } else if (CurBaseGame == MP1_BASE && ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INDEX_BOOT_VAL) {
        //normal boot into mp1 with boot sequences
        //ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
    } else if (CurBaseGame == MP1_BASE && ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INVALID_ID) {
        //mp1 is the base game and we have loaded into the boot overlay with no minigame to load
        //therefore, we need to load into the results scene to then load back into the board
        //set up the necessary overlay history to accomplish this
        mp1_LoadIntoResultsScene();
        return;
    } else { //isn't mp1 base, load minigame or boot back into original game
        if (ForeignMinigameIndexToLoad == FOREIGN_MINIGAME_INVALID_ID) {
            //just played mp1 minigame, load back into original game
            mp1_LoadOriginalGame();
        } else { //load into minigame from boot
            mp1_LoadMinigameFromBoot();
        }
        return;
    }
    mp1_omOvlReturnEx(1);
}