import os
import util

def cl(filepath):
    cmdline = "cl.exe /c %s"%filepath
    os.system(cmdline)

def compile_cpp_source(path, namespace, specs):
    cpp_path = os.path.join(path, "source")

    for s in specs:
        filename = "%s_%s.cpp"%(namespace, s['name'])
        filepath = os.path.join(cpp_path, filename)
        print("Compiling %s..."%filepath)
        cl(filepath)

    util.removeFiles(".", "*.obj")

