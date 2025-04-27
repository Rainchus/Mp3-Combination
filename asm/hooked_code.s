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
PushItemCountToGP:
    JR RA
    DADDU gp, a0, r0

newItemSpinCode:
    //s3 holds current index
    //ORI t0, r0, 3
    J 0x800F6318
    NOP

chillyWatersBankCheck:
    LB v1, 0x000F (s4) //restore from hook (load current player index)
    LUI v0, hi(mp3_gPlayers)
    LBU v0, lo(mp3_gPlayers + 0x4) (v0)
    ANDI v0, v0, 0x30
    BEQ v0, r0, originalBank
    NOP
    //at bank in team mode, check coins as a team
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v1, r0 //pass current player index to a0

    //team captain on v0
    ADDU v1, v0, r0 //return to v1

    originalBank:
    J 0x8010AE24
    SLL v0, v1, 3


chillyWatersBankCheck2:
    LB v0, 0x000F (s4) //restore from hook (load current player index)
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalBank2
    NOP
    //

    //at bank in team mode, check coins as a team
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v0, r0 //pass current player index to a0

    //team captain on v0
  
    originalBank2:
    J 0x8010AF40
    SLL v1, v0, 3

chillyWatersBankCheck3:
    LB v1, 0x000F (s4) //restore from hook (load current player index)
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalBank3
    NOP
    //    
    //at bank in team mode, check coins as a team
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v1, r0 //pass current player index to a0

    //team captain on v0
    ADDU v1, v0, r0 //return to v1

    originalBank3:
    J 0x8010AE74
    SLL v0, v1, 3

chillyWatersBankCheck4:
    LB v1, 0x000F (s4) //restore from hook (load current player index)
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalBank4
    NOP

    //at bank in team mode, check coins as a team
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v1, r0 //pass current player index to a0

    ADDU v1, v0, r0 //return to v1

    originalBank4:
    J 0x8010AECC
    SLL v0, v1, 3

chillyWatersBankCheck5:
    LB a0, 0x000F (s4) //restore from hook (load current player index)
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalBank5
    NOP

    //at bank in team mode, check coins as a team
    JAL GetTeamCaptainCurrentIndex
    NOP //player index already in a0

    ADDU a0, v0, r0 //return to a0

    originalBank5:
    J 0x8010AF1C
    SLL v0, a0, 3


chillyWatersItemMenuClosing:
    //v0 currently holds the item index chosen
    ADDU s0, v0, r0
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalItemMenuClosing
    NOP
    
    JAL GetTeamCaptainCurrentIndex
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

    JAL GetTeamCaptainCurrentIndex
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

    JAL GetTeamCaptainCurrentIndex
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
    JAL GetTeamCaptainCurrentIndex
    LB a0, 0xD067 (a0)
    ADDU v1, v0, r0
    J 0x800E3B1C
    SLL v0, v1, 3

teamCheck1Asm:
    JAL GetTeamCaptainCurrentIndex
    NOP
    J 0x800E3A28
    NOP

teamCheck2Asm:
    JAL GetTeamCaptainCurrentIndex
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
    JAL GetTeamCaptainCurrentIndex
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
    JAL GetTeamCaptainCurrentIndex
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
    JAL GetTeamCaptainCurrentIndex
    NOP
    ADDU a0, v0, r0 //return result to a0
    LW v0, 0x0010 (sp)
    ADDIU sp, sp, 0x18
    J 0x801111FC
    SLL v1, a0, 3

unkCheck:
    JAL GetCurrentPlayerIndex
    NOP
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v0, r0
    J 0x800F76F8
    NOP

shopCoinsCheck:
    JAL GetCurrentPlayerIndex
    NOP
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v0, r0
    J 0x8010BBDC
    NOP

