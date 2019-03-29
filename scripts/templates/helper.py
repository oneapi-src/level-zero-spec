import re

"""
    substitues each tag['key'] with tag['value']
    if cpp, then remove each tag['key'] if matches namespace
    if comment, then insert doxygen '::' notation at beginning (for autogen links)
"""
def subt(namespace, tags, string, comment=False, cpp=False):
    for key, value in tags.items():
        if cpp and re.match(namespace, value):
            string = re.sub(r"%s_?"%re.escape("-"+key), "-", string) #hack
            repl = "::" if comment and "$OneApi" != key else ""
            string = re.sub(r"%s_?"%re.escape(key), repl, string)
            string = re.sub(r"%s_?"%re.escape(key.upper()), repl.upper(), string)
        else:
            string = re.sub(r"-%s"%re.escape(key), "-"+value, string) #hack
            repl = "::"+value if comment and "$OneApi" != key else value+"::" if cpp else value
            string = re.sub(re.escape(key), repl, string)
            string = re.sub(re.escape(key.upper()), repl.upper(), string)
    return string

"""
    appends whitespace (in multiples of 4) to the end of the string,
    until len(string) > count
"""
def append_ws(string, count):
    while len(string) > count:
        count = count + 4
    string = '{str: <{width}}'.format(str=string, width=count)
    return string

"""
    split the line of text into a list of strings,
    where each length of each entry is less-than count
"""
def split_line(line, ch_count):
    if not line:
        return []

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
    removes items from the list with the key and whose value do not match filter
"""
def filter_items(lst, key, filter):
    flst = []
    for item in lst:
        if key in item:
            if filter in item[key]:
                flst.append(item)
    return flst

"""
    returns a list of items with key from a list of dict
"""
def extract_items(lst, key):
    klst = []
    for item in lst:
        if key in item:
            klst.append(item[key])
    return klst

"""
    returns a list of all objects in all specs
"""
def extract_objs(specs, type):
    objs = []
    for s in specs:
        for obj in s['objects']:
            if re.match(type, obj['type']):
                objs.append(obj)
    return objs

"""
    returns the type to which name belongs, if it is known
    i.e. if the name is an etor, return the name of the enum
"""
def get_typename(name, meta, type):
    if meta:
        name = re.sub(r"(\$\w+)\(.*\)", r"\1", name) # removes '()' part of macros
        name = re.sub(r"\w+\[(\$\w+)\]", r"\1", name) # extracts array size '[]' part of types
        if name in meta[type]:
            return name
        for entry in meta[type]:
            if name in meta[type][entry]:
                return entry
    return None

"""
    returns proper name of etor
"""
def make_etor_name(namespace, tags, enum, etor, cpp):
    if cpp:
        prefix = re.sub(r"(\w+)_t", r"\1", subt(namespace, tags, enum, cpp=cpp)).upper()
        name = re.sub(r"%s_(\w+)"%prefix, r"\1", subt(namespace, tags, etor, cpp=cpp))
        name = re.sub(r"^(\d+\w+)", r"_\1", name) #todo: .lower()?
    else:
        name = subt(namespace, tags, etor)
    return name

"""
    returns proper name of value
"""
def make_cpp_value_name(namespace, tags, value, cpp, meta):
    macro = get_typename(value, meta, 'macro')
    enum = get_typename(value, meta, 'enum')
    if macro:
        value = subt(namespace, tags, value)
    elif enum:
        value = "%s::%s"%(subt(namespace, tags, enum, cpp=cpp), make_etor_name(namespace, tags, enum, value, cpp))
    else:
        value = subt(namespace, tags, value, cpp=cpp)
    return value

"""
    returns a list of strings for each enumerator in an enumeration
"""
def make_etor_lines(namespace, tags, obj, cpp=False, meta=None):
    lines = []
    for item in obj['etors']:
        name = make_etor_name(namespace, tags, obj['name'], item['name'], cpp)

        if 'value' in item:
            value = make_cpp_value_name(namespace, tags, item['value'], cpp, meta)
            prologue = "%s = %s,"%(name, value)
        else:
            prologue = "%s,"%(name)

        for line in split_line(subt(namespace, tags, item['desc'], True, cpp), 70):
            lines.append("%s///< %s"%(append_ws(prologue, 48), line))
            prologue = ""
    return lines

"""
    returns a list of strings for each member of a structure or class
