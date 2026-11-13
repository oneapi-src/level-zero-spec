"""
 Copyright (C) 2019-2026 Intel Corporation

 SPDX-License-Identifier: MIT

"""
import os
import sys
import util
import re
import glob
import json
import fnmatch
import subprocess
from parse_specs import RE_DEPRECATION_MARKER, _version_compare_less, _version_compare_equal, _version_compare_greater, _version_compare_lequal, _version_compare_gequal
from templates import helper as th

RE_ENABLE   = r"^\#\#\s*\-\-validate\s*\=\s*on$"
RE_DISABLE  = r"^\#\#\s*\-\-validate\s*\=\s*off$"

RE_PYCODE_BLOCK_BEGIN = r"^[\ufeff]?\<\%\!?\s*$"
RE_PYCODE_BLOCK_END   = r"^\%\>\s*$"

RE_INVALID_TAG_FORMAT  = r".*(\$\w).*"
RE_EXTRACT_TAG_NAME    = r"\$\{(\w)\}"
RE_PROPER_TAG_FORMAT   = r".*"+RE_EXTRACT_TAG_NAME+r".*"

RE_CODE_BLOCK_BEGIN = r"\s*..\sparsed-literal::"

RE_EXTRACT_NAME     = r"\$\{\w\}\w+"
RE_EXTRACT_PARAMS   = r"\w+\((.*)\)\;"

RE_VERSION_BEGIN    = r"\%if\s+(_version_compare_\w+\(.*\)).*"
RE_VERSION_END      = r"\%endif.*"


"""
    determines if the symbol is known
"""
def _find_symbol_type(name, meta):
    for group in meta:
        if name in meta[group]:
            return group

    if name.isupper():
        for enum in meta['enum']:
            if name in meta['enum'][enum]['etors']:
                return 'etor'

    return None

"""
    fix up tag for template (e.g. $x to ${x})
"""
def _fixup_tag(name):
    return re.sub(r"\$(?P<tag>\w)", r"${\g<tag>}", name)

"""
    find the enum type name for a given enumerator
"""
def _find_enum_from_etor(etor, meta):
    for name in meta['enum']:
        if etor in meta['enum'][name]['etors']:
            return _fixup_tag(name)

    return None

"""
    make restructuredtext reference from symbol
"""
def _make_ref(fin, iline, symbol, symbol_type, meta):
    if not re.match(r"function|struct|union|enum|etor|handle|typedef", symbol_type):
        return ""

    ref = _fixup_tag(symbol)
    if re.match("etor", symbol_type):
        target = _find_enum_from_etor(symbol, meta)
        if target:
            ref = ":ref:`" + ref + " <" + target.replace("_", "-") + ">`"
        else:
            error_msg = "%s(%s) : error : enum symbol not found for etor %s"%(fin, iline+1, symbol)
            print(error_msg)
            util.makeError(error_msg)
    elif not re.match("function", symbol_type):
        ref = ":ref:`" + ref.replace("_", "-") + "`"
    else:
        ref = ":ref:`" + ref + "`"

    return ref

"""
    generate a valid reStructuredText file
"""
def _generate_valid_rst(fin, fout, namespace, tags, ver, rev, meta):
    enable = True
    code_block = False

    print("Generating %s..."%fout)

    outlines = []
    lines = util.textRead(fin)
    for iline, line in enumerate(lines):

        if re.match(RE_ENABLE, line) or re.match(RE_PYCODE_BLOCK_END, line):
            enable = True
        elif re.match(RE_DISABLE, line) or re.match(RE_PYCODE_BLOCK_BEGIN, line):
            enable = False
        elif re.match(RE_CODE_BLOCK_BEGIN, line):
            code_block = True
        elif re.match(r'^\w', line) and code_block: # code is always indented
            code_block = False
        elif re.match(RE_VERSION_BEGIN, line):
            test = re.sub(RE_VERSION_BEGIN, r"\1", line.strip())
            enable = eval(test)
            # print("DEBUG %s: enable = %s (ver = %s)" % (test, enable, ver))
        elif re.match(RE_VERSION_END, line):
            enable = True

        if not enable:
            outlines.append(line)
            continue

        # deprecation is shown from the YAML 'deprecated' field, never free text
        m = RE_DEPRECATION_MARKER.search(line)
        if m:
            error_msg = "%s(%s) : error : free-text deprecation marker '%s'; put a 'deprecated' field on the YAML object instead (see YaML.md)"%(fin, iline+1, m.group(0))
            print(error_msg)
            util.makeError(error_msg)

        # new line will contain proper tags for reStructuredText if needed
        newline = line

        # Only validate tags when not in code blocks
        if not code_block and re.match(RE_INVALID_TAG_FORMAT, line):
            error_msg = "%s(%s) : error : invalid %s tag used"%(fin, iline+1, re.sub(RE_INVALID_TAG_FORMAT, r"\1", line))
            print(error_msg)
            util.makeError(error_msg)
        if re.match(RE_PROPER_TAG_FORMAT, line):
            words = re.findall(RE_EXTRACT_NAME, line)

            newline = ""
            for word in words:
                symbol = re.sub(RE_EXTRACT_TAG_NAME, r"$\1", word)
                if symbol:
                    symbol_type = _find_symbol_type(symbol, meta)
                    if not symbol_type:
                        error_msg = "%s(%s) : error : symbol '%s' not found"%(fin, iline+1, symbol)
                        print(error_msg)
                        util.makeError(error_msg)
                        continue

                    if code_block and 'function' == symbol_type:
                        # A function call in sample code may be formatted across multiple
                        # lines for readability. Start with the current line and accumulate
                        # subsequent lines until parentheses are balanced (i.e. the call is
                        # complete), so that all parameters are visible for counting.
                        full_call = line.rstrip('\n')
                        lookahead = iline + 1
                        while full_call.count('(') != full_call.count(')') and lookahead < len(lines):
                            # Strip leading whitespace from continuation lines so they join
                            # cleanly without affecting the comma-split count below.
                            full_call += ' ' + lines[lookahead].strip()
                            lookahead += 1
                        # Extract only the argument list between the outermost parentheses
                        # using RE_EXTRACT_PARAMS, then count arguments by splitting on ','.
                        # Without this extraction step, splitting the raw line would also
                        # count commas inside nested calls or template arguments incorrectly.
                        param_str = re.sub(RE_EXTRACT_PARAMS, r"\1", full_call)
                        param_count = len(param_str.split(","))
                        if param_count != len(meta['function'][symbol]['params']):
                            error_msg = "%s(%s) : error : %s parameter count mismatch - %s actual vs. %s expected"%(fin, iline+1, symbol, param_count, len(meta['function'][symbol]['params']))
                            print(error_msg)
                            util.makeError(error_msg)
                            print("line = %s"%line)

                    ref = _make_ref(fin, iline, symbol, symbol_type, meta)
                    if ref:
                        tuple = line.partition(word)

                        newline += tuple[0] + tuple[1].replace(word, ref)
                        if tuple[2] and not re.match(r'\s', tuple[2]):
                            # reStructuredText requires an escape character after references that are not followed by whitespace
                            newline += "\\"
                        line = tuple[2]
                    else:
                        # env vars and macros have no API entry by design; others (e.g. callback) warn
                        if not re.match(r"env|macro", symbol_type):
                            print("%s(%s) : warning : reference link %s (type=%s) not used."%(fin, iline+1, symbol, symbol_type))
                else:
                    print("%s(%s) : warning : reference link %s not used."%(fin, iline+1, word))

            newline += line

        outlines.append(newline)

    util.writelines(os.path.abspath(fout), outlines)

    return util.makoWrite(os.path.abspath(fout), fout,
                          ver=ver,
                          namespace=namespace,
                          tags=tags,
                          meta=meta)

# object types rendered on the API-reference pages by api_spec.mako
RE_API_OBJ_TYPE = r"function|enum|struct|union|handle|typedef"

# synthetic bucket key for classless structs/enums -> the "Data Types" page
_DATATYPES_KEY = "__datatypes__"

# Functions are the heavy content on a class page (each carries a large,
# cross-referenced list of possible result codes). Cap functions-per-page and
# paginate the overflow onto sibling pages joined by a numbered pager. Enums and
# structs are light (no result-code lists) and do NOT count toward this cap --
# they ride on the class's final page.
_MAX_FUNCS_PER_PAGE = 25

