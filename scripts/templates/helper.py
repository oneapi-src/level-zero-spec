import re

"""
    Extracts traits from a spec object
"""
class obj_traits:

    @staticmethod
    def is_function(obj):
        try:
            return True if re.match(r"function", obj['type']) else False
        except:
            return False

    @staticmethod
    def is_class(obj):
        try:
            return True if re.match(r"class", obj['type']) else False
        except:
            return False

    @staticmethod
    def class_name(obj):
        try:
            return obj['class']
        except:
            return None

"""
    Extracts traits from a class name
"""
class class_traits:

    @staticmethod
    def is_global(name, tags):
        try:
            return True if name in tags else False
        except:
            return False

    @staticmethod
    def is_namespace(name, namespace, tags):
        try:
            return tags[name] == namespace
        except:
            return False

"""
    Extracts traits from a type name
"""
class type_traits:
    RE_HANDLE   = r"(.*)handle_t"
    RE_POINTER  = r"(.*\w+)\*+"
    RE_DESC     = r"(.*)desc_t.*"

    @classmethod
    def is_handle(cls, name):
        try:
            return True if re.match(cls.RE_HANDLE, name) else False
        except:
            return False

    @classmethod
    def is_pointer(cls, name):
        try:
            return True if re.match(cls.RE_POINTER, name) else False
        except:
            return False

    @classmethod
    def is_descriptor(cls, name):
        try:
            return True if re.match(cls.RE_DESC, name) else False
        except:
            return False

    @staticmethod
    def find_class_name(name, meta):
        try:
            name = _remove_const_ptr(name)
            for group in meta:
                if name in meta[group]:
                    return meta[group][name]['class']
            return None
        except:
            return None

"""
    Extracts traits from a value name
"""
class value_traits:
    RE_BIT      = r".*BIT\((.*)\)"
    RE_MACRO    = r"(\$\w+)\(.*\)"
    RE_ARRAY    = r"(.*)\[(.*)\]"

    @classmethod
    def is_bit(cls, name):
        try:
            return True if re.match(cls.RE_BIT, name) else False
        except:
            return False

    @classmethod
    def is_macro(cls, name, meta):
        try:
            name = re.sub(cls.RE_MACRO, r"\1", name)  # removes '()' part of macros
            name = re.sub(cls.RE_ARRAY, r"\2", name)  # extracts from '[]' part of arrays
            return True if name in meta['macro'] else False
        except:
            return False

    @classmethod
    def is_array(cls, name):
        try:
            return True if re.match(cls.RE_ARRAY, name) else False
        except:
            return False

    @classmethod
    def find_enum_name(cls, name, meta):
        try:
            name = re.sub(cls.RE_ARRAY, r"\1", name) # removes '[]' part of arrays
            # if the value is an etor, return the name of the enum
            for e in meta['enum']:
                if name in meta['enum'][e]['types']:
                    return e
            return None
        except:
            return None

"""
    Extracts traits from a parameter object
"""
class param_traits:
    RE_OPTIONAL = r".*\[optional\].*"
    RE_RANGE    = r".*\[range\((.+),\s*(.+)\)\].*"

    @classmethod
    def is_optional(cls, item):
        try:
            return True if re.match(cls.RE_OPTIONAL, item['desc']) else False
        except:
            return False

    @classmethod
    def is_range(cls, item):
        try:
            return True if re.match(cls.RE_RANGE, item['desc']) else False
        except:
            return False

    @classmethod
    def range_start(cls, item):
        try:
            return re.sub(cls.RE_RANGE, r"\1", item['desc'])
        except:
            return None

    @classmethod
    def range_end(cls, item):
        try:
            return re.sub(cls.RE_RANGE, r"\2", item['desc'])
        except:
            return None

"""
    Extracts traits from a function object
"""
class function_traits:

    @staticmethod
    def is_static(item):
        try:
            return True if re.match(r"static", item['decl']) else False
        except:
            return False

    @staticmethod
    def is_global(item, tags):
        try:
            return True if item['class'] in tags else False
        except:
            return False

