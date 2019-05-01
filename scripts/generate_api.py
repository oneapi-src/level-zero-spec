import os
import re
import util

"""
    generic function for generating c/c++ files from the specification documents
"""
def generate_code(path, section, namespace, tags, specs, meta, type):
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
            name = s['name'],
            header = s['header'],
            objects = s['objects'],
            section=section,
            namespace=namespace,
            tags=tags,
            specs=specs,
            meta = meta)
    return loc, files

"""
    generates a single c/c++ include file for the list of files
"""
def generate_include_all(path, namespace, tags, files, type):
    template = "api_all%s.mako"%type
    fin = os.path.join("templates", template)

    filename = "%s_all%s"%(namespace,type)
    fout = os.path.join(path, filename)

    return util.makoWrite(
        fin, fout,
        namespace=namespace,
        tags=tags,
        files=files)

"""
    generates c/c++ include files from the specification documents
"""
def generate_cpp_include(path, namespace, tags, specs, meta):
    util.makePath(path)
    util.removeFiles(path, "*.h")
    util.removeFiles(path, "*.hpp")
    util.removeFiles(path, "*.inl")

    hloc, hfiles = generate_code(path, os.path.basename(path), namespace, tags, specs, meta, ".h")
    hpploc, hppfiles = generate_code(path, os.path.basename(path), namespace, tags, specs, meta, ".hpp")
    inlloc, inlfiles = generate_code(path, os.path.basename(path), namespace, tags, specs, meta, ".inl")

    hloc += generate_include_all(path, namespace, tags, hfiles, ".h")
    hpploc += generate_include_all(path, namespace, tags, hppfiles + inlfiles, ".hpp")

    return hloc + hpploc + inlloc

"""
Entry-point:
    generates all c/c++ code
"""
def generate_cpp(path, namespace, tags, specs, meta):
    loc = 0
    loc += generate_cpp_include(path, namespace, tags, specs, meta)
    print("Generated %s lines of code.\n"%loc)
