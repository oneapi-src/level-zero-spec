
<%
    OneApi=tags['$OneApi']
    x=tags['$x']
    X=x.upper()
%>
==========================
 SPIR-V Programming Guide
==========================

Introduction
============

`SPIR-V <https://www.khronos.org/registry/spir-v/>`__ is an open,
royalty-free, standard intermediate language capable of representing
parallel compute kernels. SPIR-V is adaptable to multiple execution
environments: a SPIR-V module is consumed by an execution environment,
as specified by a client API. This document describes the SPIR-V
execution environment for the ${OneApi} Level-Zero API. The SPIR-V
execution environment describes required support for some SPIR-V
capabilities, additional semantics for some SPIR-V instructions, and
additional validation rules that a SPIR-V binary module must adhere to
in order to be considered valid.

This document is written for compiler developers who are generating
SPIR-V modules intended to be consumed by the ${OneApi} Level-Zero API,
for implementors of the ${OneApi} Level-Zero API, and for software
developers who are using SPIR-V modules with the ${OneApi} Level-Zero
API.

Common Properties
=================

This section describes common properties of all ${OneApi} Level-Zero
environments that consume SPIR-V modules.

A SPIR-V module is interpreted as a series of 32-bit words in host
endianness, with literal strings packed as described in the SPIR-V
specification. The first few words of the SPIR-V module must be a magic
number and a SPIR-V version number, as described in the SPIR-V
specification.

Supported SPIR-V Versions
-------------------------

The maximum SPIR-V version supported by a device is described by ${x}_device_module_properties_t.spirvVersionSupported.

Extended Instruction Sets
-------------------------

The **OpenCL.std** `extended instruction set for
OpenCL <https://www.khronos.org/registry/spir-v/>`__ is supported.

Source Language Encoding
------------------------

The source language version is purely informational and has no semantic
meaning.

Numerical Type Formats
----------------------

Floating-point types are represented and stored using
`IEEE-754 <http://dx.doi.org/10.1109/IEEESTD.2008.4610935>`__ semantics.
All integer formats are represented and stored using 2's-complement
format.

Supported Types
---------------

The following types are supported. Note that some types may require
additional capabilities, and may not be supported by all environments.

Basic Scalar and Vector Types
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

**OpTypeVoid** is supported.

The following scalar types are supported:

-  **OpTypeBool**
-  **OpTypeInt**, with *Width* equal to 8, 16, 32, or 64, and with
   *Signedness* equal to zero, indicating no signedness semantics.
-  **OpTypeFloat**, with *Width* equal to 16, 32, or 64.

**OpTypeVector** vector types are supported. The vector *Component Type*
may be any of the scalar types described above. Supported vector
*Component Counts* are 2, 3, 4, 8, or 16.

**OpTypeArray** array types are supported, **OpTypeStruct** struct types
are supported, **OpTypeFunction** functions are supported, and
**OpTypePointer** pointer types are supported.

Image-Related Data Types
~~~~~~~~~~~~~~~~~~~~~~~~

The following table describes the supported **OpTypeImage** image types:

========== ======= ========= =======================
*Dim*      *Depth* *Arrayed* **Description**
========== ======= ========= =======================
**1D**     ``0``   ``0``     A 1D image.
**1D**     ``0``   ``1``     A 1D image array.
**2D**     ``0``   ``0``     A 2D image.
**2D**     ``1``   ``0``     A 2D depth image.
**2D**     ``0``   ``1``     A 2D image array.
**2D**     ``1``   ``1``     A 2D depth image array.
**3D**     ``0``   ``0``     A 3D image.
**Buffer** ``0``   ``0``     A 1D buffer image.
========== ======= ========= =======================

**OpTypeSampler** sampler typed are supported.

Kernels
-------

An **OpFunction** in a SPIR-V module that is identified with
**OpEntryPoint** defines a kernel that may be launched using host API
interfaces.

Kernel Return Types
-------------------

