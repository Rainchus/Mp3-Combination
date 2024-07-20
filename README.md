# BUILDING

Follow this to set up armips
https://hack64.net/Thread-Importing-C-Code-Into-SM64-Using-n64chain-and-armips

After armips is set up, clone this repo

Copy a big endian mario party 2 rom named `mp2.z64` to `rom/mp2.z64`</br>
Also copy a big endian mario party 3 rom named `mp3.z64` to `rom/mp3.z64`</br>
Run `python ./configure.py` to combine the roms and generate a ninja build file</br>
Run `ninja` to build the project, which will output to `rom/mp3-mp2.mod.z64`</br>
