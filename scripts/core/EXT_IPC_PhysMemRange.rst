<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_ipc_phys_mem_handle_range:

====================================================
 IPC Physical Memory Range Extension
====================================================

API
----

* Enumerations

    * ${x}_ipc_phys_mem_handle_range_ext_version_t

* Structures

    * ${x}_ipc_phys_mem_handle_range_ext_desc_t

* Functions *(no new functions — extends existing* ${x}MemGetIpcHandleWithProperties *)*

Overview
--------

When a virtual address range is backed by multiple physical memory objects
(${x}PhysicalMemCreate) mapped via
${x}VirtualMemMap, there is no single allocation base pointer that ${x}MemGetIpcHandle
can accept to represent the whole range. This extension solves that by allowing the caller to
specify a VA range using a new descriptor passed via the ``pNext`` argument of
${x}MemGetIpcHandleWithProperties. The driver enumerates all physical handles mapped to the
range and encodes them into a single IPC handle. On the importer side, the unchanged
${x}MemOpenIpcHandle detects the range-encoded handle and maps all physical objects into a
fresh contiguous VA reservation.

Checking Extension Support
~~~~~~~~~~~~~~~~~~~~~~~~~~

Query extension support via ${x}DriverGetExtensionProperties before use:

.. parsed-literal::

    uint32_t count = 0;
    ${x}DriverGetExtensionProperties(hDriver, &count, NULL);

    ${x}_driver_extension_properties_t* props =
        malloc(count * sizeof(${x}_driver_extension_properties_t));
    ${x}DriverGetExtensionProperties(hDriver, &count, props);

    bool supported = false;
    for (uint32_t i = 0; i < count; i++) {
        if (strcmp(props[i].name, ${X}_IPC_PHYS_MEM_HANDLE_RANGE_EXT_NAME) == 0) {
            supported = true;
            break;
        }
    }
    free(props);

Export-Side Usage
~~~~~~~~~~~~~~~~~

Pass a ${x}_ipc_phys_mem_handle_range_ext_desc_t as the ``pNext`` argument of
${x}MemGetIpcHandleWithProperties. The ``ptr`` argument is the base VA of the range.

.. parsed-literal::

    ${x}_ipc_phys_mem_handle_range_ext_desc_t rangeDesc = {
        .stype = ${X}_STRUCTURE_TYPE_IPC_PHYS_MEM_HANDLE_RANGE_EXT_DESC,
        .pNext = NULL,
        .size  = totalSize
    };

    ${x}_ipc_mem_handle_t ipcHandle;
    ${x}MemGetIpcHandleWithProperties(hContext, baseVA, &rangeDesc, &ipcHandle);

    // Transmit ipcHandle to the importer process via any IPC channel.

Range Requirements and Error Behavior
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The exported range is a **static snapshot** of the physical objects mapped along
``[ptr, ptr+size)`` at the time of the call. The following requirements apply on the
export path:

* **Fully mapped range.** Every page in ``[ptr, ptr+size)`` must be mapped to a physical
  memory object. Because the importer is guaranteed a single contiguous range, unmapped
  holes cannot be represented. If the driver encounters an unmapped sub-region while
  walking the range, ${x}MemGetIpcHandleWithProperties fails with
  ``ZE_RESULT_ERROR_ADDRESS_NOT_FOUND``. For example, reserving 100 MB but mapping only the
  first 50 MB and then requesting an export of the full 100 MB fails; only the mapped
  ``[ptr, ptr+50 MB)`` sub-range may be exported.

* **Contiguous VA, any number of reservations.** The range may span more than one region
  created by ${x}VirtualMemReserve. The underlying reservations are not significant — what
  is captured is the ordered set of physical objects encountered along the contiguous VA
  range.

* **Reserved VA + physical memory only.** This extension is supported only for ranges
  backed by virtual reservations (${x}VirtualMemReserve) mapped to physical memory objects
  (${x}VirtualMemMap). Device, host, and shared USM pointers (from ${x}MemAllocDevice,
  ${x}MemAllocHost, and ${x}MemAllocShared) are not supported and will not be grouped into a
  range handle. If ``[ptr, ptr+size)`` includes any standard VA rather than a reserved
  VA, ${x}MemGetIpcHandleWithProperties fails with ``ZE_RESULT_ERROR_INVALID_ARGUMENT``.

