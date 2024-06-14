#include "mp3.h"

#define FOREIGN_DRAM 0x80000400 //mp1, mp2 and mp3 all share this addr
#define FOREIGN_OFF 0x400
#define FOREIGN_SIZE_MP2 0x0D57F0 //TODO: what should this actually be?
#define FOREIGN_CART_MP2 0x2001000 //ROM start addr + 0x1000
#define NORETURN    __attribute__((noreturn))

void cBootFunction(void) {
    //crash_screen_init();
}

//start loading into Mp2
NORETURN ComboSwitchGame(void) {
    System_DisableInterrupts();
    WaitForSubSystems();
    ComboGameSwitch2(); //doesn't return
}

NORETURN ComboSwitchGame3(void) {
    System_InvalDCache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    System_InvalICache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    comboDma_NoCacheInval((void*)FOREIGN_OFF, FOREIGN_CART_MP2, FOREIGN_SIZE_MP2);
    System_InvalDCache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    System_InvalICache((void*)FOREIGN_DRAM, FOREIGN_SIZE_MP2);
    ComboGameSwitch4(FOREIGN_DRAM);
}