# PLAYING
1) Download the `patcher.zip` file from the [releases](https://github.com/Rainchus/Mp3-Combination/releases) tab and extract it to a folder.</br>
2) Now obtain mario party 3, 2, and 1 US roms</br>
3) Name them `mp3.z64`, `mp2.z64`, and `mp1.z64` respecitvely, and place them into the `roms/` folder extracted from `patcher.zip`</br>
4) Now run `patcher.exe`, which will output the modded rom to mp3-mp2-mp1-combo.z64</br>
5) In your emulator you will need to make sure the expansion pak is on (8MB of RAM)</br>
6) Also if on project64, you need to set the save type to `16kbit eeprom`</br>

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
