.headersize 0x80105EE0 - 0x3D7690
.org 0x80105EE0
//overwrite D_80105EE0_3D7690_name_58 to point to our functions

.halfword 0, 0
.word mp3_BootLogosEntryFunc

.halfword 1, 0
.word func_80105ACC_3D727C_name_58

.halfword -1, 0
.word 0