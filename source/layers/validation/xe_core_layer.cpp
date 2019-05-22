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
* @file xe_core_layer.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/valddi.cpp.mako
* @endcond
*
******************************************************************************/
#include "xe_layer.h"

#if defined(__cplusplus)
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Global table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetGlobalProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_global_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = xe_layer::val.xeDdiTable.Global;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnInit                                     = pDdiTable->pfnInit;
    pDdiTable->pfnInit                                   = xeInit;

    dditable.pfnGetDeviceGroups                          = pDdiTable->pfnGetDeviceGroups;
    pDdiTable->pfnGetDeviceGroups                        = xeGetDeviceGroups;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Device table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetDeviceProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_device_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = xe_layer::val.xeDdiTable.Device;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGetSubDevice                             = pDdiTable->pfnGetSubDevice;
    pDdiTable->pfnGetSubDevice                           = xeDeviceGetSubDevice;

    dditable.pfnGetP2PProperties                         = pDdiTable->pfnGetP2PProperties;
    pDdiTable->pfnGetP2PProperties                       = xeDeviceGetP2PProperties;

    dditable.pfnCanAccessPeer                            = pDdiTable->pfnCanAccessPeer;
    pDdiTable->pfnCanAccessPeer                          = xeDeviceCanAccessPeer;

    dditable.pfnSetIntermediateCacheConfig               = pDdiTable->pfnSetIntermediateCacheConfig;
    pDdiTable->pfnSetIntermediateCacheConfig             = xeDeviceSetIntermediateCacheConfig;

    dditable.pfnSetLastLevelCacheConfig                  = pDdiTable->pfnSetLastLevelCacheConfig;
    pDdiTable->pfnSetLastLevelCacheConfig                = xeDeviceSetLastLevelCacheConfig;

    dditable.pfnSystemBarrier                            = pDdiTable->pfnSystemBarrier;
    pDdiTable->pfnSystemBarrier                          = xeDeviceSystemBarrier;

#if XE_ENABLE_OCL_INTEROP
    dditable.pfnRegisterCLMemory                         = pDdiTable->pfnRegisterCLMemory;
    pDdiTable->pfnRegisterCLMemory                       = xeDeviceRegisterCLMemory;
#endif

#if XE_ENABLE_OCL_INTEROP
    dditable.pfnRegisterCLProgram                        = pDdiTable->pfnRegisterCLProgram;
    pDdiTable->pfnRegisterCLProgram                      = xeDeviceRegisterCLProgram;
#endif

#if XE_ENABLE_OCL_INTEROP
    dditable.pfnRegisterCLCommandQueue                   = pDdiTable->pfnRegisterCLCommandQueue;
    pDdiTable->pfnRegisterCLCommandQueue                 = xeDeviceRegisterCLCommandQueue;
