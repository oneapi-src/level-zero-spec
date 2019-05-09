import os
import re
import util

"""
    generates c/c++ files from the specification documents
"""
def generate_spec_cpp(path, namespace, tags, specs, meta, type):
    loc = 0
    template = "spec%s.mako"%type
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
    generates c/c++ files from the specification documents
"""
def generate_api_cpp(path, namespace, tags, specs, meta, files, type):
    loc = 0
    template = "api%s.mako"%type
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
    generates c/c++ files from the specification documents
"""
def generate_loader_cpp(path, section, namespace, tags, specs, meta, type):
    template = "loader%s.mako"%type
    fin = os.path.join("templates", template)

    name = "%s_loader"%section
    filename = "%s%s"%(name, type)
    fout = os.path.join(path, filename)

    print("Generating %s..."%fout)
    return util.makoWrite(
        fin, fout,
        name=name,
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta=meta)

"""
    generates c/c++ files from the specification documents
"""
def generate_validation_layer_cpp(path, section, namespace, tags, specs, meta, type):
    dstpath = os.path.join(path, "validation")
    template = "validation%s.mako"%type
    fin = os.path.join("templates", template)

    name = "%s_layer"%section
    filename = "%s%s"%(name, type)
    fout = os.path.join(dstpath, filename)

    print("Generating %s..."%fout)
    return util.makoWrite(
        fin, fout,
        name=name,
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta=meta)

"""
    generates c/c++ include files from the specification documents
"""
def generate_cpp(path, namespace, tags, specs, meta):
    util.makePath(path)
    util.removeFiles(path, "*.h")
    util.removeFiles(path, "*.hpp")
    util.removeFiles(path, "*.inl")

    hloc, hfiles = generate_spec_cpp(path, namespace, tags, specs, meta, ".h")
    hpploc, hppfiles = generate_spec_cpp(path, namespace, tags, specs, meta, ".hpp")
    inlloc, inlfiles = generate_spec_cpp(path, namespace, tags, specs, meta, ".inl")

    hloc += generate_api_cpp(path, namespace, tags, specs, meta, hfiles, ".h")
    hpploc += generate_api_cpp(path, namespace, tags, specs, meta, hppfiles + inlfiles, ".hpp")

    return hloc + hpploc + inlloc

"""
Entry-point:
    generates all c/c++ code
"""
def generate_api(path, namespace, tags, specs, meta):
    loc = 0
    loc += generate_cpp(path, namespace, tags, specs, meta)
    print("Generated %s lines of code.\n"%loc)

"""
Entry-point:
    generates loader for level_zero driver
"""
def generate_loader(path, section, namespace, tags, specs, meta):
    dstpath = os.path.join(path, "loader")
    util.makePath(dstpath)

    loc = 0
    loc += generate_loader_cpp(dstpath, section, namespace, tags, specs, meta, ".cpp")
    return loc

"""
Entry-point:
    generates validation layer for level_zero driver
"""
def generate_layers(path, section, namespace, tags, specs, meta):
    dstpath = os.path.join(path, "layers")
    util.makePath(dstpath)

    loc = 0
    loc += generate_validation_layer_cpp(dstpath, section, namespace, tags, specs, meta, ".cpp")
    return loc

