#include "marioparty.h"

#define MAIN_DRAM 0x80000400
#define MAIN_OFF 0x400
#define MAIN_SIZE 0xBE940 //main segment size
#define MAIN_CART 0x0001000

#define FOREIGN_DRAM 0x80000400 //mp1, mp2 and mp3 all share this addr
#define FOREIGN_OFF 0x400
#define FOREIGN_SIZE_MP2 0x0D57F0
#define FOREIGN_CART_MP2 0x2001000 //ROM start addr + 0x1000

// #define FOREIGN_DRAM 0x80000400 //mp1, mp2 and mp3 all share this addr
#define FOREIGN_OFF 0x400
#define FOREIGN_SIZE_MP1 0xCDA50
#define FOREIGN_CART_MP1 0x4001000 //ROM start addr + 0x1000

void System_DisableInterrupts(void);
NORETURN void ComboGameSwitch2ToMp2(void);
void System_InvalDCache(void* addr, u32 size);
void System_InvalICache(void* addr, u32 size);
void comboDma_NoCacheInval(void* dramAddr, u32 cartAddr, u32 size);
void ComboGameSwitch4(u32);
void ComboGameSwitch2ToMp3(void);

extern s32 mp2_MinigameIndexToLoad;

s32 mp2_base = MP2_BASE;


void cBootFunction(void) {
    //crash_screen_init();
}

extern mp3_PlayerData mp3_PlayersCopy[4];
extern mp2_PlayerData mp2_PlayersCopy[4];

mp2_PlayerData mp2_gPlayerBlank = {0};

void CopyMp3_gPlayerCopy_To_Mp2(void) {
    s32 i;
    for (i = 0; i < 4; i++) {
        mp2_gPlayers[i] = mp2_gPlayerBlank;
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
    __builtin_unreachable();
}

NORETURN void ComboSwitchGame3ToMp3(void) {
    System_InvalDCache((void*)MAIN_DRAM, MAIN_SIZE);
    System_InvalICache((void*)MAIN_DRAM, MAIN_SIZE);
    comboDma_NoCacheInval((void*)MAIN_OFF, MAIN_CART, MAIN_SIZE);
    System_InvalDCache((void*)MAIN_DRAM, MAIN_SIZE);
    System_InvalICache((void*)MAIN_DRAM, MAIN_SIZE);
    ComboGameSwitch4(MAIN_DRAM);
    __builtin_unreachable();
}




//start loading into Mp2
NORETURN void ComboSwitchGameToMp2(void) {
    SaveMp3PlayerStructs();
    System_DisableInterrupts();
    WaitForSubSystems();
    ComboGameSwitch2ToMp2(); //doesn't return
    __builtin_unreachable();
}

NORETURN void ComboSwitchGame3ToMp2(void) {
    System_InvalDCache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    System_InvalICache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    comboDma_NoCacheInval((void*)FOREIGN_OFF, FOREIGN_CART_MP2, FOREIGN_SIZE_MP2);
    System_InvalDCache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    System_InvalICache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    ComboGameSwitch4(FOREIGN_DRAM);
    __builtin_unreachable();
}



NORETURN void ComboSwitchGameToMp1(void) {
    //SaveMp3PlayerStructs();
    System_DisableInterrupts();
    WaitForSubSystems();
    ComboGameSwitch2ToMp1(); //doesn't return
    __builtin_unreachable();
}

NORETURN void ComboSwitchGame3ToMp1(void) {
    System_InvalDCache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    System_InvalICache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    comboDma_NoCacheInval((void*)FOREIGN_OFF, FOREIGN_CART_MP1, FOREIGN_SIZE_MP1);
    System_InvalDCache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    System_InvalICache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    ComboGameSwitch4(FOREIGN_DRAM);
    __builtin_unreachable();
}