boughtItemShopper:
    ADDIU sp, sp, -0x18
    SW v0, 0x0010 (sp)
    JAL GetCurrentPlayerIndex
    NOP
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v0, r0

    ADDU v1, v0, r0 //return to v1
    LW v0, 0x0010 (sp)
    J 0x8010BF90
    ADDIU sp, sp, 0x18


teamCheck5Asm:
    LUI a0, 0x800D
    JAL GetTeamCaptainCurrentIndex
    LB a0, 0xD067 (a0)
    ADDU v1, v0, r0 //store result in v1
    J 0x800E2B74
    ADDU t0, v0, r0 //store in t0 for another hook (hook at 0x800E2BA8)

teamCheck7Asm:
    LUI a0, 0x800D
    JAL GetTeamCaptainCurrentIndex
    LB a0, 0xD067 (a0)
    ADDU v1, v0, r0 //store result in v1
    J 0x800E2BF8
    ADDU t0, v0, r0 //store in t0 for another hook (hook at 0x800E2C28)

teamCheck8Asm:
    LUI a0, 0x800D
    JAL GetTeamCaptainCurrentIndex
    LB a0, 0xD067 (a0)
    J 0x80106DD0
    ADDU t0, v0, r0 //store in t0 for another hook (hook at 0x80106DF8)

teamCheck9Asm:
    LUI a0, 0x800D
    JAL GetTeamCaptainCurrentIndex
    LB a0, 0xD067 (a0)
    J 0x800DDAC0
    ADDU t0, v0, r0 //store in t0 for another hook (hook at 0x80106DF8)

//for item bag writing to items array
teamCheck10Asm:
    LUI a0, 0x800D
    LB a0, 0xD067 (a0)
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalTeamCheck10Asm
    NOP

    ADDIU sp, sp, -0x18
    SW v0, 0x0014 (sp)
    originalTeamCheck10Asm:
    JAL GetTeamCaptainCurrentIndex
    NOP
    ADDU a0, v0, r0 //return to a0
    LW v0, 0x0014 (sp)
    ADDIU sp, sp, 0x18
    J 0x8010C540
    NOP

//when you use an item and the item list background flips, -
//it pulls the player index to see where to remove the item from
//adjusted for teams
itemUsedRemoveFromLargeItemList:
    ADDIU sp, sp, -0x18
    SW v0, 0x0010 (sp)
    JAL GetTeamCaptainCurrentIndex
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

teamCheck11Asm:
    JAL teamCheck11_C
    NOP
    J 0x8010FDC8
    NOP

teamCheck13Asm:
    LB v1, 0x0000 (a1) //restore
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalTeamCheck13Asm
    NOP

    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v1, r0 //pass current player index to a0

    LUI a1, 0x800D //restore from hook
    ADDIU a1, a1, 0xD067 //restore from hook

    ADDU v1, v0, r0 //return to v1
    originalTeamCheck13Asm:
    J 0x800E3240
    SLL v0, v1, 3 //restore

teamCheck14Asm: //some kind of cpu shop coins check?
    LUI a0, 0x800D //restore from hook
    LB a0, 0xD067 (a0) //restore from hook

    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalTeamCheck14Asm
    NOP

    JAL GetTeamCaptainCurrentIndex
    NOP

    ADDU a0, v0, r0 //return to a0

    originalTeamCheck14Asm:
    J 0x8010BAE0
    NOP

bowserPhoneCpuNoCoinsCheck:
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalbowserPhoneCpuNoCoinsCheck
    NOP

    ADDIU sp, sp, -0x18
    SW a0, 0x0014 (sp)

    LUI a0, 0x800D
    JAL GetTeamCaptainCurrentIndex
    LB a0, 0xD067 (a0)

    JAL mp3_GetPlayerStruct
    ADDU a0, v0, r0 //team captain player index to a0

    
    LW a0, 0x0014 (sp)
    ADDIU sp, sp, 0x18

    J 0x8011CA18
    LH v0, 0x000A (v0) //load team captain coins

    originalbowserPhoneCpuNoCoinsCheck:
    LUI at, 0x800D
    ADDU at, at, v0
    LH v0, 0x1112 (at)
    J 0x8011CA18
    NOP

