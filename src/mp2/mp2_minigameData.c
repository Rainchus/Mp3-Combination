#include "mp2.h"

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