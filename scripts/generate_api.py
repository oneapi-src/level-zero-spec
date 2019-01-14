import os
import re
import util

def generate_cpp_api_headers(path, namespace, specs):
    loc = 0
    for s in specs:
        input = os.path.join("templates", "api.h.mako")
        output = os.path.join(path, "%s_%s.h"%(namespace, s['name']))
        print("Generating %s..."%output)
        loc += util.makoWrite(input, output,
            x=namespace,
            name = s['name'],
            docs = s['docs'])
    return loc

def generate_all(path, namespace, specs):
    loc = 0
    loc += generate_cpp_api_headers(path, namespace, specs)
    print("Generated %s lines of code"%loc)
