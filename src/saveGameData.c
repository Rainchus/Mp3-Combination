//functions for saving/restoring game data between games
#include "marioparty.h"
#include "mp1.h"
#include "mp2.h"
#include "mp3.h"

s16 mp3_hidden_block_item_space_copy = 0;
s16 mp3_hidden_block_coins_space_copy = 0;
s16 mp3_hidden_block_star_space_copy = 0;

s16 mp2_hidden_block_coins_space_index_copy = 0;
s16 mp2_hidden_block_star_space_index_copy = 0;

extern s16 mp3_hidden_block_item_space_index; //hidden_block_item_space
extern s16 mp3_hidden_block_coins_space_index; //hidden_block_coins_space
extern s16 mp3_hidden_block_star_space_index; //hidden_block_star_space


void SaveMp3PlayerToMp3PlayerCopy(void) {
    for (int i = 0; i < 4; i++) {
        mp3_GwPlayerCopy[i] = mp3_GwPlayer[i];
    }
}

void SaveMp3PlayerCopyToMp3Player(void) {
    for (int i = 0; i < 4; i++) {
        mp3_GwPlayer[i] = mp3_GwPlayerCopy[i];
    }
}


void SaveMp2PlayerToMp2PlayerCopy(void) {
    for (int i = 0; i < 4; i++) {
        mp2_GwPlayerCopy[i] = mp2_GwPlayer[i];
    }
}

void SaveMp2PlayerCopyToMp2Player(void) {
    for (int i = 0; i < 4; i++) {
        mp2_GwPlayer[i] = mp2_GwPlayerCopy[i];
    }
}


void SaveMp1PlayerToMp1PlayerCopy(void) {
    for (int i = 0; i < 4; i++) {
        mp1_GwPlayerCopy[i] = mp1_GwPlayer[i];
    }
}

void SaveMp1PlayerCopyToMp1Player(void) {
    for (int i = 0; i < 4; i++) {
        mp1_GwPlayer[i] = mp1_GwPlayerCopy[i];
    }
}

//loading in from mp2 minigame back to mp3 board
void LoadMp2PlayerCopyToMp3(void) {
    for (int i = 0; i < 4; i++) {
        mp3_GwPlayer[i].group = mp2_GwPlayerCopy[i].group;
        mp3_GwPlayer[i].cpu_difficulty = mp2_GwPlayerCopy[i].cpu_difficulty;
        mp3_GwPlayer[i].cpu_difficulty = mp2_GwPlayerCopy[i].cpu_difficulty;
        mp3_GwPlayer[i].pad = mp2_GwPlayerCopy[i].pad;
        mp3_GwPlayer[i].stat = mp2_GwPlayerCopy[i].stat;
        mp3_GwPlayer[i].chr = mp2_GwPlayerCopy[i].chr;
        mp3_GwPlayer[i].coin = mp2_GwPlayerCopy[i].coin;
        mp3_GwPlayer[i].star = mp2_GwPlayerCopy[i].star;
    }
}

//loading in from mp1 minigame back to mp3 board
void LoadMp1PlayerCopyToMp3(void) {
    for (int i = 0; i < 4; i++) {
        mp3_GwPlayer[i].group = mp1_GwPlayerCopy[i].group;
        mp3_GwPlayer[i].cpu_difficulty = mp1_GwPlayerCopy[i].cpu_difficulty;
        mp3_GwPlayer[i].cpu_difficulty = mp1_GwPlayerCopy[i].cpu_difficulty;
        mp3_GwPlayer[i].pad = mp1_GwPlayerCopy[i].pad;
        mp3_GwPlayer[i].stat = mp1_GwPlayerCopy[i].stat;
        mp3_GwPlayer[i].chr = mp1_GwPlayerCopy[i].chr;
        mp3_GwPlayer[i].coin = mp1_GwPlayerCopy[i].coin;
        mp3_GwPlayer[i].star = mp1_GwPlayerCopy[i].star;
    }
}

