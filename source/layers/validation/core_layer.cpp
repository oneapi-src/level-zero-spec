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
* DO NOT EDIT: generated from /scripts/templates/validation.cpp.mako
* @endcond
*
******************************************************************************/
#include "layer.h"

extern xe_layer context;

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetCommandListProcAddrTable(
    xe_api_version_t version, ///< [in] API version
    xe_command_list_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_PARAMETER;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    context.xeCommandList.pfnCreate                                               = ptable->pfnCreate;
    ptable->pfnCreate                                                             = xeCommandListCreate;

    context.xeCommandList.pfnCreateImmediate                                      = ptable->pfnCreateImmediate;
    ptable->pfnCreateImmediate                                                    = xeCommandListCreateImmediate;

    context.xeCommandList.pfnDestroy                                              = ptable->pfnDestroy;
    ptable->pfnDestroy                                                            = xeCommandListDestroy;

    context.xeCommandList.pfnClose                                                = ptable->pfnClose;
    ptable->pfnClose                                                              = xeCommandListClose;

    context.xeCommandList.pfnReset                                                = ptable->pfnReset;
    ptable->pfnReset                                                              = xeCommandListReset;

    context.xeCommandList.pfnSetParameter                                         = ptable->pfnSetParameter;
    ptable->pfnSetParameter                                                       = xeCommandListSetParameter;

    context.xeCommandList.pfnGetParameter                                         = ptable->pfnGetParameter;
    ptable->pfnGetParameter                                                       = xeCommandListGetParameter;

    context.xeCommandList.pfnResetParameters                                      = ptable->pfnResetParameters;
    ptable->pfnResetParameters                                                    = xeCommandListResetParameters;

    context.xeCommandList.pfnReserveSpace                                         = ptable->pfnReserveSpace;
    ptable->pfnReserveSpace                                                       = xeCommandListReserveSpace;

    context.xeCommandList.pfnAppendBarrier                                        = ptable->pfnAppendBarrier;
    ptable->pfnAppendBarrier                                                      = xeCommandListAppendBarrier;

    context.xeCommandList.pfnAppendMemoryRangesBarrier                            = ptable->pfnAppendMemoryRangesBarrier;
    ptable->pfnAppendMemoryRangesBarrier                                          = xeCommandListAppendMemoryRangesBarrier;

    context.xeCommandList.pfnAppendMemoryCopy                                     = ptable->pfnAppendMemoryCopy;
    ptable->pfnAppendMemoryCopy                                                   = xeCommandListAppendMemoryCopy;

    context.xeCommandList.pfnAppendMemorySet                                      = ptable->pfnAppendMemorySet;
    ptable->pfnAppendMemorySet                                                    = xeCommandListAppendMemorySet;

    context.xeCommandList.pfnAppendMemoryCopyRegion                               = ptable->pfnAppendMemoryCopyRegion;
    ptable->pfnAppendMemoryCopyRegion                                             = xeCommandListAppendMemoryCopyRegion;

    context.xeCommandList.pfnAppendImageCopy                                      = ptable->pfnAppendImageCopy;
    ptable->pfnAppendImageCopy                                                    = xeCommandListAppendImageCopy;

    context.xeCommandList.pfnAppendImageCopyRegion                                = ptable->pfnAppendImageCopyRegion;
    ptable->pfnAppendImageCopyRegion                                              = xeCommandListAppendImageCopyRegion;

    context.xeCommandList.pfnAppendImageCopyToMemory                              = ptable->pfnAppendImageCopyToMemory;
    ptable->pfnAppendImageCopyToMemory                                            = xeCommandListAppendImageCopyToMemory;

    context.xeCommandList.pfnAppendImageCopyFromMemory                            = ptable->pfnAppendImageCopyFromMemory;
    ptable->pfnAppendImageCopyFromMemory                                          = xeCommandListAppendImageCopyFromMemory;

    context.xeCommandList.pfnAppendMemoryPrefetch                                 = ptable->pfnAppendMemoryPrefetch;
    ptable->pfnAppendMemoryPrefetch                                               = xeCommandListAppendMemoryPrefetch;

    context.xeCommandList.pfnAppendMemAdvise                                      = ptable->pfnAppendMemAdvise;
    ptable->pfnAppendMemAdvise                                                    = xeCommandListAppendMemAdvise;

    context.xeCommandList.pfnAppendSignalEvent                                    = ptable->pfnAppendSignalEvent;
    ptable->pfnAppendSignalEvent                                                  = xeCommandListAppendSignalEvent;

    context.xeCommandList.pfnAppendWaitOnEvents                                   = ptable->pfnAppendWaitOnEvents;
    ptable->pfnAppendWaitOnEvents                                                 = xeCommandListAppendWaitOnEvents;

    context.xeCommandList.pfnAppendEventReset                                     = ptable->pfnAppendEventReset;
    ptable->pfnAppendEventReset                                                   = xeCommandListAppendEventReset;

    context.xeCommandList.pfnAppendLaunchFunction                                 = ptable->pfnAppendLaunchFunction;
    ptable->pfnAppendLaunchFunction                                               = xeCommandListAppendLaunchFunction;

    context.xeCommandList.pfnAppendLaunchFunctionIndirect                         = ptable->pfnAppendLaunchFunctionIndirect;
    ptable->pfnAppendLaunchFunctionIndirect                                       = xeCommandListAppendLaunchFunctionIndirect;

    context.xeCommandList.pfnAppendLaunchMultipleFunctionsIndirect                = ptable->pfnAppendLaunchMultipleFunctionsIndirect;
    ptable->pfnAppendLaunchMultipleFunctionsIndirect                              = xeCommandListAppendLaunchMultipleFunctionsIndirect;

    context.xeCommandList.pfnAppendLaunchHostFunction                             = ptable->pfnAppendLaunchHostFunction;
    ptable->pfnAppendLaunchHostFunction                                           = xeCommandListAppendLaunchHostFunction;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetDeviceProcAddrTable(
    xe_api_version_t version, ///< [in] API version
    xe_device_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_PARAMETER;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    context.xeDevice.pfnGetSubDevice                                         = ptable->pfnGetSubDevice;
    ptable->pfnGetSubDevice                                                  = xeDeviceGetSubDevice;

    context.xeDevice.pfnGetP2PProperties                                     = ptable->pfnGetP2PProperties;
    ptable->pfnGetP2PProperties                                              = xeDeviceGetP2PProperties;

    context.xeDevice.pfnCanAccessPeer                                        = ptable->pfnCanAccessPeer;
    ptable->pfnCanAccessPeer                                                 = xeDeviceCanAccessPeer;

    context.xeDevice.pfnSetIntermediateCacheConfig                           = ptable->pfnSetIntermediateCacheConfig;
    ptable->pfnSetIntermediateCacheConfig                                    = xeDeviceSetIntermediateCacheConfig;

    context.xeDevice.pfnSetLastLevelCacheConfig                              = ptable->pfnSetLastLevelCacheConfig;
    ptable->pfnSetLastLevelCacheConfig                                       = xeDeviceSetLastLevelCacheConfig;

    context.xeDevice.pfnSystemBarrier                                        = ptable->pfnSystemBarrier;
    ptable->pfnSystemBarrier                                                 = xeDeviceSystemBarrier;

#if XE_ENABLE_OCL_INTEROP
    context.xeDevice.pfnRegisterCLMemory                                     = ptable->pfnRegisterCLMemory;
    ptable->pfnRegisterCLMemory                                              = xeDeviceRegisterCLMemory;
#endif

#if XE_ENABLE_OCL_INTEROP
    context.xeDevice.pfnRegisterCLProgram                                    = ptable->pfnRegisterCLProgram;
    ptable->pfnRegisterCLProgram                                             = xeDeviceRegisterCLProgram;
#endif

#if XE_ENABLE_OCL_INTEROP
    context.xeDevice.pfnRegisterCLCommandQueue                               = ptable->pfnRegisterCLCommandQueue;
    ptable->pfnRegisterCLCommandQueue                                        = xeDeviceRegisterCLCommandQueue;
#endif

    context.xeDevice.pfnMakeMemoryResident                                   = ptable->pfnMakeMemoryResident;
    ptable->pfnMakeMemoryResident                                            = xeDeviceMakeMemoryResident;

    context.xeDevice.pfnEvictMemory                                          = ptable->pfnEvictMemory;
    ptable->pfnEvictMemory                                                   = xeDeviceEvictMemory;

    context.xeDevice.pfnMakeImageResident                                    = ptable->pfnMakeImageResident;
    ptable->pfnMakeImageResident                                             = xeDeviceMakeImageResident;

    context.xeDevice.pfnEvictImage                                           = ptable->pfnEvictImage;
    ptable->pfnEvictImage                                                    = xeDeviceEvictImage;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandQueue table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetCommandQueueProcAddrTable(
    xe_api_version_t version, ///< [in] API version
    xe_command_queue_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_PARAMETER;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    context.xeCommandQueue.pfnCreate                                               = ptable->pfnCreate;
    ptable->pfnCreate                                                              = xeCommandQueueCreate;

    context.xeCommandQueue.pfnDestroy                                              = ptable->pfnDestroy;
    ptable->pfnDestroy                                                             = xeCommandQueueDestroy;

    context.xeCommandQueue.pfnExecuteCommandLists                                  = ptable->pfnExecuteCommandLists;
    ptable->pfnExecuteCommandLists                                                 = xeCommandQueueExecuteCommandLists;

    context.xeCommandQueue.pfnSynchronize                                          = ptable->pfnSynchronize;
    ptable->pfnSynchronize                                                         = xeCommandQueueSynchronize;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Context table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetContextProcAddrTable(
    xe_api_version_t version, ///< [in] API version
    xe_context_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_PARAMETER;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    context.xeContext.pfnCreate                                               = ptable->pfnCreate;
    ptable->pfnCreate                                                         = xeContextCreate;

    context.xeContext.pfnDestroy                                              = ptable->pfnDestroy;
    ptable->pfnDestroy                                                        = xeContextDestroy;

    context.xeContext.pfnAllocSharedMem                                       = ptable->pfnAllocSharedMem;
    ptable->pfnAllocSharedMem                                                 = xeContextAllocSharedMem;

    context.xeContext.pfnAllocDeviceMem                                       = ptable->pfnAllocDeviceMem;
    ptable->pfnAllocDeviceMem                                                 = xeContextAllocDeviceMem;

    context.xeContext.pfnAllocHostMem                                         = ptable->pfnAllocHostMem;
    ptable->pfnAllocHostMem                                                   = xeContextAllocHostMem;

    context.xeContext.pfnFreeMem                                              = ptable->pfnFreeMem;
    ptable->pfnFreeMem                                                        = xeContextFreeMem;

    context.xeContext.pfnGetMemProperties                                     = ptable->pfnGetMemProperties;
    ptable->pfnGetMemProperties                                               = xeContextGetMemProperties;

    context.xeContext.pfnGetMemAddressRange                                   = ptable->pfnGetMemAddressRange;
    ptable->pfnGetMemAddressRange                                             = xeContextGetMemAddressRange;

    context.xeContext.pfnGetMemIpcHandle                                      = ptable->pfnGetMemIpcHandle;
    ptable->pfnGetMemIpcHandle                                                = xeContextGetMemIpcHandle;

    context.xeContext.pfnOpenMemIpcHandle                                     = ptable->pfnOpenMemIpcHandle;
    ptable->pfnOpenMemIpcHandle                                               = xeContextOpenMemIpcHandle;

    context.xeContext.pfnCloseMemIpcHandle                                    = ptable->pfnCloseMemIpcHandle;
    ptable->pfnCloseMemIpcHandle                                              = xeContextCloseMemIpcHandle;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's DeviceGroup table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetDeviceGroupProcAddrTable(
    xe_api_version_t version, ///< [in] API version
    xe_device_group_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_PARAMETER;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    context.xeDeviceGroup.pfnGetDriverVersion                                     = ptable->pfnGetDriverVersion;
    ptable->pfnGetDriverVersion                                                   = xeDeviceGroupGetDriverVersion;

    context.xeDeviceGroup.pfnGetDevices                                           = ptable->pfnGetDevices;
    ptable->pfnGetDevices                                                         = xeDeviceGroupGetDevices;

    context.xeDeviceGroup.pfnGetApiVersion                                        = ptable->pfnGetApiVersion;
    ptable->pfnGetApiVersion                                                      = xeDeviceGroupGetApiVersion;

    context.xeDeviceGroup.pfnGetProperties                                        = ptable->pfnGetProperties;
    ptable->pfnGetProperties                                                      = xeDeviceGroupGetProperties;

    context.xeDeviceGroup.pfnGetComputeProperties                                 = ptable->pfnGetComputeProperties;
    ptable->pfnGetComputeProperties                                               = xeDeviceGroupGetComputeProperties;

    context.xeDeviceGroup.pfnGetMemoryProperties                                  = ptable->pfnGetMemoryProperties;
    ptable->pfnGetMemoryProperties                                                = xeDeviceGroupGetMemoryProperties;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Fence table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetFenceProcAddrTable(
    xe_api_version_t version, ///< [in] API version
    xe_fence_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_PARAMETER;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    context.xeFence.pfnCreate                                               = ptable->pfnCreate;
    ptable->pfnCreate                                                       = xeFenceCreate;

    context.xeFence.pfnDestroy                                              = ptable->pfnDestroy;
    ptable->pfnDestroy                                                      = xeFenceDestroy;

    context.xeFence.pfnHostSynchronize                                      = ptable->pfnHostSynchronize;
    ptable->pfnHostSynchronize                                              = xeFenceHostSynchronize;

    context.xeFence.pfnQueryStatus                                          = ptable->pfnQueryStatus;
    ptable->pfnQueryStatus                                                  = xeFenceQueryStatus;

    context.xeFence.pfnReset                                                = ptable->pfnReset;
    ptable->pfnReset                                                        = xeFenceReset;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's EventPool table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetEventPoolProcAddrTable(
    xe_api_version_t version, ///< [in] API version
    xe_event_pool_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_PARAMETER;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    context.xeEventPool.pfnCreate                                               = ptable->pfnCreate;
    ptable->pfnCreate                                                           = xeEventPoolCreate;

    context.xeEventPool.pfnDestroy                                              = ptable->pfnDestroy;
    ptable->pfnDestroy                                                          = xeEventPoolDestroy;

    context.xeEventPool.pfnGetIpcHandle                                         = ptable->pfnGetIpcHandle;
    ptable->pfnGetIpcHandle                                                     = xeEventPoolGetIpcHandle;

    context.xeEventPool.pfnOpenIpcHandle                                        = ptable->pfnOpenIpcHandle;
    ptable->pfnOpenIpcHandle                                                    = xeEventPoolOpenIpcHandle;

    context.xeEventPool.pfnCloseIpcHandle                                       = ptable->pfnCloseIpcHandle;
    ptable->pfnCloseIpcHandle                                                   = xeEventPoolCloseIpcHandle;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Event table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetEventProcAddrTable(
    xe_api_version_t version, ///< [in] API version
    xe_event_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_PARAMETER;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    context.xeEvent.pfnCreate                                               = ptable->pfnCreate;
    ptable->pfnCreate                                                       = xeEventCreate;

    context.xeEvent.pfnDestroy                                              = ptable->pfnDestroy;
    ptable->pfnDestroy                                                      = xeEventDestroy;

    context.xeEvent.pfnHostSignal                                           = ptable->pfnHostSignal;
    ptable->pfnHostSignal                                                   = xeEventHostSignal;

    context.xeEvent.pfnHostSynchronize                                      = ptable->pfnHostSynchronize;
    ptable->pfnHostSynchronize                                              = xeEventHostSynchronize;

    context.xeEvent.pfnQueryStatus                                          = ptable->pfnQueryStatus;
    ptable->pfnQueryStatus                                                  = xeEventQueryStatus;

    context.xeEvent.pfnReset                                                = ptable->pfnReset;
    ptable->pfnReset                                                        = xeEventReset;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Image table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetImageProcAddrTable(
    xe_api_version_t version, ///< [in] API version
    xe_image_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_PARAMETER;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    context.xeImage.pfnGetProperties                                        = ptable->pfnGetProperties;
    ptable->pfnGetProperties                                                = xeImageGetProperties;

    context.xeImage.pfnCreate                                               = ptable->pfnCreate;
    ptable->pfnCreate                                                       = xeImageCreate;

    context.xeImage.pfnDestroy                                              = ptable->pfnDestroy;
    ptable->pfnDestroy                                                      = xeImageDestroy;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetModuleProcAddrTable(
    xe_api_version_t version, ///< [in] API version
    xe_module_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_PARAMETER;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    context.xeModule.pfnCreate                                               = ptable->pfnCreate;
    ptable->pfnCreate                                                        = xeModuleCreate;

    context.xeModule.pfnDestroy                                              = ptable->pfnDestroy;
    ptable->pfnDestroy                                                       = xeModuleDestroy;

    context.xeModule.pfnGetNativeBinary                                      = ptable->pfnGetNativeBinary;
    ptable->pfnGetNativeBinary                                               = xeModuleGetNativeBinary;

    context.xeModule.pfnGetGlobalPointer                                     = ptable->pfnGetGlobalPointer;
    ptable->pfnGetGlobalPointer                                              = xeModuleGetGlobalPointer;

    context.xeModule.pfnGetFunctionPointer                                   = ptable->pfnGetFunctionPointer;
    ptable->pfnGetFunctionPointer                                            = xeModuleGetFunctionPointer;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's ModuleBuildLog table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetModuleBuildLogProcAddrTable(
    xe_api_version_t version, ///< [in] API version
    xe_module_build_log_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_PARAMETER;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    context.xeModuleBuildLog.pfnDestroy                                              = ptable->pfnDestroy;
    ptable->pfnDestroy                                                               = xeModuleBuildLogDestroy;

    context.xeModuleBuildLog.pfnGetString                                            = ptable->pfnGetString;
    ptable->pfnGetString                                                             = xeModuleBuildLogGetString;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Function table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetFunctionProcAddrTable(
    xe_api_version_t version, ///< [in] API version
    xe_function_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_PARAMETER;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    context.xeFunction.pfnCreate                                               = ptable->pfnCreate;
    ptable->pfnCreate                                                          = xeFunctionCreate;

    context.xeFunction.pfnDestroy                                              = ptable->pfnDestroy;
    ptable->pfnDestroy                                                         = xeFunctionDestroy;

    context.xeFunction.pfnSetGroupSize                                         = ptable->pfnSetGroupSize;
    ptable->pfnSetGroupSize                                                    = xeFunctionSetGroupSize;

    context.xeFunction.pfnSuggestGroupSize                                     = ptable->pfnSuggestGroupSize;
    ptable->pfnSuggestGroupSize                                                = xeFunctionSuggestGroupSize;

    context.xeFunction.pfnSetArgumentValue                                     = ptable->pfnSetArgumentValue;
    ptable->pfnSetArgumentValue                                                = xeFunctionSetArgumentValue;

    context.xeFunction.pfnSetAttribute                                         = ptable->pfnSetAttribute;
    ptable->pfnSetAttribute                                                    = xeFunctionSetAttribute;

    context.xeFunction.pfnGetAttribute                                         = ptable->pfnGetAttribute;
    ptable->pfnGetAttribute                                                    = xeFunctionGetAttribute;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sampler table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetSamplerProcAddrTable(
    xe_api_version_t version, ///< [in] API version
    xe_sampler_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_PARAMETER;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    context.xeSampler.pfnCreate                                               = ptable->pfnCreate;
    ptable->pfnCreate                                                         = xeSamplerCreate;

    context.xeSampler.pfnDestroy                                              = ptable->pfnDestroy;
    ptable->pfnDestroy                                                        = xeSamplerDestroy;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Global table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_PARAMETER
///         + invalid value for version
///         + nullptr for ptable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetGlobalProcAddrTable(
    xe_api_version_t version, ///< [in] API version
    xe_global_apitable_t* ptable      ///< [in,out] pointer to table of API function pointers
    )
{
    if( nullptr == ptable )
        return XE_RESULT_ERROR_INVALID_PARAMETER;

    if( context.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    context.xeGlobal.pfnInit                                                 = ptable->pfnInit;
    ptable->pfnInit                                                          = xeInit;

    context.xeGlobal.pfnGetDeviceGroups                                      = ptable->pfnGetDeviceGroups;
    ptable->pfnGetDeviceGroups                                               = xeGetDeviceGroups;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeInit
xe_result_t __xecall
xeInit(
    xe_init_flag_t flags                            ///< [in] initialization flags
    )
{
    if( context.enableParameterValidation )
    {
    }

    return context.xeGlobal.pfnInit( flags );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetDriverVersion
xe_result_t __xecall
xeDeviceGroupGetDriverVersion(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of device group
    uint32_t* version                               ///< [out] driver version
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == version )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeDeviceGroup.pfnGetDriverVersion( hDeviceGroup, version );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextCreate
xe_result_t __xecall
xeContextCreate(
    size_t numDevices,                              ///< [in] number of devices in phDevice
    xe_device_handle_t* phDevice,                   ///< [in] pointer to array of handle of the device objects
    xe_context_handle_t* phContext                  ///< [out] pointer to handle of context object created
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == phDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phContext )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeContext.pfnCreate( numDevices, phDevice, phContext );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextDestroy
xe_result_t __xecall
xeContextDestroy(
    xe_context_handle_t hContext                    ///< [in] handle of context object to destroy
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hContext )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeContext.pfnDestroy( hContext );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeGetDeviceGroups
xe_result_t __xecall
xeGetDeviceGroups(
    size_t* pCount,                                 ///< [in,out] pointer to the number of device groups.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of device groups available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of
                                                    ///< device groups.
    xe_device_group_handle_t* pDeviceGroups         ///< [in,out][optional] array of handle of device groups
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == pCount )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeGlobal.pfnGetDeviceGroups( pCount, pDeviceGroups );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetDevices
xe_result_t __xecall
xeDeviceGroupGetDevices(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    size_t* pCount,                                 ///< [in,out] pointer to the number of device groups.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of device groups available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of
                                                    ///< device groups.
    xe_device_group_handle_t* pDeviceGroups         ///< [in,out][optional] array of handle of device groups
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pCount )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeDeviceGroup.pfnGetDevices( hDeviceGroup, pCount, pDeviceGroups );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGetSubDevice
xe_result_t __xecall
xeDeviceGetSubDevice(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    uint32_t ordinal,                               ///< [in] ordinal of sub-device to retrieve
    xe_device_handle_t* phSubDevice                 ///< [out] pointer to handle of sub-device object.
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phSubDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeDevice.pfnGetSubDevice( hDevice, ordinal, phSubDevice );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetApiVersion
xe_result_t __xecall
xeDeviceGroupGetApiVersion(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_api_version_t* version                       ///< [out] api version
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == version )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeDeviceGroup.pfnGetApiVersion( hDeviceGroup, version );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetProperties
xe_result_t __xecall
xeDeviceGroupGetProperties(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_properties_t* pDeviceProperties       ///< [out] query result for device properties
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pDeviceProperties )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeDeviceGroup.pfnGetProperties( hDeviceGroup, pDeviceProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetComputeProperties
xe_result_t __xecall
xeDeviceGroupGetComputeProperties(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_compute_properties_t* pComputeProperties  ///< [out] query result for compute properties
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pComputeProperties )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeDeviceGroup.pfnGetComputeProperties( hDeviceGroup, pComputeProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetMemoryProperties
xe_result_t __xecall
xeDeviceGroupGetMemoryProperties(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_memory_properties_t* pMemProperties   ///< [out] query result for compute properties
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pMemProperties )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeDeviceGroup.pfnGetMemoryProperties( hDeviceGroup, pMemProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGetP2PProperties
xe_result_t __xecall
xeDeviceGetP2PProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    xe_device_p2p_properties_t* pP2PProperties      ///< [out] Peer-to-Peer properties between source and peer device
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hPeerDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pP2PProperties )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeDevice.pfnGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceCanAccessPeer
xe_result_t __xecall
xeDeviceCanAccessPeer(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device performing the access
    xe_device_handle_t hPeerDevice,                 ///< [in] handle of the peer device with the allocation
    xe_bool_t* value                                ///< [out] returned access capability
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hPeerDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == value )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeDevice.pfnCanAccessPeer( hDevice, hPeerDevice, value );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceSetIntermediateCacheConfig
xe_result_t __xecall
xeDeviceSetIntermediateCacheConfig(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device 
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeDevice.pfnSetIntermediateCacheConfig( hDevice, CacheConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceSetLastLevelCacheConfig
xe_result_t __xecall
xeDeviceSetLastLevelCacheConfig(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device 
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeDevice.pfnSetLastLevelCacheConfig( hDevice, CacheConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandQueueCreate
xe_result_t __xecall
xeCommandQueueCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
    xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == desc )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phCommandQueue )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( XE_COMMAND_QUEUE_DESC_VERSION_CURRENT < desc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return context.xeCommandQueue.pfnCreate( hDevice, desc, phCommandQueue );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandQueueDestroy
xe_result_t __xecall
xeCommandQueueDestroy(
    xe_command_queue_handle_t hCommandQueue         ///< [in] handle of command queue object to destroy
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandQueue )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandQueue.pfnDestroy( hCommandQueue );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandQueueExecuteCommandLists
xe_result_t __xecall
xeCommandQueueExecuteCommandLists(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint32_t numCommandLists,                       ///< [in] number of command lists to execute
    xe_command_list_handle_t* phCommandLists,       ///< [in] list of handles of the command lists to execute
    xe_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandQueue )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phCommandLists )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandQueue.pfnExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandQueueSynchronize
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
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandQueue )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandQueue.pfnSynchronize( hCommandQueue, timeout );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListCreate
xe_result_t __xecall
xeCommandListCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_list_desc_t* desc,             ///< [in] pointer to command list descriptor
    xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == desc )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( XE_COMMAND_LIST_DESC_VERSION_CURRENT < desc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return context.xeCommandList.pfnCreate( hDevice, desc, phCommandList );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListCreateImmediate
xe_result_t __xecall
xeCommandListCreateImmediate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device object
    const xe_command_queue_desc_t* desc,            ///< [in] pointer to command queue descriptor
    xe_command_list_handle_t* phCommandList         ///< [out] pointer to handle of command list object created
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == desc )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( XE_COMMAND_QUEUE_DESC_VERSION_CURRENT < desc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return context.xeCommandList.pfnCreateImmediate( hDevice, desc, phCommandList );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListDestroy
xe_result_t __xecall
xeCommandListDestroy(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to destroy
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnDestroy( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListClose
xe_result_t __xecall
xeCommandListClose(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnClose( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListReset
xe_result_t __xecall
xeCommandListReset(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnReset( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListSetParameter
xe_result_t __xecall
xeCommandListSetParameter(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_command_list_parameter_t parameter,          ///< [in] parameter to change
    uint32_t value                                  ///< [in] value of attribute
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnSetParameter( hCommandList, parameter, value );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListGetParameter
xe_result_t __xecall
xeCommandListGetParameter(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_command_list_parameter_t parameter,          ///< [in] parameter to retrieve
    uint32_t* value                                 ///< [out] value of attribute
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == value )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnGetParameter( hCommandList, parameter, value );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListResetParameters
xe_result_t __xecall
xeCommandListResetParameters(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnResetParameters( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListReserveSpace
xe_result_t __xecall
xeCommandListReserveSpace(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    size_t size,                                    ///< [in] size (in bytes) to reserve
    void** ptr                                      ///< [out] pointer to command buffer space reserved
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnReserveSpace( hCommandList, size, ptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendBarrier
xe_result_t __xecall
xeCommandListAppendBarrier(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
    xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before executing
                                                    ///< barrier
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendMemoryRangesBarrier
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
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pRangeSizes )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pRanges )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceSystemBarrier
xe_result_t __xecall
xeDeviceSystemBarrier(
    xe_device_handle_t hDevice                      ///< [in] handle of the device
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeDevice.pfnSystemBarrier( hDevice );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceRegisterCLMemory
#if XE_ENABLE_OCL_INTEROP
xe_result_t __xecall
xeDeviceRegisterCLMemory(
    xe_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the memory
    cl_mem mem,                                     ///< [in] the OpenCL memory to register
    void** ptr                                      ///< [out] pointer to device allocation
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeDevice.pfnRegisterCLMemory( hDevice, context, mem, ptr );
}
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceRegisterCLProgram
#if XE_ENABLE_OCL_INTEROP
xe_result_t __xecall
xeDeviceRegisterCLProgram(
    xe_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the program
    cl_program program,                             ///< [in] the OpenCL program to register
    xe_module_handle_t* phModule                    ///< [out] pointer to handle of module object created
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phModule )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeDevice.pfnRegisterCLProgram( hDevice, context, program, phModule );
}
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceRegisterCLCommandQueue
#if XE_ENABLE_OCL_INTEROP
xe_result_t __xecall
xeDeviceRegisterCLCommandQueue(
    xe_device_handle_t hDevice,                     ///< [in] handle to the device
    cl_context context,                             ///< [in] the OpenCL context that created the command queue
    cl_command_queue command_queue,                 ///< [in] the OpenCL command queue to register
    xe_command_queue_handle_t* phCommandQueue       ///< [out] pointer to handle of command queue object created
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phCommandQueue )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeDevice.pfnRegisterCLCommandQueue( hDevice, context, command_queue, phCommandQueue );
}
#endif // XE_ENABLE_OCL_INTEROP

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendMemoryCopy
xe_result_t __xecall
xeCommandListAppendMemoryCopy(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    size_t size,                                    ///< [in] size in bytes to copy
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == dstptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == srcptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendMemorySet
xe_result_t __xecall
xeCommandListAppendMemorySet(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* ptr,                                      ///< [in] pointer to memory to initialize
    int value,                                      ///< [in] value to initialize memory to
    size_t size,                                    ///< [in] size in bytes to initailize
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnAppendMemorySet( hCommandList, ptr, value, size, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendMemoryCopyRegion
xe_result_t __xecall
xeCommandListAppendMemoryCopyRegion(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    xe_copy_region_t* dstRegion,                    ///< [in] pointer to destination region to copy to
    uint32_t dstPitch,                              ///< [in] destination pitch in bytes
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    xe_copy_region_t* srcRegion,                    ///< [in] pointer to source region to copy from
    uint32_t srcPitch,                              ///< [in] source pitch in bytes
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == dstptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == dstRegion )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == srcptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == srcRegion )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, srcptr, srcRegion, srcPitch, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendImageCopy
xe_result_t __xecall
xeCommandListAppendImageCopy(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hDstImage )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hSrcImage )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnAppendImageCopy( hCommandList, hDstImage, hSrcImage, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendImageCopyRegion
xe_result_t __xecall
xeCommandListAppendImageCopyRegion(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    xe_image_region_t* pDstRegion,                  ///< [in][optional] destination region descriptor
    xe_image_region_t* pSrcRegion,                  ///< [in][optional] source region descriptor
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hDstImage )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hSrcImage )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendImageCopyToMemory
xe_result_t __xecall
xeCommandListAppendImageCopyToMemory(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    void* dstptr,                                   ///< [in] pointer to destination memory to copy to
    xe_image_handle_t hSrcImage,                    ///< [in] handle of source image to copy from
    xe_image_region_t* pSrcRegion,                  ///< [in][optional] source region descriptor
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == dstptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hSrcImage )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendImageCopyFromMemory
xe_result_t __xecall
xeCommandListAppendImageCopyFromMemory(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_image_handle_t hDstImage,                    ///< [in] handle of destination image to copy to
    const void* srcptr,                             ///< [in] pointer to source memory to copy from
    xe_image_region_t* pDstRegion,                  ///< [in][optional] destination region descriptor
    xe_event_handle_t hEvent                        ///< [in][optional] handle of the event to signal on completion
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hDstImage )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == srcptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendMemoryPrefetch
xe_result_t __xecall
xeCommandListAppendMemoryPrefetch(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    const void* ptr,                                ///< [in] pointer to start of the memory range to prefetch
    size_t count                                    ///< [in] size in bytes of the memory range to prefetch
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnAppendMemoryPrefetch( hCommandList, ptr, count );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendMemAdvise
xe_result_t __xecall
xeCommandListAppendMemAdvise(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of command list
    xe_device_handle_t hDevice,                     ///< [in] device associated with the memory advice
    const void* ptr,                                ///< [in] Pointer to the start of the memory range
    size_t size,                                    ///< [in] Size in bytes of the memory range
    xe_memory_advice_t advice                       ///< [in] Memory advice for the memory range
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventPoolCreate
xe_result_t __xecall
xeEventPoolCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_event_pool_desc_t* desc,               ///< [in] pointer to event pool descriptor
    xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == desc )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phEventPool )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( XE_EVENT_POOL_DESC_VERSION_CURRENT < desc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return context.xeEventPool.pfnCreate( hDevice, desc, phEventPool );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventPoolDestroy
xe_result_t __xecall
xeEventPoolDestroy(
    xe_event_pool_handle_t hEventPool               ///< [in] handle of event pool object to destroy
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hEventPool )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeEventPool.pfnDestroy( hEventPool );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventCreate
xe_result_t __xecall
xeEventCreate(
    xe_event_pool_handle_t hEventPool,              ///< [in] handle of the event pool
    const xe_event_desc_t* desc,                    ///< [in] pointer to event descriptor
    xe_event_handle_t* phEvent                      ///< [out] pointer to handle of event object created
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hEventPool )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == desc )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phEvent )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( XE_EVENT_DESC_VERSION_CURRENT < desc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return context.xeEvent.pfnCreate( hEventPool, desc, phEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventDestroy
xe_result_t __xecall
xeEventDestroy(
    xe_event_handle_t hEvent                        ///< [in] handle of event object to destroy
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hEvent )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeEvent.pfnDestroy( hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventPoolGetIpcHandle
xe_result_t __xecall
xeEventPoolGetIpcHandle(
    xe_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
    xe_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hEventPool )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phIpc )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeEventPool.pfnGetIpcHandle( hEventPool, phIpc );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventPoolOpenIpcHandle
xe_result_t __xecall
xeEventPoolOpenIpcHandle(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC event pool handle
    xe_ipc_event_pool_handle_t hIpc,                ///< [in] IPC event handle
    xe_event_pool_handle_t* phEventPool             ///< [out] pointer handle of event pool object created
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hIpc )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phEventPool )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeEventPool.pfnOpenIpcHandle( hDevice, hIpc, phEventPool );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventPoolCloseIpcHandle
xe_result_t __xecall
xeEventPoolCloseIpcHandle(
    xe_event_pool_handle_t hEventPool               ///< [in] handle of event pool object
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hEventPool )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeEventPool.pfnCloseIpcHandle( hEventPool );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendSignalEvent
xe_result_t __xecall
xeCommandListAppendSignalEvent(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hEvent )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnAppendSignalEvent( hCommandList, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendWaitOnEvents
xe_result_t __xecall
xeCommandListAppendWaitOnEvents(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
    xe_event_handle_t* phEvents                     ///< [in] handle of the events to wait on before continuing
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phEvents )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnAppendWaitOnEvents( hCommandList, numEvents, phEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventHostSignal
xe_result_t __xecall
xeEventHostSignal(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hEvent )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeEvent.pfnHostSignal( hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventHostSynchronize
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
    if( context.enableParameterValidation )
    {
        if( nullptr == hEvent )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeEvent.pfnHostSynchronize( hEvent, timeout );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventQueryStatus
xe_result_t __xecall
xeEventQueryStatus(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hEvent )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeEvent.pfnQueryStatus( hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendEventReset
xe_result_t __xecall
xeCommandListAppendEventReset(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hEvent )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnAppendEventReset( hCommandList, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventReset
xe_result_t __xecall
xeEventReset(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hEvent )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeEvent.pfnReset( hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFenceCreate
xe_result_t __xecall
xeFenceCreate(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of command queue
    const xe_fence_desc_t* desc,                    ///< [in] pointer to fence descriptor
    xe_fence_handle_t* phFence                      ///< [out] pointer to handle of fence object created
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandQueue )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == desc )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phFence )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( XE_FENCE_DESC_VERSION_CURRENT < desc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return context.xeFence.pfnCreate( hCommandQueue, desc, phFence );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFenceDestroy
xe_result_t __xecall
xeFenceDestroy(
    xe_fence_handle_t hFence                        ///< [in] handle of fence object to destroy
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hFence )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeFence.pfnDestroy( hFence );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFenceHostSynchronize
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
    if( context.enableParameterValidation )
    {
        if( nullptr == hFence )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeFence.pfnHostSynchronize( hFence, timeout );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFenceQueryStatus
xe_result_t __xecall
xeFenceQueryStatus(
    xe_fence_handle_t hFence                        ///< [in] handle of the fence
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hFence )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeFence.pfnQueryStatus( hFence );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFenceReset
xe_result_t __xecall
xeFenceReset(
    xe_fence_handle_t hFence                        ///< [in] handle of the fence
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hFence )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeFence.pfnReset( hFence );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeImageGetProperties
xe_result_t __xecall
xeImageGetProperties(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    xe_image_properties_t* pImageProperties         ///< [out] pointer to image properties
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == desc )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pImageProperties )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( XE_IMAGE_DESC_VERSION_CURRENT < desc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return context.xeImage.pfnGetProperties( hDevice, desc, pImageProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeImageCreate
xe_result_t __xecall
xeImageCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_image_desc_t* desc,                    ///< [in] pointer to image descriptor
    xe_image_handle_t* phImage                      ///< [out] pointer to handle of image object created
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == desc )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phImage )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( XE_IMAGE_DESC_VERSION_CURRENT < desc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return context.xeImage.pfnCreate( hDevice, desc, phImage );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeImageDestroy
xe_result_t __xecall
xeImageDestroy(
    xe_image_handle_t hImage                        ///< [in] handle of image object to destroy
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hImage )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeImage.pfnDestroy( hImage );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextAllocSharedMem
xe_result_t __xecall
xeContextAllocSharedMem(
    xe_context_handle_t hContext,                   ///< [in] handle of context
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_mem_alloc_flag_t device_flags,        ///< [in] flags specifying additional device allocation controls
    xe_host_mem_alloc_flag_t host_flags,            ///< [in] flags specifying additional host allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to shared allocation
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hContext )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeContext.pfnAllocSharedMem( hContext, hDevice, device_flags, host_flags, size, alignment, ptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextAllocDeviceMem
xe_result_t __xecall
xeContextAllocDeviceMem(
    xe_context_handle_t hContext,                   ///< [in] handle of context
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_mem_alloc_flag_t flags,               ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to device allocation
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hContext )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeContext.pfnAllocDeviceMem( hContext, hDevice, flags, size, alignment, ptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextAllocHostMem
xe_result_t __xecall
xeContextAllocHostMem(
    xe_context_handle_t hContext,                   ///< [in] handle of context
    xe_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to host allocation
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hContext )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeContext.pfnAllocHostMem( hContext, flags, size, alignment, ptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextFreeMem
xe_result_t __xecall
xeContextFreeMem(
    xe_context_handle_t hContext,                   ///< [in] handle of context
    const void* ptr                                 ///< [in] pointer to memory to free
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hContext )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeContext.pfnFreeMem( hContext, ptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextGetMemProperties
xe_result_t __xecall
xeContextGetMemProperties(
    xe_context_handle_t hContext,                   ///< [in] handle of context
    const void* ptr,                                ///< [in] Pointer to query
    xe_memory_allocation_properties_t* pMemProperties   ///< [out] Query result for memory allocation properties
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hContext )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pMemProperties )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeContext.pfnGetMemProperties( hContext, ptr, pMemProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextGetMemAddressRange
xe_result_t __xecall
xeContextGetMemAddressRange(
    xe_context_handle_t hContext,                   ///< [in] handle of context
    const void* ptr,                                ///< [in] Pointer to query
    void** pBase,                                   ///< [in,out][optional] base address of the allocation
    size_t* pSize                                   ///< [in,out][optional] size of the allocation
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hContext )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeContext.pfnGetMemAddressRange( hContext, ptr, pBase, pSize );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextGetMemIpcHandle
xe_result_t __xecall
xeContextGetMemIpcHandle(
    xe_context_handle_t hContext,                   ///< [in] handle of context
    const void* ptr,                                ///< [in] Pointer to the device memory allocation
    xe_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hContext )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pIpcHandle )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeContext.pfnGetMemIpcHandle( hContext, ptr, pIpcHandle );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextOpenMemIpcHandle
xe_result_t __xecall
xeContextOpenMemIpcHandle(
    xe_context_handle_t hContext,                   ///< [in] handle of context
    xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
    xe_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
    xe_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
    void** ptr                                      ///< [out] pointer to device allocation in this process
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hContext )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == handle )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeContext.pfnOpenMemIpcHandle( hContext, hDevice, handle, flags, ptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeContextCloseMemIpcHandle
xe_result_t __xecall
xeContextCloseMemIpcHandle(
    xe_context_handle_t hContext,                   ///< [in] handle of context
    const void* ptr                                 ///< [in] pointer to device allocation in this process
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hContext )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeContext.pfnCloseMemIpcHandle( hContext, ptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleCreate
xe_result_t __xecall
xeModuleCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_module_desc_t* pDesc,                  ///< [in] pointer to module descriptor
    xe_module_handle_t* phModule,                   ///< [out] pointer to handle of module object created
    xe_module_build_log_handle_t* phBuildLog        ///< [in,out][optional] pointer to handle of module's build log.
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pDesc )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phModule )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( XE_MODULE_DESC_VERSION_CURRENT < pDesc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return context.xeModule.pfnCreate( hDevice, pDesc, phModule, phBuildLog );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleDestroy
xe_result_t __xecall
xeModuleDestroy(
    xe_module_handle_t hModule                      ///< [in] handle of the module
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hModule )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeModule.pfnDestroy( hModule );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleBuildLogDestroy
xe_result_t __xecall
xeModuleBuildLogDestroy(
    xe_module_build_log_handle_t hModuleBuildLog    ///< [in] handle of the module build log object.
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hModuleBuildLog )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeModuleBuildLog.pfnDestroy( hModuleBuildLog );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleBuildLogGetString
xe_result_t __xecall
xeModuleBuildLogGetString(
    xe_module_build_log_handle_t hModuleBuildLog,   ///< [in] handle of the module build log object.
    size_t* pSize,                                  ///< [in,out] size of build log string.
    char* pBuildLog                                 ///< [in,out][optional] pointer to null-terminated string of the log.
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hModuleBuildLog )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pSize )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeModuleBuildLog.pfnGetString( hModuleBuildLog, pSize, pBuildLog );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleGetNativeBinary
xe_result_t __xecall
xeModuleGetNativeBinary(
    xe_module_handle_t hModule,                     ///< [in] handle of the device
    size_t* pSize,                                  ///< [in,out] size of native binary in bytes.
    uint8_t* pModuleNativeBinary                    ///< [in,out][optional] byte pointer to native binary
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hModule )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pSize )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeModule.pfnGetNativeBinary( hModule, pSize, pModuleNativeBinary );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleGetGlobalPointer
xe_result_t __xecall
xeModuleGetGlobalPointer(
    xe_module_handle_t hModule,                     ///< [in] handle of the device
    const char* pGlobalName,                        ///< [in] name of function in global
    void** pPtr                                     ///< [out] device visible pointer
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hModule )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pGlobalName )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pPtr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeModule.pfnGetGlobalPointer( hModule, pGlobalName, pPtr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionCreate
xe_result_t __xecall
xeFunctionCreate(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const xe_function_desc_t* pDesc,                ///< [in] pointer to function descriptor
    xe_function_handle_t* phFunction                ///< [out] handle of the Function object
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hModule )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pDesc )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phFunction )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( XE_FUNCTION_DESC_VERSION_CURRENT < pDesc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return context.xeFunction.pfnCreate( hModule, pDesc, phFunction );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionDestroy
xe_result_t __xecall
xeFunctionDestroy(
    xe_function_handle_t hFunction                  ///< [in] handle of the function object
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hFunction )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeFunction.pfnDestroy( hFunction );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleGetFunctionPointer
xe_result_t __xecall
xeModuleGetFunctionPointer(
    xe_module_handle_t hModule,                     ///< [in] handle of the module
    const char* pFunctionName,                      ///< [in] Name of function to retrieve function pointer for.
    void** pfnFunction                              ///< [out] pointer to function.
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hModule )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pFunctionName )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pfnFunction )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeModule.pfnGetFunctionPointer( hModule, pFunctionName, pfnFunction );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionSetGroupSize
xe_result_t __xecall
xeFunctionSetGroupSize(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    uint32_t groupSizeX,                            ///< [in] group size for X dimension to use for this function.
    uint32_t groupSizeY,                            ///< [in] group size for Y dimension to use for this function.
    uint32_t groupSizeZ                             ///< [in] group size for Z dimension to use for this function.
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hFunction )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeFunction.pfnSetGroupSize( hFunction, groupSizeX, groupSizeY, groupSizeZ );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionSuggestGroupSize
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
    if( context.enableParameterValidation )
    {
        if( nullptr == hFunction )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == groupSizeX )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == groupSizeY )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == groupSizeZ )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeFunction.pfnSuggestGroupSize( hFunction, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionSetArgumentValue
xe_result_t __xecall
xeFunctionSetArgumentValue(
    xe_function_handle_t hFunction,                 ///< [in,out] handle of the function args object.
    uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
    size_t argSize,                                 ///< [in] size of argument type
    const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                    ///< null then argument value is considered null.
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hFunction )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeFunction.pfnSetArgumentValue( hFunction, argIndex, argSize, pArgValue );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionSetAttribute
xe_result_t __xecall
xeFunctionSetAttribute(
    xe_function_handle_t hFunction,                 ///< [in,out] handle of the function.
    xe_function_set_attribute_t attr,               ///< [in] attribute to set
    uint32_t value                                  ///< [in] attribute value to set
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hFunction )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeFunction.pfnSetAttribute( hFunction, attr, value );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionGetAttribute
xe_result_t __xecall
xeFunctionGetAttribute(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function object
    xe_function_get_attribute_t attr,               ///< [in] attribute to query
    uint32_t* pValue                                ///< [out] returned attribute value
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hFunction )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pValue )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeFunction.pfnGetAttribute( hFunction, attr, pValue );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendLaunchFunction
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
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hFunction )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pLaunchFuncArgs )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnAppendLaunchFunction( hCommandList, hFunction, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendLaunchFunctionIndirect
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
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hFunction )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pLaunchArgumentsBuffer )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnAppendLaunchFunctionIndirect( hCommandList, hFunction, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendLaunchMultipleFunctionsIndirect
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
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phFunctions )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pNumLaunchArguments )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pLaunchArgumentsBuffer )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnAppendLaunchMultipleFunctionsIndirect( hCommandList, numFunctions, phFunctions, pNumLaunchArguments, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendLaunchHostFunction
xe_result_t __xecall
xeCommandListAppendLaunchHostFunction(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_host_pfn_t pfnHostFunc,                      ///< [in] pointer to host function.
    void* pUserData,                                ///< [in] pointer to user data to pass to host function.
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    xe_event_handle_t* phWaitEvents                 ///< [in][optional] handle of the events to wait on before launching
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pUserData )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeCommandList.pfnAppendLaunchHostFunction( hCommandList, pfnHostFunc, pUserData, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceMakeMemoryResident
xe_result_t __xecall
xeDeviceMakeMemoryResident(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    void* ptr,                                      ///< [in] pointer to memory to make resident
    size_t size                                     ///< [in] size in bytes to make resident
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeDevice.pfnMakeMemoryResident( hDevice, ptr, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceEvictMemory
xe_result_t __xecall
xeDeviceEvictMemory(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    void* ptr,                                      ///< [in] pointer to memory to evict
    size_t size                                     ///< [in] size in bytes to evict
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeDevice.pfnEvictMemory( hDevice, ptr, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceMakeImageResident
xe_result_t __xecall
xeDeviceMakeImageResident(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_image_handle_t hImage                        ///< [in] handle of image to make resident
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hImage )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeDevice.pfnMakeImageResident( hDevice, hImage );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceEvictImage
xe_result_t __xecall
xeDeviceEvictImage(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_image_handle_t hImage                        ///< [in] handle of image to make evict
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == hImage )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeDevice.pfnEvictImage( hDevice, hImage );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeSamplerCreate
xe_result_t __xecall
xeSamplerCreate(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    const xe_sampler_desc_t* pDesc,                 ///< [in] pointer to sampler descriptor
    xe_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == pDesc )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( nullptr == phSampler )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

        if( XE_SAMPLER_DESC_VERSION_CURRENT < pDesc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return context.xeSampler.pfnCreate( hDevice, pDesc, phSampler );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeSamplerDestroy
xe_result_t __xecall
xeSamplerDestroy(
    xe_sampler_handle_t hSampler                    ///< [in] handle of the sampler
    )
{
    if( context.enableParameterValidation )
    {
        if( nullptr == hSampler )
            return XE_RESULT_ERROR_INVALID_PARAMETER;

    }

    return context.xeSampler.pfnDestroy( hSampler );
}

#if defined(__cplusplus)
};
#endif
