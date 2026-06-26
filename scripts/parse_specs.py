"""
 Copyright (C) 2019-2022 Intel Corporation

 SPDX-License-Identifier: MIT

"""
import os
import util
import re
import hashlib
import json
import yaml
import copy
from templates.helper import param_traits, type_traits, value_traits, get_tag, version_key

default_version = "1.0"
all_versions = ["1.0", "1.1", "1.2", "1.3", "1.4", "1.5", "1.6", "1.7", "1.8", "1.9", "1.10", "2.0"]

"""
    preprocess object
"""
def _preprocess(d):
    if 'enum' == d['type']:
        use_hex = False
        next = 0
        for etor in d['etors']:
            if type_traits.is_flags(d['name']):
                etor['name'] = "%s_%s"%(d['name'][:-3].upper(), etor['name'])
                etor['value'] = etor.get('value',"$X_BIT(%s)"%next)
                next = int(value_traits.get_bit_count(etor['value']))+1
            else:
                etor['name'] = d['name'][:-1].upper() + etor['name']
                use_hex = use_hex or value_traits.is_hex(etor.get('value'))
                if use_hex:
                    etor['value'] = etor.get('value',"%s"%hex(next))
                    next = int(etor['value'], 16)+1
                elif not value_traits.is_ver(etor.get('value')):
                    etor['value'] = etor.get('value',"%s"%next)
                    next = int(etor['value'])+1
    return d

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
    convert etor to int
"""
def _get_etor_value(value, prev):
    if value:
        if value_traits.is_ver(value):
            return (value_traits.get_major_ver(value) << 16) + value_traits.get_minor_ver(value)
        elif value_traits.is_bit(value):
            return 1 << value_traits.get_bit_count(value)
        elif value_traits.is_hex(value):
            return int(value, 16)
        else:
            return int(value)
    else:
        return prev+1
    
"""
    check if type is declares given requirement
"""
def _declares_requirement(type, requirement):
    return requirement in type.get("requires", [])

"""
    check if type is allowed to use handles as members