# {pagename: class-TOC HTML} for classes that paginate across >1 page. Populated
# by generate_rst (accumulated across the per-section calls of one build) and
# written to source/class_toc.json for conf.py to load into html_context; the
# _templates/class-toc.html secondary-sidebar component renders it so a paginated
# page's right sidebar lists the WHOLE class, not just the current page.
_CLASS_TOC_MAP = {}
_CLASS_TOC_FILENAME = "class_toc.json"

# {C enumerator name: version} for enum values introduced LATER than their enum
# (added to an existing enum). Populated by generate_rst (--rst phase); injected into
# the Doxygen XML by _postprocess_generated_xml (--html phase) so Breathe renders a
# "(since vX)" note on just those values. Docs-only -- the generated C headers are
# never touched. Persisted to source/etor_since.json so it survives when CI runs the
# --rst and --html phases as SEPARATE processes (the html process reloads it).
_ETOR_SINCE = {}
_ETOR_SINCE_FILENAME = "etor_since.json"

# Doxygen writes progress to stdout and diagnostics to stderr, so its stderr is exactly
# the set of lines a contributor needs to act on. generate_common() saves it here so CI
# can quote just those lines into a PR comment instead of the whole multi-thousand-line
# build log. Written under docs/, which is gitignored.
DOXYGEN_WARNINGS_FILENAME = "doxygen-warnings.log"

# Same idea for sphinx-build: its -w option copies just the warnings to this file.
SPHINX_WARNINGS_FILENAME = "sphinx-warnings.log"

"""
    Collect enum values whose version exceeds their enum's version (i.e. added to an
    already-existing enum) into _ETOR_SINCE, keyed by the C enumerator name exactly as
    it appears in the generated header / Doxygen XML (th.make_etor_name, C form).
"""
def _collect_etor_since(specs, meta, namespace, tags):
    for s in specs:
        for obj in s['objects']:
            if not re.match(r"enum", obj['type']):
                continue
            enum_ver = obj.get('version', '1.0')
            for item in obj.get('etors', []):
                ever = item.get('version', enum_ver)
                if th.version_key(ever) > th.version_key(enum_ver):
                    cname = th.make_etor_name(namespace, tags, obj['name'], item['name'], False, meta)
                    _ETOR_SINCE[cname] = ever

"""
    Load the persisted enum-value version map (if this is a separate --html process
    where generate_rst did not run in-process to populate _ETOR_SINCE).
"""
def _ensure_etor_since_loaded(dstpath):
    path = os.path.join(dstpath, "source", _ETOR_SINCE_FILENAME)
    if not _ETOR_SINCE and util.exists(path):
        _ETOR_SINCE.update(util.jsonRead(path))

"""
    Append a "(since vX)" note to each later-added enum value's rendered description in
    the FINAL HTML (after sphinx-build). We post-process the Breathe/Sphinx output rather
    than Doxygen's XML because sphinx+breathe are version-pinned (run.py enforces
    third_party/requirements.txt) and therefore emit identical markup everywhere, whereas
    the doxygen binary is unpinned (system apt) and its XML serialization can differ
    between local and CI -- which silently broke the XML-based injection in CI.

    Each enumerator renders as `... <span class="pre">CNAME</span> ... </dt><dd><p>DESC</p>`.
    We match the value's name span and append the note just before the </p> of its
    description, staying within the same enumerator (tempered `(?!</dd>)`).
"""
def _inject_etor_versions_html(htmlpath):
    if not _ETOR_SINCE:
        return
    for fn in glob.iglob(os.path.join(os.path.abspath(htmlpath), "**", "*.html"), recursive=True):
        with open(fn, "r+", encoding="utf-8") as f:
            data = f.read()
            if "cpp enumerator" not in data:
                continue
            changed = False
            for cname, ver in _ETOR_SINCE.items():
                needle = '<span class="pre">%s</span>' % cname
                if needle not in data:
                    continue
                # Anchor to the enumerator's OWN <dt ...> (which contains the name span)
                # through to the first <p> of its <dd>, without crossing a </dt> or </dd>.
                # This prevents a stray name-span (e.g. a cross-reference) from matching an
                # unrelated element's description far away in the page.
                pattern = (r'(<dt class="sig sig-object cpp"[^>]*>(?:(?!</dt>).)*?'
                           + re.escape(needle)
                           + r'(?:(?!</dt>).)*?</dt>\s*<dd>\s*<p>(?:(?!</dd>).)*?)(</p>)')
                new = re.sub(pattern,
                             r'\1<em class="since-note"> (since v' + ver + r')</em>\2',
                             data, count=1, flags=re.DOTALL)
                if new != data:
                    data = new
                    changed = True
            if changed:
                f.seek(0)
                f.write(data)
                f.truncate()

"""
    Turn the generated "[DEPRECATED since X]" text tag (see helper.make_deprecated_tag)
    into a styled badge wherever it shows: briefs, enum values, members, params.
    Text only -- never inside a tag's attributes.
    Also drop what the page callout already says: doxygen's "Deprecated: Since X."
    block made from the generated @deprecated (helper.make_details_lines), and the
    tag on the brief of an object that has a callout.
"""
def _badge_deprecated_html(htmlpath):
    tag_re = re.compile(r'\[DEPRECATED since (\d+\.\d+)\](?![^<]*>)')
    block_re = re.compile(r'<p><dl>\s*<dt class="sig sig-object cpp">\s*<em><span class="pre">'
                          r'Deprecated:</span></em></dt>\s*<dd><p>Since \d+\.\d+\.'
                          r'(?:(?!</dd>).)*</dd></dl>\s*</p>\s*', re.S)
    # the brief's tag right under a page callout repeats it; enum values, members
    # and params have no callout, so they keep their badge
    brief_re = re.compile(r'(<p class="api-deprecated">(?:(?!</p>).)*</p>\s*<dl class="cpp [^"]+">'
                          r'\s*<dt (?:(?!</dt>).)*</dt>\s*<dd><p>)\[DEPRECATED since \d+\.\d+\]\s*', re.S)
    for fn in glob.iglob(os.path.join(os.path.abspath(htmlpath), "**", "*.html"), recursive=True):
        with open(fn, encoding="utf-8") as f:
            data = f.read()
        new = brief_re.sub(r'\1', data)
        new = tag_re.sub(r'<span class="deprecated-badge">Deprecated since \1</span>', new)
        new = block_re.sub('', new)
        if new != data:
            with open(fn, "w", encoding="utf-8", newline="\n") as f:
                f.write(new)

"""
    Point cross-references at an API's section heading (e.g. #zeinitdrivers) rather
    than its signature anchor (#ze__api_8h_1a...), which lands below the heading.
    Only ids of the section's own first definition are retargeted, so links to enum
    values or struct members still land on their row.
"""
def _retarget_api_links_html(htmlpath):
    files = glob.glob(os.path.join(os.path.abspath(htmlpath), "**", "*.html"), recursive=True)
    sec_re = re.compile(r'<section id="([^"]+)">((?:(?!<section|</dt>).)*?<h[1-6][^>]*>'
                        r'(?:(?!<section|</dt>).)*?<dt class="sig sig-object[^"]*"(?:(?!</dt>).)*)</dt>',
                        re.S)
    pages, targets = {}, {}
    for fn in files:
        with open(fn, encoding="utf-8") as f:
            pages[fn] = f.read()
        for m in sec_re.finditer(pages[fn]):
            dt = m.group(2)[m.group(2).rfind('<dt '):]
            for i in re.findall(r'id="([^"]+)"', dt):
                targets[(fn, i)] = m.group(1)

    ref_re = re.compile(r'(<a class="reference internal" href=")([^"#]*)#([^"]+)"')
    for fn, data in pages.items():
        def repl(m):
            page = os.path.normpath(os.path.join(os.path.dirname(fn), m.group(2))) if m.group(2) else fn
            sec = targets.get((page, m.group(3)))
            return '%s%s#%s"'%(m.group(1), m.group(2), sec) if sec else m.group(0)
        new = ref_re.sub(repl, data)
        if new != data:
            with open(fn, "w", encoding="utf-8", newline="\n") as f:
                f.write(new)

"""
    Reproduce Sphinx's HTML id for a heading/label from an object name, so we can
    build cross-page anchor links without a Sphinx round-trip. For the identifier
    names used here this matches nodes.make_id: lower-case, non-alphanumerics ->
    single hyphen (verified: zeCommandListCreate -> zecommandlistcreate,
    ze_command_list_desc_t -> ze-command-list-desc-t).
"""
def _anchor_id(name):
    return re.sub(r"[^a-z0-9]+", "-", name.lower()).strip("-")

