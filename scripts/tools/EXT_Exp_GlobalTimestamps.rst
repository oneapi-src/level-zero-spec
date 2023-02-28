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

.. _ZET_experimental_global_metric_timestamps:

==========================================
Global Metrics Timestamps Extension
==========================================

API
----

* Structures

    * ${t}_metric_global_timestamps_resolution_exp_t

* Functions

    * ${t}MetricGroupGetGlobalTimestampsExp