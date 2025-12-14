# this really shouldn't be neccessary, but somewhere there's a headersize and ram combo that is writing -
# into mp1's rom space. since this is only used when building mp3-mp2, we can just trim the file
filename = 'rom/mp3-mp2.mod.z64'
offset = 0x4000000
with open(filename, 'rb+') as f:
    f.truncate(offset)
print(f"File '{filename}' truncated to {offset} bytes.")

