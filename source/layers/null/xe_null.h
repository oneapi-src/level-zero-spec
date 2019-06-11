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
#pragma once
#include <stdlib.h>
#include "xe_ddi.h"
#include "xex_ddi.h"
#include "xet_ddi.h"
#include "xe_util.h"

namespace driver
{
    ///////////////////////////////////////////////////////////////////////////////
    class context_t
    {
    public:
        xe_api_version_t version = XE_API_VERSION_1_0;

        xe_device_properties_t deviceProperties = {};
        xe_device_compute_properties_t computeProperties = {};
        xe_device_memory_properties_t memoryProperties = {};
        xe_device_memory_access_properties_t memoryAccessProperties = {};
        xe_device_cache_properties_t cacheProperties = {};
        xe_device_image_properties_t imageProperties = {};
        xe_device_p2p_properties_t p2pProperties = {};

        xet_metric_group_properties_t metricGroupProperties = {};
        xet_metric_properties_t metricProperties = {};

        bool enableTracing = false;
        xet_core_callbacks_t xePrologueCbs = {};
        xet_core_callbacks_t xeEpilogueCbs = {};
        xet_extended_callbacks_t xexPrologueCbs = {};
        xet_extended_callbacks_t xexEpilogueCbs = {};

        context_t();
        ~context_t() = default;

        void* get( void )
        {
            static uint64_t count = 0x80800000;
            return reinterpret_cast<void*>( ++count );
        }
    };

    extern context_t context;
}