storeTeamIndex_Asm:
    JAL mp3_GetPlayerStruct //restore from hook
    ADDIU a0, r0, 0xFFFF //restore from hook
    SW v0, 0x0074 (sp) //restore from hook
    JAL storeTeamIndex
    NOP
    J 0x8010B6AC
    SW v0, 0x00E8 (sp) //store to extended stack space

GiveTeamCaptainMinigameItem2:
    LB v1, 0x000F (s4)
    J 0x800FE88C
    SLL a0, v1, 3

GiveTeamCaptainMinigameItem3:
    LUI t1, hi(mp3_gPlayers)
    LBU t1, lo(mp3_gPlayers + 0x4) (t1)
    ANDI t1, t1, 0x30
    BEQL t1, r0, GiveTeamCaptainMinigameItemExit3
    SB v0, 0x0000 (v1)
    
    ADDIU sp, sp, -0x20
    SW t0, 0x0014 (sp) //empty item slot
    SW v0, 0x0018 (sp) //item id

    JAL GetTeamCaptainCurrentIndex
    LB a0, 0x000F (s4) //current player index

    JAL mp3_GetPlayerStruct
    ADDU a0, v0, r0
    ADDIU v0, v0, 0x18 //point to items beginning

    LW t0, 0x0014 (sp) //empty item slot
    ADDU v0, v0, t0 //now points to player's item slot to store to
    LW v1, 0x0018 (sp) //item id
    SB v1, 0x0000 (v0) //store to team captain's item array
    ADDIU sp, sp, 0x20

    GiveTeamCaptainMinigameItemExit3:
    J 0x800FE9B0
    NOP

bowserCoinCheckAsm:
    JAL bowserCoinCheck
    NOP
    J 0x80108F50
    ADDU a0, v0, r0 //return result to a0
    
duelingGloveCheck:
    LUI s0, 0x800D //restore from hook
    ADDIU s0, s0, 0xD067 //restore from hook
    LB v1, 0x0000 (s0) //restore from hook

    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalDuelingGlove
    NOP
    //
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v1, r0 //pass current player index to a0
    ADDU v1, v0, r0
    originalDuelingGlove:
    J 0x800E2D18
    NOP

//removes warp block from inventory
warpBlockCheck:
    LUI v1, 0x800D
    LB v1, 0xD067 (v1)
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalWarpBlockCheck
    NOP
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v1, r0 //pass current player index to a0
    ADDU v1, v0, r0 //return to v1 for hooked code
    originalWarpBlockCheck:
    J 0x800E2E54
    NOP

//checks if you can afford to steal (5 coins)
newBooCheck:
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalBooCheck
    NOP
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v0, r0 //pass current player index to a0    
    originalBooCheck:
    J 0x8010E374
    SLL v1, v0, 3

//TODO: add check so if a teammate is the only one you can steal from, gray out the option
newBooCanStealStarCheck:
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalBooStarStealCheck
    NOP
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v0, r0 //pass current player index to a0
    originalBooStarStealCheck:
    J 0x8010E4BC
    SLL v1, v0, 3

newBooCheckIfAnyCanBeStolenFrom:
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalBooCheckIfAnyCanBeStolenFrom
    NOP

    JAL FindCurPlayerTeammate
    LB a0, 0x000F (s7)

    ADDU t1, v0, r0 //return to t1

    originalBooCheckIfAnyCanBeStolenFrom:
    ADDU s0, r0, r0
    J 0x8010E478
    LB v1, 0x000F (s7)

