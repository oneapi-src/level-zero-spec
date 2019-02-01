import os
import util

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

def generate_html():
    util.removePath("../html")
    util.removePath("../latex")
    print("Generating HTML/LaTeX...")
    cmdline = "doxygen Doxyfile"
    os.system(cmdline)