"""
def _handle_members_allowed(parent_desc, member_desc, tags):
    return get_tag(member_desc['type'], tags) == "$x" \
           and (_version_compare_gequal(parent_desc.get("version", default_version), "1.17")
                or _declares_requirement(parent_desc, "ZE_extension_driver_ddi_handles"))

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

    def __validate_version(d, prefix="", base_version=default_version):
        if 'version' in d:
            if not isinstance(d['version'], str):
                raise Exception(prefix+"'version' must be a string: '%s'"%type(d['version']))

        return d.get('version', base_version)

    def __validate_tag(d, key, tags, case):
        for x in tags:
            if d[key].startswith(x.upper() if case == 'upper' else x):
                return x
        return None

    def __validate_desc(desc):
        if isinstance(desc, dict):
            for k, v in desc.items():
                if not isinstance(k, str):
                    raise Exception(prefix+"'version' must be a string: '%s'"%type(k))

                for x in ['[in]', '[out]', '[in,out]']:
                    if v.startswith(x):
                        return x
        else:
            for x in ['[in]', '[out]', '[in,out]']:
                if desc.startswith(x):
                    return x
        return None

    def __validate_name(d, key, tags, case='lower', prefix=""):
        if not isinstance(d[key], str):
            raise Exception(prefix+"'%s' must be a string: '%s'"%(key, type(d[key])))
        if isinstance(d.get('type'), str) and d['type'] == 'default_struct' and key == 'name':
            # Name must start with Default, then two uppercase letters, and be camel case
            if not any(d[key].startswith(tag + 'Default') for tag in ['$r', '$t', '$x', '$s']):
                raise Exception(prefix+"'%s' must start with one of ['$rDefault', '$tDefault', '$xDefault', '$sDefault']: '%s'" % (key, d[key]))
            if d[key].endswith('_t'):
                raise Exception(prefix+"'%s' must not end with '_t': '%s'" % (key, d[key]))
            name = _subt(d[key], tags)
            print("Validating default_struct name '%s'..." % name)
            # Check that name is CamelCase (starts with uppercase, contains at least one lowercase, no underscores)
            if (name.isupper() or name.islower()):
                raise Exception(prefix+"'%s' must be CamelCase: '%s'" % (key, name))
            return  # Early return for default_struct case

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

        value = -1
        d_ver = d.get('version', default_version)
        max_ver = d_ver
        for i, item in enumerate(d['etors']):
            prefix="'etors'[%s] "%i
            if not isinstance(item, dict):
                raise Exception(prefix+"must be a mapping: '%s'"%(i, type(item)))

            if ('desc' not in item) or ('name' not in item):
                raise Exception(prefix+"requires the following scalar fields: {`desc`, `name`}")

            __validate_name(item, 'name', tags, case='upper', prefix=prefix)

            value = _get_etor_value(item.get('value'), value)
            if type_traits.is_flags(d['name']) and not value_traits.is_bit(item.get('value')):
                raise Exception(prefix+"'value' must use BIT macro: %s"%value)
            elif not type_traits.is_flags(d['name']) and value_traits.is_bit(item.get('value')):
                raise Exception(prefix+"'value' must not use BIT macro: %s"%value)

            if value >= 0x7fffffff:
                raise Exception(prefix+"'value' must be less than 0x7fffffff: %s"%value)

            ver = __validate_version(item, prefix=prefix, base_version=d_ver)
            if item.get('value'):
                max_ver = ver
            if _version_compare_less(ver, max_ver):
                raise Exception(prefix+"'version' must be increasing: %s"%item['version'])
            max_ver = ver

    def __validate_base(d):
        namespace = re.sub(r"(\$[a-z])\w+", r"\1", d['name'])
        valid_names = [
            "%s_base_desc_t"%namespace,
            "%s_base_properties_t"%namespace,
            "%s_base_cb_params_t"%namespace,
            "%s_driver_extension_properties_t"%namespace
            ]
        if d['name'] not in valid_names:
            if type_traits.is_descriptor(d['name']) and not d.get('base', "").endswith("base_desc_t"):
                raise Exception("'base' must be '%s_base_desc_t': %s"%(namespace, d['name']))

            elif type_traits.is_properties(d['name']) and not d.get('base', "").endswith("base_properties_t"):
                raise Exception("'base' must be '%s_base_properties_t': %s"%(namespace, d['name']))

            elif type_traits.is_cb_params(d['name']) and not d.get('base', "").endswith("base_cb_params_t"):
                raise Exception("'base' must be '%s_base_cb_params_t': %s"%(namespace, d['name']))

    def __validate_members(d, tags):
        if 'members' not in d:
            raise Exception("'%s' requires the following sequence of mappings: {`members`}"%d['type'])

        if not isinstance(d['members'], list):
            raise Exception("'members' must be a sequence: '%s'"%type(d['members']))

        d_ver = d.get('version', default_version)
        max_ver = d_ver
        for i, item in enumerate(d['members']):
            prefix="'members'[%s] "%i
            if not isinstance(item, dict):
                raise Exception(prefix+"must be a mapping: '%s'"%(i, type(item)))

            if ('desc' not in item) or ('type' not in item) or ('name' not in item):
                raise Exception(prefix+"requires the following scalar fields: {`desc`, 'type', `name`}")

            annotation = __validate_desc(item['desc'])
            if not annotation:
                raise Exception(prefix+"'desc' must start with {'[in]', '[out]', '[in,out]'}")

            if type_traits.is_handle(item['type']) and not _handle_members_allowed(d, item, tags):
                raise Exception(prefix+"'type' must not be '*_handle_t': %s"%item['type'])

            if item['type'].endswith("flag_t"):
                raise Exception(prefix+"'type' must not be '*_flag_t': %s"%item['type'])

            ver = __validate_version(item, prefix=prefix, base_version=d_ver)
            if _version_compare_less(ver, max_ver):
                raise Exception(prefix+"'version' must be increasing: %s"%item['version'])
            max_ver = ver

    def __validate_params(d, tags):
        if 'params' not in d:
            raise Exception("'function' requires the following sequence of mappings: {`params`}")

        runtime = False
        if 'class' in d and '$r' in d['class']:
            runtime = True
        if not isinstance(d['params'], list):
            if not runtime:
                raise Exception("'params' must be a sequence: '%s'"%type(d['params']))
            else:
                return

        d_ver = d.get('version', default_version)
        max_ver = d_ver
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

            runtime = False
            if 'class' in d and '$r' in d['class']:
                runtime = True
            if d.get('decl') != "static" and i == 0 and not runtime and not type_traits.is_handle(item['type']):
                raise Exception(prefix+"'type' must be '*_handle_t': %s"%item['type'])

            if item['type'].endswith("flag_t"):
                raise Exception(prefix+"'type' must not be '*_flag_t': %s"%item['type'])

            ver = __validate_version(item, prefix=prefix, base_version=d_ver)
            if _version_compare_greater(ver, max_ver):
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

        elif 'default_struct' == d['type']:
            print("Validating default_struct '%s'..." % d['name'])
            if ('desc' not in d) or ('name' not in d):
                raise Exception("'%s' requires the following scalar fields: {`desc`, `name`}"%d['type'])

            __validate_name(d, 'name', tags)
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
        return False

"""
    validate that all structs have an associated _structure_type_t enum entry