//if teammate is only valid star steal target, remove the option from being available
newBooCheckIfAnyCanBeStolenFrom2:
    SLL v0, s0, 3 //restore from hook
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalBooCheckIfAnyCanBeStolenFrom2
    NOP

    BEQ t1, s0, booCheckIsTeammate
    NOP

    originalBooCheckIfAnyCanBeStolenFrom2:
    SUBU v0, v0, s0
    J 0x8010E488
    SLL v0, v0, 3

    booCheckIsTeammate:
    J 0x8010E49C
    NOP

newPlunderChestCheck:
    //black out all 4 characters, then go back and make enemy team captain available
    lui        $v0, 0x800D //restore from hook
    lb         $v0, 0xD067($v0) //restore from hook
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BNE t0, r0, newPlunderChestCheckLabel
    NOP
    //is vanilla, exit
    J 0x80117E34
    NOP
    //teams active, modify selectable players in plunder chest
    newPlunderChestCheckLabel:
    //black out all 4 character's name in plunder chest event
    sll       $v0, $s0, 4
    addu       $v0, $s1, $v0
    sb         $s3, 0x0($v0)
    addu       $v0, $s2, $s0
    j          L80117E60_32D9D0_name_48
    sb        $zero, 0x0($v0)

    //fallthrough

    L80117E60_32D9D0_name_48:
        sll        $a1, $s0, 4
        addu       $a1, $s1, $a1
        addu       $a0, $s0, $zero
        jal        0x800E2260
        addiu     $a1, $a1, 0x1
        addiu      $s0, $s0, 0x1
        slti       $v0, $s0, 0x4
        bnez       $v0, newPlunderChestCheck
        addiu     $v0, $zero, 0x1

    //all 4 characters have been set as invalid. now set enemy team captain to active
    //makes character able to be chosen
    //s0 was just the loop counter so we can use it here
    L80117E50_32D9C0_name_48: //s0 needs to be player index
        lui        $a0, 0x800D
        JAL mp3_GetPlayerStruct
        lb         $a0, 0xD067($a0)

        LBU t0, 0x0004 (v0) //load flags1
        ANDI t0, t0, 0x0030
        SRL t0, t0, 5 //convert team index into index (0 or 1)
        XORI t0, t0, 1 //flip to other team
        LI t1, firstPlayerEachTeam
        SLL t0, t0, 2
        ADDU t1, t1, t0
        LW t1, 0x0000 (t1) //load enemy captain player pointer
        LBU s0, 0x001D (t1) //load current player turn order
        sll       $v0, $s0, 4
        addu       $v0, $s1, $v0
        sb         $s5, 0x0($v0)
        addu       $v0, $s2, $s0
        sb         $s3, 0x0($v0)
        J 0x80117E84
        ADDIU v0, r0, 1


newPlunderChestItemStoreCheck:
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalPlunderChestItemStoreCheck
    LB a0, 0x000F (s6)
    ADDIU sp, sp, -0x18
    SW v0, 0x0014 (sp)
    JAL GetTeamCaptainCurrentIndex
    NOP
    ADDU a0, v0, r0 //return team captain index to a0
    LW v0, 0x0014 (sp)
    ADDIU sp, sp, 0x18
    originalPlunderChestItemStoreCheck:
    J 0x80118004
    SLL v1, a0, 3

//related to how items spawn when using a plunder chest
newPlunderChest2:
    LB a0, 0x000F (s6) //restore from hook
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalNewPlunderChest2
    NOP
    ADDIU sp, sp, -0x18
    SW v0, 0x0014 (sp)
    JAL GetTeamCaptainCurrentIndex
    NOP
    ADDU a0, v0, r0 //return team captain index to a0
    LW v0, 0x0014 (sp)
    ADDIU sp, sp, 0x18
    originalNewPlunderChest2:
    J 0x80118098
    SLL v1, a0, 3 //restore from hook

newPlunderChest5:
    LB v0, 0x000F (s6) //restore from hook
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalPlunderChest5
    NOP
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v0, r0 //move cur player index into a0
    ADDU a0, v0, r0 //return team captain index to a0    
    originalPlunderChest5:
    J 0x80118134
    SLL v0, v0, 3