"""
    Longest shared class-name prefix across a set of camelCase function names,
    trimmed to a word boundary (i.e. ending right before a capital letter), so the
    sidebar can show it once and list only the distinguishing tails:
      [zeCommandListCreate, zeCommandListCreateImmediate, zeCommandListDestroy]
      -> "zeCommandList"  (tails: Create / CreateImmediate / Destroy)
    Returns "" when there is no useful shared prefix (fewer than 2 names, or the
    prefix would be too short to be worth factoring out).
"""
def _common_func_prefix(names):
    if len(names) < 2:
        return ""
    raw = os.path.commonprefix(names)
    if not raw:
        return ""
    tails = [n[len(raw):] for n in names]
    if all(t[:1].isupper() for t in tails):
        # prefix already ends on a word boundary (next char capitalized everywhere)
        prefix = raw
    else:
        # prefix cut mid-word -> back off to the last capital in the shared prefix
        idx = max((i for i, c in enumerate(raw) if c.isupper()), default=-1)
        prefix = raw[:idx] if idx > 0 else ""
    return prefix if len(prefix) >= 3 else ""

# maturity tiers, in nav order: (maturity, subdir, index title, page-title adjective).
# The adjective disambiguates class pages whose names collide with their base
# counterparts: page title "<Class> - Extensions", headings "<Class> - Extension
# Structures". Base ("") gets no suffix. Empty adjective => base behavior.
_TIERS = [("base", "apis", "APIs", ""),
          ("ext", "extensions", "Extensions", "Extension"),
          ("exp", "experimental", "Experimental", "Experimental"),
          ("deprecated", "deprecated", "Deprecated", "Deprecated")]

"""
    per-object maturity: 'deprecated' if it has a 'deprecated' record, else derived
    from its name: 'exp' (experimental), 'ext' (stable extension), or 'base'. Uses the reliable object-name signal (Exp/Ext suffix on
    functions, _exp_/_ext_ on type names) rather than the header desc (whose parse
    regex is anchored/broken -- see TODO.md). Base files are internally mixed
    (device.yml = base + ext), so maturity MUST be per-object, not per-file.
"""
def _obj_maturity(obj):
    # deprecated objects leave their tier, whatever their maturity
    if obj.get('deprecated'):
        return "deprecated"
    name = obj.get('name', "")
    if re.search(r"Exp[0-9]*$", name) or re.search(r"_exp[0-9]*_", name):
        return "exp"
    if re.search(r"Ext$", name) or re.search(r"_ext_", name):
        return "ext"
    return "base"

"""
    True if the object list has anything api_spec.mako would render
    (a non-conditional function, or any enum/struct/union).
"""
def _objs_have_api_content(objs):
    for obj in objs:
        t = obj['type']
        if re.match(r"function", t) and ("condition" not in obj):
            return True
        if re.match(r"enum|struct|union|handle|typedef", t):
            return True
    return False

"""
    Build the bottom paginator (`< Prev  1 2 3  Next >`) linking a class's chunk
    pages. `slugs` is every chunk slug for the class, in order; `current` is the
    index being rendered. Returns a single-line raw-HTML <nav>, or "" when the
    class is a single page (nothing to paginate). Links are bare relative
    filenames -- all chunks are siblings in the same tier directory.
"""
def _paginator_html(slugs, current):
    if len(slugs) <= 1:
        return ""

    parts = []
    if current > 0:
        parts.append('<a class="prev" href="%s.html">&lsaquo; Prev</a>' % slugs[current - 1])
    else:
        parts.append('<span class="prev disabled">&lsaquo; Prev</span>')

    for i, slug in enumerate(slugs):
        if i == current:
            parts.append('<strong class="current">%d</strong>' % (i + 1))
        else:
            parts.append('<a href="%s.html">%d</a>' % (slug, i + 1))

    if current < len(slugs) - 1:
        parts.append('<a class="next" href="%s.html">Next &rsaquo;</a>' % slugs[current + 1])
    else:
        parts.append('<span class="next disabled">Next &rsaquo;</span>')

    return '<nav class="api-pager" aria-label="Page navigation">%s</nav>' % "".join(parts)

"""
    Build the right-sidebar "In this class" TOC for one class: every function/enum/
    struct across ALL of the class's pages, grouped, with cross-page links. Entries
    on `current_slug` get a `current-page` marker. Reuses the theme's nav classes so
    it renders natively; anchors/display names mirror api_spec.mako exactly.
"""
def _class_toc_html(class_pages, current_slug, namespace, tags):
    groups = [("Handles", r"handle"),
              ("Functions", r"function"),
              ("Enumerations", r"enum"),
              ("Typedefs", r"typedef"),
              ("Structures", r"struct|union")]
    # The current-page marker only means something when the class spans >1 page;
    # for a single-page class every entry is "on this page", so skip the marker.
    multipage = len(class_pages) > 1
    collected = {label: [] for label, _ in groups}
    for page in class_pages:
        pslug = page['slug']
        is_cur = multipage and (pslug == current_slug)
        for obj in page['objects']:
            t = obj['type']
            if re.match(r"function", t):
                if "condition" in obj:  # not rendered by api_spec.mako -> no anchor
                    continue
                name, label = th.make_func_name(namespace, tags, obj), "Functions"
            elif re.match(r"enum", t):
                name, label = th.make_type_name(namespace, tags, obj), "Enumerations"
            elif re.match(r"struct|union", t):
                name, label = th.make_type_name(namespace, tags, obj), "Structures"
            elif re.match(r"handle", t):
                name, label = th.make_type_name(namespace, tags, obj), "Handles"
            elif re.match(r"typedef", t):
                name, label = th.make_type_name(namespace, tags, obj), "Typedefs"
            else:
                continue
            href = "%s.html#%s" % (pslug, _anchor_id(name))
            collected[label].append((name, href, is_cur))

    # Own markup (collapsible <details> groups + custom classes) rather than the
    # theme's nav/section-nav classes: the theme hides nested nav levels and drives
    # them via scroll-spy on real page sections, which this cross-page index has no
    # match for. Native <details> also gives collapsible groups with no JS.
    out = []
    for label, _ in groups:
        entries = collected[label]
        if not entries:
            continue
        # Functions only: factor out the shared class prefix (e.g. "zeCommandList")
        # and show it once, then list just the tails ("...Create"). Enums/structs
        # keep full names -- their naming doesn't follow this convention.
        prefix = _common_func_prefix([n for n, _, _ in entries]) if label == "Functions" else ""
        out.append('<details class="ctoc-group" open>'
                   '<summary>%s <span class="ctoc-count">%d</span></summary>' % (label, len(entries)))
        if prefix:
            out.append('<div class="ctoc-prefix">%s</div>' % prefix)
        out.append('<ul class="ctoc-list">')
        for name, href, is_cur in entries:
            cls = ' class="current-page"' if is_cur else ''
            if prefix and name.startswith(prefix):
                disp = "&hellip;" + name[len(prefix):]
            else:
                disp = name
            out.append('<li%s><a href="%s">%s</a></li>' % (cls, href, disp))
        out.append('</ul></details>')
    return "".join(out)

