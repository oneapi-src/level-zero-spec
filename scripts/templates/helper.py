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

    @staticmethod
    def is_singleton(item):
        try:
            return "singleton" == item['attribute']
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

    @staticmethod
    def is_class_handle(name, meta):
        try:
            name = _remove_const_ptr(name)
            return len(meta['handle'][name]['class']) > 0
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
    def is_known(name, meta):
        try:
            name = _remove_const_ptr(name)
            for group in meta:
                if name in meta[group]:
                    return True
            return False
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
            name = cls.get_macro_name(name)
            name = cls.get_array_length(name)
            return True if name in meta['macro'] else False
        except:
            return False

    @classmethod
    def get_macro_name(cls, name):
        try:
            return re.sub(cls.RE_MACRO, r"\1", name)    # 'NAME()' -> 'NAME'
        except:
            return name

    @classmethod
    def is_array(cls, name):
        try:
            return True if re.match(cls.RE_ARRAY, name) else False
        except:
            return False

    @classmethod
    def get_array_name(cls, name):
        try:
            return re.sub(cls.RE_ARRAY, r"\1", name)    # 'name[len]' -> 'name'
        except:
            return name

    @classmethod
    def get_array_length(cls, name):
        try:
            return re.sub(cls.RE_ARRAY, r"\2", name)    # 'name[len]' -> 'len'
        except:
            return name

    @classmethod
    def find_enum_name(cls, name, meta):
        try:
            name = cls.get_array_name(name)
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
    RE_IN       = r"^\[in\].*"
    RE_OUT      = r"^\[out\].*"
    RE_INOUT    = r"^\[in,out\].*"
    RE_OPTIONAL = r".*\[optional\].*"
    RE_RANGE    = r".*\[range\((.+),\s*(.+)\)\][\S\s]*"
    RE_RELEASE  = r".*\[release\].*"

    @classmethod
    def is_input(cls, item):
        try:
            return True if re.match(cls.RE_IN, item['desc']) else False
        except:
            return False

    @classmethod
    def is_output(cls, item):
        try:
            return True if re.match(cls.RE_OUT, item['desc']) else False
        except:
            return False

    @classmethod
    def is_inoutput(cls, item):
        try:
            return True if re.match(cls.RE_INOUT, item['desc']) else False
        except:
            return False

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
    @classmethod
    def is_release(cls, item):
        try:
            return True if re.match(cls.RE_RELEASE, item['desc']) else False
        except:
            return False

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
    name = name.split(" ")[-1]
    return name

"""
Private:
    removes '*' from c++ type
"""
def _remove_ptr(name, last=True):
    if last:
        name = re.sub(r"(.*)\*$", r"\1", name) # removes only last '*'
    else:
        name = re.sub(r"\*", "", name) # removes all '*'
    return name

"""
Private:
    removes 'const' and '*' from c++ type
"""
def _remove_const_ptr(name):
    name = _remove_ptr(_remove_const(name))
    return name

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
    determines whether the enumeration represents a bitfield
"""
def is_enum_bitfield(obj):
    for item in obj['etors']:
        if 'value' in item and value_traits.is_bit(item['value']):
            return True
    return False

"""
Private:
    returns c/c++ name of any type
"""
def _get_type_name(namespace, tags, obj, item, cpp=False, meta=None, handle_to_class=True):
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

            elif handle_to_class and is_handle and not obj_traits.is_class(obj):
                # convert handles to class pointers
                name = re.sub(r"(const\s*)?(\w*:?:?\w+)(\**)", r"\1%s*\3"%cname, name) # e.g., const name* -> const cname**

            if not is_handle:
                # remove the verbose class part from the type name
                name = _remove_class(name, cname)

    return name

"""
Public:
    returns c/c++ name of member of struct/class
"""
def make_member_name(namespace, tags, item, prefix="", cpp=False, meta=None, remove_array=False):
    if cpp and value_traits.is_macro(item['name'], meta):
        name = subt(namespace, tags, item['name'])
    else:
        name = subt(namespace, tags, prefix+item['name'], cpp=cpp)

    if remove_array:
        name = value_traits.get_array_name(name)

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
        name = make_member_name(namespace, tags, item, prefix, cpp, meta)
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
def _filter_param_list(params, filters1=["[in]", "[in,out]", "[out]"], filters2=[""]):
    lst = []
    for p in params:
        for f1 in filters1:
            if f1 in p['desc']:
                for f2 in filters2:
                    if f2 in p['desc']:
                        lst.append(p)
                        break
                break
    return lst

"""
Private:
    returns c/c++ name of parameter
