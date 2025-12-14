import glob
import os
import sys
import platform
import shutil
import ninja_syntax

pj64_rdb_path = "C:/Users/Rainchus/Desktop/Desktop/newest_pj64/Config/Project64.rdb"

# Configuration: Set to True to use wine, False to use wibo
USE_WINE = True

def is_windows():
    """Check if the current platform is Windows."""
    return platform.system() == "Windows"

def get_exe_command(exe_name):
    """Returns the appropriate command to run an exe based on the platform."""
    exe_path = f'tools/mp_build_scripts/{exe_name}'
    
    if is_windows():
        return exe_path
    else:
        if USE_WINE:
            # Use wine
            if not shutil.which("wine"):
                print("Error: wine not found. Install it with: sudo apt install wine", file=sys.stderr)
                sys.exit(1)
            return f"wine {exe_path}"
        else:
            # Use wibo
            wibo_path = "tools/wibo"
            if not os.path.exists(wibo_path):
                print(f"Error: {wibo_path} not found", file=sys.stderr)
                sys.exit(1)
            return f"{wibo_path} {exe_path}"

def check_and_create_rom(mp1=False):
    mp3_mp2_path = 'rom/mp3-mp2.z64'
    mp3_mp2_mp1_path = 'rom/mp3-mp2-mp1.z64'
    mp3_path = 'rom/mp3-temp.z64'
    mp2_path = 'rom/mp2.z64'
    mp1_path = 'rom/mp1.z64'

    if mp1:
        # Check if mp3-mp2-mp1.z64 exists
        if os.path.exists(mp3_mp2_mp1_path):
            print(f"{mp3_mp2_mp1_path} found.")
        else:
            # Check for mp3-mp2.z64 and mp1.z64
            missing_files = []
            if not os.path.exists(mp3_mp2_path):
                missing_files.append(mp3_mp2_path)
            if not os.path.exists(mp1_path):
                missing_files.append(mp1_path)

            if missing_files:
                missing_files_str = ', '.join(missing_files)
                error_message = f"The following file(s) are missing: {missing_files_str}"
                raise FileNotFoundError(error_message)
            else:
                # Create mp3-mp2-mp1.z64 by appending mp1.z64 to mp3-mp2.z64
                with open(mp3_mp2_mp1_path, 'wb') as mp3_mp2_mp1_file:
                    with open(mp3_mp2_path, 'rb') as mp3_mp2_file:
                        mp3_mp2_mp1_file.write(mp3_mp2_file.read())
                    with open(mp1_path, 'rb') as mp1_file:
                        mp3_mp2_mp1_file.write(mp1_file.read())
                print(f"Created {mp3_mp2_mp1_path} by appending {mp1_path} to {mp3_mp2_path}.")
    else:
        # Check if mp3-mp2.z64 exists
        if os.path.exists(mp3_mp2_path):
            print(f"{mp3_mp2_path} found.")
        else:
            # Check for mp3.z64 and mp2.z64
            missing_files = []
            if not os.path.exists(mp3_path):
                missing_files.append(mp3_path)
            if not os.path.exists(mp2_path):
                missing_files.append(mp2_path)

            if missing_files:
                missing_files_str = ', '.join(missing_files)
                error_message = f"The following file(s) are missing: {missing_files_str}"
                raise FileNotFoundError(error_message)
            else:
                # Create mp3-mp2.z64 by appending mp2.z64 to mp3.z64
                with open(mp3_mp2_path, 'wb') as mp3_mp2_file:
                    with open(mp3_path, 'rb') as mp3_file:
                        mp3_mp2_file.write(mp3_file.read())
                    with open(mp2_path, 'rb') as mp2_file:
                        mp3_mp2_file.write(mp2_file.read())
                print(f"Created {mp3_mp2_path} by appending {mp2_path} to {mp3_path}.")

# Check for '-mp1' flag
mp1_flag = '-mp1' in sys.argv

# .c files are put into expansion pak ram
c_files = glob.glob('src/**/*.c', recursive=True)

# Call the function based on the flag
check_and_create_rom(mp1=mp1_flag)

# Files to exclude from asm file lists
EXCLUDED_ASM_FILES = ['headersize.asm', 'rom_start.asm']

if mp1_flag == True:
    # .s files are put into expansion pak ram and are *not* intended to have their headersize changed
    s_files = glob.glob('asm/**/*.s', recursive=True)
    
    # .asm files are assembly files that often change the headersize
    # Exclude files from the exclusion list
    asm_files = [f for f in glob.glob('asm/**/*.asm', recursive=True) 
                 if not any(excluded in f for excluded in EXCLUDED_ASM_FILES)]
