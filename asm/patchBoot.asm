//mp3
.headersize 0x7FFFF400 //ran once on boot
.org 0x80000400
    LUI t0, 0x800B
    ADDIU t0, t0, 0x8AF0
    LUI t1, 0x0003
    ADDIU t1, t1, 0xE080
    mp3_bss_clear_loop:
    SD r0, 0x0000 (t0)
    ADDI t1, t1, 0xFFF8
    BNEZ t1, mp3_bss_clear_loop
    ADDI t0, t0, 0x0008

    LUI sp, 0x800D
    ADDIU sp, sp, 0x300
    ADDU a0, r0, r0
    LI a1, 0x1EFDA80
    //these ram symbols are defined in main.asm
    LI a2, PAYLOAD_START_RAM
    LI a3, PAYLOAD_END_RAM - PAYLOAD_START_RAM
    JAL osPiRawStartDma
    NOP

//mp3
.org 0x80048128
J LoadOverlayHook_Mp3
NOP

//mp2
.headersize 0x7DFFF400 //ROM Addr of combination rom, 0x3EFDB00
.org 0x8009D950
J mp2_osEPiRawStartDmaHook
NOP

//mp2
.org 0x80018B30
J LoadOverlayHook_Mp2
NOP

//mp2
.org 0x8001AD6C //save file check ASSERT. TODO: fix this being needed
NOP