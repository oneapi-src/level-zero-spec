import argparse
import util
import parse_specs
import generate_api
import compile_api
import generate_docs
import time

"""
    Do everything...
"""
def main():
    # define cmdline arguments
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--filter",
        help="Specify a single subroutine to execute.",
        default="all",
        choices=["all","core","extended","docs"])
    parser.add_argument(
        "--compile",
        help="Enable compilation of cpp files.",
        action="store_true")
    parser.add_argument(
        "--pdf",
        help="Enable generation of pdf file.",
        action="store_true")
    args = parser.parse_args()

    # parse cmdline arguments
    configParser = util.configRead("config.ini")

    start = time.time()
    # generate 'core' APIs
    if "all" == args.filter or "core" == args.filter:
        specs, meta = parse_specs.parse("./core")
        generate_api.generate_cpp(
            configParser.get('PATH','core'),
            configParser.get('NAMESPACE','core'),
            specs, meta)
        if args.compile:
            compile_api.compile_cpp_source(
                configParser.get('PATH','core'),
                configParser.get('NAMESPACE','core'),
                specs)

    # generate 'extended' APIs
    if "all" == args.filter or "extended" == args.filter:
        specs, meta = parse_specs.parse("./extended")
        generate_api.generate_cpp(
            configParser.get('PATH','extended'),
            configParser.get('NAMESPACE','extended'),
            specs, meta)
        if args.compile:
            compile_api.compile_cpp_source(
                configParser.get('PATH','extended'),
                configParser.get('NAMESPACE','extended'),
                specs)

    # generate documentation
    if "all" == args.filter or "docs" == args.filter:
        generate_docs.generate_md(
            "./core",
            configParser.get('PATH','core'),
            configParser.get('NAMESPACE','core'))
        generate_docs.generate_md(
            "./extended",
            configParser.get('PATH','extended'),
            configParser.get('NAMESPACE','extended'))
        generate_docs.generate_html()
        if args.pdf:
            generate_docs.generate_pdf()

    print("\nCompleted in %.1f seconds!"%(time.time() - start))

if __name__ == '__main__':
    main()
# END OF FILE
