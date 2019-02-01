import argparse
import util
import parse_specs
import generate_api
import compile_api
import generate_docs

"""
    Do everything...
"""
def main():
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
    args = parser.parse_args()

    configParser = util.configRead("config.ini")

    if "all" == args.filter or "core" == args.filter:
        specs = parse_specs.parse("./core")
        generate_api.generate_cpp(
            configParser.get('PATH','core'),
            configParser.get('NAMESPACE','core'),
            specs)
        if args.compile:
            compile_api.compile_cpp_source(
                configParser.get('PATH','core'),
                configParser.get('NAMESPACE','core'),
                specs)

    if "all" == args.filter or "extended" == args.filter:
        specs = parse_specs.parse("./extended")
        generate_api.generate_cpp(
            configParser.get('PATH','extended'),
            configParser.get('NAMESPACE','extended'),
            specs)
        if args.compile:
            compile_api.compile_cpp_source(
                configParser.get('PATH','extended'),
                configParser.get('NAMESPACE','extended'),
                specs)

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

    print("\nDone")

if __name__ == '__main__':
    main()
# END OF FILE
