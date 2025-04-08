<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>

<%!
    from parse_specs import _version_compare_gequal
%>

:orphan:

.. _ZE_experimental_image_view_planar:

=============================
 Image View Planar Extension
=============================

This experimental extension is deprecated since version 1.5 onwards and replaced by the :ref:`${th.subt(namespace, tags, X)}_extension_image_view_planar <${th.subt(namespace, tags, X)}_extension_image_view_planar>` standard extension.

API
----

* Enumerations


    * ${x}_image_view_planar_exp_version_t

 
* Structures


    * ${x}_image_view_planar_exp_desc_t


