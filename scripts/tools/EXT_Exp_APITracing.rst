<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
    t=tags['$t']
    T=t.upper()
%>
:orphan:

.. _ZET_experimental_api_tracing:

=========================
 API Tracing Extension
=========================

API
----

* Functions


    * ${t}TracerExpCreate
    * ${t}TracerExpDestroy
    * ${t}TracerExpSetPrologues
    * ${t}TracerExpSetEpilogues
    * ${t}TracerExpSetEnabled

 
* Enumerations


    * ${t}_api_tracing_exp_version_t

 
* Structures


    * ${t}_tracer_exp_desc_t

