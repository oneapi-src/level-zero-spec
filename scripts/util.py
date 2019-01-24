import os
import shutil
import re
import configparser
import glob
import json
import yaml
from mako.template import Template

"""
    safely checks if path/file exists
"""
def exists(path):
    if path and os.path.exists(path):
        return True
    else:
        return False

"""
    create path if it doesn't exist
"""
def makePath(path):
    if not exists(path):
        os.makedirs(path)

"""
    remove directory and all contents
"""
def removePath(path):
    if exists(path):
        try:
            shutil.rmtree(path)
        except:
            print("Warning: failed to completely remove %s\n"%path)

"""
    returns a list of files in path matching pattern
"""
def findFiles(path, pattern):
    if exists(path):
        return glob.glob(os.path.join(path, pattern))
    else:
        return []

"""
    removes all files in path matching pattern
"""
def removeFiles(path, pattern):
    for f in findFiles(path, pattern):
        os.remove(f)

"""
    read from ini file, returns config obj
"""
def configRead(path):
    if exists(path):
        parser = configparser.ConfigParser()
        parser.read(path)
        return parser
    else:
        return None

"""
    read from json file, returns list/dict
"""
def jsonRead(path):
    if exists(path):
        with open(path, 'r') as fin:
            return json.loads(fin.read())
    else:
        return None

"""
    writes list/dict to json file
"""
def jsonWrite(path, data):
    if path and data:
        with open(path, 'w') as fout:
            fout.write(json.dumps(data, indent=4, sort_keys=True))

"""
    read from yml file, returns list/dict
"""
def yamlRead(path):
    if exists(path):
        with open(path, 'r') as fin:
            return yaml.load_all(fin.read())
    else:
        return None

"""
    generates file using template, args
"""
def makoWrite(inpath, outpath, **args):
    template = Template(filename=inpath)
    rendered = template.render(**args)
    rendered = re.sub(r"\r\n", r"\n", rendered)

    with open(outpath, 'w') as fout:
        fout.write(rendered)

    return len(rendered.splitlines())

# END OF FILE
