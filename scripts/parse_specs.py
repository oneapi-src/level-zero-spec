"""
 Copyright (C) 2019 Intel Corporation

 SPDX-License-Identifier: MIT

"""
import os
import util
import re
import hashlib
import json
from templates.helper import param_traits, type_traits, value_traits

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
    ver = float(d.get('version', default_version))
    if ver > max_ver:
        return None

    flt = []
    type = d['type']
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
            meta['class'][c]['ordinal'] = 0

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
            meta[type][name] = {'types': [], 'names': [], 'desc': [], 'class': ""}

        # add values to list
        if 'enum' == type:
            max_value = -1
            for idx, etor in enumerate(d['etors']):
                meta[type][name]['types'].append(etor['name'])
                if 'value' in etor:
                    ver = re.match(r"\$X_MAKE_VERSION\(\s*(\d+)\s*\,\s*(\d+)\s*\)", etor['value'])
                    if ver:
                        value = (int(ver.group(1)) << 16) + int(ver.group(2))
                    elif value_traits.is_bit(etor['value']):
                        value = 1 << int(value_traits.get_bit_count(etor['value']))
                    elif re.match(r"0x\w+", etor['value']):
                        value = int(etor['value'], 16)
                    else:
                        value = int(etor['value'])
                else:
                    value = max_value+1
                if value > max_value:
                    max_value = value
                    max_index = idx
            if type_traits.is_flag(name):
                meta[type][name]['max'] = hex((max_value << 1)-1)
            else:
                meta[type][name]['max'] = d['etors'][idx]['name']

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
                meta[type][name]['desc'].append(m['desc'])

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
    generate complete return permutations
"""
def _generate_returns(specs, meta):
    for s in specs:
        for obj in s['objects']:
            if re.match(r"function", obj['type']):
                # default results for all functions
                rets = [
                    {"$X_RESULT_SUCCESS":[]},
                    {"$X_RESULT_ERROR_UNINITIALIZED":[]},
                    {"$X_RESULT_ERROR_DEVICE_LOST":[]}
                    ]

                # special function for appending to our list of dicts; avoiding duplicates
                def _append(lst, key, val):
                    idx = next((i for i, v in enumerate(lst) if v.get(key)), len(lst))
                    if idx == len(lst):
                        rets.append({key:[]})
                    if val and val not in rets[idx][key]:
                        rets[idx][key].append(val)

                # generate results based on parameters
                for item in obj['params']:
                    if not param_traits.is_optional(item):
                        typename = type_traits.base(item['type'])

                        if type_traits.is_pointer(item['type']):
                            _append(rets, "$X_RESULT_ERROR_INVALID_NULL_POINTER", "`nullptr == %s`"%item['name'])

                        elif type_traits.is_handle(item['type']) and not type_traits.is_ipc_handle(item['type']):
                            _append(rets, "$X_RESULT_ERROR_INVALID_NULL_HANDLE", "`nullptr == %s`"%item['name'])

                        elif type_traits.is_enum(item['type'], meta):
                            _append(rets, "$X_RESULT_ERROR_INVALID_ENUMERATION", "`%s < %s`"%(meta['enum'][typename]['max'], item['name']))

                        if type_traits.is_descriptor(item['type']):
                            # walk each entry in the desc for pointers and enums
                            for i, mtype in enumerate(meta['struct'][typename]['types']):
                                mtypename = type_traits.base(mtype)

                                if type_traits.is_pointer(mtype) and not param_traits.is_optional({'desc': meta['struct'][typename]['desc'][i]}):
                                    _append(rets, "$X_RESULT_ERROR_INVALID_NULL_POINTER", "`nullptr == %s->%s`"%(item['name'], meta['struct'][typename]['names'][i]))

                                elif type_traits.is_enum(mtype, meta):
                                    if re.match(r"stype", meta['struct'][typename]['names'][i]):
                                        _append(rets, "$X_RESULT_ERROR_UNSUPPORTED_VERSION", "`%s != %s->stype`"%(re.sub(r"(\$\w)_(.*)_t.*", r"\1_STRUCTURE_TYPE_\2", typename).upper(), item['name']))
                                    else:
                                        _append(rets, "$X_RESULT_ERROR_INVALID_ENUMERATION", "`%s < %s->%s`"%(meta['enum'][mtypename]['max'], item['name'], meta['struct'][typename]['names'][i]))

                        elif type_traits.is_properties(item['type']):
                            # walk each entry in the properties
                            for i, mtype in enumerate(meta['struct'][typename]['types']):
                                if type_traits.is_enum(mtype, meta):
                                    if re.match(r"stype", meta['struct'][typename]['names'][i]):
                                        _append(rets, "$X_RESULT_ERROR_UNSUPPORTED_VERSION", "`%s != %s->stype`"%(re.sub(r"(\$\w)_(.*)_t.*", r"\1_STRUCTURE_TYPE_\2", typename).upper(), item['name']))

                # finally, append all user entries
                for item in obj.get('returns', []):
                    if isinstance(item, dict):
                        for key, values in item.items():
                            for val in values:
                                _append(rets, key, val)
                    else:
                        _append(rets, item, None)

                # update doc
                obj['returns'] = rets

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

        header = None
        objects = []

        for d in docs:
            d = _filter_version(d, float(version))
            if d:
                # extract header from objects
                if re.match(r"header", d['type']):
                    header = d
                    header['ordinal'] = int(int(header.get('ordinal',"1000")) * float(header.get('version',"1.0")))

                elif header:
                    hash = _generate_hash(d)
                    if hash:
                        d['hash'] = hash

                    objects.append(d)
                    meta = _generate_meta(d, header['ordinal'], meta)
                    ref = _generate_ref(d, tags, ref)

        if header:
            specs.append({
                'name'      : os.path.splitext(os.path.basename(f))[0],
                'header'    : header,
                'objects'   : objects
            })

    specs = sorted(specs, key=lambda s: s['header']['ordinal'])
    _generate_returns(specs, meta)

    print("Parsed %s files and found:"%len(specs))
    for key in meta:
        print(" - %s %s(s)"%(len(meta[key]),key))
    return specs, meta, ref
