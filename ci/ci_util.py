import os
import sys
import importlib


"""
    loads module from an explicit pathname
"""
def load_module_from_file(module_pathname):
    (dir, file) = os.path.split(module_pathname)
    module_name = os.path.splitext(file)[0]
    if dir not in sys.path:
        sys.path.append(dir)
    return importlib.import_module(module_name)