"""
Public:
    substitues each tag['key'] with tag['value']
    if cpp, then remove each tag['key'] if matches namespace
    if comment, then insert doxygen '::' notation at beginning (for autogen links)
"""
def subt(namespace, tags, string, comment=False, cpp=False):
    for key, value in tags.items():
        if cpp and re.match(namespace, value):                                  # generating c++ names and tag matches current namespace
            string = re.sub(r"%s_?"%re.escape("-"+key), "-", string)            # hack for compile options
            repl = "::" if comment and "$OneApi" != key else ""                 # remove tags; e.g., "$x" -> ""
            string = re.sub(r"%s_?"%re.escape(key), repl, string)
            string = re.sub(r"%s_?"%re.escape(key.upper()), repl.upper(), string)
        elif cpp:                                                               # generating c++ names and tags do _not_ match current namespace
            string = re.sub(r"-%s"%re.escape(key), "-"+value, string)           # hack for compile options
            repl = "::"+value if comment and "$OneApi" != key else value+"::"   # add namespace; e.g. "$x" -> "xe::"
            string = re.sub(r"%s_?"%re.escape(key), repl, string)
            string = re.sub(r"%s_?"%re.escape(key.upper()), repl.upper(), string)
        else:                                                                   # generating c names
            string = re.sub(r"-%s"%re.escape(key), "-"+value, string)           # hack for compile options
            repl = "::"+value if comment and "$OneApi" != key else value        # replace tag; e.g., "$x" -> "xe"
            string = re.sub(re.escape(key), repl, string)
            string = re.sub(re.escape(key.upper()), repl.upper(), string)
    return string

"""
Public:
    appends whitespace (in multiples of 4) to the end of the string,
    until len(string) > count
"""
def append_ws(string, count):
    while len(string) > count:
        count = count + 4
    string = '{str: <{width}}'.format(str=string, width=count)
    return string

"""
Public:
    split the line of text into a list of strings,
    where each length of each entry is less-than count
"""
def split_line(line, ch_count):
    if not line:
        return [""]

    RE_NEWLINE = r"(.*)\n(.*)"

    words           = line.split(" ")
    lines           = []
    word_list       = []

    for word in words:
        if re.match(RE_NEWLINE, word):
            prologue = re.sub(RE_NEWLINE,r"\1",word)
            epilogue = re.sub(RE_NEWLINE,r"\2",word)
            word_list.append(prologue)
            lines.append(" ".join(word_list))
            word_list = []
            if len(epilogue):
                word_list.append(epilogue)

        elif sum(map(len, word_list)) + len(word_list) + len(word) <= ch_count:
            word_list.append(word)

        else:
            lines.append(" ".join(word_list))
            word_list = [word]

    if len(word_list):
        lines.append(" ".join(word_list))
    return lines

"""
Private:
    converts string from camelCase to snake_case
"""
def _camel_to_snake(name):
    str = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    str = re.sub('([a-z0-9])([A-Z])', r'\1_\2', str).lower()
    return str

"""
Public:
    removes items from the list with the key and whose value do not match filter
"""
def filter_items(lst, key, filter):
    flst = []
    for item in lst:
        if key in item:
            if filter == item[key]:
                flst.append(item)
    return flst

"""
Public:
    returns a list of items with key from a list of dict
"""
def extract_items(lst, key):
    klst = []
    for item in lst:
        if key in item:
            klst.append(item[key])
    return klst

"""
Public:
    returns a list of all objects of type in all specs
"""
def extract_objs(specs, value):
    objs = []
    for s in specs:
        for obj in s['objects']:
            if re.match(value, obj['type']):
                objs.append(obj)
    return objs

"""
Private:
    removes 'const' from c++ type
"""
def _remove_const(name):

    return name.split(" ")[-1]

"""
Private:
    removes 'const' and '*' from c++ type
"""
def _remove_const_ptr(name):

    return re.sub(r"(.*)\*", r"\1", _remove_const(name))

"""
Private:
    adds class name to type
    e.g., "const type*" -> "const cname::type*"
"""
def _add_class(name, cname):
    words = name.split(" ")
    words[-1] = "%s::%s"%(cname, words[-1])
    return " ".join(words)

"""
Private:
    removes class name from type
    e.g., "const cls_type*" -> "const type*"
"""
def _remove_class(name, cname):
    if cname:
        RE_CLS = r"(.*)(%s_)(\w+)"%_camel_to_snake(cname) # remove "cls_" part
        if re.match(RE_CLS, name):
            name = re.sub(RE_CLS, r"\1\3", name)
    return name