"""
def _validate_struct_enum_mapping(specs, tags):
    """
    Validates that for each struct, there exists a corresponding enum entry in a _structure_type_t enum.
    The validation checks that the enum entry's 'desc' field matches the struct name.
    
    This function also validates structs that have a "base" field, ensuring they have their own
    enum entries and are not just relying on their base struct's enum entry.
    
    Excludes certain struct types that don't require structure type enum entries:
    - kernel_max_group_size_properties_ext_t
    - Base structs themselves (*_base_*_t) 
    - Simple data container structs that don't have stype fields
    """
    structs_info = []
    structure_type_enums = {}
    
    # Collect all struct names (including base info) and structure_type enums
    for spec in specs:
        for obj in spec['objects']:
            if obj['type'] == 'struct':
                structs_info.append({
                    'name': obj['name'],
                    'base': obj.get('base', None)
                })
            elif obj['type'] == 'enum' and obj['name'].endswith('_structure_type_t'):
                # Collect enum entries with their desc fields
                structure_type_enums[obj['name']] = [
                    {'name': etor['name'], 'desc': etor.get('desc', '')} 
                    for etor in obj['etors']
                ]
    
    # Check each struct has a corresponding enum entry
    for struct_info in structs_info:
        struct_name = struct_info['name']
        base_struct = struct_info['base']
        
        # Get namespace from struct name for base validation
        namespace = re.sub(r"(\$[a-z])\w+", r"\1", struct_name)
        base_struct_names = [
            "%s_base_desc_t" % namespace,
            "%s_base_properties_t" % namespace,
            "%s_base_cb_params_t" % namespace,
            "%s_driver_extension_properties_t" % namespace
        ]
        
        # Skip validation for base structs themselves (they don't need enum entries)
        if struct_name in base_struct_names:
            continue

        if base_struct == None:
            continue  # Skip structs without a base struct

        if struct_name.endswith("_kernel_max_group_size_properties_ext_t"):
            continue  # Skip specific structs that don't require enum entries

        # Check if any enum entry's desc field matches this struct name
        found = False
        matching_enum_entry = None
        for enum_name, enum_entries in structure_type_enums.items():
            for enum_entry in enum_entries:
                if enum_entry['desc'] == struct_name:
                    found = True
                    matching_enum_entry = enum_entry['name']
                    break
            if found:
                break
        
        if not found:
            base_info = " (inherits from '%s')" % base_struct if base_struct else ""
            print("Struct-Enum Mapping Validation Error:")
            print("Struct '%s'%s does not have a corresponding enum entry with matching 'desc' field in any '*_structure_type_t' enum!" % (struct_name, base_info))
            print("Available enum entries in structure_type_t enums:")
            for enum_name, enum_entries in structure_type_enums.items():
                entry_names = [entry['name'] for entry in enum_entries[:5]]
                print("  %s: %s" % (enum_name, ", ".join(entry_names) + ("..." if len(enum_entries) > 5 else "")))
            return False
    
    return True

"""
    filters object by version
