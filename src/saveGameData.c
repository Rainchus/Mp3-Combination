//functions for saving/restoring game data between games
#include "marioparty.h"
#include "mp1.h"
#include "mp2.h"
#include "mp3.h"


void SaveMp3PlayerToMp3PlayerCopy(void) {
    //this is a bit odd, but im unsure how else to handle it;
    //the bonus coins in the player struct linger until you start the next minigame, in which case it's cleared
    //however if you play a mp3 battle minigame, get bonus coins, then play a mp2 minigame, it will reaward you the bonus coins
    //so when we swap games (basically when "loading the minigame"), we clear the bonus coins
    for (int i = 0; i < 4; i++) {
        mp3_GwPlayer[i].gameCoin = 0;
        mp3_GwPlayer[i].bonusCoin = 0;
    }

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
        mp2_GwPlayer[i].bonusCoin = 0;
    }

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
        mp1_GwPlayer[i].bonusCoin = 0;
    }
    
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
        mp3_GwPlayer[i].pad = mp1_GwPlayerCopy[i].pad;
        mp3_GwPlayer[i].stat = mp1_GwPlayerCopy[i].stat;
        mp3_GwPlayer[i].chr = mp1_GwPlayerCopy[i].chr;
        mp3_GwPlayer[i].coin = mp1_GwPlayerCopy[i].coin;
        mp3_GwPlayer[i].star = mp1_GwPlayerCopy[i].star;
    }
}

//loading in from mp3 minigame back to mp2 board
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
        mp2_GwPlayerCopy[i].bonusCoin = mp3_GwPlayer[i].checkCoin; //TODO: are we sure about these 2 lines
        mp2_GwPlayerCopy[i].bonusCoin += mp3_GwPlayer[i].bonusCoin;
    }
}

//save mp2 to mp1PlayerCopy before swapping to mp1
void SaveMp2PlayerToMp1PlayerCopy(void) {
    for (int i = 0; i < 4; i++) {
        mp1_GwPlayerCopy[i].group = mp2_GwPlayerCopy[i].group;
        mp1_GwPlayerCopy[i].cpu_difficulty = mp2_GwPlayerCopy[i].cpu_difficulty;
        mp1_GwPlayerCopy[i].pad = mp2_GwPlayerCopy[i].pad;
        mp1_GwPlayerCopy[i].stat = mp2_GwPlayerCopy[i].stat;
        mp1_GwPlayerCopy[i].chr = mp2_GwPlayerCopy[i].chr;
        mp1_GwPlayerCopy[i].coin = mp2_GwPlayerCopy[i].coin;
        mp1_GwPlayerCopy[i].bonusCoin = mp2_GwPlayerCopy[i].bonusCoin;
        mp1_GwPlayerCopy[i].star = mp2_GwPlayerCopy[i].star;
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
        mp3_GwPlayerCopy[i].bonusCoin = mp2_GwPlayer[i].checkCoin; //checkCoin isn't read by mp3? bonusCoin is, throw the extra coins into it
        mp3_GwPlayerCopy[i].bonusCoin += mp2_GwPlayer[i].bonusCoin;
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
        mp2_GwPlayerCopy[i].coin = mp1_GwPlayer[i].coin;
        mp2_GwPlayerCopy[i].bonusCoin = mp1_GwPlayer[i].bonusCoin;
        mp2_GwPlayerCopy[i].star = mp1_GwPlayer[i].star;
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
        mp3_GwPlayerCopy[i].coin = mp1_GwPlayer[i].coin;
        mp3_GwPlayerCopy[i].bonusCoin = mp1_GwPlayer[i].bonusCoin;
        mp3_GwPlayerCopy[i].star = mp1_GwPlayer[i].star;
    }
}

extern u8 mp3_D_800B23B0;
extern u8 mp3_D_800B23B1;
extern u8 mp3_D_800D030A;
extern u8 mp3_D_800D0308; //mp3 story progress byte
extern u8 mp3_D_800D0309;

s16 mp3_hidden_block_item_space_copy = 0;
s16 mp3_hidden_block_coins_space_copy = 0;
s16 mp3_hidden_block_star_space_copy = 0;

s16 mp2_hidden_block_coins_space_index_copy = 0;
s16 mp2_hidden_block_star_space_index_copy = 0;

