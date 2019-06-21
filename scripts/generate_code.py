"""
 Copyright (C) 2019 Intel Corporation

 SPDX-License-Identifier: MIT

"""
import os
import re
import util

"""
    generates c/c++ files from the specification documents
"""
def mako_spec_cpp(path, namespace, tags, specs, meta, ext):
    loc = 0
    template = "spec%s.mako"%ext
    fin = os.path.join("templates", template)

    files = []
    for s in specs:
        filename = "%s_%s%s"%(namespace, s['name'], ext)
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
def mako_api_cpp(path, namespace, tags, specs, meta, files, ext):
    template = "api%s.mako"%ext
    fin = os.path.join("templates", template)

    filename = "%s_api%s"%(namespace,ext)
    fout = os.path.join(path, filename)

    print("Generating %s..."%fout)
    return util.makoWrite(
        fin, fout,
        section=os.path.basename(path),
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta=meta,
        files=files)

"""
    generates c/c++ files from the specification documents
"""
def mako_api_py(path, namespace, tags, specs, meta):
    template = "api.py.mako"
    fin = os.path.join("templates", template)

    filename = "%s.py"%(namespace)
    fout = os.path.join(path, filename)

    print("Generating %s..."%fout)
    return util.makoWrite(
        fin, fout,
        section=os.path.basename(path),
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta=meta)

"""
    generates c/c++ files from the specification documents
"""
def mako_ddi_cpp(path, namespace, tags, specs, meta):
    template = "ddi.h.mako"
    fin = os.path.join("templates", template)

    filename = "%s_ddi.h"%(namespace)
    fout = os.path.join(path, filename)

    print("Generating %s..."%fout)
    return util.makoWrite(
        fin, fout,
        section=os.path.basename(path),
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta=meta)

"""
    generates c/c++ files from the specification documents
"""
def mako_callbacks_cpp(path, namespace, tags, specs, meta):
    template = "callbacks.h.mako"
    fin = os.path.join("templates", template)

    filename = "%s_callbacks.h"%(namespace)
    fout = os.path.join(path, filename)

    print("Generating %s..."%fout)
    return util.makoWrite(
        fin, fout,
        section=os.path.basename(path),
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta=meta)

"""
    generates c/c++ files from the specification documents
"""
def mako_lib_cpp(path, namespace, tags, specs, meta):
    loc = 0
    template = "libspec.cpp.mako"
    fin = os.path.join("templates", template)

    files = []
    for s in specs:
        filename = "%s_%s.cpp"%(namespace, s['name'])
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

    template = "libddi.cpp.mako"
    fin = os.path.join("templates", template)

    name = "%s_%s_lib"%(namespace, os.path.basename(path))
    filename = "%s.cpp"%(name)
    files.append(filename)
    fout = os.path.join(path, filename)

    print("Generating %s..."%fout)
    loc += util.makoWrite(
        fin, fout,
        name=name,
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta=meta)
    return loc, files

"""
    generates c/c++ files from the specification documents
"""
def mako_cmake_cpp(path, namespace, files):
    template = "lib.cmake.mako"
    fin = os.path.join("templates", template)

    filename = "CMakeLists.txt"
    fout = os.path.join(path, filename)

    print("Generating %s..."%fout)
    return util.makoWrite(
        fin, fout,
        n=namespace,
        files=files)

"""
    generates c/c++ files from the specification documents
"""
def mako_loader_cpp(path, section, namespace, tags, specs, meta):
    loc = 0
    template = "ldrddi.h.mako"
    fin = os.path.join("templates", template)

    name = "%s_%s_loader"%(tags['$x'], section)
    filename = "%s.h"%(name)
    fout = os.path.join(path, filename)

    print("Generating %s..."%fout)
    loc += util.makoWrite(
        fin, fout,
        name=name,
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta=meta)

    template = "ldrddi.cpp.mako"
    fin = os.path.join("templates", template)

    name = "%s_%s_loader"%(tags['$x'], section)
    filename = "%s.cpp"%(name)
    fout = os.path.join(path, filename)

    print("Generating %s..."%fout)
    loc += util.makoWrite(
        fin, fout,
        name=name,
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta=meta)
    return loc

