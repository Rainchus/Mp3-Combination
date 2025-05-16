.headersize 0x80102D30 - 0x36DED0 - 0x02000000
//overwrite D_80102D30_36DED0_BootLogos to point to our functions
.org 0x80102D30

.halfword 0, 0
.word mp2_BootLogosEntryFunc

.halfword 1, 0
.word mp2_BootLogosEntryFunc

.halfword -1, 0
.word 0