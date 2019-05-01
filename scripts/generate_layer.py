import os
import re
import util

"""
    generic function for generating c/c++ files from the specification documents
"""
def generate_code(dstpath, section, namespace, tags, specs, type):
    template = "layer%s.mako"%type
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
        specs=specs)

"""
Entry-point:
    generates validation layer for level_zero driver
"""
def generate(section, namespace, tags, specs):
    dstpath = "../source/validation_layer"
    util.makePath(dstpath)

    loc = 0
    loc += generate_code(dstpath, section, namespace, tags, specs, ".h")
    loc += generate_code(dstpath, section, namespace, tags, specs, ".cpp")
    return loc
