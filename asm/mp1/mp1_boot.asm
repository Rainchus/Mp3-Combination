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

//.org 0x8005B748
    //JAL 0x800BB6A4 //set up crash screen
    //NOP
    //J mp1_prevCode
    //NOP

//remove checksum failed (TODO: fix the code to not need this)
//.org 0x8005B1D0
    //NOP