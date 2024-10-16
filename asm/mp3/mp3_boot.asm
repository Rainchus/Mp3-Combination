//mp3
//rom 0x115CE8 ram pointer to 4p minigames
.orga 0x115CE8
.word new4PMinigameListNormalMp3
.word new1v3MinigameListNormalMp3
.word new2v2MinigameListNormalMp3
.word newItemMinigameListNormalMp3
.word newBattleMinigameListNormalMp3

.word new4PMinigameListEasyMp3
.word new1v3MinigameListEasyMp3
.word new2v2MinigameListEasyMp3
.word newItemMinigameListEasyMp3
.word newBattleMinigameListEasyMp3

//advanced homebrew rom header
.orga 0x34
.byte 0x00 //p1
.byte 0x00 //p2
.byte 0x00 //p3
.byte 0x00 //p4

.orga 0x3C //for emualtors to know to use advanced header
.ascii "ED"

.orga 0x3F //set save type of game to 16K eeprom
.byte 0x01

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

//.org 0x8000C2A8 //remove save type check assert
//NOP

//.org 0x8000C2C0 //remove another save type check assert
//NOP