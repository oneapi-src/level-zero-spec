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

This feature helps to prevent flashing of older firmware that have certain security vulnerabilities by using an hardware enforced anti-rollback scheme. 
User can flash a firmware image and sets its version as the security version number (SVN). Images with lower SVN cannot be applied to device with 
higher SVN for security considerations.

.. parsed-literal::

    // Fetch current security version from the fuses
    char* version = allocate(version_size);
    ${s}FirmwareGetSecurityVersionExp(hFirmware, version);

    // Set security version
    ${s}FirmwareSetSecurityVersionExp(hFirmware);
