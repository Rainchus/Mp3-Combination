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
