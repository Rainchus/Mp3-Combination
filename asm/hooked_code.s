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
    //JAL ComboSwitchGameToMp1
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

//mp1
mp1_osEPiRawStartDmaHook:
    ADDIU sp, sp, -0x28
    SW s0, 0x0010 (sp)

    LI t0, 0x4000000
    ADDU a2, a2, t0

    J 0x80090308
    NOP


//unfortunately this needs to be asm due to how
setCustomMinigameIndex:
    LUI v0, 0x800D
    LBU v0, 0xD068 (v0) //get minigame chosen

    ORI at, r0, 72
    SLT at, v0, at //first mp2 minigame
    BNEZ at, isMp3Minigame
    NOP

    //is mp1 or mp2, backup needed data

    LI a0, ForeignMinigameIndexToLoad
    SW v0, 0x0000 (a0) //store overlay mp1/mp2 should load on boot

    JAL SaveMp3PlayerStructs
    NOP

    JAL PushMp3BoardState
    NOP

    JAL PushMp3MinigamesPlayedList
    NOP

    LI t0, ForeignMinigameAlreadyLoaded
    SW r0, 0x0000 (t0)

    //check if mp1 or mp2 minigame
    LUI v0, 0x800D
    LBU v0, 0xD068 (v0) //get minigame chosen
    ORI at, r0, 139
    SLT at, v0, at //first mp1 minigame
    BNEZ at, isMp2Minigame
    NOP

    //else, is mp1
    isMp1Minigame:
        JAL ComboSwitchGameToMp1
        NOP

    isMp2Minigame:
        JAL mp3_StoreBattleMinigameCoins
        NOP

        //swap to mp2
        JAL ComboSwitchGameToMp2
        NOP

    isMp3Minigame:
        ADDIU v0, v0, 0xFFFF //convert to index
        J 0x80105A6C
        NOP

mp3_ClearBss:
    LUI t0, 0x800B
    ADDIU t0, t0, 0x8AF0
    LUI t1, 0x0003
    ADDIU t1, t1, 0xE080
    mp3_bss_clear_loop:
    SD r0, 0x0000 (t0)
    ADDI t1, t1, 0xFFF8
    BNEZ t1, mp3_bss_clear_loop
    ADDI t0, t0, 0x0008

    J checkosAppNmiBufferReset
    NOP

NegativeCheck:
    JAL 0x8004EE18
    NOP
    JAL PushMp3OvlHis
    NOP

    //if the value is less than 0, it should do something different
    //however, we need this to be a LBU not a LB. so let's check if it's 0xFF directly
    LBU v0, 0x0010 (s4)
    ORI v1, r0, 0x00FF
    BEQ v0, v1, isNegative
    NOP
    //otherwise, not negative
    J 0x800FEF74
    NOP
    isNegative:
    J 0x800FEFEC
    NOP

wackyWatchSet:
    //v1 holds previous watch used value (should always be 2)
    LI at, wackyWatchUsedCopy
    SW v1, 0x0000 (at) //set watch used
    LUI at, 0x800D
    J 0x800F9314
    SH v0, 0xD0AA (at)

clearWackyWatchCopy:
    LI at, wackyWatchUsedCopy
    SW r0, 0x0000 (at) //clear watch used
    JAL 0x8003602C
    ADDIU a0, r0, 0x0006
    J 0x800F9028
    NOP

checkIfCursorShouldMove:
    //v0 currently holds input pressed
    //s0 holds current file index selected
    BEQZ s0, stripLeftRightInput
    NOP
    IfCursorMoveEnd:
        ADDU v1, v0, r0
        J 0x801095BC
        ADDIU v0, r0, 0xFFFF
    stripLeftRightInput:
        J IfCursorMoveEnd
        ANDI v0, v0, 0xFCFF

//IfMidTurnMinigameCheckAsm:
    //JAL IfMidTurnMinigameCheck
    //NOP
    //LUI v1, 0x800D
    //J 0x800FCDE0
    //LW v1, 0x1240 (v1)

mp3_IfMidTurnMinigameCheckAsm2:
    JAL mp3_IfMidTurnMinigameCheck
    NOP
    LUI v0, 0x800D
    J 0x800FCAD0
    LW v0, 0x1240 (v0)

mp2_IfMidTurnMinigameCheckAsm2:
    JAL mp2_IfMidTurnMinigameCheck
    NOP
    LUI v0, 0x800E
    J 0x800653F0
    LW v0, 0x1F8C (v0)

EepromCheckAsmHook:
    JAL EepromTypeSet
        ADDU a0, v0, r0
    
    ADDU a0, v0, r0
    J 0x8000C254
    SLL v0, v0, 16

mp1_prevCode:
    LW ra, 0x0018 (sp)
    LW s1, 0x0014 (sp)
    LW s0, 0x0010 (sp)
    JR RA
    ADDIU sp, sp, 0x20