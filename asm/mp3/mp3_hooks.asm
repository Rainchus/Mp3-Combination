//mp3
.org 0x80048128
J LoadOverlayHook_Mp3
NOP

.org 0x8000E658
JAL checkIfLoadingFromMp2Minigame
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
    ORI v0, r0, 1 //always display names of minigames (remove "???" from appearing)

.org 0x800DFFD4
    J getNewMinigameString1
    NOP

.org 0x800DFE7C
    J checkIfMinigameIndexIsBlacklisted
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

//patch a bunch of LB -> LBU
.org 0x800DFEAC
    LBU v1, 0x2C08 (v1)

.org 0x800DFEB8
    LBU v0, 0x2C08 (v0)

.org 0x800DFF1C
    LBU a1, 0x2C08 (a1)

.org 0x800DFF60
    LBU v1, 0x2C08 (v1)

.org 0x800DFFC0
    LBU a1, 0x2C08 (a1)

.org 0x800DFFE8
    LBU v0, 0x2C08 (v0)

.org 0x800DF468
    LBU a1, 0x2C08 (a1)

.org 0x800DF690
    LBU a0, 0x2C08 (a0)

//there is an LB here that needs to be patched, but patching it might cause issues
//because there is a BLTZ check
.org 0x800FEF60
    JAL CustomFuncTest
    NOP

//mp3 load minigame index and short after converts to overlay id
.headersize 0x80105A60 - 0x4DEC20
.org 0x80105A60
    J setCustomMinigameIndex
    NOP
    NOP
