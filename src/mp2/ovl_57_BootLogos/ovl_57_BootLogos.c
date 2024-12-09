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
extern s32 mp2_midTurnMinigameThing;

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
extern s16 mp2_BattleMinigameCoins;
extern s16 mp3_BattleMinigameCoins;
extern s16 mp3_BattleMinigameCoins_Copy;
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

void PushMp1BoardState(void) {
    mp1_GwSystemCopy = mp1_GwSystem;
    mp1_GwCommonCopy = mp1_GwCommon;
}

void PopMp1BoardState(void) {
    mp1_GwSystem = mp1_GwSystemCopy;
    mp1_GwCommon = mp1_GwCommonCopy;
}

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
    mp2_omOvlCallEx(boardOverlays[curBoardIndex], 2, 0x192);
}

//the blacklisted minigames below are blacklisted due to having issues loading them...
//once this is fixed this can be removed
u8 mp2_battleMinigameBlacklist[] = {
    // STACKED_DECK, THREE_DOOR_MONTY, MERRY_GO_CHOMP, SLAP_DOWN, LOCKED_OUT,
    // ALL_FIRED_UP, STORM_CHASERS, EYE_SORE
};

u8 mp2_duelMinigameBlacklist[] = {
    VINE_WITH_ME, POPGUN_PICK_OFF, END_OF_THE_LINE, BABY_BOWSER_BONKERS, SILLY_SCREWS,
    CROWD_COVER, TICK_TOCK_HOP, BOWSER_TOSS, MOTOR_ROOTER, FOWL_PLAY
};

u8 mp2_itemMinigameBlacklist[] = {
    WINNERS_WHEEL, HEY_BATTER_BATTER, BOBBING_BOW_LOONS, DORRIE_DIP, SWINGING_WITH_SHARKS,
    SWING_N_SWIPE
};

u8 mp2_minigame4PBlacklist[] = {
    #ifdef MP1
    YOSHIS_TONGUE_MEETING
    #endif
};

//these probably dont need to be separate from mp3's list, but this provides a bit of clarity
#define MP2_4P_MINIGAME_MAX 66
#define MP2_1V3_MINIGAME_MAX 32
#define MP2_2V2_MINIGAME_MAX 28
#define MP2_BATTLE_MINIGAME_MAX 17
#define MP2_ITEM_MINIGAME_MAX 7
#define MP2_DUEL_MINIGAME_MAX 11
#define MP2_TOTAL_CATEGORIES 6

u8 new4PMinigameListNormalMp2[MP2_4P_MINIGAME_MAX] = {0};
u8 new1v3MinigameListNormalMp2[MP2_1V3_MINIGAME_MAX] = {0};
u8 new2v2MinigameListNormalMp2[MP2_2V2_MINIGAME_MAX] = {0};
u8 newBattleMinigameListNormalMp2[MP2_BATTLE_MINIGAME_MAX] = {0};
u8 newItemMinigameListNormalMp2[MP2_ITEM_MINIGAME_MAX] = {0};
u8 newDuelMinigameListNormalMp2[MP2_DUEL_MINIGAME_MAX] = {0};
u8 newCategoryAmountsNormalMp2[MP2_TOTAL_CATEGORIES] = {0};

void mp2_ClearMinigameList(void) {
    s32 i;
    
    for (i = 0; i < MP2_4P_MINIGAME_MAX; i++) {
        new4PMinigameListNormalMp2[i] = 0;
    }

    for (i = 0; i < MP2_1V3_MINIGAME_MAX; i++) {
        new1v3MinigameListNormalMp2[i] = 0;
    }

    for (i = 0; i < MP2_2V2_MINIGAME_MAX; i++) {
        new2v2MinigameListNormalMp2[i] = 0;
    }

    for (i = 0; i < MP2_BATTLE_MINIGAME_MAX; i++) {
        newBattleMinigameListNormalMp2[i] = 0;
    }

    for (i = 0; i < MP2_ITEM_MINIGAME_MAX; i++) {
        newItemMinigameListNormalMp2[i] = 0;
    }

    for (i = 0; i < MP2_DUEL_MINIGAME_MAX; i++) {
        newDuelMinigameListNormalMp2[i] = 0;
    }

    for (i = 0; i < MP2_TOTAL_CATEGORIES; i++) {
        newCategoryAmountsNormalMp2[i] = 0;
    }
}

