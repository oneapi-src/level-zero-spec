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
def _mako_api_cpp(path, namespace, tags, specs, meta, ext):
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
        meta=meta)

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
def _mako_lib_cpp(path, namespace, tags, specs, meta):
    loc = 0
    template = "libapi.cpp.mako"
    fin = os.path.join("templates", template)

    name = "%s_libapi"%(namespace)
    filename = "%s.cpp"%(name)
    fout = os.path.join(path, filename)

    print("Generating %s..."%fout)
    loc += util.makoWrite(
        fin, fout,
        name = name,
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta = meta)

    template = "libddi.cpp.mako"
    fin = os.path.join("templates", template)

    name = "%s_libddi"%(namespace)
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
def _mako_wrapper_cpp(path, namespace, tags, specs, meta):
    loc = 0
    template = "wprapi.cpp.mako"
    fin = os.path.join("templates", template)

    name = "%s_wprapi"%(namespace)
    filename = "%s.cpp"%(name)
    fout = os.path.join(path, filename)

    print("Generating %s..."%fout)
    loc += util.makoWrite(
        fin, fout,
        name = name,
        namespace=namespace,
        tags=tags,
        specs=specs,
        meta = meta)
    return loc

"""
    generates c/c++ files from the specification documents
"""
def _mako_loader_cpp(path, namespace, tags, specs, meta):
    loc = 0
    template = "ldrddi.h.mako"
    fin = os.path.join("templates", template)

    name = "%s_ldrddi"%(namespace)
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

    name = "%s_ldrddi"%(namespace)
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
def _mako_validation_layer_cpp(path, namespace, tags, specs, meta):
    dstpath = os.path.join(path, "validation")
    util.makePath(dstpath)

    template = "valddi.cpp.mako"
    fin = os.path.join("templates", template)

    name = "%s_valddi"%(namespace)
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
def _mako_null_driver_cpp(path, namespace, tags, specs, meta):
    dstpath = os.path.join(path, "null")
    util.makePath(dstpath)

    template = "nullddi.cpp.mako"
    fin = os.path.join("templates", template)

    name = "%s_nullddi"%(namespace)
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

    loc = _mako_api_cpp(path, namespace, tags, specs, meta, ".h")
    loc += _mako_ddi_cpp(path, namespace, tags, specs, meta)

    return loc

"""
    generates c/c++ files from the specification documents
"""
def _generate_api_cpp(path, namespace, tags, specs, meta):
    util.makePath(path)

    loc = _mako_api_cpp(path, namespace, tags, specs, meta, ".hpp")

    return loc

"""
    generates python files from the specification documents
"""
def _generate_api_py(path, namespace, tags, specs, meta):
    util.makePath(path)

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
    dstpath = os.path.join(path, "lib")
    util.makePath(dstpath)

    loc = 0
    loc += _mako_lib_cpp(dstpath, namespace, tags, specs, meta)
    print("Generated %s lines of code.\n"%loc)

"""
Entry-point:
    generates loader for level_zero driver
"""
def generate_loader(path, section, namespace, tags, specs, meta):
    dstpath = os.path.join(path, "loader")
    util.makePath(dstpath)

    loc = 0
    loc += _mako_loader_cpp(dstpath, namespace, tags, specs, meta)
    print("Generated %s lines of code.\n"%loc)

"""
Entry-point:
    generates layers for level_zero driver
"""
def generate_layers(path, section, namespace, tags, specs, meta):
    dstpath = os.path.join(path, "layers")
    util.makePath(dstpath)

    loc = 0
    loc += _mako_validation_layer_cpp(dstpath, namespace, tags, specs, meta)
    print("Generated %s lines of code.\n"%loc)

"""
Entry-point:
    generates drivers for level_zero driver
"""
def generate_drivers(path, section, namespace, tags, specs, meta):
    dstpath = os.path.join(path, "drivers")
    util.makePath(dstpath)

    loc = 0
    loc += _mako_null_driver_cpp(dstpath, namespace, tags, specs, meta)
    print("Generated %s lines of code.\n"%loc)

"""
Entry-point:
    generates c++ wrapper for level_zero driver
"""
def generate_wrapper(path, section, namespace, tags, specs, meta):
    dstpath = os.path.join(path, "wrapper")
    util.makePath(dstpath)

    loc = 0
    loc += _generate_api_cpp(os.path.join(dstpath, "include"), namespace, tags, specs, meta)
    loc += _mako_wrapper_cpp(dstpath, namespace, tags, specs, meta)

    print("Generated %s lines of code.\n"%loc)
