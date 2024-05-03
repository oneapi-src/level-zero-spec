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

.. _ZE_experimental_image_view:

=========================
 Image View Extension
=========================

%if _version_compare_gequal(ver, "1.5"):
This experimental extension is deprecated and replaced by the :ref:`${th.subt(namespace, tags, X)}_extension_image_view <${th.subt(namespace, tags, X)}_extension_image_view>` standard extension.
%endif

API
----

* Functions


    * ${x}ImageViewCreateExp

 
* Enumerations


    * ${x}_image_view_exp_version_t

