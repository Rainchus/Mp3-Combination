#include "marioparty.h"
#include "mp3.h"
#include "mp2.h"
#include "mp1.h"

s16 mp1_InitSprite(s32);
void mp1_SetBasicSpritePos(s32, s32, s32);
void mp1_SetFadeInTypeAndTime(s32, s32);
void mp1_ShowBasicSprite(s32);
void mp1_func_80018D84(s32, s32);
s32 mp1_func_80019060(s16, s32, s32);
void mp1_func_800191F8(s32);
void mp1_func_80067704(s16);
void mp1_func_800726AC(s32, s32);
s32 mp1_func_80072718(void);
void mp1_HuPrcVSleep(void);
void mp1_HuPrcSleep(s32);
NORETURN void ComboSwitchGameToMp3(void);
s32 mp1_omOvlCallEx(s32 arg0, s16 arg1, u16 arg2);
void CopyMp3_gPlayerCopy_To_Mp1(void);
void mp1_omInitObjMan(s32, s32);
void CopyMp2_gPlayerCopy_To_Mp1(void);
extern s16 mp1_D_800F5144;
extern s32 ForeignMinigameIndexToLoad;
extern s32 CurBaseGame;
extern u32 mp1_rnd_seed;
extern u8 mp3_BoardStateCopy[BOARD_STATE_STRUCT_SIZE];
#define MP1_MINIGAME_PLAY 20
extern u8 mp1_prevMinigamesPlayed[MP1_MINIGAME_PLAY];
u8 mp1_prevMinigamesPlayedCopy[MP1_MINIGAME_PLAY] = {0};

//these probably dont need to be separate from mp3's list, but this provides a bit of clarity
#define MP1_4P_MINIGAME_MAX 66
#define MP1_1V3_MINIGAME_MAX 32
#define MP1_2V2_MINIGAME_MAX 28
#define MP1_BATTLE_MINIGAME_MAX 17
#define MP1_ITEM_MINIGAME_MAX 7
#define MP1_DUEL_MINIGAME_MAX 11
#define MP1_TOTAL_CATEGORIES 6

u8 new4PMinigameListNormalMp1[MP1_4P_MINIGAME_MAX] = {0};
u8 new1v3MinigameListNormalMp1[MP1_1V3_MINIGAME_MAX] = {0};
u8 new2v2MinigameListNormalMp1[MP1_2V2_MINIGAME_MAX] = {0};
u8 newBattleMinigameListNormalMp1[MP1_BATTLE_MINIGAME_MAX] = {0};
u8 newItemMinigameListNormalMp1[MP1_ITEM_MINIGAME_MAX] = {0};
u8 newDuelMinigameListNormalMp1[MP1_DUEL_MINIGAME_MAX] = {0};
u8 newCategoryAmountsNormalMp1[MP1_TOTAL_CATEGORIES] = {0};

s16 mp1_getMinigameExplanationOverlay(s16 arg0) {
    s32 i;

    mp1_D_800F64F2 = 1;
    if (mp1_D_800ED5DE >= MEMORY_MATCH && mp1_D_800ED5DE <= PADDLE_BATTLE) { //mp1
        MinigameIndexTable* curMinigameData = NULL;
        for (i = 0; i < MINIGAME_END; i++) {
            if (mp1_D_800ED5DE == minigameLUT[i].minigameIndex) {
                curMinigameData = &minigameLUT[i];
                break;
            }
        }
        mp1_D_800ED5DE = curMinigameData->gameOverlayID;
    } else if (mp1_D_800ED5DE >= HAND_LINE_AND_SINKER && mp1_D_800ED5DE <= MARIO_PUZZLE_PARTY_PRO) { //mp3
        SaveMp1PlayerStructs();
        PushMp1BoardState();
        PushMp1MinigamesPlayedList();
        ForeignMinigameIndexToLoad = mp1_D_800ED5DE;
        ForeignMinigameAlreadyLoaded = FALSE;
        PushMp1OvlHis();
        ComboSwitchGameToMp3();
    } else { //mp2
        SaveMp1PlayerStructs();
        PushMp1BoardState();
        PushMp1MinigamesPlayedList();
        ForeignMinigameIndexToLoad = mp1_D_800ED5DE;
        ForeignMinigameAlreadyLoaded = FALSE;
        PushMp1OvlHis();
        ComboSwitchGameToMp2();
    }
    return mp1_D_800ED5DE;
}