newDuelGlove: //f0 is not pushed here but it should be fine
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalDuelGlove
    LB a0, 0x000F (s3)
    JAL GetTeamCaptainCurrentIndex
    NOP
    ADDU a0, v0, r0 //return to a0
    originalDuelGlove:
    J 0x801103E8
    MUL.S f0, f0, f20

newDuelGlove3: //f0 is not pushed here but it should be fine
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalDuelGlove2
    LB a0, 0x000F (s3)
    JAL GetTeamCaptainCurrentIndex
    NOP
    ADDU a0, v0, r0 //return to a0
    originalDuelGlove2:
    J 0x8011046C
    MUL.S f0, f0, f20

newBattleCheck:
    LUI t1, hi(mp3_gPlayers)
    LBU t1, lo(mp3_gPlayers + 0x4) (t1)
    ANDI t1, t1, 0x30
    LW t0, 0x0074 (sp)
    BEQ t1, r0, originalBattleCheck
    LBU v1, 0x001D (t0)
    
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v1, r0 //move player index to a0
    LW t0, 0x0074 (sp)
    ADDU v1, v0, r0 //return captain index to v1
    originalBattleCheck:
    J 0x800FADBC
    NOP

newBattleCheck3: //s0 is loop counter
    LUI at, 0x800D
    ADDU at, at, v0
    LH v0, 0x1112 (at)

    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalBattleCheck3
    NOP
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, s0, r0 //move player index to a0
    JAL mp3_GetPlayerStruct
    ADDU a0, v0, r0 //player index to a0
    LH v0, 0x000A (v0) //load coins from team captain
    originalBattleCheck3:
    BEQZ v0, goto800FAE58 //if team has 0 coins, use black text for player's name in duel
    SLL v0, s0, 4
    ADDIU sp, sp, -0x18
    SW fp, 0x0014 (sp)

    //if s0 and cur_player_index are on same team, black out text
    JAL mp3_GetPlayerStruct
    ADDU a0, s0, r0 //check current player in loop

    ADDU fp, v0, r0 //player struct of player in loop

    LUI a0, 0x800D
    JAL mp3_GetPlayerStruct
    LB a0, 0xD067 (a0)

    //player struct of cur player

    LBU t0, 0x0004 (fp) //load first player flags1
    LBU t1, 0x0004 (v0) //load second player flags1
    ANDI t0, t0, 0x0030
    ANDI t1, t1, 0x0030
    LW fp, 0x0014 (sp)
    ADDIU sp, sp, 0x18

    BEQ t0, t1, goto800FAE58 //if player is on your team, black out text
    SLL v0, s0, 4
    J 0x800FAE28
    NOP

    goto800FAE58:
    J 0x800FAE58
    NOP

newDuelCheck2Asm:
    LUI t1, hi(mp3_gPlayers)
    LBU t1, lo(mp3_gPlayers + 0x4) (t1)
    ANDI t1, t1, 0x30
    BEQ t1, r0, originalDuelCheck2Asm
    ADDU t0, s4, r0 //move s4 to t0

    ADDIU sp, sp, -0x18
    SW r0, 0x0014 (sp)

    JAL newDuelCheck
    NOP
    SW v0, 0x0014 (sp)

    JAL newDuelCheck2
    NOP
    LW t0, 0x0014 (sp) //we return the opponent from newDuelCheck to t0 for 2nd hook
    J 0x800FB0D4
    ADDIU sp, sp, 0x18

    originalDuelCheck2Asm:
    LUI v0, 0x800D
    J 0x800FB0D4
    LB v0, 0xD067 (v0)
    
