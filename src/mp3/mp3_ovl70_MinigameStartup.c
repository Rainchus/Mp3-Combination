#include "mp3.h"
#include "shared_board/ovl_80.h"

typedef struct MinigameTable {
    u8 minigameType;
    char unk_01[0x13];
} MinigameTable;

extern MinigameTable mp3_D_800A6D44_A7944[];

void LoadMp1PlayerCopyToMp3(void);
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
void mp3_StoreBattleMinigameCoins(void);
void PushMp3OvlHis(void);
void SaveMp3PlayerToMp1PlayerCopy(void);
void func_801061EC_4DF3AC_inst(void);

extern s8 mp3_D_8010D400_4E65C0_name_70[7];
extern s8 mp3_D_8010D407_4E65C7_name_70;
extern s8 mp3_D_8010D408_4E65C8_name_70;
extern s8 mp3_D_8010D40A_4E65CA_name_70;
extern s8 mp3_D_8010D40B_4E65CB_name_70;
extern s8 mp3_D_8010D411_4E65D1_name_70;
extern Vec mp3_D_8010D45C_4E661C_name_70;
extern Vec mp3_D_8010D48C_4E664C_name_70;

void Mp3SwapGameIfNeeded(void) {
    //we use mp3_GwSystem.minigame_index here because ForeignMinigameIndexToLoad could be -1 at this point
    s32 localOverlayID = ForeignMinigameIDToGame(mp3_GwSystem.minigame_index);

    //determine if we are loading a mp2 or mp1 minigame
    if (ForeignMinigameIndexToLoad >= BOWSER_SLOTS && ForeignMinigameIndexToLoad <= DEEP_SEA_SALVAGE) { //mp2
        //save necessary data, swap to mp2
        PushMp3BoardState();
        SaveMp3PlayerToMp3PlayerCopy();
        ComboSwitchGameToMp2();
    } else if (ForeignMinigameIndexToLoad >= MEMORY_MATCH && ForeignMinigameIndexToLoad <= PADDLE_BATTLE) { //mp1
        //save necessary data, swap to mp1
        PushMp3BoardState();
        SaveMp3PlayerToMp3PlayerCopy();
        ComboSwitchGameToMp1();
    } else {
        //is mp3 minigame
        mp3_GwSystem.minigame_index = localOverlayID;
        mp3_D_8010D40B_4E65CB_name_70 = mp3_GwSystem.minigame_index - 1;
        ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
    }
}

//first function ran in ovl_70;
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

    //we are entering a minigame from another base game. Load playercopy from that game to mp3's GwPlayers
    if (CurBaseGame == MP1_BASE) {
        LoadMp1PlayerCopyToMp3();
        mp3_HuPrcSleep(10); //sleep 10 frames so wipe inits (fixes pop in bugs on minigame loads from boot)
    } else if (CurBaseGame == MP2_BASE) {
        LoadMp2PlayerCopyToMp3();
        mp3_HuPrcSleep(10); //sleep 10 frames so wipe inits (fixes pop in bugs on minigame loads from boot)
    }

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
    mp3_func_80107308_4E04C8_name_70();
    
    if ((mp3_GwSystem.show_minigame_explanations == 1) || (mp3_D_8010D40A_4E65CA_name_70 == 6)) {
        func_801061EC_4DF3AC_inst();
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

typedef struct unkStruct {
    char unk_00[16];
    s32 unk_10;
} unkStruct;

extern unkStruct mp3_D_800A6D30[];
extern s8 mp3_D_8010D40A_4E65CA_inst;
extern u8 mp3_D_8010D40B_4E65CB_inst;
extern s8 mp3_D_8010D5B1_4E6771_inst;

void func_801061EC_4DF3AC_inst(void) {
    mp3_omOvlCallEx(mp3_D_800A6D30[mp3_D_8010D40B_4E65CB_inst].unk_10, 0, 0x14);

    if (mp3_D_8010D5B1_4E6771_inst == 1) {
        mp3__SetFlag(0xF);
        return;
    }

    if (mp3__CheckFlag(0xD) != 0) {
        if (mp3_omovlhisidx > 0) {
            mp3_omovlhisidx -= 1;
        }
    } else {
        switch (mp3_D_8010D40A_4E65CA_inst) {
        case 6:
            mp3_omOvlHisChg(1, mgresultdealer, 0, 0x14);
            break;
        case 4:
            if (mp3_GwSystem.playMode & 2) {
                mp3_omOvlHisChg(1, mgresultduel, 0, 0x4010);
                break;
            }
            if (mp3_omovlhisidx > 0) {
                mp3_omovlhisidx -= 1;
            }
            break;
        case 3:
            if (CurBaseGame == MP3_BASE) {
                mp3_omOvlHisChg(1, mgresultbattle, 0, 0x12); //original code; push battle results scene to history
            } else {
                mp3_omOvlHisChg(1, boot, 0, 0x12); //push boot logos overlay (has logic for returning to original game)
            }
            
            break;
        case 5:
        case 7:
        case 8:
            if (mp3_omovlhisidx > 0) {
                mp3_omovlhisidx -= 1;
            }
            break;
        default:
            if (CurBaseGame == MP3_BASE) {
                mp3_omOvlHisChg(1, mgresultboard, 0, 0x12); //original code; push battle results scene to history
            } else {
                mp3_omOvlHisChg(1, boot, 0, 0x12); //push boot logos overlay (has logic for returning to original game)
            }
            break;
        }
    }
}

typedef struct {
    /* 0x00 */ u16 data;
    /* 0x02 */ char pad[0x12];
} InstrPageEntry; //sizeof 0x14

extern InstrPageEntry D_800A6D46[];
extern u8 D_800CE20A;
extern s8 D_8010D407_4E65C7_inst;
extern u8 mp3_D_8010D40B_4E65CB_inst;
extern s32 D_8010D4A4_4E6664_inst;
u8 rand8_Shared(void);

void func_80107308_4E04C8_inst(void) {
    s32 useDefault;
    s32 instrIndex;
    u32 entry;

    useDefault = 1;
    instrIndex = 0;

    if (D_8010D407_4E65C7_inst == (COCONUT_CONK -1) &&
       (mp3_D_8010D40B_4E65CB_inst == (PICTURE_IMPERFECT -1) || mp3_D_8010D40B_4E65CB_inst == (CROWD_COVER -1))) {
        instrIndex = (D_800A6D46[mp3_D_8010D40B_4E65CB_inst].data & 0x7FF) + (D_800CE20A * 2);
        useDefault = 0;
    }

    if (useDefault == 1) {
        entry = D_800A6D46[mp3_D_8010D40B_4E65CB_inst].data;
        instrIndex = entry & 0x7FF;

        if (entry & 0x4000) {
            /* This page has character-specific variants (e.g. different text per character) */
            if (mp3_D_8010D40B_4E65CB_inst == 0x46) {
                instrIndex += D_800CE20A * 2;
            } else {
                 /* Pick a random variant within the allowed count */
                entry &= 0x3800; //? tf
                entry >>= 11; //? tf
                D_800CE20A = (rand8_Shared()) % entry;
                instrIndex += D_800CE20A * 2;               
            }
        } else if (mp3_D_8010D40B_4E65CB_inst == 0x47) {
            D_800CE20A = 2;
        } else if (mp3_D_8010D40B_4E65CB_inst == 0x1E && mp3__CheckFlag(0x1C)) {
            D_800CE20A = 1;
        } else {
            D_800CE20A = 0;
        }
    }

    D_8010D4A4_4E6664_inst = instrIndex;
}