void mp1_GetNewMinigameString(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 minigameCombinedIndex = arg1 - 0x324;
    s32 i;

    for (i = 0; i < MINIGAME_END; i++) {
        if (minigameCombinedIndex == minigameLUT[i].minigameIndex) {
            //skip first 0xB character since mp1 displays a bit different from mp2 and mp3
            mp1_func_8006D7D8(arg0, &minigameLUT[i].minigameStr[1], arg2, arg3);
            return;
        }
    }
    mp1_func_8006D7D8(arg0, (char*)arg1, arg2, arg3);
}

void SaveMp1PlayerStructs(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        mp1_PlayersCopy[i] = mp1_gPlayers[i];
    }
}

void PushMp1MinigamesPlayedList(void) {
    s32 i;

    for (i = 0; i < 0x14; i++) {
        mp1_prevMinigamesPlayedCopy[i] = mp1_prevMinigamesPlayed[i];
    }
}

void PopMp1MinigamesPlayedList(void) {
    s32 i;

    for (i = 0; i < 0x14; i++) {
        mp1_prevMinigamesPlayed[i] = mp1_prevMinigamesPlayedCopy[i];
    }
}

//func_800F686C_LogosSequence
void mp1_OriginalBootLogos(void) {
    s16 temp_v0;
    s16 temp_v0_3;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_v0_2;
    s32 temp_v0_4;

    temp_v0 = mp1_InitSprite(0x9006D);
    temp_v0_2 = mp1_func_80019060(temp_v0, 0, 1);
    temp_s0 = temp_v0_2 & 0xFFFF;
    mp1_SetBasicSpritePos(temp_s0, 0xA0, 0x78);
    mp1_ShowBasicSprite(temp_s0);
    mp1_func_80018D84(temp_s0, 0xFFFF);
    mp1_SetFadeInTypeAndTime(0, 5);
    
    while (mp1_func_80072718() != 0) {
        mp1_HuPrcVSleep();
    }
    
    mp1_HuPrcSleep(5);
    mp1_func_800726AC(0, 5);
    
    while (mp1_func_80072718() != 0) {
        mp1_HuPrcVSleep();
    }
    
    mp1_func_800191F8(temp_v0_2 & 0xFFFF);
    mp1_func_80067704(temp_v0);
    mp1_HuPrcSleep(5);
    temp_v0_3 = mp1_InitSprite(0x9006E);
    temp_v0_4 = mp1_func_80019060(temp_v0_3, 0, 1);
    temp_s0_2 = temp_v0_4 & 0xFFFF;
    mp1_SetBasicSpritePos(temp_s0_2, 0xA0, 0x78);
    mp1_ShowBasicSprite(temp_s0_2);
    mp1_func_80018D84(temp_s0_2, 0xFFFF);
    mp1_SetFadeInTypeAndTime(0, 5);
    
    while (mp1_func_80072718() != 0) {
        mp1_HuPrcVSleep();
    }
    
    mp1_HuPrcSleep(5);
    mp1_func_800726AC(0, 5);
    
    while (mp1_func_80072718() != 0) {
        mp1_HuPrcVSleep();
    }
    
    mp1_func_800191F8(temp_v0_4 & 0xFFFF);
    mp1_func_80067704(temp_v0_3);
    mp1_HuPrcSleep(5);
    temp_s0_3 = mp1_func_80019060(mp1_InitSprite(0x9006F), 0, 1) & 0xFFFF;
    mp1_SetBasicSpritePos(temp_s0_3, 0xA0, 0x78);
    mp1_ShowBasicSprite(temp_s0_3);
    mp1_func_80018D84(temp_s0_3, 0xFFFF);
    mp1_SetFadeInTypeAndTime(0, 5);

    while (mp1_func_80072718() != 0) {
        mp1_HuPrcVSleep();
    }
    
    mp1_HuPrcSleep(5);
    mp1_D_800F5144 = 1;
    
    while (1) {
        mp1_HuPrcVSleep();
    }
}

