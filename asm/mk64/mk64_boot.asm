.headersize 0x80000400 - 0x1000 - 0x06000000
.org 0x800d3090
    J mk64_osEPiRawStartDmaHook
    NOP

.org 0x800cdc30
    J mk64_osPiStartDmaHook
    NOP

.org 0x80091BD0
    NOP //remove jal load_save_data (causes crash because it has mario party data)

//.org 0x8000043C
//.word 1