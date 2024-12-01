
//Automatically generated by configure.py, do not edit
.n64 // Let armips know we're coding for the N64 architecture
.open "rom/mp3-mp2-mp1.z64", "rom/mp3-mp2-mp1.mod.z64", 0 // Open the ROM file
.include "rom_start.asm"
.include "asm\mp1\mp1_boot.asm"
.include "asm\mp1\mp1_boot_logos.asm"
.include "asm\mp1\mp1_crash_screen.asm"
.include "asm\mp1\mp1_hooks.asm"
.include "asm\mp1\mp1_symbols.asm"
.include "asm\mp2\mp2_boot.asm"
.include "asm\mp2\mp2_boot_logos.asm"
.include "asm\mp2\mp2_crash_screen_binary.asm"
.include "asm\mp2\mp2_hooks.asm"
.include "asm\mp2\mp2_symbols.asm"
.include "asm\mp3\mp3_boot.asm"
.include "asm\mp3\mp3_hooks.asm"
.include "asm\mp3\mp3_ovl_00_hooks.asm"
.include "asm\mp3\mp3_ovl_58_hooks.asm"
.include "asm\mp3\mp3_ovl_bootlogos.asm"
.include "asm\mp3\mp3_symbols.asm"
.include "asm\mp3\ovl_castlegrounds_hooks.asm"
.include "asm\mp3\ovl_starlift.asm"
.include "headersize.asm"
.include "asm\combo.s"
.include "asm\hooked_code.s"
.importobj "obj\cache.o"
.importobj "obj\main.o"
.importobj "obj\mp2_hooks.o"
.importobj "obj\mp2_minigame_wheel.o"
.importobj "obj\mp3_minigame_wheel.o"
.importobj "obj\switch.o"
.importobj "obj\system.o"
.importobj "obj\mp1\mp1_hooks.o"
.importobj "obj\mp1\ovl_66_BootLogos\ovl_66_BootLogos.o"
.importobj "obj\mp2\ovl_57_BootLogos\ovl_57_BootLogos.o"
.importobj "obj\mp3\ovl_00_Debug\ovl_00_Debug.o"
.importobj "obj\mp3\ovl_58_name_BootLogos\ovl_58_BootLogos.o"

.align 8
PAYLOAD_END_RAM:
.close //close file
