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
* @file icd_loader.h
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/*.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_LOADER_H
#define _XE_LOADER_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_all.h"

typedef struct _cl_mem* cl_mem;
typedef struct _cl_command_queue* cl_command_queue;
typedef struct _cl_context* cl_context;
typedef struct _cl_program* cl_program;

typedef xe_result_t (__xecall *pfn_xeDriverGetDeviceCount)(
    uint32_t* count
    );
typedef xe_result_t (__xecall *pfn_xeDriverGetDeviceUniqueIds)(
    uint32_t count,
    uint32_t* pUniqueIds
    );
typedef xe_result_t (__xecall *pfn_xeDriverGetDevice)(
    uint32_t uniqueId,
    xe_device_handle_t* phDevice
    );
typedef xe_result_t (__xecall *pfn_xeDeviceGetSubDevice)(
    xe_device_handle_t hDevice,
    uint32_t ordinal,
    xe_device_handle_t* phSubDevice
    );
typedef xe_result_t (__xecall *pfn_xeDeviceGetApiVersion)(
    xe_device_handle_t hDevice,
    xe_api_version_t* version
    );
typedef xe_result_t (__xecall *pfn_xeDeviceGetProperties)(
    xe_device_handle_t hDevice,
    xe_device_properties_t* pDeviceProperties
    );
typedef xe_result_t (__xecall *pfn_xeDeviceGetComputeProperties)(
    xe_device_handle_t hDevice,
    xe_device_compute_properties_t* pComputeProperties
    );
typedef xe_result_t (__xecall *pfn_xeDeviceGetMemoryProperties)(
    xe_device_handle_t hDevice,
    xe_device_memory_properties_t* pMemProperties
    );
typedef xe_result_t (__xecall *pfn_xeDeviceGetLinkProperties)(
    uint32_t srcOrdinal,
    uint32_t dstOrdinal,
    xe_device_link_properties_t* pLinkProperties
    );
typedef xe_result_t (__xecall *pfn_xeDeviceCanAccessPeer)(
    xe_device_handle_t hDevice,
    xe_device_handle_t hPeerDevice,
    bool* value
    );
typedef xe_result_t (__xecall *pfn_xeDeviceSetIntermediateCacheConfig)(
    xe_device_handle_t hDevice,
    xe_cache_config_t CacheConfig
    );
typedef xe_result_t (__xecall *pfn_xeDeviceSetLastLevelCacheConfig)(
    xe_device_handle_t hDevice,
    xe_cache_config_t CacheConfig
    );
typedef xe_result_t (__xecall *pfn_xeDeviceCreateCommandGraph)(
    xe_device_handle_t hDevice,
    const xe_command_graph_desc_t* desc,
    xe_command_graph_handle_t* phCommandGraph
    );
typedef xe_result_t (__xecall *pfn_xeCommandGraphDestroy)(
    xe_command_graph_handle_t hCommandGraph
    );
typedef xe_result_t (__xecall *pfn_xeCommandGraphClose)(
    xe_command_graph_handle_t hCommandGraph
    );
typedef xe_result_t (__xecall *pfn_xeCommandGraphReset)(
    xe_command_graph_handle_t hCommandGraph
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeExecutionBarrier)(
    xe_command_list_handle_t hCommandList
    );
typedef xe_result_t (__xecall *pfn_xeDeviceCreateSemaphore)(
    xe_device_handle_t hDevice,
    const xe_semaphore_desc_t* desc,
    xe_semaphore_handle_t* phSemaphore
    );
typedef xe_result_t (__xecall *pfn_xeSemaphoreDestroy)(
    xe_semaphore_handle_t hSemaphore
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeSemaphoreSignal)(
    xe_command_list_handle_t hCommandList,
    xe_semaphore_handle_t hSemaphore,
    xe_semaphore_value_t value
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeSemaphoreWait)(
    xe_command_list_handle_t hCommandList,
    xe_semaphore_handle_t hSemaphore,
    xe_semaphore_wait_operation_t operation,
    xe_semaphore_value_t value
    );
typedef xe_result_t (__xecall *pfn_xeSemaphoreQueryValue)(
    xe_semaphore_handle_t hSemaphore
    );
typedef xe_result_t (__xecall *pfn_xeSemaphoreReset)(
    xe_semaphore_handle_t hSemaphore
    );
typedef xe_result_t (__xecall *pfn_xeDriverInit)(
    xe_init_flag_t flags
    );
typedef xe_result_t (__xecall *pfn_xeDriverGetVersion)(
    uint32_t* version
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeMemoryCopy)(
    xe_command_list_handle_t hCommandList,
    void* dstptr,
    const void* srcptr,
    size_t size
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeMemorySet)(
    xe_command_list_handle_t hCommandList,
    void* ptr,
    int value,
    size_t size
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeImageCopy)(
    xe_command_list_handle_t hCommandList,
    xe_image_handle_t hDstImage,
    xe_image_handle_t hSrcImage
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeImageCopyRegion)(
    xe_command_list_handle_t hCommandList,
    xe_image_handle_t hDstImage,
    xe_image_region_t* pDstRegion,
    xe_image_handle_t hSrcImage,
    xe_image_region_t* pSrcRegion
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeImageCopyToMemory)(
    xe_command_list_handle_t hCommandList,
    void* dstptr,
    xe_image_handle_t hSrcImage,
    xe_image_region_t* pSrcRegion
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeImageCopyFromMemory)(
    xe_command_list_handle_t hCommandList,
    xe_image_handle_t hDstImage,
    xe_image_region_t* pDstRegion,
    void* srcptr
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeMemoryPrefetch)(
    xe_command_list_handle_t hCommandList,
    const void* ptr,
    size_t count
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeMemAdvise)(
    xe_command_list_handle_t hCommandList,
    xe_device_handle_t hDevice,
    const void* ptr,
    size_t size,
    xe_memory_advice_t advice
    );
typedef xe_result_t (__xecall *pfn_xeDeviceCreateModule)(
    xe_device_handle_t hDevice,
    const xe_module_desc_t* desc,
    xe_module_handle_t* phModule,
    xe_module_build_log_handle_t* phBuildLog
    );
typedef xe_result_t (__xecall *pfn_xeModuleDestroy)(
    xe_module_handle_t hModule
    );
typedef xe_result_t (__xecall *pfn_xeModuleBuildLogDestroy)(
    xe_module_build_log_handle_t hModuleBuildLog
    );
typedef xe_result_t (__xecall *pfn_xeModuleBuildLogGetString)(
    xe_module_build_log_handle_t hModuleBuildLog,
    uint32_t* pSize,
    char** pBuildLog
    );
typedef xe_result_t (__xecall *pfn_xeModuleGetNativeBinary)(
    xe_module_handle_t hModule,
    uint32_t* pSize,
    char** pModuleNativeBinary
    );
typedef xe_result_t (__xecall *pfn_xeModuleCreateFunction)(
    xe_module_handle_t hModule,
    const xe_function_desc_t* desc,
    xe_function_handle_t* phFunction
    );
typedef xe_result_t (__xecall *pfn_xeFunctionDestroy)(
    xe_function_handle_t hFunction
    );
typedef xe_result_t (__xecall *pfn_xeModuleGetFunctionPointer)(
    xe_module_handle_t hModule,
    const char* pFunctionName,
    void** pfnFunction
    );
typedef xe_result_t (__xecall *pfn_xeFunctionSetGroupSize)(
    xe_function_handle_t hFunction,
    uint32_t groupSizeX,
    uint32_t groupSizeY,
    uint32_t groupSizeZ
    );
typedef xe_result_t (__xecall *pfn_xeFunctionSuggestGroupSize)(
    xe_function_handle_t hFunction,
    uint32_t globalSizeX,
    uint32_t globalSizeY,
    uint32_t globalSizeZ,
    uint32_t* groupSizeX,
    uint32_t* groupSizeY,
    uint32_t* groupSizeZ
    );
typedef xe_result_t (__xecall *pfn_xeFunctionSetArgumentValue)(
    xe_function_handle_t hFunction,
    uint32_t argIndex,
    size_t argSize,
    const void* pArgValue
    );
typedef xe_result_t (__xecall *pfn_xeFunctionSetAttribute)(
    xe_function_handle_t hFunction,
    xe_function_set_attribute_t attr,
    uint32_t value
    );
typedef xe_result_t (__xecall *pfn_xeFunctionGetAttribute)(
    xe_function_handle_t hFunction,
    xe_function_get_attribute_t attr,
    uint32_t* pValue
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeDispatchFunction)(
    xe_command_list_handle_t hCommandList,
    xe_function_handle_t hFunction,
    const xe_dispatch_function_arguments_t* pDispatchFuncArgs,
    xe_event_handle_t hEvent
    );
typedef xe_result_t (__xecall *pfn_xeCommandGraphEncodeDispatchFunction)(
    xe_command_graph_handle_t hCommandGraph,
    xe_function_handle_t hFunction,
    const xe_dispatch_function_arguments_t* pDispatchFuncArgs,
    xe_event_handle_t hEvent
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeDispatchFunctionIndirect)(
    xe_command_list_handle_t hCommandList,
    xe_function_handle_t hFunction,
    const xe_dispatch_function_indirect_arguments_t* pDispatchArgumentsBuffer,
    xe_event_handle_t hEvent
    );
typedef xe_result_t (__xecall *pfn_xeCommandGraphEncodeDispatchFunctionIndirect)(
    xe_command_graph_handle_t hCommandGraph,
    xe_function_handle_t hFunction,
    const xe_dispatch_function_indirect_arguments_t* pDispatchArgumentsBuffer,
    xe_event_handle_t hEvent
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeDispatchHostFunction)(
    xe_command_list_handle_t hCommandList,
    xe_host_pfn_t pfnHostFunc,
    void* pUserData
    );
typedef xe_result_t (__xecall *pfn_xeCommandGraphEncodeDispatchHostFunction)(
    xe_command_graph_handle_t hCommandGraph,
    xe_host_pfn_t pfnHostFunc,
    void* pUserData
    );
typedef xe_result_t (__xecall *pfn_xeDeviceCreateEvent)(
    xe_device_handle_t hDevice,
    const xe_event_desc_t* desc,
    xe_event_handle_t* phEvent
    );
typedef xe_result_t (__xecall *pfn_xeDevicePlaceEvent)(
    xe_device_handle_t hDevice,
    const xe_event_desc_t* desc,
    void* ptr,
    xe_event_handle_t* phEvent
    );
typedef xe_result_t (__xecall *pfn_xeEventDestroy)(
    xe_event_handle_t hEvent
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeSignalEvent)(
    xe_command_list_handle_t hCommandList,
    xe_event_handle_t hEvent
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeWaitOnEvent)(
    xe_command_list_handle_t hCommandList,
    xe_event_handle_t hEvent
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeSignalMultipleEvents)(
    xe_command_list_handle_t hCommandList,
    uint32_t numEvents,
    xe_event_handle_t* phEvents
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeWaitOnMultipleEvents)(
    xe_command_list_handle_t hCommandList,
    uint32_t numEvents,
    xe_event_handle_t* phEvents
    );
typedef xe_result_t (__xecall *pfn_xeHostSignalEvent)(
    xe_event_handle_t hEvent
    );
typedef xe_result_t (__xecall *pfn_xeHostWaitOnEvent)(
    xe_event_handle_t hEvent,
    xe_synchronization_mode_t mode,
    uint32_t delay,
    uint32_t interval,
    uint32_t timeout
    );
typedef xe_result_t (__xecall *pfn_xeHostSignalMultipleEvents)(
    uint32_t numEvents,
    xe_event_handle_t* phEvents
    );
typedef xe_result_t (__xecall *pfn_xeHostWaitOnMultipleEvents)(
    uint32_t numEvents,
    xe_event_handle_t* phEvents,
    xe_synchronization_mode_t mode,
    uint32_t delay,
    uint32_t interval,
    uint32_t timeout
    );
typedef xe_result_t (__xecall *pfn_xeEventQueryStatus)(
    xe_event_handle_t hEvent
    );
typedef xe_result_t (__xecall *pfn_xeEventQueryElapsedTime)(
    xe_event_handle_t hEventStart,
    xe_event_handle_t hEventEnd,
    double_t* pTime
    );
typedef xe_result_t (__xecall *pfn_xeEventQueryMetricsData)(
    xe_event_handle_t hEventStart,
    xe_event_handle_t hEventEnd,
    size_t reportSize,
    uint32_t* pReportData
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeEventReset)(
    xe_command_list_handle_t hCommandList,
    xe_event_handle_t hEvent
    );
typedef xe_result_t (__xecall *pfn_xeEventReset)(
    xe_event_handle_t hEvent
    );
#if XE_ENABLE_OCL_INTEROP
typedef xe_result_t (__xecall *pfn_xeDeviceRegisterCLMemory)(
    xe_device_handle_t hDevice,
    cl_context context,
    cl_mem mem,
    void** ptr
    );
#endif // XE_ENABLE_OCL_INTEROP
#if XE_ENABLE_OCL_INTEROP
typedef xe_result_t (__xecall *pfn_xeDeviceRegisterCLProgram)(
    xe_device_handle_t hDevice,
    cl_context context,
    cl_program program,
    xe_module_handle_t* phModule
    );
#endif // XE_ENABLE_OCL_INTEROP
#if XE_ENABLE_OCL_INTEROP
typedef xe_result_t (__xecall *pfn_xeDeviceRegisterCLCommandQueue)(
    xe_device_handle_t hDevice,
    cl_context context,
    cl_command_queue command_queue,
    xe_command_queue_handle_t* phCommandQueue
    );
#endif // XE_ENABLE_OCL_INTEROP
typedef xe_result_t (__xecall *pfn_xeDeviceCreateImage)(
    xe_device_handle_t hDevice,
    const xe_image_desc_t* desc,
    xe_image_handle_t* phImage
    );
typedef xe_result_t (__xecall *pfn_xeImageDestroy)(
    xe_image_handle_t hImage
    );
typedef xe_result_t (__xecall *pfn_xeDeviceCreateCommandQueue)(
    xe_device_handle_t hDevice,
    const xe_command_queue_desc_t* desc,
    xe_command_queue_handle_t* phCommandQueue
    );
typedef xe_result_t (__xecall *pfn_xeCommandQueueDestroy)(
    xe_command_queue_handle_t hCommandQueue
    );
typedef xe_result_t (__xecall *pfn_xeCommandQueueEnqueueCommandLists)(
    xe_command_queue_handle_t hCommandQueue,
    uint32_t numCommandLists,
    xe_command_list_handle_t* phCommandLists,
    xe_fence_handle_t hFence
    );
typedef xe_result_t (__xecall *pfn_xeCommandQueueSynchronize)(
    xe_command_queue_handle_t hCommandQueue,
    xe_synchronization_mode_t mode,
    uint32_t delay,
    uint32_t interval,
    uint32_t timeout
    );
typedef xe_result_t (__xecall *pfn_xeCreateMemAllocator)(
    xe_mem_allocator_handle_t* phMemAllocHandle
    );
typedef xe_result_t (__xecall *pfn_xeMemAllocatorDestroy)(
    xe_mem_allocator_handle_t hMemAllocHandle
    );
typedef xe_result_t (__xecall *pfn_xeSharedMemAlloc)(
    xe_mem_allocator_handle_t hMemAllocHandle,
    xe_device_handle_t hDevice,
    xe_device_mem_alloc_flag_t device_flags,
    xe_host_mem_alloc_flag_t host_flags,
    size_t size,
    size_t alignment,
    void** ptr
    );
typedef xe_result_t (__xecall *pfn_xeMemAlloc)(
    xe_mem_allocator_handle_t hMemAllocHandle,
    xe_device_handle_t hDevice,
    xe_device_mem_alloc_flag_t flags,
    size_t size,
    size_t alignment,
    void** ptr
    );
typedef xe_result_t (__xecall *pfn_xeHostMemAlloc)(
    xe_mem_allocator_handle_t hMemAllocHandle,
    xe_host_mem_alloc_flag_t flags,
    size_t size,
    size_t alignment,
    void** ptr
    );
typedef xe_result_t (__xecall *pfn_xeMemFree)(
    xe_mem_allocator_handle_t hMemAllocHandle,
    const void* ptr
    );
typedef xe_result_t (__xecall *pfn_xeMemGetProperty)(
    xe_mem_allocator_handle_t hMemAllocHandle,
    const void* ptr,
    xe_memory_property_t property,
    void* pValue
    );
typedef xe_result_t (__xecall *pfn_xeMemGetAddressRange)(
    xe_mem_allocator_handle_t hMemAllocHandle,
    const void* ptr,
    void** pBase,
    size_t* pSize
    );
typedef xe_result_t (__xecall *pfn_xeIpcGetMemHandle)(
    xe_mem_allocator_handle_t hMemAllocHandle,
    const void* ptr,
    xe_ipc_mem_handle_t* pIpcHandle
    );
typedef xe_result_t (__xecall *pfn_xeIpcOpenMemHandle)(
    xe_mem_allocator_handle_t hMemAllocHandle,
    xe_device_handle_t hDevice,
    xe_ipc_mem_handle_t handle,
    xe_ipc_memory_flag_t flags,
    void** ptr
    );
typedef xe_result_t (__xecall *pfn_xeIpcCloseMemHandle)(
    xe_mem_allocator_handle_t hMemAllocHandle,
    const void* ptr
    );
typedef xe_result_t (__xecall *pfn_xeCommandQueueCreateFence)(
    xe_command_queue_handle_t hCommandQueue,
    const xe_fence_desc_t* desc,
    xe_fence_handle_t* phFence
    );
typedef xe_result_t (__xecall *pfn_xeFenceDestroy)(
    xe_fence_handle_t hFence
    );
typedef xe_result_t (__xecall *pfn_xeHostWaitOnFence)(
    xe_fence_handle_t hFence,
    xe_synchronization_mode_t mode,
    uint32_t delay,
    uint32_t interval,
    uint32_t timeout
    );
typedef xe_result_t (__xecall *pfn_xeHostWaitOnMultipleFences)(
    uint32_t numFences,
    xe_fence_handle_t* phFences,
    xe_synchronization_mode_t mode,
    uint32_t delay,
    uint32_t interval,
    uint32_t timeout
    );
typedef xe_result_t (__xecall *pfn_xeFenceQueryStatus)(
    xe_fence_handle_t hFence
    );
typedef xe_result_t (__xecall *pfn_xeFenceQueryElapsedTime)(
    xe_fence_handle_t hFenceStart,
    xe_fence_handle_t hFenceEnd,
    double_t* pTime
    );
typedef xe_result_t (__xecall *pfn_xeFenceReset)(
    xe_fence_handle_t hFence
    );
typedef xe_result_t (__xecall *pfn_xeDeviceMakeMemoryResident)(
    xe_device_handle_t hDevice,
    void* ptr,
    size_t size
    );
typedef xe_result_t (__xecall *pfn_xeDeviceEvictMemory)(
    xe_device_handle_t hDevice,
    void* ptr,
    size_t size
    );
typedef xe_result_t (__xecall *pfn_xeDeviceMakeImageResident)(
    xe_device_handle_t hDevice,
    xe_image_handle_t hImage
    );
typedef xe_result_t (__xecall *pfn_xeDeviceEvictImage)(
    xe_device_handle_t hDevice,
    xe_image_handle_t hImage
    );
typedef xe_result_t (__xecall *pfn_xeDeviceCreateCommandList)(
    xe_device_handle_t hDevice,
    const xe_command_list_desc_t* desc,
    xe_command_list_handle_t* phCommandList
    );
typedef xe_result_t (__xecall *pfn_xeDeviceCopyCommandList)(
    xe_device_handle_t hDevice,
    xe_command_list_handle_t hCommandList,
    xe_command_list_handle_t* phCommandList
    );
typedef xe_result_t (__xecall *pfn_xeCommandListDestroy)(
    xe_command_list_handle_t hCommandList
    );
typedef xe_result_t (__xecall *pfn_xeCommandListClose)(
    xe_command_list_handle_t hCommandList
    );
typedef xe_result_t (__xecall *pfn_xeCommandListReset)(
    xe_command_list_handle_t hCommandList
    );
typedef xe_result_t (__xecall *pfn_xeCommandListSetParameter)(
    xe_command_list_handle_t hCommandList,
    xe_command_list_parameter_t parameter,
    uint32_t value
    );
typedef xe_result_t (__xecall *pfn_xeCommandListGetParameter)(
    xe_command_list_handle_t hCommandList,
    xe_command_list_parameter_t parameter,
    uint32_t* value
    );
typedef xe_result_t (__xecall *pfn_xeCommandListResetParameters)(
    xe_command_list_handle_t hCommandList
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeCommandLists)(
    xe_command_list_handle_t hCommandList,
    uint32_t numCommandLists,
    xe_command_list_handle_t* phCommandLists
    );
typedef xe_result_t (__xecall *pfn_xeCommandListEncodeCommands)(
    xe_command_list_handle_t hCommandList,
    xe_command_format_t format,
    size_t size,
    void* pBlob
    );

typedef struct _xe_dispatch_table_t
{
    pfn_xeDriverGetDeviceCount xeDriverGetDeviceCount;
    pfn_xeDriverGetDeviceUniqueIds xeDriverGetDeviceUniqueIds;
    pfn_xeDriverGetDevice xeDriverGetDevice;
    pfn_xeDeviceGetSubDevice xeDeviceGetSubDevice;
    pfn_xeDeviceGetApiVersion xeDeviceGetApiVersion;
    pfn_xeDeviceGetProperties xeDeviceGetProperties;
    pfn_xeDeviceGetComputeProperties xeDeviceGetComputeProperties;
    pfn_xeDeviceGetMemoryProperties xeDeviceGetMemoryProperties;
    pfn_xeDeviceGetLinkProperties xeDeviceGetLinkProperties;
    pfn_xeDeviceCanAccessPeer xeDeviceCanAccessPeer;
    pfn_xeDeviceSetIntermediateCacheConfig xeDeviceSetIntermediateCacheConfig;
    pfn_xeDeviceSetLastLevelCacheConfig xeDeviceSetLastLevelCacheConfig;
    pfn_xeDeviceCreateCommandGraph xeDeviceCreateCommandGraph;
    pfn_xeCommandGraphDestroy xeCommandGraphDestroy;
    pfn_xeCommandGraphClose xeCommandGraphClose;
    pfn_xeCommandGraphReset xeCommandGraphReset;
    pfn_xeCommandListEncodeExecutionBarrier xeCommandListEncodeExecutionBarrier;
    pfn_xeDeviceCreateSemaphore xeDeviceCreateSemaphore;
    pfn_xeSemaphoreDestroy xeSemaphoreDestroy;
    pfn_xeCommandListEncodeSemaphoreSignal xeCommandListEncodeSemaphoreSignal;
    pfn_xeCommandListEncodeSemaphoreWait xeCommandListEncodeSemaphoreWait;
    pfn_xeSemaphoreQueryValue xeSemaphoreQueryValue;
    pfn_xeSemaphoreReset xeSemaphoreReset;
    pfn_xeDriverInit xeDriverInit;
    pfn_xeDriverGetVersion xeDriverGetVersion;
    pfn_xeCommandListEncodeMemoryCopy xeCommandListEncodeMemoryCopy;
    pfn_xeCommandListEncodeMemorySet xeCommandListEncodeMemorySet;
    pfn_xeCommandListEncodeImageCopy xeCommandListEncodeImageCopy;
    pfn_xeCommandListEncodeImageCopyRegion xeCommandListEncodeImageCopyRegion;
    pfn_xeCommandListEncodeImageCopyToMemory xeCommandListEncodeImageCopyToMemory;
    pfn_xeCommandListEncodeImageCopyFromMemory xeCommandListEncodeImageCopyFromMemory;
    pfn_xeCommandListEncodeMemoryPrefetch xeCommandListEncodeMemoryPrefetch;
    pfn_xeCommandListEncodeMemAdvise xeCommandListEncodeMemAdvise;
    pfn_xeDeviceCreateModule xeDeviceCreateModule;
    pfn_xeModuleDestroy xeModuleDestroy;
    pfn_xeModuleBuildLogDestroy xeModuleBuildLogDestroy;
    pfn_xeModuleBuildLogGetString xeModuleBuildLogGetString;
    pfn_xeModuleGetNativeBinary xeModuleGetNativeBinary;
    pfn_xeModuleCreateFunction xeModuleCreateFunction;
    pfn_xeFunctionDestroy xeFunctionDestroy;
    pfn_xeModuleGetFunctionPointer xeModuleGetFunctionPointer;
    pfn_xeFunctionSetGroupSize xeFunctionSetGroupSize;
    pfn_xeFunctionSuggestGroupSize xeFunctionSuggestGroupSize;
    pfn_xeFunctionSetArgumentValue xeFunctionSetArgumentValue;
    pfn_xeFunctionSetAttribute xeFunctionSetAttribute;
    pfn_xeFunctionGetAttribute xeFunctionGetAttribute;
    pfn_xeCommandListEncodeDispatchFunction xeCommandListEncodeDispatchFunction;
    pfn_xeCommandGraphEncodeDispatchFunction xeCommandGraphEncodeDispatchFunction;
    pfn_xeCommandListEncodeDispatchFunctionIndirect xeCommandListEncodeDispatchFunctionIndirect;
    pfn_xeCommandGraphEncodeDispatchFunctionIndirect xeCommandGraphEncodeDispatchFunctionIndirect;
    pfn_xeCommandListEncodeDispatchHostFunction xeCommandListEncodeDispatchHostFunction;
    pfn_xeCommandGraphEncodeDispatchHostFunction xeCommandGraphEncodeDispatchHostFunction;
    pfn_xeDeviceCreateEvent xeDeviceCreateEvent;
    pfn_xeDevicePlaceEvent xeDevicePlaceEvent;
    pfn_xeEventDestroy xeEventDestroy;
    pfn_xeCommandListEncodeSignalEvent xeCommandListEncodeSignalEvent;
    pfn_xeCommandListEncodeWaitOnEvent xeCommandListEncodeWaitOnEvent;
    pfn_xeCommandListEncodeSignalMultipleEvents xeCommandListEncodeSignalMultipleEvents;
    pfn_xeCommandListEncodeWaitOnMultipleEvents xeCommandListEncodeWaitOnMultipleEvents;
    pfn_xeHostSignalEvent xeHostSignalEvent;
    pfn_xeHostWaitOnEvent xeHostWaitOnEvent;
    pfn_xeHostSignalMultipleEvents xeHostSignalMultipleEvents;
    pfn_xeHostWaitOnMultipleEvents xeHostWaitOnMultipleEvents;
    pfn_xeEventQueryStatus xeEventQueryStatus;
    pfn_xeEventQueryElapsedTime xeEventQueryElapsedTime;
    pfn_xeEventQueryMetricsData xeEventQueryMetricsData;
    pfn_xeCommandListEncodeEventReset xeCommandListEncodeEventReset;
    pfn_xeEventReset xeEventReset;
#if XE_ENABLE_OCL_INTEROP
    pfn_xeDeviceRegisterCLMemory xeDeviceRegisterCLMemory;
#endif // XE_ENABLE_OCL_INTEROP
#if XE_ENABLE_OCL_INTEROP
    pfn_xeDeviceRegisterCLProgram xeDeviceRegisterCLProgram;
#endif // XE_ENABLE_OCL_INTEROP
#if XE_ENABLE_OCL_INTEROP
    pfn_xeDeviceRegisterCLCommandQueue xeDeviceRegisterCLCommandQueue;
#endif // XE_ENABLE_OCL_INTEROP
    pfn_xeDeviceCreateImage xeDeviceCreateImage;
    pfn_xeImageDestroy xeImageDestroy;
    pfn_xeDeviceCreateCommandQueue xeDeviceCreateCommandQueue;
    pfn_xeCommandQueueDestroy xeCommandQueueDestroy;
    pfn_xeCommandQueueEnqueueCommandLists xeCommandQueueEnqueueCommandLists;
    pfn_xeCommandQueueSynchronize xeCommandQueueSynchronize;
    pfn_xeCreateMemAllocator xeCreateMemAllocator;
    pfn_xeMemAllocatorDestroy xeMemAllocatorDestroy;
    pfn_xeSharedMemAlloc xeSharedMemAlloc;
    pfn_xeMemAlloc xeMemAlloc;
    pfn_xeHostMemAlloc xeHostMemAlloc;
    pfn_xeMemFree xeMemFree;
    pfn_xeMemGetProperty xeMemGetProperty;
    pfn_xeMemGetAddressRange xeMemGetAddressRange;
    pfn_xeIpcGetMemHandle xeIpcGetMemHandle;
    pfn_xeIpcOpenMemHandle xeIpcOpenMemHandle;
    pfn_xeIpcCloseMemHandle xeIpcCloseMemHandle;
    pfn_xeCommandQueueCreateFence xeCommandQueueCreateFence;
    pfn_xeFenceDestroy xeFenceDestroy;
    pfn_xeHostWaitOnFence xeHostWaitOnFence;
    pfn_xeHostWaitOnMultipleFences xeHostWaitOnMultipleFences;
    pfn_xeFenceQueryStatus xeFenceQueryStatus;
    pfn_xeFenceQueryElapsedTime xeFenceQueryElapsedTime;
    pfn_xeFenceReset xeFenceReset;
    pfn_xeDeviceMakeMemoryResident xeDeviceMakeMemoryResident;
    pfn_xeDeviceEvictMemory xeDeviceEvictMemory;
    pfn_xeDeviceMakeImageResident xeDeviceMakeImageResident;
    pfn_xeDeviceEvictImage xeDeviceEvictImage;
    pfn_xeDeviceCreateCommandList xeDeviceCreateCommandList;
    pfn_xeDeviceCopyCommandList xeDeviceCopyCommandList;
    pfn_xeCommandListDestroy xeCommandListDestroy;
    pfn_xeCommandListClose xeCommandListClose;
    pfn_xeCommandListReset xeCommandListReset;
    pfn_xeCommandListSetParameter xeCommandListSetParameter;
    pfn_xeCommandListGetParameter xeCommandListGetParameter;
    pfn_xeCommandListResetParameters xeCommandListResetParameters;
    pfn_xeCommandListEncodeCommandLists xeCommandListEncodeCommandLists;
    pfn_xeCommandListEncodeCommands xeCommandListEncodeCommands;
} xe_dispatch_table_t;

bool load_xe(void *handle, void *(*funcAddressGetter)(void *handle, const char *funcName), xe_dispatch_table_t *outTable){
    if((0 == funcAddressGetter) || (0 == outTable)){
        return false;
    }
    outTable->xeDriverGetDeviceCount = (pfn_xeDriverGetDeviceCount)funcAddressGetter(handle, "xeDriverGetDeviceCount");
    outTable->xeDriverGetDeviceUniqueIds = (pfn_xeDriverGetDeviceUniqueIds)funcAddressGetter(handle, "xeDriverGetDeviceUniqueIds");
    outTable->xeDriverGetDevice = (pfn_xeDriverGetDevice)funcAddressGetter(handle, "xeDriverGetDevice");
    outTable->xeDeviceGetSubDevice = (pfn_xeDeviceGetSubDevice)funcAddressGetter(handle, "xeDeviceGetSubDevice");
    outTable->xeDeviceGetApiVersion = (pfn_xeDeviceGetApiVersion)funcAddressGetter(handle, "xeDeviceGetApiVersion");
    outTable->xeDeviceGetProperties = (pfn_xeDeviceGetProperties)funcAddressGetter(handle, "xeDeviceGetProperties");
    outTable->xeDeviceGetComputeProperties = (pfn_xeDeviceGetComputeProperties)funcAddressGetter(handle, "xeDeviceGetComputeProperties");
    outTable->xeDeviceGetMemoryProperties = (pfn_xeDeviceGetMemoryProperties)funcAddressGetter(handle, "xeDeviceGetMemoryProperties");
    outTable->xeDeviceGetLinkProperties = (pfn_xeDeviceGetLinkProperties)funcAddressGetter(handle, "xeDeviceGetLinkProperties");
    outTable->xeDeviceCanAccessPeer = (pfn_xeDeviceCanAccessPeer)funcAddressGetter(handle, "xeDeviceCanAccessPeer");
    outTable->xeDeviceSetIntermediateCacheConfig = (pfn_xeDeviceSetIntermediateCacheConfig)funcAddressGetter(handle, "xeDeviceSetIntermediateCacheConfig");
    outTable->xeDeviceSetLastLevelCacheConfig = (pfn_xeDeviceSetLastLevelCacheConfig)funcAddressGetter(handle, "xeDeviceSetLastLevelCacheConfig");
    outTable->xeDeviceCreateCommandGraph = (pfn_xeDeviceCreateCommandGraph)funcAddressGetter(handle, "xeDeviceCreateCommandGraph");
    outTable->xeCommandGraphDestroy = (pfn_xeCommandGraphDestroy)funcAddressGetter(handle, "xeCommandGraphDestroy");
    outTable->xeCommandGraphClose = (pfn_xeCommandGraphClose)funcAddressGetter(handle, "xeCommandGraphClose");
    outTable->xeCommandGraphReset = (pfn_xeCommandGraphReset)funcAddressGetter(handle, "xeCommandGraphReset");
    outTable->xeCommandListEncodeExecutionBarrier = (pfn_xeCommandListEncodeExecutionBarrier)funcAddressGetter(handle, "xeCommandListEncodeExecutionBarrier");
    outTable->xeDeviceCreateSemaphore = (pfn_xeDeviceCreateSemaphore)funcAddressGetter(handle, "xeDeviceCreateSemaphore");
    outTable->xeSemaphoreDestroy = (pfn_xeSemaphoreDestroy)funcAddressGetter(handle, "xeSemaphoreDestroy");
    outTable->xeCommandListEncodeSemaphoreSignal = (pfn_xeCommandListEncodeSemaphoreSignal)funcAddressGetter(handle, "xeCommandListEncodeSemaphoreSignal");
    outTable->xeCommandListEncodeSemaphoreWait = (pfn_xeCommandListEncodeSemaphoreWait)funcAddressGetter(handle, "xeCommandListEncodeSemaphoreWait");
    outTable->xeSemaphoreQueryValue = (pfn_xeSemaphoreQueryValue)funcAddressGetter(handle, "xeSemaphoreQueryValue");
    outTable->xeSemaphoreReset = (pfn_xeSemaphoreReset)funcAddressGetter(handle, "xeSemaphoreReset");
    outTable->xeDriverInit = (pfn_xeDriverInit)funcAddressGetter(handle, "xeDriverInit");
    outTable->xeDriverGetVersion = (pfn_xeDriverGetVersion)funcAddressGetter(handle, "xeDriverGetVersion");
    outTable->xeCommandListEncodeMemoryCopy = (pfn_xeCommandListEncodeMemoryCopy)funcAddressGetter(handle, "xeCommandListEncodeMemoryCopy");
    outTable->xeCommandListEncodeMemorySet = (pfn_xeCommandListEncodeMemorySet)funcAddressGetter(handle, "xeCommandListEncodeMemorySet");
    outTable->xeCommandListEncodeImageCopy = (pfn_xeCommandListEncodeImageCopy)funcAddressGetter(handle, "xeCommandListEncodeImageCopy");
    outTable->xeCommandListEncodeImageCopyRegion = (pfn_xeCommandListEncodeImageCopyRegion)funcAddressGetter(handle, "xeCommandListEncodeImageCopyRegion");
    outTable->xeCommandListEncodeImageCopyToMemory = (pfn_xeCommandListEncodeImageCopyToMemory)funcAddressGetter(handle, "xeCommandListEncodeImageCopyToMemory");
    outTable->xeCommandListEncodeImageCopyFromMemory = (pfn_xeCommandListEncodeImageCopyFromMemory)funcAddressGetter(handle, "xeCommandListEncodeImageCopyFromMemory");
    outTable->xeCommandListEncodeMemoryPrefetch = (pfn_xeCommandListEncodeMemoryPrefetch)funcAddressGetter(handle, "xeCommandListEncodeMemoryPrefetch");
    outTable->xeCommandListEncodeMemAdvise = (pfn_xeCommandListEncodeMemAdvise)funcAddressGetter(handle, "xeCommandListEncodeMemAdvise");
    outTable->xeDeviceCreateModule = (pfn_xeDeviceCreateModule)funcAddressGetter(handle, "xeDeviceCreateModule");
    outTable->xeModuleDestroy = (pfn_xeModuleDestroy)funcAddressGetter(handle, "xeModuleDestroy");
    outTable->xeModuleBuildLogDestroy = (pfn_xeModuleBuildLogDestroy)funcAddressGetter(handle, "xeModuleBuildLogDestroy");
    outTable->xeModuleBuildLogGetString = (pfn_xeModuleBuildLogGetString)funcAddressGetter(handle, "xeModuleBuildLogGetString");
    outTable->xeModuleGetNativeBinary = (pfn_xeModuleGetNativeBinary)funcAddressGetter(handle, "xeModuleGetNativeBinary");
    outTable->xeModuleCreateFunction = (pfn_xeModuleCreateFunction)funcAddressGetter(handle, "xeModuleCreateFunction");
    outTable->xeFunctionDestroy = (pfn_xeFunctionDestroy)funcAddressGetter(handle, "xeFunctionDestroy");
    outTable->xeModuleGetFunctionPointer = (pfn_xeModuleGetFunctionPointer)funcAddressGetter(handle, "xeModuleGetFunctionPointer");
    outTable->xeFunctionSetGroupSize = (pfn_xeFunctionSetGroupSize)funcAddressGetter(handle, "xeFunctionSetGroupSize");
    outTable->xeFunctionSuggestGroupSize = (pfn_xeFunctionSuggestGroupSize)funcAddressGetter(handle, "xeFunctionSuggestGroupSize");
    outTable->xeFunctionSetArgumentValue = (pfn_xeFunctionSetArgumentValue)funcAddressGetter(handle, "xeFunctionSetArgumentValue");
    outTable->xeFunctionSetAttribute = (pfn_xeFunctionSetAttribute)funcAddressGetter(handle, "xeFunctionSetAttribute");
    outTable->xeFunctionGetAttribute = (pfn_xeFunctionGetAttribute)funcAddressGetter(handle, "xeFunctionGetAttribute");
    outTable->xeCommandListEncodeDispatchFunction = (pfn_xeCommandListEncodeDispatchFunction)funcAddressGetter(handle, "xeCommandListEncodeDispatchFunction");
    outTable->xeCommandGraphEncodeDispatchFunction = (pfn_xeCommandGraphEncodeDispatchFunction)funcAddressGetter(handle, "xeCommandGraphEncodeDispatchFunction");
    outTable->xeCommandListEncodeDispatchFunctionIndirect = (pfn_xeCommandListEncodeDispatchFunctionIndirect)funcAddressGetter(handle, "xeCommandListEncodeDispatchFunctionIndirect");
    outTable->xeCommandGraphEncodeDispatchFunctionIndirect = (pfn_xeCommandGraphEncodeDispatchFunctionIndirect)funcAddressGetter(handle, "xeCommandGraphEncodeDispatchFunctionIndirect");
    outTable->xeCommandListEncodeDispatchHostFunction = (pfn_xeCommandListEncodeDispatchHostFunction)funcAddressGetter(handle, "xeCommandListEncodeDispatchHostFunction");
    outTable->xeCommandGraphEncodeDispatchHostFunction = (pfn_xeCommandGraphEncodeDispatchHostFunction)funcAddressGetter(handle, "xeCommandGraphEncodeDispatchHostFunction");
    outTable->xeDeviceCreateEvent = (pfn_xeDeviceCreateEvent)funcAddressGetter(handle, "xeDeviceCreateEvent");
    outTable->xeDevicePlaceEvent = (pfn_xeDevicePlaceEvent)funcAddressGetter(handle, "xeDevicePlaceEvent");
    outTable->xeEventDestroy = (pfn_xeEventDestroy)funcAddressGetter(handle, "xeEventDestroy");
    outTable->xeCommandListEncodeSignalEvent = (pfn_xeCommandListEncodeSignalEvent)funcAddressGetter(handle, "xeCommandListEncodeSignalEvent");
    outTable->xeCommandListEncodeWaitOnEvent = (pfn_xeCommandListEncodeWaitOnEvent)funcAddressGetter(handle, "xeCommandListEncodeWaitOnEvent");
    outTable->xeCommandListEncodeSignalMultipleEvents = (pfn_xeCommandListEncodeSignalMultipleEvents)funcAddressGetter(handle, "xeCommandListEncodeSignalMultipleEvents");
    outTable->xeCommandListEncodeWaitOnMultipleEvents = (pfn_xeCommandListEncodeWaitOnMultipleEvents)funcAddressGetter(handle, "xeCommandListEncodeWaitOnMultipleEvents");
    outTable->xeHostSignalEvent = (pfn_xeHostSignalEvent)funcAddressGetter(handle, "xeHostSignalEvent");
    outTable->xeHostWaitOnEvent = (pfn_xeHostWaitOnEvent)funcAddressGetter(handle, "xeHostWaitOnEvent");
    outTable->xeHostSignalMultipleEvents = (pfn_xeHostSignalMultipleEvents)funcAddressGetter(handle, "xeHostSignalMultipleEvents");
    outTable->xeHostWaitOnMultipleEvents = (pfn_xeHostWaitOnMultipleEvents)funcAddressGetter(handle, "xeHostWaitOnMultipleEvents");
    outTable->xeEventQueryStatus = (pfn_xeEventQueryStatus)funcAddressGetter(handle, "xeEventQueryStatus");
    outTable->xeEventQueryElapsedTime = (pfn_xeEventQueryElapsedTime)funcAddressGetter(handle, "xeEventQueryElapsedTime");
    outTable->xeEventQueryMetricsData = (pfn_xeEventQueryMetricsData)funcAddressGetter(handle, "xeEventQueryMetricsData");
    outTable->xeCommandListEncodeEventReset = (pfn_xeCommandListEncodeEventReset)funcAddressGetter(handle, "xeCommandListEncodeEventReset");
    outTable->xeEventReset = (pfn_xeEventReset)funcAddressGetter(handle, "xeEventReset");
#if XE_ENABLE_OCL_INTEROP
    outTable->xeDeviceRegisterCLMemory = (pfn_xeDeviceRegisterCLMemory)funcAddressGetter(handle, "xeDeviceRegisterCLMemory");
#endif // XE_ENABLE_OCL_INTEROP
#if XE_ENABLE_OCL_INTEROP
    outTable->xeDeviceRegisterCLProgram = (pfn_xeDeviceRegisterCLProgram)funcAddressGetter(handle, "xeDeviceRegisterCLProgram");
#endif // XE_ENABLE_OCL_INTEROP
#if XE_ENABLE_OCL_INTEROP
    outTable->xeDeviceRegisterCLCommandQueue = (pfn_xeDeviceRegisterCLCommandQueue)funcAddressGetter(handle, "xeDeviceRegisterCLCommandQueue");
#endif // XE_ENABLE_OCL_INTEROP
    outTable->xeDeviceCreateImage = (pfn_xeDeviceCreateImage)funcAddressGetter(handle, "xeDeviceCreateImage");
    outTable->xeImageDestroy = (pfn_xeImageDestroy)funcAddressGetter(handle, "xeImageDestroy");
    outTable->xeDeviceCreateCommandQueue = (pfn_xeDeviceCreateCommandQueue)funcAddressGetter(handle, "xeDeviceCreateCommandQueue");
    outTable->xeCommandQueueDestroy = (pfn_xeCommandQueueDestroy)funcAddressGetter(handle, "xeCommandQueueDestroy");
    outTable->xeCommandQueueEnqueueCommandLists = (pfn_xeCommandQueueEnqueueCommandLists)funcAddressGetter(handle, "xeCommandQueueEnqueueCommandLists");
    outTable->xeCommandQueueSynchronize = (pfn_xeCommandQueueSynchronize)funcAddressGetter(handle, "xeCommandQueueSynchronize");
    outTable->xeCreateMemAllocator = (pfn_xeCreateMemAllocator)funcAddressGetter(handle, "xeCreateMemAllocator");
    outTable->xeMemAllocatorDestroy = (pfn_xeMemAllocatorDestroy)funcAddressGetter(handle, "xeMemAllocatorDestroy");
    outTable->xeSharedMemAlloc = (pfn_xeSharedMemAlloc)funcAddressGetter(handle, "xeSharedMemAlloc");
    outTable->xeMemAlloc = (pfn_xeMemAlloc)funcAddressGetter(handle, "xeMemAlloc");
    outTable->xeHostMemAlloc = (pfn_xeHostMemAlloc)funcAddressGetter(handle, "xeHostMemAlloc");
    outTable->xeMemFree = (pfn_xeMemFree)funcAddressGetter(handle, "xeMemFree");
    outTable->xeMemGetProperty = (pfn_xeMemGetProperty)funcAddressGetter(handle, "xeMemGetProperty");
    outTable->xeMemGetAddressRange = (pfn_xeMemGetAddressRange)funcAddressGetter(handle, "xeMemGetAddressRange");
    outTable->xeIpcGetMemHandle = (pfn_xeIpcGetMemHandle)funcAddressGetter(handle, "xeIpcGetMemHandle");
    outTable->xeIpcOpenMemHandle = (pfn_xeIpcOpenMemHandle)funcAddressGetter(handle, "xeIpcOpenMemHandle");
    outTable->xeIpcCloseMemHandle = (pfn_xeIpcCloseMemHandle)funcAddressGetter(handle, "xeIpcCloseMemHandle");
    outTable->xeCommandQueueCreateFence = (pfn_xeCommandQueueCreateFence)funcAddressGetter(handle, "xeCommandQueueCreateFence");
    outTable->xeFenceDestroy = (pfn_xeFenceDestroy)funcAddressGetter(handle, "xeFenceDestroy");
    outTable->xeHostWaitOnFence = (pfn_xeHostWaitOnFence)funcAddressGetter(handle, "xeHostWaitOnFence");
    outTable->xeHostWaitOnMultipleFences = (pfn_xeHostWaitOnMultipleFences)funcAddressGetter(handle, "xeHostWaitOnMultipleFences");
    outTable->xeFenceQueryStatus = (pfn_xeFenceQueryStatus)funcAddressGetter(handle, "xeFenceQueryStatus");
    outTable->xeFenceQueryElapsedTime = (pfn_xeFenceQueryElapsedTime)funcAddressGetter(handle, "xeFenceQueryElapsedTime");
    outTable->xeFenceReset = (pfn_xeFenceReset)funcAddressGetter(handle, "xeFenceReset");
    outTable->xeDeviceMakeMemoryResident = (pfn_xeDeviceMakeMemoryResident)funcAddressGetter(handle, "xeDeviceMakeMemoryResident");
    outTable->xeDeviceEvictMemory = (pfn_xeDeviceEvictMemory)funcAddressGetter(handle, "xeDeviceEvictMemory");
    outTable->xeDeviceMakeImageResident = (pfn_xeDeviceMakeImageResident)funcAddressGetter(handle, "xeDeviceMakeImageResident");
    outTable->xeDeviceEvictImage = (pfn_xeDeviceEvictImage)funcAddressGetter(handle, "xeDeviceEvictImage");
    outTable->xeDeviceCreateCommandList = (pfn_xeDeviceCreateCommandList)funcAddressGetter(handle, "xeDeviceCreateCommandList");
    outTable->xeDeviceCopyCommandList = (pfn_xeDeviceCopyCommandList)funcAddressGetter(handle, "xeDeviceCopyCommandList");
    outTable->xeCommandListDestroy = (pfn_xeCommandListDestroy)funcAddressGetter(handle, "xeCommandListDestroy");
    outTable->xeCommandListClose = (pfn_xeCommandListClose)funcAddressGetter(handle, "xeCommandListClose");
    outTable->xeCommandListReset = (pfn_xeCommandListReset)funcAddressGetter(handle, "xeCommandListReset");
    outTable->xeCommandListSetParameter = (pfn_xeCommandListSetParameter)funcAddressGetter(handle, "xeCommandListSetParameter");
    outTable->xeCommandListGetParameter = (pfn_xeCommandListGetParameter)funcAddressGetter(handle, "xeCommandListGetParameter");
    outTable->xeCommandListResetParameters = (pfn_xeCommandListResetParameters)funcAddressGetter(handle, "xeCommandListResetParameters");
    outTable->xeCommandListEncodeCommandLists = (pfn_xeCommandListEncodeCommandLists)funcAddressGetter(handle, "xeCommandListEncodeCommandLists");
    outTable->xeCommandListEncodeCommands = (pfn_xeCommandListEncodeCommands)funcAddressGetter(handle, "xeCommandListEncodeCommands");
    if(0 == outTable->xeDriverGetDeviceCount){
        return false;
    }
    if(0 == outTable->xeDriverGetDeviceUniqueIds){
        return false;
    }
    if(0 == outTable->xeDriverGetDevice){
        return false;
    }
    if(0 == outTable->xeDeviceGetSubDevice){
        return false;
    }
    if(0 == outTable->xeDeviceGetApiVersion){
        return false;
    }
    if(0 == outTable->xeDeviceGetProperties){
        return false;
    }
    if(0 == outTable->xeDeviceGetComputeProperties){
        return false;
    }
    if(0 == outTable->xeDeviceGetMemoryProperties){
        return false;
    }
    if(0 == outTable->xeDeviceGetLinkProperties){
        return false;
    }
    if(0 == outTable->xeDeviceCanAccessPeer){
        return false;
    }
    if(0 == outTable->xeDeviceSetIntermediateCacheConfig){
        return false;
    }
    if(0 == outTable->xeDeviceSetLastLevelCacheConfig){
        return false;
    }
    if(0 == outTable->xeDeviceCreateCommandGraph){
        return false;
    }
    if(0 == outTable->xeCommandGraphDestroy){
        return false;
    }
    if(0 == outTable->xeCommandGraphClose){
        return false;
    }
    if(0 == outTable->xeCommandGraphReset){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeExecutionBarrier){
        return false;
    }
    if(0 == outTable->xeDeviceCreateSemaphore){
        return false;
    }
    if(0 == outTable->xeSemaphoreDestroy){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeSemaphoreSignal){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeSemaphoreWait){
        return false;
    }
    if(0 == outTable->xeSemaphoreQueryValue){
        return false;
    }
    if(0 == outTable->xeSemaphoreReset){
        return false;
    }
    if(0 == outTable->xeDriverInit){
        return false;
    }
    if(0 == outTable->xeDriverGetVersion){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeMemoryCopy){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeMemorySet){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeImageCopy){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeImageCopyRegion){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeImageCopyToMemory){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeImageCopyFromMemory){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeMemoryPrefetch){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeMemAdvise){
        return false;
    }
    if(0 == outTable->xeDeviceCreateModule){
        return false;
    }
    if(0 == outTable->xeModuleDestroy){
        return false;
    }
    if(0 == outTable->xeModuleBuildLogDestroy){
        return false;
    }
    if(0 == outTable->xeModuleBuildLogGetString){
        return false;
    }
    if(0 == outTable->xeModuleGetNativeBinary){
        return false;
    }
    if(0 == outTable->xeModuleCreateFunction){
        return false;
    }
    if(0 == outTable->xeFunctionDestroy){
        return false;
    }
    if(0 == outTable->xeModuleGetFunctionPointer){
        return false;
    }
    if(0 == outTable->xeFunctionSetGroupSize){
        return false;
    }
    if(0 == outTable->xeFunctionSuggestGroupSize){
        return false;
    }
    if(0 == outTable->xeFunctionSetArgumentValue){
        return false;
    }
    if(0 == outTable->xeFunctionSetAttribute){
        return false;
    }
    if(0 == outTable->xeFunctionGetAttribute){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeDispatchFunction){
        return false;
    }
    if(0 == outTable->xeCommandGraphEncodeDispatchFunction){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeDispatchFunctionIndirect){
        return false;
    }
    if(0 == outTable->xeCommandGraphEncodeDispatchFunctionIndirect){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeDispatchHostFunction){
        return false;
    }
    if(0 == outTable->xeCommandGraphEncodeDispatchHostFunction){
        return false;
    }
    if(0 == outTable->xeDeviceCreateEvent){
        return false;
    }
    if(0 == outTable->xeDevicePlaceEvent){
        return false;
    }
    if(0 == outTable->xeEventDestroy){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeSignalEvent){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeWaitOnEvent){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeSignalMultipleEvents){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeWaitOnMultipleEvents){
        return false;
    }
    if(0 == outTable->xeHostSignalEvent){
        return false;
    }
    if(0 == outTable->xeHostWaitOnEvent){
        return false;
    }
    if(0 == outTable->xeHostSignalMultipleEvents){
        return false;
    }
    if(0 == outTable->xeHostWaitOnMultipleEvents){
        return false;
    }
    if(0 == outTable->xeEventQueryStatus){
        return false;
    }
    if(0 == outTable->xeEventQueryElapsedTime){
        return false;
    }
    if(0 == outTable->xeEventQueryMetricsData){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeEventReset){
        return false;
    }
    if(0 == outTable->xeEventReset){
        return false;
    }
#if XE_ENABLE_OCL_INTEROP
    if(0 == outTable->xeDeviceRegisterCLMemory){
        return false;
    }
#endif // XE_ENABLE_OCL_INTEROP
#if XE_ENABLE_OCL_INTEROP
    if(0 == outTable->xeDeviceRegisterCLProgram){
        return false;
    }
#endif // XE_ENABLE_OCL_INTEROP
#if XE_ENABLE_OCL_INTEROP
    if(0 == outTable->xeDeviceRegisterCLCommandQueue){
        return false;
    }
#endif // XE_ENABLE_OCL_INTEROP
    if(0 == outTable->xeDeviceCreateImage){
        return false;
    }
    if(0 == outTable->xeImageDestroy){
        return false;
    }
    if(0 == outTable->xeDeviceCreateCommandQueue){
        return false;
    }
    if(0 == outTable->xeCommandQueueDestroy){
        return false;
    }
    if(0 == outTable->xeCommandQueueEnqueueCommandLists){
        return false;
    }
    if(0 == outTable->xeCommandQueueSynchronize){
        return false;
    }
    if(0 == outTable->xeCreateMemAllocator){
        return false;
    }
    if(0 == outTable->xeMemAllocatorDestroy){
        return false;
    }
    if(0 == outTable->xeSharedMemAlloc){
        return false;
    }
    if(0 == outTable->xeMemAlloc){
        return false;
    }
    if(0 == outTable->xeHostMemAlloc){
        return false;
    }
    if(0 == outTable->xeMemFree){
        return false;
    }
    if(0 == outTable->xeMemGetProperty){
        return false;
    }
    if(0 == outTable->xeMemGetAddressRange){
        return false;
    }
    if(0 == outTable->xeIpcGetMemHandle){
        return false;
    }
    if(0 == outTable->xeIpcOpenMemHandle){
        return false;
    }
    if(0 == outTable->xeIpcCloseMemHandle){
        return false;
    }
    if(0 == outTable->xeCommandQueueCreateFence){
        return false;
    }
    if(0 == outTable->xeFenceDestroy){
        return false;
    }
    if(0 == outTable->xeHostWaitOnFence){
        return false;
    }
    if(0 == outTable->xeHostWaitOnMultipleFences){
        return false;
    }
    if(0 == outTable->xeFenceQueryStatus){
        return false;
    }
    if(0 == outTable->xeFenceQueryElapsedTime){
        return false;
    }
    if(0 == outTable->xeFenceReset){
        return false;
    }
    if(0 == outTable->xeDeviceMakeMemoryResident){
        return false;
    }
    if(0 == outTable->xeDeviceEvictMemory){
        return false;
    }
    if(0 == outTable->xeDeviceMakeImageResident){
        return false;
    }
    if(0 == outTable->xeDeviceEvictImage){
        return false;
    }
    if(0 == outTable->xeDeviceCreateCommandList){
        return false;
    }
    if(0 == outTable->xeDeviceCopyCommandList){
        return false;
    }
    if(0 == outTable->xeCommandListDestroy){
        return false;
    }
    if(0 == outTable->xeCommandListClose){
        return false;
    }
    if(0 == outTable->xeCommandListReset){
        return false;
    }
    if(0 == outTable->xeCommandListSetParameter){
        return false;
    }
    if(0 == outTable->xeCommandListGetParameter){
        return false;
    }
    if(0 == outTable->xeCommandListResetParameters){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeCommandLists){
        return false;
    }
    if(0 == outTable->xeCommandListEncodeCommands){
        return false;
    }
    return true;
}
#endif // _XE_LOADER_H
