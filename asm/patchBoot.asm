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

//mp3 file select overlay
.headersize 0x80109690 - 0x51A7D0
.org 0x80109690 //only allow use of 2 save files
ADDIU s0, r0, 0x0001

.org 0x8010969C //only allow use of 2 save files
SLTI v0, s0, 0x0002 //was SLTI v0, s0, 0x0003

//mp2
.headersize 0x7DFFF400 //ROM Addr of combination rom, 0x3EFDB00
.org 0x8009D950
J mp2_osEPiRawStartDmaHook
NOP

//mp2
.org 0x80018B30
J LoadOverlayHook_Mp2
NOP

.org 0x8001AD60
//if this fails, the game hangs
//it originally checks for a 4Kbit eeprom, but we want to check for 16Kbit since mp3 uses that
ADDIU v1, r0, 0x0002 //set eeprom to 16Kbit check instead of 4Kbit check

//mp2
//.org 0x8001AD6C //save file check ASSERT. TODO: fix this being needed
//NOP

//reimplement functions for mp2 eeprom
//mp3 has 2 save files, and will use file slots 1 and 2.
//slot 3 will be removed from mp3 to make room for mp2's save file
.org 0x8001ACD0 //replace with decompiled version of function
J GetEepType
NOP

//.org 0x8001AEDC
//J func_8001AEDC_1BADC
//NOP

.org 0x8001AF0C
J func_8001AF0C_1BB0C
NOP

.org 0x8001AFD8
J func_8001AFD8_1BBD8
NOP

.org 0x8001B014
J func_8001B014_1BC14
NOP

.org 0x8001B078
J func_8001B078_1BC78
NOP

.org 0x8001B0B4
J func_8001B0B4_1BCB4
NOP

.org 0x8001B0E8
J func_8001B0E8_1BCE8
NOP

.org 0x8001B114
J GetSaveFileChecksum
NOP

//mp2 checksum searching patches
//.headersize 0x8007DC50 - 0x207E850 //0x7E850
.org 0x8007DC50
J func_8007DC50_7E850
NOP

.org 0x80068720
J func_80068720_69320
NOP

.headersize 0x800DFFA4 - 0xF3BC4
.org 0x800DFFA4
NOP
NOP
ORI v0, r0, 1 //always display names of minigames

.org 0x800DFFD4
J getNewMinigameString1
NOP

.org 0x800DF47C //display minigame name index when chosen
J getNewMinigameString2
NOP

