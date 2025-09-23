import os
import hashlib
import subprocess
import struct

# Hardcoded MD5 checksums
MD5_CHECKSUMS = {
    "Mario Party 3": {
        "big_endian": "76a8bbc81bc2060ec99c9645867237cc",
        "little_endian": "224686fcc5de97850cffa5d92784c327",
    },
    "Mario Party 2": {
        "big_endian": "04840612a35ece222afdb2dfbf926409",
        "little_endian": "ba248c51cfac5cdecc9202772b1e1f73",
    },
    "Mario Party 1": {
        "big_endian": "8bc2712139fbf0c56c8ea835802c52dc",
        "little_endian": "20d59c3862187c651fb311983b7b8a5c",
    },
}

def calculate_md5(file_path):
    """Calculate the MD5 checksum of a file."""
    hash_md5 = hashlib.md5()
    with open(file_path, "rb") as f:
        for chunk in iter(lambda: f.read(4096), b""):
            hash_md5.update(chunk)
    return hash_md5.hexdigest()

def byte_swap(data):
    """Byte swap the provided binary data to convert to big endian."""
    swapped = bytearray()
    for i in range(0, len(data), 4):
        chunk = data[i:i+4]
        if len(chunk) == 4:
            swapped.extend(reversed(chunk))
        else:
            swapped.extend(chunk)  # Handle any remaining bytes
    return swapped

def apply_patch(patch_file, target_file, output_file):
    """Apply a patch using flips.exe."""
    command = f'flips.exe --apply "{patch_file}" "{target_file}" "{output_file}"'
    print(f"Applying patch: {command}")
    result = subprocess.run(command, shell=True)  # Run the command and wait for it to complete
    return result.returncode

def read_offset_from_bps(bps_file, start, end):
    """Read a 4-byte little endian offset from a BPS file."""
    with open(bps_file, "rb") as f:
        f.seek(start)
        data = f.read(end - start)
        return struct.unpack("<I", data)[0]

def insert_at_offset(base_data, insert_data, offset):
    """Insert/overwrite data at a specific offset in a bytearray."""
    if len(base_data) < offset + len(insert_data):
        base_data.extend(b"\x00" * (offset + len(insert_data) - len(base_data)))
    base_data[offset:offset+len(insert_data)] = insert_data
    return base_data

def main():
    files_found = {}
    roms_directory = 'roms/'

    print(f"Searching for files in {roms_directory}...")
    for file in os.listdir(roms_directory):
        if file.endswith(('.z64', '.n64')):
            file_path = os.path.join(roms_directory, file)
            checksum = calculate_md5(file_path)
            print(f"Checksum for {file}: {checksum}")

            for game_name, checksums in MD5_CHECKSUMS.items():
                if checksum == checksums["big_endian"]:
                    files_found[game_name] = (file_path, 'big_endian')
                elif checksum == checksums["little_endian"]:
                    files_found[game_name] = (file_path, 'little_endian')

    if "Mario Party 3" in files_found and "Mario Party 2" in files_found:
        # Start with MP3 data
        file_path, endian = files_found["Mario Party 3"]
        with open(file_path, "rb") as f:
            mp3_data = f.read()
            if endian == 'little_endian':
                mp3_data = byte_swap(mp3_data)
                print("Byte swapped data from Mario Party 3.")

        output_data = bytearray(mp3_data)

        # Insert MP2 at offset from mp3-mp2-combo.bps
        mp2_offset = read_offset_from_bps("mp3-mp2-combo.bps", 0xF, 0x13)
        file_path, endian = files_found["Mario Party 2"]
        with open(file_path, "rb") as f:
            mp2_data = f.read()
            if endian == 'little_endian':
                mp2_data = byte_swap(mp2_data)
                print("Byte swapped data from Mario Party 2.")
        insert_at_offset(output_data, mp2_data, mp2_offset)
        base_output_file = "mp3-mp2-base.z64"
        with open(base_output_file, "wb") as out:
            out.write(output_data)
        print(f"Files combined successfully into {base_output_file} (MP3 + MP2 at 0x{mp2_offset:X}).")

        # If MP1 exists, insert it using mp3-mp2-mp1-combo.bps
        if "Mario Party 1" in files_found:
            mp1_offset = read_offset_from_bps("mp3-mp2-mp1-combo.bps", 0x13, 0x17)
            file_path, endian = files_found["Mario Party 1"]
            with open(file_path, "rb") as f:
                mp1_data = f.read()
                if endian == 'little_endian':
                    mp1_data = byte_swap(mp1_data)
                    print("Byte swapped data from Mario Party 1.")
            insert_at_offset(output_data, mp1_data, mp1_offset)
            base_output_file_v2 = "mp3-mp2-mp1-base.z64"
            with open(base_output_file_v2, "wb") as out:
                out.write(output_data)
            print(f"Files combined successfully into {base_output_file_v2} (MP3 + MP2 + MP1 at 0x{mp1_offset:X}).")
        else:
            print("Mario Party 1 not found, skipping.")

    else:
        if "Mario Party 3" not in files_found:
            print("Error: Mario Party 3 not found.")
        if "Mario Party 2" not in files_found:
            print("Error: Mario Party 2 not found.")

if __name__ == "__main__":
    main()
