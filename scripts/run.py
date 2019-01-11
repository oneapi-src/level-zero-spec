#import argparse
import util
import parse_specs
import generate_api

"""
    Do everything...
"""
def main():
    #parser = argparse.ArgumentParser()
    #args = parser.parse_args()

    configParser = util.configRead("config.ini")

    options = {
        'namespace': configParser.get('API','namespace')
        }

    specs = parse_specs.parse()
    generate_api.generate_all(options,specs)

    print("\nDone")

if __name__ == '__main__':
    main()
# END OF FILE
