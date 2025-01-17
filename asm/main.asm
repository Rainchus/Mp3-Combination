
//Automatically generated by configure.py, do not edit
.n64 // Let armips know we're coding for the N64 architecture
.open "rom/mp3-mp2-mp1.z64", "rom/mp3-mp2-mp1.mod.z64", 0 // Open the ROM file
.include "rom_start.asm"
.include "asm\mp1\mp1_boot.asm"
.include "asm\mp1\mp1_boot_logos.asm"
.include "asm\mp1\mp1_crash_screen_binary.asm"
.include "asm\mp1\mp1_hooks.asm"
.include "asm\mp1\mp1_ovl_39_WariosBattleCanyon.asm"
.include "asm\mp1\mp1_ovl_46_BowserSpaceEvent.asm"
.include "asm\mp1\mp1_ovl_6A_AdventureModeSetup.asm"
.include "asm\mp1\mp1_ovl_7C.asm"
.include "asm\mp1\mp1_symbols.asm"
.include "asm\mp2\mp2_boot.asm"
.include "asm\mp2\mp2_boot_logos.asm"
.include "asm\mp2\mp2_crash_screen_binary.asm"
.include "asm\mp2\mp2_hooks.asm"
.include "asm\mp2\mp2_ovl_70_Results.asm"
.include "asm\mp2\mp2_symbols.asm"
.include "asm\mp3\mp3_boot.asm"
.include "asm\mp3\mp3_crash_screen_binary.asm"
.include "asm\mp3\mp3_hooks.asm"
.include "asm\mp3\mp3_ovl_00_hooks.asm"
.include "asm\mp3\mp3_ovl_48_hooks.asm"
.include "asm\mp3\mp3_ovl_50_Bowser_hooks.asm"
.include "asm\mp3\mp3_ovl_53.asm"
.include "asm\mp3\mp3_ovl_53_hooks.asm"
.include "asm\mp3\mp3_ovl_58_hooks.asm"
.include "asm\mp3\mp3_ovl_71_hooks.asm"
.include "asm\mp3\mp3_ovl_78_hooks.asm"
.include "asm\mp3\mp3_ovl_80_hooks.asm"
.include "asm\mp3\mp3_ovl_bootlogos.asm"
.include "asm\mp3\mp3_playerStructPatches.asm"
.include "asm\mp3\mp3_symbols.asm"
.include "asm\mp3\ovl_castlegrounds_hooks.asm"
.include "asm\mp3\ovl_starlift.asm"
.include "headersize.asm"
.include "asm\combo.s"
.include "asm\hooked_code.s"
.importobj "obj\cache.o"
.importobj "obj\initialSaveFileData.o"
.importobj "obj\main.o"
.importobj "obj\mp2_hooks.o"
.importobj "obj\mp2_minigame_wheel.o"
.importobj "obj\mp3_minigame_wheel.o"
.importobj "obj\switch.o"
.importobj "obj\system.o"
.importobj "obj\mp1\mp1_hooks.o"
.importobj "obj\mp1\ovl_39_WariosBattleCanyon\ovl_39_WariosBattleCanyon.o"
.importobj "obj\mp1\ovl_46_BowserSpaceEvent\mp1_ovl_46_BowserSpaceEvent.o"
.importobj "obj\mp1\ovl_66_BootLogos\ovl_66_BootLogos.o"
.importobj "obj\mp1\ovl_7C\ovl_7C_UnkResultsScene.o"
.importobj "obj\mp2\ovl_57_BootLogos\ovl_57_BootLogos.o"
.importobj "obj\mp2\ovl_70_Results\ovl_70_Results.o"
.importobj "obj\mp3\original_teams.o"
.importobj "obj\mp3\teams.o"
.importobj "obj\mp3\ovl_00_Debug\ovl_00_Debug.o"
.importobj "obj\mp3\ovl_53\ovl_53.o"
.importobj "obj\mp3\ovl_58_name_BootLogos\ovl_58_BootLogos.o"
.importobj "obj\mp3\ovl_78_StarLift\ovl_78_StarLift.o"

.align 8
PAYLOAD_END_RAM:
.close //close file