The *Result Type* for an **OpFunction** identified with **OpEntryPoint**
must be **OpTypeVoid**.

Kernel Arguments
----------------

An **OpFunctionParameter** for an **OpFunction** that is identified with
**OpEntryPoint** defines a kernel argument. Allowed types for kernel
arguments are:

-  **OpTypeInt**
-  **OpTypeFloat**
-  **OpTypeStruct**
-  **OpTypeVector**
-  **OpTypePointer**
-  **OpTypeSampler**
-  **OpTypeImage**

For **OpTypeInt** parameters, supported *Widths* are 8, 16, 32, and 64,
and must have no signedness semantics.

For **OpTypeFloat** parameters, supported *Widths* are 16 and 32.

For **OpTypeStruct** parameters, supported structure *Member Types* are:

-  **OpTypeInt**
-  **OpTypeFloat**
-  **OpTypeStruct**
-  **OpTypeVector**
-  **OpTypePointer**

For **OpTypePointer** parameters, supported *Storage Classes* are:

-  **CrossWorkgroup**
-  **Workgroup**
-  **UniformConstant**

Environments that support extensions or optional features may allow
additional types in an entry point's parameter list.

Required Capabilities
=====================

SPIR-V 1.0
----------

An environment that supports SPIR-V 1.0 must support SPIR-V 1.0 modules
that declare the following capabilities:

-  **Addresses**
-  **Float16Buffer**
-  **Int64**
-  **Int16**
-  **Int8**
-  **Kernel**
-  **Linkage**
-  **Vector16**
-  **GenericPointer**
-  **Groups**
-  **ImageBasic** (for devices supporting ${x}_device_image_properties_t.supported)
-  **Float16** (for devices supporting ${X}_DEVICE_MODULE_FLAG_FP16)
-  **Float64** (for devices supporting ${X}_DEVICE_MODULE_FLAG_FP64)
-  **Int64Atomics** (for devices supporting ${X}_DEVICE_MODULE_FLAG_INT64_ATOMICS)

If the ${OneApi} environment supports the **ImageBasic** capability,
then the following capabilities must also be supported:

-  **LiteralSampler**
-  **Sampled1D**
-  **Image1D**
-  **SampledBuffer**
-  **ImageBuffer**
-  **ImageReadWrite**

SPIR-V 1.1
----------

An environment supporting SPIR-V 1.1 must support SPIR-V 1.1 modules
that declare the capabilities required for SPIR-V 1.0 modules, above.

SPIR-V 1.1 does not add any new required capabilities.

SPIR-V 1.2
----------

An environment supporting SPIR-V 1.2 must support SPIR-V 1.2 modules
that declare the capabilities required for SPIR-V 1.1 modules, above.

SPIR-V 1.2 does not add any new required capabilities.

Validation Rules
================

The following are a list of validation rules that apply to SPIR-V
modules executing in all ${OneApi} Level-Zero environments:

The *Execution Model* declared in **OpEntryPoint** must be **Kernel**.

The *Addressing Model* declared in **OpMemoryModel** must
**Physical64**, indicating that device pointers are 64-bits.

The *Memory Model* declared in **OpMemoryModel** must be **OpenCL**.

For all **OpTypeInt** integer type-declaration instructions:

-  *Signedness* must be 0, indicating no signedness semantics.

For all **OpTypeImage** type-declaration instructions: \* *Sampled Type*
must be **OpTypeVoid**. \* *Sampled* must be 0, indicating that the
image usage will be known at run time, not at compile time. \* *MS* must
be 0, indicating single-sampled content. \* *Arrayed* may only be set to
1, indicating arrayed content, when *Dim* is set to **1D** or **2D**. \*
*Image Format* must be **Unknown**, indicating that the image does not
have a specified format. \* The optional image *Access Qualifier* must
be present.

The image write instruction **OpImageWrite** must not include any
optional *Image Operands*.

The image read instructions **OpImageRead** and
**OpImageSampleExplicitLod** must not include the optional *Image
Operand* **ConstOffset**.