"""
Public:
    returns c/c++ name of macro
"""
def make_macro_name(namespace, tags, obj, params=True):
    if params:
        return subt(namespace, tags, obj['name'])
    else:
        name = re.sub(r"(.*)\(.*", r"\1", obj['name'])  # remove '()' part
        return subt(namespace, tags, name)

"""
Public:
    returns c/c++ name of enums, structs, unions, typedefs...
"""
def make_type_name(namespace, tags, obj, cpp=False):
    name = subt(namespace, tags, obj['name'], cpp=cpp)

    # if c++, remove class part of name
    if cpp and 'class' in obj:
        cname = subt(namespace, tags, obj['class'], cpp=cpp)
        name = _remove_class(name, cname)
    return name

"""
Public:
    returns c/c++ name of etor
"""
def make_etor_name(namespace, tags, enum, etor, cpp=False):
    if cpp:
        # if c++, remove the verbose enum part of the etor
        # e.g., "ENUM_NAME_ETOR_NAME" -> "ETOR_NAME"
        prefix = re.sub(r"(\w+)_t", r"\1", subt(namespace, tags, enum, cpp=cpp)).upper()
        name = re.sub(r"%s_(\w+)"%prefix, r"\1", subt(namespace, tags, etor, cpp=cpp))
        name = re.sub(r"^(\d+\w*)", r"_\1", name)
    else:
        name = subt(namespace, tags, etor)
    return name

"""
Private:
    returns c/c++ name of value
"""
def _get_value_name(namespace, tags, value, cpp, meta):
    if cpp:
        if value_traits.is_macro(value, meta):
            value = subt(namespace, tags, value)
        else:
            name = value_traits.find_enum_name(value, meta)
            if name:
                # e.g., "ETOR_NAME" -> "ENUM_NAME::ETOR_NAME"
                enum = subt(namespace, tags, name, cpp=cpp)

                # e.g., "CLS_ENUM_NAME" -> "ENUM_NAME"
                # todo: this is assuming the class name is not needed - same class, same namespace
                cname = type_traits.find_class_name(name, meta)
                cname = subt(namespace, tags, cname, cpp=cpp)
                enum = _remove_class(enum, cname)
                value = "%s::%s"%(enum, make_etor_name(namespace, tags, name, value, cpp))
            else:
                value = subt(namespace, tags, value, cpp=cpp)
    else:
        value = subt(namespace, tags, value, cpp=cpp)
    return value

"""
Public:
    returns a list of c++ strings for declaring each enumerator in an enumeration
    format: "ETOR_NAME = VALUE, ///< DESCRIPTION"
"""
def make_etor_lines(namespace, tags, obj, cpp=False, meta=None):
    lines = []
    for item in obj['etors']:
        name = make_etor_name(namespace, tags, obj['name'], item['name'], cpp)

        if 'value' in item:
            value = _get_value_name(namespace, tags, item['value'], cpp, meta)
            prologue = "%s = %s,"%(name, value)
        else:
            prologue = "%s,"%(name)

        for line in split_line(subt(namespace, tags, item['desc'], True, cpp), 70):
            lines.append("%s///< %s"%(append_ws(prologue, 48), line))
            prologue = ""
    return lines

"""
Public:
    returns a list of c++ strings for converting each enumerator in an enumeration to a std::string
"""
def make_etor_debug_lines(namespace, tags, cname, obj):
    prologue = "%s::"%namespace
    if cname:
        prologue += "%s::"%make_class_name(namespace, tags, cname)
    prologue += make_type_name(namespace, tags, obj, cpp=True)

    etors = []
    bitfield = False
    for item in obj['etors']:
        name = make_etor_name(namespace, tags, obj['name'], item['name'], cpp=True)
        etors.append("%s::%s"%(prologue, name))
        if 'value' in item:
            bitfield |= value_traits.is_bit(item['value'])

    lines = []
    if bitfield:
        lines.append("const auto bits = static_cast<uint32_t>( val );")
        lines.append("if( 0 == bits ) return std::string(\"{}\");")
        lines.append("std::string str;")
        for item in etors:
            lines.append("if( static_cast<uint32_t>(%s) & bits )"%item)
            lines.append("    str += \"%s | \";"%item)
        lines.append("return \"{ \" + str.substr(0, str.size() - 3) + \" }\";")
    else:
        lines.append("switch( val )")
        lines.append("{")
        for item in etors:
            lines.append("case %s:"%item)
            lines.append("    return std::string(\"%s\");"%item)
        lines.append("};")
        lines.append("return std::string(\"%s::?\");"%prologue)
    return lines

