import os
import re
import util

"""
    generates the CMakeLists file for the list of files
"""
def generate_cmake(path, namespace, files):
    fin = os.path.join("templates", "CMakeLists.txt.mako")
    fout = os.path.join(path, "CMakeLists.txt")
    return util.makoWrite(
        fin, fout,
        name=namespace,
        files=files)

"""
    generic function for generating c/c++ files from the specification documents
"""
def generate_code(path, namespace, specs, meta, type):
    loc = 0
    template = "api%s.mako"%type
    fin = os.path.join("templates", template)

    files = []
    for s in specs:
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
            objects = s['objects'],
            meta = meta)
    return loc, files

"""
    generates a single c/c++ include file for the list of files
"""
def generate_include_all(path, namespace, files, type):
    template = "api_all%s.mako"%type
    fin = os.path.join("templates", template)

    filename = "%s_all%s"%(namespace,type)
    fout = os.path.join(path, filename)

    return util.makoWrite(
        fin, fout,
        x=namespace,
        X=namespace.upper(),
        Xx=namespace.title(),
        files=files)

"""
    generates c/c++ include files from the specification documents
"""
def generate_h_include(path, namespace, specs, meta):
    cpp_path = os.path.join(path, "include")
    util.makePath(cpp_path)
    util.removeFiles(path, "*.h")

    loc, files = generate_code(cpp_path, namespace, specs, meta, ".h")
    loc += generate_include_all(cpp_path, namespace, files, ".h")
    generate_cmake(cpp_path, namespace, files)
    return loc

"""
    generates c++ wrapper include files from the specification documents
"""
def generate_hpp_include(path, namespace, specs, meta):
    cpp_path = os.path.join(path, "include")
    util.makePath(cpp_path)
    util.removeFiles(path, "*.hpp")

    loc, files = generate_code(cpp_path, namespace, specs, meta, ".hpp")
    loc += generate_include_all(cpp_path, namespace, files, ".hpp")
    generate_cmake(cpp_path, namespace, files)
    return loc

"""
    generates c/c++ source files from the specification documents
"""
def generate_cpp_source(path, namespace, specs, meta):
    cpp_path = os.path.join(path, "source")
    util.makePath(cpp_path)
    util.removeFiles(path, "*.cpp")

    loc, files = generate_code(cpp_path, namespace, specs, meta, ".cpp")
    generate_cmake(cpp_path, namespace, files)
    return loc

"""
Entry-point:
    generates all c/c++ code
"""
def generate_cpp(path, namespace, specs, meta):
    loc = 0
    loc += generate_h_include(path, namespace, specs, meta)
    #loc += generate_hpp_include(path, namespace, specs, meta)
    loc += generate_cpp_source(path, namespace, specs, meta)
    print("Generated %s lines of code.\n"%loc)