"""
    Build per-class (family) pages for one tier's buckets (class-name -> [objs]).
    Ordinal-ordered (Data Types last), empty pages skipped, objects ordered
    functions -> enums -> structs. Functions are paginated at _MAX_FUNCS_PER_PAGE
    (enums/structs ride on the final page); when a class spans multiple pages,
    page 1 keeps the base slug (stable URL + the only one in the nav toctree) and
    later pages get a `-N` suffix and are marked orphan. Returns a list of
    {slug, title, objects, paginator, orphan, in_toc}.
"""
def _class_pages(buckets, meta, namespace, tags, tier_title="", tier_adjective=""):
    def order_key(key):
        if key == _DATATYPES_KEY:
            return (1, 0)
        return (0, meta.get('class', {}).get(key, {}).get('ordinal', 0))

    pages = []
    for key in sorted(buckets.keys(), key=order_key):
        objs = buckets[key]
        if not _objs_have_api_content(objs):
            continue
        if key == _DATATYPES_KEY:
            class_title, slug = "Data Types", "data_types"
        else:
            class_title = th.make_class_title(namespace, tags, key)
            slug = th.make_class_slug(namespace, tags, key)

        # Tier-qualified page title + section-heading prefix (base = no suffix).
        # nav_label stays the short class title so the sidebar isn't cluttered
        # (the tier is already the parent nav node).
        if tier_adjective:
            page_title = "%s - %s" % (class_title, tier_title)
            heading_prefix = "%s - %s" % (class_title, tier_adjective)
        else:
            page_title = class_title
            heading_prefix = class_title

        funcs = sorted([o for o in objs if re.match(r"function", o['type'])], key=th.function_sort_key)
        enums = [o for o in objs if re.match(r"enum", o['type'])]
        structs = [o for o in objs if re.match(r"struct|union", o['type'])]
        handles = [o for o in objs if re.match(r"handle", o['type'])]
        typedefs = [o for o in objs if re.match(r"typedef", o['type'])]

        # Paginate functions only; handles open page 1, enums/structs land on the final page.
        groups = [funcs[i:i + _MAX_FUNCS_PER_PAGE]
                  for i in range(0, len(funcs), _MAX_FUNCS_PER_PAGE)] or [[]]
        groups[0] = handles + groups[0]
        groups[-1] = groups[-1] + enums + typedefs + structs

        slugs = [slug] + ["%s-%d" % (slug, i + 1) for i in range(1, len(groups))]
        for idx, group in enumerate(groups):
            pages.append({
                'slug': slugs[idx],
                'title': page_title,
                'heading_prefix': heading_prefix,
                'nav_label': class_title,
                'class_key': key,
                'objects': group,
                'paginator': _paginator_html(slugs, idx),
                # Page 1 carries a HIDDEN toctree of its overflow pages: this keeps
                # pages 2+ in the doc tree (so landing on one still expands/highlights
                # the class's nav branch) without listing them in the tier index -- the
                # left nav still shows a single "Command List" entry. Because they're in
                # a toctree now, they are not orphans.
                'hidden_toctree': slugs[1:] if idx == 0 else [],
                'in_toc': idx == 0,
            })
    return pages

"""
    Split a section's renderable objects into maturity tiers (APIs / Extensions /
    Experimental); within each tier group by class/family. Returns the ordered,
    non-empty tiers: [{'dir','title','pages':[{slug,title,objects}]}].
"""
def _build_tiers(specs, meta, namespace, tags):
    buckets = {"base": {}, "ext": {}, "exp": {}, "deprecated": {}}
    for s in specs:
        for obj in s['objects']:
            if not re.match(RE_API_OBJ_TYPE, obj['type']):
                continue
            mat = _obj_maturity(obj)
            key = obj.get('class') if obj.get('class') else _DATATYPES_KEY
            buckets[mat].setdefault(key, []).append(obj)

    tiers = []
    for mat, tdir, ttitle, tadj in _TIERS:
        pages = _class_pages(buckets[mat], meta, namespace, tags, ttitle, tadj)
        if pages:
            tiers.append({'dir': tdir, 'title': ttitle, 'pages': pages})
    return tiers

"""
    Reverse "usage" index for the API reference (core, tools, sysman): for each
    struct/union/enum/handle, the functions that take it, the structs that hold it,
    the extra links from the _rule_* functions below, and for handles a link to the
    guide section that explains the object.
    Returns {raw obj name: rst container block}. Types used everywhere are skipped.
"""
_USAGE_NAMESPACES = ("ze", "zet", "zes")
_USAGE_SKIP = ("$x_result_t", "$x_bool_t", "$x_structure_type_t", "$t_structure_type_t", "$s_structure_type_t")
# Sysman handles may become their own types later, so do not show "Alias of"
# (it would suggest zes and ze handles are interchangeable).
_NO_ALIAS_NAMESPACES = ("zes",)
# display order of the usage lines
_USAGE_LABELS = ("Obtained from", "Used by", "Member of", "Variant of", "Variants", "Passed to callback in",
                 "Format value", "Buffer data for", "Packed form of", "Packed as",
                 "pNext may point to", "Goes in pNext of", "Alias of", "Extension", "See also")
# labels that also get a line per other spec, e.g. "Used by (Tools)"
_USAGE_CROSS_LABELS = ("Obtained from", "Used by", "Member of")
# a line with more links than this folds to one line with a "Show all N" toggle
_USAGE_SHOW = 10

def _usage_line_rst(label, links, uid):
    if len(links) <= _USAGE_SHOW:
        return "   | **%s:** %s" % (label, ", ".join(links))
    # CSS-only toggle (custom.css): the checkbox state unfolds the same line
    return "   | **%s:** :raw-html:`%s` %s :raw-html:`%s`" % (label,
        '<span class="api-usage-fold"><input type="checkbox" id="%s">'
        '<span class="api-usage-links">' % uid,
        ", ".join(links),
        '</span><label for="%s"><span class="more">Show all %d</span>'
        '<span class="less">Show less</span></label></span>' % (uid, len(links)))

def _usage_base_type(t):
    return re.sub(r"\b(const|struct|union)\b|\*|\[.*?\]", "", t).strip()

_RST_UNDERLINE = re.compile(r"^([=\-~^\"'`#*+])\1+\s*$")

def _read_text(path):
    with open(path, encoding="utf-8") as f:
        return f.read()

def _rst_headings(text):
    """[(title, explicit label or None)] for each section heading in rst text."""
    lines = text.splitlines()
    out = []
    for i in range(1, len(lines)):
        t = lines[i - 1].strip()
        if t and _RST_UNDERLINE.match(lines[i]) and not _RST_UNDERLINE.match(lines[i - 1]) \
                and len(lines[i].strip()) >= len(t):
            j = i - 2
            while j >= 0 and not lines[j].strip():
                j -= 1
            m = re.match(r"^\.\. _([^:]+):\s*$", lines[j]) if j >= 0 else None
            out.append((t, m.group(1) if m else None))
    return out

def _guide_pages(dstpath):
    """Read once per section: PROG.rst headings and the EXT_*.rst pages (sorted)."""
    prog = os.path.join(dstpath, "PROG.rst")
    heads = _rst_headings(_read_text(prog)) if os.path.exists(prog) else []
    exts = [(os.path.splitext(os.path.basename(f))[0], _read_text(f))
            for f in sorted(glob.glob(os.path.join(dstpath, "EXT_*.rst")))]
    return heads, exts

def _guide_link(namespace, tags, obj, heads, exts):
    """rst link to the guide section for a handle's class, or None.
    Order: PROG section label equal to the class title (e.g. Performance-Factor),
    PROG heading equal to the class title, PROG heading holding its words,
    an exact match with the last word dropped (Event Pool -> Events), then the EXT_*
    page that names the handle."""
    from docutils.nodes import make_id
    words = th.make_class_title(namespace, tags, obj['class']).lower().split()
    titles = [t for t, _ in heads]

    def word_hit(w, h):
        return h == w or (len(w) >= 3 and h.startswith(w))
    def exact(t, ws):
        return t.lower() in (" ".join(ws), " ".join(ws) + "s", " ".join(ws) + "es")
    def holds(t, ws):
        return all(any(word_hit(w, h) for h in re.split(r"[\s/]+", t.lower())) for w in ws)
    for t, label in heads:  # a section label equal to the class title is exact
        if label and label.lower().replace("-", " ").replace("_", " ") in (" ".join(words), " ".join(words) + "s"):
            return ":ref:`%s (Programming Guide) <%s>`" % (t, label)
    tries = [(exact, words), (holds, words)]
    if len(words) > 1:  # exact only: "holds" on fewer words matches unrelated headings
        tries.append((exact, words[:-1]))
    for test, ws in tries:
        for t, label in heads:
            if test(t, ws) and (label or titles.count(t) == 1):
                if label:
                    return ":ref:`%s (Programming Guide) <%s>`" % (t, label)
                return "`%s (Programming Guide) <../../PROG.html#%s>`__" % (t, make_id(t))
    name = th.make_type_name(namespace, tags, obj)
    # plain name, or its :ref: label once the page links it
    pat = re.compile(r"\b(%s|%s)\b" % (re.escape(name), re.escape(name.replace("_", "-"))))
    for page, text in exts:
        if pat.search(text):
            return ":doc:`../../%s`" % page
    return None

# --- Link rules -------------------------------------------------------------
# Each rule finds one kind of link that is not visible from param/member types.
# Each returns (from raw name, to raw name) pairs, so a rule can be removed alone.
# Rules A, B: exact, derived from types/members -- keep.
# Rules C-G: TEMPORARY, they parse prose -- delete each once its YML field exists.