//already loaded back into mp2, get data from mp3GwPlayerCopy
void LoadMp3PlayerCopyToMp2(void) {
    for (int i = 0; i < 4; i++) {
        mp2_GwPlayer[i].group = mp3_GwPlayerCopy[i].group;
        mp2_GwPlayer[i].cpu_difficulty = mp3_GwPlayerCopy[i].cpu_difficulty;
        mp2_GwPlayer[i].cpu_difficulty2 = mp3_GwPlayerCopy[i].cpu_difficulty;
        mp2_GwPlayer[i].pad = mp3_GwPlayerCopy[i].pad;
        mp2_GwPlayer[i].stat = mp3_GwPlayerCopy[i].stat;
        mp2_GwPlayer[i].chr = mp3_GwPlayerCopy[i].chr;
        mp2_GwPlayer[i].coin = mp3_GwPlayerCopy[i].coin;
        mp2_GwPlayer[i].star = mp3_GwPlayerCopy[i].star;
    }
}
//already loaded back into mp1, get data from mp3GwPlayerCopy
void LoadMp3PlayerCopyToMp1(void) {
    for (int i = 0; i < 4; i++) {
        mp1_GwPlayer[i].group = mp3_GwPlayerCopy[i].group;
        mp1_GwPlayer[i].cpu_difficulty = mp3_GwPlayerCopy[i].cpu_difficulty;
        mp1_GwPlayer[i].pad = mp3_GwPlayerCopy[i].pad;
        mp1_GwPlayer[i].stat = mp3_GwPlayerCopy[i].stat;
        mp1_GwPlayer[i].chr = mp3_GwPlayerCopy[i].chr;
        mp1_GwPlayer[i].coin = mp3_GwPlayerCopy[i].coin;
        mp1_GwPlayer[i].star = mp3_GwPlayerCopy[i].star;
    }
}

//already loaded back into mp2, get data from mp3GwPlayerCopy
void LoadMp1PlayerCopyToMp2(void) {
    for (int i = 0; i < 4; i++) {
        mp2_GwPlayer[i].group = mp1_GwPlayerCopy[i].group;
        mp2_GwPlayer[i].cpu_difficulty = mp1_GwPlayerCopy[i].cpu_difficulty;
        mp2_GwPlayer[i].cpu_difficulty2 = mp1_GwPlayerCopy[i].cpu_difficulty;
        mp2_GwPlayer[i].pad = mp1_GwPlayerCopy[i].pad;
        mp2_GwPlayer[i].stat = mp1_GwPlayerCopy[i].stat;
        mp2_GwPlayer[i].chr = mp1_GwPlayerCopy[i].chr;
        mp2_GwPlayer[i].coin = mp1_GwPlayerCopy[i].coin;
        mp2_GwPlayer[i].star = mp1_GwPlayerCopy[i].star;
    }
}

//already loaded back into mp1, get data from mp2GwPlayerCopy
void LoadMp2PlayerCopyToMp1(void) {
    for (int i = 0; i < 4; i++) {
        mp1_GwPlayer[i].group = mp2_GwPlayerCopy[i].group;
        mp1_GwPlayer[i].cpu_difficulty = mp2_GwPlayerCopy[i].cpu_difficulty;
        mp1_GwPlayer[i].pad = mp2_GwPlayerCopy[i].pad;
        mp1_GwPlayer[i].stat = mp2_GwPlayerCopy[i].stat;
        mp1_GwPlayer[i].chr = mp2_GwPlayerCopy[i].chr;
        mp1_GwPlayer[i].coin = mp2_GwPlayerCopy[i].coin;
        mp1_GwPlayer[i].star = mp2_GwPlayerCopy[i].star;
    }
}

//save mp3Player to mp1PlayerCopy before swapping to mp1
void SaveMp3PlayerToMp1PlayerCopy(void) {
    for (int i = 0; i < 4; i++) {
        mp1_GwPlayerCopy[i].group = mp3_GwPlayer[i].group;
        mp1_GwPlayerCopy[i].cpu_difficulty = mp3_GwPlayer[i].cpu_difficulty;
        mp1_GwPlayerCopy[i].cpu_difficulty = mp3_GwPlayer[i].cpu_difficulty;
        mp1_GwPlayerCopy[i].pad = mp3_GwPlayer[i].pad;
        mp1_GwPlayerCopy[i].stat = mp3_GwPlayer[i].stat;
        mp1_GwPlayerCopy[i].chr = mp3_GwPlayer[i].chr;
        mp1_GwPlayerCopy[i].bonusCoin = mp3_GwPlayer[i].bonusCoin;
    }
}

