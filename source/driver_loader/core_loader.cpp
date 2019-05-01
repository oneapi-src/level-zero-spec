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
#include "core_loader.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Loads function pointer table for loaded driver
bool xeLoad(
    void* handle,                   ///< [in] driver handle
    xeapi_pfntable_t* pfntable )  ///< [in] pointer to table of xe API function pointers
{
    if(nullptr == pfntable){
        return false;
    }

    pfntable->xeCommandListAppendBarrier                                      = (pfn_xeCommandListAppendBarrier_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendBarrier");
    pfntable->xeCommandListAppendMemoryRangesBarrier                          = (pfn_xeCommandListAppendMemoryRangesBarrier_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendMemoryRangesBarrier");
    pfntable->xeDeviceSystemBarrier                                           = (pfn_xeDeviceSystemBarrier_t)LOAD_FUNCTION_PTR(handle, "xeDeviceSystemBarrier");
    #if XE_ENABLE_OCL_INTEROP
    pfntable->xeDeviceRegisterCLMemory                                        = (pfn_xeDeviceRegisterCLMemory_t)LOAD_FUNCTION_PTR(handle, "xeDeviceRegisterCLMemory");
    #endif // XE_ENABLE_OCL_INTEROP
    #if XE_ENABLE_OCL_INTEROP
    pfntable->xeDeviceRegisterCLProgram                                       = (pfn_xeDeviceRegisterCLProgram_t)LOAD_FUNCTION_PTR(handle, "xeDeviceRegisterCLProgram");
    #endif // XE_ENABLE_OCL_INTEROP
    #if XE_ENABLE_OCL_INTEROP
    pfntable->xeDeviceRegisterCLCommandQueue                                  = (pfn_xeDeviceRegisterCLCommandQueue_t)LOAD_FUNCTION_PTR(handle, "xeDeviceRegisterCLCommandQueue");
    #endif // XE_ENABLE_OCL_INTEROP
    pfntable->xeCommandListCreate                                             = (pfn_xeCommandListCreate_t)LOAD_FUNCTION_PTR(handle, "xeCommandListCreate");
    pfntable->xeCommandListCreateImmediate                                    = (pfn_xeCommandListCreateImmediate_t)LOAD_FUNCTION_PTR(handle, "xeCommandListCreateImmediate");
    pfntable->xeCommandListDestroy                                            = (pfn_xeCommandListDestroy_t)LOAD_FUNCTION_PTR(handle, "xeCommandListDestroy");
    pfntable->xeCommandListClose                                              = (pfn_xeCommandListClose_t)LOAD_FUNCTION_PTR(handle, "xeCommandListClose");
    pfntable->xeCommandListReset                                              = (pfn_xeCommandListReset_t)LOAD_FUNCTION_PTR(handle, "xeCommandListReset");
    pfntable->xeCommandListSetParameter                                       = (pfn_xeCommandListSetParameter_t)LOAD_FUNCTION_PTR(handle, "xeCommandListSetParameter");
    pfntable->xeCommandListGetParameter                                       = (pfn_xeCommandListGetParameter_t)LOAD_FUNCTION_PTR(handle, "xeCommandListGetParameter");
    pfntable->xeCommandListResetParameters                                    = (pfn_xeCommandListResetParameters_t)LOAD_FUNCTION_PTR(handle, "xeCommandListResetParameters");
    pfntable->xeCommandListReserveSpace                                       = (pfn_xeCommandListReserveSpace_t)LOAD_FUNCTION_PTR(handle, "xeCommandListReserveSpace");
    pfntable->xeCommandQueueCreate                                            = (pfn_xeCommandQueueCreate_t)LOAD_FUNCTION_PTR(handle, "xeCommandQueueCreate");
    pfntable->xeCommandQueueDestroy                                           = (pfn_xeCommandQueueDestroy_t)LOAD_FUNCTION_PTR(handle, "xeCommandQueueDestroy");
    pfntable->xeCommandQueueExecuteCommandLists                               = (pfn_xeCommandQueueExecuteCommandLists_t)LOAD_FUNCTION_PTR(handle, "xeCommandQueueExecuteCommandLists");
    pfntable->xeCommandQueueSynchronize                                       = (pfn_xeCommandQueueSynchronize_t)LOAD_FUNCTION_PTR(handle, "xeCommandQueueSynchronize");
    pfntable->xeCommandListAppendMemoryCopy                                   = (pfn_xeCommandListAppendMemoryCopy_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendMemoryCopy");
    pfntable->xeCommandListAppendMemorySet                                    = (pfn_xeCommandListAppendMemorySet_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendMemorySet");
    pfntable->xeCommandListAppendImageCopy                                    = (pfn_xeCommandListAppendImageCopy_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendImageCopy");
    pfntable->xeCommandListAppendImageCopyRegion                              = (pfn_xeCommandListAppendImageCopyRegion_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendImageCopyRegion");
    pfntable->xeCommandListAppendImageCopyToMemory                            = (pfn_xeCommandListAppendImageCopyToMemory_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendImageCopyToMemory");
    pfntable->xeCommandListAppendImageCopyFromMemory                          = (pfn_xeCommandListAppendImageCopyFromMemory_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendImageCopyFromMemory");
    pfntable->xeCommandListAppendMemoryPrefetch                               = (pfn_xeCommandListAppendMemoryPrefetch_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendMemoryPrefetch");
    pfntable->xeCommandListAppendMemAdvise                                    = (pfn_xeCommandListAppendMemAdvise_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendMemAdvise");
    pfntable->xeDeviceGetCount                                                = (pfn_xeDeviceGetCount_t)LOAD_FUNCTION_PTR(handle, "xeDeviceGetCount");
    pfntable->xeDeviceGet                                                     = (pfn_xeDeviceGet_t)LOAD_FUNCTION_PTR(handle, "xeDeviceGet");
    pfntable->xeDeviceGetSubDevice                                            = (pfn_xeDeviceGetSubDevice_t)LOAD_FUNCTION_PTR(handle, "xeDeviceGetSubDevice");
    pfntable->xeDeviceGetApiVersion                                           = (pfn_xeDeviceGetApiVersion_t)LOAD_FUNCTION_PTR(handle, "xeDeviceGetApiVersion");
    pfntable->xeDeviceGetProperties                                           = (pfn_xeDeviceGetProperties_t)LOAD_FUNCTION_PTR(handle, "xeDeviceGetProperties");
    pfntable->xeDeviceGetComputeProperties                                    = (pfn_xeDeviceGetComputeProperties_t)LOAD_FUNCTION_PTR(handle, "xeDeviceGetComputeProperties");
    pfntable->xeDeviceGetMemoryProperties                                     = (pfn_xeDeviceGetMemoryProperties_t)LOAD_FUNCTION_PTR(handle, "xeDeviceGetMemoryProperties");
    pfntable->xeDeviceGetP2PProperties                                        = (pfn_xeDeviceGetP2PProperties_t)LOAD_FUNCTION_PTR(handle, "xeDeviceGetP2PProperties");
    pfntable->xeDeviceCanAccessPeer                                           = (pfn_xeDeviceCanAccessPeer_t)LOAD_FUNCTION_PTR(handle, "xeDeviceCanAccessPeer");
    pfntable->xeDeviceSetIntermediateCacheConfig                              = (pfn_xeDeviceSetIntermediateCacheConfig_t)LOAD_FUNCTION_PTR(handle, "xeDeviceSetIntermediateCacheConfig");
    pfntable->xeDeviceSetLastLevelCacheConfig                                 = (pfn_xeDeviceSetLastLevelCacheConfig_t)LOAD_FUNCTION_PTR(handle, "xeDeviceSetLastLevelCacheConfig");
    pfntable->xeInit                                                          = (pfn_xeInit_t)LOAD_FUNCTION_PTR(handle, "xeInit");
    pfntable->xeGetDriverVersion                                              = (pfn_xeGetDriverVersion_t)LOAD_FUNCTION_PTR(handle, "xeGetDriverVersion");
    pfntable->xeEventPoolCreate                                               = (pfn_xeEventPoolCreate_t)LOAD_FUNCTION_PTR(handle, "xeEventPoolCreate");
    pfntable->xeEventPoolDestroy                                              = (pfn_xeEventPoolDestroy_t)LOAD_FUNCTION_PTR(handle, "xeEventPoolDestroy");
    pfntable->xeEventCreate                                                   = (pfn_xeEventCreate_t)LOAD_FUNCTION_PTR(handle, "xeEventCreate");
    pfntable->xeEventDestroy                                                  = (pfn_xeEventDestroy_t)LOAD_FUNCTION_PTR(handle, "xeEventDestroy");
    pfntable->xeEventPoolGetIpcHandle                                         = (pfn_xeEventPoolGetIpcHandle_t)LOAD_FUNCTION_PTR(handle, "xeEventPoolGetIpcHandle");
    pfntable->xeEventPoolOpenIpcHandle                                        = (pfn_xeEventPoolOpenIpcHandle_t)LOAD_FUNCTION_PTR(handle, "xeEventPoolOpenIpcHandle");
    pfntable->xeEventPoolCloseIpcHandle                                       = (pfn_xeEventPoolCloseIpcHandle_t)LOAD_FUNCTION_PTR(handle, "xeEventPoolCloseIpcHandle");
    pfntable->xeCommandListAppendSignalEvent                                  = (pfn_xeCommandListAppendSignalEvent_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendSignalEvent");
    pfntable->xeCommandListAppendWaitOnEvents                                 = (pfn_xeCommandListAppendWaitOnEvents_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendWaitOnEvents");
    pfntable->xeEventHostSignal                                               = (pfn_xeEventHostSignal_t)LOAD_FUNCTION_PTR(handle, "xeEventHostSignal");
    pfntable->xeEventHostSynchronize                                          = (pfn_xeEventHostSynchronize_t)LOAD_FUNCTION_PTR(handle, "xeEventHostSynchronize");
    pfntable->xeEventQueryStatus                                              = (pfn_xeEventQueryStatus_t)LOAD_FUNCTION_PTR(handle, "xeEventQueryStatus");
    pfntable->xeCommandListAppendEventReset                                   = (pfn_xeCommandListAppendEventReset_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendEventReset");
    pfntable->xeEventReset                                                    = (pfn_xeEventReset_t)LOAD_FUNCTION_PTR(handle, "xeEventReset");
    pfntable->xeFenceCreate                                                   = (pfn_xeFenceCreate_t)LOAD_FUNCTION_PTR(handle, "xeFenceCreate");
    pfntable->xeFenceDestroy                                                  = (pfn_xeFenceDestroy_t)LOAD_FUNCTION_PTR(handle, "xeFenceDestroy");
    pfntable->xeFenceHostSynchronize                                          = (pfn_xeFenceHostSynchronize_t)LOAD_FUNCTION_PTR(handle, "xeFenceHostSynchronize");
    pfntable->xeFenceQueryStatus                                              = (pfn_xeFenceQueryStatus_t)LOAD_FUNCTION_PTR(handle, "xeFenceQueryStatus");
    pfntable->xeFenceReset                                                    = (pfn_xeFenceReset_t)LOAD_FUNCTION_PTR(handle, "xeFenceReset");
    pfntable->xeImageGetProperties                                            = (pfn_xeImageGetProperties_t)LOAD_FUNCTION_PTR(handle, "xeImageGetProperties");
    pfntable->xeImageCreate                                                   = (pfn_xeImageCreate_t)LOAD_FUNCTION_PTR(handle, "xeImageCreate");
    pfntable->xeImageDestroy                                                  = (pfn_xeImageDestroy_t)LOAD_FUNCTION_PTR(handle, "xeImageDestroy");
    pfntable->xeSharedMemAlloc                                                = (pfn_xeSharedMemAlloc_t)LOAD_FUNCTION_PTR(handle, "xeSharedMemAlloc");
    pfntable->xeMemAlloc                                                      = (pfn_xeMemAlloc_t)LOAD_FUNCTION_PTR(handle, "xeMemAlloc");
    pfntable->xeHostMemAlloc                                                  = (pfn_xeHostMemAlloc_t)LOAD_FUNCTION_PTR(handle, "xeHostMemAlloc");
    pfntable->xeMemFree                                                       = (pfn_xeMemFree_t)LOAD_FUNCTION_PTR(handle, "xeMemFree");
    pfntable->xeMemGetProperties                                              = (pfn_xeMemGetProperties_t)LOAD_FUNCTION_PTR(handle, "xeMemGetProperties");
    pfntable->xeMemGetAddressRange                                            = (pfn_xeMemGetAddressRange_t)LOAD_FUNCTION_PTR(handle, "xeMemGetAddressRange");
    pfntable->xeIpcGetMemHandle                                               = (pfn_xeIpcGetMemHandle_t)LOAD_FUNCTION_PTR(handle, "xeIpcGetMemHandle");
    pfntable->xeIpcOpenMemHandle                                              = (pfn_xeIpcOpenMemHandle_t)LOAD_FUNCTION_PTR(handle, "xeIpcOpenMemHandle");
    pfntable->xeIpcCloseMemHandle                                             = (pfn_xeIpcCloseMemHandle_t)LOAD_FUNCTION_PTR(handle, "xeIpcCloseMemHandle");
    pfntable->xeModuleCreate                                                  = (pfn_xeModuleCreate_t)LOAD_FUNCTION_PTR(handle, "xeModuleCreate");
    pfntable->xeModuleDestroy                                                 = (pfn_xeModuleDestroy_t)LOAD_FUNCTION_PTR(handle, "xeModuleDestroy");
    pfntable->xeModuleBuildLogDestroy                                         = (pfn_xeModuleBuildLogDestroy_t)LOAD_FUNCTION_PTR(handle, "xeModuleBuildLogDestroy");
    pfntable->xeModuleBuildLogGetString                                       = (pfn_xeModuleBuildLogGetString_t)LOAD_FUNCTION_PTR(handle, "xeModuleBuildLogGetString");
    pfntable->xeModuleGetNativeBinary                                         = (pfn_xeModuleGetNativeBinary_t)LOAD_FUNCTION_PTR(handle, "xeModuleGetNativeBinary");
    pfntable->xeModuleGetGlobalPointer                                        = (pfn_xeModuleGetGlobalPointer_t)LOAD_FUNCTION_PTR(handle, "xeModuleGetGlobalPointer");
    pfntable->xeFunctionCreate                                                = (pfn_xeFunctionCreate_t)LOAD_FUNCTION_PTR(handle, "xeFunctionCreate");
    pfntable->xeFunctionDestroy                                               = (pfn_xeFunctionDestroy_t)LOAD_FUNCTION_PTR(handle, "xeFunctionDestroy");
    pfntable->xeModuleGetFunctionPointer                                      = (pfn_xeModuleGetFunctionPointer_t)LOAD_FUNCTION_PTR(handle, "xeModuleGetFunctionPointer");
    pfntable->xeFunctionSetGroupSize                                          = (pfn_xeFunctionSetGroupSize_t)LOAD_FUNCTION_PTR(handle, "xeFunctionSetGroupSize");
    pfntable->xeFunctionSuggestGroupSize                                      = (pfn_xeFunctionSuggestGroupSize_t)LOAD_FUNCTION_PTR(handle, "xeFunctionSuggestGroupSize");
    pfntable->xeFunctionSetArgumentValue                                      = (pfn_xeFunctionSetArgumentValue_t)LOAD_FUNCTION_PTR(handle, "xeFunctionSetArgumentValue");
    pfntable->xeFunctionSetAttribute                                          = (pfn_xeFunctionSetAttribute_t)LOAD_FUNCTION_PTR(handle, "xeFunctionSetAttribute");
    pfntable->xeFunctionGetAttribute                                          = (pfn_xeFunctionGetAttribute_t)LOAD_FUNCTION_PTR(handle, "xeFunctionGetAttribute");
    pfntable->xeCommandListAppendLaunchFunction                               = (pfn_xeCommandListAppendLaunchFunction_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendLaunchFunction");
    pfntable->xeCommandListAppendLaunchFunctionIndirect                       = (pfn_xeCommandListAppendLaunchFunctionIndirect_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendLaunchFunctionIndirect");
    pfntable->xeCommandListAppendLaunchMultipleFunctionsIndirect              = (pfn_xeCommandListAppendLaunchMultipleFunctionsIndirect_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendLaunchMultipleFunctionsIndirect");
    pfntable->xeCommandListAppendLaunchHostFunction                           = (pfn_xeCommandListAppendLaunchHostFunction_t)LOAD_FUNCTION_PTR(handle, "xeCommandListAppendLaunchHostFunction");
    pfntable->xeDeviceMakeMemoryResident                                      = (pfn_xeDeviceMakeMemoryResident_t)LOAD_FUNCTION_PTR(handle, "xeDeviceMakeMemoryResident");
    pfntable->xeDeviceEvictMemory                                             = (pfn_xeDeviceEvictMemory_t)LOAD_FUNCTION_PTR(handle, "xeDeviceEvictMemory");
    pfntable->xeDeviceMakeImageResident                                       = (pfn_xeDeviceMakeImageResident_t)LOAD_FUNCTION_PTR(handle, "xeDeviceMakeImageResident");
    pfntable->xeDeviceEvictImage                                              = (pfn_xeDeviceEvictImage_t)LOAD_FUNCTION_PTR(handle, "xeDeviceEvictImage");
    pfntable->xeSamplerCreate                                                 = (pfn_xeSamplerCreate_t)LOAD_FUNCTION_PTR(handle, "xeSamplerCreate");
    pfntable->xeSamplerDestroy                                                = (pfn_xeSamplerDestroy_t)LOAD_FUNCTION_PTR(handle, "xeSamplerDestroy");

    if(nullptr == pfntable->xeCommandListAppendBarrier)
        return false;
    if(nullptr == pfntable->xeCommandListAppendMemoryRangesBarrier)
        return false;
    if(nullptr == pfntable->xeDeviceSystemBarrier)
        return false;
    #if XE_ENABLE_OCL_INTEROP
    if(nullptr == pfntable->xeDeviceRegisterCLMemory)
        return false;
    #endif // XE_ENABLE_OCL_INTEROP
    #if XE_ENABLE_OCL_INTEROP
    if(nullptr == pfntable->xeDeviceRegisterCLProgram)
        return false;
    #endif // XE_ENABLE_OCL_INTEROP
    #if XE_ENABLE_OCL_INTEROP
    if(nullptr == pfntable->xeDeviceRegisterCLCommandQueue)
        return false;
    #endif // XE_ENABLE_OCL_INTEROP
    if(nullptr == pfntable->xeCommandListCreate)
        return false;
    if(nullptr == pfntable->xeCommandListCreateImmediate)
        return false;
    if(nullptr == pfntable->xeCommandListDestroy)
        return false;
    if(nullptr == pfntable->xeCommandListClose)
        return false;
    if(nullptr == pfntable->xeCommandListReset)
        return false;
    if(nullptr == pfntable->xeCommandListSetParameter)
        return false;
    if(nullptr == pfntable->xeCommandListGetParameter)
        return false;
    if(nullptr == pfntable->xeCommandListResetParameters)
        return false;
    if(nullptr == pfntable->xeCommandListReserveSpace)
        return false;
    if(nullptr == pfntable->xeCommandQueueCreate)
        return false;
    if(nullptr == pfntable->xeCommandQueueDestroy)
        return false;
    if(nullptr == pfntable->xeCommandQueueExecuteCommandLists)
        return false;
    if(nullptr == pfntable->xeCommandQueueSynchronize)
        return false;
    if(nullptr == pfntable->xeCommandListAppendMemoryCopy)
        return false;
    if(nullptr == pfntable->xeCommandListAppendMemorySet)
        return false;
    if(nullptr == pfntable->xeCommandListAppendImageCopy)
        return false;
    if(nullptr == pfntable->xeCommandListAppendImageCopyRegion)
        return false;
    if(nullptr == pfntable->xeCommandListAppendImageCopyToMemory)
        return false;
    if(nullptr == pfntable->xeCommandListAppendImageCopyFromMemory)
        return false;
    if(nullptr == pfntable->xeCommandListAppendMemoryPrefetch)
        return false;
    if(nullptr == pfntable->xeCommandListAppendMemAdvise)
        return false;
    if(nullptr == pfntable->xeDeviceGetCount)
        return false;
    if(nullptr == pfntable->xeDeviceGet)
        return false;
    if(nullptr == pfntable->xeDeviceGetSubDevice)
        return false;
    if(nullptr == pfntable->xeDeviceGetApiVersion)
        return false;
    if(nullptr == pfntable->xeDeviceGetProperties)
        return false;
    if(nullptr == pfntable->xeDeviceGetComputeProperties)
        return false;
    if(nullptr == pfntable->xeDeviceGetMemoryProperties)
        return false;
    if(nullptr == pfntable->xeDeviceGetP2PProperties)
        return false;
    if(nullptr == pfntable->xeDeviceCanAccessPeer)
        return false;
    if(nullptr == pfntable->xeDeviceSetIntermediateCacheConfig)
        return false;
    if(nullptr == pfntable->xeDeviceSetLastLevelCacheConfig)
        return false;
    if(nullptr == pfntable->xeInit)
        return false;
    if(nullptr == pfntable->xeGetDriverVersion)
        return false;
    if(nullptr == pfntable->xeEventPoolCreate)
        return false;
    if(nullptr == pfntable->xeEventPoolDestroy)
        return false;
    if(nullptr == pfntable->xeEventCreate)
        return false;
    if(nullptr == pfntable->xeEventDestroy)
        return false;
    if(nullptr == pfntable->xeEventPoolGetIpcHandle)
        return false;
    if(nullptr == pfntable->xeEventPoolOpenIpcHandle)
        return false;
    if(nullptr == pfntable->xeEventPoolCloseIpcHandle)
        return false;
    if(nullptr == pfntable->xeCommandListAppendSignalEvent)
        return false;
    if(nullptr == pfntable->xeCommandListAppendWaitOnEvents)
        return false;
    if(nullptr == pfntable->xeEventHostSignal)
        return false;
    if(nullptr == pfntable->xeEventHostSynchronize)
        return false;
    if(nullptr == pfntable->xeEventQueryStatus)
        return false;
    if(nullptr == pfntable->xeCommandListAppendEventReset)
        return false;
    if(nullptr == pfntable->xeEventReset)
        return false;
    if(nullptr == pfntable->xeFenceCreate)
        return false;
    if(nullptr == pfntable->xeFenceDestroy)
        return false;
    if(nullptr == pfntable->xeFenceHostSynchronize)
        return false;
    if(nullptr == pfntable->xeFenceQueryStatus)
        return false;
    if(nullptr == pfntable->xeFenceReset)
        return false;
    if(nullptr == pfntable->xeImageGetProperties)
        return false;
    if(nullptr == pfntable->xeImageCreate)
        return false;
    if(nullptr == pfntable->xeImageDestroy)
        return false;
    if(nullptr == pfntable->xeSharedMemAlloc)
        return false;
    if(nullptr == pfntable->xeMemAlloc)
        return false;
    if(nullptr == pfntable->xeHostMemAlloc)
        return false;
    if(nullptr == pfntable->xeMemFree)
        return false;
    if(nullptr == pfntable->xeMemGetProperties)
        return false;
    if(nullptr == pfntable->xeMemGetAddressRange)
        return false;
    if(nullptr == pfntable->xeIpcGetMemHandle)
        return false;
    if(nullptr == pfntable->xeIpcOpenMemHandle)
        return false;
    if(nullptr == pfntable->xeIpcCloseMemHandle)
        return false;
    if(nullptr == pfntable->xeModuleCreate)
        return false;
    if(nullptr == pfntable->xeModuleDestroy)
        return false;
    if(nullptr == pfntable->xeModuleBuildLogDestroy)
        return false;
    if(nullptr == pfntable->xeModuleBuildLogGetString)
        return false;
    if(nullptr == pfntable->xeModuleGetNativeBinary)
        return false;
    if(nullptr == pfntable->xeModuleGetGlobalPointer)
        return false;
    if(nullptr == pfntable->xeFunctionCreate)
        return false;
    if(nullptr == pfntable->xeFunctionDestroy)
        return false;
    if(nullptr == pfntable->xeModuleGetFunctionPointer)
        return false;
    if(nullptr == pfntable->xeFunctionSetGroupSize)
        return false;
    if(nullptr == pfntable->xeFunctionSuggestGroupSize)
        return false;
    if(nullptr == pfntable->xeFunctionSetArgumentValue)
        return false;
    if(nullptr == pfntable->xeFunctionSetAttribute)
        return false;
    if(nullptr == pfntable->xeFunctionGetAttribute)
        return false;
    if(nullptr == pfntable->xeCommandListAppendLaunchFunction)
        return false;
    if(nullptr == pfntable->xeCommandListAppendLaunchFunctionIndirect)
        return false;
    if(nullptr == pfntable->xeCommandListAppendLaunchMultipleFunctionsIndirect)
        return false;
    if(nullptr == pfntable->xeCommandListAppendLaunchHostFunction)
        return false;
    if(nullptr == pfntable->xeDeviceMakeMemoryResident)
        return false;
    if(nullptr == pfntable->xeDeviceEvictMemory)
        return false;
    if(nullptr == pfntable->xeDeviceMakeImageResident)
        return false;
    if(nullptr == pfntable->xeDeviceEvictImage)
        return false;
    if(nullptr == pfntable->xeSamplerCreate)
        return false;
    if(nullptr == pfntable->xeSamplerDestroy)
        return false;

    return true;
}

///////////////////////////////////////////////////////////////////////////////
extern context_t context;

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
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListAppendBarrier(hCommandList, hSignalEvent, numWaitEvents, phWaitEvents);
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
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListAppendMemoryRangesBarrier(hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceSystemBarrier(
        xe_device_handle_t hDevice                      ///< [in] handle of the device
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeDeviceSystemBarrier(hDevice);
}

///////////////////////////////////////////////////////////////////////////////
#if XE_ENABLE_OCL_INTEROP
__xedllexport xe_result_t __xecall
xeDeviceRegisterCLMemory(
        xe_device_handle_t hDevice,                     ///< [in] handle to the device
        cl_context context,                             ///< [in] the OpenCL context that created the memory
        cl_mem mem,                                     ///< [in] the OpenCL memory to register
        void** ptr                                      ///< [out] pointer to device allocation
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeDeviceRegisterCLMemory(hDevice, context, mem, ptr);
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
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeDeviceRegisterCLProgram(hDevice, context, program, phModule);
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
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeDeviceRegisterCLCommandQueue(hDevice, context, command_queue, phCommandQueue);
}
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        const xe_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
        xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListCreate(hDevice, desc, phCommandList);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListCreateImmediate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
        xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListCreateImmediate(hDevice, desc, phCommandList);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListDestroy(
        xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to destroy
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListDestroy(hCommandList);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListClose(
        xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListClose(hCommandList);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListReset(
        xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListReset(hCommandList);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListSetParameter(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_command_list_parameter_t parameter,          ///< [in] parameter to change
        uint32_t value                                  ///< [in] value of attribute
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListSetParameter(hCommandList, parameter, value);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListGetParameter(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_command_list_parameter_t parameter,          ///< [in] parameter to retrieve
        uint32_t* value                                 ///< [out] value of attribute
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListGetParameter(hCommandList, parameter, value);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListResetParameters(
        xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListResetParameters(hCommandList);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListReserveSpace(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        size_t size,                                    ///< [in] size (in bytes) to reserve
        void** ptr                                      ///< [out] pointer to command buffer space reserved
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListReserveSpace(hCommandList, size, ptr);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandQueueCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
        xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandQueueCreate(hDevice, desc, phCommandQueue);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandQueueDestroy(
        xe_command_queue_handle_t hCommandQueue         ///< [in] handle of command queue object to destroy
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandQueueDestroy(hCommandQueue);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandQueueExecuteCommandLists(
        xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
        uint32_t numCommandLists,                       ///< [in] number of command lists to execute
        xe_command_list_handle_t* phCommandLists,       ///< [in] list of handles of the command lists to execute
        xe_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandQueueExecuteCommandLists(hCommandQueue, numCommandLists, phCommandLists, hFence);
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
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandQueueSynchronize(hCommandQueue, timeout);
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
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListAppendMemoryCopy(hCommandList, dstptr, srcptr, size, hSignalEvent, numWaitEvents, phWaitEvents);
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
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListAppendMemorySet(hCommandList, ptr, value, size, hSignalEvent, numWaitEvents, phWaitEvents);
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
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListAppendImageCopy(hCommandList, hDstImage, hSrcImage, hSignalEvent, numWaitEvents, phWaitEvents);
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
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListAppendImageCopyRegion(hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents);
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
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListAppendImageCopyToMemory(hCommandList, dstptr, hSrcImage, pSrcRegion, hSignalEvent, numWaitEvents, phWaitEvents);
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
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListAppendImageCopyFromMemory(hCommandList, hDstImage, srcptr, pDstRegion, hSignalEvent, numWaitEvents, phWaitEvents);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListAppendMemoryPrefetch(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
        size_t count                                    ///< [in] size in bytes of the memory range to prefetch
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListAppendMemoryPrefetch(hCommandList, ptr, count);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListAppendMemAdvise(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
        xe_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
        const void* ptr,                                ///< [in] Pointer to the start of the memory range
        size_t size,                                    ///< [in] Size in bytes of the memory range
        xe_memory_advice_t advice                       ///< [in] Memory advice for the memory range
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListAppendMemAdvise(hCommandList, hDevice, ptr, size, advice);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceGetCount(
        uint32_t* count                                 ///< [out] number of devices available
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeDeviceGetCount(count);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceGet(
        uint32_t ordinal,                               ///< [in] The device index in the range of [0, ::xeDeviceGetCount]
        xe_device_handle_t* phDevice                    ///< [out] pointer to handle of device object created
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeDeviceGet(ordinal, phDevice);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceGetSubDevice(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        uint32_t ordinal,                               ///< [in] ordinal of sub-device to retrieve
        xe_device_handle_t* phSubDevice                 ///< [out] pointer to handle of sub-device object.
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeDeviceGetSubDevice(hDevice, ordinal, phSubDevice);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceGetApiVersion(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        xe_api_version_t* version                       ///< [out] api version
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeDeviceGetApiVersion(hDevice, version);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceGetProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        xe_device_properties_t* pDeviceProperties       ///< [out] query result for device properties
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeDeviceGetProperties(hDevice, pDeviceProperties);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceGetComputeProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        xe_device_compute_properties_t* pComputeProperties  ///< [out] query result for compute properties
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeDeviceGetComputeProperties(hDevice, pComputeProperties);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceGetMemoryProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        xe_device_memory_properties_t* pMemProperties   ///< [out] query result for compute properties
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeDeviceGetMemoryProperties(hDevice, pMemProperties);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceGetP2PProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        xe_device_p2p_properties_t* pP2PProperties      ///< [out] Peer-to-Peer properties between source and peer device
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeDeviceGetP2PProperties(hDevice, hPeerDevice, pP2PProperties);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceCanAccessPeer(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
        xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
        xe_bool_t* value                                ///< [out] returned access capability
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeDeviceCanAccessPeer(hDevice, hPeerDevice, value);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceSetIntermediateCacheConfig(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device 
        xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeDeviceSetIntermediateCacheConfig(hDevice, CacheConfig);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceSetLastLevelCacheConfig(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device 
        xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeDeviceSetLastLevelCacheConfig(hDevice, CacheConfig);
}


///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeGetDriverVersion(
        uint32_t* version                               ///< [out] driver version
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeGetDriverVersion(version);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeEventPoolCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
        xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeEventPoolCreate(hDevice, desc, phEventPool);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeEventPoolDestroy(
        xe_event_pool_handle_t hEventPool               ///< [in] handle of event pool object to destroy
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeEventPoolDestroy(hEventPool);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeEventCreate(
        xe_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
        const xe_event_desc_t* desc,                    ///< [in] pointer to event descriptor
        xe_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeEventCreate(hEventPool, desc, phEvent);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeEventDestroy(
        xe_event_handle_t hEvent                        ///< [in] handle of event object to destroy
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeEventDestroy(hEvent);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeEventPoolGetIpcHandle(
        xe_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
        xe_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeEventPoolGetIpcHandle(hEventPool, phIpc);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeEventPoolOpenIpcHandle(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC event pool handle
        xe_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event handle
        xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeEventPoolOpenIpcHandle(hDevice, hIpc, phEventPool);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeEventPoolCloseIpcHandle(
        xe_event_pool_handle_t hEventPool               ///< [in] handle of event pool object
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeEventPoolCloseIpcHandle(hEventPool);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListAppendSignalEvent(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListAppendSignalEvent(hCommandList, hEvent);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListAppendWaitOnEvents(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
        xe_event_handle_t* phEvents                     ///< [in] handle of the events to wait on before continuing
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListAppendWaitOnEvents(hCommandList, numEvents, phEvents);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeEventHostSignal(
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeEventHostSignal(hEvent);
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
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeEventHostSynchronize(hEvent, timeout);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeEventQueryStatus(
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeEventQueryStatus(hEvent);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListAppendEventReset(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListAppendEventReset(hCommandList, hEvent);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeEventReset(
        xe_event_handle_t hEvent                        ///< [in] handle of the event
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeEventReset(hEvent);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeFenceCreate(
        xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
        const xe_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
        xe_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeFenceCreate(hCommandQueue, desc, phFence);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeFenceDestroy(
        xe_fence_handle_t hFence                        ///< [in] handle of fence object to destroy
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeFenceDestroy(hFence);
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
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeFenceHostSynchronize(hFence, timeout);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeFenceQueryStatus(
        xe_fence_handle_t hFence                        ///< [in] handle of the fence
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeFenceQueryStatus(hFence);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeFenceReset(
        xe_fence_handle_t hFence                        ///< [in] handle of the fence
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeFenceReset(hFence);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeImageGetProperties(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        xe_image_properties_t* pImageProperties         ///< [out] pointer to image properties
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeImageGetProperties(hDevice, desc, pImageProperties);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeImageCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
        xe_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeImageCreate(hDevice, desc, phImage);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeImageDestroy(
        xe_image_handle_t hImage                        ///< [in] handle of image object to destroy
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeImageDestroy(hImage);
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
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeSharedMemAlloc(hDevice, device_flags, host_flags, size, alignment, ptr);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeMemAlloc(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_device_mem_alloc_flag_t flags,               ///< [in] flags specifying additional allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** ptr                                      ///< [out] pointer to device allocation
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeMemAlloc(hDevice, flags, size, alignment, ptr);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeHostMemAlloc(
        xe_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
        size_t size,                                    ///< [in] size in bytes to allocate
        size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
        void** ptr                                      ///< [out] pointer to host allocation
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeHostMemAlloc(flags, size, alignment, ptr);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeMemFree(
        const void* ptr                                 ///< [in] pointer to memory to free
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeMemFree(ptr);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeMemGetProperties(
        const void* ptr,                                ///< [in] Pointer to query
        xe_memory_allocation_properties_t* pMemProperties   ///< [out] Query result for memory allocation properties
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeMemGetProperties(ptr, pMemProperties);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeMemGetAddressRange(
        const void* ptr,                                ///< [in] Pointer to query
        void** pBase,                                   ///< [in,out][optional] base address of the allocation
        size_t* pSize                                   ///< [in,out][optional] size of the allocation
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeMemGetAddressRange(ptr, pBase, pSize);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeIpcGetMemHandle(
        const void* ptr,                                ///< [in] Pointer to the device memory allocation
        xe_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeIpcGetMemHandle(ptr, pIpcHandle);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeIpcOpenMemHandle(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
        xe_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
        xe_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
        void** ptr                                      ///< [out] pointer to device allocation in this process
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeIpcOpenMemHandle(hDevice, handle, flags, ptr);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeIpcCloseMemHandle(
        const void* ptr                                 ///< [in] pointer to device allocation in this process
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeIpcCloseMemHandle(ptr);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeModuleCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_module_desc_t* pDesc,                  ///< [in] pointer to module descriptor
        xe_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
        xe_module_build_log_handle_t* phBuildLog        ///< [in,out][optional] pointer to handle of module's build log.
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeModuleCreate(hDevice, pDesc, phModule, phBuildLog);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeModuleDestroy(
        xe_module_handle_t hModule                      ///< [in] handle of the module
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeModuleDestroy(hModule);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeModuleBuildLogDestroy(
        xe_module_build_log_handle_t hModuleBuildLog    ///< [in] handle of the module build log object.
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeModuleBuildLogDestroy(hModuleBuildLog);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeModuleBuildLogGetString(
        xe_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
        size_t* pSize,                                  ///< [in,out] size of build log string.
        char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeModuleBuildLogGetString(hModuleBuildLog, pSize, pBuildLog);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeModuleGetNativeBinary(
        xe_module_handle_t hModule,                     ///< [in] handle of the device
        size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
        uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeModuleGetNativeBinary(hModule, pSize, pModuleNativeBinary);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeModuleGetGlobalPointer(
        xe_module_handle_t hModule,                     ///< [in] handle of the device
        const char* pGlobalName,                        ///< [in] name of function in global
        void** pPtr                                     ///< [out] device visible pointer
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeModuleGetGlobalPointer(hModule, pGlobalName, pPtr);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeFunctionCreate(
        xe_module_handle_t hModule,                     ///< [in] handle of the module
        const xe_function_desc_t* pDesc,                ///< [in] pointer to function descriptor
        xe_function_handle_t* phFunction                ///< [out] handle of the Function object
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeFunctionCreate(hModule, pDesc, phFunction);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeFunctionDestroy(
        xe_function_handle_t hFunction                  ///< [in] handle of the function object
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeFunctionDestroy(hFunction);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeModuleGetFunctionPointer(
        xe_module_handle_t hModule,                     ///< [in] handle of the module
        const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
        void** pfnFunction                              ///< [out] pointer to function.
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeModuleGetFunctionPointer(hModule, pFunctionName, pfnFunction);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeFunctionSetGroupSize(
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this function.
        uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this function.
        uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this function.
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeFunctionSetGroupSize(hFunction, groupSizeX, groupSizeY, groupSizeZ);
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
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeFunctionSuggestGroupSize(hFunction, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeFunctionSetArgumentValue(
        xe_function_handle_t hFunction,                 ///< [in,out] handle of the function args object.
        uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
        size_t argSize,                                 ///< [in] size of argument type
        const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                        ///< null then argument value is considered null.
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeFunctionSetArgumentValue(hFunction, argIndex, argSize, pArgValue);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeFunctionSetAttribute(
        xe_function_handle_t hFunction,                 ///< [in,out] handle of the function.
        xe_function_set_attribute_t attr,               ///< [in] attribute to set
        uint32_t value                                  ///< [in] attribute value to set
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeFunctionSetAttribute(hFunction, attr, value);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeFunctionGetAttribute(
        xe_function_handle_t hFunction,                 ///< [in] handle of the function object
        xe_function_get_attribute_t attr,               ///< [in] attribute to query
        uint32_t* pValue                                ///< [out] returned attribute value
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeFunctionGetAttribute(hFunction, attr, pValue);
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
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListAppendLaunchFunction(hCommandList, hFunction, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents);
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
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListAppendLaunchFunctionIndirect(hCommandList, hFunction, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents);
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
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListAppendLaunchMultipleFunctionsIndirect(hCommandList, numFunctions, phFunctions, pNumLaunchArguments, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeCommandListAppendLaunchHostFunction(
        xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
        xe_host_pfn_t pfnHostFunc,                      ///< [in] pointer to host function.
        void* pUserData                                 ///< [in] pointer to user data to pass to host function.
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeCommandListAppendLaunchHostFunction(hCommandList, pfnHostFunc, pUserData);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceMakeMemoryResident(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to make resident
        size_t size                                     ///< [in] size in bytes to make resident
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeDeviceMakeMemoryResident(hDevice, ptr, size);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceEvictMemory(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        void* ptr,                                      ///< [in] pointer to memory to evict
        size_t size                                     ///< [in] size in bytes to evict
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeDeviceEvictMemory(hDevice, ptr, size);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceMakeImageResident(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_image_handle_t hImage                        ///< [in] handle of image to make resident
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeDeviceMakeImageResident(hDevice, hImage);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeDeviceEvictImage(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        xe_image_handle_t hImage                        ///< [in] handle of image to make evict
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeDeviceEvictImage(hDevice, hImage);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeSamplerCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device
        const xe_sampler_desc_t* pDesc,                 ///< [in] pointer to sampler descriptor
        xe_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeSamplerCreate(hDevice, pDesc, phSampler);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xeSamplerDestroy(
        xe_sampler_handle_t hSampler                    ///< [in] handle of the sampler
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xeapi->xeSamplerDestroy(hSampler);
}

#if defined(__cplusplus)
};
#endif