def _rule_a_callback_params(objs):
    """RULE A (callbacks): a struct passed to a callback is linked to the struct
    that holds that callback, since callbacks have no API-page entry.
    e.g. ze_rtas_geometry_aabbs_ext_cb_params_t -> ze_rtas_builder_procedural_geometry_info_ext_t"""
    structs = [o for o in objs if o['type'] in ('struct', 'union')]
    for cb in (o for o in objs if o['type'] == 'callback'):
        holders = [o['name'] for o in structs
                   if any(_usage_base_type(m['type']) == cb['name'] for m in o['members'])]
        for p in cb['params']:
            for h in holders:
                yield _usage_base_type(p['type']), h

def _rule_b_tagged_variants(objs):
    """RULE B (tagged variants): struct T is a variant of struct B when T starts with
    all of B's members and one of them says "must be $X_..." (a type tag).
    e.g. ze_rtas_builder_procedural_geometry_info_ext_t -> ze_rtas_builder_geometry_info_ext_t
    Skips *_base_* and stype/pNext structs, which every struct would match."""
    structs = [o for o in objs if o['type'] in ('struct', 'union')]
    for b in structs:
        if b.get('base') or not b['members'] or "_base_" in b['name']:
            continue
        key = [(m['type'], m['name']) for m in b['members']]
        for t in structs:
            lead = t['members'][:len(key)]
            if t is not b and len(t['members']) > len(key) \
                    and [(m['type'], m['name']) for m in lead] == key \
                    and any(re.search(r"must be \$[A-Z]+_\w+", m['desc']) for m in lead):
                yield t['name'], b['name']

def _rule_c_pnext_prose(objs, namespace, tags):
    """RULE C (pNext prose): reads every desc/details sentence that says "pNext".
    TEMPORARY: replace with the planned `extends` YML field, then delete this rule.
    A named struct is the chain target; "this structure should point to X" or
    "use X as pNext" reverses it; a sentence naming only a function targets that
    function (if it has a pNext param) or its pNext-able struct params.
    A member desc is about its own struct's pNext, so it always reverses.
    Yields (ext struct, target struct or function); function targets end in "()"."""
    rev = re.compile(r"this structure should point|use \S+ as pNext", re.I)
    structs = {th.subt(namespace, tags, o['name']): o for o in objs if o['type'] in ('struct', 'union')}
    funcs = {th.make_func_name(namespace, tags, o): o for o in objs if o['type'] == 'function'}
    for sname, o in structs.items():
        texts = [(o['desc'], False)] + [(str(x), False) for x in o.get('details', [])]
        texts += [(m['desc'], True) for m in o['members']
                  if m['name'] != "pNext" and isinstance(m.get('desc'), str)]
        for text, member in texts:
            for sent in re.split(r"(?<=\.)\s+", th.subt(namespace, tags, text)):
                if "pNext" not in sent:
                    continue
                named = [x for x in dict.fromkeys(re.findall(r"\b\w+_t\b", sent))
                         if x in structs and x != sname]
                if member:
                    for x in named:
                        yield structs[x]['name'], o['name']
                elif rev.search(sent):
                    for x in named:
                        yield structs[x]['name'], o['name']
                elif named:
                    for x in named:
                        yield o['name'], structs[x]['name']
                else:
                    for f in dict.fromkeys(re.findall(r"\b[a-z]{2,3}[A-Z]\w+", sent)):
                        if f not in funcs:
                            continue
                        params = funcs[f]['params']
                        if any(p['name'] == "pNext" for p in params):
                            yield o['name'], f + "()"
                        for p in params:
                            ps = structs.get(th.subt(namespace, tags, _usage_base_type(p['type'])))
                            if ps and ps.get('base') and ps is not o:
                                yield o['name'], ps['name']

def _rule_d_buffer_format(objs, namespace, tags):
    """RULE D (buffer data format): an enum value whose desc says "(see S)" names
    struct S as the layout of a void* buffer; a member that says "must be <value>"
    marks the struct holding that buffer.
    e.g. ze_rtas_quad_indices_uint32_ext_t -> ..._QUAD_INDICES_UINT32 ->
         quadFormat of ze_rtas_builder_quads_geometry_info_ext_t
    TEMPORARY: replace with a planned YML field on the enum value naming its
    struct (like `extends`), then delete this rule.
    Yields ("format", S, (enum, etor)) and ("data", S, holder struct)."""
    structs = {th.subt(namespace, tags, o['name']): o for o in objs if o['type'] in ('struct', 'union')}
    for e in objs:
        if e['type'] != 'enum' or "structure_type" in e['name']:
            continue
        for et in e['etors']:
            m = re.search(r"\(see (\w+_t)\)", th.subt(namespace, tags, et['desc']))
            if not m or m.group(1) not in structs:
                continue
            s = structs[m.group(1)]['name']
            etor = th.subt(namespace, tags, et['name'])
            yield "format", s, (e['name'], etor)
            for o in structs.values():
                if any(re.search(r"must be\b.*\b%s\b" % etor, th.subt(namespace, tags, mb['desc']))
                       for mb in o['members']):
                    yield "data", s, o['name']

def _rule_e_packed_typedef(objs):
    """RULE E (packed typedefs): a typedef whose desc says "(see E)" is the packed
    storage form of enum E.
    e.g. ze_rtas_builder_packed_input_data_format_ext_t -> ze_rtas_builder_input_data_format_ext_t
    TEMPORARY: replace with a planned YML field on the typedef naming its enum,
    then delete this rule."""
    enums = {o['name'] for o in objs if o['type'] == 'enum'}
    for o in objs:
        if o['type'] == 'typedef':
            m = re.search(r"\(see (\$\w+_t)\)", o['desc'])
            if m and m.group(1) in enums:
                yield o['name'], m.group(1)

def _rule_f_void_param(objs):
    """RULE F (void* params): a struct that a void* param's text says it points to
    is used by that function, though the param type hides it.
    e.g. ze_runtime_requirements_graph_desc_t -> zeDeviceGetRuntimeRequirements (pObjDesc)
    Reads the param desc and the details that name the param; needs "point(er) to".
    TEMPORARY: replace with a planned YML field on the param naming its types,
    then delete this rule."""
    structs = {o['name'] for o in objs if o['type'] in ('struct', 'union')}
    for o in (o for o in objs if o['type'] == 'function'):
        for p in o['params']:
            if p['name'] == "pNext" or not re.fullmatch(r"(const )?void\*", p['type'].strip()):
                continue
            texts = [p['desc']] + [str(x) for x in o.get('details', [])
                                   if re.search(r"\b%s\b" % re.escape(p['name']), str(x))]
            for t in texts:
                if re.search(r"\bpoint(?:s|ing|er)? to\b", t):
                    for x in dict.fromkeys(re.findall(r"\$\w+_t\b", t)):
                        if x in structs:
                            yield x, o

def _rule_g_form_of(objs):
    """RULE G (form of): a function whose details say it takes parameters
    "in the form of S" uses struct S, e.g. ze_base_desc_t.
    TEMPORARY: replace with a planned YML field, then delete this rule."""
    structs = {o['name'] for o in objs if o['type'] in ('struct', 'union')}
    for o in (o for o in objs if o['type'] == 'function'):
        for t in (str(x) for x in o.get('details', [])):
            for x in re.findall(r"in the form of (\$\w+_t)\b", t):
                if x in structs:
                    yield x, o

