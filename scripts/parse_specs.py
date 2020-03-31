"""
 Copyright (C) 2019 Intel Corporation

 SPDX-License-Identifier: MIT

"""
import os
import util
import re
import hashlib
import json

"""
    validate documents meet some basic requirements of code generation
"""
def _validate_doc(d):
    for item in d:
        # error: struct/unions may not contain handles
        # error: invalid/unknown tag
        # warning: enum/etor mismatch
        # error: if not static or global, then first parameter must be handle/class
        # warning: first member of descriptor must be version
        # error: missing range in desc
        pass

"""
    filters object by version
"""
def _filter_version(d, max_ver):
    default_version = "1.0"
    type = d['type']
    ver = float(d.get('version', default_version))
    if ver > max_ver:
        return None

    flt = []
    if 'enum' == type:
        for e in d['etors']:
            ver = float(e.get('version', default_version))
            if ver <= max_ver:
                flt.append(e)
        if d['name'].endswith('version_t'):
            flt.append({
                'name': d['name'][:-1].upper() + "CURRENT",
                'value': flt[-1]['value'],
                'desc': "latest known version"
                })
        d['etors'] = flt

    elif 'function' == type:
        for p in d['params']:
            ver = float(p.get('version', default_version))
            if ver <= max_ver:
                flt.append(p)
        d['params'] = flt

    elif 'struct' == type or 'union' == type or 'class' == type:
        for m in d.get('members',[]):
            ver = float(m.get('version', default_version))
            if ver <= max_ver:
                flt.append(m)
        d['members'] = flt

    return d

"""
    generates SHA512 string for the given object
"""
def _generate_hash(d):
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
def _generate_meta(d, ordinal, meta):
    type = d['type']
    name = re.sub(r"(\w+)\(.*\)", r"\1", d['name']) # removes '()' part of macros

    if 'class' in d:
        c = d['class']
        # create dict if class name is not already known...
        if c not in meta['class']:
            meta['class'][c] = {}
            meta['class'][c]['ordinal'] = "0"

        # create list if object-type is not already known for class...
        if type not in meta['class'][c]:
            meta['class'][c][type] = []

        # append if object-name is not already known for object-type in class...
        if name not in meta['class'][c][type]:
            meta['class'][c][type].append(name)

        else:
            print("Error - duplicate entries for %s found!"%name)
            raise

    if 'class' != type:
        # create dict if typename is not already known...
        if type not in meta:
            meta[type] = {}

        # create list if name is not already known for type...
        if 'function' == type and 'class' in d:
            name = d['class']+name

        if name not in meta[type]:
            meta[type][name] = {'types': [], 'names': [], 'class': ""}

        # add values to list
        if 'enum' == type:
            max_value = -1
            for etor in d['etors']:
                meta[type][name]['types'].append(etor['name'])
                if 'value' in etor:
                    ver = re.match(r"\$X_MAKE_VERSION\(\s*(\d+)\s*\,\s*(\d+)\s*\)", etor['value'])
                    mask = re.match(r"\$X_BIT\(\s*(\d+)\s*\)", etor['value'])
                    if ver:
                        value = (int(ver.group(1)) << 16) + int(ver.group(2))
                    elif mask:
                        value = 1 << int(mask.group(1))
                    elif re.match(r"0x\w+", etor['value']):
                        value = int(etor['value'], 16)
                    else:
                        value = int(etor['value'])
                else:
                    value = max_value+1
                max_value = max(max_value, value)
            meta[type][name]['max'] = str(max_value)

        elif 'macro' == type:
            if 'value' in d:
                meta[type][name]['types'].append(d['value'])

            if 'altvalue' in d:
                meta[type][name]['types'].append(d['altvalue'])

        elif 'function' == type:
            for p in d['params']:
                meta[type][name]['types'].append(p['type'])

        elif 'struct' == type or 'union' == type:
            for m in d['members']:
                meta[type][name]['types'].append(m['type'])
                meta[type][name]['names'].append(m['name'])

        if 'class' in d:
            meta[type][name]['class'] = d['class']

    else:
        if name not in meta['class']:
            meta['class'][name] = {}

        meta['class'][name]['ordinal'] = ordinal

        if'base' in d:
            base = d['base']
            if 'child' not in meta['class'][base]:
                meta['class'][base]['child'] = []

            meta['class'][base]['child'].append(name)

        if 'members' in d:
            meta['class'][name]['members'] = []

            for m in d['members']:
                meta['class'][name]['members'].append(m['type'])

        if 'owner' in d:
            owner = d['owner']
            meta['class'][name]['owner'] = owner

            if owner not in meta['class']:
                meta['class'][owner] = {}

            if 'owns' not in meta['class'][owner]:
                meta['class'][owner]['owns'] = []

            meta['class'][owner]['owns'].append(name)

    return meta

"""
    generates reference-data on all objects
"""
def _generate_ref(d, tags, ref):
    # create dict if typename is not already known...
    type = d['type']
    if type not in ref:
        ref[type] = {}

    name = re.sub(r"(\w+)\(.*\)", r"\1", d['name']) # removes '()' part of macros

    # convert dict to json-string
    dstr = json.dumps(d)

    # replace all tags with values
    for key, value in tags.items():
        dstr = re.sub(r"-%s"%re.escape(key), "-"+value, dstr)
        dstr = re.sub(re.escape(key), value, dstr)
        dstr = re.sub(re.escape(key.upper()), value.upper(), dstr)

        name = re.sub(re.escape(key), value, name)
        name = re.sub(re.escape(key.upper()), value.upper(), name)

    # convert json-string back to dict
    d = json.loads(dstr)

    # update ref
    ref[type][name] = d
    return ref


"""
Entry-point:
    Reads each YML file and extracts data
    Returns list of data per file
"""
def parse(path, version, tags, meta = {'class':{}}, ref = {}):
    specs = []
    for f in util.findFiles(path, "*.yml"):
        print("Parsing %s..."%f)
        docs = util.yamlRead(f)

        header = {}
        objects = []

        for d in docs:
            # extract header from objects
            if re.match(r"header", d['type']):
                header = d
                if 'includes' not in header:
                    header['includes'] = []

                if 'ordinal' not in header:
                    header['ordinal'] = "9999"

            else:
                d = _filter_version(d, float(version))
                if d:
                    hash = _generate_hash(d)
                    if hash:
                        d['hash'] = hash

                    objects.append(d)
                    meta = _generate_meta(d, header['ordinal'], meta)
                    ref = _generate_ref(d, tags, ref)

        specs.append({
            'name'      : os.path.splitext(os.path.basename(f))[0],
            'header'    : header,
            'objects'   : objects
        })

    print("Parsed %s files and found:"%len(specs))
    for key in meta:
        print(" - %s %s(s)"%(len(meta[key]),key))
    return sorted(specs, key=lambda x: x['header']['ordinal']), meta, ref
