import os
import re
import util

def generate_cpp_headers(path, namespace, specs, driver):
    loc = 0
    for s in specs:
        input = os.path.join("templates", "api.h.mako")
        output = os.path.join(path, "%s_%s.h"%(namespace, s['name']))
        print("Generating %s..."%output)
        loc += util.makoWrite(input, output,
            x=namespace,
            X=namespace.upper(),
            Xx=namespace.title(),
            name = s['name'],
            docs = s['docs'],
            driver=driver)
    print("Generated %s lines of code"%loc)
    return loc
    
