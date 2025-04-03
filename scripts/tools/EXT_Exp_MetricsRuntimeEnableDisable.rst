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

.. _ZET_experimental_metrics_runtime_enable_disable:


=======================================================
Metrics Runtime Enable and Disable Extension
=======================================================

API
----

* Functions

    * ${t}DeviceEnableMetricsExp
    * ${t}DeviceDisableMetricsExp
