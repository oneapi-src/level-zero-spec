============================================================
Diagnostics
============================================================
oneAPI Level Zero Specification - Version 1.21.26


Diagnostics Handles
===================


.. _zes-diag-handle-t:

zes_diag_handle_t
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Obtained from:** :ref:`zesDeviceEnumDiagnosticTestSuites`
   | **Used by:** :ref:`zesDiagnosticsGetProperties`, :ref:`zesDiagnosticsGetTests`, :ref:`zesDiagnosticsRunTests`
   | **See also:** :ref:`Performing Diagnostics (Programming Guide) <Diagnostics>`

.. cpp:type:: zes_diag_handle_t

    Handle for a Sysman device diagnostics test suite.



Diagnostics Functions
=====================


.. _zesDiagnosticsGetProperties:

zesDiagnosticsGetProperties
---------------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesDiagnosticsGetProperties
    :project: LevelZero


.. _zesDiagnosticsGetTests:

zesDiagnosticsGetTests
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesDiagnosticsGetTests
    :project: LevelZero


.. _zesDiagnosticsRunTests:

zesDiagnosticsRunTests
----------------------

.. rst-class:: api-version

*Added in version 1.0*

.. doxygenfunction:: zesDiagnosticsRunTests
    :project: LevelZero



Diagnostics Enums
=================


.. _zes-diag-result-t:

zes_diag_result_t
-----------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesDiagnosticsRunTests`

.. doxygenenum:: zes_diag_result_t
    :project: LevelZero


 
Diagnostics Structures
======================


.. _zes-diag-test-t:

zes_diag_test_t
---------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesDiagnosticsGetTests`

.. doxygenstruct:: zes_diag_test_t
    :project: LevelZero
    :members:
    :undoc-members:


.. _zes-diag-properties-t:

zes_diag_properties_t
---------------------

.. rst-class:: api-version

*Added in version 1.0*

.. container:: api-usage

   | **Used by:** :ref:`zesDiagnosticsGetProperties`

.. doxygenstruct:: zes_diag_properties_t
    :project: LevelZero
    :members:
    :undoc-members:

