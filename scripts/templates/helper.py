import re

def subx(repl, string, tag=False):
    string = re.sub(r"\$Xx", repl.title(), string)
    string = re.sub(r"\-\$x", "-"+repl, string) #hack
    repl = "::"+repl if tag else repl
    string = re.sub(r"\$x", repl, string)
    string = re.sub(r"\$X", repl.upper(), string)
    return string

def append_ws(string, count):
    while len(string) > count:
        count = count + 4
    string = '{str: <{width}}'.format(str=string, width=count)
    return string

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

def filter_items(lst, key, filter):
    flst = []
    for item in lst:
        if key in item:
            if filter != item[key]:
                continue
        flst.append(item)
    return flst

def make_etor_lines(repl, obj):
    lines = []
    for item in obj['etors']:
        if 'value' in item:
            prologue = "%s = %s,"%(subx(repl, item['name']), subx(repl, item['value']))
        else:
            prologue = "%s,"%(subx(repl, item['name']))

        for line in split_line(subx(repl, item['desc'], True), 70):
            lines.append("%s///< %s"%(append_ws(prologue, 48), line))
            prologue = ""
    return lines


def make_member_lines(repl, obj):
    lines = []
    for item in obj['members']:
        prologue = "%s %s;"%(subx(repl, item['type']), subx(repl, item['name']))
        for line in split_line(subx(repl, item['desc'], True), 70):
            lines.append("%s///< %s"%(append_ws(prologue, 48), line))
            prologue = ""
    return lines

def make_param_lines(repl, obj, cls):
    lines = []
    params = filter_items(obj['params'], 'class', cls)
    for i, item in enumerate(params):
        if i < len(params)-1:
            prologue = "%s %s,"%(subx(repl, item['type']), subx(repl, item['name']))
        else:
            prologue = "%s %s"%(subx(repl, item['type']), subx(repl, item['name']))

        for line in split_line(subx(repl, item['desc'], True), 70):
            lines.append("%s///< %s"%(append_ws(prologue, 48), line))
            prologue = ""
    return lines

def make_desc_lines(repl, obj):
    lines = []
    prologue = "@brief"
    for line in split_line(subx(repl, obj['desc'], True), 70):
        lines.append("%s %s"%(prologue, line))
        prologue = "      "
    return lines

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

def make_param_checks(repl, obj, cls, tag=False):
    checks = {}
    eip = subx(repl, "$X_RESULT_ERROR_INVALID_PARAMETER", tag)
    eus = subx(repl, "$X_RESULT_ERROR_UNSUPPORTED", tag)
    checks[eip] = []
    checks[eus] = []

    params = filter_items(obj['params'], 'class', cls)
    for item in params:
        if not re.match(r".*\[optional\].*", item['desc']): #skip optional params
            if re.match(r".*\w+\*+", item['type']): # pointer-type
                checks[eip].append("nullptr == %s"%subx(repl, item['name'], tag))
            elif re.match(r".*handle_t.*", item['type']): # handle-type
                checks[eip].append("nullptr == %s"%subx(repl, item['name'], tag))

            if re.match(r".*desc_t.*", item['type']): # descriptor-type
                checks[eus].append("%s <= %s->version"%(re.sub(r"\w*\s*(.*)_t.*", r"\1_VERSION", subx(repl, item['type'], tag)).upper(), item['name']))
    return checks

def make_return_lines(repl, obj, cls):
    lines = []
    lines.append("@returns")
    lines.append("    - %s"%subx(repl, "$X_RESULT_SUCCESS", True))
    lines.append("    - %s"%subx(repl, "$X_RESULT_ERROR_UNINITIALIZED", True))

    # generate default checks
    gen = make_param_checks(repl, obj, cls, True)

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

def get_class_list(obj):
    if 'class' in obj:
        if isinstance(obj['class'], list):
            return obj['class']
        else:
            return [obj['class']]
    else:
        return ['none']

def make_func_name(repl, obj, cls):
    return subx(repl, "%s%s"%(cls, obj['name']))


