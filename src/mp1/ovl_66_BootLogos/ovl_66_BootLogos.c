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
NORETURN void ComboSwitchGameToMp3(void);
s32 mp1_omOvlCallEx(s32 arg0, s16 arg1, u16 arg2);
void CopyMp3_gPlayerCopy_To_Mp1(void);
void mp1_omInitObjMan(s32, s32);
void CopyMp2_gPlayerCopy_To_Mp1(void);
extern s16 mp1_D_800F5144;
extern s32 ForeignMinigameIndexToLoad;
extern s32 CurBaseGame;
extern u32 mp1_rnd_seed;
#define MP1_MINIGAME_PLAY 20
extern u8 mp1_prevMinigamesPlayed[MP1_MINIGAME_PLAY];
u8 mp1_prevMinigamesPlayedCopy[MP1_MINIGAME_PLAY] = {0};

//these probably dont need to be separate from mp3's list, but this provides a bit of clarity
#define MP1_4P_MINIGAME_MAX 66
#define MP1_1V3_MINIGAME_MAX 32
#define MP1_2V2_MINIGAME_MAX 28
#define MP1_BATTLE_MINIGAME_MAX 17
#define MP1_1P_MINIGAME_MAX 10
#define MP1_ITEM_MINIGAME_MAX 7
#define MP1_DUEL_MINIGAME_MAX 11
#define MP1_GAME_GUY_MINIGAME_MAX 4
#define MP1_TOTAL_CATEGORIES 8

#define MP1_PLAYERS_SPECIAL -1
#define MP1_PLAYERS_4P 0
#define MP1_PLAYERS_1V3 1
#define MP1_PLAYERS_2V2 2
#define MP1_PLAYERS_1P 3 //this clashes with the item minigames from other games...
#define MP1_PLAYERS_ITEM 4
#define MP1_PLAYERS_BATTLE 5
#define MP1_PLAYERS_DUEL 6
#define MP1_PLAYERS_GAME_GUY 7


u8 new4PMinigameListNormalMp1[MP1_4P_MINIGAME_MAX] = {0};
u8 new1v3MinigameListNormalMp1[MP1_1V3_MINIGAME_MAX] = {0};
u8 new2v2MinigameListNormalMp1[MP1_2V2_MINIGAME_MAX] = {0};
u8 newBattleMinigameListNormalMp1[MP1_BATTLE_MINIGAME_MAX] = {0};
u8 newItemMinigameListNormalMp1[MP1_ITEM_MINIGAME_MAX] = {0};
u8 newDuelMinigameListNormalMp1[MP1_DUEL_MINIGAME_MAX] = {0};
u8 newGameGuyMinigameListNormalMp1[MP1_GAME_GUY_MINIGAME_MAX] = {0};
u8 new1PMinigameListNormalMp1[MP1_1P_MINIGAME_MAX] = {0};
u8 newCategoryAmountsNormalMp1[MP1_TOTAL_CATEGORIES] = {0};

// u8 new4PMinigameListNormalMp1[MP1_4P_MINIGAME_MAX] = {0};
// u8 new1v3MinigameListNormalMp1[MP1_1V3_MINIGAME_MAX] = {0};
// u8 new2v2MinigameListNormalMp1[MP1_2V2_MINIGAME_MAX] = {0};
// u8 new1PMinigameListNormalMp1[MP1_1P_MINIGAME_MAX] = {0};
// u8 newCategoryAmountsNormalMp1[MP1_TOTAL_CATEGORIES] = {0};

//the blacklisted minigames below are blacklisted due to having issues loading them...
//once this is fixed this can be removed
u8 mp1_battleMinigameBlacklist[] = {
    // STACKED_DECK, THREE_DOOR_MONTY, MERRY_GO_CHOMP, SLAP_DOWN, LOCKED_OUT,
    // ALL_FIRED_UP, STORM_CHASERS, EYE_SORE
};

