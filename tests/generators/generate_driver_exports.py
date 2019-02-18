import os
import re
import util

"""
    generates exports table .def for UMD driver
"""
def generate_driver_exports(outPath, namespace, specs):
    loc = 0

    header = {'type': 'header', 'desc': 'Intel $Xx Driver Exports'}
    objects = []
    for s in specs:
        objects = objects + s['objects']

    filename = "driver_exports.def"
    fout = os.path.join(outPath, filename)
    print("Generating %s..."%fout)
    loc += util.makoWrite(
        os.path.join("templates", "driver_exports.def.mako"), fout,
        x=namespace,
        X=namespace.upper(),
        Xx=namespace.title(),
        name = "driver_exports",
        header = header,
        objects = objects)
        
    filename = "driver_exports_switches.cpp"
    fout = os.path.join(outPath, filename)
    print("Generating %s..."%fout)
    loc += util.makoWrite(
        os.path.join("templates", "driver_exports_switches.cpp.mako"), fout,
        x=namespace,
        X=namespace.upper(),
        Xx=namespace.title(),
        name = "driver_exports_switches",
        header = header,
        objects = objects)
    
    return loc
