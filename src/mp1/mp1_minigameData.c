#include "mp1.h"
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

    for (i = 0; i < MP1_TOTAL_CATEGORIES; i++) {
        newCategoryAmountsNormalMp1[i] = 0;
    }
}

void mp1_ClearMinigameList(void);

void Mp1_LoadMinigameList(void) {
    MinigameIndexTable* curMinigameData;
    s32 i, j;
    s32 minigameIsBlacklisted;
    u8 minigame4PCount = 0;
    u8 minigame1v3Count = 0;
    u8 minigame2v2Count = 0;
    u8 minigameItemCount = 0;
    u8 minigameBattleCount = 0;
    u8 minigameDuelCount = 0;

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
        if (curMinigameData == NULL) {
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
                newCategoryAmountsNormalMp1[PLAYERS_4P]++;
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
            newCategoryAmountsNormalMp1[PLAYERS_1V3]++;
            break;
        case PLAYERS_2V2:
            new2v2MinigameListNormalMp1[minigame2v2Count++] = curMinigameData->minigameIndex;
            newCategoryAmountsNormalMp1[PLAYERS_2V2]++;
            break;
        case PLAYERS_ITEM:
            minigameIsBlacklisted = 0;
            if (minigameIsBlacklisted == 0) {
                newItemMinigameListNormalMp1[minigameItemCount++] = curMinigameData->minigameIndex;
                newCategoryAmountsNormalMp1[PLAYERS_ITEM]++;
            }
            
            break;
        case PLAYERS_BATTLE:
            minigameIsBlacklisted = 0;
            if (minigameIsBlacklisted == 0) {
                newBattleMinigameListNormalMp1[minigameBattleCount++] = curMinigameData->minigameIndex;
                newCategoryAmountsNormalMp1[PLAYERS_BATTLE]++;
            }

            break;
        case PLAYERS_DUEL:
            minigameIsBlacklisted = 0;
            if (minigameIsBlacklisted == 0) {
                newDuelMinigameListNormalMp1[minigameDuelCount++] = curMinigameData->minigameIndex;
                newCategoryAmountsNormalMp1[PLAYERS_DUEL]++;
            }
            break;
        case PLAYERS_GAME_GUY:
            break;
        case PLAYERS_1P:
            break;
        }
    }
}