dragItemCheck:
    LUI v0, 0x800D //run this instruction a bit early
    LB v0, 0xD067 (v0) //run this instruction a bit early

    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalDragItemCheck
    NOP

    LUI a0, 0x800D //run this instruction a bit early
    JAL GetTeamCaptainCurrentIndex
    LB a0, 0xD067 (a0) //run this instruction a bit early

    originalDragItemCheck:
    LUI a0, 0x8010 //restore from hook
    J 0x8010FED0
    LH a0, 0x570C (a0) //restore from hook

luckyLampRemovalCheck:
    LUI a0, 0x800D //restore from hook
    LB a0, 0xD067 (a0) //restore from hook

    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalLuckyLampRemovalCheck
    NOP
    ADDIU sp, sp, -0x18
    SW v0, 0x0014 (sp)
    JAL GetTeamCaptainCurrentIndex
    NOP
    ADDU a0, v0, r0 //return captain team index to a0
    LW v0, 0x0014 (sp)
    ADDIU sp, sp, 0x18
    originalLuckyLampRemovalCheck:
    J 0x8011176C
    NOP

wackyWatchRemovalCheck:
    LB a0, 0x000F (s5) //load current player index
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalWackyWatchRemovalCheck
    NOP
    ADDIU sp, sp, -0x18
    SW v0, 0x0014 (sp)

    JAL GetTeamCaptainCurrentIndex
    NOP

    ADDU a0, v0, r0 //return captain index to a0
    LW v0, 0x0014 (sp)
    ADDIU sp, sp, 0x18

    originalWackyWatchRemovalCheck:
    J 0x80115E4C
    SLL v1, a0, 3

goldenMushroomCheck:
    LB v1, 0x0000 (s0) //load current player index
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalGoldenMushroomCheck
    NOP
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v1, r0 //cur player index to a0 
    ADDU v1, v0, r0 //return to v1
    originalGoldenMushroomCheck:
    J 0x800E3000
    SLL v0, v1, 3

booBellCheck:
    LUI a1, 0x800D //restore from hook
    ADDIU a1, a1, 0xD067 //restore from hook
    LB v1, 0x0000 (a1) //restore from hook

    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalBooBellCheck
    NOP
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v1, r0 //cur player index to a0 

    LUI a1, 0x800D //restore from hook
    ADDIU a1, a1, 0xD067 //restore from hook
    originalBooBellCheck:
    J 0x800E3104
    NOP

booRepellentCheck:
    LUI a1, 0x800D //restore from hook
    ADDIU a1, a1, 0xD067 //restore from hook
    LB v1, 0x0000 (a1) //restore from hook

    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalbooRepellentCheck
    NOP
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v1, r0 //cur player index to a0 

    LUI a1, 0x800D //restore from hook
    ADDIU a1, a1, 0xD067 //restore from hook
    originalbooRepellentCheck:
    J 0x800E3184
    NOP

bowserSuitCheck:
    LUI a1, 0x800D //restore from hook
    ADDIU a1, a1, 0xD067 //restore from hook
    LB v1, 0x0000 (a1) //restore from hook

    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalBowserSuitCheck
    NOP
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v1, r0 //cur player index to a0 

    ADDU v1, v0, r0 //return to v1

    LUI a1, 0x800D //restore from hook
    ADDIU a1, a1, 0xD067 //restore from hook
    originalBowserSuitCheck:
    J 0x800E321C
    NOP

magicLampCheck:
    LUI v1, 0x800D //restore from hook
    LB v1, 0xD067 (v1) //restore from hook
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalMagicLampCheck
    NOP
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v1, r0 //cur player index to a0 
    ADDU v1, v0, r0 //return to v1
    originalMagicLampCheck:
    J 0x800E32B0
    NOP

koopaKardCheck:
    LUI a1, 0x800D //restore from hook
    ADDIU a1, a1, 0xD067 //restore from hook
    LB v1, 0x0000 (a1) //restore from hook

    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalKoopaKardCheck
    NOP
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v1, r0 //cur player index to a0 

    ADDU v1, v0, r0 //return to v1
    LUI a1, 0x800D //restore from hook
    ADDIU a1, a1, 0xD067 //restore from hook

    originalKoopaKardCheck:
    J 0x800E33C0
    NOP