u8 mp1_duelMinigameBlacklist[] = {
    // VINE_WITH_ME, POPGUN_PICK_OFF, END_OF_THE_LINE, BABY_BOWSER_BONKERS, SILLY_SCREWS,
    // CROWD_COVER, TICK_TOCK_HOP, BOWSER_TOSS, MOTOR_ROOTER, FOWL_PLAY
};

u8 mp1_itemMinigameBlacklist[] = {
    // WINNERS_WHEEL, HEY_BATTER_BATTER, BOBBING_BOW_LOONS, DORRIE_DIP, SWINGING_WITH_SHARKS,
    // SWING_N_SWIPE
};

u8 mp1_minigame4PBlacklist[] = {
    #ifdef MP1
    YOSHIS_TONGUE_MEETING
    #endif
};

u8 mp1_minigame1PBlacklist[] = {
    #ifdef MP1
    SAME_GAME
    #endif
};

s16 mp1_getMinigameExplanationOverlay(s16 arg0) {
    s32 i;
    #ifdef MP1
    //confusing...but this should prevent converting an already converted ID
    if (ForeignMinigameAlreadyLoaded == TRUE) { 
        return mp1_GwSystem.curMinigame; //restore from hook
    }
    if (mp1_GwSystem.curMinigame >= MEMORY_MATCH && mp1_GwSystem.curMinigame <= PADDLE_BATTLE) { //mp1
        MinigameIndexTable* curMinigameData = NULL;
        for (i = 0; i < MINIGAME_END; i++) {
            if (mp1_GwSystem.curMinigame == minigameLUT[i].minigameIndex) {
                curMinigameData = &minigameLUT[i];
                break;
            }
        }
        mp1_GwSystem.curMinigame = curMinigameData->gameOverlayID;
        return mp1_GwSystem.curMinigame; //restore from hook
    }
    #endif
    if (mp1_GwSystem.curMinigame >= HAND_LINE_AND_SINKER && mp1_GwSystem.curMinigame <= MARIO_PUZZLE_PARTY_PRO) { //mp3
        SaveMp1PlayerStructs();
        PushMp1BoardState();
        PushMp1MinigamesPlayedList();
        ForeignMinigameIndexToLoad = mp1_GwSystem.curMinigame;
        ForeignMinigameAlreadyLoaded = FALSE;
        PushMp1OvlHis();
        ComboSwitchGameToMp3();
    } else { //mp2
        SaveMp1PlayerStructs();
        PushMp1BoardState();
        PushMp1MinigamesPlayedList();
        ForeignMinigameIndexToLoad = mp1_GwSystem.curMinigame;
        ForeignMinigameAlreadyLoaded = FALSE;
        PushMp1OvlHis();
        ComboSwitchGameToMp2();
    }
    return mp1_GwSystem.curMinigame; //restore from hook
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

    omOvlHisData NormalLoadInHis[] = {
        {0x81, 0x0000, 0x0091},
        {0x69, 0x0000, 0x0091},
        {0x35, 0x0001, 0x0092}
    };

    PopMp1BoardState();
    PopMp1MinigamesPlayedList();
    LoadMp1PlayerStructs();

    curTurn = mp1_GwSystem.currentTurn;
    totalTurns = mp1_GwSystem.maxTurns;
    curBoardIndex = mp1_GwSystem.curBoardIndex;

    isMidTurnMinigame = ForeignMinigameIsMidTurnMinigame(ForeignMinigameIndexToLoad);

    //if it's a midturn minigame, always boot back into the board (though this is impossible in mp1 currently)
    if (isMidTurnMinigame) {
        //copy a hardcoded overlay history in
        for (i = 0; i < ARRAY_COUNT(NormalLoadInHis); i++) {
            mp1_omovlhis[i] = NormalLoadInHis[i];
        }

        mp1_omovlhisidx = 2;
        //load into the board
        mp1_D_800D86B0 = 1; //required for board events to load back into the board correctly
        mp1_omOvlCallEx(0x36 + curBoardIndex, 2, 0x92);
        return;
    }

    //if game should end, load credits
    if (curTurn > totalTurns) {
        PopMp1OvlHis();
        mp1_omovlhisidx--;
        mp1_D_800D86B0 = 0; //required for board events to load back into the board correctly
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
        mp1_D_800D86B0 = 1; //required for board events to load back into the board correctly
        mp1_omOvlCallEx(0x3F, 0, 0x92); //last 5 turns
        return;
    }

    //copy a hardcoded overlay history in
    for (i = 0; i < ARRAY_COUNT(NormalLoadInHis); i++) {
        mp1_omovlhis[i] = NormalLoadInHis[i];
    }

    mp1_omovlhisidx = 2;
    //load into the board
    mp1_D_800D86B0 = 1; //required for board events to load back into the board correctly
    mp1_omOvlCallEx(0x36 + curBoardIndex, 2, 0x92);
}

