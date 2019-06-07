/**************************************************************************//**
*
* INTEL CONFIDENTIAL
* Copyright 2019
* Intel Corporation All Rights Reserved.
*
* The source code contained or described herein and all documents related to the
* source code ("Material") are owned by Intel Corporation or its suppliers or
* licensors. Title to the Material remains with Intel Corporation or its suppliers
* and licensors. The Material contains trade secrets and proprietary and confidential
* information of Intel or its suppliers and licensors. The Material is protected by
* worldwide copyright and trade secret laws and treaty provisions. No part of the
* Material may be used, copied, reproduced, modified, published, uploaded, posted
* transmitted, distributed, or disclosed in any way without Intel's prior express
* written permission.
*
* No license under any patent, copyright, trade secret or other intellectual
* property right is granted to or conferred upon you by disclosure or delivery
* of the Materials, either expressly, by implication, inducement, estoppel
* or otherwise. Any license under such intellectual property rights must be
* express and approved by Intel in writing.
*
* @file xe_ddi.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core
* @endcond
*
******************************************************************************/
#ifndef _XE_DDI_H
#define _XE_DDI_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_api.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeInit 
typedef xe_result_t (__xecall *xe_pfnInit_t)(
    xe_init_flag_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Global functions pointers
typedef struct _xe_global_dditable_t
{
    xe_pfnInit_t                                                pfnInit;
} xe_global_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Global table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetGlobalProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_global_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetGlobalProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetGlobalProcAddrTable_t)(
    xe_api_version_t,
    xe_global_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGet 
typedef xe_result_t (__xecall *xe_pfnDeviceGet_t)(
    xe_device_group_handle_t,
    uint32_t*,
    xe_device_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGetSubDevices 
typedef xe_result_t (__xecall *xe_pfnDeviceGetSubDevices_t)(
    xe_device_handle_t,
    uint32_t*,
    xe_device_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGetP2PProperties 
typedef xe_result_t (__xecall *xe_pfnDeviceGetP2PProperties_t)(
    xe_device_handle_t,
    xe_device_handle_t,
    xe_device_p2p_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceCanAccessPeer 
typedef xe_result_t (__xecall *xe_pfnDeviceCanAccessPeer_t)(
    xe_device_handle_t,
    xe_device_handle_t,
    xe_bool_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceSetIntermediateCacheConfig 
typedef xe_result_t (__xecall *xe_pfnDeviceSetIntermediateCacheConfig_t)(
    xe_device_handle_t,
    xe_cache_config_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceSetLastLevelCacheConfig 
typedef xe_result_t (__xecall *xe_pfnDeviceSetLastLevelCacheConfig_t)(
    xe_device_handle_t,
    xe_cache_config_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceSystemBarrier 
typedef xe_result_t (__xecall *xe_pfnDeviceSystemBarrier_t)(
    xe_device_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceRegisterCLMemory 
#if XE_ENABLE_OCL_INTEROP
typedef xe_result_t (__xecall *xe_pfnDeviceRegisterCLMemory_t)(
    xe_device_handle_t,
    cl_context,
    cl_mem,
    void**
    );
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceRegisterCLProgram 
#if XE_ENABLE_OCL_INTEROP
typedef xe_result_t (__xecall *xe_pfnDeviceRegisterCLProgram_t)(
    xe_device_handle_t,
    cl_context,
    cl_program,
    xe_module_handle_t*
    );
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceRegisterCLCommandQueue 
#if XE_ENABLE_OCL_INTEROP
typedef xe_result_t (__xecall *xe_pfnDeviceRegisterCLCommandQueue_t)(
    xe_device_handle_t,
    cl_context,
    cl_command_queue,
    xe_command_queue_handle_t*
    );
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceMakeMemoryResident 
typedef xe_result_t (__xecall *xe_pfnDeviceMakeMemoryResident_t)(
    xe_device_handle_t,
    void*,
    size_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceEvictMemory 
typedef xe_result_t (__xecall *xe_pfnDeviceEvictMemory_t)(
    xe_device_handle_t,
    void*,
    size_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceMakeImageResident 
typedef xe_result_t (__xecall *xe_pfnDeviceMakeImageResident_t)(
    xe_device_handle_t,
    xe_image_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceEvictImage 
typedef xe_result_t (__xecall *xe_pfnDeviceEvictImage_t)(
    xe_device_handle_t,
    xe_image_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Device functions pointers
typedef struct _xe_device_dditable_t
{
    xe_pfnDeviceGet_t                                           pfnGet;
    xe_pfnDeviceGetSubDevices_t                                 pfnGetSubDevices;
    xe_pfnDeviceGetP2PProperties_t                              pfnGetP2PProperties;
    xe_pfnDeviceCanAccessPeer_t                                 pfnCanAccessPeer;
    xe_pfnDeviceSetIntermediateCacheConfig_t                    pfnSetIntermediateCacheConfig;
    xe_pfnDeviceSetLastLevelCacheConfig_t                       pfnSetLastLevelCacheConfig;
    xe_pfnDeviceSystemBarrier_t                                 pfnSystemBarrier;
    #if XE_ENABLE_OCL_INTEROP
    xe_pfnDeviceRegisterCLMemory_t                              pfnRegisterCLMemory;
    #endif // XE_ENABLE_OCL_INTEROP
    #if XE_ENABLE_OCL_INTEROP
    xe_pfnDeviceRegisterCLProgram_t                             pfnRegisterCLProgram;
    #endif // XE_ENABLE_OCL_INTEROP
    #if XE_ENABLE_OCL_INTEROP
    xe_pfnDeviceRegisterCLCommandQueue_t                        pfnRegisterCLCommandQueue;
    #endif // XE_ENABLE_OCL_INTEROP
    xe_pfnDeviceMakeMemoryResident_t                            pfnMakeMemoryResident;
    xe_pfnDeviceEvictMemory_t                                   pfnEvictMemory;
    xe_pfnDeviceMakeImageResident_t                             pfnMakeImageResident;
    xe_pfnDeviceEvictImage_t                                    pfnEvictImage;
} xe_device_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetDeviceProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_device_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetDeviceProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetDeviceProcAddrTable_t)(
    xe_api_version_t,
    xe_device_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGroupGet 
typedef xe_result_t (__xecall *xe_pfnDeviceGroupGet_t)(
    uint32_t*,
    xe_device_group_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGroupGetDriverVersion 
typedef xe_result_t (__xecall *xe_pfnDeviceGroupGetDriverVersion_t)(
    xe_device_group_handle_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGroupGetApiVersion 
typedef xe_result_t (__xecall *xe_pfnDeviceGroupGetApiVersion_t)(
    xe_device_group_handle_t,
    xe_api_version_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGroupGetDeviceProperties 
typedef xe_result_t (__xecall *xe_pfnDeviceGroupGetDeviceProperties_t)(
    xe_device_group_handle_t,
    xe_device_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGroupGetComputeProperties 
typedef xe_result_t (__xecall *xe_pfnDeviceGroupGetComputeProperties_t)(
    xe_device_group_handle_t,
    xe_device_compute_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGroupGetMemoryProperties 
typedef xe_result_t (__xecall *xe_pfnDeviceGroupGetMemoryProperties_t)(
    xe_device_group_handle_t,
    uint32_t*,
    xe_device_memory_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGroupGetMemoryAccessProperties 
typedef xe_result_t (__xecall *xe_pfnDeviceGroupGetMemoryAccessProperties_t)(
    xe_device_group_handle_t,
    xe_device_memory_access_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGroupGetCacheProperties 
typedef xe_result_t (__xecall *xe_pfnDeviceGroupGetCacheProperties_t)(
    xe_device_group_handle_t,
    xe_device_cache_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGroupGetImageProperties 
typedef xe_result_t (__xecall *xe_pfnDeviceGroupGetImageProperties_t)(
    xe_device_group_handle_t,
    xe_device_image_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGroupAllocSharedMem 
typedef xe_result_t (__xecall *xe_pfnDeviceGroupAllocSharedMem_t)(
    xe_device_group_handle_t,
    xe_device_handle_t,
    xe_device_mem_alloc_flag_t,
    uint32_t,
    xe_host_mem_alloc_flag_t,
    size_t,
    size_t,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGroupAllocDeviceMem 
typedef xe_result_t (__xecall *xe_pfnDeviceGroupAllocDeviceMem_t)(
    xe_device_group_handle_t,
    xe_device_handle_t,
    xe_device_mem_alloc_flag_t,
    uint32_t,
    size_t,
    size_t,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGroupAllocHostMem 
typedef xe_result_t (__xecall *xe_pfnDeviceGroupAllocHostMem_t)(
    xe_device_group_handle_t,
    xe_host_mem_alloc_flag_t,
    size_t,
    size_t,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGroupFreeMem 
typedef xe_result_t (__xecall *xe_pfnDeviceGroupFreeMem_t)(
    xe_device_group_handle_t,
    void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGroupGetMemProperties 
typedef xe_result_t (__xecall *xe_pfnDeviceGroupGetMemProperties_t)(
    xe_device_group_handle_t,
    const void*,
    xe_memory_allocation_properties_t*,
    xe_device_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGroupGetMemAddressRange 
typedef xe_result_t (__xecall *xe_pfnDeviceGroupGetMemAddressRange_t)(
    xe_device_group_handle_t,
    const void*,
    void**,
    size_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGroupGetMemIpcHandle 
typedef xe_result_t (__xecall *xe_pfnDeviceGroupGetMemIpcHandle_t)(
    xe_device_group_handle_t,
    const void*,
    xe_ipc_mem_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGroupOpenMemIpcHandle 
typedef xe_result_t (__xecall *xe_pfnDeviceGroupOpenMemIpcHandle_t)(
    xe_device_group_handle_t,
    xe_device_handle_t,
    xe_ipc_mem_handle_t,
    xe_ipc_memory_flag_t,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeDeviceGroupCloseMemIpcHandle 
typedef xe_result_t (__xecall *xe_pfnDeviceGroupCloseMemIpcHandle_t)(
    xe_device_group_handle_t,
    const void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of DeviceGroup functions pointers
typedef struct _xe_device_group_dditable_t
{
    xe_pfnDeviceGroupGet_t                                      pfnGet;
    xe_pfnDeviceGroupGetDriverVersion_t                         pfnGetDriverVersion;
    xe_pfnDeviceGroupGetApiVersion_t                            pfnGetApiVersion;
    xe_pfnDeviceGroupGetDeviceProperties_t                      pfnGetDeviceProperties;
    xe_pfnDeviceGroupGetComputeProperties_t                     pfnGetComputeProperties;
    xe_pfnDeviceGroupGetMemoryProperties_t                      pfnGetMemoryProperties;
    xe_pfnDeviceGroupGetMemoryAccessProperties_t                pfnGetMemoryAccessProperties;
    xe_pfnDeviceGroupGetCacheProperties_t                       pfnGetCacheProperties;
    xe_pfnDeviceGroupGetImageProperties_t                       pfnGetImageProperties;
    xe_pfnDeviceGroupAllocSharedMem_t                           pfnAllocSharedMem;
    xe_pfnDeviceGroupAllocDeviceMem_t                           pfnAllocDeviceMem;
    xe_pfnDeviceGroupAllocHostMem_t                             pfnAllocHostMem;
    xe_pfnDeviceGroupFreeMem_t                                  pfnFreeMem;
    xe_pfnDeviceGroupGetMemProperties_t                         pfnGetMemProperties;
    xe_pfnDeviceGroupGetMemAddressRange_t                       pfnGetMemAddressRange;
    xe_pfnDeviceGroupGetMemIpcHandle_t                          pfnGetMemIpcHandle;
    xe_pfnDeviceGroupOpenMemIpcHandle_t                         pfnOpenMemIpcHandle;
    xe_pfnDeviceGroupCloseMemIpcHandle_t                        pfnCloseMemIpcHandle;
} xe_device_group_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's DeviceGroup table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetDeviceGroupProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_device_group_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetDeviceGroupProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetDeviceGroupProcAddrTable_t)(
    xe_api_version_t,
    xe_device_group_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandQueueCreate 
typedef xe_result_t (__xecall *xe_pfnCommandQueueCreate_t)(
    xe_device_handle_t,
    const xe_command_queue_desc_t*,
    xe_command_queue_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandQueueDestroy 
typedef xe_result_t (__xecall *xe_pfnCommandQueueDestroy_t)(
    xe_command_queue_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandQueueExecuteCommandLists 
typedef xe_result_t (__xecall *xe_pfnCommandQueueExecuteCommandLists_t)(
    xe_command_queue_handle_t,
    uint32_t,
    xe_command_list_handle_t*,
    xe_fence_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandQueueSynchronize 
typedef xe_result_t (__xecall *xe_pfnCommandQueueSynchronize_t)(
    xe_command_queue_handle_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandQueue functions pointers
typedef struct _xe_command_queue_dditable_t
{
    xe_pfnCommandQueueCreate_t                                  pfnCreate;
    xe_pfnCommandQueueDestroy_t                                 pfnDestroy;
    xe_pfnCommandQueueExecuteCommandLists_t                     pfnExecuteCommandLists;
    xe_pfnCommandQueueSynchronize_t                             pfnSynchronize;
} xe_command_queue_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandQueue table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetCommandQueueProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_command_queue_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetCommandQueueProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetCommandQueueProcAddrTable_t)(
    xe_api_version_t,
    xe_command_queue_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListCreate 
typedef xe_result_t (__xecall *xe_pfnCommandListCreate_t)(
    xe_device_handle_t,
    const xe_command_list_desc_t*,
    xe_command_list_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListCreateImmediate 
typedef xe_result_t (__xecall *xe_pfnCommandListCreateImmediate_t)(
    xe_device_handle_t,
    const xe_command_queue_desc_t*,
    xe_command_list_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListDestroy 
typedef xe_result_t (__xecall *xe_pfnCommandListDestroy_t)(
    xe_command_list_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListClose 
typedef xe_result_t (__xecall *xe_pfnCommandListClose_t)(
    xe_command_list_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListReset 
typedef xe_result_t (__xecall *xe_pfnCommandListReset_t)(
    xe_command_list_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListSetParameter 
typedef xe_result_t (__xecall *xe_pfnCommandListSetParameter_t)(
    xe_command_list_handle_t,
    xe_command_list_parameter_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListGetParameter 
typedef xe_result_t (__xecall *xe_pfnCommandListGetParameter_t)(
    xe_command_list_handle_t,
    xe_command_list_parameter_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListResetParameters 
typedef xe_result_t (__xecall *xe_pfnCommandListResetParameters_t)(
    xe_command_list_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListReserveSpace 
typedef xe_result_t (__xecall *xe_pfnCommandListReserveSpace_t)(
    xe_command_list_handle_t,
    size_t,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListAppendBarrier 
typedef xe_result_t (__xecall *xe_pfnCommandListAppendBarrier_t)(
    xe_command_list_handle_t,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListAppendMemoryRangesBarrier 
typedef xe_result_t (__xecall *xe_pfnCommandListAppendMemoryRangesBarrier_t)(
    xe_command_list_handle_t,
    uint32_t,
    const size_t*,
    const void**,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListAppendMemoryCopy 
typedef xe_result_t (__xecall *xe_pfnCommandListAppendMemoryCopy_t)(
    xe_command_list_handle_t,
    void*,
    const void*,
    size_t,
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListAppendMemorySet 
typedef xe_result_t (__xecall *xe_pfnCommandListAppendMemorySet_t)(
    xe_command_list_handle_t,
    void*,
    int,
    size_t,
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListAppendMemoryCopyRegion 
typedef xe_result_t (__xecall *xe_pfnCommandListAppendMemoryCopyRegion_t)(
    xe_command_list_handle_t,
    void*,
    xe_copy_region_t*,
    uint32_t,
    const void*,
    xe_copy_region_t*,
    uint32_t,
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListAppendImageCopy 
typedef xe_result_t (__xecall *xe_pfnCommandListAppendImageCopy_t)(
    xe_command_list_handle_t,
    xe_image_handle_t,
    xe_image_handle_t,
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListAppendImageCopyRegion 
typedef xe_result_t (__xecall *xe_pfnCommandListAppendImageCopyRegion_t)(
    xe_command_list_handle_t,
    xe_image_handle_t,
    xe_image_handle_t,
    xe_image_region_t*,
    xe_image_region_t*,
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListAppendImageCopyToMemory 
typedef xe_result_t (__xecall *xe_pfnCommandListAppendImageCopyToMemory_t)(
    xe_command_list_handle_t,
    void*,
    xe_image_handle_t,
    xe_image_region_t*,
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListAppendImageCopyFromMemory 
typedef xe_result_t (__xecall *xe_pfnCommandListAppendImageCopyFromMemory_t)(
    xe_command_list_handle_t,
    xe_image_handle_t,
    const void*,
    xe_image_region_t*,
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListAppendMemoryPrefetch 
typedef xe_result_t (__xecall *xe_pfnCommandListAppendMemoryPrefetch_t)(
    xe_command_list_handle_t,
    const void*,
    size_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListAppendMemAdvise 
typedef xe_result_t (__xecall *xe_pfnCommandListAppendMemAdvise_t)(
    xe_command_list_handle_t,
    xe_device_handle_t,
    const void*,
    size_t,
    xe_memory_advice_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListAppendSignalEvent 
typedef xe_result_t (__xecall *xe_pfnCommandListAppendSignalEvent_t)(
    xe_command_list_handle_t,
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListAppendWaitOnEvents 
typedef xe_result_t (__xecall *xe_pfnCommandListAppendWaitOnEvents_t)(
    xe_command_list_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListAppendEventReset 
typedef xe_result_t (__xecall *xe_pfnCommandListAppendEventReset_t)(
    xe_command_list_handle_t,
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListAppendLaunchFunction 
typedef xe_result_t (__xecall *xe_pfnCommandListAppendLaunchFunction_t)(
    xe_command_list_handle_t,
    xe_function_handle_t,
    const xe_thread_group_dimensions_t*,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListAppendLaunchFunctionIndirect 
typedef xe_result_t (__xecall *xe_pfnCommandListAppendLaunchFunctionIndirect_t)(
    xe_command_list_handle_t,
    xe_function_handle_t,
    const xe_thread_group_dimensions_t*,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListAppendLaunchMultipleFunctionsIndirect 
typedef xe_result_t (__xecall *xe_pfnCommandListAppendLaunchMultipleFunctionsIndirect_t)(
    xe_command_list_handle_t,
    uint32_t,
    xe_function_handle_t*,
    const uint32_t*,
    const xe_thread_group_dimensions_t*,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeCommandListAppendLaunchHostFunction 
typedef xe_result_t (__xecall *xe_pfnCommandListAppendLaunchHostFunction_t)(
    xe_command_list_handle_t,
    xe_host_pfn_t,
    void*,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of CommandList functions pointers
typedef struct _xe_command_list_dditable_t
{
    xe_pfnCommandListCreate_t                                   pfnCreate;
    xe_pfnCommandListCreateImmediate_t                          pfnCreateImmediate;
    xe_pfnCommandListDestroy_t                                  pfnDestroy;
    xe_pfnCommandListClose_t                                    pfnClose;
    xe_pfnCommandListReset_t                                    pfnReset;
    xe_pfnCommandListSetParameter_t                             pfnSetParameter;
    xe_pfnCommandListGetParameter_t                             pfnGetParameter;
    xe_pfnCommandListResetParameters_t                          pfnResetParameters;
    xe_pfnCommandListReserveSpace_t                             pfnReserveSpace;
    xe_pfnCommandListAppendBarrier_t                            pfnAppendBarrier;
    xe_pfnCommandListAppendMemoryRangesBarrier_t                pfnAppendMemoryRangesBarrier;
    xe_pfnCommandListAppendMemoryCopy_t                         pfnAppendMemoryCopy;
    xe_pfnCommandListAppendMemorySet_t                          pfnAppendMemorySet;
    xe_pfnCommandListAppendMemoryCopyRegion_t                   pfnAppendMemoryCopyRegion;
    xe_pfnCommandListAppendImageCopy_t                          pfnAppendImageCopy;
    xe_pfnCommandListAppendImageCopyRegion_t                    pfnAppendImageCopyRegion;
    xe_pfnCommandListAppendImageCopyToMemory_t                  pfnAppendImageCopyToMemory;
    xe_pfnCommandListAppendImageCopyFromMemory_t                pfnAppendImageCopyFromMemory;
    xe_pfnCommandListAppendMemoryPrefetch_t                     pfnAppendMemoryPrefetch;
    xe_pfnCommandListAppendMemAdvise_t                          pfnAppendMemAdvise;
    xe_pfnCommandListAppendSignalEvent_t                        pfnAppendSignalEvent;
    xe_pfnCommandListAppendWaitOnEvents_t                       pfnAppendWaitOnEvents;
    xe_pfnCommandListAppendEventReset_t                         pfnAppendEventReset;
    xe_pfnCommandListAppendLaunchFunction_t                     pfnAppendLaunchFunction;
    xe_pfnCommandListAppendLaunchFunctionIndirect_t             pfnAppendLaunchFunctionIndirect;
    xe_pfnCommandListAppendLaunchMultipleFunctionsIndirect_t    pfnAppendLaunchMultipleFunctionsIndirect;
    xe_pfnCommandListAppendLaunchHostFunction_t                 pfnAppendLaunchHostFunction;
} xe_command_list_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetCommandListProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_command_list_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetCommandListProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetCommandListProcAddrTable_t)(
    xe_api_version_t,
    xe_command_list_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeFenceCreate 
typedef xe_result_t (__xecall *xe_pfnFenceCreate_t)(
    xe_command_queue_handle_t,
    const xe_fence_desc_t*,
    xe_fence_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeFenceDestroy 
typedef xe_result_t (__xecall *xe_pfnFenceDestroy_t)(
    xe_fence_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeFenceHostSynchronize 
typedef xe_result_t (__xecall *xe_pfnFenceHostSynchronize_t)(
    xe_fence_handle_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeFenceQueryStatus 
typedef xe_result_t (__xecall *xe_pfnFenceQueryStatus_t)(
    xe_fence_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeFenceReset 
typedef xe_result_t (__xecall *xe_pfnFenceReset_t)(
    xe_fence_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Fence functions pointers
typedef struct _xe_fence_dditable_t
{
    xe_pfnFenceCreate_t                                         pfnCreate;
    xe_pfnFenceDestroy_t                                        pfnDestroy;
    xe_pfnFenceHostSynchronize_t                                pfnHostSynchronize;
    xe_pfnFenceQueryStatus_t                                    pfnQueryStatus;
    xe_pfnFenceReset_t                                          pfnReset;
} xe_fence_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Fence table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetFenceProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_fence_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetFenceProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetFenceProcAddrTable_t)(
    xe_api_version_t,
    xe_fence_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeEventPoolCreate 
typedef xe_result_t (__xecall *xe_pfnEventPoolCreate_t)(
    xe_device_group_handle_t,
    const xe_event_pool_desc_t*,
    uint32_t,
    xe_device_handle_t*,
    xe_event_pool_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeEventPoolDestroy 
typedef xe_result_t (__xecall *xe_pfnEventPoolDestroy_t)(
    xe_event_pool_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeEventPoolGetIpcHandle 
typedef xe_result_t (__xecall *xe_pfnEventPoolGetIpcHandle_t)(
    xe_event_pool_handle_t,
    xe_ipc_event_pool_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeEventPoolOpenIpcHandle 
typedef xe_result_t (__xecall *xe_pfnEventPoolOpenIpcHandle_t)(
    xe_device_handle_t,
    xe_ipc_event_pool_handle_t,
    xe_event_pool_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeEventPoolCloseIpcHandle 
typedef xe_result_t (__xecall *xe_pfnEventPoolCloseIpcHandle_t)(
    xe_event_pool_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of EventPool functions pointers
typedef struct _xe_event_pool_dditable_t
{
    xe_pfnEventPoolCreate_t                                     pfnCreate;
    xe_pfnEventPoolDestroy_t                                    pfnDestroy;
    xe_pfnEventPoolGetIpcHandle_t                               pfnGetIpcHandle;
    xe_pfnEventPoolOpenIpcHandle_t                              pfnOpenIpcHandle;
    xe_pfnEventPoolCloseIpcHandle_t                             pfnCloseIpcHandle;
} xe_event_pool_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's EventPool table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetEventPoolProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_event_pool_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetEventPoolProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetEventPoolProcAddrTable_t)(
    xe_api_version_t,
    xe_event_pool_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeEventCreate 
typedef xe_result_t (__xecall *xe_pfnEventCreate_t)(
    xe_event_pool_handle_t,
    const xe_event_desc_t*,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeEventDestroy 
typedef xe_result_t (__xecall *xe_pfnEventDestroy_t)(
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeEventHostSignal 
typedef xe_result_t (__xecall *xe_pfnEventHostSignal_t)(
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeEventHostSynchronize 
typedef xe_result_t (__xecall *xe_pfnEventHostSynchronize_t)(
    xe_event_handle_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeEventQueryStatus 
typedef xe_result_t (__xecall *xe_pfnEventQueryStatus_t)(
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeEventReset 
typedef xe_result_t (__xecall *xe_pfnEventReset_t)(
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Event functions pointers
typedef struct _xe_event_dditable_t
{
    xe_pfnEventCreate_t                                         pfnCreate;
    xe_pfnEventDestroy_t                                        pfnDestroy;
    xe_pfnEventHostSignal_t                                     pfnHostSignal;
    xe_pfnEventHostSynchronize_t                                pfnHostSynchronize;
    xe_pfnEventQueryStatus_t                                    pfnQueryStatus;
    xe_pfnEventReset_t                                          pfnReset;
} xe_event_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Event table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetEventProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_event_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetEventProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetEventProcAddrTable_t)(
    xe_api_version_t,
    xe_event_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeImageGetProperties 
typedef xe_result_t (__xecall *xe_pfnImageGetProperties_t)(
    xe_device_handle_t,
    const xe_image_desc_t*,
    xe_image_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeImageCreate 
typedef xe_result_t (__xecall *xe_pfnImageCreate_t)(
    xe_device_handle_t,
    const xe_image_desc_t*,
    xe_image_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeImageDestroy 
typedef xe_result_t (__xecall *xe_pfnImageDestroy_t)(
    xe_image_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Image functions pointers
typedef struct _xe_image_dditable_t
{
    xe_pfnImageGetProperties_t                                  pfnGetProperties;
    xe_pfnImageCreate_t                                         pfnCreate;
    xe_pfnImageDestroy_t                                        pfnDestroy;
} xe_image_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Image table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetImageProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_image_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetImageProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetImageProcAddrTable_t)(
    xe_api_version_t,
    xe_image_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeModuleCreate 
typedef xe_result_t (__xecall *xe_pfnModuleCreate_t)(
    xe_device_handle_t,
    const xe_module_desc_t*,
    xe_module_handle_t*,
    xe_module_build_log_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeModuleDestroy 
typedef xe_result_t (__xecall *xe_pfnModuleDestroy_t)(
    xe_module_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeModuleGetNativeBinary 
typedef xe_result_t (__xecall *xe_pfnModuleGetNativeBinary_t)(
    xe_module_handle_t,
    size_t*,
    uint8_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeModuleGetGlobalPointer 
typedef xe_result_t (__xecall *xe_pfnModuleGetGlobalPointer_t)(
    xe_module_handle_t,
    const char*,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeModuleGetFunctionPointer 
typedef xe_result_t (__xecall *xe_pfnModuleGetFunctionPointer_t)(
    xe_module_handle_t,
    const char*,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Module functions pointers
typedef struct _xe_module_dditable_t
{
    xe_pfnModuleCreate_t                                        pfnCreate;
    xe_pfnModuleDestroy_t                                       pfnDestroy;
    xe_pfnModuleGetNativeBinary_t                               pfnGetNativeBinary;
    xe_pfnModuleGetGlobalPointer_t                              pfnGetGlobalPointer;
    xe_pfnModuleGetFunctionPointer_t                            pfnGetFunctionPointer;
} xe_module_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetModuleProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_module_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetModuleProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetModuleProcAddrTable_t)(
    xe_api_version_t,
    xe_module_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeModuleBuildLogDestroy 
typedef xe_result_t (__xecall *xe_pfnModuleBuildLogDestroy_t)(
    xe_module_build_log_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeModuleBuildLogGetString 
typedef xe_result_t (__xecall *xe_pfnModuleBuildLogGetString_t)(
    xe_module_build_log_handle_t,
    size_t*,
    char*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of ModuleBuildLog functions pointers
typedef struct _xe_module_build_log_dditable_t
{
    xe_pfnModuleBuildLogDestroy_t                               pfnDestroy;
    xe_pfnModuleBuildLogGetString_t                             pfnGetString;
} xe_module_build_log_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's ModuleBuildLog table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetModuleBuildLogProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_module_build_log_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetModuleBuildLogProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetModuleBuildLogProcAddrTable_t)(
    xe_api_version_t,
    xe_module_build_log_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeFunctionCreate 
typedef xe_result_t (__xecall *xe_pfnFunctionCreate_t)(
    xe_module_handle_t,
    const xe_function_desc_t*,
    xe_function_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeFunctionDestroy 
typedef xe_result_t (__xecall *xe_pfnFunctionDestroy_t)(
    xe_function_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeFunctionSetGroupSize 
typedef xe_result_t (__xecall *xe_pfnFunctionSetGroupSize_t)(
    xe_function_handle_t,
    uint32_t,
    uint32_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeFunctionSuggestGroupSize 
typedef xe_result_t (__xecall *xe_pfnFunctionSuggestGroupSize_t)(
    xe_function_handle_t,
    uint32_t,
    uint32_t,
    uint32_t,
    uint32_t*,
    uint32_t*,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeFunctionSetArgumentValue 
typedef xe_result_t (__xecall *xe_pfnFunctionSetArgumentValue_t)(
    xe_function_handle_t,
    uint32_t,
    size_t,
    const void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeFunctionSetAttribute 
typedef xe_result_t (__xecall *xe_pfnFunctionSetAttribute_t)(
    xe_function_handle_t,
    xe_function_set_attribute_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeFunctionGetAttribute 
typedef xe_result_t (__xecall *xe_pfnFunctionGetAttribute_t)(
    xe_function_handle_t,
    xe_function_get_attribute_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Function functions pointers
typedef struct _xe_function_dditable_t
{
    xe_pfnFunctionCreate_t                                      pfnCreate;
    xe_pfnFunctionDestroy_t                                     pfnDestroy;
    xe_pfnFunctionSetGroupSize_t                                pfnSetGroupSize;
    xe_pfnFunctionSuggestGroupSize_t                            pfnSuggestGroupSize;
    xe_pfnFunctionSetArgumentValue_t                            pfnSetArgumentValue;
    xe_pfnFunctionSetAttribute_t                                pfnSetAttribute;
    xe_pfnFunctionGetAttribute_t                                pfnGetAttribute;
} xe_function_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Function table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetFunctionProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_function_dditable_t* pDdiTable               ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetFunctionProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetFunctionProcAddrTable_t)(
    xe_api_version_t,
    xe_function_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeSamplerCreate 
typedef xe_result_t (__xecall *xe_pfnSamplerCreate_t)(
    xe_device_handle_t,
    const xe_sampler_desc_t*,
    xe_sampler_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeSamplerDestroy 
typedef xe_result_t (__xecall *xe_pfnSamplerDestroy_t)(
    xe_sampler_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Table of Sampler functions pointers
typedef struct _xe_sampler_dditable_t
{
    xe_pfnSamplerCreate_t                                       pfnCreate;
    xe_pfnSamplerDestroy_t                                      pfnDestroy;
} xe_sampler_dditable_t;

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sampler table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetSamplerProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_sampler_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Function-pointer for xeGetSamplerProcAddrTable
typedef xe_result_t (__xecall *xe_pfnGetSamplerProcAddrTable_t)(
    xe_api_version_t,
    xe_sampler_dditable_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief Container for all DDI tables
typedef struct _xe_dditable_t
{
    xe_global_dditable_t                Global;
    xe_device_dditable_t                Device;
    xe_device_group_dditable_t          DeviceGroup;
    xe_command_queue_dditable_t         CommandQueue;
    xe_command_list_dditable_t          CommandList;
    xe_fence_dditable_t                 Fence;
    xe_event_pool_dditable_t            EventPool;
    xe_event_dditable_t                 Event;
    xe_image_dditable_t                 Image;
    xe_module_dditable_t                Module;
    xe_module_build_log_dditable_t      ModuleBuildLog;
    xe_function_dditable_t              Function;
    xe_sampler_dditable_t               Sampler;
} xe_dditable_t;

#if defined(__cplusplus)
} // extern "C"
#endif

#endif // _XE_DDI_H