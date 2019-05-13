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
* @file xe_common.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero API common types
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/common.yml
* @endcond
*
******************************************************************************/
#include "xe_api.hpp"
#include "xe_api.h"

namespace xe
{
#ifdef _DEBUG
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts result_t to std::string
    std::string to_string( result_t val )
    {
        switch( val )
        {
        case result_t::SUCCESS:
            return std::string("result_t::SUCCESS");
        case result_t::NOT_READY:
            return std::string("result_t::NOT_READY");
        case result_t::ERROR_UNINITIALIZED:
            return std::string("result_t::ERROR_UNINITIALIZED");
        case result_t::ERROR_DEVICE_LOST:
            return std::string("result_t::ERROR_DEVICE_LOST");
        case result_t::ERROR_UNSUPPORTED:
            return std::string("result_t::ERROR_UNSUPPORTED");
        case result_t::ERROR_INVALID_PARAMETER:
            return std::string("result_t::ERROR_INVALID_PARAMETER");
        case result_t::ERROR_OUT_OF_HOST_MEMORY:
            return std::string("result_t::ERROR_OUT_OF_HOST_MEMORY");
        case result_t::ERROR_OUT_OF_DEVICE_MEMORY:
            return std::string("result_t::ERROR_OUT_OF_DEVICE_MEMORY");
        case result_t::ERROR_MODULE_BUILD_FAILURE:
            return std::string("result_t::ERROR_MODULE_BUILD_FAILURE");
        case result_t::ERROR_UNKNOWN:
            return std::string("result_t::ERROR_UNKNOWN");
        };
        return std::string("result_t::?");
    }

#endif // _DEBUG
} // namespace xe
