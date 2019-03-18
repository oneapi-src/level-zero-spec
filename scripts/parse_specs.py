import os
import util
import re
import hashlib

"""
    generates SHA512 string for the given object
"""
def generate_hash(d):
    h = None
    # functions-only (for now)...
    if re.match(r"function", d['type']):
        fh = hashlib.sha256()
        # hashcode of function signature...
        fh.update(d['name'].encode())
        for p in d['params']:
            fh.update(p['type'].encode())
        # hashcode of class
        if 'class' in d:
            fh.update(d['class'].encode())
        # digest into string
        h = fh.hexdigest()
    return h

"""
    generates meta-data on all objects
"""
def generate_meta(d, meta):
    type = d['type']
    name = re.sub(r"(\w+)\(.*\)", r"\1", d['name']) # removes '()' part of macros

    if 'class' in d:
        c = d['class']
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

    if 'class' != type:
        # create dict if typename is not already known...
        if type not in meta:
            meta[type] = {}

        # create list if name is not already known for type...
        if 'function' == type and 'class' in d:
            name = d['class']+name

        if name not in meta[type]:
            meta[type][name] = []

        # add values to list
        if 'enum' == type:
            for etor in d['etors']:
                meta[type][name].append(etor['name'])
        elif 'macro' == type:   
            if 'value' in d:
                meta[type][name].append(d['value'])
            if 'altvalue' in d:
                meta[type][name].append(d['altvalue'])
        elif 'function' == type:
            for p in d['params']:
                meta[type][name].append(p['type'])
        elif 'struct' == type:
            for m in d['members']:
                meta[type][name].append(m['type'])
        elif 'class' in d:
            meta[type][name].append(d['class'])

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
                d['hash'] = generate_hash(d)
                objects.append(d)
                meta = generate_meta(d, meta)

        specs.append({
            'name'      : os.path.splitext(os.path.basename(f))[0],
            'header'    : header,
            'objects'   : objects
        })

    print("Parsed %s files and found:"%len(specs))
    print(" - %s classes"%len(meta['class']))
    print(" - %s functions"%len(meta['function']))
    print(" - %s structs"%len(meta['struct']))
    print(" - %s enums"%len(meta['enum']))
    print(" - %s macros\n"%len(meta['macro']))
    return specs, meta
