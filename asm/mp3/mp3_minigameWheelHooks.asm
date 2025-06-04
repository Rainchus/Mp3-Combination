//hook shared board overlay (ovl 0x80)
.headersize 0x800DFFA4 - 0xF3BC4
.org 0x800DFFA4
    NOP
    NOP
    ORI v0, r0, 1 //always display names of minigames (remove "???" from appearing)

.org 0x800DFFD8
    JAL GetNewMinigameString1
    ADDIU a3, r0, 0x0004

.org 0x800DF480 //display minigame name index when chosen
    JAL GetNewMinigameString1
    ADDIU a3, r0, 0x0004

.org 0x800DFFF0
    LUI a1, hi(minigameTextColor)
    ADDU a1, a1, v0
    LBU a1, lo(minigameTextColor) (a1)

.org 0x800DFE60 //new normal minigame list maxes
    LUI v0, hi(newCategoryAmountsNormalMp3)
    ADDU v0, v0, s2
    LBU v0, lo(newCategoryAmountsNormalMp3) (v0)

//hack: on the last turn of mp3 boards in story mode, force only mp3 minigames
//.org 0x800DFE7C
    //J mp3LastTurnMinigameCheck
    //NOP

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

.org 0x800DFF24
    LBU v0, 0x0000 (v0) //previously played minigames list

//there is an LB here that needs to be patched, but patching it might cause issues -
//because there is a BLTZ check
.org 0x800FEF60
    JAL NegativeCheck
    NOP