"""
Private:
    returns c/c++ name of any type
"""
def _get_type_name(namespace, tags, obj, item, cpp=False, meta=None):
    name = subt(namespace, tags, item['type'], cpp=cpp)
    if cpp:
        cname = type_traits.find_class_name(item['type'], meta)
        if cname:
            is_global = class_traits.is_global(cname, tags)
            is_namespace = class_traits.is_namespace(cname, namespace, tags)  # cname == namespace? e.g., cname == "$x"
            is_handle = type_traits.is_handle(item['type'])

            is_inscope = False
            if obj_traits.is_class(obj):                        # if the obj _is_ a class
                is_inscope = cname == obj['name']                   # then is the item's class this obj? 
            elif not is_global:                                 # else if the obj belongs to a class
                is_inscope = cname == obj_traits.class_name(obj)    # then is the item's class the same as the obj?

            cname = subt(namespace, tags, cname, cpp=cpp)   # remove tags from class name

            if not (is_global or is_namespace or is_handle or is_inscope):
                # need to prepend the class name to the type
                name = _add_class(name, cname)

            elif is_handle and not obj_traits.is_class(obj):
                # convert handles to class pointers
                name = "%s*"%cname

            if not is_handle:
                # remove the verbose class part from the type name
                name = _remove_class(name, cname)

    return name

"""
Public:
    returns a list of c++ strings for each member of a structure or class
    format: "TYPE NAME = INIT, ///< DESCRIPTION"
"""
def make_member_lines(namespace, tags, obj, prefix="", cpp=False, meta=None):
    lines = []
    if 'members' not in obj:
        return lines

    for item in obj['members']:
        if cpp:
            name = _get_value_name(namespace, tags, prefix+item['name'], cpp, meta)
        else:
            name = subt(namespace, tags, prefix+item['name'], cpp=cpp)
        
        tname = _get_type_name(namespace, tags, obj, item, cpp, meta)

        if cpp and 'init' in item:
            value = _get_value_name(namespace, tags, item['init'], cpp, meta)
            prologue = "%s %s = %s;"%(tname, name, value)
        else:
            prologue = "%s %s;"%(tname, name)

        for line in split_line(subt(namespace, tags, item['desc'], True, cpp), 70):
            lines.append("%s///< %s"%(append_ws(prologue, 48), line))
            prologue = ""
    return lines

"""
Public:
    returns a list of c++ strings for each member of a class
    format: "auto getNAME( void ) const { return MEMBER; }"
"""
def make_member_function_lines(namespace, tags, obj, prefix=""):
    lines = []
    if 'members' not in obj:
        return lines

    for item in obj['members']:
        name = subt(namespace, tags, item['name'], cpp=True)

        is_pointer = type_traits.is_pointer(item['type'])
        if is_pointer and re.match(r"p\w+", name):  # if this is a pointer and starts with 'p',
            fname = name[1:].title()                # then remove the 'p' part of the name
        else:
            fname = name.title()

        lines.append("auto get%s( void ) const { return %s; }"%(fname, prefix+name))
    return lines

"""
Private:
    returns the list of parameters, filtering based on desc tags
"""
def _filter_param_list(params, filters=["in", "in,out", "out"]):
    lst = []
    for p in params:
        for f in filters:
            if re.match(r"\[%s\]"%f, p['desc']):
                lst.append(p)
                break
    return lst

