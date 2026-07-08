#!/usr/bin/env python3
"""
 Copyright (C) 2019-2022 Intel Corporation

 SPDX-License-Identifier: MIT

"""
import argparse
import util
import parse_specs
import generate_code
import generate_docs
import os, sys, platform
import time
import subprocess
import warnings

# Default target for the sidebar "Versions" nav link. Points at the canonical,
# always-current version index (the clone of the newest release). Override per
# environment (e.g. PR previews) with --versions_url_override.
DEFAULT_VERSIONS_URL = "https://oneapi-src.github.io/level-zero-spec/level-zero/latest/versions.html"

"""
    helper for adding mutually-exclusive boolean arguments "--name" and "--!name"
"""
def add_argument(parser, name, help, default=False):
    group = parser.add_mutually_exclusive_group(required=False)
    group.add_argument("--" + name, dest=name, help="Enable "+help, action="store_true")
    group.add_argument("--!" + name, dest=name, help="Disable "+help, action="store_false")
    parser.set_defaults(**{name:default})

"""
    helper for cleaning previously generated files
"""
def clean():
    util.removePath("../include")
    util.makePath("../include")
    util.removePath("../build")
    util.makePath("../build")

"""
    helper for running cmake windows build
"""
def build():
    if "Windows" == platform.system():
        result = os.system('cmake -B ../build/ -S .. -G "Visual Studio 17 2022" -A x64')
    else:
        result = os.system('cmake -B ../build/ -S ..')
    if result == 0:
        result = os.system('cmake --build ../build --clean-first')
    return result == 0

"""
    Auto-detect the MAJOR.MINOR spec version from the most recent git tag
    reachable from the current branch. The result is branch-specific: checking
    out a different branch may yield a different version if that branch has a
    different most-recent tag in its history.
    Returns a string like '1.17', or None if detection fails.
"""
def detect_version_git_major_minor():
    result = subprocess.run(
        ['git', 'describe', '--tags', '--abbrev=0'],
        cwd=os.path.dirname(os.path.abspath(__file__)),
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE
    )
    if result.returncode != 0:
        return None
    tag = result.stdout.decode().strip().lstrip('v')
    parts = tag.split('.')
    if len(parts) >= 2:
        return '%s.%s' % (parts[0], parts[1])
    return None

"""
    helper for getting revision number from git repository
    revision is number of commits since tag 'v0'
"""
def revision():
    result = subprocess.run(['git', 'describe', '--tags', '--dirty'], cwd=os.path.dirname(os.path.abspath(__file__)), stdout=subprocess.PIPE)
    if result.returncode:
        print('ERROR: Could not get revision number from git', file=sys.stderr)
        return '0'

    items = result.stdout.decode().strip().split('-')
    tag = items[0][1:] # remove 'v'
    ver = [int(n) for n in tag.split('.')]
    count = ver[2] if len(ver) == 3 else 0
    if len(items) > 1 and items[1].isdigit():
        count += int(items[1])

    # Bump count if any local files are dirty.
    # Keeps the count the same after doing a commit (assuming all dirty files are committed)
    if 'dirty' in items[-1]:
        count += 1
    return '%s.%s.%s'%(ver[0], ver[1], count)


"""
    Validate installed package versions against third_party/requirements.txt.
    Exits with an error if any installed package does not satisfy its minimum
    version requirement, preventing silent build degradation (e.g., an outdated
    sphinx-book-theme installed via apt suppressing the light/dark theme switch).
"""
def check_requirements():
    import importlib.metadata
    try:
        from packaging.requirements import Requirement
        from packaging.version import Version
    except ImportError:
        print("WARNING: 'packaging' module not available; skipping dependency version check.")
        return

    req_file = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "third_party", "requirements.txt"))
    if not os.path.isfile(req_file):
        print("WARNING: requirements.txt not found at %s; skipping dependency version check." % req_file)
        return

    failures = []
    with open(req_file) as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith('#'):
                continue
            try:
                req = Requirement(line)
            except Exception:
                continue
            try:
                installed = Version(importlib.metadata.version(req.name))
            except importlib.metadata.PackageNotFoundError:
                failures.append("  %-40s NOT INSTALLED" % (req.name + ":"))
                continue
            if not req.specifier.contains(installed, prereleases=True):
                failures.append("  %-40s installed %s does not satisfy %s" % (req.name + ":", installed, req.specifier))

    if failures:
        print("\nERROR: The following dependencies do not meet the minimum version requirements")
        print("       specified in third_party/requirements.txt.")
        print("       This can cause missing build features (e.g., the light/dark theme switch")
        print("       requires sphinx-book-theme >= 1.1.2).")
        print()
        print("       System packages installed via apt may shadow the required pip versions.")
        print()
        print("       If you have a Python virtual environment with these packages installed,")
        print("       make sure it is activated before running this script, e.g.:")
        print()
        print("         source ~/.venv/bin/activate")
        print()
        print("       Otherwise, install the required versions with:")
        print()
        print("         pip install -r third_party/requirements.txt")
        print()
        for msg in failures:
            print(msg)
        print()
        sys.exit(1)


