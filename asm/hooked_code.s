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

checkColorSetAsm:
    JAL checkColorSet_C_1
    NOP
    J 0x800FE254
    NOP

checkColorSetAsm2:
    JAL checkColorSet_C_2
    NOP
    J 0x800FCD30
    NOP

//use gp to track the amount of items that should be parsed
//this will make it easy to do `SLTI $rd, $rs, X -> SLT $rd, $rs, $gp
SetItemCountToGP:
    JR RA
    DADDU gp, a0, r0

newItemSpinCode:
    //s3 holds current index
    //ORI t0, r0, 3
    J 0x800F6318
    NOP

chillyWatersBankCheck:
    LUI v1, hi(mp3_gPlayers)
    LBU v1, lo(mp3_gPlayers + 0x4) (v1)
    ANDI v1, v1, 0x30
    BEQ v1, r0, originalBank
    NOP
    //at bank in team mode, check coins as a team
    SRL v1, v1, 5 //convert to team index
    SLL v1, v1, 2
    LUI v0, hi(firstPlayerEachTeam)
    ADDIU v0, v0, lo(firstPlayerEachTeam)
    ADDU v0, v0, v1
    LW v1, 0x0000 (v0)
    LH a2, 0x000A (v1) //load team player's coins
    J 0x8010AE38
    SLL v0, v1, 3

    originalBank:
    LB v1, 0x000F (s4)
    J 0x8010AE24
    SLL v0, v1, 3


chillyWatersBankCheck2:
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalBank2
    NOP
    //
    //at bank in team mode, check coins as a team
    SRL t0, t0, 5 //convert to team index
    SLL t0, t0, 2
    LUI v0, hi(firstPlayerEachTeam)
    ADDIU v0, v0, lo(firstPlayerEachTeam)
    ADDU v0, v0, t0
    LW t0, 0x0000 (v0)
    J 0x8010AF54
    LH v0, 0x000A (t0) //load team player's coins    

    originalBank2:
    LUI v0, 0x800D
    ADDU v0, v0, v1
    J 0x8010AF54
    LH v0, 0x1112 (v0)

chillyWatersItemMenuClosing:
    //v0 currently holds the item index chosen
    ADDU s0, v0, r0
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalItemMenuClosing
    NOP
    
    JAL GetTeamCurrentIndex
    NOP
    SLL v1, v0, 3
    SUBU v1, v1, v0
    ADDU v0, s0, r0
    J 0x801122CC
    ADDU s0, s3, r0

    originalItemMenuClosing:
    SLL v1, s2, 3
    SUBU v1, v1, s2
    ADDU v0, s0, r0
    J 0x801122CC
    ADDU s0, s3, r0

chillyWatersSkeletonKeyThing:
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalchillyWatersSkeletonKeyThing
    NOP

    JAL GetTeamCurrentIndex
    NOP
    LUI a0, 0x8010
    J 0x80112184
    LH a0, 0x570C (a0)

    originalchillyWatersSkeletonKeyThing:
    LUI a0, 0x8010
    J 0x80112184
    LH a0, 0x570C (a0)

chillyWatersSkeletonKeyThing4:
//this hook is really strange. we replace s2 with the player index of the combined team
//this lets us use s2 temporarily
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalchillyWatersSkeletonKeyThing4
    NOP

    //is team mode
    ADDU s2, v0, r0 //push v0

    JAL GetTeamCurrentIndex
    NOP

    ADDU v1, s2, r0 //pop v0 temporarily to v1
    ADDU s2, v0, r0 //copy first found player's index of current player's team to s2
    ADDU v0, v1, r0 //pop original v0 back to v0

    SLL v1, s2, 3
    SUBU v1, v1, s2
    J 0x80112440
    NOP
    

    originalchillyWatersSkeletonKeyThing4:
    SLL v1, s2, 3
    J 0x80112440
    SUBU v1, v1, s2
    



teamCheck0Asm: //s3 holds player index (return result to v1)
    LUI a0, 0x800D
    JAL GetTeamCurrentIndex
    LB a0, 0xD067 (a0)
    ADDU v1, v0, r0
    J 0x800E3B1C
    SLL v0, v1, 3

teamCheck1Asm:
    JAL GetTeamCurrentIndex
    NOP
    J 0x800E3A28
    NOP

teamCheck2Asm:
    JAL GetTeamCurrentIndex
    NOP
    ADDU v1, v0, r0
    J 0x800E3A80
    SLL v0, v1, 3

teamCheck3Asm:
    SH v0, 0x0000 (s0)
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalTeamCheck3
    NOP
    //
    JAL GetTeamCurrentIndex
    NOP
    SLL v1, v0, 3
    SUBU v0, v1, v0
    J 0x800E3C94
    NOP
        
    originalTeamCheck3:
    SLL v0, s3, 3
    SUBU v0, v0, s3
    J 0x800E3C94
    NOP


