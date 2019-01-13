import os
import util
import glob

"""
    Reads each YML file and extracts data
    Returns list of data per file
"""
def parse(path):
    specs = []
    files = glob.glob(os.path.join(path,"*.yml"))
    for f in files:
        print("Parsing %s..."%f)
        specs.append({
            'name': os.path.splitext(os.path.basename(f))[0],
            'docs': util.yamlRead(f)
        })
    #util.jsonWrite("specs.json", specs);
    return specs
