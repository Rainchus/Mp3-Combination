NegativeCheck:
    JAL 0x8004EE18
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

mp3_setForeignMinigameIndex:
    LUI at, 0x800D
    SB a0, 0xD068 (at) //set mp3_GwSystem.minigame_index
    LI t0, ForeignMinigameIndexToLoad
    JR RA
     SW a0, 0x0000 (t0) //set ForeignMinigameIndexToLoad

mp3_PushItemCountToGP:
    JR RA
    DADDU gp, a0, r0

mp3_GetItemCount:
    JR RA
    DADDU v0, r0, gp
