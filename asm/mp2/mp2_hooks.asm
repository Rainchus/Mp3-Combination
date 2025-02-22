//mp2
.headersize 0x7DFFF400 //ROM Addr of combination rom, 0x3EFDB00
.org 0x8004AF78
    //LUI v0, hi(mp2_newCategoryAmounts)
    //ADDU v0, v0, s2
    //LBU v0, lo(mp2_newCategoryAmounts) (v0)

    LUI v0, hi(newCategoryAmountsNormalMp2)
    ADDU v0, v0, s2
    LBU v0, lo(newCategoryAmountsNormalMp2) (v0)
    
//patch a bunch of LB -> LBU
.org 0x8004AFC4
    LBU v1, 0xF6C0 (v1)

.org 0x8004AFD0
    LBU v0, 0xF6C0 (v0)

.org 0x8004B014
    LBU a0, 0xF6C0 (a0)

.org 0x8004B100
    LBU v1, 0xF6C0 (v1)

.org 0x8004B158
    LBU a1, 0xF6C0 (a1)

.org 0x8004B178
    LBU v0, 0xF6C0 (v0)

.org 0x8004A54C
    LBU a1, 0xF6C0 (a1)

.org 0x8004A7AC
    LBU a0, 0xF6C0 (a0)

.org 0x8004B168
    JAL mp2_GetNewMinigameString
    ADDIU a3, r0, 0x0004

.org 0x8004A564
    JAL mp2_GetNewMinigameString
    ADDIU a3, r0, 0x0004

.org 0x8004B180
    LUI a1, hi(minigameTextColor)
    ADDU a1, a1, v0
    LBU a1, lo(minigameTextColor) (a1)

.org 0x80063B20
    LUI a0, 0x8010
    JAL GetMp2ExplanationScreenIndex
    LH a0, 0x93C8 (a0)

//poke item minigame id to extended list
.org 0x8006642C
    LUI at, hi(mp2_itemMinigameList)
    ADDU at, at, v0
    LBU v0, lo(mp2_itemMinigameList) (at)

//this fixes a crash with the camera. normally, this gets initialized to 1.0f on -
//board load, but since we skip some of that, it's 0.0f and divides by zero, causing a crash
//manually set it to 1.0f
.org 0x800654C8
    LUI at, 0x800E
    JAL mp2_Unk_Camera_Function
    LWC1 f12, 0x1F84 (at)

//same thing again here
.org 0x80066DA8
    LUI at, 0x800E
    JAL mp2_Unk_Camera_Function
    LWC1 f12, 0x1F84 (at)

.org 0x80018AFC
    J rand8_Shared
    NOP

.org 0x800653E8
    JAL mp2_IfMidTurnMinigameCheckAsm2
    NOP

.org 0x80064C98
    J newfunc_80064C98_65898
    NOP

//writes the minigame index loaded to ForeignMinigameIndexToLoad for battle minigames
.org 0x80067E6C
    J newfunc_80067E6C_68A6C
    NOP
    NOP //nop last instruction in function for clarity