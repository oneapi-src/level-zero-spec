import os
import re
import util

"""
    generic function for generating c/c++ header files from the specification documents
"""
def generate_cpp_headers(path, namespace, tags, specs, meta, type):
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
            section=os.path.basename(path),
            namespace=namespace,
            tags=tags,
            specs=specs,
            meta = meta)
    return loc, files

"""
    generates a single c/c++ include file for the list of header files
"""
def generate_cpp_api(path, namespace, tags, specs, meta, files, type):
    loc = 0
    template = "api_all%s.mako"%type
    fin = os.path.join("templates", template)

    filename = "%s_api%s"%(namespace,type)
    fout = os.path.join(path, filename)

    print("Generating %s..."%fout)
    loc += util.makoWrite(
        fin, fout,
        section=os.path.basename(path),
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta=meta,
        files=files)
    return loc

"""
    generates c/c++ include files from the specification documents
"""
def generate_cpp(path, namespace, tags, specs, meta):
    util.makePath(path)
    util.removeFiles(path, "*.h")
    util.removeFiles(path, "*.hpp")
    util.removeFiles(path, "*.inl")

    hloc, hfiles = generate_cpp_headers(path, namespace, tags, specs, meta, ".h")
    hpploc, hppfiles = generate_cpp_headers(path, namespace, tags, specs, meta, ".hpp")
    inlloc, inlfiles = generate_cpp_headers(path, namespace, tags, specs, meta, ".inl")

    hloc += generate_cpp_api(path, namespace, tags, specs, meta, hfiles, ".h")
    hpploc += generate_cpp_api(path, namespace, tags, specs, meta, hppfiles + inlfiles, ".hpp")

    return hloc + hpploc + inlloc

"""
Entry-point:
    generates all c/c++ code
"""
def generate(path, namespace, tags, specs, meta):
    loc = 0
    loc += generate_cpp(path, namespace, tags, specs, meta)
    print("Generated %s lines of code.\n"%loc)