"""
def _get_param_name(namespace, tags, item, cpp):
    name = subt(namespace, tags, item['name'], cpp=cpp)
    if cpp and type_traits.is_handle(item['type']):
        name = re.sub(r"\bh([A-Z]\w+)", r"p\1", name) # change "hName" to "pName"
        name = re.sub(r"\bph([A-Z]\w+)", r"pp\1", name) # change "phName" to "ppName"
        if param_traits.is_output(item) and not param_traits.is_optional(item):
            name = re.sub(r"p(p[A-Z]\w+)", r"\1", name) #change ppName to pName
    return name

"""
Public:
    returns a list of c++ strings for each parameter of a function
    format: "TYPE NAME = INIT, ///< DESCRIPTION"
"""
def make_param_lines(namespace, tags, obj, cpp=False, decl=False, meta=None, format=["type", "name", "init", "delim", "desc"], delim=","):
    lines = []

    if cpp:
        is_static = function_traits.is_static(obj)
        is_global = function_traits.is_global(obj, tags)
        params = obj['params'] if is_static or is_global else obj['params'][1:]
        params = _filter_param_list(params, ["[in]", "[in,out]"]) + _filter_param_list(params, ["[out]"], ["[optional"])
    else:
        params = obj['params']

    for i, item in enumerate(params):
        name = _get_param_name(namespace, tags, item, cpp=cpp)
        tname = _get_type_name(namespace, tags, obj, item, cpp, meta)
        init = ""

        if cpp:
            if decl and param_traits.is_optional(item):
                is_pointer = type_traits.is_pointer(item['type'])
                is_handle = type_traits.is_handle(item['type'])
                if is_pointer or is_handle:
                    init += "= nullptr"
                else:
                    init += "= 0"

        words = []
        if "type*" in format:
            words.append(tname+"*")
            name = "p"+name
        elif "type" in format:
            words.append(tname)
        if "name" in format:
            words.append(name)
        if "init" in format and len(init) > 0:
            words.append(init)

        prologue = " ".join(words)
        if "delim" in format:
            if i < len(params)-1:
                prologue += delim

        if "desc" in format:
            desc = item['desc']
            if cpp:
                desc = re.sub(r"handle of", r"pointer to", desc)
            for line in split_line(subt(namespace, tags, desc, True, cpp), 70):
                lines.append("%s///< %s"%(append_ws(prologue, 48), line))
                prologue = ""
        else:
            lines.append(prologue)

    if "type" in format and len(lines) == 0:
        lines = ["void"]
    return lines

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
    params = _filter_param_list(obj['members'] if 'members' in obj else [], ["[in]"])
    return len(params) > 0

"""
Public:
    returns a list of c++ strings for ctor parameters of members
    format: "TYPE NAME, ///< DESCRIPTION"
"""
def make_ctor_param_lines(namespace, tags, obj, meta=None, format=["type", "name", "delim", "desc"]):
    lines = []
    params = _filter_param_list(obj['members'] if 'members' in obj else [], ["[in]"])
    for i, item in enumerate(params):
        name = subt(namespace, tags, item['name'])
        tname = _get_type_name(namespace, tags, obj, item, True, meta)

        if type_traits.is_descriptor(tname):
            tname = "const %s*"%tname # e.g., "xe_event_desc_t*" -> "const desc_t*"

        words = []
        if "type" in format:
            words.append(tname)
        if "name" in format:
            words.append(name)

        prologue = " ".join(words)
        if "delim" in format:
            if i < len(params)-1:
                prologue += ","

        if "desc" in format:
            for line in split_line(subt(namespace, tags, item['desc'], True), 70):
                lines.append("%s///< %s"%(append_ws(prologue, 48), line))
                prologue = ""
        else:
            lines.append(prologue)

    if "type" in format and len(lines) == 0:
        lines = ["void"]
    return lines

"""
Public:
    returns a list of c++ strings for initializing members from ctor parameters of members
    format: "MEMBER( NAME ),"
