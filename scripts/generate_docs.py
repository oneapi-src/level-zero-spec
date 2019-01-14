import os

def generate_html():
    print("Generating HTML...")
    cmdline = "doxygen.exe Doxyfile"
    os.system(cmdline)
    
def generate_all():
    generate_html()
