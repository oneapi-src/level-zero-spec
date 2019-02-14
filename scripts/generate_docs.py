import os
import util

"""
Entry-point:
    generate markdown documents from templates
"""
def generate_md(srcpath, dstpath, namespace):
    loc = 0
    util.makePath(dstpath)
    util.removeFiles(dstpath, "*.md")
    for fin in util.findFiles(srcpath, "*.md"):
        fout = os.path.join(dstpath, os.path.basename(fin))
        print("Generating %s..."%fout)
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