checkTeamCoinsForGameGuy:
    LB v0, 0x000F (s4) //restore from hook (load current player index)
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalCoinsGameGuy
    NOP
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v0, r0 //cur player index to a0

    originalCoinsGameGuy:
    J 0x800FEA5C
    SLL v1, v0, 3

/* previous implementation of checkTeamCoinsForGameGuy2
checkTeamCoinsForGameGuy2:
    LB v1, 0x000F (s4) //restore from hook (load current player index)
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalCoinsGameGuy2
    NOP
    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v1, r0 //cur player index to a0
    ADDU v1, v0, r0 //return to v1
    originalCoinsGameGuy2:
    J 0x800FEA88
    SLL v0, v1, 3
    */

checkTeamCoinsForGameGuy3:
    LB a0, 0x000F (s4) //restore from hook (load current player index)
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalCoinsGameGuy3
    NOP
    JAL GetTeamCaptainCurrentIndex
    NOP
    ADDU a0, v0, r0 //return to a0

    originalCoinsGameGuy3:
    J 0x800FEAD4
    SLL v0, a0, 3

checkTeamCoinsForGameGuy4:
    LB a0, 0x000F (s4) //restore from hook (load current player index)
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalCoinsGameGuy4
    NOP
    JAL GetTeamCaptainCurrentIndex
    NOP
    ADDU a0, v0, r0 //return to a0
    originalCoinsGameGuy4:
    J 0x800FEAB0
    SLL v0, a0, 3

newGameGuyGiveCoinsHud:
    //if teams are active, skip showing coin change (after game guy and after something else unknown)
    LUI v0, hi(mp3_gPlayers)
    LBU v0, lo(mp3_gPlayers + 0x4) (v0)
    ANDI v0, v0, 0x30
    BEQ v0, r0, newGameGuyGiveCoinsHudLabel
    NOP
    //skip showing coin change
    J 0x800FC53C
    NOP
    newGameGuyGiveCoinsHudLabel:
    JAL	0x800E1F28
    NOP
    J 0x800FC53C
    NOP

//is this only for magic lamps?
starPurchaseCheck:
    LB v0, 0x000F (s1) //restore from hook (load current player index)
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalStarPurchaseCheck
    NOP
    ADDIU sp, sp, -0x18
    SW a0, 0x0014 (sp)

    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v0, r0 //current player index to a0

    LW a0, 0x0014 (sp)
    ADDIU sp, sp, 0x18

    originalStarPurchaseCheck:
    J 0x8010A604
    SLL v1, v0, 3

snowballThrowEventCheck:
    LUI v1, 0x800D
    LB v1, 0xD067 (v1) //restore from hook (load current player index)
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalSnowballThrowEventCheck
    NOP

    JAL GetTeamCaptainCurrentIndex
    ADDU a0, v1, r0 //current player index to a0

    ADDU v1, v0, r0 //return to v1

    originalSnowballThrowEventCheck:
    J 0x8011BA30
    NOP

hiddenItemBlockCheck:
    LW a0, 0x0000 (s1) //restore from hook (load current player index)
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalItemBlockCheck
    NOP
    ADDIU sp, sp, -0x18
    SW v0, 0x0014 (sp)
    JAL GetTeamCaptainCurrentIndex
    NOP

    ADDU a0, v0, r0 //return to a0

    LW v0, 0x0014 (sp) //pop original value of v0
    ADDIU sp, sp, 0x18

    originalItemBlockCheck:
    J 0x800DE268
    SLL v1, a0, 3

