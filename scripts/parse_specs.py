import os
import util
import re
import hashlib

"""
    generate a list of classes this object belongs to
"""
def get_class_list(d):
    if 'class' in d:
        return d['class'] if isinstance(d['class'], list) else [d['class']]
    else:
        return ['none']

"""
    generates SHA512 string for the given object
"""
def generate_hash(d):
    hl = []
    # functions-only (for now)...
    if re.match(r"function", d['type']):
        fh = hashlib.sha256()
        # hashcode of function signature...
        fh.update(d['name'].encode())
        for p in d['params']:
            fh.update(p['type'].encode())
        # hashcode per-class...
        for c in d['class']:
            ch = fh
            ch.update(c.encode())
            hl.append(ch.hexdigest())
    return hl

"""
    generates meta-data on all objects
"""
def generate_meta(d, meta):
    type = d['type']
    name = re.sub(r"(\w+)\(.*\)", r"\1", d['name']) # removes '()' part of macros

    for c in d['class']:
        # create dict if class name is not already known...
        if c not in meta['class']:
            meta['class'][c] = {}

        # create list if object-type is not already known for class...
        if type not in meta['class'][c]:
            meta['class'][c][type] = []

        # append if object-name is not already known for object-type in class...
        if name not in meta['class'][c][type]:
            meta['class'][c][type].append(name)
        else:
            print("Error - duplicate entries found!")
            raise

    if 'enum' == type or 'macro' == type:
        # create dict if typename is not already known...
        if type not in meta:
            meta[type] = {}

        # create list if name is not already known for type...
        if name not in meta[type]:
            meta[type][name] = []

        # add values to list
        if 'etors' in d:
            for etor in d['etors']:
                meta[type][name].append(etor['name'])
        else:   
            if 'value' in d:
                meta[type][name].append(d['value'])
            if 'altvalue' in d:
                meta[type][name].append(d['altvalue'])

    return meta

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
                d['class'] = get_class_list(d)
                d['hash'] = generate_hash(d)
                objects.append(d)
                meta = generate_meta(d, meta)

        specs.append({
            'name'      : os.path.splitext(os.path.basename(f))[0],
            'header'    : header,
            'objects'   : objects
        })

    # for debug purposes
    #util.jsonWrite("specs.json", specs)
    #util.jsonWrite("meta.json", meta)
    return specs, meta
