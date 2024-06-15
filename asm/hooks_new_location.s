LoadOverlayHook_Mp2:
ADDIU sp, sp, -0x20 //restore from hook
SW ra, 0x0018 (sp) //restore from hook
ORI t0, r0, 0x0062 //opening scene overlay ID
BNE t0, a0, normalExitMp2
NOP
//swap game
//JAL ComboSwitchGameToMp3
//NOP
normalExitMp2:
J 0x80018B38
NOP

LoadOverlayHook_Mp3:
ADDIU sp, sp, -0x20 //restore from hook
SW ra, 0x0018 (sp) //restore from hook
ORI t0, r0, 0x0077 //party mode select
BNE t0, a0, normalExitMp3
NOP
//swap game
JAL ComboSwitchGameToMp2
NOP
normalExitMp3:
J 0x80048130
NOP

mp2_osEPiRawStartDmaHook:
ADDIU sp, sp, -0x28
SW s0, 0x0010 (sp)

LI t0, 0x2000000
ADDU a2, a2, t0

J 0x8009D958
NOP
