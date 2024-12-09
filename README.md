# PLAYING
1) This creates 2 files. One is mario parties 3 and 2 combined (for use on console). The other is mario parties 3, 2, and 1 combined (for use on emulator or flashcarts that can load 96MB roms)</br>
2) Download the `patcher.zip` file from the [releases](https://github.com/Rainchus/Mp3-Combination/releases) tab and extract it to a folder.</br>
3) Now obtain mario party 3, 2, and 1 US roms, and place them into the `roms/` folder</br>
4) If you are on windows, you can just run `patcher.exe`, which will output `mp3-mp2-combo.z64` (if mario party 1 is included, `mp3-mp2-mp1-combo.z64` will also be created).</br>
If you are on mac, you can run `python patcher_macOS.py` which will output the combined, but unmodded roms named `mp3-mp2-base.z64` and `mp3-mp2-mp1-base.z64`. Then you can go to [here](https://hack64.net/tools/patcher.php)
to patch the bps file onto the base roms. (So `mp3-mp2-combo.bps` should be applied to `mp3-mp2-base.z64`, and `mp3-mp2-mp1-combo.bps` should be applied to `mp3-mp2-mp1-base.z64`)</br>
5) In your emulator you will need to make sure the expansion pak is on (8MB of RAM)</br>
6) If on project64, you need to set the save type to `16kbit eeprom`</br>

# KNOWN ISSUES
1) Waluigi and Daisy are unselectable (they dont exist in mp1/mp2, so they will crash if attempted to be loaded)</br>
2) If you turn off too many minigames, the game *will* softlock as it'll fail to populate the minigame wheel</br>

# BUILDING
Follow this to set up armips
https://hack64.net/Thread-Importing-C-Code-Into-SM64-Using-n64chain-and-armips

After armips is set up, clone this repo

1) Copy a big endian mario party 1 rom named `mp1.z64` to `rom/mp1.z64`</br>
2) Copy a big endian mario party 2 rom named `mp2.z64` to `rom/mp2.z64`</br>
3) Copy a big endian mario party 3 rom named `mp3.z64` to `rom/mp3.z64`</br>
4) Run `python ./initial_pack_mainfs.py` to repack custom images into mario party 3</br>
From this point on, calling `python ./initial_pack_mainfs.py` is only required if more images are added.</br>
5) Now you can run `python ./configure.py` with or without the `-mp1` flag depending on if you want mario party 1 to be built in the mod
6) Run `ninja` to build the project, which will output to `rom/mp3-mp2.mod.z64` or `rom/mp3-mp2-mp1.mod.z64`</br>