void mp2_LoadMinigameList(void) {
    MinigameIndexTable* curMinigameData;
    s32 i, j;
    s32 minigameIsBlacklisted;
    u8 minigame4PCount = 0;
    u8 minigame1v3Count = 0;
    u8 minigame2v2Count = 0;
    u8 minigameItemCount = 0;
    u8 minigameBattleCount = 0;
    u8 minigameDuelCount = 0;

    mp2_ClearMinigameList();

    //load active minigames into lists
    for (i = 0; i < MINIGAME_END - 1; i++) {
        for (j = 0, curMinigameData = 0; j < MINIGAME_END - 1; j++) {
            if (i == minigameLUT[j].minigameIndex) {
                curMinigameData = &minigameLUT[j];
                break;
            }
        }

        //minigame was not found in list (??), continue loop
        if (curMinigameData == 0) {
            continue;
        }

        //else, minigame is active
        u8 minigameActiveFlag = GetMinigameFlag(curMinigameData->minigameIndex);
        if (minigameActiveFlag == 0) {
            continue;
        }

        switch(curMinigameData->minigameType) {
        case PLAYERS_4P:
            minigameIsBlacklisted = 0;
            for (j = 0; j < ARRAY_COUNT(mp2_minigame4PBlacklist); j++) {
                if (curMinigameData->minigameIndex == mp2_minigame4PBlacklist[j]) {
                    minigameIsBlacklisted = 1;
                    break;
                }
            }
            if (minigameIsBlacklisted == 0) {
                new4PMinigameListNormalMp2[minigame4PCount++] = curMinigameData->minigameIndex;
                newCategoryAmountsNormalMp2[PLAYERS_4P]++;
            }
            break;
        case PLAYERS_1V3:
            // minigameIsBlacklisted = 0;
            // for (j = 0; j < ARRAY_COUNT(minigame1v3Blacklist); j++) {
            //     if (curMinigameData->minigameIndex == minigame1v3Blacklist[j]) {
            //         minigameIsBlacklisted = 1;
            //         break;
            //     }
            // }
            // if (minigameIsBlacklisted == 0) {
            //     new1v3MinigameListNormalMp3[minigame1v3Count++] = curMinigameData->minigameIndex;
            //     newCategoryAmountsNormal[PLAYERS_1V3]++;
            // }
            new1v3MinigameListNormalMp2[minigame1v3Count++] = curMinigameData->minigameIndex;
            newCategoryAmountsNormalMp2[PLAYERS_1V3]++;
            break;
        case PLAYERS_2V2:
            new2v2MinigameListNormalMp2[minigame2v2Count++] = curMinigameData->minigameIndex;
            newCategoryAmountsNormalMp2[PLAYERS_2V2]++;
            break;
        case PLAYERS_ITEM:
            minigameIsBlacklisted = 0;
            for (j = 0; j < ARRAY_COUNT(mp2_itemMinigameBlacklist); j++) {
                if (curMinigameData->minigameIndex == mp2_itemMinigameBlacklist[j]) {
                    minigameIsBlacklisted = 1;
                    break;
                }
            }
            if (minigameIsBlacklisted == 0) {
                newItemMinigameListNormalMp2[minigameItemCount++] = curMinigameData->minigameIndex;
                newCategoryAmountsNormalMp2[PLAYERS_ITEM]++;
            }
            
            break;
        case PLAYERS_BATTLE:
            minigameIsBlacklisted = 0;
            for (j = 0; j < ARRAY_COUNT(mp2_battleMinigameBlacklist); j++) {
                if (curMinigameData->minigameIndex == mp2_battleMinigameBlacklist[j]) {
                    minigameIsBlacklisted = 1;
                    break;
                }
            }
            if (minigameIsBlacklisted == 0) {
                newBattleMinigameListNormalMp2[minigameBattleCount++] = curMinigameData->minigameIndex;
                newCategoryAmountsNormalMp2[PLAYERS_BATTLE]++;
            }

            break;
        case PLAYERS_DUEL:
            minigameIsBlacklisted = 0;
            for (j = 0; j < ARRAY_COUNT(mp2_duelMinigameBlacklist); j++) {
                if (curMinigameData->minigameIndex == mp2_duelMinigameBlacklist[j]) {
                    minigameIsBlacklisted = 1;
                    break;
                }
            }
            if (minigameIsBlacklisted == 0) {
                newDuelMinigameListNormalMp2[minigameDuelCount++] = curMinigameData->minigameIndex;
                newCategoryAmountsNormalMp2[PLAYERS_DUEL]++;
            }
            break;
        case PLAYERS_GAME_GUY:
            break;
        case PLAYERS_1P:
            break;
        }
    }
}

