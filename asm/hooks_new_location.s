LoadOverlayHook:
ADDIU sp, sp, -0x20 //restore from hook
SW ra, 0x0018 (sp) //restore from hook
ORI t0, r0, 0x007A //title screen overlay ID
BNE t0, a0, normalExit
NOP
//not normal exit, swap game
JAL ComboSwitchGame
NOP
normalExit:
J 0x80048130
NOP

mp2_osEPiRawStartDmaHook:
ADDIU sp, sp, -0x28
SW s0, 0x0010 (sp)

LI t0, 0x2000000
ADDU a2, a2, t0

J 0x8009D958
NOP
