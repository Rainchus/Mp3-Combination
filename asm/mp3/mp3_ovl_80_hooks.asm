.headersize 0x800D6B70 - 0xEA790
.org 0x800E3A04 //when moving cursor left on items, makes it go to the furthest item
    ADDIU fp, gp, -1

//? no notes on what this does?
.org 0x800E3B00
    SLT v0, v0, gp //slti       $v0, $v0, 0x3

//extend "all items you can carry" random item generation from 3 -> 5 on team mode
.org 0x800F754C
    SLT v0, s0, gp

.org 0x800F4190 //hook setup of sprites on board load for easily adding logic (such as 3 or 5 items like it does currently)
    J func_800F4190_107DB0_shared_board
    NOP

.org 0x800F6BC4 //handles 3 or 5 items depending on value of GP register
    J func_800F6BC4_10A7E4_shared_board
    NOP

.org 0x800F3400
    J newfunc_800F3400_107020_shared_board
    NOP

.org 0x800F3D70
    J newfunc_800F3D70_107990_shared_board
    NOP

.org 0x800F3FF4
    J newfunc_800F3FF4_107C14_shared_board
    NOP

.org 0x800F6ECC
    J newfunc_800F6ECC_10AAEC_shared_board
    NOP

.org 0x800F5F98
    J newfunc_800F5F98_109BB8_shared_board
    NOP

.org 0x800F7610
    J newfunc_800F7610_10B230_shared_board
    NOP

.org 0x800F7F30
    J newfunc_800F7F30_10BB50_shared_board
    NOP

.org 0x800F7D4C
    J newfunc_800F7D4C_10B96C_shared_board
    NOP

.org 0x800F7F7C
    J newfunc_800F7F7C_10BB9C_shared_board
    NOP

.org 0x800E4978
    J newPlayerHasItem
    NOP

.org 0x800E4A08
    J newFixUpPlayerItemSlots
    NOP

.org 0x800F6E4C
    J newfunc_800F6E4C_10AA6C_shared_board
    NOP

.org 0x800F6AD0
    J newfunc_800F6AD0_10A6F0_shared_board
    NOP

