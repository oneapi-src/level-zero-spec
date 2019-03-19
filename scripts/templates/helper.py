import re

"""
    substitues $x variations with namespace in string
    if namespace is None, then remove $x and any following '_'
    if tag = True, then insert doxygen '::' tags at beginning (for autogen links)
"""
def _subx(repl, string, tag):
    if repl:
        string = re.sub(r"\$Xx", repl.title(), string)
        string = re.sub(r"\-\$x", "-"+repl, string) #hack
        repl = "::"+repl if tag else repl
        string = re.sub(r"\$x", repl, string)
        string = re.sub(r"\$X", repl.upper(), string)
    else:
        string = re.sub(r"\-\$x_?", "-", string) #hack
        repl = "::" if tag else ""
        string = re.sub(r"\$x_?", repl, string)
        string = re.sub(r"\$X_", repl.upper(), string)
    return string
def _suby(repl, string, tag):
    if repl:
        string = re.sub(r"\$Yy", repl.title(), string)
        string = re.sub(r"\-\$y", "-"+repl, string) #hack
        repl = "::"+repl if tag else repl
        string = re.sub(r"\$y", repl, string)
        string = re.sub(r"\$Y", repl.upper(), string)
    else:
        string = re.sub(r"\-\$y_?", "-", string) #hack
        repl = "::" if tag else ""
        string = re.sub(r"\$y_?", repl, string)
        string = re.sub(r"\$Y_", repl.upper(), string)
    return string
def sub(namespace, string, tag=False):
    if namespace:
        string = _subx(namespace[0], string, tag)
    else:
        string = _subx(None, string, tag)

    if namespace and len(namespace) > 1:
        string = _suby(namespace[1], string, tag)
    else:
        string = _suby(None, string, tag)
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
    words           = line.split(" ")
    lines           = []
    word_list       = []
    for word in words:
        if re.match(r"(.*)\n", word):
            word_list.append(re.sub(r"(.*)\n",r"\1",word))
            lines.append(" ".join(word_list))
            word_list = []
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
def make_etor_name(namespace, enum, etor, trim):
    if trim:
        prefix = re.sub(r"(\w+)_t", r"\1", sub(namespace, enum)).upper()
        name = re.sub(r"%s_(\w+)"%prefix, r"\1", sub(namespace, etor))
        name = re.sub(r"^(\d+\w+)", r"_\1", name) #todo: .lower()?
    else:
        name = sub(namespace, etor)
    return name

"""
    returns proper name of value
"""
def make_value_name(namespace, alt_namespace, value, meta, trim=False):
    macro = get_typename(value, meta, 'macro')
    enum = get_typename(value, meta, 'enum')
    if macro:
        value = sub(alt_namespace, value)
    elif enum:
        value = "%s::%s"%(sub(namespace, enum), make_etor_name(namespace, enum, value, trim))
    else:
        value = sub(namespace, value)
    return value

"""
    returns a list of strings for each enumerator in an enumeration
"""
def make_etor_lines(namespace, obj, cpp=False, alt_namespace=[""], meta=None):
    lines = []
    for item in obj['etors']:
        name = make_etor_name(namespace, obj['name'], item['name'], cpp)

        if 'value' in item:
            value = make_value_name(namespace, alt_namespace, item['value'], meta, cpp)
            prologue = "%s = %s,"%(name, value)
        else:
            prologue = "%s,"%(name)

        for line in split_line(sub(namespace, item['desc'], True), 70):
            lines.append("%s///< %s"%(append_ws(prologue, 48), line))
            prologue = ""
    return lines

"""
    returns a list of strings for each member of a structure or class
"""
def make_member_lines(namespace, obj, cpp=False, alt_namespace=[""], meta=None):
    lines = []
    if 'members' not in obj:
        return lines

    for item in obj['members']:
        if cpp:
            name = make_value_name(namespace, alt_namespace, item['name'], meta)
        else:
            name = sub(namespace, item['name'])
        type = sub(namespace, item['type'])

        if cpp and 'init' in item:
            value = make_value_name(namespace, alt_namespace, item['init'], meta, True)
            prologue = "%s %s = %s;"%(type, name, value)
        else:
            prologue = "%s %s;"%(type, name)

        for line in split_line(sub(namespace, item['desc'], True), 70):
            lines.append("%s///< %s"%(append_ws(prologue, 48), line))
            prologue = ""
    return lines

"""
    returns a list of strings for each member of a class
"""
def make_member_function_lines(namespace, obj):
    lines = []
    if 'members' not in obj:
        return lines

    for item in obj['members']:
        name = sub(namespace, item['name'])
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
def make_param_lines(namespace, obj, cpp=False):
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
        name = sub(namespace, item['name'])
        type = sub(namespace, item['type'])

        if i < len(params)-1:
            prologue = "%s %s,"%(type, name)
        else:
            prologue = "%s %s"%(type, name)

        for line in split_line(sub(namespace, item['desc'], True), 70):
            lines.append("%s///< %s"%(append_ws(prologue, 48), line))
            prologue = ""

    if len(lines) > 0:
        return lines
    else:
        return ["void"]

"""
    returns a string of parameter names for passing to a function
"""
def make_param_call_str(prologue, namespace, obj, cpp=False):
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
    returns a string of parameter names for forwarding to a function
