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
extern u32 rnd_seed_shared;

u8 rand8_Shared(void) {
    rnd_seed_shared = rnd_seed_shared * 0x41C64E6D + 0x3039;
    return ((rnd_seed_shared + 1) >> 16);
}

void SaveMp3PlayerStructs(void) {
    for (int i = 0; i < 4; i++) {
        mp3_GwPlayerCopy[i] = mp3_GwPlayer[i];
    }

    mp3_hidden_block_item_space_copy = mp3_hidden_block_item_space_index;
    mp3_hidden_block_coins_space_copy = mp3_hidden_block_coins_space_index;
    mp3_hidden_block_star_space_copy = mp3_hidden_block_star_space_index;
}

void SaveMp2PlayerStructs(void) {
    for (int i = 0; i < 4; i++) {
        mp2_GwPlayerCopy[i] = mp2_GwPlayer[i];
    }

    mp2_hidden_block_coins_space_index_copy = mp2_hidden_block_coins_space_index;
    mp2_hidden_block_star_space_index_copy = mp2_hidden_block_star_space_index;
}

void SaveMp1PlayerStructs(void) {
    for (int i = 0; i < 4; i++) {
        mp1_GwPlayerCopy[i] = mp1_GwPlayer[i];
    }
    //TODO: doesn't this game also have "hidden blocks?"
}

void LoadMp3PlayerStructs(void) {
    for (int i = 0; i < 4; i++) {
        mp3_GwPlayer[i] = mp3_GwPlayerCopy[i];
    }

    mp3_hidden_block_item_space_index = mp3_hidden_block_item_space_copy;
    mp3_hidden_block_coins_space_index = mp3_hidden_block_coins_space_copy;
    mp3_hidden_block_star_space_index = mp3_hidden_block_star_space_copy;
}

void LoadMp2PlayerStructs(void) {
    for (int i = 0; i < 4; i++) {
        mp2_GwPlayer[i] = mp2_GwPlayerCopy[i];
    }

    mp2_hidden_block_coins_space_index = mp2_hidden_block_coins_space_index_copy;
    mp2_hidden_block_star_space_index = mp2_hidden_block_star_space_index_copy;
}

void LoadMp1PlayerStructs(void) {
    for (int i = 0; i < 4; i++) {
        mp1_GwPlayer[i] = mp1_GwPlayerCopy[i];
    }
    //TODO: doesn't this game also have "hidden blocks?"
}


/* -- functions related to pushing/popping the game state -- */
extern u8 mp3_D_800B23B0;
extern u8 mp3_D_800B23B1;
extern u8 mp3_D_800D030A;
extern u8 mp3_D_800D0308; //mp3 story progress byte
extern u8 mp3_D_800D0309;

//mp3 board state and copy (BOARD_STATE_STRUCT_SIZE isn't known what exact size we need)
mp3_GW_SYSTEM mp3_GwSystemCopy = {0};
u8 mp3_ModeCopy = 0;
u8 mp3_ModeCopy2 = 0;
u8 mp3_StoryDifficultyCopy = 0;
u8 mp3_StoryProgressCopy = 0;
u8 mp3_StoryCharacterID = 0;
u8 mp3_prevMinigamesPlayedCopy[PREV_MINIGAMES_PLAYED_SIZE] = {0};
s16 mp3_BattleMinigameCoins_Copy = 0;

void PushMp3BoardState(void) {
    mp3_GwSystemCopy = mp3_GwSystem;
    mp3_ModeCopy = mp3_D_800B23B0;
    mp3_ModeCopy2 = mp3_D_800B23B1;
    mp3_StoryDifficultyCopy = mp3_D_800D030A;
    mp3_StoryProgressCopy = mp3_D_800D0308;
    mp3_StoryCharacterID = mp3_D_800D0309;
}

void PopMp3BoardState(void) {
    mp3_GwSystem = mp3_GwSystemCopy;
    mp3_D_800B23B0 = mp3_ModeCopy;
    mp3_D_800B23B1 = mp3_ModeCopy2;
    mp3_D_800D030A = mp3_StoryDifficultyCopy;
    mp3_D_800D0308 = mp3_StoryProgressCopy;
    mp3_D_800D0309 = mp3_StoryCharacterID;
}

void mp3_StoreBattleMinigameCoins(void) {
    mp3_BattleMinigameCoins_Copy = mp3_BattleMinigameCoins;
}

void PushMp3MinigamesPlayedList(void) {
    s32 i;

    for (i = 0; i < PREV_MINIGAMES_PLAYED_SIZE; i++) {
        mp3_prevMinigamesPlayedCopy[i] = mp3_prevMinigamesPlayed[i];
    }
}