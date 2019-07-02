/*
 *
 * Copyright (C) 2019 Intel Corporation
 *
 * SPDX-License-Identifier: MIT
 *
 * @file xe_common.cpp
 *
 * @brief C++ wrapper of Intel 'One API' Level-Zero API common types
 *
 * @cond DEV
 * DO NOT EDIT: generated from /scripts/core/common.yml
 * @endcond
 *
 */
#include "xe_lib.h"
#include <sstream>

extern "C" {

} // extern "C"

namespace xe
{
} // namespace xe

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts ipc_mem_handle_t to std::string
    std::string to_string( const ipc_mem_handle_t val )
    {
        std::string str;
        
        str += "ipc_mem_handle_t::data : ";
        str += val.data;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts ipc_event_pool_handle_t to std::string
    std::string to_string( const ipc_event_pool_handle_t val )
    {
        std::string str;
        
        str += "ipc_event_pool_handle_t::data : ";
        str += val.data;
        str += "\n";

        return str;
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @brief Converts result_t to std::string
    std::string to_string( const result_t val )
    {
        std::string str;

        switch( val )
        {
        case result_t::SUCCESS:
            str = "result_t::SUCCESS";
            break;

        case result_t::NOT_READY:
            str = "result_t::NOT_READY";
            break;

        case result_t::ERROR_UNINITIALIZED:
            str = "result_t::ERROR_UNINITIALIZED";
            break;

        case result_t::ERROR_DEVICE_LOST:
            str = "result_t::ERROR_DEVICE_LOST";
            break;

        case result_t::ERROR_UNSUPPORTED:
            str = "result_t::ERROR_UNSUPPORTED";
            break;

        case result_t::ERROR_INVALID_ARGUMENT:
            str = "result_t::ERROR_INVALID_ARGUMENT";
            break;

        case result_t::ERROR_OUT_OF_HOST_MEMORY:
            str = "result_t::ERROR_OUT_OF_HOST_MEMORY";
            break;

        case result_t::ERROR_OUT_OF_DEVICE_MEMORY:
            str = "result_t::ERROR_OUT_OF_DEVICE_MEMORY";
            break;

        case result_t::ERROR_MODULE_BUILD_FAILURE:
            str = "result_t::ERROR_MODULE_BUILD_FAILURE";
            break;

        case result_t::ERROR_UNKNOWN:
            str = "result_t::ERROR_UNKNOWN";
            break;

        default:
            str = "result_t::?";
            break;
        };

        return str;
    }

} // namespace xe

namespace xe
{
    ///////////////////////////////////////////////////////////////////////////////
    std::string exception_t::formatted(
        const result_t result,
        const char* file,
        const char* line,
        const char* func )
    {
    #ifdef _DEBUG
        std::stringstream msg;
        msg << file << "(" << line << ") : exception : " << func << "(" << xe::to_string(result) << ")";
        return msg.str();
    #else
        return xe::to_string(result);
    #endif
    }
} // namespace xe
