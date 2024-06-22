//mp3
.org 0x80048128
J LoadOverlayHook_Mp3
NOP

//mp3 file select overlay
.headersize 0x80109690 - 0x51A7D0
.org 0x80109690 //only allow use of 2 save files
ADDIU s0, r0, 0x0001

.org 0x8010969C //only allow use of 2 save files
SLTI v0, s0, 0x0002 //was SLTI v0, s0, 0x0003

//hook shared board overlay?
.headersize 0x800DFFA4 - 0xF3BC4
.org 0x800DFFA4
    NOP
    NOP
    ORI v0, r0, 1 //always display names of minigames

.org 0x800DFFD4
    J getNewMinigameString1
    NOP

.org 0x800DF47C //display minigame name index when chosen
    J getNewMinigameString2
    NOP

.org 0x800DFFF0
    LUI a1, hi(unkFontTable)
    ADDU a1, a1, v0
    LBU a1, lo(unkFontTable) (a1)

.org 0x800DFE60 //new normal minigame list maxes
    LUI v0, hi(newCategoryAmountsNormal)
    ADDU v0, v0, s2
    LBU v0, lo(newCategoryAmountsNormal) (v0)

//mp3 load minigame index and short after converts to overlay id
.headersize 0x80105A60 - 0x4DEC20
.org 0x80105A60
    J setCustomMinigameIndex
    NOP
    NOP
