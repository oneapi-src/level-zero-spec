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
* @file xe_lib.h
*
******************************************************************************/
#ifndef _XE_LIB_H
#define _XE_LIB_H
#if defined(__cplusplus)
#pragma once
#endif
#include "xe_api.hpp"
#include "xe_ddi.h"
#include "xe_util.h"
#include <vector>

namespace xe_lib
{
    using namespace xe;

    ///////////////////////////////////////////////////////////////////////////////
    class Library
    {
    public:
        HMODULE loader = nullptr;

        Library();
        ~Library();

        xe_result_t Init();

        xe_dditable_t   ddiTable = {};
    };

    extern Library lib;

} // namespace xe_lib


///////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#include <sstream>
#if defined(__cplusplus)
namespace std
{
    inline string ptr_to_string( const void* ptr )
    {
        stringstream ss;
        ss << "0x" << hex << reinterpret_cast<size_t>( ptr );
        return ss.str();
    }

    inline string to_string( const uint8_t val[ 16 ] )
    {
        string str;
        for( uint32_t i = 0; i < 16; ++i )
        {
            str += to_string( val[ i ] );
            str += ", ";
        }
        return "{ " + str.substr( 0, str.size() - 2 ) + " }";;
    }

    inline string to_string( const uint32_t val[ 8 ] )
    {
        string str;
        for( uint32_t i = 0; i < 8; ++i )
        {
            str += to_string( val[ i ] );
            str += ", ";
        }
        return "{ " + str.substr( 0, str.size() - 2 ) + " }";;
    }
} // namespace std
#endif // __cplusplus
#endif // _DEBUG

#endif // _XE_LIB_H