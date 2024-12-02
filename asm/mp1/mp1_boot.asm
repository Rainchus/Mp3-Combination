//mp1
.headersize 0x7BFFF400
.org 0x80090300
    J mp1_osEPiRawStartDmaHook
    NOP

//.org 0x8005B748
    //JAL 0x800BB6A4 //set up crash screen
    //NOP
    //J mp1_prevCode
    //NOP