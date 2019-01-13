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
    
    driver = parse_specs.parse("./driver")
    generate_api.generate_all(configParser.get('PATH','driver'), configParser.get('API','namespace'), driver)
    
    #runtime = parse_specs.parse("./runtime")
    #generate_api.generate_all(configParser.get('PATH','runtime'), configParser.get('API','namespace'), runtime)

    print("\nDone")

if __name__ == '__main__':
    main()
# END OF FILE
