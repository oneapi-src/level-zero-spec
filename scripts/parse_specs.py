import os
import util
import re

"""
    Reads each YML file and extracts data
    Returns list of data per file
"""
def parse(path):
    specs = []
    for f in util.findFiles(path, "*.yml"):
        print("Parsing %s..."%f)
        docs = util.yamlRead(f)

        header = {}
        objects = []

        for d in docs:
            if re.match(r"header", d['type']):
                header = d
            else:
                objects.append(d)

        specs.append({
            'name': os.path.splitext(os.path.basename(f))[0],
            'header': header,
            'objects': objects
        })
    return specs
