import subprocess
import os
import shutil

# Path to the temporary ROM file
rom_path = 'rom/mp3-temp.z64'
target_size = 0x2000000  # Target size of 32 MB

# List of files to check and delete if they exist
files_to_delete = [
    'rom/mp3-mp2-mp1.mod.z64',
    'rom/mp3-mp2-mp1.z64',
    'rom/mp3-mp2.z64',
    'rom/mp3-temp.z64'
]

# Delete the files if they exist
for file_path in files_to_delete:
    if os.path.exists(file_path):
        os.remove(file_path)
        print(f'Deleted: {file_path}')
    else:
        print(f'File not found, skipping: {file_path}')

# Run the mpromtool.exe command to dump files
subprocess.run(['./mpromtool.exe', '-a', 'rom/mp3.z64', 'mp3_extract/'], check=True)

# Copy directories, subdirectories, and files from new_files to mp3_extract
source_dir = 'new_files'  # Source directory containing files to copy
destination_dir = 'mp3_extract'  # Destination directory

if os.path.exists(source_dir):
    shutil.copytree(source_dir, destination_dir, dirs_exist_ok=True)
    print(f'Copied files from {source_dir} to {destination_dir}.')
else:
    print(f'Source directory {source_dir} does not exist. Skipping copy.')

print(f"Repacking mainfs into {rom_path}")

# Run the mpromtool.exe command to repack everything
subprocess.run(['./mpromtool.exe', '-b', '-a', 'rom/mp3.z64', 'mp3_extract/', 'rom/mp3-temp.z64'], check=True)

# Get the current size of the ROM file
current_size = os.path.getsize(rom_path)

# Write the current size in hex format to temp.asm
with open('headersize.asm', 'w') as asm_file:
    headersize = 0x80400000 - current_size
    asm_file.write(f'.headersize 0x{headersize:08X}\n')
    asm_file.write(f'.org 0x80400000\n')
    asm_file.write('PAYLOAD_START_RAM:\n')
    print(f'Current size written to headersize.asm: 0x{current_size:08X}')

with open('rom_start.asm', 'w') as asm_file:
    asm_file.write(f'.definelabel ROM_START, 0x{current_size:08X}\n')

# Pad the file with 0xFF if it's smaller than the target size
with open(rom_path, 'ab') as rom_file:
    current_size = rom_file.tell()  # Get the current file size
    if current_size < target_size:
        padding_needed = target_size - current_size
        rom_file.write(b'\xFF' * padding_needed)
        print(f'Padded {padding_needed} bytes to {rom_path}. New size is {target_size} bytes.')
    else:
        print(f'{rom_path} is already {current_size} bytes, no padding needed.')