else:
    # Exclude any files from the 'asm/mp1' directory
    s_files = [f for f in glob.glob('asm/**/*.s', recursive=True) 
               if 'asm/mp1' not in f]
    
    # Exclude mp1 files AND files from the exclusion list
    asm_files = [f for f in glob.glob('asm/**/*.asm', recursive=True) 
                 if 'asm/mp1' not in f and not any(excluded in f for excluded in EXCLUDED_ASM_FILES)]

# Set the ROM name based on the presence of the -mp1 flag
rom_name = 'mp3-mp2-mp1' if mp1_flag else 'mp3-mp2'
rom_mod_name = f'{rom_name}.mod.z64'

# Conditionally add -DMP1 to STANDARDFLAGS if -mp1 flag is passed
standard_flags = '-O2 -Wall -Wno-missing-braces -mtune=vr4300 -march=vr4300 -mabi=32 -fomit-frame-pointer -mno-abicalls -fno-pic -G0 -fno-inline -DF3DEX_GBI_2'
if mp1_flag:
    standard_flags += ' -DMP1'

header = f"""
//Automatically generated by configure.py, do not edit
.n64 // Let armips know we're coding for the N64 architecture
.open "rom/{rom_name}.z64", "rom/{rom_mod_name}", 0 // Open the ROM file
"""

footer = """
.align 8
PAYLOAD_END_RAM:
.close //close file
"""

# Get the cross-platform n64crc command
n64crc_command = get_exe_command('n64crc.exe')

with open('build.ninja', 'w') as buildfile:
    ninja = ninja_syntax.Writer(buildfile)
    ninja.variable('CC', 'mips64-elf-gcc')
    ninja.variable('STANDARDFLAGS', standard_flags)
    ninja.variable('INCLUDE_FLAGS', '-Iinclude -Isrc')

    ninja.rule(
        "cc",
        command="$CC $STANDARDFLAGS $INCLUDE_FLAGS -c $in -o $out",
        description="Compiling $in to $out",
        depfile="$out.d",
        deps="gcc",
    )

    # List to collect all object files
    obj_files = []

    # Create build statements for each .c file
    for c_file in c_files:
        obj_file = os.path.join('obj', os.path.relpath(c_file, 'src')).replace('.c', '.o')
        ninja.build(obj_file, 'cc', c_file)
        obj_files.append(obj_file)

    # Add a phony target that depends on all object files
    ninja.build('all', 'phony', obj_files)

    # Add a rule to run armips on main.asm after all .o files are built
    ninja.rule(
        "armips",
        command="armips asm/main.asm -sym syms.txt",
        description="Running armips on main.asm"
    )

    # Create a build statement to run armips after all .o files are built
    ninja.build('run_armips', 'armips', 'all')

    # Add a rule to run n64crc.exe on mod.z64 after armips completes
    ninja.rule(
        "n64crc",
        command=f"{n64crc_command} rom/{rom_mod_name}",
        description=f"Running n64crc.exe on {rom_mod_name}"
    )

    # Create a build statement to run n64crc.exe after armips
    ninja.build('run_n64crc', 'n64crc', 'run_armips')

    if not mp1_flag:
        # Define the trim_rom rule to truncate the ROM
        ninja.rule(
            "trim_rom",
            command=f"python tools/truncate_rom.py rom/{rom_mod_name}",
            description=f"Trimming ROM at {rom_mod_name}"
        )

        # Create the build target for trim_rom with dependencies on run_armips and run_n64crc
        ninja.build('trim_rom', 'trim_rom', ['run_armips', 'run_n64crc'])



# Create an ASM file that includes other .asm and .s files and imports .o files
with open("asm/main.asm", 'w') as file:
    file.write(header)

    file.write(".include \"asm/rom_start.asm\"\n")

    for asm_file in asm_files:
        if asm_file.endswith('main.asm'):
            continue
        file.write(f".include \"{asm_file}\"\n")

    file.write(".include \"asm/headersize.asm\"\n")

    for s_file in s_files:
        file.write(f".include \"{s_file}\"\n")

    for c_file in c_files:
        obj_file = os.path.join('obj', os.path.relpath(c_file, 'src')).replace('.c', '.o')
        file.write(f".importobj \"{obj_file}\"\n")

    file.write(footer)