LoadOverlayHook_Mp2:
    ADDIU sp, sp, -0x20 //restore from hook
    SW ra, 0x0018 (sp) //restore from hook
    LI t0, mp2_OverlayToLoad
    LW t0, 0x0000 (t0) //load overlay ID
    BEQZ t0, normalMp2Boot
    NOP
    //otherwise, set overlay id to chosen index
    ADDU a0, t0, r0 //new overlay to load on boot
    normalMp2Boot:
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

ConvertMinigameIndexFromMp3ToMp2OverlayID:
ORI t0, r0, 0x0048 //hardcoded test
BEQL t0, a0, bowserSlots
ADDIU a0, r0, 1 //overlay ID of bowser slots in mp2
bowserSlots:
JR RA
ADDU v0, a0, r0

setCustomMinigameIndex:
    LUI v0, 0x800D
    LBU v0, 0xD068 (v0) //get minigame chosen
    SLTI at, v0, 0x49 //minigame index of first mp2 minigame
    BNEZ at, isMp3Minigame
    NOP
    //otherwise, is mp2 minigame. swap to mp2
    JAL ConvertMinigameIndexFromMp3ToMp2OverlayID
    ADDU a0, v0, r0

    LI a0, mp2_OverlayToLoad
    SW v0, 0x0000 (a0) //store overlay mp2 should load on boot
    
    JAL ComboSwitchGameToMp2
    NOP
    isMp3Minigame:
        ADDIU v0, v0, 0xFFFF //convert to index
    J 0x80105A6C
    NOP