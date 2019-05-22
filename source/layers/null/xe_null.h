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
* @file xe_null.h
*
******************************************************************************/
#ifndef _XE_NULL_H
#define _XE_NULL_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_ddi.h"
#include "xex_ddi.h"
#include "xet_ddi.h"

///////////////////////////////////////////////////////////////////////////////
class Driver
{
public:
    xe_api_version_t version = XE_API_VERSION_1_0;

    Driver() = default;
    ~Driver() = default;

    xe_result_t xeInit( xe_init_flag_t flags ) { return XE_RESULT_SUCCESS; }
    xe_result_t xexInit( xe_init_flag_t flags ) { return XE_RESULT_SUCCESS; }
    xe_result_t xetInit( xe_init_flag_t flags ) { return XE_RESULT_SUCCESS; }

    xe_result_t xeGetDeviceGroups( uint32_t* pCount, xe_device_group_handle_t* pDeviceGroups )
    {
        if( nullptr != pCount ) *pCount = 1;
        if( nullptr != pDeviceGroups ) *pDeviceGroups = reinterpret_cast<xe_device_group_handle_t>(-1);
        return XE_RESULT_SUCCESS;
    }

    void* get( void )
    {
        static uint64_t count = 0x80800000;
        return reinterpret_cast<void*>( ++count );
    }
};

extern Driver driver;

#endif // _XE_NULL_H