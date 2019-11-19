# Programming Guide (SPIR-V)

[DO NOT EDIT]: # (generated from /scripts/core/SPIRV.md)

NOTE: This is a **PRELIMINARY** specification, provided for review and feedback.

# Introduction

[SPIR-V](https://www.khronos.org/registry/spir-v/) is an open, royalty-free, standard intermediate language capable of representing parallel compute kernels.  SPIR-V is adaptable to multiple execution environments: a SPIR-V module is consumed by an execution environment, as specified by a client API. This document describes the SPIR-V execution environment for the 'One API' Level-Zero API. The SPIR-V execution environment describes required support for some SPIR-V capabilities, additional semantics for some SPIR-V instructions, and additional validation rules that a SPIR-V binary module must adhere to in order to be considered valid.

This document is written for compiler developers who are generating SPIR-V modules intended to be consumed by the 'One API' Level-Zero API, for implementors of the 'One API' Level-Zero API, and for software developers who are using SPIR-V modules with the 'One API' Level-Zero API.

# Common Properties

This section describes common properties of all 'One API' Level-Zero environments that consume SPIR-V modules.

A SPIR-V module is interpreted as a series of 32-bit words in host endianness, with literal strings packed as described in the SPIR-V specification.
The first few words of the SPIR-V module must be a magic number and a SPIR-V version number, as described in the SPIR-V specification.

## Supported SPIR-V Versions

The maximum SPIR-V version supported by a device is described by ::ze_device_kernel_properties_t.spirvVersionSupported.

## Extended Instruction Sets

The **OpenCL.std** [extended instruction set for OpenCL](https://www.khronos.org/registry/spir-v/) is supported.

## Source Language Encoding

The source language version is purely informational and has no semantic meaning.

## Numerical Type Formats

Floating-point types are represented and stored using [IEEE-754](http://dx.doi.org/10.1109/IEEESTD.2008.4610935) semantics.
All integer formats are represented and stored using 2's-complement format.

## Supported Types

The following types are supported.
Note that some types may require additional capabilities, and may not be supported by all environments.

### Basic Scalar and Vector Types

**OpTypeVoid** is supported.

The following scalar types are supported:

* **OpTypeBool**
* **OpTypeInt**, with _Width_ equal to 8, 16, 32, or 64, and with _Signedness_ equal to zero, indicating no signedness semantics.
* **OpTypeFloat**, with _Width_ equal to 16, 32, or 64.

**OpTypeVector** vector types are supported.
The vector _Component Type_ may be any of the scalar types described above.
Supported vector _Component Counts_ are 2, 3, 4, 8, or 16.

**OpTypeArray** array types are supported, **OpTypeStruct** struct types are supported, **OpTypeFunction** functions are supported, and **OpTypePointer** pointer types are supported.

### Image-Related Data Types

The following table describes the supported **OpTypeImage** image types:

| _Dim_   | _Depth_ | _Arrayed_ | **Description**
| :--:    | :--:    | :--:      | :--:
| **1D**  | `0`     | `0`       | A 1D image.
| **1D**  | `0`     | `1`       | A 1D image array.
| **2D**  | `0`     | `0`       | A 2D image.
| **2D**  | `1`     | `0`       | A 2D depth image.
| **2D**  | `0`     | `1`       | A 2D image array.
| **2D**  | `1`     | `1`       | A 2D depth image array.
| **3D**  | `0`     | `0`       | A 3D image.
| **Buffer** | `0`  | `0`       | A 1D buffer image.

**OpTypeSampler** sampler typed are supported.

## Kernels

An **OpFunction** in a SPIR-V module that is identified with **OpEntryPoint** defines a kernel that may be launched using host API interfaces.

## Kernel Return Types

The _Result Type_ for an **OpFunction** identified with **OpEntryPoint** must be **OpTypeVoid**.

## Kernel Arguments

An **OpFunctionParameter** for an **OpFunction** that is identified with **OpEntryPoint** defines a kernel argument.
Allowed types for kernel arguments are:

  * **OpTypeInt**
  * **OpTypeFloat**
  * **OpTypeStruct**
  * **OpTypeVector**
  * **OpTypePointer**
  * **OpTypeSampler**
  * **OpTypeImage**

For **OpTypeInt** parameters, supported _Widths_ are 8, 16, 32, and 64, and must have no signedness semantics.

For **OpTypeFloat** parameters, supported _Widths_ are 16 and 32.

For **OpTypeStruct** parameters, supported structure _Member Types_ are:

  * **OpTypeInt**
  * **OpTypeFloat**
  * **OpTypeStruct**
  * **OpTypeVector**
  * **OpTypePointer**

For **OpTypePointer** parameters, supported _Storage Classes_ are:

  * **CrossWorkgroup**
  * **Workgroup**
  * **UniformConstant**

Environments that support extensions or optional features may allow additional types in an entry point's parameter list.

# Required Capabilities

## SPIR-V 1.0

An environment that supports SPIR-V 1.0 must support SPIR-V 1.0 modules that declare the following capabilities:

  * **Addresses**
  * **Float16Buffer**
  * **Int64**
  * **Int16**
  * **Int8**
  * **Kernel**
  * **Linkage**
  * **Vector16**
  * **GenericPointer**
  * **Groups**
  * **ImageBasic** (for devices supporting ::ze_device_image_properties_t::supported)
  * **Float16** (for devices supporting ::ze_device_kernel_properties_t.fp16Supported)
  * **Float64** (for devices supporting ::ze_device_kernel_properties_t.fp64Supported)
  * **Int64Atomics** (for devices supporting ::ze_device_kernel_properties_t.int64AtomicsSupported)

If the 'One API' environment supports the **ImageBasic** capability, then
the following capabilities must also be supported:

  * **LiteralSampler**
  * **Sampled1D**
  * **Image1D**
  * **SampledBuffer**
  * **ImageBuffer**
  * **ImageReadWrite**

## SPIR-V 1.1

An environment supporting SPIR-V 1.1 must support SPIR-V 1.1
modules that declare the capabilities required for SPIR-V 1.0 modules,
above.

SPIR-V 1.1 does not add any new required capabilities.

## SPIR-V 1.2

An environment supporting SPIR-V 1.2 must support SPIR-V 1.2
modules that declare the capabilities required for SPIR-V 1.1 modules,
above.

SPIR-V 1.2 does not add any new required capabilities.

# Validation Rules

The following are a list of validation rules that apply to SPIR-V modules
executing in all 'One API' Level-Zero environments:

The _Execution Model_ declared in **OpEntryPoint** must be **Kernel**.

The _Addressing Model_ declared in **OpMemoryModel** must **Physical64**,
indicating that device pointers are 64-bits.

The _Memory Model_ declared in **OpMemoryModel** must be **OpenCL**.

For all **OpTypeInt** integer type-declaration instructions:

  * _Signedness_ must be 0, indicating no signedness semantics.

For all **OpTypeImage** type-declaration instructions:
  * _Sampled Type_ must be **OpTypeVoid**.
  * _Sampled_ must be 0, indicating that the image usage will be known at
     run time, not at compile time.
  * _MS_ must be 0, indicating single-sampled content.
  * _Arrayed_ may only be set to 1, indicating arrayed content, when _Dim_
     is set to **1D** or **2D**.
  * _Image Format_ must be **Unknown**, indicating that the image does not
     have a specified format.
  * The optional image _Access Qualifier_ must be present.

The image write instruction **OpImageWrite** must not include any optional
_Image Operands_.

The image read instructions **OpImageRead** and **OpImageSampleExplicitLod** 
must not include the optional _Image Operand_ **ConstOffset**.

For all *Atomic Instructions*:

  * 32-bit integer types are supported for the _Result Type_ and/or type of _Value_.
    64-bit integer types are optionally supported for the _Result Type_ and/or type
    of _Value_ for devices supporting ::ze_device_kernel_properties_t.int64AtomicsSupported.
  * The _Pointer_ operand must be a pointer to the **Function**, **Workgroup**,
    **CrossWorkGroup**, or **Generic** _Storage Classes_.

Recursion is not supported.
The static function call graph for an entry point must not contain cycles.

Whether irreducible control flow is legal is implementation defined.

For the instructions **OpGroupAsyncCopy** and **OpGroupWaitEvents**, _Scope_ for _Execution_ must be:

  * **Workgroup**

For all other instructions, _Scope_ for _Execution_ must be one of:

  * **Workgroup**
  * **Subgroup**

_Scope_ for _Memory_ must be one of:

  * **CrossDevice**
  * **Device**
  * **Workgroup**
  * **Invocation**
  * **Subgroup**

# Extensions

## `SPV_INTEL_subgroups`

'One API' Level-Zero API environments must accept SPIR-V modules that declare use of the `SPV_INTEL_subgroups` extension via **OpExtension**.

When use of the `SPV_INTEL_subgroups` extension is declared in the module via **OpExtension**, the environment must accept modules that declare the following SPIR-V capabilities:

  * **SubgroupShuffleINTEL**
  * **SubgroupBufferBlockIOINTEL**
  * **SubgroupImageBlockIOINTEL**

The environment must accept the following types for _Data_ for the **SubgroupShuffleINTEL** instructions:

  * Scalars and **OpTypeVectors** with 2, 4, 8, or 16 _Component Count_ components of the following _Component Type_ types:
    * **OpTypeFloat** with a _Width_ of 32 bits (`float`)
    * TBD: char types?
    * **OpTypeInt** with a _Width_ of 16 bits and _Signedness_ of 0 (`short` and `ushort`)
    * **OpTypeInt** with a _Width_ of 32 bits and _Signedness_ of 0 (`int` and `uint`)
  * Scalars of **OpTypeInt** with a _Width_ of 64 bits and _Signedness_ of 0 (`long` and `ulong`)
    * TBD: vectors of long types?

Additionally, if the **Float16** capability is declared and supported:

  * Scalars of **OpTypeFloat** with a _Width_ of 16 bits (`half`)

Additionally, if the **Float64** capability is declared and supported:

  * Scalars of **OpTypeFloat** with a _Width_ of 64 bits (`double`)

The environment must accept the following types for _Result_ and _Data_ for the **SubgroupBufferBlockIOINTEL** and **SubgroupImageBlockIOINTEL** instructions:

  * Scalars and **OpTypeVectors** with 2, 4, or 8 _Component Count_ components of the following _Component Type_ types:
    * **OpTypeInt** with a _Width_ of 32 bits and _Signedness_ of 0 (`int` and `uint`)
    * **OpTypeInt** with a _Width_ of 16 bits and _Signedness_ of 0 (`short` and `ushort`)

For _Ptr_, valid _Storage Classes_ are:

* **CrossWorkGroup** (`global`)

For _Image_:

* _Dim_ must be *2D*
* _Depth_ must be 0 (not a depth image)
* _Arrayed_ must be 0 (non-arrayed content)
* _MS_ must be 0 (single-sampled content)

For _Coordinate_, the following types are supported:

* **OpTypeVectors** with two _Component Count_ components of _Component Type_ **OpTypeInt** with a _Width_ of 32 bits and _Signedness_ of 0 (`int2`)

### Notes and Restrictions

The **SubgroupShuffleINTEL** instructions may be placed within non-uniform control flow and hence do not have to be encountered by all invocations in the subgroup, however _Data_ may only be shuffled among invocations encountering the **SubgroupShuffleINTEL** instruction.
Shuffling _Data_ from an invocation that does not encounter the **SubgroupShuffleINTEL** instruction will produce undefined results.

There is no defined behavior for out-of-range shuffle indices for the **SubgroupShuffleINTEL** instructions.

The **SubgroupBufferBlockIOINTEL** and **SubgroupImageBlockIOINTEL** instructions are only guaranteed to work correctly if placed strictly within uniform control flow within the subgroup.
This ensures that if any invocation executes it, all invocations will execute it.
If placed elsewhere, behavior is undefined.

There is no defined out-of-range behavior for the **SubgroupBufferBlockIOINTEL** instructions.

The **SubgroupImageBlockIOINTEL** instructions do support bounds checking, however they bounds-check to the image width in units of `uints`, not in units of image elements.
This means:

  * If the image has an _Image Format_ size equal to the size of a `uint` (four bytes, for example **Rgba8**), the image will be correctly bounds-checked.
    In this case, out-of-bounds reads will return the edge image element (the equivalent of **ClampToEdge**), and out-of-bounds writes will be ignored.

  * If the image has an _Image Format_ size less than the size of a `uint` (such as **R8**), the entire image is addressable, however bounds checking will occur too late.
    For this reason, extra care should be taken to avoid out-of-bounds reads and writes, since out-of-bounds reads may return invalid data and out-of-bounds writes may corrupt other images or buffers unpredictably.

The following restrictions apply to the **SubgroupBufferBlockIOINTEL** instructions:

  * The pointer _Ptr_ must be 32-bit (4-byte) aligned for reads, and must be 128-bit (16-byte) aligned for writes.

The following restrictions apply to the **SubgroupImageBlockIOINTEL** instructions:

  * The behavior of the **SubgroupImageBlockIOINTEL** instructions is undefined for images with an element size greater than four bytes (such as **Rgba32f**).

The following restrictions apply to the **OpSubgroupImageBlockWriteINTEL** instruction:

  * Unlike the image block read instruction, which may read from any arbitrary byte offset, the x-component of the byte coordinate for the image block write instruction must be a multiple of four; in other words, the write must begin at a 32-bit boundary.
    There is no restriction on the y-component of the coordinate.

## Other Extensions to Consider:

  * [SPV_INTEL_media_block_io](http://htmlpreview.github.io/?https://github.com/KhronosGroup/SPIRV-Registry/blob/master/extensions/INTEL/SPV_INTEL_media_block_io.html) / [cl_intel_spirv_media_block_io](https://www.khronos.org/registry/OpenCL/extensions/intel/cl_intel_spirv_media_block_io.html)?

# Numerical Compliance

The 'One API' Level-Zero environment will meet or exceed the numerical compliance requirements defined in the OpenCL SPIR-V Environment Specification.
See: [Numerical Compliance](https://www.khronos.org/registry/OpenCL/specs/2.2/html/OpenCL_Env.html#numerical_compliance).

# Image Addressing and Filtering

The 'One API' Level-Zero environment image addressing and filtering behavior is compatible with the behavior defined in the OpenCL SPIR-V Environment Specification.
See: [Image Addressing and Filtering](https://www.khronos.org/registry/OpenCL/specs/2.2/html/OpenCL_Env.html#image_addressing_and_filtering).
