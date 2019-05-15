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
* @file xex_extended_lib.cpp
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/templates/libimp.cpp.mako
* @endcond
*
******************************************************************************/
#include "xex_lib.h"

///////////////////////////////////////////////////////////////////////////////
xe_result_t xex_lib::Init()
{
    loader = LOAD_DRIVER_LIBRARY( "xe_loader" );

    if( NULL == context.loader )
        return XE_RESULT_ERROR_UNINITIALIZED;

    xe_result_t result = XE_RESULT_SUCCESS;

    if( XE_RESULT_SUCCESS == result )
    {
        auto getTable = reinterpret_cast<xex_pfnGetCommandGraphProcAddrTable_t>(
            GET_FUNCTION_PTR(context.loader, "xexGetCommandGraphProcAddrTable") );
        result = getTable( XE_API_VERSION_1_0, &xexCommandGraph );
    }

    if( XE_RESULT_SUCCESS == result )
    {
        auto getTable = reinterpret_cast<xex_pfnGetGlobalProcAddrTable_t>(
            GET_FUNCTION_PTR(context.loader, "xexGetGlobalProcAddrTable") );
        result = getTable( XE_API_VERSION_1_0, &xexGlobal );
    }

    return result;
}
