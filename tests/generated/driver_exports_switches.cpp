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
* @file xe_driver_exports_switches.h
*
* @brief Intel Xe Driver Exports
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/driver_exports_switches.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_DRIVER_EXPORTS_SWITCHES_H
#define _XE_DRIVER_EXPORTS_SWITCHES_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_all.h"

#define ENABLE_xeCommandListEncodeExecutionBarrier 0
#define ENABLE_xeDeviceRegisterCLMemory 0
#define ENABLE_xeDeviceRegisterCLProgram 0
#define ENABLE_xeDeviceRegisterCLCommandQueue 0
#define ENABLE_xeDeviceCreateCommandGraph 0
#define ENABLE_xeCommandGraphDestroy 0
#define ENABLE_xeCommandGraphClose 0
#define ENABLE_xeCommandGraphReset 0
#define ENABLE_xeDeviceCreateCommandList 1
#define ENABLE_xeDeviceCopyCommandList 0
#define ENABLE_xeCommandListDestroy 1
#define ENABLE_xeCommandListClose 1
#define ENABLE_xeCommandListReset 0
#define ENABLE_xeCommandListSetParameter 0
#define ENABLE_xeCommandListGetParameter 0
#define ENABLE_xeCommandListResetParameters 0
#define ENABLE_xeCommandListEncodeCommandLists 0
#define ENABLE_xeCommandListEncodeCommands 0
#define ENABLE_xeDeviceCreateCommandQueue 1
#define ENABLE_xeCommandQueueDestroy 0
#define ENABLE_xeCommandQueueEnqueueCommandLists 1
#define ENABLE_xeCommandQueueSynchronize 0
#define ENABLE_xeCommandListEncodeMemoryCopy 0
#define ENABLE_xeCommandListEncodeImageCopy 0
#define ENABLE_xeCommandListEncodeImageCopyRegion 0
#define ENABLE_xeCommandListEncodeImageCopyToMemory 0
#define ENABLE_xeCommandListEncodeImageCopyFromMemory 0
#define ENABLE_xeCommandListEncodeMemoryPrefetch 0
#define ENABLE_xeCommandListEncodeMemAdvise 0
#define ENABLE_xeDriverGetDeviceCount 0
#define ENABLE_xeDriverGetDeviceUniqueIds 0
#define ENABLE_xeDriverGetDevice 1
#define ENABLE_xeDeviceGetSubDevice 0
#define ENABLE_xeDeviceGetApiVersion 0
#define ENABLE_xeDeviceGetProperties 0
#define ENABLE_xeDeviceGetComputeProperties 0
#define ENABLE_xeDeviceGetMemoryProperties 0
#define ENABLE_xeDeviceGetLinkProperties 0
#define ENABLE_xeDeviceCanAccessPeer 0
#define ENABLE_xeDeviceSetIntermediateCacheConfig 0
#define ENABLE_xeDeviceSetLastLevelCacheConfig 0
#define ENABLE_xeDriverInit 1
#define ENABLE_xeDriverGetVersion 0
#define ENABLE_xeDeviceCreateEvent 1
#define ENABLE_xeDevicePlaceEvent 0
#define ENABLE_xeEventDestroy 0
#define ENABLE_xeCommandListEncodeSignalEvent 1
#define ENABLE_xeCommandListEncodeWaitOnEvent 1
#define ENABLE_xeCommandListEncodeSignalMultipleEvents 0
#define ENABLE_xeCommandListEncodeWaitOnMultipleEvents 0
#define ENABLE_xeHostSignalEvent 0
#define ENABLE_xeHostWaitOnEvent 0
#define ENABLE_xeHostSignalMultipleEvents 0
#define ENABLE_xeHostWaitOnMultipleEvents 0
#define ENABLE_xeEventQueryStatus 0
#define ENABLE_xeEventQueryElapsedTime 0
#define ENABLE_xeEventQueryMetricsData 0
#define ENABLE_xeCommandListEncodeEventReset 0
#define ENABLE_xeEventReset 0
#define ENABLE_xeCommandQueueCreateFence 0
#define ENABLE_xeFenceDestroy 0
#define ENABLE_xeHostWaitOnFence 0
#define ENABLE_xeHostWaitOnMultipleFences 0
#define ENABLE_xeFenceQueryStatus 0
#define ENABLE_xeFenceQueryElapsedTime 0
#define ENABLE_xeFenceReset 0
#define ENABLE_xeDeviceCreateImage 0
#define ENABLE_xeImageDestroy 0
#define ENABLE_xeCreateMemAllocator 0
#define ENABLE_xeMemAllocatorDestroy 0
#define ENABLE_xeSharedMemAlloc 1
#define ENABLE_xeMemAlloc 0
#define ENABLE_xeHostMemAlloc 0
#define ENABLE_xeMemFree 0
#define ENABLE_xeMemGetProperty 0
#define ENABLE_xeMemGetAddressRange 0
#define ENABLE_xeIpcGetMemHandle 0
#define ENABLE_xeIpcOpenMemHandle 0
#define ENABLE_xeIpcCloseMemHandle 0
#define ENABLE_xeDeviceCreateModule 1
#define ENABLE_xeModuleDestroy 1
#define ENABLE_xeModuleBuildLogDestroy 0
#define ENABLE_xeModuleBuildLogGetString 0
#define ENABLE_xeModuleGetNativeBinary 0
#define ENABLE_xeModuleCreateFunction 1
#define ENABLE_xeFunctionDestroy 1
#define ENABLE_xeFunctionCreateFunctionArgs 1
#define ENABLE_xeFunctionArgsDestroy 1
#define ENABLE_xeFunctionArgsSetValue 1
#define ENABLE_xeFunctionArgsSetAttribute 0
#define ENABLE_xeFunctionQueryAttribute 0
#define ENABLE_xeCommandListEncodeDispatchFunction 1
#define ENABLE_xeCommandGraphEncodeDispatchFunction 0
#define ENABLE_xeCommandListEncodeDispatchFunctionIndirect 0
#define ENABLE_xeCommandGraphEncodeDispatchFunctionIndirect 0
#define ENABLE_xeFunctionSuggestGroupSize 0
#define ENABLE_xeCommandListEncodeDispatchHostFunction 0
#define ENABLE_xeCommandGraphEncodeDispatchHostFunction 0
#define ENABLE_xeDeviceMakeMemoryResident 0
#define ENABLE_xeDeviceEvictMemory 0
#define ENABLE_xeDeviceMakeImageResident 0
#define ENABLE_xeDeviceEvictImage 0
#define ENABLE_xeDeviceCreateSemaphore 0
#define ENABLE_xeSemaphoreDestroy 0
#define ENABLE_xeCommandListEncodeSemaphoreSignal 0
#define ENABLE_xeCommandListEncodeSemaphoreWait 0
#define ENABLE_xeSemaphoreQueryValue 0
#define ENABLE_xeSemaphoreReset 0

