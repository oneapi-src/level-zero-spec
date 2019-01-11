import os
import util
import glob

"""
    Reads each YML file and extracts data
    Returns list of data per file
"""
def parse():
    specs = []
    files = glob.glob("./specs/*.yml")
    for f in files:
        specs.append({
            'name': os.path.splitext(os.path.basename(f))[0],
            'docs': util.yamlRead(f)
        })
    #util.jsonWrite("specs.json", specs);
    return specs

"""
    Parse and print contents (for debug purposes)
"""
def main():
    specs = parse()
    for s in specs:
        print("\nFile: %s"%s['name'])
        for doc in s['docs']:
            print("    %s"%doc['type'])
            print("    %s"%doc['name'])
            print("    %s\n"%doc['desc'])

    print("\nDone")

if __name__ == '__main__':
    main()
# END OF FILE    
