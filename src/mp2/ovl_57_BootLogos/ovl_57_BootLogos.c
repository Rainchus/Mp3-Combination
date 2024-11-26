#include "marioparty.h"
#include "mp3.h"
#include "mp2.h"
#include "mp1.h"

#define N64_LOGO 0x00090000
#define NINTENO_LOGO 0x00090001
#define HUDSON_LOGO 0x00090002

typedef struct UnkBoardStatus {
    char unk0[2];
    s16 unk_02;
    char unk4[0x1A];
    s16 unk_1E;
    s16 unk_20;
    s16 unk_22;
    s16 unk_24;
    s16 unk_26;
} UnkBoardStatus; //sizeof 0x28

extern u16 mp2_D_801011FC_101DFC;
extern s32 ForeignMinigameIndexToLoad;
extern UnkBoardStatus mp2_D_800F93A8;
extern s8 mp2_D_800F93CD_F9FCD;
extern s32 CurBaseGame;
extern u8 mp3_BoardStateCopy[BOARD_STATE_STRUCT_SIZE];

s16 mp2_func_8001A2F8_1AEF8(s32);
u16 mp2_func_8001AAAC_1B6AC(s16, s16, u16);
void mp2_espPosSet(u16, s16, s16);
void mp2_espDispOn(u16);
void mp2_func_8001A788_1B388(u16, u16);
void mp2_InitFadeIn(s32, s32);
s32 mp2_func_8008F618_90218(void);
void mp2_HuPrcVSleep(void);
void mp2_HuPrcSleep(s32);
void mp2_InitFadeOut(s32, s32);
void mp2_func_8001AC44_1B844(u16);
void mp2_SprAnimKill(s16);
void mp2__SetFlag(s32 input);
void CopyMp3_gPlayerCopy_To_Mp2(void);
void mp2_omInitObjMan(s32, s32);
void mp2_func_80026D28_27928(s32);
void mp2_func_80026DAC_279AC(s32, s32, s32, s32);
void mp2_func_80026E00_27A00(s32, f32, f32, f32);
void CopyMp1_gPlayerCopy_To_Mp2(void);
NORETURN void ComboSwitchGameToMp3(void);
extern u32 mp2_rnd_seed;
extern u16 mp2_BattleMinigameCoins;
extern u16 mp3_BattleMinigameCoins;
extern u16 mp3_BattleMinigameCoins_Copy;
extern u8 newBattleMinigameListNormalMp3[];
extern s16 mp2_D_800E1F50_E2B50;
extern s16 mp2_D_800E1F52_E2B52;
void PopMp2MinigamesPlayedList(void);
void LoadMp2PlayerStructs(void);
void PopMp2OvlHis(void);
void mp2_HuPrcEnd(void);

s32 isBattleMinigame = 0;

void mp2_OriginalBootLogos(void) {
    s16 temp_v0;
    u16 temp_s0;

    temp_v0 = mp2_func_8001A2F8_1AEF8(N64_LOGO);
    temp_s0 = mp2_func_8001AAAC_1B6AC(temp_v0, 0, 1);
    mp2_espPosSet(temp_s0, 0xA0, 0x78);
    mp2_espDispOn(temp_s0);
    mp2_func_8001A788_1B388(temp_s0, 0xFFFF);
    mp2_InitFadeIn(0, 5);

    while (mp2_func_8008F618_90218() != 0) {
        mp2_HuPrcVSleep();
    }

    mp2_HuPrcSleep(5);
    mp2_InitFadeOut(0, 5);
    
    while (mp2_func_8008F618_90218() != 0) {
        mp2_HuPrcVSleep();
    }
    
    mp2_func_8001AC44_1B844(temp_s0);
    mp2_SprAnimKill(temp_v0);
    mp2_HuPrcSleep(5);
    temp_v0 = mp2_func_8001A2F8_1AEF8(NINTENO_LOGO);
    temp_s0 = mp2_func_8001AAAC_1B6AC(temp_v0, 0, 1);
    mp2_espPosSet(temp_s0, 0xA0, 0x78);
    mp2_espDispOn(temp_s0);
    mp2_func_8001A788_1B388(temp_s0, -1);
    mp2_InitFadeIn(0, 5);
    
    while (mp2_func_8008F618_90218() != 0) {
        mp2_HuPrcVSleep();
    }

    mp2_HuPrcSleep(5);
    mp2_InitFadeOut(0, 9);
    
    while (mp2_func_8008F618_90218() != 0) {
        mp2_HuPrcVSleep();
    }
    
    mp2_func_8001AC44_1B844(temp_s0);
    mp2_SprAnimKill(temp_v0);
    mp2_HuPrcSleep(5);
    temp_s0 = mp2_func_8001AAAC_1B6AC(mp2_func_8001A2F8_1AEF8(HUDSON_LOGO), 0, 1);
    mp2_espPosSet(temp_s0, 0xA0, 0x78);
    mp2_espDispOn(temp_s0);
    mp2_func_8001A788_1B388(temp_s0, -1);
    mp2_InitFadeIn(0, 9);
    
    while (mp2_func_8008F618_90218() != 0) {
        mp2_HuPrcVSleep();
    }
    
    mp2_HuPrcSleep(5);
    mp2_D_801011FC_101DFC = 1;

    while (1) {
        mp2_HuPrcVSleep();
    }
}

