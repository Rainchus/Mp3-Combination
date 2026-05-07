#include "mp3.h"
#include "shared_board/ovl_80.h"

typedef struct MinigameTable {
    u8 minigameType;
    char unk_01[0x13];
} MinigameTable;

extern MinigameTable mp3_D_800A6D44_A7944[];

typedef struct Unk800CC3DC {
    char unk_00[4];
    s8 unk_04[8]; //unknown size
} Unk800CC3DC;

extern Unk800CC3DC D_800CC3DC_CCFDC;
void mp3_GWMgNoSet(s8 arg0);
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
void mp3__SetFlag(s32);

extern s8 mp3_D_8010D400_4E65C0_name_70[7];
extern s8 mp3_D_8010D407_4E65C7_name_70;
extern s8 mp3_D_8010D408_4E65C8_name_70;
extern s8 mp3_D_8010D40A_4E65CA_name_70;
extern s8 mp3_D_8010D40B_4E65CB_name_70;
extern s8 mp3_D_8010D411_4E65D1_name_70;
extern Vec mp3_D_8010D45C_4E661C_name_70;
extern Vec mp3_D_8010D48C_4E664C_name_70;
extern u8 minigameTextColor[];
extern u8 newCategoryAmountsNormalMp3[];
extern u8 new4PMinigameListNormalMp3[];
extern u8 new1v3MinigameListNormalMp3[];
extern u8 new2v2MinigameListNormalMp3[];
extern u8 newBattleMinigameListNormalMp3[];
extern u8 newItemMinigameListNormalMp3[];
extern u8 newDuelMinigameListNormalMp3[];

