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
* @file core_layer.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/layer.cpp.mako
* @endcond
*
******************************************************************************/
#include "core_layer.h"

namespace xe_layer
{
    extern context_t context;

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Loads function pointer table for loaded driver
    bool xeIntercept(
        xeapi_pfntable_ptr_t pfntable )   ///< [in] pointer to table of xe API function pointers
    {
        if((nullptr == context.xeapi) || (nullptr == pfntable))
            return false;

        context.xeapi->xeCommandListAppendBarrier                                  = pfntable->xeCommandListAppendBarrier;
        pfntable->xeCommandListAppendBarrier                                       = xeCommandListAppendBarrier;

        context.xeapi->xeCommandListAppendMemoryRangesBarrier                      = pfntable->xeCommandListAppendMemoryRangesBarrier;
        pfntable->xeCommandListAppendMemoryRangesBarrier                           = xeCommandListAppendMemoryRangesBarrier;

        context.xeapi->xeDeviceSystemBarrier                                       = pfntable->xeDeviceSystemBarrier;
        pfntable->xeDeviceSystemBarrier                                            = xeDeviceSystemBarrier;

        #if XE_ENABLE_OCL_INTEROP
        context.xeapi->xeDeviceRegisterCLMemory                                    = pfntable->xeDeviceRegisterCLMemory;
        pfntable->xeDeviceRegisterCLMemory                                         = xeDeviceRegisterCLMemory;
        #endif // XE_ENABLE_OCL_INTEROP

        #if XE_ENABLE_OCL_INTEROP
        context.xeapi->xeDeviceRegisterCLProgram                                   = pfntable->xeDeviceRegisterCLProgram;
        pfntable->xeDeviceRegisterCLProgram                                        = xeDeviceRegisterCLProgram;
        #endif // XE_ENABLE_OCL_INTEROP

        #if XE_ENABLE_OCL_INTEROP
        context.xeapi->xeDeviceRegisterCLCommandQueue                              = pfntable->xeDeviceRegisterCLCommandQueue;
        pfntable->xeDeviceRegisterCLCommandQueue                                   = xeDeviceRegisterCLCommandQueue;
        #endif // XE_ENABLE_OCL_INTEROP

        context.xeapi->xeCommandListCreate                                         = pfntable->xeCommandListCreate;
        pfntable->xeCommandListCreate                                              = xeCommandListCreate;

        context.xeapi->xeCommandListCreateImmediate                                = pfntable->xeCommandListCreateImmediate;
        pfntable->xeCommandListCreateImmediate                                     = xeCommandListCreateImmediate;

        context.xeapi->xeCommandListDestroy                                        = pfntable->xeCommandListDestroy;
        pfntable->xeCommandListDestroy                                             = xeCommandListDestroy;

        context.xeapi->xeCommandListClose                                          = pfntable->xeCommandListClose;
        pfntable->xeCommandListClose                                               = xeCommandListClose;

        context.xeapi->xeCommandListReset                                          = pfntable->xeCommandListReset;
        pfntable->xeCommandListReset                                               = xeCommandListReset;

        context.xeapi->xeCommandListSetParameter                                   = pfntable->xeCommandListSetParameter;
        pfntable->xeCommandListSetParameter                                        = xeCommandListSetParameter;

        context.xeapi->xeCommandListGetParameter                                   = pfntable->xeCommandListGetParameter;
        pfntable->xeCommandListGetParameter                                        = xeCommandListGetParameter;

        context.xeapi->xeCommandListResetParameters                                = pfntable->xeCommandListResetParameters;
        pfntable->xeCommandListResetParameters                                     = xeCommandListResetParameters;

        context.xeapi->xeCommandListReserveSpace                                   = pfntable->xeCommandListReserveSpace;
        pfntable->xeCommandListReserveSpace                                        = xeCommandListReserveSpace;

        context.xeapi->xeCommandQueueCreate                                        = pfntable->xeCommandQueueCreate;
        pfntable->xeCommandQueueCreate                                             = xeCommandQueueCreate;

        context.xeapi->xeCommandQueueDestroy                                       = pfntable->xeCommandQueueDestroy;
        pfntable->xeCommandQueueDestroy                                            = xeCommandQueueDestroy;

        context.xeapi->xeCommandQueueExecuteCommandLists                           = pfntable->xeCommandQueueExecuteCommandLists;
        pfntable->xeCommandQueueExecuteCommandLists                                = xeCommandQueueExecuteCommandLists;

        context.xeapi->xeCommandQueueSynchronize                                   = pfntable->xeCommandQueueSynchronize;
        pfntable->xeCommandQueueSynchronize                                        = xeCommandQueueSynchronize;

        context.xeapi->xeCommandListAppendMemoryCopy                               = pfntable->xeCommandListAppendMemoryCopy;
        pfntable->xeCommandListAppendMemoryCopy                                    = xeCommandListAppendMemoryCopy;

        context.xeapi->xeCommandListAppendMemorySet                                = pfntable->xeCommandListAppendMemorySet;
        pfntable->xeCommandListAppendMemorySet                                     = xeCommandListAppendMemorySet;

        context.xeapi->xeCommandListAppendImageCopy                                = pfntable->xeCommandListAppendImageCopy;
        pfntable->xeCommandListAppendImageCopy                                     = xeCommandListAppendImageCopy;

        context.xeapi->xeCommandListAppendImageCopyRegion                          = pfntable->xeCommandListAppendImageCopyRegion;
        pfntable->xeCommandListAppendImageCopyRegion                               = xeCommandListAppendImageCopyRegion;

        context.xeapi->xeCommandListAppendImageCopyToMemory                        = pfntable->xeCommandListAppendImageCopyToMemory;
        pfntable->xeCommandListAppendImageCopyToMemory                             = xeCommandListAppendImageCopyToMemory;

        context.xeapi->xeCommandListAppendImageCopyFromMemory                      = pfntable->xeCommandListAppendImageCopyFromMemory;
        pfntable->xeCommandListAppendImageCopyFromMemory                           = xeCommandListAppendImageCopyFromMemory;

        context.xeapi->xeCommandListAppendMemoryPrefetch                           = pfntable->xeCommandListAppendMemoryPrefetch;
        pfntable->xeCommandListAppendMemoryPrefetch                                = xeCommandListAppendMemoryPrefetch;

        context.xeapi->xeCommandListAppendMemAdvise                                = pfntable->xeCommandListAppendMemAdvise;
        pfntable->xeCommandListAppendMemAdvise                                     = xeCommandListAppendMemAdvise;

        context.xeapi->xeDeviceGetCount                                            = pfntable->xeDeviceGetCount;
        pfntable->xeDeviceGetCount                                                 = xeDeviceGetCount;

        context.xeapi->xeDeviceGet                                                 = pfntable->xeDeviceGet;
        pfntable->xeDeviceGet                                                      = xeDeviceGet;

        context.xeapi->xeDeviceGetSubDevice                                        = pfntable->xeDeviceGetSubDevice;
        pfntable->xeDeviceGetSubDevice                                             = xeDeviceGetSubDevice;

        context.xeapi->xeDeviceGetApiVersion                                       = pfntable->xeDeviceGetApiVersion;
        pfntable->xeDeviceGetApiVersion                                            = xeDeviceGetApiVersion;

        context.xeapi->xeDeviceGetProperties                                       = pfntable->xeDeviceGetProperties;
        pfntable->xeDeviceGetProperties                                            = xeDeviceGetProperties;

        context.xeapi->xeDeviceGetComputeProperties                                = pfntable->xeDeviceGetComputeProperties;
        pfntable->xeDeviceGetComputeProperties                                     = xeDeviceGetComputeProperties;

        context.xeapi->xeDeviceGetMemoryProperties                                 = pfntable->xeDeviceGetMemoryProperties;
        pfntable->xeDeviceGetMemoryProperties                                      = xeDeviceGetMemoryProperties;

        context.xeapi->xeDeviceGetP2PProperties                                    = pfntable->xeDeviceGetP2PProperties;
        pfntable->xeDeviceGetP2PProperties                                         = xeDeviceGetP2PProperties;

        context.xeapi->xeDeviceCanAccessPeer                                       = pfntable->xeDeviceCanAccessPeer;
        pfntable->xeDeviceCanAccessPeer                                            = xeDeviceCanAccessPeer;

        context.xeapi->xeDeviceSetIntermediateCacheConfig                          = pfntable->xeDeviceSetIntermediateCacheConfig;
        pfntable->xeDeviceSetIntermediateCacheConfig                               = xeDeviceSetIntermediateCacheConfig;

        context.xeapi->xeDeviceSetLastLevelCacheConfig                             = pfntable->xeDeviceSetLastLevelCacheConfig;
        pfntable->xeDeviceSetLastLevelCacheConfig                                  = xeDeviceSetLastLevelCacheConfig;

        context.xeapi->xeInit                                                      = pfntable->xeInit;
        pfntable->xeInit                                                           = xeInit;

        context.xeapi->xeGetDriverVersion                                          = pfntable->xeGetDriverVersion;
        pfntable->xeGetDriverVersion                                               = xeGetDriverVersion;

        context.xeapi->xeEventPoolCreate                                           = pfntable->xeEventPoolCreate;
        pfntable->xeEventPoolCreate                                                = xeEventPoolCreate;

        context.xeapi->xeEventPoolDestroy                                          = pfntable->xeEventPoolDestroy;
        pfntable->xeEventPoolDestroy                                               = xeEventPoolDestroy;

        context.xeapi->xeEventCreate                                               = pfntable->xeEventCreate;
        pfntable->xeEventCreate                                                    = xeEventCreate;

        context.xeapi->xeEventDestroy                                              = pfntable->xeEventDestroy;
        pfntable->xeEventDestroy                                                   = xeEventDestroy;

        context.xeapi->xeEventPoolGetIpcHandle                                     = pfntable->xeEventPoolGetIpcHandle;
        pfntable->xeEventPoolGetIpcHandle                                          = xeEventPoolGetIpcHandle;

        context.xeapi->xeEventPoolOpenIpcHandle                                    = pfntable->xeEventPoolOpenIpcHandle;
        pfntable->xeEventPoolOpenIpcHandle                                         = xeEventPoolOpenIpcHandle;

        context.xeapi->xeEventPoolCloseIpcHandle                                   = pfntable->xeEventPoolCloseIpcHandle;
        pfntable->xeEventPoolCloseIpcHandle                                        = xeEventPoolCloseIpcHandle;

        context.xeapi->xeCommandListAppendSignalEvent                              = pfntable->xeCommandListAppendSignalEvent;
        pfntable->xeCommandListAppendSignalEvent                                   = xeCommandListAppendSignalEvent;

        context.xeapi->xeCommandListAppendWaitOnEvents                             = pfntable->xeCommandListAppendWaitOnEvents;
        pfntable->xeCommandListAppendWaitOnEvents                                  = xeCommandListAppendWaitOnEvents;

        context.xeapi->xeEventHostSignal                                           = pfntable->xeEventHostSignal;
        pfntable->xeEventHostSignal                                                = xeEventHostSignal;

        context.xeapi->xeEventHostSynchronize                                      = pfntable->xeEventHostSynchronize;
        pfntable->xeEventHostSynchronize                                           = xeEventHostSynchronize;

        context.xeapi->xeEventQueryStatus                                          = pfntable->xeEventQueryStatus;
        pfntable->xeEventQueryStatus                                               = xeEventQueryStatus;

        context.xeapi->xeCommandListAppendEventReset                               = pfntable->xeCommandListAppendEventReset;
        pfntable->xeCommandListAppendEventReset                                    = xeCommandListAppendEventReset;

        context.xeapi->xeEventReset                                                = pfntable->xeEventReset;
        pfntable->xeEventReset                                                     = xeEventReset;

        context.xeapi->xeFenceCreate                                               = pfntable->xeFenceCreate;
        pfntable->xeFenceCreate                                                    = xeFenceCreate;

        context.xeapi->xeFenceDestroy                                              = pfntable->xeFenceDestroy;
        pfntable->xeFenceDestroy                                                   = xeFenceDestroy;

        context.xeapi->xeFenceHostSynchronize                                      = pfntable->xeFenceHostSynchronize;
        pfntable->xeFenceHostSynchronize                                           = xeFenceHostSynchronize;

        context.xeapi->xeFenceQueryStatus                                          = pfntable->xeFenceQueryStatus;
        pfntable->xeFenceQueryStatus                                               = xeFenceQueryStatus;

        context.xeapi->xeFenceReset                                                = pfntable->xeFenceReset;
        pfntable->xeFenceReset                                                     = xeFenceReset;

        context.xeapi->xeImageGetProperties                                        = pfntable->xeImageGetProperties;
        pfntable->xeImageGetProperties                                             = xeImageGetProperties;

        context.xeapi->xeImageCreate                                               = pfntable->xeImageCreate;
        pfntable->xeImageCreate                                                    = xeImageCreate;

        context.xeapi->xeImageDestroy                                              = pfntable->xeImageDestroy;
        pfntable->xeImageDestroy                                                   = xeImageDestroy;

        context.xeapi->xeSharedMemAlloc                                            = pfntable->xeSharedMemAlloc;
        pfntable->xeSharedMemAlloc                                                 = xeSharedMemAlloc;

        context.xeapi->xeMemAlloc                                                  = pfntable->xeMemAlloc;
        pfntable->xeMemAlloc                                                       = xeMemAlloc;

        context.xeapi->xeHostMemAlloc                                              = pfntable->xeHostMemAlloc;
        pfntable->xeHostMemAlloc                                                   = xeHostMemAlloc;

        context.xeapi->xeMemFree                                                   = pfntable->xeMemFree;
        pfntable->xeMemFree                                                        = xeMemFree;

        context.xeapi->xeMemGetProperties                                          = pfntable->xeMemGetProperties;
        pfntable->xeMemGetProperties                                               = xeMemGetProperties;

        context.xeapi->xeMemGetAddressRange                                        = pfntable->xeMemGetAddressRange;
        pfntable->xeMemGetAddressRange                                             = xeMemGetAddressRange;

        context.xeapi->xeIpcGetMemHandle                                           = pfntable->xeIpcGetMemHandle;
        pfntable->xeIpcGetMemHandle                                                = xeIpcGetMemHandle;

        context.xeapi->xeIpcOpenMemHandle                                          = pfntable->xeIpcOpenMemHandle;
        pfntable->xeIpcOpenMemHandle                                               = xeIpcOpenMemHandle;

        context.xeapi->xeIpcCloseMemHandle                                         = pfntable->xeIpcCloseMemHandle;
        pfntable->xeIpcCloseMemHandle                                              = xeIpcCloseMemHandle;

        context.xeapi->xeModuleCreate                                              = pfntable->xeModuleCreate;
        pfntable->xeModuleCreate                                                   = xeModuleCreate;

        context.xeapi->xeModuleDestroy                                             = pfntable->xeModuleDestroy;
        pfntable->xeModuleDestroy                                                  = xeModuleDestroy;

        context.xeapi->xeModuleBuildLogDestroy                                     = pfntable->xeModuleBuildLogDestroy;
        pfntable->xeModuleBuildLogDestroy                                          = xeModuleBuildLogDestroy;

        context.xeapi->xeModuleBuildLogGetString                                   = pfntable->xeModuleBuildLogGetString;
        pfntable->xeModuleBuildLogGetString                                        = xeModuleBuildLogGetString;

        context.xeapi->xeModuleGetNativeBinary                                     = pfntable->xeModuleGetNativeBinary;
        pfntable->xeModuleGetNativeBinary                                          = xeModuleGetNativeBinary;

        context.xeapi->xeModuleGetGlobalPointer                                    = pfntable->xeModuleGetGlobalPointer;
        pfntable->xeModuleGetGlobalPointer                                         = xeModuleGetGlobalPointer;

        context.xeapi->xeFunctionCreate                                            = pfntable->xeFunctionCreate;
        pfntable->xeFunctionCreate                                                 = xeFunctionCreate;

        context.xeapi->xeFunctionDestroy                                           = pfntable->xeFunctionDestroy;
        pfntable->xeFunctionDestroy                                                = xeFunctionDestroy;

        context.xeapi->xeModuleGetFunctionPointer                                  = pfntable->xeModuleGetFunctionPointer;
        pfntable->xeModuleGetFunctionPointer                                       = xeModuleGetFunctionPointer;

        context.xeapi->xeFunctionSetGroupSize                                      = pfntable->xeFunctionSetGroupSize;
        pfntable->xeFunctionSetGroupSize                                           = xeFunctionSetGroupSize;

        context.xeapi->xeFunctionSuggestGroupSize                                  = pfntable->xeFunctionSuggestGroupSize;
        pfntable->xeFunctionSuggestGroupSize                                       = xeFunctionSuggestGroupSize;

        context.xeapi->xeFunctionSetArgumentValue                                  = pfntable->xeFunctionSetArgumentValue;
        pfntable->xeFunctionSetArgumentValue                                       = xeFunctionSetArgumentValue;

        context.xeapi->xeFunctionSetAttribute                                      = pfntable->xeFunctionSetAttribute;
        pfntable->xeFunctionSetAttribute                                           = xeFunctionSetAttribute;

        context.xeapi->xeFunctionGetAttribute                                      = pfntable->xeFunctionGetAttribute;
        pfntable->xeFunctionGetAttribute                                           = xeFunctionGetAttribute;

        context.xeapi->xeCommandListAppendLaunchFunction                           = pfntable->xeCommandListAppendLaunchFunction;
        pfntable->xeCommandListAppendLaunchFunction                                = xeCommandListAppendLaunchFunction;

        context.xeapi->xeCommandListAppendLaunchFunctionIndirect                   = pfntable->xeCommandListAppendLaunchFunctionIndirect;
        pfntable->xeCommandListAppendLaunchFunctionIndirect                        = xeCommandListAppendLaunchFunctionIndirect;

        context.xeapi->xeCommandListAppendLaunchMultipleFunctionsIndirect          = pfntable->xeCommandListAppendLaunchMultipleFunctionsIndirect;
        pfntable->xeCommandListAppendLaunchMultipleFunctionsIndirect               = xeCommandListAppendLaunchMultipleFunctionsIndirect;

        context.xeapi->xeCommandListAppendLaunchHostFunction                       = pfntable->xeCommandListAppendLaunchHostFunction;
        pfntable->xeCommandListAppendLaunchHostFunction                            = xeCommandListAppendLaunchHostFunction;

        context.xeapi->xeDeviceMakeMemoryResident                                  = pfntable->xeDeviceMakeMemoryResident;
        pfntable->xeDeviceMakeMemoryResident                                       = xeDeviceMakeMemoryResident;

        context.xeapi->xeDeviceEvictMemory                                         = pfntable->xeDeviceEvictMemory;
        pfntable->xeDeviceEvictMemory                                              = xeDeviceEvictMemory;

        context.xeapi->xeDeviceMakeImageResident                                   = pfntable->xeDeviceMakeImageResident;
        pfntable->xeDeviceMakeImageResident                                        = xeDeviceMakeImageResident;

        context.xeapi->xeDeviceEvictImage                                          = pfntable->xeDeviceEvictImage;
        pfntable->xeDeviceEvictImage                                               = xeDeviceEvictImage;

        context.xeapi->xeSamplerCreate                                             = pfntable->xeSamplerCreate;
        pfntable->xeSamplerCreate                                                  = xeSamplerCreate;

        context.xeapi->xeSamplerDestroy                                            = pfntable->xeSamplerDestroy;
        pfntable->xeSamplerDestroy                                                 = xeSamplerDestroy;


        return true;
    }

} // namespace xe_layer


