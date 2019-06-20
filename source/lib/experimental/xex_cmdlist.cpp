/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xex_cmdlist.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero Experimental APIs for Command List
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/experimental/cmdlist.yml
 * @endcond
 *
 */
#include "xex_lib.h"

extern "C" {

///////////////////////////////////////////////////////////////////////////////
/// @brief Reserve a section of contiguous command buffer space within the
///        command list.
/// 
/// @details
///     - The pointer returned is valid for both Host and device access.
///     - The application may **not** call this function from simultaneous
///       threads with the same command list handle.
///     - The implementation of this function should be lock-free.
/// 
/// @returns
///     - ::XE_RESULT_SUCCESS
///     - ::XE_RESULT_ERROR_UNINITIALIZED
///     - ::XE_RESULT_ERROR_DEVICE_LOST
///     - ::XE_RESULT_ERROR_INVALID_ARGUMENT
///         + nullptr == hCommandList
///         + nullptr == ptr
///         + 0 for size
///     - ::XE_RESULT_ERROR_UNSUPPORTED
xe_result_t __xecall
xexCommandListReserveSpace(
    xex_command_list_handle_t hCommandList,         ///< [in] handle of the command list
    size_t size,                                    ///< [in] size (in bytes) to reserve
    void** ptr                                      ///< [out] pointer to command buffer space reserved
    )
{
    auto pfnReserveSpace = xex_lib::context.ddiTable.CommandList.pfnReserveSpace;
    if( nullptr == pfnReserveSpace )
        return XE_RESULT_ERROR_UNSUPPORTED;

    return pfnReserveSpace( hCommandList, size, ptr );
}

} // extern "C"

namespace xex
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Reserve a section of contiguous command buffer space within the
    ///        command list.
    /// 
    /// @details
    ///     - The pointer returned is valid for both Host and device access.
    ///     - The application may **not** call this function from simultaneous
    ///       threads with the same command list handle.
    ///     - The implementation of this function should be lock-free.
    /// 
    /// @returns
    ///     - void*: pointer to command buffer space reserved
    /// 
    /// @throws result_t
    void* __xecall
    CommandList::ReserveSpace(
        size_t size                                     ///< [in] size (in bytes) to reserve
        )
    {
        void* ptr;

        auto result = static_cast<result_t>( ::xexCommandListReserveSpace(
            reinterpret_cast<xex_command_list_handle_t>( getHandle() ),
            size,
            &ptr ) );

        if( result_t::SUCCESS != result )
            throw exception_t( result, __FILE__, STRING(__LINE__), "xex::CommandList::ReserveSpace" );

        return ptr;
    }

} // namespace xex

namespace xex
{
} // namespace xex