extern s16 mp3_hidden_block_item_space_index; //hidden_block_item_space
extern s16 mp3_hidden_block_coins_space_index; //hidden_block_coins_space
extern s16 mp3_hidden_block_star_space_index; //hidden_block_star_space

extern s16 mp3_hidden_block_item_space_index_old[10];
extern s16 mp3_hidden_block_coin_space_index_old[10];
extern s16 mp3_hidden_block_star_space_index_old[10];

#define PREV_SPACE_INDEXES_COUNT 10

typedef struct MP2_HiddenBlocks {
    s16 hidden_item_block_copy;
    s16 hidden_coin_block_copy;
    s16 hidden_star_block_copy;
} MP2_HiddenBlocks;

typedef struct MP3_HiddenBlocks {
    s16 hidden_item_block_copy;
    s16 hidden_coin_block_copy;
    s16 hidden_star_block_copy;
} MP3_HiddenBlocks;

typedef struct MP1_BoardBackupData {
    MP1_GW_SYSTEM mp1_GwSystemCopy;
} MP1_BoardBackupData;

typedef struct MP2_BoardBackupData {
    UnkData_E0290 D_800DF690_E0290_Backup;
    mp2_GW_SYSTEM mp2_GwSystemCopy;
    Unk800DF6B6 D_800DF6B6_E02B6_backup;
    s16 mp2_battleMinigameCoinsCopy;
    u16 mp2_BankCoinsCopy;
    MP2_HiddenBlocks mp2_HiddenBlocks;
} MP2_BoardBackupData;

typedef struct MP3_BoardBackupData {
    UnkData_CD0A0 D_800CC4A0_CD0A0_backup;
    mp3_GW_SYSTEM mp3_GwSystemCopy;
    Unk800CC3DC D_800CC3DC_CCFDC_backup;
    u8 mp3_ModeCopy;
    u8 mp3_ModeCopy2;
    u8 mp3_StoryDifficultyCopy;
    u8 mp3_StoryProgressCopy;
    u8 mp3_StorychrIDCopy;
    s16 mp3_battleMinigameCoinsCopy;
    MP3_HiddenBlocks mp3_HiddenBlocks;
    s16 mp3_hidden_block_item_space_index_old_copy[PREV_SPACE_INDEXES_COUNT];
    s16 mp3_hidden_block_coin_space_index_old_copy[PREV_SPACE_INDEXES_COUNT];
    s16 mp3_hidden_block_star_space_index_old_copy[PREV_SPACE_INDEXES_COUNT];
} MP3_BoardBackupData;

MP1_BoardBackupData mp1_storedData = {0};
MP2_BoardBackupData mp2_storedData = {0};
MP3_BoardBackupData mp3_storedData = {0};

u8 GetMp1ExplanationSetting(void) {
    return mp1_storedData.mp1_GwSystemCopy.minigameExplanation;
}

u8 GetMp2ExplanationSetting(void) {
    return mp2_storedData.mp2_GwSystemCopy.minigameExplanations;
}

u8 GetMp3StoredMessageSpeed(void) {
    return mp3_storedData.mp3_GwSystemCopy.message_speed;
}

u8 GetMp3ExplanationSetting(void) {
    return mp3_storedData.mp3_GwSystemCopy.show_minigame_explanations;
}

s16 GetMp2BattleMinigameCoins(void) {
    return mp2_storedData.mp2_battleMinigameCoinsCopy;
}

s16 GetMp3BattleMinigameCoins(void) {
    return mp3_storedData.mp3_battleMinigameCoinsCopy;
}

void SetMp3BattleMinigameCoins(s32 newAmount) {
    mp3_storedData.mp3_battleMinigameCoinsCopy = newAmount;
}

