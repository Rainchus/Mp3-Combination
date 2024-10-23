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


checkIfMinigameIndexIsBlacklisted:
    //v0 holds the current minigame index
    LI v1, minigameBlacklistIDs
    ADDU t0, r0, r0 //loop counter
    minigameBlacklistLoop:
    LBU t1, 0x0000 (v1) //blacklisted id
    BEQ t1, v0, isBlacklisted
    NOP
    ADDIU t0, t0, 1 //increment loop
    SLTI t2, t0, 6 //
    BNEZ t2, minigameBlacklistLoop
    ADDIU v1, v1, 1 //increment blacklist array pointer
    //otherwise, we looped all blacklisted ids and none appeared. minigame is good to use
    LUI at, 0x8010
    ADDU at, at, s0
    J 0x800DFE90
    NOP
    //reroll for a new id that isn't blacklisted
    isBlacklisted:
    J 0x800DFE60
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
    ADDU v0, a0, r0
    JR RA
    ADDIU v0, v0, 1 //minigame 0 doesn't exist, so add 1

ConvertMinigameIndexFromMp3ToMp1OverlayID:
    LI v0, mp1_base
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

    //check if mp1 or mp2 minigame
    LI at, mp1_base
    LW at, 0x0000 (at)
    SLT at, v0, at //first mp1 minigame
    BNEZ at, isMp2Minigame
    NOP

    //otherwise, is mp1 minigame. swap to mp1
    JAL ConvertMinigameIndexFromMp3ToMp1OverlayID
    ADDU a0, v0, r0    

    LI a0, ForeignMinigameIndexToLoad
    SW v0, 0x0000 (a0) //store overlay mp2 should load on boot

    //make a copy of the mp3 player structs
    JAL SaveMp3PlayerStructs
    NOP

    //also make a copy of the overlay history
    //JAL PushMp3OvlHis
    //NOP

    //push the current board state
    JAL PushMp3BoardState
    NOP

    //swap to mp1
    JAL ComboSwitchGameToMp1
    NOP




    isMp2Minigame:
    //otherwise, is mp2 minigame. swap to mp2
    JAL ConvertMinigameIndexFromMp3ToMp2OverlayID
    ADDU a0, v0, r0

    LI a0, ForeignMinigameIndexToLoad
    SW v0, 0x0000 (a0) //store overlay mp2 should load on boot

    //make a copy of the mp3 player structs
    JAL SaveMp3PlayerStructs
    NOP

    //also make a copy of the overlay history
    //JAL PushMp3OvlHis
    //NOP

    //push the current board state
    JAL PushMp3BoardState
    NOP

    //swap to mp2
    JAL ComboSwitchGameToMp2
    NOP

    isMp3Minigame:
        ADDIU v0, v0, 0xFFFF //convert to index
    J 0x80105A6C
    NOP

//80016D0C

ifSkipDebugTextDraw:
    LUI s2, 0x8010
    ADDIU s2, s2, 0x1081 //normally is ADDIU s2, s2, 0x1080 (makes first byte of all strings )
    J 0x80103884
    SB r0, 0xFFFF (s2) //set beginning of all debug drawing strings to '\0', and move printf buffer to not write first byte

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
    JR RA
    NOP

CustomFuncTest:
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

newStarliftOverlayCheck:
    BLTZ v0, lockedCharacter
    SRL t1, v0, 16
    ORI v1, r0, 7
    BEQ t1, v1, lockedCharacter
    NOP
    ORI v1, r0, 3
    BEQ t1, v1, lockedCharacter
    NOP

    //isn't waluigi or daisy, allow cursor to go to character
    J 0x801112E4
    NOP

    lockedCharacter:
    J 0x80111364
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
