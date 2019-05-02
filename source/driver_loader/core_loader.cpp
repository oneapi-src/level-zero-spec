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
* @file core_loader.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/loader.cpp.mako
* @endcond
*
******************************************************************************/
#include "xe_all.h"
#include "loader.h"

xe_apitable_t xe_apitable = {};

///////////////////////////////////////////////////////////////////////////////
/// @brief Loads function pointer table for loaded driver
bool xeLoadExports(
    void* handle )  ///< [in] driver handle
{
    xe_apitable.pfnCommandListAppendBarrier                             = (xe_pfnCommandListAppendBarrier_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendBarrier");
    if( nullptr == xe_apitable.pfnCommandListAppendBarrier )
        return false;

    xe_apitable.pfnCommandListAppendMemoryRangesBarrier                 = (xe_pfnCommandListAppendMemoryRangesBarrier_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendMemoryRangesBarrier");
    if( nullptr == xe_apitable.pfnCommandListAppendMemoryRangesBarrier )
        return false;

    xe_apitable.pfnDeviceSystemBarrier                                  = (xe_pfnDeviceSystemBarrier_t)LOAD_FUNCTION_PTR(handle, "xeDeviceSystemBarrier");
    if( nullptr == xe_apitable.pfnDeviceSystemBarrier )
        return false;

    #if XE_ENABLE_OCL_INTEROP
    xe_apitable.pfnDeviceRegisterCLMemory                               = (xe_pfnDeviceRegisterCLMemory_t)LOAD_FUNCTION_PTR(handle, "xeDeviceRegisterCLMemory");
    if( nullptr == xe_apitable.pfnDeviceRegisterCLMemory )
        return false;
    #endif // XE_ENABLE_OCL_INTEROP

    #if XE_ENABLE_OCL_INTEROP
    xe_apitable.pfnDeviceRegisterCLProgram                              = (xe_pfnDeviceRegisterCLProgram_t)LOAD_FUNCTION_PTR(handle, "xeDeviceRegisterCLProgram");
    if( nullptr == xe_apitable.pfnDeviceRegisterCLProgram )
        return false;
    #endif // XE_ENABLE_OCL_INTEROP

    #if XE_ENABLE_OCL_INTEROP
    xe_apitable.pfnDeviceRegisterCLCommandQueue                         = (xe_pfnDeviceRegisterCLCommandQueue_t)LOAD_FUNCTION_PTR(handle, "xeDeviceRegisterCLCommandQueue");
    if( nullptr == xe_apitable.pfnDeviceRegisterCLCommandQueue )
        return false;
    #endif // XE_ENABLE_OCL_INTEROP

    xe_apitable.pfnCommandListCreate                                    = (xe_pfnCommandListCreate_t)LOAD_FUNCTION_PTR(handle, "xeCommandListCreate");
    if( nullptr == xe_apitable.pfnCommandListCreate )
        return false;

    xe_apitable.pfnCommandListCreateImmediate                           = (xe_pfnCommandListCreateImmediate_t)LOAD_FUNCTION_PTR(handle, "xeCommandListCreateImmediate");
    if( nullptr == xe_apitable.pfnCommandListCreateImmediate )
        return false;

    xe_apitable.pfnCommandListDestroy                                   = (xe_pfnCommandListDestroy_t)LOAD_FUNCTION_PTR(handle, "xeCommandListDestroy");
    if( nullptr == xe_apitable.pfnCommandListDestroy )
        return false;

    xe_apitable.pfnCommandListClose                                     = (xe_pfnCommandListClose_t)LOAD_FUNCTION_PTR(handle, "xeCommandListClose");
    if( nullptr == xe_apitable.pfnCommandListClose )
        return false;

    xe_apitable.pfnCommandListReset                                     = (xe_pfnCommandListReset_t)LOAD_FUNCTION_PTR(handle, "xeCommandListReset");
    if( nullptr == xe_apitable.pfnCommandListReset )
        return false;

    xe_apitable.pfnCommandListSetParameter                              = (xe_pfnCommandListSetParameter_t)LOAD_FUNCTION_PTR(handle, "xeCommandListSetParameter");
    if( nullptr == xe_apitable.pfnCommandListSetParameter )
        return false;

    xe_apitable.pfnCommandListGetParameter                              = (xe_pfnCommandListGetParameter_t)LOAD_FUNCTION_PTR(handle, "xeCommandListGetParameter");
    if( nullptr == xe_apitable.pfnCommandListGetParameter )
        return false;

    xe_apitable.pfnCommandListResetParameters                           = (xe_pfnCommandListResetParameters_t)LOAD_FUNCTION_PTR(handle, "xeCommandListResetParameters");
    if( nullptr == xe_apitable.pfnCommandListResetParameters )
        return false;

    xe_apitable.pfnCommandListReserveSpace                              = (xe_pfnCommandListReserveSpace_t)LOAD_FUNCTION_PTR(handle, "xeCommandListReserveSpace");
    if( nullptr == xe_apitable.pfnCommandListReserveSpace )
        return false;

    xe_apitable.pfnCommandQueueCreate                                   = (xe_pfnCommandQueueCreate_t)LOAD_FUNCTION_PTR(handle, "xeCommandQueueCreate");
    if( nullptr == xe_apitable.pfnCommandQueueCreate )
        return false;

    xe_apitable.pfnCommandQueueDestroy                                  = (xe_pfnCommandQueueDestroy_t)LOAD_FUNCTION_PTR(handle, "xeCommandQueueDestroy");
    if( nullptr == xe_apitable.pfnCommandQueueDestroy )
        return false;

    xe_apitable.pfnCommandQueueExecuteCommandLists                      = (xe_pfnCommandQueueExecuteCommandLists_t)LOAD_FUNCTION_PTR(handle, "xeCommandQueueExecuteCommandLists");
    if( nullptr == xe_apitable.pfnCommandQueueExecuteCommandLists )
        return false;

    xe_apitable.pfnCommandQueueSynchronize                              = (xe_pfnCommandQueueSynchronize_t)LOAD_FUNCTION_PTR(handle, "xeCommandQueueSynchronize");
    if( nullptr == xe_apitable.pfnCommandQueueSynchronize )
        return false;

    xe_apitable.pfnCommandListAppendMemoryCopy                          = (xe_pfnCommandListAppendMemoryCopy_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendMemoryCopy");
    if( nullptr == xe_apitable.pfnCommandListAppendMemoryCopy )
        return false;

    xe_apitable.pfnCommandListAppendMemorySet                           = (xe_pfnCommandListAppendMemorySet_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendMemorySet");
    if( nullptr == xe_apitable.pfnCommandListAppendMemorySet )
        return false;

    xe_apitable.pfnCommandListAppendImageCopy                           = (xe_pfnCommandListAppendImageCopy_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendImageCopy");
    if( nullptr == xe_apitable.pfnCommandListAppendImageCopy )
        return false;

    xe_apitable.pfnCommandListAppendImageCopyRegion                     = (xe_pfnCommandListAppendImageCopyRegion_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendImageCopyRegion");
    if( nullptr == xe_apitable.pfnCommandListAppendImageCopyRegion )
        return false;

    xe_apitable.pfnCommandListAppendImageCopyToMemory                   = (xe_pfnCommandListAppendImageCopyToMemory_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendImageCopyToMemory");
    if( nullptr == xe_apitable.pfnCommandListAppendImageCopyToMemory )
        return false;

    xe_apitable.pfnCommandListAppendImageCopyFromMemory                 = (xe_pfnCommandListAppendImageCopyFromMemory_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendImageCopyFromMemory");
    if( nullptr == xe_apitable.pfnCommandListAppendImageCopyFromMemory )
        return false;

    xe_apitable.pfnCommandListAppendMemoryPrefetch                      = (xe_pfnCommandListAppendMemoryPrefetch_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendMemoryPrefetch");
    if( nullptr == xe_apitable.pfnCommandListAppendMemoryPrefetch )
        return false;

    xe_apitable.pfnCommandListAppendMemAdvise                           = (xe_pfnCommandListAppendMemAdvise_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendMemAdvise");
    if( nullptr == xe_apitable.pfnCommandListAppendMemAdvise )
        return false;

    xe_apitable.pfnDeviceGetCount                                       = (xe_pfnDeviceGetCount_t)LOAD_FUNCTION_PTR(handle, "xeDeviceGetCount");
    if( nullptr == xe_apitable.pfnDeviceGetCount )
        return false;

    xe_apitable.pfnDeviceGet                                            = (xe_pfnDeviceGet_t)LOAD_FUNCTION_PTR(handle, "xeDeviceGet");
    if( nullptr == xe_apitable.pfnDeviceGet )
        return false;

    xe_apitable.pfnDeviceGetSubDevice                                   = (xe_pfnDeviceGetSubDevice_t)LOAD_FUNCTION_PTR(handle, "xeDeviceGetSubDevice");
    if( nullptr == xe_apitable.pfnDeviceGetSubDevice )
        return false;

    xe_apitable.pfnDeviceGetApiVersion                                  = (xe_pfnDeviceGetApiVersion_t)LOAD_FUNCTION_PTR(handle, "xeDeviceGetApiVersion");
    if( nullptr == xe_apitable.pfnDeviceGetApiVersion )
        return false;

    xe_apitable.pfnDeviceGetProperties                                  = (xe_pfnDeviceGetProperties_t)LOAD_FUNCTION_PTR(handle, "xeDeviceGetProperties");
    if( nullptr == xe_apitable.pfnDeviceGetProperties )
        return false;

    xe_apitable.pfnDeviceGetComputeProperties                           = (xe_pfnDeviceGetComputeProperties_t)LOAD_FUNCTION_PTR(handle, "xeDeviceGetComputeProperties");
    if( nullptr == xe_apitable.pfnDeviceGetComputeProperties )
        return false;

    xe_apitable.pfnDeviceGetMemoryProperties                            = (xe_pfnDeviceGetMemoryProperties_t)LOAD_FUNCTION_PTR(handle, "xeDeviceGetMemoryProperties");
    if( nullptr == xe_apitable.pfnDeviceGetMemoryProperties )
        return false;

    xe_apitable.pfnDeviceGetP2PProperties                               = (xe_pfnDeviceGetP2PProperties_t)LOAD_FUNCTION_PTR(handle, "xeDeviceGetP2PProperties");
    if( nullptr == xe_apitable.pfnDeviceGetP2PProperties )
        return false;

    xe_apitable.pfnDeviceCanAccessPeer                                  = (xe_pfnDeviceCanAccessPeer_t)LOAD_FUNCTION_PTR(handle, "xeDeviceCanAccessPeer");
    if( nullptr == xe_apitable.pfnDeviceCanAccessPeer )
        return false;

    xe_apitable.pfnDeviceSetIntermediateCacheConfig                     = (xe_pfnDeviceSetIntermediateCacheConfig_t)LOAD_FUNCTION_PTR(handle, "xeDeviceSetIntermediateCacheConfig");
    if( nullptr == xe_apitable.pfnDeviceSetIntermediateCacheConfig )
        return false;

    xe_apitable.pfnDeviceSetLastLevelCacheConfig                        = (xe_pfnDeviceSetLastLevelCacheConfig_t)LOAD_FUNCTION_PTR(handle, "xeDeviceSetLastLevelCacheConfig");
    if( nullptr == xe_apitable.pfnDeviceSetLastLevelCacheConfig )
        return false;

    xe_apitable.pfnInit                                                 = (xe_pfnInit_t)LOAD_FUNCTION_PTR(handle, "xeInit");
    if( nullptr == xe_apitable.pfnInit )
        return false;

    xe_apitable.pfnGetDriverVersion                                     = (xe_pfnGetDriverVersion_t)LOAD_FUNCTION_PTR(handle, "xeGetDriverVersion");
    if( nullptr == xe_apitable.pfnGetDriverVersion )
        return false;

    xe_apitable.pfnEventPoolCreate                                      = (xe_pfnEventPoolCreate_t)LOAD_FUNCTION_PTR(handle, "xeEventPoolCreate");
    if( nullptr == xe_apitable.pfnEventPoolCreate )
        return false;

    xe_apitable.pfnEventPoolDestroy                                     = (xe_pfnEventPoolDestroy_t)LOAD_FUNCTION_PTR(handle, "xeEventPoolDestroy");
    if( nullptr == xe_apitable.pfnEventPoolDestroy )
        return false;

    xe_apitable.pfnEventCreate                                          = (xe_pfnEventCreate_t)LOAD_FUNCTION_PTR(handle, "xeEventCreate");
    if( nullptr == xe_apitable.pfnEventCreate )
        return false;

    xe_apitable.pfnEventDestroy                                         = (xe_pfnEventDestroy_t)LOAD_FUNCTION_PTR(handle, "xeEventDestroy");
    if( nullptr == xe_apitable.pfnEventDestroy )
        return false;

    xe_apitable.pfnEventPoolGetIpcHandle                                = (xe_pfnEventPoolGetIpcHandle_t)LOAD_FUNCTION_PTR(handle, "xeEventPoolGetIpcHandle");
    if( nullptr == xe_apitable.pfnEventPoolGetIpcHandle )
        return false;

    xe_apitable.pfnEventPoolOpenIpcHandle                               = (xe_pfnEventPoolOpenIpcHandle_t)LOAD_FUNCTION_PTR(handle, "xeEventPoolOpenIpcHandle");
    if( nullptr == xe_apitable.pfnEventPoolOpenIpcHandle )
        return false;

    xe_apitable.pfnEventPoolCloseIpcHandle                              = (xe_pfnEventPoolCloseIpcHandle_t)LOAD_FUNCTION_PTR(handle, "xeEventPoolCloseIpcHandle");
    if( nullptr == xe_apitable.pfnEventPoolCloseIpcHandle )
        return false;

    xe_apitable.pfnCommandListAppendSignalEvent                         = (xe_pfnCommandListAppendSignalEvent_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendSignalEvent");
    if( nullptr == xe_apitable.pfnCommandListAppendSignalEvent )
        return false;

    xe_apitable.pfnCommandListAppendWaitOnEvents                        = (xe_pfnCommandListAppendWaitOnEvents_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendWaitOnEvents");
    if( nullptr == xe_apitable.pfnCommandListAppendWaitOnEvents )
        return false;

    xe_apitable.pfnEventHostSignal                                      = (xe_pfnEventHostSignal_t)LOAD_FUNCTION_PTR(handle, "xeEventHostSignal");
    if( nullptr == xe_apitable.pfnEventHostSignal )
        return false;

    xe_apitable.pfnEventHostSynchronize                                 = (xe_pfnEventHostSynchronize_t)LOAD_FUNCTION_PTR(handle, "xeEventHostSynchronize");
    if( nullptr == xe_apitable.pfnEventHostSynchronize )
        return false;

    xe_apitable.pfnEventQueryStatus                                     = (xe_pfnEventQueryStatus_t)LOAD_FUNCTION_PTR(handle, "xeEventQueryStatus");
    if( nullptr == xe_apitable.pfnEventQueryStatus )
        return false;

    xe_apitable.pfnCommandListAppendEventReset                          = (xe_pfnCommandListAppendEventReset_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendEventReset");
    if( nullptr == xe_apitable.pfnCommandListAppendEventReset )
        return false;

    xe_apitable.pfnEventReset                                           = (xe_pfnEventReset_t)LOAD_FUNCTION_PTR(handle, "xeEventReset");
    if( nullptr == xe_apitable.pfnEventReset )
        return false;

    xe_apitable.pfnFenceCreate                                          = (xe_pfnFenceCreate_t)LOAD_FUNCTION_PTR(handle, "xeFenceCreate");
    if( nullptr == xe_apitable.pfnFenceCreate )
        return false;

    xe_apitable.pfnFenceDestroy                                         = (xe_pfnFenceDestroy_t)LOAD_FUNCTION_PTR(handle, "xeFenceDestroy");
    if( nullptr == xe_apitable.pfnFenceDestroy )
        return false;

    xe_apitable.pfnFenceHostSynchronize                                 = (xe_pfnFenceHostSynchronize_t)LOAD_FUNCTION_PTR(handle, "xeFenceHostSynchronize");
    if( nullptr == xe_apitable.pfnFenceHostSynchronize )
        return false;

    xe_apitable.pfnFenceQueryStatus                                     = (xe_pfnFenceQueryStatus_t)LOAD_FUNCTION_PTR(handle, "xeFenceQueryStatus");
    if( nullptr == xe_apitable.pfnFenceQueryStatus )
        return false;

    xe_apitable.pfnFenceReset                                           = (xe_pfnFenceReset_t)LOAD_FUNCTION_PTR(handle, "xeFenceReset");
    if( nullptr == xe_apitable.pfnFenceReset )
        return false;

    xe_apitable.pfnImageGetProperties                                   = (xe_pfnImageGetProperties_t)LOAD_FUNCTION_PTR(handle, "xeImageGetProperties");
    if( nullptr == xe_apitable.pfnImageGetProperties )
        return false;

    xe_apitable.pfnImageCreate                                          = (xe_pfnImageCreate_t)LOAD_FUNCTION_PTR(handle, "xeImageCreate");
    if( nullptr == xe_apitable.pfnImageCreate )
        return false;

    xe_apitable.pfnImageDestroy                                         = (xe_pfnImageDestroy_t)LOAD_FUNCTION_PTR(handle, "xeImageDestroy");
    if( nullptr == xe_apitable.pfnImageDestroy )
        return false;

    xe_apitable.pfnSharedMemAlloc                                       = (xe_pfnSharedMemAlloc_t)LOAD_FUNCTION_PTR(handle, "xeSharedMemAlloc");
    if( nullptr == xe_apitable.pfnSharedMemAlloc )
        return false;

    xe_apitable.pfnMemAlloc                                             = (xe_pfnMemAlloc_t)LOAD_FUNCTION_PTR(handle, "xeMemAlloc");
    if( nullptr == xe_apitable.pfnMemAlloc )
        return false;

    xe_apitable.pfnHostMemAlloc                                         = (xe_pfnHostMemAlloc_t)LOAD_FUNCTION_PTR(handle, "xeHostMemAlloc");
    if( nullptr == xe_apitable.pfnHostMemAlloc )
        return false;

    xe_apitable.pfnMemFree                                              = (xe_pfnMemFree_t)LOAD_FUNCTION_PTR(handle, "xeMemFree");
    if( nullptr == xe_apitable.pfnMemFree )
        return false;

    xe_apitable.pfnMemGetProperties                                     = (xe_pfnMemGetProperties_t)LOAD_FUNCTION_PTR(handle, "xeMemGetProperties");
    if( nullptr == xe_apitable.pfnMemGetProperties )
        return false;

    xe_apitable.pfnMemGetAddressRange                                   = (xe_pfnMemGetAddressRange_t)LOAD_FUNCTION_PTR(handle, "xeMemGetAddressRange");
    if( nullptr == xe_apitable.pfnMemGetAddressRange )
        return false;

    xe_apitable.pfnIpcGetMemHandle                                      = (xe_pfnIpcGetMemHandle_t)LOAD_FUNCTION_PTR(handle, "xeIpcGetMemHandle");
    if( nullptr == xe_apitable.pfnIpcGetMemHandle )
        return false;

    xe_apitable.pfnIpcOpenMemHandle                                     = (xe_pfnIpcOpenMemHandle_t)LOAD_FUNCTION_PTR(handle, "xeIpcOpenMemHandle");
    if( nullptr == xe_apitable.pfnIpcOpenMemHandle )
        return false;

    xe_apitable.pfnIpcCloseMemHandle                                    = (xe_pfnIpcCloseMemHandle_t)LOAD_FUNCTION_PTR(handle, "xeIpcCloseMemHandle");
    if( nullptr == xe_apitable.pfnIpcCloseMemHandle )
        return false;

    xe_apitable.pfnModuleCreate                                         = (xe_pfnModuleCreate_t)LOAD_FUNCTION_PTR(handle, "xeModuleCreate");
    if( nullptr == xe_apitable.pfnModuleCreate )
        return false;

    xe_apitable.pfnModuleDestroy                                        = (xe_pfnModuleDestroy_t)LOAD_FUNCTION_PTR(handle, "xeModuleDestroy");
    if( nullptr == xe_apitable.pfnModuleDestroy )
        return false;

    xe_apitable.pfnModuleBuildLogDestroy                                = (xe_pfnModuleBuildLogDestroy_t)LOAD_FUNCTION_PTR(handle, "xeModuleBuildLogDestroy");
    if( nullptr == xe_apitable.pfnModuleBuildLogDestroy )
        return false;

    xe_apitable.pfnModuleBuildLogGetString                              = (xe_pfnModuleBuildLogGetString_t)LOAD_FUNCTION_PTR(handle, "xeModuleBuildLogGetString");
    if( nullptr == xe_apitable.pfnModuleBuildLogGetString )
        return false;

    xe_apitable.pfnModuleGetNativeBinary                                = (xe_pfnModuleGetNativeBinary_t)LOAD_FUNCTION_PTR(handle, "xeModuleGetNativeBinary");
    if( nullptr == xe_apitable.pfnModuleGetNativeBinary )
        return false;

    xe_apitable.pfnModuleGetGlobalPointer                               = (xe_pfnModuleGetGlobalPointer_t)LOAD_FUNCTION_PTR(handle, "xeModuleGetGlobalPointer");
    if( nullptr == xe_apitable.pfnModuleGetGlobalPointer )
        return false;

    xe_apitable.pfnFunctionCreate                                       = (xe_pfnFunctionCreate_t)LOAD_FUNCTION_PTR(handle, "xeFunctionCreate");
    if( nullptr == xe_apitable.pfnFunctionCreate )
        return false;

    xe_apitable.pfnFunctionDestroy                                      = (xe_pfnFunctionDestroy_t)LOAD_FUNCTION_PTR(handle, "xeFunctionDestroy");
    if( nullptr == xe_apitable.pfnFunctionDestroy )
        return false;

    xe_apitable.pfnModuleGetFunctionPointer                             = (xe_pfnModuleGetFunctionPointer_t)LOAD_FUNCTION_PTR(handle, "xeModuleGetFunctionPointer");
    if( nullptr == xe_apitable.pfnModuleGetFunctionPointer )
        return false;

    xe_apitable.pfnFunctionSetGroupSize                                 = (xe_pfnFunctionSetGroupSize_t)LOAD_FUNCTION_PTR(handle, "xeFunctionSetGroupSize");
    if( nullptr == xe_apitable.pfnFunctionSetGroupSize )
        return false;

    xe_apitable.pfnFunctionSuggestGroupSize                             = (xe_pfnFunctionSuggestGroupSize_t)LOAD_FUNCTION_PTR(handle, "xeFunctionSuggestGroupSize");
    if( nullptr == xe_apitable.pfnFunctionSuggestGroupSize )
        return false;

    xe_apitable.pfnFunctionSetArgumentValue                             = (xe_pfnFunctionSetArgumentValue_t)LOAD_FUNCTION_PTR(handle, "xeFunctionSetArgumentValue");
    if( nullptr == xe_apitable.pfnFunctionSetArgumentValue )
        return false;

    xe_apitable.pfnFunctionSetAttribute                                 = (xe_pfnFunctionSetAttribute_t)LOAD_FUNCTION_PTR(handle, "xeFunctionSetAttribute");
    if( nullptr == xe_apitable.pfnFunctionSetAttribute )
        return false;

    xe_apitable.pfnFunctionGetAttribute                                 = (xe_pfnFunctionGetAttribute_t)LOAD_FUNCTION_PTR(handle, "xeFunctionGetAttribute");
    if( nullptr == xe_apitable.pfnFunctionGetAttribute )
        return false;

    xe_apitable.pfnCommandListAppendLaunchFunction                      = (xe_pfnCommandListAppendLaunchFunction_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendLaunchFunction");
    if( nullptr == xe_apitable.pfnCommandListAppendLaunchFunction )
        return false;

    xe_apitable.pfnCommandListAppendLaunchFunctionIndirect              = (xe_pfnCommandListAppendLaunchFunctionIndirect_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendLaunchFunctionIndirect");
    if( nullptr == xe_apitable.pfnCommandListAppendLaunchFunctionIndirect )
        return false;

    xe_apitable.pfnCommandListAppendLaunchMultipleFunctionsIndirect     = (xe_pfnCommandListAppendLaunchMultipleFunctionsIndirect_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendLaunchMultipleFunctionsIndirect");
    if( nullptr == xe_apitable.pfnCommandListAppendLaunchMultipleFunctionsIndirect )
        return false;

    xe_apitable.pfnCommandListAppendLaunchHostFunction                  = (xe_pfnCommandListAppendLaunchHostFunction_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendLaunchHostFunction");
    if( nullptr == xe_apitable.pfnCommandListAppendLaunchHostFunction )
        return false;

    xe_apitable.pfnDeviceMakeMemoryResident                             = (xe_pfnDeviceMakeMemoryResident_t)LOAD_FUNCTION_PTR(handle, "xeDeviceMakeMemoryResident");
    if( nullptr == xe_apitable.pfnDeviceMakeMemoryResident )
        return false;

    xe_apitable.pfnDeviceEvictMemory                                    = (xe_pfnDeviceEvictMemory_t)LOAD_FUNCTION_PTR(handle, "xeDeviceEvictMemory");
    if( nullptr == xe_apitable.pfnDeviceEvictMemory )
        return false;

    xe_apitable.pfnDeviceMakeImageResident                              = (xe_pfnDeviceMakeImageResident_t)LOAD_FUNCTION_PTR(handle, "xeDeviceMakeImageResident");
    if( nullptr == xe_apitable.pfnDeviceMakeImageResident )
        return false;

    xe_apitable.pfnDeviceEvictImage                                     = (xe_pfnDeviceEvictImage_t)LOAD_FUNCTION_PTR(handle, "xeDeviceEvictImage");
    if( nullptr == xe_apitable.pfnDeviceEvictImage )
        return false;

    xe_apitable.pfnSamplerCreate                                        = (xe_pfnSamplerCreate_t)LOAD_FUNCTION_PTR(handle, "xeSamplerCreate");
    if( nullptr == xe_apitable.pfnSamplerCreate )
        return false;

    xe_apitable.pfnSamplerDestroy                                       = (xe_pfnSamplerDestroy_t)LOAD_FUNCTION_PTR(handle, "xeSamplerDestroy");
    if( nullptr == xe_apitable.pfnSamplerDestroy )
        return false;

    return true;
}


#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xe_apitable.pfnCommandListAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xe_apitable.pfnCommandListAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceSystemBarrier(
    xe_device_handle_t hDevice                      ///< [in] handle of the device
    )
{
    if( nullptr == xe_apitable.pfnDeviceSystemBarrier )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnDeviceSystemBarrier( hDevice );
}

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
__xedllexport xe_result_t __xecall
xeDeviceRegisterCLMemory(
    xe_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the memory
    cl_mem mem,                                     ///< [in] the OpenCL memory to register
    void** ptr                                      ///< [out] pointer to device allocation
    )
{
    if( nullptr == xe_apitable.pfnDeviceRegisterCLMemory )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnDeviceRegisterCLMemory( hDevice, context, mem, ptr );
}
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
__xedllexport xe_result_t __xecall
xeDeviceRegisterCLProgram(
    xe_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the program
    cl_program program,                             ///< [in] the OpenCL program to register
    xe_module_handle_t* phModule                    ///< [out] pointer to handle of module object created
    )
{
    if( nullptr == xe_apitable.pfnDeviceRegisterCLProgram )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnDeviceRegisterCLProgram( hDevice, context, program, phModule );
}
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
__xedllexport xe_result_t __xecall
xeDeviceRegisterCLCommandQueue(
    xe_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the command queue
    cl_command_queue command_queue,                 ///< [in] the OpenCL command queue to register
    xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    )
{
    if( nullptr == xe_apitable.pfnDeviceRegisterCLCommandQueue )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnDeviceRegisterCLCommandQueue( hDevice, context, command_queue, phCommandQueue );
}
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
    xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    )
{
    if( nullptr == xe_apitable.pfnCommandListCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnCommandListCreate( hDevice, desc, phCommandList );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListCreateImmediate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
    xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    )
{
    if( nullptr == xe_apitable.pfnCommandListCreateImmediate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnCommandListCreateImmediate( hDevice, desc, phCommandList );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListDestroy(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to destroy
    )
{
    if( nullptr == xe_apitable.pfnCommandListDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnCommandListDestroy( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListClose(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
    )
{
    if( nullptr == xe_apitable.pfnCommandListClose )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnCommandListClose( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListReset(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
    )
{
    if( nullptr == xe_apitable.pfnCommandListReset )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnCommandListReset( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListSetParameter(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_command_list_parameter_t parameter,          ///< [in] parameter to change
    uint32_t value                                  ///< [in] value of attribute
    )
{
    if( nullptr == xe_apitable.pfnCommandListSetParameter )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnCommandListSetParameter( hCommandList, parameter, value );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListGetParameter(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_command_list_parameter_t parameter,          ///< [in] parameter to retrieve
    uint32_t* value                                 ///< [out] value of attribute
    )
{
    if( nullptr == xe_apitable.pfnCommandListGetParameter )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnCommandListGetParameter( hCommandList, parameter, value );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListResetParameters(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    )
{
    if( nullptr == xe_apitable.pfnCommandListResetParameters )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnCommandListResetParameters( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListReserveSpace(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    size_t size,                                    ///< [in] size (in bytes) to reserve
    void** ptr                                      ///< [out] pointer to command buffer space reserved
    )
{
    if( nullptr == xe_apitable.pfnCommandListReserveSpace )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnCommandListReserveSpace( hCommandList, size, ptr );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandQueueCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
    xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    )
{
    if( nullptr == xe_apitable.pfnCommandQueueCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnCommandQueueCreate( hDevice, desc, phCommandQueue );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandQueueDestroy(
    xe_command_queue_handle_t hCommandQueue         ///< [in] handle of command queue object to destroy
    )
{
    if( nullptr == xe_apitable.pfnCommandQueueDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnCommandQueueDestroy( hCommandQueue );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandQueueExecuteCommandLists(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint32_t numCommandLists,                       ///< [in] number of command lists to execute
    xe_command_list_handle_t* phCommandLists,       ///< [in] list of handles of the command lists to execute
    xe_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
    )
{
    if( nullptr == xe_apitable.pfnCommandQueueExecuteCommandLists )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnCommandQueueExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xe_apitable.pfnCommandQueueSynchronize( hCommandQueue, timeout );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xe_apitable.pfnCommandListAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xe_apitable.pfnCommandListAppendMemorySet( hCommandList, ptr, value, size, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xe_apitable.pfnCommandListAppendImageCopy( hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xe_apitable.pfnCommandListAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xe_apitable.pfnCommandListAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xe_apitable.pfnCommandListAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListAppendMemoryPrefetch(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
    size_t count                                    ///< [in] size in bytes of the memory range to prefetch
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendMemoryPrefetch )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnCommandListAppendMemoryPrefetch( hCommandList, ptr, count );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xe_apitable.pfnCommandListAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceGetCount(
    uint32_t* count                                 ///< [out] number of devices available
    )
{
    if( nullptr == xe_apitable.pfnDeviceGetCount )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnDeviceGetCount( count );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceGet(
    uint32_t ordinal,                               ///< [in] The device index in the range of [0, ::xeDeviceGetCount]
    xe_device_handle_t* phDevice                    ///< [out] pointer to handle of device object created
    )
{
    if( nullptr == xe_apitable.pfnDeviceGet )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnDeviceGet( ordinal, phDevice );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceGetSubDevice(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t ordinal,                               ///< [in] ordinal of sub-device to retrieve
    xe_device_handle_t* phSubDevice                 ///< [out] pointer to handle of sub-device object.
    )
{
    if( nullptr == xe_apitable.pfnDeviceGetSubDevice )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnDeviceGetSubDevice( hDevice, ordinal, phSubDevice );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceGetApiVersion(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_api_version_t* version                       ///< [out] api version
    )
{
    if( nullptr == xe_apitable.pfnDeviceGetApiVersion )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnDeviceGetApiVersion( hDevice, version );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceGetProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_device_properties_t* pDeviceProperties       ///< [out] query result for device properties
    )
{
    if( nullptr == xe_apitable.pfnDeviceGetProperties )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnDeviceGetProperties( hDevice, pDeviceProperties );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceGetComputeProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_device_compute_properties_t* pComputeProperties  ///< [out] query result for compute properties
    )
{
    if( nullptr == xe_apitable.pfnDeviceGetComputeProperties )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnDeviceGetComputeProperties( hDevice, pComputeProperties );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceGetMemoryProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    xe_device_memory_properties_t* pMemProperties   ///< [out] query result for compute properties
    )
{
    if( nullptr == xe_apitable.pfnDeviceGetMemoryProperties )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnDeviceGetMemoryProperties( hDevice, pMemProperties );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceGetP2PProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    xe_device_p2p_properties_t* pP2PProperties      ///< [out] Peer-to-Peer properties between source and peer device
    )
{
    if( nullptr == xe_apitable.pfnDeviceGetP2PProperties )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnDeviceGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceCanAccessPeer(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    xe_bool_t* value                                ///< [out] returned access capability
    )
{
    if( nullptr == xe_apitable.pfnDeviceCanAccessPeer )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnDeviceCanAccessPeer( hDevice, hPeerDevice, value );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceSetIntermediateCacheConfig(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device 
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    )
{
    if( nullptr == xe_apitable.pfnDeviceSetIntermediateCacheConfig )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnDeviceSetIntermediateCacheConfig( hDevice, CacheConfig );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceSetLastLevelCacheConfig(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device 
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    )
{
    if( nullptr == xe_apitable.pfnDeviceSetLastLevelCacheConfig )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnDeviceSetLastLevelCacheConfig( hDevice, CacheConfig );
}


///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeGetDriverVersion(
    uint32_t* version                               ///< [out] driver version
    )
{
    if( nullptr == xe_apitable.pfnGetDriverVersion )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnGetDriverVersion( version );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeEventPoolCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
    xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    )
{
    if( nullptr == xe_apitable.pfnEventPoolCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnEventPoolCreate( hDevice, desc, phEventPool );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeEventPoolDestroy(
    xe_event_pool_handle_t hEventPool               ///< [in] handle of event pool object to destroy
    )
{
    if( nullptr == xe_apitable.pfnEventPoolDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnEventPoolDestroy( hEventPool );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeEventCreate(
    xe_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
    const xe_event_desc_t* desc,                    ///< [in] pointer to event descriptor
    xe_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    )
{
    if( nullptr == xe_apitable.pfnEventCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnEventCreate( hEventPool, desc, phEvent );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeEventDestroy(
    xe_event_handle_t hEvent                        ///< [in] handle of event object to destroy
    )
{
    if( nullptr == xe_apitable.pfnEventDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnEventDestroy( hEvent );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeEventPoolGetIpcHandle(
    xe_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
    xe_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
    )
{
    if( nullptr == xe_apitable.pfnEventPoolGetIpcHandle )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnEventPoolGetIpcHandle( hEventPool, phIpc );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeEventPoolOpenIpcHandle(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC event pool handle
    xe_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event handle
    xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    )
{
    if( nullptr == xe_apitable.pfnEventPoolOpenIpcHandle )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnEventPoolOpenIpcHandle( hDevice, hIpc, phEventPool );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeEventPoolCloseIpcHandle(
    xe_event_pool_handle_t hEventPool               ///< [in] handle of event pool object
    )
{
    if( nullptr == xe_apitable.pfnEventPoolCloseIpcHandle )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnEventPoolCloseIpcHandle( hEventPool );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListAppendSignalEvent(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendSignalEvent )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnCommandListAppendSignalEvent( hCommandList, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListAppendWaitOnEvents(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
    xe_event_handle_t* phEvents                     ///< [in] handle of the events to wait on before continuing
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendWaitOnEvents )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnCommandListAppendWaitOnEvents( hCommandList, numEvents, phEvents );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeEventHostSignal(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    if( nullptr == xe_apitable.pfnEventHostSignal )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnEventHostSignal( hEvent );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xe_apitable.pfnEventHostSynchronize( hEvent, timeout );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeEventQueryStatus(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    if( nullptr == xe_apitable.pfnEventQueryStatus )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnEventQueryStatus( hEvent );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListAppendEventReset(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendEventReset )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnCommandListAppendEventReset( hCommandList, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeEventReset(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    if( nullptr == xe_apitable.pfnEventReset )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnEventReset( hEvent );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeFenceCreate(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
    const xe_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
    xe_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
    )
{
    if( nullptr == xe_apitable.pfnFenceCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnFenceCreate( hCommandQueue, desc, phFence );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeFenceDestroy(
    xe_fence_handle_t hFence                        ///< [in] handle of fence object to destroy
    )
{
    if( nullptr == xe_apitable.pfnFenceDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnFenceDestroy( hFence );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xe_apitable.pfnFenceHostSynchronize( hFence, timeout );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeFenceQueryStatus(
    xe_fence_handle_t hFence                        ///< [in] handle of the fence
    )
{
    if( nullptr == xe_apitable.pfnFenceQueryStatus )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnFenceQueryStatus( hFence );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeFenceReset(
    xe_fence_handle_t hFence                        ///< [in] handle of the fence
    )
{
    if( nullptr == xe_apitable.pfnFenceReset )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnFenceReset( hFence );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeImageGetProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    xe_image_properties_t* pImageProperties         ///< [out] pointer to image properties
    )
{
    if( nullptr == xe_apitable.pfnImageGetProperties )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnImageGetProperties( hDevice, desc, pImageProperties );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeImageCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    xe_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
    )
{
    if( nullptr == xe_apitable.pfnImageCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnImageCreate( hDevice, desc, phImage );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeImageDestroy(
    xe_image_handle_t hImage                        ///< [in] handle of image object to destroy
    )
{
    if( nullptr == xe_apitable.pfnImageDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnImageDestroy( hImage );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xe_apitable.pfnSharedMemAlloc( hDevice, device_flags, host_flags, size, alignment, ptr );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xe_apitable.pfnMemAlloc( hDevice, flags, size, alignment, ptr );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeHostMemAlloc(
    xe_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to host allocation
    )
{
    if( nullptr == xe_apitable.pfnHostMemAlloc )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnHostMemAlloc( flags, size, alignment, ptr );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeMemFree(
    const void* ptr                                 ///< [in] pointer to memory to free
    )
{
    if( nullptr == xe_apitable.pfnMemFree )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnMemFree( ptr );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeMemGetProperties(
    const void* ptr,                                ///< [in] Pointer to query
    xe_memory_allocation_properties_t* pMemProperties   ///< [out] Query result for memory allocation properties
    )
{
    if( nullptr == xe_apitable.pfnMemGetProperties )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnMemGetProperties( ptr, pMemProperties );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeMemGetAddressRange(
    const void* ptr,                                ///< [in] Pointer to query
    void** pBase,                                   ///< [in,out][optional] base address of the allocation
    size_t* pSize                                   ///< [in,out][optional] size of the allocation
    )
{
    if( nullptr == xe_apitable.pfnMemGetAddressRange )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnMemGetAddressRange( ptr, pBase, pSize );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeIpcGetMemHandle(
    const void* ptr,                                ///< [in] Pointer to the device memory allocation
    xe_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    )
{
    if( nullptr == xe_apitable.pfnIpcGetMemHandle )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnIpcGetMemHandle( ptr, pIpcHandle );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeIpcOpenMemHandle(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
    xe_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
    xe_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
    void** ptr                                      ///< [out] pointer to device allocation in this process
    )
{
    if( nullptr == xe_apitable.pfnIpcOpenMemHandle )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnIpcOpenMemHandle( hDevice, handle, flags, ptr );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeIpcCloseMemHandle(
    const void* ptr                                 ///< [in] pointer to device allocation in this process
    )
{
    if( nullptr == xe_apitable.pfnIpcCloseMemHandle )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnIpcCloseMemHandle( ptr );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeModuleCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_module_desc_t* pDesc,                  ///< [in] pointer to module descriptor
    xe_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
    xe_module_build_log_handle_t* phBuildLog        ///< [in,out][optional] pointer to handle of module's build log.
    )
{
    if( nullptr == xe_apitable.pfnModuleCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnModuleCreate( hDevice, pDesc, phModule, phBuildLog );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeModuleDestroy(
    xe_module_handle_t hModule                      ///< [in] handle of the module
    )
{
    if( nullptr == xe_apitable.pfnModuleDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnModuleDestroy( hModule );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeModuleBuildLogDestroy(
    xe_module_build_log_handle_t hModuleBuildLog    ///< [in] handle of the module build log object.
    )
{
    if( nullptr == xe_apitable.pfnModuleBuildLogDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnModuleBuildLogDestroy( hModuleBuildLog );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeModuleBuildLogGetString(
    xe_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
    size_t* pSize,                                  ///< [in,out] size of build log string.
    char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
    )
{
    if( nullptr == xe_apitable.pfnModuleBuildLogGetString )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnModuleBuildLogGetString( hModuleBuildLog, pSize, pBuildLog );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeModuleGetNativeBinary(
    xe_module_handle_t hModule,                     ///< [in] handle of the device
    size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
    uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
    )
{
    if( nullptr == xe_apitable.pfnModuleGetNativeBinary )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnModuleGetNativeBinary( hModule, pSize, pModuleNativeBinary );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeModuleGetGlobalPointer(
    xe_module_handle_t hModule,                     ///< [in] handle of the device
    const char* pGlobalName,                        ///< [in] name of function in global
    void** pPtr                                     ///< [out] device visible pointer
    )
{
    if( nullptr == xe_apitable.pfnModuleGetGlobalPointer )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnModuleGetGlobalPointer( hModule, pGlobalName, pPtr );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeFunctionCreate(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const xe_function_desc_t* pDesc,                ///< [in] pointer to function descriptor
    xe_function_handle_t* phFunction                ///< [out] handle of the Function object
    )
{
    if( nullptr == xe_apitable.pfnFunctionCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnFunctionCreate( hModule, pDesc, phFunction );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeFunctionDestroy(
    xe_function_handle_t hFunction                  ///< [in] handle of the function object
    )
{
    if( nullptr == xe_apitable.pfnFunctionDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnFunctionDestroy( hFunction );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeModuleGetFunctionPointer(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
    void** pfnFunction                              ///< [out] pointer to function.
    )
{
    if( nullptr == xe_apitable.pfnModuleGetFunctionPointer )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnModuleGetFunctionPointer( hModule, pFunctionName, pfnFunction );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeFunctionSetGroupSize(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this function.
    uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this function.
    uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this function.
    )
{
    if( nullptr == xe_apitable.pfnFunctionSetGroupSize )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnFunctionSetGroupSize( hFunction, groupSizeX, groupSizeY, groupSizeZ );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xe_apitable.pfnFunctionSuggestGroupSize( hFunction, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xe_apitable.pfnFunctionSetArgumentValue( hFunction, argIndex, argSize, pArgValue );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeFunctionSetAttribute(
    xe_function_handle_t hFunction,                 ///< [in,out] handle of the function.
    xe_function_set_attribute_t attr,               ///< [in] attribute to set
    uint32_t value                                  ///< [in] attribute value to set
    )
{
    if( nullptr == xe_apitable.pfnFunctionSetAttribute )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnFunctionSetAttribute( hFunction, attr, value );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeFunctionGetAttribute(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    xe_function_get_attribute_t attr,               ///< [in] attribute to query
    uint32_t* pValue                                ///< [out] returned attribute value
    )
{
    if( nullptr == xe_apitable.pfnFunctionGetAttribute )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnFunctionGetAttribute( hFunction, attr, pValue );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xe_apitable.pfnCommandListAppendLaunchFunction( hCommandList, hFunction, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xe_apitable.pfnCommandListAppendLaunchFunctionIndirect( hCommandList, hFunction, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
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

    return xe_apitable.pfnCommandListAppendLaunchMultipleFunctionsIndirect( hCommandList, numFunctions, phFunctions, pNumLaunchArguments, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListAppendLaunchHostFunction(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_host_pfn_t pfnHostFunc,                      ///< [in] pointer to host function.
    void* pUserData                                 ///< [in] pointer to user data to pass to host function.
    )
{
    if( nullptr == xe_apitable.pfnCommandListAppendLaunchHostFunction )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnCommandListAppendLaunchHostFunction( hCommandList, pfnHostFunc, pUserData );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceMakeMemoryResident(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    void* ptr,                                      ///< [in] pointer to memory to make resident
    size_t size                                     ///< [in] size in bytes to make resident
    )
{
    if( nullptr == xe_apitable.pfnDeviceMakeMemoryResident )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnDeviceMakeMemoryResident( hDevice, ptr, size );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceEvictMemory(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    void* ptr,                                      ///< [in] pointer to memory to evict
    size_t size                                     ///< [in] size in bytes to evict
    )
{
    if( nullptr == xe_apitable.pfnDeviceEvictMemory )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnDeviceEvictMemory( hDevice, ptr, size );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceMakeImageResident(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_image_handle_t hImage                        ///< [in] handle of image to make resident
    )
{
    if( nullptr == xe_apitable.pfnDeviceMakeImageResident )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnDeviceMakeImageResident( hDevice, hImage );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceEvictImage(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_image_handle_t hImage                        ///< [in] handle of image to make evict
    )
{
    if( nullptr == xe_apitable.pfnDeviceEvictImage )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnDeviceEvictImage( hDevice, hImage );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeSamplerCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_sampler_desc_t* pDesc,                 ///< [in] pointer to sampler descriptor
    xe_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
    )
{
    if( nullptr == xe_apitable.pfnSamplerCreate )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnSamplerCreate( hDevice, pDesc, phSampler );
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeSamplerDestroy(
    xe_sampler_handle_t hSampler                    ///< [in] handle of the sampler
    )
{
    if( nullptr == xe_apitable.pfnSamplerDestroy )
        return XE_RESULT_ERROR_UNINITIALIZED;

    return xe_apitable.pfnSamplerDestroy( hSampler );
}

#if defined(__cplusplus)
};
#endif
