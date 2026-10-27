#! /usr/bin/env python3
"""
 Copyright (C) 2026 Intel Corporation

 SPDX-License-Identifier: MIT

 Checks or updates the year in the Intel copyright header of changed files.

 A file that is changed should carry the current year in its copyright line.
 Only the last year is checked: 2026 alone is as good as 2019-2026.
 When updating, if the current year is 2026, a single year 2024 becomes 2024-2026 and a range
 2019-2025 becomes 2019-2026. Only the Intel line is touched. Third-party
 copyright lines, and files with no copyright line at all (most .rst pages),
 are left alone.

 Subcommands:
   check    report stale years; exit 1 if any are found (used by CI)
   update   rewrite stale years in place (run locally before committing)

 Which files are processed:
   * With no paths (the default), only files that git reports as changed are
     processed: everything changed since the merge base with --base (default
     origin/master, else innersource/master), including staged and unstaged
     edits. Untracked files and files you have not changed are NOT processed.
   * With paths, exactly those files are processed. git is not needed.
   * With --generated, the output of run.py is processed instead (include/,
     source/ and docs/source/; run run.py first). These files are generated
     from scripts/templates/*.mako, so their year comes from the template even
     when the template itself is not changed. A stale year here means the next
     regeneration ships an old year to the loader. 'update --generated' fixes
     the template and the generated file.
 Nothing is ever staged; review the result with 'git diff' and stage it yourself.

 Exit status: 0 nothing stale, 1 stale years found (check only), 2 error.
"""
import argparse
import datetime
import fnmatch
import glob
import os
import re
import shutil
import subprocess
import sys

SCRIPTS_DIR = os.path.dirname(os.path.realpath(__file__))
DEFAULT_REPO_ROOT = os.path.dirname(SCRIPTS_DIR)
DEFAULT_BASES = ["origin/master", "innersource/master"]

# A copyright header sits at the top of the file; there is no need to scan
# further, and stopping early avoids matching copyright text in code or docs.
HEADER_LINES = 30

# Matched on bytes so that encoding and line endings are preserved on rewrite.
# The second form is the Sphinx 'copyright' setting in conf.py.mako.
COPYRIGHT_RES = [
    re.compile(rb"(Copyright (?:\(C\) )?)(\d{4})(?:-(\d{4}))?( Intel Corporation)", re.IGNORECASE),
    re.compile(rb"(copyright = u?['\"])(\d{4})(?:-(\d{4}))?(, Intel)"),
]

# Generated output (glob, relative to the repo root) and the template it comes from.
GENERATED = [
    ("include/*_api.h", "scripts/templates/api.h.mako"),
    ("include/*_ddi.h", "scripts/templates/ddi.h.mako"),
    ("include/*_ddi_common.h", "scripts/templates/ddi_common.h.mako"),
    ("include/*.py", "scripts/templates/api.py.mako"),
    ("source/*_api.cpp", "scripts/templates/api.cpp.mako"),
    ("docs/source/index.rst", "scripts/templates/index.rst.mako"),
    ("docs/source/conf.py", "scripts/templates/conf.py.mako"),
]


def eprint(*args):
    print(*args, file=sys.stderr)


def git(repo_root, *args):
    result = subprocess.run(["git", "-C", repo_root] + list(args),
                            capture_output=True, text=True)
    if result.returncode != 0:
        raise RuntimeError("git %s failed: %s" % (" ".join(args), result.stderr.strip()))
    return result.stdout


def is_git_checkout(repo_root):
    """True if repo_root is the top of a git work tree and git is installed."""
    if shutil.which("git") is None:
        return False
    try:
        top = git(repo_root, "rev-parse", "--show-toplevel").strip()
    except RuntimeError:
        return False
    return os.path.realpath(top) == repo_root


def default_base(repo_root):
    for ref in DEFAULT_BASES:
        try:
            git(repo_root, "rev-parse", "--verify", "--quiet", ref)
            return ref
        except RuntimeError:
            pass
    raise RuntimeError("none of %s exist.\n       Fetch one, or pass --base <ref> for your "
                       "upstream branch." % ", ".join(DEFAULT_BASES))


def changed_files(repo_root, base):
    try:
        merge_base = git(repo_root, "merge-base", base, "HEAD").strip()
    except RuntimeError as e:
        raise RuntimeError("%s\n       Fetch %s, or pass --base <ref> for your upstream branch." % (e, base))
    # Diffing the merge base against the working tree covers committed, staged
    # and unstaged changes in one call. Deleted files are filtered out.
    out = git(repo_root, "diff", "--name-only", "--diff-filter=ACMR", "-z", merge_base)
    return [name for name in out.split("\0") if name]


def generated_files(repo_root):
    found = []
    for pattern, template in GENERATED:
        outputs = [os.path.relpath(p, repo_root) for p in glob.glob(os.path.join(repo_root, pattern))]
        # conf.py and index.rst are written only by an --html build; without the
        # output, check the template, which carries the same header.
        found += outputs or [template]
    return found


