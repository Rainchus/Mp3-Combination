#include "mp3.h"

#define MP3_4P_MINIGAME_MAX 66
#define MP3_1V3_MINIGAME_MAX 32
#define MP3_2V2_MINIGAME_MAX 28
#define MP3_BATTLE_MINIGAME_MAX 17
#define MP3_ITEM_MINIGAME_MAX 7
#define MP3_DUEL_MINIGAME_MAX 16
#define MP3_TOTAL_CATEGORIES 6

u8 new4PMinigameListNormalMp3[MP3_4P_MINIGAME_MAX] = {0};
u8 new1v3MinigameListNormalMp3[MP3_1V3_MINIGAME_MAX] = {0};
u8 new2v2MinigameListNormalMp3[MP3_2V2_MINIGAME_MAX] = {0};
u8 newBattleMinigameListNormalMp3[MP3_BATTLE_MINIGAME_MAX] = {0};
u8 newItemMinigameListNormalMp3[MP3_ITEM_MINIGAME_MAX] = {0};
u8 newDuelMinigameListNormalMp3[MP3_DUEL_MINIGAME_MAX] = {0};
u8 newCategoryAmountsNormalMp3[MP3_TOTAL_CATEGORIES] = {0};

//the blacklisted minigames below are blacklisted due to having issues loading them...
//once this is fixed this can be removed
u8 mp3_battleMinigameBlacklist[] = {
    // MP2_GRAB_BAG, BUMPER_BALLOON_CARS, RAKIN_EM_IN, DAY_AT_THE_RACES, MP2_FACE_LIFT,
    // MP2_CRAZY_CUTTERS, MP2_HOT_BOB_OMB, BOWSERS_BIG_BLAST
};

//blacklist mp2 duels while playing mario party 3
u8 mp3_duelMinigameBlacklist[] = {
    PIRATE_LAND_DUEL, WESTERN_LAND_DUEL, SPACE_LAND_DUEL, MYSTERY_LAND_DUEL, HORROR_LAND_DUEL,
    KOOPA_LAND_DUEL
};

u8 mp3_itemMinigameBlacklist[] = {
    ROLL_OUT_THE_BARRELS, GIVE_ME_A_BRAKE, HAMMER_SLAMMER, MALLET_GO_ROUND, COFFIN_CONGESTION,
    BOWSER_SLOTS
};

u8 mp3_minigame4PBlacklist[] = {
    #ifdef MP1
    YOSHIS_TONGUE_MEETING
    #endif
};

s32 GetMinigameFlag(s32 arg0) {
    return (customEepromData.minigameFlags[arg0 / 8] >> (arg0 % 8)) & 1;
}

void SetMinigameFlag(s32 arg0) {
    customEepromData.minigameFlags[arg0 / 8] |= (1 << (arg0 % 8));
}

void ClearMinigameFlag(s32 arg0) {
    customEepromData.minigameFlags[arg0 / 8] &= ~(1 << (arg0 % 8));
}

void FlipMinigameFlag(s32 flag) {
    s32 minigameFlag = GetMinigameFlag(flag);
    if (minigameFlag) {
        ClearMinigameFlag(minigameFlag);
    } else {
        SetMinigameFlag(minigameFlag);
    }
}

static void mp3_ClearMinigameList(void) {
    s32 i;

    for (i = 0; i < MP3_4P_MINIGAME_MAX; i++) {
        new4PMinigameListNormalMp3[i] = 0;
    }

    for (i = 0; i < MP3_1V3_MINIGAME_MAX; i++) {
        new1v3MinigameListNormalMp3[i] = 0;
    }

    for (i = 0; i < MP3_2V2_MINIGAME_MAX; i++) {
        new2v2MinigameListNormalMp3[i] = 0;
    }

    for (i = 0; i < MP3_BATTLE_MINIGAME_MAX; i++) {
        newBattleMinigameListNormalMp3[i] = 0;
    }

    for (i = 0; i < MP3_ITEM_MINIGAME_MAX; i++) {
        newItemMinigameListNormalMp3[i] = 0;
    }

    for (i = 0; i < MP3_DUEL_MINIGAME_MAX; i++) {
        newDuelMinigameListNormalMp3[i] = 0;
    }

    for (i = 0; i < MP3_TOTAL_CATEGORIES; i++) {
        newCategoryAmountsNormalMp3[i] = 0;
    }
}

