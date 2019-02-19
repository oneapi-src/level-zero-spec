import os
import util
import re



"""
Entry-point:
    Reads each YML file and extracts data
    Returns list of data per file
"""
def parse(path):
    specs = []
    meta = {
        'class' : {}
    }
    for f in util.findFiles(path, "*.yml"):
        print("Parsing %s..."%f)
        docs = util.yamlRead(f)

        header = {}
        objects = []

        for d in docs:
            # extract header from objects
            if re.match(r"header", d['type']):
                header = d
            else:
                objects.append(d)

                # generate meta-data
                if 'class' in d:
                    cl = d['class'] if isinstance(d['class'], list) else [d['class']]
                    for c in cl:
                        if c not in meta['class']:
                            meta['class'][c] = {}

                        if d['type'] not in meta['class'][c]:
                            meta['class'][c][d['type']] = []

                        if d['name'] not in meta['class'][c][d['type']]:
                            meta['class'][c][d['type']].append(d['name'])

                else:
                    if d['type'] not in meta:
                        meta[d['type']] = []

                    if d['name'] not in meta[d['type']]:
                        meta[d['type']].append(d['name'])

        specs.append({
            'name'      : os.path.splitext(os.path.basename(f))[0],
            'header'    : header,
            'objects'   : objects
        })
    return specs, meta
