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
* @file xet_tracing.hpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Tool APIs for API Tracing
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/tools/tracing.yml
* @endcond
*
******************************************************************************/
#ifndef _XET_TRACING_HPP
#define _XET_TRACING_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XET_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif
#include "xe_callbacks.h"
#include "xex_callbacks.h"

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for tracer
    class Tracer
    {
    public:
        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Alias the existing callbacks definition for 'core' callbacks
        using core_callbacks_t = xe_callbacks_t;

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Alias the existing callbacks definition for 'experimental' callbacks
        using experimental_callbacks_t = xex_callbacks_t;

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief API version of ::tracer_desc_t
        enum class desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Tracer descriptor
        struct desc_t
        {
            desc_version_t version = desc_version_t::CURRENT;   ///< [in] ::TRACER_DESC_VERSION_CURRENT
            void* pGlobalUserData;                          ///< [in] pointer to global data passes to every callback

        };


    protected:
        ///////////////////////////////////////////////////////////////////////////////
        tracer_handle_t m_handle;                       ///< [in] handle of tracer object
        DeviceGroup* m_pDeviceGroup;                    ///< [in] pointer to owner object
        desc_t m_desc;                                  ///< [in] descriptor of the tracer object

    public:
        ///////////////////////////////////////////////////////////////////////////////
        Tracer( void ) = delete;
        Tracer( 
            tracer_handle_t handle,                         ///< [in] handle of tracer object
            DeviceGroup* pDeviceGroup,                      ///< [in] pointer to owner object
            const desc_t* desc                              ///< [in] descriptor of the tracer object
            );

        ~Tracer( void ) = default;

        Tracer( Tracer const& other ) = delete;
        void operator=( Tracer const& other ) = delete;

        Tracer( Tracer&& other ) = delete;
        void operator=( Tracer&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////
        auto getHandle( void ) const { return m_handle; }
        auto getDevicegroup( void ) const { return m_pDeviceGroup; }
        auto getDesc( void ) const { return m_desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a tracer on the device group.
        /// 
        /// @details
        ///     - The tracer can only be used on the device group on which it was
        ///       created.
        ///     - The tracer is created in the disabled state.
        ///     - The application may call this function from simultaneous threads.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - Tracer*: pointer to handle of tracer object created
        /// 
        /// @throws result_t
        static Tracer* __xecall
        Create(
            DeviceGroup* pDeviceGroup,                      ///< [in] pointer to the device group
            const desc_t* desc                              ///< [in] pointer to tracer descriptor
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Destroys a tracer.
        /// 
        /// @details
        ///     - The implementation of this function will stall and wait on any
        ///       outstanding threads executing callbacks before freeing any Host
        ///       allocations associated with this tracer.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same tracer handle.
        ///     - The implementation of this function should be lock-free.
        /// @throws result_t
        static void __xecall
        Destroy(
            Tracer* pTracer                                 ///< [in][release] pointer to tracer object to destroy
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the collection of callbacks to be executed **before** driver
        ///        execution.
        /// 
        /// @details
        ///     - The application only needs to set the function pointers it is
        ///       interested in receiving; all others should be 'nullptr'
        ///     - The application must ensure that no other threads are executing
        ///       functions for which the tracing functions are changing.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same tracer handle.
        /// @throws result_t
        void __xecall
        SetPrologues(
            core_callbacks_t* pCoreCbs,                     ///< [in] pointer to table of 'core' callback function pointers
            experimental_callbacks_t* pExperimentalCbs = nullptr///< [in][optional] pointer to table of 'experimental' callback function
                                                            ///< pointers
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the collection of callbacks to be executed **after** driver
        ///        execution.
        /// 
        /// @details
        ///     - The application only needs to set the function pointers it is
        ///       interested in receiving; all others should be 'nullptr'
        ///     - The application must ensure that no other threads are executing
        ///       functions for which the tracing functions are changing.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same tracer handle.
        /// @throws result_t
        void __xecall
        SetEpilogues(
            core_callbacks_t* pCoreCbs,                     ///< [in] pointer to table of 'core' callback function pointers
            experimental_callbacks_t* pExperimentalCbs = nullptr///< [in][optional] pointer to table of 'experimental' callback function
                                                            ///< pointers
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Enables (or disables) the tracer
        /// 
        /// @details
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same tracer handle.
        /// @throws result_t
        void __xecall
        SetEnabled(
            xe::bool_t enable                               ///< [in] enable the tracer if true; disable if false
            );

    };

} // namespace xet

namespace xet
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Tracer::desc_version_t to std::string
    std::string to_string( const Tracer::desc_version_t val );

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts Tracer::desc_t to std::string
    std::string to_string( const Tracer::desc_t val );

} // namespace xet
#endif // defined(__cplusplus)
#endif // _XET_TRACING_HPP