void mp3_LoadMinigameList(void) {
    MinigameIndexTable* curMinigameData;
    s32 i, j;
    s32 minigameIsBlacklisted;
    u8 minigame4PCount = 0;
    u8 minigame1v3Count = 0;
    u8 minigame2v2Count = 0;
    u8 minigameItemCount = 0;
    u8 minigameBattleCount = 0;
    u8 minigameDuelCount = 0;

    mp3_ClearMinigameList();

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
            for (j = 0; j < ARRAY_COUNT(mp3_minigame4PBlacklist); j++) {
                if (curMinigameData->minigameIndex == mp3_minigame4PBlacklist[j]) {
                    minigameIsBlacklisted = 1;
                    break;
                }
            }
            if (minigameIsBlacklisted == 0) {
                new4PMinigameListNormalMp3[minigame4PCount++] = curMinigameData->minigameIndex;
                newCategoryAmountsNormalMp3[PLAYERS_4P]++;
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
            new1v3MinigameListNormalMp3[minigame1v3Count++] = curMinigameData->minigameIndex;
            newCategoryAmountsNormalMp3[PLAYERS_1V3]++;
            break;
        case PLAYERS_2V2:
            new2v2MinigameListNormalMp3[minigame2v2Count++] = curMinigameData->minigameIndex;
            newCategoryAmountsNormalMp3[PLAYERS_2V2]++;
            break;
        case PLAYERS_ITEM:
            minigameIsBlacklisted = 0;
            for (j = 0; j < ARRAY_COUNT(mp3_itemMinigameBlacklist); j++) {
                if (curMinigameData->minigameIndex == mp3_itemMinigameBlacklist[j]) {
                    minigameIsBlacklisted = 1;
                    break;
                }
            }
            if (minigameIsBlacklisted == 0) {
                newItemMinigameListNormalMp3[minigameItemCount++] = curMinigameData->minigameIndex;
                newCategoryAmountsNormalMp3[PLAYERS_ITEM]++;
            }
            
            break;
        case PLAYERS_BATTLE:
            minigameIsBlacklisted = 0;
            for (j = 0; j < ARRAY_COUNT(mp3_battleMinigameBlacklist); j++) {
                if (curMinigameData->minigameIndex == mp3_battleMinigameBlacklist[j]) {
                    minigameIsBlacklisted = 1;
                    break;
                }
            }
            if (minigameIsBlacklisted == 0) {
                newBattleMinigameListNormalMp3[minigameBattleCount++] = curMinigameData->minigameIndex;
                newCategoryAmountsNormalMp3[PLAYERS_BATTLE]++;
            }

            break;
        case PLAYERS_DUEL:
            minigameIsBlacklisted = 0;
            for (j = 0; j < ARRAY_COUNT(mp3_duelMinigameBlacklist); j++) {
                if (curMinigameData->minigameIndex == mp3_duelMinigameBlacklist[j]) {
                    minigameIsBlacklisted = 1;
                    break;
                }
            }
            if (minigameIsBlacklisted == 0) {
                newDuelMinigameListNormalMp3[minigameDuelCount++] = curMinigameData->minigameIndex;
                newCategoryAmountsNormalMp3[PLAYERS_DUEL]++;
            }
            break;
        case PLAYERS_GAME_GUY:
            break;
        case PLAYERS_1P:
            break;
        }
    }
}

//easy data, not edited
u8 new4PMinigameListEasyMp3[] = {0x15, 0x19, 0x1C, 0x1D, 0x1E, 0x21, 0x22, 0x26, 0x28};
u8 new1v3MinigameListEasyMp3[] = {0x02, 0x03, 0x04, 0x05, 0x06, 0x09, 0x0A};
u8 new2v2MinigameListEasyMp3[] = {0x0B, 0x0C, 0x10, 0x11, 0x13};
u8 newBattleMinigameListEasyMp3[] = {0x2A, 0x2B, 0x2D, 0x2E};
u8 newItemMinigameListEasyMp3[] = {0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40};
u8 newDuelMinigameListEasyMp3[] = {0x31, 0x32, 0x33, 0x35, 0x37, 0x38, 0x39};

//at 80100EF4 originally (easy minigame list, amount of minigames in each category)
u8 newCategoryAmountsEasy[] = {
    ARRAY_COUNT(new4PMinigameListEasyMp3),
    ARRAY_COUNT(new1v3MinigameListEasyMp3),
    ARRAY_COUNT(new2v2MinigameListEasyMp3),
    ARRAY_COUNT(newBattleMinigameListEasyMp3),
    ARRAY_COUNT(newItemMinigameListEasyMp3),
    ARRAY_COUNT(newDuelMinigameListEasyMp3),
};

void GetNewMinigameString1(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 minigameCombinedIndex = arg1 - 0x46FF;

    s32 i;
    for (i = 0; i < MINIGAME_END; i++) {
        if (minigameCombinedIndex == minigameLUT[i].minigameIndex) {
            mp3_func_8005B43C_5C03C(arg0, minigameLUT[i].minigameStr, arg2, arg3);
            return;
        }
    }
    mp3_func_8005B43C_5C03C(arg0, (char*)arg1, arg2, arg3);
}