import os
import shutil
import re
import fileinput
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
    fixes markdown files by converting paths relative to repo instead of html tree  
"""
def fix_md_paths(dirs):
    print("Fixing paths in markdown files...")
    regex_pattern = re.compile(r'\.[\/|\\]images')
    for dir in dirs:
        print("Looking for markdown files in %s" % dir)
        with fileinput.FileInput(files=(util.findFiles(dir, "*.md")), inplace=True) as f:
            for line in f:
                print(re.sub(regex_pattern, '../images', line), end='')

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

    # Copy over images
    print("Copying images to html dir...")
    src_dir = "../images"
    dst_dir = "../html/images"
    util.makePath(dst_dir)
    for f in os.listdir(src_dir):
        src = os.path.join(src_dir, f)
        dst = os.path.join(dst_dir, f)
        shutil.copyfile(src, dst)

"""
Entry-point:
    generate PDF file using generated LaTeX files
"""
def generate_pdf():
    print("Generating PDF..")
    cmdline = "..\latex\make.bat"
    os.system(cmdline)
