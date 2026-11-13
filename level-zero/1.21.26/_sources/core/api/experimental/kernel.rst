============================================================
Kernel - Experimental
============================================================
oneAPI Level Zero Specification - Version 1.21.26




Kernel - Experimental Functions
===============================


.. _zeKernelSetGlobalOffsetExp:

zeKernelSetGlobalOffsetExp
--------------------------

.. rst-class:: api-version

*Added in version 1.1*

.. doxygenfunction:: zeKernelSetGlobalOffsetExp
    :project: LevelZero


.. _zeKernelSchedulingHintExp:

zeKernelSchedulingHintExp
-------------------------

.. rst-class:: api-version

*Added in version 1.2*

.. doxygenfunction:: zeKernelSchedulingHintExp
    :project: LevelZero


.. _zeKernelGetBinaryExp:

zeKernelGetBinaryExp
--------------------

.. rst-class:: api-version

*Added in version 1.11*

.. doxygenfunction:: zeKernelGetBinaryExp
    :project: LevelZero


.. _zeKernelGetAllocationPropertiesExp:

zeKernelGetAllocationPropertiesExp
----------------------------------

.. rst-class:: api-version

*Added in version 1.14*

.. doxygenfunction:: zeKernelGetAllocationPropertiesExp
    :project: LevelZero



Kernel - Experimental Enums
===========================


.. _ze-scheduling-hint-exp-flags-t:

ze_scheduling_hint_exp_flags_t
------------------------------

.. rst-class:: api-version

*Added in version 1.2*

.. container:: api-usage

   | **Member of:** :ref:`ze-scheduling-hint-exp-properties-t`, :ref:`ze-scheduling-hint-exp-desc-t`

.. doxygentypedef:: ze_scheduling_hint_exp_flags_t
    :project: LevelZero

.. doxygenenum:: ze_scheduling_hint_exp_flag_t
    :project: LevelZero


 
Kernel - Experimental Structures
================================


.. _ze-scheduling-hint-exp-desc-t:

ze_scheduling_hint_exp_desc_t
-----------------------------

.. rst-class:: api-version

*Added in version 1.2*

.. container:: api-usage

   | **Used by:** :ref:`zeKernelSchedulingHintExp`

.. doxygenstruct:: ze_scheduling_hint_exp_desc_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _ze-kernel-allocation-exp-properties-t:

ze_kernel_allocation_exp_properties_t
-------------------------------------

.. rst-class:: api-version

*Added in version 1.14*

.. container:: api-usage

   | **Used by:** :ref:`zeKernelGetAllocationPropertiesExp`

.. doxygenstruct:: ze_kernel_allocation_exp_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

