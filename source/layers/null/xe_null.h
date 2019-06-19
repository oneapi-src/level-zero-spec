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
#include <vector>
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

        xe_dditable_t   xeDdiTable = {};
        xex_dditable_t  xexDdiTable = {};
        xet_dditable_t  xetDdiTable = {};

        context_t();
        ~context_t() = default;

        void* get( void )
        {
            static uint64_t count = 0x80800000;
            return reinterpret_cast<void*>( ++count );
        }
    };

    extern context_t context;
} // namespace driver

namespace instrumented
{
    //////////////////////////////////////////////////////////////////////////
    struct tracer_data_t
    {
        bool enabled = false;

        void* globalUserData = nullptr;

        xe_callbacks_t xePrologueCbs = {};
        xe_callbacks_t xeEpilogueCbs = {};

        xex_callbacks_t xexPrologueCbs = {};
        xex_callbacks_t xexEpilogueCbs = {};
    };

    ///////////////////////////////////////////////////////////////////////////////
    class context_t
    {
    public:
        bool enableTracing = false;
        std::vector< tracer_data_t > tracerData;

        context_t();
        ~context_t() = default;
    };

    extern context_t context;
} // namespace instrumented