typedef struct _cl_mem* cl_mem;
typedef struct _cl_command_queue* cl_command_queue;
typedef struct _cl_context* cl_context;
typedef struct _cl_program* cl_program;

#if !(ENABLE_xeCommandListEncodeExecutionBarrier)
xe_result_t __xecall xeCommandListEncodeExecutionBarrier(
    xe_command_list_handle_t hCommandList
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceRegisterCLMemory)
xe_result_t __xecall xeDeviceRegisterCLMemory(
    xe_device_handle_t hDevice,
    cl_context context,
    cl_mem mem,
    void** ptr
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceRegisterCLProgram)
xe_result_t __xecall xeDeviceRegisterCLProgram(
    xe_device_handle_t hDevice,
    cl_context context,
    cl_program program,
    xe_module_handle_t* phModule
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceRegisterCLCommandQueue)
xe_result_t __xecall xeDeviceRegisterCLCommandQueue(
    xe_device_handle_t hDevice,
    cl_context context,
    cl_command_queue command_queue,
    xe_command_queue_handle_t* phCommandQueue
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceCreateCommandGraph)
xe_result_t __xecall xeDeviceCreateCommandGraph(
    xe_device_handle_t hDevice,
    const xe_command_graph_desc_t* desc,
    xe_command_graph_handle_t* phCommandGraph
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandGraphDestroy)
xe_result_t __xecall xeCommandGraphDestroy(
    xe_command_graph_handle_t hCommandGraph
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandGraphClose)
xe_result_t __xecall xeCommandGraphClose(
    xe_command_graph_handle_t hCommandGraph
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandGraphReset)
xe_result_t __xecall xeCommandGraphReset(
    xe_command_graph_handle_t hCommandGraph
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceCreateCommandList)
xe_result_t __xecall xeDeviceCreateCommandList(
    xe_device_handle_t hDevice,
    const xe_command_list_desc_t* desc,
    xe_command_list_handle_t* phCommandList
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceCopyCommandList)
xe_result_t __xecall xeDeviceCopyCommandList(
    xe_device_handle_t hDevice,
    xe_command_list_handle_t hCommandList,
    xe_command_list_handle_t* phCommandList
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListDestroy)
xe_result_t __xecall xeCommandListDestroy(
    xe_command_list_handle_t hCommandList
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListClose)
xe_result_t __xecall xeCommandListClose(
    xe_command_list_handle_t hCommandList
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListReset)
xe_result_t __xecall xeCommandListReset(
    xe_command_list_handle_t hCommandList
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListSetParameter)
xe_result_t __xecall xeCommandListSetParameter(
    xe_command_list_handle_t hCommandList,
    xe_command_list_parameter_t parameter,
    uint32_t value
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListGetParameter)
xe_result_t __xecall xeCommandListGetParameter(
    xe_command_list_handle_t hCommandList,
    xe_command_list_parameter_t parameter,
    uint32_t* value
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListResetParameters)
xe_result_t __xecall xeCommandListResetParameters(
    xe_command_list_handle_t hCommandList
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListEncodeCommandLists)
xe_result_t __xecall xeCommandListEncodeCommandLists(
    xe_command_list_handle_t hCommandList,
    uint32_t numCommandLists,
    xe_command_list_handle_t* phCommandLists
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListEncodeCommands)
xe_result_t __xecall xeCommandListEncodeCommands(
    xe_command_list_handle_t hCommandList,
    xe_command_format_t format,
    size_t size,
    void* pBlob
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceCreateCommandQueue)
xe_result_t __xecall xeDeviceCreateCommandQueue(
    xe_device_handle_t hDevice,
    const xe_command_queue_desc_t* desc,
    xe_command_queue_handle_t* phCommandQueue
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandQueueDestroy)
xe_result_t __xecall xeCommandQueueDestroy(
    xe_command_queue_handle_t hCommandQueue
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandQueueEnqueueCommandLists)
xe_result_t __xecall xeCommandQueueEnqueueCommandLists(
    xe_command_queue_handle_t hCommandQueue,
    uint32_t numCommandLists,
    xe_command_list_handle_t* phCommandLists,
    xe_fence_handle_t hFence
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandQueueSynchronize)
xe_result_t __xecall xeCommandQueueSynchronize(
    xe_command_queue_handle_t hCommandQueue,
    xe_synchronization_mode_t mode,
    uint32_t delay,
    uint32_t interval,
    uint32_t timeout
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListEncodeMemoryCopy)
xe_result_t __xecall xeCommandListEncodeMemoryCopy(
    xe_command_list_handle_t hCommandList,
    void* dstptr,
    const void* srcptr,
    size_t size
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListEncodeImageCopy)
xe_result_t __xecall xeCommandListEncodeImageCopy(
    xe_command_list_handle_t hCommandList,
    xe_image_handle_t hDstImage,
    xe_image_handle_t hSrcImage
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListEncodeImageCopyRegion)
xe_result_t __xecall xeCommandListEncodeImageCopyRegion(
    xe_command_list_handle_t hCommandList,
    xe_image_handle_t hDstImage,
    xe_image_region_t* pDstRegion,
    xe_image_handle_t hSrcImage,
    xe_image_region_t* pSrcRegion
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListEncodeImageCopyToMemory)
xe_result_t __xecall xeCommandListEncodeImageCopyToMemory(
    xe_command_list_handle_t hCommandList,
    void* dstptr,
    xe_image_handle_t hSrcImage,
    xe_image_region_t* pSrcRegion
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListEncodeImageCopyFromMemory)
xe_result_t __xecall xeCommandListEncodeImageCopyFromMemory(
    xe_command_list_handle_t hCommandList,
    xe_image_handle_t hDstImage,
    xe_image_region_t* pDstRegion,
    void* srcptr
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListEncodeMemoryPrefetch)
xe_result_t __xecall xeCommandListEncodeMemoryPrefetch(
    xe_command_list_handle_t hCommandList,
    const void* ptr,
    size_t count
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListEncodeMemAdvise)
xe_result_t __xecall xeCommandListEncodeMemAdvise(
    xe_command_list_handle_t hCommandList,
    xe_device_handle_t hDevice,
    const void* ptr,
    size_t size,
    xe_memory_advice_t advice
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDriverGetDeviceCount)
xe_result_t __xecall xeDriverGetDeviceCount(
    uint32_t* count
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDriverGetDeviceUniqueIds)
xe_result_t __xecall xeDriverGetDeviceUniqueIds(
    uint32_t count,
    uint32_t* pUniqueIds
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDriverGetDevice)
xe_result_t __xecall xeDriverGetDevice(
    uint32_t uniqueId,
    xe_device_handle_t* phDevice
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceGetSubDevice)
xe_result_t __xecall xeDeviceGetSubDevice(
    xe_device_handle_t hDevice,
    uint32_t ordinal,
    xe_device_handle_t* phSubDevice
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceGetApiVersion)
xe_result_t __xecall xeDeviceGetApiVersion(
    xe_device_handle_t hDevice,
    xe_api_version_t* version
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceGetProperties)
xe_result_t __xecall xeDeviceGetProperties(
    xe_device_handle_t hDevice,
    xe_device_properties_t* pDeviceProperties
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceGetComputeProperties)
xe_result_t __xecall xeDeviceGetComputeProperties(
    xe_device_handle_t hDevice,
    xe_device_compute_properties_t* pComputeProperties
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceGetMemoryProperties)
xe_result_t __xecall xeDeviceGetMemoryProperties(
    xe_device_handle_t hDevice,
    xe_device_memory_properties_t* pMemProperties
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceGetLinkProperties)
xe_result_t __xecall xeDeviceGetLinkProperties(
    uint32_t srcOrdinal,
    uint32_t dstOrdinal,
    xe_device_link_properties_t* pLinkProperties
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceCanAccessPeer)
xe_result_t __xecall xeDeviceCanAccessPeer(
    xe_device_handle_t hDevice,
    xe_device_handle_t hPeerDevice,
    bool* value
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceSetIntermediateCacheConfig)
xe_result_t __xecall xeDeviceSetIntermediateCacheConfig(
    xe_device_handle_t hDevice,
    xe_cache_config_t CacheConfig
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceSetLastLevelCacheConfig)
xe_result_t __xecall xeDeviceSetLastLevelCacheConfig(
    xe_device_handle_t hDevice,
    xe_cache_config_t CacheConfig
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDriverInit)
xe_result_t __xecall xeDriverInit(
    xe_init_flag_t flags
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDriverGetVersion)
xe_result_t __xecall xeDriverGetVersion(
    uint32_t* version
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceCreateEvent)
xe_result_t __xecall xeDeviceCreateEvent(
    xe_device_handle_t hDevice,
    const xe_event_desc_t* desc,
    xe_event_handle_t* phEvent
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDevicePlaceEvent)
xe_result_t __xecall xeDevicePlaceEvent(
    xe_device_handle_t hDevice,
    const xe_event_desc_t* desc,
    void* ptr,
    xe_event_handle_t* phEvent
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeEventDestroy)
xe_result_t __xecall xeEventDestroy(
    xe_event_handle_t hEvent
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListEncodeSignalEvent)
xe_result_t __xecall xeCommandListEncodeSignalEvent(
    xe_command_list_handle_t hCommandList,
    xe_event_handle_t hEvent
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListEncodeWaitOnEvent)
xe_result_t __xecall xeCommandListEncodeWaitOnEvent(
    xe_command_list_handle_t hCommandList,
    xe_event_handle_t hEvent
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListEncodeSignalMultipleEvents)
xe_result_t __xecall xeCommandListEncodeSignalMultipleEvents(
    xe_command_list_handle_t hCommandList,
    uint32_t numEvents,
    xe_event_handle_t* phEvents
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListEncodeWaitOnMultipleEvents)
xe_result_t __xecall xeCommandListEncodeWaitOnMultipleEvents(
    xe_command_list_handle_t hCommandList,
    uint32_t numEvents,
    xe_event_handle_t* phEvents
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeHostSignalEvent)
xe_result_t __xecall xeHostSignalEvent(
    xe_event_handle_t hEvent
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeHostWaitOnEvent)
xe_result_t __xecall xeHostWaitOnEvent(
    xe_event_handle_t hEvent,
    xe_synchronization_mode_t mode,
    uint32_t delay,
    uint32_t interval,
    uint32_t timeout
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeHostSignalMultipleEvents)
xe_result_t __xecall xeHostSignalMultipleEvents(
    uint32_t numEvents,
    xe_event_handle_t* phEvents
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeHostWaitOnMultipleEvents)
xe_result_t __xecall xeHostWaitOnMultipleEvents(
    uint32_t numEvents,
    xe_event_handle_t* phEvents,
    xe_synchronization_mode_t mode,
    uint32_t delay,
    uint32_t interval,
    uint32_t timeout
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeEventQueryStatus)
xe_result_t __xecall xeEventQueryStatus(
    xe_event_handle_t hEvent
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeEventQueryElapsedTime)
xe_result_t __xecall xeEventQueryElapsedTime(
    xe_event_handle_t hEventStart,
    xe_event_handle_t hEventEnd,
    double_t* pTime
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeEventQueryMetricsData)
xe_result_t __xecall xeEventQueryMetricsData(
    xe_event_handle_t hEventStart,
    xe_event_handle_t hEventEnd,
    size_t reportSize,
    uint32_t* pReportData
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListEncodeEventReset)
xe_result_t __xecall xeCommandListEncodeEventReset(
    xe_command_list_handle_t hCommandList,
    xe_event_handle_t hEvent
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeEventReset)
xe_result_t __xecall xeEventReset(
    xe_event_handle_t hEvent
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandQueueCreateFence)
xe_result_t __xecall xeCommandQueueCreateFence(
    xe_command_queue_handle_t hCommandQueue,
    const xe_fence_desc_t* desc,
    xe_fence_handle_t* phFence
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeFenceDestroy)
xe_result_t __xecall xeFenceDestroy(
    xe_fence_handle_t hFence
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeHostWaitOnFence)
xe_result_t __xecall xeHostWaitOnFence(
    xe_fence_handle_t hFence,
    xe_synchronization_mode_t mode,
    uint32_t delay,
    uint32_t interval,
    uint32_t timeout
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeHostWaitOnMultipleFences)
xe_result_t __xecall xeHostWaitOnMultipleFences(
    uint32_t numFences,
    xe_fence_handle_t* phFences,
    xe_synchronization_mode_t mode,
    uint32_t delay,
    uint32_t interval,
    uint32_t timeout
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeFenceQueryStatus)
xe_result_t __xecall xeFenceQueryStatus(
    xe_fence_handle_t hFence
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeFenceQueryElapsedTime)
xe_result_t __xecall xeFenceQueryElapsedTime(
    xe_fence_handle_t hFenceStart,
    xe_fence_handle_t hFenceEnd,
    double_t* pTime
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeFenceReset)
xe_result_t __xecall xeFenceReset(
    xe_fence_handle_t hFence
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceCreateImage)
xe_result_t __xecall xeDeviceCreateImage(
    xe_device_handle_t hDevice,
    const xe_image_desc_t* desc,
    xe_image_handle_t* phImage
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeImageDestroy)
xe_result_t __xecall xeImageDestroy(
    xe_image_handle_t hImage
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCreateMemAllocator)
xe_result_t __xecall xeCreateMemAllocator(
    xe_mem_allocator_handle_t* phMemAllocHandle
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeMemAllocatorDestroy)
xe_result_t __xecall xeMemAllocatorDestroy(
    xe_mem_allocator_handle_t hMemAllocHandle
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeSharedMemAlloc)
xe_result_t __xecall xeSharedMemAlloc(
    xe_mem_allocator_handle_t hMemAllocHandle,
    xe_device_handle_t hDevice,
    xe_device_mem_alloc_flag_t device_flags,
    xe_host_mem_alloc_flag_t host_flags,
    size_t size,
    size_t alignment,
    void** ptr
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeMemAlloc)
xe_result_t __xecall xeMemAlloc(
    xe_mem_allocator_handle_t hMemAllocHandle,
    xe_device_handle_t hDevice,
    xe_device_mem_alloc_flag_t flags,
    size_t size,
    size_t alignment,
    void** ptr
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeHostMemAlloc)
xe_result_t __xecall xeHostMemAlloc(
    xe_mem_allocator_handle_t hMemAllocHandle,
    xe_host_mem_alloc_flag_t flags,
    size_t size,
    size_t alignment,
    void** ptr
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeMemFree)
xe_result_t __xecall xeMemFree(
    xe_mem_allocator_handle_t hMemAllocHandle,
    const void* ptr
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeMemGetProperty)
xe_result_t __xecall xeMemGetProperty(
    xe_mem_allocator_handle_t hMemAllocHandle,
    const void* ptr,
    xe_memory_property_t property,
    void* pValue
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeMemGetAddressRange)
xe_result_t __xecall xeMemGetAddressRange(
    xe_mem_allocator_handle_t hMemAllocHandle,
    const void* ptr,
    void** pBase,
    size_t* pSize
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeIpcGetMemHandle)
xe_result_t __xecall xeIpcGetMemHandle(
    xe_mem_allocator_handle_t hMemAllocHandle,
    const void* ptr,
    xe_ipc_mem_handle_t* pIpcHandle
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeIpcOpenMemHandle)
xe_result_t __xecall xeIpcOpenMemHandle(
    xe_mem_allocator_handle_t hMemAllocHandle,
    xe_device_handle_t hDevice,
    xe_ipc_mem_handle_t handle,
    xe_ipc_memory_flag_t flags,
    void** ptr
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeIpcCloseMemHandle)
xe_result_t __xecall xeIpcCloseMemHandle(
    xe_mem_allocator_handle_t hMemAllocHandle,
    const void* ptr
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceCreateModule)
xe_result_t __xecall xeDeviceCreateModule(
    xe_device_handle_t hDevice,
    const xe_module_desc_t* desc,
    xe_module_handle_t* phModule,
    xe_module_build_log_handle_t* phBuildLog
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeModuleDestroy)
xe_result_t __xecall xeModuleDestroy(
    xe_module_handle_t hModule
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeModuleBuildLogDestroy)
xe_result_t __xecall xeModuleBuildLogDestroy(
    xe_module_build_log_handle_t hBuildLog
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeModuleBuildLogGetString)
xe_result_t __xecall xeModuleBuildLogGetString(
    xe_module_build_log_handle_t hBuildLog,
    uint32_t* pSize,
    char** pBuildLog
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeModuleGetNativeBinary)
xe_result_t __xecall xeModuleGetNativeBinary(
    xe_module_handle_t hModule,
    uint32_t* pSize,
    char** pModuleNativeBinary
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeModuleCreateFunction)
xe_result_t __xecall xeModuleCreateFunction(
    xe_module_handle_t hModule,
    const xe_function_desc_t* desc,
    xe_function_handle_t* phFunction
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeFunctionDestroy)
xe_result_t __xecall xeFunctionDestroy(
    xe_function_handle_t hFunction
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeFunctionCreateFunctionArgs)
xe_result_t __xecall xeFunctionCreateFunctionArgs(
    xe_function_handle_t hFunction,
    xe_function_args_handle_t* phFunctionArgs
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeFunctionArgsDestroy)
xe_result_t __xecall xeFunctionArgsDestroy(
    xe_function_args_handle_t hFunctionArgs
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeFunctionArgsSetValue)
xe_result_t __xecall xeFunctionArgsSetValue(
    xe_function_args_handle_t hFunctionArgs,
    uint32_t argIndex,
    size_t argSize,
    const void* pArgValue
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeFunctionArgsSetAttribute)
xe_result_t __xecall xeFunctionArgsSetAttribute(
    xe_function_args_handle_t hFunctionArgs,
    xe_function_argument_attribute_t attr,
    uint32_t value
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeFunctionQueryAttribute)
xe_result_t __xecall xeFunctionQueryAttribute(
    xe_function_handle_t hFunction,
    xe_function_attribute_t attr,
    uint32_t* pValue
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListEncodeDispatchFunction)
xe_result_t __xecall xeCommandListEncodeDispatchFunction(
    xe_command_list_handle_t hCommandList,
    xe_function_handle_t hFunction,
    xe_function_args_handle_t hFunctionArgs,
    const xe_dispatch_function_arguments_t* pDispatchFuncArgs,
    xe_event_handle_t hEvent
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandGraphEncodeDispatchFunction)
xe_result_t __xecall xeCommandGraphEncodeDispatchFunction(
    xe_command_graph_handle_t hCommandGraph,
    xe_function_handle_t hFunction,
    xe_function_args_handle_t hFunctionArgs,
    const xe_dispatch_function_arguments_t* pDispatchFuncArgs,
    xe_event_handle_t hEvent
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListEncodeDispatchFunctionIndirect)
xe_result_t __xecall xeCommandListEncodeDispatchFunctionIndirect(
    xe_command_list_handle_t hCommandList,
    xe_function_handle_t hFunction,
    xe_function_args_handle_t hFunctionArgs,
    const xe_dispatch_function_indirect_arguments_t* pDispatchArgumentsBuffer,
    xe_event_handle_t hEvent
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandGraphEncodeDispatchFunctionIndirect)
xe_result_t __xecall xeCommandGraphEncodeDispatchFunctionIndirect(
    xe_command_graph_handle_t hCommandGraph,
    xe_function_handle_t hFunction,
    xe_function_args_handle_t hFunctionArgs,
    const xe_dispatch_function_indirect_arguments_t* pDispatchArgumentsBuffer,
    xe_event_handle_t hEvent
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeFunctionSuggestGroupSize)
xe_result_t __xecall xeFunctionSuggestGroupSize(
    xe_function_handle_t hFunction,
    uint32_t globalSizeX,
    uint32_t globalSizeY,
    uint32_t globalSizeZ,
    uint32_t* groupSizeX,
    uint32_t* groupSizeY,
    uint32_t* groupSizeZ
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListEncodeDispatchHostFunction)
xe_result_t __xecall xeCommandListEncodeDispatchHostFunction(
    xe_command_list_handle_t hCommandList,
    xe_host_pfn_t pfnHostFunc,
    void* pUserData
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandGraphEncodeDispatchHostFunction)
xe_result_t __xecall xeCommandGraphEncodeDispatchHostFunction(
    xe_command_graph_handle_t hCommandGraph,
    xe_host_pfn_t pfnHostFunc,
    void* pUserData
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceMakeMemoryResident)
xe_result_t __xecall xeDeviceMakeMemoryResident(
    xe_device_handle_t hDevice,
    void* ptr,
    size_t size
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceEvictMemory)
xe_result_t __xecall xeDeviceEvictMemory(
    xe_device_handle_t hDevice,
    void* ptr,
    size_t size
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceMakeImageResident)
xe_result_t __xecall xeDeviceMakeImageResident(
    xe_device_handle_t hDevice,
    xe_image_handle_t hImage
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceEvictImage)
xe_result_t __xecall xeDeviceEvictImage(
    xe_device_handle_t hDevice,
    xe_image_handle_t hImage
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeDeviceCreateSemaphore)
xe_result_t __xecall xeDeviceCreateSemaphore(
    xe_device_handle_t hDevice,
    const xe_semaphore_desc_t* desc,
    xe_semaphore_handle_t* phSemaphore
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeSemaphoreDestroy)
xe_result_t __xecall xeSemaphoreDestroy(
    xe_semaphore_handle_t hSemaphore
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListEncodeSemaphoreSignal)
xe_result_t __xecall xeCommandListEncodeSemaphoreSignal(
    xe_command_list_handle_t hCommandList,
    xe_semaphore_handle_t hSemaphore,
    xe_semaphore_value_t value
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeCommandListEncodeSemaphoreWait)
xe_result_t __xecall xeCommandListEncodeSemaphoreWait(
    xe_command_list_handle_t hCommandList,
    xe_semaphore_handle_t hSemaphore,
    xe_semaphore_wait_operation_t operation,
    xe_semaphore_value_t value
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeSemaphoreQueryValue)
xe_result_t __xecall xeSemaphoreQueryValue(
    xe_semaphore_handle_t hSemaphore
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#if !(ENABLE_xeSemaphoreReset)
xe_result_t __xecall xeSemaphoreReset(
    xe_semaphore_handle_t hSemaphore
    ){
    return XE_RESULT_ERROR_UNSUPPORTED;
}
#endif
#endif // _XE_DRIVER_EXPORTS_SWITCHES_H
