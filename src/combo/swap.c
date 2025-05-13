#include "marioparty.h"

#define MAIN_DRAM 0x80000400
#define MAIN_OFF 0x400
#define MAIN_SIZE 0xBE940 //main segment size
#define MAIN_CART 0x0001000

#define FOREIGN_DRAM 0x80000400 //mp1, mp2 and mp3 all share this addr
#define FOREIGN_OFF 0x400
#define FOREIGN_SIZE_MP2 0xD57F0
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
NORETURN void ComboGameSwitch2ToMp1(void);

//start loading into Mp1
NORETURN void ComboSwitchGameToMp1(void) {
    System_DisableInterrupts();
    WaitForSubSystems();
    ComboGameSwitch2ToMp1(); //doesn't return
    __builtin_unreachable();
}

NORETURN void ComboClearCacheAndExecuteMp1(void) {
    System_InvalDCache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP1);
    System_InvalICache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP1);
    comboDma_NoCacheInval((void*)FOREIGN_OFF, FOREIGN_CART_MP1, FOREIGN_SIZE_MP1);
    System_InvalDCache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP1);
    System_InvalICache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP1);
    ComboGameSwitch4(FOREIGN_DRAM);
    __builtin_unreachable();
}

//start loading into Mp2
NORETURN void ComboSwitchGameToMp2(void) {
    System_DisableInterrupts();
    WaitForSubSystems();
    ComboGameSwitch2ToMp2(); //doesn't return
    __builtin_unreachable();
}

NORETURN void ComboClearCacheAndExecuteMp2(void) {
    System_InvalDCache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    System_InvalICache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    comboDma_NoCacheInval((void*)FOREIGN_OFF, FOREIGN_CART_MP2, FOREIGN_SIZE_MP2);
    System_InvalDCache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    System_InvalICache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    ComboGameSwitch4(FOREIGN_DRAM);
    __builtin_unreachable();
}

//start loading into Mp3
NORETURN void ComboSwitchGameToMp3(void) {
    System_DisableInterrupts();
    WaitForSubSystems();
    ComboGameSwitch2ToMp3(); //doesn't return
    __builtin_unreachable();
}

NORETURN void ComboClearCacheAndExecuteMp3(void) {
    System_InvalDCache((void*)MAIN_DRAM, MAIN_SIZE);
    System_InvalICache((void*)MAIN_DRAM, MAIN_SIZE);
    comboDma_NoCacheInval((void*)MAIN_OFF, MAIN_CART, MAIN_SIZE);
    System_InvalDCache((void*)MAIN_DRAM, MAIN_SIZE);
    System_InvalICache((void*)MAIN_DRAM, MAIN_SIZE);
    ComboGameSwitch4(MAIN_DRAM);
    __builtin_unreachable();
}