"""
Public:
    returns a list of c++ strings for each parameter of a function
    format: "TYPE NAME = INIT, ///< DESCRIPTION"
"""
def make_param_lines(namespace, tags, obj, cpp=False, decl=False, meta=None, format=["type", "name", "init", "delim", "desc"]):
    lines = []

    if cpp:
        is_static = function_traits.is_static(obj)
        is_global = function_traits.is_global(obj, tags)
        if is_static or is_global:
            params = _filter_param_list(obj['params'], ["in", "in,out"])
        else:
            params = _filter_param_list(obj['params'][1:], ["in", "in,out"])
    else:
        params = obj['params']

    for i, item in enumerate(params):
        name = subt(namespace, tags, item['name'], cpp=cpp)
        tname = _get_type_name(namespace, tags, obj, item, cpp, meta)
        init = ""

        if cpp:
            is_handle = type_traits.is_handle(item['type'])
            if is_handle:
                name = re.sub(r"\bh([A-Z]\w+)", r"p\1", name) # change "hName" to "pName"

            if decl and param_traits.is_optional(item):
                is_pointer = type_traits.is_pointer(item['type'])
                if is_pointer or is_handle:
                    init += "= nullptr"
                else:
                    init += "= 0"

        words = []
        if "type" in format:
            words.append(tname)
        if "name" in format:
            words.append(name)
        if "init" in format and len(init) > 0:
            words.append(init)

        prologue = " ".join(words)
        if "delim" in format:
            if i < len(params)-1:
                prologue += ","

        if "desc" in format:
            desc = item['desc']
            if cpp:
                desc = re.sub(r"handle of", r"pointer to", desc)
            for line in split_line(subt(namespace, tags, desc, True, cpp), 70):
                lines.append("%s///< %s"%(append_ws(prologue, 48), line))
                prologue = ""
        else:
            lines.append(prologue)

    if len(lines) > 0:
        return lines
    else:
        return ["void"]

"""
Public:
    returns a string of parameter names for passing to a c++ function
    format: "PARAM0, PARAM1, PARAM2"
"""
def make_param_call_str(namespace, tags, prologue, obj, cpp=False):
    names = []
    if len(prologue) > 0:
        names.append(prologue)

    params = make_param_lines(namespace, tags, obj, cpp=cpp, format=["name"])
    if len(params) > 0 and params[0] != "void":
        names.extend(params)
    return ", ".join(names)

"""
Public:
    returns a string of c++ template parameters
    format: "TPARAM0, TPARAM1"
"""
def make_tparams_line(namespace, tags, obj):
    line = ", ".join(obj['tparams'])
    return subt(namespace, tags, line, cpp=True)

"""
Public:
    returns True if ctor has parameters
"""
def has_ctor_params(obj):
    params = _filter_param_list(obj['members'] if 'members' in obj else [], ["in"])
    return len(params) > 0

"""
Public:
    returns a list of c++ strings for ctor parameters of members
    format: "TYPE NAME, ///< DESCRIPTION"
"""
def make_ctor_param_lines(namespace, tags, obj, meta=None):
    lines = []
    params = _filter_param_list(obj['members'] if 'members' in obj else [], ["in"])
    for i, item in enumerate(params):
        name = subt(namespace, tags, item['name'])
        tname = _get_type_name(namespace, tags, obj, item, True, meta)

        if type_traits.is_descriptor(tname):
            tname = "const %s&"%tname # e.g., "xe_event_desc_t*" -> "const desc_t&"

        if i < len(params)-1:
            prologue = "%s %s,"%(tname, name)
        else:
            prologue = "%s %s"%(tname, name)

        for line in split_line(subt(namespace, tags, item['desc'], True), 70):
            lines.append("%s///< %s"%(append_ws(prologue, 48), line))
            prologue = ""

    if len(lines) > 0:
        return lines
    else:
        return ["void"]

"""
Public:
    returns a list of c++ strings for initializing members from ctor parameters of members
    format: "MEMBER( NAME ),"
"""
def make_ctor_param_init_lines(namespace, tags, obj, prefix="", meta=None):
    lines = []
    params = _filter_param_list(obj['members'] if 'members' in obj else [], ["in"])
    for i, item in enumerate(params):
        name = subt(namespace, tags, item['name'])

        if i < len(params)-1:
            lines.append("%s( %s ),"%(prefix+name, name))
        else:
            lines.append("%s( %s )"%(prefix+name, name))

    return lines

"""
Public:
    returns a list of strings for the description
    format: "@brief DESCRIPTION"
"""
def make_desc_lines(namespace, tags, obj, cpp=False):
    lines = []
    prologue = "@brief"
    for line in split_line(subt(namespace, tags, obj['desc'], True, cpp), 70):
        lines.append("%s %s"%(prologue, line))
        prologue = "      "
    return lines

