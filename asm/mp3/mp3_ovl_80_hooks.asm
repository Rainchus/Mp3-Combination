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

.org 0x800FE24C
    J checkColorSetAsm
    LBU a1, 0x001C (s2)

.org 0x800FCD28
    J checkColorSetAsm2
    ADDU a0, s1, r0