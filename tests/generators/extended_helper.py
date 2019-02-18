import re
import sys
sys.path.insert(0, "../../scripts/templates")
from helper import *

"""
    returns a list of strings for each parameter of a function
    comments are ignored
"""
def make_param_lines_short(repl, obj, cls):
    lines = []
    params = filter_items(obj['params'], 'class', cls)
    for i, item in enumerate(params):
        name = subx(repl, item['name'])
        type = subx(repl, item['type'])

        if i < len(params)-1:
            prologue = "%s %s,"%(type, name)
        else:
            prologue = "%s %s"%(type, name)

        lines.append("%s"%prologue)
    return lines
    
"""
    returns a list of strings for each parameter of a function
    comments are ignored
"""
def make_param_values_lines_short(repl, obj, cls):
    lines = []
    params = filter_items(obj['params'], 'class', cls)
    for i, item in enumerate(params):
        name = subx(repl, item['name'])

        if i < len(params)-1:
            prologue = "%s,"%name
        else:
            prologue = "%s"%name

        lines.append("%s"%prologue)
    return lines
