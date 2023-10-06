<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
    s=tags['$s']
    S=s.upper()
%>
:orphan:

.. _ZES_extension_mem_state:

========================
 Memory State Extension
========================

API
----
* Enumerations

    * ${s}_mem_page_offline_state_exp_version_t
   
* Structures

    * ${s}_mem_page_offline_state_exp_t
   
Memory State
~~~~~~~~~~~~~~~~~~

This extension extends the functionality provided by the ${s}MemoryGetState in the Sysman API. Additional MemoryOffline metrics are added to this extension.