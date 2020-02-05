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
def _mako_spec_cpp(path, namespace, tags, specs, meta, ext):
    loc = 0
    template = "spec%s.mako"%ext
    fin = os.path.join("templates", template)
    groupname = os.path.basename(os.path.normpath(path)).capitalize()

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
            meta = meta,
            groupname = groupname)
    return loc, files

"""
    generates c/c++ files from the specification documents
"""
def _mako_api_cpp(path, namespace, tags, specs, meta, files, ext):
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
def _mako_api_py(path, namespace, tags, specs, meta):
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
def _mako_ddi_cpp(path, namespace, tags, specs, meta):
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
def _mako_callbacks_cpp(path, namespace, tags, specs, meta):
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
def _mako_lib_cpp(path, namespace, tags, specs, meta):
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
def _mako_wrapper_cpp(path, namespace, tags, specs, meta):
    loc = 0
    template = "wprspec.cpp.mako"
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
    return loc, files

"""
    generates CMakeLists.txt file from the specification documents
"""
def _mako_lib_cmake(path, namespace, tags, files):
    template = "lib.cmake.mako"
    fin = os.path.join("templates", template)

    filename = "CMakeLists.txt"
    fout = os.path.join(path, filename)

    print("Generating %s..."%fout)
    return util.makoWrite(
        fin, fout,
        n=namespace,
        tags=tags,
        files=files)

"""
    generates CMakeLists.txt file for wrapper
"""
def _mako_wrapper_cmake(path, namespace, tags, files):
    template = "wpr.cmake.mako"
    fin = os.path.join("templates", template)

    filename = "CMakeLists.txt"
    fout = os.path.join(path, filename)

    print("Generating %s..."%fout)
    return util.makoWrite(
        fin, fout,
        n=namespace,
        tags=tags,
        files=files)

"""
    generates c/c++ files from the specification documents
"""
def _mako_loader_cpp(path, section, namespace, tags, specs, meta):
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
def _mako_validation_layer_cpp(path, section, namespace, tags, specs, meta):
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
def _mako_null_driver_cpp(path, section, namespace, tags, specs, meta):
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
def _generate_api_c(path, namespace, tags, specs, meta):
    util.makePath(path)
    util.removeFiles(path, "*.h")

    loc, files = _mako_spec_cpp(path, namespace, tags, specs, meta, ".h")
    loc += _mako_api_cpp(path, namespace, tags, specs, meta, files, ".h")
    loc += _mako_ddi_cpp(path, namespace, tags, specs, meta)

    if namespace != "zet": # todo: needs to be programmable
        loc += _mako_callbacks_cpp(path, namespace, tags, specs, meta)

    return loc

"""
    generates c/c++ files from the specification documents
"""
def _generate_api_cpp(path, namespace, tags, specs, meta):
    util.makePath(path)
    util.removeFiles(path, "*.hpp")

    loc, files = _mako_spec_cpp(path, namespace, tags, specs, meta, ".hpp")
    loc += _mako_api_cpp(path, namespace, tags, specs, meta, files, ".hpp")

    return loc

"""
    generates c/c++ files from the specification documents
"""
def _generate_lib_cpp(path, namespace, tags, specs, meta):
    util.makePath(path)

    loc, files = _mako_lib_cpp(path, namespace, tags, specs, meta)

    files.extend(["%s_lib.h"%namespace, "%s_lib.cpp"%namespace])
    _mako_lib_cmake(path, namespace, tags, files)

    return loc

"""
    generates python files from the specification documents
"""
def _generate_api_py(path, namespace, tags, specs, meta):
    util.makePath(path)
    util.removeFiles(path, "*.py")

    loc = _mako_api_py(path, namespace, tags, specs, meta)
    return loc

"""
Entry-point:
    generates api code
"""
def generate_api(path, namespace, tags, specs, meta):
    loc = 0
    loc += _generate_api_c(path, namespace, tags, specs, meta)
    loc += _generate_api_py(path, namespace, tags, specs, meta)
    print("Generated %s lines of code.\n"%loc)

"""
Entry-point:
    generates lib code
"""
def generate_lib(path, section, namespace, tags, specs, meta):
    dstpath = os.path.join(path, "lib", section)
    util.makePath(dstpath)

    loc = 0
    loc += _generate_lib_cpp(dstpath, namespace, tags, specs, meta)
    print("Generated %s lines of code.\n"%loc)

"""
Entry-point:
    generates loader for level_zero driver
"""
def generate_loader(path, section, namespace, tags, specs, meta):
    dstpath = os.path.join(path, "loader")
    util.makePath(dstpath)

    loc = 0
    loc += _mako_loader_cpp(dstpath, section, namespace, tags, specs, meta)
    print("Generated %s lines of code.\n"%loc)

"""
Entry-point:
    generates layers for level_zero driver
"""
def generate_layers(path, section, namespace, tags, specs, meta):
    dstpath = os.path.join(path, "layers")
    util.makePath(dstpath)

    loc = 0
    loc += _mako_validation_layer_cpp(dstpath, section, namespace, tags, specs, meta)
    print("Generated %s lines of code.\n"%loc)

"""
Entry-point:
    generates drivers for level_zero driver
"""
def generate_drivers(path, section, namespace, tags, specs, meta):
    dstpath = os.path.join(path, "drivers")
    util.makePath(dstpath)

    loc = 0
    loc += _mako_null_driver_cpp(dstpath, section, namespace, tags, specs, meta)
    print("Generated %s lines of code.\n"%loc)

"""
Entry-point:
    generates c++ wrapper for level_zero driver
"""
def generate_wrapper(path, section, namespace, tags, specs, meta):
    dstpath = os.path.join(path, "wrapper", section)
    util.makePath(dstpath)

    loc = 0
    loc += _generate_api_cpp(dstpath, namespace, tags, specs, meta)
    loc, files = _mako_wrapper_cpp(dstpath, namespace, tags, specs, meta)
    _mako_wrapper_cmake(dstpath, namespace, tags, files)

    print("Generated %s lines of code.\n"%loc)
