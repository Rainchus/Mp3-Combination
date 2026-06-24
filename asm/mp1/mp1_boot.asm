//mp1
.headersize 0x7BFFF400
.org 0x80090300
    J mp1_osEPiRawStartDmaHook
     NOP


//changes for moving the eep data offset in our combined eeprom
.org 0x80019270
    J mp1__InitEeprom
     NOP

//new eep offset + hudson header size
.org 0x80019540
    J mp1__ReadEeprom
     NOP

.org 0x80019438
    J mp1__WriteEeprom
     NOP

.org 0x8001758C
    J rand8_Shared
     NOP

.org 0x8004388C
    J func_8004388C
    NOP

.org 0x80059348
    J SetMinigameExplanation
    NOP
    NOP //NOP the last instruction of the function for clarity


//when minigame wheel stops on a minigame and highlights it, poke the string to display correctly
.org 0x80043100
    JAL SetHighlightedMinigameString

//when minigame wheel stops and indexes into an array for the string based on said minigame index
.org 0x800430E8
    LBU a1, 0x6454 (a1) //was LB a1, 0x6454 (a1) but we have more than 128 minigames, so this needs to be a u8

//make rng roll per frame in mp1
.org 0x8001A440
    JAL rand8_Shared
    NOP
    J	0x8001A430
    NOP

//when swapping to a game (mp1 in this instance) stuff would draw for a few frames when it shouldn't
//this makes it so that the game is a black screen 12 frames longer on boot, fixing the problem
//.org 0x8001AA14
    //LW	V0, 0xFD2C (S5)
    //SLTI v1, v0, 0x000C
    //BNEZ v1, 0x8001AA38