"""
# Version comparisons route through helper.version_key (single source of truth
# for major/minor decomposition). Do NOT reintroduce float(version) here.
def _version_compare_greater(a, b):
    return version_key(a) > version_key(b)

def _version_compare_equal(a, b):
    return version_key(a) == version_key(b)

def _version_compare_less(a, b):
    return version_key(a) < version_key(b)

def _version_compare_lequal(a, b):
    return version_key(a) <= version_key(b)

def _version_compare_gequal(a, b):
    return version_key(a) >= version_key(b)

def _filter_version(d, max_ver):
    ver = d.get('version', default_version)

    if _version_compare_greater(ver, max_ver):
        return None

    def __filter_desc(d):
        if 'desc' in d and isinstance(d['desc'], dict):
            for k, v in d['desc'].items():
                if _version_compare_lequal(k, max_ver):
                    desc = v
                else:
                    desc = "No description provided"
            d['desc'] = desc
        return d

    def __filter_detail(det):
        if isinstance(det, dict):
            detail = None
            for k, v in det.items():
                try:
                    version_key(k)
                except:
                    return det
                if _version_compare_lequal(k,  max_ver):
                    detail = v
            return detail
        return det

    if 'details' in d:
        flt = []
        for det in d['details']:
            fd = __filter_detail(det)
            if fd:
                flt.append(fd)
        d['details'] = flt

    flt = []
    type = d['type']
    if 'enum' == type:
        for e in d['etors']:
            ver = e.get('version', default_version)
            if _version_compare_lequal(ver, max_ver):
                flt.append(__filter_desc(e))
        if d['name'].endswith('version_t'):
            flt.append({
                'name': d['name'][:-1].upper() + "CURRENT",
                'value': flt[-1]['value'],
                'desc': "latest known version"
                })
        d['etors'] = flt

    elif 'function' == type:
        if isinstance(d['params'], list):
            for p in d['params']:
                ver = p.get('version', default_version)
                if _version_compare_lequal(ver, max_ver):
                    flt.append(__filter_desc(p))
            d['params'] = flt

    elif 'struct' == type or 'union' == type or 'class' == type:
        for m in d.get('members',[]):
            ver = m.get('version', default_version)
            if _version_compare_lequal(ver, max_ver):
                flt.append(__filter_desc(m))
        d['members'] = flt

    return __filter_desc(d)

"""
    creates docs per version
"""
def _make_versions(d, max_ver):
    docs = []
    type = d['type']
    if 'function' == type or 'struct' == type:
        for ver in all_versions:
            if _version_compare_greater(ver, max_ver):
                break

            dv = _filter_version(copy.deepcopy(d), ver)
            if not dv:
                continue

            if len(docs) > 0:
                if dv == docs[-1]:
                    continue

                dv['name'] += ver
            docs.append(dv)
    else:
        docs.append(d)
    return docs

"""
    generates meta-data on all objects
