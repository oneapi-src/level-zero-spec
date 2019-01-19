import os
import util

"""
    Reads each YML file and extracts data
    Returns list of data per file
"""
def parse(path):
    specs = []
    for f in util.findFiles(path, "*.yml"):
        print("Parsing %s..."%f)
        specs.append({
            'name': os.path.splitext(os.path.basename(f))[0],
            'docs': util.yamlRead(f)
        })
    return specs