def _build_usage_rst(specs, namespace, tags, dstpath, others=()):
    if namespace not in _USAGE_NAMESPACES:
        return {}
    objs = [o for s in specs for o in s['objects'] if "condition" not in o]
    types = {o['name']: o for o in objs if re.match(r"struct|union|enum|handle|typedef", o['type'])}
    tables = {}

    # match hard-coded prefixes too (zet_metric_handle_t == $t_metric_handle_t)
    by_cname = {th.subt(namespace, tags, n): n for n in types}

    def add(label, key, val):
        key = key if key in types else by_cname.get(th.subt(namespace, tags, key), key)
        if key in types and key not in _USAGE_SKIP and val not in tables.setdefault(label, {}).setdefault(key, []):
            tables[label][key].append(val)

    def ref(name):
        if name.endswith("()"):  # function target from rule C
            return ":ref:`%s`" % name[:-2]
        return ":ref:`%s`" % th.subt(namespace, tags, name).replace("_", "-")

    # "[out]" handle pointer params: the function gives out that handle
    # (listed under "Obtained from" instead of "Used by"). IPC handles are
    # structs, so match on the *_handle_t name too.
    def param_label(p, key):
        out = re.match(r"\[(out|in,out)\]", p.get('desc', ''))
        if out and "*" in p['type'] and "const" not in p['type'] \
                and (types.get(key, {}).get('type') == 'handle' or key.endswith("_handle_t")):
            return "Obtained from"
        return "Used by"

    # Direct links from param, return and member types: first this spec, then
    # the other specs built in this run, e.g. "Used by (Tools)" for a tools API
    # taking a core type. others: [(section, namespace, tags, specs)].
    sources = [("", namespace, tags, objs)]
    for section, other_ns, other_tags, other_specs in others:
        if other_ns in _USAGE_NAMESPACES:
            sources.append((" (%s)" % section.capitalize(), other_ns, other_tags,
                            [o for s in other_specs for o in s['objects'] if "condition" not in o]))
    cross = [sfx for sfx, _, _, _ in sources[1:]]
    for sfx, ns, tg, src in sources:
        key_of = lambda t: by_cname.get(th.subt(ns, tg, _usage_base_type(t)))
        for o in src:
            if o['type'] == 'function':
                fref = ":ref:`%s`" % th.make_func_name(ns, tg, o)
                for p in o['params']:
                    key = key_of(p['type'])
                    if key:
                        add(param_label(p, key) + sfx, key, fref)
                # a function that returns a handle (e.g. zeDriverGetDefaultContext)
                key = key_of(o.get('return_type', ""))
                if key and key.endswith("_handle_t"):
                    add("Obtained from" + sfx, key, fref)
            elif o['type'] in ('struct', 'union'):
                for m in o['members']:
                    key = key_of(m['type'])
                    if key and key != o['name']:
                        add("Member of" + sfx, key, ":ref:`%s`" % th.subt(ns, tg, o['name']).replace("_", "-"))

    for frm, to in _rule_a_callback_params(objs):
        add("Passed to callback in", frm, ref(to))
    for frm, to in _rule_b_tagged_variants(objs):
        add("Variant of", frm, ref(to))
        add("Variants", to, ref(frm))
    for frm, to in _rule_c_pnext_prose(objs, namespace, tags):
        add("Goes in pNext of", frm, ref(to))
        add("pNext may point to", to, ref(frm))
    for kind, frm, to in _rule_d_buffer_format(objs, namespace, tags):
        if kind == "format":
            enum, etor = to
            add("Format value", frm, ":ref:`%s <%s>`" % (etor, th.subt(namespace, tags, enum).replace("_", "-")))
        else:
            add("Buffer data for", frm, ref(to))

    for frm, to in _rule_e_packed_typedef(objs):
        add("Packed form of", frm, ref(to))
        add("Packed as", to, ref(frm))
    for frm, fn in _rule_g_form_of(objs):
        add("Used by", frm, ":ref:`%s`" % th.make_func_name(namespace, tags, fn))
    for frm, fn in _rule_f_void_param(objs):
        add("Used by", frm, ":ref:`%s`" % th.make_func_name(namespace, tags, fn))

    # extension version enums: link the EXT page whose label is the extension name
    ext_of = _extension_name_map(specs, namespace, tags)
    heads, exts = _guide_pages(dstpath)
    ext_labels = set()
    for _, text in exts:
        m = re.search(r"^\.\. _(\S+):\s*$", text, re.M)
        if m:
            ext_labels.add(m.group(1))
    for name, o in types.items():
        full = th.subt(namespace, tags, name)
        if o['type'] != 'enum' or not re.search(r"_(?:ext_|exp_)?version(?:_ext|_exp)?_t$", full) \
                or full not in ext_of:
            continue
        if ext_of[full] in ext_labels:
            add("Extension", name, ":ref:`%s`" % ext_of[full])
            continue
        # guard: a page names this enum but its first label is not the extension name
        pat = re.compile(r"\b(%s|%s)\b" % (re.escape(full), re.escape(full.replace("_", "-"))))
        for page, text in exts:
            if pat.search(text):
                msg = "%s.rst : error : first label must be '.. _%s:' (the extension name) so %s can link to it" % (
                    page, ext_of[full], full)
                print(msg)
                util.makeError(msg)

    for name, o in types.items():
        if o['type'] == 'typedef' and o.get('value') in types:
            add("Alias of", name, ref(o['value']))
        if o['type'] == 'handle':
            if o.get('alias') and namespace not in _NO_ALIAS_NAMESPACES:
                add("Alias of", name, ref(o['alias']))
            else:
                link = _guide_link(namespace, tags, o, heads, exts)
                if link:
                    add("See also", name, link)

    labels = [l for base in _USAGE_LABELS
              for l in [base] + ([base + sfx for sfx in cross] if base in _USAGE_CROSS_LABELS else [])]
    rst = {}
    for name in types:
        lines = [_usage_line_rst(label, tables[label][name], "usage-%s-%d" % (
                     th.subt(namespace, tags, name).replace("_", "-"), i))
                 for i, label in enumerate(labels) if tables.get(label, {}).get(name)]
        if lines:
            rst[name] = ".. container:: api-usage\n\n" + "\n".join(lines)
    return rst

"""
    Build version lookup maps for extension doc pages, keyed by the SUBSTITUTED
    (namespaced) name so they match the tokens/refs in the generated RST:
      enum_ver:   e.g. ze_image_copy_ext_version_t -> introduced spec version ("1.3")
      struct_ver: an ext/exp struct name           -> version of its structure_type etor
    Only ext/exp structs are recorded -- a base struct would wrongly report "1.0".
"""
def _extension_version_maps(specs, namespace, tags):
    enum_ver, struct_ver = {}, {}
    for s in specs:
        for obj in s['objects']:
            if not re.match(r"enum", obj['type']):
                continue
            full = th.subt(namespace, tags, obj['name'])
            # version enums appear in several orderings: _version_t, _ext_version_t,
            # _exp_version_t, _version_ext_t, _version_exp_t.
            if re.search(r'_(?:ext_|exp_)?version(?:_ext|_exp)?_t$', full):
                enum_ver[full] = obj.get('version', '1.0')
            if full.endswith("structure_type_t"):
                enum_v = obj.get('version', '1.0')
                for et in obj.get('etors', []):
                    struct = th.subt(namespace, tags, et.get('desc', '')).strip()
                    segs = struct.split('_')
                    if 'ext' in segs or 'exp' in segs:
                        struct_ver[struct] = et.get('version', enum_v)
    return enum_ver, struct_ver

"""
    Map each enum/struct/union (SUBSTITUTED name) to its 'deprecated' record, for
    extension doc pages. Includes records inherited from a deprecated extension header.
"""
def _extension_deprecation_map(specs, namespace, tags):
    return {th.subt(namespace, tags, obj['name']): obj['deprecated']
            for s in specs for obj in s['objects']
            if obj.get('deprecated') and re.match(r"enum|struct|union", obj['type'])}

"""
    Map each object (SUBSTITUTED name) to its extension name: the value of the
    nearest preceding *_NAME macro in its file, e.g. ZE_experimental_power_saving_hint.
"""
def _extension_name_map(specs, namespace, tags):
    names = {}
    for s in specs:
        ext = None
        for obj in s['objects']:
            if obj['type'] == 'macro' and obj['name'].endswith('_NAME'):
                ext = th.subt(namespace, tags, obj.get('value', '')).strip('"\'')
            elif ext:
                names[th.subt(namespace, tags, obj['name'])] = ext
    return names

def _page_refs(text, name):
    return name in text or name.replace('_', '-') in text

"""
    Resolve an extension page's introduced spec version:
      1. the version enum it references (authoritative), else
      2. the earliest structure_type-etor version among its ext/exp structs, else None.
    Tokens appear either underscored (prose/code) or hyphenated (`:ref:` targets).
    A None result is a spec bug -- every extension must define & reference a version
    enum (generate_rst turns None into a build error, no manual override).
"""
def _extension_intro_version(text, enum_ver, struct_ver):
    for table in (enum_ver, struct_ver):
        hits = [v for n, v in table.items() if _page_refs(text, n)]
        if hits:
            return min(hits, key=th.version_key)
    return None