teamCheck4Asm:
    //v0 holds current item index to write to
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQL t0, r0, originalCpuItemGet
    LB v1, 0x000F (s4)
    //team item get
    ADDIU sp, sp, -0x20
    SW v0, 0x0018 (sp)
    LUI a0, 0x800D
    JAL GetTeamCurrentIndex
    LB a0, 0xD067 (a0)
    ADDU v1, v0, r0
    LW v0, 0x0018 (sp) //pop item id to give player
    ADDIU sp, sp, 0x20

    originalCpuItemGet:
    J 0x800FE88C //jump back to normal location
    SLL a0, v1, 3

unkItemsAsm0:
    ADDIU sp, sp, -0x18
    SW v0, 0x0010 (sp)
    JAL GetTeamCurrentIndex
    NOP
    ADDU a0, v0, r0 //return result to a0
    LW v0, 0x0010 (sp)
    ADDIU sp, sp, 0x18
    J 0x801111FC
    SLL v1, a0, 3

unkCheck:
    JAL GetCurrentPlayerIndex
    NOP
    JAL GetTeamCurrentIndex
    ADDU a0, v0, r0
    J 0x800F76F8
    NOP

shopCoinsCheck:
    JAL GetCurrentPlayerIndex
    NOP
    JAL GetTeamCurrentIndex
    ADDU a0, v0, r0
    J 0x8010BBDC
    NOP

boughtItemShopper:
    ADDIU sp, sp, -0x18
    SW v0, 0x0010 (sp)
    JAL GetCurrentPlayerIndex
    NOP
    JAL GetTeamCurrentIndex
    ADDU a0, v0, r0

    ADDU v1, v0, r0 //return to v1
    LW v0, 0x0010 (sp)
    J 0x8010BF90
    ADDIU sp, sp, 0x18


teamCheck5Asm:
    LUI a0, 0x800D
    JAL GetTeamCurrentIndex
    LB a0, 0xD067 (a0)
    ADDU v1, v0, r0 //store result in v1
    J 0x800E2B74
    ADDU t0, v0, r0 //store in t0 for another hook (hook at 0x800E2BA8)

teamCheck7Asm:
    LUI a0, 0x800D
    JAL GetTeamCurrentIndex
    LB a0, 0xD067 (a0)
    ADDU v1, v0, r0 //store result in v1
    J 0x800E2BF8
    ADDU t0, v0, r0 //store in t0 for another hook (hook at 0x800E2C28)

teamCheck8Asm:
    LUI a0, 0x800D
    JAL GetTeamCurrentIndex
    LB a0, 0xD067 (a0)
    J 0x80106DD0
    ADDU t0, v0, r0 //store in t0 for another hook (hook at 0x80106DF8)

teamCheck9Asm:
    LUI a0, 0x800D
    JAL GetTeamCurrentIndex
    LB a0, 0xD067 (a0)
    J 0x80106DD0
    ADDU t0, v0, r0 //store in t0 for another hook (hook at 0x80106DF8)

teamCheck10Asm:
    LUI a0, 0x800D
    JAL GetTeamCurrentIndex
    LB a0, 0xD067 (a0)
    J 0x8010C540
    ADDU a0, v0, r0 //store in t0 for another hook (hook at 0x800DDAE8)    

//when you use an item and the item list background flips, -
//it pulls the player index to see where to remove the item from
//adjusted for teams
itemUsedRemoveFromLargeItemList:
    ADDIU sp, sp, -0x18
    SW v0, 0x0010 (sp)
    JAL GetTeamCurrentIndex
    LB a0, 0x000F (s3) //load current player index
    ADDU a0, v0, r0 //return to a0
    LW v0, 0x0010 (sp)
    ADDIU sp, sp, 0x18
    J 0x801170B8
    ADDU a1, v0, r0

teamCheck6Asm:
    JAL teamCheck6_C
    NOP
    J 0x8010FDAC
    NOP

storeTeamIndex_Asm:
    JAL mp3_GetPlayerStruct //restore from hook
    ADDIU a0, r0, 0xFFFF //restore from hook
    SW v0, 0x0074 (sp) //restore from hook
    JAL storeTeamIndex
    NOP
    J 0x8010B6AC
    SW v0, 0x00E8 (sp) //store to extended stack space

getItemFromItemSpaceQuestionHook:
    JAL 0x800E49DC
    ADDU a0, s3, r0
    //we need to poke s7 to either 0 or 1 for top left or top right area for items to go to
    ADDIU sp, sp, -0x20
    SW v0, 0x0014 (sp)
    JAL CStuff
    NOP
    ADDU s7, v0, r0
    LW v0, 0x0014 (sp)
    J 0x800F7750
    ADDIU sp, sp, 0x20

    