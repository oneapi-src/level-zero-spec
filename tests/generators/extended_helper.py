import re
import sys
sys.path.insert(0, "../../scripts/templates")
from helper import *

def change_case_snake_to_pascal(snake):
    if(len(snake) == 0):
        return ""
    camelCase = re.sub(r"_.", lambda x : x.group(0)[1].upper(), snake)
    PascalCase = camelCase[0].upper() + camelCase[1:]
    return PascalCase
    
def change_case_pascal_to_snake(PascalCase):
    if(len(PascalCase) == 0):
        return ""
    nake_case = re.sub(r"[A-Z]", lambda x : "_" + x.group(0)[0].lower(), PascalCase[1:])
    snake_case = PascalCase[0].lower() + nake_case
    return snake_case
    
def change_case_pascal_to_camel(PascalCase):
    if(len(PascalCase) == 0):
        return ""
    camelCase = PascalCase[0].lower() + PascalCase[1:]
    return camelCase
    
def change_case_camel_to_pascal(camelCase):
    if(len(camelCase) == 0):
        return ""
    PascalCase = camelCase[0].upper() + camelCase[1:]
    return PascalCase

def handle_to_actor_name(handleDefinition):
    expectedPrefix = "$x_"
    expectedSufix = "_handle_t"
    handleName = handleDefinition['name']
    assert(handleName.startswith(expectedPrefix))
    assert(handleName.endswith(expectedSufix))
    return handleName[len(expectedPrefix):-len(expectedSufix)]
    
def class_to_actor_name(classString):
    return change_case_pascal_to_snake(subx(None, classString))

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
    
def make_param_lines_short_no_actor(repl, obj, cls, handles):
    lines = []
    #print(obj)
    params = filter_items(obj['params'], 'class', cls)
    for i, item in enumerate(params):
        if(i == 0 and (item['type'] == handles[class_to_actor_name(cls)]['name'])):
            continue # skip actor param
        name = subx(repl, item['name'])
        type = subx(repl, item['type'])

        if i < len(params)-1:
            prologue = "%s %s,"%(type, name)
        else:
            prologue = "%s %s"%(type, name)

        lines.append("%s"%prologue)
    return lines
    
def merge_into_single_line(lines):
    return " ".join(lines)
    
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

def make_driver_frontend_class_name(name):
    return "I"+change_case_snake_to_pascal(name)

def make_driver_frontend_class_member_func_declaration_name(repl, obj, cls):
    return change_case_pascal_to_camel(subx(repl, obj['name']))
    
def make_params_list_single_line(obj, cls, first = 0, precedeWithComaIfNonempty = False):
    params = filter_items(obj['params'], 'class', cls)
    concatenated =  ", ".join(param['name'] for param in params[first:])
    if((len(concatenated) != 0) and precedeWithComaIfNonempty):
        concatenated = ", " + concatenated
    return concatenated
    
def get_param(obj, cls, id):
    params = filter_items(obj['params'], 'class', cls)
    return params[id]
    
def get_num_params(obj, cls):
    params = filter_items(obj['params'], 'class', cls)
    return len(params)
    