//save mp3Player to mp2PlayerCopy before swapping to mp2
void SaveMp3PlayerToMp2PlayerCopy(void) {
    for (int i = 0; i < 4; i++) {
        mp2_GwPlayerCopy[i].group = mp3_GwPlayer[i].group;
        mp2_GwPlayerCopy[i].cpu_difficulty = mp3_GwPlayer[i].cpu_difficulty;
        mp2_GwPlayerCopy[i].cpu_difficulty = mp3_GwPlayer[i].cpu_difficulty;
        mp2_GwPlayerCopy[i].pad = mp3_GwPlayer[i].pad;
        mp2_GwPlayerCopy[i].stat = mp3_GwPlayer[i].stat;
        mp2_GwPlayerCopy[i].chr = mp3_GwPlayer[i].chr;
        mp2_GwPlayerCopy[i].checkCoin = mp3_GwPlayer[i].checkCoin;
        mp2_GwPlayerCopy[i].bonusCoin = mp3_GwPlayer[i].bonusCoin;
    }
}

//save mp2 to mp1PlayerCopy before swapping to mp1
void SaveMp2PlayerToMp1PlayerCopy(void) {
    for (int i = 0; i < 4; i++) {
        mp1_GwPlayerCopy[i].group = mp2_GwPlayerCopy[i].group;
        mp1_GwPlayerCopy[i].cpu_difficulty  = mp2_GwPlayerCopy[i].cpu_difficulty;
        mp1_GwPlayerCopy[i].pad  = mp2_GwPlayerCopy[i].pad;
        mp1_GwPlayerCopy[i].stat  = mp2_GwPlayerCopy[i].stat;
        mp1_GwPlayerCopy[i].chr = mp2_GwPlayerCopy[i].chr;
    } 
}

//save mp2 to mp3PlayerCopy before swapping to mp3
void SaveMp2PlayerToMp3PlayerCopy(void) {
    for (int i = 0; i < 4; i++) {
        mp3_GwPlayerCopy[i].group = mp2_GwPlayer[i].group;
        mp3_GwPlayerCopy[i].cpu_difficulty = mp2_GwPlayer[i].cpu_difficulty;
        mp3_GwPlayerCopy[i].cpu_difficulty = mp2_GwPlayer[i].cpu_difficulty2;
        mp3_GwPlayerCopy[i].pad = mp2_GwPlayer[i].pad;
        mp3_GwPlayerCopy[i].stat = mp2_GwPlayer[i].stat;
        mp3_GwPlayerCopy[i].chr = mp2_GwPlayer[i].chr;
        mp3_GwPlayerCopy[i].checkCoin = mp2_GwPlayer[i].checkCoin;
        mp3_GwPlayerCopy[i].bonusCoin = mp2_GwPlayer[i].bonusCoin;
    }
}

//save mp1 to mp2PlayerCopy before swapping to mp2
void SaveMp1PlayerToMp2PlayerCopy(void) {
    for (int i = 0; i < 4; i++) {
        mp2_GwPlayerCopy[i].group = mp1_GwPlayer[i].group;
        mp2_GwPlayerCopy[i].cpu_difficulty = mp1_GwPlayer[i].cpu_difficulty;
        mp2_GwPlayerCopy[i].pad = mp1_GwPlayer[i].pad;
        mp2_GwPlayerCopy[i].stat = mp1_GwPlayer[i].stat;
        mp2_GwPlayerCopy[i].chr = mp1_GwPlayer[i].chr;

    } 
}

//save mp1 to mp3PlayerCopy before swapping to mp3
void SaveMp1PlayerToMp3PlayerCopy(void) {
    for (int i = 0; i < 4; i++) {
        mp3_GwPlayerCopy[i].group = mp1_GwPlayer[i].group;
        mp3_GwPlayerCopy[i].cpu_difficulty = mp1_GwPlayer[i].cpu_difficulty;
        mp3_GwPlayerCopy[i].pad = mp1_GwPlayer[i].pad;
        mp3_GwPlayerCopy[i].stat = mp1_GwPlayer[i].stat;
        mp3_GwPlayerCopy[i].chr = mp1_GwPlayer[i].chr;
    } 
}

