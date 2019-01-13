import os
import util

def generate_cpp_api_headers(path, namespace, specs):
    for s in specs:
        input = os.path.join("templates", "api.h.mako")
        output = os.path.join(path, "%s_%s.h"%(namespace, s['name']))
        print("Writing %s..."%output)
        util.makoWrite(input, output,
            x=namespace,
            name = s['name'],
            docs = s['docs'])

def generate_all(path, namespace, specs):
    generate_cpp_api_headers(path, namespace, specs)
