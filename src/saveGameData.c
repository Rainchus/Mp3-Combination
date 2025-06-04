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

// void SaveMp3PlayerStructs(void) {
//     for (int i = 0; i < 4; i++) {
//         mp3_GwPlayerCopy[i].group = mp2_GwPlayer[i].group;
//         mp3_GwPlayerCopy[i].cpu_difficulty = mp2_GwPlayer[i].cpu_difficulty;
//         mp3_GwPlayerCopy[i].cpu_difficulty = mp2_GwPlayer[i].cpu_difficulty2;
//         mp3_GwPlayerCopy[i].controller_port = mp2_GwPlayer[i].port;
//         mp3_GwPlayerCopy[i].characterID = mp2_GwPlayer[i].character;
//         mp3_GwPlayerCopy[i].flags1 = mp2_GwPlayer[i].flags;

//         mp3_GwPlayerCopy[i].coins_mg_bonus = mp2_GwPlayer[i].coins_mg_bonus;
//         mp3_GwPlayerCopy[i].minigameCoins = mp2_GwPlayer[i].minigameCoins;
//         mp3_GwPlayerCopy[i].coins = mp2_GwPlayer[i].coins;
//         mp3_GwPlayerCopy[i].stars = mp2_GwPlayer[i].stars;


//         mp3_GwPlayerCopy[i].mg_star_coins = mp2_GwPlayer[i].mg_star_coins; //mg star
//         mp3_GwPlayerCopy[i].coins_total = mp2_GwPlayer[i].coins_total; //coin star
//         mp3_GwPlayerCopy[i].blueSpacesLandedOn = mp2_GwPlayer[i].blue_spaces_landed_on; //happening star
//         mp3_GwPlayerCopy[i].redSpacesLandedOn = mp2_GwPlayer[i].red_spaces_landed_on;
//         mp3_GwPlayerCopy[i].happeningSpacesLandedOn = mp2_GwPlayer[i].red_spaces_landed_on;

//         //mp3_GwPlayerCopy[i] = mp3_GwPlayer[i];
//     }

//     mp3_hidden_block_item_space_copy = mp3_hidden_block_item_space_index;
//     mp3_hidden_block_coins_space_copy = mp3_hidden_block_coins_space_index;
//     mp3_hidden_block_star_space_copy = mp3_hidden_block_star_space_index;
// }

// void LoadMp3PlayerStructs(void) {
//     for (int i = 0; i < 4; i++) {
//         mp2_GwPlayer[i].group = mp3_GwPlayerCopy[i].group;
//         mp2_GwPlayer[i].cpu_difficulty = mp3_GwPlayerCopy[i].cpu_difficulty;
//         mp2_GwPlayer[i].cpu_difficulty2 = mp3_GwPlayerCopy[i].cpu_difficulty;
//         mp2_GwPlayer[i].port = mp3_GwPlayerCopy[i].controller_port;
//         mp2_GwPlayer[i].character = mp3_GwPlayerCopy[i].characterID;
//         mp2_GwPlayer[i].flags = mp3_GwPlayerCopy[i].flags1;

//         mp3_GwPlayerCopy[i].coins_mg_bonus = mp2_GwPlayer[i].coins_mg_bonus;
//         mp3_GwPlayerCopy[i].minigameCoins = mp2_GwPlayer[i].minigameCoins;
//         mp3_GwPlayerCopy[i].coins = mp2_GwPlayer[i].coins;
//         mp3_GwPlayerCopy[i].stars = mp2_GwPlayer[i].stars;


//         mp3_GwPlayerCopy[i].mg_star_coins = mp2_GwPlayer[i].mg_star_coins; //mg star
//         mp3_GwPlayerCopy[i].coins_total = mp2_GwPlayer[i].coins_total; //coin star
//         mp3_GwPlayerCopy[i].blueSpacesLandedOn = mp2_GwPlayer[i].blue_spaces_landed_on; //happening star
//         mp3_GwPlayerCopy[i].redSpacesLandedOn = mp2_GwPlayer[i].red_spaces_landed_on;
//         mp3_GwPlayerCopy[i].happeningSpacesLandedOn = mp2_GwPlayer[i].red_spaces_landed_on;
//     }