/* -- functions related to pushing/popping the game state -- */
extern u8 mp3_D_800B23B0;
extern u8 mp3_D_800B23B1;
extern u8 mp3_D_800D030A;
extern u8 mp3_D_800D0308; //mp3 story progress byte
extern u8 mp3_D_800D0309;

mp3_GW_SYSTEM mp3_GwSystemCopy = {0};
u8 mp3_ModeCopy = 0;
u8 mp3_ModeCopy2 = 0;
u8 mp3_StoryDifficultyCopy = 0;
u8 mp3_StoryProgressCopy = 0;
u8 mp3_StorychrID = 0;
u8 mp3_prevMinigamesPlayedCopy[PREV_MINIGAMES_PLAYED_SIZE] = {0};
s16 mp3_BattleMinigameCoins_Copy = 0;

void PushMp3BoardState(void) {
    mp3_GwSystemCopy = mp3_GwSystem;
    mp3_ModeCopy = mp3_D_800B23B0;
    mp3_ModeCopy2 = mp3_D_800B23B1;
    mp3_StoryDifficultyCopy = mp3_D_800D030A;
    mp3_StoryProgressCopy = mp3_D_800D0308;
    mp3_StorychrID = mp3_D_800D0309;
}

void PopMp3BoardState(void) {
    mp3_GwSystem = mp3_GwSystemCopy;
    mp3_D_800B23B0 = mp3_ModeCopy;
    mp3_D_800B23B1 = mp3_ModeCopy2;
    mp3_D_800D030A = mp3_StoryDifficultyCopy;
    mp3_D_800D0308 = mp3_StoryProgressCopy;
    mp3_D_800D0309 = mp3_StorychrID;
}

extern u16 mp2_BankCoins;
u16 mp2_BankCoinsCopy = 0;
s16 mp2_BattleMinigameCoins_Copy = 0;

//unsure how much of this is actually relevant
#define MP2_BOARD_DATA_SIZE 0x20
#define MP2_PREV_MINIGAMES_PLAYED_SIZE 0x1E //TODO:make sure this works

mp2_GW_SYSTEM mp2_GwSystemCopy = {0};
u8 mp2_OtherBoardStateCopy[MP2_BOARD_DATA_SIZE] = {0};
u8 mp2_prevMinigamesPlayedCopy[MP2_PREV_MINIGAMES_PLAYED_SIZE] = {0};
extern u8 mp2_OtherBoardState[MP2_BOARD_DATA_SIZE];
extern u8 mp2_prevMinigamesPlayed[MP2_PREV_MINIGAMES_PLAYED_SIZE];
extern u16 mp2_BattleMinigameCoins;

void PushMp2BoardState(void) {
    s32 i;

    mp2_GwSystemCopy = mp2_GwSystem;
    for (i = 0; i < MP2_BOARD_DATA_SIZE; i++) {
        mp2_OtherBoardStateCopy[i] = mp2_OtherBoardState[i];
    }
    mp2_BankCoinsCopy = mp2_BankCoins;
}

void PopMp2BoardState(void) {
    s32 i;

    mp2_GwSystem = mp2_GwSystemCopy;
    for (i = 0; i < MP2_BOARD_DATA_SIZE; i++) {
        mp2_OtherBoardState[i] = mp2_OtherBoardStateCopy[i];
    }
    mp2_BankCoins = mp2_BankCoinsCopy;
}

void mp2_StoreBattleMinigameCoins(void) {
    mp2_BattleMinigameCoins_Copy = mp2_BattleMinigameCoins;
}

void mp3_StoreBattleMinigameCoins(void) {
    mp3_BattleMinigameCoins_Copy = mp3_BattleMinigameCoins;
}

void PushMp2MinigamesPlayedList(void) {
    s32 i;

    for (i = 0; i < MP2_PREV_MINIGAMES_PLAYED_SIZE; i++) {
        mp2_prevMinigamesPlayedCopy[i] = mp2_prevMinigamesPlayed[i];
    }
}

void PushMp3MinigamesPlayedList(void) {
    s32 i;

    for (i = 0; i < PREV_MINIGAMES_PLAYED_SIZE; i++) {
        mp3_prevMinigamesPlayedCopy[i] = mp3_prevMinigamesPlayed[i];
    }
}