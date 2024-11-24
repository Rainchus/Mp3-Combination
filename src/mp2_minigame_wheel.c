#include "marioparty.h"

extern mp3MinigameIndexTable minigameLUT[];

u8 mp2_newCategoryAmounts[] = {
    0x15, //4p
    0x0B, //1v3
    0x0C, //?
    0x01, //?
    0x08, //
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