"""
    Resolve an extension page's 'deprecated' record from the same object that sets
    its introduced version: the earliest version enum it references, else its ext/exp
    structs (only if all of them are deprecated). Returns (object name, record);
    record is None if not deprecated.
"""
def _extension_deprecation(text, enum_ver, struct_ver, dep_map):
    hits = [n for n in enum_ver if _page_refs(text, n)]
    if hits:
        name = min(hits, key=lambda n: th.version_key(enum_ver[n]))
        return name, dep_map.get(name)
    hits = [n for n in struct_ver if _page_refs(text, n)]
    recs = [dep_map.get(n) for n in hits]
    return (hits[0], recs[0]) if recs and all(recs) else (None, None)

"""
    RST list-table rows for one deprecated item: name, since, replacement, notes.
"""
def _deprecated_row(item, dep, namespace, tags, meta):
    if 'use' in dep:
        use = th.make_symbol_ref(namespace, tags, dep['use'], meta)
    elif 'related' in dep:
        use = "Related: " + th.make_symbol_ref(namespace, tags, dep['related'], meta)
    else:
        use = "--"
    reason = th.subt(namespace, tags, dep.get('reason', ""))
    return ["   * - %s" % item, "     - %s" % dep['since'], "     - %s" % use, "     - %s" % reason]

"""
    Write <section>/deprecated.rst: every deprecated extension, function, enum,
    struct, enum value and member in the section, each with its replacement link.
    Objects deprecated only through their extension are listed via the extension.
    Returns False (and writes nothing) if nothing is deprecated.
"""
def _write_deprecated_page(dstpath, title, ext_deps, specs, namespace, tags, meta, has_tier):
    groups = {k: [] for k in ("Extensions", "Functions", "Enumerations", "Structures",
                              "Enumeration values", "Structure members", "Other")}
    for doc, ext_name, dep in ext_deps:
        groups["Extensions"].append((":doc:`%s <%s>`" % (ext_name, doc), dep))
    for s in specs:
        for obj in s['objects']:
            t, dep = obj['type'], obj.get('deprecated')
            if dep and not dep.get('from_header'):
                name = th.make_func_name(namespace, tags, obj) if t == 'function' \
                    else th.subt(namespace, tags, obj['name'])
                if t == 'function' and 'condition' not in obj:
                    groups["Functions"].append((":ref:`%s`" % name, dep))
                elif t == 'enum':
                    groups["Enumerations"].append((":ref:`%s`" % name.replace("_", "-"), dep))
                elif t in ('struct', 'union'):
                    groups["Structures"].append((":ref:`%s`" % name.replace("_", "-"), dep))
                elif not (t == 'macro' and name.endswith('_NAME')):  # covered by its extension row
                    groups["Other"].append(("``%s``" % name, dep))
            tname = th.subt(namespace, tags, obj.get('name', ""))
            for et in obj.get('etors', []) if t == 'enum' else []:
                if et.get('deprecated'):
                    groups["Enumeration values"].append(
                        (th.make_symbol_ref(namespace, tags, et['name'], meta), et['deprecated']))
            for m in obj.get('members', []) if t in ('struct', 'union') else []:
                if m.get('deprecated'):
                    groups["Structure members"].append((":ref:`%s.%s <%s>`" % (
                        tname, m['name'], tname.replace("_", "-")), m['deprecated']))
    if not any(groups.values()):
        return False

    bar = "=" * max(60, len(title))
    lines = [bar, title, bar, "",
             "Everything below is deprecated. Use the replacement where one is listed.", ""]
    if has_tier:
        lines += ["The reference pages are under :doc:`Deprecated APIs <api/deprecated/index>`.", ""]
    for label, rows in groups.items():
        if not rows:
            continue
        lines += [label, "-" * len(label), "",
                  ".. list-table::", "   :header-rows: 1", "   :widths: 28 6 28 38",
                  "   :class: deprecated-table", "",
                  "   * - Name", "     - Since", "     - Replacement", "     - Notes"]
        for item, dep in sorted(rows, key=lambda r: r[0].lower()):
            lines += _deprecated_row(item, dep, namespace, tags, meta)
        lines.append("")
    with open(os.path.join(dstpath, "deprecated.rst"), "w", encoding="utf-8") as f:
        f.write("\n".join(lines))
    return True

"""
    Inject the "Introduced in Level Zero version X.Y" note just after an extension
    page's title block (overline/title/underline).
"""
def _inject_ext_version(fout, text, version, deprecated_rst=""):
    m = re.search(r'^={3,}[ \t]*\n.+\n={3,}[ \t]*\n', text, re.M)
    if not m:
        return
    note = "\n.. rst-class:: ext-version\n\n*Introduced in Level Zero version %s*\n" % version
    if deprecated_rst:
        note += "\n.. rst-class:: api-deprecated\n\n%s\n" % deprecated_rst
    text = text[:m.end()] + note + text[m.end():]
    with open(fout, "w", encoding="utf-8", newline="\n") as f:
        f.write(text)

"""
Entry-point:
    generate restructuredtext documents from templates
"""
def generate_rst(docpath, section, namespace, tags, ver, rev, specs, meta, others=()):
    srcpath = os.path.join("./", section)
    dstpath = os.path.join(docpath, "source", section)

    loc = 0
    util.makePath(dstpath)
    util.removeFiles(dstpath, "*.rst")
    enum_ver, struct_ver = _extension_version_maps(specs, namespace, tags)
    dep_map = _extension_deprecation_map(specs, namespace, tags)
    ext_names = _extension_name_map(specs, namespace, tags)
    ext_deps = []
    for fin in util.findFiles(srcpath, "*.rst"):
        fout = os.path.join(dstpath, os.path.basename(fin))
        loc += _generate_valid_rst(os.path.abspath(fin), fout, namespace, tags, ver, rev, meta)

        # Extension doc pages (EXT_*/EXT_Exp_*): stamp the introduced spec version at
        # the top. Every such page MUST resolve a version by referencing its version
        # enum (or an ext/exp struct); a page that cannot is a spec bug -> build error.
        if os.path.basename(fin).startswith("EXT_"):
            with open(fout, encoding="utf-8") as f:
                _text = f.read()
            _v = _extension_intro_version(_text, enum_ver, struct_ver)
            if _v:
                _obj, _dep = _extension_deprecation(_text, enum_ver, struct_ver, dep_map)
                if _dep:
                    _doc = os.path.splitext(os.path.basename(fin))[0]
                    ext_deps.append((_doc, ext_names.get(_obj, _doc), _dep))
                _inject_ext_version(fout, _text, _v, th.make_deprecated_rst(
                    namespace, tags, {'deprecated': _dep}, meta) if _dep else "")
            else:
                util.makeError("%s : extension page has no resolvable version -- it "
                               "must reference its *_version_t enum (in an Enumerations "
                               "list) so the introduced version can be shown"
                               % os.path.basename(fin))

    print("Generated %s lines of reStructuredText (rst).\n"%loc)

    # Collect enum values added later than their enum (for the "(since vX)" note the
    # XML post-process injects). Accumulates across the per-section generate_rst calls,
    # and is persisted so a separate --html invocation (CI) can reload it.
    _collect_etor_since(specs, meta, namespace, tags)
    util.jsonWrite(os.path.join(docpath, "source", _ETOR_SINCE_FILENAME), _ETOR_SINCE)

    if (loc > 0):
        groupname = os.path.basename(dstpath).capitalize()

        # Split the API reference into maturity tiers (APIs / Extensions /
        # Experimental), each grouped by class/family and nested under the section.
        # Extension/experimental content (and its data types) is cordoned out of the
        # core reference, matching the "load the extension before use" contract.
        apipath = os.path.join(dstpath, "api")
        util.removePath(apipath)
        util.makePath(apipath)

        usage = _build_usage_rst(specs, namespace, tags, dstpath, others)
        tier_entries = []
        for tier in _build_tiers(specs, meta, namespace, tags):
            tierpath = os.path.join(apipath, tier['dir'])
            util.makePath(tierpath)
            for page in tier['pages']:
                util.makoWrite(
                    os.path.join("templates", "api_spec.mako"),
                    os.path.join(tierpath, page['slug'] + ".rst"),
                    ver=ver,
                    rev=rev,
                    tags=tags,
                    namespace=namespace,
                    meta=meta,
                    title=page['title'],
                    heading_prefix=page['heading_prefix'],
                    objects=page['objects'],
                    paginator=page['paginator'],
                    hidden_toctree=page['hidden_toctree'],
                    usage=usage)
            # Build the "In this class" sidebar TOC for EVERY class (keyed by Sphinx
            # pagename): the full function/enum/struct index for the class. For
            # paginated classes it spans all pages with cross-page links; for
            # single-page classes it is simply that page's contents. Loaded by conf.py
            # into html_context and rendered by _templates/class-toc.html.
            by_class = {}
            for page in tier['pages']:
                by_class.setdefault(page['class_key'], []).append(page)
            for group in by_class.values():
                for page in group:
                    docname = "%s/api/%s/%s" % (section, tier['dir'], page['slug'])
                    _CLASS_TOC_MAP[docname] = _class_toc_html(group, page['slug'], namespace, tags)
            # tier landing page: toctree of its class/family pages (page 1 of each
            # class only; paginated overflow pages are orphan, reached via the pager).
            # Use the short class title as explicit toctree text so the nav stays
            # uncluttered even though the page's own H1 carries the tier suffix.
            util.makoWrite(
                os.path.join("templates", "api_listing.mako"),
                os.path.join(tierpath, "index.rst"),
                ver=ver,
                rev=rev,
                title=tier['title'],
                entries=["%s <%s>" % (p['nav_label'], p['slug'])
                         for p in tier['pages'] if p['in_toc']],
                maxdepth=1)
            tier_entries.append("api/%s/index" % tier['dir'])

        _write_deprecated_page(dstpath, groupname + " - Deprecated", ext_deps, specs,
                               namespace, tags, meta, "api/deprecated/index" in tier_entries)

        # section index: toctree of the tier landing pages
        util.makoWrite(
            os.path.join("templates", "api_listing.mako"),
            os.path.join(dstpath, "api.rst"),
            ver=ver,
            rev=rev,
            title=groupname,
            entries=tier_entries,
            maxdepth=2)

    # Persist the accumulated class-TOC map (grows across the per-section calls of
    # one build) for conf.py to load into html_context.
    util.jsonWrite(os.path.join(docpath, "source", _CLASS_TOC_FILENAME), _CLASS_TOC_MAP)


