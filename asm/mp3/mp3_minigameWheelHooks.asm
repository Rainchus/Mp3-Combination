//hook shared board overlay (ovl 0x80)
.headersize 0x800DFFA4 - 0xF3BC4

//there is an LB here that needs to be patched, but patching it might cause issues -
//because there is a BLTZ check
//MBMain patch
.org 0x800FEF60
    JAL NegativeCheck
     NOP