"""
Public:
    returns a list of strings for the detailed description
    format: "@details DESCRIPTION"
"""
def make_details_lines(namespace, tags, obj, cpp=False):
    lines = []
    if 'details' in obj:
        lines.append("")
        lines.append("@details")

        for item in obj['details']:
            if isinstance(item, dict):
                for key, values in item.items():
                    prologue = "    -"
                    for line in split_line(subt(namespace, tags, key, True, cpp), 70):
                        lines.append("%s %s"%(prologue, line))
                        prologue = "     "
                    for val in values:
                        prologue = "        +"
                        for line in split_line(subt(namespace, tags, val, True, cpp), 66):
                            lines.append("%s %s"%(prologue, line))
                            prologue = "         "
            else:
                prologue = "    -"
                for line in split_line(subt(namespace, tags, item, True, cpp), 70):
                        lines.append("%s %s"%(prologue, line))
                        prologue = "     "
    if 'analogue' in obj:
        lines.append("")
        lines.append("@remarks")
        lines.append("  _Analogues_")
        for line in obj['analogue']:
            lines.append("    - %s"%line)
    return lines

"""
Public:
    returns a dict of auto-generated c++ parameter validation checks
"""
def make_param_checks(namespace, tags, obj, comment=False, cpp=False):
    checks = {}
    eip = subt(namespace, tags, "$X_RESULT_ERROR_INVALID_ARGUMENT", comment, cpp)
    eus = subt(namespace, tags, "$X_RESULT_ERROR_UNSUPPORTED", comment, cpp)
    checks[eip] = []
    checks[eus] = []

    for item in obj['params']:
        if not param_traits.is_optional(item):
            is_pointer = type_traits.is_pointer(item['type'])
            is_handle = type_traits.is_handle(item['type'])
            is_desc = type_traits.is_descriptor(item['type'])

            if is_pointer:
                checks[eip].append("nullptr == %s"%subt(namespace, tags, item['name'], comment, cpp))
            elif is_handle:
                checks[eip].append("nullptr == %s"%subt(namespace, tags, item['name'], comment, cpp))

            if is_desc: # descriptor-type
                name = subt(namespace, tags, _remove_const_ptr(item['type']), comment, cpp)
                ver = re.sub(r"(.*)_t.*", r"\1_VERSION_CURRENT", name).upper()
                checks[eus].append("%s < %s->version"%(ver, item['name']))
    return checks

"""
Public:
    returns a list of strings for possible return values
"""
def make_returns_lines(namespace, tags, obj, cpp=False, meta=None):
    lines = []
    if cpp:
        params = _filter_param_list(obj['params'], ["out"])
        if len(params) > 0:
            lines.append("@returns")
            for p in params:
                desc = re.sub(r"\[.*\](.*)", r"\1", p['desc'])
                tname = _remove_const_ptr(_get_type_name(namespace, tags, obj, p, cpp, meta))
                lines.append("    - %s"%subt(namespace, tags, "%s:%s"%(tname, desc), True, cpp))
            lines.append("")
        lines.append("@throws result_t")
        return lines

    lines.append("@returns")
    lines.append("    - %s"%subt(namespace, tags, "$X_RESULT_SUCCESS", True, cpp))
    lines.append("    - %s"%subt(namespace, tags, "$X_RESULT_ERROR_UNINITIALIZED", True, cpp))
    lines.append("    - %s"%subt(namespace, tags, "$X_RESULT_ERROR_DEVICE_LOST", True, cpp))

    # generate default checks
    gen = make_param_checks(namespace, tags, obj, True, cpp)

    # merge user-specified values
    if 'returns' in obj:
        for item in obj['returns']:
            if isinstance(item, dict):
                for key, values in item.items():
                    key = subt(namespace, tags, key, True, cpp)
                    if key not in gen:
                        gen[key] = []
                    for val in values:
                        gen[key].append(subt(namespace, tags, val, True, cpp))
            else:
                key = subt(namespace, tags, item, True, cpp)
                if key not in gen:
                    gen[key] = []

    # now make combined lines
    for key, values in gen.items():
        lines.append("    - %s"%key)
        for val in values:
            lines.append("        + %s"%val)
    return lines