//     mp3_hidden_block_item_space_index = mp3_hidden_block_item_space_copy;
//     mp3_hidden_block_coins_space_index = mp3_hidden_block_coins_space_copy;
//     mp3_hidden_block_star_space_index = mp3_hidden_block_star_space_copy;
// }

// void SaveMp2PlayerStructs(void) {
//     for (int i = 0; i < 4; i++) {
//         mp2_GwPlayerCopy[i] = mp2_GwPlayer[i];
//     }

//     mp2_hidden_block_coins_space_index_copy = mp2_hidden_block_coins_space_index;
//     mp2_hidden_block_star_space_index_copy = mp2_hidden_block_star_space_index;
// }

// void SaveMp1PlayerStructs(void) {
//     for (int i = 0; i < 4; i++) {
//         mp1_GwPlayerCopy[i] = mp1_GwPlayer[i];
//     }
//     //TODO: doesn't this game also have "hidden blocks?"
// }

// // void LoadMp3PlayerStructs(void) {
// //     for (int i = 0; i < 4; i++) {
// //         mp3_GwPlayer[i] = mp3_GwPlayerCopy[i];
// //     }

// //     mp3_hidden_block_item_space_index = mp3_hidden_block_item_space_copy;
// //     mp3_hidden_block_coins_space_index = mp3_hidden_block_coins_space_copy;
// //     mp3_hidden_block_star_space_index = mp3_hidden_block_star_space_copy;
// // }

// // void LoadMp2PlayerStructs(void) {
// //     for (int i = 0; i < 4; i++) {
// //         mp2_GwPlayer[i] = mp2_GwPlayerCopy[i];
// //     }

// //     mp2_hidden_block_coins_space_index = mp2_hidden_block_coins_space_index_copy;
// //     mp2_hidden_block_star_space_index = mp2_hidden_block_star_space_index_copy;
// // }

// // void LoadMp1PlayerStructs(void) {
// //     for (int i = 0; i < 4; i++) {
// //         mp1_GwPlayer[i] = mp1_GwPlayerCopy[i];
// //     }
// //     //TODO: doesn't this game also have "hidden blocks?"
// // }

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

void LoadMp3PlayerCopyToMp2(void) {
    for (int i = 0; i < 4; i++) {
        mp2_GwPlayer[i].group = mp3_GwPlayerCopy[i].group;
        mp2_GwPlayer[i].cpu_difficulty = mp3_GwPlayerCopy[i].cpu_difficulty;
        mp2_GwPlayer[i].cpu_difficulty2 = mp3_GwPlayerCopy[i].cpu_difficulty;
        mp2_GwPlayer[i].port = mp3_GwPlayerCopy[i].controller_port;
        mp2_GwPlayer[i].flags = mp3_GwPlayerCopy[i].flags1;
        mp2_GwPlayer[i].character = mp3_GwPlayerCopy[i].characterID;

        mp2_GwPlayer[i].coins = mp3_GwPlayerCopy[i].coins;
        mp2_GwPlayer[i].stars = mp3_GwPlayerCopy[i].stars;
    }

    mp3_hidden_block_item_space_copy = mp3_hidden_block_item_space_index;
    mp3_hidden_block_coins_space_copy = mp3_hidden_block_coins_space_index;
    mp3_hidden_block_star_space_copy = mp3_hidden_block_star_space_index;
}

