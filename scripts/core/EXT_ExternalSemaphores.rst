<%
import re
from templates import helper as th
%><%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
    s=tags['$s']
    S=s.upper()
%>
:orphan:

.. _ZE_external_semaphores:

=============================================
 External Semaphores Extension Specification
=============================================

API
----

* Functions

    * ${x}DeviceImportExternalSemaphoreExt
    * ${x}DeviceReleaseExternalSemaphoreExt
    * ${x}CommandListAppendSignalExternalSemaphoreExt
    * ${x}CommandListAppendWaitExternalSemaphoreExt

* Enumerations

    * ${x}_external_semaphore_ext_version_t
    * ${x}_external_semaphore_ext_flags_t

* Structures

    * ${x}_external_semaphore_ext_desc_t
    * ${x}_external_semaphore_win32_ext_desc_t
    * ${x}_external_semaphore_fd_ext_desc_t
    * ${x}_external_semaphore_signal_params_ext_t
    * ${x}_external_semaphore_wait_params_ext_t

External Semaphores
~~~~~~~~~~~~~~~~~~~
Currently L0 supports importing external buffers and images from other graphics APIs such as DX12 and Vulkan, but does not support importing external semaphores.
The only solution that exists is to do synchronization at the host level, which may not be applicable for interop
with a fullying asynchronous rendering pipeline. Therefore, we need a new API that will accept the external semaphores
from other graphics APIs for synchronization to support interoperability. To this end, this extension introduces
APIs to import external semaphores, to append wait/signal using semaphores in the command list, and to release imported external semaphores.

Semantics and Behavior model
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. The semaphore signal command waits for a list of events to complete and then signals a list of semaphore objects.
2. The semaphore wait command waits for a list of events to complete and waits on a list of semaphore objects.
3. phWaitEvents points to the list of events that need to complete before ${x}CommandListAppendSignalExternalSemaphoreExt or ${x}CommandListAppendWaitExternalSemaphoreExt can be executed. If phWaitEvents is NULL, then the command does not wait on any event to complete.
4. Signal/Wait on the semaphore are async non blocking operation which doesn't cause serialization within a queue.
5. Application must perform semaphore signal and waits in alternate manner and order producer first. Repetitive signals and wait on same semaphore object is not supported.
6. The semaphore objects are currently only allowed to be imported into L0 and therefore the semaphore semantics/definitions of the exporter API needs to be honoured by the application.
7. Resetting semaphore object needs to be handled by the exporter as L0 capabilities are only to import and perform operations on the semaphore object itself.
8. ${x}CommandListAppendSignalExternalSemaphoreExt and ${x}CommandListAppendWaitExternalSemaphoreExt calls must only be executed on an immediate commandlist.

Following pseudo-code demonstrates a sequence for importing external semaphore from Vulkan and using it in L0:

..parsed-literal::
    // Import external semaphore from Vulkan
    VkSemaphore vkSemaphore = ...;  // Create Vulkan semaphores
    void *vkSemHandle = ...; //export VK semaphore

    ${x}_external_semaphore_win32_ext_desc_t win32Desc = {};
    win32Desc.handle = vkSemHandle;
    ${x}_external_semaphore_ext_desc_t desc = {${X}_STRUCTURE_TYPE_EXTERNAL_SEMAPHORE_EXT_DESC, &win32Desc, ${X}_EXTERNAL_SEMAPHORE_EXT_FLAG_OPAQUE_WIN32};

    ${x}_external_semaphore_ext_handle_t semaphore0 = nullptr;
    ${x}DeviceImportExternalSemaphoreExt(device, &semaphore0, &desc);

    // Create command list and command queue
    ${x}_command_list_handle_t commandList = ...;
    ${x}_command_queue_handle_t commandQueue = ...;

    // Append wait on external semaphore in the command list and then launch kernel
    ${x}_external_semaphore_wait_params_ext_t waitParams = {};
    waitParams.pNext = nullptr;
    ${x}CommandListAppendWaitExternalSemaphoreExt(commandList, &semaphore0, &waitParams, 1, event0, 0, nullptr);
    ${x}CommandListAppendLaunchKernel(commandList, kernel, ..., event1, 1, &event0);

    // Append signal on external semaphore in the command after completion of kernel execution
    ${x}_external_semaphore_signal_params_ext_t signalParams = {};
    signalParams.pNext = nullptr;
    ${x}CommandListAppendLaunchKernel(commandList, kernel, ..., event2, 0, nullptr);
    ${x}CommandListAppendSignalExternalSemaphoreExt(commandList, &semaphore0, &signalParams, 1, event3, 1, &event2); 