void LoadBackIntoMp1Board(void) {
    s8 curTurn;
    s8 totalTurns;
    s8 curBoardIndex;
    s32 i;

    PopMp1BoardState();
    PopMp1MinigamesPlayedList();
    LoadMp1PlayerStructs();

    curTurn = mp1_BoardState.curTurn;
    totalTurns = mp1_BoardState.maxTurns;
    curBoardIndex = mp1_BoardState.curBoardIndex;

    if (curTurn > totalTurns) {
        PopMp1OvlHis();
        mp1_omovlhisidx--;
        // mp2_D_800E1F50_E2B50 = 0;
        // mp2_D_800E1F52_E2B52 = 0;
        mp1_omOvlCallEx(0x43, 0, 0x92); //go to end of game scene
        return;
    } else if ((totalTurns - curTurn) == 4) {
        omOvlHisData last5Turns[] = {
            {0x0081, 0x0000, 0x0091},
            {0x0069, 0x0000, 0x0091},
            {0x0035, 0x0001, 0x0092},
            {0x007C, 0x0001, 0x0014},
            {0x0017, 0x0000, 0x0014},
        };
        s32 i;
        for (i = 0; i < ARRAY_COUNT(last5Turns); i++) {
            mp1_omovlhis[i] = last5Turns[i];
        }
        mp1_omovlhisidx = 2;
        mp1_omOvlCallEx(0x3F, 0, 0x92); //last 5 turns
        return;
    }

    omOvlHisData NormalLoadInHis[] = {
        {0x81, 0x0000, 0x0091},
        {0x69, 0x0000, 0x0091},
        {0x35, 0x0001, 0x0092}
    };

    //copy a hardcoded overlay history in
    for (i = 0; i < ARRAY_COUNT(NormalLoadInHis); i++) {
        mp1_omovlhis[i] = NormalLoadInHis[i];
    }

    mp1_omovlhisidx = 2;
    //load into the board
    mp1_omOvlCallEx(0x36 + curBoardIndex, 2, 0x92);
}

//func_80102AD8_36DC78_BootLogos
void mp1_newBootLogos(void) {
    if (ForeignMinigameAlreadyLoaded == TRUE) {
        if (CurBaseGame == MP1_BASE) {
            //TODO: find this symbol in mp1
            //mp3_D_800CD2A2 = 1; //required for board events to load back into the board correctly
            LoadBackIntoMp1Board();
            mp1_HuPrcEnd();
            while (1) {
                mp1_HuPrcVSleep();
            }
        } else if (CurBaseGame == MP2_BASE) {
            s32 i;
            //copy over player changes
            for (i = 0; i < 4; i++) {
                s32 coinsEarned = mp1_gPlayers[i].coins - mp2_PlayersCopy[i].coins;
                mp2_PlayersCopy[i].coins += coinsEarned;

                if (mp2_PlayersCopy[i].coins < 0) {
                    mp2_PlayersCopy[i].coins = 0;
                }
                
                mp2_PlayersCopy[i].mg_star_coins += coinsEarned;
                if (mp2_PlayersCopy[i].coins > mp2_PlayersCopy[i].coins_total) {
                    mp2_PlayersCopy[i].coins_total = mp2_PlayersCopy[i].coins;
                }
            }
            
            ComboSwitchGameToMp2();
        } else if (CurBaseGame == MP3_BASE) {
            s32 i;
            //copy over player changes
            for (i = 0; i < 4; i++) {
                s32 coinsEarned = mp1_gPlayers[i].coins - mp3_PlayersCopy[i].coins;
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

    //if mp1 is base game, continue boot sequence as normal
    //otherwise, prepare to load minigames
    if (CurBaseGame == MP1_BASE && ForeignMinigameAlreadyLoaded == FALSE) {
        mp1_OriginalBootLogos();
        return;
    } else if (CurBaseGame == MP2_BASE && ForeignMinigameAlreadyLoaded == FALSE) {
        CopyMp2_gPlayerCopy_To_Mp1();
        mp1_D_800ED5E3 = mp2_BoardStateCopy.minigameExplanations; //minigame explanations on/off depending on mp2 setting
    } else if (CurBaseGame == MP3_BASE && ForeignMinigameAlreadyLoaded == FALSE) {
        CopyMp3_gPlayerCopy_To_Mp1();
        mp1_D_800ED5E3 = mp3_BoardStateCopy[0x13]; //minigame explanations on/off depending on mp3 setting
    }
    
    mp1_omInitObjMan(16, 4);
    mp1_D_800ED5DE = ForeignMinigameIDToGame(ForeignMinigameIndexToLoad);
    ForeignMinigameAlreadyLoaded = TRUE;
    mp1_omOvlCallEx(0x6F, 0, 0x84); //load explanation screen overlay (might be skipped depending on mp1_D_800ED5E3)
    while (1) {
        mp1_HuPrcVSleep();
    }
}