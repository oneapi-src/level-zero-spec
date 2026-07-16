<%!
# Copyright (C) 2026 Intel Corporation
# SPDX-License-Identifier: MIT
import re
from templates import helper as th
%><%page args="paginator='', hidden_toctree=None, heading_prefix=None"/>\
<%
    # `title` and `objects` are passed in by generate_rst (one call per class/family page).
    # `title` is the page H1 (tier-qualified for ext/exp, e.g. "External Semaphore - Extensions");
    # `heading_prefix` prefixes the section headings ("External Semaphore - Extension Structures").
    # `paginator` is a prebuilt raw-HTML pager (empty for single-page classes).
    # `hidden_toctree` (page 1 of a paginated class only) lists the overflow page slugs so they
    # stay in the doc tree -- keeps the nav branch highlighted on those pages -- without appearing
    # as separate tier-index nav entries.
    n = namespace
    if heading_prefix is None:
        heading_prefix = title
    if hidden_toctree is None:
        hidden_toctree = []
    title_bar = "=" * max(60, len(title))
%>\
${title_bar}
${title}
${title_bar}
%if hidden_toctree:

.. toctree::
   :hidden:

%for entry in hidden_toctree:
   ${entry}
%endfor

%endif
oneAPI Level Zero Specification - Version ${rev}

#################################################################
## Generate API documentation
## (The old in-page links table was removed -- the "In this class"
##  right sidebar now provides the full per-class index.)
#################################################################
## -------------------------
## Functions
## -------------------------
<%isempty = True%>
%for obj in objects:
%if re.match(r"function", obj['type']) and ("condition" not in obj):
%if isempty: # only display section title if there is content.
<%heading = heading_prefix + " Functions"%>\
${heading}
${"=" * len(heading)}
<%isempty = False%>
%endif
<%fname = th.make_func_name(n, tags, obj)%>\

.. _${fname.replace("_", "-")}:

${fname}
${"-" * len(fname)}

.. rst-class:: api-version

*Added in version ${obj.get('version', '1.0')}*

.. doxygenfunction:: ${fname}
    :project: LevelZero

%endif
%endfor # obj in objects

#################################################################
## -------------------------
## Enums
## -------------------------
<%isempty = True%>
%for obj in objects:
%if re.match(r"enum", obj['type']):
%if isempty: # only display section title if there is content.
<%heading = heading_prefix + " Enums"%>\
${heading}
${"=" * len(heading)}
<%isempty = False%>
%endif
<%tname = th.make_type_name(n, tags, obj)%>\

.. _${tname.replace("_", "-")}:

${tname}
${"-" * len(tname)}

.. rst-class:: api-version

*Added in version ${obj.get('version', '1.0')}*

.. doxygenenum:: ${th.make_enum_name(n, tags, obj)}
    :project: LevelZero

%endif
%endfor # obj in objects
#################################################################
## -------------------------
## Structs/Unions
## -------------------------
 <%isempty = True%>
%for obj in objects:
%if re.match(r"struct|union", obj['type']):
%if isempty: # only display section title if there is content.
<%heading = heading_prefix + " Structures"%>\
${heading}
${"=" * len(heading)}
<%isempty = False%>
%endif
<%tname = th.make_type_name(n, tags, obj)%>\

.. _${tname.replace("_", "-")}:

${tname}
${"-" * len(tname)}

.. rst-class:: api-version

*Added in version ${obj.get('version', '1.0')}*

%if re.match(r"struct", obj['type']):
.. doxygenstruct:: ${tname}
    :project: LevelZero
    :members:
    :undoc-members:
%endif
%if re.match(r"union", obj['type']):
.. doxygenunion:: ${tname}
    :project: LevelZero
%endif

%endif
%endfor # obj in objects
#################################################################
## Bottom paginator (only when the class spans multiple pages)
#################################################################
%if paginator:

.. raw:: html

   ${paginator}
%endif
