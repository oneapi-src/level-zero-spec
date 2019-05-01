/**************************************************************************//**
* INTEL CONFIDENTIAL  
* Copyright 2019  
* Intel Corporation All Rights Reserved.  
*
* @cond DEV
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
* @endcond
*
* @file core_loader.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/loader.h.mako
* @endcond
*
******************************************************************************/
#ifndef _CORE_LOADER_H
#define _CORE_LOADER_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_all.h"
#include "loader.h"

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListAppendBarrier_t)(
    xe_command_list_handle_t,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListAppendMemoryRangesBarrier_t)(
    xe_command_list_handle_t,
    uint32_t,
    const size_t*,
    const void**,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeDeviceSystemBarrier_t)(
    xe_device_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
typedef xe_result_t (__xecall *pfn_xeDeviceRegisterCLMemory_t)(
    xe_device_handle_t,
    cl_context,
    cl_mem,
    void**
    );
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
typedef xe_result_t (__xecall *pfn_xeDeviceRegisterCLProgram_t)(
    xe_device_handle_t,
    cl_context,
    cl_program,
    xe_module_handle_t*
    );
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
typedef xe_result_t (__xecall *pfn_xeDeviceRegisterCLCommandQueue_t)(
    xe_device_handle_t,
    cl_context,
    cl_command_queue,
    xe_command_queue_handle_t*
    );
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListCreate_t)(
    xe_device_handle_t,
    const xe_command_list_desc_t*,
    xe_command_list_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListCreateImmediate_t)(
    xe_device_handle_t,
    const xe_command_queue_desc_t*,
    xe_command_list_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListDestroy_t)(
    xe_command_list_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListClose_t)(
    xe_command_list_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListReset_t)(
    xe_command_list_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListSetParameter_t)(
    xe_command_list_handle_t,
    xe_command_list_parameter_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListGetParameter_t)(
    xe_command_list_handle_t,
    xe_command_list_parameter_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListResetParameters_t)(
    xe_command_list_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListReserveSpace_t)(
    xe_command_list_handle_t,
    size_t,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandQueueCreate_t)(
    xe_device_handle_t,
    const xe_command_queue_desc_t*,
    xe_command_queue_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandQueueDestroy_t)(
    xe_command_queue_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandQueueExecuteCommandLists_t)(
    xe_command_queue_handle_t,
    uint32_t,
    xe_command_list_handle_t*,
    xe_fence_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandQueueSynchronize_t)(
    xe_command_queue_handle_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListAppendMemoryCopy_t)(
    xe_command_list_handle_t,
    void*,
    const void*,
    size_t,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListAppendMemorySet_t)(
    xe_command_list_handle_t,
    void*,
    int,
    size_t,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListAppendImageCopy_t)(
    xe_command_list_handle_t,
    xe_image_handle_t,
    xe_image_handle_t,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListAppendImageCopyRegion_t)(
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
typedef xe_result_t (__xecall *pfn_xeCommandListAppendImageCopyToMemory_t)(
    xe_command_list_handle_t,
    void*,
    xe_image_handle_t,
    xe_image_region_t*,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListAppendImageCopyFromMemory_t)(
    xe_command_list_handle_t,
    xe_image_handle_t,
    const void*,
    xe_image_region_t*,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListAppendMemoryPrefetch_t)(
    xe_command_list_handle_t,
    const void*,
    size_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListAppendMemAdvise_t)(
    xe_command_list_handle_t,
    xe_device_handle_t,
    const void*,
    size_t,
    xe_memory_advice_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeDeviceGetCount_t)(
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeDeviceGet_t)(
    uint32_t,
    xe_device_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeDeviceGetSubDevice_t)(
    xe_device_handle_t,
    uint32_t,
    xe_device_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeDeviceGetApiVersion_t)(
    xe_device_handle_t,
    xe_api_version_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeDeviceGetProperties_t)(
    xe_device_handle_t,
    xe_device_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeDeviceGetComputeProperties_t)(
    xe_device_handle_t,
    xe_device_compute_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeDeviceGetMemoryProperties_t)(
    xe_device_handle_t,
    xe_device_memory_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeDeviceGetP2PProperties_t)(
    xe_device_handle_t,
    xe_device_handle_t,
    xe_device_p2p_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeDeviceCanAccessPeer_t)(
    xe_device_handle_t,
    xe_device_handle_t,
    xe_bool_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeDeviceSetIntermediateCacheConfig_t)(
    xe_device_handle_t,
    xe_cache_config_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeDeviceSetLastLevelCacheConfig_t)(
    xe_device_handle_t,
    xe_cache_config_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeInit_t)(
    xe_init_flag_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeGetDriverVersion_t)(
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeEventPoolCreate_t)(
    xe_device_handle_t,
    const xe_event_pool_desc_t*,
    xe_event_pool_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeEventPoolDestroy_t)(
    xe_event_pool_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeEventCreate_t)(
    xe_event_pool_handle_t,
    const xe_event_desc_t*,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeEventDestroy_t)(
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeEventPoolGetIpcHandle_t)(
    xe_event_pool_handle_t,
    xe_ipc_event_pool_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeEventPoolOpenIpcHandle_t)(
    xe_device_handle_t,
    xe_ipc_event_pool_handle_t,
    xe_event_pool_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeEventPoolCloseIpcHandle_t)(
    xe_event_pool_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListAppendSignalEvent_t)(
    xe_command_list_handle_t,
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListAppendWaitOnEvents_t)(
    xe_command_list_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeEventHostSignal_t)(
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeEventHostSynchronize_t)(
    xe_event_handle_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeEventQueryStatus_t)(
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListAppendEventReset_t)(
    xe_command_list_handle_t,
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeEventReset_t)(
    xe_event_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeFenceCreate_t)(
    xe_command_queue_handle_t,
    const xe_fence_desc_t*,
    xe_fence_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeFenceDestroy_t)(
    xe_fence_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeFenceHostSynchronize_t)(
    xe_fence_handle_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeFenceQueryStatus_t)(
    xe_fence_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeFenceReset_t)(
    xe_fence_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeImageGetProperties_t)(
    xe_device_handle_t,
    const xe_image_desc_t*,
    xe_image_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeImageCreate_t)(
    xe_device_handle_t,
    const xe_image_desc_t*,
    xe_image_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeImageDestroy_t)(
    xe_image_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeSharedMemAlloc_t)(
    xe_device_handle_t,
    xe_device_mem_alloc_flag_t,
    xe_host_mem_alloc_flag_t,
    size_t,
    size_t,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeMemAlloc_t)(
    xe_device_handle_t,
    xe_device_mem_alloc_flag_t,
    size_t,
    size_t,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeHostMemAlloc_t)(
    xe_host_mem_alloc_flag_t,
    size_t,
    size_t,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeMemFree_t)(
    const void*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeMemGetProperties_t)(
    const void*,
    xe_memory_allocation_properties_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeMemGetAddressRange_t)(
    const void*,
    void**,
    size_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeIpcGetMemHandle_t)(
    const void*,
    xe_ipc_mem_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeIpcOpenMemHandle_t)(
    xe_device_handle_t,
    xe_ipc_mem_handle_t,
    xe_ipc_memory_flag_t,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeIpcCloseMemHandle_t)(
    const void*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeModuleCreate_t)(
    xe_device_handle_t,
    const xe_module_desc_t*,
    xe_module_handle_t*,
    xe_module_build_log_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeModuleDestroy_t)(
    xe_module_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeModuleBuildLogDestroy_t)(
    xe_module_build_log_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeModuleBuildLogGetString_t)(
    xe_module_build_log_handle_t,
    size_t*,
    char*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeModuleGetNativeBinary_t)(
    xe_module_handle_t,
    size_t*,
    uint8_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeModuleGetGlobalPointer_t)(
    xe_module_handle_t,
    const char*,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeFunctionCreate_t)(
    xe_module_handle_t,
    const xe_function_desc_t*,
    xe_function_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeFunctionDestroy_t)(
    xe_function_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeModuleGetFunctionPointer_t)(
    xe_module_handle_t,
    const char*,
    void**
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeFunctionSetGroupSize_t)(
    xe_function_handle_t,
    uint32_t,
    uint32_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeFunctionSuggestGroupSize_t)(
    xe_function_handle_t,
    uint32_t,
    uint32_t,
    uint32_t,
    uint32_t*,
    uint32_t*,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeFunctionSetArgumentValue_t)(
    xe_function_handle_t,
    uint32_t,
    size_t,
    const void*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeFunctionSetAttribute_t)(
    xe_function_handle_t,
    xe_function_set_attribute_t,
    uint32_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeFunctionGetAttribute_t)(
    xe_function_handle_t,
    xe_function_get_attribute_t,
    uint32_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListAppendLaunchFunction_t)(
    xe_command_list_handle_t,
    xe_function_handle_t,
    const xe_thread_group_dimensions_t*,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListAppendLaunchFunctionIndirect_t)(
    xe_command_list_handle_t,
    xe_function_handle_t,
    const xe_thread_group_dimensions_t*,
    xe_event_handle_t,
    uint32_t,
    xe_event_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeCommandListAppendLaunchMultipleFunctionsIndirect_t)(
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
typedef xe_result_t (__xecall *pfn_xeCommandListAppendLaunchHostFunction_t)(
    xe_command_list_handle_t,
    xe_host_pfn_t,
    void*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeDeviceMakeMemoryResident_t)(
    xe_device_handle_t,
    void*,
    size_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeDeviceEvictMemory_t)(
    xe_device_handle_t,
    void*,
    size_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeDeviceMakeImageResident_t)(
    xe_device_handle_t,
    xe_image_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeDeviceEvictImage_t)(
    xe_device_handle_t,
    xe_image_handle_t
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeSamplerCreate_t)(
    xe_device_handle_t,
    const xe_sampler_desc_t*,
    xe_sampler_handle_t*
    );

///////////////////////////////////////////////////////////////////////////////
typedef xe_result_t (__xecall *pfn_xeSamplerDestroy_t)(
    xe_sampler_handle_t
    );


///////////////////////////////////////////////////////////////////////////////
typedef struct _xeapi_pfntable_t
{
    pfn_xeCommandListAppendBarrier_t                                xeCommandListAppendBarrier;
    pfn_xeCommandListAppendMemoryRangesBarrier_t                    xeCommandListAppendMemoryRangesBarrier;
    pfn_xeDeviceSystemBarrier_t                                     xeDeviceSystemBarrier;
    #if XE_ENABLE_OCL_INTEROP
    pfn_xeDeviceRegisterCLMemory_t                                  xeDeviceRegisterCLMemory;
    #endif // XE_ENABLE_OCL_INTEROP
    #if XE_ENABLE_OCL_INTEROP
    pfn_xeDeviceRegisterCLProgram_t                                 xeDeviceRegisterCLProgram;
    #endif // XE_ENABLE_OCL_INTEROP
    #if XE_ENABLE_OCL_INTEROP
    pfn_xeDeviceRegisterCLCommandQueue_t                            xeDeviceRegisterCLCommandQueue;
    #endif // XE_ENABLE_OCL_INTEROP
    pfn_xeCommandListCreate_t                                       xeCommandListCreate;
    pfn_xeCommandListCreateImmediate_t                              xeCommandListCreateImmediate;
    pfn_xeCommandListDestroy_t                                      xeCommandListDestroy;
    pfn_xeCommandListClose_t                                        xeCommandListClose;
    pfn_xeCommandListReset_t                                        xeCommandListReset;
    pfn_xeCommandListSetParameter_t                                 xeCommandListSetParameter;
    pfn_xeCommandListGetParameter_t                                 xeCommandListGetParameter;
    pfn_xeCommandListResetParameters_t                              xeCommandListResetParameters;
    pfn_xeCommandListReserveSpace_t                                 xeCommandListReserveSpace;
    pfn_xeCommandQueueCreate_t                                      xeCommandQueueCreate;
    pfn_xeCommandQueueDestroy_t                                     xeCommandQueueDestroy;
    pfn_xeCommandQueueExecuteCommandLists_t                         xeCommandQueueExecuteCommandLists;
    pfn_xeCommandQueueSynchronize_t                                 xeCommandQueueSynchronize;
    pfn_xeCommandListAppendMemoryCopy_t                             xeCommandListAppendMemoryCopy;
    pfn_xeCommandListAppendMemorySet_t                              xeCommandListAppendMemorySet;
    pfn_xeCommandListAppendImageCopy_t                              xeCommandListAppendImageCopy;
    pfn_xeCommandListAppendImageCopyRegion_t                        xeCommandListAppendImageCopyRegion;
    pfn_xeCommandListAppendImageCopyToMemory_t                      xeCommandListAppendImageCopyToMemory;
    pfn_xeCommandListAppendImageCopyFromMemory_t                    xeCommandListAppendImageCopyFromMemory;
    pfn_xeCommandListAppendMemoryPrefetch_t                         xeCommandListAppendMemoryPrefetch;
    pfn_xeCommandListAppendMemAdvise_t                              xeCommandListAppendMemAdvise;
    pfn_xeDeviceGetCount_t                                          xeDeviceGetCount;
    pfn_xeDeviceGet_t                                               xeDeviceGet;
    pfn_xeDeviceGetSubDevice_t                                      xeDeviceGetSubDevice;
    pfn_xeDeviceGetApiVersion_t                                     xeDeviceGetApiVersion;
    pfn_xeDeviceGetProperties_t                                     xeDeviceGetProperties;
    pfn_xeDeviceGetComputeProperties_t                              xeDeviceGetComputeProperties;
    pfn_xeDeviceGetMemoryProperties_t                               xeDeviceGetMemoryProperties;
    pfn_xeDeviceGetP2PProperties_t                                  xeDeviceGetP2PProperties;
    pfn_xeDeviceCanAccessPeer_t                                     xeDeviceCanAccessPeer;
    pfn_xeDeviceSetIntermediateCacheConfig_t                        xeDeviceSetIntermediateCacheConfig;
    pfn_xeDeviceSetLastLevelCacheConfig_t                           xeDeviceSetLastLevelCacheConfig;
    pfn_xeInit_t                                                    xeInit;
    pfn_xeGetDriverVersion_t                                        xeGetDriverVersion;
    pfn_xeEventPoolCreate_t                                         xeEventPoolCreate;
    pfn_xeEventPoolDestroy_t                                        xeEventPoolDestroy;
    pfn_xeEventCreate_t                                             xeEventCreate;
    pfn_xeEventDestroy_t                                            xeEventDestroy;
    pfn_xeEventPoolGetIpcHandle_t                                   xeEventPoolGetIpcHandle;
    pfn_xeEventPoolOpenIpcHandle_t                                  xeEventPoolOpenIpcHandle;
    pfn_xeEventPoolCloseIpcHandle_t                                 xeEventPoolCloseIpcHandle;
    pfn_xeCommandListAppendSignalEvent_t                            xeCommandListAppendSignalEvent;
    pfn_xeCommandListAppendWaitOnEvents_t                           xeCommandListAppendWaitOnEvents;
    pfn_xeEventHostSignal_t                                         xeEventHostSignal;
    pfn_xeEventHostSynchronize_t                                    xeEventHostSynchronize;
    pfn_xeEventQueryStatus_t                                        xeEventQueryStatus;
    pfn_xeCommandListAppendEventReset_t                             xeCommandListAppendEventReset;
    pfn_xeEventReset_t                                              xeEventReset;
    pfn_xeFenceCreate_t                                             xeFenceCreate;
    pfn_xeFenceDestroy_t                                            xeFenceDestroy;
    pfn_xeFenceHostSynchronize_t                                    xeFenceHostSynchronize;
    pfn_xeFenceQueryStatus_t                                        xeFenceQueryStatus;
    pfn_xeFenceReset_t                                              xeFenceReset;
    pfn_xeImageGetProperties_t                                      xeImageGetProperties;
    pfn_xeImageCreate_t                                             xeImageCreate;
    pfn_xeImageDestroy_t                                            xeImageDestroy;
    pfn_xeSharedMemAlloc_t                                          xeSharedMemAlloc;
    pfn_xeMemAlloc_t                                                xeMemAlloc;
    pfn_xeHostMemAlloc_t                                            xeHostMemAlloc;
    pfn_xeMemFree_t                                                 xeMemFree;
    pfn_xeMemGetProperties_t                                        xeMemGetProperties;
    pfn_xeMemGetAddressRange_t                                      xeMemGetAddressRange;
    pfn_xeIpcGetMemHandle_t                                         xeIpcGetMemHandle;
    pfn_xeIpcOpenMemHandle_t                                        xeIpcOpenMemHandle;
    pfn_xeIpcCloseMemHandle_t                                       xeIpcCloseMemHandle;
    pfn_xeModuleCreate_t                                            xeModuleCreate;
    pfn_xeModuleDestroy_t                                           xeModuleDestroy;
    pfn_xeModuleBuildLogDestroy_t                                   xeModuleBuildLogDestroy;
    pfn_xeModuleBuildLogGetString_t                                 xeModuleBuildLogGetString;
    pfn_xeModuleGetNativeBinary_t                                   xeModuleGetNativeBinary;
    pfn_xeModuleGetGlobalPointer_t                                  xeModuleGetGlobalPointer;
    pfn_xeFunctionCreate_t                                          xeFunctionCreate;
    pfn_xeFunctionDestroy_t                                         xeFunctionDestroy;
    pfn_xeModuleGetFunctionPointer_t                                xeModuleGetFunctionPointer;
    pfn_xeFunctionSetGroupSize_t                                    xeFunctionSetGroupSize;
    pfn_xeFunctionSuggestGroupSize_t                                xeFunctionSuggestGroupSize;
    pfn_xeFunctionSetArgumentValue_t                                xeFunctionSetArgumentValue;
    pfn_xeFunctionSetAttribute_t                                    xeFunctionSetAttribute;
    pfn_xeFunctionGetAttribute_t                                    xeFunctionGetAttribute;
    pfn_xeCommandListAppendLaunchFunction_t                         xeCommandListAppendLaunchFunction;
    pfn_xeCommandListAppendLaunchFunctionIndirect_t                 xeCommandListAppendLaunchFunctionIndirect;
    pfn_xeCommandListAppendLaunchMultipleFunctionsIndirect_t        xeCommandListAppendLaunchMultipleFunctionsIndirect;
    pfn_xeCommandListAppendLaunchHostFunction_t                     xeCommandListAppendLaunchHostFunction;
    pfn_xeDeviceMakeMemoryResident_t                                xeDeviceMakeMemoryResident;
    pfn_xeDeviceEvictMemory_t                                       xeDeviceEvictMemory;
    pfn_xeDeviceMakeImageResident_t                                 xeDeviceMakeImageResident;
    pfn_xeDeviceEvictImage_t                                        xeDeviceEvictImage;
    pfn_xeSamplerCreate_t                                           xeSamplerCreate;
    pfn_xeSamplerDestroy_t                                          xeSamplerDestroy;
} xeapi_pfntable_t;

///////////////////////////////////////////////////////////////////////////////
bool xeLoad(
    void* handle,           ///< [in] driver handle
    xeapi_pfntable_t* );  ///< [in] pointer to table of xe API function pointers

#endif // _CORE_LOADER_H
