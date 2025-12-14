import re
import os
from pathlib import Path

def extract_symbols_from_source(src_dir='src', include_dir='include'):
    """
    Extract all function and variable declarations from .c and .h files.
    
    Args:
        src_dir: Directory containing .c files
        include_dir: Directory containing .h files
        
    Returns:
        Set of symbol names with correct capitalization
    """
    symbols = set()
    
    # Patterns to match function declarations and definitions
    func_pattern = re.compile(r'\b([a-zA-Z_][a-zA-Z0-9_]*)\s*\(')
    # Pattern to match variable declarations (extern or static)
    var_pattern = re.compile(r'\b(?:extern|static)?\s+(?:const\s+)?(?:struct\s+)?[a-zA-Z_][a-zA-Z0-9_]*\s+\*?\s*([a-zA-Z_][a-zA-Z0-9_]*)\s*(?:;|=|\[)')
    
    # Process .c files
    if os.path.exists(src_dir):
        for c_file in Path(src_dir).rglob('*.c'):
            try:
                with open(c_file, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()
                    # Find function names
                    symbols.update(func_pattern.findall(content))
                    # Find variable names
                    symbols.update(var_pattern.findall(content))
            except Exception as e:
                print(f"Warning: Could not read {c_file}: {e}")
    
    # Process .h files
    if os.path.exists(include_dir):
        for h_file in Path(include_dir).rglob('*.h'):
            try:
                with open(h_file, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()
                    # Find function names
                    symbols.update(func_pattern.findall(content))
                    # Find variable names
                    symbols.update(var_pattern.findall(content))
            except Exception as e:
                print(f"Warning: Could not read {h_file}: {e}")
    
    return symbols

def find_correct_case(symbol_lower, known_symbols):
    """
    Find the correct capitalization for a symbol.
    
    Args:
        symbol_lower: Lowercase symbol name
        known_symbols: Set of correctly-cased symbols from source files
        
    Returns:
        Correctly-cased symbol name or original if not found
    """
    # Create a lowercase mapping
    lower_to_correct = {s.lower(): s for s in known_symbols}
    
    return lower_to_correct.get(symbol_lower, symbol_lower)

def parse_linker_symbols(linker_output, src_dir='src', include_dir='include'):
    """
    Parse linker error output and generate .definelabel statements.
    
    Args:
        linker_output: String containing the linker error output
        src_dir: Directory containing .c files
        include_dir: Directory containing .h files
        
    Returns:
        String containing .definelabel statements
    """
    # Extract symbols from source files
    print("Scanning source files for symbol names...")
    known_symbols = extract_symbols_from_source(src_dir, include_dir)
    print(f"Found {len(known_symbols)} symbols in source files")
    
    # Pattern to match undefined symbol errors
    pattern = r'Undefined external symbol (\S+)'
    
    # Find all unique symbols
    symbols = set(re.findall(pattern, linker_output))
    print(f"Found {len(symbols)} undefined symbols in linker output")
    
    # Pattern to match func_XXXXXXXX_YYYY or d_XXXXXXXX_YYYY format
    hex_pattern = re.compile(r'^(func|d)_([0-9a-f]{8})_[0-9a-f]+', re.IGNORECASE)
    
    definelabels = []
    corrected_count = 0
    
    for symbol in sorted(symbols):
        match = hex_pattern.match(symbol)
        
        if match:
            # Symbol follows the func_XXXXXXXX_YYYY or d_XXXXXXXX_YYYY pattern
            ram_address = match.group(2)
            # Try to find correct case
            correct_symbol = find_correct_case(symbol, known_symbols)
            if correct_symbol != symbol:
                corrected_count += 1
            definelabels.append(f".definelabel {correct_symbol}, 0x{ram_address}")
        else:
            # Named symbol - use 0x? as placeholder
            # Try to find correct case
            correct_symbol = find_correct_case(symbol, known_symbols)
            if correct_symbol != symbol:
                corrected_count += 1
            definelabels.append(f".definelabel {correct_symbol}, 0x?")
    
    print(f"Corrected capitalization for {corrected_count} symbols")
    
    return '\n'.join(definelabels)


# Example usage
if __name__ == "__main__":
    # Read from file or use the provided text
    try:
        with open("linker_errors.txt", "r") as f:
            linker_output = f.read()
    except FileNotFoundError:
        print("Error: linker_errors.txt not found")
        print("Please create a file with your linker error output")
        exit(1)
    
    # Parse with case correction
    result = parse_linker_symbols(linker_output, src_dir='src', include_dir='include')
    
    # Print to console
    print("\n" + "="*60)
    print("Generated .definelabel statements:")
    print("="*60)
    print(result)
    
    # Write to file
    with open("definelabels.asm", "w") as f:
        f.write(result)
    
    print(f"\n{len(result.splitlines())} .definelabel statements written to definelabels.asm")