"""
    generates c/c++ files from the specification documents
"""
def mako_validation_layer_cpp(path, section, namespace, tags, specs, meta):
    dstpath = os.path.join(path, "validation")
    util.makePath(dstpath)

    template = "valddi.cpp.mako"
    fin = os.path.join("templates", template)

    name = "%s_%s_layer"%(tags['$x'], section)
    filename = "%s.cpp"%(name)
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
    generates c/c++ files from the specification documents
"""
def mako_null_driver_cpp(path, section, namespace, tags, specs, meta):
    dstpath = os.path.join(path, "null")
    util.makePath(dstpath)

    template = "nullddi.cpp.mako"
    fin = os.path.join("templates", template)

    name = "%s_%s_driver"%(tags['$x'], section)
    filename = "%s.cpp"%(name)
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
    generates c/c++ files from the specification documents
"""
def generate_api_cpp(path, namespace, tags, specs, meta):
    util.makePath(path)
    util.removeFiles(path, "*.h")
    util.removeFiles(path, "*.hpp")
    util.removeFiles(path, "*.inl")

    hloc, hfiles = mako_spec_cpp(path, namespace, tags, specs, meta, ".h")
    hpploc, hppfiles = mako_spec_cpp(path, namespace, tags, specs, meta, ".hpp")

    hloc += mako_api_cpp(path, namespace, tags, specs, meta, hfiles, ".h")
    hpploc += mako_api_cpp(path, namespace, tags, specs, meta, hppfiles, ".hpp")

    hloc += mako_ddi_cpp(path, namespace, tags, specs, meta)

    if namespace != "xet": # todo: needs to be programmable
        hloc += mako_callbacks_cpp(path, namespace, tags, specs, meta)

    return hloc + hpploc

"""
    generates c/c++ files from the specification documents
"""
def generate_lib_cpp(path, namespace, tags, specs, meta):
    util.makePath(path)

    loc, files = mako_lib_cpp(path, namespace, tags, specs, meta)

    files.extend(["%s_lib.h"%namespace, "%s_lib.cpp"%namespace])
    mako_cmake_cpp(path, namespace, files)

    return loc

"""
    generates python files from the specification documents
"""
def generate_api_py(path, namespace, tags, specs, meta):
    util.makePath(path)
    util.removeFiles(path, "*.py")

    loc = mako_api_py(path, namespace, tags, specs, meta)
    return loc

"""
Entry-point:
    generates api code
"""
def generate_api(path, namespace, tags, specs, meta):
    loc = 0
    loc += generate_api_cpp(path, namespace, tags, specs, meta)
    loc += generate_api_py(path, namespace, tags, specs, meta)
    print("Generated %s lines of code.\n"%loc)

"""
Entry-point:
    generates lib code
"""
def generate_lib(path, namespace, tags, specs, meta):
    loc = 0
    loc += generate_lib_cpp(path, namespace, tags, specs, meta)
    print("Generated %s lines of code.\n"%loc)

"""
Entry-point:
    generates loader for level_zero driver
"""
def generate_loader(path, section, namespace, tags, specs, meta):
    dstpath = os.path.join(path, "loader")
    util.makePath(dstpath)

    loc = 0
    loc += mako_loader_cpp(dstpath, section, namespace, tags, specs, meta)
    return loc

"""
Entry-point:
    generates layers for level_zero driver
"""
def generate_layers(path, section, namespace, tags, specs, meta):
    dstpath = os.path.join(path, "layers")
    util.makePath(dstpath)

    loc = 0
    loc += mako_validation_layer_cpp(dstpath, section, namespace, tags, specs, meta)
    loc += mako_null_driver_cpp(dstpath, section, namespace, tags, specs, meta)
    return loc
