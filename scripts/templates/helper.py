import re

"""
    substitues $x variations with repl in string
    if repl is None, then remove $x and any following '_'
    if tag = True, then insert doxygen '::' tags at beginning (for autogen links)
"""
def subx(repl, string, tag=False):
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
            if filter != item[key]:
                continue
        flst.append(item)
    return flst

"""
    returns a list of strings for each enumerator in an enumeration
"""
def make_etor_lines(repl, obj, trim=False):
    lines = []
    for item in obj['etors']:
        if trim:
            prefix = re.sub(r"(\w+)_t", r"\1", subx(repl, obj['name'])).upper()
            name = re.sub(r"%s_(\w+)"%prefix, r"\1", subx(repl, item['name']))
            name = re.sub(r"(\d+\w+)", r"_\1", name)
        else:
            name = subx(repl, item['name'])

        if 'value' in item:
            value = subx(repl, item['value'])
            prologue = "%s = %s,"%(name, value)
        else:
            prologue = "%s,"%(name)

        for line in split_line(subx(repl, item['desc'], True), 70):
            lines.append("%s///< %s"%(append_ws(prologue, 48), line))
            prologue = ""
    return lines

"""
    returns a list of strings for each member of a structure or class
"""
def make_member_lines(repl, obj, init=False):
    lines = []
    for item in obj['members']:
        name = subx(repl, item['name'])
        type = subx(repl, item['type'])

        if init:
            value = "0"
            prologue = "%s %s = %s;"%(type, name, value)
        else:
            prologue = "%s %s;"%(type, name)

        for line in split_line(subx(repl, item['desc'], True), 70):
            lines.append("%s///< %s"%(append_ws(prologue, 48), line))
            prologue = ""
    return lines

"""
    returns a list of strings for each parameter of a function
"""
def make_param_lines(repl, obj, filter):
    lines = []

    if re.match(r"this", filter):
        params = filter_items(obj['params'][1:], 'class', filter)
    else:
        params = filter_items(obj['params'], 'class', filter)

    for i, item in enumerate(params):
        name = subx(repl, item['name'])
        type = subx(repl, item['type'])

        if i < len(params)-1:
            prologue = "%s %s,"%(type, name)
        else:
            prologue = "%s %s"%(type, name)

        for line in split_line(subx(repl, item['desc'], True), 70):
            lines.append("%s///< %s"%(append_ws(prologue, 48), line))
            prologue = ""
    return lines

"""
    returns a string of parameter names for passing to a function
"""
def make_param_call_str(prologue, repl, obj, filter):
    str = prologue

    if re.match(r"this", filter):
        params = filter_items(obj['params'][1:], 'class', filter)
    else:
        params = filter_items(obj['params'], 'class', filter)

    for item in params:
        if len(str) > 0:
            str += ", "
        str += subx(repl, item['name'])
    return str

"""
    returns a list of strings for the description
"""
def make_desc_lines(repl, obj):
    lines = []
    prologue = "@brief"
    for line in split_line(subx(repl, obj['desc'], True), 70):
        lines.append("%s %s"%(prologue, line))
        prologue = "      "
    return lines

"""
    returns a list of strings for the detailed description
"""
def make_details_lines(repl, obj):
    lines = []
    if 'details' in obj:
        lines.append("")
        lines.append("@details")

        for item in obj['details']:
            if isinstance(item, dict):
                for key, values in item.items():
                    prologue = "    -"
                    for line in split_line(subx(repl, key, True), 70):
                        lines.append("%s %s"%(prologue, line))
                        prologue = "     "
                    for val in values:
                        prologue = "        +"
                        for line in split_line(subx(repl, val, True), 66):
                            lines.append("%s %s"%(prologue, line))
                            prologue = "         "
            else:
                prologue = "    -"
                for line in split_line(subx(repl, item, True), 70):
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
def make_param_checks(repl, obj, filter, tag=False):
    checks = {}
    eip = subx(repl, "$X_RESULT_ERROR_INVALID_PARAMETER", tag)
    eus = subx(repl, "$X_RESULT_ERROR_UNSUPPORTED", tag)
    checks[eip] = []
    checks[eus] = []

    params = filter_items(obj['params'], 'class', filter)
    for item in params:
        if not re.match(r".*\[optional\].*", item['desc']): #skip optional params
            if re.match(r".*\w+\*+", item['type']): # pointer-type
                checks[eip].append("nullptr == %s"%subx(repl, item['name'], tag))
            elif re.match(r".*handle_t.*", item['type']): # handle-type
                checks[eip].append("nullptr == %s"%subx(repl, item['name'], tag))

            if re.match(r".*desc_t.*", item['type']): # descriptor-type
                checks[eus].append("%s < %s->version"%(re.sub(r"\w*\s*(.*)_t.*", r"\1_VERSION", subx(repl, item['type'], tag)).upper(), item['name']))
    return checks

"""
    returns a list of strings for possible return values
"""
def make_return_lines(repl, obj, filter):
    lines = []
    lines.append("@returns")
    lines.append("    - %s"%subx(repl, "$X_RESULT_SUCCESS", True))
    lines.append("    - %s"%subx(repl, "$X_RESULT_ERROR_UNINITIALIZED", True))
    lines.append("    - %s"%subx(repl, "$X_RESULT_ERROR_DEVICE_LOST", True))

    # generate default checks
    gen = make_param_checks(repl, obj, filter, True)

    # merge user-specified values
    if 'returns' in obj:
        for item in obj['returns']:
            if isinstance(item, dict):
                for key, values in item.items():
                    key = subx(repl, key, True)
                    if key not in gen:
                        gen[key] = []
                    for val in values:
                        gen[key].append(subx(repl, val, True))
            else:
                key = subx(repl, item, True)
                if key not in gen:
                    gen[key] = []

    # now make combined lines
    for key, values in gen.items():
        lines.append("    - %s"%key)
        for val in values:
            lines.append("        + %s"%val)
    return lines

"""
    returns the name of a function
"""
def make_func_name(repl, obj, cls, cpp=False):
    if cpp:
        return subx(repl, "%s::%s"%(cls, obj['name']))
    else:
        return subx(repl, "%s%s"%(cls, obj['name']))

"""
    returns the name of a function
"""
def make_obj_accessor(repl, obj, cls):
    noobject = repl == subx(repl, cls)
    singleton=re.match(subx(repl, "^$xDriver"), subx(repl, cls))
    method = obj['name'][0].lower() + obj['name'][1:] 
    if noobject:
        str = subx("", "%s("%(method))
        str += make_param_call_str("", "", obj, "")
    elif singleton:
        str = subx("", "%s::get()->%s("%(cls, method))
        str += make_param_call_str("", "", obj, "")
    else:
        params = obj['params']
        str = subx("", "%s::fromHandle("%cls)
        argStr=""
        lastArg=""
        calledMethod=False
        for item in params:
            if len(lastArg) == 0:
                #First must match class name
                if item['name'] == subx("h",cls):
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

"""
    returns a list of all function objects that belong to the class
"""
def get_member_funcs(cls, specs):
    # find all the functions that belong to this class
    funcs = []
    for s in specs:
        for obj in s['objects']:
            if re.match(r"function", obj['type']):
                if cls in obj['class']:
                    funcs.append(obj)
    return funcs
