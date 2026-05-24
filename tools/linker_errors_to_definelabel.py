import re
import os
from pathlib import Path

def extract_symbols_from_source(src_dir='src', include_dir='include'):
    symbols = set()
    
    func_pattern = re.compile(r'\b([a-zA-Z_][a-zA-Z0-9_]*)\s*\(')
    var_pattern = re.compile(r'\b(?:extern|static)?\s+(?:const\s+)?(?:struct\s+)?[a-zA-Z_][a-zA-Z0-9_]*\s+\*?\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*(?:;|=|\[)')
    
    if os.path.exists(src_dir):
        for c_file in Path(src_dir).rglob('*.c'):
            try:
                with open(c_file, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()
                    symbols.update(func_pattern.findall(content))
                    symbols.update(var_pattern.findall(content))
            except Exception as e:
                print(f"Warning: Could not read {c_file}: {e}")
    
    if os.path.exists(include_dir):
        for h_file in Path(include_dir).rglob('*.h'):
            try:
                with open(h_file, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()
                    symbols.update(func_pattern.findall(content))
                    symbols.update(var_pattern.findall(content))
            except Exception as e:
                print(f"Warning: Could not read {h_file}: {e}")
    
    return symbols

def capitalize_hex_in_symbol(symbol):
    return re.sub(r'_([0-9a-fA-F]+)', lambda m: '_' + m.group(1).upper(), symbol)

def find_correct_case(symbol_lower, known_symbols):
    lower_to_correct = {s.lower(): s for s in known_symbols}
    return lower_to_correct.get(symbol_lower, symbol_lower)

def load_symbol_addrs(path='symbol_addrs.txt'):
    addrs = {}
    try:
        with open(path, 'r', errors='replace') as f:
            for line in f:
                line = line.split('//')[0].strip()
                m = re.match(r'^([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;', line)
                if m:
                    addrs[m.group(1)] = m.group(2).upper().replace('0X', '0x')
    except FileNotFoundError:
        print("Note: symbol_addrs.txt not found, addresses will remain as 0x?")
    return addrs


def parse_linker_symbols(linker_output, src_dir='src', include_dir='include'):
    symbol_addrs = load_symbol_addrs()
    print(f"Loaded {len(symbol_addrs)} addresses from symbol_addrs.txt")

    print("Scanning source files for symbol names...")
    known_symbols = extract_symbols_from_source(src_dir, include_dir)
    print(f"Found {len(known_symbols)} symbols in source files")
    
    pattern = r'Undefined external symbol (\S+)'
    symbols = set(re.findall(pattern, linker_output))
    print(f"Found {len(symbols)} undefined symbols in linker output")
    
    # Matches func_XXXXXXXX_YYYY or D_XXXXXXXX_YYYY — used as address fallback only
    hex_pattern = re.compile(r'^(func|d)_([0-9a-f]{8})_[0-9a-f]+', re.IGNORECASE)
    
    definelabels = []
    corrected_count = 0
    # Case-insensitive map: lowercase name -> (correct_case_name, address)
    addrs_lower = {k.lower(): (k, v) for k, v in symbol_addrs.items()}

    for symbol in sorted(symbols):
        # Strip mp3_ prefix before processing, restore it in output
        prefix = ''
        bare = symbol
        if symbol.startswith('mp3_'):
            prefix = 'mp3_'
            bare = symbol[len('mp3_'):]

        bare_lower = bare.lower()

        # 1. Always check symbol_addrs first — gets correct casing AND address
        if bare_lower in addrs_lower:
            correct_bare, addr = addrs_lower[bare_lower]
            if correct_bare != bare:
                corrected_count += 1
            definelabels.append(f".definelabel {prefix}{correct_bare}, {addr}")
            continue

        # 2. Not in symbol_addrs — try to extract address from the symbol name itself
        match = hex_pattern.match(bare)
        if match:
            ram_address = match.group(2).upper()
            correct_bare = capitalize_hex_in_symbol(bare)
            source_symbol = find_correct_case(bare, known_symbols)
            if source_symbol != bare:
                correct_bare = source_symbol
                corrected_count += 1
            definelabels.append(f".definelabel {prefix}{correct_bare}, 0x{ram_address}")
            continue

        # 3. Named symbol not found anywhere — correct casing if possible, address unknown
        correct_bare = find_correct_case(bare, known_symbols)
        if correct_bare != bare:
            corrected_count += 1
        definelabels.append(f".definelabel {prefix}{correct_bare}, 0x?")
    
    print(f"Corrected capitalization for {corrected_count} symbols")
    
    return '\n'.join(definelabels)


if __name__ == "__main__":
    try:
        with open("linker_errors.txt", "r") as f:
            linker_output = f.read()
    except FileNotFoundError:
        print("Error: linker_errors.txt not found")
        print("Please create a file with your linker error output")
        exit(1)
    
    result = parse_linker_symbols(linker_output, src_dir='src', include_dir='include')
    
    print("\n" + "="*60)
    print("Generated .definelabel statements:")
    print("="*60)
    print(result)
    
    with open("definelabels.asm", "w") as f:
        f.write(result)
    
    print(f"\n{len(result.splitlines())} .definelabel statements written to definelabels.asm")