#endif

    dditable.pfnMakeMemoryResident                       = pDdiTable->pfnMakeMemoryResident;
    pDdiTable->pfnMakeMemoryResident                     = xeDeviceMakeMemoryResident;

    dditable.pfnEvictMemory                              = pDdiTable->pfnEvictMemory;
    pDdiTable->pfnEvictMemory                            = xeDeviceEvictMemory;

    dditable.pfnMakeImageResident                        = pDdiTable->pfnMakeImageResident;
    pDdiTable->pfnMakeImageResident                      = xeDeviceMakeImageResident;

    dditable.pfnEvictImage                               = pDdiTable->pfnEvictImage;
    pDdiTable->pfnEvictImage                             = xeDeviceEvictImage;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's DeviceGroup table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetDeviceGroupProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_device_group_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = xe_layer::val.xeDdiTable.DeviceGroup;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGetDriverVersion                         = pDdiTable->pfnGetDriverVersion;
    pDdiTable->pfnGetDriverVersion                       = xeDeviceGroupGetDriverVersion;

    dditable.pfnGetDevices                               = pDdiTable->pfnGetDevices;
    pDdiTable->pfnGetDevices                             = xeDeviceGroupGetDevices;

    dditable.pfnGetApiVersion                            = pDdiTable->pfnGetApiVersion;
    pDdiTable->pfnGetApiVersion                          = xeDeviceGroupGetApiVersion;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = xeDeviceGroupGetProperties;

    dditable.pfnGetComputeProperties                     = pDdiTable->pfnGetComputeProperties;
    pDdiTable->pfnGetComputeProperties                   = xeDeviceGroupGetComputeProperties;

    dditable.pfnGetMemoryProperties                      = pDdiTable->pfnGetMemoryProperties;
    pDdiTable->pfnGetMemoryProperties                    = xeDeviceGroupGetMemoryProperties;

    dditable.pfnAllocSharedMem                           = pDdiTable->pfnAllocSharedMem;
    pDdiTable->pfnAllocSharedMem                         = xeDeviceGroupAllocSharedMem;

    dditable.pfnAllocDeviceMem                           = pDdiTable->pfnAllocDeviceMem;
    pDdiTable->pfnAllocDeviceMem                         = xeDeviceGroupAllocDeviceMem;

    dditable.pfnAllocHostMem                             = pDdiTable->pfnAllocHostMem;
    pDdiTable->pfnAllocHostMem                           = xeDeviceGroupAllocHostMem;

    dditable.pfnFreeMem                                  = pDdiTable->pfnFreeMem;
    pDdiTable->pfnFreeMem                                = xeDeviceGroupFreeMem;

    dditable.pfnGetMemProperties                         = pDdiTable->pfnGetMemProperties;
    pDdiTable->pfnGetMemProperties                       = xeDeviceGroupGetMemProperties;

    dditable.pfnGetMemAddressRange                       = pDdiTable->pfnGetMemAddressRange;
    pDdiTable->pfnGetMemAddressRange                     = xeDeviceGroupGetMemAddressRange;

    dditable.pfnGetMemIpcHandle                          = pDdiTable->pfnGetMemIpcHandle;
    pDdiTable->pfnGetMemIpcHandle                        = xeDeviceGroupGetMemIpcHandle;

    dditable.pfnOpenMemIpcHandle                         = pDdiTable->pfnOpenMemIpcHandle;
    pDdiTable->pfnOpenMemIpcHandle                       = xeDeviceGroupOpenMemIpcHandle;

    dditable.pfnCloseMemIpcHandle                        = pDdiTable->pfnCloseMemIpcHandle;
    pDdiTable->pfnCloseMemIpcHandle                      = xeDeviceGroupCloseMemIpcHandle;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandQueue table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetCommandQueueProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_command_queue_dditable_t* pDdiTable          ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = xe_layer::val.xeDdiTable.CommandQueue;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = xeCommandQueueCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = xeCommandQueueDestroy;

    dditable.pfnExecuteCommandLists                      = pDdiTable->pfnExecuteCommandLists;
    pDdiTable->pfnExecuteCommandLists                    = xeCommandQueueExecuteCommandLists;

    dditable.pfnSynchronize                              = pDdiTable->pfnSynchronize;
    pDdiTable->pfnSynchronize                            = xeCommandQueueSynchronize;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's CommandList table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetCommandListProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_command_list_dditable_t* pDdiTable           ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = xe_layer::val.xeDdiTable.CommandList;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = xeCommandListCreate;

    dditable.pfnCreateImmediate                          = pDdiTable->pfnCreateImmediate;
    pDdiTable->pfnCreateImmediate                        = xeCommandListCreateImmediate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = xeCommandListDestroy;

    dditable.pfnClose                                    = pDdiTable->pfnClose;
    pDdiTable->pfnClose                                  = xeCommandListClose;

    dditable.pfnReset                                    = pDdiTable->pfnReset;
    pDdiTable->pfnReset                                  = xeCommandListReset;

    dditable.pfnSetParameter                             = pDdiTable->pfnSetParameter;
    pDdiTable->pfnSetParameter                           = xeCommandListSetParameter;

    dditable.pfnGetParameter                             = pDdiTable->pfnGetParameter;
    pDdiTable->pfnGetParameter                           = xeCommandListGetParameter;

    dditable.pfnResetParameters                          = pDdiTable->pfnResetParameters;
    pDdiTable->pfnResetParameters                        = xeCommandListResetParameters;

    dditable.pfnReserveSpace                             = pDdiTable->pfnReserveSpace;
    pDdiTable->pfnReserveSpace                           = xeCommandListReserveSpace;

    dditable.pfnAppendBarrier                            = pDdiTable->pfnAppendBarrier;
    pDdiTable->pfnAppendBarrier                          = xeCommandListAppendBarrier;

    dditable.pfnAppendMemoryRangesBarrier                = pDdiTable->pfnAppendMemoryRangesBarrier;
    pDdiTable->pfnAppendMemoryRangesBarrier              = xeCommandListAppendMemoryRangesBarrier;

    dditable.pfnAppendMemoryCopy                         = pDdiTable->pfnAppendMemoryCopy;
    pDdiTable->pfnAppendMemoryCopy                       = xeCommandListAppendMemoryCopy;

    dditable.pfnAppendMemorySet                          = pDdiTable->pfnAppendMemorySet;
    pDdiTable->pfnAppendMemorySet                        = xeCommandListAppendMemorySet;

    dditable.pfnAppendMemoryCopyRegion                   = pDdiTable->pfnAppendMemoryCopyRegion;
    pDdiTable->pfnAppendMemoryCopyRegion                 = xeCommandListAppendMemoryCopyRegion;

    dditable.pfnAppendImageCopy                          = pDdiTable->pfnAppendImageCopy;
    pDdiTable->pfnAppendImageCopy                        = xeCommandListAppendImageCopy;

    dditable.pfnAppendImageCopyRegion                    = pDdiTable->pfnAppendImageCopyRegion;
    pDdiTable->pfnAppendImageCopyRegion                  = xeCommandListAppendImageCopyRegion;

    dditable.pfnAppendImageCopyToMemory                  = pDdiTable->pfnAppendImageCopyToMemory;
    pDdiTable->pfnAppendImageCopyToMemory                = xeCommandListAppendImageCopyToMemory;

    dditable.pfnAppendImageCopyFromMemory                = pDdiTable->pfnAppendImageCopyFromMemory;
    pDdiTable->pfnAppendImageCopyFromMemory              = xeCommandListAppendImageCopyFromMemory;

    dditable.pfnAppendMemoryPrefetch                     = pDdiTable->pfnAppendMemoryPrefetch;
    pDdiTable->pfnAppendMemoryPrefetch                   = xeCommandListAppendMemoryPrefetch;

    dditable.pfnAppendMemAdvise                          = pDdiTable->pfnAppendMemAdvise;
    pDdiTable->pfnAppendMemAdvise                        = xeCommandListAppendMemAdvise;

    dditable.pfnAppendSignalEvent                        = pDdiTable->pfnAppendSignalEvent;
    pDdiTable->pfnAppendSignalEvent                      = xeCommandListAppendSignalEvent;

    dditable.pfnAppendWaitOnEvents                       = pDdiTable->pfnAppendWaitOnEvents;
    pDdiTable->pfnAppendWaitOnEvents                     = xeCommandListAppendWaitOnEvents;

    dditable.pfnAppendEventReset                         = pDdiTable->pfnAppendEventReset;
    pDdiTable->pfnAppendEventReset                       = xeCommandListAppendEventReset;

    dditable.pfnAppendLaunchFunction                     = pDdiTable->pfnAppendLaunchFunction;
    pDdiTable->pfnAppendLaunchFunction                   = xeCommandListAppendLaunchFunction;

    dditable.pfnAppendLaunchFunctionIndirect             = pDdiTable->pfnAppendLaunchFunctionIndirect;
    pDdiTable->pfnAppendLaunchFunctionIndirect           = xeCommandListAppendLaunchFunctionIndirect;

    dditable.pfnAppendLaunchMultipleFunctionsIndirect    = pDdiTable->pfnAppendLaunchMultipleFunctionsIndirect;
    pDdiTable->pfnAppendLaunchMultipleFunctionsIndirect  = xeCommandListAppendLaunchMultipleFunctionsIndirect;

    dditable.pfnAppendLaunchHostFunction                 = pDdiTable->pfnAppendLaunchHostFunction;
    pDdiTable->pfnAppendLaunchHostFunction               = xeCommandListAppendLaunchHostFunction;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Fence table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetFenceProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_fence_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = xe_layer::val.xeDdiTable.Fence;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = xeFenceCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = xeFenceDestroy;

    dditable.pfnHostSynchronize                          = pDdiTable->pfnHostSynchronize;
    pDdiTable->pfnHostSynchronize                        = xeFenceHostSynchronize;

    dditable.pfnQueryStatus                              = pDdiTable->pfnQueryStatus;
    pDdiTable->pfnQueryStatus                            = xeFenceQueryStatus;

    dditable.pfnReset                                    = pDdiTable->pfnReset;
    pDdiTable->pfnReset                                  = xeFenceReset;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's EventPool table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetEventPoolProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_event_pool_dditable_t* pDdiTable             ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = xe_layer::val.xeDdiTable.EventPool;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = xeEventPoolCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = xeEventPoolDestroy;

    dditable.pfnGetIpcHandle                             = pDdiTable->pfnGetIpcHandle;
    pDdiTable->pfnGetIpcHandle                           = xeEventPoolGetIpcHandle;

    dditable.pfnOpenIpcHandle                            = pDdiTable->pfnOpenIpcHandle;
    pDdiTable->pfnOpenIpcHandle                          = xeEventPoolOpenIpcHandle;

    dditable.pfnCloseIpcHandle                           = pDdiTable->pfnCloseIpcHandle;
    pDdiTable->pfnCloseIpcHandle                         = xeEventPoolCloseIpcHandle;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Event table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetEventProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_event_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = xe_layer::val.xeDdiTable.Event;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = xeEventCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = xeEventDestroy;

    dditable.pfnHostSignal                               = pDdiTable->pfnHostSignal;
    pDdiTable->pfnHostSignal                             = xeEventHostSignal;

    dditable.pfnHostSynchronize                          = pDdiTable->pfnHostSynchronize;
    pDdiTable->pfnHostSynchronize                        = xeEventHostSynchronize;

    dditable.pfnQueryStatus                              = pDdiTable->pfnQueryStatus;
    pDdiTable->pfnQueryStatus                            = xeEventQueryStatus;

    dditable.pfnReset                                    = pDdiTable->pfnReset;
    pDdiTable->pfnReset                                  = xeEventReset;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Image table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetImageProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_image_dditable_t* pDdiTable                  ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = xe_layer::val.xeDdiTable.Image;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnGetProperties                            = pDdiTable->pfnGetProperties;
    pDdiTable->pfnGetProperties                          = xeImageGetProperties;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = xeImageCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = xeImageDestroy;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Module table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetModuleProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_module_dditable_t* pDdiTable                 ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = xe_layer::val.xeDdiTable.Module;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = xeModuleCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = xeModuleDestroy;

    dditable.pfnGetNativeBinary                          = pDdiTable->pfnGetNativeBinary;
    pDdiTable->pfnGetNativeBinary                        = xeModuleGetNativeBinary;

    dditable.pfnGetGlobalPointer                         = pDdiTable->pfnGetGlobalPointer;
    pDdiTable->pfnGetGlobalPointer                       = xeModuleGetGlobalPointer;

    dditable.pfnGetFunctionPointer                       = pDdiTable->pfnGetFunctionPointer;
    pDdiTable->pfnGetFunctionPointer                     = xeModuleGetFunctionPointer;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's ModuleBuildLog table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetModuleBuildLogProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_module_build_log_dditable_t* pDdiTable       ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = xe_layer::val.xeDdiTable.ModuleBuildLog;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = xeModuleBuildLogDestroy;

    dditable.pfnGetString                                = pDdiTable->pfnGetString;
    pDdiTable->pfnGetString                              = xeModuleBuildLogGetString;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Function table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetFunctionProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_function_dditable_t* pDdiTable               ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = xe_layer::val.xeDdiTable.Function;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = xeFunctionCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = xeFunctionDestroy;

    dditable.pfnSetGroupSize                             = pDdiTable->pfnSetGroupSize;
    pDdiTable->pfnSetGroupSize                           = xeFunctionSetGroupSize;

    dditable.pfnSuggestGroupSize                         = pDdiTable->pfnSuggestGroupSize;
    pDdiTable->pfnSuggestGroupSize                       = xeFunctionSuggestGroupSize;

    dditable.pfnSetArgumentValue                         = pDdiTable->pfnSetArgumentValue;
    pDdiTable->pfnSetArgumentValue                       = xeFunctionSetArgumentValue;

    dditable.pfnSetAttribute                             = pDdiTable->pfnSetAttribute;
    pDdiTable->pfnSetAttribute                           = xeFunctionSetAttribute;

    dditable.pfnGetAttribute                             = pDdiTable->pfnGetAttribute;
    pDdiTable->pfnGetAttribute                           = xeFunctionGetAttribute;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Exported function for filling application's Sampler table