checkSetTeamModeAsm:
    ADDIU sp, sp, -0x18
    SW a0, 0x0014 (sp)
    JAL checkSetTeamMode
    NOP

    LW a0, 0x0014 (sp) //restore a0
    ORI a0, a0, 0x01FE //restore from hook
    ADDIU sp, sp, 0x18
    J 0x801067D0
    SW r0, 0x0010 (sp)  //restore from hook

getItemFromItemSpaceQuestionHook2:
    SLL s7, s3, 3 //restore from hook
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalGetItemFromItemSpaceQuestionHook2
    NOP

    //get team index, not usual team captain index
    //s3 holds current player index
    JAL mp3_GetPlayerStruct
    ADDU a0, s3, r0
    LBU t0, 0x0004 (v0) //load flags1
    ANDI t0, t0, 0x0030
    SRL t0, t0, 5 //team index to s3 (this way items given to player go top left or top right)
    SLL s7, t0, 3 //restore from hook
    originalGetItemFromItemSpaceQuestionHook2:
    J 0x800F7744
    LUI at, 0x8010
    

getOneItemBabyBowser:
    SLL v1, s3, 3 //restore from hook
    SUBU v1, v1, s3 //restore from hook
    LUI t0, hi(mp3_gPlayers)
    LBU t0, lo(mp3_gPlayers + 0x4) (t0)
    ANDI t0, t0, 0x30
    BEQ t0, r0, originalGetOneItemBabyBowser
    NOP
    ADDIU sp, sp, -0x18
    SW v0, 0x0014 (sp)

    LUI a0, 0x800D
    JAL GetTeamCaptainCurrentIndex
    LB a0, 0xD067 (a0)

    SLL v1, v0, 3 //restore from hook
    SUBU v1, v1, v0 //restore from hook

    LW v0, 0x0014 (sp)
    ADDIU sp, sp, 0x18

    J 0x800F7BF0
    NOP


    originalGetOneItemBabyBowser:
    J 0x800F7BF0
    NOP

mp1SetCpuDifficultyMod:
    LBU t0, 0x0011 (s0)
    ORI t1, r0, 2
    BEQ t0, t1, isOnHard
    NOP
    BEQZ t0, isOnEasy
    NOP
    J cpuDifficultyHookExit
    NOP

    isOnEasy:
    BEQ s3, t1, setTo3
    NOP
    J cpuDifficultyHookExit
    NOP

    isOnHard:
    //now check if they scrolled up or down
    BEQZ s3, setTo3
    NOP
    J cpuDifficultyHookExit
    NOP

    setTo3:
    ADDIU s3, r0, 3

    cpuDifficultyHookExit:
    sb $s3, 0x11($s0)
    J 0x80070854
    ADDIU v0, r0, 3

mp3LastTurnMinigameCheck:
    //currently v0 holds the index into the current random minigame type
    LUI t0, 0x800D
    LBU t0, 0xD05A (t0) //total turns
    LUI t1, 0x800D
    LBU t1, 0xD05B (t1) //current turn
    BNE t0, t1, isntLastTurn
    NOP

    LUI t0, 0x800B
    LBU t0, 0x23B0 (t0)
    BNEZ t0, isntStoryMode
    NOP


    ADDIU sp, sp, -0x18
    SW v0, 0x0014 (sp)

    LW v1, 0x0018 (s3) //restore from hook
    ADDU v1, v1, v0 //restore from hook
    LBU v0, 0x0000 (v1) //load minigame index
    JAL mp3_LastTurnMinigameWheelLogic
    NOP
    ADDU v1, v0, r0 //move result to v1

    LW v0, 0x0014 (sp)
    ADDIU sp, sp, 0x18

    BNEZ v1, isntMp3Game
    NOP

    isntLastTurn:
    isntStoryMode:
    LW v1, 0x0018 (s3) //restore from hook
    J 0x800DFE84
    ADDU v1, v1, v0 //restore from hook

    isntMp3Game:
    J 0x800DFE60
    NOP
    
