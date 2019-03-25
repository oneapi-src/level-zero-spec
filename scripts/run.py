import argparse
import util
import parse_specs
import generate_api
import compile_api
import generate_docs
import generate_icd
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
    add_argument(parser, "debug", "dump intermediate data to disk.")
    add_argument(parser, "md", "generation of markdown files.", True)
    add_argument(parser, "html", "generation of HTML files.", True)
    add_argument(parser, "pdf", "generation of PDF file.")
    add_argument(parser, "cl", "compilation of generated C/C++ files.")
    add_argument(parser, "icd", "generation of C++ icd_loader files.", True)
    args = vars(parser.parse_args())

    start = time.time()

    for idx, section in enumerate(configParser.sections()):
        dstpath = configParser.get(section,'dstpath')
        namespace = configParser.get(section,'namespace')
        tags={}
        for key in configParser.get(section,'tags').split(","):
            tags['$'+key] = configParser.get(section,key)

        srcpath = os.path.join("./", section)

        if args[section] and util.exists(srcpath):
            if idx > 0:
                specs, meta = parse_specs.parse(srcpath, meta)
            else:
                specs, meta = parse_specs.parse(srcpath)

            if args['debug']:
                util.jsonWrite(os.path.join(srcpath, "specs.json"), specs)
                util.jsonWrite(os.path.join(srcpath, "meta.json"), meta)

            generate_api.generate_cpp(dstpath, namespace, tags, specs, meta)

            if args['icd'] and idx < 1: #todo: generate per-section icd loaders
                generate_icd.generate(namespace, tags, specs, meta)

            if args['cl']:
                compile_api.compile_cpp_source(dstpath, namespace, specs)

            if args['md']:
                generate_docs.generate_md(srcpath, dstpath, tags, meta)

    # generate documentation
    if args['html']:
        generate_docs.generate_html()

    if args['pdf']:
        generate_docs.generate_pdf()

    print("\nCompleted in %.1f seconds!"%(time.time() - start))

if __name__ == '__main__':
    main()
# END OF FILE