///        with current process' addresses
///
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + invalid value for version
///         + nullptr for pDdiTable
///     - ::XE_RESULT_ERROR_UNSUPPORTED
///         + version not supported
__xedllexport xe_result_t __xecall
xeGetSamplerProcAddrTable(
    xe_api_version_t version,                       ///< [in] API version requested
    xe_sampler_dditable_t* pDdiTable                ///< [in,out] pointer to table of DDI function pointers
    )
{
    auto& dditable = xe_layer::val.xeDdiTable.Sampler;

    if( nullptr == pDdiTable )
        return XE_RESULT_ERROR_INVALID_ARGUMENT;

    if( xe_layer::val.version < version )
        return XE_RESULT_ERROR_UNSUPPORTED;

    xe_result_t result = XE_RESULT_SUCCESS;

    dditable.pfnCreate                                   = pDdiTable->pfnCreate;
    pDdiTable->pfnCreate                                 = xeSamplerCreate;

    dditable.pfnDestroy                                  = pDdiTable->pfnDestroy;
    pDdiTable->pfnDestroy                                = xeSamplerDestroy;

    return result;
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeInit
xe_result_t __xecall
xeInit(
    xe_init_flag_t flags                            ///< [in] initialization flags
    )
{
    auto pfnInit = xe_layer::val.xeDdiTable.Global.pfnInit;

    if( nullptr == pfnInit )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
    }

    return pfnInit( flags );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetDriverVersion
xe_result_t __xecall
xeDeviceGroupGetDriverVersion(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of device group
    uint32_t* version                               ///< [out] driver version
    )
{
    auto pfnGetDriverVersion = xe_layer::val.xeDdiTable.DeviceGroup.pfnGetDriverVersion;

    if( nullptr == pfnGetDriverVersion )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == version )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetDriverVersion( hDeviceGroup, version );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeGetDeviceGroups
xe_result_t __xecall
xeGetDeviceGroups(
    uint32_t* pCount,                               ///< [in,out] pointer to the number of device groups.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of device groups available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of
                                                    ///< device groups.
    xe_device_group_handle_t* pDeviceGroups         ///< [in,out][optional][range(0, *pCount)] array of handle of device groups
    )
{
    auto pfnGetDeviceGroups = xe_layer::val.xeDdiTable.Global.pfnGetDeviceGroups;

    if( nullptr == pfnGetDeviceGroups )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == pCount )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetDeviceGroups( pCount, pDeviceGroups );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetDevices
xe_result_t __xecall
xeDeviceGroupGetDevices(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    uint32_t* pCount,                               ///< [in,out] pointer to the number of device groups.
                                                    ///< if count is zero, then the driver will update the value with the total
                                                    ///< number of device groups available.
                                                    ///< if count is non-zero, then driver will only retrieve that number of
                                                    ///< device groups.
    xe_device_handle_t* pDevices                    ///< [in,out][optional][range(0, *pCount)] array of handle of devices
    )
{
    auto pfnGetDevices = xe_layer::val.xeDdiTable.DeviceGroup.pfnGetDevices;

    if( nullptr == pfnGetDevices )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pCount )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetDevices( hDeviceGroup, pCount, pDevices );
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
    auto pfnGetSubDevice = xe_layer::val.xeDdiTable.Device.pfnGetSubDevice;

    if( nullptr == pfnGetSubDevice )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phSubDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetSubDevice( hDevice, ordinal, phSubDevice );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetApiVersion
xe_result_t __xecall
xeDeviceGroupGetApiVersion(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_api_version_t* version                       ///< [out] api version
    )
{
    auto pfnGetApiVersion = xe_layer::val.xeDdiTable.DeviceGroup.pfnGetApiVersion;

    if( nullptr == pfnGetApiVersion )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == version )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetApiVersion( hDeviceGroup, version );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetProperties
xe_result_t __xecall
xeDeviceGroupGetProperties(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_properties_t* pDeviceProperties       ///< [out] query result for device properties
    )
{
    auto pfnGetProperties = xe_layer::val.xeDdiTable.DeviceGroup.pfnGetProperties;

    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pDeviceProperties )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetProperties( hDeviceGroup, pDeviceProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetComputeProperties
xe_result_t __xecall
xeDeviceGroupGetComputeProperties(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_compute_properties_t* pComputeProperties  ///< [out] query result for compute properties
    )
{
    auto pfnGetComputeProperties = xe_layer::val.xeDdiTable.DeviceGroup.pfnGetComputeProperties;

    if( nullptr == pfnGetComputeProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pComputeProperties )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetComputeProperties( hDeviceGroup, pComputeProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetMemoryProperties
xe_result_t __xecall
xeDeviceGroupGetMemoryProperties(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_memory_properties_t* pMemProperties   ///< [out] query result for compute properties
    )
{
    auto pfnGetMemoryProperties = xe_layer::val.xeDdiTable.DeviceGroup.pfnGetMemoryProperties;

    if( nullptr == pfnGetMemoryProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pMemProperties )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetMemoryProperties( hDeviceGroup, pMemProperties );
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
    auto pfnGetP2PProperties = xe_layer::val.xeDdiTable.Device.pfnGetP2PProperties;

    if( nullptr == pfnGetP2PProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hPeerDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pP2PProperties )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetP2PProperties( hDevice, hPeerDevice, pP2PProperties );
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
    auto pfnCanAccessPeer = xe_layer::val.xeDdiTable.Device.pfnCanAccessPeer;

    if( nullptr == pfnCanAccessPeer )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hPeerDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == value )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnCanAccessPeer( hDevice, hPeerDevice, value );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceSetIntermediateCacheConfig
xe_result_t __xecall
xeDeviceSetIntermediateCacheConfig(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device 
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    )
{
    auto pfnSetIntermediateCacheConfig = xe_layer::val.xeDdiTable.Device.pfnSetIntermediateCacheConfig;

    if( nullptr == pfnSetIntermediateCacheConfig )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnSetIntermediateCacheConfig( hDevice, CacheConfig );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceSetLastLevelCacheConfig
xe_result_t __xecall
xeDeviceSetLastLevelCacheConfig(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device 
    xe_cache_config_t CacheConfig                   ///< [in] CacheConfig
    )
{
    auto pfnSetLastLevelCacheConfig = xe_layer::val.xeDdiTable.Device.pfnSetLastLevelCacheConfig;

    if( nullptr == pfnSetLastLevelCacheConfig )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnSetLastLevelCacheConfig( hDevice, CacheConfig );
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
    auto pfnCreate = xe_layer::val.xeDdiTable.CommandQueue.pfnCreate;

    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == desc )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phCommandQueue )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( XE_COMMAND_QUEUE_DESC_VERSION_CURRENT < desc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return pfnCreate( hDevice, desc, phCommandQueue );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandQueueDestroy
xe_result_t __xecall
xeCommandQueueDestroy(
    xe_command_queue_handle_t hCommandQueue         ///< [in] handle of command queue object to destroy
    )
{
    auto pfnDestroy = xe_layer::val.xeDdiTable.CommandQueue.pfnDestroy;

    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandQueue )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnDestroy( hCommandQueue );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandQueueExecuteCommandLists
xe_result_t __xecall
xeCommandQueueExecuteCommandLists(
    xe_command_queue_handle_t hCommandQueue,        ///< [in] handle of the command queue
    uint32_t numCommandLists,                       ///< [in] number of command lists to execute
    xe_command_list_handle_t* phCommandLists,       ///< [in][range(0, numCommandLists)] list of handles of the command lists
                                                    ///< to execute
    xe_fence_handle_t hFence                        ///< [in][optional] handle of the fence to signal on completion
    )
{
    auto pfnExecuteCommandLists = xe_layer::val.xeDdiTable.CommandQueue.pfnExecuteCommandLists;

    if( nullptr == pfnExecuteCommandLists )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandQueue )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phCommandLists )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnExecuteCommandLists( hCommandQueue, numCommandLists, phCommandLists, hFence );
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
    auto pfnSynchronize = xe_layer::val.xeDdiTable.CommandQueue.pfnSynchronize;

    if( nullptr == pfnSynchronize )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandQueue )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnSynchronize( hCommandQueue, timeout );
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
    auto pfnCreate = xe_layer::val.xeDdiTable.CommandList.pfnCreate;

    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == desc )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( XE_COMMAND_LIST_DESC_VERSION_CURRENT < desc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return pfnCreate( hDevice, desc, phCommandList );
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
    auto pfnCreateImmediate = xe_layer::val.xeDdiTable.CommandList.pfnCreateImmediate;

    if( nullptr == pfnCreateImmediate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == desc )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( XE_COMMAND_QUEUE_DESC_VERSION_CURRENT < desc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return pfnCreateImmediate( hDevice, desc, phCommandList );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListDestroy
xe_result_t __xecall
xeCommandListDestroy(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to destroy
    )
{
    auto pfnDestroy = xe_layer::val.xeDdiTable.CommandList.pfnDestroy;

    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnDestroy( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListClose
xe_result_t __xecall
xeCommandListClose(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to close
    )
{
    auto pfnClose = xe_layer::val.xeDdiTable.CommandList.pfnClose;

    if( nullptr == pfnClose )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnClose( hCommandList );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListReset
xe_result_t __xecall
xeCommandListReset(
    xe_command_list_handle_t hCommandList           ///< [in] handle of command list object to reset
    )
{
    auto pfnReset = xe_layer::val.xeDdiTable.CommandList.pfnReset;

    if( nullptr == pfnReset )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnReset( hCommandList );
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
    auto pfnSetParameter = xe_layer::val.xeDdiTable.CommandList.pfnSetParameter;

    if( nullptr == pfnSetParameter )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnSetParameter( hCommandList, parameter, value );
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
    auto pfnGetParameter = xe_layer::val.xeDdiTable.CommandList.pfnGetParameter;

    if( nullptr == pfnGetParameter )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == value )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetParameter( hCommandList, parameter, value );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListResetParameters
xe_result_t __xecall
xeCommandListResetParameters(
    xe_command_list_handle_t hCommandList           ///< [in] handle of the command list
    )
{
    auto pfnResetParameters = xe_layer::val.xeDdiTable.CommandList.pfnResetParameters;

    if( nullptr == pfnResetParameters )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnResetParameters( hCommandList );
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
    auto pfnReserveSpace = xe_layer::val.xeDdiTable.CommandList.pfnReserveSpace;

    if( nullptr == pfnReserveSpace )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnReserveSpace( hCommandList, size, ptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendBarrier
xe_result_t __xecall
xeCommandListAppendBarrier(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before executing barrier
    )
{
    auto pfnAppendBarrier = xe_layer::val.xeDdiTable.CommandList.pfnAppendBarrier;

    if( nullptr == pfnAppendBarrier )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendBarrier( hCommandList, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendMemoryRangesBarrier
xe_result_t __xecall
xeCommandListAppendMemoryRangesBarrier(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numRanges,                             ///< [in] number of memory ranges
    const size_t* pRangeSizes,                      ///< [in][range(0, numRanges)] array of sizes of memory range
    const void** pRanges,                           ///< [in][range(0, numRanges)] array of memory ranges
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before executing barrier
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before executing barrier
    )
{
    auto pfnAppendMemoryRangesBarrier = xe_layer::val.xeDdiTable.CommandList.pfnAppendMemoryRangesBarrier;

    if( nullptr == pfnAppendMemoryRangesBarrier )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pRangeSizes )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pRanges )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendMemoryRangesBarrier( hCommandList, numRanges, pRangeSizes, pRanges, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceSystemBarrier
xe_result_t __xecall
xeDeviceSystemBarrier(
    xe_device_handle_t hDevice                      ///< [in] handle of the device
    )
{
    auto pfnSystemBarrier = xe_layer::val.xeDdiTable.Device.pfnSystemBarrier;

    if( nullptr == pfnSystemBarrier )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnSystemBarrier( hDevice );
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
    auto pfnRegisterCLMemory = xe_layer::val.xeDdiTable.Device.pfnRegisterCLMemory;

    if( nullptr == pfnRegisterCLMemory )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnRegisterCLMemory( hDevice, context, mem, ptr );
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
    auto pfnRegisterCLProgram = xe_layer::val.xeDdiTable.Device.pfnRegisterCLProgram;

    if( nullptr == pfnRegisterCLProgram )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phModule )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnRegisterCLProgram( hDevice, context, program, phModule );
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
    auto pfnRegisterCLCommandQueue = xe_layer::val.xeDdiTable.Device.pfnRegisterCLCommandQueue;

    if( nullptr == pfnRegisterCLCommandQueue )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phCommandQueue )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnRegisterCLCommandQueue( hDevice, context, command_queue, phCommandQueue );
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
    auto pfnAppendMemoryCopy = xe_layer::val.xeDdiTable.CommandList.pfnAppendMemoryCopy;

    if( nullptr == pfnAppendMemoryCopy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == dstptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == srcptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendMemoryCopy( hCommandList, dstptr, srcptr, size, hEvent );
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
    auto pfnAppendMemorySet = xe_layer::val.xeDdiTable.CommandList.pfnAppendMemorySet;

    if( nullptr == pfnAppendMemorySet )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendMemorySet( hCommandList, ptr, value, size, hEvent );
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
    auto pfnAppendMemoryCopyRegion = xe_layer::val.xeDdiTable.CommandList.pfnAppendMemoryCopyRegion;

    if( nullptr == pfnAppendMemoryCopyRegion )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == dstptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == dstRegion )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == srcptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == srcRegion )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendMemoryCopyRegion( hCommandList, dstptr, dstRegion, dstPitch, srcptr, srcRegion, srcPitch, hEvent );
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
    auto pfnAppendImageCopy = xe_layer::val.xeDdiTable.CommandList.pfnAppendImageCopy;

    if( nullptr == pfnAppendImageCopy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hDstImage )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hSrcImage )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendImageCopy( hCommandList, hDstImage, hSrcImage, hEvent );
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
    auto pfnAppendImageCopyRegion = xe_layer::val.xeDdiTable.CommandList.pfnAppendImageCopyRegion;

    if( nullptr == pfnAppendImageCopyRegion )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hDstImage )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hSrcImage )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendImageCopyRegion( hCommandList, hDstImage, hSrcImage, pDstRegion, pSrcRegion, hEvent );
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
    auto pfnAppendImageCopyToMemory = xe_layer::val.xeDdiTable.CommandList.pfnAppendImageCopyToMemory;

    if( nullptr == pfnAppendImageCopyToMemory )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == dstptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hSrcImage )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendImageCopyToMemory( hCommandList, dstptr, hSrcImage, pSrcRegion, hEvent );
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
    auto pfnAppendImageCopyFromMemory = xe_layer::val.xeDdiTable.CommandList.pfnAppendImageCopyFromMemory;

    if( nullptr == pfnAppendImageCopyFromMemory )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hDstImage )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == srcptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendImageCopyFromMemory( hCommandList, hDstImage, srcptr, pDstRegion, hEvent );
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
    auto pfnAppendMemoryPrefetch = xe_layer::val.xeDdiTable.CommandList.pfnAppendMemoryPrefetch;

    if( nullptr == pfnAppendMemoryPrefetch )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendMemoryPrefetch( hCommandList, ptr, count );
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
    auto pfnAppendMemAdvise = xe_layer::val.xeDdiTable.CommandList.pfnAppendMemAdvise;

    if( nullptr == pfnAppendMemAdvise )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendMemAdvise( hCommandList, hDevice, ptr, size, advice );
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
    auto pfnCreate = xe_layer::val.xeDdiTable.EventPool.pfnCreate;

    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == desc )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phEventPool )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( XE_EVENT_POOL_DESC_VERSION_CURRENT < desc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return pfnCreate( hDevice, desc, phEventPool );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventPoolDestroy
xe_result_t __xecall
xeEventPoolDestroy(
    xe_event_pool_handle_t hEventPool               ///< [in] handle of event pool object to destroy
    )
{
    auto pfnDestroy = xe_layer::val.xeDdiTable.EventPool.pfnDestroy;

    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hEventPool )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnDestroy( hEventPool );
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
    auto pfnCreate = xe_layer::val.xeDdiTable.Event.pfnCreate;

    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hEventPool )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == desc )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phEvent )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( XE_EVENT_DESC_VERSION_CURRENT < desc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return pfnCreate( hEventPool, desc, phEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventDestroy
xe_result_t __xecall
xeEventDestroy(
    xe_event_handle_t hEvent                        ///< [in] handle of event object to destroy
    )
{
    auto pfnDestroy = xe_layer::val.xeDdiTable.Event.pfnDestroy;

    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hEvent )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnDestroy( hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventPoolGetIpcHandle
xe_result_t __xecall
xeEventPoolGetIpcHandle(
    xe_event_pool_handle_t hEventPool,              ///< [in] handle of event pool object
    xe_ipc_event_pool_handle_t* phIpc               ///< [out] Returned IPC event handle
    )
{
    auto pfnGetIpcHandle = xe_layer::val.xeDdiTable.EventPool.pfnGetIpcHandle;

    if( nullptr == pfnGetIpcHandle )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hEventPool )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phIpc )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetIpcHandle( hEventPool, phIpc );
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
    auto pfnOpenIpcHandle = xe_layer::val.xeDdiTable.EventPool.pfnOpenIpcHandle;

    if( nullptr == pfnOpenIpcHandle )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hIpc )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phEventPool )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnOpenIpcHandle( hDevice, hIpc, phEventPool );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventPoolCloseIpcHandle
xe_result_t __xecall
xeEventPoolCloseIpcHandle(
    xe_event_pool_handle_t hEventPool               ///< [in] handle of event pool object
    )
{
    auto pfnCloseIpcHandle = xe_layer::val.xeDdiTable.EventPool.pfnCloseIpcHandle;

    if( nullptr == pfnCloseIpcHandle )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hEventPool )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnCloseIpcHandle( hEventPool );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendSignalEvent
xe_result_t __xecall
xeCommandListAppendSignalEvent(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    auto pfnAppendSignalEvent = xe_layer::val.xeDdiTable.CommandList.pfnAppendSignalEvent;

    if( nullptr == pfnAppendSignalEvent )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hEvent )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendSignalEvent( hCommandList, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendWaitOnEvents
xe_result_t __xecall
xeCommandListAppendWaitOnEvents(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numEvents,                             ///< [in] number of events to wait on before continuing
    xe_event_handle_t* phEvents                     ///< [in][range(0, numEvents)] handle of the events to wait on before
                                                    ///< continuing
    )
{
    auto pfnAppendWaitOnEvents = xe_layer::val.xeDdiTable.CommandList.pfnAppendWaitOnEvents;

    if( nullptr == pfnAppendWaitOnEvents )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phEvents )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendWaitOnEvents( hCommandList, numEvents, phEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventHostSignal
xe_result_t __xecall
xeEventHostSignal(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    auto pfnHostSignal = xe_layer::val.xeDdiTable.Event.pfnHostSignal;

    if( nullptr == pfnHostSignal )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hEvent )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnHostSignal( hEvent );
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
    auto pfnHostSynchronize = xe_layer::val.xeDdiTable.Event.pfnHostSynchronize;

    if( nullptr == pfnHostSynchronize )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hEvent )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnHostSynchronize( hEvent, timeout );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventQueryStatus
xe_result_t __xecall
xeEventQueryStatus(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    auto pfnQueryStatus = xe_layer::val.xeDdiTable.Event.pfnQueryStatus;

    if( nullptr == pfnQueryStatus )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hEvent )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnQueryStatus( hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendEventReset
xe_result_t __xecall
xeCommandListAppendEventReset(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    auto pfnAppendEventReset = xe_layer::val.xeDdiTable.CommandList.pfnAppendEventReset;

    if( nullptr == pfnAppendEventReset )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hEvent )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendEventReset( hCommandList, hEvent );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeEventReset
xe_result_t __xecall
xeEventReset(
    xe_event_handle_t hEvent                        ///< [in] handle of the event
    )
{
    auto pfnReset = xe_layer::val.xeDdiTable.Event.pfnReset;

    if( nullptr == pfnReset )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hEvent )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnReset( hEvent );
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
    auto pfnCreate = xe_layer::val.xeDdiTable.Fence.pfnCreate;

    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandQueue )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == desc )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phFence )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( XE_FENCE_DESC_VERSION_CURRENT < desc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return pfnCreate( hCommandQueue, desc, phFence );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFenceDestroy
xe_result_t __xecall
xeFenceDestroy(
    xe_fence_handle_t hFence                        ///< [in] handle of fence object to destroy
    )
{
    auto pfnDestroy = xe_layer::val.xeDdiTable.Fence.pfnDestroy;

    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hFence )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnDestroy( hFence );
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
    auto pfnHostSynchronize = xe_layer::val.xeDdiTable.Fence.pfnHostSynchronize;

    if( nullptr == pfnHostSynchronize )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hFence )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnHostSynchronize( hFence, timeout );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFenceQueryStatus
