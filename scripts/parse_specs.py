"""
 Copyright (C) 2019 Intel Corporation

 SPDX-License-Identifier: MIT

"""
import os
import util
import re
import hashlib
import json
import yaml
from templates.helper import param_traits, type_traits, value_traits

default_version = "1.0"

"""
    substitute tags
"""
def _subt(name, tags):
    name = re.sub(r"(\w+)\(.*\)", r"\1", name) # removes '()' part of macros
    for key, value in tags.items():
        name = re.sub(re.escape(key), value, name)
        name = re.sub(re.escape(key.upper()), value.upper(), name)
    return name

"""
    get the line number of each document
"""
def _get_line_nums(f):
    nums = []
    for line_num, line in enumerate(util.textRead(f)):
        if re.match(r"^\-\-\-.*", line):
            nums.append(line_num+2)
    return nums

"""
    validate documents meet some basic (easily detectable) requirements of code generation
"""
def _validate_doc(f, d, tags, line_num):
    is_iso = lambda x : re.match(r"[_a-zA-Z][_a-zA-Z0-9]{0,30}", x)

    def __validate_ordinal(d):
        if 'ordinal' in d:
            if not isinstance(d['ordinal'], str):
                raise Exception("'ordinal' must be a string: '%s'"%type(d['ordinal']))

            try:
                ordinal = str(int(d['ordinal']))
            except:
                ordinal = None

            if ordinal != d['ordinal']:
                raise Exception("'ordinal' invalid value: '%s'"%d['ordinal'])   

    def __validate_version(d, prefix=""):
        if 'version' in d:
            if not isinstance(d['version'], str):
                raise Exception(prefix+"'version' must be a string: '%s'"%type(d['version']))

            try:
                version = str(float(d['version']))
            except:
                version = None

            if version != d['version']:
                raise Exception(prefix+"'version' invalid value: '%s'"%d['version'])

        return float(d.get('version', default_version))

    def __validate_tag(d, key, tags, case):
        for x in tags:
            if d[key].startswith(x.upper() if case == 'upper' else x):
                return x
        return None

    def __validate_desc(desc):
        for x in ['[in]', '[out]', '[in,out]']:
            if desc.startswith(x):
                return x
        return None

    def __validate_name(d, key, tags, case='lower', prefix=""):
        if not isinstance(d[key], str):
            raise Exception(prefix+"'%s' must be a string: '%s'"%(key, type(d[key])))

        if not __validate_tag(d, key, tags, case):
            raise Exception(prefix+"'%s' must start with {%s}: '%s'"%(key, ", ".join([x.upper() if case == 'upper' else x for x in tags if x != "$OneApi"]), d[key]))

        name = _subt(d[key], tags)
        if not is_iso(name):
            raise Exception(prefix+"'%s' must be ISO-C: '%s'"%(key, d[key]))

        if case == 'upper' and not name.isupper():
            raise Exception(prefix+"%s' must be upper case: '%s'"%(key, d[key]))
        elif case == 'lower' and not name.islower():
            raise Exception(prefix+"'%s' must be lower case: '%s'"%(key, d[key]))
        elif case == 'camel' and (name.isupper() or name.islower()):
            raise Exception(prefix+"'%s' must be camel case: '%s'"%(key, d[key]))

    def __validate_type(d, key, tags):
        __validate_name(d, key, tags)

        if not d[key].endswith("_t"):
            raise Exception("'%s' must end with '_t': '%s'"%(key, d[key]))

    def __validate_handle(d, key, tags):
        __validate_type(d, key, tags)

        if not d[key].endswith("handle_t"):
            raise Exception("'%s' must end with 'handle_t': '%s'"%(key, d[key]))

    def __validate_details(d):
        if 'details' in d:
            if not isinstance(d['details'], list):
                raise Exception("'details' must be a sequence: '%s'"%type(d['details']))

            for i, item in enumerate(d['details']):
                prefix = "'details'[%s] "%i
                if isinstance(item, dict):
                    for key in item:
                        if not isinstance(key, str):
                            raise Exception(prefix+"must be a string: '%s'"%type(key))

                        for j, val in enumerate(item[key]):
                            prefix2 = prefix[:-1]+"[%s] "%j
                            if not isinstance(val, str):
                                raise Exception(prefix2+"must be a string: '%s'"%type(val))

                elif not isinstance(item, str):
                    raise Exception(prefix+"must be a string: '%s'"%type(item))

    def __validate_etors(d, tags):
        if 'etors' not in d:
            raise Exception("'enum' requires the following sequence of mappings: {`etors`}")

        if not isinstance(d['etors'], list):
            raise Exception("'etors' must be a sequence: '%s'"%type(d['etors']))

        max_ver = float(default_version)
        for i, item in enumerate(d['etors']):
            prefix="'etors'[%s] "%i
            if not isinstance(item, dict):
                raise Exception(prefix+"must be a mapping: '%s'"%(i, type(item)))

            if ('desc' not in item) or ('name' not in item):
                raise Exception(prefix+"requires the following scalar fields: {`desc`, `name`}")

            __validate_name(item, 'name', tags, case='upper', prefix=prefix)
            if not item['name'].startswith(d['name'][:-2].upper()):
                raise Exception(prefix+"'name' must start with enum 'name': %s"%item['name'])

            ver = __validate_version(item, prefix=prefix)
            if ver < max_ver:
                raise Exception(prefix+"'version' must be increasing: %s"%item['version'])
            max_ver = ver

    def __validate_base(d):
        namespace = re.sub(r"(\$[a-z])\w+", r"\1", d['name'])
        if type_traits.is_descriptor(d['type']) and not d.get('base', "").endswith("base_desc_t"):
            raise Exception(prefix+"'base' must be '%s_base_desc_t': %s"%(namespace, item['type']))

        elif type_traits.is_properties(d['type']) and not d.get('base', "").endswith("base_properties_t"):
            raise Exception(prefix+"'base' must be '%s_base_properties_t': %s"%(namespace, item['type']))

    def __validate_members(d, tags):
        if 'members' not in d:
            raise Exception("'%s' requires the following sequence of mappings: {`members`}"%d['type'])

        if not isinstance(d['members'], list):
            raise Exception("'members' must be a sequence: '%s'"%type(d['members']))

        max_ver = float(default_version)
        for i, item in enumerate(d['members']):
            prefix="'members'[%s] "%i
            if not isinstance(item, dict):
                raise Exception(prefix+"must be a mapping: '%s'"%(i, type(item)))

            if ('desc' not in item) or ('type' not in item) or ('name' not in item):
                raise Exception(prefix+"requires the following scalar fields: {`desc`, 'type', `name`}")

            annotation = __validate_desc(item['desc'])
            if not annotation:
                raise Exception(prefix+"'desc' must start with {'[in]', '[out]', '[in,out]'}")

            if type_traits.is_handle(item['type']):
                raise Exception(prefix+"'type' must not be '*_handle_t': %s"%item['type'])

            ver = __validate_version(item, prefix=prefix)
            if ver < max_ver:
                raise Exception(prefix+"'version' must be increasing: %s"%item['version'])
            max_ver = ver

    def __validate_params(d, tags):
        if 'params' not in d:
            raise Exception("'function' requires the following sequence of mappings: {`params`}")

        if not isinstance(d['params'], list):
            raise Exception("'params' must be a sequence: '%s'"%type(d['params']))

        max_ver = float(default_version)
        min = {'[in]': None, '[out]': None, '[in,out]': None}
        for i, item in enumerate(d['params']):
            prefix="'params'[%s] "%i
            if not isinstance(item, dict):
                raise Exception(prefix+"must be a mapping: '%s'"%(i, type(item)))

            if ('desc' not in item) or ('type' not in item) or ('name' not in item):
                raise Exception(prefix+"requires the following scalar fields: {`desc`, 'type', `name`}")

            annotation = __validate_desc(item['desc'])
            if not annotation:
                raise Exception(prefix+"'desc' must start with {'[in]', '[out]', '[in,out]'}")

            if not min[annotation]:
                min[annotation] = i

            if min['[out]'] and ("[in]" == annotation or "[in,out]" == annotation):
                raise Exception(prefix+"'%s' must come before '[out]'"%annotation)

            # todo: if not static or singleton, then first must be handle_t

            ver = __validate_version(item, prefix=prefix)
            if ver < max_ver:
                raise Exception(prefix+"'version' must be increasing: %s"%item['version'])
            max_ver = ver

    try:
        if 'type' not in d:
            raise Exception("every document must have 'type'")

        if not isinstance(d['type'], str):
            raise Exception("'type' must be a string: '%s'"%type(d['type']))

        if 'header' == d['type']:
            if 'desc' not in d:
                raise Exception("'header' requires the following scalar fields: {`desc`}")

            if not isinstance(d['desc'], str):
                raise Exception("'desc' must be a string")

            __validate_ordinal(d)
            __validate_version(d)

        elif 'macro' == d['type']:
            if ('desc' not in d) or ('name' not in d) or ('value' not in d):
                raise Exception("'macro' requires the following scalar fields: {`desc`, `name`, `value`}")

            if not isinstance(d['desc'], str):
                raise Exception("'desc' must be a string")

            __validate_name(d, 'name', tags, case='upper')
            __validate_details(d)
            __validate_ordinal(d)
            __validate_version(d)

        elif 'typedef' == d['type']:
            if ('desc' not in d) or ('name' not in d) or ('value' not in d):
                raise Exception("'typedef' requires the following scalar fields: {`desc`, `name`, `value`}")

            __validate_type(d, 'name', tags)
            __validate_details(d)
            __validate_ordinal(d)
            __validate_version(d)

        elif 'handle' == d['type']:
            if ('desc' not in d) or ('name' not in d):
                raise Exception("'handle' requires the following scalar fields: {`desc`, `name`}")

            __validate_handle(d, 'name', tags)
            __validate_details(d)
            __validate_ordinal(d)
            __validate_version(d)

        elif 'enum' == d['type']:
            if ('desc' not in d) or ('name' not in d):
                raise Exception("'enum' requires the following scalar fields: {`desc`, `name`}")

            __validate_type(d, 'name', tags)
            __validate_etors(d, tags)
            __validate_details(d)
            __validate_ordinal(d)
            __validate_version(d)

        elif 'struct' == d['type'] or 'union' == d['type']:
            if ('desc' not in d) or ('name' not in d):
                raise Exception("'%s' requires the following scalar fields: {`desc`, `name`}"%d['type'])

            __validate_type(d, 'name', tags)
            __validate_base(d)
            __validate_members(d, tags)
            __validate_details(d)
            __validate_ordinal(d)
            __validate_version(d)

        elif 'function' == d['type']:
            if ('desc' not in d) or ('name' not in d):
                raise Exception("'function' requires the following scalar fields: {`desc`, `name`}")

            if 'class' in d:
                __validate_name({'name': d['class']+d['name']}, 'name', tags, case='camel')
            else:
                __validate_name(d, 'name', tags, case='camel')

            __validate_params(d, tags)
            __validate_details(d)
            __validate_ordinal(d)
            __validate_version(d)

        elif 'class' == d['type']:
            if ('desc' not in d) or ('name' not in d):
                raise Exception("'class' requires the following scalar fields: {`desc`, `name`}")

            __validate_name(d, 'name', tags, case='camel')
            __validate_details(d)
            __validate_ordinal(d)
            __validate_version(d)

        return True

    except Exception as msg:
        print("Specification Validation Error:")
        print("%s(%s): %s!"%(os.path.abspath(f), line_num, msg))
        return True