"""
def _generate_meta(d, ordinal, meta):
    type = d['type']
    name = re.sub(r"(\w+)\(.*\)", r"\1", d['name']) # removes '()' part of macros

    # create dict if typename is not already known...
    if type not in meta:
        meta[type] = {}

    if 'class' not in meta:
        meta['class'] = {}

    cls = d.get('class')
    if cls:
        # create dict if class name is not already known...
        if cls not in meta['class']:
            meta['class'][cls] = {}
            meta['class'][cls]['ordinal'] = 0

        # create list if object-type is not already known for class...
        if type not in meta['class'][cls]:
            meta['class'][cls][type] = []

        # append if object-name is not already known for object-type in class...
        if name not in meta['class'][cls][type]:
            meta['class'][cls][type].append(name)

        else:
            print("Error - duplicate entries for %s found!"%name)
            raise

    if 'class' != type:
        # create list if name is not already known for type...
        if 'function' == type and cls:
            name = cls+name

        if name not in meta[type]:
            meta[type][name] = {'class': ""}

        # add values to list
        if 'enum' == type:
            value = -1
            max_value = -1
            meta[type][name]['etors'] = []
            for idx, etor in enumerate(d['etors']):
                meta[type][name]['etors'].append(etor['name'])
                value = _get_etor_value(etor.get('value'), value)
                if value > max_value:
                    max_value = value
                    max_index = idx
            if type_traits.is_flags(name):
                meta[type][name]['max'] = hex((max_value << 1)-1) if max_value else '0'
            else:
                meta[type][name]['max'] = d['etors'][idx]['name']

        elif 'macro' == type:
            meta[type][name]['values'] = []
            if 'value' in d:
                meta[type][name]['values'].append(d['value'])

            if 'altvalue' in d:
                meta[type][name]['values'].append(d['altvalue'])

        elif 'function' == type:
            meta[type][name]['params'] = []
            if isinstance(d['params'], list):
                for p in d['params']:
                    meta[type][name]['params'].append({
                        'type':p['type']
                        })

        elif 'struct' == type or 'union' == type:
            meta[type][name]['members'] = []
            for m in d['members']:
                meta[type][name]['members'].append({
                    'type': m['type'],
                    'name': m['name'],
                    'desc': m['desc'],
                    'init': m.get('init')
                    })

        elif 'default_struct' == type:
            meta[type][name]['members'] = []
            for m in d['members']:
                meta[type][name]['members'].append({
                    'type': m['type'],
                    'name': m['name'],
                    'desc': m['desc'],
                    'init': m.get('init')
                    })

        if cls:
            meta[type][name]['class'] = cls

    else:
        if name not in meta['class']:
            meta['class'][name] = {}

        meta['class'][name]['ordinal'] = ordinal

        if 'base' in d:
            base = d['base']
            if 'child' not in meta['class'][base]:
                meta['class'][base]['child'] = []

            meta['class'][base]['child'].append(name)

            if 'handle' not in meta['class'][name]:
                meta['class'][name]['handle'] = []

            if name[:2] == base[:2]:
                meta['class'][name]['handle'].extend(meta['class'][base]['handle'])

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
        if isinstance(obj['params'], list):
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
            for i, m in enumerate(meta['struct'][base]['members']):
                m = copy.deepcopy(m)
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
            {"$X_RESULT_ERROR_DEVICE_LOST":[]},
            {"$X_RESULT_ERROR_OUT_OF_HOST_MEMORY":[]},
            {"$X_RESULT_ERROR_OUT_OF_DEVICE_MEMORY":[]},
            {"$X_RESULT_ERROR_INVALID_ARGUMENT":[]},
            {"$X_RESULT_ERROR_UNSUPPORTED_FEATURE":[]},
            {"$X_RESULT_ERROR_DEPENDENCY_UNAVAILABLE":[]},
            {"$X_RESULT_ERROR_INSUFFICIENT_PERMISSIONS":[]},
            {"$X_RESULT_ERROR_NOT_AVAILABLE":[]},
            {"$X_RESULT_ERROR_DEVICE_REQUIRES_RESET":[]},
            {"$X_RESULT_ERROR_DEVICE_IN_LOW_POWER_STATE":[]},
            {"$X_RESULT_ERROR_UNKNOWN":[]}
            ]

        # special function for appending to our list of dicts; avoiding duplicates
        def _append(lst, key, val):
            idx = next((i for i, v in enumerate(lst) if v.get(key)), len(lst))
            if idx == len(lst):
                lst.append({key:[]})
            if val and val not in lst[idx][key]:
                lst[idx][key].append(val)

        # generate results based on parameters
        runtime = False
        if 'class' in obj and '$r' in obj['class']:
            runtime = True
        no_params = False
        if not isinstance(obj['params'], list) and runtime:
            no_params = True
        if not no_params:
            for item in obj['params']:
                if not param_traits.is_optional(item) and not param_traits.is_mbz(item):
                    typename = type_traits.base(item['type'])

                    if type_traits.is_pointer(item['type']):
                        _append(rets, "$X_RESULT_ERROR_INVALID_NULL_POINTER", "`nullptr == %s`"%item['name'])

                    elif type_traits.is_handle(item['type']) and not type_traits.is_ipc_handle(item['type']):
                        _append(rets, "$X_RESULT_ERROR_INVALID_NULL_HANDLE", "`nullptr == %s`"%item['name'])

                    elif type_traits.is_enum(item['type'], meta):
                        _append(rets, "$X_RESULT_ERROR_INVALID_ENUMERATION", "`%s < %s`"%(meta['enum'][typename]['max'], item['name']))
                        _append(rets, "$X_RESULT_ERROR_UNSUPPORTED_ENUMERATION", [])

                    if type_traits.is_descriptor(item['type']):
                        # walk each entry in the desc for pointers and enums
                        for i, m in enumerate(meta['struct'][typename]['members']):
                            mtypename = type_traits.base(m['type'])

                            if type_traits.is_pointer(m['type']) and not param_traits.is_optional({'desc': m['desc']}):
                                _append(rets, "$X_RESULT_ERROR_INVALID_NULL_POINTER", "`nullptr == %s->%s`"%(item['name'], m['name']))

                            elif type_traits.is_enum(m['type'], meta):
                                if re.match(r"stype", m['name']):
                                    _append(rets, "$X_RESULT_ERROR_UNSUPPORTED_VERSION", "`%s != %s->stype`"%(re.sub(r"(\$\w)_(.*)_t.*", r"\1_STRUCTURE_TYPE_\2", typename).upper(), item['name']))
                                else:
                                    if "$x_init_driver_type_flags_t" == mtypename:
                                        _append(rets, "$X_RESULT_ERROR_INVALID_ENUMERATION", "`%s == %s->%s`"%('0x0', item['name'], m['name']))
                                        _append(rets, "$X_RESULT_ERROR_UNSUPPORTED_ENUMERATION", [])
                                    else:
                                        _append(rets, "$X_RESULT_ERROR_INVALID_ENUMERATION", "`%s < %s->%s`"%(meta['enum'][mtypename]['max'], item['name'], m['name']))
                                        _append(rets, "$X_RESULT_ERROR_UNSUPPORTED_ENUMERATION", [])

                    elif type_traits.is_properties(item['type']):
                        # walk each entry in the properties
                        for i, m in enumerate(meta['struct'][typename]['members']):
                            if type_traits.is_enum(m['type'], meta):
                                if re.match(r"stype", m['name']):
                                    _append(rets, "$X_RESULT_ERROR_UNSUPPORTED_VERSION", "`%s != %s->stype`"%(re.sub(r"(\$\w)_(.*)_t.*", r"\1_STRUCTURE_TYPE_\2", typename).upper(), item['name']))

        return_type = None
        return_desc = None
        set_type_returns = []
        # finally, append all user entries
        for item in obj.get('returns', []):
            if item == 'type':
                for key, value in obj.get('returns', {}).items():
                    if key == 'type':
                        return_type = value
                        continue
                    if key == 'desc':
                        return_desc = value
                        continue
                    if key == 'success':
                        success_key = value
                        _append(set_type_returns, success_key, None)
                        continue
                    if key == 'failure':
                        if isinstance(value, dict):
                            # Handle dictionary format: {'key': ['val1', 'val2']}
                            for key, values in value.items():
                                for val in values:
                                    _append(set_type_returns, key, val)
                        elif isinstance(value, list):
                            # Handle list format: ['key1', {'key2': ['val1', 'val2']}]
                            for item in value:
                                if isinstance(item, str):
                                    _append(set_type_returns, item, None)
                                elif isinstance(item, dict):
                                    for key, values in item.items():
                                        for val in values:
                                            _append(set_type_returns, key, val)
                        continue
                break
            if isinstance(item, dict):
                for key, values in item.items():
                    for val in values:
                        _append(rets, key, val)
            else:
                _append(rets, item, None)
        # Remove duplicate result entries keeping the last (user-specified) occurrence.
        # Each entry is expected to be a single-key dict like {"$X_RESULT_ERROR_INVALID_ARGUMENT": [...]}
        if not return_type:  # Only dedupe the default path
            seen = set()
            dedup = []
            for entry in reversed(rets):
                if isinstance(entry, dict) and len(entry) == 1:
                    key = next(iter(entry))
                    if key in seen:
                        continue  # drop earlier duplicate (default at top)
                    seen.add(key)
                dedup.append(entry)
            rets = list(reversed(dedup))

        # update doc
        if return_type:
            obj['return_type'] = return_type
            obj['return_desc'] = return_desc
            obj['returns'] = set_type_returns
            obj['return_fail_value'] = next(iter(set_type_returns[1]))
        else:
            obj['return_type'] = "ze_result_t"
            obj['return_desc'] = "[out] ze_result_t API result"
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
def parse(section, version, tags, meta, ref):
    path = os.path.join("./", section)
    specs = []
    successful = True
    for f in util.findFiles(path, "*.yml"):
        print("Parsing %s..."%f)
        docs = util.yamlRead(f)
        line_nums = _get_line_nums(f)

        header = None
        objects = []

        for i, d in enumerate(docs):
            d = _preprocess(d)
            if not _validate_doc(f, d, tags, line_nums[i]):
                successful = False
                continue
            if 'version' not in d:
                d['version'] = default_version

            d = _filter_version(d, version)
            if not d:
                continue

            # extract header from objects
            if re.match(r"header", d['type']):
                header = d
                # Header ordinal drives DDI table/class order (and the global
                # spec emission sort below). version_key() decomposes major/minor
                # so e.g. "1.17" sorts after "1.4"; a naive float(version) would
                # treat "1.17" as 1.17 < "1.4"==1.4 and misplace sub-tables,
                # breaking N-1 ABI. See helper.version_key.
                header['ordinal'] = int(int(header.get('ordinal',"1000")) * version_key(header.get('version',"1.0")))
                header['ordinal'] *= 1000 if re.match(r"extension", header.get('desc',"").lower()) else 1
                header['ordinal'] *= 1000 if re.match(r"experimental", header.get('desc',"").lower()) else 1

            elif header:
                # for d in _make_versions(d, float(version)):
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

    # Validate struct-enum mappings after all documents are parsed
    if not _validate_struct_enum_mapping(specs, tags):
        successful = False

    print("Parsed %s files and found:"%len(specs))
    for key in meta:
        print(" - %s %s(s)"%(len(meta[key]),key))
    print("")

    if not successful:
        raise Exception("Errors occurred")

    return specs, meta, ref
