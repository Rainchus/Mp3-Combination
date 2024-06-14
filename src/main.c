#include "mp3.h"

#define MAIN_DRAM 0x80000400
#define MAIN_OFF 0x400
#define MAIN_SIZE 0xBE940 //TODO: what should this actually be?
#define MAIN_CART 0x0001000

#define FOREIGN_DRAM 0x80000400 //mp1, mp2 and mp3 all share this addr
#define FOREIGN_OFF 0x400
#define FOREIGN_SIZE_MP2 0x0D57F0 //TODO: what should this actually be?
#define FOREIGN_CART_MP2 0x2001000 //ROM start addr + 0x1000
#define NORETURN    __attribute__((noreturn))

void cBootFunction(void) {
    //crash_screen_init();
}

//start loading into Mp3
NORETURN ComboSwitchGameToMp3(void) {
    System_DisableInterrupts();
    WaitForSubSystems();
    ComboGameSwitch2ToMp2(); //doesn't return
}

NORETURN ComboSwitchGame3ToMp3(void) {
    System_InvalDCache((void*)MAIN_DRAM, MAIN_SIZE);
    System_InvalICache((void*)MAIN_DRAM, MAIN_SIZE);
    comboDma_NoCacheInval((void*)MAIN_OFF, MAIN_CART, MAIN_SIZE);
    System_InvalDCache((void*)MAIN_DRAM, MAIN_SIZE);
    System_InvalICache((void*)MAIN_DRAM, MAIN_SIZE);
    ComboGameSwitch4(MAIN_DRAM);
}




//start loading into Mp2
NORETURN ComboSwitchGameToMp2(void) {
    System_DisableInterrupts();
    WaitForSubSystems();
    ComboGameSwitch2ToMp2(); //doesn't return
}

NORETURN ComboSwitchGame3ToMp2(void) {
    System_InvalDCache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    System_InvalICache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    comboDma_NoCacheInval((void*)FOREIGN_OFF, FOREIGN_CART_MP2, FOREIGN_SIZE_MP2);
    System_InvalDCache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    System_InvalICache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    ComboGameSwitch4(FOREIGN_DRAM);
}