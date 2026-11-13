============================================================
External Semaphore - Extensions
============================================================
oneAPI Level Zero Specification - Version 1.21.26


External Semaphore - Extension Handles
======================================


.. _ze-external-semaphore-ext-handle-t:

ze_external_semaphore_ext_handle_t
----------------------------------

.. rst-class:: api-version

*Added in version 1.12*

.. container:: api-usage

   | **Obtained from:** :ref:`zeDeviceImportExternalSemaphoreExt`
   | **Used by:** :ref:`zeDeviceReleaseExternalSemaphoreExt`, :ref:`zeCommandListAppendSignalExternalSemaphoreExt`, :ref:`zeCommandListAppendWaitExternalSemaphoreExt`, :ref:`zeCommandQueueSignalExternalSemaphoreExt`, :ref:`zeCommandQueueWaitExternalSemaphoreExt`
   | **See also:** :doc:`../../EXT_ExternalSemaphores`

.. cpp:type:: ze_external_semaphore_ext_handle_t

    Handle of external semaphore object.






 
External Semaphore - Extension Structures
=========================================


.. _ze-external-semaphore-ext-desc-t:

ze_external_semaphore_ext_desc_t
--------------------------------

.. rst-class:: api-version

*Added in version 1.12*

.. container:: api-usage

   | **Used by:** :ref:`zeDeviceImportExternalSemaphoreExt`
   | **pNext may point to:** :ref:`ze-external-semaphore-win32-ext-desc-t`, :ref:`ze-external-semaphore-fd-ext-desc-t`

.. doxygenstruct:: ze_external_semaphore_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-external-semaphore-win32-ext-desc-t:

ze_external_semaphore_win32_ext_desc_t
--------------------------------------

.. rst-class:: api-version

*Added in version 1.12*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-external-semaphore-ext-desc-t`

.. doxygenstruct:: ze_external_semaphore_win32_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-external-semaphore-fd-ext-desc-t:

ze_external_semaphore_fd_ext_desc_t
-----------------------------------

.. rst-class:: api-version

*Added in version 1.12*

.. container:: api-usage

   | **Goes in pNext of:** :ref:`ze-external-semaphore-ext-desc-t`

.. doxygenstruct:: ze_external_semaphore_fd_ext_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-external-semaphore-signal-params-ext-t:

ze_external_semaphore_signal_params_ext_t
-----------------------------------------

.. rst-class:: api-version

*Added in version 1.12*

.. container:: api-usage

   | **Used by:** :ref:`zeCommandListAppendSignalExternalSemaphoreExt`, :ref:`zeCommandQueueSignalExternalSemaphoreExt`

.. doxygenstruct:: ze_external_semaphore_signal_params_ext_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-external-semaphore-wait-params-ext-t:

ze_external_semaphore_wait_params_ext_t
---------------------------------------

.. rst-class:: api-version

*Added in version 1.12*

.. container:: api-usage

   | **Used by:** :ref:`zeCommandListAppendWaitExternalSemaphoreExt`, :ref:`zeCommandQueueWaitExternalSemaphoreExt`

.. doxygenstruct:: ze_external_semaphore_wait_params_ext_t
    :project: LevelZero
    :members:
    :undoc-members:

