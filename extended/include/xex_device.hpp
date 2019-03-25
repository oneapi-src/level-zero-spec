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
* @file xex_device.hpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Extended APIs for Device
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/extended/device.yml
* @endcond
*
******************************************************************************/
#ifndef _XEX_DEVICE_HPP
#define _XEX_DEVICE_HPP
#if defined(__cplusplus)
#pragma once
#include "xex_common.hpp"

namespace xex
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for device
    class Device : public xe::Device
    {
    protected:
        ::xe_device_handle_t handle;                      ///< handle of device object

    public:
        auto getHandle( void ) const { return handle; }

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xex_command_graph_desc_version_t
        enum class command_graph_desc_version_t
        {
            CURRENT = XE_MAKE_VERSION( 1, 0 ),              ///< version 1.0

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xex_command_graph_flag_t
        enum class command_graph_flag_t
        {
            NONE = 0,                                       ///< default behavior

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ version for ::xex_command_graph_desc_t
        struct command_graph_desc_t
        {
            command_graph_desc_version_t version = command_graph_desc_version_t::CURRENT;   ///< [in] ::COMMAND_GRAPH_DESC_VERSION_CURRENT
            command_graph_flag_t flags = command_graph_flag_t::NONE;///< [in] creation flags

        };

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief C++ wrapper for ::xexDeviceCreateCommandGraph
        /// @returns
        ///     - ::command_graph_handle_t: pointer to handle of command graph object created
        /// 
        /// @throws result_t
        inline command_graph_handle_t
        CreateCommandGraph(
            const command_graph_desc_t* desc                ///< [in] pointer to command graph descriptor
            );

    };

} // namespace xex
#endif // defined(__cplusplus)
#endif // _XEX_DEVICE_HPP
