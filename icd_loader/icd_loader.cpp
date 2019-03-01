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

#if defined(__linux__)
#  include <dlfcn.h>
#  define ICD_LOAD_DRIVER_LIBRARY() dlopen("liblevel_zero.so", RTLD_LAZY|RTLD_LOCAL)
#  define ICD_LOAD_FUNCTION_PTR(LIB, FUNC_NAME) dlsym(LIB, FUNC_NAME)
#elif defined(_WIN32)
#  include <Windows.h>
#  define ICD_LOAD_DRIVER_LIBRARY() LoadLibraryA("level_zero.dll")
#  define ICD_LOAD_FUNCTION_PTR(LIB, FUNC_NAME) GetProcAddress((HMODULE)LIB, FUNC_NAME)
#else
#  error "Unsupported OS"
#endif

xe_dispatch_table_t dispatchTable = {};
bool dispatchTableInitialized = false;

#if defined(__cplusplus)
extern "C" {
#endif

xe_result_t __xecall xeDriverInit(xe_init_flag_t flags){
    static std::mutex crit;
    {
        std::lock_guard<std::mutex> lockGuard{crit};
        
        if(dispatchTableInitialized){
            return dispatchTable.xeDriverInit(flags);
        }
        
        auto driverLibrary = ICD_LOAD_DRIVER_LIBRARY(); // persistent handle
        dispatchTableInitialized = 
                load_xe(driverLibrary, 
                          [](void *library, const char *funcName)->void* { return ICD_LOAD_FUNCTION_PTR(library, funcName); }, 
                          &dispatchTable);
        if(false == dispatchTableInitialized){
            return XE_RESULT_ERROR_UNINITIALIZED;
        }
    }
    return dispatchTable.xeDriverInit(flags);
}

xe_result_t __xecall xeCommandListEncodeExecutionBarrier(
        xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeExecutionBarrier(hCommandList);
}
#if XE_ENABLE_OCL_INTEROP
xe_result_t __xecall xeDeviceRegisterCLMemory(
        xe_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context context,                             ///< [in] the OpenCL context that created the memory
        cl_mem mem,                                     ///< [in] the OpenCL memory to register
        void** ptr                                      ///< [out] pointer to device allocation
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceRegisterCLMemory(hDevice, context, mem, ptr);
}
#endif // XE_ENABLE_OCL_INTEROP
#if XE_ENABLE_OCL_INTEROP
xe_result_t __xecall xeDeviceRegisterCLProgram(
        xe_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context context,                             ///< [in] the OpenCL context that created the program
        cl_program program,                             ///< [in] the OpenCL program to register
        xe_module_handle_t* phModule                    ///< [out] pointer to handle of module object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceRegisterCLProgram(hDevice, context, program, phModule);
}
#endif // XE_ENABLE_OCL_INTEROP
#if XE_ENABLE_OCL_INTEROP
xe_result_t __xecall xeDeviceRegisterCLCommandQueue(
        xe_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context context,                             ///< [in] the OpenCL context that created the command queue
        cl_command_queue command_queue,                 ///< [in] the OpenCL command queue to register
        xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceRegisterCLCommandQueue(hDevice, context, command_queue, phCommandQueue);
}
#endif // XE_ENABLE_OCL_INTEROP
xe_result_t __xecall xeDeviceCreateCommandGraph(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        const xe_command_graph_desc_t* desc,            ///< [in] pointer to command graph descriptor
        xe_command_graph_handle_t* phCommandGraph       ///< [out] pointer to handle of command graph object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceCreateCommandGraph(hDevice, desc, phCommandGraph);
}
xe_result_t __xecall xeCommandGraphDestroy(
        xe_command_graph_handle_t hCommandGraph         ///< [in] handle of command graph object to destroy
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandGraphDestroy(hCommandGraph);
}
xe_result_t __xecall xeCommandGraphClose(
        xe_command_graph_handle_t hCommandGraph         ///< [in] handle of command graph object to close
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandGraphClose(hCommandGraph);
}
xe_result_t __xecall xeCommandGraphReset(
        xe_command_graph_handle_t hCommandGraph         ///< [in] handle of command graph object to reset
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandGraphReset(hCommandGraph);
}
xe_result_t __xecall xeDeviceCreateCommandList(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        const xe_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
        xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceCreateCommandList(hDevice, desc, phCommandList);
}
xe_result_t __xecall xeDeviceCopyCommandList(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        xe_command_list_handle_t hCommandList,          ///< [in] handle to command list to copy
        xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceCopyCommandList(hDevice, hCommandList, phCommandList);
}
xe_result_t __xecall xeCommandListDestroy(
        xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to destroy
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListDestroy(hCommandList);
}
xe_result_t __xecall xeCommandListClose(
        xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListClose(hCommandList);
}
xe_result_t __xecall xeCommandListReset(
        xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListReset(hCommandList);
}
xe_result_t __xecall xeCommandListSetParameter(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_command_list_parameter_t parameter,          ///< [in] parameter to change
        uint32_t value                                  ///< [in] value of attribute
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListSetParameter(hCommandList, parameter, value);
}
xe_result_t __xecall xeCommandListGetParameter(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_command_list_parameter_t parameter,          ///< [in] parameter to retrieve
        uint32_t* value                                 ///< [out] value of attribute
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListGetParameter(hCommandList, parameter, value);
}
xe_result_t __xecall xeCommandListResetParameters(
        xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListResetParameters(hCommandList);
}
xe_result_t __xecall xeCommandListEncodeCommandLists(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numCommandLists,                       ///< [in] number of command lists to encode
        xe_command_list_handle_t* phCommandLists        ///< [in] list of handles of the command lists to encode for execution
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeCommandLists(hCommandList, numCommandLists, phCommandLists);
}
xe_result_t __xecall xeCommandListEncodeCommands(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_command_format_t format,                     ///< [in] format of the command blob
        size_t size,                                    ///< [in] size (in bytes) of the command blob
        void* pBlob                                     ///< [in] pointer to blob of commands to encode into the command list
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeCommands(hCommandList, format, size, pBlob);
}
xe_result_t __xecall xeDeviceCreateCommandQueue(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
        xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceCreateCommandQueue(hDevice, desc, phCommandQueue);
}
xe_result_t __xecall xeCommandQueueDestroy(
        xe_command_queue_handle_t hCommandQueue         ///< [in] handle of command queue object to destroy
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandQueueDestroy(hCommandQueue);
}
xe_result_t __xecall xeCommandQueueEnqueueCommandLists(
        xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t numCommandLists,                       ///< [in] number of command lists to enqueue
        xe_command_list_handle_t* phCommandLists,       ///< [in] list of handles of the command lists to enqueue for execution
        xe_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandQueueEnqueueCommandLists(hCommandQueue, numCommandLists, phCommandLists, hFence);
}
xe_result_t __xecall xeCommandQueueSynchronize(
        xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        xe_synchronization_mode_t mode,                 ///< [in] synchronization mode
        uint32_t delay,                                 ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then time (in
                                                        ///< microseconds) to poll before putting Host thread to sleep; otherwise,
                                                        ///< must be zero.
        uint32_t interval,                              ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then maximum time (in
                                                        ///< microseconds) to put Host thread to sleep between polling; otherwise,
                                                        ///< must be zero.
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to poll or sleep
                                                        ///< before returning; if zero, then only a single status check is made
                                                        ///< before immediately returning; if MAX_UINT32, then function will not
                                                        ///< return until complete.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandQueueSynchronize(hCommandQueue, mode, delay, interval, timeout);
}
xe_result_t __xecall xeCommandListEncodeMemoryCopy(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size                                     ///< [in] size in bytes to copy
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeMemoryCopy(hCommandList, dstptr, srcptr, size);
}
xe_result_t __xecall xeCommandListEncodeMemorySet(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* ptr,                                      ///< [in] pointer to memory to initialize
        int value,                                      ///< [in] value to initialize memory to
        size_t size                                     ///< [in] size in bytes to initailize
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeMemorySet(hCommandList, ptr, value, size);
}
xe_result_t __xecall xeCommandListEncodeImageCopy(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        xe_image_handle_t hSrcImage                     ///< [in] handle of source image to copy from
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeImageCopy(hCommandList, hDstImage, hSrcImage);
}
xe_result_t __xecall xeCommandListEncodeImageCopyRegion(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        xe_image_region_t* pDstRegion,                  ///< [in][optional] destination region descriptor
        xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        xe_image_region_t* pSrcRegion                   ///< [in][optional] source region descriptor
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeImageCopyRegion(hCommandList, hDstImage, pDstRegion, hSrcImage, pSrcRegion);
}
xe_result_t __xecall xeCommandListEncodeImageCopyToMemory(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        xe_image_region_t* pSrcRegion                   ///< [in][optional] source region descriptor
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeImageCopyToMemory(hCommandList, dstptr, hSrcImage, pSrcRegion);
}
xe_result_t __xecall xeCommandListEncodeImageCopyFromMemory(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        xe_image_region_t* pDstRegion,                  ///< [in][optional] destination region descriptor
        void* srcptr                                    ///< [in] pointer to source memory to copy from
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeImageCopyFromMemory(hCommandList, hDstImage, pDstRegion, srcptr);
}
xe_result_t __xecall xeCommandListEncodeMemoryPrefetch(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        const void* ptr,                                ///< [in] pointer to start of the memory region to prefetch
        size_t count                                    ///< [in] size in bytes of the memory region to prefetch
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeMemoryPrefetch(hCommandList, ptr, count);
}
xe_result_t __xecall xeCommandListEncodeMemAdvise(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        xe_memory_advice_t advice                       ///< [in] Memory advice for the memory range
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeMemAdvise(hCommandList, hDevice, ptr, size, advice);
}
xe_result_t __xecall xeDriverGetDeviceCount(
        uint32_t* count                                 ///< [out] number of devices available
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDriverGetDeviceCount(count);
}
xe_result_t __xecall xeDriverGetDeviceUniqueIds(
        uint32_t count,                                 ///< [in] size of device unique ids array. Typically, this will be
                                                        ///< ${x}DeviceGetCount.
        uint32_t* pUniqueIds                            ///< [out] pointer to an array of unique ids for devices. Caller must
                                                        ///< supply array.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDriverGetDeviceUniqueIds(count, pUniqueIds);
}
xe_result_t __xecall xeDriverGetDevice(
        uint32_t uniqueId,                              ///< [in] unique id of device to retrieve. Use ${x}DriverGetDeviceUniqueIds
                                                        ///< to obtain a unique Id.
        xe_device_handle_t* phDevice                    ///< [out] pointer to handle of device object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDriverGetDevice(uniqueId, phDevice);
}
xe_result_t __xecall xeDeviceGetSubDevice(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        uint32_t ordinal,                               ///< [in] ordinal of sub-device to retrieve
        xe_device_handle_t* phSubDevice                 ///< [out] pointer to handle of sub-device object.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceGetSubDevice(hDevice, ordinal, phSubDevice);
}
xe_result_t __xecall xeDeviceGetApiVersion(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        xe_api_version_t* version                       ///< [out] api version
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceGetApiVersion(hDevice, version);
}
xe_result_t __xecall xeDeviceGetProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        xe_device_properties_t* pDeviceProperties       ///< [out] query result for device properties
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceGetProperties(hDevice, pDeviceProperties);
}
xe_result_t __xecall xeDeviceGetComputeProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        xe_device_compute_properties_t* pComputeProperties  ///< [out] query result for compute properties
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceGetComputeProperties(hDevice, pComputeProperties);
}
xe_result_t __xecall xeDeviceGetMemoryProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        xe_device_memory_properties_t* pMemProperties   ///< [out] query result for compute properties
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceGetMemoryProperties(hDevice, pMemProperties);
}
xe_result_t __xecall xeDeviceGetLinkProperties(
        uint32_t srcOrdinal,                            ///< [in] source device ordinal
        uint32_t dstOrdinal,                            ///< [in] destination device ordinal
        xe_device_link_properties_t* pLinkProperties    ///< [out] link properties between source and destination devices
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceGetLinkProperties(srcOrdinal, dstOrdinal, pLinkProperties);
}
xe_result_t __xecall xeDeviceCanAccessPeer(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        bool* value                                     ///< [out] returned access capability
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceCanAccessPeer(hDevice, hPeerDevice, value);
}
xe_result_t __xecall xeDeviceSetIntermediateCacheConfig(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device 
        xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceSetIntermediateCacheConfig(hDevice, CacheConfig);
}
xe_result_t __xecall xeDeviceSetLastLevelCacheConfig(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device 
        xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceSetLastLevelCacheConfig(hDevice, CacheConfig);
}
xe_result_t __xecall xeDriverGetVersion(
        uint32_t* version                               ///< [out] driver version
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDriverGetVersion(version);
}
xe_result_t __xecall xeDeviceCreateEvent(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_event_desc_t* desc,                    ///< [in] pointer to event descriptor
        xe_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceCreateEvent(hDevice, desc, phEvent);
}
xe_result_t __xecall xeDevicePlaceEvent(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_event_desc_t* desc,                    ///< [in] pointer to event descriptor
        void* ptr,                                      ///< [in] pointer to the device pointer where the event should be placed
        xe_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDevicePlaceEvent(hDevice, desc, ptr, phEvent);
}
xe_result_t __xecall xeEventDestroy(
        xe_event_handle_t hEvent                        ///< [in] handle of event object to destroy
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventDestroy(hEvent);
}
xe_result_t __xecall xeCommandListEncodeSignalEvent(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeSignalEvent(hCommandList, hEvent);
}
xe_result_t __xecall xeCommandListEncodeWaitOnEvent(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeWaitOnEvent(hCommandList, hEvent);
}
xe_result_t __xecall xeCommandListEncodeSignalMultipleEvents(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numEvents,                             ///< [in] number of events pointed to by phEvents
        xe_event_handle_t* phEvents                     ///< [in] pointer to array of handles of the events
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeSignalMultipleEvents(hCommandList, numEvents, phEvents);
}
xe_result_t __xecall xeCommandListEncodeWaitOnMultipleEvents(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numEvents,                             ///< [in] number of events pointed to by phEvents
        xe_event_handle_t* phEvents                     ///< [in] pointer to array of handles of the events
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeWaitOnMultipleEvents(hCommandList, numEvents, phEvents);
}
xe_result_t __xecall xeHostSignalEvent(
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeHostSignalEvent(hEvent);
}
xe_result_t __xecall xeHostWaitOnEvent(
        xe_event_handle_t hEvent,                       ///< [in] handle of the event
        xe_synchronization_mode_t mode,                 ///< [in] synchronization mode
        uint32_t delay,                                 ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then time (in
                                                        ///< microseconds) to poll before putting Host thread to sleep; otherwise,
                                                        ///< must be zero.
        uint32_t interval,                              ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then maximum time (in
                                                        ///< microseconds) to put Host thread to sleep between polling; otherwise,
                                                        ///< must be zero.
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to poll or sleep
                                                        ///< before returning; if zero, then only a single status check is made
                                                        ///< before immediately returning; if MAX_UINT32, then function will not
                                                        ///< return until complete.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeHostWaitOnEvent(hEvent, mode, delay, interval, timeout);
}
xe_result_t __xecall xeHostSignalMultipleEvents(
        uint32_t numEvents,                             ///< [in] number of events pointed to by phEvents
        xe_event_handle_t* phEvents                     ///< [in] pointer to array of handles of the events
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeHostSignalMultipleEvents(numEvents, phEvents);
}
xe_result_t __xecall xeHostWaitOnMultipleEvents(
        uint32_t numEvents,                             ///< [in] number of events pointed to by phEvents
        xe_event_handle_t* phEvents,                    ///< [in] pointer to array of handles of the events
        xe_synchronization_mode_t mode,                 ///< [in] synchronization mode
        uint32_t delay,                                 ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then time (in
                                                        ///< microseconds) to poll before putting Host thread to sleep; otherwise,
                                                        ///< must be zero.
        uint32_t interval,                              ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then maximum time (in
                                                        ///< microseconds) to put Host thread to sleep between polling; otherwise,
                                                        ///< must be zero.
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to poll or sleep
                                                        ///< before returning; if zero, then only a single status check is made
                                                        ///< before immediately returning; if MAX_UINT32, then function will not
                                                        ///< return until complete.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeHostWaitOnMultipleEvents(numEvents, phEvents, mode, delay, interval, timeout);
}
xe_result_t __xecall xeEventQueryStatus(
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventQueryStatus(hEvent);
}
xe_result_t __xecall xeEventQueryElapsedTime(
        xe_event_handle_t hEventStart,                  ///< [in] handle of the start event
        xe_event_handle_t hEventEnd,                    ///< [in] handle of the end event
        double_t* pTime                                 ///< [out] time in milliseconds
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventQueryElapsedTime(hEventStart, hEventEnd, pTime);
}
xe_result_t __xecall xeEventQueryMetricsData(
        xe_event_handle_t hEventStart,                  ///< [in] handle of the start event
        xe_event_handle_t hEventEnd,                    ///< [in] handle of the end event
        size_t reportSize,                              ///< [in] size of the report data buffer in bytes
        uint32_t* pReportData                           ///< [out] report data buffer
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventQueryMetricsData(hEventStart, hEventEnd, reportSize, pReportData);
}
xe_result_t __xecall xeCommandListEncodeEventReset(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeEventReset(hCommandList, hEvent);
}
xe_result_t __xecall xeEventReset(
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventReset(hEvent);
}
xe_result_t __xecall xeCommandQueueCreateFence(
        xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
        const xe_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
        xe_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandQueueCreateFence(hCommandQueue, desc, phFence);
}
xe_result_t __xecall xeFenceDestroy(
        xe_fence_handle_t hFence                        ///< [in] handle of fence object to destroy
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFenceDestroy(hFence);
}
xe_result_t __xecall xeHostWaitOnFence(
        xe_fence_handle_t hFence,                       ///< [in] handle of the fence
        xe_synchronization_mode_t mode,                 ///< [in] synchronization mode
        uint32_t delay,                                 ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then time (in
                                                        ///< microseconds) to poll before putting Host thread to sleep; otherwise,
                                                        ///< must be zero.
        uint32_t interval,                              ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then maximum time (in
                                                        ///< microseconds) to put Host thread to sleep between polling; otherwise,
                                                        ///< must be zero.
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to poll or sleep
                                                        ///< before returning; if zero, then only a single status check is made
                                                        ///< before immediately returning; if MAX_UINT32, then function will not
                                                        ///< return until complete.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeHostWaitOnFence(hFence, mode, delay, interval, timeout);
}
xe_result_t __xecall xeHostWaitOnMultipleFences(
        uint32_t numFences,                             ///< [in] number of fences in hFences
        xe_fence_handle_t* phFences,                    ///< [in] pointer to array of handles of the fences
        xe_synchronization_mode_t mode,                 ///< [in] synchronization mode
        uint32_t delay,                                 ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then time (in
                                                        ///< microseconds) to poll before putting Host thread to sleep; otherwise,
                                                        ///< must be zero.
        uint32_t interval,                              ///< [in] if ::XE_SYNCHRONIZATION_MODE_SLEEP == mode, then maximum time (in
                                                        ///< microseconds) to put Host thread to sleep between polling; otherwise,
                                                        ///< must be zero.
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to poll or sleep
                                                        ///< before returning; if zero, then only a single status check is made
                                                        ///< before immediately returning; if MAX_UINT32, then function will not
                                                        ///< return until complete.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeHostWaitOnMultipleFences(numFences, phFences, mode, delay, interval, timeout);
}
xe_result_t __xecall xeFenceQueryStatus(
        xe_fence_handle_t hFence                        ///< [in] handle of the fence
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFenceQueryStatus(hFence);
}
xe_result_t __xecall xeFenceQueryElapsedTime(
        xe_fence_handle_t hFenceStart,                  ///< [in] handle of the fence
        xe_fence_handle_t hFenceEnd,                    ///< [in] handle of the fence
        double_t* pTime                                 ///< [out] time in milliseconds
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFenceQueryElapsedTime(hFenceStart, hFenceEnd, pTime);
}
xe_result_t __xecall xeFenceReset(
        xe_fence_handle_t hFence                        ///< [in] handle of the fence
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFenceReset(hFence);
}
xe_result_t __xecall xeDeviceCreateImage(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        xe_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceCreateImage(hDevice, desc, phImage);
}
xe_result_t __xecall xeImageDestroy(
        xe_image_handle_t hImage                        ///< [in] handle of image object to destroy
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeImageDestroy(hImage);
}
xe_result_t __xecall xeCreateMemAllocator(
        xe_mem_allocator_handle_t* phMemAllocHandle     ///< [out] Returned memory allocator handle
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCreateMemAllocator(phMemAllocHandle);
}
xe_result_t __xecall xeMemAllocatorDestroy(
        xe_mem_allocator_handle_t hMemAllocHandle       ///< [in] handle of memory allocator to destroy
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeMemAllocatorDestroy(hMemAllocHandle);
}
xe_result_t __xecall xeSharedMemAlloc(
        xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_device_mem_alloc_flag_t device_flags,        ///< [in] flags specifying additional device allocation controls
        xe_host_mem_alloc_flag_t host_flags,            ///< [in] flags specifying additional host allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** ptr                                      ///< [out] pointer to shared allocation
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeSharedMemAlloc(hMemAllocHandle, hDevice, device_flags, host_flags, size, alignment, ptr);
}
xe_result_t __xecall xeMemAlloc(
        xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_device_mem_alloc_flag_t flags,               ///< [in] flags specifying additional allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** ptr                                      ///< [out] pointer to device allocation
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeMemAlloc(hMemAllocHandle, hDevice, flags, size, alignment, ptr);
}
xe_result_t __xecall xeHostMemAlloc(
        xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
        xe_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** ptr                                      ///< [out] pointer to host allocation
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeHostMemAlloc(hMemAllocHandle, flags, size, alignment, ptr);
}
xe_result_t __xecall xeMemFree(
        xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
        const void* ptr                                 ///< [in] pointer to memory to free
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeMemFree(hMemAllocHandle, ptr);
}
xe_result_t __xecall xeMemGetProperty(
        xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
        const void* ptr,                                ///< [in] Pointer to query
        xe_memory_property_t property,                  ///< [in] Property of the allocation to query
        void* pValue                                    ///< [out] Value of the queried property
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeMemGetProperty(hMemAllocHandle, ptr, property, pValue);
}
xe_result_t __xecall xeMemGetAddressRange(
        xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
        const void* ptr,                                ///< [in] Pointer to query
        void** pBase,                                   ///< [out] Returned base address of the allocation (optional)
        size_t* pSize                                   ///< [out] Returned size of the allocation (optional)
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeMemGetAddressRange(hMemAllocHandle, ptr, pBase, pSize);
}
xe_result_t __xecall xeIpcGetMemHandle(
        xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
        const void* ptr,                                ///< [in] Pointer to the device memory allocation
        xe_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeIpcGetMemHandle(hMemAllocHandle, ptr, pIpcHandle);
}
xe_result_t __xecall xeIpcOpenMemHandle(
        xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
        xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
        xe_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
        xe_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
        void** ptr                                      ///< [out] pointer to device allocation in this process
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeIpcOpenMemHandle(hMemAllocHandle, hDevice, handle, flags, ptr);
}
xe_result_t __xecall xeIpcCloseMemHandle(
        xe_mem_allocator_handle_t hMemAllocHandle,      ///< [in] handle of memory allocator for this allocation
        const void* ptr                                 ///< [in] pointer to device allocation in this process
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeIpcCloseMemHandle(hMemAllocHandle, ptr);
}
xe_result_t __xecall xeDeviceCreateModule(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_module_desc_t* desc,                   ///< [in] pointer to module descriptor
        xe_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
        xe_module_build_log_handle_t* phBuildLog        ///< [out][optional] pointer to handle of module's build log.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceCreateModule(hDevice, desc, phModule, phBuildLog);
}
xe_result_t __xecall xeModuleDestroy(
        xe_module_handle_t hModule                      ///< [in] handle of the module
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeModuleDestroy(hModule);
}
xe_result_t __xecall xeModuleBuildLogDestroy(
        xe_module_build_log_handle_t hModuleBuildLog    ///< [in] handle of the module build log object.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeModuleBuildLogDestroy(hModuleBuildLog);
}
xe_result_t __xecall xeModuleBuildLogGetString(
        xe_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
        uint32_t* pSize,                                ///< [out] size of build log string.
        char** pBuildLog                                ///< [out] pointer to null-terminated string of the log.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeModuleBuildLogGetString(hModuleBuildLog, pSize, pBuildLog);
}
xe_result_t __xecall xeModuleGetNativeBinary(
        xe_module_handle_t hModule,                     ///< [in] handle of the device
        uint32_t* pSize,                                ///< [out] size of native binary.
        char** pModuleNativeBinary                      ///< [out] pointer to native binary
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeModuleGetNativeBinary(hModule, pSize, pModuleNativeBinary);
}
xe_result_t __xecall xeModuleCreateFunction(
        xe_module_handle_t hModule,                     ///< [in] handle of the module
        const xe_function_desc_t* desc,                 ///< [in] pointer to function descriptor
        xe_function_handle_t* phFunction                ///< [out] handle of the Function object
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeModuleCreateFunction(hModule, desc, phFunction);
}
xe_result_t __xecall xeFunctionDestroy(
        xe_function_handle_t hFunction                  ///< [in] handle of the function object
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFunctionDestroy(hFunction);
}
xe_result_t __xecall xeModuleGetFunctionPointer(
        xe_module_handle_t hModule,                     ///< [in] handle of the module
        const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
        void** pfnFunction                              ///< [out] pointer to function.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeModuleGetFunctionPointer(hModule, pFunctionName, pfnFunction);
}
xe_result_t __xecall xeFunctionSetGroupSize(
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this function.
        uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this function.
        uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this function.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFunctionSetGroupSize(hFunction, groupSizeX, groupSizeY, groupSizeZ);
}
xe_result_t __xecall xeFunctionSuggestGroupSize(
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        uint32_t globalSizeX,                           ///< [in] global width for X dimension.
        uint32_t globalSizeY,                           ///< [in] global width for Y dimension.
        uint32_t globalSizeZ,                           ///< [in] global width for Z dimension.
        uint32_t* groupSizeX,                           ///< [out] recommended size of group for X dimension.
        uint32_t* groupSizeY,                           ///< [out] recommended size of group for Y dimension.
        uint32_t* groupSizeZ                            ///< [out] recommended size of group for Z dimension.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFunctionSuggestGroupSize(hFunction, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ);
}
xe_result_t __xecall xeFunctionSetArgumentValue(
        xe_function_handle_t hFunction,                 ///< [in/out] handle of the function args object.
        uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
        size_t argSize,                                 ///< [in] size of argument type
        const void* pArgValue                           ///< [in] argument value represented as matching arg type
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFunctionSetArgumentValue(hFunction, argIndex, argSize, pArgValue);
}
xe_result_t __xecall xeFunctionSetAttribute(
        xe_function_handle_t hFunction,                 ///< [in/out] handle of the function.
        xe_function_set_attribute_t attr,               ///< [in] attribute to set
        uint32_t value                                  ///< [in] attribute value to set
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFunctionSetAttribute(hFunction, attr, value);
}
xe_result_t __xecall xeFunctionGetAttribute(
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        xe_function_get_attribute_t attr,               ///< [in] attribute to query
        uint32_t* pValue                                ///< [out] returned attribute value
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFunctionGetAttribute(hFunction, attr, pValue);
}
xe_result_t __xecall xeCommandListEncodeDispatchFunction(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        const xe_dispatch_function_arguments_t* pDispatchFuncArgs,  ///< [in] dispatch function arguments.
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeDispatchFunction(hCommandList, hFunction, pDispatchFuncArgs, hEvent);
}
xe_result_t __xecall xeCommandGraphEncodeDispatchFunction(
        xe_command_graph_handle_t hCommandGraph,        ///< [in] handle of the command graph
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        const xe_dispatch_function_arguments_t* pDispatchFuncArgs,  ///< [in] dispatch function arguments.
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandGraphEncodeDispatchFunction(hCommandGraph, hFunction, pDispatchFuncArgs, hEvent);
}
xe_result_t __xecall xeCommandListEncodeDispatchFunctionIndirect(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        const xe_dispatch_function_indirect_arguments_t* pDispatchArgumentsBuffer,  ///< [in] Pointer to buffer that will contain dispatch arguments.
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeDispatchFunctionIndirect(hCommandList, hFunction, pDispatchArgumentsBuffer, hEvent);
}
xe_result_t __xecall xeCommandGraphEncodeDispatchFunctionIndirect(
        xe_command_graph_handle_t hCommandGraph,        ///< [in] handle of the command graph
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        const xe_dispatch_function_indirect_arguments_t* pDispatchArgumentsBuffer,  ///< [in] Pointer to buffer that will contain dispatch arguments.
        xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandGraphEncodeDispatchFunctionIndirect(hCommandGraph, hFunction, pDispatchArgumentsBuffer, hEvent);
}
xe_result_t __xecall xeCommandListEncodeDispatchHostFunction(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_host_pfn_t pfnHostFunc,                      ///< [in] pointer to host function.
        void* pUserData                                 ///< [in] pointer to user data to pass to host function.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeDispatchHostFunction(hCommandList, pfnHostFunc, pUserData);
}
xe_result_t __xecall xeCommandGraphEncodeDispatchHostFunction(
        xe_command_graph_handle_t hCommandGraph,        ///< [in] handle of the command graph
        xe_host_pfn_t pfnHostFunc,                      ///< [in] pointer to host function.
        void* pUserData                                 ///< [in] pointer to user data to pass to host function.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandGraphEncodeDispatchHostFunction(hCommandGraph, pfnHostFunc, pUserData);
}
xe_result_t __xecall xeDeviceMakeMemoryResident(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to make resident
        size_t size                                     ///< [in] size in bytes to make resident
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceMakeMemoryResident(hDevice, ptr, size);
}
xe_result_t __xecall xeDeviceEvictMemory(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to evict
        size_t size                                     ///< [in] size in bytes to evict
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceEvictMemory(hDevice, ptr, size);
}
xe_result_t __xecall xeDeviceMakeImageResident(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_image_handle_t hImage                        ///< [in] handle of image to make resident
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceMakeImageResident(hDevice, hImage);
}
xe_result_t __xecall xeDeviceEvictImage(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_image_handle_t hImage                        ///< [in] handle of image to make evict
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceEvictImage(hDevice, hImage);
}
xe_result_t __xecall xeDeviceCreateSemaphore(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_semaphore_desc_t* desc,                ///< [in] pointer to semaphore descriptor
        xe_semaphore_handle_t* phSemaphore              ///< [out] pointer to handle of semaphore object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceCreateSemaphore(hDevice, desc, phSemaphore);
}
xe_result_t __xecall xeSemaphoreDestroy(
        xe_semaphore_handle_t hSemaphore                ///< [in] handle of semaphore object to destroy
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeSemaphoreDestroy(hSemaphore);
}
xe_result_t __xecall xeCommandListEncodeSemaphoreSignal(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_semaphore_handle_t hSemaphore,               ///< [in] handle of the semaphore
        xe_semaphore_value_t value                      ///< [in] the value to write on signal
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeSemaphoreSignal(hCommandList, hSemaphore, value);
}
xe_result_t __xecall xeCommandListEncodeSemaphoreWait(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_semaphore_handle_t hSemaphore,               ///< [in] handle of the semaphore
        xe_semaphore_wait_operation_t operation,        ///< [in] wait operation type
        xe_semaphore_value_t value                      ///< [in] the value to wait upon
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListEncodeSemaphoreWait(hCommandList, hSemaphore, operation, value);
}
xe_result_t __xecall xeSemaphoreQueryValue(
        xe_semaphore_handle_t hSemaphore                ///< [in] handle of the semaphore
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeSemaphoreQueryValue(hSemaphore);
}
xe_result_t __xecall xeSemaphoreReset(
        xe_semaphore_handle_t hSemaphore                ///< [in] handle of the semaphore
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeSemaphoreReset(hSemaphore);
}

#if defined(__cplusplus)
};
#endif
