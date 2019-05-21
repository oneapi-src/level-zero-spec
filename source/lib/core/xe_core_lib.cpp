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
* @file xe_core_lib.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/libddi.cpp.mako
* @endcond
*
******************************************************************************/
#include "xe_lib.h"

namespace xe_lib
{
    ///////////////////////////////////////////////////////////////////////////////
    xe_result_t Library::Init()
    {
        loader = LOAD_DRIVER_LIBRARY( MAKE_DRIVER_NAME( "xe_loader" ) );

        if( NULL == loader )
            return XE_RESULT_ERROR_UNINITIALIZED;

        xe_result_t result = XE_RESULT_SUCCESS;

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetGlobalProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Global );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetDeviceProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Device );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetDeviceGroupProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetDeviceGroupProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.DeviceGroup );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetCommandQueueProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetCommandQueueProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.CommandQueue );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetCommandListProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.CommandList );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetFenceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetFenceProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Fence );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetEventPoolProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetEventPoolProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.EventPool );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetEventProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetEventProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Event );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetImageProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetImageProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Image );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetModuleProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetModuleProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Module );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetModuleBuildLogProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetModuleBuildLogProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.ModuleBuildLog );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetFunctionProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetFunctionProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Function );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xe_pfnGetSamplerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xeGetSamplerProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &ddiTable.Sampler );
        }

        return result;
    }
} // namespace xe_lib