"""
def make_ctor_param_init_lines(namespace, tags, obj, prefix="", meta=None):
    lines = []
    params = _filter_param_list(obj['members'] if 'members' in obj else [], ["[in]"])
    for i, item in enumerate(params):
        name = subt(namespace, tags, item['name'])
        tname = _get_type_name(namespace, tags, obj, item, cpp=True, meta=meta)

        member = prefix+name
        if type_traits.is_descriptor(tname):
            name = "( %s ) ? *%s : desc_t{}"%(name, name)

        delim = "," if i < len(params)-1 else ""
        lines.append("%s( %s )%s"%(member, name, delim))

    return lines

"""
Private:
    returns c/c++ name of local variable from parameter name
"""
def _get_local_name(name):
    name = re.sub(r"\bp([A-Z]\w+)", r"\1", name) # change pName to Name
    name = re.sub(r"\bp([hA-Z]\w+)", r"\1", name) # change phName to hName
    name = re.sub(r"\bp(p[A-Z]\w+)", r"\1", name) # change ppName to pName
    name = name[0].lower() + name[1:] # change Name to name
    return name

"""
Public:
    returns a list of dict for declaring local variables in c++ wrapper
"""
def make_wrapper_params(namespace, tags, obj, meta, specs):
    params = []
    returns = []

    # if the input parameter is a class,
    # then need to use getHandle
    # if the input parameter is an array of classes
    # then need to create a std::vector of handles

    # if the output parameter is a class,
    # then need to create a local handle then call the ctor
    # if the output parameter is an array of classes
    # then need to create a std::vector to receive handles(s) then call the ctor for each

    # if the parameter is an input and the cpp type is different than the c type,
    # then need to use static_cast or reinterpret_cast

    # if the parameter is an output
    # then need to create a local variable

    is_static = function_traits.is_static(obj)
    is_global = function_traits.is_global(obj, tags)

    for i, item in enumerate(obj['params']):
        c_name = _get_param_name(namespace, tags, item, cpp=False)
        cpp_name = _get_param_name(namespace, tags, item, cpp=True)

        c_tname = _get_type_name(namespace, tags, obj, item, cpp=False, meta=meta)
        cpp_tname = _get_type_name(namespace, tags, obj, item, cpp=True, meta=meta, handle_to_class=False)
        cpp_cname = _get_type_name(namespace, tags, obj, item, cpp=True, meta=meta)

        local_name = _get_local_name(c_name)

        if param_traits.is_range(item):
            range_start = param_traits.range_start(item)
            range_end   = param_traits.range_end(item)
            if type_traits.is_class_handle(item['type'], meta):
                if param_traits.is_output(item) or param_traits.is_inoutput(item):
                    cobj = next(iter(filter_items(extract_objs(specs, 'class'), 'name', type_traits.find_class_name(item['type'], meta))), None)
                    fty_name = "%sFactory"%(_remove_ptr(cpp_cname[0].lower() + cpp_cname[1:], False))
                    if param_traits.is_optional(item):
                        params.append({
                            'local': local_name,
                            'ctype': _remove_const_ptr(c_tname),
                            'cpptype': _remove_const_ptr(cpp_tname),
                            'range': (range_start, range_end),
                            'optional': True,
                            'arg': "%s.data()"%(local_name),
                            'class': _remove_ptr(cpp_cname, False),
                            'ctor': {
                                'params': _make_wrapper_ctor_params(namespace, tags, item, obj, cobj, meta),
                                'factory': fty_name if class_traits.is_singleton(cobj) else ""
                            },
                            'name': cpp_name
                        })
                    else:
                        params.append({
                            'local': local_name,
                            'ctype': _remove_const_ptr(c_tname),
                            'cpptype': _remove_const_ptr(cpp_tname),
                            'range': (range_start, range_end),
                            'optional': False,
                            'arg': "%s.data()"%(local_name),
                            'class': _remove_ptr(cpp_cname, False),
                            'ctor': {
                                'params': _make_wrapper_ctor_params(namespace, tags, item, obj, cobj, meta),
                                'factory': "%sFactory"%(_remove_ptr(cpp_cname, False)) if class_traits.is_singleton(cobj) else ""
                            },
                            'name': cpp_name
                        })
                        if param_traits.is_output(item):
                            returns.append(cpp_name)

                elif param_traits.is_optional(item):
                    params.append({
                        'local': local_name,
                        'ctype': _remove_const_ptr(c_tname),
                        'cpptype': _remove_const_ptr(cpp_tname),
                        'range': (range_start, range_end),
                        'init': cpp_name,
                        'optional': True,
                        'arg': "%s.data()"%(local_name)
                    })
                else:
                    params.append({
                        'local': local_name,
                        'ctype': _remove_const_ptr(c_tname),
                        'cpptype': _remove_const_ptr(cpp_tname),
                        'range': (range_start, range_end),
                        'init': cpp_name,
                        'optional': False,
                        'arg': "%s.data()"%(local_name)
                    })

            elif param_traits.is_output(item):
                params.append({
                    'local': local_name,
                    'ctype': _remove_const_ptr(c_tname),
                    'cpptype': _remove_const_ptr(cpp_tname),
                    'range': (range_start, range_end),
                    'optional': param_traits.is_optional(item),
                    'arg': "%s.data()"%(local_name)
                })
                returns.append(cpp_name)

            elif c_tname != cpp_tname:
                params.append({
                    'arg': "reinterpret_cast<%s>( %s )"%(c_tname, cpp_name)
                })

            else:
                params.append({
                    'arg': cpp_name
                })

        else:
            if type_traits.is_class_handle(item['type'], meta):
                is_this_handle = type_traits.find_class_name(item['type'], meta) == obj_traits.class_name(obj)
                if param_traits.is_output(item):
                    cobj = next(iter(filter_items(extract_objs(specs, 'class'), 'name', type_traits.find_class_name(item['type'], meta))), None)
                    fty_name = "%sFactory"%(_remove_ptr(cpp_cname[0].lower() + cpp_cname[1:], False))
                    if param_traits.is_optional(item):
                        params.append({
                            'local': local_name,
                            'ctype': _remove_const_ptr(c_tname),
                            'cpptype': _remove_const_ptr(cpp_tname),
                            'optional': True,
                            'arg': "( %s ) ? &%s : nullptr"%(cpp_name, local_name),
                            'release': False,
                            'class': _remove_ptr(cpp_cname, False),
                            'ctor': {
                                'params': _make_wrapper_ctor_params(namespace, tags, item, obj, cobj, meta),
                                'factory': fty_name if class_traits.is_singleton(cobj) else ""
                            },
                            'name': cpp_name
                        })
                    else:
                        params.append({
                            'local': local_name,
                            'ctype': _remove_const_ptr(c_tname),
                            'cpptype': _remove_const_ptr(cpp_tname),
                            'optional': False,
                            'arg': "&%s"%(local_name),
                            'release': False,
                            'class': _remove_ptr(cpp_cname, False),
                            'ctor': {
                                'params': _make_wrapper_ctor_params(namespace, tags, item, obj, cobj, meta),
                                'factory': fty_name if class_traits.is_singleton(cobj) else ""
                            },
                            'name': cpp_name
                        })
                        returns.append(cpp_name)
                elif param_traits.is_optional(item):
                    params.append({
                        'arg': "( %s ) ? reinterpret_cast<%s>( %s->getHandle() ) : nullptr"%(cpp_name, c_tname, cpp_name)
                    })
                elif (not is_static and not is_global) and is_this_handle:
                    params.append({
                        'arg': "reinterpret_cast<%s>( getHandle() )"%(c_tname)
                    })
                elif param_traits.is_release(item):
                    params.append({
                        'arg': "reinterpret_cast<%s>( %s->getHandle() )"%(c_tname, cpp_name),
                        'release': True,
                        'class': _remove_ptr(cpp_cname, False),
                        'name': cpp_name
                    })
                else:
                    params.append({
                        'arg': "reinterpret_cast<%s>( %s->getHandle() )"%(c_tname, cpp_name)
                    })

            elif param_traits.is_output(item):
                params.append({
                    'local': local_name,
                    'ctype': _remove_const_ptr(c_tname),
                    'cpptype': _remove_const_ptr(cpp_tname),
                    'arg': "&%s"%(local_name),
                    'name': local_name
                })
                if c_tname != cpp_tname:
                    if type_traits.is_pointer(_remove_ptr(item['type'])) or type_traits.is_handle(item['type']):
                        returns.append("reinterpret_cast<%s>( %s )"%(_remove_const_ptr(cpp_tname), local_name))
                    else:
                        returns.append("*reinterpret_cast<%s*>( &%s )"%(_remove_const_ptr(cpp_tname), local_name))
                else:
                    returns.append(local_name)

            elif c_tname != cpp_tname:
                if type_traits.is_pointer(item['type']) or type_traits.is_handle(item['type']):
                    params.append({
                        'arg': "reinterpret_cast<%s>( %s )"%(c_tname, cpp_name)
                    })
                else:
                    params.append({
                        'arg': "static_cast<%s>( %s )"%(c_tname, cpp_name)
                    })

            else:
                params.append({
                    'arg': cpp_name
                })

    if len(returns) == 0:
        rvalue = ""
    elif len(returns) > 1:
        rvalue = "std::make_tuple( %s )"%", ".join(returns)
    else:
        rvalue = "%s"%returns[0]

    return params, rvalue

"""
Private:
    returns a list of c++ strings of ctor arguments in c++ wrapper
