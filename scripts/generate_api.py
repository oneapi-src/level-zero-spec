import os
import re
import util

"""
    generates the CMakeLists file for the list of files
"""
def generate_cmake(path, type):
    fin = os.path.join("templates", "CMakeLists%s.mako"%type)
    fout = os.path.join(path, "CMakeLists.txt")
    files=[]
    files.extend([os.path.basename(f) for f in util.findFiles(path, "*.h")])
    files.extend([os.path.basename(f) for f in util.findFiles(path, "*.inl")])
    files.extend([os.path.basename(f) for f in util.findFiles(path, "*.cpp")])
    files.sort()
    return util.makoWrite(
        fin, fout,
        files=files)

"""
    generic function for generating c/c++ files from the specification documents
"""
def generate_code(path, section, namespace, specs, meta, type):
    loc = 0
    template = "api%s.mako"%type
    fin = os.path.join("templates", template)

    files = []
    for s in specs:
        filename = "%s_%s%s"%(namespace[0], s['name'], type)
        files.append(filename)
        fout = os.path.join(path, filename)

        print("Generating %s..."%fout)
        loc += util.makoWrite(
            fin, fout,
            ns=namespace,
            name = s['name'],
            header = s['header'],
            objects = s['objects'],
            section=section,
            specs=specs,
            meta = meta)
    return loc, files

"""
    generates a single c/c++ include file for the list of files
"""
def generate_include_all(path, namespace, files, type):
    template = "api_all%s.mako"%type
    fin = os.path.join("templates", template)

    filename = "%s_all%s"%(namespace[0],type)
    fout = os.path.join(path, filename)

    return util.makoWrite(
        fin, fout,
        ns=namespace,
        files=files)

"""
    generates c/c++ include files from the specification documents
"""
def generate_cpp_include(path, namespace, specs, meta):
    cpp_path = os.path.join(path, "include")
    util.makePath(cpp_path)
    util.removeFiles(cpp_path, "*.h")
    util.removeFiles(cpp_path, "*.hpp")
    util.removeFiles(cpp_path, "*.inl")

    hloc, hfiles = generate_code(cpp_path, os.path.basename(path), namespace, specs, meta, ".h")
    hpploc, hppfiles = generate_code(cpp_path, os.path.basename(path), namespace, specs, meta, ".hpp")
    inlloc, inlfiles = generate_code(cpp_path, os.path.basename(path), namespace, specs, meta, ".inl")

    hloc += generate_include_all(cpp_path, namespace, hfiles, ".h")
    hpploc += generate_include_all(cpp_path, namespace, hppfiles + inlfiles, ".hpp")

    #generate_cmake(cpp_path, hfiles + hppfiles + inlfiles)
    return hloc + hpploc + inlloc

"""
    generates c/c++ source files from the specification documents
"""
def generate_cpp_source(path, namespace, specs, meta):
    cpp_path = os.path.join(path, "source")
    util.makePath(cpp_path)
    util.removeFiles(cpp_path, "%s_*.cpp"%namespace[0])

    loc, files = generate_code(cpp_path, os.path.basename(path), namespace, specs, meta, ".cpp")
    generate_cmake(cpp_path, ".cpp")
    return loc

"""
Entry-point:
    generates all c/c++ code
"""
def generate_cpp(path, namespace, specs, meta):
    loc = 0
    loc += generate_cpp_include(path, namespace, specs, meta)
    loc += generate_cpp_source(path, namespace, specs, meta)
    print("Generated %s lines of code.\n"%loc)
