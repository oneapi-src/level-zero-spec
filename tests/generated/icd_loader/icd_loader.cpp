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
* @file icd_loader.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/<type>/*.yml
* @endcond
*
******************************************************************************/
#include "icd_loader.h"

#include <mutex>

// TODO : Add implementation for linux
#include <Windows.h>

xe_dispatch_table_t dispatchTable = {};
bool dispatchTableInitialized = false;

#if defined(__cplusplus)
extern "C" {
#endif

__xedllport xe_result_t __xecall xeDriverInit(xe_init_flag_t flags){
    static std::mutex crit;
    {
        std::lock_guard<std::mutex> lockGuard{crit};
        
        if(dispatchTableInitialized){
            return dispatchTable.xeDriverInit(flags);
        }
        
        auto driverLibrary = LoadLibraryA("level_zero.dll"); // persistent handle
        dispatchTableInitialized = 
                load_xe(driverLibrary, 
                          [](void *library, const char *funcName)->void* { return GetProcAddress((HMODULE)library, funcName); }, 
                          &dispatchTable);
        if(false == dispatchTableInitialized){
            return XE_RESULT_ERROR_UNINITIALIZED;
        }
    }
    return dispatchTable.xeDriverInit(flags);
}

__xedllport xe_result_t __xecall xeCommandListEncodeExecutionBarrier(
        xe_command_list_handle_t hCommandList
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeExecutionBarrier(hCommandList);
}
__xedllport xe_result_t __xecall xeDeviceRegisterCLMemory(
        xe_device_handle_t hDevice,
        cl_context context,
        cl_mem mem,
        void** ptr
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceRegisterCLMemory(hDevice, context, mem, ptr);
}
__xedllport xe_result_t __xecall xeDeviceRegisterCLProgram(
        xe_device_handle_t hDevice,
        cl_context context,
        cl_program program,
        xe_module_handle_t* phModule
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceRegisterCLProgram(hDevice, context, program, phModule);
}
__xedllport xe_result_t __xecall xeDeviceRegisterCLCommandQueue(
        xe_device_handle_t hDevice,
        cl_context context,
        cl_command_queue command_queue,
        xe_command_queue_handle_t* phCommandQueue
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceRegisterCLCommandQueue(hDevice, context, command_queue, phCommandQueue);
}
__xedllport xe_result_t __xecall xeDeviceCreateCommandGraph(
        xe_device_handle_t hDevice,
        const xe_command_graph_desc_t* desc,
        xe_command_graph_handle_t* phCommandGraph
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceCreateCommandGraph(hDevice, desc, phCommandGraph);
}
__xedllport xe_result_t __xecall xeCommandGraphDestroy(
        xe_command_graph_handle_t hCommandGraph
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandGraphDestroy(hCommandGraph);
}
__xedllport xe_result_t __xecall xeCommandGraphClose(
        xe_command_graph_handle_t hCommandGraph
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandGraphClose(hCommandGraph);
}
__xedllport xe_result_t __xecall xeCommandGraphReset(
        xe_command_graph_handle_t hCommandGraph
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandGraphReset(hCommandGraph);
}
__xedllport xe_result_t __xecall xeDeviceCreateCommandList(
        xe_device_handle_t hDevice,
        const xe_command_list_desc_t* desc,
        xe_command_list_handle_t* phCommandList
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceCreateCommandList(hDevice, desc, phCommandList);
}
__xedllport xe_result_t __xecall xeDeviceCopyCommandList(
        xe_device_handle_t hDevice,
        xe_command_list_handle_t hCommandList,
        xe_command_list_handle_t* phCommandList
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceCopyCommandList(hDevice, hCommandList, phCommandList);
}
__xedllport xe_result_t __xecall xeCommandListDestroy(
        xe_command_list_handle_t hCommandList
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListDestroy(hCommandList);
}
__xedllport xe_result_t __xecall xeCommandListClose(
        xe_command_list_handle_t hCommandList
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListClose(hCommandList);
}
__xedllport xe_result_t __xecall xeCommandListReset(
        xe_command_list_handle_t hCommandList
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListReset(hCommandList);
}
__xedllport xe_result_t __xecall xeCommandListSetParameter(
        xe_command_list_handle_t hCommandList,
        xe_command_list_parameter_t parameter,
        uint32_t value
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListSetParameter(hCommandList, parameter, value);
}
__xedllport xe_result_t __xecall xeCommandListGetParameter(
        xe_command_list_handle_t hCommandList,
        xe_command_list_parameter_t parameter,
        uint32_t* value
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListGetParameter(hCommandList, parameter, value);
}
__xedllport xe_result_t __xecall xeCommandListResetParameters(
        xe_command_list_handle_t hCommandList
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListResetParameters(hCommandList);
}
__xedllport xe_result_t __xecall xeCommandListEncodeCommandLists(
        xe_command_list_handle_t hCommandList,
        uint32_t numCommandLists,
        xe_command_list_handle_t* phCommandLists
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeCommandLists(hCommandList, numCommandLists, phCommandLists);
}
__xedllport xe_result_t __xecall xeCommandListEncodeCommands(
        xe_command_list_handle_t hCommandList,
        xe_command_format_t format,
        size_t size,
        void* pBlob
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeCommands(hCommandList, format, size, pBlob);
}
__xedllport xe_result_t __xecall xeDeviceCreateCommandQueue(
        xe_device_handle_t hDevice,
        const xe_command_queue_desc_t* desc,
        xe_command_queue_handle_t* phCommandQueue
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceCreateCommandQueue(hDevice, desc, phCommandQueue);
}
__xedllport xe_result_t __xecall xeCommandQueueDestroy(
        xe_command_queue_handle_t hCommandQueue
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandQueueDestroy(hCommandQueue);
}
__xedllport xe_result_t __xecall xeCommandQueueEnqueueCommandLists(
        xe_command_queue_handle_t hCommandQueue,
        uint32_t numCommandLists,
        xe_command_list_handle_t* phCommandLists,
        xe_fence_handle_t hFence
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandQueueEnqueueCommandLists(hCommandQueue, numCommandLists, phCommandLists, hFence);
}
__xedllport xe_result_t __xecall xeCommandQueueSynchronize(
        xe_command_queue_handle_t hCommandQueue,
        xe_synchronization_mode_t mode,
        uint32_t delay,
        uint32_t interval,
        uint32_t timeout
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandQueueSynchronize(hCommandQueue, mode, delay, interval, timeout);
}
__xedllport xe_result_t __xecall xeCommandListEncodeMemoryCopy(
        xe_command_list_handle_t hCommandList,
        void* dstptr,
        const void* srcptr,
        size_t size
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeMemoryCopy(hCommandList, dstptr, srcptr, size);
}
__xedllport xe_result_t __xecall xeCommandListEncodeImageCopy(
        xe_command_list_handle_t hCommandList,
        xe_image_handle_t hDstImage,
        xe_image_handle_t hSrcImage
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeImageCopy(hCommandList, hDstImage, hSrcImage);
}
__xedllport xe_result_t __xecall xeCommandListEncodeImageCopyRegion(
        xe_command_list_handle_t hCommandList,
        xe_image_handle_t hDstImage,
        xe_image_region_t* pDstRegion,
        xe_image_handle_t hSrcImage,
        xe_image_region_t* pSrcRegion
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeImageCopyRegion(hCommandList, hDstImage, pDstRegion, hSrcImage, pSrcRegion);
}
__xedllport xe_result_t __xecall xeCommandListEncodeImageCopyToMemory(
        xe_command_list_handle_t hCommandList,
        void* dstptr,
        xe_image_handle_t hSrcImage,
        xe_image_region_t* pSrcRegion
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeImageCopyToMemory(hCommandList, dstptr, hSrcImage, pSrcRegion);
}
__xedllport xe_result_t __xecall xeCommandListEncodeImageCopyFromMemory(
        xe_command_list_handle_t hCommandList,
        xe_image_handle_t hDstImage,
        xe_image_region_t* pDstRegion,
        void* srcptr
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeImageCopyFromMemory(hCommandList, hDstImage, pDstRegion, srcptr);
}
__xedllport xe_result_t __xecall xeCommandListEncodeMemoryPrefetch(
        xe_command_list_handle_t hCommandList,
        const void* ptr,
        size_t count
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeMemoryPrefetch(hCommandList, ptr, count);
}
__xedllport xe_result_t __xecall xeCommandListEncodeMemAdvise(
        xe_command_list_handle_t hCommandList,
        xe_device_handle_t hDevice,
        const void* ptr,
        size_t size,
        xe_memory_advice_t advice
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeMemAdvise(hCommandList, hDevice, ptr, size, advice);
}
__xedllport xe_result_t __xecall xeDriverGetDeviceCount(
        uint32_t* count
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDriverGetDeviceCount(count);
}
__xedllport xe_result_t __xecall xeDriverGetDeviceUniqueIds(
        uint32_t count,
        uint32_t* pUniqueIds
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDriverGetDeviceUniqueIds(count, pUniqueIds);
}
__xedllport xe_result_t __xecall xeDriverGetDevice(
        uint32_t uniqueId,
        xe_device_handle_t* phDevice
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDriverGetDevice(uniqueId, phDevice);
}
__xedllport xe_result_t __xecall xeDeviceGetSubDevice(
        xe_device_handle_t hDevice,
        uint32_t ordinal,
        xe_device_handle_t* phSubDevice
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceGetSubDevice(hDevice, ordinal, phSubDevice);
}
__xedllport xe_result_t __xecall xeDeviceGetApiVersion(
        xe_device_handle_t hDevice,
        xe_api_version_t* version
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceGetApiVersion(hDevice, version);
}
__xedllport xe_result_t __xecall xeDeviceGetProperties(
        xe_device_handle_t hDevice,
        xe_device_properties_t* pDeviceProperties
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceGetProperties(hDevice, pDeviceProperties);
}
__xedllport xe_result_t __xecall xeDeviceGetComputeProperties(
        xe_device_handle_t hDevice,
        xe_device_compute_properties_t* pComputeProperties
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceGetComputeProperties(hDevice, pComputeProperties);
}
__xedllport xe_result_t __xecall xeDeviceGetMemoryProperties(
        xe_device_handle_t hDevice,
        xe_device_memory_properties_t* pMemProperties
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceGetMemoryProperties(hDevice, pMemProperties);
}
__xedllport xe_result_t __xecall xeDeviceGetLinkProperties(
        uint32_t srcOrdinal,
        uint32_t dstOrdinal,
        xe_device_link_properties_t* pLinkProperties
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceGetLinkProperties(srcOrdinal, dstOrdinal, pLinkProperties);
}
__xedllport xe_result_t __xecall xeDeviceCanAccessPeer(
        xe_device_handle_t hDevice,
        xe_device_handle_t hPeerDevice,
        bool* value
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceCanAccessPeer(hDevice, hPeerDevice, value);
}
__xedllport xe_result_t __xecall xeDeviceSetIntermediateCacheConfig(
        xe_device_handle_t hDevice,
        xe_cache_config_t CacheConfig
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceSetIntermediateCacheConfig(hDevice, CacheConfig);
}
__xedllport xe_result_t __xecall xeDeviceSetLastLevelCacheConfig(
        xe_device_handle_t hDevice,
        xe_cache_config_t CacheConfig
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceSetLastLevelCacheConfig(hDevice, CacheConfig);
}
__xedllport xe_result_t __xecall xeDriverGetVersion(
        uint32_t* version
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDriverGetVersion(version);
}
__xedllport xe_result_t __xecall xeDeviceCreateEvent(
        xe_device_handle_t hDevice,
        const xe_event_desc_t* desc,
        xe_event_handle_t* phEvent
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceCreateEvent(hDevice, desc, phEvent);
}
__xedllport xe_result_t __xecall xeDevicePlaceEvent(
        xe_device_handle_t hDevice,
        const xe_event_desc_t* desc,
        void* ptr,
        xe_event_handle_t* phEvent
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDevicePlaceEvent(hDevice, desc, ptr, phEvent);
}
__xedllport xe_result_t __xecall xeEventDestroy(
        xe_event_handle_t hEvent
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventDestroy(hEvent);
}
__xedllport xe_result_t __xecall xeCommandListEncodeSignalEvent(
        xe_command_list_handle_t hCommandList,
        xe_event_handle_t hEvent
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeSignalEvent(hCommandList, hEvent);
}
__xedllport xe_result_t __xecall xeCommandListEncodeWaitOnEvent(
        xe_command_list_handle_t hCommandList,
        xe_event_handle_t hEvent
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeWaitOnEvent(hCommandList, hEvent);
}
__xedllport xe_result_t __xecall xeCommandListEncodeSignalMultipleEvents(
        xe_command_list_handle_t hCommandList,
        uint32_t numEvents,
        xe_event_handle_t* phEvents
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeSignalMultipleEvents(hCommandList, numEvents, phEvents);
}
__xedllport xe_result_t __xecall xeCommandListEncodeWaitOnMultipleEvents(
        xe_command_list_handle_t hCommandList,
        uint32_t numEvents,
        xe_event_handle_t* phEvents
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeWaitOnMultipleEvents(hCommandList, numEvents, phEvents);
}
__xedllport xe_result_t __xecall xeHostSignalEvent(
        xe_event_handle_t hEvent
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeHostSignalEvent(hEvent);
}
__xedllport xe_result_t __xecall xeHostWaitOnEvent(
        xe_event_handle_t hEvent,
        xe_synchronization_mode_t mode,
        uint32_t delay,
        uint32_t interval,
        uint32_t timeout
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeHostWaitOnEvent(hEvent, mode, delay, interval, timeout);
}
__xedllport xe_result_t __xecall xeHostSignalMultipleEvents(
        uint32_t numEvents,
        xe_event_handle_t* phEvents
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeHostSignalMultipleEvents(numEvents, phEvents);
}
__xedllport xe_result_t __xecall xeHostWaitOnMultipleEvents(
        uint32_t numEvents,
        xe_event_handle_t* phEvents,
        xe_synchronization_mode_t mode,
        uint32_t delay,
        uint32_t interval,
        uint32_t timeout
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeHostWaitOnMultipleEvents(numEvents, phEvents, mode, delay, interval, timeout);
}
__xedllport xe_result_t __xecall xeEventQueryStatus(
        xe_event_handle_t hEvent
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventQueryStatus(hEvent);
}
__xedllport xe_result_t __xecall xeEventQueryElapsedTime(
        xe_event_handle_t hEventStart,
        xe_event_handle_t hEventEnd,
        double_t* pTime
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventQueryElapsedTime(hEventStart, hEventEnd, pTime);
}
__xedllport xe_result_t __xecall xeEventQueryMetricsData(
        xe_event_handle_t hEventStart,
        xe_event_handle_t hEventEnd,
        size_t reportSize,
        uint32_t* pReportData
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventQueryMetricsData(hEventStart, hEventEnd, reportSize, pReportData);
}
__xedllport xe_result_t __xecall xeCommandListEncodeEventReset(
        xe_command_list_handle_t hCommandList,
        xe_event_handle_t hEvent
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeEventReset(hCommandList, hEvent);
}
__xedllport xe_result_t __xecall xeEventReset(
        xe_event_handle_t hEvent
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventReset(hEvent);
}
__xedllport xe_result_t __xecall xeCommandQueueCreateFence(
        xe_command_queue_handle_t hCommandQueue,
        const xe_fence_desc_t* desc,
        xe_fence_handle_t* phFence
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandQueueCreateFence(hCommandQueue, desc, phFence);
}
__xedllport xe_result_t __xecall xeFenceDestroy(
        xe_fence_handle_t hFence
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFenceDestroy(hFence);
}
__xedllport xe_result_t __xecall xeHostWaitOnFence(
        xe_fence_handle_t hFence,
        xe_synchronization_mode_t mode,
        uint32_t delay,
        uint32_t interval,
        uint32_t timeout
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeHostWaitOnFence(hFence, mode, delay, interval, timeout);
}
__xedllport xe_result_t __xecall xeHostWaitOnMultipleFences(
        uint32_t numFences,
        xe_fence_handle_t* phFences,
        xe_synchronization_mode_t mode,
        uint32_t delay,
        uint32_t interval,
        uint32_t timeout
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeHostWaitOnMultipleFences(numFences, phFences, mode, delay, interval, timeout);
}
__xedllport xe_result_t __xecall xeFenceQueryStatus(
        xe_fence_handle_t hFence
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFenceQueryStatus(hFence);
}
__xedllport xe_result_t __xecall xeFenceQueryElapsedTime(
        xe_fence_handle_t hFenceStart,
        xe_fence_handle_t hFenceEnd,
        double_t* pTime
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFenceQueryElapsedTime(hFenceStart, hFenceEnd, pTime);
}
__xedllport xe_result_t __xecall xeFenceReset(
        xe_fence_handle_t hFence
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFenceReset(hFence);
}
__xedllport xe_result_t __xecall xeDeviceCreateImage(
        xe_device_handle_t hDevice,
        const xe_image_desc_t* desc,
        xe_image_handle_t* phImage
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceCreateImage(hDevice, desc, phImage);
}
__xedllport xe_result_t __xecall xeImageDestroy(
        xe_image_handle_t hImage
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeImageDestroy(hImage);
}
__xedllport xe_result_t __xecall xeCreateMemAllocator(
        xe_mem_allocator_handle_t* phMemAllocHandle
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCreateMemAllocator(phMemAllocHandle);
}
__xedllport xe_result_t __xecall xeMemAllocatorDestroy(
        xe_mem_allocator_handle_t hMemAllocHandle
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeMemAllocatorDestroy(hMemAllocHandle);
}
__xedllport xe_result_t __xecall xeSharedMemAlloc(
        xe_mem_allocator_handle_t hMemAllocHandle,
        xe_device_handle_t hDevice,
        xe_device_mem_alloc_flag_t device_flags,
        xe_host_mem_alloc_flag_t host_flags,
        size_t size,
        size_t alignment,
        void** ptr
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeSharedMemAlloc(hMemAllocHandle, hDevice, device_flags, host_flags, size, alignment, ptr);
}
__xedllport xe_result_t __xecall xeMemAlloc(
        xe_mem_allocator_handle_t hMemAllocHandle,
        xe_device_handle_t hDevice,
        xe_device_mem_alloc_flag_t flags,
        size_t size,
        size_t alignment,
        void** ptr
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeMemAlloc(hMemAllocHandle, hDevice, flags, size, alignment, ptr);
}
__xedllport xe_result_t __xecall xeHostMemAlloc(
        xe_mem_allocator_handle_t hMemAllocHandle,
        xe_host_mem_alloc_flag_t flags,
        size_t size,
        size_t alignment,
        void** ptr
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeHostMemAlloc(hMemAllocHandle, flags, size, alignment, ptr);
}
__xedllport xe_result_t __xecall xeMemFree(
        xe_mem_allocator_handle_t hMemAllocHandle,
        const void* ptr
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeMemFree(hMemAllocHandle, ptr);
}
__xedllport xe_result_t __xecall xeMemGetProperty(
        xe_mem_allocator_handle_t hMemAllocHandle,
        const void* ptr,
        xe_memory_property_t property,
        void* pValue
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeMemGetProperty(hMemAllocHandle, ptr, property, pValue);
}
__xedllport xe_result_t __xecall xeMemGetAddressRange(
        xe_mem_allocator_handle_t hMemAllocHandle,
        const void* ptr,
        void** pBase,
        size_t* pSize
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeMemGetAddressRange(hMemAllocHandle, ptr, pBase, pSize);
}
__xedllport xe_result_t __xecall xeIpcGetMemHandle(
        xe_mem_allocator_handle_t hMemAllocHandle,
        const void* ptr,
        xe_ipc_mem_handle_t* pIpcHandle
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeIpcGetMemHandle(hMemAllocHandle, ptr, pIpcHandle);
}
__xedllport xe_result_t __xecall xeIpcOpenMemHandle(
        xe_mem_allocator_handle_t hMemAllocHandle,
        xe_device_handle_t hDevice,
        xe_ipc_mem_handle_t handle,
        xe_ipc_memory_flag_t flags,
        void** ptr
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeIpcOpenMemHandle(hMemAllocHandle, hDevice, handle, flags, ptr);
}
__xedllport xe_result_t __xecall xeIpcCloseMemHandle(
        xe_mem_allocator_handle_t hMemAllocHandle,
        const void* ptr
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeIpcCloseMemHandle(hMemAllocHandle, ptr);
}
__xedllport xe_result_t __xecall xeDeviceCreateModule(
        xe_device_handle_t hDevice,
        const xe_module_desc_t* desc,
        xe_module_handle_t* phModule,
        xe_module_build_log_handle_t* phBuildLog
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceCreateModule(hDevice, desc, phModule, phBuildLog);
}
__xedllport xe_result_t __xecall xeModuleDestroy(
        xe_module_handle_t hModule
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeModuleDestroy(hModule);
}
__xedllport xe_result_t __xecall xeModuleBuildLogDestroy(
        xe_module_build_log_handle_t hBuildLog
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeModuleBuildLogDestroy(hBuildLog);
}
__xedllport xe_result_t __xecall xeModuleBuildLogGetString(
        xe_module_build_log_handle_t hBuildLog,
        uint32_t* pSize,
        char** pBuildLog
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeModuleBuildLogGetString(hBuildLog, pSize, pBuildLog);
}
__xedllport xe_result_t __xecall xeModuleGetNativeBinary(
        xe_module_handle_t hModule,
        uint32_t* pSize,
        char** pModuleNativeBinary
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeModuleGetNativeBinary(hModule, pSize, pModuleNativeBinary);
}
__xedllport xe_result_t __xecall xeModuleCreateFunction(
        xe_module_handle_t hModule,
        const xe_function_desc_t* desc,
        xe_function_handle_t* phFunction
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeModuleCreateFunction(hModule, desc, phFunction);
}
__xedllport xe_result_t __xecall xeFunctionDestroy(
        xe_function_handle_t hFunction
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFunctionDestroy(hFunction);
}
__xedllport xe_result_t __xecall xeFunctionSetGroupSize(
    xe_function_handle_t hFunction,
    uint32_t groupSizeX,
    uint32_t groupSizeY,
    uint32_t groupSizeZ
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFunctionSetGroupSize(hFunction, groupSizeX, groupSizeY, groupSizeZ);
}
__xedllport xe_result_t __xecall xeFunctionCreateFunctionArgs(
        xe_function_handle_t hFunction,
        xe_function_args_handle_t* phFunctionArgs
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFunctionCreateFunctionArgs(hFunction, phFunctionArgs);
}
__xedllport xe_result_t __xecall xeFunctionArgsDestroy(
        xe_function_args_handle_t hFunctionArgs
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFunctionArgsDestroy(hFunctionArgs);
}
__xedllport xe_result_t __xecall xeFunctionArgsSetValue(
        xe_function_args_handle_t hFunctionArgs,
        uint32_t argIndex,
        size_t argSize,
        const void* pArgValue
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFunctionArgsSetValue(hFunctionArgs, argIndex, argSize, pArgValue);
}
__xedllport xe_result_t __xecall xeFunctionArgsSetAttribute(
        xe_function_args_handle_t hFunctionArgs,
        xe_function_argument_attribute_t attr,
        uint32_t value
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFunctionArgsSetAttribute(hFunctionArgs, attr, value);
}
__xedllport xe_result_t __xecall xeFunctionQueryAttribute(
        xe_function_handle_t hFunction,
        xe_function_attribute_t attr,
        uint32_t* pValue
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFunctionQueryAttribute(hFunction, attr, pValue);
}
__xedllport xe_result_t __xecall xeCommandListEncodeDispatchFunction(
        xe_command_list_handle_t hCommandList,
        xe_function_handle_t hFunction,
        xe_function_args_handle_t hFunctionArgs,
        const xe_dispatch_function_arguments_t* pDispatchFuncArgs,
        xe_event_handle_t hEvent
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeDispatchFunction(hCommandList, hFunction, hFunctionArgs, pDispatchFuncArgs, hEvent);
}
__xedllport xe_result_t __xecall xeCommandGraphEncodeDispatchFunction(
        xe_command_graph_handle_t hCommandGraph,
        xe_function_handle_t hFunction,
        xe_function_args_handle_t hFunctionArgs,
        const xe_dispatch_function_arguments_t* pDispatchFuncArgs,
        xe_event_handle_t hEvent
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandGraphEncodeDispatchFunction(hCommandGraph, hFunction, hFunctionArgs, pDispatchFuncArgs, hEvent);
}
__xedllport xe_result_t __xecall xeCommandListEncodeDispatchFunctionIndirect(
        xe_command_list_handle_t hCommandList,
        xe_function_handle_t hFunction,
        xe_function_args_handle_t hFunctionArgs,
        const xe_dispatch_function_indirect_arguments_t* pDispatchArgumentsBuffer,
        xe_event_handle_t hEvent
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeDispatchFunctionIndirect(hCommandList, hFunction, hFunctionArgs, pDispatchArgumentsBuffer, hEvent);
}
__xedllport xe_result_t __xecall xeCommandGraphEncodeDispatchFunctionIndirect(
        xe_command_graph_handle_t hCommandGraph,
        xe_function_handle_t hFunction,
        xe_function_args_handle_t hFunctionArgs,
        const xe_dispatch_function_indirect_arguments_t* pDispatchArgumentsBuffer,
        xe_event_handle_t hEvent
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandGraphEncodeDispatchFunctionIndirect(hCommandGraph, hFunction, hFunctionArgs, pDispatchArgumentsBuffer, hEvent);
}
__xedllport xe_result_t __xecall xeFunctionSuggestGroupSize(
        xe_function_handle_t hFunction,
        uint32_t globalSizeX,
        uint32_t globalSizeY,
        uint32_t globalSizeZ,
        uint32_t* groupSizeX,
        uint32_t* groupSizeY,
        uint32_t* groupSizeZ
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFunctionSuggestGroupSize(hFunction, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ);
}
__xedllport xe_result_t __xecall xeCommandListEncodeDispatchHostFunction(
        xe_command_list_handle_t hCommandList,
        xe_host_pfn_t pfnHostFunc,
        void* pUserData
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeDispatchHostFunction(hCommandList, pfnHostFunc, pUserData);
}
__xedllport xe_result_t __xecall xeCommandGraphEncodeDispatchHostFunction(
        xe_command_graph_handle_t hCommandGraph,
        xe_host_pfn_t pfnHostFunc,
        void* pUserData
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandGraphEncodeDispatchHostFunction(hCommandGraph, pfnHostFunc, pUserData);
}
__xedllport xe_result_t __xecall xeDeviceMakeMemoryResident(
        xe_device_handle_t hDevice,
        void* ptr,
        size_t size
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceMakeMemoryResident(hDevice, ptr, size);
}
__xedllport xe_result_t __xecall xeDeviceEvictMemory(
        xe_device_handle_t hDevice,
        void* ptr,
        size_t size
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceEvictMemory(hDevice, ptr, size);
}
__xedllport xe_result_t __xecall xeDeviceMakeImageResident(
        xe_device_handle_t hDevice,
        xe_image_handle_t hImage
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceMakeImageResident(hDevice, hImage);
}
__xedllport xe_result_t __xecall xeDeviceEvictImage(
        xe_device_handle_t hDevice,
        xe_image_handle_t hImage
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceEvictImage(hDevice, hImage);
}
__xedllport xe_result_t __xecall xeDeviceCreateSemaphore(
        xe_device_handle_t hDevice,
        const xe_semaphore_desc_t* desc,
        xe_semaphore_handle_t* phSemaphore
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceCreateSemaphore(hDevice, desc, phSemaphore);
}
__xedllport xe_result_t __xecall xeSemaphoreDestroy(
        xe_semaphore_handle_t hSemaphore
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeSemaphoreDestroy(hSemaphore);
}
__xedllport xe_result_t __xecall xeCommandListEncodeSemaphoreSignal(
        xe_command_list_handle_t hCommandList,
        xe_semaphore_handle_t hSemaphore,
        xe_semaphore_value_t value
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeSemaphoreSignal(hCommandList, hSemaphore, value);
}
__xedllport xe_result_t __xecall xeCommandListEncodeSemaphoreWait(
        xe_command_list_handle_t hCommandList,
        xe_semaphore_handle_t hSemaphore,
        xe_semaphore_wait_operation_t operation,
        xe_semaphore_value_t value
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeSemaphoreWait(hCommandList, hSemaphore, operation, value);
}
__xedllport xe_result_t __xecall xeSemaphoreQueryValue(
        xe_semaphore_handle_t hSemaphore
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeSemaphoreQueryValue(hSemaphore);
}
__xedllport xe_result_t __xecall xeSemaphoreReset(
        xe_semaphore_handle_t hSemaphore
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeSemaphoreReset(hSemaphore);
}

#if defined(__cplusplus)
};
#endif
