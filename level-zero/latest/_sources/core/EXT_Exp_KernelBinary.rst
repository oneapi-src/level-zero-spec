
:orphan:

.. _ZE_extension_kernel_binary_exp:

=========================================
 Get Kernel Binary Program Data Extension
=========================================

API
----

* Enumerations

    * :ref:`ze-kernel-get-binary-exp-version-t`

* Functions

    * :ref:`zeKernelGetBinaryExp`


===============================
 Get Kernel Binary Program Data
===============================

After a kernel is created with zeKernelCreate, the user will be able to retrieve the kernel
binary program data, which is in GEN ISA format.  Each valid kernel handle will provide the
information required to retrieve such data.  The user may then save this data to a file for
disassembly and analysis.  There is a 2-step process to obtain this data.  The first step is
to find the size of binary program data, so that memory may be allocated to store such data.
This is done by providing an input storage pointer with nullptr value.  After allocating a
storage array of this size, the user then provides the valid size and storage location to 
retrieve the data.

The following pseudo-code shows how to obtain the kernel binary program data save to a file:

.. parsed-literal::

    #include <fstream>
    //hKernel = valid kernel handle
    size_t kBinarySize = 0;
    char ``*``\progArray;
    :ref:`zeKernelGetBinaryExp`\(hKernel, &KBinarysize, nullptr);
    progArray = new char[kBinarySize];
    :ref:`zeKernelGetBinaryExp`\(hKernel, &kBinarySize, progArray);
    const std::string filePath = "program.bin";
    std::ofstream stream(filePath, std::ios::out | std::ios::binary);
    stream.write(reinterpret_cast<const char ``*``\>(progArray), kBinarySize);
    stream.close();
    delete[] progArray;
