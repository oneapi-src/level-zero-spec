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
* DO NOT EDIT: generated from /scripts/templates/layer_val.cpp.mako
* @endcond
*
******************************************************************************/
#include "xe_api.h"
#include "layer.h"

xe_apitable_t xe_apitable = {};

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercepts function pointer table for loaded driver
bool xeIntercept(
    xe_apitable_t* original ) ///< [in] pointer to table of xe API function pointers
{
    if(nullptr == original)
        return false;

    if( nullptr == original->pfnCommandListAppendBarrier )
        return false;
    xe_apitable.pfnCommandListAppendBarrier                             = original->pfnCommandListAppendBarrier;
    original->pfnCommandListAppendBarrier                               = xeCommandListAppendBarrier;

    if( nullptr == original->pfnCommandListAppendMemoryRangesBarrier )
        return false;
    xe_apitable.pfnCommandListAppendMemoryRangesBarrier                 = original->pfnCommandListAppendMemoryRangesBarrier;
    original->pfnCommandListAppendMemoryRangesBarrier                   = xeCommandListAppendMemoryRangesBarrier;

    if( nullptr == original->pfnDeviceSystemBarrier )
        return false;
    xe_apitable.pfnDeviceSystemBarrier                                  = original->pfnDeviceSystemBarrier;
    original->pfnDeviceSystemBarrier                                    = xeDeviceSystemBarrier;

    #if XE_ENABLE_OCL_INTEROP
    if( nullptr == original->pfnDeviceRegisterCLMemory )
        return false;
    xe_apitable.pfnDeviceRegisterCLMemory                               = original->pfnDeviceRegisterCLMemory;
    original->pfnDeviceRegisterCLMemory                                 = xeDeviceRegisterCLMemory;
    #endif // XE_ENABLE_OCL_INTEROP

    #if XE_ENABLE_OCL_INTEROP
    if( nullptr == original->pfnDeviceRegisterCLProgram )
        return false;
    xe_apitable.pfnDeviceRegisterCLProgram                              = original->pfnDeviceRegisterCLProgram;
    original->pfnDeviceRegisterCLProgram                                = xeDeviceRegisterCLProgram;
    #endif // XE_ENABLE_OCL_INTEROP

    #if XE_ENABLE_OCL_INTEROP
    if( nullptr == original->pfnDeviceRegisterCLCommandQueue )
        return false;
    xe_apitable.pfnDeviceRegisterCLCommandQueue                         = original->pfnDeviceRegisterCLCommandQueue;
    original->pfnDeviceRegisterCLCommandQueue                           = xeDeviceRegisterCLCommandQueue;
    #endif // XE_ENABLE_OCL_INTEROP

    if( nullptr == original->pfnCommandListCreate )
        return false;
    xe_apitable.pfnCommandListCreate                                    = original->pfnCommandListCreate;
    original->pfnCommandListCreate                                      = xeCommandListCreate;

    if( nullptr == original->pfnCommandListCreateImmediate )
        return false;
    xe_apitable.pfnCommandListCreateImmediate                           = original->pfnCommandListCreateImmediate;
    original->pfnCommandListCreateImmediate                             = xeCommandListCreateImmediate;

    if( nullptr == original->pfnCommandListDestroy )
        return false;
    xe_apitable.pfnCommandListDestroy                                   = original->pfnCommandListDestroy;
    original->pfnCommandListDestroy                                     = xeCommandListDestroy;

    if( nullptr == original->pfnCommandListClose )
        return false;
    xe_apitable.pfnCommandListClose                                     = original->pfnCommandListClose;
    original->pfnCommandListClose                                       = xeCommandListClose;

    if( nullptr == original->pfnCommandListReset )
        return false;
    xe_apitable.pfnCommandListReset                                     = original->pfnCommandListReset;
    original->pfnCommandListReset                                       = xeCommandListReset;

    if( nullptr == original->pfnCommandListSetParameter )
        return false;
    xe_apitable.pfnCommandListSetParameter                              = original->pfnCommandListSetParameter;
    original->pfnCommandListSetParameter                                = xeCommandListSetParameter;

    if( nullptr == original->pfnCommandListGetParameter )
        return false;
    xe_apitable.pfnCommandListGetParameter                              = original->pfnCommandListGetParameter;
    original->pfnCommandListGetParameter                                = xeCommandListGetParameter;

    if( nullptr == original->pfnCommandListResetParameters )
        return false;
    xe_apitable.pfnCommandListResetParameters                           = original->pfnCommandListResetParameters;
    original->pfnCommandListResetParameters                             = xeCommandListResetParameters;

    if( nullptr == original->pfnCommandListReserveSpace )
        return false;
    xe_apitable.pfnCommandListReserveSpace                              = original->pfnCommandListReserveSpace;
    original->pfnCommandListReserveSpace                                = xeCommandListReserveSpace;

    if( nullptr == original->pfnCommandQueueCreate )
        return false;
    xe_apitable.pfnCommandQueueCreate                                   = original->pfnCommandQueueCreate;
    original->pfnCommandQueueCreate                                     = xeCommandQueueCreate;

    if( nullptr == original->pfnCommandQueueDestroy )
        return false;
    xe_apitable.pfnCommandQueueDestroy                                  = original->pfnCommandQueueDestroy;
    original->pfnCommandQueueDestroy                                    = xeCommandQueueDestroy;

    if( nullptr == original->pfnCommandQueueExecuteCommandLists )
        return false;
    xe_apitable.pfnCommandQueueExecuteCommandLists                      = original->pfnCommandQueueExecuteCommandLists;
    original->pfnCommandQueueExecuteCommandLists                        = xeCommandQueueExecuteCommandLists;

    if( nullptr == original->pfnCommandQueueSynchronize )
        return false;
    xe_apitable.pfnCommandQueueSynchronize                              = original->pfnCommandQueueSynchronize;
    original->pfnCommandQueueSynchronize                                = xeCommandQueueSynchronize;

    if( nullptr == original->pfnCommandListAppendMemoryCopy )
        return false;
    xe_apitable.pfnCommandListAppendMemoryCopy                          = original->pfnCommandListAppendMemoryCopy;
    original->pfnCommandListAppendMemoryCopy                            = xeCommandListAppendMemoryCopy;

    if( nullptr == original->pfnCommandListAppendMemorySet )
        return false;
    xe_apitable.pfnCommandListAppendMemorySet                           = original->pfnCommandListAppendMemorySet;
    original->pfnCommandListAppendMemorySet                             = xeCommandListAppendMemorySet;

    if( nullptr == original->pfnCommandListAppendImageCopy )
        return false;
    xe_apitable.pfnCommandListAppendImageCopy                           = original->pfnCommandListAppendImageCopy;
    original->pfnCommandListAppendImageCopy                             = xeCommandListAppendImageCopy;

    if( nullptr == original->pfnCommandListAppendImageCopyRegion )
        return false;
    xe_apitable.pfnCommandListAppendImageCopyRegion                     = original->pfnCommandListAppendImageCopyRegion;
    original->pfnCommandListAppendImageCopyRegion                       = xeCommandListAppendImageCopyRegion;

    if( nullptr == original->pfnCommandListAppendImageCopyToMemory )
        return false;
    xe_apitable.pfnCommandListAppendImageCopyToMemory                   = original->pfnCommandListAppendImageCopyToMemory;
    original->pfnCommandListAppendImageCopyToMemory                     = xeCommandListAppendImageCopyToMemory;

    if( nullptr == original->pfnCommandListAppendImageCopyFromMemory )
        return false;
    xe_apitable.pfnCommandListAppendImageCopyFromMemory                 = original->pfnCommandListAppendImageCopyFromMemory;
    original->pfnCommandListAppendImageCopyFromMemory                   = xeCommandListAppendImageCopyFromMemory;

    if( nullptr == original->pfnCommandListAppendMemoryPrefetch )
        return false;
    xe_apitable.pfnCommandListAppendMemoryPrefetch                      = original->pfnCommandListAppendMemoryPrefetch;
    original->pfnCommandListAppendMemoryPrefetch                        = xeCommandListAppendMemoryPrefetch;

    if( nullptr == original->pfnCommandListAppendMemAdvise )
        return false;
    xe_apitable.pfnCommandListAppendMemAdvise                           = original->pfnCommandListAppendMemAdvise;
    original->pfnCommandListAppendMemAdvise                             = xeCommandListAppendMemAdvise;

    if( nullptr == original->pfnDeviceGetCount )
        return false;
    xe_apitable.pfnDeviceGetCount                                       = original->pfnDeviceGetCount;
    original->pfnDeviceGetCount                                         = xeDeviceGetCount;

    if( nullptr == original->pfnDeviceGet )
        return false;
    xe_apitable.pfnDeviceGet                                            = original->pfnDeviceGet;
    original->pfnDeviceGet                                              = xeDeviceGet;

    if( nullptr == original->pfnDeviceGetSubDevice )
        return false;
    xe_apitable.pfnDeviceGetSubDevice                                   = original->pfnDeviceGetSubDevice;
    original->pfnDeviceGetSubDevice                                     = xeDeviceGetSubDevice;

    if( nullptr == original->pfnDeviceGetApiVersion )
        return false;
    xe_apitable.pfnDeviceGetApiVersion                                  = original->pfnDeviceGetApiVersion;
    original->pfnDeviceGetApiVersion                                    = xeDeviceGetApiVersion;

    if( nullptr == original->pfnDeviceGetProperties )
        return false;
    xe_apitable.pfnDeviceGetProperties                                  = original->pfnDeviceGetProperties;
    original->pfnDeviceGetProperties                                    = xeDeviceGetProperties;

    if( nullptr == original->pfnDeviceGetComputeProperties )
        return false;
    xe_apitable.pfnDeviceGetComputeProperties                           = original->pfnDeviceGetComputeProperties;
    original->pfnDeviceGetComputeProperties                             = xeDeviceGetComputeProperties;

    if( nullptr == original->pfnDeviceGetMemoryProperties )
        return false;
    xe_apitable.pfnDeviceGetMemoryProperties                            = original->pfnDeviceGetMemoryProperties;
    original->pfnDeviceGetMemoryProperties                              = xeDeviceGetMemoryProperties;

    if( nullptr == original->pfnDeviceGetP2PProperties )
        return false;
    xe_apitable.pfnDeviceGetP2PProperties                               = original->pfnDeviceGetP2PProperties;
    original->pfnDeviceGetP2PProperties                                 = xeDeviceGetP2PProperties;

    if( nullptr == original->pfnDeviceCanAccessPeer )
        return false;
    xe_apitable.pfnDeviceCanAccessPeer                                  = original->pfnDeviceCanAccessPeer;
    original->pfnDeviceCanAccessPeer                                    = xeDeviceCanAccessPeer;

    if( nullptr == original->pfnDeviceSetIntermediateCacheConfig )
        return false;
    xe_apitable.pfnDeviceSetIntermediateCacheConfig                     = original->pfnDeviceSetIntermediateCacheConfig;
    original->pfnDeviceSetIntermediateCacheConfig                       = xeDeviceSetIntermediateCacheConfig;

    if( nullptr == original->pfnDeviceSetLastLevelCacheConfig )
        return false;
    xe_apitable.pfnDeviceSetLastLevelCacheConfig                        = original->pfnDeviceSetLastLevelCacheConfig;
    original->pfnDeviceSetLastLevelCacheConfig                          = xeDeviceSetLastLevelCacheConfig;

    if( nullptr == original->pfnInit )
        return false;
    xe_apitable.pfnInit                                                 = original->pfnInit;
    original->pfnInit                                                   = xeInit;

    if( nullptr == original->pfnGetDriverVersion )
        return false;
    xe_apitable.pfnGetDriverVersion                                     = original->pfnGetDriverVersion;
    original->pfnGetDriverVersion                                       = xeGetDriverVersion;

    if( nullptr == original->pfnEventPoolCreate )
        return false;
    xe_apitable.pfnEventPoolCreate                                      = original->pfnEventPoolCreate;
    original->pfnEventPoolCreate                                        = xeEventPoolCreate;

    if( nullptr == original->pfnEventPoolDestroy )
        return false;
    xe_apitable.pfnEventPoolDestroy                                     = original->pfnEventPoolDestroy;
    original->pfnEventPoolDestroy                                       = xeEventPoolDestroy;

    if( nullptr == original->pfnEventCreate )
        return false;
    xe_apitable.pfnEventCreate                                          = original->pfnEventCreate;
    original->pfnEventCreate                                            = xeEventCreate;

    if( nullptr == original->pfnEventDestroy )
        return false;
    xe_apitable.pfnEventDestroy                                         = original->pfnEventDestroy;
    original->pfnEventDestroy                                           = xeEventDestroy;

    if( nullptr == original->pfnEventPoolGetIpcHandle )
        return false;
    xe_apitable.pfnEventPoolGetIpcHandle                                = original->pfnEventPoolGetIpcHandle;
    original->pfnEventPoolGetIpcHandle                                  = xeEventPoolGetIpcHandle;

    if( nullptr == original->pfnEventPoolOpenIpcHandle )
        return false;
    xe_apitable.pfnEventPoolOpenIpcHandle                               = original->pfnEventPoolOpenIpcHandle;
    original->pfnEventPoolOpenIpcHandle                                 = xeEventPoolOpenIpcHandle;

    if( nullptr == original->pfnEventPoolCloseIpcHandle )
        return false;
    xe_apitable.pfnEventPoolCloseIpcHandle                              = original->pfnEventPoolCloseIpcHandle;
    original->pfnEventPoolCloseIpcHandle                                = xeEventPoolCloseIpcHandle;

    if( nullptr == original->pfnCommandListAppendSignalEvent )
        return false;
    xe_apitable.pfnCommandListAppendSignalEvent                         = original->pfnCommandListAppendSignalEvent;
    original->pfnCommandListAppendSignalEvent                           = xeCommandListAppendSignalEvent;

    if( nullptr == original->pfnCommandListAppendWaitOnEvents )
        return false;
    xe_apitable.pfnCommandListAppendWaitOnEvents                        = original->pfnCommandListAppendWaitOnEvents;
    original->pfnCommandListAppendWaitOnEvents                          = xeCommandListAppendWaitOnEvents;

    if( nullptr == original->pfnEventHostSignal )
        return false;
    xe_apitable.pfnEventHostSignal                                      = original->pfnEventHostSignal;
    original->pfnEventHostSignal                                        = xeEventHostSignal;

    if( nullptr == original->pfnEventHostSynchronize )
        return false;
    xe_apitable.pfnEventHostSynchronize                                 = original->pfnEventHostSynchronize;
    original->pfnEventHostSynchronize                                   = xeEventHostSynchronize;

    if( nullptr == original->pfnEventQueryStatus )
        return false;
    xe_apitable.pfnEventQueryStatus                                     = original->pfnEventQueryStatus;
    original->pfnEventQueryStatus                                       = xeEventQueryStatus;

    if( nullptr == original->pfnCommandListAppendEventReset )
        return false;
    xe_apitable.pfnCommandListAppendEventReset                          = original->pfnCommandListAppendEventReset;
    original->pfnCommandListAppendEventReset                            = xeCommandListAppendEventReset;

    if( nullptr == original->pfnEventReset )
        return false;
    xe_apitable.pfnEventReset                                           = original->pfnEventReset;
    original->pfnEventReset                                             = xeEventReset;

    if( nullptr == original->pfnFenceCreate )
        return false;
    xe_apitable.pfnFenceCreate                                          = original->pfnFenceCreate;
    original->pfnFenceCreate                                            = xeFenceCreate;

    if( nullptr == original->pfnFenceDestroy )
        return false;
    xe_apitable.pfnFenceDestroy                                         = original->pfnFenceDestroy;
    original->pfnFenceDestroy                                           = xeFenceDestroy;

    if( nullptr == original->pfnFenceHostSynchronize )
        return false;
    xe_apitable.pfnFenceHostSynchronize                                 = original->pfnFenceHostSynchronize;
    original->pfnFenceHostSynchronize                                   = xeFenceHostSynchronize;

    if( nullptr == original->pfnFenceQueryStatus )
        return false;
    xe_apitable.pfnFenceQueryStatus                                     = original->pfnFenceQueryStatus;
    original->pfnFenceQueryStatus                                       = xeFenceQueryStatus;

    if( nullptr == original->pfnFenceReset )
        return false;
    xe_apitable.pfnFenceReset                                           = original->pfnFenceReset;
    original->pfnFenceReset                                             = xeFenceReset;

    if( nullptr == original->pfnImageGetProperties )
        return false;
    xe_apitable.pfnImageGetProperties                                   = original->pfnImageGetProperties;
    original->pfnImageGetProperties                                     = xeImageGetProperties;

    if( nullptr == original->pfnImageCreate )
        return false;
    xe_apitable.pfnImageCreate                                          = original->pfnImageCreate;
    original->pfnImageCreate                                            = xeImageCreate;

    if( nullptr == original->pfnImageDestroy )
        return false;
    xe_apitable.pfnImageDestroy                                         = original->pfnImageDestroy;
    original->pfnImageDestroy                                           = xeImageDestroy;

    if( nullptr == original->pfnSharedMemAlloc )
        return false;
    xe_apitable.pfnSharedMemAlloc                                       = original->pfnSharedMemAlloc;
    original->pfnSharedMemAlloc                                         = xeSharedMemAlloc;

    if( nullptr == original->pfnMemAlloc )
        return false;
    xe_apitable.pfnMemAlloc                                             = original->pfnMemAlloc;
    original->pfnMemAlloc                                               = xeMemAlloc;

    if( nullptr == original->pfnHostMemAlloc )
        return false;
    xe_apitable.pfnHostMemAlloc                                         = original->pfnHostMemAlloc;
    original->pfnHostMemAlloc                                           = xeHostMemAlloc;

    if( nullptr == original->pfnMemFree )
        return false;
    xe_apitable.pfnMemFree                                              = original->pfnMemFree;
    original->pfnMemFree                                                = xeMemFree;

    if( nullptr == original->pfnMemGetProperties )
        return false;
    xe_apitable.pfnMemGetProperties                                     = original->pfnMemGetProperties;
    original->pfnMemGetProperties                                       = xeMemGetProperties;

    if( nullptr == original->pfnMemGetAddressRange )
        return false;
    xe_apitable.pfnMemGetAddressRange                                   = original->pfnMemGetAddressRange;
    original->pfnMemGetAddressRange                                     = xeMemGetAddressRange;

    if( nullptr == original->pfnIpcGetMemHandle )
        return false;
    xe_apitable.pfnIpcGetMemHandle                                      = original->pfnIpcGetMemHandle;
    original->pfnIpcGetMemHandle                                        = xeIpcGetMemHandle;

    if( nullptr == original->pfnIpcOpenMemHandle )
        return false;
    xe_apitable.pfnIpcOpenMemHandle                                     = original->pfnIpcOpenMemHandle;
    original->pfnIpcOpenMemHandle                                       = xeIpcOpenMemHandle;

    if( nullptr == original->pfnIpcCloseMemHandle )
        return false;
    xe_apitable.pfnIpcCloseMemHandle                                    = original->pfnIpcCloseMemHandle;
    original->pfnIpcCloseMemHandle                                      = xeIpcCloseMemHandle;

    if( nullptr == original->pfnModuleCreate )
        return false;
    xe_apitable.pfnModuleCreate                                         = original->pfnModuleCreate;
    original->pfnModuleCreate                                           = xeModuleCreate;

    if( nullptr == original->pfnModuleDestroy )
        return false;
    xe_apitable.pfnModuleDestroy                                        = original->pfnModuleDestroy;
    original->pfnModuleDestroy                                          = xeModuleDestroy;

    if( nullptr == original->pfnModuleBuildLogDestroy )
        return false;
    xe_apitable.pfnModuleBuildLogDestroy                                = original->pfnModuleBuildLogDestroy;
    original->pfnModuleBuildLogDestroy                                  = xeModuleBuildLogDestroy;

    if( nullptr == original->pfnModuleBuildLogGetString )
        return false;
    xe_apitable.pfnModuleBuildLogGetString                              = original->pfnModuleBuildLogGetString;
    original->pfnModuleBuildLogGetString                                = xeModuleBuildLogGetString;

    if( nullptr == original->pfnModuleGetNativeBinary )
        return false;
    xe_apitable.pfnModuleGetNativeBinary                                = original->pfnModuleGetNativeBinary;
    original->pfnModuleGetNativeBinary                                  = xeModuleGetNativeBinary;

    if( nullptr == original->pfnModuleGetGlobalPointer )
        return false;
    xe_apitable.pfnModuleGetGlobalPointer                               = original->pfnModuleGetGlobalPointer;
    original->pfnModuleGetGlobalPointer                                 = xeModuleGetGlobalPointer;

    if( nullptr == original->pfnFunctionCreate )
        return false;
    xe_apitable.pfnFunctionCreate                                       = original->pfnFunctionCreate;
    original->pfnFunctionCreate                                         = xeFunctionCreate;

    if( nullptr == original->pfnFunctionDestroy )
        return false;
    xe_apitable.pfnFunctionDestroy                                      = original->pfnFunctionDestroy;
    original->pfnFunctionDestroy                                        = xeFunctionDestroy;

    if( nullptr == original->pfnModuleGetFunctionPointer )
        return false;
    xe_apitable.pfnModuleGetFunctionPointer                             = original->pfnModuleGetFunctionPointer;
    original->pfnModuleGetFunctionPointer                               = xeModuleGetFunctionPointer;

    if( nullptr == original->pfnFunctionSetGroupSize )
        return false;
    xe_apitable.pfnFunctionSetGroupSize                                 = original->pfnFunctionSetGroupSize;
    original->pfnFunctionSetGroupSize                                   = xeFunctionSetGroupSize;

    if( nullptr == original->pfnFunctionSuggestGroupSize )
        return false;
    xe_apitable.pfnFunctionSuggestGroupSize                             = original->pfnFunctionSuggestGroupSize;
    original->pfnFunctionSuggestGroupSize                               = xeFunctionSuggestGroupSize;

    if( nullptr == original->pfnFunctionSetArgumentValue )
        return false;
    xe_apitable.pfnFunctionSetArgumentValue                             = original->pfnFunctionSetArgumentValue;
    original->pfnFunctionSetArgumentValue                               = xeFunctionSetArgumentValue;

    if( nullptr == original->pfnFunctionSetAttribute )
        return false;
    xe_apitable.pfnFunctionSetAttribute                                 = original->pfnFunctionSetAttribute;
    original->pfnFunctionSetAttribute                                   = xeFunctionSetAttribute;

    if( nullptr == original->pfnFunctionGetAttribute )
        return false;
    xe_apitable.pfnFunctionGetAttribute                                 = original->pfnFunctionGetAttribute;
    original->pfnFunctionGetAttribute                                   = xeFunctionGetAttribute;

    if( nullptr == original->pfnCommandListAppendLaunchFunction )
        return false;
    xe_apitable.pfnCommandListAppendLaunchFunction                      = original->pfnCommandListAppendLaunchFunction;
    original->pfnCommandListAppendLaunchFunction                        = xeCommandListAppendLaunchFunction;

    if( nullptr == original->pfnCommandListAppendLaunchFunctionIndirect )
        return false;
    xe_apitable.pfnCommandListAppendLaunchFunctionIndirect              = original->pfnCommandListAppendLaunchFunctionIndirect;
    original->pfnCommandListAppendLaunchFunctionIndirect                = xeCommandListAppendLaunchFunctionIndirect;

    if( nullptr == original->pfnCommandListAppendLaunchMultipleFunctionsIndirect )
        return false;
    xe_apitable.pfnCommandListAppendLaunchMultipleFunctionsIndirect     = original->pfnCommandListAppendLaunchMultipleFunctionsIndirect;
    original->pfnCommandListAppendLaunchMultipleFunctionsIndirect       = xeCommandListAppendLaunchMultipleFunctionsIndirect;

    if( nullptr == original->pfnCommandListAppendLaunchHostFunction )
        return false;
    xe_apitable.pfnCommandListAppendLaunchHostFunction                  = original->pfnCommandListAppendLaunchHostFunction;
    original->pfnCommandListAppendLaunchHostFunction                    = xeCommandListAppendLaunchHostFunction;

    if( nullptr == original->pfnDeviceMakeMemoryResident )
        return false;
    xe_apitable.pfnDeviceMakeMemoryResident                             = original->pfnDeviceMakeMemoryResident;
    original->pfnDeviceMakeMemoryResident                               = xeDeviceMakeMemoryResident;

    if( nullptr == original->pfnDeviceEvictMemory )
        return false;
    xe_apitable.pfnDeviceEvictMemory                                    = original->pfnDeviceEvictMemory;
    original->pfnDeviceEvictMemory                                      = xeDeviceEvictMemory;

    if( nullptr == original->pfnDeviceMakeImageResident )
        return false;
    xe_apitable.pfnDeviceMakeImageResident                              = original->pfnDeviceMakeImageResident;
    original->pfnDeviceMakeImageResident                                = xeDeviceMakeImageResident;

    if( nullptr == original->pfnDeviceEvictImage )
        return false;
    xe_apitable.pfnDeviceEvictImage                                     = original->pfnDeviceEvictImage;
    original->pfnDeviceEvictImage                                       = xeDeviceEvictImage;

    if( nullptr == original->pfnSamplerCreate )
        return false;
    xe_apitable.pfnSamplerCreate                                        = original->pfnSamplerCreate;
    original->pfnSamplerCreate                                          = xeSamplerCreate;

    if( nullptr == original->pfnSamplerDestroy )
        return false;
    xe_apitable.pfnSamplerDestroy                                       = original->pfnSamplerDestroy;
    original->pfnSamplerDestroy                                         = xeSamplerDestroy;

    return true;
}


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
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendBarrier )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
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
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendMemoryRangesBarrier )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pRangeSizes ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pRanges ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceSystemBarrier(
    xe_device_handle_t hDevice                      ///< [in] handle of the device
    )
{
    if( nullptr == xe_apitable.pfnDeviceSystemBarrier )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnDeviceSystemBarrier( hDevice );
}

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
xe_result_t __xecall
xeDeviceRegisterCLMemory(
    xe_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the memory
    cl_mem mem,                                     ///< [in] the OpenCL memory to register
    void** ptr                                      ///< [out] pointer to device allocation
    )
{
    if( nullptr == xe_apitable.pfnDeviceRegisterCLMemory )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnDeviceRegisterCLMemory( hDevice, context, mem, ptr );
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
    )
{
    if( nullptr == xe_apitable.pfnDeviceRegisterCLProgram )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phModule ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnDeviceRegisterCLProgram( hDevice, context, program, phModule );
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
    )
{
    if( nullptr == xe_apitable.pfnDeviceRegisterCLCommandQueue )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phCommandQueue ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnDeviceRegisterCLCommandQueue( hDevice, context, command_queue, phCommandQueue );
}
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
    xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    )
{
    if( nullptr == xe_apitable.pfnCommandListCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_COMMAND_LIST_DESC_VERSION_CURRENT < desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_apitable.pfnCommandListCreate( hDevice, desc, phCommandList );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListCreateImmediate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
    xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    )
{
    if( nullptr == xe_apitable.pfnCommandListCreateImmediate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_COMMAND_QUEUE_DESC_VERSION_CURRENT < desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_apitable.pfnCommandListCreateImmediate( hDevice, desc, phCommandList );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListDestroy(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to destroy
    )
{
    if( nullptr == xe_apitable.pfnCommandListDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListDestroy( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListClose(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
    )
{
    if( nullptr == xe_apitable.pfnCommandListClose )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListClose( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListReset(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
    )
{
    if( nullptr == xe_apitable.pfnCommandListReset )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListReset( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListSetParameter(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_command_list_parameter_t parameter,          ///< [in] parameter to change
    uint32_t value                                  ///< [in] value of attribute
    )
{
    if( nullptr == xe_apitable.pfnCommandListSetParameter )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListSetParameter( hCommandList, parameter, value );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListGetParameter(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_command_list_parameter_t parameter,          ///< [in] parameter to retrieve
    uint32_t* value                                 ///< [out] value of attribute
    )
{
    if( nullptr == xe_apitable.pfnCommandListGetParameter )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == value ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListGetParameter( hCommandList, parameter, value );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListResetParameters(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    )
{
    if( nullptr == xe_apitable.pfnCommandListResetParameters )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListResetParameters( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListReserveSpace(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    size_t size,                                    ///< [in] size (in bytes) to reserve
    void** ptr                                      ///< [out] pointer to command buffer space reserved
    )
{
    if( nullptr == xe_apitable.pfnCommandListReserveSpace )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListReserveSpace( hCommandList, size, ptr );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandQueueCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
    xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    )
{
    if( nullptr == xe_apitable.pfnCommandQueueCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phCommandQueue ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_COMMAND_QUEUE_DESC_VERSION_CURRENT < desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_apitable.pfnCommandQueueCreate( hDevice, desc, phCommandQueue );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandQueueDestroy(
    xe_command_queue_handle_t hCommandQueue         ///< [in] handle of command queue object to destroy
    )
{
    if( nullptr == xe_apitable.pfnCommandQueueDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandQueue ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandQueueDestroy( hCommandQueue );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandQueueExecuteCommandLists(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint32_t numCommandLists,                       ///< [in] number of command lists to execute
    xe_command_list_handle_t* phCommandLists,       ///< [in] list of handles of the command lists to execute
    xe_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
    )
{
    if( nullptr == xe_apitable.pfnCommandQueueExecuteCommandLists )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandQueue ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phCommandLists ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandQueueExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );
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
    )
{
    if( nullptr == xe_apitable.pfnCommandQueueSynchronize )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandQueue ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandQueueSynchronize( hCommandQueue, timeout );
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
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendMemoryCopy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == dstptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == srcptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
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
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendMemorySet )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListAppendMemorySet( hCommandList, ptr, value, size, hSignalEvent, numWaitEvents, phWaitEvents );
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
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendImageCopy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hDstImage ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hSrcImage ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListAppendImageCopy( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents );
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
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendImageCopyRegion )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hDstImage ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hSrcImage ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
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
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendImageCopyToMemory )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == dstptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hSrcImage ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
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
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendImageCopyFromMemory )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hDstImage ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == srcptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendMemoryPrefetch(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
    size_t count                                    ///< [in] size in bytes of the memory range to prefetch
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendMemoryPrefetch )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListAppendMemoryPrefetch( hCommandList, ptr, count );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendMemAdvise(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
    const void* ptr,                                ///< [in] Pointer to the start of the memory range
    size_t size,                                    ///< [in] Size in bytes of the memory range
    xe_memory_advice_t advice                       ///< [in] Memory advice for the memory range
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendMemAdvise )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceGetCount(
    uint32_t* count                                 ///< [out] number of devices available
    )
{
    if( nullptr == xe_apitable.pfnDeviceGetCount )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == count ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnDeviceGetCount( count );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceGet(
    uint32_t ordinal,                               ///< [in] The device index in the range of [0, ::xeDeviceGetCount]
    xe_device_handle_t* phDevice                    ///< [out] pointer to handle of device object created
    )
{
    if( nullptr == xe_apitable.pfnDeviceGet )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == phDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnDeviceGet( ordinal, phDevice );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceGetSubDevice(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t ordinal,                               ///< [in] ordinal of sub-device to retrieve
    xe_device_handle_t* phSubDevice                 ///< [out] pointer to handle of sub-device object.
    )
{
    if( nullptr == xe_apitable.pfnDeviceGetSubDevice )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phSubDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnDeviceGetSubDevice( hDevice, ordinal, phSubDevice );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceGetApiVersion(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_api_version_t* version                       ///< [out] api version
    )
{
    if( nullptr == xe_apitable.pfnDeviceGetApiVersion )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == version ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnDeviceGetApiVersion( hDevice, version );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceGetProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_device_properties_t* pDeviceProperties       ///< [out] query result for device properties
    )
{
    if( nullptr == xe_apitable.pfnDeviceGetProperties )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pDeviceProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnDeviceGetProperties( hDevice, pDeviceProperties );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceGetComputeProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_device_compute_properties_t* pComputeProperties  ///< [out] query result for compute properties
    )
{
    if( nullptr == xe_apitable.pfnDeviceGetComputeProperties )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pComputeProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnDeviceGetComputeProperties( hDevice, pComputeProperties );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceGetMemoryProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_device_memory_properties_t* pMemProperties   ///< [out] query result for compute properties
    )
{
    if( nullptr == xe_apitable.pfnDeviceGetMemoryProperties )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pMemProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnDeviceGetMemoryProperties( hDevice, pMemProperties );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceGetP2PProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    xe_device_p2p_properties_t* pP2PProperties      ///< [out] Peer-to-Peer properties between source and peer device
    )
{
    if( nullptr == xe_apitable.pfnDeviceGetP2PProperties )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hPeerDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pP2PProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnDeviceGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceCanAccessPeer(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    xe_bool_t* value                                ///< [out] returned access capability
    )
{
    if( nullptr == xe_apitable.pfnDeviceCanAccessPeer )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hPeerDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == value ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnDeviceCanAccessPeer( hDevice, hPeerDevice, value );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceSetIntermediateCacheConfig(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device 
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    )
{
    if( nullptr == xe_apitable.pfnDeviceSetIntermediateCacheConfig )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnDeviceSetIntermediateCacheConfig( hDevice, CacheConfig );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceSetLastLevelCacheConfig(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device 
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    )
{
    if( nullptr == xe_apitable.pfnDeviceSetLastLevelCacheConfig )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnDeviceSetLastLevelCacheConfig( hDevice, CacheConfig );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeInit(
    xe_init_flag_t flags                            ///< [in] initialization flags
    )
{
    if( nullptr == xe_apitable.pfnInit )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters

    return xe_apitable.pfnInit( flags );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeGetDriverVersion(
    uint32_t* version                               ///< [out] driver version
    )
{
    if( nullptr == xe_apitable.pfnGetDriverVersion )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == version ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnGetDriverVersion( version );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventPoolCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
    xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    )
{
    if( nullptr == xe_apitable.pfnEventPoolCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phEventPool ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_EVENT_POOL_DESC_VERSION_CURRENT < desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_apitable.pfnEventPoolCreate( hDevice, desc, phEventPool );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventPoolDestroy(
    xe_event_pool_handle_t hEventPool               ///< [in] handle of event pool object to destroy
    )
{
    if( nullptr == xe_apitable.pfnEventPoolDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hEventPool ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnEventPoolDestroy( hEventPool );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventCreate(
    xe_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
    const xe_event_desc_t* desc,                    ///< [in] pointer to event descriptor
    xe_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    )
{
    if( nullptr == xe_apitable.pfnEventCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hEventPool ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_EVENT_DESC_VERSION_CURRENT < desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_apitable.pfnEventCreate( hEventPool, desc, phEvent );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventDestroy(
    xe_event_handle_t hEvent                        ///< [in] handle of event object to destroy
    )
{
    if( nullptr == xe_apitable.pfnEventDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnEventDestroy( hEvent );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventPoolGetIpcHandle(
    xe_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
    xe_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
    )
{
    if( nullptr == xe_apitable.pfnEventPoolGetIpcHandle )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hEventPool ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phIpc ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnEventPoolGetIpcHandle( hEventPool, phIpc );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventPoolOpenIpcHandle(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC event pool handle
    xe_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event handle
    xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    )
{
    if( nullptr == xe_apitable.pfnEventPoolOpenIpcHandle )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hIpc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phEventPool ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnEventPoolOpenIpcHandle( hDevice, hIpc, phEventPool );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventPoolCloseIpcHandle(
    xe_event_pool_handle_t hEventPool               ///< [in] handle of event pool object
    )
{
    if( nullptr == xe_apitable.pfnEventPoolCloseIpcHandle )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hEventPool ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnEventPoolCloseIpcHandle( hEventPool );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendSignalEvent(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendSignalEvent )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListAppendSignalEvent( hCommandList, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendWaitOnEvents(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
    xe_event_handle_t* phEvents                     ///< [in] handle of the events to wait on before continuing
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendWaitOnEvents )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phEvents ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListAppendWaitOnEvents( hCommandList, numEvents, phEvents );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventHostSignal(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    if( nullptr == xe_apitable.pfnEventHostSignal )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnEventHostSignal( hEvent );
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
    )
{
    if( nullptr == xe_apitable.pfnEventHostSynchronize )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnEventHostSynchronize( hEvent, timeout );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventQueryStatus(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    if( nullptr == xe_apitable.pfnEventQueryStatus )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnEventQueryStatus( hEvent );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendEventReset(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendEventReset )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListAppendEventReset( hCommandList, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeEventReset(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    if( nullptr == xe_apitable.pfnEventReset )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hEvent ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnEventReset( hEvent );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFenceCreate(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
    const xe_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
    xe_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
    )
{
    if( nullptr == xe_apitable.pfnFenceCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandQueue ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phFence ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_FENCE_DESC_VERSION_CURRENT < desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_apitable.pfnFenceCreate( hCommandQueue, desc, phFence );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFenceDestroy(
    xe_fence_handle_t hFence                        ///< [in] handle of fence object to destroy
    )
{
    if( nullptr == xe_apitable.pfnFenceDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hFence ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnFenceDestroy( hFence );
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
    )
{
    if( nullptr == xe_apitable.pfnFenceHostSynchronize )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hFence ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnFenceHostSynchronize( hFence, timeout );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFenceQueryStatus(
    xe_fence_handle_t hFence                        ///< [in] handle of the fence
    )
{
    if( nullptr == xe_apitable.pfnFenceQueryStatus )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hFence ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnFenceQueryStatus( hFence );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFenceReset(
    xe_fence_handle_t hFence                        ///< [in] handle of the fence
    )
{
    if( nullptr == xe_apitable.pfnFenceReset )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hFence ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnFenceReset( hFence );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeImageGetProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    xe_image_properties_t* pImageProperties         ///< [out] pointer to image properties
    )
{
    if( nullptr == xe_apitable.pfnImageGetProperties )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pImageProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_IMAGE_DESC_VERSION_CURRENT < desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_apitable.pfnImageGetProperties( hDevice, desc, pImageProperties );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeImageCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    xe_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
    )
{
    if( nullptr == xe_apitable.pfnImageCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == desc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phImage ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_IMAGE_DESC_VERSION_CURRENT < desc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_apitable.pfnImageCreate( hDevice, desc, phImage );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeImageDestroy(
    xe_image_handle_t hImage                        ///< [in] handle of image object to destroy
    )
{
    if( nullptr == xe_apitable.pfnImageDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hImage ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnImageDestroy( hImage );
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
    )
{
    if( nullptr == xe_apitable.pfnSharedMemAlloc )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnSharedMemAlloc( hDevice, device_flags, host_flags, size, alignment, ptr );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeMemAlloc(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_mem_alloc_flag_t flags,               ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to device allocation
    )
{
    if( nullptr == xe_apitable.pfnMemAlloc )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnMemAlloc( hDevice, flags, size, alignment, ptr );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeHostMemAlloc(
    xe_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to host allocation
    )
{
    if( nullptr == xe_apitable.pfnHostMemAlloc )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnHostMemAlloc( flags, size, alignment, ptr );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeMemFree(
    const void* ptr                                 ///< [in] pointer to memory to free
    )
{
    if( nullptr == xe_apitable.pfnMemFree )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnMemFree( ptr );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeMemGetProperties(
    const void* ptr,                                ///< [in] Pointer to query
    xe_memory_allocation_properties_t* pMemProperties   ///< [out] Query result for memory allocation properties
    )
{
    if( nullptr == xe_apitable.pfnMemGetProperties )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pMemProperties ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnMemGetProperties( ptr, pMemProperties );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeMemGetAddressRange(
    const void* ptr,                                ///< [in] Pointer to query
    void** pBase,                                   ///< [in,out][optional] base address of the allocation
    size_t* pSize                                   ///< [in,out][optional] size of the allocation
    )
{
    if( nullptr == xe_apitable.pfnMemGetAddressRange )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnMemGetAddressRange( ptr, pBase, pSize );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeIpcGetMemHandle(
    const void* ptr,                                ///< [in] Pointer to the device memory allocation
    xe_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    )
{
    if( nullptr == xe_apitable.pfnIpcGetMemHandle )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pIpcHandle ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnIpcGetMemHandle( ptr, pIpcHandle );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeIpcOpenMemHandle(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
    xe_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
    xe_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
    void** ptr                                      ///< [out] pointer to device allocation in this process
    )
{
    if( nullptr == xe_apitable.pfnIpcOpenMemHandle )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == handle ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnIpcOpenMemHandle( hDevice, handle, flags, ptr );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeIpcCloseMemHandle(
    const void* ptr                                 ///< [in] pointer to device allocation in this process
    )
{
    if( nullptr == xe_apitable.pfnIpcCloseMemHandle )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnIpcCloseMemHandle( ptr );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeModuleCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_module_desc_t* pDesc,                  ///< [in] pointer to module descriptor
    xe_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
    xe_module_build_log_handle_t* phBuildLog        ///< [in,out][optional] pointer to handle of module's build log.
    )
{
    if( nullptr == xe_apitable.pfnModuleCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pDesc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phModule ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_MODULE_DESC_VERSION_CURRENT < pDesc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_apitable.pfnModuleCreate( hDevice, pDesc, phModule, phBuildLog );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeModuleDestroy(
    xe_module_handle_t hModule                      ///< [in] handle of the module
    )
{
    if( nullptr == xe_apitable.pfnModuleDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hModule ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnModuleDestroy( hModule );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeModuleBuildLogDestroy(
    xe_module_build_log_handle_t hModuleBuildLog    ///< [in] handle of the module build log object.
    )
{
    if( nullptr == xe_apitable.pfnModuleBuildLogDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hModuleBuildLog ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnModuleBuildLogDestroy( hModuleBuildLog );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeModuleBuildLogGetString(
    xe_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
    size_t* pSize,                                  ///< [in,out] size of build log string.
    char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
    )
{
    if( nullptr == xe_apitable.pfnModuleBuildLogGetString )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hModuleBuildLog ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pSize ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnModuleBuildLogGetString( hModuleBuildLog, pSize, pBuildLog );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeModuleGetNativeBinary(
    xe_module_handle_t hModule,                     ///< [in] handle of the device
    size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
    uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
    )
{
    if( nullptr == xe_apitable.pfnModuleGetNativeBinary )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hModule ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pSize ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnModuleGetNativeBinary( hModule, pSize, pModuleNativeBinary );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeModuleGetGlobalPointer(
    xe_module_handle_t hModule,                     ///< [in] handle of the device
    const char* pGlobalName,                        ///< [in] name of function in global
    void** pPtr                                     ///< [out] device visible pointer
    )
{
    if( nullptr == xe_apitable.pfnModuleGetGlobalPointer )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hModule ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pGlobalName ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pPtr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnModuleGetGlobalPointer( hModule, pGlobalName, pPtr );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFunctionCreate(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const xe_function_desc_t* pDesc,                ///< [in] pointer to function descriptor
    xe_function_handle_t* phFunction                ///< [out] handle of the Function object
    )
{
    if( nullptr == xe_apitable.pfnFunctionCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hModule ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pDesc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phFunction ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_FUNCTION_DESC_VERSION_CURRENT < pDesc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_apitable.pfnFunctionCreate( hModule, pDesc, phFunction );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFunctionDestroy(
    xe_function_handle_t hFunction                  ///< [in] handle of the function object
    )
{
    if( nullptr == xe_apitable.pfnFunctionDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hFunction ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnFunctionDestroy( hFunction );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeModuleGetFunctionPointer(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
    void** pfnFunction                              ///< [out] pointer to function.
    )
{
    if( nullptr == xe_apitable.pfnModuleGetFunctionPointer )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hModule ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pFunctionName ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pfnFunction ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnModuleGetFunctionPointer( hModule, pFunctionName, pfnFunction );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFunctionSetGroupSize(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this function.
    uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this function.
    uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this function.
    )
{
    if( nullptr == xe_apitable.pfnFunctionSetGroupSize )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hFunction ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnFunctionSetGroupSize( hFunction, groupSizeX, groupSizeY, groupSizeZ );
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
    )
{
    if( nullptr == xe_apitable.pfnFunctionSuggestGroupSize )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hFunction ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == groupSizeX ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == groupSizeY ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == groupSizeZ ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnFunctionSuggestGroupSize( hFunction, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFunctionSetArgumentValue(
    xe_function_handle_t hFunction,                 ///< [in,out] handle of the function args object.
    uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
    size_t argSize,                                 ///< [in] size of argument type
    const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                    ///< null then argument value is considered null.
    )
{
    if( nullptr == xe_apitable.pfnFunctionSetArgumentValue )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hFunction ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnFunctionSetArgumentValue( hFunction, argIndex, argSize, pArgValue );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFunctionSetAttribute(
    xe_function_handle_t hFunction,                 ///< [in,out] handle of the function.
    xe_function_set_attribute_t attr,               ///< [in] attribute to set
    uint32_t value                                  ///< [in] attribute value to set
    )
{
    if( nullptr == xe_apitable.pfnFunctionSetAttribute )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hFunction ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnFunctionSetAttribute( hFunction, attr, value );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeFunctionGetAttribute(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    xe_function_get_attribute_t attr,               ///< [in] attribute to query
    uint32_t* pValue                                ///< [out] returned attribute value
    )
{
    if( nullptr == xe_apitable.pfnFunctionGetAttribute )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hFunction ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pValue ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnFunctionGetAttribute( hFunction, attr, pValue );
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
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendLaunchFunction )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hFunction ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pLaunchFuncArgs ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListAppendLaunchFunction( hCommandList, hFunction, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
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
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendLaunchFunctionIndirect )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hFunction ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pLaunchArgumentsBuffer ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListAppendLaunchFunctionIndirect( hCommandList, hFunction, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
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
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendLaunchMultipleFunctionsIndirect )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phFunctions ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pNumLaunchArguments ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pLaunchArgumentsBuffer ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListAppendLaunchMultipleFunctionsIndirect( hCommandList, numFunctions, phFunctions, pNumLaunchArguments, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeCommandListAppendLaunchHostFunction(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_host_pfn_t pfnHostFunc,                      ///< [in] pointer to host function.
    void* pUserData                                 ///< [in] pointer to user data to pass to host function.
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendLaunchHostFunction )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hCommandList ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pUserData ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnCommandListAppendLaunchHostFunction( hCommandList, pfnHostFunc, pUserData );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceMakeMemoryResident(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    void* ptr,                                      ///< [in] pointer to memory to make resident
    size_t size                                     ///< [in] size in bytes to make resident
    )
{
    if( nullptr == xe_apitable.pfnDeviceMakeMemoryResident )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnDeviceMakeMemoryResident( hDevice, ptr, size );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceEvictMemory(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    void* ptr,                                      ///< [in] pointer to memory to evict
    size_t size                                     ///< [in] size in bytes to evict
    )
{
    if( nullptr == xe_apitable.pfnDeviceEvictMemory )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == ptr ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnDeviceEvictMemory( hDevice, ptr, size );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceMakeImageResident(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_image_handle_t hImage                        ///< [in] handle of image to make resident
    )
{
    if( nullptr == xe_apitable.pfnDeviceMakeImageResident )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hImage ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnDeviceMakeImageResident( hDevice, hImage );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeDeviceEvictImage(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_image_handle_t hImage                        ///< [in] handle of image to make evict
    )
{
    if( nullptr == xe_apitable.pfnDeviceEvictImage )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == hImage ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnDeviceEvictImage( hDevice, hImage );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeSamplerCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_sampler_desc_t* pDesc,                 ///< [in] pointer to sampler descriptor
    xe_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
    )
{
    if( nullptr == xe_apitable.pfnSamplerCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hDevice ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == pDesc ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( nullptr == phSampler ) return XE_RESULT_ERROR_INVALID_PARAMETER;
    if( XE_SAMPLER_DESC_VERSION_CURRENT < pDesc->version ) return XE_RESULT_ERROR_UNSUPPORTED;

    return xe_apitable.pfnSamplerCreate( hDevice, pDesc, phSampler );
}

///////////////////////////////////////////////////////////////////////////////
xe_result_t __xecall
xeSamplerDestroy(
    xe_sampler_handle_t hSampler                    ///< [in] handle of the sampler
    )
{
    if( nullptr == xe_apitable.pfnSamplerDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    // Check parameters
    if( nullptr == hSampler ) return XE_RESULT_ERROR_INVALID_PARAMETER;

    return xe_apitable.pfnSamplerDestroy( hSampler );
}

#if defined(__cplusplus)
};
#endif
