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
* @file xe_event.inl
*
* @brief C++ wrapper of Intel Xe Driver APIs for Event
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/event.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_EVENT_INL
#define _XE_EVENT_INL
#if defined(__cplusplus)
#pragma once
#include "xe_event.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeEventDestroy
    inline void Event::Destroy(
        )
    {
        // auto result = ::xeEventDestroy( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Event::Destroy");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeEventQueryStatus
    inline void Event::QueryStatus(
        )
    {
        // auto result = ::xeEventQueryStatus( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Event::QueryStatus");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for ::xeEventReset
    inline void Event::Reset(
        )
    {
        // auto result = ::xeEventReset( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Event::Reset");
    }

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_EVENT_INL
