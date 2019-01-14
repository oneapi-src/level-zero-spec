#import argparse
import util
import parse_specs
import generate_api
import generate_docs

"""
    Do everything...
"""
def main():
    #parser = argparse.ArgumentParser()
    #args = parser.parse_args()

    configParser = util.configRead("config.ini")
    
    driver = parse_specs.parse("./driver")
    generate_api.generate_all(configParser.get('PATH','driver'), configParser.get('NAMESPACE','driver'), driver)
    
    runtime = parse_specs.parse("./runtime")
    generate_api.generate_all(configParser.get('PATH','runtime'), configParser.get('NAMESPACE','runtime'), runtime)

    generate_docs.generate_all()
    
    print("\nDone")

if __name__ == '__main__':
    main()
# END OF FILE
