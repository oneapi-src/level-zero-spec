import os
import util

def generate_cpp_api_headers(options,specs):
    for s in specs:
        input = os.path.join("templates", "api.h.mako")
        output = os.path.join("..", "%s_%s.h"%(options['namespace'], s['name']))
        util.makoWrite(input, output,
            x=options['namespace'],
            name = s['name'],
            docs = s['docs'])

def generate_all(options,specs):
    generate_cpp_api_headers(options,specs)