STATIC void Mp3SwapGameIfNeeded(void) {
    s32 localOverlayID = ForeignMinigameIDToGame(ForeignMinigameIndexToLoad);

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
    }
    //is mp3 minigame
    mp3_GwSystem.minigame_index = localOverlayID;
    mp3_D_8010D40B_4E65CB_name_70 = mp3_GwSystem.minigame_index - 1;
    ForeignMinigameIndexToLoad = FOREIGN_MINIGAME_INVALID_ID;
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
    } else if (CurBaseGame == MP2_BASE) {
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
extern s8 mp3_D_8010D40B_4E65CB_inst;
extern s8 mp3_D_8010D5B1_4E6771_inst;

#define mgresultboard 0x71
#define mgresultdealer 0x72
#define mgresultduel 0x73
#define mgresultbattle 0x74
#define boot 0x58

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
            mp3_omOvlHisChg(1, mgresultbattle, 0, 0x12);
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

////////////
typedef struct ItemRect {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} ItemRect;

typedef struct DefinitelyNotItemRect {
    s8 x[100500];
} DefinitelyNotItemRect;

typedef struct ItemRectTable {
    ItemRect* rects[6];
} ItemRectTable; //sizeof 0x18

typedef struct DefinitelyNotItemRectTable {
    DefinitelyNotItemRect* notRects[6];
} DefinitelyNotItemRectTable; //sizeof 0x18

// typedef struct Sp18Struct {
//     ItemRectTable rectTable;
//     DefinitelyNotItemRectTable notRectTable1;
//     DefinitelyNotItemRectTable notRectTable2;
// } Sp18Struct;

typedef struct ItemSlotEntry {
/* 0x00 */ s16 obj;
/* 0x02 */ s16 x;
/* 0x04 */ s16 y;
/* 0x06 */ s16 w;
/* 0x08 */ s16 h;
} ItemSlotEntry; //sizeof 0xA

ItemRect D_80100E44_shared_board = {
/* x */ 60,
/* y */ 348,
/* w */ 200,
/* h */ 20
};

ItemRect D_80100E4C_shared_board = {
/* x */ 60,
/* y */ 368,
/* w */ 200,
/* h */ 20
};

ItemRect D_80100E54_shared_board = {
/* x */ 60,
/* y */ 388,
/* w */ 200,
/* h */ 20
};

ItemRect D_80100E5C_shared_board = {
/* x */ 60,
/* y */ 328,
/* w */ 200,
/* h */ 20
};

ItemRect D_80100E64_shared_board = {
/* x */ 60,
/* y */ 348,
/* w */ 200,
/* h */ 20
};

ItemRect D_80100E6C_shared_board = {
/* x */ 60,
/* y */ 368,
/* w */ 200,
/* h */ 20
};

ItemRect D_80100E74_shared_board = {
/* x */ 60,
/* y */ 388,
/* w */ 200,
/* h */ 20
};

ItemRect D_80100E7C_shared_board = {
/* x */ 60,
/* y */ 408,
/* w */ 200,
/* h */ 20
};

ItemRectTable D_801020B0_115CD0_shared_board = {
    &D_80100E5C_shared_board,
    &D_80100E44_shared_board,
    &D_80100E44_shared_board,
    &D_80100E44_shared_board,
    &D_80100E44_shared_board,
    &D_80100E5C_shared_board
};

//normal minigames, 4p?
u8 mp3Normal4pMinigames[] = {
    0x15, 0x16, 0x17, 0x18,
    0x19, 0x1B, 0x1C, 0x1D,
    0x1E, 0x1F, 0x20, 0x21,
    0x22, 0x23, 0x24, 0x25,
    0x26, 0x27, 0x28, 0x2C    
};

//easy minigames, 4p?
u8 mp3Easy4pMinigames[] = {
    TREADMILL_GRILL, 0x19, 0x1C, 0x1D,
    0x1E, 0x21, 0x22, 0x26,
    0x28, 0
};

//normal 1v3 minigames
u8 mp3Normal1v3Minigames[] = {
    HAND_LINE_AND_SINKER, 2, 3, 4, 5, 6, 7, 8, 9, 10, 0
};

//easy 1v3 minigames
u8 mp3Easy1v3Minigames[] = {
    COCONUT_CONK, 3, 4, 5, 6, 9, 10, 0
};

//2v2
u8 mp3Normal2v2Minigames[] = {
    EATSA_PIZZA, 0xC, 0xD, 0xE, 0xF, 0x10, 0x11, 0x12, 0x13, 0x14
};

//item
u8 mp3NormalItemMinigames[] = {
    WINNERS_WHEEL, 0x3C, 0x3D, 0x3E, 0x3F, 0x40
};

//battle
u8 mp3NormalBattleMinigames[] = {
    LOCKED_OUT, 0x29, 0x2A, 0x2B, 0x2D, 0x2E, 0x2F, 0x30
};

//battle
u8 mp3EasyBattleMinigames[] = {
    STACKED_DECK, 0x2B, 0x2D, 0x2E
};

//duel
u8 mp3NormalDuelMinigames[] = {
    VINE_WITH_ME, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A
};

//easy 2v2 minigames
u8 mp3Easy2v2Minigames[] = {
    EATSA_PIZZA, 0xC, 0x10, 0x11, 0x13
};

//game guy again?
u8 mp3EasyItemMinigames[] = {
    WINNERS_WHEEL, 0x3C, 0x3D, 0x3E, 0x3F, 0x40
};

//easy duel
u8 mp3EasyDuelMinigames[] = {
    VINE_WITH_ME, 0x32, 0x33, 0x35, 0x37, 0x38, 0x39
};

//noraml minigames
// u8* D_801020C8_115CE8_shared_board[] = {
//     mp3Normal4pMinigames,
//     mp3Normal1v3Minigames,
//     mp3Normal2v2Minigames,
//     mp3NormalItemMinigames,
//     mp3NormalBattleMinigames,
//     mp3NormalDuelMinigames
// };

u8* D_801020C8_115CE8_shared_board[] = {
    new4PMinigameListNormalMp3,
    new1v3MinigameListNormalMp3,
    new2v2MinigameListNormalMp3,
    newItemMinigameListNormalMp3,
    newBattleMinigameListNormalMp3,
    newDuelMinigameListNormalMp3
};

//easy minigames
u8* D_801020E0_115D00_shared_board[] = {
    mp3Easy4pMinigames,
    mp3Easy1v3Minigames,
    mp3Easy2v2Minigames,
    mp3EasyItemMinigames,
    mp3EasyBattleMinigames,
    mp3EasyDuelMinigames
};

// extern DefinitelyNotItemRectTable D_801020C8_115CE8_shared_board;
// extern DefinitelyNotItemRectTable D_801020E0_115D00_shared_board;

u8 D_80100EEC_114B0C_shared_board[] = {
    0x14,
    0xA,
    0xA,
    0x6,
    0x08,
    0xA,
    0,
    0
};

u8 D_80100EF4_114B14_shared_board[] = {
    9,
    7,
    5,
    6,
    4,
    7,
    0,
    0,
    0,
    0,
    0,
    0
};

extern u8 D_80100E20_114A40_shared_board[]; /* normal mode: recent minigame avoid count per category */
extern u8 D_80100E28_114A48_shared_board[]; /* hard mode: recent minigame avoid count per category */
extern u8 D_80100E30_114A50_shared_board[][3];
extern u16 D_80102BD4_1167F4_shared_board;
extern ItemSlotEntry D_80102BD0_1167F0_shared_board[];
// extern s8 D_80102C08_116828_shared_board[];
extern u8 D_80102C08_116828_shared_board[]; //changed to u8
extern s8 D_80102C0D_11682D_shared_board; //category index
extern u8 D_80100E18_114A38_shared_board[];
extern u8 D_80100EEC_114B0C_shared_board[];
extern u8 D_80100EF4_114B14_shared_board[];
extern u8 D_80100E20_114A40_shared_board[]; /* normal mode: recent minigame avoid count per category */
extern u8 D_80100E28_114A48_shared_board[]; /* hard mode: recent minigame avoid count per category */
extern u8 D_80100E9B_114ABB_shared_board[];
extern u8 D_80100E30_114A50_shared_board[][3];
extern s16 D_80102C12_116832_shared_board;
extern s8 D_80100E94_114AB4_shared_board[][2];
extern u8 D_80100E8C_114AAC_shared_board[];

s16 mp3_func_8005A968_5B568(s16, s16, s16, s16, s32, s16);
void mp3_func_8005BE30_5CA30(s16, s32);
void mp3_func_8005BE30_5CA30(s16, s32);
void mp3_func_8005BE30_5CA30(s16, s32);
void mp3_func_80060144_60D44(s16);
void mp3_func_8005BCA4_5C8A4(s16, s16, s16);
void mp3_func_8005BEE0_5CAE0(s16, s32);
s32 mp3_BoardGetTurnTier(s32);
void mp3_func_8005D2D4_5DED4(s16);
extern mp3_omObjData* D_80102C04_116824_shared_board;
void mp3_func_8005C02C_5CC2C(s16, s32);
void mp3_func_8005BDFC_5C9FC(s16, s32);
void mp3_func_800DF9EC_F360C_shared_board(void);
extern s16 D_80102C0E_11682E_shared_board;
void SetMp3MultigameMinigameString(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern u8 D_80100E84_114AA4_shared_board[];

void mp3_func_8005BA90_5C690(s16, s16, s16);
void mp3_func_8005BB18_5C718(s16, f32, f32);
void mp3_func_8005C154_5CD54(s16, s32, s32, s32);
void mp3_func_8005D2D4_5DED4(s16);
void mp3_func_800DECF0_F2910_shared_board(void);
void mp3_func_800DF8B4_F34D4_shared_board(void);
void mp3_func_800DFAD4_F36F4_shared_board(void);
void mp3_func_800E5B90_F97B0_shared_board(void);
void mp3_func_8005FBF8_607F8(s16, s32, s32, s32);
u8 rand8_Shared(void);
void mp3_HuAudFXPlay(s16);
void mp3_func_8005D294_5DE94(s16);

void newfunc_800DED3C_F295C_shared_board(mp3_omObjData* arg0) {
    ItemSlotEntry* entry = NULL;
    s32 i;
    s16 new_var;
    
    switch (arg0->work[0]) {
    case 3:
        break;
    case 0:
        if (arg0->work[1] == 0) {
            arg0->scale.y += 0.1f;
            if (arg0->scale.y > 1.0f) {
                arg0->scale.y = 1.0f;
            }
            for (i = 0; i < D_80100E18_114A38_shared_board[D_80102C0D_11682D_shared_board]; i++) {
                new_var = 0xE0;
                entry = &D_80102BD0_1167F0_shared_board[i];
                mp3_func_8005BA90_5C690(entry->obj, (entry->x + (entry->w / 2)), (entry->y + ((entry->h / 2) - new_var)));
                mp3_func_8005BB18_5C718(entry->obj, 0.0f, arg0->scale.y);
            }
   
            new_var = 0xE0;
            mp3_func_80054904_55504(D_80102C0E_11682E_shared_board, 0, 0xA0, (D_80102BD4_1167F4_shared_board + (D_80100E84_114AA4_shared_board[D_80102C0D_11682D_shared_board] - new_var)));
            
            
            mp3_HuSprScaleSet(D_80102C0E_11682E_shared_board, 0, mp3_HuMathSin(arg0->scale.x), arg0->scale.y);
            if (arg0->scale.y >= 1.0f) {
                arg0->work[0] = 4;
                arg0->work[1] = 5;
            }
        } else {
            arg0->work[1] -= 1;
        }
        break;
    case 4:
        if (arg0->work[1] != 0) {
            arg0->work[1] -= 1;
            break;
        }
        
        arg0->scale.x += 10.0f;
        if (arg0->scale.x > 90.0f) {
            arg0->scale.x = 90.0f;
        }

        for (i = 0; i < D_80100E18_114A38_shared_board[D_80102C0D_11682D_shared_board]; i++) {
            new_var = 0xE0;
            entry = &D_80102BD0_1167F0_shared_board[i];
            mp3_func_8005BA90_5C690(entry->obj, (entry->x + (entry->w / 2)), (entry->y + ((entry->h / 2) - new_var)));
            mp3_func_8005BB18_5C718(entry->obj, mp3_HuMathSin(arg0->scale.x), arg0->scale.y);
        }
        
        new_var = 0xE0;    
        mp3_func_80054904_55504(D_80102C0E_11682E_shared_board, 0, 0xA0,
            (D_80102BD4_1167F4_shared_board + (D_80100E84_114AA4_shared_board[D_80102C0D_11682D_shared_board] - new_var)));
        
        
        mp3_HuSprScaleSet(D_80102C0E_11682E_shared_board, 0, mp3_HuMathSin(arg0->scale.x), arg0->scale.y);
        
        if (arg0->scale.x >= 90.0f) {
            mp3_func_800DECF0_F2910_shared_board();
            arg0->work[0] = 1;
            arg0->scale.x = 1.0f;
            arg0->scale.z = -1.0f;
            arg0->scale.y = 0.0f;
            arg0->work[1] = 0;
            arg0->work[2] = mp3_MBRand((f32) D_80100E18_114A38_shared_board[D_80102C0D_11682D_shared_board]);
            arg0->work[3] = 0;
            mp3_func_800DFAD4_F36F4_shared_board();
        }
        break;
    case 1:
        arg0->scale.z += arg0->scale.x;
        
        if (arg0->scale.z >= 1.0f) {
            if ((arg0->work[3] != 0) && (arg0->scale.x <= 0.08f)) {
                arg0->work[3]--;
            }
            arg0->scale.z -= 1.0f;
            if (arg0->scale.y == 0.0f) {
                arg0->work[1]++;
                arg0->work[1] = arg0->work[1] % D_80100E18_114A38_shared_board[D_80102C0D_11682D_shared_board];
            } else {
                arg0->work[1]--;
                if (arg0->work[1] >= 0x80U) {
                    arg0->work[1] = D_80100E18_114A38_shared_board[D_80102C0D_11682D_shared_board] - 1;
                }
            }
            mp3_func_800DECF0_F2910_shared_board();
        }
        
        for (i = 0; i < D_80100E18_114A38_shared_board[D_80102C0D_11682D_shared_board]; i++) {
            entry = &D_80102BD0_1167F0_shared_board[i];
            if (i == arg0->work[1]) {
                mp3_func_8005FBF8_607F8(entry->obj, 0, 0xC8, 0);
                mp3_func_8005BEE0_5CAE0(entry->obj, 0x100);
                mp3_func_8005BE30_5CA30(entry->obj, 0x2328);
            } else {
                mp3_func_8005FBF8_607F8(entry->obj, 0x40, 0x40, 0x80);
                mp3_func_8005BEE0_5CAE0(entry->obj, 0);
                mp3_func_8005BE30_5CA30(entry->obj, 0x2710);
            }
        }
        
        if ((arg0->work[1] == arg0->work[2]) || (arg0->scale.x < 1.0f)) {
            arg0->scale.x = (f32) ((f64) arg0->scale.x - 0.02);
        }
        
        if (arg0->scale.x <= 0.08f) {
            arg0->scale.x = 0.08f;
            if ((arg0->work[1] == arg0->work[2]) && (arg0->work[3] == 0) && ((arg0->scale.z + 0.08f) >= 1.0f)) {
                if ((rand8_Shared() & 0xF) || (arg0->scale.y == 1.0f) || (arg0->work[1] == 0)) {
                    if ((mp3_GwSystem.show_minigame_explanations == 0) || (mp3_GwSystem.current_board_index == 6)) {
                        mp3_HuAudFXPlay(0x105);
                    } else {
                        mp3_HuAudFXPlay(0x112);
                    }
                    
                    arg0->work[0] = 2;
                    arg0->work[3] = 0x3C;
                    mp3_func_8005D2D4_5DED4(entry->obj);
                    mp3_func_8005D294_5DE94(D_80102BD0_1167F0_shared_board[arg0->work[1]].obj);
                    SetMp3MultigameMinigameString(D_80102BD0_1167F0_shared_board[arg0->work[1]].obj,
                        (D_80102C08_116828_shared_board[arg0->work[1]]), -2, 4);
                    // mp3_func_8005B43C_5C03C(D_80102BD0_1167F0_shared_board[arg0->work[1]].obj,
                    //     (char*)(D_80102C08_116828_shared_board[arg0->work[1]] + 0x46FF), -2, 4); 
                    mp3_func_8005C02C_5CC2C(D_80102BD0_1167F0_shared_board[arg0->work[1]].obj, 1);
                    mp3_func_8005C154_5CD54(D_80102BD0_1167F0_shared_board[arg0->work[1]].obj, 0xA0, 0xA0, 0xA0);
                    mp3_func_8005FBF8_607F8(D_80102BD0_1167F0_shared_board[arg0->work[1]].obj, 0xFE, 0xFF, 0xD0);
                    mp3_func_8005BDFC_5C9FC(D_80102BD0_1167F0_shared_board[arg0->work[1]].obj, 0);
                } else {
                    arg0->scale.y = 1.0f;
                    arg0->work[2]--;
                    if (arg0->work[2] >= 128) {
                        arg0->work[2] = D_80100E18_114A38_shared_board[D_80102C0D_11682D_shared_board] - 1;
                    }
                }
            }
        }
        break;
    case 2:
        if (arg0->work[3] != 0) {
            arg0->work[3]--;
        } else {
            D_800CC4A0_CD0A0.recentMinigames[D_80102C0D_11682D_shared_board][D_800CC3DC_CCFDC.unk_04[D_80102C0D_11682D_shared_board]] = D_80102C08_116828_shared_board[arg0->work[2]];
            D_800CC3DC_CCFDC.unk_04[D_80102C0D_11682D_shared_board]++;
            
            if (mp3__CheckFlag(0x20) != 0) {
                D_800CC3DC_CCFDC.unk_04[D_80102C0D_11682D_shared_board] = (D_800CC3DC_CCFDC.unk_04[D_80102C0D_11682D_shared_board] % (s32) D_80100E28_114A48_shared_board[D_80102C0D_11682D_shared_board]);
            } else {
                D_800CC3DC_CCFDC.unk_04[D_80102C0D_11682D_shared_board] = (D_800CC3DC_CCFDC.unk_04[D_80102C0D_11682D_shared_board] % (s32) D_80100E20_114A40_shared_board[D_80102C0D_11682D_shared_board]);
            }
            mp3_GWMgNoSet(D_80102C08_116828_shared_board[arg0->work[2]]);
            if (mp3_GwSystem.current_board_index != 6) {
                mp3_func_800E5B90_F97B0_shared_board();
                mp3_func_800DF8B4_F34D4_shared_board();
            }
        }
        arg0->rot.z += 1.0f;
        if (arg0->rot.z >= 13.0f) {
            arg0->rot.z -= 13.0f;
        }
        break;
    }
    if (D_80102C12_116832_shared_board != -1) {
        
        for (i = 0; !(arg0->rot.z < (f32) *D_80100E94_114AB4_shared_board[i]); i++) {}
        
        mp3_func_80054904_55504(D_80102C12_116832_shared_board, 0,
            (D_80100E94_114AB4_shared_board[i][1] + 50),
            (D_80100E8C_114AAC_shared_board[D_80102C0D_11682D_shared_board] + (arg0->work[1] * 20)));
    }
}

void newfunc_800DFBA8_F37C8_shared_board(s32 arg0) {
    ItemSlotEntry* entry;
    mp3_omObjData* obj;
    s32 category;
    s32 item;
    s32 forbidCount;
    s32 i;
    s32 j;
    s32 k;
    u8* minigameList;
    u8* avoidCounts;

    switch (arg0) {
        case -1:
            category = mp3_func_800F52C4_108EE4_shared_board();
            if (category == -1) {
                category = 3;
            }
            break;
        case 1:
            category = 4;
            break;
        case 2:
            category = 5;
            break;
        case 0:
        default:
            category = 3;
            break;
    }

    D_80102C0D_11682D_shared_board = category;

    if (mp3__CheckFlag(0x20)) { //hard mode?
        minigameList = D_801020E0_115D00_shared_board[category];
        avoidCounts  = D_80100EF4_114B14_shared_board;
        forbidCount  = D_80100E28_114A48_shared_board[category];
    } else { //normal mode?
        minigameList = D_801020C8_115CE8_shared_board[category];
        avoidCounts  = newCategoryAmountsNormalMp3; //D_80100EEC_114B0C_shared_board;
        forbidCount  = D_80100E20_114A40_shared_board[category];
    }

    for (i = 0; i < D_80100E18_114A38_shared_board[category]; i++) {
        entry = &D_80102BD0_1167F0_shared_board[i];

        //new way to get xy and width/height. Original code crashes for some reason but this logic works out the same
        entry->x = D_801020B0_115CD0_shared_board.rects[category]->x;
        entry->y = D_801020B0_115CD0_shared_board.rects[category]->y + (i * 20);
        entry->w = D_801020B0_115CD0_shared_board.rects[category]->w;
        entry->h = D_801020B0_115CD0_shared_board.rects[category]->h;

        entry->obj = mp3_func_8005A968_5B568(
            (entry->x + (entry->w / 2)),
            (entry->y + (entry->h / 2)),
            entry->w,
            entry->h,
            0, 4);
        mp3_func_8005BE30_5CA30(entry->obj, 0x2328);
        mp3_func_80060144_60D44(entry->obj);
        mp3_func_8005BCA4_5C8A4(entry->obj, entry->w / 2, entry->h / 2);
        mp3_func_8005BEE0_5CAE0(entry->obj, 0);

        while (1) {
            D_80102C08_116828_shared_board[i] = minigameList[mp3_MBRand(avoidCounts[category])];

            /* reject duplicates */
            for (j = 0; j < i; j++) {
                if (D_80102C08_116828_shared_board[j] == D_80102C08_116828_shared_board[i]) {
                    break;
                }
            }

            if (j != i) {
                continue;
            }

            /* reject recently played */
            for (k = 0; k < forbidCount; k++) {
                if (D_80102C08_116828_shared_board[i] == D_800CC4A0_CD0A0.recentMinigames[category][k]) {
                    break;
                }
            }

            if (k != forbidCount) {
                continue;
            }

            /* reject certain games on early turns */
            if (mp3_BoardGetTurnTier(-1) == 0) {
                item = D_80102C08_116828_shared_board[i];
                if (item == 0x11) continue;
                if (item == ((item >= 0x12) ? 0x1C : 9)) continue;
            }

            break;
        }

        mp3_func_8005D2D4_5DED4(entry->obj);

        //@patch: show all minigame names for all 3 games, even locked ones
        SetMp3MultigameMinigameString(entry->obj, (D_80102C08_116828_shared_board[i]), -2, 4);

        // if (mp3_GWMgUnlockCheck(D_80102C08_116828_shared_board[i] - 1) != 0) {
        //     mp3_func_8005B43C_5C03C(entry->obj, (char*)(D_80102C08_116828_shared_board[i] + 0x46FF), -2, 4);
        // } else {
        //     mp3_func_8005B43C_5C03C(entry->obj, (char*)0x4748, -2, 4);
        // }

        mp3_func_8005C02C_5CC2C(entry->obj, minigameTextColor[D_80102C08_116828_shared_board[i]]);
        mp3_func_8005BDFC_5C9FC(entry->obj, 0);
    }

    obj = mp3_omAddObj(-0x8000, 0U, 0U, -1, newfunc_800DED3C_F295C_shared_board);
    D_80102C04_116824_shared_board = obj;
    obj->work[0] = 3;
    obj->work[1] = 5;
    obj->trans.y = 0.0f;
    obj->scale.x = 10.0f;
    obj->scale.y = 0.0f;
    obj->rot.z = 0.0f;
    mp3_func_800DF9EC_F360C_shared_board();

    mp3_func_80055420_56020(D_80102C0E_11682E_shared_board, 0,
        D_80100E30_114A50_shared_board[D_80102C0D_11682D_shared_board][0],
        D_80100E30_114A50_shared_board[D_80102C0D_11682D_shared_board][1],
        D_80100E30_114A50_shared_board[D_80102C0D_11682D_shared_board][2]);
}