xe_result_t __xecall
xeFenceQueryStatus(
    xe_fence_handle_t hFence                        ///< [in] handle of the fence
    )
{
    auto pfnQueryStatus = xe_layer::val.xeDdiTable.Fence.pfnQueryStatus;

    if( nullptr == pfnQueryStatus )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hFence )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnQueryStatus( hFence );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFenceReset
xe_result_t __xecall
xeFenceReset(
    xe_fence_handle_t hFence                        ///< [in] handle of the fence
    )
{
    auto pfnReset = xe_layer::val.xeDdiTable.Fence.pfnReset;

    if( nullptr == pfnReset )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hFence )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnReset( hFence );
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
    auto pfnGetProperties = xe_layer::val.xeDdiTable.Image.pfnGetProperties;

    if( nullptr == pfnGetProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == desc )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pImageProperties )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( XE_IMAGE_DESC_VERSION_CURRENT < desc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return pfnGetProperties( hDevice, desc, pImageProperties );
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
    auto pfnCreate = xe_layer::val.xeDdiTable.Image.pfnCreate;

    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == desc )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phImage )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( XE_IMAGE_DESC_VERSION_CURRENT < desc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return pfnCreate( hDevice, desc, phImage );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeImageDestroy
xe_result_t __xecall
xeImageDestroy(
    xe_image_handle_t hImage                        ///< [in] handle of image object to destroy
    )
{
    auto pfnDestroy = xe_layer::val.xeDdiTable.Image.pfnDestroy;

    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hImage )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnDestroy( hImage );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupAllocSharedMem
xe_result_t __xecall
xeDeviceGroupAllocSharedMem(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_mem_alloc_flag_t device_flags,        ///< [in] flags specifying additional device allocation controls
    xe_host_mem_alloc_flag_t host_flags,            ///< [in] flags specifying additional host allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to shared allocation
    )
{
    auto pfnAllocSharedMem = xe_layer::val.xeDdiTable.DeviceGroup.pfnAllocSharedMem;

    if( nullptr == pfnAllocSharedMem )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAllocSharedMem( hDeviceGroup, hDevice, device_flags, host_flags, size, alignment, ptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupAllocDeviceMem
xe_result_t __xecall
xeDeviceGroupAllocDeviceMem(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_device_mem_alloc_flag_t flags,               ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to device allocation
    )
{
    auto pfnAllocDeviceMem = xe_layer::val.xeDdiTable.DeviceGroup.pfnAllocDeviceMem;

    if( nullptr == pfnAllocDeviceMem )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAllocDeviceMem( hDeviceGroup, hDevice, flags, size, alignment, ptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupAllocHostMem
xe_result_t __xecall
xeDeviceGroupAllocHostMem(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_host_mem_alloc_flag_t flags,                 ///< [in] flags specifying additional allocation controls
    size_t size,                                    ///< [in] size in bytes to allocate
    size_t alignment,                               ///< [in] minimum alignment in bytes for the allocation
    void** ptr                                      ///< [out] pointer to host allocation
    )
{
    auto pfnAllocHostMem = xe_layer::val.xeDdiTable.DeviceGroup.pfnAllocHostMem;

    if( nullptr == pfnAllocHostMem )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAllocHostMem( hDeviceGroup, flags, size, alignment, ptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupFreeMem
xe_result_t __xecall
xeDeviceGroupFreeMem(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    const void* ptr                                 ///< [in] pointer to memory to free
    )
{
    auto pfnFreeMem = xe_layer::val.xeDdiTable.DeviceGroup.pfnFreeMem;

    if( nullptr == pfnFreeMem )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnFreeMem( hDeviceGroup, ptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetMemProperties
xe_result_t __xecall
xeDeviceGroupGetMemProperties(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    const void* ptr,                                ///< [in] Pointer to query
    xe_memory_allocation_properties_t* pMemProperties   ///< [out] Query result for memory allocation properties
    )
{
    auto pfnGetMemProperties = xe_layer::val.xeDdiTable.DeviceGroup.pfnGetMemProperties;

    if( nullptr == pfnGetMemProperties )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pMemProperties )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetMemProperties( hDeviceGroup, ptr, pMemProperties );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetMemAddressRange
xe_result_t __xecall
xeDeviceGroupGetMemAddressRange(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    const void* ptr,                                ///< [in] Pointer to query
    void** pBase,                                   ///< [in,out][optional] base address of the allocation
    size_t* pSize                                   ///< [in,out][optional] size of the allocation
    )
{
    auto pfnGetMemAddressRange = xe_layer::val.xeDdiTable.DeviceGroup.pfnGetMemAddressRange;

    if( nullptr == pfnGetMemAddressRange )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetMemAddressRange( hDeviceGroup, ptr, pBase, pSize );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupGetMemIpcHandle
xe_result_t __xecall
xeDeviceGroupGetMemIpcHandle(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    const void* ptr,                                ///< [in] Pointer to the device memory allocation
    xe_ipc_mem_handle_t* pIpcHandle                 ///< [out] Returned IPC memory handle
    )
{
    auto pfnGetMemIpcHandle = xe_layer::val.xeDdiTable.DeviceGroup.pfnGetMemIpcHandle;

    if( nullptr == pfnGetMemIpcHandle )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pIpcHandle )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetMemIpcHandle( hDeviceGroup, ptr, pIpcHandle );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupOpenMemIpcHandle
xe_result_t __xecall
xeDeviceGroupOpenMemIpcHandle(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    xe_device_handle_t hDevice,                     ///< [in] handle of the device to associate with the IPC memory handle
    xe_ipc_mem_handle_t handle,                     ///< [in] IPC memory handle
    xe_ipc_memory_flag_t flags,                     ///< [in] flags controlling the operation
    void** ptr                                      ///< [out] pointer to device allocation in this process
    )
{
    auto pfnOpenMemIpcHandle = xe_layer::val.xeDdiTable.DeviceGroup.pfnOpenMemIpcHandle;

    if( nullptr == pfnOpenMemIpcHandle )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == handle )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnOpenMemIpcHandle( hDeviceGroup, hDevice, handle, flags, ptr );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceGroupCloseMemIpcHandle
xe_result_t __xecall
xeDeviceGroupCloseMemIpcHandle(
    xe_device_group_handle_t hDeviceGroup,          ///< [in] handle of the device group object
    const void* ptr                                 ///< [in] pointer to device allocation in this process
    )
{
    auto pfnCloseMemIpcHandle = xe_layer::val.xeDdiTable.DeviceGroup.pfnCloseMemIpcHandle;

    if( nullptr == pfnCloseMemIpcHandle )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDeviceGroup )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnCloseMemIpcHandle( hDeviceGroup, ptr );
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
    auto pfnCreate = xe_layer::val.xeDdiTable.Module.pfnCreate;

    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pDesc )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phModule )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( XE_MODULE_DESC_VERSION_CURRENT < pDesc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return pfnCreate( hDevice, pDesc, phModule, phBuildLog );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleDestroy
xe_result_t __xecall
xeModuleDestroy(
    xe_module_handle_t hModule                      ///< [in] handle of the module
    )
{
    auto pfnDestroy = xe_layer::val.xeDdiTable.Module.pfnDestroy;

    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hModule )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnDestroy( hModule );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeModuleBuildLogDestroy
xe_result_t __xecall
xeModuleBuildLogDestroy(
    xe_module_build_log_handle_t hModuleBuildLog    ///< [in] handle of the module build log object.
    )
{
    auto pfnDestroy = xe_layer::val.xeDdiTable.ModuleBuildLog.pfnDestroy;

    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hModuleBuildLog )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnDestroy( hModuleBuildLog );
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
    auto pfnGetString = xe_layer::val.xeDdiTable.ModuleBuildLog.pfnGetString;

    if( nullptr == pfnGetString )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hModuleBuildLog )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pSize )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetString( hModuleBuildLog, pSize, pBuildLog );
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
    auto pfnGetNativeBinary = xe_layer::val.xeDdiTable.Module.pfnGetNativeBinary;

    if( nullptr == pfnGetNativeBinary )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hModule )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pSize )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetNativeBinary( hModule, pSize, pModuleNativeBinary );
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
    auto pfnGetGlobalPointer = xe_layer::val.xeDdiTable.Module.pfnGetGlobalPointer;

    if( nullptr == pfnGetGlobalPointer )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hModule )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pGlobalName )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pPtr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetGlobalPointer( hModule, pGlobalName, pPtr );
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
    auto pfnCreate = xe_layer::val.xeDdiTable.Function.pfnCreate;

    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hModule )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pDesc )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phFunction )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( XE_FUNCTION_DESC_VERSION_CURRENT < pDesc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return pfnCreate( hModule, pDesc, phFunction );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionDestroy
xe_result_t __xecall
xeFunctionDestroy(
    xe_function_handle_t hFunction                  ///< [in] handle of the function object
    )
{
    auto pfnDestroy = xe_layer::val.xeDdiTable.Function.pfnDestroy;

    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hFunction )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnDestroy( hFunction );
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
    auto pfnGetFunctionPointer = xe_layer::val.xeDdiTable.Module.pfnGetFunctionPointer;

    if( nullptr == pfnGetFunctionPointer )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hModule )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pFunctionName )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pfnFunction )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetFunctionPointer( hModule, pFunctionName, pfnFunction );
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
    auto pfnSetGroupSize = xe_layer::val.xeDdiTable.Function.pfnSetGroupSize;

    if( nullptr == pfnSetGroupSize )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hFunction )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnSetGroupSize( hFunction, groupSizeX, groupSizeY, groupSizeZ );
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
    auto pfnSuggestGroupSize = xe_layer::val.xeDdiTable.Function.pfnSuggestGroupSize;

    if( nullptr == pfnSuggestGroupSize )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hFunction )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == groupSizeX )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == groupSizeY )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == groupSizeZ )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnSuggestGroupSize( hFunction, globalSizeX, globalSizeY, globalSizeZ, groupSizeX, groupSizeY, groupSizeZ );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionSetArgumentValue
xe_result_t __xecall
xeFunctionSetArgumentValue(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function args object.
    uint32_t argIndex,                              ///< [in] argument index in range [0, num args - 1]
    size_t argSize,                                 ///< [in] size of argument type
    const void* pArgValue                           ///< [in][optional] argument value represented as matching arg type. If
                                                    ///< null then argument value is considered null.
    )
{
    auto pfnSetArgumentValue = xe_layer::val.xeDdiTable.Function.pfnSetArgumentValue;

    if( nullptr == pfnSetArgumentValue )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hFunction )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnSetArgumentValue( hFunction, argIndex, argSize, pArgValue );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeFunctionSetAttribute
xe_result_t __xecall
xeFunctionSetAttribute(
    xe_function_handle_t hFunction,                 ///< [in] handle of the function.
    xe_function_set_attribute_t attr,               ///< [in] attribute to set
    uint32_t value                                  ///< [in] attribute value to set
    )
{
    auto pfnSetAttribute = xe_layer::val.xeDdiTable.Function.pfnSetAttribute;

    if( nullptr == pfnSetAttribute )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hFunction )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnSetAttribute( hFunction, attr, value );
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
    auto pfnGetAttribute = xe_layer::val.xeDdiTable.Function.pfnGetAttribute;

    if( nullptr == pfnGetAttribute )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hFunction )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pValue )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnGetAttribute( hFunction, attr, pValue );
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
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    auto pfnAppendLaunchFunction = xe_layer::val.xeDdiTable.CommandList.pfnAppendLaunchFunction;

    if( nullptr == pfnAppendLaunchFunction )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hFunction )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pLaunchFuncArgs )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendLaunchFunction( hCommandList, hFunction, pLaunchFuncArgs, hSignalEvent, numWaitEvents, phWaitEvents );
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
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    auto pfnAppendLaunchFunctionIndirect = xe_layer::val.xeDdiTable.CommandList.pfnAppendLaunchFunctionIndirect;

    if( nullptr == pfnAppendLaunchFunctionIndirect )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hFunction )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pLaunchArgumentsBuffer )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendLaunchFunctionIndirect( hCommandList, hFunction, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeCommandListAppendLaunchMultipleFunctionsIndirect
xe_result_t __xecall
xeCommandListAppendLaunchMultipleFunctionsIndirect(
    xe_command_list_handle_t hCommandList,          ///< [in] handle of the command list
    uint32_t numFunctions,                          ///< [in] maximum number of functions to launch
    xe_function_handle_t* phFunctions,              ///< [in][range(0, numFunctions)] handles of the function objects
    const uint32_t* pNumLaunchArguments,            ///< [in] pointer to device memory location that will contain the actual
                                                    ///< number of launch arguments; value must be less-than or equal-to
                                                    ///< numFunctions
    const xe_thread_group_dimensions_t* pLaunchArgumentsBuffer, ///< [in][range(0, numFunctions)] pointer to device buffer that will
                                                    ///< contain a contiguous array of launch arguments
    xe_event_handle_t hSignalEvent,                 ///< [in][optional] handle of the event to signal on completion
    uint32_t numWaitEvents,                         ///< [in][optional] number of events to wait on before launching
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    auto pfnAppendLaunchMultipleFunctionsIndirect = xe_layer::val.xeDdiTable.CommandList.pfnAppendLaunchMultipleFunctionsIndirect;

    if( nullptr == pfnAppendLaunchMultipleFunctionsIndirect )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phFunctions )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pNumLaunchArguments )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pLaunchArgumentsBuffer )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendLaunchMultipleFunctionsIndirect( hCommandList, numFunctions, phFunctions, pNumLaunchArguments, pLaunchArgumentsBuffer, hSignalEvent, numWaitEvents, phWaitEvents );
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
    xe_event_handle_t* phWaitEvents                 ///< [in][optional][range(0, numWaitEvents)] handle of the events to wait
                                                    ///< on before launching
    )
{
    auto pfnAppendLaunchHostFunction = xe_layer::val.xeDdiTable.CommandList.pfnAppendLaunchHostFunction;

    if( nullptr == pfnAppendLaunchHostFunction )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hCommandList )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pUserData )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnAppendLaunchHostFunction( hCommandList, pfnHostFunc, pUserData, hSignalEvent, numWaitEvents, phWaitEvents );
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
    auto pfnMakeMemoryResident = xe_layer::val.xeDdiTable.Device.pfnMakeMemoryResident;

    if( nullptr == pfnMakeMemoryResident )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnMakeMemoryResident( hDevice, ptr, size );
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
    auto pfnEvictMemory = xe_layer::val.xeDdiTable.Device.pfnEvictMemory;

    if( nullptr == pfnEvictMemory )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == ptr )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnEvictMemory( hDevice, ptr, size );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceMakeImageResident
