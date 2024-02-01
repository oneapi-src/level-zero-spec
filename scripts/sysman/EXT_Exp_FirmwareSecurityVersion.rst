<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    s=tags['$s']
    S=s.upper()
%>
:orphan:

.. _ZES_experimental_firmware_security_version:

===========================
 Firmware Security Version
===========================

API
----

* Functions

    * ${s}FirmwareGetSecurityVersionExp
    * ${s}FirmwareSetSecurityVersionExp

* Enumerations

    * ${s}_firmware_security_exp_version_t

Security Version
~~~~~~~~~~~~~~~~
