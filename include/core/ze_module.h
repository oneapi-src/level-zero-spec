/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_module.h
 *
 * @brief Intel 'One API' Level-Zero APIs for Module
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/module.yml
 * @endcond
 *
 */
#ifndef _ZE_MODULE_H
#define _ZE_MODULE_H
#if defined(__cplusplus)
#pragma once
#endif
#if !defined(_ZE_API_H)
#pragma message("warning: this file is not intended to be included directly")
#endif

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_module_desc_t
typedef enum _ze_module_desc_version_t
{
    ZE_MODULE_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),   ///< version 1.0

} ze_module_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported module creation input formats
typedef enum _ze_module_format_t
{
    ZE_MODULE_FORMAT_IL_SPIRV = 0,                  ///< Format is SPIRV IL format
    ZE_MODULE_FORMAT_NATIVE,                        ///< Format is device native format

} ze_module_format_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Specialization constants - User defined constants
typedef struct _ze_module_constants_t
{
    uint32_t numConstants;                          ///< [in] Number of specialization constants.
    const uint32_t* pConstantIds;                   ///< [in] Pointer to array of IDs that is sized to numConstants.
    const uint64_t* pConstantValues;                ///< [in] Pointer to array of values that is sized to numConstants.

} ze_module_constants_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Module descriptor
typedef struct _ze_module_desc_t
{
    ze_module_desc_version_t version;               ///< [in] ::ZE_MODULE_DESC_VERSION_CURRENT
    ze_module_format_t format;                      ///< [in] Module format passed in with pInputModule
    size_t inputSize;                               ///< [in] size of input IL or ISA from pInputModule.
    const uint8_t* pInputModule;                    ///< [in] pointer to IL or ISA
    const char* pBuildFlags;                        ///< [in] string containing compiler flags. See programming guide for build
                                                    ///< flags.
    const ze_module_constants_t* pConstants;        ///< [in] pointer to specialization constants. Valid only for SPIR-V input.

} ze_module_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates module object from an input IL or native binary.
/// 
/// @details
///     - Compiles the module for execution on the device.
///     - The module can only be used on the device on which it was created.
///     - The module can be copied to other devices within the same driver
///       instance by using ::zeModuleGetNativeBinary.
///     - The following build options are supported:
///         + "-ze-opt-disable" - Disable optimizations
///         + "-ze-opt-greater-than-4GB-buffer-required" - Use 64-bit offset
///           calculations for buffers.
///         + "-ze-opt-large-register-file" - Increase number of registers
///           available to threads.
///     - A build log can optionally be returned to the caller. The caller is
///       responsible for destroying build log using ::zeModuleBuildLogDestroy.
///     - The module descriptor constants are only supported for SPIR-V
///       specialization constants.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuModuleLoad**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hDevice
///         + nullptr == desc
///         + nullptr == phModule
///         + invalid pDesc->format
///         + nullptr == pDesc->pInputModule
///         + nullptr == pDesc->phModule
///         + 0 == pDesc->inputSize
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + ::ZE_MODULE_DESC_VERSION_CURRENT < desc->version
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
///     - ::ZE_RESULT_ERROR_OUT_OF_DEVICE_MEMORY
///     - ::ZE_RESULT_ERROR_MODULE_BUILD_FAILURE
///         + Failure to build module. See build log for more details.
ze_result_t __zecall
zeModuleCreate(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const ze_module_desc_t* desc,                   ///< [in] pointer to module descriptor
    ze_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
    ze_module_build_log_handle_t* phBuildLog        ///< [out][optional] pointer to handle of module's build log.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys module
/// 
/// @details
///     - The application is responsible for making sure the device is not
///       currently referencing the module before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this module
///     - The application may **not** call this function from simultaneous
///       threads with the same module handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuModuleUnload**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModule
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeModuleDestroy(
    ze_module_handle_t hModule                      ///< [in][release] handle of the module
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys module build log object
/// 
/// @details
///     - The implementation of this function will immediately free all Host
///       allocations associated with this object
///     - The application may **not** call this function from simultaneous
///       threads with the same build log handle.
///     - The implementation of this function should be lock-free.
///     - This function can be called before or after ::zeModuleDestroy for the
///       associated module.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModuleBuildLog
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeModuleBuildLogDestroy(
    ze_module_build_log_handle_t hModuleBuildLog    ///< [in][release] handle of the module build log object.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieves text string for build log.
/// 
/// @details
///     - The caller can pass nullptr for pBuildLog when querying only for size.
///     - The caller must provide memory for build log.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModuleBuildLog
///         + nullptr == pSize
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeModuleBuildLogGetString(
    ze_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
    size_t* pSize,                                  ///< [in,out] size of build log string.
    char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve native binary from Module.
/// 
/// @details
///     - The native binary output can be cached to disk and new modules can be
///       later constructed from the cached copy.
///     - The native binary will retain debugging information that is associated
///       with a module.
///     - The caller can pass nullptr for pModuleNativeBinary when querying only
///       for size.
///     - The implementation will copy the native binary into a buffer supplied
///       by the caller.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModule
///         + nullptr == pSize
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeModuleGetNativeBinary(
    ze_module_handle_t hModule,                     ///< [in] handle of the module
    size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
    uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve global variable pointer from Module.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModule
///         + nullptr == pGlobalName
///         + nullptr == pptr
///         + invalid name
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeModuleGetGlobalPointer(
    ze_module_handle_t hModule,                     ///< [in] handle of the device
    const char* pGlobalName,                        ///< [in] name of global variable in module
    void** pptr                                     ///< [out] device visible pointer
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_kernel_desc_t
typedef enum _ze_kernel_desc_version_t
{
    ZE_KERNEL_DESC_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ),   ///< version 1.0

} ze_kernel_desc_version_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Supported kernel creation flags
typedef enum _ze_kernel_flag_t
{
    ZE_KERNEL_FLAG_NONE = 0,                        ///< default driver behavior
    ZE_KERNEL_FLAG_FORCE_RESIDENCY,                 ///< force all device allocations to be resident during execution

} ze_kernel_flag_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Kernel descriptor
typedef struct _ze_kernel_desc_t
{
    ze_kernel_desc_version_t version;               ///< [in] ::ZE_KERNEL_DESC_VERSION_CURRENT
    ze_kernel_flag_t flags;                         ///< [in] creation flags
    const char* pKernelName;                        ///< [in] null-terminated name of kernel in module

} ze_kernel_desc_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Create a kernel object from a module by name
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuModuleGetFunction**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModule
///         + nullptr == desc
///         + nullptr == phKernel
///         + nullptr == pDesc->pKernelName
///         + invalid value for pDesc->pKernelName
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
///         + ::ZE_KERNEL_DESC_VERSION_CURRENT < desc->version
ze_result_t __zecall
zeKernelCreate(
    ze_module_handle_t hModule,                     ///< [in] handle of the module
    const ze_kernel_desc_t* desc,                   ///< [in] pointer to kernel descriptor
    ze_kernel_handle_t* phKernel                    ///< [out] handle of the Function object
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Destroys a kernel object
/// 
/// @details
///     - All kernels must be destroyed before the module is destroyed.
///     - The application is responsible for making sure the device is not
///       currently referencing the kernel before it is deleted
///     - The implementation of this function will immediately free all Host and
///       Device allocations associated with this kernel
///     - The application may **not** call this function from simultaneous
///       threads with the same kernel handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hKernel
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeKernelDestroy(
    ze_kernel_handle_t hKernel                      ///< [in][release] handle of the kernel object
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve a function pointer from a module by name
/// 
/// @details
///     - The function pointer is unique for the device on which the module was
///       created.
///     - The function pointer is no longer valid if module is destroyed.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hModule
///         + nullptr == pFunctionName
///         + nullptr == pfnFunction
///         + invalid value pFunctionName. Function name must exist in Module.
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeModuleGetFunctionPointer(
    ze_module_handle_t hModule,                     ///< [in] handle of the module
    const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
    void** pfnFunction                              ///< [out] pointer to function.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set group size for a kernel
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same kernel handle.
///     - The implementation of this function should be lock-free.
///     - The implementation will copy the group size information into a command
///       list when the function is appended.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hKernel
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeKernelSetGroupSize(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this kernel
    uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this kernel
    uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this kernel
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Query a suggested group size for a kernel given a global size for each
///        dimension.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
///     - This function ignores the group size that is set using
///       ::zeKernelSetGroupSize.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hKernel
///         + nullptr == groupSizeX
///         + nullptr == groupSizeY
///         + nullptr == groupSizeZ
///         + invalid global width
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeKernelSuggestGroupSize(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    uint32_t globalSizeX,                           ///< [in] global width for X dimension
    uint32_t globalSizeY,                           ///< [in] global width for Y dimension
    uint32_t globalSizeZ,                           ///< [in] global width for Z dimension
    uint32_t* groupSizeX,                           ///< [out] recommended size of group for X dimension
    uint32_t* groupSizeY,                           ///< [out] recommended size of group for Y dimension
    uint32_t* groupSizeZ                            ///< [out] recommended size of group for Z dimension
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Query a suggested max group count a cooperative kernel.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hKernel
///         + nullptr == totalGroupCount
///         + invalid number of threads.
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeKernelSuggestMaxCooperativeGroupCount(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    uint32_t* totalGroupCount                       ///< [out] recommended total group count.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Set kernel argument used on kernel launch.
/// 
/// @details
///     - This function may **not** be called from simultaneous threads with the
///       same function handle.
///     - The implementation of this function should be lock-free.
///     - The implementation will copy the arguments into a command list when
///       the function is appended.
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hKernel
///         + invalid argument index
///         + invalid size specified
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeKernelSetArgumentValue(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
    size_t argSize,                                 ///< [in] size of argument type
    const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                    ///< null then argument value is considered null.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Kernel attributes
/// 
/// @remarks
///   _Analogues_
///     - **cl_kernel_exec_info**
typedef enum _ze_kernel_set_attribute_t
{
    ZE_KERNEL_SET_ATTR_INDIRECT_HOST_ACCESS = 0,    ///< Indicates that the function accesses host allocations indirectly
                                                    ///< (default: false)
    ZE_KERNEL_SET_ATTR_INDIRECT_DEVICE_ACCESS,      ///< Indicates that the function accesses device allocations indirectly
                                                    ///< (default: false)
    ZE_KERNEL_SET_ATTR_INDIRECT_SHARED_ACCESS,      ///< Indicates that the function accesses shared allocations indirectly
                                                    ///< (default: false)

} ze_kernel_set_attribute_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets a kernel attribute
/// 
/// @details
///     - This function may **not** be called from simultaneous threads with the
///       same function handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **clSetKernelExecInfo**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hKernel
///         + invalid value for attr
///         + invalid value for value
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeKernelSetAttribute(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    ze_kernel_set_attribute_t attr,                 ///< [in] attribute to set
    uint32_t value                                  ///< [in] attribute value to set
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Sets the preferred Intermediate cache configuration for a kernel.
/// 
/// @details
///     - The application may **not** call this function from simultaneous
///       threads with the same kernel handle.
/// 
/// @remarks
///   _Analogues_
///     - **cudaFuncSetCacheConfig **
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hKernel
///         + devices do not support CacheConfig
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeKernelSetIntermediateCacheConfig(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    ze_cache_config_t CacheConfig                   ///< [in] CacheConfig
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Kernel thread group dimensions.
typedef struct _ze_thread_group_dimensions_t
{
    uint32_t groupCountX;                           ///< [in] size of thread group in X dimension
    uint32_t groupCountY;                           ///< [in] size of thread group in Y dimension
    uint32_t groupCountZ;                           ///< [in] size of thread group in Z dimension

} ze_thread_group_dimensions_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief API version of ::ze_kernel_properties_t
typedef enum _ze_kernel_properties_version_t
{
    ZE_KERNEL_PROPERTIES_VERSION_CURRENT = ZE_MAKE_VERSION( 1, 0 ), ///< version 1.0

} ze_kernel_properties_version_t;

///////////////////////////////////////////////////////////////////////////////
#ifndef ZE_MAX_KERNEL_NAME
/// @brief Maximum device name string size
#define ZE_MAX_KERNEL_NAME  256
#endif // ZE_MAX_KERNEL_NAME

///////////////////////////////////////////////////////////////////////////////
/// @brief Kernel properties
typedef struct _ze_kernel_properties_t
{
    ze_kernel_properties_version_t version;         ///< [in] ::ZE_KERNEL_PROPERTIES_VERSION_CURRENT
    char name[ZE_MAX_KERNEL_NAME];                  ///< [out] Kernel name
    uint32_t numKernelArgs;                         ///< [out] number of kernel arguments.
    ze_thread_group_dimensions_t compileGroupSize;  ///< [out] group size from kernel attribute.

} ze_kernel_properties_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Retrieve kernel properties.
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuFuncGetAttribute**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hKernel
///         + nullptr == pKernelProperties
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeKernelGetProperties(
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    ze_kernel_properties_t* pKernelProperties       ///< [in,out] query result for kernel properties.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch kernel over one or more work groups.
/// 
/// @details
///     - This may **not** be called for a command list created with
///       ::ZE_COMMAND_LIST_FLAG_COPY_ONLY.
///     - This function may **not** be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuLaunchKernel**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hKernel
///         + nullptr == pLaunchFuncArgs
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeCommandListAppendLaunchKernel(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    const ze_thread_group_dimensions_t* pLaunchFuncArgs,///< [in] thread group launch arguments
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch kernel cooperatively over one or more work groups.
/// 
/// @details
///     - This may **not** be called for a command list created with
///       ::ZE_COMMAND_LIST_FLAG_COPY_ONLY.
///     - This may only be used for a command list that are submitted to command
///       queue with cooperative flag set.
///     - This function may **not** be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
///     - Use ::zeKernelSuggestMaxCooperativeGroupCount to recommend max group
///       count for device for cooperative functions that device supports.
/// 
/// @remarks
///   _Analogues_
///     - **cudaLaunchCooperativeKernel**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hKernel
///         + nullptr == pLaunchFuncArgs
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeCommandListAppendLaunchCooperativeKernel(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    const ze_thread_group_dimensions_t* pLaunchFuncArgs,///< [in] thread group launch arguments
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch kernel over one or more work groups using indirect arguments.
/// 
/// @details
///     - The launch arguments need to be device visible.
///     - The launch arguments buffer may not be reusued until the function has
///       completed on the device.
///     - This may **not** be called for a command list created with
///       ::ZE_COMMAND_LIST_FLAG_COPY_ONLY.
///     - This function may **not** be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuLaunchKernel**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == hKernel
///         + nullptr == pLaunchArgumentsBuffer
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeCommandListAppendLaunchKernelIndirect(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_kernel_handle_t hKernel,                     ///< [in] handle of the kernel object
    const ze_thread_group_dimensions_t* pLaunchArgumentsBuffer, ///< [in] pointer to device buffer that will contain thread group launch
                                                    ///< arguments
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch multiple kernels over one or more work groups using an array of
///        indirect arguments.
/// 
/// @details
///     - The array of launch arguments need to be device visible.
///     - The array of launch arguments buffer may not be reused until the
///       kernel has completed on the device.
///     - This may **not** be called for a command list created with
///       ::ZE_COMMAND_LIST_FLAG_COPY_ONLY.
///     - This function may **not** be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuLaunchKernel**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == phKernels
///         + nullptr == pCountBuffer
///         + nullptr == pLaunchArgumentsBuffer
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeCommandListAppendLaunchMultipleKernelsIndirect(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numKernels,                            ///< [in] maximum number of kernels to launch
    ze_kernel_handle_t* phKernels,                  ///< [in][range(0, numKernels)] handles of the kernel objects
    const uint32_t* pCountBuffer,                   ///< [in] pointer to device memory location that will contain the actual
                                                    ///< number of kernels to launch; value must be less-than or equal-to
                                                    ///< numKernels
    const ze_thread_group_dimensions_t* pLaunchArgumentsBuffer, ///< [in][range(0, numKernels)] pointer to device buffer that will contain
                                                    ///< a contiguous array of thread group launch arguments
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief type definition for host function pointers used with
///        ::zeCommandListAppendLaunchHostFunction
/// 
/// @details
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
typedef void(__zecall *ze_host_pfn_t)(
    void* pUserData                                 ///< [in] Pointer to user data to pass to host function.
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Launch host function. All work after this command in the command list
///        will block until host function completes.
/// 
/// @details
///     - This may **not** be called for a command list created with
///       ::ZE_COMMAND_LIST_FLAG_COPY_ONLY.
///     - This function may **not** be called from simultaneous threads with the
///       same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuLaunchHostFunc**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == pUserData
///     - ::ZE_RESULT_ERROR_UNSUPPORTED
ze_result_t __zecall
zeCommandListAppendLaunchHostFunction(
    ze_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    ze_host_pfn_t pfnHostFunc,                      ///< [in] pointer to host function.
    void* pUserData,                                ///< [in] pointer to user data to pass to host function.
    ze_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    ze_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    );

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _ZE_MODULE_H
