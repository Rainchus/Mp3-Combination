
//Automatically generated by configure.py, do not edit
.n64 // Let armips know we're coding for the N64 architecture
.open "rom/mp3-mp2.z64", "rom/mp3-mp2.mod.z64", 0 // Open the ROM file
.include "asm\mp2\mp2_boot.asm"
.include "asm\mp2\mp2_crash_screen_binary.asm"
.include "asm\mp2\mp2_symbols.asm"
.include "asm\mp2\ovl_00_hooks.asm"
.include "asm\mp3\mp3_boot.asm"
.include "asm\mp3\mp3_hooks.asm"
.include "asm\mp3\mp3_symbols.asm"

.headersize 0x7E502580
.org 0x80400000
PAYLOAD_START_RAM:
.include "asm\combo.s"
.include "asm\hooked_code.s"
.importobj "obj\boot.o"
.importobj "obj\cache.o"
.importobj "obj\main.o"
.importobj "obj\mp2_hooks.o"
.importobj "obj\mp3_minigame_wheel.o"
.importobj "obj\system.o"
.importobj "obj\mp2\ovl_00_Debug\ovl_00_main.o"

.align 8
PAYLOAD_END_RAM:
.close //close file
