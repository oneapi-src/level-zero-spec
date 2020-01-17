/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file ze_sampler.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero APIs for Sampler
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/sampler.yml
 * @endcond
 *
 */
#include "ze_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Creates sampler object.
/// 
/// @details
///     - The sampler can only be used on the device on which it was created.
///     - The application may call this function from simultaneous threads.
///     - The implementation of this function should be lock-free.
/// 
/// @remarks
///   _Analogues_
///     - **cuTexObjectCreate**
/// 
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hDevice`
///     - ::ZE_RESULT_ERROR_INVALID_NULL_POINTER
///         + `nullptr == desc`
///         + `nullptr == phSampler`
///     - ::ZE_RESULT_ERROR_UNSUPPORTED_VERSION
///         + `::ZE_SAMPLER_DESC_VERSION_CURRENT < desc->version`
///     - ::ZE_RESULT_ERROR_INVALID_ENUMERATION
///         + desc->addressMode
///         + desc->filterMode
///     - ::ZE_RESULT_ERROR_OUT_OF_HOST_MEMORY
ze_result_t __zecall
zeSamplerCreate(
    ze_device_handle_t hDevice,                     ///< [in] handle of the device
    const ze_sampler_desc_t* desc,                  ///< [in] pointer to sampler descriptor
    ze_sampler_handle_t* phSampler                  ///< [out] handle of the sampler
    )
{
    auto pfnCreate = ze_lib::context.ddiTable.Sampler.pfnCreate;
    if( nullptr == pfnCreate )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnCreate( hDevice, desc, phSampler );
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
/// @returns
///     - ::ZE_RESULT_SUCCESS
///     - ::ZE_RESULT_ERROR_UNINITIALIZED
///     - ::ZE_RESULT_ERROR_DEVICE_LOST
///     - ::ZE_RESULT_ERROR_INVALID_NULL_HANDLE
///         + `nullptr == hSampler`
///     - ::ZE_RESULT_ERROR_HANDLE_OBJECT_IN_USE
ze_result_t __zecall
zeSamplerDestroy(
    ze_sampler_handle_t hSampler                    ///< [in][release] handle of the sampler
    )
{
    auto pfnDestroy = ze_lib::context.ddiTable.Sampler.pfnDestroy;
    if( nullptr == pfnDestroy )
        return ZE_RESULT_ERROR_UNSUPPORTED_VERSION;

    return pfnDestroy( hSampler );
}

} // extern "C"

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    Sampler::Sampler( 
        sampler_handle_t handle,                        ///< [in] handle of the sample object
        Device* pDevice,                                ///< [in] pointer to owner object
        const desc_t* desc                              ///< [in] sampler descriptor
        ) :
        m_handle( handle ),
        m_pDevice( pDevice ),
        m_desc( ( desc ) ? *desc : desc_t{} )
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Creates sampler object.
    /// 
    /// @details
    ///     - The sampler can only be used on the device on which it was created.
    ///     - The application may call this function from simultaneous threads.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @remarks
    ///   _Analogues_
    ///     - **cuTexObjectCreate**
    /// 
    /// @returns
    ///     - Sampler*: handle of the sampler
    /// 
    /// @throws result_t
    Sampler* __zecall
    Sampler::Create(
        Device* pDevice,                                ///< [in] pointer to the device
        const desc_t* desc                              ///< [in] pointer to sampler descriptor
        )
    {
        ze_sampler_handle_t hSampler;

        auto result = static_cast<result_t>( ::zeSamplerCreate(
            reinterpret_cast<ze_device_handle_t>( pDevice->getHandle() ),
            reinterpret_cast<const ze_sampler_desc_t*>( desc ),
            &hSampler ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Sampler::Create" );

        Sampler* pSampler = nullptr;

        try
        {
            pSampler = new Sampler( reinterpret_cast<sampler_handle_t>( hSampler ), pDevice, desc );
        }
        catch( std::bad_alloc& )
        {
            delete pSampler;
            pSampler = nullptr;

            throw exception_t( result_t::ERROR_OUT_OF_HOST_MEMORY, __FILE__, STRING(__LINE__), "ze::Sampler::Create" );
        }

        return pSampler;
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
    void __zecall
    Sampler::Destroy(
        Sampler* pSampler                               ///< [in][release] pointer to the sampler
        )
    {
        auto result = static_cast<result_t>( ::zeSamplerDestroy(
            reinterpret_cast<ze_sampler_handle_t>( pSampler->getHandle() ) ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "ze::Sampler::Destroy" );

        delete pSampler;
    }

} // namespace ze

namespace ze
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::desc_version_t to std::string
    std::string to_string( const Sampler::desc_version_t val )
    {
        std::string str;

        switch( val )
        {
        case Sampler::desc_version_t::CURRENT:
            str = "Sampler::desc_version_t::CURRENT";
            break;

        default:
            str = "Sampler::desc_version_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::address_mode_t to std::string
    std::string to_string( const Sampler::address_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case Sampler::address_mode_t::NONE:
            str = "Sampler::address_mode_t::NONE";
            break;

        case Sampler::address_mode_t::REPEAT:
            str = "Sampler::address_mode_t::REPEAT";
            break;

        case Sampler::address_mode_t::CLAMP:
            str = "Sampler::address_mode_t::CLAMP";
            break;

        case Sampler::address_mode_t::CLAMP_TO_BORDER:
            str = "Sampler::address_mode_t::CLAMP_TO_BORDER";
            break;

        case Sampler::address_mode_t::MIRROR:
            str = "Sampler::address_mode_t::MIRROR";
            break;

        default:
            str = "Sampler::address_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::filter_mode_t to std::string
    std::string to_string( const Sampler::filter_mode_t val )
    {
        std::string str;

        switch( val )
        {
        case Sampler::filter_mode_t::NEAREST:
            str = "Sampler::filter_mode_t::NEAREST";
            break;

        case Sampler::filter_mode_t::LINEAR:
            str = "Sampler::filter_mode_t::LINEAR";
            break;

        default:
            str = "Sampler::filter_mode_t::?";
            break;
        };

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Sampler::desc_t to std::string
    std::string to_string( const Sampler::desc_t val )
    {
        std::string str;
        
        str += "Sampler::desc_t::version : ";
        str += to_string(val.version);
        str += "\n";
        
        str += "Sampler::desc_t::addressMode : ";
        str += to_string(val.addressMode);
        str += "\n";
        
        str += "Sampler::desc_t::filterMode : ";
        str += to_string(val.filterMode);
        str += "\n";
        
        str += "Sampler::desc_t::isNormalized : ";
        str += std::to_string(val.isNormalized);
        str += "\n";

        return str;
    }

} // namespace ze
