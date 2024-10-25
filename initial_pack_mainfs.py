#this must be run before using configure.py and ninja to build

import subprocess
import os

# Run the mpromtool.exe command
subprocess.run(['./mpromtool.exe', '-b', '-a', 'rom/mp3.z64', 'mp3_extract/', 'rom/mp3-temp.z64'], check=True)

# Path to the temporary ROM file
rom_path = 'rom/mp3-temp.z64'
target_size = 0x2000000  # Target size of 32 MB

# Pad the file with 0xFF if it's smaller than the target size
with open(rom_path, 'ab') as rom_file:
    current_size = rom_file.tell()  # Get the current file size
    if current_size < target_size:
        padding_needed = target_size - current_size
        rom_file.write(b'\xFF' * padding_needed)
        print(f'Padded {padding_needed} bytes to {rom_path}. New size is {target_size} bytes.')
    else:
        print(f'{rom_path} is already {current_size} bytes, no padding needed.')
