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
* @file xet_tools_lib.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/libddi.cpp.mako
* @endcond
*
******************************************************************************/
#include "xet_lib.h"

namespace xet_lib
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
            auto getTable = reinterpret_cast<xet_pfnGetDeviceProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetDeviceProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &xetDevice );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetCommandListProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetCommandListProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &xetCommandList );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetMetricGroupProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetMetricGroupProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &xetMetricGroup );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetMetricProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetMetricProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &xetMetric );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetMetricTracerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetMetricTracerProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &xetMetricTracer );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetMetricQueryPoolProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetMetricQueryPoolProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &xetMetricQueryPool );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetMetricQueryProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetMetricQueryProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &xetMetricQuery );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetPowerProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetPowerProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &xetPower );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetFreqDomainProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetFreqDomainProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &xetFreqDomain );
        }

        if( XE_RESULT_SUCCESS == result )
        {
            auto getTable = reinterpret_cast<xet_pfnGetGlobalProcAddrTable_t>(
                GET_FUNCTION_PTR(loader, "xetGetGlobalProcAddrTable") );
            result = getTable( XE_API_VERSION_1_0, &xetGlobal );
        }

        return result;
    }
} // namespace xet_lib