xe_result_t __xecall
xeDeviceMakeImageResident(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_image_handle_t hImage                        ///< [in] handle of image to make resident
    )
{
    auto pfnMakeImageResident = xe_layer::val.xeDdiTable.Device.pfnMakeImageResident;

    if( nullptr == pfnMakeImageResident )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hImage )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnMakeImageResident( hDevice, hImage );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeDeviceEvictImage
xe_result_t __xecall
xeDeviceEvictImage(
    xe_device_handle_t hDevice,                     ///< [in] handle of the device
    xe_image_handle_t hImage                        ///< [in] handle of image to make evict
    )
{
    auto pfnEvictImage = xe_layer::val.xeDdiTable.Device.pfnEvictImage;

    if( nullptr == pfnEvictImage )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == hImage )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnEvictImage( hDevice, hImage );
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
    auto pfnCreate = xe_layer::val.xeDdiTable.Sampler.pfnCreate;

    if( nullptr == pfnCreate )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hDevice )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == pDesc )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( nullptr == phSampler )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

        if( XE_SAMPLER_DESC_VERSION_CURRENT < pDesc->version )
            return XE_RESULT_ERROR_UNSUPPORTED;

    }

    return pfnCreate( hDevice, pDesc, phSampler );
}

///////////////////////////////////////////////////////////////////////////////
/// @brief Intercept function for xeSamplerDestroy
xe_result_t __xecall
xeSamplerDestroy(
    xe_sampler_handle_t hSampler                    ///< [in] handle of the sampler
    )
{
    auto pfnDestroy = xe_layer::val.xeDdiTable.Sampler.pfnDestroy;

    if( nullptr == pfnDestroy )
        return XE_RESULT_ERROR_UNSUPPORTED;

    if( xe_layer::val.enableParameterValidation )
    {
        if( nullptr == hSampler )
            return XE_RESULT_ERROR_INVALID_ARGUMENT;

    }

    return pfnDestroy( hSampler );
}

#if defined(__cplusplus)
};
#endif
