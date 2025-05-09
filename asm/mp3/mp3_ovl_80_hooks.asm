.headersize 0x800D6B70 - 0xEA790
//check for teams by getting bit (offset 4) from p1 mp3_gPlayers (0x10 is team 1, 0x20 is team 2)
.org 0x800F2E30
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, origUpdateBoardStatus
    NOP
    //set normal p3 and p4 offscreen
    //LI v0, 0x80101794
    //ORI v1, r0, 0x280
    //SH v1, 0x0008 (v0) //set p3 xPos root off screen
    //SH v1, 0x000C (v0) //set p3 xPos root off screen
    J newUpdatePlayerBoardStatus
    NOP
    origUpdateBoardStatus:
    J originalUpdatePlayerBoardStatus
    NOP

.org 0x800F3400
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, origfunc_800F3400
    NOP
    J newfunc_800F3400_107020_shared_board
    NOP
    origfunc_800F3400:
    J originalfunc_800F3400_107020_shared_board
    NOP

.org 0x800F4874
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, origfunc_800F4874
    NOP
    J newfunc_800F4874_108494_shared_board
    NOP
    origfunc_800F4874:
    J originalfunc_800F4874_108494_shared_board
    NOP

.org 0x800F4190
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, originalfunc_800F4190
    NOP
    J newfunc_800F4190_107DB0_shared_board
    NOP
    originalfunc_800F4190:
    J originalfunc_800F4190_107DB0_shared_board
    NOP


.org 0x800F3A80
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, originalfunc_800F3A80
    NOP
    J newfunc_800F3A80_1076A0_shared_board
    NOP
    originalfunc_800F3A80:
    J originalfunc_800F3A80_1076A0_shared_board
    NOP

/*
.org 0x800F4798
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, originalfunc_800F4798
    NOP
    J newfunc_800F4798_1083B8_shared_board
    NOP
    originalfunc_800F4798:
    J originalfunc_800F4798_1083B8_shared_board
    NOP
*/

//.org 0x800FE24C
    //J checkColorSetAsm
    //LBU a1, 0x001C (s2)

//.org 0x800FCD28
    //J checkColorSetAsm2
    //ADDU a0, s1, r0

.org 0x800FC534
    J newGameGuyGiveCoinsHud
    NOP

//.org 0x800FADB4
    //J newDuelCheck3
    //NOP

//.org 0x800FAE14
    //J newDuelCheck4
    //NOP

//checks how many coins the current player has
//.org 0x800FB0CC
    //J newDuelCheck2Asm
    //ADDU a0, s4, r0

//.org 0x800FB0E0 //the 0x800FB0CC hook above modifies t0
    //SLL v0, t0, 3
    //SUBU v0, v0, t0

//.org 0x800FB118
    //SLL v0, t0, 3  //the 0x800FB0CC hook above modifies t0
    //SUBU v0, v0, t0

//when hud is spinning from pressing B, we need to offset the extra items slightly
//.org 0x800F6318
//J 

//when moving cursor left on items, makes it go to the furthest item (if team is on or off)
.org 0x800E3A04
    ADDIU fp, gp, -1

//.org 0x800F61D0
    //J newItemSpinCode
    //ADDIU v0, s3, 2
    //J 0x800F6318
    //J 0x800F6324

.org 0x800F3F0C
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, originalfunc_800F3F0C
    NOP   
    J newfunc_800F3F0C_107B2C_shared_board
    NOP
    originalfunc_800F3F0C:
    J originalfunc_800F3F0C_107B2C_shared_board
    NOP


//coin and scoring functions for teams
.org 0x800E1F48
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label0
    NOP
    J newShowPlayerCoinChange
    NOP
    label0:
    J originalShowPlayerCoinChange
    NOP


//PlayerHasItem
.org 0x800E4978
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label1
    NOP
    J newPlayerHasItem
    NOP
    label1:
    J originalPlayerHasItem
    NOP


//PlayerHasEmptyItemSlot
.org 0x800E49DC
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label2
    NOP
    J newPlayerHasEmptyItemSlot
    NOP
    label2:
    J originalPlayerHasEmptyItemSlot
    NOP

//FixUpPlayerItemSlots
.org 0x800E4A08
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label3
    NOP
    J newFixUpPlayerItemSlots
    NOP
    label3:
    J originalFixUpPlayerItemSlots
    NOP

//AdjustPlayerCoins
.org 0x800F21C0
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label4
    NOP
    J newAdjustPlayerCoins
    NOP
    label4:
    J originalAdjustPlayerCoins
    NOP

//PlayerHasCoins
.org 0x800F2230
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label5
    NOP
    J newPlayerHasCoins
    NOP
    label5:
    J originalPlayerHasCoins
    NOP

//team check is done in the hook for both of these
.org 0x800F3D70
    J newfunc_800F3D70_107990_shared_board
    NOP