"""
Public:
    returns c++ string for declaring function return type
"""
def make_return_value(namespace, tags, obj, cpp=False, decl=False, meta=None):
    # only "return" the parameters declared as "out"
    params = _filter_param_list(obj['params'], ["out"])

    # if none exist, then just return "void"
    if len(params) == 0:
        return "void"

    types = []
    for p in params:
        tname = _remove_const_ptr(_get_type_name(namespace, tags, obj, p, cpp, meta))
        if cpp:
            cname = type_traits.find_class_name(p['type'], meta)
            is_handle = type_traits.is_handle(p['type'])

            if cname and not decl and not is_handle:
                # need to prepend the class name to the type
                tname = _add_class(tname, subt(namespace, tags, cname, cpp=cpp))

            elif cname and is_handle:
                # convert handles to class pointers
                tname = _remove_const(_get_type_name(namespace, tags, obj, p, cpp, meta))

        types.append(tname)

    if len(types) > 1:
        # if more than one return value, then return a tuple of values
        return "std::tuple<%s>"%", ".join(types)
    else:
        return types[0]

"""
Public:
    returns the name of a function
"""
def make_func_name(namespace, tags, obj, cpp=False):
    if not cpp:
        cname = obj_traits.class_name(obj)
    else:
        cname = ""
    return subt(namespace, tags, "%s%s"%(cname, obj['name']), cpp=cpp)

"""
Public:
    returns the name of a function pointer
"""
def make_pfn_name(namespace, tags, obj):

    return subt(namespace, tags, "pfn%s"%obj['name'])

"""
Public:
    returns the name of a function pointer
"""
def make_pfn_type(namespace, tags, obj):
    newtags = dict()
    for key, value in tags.items():
        if re.match(namespace, value):
            newtags[key] = "pfn"
    return "%s_%s_t"%(namespace, make_func_name(namespace, newtags, obj))

"""
Public:
    returns the name of a class
"""
def make_class_name(namespace, tags, obj):
    name = subt(namespace, tags, obj['name'], cpp=True)
    return name

"""
Public:
    returns a c++ string for the declaration of a base class
"""
def make_baseclass_decl(namespace, tags, obj):
    if 'base' in obj:
        return " : public %s"%(subt(namespace, tags, obj['base'], cpp=True))
    return ""

"""
Public:
    returns a c++ string for the declaration of a base class ctor
"""
def make_baseclass_ctor(namespace, tags, obj):
    base = subt(namespace, tags, obj['base'], cpp=True)
    ctor = make_class_name(namespace, tags, obj)
    return "%s::%s"%(base, ctor)

"""
Public:
    returns a list of all function objs for the specified class
"""
def get_class_function_objs(specs, cname):
    buckets = dict() # bucket per function ordinals
    for s in specs:
        for obj in s['objects']:
            is_function = obj_traits.is_function(obj)
            match_cls = cname == obj_traits.class_name(obj)
            if is_function and match_cls:
                # append to bucket
                ordinal = obj['ordinal'] if 'ordinal' in obj else '9999'
                if ordinal not in buckets:
                    buckets[ordinal] = []
                buckets[ordinal].append(obj)

    # finally, generate a single list that is storted by ordinal
    objs = []
    for k, v in sorted(buckets.items()):
        objs.extend(v)
    return objs

"""
Public:
    returns string name of table for function object
"""
def get_table_name(namespace, tags, obj):
    cname = obj_traits.class_name(obj)
    name = subt(namespace, tags, cname, cpp=True) # i.e., "$x" -> ""
    name = name if len(name) > 0 else "Global"
    return name

"""
Public:
    returns a list of dict of each pfntables needed
"""
def get_pfntables(specs, meta, namespace, tags):
    tables = []
    for cname in sorted(meta['class'], key=lambda x: meta['class'][x]['ordinal']):
        objs = get_class_function_objs(specs, cname)
        if len(objs) > 0:
            name = get_table_name(namespace, tags, {'class': cname})
            table = "%s_%s_dditable_t"%(namespace, _camel_to_snake(name))

            params = []
            params.append({
                'type': "$x_api_version_t",
                'name': "version",
                'desc': "[in] API version requested"
                })
            params.append({
                'type': "%s*"%table,
                'name': "ptable",
                'desc': "[in,out] pointer to table of DDI function pointers"
                })
            export = {
                'name': "%sGet%sProcAddrTable"%(namespace, name),
                'params': params
                }

            pfn = "%s_pfnGet%sProcAddrTable_t"%(namespace, name)

            tables.append({
                'name': name, 
                'type': table,
                'export': export,
                'pfn': pfn,
                'functions': objs
            })
    return tables