For all *Atomic Instructions*:

-  32-bit integer types are supported for the *Result Type* and/or type
   of *Value*. 64-bit integer types are optionally supported for the
   *Result Type* and/or type of *Value* for devices supporting
   ${X}_DEVICE_MODULE_FLAG_INT64_ATOMICS.
-  The *Pointer* operand must be a pointer to the **Function**,
   **Workgroup**, **CrossWorkGroup**, or **Generic** *Storage Classes*.

Recursion is not supported. The static function call graph for an entry
point must not contain cycles.

Whether irreducible control flow is legal is implementation defined.

For the instructions **OpGroupAsyncCopy** and **OpGroupWaitEvents**,
*Scope* for *Execution* must be:

-  **Workgroup**

For all other instructions, *Scope* for *Execution* must be one of:

-  **Workgroup**
-  **Subgroup**

*Scope* for *Memory* must be one of:

-  **CrossDevice**
-  **Device**
-  **Workgroup**
-  **Invocation**
-  **Subgroup**

Extensions
==========

Intel Subgroups
---------------

${OneApi} Level-Zero API environments must accept SPIR-V modules that
declare use of the ``SPV_INTEL_subgroups`` extension via
**OpExtension**.

When use of the ``SPV_INTEL_subgroups`` extension is declared in the
module via **OpExtension**, the environment must accept modules that
declare the following SPIR-V capabilities:

-  **SubgroupShuffleINTEL**
-  **SubgroupBufferBlockIOINTEL**
-  **SubgroupImageBlockIOINTEL**

The environment must accept the following types for *Data* for the
**SubgroupShuffleINTEL** instructions:

-  Scalars and **OpTypeVectors** with 2, 4, 8, or 16 *Component Count*
   components of the following *Component Type* types:

   -  **OpTypeFloat** with a *Width* of 32 bits (``float``)
   -  **OpTypeInt** with a *Width* of 8 bits and *Signedness* of 0
      (``char`` and ``uchar``)
   -  **OpTypeInt** with a *Width* of 16 bits and *Signedness* of 0
      (``short`` and ``ushort``)
   -  **OpTypeInt** with a *Width* of 32 bits and *Signedness* of 0
      (``int`` and ``uint``)

-  Scalars of **OpTypeInt** with a *Width* of 64 bits and *Signedness*
   of 0 (``long`` and ``ulong``)

Additionally, if the **Float16** capability is declared and supported:

-  Scalars of **OpTypeFloat** with a *Width* of 16 bits (``half``)

Additionally, if the **Float64** capability is declared and supported:

-  Scalars of **OpTypeFloat** with a *Width* of 64 bits (``double``)

The environment must accept the following types for *Result* and *Data*
for the **SubgroupBufferBlockIOINTEL** and **SubgroupImageBlockIOINTEL**
instructions:

-  Scalars and **OpTypeVectors** with 2, 4, or 8 *Component Count*
   components of the following *Component Type* types:

   -  **OpTypeInt** with a *Width* of 32 bits and *Signedness* of 0
      (``int`` and ``uint``)
   -  **OpTypeInt** with a *Width* of 16 bits and *Signedness* of 0
      (``short`` and ``ushort``)

For *Ptr*, valid *Storage Classes* are:

-  **CrossWorkGroup** (``global``)

For *Image*:

-  *Dim* must be *2D*
-  *Depth* must be 0 (not a depth image)
-  *Arrayed* must be 0 (non-arrayed content)
-  *MS* must be 0 (single-sampled content)

For *Coordinate*, the following types are supported:

-  **OpTypeVectors** with two *Component Count* components of *Component
   Type* **OpTypeInt** with a *Width* of 32 bits and *Signedness* of 0
   (``int2``)

Notes and Restrictions
~~~~~~~~~~~~~~~~~~~~~~