"""
    filters object by version
"""
def _filter_version(d, max_ver):
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
            meta[type][name] = {'types': [], 'names': [], 'desc': [], 'init': [], 'class': ""}

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
                meta[type][name]['max'] = hex((max_value << 1)-1) if max_value else '0'
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
                meta[type][name]['init'].append(m.get('init'))

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
    generates SHA512 string for the given object
"""
def _generate_hash(obj):
    # functions-only (for now)...
    if re.match(r"function", obj['type']):
        hash = hashlib.sha256()
        # hashcode of function signature...
        hash.update(obj['name'].encode())
        for p in obj['params']:
            hash.update(p['type'].encode())
        # hashcode of class
        if 'class' in obj:
            hash.update(obj['class'].encode())
        # digest into string
        obj['hash'] = hash.hexdigest()
    return obj

"""
    generates structure members from base
"""
def _inline_base(obj, meta):
    if re.match(r"struct|union", obj['type']):
        base = obj.get('base')
        if base in meta['struct']:
            for i in range(len(meta['struct'][base]['types'])):
                m = {
                    'type': meta['struct'][base]['types'][i],
                    'name': meta['struct'][base]['names'][i],
                    'desc': meta['struct'][base]['desc'][i]
                    }

                if meta['struct'][base]['init'][i]:
                    m['init'] = meta['struct'][base]['init'][i]

                if m['name'] == "stype":
                    m['init'] = re.sub(r"(\$[a-z]+)(\w+)_t", r"\1_STRUCTURE_TYPE\2", obj['name']).upper()

                obj['members'].insert(i, m)
    return obj

"""
    generate complete return permutations
