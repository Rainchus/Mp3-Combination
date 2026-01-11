.headersize 0x800F65E0 - 0x2DB2A0 - 0x04000000
.org 0x800F6610
    J func_800F6610_MinigameInstructions
    NOP

//second part of minigame instructions hook for setting up overlay history back to boot logos
.org 0x800F697C
    JAL func_800F6990_MinigameInstructions
    NOP