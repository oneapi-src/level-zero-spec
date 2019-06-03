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
#include "xe_lib.h"

extern "C" {

} // extern "C"

namespace xe
{
} // namespace xe

#ifdef _DEBUG
///////////////////////////////////////////////////////////////////////////////
/// @brief Converts result_t to std::string
std::string to_string( xe::result_t val )
{
    std::string str;
    switch( val )
    {
    case xe::result_t::SUCCESS:
        str = "xe::result_t::SUCCESS";
    case xe::result_t::NOT_READY:
        str = "xe::result_t::NOT_READY";
    case xe::result_t::ERROR_UNINITIALIZED:
        str = "xe::result_t::ERROR_UNINITIALIZED";
    case xe::result_t::ERROR_DEVICE_LOST:
        str = "xe::result_t::ERROR_DEVICE_LOST";
    case xe::result_t::ERROR_UNSUPPORTED:
        str = "xe::result_t::ERROR_UNSUPPORTED";
    case xe::result_t::ERROR_INVALID_ARGUMENT:
        str = "xe::result_t::ERROR_INVALID_ARGUMENT";
    case xe::result_t::ERROR_OUT_OF_HOST_MEMORY:
        str = "xe::result_t::ERROR_OUT_OF_HOST_MEMORY";
    case xe::result_t::ERROR_OUT_OF_DEVICE_MEMORY:
        str = "xe::result_t::ERROR_OUT_OF_DEVICE_MEMORY";
    case xe::result_t::ERROR_MODULE_BUILD_FAILURE:
        str = "xe::result_t::ERROR_MODULE_BUILD_FAILURE";
    case xe::result_t::ERROR_UNKNOWN:
        str = "xe::result_t::ERROR_UNKNOWN";
    default:
        str = "xe::result_t::?";
    };
    return str;
}

#endif // _DEBUG
