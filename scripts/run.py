import argparse
import util
import parse_specs
import generate_api
import compile_api
import generate_docs
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
    # define cmdline arguments
    parser = argparse.ArgumentParser()
    add_argument(parser, "core", "generation of C/C++ 'core' files.", True)
    add_argument(parser, "extended", "generation of C/C++ 'extended' files.", True)
    add_argument(parser, "md", "generation of MD files.", True)
    add_argument(parser, "html", "generation of HTML files.", True)
    add_argument(parser, "pdf", "generation of PDF file.")
    add_argument(parser, "cl", "compilation of generated C/C++ files.")
    add_argument(parser, "debug", "dump intermediate data to disk.")
    args = parser.parse_args()

    # parse cmdline arguments
    configParser = util.configRead("config.ini")

    start = time.time()
    # generate 'core' APIs
    if args.core and util.exists("./core"):
        specs, meta = parse_specs.parse("./core")
        if args.debug:
            util.jsonWrite("./core/specs.json", specs)
            util.jsonWrite("./core/meta.json", meta)
        generate_api.generate_cpp(
            configParser.get('PATH','core'),
            configParser.get('NAMESPACE','core'),
            specs, meta)
        if args.cl:
            compile_api.compile_cpp_source(
                configParser.get('PATH','core'),
                configParser.get('NAMESPACE','core'),
                specs)

    # generate 'extended' APIs
    if args.extended and util.exists("./extended"):
        specs, meta = parse_specs.parse("./extended")
        if args.debug:
            util.jsonWrite("./extended/specs.json", specs)
            util.jsonWrite("./extended/meta.json", meta)
        generate_api.generate_cpp(
            configParser.get('PATH','extended'),
            configParser.get('NAMESPACE','extended'),
            specs, meta)
        if args.cl:
            compile_api.compile_cpp_source(
                configParser.get('PATH','extended'),
                configParser.get('NAMESPACE','extended'),
                specs)

    # generate documentation
    if args.md:
        generate_docs.generate_md(
            "./core",
            configParser.get('PATH','core'),
            configParser.get('NAMESPACE','core'))
        generate_docs.generate_md(
            "./extended",
            configParser.get('PATH','extended'),
            configParser.get('NAMESPACE','extended'))

    if args.html:
        generate_docs.generate_html()

    if args.pdf:
        generate_docs.generate_pdf()


    print("\nCompleted in %.1f seconds!"%(time.time() - start))

if __name__ == '__main__':
    main()
# END OF FILE
