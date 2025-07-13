#include "mp3.h"

typedef struct MinigameTable {
    u8 minigameType;
    char unk_01[0x13];
} MinigameTable;

extern MinigameTable mp3_D_800A6D44_A7944[];

void mp3_func_80105D9C_4DEF5C_name_70(mp3_omObjData*);      /* extern */
void mp3_func_801061EC_4DF3AC_name_70(void);                   /* extern */
void mp3_func_80106310_4DF4D0_name_70(mp3_omObjData*);      /* extern */
void mp3_func_80106388_4DF548_name_70(void);                   /* extern */
void mp3_func_8010674C_4DF90C_name_70(mp3_omObjData*);      /* extern */
void mp3_func_801067CC_4DF98C_name_70(void);                   /* extern */
void mp3_func_80106850_4DFA10_name_70(Vec*, Vec*);             /* extern */
void mp3_func_80106898_4DFA58_name_70(void);                   /* extern */
void mp3_func_80106EB4_4E0074_name_70(void);                   /* extern */
void mp3_func_80107308_4E04C8_name_70(void);                   /* extern */
void mp3_func_80107470_4E0630_name_70(void);                /* extern */
void mp3_func_80108350_4E1510_name_70(void);                /* extern */
void mp3_func_801094B0_4E2670_name_70(void);                /* extern */
void mp3_func_80109A90_4E2C50_name_70(void);                /* extern */
void mp3_func_8010A1D0_4E3390_name_70(void);                /* extern */
void mp3_func_8010B990_4E4B50_name_70(void);                /* extern */
void LoadMp2PlayerCopyToMp3(void);
s16 mp3_GWMgUnlockCheck(s16 arg0);
void mp3__ClearFlag(s32 flag);
void mp3_Hu3DAnimInit(s32);
void mp3_func_8005A6B0_5B2B0(void);
void mp3_func_8000B5F0_C1F0(u8 arg0);
void mp3_ScissorSet(u8 camIndex, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void mp3_ViewportSet(u8 camIndex, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6);
void mp3_Hu3DCamSetPerspective(s16 camIndex, f32 fov, f32 near, f32 far);
void mp3_func_800142A0_14EA0(s32);
void mp3_HmfLightColorSet(s32, s32, s32, s32);
void SaveMp3PlayerStructs(void);
void PushMp3BoardState(void);
void PushMp3MinigamesPlayedList(void);
void mp3_StoreBattleMinigameCoins(void);
void PushMp3OvlHis(void);

extern s8 mp3_D_8010D400_4E65C0_name_70[7];
extern s8 mp3_D_8010D407_4E65C7_name_70;
extern s8 mp3_D_8010D408_4E65C8_name_70;
extern s8 mp3_D_8010D40A_4E65CA_name_70;
extern s8 mp3_D_8010D40B_4E65CB_name_70;
extern s8 mp3_D_8010D411_4E65D1_name_70;
extern Vec mp3_D_8010D45C_4E661C_name_70;
extern Vec mp3_D_8010D48C_4E664C_name_70;

//TODO: current issue
/*
ForeignMinigameIndexToLoad is being converted when it shouldn't
When loading an mp2 minigame from mp3 base, it goes to boot logos in mp2
Which then goes to minigame explanation
Which then goes to mp2_func_80102830_3BDF90_name_60
Where Mp2SwapGameIfNeeded performs the wrong actions (due to ForeignMinigameIndexToLoad issues)
*/

STATIC void Mp3SwapGameIfNeeded(void) {
    s32 localOverlayID = ForeignMinigameIDToGame(ForeignMinigameIndexToLoad);

    //determine if we are loading a mp2 or mp1 minigame
    if (ForeignMinigameIndexToLoad >= BOWSER_SLOTS && ForeignMinigameIndexToLoad <= DEEP_SEA_SALVAGE) { //mp2
        //save necessary data, swap to mp2
        PushMp3BoardState();
        PushMp3MinigamesPlayedList();
        mp3_StoreBattleMinigameCoins();
        SaveMp3PlayerToMp3PlayerCopy();
        ComboSwitchGameToMp2();        
    } else if (ForeignMinigameIndexToLoad >= MEMORY_MATCH && ForeignMinigameIndexToLoad <= PADDLE_BATTLE) { //mp2
        //save necessary data, swap to mp1
        //SaveMp3PlayerStructs();
        PushMp3BoardState();
        PushMp3MinigamesPlayedList();
        mp3_StoreBattleMinigameCoins();
        SaveMp3PlayerToMp3PlayerCopy();
        ComboSwitchGameToMp1();
    }
    //is mp3 minigame
    mp3_GwSystem.minigame_index = localOverlayID;
    mp3_D_8010D40B_4E65CB_name_70 = mp3_GwSystem.minigame_index - 1;
    ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
}

//first function ran in ovl_70; the minigame overlay is loaded shortly after
void mp3_MinigameEntryFunc(void) {
    void (*procFunc)(void) = NULL;
    s16 var_a1 = 0;
    s16 i;
    s16 j;
    
    for (i = 0; i < 4; i++) {
        for (j = 0; j < MAX_PLAYERS; j++) {
            if (i != mp3_GwPlayer[j].group) {
                continue;
            }
            mp3_D_8010D400_4E65C0_name_70[var_a1] = j;
            var_a1++;

            if (var_a1 >= 4) {
                break;
            }
        }
        if (var_a1 >= 4) {
            break;
        }
    }

    Mp3SwapGameIfNeeded(); //doesn't return if game swap happens
    if (CurBaseGame == MP2_BASE) {
        LoadMp2PlayerCopyToMp3();
    }

    //is mp3 minigame, load it
    mp3_D_8010D40A_4E65CA_name_70 = mp3_D_800A6D44_A7944[mp3_D_8010D40B_4E65CB_name_70].minigameType;
    
    if (mp3__CheckFlag(0xF) != 0) {
        mp3_D_8010D407_4E65C7_name_70 = 1;
        mp3_D_8010D408_4E65C8_name_70 = 1;
    } else {
        mp3_D_8010D407_4E65C7_name_70 = 0;
        if ((mp3_GWMgUnlockCheck(mp3_D_8010D40B_4E65CB_name_70)) != 0) {
            mp3_D_8010D408_4E65C8_name_70 = 1;
        }        
    }

    mp3_GWMgUnlockSet(-1);
    mp3__ClearFlag(0xF);
    mp3_func_80106EB4_4E0074_name_70();
    mp3_func_80106898_4DFA58_name_70();
    mp3_func_80107308_4E04C8_name_70(); //calling this crashes?
    
    if ((mp3_GwSystem.show_minigame_explanations == 1) || (mp3_D_8010D40A_4E65CA_name_70 == 6)) {
        mp3_func_801061EC_4DF3AC_name_70();
        return;
    }
    
    mp3_Hu3DAnimInit(1);
    mp3_omInitObjMan(0x1E, 0x1E);
    mp3_func_8005A6B0_5B2B0();
    mp3_func_8000B5F0_C1F0(1);
    mp3_ScissorSet(0U, 0.0f, 0.0f, 320.0f, 240.0f);
    mp3_ViewportSet(0U, 640.0f, 480.0f, 511.0f, 640.0f, 480.0f, 511.0f);
    mp3_Hu3DCamSetPerspective(0, 15.0f, 500.0f, 8000.0f);
    mp3_omSetStatBit(mp3_omAddObj(0x7FDA, 0U, 0U, -1, mp3_func_8010674C_4DF90C_name_70), 0xA0U);
    mp3_func_800142A0_14EA0(0x28);
    mp3_HmfLightColorSet(1, 0xFF, 0xFF, 0xFF);
    mp3_omAddPrcObj(mp3_func_80107470_4E0630_name_70, 0x1001U, 0x1000, 0);
    mp3_omAddPrcObj(mp3_func_8010B990_4E4B50_name_70, 0x1001U, 0x1000, 0);
    mp3_omAddPrcObj(mp3_func_8010A1D0_4E3390_name_70, 0x1001U, 0x1000, 0);
    
    switch (mp3_D_8010D40A_4E65CA_name_70) {
    case 5:
        procFunc = mp3_func_801094B0_4E2670_name_70;
        mp3_D_8010D411_4E65D1_name_70 = 1;
        break;
    case 4:
        if (mp3_omovlhisidx <= 0) {
            break;
        }
        if (mp3_GwSystem.playMode & 2) {
            procFunc = mp3_func_80108350_4E1510_name_70;
            mp3_D_8010D411_4E65D1_name_70 = 0;
            break;
        }
    case 3:
        procFunc = mp3_func_80109A90_4E2C50_name_70;
        mp3_D_8010D411_4E65D1_name_70 = 2;
        break;
    case 0:
    case 1:
    case 2:
    case 6:
    case 7:
    case 8:
    default:
        procFunc = mp3_func_80108350_4E1510_name_70;
        mp3_D_8010D411_4E65D1_name_70 = 0;
        break;
    }

    mp3_omAddPrcObj(procFunc, 0x1001U, 0x800, 0);
    mp3_omAddObj(0, 0, 0, -1, mp3_func_80105D9C_4DEF5C_name_70);
    mp3_omAddObj(0, 0, 0, -1, mp3_func_80106310_4DF4D0_name_70);
    mp3_func_80106388_4DF548_name_70();
    mp3_func_80106850_4DFA10_name_70(&mp3_D_8010D45C_4E661C_name_70, &mp3_D_8010D48C_4E664C_name_70);
    mp3_func_801067CC_4DF98C_name_70();
    mp3_WipeCreateIn(0xFF, 0x10);
}