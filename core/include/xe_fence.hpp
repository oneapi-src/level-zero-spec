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
* @file xe_fence.hpp
*
* @brief C++ wrapper of Intel Xe Driver APIs for Fence
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/core/fence.yml
* @endcond
*
******************************************************************************/
#ifndef _XE_FENCE_HPP
#define _XE_FENCE_HPP
#if defined(__cplusplus)
#pragma once
#include "xe_common.hpp"

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for fence
    class Fence
    {
    protected:
        ::xe_fence_handle_t handle;                       ///< handle of fence object
        ::xe_fence_desc_t desc;                           ///< descriptor of the fence object

    public:
        auto getHandle( void ) const { return handle; }
        auto getDesc( void ) const { return desc; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeFenceDestroy
        /// @throws result_t
        inline void
        Destroy(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeFenceHostSynchronize
        /// @throws result_t
        inline static void
        HostSynchronize(
            fence_handle_t hFence,                          ///< [in] handle of the fence
            uint32_t timeout                                ///< [in] if non-zero, then indicates the maximum time to yield before
                                                            ///< returning ::RESULT_SUCCESS or ::RESULT_NOT_READY; if zero, then
                                                            ///< operates exactly like ::FenceQueryStatus; if MAX_UINT32, then function
                                                            ///< will not return until complete or device is lost.
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeFenceQueryStatus
        /// @throws result_t
        inline void
        QueryStatus(
            void
            );

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xeFenceReset
        /// @throws result_t
        inline void
        Reset(
            void
            );

    };

} // namespace xe
#endif // defined(__cplusplus)
#endif // _XE_FENCE_HPP
