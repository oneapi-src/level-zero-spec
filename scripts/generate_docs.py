"""
 Copyright (C) 2019 Intel Corporation

 SPDX-License-Identifier: MIT

"""
import os
import shutil
import util
import re

RE_ENABLE   = r"^\#\#\s*\-\-validate\s*\=\s*on$"
RE_DISABLE  = r"^\#\#\s*\-\-validate\s*\=\s*off$"

RE_PYCODE_BLOCK_BEGIN = r"^\<\%$"
RE_PYCODE_BLOCK_END   = r"^\%\>$"

RE_INVALID_TAG_FORMAT  = r".*(\$\w).*"
RE_EXTRACT_TAG_NAME    = r"\$\{(\w)\}"
RE_PROPER_TAG_FORMAT   = r".*"+RE_EXTRACT_TAG_NAME+r".*"

RE_DOXY_LINK    = r".*\:\:\$\{\w\}.*"

RE_CODE_BLOCK_BEGIN = r"^\`\`\`c$"
RE_CODE_BLOCK_END   = r"^\`\`\`$"

RE_CODE_BLOCK_BEGIN_RST = r"..\scode::"

RE_EXTRACT_NAME     = r"\$\{\w\}\w+"
RE_EXTRACT_PARAMS   = r"\w+\((.*)\)\;"


"""
    determines if the symbol is known
"""
def _find_symbol_type(name, meta):
    for group in meta:
        if name in meta[group]:
            return group

    if name.isupper():
        for enum in meta['enum']:
            if name in meta['enum'][enum]['types']:
                return 'etor'

    return None

"""
    validate the markdown file
"""
def _validate_md(fpath, meta):
    enable = True
    code_block = False

    for iline, line in enumerate(util.textRead(fpath)):
        if re.match(RE_ENABLE, line) or re.match(RE_PYCODE_BLOCK_END, line):
            enable = True
            continue
        elif re.match(RE_DISABLE, line) or re.match(RE_PYCODE_BLOCK_BEGIN, line):
            enable = False
            continue

        if re.match(RE_CODE_BLOCK_BEGIN, line) or re.match(RE_CODE_BLOCK_BEGIN_RST, line):
            code_block = True
            continue
        elif re.match(RE_CODE_BLOCK_END, line):
            code_block = False
            continue
        # code is always indented
        elif re.match(r'\w', line) and code_block:
            code_block = False
            continue

        if not enable:
            continue

        if re.match(RE_INVALID_TAG_FORMAT, line):
            print("%s(%s) : error : invalid %s tag used"%(fpath, iline+1, re.sub(RE_INVALID_TAG_FORMAT, r"\1", line)))

        if re.match(RE_PROPER_TAG_FORMAT, line):
            words = re.findall(RE_EXTRACT_NAME, line)
            for word in words:
                symbol = re.sub(RE_EXTRACT_TAG_NAME, r"$\1", word)
                if symbol:
                    symbol_type = _find_symbol_type(symbol, meta)
                    if not symbol_type:
                        print("%s(%s) : error : symbol '%s' not found"%(fpath, iline+1, symbol))

                    if code_block and 'function' == symbol_type:
                        words = re.sub(RE_EXTRACT_PARAMS, r"\1", line).split(",")
                        if len(words) != len(meta['function'][symbol]['types']):
                            print("%s(%s) : error : %s parameter count mismatch - %s actual vs. %s expected"%(fpath, iline+1, symbol, len(words), len(meta['function'][symbol]['types'])))

            if not code_block:
                 if not re.match(RE_DOXY_LINK, line):
                    print("%s(%s) : warning : doxygen link not used"%(fpath, iline+1, ))

"""
Entry-point:
    generate markdown documents from templates
"""
def generate_md(srcpath, dstpath, tags, ver, meta):
    loc = 0
    util.makePath(dstpath)
    util.removeFiles(dstpath, "*.md")
    for fin in util.findFiles(srcpath, "*.md"):
        fout = os.path.join(dstpath, os.path.basename(fin))
        print("Generating %s..."%fout)
        _validate_md(os.path.abspath(fin), meta)
        loc += util.makoWrite(fin, fout,
            tags=tags,
            ver=float(ver))
    print("Generated %s lines of markdown.\n"%loc)

"""
Entry-point:
    generate restructedtext documents from templates
"""
def generate_rst(srcpath, dstpath, tags, ver, meta):
    loc = 0
    util.makePath(dstpath)
    util.removeFiles(dstpath, "*.rst")
    for fin in util.findFiles(srcpath, "*.rst"):
        fout = os.path.join(dstpath, os.path.basename(fin))
        print("Generating %s..."%fout)
        _validate_md(os.path.abspath(fin), meta)
        loc += util.makoWrite(fin, fout,
            tags=tags,
            ver=float(ver))

    if (loc > 0):
        print("Generated %s lines of reStructuredText (rst).\n"%loc)
        
        fin = os.path.join("templates", "api_listing.mako")
        fout = os.path.join(dstpath, "api.rst")
        groupname = os.path.basename(dstpath).capitalize()
        util.makoWrite(fin, fout, groupname = groupname)
        

"""
Entry-point:
    generate reference JSON file
"""
def generate_ref(dstpath, ref):
    refpath = os.path.join(dstpath, "ref")
    util.removePath(refpath)
    util.makePath(refpath)

    util.jsonWrite(os.path.join(refpath, "level_zero.json"), ref)

"""
Entry-point:
    generate HTML files using Rst and Doxygen template
"""
def generate_html_from_rst(dstpath):  # This will become generate_html() once MD path is removed.
    htmlpath = os.path.join(dstpath, "html")
    latexpath = os.path.join(dstpath, "latex")
    xmlpath = os.path.join(dstpath, "xml")
    util.removePath(htmlpath)
    util.removePath(latexpath)
    util.removePath(xmlpath)
    util.makePath(xmlpath)

    print("Generating doxygen...")
    cmdline = "doxygen DoxyfileRST"
    os.system(cmdline)

    print("Generating HTML for RST...")
    cmdline = "sphinx-build -M html %s ..\docs"%os.path.join(dstpath, "source")
    print(cmdline)
    os.system(cmdline)

"""
Entry-point:
    generate HTML files using Doxygen template
"""
def generate_html(dstpath):
    htmlpath = os.path.join(dstpath, "html")
    latexpath = os.path.join(dstpath, "latex")
    util.removePath(htmlpath)
    util.removePath(latexpath)

    print("Generating HTML/LaTeX...")
    cmdline = "doxygen Doxyfile"
    os.system(cmdline)

"""
Entry-point:
    generate PDF file using generated LaTeX files
"""
def generate_pdf(dstpath):
    latexpath = os.path.join(dstpath, "latex")

    print("Generating PDF..")
    cmdline = "%s"%os.path.join(latexpath, "make.bat")
    os.system(cmdline)
