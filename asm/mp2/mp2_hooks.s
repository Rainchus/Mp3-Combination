mp2_osEPiRawStartDmaHook:
    ADDIU sp, sp, -0x28 //restore from hook
    SW s0, 0x0010 (sp) //restore from hook

    LI t0, 0x2000000
    ADDU a2, a2, t0

    J 0x8009D958
     NOP