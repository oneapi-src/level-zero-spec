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
* @file xe_sampler.hpp
*
* @brief C++ wrapper of Intel Xe Level-Zero APIs for Sampler
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/sampler.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_SAMPLER_HPP
#define _XE_SAMPLER_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XE_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief c++ wrapper for sampler
    class Sampler
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::sampler_desc_t
        enum class desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sampler addressing modes
        enum class address_mode_t
        {
            NONE = 0,                                       ///< No coordinate modifications for out-of-bounds image access.
            REPEAT,                                         ///< Out-of-bounds coordinates are wrapped back around.
            CLAMP,                                          ///< Out-of-bounds coordinates are clamped to edge.
            MIRROR,                                         ///< Out-of-bounds coordinates are mirrored starting from edge.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sampler filtering modes
        enum class filter_mode_t
        {
            NEAREST = 0,                                    ///< No coordinate modifications for out of bounds image access.
            LINEAR,                                         ///< Out-of-bounds coordinates are wrapped back around.

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sampler descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::SAMPLER_DESC_VERSION_CURRENT
            address_mode_t addressMode = address_mode_t::NONE;  ///< [in] Sampler addressing mode to determine how out-of-bounds
                                                            ///< coordinates are handled.
            filter_mode_t filterMode = filter_mode_t::NEAREST;  ///< [in] Sampler filter mode to determine how samples are filtered.
            bool_t isNormalized = true;                     ///< [in] Are coordinates normalized [0, 1] or not.

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        sampler_handle_t m_handle;                      ///< [in] handle of the sample object
        Device* m_pDevice;                              ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] sampler descriptor

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Sampler( void ) = delete;
        Sampler( 
            sampler_handle_t handle,                        ///< [in] handle of the sample object
            Device* pDevice,                                ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] sampler descriptor
            );

        ~Sampler( void ) = default;

        Sampler( Sampler const& other ) = delete;
        void operator=( Sampler const& other ) = delete;

        Sampler( Sampler&& other ) = delete;
        void operator=( Sampler&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevice( void ) const { return m_pDevice; }
        auto getDesc( void ) const { return m_desc; }

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
        /// @returns
        ///     - Sampler*: handle of the sampler
        /// 
        /// @throws result_t
        static Sampler* __xecall
        Create(
            Device* pDevice,                                ///< [in] pointer to the device
            const desc_t* desc                              ///< [in] pointer to sampler descriptor
            );

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
        /// @throws result_t
        static void __xecall
        Destroy(
            Sampler* pSampler                               ///< [in][release] pointer to the sampler
            );

    };

} // namespace xe

#ifdef _DEBUG
///////////////////////////////////////////////////////////////////////////////
/// @brief Converts Sampler::desc_version_t to std::string
std::string to_string( xe::Sampler::desc_version_t val );

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts Sampler::address_mode_t to std::string
std::string to_string( xe::Sampler::address_mode_t val );

///////////////////////////////////////////////////////////////////////////////
/// @brief Converts Sampler::filter_mode_t to std::string
std::string to_string( xe::Sampler::filter_mode_t val );


#endif // _DEBUG
#endif // defined(__cplusplus)
#endif // _XE_SAMPLER_HPP