def template_for(rel):
    for pattern, template in GENERATED:
        if fnmatch.fnmatch(rel, pattern):
            return template
    return None


def is_binary(data):
    return b"\0" in data[:8192]


def fix_header(data, year):
    """Return (new_data, findings); findings is a list of (line, old, new)."""
    lines = data.splitlines(keepends=True)
    findings = []
    for index, line in enumerate(lines[:HEADER_LINES]):
        for regex in COPYRIGHT_RES:
            match = regex.search(line)
            if not match:
                continue
            first = int(match.group(2))
            last = int(match.group(3)) if match.group(3) else first
            if last >= year:
                continue
            replacement = match.group(1) + b"%d-%d" % (first, year) + match.group(4)
            lines[index] = line[:match.start()] + replacement + line[match.end():]
            findings.append((index + 1, match.group(0).decode(), replacement.decode()))
    return b"".join(lines), findings


def update_file(path, year):
    """Rewrite stale years in path; return the number of lines changed."""
    with open(path, "rb") as fin:
        data = fin.read()
    new_data, findings = fix_header(data, year)
    if findings:
        with open(path, "wb") as fout:
            fout.write(new_data)
    return len(findings)


def run(args):
    repo_root = os.path.realpath(args.repo_root)
    fix_cmd = "python3 scripts/copyright_year.py update%s" % (" --generated" if args.generated else "")
    if args.generated:
        paths = generated_files(repo_root)
        if not glob.glob(os.path.join(repo_root, "include", "*_api.h")):
            eprint("error: no generated files found under %s. Run scripts/run.py first." % repo_root)
            return 2
    elif args.paths:
        paths = [os.path.relpath(os.path.realpath(p), repo_root) for p in args.paths]
    elif not is_git_checkout(repo_root):
        print("%s is not a git checkout (or git is not installed), so there are no changed "
              "files to %s. Nothing to do. Pass file paths to process specific files."
              % (repo_root, args.command))
        return 0
    else:
        paths = changed_files(repo_root, args.base or default_base(repo_root))

    stale = 0
    templates = set()
    for rel in sorted(set(paths)):
        path = os.path.join(repo_root, rel)
        if not os.path.isfile(path):
            if args.paths:
                eprint("error: %s is not a file" % rel)
                return 2
            continue
        with open(path, "rb") as fin:
            data = fin.read()
        if is_binary(data):
            continue
        new_data, findings = fix_header(data, args.year)
        template = template_for(rel) if args.generated else None
        source = " (generated from %s)" % template if template else ""
        for line, old, new in findings:
            stale += 1
            if args.github:
                print("::error file=%s,line=%d::Stale copyright year%s: '%s' should be '%s'. "
                      "Run '%s'." % (rel, line, source, old, new, fix_cmd))
            else:
                print("%s:%d: %s -> %s%s" % (rel, line, old, new, source))
        if findings and args.command == "update":
            with open(path, "wb") as fout:
                fout.write(new_data)
            if template:
                templates.add(template)

    # The template is the real source; fixing only the output would be undone by
    # the next regeneration.
    for template in sorted(templates):
        if update_file(os.path.join(repo_root, template), args.year):
            print("%s: updated" % template)

    if args.command == "update":
        print("Updated %d copyright line(s)." % stale if stale else "All copyright years are current.")
        return 0
    if stale:
        sys.stdout.flush()
        eprint("%d stale copyright line(s). Run '%s' to fix." % (stale, fix_cmd))
        return 1
    print("All copyright years are current.")
    return 0


def main():
    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--repo-root", default=DEFAULT_REPO_ROOT,
                        help="root of the level-zero-spec checkout (default: %(default)s)")
    parser.add_argument("--base",
                        help="ref to diff against when no paths are given (default: the first "
                             "of %s that exists)" % ", ".join(DEFAULT_BASES))
    parser.add_argument("--year", type=int, default=datetime.date.today().year,
                        help="year to require (default: the current year)")
    subparsers = parser.add_subparsers(dest="command", required=True)

    check = subparsers.add_parser(
        "check", help="report stale years; exit 1 if any are found",
        description="Report stale copyright years without changing any file. With no paths, "
                    "only files git reports as changed since the merge base with --base are checked.")
    check.add_argument("--github", action="store_true",
                       help="emit GitHub Actions error annotations")
    update = subparsers.add_parser(
        "update", help="rewrite stale years in place",
        description="Rewrite stale copyright years in place. With no paths, only files git "
                    "reports as changed since the merge base with --base are updated.")
    for sub in (check, update):
        sub.add_argument("--generated", action="store_true",
                         help="process the output of run.py instead of changed files; "
                              "update also fixes the source templates")
        sub.add_argument("paths", nargs="*",
                         help="files to process; if omitted, only the files git reports as changed")
    update.set_defaults(github=False)

    args = parser.parse_args()
    if args.generated and args.paths:
        parser.error("--generated takes no paths")
    try:
        return run(args)
    except (OSError, RuntimeError) as e:
        eprint("error: %s" % e)
        return 2


if __name__ == "__main__":
    sys.exit(main())
