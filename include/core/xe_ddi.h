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

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListAppendBarrier function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListAppendBarrier_t)(
    xe_command_list_handle_t,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListAppendMemoryRangesBarrier function-pointer
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
/// @brief xeDeviceSystemBarrier function-pointer
typedef xe_result_t (__xecall *xe_pfnDeviceSystemBarrier_t)(
    xe_device_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
/// @brief xeDeviceRegisterCLMemory function-pointer
typedef xe_result_t (__xecall *xe_pfnDeviceRegisterCLMemory_t)(
    xe_device_handle_t,
    cl_context,
    cl_mem,
    void**
    );
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
/// @brief xeDeviceRegisterCLProgram function-pointer
typedef xe_result_t (__xecall *xe_pfnDeviceRegisterCLProgram_t)(
    xe_device_handle_t,
    cl_context,
    cl_program,
    xe_module_handle_t*
    );
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
/// @brief xeDeviceRegisterCLCommandQueue function-pointer
typedef xe_result_t (__xecall *xe_pfnDeviceRegisterCLCommandQueue_t)(
    xe_device_handle_t,
    cl_context,
    cl_command_queue,
    xe_command_queue_handle_t*
    );
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListCreate function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListCreate_t)(
    xe_device_handle_t,
    const xe_command_list_desc_t*,
    xe_command_list_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListCreateImmediate function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListCreateImmediate_t)(
    xe_device_handle_t,
    const xe_command_queue_desc_t*,
    xe_command_list_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListDestroy function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListDestroy_t)(
    xe_command_list_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListClose function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListClose_t)(
    xe_command_list_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListReset function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListReset_t)(
    xe_command_list_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListSetParameter function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListSetParameter_t)(
    xe_command_list_handle_t,
    xe_command_list_parameter_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListGetParameter function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListGetParameter_t)(
    xe_command_list_handle_t,
    xe_command_list_parameter_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListResetParameters function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListResetParameters_t)(
    xe_command_list_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListReserveSpace function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListReserveSpace_t)(
    xe_command_list_handle_t,
    size_t,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandQueueCreate function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandQueueCreate_t)(
    xe_device_handle_t,
    const xe_command_queue_desc_t*,
    xe_command_queue_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandQueueDestroy function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandQueueDestroy_t)(
    xe_command_queue_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandQueueExecuteCommandLists function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandQueueExecuteCommandLists_t)(
    xe_command_queue_handle_t,
    uint32_t,
    xe_command_list_handle_t*,
    xe_fence_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandQueueSynchronize function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandQueueSynchronize_t)(
    xe_command_queue_handle_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListAppendMemoryCopy function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListAppendMemoryCopy_t)(
    xe_command_list_handle_t,
    void*,
    const void*,
    size_t,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListAppendMemorySet function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListAppendMemorySet_t)(
    xe_command_list_handle_t,
    void*,
    int,
    size_t,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListAppendImageCopy function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListAppendImageCopy_t)(
    xe_command_list_handle_t,
    xe_image_handle_t,
    xe_image_handle_t,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListAppendImageCopyRegion function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListAppendImageCopyRegion_t)(
    xe_command_list_handle_t,
    xe_image_handle_t,
    xe_image_handle_t,
    xe_image_region_t*,
    xe_image_region_t*,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListAppendImageCopyToMemory function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListAppendImageCopyToMemory_t)(
    xe_command_list_handle_t,
    void*,
    xe_image_handle_t,
    xe_image_region_t*,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListAppendImageCopyFromMemory function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListAppendImageCopyFromMemory_t)(
    xe_command_list_handle_t,
    xe_image_handle_t,
    const void*,
    xe_image_region_t*,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListAppendMemoryPrefetch function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListAppendMemoryPrefetch_t)(
    xe_command_list_handle_t,
    const void*,
    size_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListAppendMemAdvise function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListAppendMemAdvise_t)(
    xe_command_list_handle_t,
    xe_device_handle_t,
    const void*,
    size_t,
    xe_memory_advice_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeDeviceGetCount function-pointer
typedef xe_result_t (__xecall *xe_pfnDeviceGetCount_t)(
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeDeviceGet function-pointer
typedef xe_result_t (__xecall *xe_pfnDeviceGet_t)(
    uint32_t,
    xe_device_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeDeviceGetSubDevice function-pointer
typedef xe_result_t (__xecall *xe_pfnDeviceGetSubDevice_t)(
    xe_device_handle_t,
    uint32_t,
    xe_device_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeDeviceGetApiVersion function-pointer
typedef xe_result_t (__xecall *xe_pfnDeviceGetApiVersion_t)(
    xe_device_handle_t,
    xe_api_version_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeDeviceGetProperties function-pointer
typedef xe_result_t (__xecall *xe_pfnDeviceGetProperties_t)(
    xe_device_handle_t,
    xe_device_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeDeviceGetComputeProperties function-pointer
typedef xe_result_t (__xecall *xe_pfnDeviceGetComputeProperties_t)(
    xe_device_handle_t,
    xe_device_compute_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeDeviceGetMemoryProperties function-pointer
typedef xe_result_t (__xecall *xe_pfnDeviceGetMemoryProperties_t)(
    xe_device_handle_t,
    xe_device_memory_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeDeviceGetP2PProperties function-pointer
typedef xe_result_t (__xecall *xe_pfnDeviceGetP2PProperties_t)(
    xe_device_handle_t,
    xe_device_handle_t,
    xe_device_p2p_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeDeviceCanAccessPeer function-pointer
typedef xe_result_t (__xecall *xe_pfnDeviceCanAccessPeer_t)(
    xe_device_handle_t,
    xe_device_handle_t,
    xe_bool_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeDeviceSetIntermediateCacheConfig function-pointer
typedef xe_result_t (__xecall *xe_pfnDeviceSetIntermediateCacheConfig_t)(
    xe_device_handle_t,
    xe_cache_config_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeDeviceSetLastLevelCacheConfig function-pointer
typedef xe_result_t (__xecall *xe_pfnDeviceSetLastLevelCacheConfig_t)(
    xe_device_handle_t,
    xe_cache_config_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeInit function-pointer
typedef xe_result_t (__xecall *xe_pfnInit_t)(
    xe_init_flag_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeGetDriverVersion function-pointer
typedef xe_result_t (__xecall *xe_pfnGetDriverVersion_t)(
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeEventPoolCreate function-pointer
typedef xe_result_t (__xecall *xe_pfnEventPoolCreate_t)(
    xe_device_handle_t,
    const xe_event_pool_desc_t*,
    xe_event_pool_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeEventPoolDestroy function-pointer
typedef xe_result_t (__xecall *xe_pfnEventPoolDestroy_t)(
    xe_event_pool_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeEventCreate function-pointer
typedef xe_result_t (__xecall *xe_pfnEventCreate_t)(
    xe_event_pool_handle_t,
    const xe_event_desc_t*,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeEventDestroy function-pointer
typedef xe_result_t (__xecall *xe_pfnEventDestroy_t)(
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeEventPoolGetIpcHandle function-pointer
typedef xe_result_t (__xecall *xe_pfnEventPoolGetIpcHandle_t)(
    xe_event_pool_handle_t,
    xe_ipc_event_pool_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeEventPoolOpenIpcHandle function-pointer
typedef xe_result_t (__xecall *xe_pfnEventPoolOpenIpcHandle_t)(
    xe_device_handle_t,
    xe_ipc_event_pool_handle_t,
    xe_event_pool_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeEventPoolCloseIpcHandle function-pointer
typedef xe_result_t (__xecall *xe_pfnEventPoolCloseIpcHandle_t)(
    xe_event_pool_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListAppendSignalEvent function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListAppendSignalEvent_t)(
    xe_command_list_handle_t,
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListAppendWaitOnEvents function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListAppendWaitOnEvents_t)(
    xe_command_list_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeEventHostSignal function-pointer
typedef xe_result_t (__xecall *xe_pfnEventHostSignal_t)(
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeEventHostSynchronize function-pointer
typedef xe_result_t (__xecall *xe_pfnEventHostSynchronize_t)(
    xe_event_handle_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeEventQueryStatus function-pointer
typedef xe_result_t (__xecall *xe_pfnEventQueryStatus_t)(
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListAppendEventReset function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListAppendEventReset_t)(
    xe_command_list_handle_t,
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeEventReset function-pointer
typedef xe_result_t (__xecall *xe_pfnEventReset_t)(
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeFenceCreate function-pointer
typedef xe_result_t (__xecall *xe_pfnFenceCreate_t)(
    xe_command_queue_handle_t,
    const xe_fence_desc_t*,
    xe_fence_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeFenceDestroy function-pointer
typedef xe_result_t (__xecall *xe_pfnFenceDestroy_t)(
    xe_fence_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeFenceHostSynchronize function-pointer
typedef xe_result_t (__xecall *xe_pfnFenceHostSynchronize_t)(
    xe_fence_handle_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeFenceQueryStatus function-pointer
typedef xe_result_t (__xecall *xe_pfnFenceQueryStatus_t)(
    xe_fence_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeFenceReset function-pointer
typedef xe_result_t (__xecall *xe_pfnFenceReset_t)(
    xe_fence_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeImageGetProperties function-pointer
typedef xe_result_t (__xecall *xe_pfnImageGetProperties_t)(
    xe_device_handle_t,
    const xe_image_desc_t*,
    xe_image_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeImageCreate function-pointer
typedef xe_result_t (__xecall *xe_pfnImageCreate_t)(
    xe_device_handle_t,
    const xe_image_desc_t*,
    xe_image_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeImageDestroy function-pointer
typedef xe_result_t (__xecall *xe_pfnImageDestroy_t)(
    xe_image_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeSharedMemAlloc function-pointer
typedef xe_result_t (__xecall *xe_pfnSharedMemAlloc_t)(
    xe_device_handle_t,
    xe_device_mem_alloc_flag_t,
    xe_host_mem_alloc_flag_t,
    size_t,
    size_t,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeMemAlloc function-pointer
typedef xe_result_t (__xecall *xe_pfnMemAlloc_t)(
    xe_device_handle_t,
    xe_device_mem_alloc_flag_t,
    size_t,
    size_t,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeHostMemAlloc function-pointer
typedef xe_result_t (__xecall *xe_pfnHostMemAlloc_t)(
    xe_host_mem_alloc_flag_t,
    size_t,
    size_t,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeMemFree function-pointer
typedef xe_result_t (__xecall *xe_pfnMemFree_t)(
    const void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeMemGetProperties function-pointer
typedef xe_result_t (__xecall *xe_pfnMemGetProperties_t)(
    const void*,
    xe_memory_allocation_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeMemGetAddressRange function-pointer
typedef xe_result_t (__xecall *xe_pfnMemGetAddressRange_t)(
    const void*,
    void**,
    size_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeIpcGetMemHandle function-pointer
typedef xe_result_t (__xecall *xe_pfnIpcGetMemHandle_t)(
    const void*,
    xe_ipc_mem_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeIpcOpenMemHandle function-pointer
typedef xe_result_t (__xecall *xe_pfnIpcOpenMemHandle_t)(
    xe_device_handle_t,
    xe_ipc_mem_handle_t,
    xe_ipc_memory_flag_t,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeIpcCloseMemHandle function-pointer
typedef xe_result_t (__xecall *xe_pfnIpcCloseMemHandle_t)(
    const void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeModuleCreate function-pointer
typedef xe_result_t (__xecall *xe_pfnModuleCreate_t)(
    xe_device_handle_t,
    const xe_module_desc_t*,
    xe_module_handle_t*,
    xe_module_build_log_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeModuleDestroy function-pointer
typedef xe_result_t (__xecall *xe_pfnModuleDestroy_t)(
    xe_module_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeModuleBuildLogDestroy function-pointer
typedef xe_result_t (__xecall *xe_pfnModuleBuildLogDestroy_t)(
    xe_module_build_log_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeModuleBuildLogGetString function-pointer
typedef xe_result_t (__xecall *xe_pfnModuleBuildLogGetString_t)(
    xe_module_build_log_handle_t,
    size_t*,
    char*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeModuleGetNativeBinary function-pointer
typedef xe_result_t (__xecall *xe_pfnModuleGetNativeBinary_t)(
    xe_module_handle_t,
    size_t*,
    uint8_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeModuleGetGlobalPointer function-pointer
typedef xe_result_t (__xecall *xe_pfnModuleGetGlobalPointer_t)(
    xe_module_handle_t,
    const char*,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeFunctionCreate function-pointer
typedef xe_result_t (__xecall *xe_pfnFunctionCreate_t)(
    xe_module_handle_t,
    const xe_function_desc_t*,
    xe_function_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeFunctionDestroy function-pointer
typedef xe_result_t (__xecall *xe_pfnFunctionDestroy_t)(
    xe_function_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeModuleGetFunctionPointer function-pointer
typedef xe_result_t (__xecall *xe_pfnModuleGetFunctionPointer_t)(
    xe_module_handle_t,
    const char*,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeFunctionSetGroupSize function-pointer
typedef xe_result_t (__xecall *xe_pfnFunctionSetGroupSize_t)(
    xe_function_handle_t,
    uint32_t,
    uint32_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeFunctionSuggestGroupSize function-pointer
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
/// @brief xeFunctionSetArgumentValue function-pointer
typedef xe_result_t (__xecall *xe_pfnFunctionSetArgumentValue_t)(
    xe_function_handle_t,
    uint32_t,
    size_t,
    const void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeFunctionSetAttribute function-pointer
typedef xe_result_t (__xecall *xe_pfnFunctionSetAttribute_t)(
    xe_function_handle_t,
    xe_function_set_attribute_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeFunctionGetAttribute function-pointer
typedef xe_result_t (__xecall *xe_pfnFunctionGetAttribute_t)(
    xe_function_handle_t,
    xe_function_get_attribute_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListAppendLaunchFunction function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListAppendLaunchFunction_t)(
    xe_command_list_handle_t,
    xe_function_handle_t,
    const xe_thread_group_dimensions_t*,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListAppendLaunchFunctionIndirect function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListAppendLaunchFunctionIndirect_t)(
    xe_command_list_handle_t,
    xe_function_handle_t,
    const xe_thread_group_dimensions_t*,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListAppendLaunchMultipleFunctionsIndirect function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListAppendLaunchMultipleFunctionsIndirect_t)(
    xe_command_list_handle_t,
    uint32_t,
    const xe_function_handle_t*,
    const size_t*,
    const xe_thread_group_dimensions_t*,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeCommandListAppendLaunchHostFunction function-pointer
typedef xe_result_t (__xecall *xe_pfnCommandListAppendLaunchHostFunction_t)(
    xe_command_list_handle_t,
    xe_host_pfn_t,
    void*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeDeviceMakeMemoryResident function-pointer
typedef xe_result_t (__xecall *xe_pfnDeviceMakeMemoryResident_t)(
    xe_device_handle_t,
    void*,
    size_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeDeviceEvictMemory function-pointer
typedef xe_result_t (__xecall *xe_pfnDeviceEvictMemory_t)(
    xe_device_handle_t,
    void*,
    size_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeDeviceMakeImageResident function-pointer
typedef xe_result_t (__xecall *xe_pfnDeviceMakeImageResident_t)(
    xe_device_handle_t,
    xe_image_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeDeviceEvictImage function-pointer
typedef xe_result_t (__xecall *xe_pfnDeviceEvictImage_t)(
    xe_device_handle_t,
    xe_image_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeSamplerCreate function-pointer
typedef xe_result_t (__xecall *xe_pfnSamplerCreate_t)(
    xe_device_handle_t,
    const xe_sampler_desc_t*,
    xe_sampler_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
/// @brief xeSamplerDestroy function-pointer
typedef xe_result_t (__xecall *xe_pfnSamplerDestroy_t)(
    xe_sampler_handle_t
    );


///////////////////////////////////////////////////////////////////////////////
typedef struct _xe_apitable_t
{
    xe_pfnCommandListAppendBarrier_t                pfnCommandListAppendBarrier;
    xe_pfnCommandListAppendMemoryRangesBarrier_t    pfnCommandListAppendMemoryRangesBarrier;
    xe_pfnDeviceSystemBarrier_t                     pfnDeviceSystemBarrier;
    #if XE_ENABLE_OCL_INTEROP
    xe_pfnDeviceRegisterCLMemory_t                  pfnDeviceRegisterCLMemory;
    #endif // XE_ENABLE_OCL_INTEROP
    #if XE_ENABLE_OCL_INTEROP
    xe_pfnDeviceRegisterCLProgram_t                 pfnDeviceRegisterCLProgram;
    #endif // XE_ENABLE_OCL_INTEROP
    #if XE_ENABLE_OCL_INTEROP
    xe_pfnDeviceRegisterCLCommandQueue_t            pfnDeviceRegisterCLCommandQueue;
    #endif // XE_ENABLE_OCL_INTEROP
    xe_pfnCommandListCreate_t                       pfnCommandListCreate;
    xe_pfnCommandListCreateImmediate_t              pfnCommandListCreateImmediate;
    xe_pfnCommandListDestroy_t                      pfnCommandListDestroy;
    xe_pfnCommandListClose_t                        pfnCommandListClose;
    xe_pfnCommandListReset_t                        pfnCommandListReset;
    xe_pfnCommandListSetParameter_t                 pfnCommandListSetParameter;
    xe_pfnCommandListGetParameter_t                 pfnCommandListGetParameter;
    xe_pfnCommandListResetParameters_t              pfnCommandListResetParameters;
    xe_pfnCommandListReserveSpace_t                 pfnCommandListReserveSpace;
    xe_pfnCommandQueueCreate_t                      pfnCommandQueueCreate;
    xe_pfnCommandQueueDestroy_t                     pfnCommandQueueDestroy;
    xe_pfnCommandQueueExecuteCommandLists_t         pfnCommandQueueExecuteCommandLists;
    xe_pfnCommandQueueSynchronize_t                 pfnCommandQueueSynchronize;
    xe_pfnCommandListAppendMemoryCopy_t             pfnCommandListAppendMemoryCopy;
    xe_pfnCommandListAppendMemorySet_t              pfnCommandListAppendMemorySet;
    xe_pfnCommandListAppendImageCopy_t              pfnCommandListAppendImageCopy;
    xe_pfnCommandListAppendImageCopyRegion_t        pfnCommandListAppendImageCopyRegion;
    xe_pfnCommandListAppendImageCopyToMemory_t      pfnCommandListAppendImageCopyToMemory;
    xe_pfnCommandListAppendImageCopyFromMemory_t    pfnCommandListAppendImageCopyFromMemory;
    xe_pfnCommandListAppendMemoryPrefetch_t         pfnCommandListAppendMemoryPrefetch;
    xe_pfnCommandListAppendMemAdvise_t              pfnCommandListAppendMemAdvise;
    xe_pfnDeviceGetCount_t                          pfnDeviceGetCount;
    xe_pfnDeviceGet_t                               pfnDeviceGet;
    xe_pfnDeviceGetSubDevice_t                      pfnDeviceGetSubDevice;
    xe_pfnDeviceGetApiVersion_t                     pfnDeviceGetApiVersion;
    xe_pfnDeviceGetProperties_t                     pfnDeviceGetProperties;
    xe_pfnDeviceGetComputeProperties_t              pfnDeviceGetComputeProperties;
    xe_pfnDeviceGetMemoryProperties_t               pfnDeviceGetMemoryProperties;
    xe_pfnDeviceGetP2PProperties_t                  pfnDeviceGetP2PProperties;
    xe_pfnDeviceCanAccessPeer_t                     pfnDeviceCanAccessPeer;
    xe_pfnDeviceSetIntermediateCacheConfig_t        pfnDeviceSetIntermediateCacheConfig;
    xe_pfnDeviceSetLastLevelCacheConfig_t           pfnDeviceSetLastLevelCacheConfig;
    xe_pfnInit_t                                    pfnInit;
    xe_pfnGetDriverVersion_t                        pfnGetDriverVersion;
    xe_pfnEventPoolCreate_t                         pfnEventPoolCreate;
    xe_pfnEventPoolDestroy_t                        pfnEventPoolDestroy;
    xe_pfnEventCreate_t                             pfnEventCreate;
    xe_pfnEventDestroy_t                            pfnEventDestroy;
    xe_pfnEventPoolGetIpcHandle_t                   pfnEventPoolGetIpcHandle;
    xe_pfnEventPoolOpenIpcHandle_t                  pfnEventPoolOpenIpcHandle;
    xe_pfnEventPoolCloseIpcHandle_t                 pfnEventPoolCloseIpcHandle;
    xe_pfnCommandListAppendSignalEvent_t            pfnCommandListAppendSignalEvent;
    xe_pfnCommandListAppendWaitOnEvents_t           pfnCommandListAppendWaitOnEvents;
    xe_pfnEventHostSignal_t                         pfnEventHostSignal;
    xe_pfnEventHostSynchronize_t                    pfnEventHostSynchronize;
    xe_pfnEventQueryStatus_t                        pfnEventQueryStatus;
    xe_pfnCommandListAppendEventReset_t             pfnCommandListAppendEventReset;
    xe_pfnEventReset_t                              pfnEventReset;
    xe_pfnFenceCreate_t                             pfnFenceCreate;
    xe_pfnFenceDestroy_t                            pfnFenceDestroy;
    xe_pfnFenceHostSynchronize_t                    pfnFenceHostSynchronize;
    xe_pfnFenceQueryStatus_t                        pfnFenceQueryStatus;
    xe_pfnFenceReset_t                              pfnFenceReset;
    xe_pfnImageGetProperties_t                      pfnImageGetProperties;
    xe_pfnImageCreate_t                             pfnImageCreate;
    xe_pfnImageDestroy_t                            pfnImageDestroy;
    xe_pfnSharedMemAlloc_t                          pfnSharedMemAlloc;
    xe_pfnMemAlloc_t                                pfnMemAlloc;
    xe_pfnHostMemAlloc_t                            pfnHostMemAlloc;
    xe_pfnMemFree_t                                 pfnMemFree;
    xe_pfnMemGetProperties_t                        pfnMemGetProperties;
    xe_pfnMemGetAddressRange_t                      pfnMemGetAddressRange;
    xe_pfnIpcGetMemHandle_t                         pfnIpcGetMemHandle;
    xe_pfnIpcOpenMemHandle_t                        pfnIpcOpenMemHandle;
    xe_pfnIpcCloseMemHandle_t                       pfnIpcCloseMemHandle;
    xe_pfnModuleCreate_t                            pfnModuleCreate;
    xe_pfnModuleDestroy_t                           pfnModuleDestroy;
    xe_pfnModuleBuildLogDestroy_t                   pfnModuleBuildLogDestroy;
    xe_pfnModuleBuildLogGetString_t                 pfnModuleBuildLogGetString;
    xe_pfnModuleGetNativeBinary_t                   pfnModuleGetNativeBinary;
    xe_pfnModuleGetGlobalPointer_t                  pfnModuleGetGlobalPointer;
    xe_pfnFunctionCreate_t                          pfnFunctionCreate;
    xe_pfnFunctionDestroy_t                         pfnFunctionDestroy;
    xe_pfnModuleGetFunctionPointer_t                pfnModuleGetFunctionPointer;
    xe_pfnFunctionSetGroupSize_t                    pfnFunctionSetGroupSize;
    xe_pfnFunctionSuggestGroupSize_t                pfnFunctionSuggestGroupSize;
    xe_pfnFunctionSetArgumentValue_t                pfnFunctionSetArgumentValue;
    xe_pfnFunctionSetAttribute_t                    pfnFunctionSetAttribute;
    xe_pfnFunctionGetAttribute_t                    pfnFunctionGetAttribute;
    xe_pfnCommandListAppendLaunchFunction_t         pfnCommandListAppendLaunchFunction;
    xe_pfnCommandListAppendLaunchFunctionIndirect_t pfnCommandListAppendLaunchFunctionIndirect;
    xe_pfnCommandListAppendLaunchMultipleFunctionsIndirect_t    pfnCommandListAppendLaunchMultipleFunctionsIndirect;
    xe_pfnCommandListAppendLaunchHostFunction_t     pfnCommandListAppendLaunchHostFunction;
    xe_pfnDeviceMakeMemoryResident_t                pfnDeviceMakeMemoryResident;
    xe_pfnDeviceEvictMemory_t                       pfnDeviceEvictMemory;
    xe_pfnDeviceMakeImageResident_t                 pfnDeviceMakeImageResident;
    xe_pfnDeviceEvictImage_t                        pfnDeviceEvictImage;
    xe_pfnSamplerCreate_t                           pfnSamplerCreate;
    xe_pfnSamplerDestroy_t                          pfnSamplerDestroy;
} xe_apitable_t;

#endif // _XE_DDI_H