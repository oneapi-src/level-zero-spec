import argparse
import util
import parse_specs
import generate_api
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
    args = parser.parse_args()

    configParser = util.configRead("config.ini")

    if "all" == args.filter or "core" == args.filter:
        generate_api.generate_cpp_headers(
            configParser.get('PATH','core'),
            configParser.get('NAMESPACE','core'),
            parse_specs.parse("./core"))
    
    if "all" == args.filter or "extended" == args.filter:
        generate_api.generate_cpp_headers(
            configParser.get('PATH','extended'),
            configParser.get('NAMESPACE','extended'),
            parse_specs.parse("./extended"))

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