"""
def _make_wrapper_ctor_params(namespace, tags, item, obj, cobj, meta):
    params = []

    is_static = function_traits.is_static(obj)
    is_global = function_traits.is_global(obj, tags)

    # generate list of names for each parameter of the current function
    oparams = [ _get_param_name(namespace, tags, oparam, cpp=True) for oparam in obj['params'] ]

    # walk the ctor parameter names
    cparams = make_ctor_param_lines(namespace, tags, cobj, meta=meta, format=['name'])
    for i, name in enumerate(cparams):
        if name == "handle":
            c_name = _get_param_name(namespace, tags, item, cpp=False)
            local_name = _get_local_name(c_name)

            cpp_tname = _get_type_name(namespace, tags, obj, item, cpp=True, meta=meta, handle_to_class=False)

            if param_traits.is_range(item):
                params.append("reinterpret_cast<%s>( %s[ i ] )"%(_remove_const_ptr(cpp_tname), local_name))
            else:
                params.append("reinterpret_cast<%s>( %s )"%(_remove_const_ptr(cpp_tname), local_name))

        elif name in oparams:
            if (not is_static and not is_global) and (0 == oparams.index(name)):
                params.append("this")
            else:
                params.append(name)

        else:
            if (not is_static and not is_global):
                params.append("m_"+name)
            else:
                params.append("nullptr")

    return params

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
        params = _filter_param_list(obj['params'], ["[out]"])
        if len(params) > 0:
            lines.append("@returns")
            for p in params:
                desc = re.sub(r"\[.*\](.*)", r"\1", p['desc'])
                tname = _remove_const_ptr(_get_type_name(namespace, tags, obj, p, cpp, meta))
                lines.append("    - %s"%subt(namespace, tags, "%s:%s"%(tname, desc), True, cpp))
            lines.append("")
        if 'returns' in obj:
            for item in obj['returns']:
                if isinstance(item, dict):
                    for key, values in item.items():
                        rname = key
                else:
                    rname = item
                if "$X_RESULT_NOT_READY" == rname:
                    lines.append("    - %s"%subt(namespace, tags, "$x_bool_t:'0' when $X_RESULT_NOT_READY", cpp=cpp))
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
def make_return_type(namespace, tags, obj, cpp=False, decl=False, meta=None):
    # only "return" the parameters declared as "out"
    params = _filter_param_list(obj['params'], ["[out]"])

    types = []
    for p in params:
        if not param_traits.is_optional(p):
            tname = _remove_const_ptr(_get_type_name(namespace, tags, obj, p, cpp, meta))
            if cpp:
                cname = type_traits.find_class_name(p['type'], meta)
                is_handle = type_traits.is_handle(p['type'])

                if cname and not decl and not is_handle:
                    # need to prepend the class name to the type
                    tname = _add_class(tname, subt(namespace, tags, cname, cpp=cpp))

                elif cname and is_handle:
                    # convert handles to class pointers
                    tname = _remove_const_ptr(_get_type_name(namespace, tags, obj, p, cpp, meta))

            types.append(tname)

    if 'returns' in obj:
        for item in obj['returns']:
            if isinstance(item, dict):
                for key, values in item.items():
                    rname = key
            else:
                rname = item
            if "$X_RESULT_NOT_READY" == rname:
                types.append(subt(namespace, tags, "$x_bool_t", cpp=cpp))

    if len(types) == 0:
        # if none exist, then just return "void"
        return "void"
    elif len(types) > 1:
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
def make_pfncb_name(namespace, tags, obj):

    return subt(namespace, tags, "pfn%sCb"%obj['name'])

"""
Public:
    returns the name of a function pointer