void mp1_ClearMinigameList(void) {
    s32 i;
    
    for (i = 0; i < MP1_4P_MINIGAME_MAX; i++) {
        new4PMinigameListNormalMp1[i] = 0;
    }

    for (i = 0; i < MP1_1V3_MINIGAME_MAX; i++) {
        new1v3MinigameListNormalMp1[i] = 0;
    }

    for (i = 0; i < MP1_2V2_MINIGAME_MAX; i++) {
        new2v2MinigameListNormalMp1[i] = 0;
    }

    for (i = 0; i < MP1_BATTLE_MINIGAME_MAX; i++) {
        newBattleMinigameListNormalMp1[i] = 0;
    }

    for (i = 0; i < MP1_ITEM_MINIGAME_MAX; i++) {
        newItemMinigameListNormalMp1[i] = 0;
    }

    for (i = 0; i < MP1_DUEL_MINIGAME_MAX; i++) {
        newDuelMinigameListNormalMp1[i] = 0;
    }

    for (i = 0; i < MP1_GAME_GUY_MINIGAME_MAX; i++) {
        newGameGuyMinigameListNormalMp1[i] = 0;
    }

    for (i = 0; i < MP1_1P_MINIGAME_MAX; i++) {
        new1PMinigameListNormalMp1[i] = 0;
    }

    for (i = 0; i < MP1_TOTAL_CATEGORIES; i++) {
        newCategoryAmountsNormalMp1[i] = 0;
    }
}

