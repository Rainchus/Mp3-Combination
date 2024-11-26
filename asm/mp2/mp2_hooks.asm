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

//this fixes a crash when loading back into a mp2 board...not sure what's going on here
.org 0x800654C8
    LUI at, 0x800E
    JAL mp2_Unk_Camera_Function
    LWC1 f12, 0x1F84 (at)