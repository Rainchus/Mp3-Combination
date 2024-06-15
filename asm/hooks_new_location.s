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
    ADDIU a1, a1, 0xB900 //revert minigame str index back to minigame ID
    SLL a1, a1, 2 //multiply by sizeof(char*)
    LI a3, MinigameList
    ADDU a1, a1, a3
    LW a1, 0x0000 (a1)
    ADDIU a2, r0, 0xFFFE
    JAL 0x8005B43C
    ADDIU a3, r0, 0x0004
    J 0x800DFFE0
    NOP
    


getNewMinigameString2:
    ADDIU a1, a1, 0xB900 //revert minigame str index back to minigame ID
    SLL a1, a1, 2 //multiply by sizeof(char*)
    LI a3, MinigameList
    ADDU a1, a1, a3
    LW a1, 0x0000 (a1)
    ADDIU a2, r0, 0xFFFE
    JAL 0x8005B43C
    ADDIU a3, r0, 0x0004
    J 0x800DF488
    NOP
    