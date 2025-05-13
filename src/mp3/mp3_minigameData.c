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