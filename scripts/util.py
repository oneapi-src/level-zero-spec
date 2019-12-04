"""
 Copyright (C) 2019 Intel Corporation

 SPDX-License-Identifier: MIT

"""
import os
import shutil
import re
import configparser
import glob
import json
import yaml
from mako.template import Template
from mako.exceptions import RichTraceback

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
    try:
        if not exists(path):
            os.makedirs(path)
    except:
        print("warning: failed to make %s"%path)

"""
    remove directory and all contents
"""
def removePath(path):
    try:
        shutil.rmtree(path)
    except:
        print("warning: failed to remove %s"%path)

"""
    removes all files in list
"""
def removeFile(lst):
    for f in lst:
        try:
            os.remove(f)
        except:
            print("warning: failed to remove %s"%f)

"""
    returns a list of files in path matching pattern
"""
def findFiles(path, pattern):
    try:
        return glob.glob(os.path.join(path, pattern))
    except:
        print("warning: unable to find %s"%path)
        return []

"""
    removes all files in path matching pattern
"""
def removeFiles(path, pattern):
    for f in findFiles(path, pattern):
        try:
            os.remove(f)
        except:
            print("warning: failed to remove %s"%f)

"""
    reads from text file, returns list of lines
"""
def textRead(path):
    try:
        with open(path, "r") as fin:
            return fin.readlines()
    except Exception as e:
        print(e)
        print("error: unable to read %s"%path)
        return None

"""
    read from ini file, returns config obj
"""
def configRead(path):
    try:
        parser = configparser.ConfigParser(interpolation=configparser.ExtendedInterpolation())
        parser.read(path)
        return parser
    except:
        print("error: unable to read %s"%path)
        return None

"""
    read from json file, returns list/dict
"""
def jsonRead(path):
    try:
        with open(path, 'r') as fin:
            return json.loads(fin.read())
    except:
        print("error: unable to read %s"%path)
        return None

"""
    writes list/dict to json file
"""
def jsonWrite(path, data):
    try:
        with open(path, 'w') as fout:
            fout.write(json.dumps(data, indent=4, sort_keys=True))
    except:
        print("error: unable to write %s"%path)

"""
    read from yml file, returns list/dict
"""
def yamlRead(path):
    try:
        with open(path, 'r') as fin:
            return yaml.load_all(fin.read(), Loader = yaml.CLoader)
    except:
        print("error: unable to read %s"%path)
        return None

"""
    write to yml file
"""
def yamlWrite(path, data):
    try:
        with open(path, 'w') as fout:
            yaml.dump(data, fout, default_flow_style=False)
    except:
        print("error: unable to write %s"%path)

"""
    generates file using template, args
"""
makoFileList = []
def makoWrite(inpath, outpath, **args):
    try:
        template = Template(filename=inpath)
        rendered = template.render(**args)
        rendered = re.sub(r"\r\n", r"\n", rendered)

        with open(outpath, 'w') as fout:
            fout.write(rendered)

        makoFileList.append(outpath)
        return len(rendered.splitlines())
    except:
        traceback = RichTraceback()
        for (filename, lineno, function, line) in traceback.traceback:
            print("%s(%s) : error in %s" % (filename, lineno, function))
            print(line, "\n")
        print("%s: %s" % (str(traceback.error.__class__.__name__), traceback.error))
        return 0

def makoFileListWrite(outpath):
    jsonWrite(outpath, makoFileList)

# END OF FILE
