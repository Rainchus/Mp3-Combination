loadingBackFromMinigame:
.word 0

LoadOverlayHook_Mp2:
    ADDIU sp, sp, -0x20 //restore from hook
    SW ra, 0x0018 (sp) //restore from hook

    ORI t1, r0, 0x0057
    BNE a0, t1, notBootSequence
    NOP
    //if it is boot sequence
    //ADDU a0, r0, r0 //set overlay to 0 (debug)

    LI t0, loadingBackFromMinigame
    LW t1, 0x0000 (t0)
    BEQZ t1, normalBootSequence
    NOP
    //swap to mp3
    JAL ComboSwitchGameToMp3
    NOP

    normalBootSequence:
    notBootSequence:
    //otherwise, set overlay id to chosen index
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
    LI v0, mp2_base
    LW v0, 0x0000 (v0)
    SUBU a0, a0, v0
    JR RA
    ADDU v0, a0, r0

setCustomMinigameIndex:
    LUI v0, 0x800D
    LBU v0, 0xD068 (v0) //get minigame chosen
    LI at, mp2_base
    LW at, 0x0000 (at)
    SLT at, v0, at //first mp2 minigame
    BNEZ at, isMp3Minigame
    NOP
    //otherwise, is mp2 minigame. swap to mp2
    JAL ConvertMinigameIndexFromMp3ToMp2OverlayID
    ADDU a0, v0, r0

    LI a0, mp2_MinigameIndexToLoad
    SW v0, 0x0000 (a0) //store overlay mp2 should load on boot
    
    JAL ComboSwitchGameToMp2
    NOP

    isMp3Minigame:
        ADDIU v0, v0, 0xFFFF //convert to index
    J 0x80105A6C
    NOP

//80016D0C

//hookOvlDebugStart:
    //JAL 0x8006836C
    //ADDIU a0, r0, 0x0019
    //JAL CopyMp3_gPlayerCopy_To_Mp2
    //NOP
    //JAL LoadMinigameFromBoot
    //NOP
    //J 0x80102834
    //NOP

//hookOvlDebugSetStats:
//ADDIU sp, sp, 0x20 //restore from hook
    //J 0x80077DE0
    //NOP

hookOvlDebugStart2:
    ADDIU sp, sp, -0x20
    SW ra, 0x0018 (sp)
    JAL CopyMp3_gPlayerCopy_To_Mp2
    NOP
    LW ra, 0x0018 (sp)
    JR RA
    ADDIU sp, sp, 0x20


ifSkipDebugTextDraw:
    LUI s2, 0x8010
    ADDIU s2, s2, 0x1081 //normally is ADDIU s2, s2, 0x1080 (makes first byte of all strings )
    J 0x80103884
    SB r0, 0xFFFF (s2) //set beginning of all debug drawing strings to '\0', and move printf buffer to not write first byte
