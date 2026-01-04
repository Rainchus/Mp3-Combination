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

alwaysSetBookOpen:
    LUI at, 0x8011
    ADDIU at, at, 0xD408 //8010D408
    ORI v0, r0, 1 //also used to skip current 8010D408 read as we always make it 1
    J 0x80105DF8
    SB v0, 0x0000 (at) //set book always open

/*
example of replacing the default message window RGB value
originalWindowRGB:
.byte 0x40, 0x20, 0xB0 //original RGB values of messages boxes

newWindowRGB:
.byte 0x40, 0x80, 0x20 //new RGB values to set

.align 4
checkSetWindowRGBArgs: //hook to this inserted at 0x8005FBF8
    ADDIU sp, sp, -0x30
    SW ra, 0x002C (sp)

    LI t0, originalWindowRGB
    LBU t1, 0x0000 (t0)
    BNE a1, t1, exitCheck
     LBU t2, 0x0001 (t0)
    BNE a2, t2, exitCheck
     LBU t3, 0x0002 (t0)
    BNE a3, t3, exitCheck
     LI t0, newWindowRGB
    //load new values
    LBU a1, 0x0000 (t0)
    LBU a2, 0x0001 (t0)
    LBU a3, 0x0002 (t0)
    exitCheck:
    J 0x8005FC00
    NOP
*/