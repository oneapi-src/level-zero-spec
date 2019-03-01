import os
import re
import util

"""
    generates icd loader for level_zero driver
"""
def generate_icd_loader(outPath, namespace, specs, meta):
    loader_path = outPath
    util.makePath(loader_path)
    util.removeFiles(loader_path, "*.h")

    loc = 0

    mergedSpec = dict()
    mergedSpec['header'] = {'type': 'header', 'desc': 'Intel $Xx Driver Loader'}
    mergedSpec['name'] = 'loader'
    mergedSpec['objects'] = []
    for s in specs:
        mergedSpec['objects'] = mergedSpec['objects'] + s['objects']

    print("Generating %s..."%os.path.join(loader_path, "icd_loader.h"))
    loc += util.makoWrite(
        os.path.join("templates", "icd_loader.h.mako"),
        os.path.join(loader_path, "icd_loader.h"),
        x=namespace,
        X=namespace.upper(),
        Xx=namespace.title(),
        name = mergedSpec['name'],
        header = mergedSpec['header'],
        objects = mergedSpec['objects'])

    print("Generating %s..."%os.path.join(loader_path, "icd_loader.cpp"))
    loc += util.makoWrite(
        os.path.join("templates", "icd_loader.cpp.mako"),
        os.path.join(loader_path, "icd_loader.cpp"),
        x=namespace,
        X=namespace.upper(),
        Xx=namespace.title(),
        name = mergedSpec['name'],
        header = mergedSpec['header'],
        objects = mergedSpec['objects'])
    
    return loc
