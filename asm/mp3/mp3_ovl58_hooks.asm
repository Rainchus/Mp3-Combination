.headersize 0x80105EE0 - 0x3D7690
.org 0x80105EE0
//overwrite D_80105EE0_3D7690_name_58 to point to our functions

.word 0, mp3_BootLogosEntryFunc
.word 1, mp3_BootLogosEntryFunc
.word -1, 0