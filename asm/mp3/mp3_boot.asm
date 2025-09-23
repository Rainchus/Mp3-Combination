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

//advanced homebrew rom header
.orga 0x34
.byte 0x00 //p1
.byte 0x00 //p2
.byte 0x00 //p3
.byte 0x00 //p4

.orga 0x3C //for emualtors to know to use advanced header
.ascii "ED"

.orga 0x3F //set save type of game to 16K eeprom
.byte 0x20

//store the starting rom addresses of mp2 and mp3 in the rom header's unused space
//this is used by partyplanner64 to know where the roms start, and -
//it's also used by the patcher to grab the dynamic rom address from the .bps file
//We need to do this because to patch, the user just supplies the 3 roms with no way to know the start rom addr of each game
//Therefore, by this being the first thing we patch in the bps since it's at 0x18 in the rom, it's easy to find in the .bps -
//and then create the combined rom from that, before patching the combo code in
.orga 0x18
//dyanmic rom addresses
//.word ROM_START + (PAYLOAD_END_RAM - PAYLOAD_START_RAM) //ROM_END (mp2 rom start)
//.word ROM_START + (PAYLOAD_END_RAM - PAYLOAD_START_RAM) + 0x2000000 //ROM_END (mp1 rom start)

//hardcoded from now, update to be dynamic later
.word 0x2000000 //mp2 rom start
.word 0x4000000 //mp1 rom start

//overwrite ovl_7E (it's a blank overlay) rom start and end in ovltbl (for partyplanner purposes)
.orga 0x980AC
    .word ROM_START
    .word ROM_START + (PAYLOAD_END_RAM - PAYLOAD_START_RAM) //ROM_END


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
    //SW t2, 0x0000 (t0) //fake warm boot (does this actually work on console?)

    //else, is cold boot
    ADDU a0, r0, r0
    LI a1, ROM_START
    //these ram symbols are defined in main.asm
    LI a2, PAYLOAD_START_RAM
    LI a3, PAYLOAD_END_RAM - PAYLOAD_START_RAM
    JAL osPiRawStartDma
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

//when swapping to a game (mp3 in this instance) stuff would draw for a frame when it shouldn't
//this makes it so that the game is a black screen 1 frame longer on boot, fixing the problem
.org 0x8000EE84
    LW	V0, 0xFD14 (S4)
    SLTI v1, v0, 0x0002
    BNEZ v1, 0x8000EED8

//used for experimenting with drawing 2d objects to the screen
//.org 0x8001BC80
    //JAL drawFonts2
    //LW a0, 0x1FF4 (a0)

//used for experimenting with drawing 2d objects to the screen behind the "Wipe" overlay that happens
.org 0x8001BC74
    JAL drawFonts3
    SW s0, 0x0004 (v0)

//.org 0x8000C2A8 //remove save type check assert
    //JAL InvalidEepDetected
    //NOP

.org 0x8000C2C0 //remove another save type check assert
    JAL InvalidEepDetected
    NOP

.org 0x8000C24C
    JAL EepromCheckAsmHook
    NOP

.org 0x8000E7B8
    mp3_mainThreadCopy:
    ADDIU sp, sp, -0x18
    SW ra, 0x0010 (sp)
    JAL 0x80099424 //crash screen main binary
    NOP
    mp3_threadInfiniteLoop:
    JAL 0x8004F074
    NOP
    JAL 0x8000B16C
    NOP
    JAL 0x8000BA30
    NOP
    JAL 0x80014A3C
    ORI a0, r0, 2
    LUI a0, 0x800D
    ADDIU a0, a0, 0xCF38
    JAL 0x8001B0B4
    ADDIU a1, r0, 2
    J mp3_threadInfiniteLoop
    NOP
