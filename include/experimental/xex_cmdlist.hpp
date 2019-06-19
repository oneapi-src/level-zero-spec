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
* @file xex_cmdlist.hpp
*
* @brief C++ wrapper of Intel Xe Level-Zero Experimental APIs for Command List
*
* @cond DEV
* DO NOT EDIT: generated from /scripts/experimental/cmdlist.yml
* @endcond
*
******************************************************************************/
#ifndef _XEX_CMDLIST_HPP
#define _XEX_CMDLIST_HPP
#if defined(__cplusplus)
#pragma once
#if !defined(_XEX_API_HPP)
#pragma message("warning: this file is not intended to be included directly")
#endif

namespace xex
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief C++ wrapper for command list
    class CommandList : public xe::CommandList
    {
    public:

    protected:
        ///////////////////////////////////////////////////////////////////////////////

    public:
        ///////////////////////////////////////////////////////////////////////////////
        using xe::CommandList::CommandList;

        ~CommandList( void ) = default;

        CommandList( CommandList const& other ) = delete;
        void operator=( CommandList const& other ) = delete;

        CommandList( CommandList&& other ) = delete;
        void operator=( CommandList&& other ) = delete;

        ///////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////
        /// @brief Reserve a section of contiguous command buffer space within the
        ///        command list.
        /// 
        /// @details
        ///     - The pointer returned is valid for both Host and device access.
        ///     - The application may **not** call this function from simultaneous
        ///       threads with the same command list handle.
        ///     - The implementation of this function should be lock-free.
        /// @returns
        ///     - void*: pointer to command buffer space reserved
        /// 
        /// @throws result_t
        void* __xecall
        ReserveSpace(
            size_t size                                     ///< [in] size (in bytes) to reserve
            );

    };

} // namespace xex

namespace xex
{
} // namespace xex
#endif // defined(__cplusplus)
#endif // _XEX_CMDLIST_HPP
