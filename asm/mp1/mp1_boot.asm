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

.org 0x8005B748
    JAL 0x800BB6A4 //set up crash screen
    NOP
    J mp1_prevCode
    NOP

//when swapping to a game (mp1 in this instance) stuff would draw for a frame when it shouldn't
//this makes it so that the game is a black screen 1 frame longer on boot, fixing the problem
.org 0x8001AA14
    LW	V0, 0xFD2C (S5)
    SLTI v1, v0, 0x0002
    BNEZ v1, 0x8001AA38

.org 0x8007084C
    J mp1SetCpuDifficultyMod
    NOP
    