The **SubgroupShuffleINTEL** instructions may be placed within
non-uniform control flow and hence do not have to be encountered by all
invocations in the subgroup, however *Data* may only be shuffled among
invocations encountering the **SubgroupShuffleINTEL** instruction.
Shuffling *Data* from an invocation that does not encounter the
**SubgroupShuffleINTEL** instruction will produce undefined results.

There is no defined behavior for out-of-range shuffle indices for the
**SubgroupShuffleINTEL** instructions.

The **SubgroupBufferBlockIOINTEL** and **SubgroupImageBlockIOINTEL**
instructions are only guaranteed to work correctly if placed strictly
within uniform control flow within the subgroup. This ensures that if
any invocation executes it, all invocations will execute it. If placed
elsewhere, behavior is undefined.

There is no defined out-of-range behavior for the
**SubgroupBufferBlockIOINTEL** instructions.

The **SubgroupImageBlockIOINTEL** instructions do support bounds
checking, however they bounds-check to the image width in units of
``uints``, not in units of image elements. This means:

-  If the image has an *Image Format* size equal to the size of a
   ``uint`` (four bytes, for example **Rgba8**), the image will be
   correctly bounds-checked. In this case, out-of-bounds reads will
   return the edge image element (the equivalent of **ClampToEdge**),
   and out-of-bounds writes will be ignored.

-  If the image has an *Image Format* size less than the size of a
   ``uint`` (such as **R8**), the entire image is addressable, however
   bounds checking will occur too late. For this reason, extra care
   should be taken to avoid out-of-bounds reads and writes, since
   out-of-bounds reads may return invalid data and out-of-bounds writes
   may corrupt other images or buffers unpredictably.

The following restrictions apply to the **SubgroupBufferBlockIOINTEL**
instructions:

-  The pointer *Ptr* must be 32-bit (4-byte) aligned for reads, and must
   be 128-bit (16-byte) aligned for writes.

The following restrictions apply to the **SubgroupImageBlockIOINTEL**
instructions:

-  The behavior of the **SubgroupImageBlockIOINTEL** instructions is
   undefined for images with an element size greater than four bytes
   (such as **Rgba32f**).

The following restrictions apply to the
**OpSubgroupImageBlockWriteINTEL** instruction:

-  Unlike the image block read instruction, which may read from any
   arbitrary byte offset, the x-component of the byte coordinate for the
   image block write instruction must be a multiple of four; in other
   words, the write must begin at a 32-bit boundary. There is no
   restriction on the y-component of the coordinate.

%if ver >= 1.1:

Floating-Point Atomics
----------------------

${OneApi} Level-Zero API environments supporting the extension
**${X}_extension_float_atomics** must support additional atomic instructions,
capabilities, and types.

Atomic Load, Store, and Exchange
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

If the ${OneApi} Level-Zero API environment supports the extension **${X}_extension_float_atomics** and ${x}_device_fp_atomic_ext_flags_t.fp16Flags includes ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_GLOBAL_LOAD_STORE or ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_LOCAL_LOAD_STORE, then for the **Atomic Instructions** **OpAtomicLoad**, **OpAtomicStore**, and **OpAtomicExchange**:

-  16-bit floating-point types are supported for the *Result Type* and type of
   *Value*.
-  When ${x}_device_fp_atomic_ext_flags_t.fp16Flags includes ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_GLOBAL_LOAD_STORE, the *Pointer* operand may be a pointer to the **CrossWorkGroup** *Storage Class*.
-  When ${x}_device_fp_atomic_ext_flags_t.fp16Flags includes ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_LOCAL_LOAD_STORE, the *Pointer* operand may be a pointer to the **Workgroup** *Storage Class*.

Atomic Add and Subtract
~~~~~~~~~~~~~~~~~~~~~~~

If the ${OneApi} Level-Zero API environment supports the extension **${X}_extension_float_atomics** and ${x}_device_fp_atomic_ext_flags_t.fp16Flags, ${x}_device_fp_atomic_ext_flags_t.fp32Flags, or ${x}_device_fp_atomic_ext_flags_t.fp64Flags include ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_GLOBAL_ADD or ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_LOCAL_ADD, then the environment must accept modules that declare use of the extensions ``SPV_EXT_shader_atomic_float_add`` and ``SPV_EXT_shader_atomic_float16_add``.
Additionally:

