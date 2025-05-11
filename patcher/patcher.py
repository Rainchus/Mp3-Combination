import os
import hashlib
import subprocess
from collections import OrderedDict

MD5_CHECKSUMS = {
    "Mario Party 3": {
        "big_endian": "76a8bbc81bc2060ec99c9645867237cc",
        "little_endian": "224686fcc5de97850cffa5d92784c327",
        "middle_endian": "ac422fb77258336895ee5355f1b2b36d",
    },
    "Mario Party 2": {
        "big_endian": "04840612a35ece222afdb2dfbf926409",
        "little_endian": "ba248c51cfac5cdecc9202772b1e1f73",
        "middle_endian": "f107f70ee02dced2617a5dedff72869b",
    },
    "Mario Party 1": {
        "big_endian": "8bc2712139fbf0c56c8ea835802c52dc",
        "little_endian": "20d59c3862187c651fb311983b7b8a5c",
        "middle_endian": "22d2815355f2be326aa4ab08976ea091",
    },
}

GAME_ORDER = OrderedDict([
    ("mp3-mp2", ["Mario Party 3", "Mario Party 2"]),
    ("mp3-mp2-mp1", ["Mario Party 3", "Mario Party 2", "Mario Party 1"])
])

PATCH_MAPPING = {
    "mp3-mp2": "mp3-mp2-combo.bps",
    "mp3-mp2-mp1": "mp3-mp2-mp1-combo.bps"
}

VALID_EXTENSIONS = ('.z64', '.n64', '.v64')

def calculate_md5(file_path):
    """Calculate MD5 hash of a file"""
    hash_md5 = hashlib.md5()
    with open(file_path, "rb") as f:
        for chunk in iter(lambda: f.read(4096), b""):
            hash_md5.update(chunk)
    return hash_md5.hexdigest()

def byteswap_z64(data):
    """Convert little-endian to big-endian (4-byte swap)"""
    return bytes(bytearray(reversed(data[i:i+4])) for i in range(0, len(data), 4))

def byteswap_v64(data):
    """Convert middle-endian to big-endian (2-byte swap)"""
    swapped = bytearray()
    for i in range(0, len(data), 2):
        chunk = data[i:i+2]
        swapped += chunk[::-1]
    return swapped

def process_rom(file_path, endian):
    """Read and process ROM file once"""
    with open(file_path, "rb") as f:
        data = f.read()
    
    if endian == "little_endian":
        return byteswap_z64(data)
    if endian == "middle_endian":
        return byteswap_v64(data)
    return data

def scan_roms_directory():
    """Scan roms directory and pre-process valid ROMs"""
    roms = {}
    
    print("Scanning roms/ directory for valid ROMs...")
    for filename in os.listdir("roms"):
        if not filename.lower().endswith(VALID_EXTENSIONS):
            continue
            
        path = os.path.join("roms", filename)
        if not os.path.isfile(path):
            continue

        try:
            checksum = calculate_md5(path)
        except IOError:
            continue

        # Find matching game and endianness
        for game, formats in MD5_CHECKSUMS.items():
            for endian, target_hash in formats.items():
                if target_hash.lower() == checksum.lower():
                    print(f"Processing {game} ({endian.replace('_', ' ')})")
                    rom_data = process_rom(path, endian)
                    roms[game] = rom_data
                    print(f"Processed {game} - {len(rom_data):,} bytes")
                    break
            else:
                continue
            break
        else:
            print(f"Skipped {filename} - no matching checksum")
    
    return roms

def build_output(rom_data, games, output_name):
    """Combine pre-processed ROMs into a single file"""
    output = bytearray()
    for game in games:
        output += rom_data[game]
    
    output_path = f"{output_name}-base.z64"
    with open(output_path, "wb") as f:
        f.write(output)
    print(f"Created combined ROM: {output_path}")
    return output_path

def apply_patch(patch_file, target_file, output_name):
    """Apply BPS patch using flips"""
    output_path = f"{output_name}.z64"
    cmd = f'flips.exe --apply "{patch_file}" "{target_file}" "{output_path}"'
    result = subprocess.run(cmd, shell=True, capture_output=True)
    
    if result.returncode == 0:
        print(f"Successfully created patched ROM: {output_path}")
        return True
    print(f"Patch failed: {result.stderr.decode().strip()}")
    return False

def main():
    # Scan and pre-process all ROMs
    rom_data = scan_roms_directory()
    
    # Check for required base games
    missing_base = [g for g in GAME_ORDER['mp3-mp2'] if g not in rom_data]
    if missing_base:
        print(f"\nError: Missing required ROMs - {', '.join(missing_base)}")
        return
    
    # Build available combinations
    built_files = {}
    for variant, games in GAME_ORDER.items():
        if all(g in rom_data for g in games):
            print(f"\nBuilding {variant} package...")
            built_path = build_output(rom_data, games, variant)
            built_files[variant] = built_path
    
    # Apply patches and clean up
    for variant, path in built_files.items():
        patch_file = PATCH_MAPPING.get(variant)
        if patch_file and os.path.exists(patch_file):
            print(f"\nApplying {patch_file}...")
            if apply_patch(patch_file, path, variant.replace("-base", "-combo")):
                os.remove(path)
                print(f"Removed temporary file: {path}")

if __name__ == "__main__":
    main()