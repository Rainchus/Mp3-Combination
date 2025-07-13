//mp1
mp1_osEPiRawStartDmaHook:
    ADDIU sp, sp, -0x28
    SW s0, 0x0010 (sp)

    LI t0, 0x4000000
    ADDU a2, a2, t0

    J 0x80090308
     NOP