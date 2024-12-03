.headersize 0x7BFFF400
.org 0x80019270
    J mp1_GetEepType_New
    NOP

.org 0x8005AFC8
    J mp1_func_8005AFC8_New
    NOP

.org 0x80019438
    J mp1_func_80019438_New
    NOP

.org 0x80019540
    J mp1_func_80019540_New
    NOP

.org 0x8001758C
    J rand8_Shared
    NOP

//.org 0x80043A80
    //JAL mp1_GetRandomMinigame

//set category amounts for expanded minigame lists
.org 0x80043A8C
    LUI v1, hi(newCategoryAmountsNormalMp1)
    ADDU v1, v1, s2
    LBU v1, lo(newCategoryAmountsNormalMp1) (v1)

//extend minigame font color to support more minigames
.org 0x80043CC8
    LUI a1, hi(minigameTextColor)
    ADDU a1, a1, v0
    LBU a1, lo(minigameTextColor) (a1)

//poke some minigame wheel related loads from LB -> LBU
.org 0x80043AE0
    LBU v1, 0x6454 (v1)

.org 0x80043AEC
    LBU v0, 0x6454 (v0)

.org 0x80043B24
    LBU a0, 0x6454 (a0)

.org 0x80043B64
    LBU v1, 0x6454 (v1)

.org 0x80043B84
    LBU v0, 0x6454 (v0)

.org 0x80043CA0
    LBU a1, 0x6454 (a1)

.org 0x80043CC0
    LBU v0, 0x6454 (v0)

.org 0x800430E8
    LBU a1, 0x6454 (a1)

.org 0x800432EC
    LBU a0, 0x6454 (a0)
    //remove s8 cast
    NOP
    NOP
    NOP //remove the -1

//prev minigame load list needs to also be unsigned
.org 0x80043B70
    LBU v0, 0x6438 (v0)

//get minigame string from lookup table if applicable
.org 0x80043CB0
    JAL mp1_GetNewMinigameString
    ADDIU a3, r0, 0x0004

.org 0x80043100
    JAL mp1_GetNewMinigameString
    ADDIU a3, r0, 0x0004

.headersize 0x800F665C - 0x42DB31C
.org 0x800F6660
    JAL mp1_getMinigameExplanationOverlay
    NOP
    //NOPs for clarity (code that is skipped)
    NOP
    NOP
    NOP