-  When ${x}_device_fp_atomic_ext_flags_t.fp16Flags includes ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_GLOBAL_ADD or ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_LOCAL_ADD, the **AtomicFloat16AddEXT** capability must be supported.
-  When ${x}_device_fp_atomic_ext_flags_t.fp32Flags includes ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_GLOBAL_ADD or ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_LOCAL_ADD, the **AtomicFloat32AddEXT** capability must be supported.
-  When ${x}_device_fp_atomic_ext_flags_t.fp64Flags includes ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_GLOBAL_ADD or ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_LOCAL_ADD, the **AtomicFloat64AddEXT** capability must be supported.
-  For the **Atomic Instruction** **OpAtomicFAddEXT** added by these extensions:

  -  When ${x}_device_fp_atomic_ext_flags_t.fp32Flags, ${x}_device_fp_atomic_ext_flags_t.fp64Flags, or ${x}_device_fp_atomic_ext_flags_t.fp16Flags includes ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_GLOBAL_ADD, the *Pointer* operand may be a pointer to the **CrossWorkGroup** *Storage Class*.
  -  When ${x}_device_fp_atomic_ext_flags_t.fp32Flags, ${x}_device_fp_atomic_ext_flags_t.fp64Flags, or ${x}_device_fp_atomic_ext_flags_t.fp16Flags includes ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_LOCAL_ADD, the *Pointer* operand may be a pointer to the **Workgroup** *Storage Class*.

Atomic Min and Max
~~~~~~~~~~~~~~~~~~

If the ${OneApi} Level-Zero API environment supports the extension **${X}_extension_float_atomics** and the ${x}_device_fp_atomic_ext_flags_t.fp32Flags, ${x}_device_fp_atomic_ext_flags_t.fp64Flags, or ${x}_device_fp_atomic_ext_flags_t.fp16Flags bitfields include ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_GLOBAL_MIN_MAX or ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_LOCAL_MIN_MAX, then the environment must accept modules that declare use of the extension ``SPV_EXT_shader_atomic_float_min_max``.
Additionally:

-  When ${x}_device_fp_atomic_ext_flags_t.fp32Flags includes ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_GLOBAL_MIN_MAX or ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_LOCAL_MIN_MAX, the **AtomicFloat32MinMaxEXT** capability must be supported.
-  When ${x}_device_fp_atomic_ext_flags_t.fp64Flags includes ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_GLOBAL_MIN_MAX or ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_LOCAL_MIN_MAX, the **AtomicFloat64MinMaxEXT** capability must be supported.
-  When ${x}_device_fp_atomic_ext_flags_t.fp16Flags includes ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_GLOBAL_MIN_MAX or ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_LOCAL_MIN_MAX, the **AtomicFloat16MinMaxEXT** capability must be supported.
-  For the **Atomic Instructions** **OpAtomicFMinEXT** and **OpAtomicFMaxEXT** added by this extension:

  -  When ${x}_device_fp_atomic_ext_flags_t.fp16Flags, ${x}_device_fp_atomic_ext_flags_t.fp32Flags, or ${x}_device_fp_atomic_ext_flags_t.fp64Flags includes ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_GLOBAL_MIN_MAX , the *Pointer* operand may be a pointer to the **CrossWorkGroup** *Storage Class*.
  -  When ${x}_device_fp_atomic_ext_flags_t.fp16Flags, ${x}_device_fp_atomic_ext_flags_t.fp32Flags, or ${x}_device_fp_atomic_ext_flags_t.fp64Flags includes ${X}_DEVICE_FP_ATOMIC_EXT_FLAG_LOCAL_MIN_MAX, the *Pointer* operand may be a pointer to the **Workgroup** *Storage Class*.

%endif