"""
def make_member_lines(namespace, tags, obj, cpp=False, meta=None):
    lines = []
    if 'members' not in obj:
        return lines

    for item in obj['members']:
        if cpp:
            name = make_cpp_value_name(namespace, tags, item['name'], cpp, meta)
        else:
            name = subt(namespace, tags, item['name'], cpp=cpp)
        type = subt(namespace, tags, item['type'], cpp=cpp)

        if cpp and 'init' in item:
            value = make_cpp_value_name(namespace, tags, item['init'], cpp, meta)
            prologue = "%s %s = %s;"%(type, name, value)
        else:
            prologue = "%s %s;"%(type, name)

        for line in split_line(subt(namespace, tags, item['desc'], True, cpp), 70):
            lines.append("%s///< %s"%(append_ws(prologue, 48), line))
            prologue = ""
    return lines

"""
    returns a list of strings for each member of a class
"""
def make_member_function_lines(namespace, tags, obj):
    lines = []
    if 'members' not in obj:
        return lines

    for item in obj['members']:
        name = subt(namespace, tags, item['name'], cpp=True)
        lines.append("auto get%s( void ) const { return %s; }"%(name.title(), name))
    return lines

"""
    returns the list of parameters, filtering either inputs or outputs
"""
def filter_param_list(params, in_or_out):
    lst = []
    for p in params:
        if "in" == in_or_out and re.match(r"\[\s*in.*", p['desc']):
            lst.append(p)
        elif "out" == in_or_out and re.match(r"\[\s*out.*", p['desc']):
            lst.append(p)
    return lst

"""
    returns a list of strings for each parameter of a function
"""
def make_param_lines(namespace, tags, obj, cpp=False):
    lines = []

    if cpp:
        if ('decl' in obj and re.match(r"static", obj['decl'])) or \
           ('class' in obj and re.match(r"\$x$", obj['class'])):
            params = filter_param_list(obj['params'], "in")
        else:
            params = filter_param_list(obj['params'][1:], "in")
    else:
        params = obj['params']

    for i, item in enumerate(params):
        name = subt(namespace, tags, item['name'], cpp=cpp)
        type = subt(namespace, tags, item['type'], cpp=cpp)

        if i < len(params)-1:
            prologue = "%s %s,"%(type, name)
        else:
            prologue = "%s %s"%(type, name)

        for line in split_line(subt(namespace, tags, item['desc'], True, cpp), 70):
            lines.append("%s///< %s"%(append_ws(prologue, 48), line))
            prologue = ""

    if len(lines) > 0:
        return lines
    else:
        return ["void"]

"""
    returns a string of parameter names for passing to a function
"""
def make_param_call_str(prologue, obj, cpp=False):
    if cpp:
        if 'decl' in obj and re.match(r"static", obj['decl']):
            params = filter_param_list(obj['params'], "in")
        else:
            params = filter_param_list(obj['params'][1:], "in")
    else:
        params = obj['params']

    names = []
    if len(prologue) > 0:
        names.append(prologue)
    for item in params:
#        if re.match(r"\$\w+_handle_t", item['type']):
#            names.append("%s->getHandle()"%item['name'])
#        else:
            names.append(item['name'])
    return ", ".join(names)
    
"""
    returns a list of strings for the description
"""
def make_desc_lines(namespace, tags, obj, cpp=False):
    lines = []
    prologue = "@brief"
    for line in split_line(subt(namespace, tags, obj['desc'], True, cpp), 70):
        lines.append("%s %s"%(prologue, line))
        prologue = "      "
    return lines

"""
    returns a list of strings for the detailed description
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
    returns a dict of auto-generated parameter validation checks
