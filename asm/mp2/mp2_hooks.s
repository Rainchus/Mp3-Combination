mp2_osEPiRawStartDmaHook:
    ADDIU sp, sp, -0x28 //restore from hook
    SW s0, 0x0010 (sp) //restore from hook

    LI t0, 0x2000000
    ADDU a2, a2, t0

    J 0x8009D958
     NOP


newItemMinigameLoadCode:
    //use global minigame IDs for item minigames
    LUI at, hi(D_800CCCFC_CD8FC)
    ADDU at, at, v0
    LBU v0, lo(D_800CCCFC_CD8FC) (at)
    SH v0, 0x0020 (s7) //restore from hook
    LI at, ForeignMinigameIndexToLoad
    SW v0, 0x0000 (at) //store to ForeignMinigameIndexToLoad
    J 0x80066440
    ADDIU v0, r0, 0x000D //restore from hook