#include "marioparty.h"

extern mp3MinigameIndexTable minigameLUT[];

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

//in mp2, the explanation screen is split into 2 overlays
//we check the range, and if it's in mp2, fix the index back to -
//the correct mp2 one. this is because the minigame index list was based -
//on mp3 as a basis
extern s16 D_800F93C8;
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
        ComboSwitchGameToMp3();
    } else { //mp3
        ComboSwitchGameToMp1();
    }
    if (D_800F93C8 >= 0x1E) {
        return 0x60;
    } else {
        return 0x5F;
    }
}