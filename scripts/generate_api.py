import os
import re
import util

def generate_cmake(path, name, files):
    fin = os.path.join("templates", "CMakeLists.txt.mako")
    fout = os.path.join(path, "CMakeLists.txt")
    util.makoWrite(
        fin, fout,
        name=name,
        files=files)

def generate_cpp_headers(path, namespace, specs):
    loc = 0
    cpp_path = os.path.join(path, "include")
    util.makePath(cpp_path)
    util.removeFiles(cpp_path, "*.h")
    files = []
    for s in specs:
        fin = os.path.join("templates", "api.h.mako")
        filename = "%s_%s.h"%(namespace, s['name'])
        files.append(filename)
        fout = os.path.join(cpp_path, filename)
        print("Generating %s..."%fout)
        loc += util.makoWrite(
            fin, fout,
            x=namespace,
            X=namespace.upper(),
            Xx=namespace.title(),
            name = s['name'],
            docs = s['docs'])
    print("Generated %s lines of code.\n"%loc)
    
    generate_cmake(cpp_path, namespace, files)
    