.org 0x800F5BF4
    J newfunc_800F5BF4_109814_shared_board
    NOP


.org 0x800F39C0
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label6
    NOP
    J newfunc_800F39C0_1075E0_shared_board
    NOP
    label6:
    J originalfunc_800F39C0_1075E0_shared_board
    NOP

.org 0x800F3BD0
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label7
    NOP
    J newfunc_800F3BD0_1077F0_shared_board
    NOP
    label7:
    J originalfunc_800F3BD0_1077F0_shared_board
    NOP


.org 0x800F3E34
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label8
    NOP
    J newfunc_800F3E34_107A54_shared_board
    NOP
    label8:
    J originalfunc_800F3E34_107A54_shared_board
    NOP

.org 0x800F3FF4
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label9
    NOP
    J newfunc_800F3FF4_107C14_shared_board
    NOP
    label9:
    J originalfunc_800F3FF4_107C14_shared_board
    NOP

.org 0x800F6BC4
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label10
    NOP
    J newfunc_800F6BC4_10A7E4_shared_board
    NOP
    label10:
    J originalfunc_800F6BC4_10A7E4_shared_board
    NOP

.org 0x800F641C
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label24
    NOP
    J newfunc_800F641C_10A03C_shared_board
    NOP
    label24:
    J originalfunc_800F641C_10A03C_shared_board
    NOP

.org 0x800F3370
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label11
    NOP
    J newfunc_800F3370_106F90_shared_board
    NOP
    label11:
    J originalfunc_800F3370_106F90_shared_board
    NOP


.org 0x800F6ECC
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label12
    NOP
    J newfunc_800F6ECC_10AAEC_shared_board
    NOP
    label12:
    J originalfunc_800F6ECC_10AAEC_shared_board
    NOP



.org 0x800F6AD0
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label13
    NOP
    J newfunc_800F6AD0_10A6F0_shared_board
    NOP
    label13:
    J originalfunc_800F6AD0_10A6F0_shared_board
    NOP

.org 0x800F6E4C
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label14
    NOP
    J newfunc_800F6E4C_10AA6C_shared_board
    NOP
    label14:
    J originalfunc_800F6E4C_10AA6C_shared_board
    NOP


.org 0x800F5F98
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label15
    NOP
    J newfunc_800F5F98_109BB8_shared_board
    NOP
    label15:
    J originalfunc_800F5F98_109BB8_shared_board
    NOP

.org 0x800F59B4
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label16
    NOP
    J newfunc_800F59B4_1095D4_shared_board
    NOP
    label16:
    J originalfunc_800F59B4_1095D4_shared_board
    NOP

.org 0x800E35F8
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label17
    NOP
    J newfunc_800E35F8_F7218_shared_board
    NOP
    label17:
    J originalfunc_800E35F8_F7218_shared_board
    NOP

.org 0x800E3B14
    J teamCheck0Asm
    NOP

.org 0x800E3A20
    J teamCheck1Asm
    ADDU a0, s3, r0 //player index into a0

.org 0x800E3A78
    J teamCheck2Asm
    ADDU a0, s3, r0 //player index into a0

.org 0x800E3C88
    J teamCheck3Asm
    ADDU a0, s3, r0 //player index into a0

//items awarded after item minigames
//.org 0x800FE884
    //J teamCheck4Asm
    //NOP

.org 0x800FEA54
    J checkTeamCoinsForGameGuy
    NOP

.org 0x800FEA80
    JAL checkTeamCoinsForGameGuy2
    LB a0, 0x000F (s4) //current player index to a0
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

.org 0x800FEACC
    J checkTeamCoinsForGameGuy3
    NOP

.org 0x800FEAA8
    J checkTeamCoinsForGameGuy4
    NOP

.org 0x800FEAA8
    JAL GameGuyTakePlayerCoinsChangeHook
    LB a0, 0x000F (s4)
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP
    NOP

.org 0x800F7610
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label18
    NOP
    J newfunc_800F7610_10B230_shared_board
    NOP
    label18:
    J originalfunc_800F7610_10B230_shared_board
    NOP

.org 0x800F7BE8
    J getOneItemBabyBowser
    NOP

//for removing warp block from inventory
.org 0x800E2E4C
    J warpBlockCheck
    NOP

.org 0x800E2FF8
    J goldenMushroomCheck
    NOP

.org 0x800E30F8
    J booBellCheck
    NOP
    NOP

//.org 0x800E3210
    //J bowserSuitCheck
    //NOP
    //NOP

.org 0x800E3238
    J teamCheck13Asm
    NOP

.org 0x800E32A8
    J magicLampCheck
    NOP

.org 0x800E33B4
    J koopaKardCheck
    NOP
    NOP

.org 0x800E3178
    J booRepellentCheck
    NOP
    NOP