"""
Main entry:
    Do everything...
"""
def main():
    # Validate dependency versions before doing any work.
    check_requirements()

    # Configure Python to treat warnings as errors
    warnings.filterwarnings('error')

    # phase 0: parse cmdline arguments
    configParser = util.configRead("config.ini")

    parser = argparse.ArgumentParser()
    for section in configParser.sections():
        add_argument(parser, section, "generation of C/C++ '%s' files."%section, True)
    add_argument(parser, "clean", "cleaning previous generated files.")
    add_argument(parser, "build", "running cmake to generate and build projects.", True)
    add_argument(parser, "debug", "dump intermediate data to disk.")
    add_argument(parser, "html", "generation of HTML files.", True)
    add_argument(parser, "rst", "generation of reStructuredText files.", True)
    add_argument(parser, "ignore_git_revision", "use command-line verison (ver) as revision instead of git tag.", False)
    parser.add_argument("--ver", type=str, default=None, required=False, help="specification version to generate (e.g. 1.17). If omitted, detected from the most recent git tag.")
    parser.add_argument("--versions_url_override", type=str, default=None, required=False, help="override the sidebar 'Versions' link target. Accepts a full URL (rendered as an external link) or an internal doc name like 'versions' (links to this build's own versions.html). If unset, uses the canonical latest versions page.")

    args = vars(parser.parse_args())

    if args['ver'] is None:
        args['ver'] = detect_version_git_major_minor()
        if args['ver'] is None:
            print("\nERROR: Could not detect specification version from git tags.")
            print("       Please specify the version explicitly with --ver <MAJOR.MINOR>")
            print()
            parser.print_help()
            sys.exit(1)
        print("Detected version from git tags: %s" % args['ver'])

    if (args['ignore_git_revision']):
        args['rev'] = args['ver']
    else:
        args['rev'] = revision()

    sep = "--------------------------------------------"
    sections_on = [s for s in configParser.sections() if args.get(s, False)]
    outputs_on  = [o for o in ["rst", "html", "build", "clean", "debug"] if args.get(o, False)]

    print(sep)
    print("Building Level Zero Spec Version: %s" % args['rev'])
    print(sep)
    print("  Sections : %s" % (", ".join(sections_on) if sections_on else "(none)"))
    print("  Outputs  : %s" % (", ".join(outputs_on)  if outputs_on  else "(none)"))
    print(sep)

    start = time.time()

    # phase 1: extract configuration info from ini file
    input = {
        'configs': [],
        'specs'  : [],
        'meta'   : {},
        'ref'    : {}
        }

    for section in configParser.sections():
        input['configs'].append({
            'name'     : section,
            'namespace': configParser.get(section,'namespace'),
            'tags'     : {'$'+key : configParser.get(section,key) for key in configParser.get(section,'tags').split(",")},
            })

    # phase 2: parse specs
    for config in input['configs']:
        specs, input['meta'], input['ref'] = parse_specs.parse(config['name'], args['ver'], config['tags'], input['meta'], input['ref'])
        input['specs'].append(specs)

    if args['debug']:
        util.jsonWrite("input.json", input)

    util.jsonWrite("level_zero.json", input['ref'])

    # phase 3: generate files
    if args['clean']:
        clean()

    incpath = os.path.join("../include/")
    srcpath = os.path.join("../source/")
    docpath = os.path.join("../docs/")

    generate_docs.prepare(docpath, args['rst'], args['html'], args['ver'])
    generate_docs.generate_ref(docpath, input['ref'])

    for idx, specs in enumerate(input['specs']):
        config = input['configs'][idx]
        if args[config['name']]:

            generate_code.generate_api(incpath, srcpath, config['namespace'], config['tags'], args['ver'], args['rev'], specs, input['meta'])

            if args['rst']:
                generate_docs.generate_rst(docpath, config['name'], config['namespace'], config['tags'], args['ver'], args['rev'], specs, input['meta'])

        if util.makeErrorCount():
            util.printAllErrors()
            print("\n%s Errors found during generation, stopping execution!"%util.makeErrorCount())
            sys.exit(1)

    if args['debug']:
        util.makoFileListWrite("generated.json")

    # phase 4: build code
    if args['build']:
        if not build():
            print("\nBuild failed, stopping execution!")
            return

    # phase 5: prep for publication of html
    if args['html']:
        versions_url = args['versions_url_override'] or DEFAULT_VERSIONS_URL
        generate_docs.generate_common(docpath, configParser.sections(), args['ver'], args['rev'], versions_url)

    # phase 6: publish documentation
    if args['html']:
        generate_docs.generate_html(docpath)

    produced = (
        (["rst"]            if args["rst"]           else []) +
        (["html"]           if args["html"]          else []) +
        (["headers/source"] if any(args.get(s) for s in configParser.sections()) else []) +
        (["cmake build"]    if args["build"]                        else [])
    )
    print("\n" + sep)
    print("Completed in %.1f seconds!" % (time.time() - start))
    print("  Version  : %s" % args["rev"])
    print("  Produced : %s" % (", ".join(produced) if produced else "(none)"))
    print(sep)

if __name__ == '__main__':
    main()
# END OF FILE
