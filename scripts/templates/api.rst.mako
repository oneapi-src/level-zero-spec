<%
## Copyright (C) 2026 Intel Corporation
## SPDX-License-Identifier: MIT
import os

apidocs = []
for section in sections:
    apidocs.append(section + "/api.rst")
%>
===================
 API Documentation
===================

.. toctree::
    :maxdepth: 2

%for apidoc in apidocs:
%if os.path.exists(os.path.join(sourcepath, apidoc)):
    ${apidoc}
%endif
%endfor