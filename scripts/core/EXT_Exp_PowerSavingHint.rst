<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_experimental_power_saving_hint:

This experimental extension is deprecated since version 1.18 onwards and replaced by the :ref:`${th.subt(namespace, tags, X)}_extension_power_saving_hint <${th.subt(namespace, tags, X)}_extension_power_saving_hint>` standard extension.

============================
 Power Saving Hint Extension
============================

API
----

* Enumerations

    * ${x}_power_saving_hint_exp_version_t

 
* Structures


    * ${x}_context_power_saving_hint_exp_desc_t
