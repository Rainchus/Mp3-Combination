//mp2
.headersize 0x7DFFF400 //ROM Addr of combination rom, 0x3EFDB00
.org 0x8009D950
    J mp2_osEPiRawStartDmaHook
    NOP

//mp2 code that runs right after minigame selection
//8006399C

//mp2 starts tear down of board play and starts a minigame
//8006399C

//mp2 s8 800CCC14 is if skip minigame explanations

//mp2
.org 0x80018B30
    J LoadOverlayHook_Mp2
    NOP

.org 0x8001B014
    J mp2_func_8001B014_1BC14_New
    NOP

//.org 0x8001AD60
//if this fails, the game hangs
//it originally checks for a 4Kbit eeprom, but we want to check for 16Kbit since mp3 uses that
//ADDIU v1, r0, 0x0002 //set eeprom to 16Kbit check instead of 4Kbit check

//reimplement functions for mp2 eeprom
//mp3 has 2 save files, and will use file slots 1 and 2.
//slot 3 will be removed from mp3 to make room for mp2's save file
.org 0x8001ACD0 //replace with decompiled version of function
    J GetEepType
    NOP

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

//hook an mp2 looping thread to init a crash screen on its initialization
.headersize 0x7DFFF400 //ROM Addr of combination rom
.org 0x8001C81C
    mainThreadCopy:
        ADDIU sp, sp, -0x18
        SW ra, 0x0010 (sp)
        JAL 0x800C13F0 //crash_screen_init
        NOP
        threadInfiniteLoop:
        JAL 0x8007DA44
        NOP
        JAL 0x8002FB6C
        NOP
        JAL 0x80020E70
        NOP
        LUI a0, 0x0200
        LUI a1, 0x003D
        JAL 0x800295D4
        ORI a1, a1, 0x0800
        JAL 0x8007C668
        NOP
        J threadInfiniteLoop
        NOP

.org 0x8001C730 //check if we should change the overlay loaded in mp2's boot sequence
    JAL mp2BootOverlaySwapCheck
    NOP
