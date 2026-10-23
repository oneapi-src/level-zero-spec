<%
## Copyright (C) 2026 Intel Corporation
## SPDX-License-Identifier: MIT
import os

# Per-section pages are written by generate_docs._write_deprecated_page during the
# rst phase; a section with nothing deprecated has no page.
pages = [s + "/deprecated.rst" for s in sections
         if os.path.exists(os.path.join(sourcepath, s, "deprecated.rst"))]
%>
============
 Deprecated
============

Deprecated items still work, but new code must not use them. Each item links to
its replacement, if one exists.

%if pages:
.. toctree::
    :maxdepth: 2

%for page in pages:
    ${page}
%endfor
%else:
Nothing is deprecated in this version.
%endif
