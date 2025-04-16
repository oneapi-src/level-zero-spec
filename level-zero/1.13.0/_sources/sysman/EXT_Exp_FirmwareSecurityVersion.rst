
:orphan:

.. _ZES_experimental_firmware_security_version:

===========================
 Firmware Security Version
===========================

API
----

* Functions

    * :ref:`zesFirmwareGetSecurityVersionExp`
    * :ref:`zesFirmwareSetSecurityVersionExp`

* Enumerations

    * :ref:`zes-firmware-security-exp-version-t`

Security Version
~~~~~~~~~~~~~~~~

This feature helps to prevent flashing of older firmware that have certain security vulnerabilities by using an hardware enforced anti-rollback scheme. 
User can flash a firmware image and sets its version as the security version number (SVN). Images with lower SVN cannot be applied to device with 
higher SVN for security considerations.

.. parsed-literal::

    // Fetch current security version from the fuses
    char* version = allocate(version_size);
    :ref:`zesFirmwareGetSecurityVersionExp`\(hFirmware, version);

    // Set security version
    :ref:`zesFirmwareSetSecurityVersionExp`\(hFirmware);