%if ver >= 1.1:
Extended Subgroups
------------------

${OneApi} Level-Zero API environments supporting the extension
**${X}_extension_subgroups** must support additional subgroup instructions,
capabilities, and types.

Extended Types
~~~~~~~~~~~~~~

The following Groups instructions must be supported with *Scope* for *Execution*
equal to **Subgroup**:

-  **OpGroupBroadcast**
-  **OpGroupIAdd**, **OpGroupFAdd**
-  **OpGroupSMin**, **OpGroupUMin**, **OpGroupFMin**
-  **OpGroupSMax**, **OpGroupUMax**, **OpGroupFMax**

For these instructions, valid types for *Value* are:

-  Scalars of supported types:

  -  **OpTypeInt** (equivalent to ``char``, ``uchar``, ``short``, ``ushort``,
     ``int``, ``uint``, ``long``, and ``ulong``)
  -  **OpTypeFloat** (equivalent to ``half``, ``float``, and ``double``)

Additionally, for **OpGroupBroadcast**, valid types for *Value* are:

-  **OpTypeVectors** with 2, 3, 4, 8, or 16 Component Count components of
   supported types:

  -  **OpTypeInt** (equivalent to ``charn``, ``ucharn``, ``shortn``,
     ``ushortn``, ``intn``, ``uintn``, ``longn``, and ``ulongn``)
  -  **OpTypeFloat** (equivalent to ``halfn``, ``floatn``, and ``doublen``)

Vote
~~~~

The following capabilities must be supported:

-  **GroupNonUniform**
-  **GroupNonUniformVote**

For instructions requiring these capabilities, *Scope* for *Execution* may be:

-  **Subgroup**

For the instruction **OpGroupNonUniformAllEqual**, valid types for *Value* are:

-  Scalars of supported types:

  -  **OpTypeInt** (equivalent to ``char``, ``uchar``, ``short``, ``ushort``,
     ``int``, ``uint``, ``long``, and ``ulong``)
  -  **OpTypeFloat** (equivalent to ``half``, ``float``, and ``double``)

Ballot
~~~~~~

The following capabilities must be supported:

-  **GroupNonUniformBallot**

For instructions requiring these capabilities, *Scope* for *Execution* may be:

- **Subgroup**

For the non-uniform broadcast instruction **OpGroupNonUniformBroadcast**, valid
types for *Value* are:

-  Scalars of supported types:

  -  **OpTypeInt** (equivalent to ``char``, ``uchar``, ``short``, ``ushort``,
     ``int``, ``uint``, ``long``, and ``ulong``)
  -  **OpTypeFloat** (equivalent to ``half``, ``float``, and ``double``)

-  **OpTypeVectors** with 2, 3, 4, 8, or 16 Component Count components of
   supported types:

  -  **OpTypeInt** (equivalent to ``charn``, ``ucharn``, ``shortn``,
     ``ushortn``, ``intn``, ``uintn``, ``longn``, and ``ulongn``)
  -  **OpTypeFloat** (equivalent to ``halfn``, ``floatn``, and ``doublen``)

For the instruction **OpGroupNonUniformBroadcastFirst**, valid types for *Value* are:

-  Scalars of supported types:

  -  **OpTypeInt** (equivalent to ``char``, ``uchar``, ``short``, ``ushort``,
     ``int``, ``uint``, ``long``, and ``ulong``)
  -  **OpTypeFloat** (equivalent to ``half``, ``float``, and ``double``)

For the instruction **OpGroupNonUniformBallot**, the valid Result Type is an
OpTypeVector with four Component Count components of **OpTypeInt**, with *Width*
equal to 32 and *Signedness* equal to 0 (equivalent to ``uint4``).

For the instructions **OpGroupNonUniformInverseBallot**,
**OpGroupNonUniformBallotBitExtract**, **OpGroupNonUniformBallotBitCount**,
**OpGroupNonUniformBallotFindLSB**, and **OpGroupNonUniformBallotFindMSB**, the
valid type for *Value* is an **OpTypeVector** with four *Component Count*
components of **OpTypeInt**, with *Width* equal to 32 and *Signedness* equal to
0 (equivalent to uint4).

