//mp1
.orga 0xCB938 + 0x04000000
.word new4PMinigameListNormalMp1
.word new1v3MinigameListNormalMp1
.word new2v2MinigameListNormalMp1
.word new1PMinigameListNormalMp1

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

//when swapping to a game (mp1 in this instance) stuff would draw for a few frames when it shouldn't
//this makes it so that the game is a black screen 12 frames longer on boot, fixing the problem
.org 0x8001AA14
    LW	V0, 0xFD2C (S5)
    SLTI v1, v0, 0x000C
    BNEZ v1, 0x8001AA38