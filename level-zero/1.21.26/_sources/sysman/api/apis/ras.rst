============================================================
Ras
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Ras Handles
===========


.. _zes-ras-handle-t:

zes_ras_handle_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zesDeviceEnumRasErrorSets`
   | **Used by:** :ref:`zesRasGetProperties`, :ref:`zesRasGetConfig`, :ref:`zesRasSetConfig`, :ref:`zesRasGetState`, :ref:`zesRasGetStateExp`, :ref:`zesRasClearStateExp`, :ref:`zesRasGetSupportedCategoriesExp`, :ref:`zesRasGetStateExp2`, :ref:`zesRasGetConfigExp`, :ref:`zesRasSetConfigExp`
   | **See also:** :ref:`Querying RAS errors (Programming Guide) <RAS>`

.. cpp:type:: zes_ras_handle_t

    Handle for a Sysman device RAS error set.



Ras Functions
=============


.. _zesRasGetProperties:

zesRasGetProperties
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesRasGetProperties
    :project: LevelZero


.. _zesRasGetState:

zesRasGetState
--------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesRasGetState
    :project: LevelZero



Ras Enums
=========


.. _zes-ras-error-type-t:

zes_ras_error_type_t
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Member of:** :ref:`zes-ras-properties-t`

.. doxygenenum:: zes_ras_error_type_t
    :project: LevelZero


.. _zes-ras-error-cat-t:

zes_ras_error_cat_t
-------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenenum:: zes_ras_error_cat_t
    :project: LevelZero


 
Ras Structures
==============


.. _zes-ras-properties-t:

zes_ras_properties_t
--------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesRasGetProperties`

.. doxygenstruct:: zes_ras_properties_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-ras-state-t:

zes_ras_state_t
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesRasGetState`
   | **Member of:** :ref:`zes-ras-config-t`

.. doxygenstruct:: zes_ras_state_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-ras-config-t:

zes_ras_config_t
----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesRasGetConfig`, :ref:`zesRasSetConfig`

.. doxygenstruct:: zes_ras_config_t
    :project: LevelZero
    :members:
    :undoc-members:

