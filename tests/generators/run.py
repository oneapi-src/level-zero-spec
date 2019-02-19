#!/usr/bin/env python
import sys
sys.path.insert(0, "../../scripts")
sys.path.insert(0, ".")

import argparse
import util
import parse_specs
import generate_driver_exports
import generate_driver_frontend
import generate_icd_loader
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
        choices=["clean", "all","icd_loader","driver_exports","driver_frontend"])
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
    specs, meta = parse_specs.parse("../../scripts/core")
    
    if "all" == args.filter or "clean" == args.filter:
        util.removePath("../generated")
        
    
    if "all" == args.filter or "icd_loader" == args.filter:
        util.makePath(configParser.get('PATH','icd_loader'))
        generate_icd_loader.generate_icd_loader(
            configParser.get('PATH','icd_loader'),
            configParser.get('NAMESPACE','core'),
            specs)
            
    if "all" == args.filter or "driver_exports" == args.filter:
        util.makePath(configParser.get('PATH','driver_exports'))
        generate_driver_exports.generate_driver_exports(
            configParser.get('PATH','driver_exports'),
            configParser.get('NAMESPACE','core'),
            specs)
            
    if "all" == args.filter or "driver_frontend" == args.filter:
        util.makePath(configParser.get('PATH','driver_frontend'))
        generate_driver_frontend.generate_driver_frontend(
            configParser.get('PATH','driver_frontend'),
            configParser.get('NAMESPACE','core'),
            specs)

    print("\nCompleted in %.1f seconds!"%(time.time() - start))

if __name__ == '__main__':
    main()
# END OF FILE