"""
def _generate_returns(obj, meta):
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
    return obj

"""
    generates extra content
"""
def _generate_extra(specs, meta):
    for s in specs:
        for i, obj in enumerate(s['objects']):
            obj = _generate_hash(obj)
            obj = _inline_base(obj, meta)
            obj = _generate_returns(obj, meta)
            s['objects'][i] = obj

"""
    generates reference-data on all objects
"""
def _generate_ref(specs, tags, ref):
    for s in specs:
        for obj in s['objects']:
            # create dict if typename is not already known...
            type = obj['type']
            if type not in ref:
                ref[type] = {}

            name = _subt(obj['name'], tags)

            # convert dict to json-string
            dstr = json.dumps(obj)

            # replace all tags with values
            for key, value in tags.items():
                dstr = re.sub(r"-%s"%re.escape(key), "-"+value, dstr)
                dstr = re.sub(re.escape(key), value, dstr)
                dstr = re.sub(re.escape(key.upper()), value.upper(), dstr)

            # convert json-string back to dict
            obj = json.loads(dstr)

            # update ref
            ref[type][name] = obj

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
        line_nums = _get_line_nums(f)

        header = None
        objects = []

        for i, d in enumerate(docs):
            if not _validate_doc(f, d, tags, line_nums[i]):
                continue

            d = _filter_version(d, float(version))
            if not d:
                continue

            # extract header from objects
            if re.match(r"header", d['type']):
                header = d
                header['ordinal'] = int(int(header.get('ordinal',"1000")) * float(header.get('version',"1.0")))

            elif header:
                objects.append(d)
                meta = _generate_meta(d, header['ordinal'], meta)

        if header:
            specs.append({
                'name'      : os.path.splitext(os.path.basename(f))[0],
                'header'    : header,
                'objects'   : objects
            })

    specs = sorted(specs, key=lambda s: s['header']['ordinal'])
    _generate_extra(specs, meta)

    ref = _generate_ref(specs, tags, ref)

    print("Parsed %s files and found:"%len(specs))
    for key in meta:
        print(" - %s %s(s)"%(len(meta[key]),key))
    return specs, meta, ref