#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendBarrier(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before executing
                                                        ///< barrier
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListAppendBarrier(hCommandList, hSignalEvent, numWaitEvents, phWaitEvents);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendMemoryRangesBarrier(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numRanges,                             ///< [in] number of memory ranges
        const size_t* pRangeSizes,                      ///< [in] array of sizes of memory range
        const void** pRanges,                           ///< [in] array of memory ranges
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before executing
                                                        ///< barrier
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pRangeSizes ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pRanges ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListAppendMemoryRangesBarrier(hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceSystemBarrier(
        xe_device_handle_t hDevice                      ///< [in] handle of the device
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeDeviceSystemBarrier(hDevice);
}

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
xe_result_t __xecall
xeDeviceRegisterCLMemory(
        xe_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context context,                             ///< [in] the OpenCL context that created the memory
        cl_mem mem,                                     ///< [in] the OpenCL memory to register
        void** ptr                                      ///< [out] pointer to device allocation
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeDeviceRegisterCLMemory(hDevice, context, mem, ptr);
}
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
xe_result_t __xecall
xeDeviceRegisterCLProgram(
        xe_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context context,                             ///< [in] the OpenCL context that created the program
        cl_program program,                             ///< [in] the OpenCL program to register
        xe_module_handle_t* phModule                    ///< [out] pointer to handle of module object created
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phModule ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeDeviceRegisterCLProgram(hDevice, context, program, phModule);
}
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
xe_result_t __xecall
xeDeviceRegisterCLCommandQueue(
        xe_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context context,                             ///< [in] the OpenCL context that created the command queue
        cl_command_queue command_queue,                 ///< [in] the OpenCL command queue to register
        xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phCommandQueue ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeDeviceRegisterCLCommandQueue(hDevice, context, command_queue, phCommandQueue);
}
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        const xe_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
        xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_COMMAND_LIST_DESC_VERSION_CURRENT < desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_layer::context.xeapi->xeCommandListCreate(hDevice, desc, phCommandList);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListCreateImmediate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
        xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_COMMAND_QUEUE_DESC_VERSION_CURRENT < desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_layer::context.xeapi->xeCommandListCreateImmediate(hDevice, desc, phCommandList);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListDestroy(
        xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to destroy
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListDestroy(hCommandList);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListClose(
        xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListClose(hCommandList);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListReset(
        xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListReset(hCommandList);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListSetParameter(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_command_list_parameter_t parameter,          ///< [in] parameter to change
        uint32_t value                                  ///< [in] value of attribute
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListSetParameter(hCommandList, parameter, value);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListGetParameter(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_command_list_parameter_t parameter,          ///< [in] parameter to retrieve
        uint32_t* value                                 ///< [out] value of attribute
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == value ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListGetParameter(hCommandList, parameter, value);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListResetParameters(
        xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListResetParameters(hCommandList);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListReserveSpace(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        size_t size,                                    ///< [in] size (in bytes) to reserve
        void** ptr                                      ///< [out] pointer to command buffer space reserved
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListReserveSpace(hCommandList, size, ptr);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandQueueCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
        xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phCommandQueue ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_COMMAND_QUEUE_DESC_VERSION_CURRENT < desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_layer::context.xeapi->xeCommandQueueCreate(hDevice, desc, phCommandQueue);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandQueueDestroy(
        xe_command_queue_handle_t hCommandQueue         ///< [in] handle of command queue object to destroy
    ){
    // Check parameters
    if( nullptr == hCommandQueue ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandQueueDestroy(hCommandQueue);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandQueueExecuteCommandLists(
        xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t numCommandLists,                       ///< [in] number of command lists to execute
        xe_command_list_handle_t* phCommandLists,       ///< [in] list of handles of the command lists to execute
        xe_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
    ){
    // Check parameters
    if( nullptr == hCommandQueue ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phCommandLists ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandQueueExecuteCommandLists(hCommandQueue, numCommandLists, phCommandLists, hFence);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandQueueSynchronize(
        xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                        ///< returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::xeFenceQueryStatus;
                                                        ///< if MAX_UINT32, then function will not return until complete or device
                                                        ///< is lost.
    ){
    // Check parameters
    if( nullptr == hCommandQueue ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandQueueSynchronize(hCommandQueue, timeout);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendMemoryCopy(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        size_t size,                                    ///< [in] size in bytes to copy
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before copy
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == dstptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == srcptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListAppendMemoryCopy(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendMemorySet(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* ptr,                                      ///< [in] pointer to memory to initialize
        int value,                                      ///< [in] value to initialize memory to
        size_t size,                                    ///< [in] size in bytes to initailize
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before copy
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListAppendMemorySet(hCommandList, ptr, value, size, hSignalEvent, numWaitEvents, phWaitEvents);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendImageCopy(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before copy
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hDstImage ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hSrcImage ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListAppendImageCopy(hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendImageCopyRegion(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        xe_image_region_t* pDstRegion,                  ///< [in][optional] destination region descriptor
        xe_image_region_t* pSrcRegion,                  ///< [in][optional] source region descriptor
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before copy
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hDstImage ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hSrcImage ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListAppendImageCopyRegion(hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendImageCopyToMemory(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        void* dstptr,                                   ///< [in] pointer to destination memory to copy to
        xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
        xe_image_region_t* pSrcRegion,                  ///< [in][optional] source region descriptor
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before copy
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == dstptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hSrcImage ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListAppendImageCopyToMemory(hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendImageCopyFromMemory(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
        const void* srcptr,                             ///< [in] pointer to source memory to copy from
        xe_image_region_t* pDstRegion,                  ///< [in][optional] destination region descriptor
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before copy
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before copy
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hDstImage ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == srcptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListAppendImageCopyFromMemory(hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendMemoryPrefetch(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
        size_t count                                    ///< [in] size in bytes of the memory range to prefetch
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListAppendMemoryPrefetch(hCommandList, ptr, count);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendMemAdvise(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        xe_memory_advice_t advice                       ///< [in] Memory advice for the memory range
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListAppendMemAdvise(hCommandList, hDevice, ptr, size, advice);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceGetCount(
        uint32_t* count                                 ///< [out] number of devices available
    ){
    // Check parameters
    if( nullptr == count ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeDeviceGetCount(count);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceGet(
        uint32_t ordinal,                               ///< [in] The device index in the range of [0, ::xeDeviceGetCount]
        xe_device_handle_t* phDevice                    ///< [out] pointer to handle of device object created
    ){
    // Check parameters
    if( nullptr == phDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeDeviceGet(ordinal, phDevice);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceGetSubDevice(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        uint32_t ordinal,                               ///< [in] ordinal of sub-device to retrieve
        xe_device_handle_t* phSubDevice                 ///< [out] pointer to handle of sub-device object.
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phSubDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeDeviceGetSubDevice(hDevice, ordinal, phSubDevice);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceGetApiVersion(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        xe_api_version_t* version                       ///< [out] api version
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == version ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeDeviceGetApiVersion(hDevice, version);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceGetProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        xe_device_properties_t* pDeviceProperties       ///< [out] query result for device properties
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pDeviceProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeDeviceGetProperties(hDevice, pDeviceProperties);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceGetComputeProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        xe_device_compute_properties_t* pComputeProperties  ///< [out] query result for compute properties
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pComputeProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeDeviceGetComputeProperties(hDevice, pComputeProperties);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceGetMemoryProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        xe_device_memory_properties_t* pMemProperties   ///< [out] query result for compute properties
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pMemProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeDeviceGetMemoryProperties(hDevice, pMemProperties);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceGetP2PProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        xe_device_p2p_properties_t* pP2PProperties      ///< [out] Peer-to-Peer properties between source and peer device
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hPeerDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pP2PProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeDeviceGetP2PProperties(hDevice, hPeerDevice, pP2PProperties);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceCanAccessPeer(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        xe_bool_t* value                                ///< [out] returned access capability
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hPeerDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == value ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeDeviceCanAccessPeer(hDevice, hPeerDevice, value);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceSetIntermediateCacheConfig(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device 
        xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeDeviceSetIntermediateCacheConfig(hDevice, CacheConfig);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceSetLastLevelCacheConfig(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device 
        xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeDeviceSetLastLevelCacheConfig(hDevice, CacheConfig);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeInit(
        xe_init_flag_t flags                            ///< [in] initialization flags
    ){
    // Check parameters

    return xe_layer::context.xeapi->xeInit(flags);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeGetDriverVersion(
        uint32_t* version                               ///< [out] driver version
    ){
    // Check parameters
    if( nullptr == version ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeGetDriverVersion(version);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventPoolCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
        xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phEventPool ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_EVENT_POOL_DESC_VERSION_CURRENT < desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_layer::context.xeapi->xeEventPoolCreate(hDevice, desc, phEventPool);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventPoolDestroy(
        xe_event_pool_handle_t hEventPool               ///< [in] handle of event pool object to destroy
    ){
    // Check parameters
    if( nullptr == hEventPool ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeEventPoolDestroy(hEventPool);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventCreate(
        xe_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        const xe_event_desc_t* desc,                    ///< [in] pointer to event descriptor
        xe_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    ){
    // Check parameters
    if( nullptr == hEventPool ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_EVENT_DESC_VERSION_CURRENT < desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_layer::context.xeapi->xeEventCreate(hEventPool, desc, phEvent);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventDestroy(
        xe_event_handle_t hEvent                        ///< [in] handle of event object to destroy
    ){
    // Check parameters
    if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeEventDestroy(hEvent);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventPoolGetIpcHandle(
        xe_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
        xe_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
    ){
    // Check parameters
    if( nullptr == hEventPool ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phIpc ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeEventPoolGetIpcHandle(hEventPool, phIpc);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventPoolOpenIpcHandle(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC event pool handle
        xe_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event handle
        xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hIpc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phEventPool ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeEventPoolOpenIpcHandle(hDevice, hIpc, phEventPool);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventPoolCloseIpcHandle(
        xe_event_pool_handle_t hEventPool               ///< [in] handle of event pool object
    ){
    // Check parameters
    if( nullptr == hEventPool ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeEventPoolCloseIpcHandle(hEventPool);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendSignalEvent(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListAppendSignalEvent(hCommandList, hEvent);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendWaitOnEvents(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
        xe_event_handle_t* phEvents                     ///< [in] handle of the events to wait on before continuing
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phEvents ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListAppendWaitOnEvents(hCommandList, numEvents, phEvents);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventHostSignal(
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    // Check parameters
    if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeEventHostSignal(hEvent);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventHostSynchronize(
        xe_event_handle_t hEvent,                       ///< [in] handle of the event
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                        ///< returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::xeEventQueryStatus;
                                                        ///< if MAX_UINT32, then function will not return until complete or device
                                                        ///< is lost.
    ){
    // Check parameters
    if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeEventHostSynchronize(hEvent, timeout);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventQueryStatus(
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    // Check parameters
    if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeEventQueryStatus(hEvent);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendEventReset(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListAppendEventReset(hCommandList, hEvent);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventReset(
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    // Check parameters
    if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeEventReset(hEvent);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFenceCreate(
        xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
        const xe_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
        xe_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
    ){
    // Check parameters
    if( nullptr == hCommandQueue ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phFence ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_FENCE_DESC_VERSION_CURRENT < desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_layer::context.xeapi->xeFenceCreate(hCommandQueue, desc, phFence);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFenceDestroy(
        xe_fence_handle_t hFence                        ///< [in] handle of fence object to destroy
    ){
    // Check parameters
    if( nullptr == hFence ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeFenceDestroy(hFence);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFenceHostSynchronize(
        xe_fence_handle_t hFence,                       ///< [in] handle of the fence
        uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                        ///< returning ::XE_RESULT_SUCCESS or ::XE_RESULT_NOT_READY;
                                                        ///< if zero, then operates exactly like ::xeFenceQueryStatus;
                                                        ///< if MAX_UINT32, then function will not return until complete or device
                                                        ///< is lost.
    ){
    // Check parameters
    if( nullptr == hFence ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeFenceHostSynchronize(hFence, timeout);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFenceQueryStatus(
        xe_fence_handle_t hFence                        ///< [in] handle of the fence
    ){
    // Check parameters
    if( nullptr == hFence ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeFenceQueryStatus(hFence);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFenceReset(
        xe_fence_handle_t hFence                        ///< [in] handle of the fence
    ){
    // Check parameters
    if( nullptr == hFence ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeFenceReset(hFence);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeImageGetProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        xe_image_properties_t* pImageProperties         ///< [out] pointer to image properties
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pImageProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_IMAGE_DESC_VERSION_CURRENT < desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_layer::context.xeapi->xeImageGetProperties(hDevice, desc, pImageProperties);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeImageCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        xe_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phImage ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_IMAGE_DESC_VERSION_CURRENT < desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_layer::context.xeapi->xeImageCreate(hDevice, desc, phImage);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeImageDestroy(
        xe_image_handle_t hImage                        ///< [in] handle of image object to destroy
    ){
    // Check parameters
    if( nullptr == hImage ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeImageDestroy(hImage);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeSharedMemAlloc(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_device_mem_alloc_flag_t device_flags,        ///< [in] flags specifying additional device allocation controls
        xe_host_mem_alloc_flag_t host_flags,            ///< [in] flags specifying additional host allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** ptr                                      ///< [out] pointer to shared allocation
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeSharedMemAlloc(hDevice, device_flags, host_flags, size, alignment, ptr);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeMemAlloc(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_device_mem_alloc_flag_t flags,               ///< [in] flags specifying additional allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** ptr                                      ///< [out] pointer to device allocation
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeMemAlloc(hDevice, flags, size, alignment, ptr);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeHostMemAlloc(
        xe_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** ptr                                      ///< [out] pointer to host allocation
    ){
    // Check parameters
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeHostMemAlloc(flags, size, alignment, ptr);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeMemFree(
        const void* ptr                                 ///< [in] pointer to memory to free
    ){
    // Check parameters
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeMemFree(ptr);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeMemGetProperties(
        const void* ptr,                                ///< [in] Pointer to query
        xe_memory_allocation_properties_t* pMemProperties   ///< [out] Query result for memory allocation properties
    ){
    // Check parameters
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pMemProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeMemGetProperties(ptr, pMemProperties);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeMemGetAddressRange(
        const void* ptr,                                ///< [in] Pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
    ){
    // Check parameters
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeMemGetAddressRange(ptr, pBase, pSize);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeIpcGetMemHandle(
        const void* ptr,                                ///< [in] Pointer to the device memory allocation
        xe_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    ){
    // Check parameters
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pIpcHandle ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeIpcGetMemHandle(ptr, pIpcHandle);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeIpcOpenMemHandle(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
        xe_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
        xe_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
        void** ptr                                      ///< [out] pointer to device allocation in this process
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == handle ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeIpcOpenMemHandle(hDevice, handle, flags, ptr);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeIpcCloseMemHandle(
        const void* ptr                                 ///< [in] pointer to device allocation in this process
    ){
    // Check parameters
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeIpcCloseMemHandle(ptr);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeModuleCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_module_desc_t* pDesc,                  ///< [in] pointer to module descriptor
        xe_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
        xe_module_build_log_handle_t* phBuildLog        ///< [in,out][optional] pointer to handle of module's build log.
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pDesc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phModule ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_MODULE_DESC_VERSION_CURRENT < pDesc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_layer::context.xeapi->xeModuleCreate(hDevice, pDesc, phModule, phBuildLog);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeModuleDestroy(
        xe_module_handle_t hModule                      ///< [in] handle of the module
    ){
    // Check parameters
    if( nullptr == hModule ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeModuleDestroy(hModule);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeModuleBuildLogDestroy(
        xe_module_build_log_handle_t hModuleBuildLog    ///< [in] handle of the module build log object.
    ){
    // Check parameters
    if( nullptr == hModuleBuildLog ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeModuleBuildLogDestroy(hModuleBuildLog);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeModuleBuildLogGetString(
        xe_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
        size_t* pSize,                                  ///< [in,out] size of build log string.
        char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
    ){
    // Check parameters
    if( nullptr == hModuleBuildLog ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pSize ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeModuleBuildLogGetString(hModuleBuildLog, pSize, pBuildLog);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeModuleGetNativeBinary(
        xe_module_handle_t hModule,                     ///< [in] handle of the device
        size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
        uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
    ){
    // Check parameters
    if( nullptr == hModule ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pSize ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeModuleGetNativeBinary(hModule, pSize, pModuleNativeBinary);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeModuleGetGlobalPointer(
        xe_module_handle_t hModule,                     ///< [in] handle of the device
        const char* pGlobalName,                        ///< [in] name of function in global
        void** pPtr                                     ///< [out] device visible pointer
    ){
    // Check parameters
    if( nullptr == hModule ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pGlobalName ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pPtr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeModuleGetGlobalPointer(hModule, pGlobalName, pPtr);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFunctionCreate(
        xe_module_handle_t hModule,                     ///< [in] handle of the module
        const xe_function_desc_t* pDesc,                ///< [in] pointer to function descriptor
        xe_function_handle_t* phFunction                ///< [out] handle of the Function object
    ){
    // Check parameters
    if( nullptr == hModule ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pDesc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phFunction ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_FUNCTION_DESC_VERSION_CURRENT < pDesc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_layer::context.xeapi->xeFunctionCreate(hModule, pDesc, phFunction);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFunctionDestroy(
        xe_function_handle_t hFunction                  ///< [in] handle of the function object
    ){
    // Check parameters
    if( nullptr == hFunction ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeFunctionDestroy(hFunction);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeModuleGetFunctionPointer(
        xe_module_handle_t hModule,                     ///< [in] handle of the module
        const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
        void** pfnFunction                              ///< [out] pointer to function.
    ){
    // Check parameters
    if( nullptr == hModule ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pFunctionName ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pfnFunction ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeModuleGetFunctionPointer(hModule, pFunctionName, pfnFunction);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFunctionSetGroupSize(
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this function.
        uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this function.
        uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this function.
    ){
    // Check parameters
    if( nullptr == hFunction ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeFunctionSetGroupSize(hFunction, groupSizeX, groupSizeY, groupSizeZ);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFunctionSuggestGroupSize(
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        uint32_t globalSizeX,                           ///< [in] global width for X dimension.
        uint32_t globalSizeY,                           ///< [in] global width for Y dimension.
        uint32_t globalSizeZ,                           ///< [in] global width for Z dimension.
        uint32_t* groupSizeX,                           ///< [out] recommended size of group for X dimension.
        uint32_t* groupSizeY,                           ///< [out] recommended size of group for Y dimension.
        uint32_t* groupSizeZ                            ///< [out] recommended size of group for Z dimension.
    ){
    // Check parameters
    if( nullptr == hFunction ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == groupSizeX ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == groupSizeY ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == groupSizeZ ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeFunctionSuggestGroupSize(hFunction, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFunctionSetArgumentValue(
        xe_function_handle_t hFunction,                 ///< [in,out] handle of the function args object.
        uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
        size_t argSize,                                 ///< [in] size of argument type
        const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                        ///< null then argument value is considered null.
    ){
    // Check parameters
    if( nullptr == hFunction ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeFunctionSetArgumentValue(hFunction, argIndex, argSize, pArgValue);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFunctionSetAttribute(
        xe_function_handle_t hFunction,                 ///< [in,out] handle of the function.
        xe_function_set_attribute_t attr,               ///< [in] attribute to set
        uint32_t value                                  ///< [in] attribute value to set
    ){
    // Check parameters
    if( nullptr == hFunction ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeFunctionSetAttribute(hFunction, attr, value);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFunctionGetAttribute(
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        xe_function_get_attribute_t attr,               ///< [in] attribute to query
        uint32_t* pValue                                ///< [out] returned attribute value
    ){
    // Check parameters
    if( nullptr == hFunction ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pValue ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeFunctionGetAttribute(hFunction, attr, pValue);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendLaunchFunction(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        const xe_thread_group_dimensions_t* pLaunchFuncArgs,///< [in] launch function arguments.
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before launching
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hFunction ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pLaunchFuncArgs ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListAppendLaunchFunction(hCommandList, hFunction, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendLaunchFunctionIndirect(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        const xe_thread_group_dimensions_t* pLaunchArgumentsBuffer, ///< [in] pointer to device buffer that will contain launch arguments
        xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
        uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
        xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before launching
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hFunction ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pLaunchArgumentsBuffer ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListAppendLaunchFunctionIndirect(hCommandList, hFunction, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendLaunchMultipleFunctionsIndirect(
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
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phFunctions ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pNumLaunchArguments ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pLaunchArgumentsBuffer ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListAppendLaunchMultipleFunctionsIndirect(hCommandList, numFunctions, phFunctions, pNumLaunchArguments, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendLaunchHostFunction(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_host_pfn_t pfnHostFunc,                      ///< [in] pointer to host function.
        void* pUserData                                 ///< [in] pointer to user data to pass to host function.
    ){
    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pUserData ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeCommandListAppendLaunchHostFunction(hCommandList, pfnHostFunc, pUserData);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceMakeMemoryResident(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to make resident
        size_t size                                     ///< [in] size in bytes to make resident
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeDeviceMakeMemoryResident(hDevice, ptr, size);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceEvictMemory(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to evict
        size_t size                                     ///< [in] size in bytes to evict
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeDeviceEvictMemory(hDevice, ptr, size);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceMakeImageResident(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_image_handle_t hImage                        ///< [in] handle of image to make resident
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hImage ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeDeviceMakeImageResident(hDevice, hImage);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceEvictImage(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_image_handle_t hImage                        ///< [in] handle of image to make evict
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hImage ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeDeviceEvictImage(hDevice, hImage);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeSamplerCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_sampler_desc_t* pDesc,                 ///< [in] pointer to sampler descriptor
        xe_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
    ){
    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pDesc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phSampler ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_SAMPLER_DESC_VERSION_CURRENT < pDesc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_layer::context.xeapi->xeSamplerCreate(hDevice, pDesc, phSampler);
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeSamplerDestroy(
        xe_sampler_handle_t hSampler                    ///< [in] handle of the sampler
    ){
    // Check parameters
    if( nullptr == hSampler ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_layer::context.xeapi->xeSamplerDestroy(hSampler);
}

#if defined(__cplusplus)
};
#endif
