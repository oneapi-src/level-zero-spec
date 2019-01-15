import os
import util

def generate_md(path, namespace, name):
    input = os.path.join("templates", "%s.md.mako"%name)
    output = os.path.join(path, "%s.md"%namespace.upper())
    print("Generating %s..."%output)
    util.makoWrite(input, output,
        x=namespace,
        X=namespace.upper(),
        Xx=namespace.title())

def generate_html():
    print("\nGenerating HTML...")
    cmdline = "doxygen.exe Doxyfile"
    os.system(cmdline)
