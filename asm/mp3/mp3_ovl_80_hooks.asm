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


//.org 0x800F5D44
    //function is small, need to do team check in C code
    //J newfunc_800F5D44_109964_shared_board
    //NOP

.org 0x800F5BF4
    J newfunc_800F5BF4_109814_shared_board
    NOP

//.org 0xfunc_800F59B4_1095D4_shared_board
    //J newfunc_800F59B4_1095D4_shared_board
    //NOP

//801067B8 stores players starting flags (0x04)