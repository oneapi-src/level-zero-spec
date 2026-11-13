============================================================
Kernel
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Kernel Handles
==============


.. _zet-kernel-handle-t:

zet_kernel_handle_t
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zetKernelGetProfileInfo`
   | **Alias of:** :ref:`ze-kernel-handle-t`

.. cpp:type:: zet_kernel_handle_t

    Handle of function object.



Kernel Functions
================


.. _zetKernelGetProfileInfo:

zetKernelGetProfileInfo
-----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zetKernelGetProfileInfo
    :project: LevelZero



Kernel Enums
============


.. _zet-profile-flags-t:

zet_profile_flags_t
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zet-profile-properties-t`

.. doxygentypedef:: zet_profile_flags_t
    :project: LevelZero

.. doxygenenum:: zet_profile_flag_t
    :project: LevelZero


.. _zet-profile-token-type-t:

zet_profile_token_type_t
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zet-profile-free-register-token-t`

.. doxygenenum:: zet_profile_token_type_t
    :project: LevelZero


 
Kernel Structures
=================


.. _zet-profile-properties-t:

zet_profile_properties_t
------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zetKernelGetProfileInfo`

.. doxygenstruct:: zet_profile_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zet-profile-free-register-token-t:

zet_profile_free_register_token_t
---------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenstruct:: zet_profile_free_register_token_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zet-profile-register-sequence-t:

zet_profile_register_sequence_t
-------------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenstruct:: zet_profile_register_sequence_t
    :project: LevelZero
    :members:
    :undoc-members:

