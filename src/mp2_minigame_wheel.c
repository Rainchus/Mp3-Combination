#include "marioparty.h"
#include "mp2.h"

#define MP2_PREV_MINIGAMES_PLAYED_SIZE 0x1E

void mp2_func_800890CC(s16, char*, s32, s32); //RefreshMsg
extern mp3MinigameIndexTable minigameLUT[];
extern s32 ForeignMinigameIndexToLoad;
extern s16 D_800F93C8;
NORETURN void ComboSwitchGameToMp3(void);
u8 mp2_prevMinigamesPlayedCopy[MP2_PREV_MINIGAMES_PLAYED_SIZE] = {0};
extern u8 mp2_prevMinigamesPlayed[MP2_PREV_MINIGAMES_PLAYED_SIZE];
void PushMp2OvlHis(void);
void PushMp2BoardState(void);

u8 mp2_newCategoryAmounts[] = {
    0x15, //4p
    0x0B, //1v3
    0x0C, //?
    0x01, //?
    0x08, //
};

u8 mp2_itemMinigameList[] = {
    GIVE_ME_A_BRAKE, //mp2 5
    ROLL_OUT_THE_BARRELS, //mp2 2
    COFFIN_CONGESTION, //mp2 3
    HAMMER_SLAMMER, //mp2 4
    MALLET_GO_ROUND, //mp2 6
    BOWSER_SLOTS, //mp2 1
};

void mp2_GetNewMinigameString(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 minigameCombinedIndex = arg1 - 0x3D8;
    s32 i;

    for (i = 0; i < MINIGAME_END; i++) {
        if (minigameCombinedIndex == minigameLUT[i].minigameIndex) {
            mp2_func_800890CC(arg0, minigameLUT[i].minigameStr, arg2, arg3);
            return;
        }
    }
    mp2_func_800890CC(arg0, (char*)arg1, arg2, arg3);
}


s16 mp2_hidden_block_coins_space_index_copy = 0;
s16 mp2_hidden_block_star_space_index_copy = 0;

void SaveMp2PlayerStructs(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        mp2_PlayersCopy[i] = mp2_gPlayers[i];
    }

    mp2_hidden_block_coins_space_index_copy = mp2_hidden_block_coins_space_index;
    mp2_hidden_block_star_space_index_copy = mp2_hidden_block_star_space_index;
}

void PushMp2MinigamesPlayedList(void) {
    s32 i;

    for (i = 0; i < MP2_PREV_MINIGAMES_PLAYED_SIZE; i++) {
        mp2_prevMinigamesPlayedCopy[i] = mp2_prevMinigamesPlayed[i];
    }
}

void PopMp2MinigamesPlayedList(void) {
    s32 i;

    for (i = 0; i < MP2_PREV_MINIGAMES_PLAYED_SIZE; i++) {
        mp2_prevMinigamesPlayed[i] = mp2_prevMinigamesPlayedCopy[i];
    }
}

//in mp2, the explanation screen is split into 2 overlays
//we check the range, and if it's in mp2, fix the index back to -
//the correct mp2 one. this is because the minigame index list was based -
//on mp3 as a basis

s16 GetMp2ExplanationScreenIndex(s16 arg0) {
    s32 i;
    if (D_800F93C8 >= BOWSER_SLOTS && D_800F93C8 <= DEEP_SEA_SALVAGE) { //mp2
        mp3MinigameIndexTable* curMinigameData = NULL;
        for (i = 0; i < MINIGAME_END; i++) {
            if (D_800F93C8 == minigameLUT[i].minigameIndex) {
                curMinigameData = &minigameLUT[i];
                break;
            }
        }
        D_800F93C8 = curMinigameData->gameOverlayID;
    } else if (D_800F93C8 >= HAND_LINE_AND_SINKER && D_800F93C8 <= MARIO_PUZZLE_PARTY_PRO) { //mp3
        SaveMp2PlayerStructs();
        PushMp2BoardState();
        PushMp2MinigamesPlayedList();
        ForeignMinigameIndexToLoad = D_800F93C8;
        ForeignMinigameAlreadyLoaded = FALSE;
        PushMp2OvlHis();
        ComboSwitchGameToMp3();
    } else { //mp1
        SaveMp2PlayerStructs();
        PushMp2BoardState();
        PushMp2MinigamesPlayedList();
        ForeignMinigameIndexToLoad = D_800F93C8;
        ForeignMinigameAlreadyLoaded = FALSE;
        PushMp2OvlHis();
        ComboSwitchGameToMp1();
    }
    if (D_800F93C8 >= 0x1E) {
        return 0x60;
    } else {
        return 0x5F;
    }
}