void SaveMp2PlayerToMp3PlayerCopy(void) {
    for (int i = 0; i < 4; i++) {
        mp3_GwPlayerCopy[i].group = mp2_GwPlayer[i].group;
        mp3_GwPlayerCopy[i].cpu_difficulty = mp2_GwPlayer[i].cpu_difficulty;
        mp3_GwPlayerCopy[i].cpu_difficulty = mp2_GwPlayer[i].cpu_difficulty2;
        mp3_GwPlayerCopy[i].controller_port = mp2_GwPlayer[i].port;
        mp3_GwPlayerCopy[i].flags1 = mp2_GwPlayer[i].flags;
        mp3_GwPlayerCopy[i].characterID = mp2_GwPlayer[i].character;

        mp3_GwPlayerCopy[i].coins_mg_bonus = mp2_GwPlayer[i].coins_mg_bonus;
        mp3_GwPlayerCopy[i].minigameCoins = mp2_GwPlayer[i].minigameCoins;

        mp3_GwPlayerCopy[i].coins = mp2_GwPlayer[i].coins;
        mp3_GwPlayerCopy[i].stars = mp2_GwPlayer[i].stars;
    }

    mp3_hidden_block_item_space_index = mp3_hidden_block_item_space_copy;
    mp3_hidden_block_coins_space_index = mp3_hidden_block_coins_space_copy;
    mp3_hidden_block_star_space_index = mp3_hidden_block_star_space_copy;    
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

void CopyMp2PlayersToMp3Copy(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        mp3_GwPlayerCopy[i].group = mp2_GwPlayer[i].group;
        mp3_GwPlayerCopy[i].cpu_difficulty = mp2_GwPlayer[i].cpu_difficulty;
        mp3_GwPlayerCopy[i].cpu_difficulty = mp2_GwPlayer[i].cpu_difficulty2;
        mp3_GwPlayerCopy[i].controller_port = mp2_GwPlayer[i].port;
        mp3_GwPlayerCopy[i].characterID = mp2_GwPlayer[i].character;
        mp3_GwPlayerCopy[i].flags1 = mp2_GwPlayer[i].flags;
        mp3_GwPlayerCopy[i].stars = mp2_GwPlayer[i].stars;
        mp3_GwPlayerCopy[i].coins_mg_bonus = mp2_GwPlayer[i].coins_mg_bonus;
        mp3_GwPlayerCopy[i].minigameCoins = mp2_GwPlayer[i].minigameCoins;
        mp3_GwPlayerCopy[i].coins = mp2_GwPlayer[i].coins;
    }
}

void CopyMp3PlayersCopyToMp3(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        mp3_GwPlayer[i] = mp3_GwPlayerCopy[i];
    }
}

//we only want to copy the necessary data so that the mp2 results screen is correct,
//and the human/cpu flags and characters are copied over
// void CopyMp3_gPlayerCopy_To_Mp2(void) {
//     s32 i;

//     for (i = 0; i < 4; i++) {
//         mp2_GwPlayer[i].group = mp3_GwPlayerCopy[i].group;
//         mp2_GwPlayer[i].cpu_difficulty = mp3_GwPlayerCopy[i].cpu_difficulty;
//         mp2_GwPlayer[i].cpu_difficulty2 = mp3_GwPlayerCopy[i].cpu_difficulty;
//         mp2_GwPlayer[i].port = mp3_GwPlayerCopy[i].controller_port;
//         mp2_GwPlayer[i].character = mp3_GwPlayerCopy[i].characterID;
//         mp2_GwPlayer[i].flags = mp3_GwPlayerCopy[i].flags1;
//         mp2_GwPlayer[i].stars = mp3_GwPlayerCopy[i].stars;
//         mp2_GwPlayer[i].coins_mg_bonus = mp3_GwPlayerCopy[i].coins_mg_bonus;
//         mp2_GwPlayer[i].minigameCoins = mp3_GwPlayerCopy[i].minigameCoins;
//         mp2_GwPlayer[i].coins = mp3_GwPlayerCopy[i].coins;
//     }
// }

// void CopyMp1_gPlayerCopy_To_Mp2(void) {
//     s32 i;

//     for (i = 0; i < 4; i++) {
//         mp2_GwPlayer[i].group = mp1_GwPlayerCopy[i].group;
//         mp2_GwPlayer[i].cpu_difficulty = mp1_GwPlayerCopy[i].cpu_difficulty;
//         mp2_GwPlayer[i].cpu_difficulty = mp1_GwPlayerCopy[i].cpu_difficulty_copy;
//         mp2_GwPlayer[i].port = mp1_GwPlayerCopy[i].port;
//         mp2_GwPlayer[i].character = mp1_GwPlayerCopy[i].character;
//         mp2_GwPlayer[i].flags = mp1_GwPlayerCopy[i].flags;
//         mp2_GwPlayer[i].coins = mp1_GwPlayerCopy[i].coins;
//         mp2_GwPlayer[i].stars = mp1_GwPlayerCopy[i].stars;
//     }
// }

