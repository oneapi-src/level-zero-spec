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
* @file extended_loader.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/loader.cpp.mako
* @endcond
*
******************************************************************************/
#include "extended_loader.h"

///////////////////////////////////////////////////////////////////////////////
/// @brief Loads function pointer table for loaded driver
bool xexLoad(
    void* handle,                   ///< [in] driver handle
    xexapi_pfntable_t* pfntable )  ///< [in] pointer to table of xex API function pointers
{
    if(nullptr == pfntable){
        return false;
    }

    pfntable->xexCommandGraphCreate                                           = (pfn_xexCommandGraphCreate_t)LOAD_FUNCTION_PTR(handle, "xexCommandGraphCreate");
    pfntable->xexCommandGraphDestroy                                          = (pfn_xexCommandGraphDestroy_t)LOAD_FUNCTION_PTR(handle, "xexCommandGraphDestroy");
    pfntable->xexCommandGraphClose                                            = (pfn_xexCommandGraphClose_t)LOAD_FUNCTION_PTR(handle, "xexCommandGraphClose");

    if(nullptr == pfntable->xexCommandGraphCreate)
        return false;
    if(nullptr == pfntable->xexCommandGraphDestroy)
        return false;
    if(nullptr == pfntable->xexCommandGraphClose)
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
xexCommandGraphCreate(
        xe_device_handle_t hDevice,                     ///< [in] handle of the device object
        const xex_command_graph_desc_t* desc,           ///< [in] pointer to command graph descriptor
        xex_command_graph_handle_t* phCommandGraph      ///< [out] pointer to handle of command graph object created
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xexapi->xexCommandGraphCreate(hDevice, desc, phCommandGraph);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xexCommandGraphDestroy(
        xex_command_graph_handle_t hCommandGraph        ///< [in] handle of command graph object to destroy
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xexapi->xexCommandGraphDestroy(hCommandGraph);
}

///////////////////////////////////////////////////////////////////////////////
__xedllexport xe_result_t __xecall
xexCommandGraphClose(
        xex_command_graph_handle_t hCommandGraph        ///< [in] handle of command graph object to close
    ){
    if(false == context.initialized)
        return XE_RESULT_ERROR_UNINITIALIZED;

    return context.xexapi->xexCommandGraphClose(hCommandGraph);
}

#if defined(__cplusplus)
};
#endif
