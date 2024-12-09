import os
import hashlib

#This outputs the combined binary but without patching so you can then go to https://hack64.net/tools/patcher.php -
#and patch the rom that way

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

def main():
    files_found = {}
    roms_directory = 'roms/'

    # Search for files in the roms directory and calculate checksums
    print(f"Searching for files in {roms_directory}...")
    for file in os.listdir(roms_directory):
        if file.endswith(('.z64', '.n64')):
            file_path = os.path.join(roms_directory, file)
            checksum = calculate_md5(file_path)
            print(f"Checksum for {file}: {checksum}")

            # Match checksums with provided ones
            for game_name, checksums in MD5_CHECKSUMS.items():
                if checksum == checksums["big_endian"]:
                    files_found[game_name] = (file_path, 'big_endian')
                elif checksum == checksums["little_endian"]:
                    files_found[game_name] = (file_path, 'little_endian')

    # Verify if the required files were found
    if "Mario Party 3" in files_found and "Mario Party 2" in files_found:
        output_data = bytearray()

        # Append Mario Party 3 first, then Mario Party 2
        for game_name in ["Mario Party 3", "Mario Party 2"]:
            file_path, endian = files_found[game_name]
            with open(file_path, "rb") as f:
                data = f.read()
                if endian == 'little_endian':
                    output_data.extend(byte_swap(data))  # Byte swap for little endian
                    print(f"Byte swapped data from {game_name}.")
                else:
                    output_data.extend(data)  # No need to swap for big endian
                    print(f"Added data from {game_name} without byte swapping.")

        # Write the combined output to a new file
        base_output_file = "mp3-mp2-base.z64"
        with open(base_output_file, "wb") as output_file:
            output_file.write(output_data)
        
        print("Files combined successfully into mp3-mp2-base.z64.")

        # Check for Mario Party 1 and combine it if found
        if "Mario Party 1" in files_found:
            output_data_v2 = bytearray()
            # First add data from Mario Party 3
            file_path, endian = files_found["Mario Party 3"]
            with open(file_path, "rb") as f:
                data = f.read()
                if endian == 'little_endian':
                    output_data_v2.extend(byte_swap(data))  # Byte swap for little endian
                    print(f"Byte swapped data from Mario Party 3.")
                else:
                    output_data_v2.extend(data)  # No need to swap for big endian
                    print(f"Added data from Mario Party 3 without byte swapping.")

            # Then add data from Mario Party 2
            file_path, endian = files_found["Mario Party 2"]
            with open(file_path, "rb") as f:
                data = f.read()
                if endian == 'little_endian':
                    output_data_v2.extend(byte_swap(data))  # Byte swap for little endian
                    print(f"Byte swapped data from Mario Party 2.")
                else:
                    output_data_v2.extend(data)  # No need to swap for big endian
                    print(f"Added data from Mario Party 2 without byte swapping.")

            # Finally add data from Mario Party 1
            file_path, endian = files_found["Mario Party 1"]
            with open(file_path, "rb") as f:
                data = f.read()
                if endian == 'little_endian':
                    output_data_v2.extend(byte_swap(data))  # Byte swap for little endian
                    print(f"Byte swapped data from Mario Party 1.")
                else:
                    output_data_v2.extend(data)  # No need to swap for big endian
                    print(f"Added data from Mario Party 1 without byte swapping.")

            # Write the second output to a new file
            base_output_file_v2 = "mp3-mp2-mp1-base.z64"
            with open(base_output_file_v2, "wb") as output_file_v2:
                output_file_v2.write(output_data_v2)

            print("Files combined successfully into mp3-mp2-mp1-base.z64.")
        else:
            print("Mario Party 1 not found, skipping.")
    else:
        if "Mario Party 3" not in files_found:
            print("Error: Mario Party 3 not found.")
        if "Mario Party 2" not in files_found:
            print("Error: Mario Party 2 not found.")

if __name__ == "__main__":
    main()
