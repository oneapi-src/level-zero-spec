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
    #parser.add_argument("--clean", help="Clean output directories before generation.", action='store_true', default=False)
    parser.add_argument("--filter", help="Specify a single subroutine to execute.", default="all", choices=["all","driver","runtime","docs"])
    args = parser.parse_args()

    configParser = util.configRead("config.ini")

    if "all" == args.filter or "driver" == args.filter:
        driver = parse_specs.parse("./driver")
        generate_api.generate_all(configParser.get('PATH','driver'), configParser.get('NAMESPACE','driver'), driver)
    
    if "all" == args.filter or "runtime" == args.filter:
        runtime = parse_specs.parse("./runtime")
        generate_api.generate_all(configParser.get('PATH','runtime'), configParser.get('NAMESPACE','runtime'), runtime)

    if "all" == args.filter or "docs" == args.filter:
        generate_docs.generate_all()
    
    print("\nDone")

if __name__ == '__main__':
    main()
# END OF FILE