mp2_BoardStatus mp2_BoardStateCopy = {0};
//no idea how large this is or where it starts....
u8 mp2_OtherBoardStateCopy[0x20] = {0};
extern u8 mp2_OtherBoardState[0x20];

void PushMp2BoardState(void) {
    s32 i;

    mp2_BoardStateCopy = mp2_BoardState;
    for (i = 0; i < 0x20; i++) {
        mp2_OtherBoardStateCopy[i] = mp2_OtherBoardState[i];
    }
}

void PopMp2BoardState(void) {
    s32 i;

    mp2_BoardState = mp2_BoardStateCopy;
    for (i = 0; i < 0x20; i++) {
        mp2_OtherBoardState[i] = mp2_OtherBoardStateCopy[i];
    }
}

void LoadBackIntoMp2Board(void) {
    s8 curTurn;
    s8 totalTurns;
    s8 curBoardIndex;
    s32 i;

    PopMp2BoardState();
    PopMp2MinigamesPlayedList();
    LoadMp2PlayerStructs();

    curTurn = mp2_BoardState.curTurn;
    totalTurns = mp2_BoardState.maxTurns;
    curBoardIndex = mp2_BoardState.curBoardIndex;

    // if (isBattleMinigame == 1) {
    //     s32 i;
    //     isBattleMinigame = 0;

    //     omOvlHisData BattleResults[] = {
    //         {0x70, 0x0001, 0x0192},
    //         {0x53, 0x0000, 0x0192},
    //         {0x48, 0x0000, 0x0192},
    //     };
    //     for (i = 0; i < ARRAY_COUNT(BattleResults); i++) {
    //         mp3_omovlhis[i] = BattleResults[i];
    //     }
    //     mp3_omovlhisidx = 3;
    //     mp3_omOvlCallEx(0x74, 0, 0x12); //go to battle results scene
    //     return;
    // }
    if (curTurn > totalTurns) {
        PopMp2OvlHis();
        mp2_omovlhisidx--;
        mp2_D_800E1F50_E2B50 = 0;
        mp2_D_800E1F52_E2B52 = 0;
        mp2_omOvlCallEx(0x52, 0, 0x192); //go to end of game scene
        return;
    } else if ((totalTurns - curTurn) == 4) {
        omOvlHisData last5Turns[] = {
            {0x62, 0x0000, 0x0192},
            {0x62, 0x0000, 0x0192},
            {0x5B, 0x0000, 0x1014},
            {0x3D, 0x0001, 0x0192},
        };
        s32 i;
        for (i = 0; i < ARRAY_COUNT(last5Turns); i++) {
            mp2_omovlhis[i] = last5Turns[i];
        }
        mp2_omovlhisidx = 3;
        // func_800F8610_10C230_Copy(0x48, 2, 0x192, curBoardIndex);
        mp2_omOvlCallEx(0x40, 0, 0x192); //last 5 turns
        return;
    }

    omOvlHisData NormalLoadInHis[] = {
        {0x62, 0x0000, 0x0192},
        {0x62, 0x0000, 0x0192},
        {0x5B, 0x0000, 0x1014},
        {0x3D, 0x0001, 0x0192},
    };

    //copy a hardcoded overlay history in
    for (i = 0; i < ARRAY_COUNT(NormalLoadInHis); i++) {
        mp2_omovlhis[i] = NormalLoadInHis[i];
    }
    u8 boardOverlays[] = {
        0x3E, //western land
        0x41, //pirate land
        0x43, //horror land
        0x45, //space land
        0x47, //mystery land
        0x49, //koopa land
    };
    mp2_omovlhisidx = 3;
    //load into the board
    mp2_omOvlCallEx(boardOverlays[curBoardIndex], 2, 0x192); //load back into board
}