//for preventing your teammate being considered a duel opponent in last 5 turns of team mode
//.org 0x800FA818
    //LUI v0, hi(0x800D110C)
    //LBU v0, lo(0x800D110C) (v0)
    //ANDI v0, v0, 0x0030
    //BEQ v0, r0, label25
    //NOP
    //J newfunc_800FA818_10E438_shared_board
    //NOP
    //label25:
    //J originalfunc_800FA818_10E438_shared_board
    //NOP

.org 0x800E29E8
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label19
    NOP
    J newfunc_800E29E8_F6608_shared_board
    NOP
    label19:
    J originalfunc_800E29E8_F6608_shared_board
    NOP

.org 0x800F52C4
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label20
    NOP
    J newfunc_800F52C4_108EE4_shared_board
    NOP
    label20:
    J originalfunc_800F52C4_108EE4_shared_board
    NOP


.org 0x800E3B70
    JAL itemHandCursor3
    ADDIU a3, sp, 0x0014

.org 0x800E3944
    JAL itemHandCursor2
    ADDIU a3, sp, 0x0014

.org 0x800FE7F4
    JAL checkIfHideItemIcons
    ADDU s1, r0, r0

.org 0x800F5D44
    J newfunc_800F5D44_109964_shared_board
    NOP

//related to spawning of items above player's head when given items from a question
//TODO: by sheer chance, a0 happens to be the player index in this instance. probably shouldn't rely on this...
.org 0x800F76F0
    JAL GetTeamCaptainCurrentIndex
    SW v0, 0x0034 (sp)

//for repositioning where items move to when you get them from a toad/baby bowser question
.org 0x800F773C
    J getItemFromItemSpaceQuestionHook2
    NOP

//another item removal check
//this hook sets t0 for the 0x800E2BA8 hook below it
.org 0x800E2B6C
    J teamCheck5Asm 
    NOP
    NOP
.org 0x800E2BA8
    ADDU a0, t0, r0


//another another item removal check
//this hook sets t0 for the 0x800E2BA8 hook below it
.org 0x800E2BEC
    J teamCheck7Asm 
    NOP
    NOP
.org 0x800E2C28
    ADDU a0, t0, r0

//award star to 1st player on current player's team from hidden star block
//this hook sets t0 for the 0x800DDAE8 hook below it
.org 0x800DDAB4
    J teamCheck9Asm 
    NOP
    NOP
.org 0x800DDAE8
    ADDU v1, t0, r0

/* F7720 800E3B00 28420003 */  //slti       $v0, $v0, 0x3
.org 0x800E3B00
    SLT v0, v0, gp

.org 0x800E5870
    JAL CustomMinigameSetCheck
    NOP

.org 0x800F7F7C
    LUI v0, hi(mp3_gPlayers)
    LBU v0, lo(mp3_gPlayers + 0x4) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label21
    NOP
    J newfunc_800F7F7C_10BB9C_shared_board
    NOP
    label21:
    J originalfunc_800F7F7C_10BB9C_shared_board
    NOP

.org 0x800F7F30
    LUI v0, hi(mp3_gPlayers)
    LBU v0, lo(mp3_gPlayers + 0x4) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label22
    NOP
    J newfunc_800F7F30_10BB50_shared_board
    NOP
    label22:
    J originalfunc_800F7F30_10BB50_shared_board
    NOP

.org 0x800F7D4C
    LUI v0, hi(0x800D110C)
    LBU v0, lo(0x800D110C) (v0)
    ANDI v0, v0, 0x0030
    BEQ v0, r0, label23
    NOP
    J newfunc_800F7D4C_10B96C_shared_board
    NOP
    label23:
    J originalfunc_800F7D4C_10B96C_shared_board
    NOP

//extend "all items you can carry" random item generation from 3 -> 5 on team mode
.org 0x800F754C
    SLT v0, s0, gp

.org 0x800FE884
    //v0 holds empty slot currently
    J GiveTeamCaptainMinigameItem2
    ADDU t0, v0, r0 //store open item slot in t0 for other hook (at 0x800FE8AC)

.org 0x800FE8AC
    J GiveTeamCaptainMinigameItem3
    LBU v0, 0x1111 (v0) //item to give player

.org 0x800E2D0C
    J duelingGloveCheck
    NOP

.org 0x800EC590
    J newfunc_800EC590_1001B0_shared_board
    NOP

//.org 0x800F9D1C
    //LUI v0, hi(0x800D110C)
    //LBU v0, lo(0x800D110C) (v0)
    //ANDI v0, v0, 0x0030
    //BEQ v0, r0, label26
    //NOP
    //J newfunc_800F9D1C_10D93C_shared_board
    //NOP
    //label26:
    //J originalfunc_800F9D1C_10D93C_shared_board
    //NOP

.org 0x800DE260
    J hiddenItemBlockCheck
    NOP

.org 0x800EC4A4 //replaces a message id with a custom message already in ram
    JAL messageReplacementCheck
    ADDIU a3, r0, 0xFFFF

//801067B8 stores players starting flags (0x04)