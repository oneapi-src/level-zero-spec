<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
:orphan:

.. _ZE_extension_driver_ddi_handles:

==========================================
 Driver Direct Device Interface (DDI) Handles Extension
==========================================

API
----

* Enumerations
    * ${x}_driver_ddi_handles_ext_version_t

* Structures
    * ${x}_driver_ddi_handle_ext_flags_t
    * ${x}_driver_ddi_handles_ext_properties_t
    * ze_handle_t
    * ze_dditable_driver_t
    * zet_dditable_driver_t
    * zes_dditable_driver_t

See `ze*_ddi.h` for definitions of `ze_dditable_driver_t`, `zet_dditable_driver_t`, `zes_dditable_driver_t`.
`ze_handle_t` is defined in ze_ddi_common.h. To use it, include `ze_ddi_common.h`.

Handle Structures:
~~~~~~~~~~~~~~~~~

    /// @brief Handle with pointer to Dispatch Container allocated by the driver at the beginning of every L0 Core handle
    typedef struct _ze_handle_t
    {
        ze_dditable_driver_t *pCore; // [in] pointer to _ze_dditable_t_ object related to this handle
        zet_dditable_driver_t *pTools; // [in] pointer to _zet_dditable_t_ object related to this handle
        zes_dditable_driver_t *pSysman; // [in] pointer to _zes_dditable_t_ object related to this handle
    } ze_handle_t;

DDI Handles Extension:
~~~~~~~~~~~~~~~~~~~~~

Nowadays there are many possible scenarios of multiple Level Zero runtimes in the system (GPU + NPU, dGPU + iGPU on Windows, mainstream GPU + legacy GPU on Linux).
Our current handling of multi runtime scenario in Loader has many issues:
  - performance degradation
  - Level Zero API handles are stored in per-type maps, accessing these maps costs, especially in hot paths
  - putting and removing entries from map needs additional mutex to ensure thread-safety
  - there is significant perfomance difference between runing application when there is only one runtime active and many runtimes active, even if only one is really used by application.
    As initialization overhead is acceptable, any further API calls should not cause performance degradation. E.g. when running [`SetKernelArgSvmPointer`](https://github.com/intel/compute-benchmarks/blob/master/source/benchmarks/api_overhead_benchmark/implementations/l0/set_kernel_arg_svm_pointer_l0.cpp) test from [`api_overhead_benchmark`](https://github.com/intel/compute-benchmarks/tree/master/source/benchmarks/api_overhead_benchmark) there is degradation from 0.817us to 2.724us caused only by presence of second runtime on the system.
  - when using driver extensions, application bypasses Level Zero loader and calls runtime functions directly
  - handles that application got from loader is wrapped by loader's handle type and can't be passed to runtime directly, therefore translation is required;
    translation could be applied on two sides - app side / runtime side. How to detect double translation?
  - extension may create ze_event_t object that can be then used in core API - loader cannot recognize it

The solution which solves this problem is to define a base layout of every handle type directly in L0 spec ensuring that all L0 API handles contain a header with pointers to appropriate driver ddi tables.
Backward compatibility is covered as new loader will still support runtimes that do not support this extension.
Loader should verify the support based on extension property queried from zeDriverGetExtensionProperties.

Example Implementation of L0 Loader functions:
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. parsed-literal::
    ZE_APIEXPORT ze_result_t ZE_APICALL zeContextCreate(
        ze_driver_handle_t hDriver,
        const ze_context_desc_t *desc,
        ze_context_handle_t *phContext) {
        return hDriver->pCore->pContext->pfnCreate(hDriver, desc, phContext);
    }