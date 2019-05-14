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
* @file xe_sampler.cpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Sampler
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/sampler.yml
* @endcond
*
******************************************************************************/
#include "xe_api.hpp"
#include "xe_api.h"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    Sampler::Sampler( 
        Device* pDevice,                                ///< [in] pointer to parent object
        const desc_t& desc                              ///< [in] sampler descriptor
        ) :
        m_pDevice( pDevice ),
        m_desc( desc )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates sampler object.
    /// 
    /// @details
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuTexObjectCreate**
    /// 
    /// @returns
    ///     - Sampler: handle of the sampler
    /// 
    /// @throws result_t
    Sampler* __xecall
    Sampler::Create(
        Device* pDevice,                                ///< [in] pointer to the device
        const desc_t* pDesc                             ///< [in] pointer to sampler descriptor
        )
    {
        // auto result = ::xeSamplerCreate( handle, pDevice, pDesc );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Sampler::Create");

        return (Sampler*)0;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Destroys sampler object
    /// 
    /// @details
    ///     - The application is responsible for making sure the device is not
    ///       currently referencing the sampler before it is deleted
    ///     - The implementation of this function will immediately free all Host and
    ///       Device allocations associated with this module
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same sampler handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuModuleUnload**
    /// 
    /// @throws result_t
    void __xecall
    Sampler::Destroy(
        Sampler* pSampler                               ///< [in] pointer to the sampler
        )
    {
        // auto result = ::xeSamplerDestroy( handle, pSampler );
        // if( ::XE_RESULT_SUCCESS != result ) throw exception(result, "xe::Sampler::Destroy");
    }

#ifdef _DEBUG
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::desc_version_t to std::string
    std::string to_string( Sampler::desc_version_t val )
    {
        switch( val )
        {
        case Sampler::desc_version_t::CURRENT:
            return std::string("Sampler::desc_version_t::CURRENT");
        };
        return std::string("Sampler::desc_version_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::address_mode_t to std::string
    std::string to_string( Sampler::address_mode_t val )
    {
        switch( val )
        {
        case Sampler::address_mode_t::NONE:
            return std::string("Sampler::address_mode_t::NONE");
        case Sampler::address_mode_t::REPEAT:
            return std::string("Sampler::address_mode_t::REPEAT");
        case Sampler::address_mode_t::CLAMP:
            return std::string("Sampler::address_mode_t::CLAMP");
        case Sampler::address_mode_t::MIRROR:
            return std::string("Sampler::address_mode_t::MIRROR");
        };
        return std::string("Sampler::address_mode_t::?");
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::filter_mode_t to std::string
    std::string to_string( Sampler::filter_mode_t val )
    {
        switch( val )
        {
        case Sampler::filter_mode_t::NEAREST:
            return std::string("Sampler::filter_mode_t::NEAREST");
        case Sampler::filter_mode_t::LINEAR:
            return std::string("Sampler::filter_mode_t::LINEAR");
        };
        return std::string("Sampler::filter_mode_t::?");
    }


#endif // _DEBUG
} // namespace xe