// extern mp2_GW_PLAYER mp2_GwPlayerCopy[4];

// void CopyMp2_gPlayerCopy_To_Mp1(void) {
//     s32 i;

//     for (i = 0; i < 4; i++) {
//         mp1_GwPlayer[i].group = mp2_GwPlayerCopy[i].group;
//         mp1_GwPlayer[i].cpu_difficulty = mp2_GwPlayerCopy[i].cpu_difficulty;
//         mp1_GwPlayer[i].cpu_difficulty_copy = mp2_GwPlayerCopy[i].cpu_difficulty;
//         mp1_GwPlayer[i].port = mp2_GwPlayerCopy[i].port;
//         mp1_GwPlayer[i].character = mp2_GwPlayerCopy[i].character;
//         mp1_GwPlayer[i].flags = mp2_GwPlayerCopy[i].flags;
//         mp1_GwPlayer[i].coins = mp2_GwPlayerCopy[i].coins;
//         mp1_GwPlayer[i].stars = mp2_GwPlayerCopy[i].stars;
//     }
// }

// void CopyMp3_gPlayerCopy_To_Mp1(void) {
//     s32 i;

//     for (i = 0; i < 4; i++) {
//         mp1_GwPlayer[i].group = mp3_GwPlayerCopy[i].group;
//         mp1_GwPlayer[i].cpu_difficulty = mp3_GwPlayerCopy[i].cpu_difficulty;
//         mp1_GwPlayer[i].cpu_difficulty_copy = mp3_GwPlayerCopy[i].cpu_difficulty;
//         mp1_GwPlayer[i].port = mp3_GwPlayerCopy[i].controller_port;
//         mp1_GwPlayer[i].character = mp3_GwPlayerCopy[i].characterID;
//         mp1_GwPlayer[i].flags = mp3_GwPlayerCopy[i].flags1;
//         mp1_GwPlayer[i].coins = mp3_GwPlayerCopy[i].coins;
//         mp1_GwPlayer[i].stars = mp3_GwPlayerCopy[i].stars;
//     }
// }

// void CopyMp1_gPlayerCopy_To_Mp3(void) {
//     s32 i;

//     for (i = 0; i < 4; i++) {
//         mp3_GwPlayer[i].group = mp1_GwPlayerCopy[i].group;
//         mp3_GwPlayer[i].cpu_difficulty = mp1_GwPlayerCopy[i].cpu_difficulty;
//         mp3_GwPlayer[i].controller_port = mp1_GwPlayerCopy[i].port;
//         mp3_GwPlayer[i].characterID = mp1_GwPlayerCopy[i].character;
//         mp3_GwPlayer[i].flags1 = mp1_GwPlayerCopy[i].flags;
//         mp3_GwPlayer[i].coins = mp1_GwPlayerCopy[i].coins;
//         mp3_GwPlayer[i].stars = mp1_GwPlayerCopy[i].stars;
//         // mp3_GwPlayer[i].turn_status = mp1_GwPlayerCopy[i].turn_status;
//     }
// }

// void CopyMp2_gPlayerCopy_To_Mp3(void) {
//     s32 i;

//     for (i = 0; i < 4; i++) {
//         mp3_GwPlayer[i].group = mp2_GwPlayerCopy[i].group;
//         mp3_GwPlayer[i].cpu_difficulty = mp2_GwPlayerCopy[i].cpu_difficulty;
//         mp3_GwPlayer[i].controller_port = mp2_GwPlayerCopy[i].port;
//         mp3_GwPlayer[i].characterID = mp2_GwPlayerCopy[i].character;
//         mp3_GwPlayer[i].flags1 = mp2_GwPlayerCopy[i].flags;
//         mp3_GwPlayer[i].coins = mp2_GwPlayerCopy[i].coins;
//         mp3_GwPlayer[i].stars = mp2_GwPlayerCopy[i].stars;
//         // mp3_GwPlayer[i].turn_status = mp2_GwPlayerCopy[i].turn_status;
//     }
// }