"""
def make_param_checks(namespace, tags, obj, comment=False, cpp=False):
    checks = {}
    eip = subt(namespace, tags, "$X_RESULT_ERROR_INVALID_PARAMETER", comment, cpp)
    eus = subt(namespace, tags, "$X_RESULT_ERROR_UNSUPPORTED", comment, cpp)
    checks[eip] = []
    checks[eus] = []

    for item in obj['params']:
        if not re.match(r".*\[optional\].*", item['desc']): #skip optional params
            if re.match(r".*\w+\*+", item['type']): # pointer-type
                checks[eip].append("nullptr == %s"%subt(namespace, tags, item['name'], comment, cpp))
            elif re.match(r".*handle_t.*", item['type']): # handle-type
                checks[eip].append("nullptr == %s"%subt(namespace, tags, item['name'], comment, cpp))

            if re.match(r".*desc_t.*", item['type']): # descriptor-type
                checks[eus].append("%s < %s->version"%(re.sub(r"\w*\s*(.*)_t.*", r"\1_VERSION_CURRENT", subt(namespace, tags, item['type'], comment, cpp)).upper(), item['name']))
    return checks

"""
    returns a list of strings for possible return values
"""
def make_returns_lines(namespace, tags, obj, cpp=False):
    lines = []
    if cpp:
        params = filter_param_list(obj['params'], "out")
        if len(params) > 0:
            lines.append("@returns")
            for p in params:
                lines.append("    - %s"%subt(namespace, tags, re.sub(r"(.*)\*", r"\1:%s"%re.sub(r"\[.*\](.*)", r"\1", p['desc']), p['type']), True, cpp))
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
    returns string for declaring function return type
"""
def make_return_value(namespace, tags, obj, cpp=False, decl=False):
    if decl and 'decl' in obj:
        prologue = "static " if re.match("singleton", obj['decl']) else "%s "%obj['decl']
    else:
        prologue = ""

    params = filter_param_list(obj['params'], "out")
    if len(params) == 0:
        return prologue+"void"

    types = []
    for p in params:
        types.append(subt(namespace, tags, re.sub(r"(.*)\*", r"\1", p['type']), cpp=cpp))

    if len(types) > 1:
        return prologue+"std::tuple<%s>"%", ".join(types)
    else:
        return prologue+types[0]

"""
    returns the name of a function
"""
def make_func_name(namespace, tags, obj, cpp=False):
    if not cpp and 'class' in obj:
        cls = obj['class']
    else:
        cls = ""
    return subt(namespace, tags, "%s%s"%(cls, obj['name']), cpp=cpp)

"""
    returns the name of a class
"""
def make_class_name(namespace, tags, obj):
    name = subt(namespace, tags, obj['name'], cpp=True)
    if 'base' in obj:
        name += " : public %s"%(subt(namespace, tags, obj['base'], cpp=True))
    return name

"""
    returns a single-line driver function call
"""
def make_obj_accessor(tags, obj):
    null_tags = {}
    for key, value in tags.items():
        null_tags[key] = ""

    method = obj['name']

    if 'class' in obj:
        cls = obj['class']
    else:
        cls = ""

    if 'decl' in obj:
        decl_type = obj['decl']
    else:
        decl_type = ""

    noobject = decl_type == "static"
    if noobject:
        method = subt("", null_tags, cls) + method

    singleton = decl_type == "singleton"
    method = method[0].lower() + method[1:]
    if noobject:
        str = subt("", null_tags, "%s("%(method))
        str += make_param_call_str("", obj)
    elif singleton:
        str = subt("", null_tags, "%s::get()->%s("%(cls, method))
        str += make_param_call_str("", obj)
    else:
        params = obj['params']
        str = subt("", null_tags, "%s::fromHandle("%cls)
        argStr=""
        lastArg=""
        calledMethod=False
        for item in params:
            if len(lastArg) == 0:
                #First must match class name
                if item['name'][1:] == subt("", null_tags, cls):
                    str += item['name'] + ")->" + method + "("
                    calledMethod=True
                elif item.get('class',"") == "":
                    argStr += item['name']
                    lastArg=item['name']
            else:
                if len(argStr) > 0:
                    argStr += ", "
                argStr += item['name']
                lastArg=item['name']
        if not calledMethod:
            str += ")->" + method + "("
        str += argStr
    str += ");"
    return str