void mp1_LoadMinigameList(void) {
    MinigameIndexTable* curMinigameData;
    s32 i, j;
    s32 minigameIsBlacklisted;
    u8 minigame4PCount = 0;
    u8 minigame1v3Count = 0;
    u8 minigame2v2Count = 0;
    u8 minigameItemCount = 0;
    u8 minigameBattleCount = 0;
    u8 minigameDuelCount = 0;
    u8 minigame1PCount = 0;

    mp1_ClearMinigameList();

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
            for (j = 0; j < ARRAY_COUNT(mp1_minigame4PBlacklist); j++) {
                if (curMinigameData->minigameIndex == mp1_minigame4PBlacklist[j]) {
                    minigameIsBlacklisted = 1;
                    break;
                }
            }
            if (minigameIsBlacklisted == 0) {
                new4PMinigameListNormalMp1[minigame4PCount++] = curMinigameData->minigameIndex;
                newCategoryAmountsNormalMp1[MP1_PLAYERS_4P]++;
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
            new1v3MinigameListNormalMp1[minigame1v3Count++] = curMinigameData->minigameIndex;
            newCategoryAmountsNormalMp1[MP1_PLAYERS_1V3]++;
            break;
        case PLAYERS_2V2:
            new2v2MinigameListNormalMp1[minigame2v2Count++] = curMinigameData->minigameIndex;
            newCategoryAmountsNormalMp1[MP1_PLAYERS_2V2]++;
            break;
        case PLAYERS_ITEM:
            // minigameIsBlacklisted = 0;
            // for (j = 0; j < ARRAY_COUNT(mp1_itemMinigameBlacklist); j++) {
            //     if (curMinigameData->minigameIndex == mp1_itemMinigameBlacklist[j]) {
            //         minigameIsBlacklisted = 1;
            //         break;
            //     }
            // }
            // if (minigameIsBlacklisted == 0) {
            //     newItemMinigameListNormalMp1[minigameItemCount++] = curMinigameData->minigameIndex;
            //     newCategoryAmountsNormalMp1[MP1_PLAYERS_ITEM]++;
            // }
            
            break;
        case PLAYERS_BATTLE:
            // minigameIsBlacklisted = 0;
            // for (j = 0; j < ARRAY_COUNT(mp1_battleMinigameBlacklist); j++) {
            //     if (curMinigameData->minigameIndex == mp1_battleMinigameBlacklist[j]) {
            //         minigameIsBlacklisted = 1;
            //         break;
            //     }
            // }
            // if (minigameIsBlacklisted == 0) {
            //     newBattleMinigameListNormalMp1[minigameBattleCount++] = curMinigameData->minigameIndex;
            //     newCategoryAmountsNormalMp1[MP1_PLAYERS_BATTLE]++;
            // }

            break;
        case PLAYERS_DUEL:
            // minigameIsBlacklisted = 0;
            // for (j = 0; j < ARRAY_COUNT(mp1_duelMinigameBlacklist); j++) {
            //     if (curMinigameData->minigameIndex == mp1_duelMinigameBlacklist[j]) {
            //         minigameIsBlacklisted = 1;
            //         break;
            //     }
            // }
            // if (minigameIsBlacklisted == 0) {
            //     newDuelMinigameListNormalMp1[minigameDuelCount++] = curMinigameData->minigameIndex;
            //     newCategoryAmountsNormalMp1[MP1_PLAYERS_DUEL]++;
            // }
            break;
        case PLAYERS_GAME_GUY:
            break;
        case PLAYERS_1P:
            minigameIsBlacklisted = 0;
            for (j = 0; j < ARRAY_COUNT(mp1_minigame1PBlacklist); j++) {
                if (curMinigameData->minigameIndex == mp1_minigame1PBlacklist[j]) {
                    minigameIsBlacklisted = 1;
                    break;
                }
            }
            if (minigameIsBlacklisted == 0) {
                new1PMinigameListNormalMp1[minigame1PCount++] = curMinigameData->minigameIndex;
                newCategoryAmountsNormalMp1[MP1_PLAYERS_1P]++; //1p minigames are value 3 in this game
            }
            break;
        }
    }
}

//func_80102AD8_36DC78_BootLogos
void mp1_newBootLogos(void) {

    mp1_LoadMinigameList();

    if (ForeignMinigameAlreadyLoaded == TRUE) {
        if (CurBaseGame == MP1_BASE) {
            mp1_D_800D86B0 = 1; //required for board events to load correctly
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
        mp1_GwSystem.minigameExplanation = mp2_BoardStateCopy.minigameExplanations; //minigame explanations on/off depending on mp2 setting
    } else if (CurBaseGame == MP3_BASE && ForeignMinigameAlreadyLoaded == FALSE) {
        CopyMp3_gPlayerCopy_To_Mp1();
        mp1_GwSystem.minigameExplanation = mp3_BoardStateCopy.show_minigame_explanations; //minigame explanations on/off depending on mp3 setting
    }
    
    mp1_omInitObjMan(16, 4);
    mp1_GwSystem.curMinigame = ForeignMinigameIDToGame(ForeignMinigameIndexToLoad);
    ForeignMinigameAlreadyLoaded = TRUE;
    mp1_omOvlCallEx(0x6F, 0, 0x84);
    while (1) {
        mp1_HuPrcVSleep();
    }
}