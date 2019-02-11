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

def make_abc_line(lformat, rformat, repl, a, b, c):
    lhalf = lformat%(subx(repl,a), subx(repl,b))
    rhalf = rformat%(subx(repl,c,True))
    return "%s%s"%(append_ws(lhalf, 48), rhalf)

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

def make_param_lines(repl, obj):
    lines = []
    for i, item in enumerate(obj['params']):
        if i < len(obj['params'])-1:
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

def make_return_lines(repl, obj):
    lines = []
    lines.append("@returns")
    lines.append("    - %s"%subx(repl, "$X_RESULT_SUCCESS", True))
    lines.append("    - %s"%subx(repl, "$X_RESULT_ERROR_UNINITIALIZED", True))
    lines.append("    - %s"%subx(repl, "$X_RESULT_ERROR_UNSUPPORTED", True))

    for item in obj['returns']:
        if isinstance(item, dict):
            for key, values in item.items():
                lines.append("    - %s"%subx(repl, key, True))
                for val in values:
                    lines.append("        + %s"%subx(repl, val, True))
        else:
            lines.append("    - %s"%subx(repl, item, True))
    return lines

def make_func_name(repl, obj):
    return subx(repl, "%s%s"%(obj['class'], obj['name']))


