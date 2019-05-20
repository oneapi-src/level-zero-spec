import argparse
import util
import parse_specs
import generate_code
import generate_docs
import os
import time

"""
    helper for adding mutually-exclusive boolean arguments "--name" and "--!name"
"""
def add_argument(parser, name, help, default=False):
    group = parser.add_mutually_exclusive_group(required=False)
    group.add_argument("--" + name, dest=name, help="Enable "+help, action="store_true")
    group.add_argument("--!" + name, dest=name, help="Disable "+help, action="store_false")
    parser.set_defaults(**{name:default})

"""
    
"""
def clean():
    util.removePath("../include")
    util.makePath("../include")
    util.removePath("../build")
    util.makePath("../build")

"""
    command lines for running cmake windows build
"""
def build():
    os.system('cmake -B ../build/ -S .. -G "Visual Studio 15 2017 Win64"')
    os.system('cmake --build ../build --clean-first')


"""
Main entry:
    Do everything...
"""
def main():
    # parse cmdline arguments
    configParser = util.configRead("config.ini")

    # define cmdline arguments
    parser = argparse.ArgumentParser()
    for section in configParser.sections():
        add_argument(parser, section, "generation of C/C++ '%s' files."%section, True)
    add_argument(parser, "clean", "cleaning previous generated files.")
    add_argument(parser, "lib", "generation of lib files.", True)
    add_argument(parser, "loader", "generation of loader files.", True)
    add_argument(parser, "layers", "generation of layer files.", True)
    add_argument(parser, "build", "running cmake to generate and build projects.")
    add_argument(parser, "debug", "dump intermediate data to disk.")
    add_argument(parser, "md", "generation of markdown files.", True)
    add_argument(parser, "html", "generation of HTML files.", True)
    add_argument(parser, "pdf", "generation of PDF file.")
    args = vars(parser.parse_args())

    start = time.time()

    if args['clean']:
        clean()

    meta = None

    # generate code
    for idx, section in enumerate(configParser.sections()):
        namespace = configParser.get(section,'namespace')
        tags={}
        for key in configParser.get(section,'tags').split(","):
            tags['$'+key] = configParser.get(section,key)

        srcpath = os.path.join("./", section)
        dstpath = os.path.join("../include/", section)
        libpath = os.path.join("../source/lib/", section)

        if args[section] and util.exists(srcpath):
            if meta:
                specs, meta = parse_specs.parse(srcpath, meta)
            else:
                specs, meta = parse_specs.parse(srcpath)

            if args['debug']:
                util.jsonWrite(os.path.join(srcpath, "specs.json"), specs)
                util.jsonWrite(os.path.join(srcpath, "meta.json"), meta)

            generate_code.generate_api(dstpath, namespace, tags, specs, meta)

            if args['lib']:
                generate_code.generate_lib(libpath, namespace, tags, specs, meta)

            if args['loader']:
                generate_code.generate_loader("../source/", section, namespace, tags, specs, meta)

            if args['layers']:
                generate_code.generate_layers("../source/", section, namespace, tags, specs, meta)

            if args['md']:
                generate_docs.generate_md(srcpath, dstpath, tags, meta)

    # build code
    if args['build']:
        build()

    # generate documentation
    if args['html']:
        generate_docs.generate_html()

    if args['pdf']:
        generate_docs.generate_pdf()

    print("\nCompleted in %.1f seconds!"%(time.time() - start))

if __name__ == '__main__':
    main()
# END OF FILE
