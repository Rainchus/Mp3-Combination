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
//JAL ComboSwitchGameToMp2
//NOP
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



//mp3 notes
//800DFE84 reads 4p minigame indexes

getNewMinigameString1:
ADDIU sp, sp, -0x30
SW a0, 0x0010 (sp)
SW a1, 0x0014 (sp)
SW a2, 0x0018 (sp)
SW a3, 0x001C (sp)
SW ra, 0x0020 (sp)

JAL GetNewMinigameString
NOP

LW a0, 0x0010 (sp)
ADDU a1, v0, r0 //new str pointer to use for minigame name
LW a2, 0x0018 (sp)
LW a3, 0x001C (sp)
LW ra, 0x0020 (sp)
JR RA
ADDIU sp, sp, 0x30