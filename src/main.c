#include "marioparty.h"

#define MAIN_DRAM 0x80000400
#define MAIN_OFF 0x400
#define MAIN_SIZE 0xBE940 //TODO: what should this actually be?
#define MAIN_CART 0x0001000

#define FOREIGN_DRAM 0x80000400 //mp1, mp2 and mp3 all share this addr
#define FOREIGN_OFF 0x400
#define FOREIGN_SIZE_MP2 0x0D57F0 //TODO: what should this actually be?
#define FOREIGN_CART_MP2 0x2001000 //ROM start addr + 0x1000
#define NORETURN    __attribute__((noreturn))

void System_DisableInterrupts(void);
NORETURN void ComboGameSwitch2ToMp2(void);
void System_InvalDCache(void* addr, u32 size);
void System_InvalICache(void* addr, u32 size);
void comboDma_NoCacheInval(void* dramAddr, u32 cartAddr, u32 size);
void ComboGameSwitch4(u32);


extern s32 mp2_OverlayToLoad;

s32 mp2_base = MP2_BASE;

// void ifComingFromMP3(void) {
//     if (func_8000E9E8((void*)0x80101100) == 0) {
//         if (mp2_OverlayToLoad != -1) {
//             func_800770EC(0x3D, 0x00, 0x84); //load minigame boot up sequence
//         } else {
//             func_800770EC(0x57, 0x00, 0x84); //save data corrupted
//         }
    
//     } else {
//         func_800770EC(0x5A, 0x00, 0x81);
//     }
// }

void cBootFunction(void) {
    //crash_screen_init();
}

extern mp3_PlayerData mp3_PlayersCopy[4];
extern mp2_PlayerData mp2_PlayersCopy[4];

void CopyMp3_gPlayerCopy_To_Mp2(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        mp2_gPlayers[i].cpu_difficulty = mp3_PlayersCopy[i].cpu_difficulty;
        mp2_gPlayers[i].cpu_difficulty2 = mp3_PlayersCopy[i].cpu_difficulty;
        mp2_gPlayers[i].controller_port = mp3_PlayersCopy[i].controller_port;
        mp2_gPlayers[i].flags = mp3_PlayersCopy[i].flags1;
        mp2_gPlayers[i].group = mp3_PlayersCopy[i].group;
        mp2_gPlayers[i].characterID = mp3_PlayersCopy[i].characterID;
    }
}

//for use when loading back into mp3 after a minigame
// void RetrieveMp3PlayerData(void) {
//     s32 i;

//     for (i = 0; i < 4; i++) {
//         mp3_gPlayers[i] = mp3_PlayersCopy[i];
//     }

//     //get minigame coins won
//     for (i = 0; i < 4; i++) {
//         mp3_gPlayers[i].minigameCoins = mp2_PlayersCopy[i].minigame_coins_collected;
//         mp3_gPlayers[i].minigameCoinsWon = mp2_PlayersCopy[i].extra_coins_collected_during_minigame;
//     }
// }


void CopyMp2_gPlayerCopy_To_Mp3(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        mp3_gPlayers[i].cpu_difficulty = mp2_PlayersCopy[i].cpu_difficulty;
        mp3_gPlayers[i].controller_port = mp2_PlayersCopy[i].controller_port;
        mp3_gPlayers[i].flags1 = mp2_PlayersCopy[i].flags;
    }
}

void SaveMp2PlayerStructs(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        mp2_PlayersCopy[i] = mp2_gPlayers[i];
    }
}

void SaveMp3PlayerStructs(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        mp3_PlayersCopy[i] = mp3_gPlayers[i];
    }
}

//start loading into Mp3
NORETURN void ComboSwitchGameToMp3(void) {
    System_DisableInterrupts();
    WaitForSubSystems();
    ComboGameSwitch2ToMp3(); //doesn't return
}

NORETURN void ComboSwitchGame3ToMp3(void) {
    System_InvalDCache((void*)MAIN_DRAM, MAIN_SIZE);
    System_InvalICache((void*)MAIN_DRAM, MAIN_SIZE);
    comboDma_NoCacheInval((void*)MAIN_OFF, MAIN_CART, MAIN_SIZE);
    System_InvalDCache((void*)MAIN_DRAM, MAIN_SIZE);
    System_InvalICache((void*)MAIN_DRAM, MAIN_SIZE);
    ComboGameSwitch4(MAIN_DRAM);
}




//start loading into Mp2
NORETURN void ComboSwitchGameToMp2(void) {
    SaveMp3PlayerStructs();
    System_DisableInterrupts();
    WaitForSubSystems();
    ComboGameSwitch2ToMp2(); //doesn't return
}

NORETURN void ComboSwitchGame3ToMp2(void) {
    System_InvalDCache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    System_InvalICache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    comboDma_NoCacheInval((void*)FOREIGN_OFF, FOREIGN_CART_MP2, FOREIGN_SIZE_MP2);
    System_InvalDCache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    System_InvalICache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    ComboGameSwitch4(FOREIGN_DRAM);
}