//func_80102AD8_36DC78_BootLogos
void mp2_newBootLogos(void) {
    s32 i;

    mp2_LoadMinigameList();

    if (ForeignMinigameAlreadyLoaded == TRUE) {
        if (CurBaseGame == MP2_BASE) {
            mp2_D_800E1F50_E2B50 = 1; //required for board events like star moving to work
            LoadBackIntoMp2Board();
            mp2_HuPrcEnd();
            while (1) {
                mp2_HuPrcVSleep();
            }
        } else if (CurBaseGame == MP1_BASE) {
            for (i = 0; i < 4; i++) {
                //award battle minigame coins/extra coins if they were collected
                if (isMidTurnMinigame == 1) {
                    for (i = 0; i < 4; i++) {
                        mp2_gPlayers[i].coins += mp2_gPlayers[i].coins_mg_bonus;
                    }
                }

                s32 coinsEarned = mp2_gPlayers[i].coins - mp1_PlayersCopy[i].coins;
                mp1_PlayersCopy[i].coins += coinsEarned;

                if (mp1_PlayersCopy[i].coins < 0) {
                    mp1_PlayersCopy[i].coins = 0;
                }
                
                mp1_PlayersCopy[i].mg_star_coins += coinsEarned;
                if (mp1_PlayersCopy[i].coins > mp1_PlayersCopy[i].coins_total) {
                    mp1_PlayersCopy[i].coins_total = mp1_PlayersCopy[i].coins;
                }
            }
            
            ComboSwitchGameToMp1();
            return;
        } else if (CurBaseGame == MP3_BASE) {
            //award battle minigame coins/extra coins if they were collected
            if (isMidTurnMinigame == 1) {
                for (i = 0; i < 4; i++) {
                    mp2_gPlayers[i].coins += mp2_gPlayers[i].coins_mg_bonus;
                }
            }

            for (i = 0; i < 4; i++) {
                s32 coinsEarned = mp2_gPlayers[i].coins - mp3_PlayersCopy[i].coins;
                mp3_PlayersCopy[i].coins += coinsEarned;

                if (mp3_PlayersCopy[i].coins < 0) {
                    mp3_PlayersCopy[i].coins = 0;
                }
                
                mp3_PlayersCopy[i].mg_star_coins += coinsEarned;
                if (mp3_PlayersCopy[i].coins > mp3_PlayersCopy[i].coins_total) {
                    mp3_PlayersCopy[i].coins_total = mp3_PlayersCopy[i].coins;
                }
            }
            ComboSwitchGameToMp3();
            return;
        }
    }

    if (CurBaseGame == MP2_BASE) {
        mp2_OriginalBootLogos();
        return;
    } else if (CurBaseGame == MP1_BASE && ForeignMinigameAlreadyLoaded == FALSE) {
        CopyMp1_gPlayerCopy_To_Mp2();
        mp2_D_800F93CD_F9FCD = mp1_GwSystemCopy.minigameExplanation; //minigame explanations on/off depending on mp2 setting
    } else if (CurBaseGame == MP3_BASE && ForeignMinigameAlreadyLoaded == FALSE) {
        CopyMp3_gPlayerCopy_To_Mp2();
        mp2_D_800F93CD_F9FCD = mp3_BoardStateCopy.show_minigame_explanations; //minigame explanations on/off depending on mp3 setting
    }

    //load minigame
    mp2_omInitObjMan(16, 4);
    mp2_D_800F93A8.unk_20 = ForeignMinigameIDToGame(ForeignMinigameIndexToLoad);
    mp2_D_800F93A8.unk_22 = 0x55;
    ForeignMinigameAlreadyLoaded = TRUE;
    isMidTurnMinigame = ForeignMinigameIsMidTurnMinigame(ForeignMinigameIndexToLoad);

    //used for item minigames, duels, and battle minigames
    if (isMidTurnMinigame == 1) {
        mp2_BattleMinigameCoins = mp3_BattleMinigameCoins_Copy;
    }

    mp2_omOvlCallEx(func_8003F6F0_402F0(mp2_D_800F93A8.unk_20), 0, 0x84);
    while (1) {
        mp2_HuPrcVSleep();
    }
}

void mp2_IfMidTurnMinigameCheck(void) {
    if (isMidTurnMinigame) {
        //this needs to be done here so turn status is popped correctly
        LoadMp2PlayerStructs();
        isMidTurnMinigame = 0;
        mp2_midTurnMinigameThing = 0xE;
    }
}
