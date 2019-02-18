import os
import re
import util

"""
    generates dynamic library loader .h for UMD driver
"""
def generate_driver_loader(outPath, namespace, specs):
    loader_path = outPath
    util.makePath(loader_path)
    util.removeFiles(loader_path, "*.h")

    loc = 0
    template = "driver_loader.h.mako"
    fin = os.path.join("templates", template)

    mergedSpec = dict()
    mergedSpec['header'] = {'type': 'header', 'desc': 'Intel $Xx Driver Loader'}
    mergedSpec['name'] = 'loader'
    mergedSpec['objects'] = []
    for s in specs:
        mergedSpec['objects'] = mergedSpec['objects'] + s['objects']

    filename = "driver_loader.h"
    fout = os.path.join(loader_path, filename)
    print("Generating %s..."%fout)
    loc += util.makoWrite(
        fin, fout,
        x=namespace,
        X=namespace.upper(),
        Xx=namespace.title(),
        name = mergedSpec['name'],
        header = mergedSpec['header'],
        objects = mergedSpec['objects'])
    
    return loc
