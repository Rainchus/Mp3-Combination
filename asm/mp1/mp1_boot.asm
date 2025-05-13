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