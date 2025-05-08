import sys
import subprocess

def main():
    has_mp1 = '-mp1' in sys.argv
    has_mk64 = '-mk64' in sys.argv

    #subprocess.run(['python', 'main_configure.py'])

    if has_mp1 and has_mk64:
        subprocess.run(['python', 'main_configure.py', '-mp1', '-mk64'])
    elif has_mp1:
        subprocess.run(['python', 'main_configure.py', '-mp1'])
    else:
        subprocess.run(['python', 'main_configure.py'])

if __name__ == "__main__":
    main()