"""
def make_pfn_type(namespace, tags, obj, epilogue=""):
    newtags = dict()
    for key, value in tags.items():
        if re.match(namespace, value):
            newtags[key] = "pfn"
    return "%s_%s%s_t"%(namespace, make_func_name(namespace, newtags, obj), epilogue)

"""
Public:
    returns the name of a function pointer
"""
def make_pfncb_type(namespace, tags, obj):

    return make_pfn_type(namespace, tags, obj, epilogue="Cb")

"""
Public:
    returns the name of a function pointer
"""
def make_pfncb_param_type(namespace, tags, obj):

    return "%s_params_t"%_camel_to_snake(make_func_name(namespace, tags, obj))

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
                'name': "pDdiTable",
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
    returns a list of dict of each pfntables needed
"""
def get_pfncbtables(specs, meta, namespace, tags):
    tables = []
    for cname in sorted(meta['class'], key=lambda x: meta['class'][x]['ordinal']):
        objs = get_class_function_objs(specs, cname)
        if len(objs) > 0:
            name = get_table_name(namespace, tags, {'class': cname})
            table = "%s_%s_callbacks_t"%(namespace, _camel_to_snake(name))
            tables.append({
                'name': name, 
                'type': table,
                'functions': objs
            })
    return tables

"""
Public:
    returns a list of dict for converting loader input parameters
"""
def get_loader_prologue(namespace, tags, obj, meta):
    prologue = []

    params = _filter_param_list(obj['params'], ["[in]"])
    for item in params:
        if type_traits.is_class_handle(item['type'], meta):
            name = subt(namespace, tags, item['name'])
            tname = _remove_const_ptr(subt(namespace, tags, item['type']))

            # e.g., "xe_device_handle_t" -> "xe_device_object_t"
            obj_name = re.sub(r"(\w+)_handle_t", r"\1_object_t", tname)

            if type_traits.is_pointer(item['type']):
                range_start = param_traits.range_start(item)
                range_end   = param_traits.range_end(item)
                prologue.append({
                    'name': name,
                    'obj': obj_name,
                    'range': (range_start, range_end)
                })
            else:
                prologue.append({
                    'name': name,
                    'obj': obj_name,
                    'optional': param_traits.is_optional(item)
                })

    return prologue

"""
Public:
    returns a list of dict for converting loader output parameters
"""
def get_loader_epilogue(namespace, tags, obj, meta):
    epilogue = []

    for i, item in enumerate(obj['params']):
        if param_traits.is_release(item) or param_traits.is_output(item) or param_traits.is_inoutput(item):
            if type_traits.is_class_handle(item['type'], meta):
                name = subt(namespace, tags, item['name'])
                tname = _remove_const_ptr(subt(namespace, tags, item['type']))

                obj_name = re.sub(r"(\w+)_handle_t", r"\1_object_t", tname)
                fty_name = re.sub(r"(\w+)_handle_t", r"\1_factory", tname)

                if param_traits.is_range(item):
                    range_start = param_traits.range_start(item)
                    range_end   = param_traits.range_end(item)
                    epilogue.append({
                        'name': name,
                        'type': tname,
                        'obj': obj_name,
                        'factory': fty_name,
                        'release': param_traits.is_release(item),
                        'range': (range_start, range_end)
                    })
                else:
                    epilogue.append({
                        'name': name,
                        'type': tname,
                        'obj': obj_name,
                        'factory': fty_name,
                        'release': param_traits.is_release(item),
                        'optional': param_traits.is_optional(item)
                    })

    return epilogue
