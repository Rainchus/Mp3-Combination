#include "mp2.h"

void mp2_UnkCamThing(f32);

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

// u8 mp2_battleMinigameBlacklist[] = {
//     // STACKED_DECK, THREE_DOOR_MONTY, MERRY_GO_CHOMP, SLAP_DOWN, LOCKED_OUT,
//     // ALL_FIRED_UP, STORM_CHASERS, EYE_SORE
// };

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
            // for (j = 0; j < ARRAY_COUNT(mp2_battleMinigameBlacklist); j++) {
            //     if (curMinigameData->minigameIndex == mp2_battleMinigameBlacklist[j]) {
            //         minigameIsBlacklisted = 1;
            //         break;
            //     }
            // }
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

void mp2_Unk_Camera_Function(f32 arg0) {
    if (arg0 == 0.0f) {
        arg0 = 1.0f;
    }
    mp2_UnkCamThing(arg0);
}