* **Partial / offset ranges.** ``ptr`` may begin at an arbitrary offset within a larger
  mapped range, and ``size`` may select a subset of it, provided the requested window is
  itself fully and contiguously mapped.

* **Per-object mapping offsets are preserved.** An individual physical object along the
  range need not be mapped starting at its own offset zero — ${x}VirtualMemMap may have
  mapped it at a non-zero offset into the physical object. The export captures the offset
  at which each physical object was mapped, and the importer reproduces each mapping at
  that same offset in the new allocation, so the importer views exactly the same memory
  as the exporter.

The export call returns:

.. list-table::
   :header-rows: 1
   :widths: 45 55

   * - Result
     - Condition
   * - ``ZE_RESULT_ERROR_ADDRESS_NOT_FOUND``
     - Any sub-region within ``[ptr, ptr+size)`` is not mapped to a physical object.
   * - ``ZE_RESULT_ERROR_INVALID_SIZE``
     - ``rangeDesc.size`` is 0.
   * - ``ZE_RESULT_ERROR_UNSUPPORTED_SIZE``
     - The driver cannot accommodate the range; e.g. the number of physical objects encoded exceeds what the implementation can store.
   * - ``ZE_RESULT_ERROR_INVALID_NULL_POINTER``
     - ``ptr`` is ``NULL``.
   * - ``ZE_RESULT_ERROR_INVALID_ARGUMENT``
     - ``[ptr, ptr+size)`` includes a device, host, or shared USM allocation rather than reserved VA mapped to physical memory.
   * - ``ZE_RESULT_ERROR_UNSUPPORTED_FEATURE``
     - The driver or device does not support ``${X}_IPC_PHYS_MEM_HANDLE_RANGE_EXT_NAME``.

.. note::

    There is no application-visible limit on the number of physical objects a range may
    encode. The IPC handle is opaque: applications must not assume the encoded objects are
    stored inline within the ``${x}_ipc_mem_handle_t`` structure, and the driver's
    representation is not bound by that structure's size. If the driver cannot accommodate a
    given range, the export fails with ``ZE_RESULT_ERROR_UNSUPPORTED_SIZE`` rather than
    silently truncating.

.. note::

    Exports do not track subsequent growth. Physical memory mapped into, unmapped from, or
    grown beyond the exporter's VA range after the export call is **not** reflected in a
    previously exported handle or in any already-open importer view. Sharing additional
    mappings requires a new export. This is intentional so that the imported layout
    remains stable.

Import-Side Usage
~~~~~~~~~~~~~~~~~

Call the unchanged ${x}MemOpenIpcHandle. The driver maps all encoded physical objects into
a contiguous VA and returns its base.

.. parsed-literal::

    void* importedBase = NULL;
    ${x}MemOpenIpcHandle(hContext, hDevice, ipcHandle, 0, &importedBase);

    // importedBase covers totalSize bytes, backed by the same physical objects
    // in the same order as the exporter's VA range.

    ${x}MemCloseIpcHandle(hContext, importedBase);

The import path requires no source changes to detect a range-encoded handle: the driver
recognizes the range representation, reserves a fresh contiguous VA of ``totalSize`` bytes,
and maps every encoded physical object into it in exporter VA order. On success
``importedBase`` addresses ``size`` bytes with no holes. When the export began at an offset
within a physical memory object, ``importedBase`` corresponds to the exporter's ``ptr``, not
to the base of the first encoded object. The importer does not need to be told ``size`` out
of band — the range handle is self-describing: ${x}MemGetAddressRange called on
``importedBase`` returns its base and full ``size``. Import fails with
``ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY`` or ``ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY`` if a
contiguous VA reservation of the required size cannot be created.

.. note::

    If the driver does not support ``${X}_IPC_PHYS_MEM_HANDLE_RANGE_EXT_NAME``, the function returns
    ``ZE_RESULT_ERROR_UNSUPPORTED_FEATURE``.

.. note::

    This extension interoperates with ``ZE_extension_ipc_mem_handle_type``.
    Both descriptors may be chained through ``pNext`` to control both the range and handle type.
