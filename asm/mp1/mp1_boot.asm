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