//func_80102AD8_36DC78_BootLogos
void mp2_newBootLogo(void) {
    s32 i;
    //we need to initialize rng in a better way than vanilla's static value
    //TODO: push current count before swapping game, seed against that
    mp2_rnd_seed = mp2_osGetCount() ^ 0xD826BC89;

    if (ForeignMinigameAlreadyLoaded == TRUE) {
        if (CurBaseGame == MP2_BASE) {
            //TODO: load back into mp2 board code here
            mp2_D_800E1F50_E2B50 = 1; //required for board events like star moving to work
            LoadBackIntoMp2Board();
            mp2_HuPrcEnd();
            while (1) {
                mp2_HuPrcVSleep();
            }
        } else if (CurBaseGame == MP1_BASE) {
            for (i = 0; i < 4; i++) {
                s32 coinsEarned = mp2_gPlayers[i].coins - mp1_PlayersCopy[i].coins;
                mp1_PlayersCopy[i].coins += coinsEarned;
                // if (mp1_PlayersCopy[i].coins < 0) {
                //     mp1_PlayersCopy[i].coins = 0;
                // }
                
                mp1_PlayersCopy[i].mg_star_coins += coinsEarned;
                if (mp1_PlayersCopy[i].coins > mp1_PlayersCopy[i].coins_total) {
                    mp1_PlayersCopy[i].coins_total = mp1_PlayersCopy[i].coins;
                }
            }
            
            ComboSwitchGameToMp1();
        } else if (CurBaseGame == MP3_BASE) {
            //copy over player changes
            for (i = 0; i < 4; i++) {
                s32 coinsEarned = mp2_gPlayers[i].coins - mp3_PlayersCopy[i].coins;
                mp3_PlayersCopy[i].coins += coinsEarned;
                // if (mp3_PlayersCopy[i].coins < 0) {
                //     mp3_PlayersCopy[i].coins = 0;
                // }
                
                mp3_PlayersCopy[i].mg_star_coins += coinsEarned;
                if (mp3_PlayersCopy[i].coins > mp3_PlayersCopy[i].coins_total) {
                    mp3_PlayersCopy[i].coins_total = mp3_PlayersCopy[i].coins;
                }
            }
            ComboSwitchGameToMp3();
        }
    }

    if (CurBaseGame == MP2_BASE) {
        mp2_OriginalBootLogos();
        return;
    } else if (CurBaseGame == MP1_BASE && ForeignMinigameAlreadyLoaded == FALSE) {
        CopyMp1_gPlayerCopy_To_Mp2();
        //TODO: is this correct?
        mp2_D_800F93CD_F9FCD = mp2_BoardStateCopy.minigameExplanations; //minigame explanations on/off depending on mp2 setting
    } else if (CurBaseGame == MP3_BASE && ForeignMinigameAlreadyLoaded == FALSE) {
        CopyMp3_gPlayerCopy_To_Mp2();
        mp2_D_800F93CD_F9FCD = mp3_BoardStateCopy[0x13]; //minigame explanations on/off depending on mp3 setting
    }

    mp2__SetFlag(0x19); //no idea what this does, might be important, might not
    CopyMp3_gPlayerCopy_To_Mp2();
    mp2_omInitObjMan(16, 4);

    mp2_D_800F93A8.unk_20 = ForeignMinigameIDToGame(ForeignMinigameIndexToLoad);
    mp2_D_800F93A8.unk_22 = 0x55;
    ForeignMinigameAlreadyLoaded = TRUE;
    mp2_omOvlCallEx(func_8003F6F0_402F0(mp2_D_800F93A8.unk_20), 0, 0x84);
    while (1) {
        mp2_HuPrcVSleep();
    }
}