"""
Entry-point:
    generate reference JSON file
"""
def generate_ref(dstpath, ref):
    refpath = os.path.join(dstpath, "ref")
    util.removePath(refpath)
    util.makePath(refpath)

    util.jsonWrite(os.path.join(refpath, "level_zero.json"), ref)

"""
Entry-point:
    Post-process Doxygen-generated XML files
"""
def _postprocess_generated_xml(pathname='', extension='xml'):
    globby = '**/*.' + extension

    for fn in glob.iglob(os.path.join(os.path.abspath(pathname), globby), recursive=True):
        if fnmatch.fnmatch(fn, '*/_*'):
            continue
        with open(fn, "r+", encoding="utf-8") as f:
            data = f.read()
            data = data.replace("modul3", "module")

            f.seek(0)
            f.write(data)
            f.truncate()

def generate_common(dstpath, sections, ver, rev, versions_url, warnings_as_errors=True):
    htmlpath = os.path.join(dstpath, "html")
    latexpath = os.path.join(dstpath, "latex")
    xmlpath = os.path.join(dstpath, "xml")
    sourcepath = os.path.join(dstpath, "source")
    util.removePath(htmlpath)
    util.removePath(latexpath)
    util.removePath(xmlpath)
    util.makePath(xmlpath)

    # generate sphinx configuration file with version
    loc = 0
    for fn in ["conf.py", "index.rst", "api.rst", "deprecated.rst", "versions.rst"]:
        loc += util.makoWrite(
            "./templates/%s.mako" % fn,
            os.path.join(sourcepath, fn),
            ver=rev,
            sourcepath=sourcepath,
            sections=sections,
            versions_url=versions_url)

    # Doxygen generates XML files needed by sphinx breathe plugin for API documentation
    print("Generating doxygen...")
    # Drop any log from a previous run so CI can never quote stale diagnostics.
    warnlog = os.path.join(dstpath, DOXYGEN_WARNINGS_FILENAME)
    if util.exists(warnlog):
        os.remove(warnlog)

    if warnings_as_errors:
        argv, config = ["doxygen", "Doxyfile"], None
    else:
        # Doxyfile sets WARN_AS_ERROR=FAIL_ON_WARNINGS. Rather than mutate the checked-in
        # file, feed doxygen its config on stdin ('-') with an overriding line appended;
        # the last assignment wins, so warnings stay warnings.
        print("  WARNING: doc warnings-as-errors DISABLED (--!warnings_as_errors)")
        with open("Doxyfile", "r", encoding="utf-8") as fh:
            config = fh.read() + "\nWARN_AS_ERROR = NO\n"
        argv = ["doxygen", "-"]

    # Capture stderr (diagnostics only; progress goes to stdout and stays on the console)
    # so it can be echoed AND persisted for CI to quote into a PR comment.
    proc = subprocess.run(argv, input=config, text=True, stderr=subprocess.PIPE)
    diagnostics = proc.stderr or ""
    if diagnostics.strip():
        sys.stderr.write(diagnostics)
        sys.stderr.flush()
        with open(warnlog, "w", encoding="utf-8") as fh:
            fh.write(diagnostics)

    if proc.returncode > 0:
        raise Exception(
            "doxygen returned %d.\n"
            "If the output above shows \"error: ... could not be resolved\", a doc comment "
            "has an unresolvable reference -- fix the source YAML in scripts/<section>/*.yml, "
            "not the generated header.\n"
            "To reference a struct member, write '`memberName` member of $x_some_struct_t' "
            "rather than '$x_some_struct_t.memberName'.\n"
            "As a last resort, re-run with --!warnings_as_errors." % proc.returncode)

    # workaround for C++ standard keywords redefined due to missing Doxygen options to set the preferred C++ standard
    _postprocess_generated_xml(xmlpath)

"""
Entry-point:
    generate HTML files using reStructuredText (rst) and Doxygen template
"""
def generate_html(dstpath, warnings_as_errors=True):
    sourcepath = os.path.join(dstpath, "source")

    print("Generating HTML...")
    # Resolve sphinx-build from the same bin directory as the running Python
    # so it works correctly when invoked via a virtualenv (e.g. /opt/spec-venv).
    sphinx_build = os.path.join(os.path.dirname(sys.executable), "sphinx-build")
    cmdline = "%s -M html %s ../docs -j auto" % (sphinx_build, sourcepath)

    # Drop any log from a previous run so CI can never quote stale diagnostics.
    warnlog = os.path.join(dstpath, SPHINX_WARNINGS_FILENAME)
    if util.exists(warnlog):
        os.remove(warnlog)
    cmdline += " -w %s" % warnlog
    if warnings_as_errors:
        # --keep-going reports every warning, not just the first, before failing.
        cmdline += " -W --keep-going"
    else:
        print("  WARNING: sphinx warnings-as-errors DISABLED (--!warnings_as_errors)")

    print(cmdline)
    os.environ["PYTHONWARNINGS"] = "ignore"
    rc = os.waitstatus_to_exitcode(os.system(cmdline))
    os.environ.pop("PYTHONWARNINGS")
    if rc > 0:
        raise Exception(
            "sphinx-build returned %d.\n"
            "A WARNING above such as \"undefined label\" is a broken :ref: link in a page "
            "generated from scripts/<section>/*.rst -- fix the label or add the missing page.\n"
            "As a last resort, re-run with --!warnings_as_errors." % rc)

    # Annotate later-added enum values with "(since vX)" in the final HTML. Done here
    # (on pinned Breathe/Sphinx output) rather than on Doxygen's XML for cross-env parity.
    _ensure_etor_since_loaded(dstpath)
    _inject_etor_versions_html(os.path.join(dstpath, "html"))
    _retarget_api_links_html(os.path.join(dstpath, "html"))
    _badge_deprecated_html(os.path.join(dstpath, "html"))

"""
Entry-point:
    prepare doc folder for documentation
"""
def prepare(docpath, gen_rst, gen_html, ver):
    if gen_html:
        htmlpath = os.path.join(docpath, "html")
        if util.exists(htmlpath):
            util.removePath(htmlpath)

    # if generating rst then assume everything in docs is invalid and clean it.
    if gen_rst:
        if util.exists(docpath):
            util.removePath(docpath)

    docsourcepath = os.path.join(docpath, "source")
    util.copyTree("./assets/html/_static",    os.path.join(docsourcepath, "_static"))
    util.copyTree("./assets/html/_templates", os.path.join(docsourcepath, "_templates"))
    util.copyTree("./assets/images",          os.path.join(docsourcepath, "images"))
