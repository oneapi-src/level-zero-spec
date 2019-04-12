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
* DO NOT EDIT: generated from /scripts/templates/icd_loader.cpp.mako
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

xe_result_t __xecall xeCommandListAppendBarrier(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before executing
                                                        ///< barrier
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListAppendBarrier(hCommandList, hSignalEvent, numWaitEvents, phWaitEvents);
}
xe_result_t __xecall xeCommandListAppendMemoryRangesBarrier(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numRanges,                             ///< [in] number of memory ranges
        const size_t* pRangeSizes,                      ///< [in] array of sizes of memory range
        const void** pRanges,                           ///< [in] array of memory ranges
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before executing
                                                        ///< barrier
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListAppendMemoryRangesBarrier(hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents);
}
xe_result_t __xecall xeDeviceSystemBarrier(
        xe_device_handle_t hDevice                      ///< [in] handle of the device
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceSystemBarrier(hDevice);
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
xe_result_t __xecall xeCommandListCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        const xe_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
        xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListCreate(hDevice, desc, phCommandList);
}
xe_result_t __xecall xeCommandListCreateImmediate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
        xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListCreateImmediate(hDevice, desc, phCommandList);
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
xe_result_t __xecall xeCommandListReserveSpace(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        size_t size,                                    ///< [in] size (in bytes) to reserve
        void** ptr                                      ///< [out] pointer to command buffer space reserved
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListReserveSpace(hCommandList, size, ptr);
}
xe_result_t __xecall xeCommandQueueCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
        xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandQueueCreate(hDevice, desc, phCommandQueue);
}
xe_result_t __xecall xeCommandQueueDestroy(
        xe_command_queue_handle_t hCommandQueue         ///< [in] handle of command queue object to destroy
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandQueueDestroy(hCommandQueue);
}
xe_result_t __xecall xeCommandQueueExecuteCommandLists(
        xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t numCommandLists,                       ///< [in] number of command lists to execute
        xe_command_list_handle_t* phCommandLists,       ///< [in] list of handles of the command lists to execute
        xe_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandQueueExecuteCommandLists(hCommandQueue, numCommandLists, phCommandLists, hFence);
}
xe_result_t __xecall xeCommandQueueSynchronize(
        xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                        ///< returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::xeFenceQueryStatus;
                                                        ///< if MAX_UINT32, then function will not return until complete or device
                                                        ///< is lost.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandQueueSynchronize(hCommandQueue, timeout);
}
xe_result_t __xecall xeCommandListAppendMemoryCopy(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before copy
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListAppendMemoryCopy(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
}
xe_result_t __xecall xeCommandListAppendMemorySet(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* ptr,                                      ///< [in] pointer to memory to initialize
        int value,                                      ///< [in] value to initialize memory to
        size_t size,                                    ///< [in] size in bytes to initailize
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before copy
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListAppendMemorySet(hCommandList, ptr, value, size, hSignalEvent, numWaitEvents, phWaitEvents);
}
xe_result_t __xecall xeCommandListAppendImageCopy(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before copy
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListAppendImageCopy(hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents);
}
xe_result_t __xecall xeCommandListAppendImageCopyRegion(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        xe_image_region_t* pDstRegion,                  ///< [in][optional] destination region descriptor
        xe_image_region_t* pSrcRegion,                  ///< [in][optional] source region descriptor
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before copy
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListAppendImageCopyRegion(hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents);
}
xe_result_t __xecall xeCommandListAppendImageCopyToMemory(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        xe_image_region_t* pSrcRegion,                  ///< [in][optional] source region descriptor
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before copy
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListAppendImageCopyToMemory(hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents);
}
xe_result_t __xecall xeCommandListAppendImageCopyFromMemory(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        xe_image_region_t* pDstRegion,                  ///< [in][optional] destination region descriptor
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before copy
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListAppendImageCopyFromMemory(hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents);
}
xe_result_t __xecall xeCommandListAppendMemoryPrefetch(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
        size_t count                                    ///< [in] size in bytes of the memory range to prefetch
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListAppendMemoryPrefetch(hCommandList, ptr, count);
}
xe_result_t __xecall xeCommandListAppendMemAdvise(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        xe_memory_advice_t advice                       ///< [in] Memory advice for the memory range
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListAppendMemAdvise(hCommandList, hDevice, ptr, size, advice);
}
xe_result_t __xecall xeDeviceGetCount(
        uint32_t* count                                 ///< [out] number of devices available
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceGetCount(count);
}
xe_result_t __xecall xeDeviceGet(
        uint32_t ordinal,                               ///< [in] The device index in the range of [0, ::xeDeviceGetCount]
        xe_device_handle_t* phDevice                    ///< [out] pointer to handle of device object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceGet(ordinal, phDevice);
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
xe_result_t __xecall xeDeviceGetP2PProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        xe_device_p2p_properties_t* pP2PProperties      ///< [out] Peer-to-Peer properties between source and peer device
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeDeviceGetP2PProperties(hDevice, hPeerDevice, pP2PProperties);
}
xe_result_t __xecall xeDeviceCanAccessPeer(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        xe_bool_t* value                                ///< [out] returned access capability
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
xe_result_t __xecall xeInit(
        xe_init_flag_t flags                            ///< [in] initialization flags
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeInit(flags);
}
xe_result_t __xecall xeGetDriverVersion(
        uint32_t* version                               ///< [out] driver version
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeGetDriverVersion(version);
}
xe_result_t __xecall xeEventPoolCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
        xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventPoolCreate(hDevice, desc, phEventPool);
}
xe_result_t __xecall xeEventPoolDestroy(
        xe_event_pool_handle_t hEventPool               ///< [in] handle of event pool object to destroy
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventPoolDestroy(hEventPool);
}
xe_result_t __xecall xeEventCreate(
        xe_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        const xe_event_desc_t* desc,                    ///< [in] pointer to event descriptor
        xe_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventCreate(hEventPool, desc, phEvent);
}
xe_result_t __xecall xeEventDestroy(
        xe_event_handle_t hEvent                        ///< [in] handle of event object to destroy
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventDestroy(hEvent);
}
xe_result_t __xecall xeEventPoolGetIpcHandle(
        xe_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
        xe_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventPoolGetIpcHandle(hEventPool, phIpc);
}
xe_result_t __xecall xeEventPoolOpenIpcHandle(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC event pool handle
        xe_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event handle
        xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventPoolOpenIpcHandle(hDevice, hIpc, phEventPool);
}
xe_result_t __xecall xeEventPoolCloseIpcHandle(
        xe_event_pool_handle_t hEventPool               ///< [in] handle of event pool object
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventPoolCloseIpcHandle(hEventPool);
}
xe_result_t __xecall xeCommandListAppendSignalEvent(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListAppendSignalEvent(hCommandList, hEvent);
}
xe_result_t __xecall xeCommandListAppendWaitOnEvents(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
        xe_event_handle_t* phEvents                     ///< [in] handle of the events to wait on before continuing
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListAppendWaitOnEvents(hCommandList, numEvents, phEvents);
}
xe_result_t __xecall xeEventHostSignal(
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventHostSignal(hEvent);
}
xe_result_t __xecall xeEventHostSynchronize(
        xe_event_handle_t hEvent,                       ///< [in] handle of the event
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                        ///< returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::xeEventQueryStatus;
                                                        ///< if MAX_UINT32, then function will not return until complete or device
                                                        ///< is lost.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventHostSynchronize(hEvent, timeout);
}
xe_result_t __xecall xeEventQueryStatus(
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventQueryStatus(hEvent);
}
xe_result_t __xecall xeCommandListAppendEventReset(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListAppendEventReset(hCommandList, hEvent);
}
xe_result_t __xecall xeEventReset(
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeEventReset(hEvent);
}
xe_result_t __xecall xeFenceCreate(
        xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
        const xe_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
        xe_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFenceCreate(hCommandQueue, desc, phFence);
}
xe_result_t __xecall xeFenceDestroy(
        xe_fence_handle_t hFence                        ///< [in] handle of fence object to destroy
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFenceDestroy(hFence);
}
xe_result_t __xecall xeFenceHostSynchronize(
        xe_fence_handle_t hFence,                       ///< [in] handle of the fence
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                        ///< returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::xeFenceQueryStatus;
                                                        ///< if MAX_UINT32, then function will not return until complete or device
                                                        ///< is lost.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFenceHostSynchronize(hFence, timeout);
}
xe_result_t __xecall xeFenceQueryStatus(
        xe_fence_handle_t hFence                        ///< [in] handle of the fence
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFenceQueryStatus(hFence);
}
xe_result_t __xecall xeFenceReset(
        xe_fence_handle_t hFence                        ///< [in] handle of the fence
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFenceReset(hFence);
}
xe_result_t __xecall xeImageGetProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        xe_image_properties_t* pImageProperties         ///< [out] pointer to image properties
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeImageGetProperties(hDevice, desc, pImageProperties);
}
xe_result_t __xecall xeImageCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        xe_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeImageCreate(hDevice, desc, phImage);
}
xe_result_t __xecall xeImageDestroy(
        xe_image_handle_t hImage                        ///< [in] handle of image object to destroy
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeImageDestroy(hImage);
}
xe_result_t __xecall xeSharedMemAlloc(
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
    return dispatchTable.xeSharedMemAlloc(hDevice, device_flags, host_flags, size, alignment, ptr);
}
xe_result_t __xecall xeMemAlloc(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_device_mem_alloc_flag_t flags,               ///< [in] flags specifying additional allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** ptr                                      ///< [out] pointer to device allocation
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeMemAlloc(hDevice, flags, size, alignment, ptr);
}
xe_result_t __xecall xeHostMemAlloc(
        xe_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** ptr                                      ///< [out] pointer to host allocation
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeHostMemAlloc(flags, size, alignment, ptr);
}
xe_result_t __xecall xeMemFree(
        const void* ptr                                 ///< [in] pointer to memory to free
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeMemFree(ptr);
}
xe_result_t __xecall xeMemGetProperties(
        const void* ptr,                                ///< [in] Pointer to query
        xe_memory_allocation_properties_t* pMemProperties   ///< [out] Query result for memory allocation properties
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeMemGetProperties(ptr, pMemProperties);
}
xe_result_t __xecall xeMemGetAddressRange(
        const void* ptr,                                ///< [in] Pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeMemGetAddressRange(ptr, pBase, pSize);
}
xe_result_t __xecall xeIpcGetMemHandle(
        const void* ptr,                                ///< [in] Pointer to the device memory allocation
        xe_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeIpcGetMemHandle(ptr, pIpcHandle);
}
xe_result_t __xecall xeIpcOpenMemHandle(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
        xe_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
        xe_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
        void** ptr                                      ///< [out] pointer to device allocation in this process
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeIpcOpenMemHandle(hDevice, handle, flags, ptr);
}
xe_result_t __xecall xeIpcCloseMemHandle(
        const void* ptr                                 ///< [in] pointer to device allocation in this process
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeIpcCloseMemHandle(ptr);
}
xe_result_t __xecall xeModuleCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_module_desc_t* pDesc,                  ///< [in] pointer to module descriptor
        xe_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
        xe_module_build_log_handle_t* phBuildLog        ///< [in,out][optional] pointer to handle of module's build log.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeModuleCreate(hDevice, pDesc, phModule, phBuildLog);
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
        size_t* pSize,                                  ///< [in,out] size of build log string.
        char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeModuleBuildLogGetString(hModuleBuildLog, pSize, pBuildLog);
}
xe_result_t __xecall xeModuleGetNativeBinary(
        xe_module_handle_t hModule,                     ///< [in] handle of the device
        size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
        uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeModuleGetNativeBinary(hModule, pSize, pModuleNativeBinary);
}
xe_result_t __xecall xeModuleGetGlobalPointer(
        xe_module_handle_t hModule,                     ///< [in] handle of the device
        const char* pGlobalName,                        ///< [in] name of function in global
        void** pPtr                                     ///< [out] device visible pointer
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeModuleGetGlobalPointer(hModule, pGlobalName, pPtr);
}
xe_result_t __xecall xeFunctionCreate(
        xe_module_handle_t hModule,                     ///< [in] handle of the module
        const xe_function_desc_t* pDesc,                ///< [in] pointer to function descriptor
        xe_function_handle_t* phFunction                ///< [out] handle of the Function object
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFunctionCreate(hModule, pDesc, phFunction);
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
        xe_function_handle_t hFunction,                 ///< [in,out] handle of the function args object.
        uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
        size_t argSize,                                 ///< [in] size of argument type
        const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                        ///< null then argument value is considered null.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeFunctionSetArgumentValue(hFunction, argIndex, argSize, pArgValue);
}
xe_result_t __xecall xeFunctionSetAttribute(
        xe_function_handle_t hFunction,                 ///< [in,out] handle of the function.
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
xe_result_t __xecall xeCommandListAppendLaunchFunction(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        const xe_thread_group_dimensions_t* pLaunchFuncArgs,///< [in] launch function arguments.
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before launching
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListAppendLaunchFunction(hCommandList, hFunction, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents);
}
xe_result_t __xecall xeCommandListAppendLaunchFunctionIndirect(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        const xe_thread_group_dimensions_t* pLaunchArgumentsBuffer, ///< [in] pointer to device buffer that will contain launch arguments
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before launching
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListAppendLaunchFunctionIndirect(hCommandList, hFunction, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents);
}
xe_result_t __xecall xeCommandListAppendLaunchMultipleFunctionsIndirect(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numFunctions,                          ///< [in] maximum number of functions to launch
        const xe_function_handle_t* phFunctions,        ///< [in] handles of the function objects
        const size_t* pNumLaunchArguments,              ///< [in] pointer to device memory location that will contain the actual
                                                        ///< number of launch arguments; must be less-than or equal-to numFunctions
        const xe_thread_group_dimensions_t* pLaunchArgumentsBuffer, ///< [in] pointer to device buffer that will contain a contiguous array of
                                                        ///< launch arguments
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before launching
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListAppendLaunchMultipleFunctionsIndirect(hCommandList, numFunctions, phFunctions, pNumLaunchArguments, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents);
}
xe_result_t __xecall xeCommandListAppendLaunchHostFunction(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_host_pfn_t pfnHostFunc,                      ///< [in] pointer to host function.
        void* pUserData                                 ///< [in] pointer to user data to pass to host function.
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeCommandListAppendLaunchHostFunction(hCommandList, pfnHostFunc, pUserData);
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
xe_result_t __xecall xeSamplerCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_sampler_desc_t* pDesc,                 ///< [in] pointer to sampler descriptor
        xe_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeSamplerCreate(hDevice, pDesc, phSampler);
}
xe_result_t __xecall xeSamplerDestroy(
        xe_sampler_handle_t hSampler                    ///< [in] handle of the sampler
    ){
    if(dispatchTableInitialized == false){
        return XE_RESULT_ERROR_UNINITIALIZED;
    }
    return dispatchTable.xeSamplerDestroy(hSampler);
}

#if defined(__cplusplus)
};
#endif
