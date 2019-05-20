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
* @file xet_sysman.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Tool APIs for System Management
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/sysman.yml
* @endcond
*
******************************************************************************/
#include "xet_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief temp
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == blob
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xetSysmanfoo(
    void* blob                                      ///< [in]
    )
{
    auto pfnfoo = xet_lib::lib.xetSysman.pfnfoo;

#if _DEBUG
    if( nullptr == pfnfoo )
        return XE_RESULT_ERROR_UNSUPPORTED;
#endif

    return pfnfoo( blob );
}

} // extern "C"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    Sysman::Sysman( 
        Device* pDevice                                 ///< [in] pointer to owner object
        ) :
        m_pDevice( pDevice )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief temp
    /// 
    /// @throws result_t
    void __xecall
    Sysman::foo(
        void
        )
    {
        // auto result = ::xetSysmanfoo( handle );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xet::Sysman::foo");
    }

} // namespace xet

#ifdef _DEBUG

#endif // _DEBUG