void PushMp3BoardState(void) {
    mp3_storedData.D_800CC4A0_CD0A0_backup = D_800CC4A0_CD0A0;
    mp3_storedData.mp3_GwSystemCopy = mp3_GwSystem;
    mp3_storedData.D_800CC3DC_CCFDC_backup = mp3_D_800CC3DC_CCFDC;
    mp3_storedData.mp3_ModeCopy = mp3_D_800B23B0;
    mp3_storedData.mp3_ModeCopy2 = mp3_D_800B23B1;
    mp3_storedData.mp3_StoryDifficultyCopy = mp3_D_800D030A;
    mp3_storedData.mp3_StoryProgressCopy = mp3_D_800D0308;
    mp3_storedData.mp3_StorychrIDCopy = mp3_D_800D0309;
    mp3_storedData.mp3_battleMinigameCoinsCopy = mp3_BattleMinigameCoins;

    mp3_storedData.mp3_HiddenBlocks.hidden_item_block_copy = mp3_hidden_block_item_space_index;
    mp3_storedData.mp3_HiddenBlocks.hidden_coin_block_copy = mp3_hidden_block_coins_space_index;
    mp3_storedData.mp3_HiddenBlocks.hidden_star_block_copy = mp3_hidden_block_star_space_index;

    //store previous hidden block placements list
    for (int i = 0; i < PREV_SPACE_INDEXES_COUNT; i++) {
        mp3_storedData.mp3_hidden_block_item_space_index_old_copy[i] = mp3_hidden_block_item_space_index_old[i];
        mp3_storedData.mp3_hidden_block_star_space_index_old_copy[i] = mp3_hidden_block_star_space_index_old[i];
        mp3_storedData.mp3_hidden_block_coin_space_index_old_copy[i] = mp3_hidden_block_coin_space_index_old[i];
    }
    
}

void PopMp3BoardState(void) {
    D_800CC4A0_CD0A0 = mp3_storedData.D_800CC4A0_CD0A0_backup;
    mp3_GwSystem = mp3_storedData.mp3_GwSystemCopy;
    mp3_D_800CC3DC_CCFDC = mp3_storedData.D_800CC3DC_CCFDC_backup;
    mp3_D_800B23B0 = mp3_storedData.mp3_ModeCopy;
    mp3_D_800B23B1 = mp3_storedData.mp3_ModeCopy2;
    mp3_D_800D030A = mp3_storedData.mp3_StoryDifficultyCopy;
    mp3_D_800D0308 = mp3_storedData.mp3_StoryProgressCopy;
    mp3_D_800D0309 = mp3_storedData.mp3_StorychrIDCopy;
    mp3_BattleMinigameCoins = mp3_storedData.mp3_battleMinigameCoinsCopy;

    mp3_hidden_block_item_space_index = mp3_storedData.mp3_HiddenBlocks.hidden_item_block_copy;
    mp3_hidden_block_coins_space_index = mp3_storedData.mp3_HiddenBlocks.hidden_coin_block_copy;
    mp3_hidden_block_star_space_index = mp3_storedData.mp3_HiddenBlocks.hidden_star_block_copy;

    //restore previous hidden block placements list
    for (int i = 0; i < PREV_SPACE_INDEXES_COUNT; i++) {
        mp3_hidden_block_item_space_index_old[i] = mp3_storedData.mp3_hidden_block_item_space_index_old_copy[i];
        mp3_hidden_block_star_space_index_old[i] = mp3_storedData.mp3_hidden_block_star_space_index_old_copy[i];
        mp3_hidden_block_coin_space_index_old[i] = mp3_storedData.mp3_hidden_block_coin_space_index_old_copy[i];
    }
}

//TODO: make proper struct to store all of the mp2 needed data
extern u16 mp2_BankCoins;

//unsure how much of this is actually relevant
#define MP2_BOARD_DATA_SIZE 0x20
#define MP2_PREV_MINIGAMES_PLAYED_SIZE 0x1E //TODO:make sure this works

void PushMp2BoardState(void) {
    mp2_storedData.D_800DF690_E0290_Backup = D_800DF690_E0290;
    mp2_storedData.mp2_GwSystemCopy = mp2_GwSystem;
    mp2_storedData.D_800DF6B6_E02B6_backup = D_800DF6B6_E02B6;
    mp2_storedData.mp2_battleMinigameCoinsCopy = mp2_BattleMinigameCoins;
    mp2_storedData.mp2_BankCoinsCopy = mp2_BankCoins;
}

void PopMp2BoardState(void) {
    D_800DF690_E0290 = mp2_storedData.D_800DF690_E0290_Backup;
    mp2_GwSystem = mp2_storedData.mp2_GwSystemCopy;
    D_800DF6B6_E02B6 = mp2_storedData.D_800DF6B6_E02B6_backup;
    mp2_BattleMinigameCoins = mp2_storedData.mp2_battleMinigameCoinsCopy;
    mp2_BankCoins = mp2_storedData.mp2_BankCoinsCopy;
}