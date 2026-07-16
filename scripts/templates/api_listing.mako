<%!
# Copyright (C) 2026 Intel Corporation
# SPDX-License-Identifier: MIT
%>\
============================================================
${title}
============================================================
oneAPI Level Zero Specification - Version ${rev}

.. toctree::
   :maxdepth: ${maxdepth}

%for entry in entries:
   ${entry}
%endfor
