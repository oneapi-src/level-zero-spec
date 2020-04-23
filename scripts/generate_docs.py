"""
 Copyright (C) 2019 Intel Corporation

 SPDX-License-Identifier: MIT

"""
import os
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

RE_CODE_BLOCK_BEGIN = r"\s*..\sparsed-literal::"

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
    generate a valid reStructuredText file
"""
def _generate_valid_rst(fin, fout, tags, ver, rev, meta):
    enable = True
    code_block = False

    print("Generating %s..."%fout)

    outlines = []
    for iline, line in enumerate(util.textRead(fin)):
    
        if re.match(RE_ENABLE, line) or re.match(RE_PYCODE_BLOCK_END, line):
            enable = True
        elif re.match(RE_DISABLE, line) or re.match(RE_PYCODE_BLOCK_BEGIN, line):
            enable = False
        elif re.match(RE_CODE_BLOCK_BEGIN, line):
            code_block = True
        # code is always indented
        elif re.match(r'^\w', line) and code_block:
            code_block = False

        if not enable:
            outlines.append(line)
            continue

        if re.match(RE_INVALID_TAG_FORMAT, line):
            print("%s(%s) : error : invalid %s tag used"%(fin, iline+1, re.sub(RE_INVALID_TAG_FORMAT, r"\1", line)))

        if re.match(RE_PROPER_TAG_FORMAT, line):
            link_found = False
            words = re.findall(RE_EXTRACT_NAME, line)
            for word in words:
                symbol = re.sub(RE_EXTRACT_TAG_NAME, r"$\1", word)
                if symbol:
                    symbol_type = _find_symbol_type(symbol, meta)
                    if not symbol_type:
                        print("%s(%s) : error : symbol '%s' not found"%(fin, iline+1, symbol))

                    if re.match(r"struct|union|function", symbol_type):
                        refword = word
                        if re.match(r"struct|union", symbol_type):
                            refword = refword.replace("_", "-")
                        ref = ":ref:`" + refword + "`"
                        if not re.match(r'\s', line.partition("::" + word)[2]):
                            # need to add escape character after references that are not followed by whitespace in RST.
                            line = line.replace("::" + word, ref + "\\")
                        else:
                            line = line.replace("::" + word, ref)
                        link_found = True

                    if code_block and 'function' == symbol_type:
                        words = re.sub(RE_EXTRACT_PARAMS, r"\1", line).split(",")
                        if len(words) != len(meta['function'][symbol]['types']):
                            print("%s(%s) : error : %s parameter count mismatch - %s actual vs. %s expected"%(fin, iline+1, symbol, len(words), len(meta['function'][symbol]['types'])))

            if not code_block and not link_found:
                 if not re.match(RE_DOXY_LINK, line):
                    print("%s(%s) : warning : doxygen link not used"%(fin, iline+1, ))

        outlines.append(line)

    util.writelines(os.path.abspath(fout), outlines)

    return util.makoWrite(os.path.abspath(fout), fout,
                          tags=tags,
                          ver=float(ver))

"""
Entry-point:
    generate restructuredtext documents from templates
"""
def generate_rst(srcpath, dstpath, tags, ver, rev, meta, specs):
    loc = 0
    util.makePath(dstpath)
    util.removeFiles(dstpath, "*.rst")
    for fin in util.findFiles(srcpath, "*.rst"):
        fout = os.path.join(dstpath, os.path.basename(fin))
        loc += _generate_valid_rst(os.path.abspath(fin), fout, tags, ver, rev, meta)

    print("Generated %s lines of reStructuredText (rst).\n"%loc)

    if (loc > 0):
        fin = os.path.join("templates", "api_listing.mako")
        fout = os.path.join(dstpath, "api.rst")
        groupname = os.path.basename(dstpath).capitalize()
        util.makoWrite(fin, fout,
            groupname=groupname,
            ver=ver,
            rev=rev,
            tags=tags,
            meta=meta,
            specs=specs)
        

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
    generate HTML files using reStructuredText (rst) and Doxygen template
"""
def generate_html(dstpath, sections, ver, rev):
    htmlpath = os.path.join(dstpath, "html")
    latexpath = os.path.join(dstpath, "latex")
    xmlpath = os.path.join(dstpath, "xml")
    sourcepath = os.path.join(dstpath, "source")
    util.removePath(htmlpath)
    util.removePath(latexpath)
    util.removePath(xmlpath)
    util.makePath(xmlpath)

    # Generate sphinx configuration file with version.
    loc = 0
    for fn in ["conf.py", "index.rst", "api.rst"]:
        loc += util.makoWrite(
            "./templates/%s.mako" % fn,
            os.path.join(sourcepath, fn),
            ver=rev,
            sourcepath=sourcepath,
            sections=sections)

    # Doxygen generates XML files needed by sphinx breathe plugin for API documentation.
    print("Generating doxygen...")
    cmdline = "doxygen Doxyfile"
    os.system(cmdline)

    print("Generating HTML...")
    cmdline = "sphinx-build -M html %s ..\docs"%sourcepath
    print(cmdline)
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

"""
Entry-point:
    prepare doc folder for documentation.
"""
def prepare(docpath, gen_rst, gen_html, ver):
    if gen_html:
        htmlpath = os.path.join(docpath, "html")
        if util.exists(htmlpath):
            util.removePath(htmlpath)
    
    # if generating rst then assume everything in docs is invalid and clean it.
    if gen_rst:
        if util.exists(docpath):
            util.removePath(docpath)

    docsourcepath = os.path.join(docpath, "source")
    util.copyTree("./assets/html/_static",    os.path.join(docsourcepath, "_static"))
    util.copyTree("./assets/html/_templates", os.path.join(docsourcepath, "_templates"))
    util.copyTree("./assets/images",          os.path.join(docsourcepath, "images"))
    
