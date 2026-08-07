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
from parse_specs import _version_compare_less, _version_compare_equal, _version_compare_greater, _version_compare_lequal, _version_compare_gequal
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
    if not re.match(r"function|struct|union|enum|etor", symbol_type):
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
                        # ignore reference links for specific types that have no API documentation for them
                        if not re.match(r"env|handle|typedef|macro", symbol_type):
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
RE_API_OBJ_TYPE = r"function|enum|struct|union"

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
          ("exp", "experimental", "Experimental", "Experimental")]

"""
    per-object maturity derived from its name: 'exp' (experimental), 'ext' (stable
    extension), or 'base'. Uses the reliable object-name signal (Exp/Ext suffix on
    functions, _exp_/_ext_ on type names) rather than the header desc (whose parse
    regex is anchored/broken -- see TODO.md). Base files are internally mixed
    (device.yml = base + ext), so maturity MUST be per-object, not per-file.
"""
def _obj_maturity(obj):
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
        if re.match(r"enum|struct|union", t):
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
    groups = [("Functions", r"function"),
              ("Enumerations", r"enum"),
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

        # Paginate functions only; enums/structs land on the class's final page.
        groups = [funcs[i:i + _MAX_FUNCS_PER_PAGE]
                  for i in range(0, len(funcs), _MAX_FUNCS_PER_PAGE)] or [[]]
        groups[-1] = groups[-1] + enums + structs

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
    buckets = {"base": {}, "ext": {}, "exp": {}}
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
    Resolve an extension page's introduced spec version:
      1. the version enum it references (authoritative), else
      2. the earliest structure_type-etor version among its ext/exp structs, else None.
    Tokens appear either underscored (prose/code) or hyphenated (`:ref:` targets).
    A None result is a spec bug -- every extension must define & reference a version
    enum (generate_rst turns None into a build error, no manual override).
"""
def _extension_intro_version(text, enum_ver, struct_ver):
    def refd(name):
        return name in text or name.replace('_', '-') in text
    for table in (enum_ver, struct_ver):
        hits = [v for n, v in table.items() if refd(n)]
        if hits:
            return min(hits, key=th.version_key)
    return None

"""
    Inject the "Introduced in Level Zero version X.Y" note just after an extension
    page's title block (overline/title/underline).
"""
def _inject_ext_version(fout, text, version):
    m = re.search(r'^={3,}[ \t]*\n.+\n={3,}[ \t]*\n', text, re.M)
    if not m:
        return
    note = "\n.. rst-class:: ext-version\n\n*Introduced in Level Zero version %s*\n" % version
    text = text[:m.end()] + note + text[m.end():]
    with open(fout, "w", encoding="utf-8") as f:
        f.write(text)

"""
Entry-point:
    generate restructuredtext documents from templates
"""
def generate_rst(docpath, section, namespace, tags, ver, rev, specs, meta):
    srcpath = os.path.join("./", section)
    dstpath = os.path.join(docpath, "source", section)

    loc = 0
    util.makePath(dstpath)
    util.removeFiles(dstpath, "*.rst")
    enum_ver, struct_ver = _extension_version_maps(specs, namespace, tags)
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
                _inject_ext_version(fout, _text, _v)
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
                    hidden_toctree=page['hidden_toctree'])
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
    for fn in ["conf.py", "index.rst", "api.rst", "versions.rst"]:
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
        with open("Doxyfile", "r") as fh:
            config = fh.read() + "\nWARN_AS_ERROR = NO\n"
        argv = ["doxygen", "-"]

    # Capture stderr (diagnostics only; progress goes to stdout and stays on the console)
    # so it can be echoed AND persisted for CI to quote into a PR comment.
    proc = subprocess.run(argv, input=config, text=True, stderr=subprocess.PIPE)
    diagnostics = proc.stderr or ""
    if diagnostics.strip():
        sys.stderr.write(diagnostics)
        sys.stderr.flush()
        with open(warnlog, "w") as fh:
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
def generate_html(dstpath):
    sourcepath = os.path.join(dstpath, "source")

    print("Generating HTML...")
    # Resolve sphinx-build from the same bin directory as the running Python
    # so it works correctly when invoked via a virtualenv (e.g. /opt/spec-venv).
    sphinx_build = os.path.join(os.path.dirname(sys.executable), "sphinx-build")
    cmdline = "%s -M html %s ../docs -j auto" % (sphinx_build, sourcepath)
    print(cmdline)
    os.environ["PYTHONWARNINGS"] = "ignore"
    rc = os.waitstatus_to_exitcode(os.system(cmdline))
    os.environ.pop("PYTHONWARNINGS")
    if rc > 0:
        raise Exception("sphinx-build returned %d"%rc)

    # Annotate later-added enum values with "(since vX)" in the final HTML. Done here
    # (on pinned Breathe/Sphinx output) rather than on Doxygen's XML for cross-env parity.
    _ensure_etor_since_loaded(dstpath)
    _inject_etor_versions_html(os.path.join(dstpath, "html"))

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
