#include "mp1.h"
//these probably dont need to be separate from mp3's list, but this provides a bit of clarity
#define MP1_4P_MINIGAME_MAX 66
#define MP1_1V3_MINIGAME_MAX 32
#define MP1_2V2_MINIGAME_MAX 28
#define MP1_BATTLE_MINIGAME_MAX 17
#define MP1_1P_MINIGAME_MAX 11
#define MP1_ITEM_MINIGAME_MAX 7
#define MP1_DUEL_MINIGAME_MAX 11
#define MP1_GAME_GUY_MINIGAME_MAX 4
#define MP1_TOTAL_CATEGORIES 4

#define MP1_PLAYERS_SPECIAL -1
#define MP1_PLAYERS_4P 0
#define MP1_PLAYERS_1V3 1
#define MP1_PLAYERS_2V2 2
#define MP1_PLAYERS_1P 3 //this clashes with the item minigames from other games...
// #define MP1_PLAYERS_ITEM 4
// #define MP1_PLAYERS_BATTLE 5
// #define MP1_PLAYERS_DUEL 6
// #define MP1_PLAYERS_GAME_GUY 7


u8 new4PMinigameListNormalMp1[MP1_4P_MINIGAME_MAX] = {0};
u8 new1v3MinigameListNormalMp1[MP1_1V3_MINIGAME_MAX] = {0};
u8 new2v2MinigameListNormalMp1[MP1_2V2_MINIGAME_MAX] = {0};
u8 newBattleMinigameListNormalMp1[MP1_BATTLE_MINIGAME_MAX] = {0};
u8 newItemMinigameListNormalMp1[MP1_ITEM_MINIGAME_MAX] = {0}; //replaced by new1PMinigameListNormalMp1 in this game
u8 newDuelMinigameListNormalMp1[MP1_DUEL_MINIGAME_MAX] = {0};
u8 newGameGuyMinigameListNormalMp1[MP1_GAME_GUY_MINIGAME_MAX] = {0};
u8 new1PMinigameListNormalMp1[MP1_1P_MINIGAME_MAX] = {0};
u8 newCategoryAmountsNormalMp1[MP1_TOTAL_CATEGORIES] = {0};

u8* newMp1MinigameLists[] = {
    new4PMinigameListNormalMp1,
    new1v3MinigameListNormalMp1,
    new2v2MinigameListNormalMp1,
    new1PMinigameListNormalMp1
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

//since 1p minigame in mp1 are ID 3 and clash with item minigames in mp2/mp3, blacklist the item minigames from mp1
u8 mp1_itemMinigameBlacklist[] = {
    ROLL_OUT_THE_BARRELS, GIVE_ME_A_BRAKE, HAMMER_SLAMMER, MALLET_GO_ROUND, COFFIN_CONGESTION,
    BOWSER_SLOTS, WINNERS_WHEEL, HEY_BATTER_BATTER, BOBBING_BOW_LOONS, DORRIE_DIP, SWINGING_WITH_SHARKS,
    SWING_N_SWIPE,
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

    for (i = 0; i < MP1_1P_MINIGAME_MAX; i++) {
        new1PMinigameListNormalMp1[i] = 0;
    }

    for (i = 0; i < MP1_DUEL_MINIGAME_MAX; i++) {
        newDuelMinigameListNormalMp1[i] = 0;
    }

    for (i = 0; i < MP1_TOTAL_CATEGORIES; i++) {
        newCategoryAmountsNormalMp1[i] = 0;
    }
}

void mp1_ClearMinigameList(void);

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
        // u8 minigameActiveFlag = GetMinigameFlag(curMinigameData->minigameIndex);
        // if (minigameActiveFlag == 0) {
        //     continue;
        // }

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
        case PLAYERS_1P:
            minigameIsBlacklisted = 0;
            for (j = 0; j < ARRAY_COUNT(mp1_itemMinigameBlacklist); j++) {
                if (curMinigameData->minigameIndex == mp1_itemMinigameBlacklist[j]) {
                    minigameIsBlacklisted = 1;
                    break;
                }
            }
            if (minigameIsBlacklisted == 0) {
                new1PMinigameListNormalMp1[minigameItemCount++] = curMinigameData->minigameIndex;
                newCategoryAmountsNormalMp1[PLAYERS_ITEM]++; //Hack due to clash between 1p minigames and item minigames mentioned earlier
            } 
            break;
        }
    }
}


// u8 minigames[] = {
//     TREADMILL_GRILL, TOADSTOOL_TITAN, ACES_HIGH, BOUNCE_N_TROUNCE, ICE_RINK_RISK, CHIP_SHOT_CHALLENGE, PARASOL_PLUMMET, MESSY_MEMORY,
//     PICTURE_IMPERFECT, MARIOS_PUZZLE_PARTY, THE_BEAT_GOES_ON, MPIQ, CURTAIN_CALL, WATER_WHIRLED, FRIGID_BRIDGES, AWFUL_TOWER,
//     CHEEP_CHEEP_CHASE, PIPE_CLEANERS, SNOWBALL_SUMMIT, ROCKIN_RACEWAY, LAVA_TILE_ISLE, MP2_HOT_ROPE_JUMP, SHELL_SHOCKED, TOAD_IN_THE_BOX,
//     MECHA_MARATHON, ROLL_CALL, ABANDON_SHIP, MP2_PLATFORM_PERIL, TOTEM_POLE_POUND, MP2_BUMPER_BALLS, MP2_BOMBS_AWAY, MP2_TIPSY_TOURNEY,
//     HONEYCOMB_HAVOC, HEXAGON_HEAT, MP2_SKATEBOARD_SCAMPER, MP2_SLOT_CAR_DERBY, MP2_SHY_GUY_SAYS, SNEAK_N_SNORE, DIZZY_DANCING, TILE_DRIVER,
//     DEEP_SEA_SALVAGE, BURIED_TREASURE, TREASURE_DIVERS, MP1_HOT_BOB_OMB, MUSICAL_MUSHROOM, MP1_CRAZY_CUTTER, MP1_FACE_LIFT, MP1_BALLOON_BURST,
//     COIN_BLOCK_BLITZ, MP1_SKATEBOARD_SCAMPER, BOX_MOUNTAIN_MAYHEM, MP1_PLATFORM_PERIL, MUSHROOM_MIXUP, HAMMER_DROP, MP1_GRAB_BAG, MP1_BUMPER_BALLS,
//     MP1_TIPSY_TOURNEY, MP1_BOMBS_AWAY, MP1_SLOT_CAR_DERBY, MARIO_BANDSTAND, MP1_SHY_GUY_SAYS, CAST_AWAYS, KEY_PA_WAY, RUNNING_OF_THE_BULB,
//     MP1_HOT_ROPE_JUMP
// };