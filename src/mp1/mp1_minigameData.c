#include "mp1.h"

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
