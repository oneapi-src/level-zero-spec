
:orphan:

.. _compiler-info-query:

=======================================================
 Compiler-Info Query
=======================================================

API
----

* Enumerations
    * :ref:`ze-device-compiler-info-t`

* Structures
    * :ref:`ze-compiler-name-version-t`

* Functions
    * :ref:`zeDeviceGetCompilerInfo`

Summary:
~~~~~~~~~~~~~~~~~~~~~~

This provides a single, compiler-scoped device query, :ref:`zeDeviceGetCompilerInfo`\. The value selected
by :ref:`ze-device-compiler-info-t` determines which compiler-info list is returned; see the enumeration
for the available selectors and their payload layout. The result uses the standard two-call
convention with a single in/out size parameter: query the size with ``pData`` null, allocate, then
call again to fill.

Example usage:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. parsed-literal::
    size_t size = 0;
    :ref:`zeDeviceGetCompilerInfo`\(hDevice, :ref:`ZE_DEVICE_COMPILER_INFO_SPIRV_CAPABILITIES <ze-device-compiler-info-t>`\, nullptr, &size, nullptr);
    std::vector<uint32_t> caps(size / sizeof(uint32_t));
    :ref:`zeDeviceGetCompilerInfo`\(hDevice, :ref:`ZE_DEVICE_COMPILER_INFO_SPIRV_CAPABILITIES <ze-device-compiler-info-t>`\, nullptr, &size, caps.data());
