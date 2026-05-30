mp2_osEPiRawStartDmaHook:
    ADDIU sp, sp, -0x28 //restore from hook
    SW s0, 0x0010 (sp) //restore from hook

    LI t0, 0x2000000
    ADDU a2, a2, t0

    J 0x8009D958
     NOP


newItemMinigameLoadCode:
    //use global minigame IDs for item minigames
    LUI at, hi(mp2ItemMinigameCombinedIDs)
    ADDU at, at, v0
    LBU v0, lo(mp2ItemMinigameCombinedIDs) (at)
    SH v0, 0x0020 (s7) //restore from hook (stores minigame index)
    LI at, ForeignMinigameIndexToLoad
    SB v0, 0x0000 (at) //store to ForeignMinigameIndexToLoad
    J 0x80066440
    ADDIU v0, r0, 0x000D //restore from hook


resetBattleCoinsAndSetStateE:
    LI t0, mp2_BattleMinigameCoins
    SH r0, 0x0000 (t0) //reset coins back to zero after they have been read and are no longer needed (helps with combo logic)
    
    LI t0, mp2_D_800E1F8C_E2B8C //this would already be 0xE after a mp3 battle minigame
    LI t1, 0xE 
    SW t1, 0x0000 (t0) //set MBMain state variable to 0xE which is normally what happens after a battle minigame

    LI t0, mp2_D_800CC210_CCE10
    LI t1, 0x3faaaaa6 //1.33f
    JR RA
    SW t1, 0x0000 (t0) //set camera value to 1.33f

    
mp2_drawDebugASM:
    JAL mp2_drawDebug
    NOP
    LUI v0, 0x800D
    J 0x800775F8
    LHU v0, 0xD410 (v0) //load debug drawing bool