"""
def make_forwarding_param_call_str(namespace, obj):
    return ", ".join([item['name'] for item in obj['params']])

"""
    returns a list of strings for the description
"""
def make_desc_lines(namespace, obj):
    lines = []
    prologue = "@brief"
    for line in split_line(sub(namespace, obj['desc'], True), 70):
        lines.append("%s %s"%(prologue, line))
        prologue = "      "
    return lines

"""
    returns a list of strings for the detailed description
"""
def make_details_lines(namespace, obj):
    lines = []
    if 'details' in obj:
        lines.append("")
        lines.append("@details")

        for item in obj['details']:
            if isinstance(item, dict):
                for key, values in item.items():
                    prologue = "    -"
                    for line in split_line(sub(namespace, key, True), 70):
                        lines.append("%s %s"%(prologue, line))
                        prologue = "     "
                    for val in values:
                        prologue = "        +"
                        for line in split_line(sub(namespace, val, True), 66):
                            lines.append("%s %s"%(prologue, line))
                            prologue = "         "
            else:
                prologue = "    -"
                for line in split_line(sub(namespace, item, True), 70):
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
def make_param_checks(namespace, obj, tag=False):
    checks = {}
    eip = sub(namespace, "$X_RESULT_ERROR_INVALID_PARAMETER", tag)
    eus = sub(namespace, "$X_RESULT_ERROR_UNSUPPORTED", tag)
    checks[eip] = []
    checks[eus] = []

    for item in obj['params']:
        if not re.match(r".*\[optional\].*", item['desc']): #skip optional params
            if re.match(r".*\w+\*+", item['type']): # pointer-type
                checks[eip].append("nullptr == %s"%sub(namespace, item['name'], tag))
            elif re.match(r".*handle_t.*", item['type']): # handle-type
                checks[eip].append("nullptr == %s"%sub(namespace, item['name'], tag))

            if re.match(r".*desc_t.*", item['type']): # descriptor-type
                checks[eus].append("%s < %s->version"%(re.sub(r"\w*\s*(.*)_t.*", r"\1_VERSION_CURRENT", sub(namespace, item['type'], tag)).upper(), item['name']))
    return checks

"""
    returns a list of strings for possible return values
"""
def make_returns_lines(namespace, obj, cpp=False):
    lines = []
    if cpp:
        params = filter_param_list(obj['params'], "out")
        if len(params) > 0:
            lines.append("@returns")
            for p in params:
                lines.append("    - %s"%sub(namespace, re.sub(r"(.*)\*", r"\1:%s"%re.sub(r"\[.*\](.*)", r"\1", p['desc']), p['type'])))
            lines.append("")
        lines.append("@throws result_t")
        return lines

    lines.append("@returns")
    lines.append("    - %s"%sub(namespace, "$X_RESULT_SUCCESS", True))
    lines.append("    - %s"%sub(namespace, "$X_RESULT_ERROR_UNINITIALIZED", True))
    lines.append("    - %s"%sub(namespace, "$X_RESULT_ERROR_DEVICE_LOST", True))

    # generate default checks
    gen = make_param_checks(namespace, obj, True)

    # merge user-specified values
    if 'returns' in obj:
        for item in obj['returns']:
            if isinstance(item, dict):
                for key, values in item.items():
                    key = sub(namespace, key, True)
                    if key not in gen:
                        gen[key] = []
                    for val in values:
                        gen[key].append(sub(namespace, val, True))
            else:
                key = sub(namespace, item, True)
                if key not in gen:
                    gen[key] = []

    # now make combined lines
    for key, values in gen.items():
        lines.append("    - %s"%key)
        for val in values:
            lines.append("        + %s"%val)
    return lines

"""
"""
def make_return_value(namespace, obj, cpp=False):
    if cpp and 'decl' in obj:
        decl = "%s "%obj['decl']
    else:
        decl = ""

    params = filter_param_list(obj['params'], "out")
    if len(params) == 0:
        return decl+"void"

    types = []
    for p in params:
        types.append(sub(namespace, re.sub(r"(.*)\*", r"\1", p['type'])))

    if len(types) > 1:
        return decl+"std::tuple<%s>"%", ".join(types)
    else:
        return decl+types[0]

"""
    returns the name of a function
"""
def make_func_name(namespace, obj, cpp=False):
    if not cpp and 'class' in obj:
        cls = obj['class']
    else:
        cls = ""
    return sub(namespace, "%s%s"%(cls, obj['name']))

"""
    returns a single-line driver function call
"""
def make_obj_accessor(namespace, obj):
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
        method = sub([""], cls) + method

    singleton = decl_type == "singleton"
    method = method[0].lower() + method[1:]
    if noobject:
        str = sub([""], "%s("%(method))
        str += make_param_call_str("", "", obj)
    elif singleton:
        str = sub([""], "%s::get()->%s("%(cls, method))
        str += make_param_call_str("", "", obj)
    else:
        params = obj['params']
        str = sub([""], "%s::fromHandle("%cls)
        argStr=""
        lastArg=""
        calledMethod=False
        for item in params:
            if len(lastArg) == 0:
                #First must match class name
                if item['name'] == sub(["h"],cls):
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
