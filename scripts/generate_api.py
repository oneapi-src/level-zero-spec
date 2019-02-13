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

def generate_code(path, namespace, specs, type):
    loc = 0
    util.makePath(path)
    util.removeFiles(path, "*%s"%type)
    util.removeFiles(path, "*.txt")

    files = []
    for s in specs:
        fin = os.path.join("templates", "api%s.mako"%type)
        filename = "%s_%s%s"%(namespace, s['name'], type)
        files.append(filename)
        fout = os.path.join(path, filename)

        print("Generating %s..."%fout)
        loc += util.makoWrite(
            fin, fout,
            x=namespace,
            X=namespace.upper(),
            Xx=namespace.title(),
            name = s['name'],
            header = s['header'],
            objects = s['objects'])
    return loc, files

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
    cpp_path = os.path.join(path, "include")
    loc, files = generate_code(cpp_path, namespace, specs, ".h")
    loc += generate_cpp_header_all(cpp_path, namespace, files)
    generate_cmake(cpp_path, namespace, files)
    return loc

def generate_cpp_source(path, namespace, specs):
    cpp_path = os.path.join(path, "source")
    loc, files = generate_code(cpp_path, namespace, specs, ".cpp")
    generate_cmake(cpp_path, namespace, files)
    return loc

def generate_cpp(path, namespace, specs):
    loc = 0
    loc += generate_cpp_headers(path, namespace, specs)
    loc += generate_cpp_source(path, namespace, specs)
    print("Generated %s lines of code.\n"%loc)
