
:orphan:

.. _ZE_extension_virtual_mem_readonly_properties:

================================================
 Virtual Memory Read-Only Properties Extension
================================================

API
----

* Enumerations

    * :ref:`ze-virtual-mem-readonly-properties-ext-version-t`
    * :ref:`ze-device-readonly-memory-capability-t`

* Structures

    * :ref:`ze-device-readonly-memory-ext-properties-t`

Virtual Memory Read-Only Properties
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

'oneAPI' Level-Zero provides the :ref:`ZE_MEMORY_ACCESS_ATTRIBUTE_READONLY <ze-memory-access-attribute-t>` attribute
for virtual memory page mappings via :ref:`zeVirtualMemSetAccessAttribute`\. However,
the actual behavior when this attribute is applied varies across drivers and hardware.

This extension introduces the :ref:`ze-device-readonly-memory-ext-properties-t` struct,
which can be chained via the ``pNext`` member of :ref:`ze-device-properties-t` to query
the read-only capability supported by the device.

The ``readonlyCapability`` field reports one of the following values:

- ``:ref:`ZE_DEVICE_READONLY_MEMORY_CAPABILITY_NONE <ze-device-readonly-memory-capability-t>`\``: The read-only attribute has no effect.
- ``:ref:`ZE_DEVICE_READONLY_MEMORY_CAPABILITY_HINT <ze-device-readonly-memory-capability-t>`\``: The read-only attribute is forwarded to the OS as a performance hint.
- ``:ref:`ZE_DEVICE_READONLY_MEMORY_CAPABILITY_ENFORCED <ze-device-readonly-memory-capability-t>`\``: The read-only attribute is hardware-enforced.

The following pseudo-code demonstrates how to query the read-only memory capability:

.. parsed-literal::

       // Query device properties with read-only memory capability extension
       :ref:`ze-device-readonly-memory-ext-properties-t` roProps = {};
       roProps.stype = :ref:`ZE_STRUCTURE_TYPE_DEVICE_READONLY_MEMORY_EXT_PROPERTIES <ze-structure-type-t>`\;
       roProps.pNext = nullptr;

       :ref:`ze-device-properties-t` devProps = {};
       devProps.stype = :ref:`ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES_1_2 <ze-structure-type-t>`\; // :ref:`ZE_STRUCTURE_TYPE_DEVICE_PROPERTIES <ze-structure-type-t>` deprecated since 1.17
       devProps.pNext = &roProps;

       :ref:`zeDeviceGetProperties`\(hDevice, &devProps);

       if (roProps.readonlyCapability == :ref:`ZE_DEVICE_READONLY_MEMORY_CAPABILITY_ENFORCED <ze-device-readonly-memory-capability-t>`\) {
           // Hardware enforces read-only; writes will fault
       } else if (roProps.readonlyCapability == :ref:`ZE_DEVICE_READONLY_MEMORY_CAPABILITY_HINT <ze-device-readonly-memory-capability-t>`\) {
           // Read-only is a hint; writes may still succeed
       } else {
           // No read-only support; attribute has no effect
       }
