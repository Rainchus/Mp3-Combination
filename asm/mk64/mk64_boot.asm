.headersize 0x80000400 - 0x1000 - 0x06000000
.org 0x800d3090
    J mk64_osEPiRawStartDmaHook
    NOP

.org 0x800cdc30
    J mk64_osPiStartDmaHook
    NOP

.org 0x80091BD0
    NOP //remove jal load_save_data (causes crash because it has mario party data)

.org 0x80002714
    NOP //remove jal that reloads data for no reason

.org 0x80002754
    NOP //remove jal that reloads data for no reason

.org 0x8001C064
    NOP //remove jal that reloads data for no reason


//ROM patches for mk64...
//im too lazy to find the ram addresses because i was given this code like this
//this prevents reloading data that doesn't need to be reloaded, saving 6 whole seconds on boot
//tf is this game's coding

.headersize 0
.org 0x060B51E0
jr RA
NOP
.org 0x060B5270
jr RA
NOP
.org 0x060B619C
jr RA
NOP
.org 0x060B6548
jr RA
NOP
.org 0x060B5610
jr RA
NOP


//set the headersize back correctly
//load course on boot if frame counter is 2
.headersize 0x800942D0 - 0x94ED0 - 0x06000000
.org 0x80094658
    J checkCourseLoadFromBoot

//.org 0x8000043C
//.word 1