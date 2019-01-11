import os
import re
import configparser
import json
import yaml
from mako.template import Template
import time
import traceback

"""
    safely checks if path/file exists
"""
def exists(path):
    if path and os.path.exists(path):
        return True
    else:
        return False

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

"""
    global logfile object
"""
def log(msg, echo=False):
    timestamp = time.strftime("[%y-%m-%d.%H:%M:%S]", time.localtime())
    msg = "%s %s\n"%(timestamp,msg)
    with open("run.log", 'a') as fout:
        fout.write(msg)
    if echo:
        print(msg)

"""
    returns an exception message
"""
def msgException(msg=""):
    exc_info = sys.exc_info()
    return "Exception caught: %s\n%s\n%s"%(exc_info[1], traceback.extract_tb(exc_info[2]), msg)

# END OF FILE
