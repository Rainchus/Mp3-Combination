import subprocess
import os
import shutil
import platform
import sys
import urllib.request
from pathlib import Path

# Configuration: Set to True to use wine, False to use wibo
USE_WINE = True

def is_windows():
    """Check if the current platform is Windows."""
    return platform.system() == "Windows"

def download_wibo(wibo_path):
    """Download wibo if it doesn't exist."""
    if wibo_path.exists():
        print(f"Using existing wibo at {wibo_path}")
        return
    
    # Wibo version (should match config.wibo_tag from configure.py)
    wibo_version = "0.6.16"
    wibo_url = f"https://github.com/decompals/wibo/releases/download/{wibo_version}/wibo"
    
    print(f"Wibo not found at {wibo_path}")
    print(f"Downloading wibo {wibo_version}...")
    wibo_path.parent.mkdir(parents=True, exist_ok=True)
    
    try:
        urllib.request.urlretrieve(wibo_url, wibo_path)
        wibo_path.chmod(0o755)  # Make executable
        print(f"Successfully downloaded wibo to {wibo_path}")
    except Exception as e:
        print(f"Failed to download wibo: {e}", file=sys.stderr)
        sys.exit(1)

def get_exe_wrapper(exe_path, wrapper_path=None):
    """Returns the appropriate command to run an exe based on the platform."""
    if is_windows():
        return [str(exe_path)]
    else:
        if USE_WINE:
            # Use wine
            if not shutil.which("wine"):
                print("Error: wine not found. Install it with: sudo apt install wine", file=sys.stderr)
                sys.exit(1)
            print("Using wine to run Windows executable")
            return ["wine", str(exe_path)]
        else:
            # Use wibo
            if wrapper_path is None:
                wrapper_path = Path("tools") / "wibo"
                download_wibo(wrapper_path)
            
            if not wrapper_path.exists():
                print(f"Error: Wrapper {wrapper_path} not found", file=sys.stderr)
                sys.exit(1)
            
            print("Using wibo to run Windows executable")
            return [str(wrapper_path), str(exe_path)]

# Path to the temporary ROM file
rom_path = 'rom/mp3-temp.z64'
target_size = 0x2000000  # Target size of 32 MB

# Path to mpromtool
mpromtool_path = Path("tools") / "mp_build_scripts" / "mpromtool.exe"

# Check if mpromtool exists
if not mpromtool_path.exists():
    print(f"Error: {mpromtool_path} not found", file=sys.stderr)
    sys.exit(1)

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
print("Extracting ROM files...")
mpromtool_cmd = get_exe_wrapper(mpromtool_path)
subprocess.run(mpromtool_cmd + ['-a', 'rom/mp3.z64', 'mp3_extract/'], check=True)

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
subprocess.run(mpromtool_cmd + ['-b', '-a', 'rom/mp3.z64', 'mp3_extract/', 'rom/mp3-temp.z64'], check=True)

# Get the current size of the ROM file
current_size = os.path.getsize(rom_path)

# Write the current size in hex format to headersize.asm
with open('asm/headersize.asm', 'w') as asm_file:
    headersize = 0x80400000 - current_size
    asm_file.write(f'.headersize 0x{headersize:08X}\n')
    asm_file.write(f'.org 0x80400000\n')
    asm_file.write('PAYLOAD_START_RAM:\n')

print(f'Current size written to asm/headersize.asm: 0x{current_size:08X}')

with open('asm/rom_start.asm', 'w') as asm_file:
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

print("Initial mainfs pack complete!")