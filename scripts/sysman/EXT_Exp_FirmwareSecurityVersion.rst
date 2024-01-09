<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    s=tags['$s']
    S=s.upper()
%>
:orphan:

.. _ZES_extension_ras_state:

======================================
 Firmware security firmware version
=====================================

API
----

* Functions

    * ${s}FirmwareGetSecurityVersionExp
    * ${s}FirmwareSetSecurityVersionExp

* Enumerations

    * ${s}_firmware_security_exp_version_t

Security Version
~~~~~~~~~~~