"""
Public:
    returns a list of c++ strings for converting loader input parameters
"""
def make_loader_prologue_lines(namespace, tags, obj, meta, loader):
    lines = []

    tblname = get_table_name(namespace, tags, obj)
    pfnname = make_pfn_name(namespace, tags, obj)
    if re.match(r"Global.*", tblname):
        lines.append("auto %s = %s.%s%sDdiTable.%s;"%(pfnname, loader, namespace, tblname, pfnname))
        lines.append("")

    params = _filter_param_list(obj['params'], ["in"])
    for i, item in enumerate(params):
        is_handle = type_traits.is_handle(item['type'])
        cname = type_traits.find_class_name(item['type'], meta)

        if is_handle and cname:
            name = subt(namespace, tags, item['name'])
            tname = _remove_const_ptr(subt(namespace, tags, item['type']))

            # e.g., "$x_device_handle_t" -> "xet_device_object_t"
            obj_name = re.sub(r"^[^_]+_(\w+)", r"%s_\1"%namespace, re.sub(r"(\w+)_handle_t", r"\1_object_t", tname))

            if type_traits.is_pointer(item['type']):
                range_start = param_traits.range_start(item)
                range_end   = param_traits.range_end(item)
                lines.append("for( size_t i = %s; ( nullptr != %s ) && ( i < %s ); ++i )"%(range_start, name, range_end))
                lines.append("    %s[ i ] = std::get<0>( *reinterpret_cast<%s*>( %s[ i ] ) );"%(name, obj_name, name))
            else:
                if param_traits.is_optional(item):
                    lines.append("%s = ( %s ) ? std::get<0>( *reinterpret_cast<%s*>( %s ) ) : nullptr;"%(name, name, obj_name, name))
                else:
                    if i == 0:
                        prologue = "%s."%get_table_name(namespace, tags, {'class': obj['class']})
                        lines.append("auto %s = std::get<1>( *reinterpret_cast<%s*>( %s ) )->%s%s;"%(pfnname, obj_name, name, prologue, pfnname))
                        lines.append("")

                    lines.append("%s = std::get<0>( *reinterpret_cast<%s*>( %s ) );"%(name, obj_name, name))

    if len(lines) > 0:
        lines.append("")
    return lines

"""
Public:
    returns a list of c++ strings for converting loader output parameters
"""
def make_loader_epilogue_lines(namespace, tags, obj, meta):
    lines = []

    params = _filter_param_list(obj['params'], ["out"])
    for i, item in enumerate(params):
        is_handle = type_traits.is_handle(item['type'])
        cname = type_traits.find_class_name(item['type'], meta)

        if is_handle and cname:
            name = subt(namespace, tags, item['name'])
            tname = _remove_const_ptr(subt(namespace, tags, item['type']))

            obj_name = re.sub(r"^[^_]+_(\w+)", r"%s_\1"%namespace, re.sub(r"(\w+)_handle_t", r"\1_object_t", tname))

            if param_traits.is_range(item):
                range_start = param_traits.range_start(item)
                range_end   = param_traits.range_end(item)
                lines.append("for( size_t i = %s; ( nullptr != %s ) && ( i < %s ); ++i )"%(range_start, name, range_end))
                lines.append("    %s[ i ] = reinterpret_cast<%s>( new %s( %s[ i ], nullptr ) );"%(name, tname, obj_name, name))

            else:
                if param_traits.is_optional(item):
                    lines.append("if( nullptr != %s ) *%s = reinterpret_cast<%s>( new %s( *%s, nullptr ) );"%(name, name, tname, obj_name, name))
                else:
                    lines.append("*%s = reinterpret_cast<%s>( new %s( *%s, nullptr ) );"%(name, tname, obj_name, name))

    if len(lines) > 0:
        lines.append("")
    return lines
