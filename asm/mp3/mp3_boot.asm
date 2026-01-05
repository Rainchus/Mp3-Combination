//mp3
//rom 0x115CE8 ram pointer to 4p minigames
.orga 0x115CE8
.word new4PMinigameListNormalMp3
.word new1v3MinigameListNormalMp3
.word new2v2MinigameListNormalMp3
.word newItemMinigameListNormalMp3
.word newBattleMinigameListNormalMp3
.word newDuelMinigameListNormalMp3

.word new4PMinigameListEasyMp3
.word new1v3MinigameListEasyMp3
.word new2v2MinigameListEasyMp3
.word newItemMinigameListEasyMp3
.word newBattleMinigameListEasyMp3
.word newDuelMinigameListEasyMp3

.orga 0x20
.ascii "MarioPartyN64Combo  "

.orga 0x3F //set save type of game to 16K eeprom
.byte 0x20

.headersize 0x7FFFF400 //ran once on boot
.org 0x80000400
    //set up stack pointer
    LUI sp, 0x800D
    ADDIU sp, sp, 0x300

    //check if cold boot or warm boot to see if we should dma our code/data
    LI t0, 0x8000030C //osResetType
    LW s0, 0x0000 (t0)
    BNEZ s0, alreadyDMAed
     ORI t2, r0, 1
    
    //set to warm boot
    SW t2, 0x0000 (t0) //fake warm boot (does this actually work on console?)

    //else, is cold boot
    ADDU a0, r0, r0
    LI a1, ROM_START
    //these ram symbols are defined in main.asm
    LI a2, PAYLOAD_START_RAM
    LI a3, PAYLOAD_END_RAM - PAYLOAD_START_RAM
    JAL mp3_osPiRawStartDma
     NOP
    LI t0, 0xA4600010
    pi_loop:
    LW t1, 0x0000 (t0)
    ANDI t2, t1, 0x0001
    BNEZ t2, pi_loop
     NOP
    alreadyDMAed:
    JAL mp3_ClearBss
     ADDU a0, s0, r0

//when swapping to a game (mp3 in this instance) stuff would draw for a few frames when it shouldn't
//this makes it so that the game is a black screen 12 frames longer on boot, fixing the problem
.org 0x8000EE84
    LW	V0, 0xFD14 (S4)
    SLTI v1, v0, 0x000C
    BNEZ v1, 0x8000EED8

.org 0x8000B16C
    J rand8_Shared
     NOP

.org 0x8004FFB8 //only check file 1's checksum
    SLTI v0, s0, 0x0001 //was SLTI v0, s0, 0x0003

.org 0x8000C3F0 //only check file 1's checksum
    SLTI v0, v0, 0x0001 //SLTI v0, v0, 0x0003

.org 0x80035AB0
    J mp3_setForeignMinigameIndex
     NOP

/*
.org 0x8005FBF8
    J checkSetWindowRGBArgs
    NOP
*/

//used for experimenting with drawing 2d objects to the screen behind the "Wipe" overlay that happens
.org 0x8001BC74
    JAL drawFonts3
    SW s0, 0x0004 (v0)