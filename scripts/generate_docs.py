import os

def generate_html():
    print("\nGenerating HTML...")
    cmdline = "doxygen.exe Doxyfile"
    os.system(cmdline)
    
def generate_all():
    generate_html()