For built-in variables decorated with **SubgroupEqMask**, **SubgroupGeMask**,
**SubgroupGtMask**, **SubgroupLeMask**, or **SubgroupLtMask**, the supported
variable type is an **OpTypeVector** with four *Component Count* components of
**OpTypeInt**, with *Width* equal to 32 and *Signedness* equal to 0 (equivalent
to ``uint4``).

Non-Uniform Arithmetic
~~~~~~~~~~~~~~~~~~~~~~

The following capabilities must be supported:

-  **GroupNonUniformArithmetic**

For instructions requiring these capabilities, *Scope* for *Execution* may be:

- **Subgroup**

For the instructions **OpGroupNonUniformLogicalAnd**,
**OpGroupNonUniformLogicalOr**, and **OpGroupNonUniformLogicalXor**, the valid
type for *Value* is **OpTypeBool**.

Otherwise, for the **GroupNonUniformArithmetic** scan and reduction
instructions, valid types for *Value* are:

-  Scalars of supported types:

  -  **OpTypeInt** (equivalent to ``char``, ``uchar``, ``short``, ``ushort``,
     ``int``, ``uint``, ``long``, and ``ulong``)
  -  **OpTypeFloat** (equivalent to ``half``, ``float``, and ``double``)

For the **GroupNonUniformArithmetic** scan and reduction instructions, the
optional *ClusterSize* operand must not be present.

Shuffles
~~~~~~~~

The following capabilities must be supported:

-  **GroupNonUniformShuffle**

For instructions requiring these capabilities, *Scope* for *Execution* may be:

- **Subgroup**

For the instructions **OpGroupNonUniformShuffle** and
**OpGroupNonUniformShuffleXor** requiring these capabilities, valid types for
*Value* are:

-  Scalars of supported types:

  -  **OpTypeInt** (equivalent to ``char``, ``uchar``, ``short``, ``ushort``,
     ``int``, ``uint``, ``long``, and ``ulong``)
  -  **OpTypeFloat** (equivalent to ``half``, ``float``, and ``double``)

Relative Shuffles
~~~~~~~~~~~~~~~~~

The following capabilities must be supported:

-  **GroupNonUniformShuffleRelative**

For instructions requiring these capabilities, *Scope* for *Execution* may be:

- **Subgroup**

For the **GroupNonUniformShuffleRelative** instructions, valid types for *Value*
are:

-  Scalars of supported types:

  -  **OpTypeInt** (equivalent to ``char``, ``uchar``, ``short``, ``ushort``,
     ``int``, ``uint``, ``long``, and ``ulong``)
  -  **OpTypeFloat** (equivalent to ``half``, ``float``, and ``double``)

Clustered Reductions
~~~~~~~~~~~~~~~~~~~~

The following capabilities must be supported:

-  **GroupNonUniformClustered**

For instructions requiring these capabilities, *Scope* for *Execution* may be:

- **Subgroup**

When the **GroupNonUniformClustered** capability is declared, the
**GroupNonUniformArithmetic** scan and reduction instructions may include the
optional *ClusterSize* operand.

%endif

Numerical Compliance
====================

The ${OneApi} Level-Zero environment will meet or exceed the numerical
compliance requirements defined in the OpenCL SPIR-V Environment
Specification. See: `Numerical
Compliance <https://www.khronos.org/registry/OpenCL/specs/2.2/html/OpenCL_Env.html#numerical_compliance>`__.

Image Addressing and Filtering
==============================

The ${OneApi} Level-Zero environment image addressing and filtering
behavior is compatible with the behavior defined in the OpenCL SPIR-V
Environment Specification. See: `Image Addressing and
Filtering <https://www.khronos.org/registry/OpenCL/specs/2.2/html/OpenCL_Env.html#image_addressing_and_filtering>`__.
