import sys

class Colors:
    RESET = '\033[0m'
    BLACK = '\033[30m'
    RED = '\033[31m'
    GREEN = '\033[32m'
    YELLOW = '\033[33m'
    BLUE = '\033[34m'
    MAGENTA = '\033[35m'
    CYAN = '\033[36m'
    WHITE = '\033[37m'

ascii_translation_dictionary = {
    '+': '\\x3C',
    '-': '\\x3D',
    '×': '\\x3E',
    '→': '\\x3F',
    #'”': '\\x5B', #duplicate of 0xC1?
    "'": '\\x5C',
    '(': '\\x5D',
    ')': '\\x5E',
    '/': '\\x5F',
    ':': '\\x7B',
    '"': '\\x80',
    '°': '\\x81',
    ',': '\\x82',
    '.': '\\x85',
    '“': '\\xC0',
    '”': '\\xC1',
    '!': '\\xC2',
    '?': '\\xC3',
    '\n' : '\\n'
}

special_ascii_translation_dictionary = {
    'arg1': '\\x11',
    'arg2': '\\x12',
    'arg3': '\\x13',
    'arg4': '\\x14',
    'arg5': '\\x15',
    'arg6': '\\x16',

    'black': '\\x01',
    'default': '\\x02',
    'red': '\\x03',
    'purple': '\\x04',
    'green': '\\x05',
    'blue': '\\x06',
    'yellow': '\\x07',
    'white': '\\x08',

    'a': '\\x21',
    'b': '\\x22',
    'cup': '\\x23',
    'c-up': '\\x23',
    'cright': '\\x24',
    'c-right': '\\x24',
    'cleft': '\\x25',
    'c-left': '\\x25',
    'c-down': '\\x26',
    'z': '\\x27',
    'analog': '\\x28',
    'analog-stick': '\\x28',
    'coin': '\\x29',
    'star': '\\x2A',
    'start': '\\x2B',
    'r': '\\x2C',
}

def main():
    if len(sys.argv) > 1:  # Check if command-line argument is provided
        try:
            with open(sys.argv[1], 'r') as file:
                ascii_input = file.read()
        except FileNotFoundError:
            print("File not found.")
            return
    else:
        ascii_input = input("Enter ASCII text: ")

    ascii_output = ""

    i = 0
    while i < len(ascii_input):
        ascii_char = ascii_input[i]  # Get current char
        
        if ascii_char == '~':
            new_str_hex_value = ""
            # Read text until a space, print result
            i += 1  # Move to the next character after '~'
            text_until_space = ""  # var to store text until space
            while i < len(ascii_input) and ascii_input[i] != ' ':  # Loop until space is encountered or end of string
                text_until_space += ascii_input[i]  # Append characters until space is found
                i += 1
            text_until_space = text_until_space.lower()
            # Translate special ascii characters
            if text_until_space in special_ascii_translation_dictionary:
                ascii_output += f'""{special_ascii_translation_dictionary[text_until_space]}""'
                i += 1
                continue
            else:
                print(f"""Key "{text_until_space}" not found in special_ascii_translation_dictionary""")
                exit()

        # Translate basic ascii characters
        if ascii_char in ascii_translation_dictionary:
            ascii_output += f'""{ascii_translation_dictionary[ascii_char]}""'
        else:
            ascii_output += ascii_char
        i += 1
        

    print(f'{Colors.MAGENTA}Asm Output: {Colors.GREEN}.ascii "{ascii_output}"{Colors.RESET}')
    print(f'{Colors.MAGENTA}C Output: {Colors.CYAN}char strArray[] = {{"{ascii_output}"}};{Colors.RESET}')


if __name__ == "__main__":
    main()
