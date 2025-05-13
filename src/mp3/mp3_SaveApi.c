//contains functions for pushing/popping data needed for the board to function

#include "mp3.h"
#define COLD_BOOT 0
#define WARM_BOOT 1
#define osAppNmiBufferSize 64

extern u8 mp3_osAppNmiBuffer[osAppNmiBufferSize];

void checkosAppNmiBufferReset(s32 resetType) {
    s32 i;

    if (resetType == COLD_BOOT) {
        for (i = 0; i < osAppNmiBufferSize; i++) {
            mp3_osAppNmiBuffer[i] = 0;
        }        
    }
}

void PushMp3OvlHis(void) {
    s32 i;

    for (i = 0; i < 12; i++) {
        mp3_omovlhis_copy[i] = mp3_omovlhis[i];
    }
    mp3_omovlhisidx_copy = mp3_omovlhisidx;
}