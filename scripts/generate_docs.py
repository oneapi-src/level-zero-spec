import os
import shutil
import util
import re

"""
    convert from tag'd item to symbol name
"""
def convert_to_symbol(str):
    str = re.sub(r"\$\{x\}(.*)", r"$x\1", str)
    str = re.sub(r"\$\{X\}(.*)", r"$X\1", str)
    if re.match(r"\$[x|X]_$", str):
        str = ""
    return str

"""
    determines if the symbol is known
"""
def find_symbol_type(name, meta):
    for group in meta:
        if name in meta[group]:
            return group

    if name.isupper():
        for enum in meta['enum']:
            if name in meta['enum'][enum]:
                return 'etor'

    return None

"""
    validate the markdown file
"""
def validate_md(fpath, meta):
    RE_ENABLE   = r"^\#\#\s*\-\-validate\s*\=\s*on$"
    RE_DISABLE  = r"^\#\#\s*\-\-validate\s*\=\s*off$"
    enable = True

    RE_INVALID_TAG  = r".*\$x.*"
    RE_ANY_TAG      = r".*\$\{x\}.*"
    RE_DOXY_LINK    = r".*\:\:\$\{x\}.*"

    RE_CODE_BLOCK_BEGIN = r"^\`\`\`c$"
    RE_CODE_BLOCK_END   = r"^\`\`\`$"
    code_block = False

    RE_EXTRACT_NAME     = r"\$\{[x|X]\}\w+"
    RE_EXTRACT_PARAMS   = r"\w+\((.*)\)\;"

    for iline, line in enumerate(util.textRead(fpath)):
        if re.match(RE_ENABLE, line):
            enable = True
            continue
        elif re.match(RE_DISABLE, line):
            enable = False
            continue

        if re.match(RE_CODE_BLOCK_BEGIN, line):
            code_block = True
            continue
        elif re.match(RE_CODE_BLOCK_END, line):
            code_block = False
            continue

        if not enable:
            continue

        if re.match(RE_INVALID_TAG, line.lower()):
            print("%s(%s) : error : invalid $x tag used"%(fpath, iline+1))

        if re.match(RE_ANY_TAG, line.lower()):
            words = re.findall(RE_EXTRACT_NAME, line)
            for word in words:
                symbol = convert_to_symbol(word)
                symbol_type = find_symbol_type(symbol, meta)
                if symbol:
                    if not symbol_type:
                        print("%s(%s) : error : symbol '%s' not found"%(fpath, iline+1, symbol))

                    if code_block and 'function' == symbol_type:
                        words = re.sub(RE_EXTRACT_PARAMS, r"\1", line).split(",")
                        if len(words) != len(meta['function'][symbol]):
                            print("%s(%s) : error : %s parameter count mismatch - %s actual vs. %s expected"%(fpath, iline+1, symbol, len(words), len(meta['function'][symbol])))

            if not code_block:
                 if not re.match(RE_DOXY_LINK, line.lower()):
                    print("%s(%s) : warning : doxygen link not used"%(fpath, iline+1))

"""
Entry-point:
    generate markdown documents from templates
"""
def generate_md(srcpath, dstpath, namespace, meta):
    loc = 0
    util.makePath(dstpath)
    util.removeFiles(dstpath, "*.md")
    for fin in util.findFiles(srcpath, "*.md"):
        fout = os.path.join(dstpath, os.path.basename(fin))
        print("Generating %s..."%fout)
        validate_md(fin, meta)
        loc += util.makoWrite(fin, fout,
            x=namespace,
            X=namespace.upper(),
            Xx=namespace.title())
    print("Generated %s lines of markdown.\n"%loc)

"""
Entry-point:
    generate HTML files using Doxygen template
"""
def generate_html():
    util.removePath("../html")
    util.removePath("../latex")
    print("Generating HTML/LaTeX...")
    cmdline = "doxygen Doxyfile"
    os.system(cmdline)

"""
Entry-point:
    generate PDF file using generated LaTeX files
"""
def generate_pdf():
    print("Generating PDF..")
    cmdline = "..\latex\make.bat"
    os.system(cmdline)
