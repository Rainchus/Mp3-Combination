import sys
import subprocess

def main():
    # Call main_configure.py with no arguments
    subprocess.run(['python', 'tools/main_configure.py'])

    # Check for -mp1 argument
    if '-mp1' in sys.argv:
        subprocess.run(['python', 'tools/main_configure.py', '-mp1'])

if __name__ == "__main__":
    main()
