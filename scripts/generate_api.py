import os
import re
import util

def generate_cmake(path, namespace, files):
    fin = os.path.join("templates", "CMakeLists.txt.mako")
    fout = os.path.join(path, "CMakeLists.txt")
    return util.makoWrite(
        fin, fout,
        name=namespace,
        files=files)

def generate_cpp_header_all(path, namespace, files):
    fin = os.path.join("templates", "api_all.h.mako")
    fout = os.path.join(path, "%s_all.h"%namespace)
    return util.makoWrite(
        fin, fout,
        x=namespace,
        X=namespace.upper(),
        Xx=namespace.title(),
        files=files)

def generate_cpp_headers(path, namespace, specs):
    loc = 0
    cpp_path = os.path.join(path, "include")
    util.makePath(cpp_path)
    util.removeFiles(cpp_path, "*.h")
    util.removeFiles(cpp_path, "*.txt")

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
            header = s['header'],
            objects = s['objects'])

    loc += generate_cpp_header_all(cpp_path, namespace, files)
    generate_cmake(cpp_path, namespace, files)
    return loc

def generate_cpp_source(path, namespace, specs):
    loc = 0
    cpp_path = os.path.join(path, "source")
    util.makePath(cpp_path)
    util.removeFiles(cpp_path, "*.cpp")
    util.removeFiles(cpp_path, "*.txt")

    files = []
    for s in specs:
        fin = os.path.join("templates", "api.cpp.mako")
        filename = "%s_%s.cpp"%(namespace, s['name'])
        files.append(filename)
        fout = os.path.join(cpp_path, filename)

        print("Generating %s..."%fout)
        loc += util.makoWrite(
            fin, fout,
            x=namespace,
            X=namespace.upper(),
            Xx=namespace.title(),
            name = s['name'],
            header = s['header'],
            objects = s['objects'])

    generate_cmake(cpp_path, namespace, files)
    return loc

def generate_cpp(path, namespace, specs):
    loc = 0
    loc += generate_cpp_headers(path, namespace, specs)
    loc += generate_cpp_source(path, namespace, specs)
    print("Generated %s lines of code.\n"%loc)
